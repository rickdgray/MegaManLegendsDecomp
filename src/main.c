#include "common.h"
#include "display.h"
#include "cmd.h"

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

INCLUDE_ASM("asm/nonmatchings/main", InitCd);

void func_800110E4(void) {
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

INCLUDE_ASM("asm/nonmatchings/main", func_80011C84);

INCLUDE_ASM("asm/nonmatchings/main", func_80011CEC);

void QueuePlayMovie(int arg1, int arg2, short arg3) {
    g_cmdWritePtr->type = 5;
    g_cmdWritePtr->args.arg1 = arg1;
    g_cmdWritePtr->args.arg2 = arg2;
    g_cmdWritePtr->args.arg3 = arg3;
    g_cmdWritePtr++;
}

INCLUDE_ASM("asm/nonmatchings/main", IsBusy);

INCLUDE_ASM("asm/nonmatchings/main", func_80011DA8);

INCLUDE_ASM("asm/nonmatchings/main", DrawCopyrightWarning);

INCLUDE_ASM("asm/nonmatchings/main", Screen_FadeImage);

INCLUDE_ASM("asm/nonmatchings/main", func_800121D8);

INCLUDE_ASM("asm/nonmatchings/main", func_80012264);

INCLUDE_ASM("asm/nonmatchings/main", Screen_LaunchGame);

INCLUDE_ASM("asm/nonmatchings/main", RunIntroSequence);
