#include "common.h"
#include "code_8001786C.h"
#include "display.h"
#include "fastmem.h"
#include "game.h"
#include "moji.h"
#include "scratch.h"
#include "sub_scrn.h"
#include "system.h"
#include "vram.h"

// Called only from this file
void func_80017E94(void);
void func_800196A0(void);
void func_80019760(sint16 x, sint16 y, sint16 angle, sint16 scale);

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

// Copies D_8008F168's two half rows at D_80097A38 to its second copy, darkened by 18 while
// Game_work.unk060 is 0-32 and by 8 while it is 33-64 (unchanged from 65 up).
void func_800179FC(void)
{
    uint32 i;
    uint32 j;
    sint32 r;
    sint32 g;
    sint32 b;
    uint32 color;
    uint32 stp;
    sint32 timer;

    timer = Game_work.unk060;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 128;)
        {
            color = D_8008F168[(D_80097A38[i].y << 8) + (j + D_80097A38[i].x)];
            r     = color & 0x1F;
            g     = (color >> 5) & 0x1F;
            b     = (color >> 10) & 0x1F;
            stp   = color & 0x8000;
            if ((uint32)timer < 65)
            {
                if ((uint32)timer >= 33)
                {
                    r -= 8;
                    g -= 8;
                    b -= 8;
                }
                else
                {
                    r -= 18;
                    g -= 18;
                    b -= 18;
                }
                if (r < 0)
                {
                    r = 0;
                }
                if (g < 0)
                {
                    g = 0;
                }
                if (b < 0)
                {
                    b = 0;
                }
                color = stp | (b << 10) | (g << 5) | r;
            }
            D_8008F168[CLUT_BUF_COPY + (j++ + D_80097A38[i].x) + (D_80097A38[i].y << 8)] = color;
        }
    }
}

// Draws the full-screen D_80098A28 tile at the fade's gray level while its draw flag is set.
void func_80017B24(void)
{
    if (Fade_work.draw != 0)
    {
        setRGB0(&D_80098A28[Dbl_buff_idx], Fade_work.level, Fade_work.level, Fade_work.level);
        addPrim(&Disp_env_ptr->ot[1], &D_80098A28[Dbl_buff_idx]);
        addPrim(&Disp_env_ptr->ot[1], &D_80098A10[Dbl_buff_idx]);
    }
}

// Starts a screen fade unless one is running: arg 0-3 fade in from black, 8-11 out to black,
// 5-7 in from white, 13-15 out to white (bits 0-1 pick the speed); 16-23 start a wipe (others
// wipe 0). Sets up the fade tiles and opens the fade thread.
void Fade_start(sint32 arg)
{
    uint32 i;
    TILE *tile;

    if (Fade_work.busy == 0)
    {
        // Each case is written out in full: the shared tails come from cross-jumping.
        switch (arg)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 8:
            case 9:
            case 10:
            case 11:
                Fade_work.routine_0 = 0;
                Fade_work.busy      = D_80097A44[arg >> 3];
                Fade_work.speed     = D_80097A48[arg & 3];
                break;
            case 5:
            case 6:
            case 7:
            case 13:
            case 14:
            case 15:
                Fade_work.routine_0 = 1;
                Fade_work.busy      = D_80097A44[arg >> 3];
                Fade_work.speed     = D_80097A48[arg & 3];
                break;
            case 16:
            case 17:
            case 18:
                Fade_work.routine_0         = 2;
                Fade_work.routine_3         = arg - 16;
                Fade_work.routine_1         = 0;
                Fade_work.routine_2         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
            case 19:
                Fade_work.routine_0         = 2;
                Fade_work.routine_1         = 1;
                Fade_work.routine_2         = 0;
                Fade_work.routine_3         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
            case 20:
                Fade_work.routine_0         = 2;
                Fade_work.routine_1         = 2;
                Fade_work.routine_2         = 0;
                Fade_work.routine_3         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
            case 21:
                Fade_work.routine_0         = 2;
                Fade_work.routine_1         = 3;
                Fade_work.routine_2         = 0;
                Fade_work.routine_3         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
            case 22:
                Fade_work.routine_0         = 2;
                Fade_work.routine_1         = 4;
                Fade_work.routine_2         = 0;
                Fade_work.routine_3         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
            case 23:
                Fade_work.routine_0         = 2;
                Fade_work.routine_1         = 5;
                Fade_work.routine_2         = 0;
                Fade_work.routine_3         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
            default:
                Fade_work.routine_0         = 2;
                Fade_work.routine_1         = 0;
                Fade_work.routine_2         = 0;
                Fade_work.routine_3         = 0;
                *(uint32 *)&Fade_work.timer = 0;
                Fade_work.busy              = -1;
                break;
        }
        for (i = 0; i < 2; i++)
        {
            setlen(&D_80098A28[i], 3);
            setcode(&D_80098A28[i], 0x62);
            tile     = &D_80098A28[i];
            tile->w  = 320;
            tile->x0 = 0;
            tile->y0 = 0;
            tile->h  = 240;
            SetDrawMode(&D_80098A10[i], 0, 0, GetTPage(2, 2 - (Fade_work.routine_0 & 1), 0, 0), NULL);
        }
        Thread_open(2, func_80017E94);
    }
}

