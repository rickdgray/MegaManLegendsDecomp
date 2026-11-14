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

// Store to a bogus address, done when func_8002FA38 finds no matching entry.
#define Entry_missing_trap (*(sint32 *)0x87654321)

// ---- Work pool slots (Work_pools_init). ----
// Every slot, and PL_WORK, starts with the same header: routine_0, kind_1 (pool kind, 0x10 * pool
// number, ORed with the slot index), and at 6 a flags byte: set to 3 on open, bits 0-1 changed by
// func_8002F3A8, bit 5 keeps the slot alive in func_8002F420 (moved instead of closed), bit 6 set
// by func_80033500/func_8003354C.

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
    sint16 x_14; // position (x, height, z); x and z moved by func_8002F998
    sint16 y_16;
    sint16 z_18;
    uint8 pad_1A[0xA];
} EVE_WORK; // 0x24 bytes

typedef struct
{
    uint8 r, g, b, pad;
} RGB_ENT;

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
    sint16 x_14; // position (x, height, z)
    sint16 y_16;
    sint16 z_18;
    uint8 pad_1A[0x5A];
    uint32 field_74;
    uint32 field_78;
    uint8 pad_7C[4];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    uint8 pad_88[0x300];
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
    } field_C;
    uint32 field_10;
    uint32 field_14;
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
            uint8 pad_26[6]; // func_80047DD8: eight angles from 0x28 and eight counts from 0x38
            sint16 vx_2C;    // speed, added to pos_38 each frame (func_80045750)
            sint16 vy_2E;
            sint16 vz_30;
            sint16 ax_32; // acceleration, added to the speed each frame
            sint16 ay_34;
            sint16 az_36;
        } s;
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
    uint32 field_8;
    uint8 field_C; // field_C to pad_E are cleared by one word store (on open)
    sint8 slot_D;  // slot claimed by func_8003545C
    uint8 pad_E[2];
    uint32 field_10;
    sint16 x_14; // position (x, height, z)
    sint16 y_16;
    sint16 z_18;
    sint16 field_1A;
    sint32 x_1C; // 16.16 fixed-point position
    sint32 y_20;
    sint32 z_24;
    uint8 pad_28[0x3C];
    uint16 field_64;
    uint8 pad_66[0xE];
    uint32 field_74;
    uint32 field_78;
    uint8 pad_7C[4];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    uint8 pad_88[0x84];
} WORK_10C; // 0x10C bytes

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
    uint32 field_8;
    uint32 field_C;
    uint32 field_10;
    sint16 x_14; // position (x, height, z)
    sint16 y_16;
    sint16 z_18;
    uint8 pad_1A[0x5A];
    uint32 field_74;
    uint32 field_78;
    uint8 pad_7C[4];
    uint32 dist_80[2]; // squared distance (<< 2) to each player, -1 when too far (func_8003606C)
    uint8 pad_88[0x4B8];
    RGB_ENT base;    // 0x540
    RGB_ENT tbl[24]; // 0x544
} WORK_5A4;          // 0x5A4 bytes

// 0x28-byte fog/far-colour block (copied by func_80036B40); far colour RGB at +0x20, near at +0x24.
typedef struct
{
    uint8 b[0x28];
} FOG_BLOCK;

// Four 0x14-byte entries at D_8009A306 (func_80036C50): id 0 means free.
typedef struct
{
    uint8 id;
    uint8 pad_1[8];
    sint8 flag; // toggled when the entry is taken
    uint8 pad_A[0xA];
} SLOT_ENT;

typedef struct
{
    sint32 val;
    uint8 pad_4[0x10];
} SLOT_VAL; // the word at +0xA of a SLOT_ENT, seen from D_8009A310

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

// ---- Views of the common object header ----
// The functions below take any object (PL_WORK or a pool slot), so each view covers only the
// fields that one function reads. They can merge once the common header has its own type.

