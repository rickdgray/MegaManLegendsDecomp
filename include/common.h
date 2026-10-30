#ifndef COMMON_H
#define COMMON_H
#include "include_asm.h"

// Fixed-width names (as used by m2c output).
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

// Capcom's original names from exposed source.
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;

// PsyQ-style names. On the R3000, long is 32 bits.
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif // COMMON_H
