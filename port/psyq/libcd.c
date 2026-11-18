// PsyQ libcd for the native port, on the owner's disc image.
//
// The drive is modeled at the level libcd presents to the game: commands, their first response
// (the "acknowledge", which CdControl/CdControlB wait for), a second response for the commands
// that have one (Pause, Stop, the seeks, Init, GetID, ReadTOC), and data sectors arriving one at
// a time while ReadN/ReadS runs. Everything that the hardware delivers by interrupt is delivered
// from the vertical-blank signal (port_cd_tick, called by port_game.c), so the game's callbacks
// run in "interrupt context" as on the console: CdSyncCallback when a second response arrives,
// CdReadyCallback with CdlDataReady for each sector. CdGetSector reads the current sector the way
// the DMA reads the drive's buffer: consecutive calls continue where the previous one stopped,
// from the sector's header in 2340-byte mode (CdlModeSize1) or its user data in 2048-byte mode.
//
// Timing: 75 sectors a second, 150 at double speed, spread over the vertical blanks (2.5 sectors
// a blank at double speed and 60 Hz). With --fast the blank rate rises and the drive with it;
// --cd-speed N multiplies the rate. XA audio sectors met while reading with CdlModeRT (filtered
// by Setfilter with CdlModeSF) and CD-DA sectors while playing are decoded here and go to the
// SPU's CD input (port/runtime/spu.c) through CdMix's volume matrix; the game watches GetlocP
// to stop them.
//
// CdIntToPos/CdPosToInt run from the retail image (psyq_emulated.c).
#define _GNU_SOURCE
#include "port_game.h"
#include "spu.h"

#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#define CdlNop       0x01
#define CdlSetloc    0x02
#define CdlPlay      0x03
#define CdlReadN     0x06
#define CdlStandby   0x07
#define CdlStop      0x08
#define CdlPause     0x09
#define CdlInit      0x0A
#define CdlSetfilter 0x0D
#define CdlSetmode   0x0E
#define CdlGetlocL   0x10
#define CdlGetlocP   0x11
#define CdlGetTN     0x13
#define CdlSeekL     0x15
#define CdlSeekP     0x16
#define CdlGetID     0x1A
#define CdlReadS     0x1B
#define CdlReset     0x1C
#define CdlReadTOC   0x1E

#define CdlNoIntr    0
#define CdlDataReady 1
#define CdlComplete  2

#define MODE_RT    0x40
#define MODE_SF    0x08
#define MODE_SPEED 0x80
#define MODE_SIZE1 0x20

#define STAT_MOTOR 0x02
#define STAT_READ  0x20
#define STAT_PLAY  0x80

#define RAW_SECTOR 2352
#define LEAD_IN    150 // sectors before LBA 0 (two seconds)

typedef void (*CD_CB)(uint8_t status, uint8_t *result);

typedef struct
{
    int fd;
    int32_t start;   // first LBA of this track (its file's first sector)
    int32_t sectors; // length in sectors
    int audio;
    int32_t pregap; // INDEX 01 relative to the file's start
} TRACK;

static TRACK tracks[8];
static int track_count;

static CD_CB volatile sync_cb, ready_cb;
static uint8_t mode;
static uint8_t filter_file, filter_chan;
static int32_t setloc_lba;  // target of the next read or seek
static int32_t pos_lba;     // the head: next sector to deliver
static int reading;         // ReadN/ReadS running
static int playing;         // CD-DA play running
static int sync_pending;    // a second response is due at the next tick
static uint8_t sync_status; // the last command's state: CdlComplete or CdlNoIntr
static uint8_t pending_result[8];
static uint8_t last_result[8];
static uint32_t budget; // owed sectors, in 1/60 sector units
static uint8_t sector[RAW_SECTOR];
static int sector_valid;
static int fifo_pos; // byte offset of the next CdGetSector word in `sector`
static uint8_t last_header[8];
static uint32_t sectors_read;

int port_cd_speed = 1; // --cd-speed: multiplier on the drive's sector rate

// --- the disc image -------------------------------------------------------------------------

