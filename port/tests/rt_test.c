// Runtime test: builds PS1 primitive packets in the RAM window, links them into an ordering
// table, walks it with the software GPU, shows VRAM in an SDL window, and draws live pad state.
//
// Usage:
//   rt_test                       window; Esc quits, Tab toggles full VRAM / display area
//   rt_test --headless N [--dump out.ppm] [--buttons 0xMASK]
//                                 render N frames without SDL, optionally write VRAM as PPM,
//                                 with the given PS1 button bits pressed on pad 1
#include "gpu.h"
#include "pad.h"
#include "psx_mem.h"
#ifdef PORT_HAVE_SDL
#include "platform_sdl.h"
#endif

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OT_LEN    10
#define PRIM_BASE 0x80100000u // primitive buffer in PS1 RAM, as the game keeps its own
#define OT_BASE   0x800F0000u
#define DISP_W    320
#define DISP_H    240
#define TEX_X     640 // 4-bit texture page x (a multiple of 64)
#define TEX_Y     0
#define CLUT_X    0
#define CLUT_Y    480

static uint32_t *ot;
static uint32_t *heap;

static uint32_t a24(const void *p)
{
    return psx_addr(p) & 0xFFFFFF;
}

static void ot_clear(void)
{
    int i;

    ot = psx_ptr(OT_BASE);
    for (i = 0; i < OT_LEN - 1; i++)
    {
        ot[i] = a24(&ot[i + 1]);
    }
    ot[OT_LEN - 1] = 0xFFFFFF;
    heap           = psx_ptr(PRIM_BASE);
}

// Allocates a packet of `words` command words and links it at OT entry `z` (like addPrim).
// Within one entry the last packet added is drawn first, as with PsyQ's addPrim.
static uint32_t *prim(int z, int words)
{
    uint32_t *p = heap;

    heap += words + 1;
    p[0]  = ((uint32_t)words << 24) | (ot[z] & 0xFFFFFF);
    ot[z] = (ot[z] & 0xFF000000u) | a24(p);
    return p + 1;
}

static uint32_t xy(int x, int y)
{
    return ((uint32_t)(y & 0xFFFF) << 16) | (uint32_t)(x & 0xFFFF);
}

static uint32_t rgb(uint32_t code, int r, int g, int b)
{
    return (code << 24) | ((uint32_t)b << 16) | ((uint32_t)g << 8) | (uint32_t)r;
}

static uint32_t uv(int u, int v, uint32_t hi)
{
    return (hi << 16) | ((uint32_t)v << 8) | (uint32_t)u;
}

static uint32_t tpage(int depth, int semi, int x, int y)
{
    return ((uint32_t)depth << 7) | ((uint32_t)semi << 5) | (uint32_t)((x / 64) | ((y / 256) << 4));
}

static uint32_t clut(int x, int y)
{
    return (uint32_t)((y << 6) | (x >> 4));
}

static void tile(int z, int x, int y, int w, int h, int r, int g, int b, int semi)
{
    uint32_t *p = prim(z, 3);

    p[0] = rgb(semi ? 0x62 : 0x60, r, g, b);
    p[1] = xy(x, y);
    p[2] = xy(w, h);
}

static void upload_texture(void)
{
    uint16_t clut_data[16];
    uint16_t tex[64 * 16]; // 64x64 texels at 4 bits = 16 halfwords per row
    GPU_RECT r;
    int x, y, i;

    for (i = 0; i < 16; i++)
    {
        // A ramp; entry 0 stays 0 (transparent), entry 15 has the semi-transparency bit.
        clut_data[i] = i == 0 ? 0 : (uint16_t)((i * 2) | ((31 - i * 2) << 5) | (i << 10));
    }
    clut_data[15] |= 0x8000;
    r.x = CLUT_X;
    r.y = CLUT_Y;
    r.w = 16;
    r.h = 1;
    gpu_load_image(&r, clut_data);

    for (y = 0; y < 64; y++)
    {
        for (x = 0; x < 16; x++)
        {
            uint16_t w = 0;
            for (i = 0; i < 4; i++)
            {
                int tx  = x * 4 + i;
                int idx = (((tx >> 3) ^ (y >> 3)) & 1) ? 1 + ((tx + y) & 13) : 14;
                if ((tx - 32) * (tx - 32) + (y - 32) * (y - 32) < 64)
                {
                    idx = 0; // a transparent hole
                }
                w |= (uint16_t)(idx << (i * 4));
            }
            tex[y * 16 + x] = w;
        }
    }
    r.x = TEX_X;
    r.y = TEX_Y;
    r.w = 16;
    r.h = 64;
    gpu_load_image(&r, tex);
}

