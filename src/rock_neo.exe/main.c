#include "common.h"
#include "system.h"
#include "pad.h"
#include "display.h"
#include "psyq/libetc.h"
#include "psyq/libsn.h"
#include "psyq/libgpu.h"
#include "cd.h"
#include "game.h"
#include "moji.h"
#include "scratch.h"
#include "debug.h"
#include "code_8001786C.h"
#include "code_8006430C.h"
#include "code_8001F828.h"
#include "fastmem.h"
#include "sound.h"
#include "psyq/libgte.h"

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

// Pool variable (0x80098A8C): set to 1 by System_init, read by main.
uint8 D_80098A8C;

// Pool variable (0x80098A90): DrawSync(1) at the start of the frame (main). volatile: without
// it, the store moves ahead of DrawSync(0)'s argument setup in main.
volatile sint32 D_80098A90;

// Called only from this file
void thread_dispatch(void);
void exception_handler(void);
void debug_addr_move(uint32 *addr);
void debug_mem_dump(uint8 *addr, uint32 mode);

void main(void)
{
    if (D_80097864[0] == 0)
    {
        func_80012938();
    }

    System_init();
    Thread_open(0, func_800131FC);

    while (1)
    {
        while (Vsync_count < Vsync_wait)
        {
        }

        Vsync_count = 0;
        D_800D9BCC = D_800D9BD0 = VSync(1);
        D_80098A90              = DrawSync(1);
        DrawSync(0);
        ResetGraph(1);

        if (D_80098A8C == 0)
        {
            PutDispEnv(&Disp_env_ptr->disp);
            PutDrawEnv(&Disp_env_ptr->draw);
        }

        func_80017734();

        if (D_80098810 == 0)
        {
            DrawOTag(&Disp_env_ptr->ot[OT_LEN - 1]);
        }

        Pad_update_all();

        Dbl_buff_idx ^= 1;
        Disp_env_ptr = &Disp_env[Dbl_buff_idx];
        Scratch_ot   = D_800A4D40[Dbl_buff_idx];
        ClearOTagR(Disp_env_ptr->ot, OT_LEN);
        ClearOTagR(D_800A4D40[Dbl_buff_idx], 0x1000);
        ClearOTagR(D_8009BF88[Dbl_buff_idx], 0x200);
        ClearOTagR(D_8009AE48[Dbl_buff_idx], 0x200);
        Map_prim_ptr = D_800806EC[D_80098864][Dbl_buff_idx];

        thread_dispatch();
        Sound_update();
        Cd_cmd_exec();
        func_800203A8();
        func_80053B40();
        func_80064060();
        DrawSync(0);
        func_80017B24();
        func_800178FC();

        if (D_80097864[0] != 0)
        {
            DEBUG_BREAK();
        }

        System_timer++;
    }
}

void System_init(void)
{
    sint32 i;

    ResetCallback();
    Cd_init();
    ResetGraph(3);
    D_80098A8C = 1;
    SetVideoMode(MODE_NTSC);
    InitGeom();
    SetGeomOffset(160, 120);
    SetGeomScreen(384);
    Mem_clear(&Joy1, (uint8 *)&Joy1 + 0x4C8);
    Mem_clear(&Joy2, (uint8 *)&Joy2 + 0x4C8);
    Mem_clear(D_800C0FC0, D_800C0FC0 + 0x4C8);
    InitPAD((char *)&Joy1, 8, (char *)&Joy2, 8);
    *(uint32 *)Joy1.unk34 = 0x4001;
    *(uint32 *)Joy2.unk34 = 0x4001;
    StartPAD();
    func_8006479C();
    Sound_init();
    ChangeClearPAD(0);
    Disp_env_setup();
    func_80012BC4();
    Disp_env_ptr = Disp_env;
    D_800D9B00   = 0;
    Dbl_buff_idx = 0;
    Vsync_wait   = VSYNC_30FPS;
    VSyncCallback(Vsync_handler);
    D_80098824 = 0;
    D_80098864 = 0;
    for (i = 0; i < 0x1000; i += 0x40)
    {
        D_800BAEB0[i >> 6] = rcos(i);
        D_800BBCF8[i >> 6] = rsin(i);
    }
    func_8002037C();
}

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

