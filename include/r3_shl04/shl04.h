#ifndef SHL04_H
#define SHL04_H

#include "common.h"
#include "shl/shl.h"

// Model data loaded with the module (ARM01R.BIN), outside the code chunk.
typedef struct
{
    uint8 reserved00[0x20];
    SVECTOR pos_20; // 20
} SHL04_MODEL;

extern SHL04_MODEL *D_800DD600;
extern uint8 D_80089AB6;

extern SHL_FUNC D_800D8C44[]; // routine_0 handlers

void func_800D89F8(SHL_WORK *wp);
void func_800D8ADC(SHL_WORK *wp, sint32 arg);
void func_800D8AE4(SHL_PLAYER *tp, SVECTOR *rot);

#endif // SHL04_H
