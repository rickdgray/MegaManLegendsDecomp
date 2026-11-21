#ifndef ST1A_H
#define ST1A_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom16.h"
#include "stage_common/stcom23.h"
#include "stage_common/gte.h"

// A 0x5A4-byte slot's hit state at +0x440: flags (bit 9 set while the player is down), and a
// word at +0x18 cleared every frame (func_8011925C).
typedef struct
{
    union
    {
        sint32 word;
        uint16 half;
        uint16 h[2];      // h[1]: a random number each frame (func_80119714)
    } flags_0;            // 00
    sint16 value_4;       // 04
    sint16 value_6;       // 06
    uint16 value_8;       // 08: kind bits for the hit box
    sint16 value_A;       // 0A
    sint32 value_C;       // 0C: the ground height
    STCOM_SVECTOR pos_10; // 10: where the hit box sits
    sint32 value_18;      // 18
} ST1A_HIT;

// STAGE_FACE with a flag at +0x12 that turns the shadow on (func_8011146C's objects).
typedef struct
{
    sint16 timer_0;  // 0
    sint16 value_2;  // 2: animation speed
    sint8 *mouth_4;  // 4: shape, then a byte 0x7E (hold) or 0x7F (loop)
    sint8 *eyes_8;   // 8
    sint8 shape_C;   // C
    sint8 prev_D;    // D
    sint8 index_E;   // E
    sint8 shape_F;   // F
    sint8 prev_10;   // 10
    sint8 index_11;  // 11
    uint8 shadow_12; // 12
} ST1A_FACE;

// Four bytes per model part in the 0x3C0 slots (STAGE_PART, with a signed last byte).
typedef struct
{
    uint8 value_0;
    uint8 reserved1[2];
    sint8 value_3;
} ST1A_PART;

// A 0x48-byte effect slot of the smoke column (kind 0x21, func_8012B284): variant 0 is the
// emitter (func_8012B320), variant 1 a puff it spawns, variant 2 a spark (func_8012B440).
typedef struct ST1A_PUFF ST1A_PUFF;

struct ST1A_PUFF
{
    uint8 flags_0;       // 00
    uint8 reserved01;    // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 reserved04[2]; // 04
    uint8 flags_6;       // 06
    uint8 reserved07;    // 07
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B: frames to the next puff
    sint8 value_C;       // 0C
    sint8 timer_D;       // 0D
    sint8 frame_E;       // 0E
    sint8 type_F;        // 0F
    uint8 reserved10[4]; // 10
    uint32 mode_14;      // 14
    uint32 color_18;     // 18
    sint16 x_1C;         // 1C
    sint16 y_1E;         // 1E
    sint16 z_20;         // 20
    uint8 u_22;          // 22
    uint8 v_23;          // 23
    uint16 w_24;         // 24
    uint16 h_26;         // 26: the emitter's puffs to spawn at once
    sint32 value_28;     // 28
    union
    {
        ST1A_PUFF *owner; // a puff's emitter
        sint32 value;
        uint32 rise; // a spark's rising speed, in 16ths (func_8012AE60)
    } u_2C;
    sint32 value_30;        // 30
    uint8 reserved34[0x14]; // 34
};

// A view of STAGE_10C with the fields r3_st1a's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 value_4;                     // 04
    uint8 value_5;                     // 05
    uint8 value_6;                     // 06
    uint8 value_7;                     // 07
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    uint8 value_C;                     // 0C
    sint8 value_D;                     // 0D
    sint8 value_E;                     // 0E
    sint8 value_F;                     // 0F
    sint32 value_10;                   // 10
    STCOM_SVECTOR position;            // 14
    STAGE_FIXED_VECTOR position_fixed; // 1C
    sint32 value_2C;                   // 2C
    sint32 value_30;                   // 30
    sint32 value_34;                   // 34
    sint32 value_38;                   // 38
    sint32 value_3C;                   // 3C
    sint32 value_40;                   // 40
    sint32 value_44;                   // 44
    sint32 value_48;                   // 48
    uint8 reserved4C[0x2];             // 4C
    sint16 value_4E;                   // 4E
    sint32 value_50;                   // 50
    uint8 reserved54[0x2];             // 54
    sint16 value_56;                   // 56
    sint32 value_58;                   // 58
    uint8 reserved5C[0x2];             // 5C
    sint16 value_5E;                   // 5E
    uint8 reserved60[0x6];             // 60
    sint16 value_66;                   // 66
    uint8 reserved68[0x6];             // 68
    sint16 value_6E;                   // 6E
    sint32 value_70;                   // 70
    sint32 value_74;                   // 74
    sint32 value_78;                   // 78
    uint8 reserved7C[0x4];             // 7C
    sint32 value_80;                   // 80
    uint8 reserved84[0x4];             // 84
    void *model_88;                    // 88
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    sint32 value_B8;                   // B8
    sint32 value_BC;                   // BC
    sint32 value_C0;                   // C0
    sint32 value_C4;                   // C4
    sint32 value_C8;                   // C8
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[0x4];             // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0xE];             // E2
    sint32 value_F0;                   // F0
    sint32 value_F4;                   // F4
    sint32 value_F8;                   // F8
    sint32 value_FC;                   // FC
    uint8 reserved100[0x8];            // 100
    uint8 value_108;                   // 108
    uint8 reserved109[0x3];            // 109
} ST1A_10C;

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
    STAGE_FIXED value_64;                   // 64: the integer half is a turn speed
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
    STAGE_FX *fx_A0;                        // A0
    uint8 value_A4;                         // A4
    uint8 reservedA5[2];                    // A5
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
    STAGE_OBJ *owner_F0;                    // F0
    sint32 value_F4;                        // F4
    union
    {
        ST1A_PART part[14]; // model parts
        struct
        {
            sint32 value_F8;
            sint32 value_FC;
        } w;
    } u_F8;                     // F8
    uint8 reserved130[0x18];    // 130
    sint8 value_148[4];         // 148
    uint8 reserved14C[0xC];     // 14C
    STCOM_SVECTOR_W scale;      // 158
    uint8 reserved160[0x20];    // 160
    STCOM_SVECTOR part_180[24]; // 180: the parts' positions; pad is the palette (STAGE_PAL)
    STAGE_MATRIX matrix_240;    // 240
    uint8 reserved260[0x28];    // 260
    STAGE_MATRIX matrix_288;    // 288
    uint8 reserved2A8[0xA0];    // 2A8
    sint16 value_348;           // 348
    sint16 value_34A;           // 34A
    uint8 reserved34C[0x4];     // 34C
    sint32 value_350;           // 350
    sint32 value_354;           // 354
    uint8 reserved358[0x54];    // 358
    sint16 value_3AC;           // 3AC
    uint8 reserved3AE[0x4];     // 3AE
    uint16 value_3B2;           // 3B2
    uint8 value_3B4;            // 3B4
    uint8 reserved3B5[0x6B];    // 3B5
    STAGE_MATRIX matrix_420;    // 420
    ST1A_HIT hit_440;           // 440
    uint8 reserved45C[0x24];    // 45C
    sint32 value_480;           // 480
    sint32 value_484;           // 484
    sint32 value_488;           // 488
    sint32 value_48C;           // 48C
    sint16 value_490;           // 490
    uint8 value_492;            // 492
    uint8 value_493;            // 493
    uint8 reserved494[0xC];     // 494
    ST1A_10C *table_4A0;        // 4A0
    uint8 reserved4A4[0x14];    // 4A4
    sint16 value_4B8;           // 4B8
    sint16 value_4BA;           // 4BA
    uint8 reserved4BC[0x1C];    // 4BC
    sint16 value_4D8;           // 4D8
    sint8 value_4DA;            // 4DA
    sint8 value_4DB;            // 4DB
    uint8 reserved4DC[0x2];     // 4DC
    sint16 value_4DE;           // 4DE
    ST1A_FACE face;             // 4E0
    uint8 reserved4F4[0x1C];    // 4F4: (0x5A4-byte slots)
    sint32 value_510;           // 510
    sint16 value_514;           // 514
    sint16 value_516;           // 516
    uint8 reserved518[2];       // 518
    uint16 value_51A;           // 51A
    sint32 value_51C;           // 51C
    sint32 value_520;           // 520
} ST1A_OBJ;

// ST1A_10C's model block at +0x88: a word, then the matrix and the position it draws at.
typedef struct
{
    sint32 value_0;        // 00
    STAGE_MATRIX matrix_4; // 04
    STCOM_SVECTOR pos_24;  // 24
} ST1A_COORD;

// A 0x10C-byte piece of debris that falls and shrinks (func_80121968, func_80121ED4).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03: 0 and 1 fall, others bounce
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09: also its turn, in 16ths
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 reserved0C[8];                    // 0C
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    uint8 reserved54[0x1A];                 // 54
    sint16 scale_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[0xC];                  // 7C
    ST1A_COORD coord_88;                    // 88
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 hit_C4;                          // C4
    sint32 value_C8;                        // C8
    uint8 reservedCC[0x40];                 // CC
} ST1A_DEBRIS;

