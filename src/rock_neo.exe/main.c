#include "common.h"
#include "display.h"
#include "thread.h"
#include "system.h"
#include "pad.h"
#include "debug.h"
#include "game.h"
#include "main.h"
#include "psyq/libapi.h"

// Small data reached through $gp
THREAD_FUNC D_80098158;
sint32 D_800979D8;
sint32 D_80097864;
long D_800988D8;
uint8 D_80098A8C;
volatile sint32 D_80098A90;

void main(void)
{
    if (D_80097864 == 0)
    {
        func_80012938();
    }
    func_80011F04();
    func_80012E10(0, func_800131FC);
    while (1)
    {
        while (Vsync_count < SCRATCH_VSYNC_WAIT)
        {
            VSYNC_IDLE();
        }
        Vsync_count = 0;
        D_800D9BCC = D_800D9BD0 = VSync(1);
        D_80098A90              = DrawSync(1);
        DrawSync(0);
        ResetGraph(1);
        if (D_80098A8C == 0)
        {
            PutDispEnv(&CURRENT_DISP_ENV->disp);
            PutDrawEnv(&CURRENT_DISP_ENV->draw);
        }
        func_80017734();
        if (D_80098810 == 0)
        {
            DrawOTag(&CURRENT_DISP_ENV->ot[OT_LEN - 1]);
        }
        Pad_update_all();
        SCRATCH_BUFFER_INDEX ^= 1;
        D_80098934       = (CODE800133D8_LINK *)&Joy1.disp_env[SCRATCH_BUFFER_INDEX];
        SCRATCH_PRIM_PTR = D_800A4D40[SCRATCH_BUFFER_INDEX];
        ClearOTagR(CURRENT_DISP_ENV->ot, OT_LEN);
        ClearOTagR((u_long *)D_800A4D40[SCRATCH_BUFFER_INDEX], 0x1000);
        ClearOTagR(D_8009BF88[SCRATCH_BUFFER_INDEX], 0x200);
        ClearOTagR(D_8009AE48[SCRATCH_BUFFER_INDEX], 0x200);
        SCRATCH_SCREEN_WORD = D_800806EC[D_80098864][SCRATCH_BUFFER_INDEX];
        func_80012C80();
        func_8001A110();
        func_8001C95C();
        func_800203A8();
        func_80053B40();
        func_80064060();
        DrawSync(0);
        func_80017B24();
        func_800178FC();
        if (D_80097864 != 0)
        {
            __asm__ volatile("break 0x400");
        }
        SCRATCH_FRAME_COUNT++;
    }
}

void func_80011F04(void)
{
    sint32 angle;

    ResetCallback();
    Cd_init();
    ResetGraph(3);
    D_80098A8C = 1;
    func_80077748(0);
    InitGeom();
    func_8007B118(0xA0, 0x78);
    func_8007B138(0x180);
    func_800177CC(&Joy1, (uint8 *)&Joy1 + 0x4C8);
    func_800177CC(&Joy2, (uint8 *)&Joy2 + 0x4C8);
    func_800177CC(D_800C0FC0, D_800C0FC0 + 0x4C8);
    InitPAD(&Joy1.status, 8, &Joy2.status, 8);
    *(uint32 *)Joy1.unk34 = 0x4001;
    *(uint32 *)Joy2.unk34 = 0x4001;
    StartPAD();
    func_8006479C();
    func_80019DE0();
    ChangeClearPAD(0);
    func_800120A8();
    func_80012BC4();
    D_80098934           = (CODE800133D8_LINK *)D_800C0C48;
    D_800D9B00           = 0;
    SCRATCH_BUFFER_INDEX = 0;
    SCRATCH_VSYNC_WAIT   = 2;
    VSyncCallback(Vsync_handler);
    D_80098824 = 0;
    D_80098864 = 0;
    for (angle = 0; angle < 0x1000; angle += 0x40)
    {
        D_800BAEB0[angle >> 6] = rcos(angle);
        D_800BBCF8[angle >> 6] = rsin(angle);
    }
    func_8002037C();
}

