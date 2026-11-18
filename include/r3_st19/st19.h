#ifndef ST19_H
#define ST19_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom23.h"
#include "stage_common/stcom18.h"

// Byte offset of the wheel life array in ST19_WHEEL_CTL.
#define ST19_WHEEL_LIFE_OFFSET 0x62

// A view of STAGE_OBJ with the fields r3_st19's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint16 value_4;  // 04
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
    uint16 value_50;                        // 50
    uint8 reserved52[0x2];                  // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_64;                // 64
    uint8 reserved68[0x6]; // 68
    sint16 value_6E;       // 6E
    union
    {
        sint8 b[4]; // 73: the hit kind
        sint32 w[1];
    } u_70;                  // 70
    sint32 value_74;         // 74
    void *data_78;           // 78
    uint8 reserved7C[0x4];   // 7C
    sint32 value_80;         // 80
    uint8 reserved84[0x4];   // 84
    void *model_88;          // 88
    sint32 value_8C;         // 8C
    sint16 value_90;         // 90
    sint16 value_92;         // 92
    sint16 value_94;         // 94
    uint8 value_96;          // 96
    uint8 value_97;          // 97
    uint8 *anim_98;          // 98
    sint32 value_9C;         // 9C
    uint8 reservedA0[0x6];   // A0
    uint8 value_A6;          // A6
    sint8 value_A7;          // A7
    uint8 reservedA8[0x4];   // A8
    uint8 anim_AC;           // AC
    uint8 anim_prev_AD;      // AD
    uint8 reservedAE[0x2];   // AE
    sint16 value_B0;         // B0
    sint16 value_B2;         // B2
    uint8 reservedB4[0x8];   // B4
    sint32 value_BC;         // BC
    uint8 reservedC0[0xC];   // C0
    sint32 value_CC;         // CC
    uint8 reservedD0[0x30];  // D0
    STAGE_PART part_100[12]; // 100
    uint8 reserved130[0x18]; // 130
    sint8 value_148[4];      // 148
    uint8 reserved14C[0xC];  // 14C
    STCOM_SVECTOR_W scale;   // 158
    uint8 reserved160[0x8];  // 160
    uint8 value_168;         // 168
    uint8 value_169;         // 169
    uint8 reserved16A[0x16]; // 16A
    uint16 value_180;        // 180
    uint16 value_182;        // 182
    uint16 value_184;        // 184
    STAGE_PAL pal[24];       // 186
    uint8 reserved246[0x2];  // 246
    STAGE_MATRIX matrix_248; // 248
    uint8 reserved268[0x20]; // 268
    STAGE_MATRIX matrix_288; // 288
    uint8 reserved2A8[0x20]; // 2A8
    sint32 value_2C8;        // 2C8
    sint32 value_2CC;        // 2CC
    sint16 value_2D0;        // 2D0
    sint16 value_2D2;        // 2D2
    sint16 value_2D4;        // 2D4
    uint8 reserved2D6[0x2];  // 2D6
    sint16 value_2D8;        // 2D8
    sint16 value_2DA;        // 2DA
    sint16 value_2DC;        // 2DC
    uint8 reserved2DE[0x2];  // 2DE
    sint16 value_2E0;        // 2E0
    sint16 value_2E2;        // 2E2
    sint16 value_2E4;        // 2E4
    uint8 reserved2E6[0xE];  // 2E6
    sint32 value_2F4;        // 2F4
    sint32 value_2F8;        // 2F8
    sint32 value_2FC;        // 2FC
    uint8 track_300[0xC];    // 300: func_80036478
    uint16 value_30C;        // 30C
    uint16 value_30E;        // 30E
    sint32 value_310;        // 310
    sint32 value_314;        // 314
    sint32 value_318;        // 318
    sint32 value_31C;        // 31C
    sint32 value_320;        // 320
    sint32 value_324;        // 324
    sint32 value_328;        // 328
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_32C;                  // 32C: [0], [1] life and its maximum
    sint16 value_330;         // 330
    sint16 value_332;         // 332
    sint16 value_334;         // 334
    uint8 reserved336[0x6];   // 336
    sint16 value_33C;         // 33C
    sint16 value_33E;         // 33E
    uint8 reserved340[0x4];   // 340
    uint16 value_344;         // 344
    sint16 value_346;         // 346
    uint8 reserved348;        // 348
    uint8 value_349;          // 349
    uint8 value_34A;          // 34A
    uint8 value_34B;          // 34B
    uint8 value_34C;          // 34C
    uint8 value_34D;          // 34D
    uint8 reserved34E;        // 34E
    uint8 value_34F;          // 34F
    uint8 reserved350[0x4];   // 350
    uint8 *data_354;          // 354: a 0x38-byte record by variant (func_80107724)
    uint8 *data_358;          // 358
    uint8 value_35C;          // 35C
    uint8 value_35D;          // 35D
    uint16 value_35E;         // 35E
    sint32 value_360;         // 360
    sint16 value_364;         // 364
    sint16 value_366;         // 366
    uint16 value_368;         // 368
    uint8 value_36A;          // 36A
    uint8 reserved36B[0x9];   // 36B
    uint16 *value_374;        // 374: a sound script (id, frames)
    uint16 value_378;         // 378
    uint8 reserved37A[0x2];   // 37A
    sint32 value_37C;         // 37C
    uint8 reserved380[0x8];   // 380
    sint32 value_388;         // 388
    sint32 value_38C;         // 38C
    uint8 reserved390[0x150]; // 390
    STAGE_FACE face;          // 4E0
} ST19_OBJ;

