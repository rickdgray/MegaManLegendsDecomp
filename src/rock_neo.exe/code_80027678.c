#include "common.h"
#include "code_80027678.h"
#include "code_8001786C.h"
#include "code_80048620.h"
#include "code_8005C258.h"
#include "fastmem.h"
#include "game.h"
#include "player.h"
#include "psyq/inline_c.h"
#include "psyq/libetc.h"
#include "scene.h"
#include "scratch.h"
#include "system.h"
#include "stage.h"

// Small uninitialized statics (.sbss 0x80098550-0x8009855C).
static sint32 D_80098550;
static sint32 D_80098554[2];

// Called only from this file
void pl_body_draw(PL_WORK *pl, u_long *ot);
sint32 func_80027F78(PL_WORK *pl, u_long *ot);
void shl_work_draw(void);
void work_48_draw(void);
void work_50_draw(void);
void shadow_draw_all(void);
void billboard_queue_draw(void);
void func_800289A0(MESH *m);
void prim_mesh_tri_draw(uint32 *p, u_long *ot, SVECTOR **vtx);
void prim_mesh_quad_draw(uint32 *p, u_long *ot, SVECTOR **vtx);
void func_80029608(MESH *m);
void func_8002A6E8(MESH *m, u_long rgb, uint32 flags);
void func_8002AEE4(MESH *m, u_long *rgb);
void mesh_gt_vtx_rgb_draw(MESH *m, u_long *rgb_tbl, u_long rgb);
void mesh_gt_face_rgb_draw(MESH *m, u_long *rgb_tbl, u_long rgb);
void shadow_draw(SVECTOR *pos, sint32 r, uint32 da, uint32 ang, sint32 dist);
void prim_mesh_uv_copy(PRIM_MESH *m, sint32 delta);

// Draws the frame's objects: each live player into its own ordering table (D_8009BF88,
// D_8009AE48), then the shots, the WORK_48 and WORK_50 pools, the shadows and the billboards,
// timing each pass in VSync(1) counts. Nothing while D_80098824 is set.
void Obj_draw_all(void)
{
    PL_WORK *pl;
    sint32 unused[2]; // never used; keeps the frame size

    if (D_80098824 == 0)
    {
        pl = &Player_work[0];
        if (((sint8)pl->unk00 & Player_work[0].flags_6 & 2) && func_80027F78(pl, D_8009BF88[Dbl_buff_idx]) != 0)
        {
            pl_body_draw(pl, D_8009BF88[Dbl_buff_idx]);
        }
        pl = &Player_work[1];
        if (((sint8)pl->unk00 & Player_work[1].flags_6 & 2) && func_80027F78(pl, D_8009AE48[Dbl_buff_idx]) != 0)
        {
            pl_body_draw(pl, D_8009AE48[Dbl_buff_idx]);
        }
        D_800D9BE4 = VSync(1);
        shl_work_draw();
        D_800D9BF0 = (VSync(1) - D_800D9BE4) & 0xFFFF;
        D_800D9BE4 = VSync(1);
        work_48_draw();
        D_800D9BF4 = (VSync(1) - D_800D9BE4) & 0xFFFF;
        D_800D9BE4 = VSync(1);
        work_50_draw();
        D_800D9BF8 = (VSync(1) - D_800D9BE4) & 0xFFFF;
        D_800D9BE4 = VSync(1);
        shadow_draw_all();
        D_800D9BEC = (VSync(1) - D_800D9BE4) & 0xFFFF;
        D_800D9BE4 = VSync(1);
        billboard_queue_draw();
        D_800D9BE8 = (VSync(1) - D_800D9BE4) & 0xFFFF;
    }
}

// Draws the player pl into its ordering table ot (func_80027F78): the meshes of its 5 body parts,
// from one of three variants of the body (by weapon_right_no and unk171), each mesh by the matrix of its
// joint (D_80089938) times the view matrix.
void pl_body_draw(PL_WORK *pl, u_long *ot)
{
    sint32 unused[4]; // never used; keeps the frame size
    sint32 v[3];
    sint32 var;
    sint32 i;
    sint32 j;
    sint32 k;
    sint32 n;

    if (pl->unk171 == 0)
    {
        var = 0;
    }
    else if (pl->weapon_right_no == 0)
    {
        var = 2;
    }
    else
    {
        var = 1;
    }
    for (i = 0, k = 0; i < 5; i++)
    {
        n                 = D_80089928[var][i];
        Scratch_prim_mesh = D_800898EC[var][i];
        for (j = 0; j < n; j++)
        {
            gte_MulMatrix0(&Scratch_view_mtx, &pl->joint_mtx[D_80089938[k]], &Scratch_mtx);
            gte_SetRotMatrix(&Scratch_view_mtx);
            gte_ldv0(&pl->joint_pos[D_80089938[k]]);
            gte_rtv0();
            gte_stlvnl(v);
            Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + v[0];
            Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + v[1];
            Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + v[2];
            gte_SetRotMatrix(&Scratch_mtx);
            gte_SetTransMatrix(&Scratch_mtx);
            k++;
            prim_mesh_tri_draw((uint32 *)Scratch_prim_mesh, ot, &Scratch_prim_mesh->vtx);
            prim_mesh_quad_draw((uint32 *)Scratch_prim_mesh, ot, &Scratch_prim_mesh->vtx);
            Scratch_prim_mesh++;
        }
    }
}

// Draws the triangles of m that face the camera: projects each one's vertices (from *vtx), writes
// the screen positions and the fog CLUT bits into this frame's primitive, and links it into ot at
// its depth (ot covers the depths from D_80098550 up, func_80027F78). The primitives are walked
// as words, a face (17 words) at a time: 0 is the tag, 1 the colour, 3 the uv0 / CLUT word. The
// projection before the loop is wasted: the loop projects the first face again. p is passed the
// PRIM_MESH and then reused as the primitive cursor (one register in the target).
void prim_mesh_tri_draw(uint32 *p, u_long *ot, SVECTOR **vtx)
{
    long opz;
    long otz;
    PRIM_MESH *m;
    PRIM_TRI *tri;
    uint32 *idx;
    SVECTOR *v;
    uint32 w;
    sint32 n;
    u_long rgbc;
    u_long mask;
    u_long tag;
    u_long *clut_bits;
    u_long clut_mask;

    m   = (PRIM_MESH *)p;
    tri = m->tri;
    n   = m->n_tri;
    v   = *vtx;
    idx = &tri->idx;
    p   = (uint32 *)&tri->prim[Dbl_buff_idx];
    w   = *idx;
    gte_ldv3(&v[w & 0xFF], &v[(w & 0xFF00) >> 8], &v[(w >> 16) & 0xFF]);
    gte_rtpt();
    mask = 0xFFFFFF;
    rgbc = Scratch_rgbc;
    tag  = 0x07000000;
    while (n != 0)
    {
        w = *idx;
        gte_ldv3(&v[w & 0xFF], &v[(w & 0xFF00) >> 8], &v[(w & 0xFF0000) >> 16]);
        gte_rtpt();
        gte_nclip();
        n--;
        clut_mask = 0xFFF8FFFF;
        clut_bits = &Scratch_clut_bits;
        gte_stopz(&opz);
        if (opz > 0)
        {
            gte_stsxy3_ft3(p);
            gte_avsz3();
            p[3] = (p[3] & clut_mask) | *clut_bits;
            gte_stotz(&otz);
            p[0]                 = tag | ot[otz - D_80098550];
            ot[otz - D_80098550] = (u_long)p & mask;
            p[1]                 = rgbc;
        }
        idx += sizeof(PRIM_TRI) / 4;
        p += sizeof(PRIM_TRI) / 4;
    }
}

// The same for the quads of m (POLY_FT4: the fourth corner projected on its own; the code bit
// 0x08 turns Scratch_rgbc's POLY_FT3 code into a POLY_FT4 one). Faces are 21 words. The GTE
// commands' nops are statements of their own: with the one-statement macros the loop is short
// enough for GCC to hoist the 0xFFF8FFFF constant out of it, which the target doesn't.
void prim_mesh_quad_draw(uint32 *p, u_long *ot, SVECTOR **vtx)
{
    long opz;
    long otz;
    PRIM_MESH *m;
    PRIM_QUAD *quad;
    uint32 *idx;
    SVECTOR *v;
    uint32 w;
    sint32 n;
    u_long rgbc;
    u_long mask;
    u_long tag;

    m    = (PRIM_MESH *)p;
    quad = m->quad;
    n    = m->n_quad;
    v    = *vtx;
    idx  = &quad->idx;
    p    = (uint32 *)&quad->prim[Dbl_buff_idx];
    w    = *idx;
    gte_ldv3(&v[w & 0xFF], &v[(w & 0xFF00) >> 8], &v[(w >> 16) & 0xFF]);
    gte_rtpt();
    mask = 0xFFFFFF;
    rgbc = Scratch_rgbc | 0x08000000;
    tag  = 0x09000000;
    while (n != 0)
    {
        w = *idx;
        gte_ldv3(&v[w & 0xFF], &v[(w & 0xFF00) >> 8], &v[(w >> 16) & 0xFF]);
        gte_nop();
        gte_nop();
        gte_rtpt_b();
        gte_nop();
        gte_nop();
        gte_nclip_b();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            gte_stsxy3_ft4(p);
            gte_ldv0(&v[w >> 24]);
            gte_nop();
            gte_nop();
            gte_rtps_b();
            gte_stsxy(p + 8);
            gte_nop();
            gte_nop();
            gte_avsz4_b();
            p[3] = (p[3] & 0xFFF8FFFF) | Scratch_clut_bits;
            gte_stotz(&otz);
            p[0]                 = tag | ot[otz - D_80098550];
            ot[otz - D_80098550] = (u_long)p & mask;
            p[1]                 = rgbc;
        }
        idx += sizeof(PRIM_QUAD) / 4;
        p += sizeof(PRIM_QUAD) / 4;
    }
}

