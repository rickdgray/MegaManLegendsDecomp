#include "common.h"
#include "code_8001F828.h"
#include "game.h"
#include "psyq/inline_c.h"
#include "scene.h"
#include "scratch.h"
#include "stage.h"

// Small data (.sdata 0x80097C3C-0x80097C44): reached through $gp in this file.
sint32 D_80097C3C = 0;
sint8 D_80097C40  = 0;
uint8 D_80097C41  = 0;
sint16 D_80097C42 = 0;

// Small uninitialized statics (.sbss 0x800981BC-0x80098354).
static sint16 D_800981BC[2];
static sint16 D_800981C0[4];
static sint32 D_800981C8[2];
static sint16 D_800981D0[4];
static sint32 D_800981D8[2];
static sint16 D_800981E0[4];
static sint32 D_800981E8;
static sint16 D_800981EC[4];
static sint32 D_800981F4[2];
static sint32 D_800981FC[2];
static sint32 D_80098204;
static sint16 D_80098208[2];
static sint16 D_8009820C[2];
static sint16 D_80098210[4];
static sint32 D_80098218[2];
static sint32 D_80098220[2];
static sint32 D_80098228[2];
static sint32 D_80098230;
static sint16 D_80098234[2];
static sint16 D_80098238[4];
static sint16 D_80098240[4];
static sint32 D_80098248;
static sint16 D_8009824C[4];
static sint32 D_80098254;
static sint16 D_80098258[4];
static sint32 D_80098260[2];
static sint32 D_80098268[2];
static sint16 D_80098270[4];
static sint32 D_80098278;
static sint16 D_8009827C[4];
static sint32 D_80098284[2];
static sint16 D_8009828C[2];
static sint32 D_80098290[2];
static sint32 D_80098298;
static sint32 D_8009829C[2];
static sint32 D_800982A4[2];
static sint32 D_800982AC[2];
static sint32 D_800982B4[2];
static sint32 D_800982BC[2];
static sint32 D_800982C4;
static sint32 D_800982C8[2];
static sint32 D_800982D0[2];
static sint32 D_800982D8[2];
static sint32 D_800982E0;
static sint32 D_800982E4[2];
static sint32 D_800982EC[2];
static sint32 D_800982F4;
static sint16 D_800982F8[2];
static sint16 D_800982FC[4];
static sint32 D_80098304[2];
static sint32 D_8009830C[2];
static sint32 D_80098314[2];
static sint32 D_8009831C[2];
static sint32 D_80098324[2];
static sint32 D_8009832C[2];
static sint32 D_80098334[2];
static sint32 D_8009833C;
static uint8 D_80098340[4];
static sint8 D_80098344[4];
static uint8 D_80098348[4];
static uint8 D_8009834C[8];

// Called only from this file
void map_blocks_draw(uint32 *rows, sint32 kind);
void map_blocks_draw2(uint32 *rows, sint32 kind);

void func_8001F828(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            if (Sce_flag_test(0xC))
            {
                D_800981BC[0] = 0x32;
            }
            else
            {
                D_800981BC[0] = 0x31;
            }
            return;
        case 1:
            D_800981BC[0] = 0x32;
            id            = 0x36;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            D_800981BC[0] = 0x32;
            id            = 0x34;
            break;
        default:
            D_800981BC[0] = 0x32;
            id            = 0x35;
            break;
    }
    D_800981BC[1] = D_800981C0[0] = D_800981C0[1] = id;
}

void func_8001F8DC(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            if (Sce_flag_test(6) && !Sce_flag_test(0x59))
            {
                D_800981D0[0] = 0x3D;
            }
            else
            {
                D_800981D0[0] = 0x3C;
            }
            return;
        case 1:
            D_800981D0[0] = 0x3C;
            id            = 0x3F;
            break;
        case 2:
        case 3:
            D_800981D0[0] = 0x3C;
            id            = 0x40;
            break;
        case 4:
        case 5:
            D_800981D0[0] = 0x3C;
            id            = 0x41;
            break;
        case 11:
            D_800981D0[0] = 0x3C;
            id            = 0x43;
            break;
        default:
            D_800981D0[0] = 0x3C;
            id            = 0x42;
            break;
    }
    D_800981D0[1] = id;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8001F9AC);

void func_8001FA94(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            D_800981EC[1] = 0x59;
            if (Sce_flag_test(0x630))
            {
                D_800981EC[3] = 0x61;
            }
            else
            {
                D_800981EC[3] = 0x5F;
            }
            return;
        case 1:
            id = 0x5A;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x5B;
            break;
        default:
            id = 0x5C;
            break;
    }
    D_800981EC[1] = id;
}

void func_8001FB24(void)
{
    if (Game_work.sce_no == 6)
    {
        D_80098208[0] = D_80098208[1] = D_8009820C[0] = D_8009820C[1] = 0x67;
    }
    else
    {
        D_80098208[0] = D_80098208[1] = D_8009820C[0] = D_8009820C[1] = 0x66;
    }
}

