#ifndef ST08_H
#define ST08_H

#include "common.h"
#include "stage_common/stage.h"
#include "stage_common/stcom05.h"

// Game_work's words past STCOM_GAME_WORK's named fields.
#define ST08_GAME_WORD(offset) (*(sint32 *)((uint8 *)&Game_work + (offset)))

// An effect routine that also takes a value.
typedef void (*ST08_FX_ARG_FUNC)(STAGE_FX *wp, sint32 arg);

typedef struct
{
    sint32 value_0;
    sint32 value_4;
} ST08_PAIR;

// The pad's held-key mask (D_800C0C26) as a one-field record: in-struct memory to GCC, so a
// store to it stays ahead of a later key load through a player pointer (func_80101604).
typedef struct
{
    uint16 value;
} ST08_PAD_MASK;

// A 0x24-byte event slot (freed through Close_EVE_WORK) with a key at +0x20.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 reserved09[0xB]; // 09
    uint8 value_14;        // 14
    uint8 value_15;        // 15
    uint8 value_16;        // 16
    uint8 value_17;        // 17
    uint8 value_18;        // 18
    uint8 value_19;        // 19
    uint8 value_1A;        // 1A
    uint8 value_1B;        // 1B
    uint8 value_1C;        // 1C
    uint8 value_1D;        // 1D
    uint8 reserved1E[2];   // 1E
    uint32 key_20;         // 20
} ST08_EV;

// Scale choices copied to the stack by func_8010C3D8.
typedef struct
{
    sint16 value[3];
} ST08_SCALE_SIZES;

extern ST08_SCALE_SIZES D_801001D8;

extern STAGE_FUNC D_8011847C[];
extern STAGE_FUNC D_80118508[];
extern STAGE_OBJ_FUNC D_80113AAC[];
extern STAGE_OBJ_FUNC D_80113AB4[];
extern STAGE_OBJ_FUNC D_80113AC4[];
extern STAGE_OBJ_FUNC D_80113B30[];
extern STAGE_OBJ_FUNC D_80113B3C[];
extern STAGE_SLOT_FUNC *D_8011206C[];
extern STAGE_SLOT_FUNC *D_8011220C[];
extern STAGE_SLOT_FUNC D_80112210[];
extern STAGE_SLOT_FUNC D_801122D0[];
extern STAGE_SLOT_FUNC D_80112300[];
extern STAGE_SLOT_FUNC D_8011234C[];
extern STAGE_ROOM2_FUNC D_80113228[];
extern STAGE_ROOM2_FUNC D_8011330C[];
extern STAGE_FX_FUNC D_80114224[];
extern STAGE_FUNC D_80114394[];
void func_801119F0(STAGE_WORK *wp);
void func_80111D24(STAGE_WORK *wp);
void func_80105B60(STAGE_OBJ *wp);
void func_80106218(STAGE_OBJ *wp);
void func_801066D8(STAGE_OBJ *wp);
void func_80108540(STAGE_OBJ *wp);
void func_8010857C(STAGE_FX *wp);
void func_8010859C(STAGE_OBJ *wp);
void func_8010A8F0(STAGE_FX *wp);
void func_8010031C(void);
void func_80101F84(STAGE_FX *wp);
void func_80101FA4(STAGE_ROOM *wp);
void func_80102B58(STAGE_ROOM *wp);
void func_80110084(STAGE_FX *wp);
void func_80110BA0(STAGE_WORK *wp);

sint32 func_80101404(void);

void func_80100708(STAGE_ROOM *wp);

extern STAGE_OBJ_FUNC D_801143A0[];
void func_80110BDC(STAGE_OBJ *wp);

sint32 func_80101228(STAGE_ROOM *wp);

void func_80100724(uint8 arg0, uint8 arg1, sint16 arg2, sint16 arg3, uint16 arg4);

void func_8010159C(sint16 arg0, sint16 arg1, sint16 arg2, sint16 arg3);

void Sce_event_next(void);
void func_80102328(STAGE_FX *wp);

void func_80107620(STAGE_ACTOR *wp);
void func_80107560(STAGE_ACTOR *wp);

void func_801104C8(STAGE_OBJ *wp);

extern uint8 D_801127F4[][0x28]; // by room (func_800371A0)
extern uint8 D_80112F70[];
extern uint8 D_80112F80[];
extern uint8 D_80112F88[];
extern uint8 D_80112F90[];
extern uint8 D_80112F98[];
extern uint8 D_80112FA0[];
extern uint8 D_80112FA8[];
extern uint8 D_80113128[];
extern uint8 D_80113190[];
extern uint8 D_801131B8[];
extern uint8 D_801132EC[];
extern uint8 D_80113B24[];
extern uint8 D_80113FEC[];
extern uint8 D_801140D0[][0xC];
extern uint8 D_801143A8[];

