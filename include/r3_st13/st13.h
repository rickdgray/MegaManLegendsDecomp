#ifndef ST13_H
#define ST13_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom16.h"

// A scratchpad halfword func_80111814 sets before func_8003346C.
#define ST13_SP_13C (*(uint16 *)0x1F80013C)

// From r3_st10 (ST10_ACTOR_CTL), itself from r3_st04.
// A 0x20-byte control block of ST13_ACTOR (at +0x348 and +0x368).
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
    uint16 value_18;        // 18
    uint16 value_1A;        // 1A
    uint16 value_1C;        // 1C
    uint16 value_1E;        // 1E
} ST13_ACTOR_CTL;

// From r3_st04 (ST04_ACTOR).
// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C
    sint8 value_D;                          // 0D
    sint8 value_E;                          // 0E
    uint8 reserved0F;                       // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0x28];                 // 7C
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
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    STCOM_SVECTOR value_188;                // 188: a joint
    uint8 reserved190[0x1B8];               // 190
    ST13_ACTOR_CTL ctl;                     // 348
    ST13_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST13_ACTOR;

// A 0x3C0-byte slot that sends 0x48-byte effects (kind 0x13) from the joint +0x188 of the slot
// whose id is in id_F (func_80101D78, func_80101E4C).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 index_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 count_C;                          // 0C
    uint8 frame_D;                          // 0D
    sint8 left_E;                           // 0E: effects still to send
    sint8 id_F;                             // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x4C];                 // 44
    STCOM_SVECTOR origin_90;                // 90
    uint8 reserved98[0x34];                 // 98
    sint32 angle_CC;                        // CC: toward the player
    uint8 reservedD0[0x2F0];                // D0
} ST13_EMITTER;

// A record of ROCK_NEO's table at D_8009884C, by kind.
typedef struct
{
    uint8 reserved0[8]; // 0
    uint8 life_8;       // 8: times 16
    uint8 value_9;      // 9
    uint8 value_A;      // A: or'd into the hit box's kind bits
    uint8 value_B;      // B
    uint8 reservedC[3]; // C
    uint8 track_F;      // F: func_80036478's argument
} ST13_KIND;

// A map position (x, z).
typedef struct
{
    sint16 x, z;
} ST13_XZ;

// A texture position.
typedef struct
{
    uint8 u, v;
} ST13_UV;

// The block at +0x28 of a drifting spark (ST13_SPARK).
typedef struct
{
    sint32 angle_0;          // 28: its heading
    uint16 bob_4;            // 2C: the bobbing angle
    sint16 timer_6;          // 2E: frames left
    uint32 hit_8;            // 30
    uint32 value_C;          // 34
    STCOM_SVECTOR origin_10; // 38
    uint8 shade_18;          // 40
    uint8 frame_19;          // 41
    sint16 wobble_1A;        // 42
} ST13_SPARK_CTL;

// A 0x48-byte effect slot (func_80031618) of a spark with a hit box (func_80104B68, func_80104C9C).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 index_1;       // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    uint8 value_C;       // 0C
    sint8 value_D;       // 0D
    uint8 reserved0E[6]; // 0E
    uint32 mode_14;      // 14
    uint32 color_18;     // 18
    union
    {
        STCOM_SVECTOR pos; // the hit box's center
        struct
        {
            sint16 x, y, z;
            uint8 u, v; // texture position
        } spr;
    } u_1C;              // 1C
    uint16 w_24;         // 24
    uint16 h_26;         // 26
    ST13_SPARK_CTL ctl;  // 28
    uint8 reserved44[4]; // 44
} ST13_SPARK;

// stcom27's block (STCOM27_CTL), as far as this stage's copies use it.
typedef struct
{
    uint8 track_0[0x10];   // 00
    sint32 sees_10;        // 10
    sint32 flags_14;       // 14: 1 hit a wall, 2 on the ground, 4 at a ledge
    STCOM_SVECTOR pos_18;  // 18: the hit box's center
    uint32 hit_20;         // 20: damage in the low 24 bits, kind bits above
    uint32 value_24;       // 24
    STCOM_SVECTOR from_28; // 28
    uint32 kind_30;        // 30: the hit box's kind bits
    uint16 timer_34;       // 34
    uint16 timer_36;       // 36
    uint16 count_38;       // 38: frames the player has been near
} ST13_STCOM27_CTL;

