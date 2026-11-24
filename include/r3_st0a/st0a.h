#ifndef ST0A_H
#define ST0A_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom23.h"
#include "stage_common/stcom18.h"

// From r3_st17 (ST17_TALK_FUNC).
// Talk routines: the work slot, the scene's script position and the slot's face.
typedef void (*ST0A_TALK_FUNC)(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);

// The routines of D_80115938: the work slot, the scene's script position and the slot's +0x348.
typedef void (*ST0A_SCENE_HIT_FUNC)(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *hit);

// From r3_st17 (ST17_SPRITE).
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
} ST0A_SPRITE;

// From r3_st17 (ST17_PART_D0).
// The state a 0x10C-byte slot keeps at +0xD0 (func_80111A7C's objects).
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
} ST0A_PART_D0;

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
    ST0A_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    ST0A_PART_D0 part_D0;                   // D0
} ST0A_10C;

// From r3_st02 (ST02_SPARK).
// A rising spark effect and its emitter (variant_3 1 and 0): the emitter (func_80104448) sheds a
// spark every few frames (func_80113AA4); a spark fades out while it rises (func_80104184), and
// ends when its emitter's routine does.
typedef struct ST0A_SPARK ST0A_SPARK;

// From r3_st02 (ST02_SPARK).
struct ST0A_SPARK
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
    ST0A_SPARK *owner_2C;   // 2C
    uint8 reserved30[0x18]; // 30
};

// From r3_st17 (ST17_CELL).
// A grid of 9 rows of 8 cells kept at a work slot's +0x88 (func_80105D04's objects).
typedef struct
{
    STAGE_XYZ *origin_0; // 00
    uint8 state_4;       // 04
    uint8 shade_5;       // 05: subtracted from each color channel
    sint16 frame_6;      // 06: D_8011AF44[frame_6 / 4] is the texture u
    uint16 size_8;       // 08
    sint16 x_A;          // 0A
    sint16 y_C;          // 0C
    sint16 z_E;          // 0E
} ST0A_CELL;

// From r3_st17 (ST17_GRID6).
// A grid of 6 rows of 8 cells kept at a work slot's +0x88 (func_80101D10's objects).
typedef struct
{
    sint8 mode_0;            // 00: D_8011AF24 handler
    uint8 mask_1;            // 01: rows that also run D_8011AF38
    uint8 reserved02;        // 02
    uint8 rows_3;            // 03: rows func_80102038 runs
    uint8 count_4[6];        // 04: per row
    uint8 reserved0A;        // 0A
    sint8 kind_B;            // 0B: D_8011AF38 handler
    sint32 frame_C;          // 0C
    sint32 value_10;         // 10
    ST0A_CELL cell_14[6][8]; // 14
} ST0A_GRID6;

// A work slot (func_80031418) that carries a ST0A_GRID6 at +0x88 (func_80108334, func_80108478).
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
    ST0A_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0A_GRID_OBJ;

// A talking slot's face block (+0x4E0) followed by a grid object and the six origins its rows
// hang from (func_8010FBD0).
typedef struct
{
    STAGE_FACE face;            // 00
    ST0A_GRID_OBJ *grid_14;     // 14
    STCOM_SVECTOR origin_18[6]; // 18
} ST0A_GRID_HOLDER;

// From r3_st17 (ST17_CELL_FUNC).
typedef void (*ST0A_CELL_FUNC)(ST0A_CELL *cell, sint32 value);

// From r3_st17 (ST17_GRID6_FUNC).
typedef void (*ST0A_GRID6_FUNC)(ST0A_GRID6 *grid, ST0A_CELL *cell);

// A view of the work slots r3_st0a's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST0A_VIEW ST0A_VIEW;

