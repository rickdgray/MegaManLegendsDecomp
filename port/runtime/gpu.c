// Software PS1 GPU. See gpu.h. Command formats follow psx-spx "GPU Render ... Commands".
#include "gpu.h"

#include "psx_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint16_t vram[GPU_VRAM_W * GPU_VRAM_H];
static GPU_DISPLAY display;
static GPU_STATS stats;

// Drawing environment (GP0 E1-E6).
static struct
{
    int tp_x, tp_y, tp_semi, tp_depth; // texture page (E1, or a textured polygon's tpage)
    int tw_mask_x, tw_mask_y, tw_off_x, tw_off_y;
    int clip_x1, clip_y1, clip_x2, clip_y2; // inclusive
    int off_x, off_y;
    int mask_set, mask_check;
    int dither; // E1 bit 9: dither shaded and texture-blended polygons and lines
} env;

typedef struct
{
    int x, y;
    int r, g, b;
    int u, v;
} VTX;

typedef struct
{
    int shaded, textured, raw, semi;
    int semi_mode;
    int dither; // this primitive is dithered (E1 bit 9, and shaded or texture-blended)
    int tp_x, tp_y, depth;
    int clut_x, clut_y;
} DRAWCTX;

#define VRAM(x, y) vram[(((y) & (GPU_VRAM_H - 1)) * GPU_VRAM_W) + ((x) & (GPU_VRAM_W - 1))]

void gpu_init(void)
{
    memset(vram, 0, sizeof(vram));
    memset(&env, 0, sizeof(env));
    env.clip_x2     = GPU_VRAM_W - 1;
    env.clip_y2     = GPU_VRAM_H - 1;
    display.x       = 0;
    display.y       = 0;
    display.w       = 320;
    display.h       = 240;
    display.is24    = 0;
    display.enabled = 1;
    memset(&stats, 0, sizeof(stats));
}

uint16_t *gpu_vram(void)
{
    return vram;
}

const GPU_STATS *gpu_stats(void)
{
    return &stats;
}

void gpu_reset_stats(void)
{
    memset(&stats, 0, sizeof(stats));
}

void gpu_set_display(int x, int y, int w, int h, int is24)
{
    display.x    = x;
    display.y    = y;
    display.w    = w;
    display.h    = h;
    display.is24 = is24;
}

const GPU_DISPLAY *gpu_display(void)
{
    return &display;
}

// --- pixels ----------------------------------------------------------------------------------

static int sext11(uint32_t v)
{
    v &= 0x7FF;
    return (v & 0x400) ? (int)v - 0x800 : (int)v;
}

static void set_texpage(uint32_t tp)
{
    env.tp_x     = (int)(tp & 0xF) * 64;
    env.tp_y     = (int)((tp >> 4) & 1) * 256;
    env.tp_semi  = (int)((tp >> 5) & 3);
    env.tp_depth = (int)((tp >> 7) & 3);
}

static uint16_t blend(uint16_t back, uint16_t front, int mode)
{
    int i, out = 0;

    for (i = 0; i < 15; i += 5)
    {
        int b = (back >> i) & 0x1F;
        int f = (front >> i) & 0x1F;
        int c;

        switch (mode)
        {
            case 0:
                c = (b + f) >> 1;
                break;
            case 1:
                c = b + f;
                break;
            case 2:
                c = b - f;
                break;
            default:
                c = b + (f >> 2);
                break;
        }
        c = c < 0 ? 0 : c > 31 ? 31 : c;
        out |= c << i;
    }
    return (uint16_t)out;
}

// Writes one pixel. `color` carries the texel's bit 15 for textured primitives; `semi` says
// whether semi-transparency applies to this pixel.
static void plot(int x, int y, uint16_t color, int semi, int semi_mode)
{
    uint16_t *d;

    if (x < env.clip_x1 || x > env.clip_x2 || y < env.clip_y1 || y > env.clip_y2)
    {
        return;
    }
    d = &VRAM(x, y);
    if (env.mask_check && (*d & 0x8000))
    {
        return;
    }
    if (semi)
    {
        color = (uint16_t)((color & 0x8000) | blend(*d, color, semi_mode));
    }
    *d = (uint16_t)(color | (env.mask_set ? 0x8000 : 0));
}