static int msf_to_lba(int m, int s, int f)
{
    return (m * 60 + s) * 75 + f;
}

static uint8_t to_bcd(int v)
{
    return (uint8_t)(((v / 10) << 4) | (v % 10));
}

static int from_bcd(uint8_t v)
{
    return (v >> 4) * 10 + (v & 15);
}

static void lba_to_bcd(int32_t lba, uint8_t *out)
{
    int32_t a = lba + LEAD_IN;

    out[0] = to_bcd(a / 4500);
    out[1] = to_bcd(a / 75 % 60);
    out[2] = to_bcd(a % 75);
}

static int32_t bcd_to_lba(const uint8_t *p)
{
    return msf_to_lba(from_bcd(p[0]), from_bcd(p[1]), from_bcd(p[2])) - LEAD_IN;
}

// Reads a .cue sheet: FILE "x.bin" BINARY, TRACK n MODE2/2352|AUDIO, INDEX 01 mm:ss:ff.
// Each FILE holds one track (the usual layout of a dump); the tracks follow each other.
static int load_cue(const char *cue)
{
    FILE *f = fopen(cue, "r");
    char line[1024], dir[1024], path[2048];
    const char *slash;
    int32_t next = 0;
    TRACK *t     = NULL;
    FILE *img    = NULL;
    int fd       = -1;

    if (f == NULL)
    {
        return -1;
    }
    slash = strrchr(cue, '/');
    if (slash != NULL)
    {
        snprintf(dir, sizeof(dir), "%.*s", (int)(slash - cue), cue);
    }
    else
    {
        strcpy(dir, ".");
    }
    while (fgets(line, sizeof(line), f) != NULL)
    {
        char *p = line;
        int m, s, fr, idx;

        while (*p == ' ' || *p == '\t')
        {
            p++;
        }
        if (strncmp(p, "FILE ", 5) == 0)
        {
            char *q = strchr(p, '"');
            char *e = q != NULL ? strchr(q + 1, '"') : NULL;

            if (e == NULL)
            {
                continue;
            }
            *e = 0;
            snprintf(path, sizeof(path), "%s/%s", dir, q + 1);
            // stdio, not open(): in the placed objects open/close/read/write are PsyQ's
            // (gen_link.py renames them to psyq_*).
            img = fopen(path, "rb");
            fd  = img != NULL ? fileno(img) : -1;
            if (fd < 0)
            {
                port_log("CD: cannot open %s", path);
                fclose(f);
                return -1;
            }
        }
        else if (strncmp(p, "TRACK ", 6) == 0 && track_count < 8 && fd >= 0)
        {
            off_t size = lseek(fd, 0, SEEK_END);

            t          = &tracks[track_count++];
            t->fd      = fd;
            t->audio   = strstr(p, "AUDIO") != NULL;
            t->sectors = (int32_t)(size / RAW_SECTOR);
            t->start   = next;
            t->pregap  = 0;
            next += t->sectors;
        }
        else if (t != NULL && sscanf(p, "INDEX %d %d:%d:%d", &idx, &m, &s, &fr) == 4 && idx == 1)
        {
            t->pregap = msf_to_lba(m, s, fr);
        }
    }
    fclose(f);
    if (track_count > 0)
    {
        port_log("CD: %s: %d track(s), %d sectors", cue, track_count, next);
    }
    return track_count > 0 ? 0 : -1;
}

// `path` is a .cue file or a directory holding one.
int port_cd_open(const char *path)
{
    DIR *d;
    struct dirent *e;
    char cue[2048];
    size_t n = strlen(path);

    if (n > 4 && strcasecmp(path + n - 4, ".cue") == 0)
    {
        return load_cue(path);
    }
    d = opendir(path);
    if (d == NULL)
    {
        return -1;
    }
    cue[0] = 0;
    while ((e = readdir(d)) != NULL)
    {
        size_t l = strlen(e->d_name);

        if (l > 4 && strcasecmp(e->d_name + l - 4, ".cue") == 0)
        {
            snprintf(cue, sizeof(cue), "%s/%s", path, e->d_name);
            break;
        }
    }
    closedir(d);
    return cue[0] != 0 ? load_cue(cue) : -1;
}

