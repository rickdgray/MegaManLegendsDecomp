#ifndef GAME_H
#define GAME_H

#include "common.h"

#define MONEY_MAX 999999 // Game_work.money's cap

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
    sint8 routine_0; // 0x00: lb; index of Game_main_tbl (func_800155A4)
    uint8 routine_1; // 0x01
    uint8 unk002[0x0C - 0x02];
    uint32 timer_0c; // 0x0C: frame counter; the logo sprites (func_800640F0) blink on (timer_0c / 15) % 60
    uint32 unk010;   // 0x10: cleared by func_8001326C
    uint32 unk014;   // 0x14: cleared by func_8001326C
    uint16 unk018;   // 0x18: lhu; cleared by func_8001326C; nonzero adds a fourth entry to func_8001456C's menu
    sint16 unk01A;   // 0x1A: cleared by func_8001326C
    uint32 money;    // 0x1C: zenny, capped at MONEY_MAX (Money_add)
    uint32 unk020;   // 0x20: Money_add adds the amount of a payment here (c == 0) ...
    uint32 unk024;   // 0x24: ... or here (c != 0)
    // 0x28: words that func_80059D20 subtracts from D_8008AF00's entries ([n] for n < 4, else
    // [9 - n]); count not confirmed (9 fills the gap)
    uint32 unk028[9];
    uint32 unk04C; // 0x4C: func_80043340 adds the amount when player 0's unk6E is lowered
    // 0x50-0x52: Capcom's names (sub_scrn.c's Map_screen_init and map_cursor_set)
    sint8 stage_no; // 0x50: lb; indexes Sound_stage_func_tbl in func_80019FB4
    sint8 area_no;  // 0x51: lb; indexes the list at Sound_stage_id_tbl[stage_no] in Sound_stage_play
    sint8 sce_no;   // 0x52: lb; scenario; picks the ids func_8001FB24, func_8001FB54, func_8001FB8C, func_8001FCA4 set
    sint8 unk053;   // 0x53: lb; 1 selects a different value in func_8001997C
    uint8 unk054;   // 0x54: cleared by func_8001326C
    uint8 unk055;   // 0x55: cleared by func_8001326C
    uint8 unk056[2];
    sint8 mono; // 0x58: mono sound output (volume_update: SsSetMono, CD mixed to both sides; calc_vol)
    uint8 unk059;
    sint8 unk05A; // 0x5A: lb; when nonzero, func_8001DE84 skips its scene-flag test
    sint8 unk05B; // 0x5B: lb; row of D_8008A678/D_8008A680 (func_80046A0C); 0-2 picks the
                  // fourth menu entry's image in func_8001456C
    uint8 unk05C[0x60 - 0x5C];
    sint16 unk060;             // 0x60: lh; func_8005A598 picks a message by whether it lies in a byte range
    uint8 unk062[0x68 - 0x62]; // 0x62: func_80059D20 multiplies [9 - n] (n = 4, 5) by D_8008AF00[n]
    sint16 unk068;             // 0x68: lh; compared with entry 0 of the stage's D_800893BC list (func_8001F6C4)
    sint16 unk06A;             // 0x6A: lh; compared with the list's entry D_800C356F + 1 (func_8001F6C4)
    uint8 unk06C[0x70 - 0x6C];
    // 0x70-0x74: files last loaded by func_8001F5E4 (Cd_read_comb), one per player setting:
    // D_80089200[Player_work[0].unk16A], D_80089204[unk16B >> 1], D_80089208[tbl_sel]
    sint16 file_070;
    sint16 file_072;
    sint16 file_074;
    sint16 unk076; // 0x76: set to -1 with file_070-074 by func_8001326C
    uint8 unk078[0x7C - 0x78];
    uint8 unk07C; // 0x7C: func_80057924 sets it to unk07D after charging 10 zenny per unit of
                  // the difference (or all the money)
    uint8 unk07D; // 0x7D
    uint8 unk07E[0x82 - 0x7E];
    sint8 unk082; // 0x82: func_80013578 sets -0x80 (signed: the target loads it with li -0x80)
    uint8 unk083; // 0x83: lbu; 1 changes the speed func_80042A40/func_80042DF8 set

    uint16 unk084[19][8]; // 0x84: rows of 8 halfwords, row from D_800989D4; func_80057DF4 copies the
                          // low bytes of [2..4]. Row count not confirmed (19 fits before 0x1B8).
    uint8 unk1B4[0x1B8 - 0x1B4];
    GAME_VAB vab[5];   // 0x1B8 (at least 5: cd_cmd_read_comb reads vab[4].num)
    sint16 unk1E0[24]; // 0x1E0: per-SPU-voice distance to the player, stored by voice_check
} GAME_WORK;

extern GAME_WORK Game_work; // 0x800C1B10
// Pool sint16 (lh) read by code_800133D8, game, code_80014AC0, code_8001786C: while nonzero,
// func_80013F60 and func_80016D0C/D38 hold their routine_1 step. Owner unknown: only
// code_8001786C stores to it (func_80017C30, func_800182D4, func_8001840C), but nothing reaches
// it through $gp, so no file is confirmed.
extern sint16 D_80098A72;

void func_800155A4(void); // thread entry: runs Game_main_tbl[Game_work.routine_0]

#endif // GAME_H
