#ifndef ST00_H
#define ST00_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom02.h"
#include "stage_common/gte.h"

// Palette slots in a work slot, eight bytes apart from +0x186 (STAGE_PAL with its +4 halfword).
typedef struct
{
    sint16 color;        // 0
    uint8 reserved02[2]; // 2
    uint16 value_4;      // 4
    uint8 reserved06[2]; // 6
} ST00_PAL;

// A view of STAGE_OBJ with the fields r3_st00's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    sint16 value_4;  // 04
    uint8 value_6;   // 06
    uint8 reserved7; // 07
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
    uint8 reserved50[0x4];                  // 50
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        sint32 word; // 64
        struct
        {
            sint16 value_64; // 64
            sint16 value_66; // 66
        } h;
    } u_64;
    uint8 reserved68[0x6];     // 68
    sint16 value_6E;           // 6E
    sint32 value_70;           // 70
    sint32 value_74;           // 74
    uint8 *value_78;           // 78
    uint8 reserved7C[0x4];     // 7C
    sint32 value_80;           // 80
    uint8 reserved84[0x4];     // 84
    void *model_88;            // 88
    sint32 value_8C;           // 8C
    sint32 value_90;           // 90
    sint32 value_94;           // 94
    uint8 *anim_98;            // 98
    sint32 value_9C;           // 9C
    sint32 value_A0;           // A0
    sint32 value_A4;           // A4
    sint32 value_A8;           // A8
    uint8 anim_AC;             // AC
    uint8 anim_prev_AD;        // AD
    uint8 reservedAE[0x2];     // AE
    sint16 value_B0;           // B0
    sint16 value_B2;           // B2
    sint32 value_B4;           // B4
    uint8 reservedB8[0x4];     // B8
    uint16 value_BC;           // BC
    uint8 reservedBE[0x2];     // BE
    sint32 value_C0;           // C0
    sint32 value_C4;           // C4
    uint8 reservedC8[0x8];     // C8
    sint32 value_D0;           // D0
    uint8 reservedD4[0x1C];    // D4
    sint32 value_F0;           // F0
    sint32 value_F4;           // F4
    sint32 value_F8;           // F8
    uint8 reservedFC[0x3];     // FC
    sint8 value_FF;            // FF
    STAGE_PART_S part_100[12]; // 100
    uint8 reserved130[0x18];   // 130
    sint8 value_148[4];        // 148
    uint8 reserved14C[0xC];    // 14C
    STCOM_SVECTOR_W scale;     // 158
    uint8 reserved160[0x20];   // 160
    sint16 value_180;          // 180
    uint16 value_182;          // 182
    sint16 value_184;          // 184
    ST00_PAL pal[24];          // 186
    uint8 reserved246[0x2];    // 246
    STAGE_MATRIX matrix_248;   // 248
    uint8 reserved268[0x20];   // 268
    STAGE_MATRIX matrix_288;   // 288
    uint8 reserved2A8[0xA0];   // 2A8
    uint16 value_348;          // 348
    uint16 value_34A;          // 34A
    sint32 value_34C;          // 34C
    sint32 value_350;          // 350
    uint8 reserved354[0x8];    // 354
    sint32 value_35C;          // 35C
    sint32 value_360;          // 360
    uint8 reserved364[0x6];    // 364
    uint16 value_36A;          // 36A
    uint8 track_36C[0x10];     // 36C: func_80036478
    sint32 value_37C;          // 37C
    sint32 value_380;          // 380
    sint32 value_384;          // 384
    uint8 reserved388[0x158];  // 388
    STAGE_FACE face;           // 4E0
} ST00_OBJ;

typedef void (*ST00_OBJ_FUNC)(ST00_OBJ *wp);

// Scene_work's object slots from +0x24 as r3_st00's view.
typedef struct
{
    uint8 reserved00[0x24]; // 00
    ST00_OBJ *slot_24[32];  // 24
} ST00_SCENE_VIEW;

#define ST00_SCENE (*(ST00_SCENE_VIEW *)&Scene_work)

// A view of STAGE_10C with the fields r3_st00's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    sint16 value_4;                    // 04
    uint8 value_6;                     // 06
    uint8 reserved7;                   // 07
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
    sint32 value_44;                   // 44
    sint32 value_48;                   // 48
    uint16 value_4C;                   // 4C
    uint16 value_4E;                   // 4E
    uint8 reserved50[0x6];             // 50
    sint16 value_56;                   // 56
    sint32 value_58;                   // 58
    sint32 value_5C;                   // 5C
    sint32 value_60;                   // 60
    uint8 reserved64[0x2];             // 64
    sint16 value_66;                   // 66
    uint8 reserved68[0x6];             // 68
    sint16 value_6E;                   // 6E
    sint32 value_70;                   // 70
    sint32 value_74;                   // 74
    sint32 value_78;                   // 78
    uint8 reserved7C[0x4];             // 7C
    sint32 value_80;                   // 80
    uint8 reserved84[0x4];             // 84
    sint32 value_88;                   // 88
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    uint8 reservedB8[0x4];             // B8
    uint16 value_BC;                   // BC
    uint8 reservedBE[0x2];             // BE
    sint32 value_C0;                   // C0
    sint32 value_C4;                   // C4
    uint8 reservedC8[0x4];             // C8
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
    uint8 reservedFC[0x3];             // FC
    uint8 value_FF;                    // FF
    uint8 reserved100[0x3];            // 100
    uint8 value_103;                   // 103
    uint8 reserved104[0x3];            // 104
    sint8 value_107;                   // 107
    uint8 value_108;                   // 108
    uint8 reserved109[0x2];            // 109
    uint8 value_10B;                   // 10B
} ST00_10C;

typedef void (*ST00_10C_FUNC)(ST00_10C *wp);

// A view of STAGE_FX with the fields r3_st00's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    sint16 value_4;  // 04
    uint8 flags_6;   // 06
    uint8 reserved7; // 07
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
    sint32 value_44;      // 44
} ST00_FX;

typedef void (*ST00_FX_FUNC)(ST00_FX *wp);

// The 12-byte slot table at 0x8015C008, loaded with the stage (ROCK_NEO's code_8003ac24 view).
typedef struct
{
    sint32 value_0;     // 0
    uint8 reserved4[8]; // 4
} ST00_SLOT;

#define ST00_SLOTS ((ST00_SLOT *)0x8015C008)

// A box: offsets and size in x and y (func_801159F8). The room's boxes are lists of these
// (D_8011CC9C by room, ended by kind_0 -1); kind_0 picks the handler in D_8011CB24.
typedef struct
{
    sint8 kind_0;        // 0
    sint8 value_1;       // 1: a message (func_80114838)
    sint8 x_2;           // 2
    sint8 y_3;           // 3
    uint16 w_4;          // 4
    uint16 h_6;          // 6
    sint8 state_8;       // 8: 1 once the player is inside (func_801145F4)
    uint8 reserved09[3]; // 9
    sint16 timer_C;      // C: frames the player has stood inside (func_80114E98)
    uint8 reserved0E[2]; // E
} ST00_BOX;

typedef void (*ST00_BOX_FUNC)(STAGE_MATRIX_OBJ *wp, ST00_BOX *box);

// A 0x5A4-byte slot holding two other slots at +0x514 and +0x518 (func_80107F00).
typedef struct
{
    uint8 reserved000[0x514]; // 000
    void *child_514;          // 514
    void *child_518;          // 518
} ST00_PAIR_OBJ;

void func_80112AB4(STAGE_OBJ *wp);

void func_8010CE2C(STAGE_OBJ *wp);

void func_8010D590(STAGE_OBJ *wp);

void func_8010E394(STAGE_OBJ *wp);