void func_8001DF10(uint8 *);
void func_80100B48(STAGE_ROOM *wp);

void func_80100A48(STAGE_ROOM *wp);

void func_80100C48(STAGE_ROOM *wp);

void func_80100D48(STAGE_ROOM *wp);

void func_80100E48(STAGE_ROOM *wp);

extern STAGE_ACTOR D_8009F108[]; // ROCK_NEO's 0x3C0-byte slots
sint32 func_80036294(sint32 arg);
extern STAGE_OBJ_FUNC D_80113ACC[];
extern STAGE_SLOT_FUNC D_801140C0[];
extern uint8 D_80113130[][8];
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
void func_8001E460(sint32 a0, sint32 a1, sint32 a2);
void Sce_flag_off(sint32 flag);
void func_8005C224(sint32 arg);
extern sint32 D_80113220;
extern uint8 D_80113224;
extern ST08_PAIR D_80113208[];
void func_80106714(STAGE_OBJ *wp);

void Sce_flag_off(sint32 flag);
void func_8010C37C(STAGE_10C *wp);

void Sce_flag_off(sint32 flag);
void func_80100578(void);

void func_8001EC0C(void);
void Sce_event_update(void);
sint16 func_80048E6C(void *wp);
void func_80102158(STAGE_ROOM_WORK *wp);

void func_80100690(STAGE_ROOM_WORK *wp);

void func_801084C0(STAGE_ACTOR *wp);

void func_80100A94(STAGE_ROOM_WORK *wp);
void func_80100B94(STAGE_ROOM_WORK *wp);
void func_80100C94(STAGE_ROOM_WORK *wp);
void func_80100D94(STAGE_ROOM_WORK *wp);
void func_80100E94(STAGE_ROOM_WORK *wp);
void func_80100F48(STAGE_ROOM_WORK *wp);
void func_80100FFC(STAGE_ROOM_WORK *wp);

extern STAGE_ACTOR_FUNC D_80113AF4[];
extern STAGE_ACTOR_FUNC D_80113AF8[];
void func_80107470(STAGE_ACTOR *wp);
void func_801076BC(STAGE_ACTOR *wp);

extern ST08_FX_ARG_FUNC D_801140F4[];
void Sce_flag_off(sint32 flag);
STAGE_ACTOR *func_80107FF8(void);

void Sce_flag_off(sint32 flag);
void func_80101858(STAGE_ROOM *wp);

void Sce_flag_off(sint32 flag);
void func_8010CB24(STAGE_FX *wp);

extern uint8 D_801128E4[][8]; // by D_8011295C[room]
extern uint8 D_80112F78[];

void func_80107AE4(STAGE_ACTOR *wp);

void func_8001EB98(void *entry);
void func_8001E3F0(sint32 arg);
extern uint8 D_801131CC[];
extern STAGE_SCRIPT_ENTRY D_801131E0[];
sint32 func_80101360(STAGE_ROOM_WORK *wp);

void func_80110C28(STAGE_OBJ50 *wp);

uint32 func_8003AC24(uint32 key);
void Close_EVE_WORK(void *wp);
extern uint8 D_80118345;
extern uint8 D_8011837F[];
extern uint8 D_801183B9[];
extern uint8 D_801183F3[];
extern uint8 D_8011842D[];
void func_80111A2C(ST08_EV *wp);

// A 0x24-byte event slot (freed through Close_EVE_WORK) with a key at +0x1C.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 reserved09[0xB]; // 09
    uint8 value_14;        // 14
    uint8 value_15;        // 15
    uint8 value_16;        // 16
    uint8 value_17;        // 17
    uint8 value_18;        // 18
    uint8 value_19;        // 19
    uint8 value_1A;        // 1A
    uint8 reserved1B;      // 1B
    uint32 key_1C;         // 1C
    uint8 reserved20[4];   // 20
} ST08_EV1C;

extern STAGE_ROOM_FUNC D_80113110[];
extern STAGE_ROOM_FUNC *D_801130D0[];
extern uint8 D_80118485;
extern uint8 D_801184BF[];
extern uint8 D_801184F9[];
extern uint8 D_80118533[];
extern uint8 D_8011856D[];

// A room's music by scene flag: the first set flag picks the song (flag 0xFFFF ends the list).
typedef struct
{
    uint16 flag;
    uint8 id;
    uint8 reserved03;
} ST08_MUSIC;

