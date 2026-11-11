#include "common.h"

// Small data (.sdata 0x80097864-0x800979DC): reached through $gp in this file. The strings
// are the exception handler's (names, then the register dump's labels and formats).
sint32 D_80097864[6] = {0, 0, 0, 0, 0, 0x02000400};
char D_8009787C[]    = "INT";
char D_80097880[]    = "MOD";
char D_80097884[]    = "TLBL";
char D_8009788C[]    = "TLBS";
char D_80097894[]    = "ADEL";
char D_8009789C[]    = "ADES";
char D_800978A4[]    = "IBE";
char D_800978A8[]    = "DBE";
char D_800978AC[]    = "SYS";
char D_800978B0[]    = "BP";
char D_800978B4[]    = "RI";
char D_800978B8[]    = "CPU";
char D_800978BC[]    = "OV";
char D_800978C0[]    = "\?1";
char D_800978C4[]    = "\?2";
char D_800978C8[]    = "\?3";
char D_800978CC[]    = "0x80000000 / -1";
char D_800978DC[]    = "0x\?\?\?\?\?\?\?\? / 0";
char D_800978EC[]    = "EXCEPTION=%s";
char D_800978FC[]    = "CAUS=";
char D_80097904[]    = "SR=";
char D_80097908[]    = "MDLO=";
char D_80097910[]    = "MDHI=";
char D_80097918[]    = "EPC=";
char D_80097920[]    = "RA=";
char D_80097924[]    = "FP=";
char D_80097928[]    = "SP=";
char D_8009792C[]    = "GP=";
char D_80097930[]    = "K1=";
char D_80097934[]    = "K0=";
char D_80097938[]    = "T9=";
char D_8009793C[]    = "T8=";
char D_80097940[]    = "S7=";
char D_80097944[]    = "S6=";
char D_80097948[]    = "S5=";
char D_8009794C[]    = "S4=";
char D_80097950[]    = "S3=";
char D_80097954[]    = "S2=";
char D_80097958[]    = "S1=";
char D_8009795C[]    = "S0=";
char D_80097960[]    = "T7=";
char D_80097964[]    = "T6=";
char D_80097968[]    = "T5=";
char D_8009796C[]    = "T4=";
char D_80097970[]    = "T3=";
char D_80097974[]    = "T2=";
char D_80097978[]    = "T1=";
char D_8009797C[]    = "T0=";
char D_80097980[]    = "A3=";
char D_80097984[]    = "A2=";
char D_80097988[]    = "A1=";
char D_8009798C[]    = "A0=";
char D_80097990[]    = "V1=";
char D_80097994[]    = "V0=";
char D_80097998[]    = "AT=";
char D_8009799C[]    = "ZERO=";
char D_800979A4[]    = "%08x";
char D_800979AC[]    = "%08x %08x %08x";
char D_800979BC[]    = "%08x %04x %04x %04x %04x";
sint32 D_800979D8    = 0;

// Small uninitialized statics (.sbss 0x80098158-0x80098160).
static sint32 D_80098158[2];

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", main);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80011F04);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_800120A8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", Disp_env_init);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", Pad_update);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", Pad_update_all);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_800122D0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012350);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", Vsync_handler);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012424);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_8001246C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012938);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012988);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012A5C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012BC4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012C80);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012E10);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", Thread_wait);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012ECC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012F24);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012F78);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012FA4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012FC8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012FEC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_800130D0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_8001319C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_800131FC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_8001326C);

// For the code and data still in assembly: statics that other files point to (made global).
// D_80098158 is also the start of the BSS, which 2MBYTE.OBJ's startup clears from.
__asm__(".text\n"
        ".globl D_80098158\n");
