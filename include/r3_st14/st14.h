#ifndef ST14_H
#define ST14_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"

// Four bytes per model part from +0x100 (STAGE_PART), with the last byte signed.
typedef struct
{
    uint8 value_0;
    uint8 reserved1[2];
    sint8 value_3;
} ST14_PART;

// From r3_st0e (ST0E_TALKER).
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
    ST14_PART part_100[20];   // 100: value_3 is -1 on hidden parts
    uint8 reserved150[8];     // 150
    STCOM_SVECTOR_W scale;    // 158
    uint8 reserved160[0x26];  // 160
    STAGE_PAL pal[24];        // 186
    uint8 reserved246[0x2BA]; // 246
    STAGE_FACE16 face_500;    // 500
    uint8 reserved514[0x90];  // 514
} ST14_TALKER;

// From r3_st0e (ST0E_TALKER_FUNC).
typedef void (*ST14_TALKER_FUNC)(ST14_TALKER *wp);

// A hit record: flags, then four bytes.
typedef struct
{
    sint32 flags;
    sint32 value_4;
} ST14_HIT;

// The villager's own fields from +0x4E0 (its routines keep a pointer to them).
typedef struct
{
    sint32 flags_0;         // 00: 1 hit a wall, 2 on the ground, 4 at a ledge
    STCOM_SVECTOR target_4; // 04: where it heads
    STCOM_SVECTOR pos_C[6]; // 0C: the hit boxes' centers
    ST14_HIT hit_3C[6];     // 3C
    sint32 value_6C[6];     // 6C
    uint32 value_84;        // 84
    uint16 timer_88;        // 88
    uint16 count_8A;        // 8A
    uint16 value_8C;        // 8C
    sint16 value_8E;        // 8E
    sint16 value_90;        // 90
    sint16 value_92;        // 92
    STCOM_EFFECT *fx_94;    // 94
    uint8 reserved98[0x2C]; // 98
} ST14_VILLAGER_EXT;

// A 0x5A4-byte work slot of a villager (the fields this stage's routines use).
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
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[4];                    // 70
    sint8 value_74;                         // 74
    sint8 value_75;                         // 75: value_74 before this frame
    uint8 reserved76[2];                    // 76
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80
    uint8 reserved84[0x20];                 // 84
    uint8 value_A4;                         // A4
    uint8 reservedA5[2];                    // A5
    sint8 value_A7;                         // A7
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR scale;                    // 158
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joint_180[24];            // 180: joint positions
    uint8 reserved240[0xEC];                // 240
    uint16 flags_32C;                       // 32C
    uint8 reserved32E[0x1B2];               // 32E
    ST14_VILLAGER_EXT ext;                  // 4E0
} ST14_VILLAGER;

typedef void (*ST14_VILLAGER_FUNC)(ST14_VILLAGER *wp);

// A map rectangle (a corner and its size, in cells) and the room it is in (-1: any).
typedef struct
{
    sint8 x;    // 0
    sint8 z;    // 1
    uint8 w;    // 2
    uint8 h;    // 3
    sint8 room; // 4
} ST14_BOX;

// A 0x10C-byte slot (func_80031518) with a rotation at +0x64 (the pieces func_8010D8FC spawns).
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
    STCOM_SVECTOR rotation;            // 64
    uint8 reserved6C[0xA0];            // 6C
} ST14_PIECE;

// A record of ROCK_NEO's table at D_8009884C, by kind (ST13_KIND).
typedef struct
{
    uint8 reserved0[8]; // 0
    uint8 life_8;       // 8: times 16
    uint8 value_9;      // 9
    uint8 value_A;      // A
    uint8 value_B;      // B
} ST14_KIND;

// The 0x98 bytes from +0x328 of this stage's actor (ST14_ACTOR), offsets relative to +0x328.
typedef struct
{
    uint8 reserved0[4]; // 328
    uint16 flags_4;     // 32C
    uint16 random_6;    // 32E: a new random number every frame
    union
    {
        sint16 h[2];
        sint32 w;
    } u_8; // 330
    union
    {
        struct
        {
            uint16 kind_C;  // 334: or'd into the hit's kind bits
            sint16 timer_E; // 336
        } h;
        sint32 w;
    } u_C;                // 334
    STCOM_SVECTOR pos_10; // 338
    sint32 hit_18;        // 340: damage in the low 24 bits, kind bits above
    sint32 value_1C;      // 344
    uint8 reserved20[8];  // 348
    union
    {
        uint8 track[0x10]; // func_80036478
        sint32 w[4];
    } u_28;                 // 350
    sint16 value_38;        // 360
    sint16 value_3A;        // 362
    sint16 value_3C;        // 364
    sint16 value_3E;        // 366
    STCOM_SVECTOR vec_40;   // 368
    STCOM_SVECTOR vec_48;   // 370
    uint8 reserved50[0x48]; // 378
} ST14_ACTOR_CTL;

