// PsyQ imports for the compiled shim, and native entries for the retail interpreter.
#include "gpu.h"
#include "mips_cpu.h"
#include "mips_memory.h"
#include "shim_host.h"
#include "port_game.h"
#include "port_stubs.h"
#include "psx_mem.h"
#include "shim_addresses.h"

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PSYQ_RECT;
struct PSYQ_DISPENV;
struct PSYQ_DRAWENV;
extern int LoadImage(struct PSYQ_RECT *, uint32_t *);

static w2c_shim *active_shim;
static jmp_buf *loadexec_target;

int port_aot_shim_wait_for_loadexec(w2c_shim *shim)
{
    jmp_buf target;

    loadexec_target = &target;
    if (setjmp(target) == 0)
    {
        w2c_shim_psx_main(shim);
        loadexec_target = NULL;
        return 0;
    }

    loadexec_target = NULL;
#if WASM_RT_STACK_DEPTH_COUNT
    wasm_rt_call_stack_depth = 0; // LoadExec discarded the shim's compiled call stack.
#endif
    return 1;
}

void port_aot_shim_start(w2c_shim *shim)
{
    wasm_rt_init();
    wasm2c_shim_instantiate(shim, NULL);
    wasm_rt_memory_t *memory = w2c_shim_memory(shim);
    port_aot_mips_bind(memory->data, memory->size);
    active_shim = shim;
}

void port_aot_shim_finish(w2c_shim *shim)
{
    port_aot_mips_bind(NULL, 0);
    active_shim = NULL;
    wasm2c_shim_free(shim);
    wasm_rt_free();
}

static uint32_t load_image(uint32_t rect_address, uint32_t pixels_address)
{
    GPU_RECT rect;
    void *encoded = port_aot_memory_span(rect_address, sizeof(rect));

    if (encoded == NULL)
    {
        abort();
    }
    memcpy(&rect, encoded, sizeof(rect));
    if (rect.w <= 0 || rect.w > GPU_VRAM_W || rect.h <= 0 || rect.h > GPU_VRAM_H)
    {
        abort();
    }
    void *pixels = port_aot_memory_span(
        pixels_address, (size_t)rect.w * (size_t)rect.h * sizeof(uint16_t));

    if (pixels == NULL)
    {
        abort();
    }
    return LoadImage(encoded, pixels);
}

u32 w2c_host_LoadImage(struct w2c_host *host, u32 rect, u32 pixels)
{
    return load_image(rect, pixels);
}

void w2c_host_SetDrawMode(struct w2c_host *host, u32 mode, u32 dfe, u32 dtd, u32 tpage, u32 tw)
{
    const uint32_t args[8] = {mode, dfe, dtd, tpage, tw};

    mips_call(RETAIL_SetDrawMode, args);
}

static uint64_t native_load_image(uint32_t rect, uint32_t pixels, uint32_t a2, uint32_t a3,
                                     uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7,
                                     uint32_t a8, uint32_t a9)
{
    return load_image(rect, pixels);
}

void *port_stub_target(const PORT_STUB *stub)
{
    return (void *)stub->native;
}

void *port_overlay_native_find(uint32_t address)
{
    return NULL;
}


// The native PsyQ entry points used by the shim. The game-facing imports always
// take 32-bit words. Buffer parameters are translated here at the host boundary.
typedef void (*CD_CALLBACK)(uint8_t, uint8_t *);
extern int VSync(int), DrawSync(int), ResetGraph(int);
extern int CdInit(void), CdReset(int), CdMix(void *);
extern int CdSync(int, uint8_t *), CdGetSector(void *, int);
extern int CdControl(uint8_t, uint8_t *, uint8_t *), CdControlB(uint8_t, uint8_t *, uint8_t *);
extern void *CdReadyCallback(CD_CALLBACK), *CdSyncCallback(CD_CALLBACK);
extern void ResetCallback(void), SetDispMask(int);
extern void *InterruptCallback(int, void *), *DMACallback(int, void *);
extern void *VSyncCallback(void (*)(void));
extern struct PSYQ_DISPENV *PutDispEnv(struct PSYQ_DISPENV *);
extern struct PSYQ_DRAWENV *PutDrawEnv(struct PSYQ_DRAWENV *);
extern uint32_t *ClearOTag(uint32_t *, int);
extern int ClearImage(struct PSYQ_RECT *, uint8_t, uint8_t, uint8_t);
extern void DrawOTag(uint32_t *);

static void *guest_pointer(uint32_t address)
{
    return address != 0 ? port_aot_mips_ptr(address) : NULL;
}

#define HOST_0(result, name, expression) \
    result w2c_host_##name(struct w2c_host *host) { expression; }
#define HOST_1(result, name, expression) \
    result w2c_host_##name(struct w2c_host *host, u32 a0) { expression; }
#define HOST_2(result, name, expression) \
    result w2c_host_##name(struct w2c_host *host, u32 a0, u32 a1) { expression; }
#define HOST_3(result, name, expression) \
    result w2c_host_##name(struct w2c_host *host, u32 a0, u32 a1, u32 a2) { expression; }
