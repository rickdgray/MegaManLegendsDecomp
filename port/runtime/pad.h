// PS1 controller state and the receive-buffer format the game reads (PAD_WORK in
// include/rock_neo.exe/pad.h: status, id, buttons, then four analog bytes).
// Host input (SDL gamepad and keyboard) fills a PSX_PAD_STATE in platform_sdl.c.
#ifndef PORT_PAD_H
#define PORT_PAD_H

#include <stdint.h>

// Button bits as the PS1 reports them (in the buffer they are active-low).
#define PSX_PAD_SELECT   0x0001
#define PSX_PAD_L3       0x0002
#define PSX_PAD_R3       0x0004
#define PSX_PAD_START    0x0008
#define PSX_PAD_UP       0x0010
#define PSX_PAD_RIGHT    0x0020
#define PSX_PAD_DOWN     0x0040
#define PSX_PAD_LEFT     0x0080
#define PSX_PAD_L2       0x0100
#define PSX_PAD_R2       0x0200
#define PSX_PAD_L1       0x0400
#define PSX_PAD_R1       0x0800
#define PSX_PAD_TRIANGLE 0x1000
#define PSX_PAD_CIRCLE   0x2000
#define PSX_PAD_CROSS    0x4000
#define PSX_PAD_SQUARE   0x8000

// The port's own buttons (PSX_PAD_STATE.host): bound in the settings, never sent to the game.
#define PORT_HOST_MODS 0x0001 // opens the mod panel ([keyboard]/[gamepad] mods_menu)

// Controller ids in the second buffer byte.
#define PSX_PAD_ID_DIGITAL 0x41
#define PSX_PAD_ID_ANALOG  0x73 // DualShock in analog mode

typedef struct
{
    int connected;
    int analog;       // report as an analog pad (id 0x73) with stick bytes
    uint16_t buttons; // PSX_PAD_* bits, 1 = pressed
    uint8_t lx, ly;   // sticks, 0x00..0xFF with 0x80 at rest (y grows downwards)
    uint8_t rx, ry;
    uint16_t host; // PORT_HOST_* bits: the port's own buttons (not part of the PS1 pad)
} PSX_PAD_STATE;

// Writes the receive buffer for one port: status (0x00 ok, 0xFF nothing connected), id,
// buttons (active-low, little-endian), then RX, RY, LX, LY. `size` is at least 2.
void psx_pad_to_buffer(const PSX_PAD_STATE *s, uint8_t *buf, int size);

// Sets every field to "connected, analog, nothing pressed, sticks centred".
void psx_pad_reset(PSX_PAD_STATE *s);

#endif
