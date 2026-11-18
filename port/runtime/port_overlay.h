// A text layer drawn over the game picture by the window (platform_sdl.c): the port's own menus
// (the mod system's start-up choice and its pause panel, port/mods/). The game never sees it:
// it is not in VRAM, so dumps, hashes and the game's own rendering are unchanged.
//
// The layer is a grid of 8x8 characters over a 320x240 picture (40 columns, 30 rows), drawn
// with SDL's built-in debug font, scaled like the game. A panel is a box of cells with a dark
// translucent background. The game process fills it; the one-window host (port_remote.h)
// receives a copy with every frame.
#ifndef PORT_OVERLAY_H
#define PORT_OVERLAY_H

#include <stdint.h>

#define PORT_OVERLAY_COLS 40
#define PORT_OVERLAY_ROWS 30

// Text colours.
enum
{
    OVL_TEXT,   // plain
    OVL_DIM,    // hints, descriptions
    OVL_TITLE,  // headings
    OVL_CURSOR, // the selected line
    OVL_ON,     // a switched-on value
    OVL_OFF,    // a switched-off value
    OVL_COLOURS
};

typedef struct
{
    int32_t visible;      // 0: nothing is drawn
    int32_t shade;        // 0-255: darkens the whole picture under the panel
    int32_t box_x, box_y; // the panel, in cells
    int32_t box_w, box_h; // (0 wide: no panel background)
    char text[PORT_OVERLAY_ROWS][PORT_OVERLAY_COLS]; // 0 or ' ': nothing
    uint8_t colour[PORT_OVERLAY_ROWS][PORT_OVERLAY_COLS];
} PORT_OVERLAY;

// This process's layer (what platform_present draws over the game).
PORT_OVERLAY *port_overlay(void);

// Empties the layer and hides it.
void port_overlay_clear(PORT_OVERLAY *o);
// Sets the panel box (cells) and makes the layer visible.
void port_overlay_box(PORT_OVERLAY *o, int x, int y, int w, int h, int shade);
// printf-style text at a cell; clipped at the right edge. Returns the column after the text.
int port_overlay_print(PORT_OVERLAY *o, int row, int col, int colour, const char *fmt, ...)
    __attribute__((format(printf, 5, 6)));
// The same, centred in the panel box (or the screen when there is none).
void port_overlay_center(PORT_OVERLAY *o, int row, int colour, const char *fmt, ...)
    __attribute__((format(printf, 4, 5)));
// Writes the visible text to stderr, one line per row (headless tests and logs).
void port_overlay_log(const PORT_OVERLAY *o, const char *title);

#endif