// A 0x3C0-byte actor slot of this stage (STAGE_OBJ's fields, then ST14_ACTOR_CTL at +0x328).
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
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR_W accel;                  // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[0x8];                  // 70
    uint8 *data_78;                         // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80
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
    uint8 reserved2A8[0x80];                // 2A8
    ST14_ACTOR_CTL ctl;                     // 328
} ST14_ACTOR;

typedef void (*ST14_ACTOR_FUNC)(ST14_ACTOR *wp);

// A ROCK_NEO record per object kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8; // 08: times 16
    uint8 value_9;
    uint8 value_A; // 0A
    uint8 value_B;
    uint8 reserved0C[3];
    uint8 value_F; // 0F
} ST14_KIND2;

// Player_work with its vectors at +0xC4 and +0x3A8.
typedef struct
{
    uint8 reserved00[0xC4];   // 00
    STCOM_SVECTOR value_C4;   // C4
    uint8 reservedCC[0x2DC];  // CC
    STCOM_SVECTOR value_3A8;  // 3A8
    uint8 reserved3B0[0x3D4]; // 3B0
} ST14_PL_VIEW;

#define ST14_PL (*(ST14_PL_VIEW *)&Player_work)

// A test on an event slot (D_80116208): nonzero when it holds.
typedef sint32 (*ST14_TEST_FUNC)(STAGE_OBJ *wp);

// A splash's growth: a speed added to a size each frame, itself changed by an acceleration.
typedef struct
{
    sint16 speed_0; // 2C
    sint16 accel_2; // 2E
    sint16 size_4;  // 30
    sint16 speed_6; // 32
    sint16 accel_8; // 34
    sint16 size_A;  // 36
} ST14_GROW;

// A 0x48-byte effect slot drawn as a model (func_801053B4); its growth sits in the matrix's
// translation, which RotMatrixYXZ and ScaleMatrix leave alone.
typedef struct ST14_SPLASH ST14_SPLASH;

typedef void (*ST14_SPLASH_FUNC)(ST14_SPLASH *wp);

struct ST14_SPLASH
{
    uint8 flags_0;         // 00
    uint8 reserved01;      // 01
    uint8 kind_2;          // 02
    uint8 variant_3;       // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 alpha_A;         // 0A
    uint8 timer_B;         // 0B
    uint8 value_C;         // 0C: bit 0 picks the larger splash
    uint8 reserved0D[0xB]; // 0D
    union
    {
        STCOM_MATRIX matrix;
        struct
        {
            uint8 reserved[0x14];
            ST14_GROW grow; // 2C
        } s;
    } u_18;               // 18
    STCOM_SVECTOR pos_38; // 38
    uint32 color_40;      // 40
    uint8 reserved44[4];  // 44
};

// Scene_work's first byte.
#define ST14_SCENE_BYTE_0 (*(uint8 *)&Scene_work)

// A model drawn with its own matrix (ROCK_NEO's model record inside a work slot at +0x88).
typedef struct
{
    uint32 word_88;         // 88
    STCOM_MATRIX matrix_8C; // 8C
    STCOM_SVECTOR pos_AC;   // AC
    uint32 color_B4;        // B4
    uint8 reservedB8[4];    // B8
} ST14_MODEL;

// A prop drawn as a model (func_80111C7C's and func_80111FB8's objects).
typedef struct ST14_PROP ST14_PROP;

typedef void (*ST14_PROP_FUNC)(ST14_PROP *wp);

