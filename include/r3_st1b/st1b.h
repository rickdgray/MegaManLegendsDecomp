#ifndef ST1B_H
#define ST1B_H

#include "common.h"
#include "stage_common/stage.h"

// From r3_st03 (ST03_ACTOR_CTL).
// A 0x20-byte control block of ST1B_ACTOR (at +0x348 and +0x368).
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
} ST1B_ACTOR_CTL;

// From r3_st03 (ST03_ACTOR).
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
    uint8 reserved188[0x1C0];               // 188
    ST1B_ACTOR_CTL ctl;                     // 348
    ST1B_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST1B_ACTOR;

// From r3_st03 (STCOM01_CTL).
// The block at +0x348 of the work slot; routines take its address for its routine byte.
typedef struct
{
    uint16 flags;        // 348
    uint8 value_2;       // 34A
    uint8 routine;       // 34B
    sint16 value_4;      // 34C
    sint16 turn;         // 34E: turn speed
    sint16 timer;        // 350: countdown
    sint16 value_A;      // 352
    STCOM_SVECTOR pos_C; // 354
    sint16 value_14;     // 35C
    sint16 value_16;     // 35E
    sint16 value_18;     // 360
    sint16 value_1A;     // 362
    sint16 value_1C;     // 364
    sint16 value_1E;     // 366
    uint16 range_20;     // 368: how near the player must come (stcom01_func_01FC)
} ST1B_STCOM01_CTL;

// From r3_st03 (STCOM01_WORK).
// The work slot stcom01's routines run on. Freed through ROCK_NEO.EXE's func_80031824, so it is
// one of the 0x3C0-byte slots at D_8009F108 there (GAME_WORK_3C0 in ROCK_NEO's game.h, which
// names other fields; the two views aren't reconciled yet). Only the fields used so far.
typedef struct ST1B_STCOM01_WORK
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
    uint8 param_C;                          // 0C
    uint8 param_D;                          // 0D
    uint8 param_E;                          // 0E
    uint8 param_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 rot_goal_64;                     // 64: angle the slot turns toward
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint32 value_78;                        // 78
    uint8 reserved7C[0x2B];                 // 7C
    sint8 state_A7;                         // A7: negative ends routine_2's step
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC: animation (stcom01_func_28D8 picks it)
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x1E8];               // 160
    ST1B_STCOM01_CTL ctl;                   // 348
    uint8 reserved36A[0x56];                // 36A
} ST1B_STCOM01_WORK;

// From r3_st0d (ST0D_ORBIT, ST0D_ORBITER).
// The circle a ST1B_ORBITER runs round (+0xCC).
typedef struct
{
    sint16 x_0;         // CC: center
    sint16 y_2;         // CE
    sint16 z_4;         // D0
    sint16 speed_6;     // D2: added to the angle every frame
    sint16 angle_8;     // D4
    uint8 reservedA[2]; // D6
    sint32 radius_C;    // D8
} ST1B_ORBIT;

// A 0x10C-byte slot (Open_SHL_WORK) whose model runs round a circle (func_8010AF9C).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 reserved09[3];                    // 09
    sint8 value_C;                          // 0C: nonzero: func_8002F9EC sets it up
    sint8 radius_D;                         // 0D: radius / 10
    sint8 speed_E;                          // 0E
    sint8 reverse_F;                        // 0F: runs the other way round
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x28];                 // 64
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR position_AC;              // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    ST1B_ORBIT orbit;                       // CC
    uint8 reservedDC[0x30];                 // DC
} ST1B_ORBITER;

// From r3_st04 (ST04_CAM).
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
} ST1B_CAM;

// The camera request at D_800C3558 (D_800C3560..D_800C3571 are also reached through their own
// symbols).
typedef struct
{
    uint8 reserved00[8]; // 00
    sint16 x_8;          // 08
    sint16 y_A;          // 0A
    sint16 z_C;          // 0C
    uint8 reserved0E[4]; // 0E
    sint16 value_12;     // 12
    sint8 state_14;      // 14
    uint8 value_15;      // 15
    uint8 mode_16;       // 16
    uint8 value_17;      // 17
    uint8 value_18;      // 18
    uint8 value_19;      // 19
} ST1B_CAMERA;

