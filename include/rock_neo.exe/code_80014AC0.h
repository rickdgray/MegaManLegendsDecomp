#ifndef CODE_80014AC0_H
#define CODE_80014AC0_H

#include "common.h"
#include "code_8002E7A8.h"
#include "code_800133D8.h"

// Routine of the scripted WORK_3C0 object, chosen by routine_0 (func_800153EC).
typedef void (*SCRIPT_OBJ_FUNC)(WORK_3C0 *wp, SCRIPT_WORK *sp);

// func_80014AC0, func_800150E0 (runs the script), func_800153CC (frees the slot).
extern SCRIPT_OBJ_FUNC D_80082104[];

// Command scripts of the WORK_3C0 objects: [field_C][type] (func_80014AC0); 0: none.
extern sint16 **D_800820E0[];

// Collision box of the scripted WORK_3C0 objects (func_80014AC0).
extern HIT_ENT D_800979FC;

// The routines in D_80082104 (and func_800153EC, the slot's per-frame call) are reached through
// data tables, func_80015428 from code_800133D8.
void func_80014AC0(WORK_3C0 *wp, SCRIPT_WORK *sp);
void func_800150E0(WORK_3C0 *wp, SCRIPT_WORK *sp);
void func_800153CC(WORK_3C0 *wp, SCRIPT_WORK *sp);
void func_800153EC(WORK_3C0 *wp);
void func_80015428(CODE_800133D8_WORK *wp);

#endif
