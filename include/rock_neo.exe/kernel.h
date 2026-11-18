#ifndef ROCK_KERNEL_H
#define ROCK_KERNEL_H

#include "common.h"

// The BIOS keeps its tables in the kernel area at physical 0x0000..0xFFFF, which the game reaches
// through KUSEG addresses (0x100). KSEG0 (0x80000100) is the same memory; the native port can
// map only that view, so its build defines KERNEL_ADDR to it (port/include/port_prelude.h).
#ifndef KERNEL_ADDR
#define KERNEL_ADDR(addr) (addr)
#endif

// BIOS thread records are 0xC0 bytes apart.
typedef struct
{
    uint8 unk00[0x78];
    uint32 gp;
    uint8 unk7C[0x18];
    uint32 sr;
    uint8 unk98[0x28];
} KERNEL_THREAD_CONTEXT;

typedef struct
{
    uint8 unk00[0x10];
    KERNEL_THREAD_CONTEXT *threads;
} KERNEL_TABLE;

#define KERNEL_TABLE_PTR  ((KERNEL_TABLE *)KERNEL_ADDR(0x100))
#define THREAD_INITIAL_SR 0x40000404

#endif // ROCK_KERNEL_H