int port_cd_present(void)
{
    return track_count > 0;
}

static TRACK *track_of(int32_t lba)
{
    int i;

    for (i = 0; i < track_count; i++)
    {
        if (lba >= tracks[i].start && lba < tracks[i].start + tracks[i].sectors)
        {
            return &tracks[i];
        }
    }
    return NULL;
}

// Loads raw sector `lba` (2352 bytes, sync and header included). Returns 0, or -1 off the disc.
static int read_raw(int32_t lba, uint8_t *out)
{
    TRACK *t = track_of(lba);

    if (t == NULL ||
        pread(t->fd, out, RAW_SECTOR, (off_t)(lba - t->start) * RAW_SECTOR) != RAW_SECTOR)
    {
        memset(out, 0, RAW_SECTOR);
        return -1;
    }
    return 0;
}

// Copies raw sector `lba`'s 2048 bytes of user data (mode 2 form 1) to `out`, for host tools.
int port_cd_read_user(int32_t lba, uint8_t *out)
{
    uint8_t raw[RAW_SECTOR];
    int r = read_raw(lba, raw);

    memcpy(out, raw + 24, 2048);
    return r;
}

// --- CD audio: XA ADPCM and CD-DA to the SPU's CD input ---------------------------------------

static uint8_t atv[4] = {0x80, 0x00, 0x80, 0x00}; // CdMix: L->L, L->R, R->R, R->L (0x80 = 1.0)
static int32_t xa_hist[2][2];                      // per channel: the last two samples
static int32_t xa_prev[2];                          // resampler: the previous input frame
static uint32_t xa_phase;                           // resampler position, 16.16

static int16_t clamp16(int32_t v)
{
    return (int16_t)(v < -0x8000 ? -0x8000 : v > 0x7FFF ? 0x7FFF : v);
}

// The drive's volume matrix, then the SPU's CD input.
static void cd_audio_out(int16_t *frames, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        int32_t l = frames[i * 2], r = frames[i * 2 + 1];

        frames[i * 2]     = clamp16((l * atv[0] + r * atv[3]) >> 7);
        frames[i * 2 + 1] = clamp16((r * atv[2] + l * atv[1]) >> 7);
    }
    spu_cd_push(frames, n);
}

static void xa_reset(void)
{
    memset(xa_hist, 0, sizeof(xa_hist));
    memset(xa_prev, 0, sizeof(xa_prev));
    xa_phase = 0;
}

// Decodes one XA audio sector (raw, 2352 bytes) and plays it: 18 sound groups of 128 bytes, each
// with 8 sound units of 28 4-bit samples (or 4 of 8-bit), alternating left and right in stereo;
// the same filters as the SPU's ADPCM. The 37.8 or 18.9 kHz stream is resampled to 44.1 kHz.
static void xa_play_sector(const uint8_t *sec)
{
    static const int32_t pos[4] = {0, 60, 115, 98}, neg[4] = {0, 0, -52, -55};
    static int16_t in[2][4032];
    static int16_t out[4800 * 2 * 3];
    uint8_t coding = sec[19];
    int stereo = (coding & 3) == 1, bits8 = ((coding >> 4) & 3) == 1;
    int rate = ((coding >> 2) & 3) == 1 ? 18900 : 37800;
    int units = bits8 ? 4 : 8, count[2] = {0, 0};
    uint32_t step = (uint32_t)(((uint64_t)rate << 16) / 44100);
    int g, u, k, i, n = 0;

    for (g = 0; g < 18; g++)
    {
        const uint8_t *grp = sec + 24 + g * 128;

        for (u = 0; u < units; u++)
        {
            int ch = stereo ? (u & 1) : 0;
            int shift = grp[4 + u] & 0x0F, filter = (grp[4 + u] >> 4) & 3;

            if (shift > 12)
            {
                shift = 9;
            }
            for (k = 0; k < 28; k++)
            {
                int32_t smp;

                if (bits8)
                {
                    smp = (int32_t)(int16_t)(grp[16 + k * 4 + u] << 8);
                }
                else
                {
                    int nib = (grp[16 + k * 4 + u / 2] >> ((u & 1) * 4)) & 0xF;
                    smp     = (int32_t)(int16_t)(nib << 12);
                }
                smp >>= shift;
                smp += (xa_hist[ch][0] * pos[filter] + xa_hist[ch][1] * neg[filter] + 32) >> 6;
                smp              = clamp16(smp);
                xa_hist[ch][1]   = xa_hist[ch][0];
                xa_hist[ch][0]   = smp;
                in[ch][count[ch]++] = (int16_t)smp;
            }
        }
    }
    // Linear resampling to the SPU's rate.
    for (i = 0; i < count[0]; i++)
    {
        int32_t l = in[0][i], r = stereo ? in[1][i] : l;

        while (xa_phase < 0x10000)
        {
            out[n * 2]     = (int16_t)(xa_prev[0] + (((l - xa_prev[0]) * (int32_t)xa_phase) >> 16));
            out[n * 2 + 1] = (int16_t)(xa_prev[1] + (((r - xa_prev[1]) * (int32_t)xa_phase) >> 16));
            n++;
            xa_phase += step;
        }
        xa_phase -= 0x10000;
        xa_prev[0] = l;
        xa_prev[1] = r;
    }
    cd_audio_out(out, n);
}

