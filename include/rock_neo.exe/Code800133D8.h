#ifndef CODE800133D8_H
#define CODE800133D8_H

#include "common.h"

// The module's state, 0x10 bytes (pool variable Code800133D8_work). func_80013420 runs
// Code800133D8_main_tbl[routine_0] on it; func_800133D8 clears its first three words.
typedef struct
{
    sint8 routine_0; // 0x0: lb; index of Code800133D8_main_tbl
    uint8 routine_1; // 0x1
    uint8 pad2[0xE];
} CODE800133D8_WORK;

extern CODE800133D8_WORK Code800133D8_work; // 0x80098AA8

void func_80013F60(CODE800133D8_WORK *wp);

#endif
