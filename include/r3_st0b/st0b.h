#ifndef ST0B_H
#define ST0B_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"

typedef struct ST0B_10C ST0B_10C;

// A view of STAGE_OBJ with the fields r3_st0b's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint8 reserved4; // 04
    uint8 value_5;   // 05
    uint8 flags_6;   // 06
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
    uint16 value_50;                        // 50
    uint8 reserved52[0x2];                  // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[0x6];                  // 68
    uint16 value_6E;                        // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x2];                  // 7E
    sint32 value_80;                        // 80
    uint8 reserved84[0x4];                  // 84
    void *model_88;                         // 88
    sint32 value_8C;                        // 8C
    sint32 value_90;                        // 90
    sint32 value_94;                        // 94
    uint8 *anim_98;                         // 98
    sint32 value_9C;                        // 9C
    sint32 value_A0;                        // A0
    uint8 reservedA4[2];                    // A4
    sint8 frame_A6;                         // A6: animation frame
    sint8 value_A7;                         // A7
    sint32 value_A8;                        // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[0x2];                  // AE
    uint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    uint8 reservedB8[0x4];                  // B8
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    sint32 value_CC;                        // CC
    uint8 reservedD0[0x28];                 // D0
    STAGE_PART_S part_F8[14];               // F8: value_3 -1 hides a part
    uint8 reserved130[0x18];                // 130
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x8];                 // 160
    uint8 value_168;                        // 168
    uint8 value_169;                        // 169
    uint8 reserved16A[0x18];                // 16A
    sint16 value_182;                       // 182
    uint8 reserved184[0x2];                 // 184
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[0x2];                 // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x74];                // 2A8
    uint16 value_31C;                       // 31C
    sint16 value_31E;                       // 31E
    uint8 reserved320[0x28];                // 320
    uint16 value_348;                       // 348
    sint16 value_34A;                       // 34A
    sint32 value_34C;                       // 34C
    uint8 reserved350[0x4];                 // 350
    STCOM_SVECTOR pos_354;                  // 354
    uint8 reserved35C[0x24];                // 35C
    uint16 value_380;                       // 380
    uint16 value_382;                       // 382
    sint16 value_384;                       // 384
    sint16 value_386;                       // 386
    uint8 reserved388[0x4];                 // 388
    sint16 value_38C;                       // 38C
    uint8 value_38E;                        // 38E
    uint8 reserved38F[0x9];                 // 38F
    sint32 value_398;                       // 398
    uint8 reserved39C[0x10];                // 39C
    sint32 value_3AC;                       // 3AC
    uint8 reserved3B0[0x18];                // 3B0
    STCOM_SVECTOR pos_3C8;                  // 3C8: a point ahead of the object
    STCOM_FIXED_VECTOR fixed_3D0;           // 3D0: the same point in 16.16
    ST0B_10C *slot_3E0;                     // 3E0: the shot it holds
    sint32 value_3E4;                       // 3E4
    uint8 reserved3E8[0x8];                 // 3E8
    sint32 value_3F0;                       // 3F0
    uint8 reserved3F4[0x10];                // 3F4
    sint32 value_404;                       // 404
    uint8 reserved408[0x10];                // 408
    sint32 value_418;                       // 418
    uint8 reserved41C[0x8];                 // 41C
    uint8 reserved424[0x8];                 // 424
    uint8 reserved42C[0x4];                 // 42C
    sint32 value_430;                       // 430
    uint8 value_434;                        // 434
    uint8 value_435;                        // 435
    uint8 value_436;                        // 436
    uint8 value_437;                        // 437
    uint16 value_438;                       // 438
    sint16 value_43A;                       // 43A
    uint8 value_43C;                        // 43C
    uint8 value_43D;                        // 43D
    uint8 value_43E;                        // 43E
    uint8 reserved43F;                      // 43F
    sint16 value_440;                       // 440
    uint16 value_442;                       // 442
    uint8 reserved444[0x4];                 // 444
    uint8 value_448;                        // 448
    uint8 reserved449[0x7];                 // 449
    STAGE_OBJ *value_450;                   // 450
    STCOM_SVECTOR *target_454;              // 454
    uint8 reserved458[0x2];                 // 458
    sint16 value_45A;                       // 45A
    sint16 value_45C;                       // 45C
    sint16 value_45E;                       // 45E
    sint32 value_460;                       // 460
    sint32 value_464;                       // 464
    uint8 reserved468[0x78];                // 468
    STAGE_FACE face;                        // 4E0
} ST0B_OBJ;

// A hit box in ST0B_CTL, registered through func_800341BC (func_801048FC).
typedef struct
{
    STCOM_SVECTOR pos_0; // 00
    uint32 hit_8;        // 08: func_800341BC's record
    uint32 value_C;      // 0C
    sint16 size_10;      // 10
    sint16 size_12;      // 12
} ST0B_HITBOX;

// An action slot in ST0B_CTL: an index into a handler table and a value.
typedef struct
{
    uint8 index_0;  // 0
    uint8 state_1;  // 1
    uint8 timer_2;  // 2
    uint8 count_3;  // 3
    sint16 angle_4; // 4
    sint16 step_6;  // 6
} ST0B_ACT;

// ST0B_OBJ's control block at +0x380, which its routines take with the slot (D_8011ABEC).
typedef struct
{
    uint16 flags_0;              // 00 (+0x380)
    uint16 rand_2;               // 02: rand() each frame
    sint16 index_4;              // 04: the waypoint it heads for (path_D4)
    sint16 count_6;              // 06
    sint16 value_8;              // 08
    sint16 timer_A;              // 0A
    uint16 timer_C;              // 0C (+0x38C)
    uint8 index_E;               // 0E: the action slot being run
    uint8 toggle_F;              // 0F (+0x38F)
    ST0B_HITBOX hit_10[2];       // 10
    uint8 track_38[0x10];        // 38: func_80036478
    STCOM_SVECTOR_W rot_48;      // 48 (+0x3C8)
    STCOM_FIXED_VECTOR scale_50; // 50 (+0x3D0)
    STAGE_OBJ *slot_60;          // 60 (+0x3E0)
    uint32 time_64;              // 64 (+0x3E4): frames in this mode
    ST0B_HITBOX hit_68[2];       // 68
    ST0B_HITBOX hit_90;          // 90
    ST0B_ACT act_A4[4];          // A4: [2] (+0x434) indexes D_8011AB38, [3] D_8011AB40
    uint8 reservedC4[8];         // C4
    sint32 wave_CC;              // CC (+0x44C): into D_800BBCF8, 0 to 63
    STAGE_OBJ *child_D0;         // D0 (+0x450)
    STCOM_SVECTOR *path_D4;      // D4: into D_8011AB24
    uint16 msg_D8;               // D8: messages already shown
    sint16 base_DA;              // DA (+0x45A): the height it bobs around
    sint16 count_DC;             // DC (+0x45C)
    uint16 count_DE;             // DE
    uint8 *data_E0;              // E0 (+0x460)
    sint32 value_E4;             // E4
    sint32 value_E8;             // E8
} ST0B_CTL;

// ST0B_OBJ's step record at +0x434: a step, its countdown and the countdown's reload value
// (func_801060F8).
typedef struct
{
    uint8 value_0;   // 0 (+0x434)
    uint8 step_1;    // 1
    uint8 value_2;   // 2
    uint8 count_3;   // 3
    uint16 timer_4;  // 4
    sint16 reload_6; // 6
} ST0B_STEP;

sint32 func_80106B08(ST0B_OBJ *wp, sint32 side);

typedef void (*ST0B_OBJ_FUNC)(ST0B_OBJ *wp);

// A view of STAGE_10C with the fields r3_st0b's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
struct ST0B_10C
{
    uint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 value_4;                     // 04
    uint8 value_5;                     // 05
    uint16 value_6;                    // 06
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    sint8 value_C;                     // 0C
    sint8 value_D;                     // 0D
    uint8 reservedE;                   // 0E
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
    uint16 value_50;                   // 50
    uint8 reserved52[0x2];             // 52
    sint16 value_54;                   // 54
    sint16 value_56;                   // 56
    sint16 value_58;                   // 58
    uint8 reserved5A[0xA];             // 5A
    sint32 value_64;                   // 64
    uint8 reserved68[0x6];             // 68
    uint16 value_6E;                   // 6E
    uint8 reserved70[0x8];             // 70
    sint32 value_78;                   // 78
    sint16 value_7C;                   // 7C
    uint8 reserved7E[0x2];             // 7E
    sint32 value_80;                   // 80
    uint8 reserved84[0x4];             // 84
    sint32 value_88;                   // 88
    STAGE_MATRIX matrix_8C;            // 8C
    STCOM_SVECTOR position_AC;         // AC
    sint32 color_B4;                   // B4
    void *target_B8;                   // B8
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
    uint8 reservedE2[0x19];            // E2
    uint8 value_FB;                    // FB
    uint8 reservedFC[0x3];             // FC
    uint8 value_FF;                    // FF
    uint8 reserved100[0x7];            // 100
    uint8 value_107;                   // 107
    uint8 reserved108[0x3];            // 108
    uint8 value_10B;                   // 10B
};