// func_8002F928: called by func_8002F420 on the slots of D_800A3B40 (WORK_48) and D_800BF118
// (WORK_50). Bit 2 of the first byte selects which of two (x, y, z) positions moves.
typedef struct
{
    uint8 flags;
    uint8 pad_1[0x1B];
    uint16 pos_1C[3]; // 0x1C
    uint8 pad_22[0x16];
    uint16 pos_38[3]; // 0x38
} POS_WORK;

// func_8002F3A8: called by Obj_work_flag_change on both players and the slots of every pool;
// flags is the header byte at 6.
typedef struct
{
    uint8 pad_0[6];
    uint8 flags;
} FLAG_WORK;

// func_8002F884: called by func_8002F420 on the slots of D_8009F108 (WORK_3C0), D_800C3580
// (WORK_5A4), D_8009CF88 and D_800BFB20 (WORK_10C). Two position accumulators (16-bit and
// 16.16 fixed), x and z.
typedef struct
{
    uint8 pad_0[0x14];
    uint16 x_14;
    uint16 pad_16;
    uint16 z_18;
    uint16 pad_1A;
    sint32 x_1C;
    uint32 pad_20;
    sint32 z_24;
    uint8 pad_28[4];
    uint16 x_2C;
    uint16 pad_2E;
    uint16 z_30;
    uint16 pad_32;
    sint32 x_34;
    uint32 pad_38;
    sint32 z_3C;
} MOVE_WORK;

// Object holding a bitmask of the slots it owns (see func_8003545C). An embedded block, not a
// whole object: PL_WORK.owner_188, D_800986D8, and the owner stored in each SLOT_REQ.
typedef struct
{
    uint32 pad_0;
    uint32 mask_4;
} SLOT_OWNER;

// Queued request (func_800341BC): vector plus packed flags.
typedef struct
{
    SVECTOR v;
    uint32 flags;
} SLOT_REQ;

// Parent object that owns indexed child slots (see func_80031324). func_80031324 has no callers
// in the code split so far (no jal, no table entry), so the origins of CHILD_PARENT and
// CHILD_WORK are unknown.
typedef struct
{
    uint8 pad_0[0x14];
} ENT_14;

typedef struct
{
    uint8 pad_0[0x70];
    ENT_14 *tbl_70;
} PARENT_INFO;

typedef struct
{
    uint8 pad_0;
    sint8 child_id;
    uint8 pad_2[2];
} CHILD_SLOT;

typedef struct
{
    uint16 x, y, z, pad;
} CHILD_POS;

typedef struct
{
    uint32 w[8];
} CHILD_BLK;

typedef struct
{
    uint8 pad_0[0x88];
    PARENT_INFO *info_88;
    uint8 pad_8C[0x6C];
    CHILD_SLOT slot_F8[0x10]; // child_id at 0xF9
    uint8 pad_138[0x48];
    CHILD_POS pos_180[0x18];
    CHILD_BLK blk_240[0x10];
} CHILD_PARENT;

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
    CHILD_PARENT *parent_B8;
} CHILD_WORK;

// Object moved by a vector rotated about Y by angle_56 (see func_8002FEA4). func_8002FEA4 is called
// on the player (func_80041E90) and on the object of the routine table at 0x80082104
// (func_800150E0, type unknown); the fields match PL_WORK pos, pos_1C, pos_428 and svec_438.
typedef struct
{
    uint8 pad_0[0x14];
    SVECTOR svec_14;
    VECTOR pos_1C; // 0x1C, only x/y/z used
    uint8 pad_2C[0x2A];
    sint16 angle_56;
    uint8 pad_58[0x3D0];
    VECTOR pos_428;
    SVECTOR svec_438;
} TURN_WORK;

// Object with a view direction (angle_56) and a position (x_C4..z_C8); see func_80030418.
// func_80030418, func_80030CB8 and func_80030CF0 have no callers in the code split so far.
typedef struct
{
    uint8 pad_0[0x56];
    sint16 angle_56;
    uint8 pad_58[0x6C];
    uint16 x_C4;
    uint16 y_C6;
    uint16 z_C8;
} VIEW_WORK;