// The shim's Pad_update, plus the auto-repeat update.
void Pad_update(PAD_WORK *pad)
{
    if (pad->status == 0xFF)
    {
        pad->type                  = 0xFF;
        pad->flags.all             = 0;
        PAD_NOW(*pad)              = 0;
        *(uint32 *)pad->analog_cpy = 0;
        *(uint32 *)pad->old        = 0;
    }
    else
    {
        pad->type                  = pad->id >> 4;
        PAD_OLD(*pad)              = PAD_NOW(*pad);
        *(uint32 *)pad->analog_cpy = *(uint32 *)pad->analog;
        PAD_NOW(*pad)              = ~PAD_RAW(*pad);
        PAD_ON(*pad)               = PAD_NOW(*pad) & ~PAD_OLD(*pad);
        PAD_OFF(*pad)              = PAD_OLD(*pad) & ~PAD_NOW(*pad);
        Pad_repeat_update(pad);

        if ((pad->flags.all & 3) == 1)
        {
            pad->unk36 = 1;
        }

        if ((pad->flags.all & 3) == 2)
        {
            pad->unk36 = 0;
        }

        pad->flags.bit.prev = pad->flags.bit.cur;
    }
}

void Pad_update_all(void)
{
    Pad_update(&Joy1);
    Pad_update(&Joy2);
}

void Pad_repeat_update(PAD_WORK *pad)
{
    func_80012350(pad, PAD_UP, 0);
    func_80012350(pad, PAD_DOWN, 1);
    func_80012350(pad, PAD_LEFT, 2);
    func_80012350(pad, PAD_RIGHT, 3);
    func_80012350(pad, PAD_L1, 4);
    func_80012350(pad, PAD_R1, 5);
}