typedef void (*ST0B_10C_FUNC)(ST0B_10C *wp);

// A view of STAGE_FX with the fields r3_st0b's own code uses named by offset (generated from the
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
    sint32 value_44;      // 44
} ST0B_FX;

typedef void (*ST0B_FX_FUNC)(ST0B_FX *wp);

void Sce_event_next(void);
void func_801026E4(void);

void func_801053B0(ST0B_OBJ *wp);
void func_801070B0(ST0B_OBJ *wp);

void func_801053E4(STAGE_OBJ *wp);

void func_8010CC38(STAGE_OBJ *wp);

void func_8010CEA0(STAGE_OBJ *wp);

void func_8010CEC0(STAGE_OBJ *wp);

void func_8010E34C(STAGE_OBJ *wp);

void func_801134D0(STCOM_EFFECT *arg0);

void func_80114B24(STCOM_EFFECT *arg0);

void func_80114E3C(STCOM_EFFECT *arg0);

void func_80115048(STCOM_EFFECT *arg0);

void func_80115760(STCOM_EFFECT *arg0);

void func_80116A68(STAGE_OBJ *wp);

void func_80100F84(STAGE_ROOM *wp);

void func_80117F0C(STAGE_OBJ *wp);

void func_80101048(STAGE_ROOM *wp);

void func_80101864(STAGE_ROOM *wp);

void func_80101890(STAGE_ROOM *wp);

void func_801018BC(STAGE_ROOM *wp);

void func_801018E8(STAGE_ROOM *wp);

void func_80101C24(STAGE_ROOM *wp);

void func_801071A0(STAGE_OBJ *wp);

void func_8011850C(STAGE_FX *wp);

void func_80100FA8(STAGE_ROOM *wp);

void func_80113410(STAGE_SPARK *wp);
void func_8011349C(STAGE_SPARK *wp);

extern STAGE_ROOM2_FUNC D_801198A0[];
void func_80100808(STAGE_ROOM *wp);

void func_80114F1C(STAGE_OBJ *wp);

