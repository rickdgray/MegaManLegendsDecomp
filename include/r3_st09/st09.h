#ifndef ST09_H
#define ST09_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/gte.h"

// From stcom13 (STCOM13_CTL, STCOM13_WORK, STCOM13_FUNC): func_80107CDC is its copy.
// The block at +0x348 of the work slot.
// A room area in world units: corner x, z and its width and depth, tested with unsigned
// differences (func_801106F0). As a struct its loads keep source order.
typedef struct
{
    sint16 x;
    sint16 z;
    sint16 w;
    sint16 d;
} ST09_AREA;

typedef struct
{
    uint16 flags_0;        // 348
    uint16 rand_2;         // 34A: a new random number every frame
    sint16 timer_4;        // 34C
    uint8 reserved06[2];   // 34E
    sint16 value_8;        // 350
    sint16 damage_A;       // 352: damage taken while stunned
    STCOM_SVECTOR pos_C;   // 354: the hit box's center
    uint32 hit_14;         // 35C: damage in the low 24 bits, kind bits above
    uint32 value_18;       // 360
    STCOM_SVECTOR from_1C; // 364: where the hit came from
    uint8 track_24[0x10];  // 36C
    sint16 count_34;       // 37C: drops so far (stcom13_func_08B0)
    uint16 timer_36;       // 37E: frames before it may vanish off screen
} ST09_STCOM13_CTL;

// The 0x3C0-byte work slot stcom13 runs on (freed through ROCK_NEO's func_80031824): an enemy
// that can be stunned and knocked about, dropping effects from its joints.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03
    uint8 reserved04[2];                    // 04
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 reserved0C[4];                    // 0C
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[2];                    // 4C
    sint16 gravity_4E;                      // 4E
    uint8 reserved50[4];                    // 50
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 turn_66;                         // 66: turn speed (stcom13_func_0C24)
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: screen depth?
    uint8 reserved84[0x20];                 // 84
    uint8 value_A4;                         // A4
    uint8 reservedA5[7];                    // A5
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0x5C];                 // B4
    uint8 value_110;                        // 110
    uint8 reserved111[0x47];                // 111
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x39];         // 180: joint positions
    ST09_STCOM13_CTL ctl;                   // 348
    uint8 reserved380[0x40];                // 380
} ST09_STCOM13_WORK;

typedef void (*ST09_STCOM13_FUNC)(ST09_STCOM13_WORK *wp);

// From r3_st00 (ST00_PAIR_OBJ).
// A 0x5A4-byte slot holding two other slots at +0x514 and +0x518 (func_801103D0).
typedef struct
{
    uint8 reserved000[0x514]; // 000
    void *child_514;          // 514
    void *child_518;          // 518
} ST09_PAIR_OBJ;

// The boss a part follows (func_80036294 of the part's parent_C): its joints' positions and
// matrices.
typedef struct
{
    uint8 reserved00[0x54];      // 00
    STCOM_SVECTOR rotation;      // 54
    uint8 reserved5C[0x124];     // 5C
    STCOM_SVECTOR joint_180[24]; // 180
    STAGE_MATRIX joint_240[1];   // 240: by joint
} ST09_BOSS;

// The block a boss part keeps at +0xBC.
typedef struct
{
    uint16 flags_0;              // BC: 1 resets the routine, 2 hittable, 8 registers its hit box,
                                 // 0x10 follows its joint, 0x40 keeps it on the ground
    uint16 random_2;             // BE: rand()
    uint16 timer_4;              // C0
    uint16 count_6;              // C2: frames, for every other one (func_80115014)
    uint8 value_8;               // C4: hit flags
    uint8 reserved9;             // C5
    sint16 timer_A;              // C6
    STCOM_SVECTOR pos_C;         // C8: its hit box
    uint32 hit_14;               // D0: damage (low 24 bits) and kind bits
    uint8 reserved18[0xC];       // D4
    uint8 track_24[0x10];        // E0 (Track_stop)
    ST09_BOSS *parent_34;        // F0
    STCOM_FIXED_VECTOR scale_38; // F4
    uint8 reserved48[8];         // 104
} ST09_PART_CTL;

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
    ST09_PART_CTL ctl;                      // BC
} ST09_PART;