static uint16_t rgb15(int r, int g, int b)
{
    r = r < 0 ? 0 : r > 255 ? 255 : r;
    g = g < 0 ? 0 : g > 255 ? 255 : g;
    b = b < 0 ? 0 : b > 255 ? 255 : b;
    return (uint16_t)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10));
}

// The GPU's 4x4 ordered dither (psx-spx, "GPU Rendering Attributes"): added to the 8-bit colour
// before it is cut to 5 bits, by screen position.
static const int8_t dither_tbl[4][4] = {
    {-4, 0, -3, 1},
    {2, -2, 3, -1},
    {-3, 1, -4, 0},
    {3, -1, 2, -2},
};

static uint16_t rgb15_at(int r, int g, int b, int dither, int x, int y)
{
    if (dither)
    {
        int d = dither_tbl[y & 3][x & 3];

        r += d;
        g += d;
        b += d;
    }
    return rgb15(r, g, b);
}

static uint16_t texel(const DRAWCTX *c, int u, int v)
{
    uint16_t w;
    int idx;

    u = (u & ~(env.tw_mask_x * 8)) | ((env.tw_off_x & env.tw_mask_x) * 8);
    v = (v & ~(env.tw_mask_y * 8)) | ((env.tw_off_y & env.tw_mask_y) * 8);
    u &= 0xFF;
    v &= 0xFF;
    switch (c->depth)
    {
        case 0:
            w   = VRAM(c->tp_x + u / 4, c->tp_y + v);
            idx = (w >> ((u & 3) * 4)) & 0xF;
            return VRAM(c->clut_x + idx, c->clut_y);
        case 1:
            w   = VRAM(c->tp_x + u / 2, c->tp_y + v);
            idx = (w >> ((u & 1) * 8)) & 0xFF;
            return VRAM(c->clut_x + idx, c->clut_y);
        default:
            return VRAM(c->tp_x + u, c->tp_y + v);
    }
}

// Shades and writes one pixel of a primitive. Texture blending works in 8 bits per channel
// (texel * 8 * colour / 0x80) so that dithering applies before the cut to 5 bits.
static void shade(const DRAWCTX *c, int x, int y, int r, int g, int b, int u, int v)
{
    uint16_t t;

    if (!c->textured)
    {
        plot(x, y, rgb15_at(r, g, b, c->dither, x, y), c->semi, c->semi_mode);
        return;
    }
    t = texel(c, u, v);
    if (t == 0)
    {
        return; // fully transparent texel
    }
    if (!c->raw)
    {
        int tr = (t & 0x1F) << 3, tg = ((t >> 5) & 0x1F) << 3, tb = ((t >> 10) & 0x1F) << 3;

        t = (uint16_t)((t & 0x8000) |
                       rgb15_at(tr * r >> 7, tg * g >> 7, tb * b >> 7, c->dither, x, y));
    }
    plot(x, y, t, c->semi && (t & 0x8000), c->semi_mode);
}

// --- triangles -------------------------------------------------------------------------------

static int64_t edge(const VTX *a, const VTX *b, int px, int py)
{
    return (int64_t)(b->x - a->x) * (py - a->y) - (int64_t)(b->y - a->y) * (px - a->x);
}

// Top-left fill rule (the GPU leaves out right and bottom edges).
static int top_left(const VTX *a, const VTX *b)
{
    int dy = b->y - a->y, dx = b->x - a->x;
    return dy < 0 || (dy == 0 && dx > 0);
}

static const uint32_t *trace_tag;

