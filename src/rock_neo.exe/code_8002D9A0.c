#include "common.h"
#include "code_8002D9A0.h"
#include "code_80027678.h"
#include "code_8002E7A8.h"
#include "psyq/gtemac.h"
#include "psyq/inline_c.h"
#include "psyq/libgpu.h"
#include "scratch.h"

void billboard_draw(void)
{
    VECTOR pos;
    SVECTOR v[3];
    DVECTOR sxy0;
    DVECTOR sxy1;
    CVECTOR rgb;
    BILLBOARD *p;
    u_long *ot;
    sint32 r;
    uint32 n;
    uint32 i;

    n          = D_800988FC;
    D_800988FC = 0;
    for (i = 0; i < n; i++)
    {
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_SetTransMatrix(&Scratch_view_mtx);
        *(sint32 *)&v[0].vx = D_800BE6D8[i]->xy0;
        *(sint32 *)&v[0].vz = D_800BE6D8[i]->xy1;
        gte_ldv0(&v[0]);
        gte_rt();
        gte_stlvnl(&pos);
        if (Scratch_fog_0 * 4 >= pos.vz && pos.vz >= 0xC0)
        {
            gte_SetRotMatrix(&D_80097CD4);
            gte_SetTransMatrix(&D_80097CD4);
            p       = D_800BE6D8[i];
            r       = p->xy2;
            v[2].vx = pos.vx;
            v[2].vy = pos.vy;
            v[0].vz = v[1].vz = v[2].vz = pos.vz;
            v[0].vx                     = pos.vx - r;
            v[0].vy                     = pos.vy - r;
            v[1].vx                     = pos.vx + r;
            v[1].vy                     = pos.vy + r;
            gte_ldv3c(v);
            gte_rtpt();
            ot = &Scratch_ot[pos.vz >> 3];
            if (D_800BE6D8[i]->xy3 & BILLBOARD_NO_FOG) // re-read through the list, not p
            {
                p->tag = *ot | 0x09000000;
                *ot    = (u_long)p & 0xFFFFFF;
            }
            else
            {
                Scratch_clut_bits = D_800C0DC0.b[(pos.vz / 512) & 0x1F] << 16;
                gte_ldrgb(&D_800BE6D8[i]->rgbc);
                gte_dpcs();
                p->tag = *ot | 0x09000000;
                *ot    = (u_long)p & 0xFFFFFF;
                gte_strgb(&rgb);
                p->rgbc = *(u_long *)&rgb;
                p->uv0_clut |= Scratch_clut_bits;
            }
            gte_stsxy0(&p->xy0);
            gte_stsxy0(&sxy0);
            gte_stsxy1(&p->xy3);
            gte_stsxy1(&sxy1);
            p->xy1 = (sxy0.vy << 16) | (u_short)sxy1.vx;
            p->xy2 = (sxy1.vy << 16) | (u_short)sxy0.vx;
        }
    }
}

BLK_ENT func_8002DC84(BLK_SRC *src, sint32 blk, sint32 idx)
{
    BLK_ENT val;
    uint32 *p;
    uint32 w;

    p         = src->blk_tbl[blk];
    w         = p[0];
    val.head  = w;
    p         = &(p + (w & 0xFF) + 1)[idx * 2]; // skip the header, then to entry idx
    val.addr0 = (p[0] & 0xFFFFFF) | 0x80000000;
    w         = p[1];
    val.hi    = w >> 24;
    val.addr1 = (w & 0xFFFFFF) | 0x80000000;
    return val;
}

BYTES8 func_8002DD1C(WORDS2 *tbl, sint32 idx)
{
    BYTES8 val;

    ((sint32 *)&val)[0] = tbl[idx].w[0];
    ((sint32 *)&val)[1] = tbl[idx].w[1];
    return val;
}

BYTES4 func_8002DD68(WORDS4 *tbl, sint32 idx)
{
    BYTES4 val;

    *(sint32 *)&val = tbl[idx].head;
    return val;
}

BYTES12 func_8002DDA0(WORDS4 *tbl, sint32 idx)
{
    BYTES12 val;

    ((sint32 *)&val)[0] = tbl[idx].body.w[0];
    ((sint32 *)&val)[1] = tbl[idx].body.w[1];
    ((sint32 *)&val)[2] = tbl[idx].body.w[2];
    return val;
}

void func_8002DE04(WORDS2 *tbl, sint32 idx, WORDS2 *val)
{
    tbl[idx].w[0] = val->w[0];
    tbl[idx].w[1] = val->w[1];
}

void func_8002DE20(WORDS4 *tbl, sint32 idx, sint32 *val)
{
    tbl[idx].head = *val;
}

void func_8002DE34(WORDS4 *tbl, sint32 idx, WORDS3 *val)
{
    tbl[idx].body.w[0] = val->w[0];
    tbl[idx].body.w[1] = val->w[1];
    tbl[idx].body.w[2] = val->w[2];
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002D9A0", func_8002DE5C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002D9A0", func_8002DEEC);

