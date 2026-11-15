#include "common.h"
#include "code_8001786C.h"
#include "display.h"
#include "moji.h"
#include "scratch.h"

// Called only from this file
void func_800196A0(void);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_8001786C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800178FC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017944);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017994);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800179FC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017B24);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017C30);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017E94);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80017ED0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018050);

// Entry 0 of D_800821BC. Sub-step 0: once Dbl_buff_idx is 1, zeroes both buffers' vertical
// offsets and the clear/dither flags, stops all messages and moves on; sub-step 1 ends the step.
void func_800180D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (Dbl_buff_idx != 0)
            {
                Disp_env[0].draw.ofs[1] = 0;
                Disp_env[0].draw.clip.y = 0;
                Disp_env[0].disp.disp.y = 0;
                Disp_env[0].draw.isbg   = 0;
                Disp_env[0].draw.dfe    = 0;
                Disp_env[1].draw.ofs[1] = 0;
                Disp_env[1].draw.clip.y = 0;
                Disp_env[1].disp.disp.y = 0;
                Disp_env[1].draw.isbg   = 0;
                Disp_env[1].draw.dfe    = 0;
                MojiTaskKill();
                D_80098810 = 1;
                D_80098824 = 1;
                D_80098864 = 1;
                D_80098A6B++;
                func_800196A0();
            }
            break;
        case 1:
            D_80098A6B = 0;
            D_80098A6A++;
            break;
    }
}

// Same code as func_800180D4.
void func_800181D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (Dbl_buff_idx != 0)
            {
                Disp_env[0].draw.ofs[1] = 0;
                Disp_env[0].draw.clip.y = 0;
                Disp_env[0].disp.disp.y = 0;
                Disp_env[0].draw.isbg   = 0;
                Disp_env[0].draw.dfe    = 0;
                Disp_env[1].draw.ofs[1] = 0;
                Disp_env[1].draw.clip.y = 0;
                Disp_env[1].disp.disp.y = 0;
                Disp_env[1].draw.isbg   = 0;
                Disp_env[1].draw.dfe    = 0;
                MojiTaskKill();
                D_80098810 = 1;
                D_80098824 = 1;
                D_80098864 = 1;
                D_80098A6B++;
                func_800196A0();
            }
            break;
        case 1:
            D_80098A6B = 0;
            D_80098A6A++;
            break;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800182D4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_8001840C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018534);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018850);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80018BB8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80019210);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800194C4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_800196A0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8001786C", func_80019760);
