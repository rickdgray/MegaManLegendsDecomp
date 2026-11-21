#ifndef CODE_8006430C_H
#define CODE_8006430C_H

#include "common.h"
#include "code_800456D8.h"

// State of this file's module: the global D_80098910, a pool common owned by this file
// (func_800665E8 reaches offset 0 through $gp; maspsx keeps a common with an offset lui-based).
// func_800665FC copies the pad into it, sets mode_2 from its argument and runs
// D_8008FD10[routine_0] on it; routines 1 and 2 (func_800666D8, func_80066714, the same code) both
// run D_8008FD20[routine_1]. Also read by game (func_80016BF4: no soft reset while active_0 is set)
// and moji (func_8005BC90: mode_2). Size at least 0xC; the pool's next label is at 0x80098924.
typedef struct
{
    uint16 active_0;  // 0x0: set to 1 by func_80066664 (routine 0), cleared by func_80066750 (routine 3)
    uint16 mode_2;    // 0x2: func_800665FC's argument; 0 selects routine 2, else routine 1
    sint8 routine_0;  // 0x4: lb; index of D_8008FD10
    sint8 routine_1;  // 0x5: lb; index of D_8008FD20
    uint16 unk_6;     // 0x6: cleared (sh) by func_80066664; func_80066750 clears 0x4-0x7 with one sw
    uint16 pad_now_8; // 0x8: copy of PAD_NOW(Joy1), taken by func_800665FC
    uint16 pad_on_A;  // 0xA: copy of PAD_ON(Joy1), taken by func_800665FC
} CODE_8006430C_WORK;

typedef void (*CODE_8006430C_FUNC)(CODE_8006430C_WORK *wp);
// routine_0 handlers (D_8008FD10); func_800665FC returns their result.
typedef sint32 (*CODE_8006430C_ROUTINE_FUNC)(CODE_8006430C_WORK *wp);

extern CODE_8006430C_WORK D_80098910;           // the module's state
extern CODE_8006430C_ROUTINE_FUNC D_8008FD10[]; // routine_0 handlers
extern CODE_8006430C_FUNC D_8008FD20[];         // routine_1 steps of routines 1 and 2

// The four SPEC_ENT tables (code_800456D8.h's D_80098844, D_8009884C, D_80098928, D_8009892C)
// func_8006471C selects: one set when Game_work.unk05B is 2, the other otherwise.
extern SPEC_ENT *D_8008EDC4[];
extern SPEC_ENT *D_8008EF64[];
extern SPEC_ENT *D_8008EFC4[];
extern SPEC_ENT *D_8008F048[];
extern SPEC_ENT *D_8008F060[];
extern SPEC_ENT *D_8008F200[];
extern SPEC_ENT *D_8008F260[];
extern SPEC_ENT *D_8008F2E4[];

// Set by func_80067E18 (0x3F00, 0x18, 0x80, 0).
extern sint32 D_800BE428;
extern sint32 D_800BE42C;
extern sint32 D_800BE430;
extern sint32 D_800BE434;

// func_80067D10 fills entries 0, 2, 3, 5, 6, 8 and 9 of D_8008FA84 from D_80098124, indexed by
// D_80098A04 + 1 and by the bytes D_80098800-D_80098805.
extern uint16 D_8008FA84[];
extern uint16 D_80098124[];
extern uint8 D_80098800;
extern uint8 D_80098801;
extern uint8 D_80098802;
extern uint8 D_80098803;
extern uint8 D_80098804;
extern uint8 D_80098805;

void func_8006479C(void); // opens events (OpenEvent) inside a critical section; called at init
void func_800665E8(void); // clears active_0 and the word at 0x4

#endif
