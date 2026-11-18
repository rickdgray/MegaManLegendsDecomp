// Software GTE. See gte.h.
#include "gte.h"

#include <string.h>

static uint32_t data[32];
static uint32_t ctrl[32];
static uint32_t flag;

// FLAG bits that the hardware reports (psx-spx, "GTE Saturation").
#define FLAG_IR1   (1u << 24)
#define FLAG_IR2   (1u << 23)
#define FLAG_IR3   (1u << 22)
#define FLAG_COLR  (1u << 21)
#define FLAG_COLG  (1u << 20)
#define FLAG_COLB  (1u << 19)
#define FLAG_SZ3   (1u << 18)
#define FLAG_DIV   (1u << 17)
#define FLAG_SX2   (1u << 14)
#define FLAG_SY2   (1u << 13)
#define FLAG_IR0   (1u << 12)
#define FLAG_ERROR 0x7F87E000u

void gte_reset(void)
{
    memset(data, 0, sizeof(data));
    memset(ctrl, 0, sizeof(ctrl));
    flag = 0;
}

static int32_t sext16(uint32_t v)
{
    return (int16_t)(v & 0xFFFF);
}

// --- register file -------------------------------------------------------------------------

static int32_t clamp_i(int64_t v, int64_t lo, int64_t hi, uint32_t bit)
{
    if (v < lo)
    {
        flag |= bit;
        return (int32_t)lo;
    }
    if (v > hi)
    {
        flag |= bit;
        return (int32_t)hi;
    }
    return (int32_t)v;
}

uint32_t gte_read_data(int reg)
{
    int32_t r, g, b;

    switch (reg)
    {
        case 1:
        case 3:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
            return (uint32_t)sext16(data[reg]);
        case 7:
        case 16:
        case 17:
        case 18:
        case 19:
            return data[reg] & 0xFFFF;
        case 15:
            return data[14];
        case 28:
        case 29:
            r = clamp_i(sext16(data[9]) >> 7, 0, 0x1F, 0);
            g = clamp_i(sext16(data[10]) >> 7, 0, 0x1F, 0);
            b = clamp_i(sext16(data[11]) >> 7, 0, 0x1F, 0);
            return (uint32_t)(r | (g << 5) | (b << 10));
        default:
            return data[reg];
    }
}

void gte_write_data(int reg, uint32_t value)
{
    uint32_t v;
    int n;

    switch (reg)
    {
        case 1:
        case 3:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
            data[reg] = (uint32_t)sext16(value);
            break;
        case 7:
        case 16:
        case 17:
        case 18:
        case 19:
            data[reg] = value & 0xFFFF;
            break;
        case 15: // SXYP pushes the screen XY FIFO
            data[12] = data[13];
            data[13] = data[14];
            data[14] = value;
            break;
        case 28: // IRGB expands into IR1..IR3
            data[28] = value & 0x7FFF;
            data[9]  = (value & 0x1F) << 7;
            data[10] = ((value >> 5) & 0x1F) << 7;
            data[11] = ((value >> 10) & 0x1F) << 7;
            break;
        case 29: // ORGB is read-only
            break;
        case 30: // LZCS: LZCR counts the leading bits equal to the sign bit
            data[30] = value;
            v        = (value & 0x80000000u) ? ~value : value;
            for (n = 0; n < 32 && !(v & 0x80000000u); n++)
            {
                v <<= 1;
            }
            data[31] = (uint32_t)n;
            break;
        case 31:
            break;
        default:
            data[reg] = value;
            break;
    }
}

uint32_t gte_read_ctrl(int reg)
{
    switch (reg)
    {
        case 4:
        case 12:
        case 20:
        case 26: // H reads back sign-extended (a hardware quirk)
        case 27:
        case 29:
        case 30:
            return (uint32_t)sext16(ctrl[reg]);
        case 31:
            return flag | ((flag & FLAG_ERROR) ? 0x80000000u : 0);
        default:
            return ctrl[reg];
    }
}

void gte_write_ctrl(int reg, uint32_t value)
{
    if (reg == 31)
    {
        flag = value & 0x7FFFF000u;
        return;
    }
    ctrl[reg] = value;
}

// --- helpers -------------------------------------------------------------------------------

