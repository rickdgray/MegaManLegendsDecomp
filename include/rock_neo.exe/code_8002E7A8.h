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

// Obj_work_flag_change's flag: close the slots (Capcom's name, from eve19.c).
#define WORK_KILL 0x80

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
// whole object: PL_WORK.owner_188, SHL_WORK.owner_C4, D_800986D8, and the owner stored in each
// SLOT_REQ.
typedef struct
{
    uint32 pad_0;
    uint32 mask_4;
} SLOT_OWNER;

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint16 field_2;
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

typedef struct
{
    uint8 r, g, b, pad;
} RGB_ENT;

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

// Per-part 0x20-byte block (WORK_5A4.blk_240), copied whole into a detached part (func_80031324).
typedef struct
{
    uint32 w[8];
} CHILD_BLK;

// Per-part entries of a model object (WORK_5A4.slot_F8/pos_180).
typedef struct
{
    uint8 pad_0;
    sint8 child_id;
    uint8 pad_2;
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
    uint8 field_2; // field_2 and field_3 are cleared together by one halfword store (on open)
    uint8 field_3; // func_80015428: index of the object (0..15)
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8; // routine_8 to timer_B are cleared by one word store (on open)
    uint8 field_9;   // set (with field_A cleared) by the event steps of code_800680BC
    uint8 field_A;
    uint8 timer_B;
    sint8 field_C; // field_C to timer_F are cleared by one word store (on open)
    sint8 slot_D;  // nonzero: play the sound of field_E (func_800150E0)
    sint8 field_E; // sound: 0-2 repeat every timer_F frames, 3-4 play once
    sint8 timer_F; // frames to the next repeat of the sound
    uint32 field_10;
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
    SVECTOR vec_158; // moved by script.add_A/C/E each frame (func_800150E0)
    uint8 pad_160[0x1E8];
    SCRIPT_WORK script; // 0x348: command script run by script_exec
    uint8 pad_360[0x28];
    RGB_ENT base;    // 0x388
    RGB_ENT tbl[13]; // 0x38C
} WORK_3C0;          // 0x3C0 bytes

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 field_2; // field_2 and flag_3 are cleared together by one halfword store
    uint8 flag_3;  // selects the sound id in func_80046848
    uint8 flag_4;  // index into the dispatch tables of func_800485E4
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint8 routine_8;
    uint8 field_9;
    uint8 field_A;
    uint8 timer_B; // counts down; routine_8 advances when it reaches 0
    union
    {
        uint32 word;
        sint16 angle; // Y rotation of the matrix at 0x18 (func_800469A4)
        sint16 hw[2]; // hw[1] (0xE) is the X rotation (func_80045AB4)
        struct
        {
            sint8 b0;
            sint8 idx;   // index into the 6-byte records of D_8008A730/D_8008A748 (func_80048390)
            uint8 timer; // counts down per record
            uint8 b3;
        } rec;
        struct
        {
            sint8 sound;   // nonzero: func_80043F70 plays sound 0xA1 after the init
            sint8 col;     // column of D_8008A138 (func_80043F70)
            sint8 variant; // index into D_80097DE0 (the model id); nonzero sets bit 7 of routine_0
            uint8 b3;
        } mdl;
        struct
        {
            sint8 b0;
            sint8 size;  // index into D_80097DDC, the size passed to func_800341BC (func_800441CC)
            sint8 mode;  // 0 or 1 selects the func_800341BC call; others make none
            sint8 level; // nonzero in mode 0, flag_3 6: adds 0x20/0x30/0x40 to Player_work's owner
        } hit;
    } field_C;
    uint32 field_10;
    union
    {
        uint32 word; // packed start word of the sprite kinds (0x3D48002E, func_80044AEC)
        uint8 *data; // model data of the EBD entry, set by Model_work_init (kinds 0x80, 0xE0)
    } u_14;
    // 0x18-0x37 depend on the kind. Bit 2 of routine_0 selects which position func_8002F928 moves:
    // set, the kind has a model matrix here and its position in pos_38; clear, pos_1C.
    union
    {
        MATRIX mtx; // rotation and scale (diagonal = pos_38.pad) of the model kinds; the debris
                    // kinds keep their speed in the bytes of t (s.vx_2C..az_36)
        struct
        {
            uint32 field_18;  // packed word (func_80048390, func_80047354)
            uint16 pos_1C[3]; // position (x, y, z), e.g. copied from the player (func_80047EC8)
            uint8 field_22;
            uint8 field_23;
            uint16 field_24;
            uint16 field_26;
            sint16 field_28; // func_80047DD8: eight angles from 0x28 and eight counts from 0x38
            sint16 field_2A;
            sint16 vx_2C; // speed, added to pos_38 each frame (func_80045750)
            sint16 vy_2E;
            sint16 vz_30;
            sint16 ax_32; // acceleration, added to the speed each frame
            sint16 ay_34;
            sint16 az_36;
        } s;
        // The sprite kinds that keep their position in pos_1C (u_14.word is their packed start
        // word; func_80045400, func_8004548C): add is added to spd, and spd to pos_1C, each frame.
        struct
        {
            uint32 field_18;  // packed colour word (s.field_18)
            uint16 pos_1C[3]; // position (s.pos_1C)
            uint8 field_22;
            uint8 field_23;
            uint16 field_24;
            uint16 field_26;
            SVECTOR add; // 0x28: acceleration
            SVECTOR spd; // 0x30: speed
        } spr;
    } u_18;
    SVECTOR pos_38;  // 0x38: position (x, y = height, z); pad: scale of the diagonal of mtx
                     // (func_800469A4). Passed to Sound_call2 as the source.
    uint32 field_40; // packed colour (code in the top byte of some users)
    union
    {
        void *ptr;    // table the object steps through (func_80045CE8)
        sint16 hw[2]; // hw[0] += hw[1] each frame, then added to pos_38.pad (func_800477A0)
    } u_44;
} WORK_48; // 0x48 bytes

