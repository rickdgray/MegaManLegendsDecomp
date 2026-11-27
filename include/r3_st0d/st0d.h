#ifndef ST0D_H
#define ST0D_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"

// From r3_st0a (ST0A_CELL).
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
} ST0D_CELL;

// From r3_st0a (ST0A_GRID6).
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
    ST0D_CELL cell_14[6][8]; // 14
} ST0D_GRID6;

// From r3_st17 (ST17_TALK_FUNC).
// Talk routines: the work slot, the scene's script position and the slot's face.
typedef void (*ST0D_TALK_FUNC)(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);

// The circle a ST0D_ORBITER runs round (+0xCC).
typedef struct
{
    sint16 x_0;         // CC: center
    sint16 y_2;         // CE
    sint16 z_4;         // D0
    sint16 speed_6;     // D2: added to the angle every frame
    sint16 angle_8;     // D4
    uint8 reservedA[2]; // D6
    sint32 radius_C;    // D8
} ST0D_ORBIT;

// A 0x10C-byte slot (Open_SHL_WORK) whose model runs round a circle (func_801050E8).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 reserved02[6];                    // 02
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
    ST0D_ORBIT orbit;                       // CC
    uint8 reservedDC[0x30];                 // DC
} ST0D_ORBITER;

// Scene_work's halfword at +4, read on its own by the talk routines (func_80102210).
#define ST0D_SCENE_HALF_4(scene) (*(uint16 *)((uint8 *)(scene) + 4))

// A signed byte of a STAGE_OBJ that STAGE_OBJ leaves reserved (+0x143 and +0x147: func_80102C00).
#define ST0D_OBJ_SBYTE(wp, offset) (*((sint8 *)(wp) + (offset)))

// The routines of D_8010DBE0 and D_8010DBF8: a 0x10C-byte prop and the bobbing state its caller
// passes through (func_80105058).
typedef void (*ST0D_BOB_FUNC)(STAGE_PROP *wp, uint16 *bob);

// A flame of ST0D_FLAMES: bit 0 of flags_0 lit, frame_1 its animation frame.
typedef struct
{
    uint8 flags_0; // 0
    sint8 frame_1; // 1
} ST0D_FLAME;

// A 0x48-byte effect slot (func_80031618) of four flames that follow the slot whose id is in
// value_C (func_8010B544, func_8010B9B8).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 slot;             // 01
    uint8 id;               // 02
    uint8 type;             // 03
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
    ST0D_FLAME flame_28[6]; // 28: four or six
    uint8 reserved34[0x14]; // 34
} ST0D_FLAMES;

// From r3_st0a (ST0A_GRID_OBJ).
// A work slot (func_80031418) that carries a ST0D_GRID6 at +0x88 (func_80108468, func_801085AC).
typedef struct
{
    uint8 be_flag;       // 00
    uint8 slot;          // 01
    uint8 id;            // 02
    uint8 type;          // 03
    uint8 value_4;       // 04
    uint8 reserved05;    // 05
    uint8 flags;         // 06
    uint8 reserved07[5]; // 07
    union
    {
        sint32 word;
        uint8 flags;         // bit 0: set by the lift (func_80104444)
    } u_C;                   // 0C
    sint32 value_10;         // 10
    uint8 reserved14[0x74];  // 14
    ST0D_GRID6 grid;         // 88
    uint8 reserved39C[0x24]; // 39C
} ST0D_GRID_OBJ;

// From r3_st0a (ST0A_CELL_FUNC).
// From r3_st17 (ST17_CELL_FUNC).
typedef void (*ST0D_CELL_FUNC)(ST0D_CELL *cell, sint32 value);

// From r3_st0a (ST0A_GRID6_FUNC).
// From r3_st17 (ST17_GRID6_FUNC).
typedef void (*ST0D_GRID6_FUNC)(ST0D_GRID6 *grid, ST0D_CELL *cell);

// From r3_st05 (STCOM21_WORK).
// The 0x50-byte work slot (func_80031734) of the objects in stcom21: a villager who talks
// (0000..0E48), a treasure chest whose lid opens (0E88..1908) and a smaller box (19D0..1DDC).
typedef struct ST0D_STCOM21_WORK ST0D_STCOM21_WORK;

// From r3_st05 (STCOM21_MATRIX).
// A matrix whose identity setup writes it as eight words.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} ST0D_STCOM21_MATRIX;

