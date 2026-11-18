#ifndef ROCK_NEO_CODE_8002E7A8_H
#define ROCK_NEO_CODE_8002E7A8_H

#include "common.h"
#include "rock_neo.exe/game.h"
#include "rock_neo.exe/gte_inline.h"

// Local views: only the fields these helpers touch.
typedef struct
{
    uint8 reserved00[0x14];
    uint16 x_14;
    uint8 reserved16[2];
    uint16 y_18;
} POS_WORK;

typedef struct
{
    uint8 reserved00[6];
    uint8 byte_6;
    uint8 byte_7;
    uint8 reserved08[7];
    uint8 byte_F;
} BYTE_WORK;

typedef struct
{
    uint8 reserved00[0x56];
    sint16 angle_56;
} ANGLE_WORK;

typedef struct
{
    uint8 flags;
    uint8 reserved01[0x1B];
    uint16 x_1C;
    uint8 reserved1E[2];
    uint16 z_20;
    uint8 reserved22[0x16];
    uint16 x_38;
    uint8 reserved3A[2];
    uint16 z_3C;
} MOVE_WORK;

typedef struct
{
    sint16 x;
    sint16 y;
    sint16 z;
} POS_VEC;

typedef struct
{
    sint16 m[3][3];
    sint16 pad;
    sint32 t[3];
} MATRIX;

typedef struct
{
    sint16 vx, vy, vz, pad;
} SVECTOR;

typedef struct
{
    uint8 flags_00;
    uint8 reserved01[0x8F];
    uint32 **tbl_90;
    uint32 *tbl_94;
    uint32 *ent_98;
    uint8 reserved9C[8];
    uint32 word_A4;
    uint8 reservedA8[4];
    uint8 index_AC;
} ENEMY_WORK;

typedef struct
{
    sint16 x, y, z, w;
} POS_VEC4;

// Header words common to every pool slot, for the allocators that clear them.
typedef struct
{
    sint8 flags_0;
    uint8 reserved01;
    sint16 half_2;
    uint8 routine_4;
    uint8 reserved5;
    uint8 active_6;
    uint8 reserved7;
    sint32 word_8;
    sint32 word_c;
    sint32 word_10;
    uint8 reserved14[0x60];
    sint32 word_74;
    sint32 word_78;
} SLOT_INIT;

// Eight-byte animation script step: the first word is copied into the work area.
typedef struct
{
    union
    {
        uint32 word;
        struct
        {
            uint8 id_0;
            uint8 time_1;
            uint8 reserved2;
            sint8 ctl_3;
        } b;
    } w0;
    sint32 word_4;
} STEP_WORK;

typedef struct
{
    uint8 reserved00[0xF8];
    STEP_WORK *steps_f8;
    STEP_WORK *cur_fc;
    union
    {
        uint32 word;
        struct
        {
            uint8 id_0;
            sint8 timer_1;
            uint8 reserved2[2];
        } b;
    } w100;
    uint8 reserved104[2];
    sint16 half_106;
} STEP_OWNER;

typedef struct
{
    uint8 reserved00[4];
    uint32 mask_4;
} MASK_WORK;

// Fixed-point position record: halfword position at +0x14, 16.16 position at +0x1C.
typedef struct
{
    uint8 reserved00[0x14];
    sint16 pos_14[4];
    sint32 fixed_1c[3];
    uint8 reserved28[0x2E];
    sint16 angle_56;
} FIXED_POS_WORK;

// Same, at +0x428 inside a larger work area.
typedef struct
{
    uint8 reserved00[0x56];
    sint16 angle_56;
    uint8 reserved58[0x428 - 0x58];
    sint32 fixed_428[3];
    uint8 reserved434[4];
    sint16 pos_438[4];
} FIXED_POS_BIG;

typedef struct
{
    uint8 reserved00[0x14];
    uint16 x_14;
    uint16 y_16;
    uint16 z_18;
} DELTA14_WORK;

typedef struct
{
    uint16 x_0;
    uint16 y_2;
    uint16 z_4;
} DELTA0_WORK;

typedef struct
{
    sint32 x;
    sint32 y;
    sint32 z;
} VEC32_WORK;

