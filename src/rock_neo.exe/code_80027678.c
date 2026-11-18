#include "common.h"
#include "rock_neo.exe/code_80027678.h"
#include "psyq/libgpu.h"

// Small data reached through $gp
sint32 D_80098550;
sint32 D_80098554;

void func_80027678(void)
{
    C80027678_UPD *wp;
    sint32 unused[2]; // unused (frame size)

    if (D_80098824 == 0)
    {
        wp = &Player_work;
        if ((wp->flags & Player_work.mask & 2) &&
            func_80027F78(wp, D_8009BF88 + (C80027678_SCRATCH_00 << 11)) != 0)
        {
            func_8002786C(wp, D_8009BF88 + (C80027678_SCRATCH_00 << 11));
        }
        wp = &Player_work2;
        if ((wp->flags & Player_work2.mask & 2) &&
            func_80027F78(wp, D_8009AE48 + (C80027678_SCRATCH_00 << 11)) != 0)
        {
            func_8002786C(wp, D_8009AE48 + (C80027678_SCRATCH_00 << 11));
        }
        C80027678_VSYNC_MARK = VSync(1);
        func_80029A38();
        D_800D9BF0           = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
        C80027678_VSYNC_MARK = VSync(1);
        func_80029B10();
        D_800D9BF4           = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
        C80027678_VSYNC_MARK = VSync(1);
        func_80029B94();
        D_800D9BF8           = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
        C80027678_VSYNC_MARK = VSync(1);
        func_8002CB18();
        D_800D9BEC           = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
        C80027678_VSYNC_MARK = VSync(1);
        func_8002D50C();
        D_800D9BE8 = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
    }
}

void func_8002786C(void *work, void *arg)
{
    C80027678_BODY *wp;
    sint32 unused[4]; // never used; retail reserves the stack space
    sint32 v[3];
    sint32 pose;
    sint32 i;
    sint32 j;
    sint32 k;
    sint32 n;

    wp = work;
    if (wp->f171 == 0)
    {
        pose = 0;
    }
    else if (wp->f170 == 0)
    {
        pose = 2;
    }
    else
    {
        pose = 1;
    }
    for (i = 0, k = 0; i < 5; i++)
    {
        n                  = D_80089928[pose][i];
        C80027678_MESH_PTR = D_800898EC[pose][i];
        for (j = 0; j < n; j++)
        {
            C80027678_GTE_SET_ROT(C80027678_ROT_A);
            C80027678_GTE_LDCLMV(wp->mats[D_80089938[k]]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C);
            C80027678_GTE_LDCLMV((uint8 *)wp->mats[D_80089938[k]] + 2);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
            C80027678_GTE_LDCLMV((uint8 *)wp->mats[D_80089938[k]] + 4);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
            C80027678_GTE_SET_ROT(C80027678_ROT_A);
            GTE_LDV0(wp->offsets[D_80089938[k]]);
            C80027678_GTE_RTV0();
            GTE_STLVNL(v);
            C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
            C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
            C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
            GTE_SET_MATRIX(C80027678_MAT_C);
            k++;
            func_80027BE0((uint32 *)C80027678_MESH_PTR, arg, &C80027678_MESH_PTR->verts);
            func_80027D94((uint32 *)C80027678_MESH_PTR, arg, &C80027678_MESH_PTR->verts);
            C80027678_MESH_PTR++;
        }
    }
}

// Same shape as func_80027D94 (mesh argument reused as the prim cursor; mask, clut and tag
// locals before the loop). The clut mask and the 0x1F8000E0 pointer are set in the loop after
// n--, so loop.c hoists them as retail does; one STSXY3 statement keeps prim's use count low
// enough for the prim + 4 induction pointer to take the lower register.
void func_80027BE0(uint32 *prim, uint32 *ot, uint8 **verts)
{
    sint32 clip;
    sint32 otz;
    uint8 *rec;
    C80027678_MESH *mesh;
    uint32 *face;
    uint8 *v;
    uint32 idx;
    sint32 n;
    uint32 clut;
    uint32 mask;
    uint32 code;
    uint32 *e0;
    uint32 clut_mask;

    mesh = (C80027678_MESH *)prim;
    rec  = mesh->tri;
    n    = mesh->n_tri;
    v    = *verts;
    face = (uint32 *)(rec + 0x40);
    prim = (uint32 *)(rec + (C80027678_SCRATCH_00 << 5));
    idx  = *face;
    C80027678_GTE_LDV3(v + ((idx & 0xFF) << 3), v + ((idx & 0xFF00) >> 5),
                       v + ((idx >> 13) & 0x7F8));
    GTE_NOP2();
    GTE_RTPT();
    mask = 0xFFFFFF;
    clut = C80027678_SCRATCH_E4;
    code = 0x07000000;
    while (n != 0)
    {
        idx = *face;
        C80027678_GTE_LDV3(v + ((idx & 0xFF) << 3), v + ((idx & 0xFF00) >> 5),
                           v + ((idx & 0xFF0000) >> 13));
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        clut_mask = 0xFFF8FFFF;
        e0        = &C80027678_SCRATCH_E0;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            C80027678_GTE_STSXY3_FT(prim);
            GTE_NOP2();
            C80027678_GTE_AVSZ3();
            prim[3] = (prim[3] & clut_mask) | *e0;
            GTE_SWC2(7, &otz);
            prim[0]              = code | ot[otz - D_80098550];
            ot[otz - D_80098550] = (uint32)prim & mask;
            prim[1]              = clut;
        }
        face += 0x11;
        prim += 0x11;
    }
}

void func_80027D94(uint32 *prim, uint32 *ot, uint8 **verts)
{
    sint32 clip;
    sint32 otz;
    uint8 *rec;
    C80027678_MESH *mesh;
    uint32 *face;
    uint8 *v;
    uint32 idx;
    sint32 n;
    uint32 clut;
    uint32 mask;
    uint32 code;

    mesh = (C80027678_MESH *)prim;
    rec  = mesh->quad;
    n    = mesh->n_quad;
    v    = *verts;
    face = (uint32 *)(rec + 0x50);
    prim = (uint32 *)(rec + C80027678_SCRATCH_00 * 0x28);
    idx  = *face;
    C80027678_GTE_LDV3(v + ((idx & 0xFF) << 3), v + ((idx & 0xFF00) >> 5),
                       v + ((idx >> 13) & 0x7F8));
    GTE_NOP2();
    GTE_RTPT();
    mask = 0xFFFFFF;
    clut = C80027678_SCRATCH_E4 | 0x08000000;
    code = 0x09000000;
    while (n != 0)
    {
        idx = *face;
        C80027678_GTE_LDV3(v + ((idx & 0xFF) << 3), v + ((idx & 0xFF00) >> 5),
                           v + ((idx >> 13) & 0x7F8));
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            GTE_SWC2_OFF(12, 8, prim);
            GTE_SWC2_OFF(13, 16, prim);
            GTE_SWC2_OFF(14, 24, prim);
            GTE_LDV0(v + ((idx >> 24) << 3));
            GTE_NOP2();
            GTE_RTPS();
            GTE_STSXY2(prim + 8);
            GTE_NOP2();
            C80027678_GTE_AVSZ4();
            prim[3] = (prim[3] & 0xFFF8FFFF) | C80027678_SCRATCH_E0;
            GTE_SWC2(7, &otz);
            prim[0]              = code | ot[otz - D_80098550];
            ot[otz - D_80098550] = (uint32)prim & mask;
            prim[1]              = clut;
        }
        face += 0x15;
        prim += 0x15;
    }
}

sint32 func_80027F78(void *work, void *arg)
{
    C80027678_BODY *wp;
    C80027678_OT_ENTRY *ot;
    sint16 pos[3];
    sint32 z;
    sint32 a;
    sint32 b;
    sint32 c;
    sint32 lo;
    sint32 hi;
    sint32 end;
    sint32 i;

    wp         = work;
    ot         = arg;
    pos[0]     = ((sint16 *)wp->offsets[0])[0];
    pos[1]     = ((sint16 *)wp->offsets[0])[1];
    pos[2]     = ((sint16 *)wp->offsets[0])[2];
    D_80098554 = 0;
    GTE_SET_MATRIX(C80027678_ROT_A);
    GTE_LDV0(pos);
    GTE_NOP2();
    GTE_RTPS();
    C80027678_GTE_STSZOTZ(&z);
    C80027678_SCRATCH_E4 = 0x24808080;
    if (Scene_work == 0)
    {
        a = func_8005EBC4();
        b = func_8005EBD4();
        if (a >= 0x5A || b >= 0x5A || !(C80027678_SCRATCH_02 & 1))
        {
            if (a != 0)
            {
                c                    = (D_800BBCF8[(C80027678_SCRATCH_02 & 0x1F) * 2] >> 6) + 0xBF;
                C80027678_SCRATCH_E4 = 0x24000000 | c | (c << 8) | (c << 16);
            }
            if (b != 0)
            {
                C80027678_SCRATCH_E4 |= 0x02000000;
            }
        }
    }
    C80027678_GTE_DPCS(&C80027678_SCRATCH_E4);
    C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    if (z > C80027678_FAR_Z)
    {
        return 0;
    }
    lo         = ((z - 0x100) >> 1 << 1) + 2;
    hi         = (z + 0xFF) >> 1 << 1;
    end        = hi + 2;
    z          = z - 0x100;
    D_80098550 = z;
    if (lo >= 0)
    {
        addPrims(&D_800A4D40[C80027678_SCRATCH_00][lo >> 1], ot + lo - z - 1, ot);
    }
    for (i = lo; i < hi; i += 2)
    {
        if (i >= 0)
        {
            addPrims(&D_800A4D40[C80027678_SCRATCH_00][i >> 1], &ot[i - z + 1], &ot[i - z]);
        }
    }
    if (end >= 0)
    {
        addPrims(&D_800A4D40[C80027678_SCRATCH_00][end >> 1], &ot[0x1FF], ot + hi - z);
    }
    return 1;
}