// From r3_st05 (STCOM21_WORK).
struct ST0D_STCOM21_WORK
{
    uint8 be_flag;              // 00
    uint8 slot;                 // 01: pool id and slot
    uint8 id;                   // 02
    uint8 type;                 // 03
    uint8 reserved04[4];        // 04
    uint8 routine_0;            // 08
    uint8 routine_1;            // 09
    uint8 routine_2;            // 0A
    uint8 value_B;              // 0B: message (villager), lid frame (chest)
    sint8 value_C;              // 0C: flags (villager), scene flag - 0x400 (chest)
    sint8 value_D;              // 0D: contents' kind
    sint8 value_E;              // 0E: timer (villager), contents (chest)
    sint8 value_F;              // 0F: rotation
    void *model_10;             // 10
    uint8 reserved14[4];        // 14
    ST0D_STCOM21_MATRIX matrix; // 18
    STCOM_SVECTOR pos_38;       // 38: pad holds the spawn's scene flag
    uint32 color_40;            // 40
    union
    {
        sint32 flag;              // the scene flag that must be set (chests)
        STCOM_EFFECT *effect;     // the effect it waits for (villager)
        ST0D_STCOM21_WORK *chest; // the chest a lid belongs to
    } u_44;
    STCOM_FIXED y_48; // 48: hit result bits; a lid's height
    sint32 speed_4C;  // 4C
};

// From r3_st05 (STCOM21_IDENTITY).
#define ST0D_STCOM21_IDENTITY(mw)                                                                                                          \
    ((mw)->words[0] = 0x1000, (mw)->words[1] = 0, (mw)->words[2] = 0x1000, (mw)->words[3] = 0, (mw)->words[4] = 0x1000,                    \
     (mw)->words[5] = 0, (mw)->words[6] = 0, (mw)->words[7] = 0)

// From r3_st05 (STCOM21_OBJ).
// A 0x3C0-byte work slot (func_80031418) as func_8010AA54 sets it up.
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 slot;                        // 01
    uint8 id;                          // 02
    uint8 type;                        // 03
    uint8 handler;                     // 04
    uint8 reserved05[0xF];             // 05
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
} ST0D_STCOM21_OBJ;

// A slot with sixteen byte pairs at +0x28 (cleared together).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 slot;             // 01
    uint8 reserved02[6];    // 02
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 reserved0C[3];    // 0C
    uint8 value_F;          // 0F
    uint8 reserved10[0x18]; // 10
    uint8 pair_28[16][2];   // 28
} ST0D_PAIRS;

typedef void (*ST0D_10C_FUNC)(STAGE_10C *wp, sint32 *part);
// From r3_st04 (ST04_ACTOR_CTL).
// A 0x20-byte control block of ST0D_ACTOR (at +0x348 and +0x368).
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
} ST0D_ACTOR_CTL;

// From r3_st04 (ST04_ACTOR).
// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
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
    ST0D_ACTOR_CTL ctl;                     // 348
    ST0D_ACTOR_CTL ctl2;                    // 368
    uint8 reserved388[0x38];                // 388
} ST0D_ACTOR;

typedef void (*ST0D_ACTOR_FUNC)(ST0D_ACTOR *wp);
// The camera request at D_800C3558 (D_800C356C..D_800C3571 are reached through their own symbols).
typedef struct
{
    uint8 reserved00[8]; // 00
    sint16 x_8;          // 08
    sint16 y_A;          // 0A
    sint16 z_C;          // 0C
    uint8 reserved0E[4]; // 0E
    sint16 value_12;     // 12
    sint8 value_14;      // 14
    uint8 value_15;      // 15
    uint8 mode_16;       // 16
    uint8 value_17;      // 17
} ST0D_CAMERA;

// The bobbing motion of a ST0D_BOBBER (+0x348): moves forward and turns every frame, and
// rides a sine wave in y (func_80109714).
typedef struct
{
    sint16 speed_0;  // 0
    sint16 height_2; // 2: wave height
    sint16 period_4; // 4: frames per wave
    sint16 turn_6;   // 6
    sint16 phase_8;  // 8
    sint16 base_A;   // A: y at the wave's middle
} ST0D_BOB;