static void draw_tri(const VTX *a, const VTX *b, const VTX *c, const DRAWCTX *ctx)
{
    const VTX *v0 = a, *v1 = b, *v2 = c;
    int64_t area;
    int minx, maxx, miny, maxy, x, y;
    int tl0, tl1, tl2;

    area = edge(v0, v1, v2->x, v2->y);
    if (area == 0)
    {
        return;
    }
    if (area < 0)
    {
        v1   = c;
        v2   = b;
        area = -area;
    }
    minx = v0->x < v1->x ? v0->x : v1->x;
    minx = minx < v2->x ? minx : v2->x;
    maxx = v0->x > v1->x ? v0->x : v1->x;
    maxx = maxx > v2->x ? maxx : v2->x;
    miny = v0->y < v1->y ? v0->y : v1->y;
    miny = miny < v2->y ? miny : v2->y;
    maxy = v0->y > v1->y ? v0->y : v1->y;
    maxy = maxy > v2->y ? maxy : v2->y;
    if (maxx - minx >= GPU_VRAM_W || maxy - miny >= GPU_VRAM_H)
    {
        stats.oversized++;
        if (getenv("PORT_GPU_TRACE") != NULL)
        {
            fprintf(stderr, "gpu: oversized (%d,%d) (%d,%d) (%d,%d), packet 0x%08x cmd %02x\n",
                    v0->x, v0->y, v1->x, v1->y, v2->x, v2->y, (unsigned)(uintptr_t)trace_tag,
                    trace_tag ? trace_tag[1] >> 24 : 0);
            if (trace_tag != NULL)
            {
                int k;

                for (k = 0; k < 12; k++)
                {
                    fprintf(stderr, " %08x", trace_tag[k]);
                }
                fprintf(stderr, "\n");
            }
        }
        return; // the GPU skips oversized polygons
    }
    minx = minx < env.clip_x1 ? env.clip_x1 : minx;
    miny = miny < env.clip_y1 ? env.clip_y1 : miny;
    maxx = maxx > env.clip_x2 ? env.clip_x2 : maxx;
    maxy = maxy > env.clip_y2 ? env.clip_y2 : maxy;
    tl0  = top_left(v1, v2);
    tl1  = top_left(v2, v0);
    tl2  = top_left(v0, v1);

    for (y = miny; y <= maxy; y++)
    {
        for (x = minx; x <= maxx; x++)
        {
            int64_t w0 = edge(v1, v2, x, y);
            int64_t w1 = edge(v2, v0, x, y);
            int64_t w2 = edge(v0, v1, x, y);
            int r, g, bl, u, v;

            if (w0 < 0 || w1 < 0 || w2 < 0)
            {
                continue;
            }
            if ((w0 == 0 && !tl0) || (w1 == 0 && !tl1) || (w2 == 0 && !tl2))
            {
                continue;
            }
            if (ctx->shaded)
            {
                r  = (int)((w0 * v0->r + w1 * v1->r + w2 * v2->r) / area);
                g  = (int)((w0 * v0->g + w1 * v1->g + w2 * v2->g) / area);
                bl = (int)((w0 * v0->b + w1 * v1->b + w2 * v2->b) / area);
            }
            else
            {
                r  = v0->r;
                g  = v0->g;
                bl = v0->b;
            }
            u = v = 0;
            if (ctx->textured)
            {
                u = (int)((w0 * v0->u + w1 * v1->u + w2 * v2->u) / area);
                v = (int)((w0 * v0->v + w1 * v1->v + w2 * v2->v) / area);
            }
            shade(ctx, x, y, r, g, bl, u, v);
        }
    }
}

// --- command decoding ------------------------------------------------------------------------

static void color_of(uint32_t w, VTX *v)
{
    v->r = (int)(w & 0xFF);
    v->g = (int)((w >> 8) & 0xFF);
    v->b = (int)((w >> 16) & 0xFF);
}

static void xy_of(uint32_t w, VTX *v)
{
    v->x = sext11(w) + env.off_x;
    v->y = sext11(w >> 16) + env.off_y;
}

static int poly_size(uint32_t cmd)
{
    int n   = (cmd & 0x08) ? 4 : 3;
    int tex = (cmd & 0x04) ? 1 : 0;
    return 1 + n * (1 + tex) + ((cmd & 0x10) ? n - 1 : 0);
}