// One CD-DA sector: 588 stereo frames at 44.1 kHz.
static void cdda_play_sector(int32_t lba)
{
    int16_t frames[588 * 2];

    if (read_raw(lba, (uint8_t *)frames) != 0)
    {
        return;
    }
    cd_audio_out(frames, 588);
}

// --- the drive ------------------------------------------------------------------------------

static uint8_t drive_status(void)
{
    uint8_t s = STAT_MOTOR;

    if (reading)
    {
        s |= STAT_READ;
    }
    if (playing)
    {
        s |= STAT_PLAY;
    }
    return s;
}

static void fill_result(int com, uint8_t *r)
{
    TRACK *t;

    memset(r, 0, 8);
    r[0] = drive_status();
    switch (com)
    {
        case CdlGetlocL:
            memcpy(r, last_header, 8);
            break;
        case CdlGetlocP:
            t    = track_of(pos_lba);
            r[0] = to_bcd(t != NULL ? (int)(t - tracks) + 1 : 1);
            r[1] = 1;
            if (t != NULL)
            {
                int32_t rel = pos_lba - t->start - t->pregap;

                if (rel < 0)
                {
                    rel = -rel;
                    r[1] = 0;
                }
                r[2] = to_bcd(rel / 4500);
                r[3] = to_bcd(rel / 75 % 60);
                r[4] = to_bcd(rel % 75);
            }
            lba_to_bcd(pos_lba, &r[5]);
            break;
        case CdlGetTN:
            r[1] = 1;
            r[2] = to_bcd(track_count);
            break;
        case CdlGetID:
            r[1] = 0x00; // a licensed data disc
            r[2] = 0x20;
            r[4] = 'S';
            r[5] = 'C';
            r[6] = 'E';
            r[7] = 'A';
            break;
    }
}

