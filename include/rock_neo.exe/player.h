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
// D_80089EAC[n][idx[k]].val[k]. Capcom's pp->weapon_data[n] (sub_scrn.c): idx[0..3] are its
// attack_level, bullet_level (energy), dist_level (range) and repeat_level (rapid); rec[1] is the
// buster's, the sum of its equipped parts (Sub_screen_rb_parts_set).
typedef struct
{
    sint8 idx[4];
    sint8 sp_perform; // 0x04: Capcom's name; the special level, index of the sub screen's gauges
    uint8 unk05;
    sint16 val; // 0x06: copy of D_80089EAC[n][idx[1]].val[1]; 0x7FFF is never counted down (func_80035724)
} TBL_IDX;

// Player work, 0x5F4 bytes. Tagged so code_8002E7A8.h can forward-declare it.
typedef struct PL_WORK
{
    uint8 unk00;
    uint8 unk01; // 0x01: lbu; copied to the spawned object's field_C (func_80035724)
    uint8 id_2;  // 0x02: id_2 to flag_5 set by two halfword stores from a SPAWN_ENT (Obj_spawn_tbl_set)
    uint8 type_3;
    uint8 flag_4;
    uint8 flag_5;
    uint8 unk06[2];
    uint8 routine_8; // 0x08: 3 makes player_entry_set also set the saved position (pos_428 ...)
    uint8 routine_9; // 0x09: player state; the state checks (func_800402C4, ...) set it and clear
                     // field_A and field_B with one halfword store; 3 is the pad-driven state of
                     // func_800482A8
    uint8 field_A;   // 0x0A: step within the state; field_A >> 1 picks the joint_pos func_800424D4
                     // copies
    uint8 field_B;
    uint32 field_C; // 0x0C: SPAWN_ENT.field_8 (Obj_spawn_tbl_set)
    uint8 unk10[0x14 - 0x10];
    // 0x14-0x5C: the MODEL_WORK layout (names from Capcom's source: Player_work[0].pos_l, .ang.vy).
    SVECTOR pos;  // 0x14: position (vx and vz are the horizontal axes, vy the height)
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position; pos is its rounded copy (Obj_pos_set)
    SVECTOR old;  // 0x2C: previous position
    VECTOR old_l; // 0x34: 16.16 previous position
    SVECTOR spd;  // 0x44: speed; spd.vx is the move passed to func_80041E90 (func_80042A40)
    uint8 unk4C[0x54 - 0x4C];
    SVECTOR ang;     // 0x54: rotation; ang.vy is the facing angle (0..0xFFF), used by calc_vol
    SVECTOR old_ang; // 0x5C: previous rotation
    uint8 unk64[0x6E - 0x64];
    sint16 unk6E; // 0x6E: sh; copy of unkB0 (func_8005D9EC); func_8001DDE4 does nothing while negative
    uint8 unk70[0x74 - 0x70];
    sint8 field_74; // 0x74: same as MODEL_WORK.field_74; nonzero makes func_80042B58 call
                    // Pl00_shot_enable_off, and func_800441CC leave owner_188 alone
    sint8 field_75; // 0x75: cleared with field_74 when player_entry_set is asked to reset
    uint8 unk76[0x94 - 0x76];
    KEY_ENT *seq_94; // 0x94: same as MODEL_WORK.seq_94: start of the sequence (func_800320B8)
    KEY_ENT *ptr_98; // 0x98: same as MODEL_WORK.ptr_98; b0 picks the packed pose (Pl_pose_unpack)
    uint8 unk9C[0xA4 - 0x9C];
    KEY_CMD cmd_A4; // 0xA4: same as MODEL_WORK.cmd_A4; Pl00_shot_enable_off copies b0 to cmd_100
    uint8 unkA8[0xAC - 0xA8];
    uint8 idx_AC; // 0xAC: same as MODEL_WORK.idx_AC; passed to func_800320B8 with a set
    uint8 unkAD[0xB0 - 0xAD];
    sint16 unkB0; // 0xB0: upper limit of unk6E (func_80043340)
    uint8 unkB2[2];
    sint16 turn_B4; // 0xB4: added (* 5) to the Y rotation of joint 1 (Pl_joint_mtx_set)
    uint8 unkB6[0xBD - 0xB6];
    uint8 flags_BD; // 0xBD: func_80048A9C sets bit 5, then swaps it for bit 6
    uint8 unkBE[0xF8 - 0xBE];
    KEY_ENT *tbl_F8; // 0xF8: keyframe table in use (func_800321C8)
    KEY_ENT *ent_FC; // 0xFC: current keyframe
    KEY_CMD cmd_100; // 0x100: copy of the current keyframe's command; time counts down (func_800323FC)
    uint8 set_104;   // 0x104: index of the keyframe table set in use
    uint8 unk105;    // 0x105: set_104 when func_800321C8 last ran (func_8003C418)
    uint16 pose_mix; // 0x106: set by func_800323FC; 1-3 give limbs the second pose (Pl_joint_mtx_set)
    uint8 unk108[0x110 - 0x108];
    sint8 unk110; // 0x110: sb; set to -1 or 0 by func_80042B58
    uint8 unk111;
    uint8 unk112; // 0x112: lbu; set to 0 or 2 by the state checks that enter state 2, which save
                  // the old value in unk113 (func_80040380, func_800404FC)
    uint8 unk113; // 0x113: previous unk112
    uint8 unk114[0x116 - 0x114];
    sint16 unk116; // 0x116: added to ang.vy for the camera yaw (func_800355F0); lh in front_obj_search
    uint8 unk118[0x11C - 0x118];
    uint16 unk11C; // 0x11C: lhu; mask tested against keys_124[2] and [3] (func_800482A8)
    uint16 unk11E; // 0x11E: lhu; mask tested against keys_124[10] (func_800406A8, func_800406DC)
    uint8 unk120[0x124 - 0x120];
    uint16 keys_124[16];   // 0x124: pad-bit masks, one row of D_8008A04C (func_800425FC)
    uint16 key_pair[8][2]; // 0x144: [0] is the OR of two keys_124 masks, [1] one of the two
                           // (func_800425FC)
    uint8 unk164[0x16A - 0x164];
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
    uint8 unk175; // 0x175: lbu; bits 0-2 tested by func_80042770 and func_80042F78
    uint8 unk176;
    sint8 unk177; // 0x177: lb; nonzero tested by func_8004324C
    sint8 unk178; // 0x178: lb; step of func_80042A40 and func_80042DF8
    uint8 unk179[0x184 - 0x179];
    uint32 unk184;        // 0x184: lw; func_80051970 answers 0 unless it is 0
    SLOT_OWNER owner_188; // 0x188: slot owner passed to func_800341BC (func_8003C2D8)
    uint32 unk198;        // 0x198: cleared by func_800433FC/func_800435BC, set to 1 by func_800434F0
                          // (state of the player's SHL_WORK slot of D_8008A0CC)
    uint8 unk19C[0x1A8 - 0x19C];
    MATRIX base_mtx;       // 0x1A8: body matrix, copied from the scratchpad matrix (Pl_joint_mtx_set)
    MATRIX joint_mtx[15];  // 0x1C8: joint matrices (func_800331A0)
    SVECTOR joint_pos[15]; // 0x3A8: joint positions (func_800331A0); [4] and [7] are copied to the
                           // objects func_80035724 spawns, [11] and [14] by func_80047EC8
    SVECTOR pos_420;       // 0x420: point 0x96 above joint 1, in scaled world units (Pl_joint_mtx_set)
    VECTOR pos_428;        // 0x428: 16.16 position, moved like pos_l (func_8002FF34)
    SVECTOR svec_438;      // 0x438: rounded copy of pos_428
    SVECTOR ang_440;       // 0x440: rotation saved with pos_428 and svec_438 (player_entry_set)
    uint8 unk448;
    sint8 unk449; // 0x449: sb; set to 1 by func_80042208 when unk6E is not negative
    uint8 unk44A; // 0x44A: frames keys_124[8] has been held (func_80040574 enters state 3 at 9);
                  // cleared on release
    uint8 unk44B; // 0x44B: nonzero keeps func_80040574 from entering state 3
    sint8 unk44C; // 0x44C: bits read and cleared by func_80042B58 (bit 1: spd.vx = -0x280,
                  // bit 0: unk110 = -1)
    uint8 unk44D; // 0x44D: sb; cleared by func_80039DE8
    uint8 unk44E[0x450 - 0x44E];
    // 0x450: the equipped buster parts (ids as in rb_parts_sort_data; Capcom's name, sub_scrn.c);
    // Sce_flag_off clears the flag's id here too
    uint8 rb_parts_equip_data[3];
    uint8 unk453;
    // 0x454: the buster parts owned (ids = scene flag 0x500-0x51F - 0x4FF, 0 = empty; index of
    // Rock_buster_parts_tbl + 1), in the sub screen's sort order (Capcom's name, sub_scrn.c).
    // Sce_flag_on adds to the first empty entry, Sce_flag_off removes
    uint8 rb_parts_sort_data[32];
    uint8 unk474[0x4F4 - 0x474];
    TBL_IDX rec[16]; // 0x4F4
    uint8 unk574[0x5F4 - 0x574];
} PL_WORK;

extern TBL_ROW *D_80089EAC[];    // 16 tables, one per Player_work.rec[n]
extern PL_WORK Player_work[2];   // 0x800B51B0: two players, 0x5F4 apart
extern PL_WORK *Player_work_ptr; // 0x80098A50
// The pad bits the player sees this frame (read by func_8003C07C); func_80048A9C sets [0] to
// Player_work[0].keys_124[0] while its scene step runs, 0 otherwise.
extern uint16 D_800C0F96[];

void func_80041E90(PL_WORK *pl, sint16 x, sint16 y, sint16 z);
sint32 func_80042238(PL_WORK *pl);
void func_80042314(PL_WORK *pl);
sint32 func_80042208(void);
void Pl00_shot_enable_off(PL_WORK *pl);
void Pl00_shot_enable_on(PL_WORK *pl);
sint32 func_800423DC(PL_WORK *pl); // keyframe set for func_80042F78 (0x40-0x43)
sint32 func_80042458(PL_WORK *pl); // keyframe set for func_80042770 (0x40-0x43)

#endif // PLAYER_H
