#ifndef ST06_H
#define ST06_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom05.h"

// The block at +0x2C8 of the object whose parts (0x10C slots, by variant) it shows: a bit per part
// still standing, and the part that is lit (variant * 2, plus 1 while lit).
typedef struct
{
    STCOM_SVECTOR origin_0; // 00: where the shot started (func_80114988)
    uint32 hit_8;           // 08: filled by func_800341BC
    sint32 value_C;         // 0C
    uint32 mask_10;         // 10
    uint32 lit_14;          // 14
} ST06_PARTS;

// Scene_work (ROCK_NEO's SCENE_WORK) as the villagers' script handlers read it: routine_0 is zero
// once the scene has ended, flag_9 counts its cuts, work_1C is compared signed.
typedef struct
{
    uint8 routine_0;     // 00
    uint8 reserved01[8]; // 01
    uint8 flag_9;        // 09
    uint8 reserved0A[0x12];
    sint32 work_1C; // 1C
} ST06_SCENE;

// Player_work's joint positions (ROCK_NEO's SVECTOR pos_3a8[15]).
#define ST06_PL_JOINT ((STCOM_SVECTOR *)&STAGE_PL_BYTE(0x3A8))

// The 0x3C0-byte slot of func_8011494C's family: a shot that flies from parts_2C8.origin_0 along
// dir_44, leaving a part (func_80114FA8) at every step.
typedef struct
{
    sint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[4];               // 04
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B: steps flown
    uint8 reserved0C[4];               // 0C
    sint32 value_10;                   // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    STCOM_SVECTOR position_prev;       // 2C
    uint8 reserved34[0x10];            // 34
    STCOM_SVECTOR dir_44;              // 44: a unit vector (4096)
    uint8 reserved4C[8];               // 4C
    STCOM_SVECTOR rotation;            // 54
    uint8 reserved5C[0x1C];            // 5C
    void *data_78;                     // 78
    uint8 reserved7C[0x2B];            // 7C
    sint8 value_A7;                    // A7
    uint8 reservedA8[0xB0];            // A8
    STCOM_SVECTOR_W scale;             // 158
    STCOM_MATRIX matrix_160;           // 160
    uint8 reserved180[0x20];           // 180
    STCOM_SVECTOR pos_1A0;             // 1A0: its hit box's center
    uint8 reserved1A8[0x120];          // 1A8
    ST06_PARTS parts_2C8;              // 2C8
    uint8 reserved2E0[0xE0];           // 2E0
} ST06_BEAM;

// A view of STAGE_OBJ with the fields r3_st06's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint8 value_4;   // 04
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
        struct
        {
            uint8 byte_C; // 0C
            uint8 byte_D; // 0D
        } ub;
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
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
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
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    sint32 value_A8;                        // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[0x2];                  // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    sint32 value_B4;                        // B4
    sint32 value_B8;                        // B8
    uint8 reservedBC[0x20];                 // BC
    sint32 value_DC;                        // DC
    uint8 reservedE0[0x1C];                 // E0
    uint8 value_FC;                         // FC
    uint8 reservedFD[0x3];                  // FD
    STAGE_PART part_100[12];                // 100
    uint8 reserved130[0x18];                // 130
    sint8 value_148[4];                     // 148
    uint8 reserved14C[0xC];                 // 14C
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x20];                // 160
    sint16 value_180;                       // 180
    sint16 value_182;                       // 182
    uint8 reserved184[0x2];                 // 184
    STAGE_PAL pal[24];                      // 186
    uint8 reserved246[0x2];                 // 246
    STAGE_MATRIX matrix_248;                // 248
    uint8 reserved268[0x20];                // 268
    STAGE_MATRIX matrix_288;                // 288
    uint8 reserved2A8[0x20];                // 2A8
    ST06_PARTS parts_2C8;                   // 2C8
    uint8 reserved2E0[0x48];                // 2E0
    sint32 value_328;                       // 328
    uint16 value_32C;                       // 32C
    sint16 value_32E;                       // 32E
    sint32 value_330;                       // 330
    sint32 value_334;                       // 334
    uint8 reserved338[0x8];                 // 338
    sint32 value_340;                       // 340
    sint32 value_344;                       // 344
    uint16 value_348;                       // 348
    sint16 value_34A;                       // 34A
    sint32 value_34C;                       // 34C
    uint8 reserved350[0x2];                 // 350
    sint16 value_352;                       // 352
    sint32 value_354;                       // 354
    uint8 reserved358[0x8];                 // 358
    sint32 value_360;                       // 360
    sint32 value_364;                       // 364
    sint16 value_368;                       // 368
    sint16 value_36A;                       // 36A
    uint8 value_36C;                        // 36C
    uint8 reserved36D[0xBB];                // 36D
    sint32 value_428;                       // 428
    sint32 value_42C;                       // 42C
    sint32 value_430;                       // 430
    uint8 reserved434[0x4];                 // 434
    sint16 value_438;                       // 438
    sint16 value_43A;                       // 43A
    sint16 value_43C;                       // 43C
    uint8 reserved43E[0x2];                 // 43E
    uint16 value_440;                       // 440
    sint16 value_442;                       // 442
    sint32 value_444;                       // 444
    sint32 value_448;                       // 448
    sint16 value_44C;                       // 44C
    uint16 value_44E;                       // 44E
    uint8 reserved450[0x8];                 // 450
    sint32 value_458;                       // 458
    sint32 value_45C;                       // 45C
    uint8 reserved460[0x8];                 // 460
    uint8 track_468[0x10];                  // 468: func_80036478
    uint8 reserved478[0x8];                 // 478
    sint32 value_480;                       // 480
    sint32 value_484;                       // 484
    sint32 value_488;                       // 488
    sint32 value_48C;                       // 48C
    uint8 reserved490[0x10];                // 490
    sint32 value_4A0;                       // 4A0
    sint32 value_4A4;                       // 4A4
    uint8 reserved4A8[0x8];                 // 4A8
    sint32 value_4B0;                       // 4B0
    sint32 value_4B4;                       // 4B4
    sint32 value_4B8;                       // 4B8
    sint32 value_4BC;                       // 4BC
    sint16 value_4C0;                       // 4C0
    uint16 value_4C2;                       // 4C2
    sint32 value_4C4;                       // 4C4
    uint16 value_4C8;                       // 4C8
    uint8 reserved4CA[0x2];                 // 4CA
    sint32 value_4CC;                       // 4CC
    uint8 reserved4D0[0x10];                // 4D0
    STAGE_FACE face;                        // 4E0
} ST06_OBJ;

