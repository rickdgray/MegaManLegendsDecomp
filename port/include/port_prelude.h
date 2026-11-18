// Forced first include (-include port_prelude.h) for every game C file in the native port.
//
// The game's headers are used unchanged. This file runs before them and claims the include
// guards of the two headers that cannot work natively, so their later `#include`s become no-ops
// even when they are found through a quoted include next to the including header:
//   - include_asm.h: INCLUDE_ASM pulls MIPS assembly into the C file, and it places a file-scope
//     `.include "labels.inc"` asm statement. Natively a function still in assembly is simply not
//     defined; the link step generates a stub that reports it when called (port/tools/gen_link.py).
//   - common.h: re-declared here with the same typedefs so the guard can be claimed.
#ifndef PORT_PRELUDE_H
#define PORT_PRELUDE_H

#ifndef PORT
#error "port_prelude.h is for the native port build only"
#endif

#if !defined(__i386__)
// Game structures store pointers in 32-bit fields and data loaded from the disc holds 32-bit
// addresses, so the port is an ILP32 build.
#error "the game code must be built as 32-bit x86 (-m32)"
#endif

// --- include_asm.h ---------------------------------------------------------------------------
#define INCLUDE_ASM_H
// A declaration that names the missing function, so the file still parses (the `;` after the
// macro use completes it). The stub itself comes from the link step.
#define INCLUDE_ASM(FOLDER, NAME)    extern int port_asm_missing_##NAME
#define INCLUDE_RODATA(FOLDER, NAME) extern int port_rodata_missing_##NAME

// --- common.h --------------------------------------------------------------------------------
// Keep in step with include/common.h (only typedefs live there).
#define COMMON_H
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
// On the R3000 long is 32 bits; with -m32 it is too.
typedef unsigned long u_long;

#ifndef NULL
#define NULL ((void *)0)
#endif

// --- the BIOS kernel area --------------------------------------------------------------------
// include/rock_neo.exe/kernel.h: the game reads the BIOS tables at KUSEG 0x100; natively only
// the KSEG0 view of RAM is mapped (address 0 cannot be), and the runtime builds the tables there
// (port/psyq/libapi.c, port_kernel_init).
#define KERNEL_ADDR(addr) ((addr) | 0x80000000u)

// --- polling loops counted in iterations -----------------------------------------------------
// The boot shim's movie player waits for CD data by polling MOVIE_TIMEOUT (0x3FFFFF) times before
// it declares a timeout: about two seconds on the console, a few milliseconds natively, far less
// than a sector takes to arrive. Each poll here first waits about half a microsecond
// (port/runtime/port_game.c), so the limit means what it does on the console.
void port_spin_pause(void);
#define MOVIE_TIMEOUT (port_spin_pause(), 0x3FFFFF)

// --- the main loop's wait for the vertical blank ---------------------------------------------
// include/rock_neo.exe/display.h and include/slus_006.03/display.h put VSYNC_IDLE() in the body
// of the main loop's `while (Vsync_count < ...)`. With the game-paced clock (headless default,
// port/runtime/port_game.c) each call delivers one vertical blank; in real time it does nothing.
void port_vblank_idle(void);
#define VSYNC_IDLE() port_vblank_idle()

#endif // PORT_PRELUDE_H
