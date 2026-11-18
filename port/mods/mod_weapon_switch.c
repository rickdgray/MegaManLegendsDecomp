// Switch special weapon: a page in the pause panel that equips any special weapon Mega Man owns,
// from anywhere, instead of only through Roll.
//
// How the game tracks them:
// - Owned: scenario flag 0x4C0 + id (Sce_flag, 0x800BE378, bit 0x80 >> (flag & 7)). Roll's
//   equip list (r3_sup func_801D952C, ids from D_801DC0C8) and the pause menu's special-weapon
//   screen (sub_scrn.c) both test it. Ids 2-13 are the special weapons; id 1 is the buster
//   (the buster part's slot, PL_WORK.value171), id 0 is no special weapon.
// - Chosen: PL_WORK +0x172 (the special weapon picked at Roll's, kept in the save). In use:
//   +0x170, the weapon the handlers (D_8008A08C) and the shot spawner read; +0x44F says the
//   special weapon is out (the pause menu's special-weapon screen puts it away and back), and
//   +0x44E > 0 says weapons are usable in this area (0 in towns: the room loader sets +0x170
//   from +0x172 and +0x44F on the way out, scene.c).
// - Energy: PL_WORK.parts[id].value06 (+0x4F4 + id * 8 + 6), kept per weapon.
//
// Equipping does what Roll's equip does (func_801D952C): +0x172 = id; where weapons are
// usable, Obj_work_flag_change(8, 0x80) (removes the old weapon's shots before its code goes
// away), +0x170 = +0x172 and +0x44F = (id > 0). Roll then calls func_8001F5E4, which queues the
// weapon's ARM file (D_80089208[id]: the projectile code at 0x800D8800 and its data) on the CD.
// The pause menu does that itself when it closes: func_80015FE8 state 3 calls func_8001F5E4 and
// state 4 hands the field back only when the CD queue is empty (Cd_read_sync2), so the new
// weapon's code is in memory before Mega Man can fire it. The page therefore only changes
// Player_work while the pause menu is up and leaves the loading to the game's own exit path.
// Roll also refills the weapon's energy (func_80037594); here that is the setting "Refill
// energy" (off by default: weapons keep the energy they had).
#include "mods.h"

#include "port_game.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FUNC_OBJ_FLAG_CHANGE 0x8002EE90u // void Obj_work_flag_change(sint32 mask, sint32 flags)
#define FUNC_REFILL          0x80037594u // void func_80037594(void): parts[+0x172] energy full
#define FUNC_ENERGY_MAX      0x80037604u // sint32 func_80037604(PL_WORK *wp, sint32 id)
#define SCE_FLAG             0x800BE378u // Sce_flag[]
#define SUB_WORK             0x800A38F0u // D_800A38F0, the sub-screen's state word
#define FLAG_OWNED           0x4C0       // + id

#define PL_IN_USE    (MODS_PLAYER_WORK + 0x170) // sint8: the special weapon in use
#define PL_CHOSEN    (MODS_PLAYER_WORK + 0x172) // sint8: the special weapon chosen at Roll's
#define PL_SHOT      (MODS_PLAYER_WORK + 0x174) // value174: 0x40 special / 0x80 buster firing
#define PL_ARMED     (MODS_PLAYER_WORK + 0x44E) // sint8: > 0 where weapons are usable
#define PL_OUT       (MODS_PLAYER_WORK + 0x44F) // the special weapon is out
#define PL_ENERGY(i) (MODS_PLAYER_WORK + 0x4F4 + (i) * 8 + 6) // parts[i].value06

#define POKE8(a, v) (*(volatile uint8_t *)(uintptr_t)(a) = (uint8_t)(v))

#define NWEAPONS 14 // ids 0..13 (1 is the buster, never a special weapon)

