#ifndef CODE_80048620_H
#define CODE_80048620_H

// code_80048620.c (not identified yet; rename with the file): the stage collision services. They
// take any model object (MODEL_WORK) and its collision box (HIT_ENT), both in code_8002E7A8.h.

#include "common.h"
#include "psyq/libgte.h"
#include "code_8002E7A8.h"

sint32 func_80049C24(MODEL_WORK *obj); // the IDX entry obj touches, or 0
void func_8004B414(MODEL_WORK *obj);
sint32 func_8004920C(SVECTOR *v);
// Moves pos along the ground; returns the height of the surface below it.
sint32 func_80048EA4(SVECTOR *pos, HIT_ENT *ent, sint32 angle, uint32 mask);
// Collides the move old -> pos against ent; returns hit flags (0x1000 = floor).
sint32 func_8004B5CC(SVECTOR *pos, SVECTOR *old, sint32 n, HIT_ENT *ent);
void func_8004AC8C(void *vel, sint32 hit);
// If obj's routine_0 has bit 0 or 1 set, pushes obj on the list at D_80098898; clears +0x7C.
// Called with player objects, SHL_WORK shots and the stage overlays' objects.
void func_80051BAC(MODEL_WORK *obj);

#endif // CODE_80048620_H
