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

// Per-controller state. The first 8 bytes are the raw buffer given to InitPAD.
// Every member is a byte (or a bit field): the target copies the struct with lwl/lwr and reaches
// the flag bits with byte accesses, which a 2-aligned struct would not give. Wider fields are
// read through the PAD_* accessors below.
typedef struct
{
    uint8 status;        // 0x00 0xFF = no controller
    uint8 id;            // 0x01 high nibble = controller type
    uint8 raw[2];        // 0x02 buttons, active low
    uint8 analog[4];     // 0x04
    uint8 unk08[0x1C];   // 0x08
    uint8 type;          // 0x24 0xFF = no controller
    PAD_FLAGS flags;     // 0x25
    uint8 now[2];        // 0x26 buttons held this frame
    uint8 old[2];        // 0x28 buttons held last frame
    uint8 on[2];         // 0x2A buttons pressed this frame
    uint8 off[2];        // 0x2C buttons released this frame
    uint8 unk2E[2];      // 0x2E
    uint8 analog_cpy[4]; // 0x30
    uint8 unk34[2];      // 0x34 InitPAD's caller stores 0x4001 here with one word store
    uint8 unk36;         // 0x36
    uint8 unk37;         // 0x37
} PAD_WORK;              // 0x38 (each controller's block is 0x158 apart)

#define PAD_RAW(p) (*(uint16 *)(p).raw)
#define PAD_NOW(p) (*(uint16 *)(p).now)
#define PAD_OLD(p) (*(uint16 *)(p).old)
#define PAD_ON(p)  (*(uint16 *)(p).on)
#define PAD_OFF(p) (*(uint16 *)(p).off)

// ROCK_NEO only: the per-controller block goes past PAD_WORK, with auto-repeat state per button.
typedef struct
{
    PAD_WORK pad;
    uint8 rep_state[8]; // 0x38 0 idle, 1 first press, 2 repeating
    uint8 rep_count[8]; // 0x40 frames held
} PAD_REP;

#define PAD_REP_OUT(p) (*(uint16 *)(p)->pad.unk2E) // repeat output bits

// Both programs (0x158 apart in each: shim 0x8005B570, ROCK_NEO 0x800C0C00).
extern PAD_WORK Joy1; // controller 1
extern PAD_WORK Joy2; // controller 2

void Pad_update(PAD_WORK *pad);
void Pad_update_all(void);

// Shim only.
void Disp_adjust(void);

// ROCK_NEO only.
void Pad_repeat_update(PAD_REP *pad);
void func_80012350(PAD_REP *pad, sint32 mask, sint32 i);

#endif // PAD_H
