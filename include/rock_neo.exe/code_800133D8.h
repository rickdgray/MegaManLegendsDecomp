#ifndef CODE_800133D8_H
#define CODE_800133D8_H

#include "common.h"

// The module's state, 0x10 bytes (pool variable D_80098AA8). func_80013420 runs
// D_80080950[routine_0] on it; func_800133D8 clears its first three words.
typedef struct
{
    sint8 routine_0; // 0x0: lb; index of D_80080950
    uint8 routine_1; // 0x1
    uint8 pad2[0xE];
} CODE_800133D8_WORK;

extern CODE_800133D8_WORK D_80098AA8; // 0x80098AA8

void func_80013F60(CODE_800133D8_WORK *wp);

#endif
