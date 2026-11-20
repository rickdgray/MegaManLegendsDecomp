#ifndef ST10_H
#define ST10_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"

// From r3_st04 (ST04_ACTOR_CTL).
// A 0x20-byte control block of ST10_ACTOR (at +0x348 and +0x368).
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
} ST10_ACTOR_CTL;

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
    uint8 reserved188[0x1C0];               // 188
    ST10_ACTOR_CTL ctl;                     // 348
    ST10_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST10_ACTOR;

// A 0x10C-byte slot (Open_SHL_WORK) of a turning model with a hit box (D_801148CC).
typedef struct ST10_PROP ST10_PROP;
typedef void (*ST10_PROP_FUNC)(ST10_PROP *wp);

struct ST10_PROP
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
    uint8 reserved0D[7];                    // 0D
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[0x12];                 // 66
    sint32 value_78;                        // 78
    uint8 reserved7C[0x10];                 // 7C
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR position_AC;              // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    uint32 hit_BC;                          // BC
    uint8 reservedC0[0x4C];                 // C0
};

// From r3_st0c (ST0C_PL).
// Player_work as the stage's player routines take it: +0xC is their routine (a signed byte), and
// +0x428/+0x438 a second position in 16.16 and in halfwords.
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01[0xB];             // 01
    sint8 routine_C;                   // 0C
    sint8 routine_D;                   // 0D
    uint8 reserved0E[6];               // 0E
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x158];           // 2C
    void *target_184;                  // 184
    uint8 reserved188[0x2A0];          // 188
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    STCOM_SVECTOR rot_440;             // 440
    uint8 value_448;                   // 448
} ST10_PL;

// A 0x18-byte spawn record, copied whole (func_80100354).
typedef struct
{
    uint8 bytes[0x18];
} ST10_SPAWN;

// The work slot Scene_work keeps at +0x24.
#define ST10_SCENE_OBJ_24 (*(STAGE_OBJ **)((uint8 *)&Scene_work + 0x24))

// From r3_st0c (ST0C_PL_FUNC).
typedef void (*ST10_PL_FUNC)(ST10_PL *wp);

// A view of the work slots r3_st10's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST10_VIEW ST10_VIEW;

typedef void (*ST10_VIEW_FUNC)(ST10_VIEW *wp);
struct ST10_VIEW
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
    sint16 value_4E;                        // 4E
    sint16 value_50;                        // 50
    uint8 reserved52[0x2];                  // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    uint16 value_66;                        // 66
    uint8 reserved68[0x6];                  // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[0x8];                  // 70
    sint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x26];                 // 7E
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_A4;                 // A4
    uint8 reservedA8[0x4];  // A8
    STCOM_SVECTOR vec_AC;   // AC
    sint32 value_B4;        // B4
    uint8 reservedB8[0x4];  // B8
    sint32 value_BC;        // BC
    uint8 reservedC0[0x4];  // C0
    sint32 value_C4;        // C4
    sint32 value_C8;        // C8
    uint8 reservedCC[0x8C]; // CC
    sint32 value_158;       // 158
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
    uint16 value_34C;         // 34C
    uint8 reserved34E[0xDA];  // 34E
    sint32 value_428;         // 428
    sint32 value_42C;         // 42C
    sint32 value_430;         // 430
    uint8 reserved434[0x4];   // 434
    sint16 value_438;         // 438
    sint16 value_43A;         // 43A
    sint16 value_43C;         // 43C
    uint8 reserved43E[0x2];   // 43E
    sint16 value_440;         // 440
    sint16 value_442;         // 442
    sint16 value_444;         // 444
    uint8 reserved446[0x2];   // 446
    uint8 value_448;          // 448
    uint8 reserved449[0x15B]; // 449
};

