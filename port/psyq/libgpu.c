// PsyQ libgpu on the software GPU (port/runtime/gpu.c): the entries that talk to the hardware.
// The pure packet builders (GetTPage, SetDrawMode, SetDefDrawEnv, ...) run from the retail image
// (psyq_emulated.c); they read the GPU type and VRAM size that ResetGraph stores in libgpu's
// retail globals, so ResetGraph below sets those as the library does.
//
// Drawing is synchronous: DrawOTag walks the whole ordering table before it returns, so
// DrawSync always reports an idle GPU.
#include "gpu.h"
#include "port_game.h"
#include "psx_mem.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int16_t x, y, w, h;
} PSYQ_RECT;

// DRAWENV (include/psyq/libgpu.h): 0x5C bytes, the DR_ENV packet at 0x1C.
typedef struct
{
    PSYQ_RECT clip;
    int16_t ofs[2];
    PSYQ_RECT tw;
    uint16_t tpage;
    uint8_t dtd, dfe, isbg;
    uint8_t r0, g0, b0;
    uint32_t dr_env[16];
} PSYQ_DRAWENV;

// DISPENV: 0x14 bytes.
typedef struct
{
    PSYQ_RECT disp;
    PSYQ_RECT screen;
    uint8_t isinter, isrgb24, pad0, pad1;
} PSYQ_DISPENV;

_Static_assert(sizeof(PSYQ_DRAWENV) == 0x5C, "DRAWENV layout");
_Static_assert(sizeof(PSYQ_DISPENV) == 0x14, "DISPENV layout");

// libgpu's own state in retail data (the matching build's names), from its first byte:
// ROCK_NEO.EXE's at 0x80097718, the boot shim's (-DPORT_GPU_STATE) at 0x80048090.
#ifndef PORT_GPU_STATE
#define PORT_GPU_STATE 0x80097718u
#endif
#define GPU_STATE(off, type) (*(volatile type *)(PORT_GPU_STATE + (off)))
#define GPU_TYPE        GPU_STATE(0x00, uint8_t) // 0: the retail GPU's command layout
#define GPU_RESET_DONE  GPU_STATE(0x01, uint8_t)
#define GPU_DEBUG       GPU_STATE(0x02, uint8_t)
#define GPU_VRAM_WIDTH  GPU_STATE(0x04, int16_t)
#define GPU_VRAM_HEIGHT GPU_STATE(0x06, int16_t)
#define GPU_DRAW_ENV    ((PSYQ_DRAWENV *)(PORT_GPU_STATE + 0x10))   // last PutDrawEnv
#define GPU_DISP_ENV    ((PSYQ_DISPENV *)(PORT_GPU_STATE + 0x6C))   // last PutDispEnv
#define GPU_WIDTH_TBL   ((const uint32_t *)(PORT_GPU_STATE + 0x80)) // VRAM size by GPU type
#define GPU_HEIGHT_TBL  ((const uint32_t *)(PORT_GPU_STATE + 0x94))

uint32_t psyq_SetDrawEnv2(uint32_t dr_env, uint32_t env, uint32_t, uint32_t, uint32_t, uint32_t,
                          uint32_t, uint32_t);

static void (*draw_sync_cb)(void);

int ResetGraph(int mode)
{
    switch (mode & 7)
    {
        case 0:
        case 3:
        case 5:
            // Full reset: the library's state, as libgpu's ResetGraph sets it up.
            memset((void *)PORT_GPU_STATE, 0, 0x80);
            GPU_TYPE        = 0;
            GPU_RESET_DONE  = 1;
            GPU_VRAM_WIDTH  = (int16_t)GPU_WIDTH_TBL[0];
            GPU_VRAM_HEIGHT = (int16_t)GPU_HEIGHT_TBL[0];
            memset(GPU_DRAW_ENV, 0xFF, sizeof(PSYQ_DRAWENV));
            memset(GPU_DISP_ENV, 0xFF, sizeof(PSYQ_DISPENV));
            port_log("ResetGraph(%d): VRAM %dx%d", mode, GPU_VRAM_WIDTH, GPU_VRAM_HEIGHT);
            return 0;
        default:
            // 1: cancel drawing in progress (there never is any).
            return 0;
    }
}

