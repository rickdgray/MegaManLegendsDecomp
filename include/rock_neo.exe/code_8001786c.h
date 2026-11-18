#ifndef ROCK_NEO_CODE_8001786C_H
#define ROCK_NEO_CODE_8001786C_H

#include "code_800133d8.h"

typedef void (*CODE178_FUNC)(void);

typedef struct
{
    uint16 value;
    uint16 reserved02;
} CODE178_HALF;

typedef struct
{
    sint16 value;
    sint16 reserved02;
} CODE178_SIGNED_HALF;

typedef struct
{
    sint8 routine_0, routine_1, routine_2, routine_3;
    sint8 flags04;
    uint8 reserved05[3];
    sint16 enabled;
    sint16 terminate;
    sint16 step;
    sint16 value;
} CODE178_FADE;

// The fade work at D_80098A68, as one struct (its fields are also declared singly).
#define CODE178_FADE_WORK (*(CODE178_FADE *)&D_80098A68)

typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    sint16 x, y, w, h;
} CODE178_TILE;

// Word view of a POLY_G4 (colour words written whole).
typedef struct
{
    u_long tag;
    u_long rgb0;
    u_long xy0;
    u_long rgb1;
    u_long xy1;
    u_long rgb2;
    u_long xy2;
    u_long rgb3;
    u_long xy3;
} CODE178_G4_WORDS;

extern CODE178_FUNC D_80082140[];
extern CODE178_FUNC D_800821BC[];
extern uint8 D_800821E0[][4];
extern sint8 D_80098A68;
extern sint8 D_80098A69;
extern sint8 D_80098A6A;
extern sint8 D_80098A6B;
extern RECT D_80097A28;
extern RECT D_80097A30;
extern uint16 D_800B1168[];
extern uint16 D_800AD168[];
extern uint32 D_80098868;
extern uint8 D_80098B70[];
extern sint32 D_80098824;
extern sint16 D_800C0C66;
extern sint16 D_800C0C5E;
extern sint16 D_800C0C4A;
extern uint8 D_800C0C74;
extern uint8 D_800C0C73;
extern sint16 D_800C0CF6;
extern sint16 D_800C0CEE;
extern sint16 D_800C0CDA;
extern uint8 D_800C0D04;
extern uint8 D_800C0D03;
extern POLY_FT4 D_80098E70[2][10];
extern uint16 D_80098A76;
extern CODE178_TILE D_80098A28[2];
extern DR_MODE D_80098A10[];
extern CODE178_HALF D_80097A38[];
extern CODE178_HALF D_80097A3A[];
extern uint16 D_8008F168[];
extern sint8 D_800C0C72;
extern sint8 D_800C0D02;
extern CODE178_SIGNED_HALF D_8008214C[];
extern CODE178_SIGNED_HALF D_8008214E[];
extern CODE178_HALF D_80099190[];
extern CODE178_HALF D_80099192[];
extern sint16 D_80097A44[];
extern uint16 D_80097A48[];
extern sint8 D_80098A6C;
extern uint16 D_80098A74;
extern DR_MODE D_80098160[2];
extern CODE178_TILE D_80098178[2];
extern POLY_G4 D_800991D8[2][32];
extern uint32 D_80097A60[][2];
extern CODE178_SIGNED_HALF D_80099AD8[];
extern CODE178_SIGNED_HALF D_80099ADA[];
extern uint32 D_80097A78[];
// Corner indices of the ten iris quads, four bytes each (table at 0x80082194).
// The registry only names the first record's last byte, so the table is reached
// from there.
extern uint8 D_80082197[][4];
#define CODE178_QUAD_CORNER(i, k) (D_80082197[i][(k) - 3])

void func_800196A0(void);
sint32 rcos(sint32 angle);
sint32 rsin(sint32 angle);
void func_80012ECC(void);
void func_80017E94(void);
void func_80019760(sint16 x, sint16 y, sint16 angle, sint16 scale);

void func_800176A4(void *src, void *dst, sint32 count);
void func_800176DC(void *src, void *dst, sint32 count);

#endif
