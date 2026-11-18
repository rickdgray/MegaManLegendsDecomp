// Software MDEC. See mdec.h. The decoding follows the publicly documented hardware model
// (no-cash "psx-spx", "MDEC"): run-length codes with the quantization step in the DC word,
// coefficients in zigzag order, dequantized with the table entry of their position in the code
// sequence, a two-pass IDCT on the uploaded scale table, and the fixed YUV to RGB matrix.
#include "mdec.h"

#include <stdlib.h>
#include <string.h>

#define IN_MAX  (1u << 18) // words of parameters for one command
#define OUT_MAX (1u << 18) // words of decoded pixels

static const uint8_t zigzag[64] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,  12, 19, 26, 33, 40, 48,
    41, 34, 27, 20, 13, 6,  7,  14, 21, 28, 35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23,
    30, 37, 44, 51, 58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
};

static uint32_t cmd;
static uint32_t params_left;
static uint32_t *in;
static uint32_t in_count;
static uint32_t *out;
static uint32_t out_count, out_pos;
static uint8_t qt_y[64], qt_uv[64];
static int16_t scale[64];

void mdec_reset(void)
{
    if (in == NULL)
    {
        in  = calloc(IN_MAX, 4);
        out = calloc(OUT_MAX, 4);
    }
    cmd = params_left = in_count = out_count = out_pos = 0;
}

static int32_t sext10(uint32_t v)
{
    return (int32_t)(v << 22) >> 22;
}

static int32_t clampi(int32_t v, int32_t lo, int32_t hi)
{
    return v < lo ? lo : v > hi ? hi : v;
}

static void idct(int32_t *blk)
{
    int32_t tmp[64];
    int32_t *src = blk, *dst = tmp, *t;
    int pass, x, y, z;

    for (pass = 0; pass < 2; pass++)
    {
        for (x = 0; x < 8; x++)
        {
            for (y = 0; y < 8; y++)
            {
                int64_t sum = 0;

                for (z = 0; z < 8; z++)
                {
                    sum += (int64_t)src[y + z * 8] * scale[x + z * 8];
                }
                dst[x + y * 8] = (int32_t)((sum + 0x8000) >> 16);
            }
        }
        t   = src;
        src = dst;
        dst = t;
    }
    // Two passes leave the result back in `blk`.
}

// Decodes one block from the halfword stream; returns 0 when the stream is exhausted.
static int rl_block(const uint16_t *h, uint32_t n, uint32_t *pos, const uint8_t *qt, int32_t *blk)
{
    uint32_t v, k = 0;
    int32_t q, val;

    memset(blk, 0, 64 * sizeof(int32_t));
    do
    {
        if (*pos >= n)
        {
            return 0;
        }
        v = h[(*pos)++];
    } while (v == 0xFE00);
    q   = (int32_t)(v >> 10);
    val = sext10(v & 0x3FF) * qt[0];
    for (;;)
    {
        if (q == 0)
        {
            val = sext10(v & 0x3FF) * 2;
        }
        val                        = clampi(val, -0x400, 0x3FF);
        blk[q > 0 ? zigzag[k] : k] = val;
        if (*pos >= n)
        {
            break;
        }
        v = h[(*pos)++];
        k += (v >> 10) + 1;
        if (k > 63)
        {
            break;
        }
        val = (sext10(v & 0x3FF) * qt[k] * q + 4) >> 3;
    }
    idct(blk);
    return 1;
}

static void put_out(uint32_t w)
{
    if (out_count < OUT_MAX)
    {
        out[out_count++] = w;
    }
}