typedef void (*ST09_PART_FUNC)(ST09_PART *wp);

// From r3_st03 (STCOM36_OBJ).
// A work slot as stcom36 sees it.
typedef struct ST09_STCOM36_OBJ ST09_STCOM36_OBJ;

// From r3_st03 (STCOM36_OBJ_FUNC).
typedef void (*ST09_STCOM36_OBJ_FUNC)(ST09_STCOM36_OBJ *wp);

// From r3_st03 (STCOM36_OBJ).
struct ST09_STCOM36_OBJ
{
    uint8 flags_0;          // 00
    uint8 index_1;          // 01: pool id and slot
    uint8 kind_2;           // 02: first index into the pool's handler table
    uint8 value_3;          // 03
    uint8 handler_4;        // 04: second index (two-level tables)
    uint8 value_5;          // 05
    uint8 flags_6;          // 06: 0x20 cleared once the room's script has it
    uint8 reserved07;       // 07
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 reserved0C[8];    // 0C
    STCOM_SVECTOR position; // 14
};

// From r3_st03 (STCOM36_TABLE_3C0).
// The pools' handler tables (scratchpad).
#define ST09_STCOM36_TABLE_3C0 (*(ST09_STCOM36_OBJ_FUNC ***)0x1F800058)

// From r3_st03 (STCOM36_TABLE_10C).
#define ST09_STCOM36_TABLE_10C (*(ST09_STCOM36_OBJ_FUNC **)0x1F800060)

// A view of the work slots r3_st09's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST09_VIEW ST09_VIEW;

typedef void (*ST09_VIEW_FUNC)(ST09_VIEW *wp);
struct ST09_VIEW
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
        uint16 h[2];
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
    } u_48;                      // 48
    uint16 value_4C;             // 4C
    uint16 value_4E;             // 4E
    uint8 reserved50[0x4];       // 50
    STCOM_SVECTOR rotation;      // 54
    STCOM_SVECTOR rotation_prev; // 5C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_64;                // 64
    uint8 reserved68[0x6]; // 68
    sint16 value_6E;       // 6E
    sint32 value_70;       // 70
    sint32 value_74;       // 74
    uint8 *data_78;        // 78
    uint8 reserved7C[0x4]; // 7C
    sint32 value_80;       // 80
    uint8 reserved84[0x4]; // 84
    sint32 value_88;       // 88
    sint32 value_8C;       // 8C
    sint32 value_90;       // 90
    sint32 value_94;       // 94
    sint32 value_98;       // 98
    sint32 value_9C;       // 9C
    sint32 value_A0;       // A0
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_A4;                // A4
    sint32 value_A8;       // A8
    uint8 value_AC;        // AC
    uint8 value_AD;        // AD
    uint8 reservedAE[0x2]; // AE
    sint16 value_B0;       // B0
    sint16 value_B2;       // B2
    sint32 value_B4;       // B4
    uint8 reservedB8[0x4]; // B8
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_BC; // BC
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_C0; // C0
    union
    {
        uint8 b[4];
        sint32 w[1];
    } u_C4;                // C4
    uint8 reservedC8[0x4]; // C8
    sint16 value_CC;       // CC
    sint16 value_CE;       // CE
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_D0;                 // D0
    sint16 value_D4;        // D4
    sint16 value_D6;        // D6
    sint16 value_D8;        // D8
    uint16 value_DA;        // DA
    uint8 reservedDC[0x14]; // DC
    sint32 value_F0;        // F0
    sint32 value_F4;        // F4
    union
    {
        uint8 b[4];
        sint8 s[4];
        sint32 w[1];
    } u_F8;                  // F8
    sint32 value_FC;         // FC
    uint8 reserved100[0x7];  // 100
    uint8 value_107;         // 107
    uint8 value_108;         // 108
    uint8 reserved109[0x4F]; // 109
    sint32 value_158;        // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    uint8 reserved160[0x20];  // 160
    STCOM_SVECTOR vec_180;    // 180
    STCOM_SVECTOR vec_188;    // 188
    STCOM_SVECTOR vec_190;    // 190
    uint8 reserved198[0x190]; // 198
    STAGE_ACTOR_EXT ext;      // 328
    uint8 reserved3C0[0x120]; // 3C0
    uint16 value_4E0;         // 4E0
    sint16 value_4E2;         // 4E2
    sint16 value_4E4;         // 4E4
    uint16 value_4E6;         // 4E6
    sint16 value_4E8;         // 4E8
    uint8 reserved4EA[0xA];   // 4EA
    sint32 value_4F4;         // 4F4
    uint8 reserved4F8[0x1C];  // 4F8
    sint32 value_514;         // 514
    uint8 reserved518[0x6];   // 518
    sint16 value_51E;         // 51E
    sint32 value_520;         // 520
    uint8 reserved524[0x80];  // 524
};