void func_80017E94(void)
{
    D_80082140[Fade_work.routine_0]();
}

// The fade thread for routine_0 0 and 1: fading in (busy > 0) steps the level down from 255
// (routine_1 0), fading out steps it up from 0 (1), by speed each frame; then it holds
// Vsync_wait frames (2) and ends the thread, hiding the tile after a fade in.
void Fade_main(void)
{
    FADE_WORK *wp;

    wp = &Fade_work;
    if (Fade_work.busy > 0)
    {
        Fade_work.routine_1 = 0;
        Fade_work.level     = 255;
    }
    else
    {
        Fade_work.routine_1 = 1;
        Fade_work.level     = 0;
    }
    wp->timer = 0;
    wp->draw  = 1;
    while (1)
    {
        switch (wp->routine_1)
        {
            case 0:
                if ((wp->level -= wp->speed) <= 0)
                {
                    wp->level     = 0;
                    wp->routine_1 = 2;
                    wp->speed     = Vsync_wait;
                }
                break;
            case 1:
                if ((wp->level += wp->speed) >= 256)
                {
                    wp->level     = 255;
                    wp->routine_1 = 2;
                    wp->speed     = Vsync_wait;
                }
                break;
            case 2:
                if (wp->speed == 0)
                {
                    if (wp->busy == 1)
                    {
                        wp->draw = 0;
                    }
                    wp->busy = 0;
                    func_80012ECC();
                }
                else
                {
                    wp->speed--;
                }
                break;
        }
        Thread_wait(1);
    }
}

// Runs the wipe's step D_800821E0[routine_1][routine_2] once a frame, forever.
void func_80018050(void)
{
    while (1)
    {
        D_800821BC[D_800821E0[Fade_work.routine_1][Fade_work.routine_2]]();
        Thread_wait(1);
    }
}

// Entry 0 of D_800821BC. Sub-step 0: once Dbl_buff_idx is 1, zeroes both buffers' vertical
// offsets and the clear/dither flags, stops all messages and moves on; sub-step 1 ends the step.
void func_800180D4(void)
{
    switch (Fade_work.routine_3)
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
                Fade_work.routine_3++;
                func_800196A0();
            }
            break;
        case 1:
            Fade_work.routine_3 = 0;
            Fade_work.routine_2++;
            break;
    }
}

// Same code as func_800180D4.
void func_800181D4(void)
{
    switch (Fade_work.routine_3)
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
                Fade_work.routine_3++;
                func_800196A0();
            }
            break;
        case 1:
            Fade_work.routine_3 = 0;
            Fade_work.routine_2++;
            break;
    }
}

// Entry 1 of D_800821BC. Sub-step 0: on the frame Dbl_buff_idx is 1 (and D_80098824 clear),
// sets buffer 0 to display from y 256 and draw at y 0, buffer 1 the other way round, with
// the background clear and dither on; on buffer 0's frames clears D_80098824 and D_80098864.
// Sub-step 1 clears D_80098810 and the fade's busy flag and calls func_80012ECC.
void func_800182D4(void)
{
    switch (Fade_work.routine_3)
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
                Fade_work.routine_3++;
            }
            break;
        case 1:
            D_80098810     = 0;
            Fade_work.busy = 0;
            func_80012ECC();
            break;
    }
}

// Entry 8 of D_800821BC: func_800182D4 without the D_80098864 stores.
void func_8001840C(void)
{
    switch (Fade_work.routine_3)
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
                Fade_work.routine_3++;
            }
            break;
        case 1:
            D_80098810     = 0;
            Fade_work.busy = 0;
            func_80012ECC();
            break;
    }
}

