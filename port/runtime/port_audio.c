// Sound output. See port_audio.h.
#include "port_audio.h"

#include "port_config.h"
#include "port_remote.h"
#include "spu.h"
#ifdef PORT_HAVE_SDL
#include "platform_sdl.h"
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BLANK_FRAMES (SPU_RATE / 60) // 735: one vertical blank of game time

// Single-producer, single-consumer ring of stereo frames. The indices live wherever `head` and
// `tail` point: here, or in the window block shared with another process (port_remote.h).
typedef struct
{
    int16_t (*buf)[2];
    uint32_t size; // frames, a power of two
    uint32_t *head, *tail;
} RING;

static int16_t wav_buf[1u << 18][2]; // about six seconds
static int16_t dev_buf[1u << 14][2]; // about 0.37 s
static uint32_t wav_index[2], dev_index[2];
static RING wav_ring = {wav_buf, 1u << 18, &wav_index[0], &wav_index[1]};
static RING dev_ring = {dev_buf, 1u << 14, &dev_index[0], &dev_index[1]};
static FILE *wav;
static uint32_t wav_frames;
static int device_open;
static int volume = 256; // 256 = full

static void ring_put(RING *r, const int16_t *frames, uint32_t n)
{
    uint32_t head = *r->head, tail = __atomic_load_n(r->tail, __ATOMIC_ACQUIRE);
    uint32_t i;

    if (r->size - (head - tail) < n)
    {
        return; // the consumer is behind: drop this blank
    }
    for (i = 0; i < n; i++)
    {
        r->buf[(head + i) & (r->size - 1)][0] = frames[i * 2];
        r->buf[(head + i) & (r->size - 1)][1] = frames[i * 2 + 1];
    }
    __atomic_store_n(r->head, head + n, __ATOMIC_RELEASE);
}

// Takes up to `n` frames; returns how many.
static uint32_t ring_get(RING *r, int16_t *frames, uint32_t n)
{
    uint32_t tail = *r->tail, head = __atomic_load_n(r->head, __ATOMIC_ACQUIRE);
    uint32_t have = head - tail, i;

    if (n > have)
    {
        n = have;
    }
    for (i = 0; i < n; i++)
    {
        frames[i * 2]     = r->buf[(tail + i) & (r->size - 1)][0];
        frames[i * 2 + 1] = r->buf[(tail + i) & (r->size - 1)][1];
    }
    __atomic_store_n(r->tail, tail + n, __ATOMIC_RELEASE);
    return n;
}

static void put_le32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static void wav_header(uint32_t frames)
{
    uint8_t h[44];

    memcpy(h, "RIFF\0\0\0\0WAVEfmt ", 16);
    put_le32(h + 4, 36 + frames * 4);
    put_le32(h + 16, 16);
    h[20] = 1; // PCM
    h[21] = 0;
    h[22] = 2; // stereo
    h[23] = 0;
    put_le32(h + 24, SPU_RATE);
    put_le32(h + 28, SPU_RATE * 4);
    h[32] = 4;
    h[33] = 0;
    h[34] = 16;
    h[35] = 0;
    memcpy(h + 36, "data", 4);
    put_le32(h + 40, frames * 4);
    fseek(wav, 0, SEEK_SET);
    fwrite(h, 1, sizeof(h), wav);
    fseek(wav, 0, SEEK_END);
}

int port_audio_wav_open(const char *path)
{
    wav = fopen(path, "wb");
    if (wav == NULL)
    {
        perror(path);
        return -1;
    }
    wav_header(0);
    return 0;
}

#ifdef PORT_HAVE_SDL
// SDL's audio thread: the device asks for `frames`; silence fills an underrun.
static void device_pull(int16_t *out, int frames)
{
    static int primed;
    uint32_t have = __atomic_load_n(dev_ring.head, __ATOMIC_ACQUIRE) - *dev_ring.tail;
    uint32_t got, i;

    // After an underrun, wait for three blanks of sound so the next ones arrive in time.
    if (!primed && have < 3 * BLANK_FRAMES)
    {
        memset(out, 0, (size_t)frames * 4);
        return;
    }
    primed = 1;
    got    = ring_get(&dev_ring, out, (uint32_t)frames);
    if (got < (uint32_t)frames)
    {
        primed = 0;
    }
    if (got < (uint32_t)frames)
    {
        memset(out + got * 2, 0, (size_t)(frames - (int)got) * 4);
    }
    if (volume != 256)
    {
        for (i = 0; i < got * 2; i++)
        {
            out[i] = (int16_t)((out[i] * volume) >> 8);
        }
    }
}
#endif

void port_audio_set_volume(int percent)
{
    volume = (percent < 0 ? 0 : percent > 100 ? 100 : percent) * 256 / 100;
}

void port_audio_use_shared(uint32_t *head, uint32_t *tail, int16_t (*buf)[2], uint32_t size,
                           int producer)
{
    dev_ring.buf  = buf;
    dev_ring.size = size;
    dev_ring.head = head;
    dev_ring.tail = tail;
    if (producer)
    {
        device_open = 1; // port_audio_tick fills it; the other process plays it
    }
}

int port_audio_device_open(void)
{
    PORT_REMOTE *r = port_remote();

    port_audio_set_volume(port_config_int("audio", "volume", 100));
    if (r != NULL)
    {
        // The game in the window host's process: the host's device plays the shared ring.
        port_audio_use_shared(&r->audio_head, &r->audio_tail, r->audio, PORT_REMOTE_AUDIO_SIZE, 1);
        return 0;
    }
#ifdef PORT_HAVE_SDL
    if (platform_audio_open(SPU_RATE, device_pull) == 0)
    {
        device_open = 1;
        return 0;
    }
#endif
    return -1;
}

void port_audio_tick(void)
{
    int16_t mix[BLANK_FRAMES * 2];

    spu_render(mix, BLANK_FRAMES);
    if (wav != NULL)
    {
        ring_put(&wav_ring, mix, BLANK_FRAMES);
    }
    if (device_open)
    {
        // Keep the device's latency bounded: a blank is dropped when a quarter second waits.
        if (*dev_ring.head - __atomic_load_n(dev_ring.tail, __ATOMIC_ACQUIRE) < SPU_RATE / 4)
        {
            ring_put(&dev_ring, mix, BLANK_FRAMES);
        }
    }
}

void port_audio_flush(void)
{
    int16_t chunk[4096 * 2];
    uint32_t n;

    if (wav == NULL)
    {
        return;
    }
    while ((n = ring_get(&wav_ring, chunk, 4096)) > 0)
    {
        fwrite(chunk, 4, n, wav);
        wav_frames += n;
    }
}

void port_audio_close(void)
{
    if (wav == NULL)
    {
        return;
    }
    port_audio_flush();
    wav_header(wav_frames);
    fclose(wav);
    fprintf(stderr, "port: wrote %u frames (%.1f s) of sound\n", wav_frames,
            (double)wav_frames / SPU_RATE);
    wav = NULL;
}
