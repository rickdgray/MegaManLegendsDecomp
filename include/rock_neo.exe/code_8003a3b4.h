#ifndef CODE_8003A3B4_H
#define CODE_8003A3B4_H

#include "common.h"

// Local GTE shapes (no shared libgte header yet).
typedef struct
{
    sint16 m[3][3];
    sint16 pad;
    sint32 t[3];
} LIGHT_MATRIX;

typedef struct
{
    sint16 vx, vy, vz, pad;
} LIGHT_SVEC;

typedef struct
{
    uint8 r, g, b, cd;
} LIGHT_CVEC;

typedef struct
{
    sint32 vx, vy, vz, pad;
} LIGHT_VEC;

#define LIGHT_ABS(x)        (((x) < 0) ? -(x) : (x))
#define LIGHT_MAX_ABS(a, b) ((LIGHT_ABS(a) > LIGHT_ABS(b)) ? (a) : (b))

// Light state: directions, colours and back colour (defined in code_8003A3B4.c, built
// with -G32 so they are reached through $gp).
extern LIGHT_SVEC D_80098870[3];
extern LIGHT_CVEC D_80098858[3];
extern LIGHT_VEC D_80098900;

#define LIGHT_MODEL_TBL    ((uint32 *)0x8013A004)
#define LIGHT_PLAYER_PARTS ((uint32 *)0x801F6030)

extern void SetBackColor(sint32 r, sint32 g, sint32 b);
extern void SetLightMatrix(LIGHT_MATRIX *m);
extern void SetColorMatrix(LIGHT_MATRIX *m);
extern void OuterProduct0(LIGHT_VEC *v0, LIGHT_VEC *v1, LIGHT_VEC *v2);
extern void VectorNormal(LIGHT_VEC *v0, LIGHT_VEC *v1);
extern void NormalColorCol(LIGHT_SVEC *v0, LIGHT_CVEC *v1, LIGHT_CVEC *v2);

extern uint8 D_8015C006[];
extern uint8 D_8015C008[];
extern uint8 D_8013A004[];

void func_8003A480(void);
void func_8003A538(void);
void func_8003A3B4(void);
void func_8003A744(void);
void func_8003A918(uint32 *prim);

int abs(int x);

#endif // CODE_8003A3B4_H
