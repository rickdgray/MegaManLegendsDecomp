#ifndef CODE_80014AC0_H
#define CODE_80014AC0_H

#include "common.h"
#include "code_8002E7A8.h"

// Routine of the scripted WORK_3C0 object, chosen by routine_8 (func_800153EC).
typedef void (*SCRIPT_OBJ_FUNC)(WORK_3C0 *wp, SCRIPT_WORK *sp);

// func_80014AC0, func_800150E0 (runs the script), func_800153CC (frees the slot).
extern SCRIPT_OBJ_FUNC D_80082104[];

// Command scripts of the WORK_3C0 objects: [field_C][field_3] (func_80014AC0); 0: none.
extern sint16 **D_800820E0[];

// Collision box of the scripted WORK_3C0 objects (func_80014AC0).
extern HIT_ENT D_800979FC;

#endif