typedef void (*ST06_OBJ_FUNC)(ST06_OBJ *wp);

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
    STCOM_SVECTOR rotation;            // 54
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
    ST06_BEAM *owner_B8;               // B8
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
} ST06_10C;

typedef void (*ST06_10C_FUNC)(ST06_10C *wp);

// A view of STAGE_FX with the fields r3_st06's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    uint8 flags_0;   // 00
    uint8 value_1;   // 01
    uint8 kind_2;    // 02
    uint8 variant_3; // 03
    uint8 value_4;   // 04
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
} ST06_FX;

typedef void (*ST06_FX_FUNC)(ST06_FX *wp);

void func_80114AE8(STAGE_OBJ *wp);

void func_80100D78(STAGE_ROOM *wp);

sint32 func_801010C4(void);

void func_80102878(void);

void func_80102898(void);

void Sce_event_next(void);
void func_80105C14(void);

void func_801140DC(STAGE_OBJ *wp);

void func_80114430(STAGE_OBJ *wp);

void func_80115248(STAGE_OBJ *wp);

void func_801155C8(STAGE_OBJ *wp);

void func_80117784(STAGE_OBJ *wp);

extern STAGE_REC D_8012B990[];
void func_801023D0(uint8 index);

void func_80101A38(void);

void func_80120A0C(STAGE_OBJ *wp);

void func_80102124(void);

void func_8010313C(STAGE_OBJ *wp);

void func_80103DC8(STAGE_ROOM *wp);

void func_80103DF4(STAGE_ROOM *wp);

void func_80103EA4(STAGE_ROOM *wp);

void func_80114EE4(STAGE_OBJ *wp);

void func_8010772C(STAGE_OBJ *wp);

// The two objects func_801010E4 spawns ([1] is also reached as D_8012BECC).
extern STAGE_OBJ *D_8012BEC8[];
extern sint32 D_8012BECC;
// D_800BC7F0 written as an array (the same symbol): an array store keeps its place among struct
// stores (func_8010130C).
extern uint8 *D_800BC7F0_A[] __asm__("D_800BC7F0");
void func_80101294(void);

void func_80114AFC(STAGE_OBJ *wp);