typedef void (*ST0A_VIEW_FUNC)(ST0A_VIEW *wp);
struct ST0A_VIEW
{
    sint8 flags_0;        // 0
    uint8 value_1;        // 1
    uint8 kind_2;         // 2
    uint8 variant_3;      // 3
    uint8 value_4;        // 4
    uint8 value_5;        // 5
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
    uint16 value_50;             // 50
    uint8 reserved52[0x2];       // 52
    STCOM_SVECTOR rotation;      // 54
    STCOM_SVECTOR rotation_prev; // 5C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_64;                // 64
    uint8 reserved68[0x6]; // 68
    sint16 value_6E;       // 6E
    uint8 reserved70[0x8]; // 70
    sint32 value_78;       // 78
    sint16 value_7C;       // 7C
    uint8 reserved7E[0x2]; // 7E
    sint32 value_80;       // 80
    uint8 reserved84[0x4]; // 84
    sint32 value_88;       // 88
    sint32 value_8C;       // 8C
    sint16 value_90;       // 90
    sint16 value_92;       // 92
    sint16 value_94;       // 94
    uint8 value_96;        // 96
    uint8 value_97;        // 97
    uint16 value_98;       // 98
    uint8 reserved9A[0x2]; // 9A
    sint32 value_9C;       // 9C
    uint8 reservedA0[0x4]; // A0
    STCOM_SVECTOR vec_A4;  // A4
    union
    {
        uint8 b[2];
        sint16 h[1];
    } u_AC;                  // AC
    sint16 value_AE;         // AE
    sint16 value_B0;         // B0
    sint16 value_B2;         // B2
    sint32 value_B4;         // B4
    uint8 reservedB8[0xC];   // B8
    sint32 value_C4;         // C4
    sint32 value_C8;         // C8
    sint32 value_CC;         // CC
    uint8 reservedD0[0x4];   // D0
    STCOM_SVECTOR vec_D4;    // D4
    STCOM_SVECTOR vec_DC;    // DC
    STCOM_SVECTOR vec_E4;    // E4
    STCOM_SVECTOR vec_EC;    // EC
    STCOM_SVECTOR vec_F4;    // F4
    STCOM_SVECTOR vec_FC;    // FC
    uint8 reserved104[0xC];  // 104
    uint8 value_110;         // 110
    uint8 reserved111[0x47]; // 111
    sint32 value_158;        // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    uint8 reserved160[0x38];  // 160
    STCOM_SVECTOR vec_198;    // 198
    uint8 reserved1A0[0x20];  // 1A0
    STCOM_SVECTOR vec_1C0;    // 1C0
    uint8 reserved1C8[0x16];  // 1C8
    sint16 value_1DE;         // 1DE
    uint8 reserved1E0[0x148]; // 1E0
    uint16 value_328;         // 328
    sint16 value_32A;         // 32A
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_32C; // 32C
    union
    {
        uint16 h[2];
        sint32 w[1];
    } u_330;                 // 330
    uint8 reserved334[0x8];  // 334
    sint32 value_33C;        // 33C
    sint32 value_340;        // 340
    uint8 reserved344[0x18]; // 344
    STCOM_SVECTOR vec_35C;   // 35C
    sint32 value_364;        // 364
    sint32 value_368;        // 368
    uint8 reserved36C[0xD4]; // 36C
    uint16 value_440;        // 440
    uint8 reserved442[0x2];  // 442
    uint16 value_444;        // 444
    sint16 value_446;        // 446
    uint8 reserved448[0xC];  // 448
    sint32 value_454;        // 454
    uint8 reserved458[0x28]; // 458
    sint16 value_480;        // 480
    uint16 value_482;        // 482
    uint16 value_484;        // 484
    uint8 reserved486[0xA];  // 486
    sint32 value_490;        // 490
    uint8 reserved494[0xC];  // 494
    sint32 value_4A0;        // 4A0
    uint8 reserved4A4[0x4];  // 4A4
    STCOM_SVECTOR vec_4A8;   // 4A8
    sint32 value_4B0;        // 4B0
    sint32 value_4B4;        // 4B4
    sint32 value_4B8;        // 4B8
    sint32 value_4BC;        // 4BC
    uint8 reserved4C0[0x40]; // 4C0
    sint16 value_500;        // 500
    uint8 reserved502[0x30]; // 502
    uint16 value_532;        // 532
    uint8 reserved534[0x70]; // 534
};

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
} ST0A_SHOT_FIXED;

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
    ST0A_SHOT_FIXED fpos;       // 1C
    STCOM_SVECTOR old_pos;      // 2C
    ST0A_SHOT_FIXED old_fpos;   // 34
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
} ST0A_SHOT;

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
} ST0A_SHOT_FX;

