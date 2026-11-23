#ifndef CODE_8003A3B4_H
#define CODE_8003A3B4_H

// code_8003A3B4.c: GTE lighting of the stage and SUPPORT models (not identified yet; rename with
// the file).

#include "common.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
// Whichever of a and b has the larger magnitude (each argument expands more than once).
#define MAX_ABS(a, b) (ABS(a) > ABS(b) ? (a) : (b))

void func_8003A3B4(void); // called from scene (func_8001F23C)
void func_8003A744(void); // called from game (func_80016160)

#endif // CODE_8003A3B4_H