// VEC32_WORK with its padding word (PsyQ's VECTOR layout)
typedef struct
{
    sint32 x;
    sint32 y;
    sint32 z;
    sint32 pad;
} VEC32_PAD_WORK;

typedef struct
{
    sint16 x;
    sint16 y;
    sint16 z;
} SHORT3_WORK;

// Position kept twice (+0x14 and +0x2C), with 16.16 copies beside each.
typedef struct
{
    uint8 reserved00[0x14];
    uint16 x_14;
    uint8 reserved16[2];
    uint16 y_18;
    uint8 reserved1A[2];
    sint32 fixed_1c;
    uint8 reserved20[4];
    sint32 fixed_24;
    uint8 reserved28[4];
    uint16 x_2c;
    uint8 reserved2E[2];
    uint16 y_30;
    uint8 reserved32[2];
    sint32 fixed_34;
    uint8 reserved38[4];
    sint32 fixed_3c;
} SYNC_POS_WORK;

typedef struct
{
    uint8 reserved00[0x94];
    STEP_WORK *steps_94;
    STEP_WORK *cur_98;
    uint8 reserved9C[8];
    union
    {
        uint32 word;
        struct
        {
            uint8 id_0;
            sint8 timer_1;
            uint8 reserved2[2];
        } b;
    } wa4;
} STEP_OWNER2;

// Spawner views: an owner record that hands out child records.
typedef struct
{
    uint32 w[8];
} BLOCK32_WORK;

typedef struct
{
    uint8 reserved00[0x14];
} ENT14_WORK;

typedef struct
{
    uint8 reserved00[0x70];
    ENT14_WORK *tbl_70;
} LINK70_WORK;

typedef struct
{
    uint8 reserved0;
    sint8 byte_1;
    uint8 reserved2[2];
} SLOT4_WORK;

typedef struct
{
    uint16 x, y, z, pad;
} POS4_WORK;

typedef struct
{
    uint8 reserved00[0x88];
    LINK70_WORK *link_88;
    uint8 reserved8C[0xF8 - 0x8C];
    SLOT4_WORK slots_f8[34];
    POS4_WORK pos_180[24];
    BLOCK32_WORK blocks_240[1];
} SPAWN_OWNER;

typedef struct
{
    uint8 reserved00[0xB];
    uint8 byte_b;
    uint8 reserved0c[8];
    uint16 x_14;
    uint16 y_16;
    uint16 z_18;
    uint8 reserved1a[2];
    sint32 fx_1c;
    sint32 fx_20;
    sint32 fx_24;
    uint8 reserved28[0x60];
    ENT14_WORK *link_88;
    BLOCK32_WORK blk_8c;
    uint16 x_ac;
    uint16 y_ae;
    uint16 z_b0;
    uint8 reservedb2[2];
    uint32 word_b4;
    SPAWN_OWNER *owner_b8;
} SPAWN_CHILD;

// Player slot as the camera helper sees it (stride 0x5F4).
typedef struct
{
    uint8 reserved00[0x14];
    sint16 x_14, y_16, z_18;
    uint8 reserved1A[0x56 - 0x1A];
    uint16 rot_y_56;
    uint8 reserved58[0x116 - 0x58];
    uint16 rot_off_116;
    uint8 reserved118[0x5F4 - 0x118];
} PLAYER_ENT;

// Mover record: position at +0x14, velocity halfwords at +0x44.
typedef struct
{
    uint8 reserved00[0x14];
    sint16 x_14, y_16, z_18;
    uint8 reserved1A[0x44 - 0x1A];
    sint16 vel_x_44, vel_y_46, vel_z_48, vel_w_4a, v4c, v4e, v50;
} MOVER_WORK;

// Effect record handed out by func_80031598.
typedef struct
{
    uint8 flags_0;
    uint8 reserved1;
    uint8 kind_2;
    uint8 flag_3;
    uint8 reserved4[8];
    uint8 value_c;
    sint8 id_d;
    uint8 reservedE[6];
    uint16 x_14, y_16, z_18;
    sint16 half_1a;
    sint32 fx_1c, fx_20, fx_24;
    uint8 reserved28[0x3C];
    uint16 half_64;
} FX35_WORK;

