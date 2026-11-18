// Software model of the PS1 GPU: 1024x512 16-bit VRAM, GP0 drawing commands, ordering-table
// walk, and the image transfers that libgpu's LoadImage/StoreImage/MoveImage/ClearImage do.
// Pixel format is the PS1's own (bits 0-4 red, 5-9 green, 10-14 blue, 15 mask), which SDL
// presents directly as SDL_PIXELFORMAT_XBGR1555.
//
// Modelled: polygons (flat/gouraud, textured 4/8/15-bit, raw texture, semi-transparency modes
// 0-3, texture window, mask bit), rectangles and sprites of every size, lines and polylines,
// fill, VRAM copy, CPU-to-VRAM in a packet, and the E1-E6 environment commands. Not yet:
// dithering, 24-bit display mode, interlace, and the GPU's exact edge/UV rounding quirks.
#ifndef PORT_GPU_H
#define PORT_GPU_H

#include <stdint.h>

#define GPU_VRAM_W 1024
#define GPU_VRAM_H 512

typedef struct
{
    int16_t x, y, w, h;
} GPU_RECT;

typedef struct
{
    int x, y, w, h; // display area in VRAM (PutDispEnv's disp rect)
    int is24;       // 24-bit colour mode (movies)
    int enabled;
} GPU_DISPLAY;

void gpu_init(void);
uint16_t *gpu_vram(void);

// Executes `words` words of GP0 data (one or more commands back to back).
void gpu_gp0(const uint32_t *words, int count);

// Walks an ordering table / primitive chain starting at the PS1 address of its first tag, as
// DrawOTag does, until the terminator (24-bit address 0xFFFFFF).
void gpu_draw_ot(uint32_t first_tag);

// Executes one primitive packet (tag word at p), as DrawPrim does.
void gpu_draw_prim(const uint32_t *tag);

void gpu_load_image(const GPU_RECT *r, const void *src);
void gpu_store_image(const GPU_RECT *r, void *dst);
void gpu_move_image(const GPU_RECT *r, int x, int y);
void gpu_clear_image(const GPU_RECT *r, uint8_t red, uint8_t green, uint8_t blue);

void gpu_set_display(int x, int y, int w, int h, int is24);
const GPU_DISPLAY *gpu_display(void);

// Counters for tests and debugging.
typedef struct
{
    uint32_t commands, polygons, rects, lines, fills, packets, unknown;
    uint32_t oversized; // polygons the GPU drops for their size
} GPU_STATS;
const GPU_STATS *gpu_stats(void);
void gpu_reset_stats(void);

#endif