// ST1A_OBJ's block at +0x440 that the boss's routines keep a pointer to.
typedef struct
{
    ST1A_HIT hit_0;              // 00
    uint8 reserved1C[0x1C];      // 1C
    STCOM_SVECTOR target_38;     // 38: where the jump lands (func_8011B000)
    STCOM_FIXED_VECTOR fixed_40; // 40
    sint16 value_50;             // 50
    sint8 value_52;              // 52
    sint8 value_53;              // 53
    sint16 value_54;             // 54
    uint8 reserved56[2];         // 56
    ST1A_10C *part_58[4];        // 58: freed with the boss
    ST1A_10C *slot_68[2];        // 68
    uint16 value_70;             // 70
    sint8 value_72[2];           // 72
    uint8 reserved74[4];         // 74
    uint16 value_78;             // 78
    sint16 value_7A;             // 7A
    uint8 reserved7C[0x1C];      // 7C
    sint16 value_98;             // 98
    sint8 value_9A;              // 9A
    sint8 value_9B;              // 9B
    sint16 value_9C;             // 9C
    uint8 reserved9E[0x30];      // 9E
    sint16 count_CE;             // CE: which three parts burst next
} ST1A_BLOCK;

// A scene object routine (the object, Scene_work and its face).
typedef void (*ST1A_SCENE_FUNC)(STAGE_OBJ *wp, void *scene, void *face);

typedef void (*ST1A_OBJ_FUNC)(ST1A_OBJ *wp);
void func_8011EAFC(ST1A_OBJ *wp, sint32 arg);
void func_80033500(void *wp);
void Mem_clear(void *start, void *end);
void func_8011ED6C(ST1A_OBJ *wp);
extern ST1A_OBJ_FUNC D_80132EF0[];

typedef void (*ST1A_10C_FUNC)(ST1A_10C *wp);

// A view of STAGE_FX with the fields r3_st1a's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint8 reserved4; // 04
    uint8 value_5;   // 05
    uint8 flags_6;   // 06
    uint8 value_7;   // 07
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    sint8 value_C;   // 0C
    sint8 timer_D;   // 0D
    sint8 frame_E;   // 0E
    sint8 type_F;    // 0F
    sint32 value_10; // 10
    uint32 mode_14;  // 14
    uint32 color_18; // 18
    sint16 x_1C;     // 1C
    sint16 y_1E;     // 1E
    sint16 z_20;     // 20
    uint8 u_22;      // 22
    uint8 v_23;      // 23
    uint16 w_24;     // 24
    uint16 h_26;     // 26
    union
    {
        STAGE_FX *parent;  // the spawner
        STAGE_OBJ *object; // the object it follows
    } u_28;
    STAGE_FIXED x_2C;     // 2C
    STAGE_FIXED y_30;     // 30
    STAGE_FIXED z_34;     // 34
    STAGE_FIXED value_38; // 38
    STAGE_FIXED value_3C; // 3C
    sint32 value_40;      // 40
    STAGE_FX *owner_44;   // 44
} ST1A_FX;

typedef void (*ST1A_FX_FUNC)(ST1A_FX *wp);

void func_8012C1B4(STAGE_OBJ *wp);

void func_801226A8(STAGE_OBJ *wp);

void func_801226BC(STAGE_OBJ *wp);

void func_801226D0(STAGE_OBJ *wp);

void func_80127F00(STAGE_ROOM *wp);

void func_8011E9D0(STAGE_OBJ *wp);

void func_801058F8(void);

void func_80127EE8(STAGE_OBJ *wp);

void func_8011057C(STAGE_OBJ *wp);

void func_801178F0(STAGE_OBJ *wp);

void func_8011801C(STAGE_OBJ *wp);

void func_80119AF8(STAGE_OBJ *wp);

void func_8012367C(STAGE_OBJ *wp);

void func_801295A0(STCOM_EFFECT *arg0);

void func_801296F4(STCOM_EFFECT *arg0);

void func_80129A04(STCOM_EFFECT *arg0);

void func_8012A6D4(STCOM_EFFECT *arg0);

void func_8012A964(STCOM_EFFECT *arg0);

void func_8012B95C(STAGE_OBJ *wp);

void func_80101BF0(STAGE_ROOM *wp);

void func_80102CA4(STAGE_ROOM *wp);

void func_80100C24(void);

void func_80100C5C(void);

void func_80129648(STAGE_OBJ *wp);

void func_8011FC74(STAGE_OBJ *wp);

void func_8012788C(STAGE_OBJ *wp);