typedef struct
{
    sint16 a, b, c, d;
} ENT8_WORK;

typedef struct
{
    uint8 reserved00;
    uint8 byte_1;
    uint8 reserved02[0x54];
    uint16 rot_56;
    uint8 reserved58[0x170 - 0x58];
    sint8 idx_170;
    sint8 idx_171;
    uint8 reserved172[0x3C8 - 0x172];
    uint16 pos_3c8[3];
    uint8 reserved3CE[0x3E0 - 0x3CE];
    uint16 pos_3e0[3];
    uint8 reserved3E6[0x4F8 - 0x3E6];
    ENT8_WORK ent_4f8[1];
} OWNER35_WORK;

// Positions at +0xC4 and the heading at +0x56, for the view-clip test.
typedef struct
{
    uint8 reserved00[0x56];
    sint16 angle_56;
    uint8 reserved58[0xC4 - 0x58];
    uint16 x_c4, y_c6, z_c8;
} CLIP_WORK;

// Pool slot as the player-distance pass sees it.
typedef struct
{
    uint8 flags_0;
    uint8 reserved01[0x13];
    sint16 x_14;
    uint8 reserved16[2];
    sint16 z_18;
    uint8 reserved1A[0x80 - 0x1A];
    sint32 dist_80[2];
} DIST_SLOT;

#define FOG_MODE (*(uint8 *)0x1F800074)
#define FOG_A    (*(uint16 *)0x1F800006)
#define FOG_B    (*(uint16 *)0x1F800076)

extern uint32 D_80098798;
extern uint32 D_80098818, D_800987EC, D_8009880C, D_800987E8;
extern uint32 D_80098808, D_800987CC, D_80098A60, D_800989F0;
extern uint32 D_80098A4C, D_800989CC, D_80098B64, D_80098B20;
// Two-word masks, indexed as (&D_x)[i]: retail reaches word 0 like a scalar
extern uint32 D_800988C8, D_80098838;
extern uint32 D_800988CC, D_8009883C;
typedef struct
{
    uint8 reserved00[0xBC];
    POS4_WORK pos_bc;
} SPAWN_TARGET;

// Hit-check queue entry: position (read unsigned when copied, signed when averaged), then the
// owner word (id << 24 | owner pointer & 0x7FFFFF).
typedef struct
{
    union
    {
        POS4_WORK u;
        SVECTOR s;
    } pos;
    uint32 word_8;
} QUEUE_ENTRY;

extern SPAWN_TARGET *D_800BE478[];
sint32 func_8003545C(SPAWN_TARGET *value, MASK_WORK *wp);
extern uint32 D_800988E0;
extern uint32 D_800A2F50[];
extern QUEUE_ENTRY D_800A2F48[];
// Entry i's pad halfword read through a halfword view of the queue: the kind tests use this
// form, which makes GCC hoist &D_800A2F48[0].pos.pad into a base register as retail does.
#define QUEUE_PAD(i) (((uint16 *)D_800A2F48)[(i) * 6 + 3])
extern sint32 D_800A32E0[];
// Fog colour and near distance last set by func_80036A88
typedef struct
{
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 pad;
    uint16 near;
} C8002E7A8_FOG;
extern C8002E7A8_FOG D_8009A370;
extern uint16 D_800BC81C;
extern uint8 D_800BC818, D_800BC819, D_800BC81A;

// Saved fog state: unknown alignment makes retail copy it with a runtime check.
typedef struct
{
    uint8 b[0x28];
} FOGSAVE_WORK;

extern FOGSAVE_WORK D_8009A350;

extern void RotMatrixYXZ(SVECTOR *r, MATRIX *m);
extern void RotMatrix(SVECTOR *r, MATRIX *m);
extern sint32 SquareRoot0(sint32 v);
extern void SetFogNear(sint32 a, sint32 b);
extern void SetFarColor(sint32 r, sint32 g, sint32 b);
extern void func_80033A28(void *wp);
extern sint16 func_80030D30(SHORT3_WORK *a, SHORT3_WORK *b, sint16 c, sint16 d, sint16 e);
extern void func_80032304(ENEMY_WORK *wp, sint32 a1, sint32 a2);
extern void func_8003346C(void *wp);

