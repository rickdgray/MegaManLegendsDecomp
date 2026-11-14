#include "common.h"
#include "system.h"
#include "pad.h"
#include "display.h"

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

// Pool variable (0x800988D8): the event handle func_80012938 opens.
sint32 D_800988D8;

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", main);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80011F04);

void Disp_env_setup(void)
{
    SetDefDrawEnv(&Disp_env[0].draw, 0, 0, 320, 240);
    SetDefDispEnv(&Disp_env[0].disp, 0, 256, 320, 240);
    SetDefDrawEnv(&Disp_env[1].draw, 0, 256, 320, 240);
    SetDefDispEnv(&Disp_env[1].disp, 0, 0, 320, 240);
    Disp_env_init(&Disp_env[0]);
    Disp_env_init(&Disp_env[1]);
}

void Disp_env_init(DISP_ENV *buf)
{
    ClearOTagR(buf->ot, OT_LEN);
    buf->disp.screen.y = 0;
    buf->draw.dtd      = 0;
    buf->draw.dfe      = 0;
    buf->draw.isbg     = 1;
    buf->draw.r0       = 0;
    buf->draw.g0       = 0;
    buf->draw.b0       = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", Pad_update);

void Pad_update_all(void)
{
    Pad_update(&Joy1);
    Pad_update(&Joy2);
}

void Pad_repeat_update(PAD_REP *pad)
{
    func_80012350(pad, PAD_UP, 0);
    func_80012350(pad, PAD_DOWN, 1);
    func_80012350(pad, PAD_LEFT, 2);
    func_80012350(pad, PAD_RIGHT, 3);
    func_80012350(pad, PAD_L1, 4);
    func_80012350(pad, PAD_R1, 5);
}

void func_80012350(PAD_REP *pad, sint32 mask, sint32 i)
{
    if (!(PAD_REP_OUT(pad) & mask) && (PAD_ON(pad->pad) & mask) == mask)
    {
        pad->rep_count[i] = 0;
        if (pad->rep_state[i] == 0)
        {
            pad->rep_state[i] = 1;
        }
        else
        {
            pad->rep_state[i] = 2;
            PAD_REP_OUT(pad) |= mask;
        }
    }
    else if (pad->rep_state[i] != 0)
    {
        if (pad->rep_state[i] == 2 || pad->rep_count[i]++ >= 6)
        {
            pad->rep_state[i] = 0;
            PAD_REP_OUT(pad) &= ~mask;
        }
    }
}

void Vsync_handler(void)
{
    Vsync_count++;
}

void func_80012424(void)
{
    if ((PAD_NOW(Joy1) & (PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1)) == (PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1) && (PAD_NOW(Joy2) & PAD_CIRCLE))
    {
        D_80097864[0] ^= 1;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_8001246C);

void func_80012938(void)
{
    EnterCriticalSection();
    D_800988D8 = OpenEvent(0xF0000010, 0x1000, 0x1000, func_8001246C);
    EnableEvent(D_800988D8);
    ExitCriticalSection();
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012988);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012A5C);

// Best attempt: the table base and gp now match; the target reloads THREAD_TBL[i].tcb from memory
// before storing ->sr (mine reuses the register) and schedules the loop counter/giv differently.
#ifdef NON_MATCHING
void func_80012BC4(void)
{
    sint32 i;
    uint32 gp;
    TCB **kp;

    kp = (TCB **)0x100;
    gp = kp[4]->reg[28];
    for (i = 0; i < 4; i++)
    {
        THREAD_TBL[i].flags   = 0;
        THREAD_TBL[i].sp      = 0x801FEC00 + i * 0x400;
        THREAD_TBL[i].gp      = gp;
        THREAD_TBL[i].tcb     = &kp[4][i + 1];
        THREAD_TBL[i].tcb->sr = 0x40000404;
        THREAD_TBL[i].unk70   = 0;
    }
    for (i = 0; i < 9; i++)
    {
        ((uint32 *)0x801F8000)[i] = ((uint32 *)0x80080870)[i];
    }
    Thread_current = THREAD_TBL;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012BC4);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012C80);

void Thread_open(sint32 n, TH_FUNC func)
{
    EnterCriticalSection();
    THREAD_TBL[n].th = OpenTh(func, THREAD_TBL[n].sp, THREAD_TBL[n].gp);
    ExitCriticalSection();
    THREAD_TBL[n].flags = 2;
}

void Thread_wait(sint32 arg)
{
    Thread_current->wait  = arg;
    Thread_current->flags = 1;
    ChangeTh(0xFF000000);
}

void func_80012ECC(void)
{
    Thread_current->flags = 0;
    EnterCriticalSection();
    CloseTh(Thread_current->th);
    ExitCriticalSection();
    ChangeTh(0xFF000000);
}

void func_80012F24(sint32 n)
{
    THREAD_TBL[n].flags = 0;
    EnterCriticalSection();
    CloseTh(THREAD_TBL[n].th);
    ExitCriticalSection();
}

void func_80012F78(sint32 arg)
{
    D_80098158[0] = arg;
    D_800979D8    = 1;
    ChangeTh(0xFF000000);
}

void func_80012FA4(sint32 n)
{
    THREAD_TBL[n].flags |= THREAD_FLAG_40;
}

void func_80012FC8(sint32 n)
{
    THREAD_TBL[n].flags &= ~THREAD_FLAG_40;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_80012FEC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_800130D0);

void func_8001319C(void)
{
    sint32 i;

    for (i = 0; i < 8; i++)
    {
        Thread_current->unk60[i] = 0;
    }
    for (i = 0; i < 16; i++)
    {
        Thread_current->unk71[i] = 0;
    }
}

void func_800131FC(void)
{
    D_80098B1C = 0;
    D_80098B1D = 0;
    while (1)
    {
        D_80080894[D_80098B1C](&D_80098B1C);
        Thread_wait(1);
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", func_8001326C);

// For the code and data still in assembly: statics that other files point to (made global).
// D_80098158 is also the start of the BSS, which 2MBYTE.OBJ's startup clears from.
__asm__(".text\n"
        ".globl D_80098158\n");
