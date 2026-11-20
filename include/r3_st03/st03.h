#ifndef ST03_H
#define ST03_H

#include "common.h"
#include "stage_common/stage.h"

// The frame counter in the scratchpad.
#define ST03_FRAME (*(uint16 *)0x1F800002)

// A view of STAGE_OBJ with the fields r3_st05's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    sint16 value_4;  // 04
    sint16 value_6;  // 06
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    union
    {
        struct
        {
            sint8 byte_C; // 0C
            sint8 byte_D; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 byte_E; // 0E
            sint8 byte_F; // 0F
        } b;
        sint16 angle; // 0E
    } u_E;
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    uint16 value_50;                        // 50
    sint16 value_52;                        // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    sint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x2];                  // 7E
    sint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98
    uint8 reserved9C[0xA];                  // 9C
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    sint16 value_AE;                        // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    sint32 value_B8;                        // B8
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    sint32 value_CC;                        // CC
    uint8 reservedD0[0x2B];                 // D0
    uint8 value_FB;                         // FB
    uint8 reservedFC[0x4];                  // FC
    STAGE_PART part_100[12];                // 100
    uint8 reserved130[0x18];                // 130
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x8];                 // 160
    uint8 value_168;                        // 168
    uint8 value_169;                        // 169
    uint8 reserved16A[0x16];                // 16A
    sint16 value_180;                       // 180
    sint16 value_182;                       // 182
    sint16 value_184;                       // 184
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[0x2];                 // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    uint16 value_308;                       // 308
    uint16 value_30A;                       // 30A
    sint16 value_30C;                       // 30C
    uint8 reserved30E[0x2];                 // 30E
    sint16 value_310;                       // 310
    uint8 reserved312[0xA];                 // 312
    sint32 value_31C;                       // 31C
    uint8 reserved320[0x8];                 // 320
    uint16 value_328;                       // 328
    sint16 value_32A;                       // 32A
    uint16 value_32C;                       // 32C
    sint16 value_32E;                       // 32E
    sint16 value_330;                       // 330
    uint8 reserved332[0xA];                 // 332
    sint32 value_33C;                       // 33C
    sint32 value_340;                       // 340
    sint32 value_344;                       // 344
    sint32 value_348;                       // 348
    sint32 value_34C;                       // 34C
    sint32 value_350;                       // 350
    uint8 reserved354[0x4];                 // 354
    uint16 value_358;                       // 358
    uint8 reserved35A[0x2];                 // 35A
    sint32 value_35C;                       // 35C
    sint32 value_360;                       // 360
    sint32 value_364;                       // 364
    uint16 value_368;                       // 368
    uint16 value_36A;                       // 36A
    sint32 value_36C;                       // 36C
    uint8 reserved370[0x2];                 // 370
    uint16 value_372;                       // 372
    uint8 reserved374[0x4];                 // 374
    sint32 value_378;                       // 378
    sint32 value_37C;                       // 37C
    STAGE_OBJ *value_380;                   // 380
    uint8 reserved384[0xBC];                // 384
    uint16 value_440;                       // 440
    uint16 value_442;                       // 442
    sint16 value_444;                       // 444
    uint8 reserved446[0x2];                 // 446
    sint16 value_448;                       // 448
    sint16 value_44A;                       // 44A
    uint8 reserved44C[0x94];                // 44C
    STAGE_FACE face;                        // 4E0
} ST03_OBJ;

// The control block at +0x348 of ST03_ACTOR.
typedef struct ST03_ACTOR ST03_ACTOR;

// A 0x10C-byte slot (Open_SHL_WORK) a villager carries above its head and then throws.
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[4];               // 04
    uint8 routine_0;                   // 08
    uint8 reserved09[0xB];             // 09
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 turn_64;                    // 64: direction it is thrown in
    uint8 reserved66[0x36];            // 66
    sint32 value_9C;                   // 9C: throw speed
    sint32 value_A0;                   // A0: throw height
    uint8 reservedA4[0x68];            // A4
} ST03_HELD;

