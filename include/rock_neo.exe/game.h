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
    uint8 unk000[0x1B8];
    GAME_VAB vab[5]; // 0x1B8 (at least 5: cd_cmd_read_comb reads vab[4].num)
    uint8 unk1E0[0x210 - 0x1E0];
} GAME_WORK;

extern GAME_WORK Game_work; // 0x800C1B10

#endif // GAME_H
