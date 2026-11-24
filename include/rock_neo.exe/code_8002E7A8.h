#ifndef CODE_8002E7A8_H
#define CODE_8002E7A8_H

// code_8002E7A8.c's subsystem (not identified yet; rename with the file): the work pools
// (Work_pools_init), the scratchpad scene scale and fog, distances and angles, keyframe tables.

#include "common.h"
#include "psyq/libgte.h"
#include "scratch.h"

// Keyframe table sets, loaded at fixed addresses (indexed by set number).
#define Key_tbl_a ((KEY_ENT **)0x800D9D00)

#define Key_tbl_b     ((KEY_ENT **)0x800DB800)
#define Key_tbl_c     ((KEY_ENT **)0x800DC300)
#define Key_tbl_c_alt ((KEY_ENT **)0x800DC780)
#define Key_tbl_d     ((KEY_ENT **)0x800DCB80)
#define Key_tbl_d_alt ((KEY_ENT **)0x800DD000)

// Offsets of the player's joints (15 SVECTORs, one per PL_WORK.joint_pos), loaded with the keyframe
// tables (Pl_joint_mtx_set). The weapon overlay r3_shl04 reads the same word as its own model pointer.
#define Joint_ofs_tbl (*(SVECTOR **)0x800DD600)

// The player's packed poses, per keyframe set (Pose_tbl_x[set - first set of the range][step's
// b0] is a packed pose), in the same set ranges as the Key_tbl_* above (Pl_pose_unpack).
#define Pose_tbl_a     ((uint32 ***)0x800DD604)
#define Pose_tbl_b     ((uint32 ***)0x800E9600)
#define Pose_tbl_c     ((uint32 ***)0x800ED600)
#define Pose_tbl_c_alt ((uint32 ***)0x800EF600)
#define Pose_tbl_d     ((uint32 ***)0x800F1600)
#define Pose_tbl_d_alt ((uint32 ***)0x800F3600)

// Obj_work_flag_change's flag: close the slots (Capcom's name, from eve19.c).
#define WORK_KILL 0x80
// Obj_work_flag_change's mask bit for the player's shots (Capcom's name, from sub_scrn.c).
#define WORK_PL_SHL 0x8

// Handler tables of the work pools, kept on the scratchpad (func_800135DC stores Work_3C0_tbl).
// Each pool's update loop (game.c) calls tbl[id_2] (tbl[id_2][flag_4] for the two-level ones)
// for every slot whose routine_0 and flags both have bit 0 set.
#define Work_3C0_tbl (*(WORK3C0_FUNC ***)0x1F800058) // D_8009F108's
#define Work_5A4_tbl (*(WORK5A4_FUNC ***)0x1F80005C) // D_800C3580's
#define Shl_work_tbl (*(SHL_FUNC **)0x1F800060)      // D_8009CF88's, ids below 0x80
#define Work_48_tbl  (*(WORK48_FUNC **)0x1F800064)   // D_800A3B40's, ids below 0x80
#define Eve_work_tbl (*(EVE_FUNC **)0x1F800068)      // D_800A2D08's
#define Work_50_tbl  (*(WORK50_FUNC **)0x1F80006C)   // D_800BF118's

#define ABS(x) ((x) < 0 ? -(x) : (x))

// Store to a bogus address, done when func_8002FA38 finds no matching entry.
#define Entry_missing_trap (*(sint32 *)0x87654321)

// Collision box passed to Pos_map_push_out/func_80048EA4: three (min, max) halfword pairs, each
// -n, +n in the tables (D_8008A310, D_8008A618). max_A is the half-height kept clear above the
// ground (func_80046438).
typedef struct
{
    sint16 min_0;
    sint16 max_2;
    sint16 min_4;
    sint16 max_6;
    sint16 min_8;
    sint16 max_A;
} HIT_ENT;

// PL_WORK is defined in player.h, which includes this header.
struct PL_WORK;

// ---- Work pool slots (Work_pools_init). ----
// Every slot, and PL_WORK, starts with the same header: routine_0, kind_1 (pool kind, 0x10 * pool
// number, ORed with the slot index), and at 6 a flags byte: set to 3 on open, bits 0-1 changed by
// func_8002F3A8, bit 5 keeps the slot alive in func_8002F420 (moved instead of closed), bit 6 set
// by func_80033500/func_8003354C.

// Object holding a bitmask of the slots it owns (see func_8003545C). An embedded block, not a
// whole object: PL_WORK.owner_188, PL_SHL_WORK.owner_C4, D_800986D8, and the owner stored in each
// SLOT_REQ.
typedef struct
{
    uint32 hit_0; // hits taken: top byte ORed from the other request's word, low 16 bits its
                  // damage summed (hit_pair_check; func_80043F34's code adds to it too)
    uint32 mask_4;
    SVECTOR vec_8; // where the hit came from (pad 1), or the other capsule's axis (pad 0)
} SLOT_OWNER;

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2; // the kind: index of Eve_work_tbl (eve_work_exec); id_2 and type_3 are cleared
                // by one halfword store (on open)
    uint8 type_3;
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 field_8; // field_8 to field_B are cleared by one word store (on open)
    uint8 field_9;
    uint8 field_A;
    uint8 field_B;
    sint8 field_C; // field_C to field_F are cleared by one word store (on open); the stage events'
                   // timer (r3 overlays' STAGE_EVENT.timer_C)
    sint8 field_D;
    sint8 field_E;
    sint8 field_F;
    uint32 field_10;
    SVECTOR pos; // 0x14: position (x, height, z); x and z moved by func_8002F998
    uint8 pad_1C[8];
} EVE_WORK; // 0x24 bytes

typedef void (*EVE_FUNC)(EVE_WORK *wp);

typedef struct
{
    uint8 r, g, b, pad;
} RGB_ENT;

// The rotation part of a MATRIX (m and its pad, 0x14 bytes), copied as one block without t
// (Model_parts_mtx_set).
typedef struct
{
    sint32 w[5];
} MATRIX_ROT;