void func_80112C70(STAGE_OBJ *wp);

void func_80115E34(STAGE_OBJ *wp);

void func_80116A54(STAGE_OBJ *wp);

void func_80116A68(STAGE_OBJ *wp);

void func_801182AC(STAGE_OBJ *wp);

void func_80112C84(STAGE_OBJ *wp);

void func_801130A8(STAGE_OBJ *wp);

void func_80113804(STAGE_OBJ *wp);

void func_801135E4(STAGE_OBJ *wp);

void func_80104DC8(STAGE_OBJ *wp);

void func_801066B8(STAGE_OBJ *wp);

void func_8010ACE8(STAGE_OBJ *wp);

void func_80110834(STAGE_OBJ *wp);

void func_80116B5C(STCOM_EFFECT *arg0);

void func_801172DC(STCOM_EFFECT *arg0);

void func_80117538(STCOM_EFFECT *arg0);

void func_80117720(STCOM_EFFECT *arg0);

void func_80100A70(STAGE_ROOM *wp);

void func_801017E8(STAGE_ROOM *wp);

void func_80104764(STAGE_OBJ *wp);

void func_8010DC84(STAGE_OBJ *wp);

void func_80101764(STAGE_ROOM *wp);

void func_8010E1E4(STAGE_OBJ *wp);

void func_8010DD04(STAGE_OBJ *wp);

void func_8010EE7C(STAGE_OBJ *wp);

void func_8010086C(STAGE_ROOM *wp);

void func_801008A4(STAGE_ROOM *wp);

void func_80100D04(STAGE_ROOM *wp);

void func_80100E9C(STAGE_ROOM *wp);

void func_80100ECC(STAGE_ROOM *wp);

void func_8010148C(STAGE_ROOM *wp);

void func_801014BC(STAGE_ROOM *wp);

void func_80101598(STAGE_ROOM *wp);

void func_8010180C(STAGE_ROOM *wp);

void func_80101680(STAGE_ROOM *wp);

void func_80101B6C(STAGE_ROOM *wp);

void func_80101DAC(STAGE_ROOM *wp);

void func_80101F44(STAGE_ROOM *wp);

void func_8010CACC(STAGE_OBJ *wp);

void func_8010CB4C(STAGE_OBJ *wp);

void func_8010CC58(STAGE_OBJ *wp);

void func_8010D334(STAGE_OBJ *wp);

void func_8010D430(STAGE_OBJ *wp);

void func_8010D6E8(STAGE_OBJ *wp);

void func_8010EA04(STAGE_OBJ *wp);

void func_8010E31C(STAGE_OBJ *wp);

void func_80100A3C(STAGE_ROOM *wp);

void func_80104730(STAGE_OBJ *wp);

void func_8010CB7C(STAGE_OBJ *wp);

void func_80112AC0(STAGE_OBJ *wp);

void func_8010E2E8(STAGE_OBJ *wp);

void func_80112AF4(STAGE_OBJ *wp);

void func_80116658(STAGE_OBJ *wp);

void func_80116A9C(STAGE_SPARK *wp);
void func_80116B28(STAGE_SPARK *wp);

void func_80100D34(STAGE_ROOM *wp);

void func_80113054(STAGE_FX *wp);

void func_801014EC(STAGE_ROOM *wp);

void func_801016B0(STAGE_ROOM *wp);

