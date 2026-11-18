// The mod system's menus (mods.h): the start-up choice before the game, and the pause panel over
// the game's own pause menu. Both are drawn on the port's text layer (port_overlay.h).
//
// Panel controls (pad 1): Up/Down choose, Left/Right change a value, Cross or Circle open or
// switch, Triangle goes back (closes on the mod list), Start or the mod-panel button closes.
#define _GNU_SOURCE
#include "mods_internal.h"

#include "port_game.h"
#ifdef PORT_HAVE_SDL
#include "platform_sdl.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DIRS (PSX_PAD_UP | PSX_PAD_DOWN | PSX_PAD_LEFT | PSX_PAD_RIGHT)
#define OK   (PSX_PAD_CROSS | PSX_PAD_CIRCLE)

// --- input edges with d-pad repeat ------------------------------------------------------------

typedef struct
{
    uint16_t prev, prev_host;
    int hold; // frames the same d-pad direction has been held
} EDGES;

// The newly pressed buttons (PSX_PAD_*), with the d-pad repeating while held.
static uint16_t edges(EDGES *e, uint16_t buttons, uint16_t host, uint16_t *host_pressed)
{
    uint16_t pressed = buttons & ~e->prev;

    if ((buttons & DIRS) != 0 && (buttons & DIRS) == (e->prev & DIRS))
    {
        e->hold++;
        if (e->hold >= 10 && (e->hold - 10) % 3 == 0)
        {
            pressed |= buttons & DIRS;
        }
    }
    else
    {
        e->hold = 0;
    }
    *host_pressed = host & ~e->prev_host;
    e->prev       = buttons;
    e->prev_host  = host;
    return pressed;
}

// --- shared drawing ---------------------------------------------------------------------------

static void draw_hints(PORT_OVERLAY *o, int row, const char *a, const char *b)
{
    port_overlay_center(o, row, OVL_DIM, "%s", a);
    if (b != NULL)
    {
        port_overlay_center(o, row + 1, OVL_DIM, "%s", b);
    }
}

// Word-wraps `text` into rows from `row` (at most `rows`), `width` columns from `col`.
static int draw_wrapped(PORT_OVERLAY *o, int row, int col, int width, int rows, const char *text)
{
    const char *p = text;
    int used      = 0;

    while (*p != 0 && used < rows)
    {
        int n = (int)strlen(p), cut = n;

        if (n > width)
        {
            cut = width;
            while (cut > 0 && p[cut] != ' ')
            {
                cut--;
            }
            if (cut == 0)
            {
                cut = width;
            }
        }
        port_overlay_print(o, row + used, col, OVL_DIM, "%.*s", cut, p);
        p += cut;
        while (*p == ' ')
        {
            p++;
        }
        used++;
    }
    return used;
}

// One "label   < value >" line; the value centred in its brackets.
static void draw_value_line(PORT_OVERLAY *o, int row, int col, int width, int selected,
                            const char *label, const char *value, int colour)
{
    int vcol = col + width - 10;

    port_overlay_print(o, row, col, selected ? OVL_CURSOR : OVL_TEXT, "%s %s", selected ? ">" : " ",
                       label);
    port_overlay_print(o, row, vcol, selected ? OVL_CURSOR : OVL_DIM, "<");
    port_overlay_print(o, row, vcol + 1 + (8 - (int)strlen(value)) / 2, colour, "%s", value);
    port_overlay_print(o, row, vcol + 9, selected ? OVL_CURSOR : OVL_DIM, ">");
}

// Writes the layer to the log when it changed (modded runs only): headless tests read it.
static void log_layer(const char *what)
{
    static PORT_OVERLAY last;
    PORT_OVERLAY *o = port_overlay();

    if (memcmp(&last, o, sizeof(last)) == 0)
    {
        return;
    }
    memcpy(&last, o, sizeof(last));
    if (port_options.headless || port_options.verbose)
    {
        if (o->visible)
        {
            port_overlay_log(o, what);
        }
        else
        {
            port_log("%s: closed", what);
        }
    }
}

