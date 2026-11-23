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

// Primitive header: 24-bit address of the next primitive + 8-bit length. The primitives type
// it `u_long *tag`, as the Library Reference does, though it holds this packed word rather than
// a pointer; code that builds it with integer operations casts (code_8002D9A0).
typedef struct
{
    unsigned addr : 24;
    unsigned len : 8;
    u_char r0, g0, b0, code;
} P_TAG;

typedef struct
{
    u_long *tag;
    u_long code[15];
} DR_ENV; // 0x40

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
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
    short w, h;              // 0x10
} SPRT;                      // 0x14

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
} SPRT_8;                    // 0x10

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    short w, h;              // 0x0c
} TILE;                      // 0x10

typedef struct
{
    u_long *tag;
    u_long code[2];
} DR_MODE; // 0x0c

typedef struct
{
    u_long *tag;
    u_long code[2];
} DR_AREA; // 0x0c

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    short x1, y1;            // 0x0c
    short x2, y2;            // 0x10
    short x3, y3;            // 0x14
} POLY_F4;                   // 0x18

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char r1, g1, b1, pad1; // 0x0c
    short x1, y1;            // 0x10
    u_char r2, g2, b2, pad2; // 0x14
    short x2, y2;            // 0x18
} POLY_G3;                   // 0x1c

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char r1, g1, b1, pad1; // 0x0c
    short x1, y1;            // 0x10
    u_char r2, g2, b2, pad2; // 0x14
    short x2, y2;            // 0x18
    u_char r3, g3, b3, pad3; // 0x1c
    short x3, y3;            // 0x20
} POLY_G4;                   // 0x24

typedef struct
{
    u_long *tag;             // 0x00
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
    u_long *tag;             // 0x00
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

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
    u_char r1, g1, b1, p1;   // 0x10
    short x1, y1;            // 0x14
    u_char u1, v1;           // 0x18
    u_short tpage;           // 0x1a
    u_char r2, g2, b2, p2;   // 0x1c
    short x2, y2;            // 0x20
    u_char u2, v2;           // 0x24
    u_short pad2;            // 0x26
} POLY_GT3;                  // 0x28

typedef struct
{
    u_long *tag;             // 0x00
    u_char r0, g0, b0, code; // 0x04
    short x0, y0;            // 0x08
    u_char u0, v0;           // 0x0c
    u_short clut;            // 0x0e
    u_char r1, g1, b1, p1;   // 0x10
    short x1, y1;            // 0x14
    u_char u1, v1;           // 0x18
    u_short tpage;           // 0x1a
    u_char r2, g2, b2, p2;   // 0x1c
    short x2, y2;            // 0x20
    u_char u2, v2;           // 0x24
    u_short pad2;            // 0x26
    u_char r3, g3, b3, p3;   // 0x28
    short x3, y3;            // 0x2c
    u_char u3, v3;           // 0x30
    u_short pad3;            // 0x32
} POLY_GT4;                  // 0x34

// Ordering-table linking. Confirmed by ROCK_NEO's screen_tile_draw.
#define getaddr(p)        (u_long)(((P_TAG *)(p))->addr)
#define setaddr(p, _addr) (((P_TAG *)(p))->addr = (u_long)(_addr))
#define addPrim(ot, p)    setaddr(p, getaddr(ot)), setaddr(ot, p)
// Links the chain p0..p1 (already linked together) into ot.
#define addPrims(ot, p0, p1) setaddr(p1, getaddr(ot)), setaddr(ot, p0)

