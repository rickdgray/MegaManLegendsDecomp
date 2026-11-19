#ifndef CODE_8004324C_H
#define CODE_8004324C_H

// code_8004324C.c (not identified yet; rename with the file).

#include "common.h"
#include "code_8002E7A8.h"
#include "player.h"

typedef void (*PL_SHL_FUNC)(PL_SHL_WORK *wp);

extern PL_SHL_FUNC D_8008A0CC[]; // routine_8 dispatch table of func_800433C0
extern PL_SHL_FUNC D_8008A0D8[]; // routine_8 dispatch table of func_800437A8: func_800437F8, func_80043A8C

sint32 func_8004324C(PL_WORK *pl);
sint32 Money_check(sint32 amount); // -1 when Game_work.money can't cover the (negative) amount, else 0
// Returns nothing, but declared sint32: moji.c's callers only match when the call is seen as returning
// int (Capcom's file presumably called it undeclared, i.e. implicit int). See notes/rock_neo.md.
sint32 Money_add(sint32 amount, sint32 b, sint32 c);
void func_80043340(sint32 amount, sint32 n);
void func_800433C0(PL_SHL_WORK *wp);
void func_800435BC(PL_SHL_WORK *wp);
void func_800435F8(PL_SHL_WORK *wp);
void func_80043740(PL_SHL_WORK *wp);
void func_80043DF8(PL_SHL_WORK *wp, MATRIX *m); // empty; func_800437F8 passes its rotation matrix
void func_80043E00(PL_SHL_WORK *wp, uint8 arg);
void func_80043E78(PL_SHL_WORK *wp);

#endif // CODE_8004324C_H