typedef void (*ST19_OBJ_FUNC)(ST19_OBJ *wp);

// A view of STAGE_10C with the fields r3_st19's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint16 value_4;                    // 04
    uint8 value_6;                     // 06
    uint8 value_7;                     // 07
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    uint8 reservedC;                   // 0C
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
    sint16 value_44;                   // 44
    sint16 value_46;                   // 46
    sint16 value_48;                   // 48
    uint8 reserved4A[0x2];             // 4A
    uint16 value_4C;                   // 4C
    uint16 value_4E;                   // 4E
    uint16 value_50;                   // 50
    uint8 reserved52[0x2];             // 52
    sint16 value_54;                   // 54
    sint16 value_56;                   // 56
    sint16 value_58;                   // 58
    uint8 reserved5A[0xA];             // 5A
    sint32 value_64;                   // 64
    uint8 reserved68[0x6];             // 68
    sint16 value_6E;                   // 6E
    uint8 reserved70[0x3];             // 70
    sint8 value_73;                    // 73
    sint32 value_74;                   // 74
    sint32 value_78;                   // 78
    uint8 reserved7C[0x4];             // 7C
    sint32 value_80;                   // 80
    uint8 reserved84[0x4];             // 84
    sint32 value_88;                   // 88
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    sint16 *target_B8;                 // B8: what it flies at
    sint32 value_BC;                   // BC
    uint8 reservedC0[0xC];             // C0
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[0x4];             // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0x26];            // E2
    uint8 value_108;                   // 108
    uint8 reserved109[0x3];            // 109
} ST19_10C;

typedef void (*ST19_10C_FUNC)(ST19_10C *wp);

// A view of STAGE_FX with the fields r3_st19's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint16 value_4;  // 04
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
    sint16 value_44;      // 44
    sint16 value_46;      // 46
} ST19_FX;

typedef void (*ST19_FX_FUNC)(ST19_FX *wp);

// An effect slot with sixteen two-byte trail entries at +0x28 (func_8010FB3C).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    sint8 value_C;         // 0C
    sint8 timer_D;         // 0D
    sint8 frame_E;         // 0E
    sint8 type_F;          // 0F
    uint8 reserved10[0xC]; // 10
    sint16 x_1C;           // 1C
    sint16 y_1E;           // 1E
    sint16 z_20;           // 20
    uint8 reserved22[2];   // 22
    uint16 w_24;           // 24
    uint8 reserved26[2];   // 26
    uint8 trail_28[16][2]; // 28
} ST19_TRAIL;

void func_80108038(STAGE_OBJ *wp);

void func_80104104(STAGE_OBJ *wp);

void func_80105E10(STAGE_OBJ *wp);

void func_80108018(STAGE_OBJ *wp);

void func_8010E798(STCOM_EFFECT *arg0);

void func_80110200(STCOM_EFFECT *arg0);

void func_80110380(STCOM_EFFECT *arg0);

void func_80105390(STAGE_OBJ *wp);

void func_80107608(STAGE_OBJ *wp);

void func_8011251C(STAGE_ROOM *wp);

void func_80112A10(STAGE_ROOM *wp);

void func_80112A38(STAGE_ROOM *wp);

void func_80112A60(STAGE_ROOM *wp);

void func_80112ADC(STAGE_ROOM *wp);

void func_801136DC(STAGE_OBJ *wp);

void func_8011122C(STAGE_ROOM *wp);