// A leg of a walking route (func_80110CA0): the turn while it waits, then the area that ends it.
typedef struct
{
    sint16 turn_0;
    uint8 reserved2[2];
    sint16 x_4;
    sint16 z_6;
    sint16 w_8;
    sint16 d_A;
} ST09_ROUTE;

// stcom15's control block as the walking object uses it (func_80110CA0): its route at +0x3E.
typedef struct
{
    uint8 reserved00[0x3E];
    sint16 step_3E;
    ST09_ROUTE *route_40;
} ST09_ROUTE_CTL;

// From r3_st1d (ST1D_VIEW).
typedef struct ST09_VIEW_B ST09_VIEW_B;

typedef void (*ST09_VIEW_B_FUNC)(ST09_VIEW_B *wp);
struct ST09_VIEW_B
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

// An object func_80107334 spawns: copied into a new 0x3C0 slot (D_8011C9A0, by the spawner's
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
} ST09_SPAWN_REC;

extern STAGE_SLOT_FUNC *D_8011CCBC[];
extern STAGE_SLOT_FUNC *D_8011CDCC[];
extern STAGE_SLOT_FUNC D_8011CDD8[];
extern STAGE_SLOT_FUNC D_8011CE28[];
extern STAGE_SLOT_FUNC D_8011CE68[];
extern STAGE_SLOT_FUNC D_8011CEF0[];
extern STAGE_ROOM2_FUNC *D_8011DD20[];
extern STAGE_ROOM2_FUNC D_8011DD64[];
extern STAGE_OBJ_FUNC D_8011E3AC[];
extern STAGE_OBJ_FUNC D_8011E3BC[];
extern STAGE_FX_FUNC D_8011E4D8[];
extern ST09_PART_FUNC D_8011E2D8[];
extern ST09_PART_FUNC D_8011E2E4[];
extern ST09_STCOM13_FUNC D_8011DF34[]; // routine_0 handlers (func_80107CDC)
extern uint32 D_8011DD60;              // the objects still to be ended, one bit per slot
extern ST09_STCOM36_OBJ *D_8011EA60[]; // the spawned objects, by slot
extern sint32 D_8011BBB4[];
extern ST09_SPAWN_REC D_8011C9A0[];
extern void *D_8011D488[];
extern uint8 D_8011D4B2;
extern uint8 D_8011D542;
extern uint8 D_8011D67B;
extern void *D_8011DAAC[];
extern uint8 D_8011DAD0[][0x28];
extern uint8 D_8011DC38[][8];
extern sint32 D_8011DC90[];
extern STAGE_ROOM_FUNC D_8011DD7C[];
extern uint8 D_8011DD8C[];
extern STAGE_SLOT_FUNC D_8011DDD4[];
extern STAGE_SLOT_FUNC D_8011DDE8[];
extern uint8 D_8011DE20[];
extern sint16 D_8011DE2C[];
extern uint8 D_8011DE30[];
extern STCOM_SVECTOR D_8011DE34;
extern STAGE_SLOT_FUNC D_8011DEB0[];
extern STAGE_SLOT_FUNC D_8011DEBC[];
extern uint8 D_8011DEE4[];
extern sint16 D_8011DEF0[];
extern sint8 D_8011DEF8[];
extern sint16 D_8011DEFC[];
extern sint8 D_8011DF04[];
extern uint8 D_8011DF08[4];
extern ST09_VIEW_B_FUNC D_8011DF0C[];
extern STAGE_SLOT_FUNC D_8011DF18[];
extern uint8 D_8011DF24[];
extern sint16 D_8011DF30[];
extern sint16 D_8011DF68[];
extern sint16 D_8011DF6C[];
extern STAGE_STCOM15_FUNC_348 D_8011DF88[];
extern uint8 D_8011DFAC[];
extern uint8 D_8011DFB8[4];
extern STAGE_STCOM15_FUNC_4E0 D_8011E154[];
extern STAGE_STCOM15_FUNC_4E0 D_8011E168[];
extern uint8 D_8011E1A4[];
extern ST09_AREA D_8011E1B4;
extern ST09_AREA D_8011E1C0;
extern ST09_ROUTE D_8011E1C8[];
extern uint16 D_8011E1CC;
extern uint16 D_8011E1CE;
extern uint16 D_8011E1D0;
extern uint16 D_8011E1D2;
extern uint16 D_8011E1F0;
extern uint16 D_8011E1F2;
extern uint16 D_8011E1F4;
extern uint16 D_8011E1F6;
extern ST09_ROUTE D_8011E1F8[];
extern ST09_AREA D_8011E22C;
extern uint8 D_8011E238[];
extern sint16 D_8011E23A;
extern sint16 D_8011E23C;
extern sint16 D_8011E23E;
extern uint8 D_8011E244[];
extern sint16 D_8011E246;
extern sint16 D_8011E248;
extern sint16 D_8011E24A;
extern sint16 D_8011E24C[]; // the three dust puffs' offsets (func_801109A4)
extern sint16 D_8011E254[]; // the three dust puffs' offsets (func_80110CA0)
extern uint16 D_8011E25C[];
extern sint16 D_8011E268[]; // the three dust puffs' offsets (func_80111B08)
extern sint16 D_8011E270[]; // the three dust puffs' offsets (func_80111DC0)
extern STCOM_SVECTOR D_8011E2F8[];
extern STCOM_SVECTOR D_8011E3C8[3];
extern uint8 D_8011E4B0[];
extern STAGE_SLOT_FUNC D_8011E4C0[];
extern STAGE_SLOT_FUNC D_8011E4E4[];
extern sint32 D_8011E4EC[];
extern sint32 D_8011E4F4[];
extern STCOM_FIXED_VECTOR D_8011E4FC[];
extern sint32 D_8011E500;
extern sint32 D_8011E504;
extern STAGE_PANEL_ROOM D_8011E55C[];
extern STAGE_PANEL_OFFSET D_8011E5AC[][2]; // by direction and variant
extern STAGE_SLOT_FUNC D_8011E5CC[];
extern STCOM_SVECTOR D_8011E930[1];
extern STCOM_FIXED_VECTOR D_8011E938;
extern uint8 D_8011E948[];
extern uint8 D_8011E949[];
extern STCOM_SVECTOR D_8011E950[1];
extern STCOM_FIXED_VECTOR D_8011E958[1];
extern STCOM_SVECTOR D_8011E968[];
extern STCOM_FIXED_VECTOR D_8011E970[];
extern STCOM_SVECTOR D_8011E988[];
extern STCOM_FIXED_VECTOR D_8011E990[];
extern STCOM_SVECTOR D_8011E9A0;
extern STCOM_FIXED_VECTOR D_8011E9A8;
extern STCOM_FIXED_VECTOR D_8011E9B8[];
extern sint32 D_8011E9BC;
extern sint32 D_8011E9C0;
extern uint16 D_8015C004[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_8010071C(void);
void func_8010074C(STAGE_ROOM *wp);
void func_80100AF8(void);
void func_801149F0(STAGE_OBJ *wp);
void func_80115BD0(STAGE_OBJ *wp);
void func_801170B0(STAGE_OBJ *wp);
void func_8011720C(STAGE_OBJ *wp);
void func_80118B30(STAGE_FX *wp);
void func_80118D98(STAGE_OBJ *wp);
void func_80105D20(STAGE_OBJ *wp);
void func_80108098(STAGE_OBJ *wp);
void func_80108C70(STAGE_OBJ *wp);
void func_8003187C(void *wp);
void func_801143B4(ST09_PART *wp);
void func_80114400(ST09_PART *wp);
void func_801144E8(ST09_PART *wp);
void func_80114A18(ST09_PART *wp);
void func_80114D5C(ST09_PART *wp);
void func_80114EE0(ST09_PART *wp);
void func_80115014(ST09_PART *wp);
sint32 func_801157F0(ST09_PART *wp);
void Track_stop(void *track);
void func_80101740(ST09_VIEW *wp);
void func_80107828(ST09_VIEW *wp);
void func_8010779C(ST09_VIEW *wp);
sint32 func_80107C28(ST09_VIEW *wp);
void func_801076FC(ST09_VIEW *wp);
// func_800317AC is declared in stage_common/stage.h.
void func_8011A440(STAGE_EV *wp);
void func_80101E84(ST09_VIEW *wp);

sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

// A ROCK_NEO record per object kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;        // 08: times 16
    uint8 limit_9;       // 09
    uint8 value_A;       // 0A
    uint8 reserved0B[4]; // 0B
    uint8 value_F;       // 0F
} ST09_KIND;

