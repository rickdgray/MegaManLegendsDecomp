#ifndef THREAD_H
#define THREAD_H

#include "common.h"
#include "kernel.h"

#define THREAD_WAITING          1
#define THREAD_READY            2
#define THREAD_FLAG_SUSPENDED   0x40
#define THREAD_WORK_TABLE       ((THREAD_WORK *)0x801F8100)
#define THREAD_CURRENT_PTR      ((THREAD_WORK **)0x801F8300)
#define THREAD_MAIN_HANDLE      0xFF000000
#define THREAD_SLOT_COUNT       4
#define THREAD_STACK_SIZE       0x400
#define THREAD_STACK_BASE       ((uint8 *)0x801FEC00)
#define THREAD_VECTOR_TABLE     ((THREAD_FUNC *)0x801F8000)
#define THREAD_VECTOR_COUNT     9
#define THREAD_FILE_HEADER_SIZE 0x10
#define THREAD_FILE_WORK_SIZE   0x3C
#define THREAD_FILE_PREFIX_SIZE 0x7B4
#define THREAD_FILE_CHUNK_SIZE  0x800

typedef void (*THREAD_FUNC)(void);

// Scheduler slots are 0x80 bytes apart in 0x801F8100..0x801F82FF.
typedef struct
{
    uint16 state;
    uint16 wait;
    uint32 unk04;
    sint32 handle;
    KERNEL_THREAD_CONTEXT *context;
    void *stack;
    THREAD_FUNC entry;
    uint32 unk18;
    void *load_addr;
    uint8 unk20[0x24];
    uint32 gp;
    uint8 unk48[0x18];
    sint16 unk60[8];
    uint8 unk70;
    uint8 unk71[0xF];
} THREAD_WORK;

extern THREAD_WORK *Thread_current;
extern THREAD_FUNC D_80080870[THREAD_VECTOR_COUNT];

#endif // THREAD_H
