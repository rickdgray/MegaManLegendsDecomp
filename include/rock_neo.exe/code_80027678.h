#ifndef CODE_80027678_H
#define CODE_80027678_H

// code_80027678.c (not identified yet; rename with the file).

#include "common.h"

// Billboard sprite queued by func_8002D464 (0x28 bytes from Map_prim_ptr, listed in
// D_800BE6D8, counted by D_800988FC): a POLY_FT4 whose vertex words hold the sprite's world
// position, half size and flags until billboard_draw projects it and links it into the
// ordering table. func_8002D464 still returns it as a uint32 * (its user writes it by index).
typedef struct
{
    u_long tag;       // 0x00
    u_long rgbc;      // 0x04 r0, g0, b0, code
    sint32 xy0;       // 0x08 before: world x, y (two sint16)
    u_long uv0_clut;  // 0x0C
    sint32 xy1;       // 0x10 before: world z (sint16)
    u_long uv1_tpage; // 0x14
    sint32 xy2;       // 0x18 before: half size
    u_long uv2;       // 0x1C
    sint32 xy3;       // 0x20 before: flags (BILLBOARD_NO_FOG)
    u_long uv3;       // 0x24
} BILLBOARD;

#define BILLBOARD_NO_FOG 8 // xy3 flag: keep the color, no depth cue or fog CLUT

extern uint32 D_800988FC;            // number of queued billboards
extern BILLBOARD *D_800BE6D8[0x100]; // the queued billboards

uint32 *func_8002D4B8(void); // returns a free line primitive (func_80047EC8)
uint32 *func_8002D464(void); // returns a free primitive in the ordering table

#endif // CODE_80027678_H