// Before a player is drawn into its own ordering table ot (512 entries, one per depth from the
// player's depth - 0x100): projects the player's first joint, sets the colour its primitives get
// (Scratch_rgbc: dimmed by a sine wave, every other frame, while either countdown of
// code_8005C258 runs, and semi-transparent while the second does), depth-cued, and the fog CLUT
// bits, then links ot into the frame's ordering table, two depths to an entry. Returns 0 when the
// player is beyond the fog (nothing to draw).
sint32 func_80027F78(PL_WORK *pl, u_long *ot)
{
    SVECTOR pos;
    long z;
    sint32 cnt0;
    sint32 cnt1;
    sint32 c;
    sint32 lo;
    sint32 hi;
    sint32 end;
    sint32 i;

    pos.vx        = pl->joint_pos[0].vx;
    pos.vy        = pl->joint_pos[0].vy;
    pos.vz        = pl->joint_pos[0].vz;
    D_80098554[0] = 0;
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    gte_ldv0(&pos);
    gte_rtps();
    gte_stszotz(&z);
    Scratch_rgbc = 0x24808080;
    if (Scene_work.unk00 == 0)
    {
        cnt0 = func_8005EBC4();
        cnt1 = func_8005EBD4();
        if (cnt0 >= 90 || cnt1 >= 90 || !(System_timer & 1))
        {
            if (cnt0 != 0)
            {
                c            = (D_800BBCF8[(System_timer & 0x1F) * 2] >> 6) + 0xBF;
                Scratch_rgbc = 0x24000000 | c | (c << 8) | (c << 16);
            }
            if (cnt1 != 0)
            {
                Scratch_rgbc |= 0x02000000;
            }
        }
    }
    gte_ldrgb(&Scratch_rgbc);
    gte_dpcs();
    gte_strgb(&Scratch_rgbc);
    Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    if (z > Scratch_fog_0)
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
        addPrims(&D_800A4D40[Dbl_buff_idx][lo >> 1], ot + lo - z - 1, ot);
    }
    for (i = lo; i < hi; i += 2)
    {
        if (i >= 0)
        {
            addPrims(&D_800A4D40[Dbl_buff_idx][i >> 1], &ot[i - z + 1], &ot[i - z]);
        }
    }
    if (end >= 0)
    {
        addPrims(&D_800A4D40[Dbl_buff_idx][end >> 1], &ot[0x1FF], ot + hi - z);
    }
    return 1;
}

// The same as Model_parts_draw, but each part through func_800289A0 (only the faces within the
// first 0x800 entries of Scratch_ot).
void func_8002831C(MODEL_WORK *wp)
{
    VECTOR v;
    SVECTOR unused; // never used; keeps the frame size
    DVECTOR sxy;
    long z;
    sint32 col;
    sint32 c;
    sint32 i;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransVector(&Scratch_trans);
    gte_ldv0(&wp->pos);
    gte_rtps();
    gte_stdp(&Scratch_dp);
    gte_stsxy(&sxy);
    gte_stszotz(&z);
    wp->flags &= 0x7F;
    if (!(wp->routine_0 & 0x40) || z >= Scratch_fog_0)
    {
        if (z > Scratch_fog_0 || z < (0x30 >> Scratch_scale_shift))
        {
            return;
        }
        if ((u_short)(sxy.vx + 0x160) > 0x400 || (u_short)(sxy.vy + 0x88) > 0x400)
        {
            return;
        }
    }
    wp->flags |= 0x80;
    Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    if (z > 0x708)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[2][1];
    }
    else if (z > 0x2BC)
    {
        if (Scratch_fog_2 & 8)
        {
            Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[2][1];
        }
        else
        {
            Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[1][1];
        }
    }
    else
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[0][1];
    }
    col          = wp->scale_158.pad;
    z            = wp->slot_F8[0].child_id; // the part count
    Scratch_rgbc = RGB555_TO_RGBC(col);
    gte_ldrgb(&Scratch_rgbc);
    gte_dpcs();
    gte_strgb(&Scratch_rgbc);
    for (i = 0; i < z; i++)
    {
        if (wp->slot_F8[i].hide_3 < 0)
        {
            continue;
        }
        if ((wp->kind_1 & 0xE0) == 0x40)
        {
            gte_MulMatrix0(&Scratch_view_mtx, &((WORK_5A4 *)wp)->mtx_240[i], &Scratch_mtx);
        }
        else
        {
            gte_MulMatrix0(&Scratch_view_mtx, &((WORK_3C0 *)wp)->mtx_1E8[i], &Scratch_mtx);
        }
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_ldv0(&wp->part_180[i]);
        gte_rtv0();
        gte_stlvnl(&v);
        Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + v.vx;
        Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + v.vy;
        Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + v.vz;
        gte_SetRotMatrix(&Scratch_mtx);
        gte_SetTransMatrix(&Scratch_mtx);
        if (col == 0)
        {
            c            = wp->part_180[i].pad;
            Scratch_rgbc = RGB555_TO_RGBC(c);
            // Restores the depth-cue value saved above, but loads its address, not the value
            // (the target's mtc2 takes the address).
            gte_lddp(&Scratch_dp);
            gte_ldrgb(&Scratch_rgbc);
            gte_dpcs();
            gte_strgb(&Scratch_rgbc);
        }
        func_800289A0(Scratch_mesh_tbl + wp->slot_F8[i].mesh_0);
    }
}

// The same as func_80029608, but a face is only linked when its depth falls within the first
// 0x800 entries of Scratch_ot.
#ifdef NON_MATCHING
// Only a register swap remains: the target keeps m in t3 and f in t2 (func_80029608 has them the
// other way round, as this version does). Splitting the GTE commands' nops into statements of
// their own (vertex, triangle or quad loop) doesn't change it.
void func_800289A0(MESH *m)
{
    long sz[4];
    long opz;
    u_long otz;
    long *sxy;
    uint16 *sz_tbl;
    SVECTOR *v;
    MESH_FACE *f;
    POLY_FT3 *p3;
    POLY_FT4 *p4;
    u_long *ot;
    uint32 ct;
    u_long mask;
    u_long tag;
    u_long code;
    uint32 i;
    uint32 n;
    uint32 n_vtx;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;
    uint32 w;

    mask   = 0xFFFFFF;
    sxy    = Scratch_sxy;
    sz_tbl = Scratch_sz;
    n_vtx  = m->n_vtx;
    ct     = m->clut_tpage;
    v      = m->vtx;
    for (i = 0; i < n_vtx; i += 3)
    {
        gte_ldv3c(&v[i]);
        gte_rtpt();
        gte_stsxy3c(&sxy[i]);
        gte_stsz3c(sz);
        sz_tbl[i]     = sz[0];
        sz_tbl[i + 1] = sz[1];
        sz_tbl[i + 2] = sz[2];
    }
    tag  = 0x07000000;
    code = Scratch_rgbc | 0x24000000; // POLY_FT3
    for (n = m->n_tri, f = m->tri; n != 0; f++)
    {
        w  = f->idx.word;
        i0 = w & 0xFF;
        i1 = (w >> 8) & 0xFF;
        i2 = (w >> 16) & 0xFF;
        gte_ldSXY012(sxy[i0], sxy[i1], sxy[i2]);
        gte_nclip();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            p3           = (POLY_FT3 *)Map_prim_ptr;
            Map_prim_ptr = (POLY_FT4 *)(p3 + 1);
            gte_stsxy3_ft3(p3);
            gte_ldsz3(sz_tbl[i0], sz_tbl[i1], sz_tbl[i2]);
            gte_avsz3();
            gte_stotz(&otz);
            ot = Scratch_ot + (otz >> 1);
            if ((otz >> 1) * sizeof(u_long) >= 0x2000)
            {
                continue;
            }
            p3->tag            = (u_long *)(tag | *ot);
            *ot                = (u_long)p3 & mask;
            *(u_long *)&p3->r0 = code;
            *(u_long *)&p3->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
            *(u_long *)&p3->u1 = (ct << 16) | f->uv.pair[1] | (getTPage(0, 1, 0, 0) << 16);
            *(u_long *)&p3->u2 = f->uv.pair[2];
        }
    }
    tag  = 0x09000000;
    code = Scratch_rgbc | 0x2C000000; // POLY_FT4
    for (n = m->n_quad, f = m->quad; n != 0; f++)
    {
        // Never used; keeps the frame size. Block-local: the target has it above opz and otz,
        // where only a block after their first use puts it.
        long unused[4];

        w  = f->idx.word;
        i0 = w & 0xFF;
        i1 = (w >> 8) & 0xFF;
        i2 = (w >> 16) & 0xFF;
        i3 = w >> 24;
        gte_ldSXY012(sxy[i0], sxy[i1], sxy[i2]);
        gte_nclip();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            p4           = Map_prim_ptr;
            Map_prim_ptr = p4 + 1;
            gte_stsxy3_ft4(p4);
            *(long *)&p4->x3 = sxy[i3];
            gte_ldsz4(sz_tbl[i0], sz_tbl[i1], sz_tbl[i2], sz_tbl[i3]);
            gte_avsz4();
            gte_stotz(&otz);
            ot = Scratch_ot + (otz >> 1);
            if ((otz >> 1) * sizeof(u_long) >= 0x2000)
            {
                continue;
            }
            p4->tag            = (u_long *)(tag | *ot);
            *ot                = (u_long)p4 & mask;
            *(u_long *)&p4->r0 = code;
            *(u_long *)&p4->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
            *(u_long *)&p4->u1 = (ct << 16) | f->uv.pair[1] | (getTPage(0, 1, 0, 0) << 16);
            *(u_long *)&p4->u2 = f->uv.pair[2];
            *(u_long *)&p4->u3 = f->uv.pair[3];
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_800289A0);
#endif

