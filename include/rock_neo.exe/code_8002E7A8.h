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

// Handler tables of the work pools, kept on the scratchpad (func_800135DC stores Work_3C0_tbl).
// Each pool's update loop (game.c) calls tbl[id_2] (tbl[id_2][flag_4] for the two-level ones)
// for every slot whose routine_0 and flags both have bit 0 set.
#define Work_3C0_tbl (*(WORK3C0_FUNC ***)0x1F800058) // D_8009F108's
#define Work_5A4_tbl (*(WORK5A4_FUNC ***)0x1F80005C) // D_800C3580's
#define Eve_work_tbl (*(EVE_FUNC **)0x1F800068)      // D_800A2D08's
#define Work_50_tbl  (*(WORK50_FUNC **)0x1F80006C)   // D_800BF118's

#define ABS(x) ((x) < 0 ? -(x) : (x))

// Store to a bogus address, done when func_8002FA38 finds no matching entry.
#define Entry_missing_trap (*(sint32 *)0x87654321)

// Collision box passed to func_8004B5CC/func_80048EA4: three (min, max) halfword pairs, each
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
    uint32 field_8;
    uint32 field_C;
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
    uint8 pad_0;
    sint8 child_id;
    uint8 part_2;
    sint8 field_3; // set to -1 or 0 by the event steps (func_80068388, func_8006854C)
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
    uint16 add_A; // 0xA, 0xC, 0xE: added to WORK_3C0.vec_158.vx, vy, vz each frame
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
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    uint8 pad_88[0x24];
    uint8 idx_AC;     // MODEL_WORK.idx_AC: keyframe sequence
    uint8 old_idx_AD; // previous idx_AC: a change restarts the sequence (func_800150E0)
    uint8 pad_AE[0x62];
    uint8 field_110; // set from script.field_13 when it changes
    uint8 pad_111[0x47];
    SVECTOR vec_158; // MODEL_WORK.scale_158; moved by script.add_A/C/E each frame (func_800150E0)
    MATRIX mtx_160;  // 0x160: MODEL_WORK.mtx_160
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
    uint32 code;   // packed start word (0x3D48002E)
    uint32 rgbc;   // 0x04: code and colour (0x2E808080)
    uint16 pos[3]; // 0x08: position (x, y, z)
    uint8 field_E; // 0x0E-0x13: the WORK_48 kinds' field_22..field_26
    uint8 field_F;
    uint16 field_10;
    uint16 field_12;
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
                  // by func_8001E968
    uint8 pad_5C[0x18];
    sint8 field_74; // MODEL_WORK.field_74; 0x74-0x77 cleared by one word store on open
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24); 0 on open
    sint16 field_7C; // MODEL_WORK.field_7C
    uint8 pad_7E[2];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    EFC efc;           // 0x88
    uint8 free[0x54];  // 0xB8: the shot kind's own data
} SHL_WORK;            // 0x10C bytes

// A player's shot: a slot of the pool D_800BFB20[16], kind 0x10 (func_80031598 / func_80031930),
// spawned by func_80035724. Its id_2 is byte 7 of the player's action record (D_80089A8B), and
// handler[id_2] is func_800433C0 or func_800437A8 (code_8004324C). Same layout as SHL_WORK, with
// its sprite EFC and free block written out: the flight direction sits in the EFC's kind bytes,
// the target and slot owner in the free block.
typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 id_2;   // the shot kind; id_2 and type_3 are cleared together by one halfword store
    uint8 type_3; // 0x80 while the object holds a slot of D_80098798 (func_80035724)
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
    SVECTOR pos;  // 0x14: position (x, height, z); pad: set by func_80035724
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
    uint32 field_8;
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
    uint32 dist_80[2];    // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    PARENT_INFO *info_88; // 0x88: model data (func_80031324)
    uint8 pad_8C[0x6C];
    // 24 parts, like tbl (func_80031324 detaches part n into a CHILD_WORK).
    CHILD_SLOT slot_F8[24]; // 0xF8: child_id at +1
    SVECTOR scale_158;      // 0x158: MODEL_WORK.scale_158
    MATRIX mtx_160;         // 0x160: MODEL_WORK.mtx_160
    CHILD_POS pos_180[24];  // 0x180
    MATRIX mtx_240[24];     // 0x240: the parts' matrices (Model_parts_mtx_set); copied into a detached part
    RGB_ENT base;           // 0x540: also the scales of Model_parts_mtx_set (x, y, z in r, g, b; 0x20 = 1)
    RGB_ENT tbl[24];        // 0x544
} WORK_5A4;                 // 0x5A4 bytes