void func_800120A8(void)
{
    SetDefDrawEnv(&Joy1.disp_env[0].draw, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    SetDefDispEnv(&Joy1.disp_env[0].disp, 0, DISPLAY_BUFFER_Y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    SetDefDrawEnv(&Joy1.disp_env[1].draw, 0, DISPLAY_BUFFER_Y, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    SetDefDispEnv(&Joy1.disp_env[1].disp, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    Disp_env_init(&Joy1.disp_env[0]);
    Disp_env_init(&Joy1.disp_env[1]);
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

void Pad_update(PAD_WORK *pad)
{
    uint32 repeat_flag;

    if (pad->status == 0xFF)
    {
        pad->type                 = 0xFF;
        pad->flags                = 0;
        pad->held                 = 0;
        pad->analog_copy          = 0;
        *(uint32 *)&pad->previous = 0;
    }
    else
    {
        pad->type        = pad->id >> 4;
        pad->previous    = pad->held;
        pad->analog_copy = pad->analog;
        pad->held        = ~pad->buttons;
        pad->pressed     = pad->held & ~pad->previous;
        pad->released    = pad->previous & ~pad->held;
        func_800122D0(pad);
        if ((pad->flags & 3) == 1)
        {
            pad->unk36 = 1;
        }
        if ((pad->flags & 3) == 2)
        {
            pad->unk36 = 0;
        }
        repeat_flag = (pad->flags & 1) << 1;
        pad->flags  = (pad->flags & ~2) | repeat_flag;
    }
}

void Pad_update_all(void)
{
    Pad_update(&Joy1);
    Pad_update(&Joy2);
}

void func_800122D0(PAD_WORK *pad)
{
    func_80012350(pad, PAD_UP, 0);
    func_80012350(pad, PAD_DOWN, 1);
    func_80012350(pad, PAD_LEFT, 2);
    func_80012350(pad, PAD_RIGHT, 3);
    func_80012350(pad, PAD_L1, 4);
    func_80012350(pad, PAD_R1, 5);
}

void func_80012350(PAD_WORK *pad, sint32 mask, sint32 index)
{
    if (!(pad->repeat & mask) && (pad->pressed & mask) == mask)
    {
        pad->repeat_count[index] = 0;
        if (pad->repeat_state[index] == 0)
        {
            pad->repeat_state[index] = 1;
        }
        else
        {
            pad->repeat_state[index] = 2;
            pad->repeat |= mask;
        }
    }
    else if (pad->repeat_state[index] != 0)
    {
        if (pad->repeat_state[index] == 2 || pad->repeat_count[index]++ >= PAD_REPEAT_DELAY)
        {
            pad->repeat_state[index] = 0;
            pad->repeat &= ~mask;
        }
    }
}

void Vsync_handler(void)
{
    Vsync_count++;
}

void func_80012424(void)
{
    if ((D_800C0C26 & 0xF00) == 0xF00 && (D_800C0D8E[0] & 0x2000))
    {
        D_80097864 ^= 1;
    }
}

// Exception handler: a register and memory viewer that never returns.
// The exception code is written out at each use: loop.c then hoists its shift and mask out of
// the outer loop, and those two extra moves lower its threshold enough that the D_800979A4
// address of the last five calls stays inside the loop (in s0) as in retail.
long func_8001246C(void)
{
    char *names[16] = {
        D_8009787C, D_80097880, D_80097884, D_8009788C, D_80097894, D_8009789C,
        D_800978A4, D_800978A8, D_800978AC, D_800978B0, D_800978B4, D_800978B8,
        D_800978BC, D_800978C0, D_800978C4, D_800978C8,
    };
    uint32 bank[2];
    TCB tcb;
    TCB *cur;
    uint32 cause;
    uint32 *epc;
    uint32 brk;
    uint32 sel;
    uint32 page;
    uint32 i;

    cur   = BIOS_PROCESS_TABLE->entry;
    tcb   = *cur;
    cause = cur->reg[TCB_R_CAUSE];
    epc   = (uint32 *)cur->reg[TCB_R_EPC];
    func_8007FF80();
    sel                       = 0;
    bank[0]                   = 0x80000000;
    bank[1]                   = 0x1F800000;
    D_800C0C48[0].draw.ofs[1] = 0;
    D_800C0C48[0].draw.clip.y = 0;
    D_800C0C48[0].disp.disp.y = 0x100;
    D_800C0C48[0].draw.isbg   = 1;
    D_800C0C48[0].draw.dtd    = 0;
    D_800C0C48[0].draw.dfe    = 1;
    D_800C0C48[1].draw.ofs[1] = 0x100;
    D_800C0C48[1].draw.clip.y = 0x100;
    D_800C0C48[1].disp.disp.y = 0;
    D_800C0C48[1].draw.isbg   = 1;
    D_800C0C48[1].draw.dtd    = 0;
    D_800C0C48[1].draw.dfe    = 1;
    D_80098824                = 0;
    page                      = 0;
    func_80020A40();
    while (1)
    {
        VSync(0);
        PutDispEnv(&CURRENT_DISP_ENV->disp);
        PutDrawEnv(&CURRENT_DISP_ENV->draw);
        DrawOTag(&CURRENT_DISP_ENV->ot[OT_LEN - 1]);
        Pad_update_all();
        SCRATCH_BUFFER_INDEX ^= 1;
        D_80098934       = (CODE800133D8_LINK *)&D_800C0C48[SCRATCH_BUFFER_INDEX];
        SCRATCH_PRIM_PTR = D_800A4D40[SCRATCH_BUFFER_INDEX];
        ClearOTagR(CURRENT_DISP_ENV->ot, OT_LEN);
        ClearOTagR((u_long *)D_800A4D40[SCRATCH_BUFFER_INDEX], 0x1000);
        SCRATCH_SCREEN_WORD = (SCRATCH_BUFFER_INDEX << 17) + 0x801B8000;
        func_800203A8();
        D_800987D4 = 0;
        func_8001FE38(DEBUG_TEXT_POS(D_80080858[0].x, D_80080858[0].y, D_80080858[0].color),
                      D_80080858[0].text, names[(cause >> 2) & 0xF]);
        if (Joy2.pressed & 1)
        {
            page = (page + 1) & 3;
        }
        if (Joy2.pressed & 0x1000)
        {
            sel ^= 1;
        }
        if (page == 0)
        {
            if (((cause >> 2) & 0xF) == EXC_BREAK)
            {
                brk = *epc >> 6;
                switch (brk)
                {
                    case 0x1C00:
                        func_8001FE38(
                            DEBUG_TEXT_POS(D_80080858[1].x, D_80080858[1].y, D_80080858[1].color),
                            D_80080858[1].text);
                        break;
                    case 0x1800:
                        func_8001FE38(
                            DEBUG_TEXT_POS(D_80080858[2].x, D_80080858[2].y, D_80080858[2].color),
                            D_80080858[2].text);
                        break;
                    default:
                        func_8001FE38(DEBUG_TEXT_POS(2, 3, 0), D_800979A4, brk);
                        break;
                }
            }
            func_8001FE38(DEBUG_TEXT_POS(22, 2, 0), D_800979A4, epc);
            for (i = 0; i < 37; i++)
            {
                func_8001FE38(DEBUG_TEXT_POS(D_80080730[i].x, D_80080730[i].y, D_80080730[i].color),
                              D_80080730[i].text);
            }
            for (i = 0, brk = 0; i < 32; i++)
            {
                if (i >= 20)
                {
                    brk = 1;
                }
                func_8001FE38(DEBUG_TEXT_POS(brk * 20 + 7, i - brk * 20 + 4, 0), D_800979A4,
                              tcb.reg[i]);
            }
            func_8001FE38(DEBUG_TEXT_POS(27, 16, 0), D_800979A4, tcb.reg[TCB_R_EPC]);
            func_8001FE38(DEBUG_TEXT_POS(27, 17, 0), D_800979A4, tcb.reg[TCB_R_MDHI]);
            func_8001FE38(DEBUG_TEXT_POS(27, 18, 0), D_800979A4, tcb.reg[TCB_R_MDLO]);
            func_8001FE38(DEBUG_TEXT_POS(27, 19, 0), D_800979A4, tcb.reg[TCB_R_SR]);
            func_8001FE38(DEBUG_TEXT_POS(27, 20, 0), D_800979A4, tcb.reg[TCB_R_CAUSE]);
        }
        else
        {
            func_80012988(&bank[sel]);
            func_80012A5C((DEBUG_MEMORY_ROW *)bank[sel], page - 1);
        }
    }
}

void func_80012938(void)
{
    func_8007FF70();
    D_800988D8 = OpenEvent(SYSTEM_EVENT_CLASS, EvSpTRAP, EvMdINTR, func_8001246C);
    EnableEvent(D_800988D8);
    func_8007FF80();
}

void func_80012988(uint32 *value)
{
    sint32 original;
    sint32 step;
    uint32 limit;
    uint32 current;
    uint16 *buttons;
    RECT rect; // Retail reserves eight bytes of unused local storage.

    buttons  = D_800C0D8E;
    original = *value;
    step     = 1;
    if (*buttons & 0x8000)
    {
        step = 0x10;
    }
    if (*buttons & 0x4000)
    {
        step = 0x100;
    }
    if (*buttons & 0x2000)
    {
        step = 0x1000;
    }
    if (*buttons & PAD_UP)
    {
        *value = original - step * 8;
    }
    if (*buttons & PAD_DOWN)
    {
        *value += step * 8;
    }
    limit = 0x7FFFFFFF;
    if (original < 0)
    {
        current = *value;
        if (current <= limit)
        {
            *value = original;
            return;
        }
        limit = 0x801FFF80;
    }
    else
    {
        limit   = 0x1F7FFFFF;
        current = *value;
        if (current <= limit)
        {
            *value = original;
            return;
        }
        limit = 0x1F800380;
    }
    if (current > limit)
    {
        *value = original;
    }
}

void func_80012A5C(DEBUG_MEMORY_ROW *rows, uint32 mode)
{
    uint32 i;
    DEBUG_MEMORY_ROW *row;

    D_800987D4 = 0;
    switch (mode)
    {
        case 0:
            for (i = 0; i < DEBUG_MEMORY_ROWS; i++)
            {
                row = &rows[i];
                func_8001FE38((DEBUG_MEMORY_BASE + i * DEBUG_MEMORY_SLOT_STEP) | DEBUG_MEMORY_FLAGS,
                              D_800979AC, row, row->words[0], row->words[1]);
            }
            break;
        case 1:
            for (i = 0; i < DEBUG_MEMORY_ROWS; i++)
            {
                row = &rows[i];
                func_8001FE38((DEBUG_MEMORY_BASE + i * DEBUG_MEMORY_SLOT_STEP) | DEBUG_MEMORY_FLAGS,
                              D_800979BC, row, row->halves[0], row->halves[1], row->halves[2],
                              row->halves[3]);
            }
            break;
        case 2:
            for (i = 0; i < DEBUG_MEMORY_ROWS; i++)
            {
                row = &rows[i];
                func_8001FE38((DEBUG_MEMORY_BASE + i * DEBUG_MEMORY_SLOT_STEP) | DEBUG_MEMORY_FLAGS,
                              D_80010040, row, row->bytes[0], row->bytes[1], row->bytes[2],
                              row->bytes[3], row->bytes[4], row->bytes[5], row->bytes[6],
                              row->bytes[7]);
            }
            break;
    }
}

// The context store comes before the stack and gp stores: those struct stores make CSE forget the
// stored context, so it is reloaded for the sr store as in retail.
void func_80012BC4(void)
{
    sint32 i;
    uint32 gp;
    KERNEL_TABLE *kernel;
    THREAD_FUNC *vec;

    kernel = KERNEL_TABLE_PTR;
    gp     = kernel->threads[0].gp;
    for (i = 0; i < THREAD_SLOT_COUNT; i++)
    {
        THREAD_WORK_TABLE[i].state       = 0;
        THREAD_WORK_TABLE[i].context     = &kernel->threads[i + 1];
        THREAD_WORK_TABLE[i].stack       = THREAD_STACK_BASE + i * THREAD_STACK_SIZE;
        THREAD_WORK_TABLE[i].gp          = gp;
        THREAD_WORK_TABLE[i].context->sr = THREAD_INITIAL_SR;
        THREAD_WORK_TABLE[i].unk70       = 0;
    }
    vec = THREAD_VECTOR_TABLE;
    for (i = 0; i < THREAD_VECTOR_COUNT; i++)
    {
        *vec++ = D_80080870[i];
    }
    Thread_current = THREAD_WORK_TABLE;
}

void func_80012C80(void)
{
    Thread_current = THREAD_WORK_TABLE;
    do
    {
        switch (Thread_current->state)
        {
            case THREAD_WAITING:
                if (--*(sint16 *)&Thread_current->wait != 0) // signed countdown
                {
                    break;
                }
                // fall through
            case THREAD_READY:
            case 4:
            case THREAD_RUNNING:
                if ((*THREAD_CURRENT_PTR)->unk70)
                {
                    StopCallback();
                }
                (*THREAD_CURRENT_PTR)->state = THREAD_RUNNING;
                ChangeTh((*THREAD_CURRENT_PTR)->handle);
                if ((*THREAD_CURRENT_PTR)->unk70)
                {
                    ResetCallback();
                    VSyncCallback(Vsync_handler);
                    (*THREAD_CURRENT_PTR)->unk70 = 0;
                }
                if (D_800979D8)
                {
                    D_800979D8 = 0;
                    func_8007FF70();
                    CloseTh((*THREAD_CURRENT_PTR)->handle);
                    (*THREAD_CURRENT_PTR)->handle =
                        OpenTh(D_80098158, (*THREAD_CURRENT_PTR)->stack, (*THREAD_CURRENT_PTR)->gp);
                    func_8007FF80();
                }
                break;
        }
    } while (++*THREAD_CURRENT_PTR < &THREAD_WORK_TABLE[THREAD_SLOT_COUNT]);
}

void func_80012E10(sint32 index, THREAD_FUNC entry)
{
    THREAD_WORK *thread;

    func_8007FF70();
    thread = &THREAD_WORK_TABLE[index];
    THREAD_WORK_TABLE[index].handle =
        OpenTh(entry, THREAD_WORK_TABLE[index].stack, THREAD_WORK_TABLE[index].gp);
    func_8007FF80();
    thread->state = THREAD_READY;
}

void Thread_wait(sint32 arg)
{
    Thread_current->wait  = arg;
    Thread_current->state = THREAD_WAITING;
    ChangeTh(THREAD_MAIN_HANDLE);
}

void func_80012ECC(void)
{
    (*THREAD_CURRENT_PTR)->state = 0;
    func_8007FF70();
    CloseTh((*THREAD_CURRENT_PTR)->handle);
    func_8007FF80();
    ChangeTh(THREAD_MAIN_HANDLE);
}

void func_80012F24(sint32 index)
{
    THREAD_WORK_TABLE[index].state = 0;
    func_8007FF70();
    CloseTh(THREAD_WORK_TABLE[index].handle);
    func_8007FF80();
}

void func_80012F78(THREAD_FUNC entry)
{
    D_80098158 = entry;
    D_800979D8 = 1;
    ChangeTh(THREAD_MAIN_HANDLE);
}

void func_80012FA4(sint32 index)
{
    THREAD_WORK_TABLE[index].state |= THREAD_FLAG_SUSPENDED;
}

void func_80012FC8(sint32 index)
{
    THREAD_WORK_TABLE[index].state &= ~THREAD_FLAG_SUSPENDED;
}

void func_80012FEC(sint32 index, char *name)
{
    uint8 header[THREAD_FILE_HEADER_SIZE];
    sint32 handle;
    sint32 size;
    uint8 *dest;

    handle = PCopen(name, 0, 0);
    PCread(handle, header, THREAD_FILE_HEADER_SIZE);
    PCread(handle, &THREAD_WORK_TABLE[index].entry, THREAD_FILE_WORK_SIZE);
    PCread(handle, THREAD_WORK_TABLE[index].load_addr, THREAD_FILE_PREFIX_SIZE);
    dest = THREAD_WORK_TABLE[index].load_addr;
    do
    {
        size = PCread(handle, dest, THREAD_FILE_CHUNK_SIZE);
        dest += THREAD_FILE_CHUNK_SIZE;
    } while (size == THREAD_FILE_CHUNK_SIZE);
    func_8007699C(handle);
    FlushCache();
    func_80012E10(index, THREAD_WORK_TABLE[index].entry);
}

void func_800130D0(char *name)
{
    uint8 header[THREAD_FILE_HEADER_SIZE];
    sint32 handle;
    sint32 size;
    uint8 *dest;

    handle = PCopen(name, 0, 0);
    PCread(handle, header, THREAD_FILE_HEADER_SIZE);
    PCread(handle, &(*THREAD_CURRENT_PTR)->entry, THREAD_FILE_WORK_SIZE);
    PCread(handle, (*THREAD_CURRENT_PTR)->load_addr, THREAD_FILE_PREFIX_SIZE);
    dest = (*THREAD_CURRENT_PTR)->load_addr;
    do
    {
        size = PCread(handle, dest, THREAD_FILE_CHUNK_SIZE);
        dest += THREAD_FILE_CHUNK_SIZE;
    } while (size == THREAD_FILE_CHUNK_SIZE);
    func_8007699C(handle);
    FlushCache();
    func_80012F78(Thread_current->entry);
}

void func_8001319C(void)
{
    sint32 i;

    for (i = 0; i < 8; i++)
    {
        (*THREAD_CURRENT_PTR)->unk60[i] = 0;
    }
    for (i = 0; i < 16; i++)
    {
        (*THREAD_CURRENT_PTR)->unk71[i] = 0;
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

void func_8001326C(sint8 *state)
{
    uint32 i;
    CODE178_TILE *tile;

    SetDispMask(1);
    for (i = 0; i < 2; i++)
    {
        // Naming the table twice lets loop.c hoist its address and walk one tile pointer.
        setlen(&D_80098A28[i], 3);
        setcode(&D_80098A28[i], 0x62);
        tile    = &D_80098A28[i];
        tile->w = 320;
        tile->x = 0;
        tile->y = 0;
        tile->h = 240;
        SetDrawMode(&D_80098A10[i], 0, 0, GetTPage(2, 2, 0, 0), NULL);
    }
    func_80063EF0();
    func_80053788();
    func_800665E8();
    Cd_read_comb(0x1D);
    Game_work.option_5b  = 1;
    *(uint8 *)0x1F800074 = 0;
    Game_work.value10    = 0;
    Game_work.value14    = 0;
    Game_work.flags_18   = 0;
    Game_work.flags_1a   = 0;
    Game_work.flags_54   = 0;
    Game_work.flags_55   = 0;
    Game_work.flags_58   = 0;
    Game_work.flags_59   = 0;
    Game_work.value70[0] = -1;
    Game_work.value70[1] = -1;
    Game_work.value70[2] = -1;
    Game_work.value70[3] = -1;
    (*state)++;
}
