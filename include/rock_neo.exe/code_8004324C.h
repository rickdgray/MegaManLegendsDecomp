#ifndef CODE_8004324C_H
#define CODE_8004324C_H

// code_8004324C.c (not identified yet; rename with the file).

#include "common.h"
#include "code_8002E7A8.h"
#include "player.h"

typedef void (*SHL_FUNC)(SHL_WORK *wp);

extern SHL_FUNC D_8008A0CC[]; // routine_8 dispatch table of func_800433C0
extern SHL_FUNC D_8008A0D8[]; // routine_8 dispatch table of func_800437A8: func_800437F8, func_80043A8C

// Tables of the shot launched by func_800437F8; the uint8/uint32 tables are indexed by
// Player_work[0].rec[1].idx[0] or idx[2].
extern HIT_ENT D_80097DA0;   // collision box (hit_78): -16..16 on each axis
extern uint32 D_80097DAC[8]; // field_88, by idx[0]
extern uint8 D_80097DCC[8];  // field_98, by idx[0]
extern uint8 D_80097DD4[8];  // speed (spd = dir * n >> 4), by idx[2]

sint32 func_8004324C(PL_WORK *pl);
sint32 Money_check(sint32 amount); // -1 when Game_work.money can't cover the (negative) amount, else 0
// Returns nothing, but declared sint32: moji.c's callers only match when the call is seen as returning
// int (Capcom's file presumably called it undeclared, i.e. implicit int). See notes/rock_neo.md.
sint32 Money_add(sint32 amount, sint32 b, sint32 c);
void func_80043340(sint32 amount, sint32 n);
void func_800433C0(SHL_WORK *wp);
void func_800435BC(SHL_WORK *wp);
void func_800435F8(SHL_WORK *wp);
void func_80043740(SHL_WORK *wp);
void func_80043DF8(SHL_WORK *wp, MATRIX *m); // empty; func_800437F8 passes its rotation matrix
void func_80043E00(SHL_WORK *wp, uint8 arg);
void func_80043E78(SHL_WORK *wp);

#endif // CODE_8004324C_H