extern sint32 ratan2(sint32 x, sint32 y);
extern uint32 func_80030628(DELTA14_WORK *a, DELTA14_WORK *b, SHORT3_WORK *range, sint32 *out,
                            sint16 angle);
extern void func_80030968(void *wp, void *other, sint16 a2, sint16 a3, sint16 a4);
extern void func_800309E0(SHORT3_WORK *a, SHORT3_WORK *b, SHORT3_WORK *out, sint16 *size, sint16 e,
                          sint16 f, sint16 g);
extern sint32 func_80030CF0(void *a0, sint32 a1, sint16 a2, sint16 a3, sint16 a4);

void func_800358E8(void);
void func_8002F884(SYNC_POS_WORK *wp, uint16 *delta);
void func_8002F928(MOVE_WORK *wp, uint16 *delta);
void func_80031824(GAME_WORK_3C0 *wp);
void Close_EVE_WORK(GAME_WORK_24 *wp);
void func_80036470(BYTE_WORK *wp);
void func_80036A78(sint32 arg);
void func_8002F3A8(BYTE_WORK *wp, uint32 flags);
void func_80036478(BYTE_WORK *wp, uint8 arg1, uint32 arg2);
void func_8002F9EC(void *wp, sint32 arg);
uint32 func_80030604(ANGLE_WORK *wp, sint32 a1, sint32 a2, sint32 a3);
void func_8002F9C4(void *wp, sint32 arg);
void func_8002FA10(void *wp, sint32 arg);
void func_800354E0(sint32 bit);
void func_8002F998(POS_WORK *wp, uint16 *delta);
uint32 func_8002FE74(uint32 val);
sint32 func_80031198(SHORT3_WORK *a, SHORT3_WORK *b);
extern SHORT3_WORK D_80097CF4;
void func_800329D4(void *wp, sint32 arg);
extern void ApplyMatrixLV(MATRIX *m, sint32 *v0, sint32 *v1);
void func_80031324(SPAWN_OWNER *owner, SPAWN_CHILD *child, sint16 index);
void func_80030150(sint32 *in, sint16 *out);
extern void RotMatrixY(sint32 angle, MATRIX *m);
extern void SetRotMatrix(MATRIX *m);
extern void SetTransMatrix(MATRIX *m);
extern sint32 RotTrans(SVECTOR *v0, sint32 *v1, sint32 *flag);
extern void ApplyMatrix(MATRIX *m, SVECTOR *v, sint32 *out);
extern void MulMatrix(MATRIX *m0, MATRIX *m1);
void func_80033D80(MATRIX *src, MATRIX *dst, SVECTOR *rot, SVECTOR *vec);
extern void TransposeMatrix(MATRIX *src, MATRIX *dst);
MATRIX *func_800355F0(MATRIX *out, sint32 index, sint32 angle);
typedef struct
{
    sint32 w[4];
} VEC4_WORK;

sint32 *func_80030058(sint32 *out, sint32 angle, sint16 x, sint16 y, sint16 z);
sint32 func_800310CC(VEC32_WORK *a, VEC32_WORK *b);
extern sint32 catan(sint32 v);
void func_80030934(void *a0, void *a1, sint16 a2, sint16 a3);
sint32 func_80031268(sint16 *a, sint16 *b);
sint16 func_80030CB8(void *a0, sint32 a1, sint16 a2, sint16 a3);

// Pool slot views for the sweep over every slot table.
typedef struct
{
    uint8 reserved00[0x88];
    uint32 link_88;
} LINK88_VIEW;

typedef struct
{
    uint8 reserved00[0x14];
    uint32 link_14;
} LINK14_VIEW;

extern void func_80052528(void *wp);
void func_8002FBF4(void);
void func_8003187C(GAME_WORK_5A4 *wp);
void func_800318D8(GAME_WORK_10C *wp);
void func_80031930(GAME_WORK_10C *wp);
void func_80031988(GAME_WORK_48 *wp);
void func_80031A4C(GAME_WORK_50 *wp);

