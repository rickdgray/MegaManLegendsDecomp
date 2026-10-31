#include "common.h"
#include "system.h"
#include "display.h"
#include "cmd.h"
#include "intro.h"
#include "pad.h"
#include "scratch.h"
#include "psyq/libapi.h"
#include "psyq/libpress.h"
#include "psyq/libsnd.h"
#include "psyq/libetc.h"

void main(void)
{
    System_init();
    VSync(0);
    SetDispMask(1);
    Intro_init();

    while (1)
    {
        while (Vsync_count < Vsync_wait)
        {
        }

        Vsync_count = 0;
        PutDispEnv(&Disp_env_ptr->disp);
        PutDrawEnv(&Disp_env_ptr->draw);
        func_80011680();
        DrawOTag(Disp_env_ptr->ot);
        Pad_update_all();
        Dbl_buff_idx ^= 1;
        Disp_env_ptr = &Disp_env[Dbl_buff_idx];
        ClearOTag(Disp_env_ptr->ot, 8);
        Intro_task();
        Cmd_exec();
        DrawSync(0);
    }
}

void System_init(void)
{
    ResetCallback();
    Cd_init();
    SsInit();
    VSync(0);
    ResetGraph(0);
    DecDCTReset(0);
    SetVideoMode(MODE_NTSC);

    InitPAD((u_char *)&Joy1, 8, (u_char *)&Joy2, 8);
    // ugly, but idiomatic to Capcom's codebase
    *(uint32 *)Joy1.unk34 = 0x4001;
    *(uint32 *)Joy2.unk34 = 0x4001;
    StartPAD();
    ChangeClearPAD(0);

    ClearImage(&Clear_rect, 0, 0, 0);
    Disp_env_set(DISP_MODE_640);
    Disp_env_ptr = Disp_env;
    Dbl_buff_idx = 0;
    Vsync_wait   = VSYNC_30FPS;
    VSyncCallback(Vsync_handler);
    D_80059BBC = 0;
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);
    SsSetSerialVol(SS_SERIAL_A, SS_VOL_MAX, SS_VOL_MAX);
}

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

void Pad_update(PAD_WORK *pad)
{
    if (pad->status == 0xFF)
    {
        pad->type                  = 0xFF;
        pad->flags.all             = 0;
        PAD_NOW(*pad)              = 0;
        *(uint32 *)pad->analog_cpy = 0;
        *(uint32 *)pad->old        = 0;
    }
    else
    {
        pad->type                  = pad->id >> 4;
        PAD_OLD(*pad)              = PAD_NOW(*pad);
        *(uint32 *)pad->analog_cpy = *(uint32 *)pad->analog;
        PAD_NOW(*pad)              = ~PAD_RAW(*pad);
        PAD_ON(*pad)               = PAD_NOW(*pad) & ~PAD_OLD(*pad);
        PAD_OFF(*pad)              = PAD_OLD(*pad) & ~PAD_NOW(*pad);

        if ((pad->flags.all & 3) == 1)
        {
            pad->unk36 = 1;
        }

        if ((pad->flags.all & 3) == 2)
        {
            pad->unk36 = 0;
        }

        pad->flags.bit.prev = pad->flags.bit.cur;
    }
}

void Pad_update_all(void)
{
    Pad_update(&Joy1);
    Pad_update(&Joy2);
}

void Vsync_handler(void)
{
    Vsync_count++;
}

void Disp_adjust(void)
{
    DISPENV disp;
    PAD_WORK save0;
    PAD_WORK save1;
    sint32 x;
    sint32 y;

    save0 = Joy1;
    save1 = Joy2;
    y     = 0;
    x     = 0;

    while (1)
    {
        Pad_update_all();

        if (PAD_NOW(Joy2) & PAD_UP)
        {
            y -= 8;
        }

        if (PAD_NOW(Joy2) & PAD_DOWN)
        {
            y += 8;
        }

        if (PAD_NOW(Joy2) & PAD_RIGHT)
        {
            x += 8;
        }

        if (PAD_NOW(Joy2) & PAD_LEFT)
        {
            x -= 8;
        }

        if (PAD_ON(Joy2) & PAD_START)
        {
            break;
        }

        if (PAD_ON(Joy2) & PAD_R2)
        {
            break;
        }

        SetDefDispEnv(&disp, x, y, 320, 240);
        VSync(0);
        PutDispEnv(&disp);
    }

    Joy1 = save0;
    Joy2 = save1;
}

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
    uint32 i;
    uint32 j;
    uint32 k;
    SPRT *p0;
    SPRT *p1;

    img                         = copyright_tim;
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
                p0->x0 = p1->x0 = i * 128 + j * 32;
                p0->y0 = p1->y0 = k * 64;
                p0->u0 = p1->u0 = j * 32;
                p0->v0 = p1->v0 = k * 64;
                p0->clut = p1->clut = getClut(0, 240);
                p0->r0 = p1->r0 = 0;
                p0->g0 = p1->g0 = 0;
                p0->b0 = p1->b0 = 0;
                p0->w = p1->w = 32;
                p0->h = p1->h = 64;
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
            Disp_env_set(DISP_MODE_320);
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
            Disp_env_set(DISP_MODE_320);
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
            Disp_env_set(DISP_MODE_320);

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
