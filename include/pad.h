#ifndef PAD_H
#define PAD_H

#include "common.h"

// Pad buttons, as Capcom reads them (PAD_NOW = ~raw, so 1 = pressed).
// Layout from the Library Overview, "Button status bit assign", byte-swapped by the 16-bit read.
#define PAD_SELECT   0x0001
#define PAD_L3       0x0002
#define PAD_R3       0x0004
#define PAD_START    0x0008
#define PAD_UP       0x0010
#define PAD_RIGHT    0x0020
#define PAD_DOWN     0x0040
#define PAD_LEFT     0x0080
#define PAD_L2       0x0100
#define PAD_R2       0x0200
#define PAD_L1       0x0400
#define PAD_R1       0x0800
#define PAD_TRIANGLE 0x1000
#define PAD_CIRCLE   0x2000
#define PAD_CROSS    0x4000
#define PAD_SQUARE   0x8000

// Bit 0 is set by the pad each frame; bit 1 holds the previous frame's bit 0.
typedef union
{
    uint8 all;
    struct
    {
        uint8 cur : 1;
        uint8 prev : 1;
    } bit;
} PAD_FLAGS;

// PAD_WORK, the per-controller state, has a different layout in each program (ROCK_NEO adds the
// auto-repeat state), so each defines it in its own include/<target>/pad_work.h. It needs
// PAD_FLAGS, so it's included here rather than at the top.
#include "pad_work.h"

#define PAD_RAW(p) (*(uint16 *)(p).raw)
#define PAD_NOW(p) (*(uint16 *)(p).now)
#define PAD_OLD(p) (*(uint16 *)(p).old)
#define PAD_ON(p)  (*(uint16 *)(p).on)
#define PAD_OFF(p) (*(uint16 *)(p).off)

// Both programs (shim 0x8005B570, ROCK_NEO 0x800C0C00).
extern PAD_WORK Joy1; // controller 1
extern PAD_WORK Joy2; // controller 2

void Pad_update(PAD_WORK *pad);
void Pad_update_all(void);

// Shim only.
void Disp_adjust(void);

// ROCK_NEO only.
void Pad_repeat_update(PAD_WORK *pad);
void func_80012350(PAD_WORK *pad, sint32 mask, sint32 i);

#endif // PAD_H
