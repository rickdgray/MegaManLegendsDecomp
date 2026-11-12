#include "common.h"
#include "player.h"
#include "code_80037FB4.h"
#include "scene.h"

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
uint32 D_80097D70 = 0;

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

void func_80038324(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39A0 = *arg0;
    func_80037FB4(arg0, arg1, arg2, arg3);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038370);

void func_800384A4(VECTOR *arg0, sint32 arg1)
{
    D_800A39A0 = *arg0;
    func_80038370(arg0, arg1);
}

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

void func_800395E8(void)
{
    D_800A396C = 0x30;
    D_800A3964 = 0x200;
    D_800A3962 = -1;
    D_800A3960 = 0;
    D_800A39B4 = 0x96;
    D_800A3959 = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039630);

void func_800397E8(void)
{
    D_800A396C         = 0x30;
    D_80097D2C         = 0x200;
    D_800A3964         = 0x200;
    D_800A3962         = -1;
    Player_work.unk44D = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039820);

void func_800398E0(sint32 arg0)
{
    if (arg0 > 0)
    {
        D_800A395F = arg0;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", Swing_Camera2);

sint32 func_800399EC(sint32 arg0)
{
    if (D_80097D70 >= 8)
    {
        return 0;
    }
    D_8009869C[(D_80097D6C + D_80097D70++) & 7] = arg0;
    return 1;
}

void func_80039A38(sint32 arg0)
{
    D_80097D6C = 0;
    D_80097D70 = 0;
    func_800399EC(arg0);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039A60);

sint32 func_80039B80(void)
{
    if (D_800A3960 == 0)
    {
        return 0;
    }
    return D_800A396C;
}

void func_80039BA4(sint32 arg0, sint32 arg1)
{
    D_800A395A = arg0;
    D_800A395B = arg1;
}

void func_80039BBC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39A0 = *arg0;
    D_800A3964 = arg1;
    D_800A3968 = arg2;
    D_800A396C = arg3;
}

void func_80039C08(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39D0 = *arg0;
    D_800A3988 = arg1;
    D_800A398C = arg2;
    D_800A3990 = arg3;
}

void func_80039C54(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39C0 = *arg0;
    D_800A397C = arg1;
    D_800A3980 = arg2;
    D_800A3984 = arg3;
}

void func_80039CA0(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39B0 = *arg0;
    D_800A3970 = arg1;
    D_800A3974 = arg2;
    D_800A3978 = arg3;
}

void func_80039CEC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39E0 = *arg0;
    D_800A3994 = arg1;
    D_800A3998 = arg2;
    D_800A399C = arg3;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039D38);

void func_80039DE8(void)
{
    D_80097D2C         = 0x200;
    Player_work.unk44D = 0;
    Scene_work.unk01   = D_80098674;
    Scene_work.unk00   = D_80098670;
}

void func_80039E18(void)
{
    Scene_work.unk01 = D_80098674;
    Scene_work.unk00 = D_80098670;
    func_80039E50();
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039E50);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039FAC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80039FFC);

sint32 func_8003A13C(void)
{
    return D_800A3962 >= 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A154);

// Shortest angular distance (mod 0x1000) from arg0 to D_800A3968.
// Remaining difference: GCC inverts the a < b test and swaps the branch bodies.
#ifdef NON_MATCHING
sint32 func_8003A218(sint32 arg0)
{
    sint32 a;
    sint32 b;
    sint32 d1;
    sint32 d2;
    sint32 t;

    a = arg0 & 0xFFF;
    b = D_800A3968 & 0xFFF;
    if (a < b)
    {
        d1 = b - a;
        t  = b - 0x1000;
        d2 = a - t;
    }
    else
    {
        d1 = a - b;
        t  = a - 0x1000;
        d2 = b - t;
    }
    if (d2 < d1)
    {
        return d2;
    }
    return d1;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A218);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A264);

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_80098662\n.set D_80098662, D_80098660+2\n");