extern STAGE_ROOM2_FUNC D_80119D08[];
void func_80101234(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_8011A2E8[];
void func_80102234(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_8011B42C[];
void func_8010CC58(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011B658[];
void func_8010FA3C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011B76C[];
void func_801116E0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BC60[];
void func_801134F0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BD50[];
void func_801147FC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BE54[];
void func_801154F4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BE60[];
void func_801159EC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BE6C[];
void func_80115E60(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011BE94[];
void func_80116134(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C16C[];
void func_801166EC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C178[];
void func_80116A2C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C404[];
void func_80117ED0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C40C[];
void func_8011847C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011C41C[];
void func_8011853C(STAGE_OBJ *wp);

void func_80118578(void);
void func_80118580(STAGE_OBJ *wp);
void func_80118594(STAGE_OBJ *wp);

void func_801186E8(uint8 arg0);

extern uint8 D_80119890;
void func_801007BC(STAGE_ROOM *wp);

void func_8010B288(STAGE_OBJ *wp);

void func_8010B2D4(STAGE_OBJ *wp);

void func_8010B470(STAGE_OBJ *wp);

void func_8010E854(STAGE_OBJ *wp);

void func_8010069C(STAGE_ROOM *wp);

void func_80101D40(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_8011B3EC[];
void func_8010B0B8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011B3FC[];
void func_8010B394(STAGE_OBJ *wp);

void func_80114F54(STAGE_OBJ *wp);

void func_80101E2C(uint8 arg0);

void func_80100D10(STAGE_ROOM *wp);

void func_80107130(STAGE_OBJ *wp);

extern uint8 D_80119D04;
void func_80100C34(STAGE_ROOM *wp);

void func_80103FC4(STAGE_OBJ *wp);

void func_8010B3F4(STAGE_OBJ *wp);

void func_8010E574(STAGE_OBJ *wp);

void func_80102F98(STAGE_OBJ *wp);

void func_801030BC(STAGE_OBJ *wp);

void func_80103DE0(STAGE_OBJ *wp);

void func_80101070(sint32 arg0, uint8 arg1);

extern STAGE_SLOT_FUNC *D_801190DC[];
extern STAGE_SLOT_FUNC *D_801191A8[];
extern STAGE_SLOT_FUNC D_801191DC[];
extern STAGE_SLOT_FUNC D_80119260[];
extern STAGE_SLOT_FUNC D_801192C8[];
extern STAGE_SLOT_FUNC D_801192FC[];
extern STAGE_ROOM2_FUNC *D_80119814[];

extern STAGE_PART_FUNC D_8011B3A8[];

// Used by functions still in assembly (types from their accesses).
extern sint32 D_800989FC;
extern uint8 D_800A395E[];
extern sint16 D_800BBCF8[];
extern sint32 D_800BC7D4[];
extern uint8 D_801000B8[];
extern sint32 D_80119774[];
extern uint8 D_80119898[];
extern STAGE_SCRIPT_ENTRY D_801198AC[];
extern STAGE_SCRIPT_ENTRY D_801198FC[];
extern uint8 D_80119960[];
extern uint8 D_801199B0[];
extern STAGE_ROOM2_FUNC D_80119C9C[];
extern STAGE_ROOM2_FUNC D_80119CAC[];
extern STAGE_SCRIPT_ENTRY D_80119D14[]; // the room scripts D_80119D28.. continue
extern uint8 D_80119D28[];
extern STAGE_SCRIPT_ENTRY D_80119D3C[];
extern STAGE_SCRIPT_ENTRY D_80119D64[];
extern uint8 D_80119DDC[];
extern uint8 D_80119E2C[];
extern STAGE_ROOM2_FUNC D_8011A238[];
extern STAGE_ROOM2_FUNC D_8011A248[];
extern sint16 D_8011A2C0[];
extern sint16 D_8011A2C8[];
extern STAGE_SCRIPT_ENTRY D_8011A2F8[];
extern uint8 D_8011A30C[];
extern STAGE_ROOM2_FUNC D_8011A394[];
extern uint8 D_8011A3C4[];
extern STAGE_ROOM2_FUNC D_8011A410[];
extern uint8 D_8011AAF0[];
extern STCOM_SVECTOR D_8011AB24[][4];
extern uint8 D_8011AB48[];
extern STCOM_SVECTOR D_8011AB54;
extern sint16 D_8011AB56;
extern sint16 D_8011AB58;
extern uint16 D_8011ABA4[][4];
extern uint8 D_8011ABA6[][8];
extern uint8 D_8011ABC4[];
extern sint16 D_8011ABD4;
extern sint16 D_8011ABD6;
extern sint16 D_8011ABD8;
extern uint8 D_8011ABDC[];
extern sint16 D_8011ABE4;
extern sint16 D_8011ABE6;
extern sint16 D_8011ABE8;
extern uint8 D_8011ABFC[];
extern uint8 D_8011B3D8[];
extern sint16 D_8011B424[]; // func_8010C69C: the glow level per palette slot
extern uint8 D_8011B454[];
extern sint16 D_8011B460[];
extern uint8 D_8011B61D[];
extern uint8 D_8011B629[];
extern sint32 D_8011B640[];
extern sint32 D_8011B64C[];
extern sint16 D_8011B66A[];
extern uint16 D_8011B66C[];
extern sint16 D_8011B66E[];
extern uint8 D_8011B778[];
extern uint8 D_8011B788[];
extern uint8 D_8011B9EC[];
extern uint16 D_8011BB50;
extern STCOM_SVECTOR D_8011BBB8;
extern uint8 D_8011BBC0[];
extern sint32 D_8011BBCC[];
extern sint32 D_8011BBE0[];
extern sint32 D_8011BC2C[];
extern uint8 D_8011BC40[];     // ST0B_TRAIL5 data_78
extern sint16 D_8011BCD0[][4]; // ST0B_SPLASH sizes by variant and value_C
extern sint16 D_8011BCE8[][4]; // and their growth
extern sint16 D_8011BD00[];    // variant 0's second size by value_C
extern sint16 D_8011BD18[][4]; // and its growth
extern uint8 D_8011BD30[];
extern sint32 D_8011BE30[];
extern sint32 D_8011BE38[];
extern sint32 D_8011BE40[];
extern uint8 D_8011BE78[];
extern uint8 D_8011BE79[];
extern uint8 D_8011BE84[];
extern uint8 D_8011BE8C[];
extern sint16 D_8012034C;
extern STCOM_FIXED_VECTOR D_80120350;
extern STAGE_OBJ *D_80120364; // the slot func_80117938 spawns
extern STAGE_OBJ *D_80120368;
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern sint32 D_80164008[];

void func_8001DEE4(void);
void func_80100570(void);

void func_801060E0(ST0B_OBJ *wp);

void func_80118730(ST0B_OBJ *wp);

void func_80118824(ST0B_OBJ *wp);

void func_801187D4(ST0B_OBJ *wp);

extern ST0B_OBJ_FUNC D_8011AAF8[];
extern ST0B_OBJ_FUNC D_8011B438[];
void func_8010CD90(ST0B_OBJ *wp);
void func_80104598(ST0B_OBJ *wp);

void func_80113674(STAGE_OBJ *wp);

void func_80118758(ST0B_OBJ *wp);

extern STAGE_OBJ_FUNC D_8011B634[];
void func_8010F9CC(STAGE_OBJ *wp, STAGE_FX *fx);
void func_8010FA0C(STAGE_OBJ *wp, STAGE_FX *fx);

extern sint16 *D_8011A520[];
extern sint16 *D_8011A548[];
extern sint16 *D_8011A6E4[];
extern sint16 *D_8011A720[];
extern sint16 *D_8011A8D0[];
extern sint16 *D_8011A904[];
extern sint16 *D_8011AA90[];
extern sint16 *D_8011AAC0[];

void func_80102D90(void *wp, STAGE_FACE16 *face, sint32 index);

void func_801033C8(void *wp, STAGE_FACE16 *face, sint32 index);

void func_80103BC8(void *wp, STAGE_FACE16 *face, sint32 index);

void func_80104404(void *wp, STAGE_FACE16 *face, sint32 index);

void func_8003187C(void *wp);

extern void *D_80119354[];
extern void *D_80119554[];
extern void *D_801195EC[];
extern uint8 D_8011960C[][0x28];
extern uint8 D_8011974C[][8];

sint32 func_8003648C(void *track, void *wp);
sint32 func_800364B0(void *track, void *target, sint32 angle);
void func_8001DF10(uint8 *list);

// PsyQ's TILE (a flat rectangle), as func_80101110 fills it.
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} ST0B_TILE;

// ends when its emitter's routine does.
typedef struct ST0B_SPARK ST0B_SPARK;

struct ST0B_SPARK
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
    ST0B_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

typedef struct
{
    STAGE_XYZ *origin_0; // 00
    uint8 state_4;       // 04
    uint8 shade_5;       // 05: subtracted from each color channel
    sint16 frame_6;      // 06
    uint16 size_8;       // 08
    sint16 x_A;          // 0A
    sint16 y_C;          // 0C
    sint16 z_E;          // 0E
} ST0B_CELL;

typedef struct
{
    sint8 mode_0;            // 00
    uint8 mask_1;            // 01
    uint8 reserved02;        // 02
    uint8 rows_3;            // 03
    uint8 count_4[6];        // 04: per row
    uint8 reserved0A;        // 0A
    sint8 kind_B;            // 0B
    sint32 frame_C;          // 0C
    sint32 value_10;         // 10
    ST0B_CELL cell_14[6][8]; // 14
} ST0B_GRID6;

typedef void (*ST0B_GRID6_FUNC)(ST0B_GRID6 *grid, ST0B_CELL *cell);

typedef void (*ST0B_CELL_FUNC)(ST0B_CELL *cell, sint32 value);

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
} ST0B_SPRITE;

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
} ST0B_PART_D0;

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
    ST0B_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    uint8 reservedD0[4];                    // D0
    STCOM_SVECTOR trail_D4[6];              // D4: the trail's points
    uint8 reserved104[8];                   // 104
} ST0B_10C_B;

void func_80101110(uint8 r, uint8 g, uint8 b, uint16 abr);
void func_80101E90(uint8 r, uint8 g, uint8 b, uint16 abr);
void func_8001EC0C(void);
void Sce_event_update(void);
void func_801024DC(STAGE_ROOM_WORK *wp);
extern STAGE_OBJ_FUNC D_8011A420[];
void func_80102DD8(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_801028E8(STAGE_OBJ *wp);
extern STAGE_OBJ_FUNC D_8011A570[];
void func_80103410(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_80102F24(STAGE_OBJ *wp);
extern STAGE_OBJ_FUNC D_8011A75C[];
void func_80103C10(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_8010355C(STAGE_OBJ *wp);
void func_8010444C(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_8011352C(ST0B_SPARK *wp);
void func_80109FA0(uint8 *wp, sint32 value);
void func_8010A558(ST0B_GRID6 *grid, uint8 row, uint8 col);
void func_80109FE8(STAGE_OBJ *wp, ST0B_GRID6 *grid);
void func_8010A490(STAGE_OBJ *wp, ST0B_GRID6 *grid);
extern ST0B_GRID6_FUNC D_8011B3B8[];
extern ST0B_CELL_FUNC D_8011B3CC[];
void func_8010A604(ST0B_GRID6 *grid, ST0B_CELL *cell);
void func_8010A70C(ST0B_GRID6 *grid, ST0B_CELL *cell);
void func_8010A834(ST0B_GRID6 *grid, ST0B_CELL *cell);
void func_8010A95C(ST0B_GRID6 *grid, ST0B_CELL *cell);
void func_8010AA4C(ST0B_GRID6 *grid, ST0B_CELL *cell);
void func_8010AB6C(ST0B_CELL *cell, sint32 color);
void func_8010AC10(ST0B_CELL *cell, sint32 color);
void func_8010ACE0(ST0B_CELL *cell, sint32 color);
STCOM_SVECTOR func_8011010C(ST0B_10C_B *wp);
void func_8010FB6C(ST0B_10C_B *wp);

extern STCOM18_PAIR D_8011B61C[6];
extern STCOM18_PAIR D_8011B628[6];
void func_8010F534(STCOM18_WORK *wp);

void func_8010F6F8(STCOM18_WORK *wp);

extern STAGE_PL_SCRIPT_FUNC D_80120314[];
void func_80118854(STAGE_PL_SCRIPT *wp);

ST0B_SPARK *func_801136D4(STCOM_SVECTOR *pos, sint32 width, sint32 type, sint32 count, sint32 rise,
                          uint8 hide);

void func_8010403C(STAGE_OBJ *wp);
void func_801041A8(STAGE_OBJ *wp);

typedef void (*ST0B_10C_FUNC_B)(STAGE_10C *wp, sint32 *part);

// ---- ported declarations
// A slot with sixteen byte pairs at +0x28 (cleared together).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 reserved0C[3];    // 0C
    uint8 value_F;          // 0F
    uint8 reserved10[0x18]; // 10
    uint8 pair_28[16][2];   // 28
} ST0B_PAIRS;

extern ST0B_10C_FUNC_B D_8011BB84[];
void func_80111934(STAGE_10C *wp);
STAGE_OBJ *func_80036294(sint32 id);
extern STAGE_OBJ_FUNC D_8011BE48[];
void func_80115478(STAGE_OBJ *wp);
void func_80115530(ST0B_PAIRS *wp);

// A view of STAGE_10C with the fields r3_st06's own code uses named by offset (generated from the
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
    sint16 value_4C;                   // 4C
    sint16 value_4E;                   // 4E
    uint16 value_50;                   // 50
    uint8 reserved52[0x2];             // 52
    uint16 value_54;                   // 54
    sint16 value_56;                   // 56
    sint16 value_58;                   // 58
    uint8 reserved5A[0x2];             // 5A
    sint16 value_5C;                   // 5C
    sint16 value_5E;                   // 5E
    sint16 value_60;                   // 60
    uint8 reserved62[0x2];             // 62
    sint32 value_64;                   // 64
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
    sint32 value_B8;                   // B8
    uint8 reservedBC[0x10];            // BC
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[0x4];             // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0x1A];            // E2
    uint8 value_FC;                    // FC
    uint8 reservedFD[0xF];             // FD
} ST0B_10C_C;

void func_8011180C(ST0B_10C_C *wp);

void func_80100A64(STAGE_ROOM_WORK *wp);

// A view of STAGE_10C with the fields r3_st06's own code uses named by offset (generated from the
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
    sint16 value_4C;                   // 4C
    sint16 value_4E;                   // 4E
    uint16 value_50;                   // 50
    uint8 reserved52[0x2];             // 52
    uint16 value_54;                   // 54
    sint16 value_56;                   // 56
    sint16 value_58;                   // 58
    uint8 reserved5A[0x2];             // 5A
    sint16 value_5C;                   // 5C
    sint16 value_5E;                   // 5E
    sint16 value_60;                   // 60
    uint8 reserved62[0x2];             // 62
    sint32 value_64;                   // 64
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
    sint32 value_B8;                   // B8
    uint8 reservedBC[0x10];            // BC
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[0x4];             // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0x1A];            // E2
    uint8 value_FC;                    // FC
    uint8 reservedFD[0xF];             // FD
} ST0B_10C_D;

void func_80111884(ST0B_10C_D *wp);
sint32 func_8010DB7C(STAGE_OBJ *wp);

// A view of STAGE_10C with the fields r3_st06's own code uses named by offset (generated from the
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
    sint16 value_4C;                   // 4C
    sint16 value_4E;                   // 4E
    uint16 value_50;                   // 50
    uint8 reserved52[0x2];             // 52
    uint16 value_54;                   // 54
    sint16 value_56;                   // 56
    sint16 value_58;                   // 58
    uint8 reserved5A[0x2];             // 5A
    sint16 value_5C;                   // 5C
    sint16 value_5E;                   // 5E
    sint16 value_60;                   // 60
    uint8 reserved62[0x2];             // 62
    sint32 value_64;                   // 64
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
    sint32 value_B8;                   // B8
    uint8 reservedBC[0x10];            // BC
    sint32 x_CC;                       // CC
    sint32 y_D0;                       // D0
    sint32 z_D4;                       // D4
    uint8 reservedD8[0x4];             // D8
    sint16 radius_DC;                  // DC
    sint16 angle_DE;                   // DE
    sint16 speed_E0;                   // E0
    uint8 reservedE2[0x1A];            // E2
    uint8 value_FC;                    // FC
    uint8 reservedFD[0xF];             // FD
} ST0B_10C_E;

void func_8011171C(ST0B_10C_E *wp);

// From r3_st04 (ST04_ACTOR_CTL).
// A 0x20-byte control block of ST0B_ACTOR (at +0x348 and +0x368).
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
} ST0B_ACTOR_CTL;

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
    uint8 value_F;                          // 0F
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
    sint32 color_B4;                        // B4
    uint8 reservedB8[0xC];                  // B8
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST0B_ACTOR_CTL ctl;                     // 348
    ST0B_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST0B_ACTOR;

void func_801127A0(ST0B_ACTOR *wp, uint16 *bob);

void func_80112C18(STAGE_OBJ *wp, uint16 *bob);

// Player_work as the stage's player routines take it: +0xC is their routine (a signed byte), and
// +0x428/+0x438 a second position in 16.16 and in halfwords.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 reserved0A[2];                    // 0A
    sint8 routine_C;                        // 0C
    sint8 value_D;                          // 0D
    uint8 reserved0E[6];                    // 0E
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint16 speed_44[3];                     // 44
    uint8 reserved4A[0xA];                  // 4A
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x10];                 // 64
    uint8 value_74;                         // 74
    uint8 reserved75;                       // 75
    sint8 value_76;                         // 76
    uint8 reserved77[0x46];                 // 77
    uint8 flags_BD;                         // BD
    uint8 reservedBE[2];                    // BE
    void *held_C0;                          // C0: the work slot it holds
    uint8 reservedC4[0x2E4];                // C4
    STCOM_SVECTOR pos_3A8;                  // 3A8: where the stage's homing objects aim
    uint8 reserved3B0[0x78];                // 3B0
    STCOM_FIXED_VECTOR fixed_428;           // 428
    STCOM_SVECTOR pos_438;                  // 438
    sint16 value_440;                       // 440
    sint16 value_442;                       // 442
    uint8 reserved444[5];                   // 444
    sint8 value_449;                        // 449
} ST0B_PL;