// --- the start-up menu ------------------------------------------------------------------------

#ifdef PORT_HAVE_SDL
// Rows: 0 Vanilla, 1 Mods, then one per mod.
static void draw_startup(int cursor)
{
    PORT_OVERLAY *o = port_overlay();
    int i, row;

    port_overlay_clear(o);
    port_overlay_box(o, 3, 3, 34, 24, 0);
    port_overlay_center(o, 4, OVL_TITLE, "MEGA MAN LEGENDS");
    port_overlay_center(o, 6, OVL_DIM, "How do you want to play?");
    port_overlay_print(o, 9, 6, cursor == 0 ? OVL_CURSOR : OVL_TEXT, "%s Vanilla",
                       cursor == 0 ? ">" : " ");
    port_overlay_print(o, 9, 18, OVL_DIM, "the original game");
    port_overlay_print(o, 11, 6, cursor == 1 ? OVL_CURSOR : OVL_TEXT, "%s Mods",
                       cursor == 1 ? ">" : " ");
    port_overlay_print(o, 11, 18, OVL_DIM, "the mods below");
    port_overlay_print(o, 12, 18, OVL_DIM, "(its own saves)");
    port_overlay_print(o, 14, 6, OVL_TITLE, "Mods for a modded run:");
    for (i = 0, row = 16; mods_list[i] != NULL && row < 22; i++, row++)
    {
        MOD *m  = mods_list[i];
        int sel = cursor == 2 + i;

        port_overlay_print(o, row, 6, sel ? OVL_CURSOR : OVL_TEXT, "%s [%c] %s", sel ? ">" : " ",
                           m->enabled ? 'x' : ' ', m->name);
        if (m->nsettings > 0 && m->enabled)
        {
            port_overlay_print(o, row, 31, OVL_DIM, "%s",
                               m->settings[0].choices[m->settings[0].value]);
        }
    }
    draw_hints(o, 22, "Up/Down choose  Cross/Start play",
               cursor >= 2 ? "Cross/Left/Right: switch a mod" : "Settings: pause menu, then M/R3");
    port_overlay_center(o, 25, OVL_DIM, "(keyboard: Enter Start, X Cross)");
}
#endif

void mods_startup_menu(void)
{
#ifdef PORT_HAVE_SDL
    PSX_PAD_STATE pads[PLATFORM_PADS];
    EDGES e;
    int cursor = 0, rows = 2 + mods_count(), first = 1;
    struct timespec frame = {0, 8000000};

    memset(&e, 0, sizeof(e));
    for (;;)
    {
        uint16_t pressed, host_pressed;

        if (!platform_poll(pads))
        {
            port_overlay_clear(port_overlay());
            exit(0); // the window was closed
        }
        pressed = edges(&e, pads[0].buttons, pads[0].host, &host_pressed);
        if (first)
        {
            pressed = 0; // buttons already down when the menu appeared count from their release
            first   = 0;
        }
        if (pressed & PSX_PAD_UP)
        {
            cursor = (cursor + rows - 1) % rows;
        }
        if (pressed & PSX_PAD_DOWN)
        {
            cursor = (cursor + 1) % rows;
        }
        if (cursor >= 2 && (pressed & (OK | PSX_PAD_LEFT | PSX_PAD_RIGHT)))
        {
            MOD *m = mods_list[cursor - 2];

            mods_set_enabled(m, !m->enabled);
        }
        if (cursor < 2 && (pressed & (OK | PSX_PAD_START)))
        {
            mods_mode = cursor == 1 ? MODS_ON : MODS_VANILLA;
            break;
        }
        if (cursor >= 2 && (pressed & PSX_PAD_START))
        {
            mods_mode = MODS_ON; // Start on a mod's line: play with the mods
            break;
        }
        draw_startup(cursor);
        platform_present();
        nanosleep(&frame, NULL);
    }
    port_overlay_clear(port_overlay());
    platform_present();
    port_log("mods: start-up menu: %s", mods_mode == MODS_ON ? "mods" : "vanilla");
#endif
}

