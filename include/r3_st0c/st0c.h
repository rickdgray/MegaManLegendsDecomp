#ifndef ST0C_H
#define ST0C_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom18.h"
#include "stage_common/stcom23.h"

// From r3_st0b (ST0B_OBJ).
// A view of STAGE_OBJ with the fields r3_st0b's own code uses named by offset (generated from the
// accesses; the objects differ, so a field may mean different things in different routines).
typedef struct
{
    sint8 be_flag;   // 00
    uint8 work_id;   // 01
    uint8 id;        // 02
    uint8 type;      // 03
    uint8 reserved4; // 04
    uint8 value_5;   // 05
    uint16 value_6;  // 06
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    union
    {
        struct
        {
            sint8 work_0; // 0C
            sint8 work_1; // 0D
        } b;
        sint16 timer; // 0C
    } u_C;
    union
    {
        struct
        {
            sint8 work_2; // 0E
            sint8 work_3; // 0F
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
    sint32 value_A4;                        // A4
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
    uint8 reservedD0[0x2B];                 // D0
    uint8 value_FB;                         // FB
    uint8 reservedFC[0x3];                  // FC
    uint8 value_FF;                         // FF
    STAGE_PART part_100[12];                // 100
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
    uint8 reserved350[0x30];                // 350
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
    uint8 reserved3B0[0x20];                // 3B0
    sint32 value_3D0;                       // 3D0
    sint32 value_3D4;                       // 3D4
    sint32 value_3D8;                       // 3D8
    sint32 value_3DC;                       // 3DC
    sint32 value_3E0;                       // 3E0
    sint32 value_3E4;                       // 3E4
    uint8 reserved3E8[0x8];                 // 3E8
    sint32 value_3F0;                       // 3F0
    uint8 reserved3F4[0x10];                // 3F4
    sint32 value_404;                       // 404
    uint8 reserved408[0x10];                // 408
    sint32 value_418;                       // 418
    uint8 reserved41C[0x14];                // 41C
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
    void *value_450;                        // 450
    sint32 value_454;                       // 454
    uint8 reserved458[0x2];                 // 458
    sint16 value_45A;                       // 45A
    sint16 value_45C;                       // 45C
    sint16 value_45E;                       // 45E
    sint32 value_460;                       // 460
    sint32 value_464;                       // 464
    uint8 reserved468[0x78];                // 468
    STAGE_FACE face;                        // 4E0
} ST0C_OBJ;

// A 0x50-byte slot (func_80031734) that turns a model about z (func_8010B6D8; D_8010D83C by
// type).
typedef struct ST0C_WHEEL ST0C_WHEEL;
typedef void (*ST0C_WHEEL_FUNC)(ST0C_WHEEL *wp);

struct ST0C_WHEEL
{
    uint8 be_flag;             // 00
    uint8 work_id;             // 01
    uint8 reserved02;          // 02
    uint8 type;                // 03
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

// An object to place (func_80100168's tables): ROCK_NEO's spawn entry, copied field by field.
typedef struct
{
    uint8 flags_0;    // 00
    uint8 reserved01; // 01
    uint8 kind_2;     // 02
    uint8 variant_3;  // 03
    uint8 value_4;    // 04
    uint8 value_5;    // 05
    uint8 reserved06; // 06
    uint8 dir_7;      // 07: rotation.y / 16
    sint8 value_8[4]; // 08: copied to +0xC
    sint16 x_C;       // 0C
    sint16 y_E;       // 0E
    sint16 z_10;      // 10
    sint16 pad_12;    // 12
} ST0C_SPAWN;

// A view of the work slots r3_st0c's remaining routines take, with the fields named by offset
// (generated from their accesses; the objects differ, so a field may mean different things).
typedef struct ST0C_VIEW ST0C_VIEW;

typedef void (*ST0C_VIEW_FUNC)(ST0C_VIEW *wp);
struct ST0C_VIEW
{
    sint8 be_flag;        // 0
    uint8 work_id;        // 1
    uint8 id;             // 2
    uint8 type;           // 3
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
        sint16 h[2];
        sint32 w[1];
    } u_C; // C
    union
    {
        sint16 h[2];
        sint32 w[1];
    } u_10;                                 // 10
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
    uint8 reserved68[0x10];                 // 68
    sint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0x26];                 // 7E
    sint32 value_A4;                        // A4
    uint8 reservedA8[0x4];                  // A8
    sint16 value_AC;                        // AC
    sint16 value_AE;                        // AE
    sint16 value_B0;                        // B0
    uint8 reservedB2[0x2];                  // B2
    sint32 value_B4;                        // B4
    uint8 reservedB8[0xC];                  // B8
    sint32 value_C4;                        // C4
    sint32 value_C8;                        // C8
    ST0C_VIEW *child_CC[4];                 // CC
    uint8 reservedDC[0x10];                 // DC
    uint8 value_EC;                         // EC
    uint8 reservedED[0x2D3];                // ED
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
} ST0C_SHOT_FIXED;

// From r3_st0a (ST0A_SHOT).
// A 0x10C-byte shot (shl/shl.h's SHL_WORK with a model: the fields its routines use).
typedef struct
{
    uint8 be_flag;              // 00
    uint8 work_id;              // 01
    uint8 value_2;              // 02
    uint8 type;                 // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];        // 04
    uint8 flags;                // 06
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
    ST0C_SHOT_FIXED fpos;       // 1C
    STCOM_SVECTOR old_pos;      // 2C
    ST0C_SHOT_FIXED old_fpos;   // 34
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
} ST0C_SHOT;

// From r3_st0a (ST0A_SHOT_FX).
// An effect slot as the shot's sparks use it (shl/shl.h's SHL_FX).
typedef struct
{
    sint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 id;               // 02
    uint8 type;             // 03
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
} ST0C_SHOT_FX;

// Player_work as the stage's player routines take it: +0xC is their routine (a signed byte), and
// +0x428/+0x438 a second position in 16.16 and in halfwords.
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 reserved02[10];              // 02
    sint8 routine_C;                   // 0C
    sint8 value_D;                     // 0D
    uint8 reserved0E[6];               // 0E
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x3FC];           // 2C
    STCOM_FIXED_VECTOR fixed_428;      // 428
    STCOM_SVECTOR pos_438;             // 438
    sint16 value_440;                  // 440
    sint16 value_442;                  // 442
} ST0C_PL;