// 16-byte entry of the EBD tables func_8002FA38 searches (Stage_ebd_0, ...).
typedef struct
{
    uint8 kind_0;
    uint8 id_1;
    uint8 sub_2;
    uint8 pad_3;
    uint8 *ptr_4;
    sint32 *ptr_8;
    uint32 val_C;
} ATTACH_ENT;

// Object that func_8002FA38 binds an entry to: any pool slot (the kind selects the fields it
// writes: ptr_14 for WORK_48/WORK_50, ptr_88 and up for the others), and the player
// (func_8003C418 reads cmd_A4 and idx_AC; the keyframe functions take PL_WORK).
typedef struct
{
    uint8 pad_0;
    uint8 kind_1;
    uint8 id_2;
    uint8 pad_3[0x11];
    uint8 *ptr_14;
    uint8 pad_18[0x70];
    uint8 *ptr_88;
    uint8 pad_8C[4];
    uint32 val_90;
    KEY_ENT *seq_94; // start of the sequence chosen by idx_AC (func_80032304)
    KEY_ENT *ptr_98; // current step; b0 indexes the entry of ptr_A0[idx_AC] (func_80033A28)
    sint32 val_9C;
    sint32 *ptr_A0; // table of tables of packed pose data (func_80033A28)
    KEY_CMD cmd_A4; // copy of the current step's command; time counts down
    uint8 pad_A8[4];
    uint8 idx_AC;
    uint8 pad_AD[0x4B];
    uint8 buf_F8[0x18];
} ATTACH_WORK;

// Object with a position at 0x14 (see func_80030628). func_800364B0 passes the player as `to`
// and an unknown object as `from`; func_80030604 and func_80030EE8 have no callers so far.
typedef struct
{
    uint8 pad_0[0x14];
    uint16 x_14;
    uint16 y_16;
    uint16 z_18;
    uint8 pad_1A[0x2A];
    sint16 vx_44;
    sint16 vy_46;
    sint16 vz_48;
    sint16 time_4A;
    sint16 ax_4C;
    sint16 ay_4E;
    sint16 az_50;
} POS14_WORK;

extern SVECTOR D_80097CF4; // zero vector
extern uint8 D_800899E0[][16];
extern WORK_10C D_800BFB22[]; // D_800BFB20 again, based at field_2 (routine_0 is its field_2)
extern WORK_48 D_800A3B40[];
extern uint32 D_800988C8; // [2] bitmasks, second word is D_800988CC
extern uint32 D_80098838; // [2] bitmasks, second word is D_8009883C
extern uint32 D_8009883C;
extern uint32 D_800988CC;
extern WORK_10C D_800BFB20[];
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
extern WORK_10C D_8009CF88[];
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
extern uint8 D_8009A306;
extern SLOT_VAL D_8009A310[]; // word at +0xA of each 0x14-byte entry starting at D_8009A306
extern uint8 D_8009A31A;
extern uint8 D_8009A32E;
extern uint8 D_8009A342;
extern uint8 D_8009A370;
extern uint8 D_8009A371;
extern uint8 D_8009A372;
extern uint16 D_8009A374;
extern MATRIX D_800BC728[]; // matrix stack; D_80098A80 starts at its end (func_800333A0)

SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 angle, sint32 limit);
void Model_work_init(ATTACH_WORK *wp, uint8 *sub);
void func_80030150(VECTOR *src, SVECTOR *dst);
void func_80031988(WORK_48 *wp);
WORK_48 *func_80031618(void); // claims a free slot of D_800A3B40, or 0
uint32 func_8002FE74(uint32 a);
sint32 func_800341BC(SVECTOR *v, uint32 a1, uint32 a2, uint32 a3, uint32 a4, SLOT_OWNER *owner, uint32 a6, uint32 a7, uint32 a8);

#endif // CODE_8002E7A8_H