// Element (row, col) of the 3x3 matrix whose five packed words start at control register base.
static int32_t mat(int base, int row, int col)
{
    int k      = row * 3 + col;
    uint32_t w = ctrl[base + k / 2];

    return (k & 1) ? (int16_t)(w >> 16) : (int16_t)(w & 0xFFFF);
}

static void vec(int v, int32_t out[3])
{
    if (v == 3)
    {
        out[0] = sext16(data[9]);
        out[1] = sext16(data[10]);
        out[2] = sext16(data[11]);
        return;
    }
    out[0] = (int16_t)(data[v * 2] & 0xFFFF);
    out[1] = (int16_t)(data[v * 2] >> 16);
    out[2] = sext16(data[v * 2 + 1]);
}

static void set_mac_ir(int64_t m1, int64_t m2, int64_t m3, int sf, int lm)
{
    int shift  = sf ? 12 : 0;
    int32_t lo = lm ? 0 : -0x8000;

    data[25] = (uint32_t)(int32_t)(m1 >> shift);
    data[26] = (uint32_t)(int32_t)(m2 >> shift);
    data[27] = (uint32_t)(int32_t)(m3 >> shift);
    data[9]  = (uint32_t)clamp_i((int32_t)data[25], lo, 0x7FFF, FLAG_IR1);
    data[10] = (uint32_t)clamp_i((int32_t)data[26], lo, 0x7FFF, FLAG_IR2);
    data[11] = (uint32_t)clamp_i((int32_t)data[27], lo, 0x7FFF, FLAG_IR3);
}

static void push_sz(int32_t z)
{
    data[16] = data[17];
    data[17] = data[18];
    data[18] = data[19];
    data[19] = (uint32_t)clamp_i(z, 0, 0xFFFF, FLAG_SZ3);
}

static void push_color(int32_t r, int32_t g, int32_t b)
{
    uint32_t code = data[6] >> 24;

    r        = clamp_i(r, 0, 0xFF, FLAG_COLR);
    g        = clamp_i(g, 0, 0xFF, FLAG_COLG);
    b        = clamp_i(b, 0, 0xFF, FLAG_COLB);
    data[20] = data[21];
    data[21] = data[22];
    data[22] = (uint32_t)r | ((uint32_t)g << 8) | ((uint32_t)b << 16) | (code << 24);
}

// The hardware's unsigned Newton-Raphson division of H by SZ3 (psx-spx "GTE Division").
static uint32_t gte_divide(uint32_t h, uint32_t sz3)
{
    static uint8_t unr[0x101];
    static int unr_ready;
    uint32_t n, d, u;
    int z, i;

    if (!unr_ready)
    {
        for (i = 0; i <= 0x100; i++)
        {
            int v  = (0x40000 / (i + 0x100) + 1) / 2 - 0x101;
            unr[i] = (uint8_t)(v < 0 ? 0 : v);
        }
        unr_ready = 1;
    }
    if (h >= sz3 * 2)
    {
        flag |= FLAG_DIV;
        return 0x1FFFF;
    }
    for (z = 0; z < 16 && !(sz3 & (0x8000u >> z)); z++)
    {
    }
    n = h << z;
    d = sz3 << z;
    u = unr[(d - 0x7FC0) >> 7] + 0x101;
    d = (0x2000080 - d * u) >> 8;
    d = (0x0000080 + d * u) >> 8;
    n = (uint32_t)(((uint64_t)n * d + 0x8000) >> 16);
    return n > 0x1FFFF ? 0x1FFFF : n;
}