extern ST09_KIND **D_80098844;
void *func_80036294(sint32 id); // the spawned slot with this id; callers use their own view
void Track_reset(void *track, uint8 arg1, uint32 arg2);
// The scale vector r3_st09's stcom15 enemies keep in their block's +0x34 (ScaleMatrix).
#define ST09_STCOM15_SCALE(ctl) (*(STCOM_FIXED_VECTOR *)&(ctl)->timer_34)
sint16 Obj_ceiling_height_get(void *wp);

sint32 func_801031E8(ST09_VIEW *wp);
void func_80047228(void *wp, STCOM_SVECTOR *pos, sint32 arg2);

sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
sint32 func_80103170(ST09_VIEW *wp);

sint32 func_80031E60(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);

sint32 func_800364B0(void *track, void *wp, sint32 angle);

// A model part as func_801170EC reads it from a Stage_hed_model_get record: its colors at +0x24.
typedef struct
{
    uint8 reserved00[0x24]; // 00
    uint32 *color_24;       // 24: four words of two colors each
} ST09_MODEL_PART;

// The model record Stage_hed_model_get returns (key & 0xFFFFFF).
typedef struct
{
    uint8 reserved00[0x18];      // 00
    ST09_MODEL_PART *part_18[2]; // 18
} ST09_MODEL;