// --- the pause panel --------------------------------------------------------------------------

#define PANEL_X     3
#define PANEL_Y     3
#define PANEL_W     34
#define PANEL_H     24
#define PANEL_TOP   (PANEL_Y + 3)           // first content row
#define PANEL_HINTS (PANEL_Y + PANEL_H - 2) // the two hint rows

static volatile int panel_open;
static volatile uint16_t raw_buttons, raw_host; // pad 1 as the player holds it
static volatile uint16_t suppress;              // kept from the game until released
static EDGES panel_edges;
static int page = -1; // -1: the mod list; else the mod's index
static int cursor;    // the list's line, or the page's (0 on/off, 1.. settings or its own page)

// The game's pause menu (the sub-screen) is up: Game_work.routine_0 == 4 (Game_main_tbl's
// sub-screen state, entered on Start in the field: game.c func_800158F0) and routine_1 == 2
// (the sub-screen running; 0/1 open it, 3/4 close it: func_80015FE8).
static int game_paused(void)
{
    return MODS_PEEK8(MODS_GAME_WORK + 0) == 4 && MODS_PEEK8(MODS_GAME_WORK + 1) == 2;
}

void mods_pad_filter(PSX_PAD_STATE pads[2])
{
    if (!mods_started)
    {
        return;
    }
    raw_buttons = pads[0].buttons;
    raw_host    = pads[0].host;
    if (panel_open)
    {
        pads[0].buttons = 0;
        pads[0].lx = pads[0].ly = pads[0].rx = pads[0].ry = 0x80;
        return;
    }
    if (suppress != 0)
    {
        suppress &= pads[0].buttons;
        pads[0].buttons &= (uint16_t)~suppress;
    }
}

static void draw_list(PORT_OVERLAY *o)
{
    int i, row;

    port_overlay_center(o, PANEL_Y + 1, OVL_TITLE, "MODS");
    for (i = 0, row = PANEL_TOP; mods_list[i] != NULL && row < PANEL_HINTS - 1; i++, row += 2)
    {
        MOD *m = mods_list[i];

        port_overlay_print(o, row, PANEL_X + 1, cursor == i ? OVL_CURSOR : OVL_TEXT, "%s %s",
                           cursor == i ? ">" : " ", m->name);
        port_overlay_print(o, row, PANEL_X + PANEL_W - 5, m->enabled ? OVL_ON : OVL_OFF, "%s",
                           m->enabled ? "ON" : "OFF");
    }
    draw_hints(o, PANEL_HINTS, "Cross: open  Left/Right: on/off", "Triangle/Start/M/R3: close");
}

static void draw_page(PORT_OVERLAY *o, MOD *m)
{
    int row = PANEL_TOP, i;

    port_overlay_center(o, PANEL_Y + 1, OVL_TITLE, "%s", m->name);
    if (m->about != NULL)
    {
        row += draw_wrapped(o, row, PANEL_X + 1, PANEL_W - 2, 4, m->about) + 1;
    }
    draw_value_line(o, row, PANEL_X + 1, PANEL_W - 2, cursor == 0, "Enabled",
                    m->enabled ? "ON" : "OFF", m->enabled ? OVL_ON : OVL_OFF);
    row += 2;
    if (m->page_draw != NULL)
    {
        m->page_draw(m, o, row, PANEL_HINTS - 2, cursor == 1);
    }
    else
    {
        for (i = 0; i < m->nsettings && row < PANEL_HINTS - 1; i++, row++)
        {
            MOD_SETTING *s = &m->settings[i];

            draw_value_line(o, row, PANEL_X + 1, PANEL_W - 2, cursor == i + 1, s->label,
                            s->choices[s->value], OVL_TEXT);
        }
    }
    draw_hints(o, PANEL_HINTS, "Up/Down choose  Left/Right change", "Triangle: back  Start: close");
}