void func_80115734(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80117EBC[];
void func_801076E8(STAGE_OBJ *wp);

void func_8010E6D8(STAGE_SPARK *wp);
void func_8010E764(STAGE_SPARK *wp);

extern STAGE_OBJ_FUNC D_801182EC[];
void func_8010E7B8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80118094[];
void func_8010A0BC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80118488[];
void func_8010FB00(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80118480[];
void func_8010FAC4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80118494[];
void func_8010FE88(STAGE_OBJ *wp);

extern STAGE_ROOM2_FUNC D_80118510[];
void func_801103A0(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_80119D50[];
void func_80114BA0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80119D20[];
void func_801141B8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011A3A8[];
void func_80115888(STAGE_OBJ *wp);

void func_80112738(STAGE_ROOM *wp);

void func_801129C8(STAGE_ROOM *wp);

extern uint8 D_80117190[];
void func_80100A38(STAGE_ROOM *wp);

extern uint8 D_801171B8[];
void func_80100A84(STAGE_ROOM *wp);

extern uint8 D_801171C8[];
void func_80100DDC(STAGE_ROOM *wp);

extern uint8 D_801171A0[];
void func_80100E28(STAGE_ROOM *wp);

void func_80107040(STCOM_PL_WORK *arg0);

void func_801070FC(STAGE_OBJ *wp);

void func_801052E8(STAGE_OBJ *wp);

void func_8010533C(STAGE_OBJ *wp);

void func_80107560(STAGE_OBJ *wp);

void func_801075B4(STAGE_OBJ *wp);

void func_80112A88(STAGE_ROOM *wp);

void func_80113BDC(STAGE_OBJ *wp);

void func_801151B8(STAGE_OBJ *wp);

void func_8011520C(STAGE_OBJ *wp);

void func_801152BC(STAGE_OBJ *wp);

void func_801008F0(STAGE_ROOM *wp);

void func_80111144(STAGE_ROOM *wp);

extern uint8 D_80117198[];
void func_80100AD0(STAGE_ROOM *wp);

void func_80115260(STAGE_OBJ *wp);

void func_8010E93C(STAGE_OBJ *wp);

void func_80100C6C(STAGE_ROOM *wp);

void func_80111FE4(uint8 arg0);

void func_80113B78(STAGE_OBJ *wp);

void func_80114800(STAGE_OBJ *wp);

void func_80115154(STAGE_OBJ *wp);

void func_80111EFC(void);
void func_801123F8(STAGE_OBJ *wp);

void func_801126CC(STAGE_ROOM *wp);

void func_80113FA0(STAGE_OBJ *wp);

void func_8011400C(STAGE_OBJ *wp);

void func_80114078(STAGE_OBJ *wp);

void func_80115764(STAGE_OBJ *wp);

void func_801155C0(STAGE_OBJ *wp);

void func_80113F24(STAGE_OBJ *wp);

void func_801149BC(STAGE_OBJ *wp);

void func_801156B8(STAGE_OBJ *wp);

void func_80115634(STAGE_OBJ *wp);

void func_80113CEC(STAGE_OBJ *wp);

void func_80113D78(STAGE_OBJ *wp);

void func_80113E04(STAGE_OBJ *wp);

void func_80113E90(STAGE_OBJ *wp);

void func_80114920(STAGE_OBJ *wp);

void func_80115480(STAGE_OBJ *wp);

void func_801153DC(STAGE_OBJ *wp);

void func_8011551C(STAGE_OBJ *wp);

void func_80114A38(STAGE_OBJ *wp);

void func_80114AEC(STAGE_OBJ *wp);

void func_80113C30(STAGE_OBJ *wp);

void func_80114864(STAGE_OBJ *wp);

void func_80112B04(STAGE_ROOM *wp);

void func_801140E4(STAGE_OBJ *wp);

void func_80112048(STAGE_ROOM *wp);

extern STAGE_SLOT_FUNC *D_80116514[];
extern STAGE_SLOT_FUNC *D_801166A4[];
extern STAGE_SLOT_FUNC D_801166D4[];
extern STAGE_SLOT_FUNC D_8011671C[];
extern STAGE_SLOT_FUNC D_8011679C[];
extern STAGE_SLOT_FUNC D_801167A0[];
extern STAGE_ROOM2_FUNC *D_80116C20[];

extern sint8 *D_80119CCC[];
extern sint8 *D_80119D00[];
extern sint16 *D_80119E68[];
extern sint8 *D_8011A308[];
extern sint8 *D_8011A378[];

extern STAGE_FACE8 D_8011F4B8;
extern sint8 *D_80118FCC[];
extern sint8 *D_80119034[];
void func_80111C08(sint32 index);
// A talking face kept in the stage data, not in a work slot.
extern STAGE_FACE D_8011F4C8;
extern sint8 *D_801196B0[];
extern sint8 *D_801197A8[];
void func_80111E84(sint32 index);
void func_80111EC0(sint32 index);

void func_80106AC0(ST19_OBJ *wp);

void func_80108044(ST19_OBJ *wp);

void func_8010714C(ST19_OBJ *wp);

void func_80104F04(ST19_OBJ *wp);

void func_80108D18(ST19_OBJ *wp);
void func_8010806C(ST19_OBJ *wp);

void func_80104E94(ST19_OBJ *wp);

void func_801067D0(ST19_OBJ *wp);

void func_8005D6E8(ST19_OBJ *);
void func_80107178(ST19_OBJ *wp);

void func_80104F34(ST19_OBJ *wp);

void func_8010A04C(STAGE_OBJ *wp, STAGE_FX *fx);
void func_8010A08C(STAGE_OBJ *wp, STAGE_FX *fx);

extern sint16 *D_80119AE0[];
extern sint16 *D_80119B60[];
void func_801139E4(void *wp, STAGE_FACE16 *face, sint32 index);
void func_80114FC4(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index);

extern uint8 D_80118370[][2];

void func_80111C6C(STAGE_PL_VIEW *pl);

extern uint8 D_801171D0[];
extern uint8 D_801171D8[][8];
void func_8001DEE4(void);
void func_8001E4C4(uint8 *ids, uint8 *flags);

sint32 func_80048E6C(void *wp);
uint8 func_80108CAC(STCOM_SVECTOR a, STCOM_SVECTOR b, sint16 w, sint16 d);
sint32 func_80031BEC(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

extern uint8 D_8011835C[][2];

void func_8001DF10(uint8 *list);
extern uint8 D_801171C0[];

extern STAGE_FX_FUNC D_801184A0[];
extern STAGE_FX_FUNC D_801184A8[];

extern uint8 D_80118530[];
void func_8003187C(void *wp);

// ROCK_NEO scalar declared as an array: GCC then keeps later struct loads after the stores.
extern sint32 D_800BC7D4[];
extern sint16 D_80118E88[];
STAGE_OBJ *func_80031418(void);

extern STAGE_OBJ_FUNC D_80118070[];

void func_80111DE4(sint32 variant);
extern STAGE_FX *D_8011F4A8[];

extern uint8 D_8011851C[];

void func_8001E20C(sint32 flag);

extern STAGE_OBJ_FUNC D_80117AB4[];

extern uint8 D_801190D8[];
extern STAGE_ROOM2_FUNC D_801197C0[];
extern STAGE_SCRIPT_ENTRY D_8011909C[];

extern STAGE_OBJ_FUNC D_80119858[];
void func_80113A2C(STAGE_OBJ *wp, STAGE_FACE16 *face);
extern STAGE_OBJ_FUNC D_80119D68[];
void func_80115008(STAGE_OBJ *wp, STAGE_FACE16 *face);

void Sound_call(sint32 id, sint32 a1, sint32 a2);

extern STAGE_XYZ D_80118388[];

extern STAGE_OBJ_FUNC D_80117BD4[];

extern void *D_80116820[];
extern void *D_80116970[];
extern void *D_80116A88[];
extern uint8 D_80116A98[][0x28];
extern uint8 D_80116B38[][8];
extern sint32 D_80116B90[];

void func_80100780(void);

void func_8002FFC4(STCOM_SVECTOR *pos, STCOM_FIXED_VECTOR *fixed, sint32 angle, sint32 x, sint32 y,
                   sint32 z);

// STCOM_SPRITE's layout, with the direction the 0x10C-byte objects keep at +0x1C.
typedef struct
{
    uint32 mode_0;          // 00
    STCOM_COLOR color_4;    // 04
    sint16 pos_8[3];        // 08: x, y, z
    uint8 value_E;          // 0E
    uint8 value_F;          // 0F
    uint16 value_10;        // 10
    sint16 value_12;        // 12
    uint32 hit_14;          // 14
    sint32 value_18;        // 18
    STCOM_SVECTOR dir_1C;   // 1C
    STCOM_SVECTOR position; // 24
    uint8 reserved2C[8];    // 2C
} ST19_SPRITE;

typedef struct
{
    uint8 flags_0;          // 00: bit 0: done
    uint8 value_1;          // 01
    sint16 random_2;        // 02
    sint16 value_4;         // 04
    sint16 value_6;         // 06
    uint8 reserved08[2];    // 08
    sint16 value_A;         // 0A
    sint16 value_C;         // 0C
    sint8 value_E;          // 0E
    uint8 reserved0F[0x2D]; // 0F
} ST19_PART_D0;

// A 0x10C-byte work slot with a sprite at +0x88 (STCOM06_WORK's layout) and its state at +0xD0.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 byte_C;                           // 0C
    sint8 byte_D;                           // 0D
    sint8 byte_E;                           // 0E
    sint8 byte_F;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    sint16 value_50;                        // 50
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x24];                 // 64
    ST19_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    uint8 reservedD0[4];                    // D0
    STCOM_SVECTOR trail_D4[6];              // D4: the trail's points
    uint8 reserved104[8];                   // 104
} ST19_10C_B;

// ends when its emitter's routine does.
typedef struct ST19_SPARK ST19_SPARK;

struct ST19_SPARK
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
    ST19_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

STCOM_SVECTOR func_8010A78C(ST19_10C_B *wp);
void func_8010A1EC(ST19_10C_B *wp);
void func_8010E7F4(ST19_SPARK *wp);

extern STCOM18_PAIR D_80118058[6];
extern STCOM18_PAIR D_80118064[6];
void func_80109BB4(STCOM18_WORK *wp);
void func_80109D78(STCOM18_WORK *wp);

ST19_SPARK *func_8010E99C(STCOM_SVECTOR *pos, sint32 width, sint32 type, sint32 count, sint32 rise,
                          uint8 hide);

// func_8010E99C as the turret's caller saw it: retail passes no sixth argument there
// (func_80106CF4), so that file's declaration had no prototype.
typedef ST19_SPARK *(*ST19_SPARK_NEW_FUNC)();
#define ST19_SPARK_NEW ((ST19_SPARK_NEW_FUNC)func_8010E99C)

// Game_work's bytes at +0x78 as func_80107724 reads them (through a pointer, so the address is built
// once; the word member lets GCC merge the two byte tests into one masked word load).
typedef struct
{
    sint8 value_0;    // 78
    uint8 value_1;    // 79: 0x19 here
    uint8 value_2;    // 7A
    uint8 reserved3;  // 7B
    sint32 reserved4; // 7C
} ST19_GAME_78;

// Sound_call2 as func_80108D18's file saw it: without a prototype, so the id goes unextended.
typedef void (*ST19_SOUND_CALL2_FUNC)();
#define ST19_SOUND_CALL2 ((ST19_SOUND_CALL2_FUNC)Sound_call2)

void func_8010A6D8(ST19_10C_B *wp);

void func_8010A86C(ST19_10C_B *wp);

void func_8010A0F8(ST19_10C_B *wp);

// An absolute value; the subtraction is written out again for the negative case.
#define ST19_ABS(x) ((x) >= 0 ? (x) : -(x))

// The block at +0x348 of an ST19_OBJ that keeps its home position (func_80107724).
typedef struct
{
    STCOM_SVECTOR pos_0;     // 348
    sint16 rot_8;            // 350
    uint8 reserved0A[2];     // 352
    uint8 *data_C;           // 354: ST19_OBJ's data_354
    uint8 *data_10;          // 358: ST19_OBJ's data_358
    uint8 flags_14;          // 35C
    uint8 hit_15;            // 35D: nonzero while its hit box is live (its stage, func_8010896C)
    uint16 timer_16;         // 35E: frames left in the script step
    sint32 value_18;         // 360: nonzero to stop
    sint16 x_1C;             // 364: the point it walks to
    sint16 z_1E;             // 366
    sint16 value_20;         // 368
    uint8 reserved22[0xA];   // 36A
    uint16 *sound_2C;        // 374: a sound script (id, frames)
    uint16 frames_30;        // 378
    uint8 reserved32[2];     // 37A
    uint32 hit_kind_34;      // 37C
    STCOM_SVECTOR hitpos_38; // 380
    sint32 hit_40;           // 388
} ST19_HOME;

// The 0x10C-byte slot (func_80031518) a spinning car holds in front of it (func_80104124).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 handler_4;                   // 04
    uint8 reserved05[7];               // 05
    sint8 value_C;                     // 0C
    uint8 value_D;                     // 0D
    uint8 reserved0E[6];               // 0E
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    uint8 reserved66[0xA6];            // 66
} ST19_HELD;

// The block at +0x2C8 of an ST19_OBJ (func_801044B4 reaches it through a pointer).
typedef struct
{
    uint8 reserved0[8];         // 2C8
    STCOM_SVECTOR pos_8;        // 2D0: a hit sphere's center (func_80103B3C)
    STCOM_SVECTOR wheel_10[2];  // 2D8: the wheels' hit points
    sint32 hit_20[3][2];        // 2E8: [0] is cleared on setup (func_801039B8)
    uint8 reserved38[0x10];     // 300
    ST19_HELD *held_48;         // 310: the object it carries (func_80104124)
    STCOM_FIXED_VECTOR step_4C; // 314: a shell's step (func_801046A0)
    STCOM_SVECTOR step_5C;      // 324: the same in halfwords
    sint16 life_64[2];          // 32C: by gun
    sint16 angle_68[2];         // 330
    sint16 timer_6C;            // 334
    sint16 value_6E;            // 336
    sint16 value_70;            // 338
    sint16 value_72;            // 33A
    uint8 reserved74[8];        // 33C
    uint16 value_7C;            // 344
    uint8 reserved7E[3];        // 346
    uint8 state_81;             // 349
    uint8 flags_82;             // 34A
    uint8 value_83;             // 34B
    uint8 reserved84;           // 34C
    uint8 value_85;             // 34D
    uint8 timer_86;             // 34E
    uint8 count_87;             // 34F: volleys fired
} ST19_SPIN;

// A STAGE_MATRIX_OBJ with its state bytes named (func_8010FEC4).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 reserved03[5];    // 03
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 index_C;          // 0C
    uint8 value_D;          // 0D
    uint8 value_E;          // 0E
    uint8 value_F;          // 0F
    uint8 reserved10[8];    // 10
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
} ST19_PROP;