extern STAGE_ROOM2_FUNC D_8012E94C[];
void func_80100DC0(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_8012FED8[];
void func_801039A0(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_80130508[];
void func_80105200(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_80130514[];
void func_8010523C(STAGE_ROOM *wp);

void func_80112494(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80132AD4[];
void func_80116744(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80132B08[];
void func_8011750C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80133084[];
void func_8011FA80(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801330DC[];
void func_80120FEC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8013310C[];
void func_8012192C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80133134[];
void func_8012222C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801335DC[];
void func_80126514(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801335FC[];
void func_801268D8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80133678[];
void func_80127814(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80133690[];
void func_80127AA8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138CF8[];
void func_8012897C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138CFC[];
void func_801289B8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138D74[];
void func_801293A4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138D88[];
void func_801293E0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138D94[];
void func_801295C0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138DA4[];
void func_80129810(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138DB0[];
void func_80129A24(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138DBC[];
void func_80129D28(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138EE8[];
void func_8012A0DC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80138F3C[];
void func_8012A6F4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801396C4[];
void func_8012B8E4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801396CC[];
void func_8012B920(STAGE_OBJ *wp);

void func_80116DD0(ST1A_OBJ *wp);
void func_80116D08(STAGE_OBJ *wp);

void func_80116E10(STAGE_OBJ *wp);

void func_80127A68(STAGE_OBJ *wp);

void func_801174B8(ST1A_OBJ *wp);
void func_801173F0(STAGE_OBJ *wp);

void func_801048F8(STAGE_ROOM *wp);

void func_80122DA4(STAGE_OBJ *wp);

void func_80117820(STAGE_OBJ *wp);

void func_8012742C(STAGE_FX *wp);
void func_80126890(STAGE_OBJ *wp);

void func_80102290(STAGE_OBJ *wp);

void func_80102A50(STAGE_ROOM *wp);

void func_801033FC(STAGE_ROOM *wp);

void func_801295FC(STAGE_OBJ *wp);

void func_801120E4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8013366C[];
void func_80127F3C(STAGE_OBJ50 *wp);
void func_801277C4(STAGE_OBJ *wp);

void func_801021A8(STAGE_ROOM *wp);

void func_801283CC(STAGE_OBJ *wp);

void func_8010182C(STAGE_ROOM *wp);

void func_80117AB4(STAGE_OBJ *wp, void *face); // face is unused but passed

extern STAGE_OBJ_FUNC D_80132EE4[];
void func_8011C5C4(STAGE_OBJ *wp);

void func_80129BD8(STAGE_FX *wp);
void func_80129B7C(STAGE_OBJ *wp);

void func_80129EC4(STAGE_FX *wp);
void func_80129E68(STAGE_OBJ *wp);

void func_80102590(uint8 arg0);

void func_80126288(STAGE_FX *wp);

void func_80103B34(uint8 arg0, sint16 arg1, sint16 arg2, sint16 arg3, uint16 arg4);

void func_801029E8(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_801335D0[];
void func_801264AC(STAGE_OBJ *wp);

void func_80129D64(STAGE_OBJ *wp);

extern uint8 D_80139734;
void func_80105F18(STAGE_ROOM *wp);

void func_801279E8(STAGE_OBJ *wp);

void func_80129A60(STAGE_FX *wp);

void func_80129670(STAGE_OBJ *wp);

void func_801021FC(STAGE_ROOM *wp);

void func_80101DC0(STAGE_ROOM *wp);

void func_8012ABE0(ST1A_PUFF *wp);
void func_8012AD08(ST1A_PUFF *wp);
void func_8012AE60(ST1A_PUFF *wp);
void func_8012B284(ST1A_PUFF *wp);

extern STAGE_SLOT_FUNC *D_8012D648[];
extern STAGE_SLOT_FUNC *D_8012D7C0[];
extern STAGE_SLOT_FUNC D_8012D81C[];
extern STAGE_SLOT_FUNC D_8012D8FC[];
extern STAGE_SLOT_FUNC D_8012D984[];
extern STAGE_SLOT_FUNC D_8012DA0C[];
extern STAGE_ROOM2_FUNC *D_8012E8DC[];
extern sint8 *D_801320F0[];
extern sint8 *D_80132100[];
extern sint8 *D_8013258C[];
extern sint8 *D_801325DC[];
extern sint8 *D_801326B4[];
extern sint8 *D_801326C8[];
extern sint8 *D_801327F8[];
extern sint8 *D_8013282C[];
extern sint8 *D_80132A58[];
extern sint8 *D_80132A98[];
extern sint8 *D_80132D38[];
extern sint8 *D_80132D64[];

// Used by functions still in assembly (types from their accesses).
// A record of ROCK_NEO's table at D_8009884C, by kind.
typedef struct
{
    uint8 reserved0[8]; // 0
    uint8 life_8;       // 8: times 16
    uint8 value_9;      // 9
    uint8 value_A;      // A: or'd into the hit box's kind bits
    uint8 value_B;      // B
    uint8 value_C;      // C
    uint8 value_D;      // D
    uint8 value_E;      // E
    uint8 track_F;      // F: func_80036478's argument
} ST1A_KIND;

extern ST1A_KIND **D_8009884C;
extern sint32 D_800989FC;
extern uint8 D_800A395F;
extern STCOM_FIXED_VECTOR D_800A39F0; // the camera position (ROCK_NEO's PL_FIXED_VECTOR)
extern sint16 D_800BAEB0[];
extern sint32 D_800BBA94;
extern sint32 D_800BBA98;
extern sint16 D_800BBA9C;
extern sint16 D_800BBA9E;
extern sint32 D_800BBACC;
extern sint32 D_800BBAD0;
extern sint16 D_800BBAD4;
extern sint16 D_800BBAD6;
extern sint32 D_800BBB04;
extern sint32 D_800BBB08;
extern sint16 D_800BBB0C;
extern sint16 D_800BBB0E;
extern uint8 D_800BBB38;
extern sint16 D_800BBCF8[];
extern sint16 D_800BBD38[];
extern sint16 D_800C0F96[];
extern uint8 D_80100004[];
extern uint8 D_8010069C[];
extern uint8 D_801006E4[];
extern uint8 D_801006E8[];
extern uint8 D_801006EC[];
extern uint8 D_801006F0[];
extern uint8 D_801006F4[];
extern uint8 D_8012E944[];
extern STAGE_SCRIPT_ENTRY D_8012E958[];
extern STAGE_SCRIPT_ENTRY D_8012EAC0[];
extern uint8 D_8012EB4C[];
extern STAGE_ROOM2_FUNC D_8012F580[];
extern STCOM_SVECTOR D_8012F708;
extern uint8 D_8012F710[][7];
extern STAGE_SCRIPT_ENTRY D_8012F7A4;
extern STAGE_SCRIPT_ENTRY D_8012F7B8;
extern STAGE_SCRIPT_ENTRY D_8012F7CC;
extern STAGE_SCRIPT_ENTRY D_8012F7E0;
extern STAGE_SCRIPT_ENTRY D_8012F7F4;
extern STAGE_SCRIPT_ENTRY D_8012F808[];
extern uint8 D_8012F894[];
extern STAGE_ROOM2_FUNC D_8012FE48[];
extern STAGE_SCRIPT_ENTRY D_8012FF64;
extern STAGE_SCRIPT_ENTRY D_8012FF78;
extern uint8 D_8012FF8C[];
extern STAGE_SCRIPT_ENTRY D_8012FFA0;
extern uint8 D_8012FFB4[];
extern STAGE_ROOM2_FUNC D_80130000[];
extern uint8 D_80130010[];
extern STAGE_ROOM2_FUNC D_80130498[];
extern STAGE_SCRIPT_ENTRY D_80130520[];
extern STAGE_SCRIPT_ENTRY D_80130534[];
extern STAGE_SCRIPT_ENTRY D_801305FC[];
extern uint8 D_80130610[];
extern STAGE_SCRIPT_ENTRY D_80130624;
extern STAGE_SCRIPT_ENTRY D_80130638;
extern STAGE_SCRIPT_ENTRY D_8013064C[];
extern uint8 D_80130674[];
extern STAGE_ROOM2_FUNC D_80131270[];
extern uint16 D_801315A0[];
extern sint32 D_80131DDC[];
extern uint16 D_80131DF0[];
extern uint8 D_80131EFC[];
extern uint8 D_80131EFD[];
extern uint8 D_80131EFE[];
// A spark of a stunned object (D_80131F44): the joint and the look.
typedef struct
{
    uint8 joint_0;
    uint8 look_1;
} ST1A_STUN_SPARK;

extern ST1A_STUN_SPARK D_80131F44[];
extern uint8 D_80131F45[];
extern uint16 D_80131F54[];
extern uint8 D_80131F74[];
extern STCOM_SVECTOR D_80132130[]; // func_80111D88's spawn offsets, by wp->u_C.b.byte_C
extern sint8 *D_80132164[];
extern uint8 D_80132AE0[];
extern uint8 D_80132EBC[];
extern uint8 D_80132EC4[];
extern uint8 D_80132ECC[];
extern uint8 D_80132ED4[];
extern uint8 D_80132EDC[];
extern uint8 D_80132F10[];
extern uint8 D_80132F20[];
extern uint8 D_80132F3C[];
extern uint8 D_80132F58[];
extern uint8 D_801330D0[];
extern uint8 D_801330E4[];
extern uint16 D_801330F0[];
extern sint16 D_801330F4[];
extern uint16 D_801330F8[];
extern sint16 D_80133100[];
extern uint8 D_80133108[];
extern uint8 D_8013311C[];
extern uint16 D_80133128;
extern sint16 D_8013312C;
// An array view of D_8013312C: its load stays after struct stores (func_80122448).
extern sint16 D_8013312C_A[] __asm__("D_8013312C");
extern sint16 D_80133130;
extern sint16 D_80133160[];
extern uint8 D_8013318C[];
extern STCOM_FIXED_VECTOR D_80133198;
extern uint16 D_80133264[];
extern STCOM_SVECTOR D_8013361C[]; // the doors' two cells each: [n] and [n + 5]
extern STCOM_SVECTOR D_801336A8[]; // the gate's two cells
extern uint8 D_80138CDD[];
extern uint8 D_80138CEC[];
extern uint16 D_80138D24[];
extern uint16 D_80138D26[];
extern uint16 D_80138D28[];
extern uint16 D_80138D48[];
extern uint16 D_80138D4A[];
extern uint16 D_80138D4C[];
extern uint16 D_80138D54[];
extern uint8 D_80138D56[];
extern uint8 D_80138D5C[];
extern uint8 D_80138D5D[];
extern sint32 D_80138DC8[];
extern sint32 D_80138DD8[];
extern uint8 D_80138EE0[][4];
extern STAGE_OBJ50_FUNC D_80138EF4[];
extern STAGE_OBJ50_FUNC D_801336B8[];
extern sint16 D_801396F4;
extern uint16 D_801396F8;
extern sint32 D_8013973C;
extern sint32 D_80139740;
extern sint32 D_80139744;
extern sint32 D_80139748;
extern uint8 D_801397DC[];
extern uint16 D_8015C002[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern sint32 D_80164008[];

void func_8010097C(void);

extern ST1A_OBJ_FUNC D_80133170[];
void func_80123154(ST1A_OBJ *wp);

void func_801022DC(void *wp, sint32 arg);

extern sint8 *D_8013231C[];
void func_80031A4C(void *wp);

extern sint8 *D_801321B8[];
extern sint8 *D_80132B2C[];
extern sint8 *D_80132BAC[];

// Two talking faces kept in the stage data.
extern STAGE_FACE8 D_80139700;
extern STAGE_FACE8 D_80139714;
extern STAGE_FACE2 D_80139724;

extern sint8 *D_8012F74C[];
extern sint8 *D_8012F794[];
extern sint8 *D_8012FF0C[];

extern sint8 *D_8012FF50[];
extern sint8 *D_801314EC[];
extern sint8 *D_8013154C[];
extern STAGE_PART_FUNC D_80132C18[];
extern STAGE_PART_FUNC D_80132C28[];

extern STAGE_PART_FUNC D_801336C0[];

void func_801177AC(ST1A_OBJ *wp);

void func_80106F38(sint32 index);
void func_80106FBC(sint32 index);
void func_80106FF4(sint32 index);

extern ST1A_SCENE_FUNC *D_80132370[];

void func_80117758(ST1A_OBJ *wp);

extern void *D_8012DAFC[];
extern void *D_8012E0E0[];
extern void *D_8012E4CC[];
extern uint8 D_8012E510[][0x28];
extern uint8 D_8012E7B8[][8];
extern sint32 D_8012E810[];
extern sint32 D_8012CF28[];
void Pl00_shot_enable_off(void *pl);
void Pl00_shot_enable_on(void *pl);

void func_8003187C(void *wp);

void func_80115828(STAGE_OBJ *wp, STAGE_FACE *face);
void func_801165FC(STAGE_OBJ *wp, STAGE_FACE *face);

void func_80116E50(STAGE_OBJ *wp);
void func_80117658(STAGE_OBJ *wp);

// Player_work's face shapes (mouth and eyes) at +0x168.
typedef struct
{
    uint8 reserved00[0x168]; // 000
    sint8 mouth_168;         // 168
    sint8 eyes_169;          // 169
} ST1A_PL_FACE;

typedef struct
{
    sint8 shape_0;       // 0
    sint8 prev_1;        // 1
    sint8 index_2;       // 2
    sint8 shape_3;       // 3
    sint8 prev_4;        // 4
    sint8 index_5;       // 5
    uint8 reserved06[2]; // 6
    sint8 *mouth_8;      // 8
    sint8 *eyes_C;       // C
} ST1A_FACE2;

void func_801024A8(void);
void func_80103A4C(void);

// A 0x50-byte slot with a matrix at +0x18 and a rotation at +0x48 (func_80125438 builds the
// matrix from it).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 value_1;          // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[2];    // 04
    uint8 flags_6;          // 06
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 angle_C;          // 0C: in 64ths of a turn (func_8012642C)
    sint8 value_D;          // 0D
    sint8 value_E;          // 0E
    uint8 reserved0F[9];    // 0F
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    sint32 color_40;        // 40
    void *link_44;          // 44: the paired slot
    STCOM_SVECTOR rot_48;   // 48
} ST1A_50;
typedef void (*ST1A_50_FUNC)(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot);
extern ST1A_50_FUNC D_80133234[];
void func_80125438(ST1A_50 *wp, STCOM_SVECTOR *rot);
// Second-level tables, reached from D_80133234[1] and D_801335C0[1] with the same arguments
extern ST1A_50_FUNC D_8013323C[];
void func_80124BA8(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot);
extern ST1A_50_FUNC D_801335C8[];
void func_801262EC(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot);

extern ST1A_50_FUNC D_801335C0[];
void func_80126224(ST1A_50 *wp);
void func_8012800C(STAGE_FX *wp);
void func_8012C2EC(STAGE_EV *wp);

void func_80122C5C(STAGE_OBJ *wp);

void func_801144C8(STAGE_OBJ *wp, STAGE_FACE *face);
void func_80114B70(STAGE_OBJ *wp, STAGE_FACE *face);

void func_801176FC(STAGE_OBJ *wp, sint32 anim);

// A talking face, with a byte kept in the padding after its fields (r3_st1a's talkers).
typedef union
{
    STAGE_FACE face;
    struct
    {
        uint8 reserved00[0x12];
        uint8 value_12; // 12
    } b;
} ST1A_TALK;

void func_80115A90(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk);

void func_801157D8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80115800(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);

// ---- ported declarations
// A view of the work slots r3_st1d's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST1A_VIEW ST1A_VIEW;

struct ST1A_VIEW
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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
    sint32 value_78;        // 78
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
    uint8 value_FB;         // FB
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
    STCOM_SVECTOR vec_180;    // 180
    STCOM_SVECTOR vec_188;    // 188
    STCOM_SVECTOR vec_190;    // 190
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
    union
    {
        uint8 b[4];
        uint16 h[2];
        sint32 w[1];
    } u_328; // 328
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_32C; // 32C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_330;                // 330
    STCOM_SVECTOR vec_334;  // 334
    sint32 value_33C;       // 33C
    STCOM_SVECTOR vec_340;  // 340
    uint8 reserved348[0x2]; // 348
    uint16 value_34A;       // 34A
    uint8 reserved34C[0x2]; // 34C
    union
    {
        uint8 b[2];
        sint16 h[1];
    } u_34E; // 34E
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_350;                // 350
    sint32 value_354;       // 354
    uint8 reserved358[0x4]; // 358
    sint16 value_35C;       // 35C
    sint16 value_35E;       // 35E
    sint16 value_360;       // 360
    uint8 reserved362[0x2]; // 362
    uint16 value_364;       // 364
    uint8 reserved366[0x2]; // 366
    sint32 value_368;       // 368
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_36C;          // 36C
    sint32 value_370; // 370
    sint32 value_374; // 374
    sint32 value_378; // 378
    sint32 value_37C; // 37C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_380;                 // 380
    uint8 value_384;         // 384
    sint8 value_385;         // 385
    sint8 value_386;         // 386
    uint8 value_387;         // 387
    uint8 reserved388[0xD];  // 388
    uint8 value_395;         // 395
    uint8 reserved396[0x16]; // 396
    sint16 value_3AC;        // 3AC
    uint8 reserved3AE[0x4];  // 3AE
    uint16 value_3B2;        // 3B2
    uint8 value_3B4;         // 3B4
    uint8 reserved3B5[0x43]; // 3B5
    sint32 value_3F8;        // 3F8
    uint8 reserved3FC[0x4];  // 3FC
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

extern STAGE_SLOT_FUNC D_80131F14[];
void func_8010FFD8(ST1A_VIEW *wp);

void func_80110EB8(ST1A_VIEW *wp);

// ---- ported declarations
// A view of the work slots r3_st13's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST1A_VIEW_B ST1A_VIEW_B;

struct ST1A_VIEW_B
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
        sint32 w[1];
    } u_514; // 514
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_518;                 // 518
    uint16 value_51C;        // 51C
    sint16 value_51E;        // 51E
    uint8 reserved520[0x84]; // 520
};

void func_80116D48(ST1A_VIEW_B *wp);

// ---- ported declarations
// A view of the work slots r3_st13's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST1A_VIEW_C ST1A_VIEW_C;

struct ST1A_VIEW_C
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
        sint32 w[1];
    } u_514; // 514
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_518;                 // 518
    uint16 value_51C;        // 51C
    sint16 value_51E;        // 51E
    uint8 reserved520[0x84]; // 520
};

void func_80117430(ST1A_VIEW_C *wp);

void func_8011072C(ST1A_VIEW *wp);

void func_80110C64(ST1A_VIEW *wp);

// A 0x3C0-byte slot that follows another slot's state (func_80127EA4).
typedef struct ST1A_FOLLOWER ST1A_FOLLOWER;

struct ST1A_FOLLOWER
{
    uint8 flags_0;           // 00
    uint8 reserved01[7];     // 01
    uint8 routine_0;         // 08
    uint8 reserved09[5];     // 09
    sint8 value_E;           // 0E
    uint8 reserved0F[0x31];  // 0F
    sint32 value_40;         // 40
    ST1A_FOLLOWER *owner_44; // 44
};

// STAGE_ROOM with the effects the room handlers keep from +0x98 (func_8010282C sets fx_A0).
typedef struct
{
    uint8 reserved00[5];    // 00
    uint8 routine_5;        // 05
    uint8 routine_6;        // 06
    uint8 reserved07[9];    // 07
    sint32 frame_10;        // 10
    uint8 reserved14[0x10]; // 14
    STAGE_OBJ *child_24;    // 24
    STAGE_OBJ *child_28;    // 28
    STAGE_OBJ *child_2C;    // 2C
    uint8 reserved30[0x68]; // 30
    STAGE_FX *fx_98;        // 98
    STAGE_FX *fx_9C;        // 9C
    STAGE_FX *fx_A0;        // A0
} ST1A_ROOM_FX;

// The room script work with its driven objects as an array (STAGE_ROOM's child_24..child_60).
typedef struct
{
    uint8 reserved00[5];    // 00
    uint8 routine_5;        // 05
    uint8 routine_6;        // 06
    uint8 reserved07[3];    // 07
    uint8 flags_A;          // 0A: bit 7: skipping off
    uint8 reserved0B[5];    // 0B
    sint32 frame_10;        // 10
    uint8 reserved14[0x10]; // 14
    STAGE_OBJ *child[20];   // 24
} ST1A_ROOM;

// A 0x3C0-byte villager slot driven by the scene, with a talking face at +0x348 (STAGE_OBJ's fields).
typedef struct
{
    sint8 flags_0;    // 00
    uint8 value_1;    // 01
    uint8 kind_2;     // 02
    uint8 variant_3;  // 03
    uint8 value_4;    // 04
    uint8 reserved05; // 05
    uint8 flags_6;    // 06
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
    uint8 routine_1;  // 09
    uint8 routine_2;  // 0A
    uint8 routine_3;  // 0B
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
    sint16 value_50;                        // 50: with value_4C, the acceleration
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98: current animation frame
    uint8 reserved9C[0x8];                  // 9C
    uint8 value_A4;                         // A4
    uint8 reservedA5[0x2];                  // A5
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2: life_6E before this frame's hits
    uint8 reservedB4[0x48];                 // B4
    uint8 face_FC;                          // FC
    uint8 reservedFD[0x3];                  // FD
    uint8 value_100;                        // 100
    uint8 reserved101[0xF];                 // 101
    uint8 value_110;                        // 110
    uint8 reserved111[0x3];                 // 111
    uint8 blink_114;                        // 114
    uint8 reserved115[0x33];                // 115
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x26];                // 160
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[2];                   // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[0x3C];                // 30C
    STAGE_FACE face_348;                    // 348 (0x14 bytes)
    uint8 reserved35C[0x64];                // 35C
} ST1A_NPC;

typedef void (*ST1A_NPC_FUNC)(ST1A_NPC *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);

extern ST1A_NPC_FUNC D_80131DC8[];
extern sint32 D_80131DFC[];

extern STAGE_PART_FUNC D_80132C20[];
void func_80117950(STAGE_OBJ *wp, STAGE_FACE2 *face);

void func_8012806C(ST1A_50 *wp);

// Sets a face's mouth and eye scripts as one statement (the do-while changes func_80118270's
// register allocation; found by the permuter).
#define ST1A_FACE_SCRIPTS(face, mouth, eyes)                                                                                               \
    do                                                                                                                                     \
    {                                                                                                                                      \
        func_80117910(face, mouth);                                                                                                        \
        func_80117930(face, eyes);                                                                                                         \
    } while (0)

// A 0x3C0-byte slot with a talking face's scripts at +0x348 (func_8011259C).
typedef struct
{
    sint8 flags_0;    // 00
    uint8 value_1;    // 01
    uint8 kind_2;     // 02
    uint8 variant_3;  // 03
    uint8 value_4;    // 04
    uint8 reserved05; // 05
    uint8 flags_6;    // 06
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
    uint8 routine_1;  // 09
    uint8 routine_2;  // 0A
    uint8 routine_3;  // 0B
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
    sint16 value_50;                        // 50: with value_4C, the acceleration
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98: current animation frame
    uint8 reserved9C[0x8];                  // 9C
    uint8 value_A4;                         // A4
    uint8 reservedA5[0x2];                  // A5
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2: life_6E before this frame's hits
    uint8 reservedB4[0x4C];                 // B4
    uint8 value_100;                        // 100
    uint8 reserved101[0xF];                 // 101
    uint8 value_110;                        // 110
    uint8 reserved111[0x37];                // 111
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x26];                // 160
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[2];                   // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[0x3C];                // 30C
    STAGE_FACE2 face_348;                   // 348
    uint8 reserved358[0x68];                // 358
} ST1A_TALKER;

typedef void (*ST1A_TALKER_FUNC)(ST1A_TALKER *wp, STAGE_FACE2 *face);

extern ST1A_TALKER_FUNC D_801321F8[];
void func_80111F80(ST1A_TALKER *wp, STAGE_FACE2 *face);

// ST1A_10C as func_801218D0 sees it: eight 8-byte pieces from +0xCC.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved4;                        // 04
    uint8 value_5;                          // 05
    uint8 value_6;                          // 06
    uint8 value_7;                          // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 id_C;                             // 0C: the owner's slot id (func_80036294)
    sint8 value_D;                          // 0D
    sint8 value_E;                          // 0E
    sint8 value_F;                          // 0F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44: a piece's step, in 1/256
    uint8 reserved4C[0x2];                  // 4C
    sint16 value_4E;                        // 4E
    sint32 value_50;                        // 50
    uint8 reserved54[0x2];                  // 54
    sint16 value_56;                        // 56
    sint32 value_58;                        // 58
    uint8 reserved5C[0x2];                  // 5C
    sint16 value_5E;                        // 5E
    uint8 reserved60[0x6];                  // 60
    sint16 value_66;                        // 66
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    sint32 value_78;                        // 78
    uint8 reserved7C[0x4];                  // 7C
    sint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    sint32 value_88;                        // 88
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC
    sint32 color_B4;                        // B4
    sint32 value_B8;                        // B8
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    STCOM_SVECTOR_W piece_CC[8];            // CC: per piece; the top byte of words[0] marks it live
} ST1A_PIECES;

sint32 func_801218D0(ST1A_PIECES *wp);

// A floor rectangle in 512-unit cells: its corner and size (func_8012C1C0).
typedef struct
{
    sint8 x_0; // 0
    sint8 z_1; // 1
    uint8 w_2; // 2
    uint8 d_3; // 3
} ST1A_AREA;

sint32 func_8012C1C0(void *wp, ST1A_AREA *area);
sint32 func_8012C228(STAGE_EV *wp);
void *func_80031498(void);

typedef struct ST1A_VIEW_D ST1A_VIEW_D;

struct ST1A_VIEW_D
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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
    uint8 value_FB;         // FB
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

void func_80110CF4(ST1A_VIEW_D *wp);

typedef struct ST1A_VIEW_E ST1A_VIEW_E;

struct ST1A_VIEW_E
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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
    uint8 value_FB;         // FB
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

void func_80110D8C(ST1A_VIEW_E *wp);

typedef struct ST1A_VIEW_F ST1A_VIEW_F;

struct ST1A_VIEW_F
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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
    uint8 value_FB;         // FB
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

sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_80110E20(ST1A_VIEW_F *wp);

// The slot a copy draws (func_80123A64): its parts' positions at +0x180, eight bytes apart (the
// pad halfword is the part's palette, STAGE_PAL).
typedef struct
{
    sint8 flags_0;               // 00
    uint8 reserved01[0xB];       // 01
    uint8 count_C;               // 0C
    uint8 reserved0D;            // 0D
    sint8 flags_E;               // 0E
    sint8 flags_F;               // 0F: 0x80 once it lands, 0x10 hidden
    uint32 value_10;             // 10
    STCOM_SVECTOR position;      // 14
    uint8 reserved1C[0x38];      // 1C
    STCOM_SVECTOR rotation;      // 54
    uint8 reserved5C[0x2C];      // 5C
    void *model_88;              // 88
    STCOM_MATRIX matrix_8C;      // 8C
    uint8 reservedAC[0xD4];      // AC
    STCOM_SVECTOR part_180[24];  // 180: pad is the part's palette color
    STCOM_MATRIX matrix_240[24]; // 240: the parts' matrices
} ST1A_COPY_SRC;

// A 0x10C-byte slot that faces along its velocity and scales by position_AC.pad (func_80122CC8),
// launched from its owner's part 15 (func_80122268).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[2];                    // 01
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B: also the pitch, in 128ths
    sint8 fire_C;                           // 0C: set to launch it at the player
    uint8 reserved0D[7];                    // 0D
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    uint8 reserved54[0x1A];                 // 54
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[0x10];                 // 7C
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC: pad is the scale
    uint32 color_B4;                        // B4
    STCOM_SVECTOR *target_B8;               // B8: what it homes in on
    sint32 value_BC[4];                     // BC
    STCOM_SVECTOR dir_CC;                   // CC
    ST1A_COPY_SRC *owner_D4;                // D4
    uint8 reservedD8[0x34];                 // D8
} ST1A_DART;

sint32 ratan2(sint32 y, sint32 x);

void func_8012642C(ST1A_50 *wp, STCOM_SVECTOR *rot);

void func_8012748C(ST1A_50 *wp);

// A watching face's eye script at +0x348 (func_801125F8's objects): its first halfword is
// cleared with the mode, the second is the animation speed.
typedef struct
{
    sint16 value_0; // 0
    sint16 speed_2; // 2: animation speed
    sint8 *eyes_4;  // 4: shape, then a byte 0x7E (hold) or 0x7F (loop)
    sint8 shape_8;  // 8
    sint8 prev_9;   // 9
    sint8 index_A;  // A
    uint8 mode_B;   // B
} ST1A_EYES;

// A watching object: ST1A_NPC with the eye script at +0x348.
typedef struct
{
    sint8 flags_0;    // 00
    uint8 value_1;    // 01
    uint8 kind_2;     // 02
    uint8 variant_3;  // 03
    uint8 value_4;    // 04
    uint8 reserved05; // 05
    uint8 flags_6;    // 06
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
    uint8 routine_1;  // 09
    uint8 routine_2;  // 0A
    uint8 routine_3;  // 0B
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
    sint16 value_50;                        // 50: with value_4C, the acceleration
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98: current animation frame
    uint8 reserved9C[0x8];                  // 9C
    uint8 value_A4;                         // A4
    uint8 reservedA5[0x2];                  // A5
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2: life_6E before this frame's hits
    uint8 reservedB4[0x48];                 // B4
    uint8 face_FC;                          // FC
    uint8 reservedFD[0x3];                  // FD
    uint8 value_100;                        // 100
    uint8 reserved101[0xF];                 // 101
    uint8 value_110;                        // 110
    uint8 reserved111[0x3];                 // 111
    uint8 blink_114;                        // 114
    uint8 reserved115[0x33];                // 115
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x26];                // 160
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[2];                   // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[0x3C];                // 30C
    ST1A_EYES face_348;                     // 348
    uint8 reserved354[0x6C];                // 354
} ST1A_WATCHER;

typedef void (*ST1A_EYES_FUNC)(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face);

extern ST1A_EYES_FUNC D_80132200[];
extern ST1A_EYES_FUNC D_80132208[];

void func_80112818(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face);

extern ST1A_TALKER_FUNC D_801321D0[]; // by scene: the talker's script step, or NULL

// ST1A_NPC with ST1A_FACE at +0x348.
typedef struct
{
    sint8 flags_0;    // 00
    uint8 value_1;    // 01
    uint8 kind_2;     // 02
    uint8 variant_3;  // 03
    uint8 value_4;    // 04
    uint8 reserved05; // 05
    uint8 flags_6;    // 06
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
    uint8 routine_1;  // 09
    uint8 routine_2;  // 0A
    uint8 routine_3;  // 0B
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
    sint16 value_50;                        // 50: with value_4C, the acceleration
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98: current animation frame
    uint8 reserved9C[0x8];                  // 9C
    uint8 value_A4;                         // A4
    uint8 reservedA5[0x2];                  // A5
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2: life_6E before this frame's hits
    uint8 reservedB4[0x48];                 // B4
    uint8 face_FC;                          // FC
    uint8 reservedFD[0x3];                  // FD
    uint8 value_100;                        // 100
    uint8 reserved101[0xF];                 // 101
    uint8 value_110;                        // 110
    uint8 reserved111[0x3];                 // 111
    uint8 blink_114;                        // 114
    uint8 reserved115[0x33];                // 115
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x26];                // 160
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[2];                   // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[0x3C];                // 30C
    ST1A_FACE face_348;                     // 348
    uint8 reserved35C[0x64];                // 35C
} ST1A_TALKER3;

typedef void (*ST1A_TALKER3_FUNC)(ST1A_TALKER3 *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face);

extern ST1A_TALKER3_FUNC D_80131F80[];

extern STAGE_PART_FUNC D_80132BD4[]; // by scene: the step of func_80118138's object, or NULL

void func_80118138(STAGE_OBJ *wp, STAGE_FACE2 *face);

typedef void (*ST1A_OBJ_FACE_FUNC)(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face);

extern ST1A_OBJ_FACE_FUNC D_80132C30[];

extern STAGE_OBJ_FUNC D_80132DA0[];

void func_801273A0(ST1A_50 *wp);

void *func_80036294(sint32 id); // the work slot with that id

void func_801255CC(ST1A_50 *wp);

// Called without arguments: it reads wp and the scene from a0/a1 as func_80124D94 received them.
void func_801254E8(ST1A_50 *wp, STAGE_SCENE_WORK *scene);
void func_801255CC(ST1A_50 *wp);

void func_80114B20(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80114B48(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);

void func_80121164(ST1A_PIECES *wp);
void func_80121418(ST1A_PIECES *wp);
void func_8001D974(void);

void func_80121164(ST1A_PIECES *wp);
void func_80121418(ST1A_PIECES *wp);
sint32 func_80121710(ST1A_PIECES *wp);
void func_8001D974(void);

// A 0x3C0-byte slot that sends 0x48-byte effects (kind 0x13) from the joint +0x188 of the slot
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
} ST1A_EMITTER;

void func_8011FABC(ST1A_EMITTER *wp);

// A view of the work slots r3_st13's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST1A_VIEW_G ST1A_VIEW_G;

struct ST1A_VIEW_G
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
        sint32 w[1];
    } u_514; // 514
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_518;                 // 518
    uint16 value_51C;        // 51C
    sint16 value_51E;        // 51E
    uint8 reserved520[0x84]; // 520
};