// A 0x3C0-byte work slot that bobs along (func_8010957C).
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 reserved02[6];                    // 02
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
    ST0D_BOB bob;                           // 348
    uint8 reserved354[0x6C];                // 354
} ST0D_BOBBER;

// A 0x5A4-byte work slot moved with the second controller's buttons (func_80109A38): a debug
// marker.
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 reserved02[6];                    // 02
    uint8 routine_0;                        // 08
    uint8 reserved09[0xB];                  // 09
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint32 value_44;                        // 44
    sint32 value_48;                        // 48
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR_W rotation;               // 54
    uint8 reserved5C[8];                    // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[8];                    // 68
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 reserved78[0xE0];                 // 78
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x1F0];               // 160
    sint32 value_350;                       // 350
    uint8 reserved354[0xC];                 // 354
    uint8 anim_360;                         // 360
    uint8 reserved361[0x243];               // 361
} ST0D_MARKER;

// A step of a ST0D_LIFT's path (0xC bytes, D_8010D7D0, D_8010DA34, D_8010DB90).
typedef struct
{
    sint16 flag_0;   // 0: nonzero: jump to (x_2, z_4) first, carrying the player
    sint16 x_2;      // 2: speeds to reach, forward and sideways
    sint16 z_4;      // 4
    sint16 rot_6;    // 6: heading to reach
    sint16 frames_8; // 8
    sint16 next_A;   // A: -1 stay, 0x80 | n go to D_8010DB90[n], else go on
} ST0D_PATH_STEP;

// A ST0D_LIFT's path state (+0xCC).
typedef struct
{
    uint8 reserved00[4];     // 00
    sint16 timer_4;          // 04: frames left in the step
    sint16 x_6;              // 06: the step's goal
    sint16 z_8;              // 08
    sint16 rot_A;            // 0A
    sint16 next_C;           // 0C
    uint8 reserved0E[2];     // 0E
    sint32 x_10;             // 10: 16.16 values and their steps
    sint32 z_14;             // 14
    sint32 dx_18;            // 18
    sint32 dz_1C;            // 1C
    sint32 rot_20;           // 20
    sint32 drot_24;          // 24
    ST0D_GRID_OBJ *grid_28;  // 28
    ST0D_PATH_STEP *step_2C; // 2C
    STCOM_SVECTOR box_30;    // 30: hit boxes
    STCOM_SVECTOR box_38;    // 38
} ST0D_PATH;

// A 0x10C-byte slot (Open_SHL_WORK) that follows a path, carrying the player (func_80104184).
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
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
    ST0D_PATH path;                         // CC
} ST0D_LIFT;

typedef void (*ST0D_LIFT_FUNC)(ST0D_LIFT *wp, ST0D_PATH *path);

// A camera request a sign sets when it is read (D_8010DC60).
typedef struct
{
    sint16 x_0;     // 0
    sint16 y_2;     // 2
    sint16 z_4;     // 4
    sint16 value_6; // 6
    sint8 value_8;  // 8
    uint8 value_9;  // 9
    uint8 value_A;  // A
} ST0D_CAM_SHOT;

// What a ST0D_VILLAGER says and does (+0x348), from tables by its value_D.
typedef struct
{
    sint32 msg_0;           // 00: message (0x7FFFFFFF: none)
    sint32 flag_on_4;       // 04: scene flag set afterwards
    sint32 flag_8;          // 08: scene flag tested
    sint32 first_C;         // 0C: 1 until the flag test fails
    ST0D_CAM_SHOT *shot_10; // 10: camera afterwards (0x7FFFFFFF: none)
} ST0D_TALK;

// A 0x3C0-byte villager who turns to the player and talks (func_80107DDC).
typedef struct
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 value_C;                          // 0C: nonzero: func_8002F9EC sets it up
    sint8 value_D;                          // 0D: talk table index
    sint8 value_E;                          // 0E
    sint8 value_F;                          // 0F
    uint8 *data_10;                         // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0x30];                 // 7C
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180: the talk camera's point
    uint8 reserved188[0x1C0];               // 188
    ST0D_TALK talk;                         // 348
    uint8 reserved35C[0x64];                // 35C
} ST0D_VILLAGER;

// A view of the work slots r3_st0d's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST0D_VIEW ST0D_VIEW;

