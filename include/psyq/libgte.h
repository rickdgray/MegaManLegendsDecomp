#ifndef PSYQ_LIBGTE_H
#define PSYQ_LIBGTE_H

#include "common.h"

// Self-written PsyQ GTE types and prototypes (libgte), offsets checked against the binaries.
// ROCK_NEO.EXE's own files still declare local views of these; the overlays use this header.

typedef struct
{
    short m[3][3];
    long t[3];
} MATRIX;

typedef struct
{
    long vx, vy, vz, pad;
} VECTOR;

typedef struct
{
    short vx, vy, vz, pad;
} SVECTOR;

typedef struct
{
    u_char r, g, b, cd;
} CVECTOR;

MATRIX *RotMatrix(SVECTOR *r, MATRIX *m);
MATRIX *RotMatrixY(long r, MATRIX *m);
MATRIX *RotMatrixYXZ(SVECTOR *r, MATRIX *m);
MATRIX *ScaleMatrix(MATRIX *m, VECTOR *v);
MATRIX *MulMatrix(MATRIX *m0, MATRIX *m1);
MATRIX *MulMatrix2(MATRIX *m0, MATRIX *m1);
VECTOR *ApplyMatrix(MATRIX *m, SVECTOR *v0, VECTOR *v1);
void VectorNormalS(VECTOR *v0, SVECTOR *v1);
int rsin(int a);
int rcos(int a);
int ratan2(int y, int x);
long SquareRoot0(long a);

#endif // PSYQ_LIBGTE_H
