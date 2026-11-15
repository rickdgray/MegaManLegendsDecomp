#ifndef CODE_80037FB4_H
#define CODE_80037FB4_H

// code_80037FB4.c's subsystem (not identified yet; it contains Swing_Camera2, so possibly the
// camera; rename with the file).

#include "common.h"
#include "psyq/libgte.h"

// Globals at 0x800A395A.. (struct layout still unknown)
extern uint8 D_800A395A;
extern uint8 D_800A395B;
extern uint8 D_800A395C; // set to 3 by func_8001E6C0
extern uint8 D_800A395F;
extern uint8 D_800A3960;
extern sint8 D_800A3962;
extern sint32 D_800A396C;
extern uint8 D_800A3959;
extern sint32 D_800A3964;
extern sint32 D_800A39B4;
extern VECTOR D_800A39A0;
extern VECTOR D_800A39B0;
extern VECTOR D_800A39C0;
extern VECTOR D_800A39D0;
extern VECTOR D_800A39E0;
extern sint32 D_800A3968;
extern sint32 D_800A3970;
extern sint32 D_800A3974;
extern sint32 D_800A3978;
extern sint32 D_800A397C;
extern sint32 D_800A3980;
extern sint32 D_800A3984;
extern sint32 D_800A3988;
extern sint32 D_800A398C;
extern sint32 D_800A3990;
extern sint32 D_800A3994;
extern sint32 D_800A3998;
extern sint32 D_800A399C;
extern uint32 D_8009869C[8];

void func_80037FB4(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80038370(VECTOR *arg0, VECTOR *arg1); // arg1: point to look at (func_8001E550)
void func_80038324(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_800384A4(VECTOR *arg0, VECTOR *arg1);
void func_80039BBC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039C08(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039C54(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039CA0(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039CEC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3);
sint32 func_8003A218(sint32 arg0);
void func_80039E50(void);
// Returns nothing; declared sint32 for the same reason as Money_add (func_80055C1C needs it).
sint32 func_80039E18(void);
void func_800398E0(sint32 arg0);
void Swing_Camera2(sint32 arg0, sint32 arg1, sint32 arg2, SVECTOR *pos);
sint32 func_800399EC(sint32 arg0);
void func_80039A38(sint32 arg0); // callers pass an address; forwarded to func_800399EC

#endif // CODE_80037FB4_H
