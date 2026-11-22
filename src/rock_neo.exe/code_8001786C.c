#include "common.h"
#include "code_8001786C.h"
#include "display.h"
#include "fastmem.h"
#include "game.h"
#include "moji.h"
#include "scratch.h"
#include "system.h"
#include "vram.h"

// Called only from this file
void func_800196A0(void);

// Copies the Clut_buf rows whose Clut_buf_dirty bit is set to the second copy, clearing the
// mask as it goes.
// TODO: don't think it has callers; might be dead code
void clut_buf_dirty_copy(void)
{
    sint32 i;

    for (i = 0; i < CLUT_BUF_ROWS; i++)
    {
        if (Clut_buf_dirty & 1)
        {
            Mem_copy16(&Clut_buf[i * CLUT_BUF_COLS], &Clut_buf[CLUT_BUF_COPY + i * CLUT_BUF_COLS], 0x20);
        }
        Clut_buf_dirty >>= 1;
    }
}

// Uploads the second copy of Clut_buf to VRAM's CLUT rows.
void Clut_buf_load(void)
{
    LoadImage(&D_80097A28, (u_long *)&Clut_buf[CLUT_BUF_COPY]);
    LoadImage(&D_80097A30, (u_long *)&Clut_buf[CLUT_BUF_COPY + 16 * CLUT_BUF_COLS]);
}

// In the second copy of Clut_buf, makes 0x8000 (black, semi-transparent) fully transparent
// and sets the semi-transparency bit on every other nonzero color.
void Clut_buf_stp_set(void)
{
    sint32 i;
    uint16 color;

    for (i = CLUT_BUF_COPY; i < 2 * CLUT_BUF_COPY; i++)
    {
        color = Clut_buf[i];
        if (color != 0)
        {
            if (color == 0x8000)
            {
                Clut_buf[i] = 0;
            }
            else
            {
                Clut_buf[i] = color | 0x8000;
            }
        }
    }
}

// Saves three half rows of Clut_buf to D_80098B70.
void func_80017994(void)
{
    Mem_copy32(&Clut_buf[0], D_80098B70[0], 8);
    Mem_copy32(&Clut_buf[128], D_80098B70[1], 8);
    Mem_copy32(&Clut_buf[9 * CLUT_BUF_COLS + 128], D_80098B70[2], 8);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800179FC);

// Draws the full-screen D_80098A28 tile at gray level D_80098A76 while D_80098A70 is set.
void func_80017B24(void)
{
    if (D_80098A70 != 0)
    {
        setRGB0(&D_80098A28[Dbl_buff_idx], D_80098A76, D_80098A76, D_80098A76);
        addPrim(&Disp_env_ptr->ot[1], &D_80098A28[Dbl_buff_idx]);
        addPrim(&Disp_env_ptr->ot[1], &D_80098A10[Dbl_buff_idx]);
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017C30);

void func_80017E94(void)
{
    D_80082140[D_80098A68]();
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017ED0);

// Runs the step D_800821E0[D_80098A69][D_80098A6A] once a frame, forever.
void func_80018050(void)
{
    while (1)
    {
        D_800821BC[D_800821E0[D_80098A69][D_80098A6A]]();
        Thread_wait(1);
    }
}

// Entry 0 of D_800821BC. Sub-step 0: once Dbl_buff_idx is 1, zeroes both buffers' vertical
// offsets and the clear/dither flags, stops all messages and moves on; sub-step 1 ends the step.
void func_800180D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (Dbl_buff_idx != 0)
            {
                Disp_env[0].draw.ofs[1] = 0;
                Disp_env[0].draw.clip.y = 0;
                Disp_env[0].disp.disp.y = 0;
                Disp_env[0].draw.isbg   = 0;
                Disp_env[0].draw.dfe    = 0;
                Disp_env[1].draw.ofs[1] = 0;
                Disp_env[1].draw.clip.y = 0;
                Disp_env[1].disp.disp.y = 0;
                Disp_env[1].draw.isbg   = 0;
                Disp_env[1].draw.dfe    = 0;
                MojiTaskKill();
                D_80098810 = 1;
                D_80098824 = 1;
                D_80098864 = 1;
                D_80098A6B++;
                func_800196A0();
            }
            break;
        case 1:
            D_80098A6B = 0;
            D_80098A6A++;
            break;
    }
}