typedef struct
{
    uint16 flags_0;         // 00
    uint16 value_2;         // 02
    sint16 timer_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 timer_A;         // 0A
    STCOM_SVECTOR target_C; // 0C: where the actor turns or walks to
    uint32 hit_14;          // 14: damage in the low 24 bits, kind bits above
    uint32 value_18;        // 18
    STCOM_SVECTOR from_1C;  // 1C: where the hit came from (pad bit 0: use it)
    uint8 track_24[0x10];   // 24: func_80036478's record
    uint32 range_34;        // 34
    ST03_HELD *other_38;    // 38: the slot it carries
    uint8 reserved3C[4];    // 3C
} ST03_ACTOR_CTL;

// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the block at +0x348
// named.
struct ST03_ACTOR
{
    sint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 value_4;                          // 04
    uint8 reserved05;                       // 05
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C
    sint8 value_D;                          // 0D
    sint8 value_E;                          // 0E
    sint8 value_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel_4C;                 // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 spin_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80
    uint8 reserved84[0x18];                 // 84
    sint32 value_9C;                        // 9C
    sint32 value_A0;                        // A0
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x2F];                 // CC
    sint8 value_FB;                         // FB
    uint8 reservedFC[7];                    // FC
    sint8 value_103;                        // 103
    uint8 reserved104[3];                   // 104
    sint8 value_107;                        // 107
    uint8 reserved108[3];                   // 108
    sint8 value_10B;                        // 10B
    uint8 reserved10C[3];                   // 10C
    sint8 value_10F;                        // 10F
    uint8 value_110;                        // 110
    uint8 reserved111[0x47];                // 111
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180[6];             // 180: [0] the talk camera's point; the body's points
    uint8 reserved1B0[0x198];               // 1B0
    ST03_ACTOR_CTL ctl;                     // 348
    uint8 reserved388[0x38];                // 388
};

// A rising spark effect and its emitter (variant_3 1 and 0): the emitter (func_8010FD1C) sheds a
// spark every few frames (func_8010FB74); a spark fades out while it rises (func_80104184), and
// ends when its emitter's routine does.
typedef struct ST03_SPARK ST03_SPARK;

struct ST03_SPARK
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[2];    // 04
    uint8 flags_6;          // 06
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B: emitter: frames to the next spark
    sint8 value_C;          // 0C
    sint8 timer_D;          // 0D
    sint8 width_E;          // 0E: emitter: the sparks' width
    sint8 type_F;           // 0F: growth per frame
    uint8 reserved10[4];    // 10
    uint32 mode_14;         // 14
    uint32 color_18;        // 18
    sint16 x_1C;            // 1C
    uint16 y_1E;            // 1E
    sint16 z_20;            // 20
    uint8 u_22;             // 22
    uint8 v_23;             // 23
    uint16 w_24;            // 24
    uint16 count_26;        // 26: emitter: sparks to run ahead
    sint32 rise_28;         // 28
    ST03_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

// A spark emitter's setup (func_80101918 passes it to func_8010FD1C).
typedef struct
{
    STAGE_XYZ pos;       // 00
    uint8 reserved06[2]; // 06
    uint8 width_8;       // 08
    uint8 growth_9;      // 09
    sint16 count_A;      // 0A
    sint32 rise_C;       // 0C
} ST03_EMIT;

// A view of the work slots r3_st03's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST03_VIEW ST03_VIEW;