// Game_work fields func_801021BC updates when the stage ends (play time at +0xC, its copy at
// +0x14, a saturating count at +0x18).
#define ST1B_GAME_TIME_C   (*(uint32 *)((uint8 *)&Game_work + 0xC))
#define ST1B_GAME_TIME_14  (*(uint32 *)((uint8 *)&Game_work + 0x14))
#define ST1B_GAME_COUNT_18 (*(uint16 *)((uint8 *)&Game_work + 0x18))
#define ST1B_GAME_FLAG_1A  (*(uint16 *)((uint8 *)&Game_work + 0x1A))
#define ST1B_GAME_VALUE_5B (*((sint8 *)&Game_work + 0x5B))

// The routines of D_8010E6EC: the work slot and the halfwords at its +0x328.
typedef void (*ST1B_BASE_FUNC)(STAGE_OBJ *wp, sint16 *base);

// A view of the work slots r3_st1b's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST1B_VIEW ST1B_VIEW;

typedef void (*ST1B_VIEW_FUNC)(ST1B_VIEW *wp);
struct ST1B_VIEW
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
    sint16 value_44;                        // 44
    uint8 reserved46[0x2];                  // 46
    sint16 value_48;                        // 48
    uint8 reserved4A[0xA];                  // 4A
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    uint8 reserved66[0x8];                  // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0x1C];                 // 7C
    sint32 value_98;                        // 98
    uint8 reserved9C[0x8];                  // 9C
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_A4;                 // A4
    uint8 reservedA8[0x4];  // A8
    STCOM_SVECTOR vec_AC;   // AC
    sint32 value_B4;        // B4
    uint8 reservedB8[0x14]; // B8
    uint16 value_CC;        // CC
    sint16 value_CE;        // CE
    uint16 value_D0;        // D0
    uint16 value_D2;        // D2
    sint16 value_D4;        // D4
    uint8 reservedD6[0x2];  // D6
    sint32 value_D8;        // D8
    uint8 reservedDC[0x20]; // DC
    uint8 value_FC;         // FC
    uint8 reservedFD[0x5B]; // FD
    sint32 value_158;       // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    uint8 reserved160[0x20];  // 160
    sint16 value_180;         // 180
    sint16 value_182;         // 182
    sint16 value_184;         // 184
    uint8 reserved186[0x35A]; // 186
    uint16 value_4E0;         // 4E0
    uint8 value_4E2;          // 4E2
    uint8 value_4E3;          // 4E3
    sint16 value_4E4;         // 4E4
    sint16 value_4E6;         // 4E6
    uint8 reserved4E8[0x2];   // 4E8
    sint16 value_4EA;         // 4EA
    uint8 reserved4EC[0xB8];  // 4EC
};

// The block at +0x4E0 of ST1B_TALKER.
typedef struct
{
    uint16 flags_0;  // 00
    uint8 anim_2;    // 02: the animation to go back to
    uint8 routine_3; // 03
    sint16 angle_4;  // 04: the rotation.y to turn back to
    sint16 turn_6;   // 06: turn speed
} ST1B_TALK;

// A 0x5A4-byte work slot of a villager who talks, with its talk block at +0x4E0.
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
    uint8 value_C;                          // 0C
    uint8 reserved0D[7];                    // 0D
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x43];                 // 64
    sint8 value_A7;                         // A7: negative at the end of the animation
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[0x432];                // AE
    ST1B_TALK talk;                         // 4E0
    uint8 reserved4E8[0xBC];                // 4E8
} ST1B_TALKER;

typedef void (*ST1B_TALKER_FUNC)(ST1B_TALKER *wp);

