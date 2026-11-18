#ifndef CODE_800425FC_H
#define CODE_800425FC_H

#include "common.h"
#include "player.h"
#include "game.h"
#include "code_80037534.h"

typedef void (*PL_FUNC)(PL_WORK *pl);

// 12-byte record indexed by PL_WORK.unk170 or unk171. key_0-key_2 are keyframe numbers, compared
// with PL_WORK.cmd_100.b.b0 or passed to func_800320B8/func_800321C8 as the keyframe index.
// Byte 0xB is read by code_8002E7A8 as D_80089A8B.
typedef struct
{
    uint8 key_0;
    uint8 key_1;
    uint8 key_2;
    uint8 flag_3; // nonzero: func_80042770 adds func_80037664's value to key_1
    uint8 unk4[8];
} PL_ACT_ENT;

extern PL_ACT_ENT D_80089A84[];
extern uint16 D_8008A04C[2][16]; // two rows of pad-bit masks for PL_WORK.keys_124
extern PL_FUNC D_8008A08C[];     // 14 handlers, indexed by PL_WORK.unk170
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