typedef void (*ST0D_VIEW_FUNC)(ST0D_VIEW *wp);
struct ST0D_VIEW
{
    sint8 be_flag;   // 0
    uint8 slot;      // 1
    uint8 id;        // 2
    uint8 type;      // 3
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
    uint8 reserved4C[0x8];       // 4C
    STCOM_SVECTOR rotation;      // 54
    STCOM_SVECTOR rotation_prev; // 5C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_64;                 // 64
    uint8 reserved68[0x6];  // 68
    sint16 value_6E;        // 6E
    sint32 value_70;        // 70
    sint32 value_74;        // 74
    sint32 value_78;        // 78
    uint8 reserved7C[0x28]; // 7C
    union
    {
        sint8 b[4];
        sint32 w[1];
    } u_A4;                  // A4
    uint8 reservedA8[0x4];   // A8
    STCOM_SVECTOR vec_AC;    // AC
    sint32 value_B4;         // B4
    uint8 reservedB8[0x4];   // B8
    sint32 value_BC;         // BC
    sint32 value_C0;         // C0
    sint32 value_C4;         // C4
    sint32 value_C8;         // C8
    uint16 value_CC;         // CC
    sint16 value_CE;         // CE
    uint16 value_D0;         // D0
    uint16 value_D2;         // D2
    sint16 value_D4;         // D4
    uint8 reservedD6[0x2];   // D6
    sint32 value_D8;         // D8
    uint8 reservedDC[0x67];  // DC
    uint8 value_143;         // 143
    uint8 reserved144[0x3];  // 144
    uint8 value_147;         // 147
    uint8 reserved148[0x10]; // 148
    sint32 value_158;        // 158
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_15C;                  // 15C
    uint8 reserved160[0x20];  // 160
    sint16 value_180;         // 180
    sint16 value_182;         // 182
    sint16 value_184;         // 184
    uint8 reserved186[0x90];  // 186
    sint16 value_216;         // 216
    uint8 reserved218[0x6];   // 218
    sint16 value_21E;         // 21E
    uint8 reserved220[0x130]; // 220
    sint32 value_350;         // 350
    uint8 reserved354[0xC];   // 354
    uint8 value_360;          // 360
    uint8 reserved361[0x181]; // 361
    sint16 value_4E2;         // 4E2
    uint8 reserved4E4[0xC0];  // 4E4
};

