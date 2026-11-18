// The PS1 address space, mapped into the host process at the PS1's own addresses.
//
// Main RAM (2 MB) lives at 0x80000000 (KSEG0) and the scratchpad (1 KB, mapped as one 4 KB
// page) at 0x1F800000, so the game's literal addresses (`(uint32 *)0x801F8100`,
// `*(uint8 *)0x1F800074`) and the 32-bit pointers stored in its data work unchanged.
// 0x80000000..0x80FFFFFF (16 MB) is reserved: a GPU ordering-table tag holds a 24-bit address,
// so everything the GPU walks must sit in this window; the space above the real 2 MB is
// available for native data that the game hands to the GPU.
#ifndef PORT_PSX_MEM_H
#define PORT_PSX_MEM_H

#include <stdint.h>

#define PSX_RAM_BASE     0x80000000u
#define PSX_RAM_SIZE     0x00200000u
#define PSX_RAM_WINDOW   0x01000000u
#define PSX_SCRATCH_BASE 0x1F800000u
#define PSX_SCRATCH_SIZE 0x00000400u
#define PSX_SCRATCH_PAGE 0x00001000u
#define PSX_KUSEG_MIRROR 0x00010000u // first KUSEG address mirrored onto RAM (vm.mmap_min_addr)

// Maps RAM and scratchpad. Returns 0 on success, -1 (with a message) if the fixed addresses are
// taken or the host refuses the mapping.
int psx_mem_init(void);

// Translates a PS1 address (KUSEG/KSEG0/KSEG1 RAM, 24-bit OT address, or scratchpad) into a host
// pointer; NULL if it is outside RAM and the scratchpad.
void *psx_ptr(uint32_t addr);

// The PS1 address of a host pointer into the mapped window (or the pointer value itself).
uint32_t psx_addr(const void *p);

// Loads a PS-X EXE (header + text/data image) into RAM at its load address. Fills the entry
// point, initial $gp and stack if the pointers are non-NULL. Returns 0 on success.
typedef struct
{
    uint32_t pc0, gp0, t_addr, t_size, b_addr, b_size, s_addr, s_size;
} PSX_EXE_INFO;
int psx_load_exe(const char *path, PSX_EXE_INFO *info);

// Writes an x86 jump to `native` at a retail function address in RAM, so a 32-bit function
// pointer taken from retail data (a dispatch table, a callback field) still calls the native
// code. 5 bytes on i386 (jmp rel32); MIPS functions are at least 8 bytes apart.
// Returns 0 on success.
int psx_install_stub(uint32_t addr, void (*native)(void));

#endif