#define ST0B_PL_PTR ((ST0B_PL *)&Player_work)

void func_801188B4(STAGE_ROOM *wp);

void func_80118978(STAGE_ROOM *wp);

void func_80118A74(STAGE_ROOM *wp);

void func_80118B38(STAGE_ROOM *wp);

extern uint8 D_80120214[];
extern uint8 D_80120114[];
extern STAGE_ROOM2_FUNC D_80120324[];
extern STAGE_SCRIPT_ENTRY D_801200D8[];
void func_80118C34(STAGE_ROOM *wp);

// The control block func_8010C060 and func_8010C1EC take with their slot: flags, an angle, a
// bobbing counter, the last hit (func_8010BAFC) and a tracking block for func_800364B0/func_8003648C.
typedef struct
{
    uint8 reserved00[4];       // 00
    STCOM_EFFECT *effect_4[3]; // 04
    uint8 reserved10[4];       // 10
    uint16 flags_14;           // 14
    uint16 seed_16;            // 16
    sint16 value_18;           // 18
    sint16 angle_1A;           // 1A
    sint16 value_1C;           // 1C
    sint16 value_1E;           // 1E
    sint16 value_20;           // 20
    sint16 value_22;           // 22
    sint16 timer_24;           // 24
    uint16 count_26;           // 26
    sint16 value_28;           // 28
    uint16 index_2A;           // 2A: into D_8011B460, or 0xFFFF
    STCOM_SVECTOR pos_2C;      // 2C: where it was hit
    uint32 hit_34;             // 34: damage in the low 24 bits, kind bits above
    sint32 value_38;           // 38
    uint8 track_3C[0x10];      // 3C
} ST0B_BOB;

typedef void (*ST0B_BOB2_FUNC)(STAGE_OBJ *wp, ST0B_BOB *bob);

// The control block a bobbing object keeps at +0x308 (func_8010B4BC passes it to its routines).
#define ST0B_OBJ_BOB(wp) ((ST0B_BOB *)((uint8 *)(wp) + 0x308))

// A scratchpad vector func_8003346C reads (its y is a turn angle).
#define ST0B_SP_ROT ((STCOM_SVECTOR *)0x1F800140)

void func_8010BE88(STAGE_OBJ *wp, ST0B_BOB *bob);
void func_8010C1EC(STAGE_OBJ *wp, ST0B_BOB *bob);
void func_8010C264(STAGE_OBJ *wp, ST0B_BOB *bob);
void func_8010C3B0(STAGE_OBJ *wp, ST0B_BOB *bob);

extern ST0B_10C_FUNC D_8011BC58[];
void func_80113120(ST0B_10C *wp);
void func_801131F0(ST0B_10C *wp);

// A ROCK_NEO record per 0x10C-slot kind (D_80098928).
typedef struct
{
    uint8 reserved00[8];
    uint8 value_8; // 08
    uint8 value_9; // 09: or'd into the hit's kind bits
    uint8 value_A; // 0A
} ST0B_KIND10C;

extern ST0B_KIND10C **D_80098928;

// A 0x3C0-byte slot whose handlers also get the word at +0x380 (func_801070D0).
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
    uint8 reserved30C[0x74];                // 30C
    sint32 value_380;                       // 380
    uint8 reserved384[0x3C];                // 384
} ST0B_PROP;

typedef void (*ST0B_PROP_FUNC)(ST0B_PROP *wp, sint32 *value);

extern ST0B_PROP_FUNC D_8011ABEC[];

extern STAGE_OBJ_FUNC D_8011A938[];

// A 0x3C0-byte slot with its joint positions at +0x180 (func_80106958).
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
    STAGE_PART_S part_100[18];              // 100
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
    uint8 reserved30C[0xB4];                // 30C
} ST0B_JOINTED;