typedef void (*ST0A_HIT_FUNC)(STAGE_OBJ *wp, sint32 arg, STCOM_SVECTOR *hit);
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
} ST0A_SHL;

// Player_work's signed bytes past STCOM_PL_WORK's fields.
#define ST0A_PL_SBYTE(offset) (*((sint8 *)&Player_work + (offset)))

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
    ST0A_SPRITE sprite;                     // 88
    sint32 value_BC;                        // BC
    sint32 value_C0;                        // C0
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    uint32 count_CC;                        // CC
    uint8 reservedD0[4];                    // D0
    STCOM_SVECTOR trail_D4[6];              // D4: the trail's points
    uint8 reserved104[8];                   // 104
} ST0A_10C_B;

#define ST0A_ABS(x) ((x) < 0 ? -(x) : (x))

// An enemy slot (D_80116208's routines): STAGE_OBJ's layout, then its own state at +0x440.
// func_80113C4C's arguments for the enemy's two spark emitters (D_801161F8).
typedef struct
{
    uint8 width_0;  // 0
    uint8 growth_1; // 1
    sint16 count_2; // 2
    sint32 rise_4;  // 4
} ST0A_SPARK_ARGS;

// A hit point the enemy reports to func_800341BC: where, and what it hit.
typedef struct
{
    STCOM_SVECTOR pos_0; // 0
    uint32 hit_8;        // 8
    sint32 value_C;      // C
} ST0A_EM_HIT;

typedef struct
{
    uint16 flags_0;             // 00
    uint16 value_2;             // 02
    sint16 timer_4;             // 04
    sint16 value_6;             // 06
    sint16 value_8;             // 08
    sint16 value_A;             // 0A
    ST0A_EM_HIT hit_C;          // 0C
    uint8 reserved1C[8];        // 1C
    uint8 track_24[0x10];       // 24: Track_reset
    uint8 *uv_34;               // 34: a face's texture coordinates (Model_face_get)
    sint16 *vtx_38;             // 38: vertices (Model_vertex_get)
    sint16 *vtx_3C;             // 3C
    sint16 value_40;            // 40
    uint16 angle_42;            // 42
    uint16 value_44;            // 44
    sint16 value_46;            // 46
    ST0A_EM_HIT hit_48;         // 48
    ST0A_EM_HIT hit_58;         // 58
    STCOM_SVECTOR pos_68;       // 68
    STCOM_FIXED_VECTOR fpos_70; // 70
    STAGE_OBJ *obj_80[2];       // 80
    ST0A_EM_HIT hit_88[6];      // 88
    ST0A_SPARK *spark_E8[2];    // E8
    sint16 value_F0;            // F0
    uint16 flags_F2;            // F2
    sint16 value_F4;            // F4
    sint16 value_F6;            // F6
    sint16 value_F8;            // F8: life_6E as last shown
    uint8 reservedFA[2];        // FA
} ST0A_EM_EXT;

typedef struct
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
    sint8 byte_C;                           // 0C
    sint8 byte_D;                           // 0D
    sint8 byte_E;                           // 0E
    sint8 byte_F;                           // 0F
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STAGE_FIXED value_44;                   // 44
    STAGE_FIXED value_48;                   // 48
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    sint16 value_66;                        // 66
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[4];                    // 7C
    uint32 dist_80;                         // 80: to the player
    uint8 reserved84[4];                    // 84
    void *model_88;                         // 88
    uint8 reserved8C[0x1A];                 // 8C
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joint_180[24];            // 180
    STCOM_MATRIX mtx_240[12];               // 240
    uint8 reserved3C0[0x80];                // 3C0
    ST0A_EM_EXT ext;                        // 440
    uint8 reserved53C[0x68];                // 53C
} ST0A_EM;