static void do_poly(const uint32_t *w)
{
    uint32_t cmd = w[0] >> 24;
    int n        = (cmd & 0x08) ? 4 : 3;
    VTX v[4];
    DRAWCTX ctx;
    int i, k = 0;

    memset(&ctx, 0, sizeof(ctx));
    ctx.shaded   = (cmd & 0x10) != 0;
    ctx.textured = (cmd & 0x04) != 0;
    ctx.semi     = (cmd & 0x02) != 0;
    ctx.raw      = (cmd & 0x01) != 0;
    for (i = 0; i < n; i++)
    {
        if (i == 0 || ctx.shaded)
        {
            color_of(w[k++], &v[i]);
        }
        else
        {
            v[i].r = v[0].r;
            v[i].g = v[0].g;
            v[i].b = v[0].b;
        }
        xy_of(w[k++], &v[i]);
        v[i].u = v[i].v = 0;
        if (ctx.textured)
        {
            uint32_t uv = w[k++];
            v[i].u      = (int)(uv & 0xFF);
            v[i].v      = (int)((uv >> 8) & 0xFF);
            if (i == 0)
            {
                ctx.clut_x = (int)((uv >> 16) & 0x3F) * 16;
                ctx.clut_y = (int)((uv >> 22) & 0x1FF);
            }
            else if (i == 1)
            {
                set_texpage(uv >> 16); // a textured polygon also sets the texpage state
            }
        }
    }
    if (ctx.raw)
    {
        for (i = 0; i < n; i++)
        {
            v[i].r = v[i].g = v[i].b = 0x80;
        }
    }
    ctx.tp_x      = env.tp_x;
    ctx.tp_y      = env.tp_y;
    ctx.depth     = env.tp_depth;
    ctx.semi_mode = env.tp_semi;
    ctx.dither    = env.dither && (ctx.shaded || (ctx.textured && !ctx.raw));
    draw_tri(&v[0], &v[1], &v[2], &ctx);
    if (n == 4)
    {
        draw_tri(&v[1], &v[2], &v[3], &ctx);
    }
    stats.polygons++;
}

static int rect_size(uint32_t cmd)
{
    return 2 + ((cmd & 0x04) ? 1 : 0) + (((cmd >> 3) & 3) == 0 ? 1 : 0);
}

static void do_rect(const uint32_t *w)
{
    uint32_t cmd = w[0] >> 24;
    VTX v;
    DRAWCTX ctx;
    int k = 1, width, height, x, y, u0 = 0, v0 = 0;

    memset(&ctx, 0, sizeof(ctx));
    ctx.textured = (cmd & 0x04) != 0;
    ctx.semi     = (cmd & 0x02) != 0;
    ctx.raw      = (cmd & 0x01) != 0;
    color_of(w[0], &v);
    xy_of(w[k++], &v);
    if (ctx.textured)
    {
        uint32_t uv = w[k++];
        u0          = (int)(uv & 0xFF);
        v0          = (int)((uv >> 8) & 0xFF);
        ctx.clut_x  = (int)((uv >> 16) & 0x3F) * 16;
        ctx.clut_y  = (int)((uv >> 22) & 0x1FF);
    }
    switch ((cmd >> 3) & 3)
    {
        case 0:
            width  = (int)(w[k] & 0x3FF);
            height = (int)((w[k] >> 16) & 0x1FF);
            break;
        case 1:
            width = height = 1;
            break;
        case 2:
            width = height = 8;
            break;
        default:
            width = height = 16;
            break;
    }
    if (ctx.raw)
    {
        v.r = v.g = v.b = 0x80;
    }
    ctx.tp_x      = env.tp_x;
    ctx.tp_y      = env.tp_y;
    ctx.depth     = env.tp_depth;
    ctx.semi_mode = env.tp_semi;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            shade(&ctx, v.x + x, v.y + y, v.r, v.g, v.b, u0 + x, v0 + y);
        }
    }
    stats.rects++;
}