static void draw_pad(int zb, int z, int px, int py, const PSX_PAD_STATE *s)
{
    static const struct
    {
        uint16_t bit;
        int x, y;
    } layout[] = {
        {PSX_PAD_UP, 16, 8},       {PSX_PAD_DOWN, 16, 32},   {PSX_PAD_LEFT, 4, 20},
        {PSX_PAD_RIGHT, 28, 20},   {PSX_PAD_SELECT, 48, 20}, {PSX_PAD_START, 64, 20},
        {PSX_PAD_TRIANGLE, 96, 8}, {PSX_PAD_CROSS, 96, 32},  {PSX_PAD_SQUARE, 84, 20},
        {PSX_PAD_CIRCLE, 108, 20}, {PSX_PAD_L2, 4, -14},     {PSX_PAD_L1, 20, -14},
        {PSX_PAD_R1, 92, -14},     {PSX_PAD_R2, 108, -14},   {PSX_PAD_L3, 40, 48},
        {PSX_PAD_R3, 72, 48},
    };
    size_t i;
    uint8_t buf[8];

    psx_pad_to_buffer(s, buf, sizeof(buf));
    tile(zb, px - 4, py - 20, 128, 120, 30, 30, 50, 0);
    // Packets in one entry draw last-added first: the stick dots go in before their boxes.
    if (buf[1] == PSX_PAD_ID_ANALOG)
    {
        tile(z, px + 24 + buf[6] / 8, py + 62 + buf[7] / 8, 3, 3, 255, 255, 255, 0);
        tile(z, px + 66 + buf[4] / 8, py + 62 + buf[5] / 8, 3, 3, 255, 255, 255, 0);
    }
    tile(z, px + 24, py + 62, 34, 34, 60, 60, 60, 0);
    tile(z, px + 66, py + 62, 34, 34, 60, 60, 60, 0);
    for (i = 0; i < sizeof(layout) / sizeof(layout[0]); i++)
    {
        // Read the pressed state back out of the PS1 buffer (active-low), as the game would.
        int pressed = !((buf[2] | (buf[3] << 8)) & layout[i].bit) && buf[0] == 0;
        tile(z, px + layout[i].x, py + layout[i].y, 10, 10, pressed ? 255 : 70, pressed ? 220 : 70,
             pressed ? 60 : 80, 0);
    }
}