typedef void (*ST03_VIEW_FUNC)(ST03_VIEW *wp);
struct ST03_VIEW
{
    sint8 flags_0;   // 0
    uint8 value_1;   // 1
    uint8 kind_2;    // 2
    uint8 variant_3; // 3
    uint8 value_4;   // 4
    uint8 value_5;   // 5
    uint8 value_6;   // 6
    uint8 value_7;   // 7
    uint8 routine_0; // 8
    uint8 routine_1; // 9
    uint8 routine_2; // A
    uint8 routine_3; // B
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_C;                                  // C
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_44; // 44
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_48; // 48
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_4C;                      // 4C
    sint16 value_50;             // 50
    uint8 reserved52[0x2];       // 52
    STCOM_SVECTOR rotation;      // 54
    STCOM_SVECTOR rotation_prev; // 5C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_64;                 // 64
    uint8 reserved68[0x6];  // 68
    sint16 value_6E;        // 6E
    sint32 value_70;        // 70
    sint32 value_74;        // 74
    sint32 value_78;        // 78
    uint8 reserved7C[0x4];  // 7C
    sint32 value_80;        // 80
    uint8 reserved84[0x20]; // 84
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_A4;                // A4
    uint8 reservedA8[0x4]; // A8
    STCOM_SVECTOR vec_AC;  // AC
    sint32 value_B4;       // B4
    uint8 reservedB8[0x4]; // B8
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_BC; // BC
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_C0;                  // C0
    uint8 reservedC4[0x6];   // C4
    sint16 value_CA;         // CA
    sint16 value_CC;         // CC
    sint16 value_CE;         // CE
    uint8 reservedD0[0x2B];  // D0
    uint8 value_FB;          // FB
    uint8 reservedFC[0x7];   // FC
    uint8 value_103;         // 103
    uint8 reserved104[0x3];  // 104
    uint8 value_107;         // 107
    uint8 reserved108[0x3];  // 108
    uint8 value_10B;         // 10B
    uint8 reserved10C[0x3];  // 10C
    uint8 value_10F;         // 10F
    uint8 value_110;         // 110
    uint8 reserved111[0x47]; // 111
    sint32 value_158;        // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    uint8 reserved160[0x24];  // 160
    sint32 value_184;         // 184
    uint8 reserved188[0x1C0]; // 188
    uint16 value_348;         // 348
    uint16 value_34A;         // 34A
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_34C; // 34C
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_350;                  // 350
    STCOM_SVECTOR vec_354;    // 354
    sint32 value_35C;         // 35C
    sint32 value_360;         // 360
    uint8 reserved364[0x18];  // 364
    sint32 value_37C;         // 37C
    sint32 value_380;         // 380
    uint8 reserved384[0xA4];  // 384
    sint32 value_428;         // 428
    sint32 value_42C;         // 42C
    sint32 value_430;         // 430
    uint8 reserved434[0x4];   // 434
    sint16 value_438;         // 438
    sint16 value_43A;         // 43A
    sint16 value_43C;         // 43C
    uint8 reserved43E[0x2];   // 43E
    sint16 value_440;         // 440
    uint16 value_442;         // 442
    sint16 value_444;         // 444
    uint8 reserved446[0x2];   // 446
    uint8 value_448;          // 448
    uint8 reserved449[0x15B]; // 449
};

// A ROCK_NEO record per object kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // 08
    uint8 limit_9; // 09: damage that knocks it back (ST03_ACTOR_CTL timer_A)
    uint8 value_A; // 0A: how long it stays down (func_801065F8)
} ST03_KIND;

// The camera block at 0x800BC730 (ROCK_NEO's SCENE_CAM): position and angles, 16.16.
typedef struct
{
    uint8 reserved00[0x10]; // 00
    sint32 pos_10;          // 10
    sint32 pos_14;          // 14
    sint32 pos_18;          // 18
    uint8 reserved1C[0x24]; // 1C
    sint32 rot_40;          // 40
    sint32 rot_44;          // 44
    sint32 rot_48;          // 48
} ST03_CAM;

// The room script work (D_800989F8, STAGE_ROOM_WORK) with the object its scripts drive typed.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[3];   // 01
    uint8 routine_4;       // 04
    uint8 routine_5;       // 05
    uint8 routine_6;       // 06
    uint8 routine_7;       // 07
    uint8 routine_8;       // 08
    uint8 reserved09[3];   // 09
    sint32 timer_C;        // 0C
    sint32 frame_10;       // 10
    sint32 word_14;        // 14
    uint8 reserved18[0xC]; // 18
    ST03_ACTOR *child_24;  // 24
} ST03_ROOM_WORK;

