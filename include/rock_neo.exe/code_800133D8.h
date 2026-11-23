#ifndef CODE_800133D8_H
#define CODE_800133D8_H

#include "common.h"
#include "code_8002E7A8.h"

// The module's state, 0x10 bytes (pool variable D_80098AA8). func_80013420 runs
// D_80080950[routine_0] on it; func_800133D8 clears its first three words.
typedef struct
{
    sint8 routine_0;  // 0x0: lb; index of D_80080950
    uint8 routine_1;  // 0x1
    uint8 routine_2;  // 0x2
    uint8 routine_3;  // 0x3: func_80013578 toggles it 0/1 to pick the area it starts (Game_work.stage_no 1 or 7)
    sint16 timer_4;   // 0x4: the menu screens set it to 900; func_800136B8 counts it down
    sint16 timer_6;   // 0x6: func_80015428 counts it down before closing the objects
    sint16 field_8;   // 0x8: func_80015428 cycles it 0..8, passed to each object's field_C
    sint16 routine_A; // 0xA: func_80015428's state
    sint8 cursor_C;   // 0xC: lb; func_8001389C's menu cursor (0-2, or 3 with the fourth entry),
                      // drawn by func_8001456C; func_80013420 clears 0xC-0xF with one word store
    uint8 field_D;    // 0xD
    sint16 field_E;   // 0xE: func_8001389C sets it to 1 on PAD_TRIANGLE
} CODE_800133D8_WORK;

typedef void (*CODE_800133D8_FUNC)(CODE_800133D8_WORK *wp);

extern CODE_800133D8_WORK D_80098AA8;   // 0x80098AA8
extern CODE_800133D8_FUNC D_80080950[]; // func_80013420's handlers, by routine_0
extern WORK3C0_FUNC *D_800808A4[];      // func_800135DC's Work_3C0_tbl: one kind, D_800808A0
extern FOG_BLOCK D_800808A8;            // func_800135DC's fog block
extern uint32 D_800808D0[0x20];         // func_800135DC's scene block (func_800371A0's src)
extern VECTOR D_800979DC;               // func_800137D4's camera position (.sdata, defined in assembly)
extern VECTOR D_800979EC;               // func_800137D4's camera target

void func_80013420(void); // thread entry: runs D_80080950[D_80098AA8.routine_0]

#endif