// Runs a command; `blocking` for CdControlB, which also waits for a second response.
// Interrupts are blocked by the caller.
static void command(int com, const uint8_t *param, uint8_t *result, int blocking)
{
    int second = 0; // the command has a second response

    switch (com)
    {
        case CdlSetloc:
            if (param != NULL)
            {
                setloc_lba = bcd_to_lba(param);
            }
            break;
        case CdlReadN:
        case CdlReadS:
            if (param != NULL)
            {
                setloc_lba = bcd_to_lba(param);
            }
            pos_lba      = setloc_lba;
            xa_reset();
            reading      = 1;
            playing      = 0;
            sector_valid = 0;
            budget       = 0;
            port_log_limited("CD read", 12, "CD: %s from sector %d (%s bytes%s)",
                             com == CdlReadN ? "ReadN" : "ReadS", setloc_lba,
                             mode & MODE_SIZE1 ? "2340" : "2048", mode & MODE_RT ? ", XA" : "");
            if (port_options.stop_on_cd)
            {
                port_stop(0, "the game reads the CD (--stop-on-cd)");
            }
            break;
        case CdlPlay:
            if (param != NULL && param[0] != 0)
            {
                // a track number: play from its start
                int n = from_bcd(param[0]);

                if (n >= 1 && n <= track_count)
                {
                    setloc_lba = tracks[n - 1].start + tracks[n - 1].pregap;
                }
            }
            pos_lba = setloc_lba;
            playing = 1;
            reading = 0;
            break;
        case CdlSeekL:
        case CdlSeekP:
            if (param != NULL)
            {
                setloc_lba = bcd_to_lba(param);
            }
            pos_lba = setloc_lba;
            reading = 0;
            playing = 0;
            second  = 1;
            break;
        case CdlPause:
        case CdlStop:
        case CdlStandby:
            reading = 0;
            playing = 0;
            second  = 1;
            break;
        case CdlInit:
        case CdlReset:
            reading = 0;
            playing = 0;
            mode    = 0;
            second  = 1;
            break;
        case CdlGetID:
        case CdlReadTOC:
            second = 1;
            break;
        case CdlSetmode:
            if (param != NULL)
            {
                mode = param[0];
            }
            break;
        case CdlSetfilter:
            if (param != NULL)
            {
                filter_file = param[0];
                filter_chan = param[1];
            }
            break;
        default:
            break;
    }
    if (port_options.verbose && com != CdlNop && com != CdlGetlocP && com != CdlGetlocL)
    {
        port_log("CD: command 0x%02X%s", com, blocking ? " (B)" : "");
    }
    fill_result(com, last_result);
    if (result != NULL)
    {
        int n = com == CdlGetlocP || com == CdlGetlocL || com == CdlGetID || com == CdlGetTN
                    ? 8
                    : 1;

        memcpy(result, last_result, (size_t)n);
    }
    if (second)
    {
        // CdControlB returns after the second response; CdControl before it. Either way the
        // sync callback, if one is set, runs from the next interrupt.
        sync_pending = 1;
        sync_status  = blocking ? CdlComplete : CdlNoIntr;
        fill_result(CdlNop, pending_result);
    }
    else
    {
        sync_pending = 0;
        sync_status  = CdlComplete;
    }
}

// Delivers one data sector to the game: loads it, then calls the ready callback.
static void deliver_sector(void)
{
    CD_CB cb;

    read_raw(pos_lba, sector);
    memcpy(last_header, sector + 12, 8);
    sector_valid = 1;
    fifo_pos     = (mode & MODE_SIZE1) ? 12 : 24;
    pos_lba++;
    sectors_read++;
    // With CdlModeRT, XA audio sectors (form 2, real-time, audio) go to the SPU and never
    // reach the game; with CdlModeSF only those of the Setfilter file and channel are played.
    if ((mode & MODE_RT) && (sector[18] & 0x04))
    {
        if (!(mode & MODE_SF) || (sector[16] == filter_file && sector[17] == filter_chan))
        {
            xa_play_sector(sector);
        }
        return;
    }
    cb = ready_cb;
    if (cb != NULL)
    {
        static uint8_t res[8];

        memset(res, 0, sizeof(res));
        res[0] = drive_status();
        cb(CdlDataReady, res);
    }
}

// Called at every vertical blank (from the signal handler, so with interrupts blocked).
void port_cd_tick(void)
{
    // Second responses first: their commands were issued before this blank.
    if (sync_pending)
    {
        CD_CB cb = sync_cb;

        sync_pending = 0;
        sync_status  = CdlComplete;
        if (cb != NULL)
        {
            cb(CdlComplete, pending_result);
        }
    }
    if (reading || playing)
    {
        // 75 sectors a second (150 at double speed) over 60 blanks a second.
        budget += (uint32_t)((mode & MODE_SPEED) ? 150 : 75) * (uint32_t)port_cd_speed;
        while (budget >= 60 && (reading || playing))
        {
            budget -= 60;
            if (playing)
            {
                cdda_play_sector(pos_lba);
                pos_lba++;
                continue;
            }
            deliver_sector();
        }
    }
}

