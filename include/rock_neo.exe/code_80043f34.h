#ifndef ROCK_NEO_CODE_80043F34_H
#define ROCK_NEO_CODE_80043F34_H

#include "common.h"

// Local view of the effect work structure used by the code_80043F34 helpers.
typedef struct CODE43_INNER
{
    uint8 reserved00[0x10];
    uint32 value_10;
} CODE43_INNER;

typedef struct CODE43_PARENT
{
    uint8 reserved00[0x70];
    CODE43_INNER *inner_70;
} CODE43_PARENT;

// Position record at +0x38 (copied as eight unaligned bytes)
typedef struct
{
    sint16 x;
    sint16 y;
    sint16 z;
    sint16 w;
} CODE43_POS8;

typedef struct
{
    uint8 b[8];
} CODE43_B8;

typedef struct CODE43_WORK
{
    uint8 flags_0;
    uint8 byte_1;
    uint8 value_2;
    uint8 value_3;
    uint8 reserved04[4];
    uint8 routine_8;
    uint8 count_9;
    uint8 index_a;
    uint8 timer_b;
    sint8 sound_flag_c;
    sint8 sel_d;
    sint8 sel_e;
    sint8 sel_f;
    uint8 reserved10[4];
    union
    {
        uint32 word;
        CODE43_PARENT *parent;
    } u14;
    uint32 word_18;
    uint8 sound_1c[2];
    uint16 value_1e;
    uint16 value_20;
    uint8 value_22;
    uint8 value_23;
    uint16 value_24;
    uint16 value_26;
    sint16 value_28;
    sint16 value_2a;
    sint16 value_2c;
    sint16 reserved2e;
    sint16 value_30;
    sint16 value_32;
    sint16 value_34;
    uint8 reserved36[2];
    CODE43_POS8 pos_38;
    uint32 word_40;
    uint32 word_44;
} CODE43_WORK;

// Halfword view of the packed field at +0x1C
#define CODE43_HALF_1C(wp) (*(uint16 *)(wp)->sound_1c)

// Word and halfword views of packed fields by byte offset
#define CODE43_W(wp, off) (*(uint32 *)((uint8 *)(wp) + (off)))
#define CODE43_H(wp, off) (*(uint16 *)((uint8 *)(wp) + (off)))

typedef void (*CODE43_FUNC)(CODE43_WORK *wp);

typedef struct
{
    uint16 a;
    uint16 b;
} CODE43_PAIR;

typedef struct
{
    uint32 word_14;
    uint32 word_18;
    uint8 value_22;
    uint8 value_23;
    uint8 value_24;
    uint8 routine_8;
} CODE43_ENTRY;

typedef struct
{
    sint32 vx;
    sint32 vy;
    sint32 vz;
} CODE43_VEC;

extern uint8 Player_work[];
#define CODE43_PLAYER_H(off) (*(sint16 *)(Player_work + (off)))
#define CODE43_PLAYER_B(off) (*(sint8 *)(Player_work + (off)))
#define CODE43_PLAYER_W(off) (*(uint32 *)(Player_work + (off)))
// Fade limits per selector (eight-byte records)
typedef struct
{
    sint16 limit;
    sint16 speed;
    sint16 high;
    uint8 step;
    uint8 reserved07;
} CODE43_FADE;

extern CODE43_FADE D_8008A1A8[];
extern CODE43_FADE D_8008A1C8[];
// The fade-out table keeps its step in the byte after the limit.
typedef struct
{
    sint16 limit;
    uint8 step;
    uint8 reserved03[5];
} CODE43_FADE_STEP;
extern CODE43_FADE_STEP D_8008A1E8[];
extern CODE43_FUNC D_8008A214[];
extern uint8 D_80097DDC[];
extern uint8 D_800986C0[];
extern CODE43_FUNC D_8008A208[];
extern CODE43_FUNC D_8008A220[];
extern CODE43_FUNC D_8008A250[];
extern CODE43_FUNC D_8008A258[];
extern CODE43_FUNC D_8008A288[];
extern CODE43_FUNC D_8008A290[];
extern CODE43_FUNC D_8008A358[];
extern CODE43_PAIR D_80097E08[];
extern CODE43_ENTRY D_80097DF0[];
extern uint8 D_80097DE0[];
extern CODE43_PAIR D_8008A138[][4]; // [value_3 & 0xF][sel_d]
extern uint8 D_80097DE5[];
extern uint8 D_80097DE6[];
extern uint8 D_80097DE7[];
extern uint8 D_80097DE4[4];
extern uint8 D_80097DE8[4];
extern uint8 D_80097DEC[4];
extern uint8 D_8008A234[];
extern uint8 D_8008A235[];
extern uint8 D_8008A240[];
extern uint8 D_8008A248[];
extern uint8 D_8008A26C[];
extern uint8 D_8008A26D[];
extern uint8 D_8008A278[];
extern uint8 D_8008A280[];

void func_80031988(CODE43_WORK *wp);
void RotMatrixY();
sint32 func_800341BC(void *pos, sint32 half, sint32 arg2, sint32 arg3, sint32 id, void *tbl,
                     uint32 flags, sint32 arg7, sint32 arg8);
sint32 func_80049C54(void *a, void *b, sint32 c, uint8 d);
void func_8002F9C4(CODE43_WORK *wp, void *arg);
CODE43_WORK *func_80031618(void);
void func_800398E0(sint32 arg);
sint32 func_8004920C(void *pos);
void Sound_call2(sint16 id, void *args);
void ScaleMatrix(void *matrix, CODE43_VEC *scale);
sint32 rand(void);
sint32 rcos(sint32 angle);
sint32 rsin(sint32 angle);

#endif