static void rtp(int v, int sf, int lm, int last)
{
    int32_t vv[3];
    int64_t m[3];
    int64_t mac0;
    uint32_t div;
    int i;
    int32_t sx, sy;

    vec(v, vv);
    for (i = 0; i < 3; i++)
    {
        m[i] = ((int64_t)(int32_t)ctrl[5 + i] << 12) + (int64_t)mat(0, i, 0) * vv[0] +
               (int64_t)mat(0, i, 1) * vv[1] + (int64_t)mat(0, i, 2) * vv[2];
    }
    set_mac_ir(m[0], m[1], m[2], sf, lm);
    push_sz((int32_t)(m[2] >> 12));

    div      = gte_divide(ctrl[26] & 0xFFFF, data[19]);
    mac0     = (int64_t)div * sext16(data[9]) + (int32_t)ctrl[24];
    sx       = clamp_i(mac0 >> 16, -0x400, 0x3FF, FLAG_SX2);
    mac0     = (int64_t)div * sext16(data[10]) + (int32_t)ctrl[25];
    sy       = clamp_i(mac0 >> 16, -0x400, 0x3FF, FLAG_SY2);
    data[12] = data[13];
    data[13] = data[14];
    data[14] = ((uint32_t)sx & 0xFFFF) | ((uint32_t)sy << 16);
    if (last)
    {
        mac0     = (int64_t)div * sext16(ctrl[27]) + (int32_t)ctrl[28];
        data[24] = (uint32_t)(int32_t)mac0;
        data[8]  = (uint32_t)clamp_i(mac0 >> 12, 0, 0x1000, FLAG_IR0);
    }
}

// --- commands ------------------------------------------------------------------------------

void gte_rtps(const GTE_OP *op)
{
    flag = 0;
    rtp(0, op->sf, op->lm, 1);
}

void gte_rtpt(const GTE_OP *op)
{
    flag = 0;
    rtp(0, op->sf, op->lm, 0);
    rtp(1, op->sf, op->lm, 0);
    rtp(2, op->sf, op->lm, 1);
}

void gte_nclip(void)
{
    int32_t x0 = (int16_t)(data[12] & 0xFFFF), y0 = (int16_t)(data[12] >> 16);
    int32_t x1 = (int16_t)(data[13] & 0xFFFF), y1 = (int16_t)(data[13] >> 16);
    int32_t x2 = (int16_t)(data[14] & 0xFFFF), y2 = (int16_t)(data[14] >> 16);

    flag     = 0;
    data[24] = (uint32_t)(x0 * y1 + x1 * y2 + x2 * y0 - x0 * y2 - x1 * y0 - x2 * y1);
}

void gte_avsz3(void)
{
    int64_t m = (int64_t)sext16(ctrl[29]) * (int64_t)(data[17] + data[18] + data[19]);

    flag     = 0;
    data[24] = (uint32_t)(int32_t)m;
    data[7]  = (uint32_t)clamp_i(m >> 12, 0, 0xFFFF, FLAG_SZ3);
}

void gte_avsz4(void)
{
    int64_t m = (int64_t)sext16(ctrl[30]) * (int64_t)(data[16] + data[17] + data[18] + data[19]);

    flag     = 0;
    data[24] = (uint32_t)(int32_t)m;
    data[7]  = (uint32_t)clamp_i(m >> 12, 0, 0xFFFF, FLAG_SZ3);
}

void gte_dpcs(const GTE_OP *op)
{
    int64_t m[3], fc;
    int32_t ir0 = sext16(data[8]);
    int shift   = op->sf ? 12 : 0;
    int i;

    flag = 0;
    for (i = 0; i < 3; i++)
    {
        m[i] = (int64_t)((data[6] >> (8 * i)) & 0xFF) << 16;
        fc   = (int64_t)(int32_t)ctrl[21 + i] << 12;
        // IR = (FC - MAC) >> shift, saturated; MAC += IR * IR0
        m[i] += (int64_t)clamp_i((fc - m[i]) >> shift, -0x8000, 0x7FFF, FLAG_IR1 >> i) * ir0;
    }
    set_mac_ir(m[0], m[1], m[2], op->sf, op->lm);
    push_color((int32_t)data[25] >> 4, (int32_t)data[26] >> 4, (int32_t)data[27] >> 4);
}

void gte_mvmva(const GTE_OP *op)
{
    int32_t vv[3];
    int64_t m[3];
    int base = op->mx == 0 ? 0 : op->mx == 1 ? 8 : 16;
    int i;

    flag = 0;
    vec(op->v, vv);
    for (i = 0; i < 3; i++)
    {
        int64_t t = 0;
        if (op->cv == 0)
        {
            t = (int64_t)(int32_t)ctrl[5 + i] << 12;
        }
        else if (op->cv == 1)
        {
            t = (int64_t)(int32_t)ctrl[13 + i] << 12;
        }
        else if (op->cv == 2)
        {
            t = (int64_t)(int32_t)ctrl[21 + i] << 12;
        }
        m[i] = t + (int64_t)mat(base, i, 0) * vv[0] + (int64_t)mat(base, i, 1) * vv[1] +
               (int64_t)mat(base, i, 2) * vv[2];
    }
    set_mac_ir(m[0], m[1], m[2], op->sf, op->lm);
}

