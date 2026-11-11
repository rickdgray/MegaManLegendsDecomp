#include "common.h"

// Small uninitialized statics (.sbss 0x80098198-0x800981A0).
static uint8 D_80098198[8];

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D854);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D878);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D888);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D8C0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D928);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D974);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001D990);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", Sce_flag_test);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", Sce_flag_on);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", Sce_flag_off);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DD88);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DDC0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DDE4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DE84);

void func_8001DEDC(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DEE4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DF10);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001DFEC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E068);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E20C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E390);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E3F0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E460);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E4C4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E550);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E6C0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E7E4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E810);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E83C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001E968);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001EAE8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001EB98);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001EC0C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F070);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F158);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F1DC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F20C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F23C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F3C8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F580);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F5E4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F6C4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F740);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/scene", func_8001F798);

void func_8001F820(void)
{
}

INCLUDE_RODATA("asm/rock_neo.exe/nonmatchings/scene", D_800102B0);

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_80098199\n.set D_80098199, D_80098198+1\n");