// Same code as func_800180D4.
void func_800181D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (Dbl_buff_idx != 0)
            {
                Disp_env[0].draw.ofs[1] = 0;
                Disp_env[0].draw.clip.y = 0;
                Disp_env[0].disp.disp.y = 0;
                Disp_env[0].draw.isbg   = 0;
                Disp_env[0].draw.dfe    = 0;
                Disp_env[1].draw.ofs[1] = 0;
                Disp_env[1].draw.clip.y = 0;
                Disp_env[1].disp.disp.y = 0;
                Disp_env[1].draw.isbg   = 0;
                Disp_env[1].draw.dfe    = 0;
                MojiTaskKill();
                D_80098810 = 1;
                D_80098824 = 1;
                D_80098864 = 1;
                D_80098A6B++;
                func_800196A0();
            }
            break;
        case 1:
            D_80098A6B = 0;
            D_80098A6A++;
            break;
    }
}

// Entry 1 of D_800821BC. Sub-step 0: on the frame Dbl_buff_idx is 1 (and D_80098824 clear),
// sets buffer 0 to display from y 256 and draw at y 0, buffer 1 the other way round, with
// the background clear and dither on; on buffer 0's frames clears D_80098824 and D_80098864.
// Sub-step 1 clears D_80098810 and D_80098A72 and calls func_80012ECC.
void func_800182D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (Dbl_buff_idx == 0)
            {
                if (D_80098824 != 0)
                {
                    D_80098824 = 0;
                    D_80098864 = 0;
                }
            }
            else if (D_80098824 == 0)
            {
                Disp_env[0].draw.ofs[1] = 0;
                Disp_env[0].draw.clip.y = 0;
                Disp_env[0].disp.disp.y = 256;
                Disp_env[0].draw.isbg   = 1;
                Disp_env[0].draw.dtd    = 0;
                Disp_env[0].draw.dfe    = 1;
                Disp_env[1].draw.ofs[1] = 256;
                Disp_env[1].draw.clip.y = 256;
                Disp_env[1].disp.disp.y = 0;
                Disp_env[1].draw.isbg   = 1;
                Disp_env[1].draw.dtd    = 0;
                Disp_env[1].draw.dfe    = 1;
                D_80098810              = 0;
                D_80098824              = 0;
                D_80098864              = 0;
                D_80098A6B++;
            }
            break;
        case 1:
            D_80098810 = 0;
            D_80098A72 = 0;
            func_80012ECC();
            break;
    }
}

// Entry 8 of D_800821BC: func_800182D4 without the D_80098864 stores.
void func_8001840C(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (Dbl_buff_idx == 0)
            {
                if (D_80098824 != 0)
                {
                    D_80098824 = 0;
                }
            }
            else if (D_80098824 == 0)
            {
                Disp_env[0].draw.ofs[1] = 0;
                Disp_env[0].draw.clip.y = 0;
                Disp_env[0].disp.disp.y = 256;
                Disp_env[0].draw.isbg   = 1;
                Disp_env[0].draw.dtd    = 0;
                Disp_env[0].draw.dfe    = 1;
                Disp_env[1].draw.ofs[1] = 256;
                Disp_env[1].draw.clip.y = 256;
                Disp_env[1].disp.disp.y = 0;
                Disp_env[1].draw.isbg   = 1;
                Disp_env[1].draw.dtd    = 0;
                Disp_env[1].draw.dfe    = 1;
                D_80098810              = 0;
                D_80098824              = 0;
                D_80098A6B++;
            }
            break;
        case 1:
            D_80098810 = 0;
            D_80098A72 = 0;
            func_80012ECC();
            break;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018534);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018850);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018BB8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80019210);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800194C4);

// Sets the texture page and uv of D_80098E70's quads: pages 0-4 across, two rows of 120 lines
// (v 0 and 119); the last page's quads are 63 wide, the others 64.
void func_800196A0(void)
{
    sint32 i;
    sint32 j;
    sint32 v;
    sint32 page;
    POLY_FT4 *p;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 10; j++)
        {
            p = &D_80098E70[i][j];
            if (j < 5)
            {
                v    = 0;
                page = j;
            }
            else
            {
                v    = 119;
                page = j - 5;
            }
            p->tpage = page;
            if (page == 4)
            {
                p->u0 = 0;
                p->v0 = v;
                p->u1 = 63;
                p->v1 = v;
                p->u2 = 0;
                p->v2 = v + 120;
                p->u3 = 63;
                p->v3 = v + 120;
            }
            else
            {
                p->u0 = 0;
                p->v0 = v;
                p->u1 = 64;
                p->v1 = v;
                p->u2 = 0;
                p->v2 = v + 120;
                p->u3 = 64;
                p->v3 = v + 120;
            }
        }
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80019760);