typedef void (*ST0A_EM_FUNC)(ST0A_EM *wp);

// A record of ROCK_NEO's table at D_8009884C, by kind (r3_st13's ST13_KIND).
typedef struct
{
    uint8 reserved0[8]; // 0
    uint8 life_8;       // 8: times 32
    uint8 value_9;      // 9
    uint8 value_A;      // A: or'd into the hit box's kind bits
    uint8 value_B;      // B
    uint8 value_C;      // C
    uint8 value_D;      // D
    uint8 value_E;      // E
    uint8 value_F;      // F
} ST0A_KIND;

extern ST0A_KIND **D_8009884C;

// A model's draw record at a 0x10C-byte slot's +0x88.
typedef struct
{
    void *model_0;         // 00
    STCOM_MATRIX mtx_4;    // 04
    STCOM_SVECTOR pos_24;  // 24
    uint32 color_2C;       // 2C
    uint8 reserved30[0xC]; // 30
} ST0A_MODEL;

// A 0x10C-byte piece of debris (D_801164EC's routines): it flies off, homes in on the player
// and drops, cycling through four models (routine_2 picks the one drawn).
typedef struct ST0A_PIECE ST0A_PIECE;
typedef void (*ST0A_PIECE_FUNC)(ST0A_PIECE *wp);

struct ST0A_PIECE
{
    uint8 flags_0;                // 00
    uint8 value_1;                // 01
    uint8 kind_2;                 // 02
    uint8 variant_3;              // 03
    uint8 reserved04[4];          // 04
    uint8 routine_0;              // 08
    uint8 routine_1;              // 09
    uint8 routine_2;              // 0A: the model drawn
    uint8 timer_B;                // 0B
    sint8 range_C;                // 0C
    uint8 reserved0D[7];          // 0D
    STCOM_SVECTOR position;       // 14
    ST0A_SHOT_FIXED fpos;         // 1C
    STCOM_SVECTOR position_prev;  // 2C
    STCOM_FIXED_VECTOR fpos_prev; // 34
    sint16 vx, vy, vz;            // 44
    uint8 reserved4A[2];          // 4A
    sint16 ax, ay, az;            // 4C
    uint8 reserved52[2];          // 52
    STCOM_SVECTOR rotation;       // 54
    uint8 reserved5C[0x1C];       // 5C
    void *box_78;                 // 78
    sint16 hit_7C;                // 7C
    uint8 reserved7E[2];          // 7E
    uint32 dist_80;               // 80: to the player, squared
    uint8 reserved84[4];          // 84
    ST0A_MODEL model;             // 88
    uint32 hit_C4;                // C4
    uint32 hit_C8;                // C8
    void *models_CC[4];           // CC
    uint8 reservedDC[0x30];       // DC
};

// A 0x24-byte event slot (STAGE_EV) with a frame count at +0x1C.
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
    uint8 reserved0C[0x10]; // 0C
    uint32 frame_1C;        // 1C
    uint8 reserved20[4];    // 20
} ST0A_EV;

// A model slot carrying its own matrix (STAGE_LIGHT's layout): func_80114580's prop.
typedef struct
{
    uint8 flags_0;          // 00
    uint8 value_1;          // 01
    uint8 kind_2;           // 02
    uint8 variant_3;        // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 reserved09[0xF];  // 09
    STAGE_MATRIX matrix;    // 18
    STCOM_SVECTOR position; // 38
    uint32 color_40;        // 40
} ST0A_PROP;