// Model data of a WORK_5A4 (info_88): tbl_70 holds one 0x14-byte entry per part, after one for
// the body (func_80031324 takes entry n + 1).
typedef struct
{
    uint8 pad_0[0x14];
} ENT_14;

typedef struct
{
    uint8 pad_0[0x70];
    ENT_14 *tbl_70;
} PARENT_INFO;

// Per-part entries of a model object (MODEL_WORK.slot_F8, WORK_5A4.slot_F8/pos_180). slot_F8[0]'s
// child_id is the part count; for the other parts it is the parent part (negative: none) and
// part_2 the index of the part's offset (MODEL_WORK.ofs_9C) and pose rotation (Model_parts_mtx_set).
typedef struct
{
    uint8 mesh_0; // the part's mesh in the level of detail (Model_parts_draw)
    sint8 child_id;
    uint8 part_2;
    sint8 hide_3; // < 0: the part is not drawn (Model_parts_draw); set to -1 or 0 by the event steps
                  // (func_80068388, func_8006854C)
} CHILD_SLOT;

typedef struct
{
    uint16 x, y, z;
    sint16 col; // RGB555 colour, faded by part_col_step (func_80068388 sets it)
} CHILD_POS;

// Command script of a WORK_3C0 (WORK_3C0.script, run by script_exec from func_800150E0): data
// is a list of halfword commands (1..27, 0 ends a frame) followed by their arguments.
typedef struct
{
    sint16 *data; // 0x0: command stream
    uint16 pos;   // 0x4: index of the current command in data
    sint16 wait;  // 0x6: frames left before the next commands run
    uint16 add_8; // 0x8: added to WORK_3C0.ang.vy each frame
    uint16 add_A; // 0xA, 0xC, 0xE: added to WORK_3C0.scale.vx, vy, vz each frame
    uint16 add_C;
    uint16 add_E;
    uint8 pad_10[2];
    uint8 direct_12; // nonzero: pos_l moved by spd directly, else through Obj_pos_set
    uint8 field_13;  // copied to WORK_3C0 0x110 when it changes
    uint8 field_14;  // previous field_13
} SCRIPT_WORK;

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2;   // MODEL_WORK.id_2; id_2 and type_3 are cleared by one halfword store (on open)
    uint8 type_3; // MODEL_WORK.type_3; func_80015428 sets it to the object's index (0..15)
    uint8 flag_4; // second index of Work_3C0_tbl (first: id_2): the kind's routine (func_80016FD4)
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8; // routine_8 to timer_B are cleared by one word store (on open)
    uint8 field_9;   // set (with field_A cleared) by the event steps of code_800680BC
    uint8 field_A;
    uint8 timer_B;
    sint8 field_C;   // field_C to timer_F are cleared by one word store (on open)
    sint8 slot_D;    // nonzero: play the sound of field_E (func_800150E0)
    sint8 field_E;   // sound: 0-2 repeat every timer_F frames, 3-4 play once
    sint8 timer_F;   // frames to the next repeat of the sound
    HIT_ENT *box_10; // 0x10: box the player's search in front tests (front_box_search), or 0
    // 0x14-0x5C: the MODEL_WORK layout (a model kind).
    SVECTOR pos;     // 0x14: position (x, height, z)
    VECTOR pos_l;    // 0x1C: 16.16 fixed-point position
    SVECTOR old;     // 0x2C: previous position
    VECTOR old_l;    // 0x34: 16.16 previous position
    SVECTOR spd;     // 0x44: speed
    SVECTOR add;     // 0x4C: acceleration
    SVECTOR ang;     // 0x54: rotation; ang.vy is the Y angle (0..0xFFF)
    SVECTOR old_ang; // 0x5C: previous rotation (func_800150E0)
    uint32 field_64; // cleared on open (func_80014AC0)
    uint8 pad_68[0xC];
    sint8 field_74; // MODEL_WORK.field_74; 0x74-0x77 cleared by one word store on open
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (MODEL_WORK.hit_78)
    uint8 pad_7C[4];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (Obj_player_dist_set)
    uint8 *data_88;    // 0x88: MODEL_WORK.data_88
    uint8 pad_8C[0x20];
    uint8 idx_AC;     // MODEL_WORK.idx_AC: keyframe sequence
    uint8 old_idx_AD; // previous idx_AC: a change restarts the sequence (func_800150E0)
    uint8 pad_AE[0x62];
    uint8 field_110; // set from script.field_13 when it changes
    uint8 pad_111[0x47];
    SVECTOR scale;  // MODEL_WORK.scale; moved by script.add_A/C/E each frame (func_800150E0)
    MATRIX mtx_160; // 0x160: MODEL_WORK.mtx_160
    CHILD_POS pos_180[13];
    MATRIX mtx_1E8[11]; // 0x1E8: the parts' matrices (Model_parts_mtx_set)
    SCRIPT_WORK script; // 0x348: command script run by script_exec
    uint8 pad_360[0x28];
    RGB_ENT base;    // 0x388: also the scales of Model_parts_mtx_set (x, y, z in r, g, b; 0x20 = 1)
    RGB_ENT tbl[13]; // 0x38C
} WORK_3C0;          // 0x3C0 bytes

typedef void (*WORK3C0_FUNC)(WORK_3C0 *wp);

// The effect layout of the shot and effect objects (WORK_48 at 0x14, SHL_WORK at 0x88), after
// Capcom's shot code (wk_p->efc.model.m, .sv, .rgbc). Which one an object uses is its kind's: bit 2
// of routine_0 is set for the model one. The sprite one's code word is the same packed value in
// both pools (0x3D48002E).
typedef struct
{
    uint8 *data; // model data of the EBD entry, set by Model_work_init
    MATRIX mtx;  // 0x04: rotation and scale (diagonal = pos.pad); Capcom's m
    SVECTOR pos; // 0x24: position (x, y = height, z); Capcom's sv. Passed to Sound_call2.
    uint32 rgbc; // 0x2C: code and colour (0x02808080)
} EFC_MODEL;     // 0x30 bytes

