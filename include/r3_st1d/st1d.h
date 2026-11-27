#ifndef ST1D_H
#define ST1D_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"
#include "stage_common/stcom16.h"

// A view of the work slots r3_st1d's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
// A spark point (func_80102B54): the joint it starts from and its offset.
typedef struct
{
    uint8 joint_0;          // 00
    uint8 reserved01;       // 01
    STCOM_SVECTOR offset_2; // 02
} ST1D_SPARK_POINT;

// A hit result of func_800341BC: damage in the low 24 bits, kind bits above.
typedef struct
{
    uint32 hit;
    uint32 value_4;
} ST1D_HIT;

// The block at +0x3E0 of the object that throws sparks (func_80102B54).
typedef struct
{
    STCOM_FIXED_VECTOR pos_0; // 00: pos_10 in 16.16
    STCOM_SVECTOR pos_10;     // 10: a hit box's center
    ST1D_HIT hit_18[4];       // 18
    STCOM_SVECTOR offset_38;  // 38
    uint8 reserved40[6];      // 40
    sint16 turn_46;           // 46: the view's value_426
    sint16 angle_48;          // 48: the view's value_428
    uint8 reserved4A[2];      // 4A
    sint16 timer_4C;          // 4C
    sint16 count_4E;          // 4E
    sint16 timer_50;          // 50: the view's value_430
    union
    {
        uint16 h;        // a new random number every frame (the view's value_432)
        uint8 b;         // the spark point, and the spark's look in the low two bits
    } rand_52;           // 52
    uint8 reserved54[4]; // 54
    uint8 node_58;       // 58: the view's value_438, an index into D_80114AB0
    uint8 child_59;      // 59: the view's value_439
    uint8 partner_5A;    // 5A: the view's value_43A
    uint8 routine_5B;    // 5B: the view's value_43B
    uint8 limit_5C;      // 5C
} ST1D_SPARK;

// The spark block at +0x308 of the second object that throws sparks (func_8010B77C).
typedef struct
{
    uint8 reserved00[0x38];  // 00
    STCOM_SVECTOR offset_38; // 38
    uint8 reserved40[6];     // 40
    uint8 value_46;          // 46: the spark point, and the spark's look in the low two bits
    uint8 reserved47;        // 47
    sint8 timer_48;          // 48
} ST1D_SPARK2;

// A spark of a stunned object (D_80114DF0, by stun.timer_5): the joint and the look.
typedef struct
{
    uint8 joint_0;
    uint8 look_1;
} ST1D_STUN_SPARK;

// The control block at +0x348 of the turning enemy (func_8010B988; the view's ext from +0x20).
typedef struct
{
    STCOM_SVECTOR pos_0;  // 348
    sint32 hit_8;         // 350
    sint32 value_C;       // 354
    uint8 reserved10[8];  // 358
    uint8 track_18[0x48]; // 360
    sint32 ground_60;     // 3A8: Obj_map_push_out's result
    sint16 angle_64;      // 3AC: the rotation.y to turn back to
    uint16 value_66;      // 3AE: damage taken since the last stun
    uint8 reserved68[2];  // 3B0
    uint16 rand_6A;       // 3B2
    uint8 flags_6C;       // 3B4
} ST1D_CTL;

// The view's control block at +0x348.
#define ST1D_CTL_OF(wp) ((ST1D_CTL *)((uint8 *)&(wp)->ext + 0x20))

// A camera request per room (D_80115258, func_80111C1C): copied to D_800C3560..D_800C356F.
typedef struct
{
    sint16 x_0;     // 0
    sint16 y_2;     // 2
    sint16 z_4;     // 4
    sint16 value_6; // 6: to D_800C356A
    uint8 value_8;  // 8: to D_800C356F
    uint8 reserved9;
} ST1D_CAM_REQ;