// Player_work seen as the array of two player slots (stride 0x5F4), tag byte at +1.
typedef struct
{
    uint8 flags_0;
    uint8 id_1;
    uint8 reserved02[0x12];
    SVECTOR pos_14;
    uint8 reserved1C[0x56 - 0x1C];
    uint16 rot_56;
    uint8 reserved58[0x116 - 0x58];
    uint16 rot_116;
    uint8 reserved118[0x170 - 0x118];
    sint8 part_170;
    uint8 reserved171[3];
    uint8 lock_174;
    uint8 reserved175[0x538 - 0x175];
    sint8 zone_538;
    uint8 reserved539[0x5F4 - 0x539];
} PLAYER_TAG_SLOT;

extern PLAYER_TAG_SLOT Player_slots[2] __asm__("Player_work");
extern uint8 D_800BBA90[];
void func_800177CC(void *start, void *end);

// Player as the target-seek helper sees it: heading at +0x56 and +0x116, position at +0x14.
typedef struct
{
    uint8 reserved00[0x14];
    sint16 x_14, y_16, z_18, w_1a;
    uint8 reserved1C[0x56 - 0x1C];
    sint16 rot_56;
    uint8 reserved58[0x116 - 0x58];
    sint16 rot_116;
} SEEK_PLAYER;

// Candidate slot (stride varies by pool): flags at +0, position at +0x14, distance at +0x80.
typedef struct
{
    uint8 flags_0;
    uint8 reserved01[0x13];
    SVECTOR pos_14;
    uint8 reserved1C[0x80 - 0x1C];
    uint32 dist_80;
} SEEK_SLOT;

typedef struct
{
    uint8 reserved00[0x14];
    SVECTOR pos_14;
    uint8 reserved1C[0x3C0 - 0x1C];
} SEEK_SLOT_3C0;

typedef struct
{
    uint8 reserved00[0x14];
    SVECTOR pos_14;
    uint8 reserved1C[0x5A4 - 0x1C];
} SEEK_SLOT_5A4;

extern SEEK_SLOT_3C0 Seek_3c0[16] __asm__("D_8009F108");
extern SEEK_SLOT_5A4 Seek_5a4[4] __asm__("D_800C3580");

extern sint32 rsin(sint32 angle);
extern sint32 rcos(sint32 angle);
extern void VectorNormalS(VEC32_WORK *v, SVECTOR *out);
void *func_80035C90(SEEK_PLAYER *pl, sint32 arc, uint32 max_dist, sint32 min_dot);

// Unsigned-halfword vector: the retail code reads these fields with lhu.
typedef struct
{
    uint16 vx, vy, vz, pad;
} USVECTOR;

// Skeleton owner for the joint pass: position at +0x14, heading at +0x56, matrix at +0x1A8.
typedef struct
{
    uint8 reserved00[0x14];
    sint16 x_14, y_16, z_18;
    uint8 reserved1A[0x56 - 0x1A];
    uint16 rot_56;
    uint8 reserved58[0xB4 - 0x58];
    sint16 spin_b4;
    uint8 reservedB6[0x106 - 0xB6];
    uint16 mode_106;
    uint8 reserved108[0x116 - 0x108];
    uint16 rot_116;
    uint8 reserved118[0x1A8 - 0x118];
    MATRIX mtx_1a8;
    MATRIX mats_1c8[15];
    SVECTOR pos_3a8[15];
    sint16 pos_420[3];
} JOINT_WORK;

extern sint32 D_80097CFC;
#define JOINT_SCR_MTX ((MATRIX *)0x1F8000C0)
#define JOINT_SRC_A   ((SVECTOR *)0x1F800120)
#define JOINT_SRC_B   ((SVECTOR *)0x1F8001A0)