extern STAGE_ROOM2_FUNC D_801231D4[];
void func_80102430(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_80123490[];
void func_80102A34(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_801239E8[];
void func_80103710(STAGE_ROOM *wp);

extern STAGE_ROOM2_FUNC D_801245F0[];
void func_801074F0(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_80125130[];
void func_8010BDEC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8012513C[];
void func_8010BE28(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125164[];
void func_8010C3CC(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801251A4[];
void func_8010DAA4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125198[];
void func_8010DA68(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801251CC[];
void func_8010E0E0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125368[];
void func_80111EA8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801253D0[];
void func_80112C24(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801253DC[];
void func_80112C60(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125424[];
void func_80113748(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125418[];
void func_8011370C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8012551C[];
void func_8011494C(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8012547C[];
void func_80114450(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_801258DC[];
void func_80118CE4(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125568[];
void func_80115764(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125914[];
void func_801194D8(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125A6C[];
void func_8011AD50(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_80125A74[];
void func_8011AFD0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8012B82C[];
void func_8011F2B0(STAGE_OBJ *wp);

extern STAGE_OBJ_FUNC D_8012B910[];
void func_801208B0(STAGE_OBJ *wp);

void func_8010130C(STAGE_ROOM *wp);
void func_80101470(STAGE_ROOM *wp);
void func_801012CC(STAGE_ROOM *wp);

void func_80103240(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_80125554[];
void func_801154E4(STAGE_OBJ *wp);

void func_80103B98(STAGE_ROOM *wp);

extern sint32 D_8012BB18;
void func_8011AD8C(STAGE_OBJ *wp);

void func_801077EC(STAGE_OBJ *wp);

void func_8010EDEC(STAGE_OBJ *wp);

void func_80113310(STAGE_OBJ *wp);

void func_801168E0(STAGE_OBJ *wp);

void func_80116A40(STAGE_OBJ *wp);

extern uint32 D_801228A4;
void func_80102238(void);

void func_80103BE4(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_80125480[];
void func_8011448C(STAGE_OBJ *wp);

void func_80100ADC(STAGE_ROOM *wp);

void func_80103ED0(uint8 arg0);

void func_8010C2B4(STAGE_OBJ *wp);

void func_8010DF30(STAGE_OBJ *wp);

void func_801130F4(STAGE_OBJ *wp);

void func_80113BDC(STAGE_OBJ *wp);

void func_80106A44(sint16 arg0, sint16 arg1, sint16 arg2, sint16 arg3);

void func_80102CE8(sint8 *arg0);

void func_801151D8(STAGE_OBJ *wp);

void func_80103304(STAGE_ROOM *wp);

void func_80103280(STAGE_ROOM *wp);

void func_80107E08(STAGE_ROOM *wp);
sint32 func_80107DB0(void);

void func_80104654(STAGE_ROOM *wp);

void func_8010483C(STAGE_ROOM *wp);

void func_801048C4(STAGE_ROOM *wp);

void func_80104B74(STAGE_ROOM *wp);

void func_80104C98(STAGE_ROOM *wp);

void func_80104FE8(STAGE_ROOM *wp);

void func_80105548(STAGE_ROOM *wp);

void func_80105730(STAGE_ROOM *wp);

void func_801057B8(STAGE_ROOM *wp);

void func_80105A68(STAGE_ROOM *wp);

void func_80105B8C(STAGE_ROOM *wp);

void func_80103B0C(STAGE_ROOM *wp);

extern sint16 D_8012462C;
extern sint16 D_8012462E;
extern sint16 D_80124630;
void func_80107E8C(STAGE_ROOM *wp);

void func_801046DC(STAGE_ROOM *wp);

void func_801055D0(STAGE_ROOM *wp);

void func_80104AAC(STAGE_ROOM *wp);

void func_801059A0(STAGE_ROOM *wp);

void func_80103CD8(STAGE_ROOM *wp);

extern STAGE_FX_FUNC D_8012B94C[];
extern STAGE_FX_FUNC D_8012B950[];
extern STAGE_SLOT_FUNC *D_80121BD8[];
extern STAGE_SLOT_FUNC *D_80121D14[];
extern STAGE_SLOT_FUNC D_80121D4C[];
extern STAGE_SLOT_FUNC D_80121E0C[];
extern STAGE_SLOT_FUNC D_80121E40[];
extern STAGE_SLOT_FUNC D_80121E64[];

// Used by functions still in assembly (types from their accesses).
extern sint32 D_800987E0;
extern uint8 D_800989FC;
extern uint8 D_800989FD;
extern sint16 D_800BBCF8[];
extern sint16 D_800BBD38[];
extern STAGE_CAM Sce_camera_work;
extern sint16 D_800C0F96[];
extern uint8 D_80100474[];
extern sint32 D_801224F0[];
extern uint8 D_80122668[];
extern uint8 D_80122678[];
extern uint8 D_80122680[];
extern uint8 D_801226A4[];
extern uint8 D_801226AC[][8];
// A record func_801011D8 spawns an object from: kind, handler, variant, a word for +0xC, and the
// position with the angle in pad.
typedef struct
{
    uint8 reserved0;     // 00
    uint8 kind_1;        // 01
    uint8 handler_2;     // 02
    uint8 reserved3;     // 03
    uint8 variant_4;     // 04
    uint8 reserved5[3];  // 05
    sint32 value_8;      // 08
    STCOM_SVECTOR pos_C; // 0C
} ST06_SPAWN;

extern ST06_SPAWN D_8012271C[];
extern STAGE_ROOM2_FUNC D_80122744[];
extern STAGE_ROOM2_FUNC D_80122754[];
extern STAGE_ROOM2_FUNC D_80123130[];
extern uint8 D_80123140[];
// A group of objects func_8010214C spawns: how many, then their 0x14-byte spawn records (the first
// byte is the scene slot).
typedef struct
{
    uint32 count_0;
    uint8 (*list_4)[0x14];
} ST06_SPAWN_GROUP;

extern ST06_SPAWN_GROUP D_80123194[];
extern ST06_SPAWN D_801231E0[];
extern uint8 D_801231F4[];
extern STAGE_ROOM2_FUNC D_80123240[];
extern uint8 D_80123250[];
extern STAGE_ROOM2_FUNC D_80123468[];
extern uint8 D_801234AC[];
// Per room variant (func_80102B3C): the room data, its script table and the file to load.
extern uint8 *D_801238CC[];
extern STAGE_ROOM2_FUNC *D_801238E0[];
extern uint32 D_801238F4[];
extern ST06_SPAWN D_80123908[];
extern ST06_SPAWN D_8012391C[];
extern uint8 D_80123944[];
extern STAGE_ROOM2_FUNC D_801239C0[];
extern ST06_SPAWN D_801239F4[];
extern STAGE_SCRIPT_ENTRY D_80123A08[];
extern uint8 D_80123A1C[];
extern uint8 D_80123A30[];
extern uint8 D_80123A80[];
extern STAGE_ROOM2_FUNC D_80123E70[];
extern STAGE_ROOM2_FUNC D_80123E80[];
extern uint8 D_80123EF0;
extern uint16 D_80123EF2;
extern uint16 D_80123EF4;
// A room model's flags and two values, as func_80103C34 copies them into models 1 to 4.
typedef struct
{
    uint8 flags_0;   // 0
    uint8 reserved1; // 1
    sint16 value_2;  // 2
    sint16 value_4;  // 4
} ST06_MODEL_INIT;

extern ST06_MODEL_INIT D_80123EF6[];
extern ST06_SPAWN D_80123EFC[];
extern ST06_SPAWN D_80123F4C[];
extern uint8 D_80123F74[];
extern uint8 D_8012411C[];
extern STAGE_ROOM2_FUNC D_801242C4[];
extern STAGE_ROOM2_FUNC D_80124374[];
extern uint8 D_80124434[][0x14];
extern uint8 D_80124484[];
extern STAGE_ROOM2_FUNC D_801245B0[];
// Where func_801075A0 puts the player, by the room object's value_6.
typedef struct
{
    sint32 x, y, z;
    sint32 angle;
} ST06_PL_START;

extern ST06_PL_START D_801245FC[];
extern ST06_SPAWN D_80124634[];
extern uint8 *D_801247D8[];
extern STAGE_ROOM2_FUNC D_801247E4[];
extern STAGE_ROOM2_FUNC D_801247F4[];
extern uint8 D_80124824[];
extern STAGE_SCRIPT_ENTRY D_801248E4[];
extern STAGE_ROOM2_FUNC D_80124934[];
extern uint8 D_80125158[];
extern uint8 D_8012518C[];
extern uint8 D_801251C0[];
extern uint8 D_801251E4[];
extern uint8 D_801251F8[];
extern uint8 D_80125240[];
extern uint8 D_8012526C[];
extern STCOM_SVECTOR D_80125278[][10]; // each variant's path points (ST06_CRAB_CTL's rec_0)
extern uint8 D_80125384[];
extern uint8 D_80125390[];
extern STCOM_SVECTOR D_8012539C[]; // walk targets by value_D, the turn speed in pad (func_8011232C)
extern STCOM_SVECTOR D_801253AC;
extern uint32 D_801253B4[]; // squared arrival distances by value_D
extern uint8 D_801253C4[];
extern uint8 D_801253F8[];
extern uint8 D_8012540C[];
extern uint8 D_80125440[];
extern uint8 D_80125458[];
extern uint8 D_80125470[];
// An animation and its argument for func_800322A8, by routine (func_80114798).
typedef struct
{
    uint8 anim_0;    // 0
    uint8 arg_1;     // 1
    uint8 loops_2;   // 2: how often to play it (func_80114648)
    uint8 reserved3; // 3
} ST06_ANIM;

extern ST06_ANIM D_801254A4[];
// When func_80114880's object starts and stops blinking: a scene (0xFF ends the list) and its frame.
typedef struct
{
    uint8 scene_0;   // 0
    uint8 reserved1; // 1
    sint16 frame_2;  // 2
} ST06_CUE;

extern ST06_CUE D_801254C8[];
extern uint8 D_801258AC[];
extern STCOM_SVECTOR D_801258B8; // the point the crab family heads for (func_8011837C)
extern sint16 D_801258C0;
extern sint16 D_801258C2;
extern sint16 D_801258C4;
extern sint16 D_801258C6;
extern uint16 D_801258C8[];
extern uint8 D_801258D4[];
// Where each of the seven crabs starts (func_801196E8): a word for +0xC and the position, with the
// angle in pad.
typedef struct
{
    uint8 flags_0;       // 00
    uint8 kind_1;        // 01: for +2
    uint8 value_2;       // 02: for +4
    uint8 variant_3;     // 03
    sint32 value_4;      // 04
    STCOM_SVECTOR pos_8; // 08
} ST06_CRAB_START;

extern ST06_CRAB_START D_80125924[]; // the crabs' first spawn (func_80119514)
extern ST06_CRAB_START D_80125994[];
extern STCOM_SVECTOR D_80125A80[];
extern uint8 D_8012B7D8[];
extern uint16 D_8012B7E4[];
extern STCOM_FIXED_VECTOR D_8012B838; // the scale
// A leg of func_80120AAC's route: where it ends along the heading, then the turn per frame (0 ends).
typedef struct
{
    sint16 limit_0; // 0
    sint16 turn_2;  // 2
} ST06_LEG;

extern ST06_LEG D_8012B91C[];
// Where each of func_801215CC's particle columns starts.
extern STCOM_SVECTOR D_8012B954[];
extern uint16 D_8012B984[];
extern uint8 D_8012BA00;
extern sint16 D_8012BA08;
extern sint32 D_8012BA24;
extern sint32 D_8012BA28;
extern sint16 D_8012BA30;
extern sint16 D_8012BA38;
extern sint32 D_8012BA44;
extern sint32 D_8012BA48;
extern STCOM_FIXED_VECTOR D_8012BA50;
extern sint32 D_8012BA64;
extern sint32 D_8012BA68;
extern sint16 D_8012BA70;
extern sint32 D_8012BA7C;
extern sint32 D_8012BA80;
extern sint16 D_8012BA88;
extern sint16 D_8012BA98;
extern uint16 D_8012BAA0;
extern uint8 D_8012BAA4;
extern uint8 D_8012BAA8;
extern STCOM_EFFECT *D_8012BB20[]; // six effect slots
extern sint32 D_8012BB3C[];
// Sixteen particle positions per column (func_801215CC).
extern STCOM_SVECTOR D_8012BB88[][16];
extern STAGE_OBJ *D_8012BE94; // D_8012BE88[3]
extern STAGE_OBJ *D_8012BE98;
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern sint32 D_80164008[];

void func_8011505C(ST06_BEAM *wp, sint32 arg1);

void func_801177A4(ST06_OBJ *wp);

void func_80115670(ST06_10C *wp);

void func_80116520(ST06_OBJ *wp);

extern ST06_OBJ_FUNC D_80125884[];
void func_8011710C(ST06_OBJ *wp);

void func_8010752C(ST06_OBJ *wp);

void func_801010E4(ST06_SPAWN *rec);
void func_80100928(ST06_OBJ *wp);

void func_80102C5C(ST06_OBJ *wp);

extern ST06_OBJ_FUNC D_80125538[];
void func_80115078(ST06_OBJ *wp);

void func_80103998(ST06_OBJ *wp);

extern sint16 *D_801257A4[];
extern sint16 *D_80125810[];

void func_80116A8C(void *wp, STAGE_FACE16 *face, sint32 index);

void func_80031A4C(void *wp);

void func_801011D8(ST06_SPAWN *rec);
extern ST06_SPAWN D_80122688[];
extern void *D_80123188[];

extern void *D_80121EE4[];
extern void *D_801220A0[];
extern void *D_80122208[];
extern uint8 D_80122220[][0x28];
extern uint8 D_80122310[][8];

void Sound_key_off_voice(sint32 voice);
void func_8003187C(void *wp);
void Sce_flag_off(sint32 flag);
void func_8001E3F0(sint32 arg);
void func_8003697C(void);
void func_801006B8(void);

// A 0x20-byte control block of ST06_ACTOR (at +0x348 and +0x368).
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
} ST06_ACTOR_CTL;

// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 value_4;                          // 04
    uint8 reserved05[3];                    // 05
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
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    void *value_78;                         // 78: a motion table
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
    uint8 reservedCC[0x30];                 // CC
    uint8 value_FC;                         // FC
    uint8 reservedFD[0x5B];                 // FD
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x18];                // 188
    STCOM_SVECTOR pos_1A0;                  // 1A0: a hit box's center
    uint8 reserved1A8[0x128];               // 1A8
    uint32 hit_2D0;                         // 2D0: kind bits in the top byte
    uint8 reserved2D4[0x60];                // 2D4
    uint16 kind_334;                        // 334: or'd into the hit's kind bits
    uint8 reserved336[2];                   // 336
    STCOM_SVECTOR hit_pos_338;              // 338
    uint32 hit_340;                         // 340: filled by func_800341BC
    uint8 reserved344[4];                   // 344
    ST06_ACTOR_CTL ctl;                     // 348
    ST06_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST06_ACTOR;

typedef void (*ST06_ACTOR_FUNC)(ST06_ACTOR *wp);

// A 0x10C-byte work slot as this stage's own objects use it (STCOM05_WORK's layout, with the hit
// record at +0xBC).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 value_C;                          // 0C
    sint8 value_D;                          // 0D
    sint8 value_E;                          // 0E
    sint8 value_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    sint16 value_4C;                        // 4C
    sint16 value_4E;                        // 4E
    sint16 value_50;                        // 50
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 turn_64;                         // 64
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    void *data_78;                          // 78
    uint8 reserved7C[0x10];                 // 7C
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR pos_AC;                   // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    sint32 hit_BC;                          // BC: hit result bits
    uint8 reservedC0[0xC];                  // C0
    sint32 speed_CC;                        // CC
    uint8 reservedD0[0x3C];                 // D0
} ST06_10C_B;

extern STAGE_ROOM_FUNC D_80122650[];
extern STAGE_ROOM_FUNC *D_80122610[];
void func_80100764(void);
extern ST06_ACTOR_FUNC D_801253BC[];
void func_801124BC(ST06_ACTOR *wp);
void func_80112ED0(STAGE_OBJ *wp);
void func_801139B8(STAGE_OBJ *wp);
extern STAGE_ACTOR_FUNC D_8012544C[];
void func_80113CF4(STAGE_ACTOR *wp);
extern STAGE_ACTOR_FUNC D_80125464[];
void func_801140FC(STAGE_ACTOR *wp);
void func_80115A58(STAGE_OBJ *wp);
extern STAGE_OBJ_FUNC D_801255A0[];
void func_80116AD4(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_80115F34(STAGE_OBJ *wp);
void func_80120A2C(ST06_10C_B *wp, sint16 scale);
void func_8010C090(STAGE_OBJ *wp);
void func_8010C408(STAGE_OBJ *wp);
extern ST06_ACTOR_FUNC D_80125184[];
void func_8010D1F8(ST06_ACTOR *wp);
void func_8010DD0C(STAGE_OBJ *wp);

sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
extern STCOM_FIXED_VECTOR D_8012BA60;
sint32 func_80112A60(ST06_ACTOR *wp);

extern STCOM_FIXED_VECTOR D_8012BA20;
sint32 func_8010D8A4(ST06_ACTOR *wp);

void func_801138A0(ST06_ACTOR *wp);
void func_8010BF78(ST06_ACTOR *wp);
void func_8010DBF4(ST06_ACTOR *wp);
void func_8010E11C(ST06_ACTOR *wp);

extern ST06_ACTOR_FUNC D_801253F0[];

extern ST06_ACTOR_FUNC D_80125438[];
void func_80113678(ST06_ACTOR *wp);
void func_80113C40(ST06_ACTOR *wp);
extern ST06_ACTOR_FUNC D_80125150[];
void func_8010BD58(ST06_ACTOR *wp);
void func_8010C318(ST06_ACTOR *wp);
extern ST06_ACTOR_FUNC D_801251B8[];
void func_8010D9D4(ST06_ACTOR *wp);
void func_8010DF94(ST06_ACTOR *wp);

void func_8010C0F4(ST06_ACTOR *wp);
void func_8010C20C(ST06_ACTOR *wp);
void func_8010DD70(ST06_ACTOR *wp);
void func_8010DE88(ST06_ACTOR *wp);
void func_8010E234(ST06_ACTOR *wp);

extern STAGE_PL_SCRIPT_FUNC D_801245AC[];

extern STAGE_PL_SCRIPT_FUNC D_80124954[];
void func_80108074(STAGE_PL_SCRIPT *wp);

extern STAGE_SPAWNED *D_8012BE88[];
void func_80102288(sint8 index);

void func_80111BE0(STCOM_SVECTOR *pos);

extern STCOM_FIXED_VECTOR D_8012BA78;
sint32 func_80113548(ST06_ACTOR *wp);

void func_80113B34(ST06_ACTOR *wp);

extern STCOM_FIXED_VECTOR D_8012BA40;
sint32 func_8010F024(ST06_ACTOR *wp);

sint32 func_80048E6C(void *wp);

void func_801134B8(ST06_ACTOR *wp);

extern ST06_ACTOR_FUNC D_8012556C[];
void func_801158B8(ST06_ACTOR *wp);
void func_8010EF94(ST06_ACTOR *wp);

// A ROCK_NEO record per object kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // 08: in units of 8 or 16
    uint8 limit_9; // 09: a damage threshold (func_80118B2C)
    uint8 value_A; // 0A
    uint8 value_B; // 0B: func_80037738's amount (func_801180F8)
} ST06_KIND;

extern ST06_KIND **D_80098844;

void func_80105AF0(STAGE_ROOM *wp);

void func_80100C44(STAGE_ROOM *wp);
void func_801054A8(STAGE_ROOM *wp);

void func_801141EC(ST06_ACTOR *wp);

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
    STCOM_SVECTOR accel_4C;                 // 4C
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
    uint8 reserved188[0x1C0];               // 188
    ST06_ACTOR_CTL ctl;                     // 348
    ST06_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST06_ACTOR_B;

void func_8011594C(ST06_ACTOR_B *wp);

// The control block at +0x328 of this stage's own 0x3C0-byte enemies (func_8010F35C and
// func_80110CFC set them up); its tail differs by kind.
typedef struct
{
    STAGE_OBJ *owner_0;       // 328
    uint16 flags_4;           // 32C
    uint16 random_6;          // 32E: a new random number every frame
    sint16 timer_8;           // 330
    sint16 value_A;           // 332
    uint16 kind_C;            // 334: or'd into the hit's kind bits
    uint8 reservedE[2];       // 336
    STCOM_SVECTOR hit_pos_10; // 338
    sint32 hit_18;            // 340: damage in the low 24 bits, kind bits above
    sint32 value_1C;          // 344
    uint8 reserved20[0xC];    // 348
    sint32 value_2C;          // 354
    uint8 reserved30[8];      // 358
    union
    {
        uint32 dist;
        struct
        {
            sint16 lo;
            sint16 hi;
        } h;
    } u_38; // 360
    union
    {
        struct
        {
            sint8 reserved0;
            sint8 turn_1;           // 365
            STCOM_SVECTOR target_2; // 366
        } a;
        struct
        {
            STCOM_SVECTOR *rec_0; // 364: D_80125278[variant]
            uint8 reserved4[2];   // 368
            uint8 flag_6;         // 36A
            uint8 value_7;        // 36B
            uint8 value_8;        // 36C
        } b;
    } u_3C;                 // 364
    uint8 reserved48[0x50]; // 370
} ST06_CRAB_CTL;

// The block at +0x440 of func_80117290's family: its flags, timers and three hit spheres (the body
// and joints 5 and 10).
typedef struct
{
    uint16 flags_0;  // 440
    sint16 random_2; // 442: a new random number every frame
    union
    {
        sint32 word;
        struct
        {
            sint16 timer_4; // 444
            sint16 hi;
        } h;
    } u_4; // 444
    union
    {
        sint32 word;
        struct
        {
            sint16 lo;
            sint16 timer_A; // 44A
        } h;
    } u_8;                             // 448
    uint16 timer_C;                    // 44C
    uint16 timer_E;                    // 44E
    STCOM_SVECTOR hit_pos_10;          // 450
    uint32 hit_18;                     // 458: filled by func_800341BC
    sint32 value_1C;                   // 45C
    uint8 reserved20[8];               // 460
    uint8 track_28[0x10];              // 468: func_80036478
    STCOM_SVECTOR_W probe_38;          // 478: a point ahead (func_80118708), or a rotation
    STCOM_FIXED_VECTOR probe_fixed_40; // 480: or a scale (func_801189B4)
    STCOM_SVECTOR target_50;           // 490: the point it turns to
    STCOM_SVECTOR hit_pos_58;          // 498: joint 5
    uint32 hit_60;                     // 4A0
    sint32 value_64;                   // 4A4
    STCOM_SVECTOR hit_pos_68;          // 4A8: joint 10
    uint32 hit_70;                     // 4B0
    sint32 value_74;                   // 4B4
    sint32 ground_78;                  // 4B8: func_8004B414's result
    sint32 hit_7C;                     // 4BC: func_80049C54's result
    uint16 timer_80;                   // 4C0
    uint16 timer_82;                   // 4C2
    STAGE_OBJ *child_84;               // 4C4: func_80117BF0
    uint16 value_88;                   // 4C8
    uint8 reserved8A[2];               // 4CA
    sint32 area_8C;                    // 4CC: Map_cell_get's result
} ST06_CRAB_BODY;

// A 0x3C0-byte enemy slot of this stage (STAGE_OBJ's fields, then ST06_CRAB_CTL at +0x328).
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
        struct
        {
            uint8 byte_C; // 0C
            uint8 byte_D; // 0D
        } ub;
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
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[4];                    // 7C
    uint32 dist_80;                         // 80: squared distance to the player
    uint8 reserved84[4];                    // 84
    void *model_88;                         // 88
    uint8 reserved8C[0xC];                  // 8C
    uint8 *anim_98;                         // 98: current animation frame
    uint8 reserved9C[0x8];                  // 9C
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[0x4];                  // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2: life_6E before this frame's hits
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x34];                 // CC
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
    uint8 reserved308[0x20];                // 308
    ST06_CRAB_CTL ctl;                      // 328
    uint8 reserved3C0[0x80];                // 3C0
    ST06_CRAB_BODY body;                    // 440: func_80117290's family
} ST06_CRAB;

extern ST06_CRAB *D_8012BAAC[]; // the seven crabs

typedef void (*ST06_CRAB_FUNC)(ST06_CRAB *wp);

extern ST06_CRAB_FUNC D_80125218[];
extern ST06_CRAB_FUNC D_80125234[];
extern ST06_CRAB_FUNC D_8012525C[];
void func_8010F7E8(ST06_CRAB *wp);
void func_80110734(STCOM_SVECTOR *pos);
void func_801107A0(ST06_CRAB *wp);
sint32 func_80110AF0(ST06_CRAB *wp);
void func_80111250(ST06_CRAB *wp);
void func_80111A30(ST06_CRAB *wp);
void func_80111AFC(ST06_CRAB *wp);
void func_80111CF8(ST06_CRAB *wp);
sint32 func_80111DF0(ST06_CRAB *wp);
void func_80052528(void *wp);
sint32 func_80110A54(ST06_CRAB *wp);
sint32 func_80111D54(ST06_CRAB *wp);
void func_80110498(ST06_CRAB *wp);
void func_80111C4C(ST06_CRAB *wp);
sint32 func_80030418(void *a, void *b, STCOM_SVECTOR *size, STCOM_FIXED_VECTOR *out);
extern ST06_CRAB_FUNC D_80125204[];

// The scratchpad as the crab writes it: two angles its model's draw reads.
typedef struct
{
    uint8 reserved000[0x150]; // 000
    uint16 angle_150;         // 150
    uint8 reserved152[6];     // 152
    uint16 angle_158;         // 158
} ST06_SCRATCH;

#define ST06_SP ((ST06_SCRATCH *)0x1F800000)
extern ST06_CRAB_FUNC D_8012524C[];
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);
sint32 SquareRoot0(sint32 v);
// The crabs pass only two arguments (retail leaves a2 as the call before left it).
void func_80047148(void *wp, STCOM_SVECTOR *pos);

// The 0x10C-byte slot func_80111C4C spawns at the crab (kind 6: stcom06's emitter, like
// stcom15's STCOM15_SHOT).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[4];               // 04
    uint32 routine_8;                  // 08: routine_0..3
    uint32 value_C;                    // 0C
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    uint8 reserved66[0x36];            // 66
    sint32 speed_9C;                   // 9C
    sint32 rise_A0;                    // A0
} ST06_SHOT;

sint32 func_80048E18(void *arg);

void func_80104DF8(STAGE_ROOM *wp);

// A 0x3C0-byte slot with a halfword face at +0x4E0 and a byte at +0x10C (func_80116048).
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
    uint8 reserved101[0xB];                 // 101
    uint8 value_10C;                        // 10C
    uint8 reserved10D[3];                   // 10D
    uint8 value_110;                        // 110
    uint8 reserved111[7];                   // 111
    uint8 value_118;                        // 118
    uint8 reserved119[0x2F];                // 119
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
    STAGE_FACE16 face16_4E0;                // 4E0
} ST06_TALKER;

// STAGE_MATRIX_OBJ with its index bytes named (func_80118D20).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    sint8 index_C;          // 0C
    sint8 value_D;          // 0D
    uint8 reserved0E[6];    // 0E
    void *model_14;         // 14
    STAGE_MATRIX matrix_18; // 18
    STCOM_SVECTOR pos_38;   // 38
    uint32 color_40;        // 40
} ST06_MATRIX_OBJ;

STCOM_MATRIX *MulMatrix2(STCOM_MATRIX *m0, STCOM_MATRIX *m1);

// A slot that waits a number of frames before setting a scene flag (func_80119AF8).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 reserved01[7]; // 01
    uint8 routine_0;     // 08
    uint8 routine_1;     // 09
    uint8 routine_2;     // 0A
    uint8 routine_3;     // 0B
    uint8 reserved0C[8]; // 0C
    sint32 timer_14;     // 14
} ST06_WAIT;

// The boat's state at +0xCC (func_8011E75C's object).
typedef struct
{
    uint16 flags_0;     // 00: bit 0 while it can be hit
    sint16 angle_2;     // 02
    sint16 wave_4;      // 04: index into D_800BBCF8, 0 to 63
    uint8 reserved6[2]; // 06
    sint32 life_8;      // 08
    sint32 life_prev_C; // 0C
    sint32 hit_10;      // 10: from func_800341BC
} ST06_BOAT_CTL;

// A 0x10C-byte slot: the boat that bobs on the waves (func_8011E75C).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 timer_C;                          // 0C
    uint8 sway_D;                           // 0D
    uint8 reserved0E[2];                    // 0E
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x14];                 // 64
    uint8 *data_78;                         // 78
    uint8 reserved7C[0x10];                 // 7C
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC
    sint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    ST06_BOAT_CTL ctl_CC;                   // CC
    uint8 reservedE0[0x2C];                 // E0
} ST06_BOAT;

typedef void (*ST06_BOAT_FUNC)(ST06_BOAT *wp, ST06_BOAT_CTL *ctl);

extern ST06_BOAT_FUNC D_8012B7CC[];

extern STAGE_OBJ_FUNC D_801251E0[];

extern STAGE_ROOM_FUNC D_801228A8[];

void func_80113A1C(ST06_ACTOR *wp);

void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);

void func_801067CC(STAGE_ROOM *wp);

// The block at +0x440 of a floating prop driven by the scene (D_8012587C's routines).
typedef struct
{
    sint16 count_0; // 0
    sint16 base_2;  // 2: its resting height
} ST06_FLOAT;

typedef void (*ST06_FLOAT_FUNC)(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST06_FLOAT *fl);

extern ST06_FLOAT_FUNC D_8012587C[];

extern STAGE_OBJ_FUNC D_801251F0[];

extern STAGE_OBJ_FUNC D_80125404[];

extern ST06_ACTOR_FUNC D_80125374[];
sint32 func_80112488(ST06_ACTOR *wp);

void func_8011201C(ST06_ACTOR *wp);

void func_8001E390(sint32 id);

sint32 Map_cell_get(STCOM_SVECTOR *pos);

sint32 func_80037C14(sint32 cell);

void func_80114880(ST06_ACTOR *wp);

STAGE_OBJ *func_80031498(void);

void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 color);

sint32 func_80049C54(STCOM_SVECTOR *pos, STCOM_SVECTOR *prev, void *info, sint32 mask);

void func_80039E50(void);

void func_8010214C(sint8 index);

extern STAGE_ACTOR D_8009F108[]; // ROCK_NEO's 0x3C0-byte slots

void func_8003A264(void);

void func_8001E460(sint32 a0, sint32 a1, sint32 a2);

uint8 *Model_face_get(void *model, sint32 id);

extern ST06_KIND **D_8009884C; // the same record layout as D_80098844 (func_80117160)

extern ST06_CRAB_FUNC D_80125890[];

void func_80117290(ST06_CRAB *wp);

sint32 func_80118884(ST06_CRAB *wp);

void func_8005D4C0(void);

void func_8005D6E8(void *wp);

sint32 func_8003B360(sint32 area);

sint32 func_80042208(void);

sint32 func_80118B2C(ST06_CRAB *wp);

sint32 func_801189B4(ST06_CRAB *wp);

// A 0x10C-byte slot that func_801189B4 throws: it homes on target_B8.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 value_1;          // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[0x10]; // 04
    STCOM_SVECTOR position; // 14
    uint8 reserved1C[0x70]; // 1C
    STAGE_MATRIX matrix_8C; // 8C
    uint8 reservedAC[0xC];  // AC
    uint8 *target_B8;       // B8
    uint8 reservedBC[0x50]; // BC
} ST06_HOMER;

sint32 func_80118708(ST06_CRAB *wp);

sint32 func_801187D4(ST06_CRAB *wp);

sint32 Distance_xz(sint16 *a, sint16 *b);

sint16 func_80031CA4(STCOM_SVECTOR *a, STCOM_SVECTOR *b, sint32 c, sint32 d);

void ApplyMatrix(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_FIXED_VECTOR *out);

void VectorNormalS(STCOM_FIXED_VECTOR *v0, STCOM_SVECTOR *v1);

sint32 func_80114F10(ST06_BEAM *wp);
void func_80114F48(ST06_BEAM *wp);
void func_80114FA8(ST06_BEAM *wp, uint8 index);

sint32 func_8003B2D4(sint32 row, sint32 bit);

sint16 func_8010EB68(void);

sint32 Money_check(sint32 a0);

void Money_add(sint32 a0, sint32 a1, sint32 a2);

void func_8005C224(sint32 price);

sint32 func_80048EA4(STCOM_SVECTOR *pos, void *arg1, sint32 arg2, sint32 arg3);

// A 0x50-byte slot (func_80031734) as func_8011B00C starts it.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 value_4;          // 04
    uint8 reserved05[7];    // 05
    uint32 value_C;         // 0C
    uint8 reserved10[0x40]; // 10
} ST06_SLOT50;

// The 0x24-byte event slot of func_8011AFD0's family (STAGE_EVENT with its fields named).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 reserved01[7];    // 01
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 reserved0A[0x12]; // 0A
    ST06_SLOT50 *slot_1C;   // 1C
    uint8 reserved20[4];    // 20
} ST06_EVENT;

