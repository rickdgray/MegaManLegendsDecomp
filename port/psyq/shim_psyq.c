// PsyQ for the boot shim (SLUS_006.03, port/shim.cmake): the routines run from the shim's retail
// image by the MIPS interpreter, and the two that leave the program.
//
// The hardware-facing libraries are the same native ones as ROCK_NEO.EXE's (port/psyq/libgpu.c,
// libetc.c, libapi.c, libcd.c, compiled again with -DPORT_SHIM and placed at the shim's
// addresses). The rest is pure software in the shim's image, like psyq_emulated.c is for the game:
// libgpu's packet builders, SetVideoMode, CdIntToPos, libsnd's start-up (on the software SPU), and
// libpress: DecDCTvlc decodes the movie's bitstream on the CPU, and DecDCTReset/DecDCTin/
// DecDCTout drive the MDEC through its registers and DMA, which the interpreter hands to the
// software MDEC (port/runtime/mdec.c). This file is linked but not placed.
#include "mips_cpu.h"
#include "port_game.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ARGS(...) uint32_t a[8] = {__VA_ARGS__}
#define S(x)      ((uint32_t)(int32_t)(x))
#define P(x)      ((uint32_t)(uintptr_t)(x))

// Addresses in the shim's matching build (build/slus_006.03/slus_006.03.elf).
#define EMULATED(name, addr)                                                                       \
    uint32_t name(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5,    \
                  uint32_t a6, uint32_t a7)                                                        \
    {                                                                                              \
        uint32_t args[8] = {a0, a1, a2, a3, a4, a5, a6, a7};                                       \
        return mips_call(addr, args);                                                              \
    }

EMULATED(CdIntToPos, 0x80013AEC)
EMULATED(SetDefDispEnv, 0x80015F38)
EMULATED(SetDefDrawEnv, 0x80015E80)
EMULATED(SetDrawMode, 0x80017A34)
EMULATED(SetVideoMode, 0x800133AC)
EMULATED(psyq_SetDrawEnv2, 0x80017CA4) // for the native PutDrawEnv
EMULATED(DecDCTReset, 0x800196FC)
EMULATED(DecDCTin, 0x80019868)
EMULATED(DecDCTout, 0x800198E4)
EMULATED(DecDCToutCallback, 0x800199A0)
EMULATED(DecDCTvlc, 0x80019E90)
EMULATED(SsInit, 0x8001A864)
EMULATED(SsQuit, 0x8001B6E8)

void SsSetSerialAttr(int8_t s, int8_t attr, int8_t mode)
{
    ARGS(S(s), S(attr), S(mode));
    mips_call(0x8001B7A4, a);
}

void SsSetSerialVol(int8_t s, int16_t l, int16_t r)
{
    ARGS(S(s), S(l), S(r));
    mips_call(0x8001BBCC, a);
}

// The BIOS's interrupt-handler reset before LoadExec: nothing to undo here.
void _96_init(void)
{
}

// The arguments the shim was started with (port/runtime/shim_main.c), passed on to the game.
char **port_shim_argv;

// LoadExec("cdrom:\\ROCK_NEO.EXE;1", ...): the game is the `mml` program next to this one; it
// loads ROCK_NEO.EXE itself. It gets the shim's own arguments.
long LoadExec(const char *name, uint32_t sp, uint32_t sp_size)
{
    static char path[PATH_MAX];
    ssize_t n = readlink("/proc/self/exe", path, sizeof(path) - 8);
    char *slash;

    if (n <= 0)
    {
        port_stop(1, "LoadExec: cannot find the game program");
    }
    path[n] = 0;
    slash   = strrchr(path, '/');
    strcpy(slash != NULL ? slash + 1 : path, "mml");
    port_log("LoadExec(%s): running %s", name, path);
    port_shim_argv[0] = path;
    port_exec(path, port_shim_argv);
}