extern SVECTOR *D_800DD600;
// Packed pose banks (12-bit components) at fixed addresses, picked like the script banks.
#define POSE_BANK_DD604 ((uint32 ***)0x800DD604)
#define POSE_BANK_E9600 ((uint32 ***)0x800E9600)
#define POSE_BANK_ED600 ((uint32 ***)0x800ED600)
#define POSE_BANK_EF600 ((uint32 ***)0x800EF600)
#define POSE_BANK_F1600 ((uint32 ***)0x800F1600)
#define POSE_BANK_F3600 ((uint32 ***)0x800F3600)
extern void func_800333A0(void);
extern void func_800333B4(MATRIX *m);
extern void func_8003340C(MATRIX *m);
extern void func_800331A0(JOINT_WORK *wp, sint32 index, void *src, SVECTOR *dst);
void func_800325D4(void *wp);

// Spawn table entry (0x14 bytes, terminated by flags == 0xFF).
typedef struct
{
    uint8 flags_0;
    uint8 kind_1;
    union
    {
        uint16 half;
        struct
        {
            uint8 id_2;
            uint8 byte_3;
        } b;
    } w2;
    uint16 half_4;
    uint8 reserved6;
    uint8 byte_7;
    uint32 word_8;
    sint16 x_c, y_e, z_10, pad_12;
} SPAWN_ENTRY;

// Prefix shared by the player slot (stride 0x5F4) and the pool records the spawner fills.
typedef struct
{
    uint8 flags_0;
    uint8 reserved01;
    uint16 half_2;
    uint16 half_4;
    uint8 reserved06[2];
    uint32 word_8;
    uint32 word_c;
    uint8 reserved10[4];
    SVECTOR pos_14;
    sint32 fx_1c[3];
    sint32 pad_28;
    SVECTOR pos_2c;
    sint32 fx_34[3];
    uint8 reserved40[0x54 - 0x40];
    SVECTOR rot_54;
    SVECTOR rot_5c;
    uint8 reserved64[0x5F4 - 0x64];
} SPAWN_SLOT;

typedef struct
{
    uint8 flags_0;
    uint8 reserved01;
    uint16 half_2;
    uint16 half_4;
    uint8 reserved06[6];
    uint32 word_c;
    uint8 reserved10[0xC];
    uint16 x_1c, y_1e, z_20;
    uint8 reserved22[0x38 - 0x22];
    SVECTOR pos_38;
} SPAWN_FX;

typedef struct
{
    uint8 flags_0;
    uint8 reserved01;
    uint16 half_2;
    uint16 half_4;
    uint8 reserved06[6];
    uint32 word_c;
    uint8 reserved10[4];
    SVECTOR pos_14;
} SPAWN_LINK;

typedef struct
{
    uint8 reserved00[0x50];
    sint16 room_50;
    uint8 reserved52[0x78 - 0x52];
    union
    {
        sint8 flag;
        sint32 word;
    } mark_78;
} SPAWN_GAME_VIEW;

extern SPAWN_GAME_VIEW Spawn_game __asm__("Game_work");
#define SPAWN_GAME Spawn_game

extern uint32 D_8009888C;
void func_8002EA50(SPAWN_ENTRY *e, sint32 spawn_player);

// Skeleton owner for the bone-matrix pass.
typedef struct
{
    uint8 reserved0;
    sint8 parent_1;
    uint8 kind_2;
    uint8 reserved3;
} BONE_REC;

typedef struct
{
    sint32 w[5];
} MROT_WORK;

typedef struct
{
    uint8 reserved00;
    uint8 id_1;
    uint8 reserved02[4];
    uint8 flags_6;
    uint8 reserved07[0x14 - 7];
    sint16 x_14, y_16, z_18;
    uint8 reserved1A[0x9C - 0x1A];
    SVECTOR *tbl_9c;
    uint8 reservedA0[0xF8 - 0xA0];
    BONE_REC bones_f8[1];
    uint8 reservedFC[0x158 - 0xFC];
    sint16 sx_158, sy_15a, sz_15c;
    uint8 reserved15E[2];
    MATRIX mtx_160;
    POS4_WORK pos_180[13];
    MATRIX mats_1e8[2];
    uint8 reserved228[0x240 - 0x228];
    MATRIX mats_240[2];
    uint8 reserved280[0x388 - 0x280];
    uint8 scale_388[0x540 - 0x388];
    uint8 scale_540[4];
} BONE_WORK;

extern void MulMatrix0(MATRIX *m0, MATRIX *m1, MATRIX *out);
extern void ScaleMatrix(MATRIX *m, VEC32_WORK *v);
void func_80033598(BONE_WORK *wp, MATRIX *m);

