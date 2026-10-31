#ifndef PSYQ_LIBGPU_H
#define PSYQ_LIBGPU_H

/*
 * Self-written declarations for the PsyQ libgpu types and functions this
 * project uses. Layouts are checked against the binary (offsets noted).
 * Not a copy of Sony's header.
 */

#include "common.h"

typedef struct
{
    short x, y, w, h;
} RECT;

// Primitive header: 24-bit address of the next primitive + 8-bit length.
typedef struct
{
    unsigned addr : 24;
    unsigned len : 8;
    u_char r0, g0, b0, code;
} P_TAG;

typedef struct
{
    u_long tag;
    u_long code[15];
} DR_ENV; // 0x40 */

typedef struct
{
    RECT clip;             // 0x00
    short ofs[2];          // 0x08
    RECT tw;               // 0x0c
    u_short tpage;         // 0x14
    u_char dtd, dfe, isbg; // 0x16
    u_char r0, g0, b0;     // 0x19
    DR_ENV dr_env;         // 0x1c
} DRAWENV;                 // 0x5c

typedef struct
{
    RECT disp;                           // 0x00
    RECT screen;                         // 0x08
    u_char isinter, isrgb24, pad0, pad1; // 0x10
} DISPENV;                               // 0x14

typedef struct
{
    u_long tag;              // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
    short w, h;              // 0x10
} SPRT;                      // 0x14

typedef struct
{
    u_long tag;
    u_long code[2];
} DR_MODE; // 0x0c

// Ordering-table linking. Suspected to match PsyQ's macros; confirm when a
// function using addPrim matches.
#define getaddr(p) (u_long)(((P_TAG *)(p))->addr)
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u_long)(_addr))
#define addPrim(ot, p) setaddr(p, getaddr(ot)), setaddr(ot, p)

// Primitive header setters. Same effect as PsyQ's macros, written from the layouts above.
#define setlen(p, _len) (((P_TAG *)(p))->len = (u_long)(_len))
#define setcode(p, _code) (((P_TAG *)(p))->code = (u_char)(_code))
#define setSprt(p) (setlen(p, 4), setcode(p, 0x64))

// Texture page: which 64x256 block of VRAM to texture from, and how.
//   tp:  color depth (0 = 4-bit, 1 = 8-bit, 2 = 16-bit)
//   abr: semi-transparency blend mode (0-3)
//   x:   VRAM x, a multiple of 64.  y: VRAM y, 0 or 256
#define getTPage(tp, abr, x, y) \
    ((((tp) & 0x3) << 7) | (((abr) & 0x3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3ff) >> 6))

// CLUT (palette) position in VRAM. x must be a multiple of 16.
#define getClut(x, y) (((y) << 6) | (((x) >> 4) & 0x3f))

u_long *ClearOTag(u_long *ot, int n);
void DrawOTag(u_long *p);
int DrawSync(int mode);
DRAWENV *SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h);
DISPENV *SetDefDispEnv(DISPENV *env, int x, int y, int w, int h);
DRAWENV *PutDrawEnv(DRAWENV *env);
DISPENV *PutDispEnv(DISPENV *env);
void SetDispMask(int mask);
int LoadImage(RECT *rect, u_long *p);
void SetDrawMode(DR_MODE *p, int dfe, int dtd, int tpage, RECT *tw);

#endif // PSYQ_LIBGPU_H