// Draws the live model objects of the D_800C3580 and D_8009F108 pools, last slot first: through
// func_8002831C on stage 0x17, else Model_parts_draw. Times each pool's pass in VSync(1) counts.
// Nothing while D_80098824 is set.
void Model_draw_all(void)
{
    sint32 i;
    WORK_5A4 *a;
    WORK_3C0 *b;

    if (D_80098824 == 0)
    {
        D_800D9BE4 = VSync(1);
        i          = 4;
        while (i != 0)
        {
            i--;
            a = &D_800C3580[i];
            if (Game_work.stage_no == 0x17)
            {
                if ((sint8)a->routine_0 & a->flags & 2)
                {
                    func_8002831C((MODEL_WORK *)a);
                }
            }
            else if ((sint8)a->routine_0 & a->flags & 2)
            {
                Model_parts_draw((MODEL_WORK *)a);
            }
        }
        D_800D9BFC = (VSync(1) - D_800D9BE4) & 0xFFFF;
        D_800D9BE4 = VSync(1);
        i          = 16;
        while (i != 0)
        {
            i--;
            b = &D_8009F108[i];
            if (Game_work.stage_no == 0x17)
            {
                if ((sint8)b->routine_0 & b->flags & 2)
                {
                    func_8002831C((MODEL_WORK *)b);
                }
            }
            else if ((sint8)b->routine_0 & b->flags & 2)
            {
                Model_parts_draw((MODEL_WORK *)b);
            }
        }
        D_800D9C00 = (VSync(1) - D_800D9BE4) & 0xFFFF;
    }
}

// Draws a model object (WORK_3C0, or WORK_5A4 for pool kind 0x40) part by part, each part's mesh
// (func_80029608) at the level of detail its depth picks, by the part's matrix times the view
// matrix, in the object's RGB555 colour (scale_158.pad; 0: each part's own, part_180[n].pad),
// depth-cued. Bit 7 of flags says whether it was drawn: it is skipped beyond the fog, too near or
// off the screen, unless routine_0 has bit 6 and it is nearer than the fog.
void Model_parts_draw(MODEL_WORK *wp)
{
    VECTOR v;
    SVECTOR unused; // never used; keeps the frame size
    DVECTOR sxy;
    long z;
    sint32 col;
    sint32 c;
    sint32 i;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransVector(&Scratch_trans);
    gte_ldv0(&wp->pos);
    gte_rtps();
    gte_stdp(&Scratch_dp);
    gte_stsxy(&sxy);
    gte_stszotz(&z);
    wp->flags &= 0x7F;
    if (!(wp->routine_0 & 0x40) || z >= Scratch_fog_0)
    {
        if (z > Scratch_fog_0 || z < (0x30 >> Scratch_scale_shift))
        {
            return;
        }
        if ((u_short)(sxy.vx + 0x160) > 0x400 || (u_short)(sxy.vy + 0x88) > 0x400)
        {
            return;
        }
    }
    wp->flags |= 0x80;
    Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    if (z > 0x708)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[2][1];
    }
    else if (z > 0x2BC)
    {
        if (Scratch_fog_2 & 8)
        {
            Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[2][1];
        }
        else
        {
            Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[1][1];
        }
    }
    else
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)wp->data_88)->lod[0][1];
    }
    col          = wp->scale_158.pad;
    z            = wp->slot_F8[0].child_id; // the part count
    Scratch_rgbc = RGB555_TO_RGBC(col);
    gte_ldrgb(&Scratch_rgbc);
    gte_dpcs();
    gte_strgb(&Scratch_rgbc);
    for (i = 0; i < z; i++)
    {
        if (wp->slot_F8[i].hide_3 < 0)
        {
            continue;
        }
        if ((wp->kind_1 & 0xE0) == 0x40)
        {
            gte_MulMatrix0(&Scratch_view_mtx, &((WORK_5A4 *)wp)->mtx_240[i], &Scratch_mtx);
        }
        else
        {
            gte_MulMatrix0(&Scratch_view_mtx, &((WORK_3C0 *)wp)->mtx_1E8[i], &Scratch_mtx);
        }
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_ldv0(&wp->part_180[i]);
        gte_rtv0();
        gte_stlvnl(&v);
        Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + v.vx;
        Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + v.vy;
        Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + v.vz;
        gte_SetRotMatrix(&Scratch_mtx);
        gte_SetTransMatrix(&Scratch_mtx);
        if (col == 0)
        {
            c            = wp->part_180[i].pad;
            Scratch_rgbc = RGB555_TO_RGBC(c);
            gte_ldrgb(&Scratch_rgbc);
            gte_dpcs();
            gte_strgb(&Scratch_rgbc);
        }
        func_80029608(Scratch_mesh_tbl + wp->slot_F8[i].mesh_0);
    }
}

// Draws m as mesh_draw does: projects all its vertices three at a time into Scratch_sxy and
// Scratch_sz, then draws the faces that face the camera as textured polygons (POLY_FT3, POLY_FT4)
// of colour Scratch_rgbc.
void func_80029608(MESH *m)
{
    long sz[4];
    long opz;
    u_long otz;
    long *sxy;
    uint16 *sz_tbl;
    SVECTOR *v;
    MESH_FACE *f;
    POLY_FT3 *p3;
    POLY_FT4 *p4;
    u_long *ot;
    uint32 ct;
    u_long mask;
    u_long tag;
    u_long code;
    uint32 i;
    uint32 n;
    uint32 n_vtx;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;
    uint32 w;

    mask   = 0xFFFFFF;
    sxy    = Scratch_sxy;
    sz_tbl = Scratch_sz;
    n_vtx  = m->n_vtx;
    ct     = m->clut_tpage;
    v      = m->vtx;
    for (i = 0; i < n_vtx; i += 3)
    {
        gte_ldv3c(&v[i]);
        gte_rtpt();
        gte_stsxy3c(&sxy[i]);
        gte_stsz3c(sz);
        sz_tbl[i]     = sz[0];
        sz_tbl[i + 1] = sz[1];
        sz_tbl[i + 2] = sz[2];
    }
    tag  = 0x07000000;
    code = Scratch_rgbc | 0x24000000; // POLY_FT3
    for (n = m->n_tri, f = m->tri; n != 0; f++)
    {
        w  = f->idx.word;
        i0 = w & 0xFF;
        i1 = (w >> 8) & 0xFF;
        i2 = (w >> 16) & 0xFF;
        gte_ldSXY012(sxy[i0], sxy[i1], sxy[i2]);
        gte_nclip();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            p3           = (POLY_FT3 *)Map_prim_ptr;
            Map_prim_ptr = (POLY_FT4 *)(p3 + 1);
            gte_stsxy3_ft3(p3);
            gte_ldsz3(sz_tbl[i0], sz_tbl[i1], sz_tbl[i2]);
            gte_avsz3();
            gte_stotz(&otz);
            ot                 = Scratch_ot + (otz >> 1);
            p3->tag            = (u_long *)(tag | *ot);
            *ot                = (u_long)p3 & mask;
            *(u_long *)&p3->r0 = code;
            *(u_long *)&p3->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
            *(u_long *)&p3->u1 = (ct << 16) | f->uv.pair[1] | (getTPage(0, 1, 0, 0) << 16);
            *(u_long *)&p3->u2 = f->uv.pair[2];
        }
    }
    tag  = 0x09000000;
    code = Scratch_rgbc | 0x2C000000; // POLY_FT4
    for (n = m->n_quad, f = m->quad; n != 0; f++)
    {
        w  = f->idx.word;
        i0 = w & 0xFF;
        i1 = (w >> 8) & 0xFF;
        i2 = (w >> 16) & 0xFF;
        i3 = w >> 24;
        gte_ldSXY012(sxy[i0], sxy[i1], sxy[i2]);
        gte_nclip();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            p4           = Map_prim_ptr;
            Map_prim_ptr = p4 + 1;
            gte_stsxy3_ft4(p4);
            *(long *)&p4->x3 = sxy[i3];
            gte_ldsz4(sz_tbl[i0], sz_tbl[i1], sz_tbl[i2], sz_tbl[i3]);
            gte_avsz4();
            gte_stotz(&otz);
            ot                 = Scratch_ot + (otz >> 1);
            p4->tag            = (u_long *)(tag | *ot);
            *ot                = (u_long)p4 & mask;
            *(u_long *)&p4->r0 = code;
            *(u_long *)&p4->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
            *(u_long *)&p4->u1 = (ct << 16) | f->uv.pair[1] | (getTPage(0, 1, 0, 0) << 16);
            *(u_long *)&p4->u2 = f->uv.pair[2];
            *(u_long *)&p4->u3 = f->uv.pair[3];
        }
    }
}

// Draws the shots of both pools, as work_48_draw does the effects. A player's shot spells out its
// sprite EFC at 0x88 (PL_SHL_WORK), hence the cast.
void shl_work_draw(void)
{
    uint32 i;
    PL_SHL_WORK *ps;
    SHL_WORK *sh;
    sint32 flags;

    for (i = 0; i < 16; i++)
    {
        ps    = &D_800BFB20[i];
        flags = (sint8)ps->routine_0;
        if (flags & ps->flags & WORK_DRAW)
        {
            D_800898D0[(flags & 0x1C) >> 2]((EFC *)&ps->code_88, flags);
        }
    }
    for (i = 0; i < 32; i++)
    {
        sh    = &D_8009CF88[i];
        flags = (sint8)sh->routine_0;
        if (flags & sh->flags & WORK_DRAW)
        {
            D_800898D0[(flags & 0x1C) >> 2](&sh->efc, flags);
        }
    }
}