sint32 func_8011B444(void);

void func_8011B4E0(sint32 level);

void func_8005D4D4(void);

void func_8005D4E8(void);

void func_80119B78(ST06_CRAB *wp, sint16 slot, uint8 variant);

extern uint8 *D_80122894;
extern uint8 *D_80122898;
extern uint8 *D_8012289C;
extern uint8 *D_801228A0;

// STAGE_PL_SCRIPT with the talk target at +0x184 named (func_80107F24).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01[0xB];             // 01
    sint8 routine_C;                   // 0C
    sint8 routine_D;                   // 0D
    sint8 timer_E;                     // 0E
    uint8 reserved0F[0x5];             // 0F
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x158];           // 2C
    void *target_184;                  // 184
    uint8 reserved188[0x2A0];          // 188
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    sint16 value_440;                  // 440
    uint16 value_442;                  // 442
    sint16 value_444;                  // 444
    uint8 reserved446[0x2];            // 446
    uint8 value_448;                   // 448
} ST06_PL_SCRIPT;

void Sce_event_timer_clear(void);

void func_80102388(uint8 index, uint8 kind);

void func_801023F4(void);

void func_80063BA8(void);

void func_8001B314(void);

void func_8005D7C0(void);

// A smoke puff's sprite packet (Billboard_get; stcom23's STCOM23_PACKET).
typedef struct
{
    uint32 tag_0;   // 00
    uint32 code_4;  // 04
    uint32 xy_8;    // 08
    uint32 uv_C;    // 0C: and the palette
    uint32 z_10;    // 10
    uint32 uv_14;   // 14: and the texture page
    uint32 size_18; // 18
    uint32 uv_1C;   // 1C
    uint32 pad_20;  // 20
    uint32 uv_24;   // 24
} ST06_PUFF;

ST06_PUFF *Billboard_get(void); // ROCK_NEO.EXE: a smoke puff packet

// The room-entry request at D_800C3558 (stcom22's STCOM22_ENTRY; only the fields used here).
typedef struct
{
    uint8 reserved00[0x15]; // 00
    sint8 flags15;          // 15
    uint8 reserved16[2];    // 16
    uint8 fade_in;          // 18
    uint8 fade_out;         // 19
} ST06_ENTRY;

extern ST06_ENTRY D_800C3558; // ROCK_NEO.EXE

void func_8001D974(void); // ROCK_NEO.EXE

void func_80039FFC(STCOM_FIXED_VECTOR *vec, sint32 arg1, sint32 arg2,
                   sint32 arg3); // ROCK_NEO.EXE: moves the camera

#endif
