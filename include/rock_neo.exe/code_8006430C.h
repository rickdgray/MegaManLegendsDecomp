#ifndef CODE_8006430C_H
#define CODE_8006430C_H

#include "common.h"

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

extern CODE_8006430C_WORK D_80098910;   // the module's state
extern CODE_8006430C_FUNC D_8008FD20[]; // routine_1 steps of routines 1 and 2

#endif