// A map-object record (ROCK_NEO's D_8015C000, 12 bytes).
typedef struct
{
    sint16 x;     // 0
    sint16 y;     // 2
    sint16 z;     // 4
    uint16 flags; // 6
    sint32 *data; // 8
} ST09_MAP_OBJ;

// A literal address: with the field at +2, retail's loads expand as lui at / addu at,reg,at.
#define ST09_MAP_OBJS ((ST09_MAP_OBJ *)0x8015C000)

// A 0x24-byte event slot of r3_st09_170B0.c: the glowing panels (func_801170B0) and the three
// lifts (func_8011720C).
typedef struct
{
    uint8 flags_0;       // 00
    uint8 reserved01[3]; // 01
    uint8 value_4;       // 04
    uint8 delay_5[3];    // 05: per lift
    union
    {
        sint8 state[4];  // 08: per lift: 0 rising, 1 sinking
        uint8 routine_0; // 08
        uint32 word;
    } u_8;
    uint16 cell_C[3];    // 0C: per lift, its map object (Map_cell_get)
    uint8 reserved12[2]; // 12
    sint16 value_14[3];  // 14
    uint8 reserved1A[2]; // 1A
    uint32 *color_1C[2]; // 1C
} ST09_EVENT;

extern ST09_MODEL_PART *D_8011E9C8;
extern ST09_MODEL_PART *D_8011E9CC;

void func_801170EC(ST09_EVENT *wp);
void func_80117180(ST09_EVENT *wp);
void func_80117248(ST09_EVENT *wp);
void func_80117300(ST09_EVENT *wp);
void func_80117354(ST09_EVENT *wp);

// What the box keeps in its matrix's translation (as STCOM22_CTL): flags, a random value and
// its hit bits (func_800341BC).
typedef struct
{
    uint16 flags_0; // 2C: 2 hittable, 4 registers its hit box, 8 resets the color
    uint16 value_2; // 2E: rand(); bit 0 picks func_80047228's drop
    uint32 hit_4;   // 30: damage (low 24 bits) and kind bits
    uint32 value_8; // 34
} ST09_BOX_CTL;

typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
    struct
    {
        sint16 m[3][3];
        sint16 pad;
        ST09_BOX_CTL ctl; // 2C
    } f;
} ST09_BOX_MATRIX;

// A breakable box (a 0x50-byte slot, func_80118B30; as stcom22's crate).
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
    ST09_BOX_MATRIX matrix; // 18
    STCOM_SVECTOR pos_38;   // 38: pad holds the scenario flag it sets
    uint32 color_40;        // 40
    sint16 life_44;         // 44
    sint16 flag_46;         // 46
    uint8 reserved48[8];    // 48
} ST09_BOX;

void func_80118B7C(ST09_BOX *wp);
void func_80118C3C(ST09_BOX *wp);
void func_80118DC0(ST09_BOX *wp);
sint32 func_80118FC0(ST09_BOX *wp);

// An object a room's script spawns (a 0x14-byte record, Scene_obj_ent_open; stcom36's STCOM36_SPAWN).
typedef struct
{
    uint8 index_0; // 00: its slot in Scene_work's object table
    uint8 reserved01[0x13];
} ST09_SPAWN;

extern ST09_SPAWN D_8011DD68[];

void func_80100670(STAGE_ROOM *wp);
void func_80100B20(sint8 skip);
void func_80100788(STAGE_ROOM_WORK *wp);
void func_801005F4(void);
void func_80100BF0(void);
void Sce_event_timer_clear(void);
void func_80063BA8(void);
void func_8001B314(void);

// The block a sliding platform keeps at +0xCC.
typedef struct
{
    uint16 value_0;  // CC
    uint16 random_2; // CE: rand()
    sint16 delay_4;  // D0: frames before it starts (param_C)
    sint16 count_6;  // D2: frames per sweep (param_D)
    sint16 wait_8;   // D4: frames it rests at each end (param_E)
    sint16 speed_A;  // D6: param_F; its sign is the direction
    uint16 angle_C;  // D8: its spin
    sint16 rot_E;    // DA: its starting rotation.y
} ST09_SLIDER_CTL;

// A platform that slides back and forth (a 0x10C-byte slot, func_80115898).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 index_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03: low 7 bits: spin speed
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 param_C;                          // 0C
    sint8 param_D;                          // 0D
    sint8 param_E;                          // 0E
    sint8 param_F;                          // 0F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 *data_78;                         // 78
    uint8 reserved7C[0x10];                 // 7C
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR pos_AC;                   // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    uint32 hit_BC;                          // BC
    uint8 reservedC0[0xC];                  // C0
    ST09_SLIDER_CTL ctl;                    // CC
    uint8 reservedDC[0x30];                 // DC
} ST09_SLIDER;

typedef void (*ST09_SLIDER_FUNC)(ST09_SLIDER *wp);

extern ST09_SLIDER_FUNC D_8011E304[];
extern ST09_SLIDER_FUNC D_8011E310[];

void func_80115898(ST09_SLIDER *wp);
void func_801158E4(ST09_SLIDER *wp);
void func_80115A0C(ST09_SLIDER *wp);
void func_80115BF0(ST09_SLIDER *wp);

// A talk area in map cells (position >> 9): corner x, z and its width and depth (func_801080B8).
typedef struct
{
    sint8 x;
    sint8 z;
    uint8 w;
    uint8 d;
} ST09_TALK_AREA;

// The block at +0x348 of ST09_ACTOR (STAGE_ACTOR_CTL with more fields named).
typedef struct
{
    uint16 flags_0;          // 348
    uint16 value_2;          // 34A: low nibble picks the turn (func_80106C44)
    uint16 timer_4;          // 34C
    uint8 reserved06[2];     // 34E
    sint16 value_8;          // 350
    sint16 timer_A;          // 352
    STCOM_SVECTOR pos_C;     // 354: the hit box
    uint32 hit_14;           // 35C: damage in the low 24 bits, kind bits above
    sint32 value_18;         // 360
    STCOM_SVECTOR target_1C; // 364: the attacker's position (pad bit 0: from the player?)
    uint8 track_24[0x10];    // 36C (Track_reset)
    union
    {
        STCOM_SVECTOR target; // an NPC's walk target (func_80107D28)
        sint16 timer[4];      // [1]: an enemy's frames before it bursts
    } u_34;                   // 37C
    uint8 reserved3C[0x3C];   // 384
} ST09_ACTOR_CTL;

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
    uint8 reserved188[0x1C0];               // 188
    ST09_ACTOR_CTL ctl;                     // 348
} ST09_ACTOR;