// A 16-byte prop placement record (D_801183C0, func_8010FEC4).
typedef struct
{
    sint16 x, y, z;             // 0
    sint16 scale_6;             // 6
    sint16 rot_x, rot_y, rot_z; // 8
    uint8 variant_E[2];         // E
} ST19_PROP_REC;

extern ST19_PROP_REC D_801183C0[];

// The block at +0x2E8 of an ST19_OBJ (func_80105474 reaches it through a pointer).
// A hit record: damage in the low 24 bits (ST19_WHEEL_CTL, ST19_CTL).
typedef struct
{
    uint32 hit;   // damage (low 24 bits) and kind bits
    uint32 value; //
} ST19_WHEEL_HIT;

typedef struct
{
    ST19_SPARK *spark_0[2];     // 2E8: by gun
    ST19_SPARK *spark_8;        // 2F0: the body's
    STCOM_FIXED_VECTOR fixed_C; // 2F4: a gun's position (func_80105E30); a scale (func_801064A0)
    STCOM_SVECTOR pos_1C;       // 304: a hit sphere's center (func_80105818)
    STCOM_SVECTOR rot_24;       // 30C: a shell's rotation (func_801064A0)
    ST19_WHEEL_HIT hit_2C;      // 314: the body's
    ST19_WHEEL_HIT hit_34[3];   // 31C: [0] and [1] the guns'
    uint8 track_4C[0x10];       // 334: func_80036478
    uint8 reserved5C[0xC];      // 344
    sint16 turn_68[4];          // 350: by gun
    sint16 life_70[4];          // 358: by gun
    sint16 random_78;           // 360: a new random number every frame
    uint8 reserved7A;           // 362
    uint8 flags_7B;             // 363: 4 when it should move on (func_80106238)
    sint8 timer_7C;             // 364
    uint8 count_7D;             // 365
    sint8 gun_7E;               // 366: which gun aims
    uint8 cell_7F;              // 367: where it stands (a row of D_80117B04)
    uint8 value_80;             // 368
    uint8 value_81;             // 369
    uint8 value_82;             // 36A: the turret's sound has played (func_8010720C)
} ST19_CTL;

