#ifndef SHL0C_H
#define SHL0C_H

#include "common.h"
#include "shl/shl.h"

// An entry of ROCK_NEO.EXE's 32-slot object table D_8009CF88 (stride 0x10C).
typedef struct
{
    sint8 flag_0; // 00
    uint8 reserved01[0x13];
    SVECTOR pos; // 14
    uint8 reserved1c[0xF0];
} SHL0C_OBJ;

extern SHL0C_OBJ D_8009CF88[32];

extern SHL_BOX D_800D9080;
extern sint32 D_800D908C[];   // scale by value_f
extern sint32 D_800D90AC[];   // hit size by value_f
extern uint32 D_800D90CC[];   // aim range by value_f
extern SHL_FUNC D_800D90EC[]; // routine_0 handlers

uint8 func_800D8D28(void);
void func_800D8D74(SHL_WORK *wp);
uint8 func_800D8E8C(SHL_WORK *wp);

#endif // SHL0C_H