// The 0x10C-byte object a ST0A_EN carries and throws (ST0A_EN_CTL's held_3C).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[2];               // 04
    uint8 flags_6;                     // 06
    uint8 reserved07;                  // 07
    uint8 routine_0;                   // 08
    uint8 reserved09[0xB];             // 09
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    uint16 angle_64;                   // 64
    uint8 reserved66[0x36];            // 66
    sint32 speed_9C;                   // 9C
    sint32 value_A0;                   // A0
    uint8 reservedA4[0x68];            // A4
} ST0A_HELD;

// The block at +0x328 of a ST0A_EN (stcom13's STCOM13_CTL, 0x20 bytes earlier and longer).
typedef struct
{
    uint16 flags_0;        // 328
    uint16 rand_2;         // 32A: a new random number every frame
    sint16 timer_4;        // 32C
    sint16 timer_6;        // 32E
    sint16 value_8;        // 330
    sint16 damage_A;       // 332
    STCOM_SVECTOR pos_C;   // 334: the hit box's center
    uint32 hit_14;         // 33C: damage in the low 24 bits, kind bits above
    uint32 value_18;       // 340
    STCOM_SVECTOR from_1C; // 344
    uint8 track_24[0x10];  // 34C: Track_reset
    STCOM_SVECTOR home_34; // 35C: where it started
    ST0A_HELD *held_3C;    // 364
    STAGE_OBJ *owner_40;   // 368: func_80036294's object
} ST0A_EN_CTL;

// A 0x3C0-byte enemy (D_8011597C's routines; stcom13's STCOM13_WORK with its block at +0x328).
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
    sint8 byte_C;                           // 0C: func_80036294's argument
    uint8 reserved0D[3];                    // 0D
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
    sint16 turn_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[0x28];                 // 7C
    uint8 value_A4;                         // A4
    uint8 reservedA5;                       // A5
    sint8 value_A6;                         // A6
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
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
    STCOM_SVECTOR joints_180[0x35];         // 180
    ST0A_EN_CTL ctl;                        // 328
    uint8 reserved36C[0x54];                // 36C
} ST0A_EN;

typedef void (*ST0A_EN_FUNC)(ST0A_EN *wp);

// A ROCK_NEO record per kind (D_80098844; stcom13's STCOM13_KIND has the same at 0x18).
typedef struct
{
    uint8 reserved00[0x28];
    uint8 life_28;
    uint8 stun_29; // damage that ends a stun
} ST0A_EN_KIND;

extern ST0A_EN_KIND **D_80098844;
void *func_80036294(sint32 kind);
sint32 func_8003648C(void *track, void *wp);