extern STAGE_SLOT_FUNC *D_8010BC98[];
extern STAGE_SLOT_FUNC *D_8010BDF0[];
extern STAGE_SLOT_FUNC D_8010BE2C[];
extern STAGE_SLOT_FUNC D_8010BEC4[];
extern STAGE_SLOT_FUNC D_8010BF1C[];
extern STAGE_SLOT_FUNC D_8010BF30[];
extern uint8 D_8010C7D8[];
extern uint8 D_8010C7E0[][8];
extern STAGE_ROOM2_FUNC *D_8010C3FC[];
extern STAGE_ROOM2_FUNC D_8010C840[];
extern STAGE_ROOM2_FUNC D_8010CF54[];
extern sint8 *D_8010D570[]; // mouth scripts (func_8010283C)
extern sint8 *D_8010D5A8[]; // eye scripts (func_80102864)
extern sint8 *D_8010D714[]; // mouth scripts (func_80103690)
extern sint8 *D_8010D748[]; // eye scripts (func_801036B8)
extern sint8 *D_8010D7B8[]; // mouth scripts (func_80103C90)
extern STAGE_PART_FUNC D_8010E490[];
extern uint8 D_8010E4C0[];
extern STAGE_OBJ_FUNC D_8010E4D4[];
extern STAGE_OBJ_FUNC D_8011244C[];
extern uint8 D_80112470[];
extern STAGE_OBJ50_FUNC D_80112458[]; // by type
extern STAGE_OBJ_FUNC D_80112464[];
extern STAGE_OBJ50_FUNC D_8011248C[]; // by routine_0
extern uint8 D_8011249C[];
extern STAGE_OBJ_FUNC D_801124CC[];
extern STAGE_OBJ_FUNC D_801124D8[];
extern STAGE_OBJ_FUNC D_801124E4[];
extern ST0D_TALK_FUNC D_8010D440[];
extern ST0D_GRID6_FUNC D_8010E4A0[];
extern ST0D_CELL_FUNC D_8010E4B4[];
extern uint16 D_8011247C[]; // lid angles
extern uint8 D_8010C7A0;
extern uint8 D_8010C7B0;
extern uint8 D_8010C7C0;
extern uint8 D_8010C7D0;
extern uint8 D_8010C770;
extern uint8 D_8010C798;
extern uint8 D_8010C7A8;
extern uint8 D_8010C7C8;
extern uint8 D_8010C7B8;
extern uint8 D_8010C778;
extern uint8 D_8010C790;
extern ST0D_10C_FUNC D_8010DBCC[];
extern ST0D_TALK_FUNC D_8010D5E0[];
extern STAGE_OBJ_FUNC D_801124C0[];
extern uint8 D_8010C888[];
extern uint8 D_8010CF74[];
extern uint8 D_8010C788[];
extern sint16 D_800BBCF8[];
extern uint16 D_800C0C26;
// Player_work declared as a work slot (not a cast view): GCC relates its field addresses through one
// base register (func_80104444).
extern STAGE_OBJ Player_work_obj __asm__("Player_work");
extern uint8 D_8010C874[];
extern uint8 D_8010C89C[];
extern ST0D_CAMERA D_800C3558;
extern uint8 D_8010C780[];
extern uint8 D_8010DC08[];
extern uint8 D_80100004[];
extern const STCOM_FIXED_VECTOR D_801000F0; // a model scale
extern const STCOM_FIXED_VECTOR D_80100118; // func_801050E8's scale
extern void *D_8010BFA4[];
extern void *D_8010C0D4[];
extern void *D_8010C1DC[];
extern uint8 D_8010C1F4[][0x28];
extern uint8 D_8010C2E4[][8];
extern sint32 D_8010C2F4[];
extern uint8 D_8010C84C[];
extern uint8 D_8010C8B0[];
extern STAGE_ROOM2_FUNC D_8010C8FC[];
extern uint8 D_8010C90C[];
extern STAGE_ROOM2_FUNC D_8010CEEC[];
extern uint8 D_8010CF60[];
extern uint8 D_8010CF88[];
extern STAGE_SCRIPT_ENTRY D_8010CFB0[];
extern STAGE_SCRIPT_ENTRY D_8010CFD8[];
extern uint8 D_8010D000[];
extern STAGE_ROOM2_FUNC D_8010D04C[];
extern uint8 D_8010D05C[];
extern STAGE_ROOM2_FUNC D_8010D258[];
extern uint8 D_8010D278[];
extern uint8 D_8010D2C4[];
extern STAGE_ROOM2_FUNC D_8010D430[];
extern ST0D_TALK_FUNC D_8010D5D8[];
extern ST0D_PATH_STEP D_8010DB90[];
extern ST0D_PATH_STEP D_8010D7D0[];
extern ST0D_PATH_STEP D_8010DA34[];
extern STCOM_SVECTOR D_8010DC00;
extern uint16 D_8010DB98;
extern ST0D_BOB_FUNC D_8010DBE0[];
extern ST0D_LIFT_FUNC D_8010DBE8[];
extern ST0D_BOB_FUNC D_8010DBF0[];
extern ST0D_BOB_FUNC D_8010DBF8[];
extern sint32 D_8010DC14[];         // messages (0x7FFFFFFF: none)
extern sint32 D_8010DC28[];         // scene flags to set
extern ST0D_CAM_SHOT *D_8010DC60[]; // (0x7FFFFFFF: none)
extern sint32 D_8010DC74[];         // scene flags to test
extern uint8 D_8010E41C[];
extern sint32 D_8010E428[];
extern sint32 D_8010E43C[];
extern ST0D_CAM_SHOT *D_8010E468[];
extern sint32 D_8010E47C[];
extern uint32 D_801124A8[]; // flame distances and heights by timer_D (func_8010B08C)
extern uint32 D_801124B0[];
extern uint32 D_801124B8[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];
extern sint32 D_800BC740; // the camera's position and target (ROCK_NEO's scene.h)
extern sint32 D_800BC744;
extern sint32 D_800BC748;
extern sint32 D_800BC770;
extern sint32 D_800BC774;
extern sint32 D_800BC778;