typedef void (*WORK48_FUNC)(WORK_48 *wp);

// Capcom's SHL_WORK (their source opens one with `(SHL_WORK *)Open_SHL_WORK()`): a shot. Two pools
// hold them, with the same allocator code: kind 0x60, D_8009CF88[32] (Open_SHL_WORK /
// Close_SHL_WORK; the scene code and the stage overlays), and kind 0x10, D_800BFB20[16]
// (func_80031598 / func_80031930; the player's shots, spawned by func_80035724).
typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint8 field_2; // field_2 and flag_3 are cleared together by one halfword store (on open)
    uint8 flag_3;  // 0x80 while the object holds a slot of D_80098798 (func_80035724)
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
    sint8 field_E; // set to -0x80 by the event step func_80068728
    uint8 pad_F;
    uint32 field_10;
    // 0x14-0x5C: the MODEL_WORK layout (a model kind: Model_work_init binds kinds 0x10 and 0x60).
    SVECTOR pos;  // 0x14: position (x, height, z); pad: set by func_80035724
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position
    SVECTOR old;  // 0x2C: previous position, passed to func_8003430C with pos (func_800435F8)
    VECTOR old_l; // 0x34: 16.16 previous position (moved with pos_l by func_8002F884)
    SVECTOR spd;  // 0x44: speed; added (<< 8) to pos_l each frame by func_80043A8C
    SVECTOR add;  // 0x4C: acceleration
    SVECTOR ang;  // 0x54: rotation; ang.vy is the Y angle (0..0xFFF), set from the scene data
                  // by func_8001E968
    uint8 pad_5C[8];
    uint16 field_64; // low 12 bits: Y angle of the launch direction (func_800437F8)
    uint8 pad_66[0xE];
    sint8 field_74; // MODEL_WORK.field_74; 0x74-0x77 cleared by one word store on open
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24); 0 on open
    sint16 field_7C; // nonzero ends the flight of func_80043A8C
    uint8 pad_7E[2];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    uint32 field_88;   // 0x88: set from D_80097DAC (by Player_work[0].rec[1].idx[0])
    uint32 rgbc_8C;    // 0x8C: code and colour (0x2E808080)
    sint16 x_90;       // 0x90: copy of pos (func_800437F8, func_80043A8C)
    sint16 y_92;
    sint16 z_94;
    uint8 field_96;
    uint8 field_97;
    uint16 field_98; // passed to func_8003430C as both positions' pad (func_80043E78)
    uint16 field_9A; // 0x9A: += 5 each frame by func_80043A8C
    uint8 pad_9C[8];
    SVECTOR dir_A4; // 0xA4: unit direction of flight (func_800437F8), turned toward tgt_BC
    uint8 pad_AC[0x10];
    SVECTOR tgt_BC;      // 0xBC: target position (0 when none); projected and cleared each frame by
                         // func_80035508 while the object holds a slot of D_80098798
    SLOT_OWNER owner_C4; // 0xC4: slot owner passed to func_8003430C
    uint8 pad_CC[0x40];
} SHL_WORK; // 0x10C bytes

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint16 field_2;
    uint8 flag_4;
    uint8 flag_5;
    uint8 flags; // 6: see above
    uint8 pad_7;
    uint32 field_8;
    sint8 field_C; // field_C to pad_F are cleared by one word store (on open)
    sint8 slot_D;
    sint8 field_E; // set to -0x80 by the event step func_80068728
    uint8 pad_F;
    uint32 field_10;
    uint8 pad_14[0x3C];
} WORK_50; // 0x50 bytes

