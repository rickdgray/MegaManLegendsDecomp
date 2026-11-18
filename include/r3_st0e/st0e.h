#ifndef ST0E_H
#define ST0E_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom16.h"
#include "stage_common/stcom23.h"
#include "stage_common/stcom18.h"

// An absolute value; GCC 2.7 reserves an 8-byte stack temporary for each use (func_801081AC).
#define ST0E_ABS(x) ((x) >= 0 ? (x) : -(x))

// The hit block at +0x368 of ST0E_ACTOR (+0x20 of its control block; registered through
// func_800341BC) and three timers.
typedef struct
{
    uint32 flags_0;        // 00
    sint32 value_4;        // 04
    uint32 value_8;        // 08: ORed into the hit flags
    uint16 value_C;        // 0C
    uint16 timer_E;        // 0E
    uint16 timer_10;       // 10
    uint8 reserved12[0xE]; // 12
} ST0E_ACTOR_HIT;

// From r3_st04 (ST04_ACTOR_CTL).
// The control block of ST0E_ACTOR at +0x348 (its routines reach the hit block through it).
typedef struct
{
    uint16 flags_0;       // 00
    uint16 value_2;       // 02
    sint16 timer_4;       // 04
    sint16 value_6;       // 06
    sint16 value_8;       // 08
    sint16 timer_A;       // 0A
    uint16 value_C;       // 0C
    uint16 timer_E;       // 0E
    sint32 value_10;      // 10: nonzero when it was hit (func_80105228)
    uint32 hit_14;        // 14: damage in the low 24 bits, kind bits above
    STCOM_SVECTOR pos_18; // 18: a copy of the position for the hit test
    ST0E_ACTOR_HIT hit;   // 20
} ST0E_ACTOR_CTL;

// From r3_st04 (ST04_ACTOR).
// A 0x3C0-byte work slot as this stage's villagers use it: STAGE_ACTOR with the blocks at +0x348
// and +0x368 named.
typedef struct
{
    sint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02
    uint8 variant_3;                        // 03
    uint8 reserved04[2];                    // 04
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
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
    sint16 value_4C;                        // 4C
    sint16 value_4E;                        // 4E
    sint16 value_50;                        // 50
    uint8 reserved52[2];                    // 52
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[4];                    // 70
    sint8 value_74;                         // 74
    uint8 reserved75[3];                    // 75
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80
    uint8 reserved84[0x20];                 // 84
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
    STCOM_SVECTOR value_188;                // 188: where its pieces fly from (func_801021D4)
    uint8 reserved190[0x1B8];               // 190
    ST0E_ACTOR_CTL ctl;                     // 348: and the hit block at 368
    uint8 reserved388[0x38];                // 388
} ST0E_ACTOR;

typedef void (*ST0E_ACTOR_FUNC)(ST0E_ACTOR *wp);
// Four bytes per model part from +0x100 (STAGE_PART), with the last byte signed.
typedef struct
{
    uint8 value_0;
    uint8 reserved1[2];
    sint8 value_3;
} ST0E_PART;

// A 0x5A4-byte work slot of a villager who talks, with the face at +0x500 (STAGE_OBJ keeps it at
// +0x4E0).
typedef struct
{
    sint8 flags_0;            // 00
    uint8 value_1;            // 01
    uint8 kind_2;             // 02
    uint8 variant_3;          // 03
    uint8 reserved04[4];      // 04
    uint8 routine_0;          // 08
    uint8 routine_1;          // 09
    uint8 routine_2;          // 0A
    uint8 routine_3;          // 0B
    sint8 timer_C;            // 0C
    sint8 value_D;            // 0D
    uint8 reserved0E[0x46];   // 0E
    STCOM_SVECTOR rotation;   // 54
    uint8 reserved5C[0x2C];   // 5C
    void *model_88;           // 88
    uint8 reserved8C[0x74];   // 8C
    ST0E_PART part_100[20];   // 100: value_3 is -1 on hidden parts
    uint8 reserved150[8];     // 150
    STCOM_SVECTOR_W scale;    // 158
    uint8 reserved160[0x26];  // 160
    STAGE_PAL pal[24];        // 186
    uint8 reserved246[0x2BA]; // 246
    STAGE_FACE16 face_500;    // 500
    uint8 reserved514[0x90];  // 514
} ST0E_TALKER;