static void build_frame(int frame, const PSX_PAD_STATE pads[2])
{
    uint32_t *p;
    double a = frame * 0.03;
    int cx = 70, cy = 70, i;

    ot_clear();

    // Entry 0 (drawn first): environment and background.
    p    = prim(0, 5);
    p[0] = 0xE1000000u | tpage(0, 0, TEX_X, TEX_Y); // texpage
    p[1] = 0xE3000000u;                             // draw area top-left (0,0)
    p[2] = 0xE4000000u | ((DISP_H - 1) << 10) | (DISP_W - 1);
    p[3] = 0xE5000000u; // offset (0,0)
    p[4] = 0xE6000000u; // mask off
    p    = prim(0, 3);  // fill (not clipped, no offset)
    p[0] = rgb(0x02, 16, 24, 64);
    p[1] = xy(0, 0);
    p[2] = xy(DISP_W, DISP_H);

    // Entry 1: flat triangle (POLY_F3), rotating.
    p    = prim(1, 4);
    p[0] = rgb(0x20, 230, 40, 40);
    for (i = 0; i < 3; i++)
    {
        double t = a + i * 2.0943951;
        p[1 + i] = xy(cx + (int)(40 * cos(t)), cy + (int)(40 * sin(t)));
    }
    // Gouraud quad (POLY_G4).
    p    = prim(1, 8);
    p[0] = rgb(0x38, 255, 0, 0);
    p[1] = xy(130, 30);
    p[2] = rgb(0, 0, 255, 0);
    p[3] = xy(210, 30);
    p[4] = rgb(0, 0, 0, 255);
    p[5] = xy(130, 110);
    p[6] = rgb(0, 255, 255, 255);
    p[7] = xy(210, 110);
    // Gouraud triangle (POLY_G3).
    p    = prim(1, 6);
    p[0] = rgb(0x30, 255, 255, 0);
    p[1] = xy(230, 30);
    p[2] = rgb(0, 0, 255, 255);
    p[3] = xy(300, 70);
    p[4] = rgb(0, 255, 0, 255);
    p[5] = xy(240, 110);

    // Entry 2: textured quad (POLY_FT4, 4-bit CLUT, modulated) and textured gouraud triangle.
    p    = prim(2, 9);
    p[0] = rgb(0x2C, 128, 128, 128);
    p[1] = xy(20, 130);
    p[2] = uv(0, 0, clut(CLUT_X, CLUT_Y));
    p[3] = xy(100, 130);
    p[4] = uv(63, 0, tpage(0, 0, TEX_X, TEX_Y));
    p[5] = xy(20, 210);
    p[6] = uv(0, 63, 0);
    p[7] = xy(100, 210);
    p[8] = uv(63, 63, 0);
    p    = prim(2, 9);
    p[0] = rgb(0x34, 255, 64, 64);
    p[1] = xy(110, 130);
    p[2] = uv(0, 0, clut(CLUT_X, CLUT_Y));
    p[3] = rgb(0, 64, 255, 64);
    p[4] = xy(190, 150);
    p[5] = uv(63, 0, tpage(0, 0, TEX_X, TEX_Y));
    p[6] = rgb(0, 64, 64, 255);
    p[7] = xy(120, 210);
    p[8] = uv(0, 63, 0);
    // Sprite (SPRT 32x32, raw texture), moving.
    p    = prim(2, 4);
    p[0] = rgb(0x65, 128, 128, 128);
    p[1] = xy(200 + (frame % 60), 130);
    p[2] = uv(16, 16, clut(CLUT_X, CLUT_Y));
    p[3] = xy(32, 32);

    // Entry 3: DR_MODE switching to additive semi-transparency, then a semi-transparent TILE
    // (added in reverse drawing order).
    tile(3, 60, 100, 120, 40, 80, 80, 0, 1);
    p    = prim(3, 2);
    p[0] = 0xE1000000u | tpage(0, 1, TEX_X, TEX_Y);
    p[1] = 0xE2000000u;

    // Entry 4: lines (LINE_F2, LINE_G2, a flat polyline).
    p    = prim(4, 3);
    p[0] = rgb(0x40, 255, 255, 255);
    p[1] = xy(10, 225);
    p[2] = xy(310, 225);
    p    = prim(4, 4);
    p[0] = rgb(0x50, 255, 0, 0);
    p[1] = xy(10, 232);
    p[2] = rgb(0, 0, 0, 255);
    p[3] = xy(310, 232);
    p    = prim(4, 6);
    p[0] = rgb(0x48, 255, 255, 0);
    p[1] = xy(250, 175);
    p[2] = xy(280, 200);
    p[3] = xy(310, 175);
    p[4] = xy(280, 150);
    p[5] = 0x55555555u;

    // Entry 5: DR_AREA clip (a big triangle confined to a box), then the area restored
    // (added in reverse drawing order).
    p    = prim(5, 2);
    p[0] = 0xE3000000u;
    p[1] = 0xE4000000u | ((DISP_H - 1) << 10) | (DISP_W - 1);
    p    = prim(5, 4);
    p[0] = rgb(0x20, 255, 128, 0);
    p[1] = xy(200, 140);
    p[2] = xy(400, 180);
    p[3] = xy(220, 300);
    p    = prim(5, 3);
    p[0] = 0xE3000000u | (150 << 10) | 230;
    p[1] = 0xE4000000u | (210 << 10) | 300;
    p[2] = 0xE5000000u | (0 << 11) | 0;

    // Entry 6: live pad state, drawn in its own 320x240 region beside the display area.
    p    = prim(6, 3);
    p[0] = 0xE3000000u | (0 << 10) | 320;
    p[1] = 0xE4000000u | ((DISP_H - 1) << 10) | 639;
    p[2] = 0xE5000000u | 320;
    p    = prim(6, 3);
    p[0] = rgb(0x02, 0, 0, 0);
    p[1] = xy(320, 0);
    p[2] = xy(320, 240);
    draw_pad(7, 8, 30, 40, &pads[0]);
    draw_pad(7, 8, 170, 40, &pads[1]);
}