// A work slot with its own scaled, turned matrix (func_801132F8).
typedef struct
{
    uint8 flags_0;        // 00
    uint8 reserved01[2];  // 01
    uint8 variant_3;      // 03
    uint8 reserved04[4];  // 04
    uint8 routine_0;      // 08
    uint8 reserved09[3];  // 09
    sint8 angle_C;        // 0C
    uint8 reserved0D[11]; // 0D
    STAGE_MATRIX matrix;  // 18
    uint8 reserved38[8];  // 38
    sint32 color_40;      // 40
    uint8 reserved44[4];  // 44
    sint32 value_48;      // 48
    sint32 value_4C;      // 4C
} ST03_MODEL;

// A halfword pair also written as one word: a 16.16 value whose halves are read on their own.
typedef union
{
    sint16 h[2];
    sint32 w;
} ST03_HW;

// A floating prop (func_8010FF4C; routines D_801171E4 and D_801171F0): STAGE_PROP with the
// fields its movers use named.
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 id_1;                             // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 path_C;                           // 0C: ST03_PATH index
    sint8 path_D;                           // 0D
    uint8 reserved0E[2];                    // 0E
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    ST03_HW speed_44;                       // 44: h[0] forward, h[1] rise
    sint32 value_48;                        // 48
    ST03_HW accel_4C;                       // 4C: h[1] rise
    uint8 reserved50[4];                    // 50
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[0x10];                 // 7C
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC
    sint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    union
    {
        uint32 w;
        uint16 h[4];
    } hit_BC;                // BC: h[2] timer, h[3] bob index
    uint8 reservedC4[6];     // C4
    STCOM_SVECTOR target_CA; // CA
    uint8 reservedD2[0x3A];  // D2
} ST03_PROP;

// A path entry of the props that walk (func_80110284).
typedef struct
{
    STCOM_SVECTOR target; // 00: x, y, z and the speed in pad
    uint32 reach_8;       // 08: squared distance that counts as arrived
    sint32 turn_C;        // 0C
} ST03_PATH;

// Player_work as the stage's player routines take it: +0xC is their routine (a signed byte), and
// +0x428/+0x438 a second position in 16.16 and in halfwords.
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01[7];               // 01
    uint8 routine_8;                   // 08
    uint8 routine_9;                   // 09
    uint8 reserved0A[2];               // 0A
    sint8 routine_C;                   // 0C
    sint8 value_D;                     // 0D: the cutscene routines' step
    sint8 timer_E;                     // 0E
    uint8 reserved0F[5];               // 0F
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x61];            // 5C
    uint8 flags_BD;                    // BD
    uint8 reservedBE[0x6A];            // BE
    uint16 pad_128;                    // 128: buttons
    uint16 pad_12A;                    // 12A
    uint8 reserved12C[0x58];           // 12C
    void *target_184;                  // 184
    uint8 reserved188[0x2A0];          // 188
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    STCOM_SVECTOR rot_440;             // 440
    uint8 anim_448;                    // 448
    uint8 reserved449[5];              // 449
    uint8 value_44E;                   // 44E
} ST03_PL;

// Player_work through ST03_PL.
#define ST03_PL_PTR ((ST03_PL *)&Player_work)