void work_48_draw(void)
{
    uint32 i;
    WORK_48 *wp;
    sint32 flags;

    for (i = 0; i < 64; i++)
    {
        wp    = &D_800A3B40[i];
        flags = (sint8)wp->routine_0;
        if (flags & wp->flags & WORK_DRAW)
        {
            D_800898D0[(flags & 0x1C) >> 2](&wp->efc, flags);
        }
    }
}

void work_50_draw(void)
{
    uint32 i;
    WORK_50 *wp;
    sint32 flags;

    for (i = 0; i < 32; i++)
    {
        wp    = &D_800BF118[i];
        flags = (sint8)wp->routine_0;
        if (flags & wp->flags & WORK_DRAW)
        {
            D_800898D0[(flags & 0x1C) >> 2](&wp->efc, flags);
        }
    }
}

// Draw functions 0 and 2 of D_800898D0: draws a sprite EFC as a square POLY_FT4 facing the camera,
// size across (rolled by angle with flags bit 5) and depth-cued unless flags has bit 3, its
// texture the 32 x 32 cell at u, v. The fourth corner is the second's mirror through the centre.
void Efc_sprite_draw(EFC *efc, sint32 flags)
{
    MATRIX m;
    VECTOR pos;
    SVECTOR v[3];
    DVECTOR sxy[3];
    CVECTOR rgb;
    POLY_FT4 *p;
    u_long *ot;
    uint32 size;
    uint32 s;
    uint32 c;
    uint32 uv;

    if (Scratch_scale_shift == 0)
    {
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_SetTransVector(&Scratch_trans);
        gte_ldv0(efc->sprite.pos);
        gte_rt();
        gte_stlvnl(&pos);
        if (pos.vz > Scratch_fog_0 * 4 || pos.vz < 0xC0)
        {
            return;
        }
        size = efc->sprite.size;
    }
    else
    {
        gte_SetRotMatrix(&Scratch_view_mtx);
        gte_SetTransVector(&Scratch_trans);
        gte_ldv0(efc->sprite.pos);
        gte_rt();
        gte_stlvnl(&pos);
        if (pos.vz > Scratch_fog_0 * 4 || pos.vz < (0xC0 >> Scratch_scale_shift))
        {
            return;
        }
        gte_SetTransMatrix(&Scratch_view_mtx);
        v[0].vx = efc->sprite.pos[0] << Scratch_scale_shift;
        v[0].vy = efc->sprite.pos[1] << Scratch_scale_shift;
        v[0].vz = efc->sprite.pos[2] << Scratch_scale_shift;
        gte_ldv0(&v[0]);
        gte_rt();
        gte_stlvnl(&pos);
        if (pos.vz < 0)
        {
            return;
        }
        size = efc->sprite.size << Scratch_scale_shift;
    }
    *(uint32 *)&m.m[0][0] = 0x1000; // identity: m[0][0] = 1.0, m[0][1] = 0
    *(uint32 *)&m.m[0][2] = 0;
    *(uint32 *)&m.m[1][1] = 0x1000;
    *(uint32 *)&m.m[2][0] = 0;
    *(uint32 *)&m.m[2][2] = 0x1000;
    m.t[0]                = 0;
    m.t[1]                = 0;
    m.t[2]                = 0;
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
    p = Map_prim_ptr++;
    if (flags & 0x20)
    {
        s       = (D_800BBCF8[efc->sprite.angle & 0x3F] * size) >> 12;
        c       = (D_800BAEB0[efc->sprite.angle & 0x3F] * size) >> 12;
        v[0].vx = pos.vx - c + s;
        v[0].vy = pos.vy - c - s;
        v[1].vx = pos.vx + c + s;
        v[1].vy = pos.vy - c + s;
    }
    else
    {
        v[0].vx = pos.vx - size;
        v[0].vy = pos.vy - size;
        v[1].vx = pos.vx + size;
        v[1].vy = pos.vy - size;
    }
    v[2].vx = pos.vx;
    v[2].vy = pos.vy;
    v[0].vz = v[1].vz = v[2].vz = pos.vz;
    gte_ldv3c(v);
    gte_rtpt();
    ot = &Scratch_ot[pos.vz >> 3];
    uv = *(uint16 *)&efc->sprite.u;
    if (flags & 8)
    {
        p->tag            = (u_long *)(*ot | 0x09000000);
        *ot               = (u_long)p & 0xFFFFFF;
        *(u_long *)&p->r0 = efc->sprite.rgbc | 0x2C000000; // POLY_FT4
        *(u_long *)&p->u0 = uv | (efc->sprite.code & 0xFFFF0000);
    }
    else
    {
        Scratch_clut_bits = D_800C0DC0.b[(pos.vz / 512) & 0x1F] << 16;
        gte_ldrgb(&efc->sprite.rgbc);
        gte_dpcs();
        p->tag = (u_long *)(*ot | 0x09000000);
        *ot    = (u_long)p & 0xFFFFFF;
        gte_strgb(&rgb);
        *(u_long *)&p->r0 = *(u_long *)&rgb;
        *(u_long *)&p->u0 = uv | (efc->sprite.code & 0xFFFF0000) | Scratch_clut_bits;
    }
    // Overwrites the word just set (the target has both stores).
    *(u_long *)&p->u0 = (efc->sprite.code & 0xFFFF0000) | (uv & 0xFFFF);
    *(u_long *)&p->u1 = (efc->sprite.code << 16) | ((uv & 0xFFFF) + 0x1F);
    *(u_long *)&p->u2 = (uv & 0xFFFF) + 0x1F00;
    *(u_long *)&p->u3 = (uv & 0xFFFF) + 0x1F1F;
    gte_stsxy3c(sxy);
    gte_stsxy0(&p->x0);
    gte_stsxy1(&p->x1);
    *(u_long *)&p->x2 = ((sxy[2].vy * 2 - sxy[1].vy) << 16) | (u_short)(sxy[2].vx * 2 - sxy[1].vx);
    *(u_long *)&p->x3 = ((sxy[2].vy * 2 - sxy[0].vy) << 16) | (u_short)(sxy[2].vx * 2 - sxy[0].vx);
}

void func_8002A158(void)
{
}

// Draw functions 1 and 3 of D_800898D0: draws a model EFC as textured polygons (func_8002A6E8) of
// its colour, at the level of detail its depth picks, by its matrix times the view matrix (both
// scaled up by Scratch_scale_shift). It is skipped beyond the fog, too near or off the screen,
// unless flags has bit 6 and it is nearer than the fog. With flags bit 5, only mesh pos.pad is
// drawn, else the first; bit 3 draws it without the fog CLUT, bit 7 with another row of it.
void Efc_model_draw(EFC *efc, sint32 flags)
{
    VECTOR t;
    SVECTOR pos;
    MATRIX m;
    DVECTOR sxy;
    long z;
    sint32 shift;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransVector(&Scratch_trans);
    gte_ldv0(&efc->model.pos);
    gte_rtps();
    gte_stsxy(&sxy);
    gte_stszotz(&z);
    if (!(flags & 0x40) || z >= Scratch_fog_0)
    {
        if (z > Scratch_fog_0 || z < (0x30 >> Scratch_scale_shift))
        {
            return;
        }
        if ((u_short)(sxy.vx + 0x160) > 0x400 || (u_short)(sxy.vy + 0x88) > 0x400)
        {
            return;
        }
    }
    pos   = efc->model.pos;
    shift = Scratch_scale_shift;
    m     = efc->model.mtx;
    if (shift != 0)
    {
        pos.vx <<= shift;
        pos.vy <<= shift;
        pos.vz <<= shift;
        m.m[0][0] <<= shift;
        m.m[0][1] <<= shift;
        m.m[0][2] <<= shift;
        m.m[1][0] <<= shift;
        m.m[1][1] <<= shift;
        m.m[1][2] <<= shift;
        m.m[2][0] <<= shift;
        m.m[2][1] <<= shift;
        m.m[2][2] <<= shift;
    }
    if (z > 0x708)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[2][1];
    }
    else if (z > 0x2BC)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[1][1];
    }
    else
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[0][1];
    }
    if (flags & 8)
    {
        Scratch_clut_bits = 0;
    }
    else if (flags & 0x80)
    {
        Scratch_clut_bits = (((D_800C0DC0.b[(z / 128) & 0x1F] >> 2) << 6) + (D_800C0DC0.b[(z / 128) & 0x1F] & 3)) << 16;
    }
    else
    {
        Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    }
    gte_MulMatrix0(&Scratch_view_mtx, &m, &Scratch_mtx);
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_ldv0(&pos);
    gte_rtv0();
    gte_stlvnl(&t);
    Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + t.vx;
    Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + t.vy;
    Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + t.vz;
    gte_SetRotMatrix(&Scratch_mtx);
    gte_SetTransMatrix(&Scratch_mtx);
    if (flags & 0x20)
    {
        func_8002A6E8(Scratch_mesh_tbl + efc->model.pos.pad, efc->model.rgbc & 0x2FFFFFF, flags);
    }
    else
    {
        func_8002A6E8(Scratch_mesh_tbl, efc->model.rgbc & 0x2FFFFFF, flags);
    }
}