struct ST14_PROP
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
    sint8 value_C;                          // 0C
    sint8 value_D;                          // 0D
    sint8 value_E;                          // 0E
    sint8 count_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STAGE_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    STCOM_SVECTOR angle_64;                 // 64
    uint8 reserved6C[0xC];                  // 6C
    void *data_78;                          // 78
    uint8 reserved7C[0xC];                  // 7C
    ST14_MODEL model;                       // 88
    sint32 hit_BC;                          // BC
    sint32 hit_C0;                          // C0
    sint32 hit_C4;                          // C4
    sint32 hit_C8;                          // C8
};

extern ST14_KIND **D_8009884C;
extern ST14_KIND2 **D_80098844;
extern STAGE_SLOT_FUNC *D_801144F4[];
extern STAGE_SLOT_FUNC *D_80114634[];
extern STAGE_SLOT_FUNC D_80114694[];
extern STAGE_SLOT_FUNC D_80114754[];
extern STAGE_SLOT_FUNC D_801147D4[];
extern STAGE_SLOT_FUNC D_8011485C[];
extern STAGE_ROOM2_FUNC *D_80114FB8[];
extern STAGE_ROOM2_FUNC D_80115088[];
extern STAGE_ROOM2_FUNC D_80115244[];
extern ST14_PROP_FUNC D_80115ED8[];
extern STAGE_OBJ_FUNC D_801161F4[];
extern STAGE_OBJ_FUNC D_80116200[];
extern STAGE_OBJ_FUNC D_801154B0[];
extern ST14_SPLASH_FUNC D_80115A58[];
extern sint16 *D_80115D54[];
extern sint16 *D_80115D78[];
extern STAGE_OBJ_FUNC D_80115D9C[];
extern STAGE_OBJ_FUNC D_80115DB0[];
extern STAGE_OBJ_FUNC D_80115E10[];
extern uint8 D_80114FFC[];
extern uint8 D_80115004[][8];
extern STCOM_FIXED_VECTOR D_801154A0;
extern STCOM_EFFECT *D_801162E0[];
extern ST14_TALKER_FUNC D_80115C58[];
extern ST14_BOX D_80116224[];
extern sint32 D_80113F94[];
extern void *D_80114C64[];
extern void *D_80114E70[];
extern uint8 D_80114E84[][0x28];
extern uint8 D_80114F4C[][8];
extern sint32 D_80114F7C[];
extern ST14_BOX D_80114FF8; // only x, z, w, h (func_801006DC)
extern uint8 D_80115064[];
extern uint8 D_8011506C[];
extern uint8 D_80115074[];
extern STAGE_SCRIPT_ENTRY D_80115094[];
extern uint8 D_801150BC[];
extern uint8 D_8011510C[];
extern STAGE_ROOM2_FUNC D_80115214[];
extern STAGE_ROOM2_FUNC D_80115224[];
extern uint8 D_80115250[];
extern uint8 D_80115264[];
extern uint8 D_801152B4[];
extern STAGE_ROOM2_FUNC D_801153E4[];
extern STAGE_ROOM2_FUNC D_801153F4[];
extern sint16 D_801159F4[][4];
extern sint16 D_80115A0C[][4];
extern sint16 D_80115A24[][4];
extern sint16 D_80115A3C[][4];
extern uint16 D_80115A54[];
extern ST14_ACTOR_FUNC D_80115C1C[];
extern ST14_ACTOR_FUNC D_80115C2C[];
extern uint8 D_80115C4C[];
extern uint8 D_80115DBC[];
extern ST14_VILLAGER_FUNC D_80115DC8[];
extern uint32 D_80115DE4[];
extern sint8 D_80115DFC[];
extern sint16 D_80115E04[];
extern sint16 D_80115E0E;
extern sint16 D_80115E20[];
extern uint16 D_80115E28[];
extern sint16 D_80115EB4[];
extern ST14_PROP_FUNC D_80115EC0[];
extern sint16 D_80115ECC[];
extern ST14_TEST_FUNC D_80116208[];
extern uint8 D_80116248[];
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

// Sound_call2 as func_8010D984's file saw it: without a prototype, so the call returns int and
// sets v0 (which changes how GCC schedules the other value-returning call there).
typedef sint32 (*ST14_SOUND_CALL2_FUNC)();
#define ST14_SOUND_CALL2 ((ST14_SOUND_CALL2_FUNC)Sound_call2)

