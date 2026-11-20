#ifndef STCOM33_H
#define STCOM33_H

#include "common.h"
#include "psyq/libgpu.h"
#include "stage_common/rock_neo.h"

// PsyQ's DR_MOVE (a VRAM-to-VRAM move primitive, 0x18 bytes).
typedef struct
{
    u_long tag;
    u_long code[5];
} STCOM33_DR_MOVE;

// The display link record; ordering-table entries.
typedef struct
{
    uint8 reserved00[0x88];
    u_long ot_88;
} STCOM33_LINK;

// Where the next primitive goes (scratchpad).
#define STCOM33_PACKET_PTR (*(STCOM33_DR_MOVE **)0x1F800070)

// A texture that scrolls in VRAM: two 0x40- and 0x20-line strips, moved down by the scroll
// offset and wrapped (one 0x24-byte event slot per texture).
typedef struct
{
    sint16 x0, y0; // 0: the 0x10-wide, 0x40-high strip
    sint16 x1, y1; // 4: the 8-wide, 0x20-high strip
    uint8 speed_8; // 8
    uint8 reserved9;
    uint16 flag_A; // A: scene flag that turns it on
} STCOM33_SCROLL;

// The 0x24-byte event slot (freed through Close_EVE_WORK).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[2];    // 01
    uint8 variant_3;        // 03: index into stcom33_D_0000
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 scroll_A;         // 0A
    uint8 reverse_B;        // 0B: scrolls up
    sint8 strips_C;         // 0C: 1 moves only the first strip, 2 only the second
    uint8 reserved0D[0x17]; // 0D
} STCOM33_WORK;

typedef void (*STCOM33_FUNC)(STCOM33_WORK *wp);

extern STCOM33_SCROLL stcom33_D_0000[]; // by variant_3
extern STCOM33_FUNC stcom33_D_003C[];   // routine_0 handlers (stcom33_func_0000)

// ROCK_NEO.EXE.
extern STCOM33_LINK *Disp_env_ptr;
sint32 Sce_flag_test(sint32 flag);
void SetDrawMove(STCOM33_DR_MOVE *p, RECT *rect, sint32 x, sint32 y);

#endif // STCOM33_H