// Draws the faces of m as textured polygons (POLY_FT3, POLY_FT4) of colour rgb, depth-cued unless
// flags has bit 3, all of them with bit 6 (else only those facing the camera). Each face's
// vertices are copied to Scratch_vtx to be loaded into the GTE.
void func_8002A6E8(MESH *m, u_long rgb, uint32 flags)
{
    u_long code;
    long opz;
    u_long otz;
    SVECTOR *v;
    SVECTOR *vtx;
    MESH_FACE *f;
    POLY_FT3 *p3;
    POLY_FT4 *p4;
    u_long *ot;
    sint32 n;
    u_long tag;
    u_long mask;
    uint32 ct;

    tag  = 0x07000000;
    mask = 0xFFFFFF;
    v    = Scratch_vtx;
    n    = m->n_tri;
    f    = m->tri;
    code = rgb | 0x24000000; // POLY_FT3
    vtx  = m->vtx;
    ct   = m->clut_tpage;
    gte_ldrgb(&code);
    for (; n != 0; f++)
    {
        v[0] = vtx[f->idx.b[0]];
        v[1] = vtx[f->idx.b[1]];
        v[2] = vtx[f->idx.b[2]];
        gte_ldv3c(v);
        gte_rtpt();
        n--;
        if (!(flags & 0x40))
        {
            gte_nclip();
            gte_stopz(&opz);
            if (opz <= 0)
            {
                continue;
            }
        }
        gte_dpcs();
        p3           = (POLY_FT3 *)Map_prim_ptr;
        Map_prim_ptr = (POLY_FT4 *)(p3 + 1);
        gte_stsxy3_ft3(p3);
        gte_avsz3();
        gte_stotz(&otz);
        ot      = Scratch_ot + (otz >> 1);
        p3->tag = (u_long *)(tag | *ot);
        *ot     = (u_long)p3 & mask;
        if (!(flags & 8))
        {
            gte_strgb(&code);
        }
        *(u_long *)&p3->r0 = code;
        *(u_long *)&p3->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
        *(u_long *)&p3->u1 = (ct << 16) | f->uv.pair[1];
        *(u_long *)&p3->u2 = f->uv.pair[2];
    }
    tag  = 0x09000000;
    n    = m->n_quad;
    f    = m->quad;
    code = rgb | 0x2C000000; // POLY_FT4
    gte_ldrgb(&code);
    for (; n != 0; f++)
    {
        v[0] = vtx[f->idx.b[0]];
        v[1] = vtx[f->idx.b[1]];
        v[2] = vtx[f->idx.b[2]];
        v[3] = vtx[f->idx.b[3]];
        gte_ldv3c(v);
        gte_rtpt();
        n--;
        if (!(flags & 0x40))
        {
            gte_nclip();
            gte_stopz(&opz);
            if (opz <= 0)
            {
                continue;
            }
        }
        gte_dpcs();
        p4           = Map_prim_ptr;
        Map_prim_ptr = p4 + 1;
        gte_stsxy3_ft4(p4);
        gte_ldv0(&v[3]);
        gte_rtps();
        gte_stsxy(&p4->x3);
        gte_avsz4();
        gte_stotz(&otz);
        ot      = Scratch_ot + (otz >> 1);
        p4->tag = (u_long *)(tag | *ot);
        *ot     = (u_long)p4 & mask;
        if (!(flags & 8))
        {
            gte_strgb(&code);
        }
        *(u_long *)&p4->r0 = code;
        *(u_long *)&p4->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
        *(u_long *)&p4->u1 = (ct << 16) | f->uv.pair[1];
        *(u_long *)&p4->u2 = f->uv.pair[2];
        *(u_long *)&p4->u3 = f->uv.pair[3];
    }
}

void func_8002AB68(void)
{
}

// Draw function 4 of D_800898D0: draws a model EFC Gouraud-shaded (func_8002AEE4), at the level
// of detail its depth picks, by its matrix times the view matrix. The corner colours are a table
// whose address is the word right after the EFC (in the object holding it). With flags bit 5,
// only mesh pos.pad is drawn, else the first.
void Efc_model_g_draw(EFC *efc, sint32 flags)
{
    sint32 v[3];
    long z;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    gte_ldv0(&efc->model.pos);
    gte_rtps();
    gte_stszotz(&z);
    if (z > Scratch_fog_0 || z < 0x30)
    {
        return;
    }
    if (z > 0x708)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[2][1];
    }
    else if (z > 0x2BC)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[1][1];
    }
    else
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[0][1];
    }
    Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    gte_MulMatrix0(&Scratch_view_mtx, &efc->model.mtx, &Scratch_mtx);
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_ldv0(&efc->model.pos);
    gte_rtv0();
    gte_stlvnl(v);
    Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + v[0];
    Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + v[1];
    Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + v[2];
    gte_SetRotMatrix(&Scratch_mtx);
    gte_SetTransMatrix(&Scratch_mtx);
    if (flags & 0x20)
    {
        func_8002AEE4(Scratch_mesh_tbl + efc->model.pos.pad, *(u_long **)(efc + 1));
    }
    else
    {
        func_8002AEE4(Scratch_mesh_tbl, *(u_long **)(efc + 1));
    }
}

// Draws the faces of m that face the camera as Gouraud-shaded polygons (POLY_G3, POLY_G4), with
// the corner colours rgb gives, three per triangle, then four per quad. Each face's vertices are
// copied to Scratch_vtx to be loaded into the GTE.
void func_8002AEE4(MESH *m, u_long *rgb)
{
    u_long code;
    long opz;
    u_long otz;
    SVECTOR *v;
    SVECTOR *vtx;
    MESH_FACE *f;
    POLY_G3 *p3;
    POLY_G4 *p4;
    u_long *ot;
    sint32 n;
    u_long tag;
    u_long mask;

    tag  = 0x06000000;
    mask = 0xFFFFFF;
    v    = Scratch_vtx;
    n    = m->n_tri;
    f    = m->tri;
    code = 0x30000000; // POLY_G3
    vtx  = m->vtx;
    gte_ldrgb(&code);
    for (; n != 0; rgb += 3, f++)
    {
        v[0] = vtx[f->idx.b[0]];
        v[1] = vtx[f->idx.b[1]];
        v[2] = vtx[f->idx.b[2]];
        gte_ldv3c(v);
        gte_rtpt();
        gte_nclip();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            p3           = (POLY_G3 *)Map_prim_ptr;
            Map_prim_ptr = (POLY_FT4 *)(p3 + 1);
            gte_stsxy3_g3(p3);
            gte_avsz3();
            gte_stotz(&otz);
            ot                 = Scratch_ot + (otz >> 1);
            p3->tag            = (u_long *)(tag | *ot);
            *ot                = (u_long)p3 & mask;
            *(u_long *)&p3->r0 = code | rgb[0];
            *(u_long *)&p3->r1 = rgb[1];
            *(u_long *)&p3->r2 = rgb[2];
        }
    }
    tag  = 0x08000000;
    n    = m->n_quad;
    f    = m->quad;
    code = 0x38000000; // POLY_G4
    gte_ldrgb(&code);
    for (; n != 0; rgb += 4, f++)
    {
        v[0] = vtx[f->idx.b[0]];
        v[1] = vtx[f->idx.b[1]];
        v[2] = vtx[f->idx.b[2]];
        v[3] = vtx[f->idx.b[3]];
        gte_ldv3c(v);
        gte_rtpt();
        gte_nclip();
        n--;
        gte_stopz(&opz);
        if (opz > 0)
        {
            p4           = (POLY_G4 *)Map_prim_ptr;
            Map_prim_ptr = (POLY_FT4 *)(p4 + 1);
            gte_stsxy3_g4(p4);
            gte_ldv0(&v[3]);
            gte_rtps();
            gte_stsxy(&p4->x3);
            gte_avsz4();
            gte_stotz(&otz);
            ot                 = Scratch_ot + (otz >> 1);
            p4->tag            = (u_long *)(tag | *ot);
            *ot                = (u_long)p4 & mask;
            *(u_long *)&p4->r0 = code | rgb[0];
            *(u_long *)&p4->r1 = rgb[1];
            *(u_long *)&p4->r2 = rgb[2];
            *(u_long *)&p4->r3 = rgb[3];
        }
    }
}

// Draw function 5 of D_800898D0: the same as Efc_model_g_draw, but as Gouraud-shaded textured
// polygons (mesh_gt_vtx_rgb_draw): the vertex colours are the table whose address is the word
// right after the EFC, scaled by the EFC's rgbc.
void Efc_model_gt_vtx_draw(EFC *efc, sint32 flags)
{
    sint32 v[3];
    long z;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    gte_ldv0(&efc->model.pos);
    gte_rtps();
    gte_stszotz(&z);
    if (z > Scratch_fog_0 || z < 0x30)
    {
        return;
    }
    if (z > 0x708)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[2][1];
    }
    else if (z > 0x2BC)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[1][1];
    }
    else
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[0][1];
    }
    Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    gte_MulMatrix0(&Scratch_view_mtx, &efc->model.mtx, &Scratch_mtx);
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_ldv0(&efc->model.pos);
    gte_rtv0();
    gte_stlvnl(v);
    Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + v[0];
    Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + v[1];
    Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + v[2];
    gte_SetRotMatrix(&Scratch_mtx);
    gte_SetTransMatrix(&Scratch_mtx);
    if (flags & 0x20)
    {
        mesh_gt_vtx_rgb_draw(Scratch_mesh_tbl + efc->model.pos.pad, *(u_long **)(efc + 1), efc->model.rgbc);
    }
    else
    {
        mesh_gt_vtx_rgb_draw(Scratch_mesh_tbl, *(u_long **)(efc + 1), efc->model.rgbc);
    }
}