extern ST19_OBJ_FUNC D_80117B38[];

// An object that rides another (func_80104548): its target and the target's fixed position.
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
    uint8 reserved2A8[0x20];                // 2A8
    uint8 trail_2C8[0x40];                  // 2C8: ST19_FOLLOW_CTL's start (func_80104954)
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[8];                   // 30C
    STCOM_FIXED_VECTOR fixed_314;           // 314
    STCOM_SVECTOR target_324;               // 324
    uint8 reserved32C[0x1D];                // 32C
    uint8 value_349;                        // 349
    uint8 reserved34A[3];                   // 34A
    uint8 flags_34D;                        // 34D
    uint8 reserved34E[0x72];                // 34E
} ST19_FOLLOWER;

STAGE_OBJ *func_80036294(sint32 id);
sint32 func_80048E6C(void *wp);
uint8 func_80108CAC(STCOM_SVECTOR a, STCOM_SVECTOR b, sint16 w, sint16 d);
sint32 func_80031BEC(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

void func_80111B1C(sint32 index, uint8 arg1);

// ROCK_NEO's camera request at 0x800C3560 (D_800C3560 to D_800C3571) through its literal
// address: GCC then keeps the stores in order with the loads from the stack table.
typedef struct
{
    sint16 x_0;         // 0
    sint16 y_2;         // 2
    sint16 z_4;         // 4
    uint8 reserved6[4]; // 6
    sint16 angle_A;     // A
    sint8 mode_C;       // C
    sint8 value_D;      // D
    uint8 value_E;      // E
    uint8 value_F;      // F
    uint8 value_10;     // 10
    uint8 value_11;     // 11
} ST19_CAM_REQ;

#define ST19_CAM_REQ_PTR ((ST19_CAM_REQ *)0x800C3560)

extern ST19_OBJ_FUNC D_801179D8[];

// An object that walks to the points of D_80117AD8 (func_801066C0).
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
    uint8 reservedA5;                       // A5
    uint8 flags_A6;                         // A6
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
    uint8 reserved2A8[0x40];                // 2A8
    uint8 ctl_2E8[0x20];                    // 2E8: ST19_CTL's start (func_80106860)
    void *owner_308;                        // 308: the object that spawned it
    STCOM_SVECTOR target_30C;               // 30C
    uint8 reserved314[0x30];                // 314
    sint32 dist_344;                        // 344
    sint32 dist_prev_348;                   // 348
    uint8 reserved34C[0x17];                // 34C
    uint8 flags_363;                        // 363
    uint8 reserved364[3];                   // 364
    uint8 point_367;                        // 367
    uint8 reserved368[0x58];                // 368
} ST19_MOVER;