// Multi-part model: culls and picks the LOD by depth, then draws each visible part with its
// own rotation and offset (and, without a model colour, the part colour) through func_800289A0.
void func_8002831C(void *rec)
{
    sint32 v[3];
    sint32 unused[2]; // unused (frame size)
    sint16 sxy[2];
    sint32 z;
    C80027678_MULTI *wp;
    sint32 color;
    sint32 c;
    sint32 i;

    wp = rec;
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_SET_TR(C80027678_VIEW_TR);
    GTE_LDV0(wp->pos);
    GTE_NOP2();
    GTE_RTPS();
    GTE_SWC2(8, C80027678_IR0_SAVE);
    GTE_STSXY2(sxy);
    C80027678_GTE_STSZOTZ(&z);
    wp->draw &= 0x7F;
    if (!(wp->flags & 0x40) || z >= C80027678_FAR_Z)
    {
        if (z > C80027678_FAR_Z || z < (0x30 >> C80027678_SHIFT))
        {
            return;
        }
        if ((uint16)(sxy[0] + 0x160) > 0x400 || (uint16)(sxy[1] + 0x88) > 0x400)
        {
            return;
        }
    }
    wp->draw |= 0x80;
    C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    if (z >= 0x709)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        if (C80027678_LOD_MODE & 8)
        {
            C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[2] + 0x14);
        }
        else
        {
            C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[1] + 0x14);
        }
    }
    else
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[0] + 0x14);
    }
    color                = wp->color;
    z                    = wp->parts[0].count;
    C80027678_SCRATCH_E4 = ((color & 0x1F) << 3) | ((color & 0x3E0) << 6) |
                           ((color & 0x7C00) << 9) | ((color & 0x8000) << 10);
    C80027678_GTE_DPCS(&C80027678_SCRATCH_E4);
    for (i = 0; i < z; i++)
    {
        if (wp->parts[i].hide < 0)
        {
            continue;
        }
        if ((wp->kind & 0xE0) == 0x40)
        {
            C80027678_GTE_SET_ROT(C80027678_ROT_A);
            C80027678_GTE_LDCLMV(&wp->rot.kind40.mats[i].m[0][0]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C);
            C80027678_GTE_LDCLMV(&wp->rot.kind40.mats[i].m[0][1]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
            C80027678_GTE_LDCLMV(&wp->rot.kind40.mats[i].m[0][2]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
        }
        else
        {
            C80027678_GTE_SET_ROT(C80027678_ROT_A);
            C80027678_GTE_LDCLMV(&wp->rot.mats[i].m[0][0]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C);
            C80027678_GTE_LDCLMV(&wp->rot.mats[i].m[0][1]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
            C80027678_GTE_LDCLMV(&wp->rot.mats[i].m[0][2]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
        }
        C80027678_GTE_SET_ROT(C80027678_ROT_A);
        GTE_LDV0(&wp->offs[i]);
        C80027678_GTE_RTV0();
        GTE_STLVNL(v);
        C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
        C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
        C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
        GTE_SET_MATRIX(C80027678_MAT_C);
        if (color == 0)
        {
            c = wp->offs[i].pad;
            C80027678_SCRATCH_E4 =
                ((c & 0x1F) << 3) | ((c & 0x3E0) << 6) | ((c & 0x7C00) << 9) | ((c & 0x8000) << 10);
            GTE_MTC2(8, C80027678_IR0_SAVE);
            C80027678_GTE_DPCS(&C80027678_SCRATCH_E4);
        }
        func_800289A0(C80027678_LOD_PTR + wp->parts[i].lod);
    }
}

// Like func_80029608 plus an OT range check. Register choice hangs on global-alloc
// priorities: the shared index word w, separate per-loop primitive pointers and vertex
// count, the quad loop's one-statement nop/nclip and n-- after nclip give f > d > n as
// retail. The 16-byte unused block local reproduces the frame (it is placed after otz).
void func_800289A0(C80027678_LOD *lod)
{
    sint32 sz[4];
    sint32 clip;
    uint32 otz;
    uint32 *sxy_tbl;
    uint16 *sz_tbl;
    C80027678_VTX8 *v;
    C80027678_FACE *f;
    uint32 *p;
    uint32 *q;
    uint32 *ot;
    uint32 tex;
    uint32 mask;
    uint32 tag;
    uint32 color;
    uint32 i;
    uint32 n;
    uint32 n_verts;
    uint32 a;
    uint32 b;
    uint32 c;
    uint32 d;
    uint32 w;

    mask    = 0xFFFFFF;
    sxy_tbl = C80027678_SXY;
    sz_tbl  = C80027678_SZ;
    n_verts = lod->n_verts;
    tex     = lod->tex;
    v       = lod->verts;
    for (i = 0; i < n_verts; i += 3)
    {
        GTE_LDV3C(&v[i]);
        GTE_NOP2();
        GTE_RTPT();
        C80027678_GTE_STSXY3C(&sxy_tbl[i]);
        C80027678_GTE_STSZ3(sz);
        sz_tbl[i]     = sz[0];
        sz_tbl[i + 1] = sz[1];
        sz_tbl[i + 2] = sz[2];
    }
    tag   = 0x07000000;
    color = C80027678_SCRATCH_E4 | 0x24000000;
    for (n = lod->n_tri, f = lod->tri; n != 0; f++)
    {
        w = f->index.word;
        a = w & 0xFF;
        b = (w >> 8) & 0xFF;
        c = (w >> 16) & 0xFF;
        C80027678_GTE_LDSXY3(sxy_tbl[a], sxy_tbl[b], sxy_tbl[c]);
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            p              = C80027678_PRIM;
            C80027678_PRIM = p + 8;
            GTE_SWC2_OFF(12, 8, p);
            GTE_SWC2_OFF(13, 16, p);
            GTE_SWC2_OFF(14, 24, p);
            C80027678_GTE_LDSZ3(sz_tbl[a], sz_tbl[b], sz_tbl[c]);
            GTE_NOP2();
            C80027678_GTE_AVSZ3();
            GTE_SWC2(7, &otz);
            ot = C80027678_OT + (otz >> 1);
            if ((otz >> 1) * 4 >= 0x2000)
            {
                continue;
            }
            p[0] = tag | *ot;
            *ot  = (uint32)p & mask;
            p[1] = color;
            p[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
            p[5] = (tex << 16) | f->uv[1] | 0x200000;
            p[7] = f->uv[2];
        }
    }
    tag   = 0x09000000;
    color = C80027678_SCRATCH_E4 | 0x2C000000;
    for (n = lod->n_quad, f = lod->quad; n != 0; f++)
    {
        w = f->index.word;
        a = w & 0xFF;
        b = (w >> 8) & 0xFF;
        c = (w >> 16) & 0xFF;
        d = w >> 24;
        C80027678_GTE_LDSXY3(sxy_tbl[a], sxy_tbl[b], sxy_tbl[c]);
        C80027678_GTE_NCLIP_NOP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            q              = C80027678_PRIM;
            C80027678_PRIM = q + 10;
            GTE_SWC2_OFF(12, 8, q);
            GTE_SWC2_OFF(13, 16, q);
            GTE_SWC2_OFF(14, 24, q);
            q[8] = sxy_tbl[d];
            C80027678_GTE_LDSZ4(sz_tbl[a], sz_tbl[b], sz_tbl[c], sz_tbl[d]);
            GTE_NOP2();
            C80027678_GTE_AVSZ4();
            GTE_SWC2(7, &otz);
            ot = C80027678_OT + (otz >> 1);
            if ((otz >> 1) * 4 >= 0x2000)
            {
                continue;
            }
            q[0] = tag | *ot;
            *ot  = (uint32)q & mask;
            q[1] = color;
            q[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
            q[5] = (tex << 16) | f->uv[1] | 0x200000;
            q[7] = f->uv[2];
            q[9] = f->uv[3];
        }
    }
    {
        // Unused, allocated after clip and otz (16 bytes at the frame top, as retail).
        sint32 unused[4];
    }
}

// Two descending record scans. Indexing the tables by symbol with a pre-decremented count
// gives retail's separate byte offset and counter, with the base rebuilt each pass.
void func_80028DE0(void)
{
    sint32 i;
    C80027678_REC5A4 *a;
    C80027678_REC3C0 *b;

    if (D_80098824 == 0)
    {
        C80027678_VSYNC_MARK = VSync(1);
        i                    = 4;
        while (i != 0)
        {
            i--;
            a = &D_800C3580[i];
            if (C80027678_ROOM == 0x17)
            {
                if (a->flags & a->mask & 2)
                {
                    func_8002831C(a);
                }
            }
            else if (a->flags & a->mask & 2)
            {
                func_80028F90(a);
            }
        }
        D_800D9BFC           = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
        C80027678_VSYNC_MARK = VSync(1);
        i                    = 16;
        while (i != 0)
        {
            i--;
            b = &D_8009F108[i];
            if (C80027678_ROOM == 0x17)
            {
                if (b->flags & b->mask & 2)
                {
                    func_8002831C(b);
                }
            }
            else if (b->flags & b->mask & 2)
            {
                func_80028F90(b);
            }
        }
        D_800D9C00 = (VSync(1) - C80027678_VSYNC_MARK) & 0xFFFF;
    }
}

// As func_8002831C, drawing the parts through func_80029608 and without the IR0 reload.
void func_80028F90(void *rec)
{
    sint32 v[3];
    sint32 unused[2]; // unused (frame size)
    sint16 sxy[2];
    sint32 z;
    C80027678_MULTI *wp;
    sint32 color;
    sint32 c;
    sint32 i;

    wp = rec;
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_SET_TR(C80027678_VIEW_TR);
    GTE_LDV0(wp->pos);
    GTE_NOP2();
    GTE_RTPS();
    GTE_SWC2(8, C80027678_IR0_SAVE);
    GTE_STSXY2(sxy);
    C80027678_GTE_STSZOTZ(&z);
    wp->draw &= 0x7F;
    if (!(wp->flags & 0x40) || z >= C80027678_FAR_Z)
    {
        if (z > C80027678_FAR_Z || z < (0x30 >> C80027678_SHIFT))
        {
            return;
        }
        if ((uint16)(sxy[0] + 0x160) > 0x400 || (uint16)(sxy[1] + 0x88) > 0x400)
        {
            return;
        }
    }
    wp->draw |= 0x80;
    C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    if (z >= 0x709)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        if (C80027678_LOD_MODE & 8)
        {
            C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[2] + 0x14);
        }
        else
        {
            C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[1] + 0x14);
        }
    }
    else
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(wp->model->lod[0] + 0x14);
    }
    color                = wp->color;
    z                    = wp->parts[0].count;
    C80027678_SCRATCH_E4 = ((color & 0x1F) << 3) | ((color & 0x3E0) << 6) |
                           ((color & 0x7C00) << 9) | ((color & 0x8000) << 10);
    C80027678_GTE_DPCS(&C80027678_SCRATCH_E4);
    for (i = 0; i < z; i++)
    {
        if (wp->parts[i].hide < 0)
        {
            continue;
        }
        if ((wp->kind & 0xE0) == 0x40)
        {
            C80027678_GTE_SET_ROT(C80027678_ROT_A);
            C80027678_GTE_LDCLMV(&wp->rot.kind40.mats[i].m[0][0]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C);
            C80027678_GTE_LDCLMV(&wp->rot.kind40.mats[i].m[0][1]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
            C80027678_GTE_LDCLMV(&wp->rot.kind40.mats[i].m[0][2]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
        }
        else
        {
            C80027678_GTE_SET_ROT(C80027678_ROT_A);
            C80027678_GTE_LDCLMV(&wp->rot.mats[i].m[0][0]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C);
            C80027678_GTE_LDCLMV(&wp->rot.mats[i].m[0][1]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
            C80027678_GTE_LDCLMV(&wp->rot.mats[i].m[0][2]);
            C80027678_GTE_RTIR();
            C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
        }
        C80027678_GTE_SET_ROT(C80027678_ROT_A);
        GTE_LDV0(&wp->offs[i]);
        C80027678_GTE_RTV0();
        GTE_STLVNL(v);
        C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
        C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
        C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
        GTE_SET_MATRIX(C80027678_MAT_C);
        if (color == 0)
        {
            c = wp->offs[i].pad;
            C80027678_SCRATCH_E4 =
                ((c & 0x1F) << 3) | ((c & 0x3E0) << 6) | ((c & 0x7C00) << 9) | ((c & 0x8000) << 10);
            C80027678_GTE_DPCS(&C80027678_SCRATCH_E4);
        }
        func_80029608(C80027678_LOD_PTR + wp->parts[i].lod);
    }
}

// Register choice hangs on global-alloc priorities: separate per-loop primitive pointers and
// vertex count, the shared index word w, a three-store screen-XY macro in the vertex loop and
// the one-statement store in the quad loop give f > d > n (t3, t4, t5) as retail.
void func_80029608(C80027678_LOD *lod)
{
    sint32 sz[4];
    sint32 clip;
    uint32 otz;
    uint32 *sxy_tbl;
    uint16 *sz_tbl;
    C80027678_VTX8 *v;
    C80027678_FACE *f;
    uint32 *p;
    uint32 *q;
    uint32 *ot;
    uint32 tex;
    uint32 mask;
    uint32 tag;
    uint32 color;
    uint32 i;
    uint32 n;
    uint32 n_verts;
    uint32 a;
    uint32 b;
    uint32 c;
    uint32 d;
    uint32 w;

    mask    = 0xFFFFFF;
    sxy_tbl = C80027678_SXY;
    sz_tbl  = C80027678_SZ;
    n_verts = lod->n_verts;
    tex     = lod->tex;
    v       = lod->verts;
    for (i = 0; i < n_verts; i += 3)
    {
        GTE_LDV3C(&v[i]);
        GTE_NOP2();
        GTE_RTPT();
        C80027678_GTE_STSXY3C(&sxy_tbl[i]);
        C80027678_GTE_STSZ3(sz);
        sz_tbl[i]     = sz[0];
        sz_tbl[i + 1] = sz[1];
        sz_tbl[i + 2] = sz[2];
    }
    tag   = 0x07000000;
    color = C80027678_SCRATCH_E4 | 0x24000000;
    for (n = lod->n_tri, f = lod->tri; n != 0; f++)
    {
        w = f->index.word;
        a = w & 0xFF;
        b = (w >> 8) & 0xFF;
        c = (w >> 16) & 0xFF;
        C80027678_GTE_LDSXY3(sxy_tbl[a], sxy_tbl[b], sxy_tbl[c]);
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            p              = C80027678_PRIM;
            C80027678_PRIM = p + 8;
            GTE_SWC2_OFF(12, 8, p);
            GTE_SWC2_OFF(13, 16, p);
            GTE_SWC2_OFF(14, 24, p);
            C80027678_GTE_LDSZ3(sz_tbl[a], sz_tbl[b], sz_tbl[c]);
            GTE_NOP2();
            C80027678_GTE_AVSZ3();
            GTE_SWC2(7, &otz);
            ot   = C80027678_OT + (otz >> 1);
            p[0] = tag | *ot;
            *ot  = (uint32)p & mask;
            p[1] = color;
            p[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
            p[5] = (tex << 16) | f->uv[1] | 0x200000;
            p[7] = f->uv[2];
        }
    }
    tag   = 0x09000000;
    color = C80027678_SCRATCH_E4 | 0x2C000000;
    for (n = lod->n_quad, f = lod->quad; n != 0; f++)
    {
        w = f->index.word;
        a = w & 0xFF;
        b = (w >> 8) & 0xFF;
        c = (w >> 16) & 0xFF;
        d = w >> 24;
        C80027678_GTE_LDSXY3(sxy_tbl[a], sxy_tbl[b], sxy_tbl[c]);
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            q              = C80027678_PRIM;
            C80027678_PRIM = q + 10;
            C80027678_GTE_STSXY3_FT(q);
            q[8] = sxy_tbl[d];
            C80027678_GTE_LDSZ4(sz_tbl[a], sz_tbl[b], sz_tbl[c], sz_tbl[d]);
            GTE_NOP2();
            C80027678_GTE_AVSZ4();
            GTE_SWC2(7, &otz);
            ot   = C80027678_OT + (otz >> 1);
            q[0] = tag | *ot;
            *ot  = (uint32)q & mask;
            q[1] = color;
            q[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
            q[5] = (tex << 16) | f->uv[1] | 0x200000;
            q[7] = f->uv[2];
            q[9] = f->uv[3];
        }
    }
}

void func_80029A38(void)
{
    uint32 i;
    C80027678_SLOT10C *p;
    sint32 f;

    for (i = 0; i < 16; i++)
    {
        p = &D_800BFB20[i];
        f = p->flags;
        if (f & p->mask & 2)
        {
            D_800898D0[(f & 0x1C) >> 2](p->work, f);
        }
    }
    for (i = 0; i < 32; i++)
    {
        p = &D_8009CF88[i];
        f = p->flags;
        if (f & p->mask & 2)
        {
            D_800898D0[(f & 0x1C) >> 2](p->work, f);
        }
    }
}

void func_80029B10(void)
{
    uint32 i;
    C80027678_SLOT48 *p;
    sint32 f;

    for (i = 0; i < 64; i++)
    {
        p = &D_800A3B40[i];
        f = p->flags;
        if (f & p->mask & 2)
        {
            D_800898D0[(f & 0x1C) >> 2](p->work, f);
        }
    }
}

void func_80029B94(void)
{
    uint32 i;
    C80027678_SLOT50 *p;
    sint32 f;

    for (i = 0; i < 32; i++)
    {
        p = &D_800BF118[i];
        f = p->flags;
        if (f & p->mask & 2)
        {
            D_800898D0[(f & 0x1C) >> 2](p->work, f);
        }
    }
}

// Camera-facing sprite (POLY_FT4), optionally rolled by obj->angle.
void func_80029C18(C80027678_SPRITE *obj, uint32 flags)
{
    sint32 m[8];
    sint32 v[3];
    C80027678_SVEC pts[3];
    C80027678_DVEC sxy[3];
    uint32 col;
    uint32 *p;
    uint32 *prim;
    uint32 *ot;
    uint32 size;
    uint32 s;
    uint32 c;
    uint32 uv;
    sint32 z;

    if (C80027678_SHIFT == 0)
    {
        C80027678_GTE_SET_ROT(C80027678_ROT_A);
        GTE_SET_TR(C80027678_VIEW_TR);
        GTE_LDV0(obj->pos);
        GTE_NOP2();
        GTE_RTV0();
        GTE_STLVNL(v);
        if (v[2] > (C80027678_FAR_Z << 2) || v[2] < 0xC0)
        {
            return;
        }
        size = obj->size;
    }
    else
    {
        C80027678_GTE_SET_ROT(C80027678_ROT_A);
        GTE_SET_TR(C80027678_VIEW_TR);
        GTE_LDV0(obj->pos);
        GTE_NOP2();
        GTE_RTV0();
        GTE_STLVNL(v);
        if (v[2] > (C80027678_FAR_Z << 2) || v[2] < (0xC0 >> C80027678_SHIFT))
        {
            return;
        }
        C80027678_GTE_SET_TRANS(C80027678_ROT_A);
        pts[0].vx = obj->pos[0] << C80027678_SHIFT;
        pts[0].vy = obj->pos[1] << C80027678_SHIFT;
        pts[0].vz = obj->pos[2] << C80027678_SHIFT;
        GTE_LDV0(&pts[0]);
        GTE_NOP2();
        GTE_RTV0();
        GTE_STLVNL(v);
        if (v[2] < 0)
        {
            return;
        }
        size = obj->size << C80027678_SHIFT;
    }
    m[0] = 0x1000;
    m[1] = 0;
    m[2] = 0x1000;
    m[3] = 0;
    m[4] = 0x1000;
    m[5] = 0;
    m[6] = 0;
    m[7] = 0;
    GTE_SET_MATRIX(m);
    prim           = C80027678_PRIM;
    C80027678_PRIM = prim + 10;
    p              = prim; // a separate copy, as retail (lw into v1, move to a3)
    if (flags & 0x20)
    {
        s         = (D_800BBCF8[obj->angle & 0x3F] * size) >> 12;
        c         = (D_800BAEB0[obj->angle & 0x3F] * size) >> 12;
        pts[0].vx = v[0] - c + s;
        pts[0].vy = v[1] - c - s;
        pts[1].vx = v[0] + c + s;
        pts[1].vy = v[1] - c + s;
    }
    else
    {
        pts[0].vx = v[0] - size;
        pts[0].vy = v[1] - size;
        pts[1].vx = v[0] + size;
        pts[1].vy = v[1] - size;
    }
    pts[2].vx = v[0];
    pts[2].vy = v[1];
    z         = v[2];
    pts[0].vz = pts[1].vz = pts[2].vz = z;
    GTE_LDV3C(pts);
    GTE_NOP2();
    GTE_RTPT();
    ot = C80027678_OT + (z >> 3);
    uv = obj->uv;
    if (flags & 8)
    {
        p[0] = *ot | 0x09000000;
        *ot  = (uint32)p & 0xFFFFFF;
        p[1] = obj->color | 0x2C000000;
        p[3] = uv | (obj->tex & 0xFFFF0000);
    }
    else
    {
        C80027678_SCRATCH_E0 = D_800C0DC0[(z / 512) & 0x1F] << 16;
        GTE_LWC2(6, &obj->color);
        GTE_NOP2();
        GTE_DPCS_RUN();
        p[0] = *ot | 0x09000000;
        *ot  = (uint32)p & 0xFFFFFF;
        GTE_SWC2(22, &col);
        p[1] = col;
        p[3] = uv | (obj->tex & 0xFFFF0000) | C80027678_SCRATCH_E0;
    }
    p[3] = (obj->tex & 0xFFFF0000) | (uv & 0xFFFF);
    p[5] = (obj->tex << 16) | ((uv & 0xFFFF) + 0x1F);
    p[7] = (uv & 0xFFFF) + 0x1F00;
    p[9] = (uv & 0xFFFF) + 0x1F1F;
    C80027678_GTE_STSXY3C(sxy);
    GTE_STSXY0(p + 2);
    GTE_STSXY1(p + 4);
    p[6] = ((sxy[2].y * 2 - sxy[1].y) << 16) | (uint16)(sxy[2].x * 2 - sxy[1].x);
    p[8] = ((sxy[2].y * 2 - sxy[0].y) << 16) | (uint16)(sxy[2].x * 2 - sxy[0].x);
}

void func_8002A158(void)
{
}

void func_8002A160(C80027678_OBJ *obj, uint32 flags)
{
    sint32 v[3];
    C80027678_VTX8 pos;
    C80027678_MATRIX rot;
    sint16 sxy[2];
    sint32 z;
    sint32 shift;

    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_SET_TR(C80027678_VIEW_TR);
    GTE_LDV0(obj->pos);
    GTE_NOP2();
    GTE_RTPS();
    GTE_STSXY2(sxy);
    C80027678_GTE_STSZOTZ(&z);
    if (!(flags & 0x40) || z >= C80027678_FAR_Z)
    {
        if (z > C80027678_FAR_Z || z < (0x30 >> C80027678_SHIFT))
        {
            return;
        }
        if ((uint16)(sxy[0] + 0x160) > 0x400 || (uint16)(sxy[1] + 0x88) > 0x400)
        {
            return;
        }
    }
    pos   = *(C80027678_VTX8 *)obj->pos;
    shift = C80027678_SHIFT;
    rot   = *(C80027678_MATRIX *)obj->rot;
    if (shift != 0)
    {
        ((sint16 *)&pos)[0] <<= shift;
        ((sint16 *)&pos)[1] <<= shift;
        ((sint16 *)&pos)[2] <<= shift;
        rot.m[0][0] <<= shift;
        rot.m[0][1] <<= shift;
        rot.m[0][2] <<= shift;
        rot.m[1][0] <<= shift;
        rot.m[1][1] <<= shift;
        rot.m[1][2] <<= shift;
        rot.m[2][0] <<= shift;
        rot.m[2][1] <<= shift;
        rot.m[2][2] <<= shift;
    }
    if (z >= 0x709)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[1] + 0x14);
    }
    else
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[0] + 0x14);
    }
    if (flags & 8)
    {
        C80027678_SCRATCH_E0 = 0;
    }
    else if (flags & 0x80)
    {
        C80027678_SCRATCH_E0 =
            (((D_800C0DC0[(z / 128) & 0x1F] >> 2) << 6) + (D_800C0DC0[(z / 128) & 0x1F] & 3)) << 16;
    }
    else
    {
        C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    }
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    C80027678_GTE_LDCLMV(&rot.m[0][0]);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C);
    C80027678_GTE_LDCLMV(&rot.m[0][1]);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
    C80027678_GTE_LDCLMV(&rot.m[0][2]);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_LDV0(&pos);
    C80027678_GTE_RTV0();
    GTE_STLVNL(v);
    C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
    C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
    C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
    GTE_SET_MATRIX(C80027678_MAT_C);
    if (flags & 0x20)
    {
        func_8002A6E8(C80027678_LOD_PTR + obj->part, obj->tex2 & 0x2FFFFFF, flags);
    }
    else
    {
        func_8002A6E8(C80027678_LOD_PTR, obj->tex2 & 0x2FFFFFF, flags);
    }
}