typedef void (*ST0E_TALKER_FUNC)(ST0E_TALKER *wp);
// A matrix whose translation holds a rotation at +0x14 (ST0E_LEVER).
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
    struct
    {
        sint16 m[3][3];
        sint16 pad;
        STCOM_SVECTOR rot; // 14
        uint16 flag_1C;    // 1C: a scene flag (ST0E_LEVER)
    } f;
} ST0E_ROT_MATRIX;

// A 0x50-byte slot (func_80031734) like stcom22's lever, with its rotation at +0x2C.
typedef struct ST0E_LEVER ST0E_LEVER;
typedef void (*ST0E_LEVER_FUNC)(ST0E_LEVER *wp);

struct ST0E_LEVER
{
    uint8 flags_0;          // 00
    uint8 reserved01[2];    // 01
    uint8 variant_3;        // 03
    uint8 reserved04;       // 04
    uint8 value_5;          // 05: picks the scene flag
    uint8 reserved06[2];    // 06
    uint8 routine_0;        // 08
    uint8 routine_1;        // 09
    uint8 routine_2;        // 0A
    uint8 routine_3;        // 0B
    uint8 reserved0C[0xC];  // 0C
    ST0E_ROT_MATRIX matrix; // 18
    uint8 reserved38[8];    // 38
    uint32 color_40;        // 40
    uint8 reserved44[0xC];  // 44
};

// Eight bytes of texture coordinates of a model face (func_8002D22C, func_8002D27C).
typedef struct
{
    uint8 b[8];
} ST0E_UV8;

// A model's part list record (8 bytes; +2 is saved by func_8010BFB4).
typedef struct
{
    uint8 reserved0[2]; // 0
    uint16 value_2;     // 2
    uint8 reserved4[4]; // 4
} ST0E_PART_REC;

typedef struct
{
    uint8 reserved00[0x24];
    ST0E_PART_REC *recs_24; // 24
} ST0E_MODEL_PARTS;

// A model as func_8010BFB4 reaches it.
typedef struct
{
    uint8 reserved00[0x70];
    ST0E_MODEL_PARTS *parts_70; // 70
} ST0E_MODEL;

// A 0x50-byte slot of a panel whose face colors are kept per variant (func_8010BFB4).
typedef struct
{
    uint8 flags_0;        // 00
    uint8 reserved01[2];  // 01
    uint8 variant_3;      // 03
    uint8 reserved04[4];  // 04
    uint8 routine_0;      // 08
    uint8 routine_1;      // 09
    sint8 value_A;        // 0A
    uint8 routine_3;      // 0B
    uint32 cell_C;        // 0C: the cell's value word
    uint8 reserved10[4];  // 10
    ST0E_MODEL *model_14; // 14
    union
    {
        STCOM_MATRIX m;
        struct
        {
            uint8 reserved00[0x14];
            uint32 key_14;   // 2C: the model (func_8003AC24)
            sint32 value_18; // 30
            sint32 lit_1C;   // 34: nonzero once all three flags lit the panel
        } f;
    } matrix_18;          // 18
    STCOM_SVECTOR pos_38; // 38
    uint32 color_40;      // 40
    sint32 cell_44;       // 44: index into the room's cell table
    uint8 reserved48[8];  // 48
} ST0E_PANEL;

// A map rectangle: a corner (cells) and its size.
typedef struct
{
    sint8 x; // 0
    sint8 z; // 1
    uint8 w; // 2
    uint8 h; // 3
} ST0E_BOX;

typedef sint32 (*ST0E_TEST_FUNC)(STAGE_OBJ *wp);

// A hit block registered through func_800341BC: where it is tested and the flags of what hit it.
typedef struct
{
    STCOM_SVECTOR pos_0; // 00
    uint32 flags_8;      // 08: the hit's damage and kind bits
    uint8 reserved0C[4]; // 0C
} ST0E_HIT;

