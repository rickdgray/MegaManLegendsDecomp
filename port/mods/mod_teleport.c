// Teleport: a page in the pause panel that moves Mega Man to any room of the game.
//
// The destinations (mod_teleport_dests.c) are the arrival points of the game's own doors: every
// stage module has a table of exit lists by room, and an exit names the stage and room it leads
// to and where Mega Man appears there, facing which way (tools/teleport_dests.py reads them).
//
// A teleport goes through the same path as a door. Leaving a room by a door, func_80050C2C
// (code_80048620.c) fills the room-entry request D_800C3558 (GAME_ENTRY_WORK: arrival x/y/z,
// facing, stage, room, fades) with flags14 = 2 and starts the next room's music
// (func_8001F6C4). The field state, func_800158F0 (Game_main_tbl[3], game.c) in its state 2,
// sees the request, fades out, and at state 6 reloads: Game_work.routine_0 = 1 (the stage
// loader) for another stage, 2 for another room of the same stage. The loaders place
// Mega Man with func_80015EE8 and set Game_work's stage and room (+0x50, +0x51).
//
// From the panel: choosing a destination closes the game's pause menu the way Start does on its
// top screen (the sub-screen's state word D_800A38F0 = 8, func_80060DB8: returns 1, and
// func_80015FE8 takes the field back) and closes the panel. The mod hooks func_800158F0; once
// the field is back in its normal state 2 with no request, no cutscene and no fade, it writes
// the request and calls the music function exactly as a door does, then lets the state run.
// Nothing is saved: the memory card is untouched.
//
// "Return to where I was" goes back to the stage, room, position and facing Mega Man had when
// the last teleport was chosen (a teleport back also becomes the new return point).
#include "mods.h"

#include "mod_teleport.h"
#include "port_game.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FUNC_FIELD    0x800158F0u // void func_800158F0(GAME_WORK *wp): Game_main_tbl[3]
#define FUNC_MUSIC    0x8001F6C4u // void func_8001F6C4(void): the next room's music (exits)
#define ENTRY         0x800C3558u // D_800C3558, GAME_ENTRY_WORK (include/rock_neo.exe/game.h)
#define SUB_WORK      0x800A38F0u // D_800A38F0, the sub-screen's SUB_WORK (sub_scrn.h)
#define SCENE_WORK    0x800C4C48u // Scene_work: non-zero during a cutscene
#define FADE_BUSY     0x80098A72u // D_80098A72: a screen fade is running
#define PL_POSITION   (MODS_PLAYER_WORK + 0x14) // PL_WORK.position x, y, z
#define PL_ROTATION_Y (MODS_PLAYER_WORK + 0x56) // PL_WORK.rotation.y

#define POKE8(a, v)  MODS_POKE8(a, v)
#define POKE16(a, v) MODS_POKE16(a, v)

typedef void (*FIELD_FN)(uint32_t wp);

static FIELD_FN orig_field;

static TP_DEST pending; // the requested destination
static int pending_on;  // waiting for the field to take it
static char pending_name[40];
static TP_DEST back; // "Return to where I was"
static int back_on;
static char back_name[40];

// The page.
static int view;     // 0: the area list (line 0 is "Return"), 1: an area's destinations
static int area_cur; // area list line (0 Return, 1.. areas)
static int area_top;
static int dest_cur; // line in the area
static int dest_top;
static int armed = -1;  // a destination with a warning: the first Cross arms it
static const char *msg; // a one-line note under the list
static int msg_colour;

// --- the teleport -----------------------------------------------------------------------------

static void field_hook(uint32_t wp)
{
    if (pending_on && MODS_PEEK8(wp + 1) == 2 && MODS_PEEK8(ENTRY + 0x14) == 0 && MODS_PEEK8(SCENE_WORK) == 0 &&
        MODS_PEEK16(FADE_BUSY) == 0)
    {
        // As func_80050C2C does for a door (its kinds 2, 4-6 and 8).
        POKE16(ENTRY + 0x08, pending.x);
        POKE16(ENTRY + 0x0A, pending.y);
        POKE16(ENTRY + 0x0C, pending.z);
        POKE16(ENTRY + 0x12, pending.rot);
        POKE8(ENTRY + 0x16, pending.stage);
        POKE8(ENTRY + 0x17, pending.room);
        POKE8(ENTRY + 0x15, 0);    // flags15
        POKE8(ENTRY + 0x19, 0x15); // fade out
        POKE8(ENTRY + 0x18, 2);    // fade in
        POKE8(ENTRY + 0x14, 2);    // flags14: a door request
        mods_call(FUNC_MUSIC, 0, 0, 0, 0, 0);
        pending_on = 0;
        port_log("teleport: to stage %02X room %02X at (%d, %d, %d) facing 0x%03X (%s)",
                 pending.stage, pending.room, pending.x, pending.y, pending.z, pending.rot & 0xFFF,
                 pending.name);
    }
    orig_field(wp);
}