void func_8002A6E8(C80027678_LOD *lod, uint32 color, uint32 flags)
{
    uint32 code;
    sint32 clip;
    uint32 otz;
    C80027678_VTX8 *v;
    C80027678_VTX8 *verts;
    C80027678_FACE *f;
    uint32 *p;
    uint32 *ot;
    sint32 n;
    uint32 tag;
    uint32 mask;
    uint32 tex;

    tag   = 0x07000000;
    mask  = 0xFFFFFF;
    v     = C80027678_VTX_BUF;
    n     = lod->n_tri;
    f     = lod->tri;
    code  = color | 0x24000000;
    verts = lod->verts;
    tex   = lod->tex;
    GTE_LWC2(6, &code);
    for (; n != 0; f++)
    {
        v[0] = verts[f->index.b[0]];
        v[1] = verts[f->index.b[1]];
        v[2] = verts[f->index.b[2]];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        n--;
        if (!(flags & 0x40))
        {
            GTE_NOP2();
            C80027678_GTE_NCLIP();
            GTE_SWC2(24, &clip);
            if (clip <= 0)
            {
                continue;
            }
        }
        GTE_NOP2();
        GTE_DPCS_RUN();
        p              = C80027678_PRIM;
        C80027678_PRIM = p + 8;
        GTE_SWC2_OFF(12, 8, p);
        GTE_SWC2_OFF(13, 16, p);
        GTE_SWC2_OFF(14, 24, p);
        GTE_NOP2();
        C80027678_GTE_AVSZ3();
        GTE_SWC2(7, &otz);
        ot   = C80027678_OT + (otz >> 1);
        p[0] = tag | *ot;
        *ot  = (uint32)p & mask;
        if (!(flags & 8))
        {
            GTE_SWC2(22, &code);
        }
        p[1] = code;
        p[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
        p[5] = (tex << 16) | f->uv[1];
        p[7] = f->uv[2];
    }
    tag  = 0x09000000;
    n    = lod->n_quad;
    f    = lod->quad;
    code = color | 0x2C000000;
    GTE_LWC2(6, &code);
    for (; n != 0; f++)
    {
        v[0] = verts[f->index.b[0]];
        v[1] = verts[f->index.b[1]];
        v[2] = verts[f->index.b[2]];
        v[3] = verts[f->index.b[3]];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        n--;
        if (!(flags & 0x40))
        {
            GTE_NOP2();
            C80027678_GTE_NCLIP();
            GTE_SWC2(24, &clip);
            if (clip <= 0)
            {
                continue;
            }
        }
        GTE_NOP2();
        GTE_DPCS_RUN();
        p              = C80027678_PRIM;
        C80027678_PRIM = p + 10;
        GTE_SWC2_OFF(12, 8, p);
        GTE_SWC2_OFF(13, 16, p);
        GTE_SWC2_OFF(14, 24, p);
        GTE_LDV0(&v[3]);
        GTE_NOP2();
        GTE_RTPS();
        GTE_STSXY2(p + 8);
        GTE_NOP2();
        C80027678_GTE_AVSZ4();
        GTE_SWC2(7, &otz);
        ot   = C80027678_OT + (otz >> 1);
        p[0] = tag | *ot;
        *ot  = (uint32)p & mask;
        if (!(flags & 8))
        {
            GTE_SWC2(22, &code);
        }
        p[1] = code;
        p[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
        p[5] = (tex << 16) | f->uv[1];
        p[7] = f->uv[2];
        p[9] = f->uv[3];
    }
}

void func_8002AB68(void)
{
}

void func_8002AB70(C80027678_OBJ *obj, uint32 flags)
{
    sint32 v[3];
    sint32 z;

    GTE_SET_MATRIX(C80027678_ROT_A);
    GTE_LDV0(obj->pos);
    GTE_NOP2();
    GTE_RTPS();
    C80027678_GTE_STSZOTZ(&z);
    if (z > C80027678_FAR_Z || z < 0x30)
    {
        return;
    }
    if (z >= 0x709)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[1] + 0x14);
    }
    else
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[0] + 0x14);
    }
    C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    C80027678_GTE_LDCLMV(obj->rot);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C);
    C80027678_GTE_LDCLMV(obj->rot + 2);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
    C80027678_GTE_LDCLMV(obj->rot + 4);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_LDV0(obj->pos);
    C80027678_GTE_RTV0();
    GTE_STLVNL(v);
    C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
    C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
    C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
    GTE_SET_MATRIX(C80027678_MAT_C);
    if (flags & 0x20)
    {
        func_8002AEE4(C80027678_LOD_PTR + obj->part, obj->tex);
    }
    else
    {
        func_8002AEE4(C80027678_LOD_PTR, obj->tex);
    }
}