typedef void (*WORK5A4_FUNC)(WORK_5A4 *wp);

// 0x28-byte fog/far-colour block (copied by func_80036B40); far colour RGB at +0x20, near at +0x24.
typedef struct
{
    uint8 b[0x28];
} FOG_BLOCK;

// Four 0x14-byte entries at D_8009A300 (func_800358F0 bases it there; func_80036C50 claims one,
// func_80033EBC frees all): id 0 means free.
typedef struct
{
    uint8 pad_0[6];
    uint8 id_6;
    uint8 pad_7[8];
    sint8 flag_F; // toggled when the entry is taken
    sint32 val_10;
} SLOT_ENT;

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
// The stage collision services (func_80037694, code_80048620's func_80049C24, func_8004B414,
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
    sint8 field_74; // read with lb by func_8004B414, passed to func_8004B6AC
    uint8 pad_75;
    sint8 field_76; // cleared with field_C0 by func_80052644
    uint8 pad_77;
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24, func_8004B414)
    sint16 field_7C; // cleared by func_80051BAC
    uint8 pad_7E[0xA];
    uint8 *data_88; // 0x88: model data of the EBD entry (func_8002FA38)
    uint8 pad_8C[4];
    KEY_ENT **seq_tbl_90; // keyframe sequences, indexed by idx_AC (func_80032304)
    KEY_ENT *seq_94;      // start of the sequence chosen by idx_AC (func_80032304)
    KEY_ENT *ptr_98;      // current step; b0 indexes the entry of ptr_A0[idx_AC] (func_80033A28)
    SVECTOR *ofs_9C;      // offset of each part from its parent, by CHILD_SLOT.part_2 (Model_parts_mtx_set)
    sint32 *ptr_A0;       // table of tables of packed pose data (func_80033A28)
    KEY_CMD cmd_A4;       // copy of the current step's command; time counts down
    uint8 pad_A8[4];
    uint8 idx_AC;
    uint8 pad_AD[0x13];
    sint32 field_C0; // func_80052644 clears it (and field_76) when it equals its key
    uint32 field_C4; // top byte nonzero: func_80037694 skips the stage collision
    uint8 pad_C8[0x30];
    // 0xF8: the part tree; func_8002FA38 copies 0x18 bytes of the model data here (kinds 0x20
    // and 0x40). The count of parts depends on the kind (WORK_5A4: 24).
    CHILD_SLOT slot_F8[24];
    SVECTOR scale_158; // 0x158: scale (0x400 = 1, func_80014AC0), shifted by Scratch_scale_shift
    MATRIX mtx_160;    // 0x160: body matrix, scaled (Model_parts_mtx_set)
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

// Screen box of the lock-on search (D_8008994C, by the special level when Player_work[0].unk170
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