// Leaves the pause menu and the panel; the field hook does the rest.
static void go(const TP_DEST *d)
{
    TP_DEST t = *d; // d may be `back`, rewritten below

    // The sub-screen's top screen is state 1 (func_8005ECE0); another screen (items, parts,
    // ...) has its own way out, so ask the player to go back to the top first.
    if (MODS_PEEK8(SUB_WORK) != 1)
    {
        msg        = "Go back to the top menu first";
        msg_colour = OVL_OFF;
        return;
    }
    snprintf(pending_name, sizeof(pending_name), "%s", d->name);
    t.name = pending_name;

    back.stage = MODS_PEEK8(MODS_GAME_WORK + 0x50);
    back.room  = MODS_PEEK8(MODS_GAME_WORK + 0x51);
    back.x     = MODS_PEEK16(PL_POSITION + 0);
    back.y     = MODS_PEEK16(PL_POSITION + 2);
    back.z     = MODS_PEEK16(PL_POSITION + 4);
    back.rot   = MODS_PEEK16(PL_ROTATION_Y) & 0xFFF;
    snprintf(back_name, sizeof(back_name), "Stage %02X Room %02X (%d, %d)", back.stage, back.room,
             back.x, back.z);
    back.name    = back_name;
    back.warning = NULL;
    back_on      = 1;

    pending    = t;
    pending_on = 1;
    armed      = -1;
    view       = 0; // reopened, the page shows the areas (Return is one line up)
    msg        = NULL;
    port_log("teleport: chosen: stage %02X room %02X (%s); return point stage %02X room %02X at "
             "(%d, %d, %d)",
             t.stage, t.room, t.name, back.stage, back.room, back.x, back.y, back.z);
    MODS_POKE32(SUB_WORK, 8); // as Start on the top screen
    mods_panel_close();
}

// --- the page ---------------------------------------------------------------------------------

static void scroll(int cur, int *top, int rows)
{
    if (cur < *top)
    {
        *top = cur;
    }
    if (cur >= *top + rows)
    {
        *top = cur - rows + 1;
    }
}

static void page_draw(MOD *m, PORT_OVERLAY *o, int top, int bottom, int focused)
{
    int rows = bottom - top - 1; // the last row is the page's own hint
    int col  = 4, i;

    if (!m->enabled)
    {
        port_overlay_print(o, top, col, OVL_DIM, "Switch it on to teleport.");
        return;
    }
    if (pending_on)
    {
        port_overlay_print(o, top, col, OVL_ON, "On the way: %.24s", pending.name);
        top++;
        rows--;
    }
    if (view == 0)
    {
        int n = 1 + tp_area_count;

        scroll(area_cur, &area_top, rows);
        for (i = 0; i < rows && area_top + i < n; i++)
        {
            int line = area_top + i, sel = focused && line == area_cur;

            if (line == 0)
            {
                port_overlay_print(o, top + i, col,
                                   sel       ? OVL_CURSOR
                                   : back_on ? OVL_TEXT
                                             : OVL_DIM,
                                   "%s Return to where I was", sel ? ">" : " ");
            }
            else
            {
                const TP_AREA *a = &tp_areas[line - 1];

                port_overlay_print(o, top + i, col, sel ? OVL_CURSOR : OVL_TEXT, "%s %-22.22s",
                                   sel ? ">" : " ", a->name);
                port_overlay_print(o, top + i, col + 26, OVL_DIM, "%3d", a->count);
            }
        }
        if (msg != NULL)
        {
            port_overlay_print(o, bottom, col, msg_colour, "%.32s", msg);
        }
        else if (focused && area_cur == 0 && back_on)
        {
            port_overlay_print(o, bottom, col, OVL_DIM, "%.32s", back_name);
        }
        else
        {
            port_overlay_print(o, bottom, col, OVL_DIM, "Cross: open an area");
        }
        return;
    }
    {
        const TP_AREA *a = &tp_areas[area_cur - 1];
        const TP_DEST *cur;

        port_overlay_print(o, top, col, OVL_TITLE, "%.30s", a->name);
        top++;
        rows--;
        scroll(dest_cur, &dest_top, rows);
        for (i = 0; i < rows && dest_top + i < a->count; i++)
        {
            int line = dest_top + i, sel = focused && line == dest_cur;
            const TP_DEST *d = &tp_dests[a->first + line];

            port_overlay_print(o, top + i, col,
                               sel          ? OVL_CURSOR
                               : d->warning ? OVL_DIM
                                            : OVL_TEXT,
                               "%s %.30s", sel ? ">" : " ", d->name);
        }
        cur = &tp_dests[a->first + dest_cur];
        if (msg != NULL)
        {
            port_overlay_print(o, bottom, col, msg_colour, "%.32s", msg);
        }
        else if (cur->warning != NULL)
        {
            port_overlay_print(o, bottom, col, OVL_OFF, "! %.30s", cur->warning);
        }
        else
        {
            port_overlay_print(o, bottom, col, OVL_DIM, "Cross: go  Circle/Left: areas");
        }
    }
}