void func_8002AEE4(C80027678_LOD *lod, uint32 *attr)
{
    uint32 code;
    sint32 clip;
    uint32 otz;
    C80027678_VTX8 *v;
    C80027678_VTX8 *verts;
    C80027678_FACE *f;
    uint32 *p;
    uint32 *ot;
    sint32 n;
    uint32 tag;
    uint32 mask;

    tag   = 0x06000000;
    mask  = 0xFFFFFF;
    v     = C80027678_VTX_BUF;
    n     = lod->n_tri;
    f     = lod->tri;
    code  = 0x30000000;
    verts = lod->verts;
    GTE_LWC2(6, &code);
    for (; n != 0; attr += 3, f++)
    {
        v[0] = verts[f->index.b[0]];
        v[1] = verts[f->index.b[1]];
        v[2] = verts[f->index.b[2]];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            p              = C80027678_PRIM;
            C80027678_PRIM = p + 7;
            GTE_SWC2_OFF(12, 8, p);
            GTE_SWC2_OFF(13, 16, p);
            GTE_SWC2_OFF(14, 24, p);
            GTE_NOP2();
            C80027678_GTE_AVSZ3();
            GTE_SWC2(7, &otz);
            ot   = C80027678_OT + (otz >> 1);
            p[0] = tag | *ot;
            *ot  = (uint32)p & mask;
            p[1] = code | attr[0];
            p[3] = attr[1];
            p[5] = attr[2];
        }
    }
    tag  = 0x08000000;
    n    = lod->n_quad;
    f    = lod->quad;
    code = 0x38000000;
    GTE_LWC2(6, &code);
    for (; n != 0; attr += 4, f++)
    {
        v[0] = verts[f->index.b[0]];
        v[1] = verts[f->index.b[1]];
        v[2] = verts[f->index.b[2]];
        v[3] = verts[f->index.b[3]];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        if (clip > 0)
        {
            p              = C80027678_PRIM;
            C80027678_PRIM = p + 9;
            GTE_SWC2_OFF(12, 8, p);
            GTE_SWC2_OFF(13, 16, p);
            GTE_SWC2_OFF(14, 24, p);
            GTE_LDV0(&v[3]);
            GTE_NOP2();
            GTE_RTPS();
            GTE_STSXY2(p + 8);
            GTE_NOP2();
            C80027678_GTE_AVSZ4();
            GTE_SWC2(7, &otz);
            ot   = C80027678_OT + (otz >> 1);
            p[0] = tag | *ot;
            *ot  = (uint32)p & mask;
            p[1] = code | attr[0];
            p[3] = attr[1];
            p[5] = attr[2];
            p[7] = attr[3];
        }
    }
}