#define HOST_4(result, name, expression) \
    result w2c_host_##name(struct w2c_host *host, u32 a0, u32 a1, u32 a2, u32 a3) { expression; }
#define HOST_5(result, name, expression) \
    result w2c_host_##name(struct w2c_host *host, u32 a0, u32 a1, u32 a2, u32 a3, u32 a4) { expression; }

#define MIPS(name, ...) mips_call(RETAIL_##name, (const uint32_t[8]){__VA_ARGS__})

HOST_0(u32, CdInit, return CdInit())
HOST_0(void, ResetCallback, ResetCallback())
HOST_0(void, StartPAD, port_pad_start(1))
HOST_0(void, StopPAD, port_pad_start(0))
HOST_0(void, 0x5F96_init, (void)0)
HOST_0(void, port_spin_pause, port_spin_pause())
HOST_0(void, port_vblank_idle, port_vblank_idle())
HOST_0(void, SsInit, MIPS(SsInit, 0))
HOST_0(void, SsQuit, MIPS(SsQuit, 0))
HOST_1(void, ChangeClearPAD, (void)a0)
HOST_1(void, DrawOTag, DrawOTag(guest_pointer(a0)))
HOST_1(void, SetDispMask, SetDispMask(a0))
HOST_1(void, DecDCTReset, MIPS(DecDCTReset, a0))
HOST_1(u32, DecDCToutCallback, return MIPS(DecDCToutCallback, a0))
HOST_1(u32, CdMix, return CdMix(guest_pointer(a0)))
HOST_1(u32, CdReset, return CdReset(a0))
HOST_1(u32, DrawSync, return DrawSync(a0))
HOST_1(u32, ResetGraph, return ResetGraph(a0))
HOST_1(u32, VSync, return VSync(a0))
HOST_1(u32, SetVideoMode, return MIPS(SetVideoMode, a0))
HOST_1(u32, PutDispEnv, return psx_addr(PutDispEnv(guest_pointer(a0))))
HOST_1(u32, PutDrawEnv, return psx_addr(PutDrawEnv(guest_pointer(a0))))
HOST_2(u32, CdGetSector, return CdGetSector(guest_pointer(a0), a1))
HOST_2(u32, CdIntToPos, return MIPS(CdIntToPos, a0, a1))
HOST_2(u32, CdSync, return CdSync(a0, guest_pointer(a1)))
HOST_2(u32, ClearOTag, return psx_addr(ClearOTag(guest_pointer(a0), a1)))
HOST_2(void, DecDCTin, MIPS(DecDCTin, a0, a1))
HOST_2(void, DecDCTout, MIPS(DecDCTout, a0, a1))
HOST_2(u32, DecDCTvlc, return MIPS(DecDCTvlc, a0, a1))
HOST_3(u32, CdControl, return CdControl(a0, guest_pointer(a1), guest_pointer(a2)))
HOST_3(u32, CdControlB, return CdControlB(a0, guest_pointer(a1), guest_pointer(a2)))
HOST_3(void, SsSetSerialAttr, MIPS(SsSetSerialAttr, a0, a1, a2))
HOST_3(void, SsSetSerialVol, MIPS(SsSetSerialVol, a0, a1, a2))
HOST_4(u32, ClearImage, return ClearImage(guest_pointer(a0), a1, a2, a3))
HOST_4(void, InitPAD, port_pad_init(guest_pointer(a0), a1, guest_pointer(a2), a3))
HOST_5(u32, SetDefDispEnv, return MIPS(SetDefDispEnv, a0, a1, a2, a3, a4))
HOST_5(u32, SetDefDrawEnv, return MIPS(SetDefDrawEnv, a0, a1, a2, a3, a4))

static uint32_t draw_env_builder = RETAIL_SetDrawEnv2;

void port_gpu_set_draw_env_builder(uint32_t address)
{
    draw_env_builder = address;
}

uint32_t psyq_SetDrawEnv2(uint32_t packet, uint32_t env, uint32_t a2, uint32_t a3,
                          uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7)
{
    const uint32_t args[8] = {packet, env, a2, a3, a4, a5, a6, a7};
    return mips_call(draw_env_builder, args);
}

static void vsync_callback(void)
{
    w2c_shim_Vsync_handler(active_shim);
}

static void cd_sync_callback(uint8_t status, uint8_t *result)
{
    const uint32_t address = 0x80218000u;
    memcpy(port_aot_mips_ptr(address), result, 8);
    w2c_shim_Cd_sync_cb(active_shim, status, address);
}

static void cd_ready_callback(uint8_t status, uint8_t *result)
{
    const uint32_t address = 0x80218008u;
    memcpy(port_aot_mips_ptr(address), result, 8);
    w2c_shim_Movie_sector_cb(active_shim, status, address);
}

static void check_callback(uint32_t address, uint32_t expected)
{
    if (address != 0 && address != expected)
    {
        port_log("unexpected boot callback 0x%08X (expected 0x%08X)", address, expected);
        port_stop(1, "invalid boot callback");
    }
}

void w2c_host_VSyncCallback(struct w2c_host *host, u32 address)
{
    check_callback(address, RETAIL_Vsync_handler);
    VSyncCallback(address != 0 ? vsync_callback : NULL);
}