void func_80101844(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_8011C440[];
void func_8010CDA8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C47C[];
void func_8010D18C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C48C[];
void func_8010D25C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C498[];
void func_8010D3AC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C4A8[];
void func_8010D4FC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C4C4[];
void func_8010D768(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C6F4[];
void func_8010DE68(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C70C[];
void func_8010E20C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C7C4[];
void func_8010EBA8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C7E4[];
void func_8010EEA4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C7F0[];
void func_8010EF7C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA10[];
void func_80113010(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA28[];
void func_80113130(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA34[];
void func_80113280(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA48[];
void func_801134A8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA58[];
void func_801134E4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA68[];
void func_80113564(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA70[];
void func_801135A0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA78[];
void func_8011372C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CA8C[];
void func_80113768(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CAA0[];
void func_80113B78(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CAB8[];
void func_80113BB4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CAC0[];
void func_80113EA4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CB18[];
void func_80114424(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CCE4[];
void func_80115A4C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CD2C[];
void func_80115E70(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CD54[];
void func_80116B7C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CE74[];
void func_80118FB8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CF48[];
void func_80119398(STAGE_OBJ *wp);

void func_80101620(STAGE_ROOM *wp);

void func_801044B4(STAGE_OBJ *wp);
void func_80104474(STAGE_OBJ *wp);

void func_8010602C(STAGE_OBJ *wp);

void func_8010CD60(STAGE_OBJ *wp);

void func_8010D144(STAGE_OBJ *wp);

void func_8010CF0C(ST00_OBJ *wp);
void func_8010CF60(STAGE_OBJ *wp);
void func_8010CFF8(STAGE_OBJ *wp);

void func_8010D364(STAGE_OBJ *wp);

void func_8010D460(STAGE_OBJ *wp);

void func_8010D6A8(STAGE_OBJ *wp);

void func_8010E9C4(STAGE_OBJ *wp);

void func_8010EDD4(STAGE_OBJ *wp);

void func_8010EAA0(STAGE_OBJ *wp);

void func_8010EEE0(STAGE_OBJ *wp);

void func_8010ECF0(ST00_OBJ *wp);
void func_8010F004(STAGE_OBJ *wp);
void func_8010F074(STAGE_OBJ *wp);

void func_80112994(STAGE_OBJ *wp);

void func_8010F2AC(STAGE_OBJ *wp);
void func_8010F314(STAGE_OBJ *wp);

void func_80115DF4(STAGE_OBJ *wp);

void func_80118264(STAGE_OBJ *wp);
void func_80118518(void);
void func_80118520(STAGE_OBJ *wp);

typedef struct ST00_POINT_FX ST00_POINT_FX;
void func_80118814(ST00_POINT_FX *wp);
void func_80118960(ST00_POINT_FX *wp);
void func_80118AA0(STAGE_OBJ *wp);

void func_8010CBB0(STAGE_OBJ *wp);

void func_8010D210(STAGE_OBJ *wp);

void func_8010D664(STAGE_OBJ *wp);

void func_80113B2C(STAGE_FX *wp);

void func_80100BE8(STAGE_ROOM *wp);

void func_8010CDE4(STAGE_OBJ *wp);

void func_8010D09C(STAGE_OBJ *wp);

void func_8010D1C8(STAGE_OBJ *wp);

void func_8010D3E8(STAGE_OBJ *wp);

void func_8010D2EC(STAGE_OBJ *wp);

void func_8010D61C(STAGE_OBJ *wp);

void func_8010D718(STAGE_OBJ *wp);

void func_8010DEA4(STAGE_OBJ *wp);

void func_8010E34C(STAGE_OBJ *wp);

void func_80117CCC(STAGE_FX *wp);

void func_801008D4(STAGE_ROOM *wp);

void func_8010CA18(STAGE_OBJ *wp);

void func_8010E198(STAGE_OBJ *wp);

void func_8010E29C(STAGE_OBJ *wp);

void func_8010ED88(STAGE_OBJ *wp);

void func_8010EFB8(STAGE_OBJ *wp);

void func_8010F260(STAGE_OBJ *wp);

extern STAGE_FX_FUNC D_8011CAE4[];
void func_80113EE0(STAGE_FX *wp);

void func_801015C8(STAGE_ROOM *wp);

void func_8010C9C8(STAGE_OBJ *wp);

void func_8010CAFC(STAGE_OBJ *wp);

void func_80101794(STAGE_ROOM *wp);

void func_8010CEB8(STAGE_OBJ *wp);

void func_8010D298(STAGE_OBJ *wp);

void func_8010D4A0(STAGE_OBJ *wp);

void func_8010DFB0(STAGE_OBJ *wp);

void func_8010E004(STAGE_OBJ *wp);

void func_8010E058(STAGE_OBJ *wp);

void func_8010E248(STAGE_OBJ *wp);

void func_8010EF20(STAGE_OBJ *wp);

void func_80117FF8(STAGE_FX *wp);
void func_80118190(STAGE_FX *wp);

void func_80115C4C(STAGE_OBJ *wp);

void func_8010CD04(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011CE50[];
void func_80118560(STAGE_OBJ *wp);

void func_8010D0E4(STAGE_OBJ *wp);

void func_8010F140(STAGE_OBJ *wp);

void func_8010F1A0(STAGE_OBJ *wp);

void func_8010F200(STAGE_OBJ *wp);

void func_8010CBF4(STAGE_OBJ *wp);

void func_8010EAE0(STAGE_OBJ *wp);

void func_8010EB44(STAGE_OBJ *wp);

void func_80117D14(STAGE_FX *wp);
void func_80117F94(STAGE_FX *wp);

void func_8010DEEC(STAGE_OBJ *wp);

void func_8010EE14(STAGE_OBJ *wp);

void func_8010EA34(STAGE_OBJ *wp);

void func_80115BD8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C474[];
void func_8010CE40(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C4BC[];
void func_8010D5A4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C6EC[];
void func_8010DD2C(STAGE_OBJ *wp);

void func_801175C4(STAGE_OBJ *wp);

extern uint8 D_800A2D0B;
void func_801009B0(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_8011C72C[];
void func_8010E474(STAGE_OBJ *wp);

void func_8010E0AC(STAGE_OBJ *wp);

extern uint8 D_80122428;
extern uint8 D_8012242C;
extern uint8 D_80122430;
extern uint8 D_80122434;
extern uint8 D_80122438;
void func_80100738(STAGE_ROOM *wp);

void func_80100C30(STAGE_ROOM *wp);

extern STAGE_SLOT_FUNC *D_8011A4D0[];
extern STAGE_SLOT_FUNC *D_8011A5B0[];
extern STAGE_SLOT_FUNC D_8011A5D4[];
extern STAGE_SLOT_FUNC D_8011A604[];
extern STAGE_SLOT_FUNC D_8011A644[];
extern STAGE_SLOT_FUNC D_8011A6CC[];

// Used by functions still in assembly (types from their accesses).

extern sint32 D_8009888C;
extern sint32 D_800988FC;
extern sint32 D_800BC744[];
extern uint32 *D_800BE6D8[];
extern uint8 D_800C3588;
extern uint8 D_801000CC[];
extern sint32 D_8011A0FC[];      // by room (func_8005DC10)
extern void *D_8011A6F0[];       // model table by room (Room_model_init)
extern void *D_8011AB3C[];       // spawn list by room
extern void *D_8011AC40[];       // exit list by room
extern uint8 D_8011AC54[][0x28]; // by room (func_800371A0)
extern uint8 D_8011AD1C[][8];    // by D_8011ADE4[room]
extern sint32 D_8011ADE4[];
extern STAGE_SCRIPT_ENTRY D_8011AE0C[];
extern uint8 D_8011AF4C[];
extern STAGE_ROOM2_FUNC D_8011B2E8[];
extern uint8 D_8011B377[];
extern STAGE_SCRIPT_ENTRY D_8011B388[];
extern uint8 D_8011B4B4[];
extern STAGE_ROOM2_FUNC D_8011BA4C[];
extern STAGE_SCRIPT_ENTRY D_8011BB14[];
extern uint8 D_8011BB3C[];
extern STAGE_ROOM2_FUNC D_8011BE44[];
extern uint8 D_8011BF50[];
extern uint8 D_8011BF5C[];
extern uint8 D_8011C014[];
extern uint8 D_8011C0A4[];
extern sint16 D_8011C0B6;
extern sint16 D_8011C0B8;
extern sint16 D_8011C0BA;
extern sint16 D_8011C0C0;
extern sint16 D_8011C0C2;
extern sint16 D_8011C0C4;
extern sint16 D_8011C0C6;
extern uint16 D_8011C0CC;
extern uint16 D_8011C0CE;
extern uint16 D_8011C0D0;
extern uint16 D_8011C0D2;
extern uint16 D_8011C0F0;
extern uint16 D_8011C0F2;
extern uint16 D_8011C0F4;
extern uint16 D_8011C0F6;
extern sint16 D_8011C12C;
extern sint16 D_8011C12E;
extern sint16 D_8011C130;
extern sint16 D_8011C132;
extern uint8 D_8011C138[];
extern sint16 D_8011C13A;
extern sint16 D_8011C13C;
extern sint16 D_8011C13E;
extern uint8 D_8011C144[];
extern sint16 D_8011C146;
extern sint16 D_8011C148;
extern sint16 D_8011C14A;
extern uint16 D_8011C15C[];
extern sint16 D_8011C168[]; // forward steps (func_80109638)
extern sint16 D_8011C170[]; // forward steps (func_801098F0)
extern uint8 D_8011C1B4[];
extern sint16 D_8011C1C0;
extern sint16 D_8011C1C2;
extern sint16 D_8011C1C4;
extern sint16 D_8011C1C6;
extern uint8 D_8011C1D0[];
extern STAGE_MOUTH_CUE D_8011C338[];
extern STAGE_MOUTH_CUE D_8011C3A4[];
extern STAGE_MOUTH_CUE D_8011C630[];
extern STAGE_MOUTH_CUE D_8011C684[];
extern STAGE_MOUTH_CUE D_8011C798[];
extern STAGE_MOUTH_CUE D_8011C7B0[];
extern uint8 D_8011C880[];
extern uint8 D_8011C918[];
extern uint16 D_8011C940[];
extern uint16 D_8011C942[];
extern uint16 D_8011C944[];
extern uint8 *D_8011C9FC[];
extern uint8 D_8011CA94[][2]; // by frame: u, v (func_8011381C)
extern STCOM_FIXED_VECTOR D_8011CB08[];
extern sint32 D_8011CB0C;
extern sint32 D_8011CB10;
extern ST00_BOX_FUNC D_8011CB24[];
extern ST00_BOX *D_8011CC9C[];
extern sint32 D_8011CCC0[];
extern uint32 D_8011CCE0;
extern sint32 D_8011CD0C[];
extern uint8 D_8011CD14[];
extern uint8 D_8011CD20[];
extern sint32 D_8011CD74[];
extern sint16 D_8011CDA8[];
extern uint8 D_8011CDCC[];
extern uint8 D_8011CDCD[];
extern uint8 D_8011CDCE[];
extern uint8 D_8011CDCF[];
extern uint8 D_8011CE11[];
extern uint8 D_8011CE21[];
extern uint16 D_8011CE22[];
extern sint32 D_8011CE30[];
extern uint32 D_8011CE7C[];
extern STCOM02_STEP *D_8011CF28[]; // palette fade scripts, by index_3 (func_801193D4)

extern uint8 D_80122424;
extern STAGE_FX *D_80122450;
extern STAGE_FX *D_80122454;
extern sint16 D_8012245A;
extern sint16 D_8012245C;
extern STAGE_LIP_CUES D_80122470;
extern STAGE_LIP_CUES D_80122488;
extern STAGE_LIP_CUES D_801224A0;
extern STCOM_SVECTOR D_801224C4;      // the player's position, saved (func_8011085C)
extern STCOM_FIXED_VECTOR D_801224CC; // and its 16.16 copy

extern uint32 D_80122640[6][8];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern sint32 D_80164008[];

void func_80113528(ST00_FX *wp);

void func_8011308C(ST00_FX *wp);

void func_80113544(ST00_FX *wp);

void func_80113390(ST00_FX *wp);

void func_80112B9C(STAGE_OBJ *wp);

extern ST00_OBJ_FUNC D_8011C860[];
void func_801101F8(ST00_OBJ *wp);

void func_80116D00(STAGE_OBJ *wp);

void func_8010DBF0(STAGE_OBJ *wp);

void func_8010E928(STAGE_OBJ *wp);

void func_8010C930(STAGE_OBJ *wp);

void func_80031A4C(void *wp);

extern STAGE_OBJ_FUNC D_8011CA3C[];
void func_8003187C(void *wp);

extern STAGE_OBJ_FUNC D_8011C700[];

extern STAGE_OBJ_FUNC D_8011C718[];

void Sound_call(sint32 id, sint32 a1, sint32 a2);
void func_800398E0(sint32 arg);

// PsyQ's TILE (a flat rectangle), as func_80100614 fills it.
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} ST00_TILE;

void func_80100614(uint8 r, uint8 g, uint8 b, uint16 abr);

// ends when its emitter's routine does.
typedef struct ST00_SPARK ST00_SPARK;

struct ST00_SPARK
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
    ST00_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

void func_80116BB8(ST00_SPARK *wp);

void func_80117B88(STAGE_FX *wp);

void func_801181E4(STAGE_FX *wp);

void func_801184B4(STAGE_FX *wp);

STAGE_FX *func_801185BC(STAGE_OBJ *owner, sint32 x, sint32 y, sint32 z, uint8 variant);

extern STAGE_OBJ_FUNC D_8011BF24[];
void func_80104808(STAGE_OBJ *wp);

extern STAGE_MOUTH *D_8011C2A8[];
extern STAGE_MOUTH *D_80122460[];
// The lip-sync script pointers also read and written as scalars (the same symbols).
extern STAGE_MOUTH *D_80122460_S __asm__("D_80122460");
extern sint16 D_80122464[];
void func_8010C5D0(STAGE_OBJ *wp, sint32 index);

extern STAGE_MOUTH *D_8011C2E0[];
extern STAGE_MOUTH *D_80122468[];
extern STAGE_MOUTH *D_80122468_S __asm__("D_80122468");
extern sint16 D_8012246C[];
void func_8010C644(STAGE_OBJ *wp, sint32 index);

// A one-field struct view of a lip-sync script pointer: its stores then stay ordered against the
// step loads that follow (a scalar store and a struct read do not alias for GCC 2.7).
typedef struct
{
    STAGE_MOUTH *step;
} ST00_MOUTH_STEP;

extern STAGE_MOUTH *D_8011C5CC[];
extern STAGE_MOUTH *D_80122478[];
extern ST00_MOUTH_STEP D_80122478_V __asm__("D_80122478");
#define D_80122478_S (D_80122478_V.step)
extern sint16 D_8012247C[];
void func_8010D8C0(STAGE_OBJ *wp, sint32 index);

extern STAGE_MOUTH *D_8011C5F4[];
extern STAGE_MOUTH *D_80122480[];
extern ST00_MOUTH_STEP D_80122480_V __asm__("D_80122480");
#define D_80122480_S (D_80122480_V.step)
extern sint16 D_80122484[];
void func_8010D934(STAGE_OBJ *wp, sint32 index);

extern STAGE_MOUTH *D_8011C784[];
extern STAGE_MOUTH *D_80122490[];
extern ST00_MOUTH_STEP D_80122490_V __asm__("D_80122490");
#define D_80122490_S (D_80122490_V.step)
extern sint16 D_80122494[];
void func_8010E5F8(STAGE_OBJ *wp, sint32 index);

extern STAGE_MOUTH *D_8011C790[];
extern STAGE_MOUTH *D_80122498[];
extern ST00_MOUTH_STEP D_80122498_V __asm__("D_80122498");
#define D_80122498_S (D_80122498_V.step)
extern sint16 D_8012249C[];
void func_8010E66C(STAGE_OBJ *wp, sint32 index);

// From r3_st09 (STCOM19_MATRIX).
// A matrix whose identity setup writes its halfwords two at a time.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} ST00_STCOM19_MATRIX;

// From r3_st09 (STCOM19_WORK).
// The 0x50-byte work slot of a floor panel that turns over (func_80031734).
typedef struct
{
    uint8 flags_0;              // 00
    uint8 reserved01;           // 01
    uint8 kind_2;               // 02
    uint8 value_3;              // 03: 0xFF for the spawner
    uint8 reserved04[4];        // 04
    uint8 routine_0;            // 08
    uint8 reserved09[2];        // 09
    uint8 timer_B;              // 0B
    sint8 dir_C;                // 0C: rotation.y / 0x400
    uint8 value_D;              // 0D
    uint8 reserved0E[0xA];      // 0E
    ST00_STCOM19_MATRIX matrix; // 18: words[5] and words[6] hold the cell values to restore
    STCOM_SVECTOR pos_38;       // 38
    uint32 color_40;            // 40
    sint32 cell_44;             // 44: index into the room's cell table
    uint8 reserved48[8];        // 48
} ST00_STCOM19_WORK;

void func_801127A0(ST00_STCOM19_WORK *wp);

extern STAGE_UVW D_8011CE10[];
void func_80117D80(STAGE_FX *wp);

extern STAGE_UVW D_8011CE20[];
void func_80118050(STAGE_FX *wp);

void func_8010C6B8(STAGE_OBJ *wp);
void func_8010C820(STAGE_OBJ *wp);
void func_8010D9A8(STAGE_OBJ *wp);
void func_8010DAE0(STAGE_OBJ *wp);
void func_8010E6E0(STAGE_OBJ *wp);
void func_8010E818(STAGE_OBJ *wp);

extern ST00_OBJ_FUNC D_8011CD60[];
extern ST00_OBJ_FUNC D_8011CD68[];

extern ST00_OBJ_FUNC D_8011CD9C[];
extern ST00_OBJ_FUNC D_8011CD94[];
void func_801172FC(ST00_OBJ *wp);
extern ST00_OBJ_FUNC D_8011CDC0[];
extern ST00_OBJ_FUNC D_8011CDC4[];
void func_80117558(ST00_OBJ *wp);

// A slot that lowers a matrix-drawn model (STAGE_MATRIX_OBJ with a 16.16 height at +0xC).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint32 y_C;             // 0C: 16.16
    uint8 reserved10[8];    // 10
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
    STAGE_FIXED value_44;   // 44
} ST00_LOWER;

typedef void (*ST00_LOWER_FUNC)(ST00_LOWER *wp);

// STAGE_ACTOR_CTL with the halfword at +0x34A named.
typedef struct
{
    uint16 flags_0;        // 348
    uint16 value_2;        // 34A: random bits (func_80105D10)
    sint16 timer_4;        // 34C
    uint8 reserved06[2];   // 34E
    sint16 value_8;        // 350
    uint8 reserved0A[0xA]; // 352
    uint32 hit_14;         // 35C: damage in the low 24 bits, kind bits above
} ST00_ACTOR_CTL;

// STAGE_ACTOR as r3_st00's own actors use it (with the player distance at +0x80).
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 reserved01;                       // 01
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
    sint16 value_66;                        // 66
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[4];                    // 7C
    uint32 dist_80;                         // 80: squared distance to the player
    uint8 reserved84[0x28];                 // 84
    uint8 anim_AC;                          // AC
    uint8 reservedAD[3];                    // AD
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST00_ACTOR_CTL ctl;                     // 348
    uint8 reserved360[0x60];                // 360
} ST00_ACTOR;

typedef void (*ST00_ACTOR_FUNC)(ST00_ACTOR *wp);

extern STAGE_OBJ_FUNC D_8011C80C[];
sint32 func_8011974C(STCOM02_WORK *wp);
void func_80119580(STCOM02_WORK *wp);

extern STAGE_OBJ_FUNC D_8011C7DC[];
extern STAGE_OBJ_FUNC D_8011C7FC[];
extern ST00_LOWER_FUNC D_8011CA20[];

// A matrix-drawn slot whose byte at +0xD scales the matrix (func_80112B28).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 index_C;          // 0C
    sint8 scale_D;          // 0D: percent
    uint8 reserved0E[0xA];  // 0E
    STAGE_MATRIX matrix_18; // 18
} ST00_SCALER;

typedef void (*ST00_SCALER_FUNC)(ST00_SCALER *wp);

extern ST00_SCALER_FUNC D_8011C94C[];

void func_80112B28(ST00_SCALER *wp);

// The block at +0x4E0 of the object func_80107F40 runs.
typedef struct
{
    uint16 flags_0;      // 0
    uint8 reserved2[6];  // 2
    sint16 value_8;      // 8
    uint8 reservedA[10]; // A
    uint32 color_14;     // 14: low 24 bits the color
} ST00_GLOW;

// A 0x3C0-byte slot with an ST00_GLOW at +0x4E0 (func_80107F40).
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
    uint8 reserved30C[0xB4];                // 30C
    uint8 ext_3C0[0x120];                   // 3C0
    ST00_GLOW glow_4E0;                     // 4E0
} ST00_GLOW_OBJ;

void func_8011877C(STCOM_SVECTOR *pos, sint32 a1, sint32 a2);

extern ST00_LOWER_FUNC D_8011CA08[];
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);

void func_801128CC(STAGE_PANEL_WORK *wp);

// A scene flag and the music to play while it is set; a flag of 0xFFFF ends the list (D_8011ADF8).
typedef struct
{
    uint16 flag_0; // 0
    uint8 id_2;    // 2
} ST00_FLAG_MUSIC;

extern ST00_FLAG_MUSIC D_8011ADF8[];

// A 0x3C0-byte slot whose rotation is copied as two words (func_8010478C).
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
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR_W rotation_prev;          // 5C
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
    uint8 reserved30C[0xB4];                // 30C
} ST00_MOVER;

typedef void (*ST00_MOVER_FUNC)(ST00_MOVER *wp);

extern ST00_MOVER_FUNC D_8011BF10[];
void Ride_move(STAGE_OBJ *target, void *wp);

extern STAGE_OBJ_FUNC D_8011C4DC[];

void func_8010F0B4(ST00_OBJ *wp);

// STAGE_MATRIX_OBJ with its kind bytes named (func_80112BDC).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 index_C;          // 0C
    sint8 count_D;          // 0D
    sint8 frame_E;          // 0E
    uint8 reserved0F[5];    // 0F
    uint32 model_14;        // 14
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
} ST00_MATRIX_OBJ;

void func_80112BDC(ST00_MATRIX_OBJ *wp);

// A scratchpad halfword func_8010A68C sets before Model_parts_mtx_set_y.
#define ST00_SP_13C (*(uint16 *)0x1F80013C)

void func_801182C0(STAGE_FX *wp);
extern STAGE_STCOM15_FUNC_348 D_8011BF2C[];
void func_80104864(STAGE_STCOM15_WORK_348 *wp);
extern STAGE_STCOM15_FUNC_4E0 D_8011C054[];
void func_801076E8(STAGE_STCOM15_WORK_4E0 *wp);
extern STAGE_STCOM15_FUNC_4E0 D_8011C178[];
void func_8010A68C(STAGE_STCOM15_WORK_4E0 *wp);
void func_8010AD08(STAGE_STCOM15_WORK_4E0 *wp);
void func_8010B8CC(STAGE_STCOM15_WORK_4E0 *wp);
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_8010BDF0(STAGE_STCOM15_WORK_4E0 *wp);
sint32 func_8010C294(STAGE_STCOM15_WORK_4E0 *wp);

// A 0x48-byte effect slot (func_80031618) of kind 9 placed at a point in 16.16 (func_8011877C):
// an emitter (func_80118960) and the puffs it spawns (func_80118648, func_80118814).
struct ST00_POINT_FX
{
    uint8 flags_0;           // 00
    uint8 reserved01;        // 01
    uint8 kind_2;            // 02
    uint8 variant_3;         // 03
    uint8 reserved04[4];     // 04
    uint8 routine_0;         // 08
    uint8 routine_1;         // 09
    uint8 routine_2;         // 0A
    uint8 routine_3;         // 0B
    sint8 value_C;           // 0C
    sint8 value_D;           // 0D
    sint8 value_E;           // 0E: frames
    uint8 reserved0F[9];     // 0F
    uint32 color_18;         // 18
    sint16 x_1C;             // 1C
    sint16 y_1E;             // 1E
    sint16 z_20;             // 20
    uint8 reserved22[2];     // 22
    uint16 w_24;             // 24
    uint8 reserved26[2];     // 26
    STAGE_FIXED x_28;        // 28
    STAGE_FIXED y_2C;        // 2C
    STAGE_FIXED z_30;        // 30
    STAGE_FIXED speed_34;    // 34: the emitter's, grown each frame
    sint16 value_38;         // 38: the angles the puffs fly at
    sint16 value_3A;         // 3A
    ST00_POINT_FX *owner_3C; // 3C: a puff's emitter
    uint8 reserved40[8];     // 40
};

void func_80118648(STCOM_SVECTOR *pos, sint16 a1, sint16 a2, ST00_POINT_FX *owner, uint8 variant);
STCOM_MATRIX *RotMatrixX(sint32 r, STCOM_MATRIX *m);

void func_80113C98(STAGE_MATRIX_OBJ *wp);

void func_80113C30(STAGE_MATRIX_OBJ *wp);

void func_80113D64(STAGE_MATRIX_OBJ *wp);
void func_80113E10(STAGE_MATRIX_OBJ *wp);

// The hit block at +0x2C of ST00_TARGET (over the matrix's translation).
typedef struct
{
    uint16 flags_0;      // 2C: bit 1: hit box on
    uint8 reserved02[2]; // 2E
    uint32 hit_4;        // 30: damage in the low 24 bits, kind bits above
    uint32 value_8;      // 34
} ST00_TARGET_HIT;

// A 0x50-byte slot (func_80031734) that can be shot (func_80113F2C, func_80114370).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01;      // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    uint8 reserved0C[0xC]; // 0C
    union
    {
        STAGE_MATRIX matrix;
        struct
        {
            uint8 reserved00[0x14];
            ST00_TARGET_HIT hit; // 2C
        } h;
    } u_18;               // 18
    STCOM_SVECTOR pos_38; // 38
    sint32 color_40;      // 40
    sint16 life_44;       // 44
    sint16 value_46;      // 46
    uint8 reserved48[8];  // 48
} ST00_TARGET;

// The block at +0x348 of ST00_SPINNER.
typedef struct
{
    uint16 flags_0;         // 348: bit 0: done
    uint8 reserved02[2];    // 34A
    sint16 timer_4;         // 34C
    uint8 reserved06[2];    // 34E
    sint16 value_8;         // 350
    uint8 reserved0A[0x32]; // 352
    sint32 angle_3C;        // 384
    uint8 reserved40[0x38]; // 388
} ST00_SPIN;

// A 0x3C0-byte work slot that spins up and rises (func_8010673C).
typedef struct
{
    sint8 flags_0;            // 00
    uint8 reserved01[7];      // 01
    uint8 routine_0;          // 08
    uint8 routine_1;          // 09
    uint8 routine_2;          // 0A
    uint8 routine_3;          // 0B
    uint8 reserved0C[0xA0];   // 0C
    uint8 anim_AC;            // AC
    uint8 reservedAD[0x52];   // AD
    uint8 value_FF;           // FF
    uint8 reserved100[0x248]; // 100
    ST00_SPIN spin;           // 348
} ST00_SPINNER;

// A 0x50-byte slot (func_80031734) that leaves an effect beside itself, at its angle
// (func_8011668C).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 index_1;       // 01
    uint8 reserved02;    // 02
    uint8 variant_3;     // 03: 0x60 its quarter turn
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B: frames
    uint8 reserved0C[4]; // 0C
    sint32 value_10;     // 10
    uint8 reserved14[4]; // 14
    union
    {
        STCOM_MATRIX m;
        struct
        {
            sint32 rot[5];   // the rotation part, as words
            sint32 t_x;      // 2C
            sint32 angle_30; // 30: the matrix's t[1] holds its angle
            sint32 t_z;      // 34
        } f;
    } matrix_18;           // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    uint8 reserved44[0xC]; // 44
} ST00_ORBIT;

// A 0x3C0-byte work slot that turns and bobs on a sine (func_80106218).
typedef struct
{
    sint8 flags_0;                     // 00
    uint8 reserved01[2];               // 01
    uint8 variant_3;                   // 03: row of D_8011BF60
    uint8 reserved04[4];               // 04
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    uint8 reserved0C[8];               // 0C
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    STAGE_FIXED value_44;              // 44: [0] the speed forward
    sint16 value_48;                   // 48
    uint8 reserved4A[0xA];             // 4A
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x50];            // 5C
    uint8 anim_AC;                     // AC
    uint8 reservedAD[0xAB];            // AD
    STCOM_SVECTOR_W scale;             // 158
    uint8 reserved160[0x78];           // 160
    sint16 spin_1D8;                   // 1D8: turn per frame
    sint16 base_1DA;                   // 1DA: the height bobbed about
    uint8 reserved1DC[4];              // 1DC
    sint16 count_1E0;                  // 1E0
    sint16 period_1E2;                 // 1E2
    sint16 step_1E4;                   // 1E4: angle per count
    sint16 height_1E6;                 // 1E6
    uint8 reserved1E8[0x1D8];          // 1E8
} ST00_SWAY;

void func_80106218(ST00_SWAY *wp);

void func_801129D4(ST00_STCOM19_WORK *wp);

// The player's work slot as func_80112E80 reads it: two hand points and the body matrix.
typedef struct
{
    uint8 reserved00[0x198];  // 000
    STCOM_SVECTOR pos_198;    // 198
    STCOM_SVECTOR hand_1A0;   // 1A0
    uint8 reserved1A8[0x10];  // 1A8
    STCOM_SVECTOR hand_1B8;   // 1B8
    uint8 reserved1C0[0xE0];  // 1C0
    STCOM_MATRIX matrix_2A0;  // 2A0
    uint8 reserved2C0[0x100]; // 2C0
} ST00_PL_HANDS;

STCOM_MATRIX *MulMatrix0(STCOM_MATRIX *m0, STCOM_MATRIX *m1, STCOM_MATRIX *out);

// A 0x10C-byte slot that follows the model of the object spawned with its id (func_80110244).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 id_C;             // 0C: the owner's id (index_1)
    sint8 value_D;          // 0D
    uint8 flags_E;          // 0E
    uint8 reserved0F[0x45]; // 0F
    sint32 value_54;        // 54
    sint32 value_58;        // 58
    uint8 reserved5C[0x8];  // 5C
    sint32 value_64;        // 64
    uint8 reserved68[0x6];  // 68
    sint16 value_6E;        // 6E
    sint32 value_70;        // 70
    sint32 value_74;        // 74
    uint8 *value_78;        // 78
    uint8 reserved7C[0xC];  // 7C
    void *model_88;         // 88
    uint8 reserved8C[0x26]; // 8C
    sint16 value_B2;        // B2
    sint32 color_B4;        // B4
    uint8 reservedB8[0x4];  // B8
    sint16 value_BC;        // BC
    uint8 reservedBE[0x2];  // BE
    sint32 value_C0;        // C0
    sint32 value_C4;        // C4
    uint8 reservedC8[0x8];  // C8
    sint32 value_D0;        // D0
    uint8 reservedD4[0xC];  // D4
    uint8 track_E0[0x10];   // E0
    STAGE_OBJ *owner_F0;    // F0
    sint32 scale_F4;        // F4
    sint32 scale_F8;        // F8
    sint32 scale_FC;        // FC
    uint8 reserved100[0xC]; // 100
} ST00_FOLLOWER;

void func_80036470(void *track);

STAGE_OBJ *func_80036294(sint32 id);

void func_80036478(void *track, uint8 arg1, uint32 arg2);

// A ROCK_NEO record per object kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;        // 08: times 16
    uint8 limit_9;       // 09
    uint8 value_A;       // 0A
    uint8 count_B;       // 0B: shots in a burst (func_8010B1C0)
    uint8 reserved0C[3]; // 0C
    uint8 value_F;       // 0F
} ST00_KIND;

extern ST00_KIND **D_80098844;

// The boss a part follows (func_80036294 of the part's parent_C): its joints' positions and
// matrices.
typedef struct
{
    uint8 reserved00[0x54];      // 00
    STCOM_SVECTOR rotation;      // 54
    uint8 reserved5C[0x124];     // 5C
    STCOM_SVECTOR joint_180[24]; // 180
    STAGE_MATRIX joint_240[1];   // 240: by joint
} ST00_BOSS;

// The block a boss part keeps at +0xBC.
typedef struct
{
    uint16 flags_0;              // BC: 1 resets the routine, 2 hittable, 8 registers its hit box,
                                 // 0x10 follows its joint, 0x40 keeps it on the ground
    uint16 random_2;             // BE: rand()
    uint16 timer_4;              // C0
    uint16 count_6;              // C2: frames, for every other one (func_80110E58)
    uint8 value_8;               // C4: hit flags
    uint8 reserved9;             // C5
    sint16 timer_A;              // C6
    STCOM_SVECTOR pos_C;         // C8: its hit box
    uint32 hit_14;               // D0: damage (low 24 bits) and kind bits
    uint8 reserved18[0xC];       // D4
    uint8 track_24[0x10];        // E0 (func_80036470)
    ST00_BOSS *parent_34;        // F0
    STCOM_FIXED_VECTOR scale_38; // F4
    uint8 reserved48[8];         // 104
} ST00_PART_CTL;

// A part of the boss (a 0x10C-byte slot): it follows one of the boss's joints (index_D), takes
// hits, and falls off when the boss breaks.
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
    sint8 parent_C;                         // 0C: the boss's id
    sint8 index_D;                          // 0D: its joint
    uint8 flags_E;                          // 0E: 1 broken, 0x20 flash, 0x40 falls to the left
    uint8 reserved0F;                       // 0F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
    uint8 reserved7C[0xC];                  // 7C
    void *model_88;                         // 88
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR pos_AC;                   // AC: pad holds index_D
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    ST00_PART_CTL ctl;                      // BC
} ST00_PART;