typedef void (*ST09_ACTOR_FUNC)(ST09_ACTOR *wp);

void func_80106AFC(ST09_ACTOR *wp);
void func_80106B78(ST09_ACTOR *wp);
sint32 func_80106C44(ST09_ACTOR *wp);
void func_801067E4(ST09_ACTOR *wp);
void func_80106424(ST09_ACTOR *wp);
void func_80107D28(ST09_ACTOR *wp);
void func_80107E54(ST09_ACTOR *wp);
void func_80108A8C(ST09_ACTOR *wp);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80109C94(ST09_ACTOR *wp);
extern ST09_ACTOR_FUNC D_8011DF94[];
extern ST09_ACTOR_FUNC D_8011DF40[];
extern uint8 D_8011DF4C[];
extern uint8 D_8011DF58[];
void func_80108384(ST09_ACTOR *wp);
sint32 func_80109BB8(ST09_ACTOR *wp);

void func_80111450(STAGE_OBJ *wp);

void func_80111508(STAGE_OBJ *wp);

sint32 func_80112918(STAGE_STCOM15_WORK_4E0 *wp);
sint32 func_80042208(void);

// A ROCK_NEO record per kind and variant (D_8009884C): 16 bytes each.
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // life / 32
    uint8 limit_9; // damage that stuns it (times 4)
    uint8 reserved0A[5];
    uint8 value_F; // Track_reset's second argument
} ST09_KIND_REC;

extern ST09_KIND_REC **D_8009884C;

// stcom15's control block as the paired object uses it (func_80112918): its two parts at +0x34.
typedef struct
{
    uint8 reserved00[0x34];
    STAGE_OBJ *part_34;
    STAGE_OBJ *part_38;
} ST09_PAIR_CTL;

void func_8005D6E8(void *wp);

void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);

// The patrol data at D_8011E1C8 (func_801127A4): two routes, then the areas that start them.
typedef struct
{
    ST09_ROUTE route_0[4];  // 00: D_8011E1C8
    ST09_ROUTE route_30[4]; // 30: D_8011E1F8
    uint8 reserved60[0x10]; // 60
    sint16 area_70[4];      // 70: D_8011E238 (x, z, w, d)
    uint8 reserved78[4];    // 78
    sint16 area_7C[4];      // 7C: D_8011E244
} ST09_PATROL;

#define ST09_PATROL_DATA (*(ST09_PATROL *)D_8011E1C8)

// ROCK_NEO's sprite list (Billboard_get fills it the same way).
extern uint32 D_800988FC;
extern uint32 *D_800BE6D8[];
#define ST09_PACKET_PTR ((uint32 **)0x1F800070)

// A slot's part records from +0x100 (value_3 -1 hides a part).
#define ST09_OBJ_PART(wp) ((STAGE_PART_S *)((uint8 *)(wp) + 0x100))

extern ST09_TALK_AREA D_8011DF64;
extern STAGE_ACTOR D_8009F108[]; // ROCK_NEO's 0x3C0-byte slots
extern uint32 D_800987E8;        // ROCK_NEO: allocation mask of the 0x3C0 slots

void func_801080B8(ST09_ACTOR *wp);

// A 0x3C0-byte slot seen through its part flags from +0xF8; value_3 is -1 while the part is
// hidden (func_80111650; r3_st00's ST00_PARTS_VIEW).
typedef struct
{
    uint8 reserved00[0xF8];     // 00
    STAGE_PART_S part_F8[0x18]; // F8
} ST09_PARTS_VIEW;

#define ST09_PART_FLAGS_F8(wp) (((ST09_PARTS_VIEW *)(wp))->part_F8)

#endif