static void close_panel(void)
{
    panel_open = 0;
    suppress   = raw_buttons; // the buttons still down reach the game only after a release
    port_overlay_clear(port_overlay());
    log_layer("mods: panel");
}

void mods_panel_close(void)
{
    if (panel_open)
    {
        close_panel();
    }
}

// One frame of the open panel; `pressed` is pad 1's new buttons.
static void panel_input(uint16_t pressed, uint16_t host_pressed)
{
    int nmods = mods_count();

    if ((host_pressed & PORT_HOST_MODS) || (pressed & PSX_PAD_START))
    {
        close_panel();
        return;
    }
    if (page < 0)
    {
        if (pressed & PSX_PAD_TRIANGLE)
        {
            close_panel();
            return;
        }
        if (pressed & PSX_PAD_UP)
        {
            cursor = (cursor + nmods - 1) % nmods;
        }
        if (pressed & PSX_PAD_DOWN)
        {
            cursor = (cursor + 1) % nmods;
        }
        if (pressed & (PSX_PAD_LEFT | PSX_PAD_RIGHT))
        {
            mods_set_enabled(mods_list[cursor], !mods_list[cursor]->enabled);
        }
        if (pressed & OK)
        {
            page   = cursor;
            cursor = 0;
        }
        return;
    }
    {
        MOD *m    = mods_list[page];
        int lines = 1 + (m->page_draw != NULL ? 1 : m->nsettings);

        if (pressed & PSX_PAD_TRIANGLE)
        {
            cursor = page;
            page   = -1;
            return;
        }
        if (m->page_draw != NULL && cursor == 1)
        {
            // The mod's own page has the cursor.
            if (m->page_input != NULL && m->page_input(m, pressed))
            {
                cursor = 0;
            }
            return;
        }
        if (pressed & PSX_PAD_UP)
        {
            cursor = (cursor + lines - 1) % lines;
        }
        if (pressed & PSX_PAD_DOWN)
        {
            cursor = (cursor + 1) % lines;
        }
        if (cursor == 0 && (pressed & (OK | PSX_PAD_LEFT | PSX_PAD_RIGHT)))
        {
            mods_set_enabled(m, !m->enabled);
        }
        else if (cursor > 0 && m->page_draw == NULL)
        {
            MOD_SETTING *s = &m->settings[cursor - 1];

            if (pressed & (PSX_PAD_RIGHT | OK))
            {
                mods_set_value(m, s, s->value + 1);
            }
            else if (pressed & PSX_PAD_LEFT)
            {
                mods_set_value(m, s, s->value - 1);
            }
        }
    }
}

void mods_frame(void)
{
    uint16_t pressed, host_pressed;
    PORT_OVERLAY *o = port_overlay();

    if (!mods_started)
    {
        return;
    }
    pressed = edges(&panel_edges, raw_buttons, raw_host, &host_pressed);
    if (!panel_open)
    {
        if ((host_pressed & PORT_HOST_MODS) && game_paused())
        {
            panel_open = 1;
            page       = -1;
            cursor     = 0;
            port_log("mods: panel opened");
        }
        else
        {
            return;
        }
    }
    else if (!game_paused())
    {
        close_panel(); // the pause menu went away underneath (it should not, without input)
        return;
    }
    else
    {
        panel_input(pressed, host_pressed);
        if (!panel_open)
        {
            return;
        }
    }
    port_overlay_clear(o);
    port_overlay_box(o, PANEL_X, PANEL_Y, PANEL_W, PANEL_H, 96);
    if (page < 0)
    {
        draw_list(o);
    }
    else
    {
        draw_page(o, mods_list[page]);
    }
    log_layer("mods: panel");
}