void func_80110D24(ST00_PART *wp);

// What the box keeps in its matrix's translation (as STCOM22_CTL): flags, a random value and
// its hit bits (func_800341BC).
typedef struct
{
    uint16 flags_0; // 2C: 2 hittable, 4 registers its hit box, 8 resets the color
    uint16 value_2; // 2E: rand(); bit 0 picks func_80047228's drop
    uint32 hit_4;   // 30: damage (low 24 bits) and kind bits
    uint32 value_8; // 34
} ST00_BOX_CTL;

typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
    struct
    {
        sint16 m[3][3];
        sint16 pad;
        ST00_BOX_CTL ctl; // 2C
    } f;
} ST00_BOX_MATRIX;

typedef struct
{
    uint8 flags_0;          // 00
    uint8 index_1;          // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03: low nibble: what breaking it does; high nibble: its size
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 value_B;          // 0B
    sint8 timer_C;          // 0C
    uint8 reserved0D[3];    // 0D
    void *model_10;         // 10
    uint8 reserved14[4];    // 14
    ST00_BOX_MATRIX matrix; // 18
    STCOM_SVECTOR pos_38;   // 38: pad holds the scenario flag it sets
    uint32 color_40;        // 40
    sint16 life_44;         // 44
    sint16 flag_46;         // 46
    uint8 reserved48[8];    // 48
} ST00_BOX_B;

