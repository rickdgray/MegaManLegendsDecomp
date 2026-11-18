// Software SPU. See spu.h.
//
// References for the hardware behaviour: the PS1 register layout as libspu uses it, and the
// publicly documented SPU model (no-cash "psx-spx": ADPCM blocks, ADSR, noise, reverb).
#include "spu.h"
#include "spu_tables.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VOICES 24

// Register offsets (from 0x1F801C00).
#define R_MAIN_VOL_L 0x180
#define R_MAIN_VOL_R 0x182
#define R_REV_VOL_L  0x184
#define R_REV_VOL_R  0x186
#define R_KON_LO     0x188
#define R_KON_HI     0x18A
#define R_KOFF_LO    0x18C
#define R_KOFF_HI    0x18E
#define R_PMON_LO    0x190
#define R_PMON_HI    0x192
#define R_NON_LO     0x194
#define R_NON_HI     0x196
#define R_EON_LO     0x198
#define R_EON_HI     0x19A
#define R_ENDX_LO    0x19C
#define R_ENDX_HI    0x19E
#define R_REV_BASE   0x1A2
#define R_TRANS_ADDR 0x1A6
#define R_FIFO       0x1A8
#define R_CNT        0x1AA
#define R_TRANS_CTL  0x1AC
#define R_STAT       0x1AE
#define R_CD_VOL_L   0x1B0
#define R_CD_VOL_R   0x1B2
#define R_CUR_VOL_L  0x1B8
#define R_CUR_VOL_R  0x1BA
#define R_REVERB     0x1C0 // 32 reverb parameters

#define CNT_ENABLE    0x8000
#define CNT_UNMUTE    0x4000
#define CNT_REVERB    0x0080
#define CNT_CD_REVERB 0x0004
#define CNT_CD_ENABLE 0x0001

enum
{
    PH_OFF,
    PH_ATTACK,
    PH_DECAY,
    PH_SUSTAIN,
    PH_RELEASE
};

typedef struct
{
    int32_t level; // 0..0x7FFF (ADSR) or -0x8000..0x7FFF (volume sweep)
    int32_t wait;  // samples until the next step
} ENVELOPE;

typedef struct
{
    uint32_t start;   // byte addresses in sound RAM
    uint32_t repeat;  // loop address
    uint32_t addr;    // the block being played
    uint32_t counter; // pitch counter: 12 fraction bits
    int16_t block[28];
    int idx;         // next sample in `block`
    uint8_t flags;   // the playing block's loop flags
    int32_t s1, s2;  // ADPCM filter history
    int16_t hist[4]; // the last four samples, newest last (interpolation)
    int phase;
    ENVELOPE adsr;
    ENVELOPE sweep[2]; // volume sweeps, left and right
    int repeat_set;    // the CPU wrote the loop address after key on
    int32_t out;       // last output, before volume (pitch modulation source)
} VOICE;

static uint16_t regs[0x200];
static uint8_t ram[SPU_RAM_BYTES];
static VOICE voices[VOICES];
static uint32_t endx;
static uint32_t trans_addr;
static ENVELOPE main_sweep[2];
static int32_t noise_timer;
static uint16_t noise_level = 1;
// reverb
static uint32_t rev_addr;
static int rev_phase;
static int32_t rev_out_l, rev_out_r;
// The reverb unit's resampling FIRs (spu_tables.h): the last 39 inputs at 44.1 kHz, and the
// last 39 outputs zero-stuffed back to 44.1 kHz; per side.
#define REV_TAPS 39
static int16_t rev_hist_in[2][REV_TAPS], rev_hist_out[2][REV_TAPS];
static int rev_hist_pos;

// CD audio input: a single-producer ring (the drive at each vertical blank) read by the mixer.
#define CD_RING  16384
#define CD_PRIME 3000 // frames buffered before playback starts (sectors arrive in bursts)
static int16_t cd_ring[CD_RING][2];
static uint32_t cd_head, cd_tail; // written / read frames
static int cd_primed;

static const int32_t adpcm_pos[5] = {0, 60, 115, 98, 122};
static const int32_t adpcm_neg[5] = {0, 0, -52, -55, -60};

