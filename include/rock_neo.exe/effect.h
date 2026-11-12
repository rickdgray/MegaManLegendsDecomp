#ifndef EFFECT_H
#define EFFECT_H

#include "common.h"

// Effect work slot handed out by func_80031618 (partial).
typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    uint8 unk04[0x1C - 0x04];
    sint16 pos_1C[3]; // 0x1C: position (x, y, z), written by func_80037890's second burst
    uint8 unk22[0x38 - 0x22];
    sint16 pos_38[3]; // 0x38: position (x, y, z), written by func_80037890's first burst
} EFFECT_WORK;

EFFECT_WORK *func_80031618(void);

#endif // EFFECT_H