// stcom27's work slot with its block at +0x4E0 instead of +0x348 (func_8010103C).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 index_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[2];                    // 04
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 value_C;                          // 0C: nonzero: it watches the player (func_8003648C)
    sint8 value_D;                          // 0D
    uint8 reserved0E[6];                    // 0E
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[4];                    // 70
    sint8 jump_74;                          // 74: set while it is in the air
    sint8 jump_prev_75;                     // 75
    uint8 reserved76[2];                    // 76
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 dist_80;                         // 80: distance to the player (squared?)
    uint8 reserved84[0x20];                 // 84
    uint8 value_A4;                         // A4
    uint8 reservedA5[7];                    // A5
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 damage_B2;                       // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x380];               // 160
    ST13_STCOM27_CTL ctl;                   // 4E0
} ST13_STCOM27_WORK;

// From r3_st1a (ST1A_OBJ).
// A view of STAGE_OBJ with the fields r3_st1a's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint8 reserved4; // 04
    uint8 value_5;   // 05
    uint8 value_6;   // 06
    uint8 value_7;   // 07
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
    sint32 value_50;                        // 50
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x2];                  // 64
    sint16 value_66;                        // 66
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    sint32 value_78;                        // 78
    uint8 reserved7C[0x4];                  // 7C
    sint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    sint32 value_8C;                        // 8C
    sint32 value_90;                        // 90
    sint32 value_94;                        // 94
    uint8 *anim_98;                         // 98
    sint32 value_9C;                        // 9C
    sint32 value_A0;                        // A0
    uint8 reservedA4[3];                    // A4
    sint8 value_A7;                         // A7
    sint32 value_A8;                        // A8
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
    sint32 value_D0;                        // D0
    sint32 value_D4;                        // D4
    uint8 reservedD8[0x18];                 // D8
    sint32 value_F0;                        // F0
    sint32 value_F4;                        // F4
    sint32 value_F8;                        // F8
    sint32 value_FC;                        // FC
    STAGE_PART part_100[12];                // 100
    uint8 reserved130[0x18];                // 130
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x20];                // 160
    uint16 value_180;                       // 180
    uint16 value_182;                       // 182
    uint16 value_184;                       // 184
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[0x2];                 // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0xA0];                // 2A8
    sint16 value_348;                       // 348
    sint16 value_34A;                       // 34A
    uint8 reserved34C[0x4];                 // 34C
    sint32 value_350;                       // 350
    sint32 value_354;                       // 354
    uint8 reserved358[0x54];                // 358
    sint16 value_3AC;                       // 3AC
    uint8 reserved3AE[0x4];                 // 3AE
    uint16 value_3B2;                       // 3B2
    uint8 value_3B4;                        // 3B4
    uint8 reserved3B5[0x6B];                // 3B5
    sint32 value_420;                       // 420
    sint32 value_424;                       // 424
    sint32 value_428;                       // 428
    sint32 value_42C;                       // 42C
    sint32 value_430;                       // 430
    sint32 value_434;                       // 434
    sint32 value_438;                       // 438
    sint32 value_43C;                       // 43C
    sint32 value_440;                       // 440
    sint16 value_444;                       // 444
    uint8 reserved446[0x2];                 // 446
    sint16 value_448;                       // 448
    uint8 reserved44A[0xE];                 // 44A
    sint32 value_458;                       // 458
    uint8 reserved45C[0x24];                // 45C
    sint32 value_480;                       // 480
    sint32 value_484;                       // 484
    sint32 value_488;                       // 488
    sint32 value_48C;                       // 48C
    uint16 value_490;                       // 490
    uint8 value_492;                        // 492
    uint8 value_493;                        // 493
    uint8 reserved494[0xC];                 // 494
    sint32 value_4A0;                       // 4A0
    uint8 reserved4A4[0x14];                // 4A4
    sint16 value_4B8;                       // 4B8
    sint16 value_4BA;                       // 4BA
    uint8 reserved4BC[0x1C];                // 4BC
    sint16 value_4D8;                       // 4D8
    sint8 value_4DA;                        // 4DA
    sint8 value_4DB;                        // 4DB
    uint8 reserved4DC[0x2];                 // 4DC
    sint16 value_4DE;                       // 4DE
    STAGE_FACE face;                        // 4E0
    uint8 reserved4F4[0x20];                // 4F4: (0x5A4-byte slots)
    sint16 value_514;                       // 514
    sint16 value_516;                       // 516
    uint8 reserved518[2];                   // 518
    uint16 value_51A;                       // 51A
} ST13_OBJ;