static int page_input(MOD *m, uint16_t pressed)
{
    if (!m->enabled)
    {
        return (pressed & PSX_PAD_UP) != 0;
    }
    if (pressed & (PSX_PAD_UP | PSX_PAD_DOWN | PSX_PAD_LEFT | PSX_PAD_RIGHT | PSX_PAD_CIRCLE))
    {
        msg = NULL;
    }
    if (view == 0)
    {
        int n = 1 + tp_area_count;

        if (pressed & PSX_PAD_UP)
        {
            if (area_cur == 0)
            {
                return 1;
            }
            area_cur--;
        }
        if ((pressed & PSX_PAD_DOWN) && area_cur < n - 1)
        {
            area_cur++;
        }
        if (pressed & PSX_PAD_RIGHT)
        {
            area_cur = area_cur + 5 < n ? area_cur + 5 : n - 1;
        }
        if (pressed & PSX_PAD_LEFT)
        {
            area_cur = area_cur > 5 ? area_cur - 5 : 0;
        }
        if (pressed & PSX_PAD_CROSS)
        {
            if (area_cur == 0)
            {
                if (back_on)
                {
                    go(&back);
                }
                else
                {
                    msg        = "No teleport yet";
                    msg_colour = OVL_DIM;
                }
            }
            else
            {
                view     = 1;
                dest_cur = dest_top = 0;
                armed               = -1;
            }
        }
        return 0;
    }
    {
        const TP_AREA *a = &tp_areas[area_cur - 1];

        if (pressed & (PSX_PAD_CIRCLE | PSX_PAD_LEFT))
        {
            view  = 0;
            armed = -1;
            return 0;
        }
        if (pressed & PSX_PAD_UP)
        {
            dest_cur = dest_cur > 0 ? dest_cur - 1 : a->count - 1;
            armed    = -1;
        }
        if (pressed & PSX_PAD_DOWN)
        {
            dest_cur = dest_cur < a->count - 1 ? dest_cur + 1 : 0;
            armed    = -1;
        }
        if (pressed & PSX_PAD_RIGHT)
        {
            dest_cur = dest_cur + 5 < a->count ? dest_cur + 5 : a->count - 1;
            armed    = -1;
        }
        if (pressed & PSX_PAD_CROSS)
        {
            const TP_DEST *d = &tp_dests[a->first + dest_cur];

            if (d->warning != NULL && armed != a->first + dest_cur)
            {
                armed      = a->first + dest_cur;
                msg        = "May be unstable: Cross again";
                msg_colour = OVL_OFF;
            }
            else
            {
                go(d);
            }
        }
    }
    return 0;
}

static void enable(MOD *m, int on)
{
    (void)m;
    if (on)
    {
        orig_field = (FIELD_FN)mods_hook(FUNC_FIELD, (void *)field_hook);
    }
    else
    {
        mods_unhook(FUNC_FIELD);
        pending_on = 0;
    }
}

MOD mod_teleport = {
    "teleport",
    "Teleport",
    "Moves Mega Man to any room, through the game's own door path. Choose an area, then a "
    "place.",
    NULL,
    0,
    enable,
    NULL,
    page_draw,
    page_input,
    0,
};