// The block at +0xCC of ST0E_VIEW as func_80107DE0 reaches it: its hit block first.
typedef struct
{
    ST0E_HIT hit;         // 00
    uint8 data_10[4];     // 10
    STCOM_SVECTOR vec_14; // 14
    sint32 value_1C;      // 1C
    sint32 value_20;      // 20
    uint16 value_24;      // 24
    uint8 reserved26[2];  // 26
    sint16 value_28;      // 28
    uint8 reserved2A[4];  // 2A
    uint8 value_2E;       // 2E
    uint8 value_2F;       // 2F: nonzero while it can be hit
} ST0E_VIEW_CTL;

// The hit block at +0xCC of ST0E_ITEM (registered through func_800341BC).
typedef struct
{
    STCOM_SVECTOR pos_0; // 00
    uint32 flags_8;      // 08: set when it was hit
    uint8 reserved0C[4]; // 0C
    uint8 msg_10;        // 10: the message it shows
    uint8 reserved11[3]; // 11
} ST0E_ITEM_HIT;

// A 0x10C-byte slot drawn as a sprite that jumps out and waits to be hit (func_80108D30,
// func_80108E00).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 value_1;                     // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[4];               // 04
    uint8 routine_0;                   // 08
    uint8 routine_1;                   // 09
    uint8 routine_2;                   // 0A
    uint8 routine_3;                   // 0B
    sint8 flag_C;                      // 0C: which scene flag the hit sets
    uint8 reserved0D[7];               // 0D
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x18];            // 2C
    union
    {
        sint16 h[2];
        sint32 w;
    } u_44; // 44: speed x and y
    union
    {
        sint16 h[2];
        sint32 w;
    } u_48; // 48: speed z
    union
    {
        sint16 h[2];
        sint32 w;
    } u_4C;                 // 4C: [1] gravity
    uint8 reserved50[4];    // 50
    STCOM_SVECTOR rotation; // 54
    uint8 reserved5C[8];    // 5C
    sint32 value_64;        // 64
    uint8 reserved68[6];    // 68
    sint16 value_6E;        // 6E
    sint32 value_70;        // 70
    sint32 value_74;        // 74
    sint32 value_78;        // 78
    uint8 reserved7C[0xC];  // 7C
    uint32 code_88;         // 88: the sprite (as the SHL modules' SHL_SPRITE)
    uint32 color_8C;        // 8C
    sint16 x_90;            // 90
    sint16 y_92;            // 92
    sint16 z_94;            // 94
    uint8 scale_96;         // 96
    uint8 scale_97;         // 97
    uint16 size_98;         // 98
    uint8 reserved9A[0x32]; // 9A
    ST0E_ITEM_HIT hit;      // CC
    uint8 reservedE0[0x2C]; // E0
} ST0E_ITEM;

// A 0x10C-byte work slot with a model matrix at +0x8C.
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
    sint8 byte_C;                           // 0C
    sint8 byte_D;                           // 0D
    sint8 byte_E;                           // 0E
    sint8 byte_F;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    sint32 value_44;                        // 44
    sint32 value_48;                        // 48
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[8];                    // 68
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    uint8 reserved78[0x14];                 // 78
    STAGE_MATRIX matrix_8C;                 // 8C
    STCOM_SVECTOR position_AC;              // AC: the model's position
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x1C];                 // B8
    sint32 value_D4;                        // D4
    uint8 reservedD8[0x34];                 // D8
} ST0E_10C;

typedef void (*ST0E_10C_FUNC)(ST0E_10C *wp);

// The block at +0xBC of ST0E_PROP (STCOM31_CTL's layout).
typedef struct
{
    uint16 flags_0;        // BC: 1 ends the state, 2 once it has landed
    uint16 random_2;       // BE: rand() each frame
    sint16 timer_4;        // C0
    uint16 reserved6;      // C2
    sint32 hit_8;          // C4: func_800341BC's result
    uint8 reservedC[0x44]; // C8
} ST0E_PROP_CTL;

// A 0x10C-byte slot (func_80031518) of a prop drawn as a model, laid out as stcom31's vehicle
// (STCOM31_WORK); STAGE_PROP describes the same slot with the velocity as words.
typedef struct ST0E_PROP ST0E_PROP;
typedef void (*ST0E_PROP_FUNC)(ST0E_PROP *wp);