void func_8002B2C8(C80027678_OBJ *obj, uint32 flags)
{
    sint32 v[3];
    sint32 z;

    GTE_SET_MATRIX(C80027678_ROT_A);
    GTE_LDV0(obj->pos);
    GTE_NOP2();
    GTE_RTPS();
    C80027678_GTE_STSZOTZ(&z);
    if (z > C80027678_FAR_Z || z < 0x30)
    {
        return;
    }
    if (z >= 0x709)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[1] + 0x14);
    }
    else
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[0] + 0x14);
    }
    C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    C80027678_GTE_LDCLMV(obj->rot);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C);
    C80027678_GTE_LDCLMV(obj->rot + 2);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
    C80027678_GTE_LDCLMV(obj->rot + 4);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_LDV0(obj->pos);
    C80027678_GTE_RTV0();
    GTE_STLVNL(v);
    C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
    C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
    C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
    GTE_SET_MATRIX(C80027678_MAT_C);
    if (flags & 0x20)
    {
        func_8002B644(C80027678_LOD_PTR + obj->part, obj->tex, obj->tex2);
    }
    else
    {
        func_8002B644(C80027678_LOD_PTR, obj->tex, obj->tex2);
    }
}

// Gouraud-textured LOD model, vertex colours scaled by rgb. The colour parameter doubles as the
// loop temporary, so the quad code takes the top byte of the last scaled colour, as in retail.
// Each loop has its own primitive pointer (one shared pointer would be a global pseudo and
// shift the allocation), and n/f are loaded first so i2 outranks them for t5.
void func_8002B644(C80027678_LOD *lod, uint32 *colors, uint32 rgb)
{
    uint32 code;
    sint32 clip;
    uint32 otz;
    C80027678_VTX8 *v;
    C80027678_VTX8 *verts;
    C80027678_FACE *f;
    uint32 *p;
    uint32 *q;
    uint32 *ot;
    sint32 n;
    uint32 tag;
    uint32 mask;
    uint32 tex;
    uint32 r;
    uint32 g;
    uint32 b;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;

    n     = lod->n_tri;
    f     = lod->tri;
    verts = lod->verts;
    tex   = lod->tex & ~0x60;
    tag   = 0x09000000;
    mask  = 0xFFFFFF;
    v     = C80027678_VTX_BUF;
    code  = (rgb & 0xFF000000) | 0x34000000;
    r     = rgb & 0xFF;
    g     = (rgb & 0xFF00) >> 8;
    b     = (rgb >> 16) & 0xFF;
    GTE_LWC2(6, &code);
    for (; n != 0; f++)
    {
        i0   = f->index.b[0];
        i1   = f->index.b[1];
        i2   = f->index.b[2];
        v[0] = verts[i0];
        v[1] = verts[i1];
        v[2] = verts[i2];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        p              = C80027678_PRIM;
        C80027678_PRIM = p + 10;
        GTE_SWC2_OFF(12, 8, p);
        GTE_SWC2_OFF(13, 20, p);
        GTE_SWC2_OFF(14, 32, p);
        GTE_NOP2();
        C80027678_GTE_AVSZ3();
        GTE_SWC2(7, &otz);
        ot   = C80027678_OT + (otz >> 1);
        p[0] = tag | *ot;
        *ot  = (uint32)p & mask;
        rgb  = colors[i0];
        rgb  = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
               ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        p[1] = code | rgb;
        rgb  = colors[i1];
        rgb  = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
               ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        p[4] = rgb;
        rgb  = colors[i2];
        rgb  = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
               ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        p[7] = rgb;
        p[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
        p[6] = (tex << 16) | f->uv[1];
        p[9] = f->uv[2];
    }
    tag  = 0x0C000000;
    n    = lod->n_quad;
    f    = lod->quad;
    code = (rgb & 0xFF000000) | 0x3C000000;
    GTE_LWC2(6, &code);
    for (; n != 0; f++)
    {
        i0   = f->index.b[0];
        i1   = f->index.b[1];
        i2   = f->index.b[2];
        i3   = f->index.b[3];
        v[0] = verts[i0];
        v[1] = verts[i1];
        v[2] = verts[i2];
        v[3] = verts[i3];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        q              = C80027678_PRIM;
        C80027678_PRIM = q + 13;
        GTE_SWC2_OFF(12, 8, q);
        GTE_SWC2_OFF(13, 20, q);
        GTE_SWC2_OFF(14, 32, q);
        GTE_LDV0(&v[3]);
        GTE_NOP2();
        GTE_RTPS();
        GTE_STSXY2(q + 11);
        GTE_NOP2();
        C80027678_GTE_AVSZ4();
        GTE_SWC2(7, &otz);
        ot    = C80027678_OT + (otz >> 1);
        q[0]  = tag | *ot;
        *ot   = (uint32)q & mask;
        rgb   = colors[i0];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[1]  = code | rgb;
        rgb   = colors[i1];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[4]  = rgb;
        rgb   = colors[i2];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[7]  = rgb;
        rgb   = colors[i3];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[10] = rgb;
        q[3]  = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
        q[6]  = (tex << 16) | f->uv[1];
        q[9]  = f->uv[2];
        q[12] = f->uv[3];
    }
}

void func_8002BD48(C80027678_OBJ *obj, uint32 flags)
{
    sint32 v[3];
    sint32 z;

    GTE_SET_MATRIX(C80027678_ROT_A);
    GTE_LDV0(obj->pos);
    GTE_NOP2();
    GTE_RTPS();
    C80027678_GTE_STSZOTZ(&z);
    if (z > C80027678_FAR_Z || z < 0x30)
    {
        return;
    }
    if (z >= 0x709)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[2] + 0x14);
    }
    else if (z >= 0x2BD)
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[1] + 0x14);
    }
    else
    {
        C80027678_LOD_PTR = (C80027678_LOD *)(obj->model->lod[0] + 0x14);
    }
    C80027678_SCRATCH_E0 = D_800C0DC0[(z / 128) & 0x1F] << 16;
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    C80027678_GTE_LDCLMV(obj->rot);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C);
    C80027678_GTE_LDCLMV(obj->rot + 2);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 2);
    C80027678_GTE_LDCLMV(obj->rot + 4);
    C80027678_GTE_RTIR();
    C80027678_GTE_STCLMV(C80027678_MAT_C + 4);
    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    GTE_LDV0(obj->pos);
    C80027678_GTE_RTV0();
    GTE_STLVNL(v);
    C80027678_TRANS_C[0] = C80027678_TRANS_A[0] + v[0];
    C80027678_TRANS_C[1] = C80027678_TRANS_A[1] + v[1];
    C80027678_TRANS_C[2] = C80027678_TRANS_A[2] + v[2];
    GTE_SET_MATRIX(C80027678_MAT_C);
    if (flags & 0x20)
    {
        func_8002C0C4(C80027678_LOD_PTR + obj->part, obj->tex, obj->tex2);
    }
    else
    {
        func_8002C0C4(C80027678_LOD_PTR, obj->tex, obj->tex2);
    }
}

