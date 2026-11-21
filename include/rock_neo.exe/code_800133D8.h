#ifndef CODE_800133D8_H
#define CODE_800133D8_H

#include "common.h"

// The module's state, 0x10 bytes (pool variable D_80098AA8). func_80013420 runs
// D_80080950[routine_0] on it; func_800133D8 clears its first three words.
typedef struct
{
    sint8 routine_0; // 0x0: lb; index of D_80080950
    uint8 routine_1; // 0x1
    uint8 routine_2; // 0x2
    uint8 routine_3; // 0x3: func_80013578 toggles it 0/1 to pick the area it starts (Game_work.stage_no 1 or 7)
    uint8 pad4[2];
    sint16 timer_6;   // 0x6: func_80015428 counts it down before closing the objects
    sint16 field_8;   // 0x8: func_80015428 cycles it 0..8, passed to each object's field_C
    sint16 routine_A; // 0xA: func_80015428's state
    uint8 padC[4];
} CODE_800133D8_WORK;

extern CODE_800133D8_WORK D_80098AA8; // 0x80098AA8

void func_80013420(void); // thread entry: runs D_80080950[D_80098AA8.routine_0]

#endif