static int32_t clamp16(int32_t v)
{
    return v < -0x8000 ? -0x8000 : v > 0x7FFF ? 0x7FFF : v;
}

static int32_t mul15(int32_t a, int32_t b)
{
    return (a * b) >> 15;
}

const uint8_t *spu_ram(void)
{
    return ram;
}

void spu_reset(void)
{
    memset(regs, 0, sizeof(regs));
    memset(voices, 0, sizeof(voices));
    memset(main_sweep, 0, sizeof(main_sweep));
    endx        = 0;
    trans_addr  = 0;
    noise_timer = 0;
    noise_level = 1;
    rev_addr    = 0;
    rev_phase   = 0;
    memset(rev_hist_in, 0, sizeof(rev_hist_in));
    memset(rev_hist_out, 0, sizeof(rev_hist_out));
    cd_head = cd_tail = 0;
    cd_primed         = 0;
}

// --- envelopes ------------------------------------------------------------------------------

// One step of the hardware's envelope generator (psx-spx "ADSR/Sweep"): every 2^(shift-11)
// samples the level moves by step << (11-shift); exponential increase slows above 0x6000,
// exponential decrease is proportional to the level.
static void env_tick(ENVELOPE *e, int exponential, int decrease, int shift, int step, int32_t lo,
                     int32_t hi)
{
    int32_t cycles = 1 << (shift > 11 ? shift - 11 : 0);
    int32_t delta  = step << (shift < 11 ? 11 - shift : 0);

    if (exponential && !decrease && e->level > 0x6000)
    {
        cycles *= 4;
    }
    if (exponential && decrease)
    {
        delta = (delta * e->level) >> 15;
    }
    if (--e->wait > 0)
    {
        return;
    }
    e->wait = cycles;
    e->level += delta;
    if (e->level < lo)
    {
        e->level = lo;
    }
    if (e->level > hi)
    {
        e->level = hi;
    }
}

static void adsr_tick(int v, VOICE *vc)
{
    uint16_t lo = regs[v * 8 + 4], hi = regs[v * 8 + 5];

    switch (vc->phase)
    {
        case PH_ATTACK:
            env_tick(&vc->adsr, lo >> 15, 0, (lo >> 10) & 0x1F, 7 - ((lo >> 8) & 3), 0, 0x7FFF);
            if (vc->adsr.level >= 0x7FFF)
            {
                vc->phase     = PH_DECAY;
                vc->adsr.wait = 0;
            }
            break;
        case PH_DECAY:
            env_tick(&vc->adsr, 1, 1, (lo >> 4) & 0xF, -8, 0, 0x7FFF);
            if (vc->adsr.level <= (int32_t)(((lo & 0xF) + 1) * 0x800))
            {
                vc->phase     = PH_SUSTAIN;
                vc->adsr.wait = 0;
            }
            break;
        case PH_SUSTAIN:
        {
            int dec = (hi >> 14) & 1;

            env_tick(&vc->adsr, hi >> 15, dec, (hi >> 8) & 0x1F,
                     dec ? -8 + ((hi >> 6) & 3) : 7 - ((hi >> 6) & 3), 0, 0x7FFF);
            break;
        }
        case PH_RELEASE:
            env_tick(&vc->adsr, (hi >> 5) & 1, 1, hi & 0x1F, -8, 0, 0x7FFF);
            if (vc->adsr.level <= 0)
            {
                vc->phase = PH_OFF;
            }
            break;
        default:
            break;
    }
}

// A volume register: fixed (bit 15 clear: a 15-bit signed volume) or a sweep.
static int32_t volume(uint16_t reg, ENVELOPE *sw)
{
    if (!(reg & 0x8000))
    {
        sw->level = (int16_t)(reg << 1);
        sw->wait  = 0;
        return sw->level;
    }
    {
        int exponential = (reg >> 14) & 1, decrease = (reg >> 13) & 1;
        int step = decrease ? -8 + (reg & 3) : 7 - (reg & 3);

        env_tick(sw, exponential, decrease, (reg >> 2) & 0x1F, step, 0, 0x7FFF);
        return (reg & 0x1000) ? -sw->level : sw->level;
    }
}