// The panels func_80111D78 spawns on every cell whose attribute is key_0 or type_4: records 0 and
// 2 for the first pair, 1 and 3 for the second.
typedef struct
{
    uint32 key_0;  // 00
    uint32 type_4; // 04
    sint16 x_8;    // 08
    sint16 y_A;    // 0A
    sint16 z_C;    // 0C
    sint8 dir_E;   // 0E
    uint8 value_F; // 0F
} ST1D_PANEL_SPAWN;

// The rooms that have them: stage 0xFF ends the table.
typedef struct
{
    uint8 stage;
    uint8 room;
    uint8 reserved2[2];
    ST1D_PANEL_SPAWN *list;
} ST1D_PANEL_ROOM;

// The control block at +0x308 of an arm (D_80114D50's routines; ST1D_SPARK2 views it too).
typedef struct
{
    STCOM_FIXED_VECTOR pos_0; // 308: pos_10 in 16.16
    STCOM_SVECTOR pos_10;     // 318: a hit box's center
    ST1D_HIT hit_18[4];       // 320
    STCOM_SVECTOR offset_38;  // 340
    uint8 reserved40[2];      // 348
    uint16 value_42;          // 34A
    uint8 reserved44[2];      // 34C
    uint16 rand_46;           // 34E
    sint8 timer_48;           // 350
    uint8 reserved49[0x6F];   // 351
} ST1D_ARM_CTL;

// A 0x3C0-byte arm of an object (D_80114D50's routines): placed by its owner's bone matrices.
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03: the bone it hangs from
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 parent_C;                         // 0C: the object it belongs to
    sint8 owner_D;                          // 0D: the object whose bones place it
    uint8 flags_E;                          // 0E
    uint8 value_F;                          // 0F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[3];                    // 70
    sint8 power_73;                         // 73
    uint8 reserved74[4];                    // 74
    sint32 value_78;                        // 78
    uint8 reserved7C[0x30];                 // 7C
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158
    STCOM_MATRIX matrix_160;                // 160
    STCOM_SVECTOR joints_180[0x11];         // 180
    uint8 reserved208[0x100];               // 208
    ST1D_ARM_CTL ctl;                       // 308
} ST1D_ARM;

typedef void (*ST1D_ARM_FUNC)(ST1D_ARM *wp);

// Starts an animation unless it is already running.
#define ST1D_ARM_ANIM(wp, n)                                                                                                               \
    do                                                                                                                                     \
    {                                                                                                                                      \
        (wp)->anim_AC = (n);                                                                                                               \
        if ((wp)->anim_prev_AD != (n))                                                                                                     \
        {                                                                                                                                  \
            (wp)->anim_prev_AD = (n);                                                                                                      \
            func_80032304((wp), (wp)->anim_AC, 0);                                                                                         \
        }                                                                                                                                  \
    } while (0)

// The objects an arm reaches through func_80036294: their bone matrices from +0x208.
typedef struct
{
    sint8 be_flag;              // 00
    uint8 slot;                 // 01
    uint8 reserved02[10];       // 02
    sint8 flags_C;              // 0C
    sint8 arm_D;                // 0D
    sint8 arm_E;                // 0E
    sint8 timer_F;              // 0F
    uint8 reserved10[0x5E];     // 10
    sint16 life_6E;             // 6E
    uint8 reserved70[0x42];     // 70
    sint16 life_prev_B2;        // B2
    uint8 reservedB4[0x154];    // B4
    STCOM_MATRIX matrix_208[8]; // 208
} ST1D_ARM_OWNER;

// An owner's bone matrix (retail adds the index to the base before the field offset).
#define ST1D_BONE_MATRIX(owner, i) ((STCOM_MATRIX *)((uint8 *)(owner) + ((i) << 5) + 0x208))

// The timers at +0x1D8 of the turning enemy (func_8010C070; STCOM16_STUN's place in stcom16).
typedef struct
{
    sint16 timer_0; // 1D8
    sint16 count_2; // 1DA: shots left
    sint8 delay_4;  // 1DC: frames to the next shot
    uint8 value_5;  // 1DD
    uint8 index_6;  // 1DE: the next shot's direction (0..15)
} ST1D_SHOT;