extern STAGE_SLOT_FUNC *D_801146A8[];
extern STAGE_SLOT_FUNC *D_801147E8[];
extern STAGE_SLOT_FUNC D_80114818[];
extern STAGE_SLOT_FUNC D_801148D8[];
extern STAGE_SLOT_FUNC D_80114918[];
extern STAGE_SLOT_FUNC D_80114950[];
extern STAGE_ROOM2_FUNC *D_80114B08[];
extern STAGE_OBJ_FUNC D_80116410[];
extern STAGE_OBJ_FUNC D_8011656C[];
extern STAGE_OBJ_FUNC D_80116574[];
extern STAGE_OBJ_FUNC D_80116594[];
extern uint8 D_80114EE0[];
extern STAGE_ROOM2_FUNC D_80114F50[];
extern STAGE_PART_FUNC D_80116144[];
extern uint8 D_80116174[];
extern STAGE_ROOM2_FUNC D_801154C0[];
extern ST0A_GRID6_FUNC D_80116154[];
extern ST0A_CELL_FUNC D_80116168[];
extern uint8 D_80114EE8[];
extern uint8 D_80114EF0[][8];
extern ST0A_HIT_FUNC D_80115948[];
extern ST0A_HIT_FUNC D_80115960[];
extern void *D_8011499C[];
extern void *D_801149C8[];
extern void *D_80114A14[];
extern uint8 D_80114A18[][0x28];
extern uint8 D_80114A40[][8];
extern sint32 D_80114AD8[];
extern uint8 D_80114EB8[];
extern STAGE_SCRIPT_ENTRY D_80114F5C[];
extern uint8 D_80114FE8[];
extern STAGE_ROOM2_FUNC D_80115034[];
extern uint8 D_80115044[];
extern STAGE_ROOM2_FUNC D_80115470[];
extern STAGE_SCRIPT_ENTRY D_801154CC[];
extern STAGE_SCRIPT_ENTRY D_80115508[];
extern STAGE_SCRIPT_ENTRY D_8011551C[];
extern uint8 D_80115558[];
extern STAGE_ROOM2_FUNC D_801155A4[];
extern uint8 D_801155B4[];
extern STAGE_ROOM2_FUNC D_801158BC[];
extern ST0A_SCENE_HIT_FUNC D_80115938[];
extern ST0A_EN_FUNC D_80115970[];
extern ST0A_EN_FUNC D_8011597C[];
extern sint16 D_80115988[]; // the enemy's hit box
extern ST0A_SPARK_ARGS D_801161F8[];
extern ST0A_EM_FUNC D_80116208[];
extern ST0A_EM_FUNC D_80116218[];
// The center the enemy circles. An incomplete array: as a complete 8-byte object GCC would treat
// it as small data and fold its address into the copies.
extern STCOM_SVECTOR D_80116248[];
extern STCOM_FIXED_VECTOR D_80116250; // the same point in 16.16
extern STCOM_SVECTOR D_80116260[6];   // the six hit points' offsets, in 16ths
extern sint16 D_80116290[];
extern sint16 D_80116292[];
extern ST0A_TALK_FUNC D_801162B0[];
extern void *D_80116334[];
extern void *D_80116360[];
extern void *D_8011638C[];
extern void *D_80116398[];
extern STCOM_SVECTOR D_801163A4[]; // the six grid origins' offsets (func_8010FBD0)
extern uint32 D_801163F8[];        // hit kinds, by byte_D
extern uint32 D_80116404[];        // func_80037738's amounts, by byte_D
extern sint16 D_80116422[];
extern uint16 D_80116424[];
extern sint16 D_80116426[];
extern sint16 D_801164E0[]; // the pieces' hit box
extern ST0A_PIECE_FUNC D_801164EC[];
extern uint8 D_80116560[];
extern uint8 D_8011B604;
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_8011025C(STAGE_OBJ *wp);
STCOM_SVECTOR func_8011092C(ST0A_10C *wp);
void func_80113174(STAGE_OBJ *wp);
void func_80113988(STAGE_SPARK *wp);
void func_80113A14(STAGE_SPARK *wp);
void func_80113A48(STAGE_OBJ *wp);
void func_80113A68(STAGE_OBJ *wp);
void func_80113AA4(ST0A_SPARK *wp);
void func_80113BEC(STAGE_OBJ *wp);
ST0A_SPARK *func_80113C4C(STAGE_XYZ *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag);
void func_8011422C(STAGE_OBJ *wp);
void func_801043B8(ST0A_EN *wp);
void func_801043D8(ST0A_EN *wp);
void func_80104154(ST0A_EN *wp);
sint32 func_8010490C(ST0A_EN *wp);
void Scene_obj_list_open(uint8 *);
void func_801007D8(STAGE_ROOM *wp);
void func_80100824(STAGE_ROOM *wp);
void func_8010F0D4(STAGE_OBJ *wp);
void func_8010FA88(STAGE_OBJ *wp, STAGE_FACE *face);
void func_80101178(STAGE_ROOM *wp);
void func_80108BDC(ST0A_GRID6 *grid, uint8 row, uint8 col);
void func_8010E584(STAGE_OBJ *wp);
void func_80100DE8(STAGE_ROOM *wp);
void func_80100E34(STAGE_ROOM *wp);
void func_801015D4(STAGE_OBJ *wp);
void func_80102F58(STAGE_OBJ *wp, STAGE_OBJ *arg1);
void func_80103530(STAGE_OBJ *wp, STAGE_ROOM *arg1, sint16 *arg2);
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void *func_80031498(void);
void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 color);
sint32 func_800375D4(void *pl, sint32 arg);
// func_8003430C is declared in stage_common/stage.h.
void func_80113744(ST0A_SHOT *wp);
void func_80113888(ST0A_SHOT *wp, sint32 arg);
void func_800354E0(sint32 bit);
sint16 func_80039B80(void);
sint32 func_80037634(void *player, sint32 arg);
void func_801131C4(ST0A_SHL *wp);
void func_80110298(ST0A_10C_B *wp);
void func_80110878(ST0A_10C_B *wp);
void func_80110A0C(ST0A_10C_B *wp);