extern STAGE_SLOT_FUNC D_8011CAF0[];
extern sint32 D_8011CAF8[];
extern sint32 D_8011CB00[];
void func_80113FEC(ST00_BOX_B *wp);

// The block at +0x348 of ST00_ACTOR_B (STAGE_ACTOR_CTL with more fields named).
typedef struct
{
    uint16 flags_0;          // 348
    uint16 value_2;          // 34A
    uint16 timer_4;          // 34C
    uint8 reserved06[2];     // 34E
    uint16 value_8;          // 350: or'd into the hit box's kind bits
    sint16 timer_A;          // 352
    STCOM_SVECTOR pos_C;     // 354: the hit box
    uint32 hit_14;           // 35C: damage in the low 24 bits, kind bits above
    sint32 value_18;         // 360
    STCOM_SVECTOR target_1C; // 364: the attacker's position (pad bit 0: from the player?)
    uint8 track_24[0x10];    // 36C (func_80036478)
    union
    {
        STCOM_SVECTOR target;
        sint16 timer[4];          // [1]: an enemy's frames before it bursts
        STCOM_FIXED_VECTOR scale; // the body's scale (flags_0 0x20)
    } u_34;                       // 37C
    uint8 reserved44[0x34];       // 38C
} ST00_ACTOR_CTL_B;