// A 0x48-byte effect that grows and fades over routine_2 frames (func_80114DAC).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[2];    // 01
    uint8 variant_3;        // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09: frames so far
    uint8 routine_2;        // 0A: frames left
    uint8 reserved0B[0xD];  // 0B
    sint16 size_18;         // 18
    uint8 reserved1A[0xE];  // 1A
    sint16 size_28;         // 28
    uint8 reserved2A[0x16]; // 2A
    uint32 color_40;        // 40
} ST0B_RING;

// A 0x48-byte effect slot drawn with a scale matrix whose translation words hold its growth
// (func_80114A14, func_80114C94).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[2];   // 01
    uint8 variant_3;       // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    sint8 value_C;         // 0C: the row of the size tables
    uint8 reserved0D[0xB]; // 0D
    union
    {
        STCOM_MATRIX m;
        struct
        {
            sint32 w[5];    // 18
            sint16 size[6]; // 2C: three pairs of size and growth
        } s;
    } matrix;             // 18
    STCOM_SVECTOR pos_38; // 38
    uint32 color_40;      // 40
    uint8 reserved44[4];  // 44
} ST0B_SPLASH;

typedef void (*ST0B_BOB_FUNC)(STAGE_PROP *wp, uint16 *bob);

extern const STCOM_FIXED_VECTOR D_80100284;
extern ST0B_BOB_FUNC D_8011BBB0[];
void func_80112B00(STAGE_PROP *wp, uint16 *bob);

// A 0x50-byte slot (func_80031734) that turns a model about z (func_801185D4; D_8011C42C by
// variant_3).
typedef struct ST0B_WHEEL ST0B_WHEEL;

struct ST0B_WHEEL
{
    uint8 flags_0;             // 00
    uint8 reserved01[2];       // 01
    uint8 variant_3;           // 03
    uint8 reserved04[4];       // 04
    uint8 routine_0;           // 08
    uint8 routine_1;           // 09
    uint8 reserved0A[2];       // 0A
    sint16 angle_C;            // 0C
    uint8 reserved0E[2];       // 0E
    sint16 value_10;           // 10
    uint8 reserved12[6];       // 12
    STAGE_PANEL_MATRIX matrix; // 18
    uint8 reserved38[8];       // 38
    uint32 color_40;           // 40
    uint8 reserved44[0xC];     // 44
};

typedef void (*ST0B_WHEEL_FUNC)(ST0B_WHEEL *wp);

extern ST0B_WHEEL_FUNC D_8011C42C[];
void func_801185D4(ST0B_WHEEL *wp);

typedef struct
{
    uint8 flags_0;           // 00
    uint8 value_1;           // 01
    uint8 kind_2;            // 02
    uint8 variant_3;         // 03
    uint8 value_4;           // 04
    uint8 reserved05;        // 05
    uint8 flags_6;           // 06
    uint8 reserved07[5];     // 07
    sint32 value_C;          // 0C
    sint32 value_10;         // 10
    uint8 reserved14[0x74];  // 14
    ST0B_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0B_GRID_OBJ;

ST0B_GRID_OBJ *func_80109CB0(STAGE_OBJ *owner, uint8 rows, STCOM_SVECTOR *origin);

ST0B_GRID_OBJ *func_80109DF4(STAGE_OBJ *owner, sint8 variant, STCOM_SVECTOR *origin);

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
} ST0B_PART_D0_B;

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
    ST0B_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    ST0B_PART_D0_B part_D0;                 // D0
} ST0B_10C_F;

// func_801102A4's 24 spiral sparks: each one flies for 16 frames from its start, spiraling out.
typedef struct
{
    sint16 start_0;  // 0: count_CC when it appears
    sint16 radius_2; // 2
    uint16 angle_4;  // 4
    sint16 height_6; // 6
} ST0B_SPIRAL;

extern ST0B_SPIRAL D_8011B668[24];
void func_801102A4(ST0B_10C_F *wp);

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
} ST0B_PART_D0_C;

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
    ST0B_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    ST0B_PART_D0_C part_D0;                 // D0
} ST0B_10C_G;

void func_80110540(ST0B_10C_G *wp);

// A 0x48-byte effect slot (func_80031618) that drifts and fades (func_80114E5C runs it through
// D_8011BE20; func_80114FB4) and draws itself as a sprite packet.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 value_1;         // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03: nonzero: draw
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    uint8 reserved0C[0xC]; // 0C
    uint32 color_18;       // 18
    sint16 x_1C;           // 1C
    sint16 y_1E;           // 1E
    sint16 z_20;           // 20
    uint8 reserved22[2];   // 22
    uint16 size_24;        // 24
    uint8 reserved26[2];   // 26
    sint16 vx_28;          // 28
    sint16 vy_2A;          // 2A
    sint16 vz_2C;          // 2C
    sint16 ay_2E;          // 2E
    sint16 timer_30;       // 30
    uint8 reserved32[2];   // 32
    uint32 uv_34;          // 34: the packet's uv words
    uint32 uv_38;          // 38
    uint32 uv_3C;          // 3C: two halves
    uint8 reserved40[8];   // 40
} ST0B_DRIFT;

typedef void (*ST0B_DRIFT_FUNC)(ST0B_DRIFT *wp);

extern ST0B_DRIFT_FUNC D_8011BE20[];

void func_80114FB4(ST0B_DRIFT *wp);

void func_80101FB4(STAGE_ROOM *wp);

STAGE_OBJ *func_80031498(void);

void func_8010BAFC(ST0B_OBJ *wp, ST0B_BOB *bob);

// The slot func_8011754C runs (a timed event with D_80120368's object), with its frame counter.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[2];   // 01
    uint8 variant_3;       // 03: 0 first visit, 1 on returning, 2 later
    uint8 reserved04[2];   // 04
    uint8 flags_6;         // 06
    uint8 reserved07;      // 07
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    uint8 value_C;         // 0C
    uint8 reserved0D[0xF]; // 0D
    uint32 timer_1C;       // 1C
} ST0B_EVENT;

void func_80117E2C(ST0B_EVENT *wp);

// The control block at +0x308 of the floating object (func_8010CEE0 passes it to its routines;
// func_8010D494 reads its hit record, func_8010DC28 and func_8010DDD8 patrol with it).
typedef struct
{
    uint8 reserved00[4];    // 00
    STCOM_EFFECT *effect_4; // 04
    uint8 reserved08[0xC];  // 08
    uint16 flags_14;        // 14: bit 2: hit this frame
    uint16 rand_16;         // 16: rand() each frame
    sint16 timer_18;        // 18
    sint16 value_1A;        // 1A
    sint16 count_1C;        // 1C: frames since it sank
    uint16 life_1E;         // 1E: the kind's life_A[0]
    sint16 rise_20;         // 20: how fast it rises
    sint16 fall_22;         // 22: how fast it sinks
    sint16 speed_24;        // 24: how fast it sinks while dying
    sint16 angle_26;        // 26
    sint16 height_28;       // 28: the height it floats at
    sint16 index_2A;        // 2A: into D_8011B460, or -1
    sint32 value_2C;        // 2C
    sint32 value_30;        // 30
    sint32 value_34;        // 34
    uint32 hit_38;          // 38: damage in the low 24 bits, kind bits above
    sint32 value_3C;        // 3C
    uint8 track_40[0x10];   // 40: func_80036478
} ST0B_HIT_B;

void func_80036470(void *track);

void func_8010D494(STAGE_OBJ *wp, ST0B_HIT_B *hit);

void func_8010AE94(ST0B_ACTOR *wp, ST0B_ACTOR_CTL *ctl);

void func_80117DD8(ST0B_EVENT *wp);
// A trigger zone of func_80117B14: which side of an x line, then of a z line, the player must be on.
typedef struct
{
    uint8 kind_0; // 0: 0 (x above), 1 (z only), 0xFF (none), else x below
    uint8 type_1; // 1: 3 (z above), 5 (z below), else any z
    sint16 x_2;   // 2
    sint16 z_4;   // 4
} ST0B_ZONE;

extern ST0B_ZONE D_8011C190[];
extern ST0B_ZONE D_8011C1E4[];
extern ST0B_ZONE D_8011C1F0[];

sint32 func_80117B14(ST0B_EVENT *wp, sint32 arg);

// A u, v texture corner.
typedef struct
{
    uint8 u;
    uint8 v;
} ST0B_UV;

