#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

// Player work, 0x5F4 bytes.
typedef struct
{
    uint8 unk00[0x14];
    sint16 unk14; // 0x14: lh; position, one horizontal axis (sound distance check)
    uint8 unk16[2];
    sint16 unk18; // 0x18: lh; position, the other horizontal axis
    uint8 unk1A[0x56 - 0x1A];
    sint16 unk56; // 0x56: lh; facing angle (0..0xFFF), used by func_8001A274
    uint8 unk58[0x5F4 - 0x58];
} PL_WORK;

extern PL_WORK Player_work;    // 0x800B51B0
extern PL_WORK *p_Player_work; // 0x80098A50

#endif // PLAYER_H
