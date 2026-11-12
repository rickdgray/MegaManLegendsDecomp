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

long SquareRoot0(long a);
int ccos(int a);
int rsin(int a);
int rcos(int a);

#endif // PSYQ_LIBGTE_H