// A view of the work slots r3_st13's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST13_VIEW ST13_VIEW;

typedef void (*ST13_VIEW_FUNC)(ST13_VIEW *wp);
struct ST13_VIEW
{
    sint8 flags_0;        // 0
    uint8 value_1;        // 1
    uint8 kind_2;         // 2
    uint8 variant_3;      // 3
    uint8 value_4;        // 4
    uint8 reserved5[0x1]; // 5
    uint8 value_6;        // 6
    uint8 reserved7[0x1]; // 7
    uint8 routine_0;      // 8
    uint8 routine_1;      // 9
    uint8 routine_2;      // A
    uint8 routine_3;      // B
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
    sint16 value_44;                        // 44
    sint16 value_46;                        // 46
    sint16 value_48;                        // 48
    uint8 reserved4A[0x2];                  // 4A
    sint16 value_4C;                        // 4C
    uint16 value_4E;                        // 4E
    sint16 value_50;                        // 50
    uint8 reserved52[0x2];                  // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_64;                // 64
    uint8 reserved68[0x6]; // 68
    sint16 value_6E;       // 6E
    uint8 reserved70[0x4]; // 70
    sint8 value_74;        // 74
    sint8 value_75;        // 75
    uint8 reserved76[0x2]; // 76
    sint32 value_78;       // 78
    uint8 reserved7C[0x4]; // 7C
    sint32 value_80;       // 80
    uint8 reserved84[0xC]; // 84
    sint16 value_90;       // 90
    sint16 value_92;       // 92
    sint16 value_94;       // 94
    uint8 reserved96[0xE]; // 96
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_A4;                 // A4
    uint8 reservedA8[0x4];  // A8
    uint8 value_AC;         // AC
    uint8 value_AD;         // AD
    uint8 reservedAE[0x2];  // AE
    sint16 value_B0;        // B0
    sint16 value_B2;        // B2
    uint8 reservedB4[0x16]; // B4
    uint8 value_CA;         // CA
    uint8 value_CB;         // CB
    sint32 value_CC;        // CC
    uint8 reservedD0[0x88]; // D0
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_158; // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    uint8 reserved160[0x20];  // 160
    STCOM_SVECTOR vec_180;    // 180
    STCOM_SVECTOR vec_188;    // 188
    uint8 reserved190[0x1F2]; // 190
    sint16 value_382;         // 382
    uint8 reserved384[0x15C]; // 384
    uint16 value_4E0;         // 4E0
    uint16 value_4E2;         // 4E2
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_4E4; // 4E4
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_4E8;                // 4E8
    uint8 reserved4EC[0x4]; // 4EC
    sint32 value_4F0;       // 4F0
    sint32 value_4F4;       // 4F4
    STCOM_SVECTOR vec_4F8;  // 4F8
    sint32 value_500;       // 500
    sint32 value_504;       // 504
    uint8 reserved508[0x8]; // 508
    sint32 value_510;       // 510
    union
    {
        sint16 h[2];
        uint16 uh[2];
        sint32 w[1];
    } u_514; // 514
    union
    {
        sint16 h[2];
        uint16 uh[2];
        sint32 w[1];
    } u_518;                 // 518
    uint16 value_51C;        // 51C
    sint16 value_51E;        // 51E
    uint8 reserved520[0x84]; // 520
};

// A 10-byte record in a room's table: a map rectangle and the routine it starts; routine_9 -1
// ends the table.
typedef struct
{
    sint16 x_0;      // 0
    sint16 z_2;      // 2
    uint16 w_4;      // 4
    uint16 d_6;      // 6
    uint8 value_8;   // 8
    sint8 routine_9; // 9
} ST13_REC10;

typedef void (*ST13_REC_FUNC)(STAGE_OBJ *wp, ST13_REC10 *rec);