// Like func_8002B644 with per-face colours and semi-transparency. The quad loop's GTE
// statements carry their nops (and the XY stores are one statement); with the triangle loop's
// split form the hoisted 0xFF0000 mask outranks the colours+12 pointer and takes t4.
void func_8002C0C4(C80027678_LOD *lod, uint32 *colors, uint32 rgb)
{
    uint32 code;
    sint32 clip;
    uint32 otz;
    C80027678_VTX8 *v;
    C80027678_VTX8 *verts;
    C80027678_FACE *f;
    uint32 *p;
    uint32 *q;
    uint32 *ot;
    sint32 n;
    uint32 tag;
    uint32 mask;
    uint32 tex;
    uint32 r;
    uint32 g;
    uint32 b;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;

    tag   = 0x09000000;
    mask  = 0xFFFFFF;
    v     = C80027678_VTX_BUF;
    n     = lod->n_tri;
    f     = lod->tri;
    code  = 0x36000000;
    r     = rgb & 0xFF;
    g     = (rgb & 0xFF00) >> 8;
    b     = (rgb >> 16) & 0xFF;
    verts = lod->verts;
    tex   = lod->tex;
    GTE_LWC2(6, &code);
    for (; n != 0; colors += 3, f++)
    {
        i0   = f->index.b[0];
        i1   = f->index.b[1];
        i2   = f->index.b[2];
        v[0] = verts[i0];
        v[1] = verts[i1];
        v[2] = verts[i2];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        GTE_NOP2();
        C80027678_GTE_NCLIP();
        n--;
        GTE_SWC2(24, &clip);
        p              = C80027678_PRIM;
        C80027678_PRIM = p + 10;
        GTE_SWC2_OFF(12, 8, p);
        GTE_SWC2_OFF(13, 20, p);
        GTE_SWC2_OFF(14, 32, p);
        GTE_NOP2();
        C80027678_GTE_AVSZ3();
        GTE_SWC2(7, &otz);
        ot   = C80027678_OT + (otz >> 1);
        p[0] = tag | *ot;
        *ot  = (uint32)p & mask;
        rgb  = colors[0];
        rgb  = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
               ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        p[1] = code | rgb;
        rgb  = colors[1];
        rgb  = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
               ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        p[4] = rgb;
        rgb  = colors[2];
        rgb  = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
               ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        p[7] = rgb;
        p[3] = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
        p[6] = (tex << 16) | f->uv[1] | 0x200000;
        p[9] = f->uv[2];
    }
    tag  = 0x0C000000;
    n    = lod->n_quad;
    f    = lod->quad;
    code = 0x3E000000;
    GTE_LWC2(6, &code);
    for (; n != 0; colors += 4, f++)
    {
        i0   = f->index.b[0];
        i1   = f->index.b[1];
        i2   = f->index.b[2];
        i3   = f->index.b[3];
        v[0] = verts[i0];
        v[1] = verts[i1];
        v[2] = verts[i2];
        v[3] = verts[i3];
        GTE_LDV3C(v);
        GTE_NOP2();
        GTE_RTPT();
        C80027678_GTE_NCLIP_NOP();
        n--;
        GTE_SWC2(24, &clip);
        q              = C80027678_PRIM;
        C80027678_PRIM = q + 13;
        C80027678_GTE_STSXY3_GT(q);
        GTE_LDV0(&v[3]);
        C80027678_GTE_RTPS_NOP();
        GTE_STSXY2(q + 11);
        C80027678_GTE_AVSZ4_NOP();
        GTE_SWC2(7, &otz);
        ot    = C80027678_OT + (otz >> 1);
        q[0]  = tag | *ot;
        *ot   = (uint32)q & mask;
        rgb   = colors[0];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[1]  = code | rgb;
        rgb   = colors[1];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[4]  = rgb;
        rgb   = colors[2];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[7]  = rgb;
        rgb   = colors[3];
        rgb   = ((((rgb & 0xFF) * r) >> 7) & 0xFF) | ((((rgb & 0xFF00) * g) >> 7) & 0xFF00) |
                ((((rgb & 0xFF0000) * b) >> 7) & 0xFF0000);
        q[10] = rgb;
        q[3]  = (tex & 0xFFFF0000) | f->uv[0] | C80027678_SCRATCH_E0;
        q[6]  = (tex << 16) | f->uv[1] | 0x200000;
        q[9]  = f->uv[2];
        q[12] = f->uv[3];
    }
}