// A wipe step: the screen image, cut into the ten D_80098E70 quads, spins (routine_3 1 only
// zooms) and grows from the center for 64 frames, flashing between two colors; then the
// screen is left black and the wipe moves on.
void Wipe_zoom(void)
{
    POLY_FT4 *prims;
    POLY_FT4 *p;
    sint32 i;
    uint32 color;
    uint32 tpage;
    sint32 frame;
    sint32 mode;
    sint32 scale;

    D_80098810 = 0;
    prims      = D_80098E70[Dbl_buff_idx];
    frame      = Fade_work.timer;
    mode       = Fade_work.routine_3;
    if ((frame & 3) == 0)
    {
        color = D_80097A60[mode][0];
    }
    else
    {
        color = D_80097A60[mode][1];
    }
    tpage = D_80097A78[mode];
    scale = frame * 200 + 256;
    if (mode == 1)
    {
        func_80019760(160, 120, 0, scale);
    }
    else
    {
        func_80019760(160, 120, frame << 5, scale);
    }
    for (i = 0; i < 10; i++)
    {
        p = &prims[i];
        SET_TAG_LEN(p, 9);
        *(uint32 *)&p->r0 = color;
        p->tpage          = (p->tpage & 0x7F) | tpage;
        p->clut           = GetClut(0, 0x1F0);
        p->x0             = D_80099190[D_80082194[i][0]].vx;
        p->y0             = D_80099190[D_80082194[i][0]].vy;
        p->x1             = D_80099190[D_80082194[i][1]].vx;
        p->y1             = D_80099190[D_80082194[i][1]].vy;
        p->x2             = D_80099190[D_80082194[i][2]].vx;
        p->y2             = D_80099190[D_80082194[i][2]].vy;
        p->x3             = D_80099190[D_80082194[i][3]].vx;
        p->y3             = D_80099190[D_80082194[i][3]].vy;
        addPrim(&Disp_env_ptr->ot[2], p);
    }
    if (++Fade_work.timer >= 64)
    {
        Fade_work.draw      = 1;
        Fade_work.routine_0 = 0;
        Fade_work.routine_3 = 0;
        Fade_work.level     = 255;
        Fade_work.routine_2++;
    }
}

// A wipe step: a dark spot (32 subtractive fan segments, full at the center) grows from the
// screen's center for 64 frames; then the screen is left black (fade tile at 255) and the
// wipe moves on.
void Wipe_spot(void)
{
    sint32 j;
    sint32 i;
    uint8 idx;
    POLY_G4 *g4;
    POLY_G4 *p;
    DISP_ENV *de;

    switch (Fade_work.routine_3)
    {
        case 0:
            for (i = 0; i < 32; i++)
            {
                D_80099AD8[i].vx = rcos(i << 7);
                D_80099AD8[i].vy = rsin(i << 7);
            }
            for (j = 0; j < 2; j++)
            {
                for (i = 0; i < 32; i++)
                {
                    g4 = &D_800991D8[j][i];
                    SET_TAG_LEN(g4, 8);
                    SET_CODE_RGB(g4, 0x3A, 0xFF, 0xFF, 0xFF);
                    SET_RGB_WORD(g4->r1, 0xFF, 0xFF, 0xFF);
                    SET_RGB_WORD(g4->r2, 0, 0, 0);
                    SET_RGB_WORD(g4->r3, 0, 0, 0);
                }
                SetDrawMode(&D_80098160[j], 1, 1, 0x140, NULL);
            }
            Fade_work.routine_3++;
            break;
        case 1:
            D_80098810 = 0;
            // j: the radius
            j  = Fade_work.timer * 4;
            de = Disp_env_ptr;
            for (i = 0; i < 32; i++)
            {
                idx   = Dbl_buff_idx;
                p     = &D_800991D8[idx][i];
                p->x0 = 160;
                p->y0 = 120;
                p->x1 = 160;
                p->y1 = 120;
                p->x2 = ((D_80099AD8[i].vx * j) >> 12) + 160;
                p->y2 = ((D_80099AD8[i].vy * j) >> 12) + 120;
                p->x3 = ((D_80099AD8[(i + 1) & 0x1F].vx * j) >> 12) + 160;
                p->y3 = ((D_80099AD8[(i + 1) & 0x1F].vy * j) >> 12) + 120;
                addPrim(&de->ot[2], p);
            }
            addPrim(&Disp_env_ptr->ot[2], &D_80098160[idx]);
            if (++Fade_work.timer >= 64)
            {
                Fade_work.draw      = 1;
                Fade_work.routine_0 = 0;
                Fade_work.routine_3 = 0;
                Fade_work.level     = 255;
                Fade_work.routine_2++;
            }
            break;
    }
}