void func_8011FB90(ST1A_EMITTER *wp);

// The block at +0x28 of a drifting spark (ST1A_SPARK).
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
} ST1A_SPARK_CTL;

// A drifting spark (func_801289F4, func_80128B28).
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
    ST1A_SPARK_CTL ctl;  // 28
    uint8 reserved44[4]; // 44
} ST1A_SPARK;

// A texture position.
typedef struct
{
    uint8 u, v;
} ST1A_UV;

extern ST1A_UV D_80138CDC[];
void func_801289F4(ST1A_SPARK *wp);

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
} ST1A_STCOM27_CTL;

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
    uint8 reserved0C;                       // 0C
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
    uint8 reserved7C[0x34];                 // 7C
    sint16 life_max_B0;                     // B0
    sint16 damage_B2;                       // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x380];               // 160
    ST1A_STCOM27_CTL ctl;                   // 4E0
} ST1A_STCOM27_WORK;

void func_80116B78(ST1A_STCOM27_WORK *wp);

sint32 func_80048E6C(void *wp);
void func_80116C10(ST1A_STCOM27_WORK *wp);

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
} ST1A_OBJ_B;

void func_801170E0(STAGE_OBJ *wp);

// From r3_st10 (ST10_ACTOR_CTL), itself from r3_st04.
// A 0x20-byte control block of ST1A_ACTOR (at +0x348 and +0x368).
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
} ST1A_ACTOR_CTL;

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
    ST1A_ACTOR_CTL ctl;                     // 348
    ST1A_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST1A_ACTOR;