// --- voices ---------------------------------------------------------------------------------

static void decode_block(VOICE *vc)
{
    const uint8_t *b = &ram[vc->addr & (SPU_RAM_BYTES - 1) & ~15u];
    int shift = b[0] & 0x0F, filter = (b[0] >> 4) & 7;
    int i;

    if (shift > 12)
    {
        shift = 9; // the hardware treats 13-15 like 9
    }
    if (filter > 4)
    {
        filter = 4;
    }
    vc->flags = b[1];
    if ((vc->flags & 4) && !vc->repeat_set)
    {
        vc->repeat = vc->addr;
    }
    for (i = 0; i < 28; i++)
    {
        int32_t n = (b[2 + i / 2] >> ((i & 1) * 4)) & 0xF;
        int32_t s = ((int32_t)(int16_t)(n << 12)) >> shift;

        s += (vc->s1 * adpcm_pos[filter] + vc->s2 * adpcm_neg[filter] + 32) >> 6;
        s            = clamp16(s);
        vc->s2       = vc->s1;
        vc->s1       = s;
        vc->block[i] = (int16_t)s;
    }
    vc->idx = 0;
}

static int trace = -1; // PORT_SPU_TRACE=1: log key on/off

static void key_on(int v)
{
    VOICE *vc = &voices[v];

    if (trace < 0)
    {
        trace = getenv("PORT_SPU_TRACE") != NULL;
    }
    if (trace)
    {
        fprintf(stderr, "spu: kon %2d start %05X pitch %04X adsr %04X:%04X vol %04X/%04X\n", v,
                (unsigned)regs[v * 8 + 3] * 8, regs[v * 8 + 2], regs[v * 8 + 4], regs[v * 8 + 5],
                regs[v * 8 + 0], regs[v * 8 + 1]);
    }
    vc->start      = (uint32_t)regs[v * 8 + 3] * 8;
    vc->addr       = vc->start;
    vc->counter    = 0;
    vc->s1         = 0;
    vc->s2         = 0;
    vc->repeat_set = 0;
    memset(vc->hist, 0, sizeof(vc->hist));
    vc->phase      = PH_ATTACK;
    vc->adsr.level = 0;
    vc->adsr.wait  = 0;
    endx &= ~(1u << v);
    decode_block(vc);
}

static void key_off(int v)
{
    VOICE *vc = &voices[v];

    if (vc->phase != PH_OFF)
    {
        vc->phase     = PH_RELEASE;
        vc->adsr.wait = 0;
    }
}

// The next sample of a voice's ADPCM stream, moving to the next block (and following the loop
// flags of the one just finished) when needed.
static int16_t next_sample(int v, VOICE *vc)
{
    if (vc->idx >= 28)
    {
        if (vc->flags & 1)
        {
            endx |= 1u << v;
            vc->addr = vc->repeat;
            if (!(vc->flags & 2))
            {
                vc->phase      = PH_OFF; // end without repeat: release and silence at once
                vc->adsr.level = 0;
            }
        }
        else
        {
            vc->addr += 16;
        }
        vc->addr &= SPU_RAM_BYTES - 1;
        decode_block(vc);
    }
    return vc->block[vc->idx++];
}

// The hardware's 4-point Gaussian interpolation (spu_tables.h), on the 8-bit phase in bits 4-11
// of the pitch counter; hist[3] is the newest sample.
static int32_t interpolate(const int16_t *h, uint32_t frac)
{
    uint32_t i = (frac >> 4) & 0xFF;
    int32_t out;

    out = (spu_gauss[0x0FF - i] * h[0]) >> 15;
    out += (spu_gauss[0x1FF - i] * h[1]) >> 15;
    out += (spu_gauss[0x100 + i] * h[2]) >> 15;
    out += (spu_gauss[0x000 + i] * h[3]) >> 15;
    return clamp16(out);
}

