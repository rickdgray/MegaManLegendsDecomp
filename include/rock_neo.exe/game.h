#ifndef GAME_H
#define GAME_H

#include "common.h"

// One loaded sound bank (VAB) per slot, filled by cd_cmd_read_comb's VAB entries.
typedef struct
{
    sint16 vab_id; // 0x0: SsVabOpenHeadSticky's result, -1 when no bank is open
    uint8 num;     // 0x2: bank number from the comb header
    uint8 pad3;
    uint32 sbaddr; // 0x4: SPU address
} GAME_VAB;

// Global game state, 0x210 bytes. Only the fields decompiled code uses are named.
typedef struct
{
    uint8 unk000[0x50];
    sint8 unk050; // 0x50: lb; indexes Sound_stage_func_tbl in func_80019FB4
    sint8 unk051; // 0x51: lb; indexes the list at Sound_stage_id_tbl[unk050] in func_80019D18
    uint8 unk052;
    sint8 unk053; // 0x53: lb; 1 selects a different value in func_8001997C
    uint8 unk054[4];
    sint8 unk058; // 0x58: lb; nonzero makes calc_vol use the louder channel for both
    uint8 unk059[0x1B8 - 0x59];
    GAME_VAB vab[5];   // 0x1B8 (at least 5: cd_cmd_read_comb reads vab[4].num)
    sint16 unk1E0[24]; // 0x1E0: per-SPU-voice distance to the player, stored by voice_check
} GAME_WORK;

extern GAME_WORK Game_work; // 0x800C1B10

sint32 Sce_flag_test(sint32 flag);

#endif // GAME_H
