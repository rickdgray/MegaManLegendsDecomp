// The PS1's hardware registers (0x1F801000..0x1F802FFF) for code the MIPS interpreter runs.
//
// Native code never touches hardware registers (the native PsyQ libraries stand in for the
// hardware-facing routines); the retail library code the interpreter runs (libsnd and libspu)
// does. Loads and stores in that range come here: the SPU (spu.c) with DMA channel 4 (sound RAM),
// the MDEC (mdec.c) with DMA channels 0 and 1 (transfers complete at once; their DMACallback runs
// when the interpreted call returns), and the interrupt, timer and memory control registers as
// plain storage. Anything else is logged once and reads as zero.
#ifndef PORT_PSX_IO_H
#define PORT_PSX_IO_H

#include <stdint.h>

#define PSX_IO_BASE 0x1F801000u
#define PSX_IO_END  0x1F803000u

// True for an address (any segment) in the hardware register range.
static inline int psx_io_is(uint32_t ea)
{
    uint32_t seg = ea >> 29, phys = ea & 0x1FFFFFFFu;

    return (seg == 0 || seg == 4 || seg == 5) && phys >= PSX_IO_BASE && phys < PSX_IO_END;
}

uint32_t psx_io_read(uint32_t ea, int size);
void psx_io_write(uint32_t ea, uint32_t value, int size);

// DMA completion callbacks (libetc's DMACallback): a MIPS or retail-native address, 0 = none.
void psx_io_reset(void);

uint32_t psx_dma_set_callback(int channel, uint32_t func);

// Runs the DMA completion callbacks of transfers started since the last call (the MIPS
// interpreter calls it when an interpreted call returns to native code).
void psx_io_run_pending(void);

// Calls a callback with no arguments: retail code (MIPS, or a native stub) by its PS1 address,
// or a native function by its host address. 0 does nothing.
void psx_call(uint32_t func);

#endif