void func_8001FB54(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x69;
            break;
        case 6:
        case 7:
            id = 0x6A;
            break;
        default:
            id = 0x6B;
            break;
    }
    D_80098210[1] = id;
}

void func_8001FB8C(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
            id = 0x76;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x77;
            break;
        default:
            id = 0x78;
            break;
    }
    D_80098234[1] = id;
}

void func_8001FBC4(void)
{
    sint16 id;

    if (Game_work.sce_no == 5)
    {
        if (Sce_flag_test(0x1C))
        {
            D_80098238[1] = 0x7A;
            D_80098238[3] = 0x7C;
            D_80098240[0] = -1;
            return;
        }
        if (Sce_flag_test(0x1B))
        {
            D_80098238[1] = D_80098238[3] = D_80098240[0] = -1;
            return;
        }
        id = 0x7A;
    }
    else
    {
        id = 0x7B;
    }
    D_80098238[3] = D_80098240[0] = id;
}

void func_8001FC50(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 1:
        case 2:
        case 3:
            if (!Sce_flag_test(0x30))
            {
                id = 0x82;
                break;
            }
            // fall through
        case 0:
        default:
            id = 0x81;
            break;
    }
    D_8009824C[0] = id;
}

void func_8001FCA4(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            id = 0x85;
            break;
        case 5:
            id = 0x86;
            break;
        default:
            id = 0x87;
            break;
    }
    D_80098258[1] = id;
}

void func_8001FCE4(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
            id = 0x8E;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            id = 0x8F;
            break;
        case 6:
        case 7:
            id = 0x90;
            break;
        default:
            id = 0x91;
            break;
    }
    D_80098270[3] = id;
}

void func_8001FD3C(void)
{
    switch (Game_work.sce_no)
    {
        case 1:
            D_8009827C[0] = 0x93;
            break;
        default:
            D_8009827C[0] = 0x94;
            break;
    }
    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
            D_8009827C[1] = 0x95;
            break;
        case 2:
        case 3:
        case 4:
            D_8009827C[1] = 0x96;
            break;
        default:
            D_8009827C[1] = 0x97;
            break;
    }
}

void func_8001FD90(void)
{
    switch (Game_work.sce_no)
    {
        case 1:
            D_8009828C[0] = 0x9D;
            break;
        default:
            D_8009828C[0] = 0x9E;
            break;
    }
    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
            D_8009828C[1] = 0x9F;
            break;
        case 2:
        case 3:
        case 4:
            D_8009828C[1] = 0xA0;
            break;
        default:
            D_8009828C[1] = 0xA1;
            break;
    }
}

void func_8001FDE4(void)
{
    sint16 id;

    switch (Game_work.sce_no)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            id = 0xC3;
            break;
        case 4:
            id = 0xC4;
            break;
        case 11:
            id = 0xC4;
            break;
        default:
            return;
    }
    D_800982F8[1] = D_800982FC[0] = D_800982FC[1] = id;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8001FE38);

void func_8002037C(void)
{
    D_800BEAD8[0] = 0;
    D_8009893C    = D_800BEAD8;
    D_800987D4    = 0;
    D_800987DC    = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_800203A8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_800207F8);

void func_80020A40(void)
{
    D_80097C3C = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80020A4C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80020BB4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80021258);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80021548);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80021834);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8002196C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80021B14);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_800221E0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8002235C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80022A94);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80022FD4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80023144);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8002366C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80023728);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_800238B4);

