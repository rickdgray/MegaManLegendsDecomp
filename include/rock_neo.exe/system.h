#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"

// The kernel's system tables (PsyQ's ToT) start at 0x100, 8 bytes each: 0x108 points to the TCB
// header (TCBH), 0x110 to the TCB table.
#define TCB_TBL (((TCB **)0x100)[4])
// The running thread's TCB.
#define TCB_CURRENT (((TCBH **)0x100)[2]->entry)

// A label of the exception screen: text position for Print (see TEXT_POS) and string.
typedef struct
{
    uint8 x;    // 0x00
    uint8 y;    // 0x01
    uint8 unk2; // 0x02 position bits from bit 17
    uint8 pad3; // 0x03
    char *str;  // 0x04
} DEBUG_TEXT;   // 0x08

// Thread records live at 0x801F8100, 0x80 bytes apart (see notes/rock_neo.md, "Threads").
typedef struct
{
    uint16 flags;      // 0x00 Thread_wait stores 1 here; func_80012FA4/func_80012FC8 set/clear THREAD_FLAG_40
    sint16 wait;       // 0x02 Thread_wait's argument: frames to sleep (thread_dispatch counts it down)
    uint8 unk04[4];    // 0x04
    uint32 th;         // 0x08 BIOS thread handle, closed by func_80012ECC/func_80012F24
    TCB *tcb;          // 0x0C this thread's BIOS TCB (thread_init)
    uint32 sp;         // 0x10 initial stack pointer for OpenTh (stacks 0x400 apart from 0x801FEC00)
    EXEC exec;         // 0x14 exec info of a PS-X EXE loaded by Thread_exec_file; exec.gp (0x44) is the
                       //      initial gp for OpenTh (copied from TCB 0)
    uint8 unk50[0x10]; // 0x50
    uint16 unk60[8];   // 0x60 zeroed by func_8001319C
    uint8 unk70;       // 0x70
    uint8 unk71[15];   // 0x71 func_8001319C zeroes 16 bytes from here (the last is the next record's flags)
} THREAD_WORK;         // 0x80

typedef void (*TASK_FUNC)(sint8 *routine);

// An entry of the thread functions' table (Thread_api_tbl: Thread_open ... Thread_exec_file). The
// entries take different arguments; the table is only copied, never called through, here.
typedef void (*THREAD_API_FUNC)(void);

#define THREAD_FLAG_40 0x0040

#define THREAD_MAX        4          // thread records
#define THREAD_STACK_BASE 0x801FEC00 // record 0's initial sp
#define THREAD_STACK_SIZE 0x400      // stacks are this far apart
#define THREAD_INITIAL_SR 0x40000404 // SR in each record's TCB: CU2 (GTE), IM2 and IEp set
#define THREAD_API_MAX    9          // entries of Thread_api_tbl

// Literal addresses, not symbols: the target builds them with lui/ori (`li`), which only a
// constant gives (a symbol gives lui %hi / %lo). Thread_current is also in symbol_addrs
// (absolute) for the code still in assembly.
#define THREAD_TBL     ((THREAD_WORK *)0x801F8100)
#define Thread_current (*(THREAD_WORK **)0x801F8300) // the running thread's record
// thread_init's copy of Thread_api_tbl, at a fixed address for code loaded from outside.
#define Thread_api_copy ((THREAD_API_FUNC *)0x801F8000)

extern THREAD_API_FUNC Thread_api_tbl[THREAD_API_MAX]; // the thread functions (Thread_open ... Thread_exec_file)

extern DEBUG_TEXT D_80080730[37]; // exception screen: register names ("ZERO=" ... "CAUS=")
// D_80080858 has 3 entries; declared without a size: a known size of 32 bytes or less makes
// GCC treat the address as cheap ($gp) small data, and exception_handler stops keeping it in a
// register.
extern DEBUG_TEXT D_80080858[]; // exception screen: "EXCEPTION=%s", then the break 7 and break 6 notes
extern TASK_FUNC D_80080894[];  // task dispatch table, indexed by D_80098B1C
extern sint8 D_80098B1C;
extern sint8 D_80098B1D;
// Filled by System_init: rcos and rsin of every 64th angle (0-0xFC0), 64 entries each.
// Read by code_8001F828 and code_80027678; owner unknown.
extern sint16 D_800BAEB0[64]; // cosines
extern sint16 D_800BBCF8[64]; // sines
extern uint8 D_800C0FC0[];    // cleared by System_init (0x4C8 bytes past it), after Joy1 and Joy2

// Per-frame buffers, one per double buffer (Dbl_buff_idx), cleared by main each frame.
extern u_long D_800A4D40[2][0x1000]; // the frame's ordering table (main points Scratch_ot at it)
extern u_long D_8009BF88[2][0x200];  // ordering tables
extern u_long D_8009AE48[2][0x200];  // ordering tables
// Primitive buffer starts (in the stage area), a pair per mode (D_80098864); main sets
// Map_prim_ptr to the current buffer's.
extern POLY_FT4 *D_800806EC[3][2];
extern sint32 D_800D9BCC; // VSync(1) at the start of the frame (main)
extern sint32 D_800D9BD0; // VSync(1) at the start of the frame (main)
extern sint32 D_800D9BD8; // VSync(1) when Room_model_update starts
// Obj_draw_all times each draw pass: VSync(1) at the start of the pass (a literal: the target
// builds it with lui/ori), then the pass's length in VSync(1) counts.
#define D_800D9BE4 (*(sint32 *)0x800D9BE4)
extern sint32 D_800D9BE8; // billboard_queue_draw
extern sint32 D_800D9BEC; // shadow_draw_all
extern sint32 D_800D9BF0; // shl_work_draw
extern sint32 D_800D9BF4; // work_48_draw
extern sint32 D_800D9BF8; // work_50_draw
extern sint32 D_800D9BFC; // Model_draw_all's D_800C3580 pass
extern sint32 D_800D9C00; // Model_draw_all's D_8009F108 pass

void System_init(void);
void Thread_wait(sint32 arg);
void Vsync_handler(void);
void func_80012F78(TH_FUNC func);
void func_80012FA4(sint32 n);
void func_80012FC8(sint32 n);
void func_80012424(void);
void func_80012938(void);
void func_80012ECC(void);
void func_80012F24(sint32 n);
void func_8001319C(void);
void Thread_open(sint32 n, TH_FUNC func);
void func_800131FC(void);
void Thread_exec_file(char *name);
void Thread_open_file(sint32 n, char *name);

#endif // SYSTEM_H
