#ifndef STCOM26_H
#define STCOM26_H

#include "common.h"
#include "stage_common/rock_neo.h"
#include "stage_common/stcom25.h"

// The 0x50-byte work slot (freed through func_80031A4C) that spawns a room's rolling blocks
// (stcom25) and keeps them from running into each other.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 index_1;         // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03: the room's set of blocks (0xFF: none)
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 reserved09[0xB]; // 09
    union
    {
        uint8 bytes[0x10];
        uint32 words[4];
    } slot_14;              // 14: the blocks' slot numbers in D_8009CF88
    uint8 reserved24[0x2C]; // 24
} STCOM26_WORK;

typedef void (*STCOM26_FUNC)(STCOM26_WORK *wp);

extern sint16 stcom26_D_0000[][4];         // by variant_3: [0] the number of blocks
extern STCOM26_FUNC stcom26_D_0058[];      // routine_0 (stcom26_func_0000)
extern STCOM25_WORK *stcom26_E_0000[0x10]; // the blocks
extern uint8 stcom26_E_0040[0x10];         // the blocks' slot numbers, unpacked each frame

void stcom26_func_0344(STCOM26_WORK *wp);
void stcom26_func_03F4(STCOM26_WORK *wp);
void stcom26_func_06DC(STCOM25_WORK *a, STCOM25_WORK *b);
sint16 stcom26_func_0918(STCOM25_WORK *a, STCOM25_WORK *b);
sint16 stcom26_func_0B50(uint16 *cell, sint16 dir, sint32 n, sint32 range);
void stcom26_func_0CE8(STCOM26_WORK *wp);
void stcom26_func_0DAC(STCOM25_WORK *wp);

// ROCK_NEO.EXE.
// The 0x10C-byte work slots.
extern STCOM25_WORK D_8009CF88[];
// Allocates a 0x10C-byte work slot; NULL when none is free.
STCOM25_WORK *Open_SHL_WORK(void);
// Frees a 0x50-byte work slot.
void func_80031A4C(STCOM26_WORK *wp);

#endif // STCOM26_H