// A wipe step: an iris (a subtractive ring of 32 segments, black outside) closes on the
// screen's center over 60 frames, then its outer edge follows for 5 more; then the screen is
// left black and the wipe moves on.
void Wipe_iris(void)
{
    sint32 i;
    sint32 j;
    sint32 outer;
    uint8 idx;
    POLY_G4 *g4;
    POLY_G4 *p;
    DISP_ENV *de;
    DISP_ENV *ot_de;

    switch (Fade_work.routine_3)
    {
        case 0:
            for (i = 0; i < 32; i++)
            {
                D_80099AD8[i].vx = rcos(i << 7);
                D_80099AD8[i].vy = rsin(i << 7);
            }
            for (j = 0; j < 2; j++)
            {
                for (i = 0; i < 32; i++)
                {
                    g4 = &D_800991D8[j][i];
                    SET_TAG_LEN(g4, 8);
                    SET_CODE_RGB(g4, 0x3A, 0, 0, 0);
                    SET_RGB_WORD(g4->r1, 0, 0, 0);
                    SET_RGB_WORD(g4->r2, 0xFF, 0xFF, 0xFF);
                    SET_RGB_WORD(g4->r3, 0xFF, 0xFF, 0xFF);
                }
                SetDrawMode(&D_80098160[j], 1, 1, 0x140, NULL);
            }
            Fade_work.timer = 60;
            Fade_work.routine_3++;
            break;
        case 1:
            D_80098810 = 0;
            // j: the inner radius
            j  = Fade_work.timer * 4;
            de = Disp_env_ptr;
            for (i = 0; i < 32; i++)
            {
                idx   = Dbl_buff_idx;
                p     = &D_800991D8[idx][i];
                p->x0 = ((D_80099AD8[i].vx * j) >> 12) + 160;
                p->y0 = ((D_80099AD8[i].vy * j) >> 12) + 120;
                p->x1 = ((D_80099AD8[(i + 1) & 0x1F].vx * j) >> 12) + 160;
                p->y1 = ((D_80099AD8[(i + 1) & 0x1F].vy * j) >> 12) + 120;
                p->x2 = ((D_80099AD8[i].vx * 105) >> 11) + 160;
                p->y2 = ((D_80099AD8[i].vy * 105) >> 11) + 120;
                p->x3 = ((D_80099AD8[(i + 1) & 0x1F].vx * 105) >> 11) + 160;
                p->y3 = ((D_80099AD8[(i + 1) & 0x1F].vy * 105) >> 11) + 120;
                addPrim(&de->ot[2], p);
            }
            addPrim(&Disp_env_ptr->ot[2], &D_80098160[idx]);
            if (--Fade_work.timer == 0)
            {
                Fade_work.timer = 5;
                Fade_work.routine_3++;
            }
            break;
        case 2:
            if (--Fade_work.timer == 0)
            {
                Fade_work.draw      = 1;
                Fade_work.routine_0 = 0;
                Fade_work.routine_3 = 0;
                Fade_work.level     = 255;
                Fade_work.routine_2++;
            }
            j     = Fade_work.timer * 4;
            outer = Fade_work.timer * 16 + 16;
            // Its own OT pointer, loaded after the counter's start.
            for (i = 0, ot_de = Disp_env_ptr; i < 32; i++)
            {
                idx   = Dbl_buff_idx;
                p     = &D_800991D8[idx][i];
                p->x0 = ((D_80099AD8[i].vx * j) >> 12) + 160;
                p->y0 = ((D_80099AD8[i].vy * j) >> 12) + 120;
                p->x1 = ((D_80099AD8[(i + 1) & 0x1F].vx * j) >> 12) + 160;
                p->y1 = ((D_80099AD8[(i + 1) & 0x1F].vy * j) >> 12) + 120;
                p->x2 = ((D_80099AD8[i].vx * outer) >> 12) + 160;
                p->y2 = ((D_80099AD8[i].vy * outer) >> 12) + 120;
                p->x3 = ((D_80099AD8[(i + 1) & 0x1F].vx * outer) >> 12) + 160;
                p->y3 = ((D_80099AD8[(i + 1) & 0x1F].vy * outer) >> 12) + 120;
                addPrim(&ot_de->ot[2], p);
            }
            addPrim(&Disp_env_ptr->ot[2], &D_80098160[idx]);
            break;
    }
}