int SetGraphDebug(int level)
{
    int old   = GPU_DEBUG;
    GPU_DEBUG = (uint8_t)level;
    return old;
}

void SetDispMask(int mask)
{
    port_display_enable(mask != 0);
}

int DrawSync(int mode)
{
    (void)mode;
    return 0;
}

void *DrawSyncCallback(void (*func)(void))
{
    void (*old)(void) = draw_sync_cb;
    draw_sync_cb      = func;
    return (void *)old;
}

static void drawn(void)
{
    if (draw_sync_cb != NULL)
    {
        draw_sync_cb();
    }
}

uint32_t *ClearOTag(uint32_t *ot, int n)
{
    int i;

    for (i = 0; i < n - 1; i++)
    {
        ot[i] = psx_addr(&ot[i + 1]) & 0xFFFFFF;
    }
    ot[n - 1] = 0x00FFFFFF;
    return ot;
}

// Reverse order: ot[n-1] is drawn first and links down to ot[0], which ends the list.
uint32_t *ClearOTagR(uint32_t *ot, int n)
{
    int i;

    ot[0] = 0x00FFFFFF;
    for (i = 1; i < n; i++)
    {
        ot[i] = psx_addr(&ot[i - 1]) & 0xFFFFFF;
    }
    return ot;
}

void DrawOTag(uint32_t *p)
{
    gpu_draw_ot(psx_addr(p));
    drawn();
    port_frame_drawn();
}

void DrawPrim(void *p)
{
    gpu_draw_prim(p);
    drawn();
}

PSYQ_DRAWENV *PutDrawEnv(PSYQ_DRAWENV *env)
{
    // The library builds the environment packet (E1-E6, and a fill when isbg) with SetDrawEnv2
    // and sends it; the packet is drawn here the same way.
    psyq_SetDrawEnv2(psx_addr(env->dr_env), psx_addr(env), 0, 0, 0, 0, 0, 0);
    env->dr_env[0] |= 0x00FFFFFF;
    gpu_draw_prim(env->dr_env);
    memcpy(GPU_DRAW_ENV, env, sizeof(*env));
    return env;
}

PSYQ_DISPENV *PutDispEnv(PSYQ_DISPENV *env)
{
    int w = env->disp.w, h = env->disp.h;

    gpu_set_display(env->disp.x, env->disp.y, w, h, env->isrgb24);
    memcpy(GPU_DISP_ENV, env, sizeof(*env));
    return env;
}

PSYQ_DRAWENV *GetDrawEnv(PSYQ_DRAWENV *env)
{
    memcpy(env, GPU_DRAW_ENV, sizeof(*env));
    return env;
}

PSYQ_DISPENV *GetDispEnv(PSYQ_DISPENV *env)
{
    memcpy(env, GPU_DISP_ENV, sizeof(*env));
    return env;
}

static GPU_RECT rect_of(const PSYQ_RECT *r)
{
    GPU_RECT g;

    g.x = r->x;
    g.y = r->y;
    g.w = r->w;
    g.h = r->h;
    return g;
}

int LoadImage(PSYQ_RECT *rect, uint32_t *p)
{
    GPU_RECT r = rect_of(rect);

    gpu_load_image(&r, p);
    return 0;
}

int StoreImage(PSYQ_RECT *rect, uint32_t *p)
{
    GPU_RECT r = rect_of(rect);

    gpu_store_image(&r, p);
    return 0;
}

int MoveImage(PSYQ_RECT *rect, int x, int y)
{
    GPU_RECT r = rect_of(rect);

    gpu_move_image(&r, x, y);
    return 0;
}

int ClearImage(PSYQ_RECT *rect, uint8_t r, uint8_t g, uint8_t b)
{
    GPU_RECT gr = rect_of(rect);

    gpu_clear_image(&gr, r, g, b);
    return 0;
}