void func_801172D8(ST1A_ACTOR *wp);

#ifdef __wasm32__
void func_80047148(void *wp, STCOM_SVECTOR *pos);
#else
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
#endif
void func_80117548(ST1A_STCOM27_WORK *wp);

extern ST1A_OBJ_FACE_FUNC D_801326D8[];
void func_80114CB8(ST1A_OBJ *wp);

extern ST1A_OBJ_FACE_FUNC D_80132870[];
void func_80115970(ST1A_OBJ *wp);

typedef struct ST1A_VIEW_H ST1A_VIEW_H;

struct ST1A_VIEW_H
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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

// The control block at +0x348 of the turning enemy (func_80110090; the view's ext from +0x20).
typedef struct
{
    STCOM_SVECTOR pos_0;  // 348
    sint32 hit_8;         // 350
    sint32 value_C;       // 354
    uint8 reserved10[8];  // 358
    uint8 track_18[0x48]; // 360
    sint32 ground_60;     // 3A8: func_8004B414's result
    sint16 angle_64;      // 3AC: the rotation.y to turn back to
    uint16 value_66;      // 3AE: damage taken since the last stun
    uint8 reserved68[2];  // 3B0
    uint16 rand_6A;       // 3B2
    uint8 flags_6C;       // 3B4
} ST1A_CTL;