// --- the rest of the command set (psx-spx, "GTE Coordinate Calculation Commands", "GTE
// General Purpose Calculation Commands", "GTE Color Calculation Commands") ---------------------
//
// Used by the PsyQ libgte routines that the port runs from the retail image (mips_cpu.c):
// NormalColorCol is NCCS, OuterProduct0 is OP, Square0 is SQR, and so on.

// MAC + (FC - MAC) * IR0, the depth-cue interpolation shared by DPCS, DPCT, DCPL, INTPL, NCDS,
// NCDT and CDP. m[] holds the MAC values before the final shift.
static void interpolate(int64_t m[3], int sf)
{
    int32_t ir0 = sext16(data[8]);
    int shift   = sf ? 12 : 0;
    int i;

    for (i = 0; i < 3; i++)
    {
        int64_t fc = (int64_t)(int32_t)ctrl[21 + i] << 12;
        m[i] += (int64_t)clamp_i((fc - m[i]) >> shift, -0x8000, 0x7FFF, FLAG_IR1 >> i) * ir0;
    }
}

static void color_out(int64_t m[3], int sf, int lm)
{
    set_mac_ir(m[0], m[1], m[2], sf, lm);
    push_color((int32_t)data[25] >> 4, (int32_t)data[26] >> 4, (int32_t)data[27] >> 4);
}

// Background colour plus colour matrix times IR: the second stage of the lighting commands.
static void color_matrix_stage(int sf, int lm)
{
    int32_t ir[3] = {sext16(data[9]), sext16(data[10]), sext16(data[11])};
    int64_t m[3];
    int i;

    for (i = 0; i < 3; i++)
    {
        m[i] = ((int64_t)(int32_t)ctrl[13 + i] << 12) + (int64_t)mat(16, i, 0) * ir[0] +
               (int64_t)mat(16, i, 1) * ir[1] + (int64_t)mat(16, i, 2) * ir[2];
    }
    set_mac_ir(m[0], m[1], m[2], sf, lm);
}

// Light matrix times vector v, then the colour-matrix stage. Leaves the result in IR1..IR3.
static void light_stages(int v, int sf, int lm)
{
    int32_t vv[3];
    int64_t m[3];
    int i;

    vec(v, vv);
    for (i = 0; i < 3; i++)
    {
        m[i] = (int64_t)mat(8, i, 0) * vv[0] + (int64_t)mat(8, i, 1) * vv[1] +
               (int64_t)mat(8, i, 2) * vv[2];
    }
    set_mac_ir(m[0], m[1], m[2], sf, lm);
    color_matrix_stage(sf, lm);
}

// [R*IR1, G*IR2, B*IR3] << 4 with the RGBC register's colour.
static void color_times_ir(int64_t m[3])
{
    int i;

    for (i = 0; i < 3; i++)
    {
        m[i] = ((int64_t)((data[6] >> (8 * i)) & 0xFF) * sext16(data[9 + i])) << 4;
    }
}

static void ncs(int v, int sf, int lm)
{
    int64_t m[3];

    light_stages(v, sf, lm);
    m[0] = (int64_t)(int32_t)data[25] << (sf ? 12 : 0);
    m[1] = (int64_t)(int32_t)data[26] << (sf ? 12 : 0);
    m[2] = (int64_t)(int32_t)data[27] << (sf ? 12 : 0);
    color_out(m, sf, lm);
}

static void nccs(int v, int sf, int lm)
{
    int64_t m[3];

    light_stages(v, sf, lm);
    color_times_ir(m);
    color_out(m, sf, lm);
}

static void ncds(int v, int sf, int lm)
{
    int64_t m[3];

    light_stages(v, sf, lm);
    color_times_ir(m);
    interpolate(m, sf);
    color_out(m, sf, lm);
}