// Player_work as the stage's scenes see it: where a scene puts the player (+0x428..+0x448).
typedef struct
{
    sint8 flags_0;                // 00
    uint8 reserved01[7];          // 01
    uint8 routine_0;              // 08
    uint8 routine_1;              // 09
    uint8 value_A;                // 0A
    uint8 reserved0B[9];          // 0B
    STCOM_SVECTOR position;       // 14
    uint8 reserved1C[0x38];       // 1C
    STCOM_SVECTOR rotation;       // 54
    uint8 reserved5C[0x61];       // 5C
    uint8 flags_bd;               // BD
    uint8 reservedBE[0x6E];       // BE
    uint16 key_12C;               // 12C: pad bits of the player's controls
    uint16 key_12E;               // 12E
    uint8 reserved130[4];         // 130
    uint16 key_134;               // 134
    uint8 reserved136[4];         // 136
    uint16 key_13A;               // 13A
    uint16 key_13C;               // 13C
    uint8 reserved13E[0x2D];      // 13E
    uint8 flags_16B;              // 16B
    uint8 reserved16C[4];         // 16C
    uint8 value_170;              // 170
    uint8 value_171;              // 171
    uint8 reserved172[0x2B6];     // 172
    STCOM_FIXED_VECTOR fixed_428; // 428
    STCOM_SVECTOR pos_438;        // 438
    STCOM_SVECTOR rot_440;        // 440
    uint8 value_448;              // 448
    uint8 reserved449[2];         // 449
    uint8 value_44B;              // 44B
    uint8 reserved44C[2];         // 44C
    sint8 value_44E;              // 44E
} ST08_PL_WORK;

#define ST08_PL ((ST08_PL_WORK *)&Player_work)

extern ST08_MUSIC D_8011297C[];
extern uint8 D_801131A4[];
void func_80101424(void);
void func_80101478(sint16 x, sint16 y, sint16 z, sint16 angle);
uint32 func_8003AC9C(sint32 idx, uint32 key);
sint32 func_80048C60(STCOM_SVECTOR *pos);

// A ranking entry: a score (time) and four values kept with it.
typedef struct
{
    uint32 score;
    uint16 value[4];
    uint8 reserved0C[4];
} ST08_RANK;

uint8 func_80101508(ST08_RANK *tbl, uint32 score);

extern ST08_PAD_MASK D_800C0C26_S __asm__("D_800C0C26");
// The shared input mask as an array, so its address stays in a base register (func_80101604).
extern uint16 D_800C0C2A_A[] __asm__("D_800C0C2A");

extern uint8 D_80113238[];
extern uint8 D_8011324C[];
void func_8003697C(void);

extern uint8 D_80118514;

void func_8001E390(sint32 a0);

extern void *D_80112434[]; // room models by room
extern void *D_8011262C[]; // spawn list by room
extern void *D_801127DC[]; // exit list by room
extern sint32 D_8011295C[];
extern STCOM_SVECTOR D_80112974;

// A hit block whose word at +8 receives func_800341BC's result.
typedef struct
{
    uint16 flags_0;      // 0
    uint16 value_2;      // 2
    sint16 timer_4;      // 4
    uint8 reserved06[2]; // 6
    sint32 value_8;      // 8: hit result bits
} ST08_HIT;

// A 0x3C0-byte work slot as this stage's villagers use it (r3_st08_55A4.c): STAGE_ACTOR with the
// word-wide resets of +0x44..+0x74 named.
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
    sint8 value_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint32 turn_64;                         // 64
    uint8 reserved68[8];                    // 68
    sint32 value_70;                        // 70
    sint32 value_74;                        // 74
    void *data_78;                          // 78
    uint8 reserved7C[0xDC];                 // 7C
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x1E8];               // 160
    ST08_HIT hit;                           // 348
    uint8 reserved354[4];                   // 354
    uint8 anim_358;                         // 358: animation playing
    uint8 hold_359;                         // 359: frames left
    uint8 index_35A;                        // 35A: step in its script
    uint8 reserved35B[0x65];                // 35B
} ST08_ACTOR;

typedef void (*ST08_ACTOR_FUNC)(ST08_ACTOR *wp);

// The scratchpad's copy of the rotation func_8003346C draws a model with.
#define ST08_SP_ROT_X (*(sint16 *)0x1F800128)
#define ST08_SP_ROT_Z (*(sint16 *)0x1F80012C)
void func_80105B9C(ST08_ACTOR *wp, ST08_HIT *hit);

// A 0x10C-byte slot of ROCK_NEO's pool at D_8009CF88 (32 of them), as func_80110434 reads it.
typedef struct
{
    sint8 flags_0;          // 00
    uint8 reserved01;       // 01
    uint8 kind_2;           // 02
    uint8 reserved03[9];    // 03
    sint8 value_C;          // 0C
    uint8 reserved0D[0xFF]; // 0D
} ST08_SLOT10C;

