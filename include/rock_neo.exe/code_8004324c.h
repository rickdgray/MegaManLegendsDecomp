#ifndef ROCK_NEO_CODE_8004324C_H
#define ROCK_NEO_CODE_8004324C_H

#include "common.h"

// Local views: only the fields these helpers touch.
// Eight bytes of position; the halfword alignment gives retail's unaligned copies.
typedef struct
{
    uint16 x, y, z, pad;
} CODE43_POS8;

typedef struct
{
    sint16 vx, vy, vz, pad;
} CODE43_SVECTOR;

// Player slot as seen by the HP helper (stride 0x5F4).
typedef struct
{
    uint8 reserved00[0x6E];
    uint16 hp_6e;
    uint8 reserved70[0x40];
    sint16 hp_max_b0;
    uint8 reservedB2[0x4FC - 0xB2];
    sint8 speed_idx_4fc;
    uint8 reserved4FD;
    sint8 speed_idx_4fe;
    uint8 reserved4FF[0x5F4 - 0x4FF];
} CODE43_PLAYER;

// Target record returned by func_80036294.
typedef struct
{
    uint8 reserved000[0x14];
    CODE43_POS8 pos_14;
    uint8 reserved1C[0x198 - 0x1C];
    sint32 state_198;
    uint8 reserved19C[0x400 - 0x19C];
    CODE43_POS8 pos_400;
    uint8 reserved408[0x10];
    CODE43_POS8 pos_418;
} CODE43_TARGET;

// Effect record returned by func_80031618.
typedef struct
{
    uint8 flags_0;
    uint8 reserved01;
    uint8 kind_2;
    uint8 value_3;
    uint8 reserved04[8];
    sint8 value_c;
    uint8 reserved0d[0xF];
    uint16 x_1c;
    uint16 y_1e;
    uint16 z_20;
} CODE43_FX;

typedef struct
{
    sint32 vx, vy, vz, pad;
} CODE43_VECTOR;

typedef struct
{
    sint16 m[3][3];
    sint16 pad;
    sint32 t[3];
} CODE43_MATRIX;

typedef struct
{
    uint8 flags_0;
    uint8 value_1;
    uint8 reserved02;
    uint8 value_3;
    uint8 reserved04[2];
    uint8 flags_6;
    uint8 reserved07;
    uint8 routine_8;
    uint8 routine_9;
    uint8 mode_a;
    uint8 timer_b;
    sint8 index_c;
    sint8 bit_d;
    sint8 mode_e;
    uint8 reserved0f[5];
    CODE43_POS8 pos_14;
    union
    {
        CODE43_VECTOR v;
        struct
        {
            uint16 lo_1c;
            uint16 x_1e;
            uint16 lo_20;
            uint16 y_22;
            uint16 lo_24;
            uint16 z_26;
        } h;
    } pos_1c;
    CODE43_POS8 pos_2c;
    CODE43_VECTOR vec_34;
    sint16 vel_44;
    sint16 vel_46;
    sint16 vel_48;
    uint8 reserved4a[2];
    sint16 value_4c;
    sint16 value_4e;
    sint16 value_50;
    uint8 reserved52[0x12];
    uint16 angle_64;
    uint8 reserved66[0x12];
    uint8 *ptr_78;
    sint16 value_7c;
    uint8 reserved7e[10];
    uint32 word_88;
    uint32 word_8c;
    uint16 x_90;
    uint16 y_92;
    uint16 z_94;
    uint8 value_96;
    uint8 value_97;
    uint16 value_98;
    uint16 value_9a;
    uint8 reserved9c[8];
    CODE43_SVECTOR pos_a4;
    uint8 reservedac[0x10];
    union
    {
        struct
        {
            sint16 x_bc;
            sint16 y_be;
            sint16 z_c0;
            uint16 pad_c2;
        } h;
        struct
        {
            uint32 w_bc;
            uint32 w_c0;
        } w;
    } target;
    uint32 word_c4;
    uint32 word_c8;
} CODE43_WORK;

// Byte view for the flag test.
typedef struct
{
    uint8 reserved00[0x174];
    sint8 flags_174;
    uint8 reserved175[2];
    sint8 value_177;
} CODE43_FLAGS;

typedef void (*CODE43_FUNC)(CODE43_WORK *wp);

// Game_work as seen by the money and HP helpers.
typedef struct
{
    uint8 reserved00[0x1C];
    uint32 money_1c;
    uint32 spent_20;
    uint32 spent_24;
    uint8 reserved28[0x24];
    uint32 hp_lost_4c;
    uint8 reserved50[0x1C0];
} CODE43_GAME;

extern CODE43_GAME Game_work;
extern CODE43_PLAYER Player_work[];
extern uint8 D_80097DA0[];
extern uint32 D_80097DAC[];
extern uint8 D_80097DCC[];
extern uint8 D_80097DD4[];
extern CODE43_FUNC D_8008A0CC[];
extern CODE43_FUNC D_8008A0D8[];

#define CODE43_MONEY_MAX 999999

void Sound_call2(sint16 id, void *args);
CODE43_TARGET *func_80036294(uint8 id);
CODE43_FX *func_80031618(void);
void func_80031930(CODE43_WORK *wp);
void func_80051BAC(CODE43_WORK *wp);
sint32 func_80037694(CODE43_WORK *wp, sint32 arg);
void func_800354E0(sint32 bit);
void func_80043740(CODE43_WORK *wp);
sint32 func_80037634(void *player, sint32 arg);
void VectorNormalS(CODE43_VECTOR *v, CODE43_SVECTOR *out);
#ifdef __wasm32__
CODE43_SVECTOR *func_80033F04(CODE43_SVECTOR *out, CODE43_SVECTOR *dir, CODE43_SVECTOR *cur, sint32 a3,
                   sint32 a4);
#else
void func_80033F04(CODE43_SVECTOR *out, CODE43_SVECTOR *dir, CODE43_SVECTOR *cur, sint32 a3,
                   sint32 a4);
#endif
void func_80043DF8(CODE43_WORK *wp, CODE43_MATRIX *mtx);
void func_8005D97C(void);
sint16 func_80039B80(void);
void RotMatrixYXZ(CODE43_SVECTOR *r, CODE43_MATRIX *m);
void ApplyMatrix(CODE43_MATRIX *m, CODE43_SVECTOR *v, CODE43_VECTOR *out);
void func_800435F8(CODE43_WORK *wp);
void func_80043E78(CODE43_WORK *wp);
void func_80043E00(CODE43_WORK *wp, sint32 value);
sint32 func_800375D4(void *player, sint32 arg);
#ifdef __wasm32__
sint32 func_8003430C(void *pos_a, sint32 a1, void *pos_b, sint32 a3, sint32 a4, sint32 a5, sint32 a6,
                   sint32 *a7, sint32 a8, sint32 a9, sint32 a10);
#else
void func_8003430C(void *pos_a, sint32 a1, void *pos_b, sint32 a3, sint32 a4, sint32 a5, sint32 a6,
                   sint32 *a7, sint32 a8, sint32 a9, sint32 a10);
#endif

#endif
