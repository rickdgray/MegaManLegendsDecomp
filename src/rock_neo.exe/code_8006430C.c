#include "common.h"
#include "code_8006430C.h"
#include "psyq/libapi.h"
#include "game.h"
#include "pad.h"

// Small data (.sdata 0x8009808C-0x8009809C): reached through $gp in this file.
sint32 D_8009808C = 0x30307562;
sint16 D_80098090 = 0x2a3a;
sint8 D_80098092  = 0;
uint8 D_80098093  = 0;
sint32 D_80098094 = 0x30317562;
sint16 D_80098098 = 0x2a3a;
sint8 D_8009809A  = 0;
uint8 D_8009809B  = 0;

// Small uninitialized statics (.sbss 0x80098708-0x80098730).
static sint32 D_80098708;
static sint32 D_8009870C;
static sint32 D_80098710;
static sint32 D_80098714;
static sint32 D_80098718;
static sint32 D_8009871C;
static sint32 D_80098720;
static sint32 D_80098724;
static sint16 D_80098728[4];

// Pool variables reached through $gp in this file.
SPEC_ENT **D_80098844;
SPEC_ENT **D_8009884C;
CODE_8006430C_WORK D_80098910;
SPEC_ENT **D_80098928;
SPEC_ENT **D_8009892C;
uint8 D_80098A04;

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006430C);

void func_8006471C(void)
{
    if (Game_work.unk05B == 2)
    {
        D_80098844 = D_8008F060;
        D_8009884C = D_8008F200;
        D_80098928 = D_8008F260;
        D_8009892C = D_8008F2E4;
    }
    else
    {
        D_80098844 = D_8008EDC4;
        D_8009884C = D_8008EF64;
        D_80098928 = D_8008EFC4;
        D_8009892C = D_8008F048;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006479C);

sint32 func_8006491C(void)
{
    for (;;)
    {
        if (TestEvent(D_80098708) != 0)
        {
            return 0;
        }
        if (TestEvent(D_80098710) != 0)
        {
            return 1;
        }
        if (TestEvent(D_80098714) != 0)
        {
            return 2;
        }
        if (TestEvent(D_8009870C) != 0)
        {
            return 3;
        }
    }
}

sint32 func_80064984(void)
{
    for (;;)
    {
        if (TestEvent(D_80098718) != 0)
        {
            return 0;
        }
        if (TestEvent(D_80098720) != 0)
        {
            return 1;
        }
        if (TestEvent(D_8009871C) != 0)
        {
            return 2;
        }
        if (TestEvent(D_80098724) != 0)
        {
            return 3;
        }
    }
}

void func_800649EC(void)
{
    TestEvent(D_80098708);
    TestEvent(D_80098710);
    TestEvent(D_8009870C);
    TestEvent(D_80098714);
}

void func_80064A34(void)
{
    TestEvent(D_80098718);
    TestEvent(D_80098720);
    TestEvent(D_8009871C);
    TestEvent(D_80098724);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064A7C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064B60);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064BB4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064C08);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064CB8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064D74);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064EA4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064F8C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80064FF0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80065064);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80065384);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80065AA8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80065E08);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_800664BC);

void func_800665E8(void)
{
    D_80098910.active_0              = 0;
    *(uint32 *)&D_80098910.routine_0 = 0;
}

// Returns the routine's result (1 once it is done): the in-game save screen (r3_sup) adds it to
// its routine.
sint32 func_800665FC(sint16 mode)
{
    D_80098910.mode_2    = mode;
    D_80098910.pad_on_A  = PAD_ON(Joy1);
    D_80098910.pad_now_8 = PAD_NOW(Joy1);
    return D_8008FD10[D_80098910.routine_0](&D_80098910);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066664);

sint32 func_800666D8(CODE_8006430C_WORK *wp)
{
    D_8008FD20[wp->routine_1](wp);
    return 0;
}

// Same code as func_800666D8.
sint32 func_80066714(CODE_8006430C_WORK *wp)
{
    D_8008FD20[wp->routine_1](wp);
    return 0;
}

sint32 func_80066750(CODE_8006430C_WORK *wp)
{
    wp->active_0              = 0;
    *(uint32 *)&wp->routine_0 = 0;
    wp->routine_0             = 0; // the build needs this store after the word clear
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066764);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006689C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066D60);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066E48);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066F40);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067174);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006779C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067884);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_800679B8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067B7C);

void func_80067D10(void)
{
    D_8008FA84[0] = D_80098124[D_80098A04 + 1];
    D_8008FA84[9] = D_80098124[D_80098805];
    D_8008FA84[8] = D_80098124[D_80098804];
    D_8008FA84[6] = D_80098124[D_80098803];
    D_8008FA84[5] = D_80098124[D_80098802];
    D_8008FA84[3] = D_80098124[D_80098801];
    D_8008FA84[2] = D_80098124[D_80098800];
}

void func_80067E18(void)
{
    D_800BE428 = 0x3F00;
    D_800BE42C = 0x18;
    D_800BE430 = 0x80;
    D_800BE434 = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067E4C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067E6C);
