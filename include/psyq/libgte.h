#ifndef PSYQ_LIBGTE_H
#define PSYQ_LIBGTE_H

/*
 * Self-written declarations for the PsyQ libgte functions this project uses.
 * Not a copy of Sony's header.
 */

#include "common.h"

typedef struct
{
    short vx, vy, vz, pad;
} SVECTOR;

typedef struct
{
    long vx, vy, vz, pad;
} VECTOR;

typedef struct
{
    short vx, vy;
} DVECTOR;

typedef struct
{
    u_char r, g, b, cd;
} CVECTOR;

typedef struct
{
    short m[3][3];
    long t[3];
} MATRIX;

void InitGeom(void);
void SetGeomOffset(long ofx, long ofy);
void SetGeomScreen(long h);
long SquareRoot0(long a);
int catan(int a);
int ccos(int a);
int rsin(int a);
int rcos(int a);
long ratan2(long x, long y);
MATRIX *RotMatrixY(long r, MATRIX *m);
MATRIX *RotMatrixYXZ(SVECTOR *r, MATRIX *m);
void SetRotMatrix(MATRIX *m);
void SetTransMatrix(MATRIX *m);
void RotTrans(SVECTOR *v0, VECTOR *v1, long *flag);
MATRIX *TransposeMatrix(MATRIX *m0, MATRIX *m1);
MATRIX *RotMatrix(SVECTOR *r, MATRIX *m);
MATRIX *MulMatrix(MATRIX *m0, MATRIX *m1);
MATRIX *ScaleMatrix(MATRIX *m, VECTOR *v);
VECTOR *ApplyMatrix(MATRIX *m, SVECTOR *v0, VECTOR *v1);
VECTOR *ApplyMatrixLV(MATRIX *m, VECTOR *v0, VECTOR *v1);
SVECTOR *ApplyMatrixSV(MATRIX *m, SVECTOR *v0, SVECTOR *v1);
void OuterProduct0(VECTOR *v0, VECTOR *v1, VECTOR *v2);
void OuterProduct12(VECTOR *v0, VECTOR *v1, VECTOR *v2);
void VectorNormal(VECTOR *v0, VECTOR *v1);
void NormalColorCol(SVECTOR *v0, CVECTOR *v1, CVECTOR *v2);
long VectorNormalS(VECTOR *v0, SVECTOR *v1);
void SetFogNear(long a, long h);
void SetFarColor(long rfc, long gfc, long bfc);
void SetBackColor(long rbk, long gbk, long bbk);
void SetColorMatrix(MATRIX *m);
void SetLightMatrix(MATRIX *m);

#endif // PSYQ_LIBGTE_H