typedef struct
{
    uint32 code;        // packed start word (0x3D48002E): CLUT (high half) and texture page (low half)
    uint32 rgbc;        // 0x04: code and colour (0x2E808080)
    sint16 pos[3];      // 0x08: position (x, y, z)
    uint8 u;            // 0x0E-0x13: the WORK_48 kinds' field_22..field_26. u, v: texture corner of
    uint8 v;            // the 32 x 32 cell (Efc_sprite_draw reads them as one halfword)
    uint16 size;        // 0x10: half size
    uint16 angle;       // 0x12: roll (bits 0-5, 64 steps), with draw flag bit 5
    uint8 pad_14[0x1C]; // 0x14-0x2F: depends on the kind
} EFC_SPRITE;           // 0x30 bytes

typedef union
{
    EFC_MODEL model;
    EFC_SPRITE sprite;
} EFC;

// A slot of the effect pool D_800A3B40 (func_80031618 / func_80031988), as the code shared by every
// kind sees it. The kind is id_2: the pool update (game's func_800172F4/func_800173B4) calls
// handler[id_2], from the stage overlay's table for ids below 0x80 and from D_80089858 for 0x80
// and up. Each ROCK_NEO kind has its own full struct (W48_80_WORK ... W48_8A_WORK, in the header
// of the file with its code), cast to WORK_48 for the shared code, as Capcom does with
// EM_WORK -> MODEL_WORK. 0x14-0x43 hold the EFC layout of the kind (model or sprite); bit 2 of
// routine_0 says which, and func_8002F928 moves efc.model.pos or efc.sprite.pos by it.
typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2;   // the kind; id_2 and type_3 are cleared together by one halfword store
    uint8 type_3; // the kind's variant (selects the sound id in func_80046848)
    uint8 flag_4; // index into the dispatch tables of func_800485E4
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8;
    uint8 field_9;
    uint8 field_A;
    uint8 timer_B;   // counts down; routine_8 advances when it reaches 0
    uint32 field_C;  // depends on the kind; cleared on open
    uint32 field_10; // cleared on open
    EFC efc;         // 0x14: the kind's layout (model or sprite)
    uint32 field_44; // depends on the kind
} WORK_48;           // 0x48 bytes

typedef void (*WORK48_FUNC)(WORK_48 *wp);

// Capcom's SHL_WORK (their source opens one with `(SHL_WORK *)Open_SHL_WORK()`): a shot of the
// pool D_8009CF88[32], kind 0x60 (Open_SHL_WORK / Close_SHL_WORK; the scene code and the stage
// overlays). Header, the MODEL_WORK layout, the shot's EFC and, from 0xB8, a free block that each
// shot kind (id_2) lays its own struct over, as Capcom's shot 0x38 does:
// `fp = (SHL38_FREE *)&sp->free[0];`. The player's shots (pool 0x10) have their own struct,
// PL_SHL_WORK, with the same layout.
typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2;   // the shot kind; id_2 and type_3 are cleared together by one halfword store
    uint8 type_3; // the kind's variant
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8; // routine_8 to timer_B are cleared by one word store (on open)
    uint8 field_9;
    uint8 field_A;
    uint8 timer_B;
    sint8 field_C; // 0x0C-0x0F: bytes of the shot kind (PL_SHL_WORK: owner, slot), cleared by one
                   // word store on open; a byte, since a uint32 there changes how that store is
                   // scheduled (Open_SHL_WORK)
    uint8 pad_D[3];
    HIT_ENT *box_10; // 0x10: box the player's search in front tests (front_box_search, ids below
                     // 0x80), or 0; cleared on open
    // 0x14-0x5C: the MODEL_WORK layout (a model kind: Model_work_init binds kinds 0x10 and 0x60).
    SVECTOR pos;  // 0x14: position (x, height, z)
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position
    SVECTOR old;  // 0x2C: previous position
    VECTOR old_l; // 0x34: 16.16 previous position
    SVECTOR spd;  // 0x44: speed
    SVECTOR add;  // 0x4C: acceleration
    SVECTOR ang;  // 0x54: rotation; ang.vy is the Y angle (0..0xFFF), set from the scene data
                  // by scene_obj_open
    uint8 pad_5C[0x18];
    sint8 field_74; // MODEL_WORK.field_74; 0x74-0x77 cleared by one word store on open
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24); 0 on open
    sint16 field_7C; // MODEL_WORK.field_7C
    uint8 pad_7E[2];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (Obj_player_dist_set)
    EFC efc;           // 0x88
    uint8 free[0x54];  // 0xB8: the shot kind's own data
} SHL_WORK;            // 0x10C bytes

typedef void (*SHL_FUNC)(SHL_WORK *wp);