// STAGE_ACTOR as r3_st09's actors use it.
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 index_1;                          // 01
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
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 spin_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[0x28];                 // 7C
    uint8 frame_A4;                         // A4: the animation's frame
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6: animation frame
    uint8 reservedA7[5];                    // A7
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x80];                // 188
    STCOM_MATRIX matrix_208;                // 208: the body's matrix
    uint8 reserved228[0x120];               // 228
    ST00_ACTOR_CTL_B ctl;                   // 348
} ST00_ACTOR_B;

typedef void (*ST00_ACTOR_FUNC_B)(ST00_ACTOR_B *wp);

extern ST00_ACTOR_FUNC_B D_8011C00C[];

sint32 func_8003648C(void *track, void *wp);
sint32 func_80105DEC(ST00_ACTOR_B *wp);
extern ST00_ACTOR_FUNC_B D_8011BF38[];
void func_80104BE4(ST00_ACTOR_B *wp);

sint32 Obj_ceiling_height_get(void *wp);
void func_80104E64(STAGE_STCOM15_WORK_348 *wp);

sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_801050E8(STAGE_STCOM15_WORK_348 *wp);

void func_80105740(STAGE_STCOM15_WORK_348 *wp);

void func_8010AE00(STAGE_STCOM15_WORK_4E0 *wp);

