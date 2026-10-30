#include "common.h"
#include "display.h"
#include "cmd.h"
#include "screen.h"

INCLUDE_ASM("asm/nonmatchings/main", main);

INCLUDE_ASM("asm/nonmatchings/main", func_800108EC);

void Disp_env_set(int mode)
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
    buf->draw.dtd = 0;
    buf->draw.dfe = 0;
    buf->draw.isbg = 1;
    buf->draw.r0 = 0;
    buf->draw.g0 = 0;
    buf->draw.b0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main", func_80010B14);

INCLUDE_ASM("asm/nonmatchings/main", func_80010BE0);

INCLUDE_ASM("asm/nonmatchings/main", func_80010C18);

INCLUDE_ASM("asm/nonmatchings/main", func_80010C40);

void Cd_init(void)
{
    int i;

    while (CdInit() == 0)
    {
    }

    D_80059BCA = 0; // redundant
    D_80059C00 = 0;
    D_80059BC8 = 0;
    D_80059C74 = 7;
    Cd_mode = 0;
    D_80059C48 = 0;
    D_80059BCA = 0; // redundant

    Cd_control_retry(CdlSetmode, &Cd_mode, Cd_result);

    D_80059BD4 = 1;

    for (i = 0; i < 16; i++)
    {
        Cmd_queue[i].type = 0;
    }

    g_cmdHead = Cmd_queue;
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

void RunCommandQueue(void)
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

    g_cmdHandlers[g_cmdHead->type]();
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
    p[1].type = 0;
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

void Cmd_set_movie(int arg1, int arg2, short arg3)
{
    Cmd_write_ptr->type = 5;
    Cmd_write_ptr->args.arg1 = arg1;
    Cmd_write_ptr->args.arg2 = arg2;
    Cmd_write_ptr->args.arg3 = arg3;
    Cmd_write_ptr++;
}

int Cmd_busy_check(void)
{
    return Cmd_write_ptr != Cmd_queue;
}

INCLUDE_ASM("asm/nonmatchings/main", Intro_init);

INCLUDE_ASM("asm/nonmatchings/main", intro_copyright_draw);

INCLUDE_ASM("asm/nonmatchings/main", intro_copyright);

void Screen_WaitIdle(void)
{
    RECT rect; // unused, likely copy paste

    switch (g_screenState)
    {
    case 0:
        Disp_env_set(0);
        g_screenState++;
        break;
    case 1:
        if (!Cmd_busy_check())
        {
            g_screenState = 0;
            g_screenIndex++;
        }
        break;
    }
}

void Screen_PlayMovie(void)
{
    RECT rect; // unused, likely copy paste

    switch (g_screenState)
    {
    case 0:
        Disp_env_set(0);
        Cmd_set_movie(0xd0, 0x91, 0x2008);
        g_screenState++;
        break;
    case 1:
        if (!Cmd_busy_check())
        {
            g_screenState = 0;
            g_screenIndex++;
        }
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main", intro_launch_game);

void Intro_task(void)
{
    intro_tbl[g_screenIndex]();
}