static int dump_ppm(const char *path)
{
    FILE *f           = fopen(path, "wb");
    const uint16_t *v = gpu_vram();
    int i;

    if (f == NULL)
    {
        perror(path);
        return -1;
    }
    fprintf(f, "P6\n%d %d\n255\n", GPU_VRAM_W, GPU_VRAM_H);
    for (i = 0; i < GPU_VRAM_W * GPU_VRAM_H; i++)
    {
        uint8_t px[3];
        px[0] = (uint8_t)((v[i] & 0x1F) << 3);
        px[1] = (uint8_t)(((v[i] >> 5) & 0x1F) << 3);
        px[2] = (uint8_t)(((v[i] >> 10) & 0x1F) << 3);
        fwrite(px, 1, 3, f);
    }
    fclose(f);
    return 0;
}

int main(int argc, char **argv)
{
    PSX_PAD_STATE pads[2];
    int headless = 0, frames = 0, frame, i;
    const char *dump         = NULL;
    unsigned buttons         = 0;
    uint16_t last_buttons[2] = {0, 0};

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--headless") == 0 && i + 1 < argc)
        {
            headless = 1;
            frames   = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--dump") == 0 && i + 1 < argc)
        {
            dump = argv[++i];
        }
        else if (strcmp(argv[i], "--buttons") == 0 && i + 1 < argc)
        {
            buttons = (unsigned)strtoul(argv[++i], NULL, 0);
        }
    }

    if (psx_mem_init() != 0)
    {
        return 1;
    }
    gpu_init();
    gpu_set_display(0, 0, DISP_W, DISP_H, 0);
    upload_texture();
    psx_pad_reset(&pads[0]);
    psx_pad_reset(&pads[1]);
    pads[1].connected = 0;

#ifdef PORT_HAVE_SDL
    if (!headless && platform_init("Mega Man Legends port: runtime test", 2) != 0)
    {
        return 1;
    }
#else
    if (!headless)
    {
        fprintf(stderr, "rt_test was built without SDL; use --headless N\n");
        return 1;
    }
#endif

    for (frame = 0; !headless || frame < frames; frame++)
    {
        if (headless)
        {
            pads[0].buttons = (uint16_t)buttons;
            pads[0].lx      = 0xFF; // left stick pushed right, to show the analog bytes
            pads[0].ly      = 0x80;
        }
#ifdef PORT_HAVE_SDL
        else if (!platform_poll(pads))
        {
            break;
        }
#endif
        for (i = 0; i < 2; i++)
        {
            if (pads[i].buttons != last_buttons[i])
            {
                printf("pad %d buttons 0x%04X  L(%02X,%02X) R(%02X,%02X)\n", i + 1, pads[i].buttons,
                       pads[i].lx, pads[i].ly, pads[i].rx, pads[i].ry);
                last_buttons[i] = pads[i].buttons;
            }
        }
        gpu_reset_stats();
        build_frame(frame, pads);
        gpu_draw_ot(OT_BASE);
#ifdef PORT_HAVE_SDL
        if (!headless)
        {
            platform_present();
        }
#endif
    }
    {
        const GPU_STATS *s = gpu_stats();
        printf("last frame: %u commands, %u polygons, %u rects, %u lines, %u fills, %u packets, "
               "%u unknown\n",
               s->commands, s->polygons, s->rects, s->lines, s->fills, s->packets, s->unknown);
    }
    if (dump != NULL && dump_ppm(dump) == 0)
    {
        printf("wrote %s\n", dump);
    }
#ifdef PORT_HAVE_SDL
    if (!headless)
    {
        platform_shutdown();
    }
#endif
    return 0;
}