typedef void (*ST0C_PL_FUNC)(ST0C_PL *wp);
// A copy of the special-weapon shot from r3_shl02 (its SHL_WORK) at 0x80112874: an object slot
// with ROCK_NEO's generic layout up to 0x88, then a model's draw data.
typedef struct
{
    sint8 be_flag; // 00
    uint8 work_id; // 01
    uint8 id;      // 02
    uint8 type;    // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];
    uint8 flags; // 06
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
} ST0C_SHL;

// Player_work's signed bytes past STCOM_PL_WORK's fields.
#define ST0C_PL_SBYTE(offset) (*((sint8 *)&Player_work + (offset)))

extern STAGE_ROOM2_FUNC D_8010BE80[];
extern STAGE_SLOT_FUNC *D_8010C0BC[];
extern STAGE_SLOT_FUNC *D_8010C1FC[];
extern STAGE_SLOT_FUNC D_8010C200[];
extern STAGE_SLOT_FUNC D_8010C2BC[];
extern STAGE_SLOT_FUNC D_8010C2FC[];
extern STAGE_SLOT_FUNC D_8010C300[];
extern uint8 D_8010CB98[];
extern uint8 D_8010CBA0[][8];
extern STAGE_ROOM_FUNC D_8010C888[];
extern STAGE_ROOM_FUNC *D_8010C848[];
extern uint8 D_8010CB40[];
extern STAGE_OBJ_FUNC D_8010D7D0[];
extern STAGE_OBJ_FUNC D_8010D81C[];
extern STAGE_OBJ_FUNC D_8010D82C[];
extern uint8 D_8010CB48;
extern uint8 D_8010CB50;
extern uint8 D_8010CB58;
extern uint8 D_8010CB60;
extern uint8 D_8010CB68;
extern ST0C_PL_FUNC D_8010CE3C[];
extern STAGE_SCRIPT_ENTRY D_8010D874[];
extern ST0C_SPAWN D_8010BE8C[4];
extern ST0C_SPAWN D_8010BEDC[4];
extern uint8 D_8010BF2C[];
extern uint8 D_8010BF78[];
extern uint8 D_8010C078[];
extern uint8 D_8010C088[];
extern void *D_8010C3A4[];
extern void *D_8010C468[];
extern uint8 D_8010C47E;
extern void *D_8010C4D8[];
extern uint8 D_8010C4E8[][0x28];
extern uint8 D_8010C588[][8];
extern sint32 D_8010C788[];
extern uint8 D_8010CB70[];
extern uint8 D_8010CBC0[];
extern STAGE_SCRIPT_ENTRY D_8010CC00[];
extern uint8 D_8010CC3C[];
extern uint8 D_8010CD3C[];
extern STAGE_ROOM2_FUNC D_8010CE4C[];
extern uint8 D_8010D7C4[];
extern ST0C_WHEEL_FUNC D_8010D83C[];
extern ST0C_VIEW *D_801129A0;
extern uint8 D_80164004[];
extern uint8 D_80164005[];
extern uint8 D_80164006[];
extern uint8 D_80164007[];
extern void *D_80164008[];

