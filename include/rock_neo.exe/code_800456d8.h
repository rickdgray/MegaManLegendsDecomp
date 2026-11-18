#ifndef ROCK_NEO_CODE_800456D8_H
#define ROCK_NEO_CODE_800456D8_H

#include "sound.h"
#include "code_800133d8.h"
#include "game.h"

typedef struct
{
    sint16 vx, vy, vz, pad;
} CODE456_SVECTOR;

typedef struct
{
    sint32 vx, vy, vz, pad;
} CODE456_VECTOR;

// 3x3 rotation matrix; the translation area is reused for scalar fields.
typedef struct
{
    sint16 m[3][3];
    sint16 pad12;
    union
    {
        sint32 t[3];
        struct
        {
            sint16 tx_lo;
            sint16 value_2e;
            sint16 ty_lo;
            sint16 ty_hi;
            sint16 value_34;
            sint16 tz_hi;
        } h;
    } tr;
} CODE456_MTX;

typedef union
{
    SOUND_ARGS args;
    PL_SHORT_VECTOR pos;
    uint16 half[4];
    uint32 word[2];
} CODE456_SND;

typedef struct CODE456_WORK
{
    uint8 routine_0;
    uint8 id_1;
    uint8 index_2;
    uint8 flag_3;
    uint8 routine_4;
    uint8 reserved05[3];
    uint8 routine_8;
    uint8 routine_9;
    uint8 value_a;
    uint8 timer_b;
    sint16 rot_c;
    sint16 rot_e;
    uint8 reserved10[8];
    CODE456_MTX mtx_18;
    CODE456_SND snd_38;
    uint32 color_40;
    void *model_44;
} CODE456_WORK;

// Alternate view used by the animation-step routines.
typedef struct
{
    uint8 routine_0;
    uint8 reserved01[2];
    uint8 flag_3;
    uint8 reserved04[4];
    uint8 routine_8;
    uint8 step_9;
    uint8 timer_a;
    uint8 timer_b;
    sint8 value_c;
    sint8 index_d;
    sint8 value_e;
    uint8 reserved0f[5];
    uint32 word_14;
    uint32 word_18;
    uint8 reserved1c[6];
    uint8 value_22;
    uint8 value_23;
    uint16 value_24;
} CODE456_ANIM;

typedef struct
{
    uint16 angle[8];
    sint16 index[8];
} CODE456_SPARK_DATA;

// View used by the spark spawner: two parallel arrays of eight halfwords.
typedef struct
{
    uint8 routine_0;
    uint8 reserved01[2];
    uint8 flag_3;
    uint8 reserved04[2];
    uint8 flags_6;
    uint8 reserved07;
    uint8 routine_8;
    uint8 reserved09[0x13];
    sint16 x, y, z;
    uint8 reserved22[6];
    CODE456_SPARK_DATA data;
} CODE456_SPARK;

// View used by the item-box routines: the matrix area is cleared as words.
typedef struct
{
    uint8 routine_0;
    uint8 id_1;
    uint8 index_2;
    uint8 flag_3;
    uint8 reserved04[4];
    uint8 routine_8;
    uint8 reserved09;
    uint8 value_a;
    uint8 timer_b;
    sint8 sound_c;
    uint8 reserved0d[0xB];
    union
    {
        uint32 w[8];
        sint16 h[16];
        CODE456_MTX mtx;
    } m18;
    CODE456_SND snd_38;
    uint32 color_40;
    sint16 size_44[2];
} CODE456_BOX;

typedef struct
{
    uint32 word;
    uint8 value_4;
    uint8 timer_5;
    uint8 value_6;
    uint8 value_7;
} CODE456_ANIM_STEP;

typedef struct
{
    uint32 word;
    uint8 reserved04[12];
} CODE456_ENTRY;

// Six-byte table records read through separate symbols.
typedef struct
{
    uint16 v;
    uint8 pad[4];
} CODE456_H6;

typedef struct
{
    uint8 v;
    uint8 pad[5];
} CODE456_B6;

typedef struct
{
    sint16 h[6];
} CODE456_REC12;

typedef void (*CODE456_FUNC)(CODE456_WORK *wp);

#define CODE456_FRAME (*(uint16 *)0x1F800002)

