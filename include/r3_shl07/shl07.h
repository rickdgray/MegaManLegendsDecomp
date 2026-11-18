#ifndef SHL07_H
#define SHL07_H

#include "common.h"
#include "shl/shl.h"

extern SHL_BOX D_8008A310[]; // indexed by an effect's index_a
extern uint8 D_80089ADA;

extern SHL_FUNC D_800D8C28[]; // routine_0 handlers
extern sint16 D_800D8C30[];   // push strength by Player_work.value_530

void func_8004B5CC(SVECTOR *pos, SVECTOR *old, sint32 arg, SHL_BOX *box);

#endif // SHL07_H