// The names the pause menu's special-weapon screen shows (R-ARM WEAPONS), in the game's order
// (ids 2..13; Capcom's debug menu calls them M_GUN, SHOT, DRILL, BOMB, SPREAD, VACUUM, HOMING,
// BLADE, BOMB2, MINE, SHIELD, LASER). Id 0, no special weapon, is the Normal Arm.
static const char *const names[NWEAPONS] = {
    "Normal Arm",     // 0
    NULL,             // 1: the buster
    "Machine Buster", // 2
    "Powered Buster", // 3
    "Drill Arm",      // 4
    "Grenade Arm",    // 5
    "Spread Buster",  // 6
    "Vacuum Arm",     // 7
    "Active Buster",  // 8
    "Blade Arm",      // 9
    "Grand Grenade",  // 10
    "Splash Mine",    // 11
    "Shield Arm",     // 12
    "Shining Laser",  // 13
};

static const char *const off_on[] = {"Off", "On"};

static MOD_SETTING settings[] = {
    {"refill", "Refill energy", off_on, 2, 0, 0},
};

// The page: line 0 "Refill energy", then the weapons (None first).
static int list[NWEAPONS];
static int nlist;
static int cur;
static int top;
static const char *msg;
static int msg_colour;

static int owned(int id)
{
    int flag = FLAG_OWNED + id;

    return (MODS_PEEK8(SCE_FLAG + (flag >> 3)) & (0x80 >> (flag & 7))) != 0;
}

// The weapons to offer: None, then every owned special weapon in the game's order.
static void build_list(void)
{
    int id;

    nlist         = 0;
    list[nlist++] = 0;
    for (id = 2; id < NWEAPONS; id++)
    {
        if (owned(id))
        {
            list[nlist++] = id;
        }
    }
}

static int energy_max(int id)
{
    return ((int32_t (*)(uint8_t *, int32_t))(uintptr_t)FUNC_ENERGY_MAX)(
        (uint8_t *)(uintptr_t)MODS_PLAYER_WORK, id);
}

static const char *name_of(int id)
{
    return id >= 0 && id < NWEAPONS && names[id] != NULL ? names[id] : "?";
}

static void equip(int id)
{
    int chosen = (int8_t)MODS_PEEK8(PL_CHOSEN);

    if (id != 0 && !owned(id))
    {
        msg        = "Not owned";
        msg_colour = OVL_OFF;
        return;
    }
    // The pause menu's other screens show and change the weapon themselves (the special-weapon
    // screen puts it away); keep to the top screen, as Roll's equip runs with nothing else open.
    if (MODS_PEEK8(SUB_WORK) != 1)
    {
        msg        = "Go back to the top menu first";
        msg_colour = OVL_OFF;
        return;
    }
    // A shot in progress belongs to the weapon in use (its handler state, value177/178).
    if (MODS_PEEK8(PL_SHOT) & 0xC0)
    {
        msg        = "A shot is on its way: try again";
        msg_colour = OVL_OFF;
        return;
    }
    if (id == chosen && !settings[0].value)
    {
        msg        = "Already equipped";
        msg_colour = OVL_DIM;
        return;
    }
    // Roll's equip (r3_sup func_801D952C).
    POKE8(PL_CHOSEN, id);
    if (settings[0].value)
    {
        ((void (*)(void))(uintptr_t)FUNC_REFILL)();
    }
    if ((int8_t)MODS_PEEK8(PL_ARMED) > 0)
    {
        ((void (*)(int32_t, int32_t))(uintptr_t)FUNC_OBJ_FLAG_CHANGE)(8, 0x80);
        POKE8(PL_IN_USE, id);
        POKE8(PL_OUT, id > 0 ? 1 : 0);
        msg = "Equipped: loads when you unpause";
    }
    else
    {
        msg = "Equipped: usable outside towns";
    }
    msg_colour = OVL_ON;
    port_log("weapon_switch: equipped %d (%s), was %d; in use %d, out %d, energy %d", id,
             name_of(id), chosen, (int8_t)MODS_PEEK8(PL_IN_USE), MODS_PEEK8(PL_OUT),
             id > 0 ? MODS_PEEK16(PL_ENERGY(id)) : 0);
}

