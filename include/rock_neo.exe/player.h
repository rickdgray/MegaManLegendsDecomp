#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

// Row of four signed shorts, 8 bytes each; D_80089EAC[n] points to an array of these.
typedef struct
{
    sint16 val[4];
} TBL_ROW;

// Record at PL_WORK 0x4F4, 8 bytes each (four index bytes used): rec[n].idx[k] selects
// D_80089EAC[n][idx[k]].val[k].
typedef struct
{
    sint8 idx[4];
    uint8 unk04[2];
    uint16 val; // 0x06: copy of D_80089EAC[n][idx[1]].val[1]
} TBL_IDX;

// Player work, 0x5F4 bytes.
typedef struct
{
    uint8 unk00[0x14];
    sint16 unk14; // 0x14: lh; position, one horizontal axis (sound distance check)
    uint8 unk16[2];
    sint16 unk18; // 0x18: lh; position, the other horizontal axis
    uint8 unk1A[0x56 - 0x1A];
    sint16 unk56; // 0x56: lh; facing angle (0..0xFFF), used by calc_vol
    uint8 unk58[0x6E - 0x58];
    uint16 unk6E; // 0x6E: sh; copy of unkB0 (func_8005D9EC)
    uint8 unk70[0xB0 - 0x70];
    uint16 unkB0; // 0xB0: lhu
    uint8 unkB2[0x172 - 0xB2];
    sint8 tbl_sel; // 0x172: lb; index of the active TBL_IDX record
    uint8 unk173[0x44D - 0x173];
    uint8 unk44D; // 0x44D: sb; cleared by func_80039DE8
    uint8 unk44E[0x4F4 - 0x44E];
    TBL_IDX rec[16]; // 0x4F4
    uint8 unk574[0x5F4 - 0x574];
} PL_WORK;

extern TBL_ROW *D_80089EAC[];  // 16 tables, one per Player_work.rec[n]
extern PL_WORK Player_work;    // 0x800B51B0
extern PL_WORK *p_Player_work; // 0x80098A50

#endif // PLAYER_H
