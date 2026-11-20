#ifndef SHL03_H
#define SHL03_H

#include "common.h"
#include "shl/shl.h"

extern SHL_BOX D_800D8E18;
extern uint8 D_800D8E24[];    // sprite size by Player_work.value_50c
extern uint8 D_800D8E2C[];    // effect value by Player_work.value_50c
extern SHL_FUNC D_800D8E34[]; // routine_0 handlers

void func_800D8C6C(SHL_WORK *wp);
void func_800D8CF4(SHL_WORK *wp);
void func_800D8D5C(SHL_WORK *wp);

#endif // SHL03_H