extern sint16 D_80117AD8[][2]; // points on the floor (x, z)

// A 16-byte spawn point of the falling-debris effect (D_801184B0, func_801100AC).
typedef struct
{
    sint16 x, y, z;     // 0
    uint8 reserved6[2]; // 6
    sint8 w_8;          // 8
    sint8 dx_9;         // 9: per-frame step
    sint8 dy_A;         // A
    sint8 dz_B;         // B
    sint8 dw_C;         // C
    sint8 mask_x_D;     // D: random part of the step
    sint8 mask_y_E;     // E
    sint8 mask_z_F;     // F
} ST19_DEBRIS_REC;

extern ST19_DEBRIS_REC D_801184B0[];

// The block at +0x2C8 of ST19_WHEELS: the two wheels' sparks, positions, hit records and life.
typedef struct
{
    ST19_SPARK *spark_0[2];      // 2C8: by wheel
    uint8 reserved08[8];         // 2D0
    STCOM_SVECTOR wheel_10[2];   // 2D8
    ST19_WHEEL_HIT hit_20[4];    // 2E8: [1] and [2] the wheels'
    void *owner_40;              // 308: the object that spawned it
    uint8 reserved44[0x8];       // 30C
    STCOM_FIXED_VECTOR fixed_4C; // 314
    uint8 reserved5C[6];         // 324
    sint16 life_62[3];           // 32A: [1] and [2] the wheels'
    sint16 wheel_68;             // 330
    sint16 wheel_6A;             // 332
} ST19_WHEEL_CTL;

// An object with two wheel points at +0x2D8 and +0x2E0 (func_80104D38).
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
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joint_180[24];            // 180: joint positions
    uint8 reserved240[8];                   // 240
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x20];                // 2A8
    ST19_WHEEL_CTL ctl;                     // 2C8
    uint8 reserved334[0x8C];                // 334
} ST19_WHEELS;

typedef void (*ST19_WHEELS_FUNC)(ST19_WHEELS *wp);

extern ST19_WHEELS_FUNC D_80117A00[];
void func_80104B80(ST19_WHEELS *wp);

extern STCOM_SVECTOR D_80117EF0[]; // a box center for func_80108CAC

// D_80117EF0 as func_80108DB4 passes it: a plain object (not an array element) whose type was
// still incomplete when it was declared, so GCC does not take the 8-byte struct for small data.
// Each word of the by-value argument then gets its own address register, and CSE keeps them
// relative to one saved register (halves at 0 and 4 through s3, 2 and 6 absolute). The calls
// go through a view of func_80108CAC that takes this type.
typedef struct ST19_BOX ST19_BOX;
#ifdef PORT
#define D_80117EF0_S (*(ST19_BOX *)D_80117EF0) // native: the same object
#else
extern ST19_BOX D_80117EF0_S __asm__("D_80117EF0");
#endif
struct ST19_BOX
{
    sint16 x, y, z, pad;
};
uint8 func_80108CAC_box(ST19_BOX a, STCOM_SVECTOR b, sint16 w, sint16 d) __asm__("func_80108CAC");

// An object that throws sparks from its joints (func_80104FE8).
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
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joint_180[24];            // 180: joint positions
    uint8 reserved240[8];                   // 240
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x60];                // 2A8
    void *owner_308;                        // 308: the object that spawned it
    uint8 reserved30C[0x18];                // 30C
    STCOM_SVECTOR spark_324;                // 324: the last spark's offset from its joint
    uint8 reserved32C[8];                   // 32C
    sint16 timer_334;                       // 334
    uint8 reserved336[0x10];                // 336
    uint8 random_346;                       // 346: a new random number every frame
    uint8 reserved347[0x79];                // 347
} ST19_SPARKER;