void func_801004B4(void);
void func_801004E4(void);
void func_80100748(STAGE_ROOM *wp);
void func_80100CC4(STAGE_ROOM *wp);
sint32 func_801006DC(ST14_BOX *box);
void func_801010F4(void);
void func_80111FB8(ST14_PROP *wp);
void func_80112C00(STAGE_OBJ *wp);
void func_80112D70(STAGE_OBJ *wp);
void func_80112DAC(STAGE_OBJ *wp);
void func_80101C28(STAGE_OBJ *wp);
void func_801053B4(ST14_SPLASH *wp);
void func_8010583C(ST14_SPLASH *wp);
void func_8010E594(void *wp, STAGE_FACE16 *face, sint32 index);
void func_8010E9DC(STAGE_OBJ *wp);
void func_8010F0F0(STAGE_OBJ *wp);
void func_8010F5AC(STAGE_OBJ *wp);
sint32 func_80113330(void);
void func_8010CAA4(STAGE_OBJ *wp);
void func_80100C9C(STAGE_ROOM *wp);
void func_8010E8A0(STAGE_OBJ *wp);
void func_8010E934(STAGE_OBJ *wp);
void func_801010A8(STAGE_ROOM *wp);
void func_8010F9AC(STAGE_OBJ *wp);
sint32 func_80113290(STAGE_OBJ *wp);
void func_8010E8C8(STAGE_OBJ *wp);
void func_80101024(STAGE_ROOM *wp);
void func_8010F9F8(STAGE_OBJ *wp);
void func_8010E800(STAGE_OBJ *wp);
void func_8010E1AC(STAGE_OBJ *wp);
void func_8001E4C4(void *a, void *b);
// func_800317AC is declared in stage_common/stage.h.
void func_8010E5DC(STAGE_OBJ *wp, STAGE_FACE16 *face);
void func_8010F888(ST14_VILLAGER *wp);
void func_8010ED0C(ST14_VILLAGER *wp);
void func_8010EFF8(ST14_VILLAGER *wp);
void func_8010EE98(ST14_VILLAGER *wp);
sint32 func_8010DDD0(ST14_ACTOR *wp);
void func_8010D984(ST14_ACTOR *wp, sint32 side);
sint32 func_8010DEF8(ST14_ACTOR *wp);
void func_8010DB28(ST14_ACTOR *wp);
sint16 func_8010DCCC(ST14_ACTOR *wp);
sint32 func_8010DA30(ST14_ACTOR *wp, sint32 a1, sint32 a2);
void func_8010D890(STCOM_SVECTOR *pos);
void func_8010D8FC(ST14_ACTOR *wp);
sint32 func_8010F934(ST14_VILLAGER *wp);
void func_8010F8B8(ST14_VILLAGER *wp);
void func_8010F8E4(ST14_VILLAGER *wp);
void func_8010F900(ST14_VILLAGER *wp);
sint32 func_80113084(STAGE_OBJ *wp, ST14_BOX *box);
void func_80111C7C(ST14_PROP *wp);
void func_801123AC(ST14_PROP *wp);

void func_8010098C(STAGE_ROOM *wp);
void func_80100B88(STAGE_ROOM *wp);
void func_8010E0B0(ST14_TALKER *wp);
void func_8010E304(ST14_TALKER *wp);
void func_8010E454(ST14_TALKER *wp);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
// func_80047148 as func_8010C9CC calls it: without the effect (retail passes whatever a2 holds).
void func_80047148_2(void *wp, STCOM_SVECTOR *pos) __asm__("func_80047148");
// func_8002FEA4 as func_8010CDB0 calls it: without a prototype, so an int result is set in v0.
sint32 func_8002FEA4_int(void *wp, sint32 x, sint32 y, sint32 z) __asm__("func_8002FEA4");
sint32 func_80048EA4(STCOM_SVECTOR *pos, sint16 *box, sint32 dy, sint32 kind);
STAGE_OBJ *func_80031498(void);
void func_8001F1DC(void);
STCOM_MATRIX *RotMatrix(STCOM_SVECTOR *r, STCOM_MATRIX *m);
sint32 func_80048E6C(void *wp);
void func_8005D4D4(void);
void func_8005D4E8(void);
void func_8005D620(void *wp, sint32 a1, sint32 a2, sint32 a3, sint32 color);
void func_8003187C(void *wp);
void func_8003697C(void);
void func_8005D6E8(void *wp);
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);
void func_80036470(void *track);
void func_80036478(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);

#endif
