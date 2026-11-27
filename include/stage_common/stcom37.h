#ifndef STCOM37_H
#define STCOM37_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A 0x3C0-byte work slot (freed through ROCK_NEO's func_80031824): only the fields used here.
typedef struct
{
    uint8 be_flag;          // 00
    uint8 slot;             // 01
    uint8 reserved02[6];    // 02
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 reserved0B[0x9C]; // 0B
    sint8 flags_A7;         // A7: sign bit set at the end of an animation
    uint8 reservedA8[4];    // A8
    uint8 anim_AC;          // AC
} STCOM37_WORK;

#endif // STCOM37_H