// Queued request (func_800341BC): vector plus packed flags.
typedef struct
{
    SVECTOR v;
    uint32 flags;
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

// Object whose second position (pos_428/svec_438) func_8002FF34 moves along its facing (ang.vy).
// Kept as a view: func_8002FF34 is only called from the overlays ST03, ST03B and ST05, so the object
// is not known. Its fields match PL_WORK's (ang, pos_428, svec_438); MODEL_WORK ends before 0x428.
typedef struct
{
    uint8 pad_0[0x54];
    SVECTOR ang; // 0x54: same as MODEL_WORK.ang
    uint8 pad_5C[0x3CC];
    VECTOR pos_428;
    SVECTOR svec_438;
} TURN_WORK;

// Object with a view direction (ang.vy) and a position at 0xC4 (pos_C4); see func_80030418.
// Kept as a view: func_80030418 is only called from the overlays (ST00, ST03, ...), and
// func_80030CB8/func_80030CF0 have no callers. The position at 0xC4 rules out PL_SHL_WORK (owner_C4
// there) and PL_WORK has nothing known at 0xC4, so the object is not known. 0x54 is MODEL_WORK.ang.
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
extern WORK_3C0 *D_80098820;    // D_8009F108[16] (func_80016FD4)
extern WORK_5A4 *D_800989D0;    // D_800C3580[4] (func_80017094)
extern PL_SHL_WORK *D_800988F8; // D_800BFB20[16] (func_80017154)
extern EVE_WORK *D_800988F0;    // D_800A2D08[16] (eve_work_exec)
extern WORK_50 *D_80098924;     // D_800BF118[32] (func_80017528)
extern uint8 D_800BBA90[];      // 0x268 bytes, cleared by Work_pools_init
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
extern uint8 D_800BADB0[0x20];
extern uint32 D_800988E0;
extern SLOT_REQ D_800A2F48[];
extern uint8 D_80089A8B[]; // byte 7 of the 12-byte records of D_80089A84 (PL_ACT_ENT.id_7)
extern uint32 D_800A32E0[];
extern uint32 D_80098798;
extern uint32 D_800BE478[];
extern SLOT_ENT D_8009A300[4];
extern uint8 D_8009A370;
extern uint8 D_8009A371;
extern uint8 D_8009A372;
extern uint16 D_8009A374;
extern MATRIX D_800BC728[]; // matrix stack; D_80098A80 starts at its end (func_800333A0)
extern uint32 D_8009888C;   // bit 0x80000000 >> n set when player n is spawned (Obj_spawn_tbl_set)
extern LOCK_BOX D_8008994C[];
// The object the player is locked on to, or 0: func_800358F0's answer each frame (func_8003450C);
// func_8003EEC0 turns the player toward its pos.
extern MODEL_WORK *D_80097D08;

SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 angle, sint32 limit);
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
void func_80031930(PL_SHL_WORK *wp);              // frees a slot of D_800BFB20
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
void func_8002F884(MODEL_WORK *wp, SVECTOR *d);   // moves pos, pos_l, old, old_l by d (x, z)
void func_8002F928(WORK_48 *wp, SVECTOR *d);      // moves the EFC position by d (x, z)
void func_8002F998(EVE_WORK *wp, SVECTOR *d);     // moves pos by d (x, z)
void Obj_pos_set(MODEL_WORK *wp, sint16 x, sint16 y, sint16 z);
void func_800322A8(MODEL_WORK *wp, sint32 seq, sint32 step); // starts keyframe sequence seq
void func_80032488(MODEL_WORK *wp);                          // steps the keyframe sequence
void Obj_launch_set(MODEL_WORK *wp, VIEW_WORK *to, sint16 speed, sint16 max, sint16 grav);
void func_80030934(MODEL_WORK *wp, VIEW_WORK *to, sint16 speed, sint16 max);
void func_8003234C(struct PL_WORK *wp);
void Pl_joint_mtx_set(struct PL_WORK *wp);
void Pl_pose_unpack(struct PL_WORK *wp);
void Model_parts_mtx_set(MODEL_WORK *wp, MATRIX *m);
void Model_parts_mtx_set_y(MODEL_WORK *wp);
void Model_parts_mtx_set_yxz(MODEL_WORK *wp);
// mask: pool bits (1 Player_work, 2 D_8009F108, ...); flag WORK_KILL closes every live slot.
void Obj_work_flag_change(sint32 mask, sint32 flag);
void *func_80036294(uint32 id); // object of an id byte (kind | index), or 0
void func_800354E0(uint32 n);   // releases slot n of D_80098798 (claimed by func_8003545C)
uint32 func_8002FE74(uint32 a);
sint32 func_800341BC(SVECTOR *v, uint32 a1, uint32 a2, uint32 a3, uint32 a4, SLOT_OWNER *owner, uint32 a6, uint32 a7, uint32 a8);
sint32 func_8003430C(SVECTOR *va, uint32 pad_a, SVECTOR *vb, uint32 pad_b, uint32 a4, uint32 a5, uint32 a6, SLOT_OWNER *owner, uint32 val,
                     uint32 a9, uint32 a10);

#endif // CODE_8002E7A8_H
