// C version of func_8002E3D0 for the native port.
//
// In the matching build this routine is Capcom's hand-written assembly (subsegment
// asm_8002E3D0, rock_neo.exe.yaml): a hand-scheduled mesh drawer that transforms a detail
// level's vertices three at a time with RTPT into the scratchpad tables, then emits
// textured gouraud triangles (POLY_GT3-sized, 8 words) and quads (10 words) for front-facing
// faces into the ordering table. The C below is the plain-local draft that the matching side
// wrote before the routine was classified as hand-written (git history of
// src/rock_neo.exe/code_8002D9A0.c, before commit 938e777): it matched retail's face loops
// instruction for instruction except register numbers, so it is functionally the same code.
// Like the original, the vertex loop loads the six words after the last batch (a read past
// the end of the vertex array) before it tests the count.
#include "common.h"
#include "rock_neo.exe/code_8002d9a0.h"
#include "rock_neo.exe/gte_inline.h"

void func_8002E3D0(C8002D9A0_LOD *lod)
{
    uint32 otz;
    uint32 *base;
    uint16 *zbase;
    uint32 *sxy;
    uint16 *sz;
    uint32 *v;
    uint32 *p;
    uint32 *ot;
    C8002D9A0_FACE *f;
    uint32 tex;
    uint32 color;
    uint32 i;
    uint32 n;
    uint32 nv;
    uint32 a;
    uint32 b;
    uint32 c;
    uint32 d;
    sint32 clip;
    uint32 w0, w1, w2, w3, w4, w5;
    uint32 t;
    uint32 tag;
    uint32 mask;
    uint32 **otp;
    uint32 hi;
    uint32 lo;

    base  = D_1F800000.sxy;
    mask  = 0xFFFFFF;
    zbase = D_1F800000.sz;
    nv    = lod->n_verts;
    tex   = lod->tex;
    v     = lod->verts;
    if (nv == 0)
    {
        return;
    }
    GTE_LDV3C(v);
    sz  = zbase;
    sxy = base;
    i   = 0;
vertex_loop:
    GTE_RTPT();
    v += 6;
    w0 = v[0];
    w1 = v[1];
    w2 = v[2];
    w3 = v[3];
    w4 = v[4];
    w5 = v[5];
    GTE_SWC2_OFF(12, 0, sxy);
    GTE_SWC2_OFF(13, 4, sxy);
    GTE_SWC2_OFF(14, 8, sxy);
    C8002D9A0_GTE_GET(17, t);
    sxy += 3;
    sz[0] = t;
    C8002D9A0_GTE_GET(18, t);
    i += 3;
    sz[1] = t;
    C8002D9A0_GTE_GET(19, t);
    GTE_MTC2(0, w0);
    sz[2] = t;
    GTE_MTC2(1, w1);
    GTE_MTC2(2, w2);
    GTE_MTC2(3, w3);
    GTE_MTC2(4, w4);
    GTE_MTC2(5, w5);
    sz += 3;
    if (i < nv)
    {
        goto vertex_loop;
    }
    tag   = 0x07000000;
    color = C8002D9A0_REL(base, -0x1C, uint32) | 0x24000000;
    n     = lod->n_tri;
    f     = lod->tri;
    if (n == 0)
    {
        goto quads;
    }
    otp = &C8002D9A0_REL(base, -0xC4, uint32 *);
    hi  = tex & 0xFFFF0000;
    lo  = tex << 16;
tri_loop:
    a = f->index & 0xFF;
    b = (f->index >> 8) & 0xFF;
    c = (f->index >> 16) & 0xFF;
    C8002D9A0_GTE_LDSXY3(&base[a], &base[b], &base[c]);
    C8002D9A0_GTE_NCLIP();
    n--;
    C8002D9A0_GTE_GET_NOP(24, clip);
    if (clip > 0)
    {
        p                                    = C8002D9A0_REL(base, -0x90, uint32 *);
        C8002D9A0_REL(base, -0x90, uint32 *) = p + 8;
        GTE_SWC2_OFF(12, 8, p);
        GTE_SWC2_OFF(13, 16, p);
        GTE_SWC2_OFF(14, 24, p);
        C8002D9A0_GTE_LDSZ3(zbase[a], zbase[b], zbase[c]);
        C8002D9A0_GTE_AVSZ3();
        GTE_SWC2(7, &otz);
        ot   = *otp + (otz >> 1);
        p[0] = tag | *ot;
        *ot  = (uint32)p & mask;
        p[1] = color;
        p[3] = hi | f->uv[0] | C8002D9A0_REL(base, -0x20, uint32);
        p[5] = lo | f->uv[1] | 0x200000;
        p[7] = f->uv[2];
    }
    f++;
    if (n != 0)
    {
        goto tri_loop;
    }
quads:
    tag   = 0x09000000;
    color = C8002D9A0_REL(base, -0x1C, uint32) | 0x2C000000;
    n     = lod->n_quad;
    f     = lod->quad;
    if (n == 0)
    {
        return;
    }
    otp = &C8002D9A0_REL(base, -0xC4, uint32 *);
    hi  = tex & 0xFFFF0000;
quad_loop:
    a = f->index & 0xFF;
    b = (f->index >> 8) & 0xFF;
    c = (f->index >> 16) & 0xFF;
    d = f->index >> 24;
    C8002D9A0_GTE_LDSXY3(&base[a], &base[b], &base[c]);
    C8002D9A0_GTE_NCLIP();
    n--;
    C8002D9A0_GTE_GET_NOP(24, clip);
    if (clip > 0)
    {
        p                                    = C8002D9A0_REL(base, -0x90, uint32 *);
        C8002D9A0_REL(base, -0x90, uint32 *) = p + 10;
        GTE_SWC2_OFF(12, 8, p);
        GTE_SWC2_OFF(13, 16, p);
        GTE_SWC2_OFF(14, 24, p);
        p[8] = base[d];
        C8002D9A0_GTE_LDSZ4(zbase[a], zbase[b], zbase[c], zbase[d]);
        C8002D9A0_GTE_AVSZ4();
        GTE_SWC2(7, &otz);
        ot   = *otp + (otz >> 1);
        p[0] = tag | *ot;
        *ot  = (uint32)p & mask;
        p[1] = color;
        p[3] = hi | f->uv[0] | C8002D9A0_REL(base, -0x20, uint32);
        p[5] = (tex << 16) | f->uv[1] | 0x200000;
        p[7] = f->uv[2];
        p[9] = f->uv[3];
    }
    f++;
    if (n != 0)
    {
        goto quad_loop;
    }
}
