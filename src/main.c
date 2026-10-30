#include "common.h"
#include "display.h"
#include "cmd.h"
#include "screen.h"

INCLUDE_ASM("asm/nonmatchings/main", main);

INCLUDE_ASM("asm/nonmatchings/main", func_800108EC);

void SetupDisplay(int mode) {
    SetDefDrawEnv(&g_displayBuffers[0].draw, 0, 0,   g_screenWidths[mode], 240);
    SetDefDispEnv(&g_displayBuffers[0].disp, 0, 256, g_screenWidths[mode], 240);
    SetDefDrawEnv(&g_displayBuffers[1].draw, 0, 256, g_screenWidths[mode], 240);
    SetDefDispEnv(&g_displayBuffers[1].disp, 0, 0,   g_screenWidths[mode], 240);
    InitDisplayBuffer(&g_displayBuffers[0]);
    InitDisplayBuffer(&g_displayBuffers[1]);
}

void InitDisplayBuffer(DisplayBuffer *buf) {
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

void InitCd(void) {
    int i;

    while (CdInit() == 0) {
    }

    D_80059BCA = 0; // redundant
    D_80059C00 = 0;
    D_80059BC8 = 0;
    D_80059C74 = 7;
    g_cdMode = 0;
    D_80059C48 = 0;
    D_80059BCA = 0; // redundant

    Cd_ControlRetry(CdlSetmode, &g_cdMode, g_cdResult);

    D_80059BD4 = 1;

    for (i = 0; i < 16; i++) {
        g_cmdQueue[i].type = 0;
    }

    D_80059C38 = g_cmdQueue;
    g_cmdWritePtr = g_cmdQueue;
    
    D_80059BB4 = 0;
    D_80059BD8 = 0;
    D_80059C24 = 0;
    D_80059C20 = 0;
    D_80059BC9 = 0;
}

void Cmd_Nop(void) {
}

INCLUDE_ASM("asm/nonmatchings/main", func_800110EC);

INCLUDE_ASM("asm/nonmatchings/main", func_8001115C);

INCLUDE_ASM("asm/nonmatchings/main", func_80011194);

INCLUDE_ASM("asm/nonmatchings/main", func_80011614);

INCLUDE_ASM("asm/nonmatchings/main", func_80011680);

INCLUDE_ASM("asm/nonmatchings/main", func_80011730);

INCLUDE_ASM("asm/nonmatchings/main", DequeueCommand);

INCLUDE_ASM("asm/nonmatchings/main", func_80011830);

INCLUDE_ASM("asm/nonmatchings/main", func_80011860);

INCLUDE_ASM("asm/nonmatchings/main", func_800118CC);

INCLUDE_ASM("asm/nonmatchings/main", func_80011940);

INCLUDE_ASM("asm/nonmatchings/main", func_80011A64);

INCLUDE_ASM("asm/nonmatchings/main", func_80011C1C);

INCLUDE_ASM("asm/nonmatchings/main", Cd_ControlRetry);

INCLUDE_ASM("asm/nonmatchings/main", func_80011CEC);

void QueuePlayMovie(int arg1, int arg2, short arg3) {
    g_cmdWritePtr->type = 5;
    g_cmdWritePtr->args.arg1 = arg1;
    g_cmdWritePtr->args.arg2 = arg2;
    g_cmdWritePtr->args.arg3 = arg3;
    g_cmdWritePtr++;
}

int IsBusy(void) {
    return g_cmdWritePtr != g_cmdQueue;
}

INCLUDE_ASM("asm/nonmatchings/main", func_80011DA8);

INCLUDE_ASM("asm/nonmatchings/main", DrawCopyrightWarning);

INCLUDE_ASM("asm/nonmatchings/main", Screen_FadeImage);

INCLUDE_ASM("asm/nonmatchings/main", func_800121D8);

INCLUDE_ASM("asm/nonmatchings/main", func_80012264);

INCLUDE_ASM("asm/nonmatchings/main", Screen_LaunchGame);

void RunIntroSequence(void) {
    g_screenFuncs[g_screenIndex]();
}
