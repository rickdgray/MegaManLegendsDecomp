#include "common.h"
#include "code_80027678.h"
#include "fastmem.h"
#include "scratch.h"
#include "stage.h"

// Small uninitialized statics (.sbss 0x80098550-0x8009855C).
static sint32 D_80098550;
static sint32 D_80098554[2];

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80027678);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002786C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80027BE0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80027D94);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80027F78);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002831C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_800289A0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80028DE0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80028F90);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80029608);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80029A38);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_80029C18);

void func_8002A158(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002A160);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002A6E8);

void func_8002AB68(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002AB70);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002AEE4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002B2C8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002B644);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002BD48);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002C0C4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002C794);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", Model_Shadow_Trans);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002CA10);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002CB18);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002CBDC);

void func_8002CFA4(void)
{
    Mem_clear(D_8015BC00, D_8015BC00 + 0x3FC);
    D_800987D8    = 0;
    D_1F800075    = 0;
    D_1F800004    = 0;
    Scratch_fog_0 = 0xE00;
    D_800988FC    = 0;
    Scratch_fog_1 = 0xE00;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002D004);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002D0D0);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80027678", func_8002D50C);