// Draws all the faces of m as Gouraud-shaded textured polygons (POLY_GT3, POLY_GT4), each corner
// coloured by its vertex's colour in rgb_tbl scaled by rgb (RGB_SCALE); the top byte of rgb is
// ORed into the code (semi-transparency), and the texture page's blending bits are cleared. The
// winding is computed but not tested. rgb is reused for the corner colours, so the quads' code
// takes the top byte of the last one (0), not of rgb, unless m has no triangles.
void mesh_gt_vtx_rgb_draw(MESH *m, u_long *rgb_tbl, u_long rgb)
{
    u_long code;
    long opz;
    u_long otz;
    SVECTOR *v;
    SVECTOR *vtx;
    MESH_FACE *f;
    POLY_GT3 *p3;
    POLY_GT4 *p4;
    u_long *ot;
    sint32 n;
    u_long tag;
    u_long mask;
    uint32 ct;
    uint32 r;
    uint32 g;
    uint32 b;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;

    n    = m->n_tri;
    f    = m->tri;
    vtx  = m->vtx;
    ct   = m->clut_tpage & ~0x60; // no blending mode
    tag  = 0x09000000;
    mask = 0xFFFFFF;
    v    = Scratch_vtx;
    code = (rgb & 0xFF000000) | 0x34000000; // POLY_GT3
    r    = rgb & 0xFF;
    g    = (rgb & 0xFF00) >> 8;
    b    = (rgb >> 16) & 0xFF;
    gte_ldrgb(&code);
    for (; n != 0; f++)
    {
        i0   = f->idx.b[0];
        i1   = f->idx.b[1];
        i2   = f->idx.b[2];
        v[0] = vtx[i0];
        v[1] = vtx[i1];
        v[2] = vtx[i2];
        gte_ldv3c(v);
        gte_rtpt();
        gte_nclip();
        n--;
        gte_stopz(&opz);
        p3           = (POLY_GT3 *)Map_prim_ptr;
        Map_prim_ptr = (POLY_FT4 *)(p3 + 1);
        gte_stsxy3_gt3(p3);
        gte_avsz3();
        gte_stotz(&otz);
        ot                 = Scratch_ot + (otz >> 1);
        p3->tag            = (u_long *)(tag | *ot);
        *ot                = (u_long)p3 & mask;
        rgb                = rgb_tbl[i0];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p3->r0 = code | rgb;
        rgb                = rgb_tbl[i1];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p3->r1 = rgb;
        rgb                = rgb_tbl[i2];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p3->r2 = rgb;
        *(u_long *)&p3->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
        *(u_long *)&p3->u1 = (ct << 16) | f->uv.pair[1];
        *(u_long *)&p3->u2 = f->uv.pair[2];
    }
    tag  = 0x0C000000;
    n    = m->n_quad;
    f    = m->quad;
    code = (rgb & 0xFF000000) | 0x3C000000; // POLY_GT4
    gte_ldrgb(&code);
    for (; n != 0; f++)
    {
        i0   = f->idx.b[0];
        i1   = f->idx.b[1];
        i2   = f->idx.b[2];
        i3   = f->idx.b[3];
        v[0] = vtx[i0];
        v[1] = vtx[i1];
        v[2] = vtx[i2];
        v[3] = vtx[i3];
        gte_ldv3c(v);
        gte_rtpt();
        gte_nclip();
        n--;
        gte_stopz(&opz);
        p4           = (POLY_GT4 *)Map_prim_ptr;
        Map_prim_ptr = (POLY_FT4 *)(p4 + 1);
        gte_stsxy3_gt4(p4);
        gte_ldv0(&v[3]);
        gte_rtps();
        gte_stsxy(&p4->x3);
        gte_avsz4();
        gte_stotz(&otz);
        ot                 = Scratch_ot + (otz >> 1);
        p4->tag            = (u_long *)(tag | *ot);
        *ot                = (u_long)p4 & mask;
        rgb                = rgb_tbl[i0];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r0 = code | rgb;
        rgb                = rgb_tbl[i1];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r1 = rgb;
        rgb                = rgb_tbl[i2];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r2 = rgb;
        rgb                = rgb_tbl[i3];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r3 = rgb;
        *(u_long *)&p4->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
        *(u_long *)&p4->u1 = (ct << 16) | f->uv.pair[1];
        *(u_long *)&p4->u2 = f->uv.pair[2];
        *(u_long *)&p4->u3 = f->uv.pair[3];
    }
}

// Draw function 6 of D_800898D0: the same as Efc_model_gt_vtx_draw, but semi-transparent, with a colour per
// face corner (mesh_gt_face_rgb_draw).
void Efc_model_gt_face_draw(EFC *efc, sint32 flags)
{
    sint32 v[3];
    long z;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    gte_ldv0(&efc->model.pos);
    gte_rtps();
    gte_stszotz(&z);
    if (z > Scratch_fog_0 || z < 0x30)
    {
        return;
    }
    if (z > 0x708)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[2][1];
    }
    else if (z > 0x2BC)
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[1][1];
    }
    else
    {
        Scratch_mesh_tbl = &((PARTS_MODEL *)efc->model.data)->lod[0][1];
    }
    Scratch_clut_bits = D_800C0DC0.b[(z / 128) & 0x1F] << 16;
    gte_MulMatrix0(&Scratch_view_mtx, &efc->model.mtx, &Scratch_mtx);
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_ldv0(&efc->model.pos);
    gte_rtv0();
    gte_stlvnl(v);
    Scratch_mtx.t[0] = Scratch_view_mtx.t[0] + v[0];
    Scratch_mtx.t[1] = Scratch_view_mtx.t[1] + v[1];
    Scratch_mtx.t[2] = Scratch_view_mtx.t[2] + v[2];
    gte_SetRotMatrix(&Scratch_mtx);
    gte_SetTransMatrix(&Scratch_mtx);
    if (flags & 0x20)
    {
        mesh_gt_face_rgb_draw(Scratch_mesh_tbl + efc->model.pos.pad, *(u_long **)(efc + 1), efc->model.rgbc);
    }
    else
    {
        mesh_gt_face_rgb_draw(Scratch_mesh_tbl, *(u_long **)(efc + 1), efc->model.rgbc);
    }
}

// Draws all the faces of m as semi-transparent Gouraud-shaded textured polygons (POLY_GT3,
// POLY_GT4), their corner colours from rgb_tbl (three per triangle, then four per quad) scaled by
// rgb (RGB_SCALE). The winding is computed but not tested. Each face's vertices are copied to
// Scratch_vtx to be loaded into the GTE.
void mesh_gt_face_rgb_draw(MESH *m, u_long *rgb_tbl, u_long rgb)
{
    u_long code;
    long opz;
    u_long otz;
    SVECTOR *v;
    SVECTOR *vtx;
    MESH_FACE *f;
    POLY_GT3 *p3;
    POLY_GT4 *p4;
    u_long *ot;
    sint32 n;
    u_long tag;
    u_long mask;
    uint32 ct;
    uint32 r;
    uint32 g;
    uint32 b;
    uint32 i0;
    uint32 i1;
    uint32 i2;
    uint32 i3;

    tag  = 0x09000000;
    mask = 0xFFFFFF;
    v    = Scratch_vtx;
    n    = m->n_tri;
    f    = m->tri;
    code = 0x36000000; // POLY_GT3, semi-transparent
    r    = rgb & 0xFF;
    g    = (rgb & 0xFF00) >> 8;
    b    = (rgb >> 16) & 0xFF;
    vtx  = m->vtx;
    ct   = m->clut_tpage;
    gte_ldrgb(&code);
    for (; n != 0; rgb_tbl += 3, f++)
    {
        i0   = f->idx.b[0];
        i1   = f->idx.b[1];
        i2   = f->idx.b[2];
        v[0] = vtx[i0];
        v[1] = vtx[i1];
        v[2] = vtx[i2];
        gte_ldv3c(v);
        gte_rtpt();
        gte_nclip();
        n--;
        gte_stopz(&opz);
        p3           = (POLY_GT3 *)Map_prim_ptr;
        Map_prim_ptr = (POLY_FT4 *)(p3 + 1);
        gte_stsxy3_gt3(p3);
        gte_avsz3();
        gte_stotz(&otz);
        ot                 = Scratch_ot + (otz >> 1);
        p3->tag            = (u_long *)(tag | *ot);
        *ot                = (u_long)p3 & mask;
        rgb                = rgb_tbl[0];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p3->r0 = code | rgb;
        rgb                = rgb_tbl[1];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p3->r1 = rgb;
        rgb                = rgb_tbl[2];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p3->r2 = rgb;
        *(u_long *)&p3->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
        *(u_long *)&p3->u1 = (ct << 16) | f->uv.pair[1] | (getTPage(0, 1, 0, 0) << 16);
        *(u_long *)&p3->u2 = f->uv.pair[2];
    }
    tag  = 0x0C000000;
    n    = m->n_quad;
    f    = m->quad;
    code = 0x3E000000; // POLY_GT4, semi-transparent
    gte_ldrgb(&code);
    for (; n != 0; rgb_tbl += 4, f++)
    {
        i0   = f->idx.b[0];
        i1   = f->idx.b[1];
        i2   = f->idx.b[2];
        i3   = f->idx.b[3];
        v[0] = vtx[i0];
        v[1] = vtx[i1];
        v[2] = vtx[i2];
        v[3] = vtx[i3];
        gte_ldv3c(v);
        gte_rtpt();
        gte_nclip();
        n--;
        gte_stopz(&opz);
        p4           = (POLY_GT4 *)Map_prim_ptr;
        Map_prim_ptr = (POLY_FT4 *)(p4 + 1);
        gte_stsxy3_gt4(p4);
        gte_ldv0(&v[3]);
        gte_rtps();
        gte_stsxy(&p4->x3);
        gte_avsz4();
        gte_stotz(&otz);
        ot                 = Scratch_ot + (otz >> 1);
        p4->tag            = (u_long *)(tag | *ot);
        *ot                = (u_long)p4 & mask;
        rgb                = rgb_tbl[0];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r0 = code | rgb;
        rgb                = rgb_tbl[1];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r1 = rgb;
        rgb                = rgb_tbl[2];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r2 = rgb;
        rgb                = rgb_tbl[3];
        rgb                = RGB_SCALE(rgb, r, g, b);
        *(u_long *)&p4->r3 = rgb;
        *(u_long *)&p4->u0 = (ct & 0xFFFF0000) | f->uv.pair[0] | Scratch_clut_bits;
        *(u_long *)&p4->u1 = (ct << 16) | f->uv.pair[1] | (getTPage(0, 1, 0, 0) << 16);
        *(u_long *)&p4->u2 = f->uv.pair[2];
        *(u_long *)&p4->u3 = f->uv.pair[3];
    }
}