// A player's shot: a slot of the pool D_800BFB20[16], kind 0x10 (Open_PL_SHL_WORK / Close_PL_SHL_WORK),
// spawned by pl_shot_spawn. Its id_2 is byte 7 of the player's action record (D_80089A8B), and
// handler[id_2] is func_800433C0 or func_800437A8 (code_8004324C). Same layout as SHL_WORK, with
// its sprite EFC and free block written out: the flight direction sits in the EFC's kind bytes,
// the target and slot owner in the free block.
typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2;   // the shot kind; id_2 and type_3 are cleared together by one halfword store
    uint8 type_3; // 0x80 while the object holds a slot of D_80098798 (pl_shot_spawn)
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8; // routine_8 to timer_B are cleared by one word store (on open)
    uint8 field_9;
    uint8 field_A;
    uint8 timer_B;
    sint8 field_C; // field_C to pad_F are cleared by one word store (on open); id of the owning
                   // player for the kinds of D_8008A0CC (func_800433C0); read with lb
                   // (func_800435F8, func_80043E78), passed to func_80036294 as (uint8)
    sint8 slot_D;  // slot claimed by func_8003545C
    sint8 field_E;
    uint8 pad_F;
    uint32 field_10;
    // 0x14-0x5C: the MODEL_WORK layout.
    SVECTOR pos;  // 0x14: position (x, height, z); pad: set by pl_shot_spawn
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position
    SVECTOR old;  // 0x2C: previous position, passed to func_8003430C with pos (func_800435F8)
    VECTOR old_l; // 0x34: 16.16 previous position (moved with pos_l by func_8002F884)
    SVECTOR spd;  // 0x44: speed; added (<< 8) to pos_l each frame by func_80043A8C
    SVECTOR add;  // 0x4C: acceleration
    SVECTOR ang;  // 0x54: rotation
    uint8 pad_5C[8];
    uint16 field_64; // low 12 bits: Y angle of the launch direction (func_800437F8)
    uint8 pad_66[0xE];
    sint8 field_74; // MODEL_WORK.field_74; 0x74-0x77 cleared by one word store on open
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24); 0 on open
    sint16 field_7C; // nonzero ends the flight of func_80043A8C
    uint8 pad_7E[2];
    uint32 dist_80[2];
    // 0x88-0xB7: the sprite EFC.
    uint32 code_88;   // 0x88: EFC_SPRITE.code, set from D_80097DAC (by Player_work[0].rec[1].idx[0])
    uint32 rgbc_8C;   // 0x8C: code and colour (0x2E808080)
    uint16 pos_90[3]; // 0x90: copy of pos (func_800437F8, func_80043A8C)
    uint8 field_96;
    uint8 field_97;
    uint16 field_98; // passed to func_8003430C as both positions' pad (func_80043E78)
    uint16 field_9A; // 0x9A: += 5 each frame by func_80043A8C
    uint8 pad_9C[8];
    SVECTOR dir_A4; // 0xA4: unit direction of flight (func_800437F8), turned toward tgt_BC
    uint8 pad_AC[0xC];
    // 0xB8-0x10B: the free block.
    uint8 pad_B8[4];
    SVECTOR tgt_BC;      // 0xBC: target position (0 when none); projected and cleared each frame by
                         // func_80035508 while the object holds a slot of D_80098798
    SLOT_OWNER owner_C4; // 0xC4: slot owner passed to func_8003430C
    uint8 pad_D4[0x38];
} PL_SHL_WORK; // 0x10C bytes

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2; // the kind: index of Work_50_tbl (func_80017528); id_2 and type_3 are cleared
                // by one halfword store (on open)
    uint8 type_3;
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8; // routine_8 to timer_B are cleared by one word store (on open); set to 2
                     // before the scene code calls the object's handler (func_8001E20C)
    uint8 field_9;
    uint8 field_A;
    uint8 timer_B;
    sint8 field_C; // field_C to pad_F are cleared by one word store (on open)
    sint8 slot_D;
    sint8 field_E; // set to -0x80 by the event step func_80068728
    uint8 pad_F;
    HIT_ENT *box_10; // 0x10: box the player's search in front tests at efc's pos (front_box_search), or 0
    EFC efc;         // 0x14: drawn by work_50_draw, like WORK_48's
    uint8 pad_44[0xC];
} WORK_50; // 0x50 bytes

typedef void (*WORK50_FUNC)(WORK_50 *wp);

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2; // the kind: first index of Work_5A4_tbl (func_80017094); id_2 and type_3 are
                // cleared by one halfword store (on open)
    uint8 type_3;
    uint8 flag_4; // second index of Work_5A4_tbl: the kind's routine
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8; // routine_8 to timer_B are cleared by one word store (on open)
    uint8 field_9;   // set (with field_A cleared) by the event steps of code_800680BC
    uint8 field_A;
    uint8 timer_B;
    sint8 field_C; // field_C to pad_F are cleared by one word store (on open)
    sint8 slot_D;  // set and cleared by the event steps (func_800687D8, func_8006854C)
    sint8 field_E;
    uint8 pad_F;
    HIT_ENT *box_10; // 0x10: box the player's search in front tests (front_box_search), or 0
    // 0x14-0x5C: the MODEL_WORK layout (a model kind).
    SVECTOR pos;  // 0x14: position (x, height, z)
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position
    SVECTOR old;  // 0x2C: previous position
    VECTOR old_l; // 0x34: 16.16 previous position
    uint8 pad_44[0x10];
    SVECTOR ang; // 0x54: rotation; ang.vy is the Y angle (0..0xFFF)
    uint8 pad_5C[0x18];
    sint8 field_74; // MODEL_WORK.field_74; 0x74-0x77 cleared by one word store on open
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (MODEL_WORK.hit_78)
    uint8 pad_7C[4];
    uint32 dist_80[2];    // squared distance (<< 2) to each player, -1 when too far (Obj_player_dist_set)
    PARENT_INFO *info_88; // 0x88: model data (func_80031324)
    uint8 pad_8C[0x6C];
    // 24 parts, like tbl (func_80031324 detaches part n into a CHILD_WORK).
    CHILD_SLOT slot_F8[24]; // 0xF8: child_id at +1
    SVECTOR scale;          // 0x158: MODEL_WORK.scale
    MATRIX mtx_160;         // 0x160: MODEL_WORK.mtx_160
    CHILD_POS pos_180[24];  // 0x180
    MATRIX mtx_240[24];     // 0x240: the parts' matrices (Model_parts_mtx_set); copied into a detached part
    RGB_ENT base;           // 0x540: also the scales of Model_parts_mtx_set (x, y, z in r, g, b; 0x20 = 1)
    RGB_ENT tbl[24];        // 0x544
} WORK_5A4;                 // 0x5A4 bytes

typedef void (*WORK5A4_FUNC)(WORK_5A4 *wp);

// 0x28-byte fog/far-colour block (copied by fog_block_apply): the fog CLUT rows by depth, then the
// far colour and fog near distance (func_80036A88 sets them in D_8009A350, Fog_param_get reads them).
typedef struct
{
    uint8 b[0x20]; // 0x00: fog CLUT row by depth
    uint8 far_r;   // 0x20
    uint8 far_g;   // 0x21
    uint8 far_b;   // 0x22
    uint8 fog_23;  // 0x23: copied to Scratch_fog_2 (func_800371A0)
    uint16 near;   // 0x24
    uint16 unk_26; // 0x26
} FOG_BLOCK;