// A 0x10C-byte slot with a sprite at +0x88 and five trail points at +0xCC (func_80112D10 sets it
// up, func_80113324 draws the trail).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B: frames left
    uint8 reserved0C[8];                    // 0C
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint16 speed_44[3];                     // 44
    uint8 reserved4A[2];                    // 4A
    sint16 accel_4C[3];                     // 4C
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    uint8 reserved5C[0x1C];                 // 5C
    uint8 *data_78;                         // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0xA];                  // 7E
    ST0B_SPRITE sprite;                     // 88
    uint8 reservedBC[8];                    // BC
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    STCOM_SVECTOR_W trail_CC[5];            // CC
    uint8 reservedF4[0x18];                 // F4
} ST0B_TRAIL5;

extern ST0B_UV D_8011BC4C[]; // texture corners of func_80113324's trail sprites

void func_8011325C(STAGE_OBJ *wp);
void func_80113324(ST0B_TRAIL5 *wp);

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
    sint32 color_B4;                        // B4
    uint8 reservedB8[0xC];                  // B8
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST0B_ACTOR_CTL ctl;                     // 348
    ST0B_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST0B_ACTOR_B;

void func_80111A9C(ST0B_ACTOR_B *wp, uint16 *bob);

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
    sint32 color_B4;                        // B4
    uint8 reservedB8[0xC];                  // B8
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST0B_ACTOR_CTL ctl;                     // 348
    ST0B_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST0B_ACTOR_C;

void func_80111BB4(ST0B_ACTOR_C *wp, uint16 *bob);

// From r3_st0a (ST0A_GRID_OBJ).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 value_1;       // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 value_4;       // 04
    uint8 reserved05;    // 05
    uint8 flags_6;       // 06
    uint8 reserved07[5]; // 07
    union
    {
        sint32 word;
        uint8 flags;
    } u_C;                   // 0C
    sint32 value_10;         // 10
    uint8 reserved14[0x74];  // 14
    ST0B_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0B_GRID_OBJ_B;

typedef struct
{
    sint16 flag_0;   // 0: nonzero: jump to (x_2, z_4) first, carrying the player
    sint16 x_2;      // 2: speeds to reach, forward and sideways
    sint16 z_4;      // 4
    sint16 rot_6;    // 6: heading to reach
    sint16 frames_8; // 8
    sint16 next_A;   // A
} ST0B_PATH_STEP;

// A ST0B_LIFT's path state (+0xCC).
typedef struct
{
    uint8 reserved00[4];      // 00
    sint16 timer_4;           // 04: frames left in the step
    sint16 x_6;               // 06: the step's goal
    sint16 z_8;               // 08
    sint16 rot_A;             // 0A
    sint16 next_C;            // 0C
    uint8 reserved0E[2];      // 0E
    sint32 x_10;              // 10: 16.16 values and their steps
    sint32 z_14;              // 14
    sint32 dx_18;             // 18
    sint32 dz_1C;             // 1C
    sint32 rot_20;            // 20
    sint32 drot_24;           // 24
    ST0B_GRID_OBJ_B *grid_28; // 28
    ST0B_PATH_STEP *step_2C;  // 2C
    STCOM_SVECTOR box_30;     // 30: hit boxes
    STCOM_SVECTOR box_38;     // 38
} ST0B_PATH;

// A 0x10C-byte slot (Open_SHL_WORK) that follows a path, carrying the player (func_80111D44).
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
    uint8 reserved0C[4];                    // 0C
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x28];                 // 64
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC
    sint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    sint32 hit_BC;                          // BC
    sint32 value_C0;                        // C0
    sint32 hit_C4;                          // C4
    sint32 value_C8;                        // C8
    ST0B_PATH path;                         // CC
} ST0B_LIFT;

typedef void (*ST0B_LIFT_FUNC)(ST0B_LIFT *wp, ST0B_PATH *path);

extern ST0B_LIFT_FUNC D_8011BBA0[];
extern ST0B_LIFT_FUNC D_8011BB98[];
void func_80111D44(ST0B_LIFT *wp, ST0B_PATH *path);

// From r3_st0a (ST0A_GRID_OBJ).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 value_1;       // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 value_4;       // 04
    uint8 reserved05;    // 05
    uint8 flags_6;       // 06
    uint8 reserved07[5]; // 07
    union
    {
        sint32 word;
        uint8 flags;
    } u_C;                   // 0C
    sint32 value_10;         // 10
    uint8 reserved14[0x74];  // 14
    ST0B_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0B_GRID_OBJ_C;

// A ST0B_LIFT's path state (+0xCC).
typedef struct
{
    uint8 reserved00[4];      // 00
    sint16 timer_4;           // 04: frames left in the step
    sint16 x_6;               // 06: the step's goal
    sint16 z_8;               // 08
    sint16 rot_A;             // 0A
    sint16 next_C;            // 0C
    uint8 reserved0E[2];      // 0E
    sint32 x_10;              // 10: 16.16 values and their steps
    sint32 z_14;              // 14
    sint32 dx_18;             // 18
    sint32 dz_1C;             // 1C
    sint32 rot_20;            // 20
    sint32 drot_24;           // 24
    ST0B_GRID_OBJ_C *grid_28; // 28
    ST0B_PATH_STEP *step_2C;  // 2C
    STCOM_SVECTOR box_30;     // 30: hit boxes
    STCOM_SVECTOR box_38;     // 38
} ST0B_PATH_B;

void func_801123C0(ST0B_LIFT *wp, ST0B_PATH_B *path);

// From r3_st0a (ST0A_GRID_OBJ).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 value_1;       // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 value_4;       // 04
    uint8 reserved05;    // 05
    uint8 flags_6;       // 06
    uint8 reserved07[5]; // 07
    union
    {
        sint32 word;
        uint8 flags;
    } u_C;                   // 0C
    sint32 value_10;         // 10
    uint8 reserved14[0x74];  // 14
    ST0B_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0B_GRID_OBJ_D;

// A ST0B_LIFT's path state (+0xCC).
typedef struct
{
    uint8 reserved00[4];      // 00
    sint16 timer_4;           // 04: frames left in the step
    sint16 x_6;               // 06: the step's goal
    sint16 z_8;               // 08
    sint16 rot_A;             // 0A
    sint16 next_C;            // 0C
    uint8 reserved0E[2];      // 0E
    sint32 x_10;              // 10: 16.16 values and their steps
    sint32 z_14;              // 14
    sint32 dx_18;             // 18
    sint32 dz_1C;             // 1C
    sint32 rot_20;            // 20
    sint32 drot_24;           // 24
    ST0B_GRID_OBJ_D *grid_28; // 28
    ST0B_PATH_STEP *step_2C;  // 2C
    STCOM_SVECTOR box_30;     // 30: hit boxes
    STCOM_SVECTOR box_38;     // 38
} ST0B_PATH_C;

void func_8011250C(ST0B_LIFT *wp, ST0B_PATH_C *path);

extern ST0B_BOB_FUNC D_8011BBA8[];
void func_80112608(STAGE_PROP *wp, uint16 *bob);

// The bobbing motion of a ST0B_BOBBER (+0x348): moves forward and turns every frame, and
// rides a sine wave in y (func_8010AF98).
typedef struct
{
    sint16 speed_0;  // 0
    sint16 height_2; // 2: wave height
    sint16 period_4; // 4: frames per wave
    sint16 turn_6;   // 6
    sint16 phase_8;  // 8
    sint16 base_A;   // A: y at the wave's middle
} ST0B_BOB_B;

typedef struct
{
    sint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 reserved09[3];                    // 09
    sint8 speed_C;                          // 0C
    sint8 height_D;                         // 0D
    sint8 period_E;                         // 0E
    uint8 turn_F;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x14];                 // 64
    sint32 value_78;                        // 78
    uint8 reserved7C[0xDC];                 // 7C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x1E8];               // 160
    ST0B_BOB_B bob;                         // 348
    uint8 reserved354[0x6C];                // 354
} ST0B_BOBBER;

void func_8010AF98(ST0B_BOBBER *wp, ST0B_BOB_B *bob);

// From r3_st17 (ST17_PART_D0).
typedef struct
{
    uint8 flags_0;          // 00: bit 0: done
    uint8 value_1;          // 01
    sint16 random_2;        // 02
    sint16 value_4;         // 04
    sint16 value_6;         // 06
    sint16 value_8;         // 08
    sint16 value_A;         // 0A
    sint16 value_C;         // 0C
    sint8 value_E;          // 0E
    uint8 reserved0F;       // 0F
    sint16 dx_10;           // 10
    sint16 dy_12;           // 12
    sint16 dz_14;           // 14
    uint8 reserved16[0x26]; // 16
} ST0B_PART_D0_D;