// Queues the player pl's shadow: under pl (at pos.vy while field_76 is set, otherwise on the
// ground below it), turned by ang.vy - unk116, with radius r, texture tex and the given spread.
void Pl_Shadow_Trans(PL_WORK *pl, sint32 r, sint32 spread, sint32 tex)
{
    sint32 y;
    uint32 n;

    n = Shadow_num;
    if (n < SHADOW_MAX)
    {
        Shadow_tbl[n].pos.vx = pl->pos.vx;
        if (pl->field_76 != 0)
        {
            y                    = pl->pos.vy;
            Shadow_tbl[n].pos.vy = y;
        }
        else
        {
            y                    = Obj_ceiling_height_get((MODEL_WORK *)pl);
            Shadow_tbl[n].pos.vy = y;
        }
        Shadow_tbl[n].pos.vz  = pl->pos.vz;
        Shadow_tbl[n].pos.pad = ((pl->ang.vy - pl->unk116) & 0xFFF) | ((spread >> 6) << 12);
        Shadow_tbl[n].r       = r | (tex << 14);
        Shadow_num++;
        Shadow_tbl[n].dist = y - pl->pos.vy;
    }
}

// Queues obj's shadow, the same way, turned by ang.vy; the ground is never above obj.
void Model_Shadow_Trans(MODEL_WORK *obj, sint32 r, sint32 spread, sint32 tex)
{
    sint32 y;
    uint32 n;

    n = Shadow_num;
    if (n < SHADOW_MAX)
    {
        Shadow_tbl[n].pos.vx = obj->pos.vx;
        if (obj->field_76 != 0)
        {
            y                    = obj->pos.vy;
            Shadow_tbl[n].pos.vy = y;
        }
        else
        {
            y = Obj_ceiling_height_get(obj);
            if (y < obj->pos.vy)
            {
                y = obj->pos.vy;
            }
            Shadow_tbl[n].pos.vy = y;
        }
        Shadow_tbl[n].pos.vz  = obj->pos.vz;
        Shadow_tbl[n].pos.pad = (obj->ang.vy & 0xFFF) | ((spread >> 6) << 12);
        Shadow_tbl[n].r       = r | (tex << 14);
        Shadow_num++;
        Shadow_tbl[n].dist = y - obj->pos.vy;
    }
}

// Queues a shadow on the ground below pos, turned by ang, with radius r and the texture in
// pos->pad.
void Pos_Shadow_Trans(SVECTOR *pos, sint32 r, sint32 spread, sint32 ang)
{
    sint16 y;
    uint32 n;

    n = Shadow_num;
    if (n < SHADOW_MAX)
    {
        Shadow_tbl[n].pos.vx  = pos->vx;
        y                     = func_80048EA4(pos, NULL, 0, 0xFFFF);
        Shadow_tbl[n].pos.vy  = y;
        Shadow_tbl[n].pos.vz  = pos->vz;
        Shadow_tbl[n].pos.pad = (ang & 0xFFF) | ((spread >> 6) << 12);
        Shadow_tbl[n].r       = r | (pos->pad << 14);
        Shadow_num++;
        Shadow_tbl[n].dist = y - pos->vy;
    }
}

// Draws the queued shadows and empties the queue.
void shadow_draw_all(void)
{
    sint32 i;
    sint32 n;
    uint32 w;
    sint32 da;
    sint32 ang;

    n = Shadow_num;
    for (i = 0; i < n; i++)
    {
        w                     = Shadow_tbl[i].pos.pad;
        da                    = (w & 0xF000) >> 6;
        ang                   = w & 0xFFF;
        w                     = Shadow_tbl[i].r;
        Shadow_tbl[i].pos.pad = w >> 14;
        shadow_draw(&Shadow_tbl[i].pos, w & 0x3FFF, da, ang, Shadow_tbl[i].dist);
    }
    Shadow_num = 0;
}

// Draws a shadow on the ground at pos: a textured quad whose corners lie r away at angles
// ang -/+ da (and opposite), shaded darker as dist grows and not drawn past 0x240. pos->pad picks
// one of two textures (shadow_draw_all sets it).
void shadow_draw(SVECTOR *pos, sint32 r, uint32 da, uint32 ang, sint32 dist)
{
    SVECTOR v[4];
    long z;
    POLY_FT4 *p;
    sint32 x;
    sint32 y;
    sint32 w;
    sint32 c;
    u_long *ot;

    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransVector(&Scratch_trans);
    gte_ldv0(pos);
    gte_rtps();
    gte_stszotz(&z);
    if (z > Scratch_fog_0 || z < 0x30)
    {
        return;
    }
    p = Map_prim_ptr++;
    if (dist > 0x240)
    {
        return;
    }
    if (dist < 0x40)
    {
        *(u_long *)&p->r0 = 0x2E808080;
    }
    else
    {
        c                 = (0x240 - dist) >> 2;
        *(u_long *)&p->r0 = 0x2E000000 | (c << 16) | (c << 8) | c;
    }
    x       = pos->vx << Scratch_scale_shift;
    y       = pos->vy << Scratch_scale_shift;
    w       = pos->vz << Scratch_scale_shift;
    v[0].vx = ((rsin(ang - da) * r) >> (12 - Scratch_scale_shift)) + x;
    v[0].vy = y;
    v[0].vz = ((rcos(ang - da) * r) >> (12 - Scratch_scale_shift)) + w;
    v[1].vx = ((rsin(ang + da) * r) >> (12 - Scratch_scale_shift)) + x;
    v[1].vy = y;
    v[1].vz = ((rcos(ang + da) * r) >> (12 - Scratch_scale_shift)) + w;
    v[2].vx = x * 2 - v[1].vx;
    v[2].vy = y * 2 - v[1].vy;
    v[2].vz = w * 2 - v[1].vz;
    v[3].vx = x * 2 - v[0].vx;
    v[3].vy = y * 2 - v[0].vy;
    v[3].vz = w * 2 - v[0].vz;
    gte_SetTransMatrix(&Scratch_view_mtx);
    gte_ldv3c(v);
    gte_rtpt();
    p->clut  = getClut(832, 251);
    p->tpage = getTPage(0, 2, 320, 0);
    if (pos->pad != 0)
    {
        setUV4(p, 0xC0, 0xE0, 0xDF, 0xE0, 0xC0, 0xFF, 0xDF, 0xFF);
    }
    else
    {
        setUV4(p, 0xE0, 0xE0, 0xFF, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF);
    }
    gte_stsxy3_ft4(p);
    gte_ldv0(&v[3]);
    gte_rtps();
    gte_stsxy(&p->x3);
    gte_avsz4();
    gte_stotz(&z);
    ot     = Scratch_ot + (z >> 1);
    p->tag = (u_long *)(*ot | 0x09000000);
    *ot    = (u_long)p & 0xFFFFFF;
}

void func_8002CFA4(void)
{
    Mem_clear(D_8015BC00, D_8015BC00 + 0x3FC);
    Shadow_num    = 0;
    D_1F800075    = 0;
    D_1F800004    = 0;
    Scratch_fog_0 = 0xE00;
    D_800988FC    = 0;
    Scratch_fog_1 = 0xE00;
}

// Sets the textures of the two meshes at D_800F7820 and D_800F7830 to cells a and b of a grid of
// 42 x 51 cells, 6 to a row.
void func_8002D004(PL_WORK *pl, uint32 a, uint32 b)
{
    uint32 row;
    uint32 col;

    row = a / 6;
    col = a % 6;
    row *= 51;
    col *= 42;
    prim_mesh_uv_copy(D_800F7820, row << 8 | col);
    row = b / 6;
    col = b % 6;
    row *= 51;
    col *= 42;
    prim_mesh_uv_copy(D_800F7830, row << 8 | col);
}