void func_8010AFF8(STAGE_STCOM15_WORK_4E0 *wp);

sint32 Obj_floor_height_get(void *wp);
void func_8010B6C8(STAGE_STCOM15_WORK_4E0 *wp);

void func_8010BED4(STAGE_STCOM15_WORK_4E0 *wp);

// A map position (x, z).
typedef struct
{
    sint16 x, z;
} ST00_XZ;

extern ST00_XZ D_8011C1CC;
extern ST00_XZ D_8011C1C8;
extern STCOM_SVECTOR D_80122458;
void func_8010C070(STAGE_STCOM15_WORK_4E0 *wp);

void func_80104A08(STAGE_STCOM15_WORK_348 *wp);

// The sparks func_80101B9C starts and func_80101DE4 ends.
extern ST00_SPARK *D_8012243C;
extern ST00_SPARK *D_80122440;
extern ST00_SPARK *D_80122444;
extern ST00_SPARK *D_80122448;
extern ST00_SPARK *D_8012244C;

ST00_SPARK *func_80116D60(STCOM_SVECTOR *pos, sint32 width, sint32 type, sint32 count, sint32 rise, uint8 hide);

// STAGE_ROOM with the effect func_80100EFC keeps at +0x64.
typedef struct
{
    uint8 reserved00[0x28];   // 00
    STAGE_OBJ *child_28;      // 28
    uint8 reserved2C[4];      // 2C
    STAGE_OBJ *child_30;      // 30
    uint8 reserved34[0x2C];   // 34
    STAGE_OBJ *child_60;      // 60
    STAGE_FX *fx_64;          // 64
    uint8 reserved68[0x3C];   // 68
    STAGE_ROOM2_FUNC *tbl_A4; // A4
} ST00_ROOM_FX;

// A 0x24-byte event slot (STAGE_EVENT) as func_80100A94 starts it.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 value_4;          // 04
    uint8 value_5;          // 05
    uint8 reserved06[0x1E]; // 06
} ST00_EVENT;

void Sce_flag_off(sint32 flag);

void func_8005D7C0(void);
void func_8005D9EC(void);

// Obj_ceiling_height_get as func_801150CC calls it: the int result compared unnarrowed.
sint32 func_80048E6C_int(void *wp) __asm__("Obj_ceiling_height_get");

sint32 func_8010A448(STAGE_STCOM15_WORK_4E0 *wp);
extern STAGE_STCOM15_FUNC_4E0 D_8011C068[];
void func_8005D6E8(void *wp);
void func_80107B48(STAGE_STCOM15_WORK_4E0 *wp);

void func_80107D04(STAGE_STCOM15_WORK_4E0 *wp);

void func_80107FAC(STAGE_STCOM15_WORK_4E0 *wp);

sint32 func_80031E60(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
extern sint16 D_8011C14C[];
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);
void func_801084D4(STAGE_STCOM15_WORK_4E0 *wp);

// A leg of a walking route (func_801087D0): the turn while it waits, then the area that ends it.
typedef struct
{
    sint16 turn_0;
    uint8 reserved2[2];
    sint16 x_4;
    sint16 z_6;
    sint16 w_8;
    sint16 d_A;
} ST00_ROUTE;

// stcom15's control block as the walking object uses it (func_801087D0): its route at +0x3E.
typedef struct
{
    uint8 reserved00[0x3E];
    sint16 step_3E;
    ST00_ROUTE *route_40;
} ST00_ROUTE_CTL;

extern ST00_ROUTE D_8011C0C8[];
extern ST00_ROUTE D_8011C0F8[];
extern sint16 D_8011C154[];
void func_801087D0(STAGE_STCOM15_WORK_4E0 *wp);

void func_80108C18(STAGE_STCOM15_WORK_4E0 *wp);

void func_80108D48(STAGE_STCOM15_WORK_4E0 *wp);

// The area records from D_8011C0B4 on: a rectangle on the floor and two halfwords. Routines keep
// pointers to record fields, so the table is reached through one symbol.
typedef struct
{
    sint16 x; // 0
    sint16 z; // 2
    sint16 w; // 4
    sint16 d; // 6
    sint16 a; // 8
    sint16 b; // A
} ST00_AREA;

extern ST00_AREA D_8011C0B4[];
#define ST00_AREA_TBL D_8011C0B4

