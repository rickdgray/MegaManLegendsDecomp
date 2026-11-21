#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

/*
 * Self-written declarations for the PsyQ libapi functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

// Argument order differs from the Library Reference, which lists (bufA, bufB, lenA, lenB): both
// programs pass buffer, length, buffer, length (a0 = &Joy1, a1 = 8, a2 = &Joy2, a3 = 8), the
// order of the BIOS InitPAD the library calls.
long InitPAD(char *bufA, long lenA, char *bufB, long lenB);

long StartPAD(void);
void ChangeClearPAD(long val);
void StopPAD(void);
void _96_init(void);
void LoadExec(char *name, u_long s_addr, u_long s_size);

// Execution file data (kernel.h): the exec info in a PS-X EXE header's first 2 KB.
typedef struct
{
    u_long pc0;    // 0x00 execution start address
    u_long gp0;    // 0x04
    u_long t_addr; // 0x08 text section address
    u_long t_size; // 0x0C
    u_long d_addr; // 0x10
    u_long d_size; // 0x14
    u_long b_addr; // 0x18
    u_long b_size; // 0x1C
    u_long s_addr; // 0x20
    u_long s_size; // 0x24
    u_long sp;     // 0x28
    u_long fp;     // 0x2C
    u_long gp;     // 0x30
    u_long ret;    // 0x34
    u_long base;   // 0x38
} EXEC;            // 0x3C

// Register save slots in TCB.reg (kernel.h's register designation macros, in the Library
// Overview's order: R_ZERO-R_RA are the general registers 0-31).
#define R_ZERO  0
#define R_AT    1
#define R_V0    2
#define R_V1    3
#define R_A0    4
#define R_A1    5
#define R_A2    6
#define R_A3    7
#define R_T0    8
#define R_T1    9
#define R_T2    10
#define R_T3    11
#define R_T4    12
#define R_T5    13
#define R_T6    14
#define R_T7    15
#define R_S0    16
#define R_S1    17
#define R_S2    18
#define R_S3    19
#define R_S4    20
#define R_S5    21
#define R_S6    22
#define R_S7    23
#define R_T8    24
#define R_T9    25
#define R_K0    26
#define R_K1    27
#define R_GP    28
#define R_SP    29
#define R_FP    30
#define R_RA    31
#define R_EPC   32 // interrupt return address
#define R_MDHI  33 // multiply/divide result (high)
#define R_MDLO  34 // multiply/divide result (low)
#define R_SR    35 // status register
#define R_CAUSE 36 // cause register
// The documents don't give NREGS; 40 makes the TCB 0xC0 bytes, the BIOS's TCB size (the thread
// setup in func_80012BC4 steps through the TCB table by 0xC0).
#define NREGS 40

// Task control block (kernel.h).
typedef struct
{
    long status;       // 0x00
    long mode;         // 0x04
    u_long reg[NREGS]; // 0x08 register save area, indexed with R_*
    long system[6];    // 0xA8 reserved by the system
} TCB;                 // 0xC0

// Task control block header (kernel.h): the running thread's TCB.
typedef struct
{
    TCB *entry; // 0x00
    long flag;  // 0x04 reserved by the system
} TCBH;         // 0x08

void FlushCache(void);

// Threads and events. The Library Reference types both start functions as `long (*func)()` /
// `unsigned long (*func)()`; the game's handlers return nothing, so these typedefs (ours, not
// PsyQ's) return void.
typedef void (*TH_FUNC)(void);
typedef void (*EVENT_FUNC)(void);

u_long OpenTh(TH_FUNC func, u_long sp, u_long gp);
long CloseTh(u_long thread);
long ChangeTh(u_long thread);
long OpenEvent(u_long desc, long spec, long mode, EVENT_FUNC func);
long EnableEvent(u_long event);
long TestEvent(u_long event);
void EnterCriticalSection(void);
void ExitCriticalSection(void);

#endif // PSYQ_LIBAPI_H