// From r3_st17 (ST17_10C).
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
    ST0B_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    ST0B_PART_D0_D part_D0;                 // D0
} ST0B_10C_H;

void func_801101EC(ST0B_10C_B *wp);
void func_8010FC18(ST0B_10C_B *wp);

// From r3_st0a (ST0A_GRID_OBJ).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 value_1;       // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03
    uint8 value_4;       // 04
    uint8 reserved05;    // 05
    uint8 flags_6;       // 06
    uint8 reserved07[5]; // 07
    union
    {
        sint32 word;
        uint8 flags;         // bit 0: set by the lift (func_80112004)
    } u_C;                   // 0C
    sint32 value_10;         // 10
    uint8 reserved14[0x74];  // 14
    ST0B_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0B_GRID_OBJ_E;

// A ST0B_LIFT's path state (+0xCC).
typedef struct
{
    uint8 reserved00[4];      // 00
    sint16 timer_4;           // 04: frames left in the step
    sint16 x_6;               // 06: the step's goal
    sint16 z_8;               // 08
    sint16 rot_A;             // 0A
    sint16 next_C;            // 0C
    uint8 reserved0E[2];      // 0E
    sint32 x_10;              // 10: 16.16 values and their steps
    sint32 z_14;              // 14
    sint32 dx_18;             // 18
    sint32 dz_1C;             // 1C
    sint32 rot_20;            // 20
    sint32 drot_24;           // 24
    ST0B_GRID_OBJ_E *grid_28; // 28
    ST0B_PATH_STEP *step_2C;  // 2C
    STCOM_SVECTOR box_30;     // 30: hit boxes
    STCOM_SVECTOR box_38;     // 38
} ST0B_PATH_D;

sint32 Distance_xz(sint16 *a, sint16 *b);
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);
void func_80112004(ST0B_LIFT *wp, ST0B_PATH_D *path);

extern ST0B_PATH_STEP D_8011BB48[];
extern STAGE_OBJ Player_work_obj __asm__("Player_work");

sint32 func_80031EF0(STCOM_SVECTOR *pos, sint32 angle, sint32 range, STCOM_SVECTOR *target,
                     sint32 target_angle, sint32 target_range);

void func_8003697C(void);

void Pl00_shot_enable_off(void *pl);
void func_80053AA4(sint32 arg);

// The control block at +0x328 of ST0B_BOAT.
typedef struct
{
    uint16 flags_0;      // 00
    uint16 random_2;     // 02: rand() each frame
    sint16 timer_4;      // 04
    sint16 timer_6;      // 06
    uint16 count_8;      // 08
    uint8 reserved0A[2]; // 0A
    sint16 roll_C;       // 0C
    uint8 reserved0E[2]; // 0E
    uint16 value_10;     // 10: the kind's life_A[0]
    sint16 sink_12;      // 12
    uint16 flags_14;     // 14: 0x20 rising, 0x40 risen, 0x200 sound played
    uint8 reserved16[2]; // 16
    union
    {
        sint32 hit;       // func_8004B414's result
        uint16 h[2];      // [1]: frames since it rose (func_8010D558)
    } u_18;               // 18
    sint32 ground_1C;     // 1C: 1 on the ground
    sint32 hit_20;        // 20: func_800341BC's record
    sint32 value_24;      // 24
    uint8 track_28[0x10]; // 28: func_80036478/func_8003648C
} ST0B_BOAT_CTL;

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
    sint8 index_C;                          // 0C
    uint8 reserved0D[7];                    // 0D
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        sint16 h[2];
        sint32 w;
    } turn_64;                // 64
    uint8 reserved68[6];      // 68
    sint16 life_6E;           // 6E
    uint8 reserved70[8];      // 70
    sint16 *data_78;          // 78
    uint8 reserved7C[4];      // 7C
    uint32 dist_80;           // 80: squared distance to the player
    uint8 reserved84[0x23];   // 84
    sint8 value_A7;           // A7: -1 at the end of the animation
    uint8 reservedA8[4];      // A8
    uint8 anim_AC;            // AC
    uint8 anim_prev_AD;       // AD
    uint8 reservedAE[2];      // AE
    sint16 life_max_B0;       // B0
    sint16 life_prev_B2;      // B2
    uint8 reservedB4[0xA4];   // B4
    STCOM_SVECTOR_W scale;    // 158
    uint8 reserved160[0x20];  // 160
    STCOM_SVECTOR value_180;  // 180
    uint8 reserved188[0x1A0]; // 188
    ST0B_BOAT_CTL ctl;        // 328
    uint8 reserved360[0x60];  // 360
} ST0B_BOAT;

// A 0x10C-byte slot (Open_SHL_WORK) of the spray a boat throws up (kind 1, type 0x24).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 reserved03;                  // 03
    uint8 value_4;                     // 04
    uint8 reserved05[0xA];             // 05
    uint8 type_F;                      // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    STCOM_SVECTOR velocity;            // 44
    STCOM_SVECTOR accel;               // 4C
    uint8 reserved54[0xB8];            // 54
} ST0B_SPRAY;

void func_8010D6AC(ST0B_BOAT *wp, ST0B_BOAT_CTL *ctl);

typedef struct ST0B_GLOW ST0B_GLOW;

struct ST0B_GLOW
{
    uint8 flags_0;       // 00
    uint8 reserved01;    // 01
    uint8 kind_2;        // 02
    uint8 variant_3;     // 03: nonzero to draw
    uint8 reserved04[4]; // 04
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    sint8 value_C;       // 0C
    uint8 reserved0D[7]; // 0D
    uint32 mode_14;      // 14
    uint32 color_18;     // 18
    union
    {
        struct
        {
            sint16 x; // 1C
            sint16 y; // 1E
        } h;
        uint32 w;
    } xy_1C;
    union
    {
        sint16 z; // 20
        uint32 w;
        struct
        {
            sint16 z; // 20
            uint8 u;  // 22
            uint8 v;  // 23
        } b;
    } z_20;
    uint16 size_24;      // 24
    uint8 reserved26[2]; // 26
    sint16 vx_28;        // 28
    sint16 vy_2A;        // 2A
    sint16 vz_2C;        // 2C
    sint16 ay_2E;        // 2E
    sint16 timer_30;     // 30
    uint8 reserved32[2]; // 32
    uint32 uv_34;        // 34
    uint32 uv_38;        // 38
    uint32 uv_3C;        // 3C
    uint8 reserved40[8]; // 40
};

// The motion every spark record starts with (func_80115068): speed, rise, gravity, size.
typedef struct
{
    sint16 speed_0; // 0
    sint16 vy_2;    // 2
    sint16 ay_4;    // 4
    uint16 size_6;  // 6
} ST0B_SPARK_HEAD;

// A textured spark record (D_8011BE0C).
typedef struct
{
    ST0B_SPARK_HEAD head; // 00
    uint32 uv_8;          // 08
    uint32 uv_C;          // 0C
    uint32 uv_10;         // 10
} ST0B_SPARK_TEX;

// A flat spark record (D_8011BD6C).
typedef struct
{
    ST0B_SPARK_HEAD head; // 0
    uint32 mode_8;        // 8
    uint8 u_C;            // C
    uint8 v_D;            // D
    uint8 reservedE[2];   // E
} ST0B_SPARK_FLAT;

// A spark record of either kind.
typedef union
{
    ST0B_SPARK_HEAD head;
    ST0B_SPARK_TEX tex;
    ST0B_SPARK_FLAT flat;
} ST0B_SPARK_B;

extern ST0B_SPARK_TEX D_8011BE0C[];
extern ST0B_SPARK_FLAT D_8011BD6C[];
void func_80115068(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos);

// A flame of ST0B_FLAMES: bit 0 of flags_0 lit, frame_1 its animation frame.
typedef struct
{
    uint8 flags_0; // 0
    sint8 frame_1; // 1
} ST0B_FLAME;

// A 0x48-byte effect slot (func_80031618) of four flames that follow the slot whose id is in
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
    sint8 value_C;          // 0C: the followed slot's id
    sint8 timer_D;          // 0D
    sint8 frame_E;          // 0E
    sint8 count_F;          // 0F: twice the flames to light
    uint8 reserved10[0xC];  // 10
    sint16 x_1C;            // 1C
    sint16 y_1E;            // 1E
    sint16 z_20;            // 20
    uint8 reserved22[6];    // 22
    ST0B_FLAME flame_28[6]; // 28: four or six
    uint8 reserved34[0x14]; // 34
} ST0B_FLAMES;

