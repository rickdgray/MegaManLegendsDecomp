#include "common.h"
#include "rock_neo.exe/code_8002d9a0.h"
#include "rock_neo.exe/gte_inline.h"

// Point sprites: each queued poly's centre is transformed with the scratchpad matrix, then
// with D_80097CD4 as a quad of half-size r. One matrix pointer serves both loads, so the
// scratchpad one is reloaded every pass (retail's lui in the loop branch's delay slot). The
// first two words go through scalar casts and D_800BE6D8[i]: a fixed-address scalar store
// and an array load don't alias for GCC 2.7, so both loads are scheduled first.
void func_8002D9A0(void)
{
    sint32 pos[3];
    C8002D9A0_VERTS v;
    sint16 q[8];
    uint32 rgb;
    uint32 i;
    uint32 n;
    uint32 *ot;
    sint32 z;
    sint32 r;
    C8002D9A0_POLY **pp;
    sint32 *m;
    C8002D9A0_POLY *p;

    n          = D_800988FC;
    D_800988FC = 0;
    for (i = 0; i < n; i++)
    {
        m = (sint32 *)0x1F800008;
        GTE_SET_MATRIX(m);
        *(sint32 *)&v.h[0] = D_800BE6D8[i]->w8;
        *(sint32 *)&v.h[2] = D_800BE6D8[i]->w10;
        pp                 = &D_800BE6D8[i];
        GTE_LDV0(&v);
        GTE_NOP2();
        GTE_RTV0();
        GTE_STMAC123_M(pos);
        z = pos[2];
        if ((*(uint16 *)0x1F800006 << 2) >= z && z >= 0xC0)
        {
            m = D_80097CD4;
            GTE_SET_MATRIX(m);
            p      = *pp;
            r      = p->w18;
            v.h[8] = pos[0];
            v.h[9] = pos[1];
            v.h[2] = v.h[6] = v.h[10] = z;
            v.h[0]                    = pos[0] - r;
            v.h[1]                    = pos[1] - r;
            v.h[4]                    = pos[0] + r;
            v.h[5]                    = pos[1] + r;
            GTE_LDV3C(&v);
            GTE_NOP2();
            GTE_RTPT();
            ot = (uint32 *)(*(uint32 *)0x1F80003C + (z >> 3) * 4);
            if ((*pp)->w20 & 8)
            {
                p->tag = *ot | 0x09000000;
                *ot    = (uint32)p & 0xFFFFFF;
            }
            else
            {
                *(uint32 *)0x1F8000E0 = D_800C0DC0[(z / 512) & 0x1F] << 16;
                GTE_LWC2(6, &(*pp)->rgb);
                GTE_NOP2();
                GTE_DPCS_RUN();
                p->tag = *ot | 0x09000000;
                *ot    = (uint32)p & 0xFFFFFF;
                GTE_SWC2(22, &rgb);
                p->rgb = rgb;
                p->wC |= *(uint32 *)0x1F8000E0;
            }
            GTE_STSXY0(&p->w8);
            GTE_STSXY0(&q[0]);
            GTE_STSXY1(&p->w20);
            GTE_STSXY1(&q[4]);
            p->w10 = (q[1] << 16) | (uint16)q[4];
            p->w18 = (q[5] << 16) | (uint16)q[0];
        }
    }
}

// One variable holds the header word and then the second entry word.
C8002D9A0_UNPACK func_8002DC84(C8002D9A0_OBJ *obj, sint32 i, sint32 j)
{
    C8002D9A0_UNPACK r;
    uint32 w;
    uint32 *p;

    p      = obj->list[i];
    w      = p[0];
    p      = (uint32 *)((uint8 *)(p + (w & 0xFF)) + (j * 8 + 4));
    r.head = w;
    r.c    = (p[0] & 0xFFFFFF) | 0x80000000;
    w      = p[1];
    r.b    = w >> 24;
    r.d    = (w & 0xFFFFFF) | 0x80000000;
    return r;
}

// Copied word by word: a struct assignment is one block-move insn, which keeps the
// prologue's stack adjustment ahead of the loads.
C8002D9A0_B8 func_8002DD1C(C8002D9A0_ENT8 *tbl, sint32 idx)
{
    C8002D9A0_W8 tmp;
    sint32 w0;
    sint32 w1;

    w0       = tbl[idx].w[0];
    w1       = tbl[idx].w[1];
    tmp.w[0] = w0;
    tmp.w[1] = w1;
    return *(C8002D9A0_B8 *)&tmp;
}

C8002D9A0_B4 func_8002DD68(C8002D9A0_ENT16 *tbl, sint32 idx)
{
    C8002D9A0_W4 tmp;

    tmp = *(C8002D9A0_W4 *)&tbl[idx];
    return *(C8002D9A0_B4 *)&tmp;
}

// Copied word by word, like func_8002DD1C; the store order sets retail's schedule.
C8002D9A0_B12 func_8002DDA0(C8002D9A0_ENT16 *tbl, sint32 idx)
{
    C8002D9A0_W12 tmp;
    sint32 w0;
    sint32 w1;
    sint32 w2;

    w0       = tbl[idx].w[1];
    w1       = tbl[idx].w[2];
    tmp.w[1] = w1;
    w2       = tbl[idx].w[3];
    tmp.w[0] = w0;
    tmp.w[2] = w2;
    return *(C8002D9A0_B12 *)&tmp;
}