// func_80110AC4's 24 spiral sparks: each one flies for 16 frames from its start, spiraling out.
typedef struct
{
    sint16 start_0;  // 0: count_CC when it appears
    sint16 radius_2; // 2
    uint16 angle_4;  // 4
    sint16 height_6; // 6
} ST0A_SPIRAL;

extern ST0A_SPIRAL D_80116420[24];
void func_80110AC4(ST0A_10C *wp);

void func_80110D60(ST0A_10C *wp);

void func_8010BE60(ST0A_EM *wp);
void func_8010BECC(ST0A_EM *wp);
void func_8010C0A0(ST0A_EM *wp);
void func_8010CB1C(ST0A_EM *wp);
void func_8010CBBC(ST0A_EM *wp);
void func_8010CE0C(ST0A_EM *wp);
void func_8010CFE8(ST0A_EM *wp);
void func_8010D2F4(ST0A_EM *wp);
void func_8010D6C0(ST0A_EM *wp);
void func_8010DAA8(ST0A_EM *wp);
void func_8010DC08(ST0A_EM *wp);
void func_8010DD20(ST0A_EM *wp);
void func_8010E164(ST0A_EM *wp);
void func_8010E254(ST0A_EM *wp);
void func_8010E590(ST0A_EM *wp);
sint32 func_8010E8A0(ST0A_EM *wp);
sint32 func_8010E95C(ST0A_EM *wp);
void func_8010ED90(ST0A_EM *wp, sint32 index);
void func_8010E9C8(ST0A_EM *wp, sint32 side);
sint32 func_8010EE60(ST0A_EM *wp, sint32 index);
uint8 *Model_face_get(void *model, sint32 id);
sint32 func_80042208(void);
void func_8005D4C0(void);
void func_80111788(ST0A_PIECE *wp);
void func_80111864(ST0A_PIECE *wp);
void func_801118B4(ST0A_PIECE *wp);
// A scratchpad halfword Model_parts_mtx_set_y reads: the enemy's turn.
#define ST0A_SP_182 (*(uint16 *)0x1F800182)
void func_80052528(void *wp);
void func_8005D6E8(void *wp);
// Declared returning int here: retail narrows the result at each use (rock_neo.h).
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 func_8010EBE8(ST0A_EM *wp);
sint32 func_8010EF3C(ST0A_EM *wp);
sint16 *Model_vertex_get(void *model, sint32 id);

sint32 func_80101BB4(sint32 arg);
sint32 func_80101A78(sint32 down);
void func_8003187C(void *wp);
void func_80031A4C(void *wp);

void func_8005D7C0(void);
void Sce_event_timer_clear(void);
void func_8003697C(void);
void func_80053AA4(sint32 arg);
void Game_logo_kill(sint32 index);
void func_8003A264(void);
extern sint16 D_8011B5FC; // the gate's height (func_80101A78)
extern sint16 D_8011B600; // its step

extern uint16 D_800C0F96[]; // the pad bits the player sees this frame

sint32 func_8010EB40(void);

#endif