// From r3_st0a (ST0A_SHOT_FIXED).
// A 16.16 position whose halfword view reads the integer parts (shl/shl.h's SHL_FIXED).
typedef union
{
    STCOM_FIXED_VECTOR w;
    struct
    {
        uint16 x_lo;
        sint16 x;
        uint16 y_lo;
        sint16 y;
        uint16 z_lo;
        sint16 z;
        uint16 pad_lo;
        sint16 pad;
    } h;
} ST10_SHOT_FIXED;

// From r3_st0a (ST0A_SHOT).
// A 0x10C-byte shot (shl/shl.h's SHL_WORK with a model: the fields its routines use).
typedef struct
{
    uint8 flags_0;              // 00
    uint8 value_1;              // 01
    uint8 value_2;              // 02
    uint8 type_3;               // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];        // 04
    uint8 flags_6;              // 06
    uint8 reserved07;           // 07
    uint8 routine_0;            // 08
    uint8 routine_1;            // 09
    uint8 mode_A;               // 0A
    uint8 timer_B;              // 0B
    sint8 index_C;              // 0C
    sint8 bit_D;                // 0D
    sint8 value_E;              // 0E
    sint8 value_F;              // 0F
    uint8 reserved10[4];        // 10
    STCOM_SVECTOR pos;          // 14
    ST10_SHOT_FIXED fpos;       // 1C
    STCOM_SVECTOR old_pos;      // 2C
    ST10_SHOT_FIXED old_fpos;   // 34
    STCOM_SVECTOR vel;          // 44
    uint8 reserved4C[8];        // 4C
    STCOM_SVECTOR rot;          // 54
    uint8 reserved5C[8];        // 5C
    sint16 rot_y;               // 64
    sint16 rot_x;               // 66
    uint8 reserved68[0x14];     // 68
    sint16 hit_7C;              // 7C
    uint8 reserved7E[0x2E];     // 7E
    STCOM_SVECTOR model_pos_AC; // AC
    uint8 reservedB4[0x10];     // B4
    uint32 col_C4;              // C4: hit accumulator (func_8003430C, func_800341BC)
    uint8 reservedC8[0x44];     // C8
} ST10_SHOT;

// From r3_st0a (ST0A_SHOT_FX).
// An effect slot as the shot's sparks use it (shl/shl.h's SHL_FX).
typedef struct
{
    sint8 routine_0;        // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 flag_3;           // 03
    uint8 reserved04[0x18]; // 04
    sint16 x_1C;            // 1C
    sint16 y_1E;            // 1E
    sint16 z_20;            // 20
    uint8 reserved22[0xE];  // 22
    sint16 vx_30;           // 30
    sint16 vy_32;           // 32
    sint16 vz_34;           // 34
    uint8 reserved36[0xA];  // 36
    uint32 value_40;        // 40
    uint8 reserved44[4];    // 44
} ST10_SHOT_FX;

typedef void (*ST10_ACTOR_FUNC)(ST10_ACTOR *wp);
// Scene_work's byte at +4.
#define ST10_SCENE_BYTE_4 (*((uint8 *)&Scene_work + 4))

// A copy of the special-weapon shot from r3_shl02 (its SHL_WORK) at 0x80112874: an object slot
// with ROCK_NEO's generic layout up to 0x88, then a model's draw data.
typedef struct
{
    sint8 flags_0; // 00
    uint8 value_1; // 01
    uint8 kind_2;  // 02
    uint8 type_3;  // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];
    uint8 flags_6; // 06
    uint8 reserved07;
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 mode_a;    // 0A
    uint8 timer_b;   // 0B
    sint8 index_c;   // 0C
    sint8 bit_d;     // 0D
    uint8 reserved0e[6];
    STCOM_SVECTOR pos;           // 14
    STAGE_FIXED_VECTOR fpos;     // 1C
    STCOM_SVECTOR old_pos;       // 2C
    STAGE_FIXED_VECTOR old_fpos; // 34
    STCOM_SVECTOR vel;           // 44
    sint16 ax, ay, az;           // 4C
    uint8 reserved52[0x12];
    sint16 rot_y; // 64
    sint16 rot_x; // 66
    uint8 reserved68[0x10];
    sint16 *box_78; // 78
    sint16 hit_7c;  // 7C
    uint8 reserved7e[0xE];
    STCOM_MATRIX mtx_8c; // 8C
    STCOM_SVECTOR mpos;  // AC: the model's position
    uint32 color_b4;     // B4
    uint8 reservedb8[0xC];
    uint32 col_c4; // C4: hit accumulator (func_8003430C)
    uint32 col_c8; // C8
} ST10_SHL;