static void draw_line(const VTX *a, const VTX *b, int shaded, int semi)
{
    int dx = b->x - a->x, dy = b->y - a->y;
    int adx = abs(dx), ady = abs(dy);
    int steps = adx > ady ? adx : ady;
    int i;

    if (adx >= GPU_VRAM_W || ady >= GPU_VRAM_H)
    {
        return;
    }
    for (i = 0; i <= steps; i++)
    {
        int x = steps ? a->x + (dx * i + (dx >= 0 ? steps / 2 : -steps / 2)) / steps : a->x;
        int y = steps ? a->y + (dy * i + (dy >= 0 ? steps / 2 : -steps / 2)) / steps : a->y;
        int r = a->r, g = a->g, bl = a->b;

        if (shaded && steps)
        {
            r  = a->r + (b->r - a->r) * i / steps;
            g  = a->g + (b->g - a->g) * i / steps;
            bl = a->b + (b->b - a->b) * i / steps;
        }
        plot(x, y, rgb15_at(r, g, bl, shaded && env.dither, x, y), semi, env.tp_semi);
    }
}

// Returns the words used.
static int do_line(const uint32_t *w, int avail)
{
    uint32_t cmd = w[0] >> 24;
    int shaded   = (cmd & 0x10) != 0;
    int semi     = (cmd & 0x02) != 0;
    int poly     = (cmd & 0x08) != 0;
    VTX prev, cur;
    int k = 1;

    color_of(w[0], &prev);
    xy_of(w[k++], &prev);
    for (;;)
    {
        if (k >= avail)
        {
            break;
        }
        if (poly && (w[k] & 0xF000F000u) == 0x50005000u)
        {
            k++; // terminator
            break;
        }
        if (shaded)
        {
            color_of(w[k++], &cur);
        }
        else
        {
            cur.r = prev.r;
            cur.g = prev.g;
            cur.b = prev.b;
        }
        if (k >= avail)
        {
            break;
        }
        xy_of(w[k++], &cur);
        draw_line(&prev, &cur, shaded, semi);
        prev = cur;
        if (!poly)
        {
            break;
        }
    }
    stats.lines++;
    return k;
}

static void do_fill(const uint32_t *w)
{
    int x0 = (int)(w[1] & 0x3F0), y0 = (int)((w[1] >> 16) & 0x1FF);
    int width = (int)(((w[2] & 0x3FF) + 0xF) & ~0xFu), height = (int)((w[2] >> 16) & 0x1FF);
    uint16_t c = rgb15((int)(w[0] & 0xFF), (int)((w[0] >> 8) & 0xFF), (int)((w[0] >> 16) & 0xFF));
    int x, y;

    if (c == 0 && getenv("PORT_GPU_TRACE") != NULL)
    {
        c = 0x7C1F; // debugging: black fills in magenta, to tell them from black polygons
    }

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            VRAM(x0 + x, y0 + y) = c;
        }
    }
    stats.fills++;
}

static void do_env(uint32_t w)
{
    switch (w >> 24)
    {
        case 0xE1:
            set_texpage(w);
            env.dither = (int)((w >> 9) & 1);
            break;
        case 0xE2:
            env.tw_mask_x = (int)(w & 0x1F);
            env.tw_mask_y = (int)((w >> 5) & 0x1F);
            env.tw_off_x  = (int)((w >> 10) & 0x1F);
            env.tw_off_y  = (int)((w >> 15) & 0x1F);
            break;
        case 0xE3:
            env.clip_x1 = (int)(w & 0x3FF);
            env.clip_y1 = (int)((w >> 10) & 0x1FF);
            break;
        case 0xE4:
            env.clip_x2 = (int)(w & 0x3FF);
            env.clip_y2 = (int)((w >> 10) & 0x1FF);
            break;
        case 0xE5:
            env.off_x = sext11(w);
            env.off_y = sext11(w >> 11);
            break;
        case 0xE6:
            env.mask_set   = (int)(w & 1);
            env.mask_check = (int)((w >> 1) & 1);
            break;
    }
}