void func_80012350(PAD_WORK *pad, sint32 mask, sint32 i)
{
    if (!(PAD_REP_OUT(pad) & mask) && (PAD_ON(*pad) & mask) == mask)
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

// Exception handler: shows the exception's name, the faulting thread's registers and, with
// select on controller 2, a memory dump (triangle toggles main RAM / scratchpad). Never returns.
// Parked (3 instructions long): the target shares D_800979A4 in s0 across the last five prints
// (ours reloads it each time), and schedules the hoisted scratchpad base ahead of msg's.
#ifdef NON_MATCHING
void exception_handler(void)
{
    char *names[16] = {D_8009787C, D_80097880, D_80097884, D_8009788C, D_80097894, D_8009789C, D_800978A4, D_800978A8,
                       D_800978AC, D_800978B0, D_800978B4, D_800978B8, D_800978BC, D_800978C0, D_800978C4, D_800978C8};
    uint32 addr[2];
    TCB tcb;
    TCB *cur;
    DEBUG_TEXT *msg;
    uint32 cause;
    uint32 epc;
    uint32 n; // the break code, then the register column
    uint32 mode;
    uint32 sel;
    uint32 i;

    cur   = TCB_CURRENT;
    tcb   = *cur;
    cause = cur->reg[R_CAUSE];
    epc   = cur->reg[R_EPC];
    ExitCriticalSection();
    sel     = 0;
    addr[0] = 0x80000000;
    addr[1] = 0x1F800000;

    Disp_env[0].draw.ofs[1] = 0;
    Disp_env[0].draw.clip.y = 0;
    Disp_env[0].disp.disp.y = 256;
    Disp_env[0].draw.isbg   = 1;
    Disp_env[0].draw.dtd    = 0;
    Disp_env[0].draw.dfe    = 1;
    Disp_env[1].draw.ofs[1] = 256;
    Disp_env[1].draw.clip.y = 256;
    Disp_env[1].disp.disp.y = 0;
    Disp_env[1].draw.isbg   = 1;
    Disp_env[1].draw.dtd    = 0;
    Disp_env[1].draw.dfe    = 1;
    D_80098824              = 0;
    mode                    = 0;
    func_80020A40();
    msg = D_80080858;

    while (1)
    {
        VSync(0);
        PutDispEnv(&Disp_env_ptr->disp);
        PutDrawEnv(&Disp_env_ptr->draw);
        DrawOTag(&Disp_env_ptr->ot[OT_LEN - 1]);
        Pad_update_all();

        Dbl_buff_idx ^= 1;
        Disp_env_ptr = &Disp_env[Dbl_buff_idx];
        Scratch_ot   = D_800A4D40[Dbl_buff_idx];
        ClearOTagR(Disp_env_ptr->ot, OT_LEN);
        ClearOTagR(D_800A4D40[Dbl_buff_idx], 0x1000);
        Map_prim_ptr = (POLY_FT4 *)(0x801B8000 + (Dbl_buff_idx << 17));
        func_800203A8();

        D_800987D4 = 0;
        func_8001FE38(TEXT_POS(msg[0].x, msg[0].y, msg[0].unk2), msg[0].str, names[(cause >> 2) & 0xF]);

        if (PAD_ON(Joy2) & PAD_SELECT)
        {
            mode = (mode + 1) & 3;
        }

        if (PAD_ON(Joy2) & PAD_TRIANGLE)
        {
            sel ^= 1;
        }

        if (mode == 0)
        {
            if (((cause >> 2) & 0xF) == 9)
            {
                n = *(uint32 *)epc >> 6;
                switch (n)
                {
                    case 0x1C00:
                        func_8001FE38(TEXT_POS(msg[1].x, msg[1].y, msg[1].unk2), msg[1].str);
                        break;

                    case 0x1800:
                        func_8001FE38(TEXT_POS(msg[2].x, msg[2].y, msg[2].unk2), msg[2].str);
                        break;

                    default:
                        func_8001FE38(TEXT_POS(2, 3, 0), D_800979A4, n);
                        break;
                }
            }
            func_8001FE38(TEXT_POS(22, 2, 0), D_800979A4, epc);

            for (i = 0; i < 37; i++)
            {
                func_8001FE38(TEXT_POS(D_80080730[i].x, D_80080730[i].y, D_80080730[i].unk2), D_80080730[i].str);
            }

            for (i = 0, n = 0; i < 32; i++)
            {
                if (i >= 20)
                {
                    n = 1;
                }
                func_8001FE38(TEXT_POS(n * 20 + 7, i - n * 20 + 4, 0), D_800979A4, tcb.reg[i]);
            }

            i = (uint32)D_800979A4;
            func_8001FE38(TEXT_POS(27, 16, 0), (char *)i, tcb.reg[R_EPC]);
            func_8001FE38(TEXT_POS(27, 17, 0), (char *)i, tcb.reg[R_MDHI]);
            func_8001FE38(TEXT_POS(27, 18, 0), (char *)i, tcb.reg[R_MDLO]);
            func_8001FE38(TEXT_POS(27, 19, 0), (char *)i, tcb.reg[R_SR]);
            func_8001FE38(TEXT_POS(27, 20, 0), (char *)i, tcb.reg[R_CAUSE]);
        }
        else
        {
            debug_addr_move(&addr[sel]);
            debug_mem_dump((uint8 *)addr[sel], mode - 1);
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", exception_handler);
#endif

void func_80012938(void)
{
    EnterCriticalSection();
    D_800988D8 = OpenEvent(0xF0000010, 0x1000, 0x1000, exception_handler);
    EnableEvent(D_800988D8);
    ExitCriticalSection();
}

// Moves a debug address with controller 2 (up/down, by 8 lines; square, cross and circle pick
// the line size), keeping it inside main RAM or the scratchpad.
void debug_addr_move(uint32 *addr)
{
    uint32 old;
    sint32 step;

    old  = *addr;
    step = 1;
    if (PAD_NOW(Joy2) & PAD_SQUARE)
    {
        step = 0x10;
    }
    if (PAD_NOW(Joy2) & PAD_CROSS)
    {
        step = 0x100;
    }
    if (PAD_NOW(Joy2) & PAD_CIRCLE)
    {
        step = 0x1000;
    }
    if (PAD_NOW(Joy2) & PAD_UP)
    {
        *addr -= step * 8;
    }
    if (PAD_NOW(Joy2) & PAD_DOWN)
    {
        *addr += step * 8;
    }
    if (old >= 0x80000000)
    {
        if (*addr < 0x80000000)
        {
            *addr = old;
        }
        else if (*addr > 0x801FFF80)
        {
            *addr = old;
        }
    }
    else
    {
        if (*addr < 0x1F800000)
        {
            *addr = old;
        }
        else if (*addr > 0x1F800380)
        {
            *addr = old;
        }
    }
}

// Prints 16 lines of 8 bytes from addr, as words (mode 0), halfwords (1) or bytes (2).
// Parked: the code matches, but its format string lands ahead of D_80010000 in .rodata. GCC's
// MIPS port writes a file's data (string literals included) before all of its function bodies,
// and INCLUDE_ASM's .include sits inside a function body, so exception_handler.s's table always
// comes after this string. Bank this together with exception_handler: with both in C, the
// table is emitted first, as in the original.
#ifdef NON_MATCHING
void debug_mem_dump(uint8 *addr, uint32 mode)
{
    uint32 i;

    D_800987D4 = 0;
    switch (mode)
    {
        case 0:
            for (i = 0; i < 16; i++)
            {
                func_8001FE38(((i + 5) << 12) | 0x10, D_800979AC, &addr[i * 8], ((uint32 *)addr)[i * 2], ((uint32 *)addr)[i * 2 + 1]);
            }
            break;

        case 1:
            for (i = 0; i < 16; i++)
            {
                func_8001FE38(((i + 5) << 12) | 0x10, D_800979BC, &addr[i * 8], ((uint16 *)addr)[i * 4], ((uint16 *)addr)[i * 4 + 1],
                              ((uint16 *)addr)[i * 4 + 2], ((uint16 *)addr)[i * 4 + 3]);
            }
            break;

        case 2:
            for (i = 0; i < 16; i++)
            {
                func_8001FE38(((i + 5) << 12) | 0x10, "%08x %02x %02x %02x %02x %02x %02x %02x %02x", &addr[i * 8], addr[i * 8],
                              addr[i * 8 + 1], addr[i * 8 + 2], addr[i * 8 + 3], addr[i * 8 + 4], addr[i * 8 + 5], addr[i * 8 + 6],
                              addr[i * 8 + 7]);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/main", debug_mem_dump);
#endif

// Best attempt: the table base and gp now match; the target reloads THREAD_TBL[i].tcb from memory
// before storing reg[R_SR] (mine reuses the register) and schedules the loop counter/giv differently.
#ifdef NON_MATCHING
void func_80012BC4(void)
{
    sint32 i;
    uint32 gp;
    TCB **kp;

    kp = (TCB **)0x100;
    gp = kp[4]->reg[R_GP];
    for (i = 0; i < 4; i++)
    {
        THREAD_TBL[i].flags          = 0;
        THREAD_TBL[i].sp             = 0x801FEC00 + i * 0x400;
        THREAD_TBL[i].exec.gp        = gp;
        THREAD_TBL[i].tcb            = &kp[4][i + 1];
        THREAD_TBL[i].tcb->reg[R_SR] = 0x40000404;
        THREAD_TBL[i].unk70          = 0;
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

// Thread scheduler: one pass over the thread records, switching to each one that is ready.
void thread_dispatch(void)
{
    for (Thread_current = THREAD_TBL; Thread_current < &THREAD_TBL[4]; Thread_current++)
    {
        switch (Thread_current->flags)
        {
            case 1:
                if (--Thread_current->wait != 0)
                {
                    break;
                }
                // fall through
            case 2:
            case 4:
            case 0x7F:
                if (Thread_current->unk70)
                {
                    StopCallback();
                }
                Thread_current->flags = 0x7F;
                ChangeTh(Thread_current->th);
                if (Thread_current->unk70)
                {
                    ResetCallback();
                    VSyncCallback(Vsync_handler);
                    Thread_current->unk70 = 0;
                }
                if (D_800979D8)
                {
                    D_800979D8 = 0;
                    EnterCriticalSection();
                    CloseTh(Thread_current->th);
                    Thread_current->th = OpenTh((TH_FUNC)D_80098158[0], Thread_current->sp, Thread_current->exec.gp);
                    ExitCriticalSection();
                }
                break;
        }
    }
}

void Thread_open(sint32 n, TH_FUNC func)
{
    EnterCriticalSection();
    THREAD_TBL[n].th = OpenTh(func, THREAD_TBL[n].sp, THREAD_TBL[n].exec.gp);
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

// Loads a PS-X EXE from the host PC into thread n's record and opens the thread at its entry
// point (Thread_exec_file does the same for the current thread).
void Thread_open_file(sint32 n, char *name)
{
    char head[0x10];
    int fd;
    char *p;

    fd = PCopen(name, 0, 0);
    PCread(fd, head, sizeof(head));
    PCread(fd, (char *)&THREAD_TBL[n].exec, sizeof(EXEC));
    PCread(fd, (char *)THREAD_TBL[n].exec.t_addr, 0x800 - sizeof(head) - sizeof(EXEC));
    p = (char *)THREAD_TBL[n].exec.t_addr;
    while (PCread(fd, p, 0x800) == 0x800)
    {
        p += 0x800;
    }
    PCclose(fd);
    FlushCache();
    Thread_open(n, (TH_FUNC)THREAD_TBL[n].exec.pc0);
}

// Loads a PS-X EXE from the host PC: the exec info goes to the current thread's record, the
// text to its t_addr, and the thread then switches to its entry point.
void Thread_exec_file(char *name)
{
    char head[0x10];
    int fd;
    char *p;

    fd = PCopen(name, 0, 0);
    PCread(fd, head, sizeof(head));
    PCread(fd, (char *)&Thread_current->exec, sizeof(EXEC));
    PCread(fd, (char *)Thread_current->exec.t_addr, 0x800 - sizeof(head) - sizeof(EXEC));
    p = (char *)Thread_current->exec.t_addr;
    while (PCread(fd, p, 0x800) == 0x800)
    {
        p += 0x800;
    }
    PCclose(fd);
    FlushCache();
    func_80012F78(Thread_current->exec.pc0);
}

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

void func_8001326C(sint8 *routine)
{
    uint32 i;

    SetDispMask(1);
    for (i = 0; i < 2; i++)
    {
        setTile(&D_80098A28[i]);
        setSemiTrans(&D_80098A28[i], 1);
        setXY0(&D_80098A28[i], 0, 0);
        setWH(&D_80098A28[i], 320, 240);
        SetDrawMode(&D_80098A10[i], 0, 0, GetTPage(2, 2, 0, 0), NULL);
    }
    func_80063EF0();
    Moji_init();
    func_800665E8();
    Cd_read_comb(29);
    Game_work.unk05B    = 1;
    Scratch_scale_shift = 0;
    Game_work.unk010    = 0;
    Game_work.unk014    = 0;
    Game_work.unk018    = 0;
    Game_work.unk01A    = 0;
    Game_work.unk054    = 0;
    Game_work.unk055    = 0;
    Game_work.mono      = 0;
    Game_work.unk059    = 0;
    Game_work.file_070  = -1;
    Game_work.file_072  = -1;
    Game_work.file_074  = -1;
    Game_work.unk076    = -1;
    (*routine)++;
}

// For the code and data still in assembly: statics that other files point to (made global).
// D_80098158 is also the start of the BSS, which 2MBYTE.OBJ's startup clears from.
__asm__(".text\n"
        ".globl D_80098158\n");