void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void func_80100358(void);
void func_80100DB4(STAGE_ROOM *wp);
void func_80101608(STAGE_ROOM *wp);
void func_8010283C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80102864(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80103690(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801036B8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80103C90(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80109BB0(STAGE_OBJ *wp);
void func_80109FD4(STAGE_OBJ *wp);
void func_80031A4C(void *wp);
void func_8010A190(STAGE_OBJ50 *wp);
void func_8010A20C(STAGE_OBJ *wp);
uint8 func_8010A9CC(STAGE_OBJ50 *wp);
void func_8010A670(STAGE_OBJ50 *wp);
void func_8010AC80(STAGE_OBJ50 *wp);
void func_8010AEAC(STAGE_OBJ50 *wp);
void func_8010B010(STAGE_OBJ *wp);
void func_8010B27C(STAGE_OBJ *wp);
void func_8010B508(STAGE_OBJ *wp);
void func_8010B97C(STAGE_OBJ *wp);
void func_80102068(STAGE_OBJ *wp);
void func_80108D10(ST0D_GRID6 *grid, uint8 row, uint8 col);
void func_8010AA54(ST0D_STCOM21_WORK *wp);
uint8 func_8010AF28(ST0D_STCOM21_WORK *wp);
void func_80101268(STAGE_OBJ *wp);
void func_8010146C(STAGE_ROOM *wp);
void func_801006EC(void);
void func_8010129C(STAGE_OBJ *wp);
void func_801014A8(STAGE_ROOM *wp);
void func_80100890(STAGE_ROOM *wp);
void func_80100940(STAGE_ROOM *wp);
void func_801009F0(STAGE_ROOM *wp);
void func_80100AA0(STAGE_ROOM *wp);
void func_80100B50(STAGE_ROOM *wp);
void func_801014F0(STAGE_ROOM *wp);
void func_801003F8(STAGE_OBJ *wp);
void func_80100834(STAGE_OBJ *wp);
void func_801004D8(STAGE_OBJ *wp);
void func_801008E4(STAGE_OBJ *wp);
void func_80100994(STAGE_OBJ *wp);
void func_80100AF4(STAGE_OBJ *wp);
void func_80100A44(STAGE_OBJ *wp);
void func_80100D54(uint8 arg0, uint8 arg1);
void func_80101E04(uint8 arg0);
void func_80100454(STAGE_ROOM *wp);
void func_80100534(STAGE_ROOM *wp);
void func_80100668(STAGE_ROOM *wp);
void func_801007B0(STAGE_ROOM *wp);
void func_80101118(STAGE_ROOM *wp);
void func_8010134C(STAGE_ROOM *wp);
STAGE_OBJ *func_80036294(sint32 id);
void func_80100BA4(sint32 arg);
void Scene_obj_list_open(uint8 *script);
void func_80101548(sint32 mode, uint8 arg);
void func_80104BE0(ST0D_ACTOR *wp, uint16 *bob);
void func_8010964C(ST0D_BOBBER *wp, ST0D_BOB *bob);
void func_80109714(ST0D_BOBBER *wp, ST0D_BOB *bob);
sint32 Obj_ceiling_height_get(void *wp);
void func_8010B29C(ST0D_FLAMES *wp, sint16 angle, sint8 frame);
void func_8010B6E8(ST0D_FLAMES *wp, sint32 angle, sint8 frame);
void func_8010BB48(ST0D_FLAMES *wp, sint16 angle, sint8 frame);
void func_80104800(ST0D_LIFT *wp, ST0D_PATH *path);
void func_8010494C(ST0D_LIFT *wp, ST0D_PATH *path);
ST0D_GRID_OBJ *func_80108468(STAGE_OBJ *owner, uint8 rows, STCOM_SVECTOR *origin);
sint32 Distance_xz(sint16 *a, sint16 *b);
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);
void Sce_event_timer_clear(void);
void func_80107EF8(ST0D_VILLAGER *wp, ST0D_TALK *talk);
void func_80108040(ST0D_VILLAGER *wp, ST0D_TALK *talk);
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
void func_8010390C(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face);
void func_80103CB8(STAGE_OBJ *wp, STAGE_FACE *face);
void func_8010288C(STAGE_OBJ *wp, STAGE_FACE *face);
void func_801036E0(STAGE_OBJ *wp, STAGE_FACE *face);

sint32 Map_cell_get(STCOM_SVECTOR *pos);
uint32 Stage_idx_model_set(sint32 idx, uint32 key);

#endif