static void noise_tick(void)
{
    uint16_t cnt = regs[R_CNT / 2];
    int shift    = (cnt >> 10) & 0xF;
    int step     = ((cnt >> 8) & 3) + 4;
    int parity   = ((noise_level >> 15) ^ (noise_level >> 12) ^ (noise_level >> 11) ^
                    (noise_level >> 10) ^ 1) &
                   1;

    noise_timer -= step;
    if (noise_timer < 0)
    {
        noise_level = (uint16_t)(noise_level * 2 + parity);
        noise_timer += 0x20000 >> shift;
        if (noise_timer < 0)
        {
            noise_timer += 0x20000 >> shift;
        }
    }
}

// One sample of voice `v`, after the envelope, before the voice volume.
static int32_t voice_sample(int v, VOICE *vc, int32_t prev_out)
{
    uint32_t step = regs[v * 8 + 2];
    uint32_t pmon = ((uint32_t)regs[R_PMON_HI / 2] << 16 | regs[R_PMON_LO / 2]) & ~1u;
    uint32_t non  = (uint32_t)regs[R_NON_HI / 2] << 16 | regs[R_NON_LO / 2];
    int32_t s;

    if (pmon & (1u << v))
    {
        int32_t factor = prev_out + 0x8000; // 0..0xFFFF
        step           = (uint32_t)(((int32_t)(int16_t)step * factor) >> 15) & 0xFFFF;
    }
    if (step > 0x4000)
    {
        step = 0x4000;
    }
    s = (non & (1u << v)) ? (int16_t)noise_level : interpolate(vc->hist, vc->counter & 0xFFF);
    vc->counter += step;
    while (vc->counter >= 0x1000)
    {
        vc->counter -= 0x1000;
        vc->hist[0] = vc->hist[1];
        vc->hist[1] = vc->hist[2];
        vc->hist[2] = vc->hist[3];
        vc->hist[3] = next_sample(v, vc);
    }
    s = mul15(s, vc->adsr.level);
    adsr_tick(v, vc);
    return s;
}

// --- reverb ---------------------------------------------------------------------------------

#define RV(i) ((int32_t)(int16_t)regs[(R_REVERB / 2) + (i)])
#define RA(i) ((uint32_t)regs[(R_REVERB / 2) + (i)] * 8)

static uint32_t rev_wrap(uint32_t off)
{
    uint32_t base = (uint32_t)regs[R_REV_BASE / 2] * 8;
    uint32_t size = SPU_RAM_BYTES - base;
    uint32_t a;

    if (size == 0)
    {
        return 0;
    }
    a = (rev_addr - base + off) % size;
    return (base + a) & (SPU_RAM_BYTES - 2);
}

static int32_t rev_rd(uint32_t off)
{
    uint32_t a = rev_wrap(off);
    return (int16_t)(ram[a] | ram[a + 1] << 8);
}

static void rev_wr(uint32_t off, int32_t v)
{
    uint32_t a;

    if (!(regs[R_CNT / 2] & CNT_REVERB))
    {
        return;
    }
    a          = rev_wrap(off);
    v          = clamp16(v);
    ram[a]     = (uint8_t)v;
    ram[a + 1] = (uint8_t)(v >> 8);
}

