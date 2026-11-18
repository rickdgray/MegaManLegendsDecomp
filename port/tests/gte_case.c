// GTE checks written with the game's own macros (include/rock_neo.exe/gte_inline.h), compiled
// through the same pipeline as the game files: preprocess, rewrite the inline MIPS
// (port/tools/asm_rewrite.py), interpret at run time (port/runtime/mips_asm.c).
#include "common.h"
#include "rock_neo.exe/gte_inline.h"

typedef struct
{
    sint16 m[3][3];
    sint16 pad;
    sint32 t[3];
} GTE_CASE_MATRIX;

typedef struct
{
    sint16 vx, vy, vz, pad;
} GTE_CASE_SVECTOR;

// Rotation-translation of v by mat: out = TR + RT * v / 4096 (GTE_RTV0 is mvmva with cv=TR).
void gte_case_rtv0(GTE_CASE_MATRIX *mat, GTE_CASE_SVECTOR *v, sint32 *out)
{
    GTE_SET_MATRIX(mat);
    GTE_LDV0(v);
    GTE_RTV0();
    GTE_STLVNL(out);
}

// Perspective transform of v; returns SXY2 and writes SZ3 to *sz.
uint32 gte_case_rtps(GTE_CASE_MATRIX *mat, GTE_CASE_SVECTOR *v, sint32 h, sint32 ofx, sint32 ofy,
                     sint32 *sz)
{
    uint32 sxy;

    GTE_SET_MATRIX(mat);
    GTE_CTC2(24, ofx);
    GTE_CTC2(25, ofy);
    GTE_CTC2(26, h);
    GTE_LDV0(v);
    GTE_RTPS();
    GTE_MFC2(14, sxy);
    GTE_MFC2(19, *sz);
    return sxy;
}

// Normal clip of three screen points (positive = clockwise in screen space).
sint32 gte_case_nclip(uint32 a, uint32 b, uint32 c)
{
    sint32 r;

    GTE_NCLIP(a, b, c, &r);
    return r;
}
