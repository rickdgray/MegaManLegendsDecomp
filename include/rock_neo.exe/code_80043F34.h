#ifndef CODE_80043F34_H
#define CODE_80043F34_H

// code_80043F34.c's subsystem (not identified yet; rename with the file). Its objects are the
// WORK_48 pool slots of code_8002E7A8.h.

#include "common.h"
#include "code_8002E7A8.h"

// Start values of a WORK_48 for func_80045274, indexed by flag_3 (bits 0-3)
typedef struct
{
    uint32 field_14;
    uint32 field_18;
    uint8 field_22;
    uint8 field_23;
    uint8 field_24; // used when flag_3 < 0x10; otherwise field_24 is 0x40
    uint8 routine_8;
} INIT_48;

extern WORK48_FUNC D_8008A208[]; // routine_8 dispatch table of func_80043F34
extern WORK48_FUNC D_8008A220[]; // routine_8 dispatch table of func_8004495C
extern WORK48_FUNC D_8008A250[]; // routine_8 dispatch table of func_80044AB0
extern WORK48_FUNC D_8008A258[]; // routine_8 dispatch table of func_80044C58
extern WORK48_FUNC D_8008A288[]; // routine_8 dispatch table of func_80045074
extern WORK48_FUNC D_8008A290[]; // routine_8 dispatch table of func_80045238
extern WORK48_FUNC D_8008A358[]; // routine_8 dispatch table of func_8004569C

// Two halfwords per entry, indexed by routine_8 - 5; func_80045650 stores them as bytes into
// u_18.s.field_22 and field_23 (splat labels the second halfword D_80097E0A)
extern uint16 D_80097E08[][2];

// Per-step tables of func_80044BA0, indexed by field_A (1..5): two bytes for u_18.s.field_22/23
// (splat labels the second byte D_8008A235) and the step's duration
extern uint8 D_8008A234[][2];
extern uint8 D_8008A240[];
extern uint8 D_8008A248[]; // u_18.s.field_24 of func_80044BA0, indexed by field_9 (frame count)

// The same per-step tables for func_800450B0/func_80045170: bytes for u_18.s.field_22/23
// (splat labels the second byte D_8008A26D), durations, and a scale for field_24 (times
// field_C.rec.b0, >> 4) indexed by field_9
extern uint8 D_8008A26C[][2];
extern uint8 D_8008A278[];
extern uint8 D_8008A280[];

extern INIT_48 D_80097DF0[]; // 2 entries; func_80045274

#endif
