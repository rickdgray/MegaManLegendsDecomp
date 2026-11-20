#ifndef SHL0A_H
#define SHL0A_H

#include "common.h"
#include "shl/shl.h"

// Sprite scales, cycled by timer_b.
typedef struct
{
    uint8 scale_96;
    uint8 scale_97;
} SHL0A_SCALE;

extern SHL_BOX D_800D8F04;
extern uint16 D_800D8F10[]; // sprite size by Player_work.value_544
extern uint32 D_800D8F20[]; // sprite code by Player_work.value_544
extern SHL0A_SCALE D_800D8F40[8];
extern SHL_FUNC D_800D8F50[]; // routine_0 handlers

void func_800D8BE8(SHL_WORK *wp);
void func_800D8E48(SHL_WORK *wp);

#endif // SHL0A_H
