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
    // 0x14-0x5C: the MODEL_WORK layout (names from Capcom's source: Player_work[0].pos_l, .ang.vy).
    SVECTOR pos;  // 0x14: position (vx and vz are the horizontal axes, vy the height)
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position; pos is its rounded copy (Obj_pos_set)
    uint8 unk2C[0x54 - 0x2C];
    SVECTOR ang; // 0x54: rotation; ang.vy is the facing angle (0..0xFFF), used by calc_vol
    uint8 unk5C[0x6E - 0x5C];
    sint16 unk6E; // 0x6E: sh; copy of unkB0 (func_8005D9EC); func_8001DDE4 does nothing while negative
    uint8 unk70[0xB0 - 0x70];
    sint16 unkB0; // 0xB0: upper limit of unk6E (func_80043340)
    uint8 unkB2[0xF8 - 0xB2];
    KEY_ENT *tbl_F8; // 0xF8: keyframe table in use (func_800321C8)
    KEY_ENT *ent_FC; // 0xFC: current keyframe
    KEY_CMD cmd_100; // 0x100: copy of the current keyframe's command; time counts down (func_800323FC)
    uint8 set_104;   // 0x104: index of the keyframe table set in use
    uint8 unk105;    // 0x105: set_104 when func_800321C8 last ran (func_8003C418)
    sint16 unk106;   // 0x106: set by func_800323FC
    uint8 unk108[0x116 - 0x108];
    uint16 unk116; // 0x116: lhu; added to ang.vy for the camera yaw (func_800355F0)
    uint8 unk118[0x11C - 0x118];
    uint16 unk11C; // 0x11C: lhu; mask tested against unk128 and unk12A (func_800482A8)
    uint8 unk11E[0x128 - 0x11E];
    uint16 unk128; // 0x128: lhu
    uint16 unk12A; // 0x12A: lhu
    uint8 unk12C[0x16A - 0x12C];
    sint8 unk16A; // 0x16A: lb; selects the file D_80089200[unk16A] (func_8001F5E4)
    uint8 unk16B; // 0x16B: lbu; bits 1-7 (signed) select the file D_80089204[n] (func_8001F5E4)
    sint8 unk16C; // 0x16C: lb; when nonzero, Sce_flag_on sets it to the count of flags 0x53A-0x53C
    uint8 unk16D[0x170 - 0x16D];
    sint8 unk170;  // 0x170: lb; selects the TBL_IDX record counted by func_80037440; nonzero also
                   // selects the alternate keyframe tables for sets 0x40-0x5F (func_800321C8)
    sint8 unk171;  // 0x171: lb; record index for the alternative position (func_80035724); nonzero
                   // selects the alternate keyframe tables for sets 0x60-0x7F
    sint8 tbl_sel; // 0x172: lb; index of the active TBL_IDX record
    uint8 unk173;
    sint8 unk174; // 0x174: lb; bits 6-7 tested by func_8004324C
    uint8 unk175[2];
    sint8 unk177; // 0x177: lb; nonzero tested by func_8004324C
    uint8 unk178[0x188 - 0x178];
    SLOT_OWNER owner_188; // 0x188: slot owner passed to func_800341BC (func_8003C2D8)
    uint8 unk190[0x198 - 0x190];
    uint32 unk198; // 0x198: cleared by func_800433FC/func_800435BC, set to 1 by func_800434F0
                   // (state of the player's SHL_WORK slot of D_8008A0CC)
    uint8 unk19C[0x1A8 - 0x19C];
    MATRIX base_mtx;       // 0x1A8: body matrix, copied from the scratchpad matrix (func_800325D4)
    MATRIX joint_mtx[15];  // 0x1C8: joint matrices (func_800331A0)
    SVECTOR joint_pos[15]; // 0x3A8: joint positions (func_800331A0); [4] and [7] are copied to the
                           // objects func_80035724 spawns, [11] and [14] by func_80047EC8
    uint8 unk420[0x428 - 0x420];
    VECTOR pos_428;   // 0x428: 16.16 position, moved like pos_l (func_8002FF34)
    SVECTOR svec_438; // 0x438: rounded copy of pos_428
    uint8 unk440[0x44D - 0x440];
    uint8 unk44D; // 0x44D: sb; cleared by func_80039DE8
    uint8 unk44E[0x450 - 0x44E];
    uint8 ids_450[3]; // 0x450: entries of ids_454; Sce_flag_off clears the flag's id here too
    uint8 unk453;
    uint8 ids_454[32]; // 0x454: ids (flag - 0x4FF) of the set scene flags 0x500-0x51F, 0 = empty;
                       // Sce_flag_on adds to the first empty entry, Sce_flag_off removes
    uint8 unk474[0x4F4 - 0x474];
    TBL_IDX rec[16]; // 0x4F4
    uint8 unk574[0x5F4 - 0x574];
} PL_WORK;

extern TBL_ROW *D_80089EAC[];    // 16 tables, one per Player_work.rec[n]
extern PL_WORK Player_work[2];   // 0x800B51B0: two players, 0x5F4 apart
extern PL_WORK *Player_work_ptr; // 0x80098A50

sint32 func_80042238(PL_WORK *pl);
void func_80042314(PL_WORK *pl);

#endif // PLAYER_H
