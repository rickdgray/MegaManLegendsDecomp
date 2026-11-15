#ifndef CODE_8006430C_H
#define CODE_8006430C_H

#include "common.h"

// State of this file's module (D_80098910, a pool variable): func_800665FC sets mode_2 from its
// argument and runs D_8008FD10[routine_0]; routines 1 and 2 (func_800666D8, func_80066714, the same
// code) both run D_8008FD20[routine_1]. Size not known.
typedef struct
{
    uint16 unk_0;    // 0x0: set to 1 by func_80066664, cleared by func_80066750
    uint16 mode_2;   // 0x2: func_800665FC's argument; 0 selects routine 2, else routine 1
    sint8 routine_0; // 0x4: lb; index of D_8008FD10
    sint8 routine_1; // 0x5: lb; index of D_8008FD20
} CODE8006430C_WORK;

typedef void (*CODE8006430C_FUNC)(CODE8006430C_WORK *wp);

extern CODE8006430C_FUNC D_8008FD20[]; // routine_1 steps of routines 1 and 2

#endif