static void dpcs_rgb(uint32_t rgb, int sf, int lm)
{
    int64_t m[3];
    int i;

    for (i = 0; i < 3; i++)
    {
        m[i] = (int64_t)((rgb >> (8 * i)) & 0xFF) << 16;
    }
    interpolate(m, sf);
    color_out(m, sf, lm);
}

// Executes a COP2 command word (the low 25 bits of the instruction).
void gte_command(uint32_t word)
{
    GTE_OP op;
    int64_t m[3];
    int32_t ir[3], d[3];
    int i, sf, lm;

    op.sf = (word >> 19) & 1;
    op.mx = (word >> 17) & 3;
    op.v  = (word >> 15) & 3;
    op.cv = (word >> 13) & 3;
    op.lm = (word >> 10) & 1;
    sf    = op.sf;
    lm    = op.lm;
    switch (word & 0x3F)
    {
        case 0x01:
            gte_rtps(&op);
            return;
        case 0x06:
            gte_nclip();
            return;
        case 0x0C: // OP: outer product of IR with the rotation matrix diagonal
            flag  = 0;
            ir[0] = sext16(data[9]);
            ir[1] = sext16(data[10]);
            ir[2] = sext16(data[11]);
            d[0]  = mat(0, 0, 0);
            d[1]  = mat(0, 1, 1);
            d[2]  = mat(0, 2, 2);
            set_mac_ir((int64_t)ir[2] * d[1] - (int64_t)ir[1] * d[2],
                       (int64_t)ir[0] * d[2] - (int64_t)ir[2] * d[0],
                       (int64_t)ir[1] * d[0] - (int64_t)ir[0] * d[1], sf, lm);
            return;
        case 0x10:
            gte_dpcs(&op);
            return;
        case 0x11: // INTPL
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                m[i] = (int64_t)sext16(data[9 + i]) << 12;
            }
            interpolate(m, sf);
            color_out(m, sf, lm);
            return;
        case 0x12:
            gte_mvmva(&op);
            return;
        case 0x13:
            flag = 0;
            ncds(0, sf, lm);
            return;
        case 0x14: // CDP
            flag = 0;
            color_matrix_stage(sf, lm);
            color_times_ir(m);
            interpolate(m, sf);
            color_out(m, sf, lm);
            return;
        case 0x16:
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                ncds(i, sf, lm);
            }
            return;
        case 0x1B:
            flag = 0;
            nccs(0, sf, lm);
            return;
        case 0x1C: // CC
            flag = 0;
            color_matrix_stage(sf, lm);
            color_times_ir(m);
            color_out(m, sf, lm);
            return;
        case 0x1E:
            flag = 0;
            ncs(0, sf, lm);
            return;
        case 0x20:
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                ncs(i, sf, lm);
            }
            return;
        case 0x28: // SQR
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                ir[i] = sext16(data[9 + i]);
            }
            set_mac_ir((int64_t)ir[0] * ir[0], (int64_t)ir[1] * ir[1], (int64_t)ir[2] * ir[2], sf,
                       lm);
            return;
        case 0x29: // DCPL
            flag = 0;
            color_times_ir(m);
            interpolate(m, sf);
            color_out(m, sf, lm);
            return;
        case 0x2A: // DPCT: three times DPCS on the colour FIFO's oldest entry
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                dpcs_rgb(data[20], sf, lm);
            }
            return;
        case 0x2D:
            gte_avsz3();
            return;
        case 0x2E:
            gte_avsz4();
            return;
        case 0x30:
            gte_rtpt(&op);
            return;
        case 0x3D: // GPF
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                m[i] = (int64_t)sext16(data[9 + i]) * sext16(data[8]);
            }
            color_out(m, sf, lm);
            return;
        case 0x3E: // GPL
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                m[i] = ((int64_t)(int32_t)data[25 + i] << (sf ? 12 : 0)) +
                       (int64_t)sext16(data[9 + i]) * sext16(data[8]);
            }
            color_out(m, sf, lm);
            return;
        case 0x3F:
            flag = 0;
            for (i = 0; i < 3; i++)
            {
                nccs(i, sf, lm);
            }
            return;
        default:
            flag = 0;
            return;
    }
}