// The view's control block at +0x348.
#define ST1A_CTL_OF(wp) ((ST1A_CTL *)((uint8 *)&(wp)->ext + 0x20))

extern STCOM16_KIND **D_80098844;
void func_80036478(void *track, uint8 arg1, uint32 arg2);
void func_80110090(ST1A_VIEW_H *wp);

typedef struct ST1A_VIEW_I ST1A_VIEW_I;

struct ST1A_VIEW_I
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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

sint32 func_8003648C(void *track, void *wp);
extern STAGE_SLOT_FUNC D_80131F20[];
void func_801101F4(ST1A_VIEW_I *wp);

typedef struct ST1A_VIEW_J ST1A_VIEW_J;

struct ST1A_VIEW_J
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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

void func_8011059C(ST1A_VIEW_J *wp);

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
} ST1A_STCOM27_CTL_B;

// stcom27's work slot with its block at +0x4E0 instead of +0x348 (func_80116C10).
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
    ST1A_STCOM27_CTL_B ctl;                 // 4E0
} ST1A_STCOM27_WORK_B;

extern STAGE_SLOT_FUNC D_80132AEC[];
void func_80116874(ST1A_STCOM27_WORK_B *wp);

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
} ST1A_STCOM27_CTL_C;

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
    ST1A_STCOM27_CTL_C ctl;                 // 4E0
} ST1A_STCOM27_WORK_C;

void func_80116780(ST1A_STCOM27_WORK_C *wp);

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
} ST1A_STCOM27_CTL_D;

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
    ST1A_STCOM27_CTL_D ctl;                 // 4E0
} ST1A_STCOM27_WORK_D;

sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
void func_801169B0(ST1A_STCOM27_WORK_D *wp);
sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80116EBC(ST1A_STCOM27_WORK_D *wp);

typedef struct ST1A_VIEW_K ST1A_VIEW_K;

struct ST1A_VIEW_K
{
    sint8 flags_0;                          // 0
    uint8 value_1;                          // 1
    uint8 kind_2;                           // 2
    uint8 variant_3;                        // 3
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

void func_80110F54(ST1A_VIEW_K *wp);

// func_80047148 as func_80110F54 calls it: with two arguments (retail leaves a2 unset).
void func_80047148_2(void *wp, STCOM_SVECTOR *pos) __asm__("func_80047148");

void func_801025F4(sint32 x, sint32 y, sint16 radius, sint16 shade);

void Sce_event_next(void);

sint32 func_80107110(sint32 arg);

// ROCK_NEO.EXE's sound work with the volume at +4 the room scripts fade out.
typedef struct
{
    uint8 reserved00[4];
    sint16 volume_4;
    sint16 volume_6;
    uint8 reserved08[8]; // (over 8 bytes, so not small data to GCC)
} ST1A_SOUND_VIEW;

extern ST1A_SOUND_VIEW Sound_work_view __asm__("Sound_work");

// PsyQ's TILE (a flat rectangle), as func_80103B9C fills it.
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} ST1A_TILE;

// The packet pointer at 0x1F800070 seen as a TILE or a DR_MODE.
#define ST1A_TILE_PTR ((ST1A_TILE **)0x1F800070)
#define ST1A_MODE_PTR ((DR_MODE **)0x1F800070)

sint32 func_80048C60(STCOM_SVECTOR *pos);

void func_8001F580(sint32 arg0, sint32 arg1, sint32 arg2);

extern sint32 D_80139710;

void func_8003697C(void);

extern sint32 D_801396FC;
void Sce_event_timer_clear(void);
void func_80103B9C(uint8 shade);

void func_8010702C(void);

// A 0x50-byte slot (STAGE_50) as func_8010160C raises it.
typedef struct
{
    sint8 flags_0;          // 00
    uint8 reserved01[0x37]; // 01
    STCOM_SVECTOR pos_38;   // 38
    uint8 reserved40[0x10]; // 40
} ST1A_LIFT_50;

// STAGE_ROOM as func_8010160C sees it: three 0x50-byte slots it raises and the object at +0x50.
typedef struct
{
    uint8 reserved00[6];    // 00
    uint8 routine_6;        // 06
    uint8 reserved07[9];    // 07
    sint32 frame_10;        // 10
    uint8 reserved14[0x14]; // 14
    ST1A_LIFT_50 *slot_28;  // 28
    ST1A_LIFT_50 *slot_2C;  // 2C
    uint8 reserved30[0x1C]; // 30
    ST1A_LIFT_50 *slot_4C;  // 4C
    STAGE_OBJ *child_50;    // 50
} ST1A_ROOM_LIFT;