extern STAGE_ROOM2_FUNC D_8010C574[];
extern STAGE_SLOT_FUNC *D_8010C608[];
extern STAGE_SLOT_FUNC *D_8010C79C[];
extern STAGE_SLOT_FUNC D_8010C7B8[];
extern STAGE_SLOT_FUNC D_8010C80C[];
extern STAGE_SLOT_FUNC D_8010C810[];
extern STAGE_SLOT_FUNC D_8010C884[];
extern uint8 D_8010DAA0[];
extern uint8 D_8010DAA8[][8];
extern uint8 D_8010D938[];
extern STAGE_OBJ_FUNC D_8010E6F8[];
extern STAGE_OBJ_FUNC D_8010E71C[];
extern STAGE_OBJ_FUNC D_8010E794[];
extern STAGE_ACTOR_FUNC D_8010E7B0[];
extern STCOM_FIXED_VECTOR D_80113E74;
extern STAGE_MOUTH *D_80113E94[];
extern sint16 D_80113E98[];
extern STAGE_MOUTH *D_80113E9C[];
extern sint16 D_80113EA0[];
extern STAGE_LIP_CUES D_80113EA4;
extern STAGE_MOUTH *D_8010E864[];
extern STAGE_MOUTH *D_8010E870[];
extern STAGE_FUNC D_8010E8E0[];
extern STAGE_OBJ_FUNC D_8010E910[];
extern STAGE_MOUTH *D_80113EAC[];
extern sint16 D_80113EB0[];
extern STAGE_MOUTH *D_80113EB4[];
extern sint16 D_80113EB8[];
// The lip-sync script pointers also read and written as scalars (the same symbols).
extern STAGE_MOUTH *D_80113E94_S __asm__("D_80113E94");
extern STAGE_MOUTH *D_80113E9C_S __asm__("D_80113E9C");
extern STAGE_MOUTH *D_80113EAC_S __asm__("D_80113EAC");
extern STAGE_MOUTH *D_80113EB4_S __asm__("D_80113EB4");
extern STAGE_LIP_CUES D_80113EBC;
extern STAGE_MOUTH *D_8010E990[];
extern STAGE_MOUTH *D_8010E9A0[];
extern STAGE_FUNC D_8010EA40[];
extern uint8 D_8010D928[];
extern uint8 D_8010D8C8[];
extern uint8 D_8010D8E8[];
extern uint8 D_8010D908[];
extern uint8 D_8010D8D0[];
extern uint8 D_8010D8F0[];
extern uint8 D_8010D910[];
extern uint8 D_8010D8D8[];
extern uint8 D_8010D8F8[];
extern uint8 D_8010D918[];
extern uint8 D_8010DB10[];
extern STAGE_SCRIPT_ENTRY D_8010DCF0[];
extern STAGE_ROOM_FUNC D_8010DD68[];
extern uint8 D_8010E91C[];
extern uint8 D_8010D948;
extern uint8 D_8010D920;
extern STAGE_OBJ_FUNC D_8010E8FC[];
extern ST1B_TALKER_FUNC D_8010E92C[];
extern void *D_8010C8C4[];
extern void *D_8010CB18[];
extern void *D_8010CD7C[];
extern uint8 D_8010CDA0[][0x28];
extern uint8 D_8010CF08[][8];
extern sint32 D_8010D108[];
extern STAGE_ROOM_FUNC *D_8010D204[];
extern uint8 D_8010D940[];
extern STAGE_ROOM_FUNC D_8010D950[];
extern STAGE_SCRIPT_ENTRY D_8010D974[];
extern uint8 D_8010D988[];
extern uint8 D_8010DA8C[];
extern uint8 D_8010DB08[];
extern uint8 D_8010DB0C[];
extern uint8 D_8010DDC8[];
extern STAGE_SCRIPT_ENTRY D_8010DEB0[];
extern uint8 D_8010DF28[];
extern ST1B_BASE_FUNC D_8010E6EC[];
extern uint8 D_8010E724[][0x20];
extern uint8 D_8010E764[];
extern ST1B_VIEW_FUNC D_8010E768[];
extern STAGE_SLOT_FUNC D_8010E788[];
extern uint8 D_8010E7B4[];
extern STAGE_MOUTH_CUE D_8010E87C[];
extern STAGE_MOUTH_CUE D_8010E89C[];
extern STAGE_MOUTH_CUE D_8010E8C0[];
extern STAGE_MOUTH_CUE D_8010E8CC[];
extern uint8 D_8010E8F0[];
extern ST1B_TALKER_FUNC D_8010E908[];
extern STAGE_MOUTH_CUE D_8010E9B0[];
extern STAGE_MOUTH_CUE D_8010E9D0[];
extern STAGE_MOUTH_CUE D_8010EA14[];
extern STAGE_MOUTH_CUE D_8010EA28[];
extern sint32 D_80113E5C[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_8010076C(STAGE_ROOM *wp);
void func_801007A8(void);
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void func_80100A20(void);
void func_8001DF10(uint8 *);
void func_80100B30(STAGE_ROOM *wp);
void func_801050E8(STAGE_OBJ *wp);
void func_80105290(STAGE_OBJ *wp);
void func_80105108(STAGE_WORK *wp);
void func_8010617C(STAGE_OBJ *wp);
void func_8010603C(STAGE_WORK *wp);
void func_80106284(STAGE_OBJ *wp);
void func_801062D0(STAGE_OBJ *wp);
void func_80106228(STAGE_OBJ *wp);
void func_801064E4(ST1B_VIEW *wp);
void func_80106A34(STAGE_OBJ *wp);
void func_80106AFC(STAGE_OBJ *wp);
void func_80106B48(STAGE_OBJ *wp);
void func_80106D54(STAGE_OBJ *wp);
void func_80106A54(STAGE_OBJ *wp);
void func_80106E14(STAGE_ACTOR *wp);
sint32 func_80107114(ST1B_ACTOR *wp);
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_801087C4(STAGE_WORK *wp);
void func_80108820(STAGE_WORK *wp);
void func_8010887C(STAGE_OBJ *wp);
void func_801089A4(STAGE_OBJ *wp);
void func_80108C80(STAGE_OBJ *wp);
void func_80108CCC(STAGE_WORK *wp);
void func_80108AEC(STAGE_OBJ *wp);
void func_80109028(STAGE_OBJ *wp);
void func_80109048(STAGE_OBJ *wp);
void func_80109420(STAGE_WORK *wp);
void func_8010947C(STAGE_WORK *wp);
void func_801094D8(STAGE_OBJ *wp);
void func_80109600(STAGE_OBJ *wp);
void func_80109B14(STAGE_WORK *wp);
void func_80109748(STAGE_OBJ *wp);
void func_80100EE8(STAGE_ROOM *wp);
void func_80100F3C(STAGE_ROOM *wp);
void func_80100F88(STAGE_ROOM *wp);
void func_80100FD4(STAGE_ROOM *wp);
void func_80101020(STAGE_ROOM *wp);
void func_8010106C(STAGE_ROOM *wp);
void func_801010B8(STAGE_ROOM *wp);
void func_80101104(STAGE_ROOM *wp);
void func_80101120(STAGE_ROOM *wp);
void func_8010116C(STAGE_ROOM *wp);
void func_801011B8(STAGE_ROOM *wp);
void func_80101204(STAGE_ROOM *wp);
sint32 func_8010155C(void);
void func_80101C00(STAGE_ROOM_WORK *wp);
void func_801090D0(STAGE_OBJ *wp);
void func_8010218C(STAGE_ROOM *wp);
void func_801017B0(STAGE_ROOM *wp);
void func_801018E8(STAGE_ROOM *wp);
void func_80101AF8(STAGE_ROOM *wp);
void func_801018AC(STAGE_ROOM *wp);
void func_80100724(sint8 *arg0);
void func_80102148(STAGE_ROOM *wp);
void func_80106400(STAGE_OBJ *wp);
void func_80106498(STAGE_OBJ *wp);
void func_80109084(STAGE_OBJ *wp);
sint32 func_80101340(STAGE_OBJ *wp);
sint32 func_801013A0(STAGE_OBJ *wp);
void func_80101920(STAGE_ROOM *wp);
void func_80109844(STAGE_OBJ *wp);
void func_80100CFC(STAGE_OBJ *wp);
void func_8010157C(void);
sint32 func_801014E4(STAGE_OBJ *wp);
void func_80100C68(STAGE_OBJ *wp);
void func_80101A1C(STAGE_ROOM *wp);
void func_80100E64(STAGE_OBJ *wp);
void func_801060F8(STAGE_OBJ *wp);
void func_80101724(STAGE_ROOM *wp);
void func_80104FE4(STAGE_OBJ *wp, uint16 *arg1);
void func_80101984(STAGE_ROOM *wp);
void func_80108D94(STAGE_OBJ *wp);
void func_801051F4(STAGE_OBJ *wp);
void func_8010208C(STAGE_ROOM *wp);
void func_80101EFC(STAGE_ROOM *wp);
void func_801017E8(STAGE_ROOM *wp);
void func_80101B30(STAGE_ROOM *wp);
void func_80101FBC(STAGE_ROOM *wp);
void func_8010706C(ST1B_VIEW *wp);
void func_80108E2C(ST1B_VIEW *wp);
void func_8001EB98(uint8 *);
sint32 func_80101250(ST1B_VIEW *wp);
void func_80106604(ST1B_VIEW *wp);

// ROCK_NEO.EXE's camera work (scene.h): its position (16.16) and the value at +0x30.
extern sint32 D_800BC740;
extern sint32 D_800BC744;
extern sint32 D_800BC748;
extern sint32 D_800BC770;
extern sint32 D_800BC774;
extern sint32 D_800BC778;

extern ST1B_CAM Sce_camera_work;
extern ST1B_CAMERA D_800C3558;

#endif