// One step of the reverb unit (22.05 kHz, both sides), psx-spx's formulas.
static void reverb_step(int32_t in_l, int32_t in_r)
{
    uint32_t dAPF1 = RA(0), dAPF2 = RA(1);
    int32_t vIIR = RV(2), vCOMB1 = RV(3), vCOMB2 = RV(4), vCOMB3 = RV(5), vCOMB4 = RV(6);
    int32_t vWALL = RV(7), vAPF1 = RV(8), vAPF2 = RV(9);
    uint32_t mLSAME = RA(10), mRSAME = RA(11), mLCOMB1 = RA(12), mRCOMB1 = RA(13);
    uint32_t mLCOMB2 = RA(14), mRCOMB2 = RA(15), dLSAME = RA(16), dRSAME = RA(17);
    uint32_t mLDIFF = RA(18), mRDIFF = RA(19), mLCOMB3 = RA(20), mRCOMB3 = RA(21);
    uint32_t mLCOMB4 = RA(22), mRCOMB4 = RA(23), dLDIFF = RA(24), dRDIFF = RA(25);
    uint32_t mLAPF1 = RA(26), mRAPF1 = RA(27), mLAPF2 = RA(28), mRAPF2 = RA(29);
    int32_t vLIN = RV(30), vRIN = RV(31);
    int32_t lin = mul15(vLIN, in_l), rin = mul15(vRIN, in_r);
    int32_t l, r, t;

    rev_wr(mLSAME, mul15(lin + mul15(rev_rd(dLSAME), vWALL) - rev_rd(mLSAME - 2), vIIR) +
                       rev_rd(mLSAME - 2));
    rev_wr(mRSAME, mul15(rin + mul15(rev_rd(dRSAME), vWALL) - rev_rd(mRSAME - 2), vIIR) +
                       rev_rd(mRSAME - 2));
    rev_wr(mLDIFF, mul15(lin + mul15(rev_rd(dRDIFF), vWALL) - rev_rd(mLDIFF - 2), vIIR) +
                       rev_rd(mLDIFF - 2));
    rev_wr(mRDIFF, mul15(rin + mul15(rev_rd(dLDIFF), vWALL) - rev_rd(mRDIFF - 2), vIIR) +
                       rev_rd(mRDIFF - 2));

    l = mul15(vCOMB1, rev_rd(mLCOMB1)) + mul15(vCOMB2, rev_rd(mLCOMB2)) +
        mul15(vCOMB3, rev_rd(mLCOMB3)) + mul15(vCOMB4, rev_rd(mLCOMB4));
    r = mul15(vCOMB1, rev_rd(mRCOMB1)) + mul15(vCOMB2, rev_rd(mRCOMB2)) +
        mul15(vCOMB3, rev_rd(mRCOMB3)) + mul15(vCOMB4, rev_rd(mRCOMB4));

    t = rev_rd(mLAPF1 - dAPF1);
    l = clamp16(l - mul15(vAPF1, t));
    rev_wr(mLAPF1, l);
    l = mul15(l, vAPF1) + t;
    t = rev_rd(mRAPF1 - dAPF1);
    r = clamp16(r - mul15(vAPF1, t));
    rev_wr(mRAPF1, r);
    r = mul15(r, vAPF1) + t;

    t = rev_rd(mLAPF2 - dAPF2);
    l = clamp16(l - mul15(vAPF2, t));
    rev_wr(mLAPF2, l);
    l = mul15(l, vAPF2) + t;
    t = rev_rd(mRAPF2 - dAPF2);
    r = clamp16(r - mul15(vAPF2, t));
    rev_wr(mRAPF2, r);
    r = mul15(r, vAPF2) + t;

    rev_out_l = clamp16(l);
    rev_out_r = clamp16(r);

    {
        uint32_t base = (uint32_t)regs[R_REV_BASE / 2] * 8;

        rev_addr = (rev_addr + 2) & (SPU_RAM_BYTES - 2);
        if (rev_addr < base)
        {
            rev_addr = base;
        }
    }
}

// One 44.1 kHz frame through the reverb unit with its resampling filters: `in_*` is the reverb
// input of this frame, `out_*` gets the unit's output (before the reverb output volume).
static int32_t fir(const int16_t *hist, int pos)
{
    int32_t acc = 0;
    int k;

    for (k = 0; k < REV_TAPS; k++)
    {
        acc += spu_reverb_fir[k] * hist[(pos + k) % REV_TAPS];
    }
    return acc;
}