void func_8005D7C0(void);
void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 color);
void func_8005D4D4(void);

// PsyQ's POLY_G3 (a gouraud triangle), as func_801025F4 fills it.
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    u_char r1, g1, b1, pad1;
    short x1, y1;
    u_char r2, g2, b2, pad2;
    short x2, y2;
} ST1A_POLY_G3;

#define ST1A_POLY_G3_PTR ((ST1A_POLY_G3 **)0x1F800070)

void SetSemiTrans(void *p, sint32 abe);

// A work slot seen as its joint positions (func_80103CB8 sparks from a random one).
typedef struct
{
    uint8 reserved00[0x180];      // 00
    STCOM_SVECTOR joints_180[14]; // 180
} ST1A_JOINTS_OBJ;

// STAGE_ROOM with the object func_80104EC8 keeps at +0xA0 (from func_8011F27C).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[4];    // 01
    uint8 routine_5;        // 05
    uint8 reserved06[0x9A]; // 06
    STAGE_OBJ *obj_A0;      // A0
} ST1A_ROOM_A0;

STAGE_OBJ *func_8011F27C(void);
sint32 func_80048D08(sint32 a0, STCOM_SVECTOR *pos);

STAGE_FX *func_8012B320(STCOM_SVECTOR *pos, sint32 frame, sint32 type, sint32 count, sint32 count_28, uint8 attach, uint8 color);

STAGE_FX *func_8012B440(sint16 x, sint16 y, uint8 arg2, sint16 arg3, sint16 arg4, sint16 arg5);

// A sprite frame of func_8012A730's effects: its texture position and frame count.
typedef struct
{
    uint16 u_0;
    uint16 v_2;
    uint8 frames_4;
    uint8 reserved5;
} ST1A_UVF;

extern ST1A_UVF D_80138F00[];
extern ST1A_UVF D_80138F18[];

void func_80129714(STAGE_OBJ *wp);

// The block at +0xBC of a copy slot (ST1A_COPY).
typedef struct
{
    uint16 flags_0;          // BC
    uint16 rand_2;           // BE
    sint16 timer_4;          // C0
    uint8 reserved6[2];      // C2
    sint16 value_8;          // C4
    sint16 timer_A;          // C6
    uint8 reservedC[8];      // C8
    sint32 value_14;         // D0
    uint8 reserved18[0x1C];  // D4
    ST1A_COPY_SRC *owner_34; // F0
    sint32 scale_38;         // F4
    sint32 scale_3C;         // F8
    sint32 scale_40;         // FC
    uint8 reserved44[4];     // 100
    sint16 value_48;         // 104
    uint8 reserved4A[2];     // 106
} ST1A_COPY_CTL;

// A 0x3C0-byte slot drawing another slot's model (func_801231A0): the owner, its scale and color.
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 id_C;                             // 0C: the owner's slot id (func_80036294)
    sint8 value_D;                          // 0D: the owner's part it follows
    uint8 reserved0E[6];                    // 0E
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[2];                    // 44
    sint16 speed_46;                        // 46
    uint8 reserved48[4];                    // 48
    sint16 speed_4C;                        // 4C
    sint16 step_4E;                         // 4E
    uint8 reserved50[4];                    // 50
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    STCOM_MATRIX matrix_8C;                 // 8C: the owner part's matrix
    STCOM_SVECTOR position_AC;              // AC: pad is the part
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    ST1A_COPY_CTL ctl;                      // BC
    uint8 reserved108[0x2B8];               // 108
} ST1A_COPY;

typedef void (*ST1A_COPY_FUNC)(ST1A_COPY *wp);

extern ST1A_COPY_FUNC D_8013317C[]; // routine_1 (func_80123260)

void func_80123260(ST1A_COPY *wp);

// A 0x50-byte slot (STAGE_OBJ50's layout) with two halfwords at +0x44 from D_80138E10 (func_8012A118).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 index_1;         // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03: bit 7, and a type in the low four bits
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    sint8 value_C;         // 0C
    sint8 value_D;         // 0D
    sint8 value_E;         // 0E
    sint8 value_F;         // 0F
    void *model_10;        // 10
    uint8 reserved14[4];   // 14
    STAGE_MATRIX_W matrix; // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    sint16 value_44;       // 44
    sint16 value_46;       // 46
    sint32 value_48;       // 48
    sint32 value_4C;       // 4C
} ST1A_LAMP;

// Two halfwords per entry, four entries per type (func_8012A118).
typedef struct
{
    uint16 value_0;
    uint16 value_2;
} ST1A_PAIR16;

extern ST1A_PAIR16 D_80138E10[][4];

// A 0x10C-byte slot (Open_SHL_WORK) that flies along a halfword velocity until it drops below
// the floor (func_801220D0).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[0x10];                 // 04
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[0x60];                 // 4C
    STCOM_SVECTOR position_AC;              // AC
    uint8 reservedB4[0x58];                 // B4
} ST1A_SHOT;

sint32 func_80048EA4(STCOM_SVECTOR *pos, void *box, sint32 dy, sint32 kind);

// A 0x10C-byte slot of kind 0x33 as the boss spawns it, with a halfword size at +0x2C
// (func_80119B18).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[6];    // 04
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 reserved0C[8];    // 0C
    STCOM_SVECTOR position; // 14
    uint8 reserved1C[0x10]; // 1C
    STCOM_SVECTOR size_2C;  // 2C
    uint8 reserved34[0xD8]; // 34
} ST1A_FLASH;

// ROCK_NEO.EXE. Its callers here saw no prototype: the int result (set in v0) keeps their
// products out of v0.
sint32 func_80036A88(sint32 a0, sint32 a1, sint32 a2, sint32 a3);

// Game_work's word at +0x174 (STAGE_GAME_VIEW names its low halfword).
#define ST1A_GAME_U32(offset) (*(uint32 *)((uint8 *)&Game_work + (offset)))

void func_8001DF10(uint8 *script);

uint32 func_8003AC9C(sint32 idx, uint32 key);

// The timers at +0x1D8 of the turning enemy (func_80110778; STCOM16_STUN's place in stcom16).
typedef struct
{
    sint16 timer_0; // 1D8
    sint16 count_2; // 1DA: shots left
    sint8 delay_4;  // 1DC: frames to the next shot
    uint8 value_5;  // 1DD
    uint8 index_6;  // 1DE: the next shot's direction (0..15)
} ST1A_SHOT_B;

extern STAGE_SLOT_FUNC D_80131F38[];
void func_801110B4(ST1A_VIEW_H *wp, uint8 kind);
void func_80110778(ST1A_VIEW_H *wp);

sint32 Distance_xz(STCOM_SVECTOR *a, STCOM_SVECTOR *b);

void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);

#define ST1A_ABS(x) ((x) >= 0 ? (x) : -(x))

sint32 func_80049C54(STCOM_SVECTOR *pos, STCOM_SVECTOR *prev, void *info, sint32 mask);

STCOM_MATRIX *MulMatrix2(STCOM_MATRIX *m0, STCOM_MATRIX *m1);

void func_80036B00(STCOM_SVECTOR *pos);

// The boss's attack picker at +0x440 of its slot (func_8011C080), over ST1A_HIT.
typedef struct
{
    uint16 flags_0;        // 440: 0x40 alternates the weight tables
    uint16 rand_2;         // 442
    uint8 reserved4[0x6C]; // 444
    sint16 value_70;       // 4B0
    uint8 reserved72[0xA]; // 4B2
    uint8 last_7C;         // 4BC: the last attack
    uint8 count_7D;        // 4BD: how many times in a row
} ST1A_AI;

// The 0x10C-byte slot the aiming boss spawns (func_8011DCD8): it follows a target position.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[8];    // 04
    uint8 fire_C;           // 0C
    uint8 reserved0D[0xAB]; // 0D
    sint16 *target_B8;      // B8
    uint8 reservedBC[0x18]; // BC
    void *owner_D4;         // D4
    uint8 reservedD8[0x34]; // D8
} ST1A_SIGHT;

// The aiming boss's block at +0x440 of its slot (func_8011DCD8), over ST1A_HIT.
typedef struct
{
    STCOM_SVECTOR target_0;    // 440: where it turns to
    uint8 reserved8[0x90];     // 448
    sint16 value_98;           // 4D8
    sint8 value_9A;            // 4DA
    sint8 value_9B;            // 4DB
    sint16 value_9C;           // 4DC
    uint8 reserved9E[6];       // 4DE
    sint16 count_A4;           // 4E4: landings (func_8011D240)
    sint16 value_A6;           // 4E6
    STCOM_SVECTOR start_A8;    // 4E8: where the jump started
    STCOM_FIXED_VECTOR dir_B0; // 4F0
    sint16 timer_C0;           // 500: frames of the jump
    uint8 reservedC2[2];       // 502
    sint16 angle_C4;           // 504
    uint8 reservedC6[2];       // 506
    sint16 timer_C8;           // 508: frames of the charge (func_8011CE4C)
    uint8 reservedCA[2];       // 50A
    sint16 count_CC;           // 50C: frames of the breath (func_8011DE9C)
    uint8 reservedCE[2];       // 50E
    STCOM_EFFECT *fx_D0;       // 510: the breath's glow
    uint8 reservedD4[4];       // 514
    ST1A_SIGHT *sight_D8;      // 518
    uint8 reservedDC[4];       // 51C
    sint32 value_E0;           // 520
} ST1A_AIM;