struct ST0E_PROP
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
    uint8 param_C;                          // 0C: heading / 0x200
    uint8 reserved0D[3];                    // 0D
    sint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    union
    {
        sint16 h[2];
        sint32 w;
    } spin_64;              // 64: [1] a turn speed
    uint8 reserved68[6];    // 68
    sint16 value_6E;        // 6E
    sint32 value_70;        // 70
    sint32 value_74;        // 74
    void *data_78;          // 78
    uint8 reserved7C[0x10]; // 7C
    STCOM_MATRIX matrix;    // 8C
    STCOM_SVECTOR pos_AC;   // AC
    uint32 color_B4;        // B4
    uint8 reservedB8[4];    // B8
    ST0E_PROP_CTL ctl;      // BC
};

// A 0x48-byte effect slot drawn as a sprite packet (func_8010D7EC): a glow that drifts and fades.
// The motion every spark record starts with (func_8010D9F8): speed, rise, gravity, size.
typedef struct
{
    sint16 speed_0; // 0
    sint16 vy_2;    // 2
    sint16 ay_4;    // 4
    uint16 size_6;  // 6
} ST0E_SPARK_HEAD;

// A textured spark record (D_80110BDC).
typedef struct
{
    ST0E_SPARK_HEAD head; // 00
    uint32 uv_8;          // 08
    uint32 uv_C;          // 0C
    uint32 uv_10;         // 10
} ST0E_SPARK_TEX;

// A flat spark record (D_80110B3C).
typedef struct
{
    ST0E_SPARK_HEAD head; // 0
    uint32 mode_8;        // 8
    uint8 u_C;            // C
    uint8 v_D;            // D
    uint8 reservedE[2];   // E
} ST0E_SPARK_FLAT;

// A spark record of either kind.
typedef union
{
    ST0E_SPARK_HEAD head;
    ST0E_SPARK_TEX tex;
    ST0E_SPARK_FLAT flat;
} ST0E_SPARK;

typedef struct ST0E_GLOW ST0E_GLOW;
typedef void (*ST0E_GLOW_FUNC)(ST0E_GLOW *wp);

struct ST0E_GLOW
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
// A view of the work slots r3_st0e's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST0E_VIEW ST0E_VIEW;

typedef void (*ST0E_VIEW_FUNC)(ST0E_VIEW *wp);
struct ST0E_VIEW
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
    } u_48; // 48
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_4C;                      // 4C
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
    uint8 reserved84[0x4];  // 84
    sint32 value_88;        // 88
    STCOM_MATRIX matrix_8C; // 8C
    STCOM_SVECTOR vec_AC;   // AC
    sint32 value_B4;        // B4
    uint8 reservedB8[0x4];  // B8
    uint16 value_BC;        // BC
    sint16 value_BE;        // BE
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_C0;                  // C0
    uint8 reservedC4[0x8];   // C4
    ST0E_HIT hit_CC;         // CC
    uint8 data_DC[0x4];      // DC: func_80031F84's second argument (func_80107DE0)
    STCOM_SVECTOR vec_E0;    // E0
    sint32 value_E8;         // E8
    sint32 value_EC;         // EC
    uint16 value_F0;         // F0
    uint8 reservedF2[0x2];   // F2
    sint16 value_F4;         // F4
    uint8 reservedF6[0x4];   // F6
    uint8 value_FA;          // FA
    uint8 value_FB;          // FB
    uint8 reservedFC[0xF];   // FC
    uint8 value_10B;         // 10B
    uint8 reserved10C[0xB];  // 10C
    uint8 value_117;         // 117
    uint8 reserved118[0x2B]; // 118
    uint8 value_143;         // 143
    uint8 reserved144[0x3];  // 144
    uint8 value_147;         // 147
    uint8 reserved148[0x3];  // 148
    uint8 value_14B;         // 14B
    uint8 reserved14C[0x3];  // 14C
    uint8 value_14F;         // 14F
    uint8 reserved150[0x8];  // 150
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
    uint8 reserved160[0x26];  // 160
    sint16 value_186;         // 186
    STCOM_SVECTOR vec_188;    // 188
    uint8 reserved190[0x9E];  // 190
    uint16 value_22E;         // 22E
    uint8 reserved230[0x128]; // 230
    sint32 value_358;         // 358
    sint32 value_35C;         // 35C
    uint8 reserved360[0x8];   // 360
    sint32 value_368;         // 368
    sint32 value_36C;         // 36C
    sint32 value_370;         // 370
    uint8 reserved374[0x4C];  // 374
};