static void reverb_resample(int32_t in_l, int32_t in_r, int32_t *out_l, int32_t *out_r)
{
    int pos;

    rev_hist_pos = (rev_hist_pos + 1) % REV_TAPS; // the oldest slot: overwritten
    pos          = rev_hist_pos;
    rev_hist_in[0][(pos + REV_TAPS - 1) % REV_TAPS] = (int16_t)in_l;
    rev_hist_in[1][(pos + REV_TAPS - 1) % REV_TAPS] = (int16_t)in_r;
    if (++rev_phase == 2)
    {
        rev_phase = 0;
        reverb_step(clamp16(fir(rev_hist_in[0], pos) >> 15),
                    clamp16(fir(rev_hist_in[1], pos) >> 15));
        rev_hist_out[0][(pos + REV_TAPS - 1) % REV_TAPS] = (int16_t)rev_out_l;
        rev_hist_out[1][(pos + REV_TAPS - 1) % REV_TAPS] = (int16_t)rev_out_r;
    }
    else
    {
        rev_hist_out[0][(pos + REV_TAPS - 1) % REV_TAPS] = 0;
        rev_hist_out[1][(pos + REV_TAPS - 1) % REV_TAPS] = 0;
    }
    // Half the taps meet a zero: the upsampled output takes twice the filter's gain.
    *out_l = clamp16(fir(rev_hist_out[0], pos) >> 14);
    *out_r = clamp16(fir(rev_hist_out[1], pos) >> 14);
}

// --- mixing ---------------------------------------------------------------------------------

void spu_cd_push(const int16_t *stereo, int frames)
{
    int i;

    for (i = 0; i < frames; i++)
    {
        if (cd_head - cd_tail >= CD_RING)
        {
            return; // overrun: drop
        }
        cd_ring[cd_head % CD_RING][0] = stereo[i * 2];
        cd_ring[cd_head % CD_RING][1] = stereo[i * 2 + 1];
        cd_head++;
    }
}

static void cd_frame(int32_t *l, int32_t *r)
{
    uint32_t have = cd_head - cd_tail;

    *l = *r = 0;
    if (!cd_primed)
    {
        if (have < CD_PRIME)
        {
            return;
        }
        cd_primed = 1;
    }
    if (have == 0)
    {
        cd_primed = 0;
        return;
    }
    *l = cd_ring[cd_tail % CD_RING][0];
    *r = cd_ring[cd_tail % CD_RING][1];
    cd_tail++;
}

void spu_render(int16_t *out, int frames)
{
    int f, v;

    for (f = 0; f < frames; f++)
    {
        uint16_t cnt  = regs[R_CNT / 2];
        uint32_t eon  = (uint32_t)regs[R_EON_HI / 2] << 16 | regs[R_EON_LO / 2];
        int32_t sum_l = 0, sum_r = 0, rin_l = 0, rin_r = 0, rev_l, rev_r;
        int32_t prev = 0, cd_l, cd_r, ml, mr, ol, or_;

        noise_tick();
        for (v = 0; v < VOICES; v++)
        {
            VOICE *vc = &voices[v];
            int32_t s, l, r;

            if (vc->phase == PH_OFF)
            {
                vc->out             = 0;
                prev                = 0;
                regs[0x100 + v * 2] = 0;
                regs[0x101 + v * 2] = 0;
                regs[v * 8 + 6]     = 0;
                continue;
            }
            s                   = voice_sample(v, vc, prev);
            vc->out             = s;
            prev                = s;
            l                   = mul15(s, volume(regs[v * 8 + 0], &vc->sweep[0]));
            r                   = mul15(s, volume(regs[v * 8 + 1], &vc->sweep[1]));
            regs[0x100 + v * 2] = (uint16_t)l; // current volume registers (0x200..)
            regs[0x101 + v * 2] = (uint16_t)r;
            regs[v * 8 + 6]     = (uint16_t)vc->adsr.level;
            sum_l += l;
            sum_r += r;
            if (eon & (1u << v))
            {
                rin_l += l;
                rin_r += r;
            }
        }
        cd_frame(&cd_l, &cd_r);
        if (cnt & CNT_CD_ENABLE)
        {
            cd_l = mul15(cd_l, (int16_t)regs[R_CD_VOL_L / 2]);
            cd_r = mul15(cd_r, (int16_t)regs[R_CD_VOL_R / 2]);
            sum_l += cd_l;
            sum_r += cd_r;
            if (cnt & CNT_CD_REVERB)
            {
                rin_l += cd_l;
                rin_r += cd_r;
            }
        }
        // The reverb unit runs at 22.05 kHz: its input is filtered down from 44.1 kHz, its
        // output zero-stuffed and filtered back up (psx-spx, "Reverb Buffer Resampling").
        reverb_resample(clamp16(rin_l), clamp16(rin_r), &rev_l, &rev_r);
        ml                    = volume(regs[R_MAIN_VOL_L / 2], &main_sweep[0]);
        mr                    = volume(regs[R_MAIN_VOL_R / 2], &main_sweep[1]);
        ol  = mul15(clamp16(sum_l), ml) + mul15(rev_l, (int16_t)regs[R_REV_VOL_L / 2]);
        or_ = mul15(clamp16(sum_r), mr) + mul15(rev_r, (int16_t)regs[R_REV_VOL_R / 2]);
        regs[R_CUR_VOL_L / 2] = (uint16_t)ml;
        regs[R_CUR_VOL_R / 2] = (uint16_t)mr;
        if (!(cnt & CNT_ENABLE) || !(cnt & CNT_UNMUTE))
        {
            ol = or_ = 0;
        }
        out[f * 2]     = (int16_t)clamp16(ol);
        out[f * 2 + 1] = (int16_t)clamp16(or_);
    }
}