void func_80115780(ST0B_FLAMES *wp, sint16 angle, sint8 frame);
void func_80115570(ST0B_FLAMES *wp);

void func_80115A28(ST0B_FLAMES *wp);

void func_80115E9C(ST0B_FLAMES *wp);

void func_8011602C(ST0B_FLAMES *wp, sint16 angle, sint32 frame);

// A ROCK_NEO record per kind (D_80098844), as the floating object reads it.
typedef struct
{
    uint8 reserved00[8]; // 00
    uint8 life_8;        // 08: times 4 (the bobbing objects)
    uint8 reserved09;    // 09
    uint8 value_A;       // 0A
    uint8 life_B;        // 0B: times 16
} ST0B_KIND;

extern ST0B_KIND **D_80098844;

#define ST0B_ABS(x) ((x) < 0 ? -(x) : (x))

void func_8001D974(void);

sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

// Where func_80117C50 places a spawned object: a position and a heading.
typedef struct
{
    sint16 x, y, z;
    sint16 angle;
} ST0B_PLACE;

// Kind 0x2C's setup per index (D_8011C334): the variant and the bytes at +0xC..+0xF.
typedef struct
{
    sint32 variant_0;
    uint8 value_4[4];
} ST0B_SETUP_2C;

// Kind 0x32's setup per index (D_8011C314): the bytes at +0xC..+0xE.
typedef struct
{
    uint8 value_0[3];
    uint8 reserved03;
} ST0B_SETUP_32;

extern ST0B_SETUP_32 D_8011C314[];
extern ST0B_SETUP_2C D_8011C334[];
extern STAGE_OBJ *D_8012036C[]; // the kind 0x2C objects by index
extern STAGE_OBJ *D_801203D4[]; // the kind 0x32 objects by index

void func_80117C50(STAGE_OBJ *owner, sint32 kind, sint32 index, ST0B_PLACE *place);

extern ST0B_BOB2_FUNC D_8011B410[];
void func_8010BBA0(STAGE_OBJ *wp, ST0B_BOB *bob);

void func_80036478(void *track, uint8 arg1, uint32 arg2);

typedef void (*ST0B_HIT_B_FUNC)(STAGE_OBJ *wp, ST0B_HIT_B *ctl);

extern ST0B_HIT_B_FUNC D_8011B448[];
void func_8010D8D0(STAGE_OBJ *wp, ST0B_HIT_B *ctl);
void func_8010DA20(ST0B_OBJ *wp, ST0B_HIT_B *ctl);

extern STAGE_OBJ_FUNC D_8011B4A8[];

extern ST0B_BOB2_FUNC D_8011B404[];

void Sce_event_timer_clear(void);

// The floating object's control block at +0x308 and its hit point at +0x180 (func_8010CEE0).
#define ST0B_OBJ_HIT_B(wp)   ((ST0B_HIT_B *)((uint8 *)(wp) + 0x308))
#define ST0B_OBJ_POS_180(wp) ((STCOM_SVECTOR *)((uint8 *)(wp) + 0x180))

// A scratchpad vector func_8003346C reads (x and z: a tilt).
#define ST0B_SP_TILT ((STCOM_SVECTOR *)0x1F800128)

extern ST0B_HIT_B_FUNC D_8011B43C[];
sint32 func_80048E6C(void *wp);

// ST0B_OBJ's joint points from +0x180, eight bytes apart: their pads are the palette slots'
// colors (pal[i] is joint[i].pad).
#define ST0B_OBJ_JOINT(wp) ((STCOM_SVECTOR *)((uint8 *)(wp) + 0x180))

// A ROCK_NEO record per kind (D_8009884C), as the shooting objects read it.
typedef struct
{
    uint8 reserved00[0x8]; // 00
    uint8 life_8;          // 08: life / 32
    uint8 value_9;         // 09: damage before a flinch
    uint8 size_A;          // 0A: a hit box size / 32
    uint8 size_B;          // 0B: another hit box size / 32
    uint8 value_C;         // 0C
    uint8 value_D;         // 0D: a reload time
    uint8 hit_E;           // 0E: or'd into func_800341BC's flags
} ST0B_KIND_B;

extern ST0B_KIND_B **D_8009884C;

sint32 func_8004324C(void *pl);
sint32 Sce_flag_test(sint32 flag);

void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 color);
void func_8005D6E8(void *wp);

void func_80115BCC(ST0B_FLAMES *wp, sint32 angle, sint32 frame);

extern ST0B_OBJ_FUNC D_8011AB08[];
extern ST0B_OBJ_FUNC D_8011AB30[];
extern ST0B_OBJ_FUNC D_8011AB38[];
extern ST0B_OBJ_FUNC D_8011AB40[];

void func_8005D4C0(void);
void func_80106E4C(ST0B_OBJ *wp);

// ST0B_OBJ's shooting state at +0x43C (func_80106278).
typedef struct
{
    uint8 value_0; // 0 (+0x43C)
    uint8 step_1;  // 1 (+0x43D)
    uint8 value_2; // 2 (+0x43E)
} ST0B_SHOOT;

void func_801048FC(ST0B_OBJ *wp);

sint32 func_80106550(ST0B_OBJ *wp);

// A scratchpad block func_8003346C reads (func_801048FC sets two halfwords).
typedef struct
{
    uint8 reserved0[2]; // 0 (0x1F800160)
    uint16 value_2;     // 2
    uint8 reserved4[6]; // 4
    uint16 value_A;     // A
} ST0B_SP_ANIM;

#define ST0B_SP_160 ((ST0B_SP_ANIM *)0x1F800160)

extern sint16 D_8011AB5C[];

// The 0x10C-byte shell func_80105DF4 fires (kind 6).
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
    sint32 dist_9C;                    // 9C: distance to the player / 24
    sint32 height_A0;                  // A0: height difference to the player / 20
    uint8 reservedA4[0x68];            // A4
} ST0B_SHELL;

extern STCOM_SVECTOR D_8011ABCC;

extern ST0B_OBJ_FUNC D_8011AB1C[];

// ST0B_OBJ's control block.
#define ST0B_OBJ_CTL(wp) ((ST0B_CTL *)&(wp)->value_380)

void func_80117A74(ST0B_EVENT *wp);

// Game_work's halfword at +0x174 as a plain address: a STAGE_GAME field store is scheduled
// above the loads before it (func_80116728).
#define ST0B_GAME_174 (*(uint16 *)((uint8 *)&Game_work + 0x174))

extern ST0B_PLACE D_8011C204[];

extern ST0B_PLACE D_8011C2D4[];

// PsyQ's DR_MOVE (a VRAM-to-VRAM move primitive, 0x18 bytes).
typedef struct
{
    u_long tag;
    u_long code[5];
} ST0B_DR_MOVE;

// The display link record as func_80117F30 uses it.
typedef struct
{
    uint8 reserved00[0x88];
    u_long ot_88;
} ST0B_LINK;

#define ST0B_LINK_PTR ((ST0B_LINK *)Disp_env_ptr)

// Where the next primitive goes (scratchpad).
#define ST0B_PACKET_PTR (*(ST0B_DR_MOVE **)0x1F800070)

void SetDrawMove(ST0B_DR_MOVE *p, RECT *rect, sint32 x, sint32 y);

void func_8001B314(void);

// A 0x48-byte effect slot (func_80031618) as func_80101FB4 sets it up: a spark at a point.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 value_4;          // 04
    uint8 reserved05[7];    // 05
    uint8 value_C;          // 0C
    sint8 value_D;          // 0D
    uint8 reserved0E[0x2A]; // 0E
    STCOM_SVECTOR pos_38;   // 38
    uint8 reserved40[8];    // 40
} ST0B_DUST;

extern STCOM_SVECTOR D_8011A2D0[];

// A camera request a sign sets when it is read (D_8011BC18).
typedef struct
{
    sint16 x_0;     // 0
    sint16 y_2;     // 2
    sint16 z_4;     // 4
    sint16 value_6; // 6
    sint8 value_8;  // 8
    uint8 value_9;  // 9
    uint8 value_A;  // A
} ST0B_CAM_SHOT;

extern ST0B_CAM_SHOT *D_8011BC18[];

void func_80052528(void *wp);

#endif