extern ST00_KIND **D_8009884C; // by kind, then by param_D

// A texture record of a loaded set: its CLUT at data_8 (with segment bits above 24).
typedef struct
{
    uint8 reserved00[8]; // 00
    uint32 data_8;       // 08
} ST00_TEX_REC;

// A loaded texture set (Stage_hed_model_get): the two CLUT records the scroller copies and animates.
typedef struct
{
    uint8 reserved00[0x18]; // 00
    ST00_TEX_REC *clut_18;  // 18
    ST00_TEX_REC *clut_1C;  // 1C
} ST00_TEX_SET;

// The 0x24-byte event slot that scrolls the colors of three texture sets (D_8011CE74).
typedef struct
{
    uint8 flags_0;           // 00
    uint8 reserved01[7];     // 01
    uint8 routine_0;         // 08
    uint8 reserved09[2];     // 09
    uint8 timer_B;           // 0B
    sint32 scroll_C;         // 0C
    uint8 reserved10[4];     // 10
    sint32 value_14;         // 14
    ST00_TEX_SET *set_18[3]; // 18
} ST00_CLUT_SCROLL;

// A texture-coordinate animation (func_8011917C): the model key, func_8002DC84's two arguments
// and how many quads to shift.
typedef struct
{
    uint32 key;   // 0
    sint32 i;     // 4
    sint32 j;     // 8
    uint32 count; // C
} ST00_UV_SCROLL;

extern ST00_UV_SCROLL D_8011CE88[4];

extern ST00_ACTOR_FUNC_B D_8011C000[];

// A row of D_8011BF60 (by ST00_SWAY's variant_3): where it starts and how it turns and bobs.
typedef struct
{
    sint16 x;        // 0
    sint16 y;        // 2: also the height bobbed about
    sint16 z;        // 4
    uint16 rot_6;    // 6
    uint16 speed_8;  // 8
    uint16 spin_A;   // A
    uint16 height_C; // C
    uint16 period_E; // E
} ST00_SWAY_DATA;

extern ST00_SWAY_DATA D_8011BF60[];

void func_8010606C(ST00_SWAY *wp);

sint32 SquareRoot0(sint32 v);
sint32 ratan2(sint32 y, sint32 x);

void Cd_read_sync(void);

void func_80117740(STAGE_FX *wp);

// A palette range of r3_st00's blend (func_80119580): Clut_buf[offset], 16 colors; blend 0
// copies whole steps instead.
typedef struct
{
    uint16 offset;
    uint16 blend;
} ST00_PAL_RANGE;

extern ST00_PAL_RANGE D_8011CF38[];

extern STAGE_ACTOR D_8009F108[]; // ROCK_NEO's 0x3C0-byte slots

// stcom15's control block as the paired object uses it (func_8010A448): its two parts at +0x34.
typedef struct
{
    uint8 reserved00[0x34];
    STAGE_OBJ *part_34;
    STAGE_OBJ *part_38;
} ST00_PAIR_CTL;

sint32 func_80042208(void);

// ROCK_NEO: a model's UV block (stcom07's STCOM07_QUAD): u0, v0, u1, v1, u2, v2, u3, v3.
uint8 *Model_face_get(uint32 model, sint32 arg);

void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 color);

// Eight bytes of texture coordinates of a model face (Model_face_get, Model_face_uv_set; r3_st0e's
// ST0E_UV8).
typedef struct
{
    uint8 b[8];
} ST00_UV8;

// A model's part list record (8 bytes; r3_st0e's ST0E_PART_REC).
typedef struct
{
    uint8 reserved0[2]; // 0
    uint16 value_2;     // 2
    uint8 reserved4[4]; // 4
} ST00_PART_REC;

typedef struct
{
    uint8 reserved00[0x24];
    ST00_PART_REC *recs_24; // 24
} ST00_MODEL_PARTS;

// A model as func_80116750 reaches it (r3_st0e's ST0E_MODEL).
typedef struct
{
    uint8 reserved00[0x70];
    ST00_MODEL_PARTS *parts_70; // 70
} ST00_MODEL;

// A 0x50-byte slot of a pool whose surface ripples (func_80116750; r3_st0e's ST0E_PANEL).
typedef struct
{
    uint8 flags_0;        // 00
    uint8 reserved01[2];  // 01
    uint8 variant_3;      // 03: 0xA0 animates the surface; 0x40 plays its sound
    uint8 reserved04[4];  // 04
    uint8 routine_0;      // 08
    uint8 routine_1;      // 09
    sint8 value_A;        // 0A: the texture scroll
    uint8 routine_3;      // 0B
    uint32 cell_C;        // 0C
    void *data_10;        // 10
    ST00_MODEL *model_14; // 14
    union
    {
        STCOM_MATRIX m;
        sint32 words[8];
        struct
        {
            uint8 reserved00[0x14];
            uint32 key_14;   // 2C: the cell value to restore
            sint32 value_18; // 30
            sint32 value_1C; // 34
        } f;
    } matrix_18;          // 18
    STCOM_SVECTOR pos_38; // 38
    uint32 color_40;      // 40
    sint32 cell_44;       // 44: index into the room's cell table
    uint32 count_48;      // 48: frames since the last sound
    uint8 reserved4C[4];  // 4C
} ST00_POOL;

extern ST00_UV8 D_8012256C[16]; // the surface's texture coordinates
extern uint16 D_801225EC[25];   // its vertices' heights

void Model_face_uv_set(void *model, sint32 id, ST00_UV8 *uv);

// A 0x10C-byte slot (Open_SHL_WORK) as func_8010B1C0 fires it: STAGE_PIECE with two more words.
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
} ST00_SHOT;

extern STAGE_STCOM15_FUNC_4E0 D_8011C184[]; // routine_1 handlers (func_8010A9C8)

// The hit records of r3_st00's two targets (func_801161D4, by variant_3 & 1): func_800341BC's
// hit bits and where the hit came from.
typedef union
{
    struct
    {
        uint32 hit_0;         // 0: damage (low 24 bits) and kind bits
        uint32 value_4;       // 4
        STCOM_SVECTOR from_8; // 8: pad 0 when the player hit it
    } f;
    uint32 words[4];
} ST00_HIT_REC;

extern ST00_HIT_REC D_80122620[2];

typedef void (*ST00_STCOM19_FUNC)(ST00_STCOM19_WORK *wp);

extern ST00_STCOM19_FUNC D_8011C928[]; // by routine_0 (func_8011216C)

void ApplyMatrix(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_FIXED_VECTOR *out);

// Four bytes per model part from +0xF8 of a 0x3C0-byte slot; byte 3 is -1 while the part is hidden
// (func_80109180).
typedef struct
{
    uint8 value_0;      // 0
    uint8 reserved1[2]; // 1
    sint8 hide_3;       // 3
} ST00_PART_FLAGS;

// A 0x3C0-byte slot seen through its part flags.
typedef struct
{
    uint8 reserved00[0xF8];        // 00
    ST00_PART_FLAGS part_F8[0x18]; // F8
} ST00_PARTS_VIEW;

#define ST00_PART_FLAGS_F8(wp) (((ST00_PARTS_VIEW *)(wp))->part_F8)

extern STCOM_SVECTOR D_801224AC[];      // a scratch rotation, or a saved position (func_8011032C)
extern STCOM_FIXED_VECTOR D_801224B4[]; // a scratch scale, or a saved 16.16 position

typedef void (*ST00_PART_FUNC)(ST00_PART *wp);

extern ST00_PART_FUNC D_8011C86C[]; // by routine_1

sint32 func_80111634(ST00_OBJ *wp);

void func_8011032C(ST00_PART *wp);

#endif