extern STAGE_SLOT_FUNC *D_8011607C[];
extern STAGE_SLOT_FUNC *D_8011621C[];
extern STAGE_SLOT_FUNC D_80116264[];
extern STAGE_SLOT_FUNC D_801162B4[];
extern STAGE_SLOT_FUNC D_80116304[];
extern STAGE_SLOT_FUNC D_8011638C[];
extern STAGE_ROOM_FUNC D_80117354[];
extern STAGE_ROOM_FUNC *D_80117314[];
extern uint8 D_80117294[];
extern STAGE_OBJ_FUNC D_80117500[];
extern STAGE_OBJ_FUNC D_80117534[];
extern STAGE_OBJ_FUNC D_80117540[];
extern STAGE_FACE D_80118D34;
extern sint8 *D_801186E0[];
extern sint8 *D_801186F0[];
extern STAGE_OBJ_FUNC D_80118C48[];
extern STAGE_OBJ_FUNC D_80118C60[];
extern STAGE_OBJ_FUNC D_80117660[];
extern STAGE_OBJ_FUNC D_80117664[];
extern STAGE_OBJ_FUNC D_80117838[];
extern STAGE_OBJ_FUNC D_801184E4[];
extern STCOM16_FUNC D_80118480[]; // routine_0 handlers (func_8010C764)
extern uint8 D_80118474[];        // data_78
extern STCOM16_KIND **D_80098844;
extern STCOM16_FUNC D_80118490[]; // routine_1 handlers (func_8010CAD4)
extern STCOM16_FUNC D_801184B4[]; // routine_2 handlers (func_8010D4C4)
extern STCOM16_FUNC D_801184D0[]; // routine_2 handlers (func_8010DA34)
extern STCOM16_FUNC D_80118500[]; // routine_2 handlers (func_8010E504)
extern STCOM16_FUNC D_8011850C[]; // routine_2 handlers (func_8010EB98)
extern uint8 D_8011729C;
extern uint8 D_80117490[];
extern uint8 D_80117498[][8];
extern STAGE_SCRIPT_ENTRY D_8011738C[];
extern uint8 D_80118D48;
extern uint8 D_80118D4C;
extern uint8 D_8011862C[];
extern STAGE_ROOM2_FUNC D_801186F4[];
extern ST13_REC10 *D_801177FC[];
extern ST13_REC_FUNC D_80117828[];
extern sint32 D_80115C64[];
extern void *D_80116AF0[];
extern void *D_80116F78[];
extern uint8 D_80116FB0[][0x28];
extern uint8 D_801171E0[][8];
extern sint32 D_80117220[];
extern uint8 D_801174F8[];
extern uint8 D_801174FC[];
extern uint8 D_8011750C[];
extern STAGE_SLOT_FUNC D_80117518[];
extern ST13_UV D_80117644[]; // a spark's texture u, v by frame
extern uint8 D_80117654[];
extern STAGE_STCOM15_FUNC_4E0 D_801185D0[];
extern STAGE_SLOT_FUNC D_801185DC[];
extern uint8 D_8011860C[];
extern sint16 D_80118618;
extern sint16 D_8011861A;
extern sint16 D_8011861C;
extern sint16 D_8011861E;
extern uint8 D_80118628[];
extern ST13_XZ D_80118C54[]; // where func_80114BC8 puts its three slots
extern sint32 D_80118C74;
extern sint32 D_80118C78;
extern sint32 D_80118C7C;
extern sint32 D_80118C80[];
extern STCOM_SVECTOR D_80118D2C; // where the walker heads (y and z by their own symbols)
extern sint16 D_80118D2E;
extern ST13_XZ D_80118620; // a map area's corner
extern ST13_XZ D_80118624; // and its size
extern sint16 D_80118D30;
extern STAGE_OBJ *D_80118D50[]; // three work slots ([1] and [2] are also D_80118D54, D_80118D58)
extern sint32 D_80118D54;
extern sint32 D_80118D58;
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];
// ROCK_NEO's records per kind (a byte at +0xA is ORed into the hit flags).

