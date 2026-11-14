#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"
#include "psyq/libapi.h"

// BIOS thread control block (0xC0 bytes); the table's address is stored at 0x110.
typedef struct
{
    uint32 status;     // 0x00
    uint32 unk04;      // 0x04
    uint32 reg[32];    // 0x08 saved general registers (reg[28] = gp)
    uint32 epc;        // 0x88
    uint32 hi;         // 0x8C
    uint32 lo;         // 0x90
    uint32 sr;         // 0x94
    uint32 cause;      // 0x98
    uint8 unk9C[0x24]; // 0x9C
} TCB;                 // 0xC0

#define TCB_TBL (((TCB **)0x100)[4])

// Thread records live at 0x801F8100, 0x80 bytes apart (see notes/rock_neo.md, "Threads").
typedef struct
{
    uint16 flags;      // 0x00 Thread_wait stores 1 here; func_80012FA4/func_80012FC8 set/clear THREAD_FLAG_40
    uint16 wait;       // 0x02 Thread_wait's argument
    uint8 unk04[4];    // 0x04
    uint32 th;         // 0x08 BIOS thread handle, closed by func_80012ECC/func_80012F24
    TCB *tcb;          // 0x0C this thread's BIOS TCB (func_80012BC4)
    uint32 sp;         // 0x10 initial stack pointer for OpenTh (stacks 0x400 apart from 0x801FEC00)
    uint8 unk14[0x30]; // 0x14
    uint32 gp;         // 0x44 initial gp for OpenTh (copied from TCB 0)
    uint8 unk48[0x18]; // 0x48
    uint16 unk60[8];   // 0x60 zeroed by func_8001319C
    uint8 unk70;       // 0x70
    uint8 unk71[15];   // 0x71 func_8001319C zeroes 16 bytes from here (the last is the next record's flags)
} THREAD_WORK;         // 0x80

typedef void (*TASK_FUNC)(sint8 *routine);

#define THREAD_FLAG_40 0x0040

// Literal addresses, not symbols: the target builds them with lui/ori (`li`), which only a
// constant gives (a symbol gives lui %hi / %lo). Thread_current is also in symbol_addrs
// (absolute) for the code still in assembly.
#define THREAD_TBL     ((THREAD_WORK *)0x801F8100)
#define Thread_current (*(THREAD_WORK **)0x801F8300) // the running thread's record

extern TASK_FUNC D_80080894[]; // task dispatch table, indexed by D_80098B1C
extern sint8 D_80098B1C;
extern sint8 D_80098B1D;

void Thread_wait(sint32 arg);
void Vsync_handler(void);
void func_80012F78(sint32 arg);
void func_80012FA4(sint32 n);
void func_80012FC8(sint32 n);
void func_80012424(void);
void func_80012938(void);
void func_80012ECC(void);
void func_80012F24(sint32 n);
void func_8001319C(void);
void func_8001246C(void);
void func_80012BC4(void);
void Thread_open(sint32 n, TH_FUNC func);
void func_800131FC(void);

#endif // SYSTEM_H