// Homing-tracker work (func_800364B0): position, velocity, state.
typedef struct
{
    sint16 x, y, z;
    uint8 kind;
    uint8 state;
    SHORT3_WORK vel;
    uint8 timer;
    uint8 height;
} TRACK_WORK;

typedef struct
{
    uint8 start, hold, range, pad;
} TRACK_INFO;

typedef struct
{
    uint8 reserved00[0x14];
    uint16 x_14, y_16, z_18;
    uint8 reserved1A[0x80 - 0x1A];
    uint32 dist_80;
} TRACK_TARGET;

extern TRACK_INFO D_800899AC[];
extern PL_HEIGHT_INFO D_80097D0C;
extern sint32 func_8005EBD4(void);
extern void func_8005D4C0(void);
extern SVECTOR *func_80033F04(SVECTOR *out, SVECTOR *a, SVECTOR *b, sint32 len, uint32 limit);
extern sint32 func_80049C54(void *pos, void *prev, PL_HEIGHT_INFO *info, sint32 kind);
sint32 func_800364B0(TRACK_WORK *t, TRACK_TARGET *tg, sint32 angle);
sint32 func_8003648C(TRACK_WORK *a0, ANGLE_WORK *a1);

// Matrix stack: func_800333A0 resets it, func_800333B4 pushes, func_8003340C pops.
extern MATRIX D_800BC728[];
extern MATRIX *D_80098A80;

extern uint32 D_80098560, D_80098564, D_80098568;

// Animation-set owner: lower-body script at +0x94, upper-body script at +0xF8; the alternate
// table flags at +0x170/+0x171 pick between two script banks.
typedef struct
{
    uint8 reserved00[0x94];
    STEP_WORK *steps_94;
    STEP_WORK *cur_98;
    uint8 reserved9C[4];
    uint32 **tbl_a0;
    uint32 word_a4;
    uint8 reservedA8[4];
    uint8 id_ac;
    uint8 reservedAD[0xF8 - 0xAD];
    STEP_WORK *steps_f8;
    STEP_WORK *cur_fc;
    uint32 word_100;
    uint8 id_104;
    uint8 reserved105[0x170 - 0x105];
    sint8 alt_170;
    sint8 alt_171;
} ANIM_SET_WORK;

// Animation script banks loaded at fixed addresses (literal addresses in retail: lui/addu at).
#define ANIM_BANK_D9D00 ((STEP_WORK **)0x800D9D00)
#define ANIM_BANK_DB800 ((STEP_WORK **)0x800DB800)
#define ANIM_BANK_DC300 ((STEP_WORK **)0x800DC300)
#define ANIM_BANK_DC780 ((STEP_WORK **)0x800DC780)
#define ANIM_BANK_DCB80 ((STEP_WORK **)0x800DCB80)
#define ANIM_BANK_DD000 ((STEP_WORK **)0x800DD000)

// Frame-timing words at fixed addresses (retail builds 0x800D9BE4 with lui/ori).
// Four homing-shot slots at 0x8009A300 (0x14 bytes each), run by func_80036D40.
typedef struct
{
    sint16 x, y, z;
    uint8 kind;
    uint8 state;
    SHORT3_WORK vel;
    uint8 timer;
    sint8 toggle;
    MASK_WORK *target;
} TRACK_SLOT;

extern TRACK_SLOT D_8009A300[4];
void func_80036C50(uint8 kind, MASK_WORK *target);
sint32 func_80036D40(TRACK_SLOT *t);
void *func_80036294(uint8 kind);

// Player as the target pick (func_800358F0) sees it.
typedef struct
{
    uint8 reserved00;
    uint8 side_1;
    uint8 reserved02[0x12];
    SVECTOR pos_14;
} PICK_PLAYER;

// Target record (func_80036294) as the homing slots read it.
typedef struct
{
    sint8 flags_0;
    uint8 id_1;
    uint8 reserved02[4];
    uint8 flags_6;
    uint8 reserved07[0xD];
    SVECTOR pos_14;
    uint8 reserved1C[0x80 - 0x1C];
    uint32 dist_80;
} HOMING_TARGET;