#ifdef NON_MATCHING
// func_8002E3D0 reaches all its scratchpad data from one pointer, sxy (Scratch_sxy): the
// target addresses each of these relative to the register holding 0x1F800100, which GCC only
// does when the source derives them from that pointer (literal addresses get their own lui).
#define SXY_SZ(sxy)        ((uint16 *)((sxy) + 0x80)) // Scratch_sz
#define SXY_PRIM_PTR(sxy)  (*(uint8 **)((sxy)-0x24))  // Map_prim_ptr
#define SXY_CLUT_BITS(sxy) (*(u_long *)((sxy)-8))     // Scratch_clut_bits
#define SXY_RGBC(sxy)      (*(u_long *)((sxy)-7))     // Scratch_rgbc
#define SXY_OT(sxy)        (*(u_long **)((sxy)-0x31)) // Scratch_ot

void func_8002E3D0(MESH *m)
{
    long *sxy;
    POLY_FT3 *p3;
    POLY_FT4 *p4;
    MESH_FACE *f;
    long *vp;
    u_long *ot;
    u_long otz;
    long opz;
    long v0, v1, v2, v3, v4, v5;
    uint32 ct;
    uint32 code;
    uint32 sz;
    uint32 w;
    uint32 i0, i1, i2, i3;
    uint32 n;
    uint32 i;

    sxy = Scratch_sxy;
    n   = m->n_vtx;
    ct  = m->clut_tpage;
    vp  = (long *)m->vtx;
    if (n == 0)
    {
        return;
    }

    // Project the vertices three at a time, loading the next three while RTPT runs.
    gte_ldv3c(vp);
    for (i = 0; i < n; i += 3)
    {
        gte_rtpt_b();
        vp += 6;
        v0 = vp[0];
        v1 = vp[1];
        v2 = vp[2];
        v3 = vp[3];
        v4 = vp[4];
        v5 = vp[5];
        gte_stsxy3c(&sxy[i]);
        gte_getSZ1(sz);
        SXY_SZ(sxy)[i] = sz;
        gte_getSZ2(sz);
        SXY_SZ(sxy)[i + 1] = sz;
        gte_getSZ3(sz);
        SXY_SZ(sxy)[i + 2] = sz;
        gte_ldVXY0(v0);
        gte_ldVZ0(v1);
        gte_ldVXY1(v2);
        gte_ldVZ1(v3);
        gte_ldVXY2(v4);
        gte_ldVZ2(v5);
    }

    // Triangles that face the camera.
    code = SXY_RGBC(sxy) | 0x24000000; // POLY_FT3
    n    = m->n_tri;
    f    = m->tri;
    for (; n != 0; n--, f++)
    {
        w  = f->idx;
        i0 = w & 0xFF;
        i1 = (w >> 8) & 0xFF;
        i2 = (w >> 16) & 0xFF;
        gte_ldsxy3(&sxy[i0], &sxy[i1], &sxy[i2]);
        gte_nclip();
        read_opz(opz);
        if (opz > 0)
        {
            p3 = (POLY_FT3 *)SXY_PRIM_PTR(sxy);
            SXY_PRIM_PTR(sxy) += sizeof(POLY_FT3);
            gte_stsxy3_ft3(p3);
            gte_ldsz3(SXY_SZ(sxy)[i0], SXY_SZ(sxy)[i1], SXY_SZ(sxy)[i2]);
            gte_avsz3();
            gte_stotz(&otz);
            ot                 = &SXY_OT(sxy)[otz >> 1];
            p3->tag            = *ot | 0x07000000;
            *ot                = (u_long)p3 & 0xFFFFFF;
            *(u_long *)&p3->r0 = code;
            *(u_long *)&p3->u0 = (ct & 0xFFFF0000) | f->uv[0] | SXY_CLUT_BITS(sxy);
            *(u_long *)&p3->u1 = (ct << 16) | f->uv[1] | (getTPage(0, 1, 0, 0) << 16);
            *(u_long *)&p3->u2 = f->uv[2];
        }
    }

    // Quads that face the camera.
    code = SXY_RGBC(sxy) | 0x2C000000; // POLY_FT4
    n    = m->n_quad;
    f    = m->quad;
    for (; n != 0; n--, f++)
    {
        w  = f->idx;
        i0 = w & 0xFF;
        i1 = (w >> 8) & 0xFF;
        i2 = (w >> 16) & 0xFF;
        i3 = w >> 24;
        gte_ldsxy3(&sxy[i0], &sxy[i1], &sxy[i2]);
        gte_nclip();
        read_opz(opz);
        if (opz > 0)
        {
            p4 = (POLY_FT4 *)SXY_PRIM_PTR(sxy);
            SXY_PRIM_PTR(sxy) += sizeof(POLY_FT4);
            gte_stsxy3_ft4(p4);
            *(long *)&p4->x3 = sxy[i3];
            gte_ldsz4(SXY_SZ(sxy)[i0], SXY_SZ(sxy)[i1], SXY_SZ(sxy)[i2], SXY_SZ(sxy)[i3]);
            gte_avsz4();
            gte_stotz(&otz);
            ot                 = &SXY_OT(sxy)[otz >> 1];
            p4->tag            = *ot | 0x09000000;
            *ot                = (u_long)p4 & 0xFFFFFF;
            *(u_long *)&p4->r0 = code;
            *(u_long *)&p4->u0 = (ct & 0xFFFF0000) | f->uv[0] | SXY_CLUT_BITS(sxy);
            *(u_long *)&p4->u1 = (ct << 16) | f->uv[1] | (getTPage(0, 1, 0, 0) << 16);
            *(u_long *)&p4->u2 = f->uv[2];
            *(u_long *)&p4->u3 = f->uv[3];
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8002D9A0", func_8002E3D0);
#endif