// --- libcd ----------------------------------------------------------------------------------

#ifdef PORT_AOT_MIPS
// Keep the open disc and sector map while switching from the shim to the game.
void port_cd_reset_session(void)
{
    sync_cb = ready_cb = NULL;
    mode = filter_file = filter_chan = 0;
    setloc_lba = pos_lba = 0;
    reading = playing = sync_pending = sector_valid = fifo_pos = 0;
    sync_status = 0;
    budget = sectors_read = 0;
    memset(pending_result, 0, sizeof(pending_result));
    memset(last_result, 0, sizeof(last_result));
    memset(last_header, 0, sizeof(last_header));
    atv[0] = atv[2] = 0x80;
    atv[1] = atv[3] = 0;
    xa_reset();
}
#endif

int CdInit(void)
{
    int b = port_irq_block();

    if (!port_cd_present())
    {
        port_log("CdInit: no disc image (pass --disc DIR or FILE.cue)");
    }
    command(CdlInit, NULL, NULL, 1);
    sync_pending = 0;
    port_irq_restore(b);
    return 1;
}

int CdReset(int m)
{
    int b = port_irq_block();

    command(CdlInit, NULL, NULL, 1);
    sync_pending = 0;
    port_irq_restore(b);
    return 1;
}

int CdControl(uint8_t com, uint8_t *param, uint8_t *result)
{
    int b = port_irq_block();

    command(com, param, result, 0);
    port_irq_restore(b);
    return 1;
}

int CdControlB(uint8_t com, uint8_t *param, uint8_t *result)
{
    int b = port_irq_block();

    command(com, param, result, 1);
    port_irq_restore(b);
    return 1;
}

int CdControlF(uint8_t com, uint8_t *param)
{
    int b = port_irq_block();

    command(com, param, NULL, 0);
    port_irq_restore(b);
    return 1;
}

// CdSync(0) waits for the last command's completion; CdSync(1) reports it.
int CdSync(int m, uint8_t *result)
{
    if (m == 0 && sync_status != CdlComplete)
    {
        int b = port_irq_block();

        port_irq_restore(b);
        if (b)
        {
            // Called with interrupts off (from a callback): nothing can arrive; finish now.
            sync_status = CdlComplete;
        }
        else
        {
            while (sync_status != CdlComplete)
            {
                port_vblank_poll(); // the second response comes at an interrupt
            }
        }
    }
    if (result != NULL)
    {
        result[0] = drive_status();
    }
    return sync_status;
}

// CdReady(1) reports whether a sector is waiting.
int CdReady(int m, uint8_t *result)
{
    if (result != NULL)
    {
        result[0] = drive_status();
    }
    return sector_valid ? CdlDataReady : CdlNoIntr;
}

void *CdSyncCallback(CD_CB func)
{
    CD_CB old = sync_cb;

    sync_cb = func;
    return (void *)old;
}

void *CdReadyCallback(CD_CB func)
{
    CD_CB old = ready_cb;

    ready_cb = func;
    return (void *)old;
}

// Copies `size` words of the current sector to `buf`, continuing from the previous call.
int CdGetSector(void *buf, int size)
{
    int n    = size * 4;
    int have = sector_valid ? RAW_SECTOR - fifo_pos : 0;

    if (have > n)
    {
        have = n;
    }
    if (have > 0)
    {
        memcpy(buf, sector + fifo_pos, (size_t)have);
        fifo_pos += have;
    }
    if (have < n)
    {
        memset((uint8_t *)buf + (have > 0 ? have : 0), 0, (size_t)(n - (have > 0 ? have : 0)));
    }
    return 1;
}

// The drive's audio volume matrix (CdlATV: L->L, L->R, R->R, R->L; 0x80 is unity).
int CdMix(void *vol)
{
    memcpy(atv, vol, 4);
    return 1;
}

uint32_t port_cd_sectors_read(void)
{
    return sectors_read;
}