// Where a spark appears: a joint and an offset from it (D_80117A64).
typedef struct
{
    uint8 joint_0;       // 0
    uint8 reserved1;     // 1
    STCOM_SVECTOR ofs_2; // 2
} ST19_SPARK_REC;

extern ST19_SPARK_REC D_80117A64[];

typedef struct
{
    uint8 flags_0;          // 00: bit 0: done
    uint8 value_1;          // 01
    uint16 random_2;        // 02
    sint16 value_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 value_A;         // 0A
    sint16 value_C;         // 0C
    uint8 value_E;          // 0E
    uint8 reserved0F;       // 0F
    sint16 dx_10;           // 10
    sint16 dy_12;           // 12
    sint16 dz_14;           // 14
    uint8 reserved16[0x26]; // 16
} ST19_PART_D0_B;

// A 0x10C-byte work slot with a sprite at +0x88 (STCOM06_WORK's layout) and its state at +0xD0.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 byte_C;                           // 0C
    sint8 byte_D;                           // 0D
    sint8 byte_E;                           // 0E
    sint8 byte_F;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    STAGE_FIXED value_4C;                   // 4C
    sint16 value_50;                        // 50
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x24];                 // 64
    ST19_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    ST19_PART_D0_B part_D0;                 // D0
} ST19_10C_C;

// A 0x10C-byte slot's six screen points at +0xD4 (func_8010A298 projects them, func_8010A86C
// draws them).
typedef struct
{
    uint32 xy_0; // 0
    uint32 z_4;  // 4
} ST19_SXYZ;

typedef struct
{
    uint8 reserved00[0xD4]; // 00
    ST19_SXYZ point_D4[6];  // D4
    uint8 reserved104[0x8]; // 104
} ST19_TRAIL_B;

// func_8010A924's 24 spiral sparks: each one flies for 16 frames from its start, spiraling out.
typedef struct
{
    sint16 start_0;  // 0: count_CC when it appears
    sint16 radius_2; // 2
    uint16 angle_4;  // 4
    sint16 height_6; // 6
} ST19_SPIRAL;

extern uint32 D_80118088[];
extern uint32 D_8011807C[];
void func_8010A298(ST19_10C_B *wp);
extern ST19_SPIRAL D_801180A4[24];
void func_8010A924(ST19_10C_C *wp);
void func_8010ABC0(ST19_10C_C *wp);

// A ROCK_NEO record per kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 value_8; // 08: life, in 64ths
    uint8 reserved09;
    uint8 value_A; // 0A: the hit kind
    uint8 value_B; // 0B: a gun's life, in sixteenths
    uint8 life_C;  // 0C: life, in sixteenths
} ST19_KIND;

extern ST19_KIND **D_80098844;
extern uint8 D_801179CC[];
void func_80036478(void *track, uint8 arg1, uint32 arg2);

extern uint8 D_80117BF6[];
extern uint8 D_80117C94[][0x38];
extern uint8 D_80117EB0[];
extern uint8 D_8011F494;
void func_80107DD4(ST19_OBJ *wp);

// The spark a broken wheel gives off (func_80104B80): func_8010E99C's width, type, count and
// rise.
typedef struct
{
    uint8 width;  // 0
    uint8 type;   // 1
    sint16 count; // 2
    sint32 rise;  // 4
} ST19_SPARK_ARGS;

extern ST19_SPARK_ARGS D_80117A5C;
extern ST19_SPARK_ARGS D_80117B30; // a turret's (func_80106CF4)

// Four bytes per joint of a turret, from +0xF8 (func_80106CF4).
typedef struct
{
    uint8 value_0;      // 0
    uint8 reserved1[2]; // 1
    sint8 value_3;      // 3: -1 once the joint's gun is destroyed
} ST19_TURRET_PART;

// The 0x3C0-byte slot of a gun turret (func_80105E30): its two guns sit at joints 4 and 7.
typedef struct
{
    sint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 reserved02[6];               // 02
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    sint8 owner_C;                     // 0C: the object it is mounted on
    uint8 reserved0D[7];               // 0D
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    STAGE_FIXED value_44;              // 44
    uint8 reserved48[0xC];             // 48
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x12];            // 5C
    sint16 life_6E;                    // 6E
    uint8 reserved70[3];               // 70
    sint8 hit_kind_73;                 // 73: the kind it deals on contact
    uint8 reserved74[0xC];             // 74
    uint32 dist_80;                    // 80: squared distance to the player
    uint8 reserved84[0x22];            // 84
    uint8 flags_A6;                    // A6
    sint8 value_A7;                    // A7
    uint8 reservedA8[4];               // A8
    uint8 anim_AC;                     // AC
    uint8 anim_prev_AD;                // AD
    uint8 reservedAE[0x16];            // AE
    STCOM_SVECTOR value_C4;            // C4: a copy of its position (func_80030628)
    uint8 reservedCC[0x2C];            // CC
    ST19_TURRET_PART part_F8[14];      // F8: by joint
    uint8 reserved130[0x50];           // 130
    STCOM_SVECTOR joint_180[8];        // 180
    uint8 reserved1C0[0x128];          // 1C0
    ST19_CTL ctl;                      // 2E8
    uint8 reserved36C[0x54];           // 36C
} ST19_TURRET;

