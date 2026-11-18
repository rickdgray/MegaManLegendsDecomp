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

// Textured and shaded four-vertex primitives; offsets checked against callers.
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    u_char u0, v0;
    u_short clut;
    short x1, y1;
    u_char u1, v1;
    u_short tpage;
    short x2, y2;
    u_char u2, v2;
    u_short pad2;
    short x3, y3;
    u_char u3, v3;
    u_short pad3;
} POLY_FT4; // 0x28

typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    u_char r1, g1, b1, pad1;
    short x1, y1;
    u_char r2, g2, b2, pad2;
    short x2, y2;
    u_char r3, g3, b3, pad3;
    short x3, y3;
} POLY_G4; // 0x24

typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short x1, y1;
    short x2, y2;
    short x3, y3;
} POLY_F4; // 0x18

// Ordering-table linking. Suspected to match PsyQ's macros; confirm when a
// function using addPrim matches.
#define getaddr(p)        (u_long)(((P_TAG *)(p))->addr)
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u_long)(_addr))
#define addPrim(ot, p)    setaddr(p, getaddr(ot)), setaddr(ot, p)

// Links the chain p0..p1 in front of ot's entry (PsyQ's addPrims; matched in func_800640F0).
#define addPrims(ot, p0, p1) setaddr(p1, getaddr(ot)), setaddr(ot, p0)

// Primitive header setters. Same effect as PsyQ's macros, written from the layouts above.
#define setlen(p, _len)   (((P_TAG *)(p))->len = (u_long)(_len))
#define setcode(p, _code) (((P_TAG *)(p))->code = (u_char)(_code))
#define setPolyFT4(p)     (setlen(p, 9), setcode(p, 0x2C))
#define setPolyG4(p)      (setlen(p, 8), setcode(p, 0x38))
#define setPolyF4(p)      (setlen(p, 5), setcode(p, 0x28))
#define setSprt(p)        (setlen(p, 4), setcode(p, 0x64))

// Colour setter (PsyQ's setRGB0; matched in func_80017B24).
#define setRGB0(p, _r0, _g0, _b0) (p)->r0 = (_r0), (p)->g0 = (_g0), (p)->b0 = (_b0)

// Texture page: which 64x256 block of VRAM to texture from, and how.
//   tp:  color depth (0 = 4-bit, 1 = 8-bit, 2 = 16-bit)
//   abr: semi-transparency blend mode (0-3)
//   x:   VRAM x, a multiple of 64.  y: VRAM y, 0 or 256
#define getTPage(tp, abr, x, y)                                                                    \
    ((((tp) & 0x3) << 7) | (((abr) & 0x3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3ff) >> 6))

// CLUT (palette) position in VRAM. x must be a multiple of 16.
#define getClut(x, y) (((y) << 6) | (((x) >> 4) & 0x3f))

u_short GetTPage(int tp, int abr, int x, int y);
u_short GetClut(int x, int y);
void AddPrim(void *ot, void *p);

u_long *ClearOTag(u_long *ot, int n);
u_long *ClearOTagR(u_long *ot, int n);
void DrawOTag(u_long *p);
int DrawSync(int mode);
DRAWENV *SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h);
DISPENV *SetDefDispEnv(DISPENV *env, int x, int y, int w, int h);
DRAWENV *PutDrawEnv(DRAWENV *env);
DISPENV *PutDispEnv(DISPENV *env);
void SetDispMask(int mask);
int ResetGraph(int mode);
int ClearImage(RECT *rect, u_char r, u_char g, u_char b);
int LoadImage(RECT *rect, u_long *p);
void SetDrawMode(DR_MODE *p, int dfe, int dtd, int tpage, RECT *tw);

// Drawing-area primitive (tag plus two command words).
typedef struct
{
    u_long tag;
    u_long code[2];
} DR_AREA; // 0x0c

void SetDrawArea(DR_AREA *p, RECT *r);

#endif // PSYQ_LIBGPU_H