// The 0x10C-byte shot func_8010C9AC fires (Open_SHL_WORK).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 slot;                        // 01
    uint8 id;                          // 02
    uint8 type;                        // 03
    uint8 value_4;                     // 04
    uint8 reserved05[0xA];             // 05
    sint8 type_F;                      // 0F: 0x10 or 9
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0xE0];            // 2C
} ST1D_SHOT_OBJ;

// An object func_80107AF0 spawns: copied into a new 0x3C0 slot (D_80113FC0, by the spawner's
// value_C).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 value_4;          // 04
    uint8 value_5;          // 05
    uint8 reserved06;       // 06
    uint8 rotation_7;       // 07: rotation.y / 16
    sint32 value_8;         // 08: to the slot's +0xC
    STCOM_SVECTOR position; // 0C
} ST1D_SPAWN_REC;

typedef struct ST1D_VIEW ST1D_VIEW;

typedef void (*ST1D_VIEW_FUNC)(ST1D_VIEW *wp);
struct ST1D_VIEW
{
    sint8 be_flag;                          // 0
    uint8 slot;                             // 1
    uint8 id;                               // 2
    uint8 type;                             // 3
    uint8 value_4;                          // 4
    uint8 reserved5[0x3];                   // 5
    uint8 routine_0;                        // 8
    uint8 routine_1;                        // 9
    uint8 routine_2;                        // A
    uint8 routine_3;                        // B
    sint8 value_C;                          // C
    sint8 value_D;                          // D
    sint8 value_E;                          // E
    sint8 value_F;                          // F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    union
    {
        sint16 h[2];
        uint16 uh[2];
        sint32 w[1];
    } u_44; // 44
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_48;                      // 48
    uint8 reserved4C[0x2];       // 4C
    uint16 value_4E;             // 4E
    uint8 reserved50[0x4];       // 50
    STCOM_SVECTOR rotation;      // 54
    STCOM_SVECTOR rotation_prev; // 5C
    union
    {
        sint8 b[4];
        sint16 h[2];
        sint32 w[1];
    } u_64;                // 64
    uint8 reserved68[0x6]; // 68
    sint16 value_6E;       // 6E
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_70; // 70
    union
    {
        uint8 b[4];
        sint32 w[1];
    } u_74;                 // 74
    uint8 *data_78;         // 78
    uint8 reserved7C[0x4];  // 7C
    sint32 value_80;        // 80
    uint8 reserved84[0x20]; // 84
    uint8 value_A4;         // A4
    uint8 reservedA5[0x1];  // A5
    sint8 value_A6;         // A6
    sint8 value_A7;         // A7
    uint8 reservedA8[0x4];  // A8
    uint8 value_AC;         // AC
    uint8 value_AD;         // AD
    uint8 reservedAE[0x2];  // AE
    sint16 value_B0;        // B0
    sint16 value_B2;        // B2
    uint8 reservedB4[0x10]; // B4
    sint32 value_C4;        // C4
    sint16 value_C8;        // C8
    uint8 value_CA;         // CA
    uint8 value_CB;         // CB
    uint8 reservedCC[0x2F]; // CC
    sint8 value_FB;         // FB
    uint8 reservedFC[0x5C]; // FC
    sint32 value_158;       // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    sint32 value_160;         // 160
    sint32 value_164;         // 164
    sint32 value_168;         // 168
    sint32 value_16C;         // 16C
    sint32 value_170;         // 170
    sint32 value_174;         // 174
    sint32 value_178;         // 178
    sint32 value_17C;         // 17C
    STCOM_SVECTOR vec_180[3]; // 180: joint positions
    uint8 reserved198[0x8];   // 198
    uint16 value_1A0;         // 1A0
    uint16 value_1A2;         // 1A2
    uint16 value_1A4;         // 1A4
    uint8 reserved1A6[0x12];  // 1A6
    uint16 value_1B8;         // 1B8
    uint16 value_1BA;         // 1BA
    uint16 value_1BC;         // 1BC
    uint8 reserved1BE[0x1A];  // 1BE
    sint16 value_1D8;         // 1D8
    uint8 reserved1DA[0x2];   // 1DA
    sint8 value_1DC;          // 1DC
    uint8 value_1DD;          // 1DD
    uint8 value_1DE;          // 1DE
    uint8 reserved1DF[0x1];   // 1DF
    uint16 value_1E0;         // 1E0
    uint16 value_1E2;         // 1E2
    uint16 value_1E4;         // 1E4
    uint8 reserved1E6[0x13A]; // 1E6
    sint32 value_320;         // 320
    uint8 reserved324[0x4];   // 324
    STAGE_ACTOR_EXT ext;      // 328
    uint8 reserved3C0[0x38];  // 3C0
    sint32 value_3F8;         // 3F8
    uint8 reserved3FC[0x4];   // 3FC
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_400;                  // 400
    uint8 reserved404[0x4];   // 404
    sint32 value_408;         // 408
    uint8 reserved40C[0x4];   // 40C
    sint32 value_410;         // 410
    uint8 reserved414[0xC];   // 414
    uint16 value_420;         // 420
    sint16 value_422;         // 422
    uint16 value_424;         // 424
    uint16 value_426;         // 426
    sint16 value_428;         // 428
    sint16 value_42A;         // 42A
    sint16 value_42C;         // 42C
    sint16 value_42E;         // 42E
    sint16 value_430;         // 430
    sint16 value_432;         // 432
    uint16 value_434;         // 434
    uint8 reserved436[0x2];   // 436
    uint8 value_438;          // 438
    uint8 value_439;          // 439
    uint8 value_43A;          // 43A
    uint8 value_43B;          // 43B
    uint8 value_43C;          // 43C
    uint8 reserved43D[0x167]; // 43D
};

