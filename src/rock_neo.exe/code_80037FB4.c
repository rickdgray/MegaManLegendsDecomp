#include "common.h"

// Small data (.sdata 0x80097D28-0x80097D74): reached through $gp in this file.
sint32 D_80097D28 = 0;
sint32 D_80097D2C = 0x200;
sint32 D_80097D30 = 0x30;
sint32 D_80097D34 = 0x200;
sint32 D_80097D38 = 0x300;
sint32 D_80097D3C = 0xa;
sint32 D_80097D40 = 0x14;
sint32 D_80097D44 = 3;
sint32 D_80097D48 = 0x3c;
sint32 D_80097D4C = 1;
sint32 D_80097D50 = 1;
sint32 D_80097D54 = 0x4b0;
sint32 D_80097D58 = 1;
sint32 D_80097D5C = 1;
sint32 D_80097D60 = 0x20ffe0;
sint32 D_80097D64 = 0x20ffe0;
sint32 D_80097D68 = 0x20ffe0;
sint32 D_80097D6C = 0;
sint32 D_80097D70 = 0;

// Small uninitialized statics (.sbss 0x80098660-0x8009869C).
static sint16 D_80098660[2];
static sint16 D_80098664[2];
static sint32 D_80098668;
static sint32 D_8009866C;
static sint32 D_80098670;
static sint32 D_80098674;
static sint32 D_80098678;
static sint32 D_8009867C;
static sint32 D_80098680[2];
static sint32 D_80098688;
static sint32 D_8009868C;
static sint32 D_80098690;
static sint32 D_80098694;
static sint32 D_80098698;

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80037FB4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038324);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038370);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800384A4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800384F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038648);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038894);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800392CC);

void func_8003949C(void)
{
}

void func_800394A4(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800394AC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800395E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039630);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800397E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039820);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800398E0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", Swing_Camera2);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800399EC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039A38);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039A60);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039B80);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039BA4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039BBC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039C08);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039C54);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039CA0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039CEC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039D38);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039DE8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039E18);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039E50);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039FAC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039FFC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A13C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A154);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A218);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A264);

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_80098662\n.set D_80098662, D_80098660+2\n");