// Player_work's signed bytes past STCOM_PL_WORK's fields.
#define ST10_PL_SBYTE(offset) (*((sint8 *)&Player_work + (offset)))

extern STAGE_SLOT_FUNC *D_8010F048[];
extern STAGE_SLOT_FUNC *D_8010F1D4[];
extern STAGE_SLOT_FUNC D_8010F1F0[];
extern STAGE_SLOT_FUNC D_8010F2AC[];
extern STAGE_SLOT_FUNC D_8010F2EC[];
extern STAGE_SLOT_FUNC D_8010F2F0[];
extern STAGE_ROOM_FUNC D_8010FA44[];
extern STAGE_ROOM_FUNC *D_8010FA04[];
extern uint8 D_8011005C[];
extern uint8 D_80110084[];
extern uint8 D_80110054[];
extern STAGE_OBJ_FUNC D_8011465C[];
extern uint8 D_80110074[];
extern uint8 D_8011007C[];
extern STAGE_ROOM2_FUNC D_80110138[];
extern STAGE_OBJ_FUNC D_801148E0[];
extern uint8 D_80110094[];
extern uint8 D_8011009C[][8];
extern STAGE_SCRIPT_ENTRY D_801149C0[];
extern STAGE_SCRIPT_ENTRY D_801100FC[];
extern ST10_PROP_FUNC D_801148CC[];
extern uint8 D_8011004C[];
extern uint8 D_801101B4[];
extern uint8 D_80110174[];
extern STAGE_SCRIPT_ENTRY D_801101A0[];
extern STAGE_ROOM2_FUNC D_801101C8[];
extern ST10_PL_FUNC D_801101E0[];
extern void *D_8010F394[];
extern void *D_8010F58C[];
extern ST10_SPAWN D_8010F5D4;
extern ST10_SPAWN D_8010F5EC;
extern ST10_SPAWN D_8010F604;
extern void *D_8010F754[];
extern uint8 D_8010F76C[][0x28];
extern uint8 D_8010F85C[][8];
extern sint32 D_8010F8F4[];
extern STCOM_SVECTOR D_8010F90C;
extern STAGE_ROOM2_FUNC D_8011013C[];
extern uint8 D_8011014C[];
extern STAGE_SLOT_FUNC D_80114668[];
extern uint8 D_80114670[];
extern uint8 D_801148D4[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_801006FC(void);
void func_8001DF10(uint8 *);
void func_80100840(STAGE_ROOM *wp);
void func_80100894(STAGE_ROOM *wp);
void func_801008E8(STAGE_ROOM *wp);
void func_80104D48(STAGE_OBJ *wp);
void func_80105068(STAGE_OBJ *wp);
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_80100A28(STAGE_ROOM *wp);
void func_80100A44(STAGE_ROOM *wp);
void func_80100A90(STAGE_ROOM *wp);
sint32 func_80100B94(void);
sint32 func_80100BB4(void);
void func_80100BD4(STAGE_ROOM *wp);
void func_80100E38(void);
void func_8010AF4C(STAGE_OBJ *wp);
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void func_8001EB98(void *entry);
void func_8010B660(ST10_SHOT *wp, sint32 arg);
sint32 func_800375D4(void *pl, sint32 arg);
void func_8010B51C(ST10_SHOT *wp);
void func_800354E0(sint32 bit);
sint16 func_80039B80(void);
sint32 func_80037634(void *player, sint32 arg);
void func_8010AF9C(ST10_SHL *wp);

#endif