typedef struct
{
    uint8 routine_0;
    uint8 kind_1;
    uint16 field_2;
    uint8 flag_4;
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
    uint32 field_10;
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
    uint8 pad_158[0x28];
    CHILD_POS pos_180[24]; // 0x180
    CHILD_BLK blk_240[24]; // 0x240
    RGB_ENT base;          // 0x540
    RGB_ENT tbl[24];       // 0x544
} WORK_5A4;                // 0x5A4 bytes

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
        uint8 b2;
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
    uint8 pad_4[2];
    uint8 flags; // 6: bits 0-1 changed by func_8002F3A8 (see "Work pool slots" above)
    uint8 pad_7[0xD];
    SVECTOR pos;  // 0x14: position (vx and vz horizontal, vy the height)
    VECTOR pos_l; // 0x1C: 16.16 fixed-point position; pos is its rounded copy (Obj_pos_set)
    SVECTOR old;  // 0x2C: previous position
    VECTOR old_l; // 0x34: previous 16.16 position (moved with pos_l by func_8002F884)
    SVECTOR spd;  // 0x44: speed; pad: frames to the target (func_80030EE8)
    SVECTOR add;  // 0x4C: acceleration
    SVECTOR ang;  // 0x54: rotation; ang.vy is the facing angle (0..0xFFF)
    uint8 pad_5C[0x18];
    sint8 field_74; // read with lb by func_8004B414, passed to func_8004B6AC
    uint8 pad_75[3];
    HIT_ENT *hit_78; // 0x78: collision box (func_80049C24, func_8004B414)
    sint16 field_7C; // cleared by func_80051BAC
    uint8 pad_7E[0xA];
    uint8 *data_88; // 0x88: model data of the EBD entry (func_8002FA38)
    uint8 pad_8C[4];
    KEY_ENT **seq_tbl_90; // keyframe sequences, indexed by idx_AC (func_80032304)
    KEY_ENT *seq_94;      // start of the sequence chosen by idx_AC (func_80032304)
    KEY_ENT *ptr_98;      // current step; b0 indexes the entry of ptr_A0[idx_AC] (func_80033A28)
    sint32 val_9C;
    sint32 *ptr_A0; // table of tables of packed pose data (func_80033A28)
    KEY_CMD cmd_A4; // copy of the current step's command; time counts down
    uint8 pad_A8[4];
    uint8 idx_AC;
    uint8 pad_AD[0x17];
    uint32 field_C4; // top byte nonzero: func_80037694 skips the stage collision
    uint8 pad_C8[0x30];
    uint8 buf_F8[0x18]; // 0x18 bytes of the model data (kinds 0x20 and 0x40, func_8002FA38)
} MODEL_WORK;

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
    CHILD_BLK blk_8C;
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
// func_80030CB8/func_80030CF0 have no callers. The position at 0xC4 rules out SHL_WORK (owner_C4
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
extern SHL_WORK D_800BFB22[]; // D_800BFB20 again, based at field_2 (routine_0 is its field_2)
extern WORK_48 D_800A3B40[];
extern uint32 D_800988C8; // [2] bitmasks, second word is D_800988CC
extern uint32 D_80098838; // [2] bitmasks, second word is D_8009883C
extern uint32 D_8009883C;
extern uint32 D_800988CC;
extern SHL_WORK D_800BFB20[];
extern WORK_50 D_800BF118[];
extern WORK_5A4 D_800C3580[];
extern uint32 D_80098A60;
extern uint32 D_800989F0;
extern uint32 D_80098A4C;
extern uint32 D_800989CC;
extern uint32 D_80098B64;
extern uint32 D_80098B20;
extern EVE_WORK D_800A2D08[];
extern uint8 D_800BBA90[]; // 0x268 bytes, cleared by Work_pools_init
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
extern uint8 D_80089A8B[]; // byte +0xB of 12-byte records
extern uint32 D_800A32E0[];
extern uint32 D_80098798;
extern uint32 D_800BE478[];
extern SLOT_ENT D_8009A300[4];
extern uint8 D_8009A370;
extern uint8 D_8009A371;
extern uint8 D_8009A372;
extern uint16 D_8009A374;
extern MATRIX D_800BC728[]; // matrix stack; D_80098A80 starts at its end (func_800333A0)

SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 angle, sint32 limit);
void Model_work_init(MODEL_WORK *wp, uint8 *sub);
void func_80030150(VECTOR *src, SVECTOR *dst);
void func_80031988(WORK_48 *wp);
void func_800320B8(struct PL_WORK *wp, uint32 set, sint32 idx);
void func_800321C8(struct PL_WORK *wp, sint32 unused, uint32 set, sint32 idx);
WORK_48 *func_80031618(void);     // claims a free slot of D_800A3B40, or 0
void func_80031930(SHL_WORK *wp); // frees a slot of D_800BFB20
void func_80031824(WORK_3C0 *wp); // frees a slot of D_8009F108
WORK_3C0 *func_80031418(void);    // claims a free slot of D_8009F108, or 0
void Obj_pos_set(MODEL_WORK *wp, sint16 x, sint16 y, sint16 z);
void func_800322A8(MODEL_WORK *wp, sint32 seq, sint32 step); // starts keyframe sequence seq
void func_80032488(MODEL_WORK *wp);                          // steps the keyframe sequence
// mask: pool bits (1 Player_work, 2 D_8009F108, ...); flag WORK_KILL closes every live slot.
void Obj_work_flag_change(sint32 mask, sint32 flag);
void *func_80036294(uint32 id); // object of an id byte (kind | index), or 0
void func_800354E0(uint32 n);   // releases slot n of D_80098798 (claimed by func_8003545C)
uint32 func_8002FE74(uint32 a);
sint32 func_800341BC(SVECTOR *v, uint32 a1, uint32 a2, uint32 a3, uint32 a4, SLOT_OWNER *owner, uint32 a6, uint32 a7, uint32 a8);
sint32 func_8003430C(SVECTOR *va, uint32 pad_a, SVECTOR *vb, uint32 pad_b, uint32 a4, uint32 a5, uint32 a6, SLOT_OWNER *owner, uint32 val,
                     uint32 a9, uint32 a10);

#endif // CODE_8002E7A8_H