// Sets the texture coordinates of every face of m (both display buffers' primitives) to the
// original ones, kept in the copy of the face tables that follows them, plus delta (a uv offset
// word, as Model_uv_cell gives). The primitives are walked as words: 3, 5, 7 (and 9 for a quad)
// are the uv words, 17 and 21 the faces' sizes, 8 and 10 the primitives'.
void prim_mesh_uv_copy(PRIM_MESH *m, sint32 delta)
{
    uint32 i;
    uint32 j;
    uint32 n_tri;
    uint32 n_quad;
    sint32 k;
    uint32 *tri;
    uint32 *tri_src;
    uint32 *quad;
    uint32 *quad_src;

    i       = 0;
    j       = *(uint32 *)&m->n_tri; // n_tri and n_quad read in one word
    tri     = (uint32 *)m->tri;
    n_tri   = j & 0xFF;
    n_quad  = (j >> 8) & 0xFF;
    tri_src = (uint32 *)((uint8 *)tri + n_tri * sizeof(PRIM_TRI) + n_quad * sizeof(PRIM_QUAD));
    for (; i < n_tri; i++)
    {
        for (j = 0; j < 2; j++)
        {
            k          = i * 17 + j * 8;
            tri[k + 3] = tri_src[k + 3] + delta;
            tri[k + 5] = tri_src[k + 5] + delta;
            tri[k + 7] = tri_src[k + 7] + delta;
        }
    }
    quad     = (uint32 *)m->quad;
    quad_src = (uint32 *)((uint8 *)quad + n_tri * sizeof(PRIM_TRI) + n_quad * sizeof(PRIM_QUAD));
    for (i = 0; i < n_quad; i++)
    {
        for (j = 0; j < 2; j++)
        {
            k           = i * 21 + j * 10;
            quad[k + 3] = quad_src[k + 3] + delta;
            quad[k + 5] = quad_src[k + 5] + delta;
            quad[k + 7] = quad_src[k + 7] + delta;
            quad[k + 9] = quad_src[k + 9] + delta;
        }
    }
}

// id: level of detail (bits 24-31), face list (16-23: 0 tri, 1 quad), mesh (8-15; entry 0 of a
// level is skipped) and face (0-7). The two lists are indexed as an array of MESH_FACE pointers.
MESH_FACE *Model_face_get(PARTS_MODEL *model, uint32 id)
{
    return (&model->lod[id >> 24][((id >> 8) & 0xFF) + 1].tri)[(id >> 16) & 0xFF] + (id & 0xFF);
}

void Model_face_uv_set(PARTS_MODEL *model, uint32 id, MESH_UV *uv)
{
    MESH_FACE *face;

    face             = (&model->lod[id >> 24][((id >> 8) & 0xFF) + 1].tri)[(id >> 16) & 0xFF] + (id & 0xFF);
    face->uv.word[0] = uv->word[0];
    face->uv.word[1] = uv->word[1];
}

// id: level of detail (bits 24-31), mesh (8-15) and vertex (0-7).
SVECTOR *Model_vertex_get(PARTS_MODEL *model, uint32 id)
{
    return model->lod[id >> 24][((id >> 8) & 0xFF) + 1].vtx + (id & 0xFF);
}

void func_8002D318(void)
{
}

// Sets the texture coordinates of mesh (parts & 0xFFFF) of the near level of detail to those of
// mesh (parts >> 16) plus delta (a uv offset word, Model_uv_cell): swaps a face texture. The faces
// are walked as words, three per face, the first two being the uv words.
void Model_mesh_uv_copy(PARTS_MODEL *model, uint32 parts, sint32 delta)
{
    MESH *dst;
    MESH *src;
    uint32 n_tri;
    uint32 n_quad;
    uint32 i;
    uint32 dst_no;
    uint32 src_no;
    uint32 *dst_tri;
    uint32 *src_tri;
    uint32 *dst_quad;
    uint32 *src_quad;

    // Mesh n is entry n + 1 of the level. The entries are addressed with integer arithmetic: the
    // pointer forms (&lod[0][n], lod[0] + n, byte pointers) allocate the registers differently.
    dst_no   = parts & 0xFFFF;
    src_no   = parts >> 16;
    dst      = (MESH *)(dst_no * sizeof(MESH) + (uint32)model->lod[0]);
    dst_tri  = dst[1].tri->uv.word;
    i        = *(uint32 *)&dst[1].n_tri; // n_tri and n_quad read in one word
    n_tri    = (i & 0xFF) * 3;
    n_quad   = ((i >> 8) & 0xFF) * 3;
    src      = (MESH *)(src_no * sizeof(MESH) + (uint32)model->lod[0]);
    src_tri  = src[1].tri->uv.word;
    dst_quad = dst[1].quad->uv.word;
    src_quad = src[1].quad->uv.word;
    for (i = 0; i < n_tri; i += 3)
    {
        dst_tri[i]     = src_tri[i] + delta;
        dst_tri[i + 1] = src_tri[i + 1] + delta;
    }
    for (i = 0; i < n_quad; i += 3)
    {
        dst_quad[i]     = src_quad[i] + delta;
        dst_quad[i + 1] = src_quad[i + 1] + delta;
    }
}

// Texture offset of cell `cell` in a grid of cells w by h, cols to a row, as a uv word of two
// corners (u, v, u, v), for Model_mesh_uv_copy.
uint32 Model_uv_cell(uint32 cell, uint32 w, uint32 h, uint32 cols)
{
    uint32 row;
    uint32 u;

    row = cell / cols;
    u   = (cell - row * cols) * w;
    return (row * h) << 24 | u << 16 | (row * h) << 8 | u;
}

uint32 *Billboard_get(void)
{
    POLY_FT4 *p;

    if (D_800988FC >= BILLBOARD_MAX)
    {
        return NULL;
    }
    p                        = Map_prim_ptr;
    D_800BE6D8[D_800988FC++] = (BILLBOARD *)p;
    Map_prim_ptr             = p + 1;
    return (uint32 *)p;
}

uint32 *Billboard_line_get(void)
{
    uint32 *p;

    if (D_800988FC >= BILLBOARD_MAX)
    {
        return NULL;
    }
    p                        = (uint32 *)Map_prim_ptr;
    D_800BE6D8[D_800988FC++] = (BILLBOARD *)p;
    Map_prim_ptr             = (POLY_FT4 *)(p + 8); // 0x20 bytes
    return p;
}

// Projects the queued billboards and lines and links them into the frame's ordering table, as
// billboard_draw does the billboards (with an identity matrix built in the scratchpad), and
// empties the queue. A billboard is skipped when its centre is off the screen. A line is walked
// as words (code_80027678.h); with a struct, GCC reorders the copies of its ends. The nops of the
// loop's first GTE commands are statements of their own: with the one-statement macros GCC hoists
// the 0x09000000 tag constant out of the loop, which the target doesn't.
void billboard_queue_draw(void)
{
    VECTOR pos;
    SVECTOR v[3];
    DVECTOR sxy0;
    DVECTOR sxy1;
    CVECTOR rgb;
    BILLBOARD *p;
    uint32 *l;
    MATRIX *id;
    u_long *ot;
    sint32 r;
    uint32 n;
    uint32 i;

    id                      = &Scratch_id_mtx;
    *(uint32 *)&id->m[0][0] = 0x1000; // m[0][0] = 1.0, m[0][1] = 0
    *(uint32 *)&id->m[0][2] = 0;
    *(uint32 *)&id->m[1][1] = 0x1000;
    *(uint32 *)&id->m[2][0] = 0;
    *(uint32 *)&id->m[2][2] = 0x1000;
    id->t[0]                = 0;
    id->t[1]                = 0;
    id->t[2]                = 0;
    n                       = D_800988FC;
    D_800988FC              = 0;
    gte_SetRotMatrix(&Scratch_view_mtx);
    gte_SetTransMatrix(&Scratch_view_mtx);
    for (i = 0; i < n; i++)
    {
        p = D_800BE6D8[i];
        if ((getcode(p) >> 5) == 1) // polygon
        {
            *(sint32 *)&v[0].vx = p->xy0;
            *(sint32 *)&v[0].vz = p->xy1;
            gte_ldv0(&v[0]);
            gte_nop();
            gte_nop();
            gte_rt_b();
            gte_stlvnl(&pos);
            if (pos.vz > Scratch_fog_0 * 4 || pos.vz < 0xC0)
            {
                continue;
            }
            gte_nop();
            gte_nop();
            gte_rtps_b();
            gte_stsxy(&sxy0);
            if ((u_short)(sxy0.vx + 0x160) > 0x400 || (u_short)(sxy0.vy + 0x88) > 0x400)
            {
                continue;
            }
            gte_SetRotMatrix(id);
            gte_SetTransMatrix(id);
            r       = p->xy2;
            v[0].vx = pos.vx - r;
            v[0].vy = pos.vy - r;
            v[1].vx = pos.vx + r;
            v[1].vy = pos.vy + r;
            v[2].vx = pos.vx;
            v[2].vy = pos.vy;
            v[0].vz = v[1].vz = v[2].vz = pos.vz;
            gte_ldv3c(v);
            gte_rtpt();
            ot = &Scratch_ot[pos.vz >> 3];
            if (p->xy3 & BILLBOARD_NO_FOG)
            {
                p->tag = *ot | 0x09000000;
                *ot    = (u_long)p & 0xFFFFFF;
            }
            else
            {
                Scratch_clut_bits = D_800C0DC0.b[(pos.vz / 512) & 0x1F] << 16;
                gte_ldrgb(&p->rgbc);
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
            gte_SetRotMatrix(&Scratch_view_mtx);
            gte_SetTransMatrix(&Scratch_view_mtx);
        }
        else
        {
            l                   = (uint32 *)p;
            *(sint32 *)&v[0].vx = l[2];
            *(sint32 *)&v[0].vz = l[4];
            *(sint32 *)&v[1].vx = l[0];
            v[1].vz             = v[0].pad;
            gte_ldv3c(v);
            gte_rtpt();
            l[5] = ((u_long)l & 0xFFFFFF) | 0x02000000;
            l[7] = 0;
            gte_stsz3c(&pos);
            if (pos.vx > Scratch_fog_0 * 4 || pos.vx < 0xC0)
            {
                continue;
            }
            ot   = &Scratch_ot[(pos.vx + pos.vy) >> 4];
            l[0] = *ot | 0x04000000;
            *ot  = (u_long)&l[5] & 0xFFFFFF;
            gte_stsxy0(&l[2]);
            gte_stsxy1(&l[4]);
        }
    }
}