// Four 0x14-byte entries at D_8009A300 (func_800358F0 bases it there; func_80036C50 claims one,
// func_80033EBC frees all): id 0 means free. Each is a homing point run by func_80036D40, laid out
// like TRACK_WORK: launched from the player toward the object of id_6, it sets bit 0 of
// owner_10's mask_4 when it reaches it.
typedef struct
{
    sint16 x, y, z;       // position (passed to func_80049C54 as an SVECTOR)
    uint8 id_6;           // id byte of the target object (func_80036294); 0: free
    uint8 state_7;        // 0 waiting for the target to come in view, 1 flying
    sint16 vel[3];        // 0x8: velocity (passed to func_80033F04 as an SVECTOR)
    uint8 timer_E;        // frames of flight left
    sint8 flag_F;         // toggled when the entry is taken: nonzero aims the launch at the target,
                          // zero launches it straight up
    SLOT_OWNER *owner_10; // told of the hit (func_80036C50's owner)
} SLOT_ENT;

// A homing tracker kept inside a stage object (func_800364B0, through func_8003648C): a point
// launched from the object toward the player and steered after it; on reaching the player it
// holds for D_800899AC[kind].hold frames while the object stays in range.
typedef struct
{
    sint16 x, y, z; // position (passed to func_80049C54 as an SVECTOR)
    uint8 kind;     // index of D_800899AC
    uint8 state;    // 0 idle, 1 flying, 2 holding
    sint16 vel[3];  // 0x8: velocity (passed to func_80033F04 as an SVECTOR)
    uint8 timer;    // frames left in the state
    uint8 height;   // signed: launch height above the object, in units of 16
} TRACK_WORK;

// Per-kind timing of TRACK_WORK (D_800899AC).
typedef struct
{
    uint8 start; // frames of flight
    uint8 hold;  // frames to hold once the player is reached
    uint8 range; // the tracker drops when the object's dist_80 is at least range << 20
    uint8 pad;
} TRACK_INFO;

// Keyframe command word: time is the frame count, ctl < 0 is a jump (-1: reload time).
typedef union
{
    uint32 word;
    struct
    {
        uint8 b0;
        sint8 time;
        sint8 b2; // lb: the player's states test it for 1 and for bit 7 (func_8003E6B0)
        sint8 ctl;
    } b;
} KEY_CMD;

typedef struct
{
    KEY_CMD cmd;
    uint32 arg;
} KEY_ENT; // 8 bytes

// 16-byte entry of the EBD tables func_8002FA38 searches (Stage_ebd_0, ...).
typedef struct
{
    uint8 kind_0;
    uint8 id_1;
    uint8 sub_2;
    uint8 pad_3;
    uint8 *ptr_4;
    sint32 *ptr_8;
    KEY_ENT **seq_tbl_C; // keyframe sequences, copied to MODEL_WORK.seq_tbl_90
} ATTACH_ENT;

// Capcom's MODEL_WORK (their source passes EM_WORK to Model_work_init, Obj_pos_set and EM_Char_Set
// as `(MODEL_WORK *)`): the layout every model object starts with: PL_WORK and the slots of the
// model pools (SHL_WORK, WORK_3C0, WORK_5A4). Like Capcom, each object keeps its own type and is
// cast to MODEL_WORK for these functions. The header (routine_0, kind_1, flags at 6) is common
// to every pool slot, so the functions that only touch it (func_8002F3A8) take this type too.
// Names from Capcom's source: id, type, pos, pos_l, old, old_l, spd, add, ang.
// The stage collision services (func_80037694, code_80048620's func_80049C24, Obj_map_push_out,
// func_80051BAC) take it too: players, shots and every stage overlay's objects call them.
typedef struct
{
    uint8 routine_0;
    uint8 kind_1; // pool kind (0x10 * pool number) ORed with the slot index
    uint8 id_2;   // id: matched against the EBD entries (func_8002FA38)
    uint8 type_3; // type: Model_work_init's `sub` usually points here
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: bits 0-1 changed by func_8002F3A8 (see "Work pool slots" above)
    uint8 pad_7[5];
    uint32 field_C; // set from SPAWN_ENT.field_8 (Obj_spawn_tbl_set)
    uint32 field_10;
    SVECTOR pos;     // 0x14: position (vx and vz horizontal, vy the height)
    VECTOR pos_l;    // 0x1C: 16.16 fixed-point position; pos is its rounded copy (Obj_pos_set)
    SVECTOR old;     // 0x2C: previous position
    VECTOR old_l;    // 0x34: previous 16.16 position (moved with pos_l by func_8002F884)
    SVECTOR spd;     // 0x44: speed; pad: frames to the target (func_80030EE8)
    SVECTOR add;     // 0x4C: acceleration
    SVECTOR ang;     // 0x54: rotation; ang.vy is the facing angle (0..0xFFF)
    SVECTOR old_ang; // 0x5C: previous rotation
    uint8 pad_64[0x10];
    sint8 field_74; // read with lb by Obj_map_push_out, passed to map_push_out
    uint8 pad_75;
    sint8 field_76; // cleared with field_C0 by func_80052644
    uint8 pad_77;
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24, Obj_map_push_out)
    sint16 field_7C; // cleared by func_80051BAC
    uint8 pad_7E[2];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (Obj_player_dist_set)
    uint8 *data_88;    // 0x88: model data of the EBD entry (func_8002FA38)
    uint8 pad_8C[4];
    KEY_ENT **seq_tbl_90; // keyframe sequences, indexed by idx_AC (func_80032304)
    KEY_ENT *seq_94;      // start of the sequence chosen by idx_AC (func_80032304)
    KEY_ENT *ptr_98;      // current step; b0 indexes the entry of ptr_A0[idx_AC] (Model_pose_unpack)
    SVECTOR *ofs_9C;      // offset of each part from its parent, by CHILD_SLOT.part_2 (Model_parts_mtx_set)
    sint32 *ptr_A0;       // table of tables of packed pose data (Model_pose_unpack)
    KEY_CMD cmd_A4;       // copy of the current step's command; time counts down
    uint8 pad_A8[4];
    uint8 idx_AC;
    uint8 pad_AD[0x13];
    void *field_C0; // an object; func_80052644 clears it (and field_76) when it equals its key
    // 0xC4: in shots, the hit word (PL_SHL_WORK.owner_C4.hit_0, SHL_WORK's free block,
    // STCOM23_WORK.hit_C4): top byte nonzero once hit, and func_80037694 then skips the stage
    // collision. The player and stage NPCs keep a target SVECTOR here instead (VIEW_WORK.pos_C4,
    // PL_WORK.pos_C4).
    uint32 hit_C4;
    uint8 pad_C8[0x30];
    // 0xF8: the part tree; func_8002FA38 copies 0x18 bytes of the model data here (kinds 0x20
    // and 0x40). The count of parts depends on the kind (WORK_5A4: 24).
    CHILD_SLOT slot_F8[24];
    SVECTOR scale;  // 0x158: scale (0x400 = 1, func_80014AC0), shifted by Scratch_scale_shift; Capcom: size
    MATRIX mtx_160; // 0x160: body matrix, scaled (Model_parts_mtx_set)
    // 0x180: part positions (WORK_5A4.pos_180); func_800536B0 reads part n's, for the objects
    // that queue a part on the D_80098894 list. Only objects with parts have them.
    SVECTOR part_180[24];
} MODEL_WORK;