void map_block_masks_draw(void)
{
    switch (D_1F800075)
    {
        case 0:
        default:
            D_1F800004 = 0x400;
            map_blocks_draw(Map_block_mask, 0);
            map_blocks_draw(Map_block_mask + MAP_BLOCK_ROWS, 1);
            break;
        case 1:
            D_1F800004 = 0;
            map_blocks_draw(Map_block_mask, 1);
            map_blocks_draw(Map_block_mask + MAP_BLOCK_ROWS, 1);
            break;
        case 2:
            D_1F800004 = 0;
            map_blocks_draw2(Map_block_mask, 2);
            map_blocks_draw2(Map_block_mask + MAP_BLOCK_ROWS, 2);
            break;
        case 3:
            D_1F800004 = 0;
            map_blocks_draw2(Map_block_mask, 3);
            map_blocks_draw2(Map_block_mask + MAP_BLOCK_ROWS, 3);
            break;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80023CF0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80023E1C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80023EA8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8002466C);

// Draws the map blocks whose bits are set in rows[] (one word per row of 0x20 blocks, MSB first;
// the first row's bit 31 is cleared first), choosing the model's level of detail by depth.
// Remaining difference: the prologue copies rows (a0) into s4 before setting up sxy (0x1F800100) in
// s3; the target sets sxy first. Everything else matches.
#ifdef NON_MATCHING
void map_blocks_draw(uint32 *rows, sint32 kind)
{
    MAP_BLOCK *b;
    MAP_BLOCK *row_end;
    MAP_BLOCK *end;
    sint32 bits;
    long *sxy;
    STG_MODEL *model;
    uint32 *lod;
    VECTOR pos;

    sxy = Scratch_sxy;
    b   = Map_blocks;
    end = b + 0x800;
    *rows &= 0x7FFFFFFF;
    do
    {
        bits = *rows;
        if (bits != 0)
        {
            *rows = 0;
            for (row_end = b + 0x20; b < row_end; bits <<= 1, b++)
            {

                if (bits < 0)
                {
                    model     = (STG_MODEL *)(b->model & 0xFFFFFF);
                    sxy[0x10] = *(long *)&b->pos.vx;
                    sxy[0x11] = *(long *)&b->pos.vz;
                    gte_ldv0(&sxy[0x10]);
                    gte_rt();
                    gte_stlvnl(&pos);
                    pos.vz >>= Scratch_scale_shift;
                    if (pos.vz > 0x1C20)
                    {
                        lod = &model->lod[2];
                    }
                    else if (pos.vz > 0xAF0)
                    {
                        lod = &model->lod[1];
                    }
                    else
                    {
                        lod = &model->lod[0];
                    }
                    if (((sint16 *)sxy)[0x23] == 0)
                    {
                        lod += 3;
                    }
                    lod = (uint32 *)*lod;
                    Map_block_draw_tbl[kind][(uint32)lod >> 31]((uint32 *)((uint32)lod & 0xFFFFFF), pos.vz);
                }
            }
        }
        else
        {
            b += 0x20;
        }
        rows++;
    } while (b < end);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", map_blocks_draw);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80024D4C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80024E94);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80024F30);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80025748);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80025874);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80025900);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8002626C);

// Same code as map_blocks_draw (parked the same way).
#ifdef NON_MATCHING
void map_blocks_draw2(uint32 *rows, sint32 kind)
{
    MAP_BLOCK *b;
    MAP_BLOCK *row_end;
    MAP_BLOCK *end;
    sint32 bits;
    long *sxy;
    STG_MODEL *model;
    uint32 *lod;
    VECTOR pos;

    sxy = Scratch_sxy;
    b   = Map_blocks;
    end = b + 0x800;
    *rows &= 0x7FFFFFFF;
    do
    {
        bits = *rows;
        if (bits != 0)
        {
            *rows = 0;
            for (row_end = b + 0x20; b < row_end; bits <<= 1, b++)
            {

                if (bits < 0)
                {
                    model     = (STG_MODEL *)(b->model & 0xFFFFFF);
                    sxy[0x10] = *(long *)&b->pos.vx;
                    sxy[0x11] = *(long *)&b->pos.vz;
                    gte_ldv0(&sxy[0x10]);
                    gte_rt();
                    gte_stlvnl(&pos);
                    pos.vz >>= Scratch_scale_shift;
                    if (pos.vz > 0x1C20)
                    {
                        lod = &model->lod[2];
                    }
                    else if (pos.vz > 0xAF0)
                    {
                        lod = &model->lod[1];
                    }
                    else
                    {
                        lod = &model->lod[0];
                    }
                    if (((sint16 *)sxy)[0x23] == 0)
                    {
                        lod += 3;
                    }
                    lod = (uint32 *)*lod;
                    Map_block_draw_tbl[kind][(uint32)lod >> 31]((uint32 *)((uint32)lod & 0xFFFFFF), pos.vz);
                }
            }
        }
        else
        {
            b += 0x20;
        }
        rows++;
    } while (b < end);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", map_blocks_draw2);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_8002694C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80026A78);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_80026B04);

void func_800272C8(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001F828", func_800272D0);

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_800981BC\n"
        ".globl D_800981D0\n"
        ".globl D_800981E0\n"
        ".globl D_800981EC\n"
        ".globl D_800981FC\n"
        ".globl D_80098210\n"
        ".globl D_80098220\n"
        ".globl D_80098234\n"
        ".globl D_80098238\n"
        ".globl D_8009824C\n"
        ".globl D_80098258\n"
        ".globl D_80098268\n"
        ".globl D_80098270\n"
        ".globl D_8009827C\n"
        ".globl D_8009828C\n"
        ".globl D_80098290\n"
        ".globl D_8009829C\n"
        ".globl D_800982BC\n"
        ".globl D_800982C8\n"
        ".globl D_800982D0\n"
        ".globl D_800982D8\n"
        ".globl D_800982E4\n"
        ".globl D_800982EC\n"
        ".globl D_800982F8\n"
        ".globl D_8009830C\n"
        ".globl D_80098314\n"
        ".globl D_80098324\n"
        ".globl D_800981E2\n.set D_800981E2, D_800981E0+2\n");