static void page_draw(MOD *m, PORT_OVERLAY *o, int row, int bottom, int focused)
{
    int col = 4, rows, i, chosen;

    if (!m->enabled)
    {
        port_overlay_print(o, row, col, OVL_DIM, "Switch it on to change weapons.");
        return;
    }
    build_list();
    if (cur > nlist)
    {
        cur = nlist;
    }
    chosen = (int8_t)MODS_PEEK8(PL_CHOSEN);
    port_overlay_print(o, row, col, OVL_TITLE, "Equipped: %.20s", name_of(chosen));
    if (chosen > 0 && (int8_t)MODS_PEEK8(PL_ARMED) > 0 && !MODS_PEEK8(PL_OUT))
    {
        port_overlay_print(o, row + 1, col + 10, OVL_DIM, "(put away)");
    }
    row += 2;
    port_overlay_print(o, row, col, focused && cur == 0 ? OVL_CURSOR : OVL_TEXT, "%s %-20s",
                       focused && cur == 0 ? ">" : " ", settings[0].label);
    port_overlay_print(o, row, col + 23, settings[0].value ? OVL_ON : OVL_OFF, "%s",
                       off_on[settings[0].value]);
    row += 2;
    rows = bottom - row; // the last row is the page's note
    if (cur - 1 < top)
    {
        top = cur > 0 ? cur - 1 : 0;
    }
    if (cur - 1 >= top + rows)
    {
        top = cur - rows;
    }
    for (i = 0; i < rows && top + i < nlist; i++)
    {
        int id = list[top + i], sel = focused && cur == top + i + 1;

        port_overlay_print(o, row + i, col, sel ? OVL_CURSOR : OVL_TEXT, "%s %c %-14s",
                           sel ? ">" : " ", id == chosen ? '*' : ' ', name_of(id));
        if (id > 0)
        {
            char energy[16];

            snprintf(energy, sizeof(energy), "%d/%d", MODS_PEEK16(PL_ENERGY(id)), energy_max(id));
            port_overlay_print(o, row + i, col + 23, OVL_DIM, "%9s", energy);
        }
    }
    if (msg != NULL)
    {
        port_overlay_print(o, bottom, col, msg_colour, "%.32s", msg);
    }
    else if (nlist == 1)
    {
        port_overlay_print(o, bottom, col, OVL_DIM, "No special weapons yet");
    }
    else
    {
        port_overlay_print(o, bottom, col, OVL_DIM, "Cross: equip  (* equipped)");
    }
}

static int page_input(MOD *m, uint16_t pressed)
{
    if (!m->enabled)
    {
        return (pressed & PSX_PAD_UP) != 0;
    }
    build_list();
    if (pressed & (PSX_PAD_UP | PSX_PAD_DOWN | PSX_PAD_LEFT | PSX_PAD_RIGHT))
    {
        msg = NULL;
    }
    if (pressed & PSX_PAD_UP)
    {
        if (cur == 0)
        {
            return 1;
        }
        cur--;
    }
    if ((pressed & PSX_PAD_DOWN) && cur < nlist)
    {
        cur++;
    }
    if (cur == 0)
    {
        if (pressed & (PSX_PAD_LEFT | PSX_PAD_RIGHT | PSX_PAD_CROSS | PSX_PAD_CIRCLE))
        {
            settings[0].value = !settings[0].value;
            mods_save_setting(m, &settings[0]);
        }
    }
    else if (pressed & (PSX_PAD_CROSS | PSX_PAD_CIRCLE))
    {
        equip(list[cur - 1]);
    }
    return 0;
}

MOD mod_weapon_switch = {
    "weapon_switch",
    "Switch special weapon",
    "Equips any special weapon you own from the pause menu, as Roll does. The new weapon "
    "loads when you unpause.",
    settings,
    1,
    NULL,
    NULL,
    page_draw,
    page_input,
    0,
};