// A wipe step: two shaded subtractive bands close in from the top and bottom over 60 frames;
// then the screen is left black and the wipe moves on.
void Wipe_bands(void)
{
    sint32 i;
    sint32 j;
    POLY_G4 *g4;
    POLY_G4 *p;
    uint32 idx;
    DISP_ENV *de;

    switch (Fade_work.routine_3)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    g4 = &D_800991D8[i][j];
                    SET_TAG_LEN(g4, 8);
                    SET_CODE_RGB(g4, 0x3A, 0, 0, 0);
                    SET_RGB_WORD(g4->r1, 0, 0, 0);
                    SET_RGB_WORD(g4->r2, 0x30, 0x30, 0x30);
                    SET_RGB_WORD(g4->r3, 0x30, 0x30, 0x30);
                }
                SetDrawMode(&D_80098160[i], 1, 1, 0x140, NULL);
            }
            Fade_work.timer = 60;
            Fade_work.routine_3++;
            break;
        case 1:
            idx        = Dbl_buff_idx;
            de         = Disp_env_ptr;
            D_80098810 = 0;
            p          = &D_800991D8[idx][0];
            // i: the bands' height
            i     = (60 - Fade_work.timer) * 3;
            p->x0 = 0;
            p->y0 = i;
            p->x1 = 320;
            p->y1 = i;
            p->x2 = 0;
            p->y2 = 0;
            p->x3 = 320;
            p->y3 = 0;
            addPrim(&de->ot[2], p);
            p     = &D_800991D8[idx][1];
            p->y0 = 240 - i;
            p->y1 = 240 - i;
            p->x0 = 0;
            p->x1 = 320;
            p->x2 = 0;
            p->y2 = 240;
            p->x3 = 320;
            p->y3 = 240;
            addPrim(&de->ot[2], p);
            addPrim(&de->ot[2], &D_80098160[idx]);
            if (--Fade_work.timer == 0)
            {
                Fade_work.draw      = 1;
                Fade_work.routine_0 = 0;
                Fade_work.routine_3 = 0;
                Fade_work.level     = 255;
                Fade_work.routine_2++;
            }
            break;
    }
}

// A wipe step: dims the screen with a subtractive tile (8 a frame) for 63 frames; then the
// screen is left black and the wipe moves on.
void Wipe_dim(void)
{
    sint32 i;
    TILE *tile;
    uint32 idx;
    DISP_ENV *de;

    switch (Fade_work.routine_3)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                tile = &D_80098178[i];
                SET_TAG_LEN(tile, 3);
                SET_CODE_RGB(tile, 0x62, 8, 8, 8);
                SET_XY0_WORD(tile, 0);
                SET_WH_WORD(tile, 320, 240);
                SetDrawMode(&D_80098160[i], 1, 1, 0x140, NULL);
            }
            Fade_work.timer = 63;
            Fade_work.routine_3++;
            break;
        case 1:
            idx = Dbl_buff_idx;
            de  = Disp_env_ptr;
            addPrim(&de->ot[2], &D_80098178[idx]);
            addPrim(&de->ot[2], &D_80098160[idx]);
            D_80098810 = 0;
            if (--Fade_work.timer == 0)
            {
                Fade_work.draw      = 1;
                Fade_work.routine_0 = 0;
                Fade_work.routine_3 = 0;
                Fade_work.level     = 255;
                Fade_work.routine_2++;
            }
            break;
    }
}

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

// Rotates D_8008214C's 18 points by angle round (x, y), scaled by scale / 0x1000, into
// D_80099190.
void func_80019760(sint16 x, sint16 y, sint16 angle, sint16 scale)
{
    sint32 i;
    sint32 c;
    sint32 s;
    sint32 dx;
    sint32 dy;

    for (i = 0; i < 18; i++)
    {
        dx               = D_8008214C[i].vx - x;
        dy               = D_8008214C[i].vy - y;
        c                = rcos(angle);
        D_80099190[i].vx = x + ((scale * ((dx * c - dy * rsin(angle)) >> 8)) >> 16);
        s                = rsin(angle);
        D_80099190[i].vy = y + ((scale * ((dx * s + dy * rcos(angle)) >> 8)) >> 16);
    }
}