// One 0x14-byte entry of a room's spawn table (the stage overlays pass theirs to Obj_spawn_tbl_set),
// ended by routine_0 == -1. kind_1 picks the pool (0 a player, then 0x20 WORK_3C0, 0x40 WORK_5A4,
// 0x60 SHL_WORK, 0x80 WORK_48, 0xC0 EVE_WORK, 0xE0 WORK_50); the rest is copied into the slot.
typedef struct
{
    sint8 routine_0; // the slot's routine_0; -1 ends the table
    uint8 kind_1;
    uint8 id_2;   // the slot's id_2 (copied with type_3 by one halfword store)
    uint8 type_3; // the slot's type_3; for a player, its index
    uint8 flag_4; // the slot's flag_4 and flag_5 (one halfword store)
    uint8 flag_5;
    uint8 pad_6;
    uint8 ang_7;    // Y angle >> 4
    uint32 field_8; // the slot's field_C
    SVECTOR pos;    // 0xC: position
} SPAWN_ENT;

// Screen box of the lock-on search (D_8008994C, by the special level when Player_work[0].weapon_right_no
// is 8): a target is taken when its depth is below z_max and its screen point lies strictly inside
// (lock_on_search).
typedef struct
{
    sint16 z_max;
    sint16 x_min;
    sint16 x_max;
    sint16 y_min;
    sint16 y_max;
    sint16 pad;
} LOCK_BOX;

// A hit request queued for the frame in D_800A2F48 (func_800341BC, func_8003430C; tested by
// Hit_check_all). v.pad holds the radius (bits 0-8), the capsule flags (bits 9-10: paired with the
// next request) and the kind (bits 13-15).
typedef struct
{
    SVECTOR v;
    uint32 flags; // top byte: the owner's id; low 23 bits: the address of the SLOT_OWNER
} SLOT_REQ;

// A part detached from its WORK_5A4 parent (func_80031324). func_80031324 has no callers in the
// code split so far (no jal, no table entry), so CHILD_WORK's pool is still unknown.
typedef struct
{
    uint8 pad_0[0xB];
    uint8 child_id;
    uint8 pad_C[8];
    uint16 x_14;
    uint16 y_16;
    uint16 z_18;
    uint16 pad_1A;
    sint32 x_1C;
    sint32 y_20;
    sint32 z_24;
    uint8 pad_28[0x60];
    ENT_14 *ent_88;
    MATRIX mtx_8C; // the parent's part matrix (WORK_5A4.mtx_240)
    uint16 x_AC;
    uint16 y_AE;
    uint16 z_B0;
    uint16 pad_B2;
    uint32 color_B4;
    WORK_5A4 *parent_B8;
} CHILD_WORK;

// Object with a view direction (ang.vy) and a target point at 0xC4 (pos_C4): what func_80030418,
// Obj_launch_set and func_80030CF0 take as `from` and `to` (pos_C4.pad gets the flight time).
// Callers pass the player (PL_WORK.pos_C4: stcom09, stcom12, stcom17, r3_st05, r3_st14, ...),
// stage NPCs (r3_st05's villagers, r3_st03's actors: Obj_launch_set's `to` via func_80030934),
// and the stage objects func_80030418 takes as `from` (stcom17.h's value_C4, "a joint, for the
// player range tests"). Shots and stcom23-type objects keep a hit word at 0xC4 instead
// (SHL_WORK's free block, PL_SHL_WORK.owner_C4, STCOM23_WORK.hit_C4; MODEL_WORK.hit_C4, read by
// func_80037694), so there's no single type yet. To do: check against
// Capcom's EM_WORK in tcrf.txt (eve19.c names no field at 0xC4; its `size` is at 0x158).
typedef struct
{
    uint8 pad_0[0x54];
    SVECTOR ang; // 0x54
    uint8 pad_5C[0x68];
    SVECTOR pos_C4; // only x, y, z used
} VIEW_WORK;