extern STAGE_SLOT_FUNC *D_80114350[];
extern STAGE_SLOT_FUNC *D_801144E4[];
extern STAGE_SLOT_FUNC D_801144E8[];
extern STAGE_SLOT_FUNC D_80114568[];
extern STAGE_SLOT_FUNC D_8011458C[];
extern STAGE_SLOT_FUNC D_801145E0[];
extern STAGE_ROOM_FUNC D_80115124[];
extern STAGE_ROOM_FUNC *D_801150E4[];
extern STAGE_ROOM2_FUNC D_80115370[];
extern STAGE_ROOM2_FUNC D_801166A8[];
extern STAGE_ROOM2_FUNC D_801166B4[];
extern STAGE_ACTOR_FUNC D_80117168[];
extern STCOM_FIXED_VECTOR D_8011CAE8;
extern STAGE_OBJ_FUNC D_8011748C[];
extern STAGE_OBJ_FUNC D_80117060[];
extern STAGE_OBJ_FUNC D_801170B8[];
extern STAGE_OBJ_FUNC D_801170E0[];
extern STAGE_OBJ_FUNC D_80117104[];
extern STAGE_OBJ_FUNC D_80117140[];
extern STAGE_OBJ_FUNC D_801171D8[];
extern uint8 D_80100108[];
extern uint8 D_80100244[];
extern uint8 D_80100294[];
extern void *D_801146C4[];
extern void *D_80114918[];
extern void *D_80114B7C[];
extern uint8 D_80114BA0[][0x28];
extern uint8 D_80114D08[][8];
extern sint32 D_80114F08[];
extern sint8 D_80114F2C;
extern sint8 D_80114F2D;
extern uint8 D_80114F2E;
extern uint8 D_80114F2F;
extern sint8 D_80114F30;
extern sint8 D_80114F31;
extern uint8 D_80114F32;
extern uint8 D_80114F33;
extern ST03_EMIT D_80115148[4];
extern ST03_EMIT D_80115188[4];
// D_80115148 and D_80115188 at their literal address: func_80101918 reads the fields this way, so
// GCC doesn't relate them to the walking pointer.
#define ST03_EMIT_TBL ((ST03_EMIT(*)[4])0x80115148)
extern STAGE_SCRIPT_ENTRY D_801151C8[];
extern uint8 D_801151DC[];
extern sint32 D_801152E0;
extern uint8 D_801152E4[];
extern uint8 D_801152EC[][8];
extern uint8 D_80115364[];
extern uint8 D_80115368[];
extern uint8 D_80115FB4[];
extern uint8 D_80115FC4[];
extern uint8 D_8011600C[];
extern uint8 D_80116034[];
extern STAGE_ROOM_FUNC D_8011614C[];
extern uint8 D_80116164[];
extern uint8 D_801161D0[];
extern uint8 D_801161F8[];
extern uint8 D_801162EC[];
extern uint8 D_8011630C[];
extern uint8 D_8011639C[];
extern uint8 D_8011642C[];
extern uint8 D_8011644C[];
extern STCOM_SVECTOR D_801164DC;
extern uint8 D_801166C0[];
extern uint8 D_80116754[];
extern STAGE_ROOM2_FUNC D_80116768[];
extern STAGE_SLOT_FUNC D_80116790[];
extern uint8 D_80116794[];
extern STAGE_SCRIPT_ENTRY D_801167E8[];
extern STAGE_ROOM2_FUNC D_80116810[];
extern STAGE_SLOT_FUNC D_80116860[];
extern STAGE_STCOM15_FUNC_348 D_80116864[];
extern STAGE_SLOT_FUNC D_80116870[];
extern uint8 D_801168BC[];
extern uint8 D_801168C4[];
extern STAGE_SLOT_FUNC D_8011706C[];
extern uint8 D_80117084[];
extern uint8 D_80117090[];
extern STCOM_SVECTOR D_8011709C;
extern STCOM_SVECTOR D_801170A4;
extern sint16 D_801170A8;
extern uint8 D_801170AC[];
extern STAGE_SLOT_FUNC D_801170EC[];
extern uint8 D_801170F8[];
extern STAGE_SLOT_FUNC D_80117110[];
extern uint8 D_80117128[];
extern uint8 D_80117134[];
extern STAGE_SLOT_FUNC D_8011714C[];
extern uint8 D_8011715C[];
extern uint8 D_8011716C[];
extern STAGE_SLOT_FUNC D_801171E4[];
extern STAGE_SLOT_FUNC D_801171F0[];
extern sint8 D_80117200[];
extern ST03_PATH D_80117204[];
extern STAGE_SLOT_FUNC D_80117414[];
extern STAGE_SLOT_FUNC D_80117420[];
extern uint8 D_80117424[];
extern uint8 D_80117430[];
extern ST03_SPARK *D_8011CA70[4]; // the four spark emitters (func_80101918)
extern sint16 D_8011CA84;
extern ST03_ACTOR D_8009F108[]; // ROCK_NEO: the 0x3C0-byte work slots
extern ST03_CAM Sce_camera_work;
extern uint8 D_8011CA88;
extern ST03_KIND **D_80098844;
extern uint16 D_800C0F96[]; // an array: GCC keeps its address in a register (func_80103EBC)
extern sint16 D_800C0F9A;
extern uint8 D_8011CA90;
extern STCOM_FIXED_VECTOR D_8011CA98;
extern STCOM_FIXED_VECTOR D_8011CAB8;
extern STCOM_FIXED_VECTOR D_8011CAC8;
extern STCOM_FIXED_VECTOR D_8011CAD8;
extern ST03_ACTOR *D_8011CB34[5]; // the cutscenes' actors
extern ST03_ACTOR *D_80138094;    // the slot the villager carries (func_8010758C)
extern ST03_ACTOR *D_801380A0[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_8001D974(void);
void func_80063BA8(void);
void func_8001B314(void);
void Sce_event_timer_clear(void);
void func_80036478(void *track, uint8 arg1, uint32 arg2);
void func_80030934(void *a0, void *a1, sint16 a2, sint16 a3);
void func_80047148(void *wp, STCOM_SVECTOR *pos);
sint32 func_80031E60(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void Sce_event_next(void);
void func_80053AA4(sint32 arg);
void func_8003697C(void);
void func_8002FF34(void *wp, sint32 x, sint32 y, sint32 z);
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void func_80101B2C(void);
void func_801007B4(void);
void func_8010089C(void);
void func_80100ECC(STAGE_ROOM *wp);
void func_80100F10(STAGE_ROOM *wp);
void func_80101114(STAGE_ROOM *wp);
void func_801011AC(STAGE_ROOM *wp);
void func_801011F0(STAGE_ROOM *wp);
void func_80101234(STAGE_ROOM *wp);
void func_80101278(STAGE_ROOM *wp);
void func_801012C4(STAGE_ROOM *wp);
void func_80101308(STAGE_ROOM *wp);
void func_8010134C(STAGE_ROOM *wp);
void func_80101390(STAGE_ROOM *wp);
void func_801014E4(STAGE_ROOM *wp);
void func_801015B0(STAGE_ROOM *wp);
void func_801015F4(STAGE_ROOM *wp);
void func_8010167C(STAGE_ROOM *wp);
void func_801016C0(STAGE_ROOM *wp);
sint32 func_801018F8(void);
void func_80101D18(STAGE_ROOM *wp);
void func_80112220(STAGE_OBJ *wp);
void func_80104328(STAGE_ROOM *wp);
void func_8010489C(STAGE_ROOM *wp);
void func_801071E0(uint8 *arg0);
void func_8010B63C(ST03_ACTOR *wp);
void func_8010C934(STAGE_OBJ *wp);
void func_8010C954(STAGE_OBJ *wp);
void func_8010CAB8(ST03_OBJ *wp);
void func_8010D3C4(STAGE_OBJ *wp);
void func_8010D730(ST03_OBJ *wp);
void func_8010DC34(STAGE_OBJ *wp);
void func_8010DC54(STAGE_OBJ *wp);
void func_8010E014(ST03_OBJ *wp);
void func_8010E0A8(STAGE_ACTOR *wp);
sint32 func_8010E3A8(ST03_ACTOR *wp);
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_8010FA58(STAGE_SPARK *wp);
void func_8010FAE4(STAGE_SPARK *wp);
void func_8010FB18(STAGE_OBJ *wp);
void func_8010FCBC(STAGE_OBJ *wp);
void func_8010FB38(STAGE_OBJ *wp);
void func_80110128(STAGE_OBJ *wp);
void func_801132BC(STAGE_OBJ *wp);
void func_8010A594(STAGE_OBJ *wp);
void func_8010B930(STAGE_OBJ *wp);
void func_8010C66C(STAGE_OBJ *wp);
void func_8010D0F4(STAGE_OBJ *wp);
void func_8010D968(STAGE_OBJ *wp);
void func_8010FB74(ST03_SPARK *wp);
ST03_SPARK *func_8010FD1C(STAGE_XYZ *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag);
void func_8010D0B4(ST03_ACTOR *wp);
void func_801013D4(STAGE_OBJ *wp);
void func_80101418(STAGE_OBJ *wp);
void func_8010145C(STAGE_OBJ *wp);
void func_801014A0(STAGE_OBJ *wp);
void func_80101528(STAGE_OBJ *wp);
void func_8010156C(STAGE_OBJ *wp);
void func_80101638(STAGE_OBJ *wp);
void func_80101B70(void);
sint32 func_801018B0(STAGE_OBJ *wp);
void func_801010C8(STAGE_OBJ *wp);
void func_80101160(STAGE_OBJ *wp);
void func_8010093C(STAGE_OBJ *wp);
sint32 func_80101778(STAGE_OBJ *wp);
sint32 func_801017D8(STAGE_OBJ *wp);
void func_8010A9A8(STAGE_OBJ *wp);
void func_8001EB98(uint8 *);
sint32 func_80101838(ST03_VIEW *wp);
void func_8010D020(ST03_ACTOR *wp);
void func_8010B2CC(ST03_ACTOR *wp);
void func_8010E300(ST03_VIEW *wp);
void func_80104A74(ST03_PL *wp);
void func_80104EBC(ST03_PL *wp);

extern uint32 stcom36_D_0000;
extern STAGE_SPAWNED *stcom36_E2_0000[];
void func_80103CC4(sint8 index);
void stcom36_func_0118(); // no parameters, but func_80100BF8 passes a 0

void func_8010AFC0(ST03_ACTOR *wp);
void func_8010B444(ST03_ACTOR *wp);
void func_8010CD68(ST03_ACTOR *wp);

void func_80112190(STAGE_PROP *wp);
void func_8011006C(ST03_PROP *wp);

// func_8010D3E4's delay-slot nop, which falls through into func_8010D404: func_80105178 calls this
// address (registry alias).
void func_8010A788(ST03_ACTOR *wp);
void func_8010D268(ST03_ACTOR *wp);
void func_8010D400(ST03_ACTOR *wp);
void func_8010D3E4(ST03_ACTOR *wp);
void func_8010D404(ST03_ACTOR *wp);

STAGE_OBJ *func_80036294(sint32 id); // ROCK_NEO.EXE: the spawned slot with this id (index_1)

void func_80106398(ST03_ACTOR *wp);

// func_80051B68 as this file calls it: with three arguments, a3 left as it is (Capcom's file had
// no prototype for it).
typedef void (*ST03_DRAW3_FUNC)(void *wp, sint32 a1, sint32 a2);

// Game_work's signed byte at +1 (2 once the cutscene's camera is ready: func_80101D54).
#define ST03_GAME_1 (((sint8 *)&Game_work)[1])

// stcom36's first spawned object as an actor.
#define ST03_SPAWNED_0 ((ST03_ACTOR *)stcom36_E2_0000[0])

void func_80039E50(void);
void func_80039FFC(STCOM_FIXED_VECTOR *vec, sint32 arg1, sint32 arg2, sint32 arg3);

// A timed sound of a cutscene: at frame time_0 (counting down), play se_2 (func_80102DBC).
typedef struct
{
    sint16 time_0;
    sint16 se_2;
} ST03_TIMED_SE;

extern ST03_TIMED_SE D_801164E4[];
extern ST03_TIMED_SE *D_8011CA80; // the next timed sound

// Scene_work seen through its object table (stcom36's STCOM36_SCENE_WORK).
typedef struct
{
    uint8 reserved00[0x24];
    STAGE_OBJ *obj_24[32]; // 24
} ST03_SCENE_OBJS;

#define ST03_SCENE_OBJ_0 (((ST03_SCENE_OBJS *)&Scene_work)->obj_24[0])

#endif