void gpu_gp0(const uint32_t *w, int count)
{
    int i = 0;

    while (i < count)
    {
        uint32_t cmd = w[i] >> 24;
        int size     = 1;

        stats.commands++;
        if (cmd == 0x02)
        {
            size = 3;
            if (i + size <= count)
            {
                do_fill(&w[i]);
            }
        }
        else if (cmd >= 0x20 && cmd < 0x40)
        {
            size = poly_size(cmd);
            if (i + size <= count)
            {
                do_poly(&w[i]);
            }
        }
        else if (cmd >= 0x40 && cmd < 0x60)
        {
            size = do_line(&w[i], count - i);
        }
        else if (cmd >= 0x60 && cmd < 0x80)
        {
            size = rect_size(cmd);
            if (i + size <= count)
            {
                do_rect(&w[i]);
            }
        }
        else if (cmd >= 0x80 && cmd < 0xA0)
        {
            size = 4;
            if (i + size <= count)
            {
                GPU_RECT r;
                r.x = (int16_t)(w[i + 1] & 0x3FF);
                r.y = (int16_t)((w[i + 1] >> 16) & 0x1FF);
                r.w = (int16_t)(w[i + 3] & 0xFFFF);
                r.h = (int16_t)(w[i + 3] >> 16);
                gpu_move_image(&r, (int)(w[i + 2] & 0x3FF), (int)((w[i + 2] >> 16) & 0x1FF));
            }
        }
        else if (cmd >= 0xA0 && cmd < 0xC0)
        {
            GPU_RECT r;
            r.x  = (int16_t)(w[i + 1] & 0x3FF);
            r.y  = (int16_t)((w[i + 1] >> 16) & 0x1FF);
            r.w  = (int16_t)(w[i + 2] & 0xFFFF);
            r.h  = (int16_t)(w[i + 2] >> 16);
            size = 3 + (r.w * r.h + 1) / 2;
            if (i + size <= count)
            {
                gpu_load_image(&r, &w[i + 3]);
            }
        }
        else if (cmd >= 0xC0 && cmd < 0xE0)
        {
            size = 3; // VRAM-to-CPU goes through gpu_store_image instead
        }
        else if (cmd >= 0xE0)
        {
            do_env(w[i]);
        }
        else if (cmd != 0x00 && cmd != 0x01)
        {
            stats.unknown++;
        }
        i += size;
    }
}


void gpu_draw_prim(const uint32_t *tag)
{
    int len = (int)(tag[0] >> 24);

    trace_tag = tag;
    stats.packets++;
    if (len != 0)
    {
        gpu_gp0(tag + 1, len);
    }
}

void gpu_draw_ot(uint32_t addr)
{
    int guard;

    for (guard = 0; guard < (1 << 22); guard++)
    {
        const uint32_t *tag = psx_ptr(addr);
        uint32_t next;

        if (tag == NULL)
        {
            break;
        }
        gpu_draw_prim(tag);
        next = tag[0] & 0xFFFFFF;
        if (next == 0xFFFFFF)
        {
            break;
        }
        addr = next;
    }
}

// --- transfers -------------------------------------------------------------------------------

void gpu_load_image(const GPU_RECT *r, const void *src)
{
    const uint16_t *s = src;
    int x, y;

    for (y = 0; y < r->h; y++)
    {
        for (x = 0; x < r->w; x++)
        {
            VRAM(r->x + x, r->y + y) = *s++;
        }
    }
}

void gpu_store_image(const GPU_RECT *r, void *dst)
{
    uint16_t *d = dst;
    int x, y;

    for (y = 0; y < r->h; y++)
    {
        for (x = 0; x < r->w; x++)
        {
            *d++ = VRAM(r->x + x, r->y + y);
        }
    }
}

void gpu_move_image(const GPU_RECT *r, int dx, int dy)
{
    uint16_t *tmp = malloc(sizeof(uint16_t) * (size_t)(r->w * r->h));

    if (tmp == NULL)
    {
        return;
    }
    gpu_store_image(r, tmp);
    {
        GPU_RECT d = *r;
        d.x        = (int16_t)dx;
        d.y        = (int16_t)dy;
        gpu_load_image(&d, tmp);
    }
    free(tmp);
}

void gpu_clear_image(const GPU_RECT *r, uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t c = rgb15(red, green, blue);
    int x, y;

    for (y = 0; y < r->h; y++)
    {
        for (x = 0; x < r->w; x++)
        {
            VRAM(r->x + x, r->y + y) = c;
        }
    }
}
