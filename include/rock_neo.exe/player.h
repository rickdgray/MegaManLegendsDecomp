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
    sint16 val; // 0x06: copy of D_80089EAC[n][idx[1]].val[1]; 0x7FFF is never counted down (pl_shot_spawn)
} TBL_IDX;

// Two opposite keys (PL_WORK.key_pair): mask is the OR of both keys_124 masks, key one of the two.
typedef struct
{
    uint16 mask;
    uint16 key;
} KEY_PAIR;

// Player work, 0x5F4 bytes. Tagged so code_8002E7A8.h can forward-declare it.
typedef struct PL_WORK
{
    uint8 routine_0; // 0x00: as in every pool slot; bit 0: the player is live (lock_on_search)
    uint8 kind_1;    // 0x01: pool kind (0) ORed with the player's index (Work_pools_init); copied to
                     // the spawned shot's field_C (pl_shot_spawn)
    uint8 id_2;      // 0x02: id_2 to flag_5 set by two halfword stores from a SPAWN_ENT (Obj_spawn_tbl_set)
    uint8 type_3;
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags_6; // 0x06: same as MODEL_WORK.flags; 3 or 0 with routine_0 (player_work_init)
    uint8 unk07;
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
    SVECTOR pos;     // 0x14: position (vx and vz are the horizontal axes, vy the height)
    VECTOR pos_l;    // 0x1C: 16.16 fixed-point position; pos is its rounded copy (Obj_pos_set)
    SVECTOR old;     // 0x2C: previous position
    VECTOR old_l;    // 0x34: 16.16 previous position
    SVECTOR spd;     // 0x44: speed; spd.vx is the move passed to func_80041E90 (func_80042A40)
    SVECTOR add;     // 0x4C: acceleration, as MODEL_WORK.add; func_8003CD4C sets add.vx to 0x30
    SVECTOR ang;     // 0x54: rotation; ang.vy is the facing angle (0..0xFFF), used by calc_vol
    SVECTOR old_ang; // 0x5C: previous rotation
    uint8 unk64[0x6C - 0x64];
    sint16 unk6C; // 0x6C: sh; set to 0x3C by func_8003C7B0
    sint16 life;  // 0x6E: Capcom's name (sub_scrn.c); up to life_max, drawn as one gauge cell per
                  // 0x10; func_8001DDE4 does nothing while negative
    uint8 unk70;
    uint8 unk71; // 0x71: sb; cleared by func_8003C7B0
    uint8 unk72;
    uint8 unk73;    // 0x73: sb; cleared by func_8003C7B0
    sint8 field_74; // 0x74: same as MODEL_WORK.field_74; nonzero makes func_80042B58 call
                    // Pl00_shot_enable_off, and func_800441CC leave owner_188 alone
    sint8 field_75; // 0x75: cleared with field_74 when player_entry_set is asked to reset
    sint8 field_76; // 0x76: same as MODEL_WORK.field_76; nonzero: Pl_Shadow_Trans puts the shadow
                    // at pos.vy instead of looking up the ground
    uint8 unk77;
    HIT_ENT *hit_78; // 0x78: same as MODEL_WORK.hit_78; D_80097D90 (player_work_init)
    uint16 unk7C;    // 0x7C: bit 13 (as in Obj_map_push_out's hit flags) starts the fall of func_8003C4EC
    uint8 unk7E[0x94 - 0x7E];
    KEY_ENT *seq_94; // 0x94: same as MODEL_WORK.seq_94: start of the sequence (func_800320B8)
    KEY_ENT *ptr_98; // 0x98: same as MODEL_WORK.ptr_98; b0 picks the packed pose (Pl_pose_unpack)
    uint8 unk9C[0xA4 - 0x9C];
    KEY_CMD cmd_A4; // 0xA4: same as MODEL_WORK.cmd_A4; Pl00_shot_enable_off copies b0 to cmd_100
    uint8 unkA8[0xAC - 0xA8];
    uint8 idx_AC;     // 0xAC: same as MODEL_WORK.idx_AC; passed to func_800320B8 with a set
    uint8 old_idx_AD; // 0xAD: previous idx_AC: a change restarts the sequence (func_8003C418);
                      // 0xFF forces the restart (key_seq_set)
    uint8 unkAE[0xB0 - 0xAE];
    sint16 life_max;    // 0xB0: Capcom's name (sub_scrn.c); upper limit of life (func_80043340)
    sint16 old_life;    // 0xB2: life at the start of the frame (func_8003C88C, func_80041AB0)
    sint16 turn_B4;     // 0xB4: added (* 5) to the Y rotation of joint 1 (Pl_joint_mtx_set)
    sint16 turn_acc_B6; // 0xB6: last step added to turn_B4 (func_80042154)
    uint8 unkB8[0xBD - 0xB8];
    sint8 flags_BD; // 0xBD: func_80048A9C sets bit 5, then swaps it for bit 6
    uint8 unkBE[0xC0 - 0xBE];
    MODEL_WORK *ride_C0; // 0xC0: the object ridden while field_76 is set (Ride_move)
    // 0xC4: target point (x, y, z): where objects aimed at the player go. Obj_launch_set and
    // func_80030418 read it through VIEW_WORK; the stage overlays set it (r3_st05's ST05_PL_VIEW,
    // r3_st14's ST14_PL_VIEW). Obj_launch_set stores the flight time in pad.
    SVECTOR pos_C4;
    uint8 unkCC[0xF8 - 0xCC];
    KEY_ENT *tbl_F8; // 0xF8: keyframe table in use (func_800321C8)
    KEY_ENT *ent_FC; // 0xFC: current keyframe
    KEY_CMD cmd_100; // 0x100: copy of the current keyframe's command; time counts down (func_800323FC)
    uint8 set_104;   // 0x104: index of the keyframe table set in use
    uint8 unk105;    // 0x105: set_104 when func_800321C8 last ran (func_8003C418)
    uint16 pose_mix; // 0x106: set by func_800323FC; 1-3 give limbs the second pose (Pl_joint_mtx_set)
    sint16 val_108;  // 0x108: kept within -0x200..0x200, moved by step_10C (func_80041F54)
    sint16 ang_10A;  // 0x10A: facing angle toward a target (func_8003EEC0); func_8003F188 turns
                     // ang.vy to it once the turn is under 0x80
    sint16 step_10C; // 0x10C: grows toward +-max while a key is held or not, as turn_B4 (func_80041F54)
    sint16 turn_10E; // 0x10E: angle step (+-0x80 or 0x100) added to ang.vy and unk116 each frame
                     // by func_8003D7D4, until unk116 wraps to 0; func_8003EEC0 steps val_108
                     // by it (up to +-0x40) toward the lock-on target's pitch
    sint8 unk110;    // 0x110: sb; set to -1 or 0 by func_80042B58
    uint8 unk111;
    uint8 unk112;  // 0x112: lbu; set to 0 or 2 by the state checks that enter state 2, which save
                   // the old value in unk113 (func_80040380, func_800404FC)
    uint8 unk113;  // 0x113: previous unk112
    sint16 unk114; // 0x114: sh; cleared by func_8003C7B0 with unk116 and unk118
    sint16 unk116; // 0x116: added to ang.vy for the camera yaw (func_800355F0); lh in front_obj_search
    sint16 unk118;
    uint8 unk11A[0x11C - 0x11A];
    // 0x11C-0x123: the pad bits the player sees this frame, copied from a PAD_WORK's now, on, off
    // and auto-repeat words each frame (Player_exec): Joy1's, the scene's D_800C0F96, or
    // D_800C0FE6 for the second player. pad_now is tested against keys_124.
    uint16 pad_now;          // 0x11C: buttons held
    uint16 pad_on;           // 0x11E: buttons pressed this frame
    uint16 pad_off;          // 0x120: buttons released this frame
    uint16 pad_rep;          // 0x122: auto-repeat bits
    uint16 keys_124[16];     // 0x124: pad-bit masks, one row of D_8008A04C (func_800425FC)
    KEY_PAIR key_pair[4][2]; // 0x144: two key pairs per direction unk112 (func_800425FC); [n][1]
                             // picks the sideways move of func_8003D124
    sint16 key_164;          // 0x164: the keys_124 mask held when func_8003D7D4's turn started; cleared
                             // when released or another direction is pressed
    uint8 unk166[0x168 - 0x166];
    sint8 unk168; // 0x168: cleared with unk169 when func_80040764 enters state 9; lb, with unk169
                  // the two grid cells passed to func_8002D004 (func_8003C4EC)
    sint8 unk169;
    sint8 unk16A; // 0x16A: lb; selects the file D_80089200[unk16A] (func_8001F5E4)
    uint8 unk16B; // 0x16B: lbu; bits 1-7 (signed) select the file D_80089204[n] (func_8001F5E4)
    sint8 unk16C; // 0x16C: lb; when nonzero, Sce_flag_on sets it to the count of flags 0x53A-0x53C
    uint8 unk16D[0x170 - 0x16D];
    sint8
        weapon_right_no; // 0x170: lb; the special weapon (Capcom's name, sub_scrn.c); selects the TBL_IDX record counted by func_80037440; nonzero also
                         // selects the alternate keyframe tables for sets 0x40-0x5F (func_800321C8)
    sint8 unk171;  // 0x171: lb; record index for the alternative position (pl_shot_spawn); nonzero
                   // selects the alternate keyframe tables for sets 0x60-0x7F
    sint8 tbl_sel; // 0x172: lb; index of the active TBL_IDX record
    uint8 unk173;
    sint8 unk174; // 0x174: lb; bits 6-7 tested by func_8004324C
    uint8 unk175; // 0x175: lbu; bits 0-2 tested by func_80042770 and func_80042F78
    uint8 unk176;
    sint8 unk177; // 0x177: lb; nonzero tested by func_8004324C
    sint8 unk178; // 0x178: lb; step of func_80042A40 and func_80042DF8
    uint8 unk179[0x182 - 0x179];
    sint16 dist_182; // 0x182: XZ distance to obj_184 (front_box_search)
    // 0x184: the nearest pool object whose box_10 lies in front of the player while keys_124[9] is
    // held (front_box_search), or 0; func_80051970 answers 0 unless it is 0
    MODEL_WORK *obj_184;
    SLOT_OWNER owner_188; // 0x188: slot owner passed to func_800341BC (func_8003C2D8)
    uint32 unk198;        // 0x198: cleared by func_800433FC/func_800435BC, set to 1 by func_800434F0
                          // (state of the player's SHL_WORK slot of D_8008A0CC)
    uint8 unk19C[0x1A8 - 0x19C];
    MATRIX base_mtx;       // 0x1A8: body matrix, copied from the scratchpad matrix (Pl_joint_mtx_set)
    MATRIX joint_mtx[15];  // 0x1C8: joint matrices (func_800331A0)
    SVECTOR joint_pos[15]; // 0x3A8: joint positions (func_800331A0); [4] and [7] are copied to the
                           // objects pl_shot_spawn spawns, [11] and [14] by func_80047EC8
    SVECTOR pos_420;       // 0x420: point 0x96 above joint 1, in scaled world units (Pl_joint_mtx_set)
    VECTOR pos_428;        // 0x428: 16.16 position, moved like pos_l (func_8002FF34)
    SVECTOR svec_438;      // 0x438: rounded copy of pos_428
    SVECTOR ang_440;       // 0x440: rotation saved with pos_428 and svec_438 (player_entry_set)
    uint8 unk448;
    sint8 unk449; // 0x449: sb; set to 1 by func_80042208 when life is not negative
    uint8 unk44A; // 0x44A: frames keys_124[8] has been held (func_80040574 enters state 3 at 9);
                  // cleared on release
    uint8 unk44B; // 0x44B: nonzero keeps func_80040574 from entering state 3
    sint8 unk44C; // 0x44C: bits read and cleared by func_80042B58 (bit 1: spd.vx = -0x280,
                  // bit 0: unk110 = -1)
    sint8 unk44D; // 0x44D: cleared by func_80039DE8; 1 makes Camera_update test the camera for walls
    sint8 unk44E; // 0x44E: lb; when not negative, func_8001F3C8 sets weapon_right_no/unk171 (0 when it is 0)
    sint8 unk44F; // 0x44F: lb; nonzero makes func_8001F3C8 copy tbl_sel to weapon_right_no
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

typedef void (*PL_FUNC)(PL_WORK *pl);

extern TBL_ROW *D_80089EAC[];    // 16 tables, one per Player_work.rec[n]
extern PL_WORK Player_work[2];   // 0x800B51B0: two players, 0x5F4 apart
extern PL_WORK *Player_work_ptr; // 0x80098A50
extern PL_FUNC D_80089F94[4];    // handlers, indexed by PL_WORK.routine_8 (func_8003C418)
extern PL_FUNC D_80089FA4[21];   // state handlers, indexed by routine_9; run second (func_8003C88C)
extern PL_FUNC D_80089FF8[21];   // state handlers, indexed by routine_9; run first (func_8003C88C)
extern HIT_ENT D_80097D90;       // the player's collision box (player_work_init)
extern uint32 D_80097D9C;        // 2; passed to func_80039A38 when the player gets up (func_8003E860)
// The pad bits the player sees during scenes (Player_exec copies them to pad_now ... pad_rep
// when flags_BD bit 5 is set): now, on, off and auto-repeat, as in a PAD_WORK. func_80048A9C sets
// [0] to Player_work[0].keys_124[0] while its scene step runs, 0 otherwise.
extern uint16 D_800C0F96[];
extern uint16 D_800C0F9A;
extern uint16 D_800C0F9C;
extern uint16 D_800C0F9E;
// The same for the second player (Player_work[1]).
extern uint16 D_800C0FE6;
extern uint16 D_800C0FEA;
extern uint16 D_800C0FEC;
extern uint16 D_800C0FEE;

void Player_init(sint32 load);
void Player_exec(void); // per frame (game's game_frame_exec): pad bits, then each player's state
void func_80041E90(PL_WORK *pl, sint16 x, sint16 y, sint16 z);
sint32 func_80042238(PL_WORK *pl);
void func_80042314(PL_WORK *pl);
sint32 func_80042208(void);
void Pl00_shot_enable_off(PL_WORK *pl);
void Pl00_shot_enable_on(PL_WORK *pl);
sint32 func_800423DC(PL_WORK *pl); // keyframe set for func_80042F78 (0x60-0x63)
sint32 func_80042458(PL_WORK *pl); // keyframe set for func_80042770 (0x40-0x43)
void func_8003C2D8(void);          // per frame (game's game_frame_exec)

#endif // PLAYER_H