extern CODE456_FUNC D_8008A708[];
extern CODE456_FUNC D_8008A724[];
extern CODE456_FUNC D_8008A76C[];
extern CODE456_FUNC D_8008A778[];
extern uint16 D_80097E64[];
extern uint16 D_80097EE0[];
extern uint16 D_80097E70[];
extern uint16 D_80097EEC[][4];
extern uint16 D_8008A678[][8];
extern uint16 D_8008A680[][8];
extern CODE456_ANIM_STEP D_8008A6C8[];
extern CODE456_ENTRY **D_80098844;
extern CODE456_ENTRY **D_8009884C;
extern CODE456_ENTRY **D_80098928;
extern CODE456_ENTRY **D_8009892C;
extern PL_WORK Player_work2;
extern CODE456_FUNC D_8008A718[];
extern uint8 D_800986D8[];
extern CODE456_B6 D_8008A734[];
extern CODE456_B6 D_8008A74C[];
extern CODE456_H6 D_8008A730[];
extern CODE456_H6 D_8008A732[];
extern CODE456_H6 D_8008A748[];
extern CODE456_H6 D_8008A74A[];
extern CODE456_REC12 D_8008A618[][4];
extern CODE456_REC12 D_8008A310[];
extern uint16 D_80097E7A[];
extern uint16 D_80097EFA[];
extern sint16 D_80097F1C[];
extern uint16 D_80097F24[];
extern uint8 D_8008A5A8[][16];
extern uint32 D_8009A6C0[][5];
extern uint32 D_8009A710[][4];
extern uint32 D_8008A378[][32];
extern uint32 D_8008A578[];
extern sint16 D_80097E9C[];
extern uint16 D_80097EA8[];
extern uint8 D_8008A2B0[][16];
extern uint8 D_8009A5A0[];
extern uint8 D_8009A5D0[];
extern uint8 D_8009A600[];
extern uint8 D_8009A630[];
extern uint8 D_8009A660[];
extern sint32 D_800986D0;
extern CODE456_FUNC D_8008A6A8[];
extern uint16 D_80097EC0[][4];
extern uint8 D_80097EE8[];

void func_80031988(void *wp);
uint32 func_8002FE74(uint8 id);
void func_8002F9C4(void *wp, uint8 *arg);
void func_80043294(uint32 id, sint32 arg1, sint32 arg2);
void func_80043340(uint32 id, sint32 arg1);
sint32 func_80048EA4(void *snd, CODE456_REC12 *rec, sint32 arg2, sint32 arg3);
sint32 func_8004B5CC(void *snd, PL_SHORT_VECTOR *old, sint32 arg2, CODE456_REC12 *rec);
void func_80046B34(PL_SHORT_VECTOR *pos, uint32 arg);
#ifdef __wasm32__
sint32 func_8004AC8C(void *tr, sint32 flags);
#else
void func_8004AC8C(void *tr, sint32 flags);
#endif
void func_80045AB4(CODE456_WORK *wp);
void func_80045BC8(CODE456_WORK *wp);
void func_80046890(CODE456_WORK *wp);
void func_800469A4(CODE456_WORK *wp);
void func_80046A0C(CODE456_WORK *wp);
void func_80047CD8(CODE456_ANIM *wp);
void func_80047C84(CODE456_ANIM *wp);
sint32 func_80047BF8(CODE456_SVECTOR *a, CODE456_SVECTOR *b);
void func_800398E0(sint32 arg);
uint32 *func_8002D4B8(void);
sint32 func_8004920C(void *pos);
uint8 func_800482A8(void *wp);
void func_80047DD8(CODE456_SPARK *wp);
sint32 func_800341BC(void *pos, sint32 half, sint32 arg2, sint32 arg3, sint32 id, void *tbl,
                     uint32 flags, sint32 arg7, sint32 arg8);
sint32 rand(void);
sint32 rcos(sint32 angle);
sint32 rsin(sint32 angle);
CODE456_WORK *func_80031618(void);
void RotMatrixY(sint32 angle, CODE456_MTX *m);
void RotMatrix(CODE456_SVECTOR *r, CODE456_MTX *m);
void ScaleMatrix(CODE456_MTX *m, CODE456_VECTOR *v);
sint32 SquareRoot0(sint32 a);
void func_80046F38(void);
uint32 *func_8002D464(void);

#endif