// The 0x10C-byte slot (func_80031518) of a turret's shell (func_8010601C).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 reserved03;                  // 03
    uint8 handler_4;                   // 04
    uint8 reserved05[0xA];             // 05
    uint8 value_F;                     // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    sint16 speed_44;                   // 44
    sint16 speed_46;                   // 46
    sint16 speed_48;                   // 48
    uint8 reserved4A[0x1A];            // 4A
    sint16 angle_64;                   // 64
    uint8 reserved66[0xA6];            // 66
} ST19_SHELL;

void func_80030EE8(void *wp, STCOM_SVECTOR *target, sint32 speed);

extern STAGE_SCRIPT_ENTRY D_80118544[];
extern uint8 D_8011856C[];
extern STAGE_ROOM2_FUNC D_80118D98[];
extern uint8 D_801185BC[];
extern STAGE_ROOM2_FUNC D_80118DA8[];
void func_8001B314(void);
void func_8001F1DC(void);

// D_800BC7F0 read as an array (the same symbol): an array store keeps its place among struct
// stores (func_801103DC).
extern uint8 *D_800BC7F0_A[] __asm__("D_800BC7F0");

// The block at +0x2C8 of a follower that trails its owner (func_80104954).
typedef struct
{
    uint8 reserved0[0x4C];       // 2C8
    STCOM_FIXED_VECTOR fixed_4C; // 314
    STCOM_SVECTOR target_5C;     // 324: the point behind the owner
    sint16 reserved64[4];        // 32C
    sint16 count_6C;             // 334: frames since it started following
    uint8 reserved6E[6];         // 336
    sint16 speed_74;             // 33C: turn speed
    sint16 value_76;             // 33E
    uint8 reserved78[8];         // 340
    uint8 stage_80;              // 348: the next entry of D_80117A50
} ST19_FOLLOW_CTL;

extern sint16 D_80117A44[]; // the turn speed from each stage
extern sint16 D_80117A50[]; // the frame each stage starts

uint32 func_80030628(void *wp, void *other, STCOM_SVECTOR *range, STCOM_FIXED_VECTOR *out,
                     sint32 angle);

// The cells a turret can move to (func_80106238): four neighbours by direction, 0xFF for none.
extern uint8 D_80117B04[][4];

extern uint8 D_80117C64[];
extern sint16 D_80117CC4[][0x1C]; // in D_80117C94's records: the range func_80108CAC checks

extern ST19_OBJ_FUNC D_80117ECC[];

void func_8010896C(ST19_OBJ *wp);

uint8 func_80108DB4(ST19_OBJ *wp);

void func_80051B68(void *wp, sint32 a1, sint32 a2, sint32 a3);

extern uint8 D_80117C54[];
extern uint8 D_80117C74[];

// Where a turret's smoke comes from: a joint and an offset (D_80117B84, by random number).
typedef struct
{
    uint8 joint_0;          // 0
    uint8 reserved1;        // 1
    STCOM_SVECTOR offset_2; // 2
} ST19_SMOKE;

extern ST19_SMOKE D_80117B84[];

void func_8001F158(void);

void func_8003786C(sint32 id);

extern uint8 D_80117ACC[];

// An ST19_OBJ's block at +0x2E8.
#define ST19_OBJ_CTL(wp) ((ST19_CTL *)&(wp)->reserved2E6[2])

// Where a car's guns fire from and their heading (D_80117A14, by volley).
typedef struct
{
    sint16 x;     // 0
    sint16 y;     // 2
    sint16 z;     // 4
    uint16 angle; // 6
} ST19_GUN;

extern ST19_GUN D_80117A14[];

// An ST19_OBJ's joint points from +0x180.
#define ST19_OBJ_JOINT(wp) ((STCOM_SVECTOR *)&(wp)->value_180)

void func_8010FCD4(ST19_TRAIL *wp);

void func_80106CF4(ST19_TURRET *wp);

extern uint8 D_8011F4DC; // the player's value_170 while the scene runs (func_80112D00)

extern uint8 D_8011F4E0; // and value_171

void func_8001F580(sint32 arg0, sint32 arg1, sint32 arg2);

// An ST19_OBJ's joint matrices from +0x1E8 (func_80104124).
#define ST19_OBJ_MATRIX(wp) ((STAGE_MATRIX *)((uint8 *)(wp) + 0x1E8))

sint32 func_80031CA4(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target,
                     sint32 target_rot, sint32 target_range);

void func_80114668(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);

void func_80114690(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);

void func_801146B8(STAGE_OBJ *wp, STAGE_FACE *face);

extern ST19_OBJ_FUNC D_801179E8[]; // by value_349

extern ST19_OBJ_FUNC D_801179FC[]; // by routine_1

extern ST19_OBJ_FUNC D_801179F4[]; // by value_34B

// Joint rotations in the scratchpad that the model code reads (func_80103B3C: the wheels at
// joints 1 and 3; func_80105818: the guns at joints 3 and 6).
#define ST19_SP_ROT ((STCOM_SVECTOR *)0x1F800130)

typedef void (*ST19_TURRET_FUNC)(ST19_TURRET *wp);

extern ST19_TURRET_FUNC D_80117B50[]; // a turret's, by routine_1

extern ST19_TURRET_FUNC D_80117B70[]; // by routine_1 (func_80107090)

extern ST19_TURRET_FUNC D_80117B48[]; // by ctl.count_7D

extern uint8 D_800A395F;

extern uint16 D_80117E8C[][2]; // sound scripts: (id, frames) pairs

void func_80116038(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);

void func_80116060(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);

void func_80116088(STAGE_OBJ *wp, STAGE_FACE *face);

#endif
