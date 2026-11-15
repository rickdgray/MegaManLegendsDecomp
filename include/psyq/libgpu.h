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
    u_long tag;              // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    short w, h;              // 0x0c
} TILE;                      // 0x10

typedef struct
{
    u_long tag;
    u_long code[2];
} DR_MODE; // 0x0c

typedef struct
{
    u_long tag;              // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
    short x1, y1;            // 0x10
    u_char u1, v1;           // 0x14
    u_short tpage;           // 0x16
    short x2, y2;            // 0x18
    u_char u2, v2;           // 0x1c
    u_short pad1;            // 0x1e
} POLY_FT3;                  // 0x20

typedef struct
{
    u_long tag;              // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
    short x1, y1;            // 0x10
    u_char u1, v1;           // 0x14
    u_short tpage;           // 0x16
    short x2, y2;            // 0x18
    u_char u2, v2;           // 0x1c
    u_short pad1;            // 0x1e
    short x3, y3;            // 0x20
    u_char u3, v3;           // 0x24
    u_short pad2;            // 0x26
} POLY_FT4;                  // 0x28

// Ordering-table linking. Confirmed by ROCK_NEO's screen_tile_draw.
#define getaddr(p)        (u_long)(((P_TAG *)(p))->addr)
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u_long)(_addr))
#define addPrim(ot, p)    setaddr(p, getaddr(ot)), setaddr(ot, p)

// Primitive header setters. Same effect as PsyQ's macros, written from the layouts above.
#define setlen(p, _len)           (((P_TAG *)(p))->len = (u_long)(_len))
#define setcode(p, _code)         (((P_TAG *)(p))->code = (u_char)(_code))
#define getcode(p)                (u_char)(((P_TAG *)(p))->code)
#define setSprt(p)                (setlen(p, 4), setcode(p, 0x64))
#define setTile(p)                (setlen(p, 3), setcode(p, 0x60))
#define setSemiTrans(p, abe)      ((abe) ? setcode(p, getcode(p) | 0x02) : setcode(p, getcode(p) & ~0x02))
#define setWH(p, _w, _h)          ((p)->w = (_w), (p)->h = (_h))
#define setRGB0(p, _r0, _g0, _b0) ((p)->r0 = (_r0), (p)->g0 = (_g0), (p)->b0 = (_b0))

// Texture page: which 64x256 block of VRAM to texture from, and how.
//   tp:  color depth (0 = 4-bit, 1 = 8-bit, 2 = 16-bit)
//   abr: semi-transparency blend mode (0-3)
//   x:   VRAM x, a multiple of 64.  y: VRAM y, 0 or 256
#define getTPage(tp, abr, x, y) ((((tp)&0x3) << 7) | (((abr)&0x3) << 5) | (((y)&0x100) >> 4) | (((x)&0x3ff) >> 6))

// CLUT (palette) position in VRAM. x must be a multiple of 16.
#define getClut(x, y) (((y) << 6) | (((x) >> 4) & 0x3f))

u_long *ClearOTag(u_long *ot, int n);
void ClearOTagR(u_long *ot, long n);
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

#endif // PSYQ_LIBGPU_H