// Lock-on screen windows (func_80034EB8), one per zone.
typedef struct
{
    sint16 z_max;
    sint16 x_min, x_max;
    sint16 y_min, y_max;
    sint16 pad;
} LOCK_WINDOW;

extern LOCK_WINDOW D_8008994C[];
#define LOCK_ABS(x) ((x) < 0 ? -(x) : (x))
// Store SZ3 / 4 (data register 19 through $12) to the word at p
#define LOCK_GTE_STSZ3_4(p)                                                                        \
    __asm__ volatile("mfc2 $12, $19; nop; sra $12, $12, 2; sw $12, 0(%0)"                          \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "memory")
void func_80035508(void);
extern uint8 D_80089A8B[];
void func_80035724(sint32 a0, sint32 a1, OWNER35_WORK *owner, sint32 index, sint32 flag);

extern PL_HEIGHT_INFO D_80097D18;
sint32 func_8003081C(DELTA0_WORK *a, DELTA0_WORK *b, sint16 *shift, sint16 angle);
#define TIME_START (*(sint32 *)0x800D9BE4)
#define TIME_SPLIT (*(sint32 *)0x800D9BF4)
#define TIME_TOTAL (*(sint32 *)0x800D9BF8)

extern sint32 VSync(sint32 mode);
extern uint8 D_80097D00[];
extern sint32 D_80097D08;
extern uint8 D_80097D02, D_80097D03;
void func_80034EB8(void);
sint32 func_800358F0(void *pl);
void func_800346AC(uint32 *pi, uint32 *pj);

// Owner record a queue entry points at (word_8 & 0x7FFFFF): hit flags, then the hit point.
typedef struct
{
    uint32 flags_0;
    uint32 reserved4;
    sint16 x_8, y_a, z_c, w_e;
} HIT_OWNER;

// Resource directory entry (0x10 bytes) searched by func_8002FA38; the directory starts with
// its entry count.
typedef struct
{
    uint8 kind_0;
    uint8 id_1;
    uint8 sub_2;
    uint8 reserved3;
    uint8 *data_4;
    uint32 *tbl_8;
    uint32 word_c;
} RES_ENTRY;

typedef struct
{
    sint32 count;
    RES_ENTRY entries[1];
} RES_DIR;

typedef struct
{
    uint8 reserved00;
    uint8 id_1;
    uint8 sub_2;
    uint8 reserved03[0x11];
    uint8 *data_14;
    uint8 reserved18[0x88 - 0x18];
    uint8 *data_88;
    uint8 reserved8C[4];
    uint32 word_90;
    uint8 reserved94[8];
    uint32 word_9c;
    uint32 *tbl_a0;
    uint8 reservedA4[0xF8 - 0xA4];
    uint8 head_f8[0x18];
} RES_OWNER;

sint32 func_8002FA38(RES_OWNER *wp, sint32 *dir, uint8 *key);

// Hand-written copies inside asm_fastmem.s (0x80017684 words, 0x800176DC 32-byte blocks; not
// in the registry yet)
void func_80017684(void *src, void *dst, sint32 count);
void func_800176DC(void *src, void *dst, sint32 count);
extern uint32 D_800BADB0[];
extern uint8 D_800C0DC0[];
extern FOGSAVE_WORK D_800BC7F8;
#define FOG_FAR_MODE (*(uint8 *)0x1F800078)
#define DEBUG_TRAP   (*(sint32 *)0x87654321)

extern void OuterProduct12(VEC32_PAD_WORK *a, VEC32_PAD_WORK *b, VEC32_PAD_WORK *out);

// Object-slot allocators defined later in code_8002E7A8.c, declared so earlier callers see
// pointer returns (GCC 2.7 accepted the implicit declarations; other compilers don't).
#include "rock_neo.exe/game.h"
GAME_WORK_3C0 *func_80031418(void);
GAME_WORK_5A4 *func_80031498(void);
GAME_WORK_10C *func_80031518(void);
GAME_WORK_24 *func_800316BC(void);
GAME_WORK_50 *func_80031734(void);

#endif
