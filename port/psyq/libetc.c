// PsyQ libetc: vertical sync and the interrupt callbacks, on the host's vblank timer
// (port/runtime/port_game.c).
#define _GNU_SOURCE
#include "port_game.h"
#include "psx_io.h"

#include <stdint.h>
#include <string.h>
#include <time.h>

typedef void (*CALLBACK)(void);

static volatile CALLBACK vsync_cb;
static volatile uint32_t irq_cb[11]; // InterruptCallback, by PS1 address (retail code)
static uint32_t last_vsync; // vblank count at the previous VSync call
static struct timespec last_blank;
static int started;
static int initialized;

#ifdef PORT_AOT_MIPS
void port_libetc_reset_session(void)
{
    port_vblank_stop();
    vsync_cb = NULL;
    memset((void *)irq_cb, 0, sizeof(irq_cb));
    last_vsync = 0;
    started = 0;
    initialized = 0;
}
#endif

static void vblank(void)
{
    clock_gettime(CLOCK_MONOTONIC, &last_blank);
    if (vsync_cb != NULL)
    {
        vsync_cb();
    }
    // An IRQ0 hook (libsnd's sequencer tick, _SsTrapIntrVSync): on the console it replaces
    // libetc's vblank dispatcher and chains to it; here the dispatcher has just run.
    psx_call(irq_cb[0]);
}

// Horizontal lines since the last vertical blank (NTSC: 263 lines per 1/60 s).
static int hcount(void)
{
    struct timespec now;
    long us;

    if (port_options.deterministic)
    {
        return 8; // the game-paced clock: work takes no time; a few lines after the blank
    }
    clock_gettime(CLOCK_MONOTONIC, &now);
    us = (now.tv_sec - last_blank.tv_sec) * 1000000L + (now.tv_nsec - last_blank.tv_nsec) / 1000;
    if (us < 0)
    {
        us = 0;
    }
    return (int)((us * 263L) / 16683L) & 0xFFFF;
}

// VSync(0) waits for the next vertical blank, VSync(n > 1) until n blanks after the previous
// call, VSync(1) only reports; all return the lines since the last blank. VSync(-1) returns the
// blank count.
int VSync(int mode)
{
    uint32_t target;

    if (mode < 0)
    {
        return (int)port_vblank_count();
    }
    if (mode == 1)
    {
        return hcount();
    }
    if (!started)
    {
        port_log_limited("VSync", 1, "VSync(%d) before ResetCallback: not waiting", mode);
        return 0;
    }
    target = mode > 1 ? last_vsync + (uint32_t)mode - 1 : port_vblank_count();
    port_vblank_wait(target);
    last_vsync = port_vblank_count();
    return hcount();
}

void *VSyncCallback(CALLBACK func)
{
    CALLBACK old = vsync_cb;

    vsync_cb = func;
    return (void *)old;
}

// Initializes the interrupt system with no callbacks registered.
// Like the library's, only the first call does anything: libspu's SpuInit and libpress's
// DecDCTReset call it again after the game has set its callbacks.
void ResetCallback(void)
{
    if (initialized)
    {
        return;
    }
    initialized = 1;
    vsync_cb = NULL;
    memset((void *)irq_cb, 0, sizeof(irq_cb));
    if (!started)
    {
        clock_gettime(CLOCK_MONOTONIC, &last_blank);
        port_vblank_start(vblank);
        started = 1;
    }
}

// Stops interrupt handling (the game does this around a thread switch it flags).
void StopCallback(void)
{
    if (started)
    {
        port_vblank_stop();
        started = 0;
    }
}

// Restarts after StopCallback with the callbacks kept.
void RestartCallback(void)
{
    if (!started)
    {
        port_vblank_start(vblank);
        started = 1;
    }
}

// Interrupt callbacks for the other sources. Only IRQ0 (vertical blank) is raised by the port;
// libsnd hooks it with _SsStart. The previous IRQ0 callback is reported as none: the vblank
// dispatcher (VSyncCallback) always runs first (see vblank above), so libsnd must not chain to
// it a second time.
void *InterruptCallback(int irq, void *func)
{
    uint32_t old;

    if (irq < 0 || irq >= 11)
    {
        return NULL;
    }
    old         = irq_cb[irq];
    irq_cb[irq] = (uint32_t)(uintptr_t)func;
    return (void *)(uintptr_t)old;
}

// DMA completion callbacks: psx_io.c completes DMA (only channel 4, sound RAM, is used by
// interpreted code) at once and then calls it.
void *DMACallback(int ch, void *func)
{
    return (void *)(uintptr_t)psx_dma_set_callback(ch, (uint32_t)(uintptr_t)func);
}

// Root counters: libsnd programs counter 3 (the vertical blank) for its tick; the port drives
// the tick from the vertical blank itself.
long SetRCnt(uint32_t spec, uint16_t target, long mode)
{
    return 1;
}
long GetRCnt(uint32_t spec)
{
    return 0;
}
long StartRCnt(uint32_t spec)
{
    return 1;
}
long StopRCnt(uint32_t spec)
{
    return 1;
}
long ResetRCnt(uint32_t spec)
{
    return 1;
}