extern ST08_SLOT10C D_8009CF88[];
extern ST08_PAIR D_8011422C[]; // by Game_work +0x150
void func_801100C0(sint16 x, sint16 y, sint16 z, sint16 angle);
uint8 func_80110314(ST08_RANK *tbl, uint32 score);
void func_801103A8(STAGE_OBJ50 *wp);
uint8 func_80110434(STAGE_OBJ50 *wp);

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
    uint8 reservedC0[4];                    // C0
    STCOM_SVECTOR value_C4;                 // C4: a point it is pushed away from
    sint32 speed_CC;                        // CC
    uint8 reservedD0[0x3C];                 // D0
} ST08_10C;

typedef void (*ST08_10C_FUNC)(ST08_10C *wp);

extern ST08_10C_FUNC D_80113FE0[];

void func_8010BCBC(ST08_10C *wp, sint16 scale);

void func_8010C3D8(ST08_10C *wp);
void func_8010C4AC(ST08_10C *wp);

void func_8010C544(ST08_10C *wp, sint32 angle);

void func_8010BD3C(ST08_10C *wp);

// An animation script: animation, then frames to hold it (anim 0xFF loops).
typedef struct
{
    uint8 anim;
    uint8 hold;
} ST08_ANIM;

extern ST08_ANIM D_80113B1C[];

// Scene_work's object slots from +0x24 (the actors a scene drives).
#define ST08_SCENE_OBJ(i) (*(void **)((uint8 *)&Scene_work + 0x24 + (i) * 4))

// ST08_EV as a five-layer texture animation: each layer's script step and frames left.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 reserved09[0xB]; // 09
    uint8 step_14[5];      // 14
    uint8 timer_19[5];     // 19
    uint8 reserved1E[2];   // 1E
    uint32 key_20;         // 20
} ST08_ANIM_EV;

extern uint8 D_80118344[5][29][2]; // per layer: frame, then frames to hold it (0xFF loops)
extern uint8 D_80118468[5][4];     // per layer: the four corners' base u/v

// ST08_EV1C as a two-layer texture animation.
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 reserved09[0xB]; // 09
    uint8 step_14[2];      // 14
    uint8 timer_16[2];     // 16
    uint8 reserved18[4];   // 18
    uint32 key_1C;         // 1C
    uint8 reserved20[4];   // 20
} ST08_ANIM2_EV;

extern uint8 D_80118484[2][29][2]; // per layer: frame, then frames to hold it (0xFF loops)
extern uint8 D_801184F8[2][4];     // per layer: the four corners' base u
extern uint8 D_80118500[2][4];     // per layer: the four corners' base v

// A falling rock's start: x and z, then its kind and a parameter (func_80110150).
typedef struct
{
    sint16 x;      // 0
    sint16 z;      // 2
    sint8 kind_4;  // 4
    sint8 value_5; // 5
} ST08_DROP;

// A set of falling rocks per Game_work +0x150 (D_80114374).
typedef struct
{
    ST08_DROP *drops; // 0
    uint8 count_4;    // 4
} ST08_DROP_SET;

extern ST08_DROP_SET D_80114374[];

void func_80110150(STAGE_OBJ *wp);

// Scene_work as the shooting game (func_80106428) reads it.
typedef struct
{
    uint8 reserved00[4]; // 00
    uint8 value_4;       // 04: 5 while the game runs
    uint8 reserved05[5]; // 05
    uint8 value_A;       // 0A: the score
    uint8 value_B;       // 0B: added to the score per hit
    uint32 flags_C;      // 0C
} ST08_SCENE_WORK;

#define ST08_SCENE (*(ST08_SCENE_WORK *)&Scene_work)

extern STAGE_CAM Sce_camera_work;

void func_8010C784(ST08_10C *wp, STAGE_OBJ50 *owner);

// The rock game's script (func_801105AC): its place in the ranking (0xFF: none) and the score calls.
extern uint8 D_80118598;
void func_8005C218(sint32 arg);
void func_8005C230(sint32 score);
void func_8005C24C(sint32 arg);
sint32 Sound_seq_is_eos(sint32 arg);

void func_80039E50(void);
void func_80039FFC(STCOM_FIXED_VECTOR *vec, sint32 arg1, sint32 arg2, sint32 arg3);

// The shooting game's script (func_801018CC): its place in the ranking (0xFF: none).
extern uint8 D_80118510;
void func_8005C23C(sint32 hits);
void func_800425FC(void *pl, sint32 arg);

#endif // ST08_H