u32 w2c_host_CdSyncCallback(struct w2c_host *host, u32 address)
{
    check_callback(address, RETAIL_Cd_sync_cb);
    return CdSyncCallback(address != 0 ? cd_sync_callback : NULL) != NULL ? RETAIL_Cd_sync_cb : 0;
}

u32 w2c_host_CdReadyCallback(struct w2c_host *host, u32 address)
{
    check_callback(address, RETAIL_Movie_sector_cb);
    return CdReadyCallback(address != 0 ? cd_ready_callback : NULL) != NULL
               ? RETAIL_Movie_sector_cb : 0;
}

void w2c_host_LoadExec(struct w2c_host *host, u32 name, u32 stack, u32 stack_size)
{
    const char *path = guest_pointer(name);

    port_log("LoadExec(%s), stack 0x%08X", path, stack);
    if (loadexec_target != NULL)
    {
        if (strcmp(path, "cdrom:\\ROCK_NEO.EXE;1") != 0)
            port_stop(1, "unexpected LoadExec target");
        port_vblank_stop();
        longjmp(*loadexec_target, 1);
    }
    port_stop(0, "boot shim reached LoadExec");
}

#define MIPS_ADAPTER(name, expression) \
    static uint64_t native_##name(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, \
                                  uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, \
                                  uint32_t a8, uint32_t a9) \
    { \
        expression; \
    }

extern long OpenEvent(uint32_t, long, long, uint32_t);
extern long EnableEvent(long), CloseEvent(long), DisableEvent(long), WaitEvent(long), TestEvent(long);
extern void DeliverEvent(uint32_t, long);
MIPS_ADAPTER(VSync, return (uint32_t)VSync(a0))
MIPS_ADAPTER(OpenEvent, return (uint32_t)OpenEvent(a0, a1, a2, a3))
MIPS_ADAPTER(EnableEvent, return (uint32_t)EnableEvent(a0))
MIPS_ADAPTER(TestEvent, return (uint32_t)TestEvent(a0))
MIPS_ADAPTER(WaitEvent, return (uint32_t)WaitEvent(a0))
MIPS_ADAPTER(CloseEvent, return (uint32_t)CloseEvent(a0))
MIPS_ADAPTER(DisableEvent, return (uint32_t)DisableEvent(a0))
MIPS_ADAPTER(DeliverEvent, DeliverEvent(a0, a1); return 0)
MIPS_ADAPTER(ResetCallback, ResetCallback(); return 0)
MIPS_ADAPTER(InterruptCallback, return (uint32_t)(uintptr_t)InterruptCallback(a0, (void *)(uintptr_t)a1))
MIPS_ADAPTER(DMACallback, return (uint32_t)(uintptr_t)DMACallback(a0, (void *)(uintptr_t)a1))
MIPS_ADAPTER(Movie_dct_out_callback, w2c_shim_Movie_dct_out_callback(active_shim); return 0)

#define STUB(name) {RETAIL_##name, (void (*)(void))native_##name, #name, 0}

static int game_bios_active;

void port_aot_select_game_bios(void)
{
    game_bios_active = 1;
}

const PORT_STUB *port_stub_find(uint32_t address)
{
    static const PORT_STUB game_entries[] = {
        {0x80076A84u, (void (*)(void))native_VSync, "VSync", 0},
        {0x80076C68u, (void (*)(void))native_ResetCallback, "ResetCallback", 0},
        {0x80076C98u, (void (*)(void))native_InterruptCallback, "InterruptCallback", 0},
        {0x80076CC8u, (void (*)(void))native_DMACallback, "DMACallback", 0},
        {0x8007FEC0u, (void (*)(void))native_DeliverEvent, "DeliverEvent", 0},
        {0x8007FED0u, (void (*)(void))native_OpenEvent, "OpenEvent", 0},
        {0x8007FEE0u, (void (*)(void))native_WaitEvent, "WaitEvent", 0},
        {0x8007FEF0u, (void (*)(void))native_TestEvent, "TestEvent", 0},
        {0x8007FF00u, (void (*)(void))native_EnableEvent, "EnableEvent", 0},
    };
    static const PORT_STUB shim_entries[] = {
        {RETAIL_LoadImage, (void (*)(void))native_load_image, "LoadImage", 0},
        STUB(VSync),
        STUB(OpenEvent),
        STUB(EnableEvent),
        STUB(CloseEvent),
        STUB(DisableEvent),
        STUB(DeliverEvent),
        STUB(ResetCallback),
        STUB(InterruptCallback),
        STUB(DMACallback),
        STUB(Movie_dct_out_callback),
    };
    const PORT_STUB *entries = game_bios_active ? game_entries : shim_entries;
    size_t count = game_bios_active ? sizeof(game_entries) / sizeof(game_entries[0])
                                   : active_shim != NULL ? sizeof(shim_entries) / sizeof(shim_entries[0]) : 0;
    for (size_t i = 0; i < count; i++)
    {
        if (entries[i].addr == address)
            return &entries[i];
    }
    return NULL;
}