static void decode(void)
{
    const uint16_t *h = (const uint16_t *)in;
    uint32_t n = in_count * 2, pos = 0;
    int depth = (int)((cmd >> 27) & 3), sgn = (cmd >> 26) & 1;
    uint32_t bit15 = (cmd >> 25) & 1 ? 0x8000u : 0;
    int32_t cr[64], cb[64], y[4][64];
    uint8_t rgb[16 * 16][3];
    int b, px, py, i;

    out_count = out_pos = 0;
    if (depth < 2)
    {
        // Monochrome: one Y block per 8x8 output (8-bit; 4-bit packs two pixels a byte).
        while (rl_block(h, n, &pos, qt_y, y[0]))
        {
            uint8_t pix[64];

            for (i = 0; i < 64; i++)
            {
                int32_t v = clampi(y[0][i], -128, 127);
                pix[i]    = (uint8_t)(sgn ? v : v + 128);
            }
            if (depth == 1)
            {
                for (i = 0; i < 64; i += 4)
                {
                    put_out(pix[i] | pix[i + 1] << 8 | pix[i + 2] << 16 |
                            (uint32_t)pix[i + 3] << 24);
                }
            }
            else
            {
                for (i = 0; i < 64; i += 8)
                {
                    uint32_t w = 0;
                    int j;

                    for (j = 0; j < 8; j++)
                    {
                        w |= (uint32_t)(pix[i + j] >> 4) << (j * 4);
                    }
                    put_out(w);
                }
            }
        }
        return;
    }
    for (;;)
    {
        if (!rl_block(h, n, &pos, qt_uv, cr) || !rl_block(h, n, &pos, qt_uv, cb))
        {
            break;
        }
        for (b = 0; b < 4; b++)
        {
            if (!rl_block(h, n, &pos, qt_y, y[b]))
            {
                return;
            }
        }
        for (b = 0; b < 4; b++)
        {
            int xx = (b & 1) * 8, yy = (b >> 1) * 8;

            for (py = 0; py < 8; py++)
            {
                for (px = 0; px < 8; px++)
                {
                    int ci    = ((px + xx) >> 1) + ((py + yy) >> 1) * 8;
                    int32_t r = cr[ci], bl = cb[ci], lum = y[b][px + py * 8];
                    int32_t g  = (-22525 * bl - 46812 * r) >> 16;
                    int32_t rr = (91881 * r) >> 16, bb = (116130 * bl) >> 16;
                    int32_t c[3];
                    int k;

                    c[0] = clampi(lum + rr, -128, 127);
                    c[1] = clampi(lum + g, -128, 127);
                    c[2] = clampi(lum + bb, -128, 127);
                    for (k = 0; k < 3; k++)
                    {
                        rgb[(px + xx) + (py + yy) * 16][k] = (uint8_t)(sgn ? c[k] : c[k] + 128);
                    }
                }
            }
        }
        if (depth == 3)
        {
            for (i = 0; i < 256; i += 2)
            {
                uint32_t p0 = (uint32_t)(rgb[i][0] >> 3) | (uint32_t)(rgb[i][1] >> 3) << 5 |
                              (uint32_t)(rgb[i][2] >> 3) << 10 | bit15;
                uint32_t p1 = (uint32_t)(rgb[i + 1][0] >> 3) | (uint32_t)(rgb[i + 1][1] >> 3) << 5 |
                              (uint32_t)(rgb[i + 1][2] >> 3) << 10 | bit15;
                put_out(p0 | p1 << 16);
            }
        }
        else
        {
            const uint8_t *bytes = &rgb[0][0];

            for (i = 0; i < 768; i += 4)
            {
                put_out(bytes[i] | bytes[i + 1] << 8 | bytes[i + 2] << 16 |
                        (uint32_t)bytes[i + 3] << 24);
            }
        }
    }
}

static void execute(void)
{
    const uint8_t *bytes = (const uint8_t *)in;

    switch (cmd >> 29)
    {
        case 1:
            decode();
            break;
        case 2:
            memcpy(qt_y, bytes, 64);
            if (cmd & 1)
            {
                memcpy(qt_uv, bytes + 64, 64);
            }
            break;
        case 3:
            memcpy(scale, bytes, sizeof(scale));
            break;
        default:
            break;
    }
    in_count = 0;
}

static void param(uint32_t w)
{
    if (in_count < IN_MAX)
    {
        in[in_count++] = w;
    }
    if (--params_left == 0)
    {
        execute();
    }
}

void mdec_write_cmd(uint32_t word)
{
    if (in == NULL)
    {
        mdec_reset();
    }
    if (params_left > 0)
    {
        param(word);
        return;
    }
    cmd      = word;
    in_count = 0;
    switch (word >> 29)
    {
        case 1:
            params_left = word & 0xFFFF;
            break;
        case 2:
            params_left = (word & 1) ? 32 : 16;
            break;
        case 3:
            params_left = 32;
            break;
        default:
            params_left = 0;
            break;
    }
    if (params_left == 0)
    {
        execute();
    }
}

void mdec_write_ctl(uint32_t word)
{
    if (word & 0x80000000u)
    {
        if (in == NULL)
        {
            mdec_reset();
        }
        cmd = params_left = in_count = 0;
    }
}

uint32_t mdec_read_status(void)
{
    uint32_t s = 0;

    if (out_pos >= out_count)
    {
        s |= 0x80000000u; // output FIFO empty
    }
    s |= ((cmd >> 25) & 0xF) << 23; // depth, signed, bit 15
    s |= (params_left - 1) & 0xFFFF;
    return s;
}

uint32_t mdec_read_data(void)
{
    return out_pos < out_count ? out[out_pos++] : 0;
}

void mdec_dma_in(const uint32_t *src, uint32_t words)
{
    uint32_t i;

    if (in == NULL)
    {
        mdec_reset();
    }
    for (i = 0; i < words && params_left > 0; i++)
    {
        param(src[i]);
    }
}

void mdec_dma_out(uint32_t *dst, uint32_t words)
{
    uint32_t i;

    for (i = 0; i < words; i++)
    {
        dst[i] = out_pos < out_count ? out[out_pos++] : 0;
    }
}
