#ifndef SHL06_H
#define SHL06_H

#include "common.h"
#include "shl/shl.h"

// Sprite scales, cycled by routine_1.
typedef struct
{
    sint32 scale_96;
    sint32 scale_97;
} SHL06_SCALE;

extern SHL_BOX D_800D9090;
extern SHL06_SCALE D_800D909C[6];
extern SHL_FUNC D_800D90CC[]; // routine_0 handlers

void func_800D8C2C(SHL_WORK *wp);
void func_800D8CB8(SHL_WORK *wp, MATRIX *m);
void func_800D8D28(SHL_WORK *wp);
void func_800D8DD8(SHL_WORK *wp, SHL_WORK *np);
void func_800D8E44(SHL_WORK *wp, sint32 rx, sint32 ry);

#endif // SHL06_H