void Model_Shadow_Trans(C80027678_MODEL_OBJ *o, sint32 a1, sint32 a2, sint32 a3)
{
    sint32 r;
    uint32 n;

    n = D_800987D8;
    if (n < 0x40)
    {
        D_800ACE00[n].f0 = o->f14;
        if (o->f76 != 0)
        {
            r                = o->f16;
            D_800ACE00[n].f2 = r;
        }
        else
        {
            r                = func_80048E6C(o);
            D_800ACE00[n].f2 = r;
        }
        D_800ACE00[n].f4 = o->f18;
        D_800ACE00[n].f6 = ((o->f56 - o->f116) & 0xFFF) | ((a2 >> 6) << 12);
        D_800ACE00[n].f8 = a1 | (a3 << 14);
        D_800987D8++;
        D_800ACE00[n].fA = r - o->f16;
    }
}

void func_8002C8CC(C80027678_MODEL_OBJ *o, sint32 a1, sint32 a2, sint32 a3)
{
    sint32 r;
    uint32 n;

    n = D_800987D8;
    if (n < 0x40)
    {
        D_800ACE00[n].f0 = o->f14;
        if (o->f76 != 0)
        {
            r                = o->f16;
            D_800ACE00[n].f2 = r;
        }
        else
        {
            r = func_80048E6C(o);
            if (r < o->f16)
            {
                r = o->f16;
            }
            D_800ACE00[n].f2 = r;
        }
        D_800ACE00[n].f4 = o->f18;
        D_800ACE00[n].f6 = (o->f56 & 0xFFF) | ((a2 >> 6) << 12);
        D_800ACE00[n].f8 = a1 | (a3 << 14);
        D_800987D8++;
        D_800ACE00[n].fA = r - o->f16;
    }
}

void func_8002CA10(C80027678_SRC *p, sint32 a1, sint32 a2, sint32 a3)
{
    sint16 r;
    uint32 n;

    n = D_800987D8;
    if (n < 0x40)
    {
        D_800ACE00[n].f0 = p->f0;
        r                = func_80048EA4(p, 0, 0, 0xFFFF);
        D_800ACE00[n].f2 = r;
        D_800ACE00[n].f4 = p->f4;
        D_800ACE00[n].f6 = (a3 & 0xFFF) | ((a2 >> 6) << 12);
        D_800ACE00[n].f8 = a1 | (p->f6 << 14);
        D_800987D8++;
        D_800ACE00[n].fA = r - p->f2;
    }
}

// One variable holds the f6 word and then the D_800ACE08 width (retail reuses a1 for both).
void func_8002CB18(void)
{
    sint32 i;
    sint32 n;
    uint32 w;
    sint32 rx;
    sint32 ry;

    n = D_800987D8;
    for (i = 0; i < n; i++)
    {
        w                = D_800ACE00[i].f6;
        rx               = (w & 0xF000) >> 6;
        ry               = w & 0xFFF;
        w                = D_800ACE08[i].v;
        D_800ACE00[i].f6 = w >> 14;
        func_8002CBDC((C80027678_SHADOW *)&D_800ACE00[i], w & 0x3FFF, rx, ry, D_800ACE0A[i].v);
    }
    D_800987D8 = 0;
}

void func_8002CBDC(C80027678_SHADOW *rec, sint32 r, uint32 da, uint32 ang, sint32 dist)
{
    sint16 v[4][4];
    sint32 z;
    C80027678_FT4 *p;
    sint32 x;
    sint32 y;
    sint32 w;
    sint32 c;
    uint32 *ot;
    uint8 *prim;

    C80027678_GTE_SET_ROT(C80027678_ROT_A);
    C80027678_GTE_SET_TRANS_V(C80027678_TRANS_V);
    GTE_LDV0(rec);
    GTE_NOP2();
    GTE_RTPS();
    C80027678_GTE_STSZOTZ(&z);
    if (z > C80027678_FAR_Z || z < 0x30)
    {
        return;
    }
    prim                = *C80027678_PRIM_PTR;
    *C80027678_PRIM_PTR = prim + sizeof(C80027678_FT4);
    p                   = (C80027678_FT4 *)prim;
    if (dist > 0x240)
    {
        return;
    }
    if (dist < 0x40)
    {
        p->rgbc = 0x2E808080;
    }
    else
    {
        c       = (0x240 - dist) >> 2;
        p->rgbc = 0x2E000000 | (c << 16) | (c << 8) | c;
    }
    x       = rec->x << C80027678_SHIFT;
    y       = rec->y << C80027678_SHIFT;
    w       = rec->z << C80027678_SHIFT;
    v[0][0] = ((rsin(ang - da) * r) >> (12 - C80027678_SHIFT)) + x;
    v[0][1] = y;
    v[0][2] = ((rcos(ang - da) * r) >> (12 - C80027678_SHIFT)) + w;
    v[1][0] = ((rsin(ang + da) * r) >> (12 - C80027678_SHIFT)) + x;
    v[1][1] = y;
    v[1][2] = ((rcos(ang + da) * r) >> (12 - C80027678_SHIFT)) + w;
    v[2][0] = x * 2 - v[1][0];
    v[2][1] = y * 2 - v[1][1];
    v[2][2] = w * 2 - v[1][2];
    v[3][0] = x * 2 - v[0][0];
    v[3][1] = y * 2 - v[0][1];
    v[3][2] = w * 2 - v[0][2];
    C80027678_GTE_SET_TRANS(C80027678_ROT_A);
    GTE_LDV3C(v);
    GTE_NOP2();
    GTE_RTPT();
    p->clut  = 0x3EF4;
    p->tpage = 0x45;
    if (rec->flag != 0)
    {
        p->u0 = 0xC0;
        p->v0 = 0xE0;
        p->u1 = 0xDF;
        p->v1 = 0xE0;
        p->u2 = 0xC0;
        p->v2 = 0xFF;
        p->u3 = 0xDF;
        p->v3 = 0xFF;
    }
    else
    {
        p->u0 = 0xE0;
        p->v0 = 0xE0;
        p->u1 = 0xFF;
        p->v1 = 0xE0;
        p->u2 = 0xE0;
        p->v2 = 0xFF;
        p->u3 = 0xFF;
        p->v3 = 0xFF;
    }
    GTE_SWC2_OFF(12, 8, p);
    GTE_SWC2_OFF(13, 16, p);
    GTE_SWC2_OFF(14, 24, p);
    GTE_LDV0(v[3]);
    GTE_NOP2();
    GTE_RTPS();
    GTE_STSXY2(&p->x3);
    GTE_NOP2();
    C80027678_GTE_AVSZ4();
    GTE_SWC2(7, &z);
    ot     = C80027678_OT + (z >> 1);
    p->tag = *ot | 0x09000000;
    *ot    = (uint32)p & 0xFFFFFF;
}

void func_8002CFA4(void)
{
    func_800177CC((void *)0x8015BC00, (void *)0x8015BFFC);
    D_800987D8           = 0;
    C80027678_SCRATCH_75 = 0;
    C80027678_SCRATCH_04 = 0;
    C80027678_SCRATCH_06 = 0xE00;
    D_800988FC           = 0;
    C80027678_SCRATCH_76 = 0xE00;
}

// Scales the quotient and remainder in place (q *= 51, r *= 42) before packing them.
void func_8002D004(sint32 unused, uint32 x, uint32 y)
{
    uint32 q;
    uint32 r;

    q = x / 6;
    r = x % 6;
    q *= 51;
    r *= 42;
    func_8002D0D0((void *)0x800F7820, q << 8 | r);
    q = y / 6;
    r = y % 6;
    q *= 51;
    r *= 42;
    func_8002D0D0((void *)0x800F7830, q << 8 | r);
}

