#include "common.h"
#include "display.h"
#include "cmd.h"
#include "intro.h"
#include "psyq/libsnd.h"

INCLUDE_ASM("asm/nonmatchings/main", main);

INCLUDE_ASM("asm/nonmatchings/main", func_800108EC);

void Disp_env_set(sint32 mode)
{
    SetDefDrawEnv(&Disp_env[0].draw, 0, 0, disp_width_tbl[mode], 240);
    SetDefDispEnv(&Disp_env[0].disp, 0, 256, disp_width_tbl[mode], 240);
    SetDefDrawEnv(&Disp_env[1].draw, 0, 256, disp_width_tbl[mode], 240);
    SetDefDispEnv(&Disp_env[1].disp, 0, 0, disp_width_tbl[mode], 240);
    Disp_env_init(&Disp_env[0]);
    Disp_env_init(&Disp_env[1]);
}

void Disp_env_init(DISP_ENV *buf)
{
    ClearOTag(buf->ot, 8);
    buf->disp.screen.y = 0;
    buf->draw.dtd      = 0;
    buf->draw.dfe      = 0;
    buf->draw.isbg     = 1;
    buf->draw.r0       = 0;
    buf->draw.g0       = 0;
    buf->draw.b0       = 0;
}

INCLUDE_ASM("asm/nonmatchings/main", func_80010B14);

INCLUDE_ASM("asm/nonmatchings/main", func_80010BE0);

INCLUDE_ASM("asm/nonmatchings/main", func_80010C18);

INCLUDE_ASM("asm/nonmatchings/main", func_80010C40);

void Cd_init(void)
{
    sint32 i;

    while (CdInit() == 0)
    {
    }

    D_80059BCA = 0; // redundant
    D_80059C00 = 0;
    D_80059BC8 = 0;
    D_80059C74 = 7;
    Cd_mode    = 0;
    D_80059C48 = 0;
    D_80059BCA = 0; // redundant

    Cd_control_retry(CdlSetmode, &Cd_mode, Cd_result);

    D_80059BD4 = 1;

    for (i = 0; i < 16; i++)
    {
        Cmd_queue[i].type = 0;
    }

    Cmd_exec_ptr  = Cmd_queue;
    Cmd_write_ptr = Cmd_queue;

    D_80059BB4 = 0;
    D_80059BD8 = 0;
    D_80059C24 = 0;
    D_80059C20 = 0;
    D_80059BC9 = 0;
}

void cmd_nop(void)
{
}

INCLUDE_ASM("asm/nonmatchings/main", func_800110EC);

INCLUDE_ASM("asm/nonmatchings/main", func_8001115C);

INCLUDE_ASM("asm/nonmatchings/main", cmd_play_movie);

INCLUDE_ASM("asm/nonmatchings/main", func_80011614);

INCLUDE_ASM("asm/nonmatchings/main", func_80011680);

void Cmd_exec(void)
{
    if (D_80059BDC)
    {
        Cmd_dequeue();
        CdSyncCallback(0);
        CdReadyCallback(0);
        while (CdReset(0) == 0)
        {
        }
    }

    cmd_tbl[Cmd_exec_ptr->type]();
}

#ifdef NON_MATCHING
void Cmd_dequeue(void)
{
    CMD *p;

    p = Cmd_queue;
    while (p->type != 0)
    {
        p->type = p[1].type;
        p->args = p[1].args;
        p++;
    }

    p[1].type  = 0;
    D_80059C24 = 0;
    D_80059C20 = 0;
    Cmd_write_ptr--;
}
#else
INCLUDE_ASM("asm/nonmatchings/main", Cmd_dequeue);
#endif

INCLUDE_ASM("asm/nonmatchings/main", func_80011830);

INCLUDE_ASM("asm/nonmatchings/main", func_80011860);

INCLUDE_ASM("asm/nonmatchings/main", func_800118CC);

INCLUDE_ASM("asm/nonmatchings/main", func_80011940);

INCLUDE_ASM("asm/nonmatchings/main", func_80011A64);

INCLUDE_ASM("asm/nonmatchings/main", func_80011C1C);

void Cd_control_retry(u_char com, u_char *param, u_char *result)
{
    while (CdSync(1, result) == 0)
    {
    }

    while (CdControlB(com, param, result) == 0)
    {
    }
}

INCLUDE_ASM("asm/nonmatchings/main", func_80011CEC);

void Cmd_set_movie(sint32 arg1, sint32 arg2, sint16 arg3)
{
    Cmd_write_ptr->type      = 5;
    Cmd_write_ptr->args.arg1 = arg1;
    Cmd_write_ptr->args.arg2 = arg2;
    Cmd_write_ptr->args.arg3 = arg3;
    Cmd_write_ptr++;
}

sint32 Cmd_busy_check(void)
{
    return Cmd_write_ptr != Cmd_queue;
}

