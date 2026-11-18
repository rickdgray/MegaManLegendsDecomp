// A small R3000A interpreter that runs retail MIPS functions in place.
//
// Pure PsyQ library routines (libgte's matrix and trig functions, ratan2, SquareRoot0, the CD
// position conversions, rand) touch nothing but memory and the GTE. Rather than rewriting them,
// the port calls the retail code itself: the retail image is loaded at its own addresses, and
// because the process is 32-bit with PS1 memory mapped where the PS1 has it, every address the
// MIPS code computes (PS1 RAM, the scratchpad, or a pointer to a native local on the host stack)
// is directly a host address. COP2 instructions go to the software GTE (gte.c), so results are
// bit-exact with the hardware model.
//
// The same interpreter runs the stage, weapon and support overlays (overlay.c): a call from
// interpreted code into native code (a retail function the port compiled, found in the stub
// table, or an overlay function with a native replacement) calls it with a0-a3 and the stack
// arguments and returns its result in v0/v1.
//
// Hardware register loads and stores go to psx_io.c (the SPU and DMA for libsnd/libspu).
// syscall 1/2 are the critical sections; COP0 moves are storage.
// Not supported, and reported as fatal: other syscalls, break, unaligned (lwl/lwr/swl/swr) or
// coprocessor accesses to hardware registers.
#ifndef PORT_MIPS_CPU_H
#define PORT_MIPS_CPU_H

#include <stdint.h>

// Calls the MIPS function at `addr` with up to eight word arguments (a0-a3, then the stack
// slots at sp+0x10.. as the MIPS ABI places them). Returns v0.
uint32_t mips_call(uint32_t addr, const uint32_t args[8]);

// The same, returning v1:v0.
uint64_t mips_call64(uint32_t addr, const uint32_t args[8]);

// The native code standing for `addr`, or NULL when it is MIPS code to interpret.
void *mips_native_target(uint32_t addr);

// gp register value for interpreted code (the executable's small-data base).
extern uint32_t mips_gp;

// Native replacements for overlay functions (overlay.c).
void *port_overlay_native_find(uint32_t addr);

// Sets up the native-to-overlay call trap (overlay.c). Returns 0 on success.
int port_overlay_init(void);
uint64_t port_overlay_entries(void);

// Instructions executed so far (for tests).
uint64_t mips_cpu_steps(void);

#endif