void func_8010012C(STAGE_ROOM *wp);
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void func_80100DE8(void);
void func_80100E34(void);
void Scene_obj_list_open(uint8 *);
void func_80100F58(STAGE_ROOM *wp);
void func_80100FAC(STAGE_ROOM *wp);
sint32 func_80101330(void);
void func_80101350(uint8 arg0);
void func_80101398(ST0C_OBJ *wp);
void func_801013C0(ST0C_OBJ *wp);
void func_8010143C(ST0C_OBJ *wp);
void func_8010148C(ST0C_OBJ *wp);
void func_8010A590(STAGE_OBJ *wp);
void func_8010B580(STAGE_OBJ *wp);
void func_8010B610(STAGE_FX *wp);
void func_8010B640(STAGE_OBJ *wp);
void func_8010B684(STAGE_OBJ *wp);
void func_8010B67C(void);
void func_8010B698(STAGE_OBJ *wp);
void func_801010AC(void);
void func_801010DC(STAGE_OBJ *wp);
void func_80101130(STAGE_OBJ *wp);
void func_80101184(STAGE_OBJ *wp);
void func_801011D8(STAGE_OBJ *wp);
void func_8010122C(STAGE_OBJ *wp);
void func_80101280(STAGE_OBJ *wp);
void func_8001EB98(void *entry);
void func_8010ACA4(ST0C_SHOT *wp, sint32 arg);
sint32 func_800375D4(void *pl, sint32 arg);
void func_8010AB60(ST0C_SHOT *wp);
sint32 Map_cell_get(STCOM_SVECTOR *pos);
uint32 Stage_idx_model_set(sint32 idx, uint32 key);
void func_8003786C(sint32 id);
void func_800354E0(sint32 bit);
sint16 func_80039B80(void);
sint32 func_80037634(void *player, sint32 arg);
void func_8010A5E0(ST0C_SHL *wp);

// The player's second position (STAGE_PL_VIEW's fixed_428) read by its integer halves.
#define ST0C_PL_FIXED_428 (*(STAGE_FIXED_VECTOR *)&STAGE_PL.fixed_428)

extern sint16 D_800C0F96;
void Sce_event_next(void);
void func_80053AA4(sint32 arg);
void func_8003A264(void);

#endif