// --- registers ------------------------------------------------------------------------------

uint16_t spu_read16(uint32_t off)
{
    off &= 0x3FE;
    switch (off)
    {
        case R_ENDX_LO:
            return (uint16_t)endx;
        case R_ENDX_HI:
            return (uint16_t)(endx >> 16);
        case R_STAT:
            // Mode bits mirror SPUCNT; never busy (transfers complete at once).
            return regs[R_CNT / 2] & 0x3F;
        case R_TRANS_ADDR:
            return regs[off / 2];
        default:
            return regs[off / 2];
    }
}

void spu_write16(uint32_t off, uint16_t value)
{
    int v;

    off &= 0x3FE;
    regs[off / 2] = value;
    if (off < 0x180)
    {
        v = (int)(off >> 4);
        switch (off & 0xF)
        {
            case 0xC: // current ADSR level
                voices[v].adsr.level = (int16_t)value;
                break;
            case 0xE: // loop address
                voices[v].repeat     = (uint32_t)value * 8;
                voices[v].repeat_set = 1;
                break;
            default:
                break;
        }
        return;
    }
    switch (off)
    {
        case R_KON_LO:
        case R_KON_HI:
            for (v = 0; v < 16; v++)
            {
                if (value & (1u << v))
                {
                    key_on(v + (off == R_KON_HI ? 16 : 0));
                }
            }
            break;
        case R_KOFF_LO:
        case R_KOFF_HI:
            for (v = 0; v < 16; v++)
            {
                if (value & (1u << v))
                {
                    key_off(v + (off == R_KOFF_HI ? 16 : 0));
                }
            }
            break;
        case R_ENDX_LO:
        case R_ENDX_HI:
            break;
        case R_TRANS_ADDR:
            trans_addr = (uint32_t)value * 8;
            break;
        case R_FIFO:
            ram[trans_addr & (SPU_RAM_BYTES - 1)]       = (uint8_t)value;
            ram[(trans_addr + 1) & (SPU_RAM_BYTES - 1)] = (uint8_t)(value >> 8);
            trans_addr                                  = (trans_addr + 2) & (SPU_RAM_BYTES - 1);
            break;
        case R_REV_BASE:
            rev_addr = (uint32_t)value * 8;
            break;
        default:
            break;
    }
}

void spu_dma_write(const uint32_t *src, uint32_t words)
{
    uint32_t i;

    for (i = 0; i < words; i++)
    {
        uint32_t w = src[i];
        int k;

        for (k = 0; k < 4; k++)
        {
            ram[trans_addr] = (uint8_t)(w >> (k * 8));
            trans_addr      = (trans_addr + 1) & (SPU_RAM_BYTES - 1);
        }
    }
}

void spu_dma_read(uint32_t *dst, uint32_t words)
{
    uint32_t i;

    for (i = 0; i < words; i++)
    {
        uint32_t w = 0;
        int k;

        for (k = 0; k < 4; k++)
        {
            w |= (uint32_t)ram[trans_addr] << (k * 8);
            trans_addr = (trans_addr + 1) & (SPU_RAM_BYTES - 1);
        }
        dst[i] = w;
    }
}