// A 10-byte record of a position table (x, z, then three values).
typedef struct
{
    sint16 x;       // 0
    sint16 z;       // 2
    uint16 value_4; // 4
    uint16 value_6; // 6
    uint8 value_8;  // 8
    uint8 value_9;  // 9
} ST1D_POS_REC;

extern STAGE_SLOT_FUNC *D_801140A4[];
extern STAGE_SLOT_FUNC *D_80114244[];
extern STAGE_SLOT_FUNC D_801142A4[];
extern STAGE_SLOT_FUNC D_801142CC[];
extern STAGE_SLOT_FUNC D_8011430C[];
extern STAGE_SLOT_FUNC D_80114394[];
extern STAGE_ROOM2_FUNC *D_80114A28[];
extern STAGE_OBJ_FUNC D_80114A80[];
extern STAGE_OBJ_FUNC D_80115584[];
extern STAGE_OBJ_FUNC D_8011558C[];
extern STAGE_OBJ_FUNC D_80114D68[];
extern STAGE_OBJ_FUNC D_80114EA8[];
extern STCOM16_FUNC D_80114E44[]; // routine_0 handlers (func_8010D0A4)
extern STCOM16_FUNC D_80114E78[]; // routine_2 handlers (func_8010DE14)
extern STCOM16_FUNC D_80114E94[]; // routine_2 handlers (func_8010E384)
extern STCOM16_KIND **D_80098844;
extern STCOM16_FUNC D_80114EC4[]; // routine_2 handlers (func_8010EE48)
extern STCOM16_FUNC D_80114ED0[]; // routine_2 handlers (func_8010F4DC)
extern ST1D_SPAWN_REC D_80113FC0[];
extern void *D_80114474[];
extern void *D_80114798[];
extern void *D_80114858[];
extern uint8 D_80114870[][0x28];
extern uint8 D_80114960[][8];
extern sint32 D_801149E0[];
extern STAGE_SLOT_FUNC D_80114A68[];
extern STAGE_SLOT_FUNC D_80114A74[];
extern STAGE_SLOT_FUNC D_80114A94[];
extern STAGE_ACTOR D_8009F108[]; // ROCK_NEO's 0x3C0-byte slots
extern STAGE_SLOT_FUNC D_80114AA8[];
extern uint16 D_80114AB4[];
extern uint16 D_80114AB6[];
extern ST1D_SPARK_POINT D_80114B50[];
extern STAGE_SLOT_FUNC D_80114BB4[];
extern uint8 D_80114BEC[];
extern uint8 D_80114BFC[];
extern STCOM_SVECTOR D_80114C00;
extern STAGE_SLOT_FUNC D_80114C7C[];
extern STAGE_SLOT_FUNC D_80114C88[];
extern uint8 D_80114C94[];
extern sint16 D_80114CA0[];
extern ST1D_ARM_FUNC D_80114D50[];
extern ST1D_ARM_FUNC D_80114D5C[];
extern ST1D_SPARK_POINT D_80114D70[];
extern STAGE_SLOT_FUNC D_80114DC0[];
extern STAGE_SLOT_FUNC D_80114DCC[];
extern STAGE_SLOT_FUNC D_80114DE4[];
extern ST1D_STUN_SPARK D_80114DF0[];
extern uint8 D_80114DF1[];
extern uint16 D_80114E00[];
extern uint8 D_80114E20[];
extern STAGE_SLOT_FUNC D_80114E2C[];
extern uint8 D_80114E38[];
extern STAGE_SLOT_FUNC D_80114E54[];
extern STAGE_PANEL_ROOM D_80114FD0[];
extern STAGE_PANEL_OFFSET D_80114FF0[];
extern STAGE_SLOT_FUNC D_80115000[];
extern ST1D_PANEL_ROOM D_80115220[];
extern ST1D_CAM_REQ D_80115258[];
extern uint8 D_80115294[];
extern sint16 D_80115598[];
extern sint32 D_801155A0[]; // a scene flag per room
extern sint32 D_801155AC[]; // three scene flags
extern sint32 D_801155B8[];
extern STCOM_SVECTOR D_8011A6B0[1];
extern STCOM_FIXED_VECTOR D_8011A6B8[1];
extern uint32 D_8011A758; // the attribute of the cell func_80111D78 spawns panels on
extern uint16 D_8015C000[];
extern uint16 D_8015C002[];
extern uint16 D_8015C004[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];
extern ST1D_POS_REC D_80114AB0[];