// Adds delta to the coordinate words of two record tables (0x44- and 0x54-byte records, two
// sub-records each). The word index m = i * 17 + j * 8 keeps retail's unreduced a3 * 4 address;
// j first holds the header word (retail reuses its register).
void func_8002D0D0(C80027678_COUNTS *c, sint32 delta)
{
    uint32 i;
    uint32 j;
    uint32 n_a;
    uint32 n_b;
    sint32 m;
    sint32 *da;
    sint32 *sa;
    sint32 *db;
    sint32 *sb;

    i   = 0;
    j   = c->counts;
    da  = (sint32 *)c->tbl_a;
    n_a = j & 0xFF;
    n_b = (j >> 8) & 0xFF;
    sa  = (sint32 *)((uint8 *)da + n_a * 0x44 + n_b * 0x54);
    for (; i < n_a; i++)
    {
        for (j = 0; j < 2; j++)
        {
            m         = i * 17 + j * 8;
            da[m + 3] = sa[m + 3] + delta;
            da[m + 5] = sa[m + 5] + delta;
            da[m + 7] = sa[m + 7] + delta;
        }
    }
    db = (sint32 *)c->tbl_b;
    sb = (sint32 *)((uint8 *)db + n_a * 0x44 + n_b * 0x54);
    for (i = 0; i < n_b; i++)
    {
        for (j = 0; j < 2; j++)
        {
            m         = i * 21 + j * 10;
            db[m + 3] = sb[m + 3] + delta;
            db[m + 5] = sb[m + 5] + delta;
            db[m + 7] = sb[m + 7] + delta;
            db[m + 9] = sb[m + 9] + delta;
        }
    }
}

// The id packs model, detail level, face list (tri/quad) and face index.
uint8 *func_8002D22C(C80027678_TBL *tbl, uint32 id)
{
    return (uint8 *)(&((C80027678_LOD *)(tbl->block[id >> 24] + 0x14))[(id >> 8) & 0xFF]
                          .tri)[(id >> 16) & 0xFF] +
           (id & 0xFF) * 12;
}

void func_8002D27C(C80027678_TBL *tbl, uint32 id, uint32 *src)
{
    uint32 *dst;

    dst = (uint32 *)((uint8 *)(&((C80027678_LOD *)(tbl->block[id >> 24] + 0x14))[(id >> 8) & 0xFF]
                                    .tri)[(id >> 16) & 0xFF] +
                     (id & 0xFF) * 12);
    dst[0] = src[0];
    dst[1] = src[1];
}

uint8 *func_8002D2DC(C80027678_TBL *tbl, uint32 id)
{
    return *(uint8 **)(tbl->block[id >> 24] + ((id >> 8) & 0xFF) * 20 + 0x24) + (id & 0xFF) * 8;
}

void func_8002D318(void)
{
}

// The header word is read once into the loop counter (retail keeps both in t0), and both part
// indices are taken from idx before the first record is read.
void func_8002D320(C80027678_MODEL *m, uint32 idx, sint32 delta)
{
    C80027678_PART *dst;
    C80027678_PART *src;
    uint32 n_a;
    uint32 n_b;
    uint32 i;
    uint32 dst_no;
    uint32 src_no;
    sint32 *da;
    sint32 *sa;
    sint32 *db;
    sint32 *sb;

    dst_no = idx & 0xFFFF;
    src_no = idx >> 16;
    dst    = (C80027678_PART *)(dst_no * 0x14 + (uint32)m->parts);
    da     = dst->buf_a;
    i      = dst->hdr;
    n_a    = (i & 0xFF) * 3;
    n_b    = ((i >> 8) & 0xFF) * 3;
    src    = (C80027678_PART *)(src_no * 0x14 + (uint32)m->parts);
    sa     = src->buf_a;
    db     = dst->buf_b;
    sb     = src->buf_b;
    for (i = 0; i < n_a; i += 3)
    {
        da[i]     = sa[i] + delta;
        da[i + 1] = sa[i + 1] + delta;
    }
    for (i = 0; i < n_b; i += 3)
    {
        db[i]     = sb[i] + delta;
        db[i + 1] = sb[i + 1] + delta;
    }
}

uint32 func_8002D404(uint32 a, uint32 b, uint32 c, uint32 d)
{
    uint32 q;
    uint32 r;

    q = a / d;
    r = (a - q * d) * b;
    return (q * c) << 24 | r << 16 | (q * c) << 8 | r;
}

uint8 *func_8002D464(void)
{
    uint8 *p;

    if (D_800988FC >= 0x100)
    {
        return 0;
    }
    p                        = *C80027678_PRIM_PTR;
    D_800BE6D8[D_800988FC++] = p;
    *C80027678_PRIM_PTR      = p + 0x28;
    return p;
}

uint8 *func_8002D4B8(void)
{
    uint8 *p;

    if (D_800988FC >= 0x100)
    {
        return 0;
    }
    p                        = *C80027678_PRIM_PTR;
    D_800BE6D8[D_800988FC++] = p;
    *C80027678_PRIM_PTR      = p + 0x20;
    return p;
}

// Billboard and line renderer. The identity matrix is loaded with separate rotation and
// translation macros (two asm statements): the extra uses give its pointer retail's t3.
void func_8002D50C(void)
{
    sint32 v[3];
    C80027678_SVEC pts[3];
    C80027678_SVEC scr[2];
    uint32 col;
    C80027678_BB *p;
    uint32 *ot;
    uint32 n;
    uint32 i;
    sint32 size;
    sint32 z;
    sint32 *mat;

    mat        = C80027678_MAT_ID;
    mat[0]     = 0x1000;
    mat[1]     = 0;
    mat[2]     = 0x1000;
    mat[3]     = 0;
    mat[4]     = 0x1000;
    mat[5]     = 0;
    mat[6]     = 0;
    mat[7]     = 0;
    n          = D_800988FC;
    D_800988FC = 0;
    GTE_SET_MATRIX(C80027678_ROT_A);
    for (i = 0; i < n; i++)
    {
        p = (C80027678_BB *)D_800BE6D8[i];
        if ((p->rgbc.c.code >> 5) == 1)
        {
            *(uint32 *)&pts[0].vx = p->xy0;
            *(uint32 *)&pts[0].vz = p->xy1;
            GTE_LDV0(&pts[0]);
            GTE_NOP2();
            GTE_RTV0();
            GTE_STLVNL(v);
            if (v[2] > (C80027678_FAR_Z << 2) || v[2] < 0xC0)
            {
                continue;
            }
            GTE_NOP2();
            GTE_RTPS();
            GTE_STSXY2(&scr[0]);
            if ((uint16)(scr[0].vx + 0x160) > 0x400 || (uint16)(scr[0].vy + 0x88) > 0x400)
            {
                continue;
            }
            GTE_SET_ROT_MATRIX(mat);
            GTE_SET_TRANS_MATRIX(mat);
            size      = p->xy2;
            pts[0].vx = v[0] - size;
            pts[0].vy = v[1] - size;
            pts[1].vx = v[0] + size;
            pts[1].vy = v[1] + size;
            pts[2].vx = v[0];
            pts[2].vy = v[1];
            z         = v[2];
            pts[0].vz = pts[1].vz = pts[2].vz = z;
            GTE_LDV3C(pts);
            GTE_NOP2();
            GTE_RTPT();
            ot = C80027678_OT + (z >> 3);
            if (p->xy3 & 8)
            {
                p->tag = *ot | 0x09000000;
                *ot    = (uint32)p & 0xFFFFFF;
            }
            else
            {
                C80027678_SCRATCH_E0 = D_800C0DC0[(z / 512) & 0x1F] << 16;
                GTE_LWC2(6, &p->rgbc);
                GTE_NOP2();
                GTE_DPCS_RUN();
                p->tag = *ot | 0x09000000;
                *ot    = (uint32)p & 0xFFFFFF;
                GTE_SWC2(22, &col);
                p->rgbc.word = col;
                p->uv0 |= C80027678_SCRATCH_E0;
            }
            GTE_STSXY0(&p->xy0);
            GTE_STSXY0(&scr[0]);
            GTE_STSXY1(&p->xy3);
            GTE_STSXY1(&scr[1]);
            p->xy1 = (scr[0].vy << 16) | (uint16)scr[1].vx;
            p->xy2 = (scr[1].vy << 16) | (uint16)scr[0].vx;
            GTE_SET_MATRIX(C80027678_ROT_A);
        }
        else
        {
            *(uint32 *)&pts[0].vx = p->xy0;
            *(uint32 *)&pts[0].vz = p->xy1;
            // Scheduling barrier: retail keeps both vertex-word copies ahead of the tag copy
            __asm__ volatile("");
            *(uint32 *)&pts[1].vx = p->tag;
            pts[1].vz             = pts[0].pad;
            GTE_LDV3C(pts);
            GTE_NOP2();
            GTE_RTPT();
            p->uv1 = ((uint32)p & 0xFFFFFF) | 0x02000000;
            p->uv2 = 0;
            C80027678_GTE_STSZ3(v);
            if (v[0] > (C80027678_FAR_Z << 2) || v[0] < 0xC0)
            {
                continue;
            }
            ot     = C80027678_OT + ((v[0] + v[1]) >> 4);
            p->tag = *ot | 0x04000000;
            *ot    = (uint32)&p->uv1 & 0xFFFFFF;
            GTE_STSXY0(&p->xy0);
            GTE_STSXY1(&p->xy1);
        }
    }
}