void func_8010051C(void);
void func_801007D0(void);
void func_8001DF10(uint8 *);
void func_80100808(STAGE_ROOM *wp);
sint32 func_80100968(void);
void func_80100B70(STAGE_OBJ *wp);
void func_80101174(ST13_VIEW *wp);
void func_80101134(STAGE_OBJ *wp);
void func_801011FC(ST13_OBJ *wp);
void func_80101BD8(ST13_OBJ *wp);
void func_8010127C(STAGE_OBJ *wp);
void func_801012E8(ST13_STCOM27_WORK *wp);
void func_8010123C(STAGE_OBJ *wp);
void func_80101C4C(STAGE_OBJ *wp);
void func_801017DC(ST13_OBJ *wp);
void func_8010185C(ST13_VIEW *wp);
void func_8010181C(STAGE_OBJ *wp);
void func_801018E4(ST13_OBJ *wp);
void func_80101B84(ST13_OBJ *wp);
void func_80101938(STAGE_OBJ *wp);
void func_80101D1C(STAGE_OBJ *wp);
void func_80101D3C(STAGE_OBJ *wp);
void func_80101F30(STAGE_OBJ *wp);
void func_80111E70(STAGE_OBJ *wp);
void func_80113758(sint32 index);
void func_80113794(sint32 index);
void func_801137D0(void);
void func_80114B8C(STAGE_OBJ *wp);
void func_80114CF0(STAGE_OBJ *wp);
void func_801150D4(STAGE_OBJ *wp);
void func_80104AF0(STAGE_OBJ *wp);
void func_80104B2C(STAGE_OBJ *wp);
STAGE_OBJ *func_80036294(sint32 id);
void func_80107DA0(STAGE_OBJ *wp);
void func_8010D3E8(STAGE_OBJ *wp);
void func_8010E048(STAGE_OBJ *wp);
void func_8003354C(void *wp);
void func_80036478(void *track, uint8 arg1, uint32 arg2);
sint32 func_80049448(void *wp);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
void func_80100DDC(ST13_STCOM27_WORK *wp);
void func_80101B28(STAGE_OBJ *wp, sint32 anim);
void func_80101BF8(ST13_OBJ *wp);
void func_80101C94(ST13_VIEW *wp);
void Sce_flag_off(sint32 flag);
void func_801004D8(void);
void func_80100FA4(ST13_STCOM27_WORK *wp);
void func_8010103C(ST13_STCOM27_WORK *wp);
sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target,
                     sint32 target_rot, sint32 target_range);
void ApplyMatrix(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_FIXED_VECTOR *out);
void func_8010CAD4(STCOM16_WORK *wp);
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_8010EF4C(STCOM16_WORK *wp);
sint32 func_80048E6C(void *wp);
void func_8010D88C(STCOM16_WORK *wp);
void func_8010D718(STCOM16_WORK *wp);
void func_8010D928(STCOM16_WORK *wp);
void func_8010DDCC(STCOM16_WORK *wp);
void func_8010DEF4(STCOM16_WORK *wp);
#ifdef __wasm32__
void func_80047148(void *wp, STCOM_SVECTOR *pos);
#else
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
#endif
void func_80100988(void);
void func_801150B0(STAGE_OBJ *wp);
void func_801009C8(void);
sint32 func_80100920(STAGE_OBJ *wp);
void func_80115060(STAGE_OBJ *wp);
void func_80100854(STAGE_OBJ *wp);
void func_80101A84(STAGE_OBJ *wp);
void func_801079DC(STAGE_OBJ *wp);
void func_80100664(STAGE_OBJ *wp);
// func_800317AC is declared in stage_common/stage.h.
void func_8001E4C4(void *a, void *b);
void func_8001EB98(void *entry);

// Game_work's four halfwords at +0x194 that this stage's room script clears.
#define ST13_GAME_HALF(offset) (*(uint16 *)((uint8 *)&Game_work + (offset)))

extern ST13_KIND **D_8009884C;

extern uint32 D_80098B20; // ROCK_NEO.EXE

STAGE_OBJ *func_80031498(void); // ROCK_NEO.EXE: allocates a work slot (NULL when none is free)

sint32 func_80049C54(STCOM_SVECTOR *pos, STCOM_SVECTOR *prev, void *info, sint32 mask);
sint32 func_80048EA4(STCOM_SVECTOR *pos, void *box, sint32 dy, sint32 kind);
void func_80104C9C(ST13_SPARK *wp);

// A 0x10C-byte slot (Open_SHL_WORK) as func_80112348 fires it: STAGE_PIECE with two more words.
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[0x10];            // 04
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    uint8 reserved66[0x36];            // 66
    sint32 value_9C;                   // 9C
    sint32 value_A0;                   // A0
    uint8 reservedA4[0x68];            // A4
} ST13_SHOT;

sint32 func_801134E4(STAGE_STCOM15_WORK_4E0 *wp);

void func_80113958(STAGE_ROOM *wp);
void func_801139A8(STAGE_ROOM_WORK *wp);

#endif