void func_80100288(void);
void func_80100E38(STAGE_OBJ *wp);
void func_80100FE0(STAGE_OBJ *wp);
void func_80111D4C(STAGE_OBJ *wp);
void func_80111D6C(STAGE_OBJ *wp);
void func_80112B18(STAGE_OBJ *wp);
void func_80112B54(STAGE_OBJ *wp);
void func_80112B90(STAGE_OBJ *wp);
void func_8010B5B4(STAGE_OBJ *wp);
void func_8010B6BC(STAGE_OBJ *wp);
void func_8010BE74(STAGE_OBJ *wp);
void func_8010D084(STAGE_OBJ *wp);
void func_8010DD38(STAGE_OBJ *wp);
void func_8010E98C(STAGE_OBJ *wp);
void func_8010F890(STCOM16_WORK *wp);
sint32 Obj_ceiling_height_get(void *wp);
void func_8010E068(STCOM16_WORK *wp);
void func_8010E278(STCOM16_WORK *wp);
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
// func_80047148 as func_8010C84C calls it: with two arguments (retail leaves a2 unset).
void func_80047148_2(void *wp, STCOM_SVECTOR *pos) __asm__("func_80047148");
void func_8010B75C(STAGE_OBJ *wp);
void func_80111BA8(STAGE_OBJ *wp);
void func_80102B08(STAGE_OBJ *wp);
void func_8010B6F8(STAGE_OBJ *wp);
void func_80103FB4(ST1D_VIEW *wp);
void func_8010E804(ST1D_VIEW *wp);
void func_80103870(ST1D_VIEW *wp);
void func_80107FE4(ST1D_VIEW *wp);
void func_8010F02C(ST1D_VIEW *wp);
void func_8010E0F0(ST1D_VIEW *wp);
void func_8010F6D0(ST1D_VIEW *wp);
void func_8010F110(ST1D_VIEW *wp);
void func_8010CD64(STAGE_OBJ *wp);
void func_801029F4(ST1D_VIEW *wp);
void func_8010C7B0(ST1D_VIEW *wp);
sint32 func_801083E4(ST1D_VIEW *wp);
void func_80107EB8(ST1D_VIEW *wp);
void func_80102E10(ST1D_VIEW *wp);
void func_80102EC0(ST1D_VIEW *wp);
void func_80102D5C(ST1D_VIEW *wp);
void func_8010B8D0(ST1D_VIEW *wp);
void func_801113A4(void);
// func_800317AC is declared in stage_common/stage.h.
void func_8010E1DC(STCOM16_WORK *wp);
void func_8010E710(STCOM16_WORK *wp);
void func_8010E838(STCOM16_WORK *wp);
void func_8010DD58(STCOM16_WORK *wp);
void func_8010F738(STCOM16_WORK *wp);
void func_80107F58(ST1D_VIEW *wp);

