#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "psyq/libgte.h"

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
    sint16 val; // 0x06: copy of D_80089EAC[n][idx[1]].val[1]; 0x7FFF is never counted down (func_80035724)
} TBL_IDX;

// Player work, 0x5F4 bytes.
typedef struct
{
    uint8 unk00;
    uint8 unk01; // 0x01: lbu; copied to the spawned object's field_C (func_80035724)
    uint8 unk02[7];
    uint8 unk09; // 0x09: lbu; 3 while the pad-driven state of func_800482A8 applies
    uint8 unk0A[0x14 - 0x0A];
    SVECTOR pos; // 0x14: position (vx and vz are the horizontal axes, vy the height)
    uint8 unk1C[0x56 - 0x1C];
    sint16 unk56; // 0x56: lh; facing angle (0..0xFFF), used by calc_vol
    uint8 unk58[0x6E - 0x58];
    uint16 unk6E; // 0x6E: sh; copy of unkB0 (func_8005D9EC)
    uint8 unk70[0xB0 - 0x70];
    uint16 unkB0; // 0xB0: lhu
    uint8 unkB2[0x116 - 0xB2];
    uint16 unk116; // 0x116: lhu; added to unk56 for the camera yaw (func_800355F0)
    uint8 unk118[0x11C - 0x118];
    uint16 unk11C; // 0x11C: lhu; mask tested against unk128 and unk12A (func_800482A8)
    uint8 unk11E[0x128 - 0x11E];
    uint16 unk128; // 0x128: lhu
    uint16 unk12A; // 0x12A: lhu
    uint8 unk12C[0x170 - 0x12C];
    sint8 unk170;  // 0x170: lb; selects the TBL_IDX record counted by func_80037440
    sint8 unk171;  // 0x171: lb; record index for the alternative position (func_80035724)
    sint8 tbl_sel; // 0x172: lb; index of the active TBL_IDX record
    uint8 unk173[0x3C8 - 0x173];
    uint16 unk3C8[3]; // 0x3C8: three lhu, copied to the object's position (func_80035724)
    uint8 unk3CE[0x3E0 - 0x3CE];
    uint16 unk3E0[3]; // 0x3E0: three lhu, the alternative position
    uint8 unk3E6[0x400 - 0x3E6];
    uint16 unk400[3]; // 0x400: three lhu, position copied by func_80047EC8 (when the effect's flag_3 is set)
    uint8 unk406[0x418 - 0x406];
    uint16 unk418[3]; // 0x418: three lhu, position copied by func_80047EC8 (flag_3 clear)
    uint8 unk41E[0x44D - 0x41E];
    uint8 unk44D; // 0x44D: sb; cleared by func_80039DE8
    uint8 unk44E[0x4F4 - 0x44E];
    TBL_IDX rec[16]; // 0x4F4
    uint8 unk574[0x5F4 - 0x574];
} PL_WORK;

extern TBL_ROW *D_80089EAC[];  // 16 tables, one per Player_work.rec[n]
extern PL_WORK Player_work[];  // 0x800B51B0 (a second at 0x800B57A4)
extern PL_WORK Player_work2;   // 0x800B57A4, the second player (addressed as its own symbol)
extern PL_WORK *p_Player_work; // 0x80098A50

#endif // PLAYER_H
