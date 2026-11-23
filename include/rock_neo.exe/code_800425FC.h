#ifndef CODE_800425FC_H
#define CODE_800425FC_H

#include "common.h"
#include "player.h"

// 12-byte record indexed by PL_WORK.weapon_right_no or unk171. key_0-key_2 are keyframe numbers, compared
// with PL_WORK.cmd_100.b.b0 or passed to func_800320B8/func_800321C8 as the keyframe index.
// Byte 7 is read by code_8002E7A8 as D_80089A8B.
typedef struct
{
    uint8 key_0; // also: func_80040FA8 answers 1 once cmd_100.b.b0 is past it
    uint8 key_1;
    uint8 key_2;
    uint8 flag_3;  // nonzero: func_80042770 adds func_80037664's value to key_1
    uint8 flag_4;  // zero: func_80041044 answers 1 when the record's button is pressed
    uint8 flag_5;  // zero: func_800410D4 answers 1 for the record in use
    uint8 flag_6;  // zero: func_80041158 answers 1 for the record in use
    uint8 id_7;    // id_2 of the object pl_shot_spawn spawns
    uint8 shift_8; // weapon_gauge_draw draws the energy gauge one pixel per 1 << shift_8 units
    uint8 unk9[3];
} PL_ACT_ENT;

extern PL_ACT_ENT D_80089A84[];
extern uint16 D_8008A04C[2][16]; // two rows of pad-bit masks for PL_WORK.keys_124
extern PL_FUNC D_8008A08C[];     // 14 handlers, indexed by PL_WORK.weapon_right_no
extern PL_FUNC D_8008A0C4[];     // 2 handlers, indexed by PL_WORK.unk171

void func_800425FC(PL_WORK *pl, sint32 row);
void func_800426F8(PL_WORK *pl);
void func_80042734(PL_WORK *pl);
void func_80042770(PL_WORK *pl);
void func_80042A40(PL_WORK *pl);
void func_80042B58(PL_WORK *pl);
void func_80042DF8(PL_WORK *pl);
void func_80042F78(PL_WORK *pl);

#endif // CODE_800425FC_H
