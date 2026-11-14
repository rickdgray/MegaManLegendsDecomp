#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "psyq/libgte.h"
#include "code_8002E7A8.h"

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
    SVECTOR pos;   // 0x14: position (vx and vz are the horizontal axes, vy the height)
    VECTOR pos_1C; // 0x1C: 16.16 fixed-point position; pos is its rounded copy (func_8002FEA4)
    uint8 unk2C[0x56 - 0x2C];
    sint16 unk56; // 0x56: lh; facing angle (0..0xFFF), used by calc_vol
    uint8 unk58[0x6E - 0x58];
    uint16 unk6E; // 0x6E: sh; copy of unkB0 (func_8005D9EC)
    uint8 unk70[0xB0 - 0x70];
    uint16 unkB0; // 0xB0: lhu
    uint8 unkB2[0xF8 - 0xB2];
    KEY_ENT *tbl_F8; // 0xF8: keyframe table in use (func_800321C8)
    KEY_ENT *ent_FC; // 0xFC: current keyframe
    KEY_CMD cmd_100; // 0x100: copy of the current keyframe's command; time counts down (func_800323FC)
    uint8 set_104;   // 0x104: index of the keyframe table set in use
    uint8 unk105;    // 0x105: set_104 when func_800321C8 last ran (func_8003C418)
    sint16 unk106;   // 0x106: set by func_800323FC
    uint8 unk108[0x116 - 0x108];
    uint16 unk116; // 0x116: lhu; added to unk56 for the camera yaw (func_800355F0)
    uint8 unk118[0x11C - 0x118];
    uint16 unk11C; // 0x11C: lhu; mask tested against unk128 and unk12A (func_800482A8)
    uint8 unk11E[0x128 - 0x11E];
    uint16 unk128; // 0x128: lhu
    uint16 unk12A; // 0x12A: lhu
    uint8 unk12C[0x170 - 0x12C];
    sint8 unk170;  // 0x170: lb; selects the TBL_IDX record counted by func_80037440; nonzero also
                   // selects the alternate keyframe tables for sets 0x40-0x5F (func_800321C8)
    sint8 unk171;  // 0x171: lb; record index for the alternative position (func_80035724); nonzero
                   // selects the alternate keyframe tables for sets 0x60-0x7F
    sint8 tbl_sel; // 0x172: lb; index of the active TBL_IDX record
    uint8 unk173[0x188 - 0x173];
    SLOT_OWNER owner_188; // 0x188: slot owner passed to func_800341BC (func_8003C2D8)
    uint8 unk190[0x1A8 - 0x190];
    MATRIX base_mtx;       // 0x1A8: body matrix, copied from the scratchpad matrix (func_800325D4)
    MATRIX joint_mtx[15];  // 0x1C8: joint matrices (func_800331A0)
    SVECTOR joint_pos[15]; // 0x3A8: joint positions (func_800331A0); [4] and [7] are copied to the
                           // objects func_80035724 spawns, [11] and [14] by func_80047EC8
    uint8 unk420[0x428 - 0x420];
    VECTOR pos_428;   // 0x428: 16.16 position, moved like pos_1C (func_8002FF34)
    SVECTOR svec_438; // 0x438: rounded copy of pos_428
    uint8 unk440[0x44D - 0x440];
    uint8 unk44D; // 0x44D: sb; cleared by func_80039DE8
    uint8 unk44E[0x4F4 - 0x44E];
    TBL_IDX rec[16]; // 0x4F4
    uint8 unk574[0x5F4 - 0x574];
} PL_WORK;

extern TBL_ROW *D_80089EAC[];  // 16 tables, one per Player_work.rec[n]
extern PL_WORK Player_work[];  // 0x800B51B0: two players, 0x5F4 apart
extern PL_WORK *p_Player_work; // 0x80098A50

#endif // PLAYER_H