// The slot a hand piece follows (func_80125628): a position at +0x180 and a matrix at +0x1E8.
typedef struct
{
    uint8 reserved000[0x180]; // 000
    STCOM_SVECTOR pos_180;    // 180
    uint8 reserved188[0x60];  // 188
    STCOM_MATRIX matrix_1E8;  // 1E8
} ST1A_HAND_OWNER;

// A 0x50-byte slot that hangs off its owner's matrix (func_80125628): the angle at +0x48 is a word.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 value_1;          // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 id_C;             // 0C: the owner's slot id (func_80036294)
    uint8 reserved0D[0xB];  // 0D
    STCOM_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
    uint8 reserved44[4];    // 44
    sint32 angle_48;        // 48
    uint8 reserved4C[4];    // 4C
} ST1A_HAND50;

// The flame sprites' sizes and offsets by frame (func_80129EC4).
typedef struct
{
    uint16 w_0;      // 0: the sprite width
    sint16 radius_2; // 2: how far it sits toward the camera
    uint16 rise_4;   // 4: how far above its owner
    uint16 pad_6;    // 6
} ST1A_FLAME;

extern ST1A_UV D_80138D6C[];
extern ST1A_FLAME D_80138DE8[];

// A flying shard of a breaking wall (func_8012A984): a quad from two corners, each moving.
typedef struct
{
    STCOM_SVECTOR pos_0; // 00: the corners (x0, y0, x1, y1)
    STCOM_SVECTOR vel_8; // 08: their steps, 16ths per frame
    uint8 tex_10;        // 10: D_80138F48's texture
    uint8 shade_11;      // 11: how much darker than 0x80
    uint8 pad_12[2];     // 12
} ST1A_SHARD;

// A wall's shards (func_8012A984).
typedef struct
{
    ST1A_SHARD *list_0; // 0
    sint32 count_4;     // 4
} ST1A_SHARD_SET;

// A texture rectangle.
typedef struct
{
    uint8 u, v, w, h;
} ST1A_TEX;

// A 0x48-byte effect slot drawing a wall's shards by variant_3 (func_8012A984).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[2];    // 01
    uint8 variant_3;        // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 reserved09[0x1F]; // 09
    uint32 time_28;         // 28: frames since it started
    uint8 reserved2C[0x1C]; // 2C
} ST1A_SHARDS;

extern ST1A_TEX D_80138F48[];
extern ST1A_SHARD_SET D_801393A0[];

// The boss's attack picker at +0x440 of its slot (func_8011CB80): a phase and the last four moves.
typedef struct
{
    uint8 reserved0[0x9E]; // 440
    sint16 phase_9E;       // 4DE
    uint8 move_A0;         // 4E0: the move just picked
    uint8 move_A1;         // 4E1
    uint8 move_A2;         // 4E2
    uint8 move_A3;         // 4E3
} ST1A_PICK;

sint32 func_8011E9E8(STCOM_SVECTOR *pos);

sint32 func_8011EAC0(STCOM_SVECTOR *pos);

sint32 func_8011EA54(STCOM_SVECTOR *pos);

void func_8011F208(void);

// The boss's damage block at +0x440 of its slot (func_8011C260), over ST1A_HIT.
typedef struct
{
    uint16 flags_0;         // 440: 8 counts stagger damage; 0x800, 0x1000, 0x2000 the cries said
    uint8 reserved2[8];     // 442
    sint16 stagger_A;       // 44A: damage toward the next stagger
    uint8 reservedC[0xC];   // 44C
    sint32 hit_18;          // 458: the damage taken, and kind bits
    uint8 reserved1C[0x58]; // 45C
    sint32 *life_74;        // 4B4: the next life threshold
    sint16 value_78;        // 4B8
    sint16 timer_7A;        // 4BA
} ST1A_DAMAGE;

sint32 func_80042208(void);

sint32 func_8011BD08(ST1A_OBJ *wp, sint32 i);

// A hit record in the boss's block (func_800341BC's): the damage in the low 24 bits, then the
// kind bits.
typedef struct
{
    sint32 damage_0; // 0
    sint32 value_4;  // 4
} ST1A_HIT_REC;

// The breathing boss's block at +0x440 of its slot (func_8011ED6C): its hit records and cry flags.
typedef struct
{
    uint8 reserved0[8];     // 440
    ST1A_HIT_REC hit_8[18]; // 448: by hit sphere (D_80132F90)
    sint16 value_98;        // 4D8
    uint8 reserved9A[0x42]; // 4DA
    uint32 cried_DC;        // 51C: the life thresholds whose cry has played
    sint32 kind_E0;         // 520: the row of D_80133020 and D_80133040 (func_8011EAFC)
} ST1A_HITS;

void func_80030EE8(void *wp, STCOM_SVECTOR *target, sint32 speed);

void func_80030968(void *shot, void *target, sint32 speed, sint32 arg3, sint32 arg4);

// The boss's block at +0x440 of its slot as its setup writes it (func_80119320).
typedef struct
{
    uint16 flags_0;       // 440
    uint8 reserved2[2];   // 442
    sint32 value_4;       // 444
    sint32 value_8;       // 448
    sint32 value_C;       // 44C
    uint8 reserved10[8];  // 450
    sint32 value_18;      // 458
    sint32 value_1C;      // 45C
    uint8 reserved20[8];  // 460
    uint8 track_28[0x2A]; // 468: func_80036478's
    uint8 value_52;       // 492
    uint8 value_53;       // 493
    sint32 value_54;      // 494
    ST1A_10C *part_58[4]; // 498: freed with the boss
    uint8 reserved68[8];  // 4A8
    sint16 value_70;      // 4B0
    uint8 value_72;       // 4B2
    uint8 value_73;       // 4B3
    sint32 *life_74;      // 4B4: the next life threshold
    sint16 value_78;      // 4B8
    sint16 value_7A;      // 4BA
    uint8 value_7C;       // 4BC
    uint8 value_7D;       // 4BD
    uint8 value_7E;       // 4BE
    uint8 value_7F;       // 4BF
} ST1A_BOSS;

void func_80119714(ST1A_OBJ *wp);

// The boss's life thresholds for its cries (func_80119320), at D_80139738.
typedef struct
{
    sint32 life_0[4]; // the next one is ST1A_DAMAGE's life_74
    sint32 end_10;    // -1
} ST1A_LIFE;

extern ST1A_LIFE D_80139738;

extern ST1A_OBJ_FUNC D_80132DAC[];
extern sint32 D_80132DE4[];
extern uint32 D_80132DF0[];

void func_8005D4C0(void);

sint32 func_8011C080(ST1A_OBJ *wp);

sint32 func_8011C260(ST1A_OBJ *wp);

void func_8011BDD8(ST1A_OBJ *wp, uint8 side);

// A spark of the boss's hand charge (func_8011BDD8): shown while the hand's count is within 16 of
// start_0, it closes in on the hand along angle_4.
typedef struct
{
    sint16 start_0; // 0
    sint16 dist_2;  // 2: horizontal distance at the start
    uint16 angle_4; // 4
    sint16 dy_6;    // 6: height at the start
} ST1A_CHARGE;

extern ST1A_CHARGE D_80132DFC[];

// A lamp's flicker parameters by its value_D (func_8012A374): 8 bytes each.
typedef struct
{
    sint16 low_0;  // 0: the brightness it goes out below
    uint16 kick_2; // 2
    sint16 high_4; // 4: full brightness above this
    uint8 reserved6[2];
} ST1A_FLICKER;

// A lamp's fade parameters by its value_D (func_8012A374): 8 bytes each.
typedef struct
{
    sint16 level_0; // 0
    uint8 step_2;   // 2
    uint8 reserved3[5];
} ST1A_FADE;

extern ST1A_FLICKER D_80138E80[];
extern ST1A_FLICKER D_80138EA0[];
extern ST1A_FADE D_80138EC0[];

// A spark's texture rectangle by its value_C (func_8012AE60).
typedef struct
{
    uint8 u, v, w, h;
} ST1A_UVWH;

extern ST1A_UVWH D_801393C0[];

#define ST1A_PL_U16(pl, offset) (*(uint16 *)((uint8 *)(pl) + (offset)))

// A hit sphere of the breathing boss (D_80132F90, func_8011EAFC): its center in a part's frame,
// its radius and the part.
typedef struct
{
    sint16 x, y, z; // 0
    uint8 radius_6; // 6
    uint8 part_7;   // 7
} ST1A_SPHERE_REC;

extern ST1A_SPHERE_REC D_80132F90[18]; // the boss's hit spheres
extern uint32 D_80133020[][4];         // hit kinds of spheres 0-7, by kind_E0 and attack
extern uint32 D_80133040[][4];         // of spheres 8-17

void func_8012751C(ST1A_50 *wp);

#endif
