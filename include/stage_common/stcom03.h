#ifndef STCOM03_H
#define STCOM03_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The 0x48-byte work slot stcom03 runs on (freed through ROCK_NEO's func_80031988): a screen
// effect drawn as a semi-transparent primitive whose color word (GPU code and RGB) fades.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[2];    // 01
    uint8 type_3;           // 03: which effect (stcom03_func_003C)
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B: also a countdown (stcom03_func_02CC)
    sint8 param_C;          // 0C
    uint8 reserved0D[7];    // 0D
    uint32 mode_14;         // 14: draw mode word
    uint32 color_18;        // 18: GPU code and RGB
    uint8 reserved1C[6];    // 1C
    uint8 value_22;         // 22
    uint8 value_23;         // 23
    sint16 size_24;         // 24
    uint16 step_26;         // 26: added to color_18 each frame
    uint8 reserved28[0x20]; // 28
} STCOM03_WORK;

typedef void (*STCOM03_FUNC)(STCOM03_WORK *wp);

extern STCOM03_FUNC stcom03_D_0000[]; // routine_0 handlers (stcom03_func_0000)

// ROCK_NEO.EXE: frees a 0x48-byte work slot.
void func_80031988(STCOM03_WORK *wp);

#endif // STCOM03_H