extern STAGE_SLOT_FUNC *D_8010F508[];
extern STAGE_SLOT_FUNC *D_8010F608[];
extern STAGE_SLOT_FUNC D_8010F624[];
extern STAGE_SLOT_FUNC D_8010F6E4[];
extern STAGE_SLOT_FUNC D_8010F748[];
extern STAGE_SLOT_FUNC D_8010F7D0[];
extern STAGE_ROOM2_FUNC *D_8010FF04[];
extern STAGE_ROOM2_FUNC D_8010FF44[];
extern sint16 *D_8011024C[];
extern sint16 *D_80110270[];
extern STAGE_OBJ_FUNC D_80110398[];
extern STAGE_OBJ_FUNC D_801104D4[];
extern STAGE_OBJ_FUNC D_80110508[];
extern STAGE_OBJ_FUNC D_801105D4[];
extern STAGE_OBJ_FUNC D_801106A0[];
extern STAGE_OBJ_FUNC D_801106B0[];
extern STAGE_OBJ_FUNC D_801106C4[];
extern STAGE_OBJ_FUNC D_80110C60[];
extern STAGE_OBJ_FUNC D_80110C6C[];
extern uint16 D_80110504;
extern STAGE_OBJ_FUNC D_801104F8[];
extern ST0E_TALKER_FUNC D_80110150[];
extern STCOM_FIXED_VECTOR D_801105C4;
extern STCOM_EFFECT *D_80110D58[];
extern uint16 D_801103C4[];
extern ST0E_10C_FUNC D_801104EC[];
extern ST0E_10C_FUNC D_8011052C[];
extern sint32 D_8010F294[];
extern void *D_8010FC8C[];
extern void *D_8010FE18[];
extern uint8 D_8010FE24[][0x28];
extern uint8 D_8010FE9C[][8];
extern sint32 D_8010FED4[];
extern STAGE_SCRIPT_ENTRY D_8010FF50[];
extern uint8 D_8010FF78[];
extern uint8 D_8010FFC8[];
extern STAGE_ROOM2_FUNC D_80110118[];
extern STAGE_ROOM2_FUNC D_80110128[];
extern uint8 D_801102C8[];
extern uint8 D_801102D4[];
extern STAGE_SLOT_FUNC D_801102E0[];
extern uint8 D_801103A4[];
extern STAGE_SLOT_FUNC D_801103B0[];
extern ST0E_PROP_FUNC D_801103CC[];
extern ST0E_PROP_FUNC D_801103D8[];
extern sint16 D_801103F0[];
extern STAGE_SLOT_FUNC D_801104A4[];
extern ST0E_10C_FUNC D_801104B0[];
extern STAGE_SLOT_FUNC D_801104E0[];
extern uint16 D_80110514[];
extern uint8 D_80110524[];
extern uint32 D_80110698[]; // the panel model key (func_8010BFB4)
extern ST0E_LEVER_FUNC D_801106BC[];
extern ST0E_SPARK_FLAT D_80110B3C[];
extern ST0E_SPARK_TEX D_80110BDC[];
extern ST0E_GLOW_FUNC D_80110BF0[];
extern ST0E_TEST_FUNC D_80110C78[]; // whether each box may talk (func_8010E8A0)
extern ST0E_BOX D_80110C90[];
extern sint32 D_80110CA8[];
extern uint8 D_80110CC0[];
extern ST0E_UV8 D_80110CF4[][16]; // face coordinates by variant (func_8010BFB4)
extern ST0E_UV8 D_80110D74[][16]; // D_80110CF4[1]: by variant - 1 (func_8010C1C0)
extern ST0E_UV8 D_80110EF4[16];   // D_80110CF4[4]
extern uint16 D_80110F42[][25];
extern void *D_8015C008[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_80100474(void);
void func_801004A4(void);
void func_801004D4(void);
void func_80100504(void);
void func_80100534(void);
void func_80100564(STAGE_ROOM *wp);
void func_80101090(void *wp, STAGE_FACE16 *face, sint32 index);
void func_80104DBC(STAGE_OBJ *wp);
void func_80105B40(STAGE_OBJ *wp);
void func_80105D6C(uint8 *arg0);
void func_80105D80(uint8 *arg0);
void func_80105FA0(STAGE_OBJ *wp);
void func_80107B94(STAGE_OBJ *wp);
void func_80107C58(STAGE_OBJ *wp);
void func_80108084(STAGE_OBJ *wp);
void func_8010857C(STAGE_OBJ *wp);
void func_801085B4(STAGE_OBJ *wp);
void func_801085D4(STAGE_OBJ *wp);
void func_80108C94(STAGE_OBJ *wp);
void func_80109038(STAGE_OBJ *wp);
void func_80109AE8(STAGE_OBJ *wp);
void func_8010BC64(STAGE_OBJ *wp);
void func_8010BCA0(STAGE_OBJ *wp);
void func_8010BE04(STAGE_OBJ *wp);
void func_8010BF78(STAGE_OBJ *wp);
void func_8010C694(STAGE_OBJ *wp);
void func_8010D8AC(STAGE_OBJ *wp);
void func_8010D8E4(STAGE_OBJ *wp);
void func_8010D9D8(STAGE_OBJ *wp);
void func_8010E7BC(STAGE_OBJ *wp);
void func_8010E844(STAGE_OBJ *wp);
void func_8010E880(STAGE_OBJ *wp);
sint32 func_8010ED60(void);
void func_80100AC0(STAGE_ROOM *wp);
void func_8010576C(STAGE_OBJ *wp);
void func_80105798(STAGE_OBJ *wp);
void func_801057C4(STAGE_OBJ *wp);
void func_80108540(STAGE_OBJ *wp);
void func_8010BF34(STAGE_FX *wp);
void func_80100AE8(STAGE_ROOM *wp);
void func_801052EC(STAGE_OBJ *wp);
void func_801083EC(STAGE_OBJ *wp);
void func_80105414(ST0E_ACTOR *wp);
void func_80105490(ST0E_ACTOR *wp);
void func_801053AC(STAGE_OBJ *wp);
void func_80100CA8(STAGE_OBJ *wp);
void func_801010D8(STAGE_OBJ *wp, STAGE_FACE16 *face);
// func_800317AC is declared in stage_common/stage.h.
void func_8010571C(ST0E_ACTOR *wp);
void func_80031A4C(void *wp);
void func_80105228(ST0E_ACTOR *wp);
void func_801056B8(ST0E_ACTOR *wp);
void func_801021D4(ST0E_ACTOR *wp);
void func_80105738(ST0E_ACTOR *wp);
void func_80108610(ST0E_VIEW *wp);
void func_80102064(ST0E_VIEW *wp);
void func_801077E8(ST0E_VIEW *wp);
void func_80108A44(ST0E_VIEW *);
void func_80108AE4(ST0E_VIEW *);
void func_80108820(ST0E_VIEW *wp);
void func_80108980(ST0E_VIEW *wp);
#ifdef __wasm32__
void func_80047148(void *wp, STCOM_SVECTOR *pos);
#else
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
#endif

void func_80105AB0(ST0E_PROP *wp);

extern sint16 D_800BBCF8[]; // ROCK_NEO.EXE: a sine table
sint32 func_80048D08(sint32 a0, STCOM_SVECTOR *pos);
uint32 func_8003AC9C(sint32 idx, uint32 key);
void func_8010BD90(ST0E_LEVER *wp);
sint32 func_8003648C(void *track, void *wp);

void func_8010D9F8(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos);
void func_8010DC00(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos, sint32 from,
                   sint32 to);
void func_80050C2C(void *wp);
void func_80052528(void *wp);

// A ROCK_NEO record per 0x10C-slot kind (D_80098928).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;     // 08: life, in sixteenths
    uint8 reserved09; // 09
    uint8 value_A;    // 0A: its hit kind
} ST0E_KIND10C;

extern ST0E_KIND10C **D_80098928;

void func_8001E460(sint32 a0, sint32 a1, sint32 a2);

ST0E_UV8 *func_8002D22C(void *model, sint32 id);
void func_8002D27C(void *model, sint32 id, ST0E_UV8 *uv);
sint32 func_80048C60(STCOM_SVECTOR *pos);

#endif