void func_801038B0(ST1D_VIEW *wp);
void func_801040F8(ST1D_VIEW *wp);
sint32 func_801052A0(ST1D_VIEW *wp);

void func_80047228(void *wp, STCOM_SVECTOR *pos, sint32 arg2);
void func_801036B0(ST1D_VIEW *wp);

void func_80103FD8(ST1D_VIEW *wp);

void func_80104B20(ST1D_VIEW *wp);

// A ROCK_NEO record per object kind (D_80098844), past stcom16's fields.
typedef struct
{
    uint8 reserved00[0xF];
    uint8 value_F; // 0F
} ST1D_KIND;

STAGE_OBJ *func_80036294(sint32 id);

extern STAGE_SLOT_FUNC D_80114BA0[];
extern STCOM_SVECTOR D_8011A698[1];
extern STCOM_FIXED_VECTOR D_8011A6A0;
extern sint16 D_80114BF8[];
void func_80102F24(ST1D_VIEW *wp);

sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80103920(ST1D_VIEW *wp);

sint32 func_80031E60(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80103D6C(ST1D_VIEW *wp);

void func_80105060(ST1D_VIEW *wp);

sint32 func_80105318(ST1D_VIEW *wp);

void func_8010802C(ST1D_VIEW *wp);

void func_80100554(STAGE_ROOM_WORK *wp);
void func_801005E4(STAGE_ROOM_WORK *wp);

sint32 func_800364B0(void *track, void *wp, sint32 angle);

void func_8005D6E8(void *wp);

void Sound_key_off_voice(sint32 voice);
void func_80111D78(void);
extern STCOM16_KIND **D_8009884C; // a second record per kind
void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 a4);
void Mem_copy4(void *src, void *dst, sint32 count);
void func_8010C9AC(ST1D_VIEW *wp, uint8 kind);
void func_80030EE8(void *wp, STCOM_SVECTOR *target, sint32 speed);
void Obj_launch_set(void *shot, void *target, sint32 speed, sint32 arg3, sint32 arg4);
void func_8001D974(void);
void Model_parts_mtx_set(void *wp, STCOM_MATRIX *m);

extern uint32 D_800987E8; // allocation masks: 0x3C0 slots
extern uint32 D_80098B20; // 0x5A4

#endif
