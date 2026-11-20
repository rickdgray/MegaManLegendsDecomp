#ifndef STCOM35_H
#define STCOM35_H

#include "common.h"
#include "stage_common/rock_neo.h"

typedef void (*STCOM35_FUNC)(STCOM_EFFECT *wp);

extern STCOM35_FUNC stcom35_D_0000[]; // a puff's routine_0 handlers (stcom35_func_0000)
extern STCOM35_FUNC stcom35_D_0008[]; // the emitter's, by variant_3
extern uint32 stcom35_D_0010[];       // color steps by timer_E

// ROCK_NEO.EXE.
void func_80031988(STCOM_EFFECT *wp);

#endif // STCOM35_H