extern SVECTOR D_80097CF4; // zero vector
extern uint8 D_800899E0[][16];
extern PL_SHL_WORK D_800BFB22[]; // D_800BFB20 again, based at id_2 (routine_0 is its id_2)
extern WORK_48 D_800A3B40[];
extern uint32 D_800988C8; // [2] bitmasks, second word is D_800988CC
extern uint32 D_80098838; // [2] bitmasks, second word is D_8009883C
extern uint32 D_8009883C;
extern uint32 D_800988CC;
extern PL_SHL_WORK D_800BFB20[];
extern WORK_50 D_800BF118[];
extern WORK_5A4 D_800C3580[];
extern uint32 D_80098A60;
extern uint32 D_800989F0;
extern uint32 D_80098A4C;
extern uint32 D_800989CC;
extern uint32 D_80098B64;
extern uint32 D_80098B20;
extern EVE_WORK D_800A2D08[];
// The slot each pool's update loop (game.c) is running, one per pool.
extern WORK_3C0 *D_80098820;     // D_8009F108[16] (func_80016FD4)
extern WORK_5A4 *D_800989D0;     // D_800C3580[4] (func_80017094)
extern PL_SHL_WORK *D_800988F8;  // D_800BFB20[16] (func_80017154), D_8009CF88[32] (func_80017210)
extern WORK_48 *D_800988E4;      // D_800A3B40[64] (func_800172F4, func_800173B4)
extern WORK48_FUNC D_80089858[]; // D_800A3B40's handlers for ids 0x80 and up (func_800173B4)
extern EVE_WORK *D_800988F0;     // D_800A2D08[16] (eve_work_exec)
extern WORK_50 *D_80098924;      // D_800BF118[32] (func_80017528)
extern WORK_3C0 D_8009F108[];
extern SHL_WORK D_8009CF88[];
extern uint32 D_80098818;
extern uint32 D_800987EC;
extern uint32 D_8009880C;
extern uint32 D_800987E8;
extern uint32 D_80098808;
extern uint32 D_800987CC;
extern uint8 D_800BC818;
extern uint8 D_800BC819;
extern uint8 D_800BC81A;
extern uint16 D_800BC81C;
extern FOG_BLOCK D_8009A350;
extern FOG_BLOCK D_800BC7F8;
extern FOG_BLOCK D_800C0DC0;
// The halfword at D_800C0DC0 + 0x26, read as its own symbol: func_80023728 copies it to the map
// draw mode, D_1F800075.
extern uint16 D_800C0DE6;
extern uint8 D_800BADB0[0x20];
extern uint32 D_800988E0;
extern SLOT_REQ D_800A2F48[];
extern uint8 D_80089A8B[]; // byte 7 of the 12-byte records of D_80089A84 (PL_ACT_ENT.id_7)
extern uint32 D_800A32E0[];
extern uint32 D_80098798;
// The shot holding each slot of D_80098798 (func_8003545C, from pl_shot_spawn): its tgt_BC gets the
// position of the request that owns the slot.
extern PL_SHL_WORK *D_800BE478[];
extern SLOT_ENT D_8009A300[4];
extern TRACK_INFO D_800899AC[];
extern HIT_ENT D_80097D18; // collision box of the SLOT_ENT point (func_80036D40)
// A position as three words (Camera_work.pos_98, which game.c's func_800158F0 moves; r3_st1a's
// header calls it the camera position): func_80036D40 tests its targets' visibility from it.
extern sint32 D_800A39F0;
extern sint32 D_800A39F4;
extern sint32 D_800A39F8;
extern HIT_ENT D_80097D0C;  // collision box of the TRACK_WORK point (func_800364B0)
extern MATRIX D_800BC728[]; // matrix stack; D_80098A80 starts at its end (func_800333A0)
extern uint32 D_8009888C;   // bit 0x80000000 >> n set when player n is spawned (Obj_spawn_tbl_set)
extern LOCK_BOX D_8008994C[];
// The object the player is locked on to, or 0: func_800358F0's answer each frame (Hit_check_all);
// func_8003EEC0 turns the player toward its pos.
extern MODEL_WORK *D_80097D08;

SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 angle, sint32 limit);
void Work_pools_init(sint32 players);
void Hit_check_all(void);
void Model_work_init(MODEL_WORK *wp, uint8 *sub);
void func_80030150(VECTOR *src, SVECTOR *dst);
void func_800301A8(MATRIX *m, VECTOR *pos, VECTOR *origin); // rotates pos by m around origin
long Distance_xz(SVECTOR *a, SVECTOR *b);
sint32 Angle_xz_svector(SVECTOR *from, SVECTOR *to);
sint32 func_80031268(SVECTOR *from, SVECTOR *to); // XZ angle from from to to
sint32 func_8003129C(SVECTOR *a, SVECTOR *b);     // pitch angle from a to b
void func_80031988(WORK_48 *wp);
void func_800320B8(struct PL_WORK *wp, uint32 set, sint32 idx);
void func_800321C8(struct PL_WORK *wp, sint32 unused, uint32 set, sint32 idx);
void func_800323FC(struct PL_WORK *wp, sint32 a); // steps the keyframe table; a: pose_mix
WORK_48 *func_80031618(void);                     // claims a free slot of D_800A3B40, or 0
void Close_PL_SHL_WORK(PL_SHL_WORK *wp);          // frees a slot of D_800BFB20
void func_80031824(WORK_3C0 *wp);                 // frees a slot of D_8009F108
WORK_3C0 *func_80031418(void);                    // claims a free slot of D_8009F108, or 0
WORK_5A4 *func_80031498(void);                    // claims a free slot of D_800C3580, or 0
SHL_WORK *Open_SHL_WORK(void);                    // claims a free slot of D_8009CF88, or 0
EVE_WORK *Open_EVE_WORK(void);                    // claims a free slot of D_800A2D08, or 0
WORK_50 *func_80031734(void);                     // claims a free slot of D_800BF118, or 0
void func_8003187C(WORK_5A4 *wp);                 // frees a slot of D_800C3580
void Close_SHL_WORK(SHL_WORK *wp);                // frees a slot of D_8009CF88
void Close_EVE_WORK(EVE_WORK *wp);                // frees a slot of D_800A2D08
void func_80031A4C(WORK_50 *wp);                  // frees a slot of D_800BF118
void func_80031AA4(void);                         // called every frame by code_800133D8's func_80013420
void func_8002FBF4(void);                         // closes the objects whose model lies in the stage's first EBD file
void func_80033EBC(void);
// Every live slot of the pools picked in flag moves by d (when given) if its flags bit 5 is set,
// else closes.
void func_8002F420(sint32 flag, SVECTOR *d);
void func_8002F884(MODEL_WORK *wp, SVECTOR *d); // moves pos, pos_l, old, old_l by d (x, z)
void func_8002F928(WORK_48 *wp, SVECTOR *d);    // moves the EFC position by d (x, z)
void func_8002F998(EVE_WORK *wp, SVECTOR *d);   // moves pos by d (x, z)
void Obj_pos_set(MODEL_WORK *wp, sint16 x, sint16 y, sint16 z);
void func_800322A8(MODEL_WORK *wp, sint32 seq, sint32 step); // starts keyframe sequence seq
void func_80032488(MODEL_WORK *wp);                          // steps the keyframe sequence
void Obj_launch_set(MODEL_WORK *wp, VIEW_WORK *to, sint16 speed, sint16 max, sint16 grav);
void func_80030934(MODEL_WORK *wp, VIEW_WORK *to, sint16 speed, sint16 max);
void func_8003234C(struct PL_WORK *wp);
uint32 func_80037440(void);
void Pl_joint_mtx_set(struct PL_WORK *wp);
void Pl_pose_unpack(struct PL_WORK *wp);
void Model_parts_mtx_set(MODEL_WORK *wp, MATRIX *m);
void Model_parts_mtx_set_y(MODEL_WORK *wp);
void Model_parts_mtx_set_yxz(MODEL_WORK *wp);
// mask: pool bits (1 Player_work, 2 D_8009F108, ...); flag WORK_KILL closes every live slot.
void Obj_work_flag_change(sint32 mask, sint32 flag);
void *func_80036294(uint32 id); // object of an id byte (kind | index), or 0
// Steps tracker t of object wp (facing angle); 1 while it holds the player.
sint32 func_800364B0(TRACK_WORK *t, MODEL_WORK *wp, sint32 angle);
void func_800354E0(uint32 n); // releases slot n of D_80098798 (claimed by func_8003545C)
uint32 func_8002FE74(uint32 a);
void func_8003697C(void); // Scratch_scale_shift = 0, with its fog distances
void func_800369C0(void); // Scratch_scale_shift = 1, with its fog distances
void func_80036A1C(void); // Scratch_scale_shift = 2, with its fog distances
// Loads a scene block (0x20 bytes of src into D_800BADB0) and a fog block into the fog copies.
void func_800371A0(void *src, FOG_BLOCK *fog);
sint32 func_800341BC(SVECTOR *v, uint32 a1, uint32 a2, uint32 a3, uint32 a4, SLOT_OWNER *owner, uint32 a6, uint32 a7, uint32 a8);
sint32 func_8003430C(SVECTOR *va, uint32 pad_a, SVECTOR *vb, uint32 pad_b, uint32 a4, uint32 a5, uint32 a6, SLOT_OWNER *owner, uint32 val,
                     uint32 a9, uint32 a10);
void Obj_player_dist_set(void); // per frame (game's game_frame_exec)
// Called from the overlays.
void Obj_spawn_tbl_set(SPAWN_ENT *e, sint32 players);
void func_8002F9EC(MODEL_WORK *wp, uint8 *sub);
void func_8002FA10(MODEL_WORK *wp, uint8 *sub);
void func_8002FF34(struct PL_WORK *wp, sint16 x, sint16 y, sint16 z); // moves pos_428 along ang.vy
void func_8002FFC4(SVECTOR *dst, VECTOR *pos, sint32 angle, sint16 x, sint16 y, sint16 z);
VECTOR *func_80030058(VECTOR *out, sint32 angle, sint16 x, sint16 y, sint16 z);
long Obj_distance_xyz(MODEL_WORK *a, MODEL_WORK *b);
long Distance_xyz(SVECTOR *a, SVECTOR *b);
sint32 Dist_xz_sq(SVECTOR *from, SVECTOR *to);
uint32 func_80030418(VIEW_WORK *from, VIEW_WORK *to, sint16 *shift, VECTOR *out);
uint32 func_80030604(MODEL_WORK *from, MODEL_WORK *to, sint16 *shift, VECTOR *out);
uint32 func_80030628(MODEL_WORK *from, MODEL_WORK *to, sint16 *shift, VECTOR *out, sint16 angle);
sint16 func_80030D30(SVECTOR *from, SVECTOR *to, sint16 height, sint16 max_dist, sint16 arc);
void func_80030EE8(MODEL_WORK *wp, SVECTOR *target, sint16 speed);
sint32 Angle_xz_vector(VECTOR *from, VECTOR *to);
PL_SHL_WORK *Open_PL_SHL_WORK(void); // claims a free slot of D_800BFB20, or 0
WORK_50 *func_800317AC(sint32 i);
sint16 Muku(SVECTOR *pos, SVECTOR *target, sint32 rot, sint32 speed);
sint16 func_80031CA4(SVECTOR *pos, SVECTOR *target, sint32 rot, sint32 speed);
sint16 Angle_diff_clamp(sint16 a, sint16 b, sint16 limit);
sint32 func_80031DCC(VECTOR *from, sint32 center1, sint32 half1, VECTOR *to, sint32 center2, sint32 half2);
sint32 func_80031E60(VECTOR *from, sint32 center1, sint32 half1, VECTOR *to, sint32 center2, sint32 half2);
sint32 func_80031EF0(SVECTOR *from, sint32 center1, sint32 half1, SVECTOR *to, sint32 center2, sint32 half2);
sint32 func_80031F84(SVECTOR *from, SVECTOR *to, sint16 base, uint16 mode);
void func_80032304(MODEL_WORK *wp, sint32 idx, sint32 step);
void func_80032538(MODEL_WORK *wp);
void func_80033500(WORK_5A4 *wp);
void func_8003354C(WORK_3C0 *wp);
void Model_pose_unpack(MODEL_WORK *wp);
void Track_stop(TRACK_WORK *t);
void Track_reset(TRACK_WORK *t, uint8 kind, uint32 height);
sint32 func_8003648C(TRACK_WORK *t, MODEL_WORK *wp);
void func_80036A88(sint32 r, sint32 g, sint32 b, sint32 n);
void Fog_param_get(sint16 *out);

#endif // CODE_8002E7A8_H