#ifdef NON_MATCHING
void Intro_init(void)
{
    RECT rect;
    u_long *img;
    SPRT *p0;
    SPRT *p1;
    uint32 k;
    uint32 j;
    uint32 i;

    img                         = D_8001DFA4;
    *(uint32 *)&Intro_routine_0 = 2;
    *(uint32 *)&Intro_bright    = 0;

    rect.x = 0;
    rect.y = 240;
    rect.w = 256;
    rect.h = 1;
    LoadImage(&rect, img + 5);

    rect.x = 640;
    rect.y = 0;
    rect.w = 320;
    rect.h = 256;
    LoadImage(&rect, img + 0x88);

    p0 = copyright_sprt[0];
    p1 = copyright_sprt[1];
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 4; k++)
            {
                setSprt(p0);
                setSprt(p1);
                p1->x0   = i * 128 + j * 32;
                p0->x0   = i * 128 + j * 32;
                p1->y0   = k * 64;
                p0->y0   = k * 64;
                p1->u0   = j * 32;
                p0->u0   = j * 32;
                p1->v0   = k * 64;
                p0->v0   = k * 64;
                p1->clut = 0x3c00;
                p0->clut = 0x3c00;
                p1->r0   = 0;
                p0->r0   = 0;
                p1->g0   = 0;
                p0->g0   = 0;
                p1->b0   = 0;
                p0->b0   = 0;
                p1->w    = 32;
                p0->w    = 32;
                p1->h    = 64;
                p0->h    = 64;
                p0++;
                p1++;
            }
        }
    }

    for (i = 0; i < 5; i++)
    {
        SetDrawMode(&copyright_dr_mode[0][i], 0, 0, (i + 10) | 0x80, NULL);
        SetDrawMode(&copyright_dr_mode[1][i], 0, 0, (i + 10) | 0x80, NULL);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main", Intro_init);
#endif

void intro_copyright_draw(uint8 brightness)
{
    sint32 i;
    sint32 j;
    SPRT *sprt;
    DR_MODE *mode;

    sprt = copyright_sprt[Dbl_buff_idx];
    mode = copyright_dr_mode[Dbl_buff_idx];

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 16; j++)
        {
            sprt->r0 = sprt->g0 = sprt->b0 = brightness;
            addPrim(Disp_env_ptr->ot[0], sprt);
            sprt++;
        }

        addPrim(Disp_env_ptr->ot[0], mode);
        mode++;
    }
}

void intro_copyright(void)
{
    switch (Intro_routine_1)
    {
        case 0:
            Intro_bright += 4;
            if (Intro_bright >= 0x80)
            {
                Intro_routine_1++;
                Intro_bright = 0x80;
            }
            intro_copyright_draw(Intro_bright);
            break;
        case 1:
            Intro_timer++;
            if (Intro_timer == 100)
            {
                Intro_bright = 0x80;
                Intro_timer  = 0;
                Intro_routine_1++;
            }
            intro_copyright_draw(0x80);
            break;
        case 2:
            Intro_bright -= 4;
            if (Intro_bright >= 0x80)
            {
                Intro_routine_1 = 0;
                Intro_bright    = 0;
                Intro_routine_0++;
            }
            intro_copyright_draw(Intro_bright);
            break;
    }
}

void intro_wait_idle(void)
{
    RECT rect; // unused, likely copy paste

    switch (Intro_routine_1)
    {
        case 0:
            Disp_env_set(0);
            Intro_routine_1++;
            break;
        case 1:
            if (!Cmd_busy_check())
            {
                Intro_routine_1 = 0;
                Intro_routine_0++;
            }
            break;
    }
}

void intro_play_movie(void)
{
    RECT rect; // unused, likely copy paste

    switch (Intro_routine_1)
    {
        case 0:
            Disp_env_set(0);
            Cmd_set_movie(0xd0, 0x91, 0x2008);
            Intro_routine_1++;
            break;
        case 1:
            if (!Cmd_busy_check())
            {
                Intro_routine_1 = 0;
                Intro_routine_0++;
            }
            break;
    }
}

void intro_launch_game(void)
{
    RECT rect;
    u_long *img;

    switch (Intro_routine_1)
    {
        case 0:
            Disp_env_set(0);

            img = loading_tim;

            rect.x = 0;
            rect.y = 241;
            rect.w = 16;
            rect.h = 1;
            LoadImage(&rect, img + 5);

            rect.x = 640;
            rect.y = 256;
            rect.w = 36;
            rect.h = 32;
            LoadImage(&rect, img + 0x10);

            setSprt(&loading_sprt[0]);
            setSprt(&loading_sprt[1]);

            loading_sprt[0].r0 = loading_sprt[1].r0 = 0x80;
            loading_sprt[0].g0 = loading_sprt[1].g0 = 0x80;
            loading_sprt[0].b0 = loading_sprt[1].b0 = 0x80;
            loading_sprt[0].x0 = loading_sprt[1].x0 = 160;
            loading_sprt[0].y0 = loading_sprt[1].y0 = 200;
            loading_sprt[0].w = loading_sprt[1].w = 144;
            loading_sprt[0].h = loading_sprt[1].h = 32;
            loading_sprt[0].clut = loading_sprt[1].clut = getClut(0, 241);
            loading_sprt[0].u0 = loading_sprt[1].u0 = 0;
            loading_sprt[0].v0 = loading_sprt[1].v0 = 0;

            SetDrawMode(&loading_dr_mode[0], 0, 0, getTPage(0, 0, 640, 256), NULL);
            SetDrawMode(&D_80059B4C, 0, 0, getTPage(0, 0, 640, 256), NULL);

            Intro_routine_1++;
            break;
        case 1:
            Intro_routine_1++;
            break;
        case 2:
            DrawSync(0);
            SsQuit();
            StopPAD();
            _96_init();
            LoadExec(rock_neo_path, 0x801fff00, 0);
            break;
    }

    addPrim(Disp_env_ptr->ot, &loading_sprt[Dbl_buff_idx]);
    addPrim(Disp_env_ptr->ot, &loading_dr_mode[Dbl_buff_idx]);
}

void Intro_task(void)
{
    intro_tbl[Intro_routine_0]();
}