void func_8002DE04(C8002D9A0_ENT8 *tbl, sint32 idx, sint32 *src)
{
    tbl[idx].w[0] = src[0];
    tbl[idx].w[1] = src[1];
}

void func_8002DE20(C8002D9A0_ENT16 *tbl, sint32 idx, sint32 *src)
{
    tbl[idx].w[0] = src[0];
}

void func_8002DE34(C8002D9A0_ENT16 *tbl, sint32 idx, sint32 *src)
{
    tbl[idx].w[1] = src[0];
    tbl[idx].w[2] = src[1];
    tbl[idx].w[3] = src[2];
}

void func_8002DE5C(void)
{
    C8002D9A0_REC *p;
    uint32 i;

    i = 4;
    p = (C8002D9A0_REC *)0x800C4B00;
    do
    {
        i--;
        p--;
        if (p->flags & 2)
        {
            func_8002DEEC(p);
        }
    } while (i != 0);
    i = 16;
    p = (C8002D9A0_REC *)0x800A4708;
    do
    {
        i--;
        p--;
        if (p->flags & 2)
        {
            func_8002DEEC(p);
        }
    } while (i != 0);
}

// The fog-table load uses ASPSX 2.34's constant-address expansion (tools/patches/maspsx-*).
void func_8002DEEC(C8002D9A0_REC *rec)
{
    sint32 v[4];
    sint16 unused[4];
    sint16 sxy[2];
    sint32 z;
    sint32 i;
    sint32 c;
    sint32 c2;

    C8002D9A0_GTE_SET_ROT(C8002D9A0_ROT_A);
    C8002D9A0_GTE_SET_TRANS_V(C8002D9A0_TRANS_V);
    GTE_LDV0(rec->pos);
    GTE_NOP2();
    GTE_RTPS();
    GTE_SWC2(8, C8002D9A0_DEPTH);
    GTE_STSXY2(sxy);
    C8002D9A0_GTE_STSZOTZ(&z);
    if (z > C8002D9A0_FAR_Z || z < (0x30 >> C8002D9A0_SHIFT))
    {
        return;
    }
    if ((uint16)(sxy[0] + 0x160) > 0x400 || (uint16)(sxy[1] + 0x88) > 0x400)
    {
        return;
    }
    C8002D9A0_TPAGE = C8002D9A0_FOG_TBL[(z / 128) & 0x1F] << 16;
    if (z >= 0x709)
    {
        C8002D9A0_LOD_PTR = (C8002D9A0_LOD *)(rec->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        C8002D9A0_LOD_PTR = (C8002D9A0_LOD *)(rec->model->lod[1] + 0x14);
    }
    else
    {
        C8002D9A0_LOD_PTR = (C8002D9A0_LOD *)(rec->model->lod[0] + 0x14);
    }
    c               = rec->color;
    z               = rec->parts[0].count;
    C8002D9A0_COLOR = C8002D9A0_RGB24(c);
    C8002D9A0_GTE_DPCS(&C8002D9A0_COLOR);
    for (i = 0; i < z; i++)
    {
        if (rec->parts[i].hidden < 0)
        {
            continue;
        }
        C8002D9A0_GTE_SET_ROT(C8002D9A0_ROT_A);
        C8002D9A0_GTE_LDCLMV(rec->mats[i]);
        C8002D9A0_GTE_RTIR();
        C8002D9A0_GTE_STCLMV(C8002D9A0_MAT_C);
        C8002D9A0_GTE_LDCLMV(rec->mats[i] + 2);
        C8002D9A0_GTE_RTIR();
        C8002D9A0_GTE_STCLMV(C8002D9A0_MAT_C + 2);
        C8002D9A0_GTE_LDCLMV(rec->mats[i] + 4);
        C8002D9A0_GTE_RTIR();
        C8002D9A0_GTE_STCLMV(C8002D9A0_MAT_C + 4);
        C8002D9A0_GTE_SET_ROT(C8002D9A0_ROT_A);
        GTE_LDV0(rec->offsets[i]);
        C8002D9A0_GTE_RTV0();
        GTE_STLVNL(v);
        C8002D9A0_TRANS_C[0] = C8002D9A0_TRANS_A[0] + v[0];
        C8002D9A0_TRANS_C[1] = C8002D9A0_TRANS_A[1] + v[1];
        C8002D9A0_TRANS_C[2] = C8002D9A0_TRANS_A[2] + v[2];
        GTE_SET_MATRIX(C8002D9A0_MAT_C);
        if (c == 0)
        {
            c2              = rec->offsets[i][3];
            C8002D9A0_COLOR = C8002D9A0_RGB24(c2);
            GTE_MTC2(8, C8002D9A0_DEPTH);
            C8002D9A0_GTE_DPCS(&C8002D9A0_COLOR);
        }
        func_8002E3D0((C8002D9A0_LOD *)(rec->parts[i].index * sizeof(C8002D9A0_LOD) +
                                        (uint32)C8002D9A0_LOD_PTR));
    }
}