// Primitive header setters. Same effect as PsyQ's macros, written from the layouts above.
#define setlen(p, _len)           (((P_TAG *)(p))->len = (u_long)(_len))
#define setcode(p, _code)         (((P_TAG *)(p))->code = (u_char)(_code))
#define getcode(p)                (u_char)(((P_TAG *)(p))->code)
#define getcode(p)                (u_char)(((P_TAG *)(p))->code)
#define setSprt(p)                (setlen(p, 4), setcode(p, 0x64))
#define setSprt8(p)               (setlen(p, 3), setcode(p, 0x74))
#define setTile(p)                (setlen(p, 3), setcode(p, 0x60))
#define setPolyF4(p)              (setlen(p, 5), setcode(p, 0x28))
#define setPolyFT4(p)             (setlen(p, 9), setcode(p, 0x2C))
#define setPolyG4(p)              (setlen(p, 8), setcode(p, 0x38))
#define setSemiTrans(p, abe)      ((abe) ? setcode(p, getcode(p) | 0x02) : setcode(p, getcode(p) & ~0x02))
#define setXY0(p, _x0, _y0)       ((p)->x0 = (_x0), (p)->y0 = (_y0))
#define setWH(p, _w, _h)          ((p)->w = (_w), (p)->h = (_h))
#define setRGB0(p, _r0, _g0, _b0) ((p)->r0 = (_r0), (p)->g0 = (_g0), (p)->b0 = (_b0))
#define setRGB1(p, _r1, _g1, _b1) ((p)->r1 = (_r1), (p)->g1 = (_g1), (p)->b1 = (_b1))
#define setRGB2(p, _r2, _g2, _b2) ((p)->r2 = (_r2), (p)->g2 = (_g2), (p)->b2 = (_b2))
#define setRGB3(p, _r3, _g3, _b3) ((p)->r3 = (_r3), (p)->g3 = (_g3), (p)->b3 = (_b3))
#define setXY4(p, _x0, _y0, _x1, _y1, _x2, _y2, _x3, _y3)                                                                                  \
    ((p)->x0 = (_x0), (p)->y0 = (_y0), (p)->x1 = (_x1), (p)->y1 = (_y1), (p)->x2 = (_x2), (p)->y2 = (_y2), (p)->x3 = (_x3), (p)->y3 = (_y3))
#define setUV4(p, _u0, _v0, _u1, _v1, _u2, _v2, _u3, _v3)                                                                                  \
    ((p)->u0 = (_u0), (p)->v0 = (_v0), (p)->u1 = (_u1), (p)->v1 = (_v1), (p)->u2 = (_u2), (p)->v2 = (_v2), (p)->u3 = (_u3), (p)->v3 = (_v3))

// Texture page: which 64x256 block of VRAM to texture from, and how.
//   tp:  color depth (0 = 4-bit, 1 = 8-bit, 2 = 16-bit)
//   abr: semi-transparency blend mode (0-3)
//   x:   VRAM x, a multiple of 64.  y: VRAM y, 0 or 256
#define getTPage(tp, abr, x, y) ((((tp)&0x3) << 7) | (((abr)&0x3) << 5) | (((y)&0x100) >> 4) | (((x)&0x3ff) >> 6))

// CLUT (palette) position in VRAM. x must be a multiple of 16.
#define getClut(x, y) (((y) << 6) | (((x) >> 4) & 0x3f))

u_long *ClearOTag(u_long *ot, int n);
void ClearOTagR(u_long *ot, long n);
void DrawOTag(u_long *ot);
long DrawSync(long mode);
DRAWENV *SetDefDrawEnv(DRAWENV *env, int x, int y, int w, int h);
DISPENV *SetDefDispEnv(DISPENV *disp, int x, int y, int w, int h);
DRAWENV *PutDrawEnv(DRAWENV *env);
DISPENV *PutDispEnv(DISPENV *env);
void SetDispMask(int mask);
int ResetGraph(int mode);
int ClearImage(RECT *rect, u_char r, u_char g, u_char b);
int LoadImage(RECT *recp, u_long *p);
void SetDrawMode(DR_MODE *p, int dfe, int dtd, int tpage, RECT *tw);
void SetDrawArea(DR_AREA *p, RECT *r);
u_short GetTPage(int tp, int abr, int x, int y);
u_short GetClut(int x, int y);
void AddPrim(void *ot, void *p);

#endif // PSYQ_LIBGPU_H
