// Memory card images. See memcard.h.
//
// Layout (psx-spx, "Memory Card Data Format"): frame 0 is the header ("MC", XOR checksum in
// byte 0x7F); frames 1..15 are the directory, one entry per data block:
//   +0x00 u32 state: 0x51 first block of a file, 0x52 middle, 0x53 last, 0xA0 free,
//                    0xA1..0xA3 the same of a deleted file (free for reuse)
//   +0x04 u32 file size in bytes (first block only)
//   +0x08 u16 next block of the file (directory index 0..14), 0xFFFF at the end
//   +0x0A     file name, up to 20 characters and a 00h
//   +0x7F     XOR of bytes 0x00..0x7E
// Frames 16..35 are the broken-sector list (none: FFFFFFFFh), 36..62 unused, and frame 63 a copy
// of the header (the write-test frame). Blocks 1..15 hold the files' data.
#define _GNU_SOURCE
#include "memcard.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define ST_FIRST   0x51
#define ST_MIDDLE  0x52
#define ST_LAST    0x53
#define ST_FREE    0xA0
#define NEXT_NONE  0xFFFF

typedef struct
{
    char *path;
    int create;   // a missing file is a formatted card
    int checked;  // the file has been looked at
    int present;  // a card is in the slot
    int on_disk;  // the file existed at the last look
    int is_new;   // not yet acknowledged by the game
    struct timespec mtime;
    off_t size;
    uint8_t image[MEMCARD_SIZE];
} CARD;

static CARD cards[MEMCARD_SLOTS];

static void card_log(const char *fmt, const char *a, const char *b)
{
    fprintf(stderr, "port: memory card: ");
    fprintf(stderr, fmt, a, b);
    fputc('\n', stderr);
}

static uint8_t checksum(const uint8_t *frame)
{
    uint8_t x = 0;
    int i;

    for (i = 0; i < MEMCARD_FRAME - 1; i++)
    {
        x ^= frame[i];
    }
    return x;
}

void memcard_format_image(uint8_t *image)
{
    int f;

    memset(image, 0xFF, MEMCARD_SIZE);
    memset(image, 0, MEMCARD_FRAME);
    image[0]    = 'M';
    image[1]    = 'C';
    image[0x7F] = checksum(image);
    for (f = 1; f < 16; f++)
    {
        uint8_t *e = image + f * MEMCARD_FRAME;

        memset(e, 0, MEMCARD_FRAME);
        e[0]    = ST_FREE;
        e[8]    = 0xFF;
        e[9]    = 0xFF;
        e[0x7F] = checksum(e);
    }
    for (f = 16; f < 36; f++)
    {
        uint8_t *e = image + f * MEMCARD_FRAME;

        memset(e, 0, MEMCARD_FRAME);
        memset(e, 0xFF, 4);
        e[8]    = 0xFF;
        e[9]    = 0xFF;
        e[0x7F] = checksum(e);
    }
    memcpy(image + 63 * MEMCARD_FRAME, image, MEMCARD_FRAME);
}

void memcard_set_path(int slot, const char *path, int create)
{
    CARD *c;

    if (slot < 0 || slot >= MEMCARD_SLOTS)
    {
        return;
    }
    c = &cards[slot];
    free(c->path);
    c->path    = path != NULL && *path != 0 ? strdup(path) : NULL;
    c->create  = create;
    c->checked = 0;
    c->present = 0;
}

const char *memcard_path(int slot)
{
    return slot >= 0 && slot < MEMCARD_SLOTS ? cards[slot].path : NULL;
}

// Reads the file again (or makes the blank card a missing file stands for).
static void load(CARD *c)
{
    struct stat st;
    int fd;

    c->checked = 1;
    c->present = 0;
    c->on_disk = 0;
    c->is_new  = 1;
    if (c->path == NULL)
    {
        return;
    }
    if (stat(c->path, &st) != 0)
    {
        if (c->create)
        {
            memcard_format_image(c->image);
            c->present = 1;
        }
        return;
    }
    c->on_disk = 1;
    c->mtime   = st.st_mtim;
    c->size    = st.st_size;
    if (st.st_size != MEMCARD_SIZE)
    {
        card_log("%s is not a 128 KB raw card image%s", c->path, ": slot left empty");
        return;
    }
    fd = open(c->path, O_RDONLY | O_CLOEXEC);
    if (fd < 0 || read(fd, c->image, MEMCARD_SIZE) != MEMCARD_SIZE)
    {
        card_log("cannot read %s: %s", c->path, strerror(errno));
        if (fd >= 0)
        {
            close(fd);
        }
        return;
    }
    close(fd);
    c->present = 1;
}

static int mkdirs(const char *path)
{
    char buf[4096];
    char *p;

    if (strlen(path) >= sizeof(buf))
    {
        return -1;
    }
    strcpy(buf, path);
    p = strrchr(buf, '/');
    if (p == NULL)
    {
        return 0;
    }
    *p = 0;
    for (p = buf + 1; *p != 0; p++)
    {
        if (*p == '/')
        {
            *p = 0;
            mkdir(buf, 0755);
            *p = '/';
        }
    }
    mkdir(buf, 0755);
    return 0;
}

// Writes the whole image: to PATH.tmp, then renamed over PATH.
static int save(CARD *c)
{
    char tmp[4200];
    struct stat st;
    int fd;
    ssize_t n;

    if (c->path == NULL)
    {
        return -1;
    }
    snprintf(tmp, sizeof(tmp), "%s.tmp", c->path);
    mkdirs(c->path);
    fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
    if (fd < 0)
    {
        card_log("cannot write %s: %s", tmp, strerror(errno));
        return -1;
    }
    n = write(fd, c->image, MEMCARD_SIZE);
    if (n != MEMCARD_SIZE || fsync(fd) != 0)
    {
        card_log("cannot write %s: %s", tmp, strerror(errno));
        close(fd);
        unlink(tmp);
        return -1;
    }
    close(fd);
    if (rename(tmp, c->path) != 0)
    {
        card_log("cannot replace %s: %s", c->path, strerror(errno));
        unlink(tmp);
        return -1;
    }
    if (stat(c->path, &st) == 0)
    {
        c->on_disk = 1;
        c->mtime   = st.st_mtim;
        c->size    = st.st_size;
    }
    return 0;
}

static CARD *card(int slot)
{
    CARD *c;

    if (slot < 0 || slot >= MEMCARD_SLOTS)
    {
        return NULL;
    }
    c = &cards[slot];
    if (!c->checked)
    {
        load(c);
    }
    return c->present ? c : NULL;
}

int memcard_poll(int slot)
{
    CARD *c;
    struct stat st;
    int exists;

    if (slot < 0 || slot >= MEMCARD_SLOTS)
    {
        return -1;
    }
    c = &cards[slot];
    if (!c->checked)
    {
        load(c);
    }
    else if (c->path != NULL)
    {
        exists = stat(c->path, &st) == 0;
        if (exists != c->on_disk ||
            (exists && (st.st_mtim.tv_sec != c->mtime.tv_sec ||
                        st.st_mtim.tv_nsec != c->mtime.tv_nsec || st.st_size != c->size)))
        {
            load(c); // changed behind our back: a different card was inserted
        }
    }
    if (!c->present)
    {
        return -1;
    }
    return c->is_new;
}

int memcard_present(int slot)
{
    return card(slot) != NULL;
}

int memcard_formatted(int slot)
{
    CARD *c = card(slot);

    return c != NULL && c->image[0] == 'M' && c->image[1] == 'C';
}

void memcard_ack(int slot)
{
    CARD *c = card(slot);

    if (c != NULL)
    {
        c->is_new = 0;
    }
}

int memcard_read_frame(int slot, int frame, uint8_t *buf)
{
    CARD *c = card(slot);

    if (c == NULL || frame < 0 || frame >= MEMCARD_FRAMES)
    {
        return -1;
    }
    memcpy(buf, c->image + frame * MEMCARD_FRAME, MEMCARD_FRAME);
    return 0;
}

int memcard_write_frame(int slot, int frame, const uint8_t *buf)
{
    CARD *c = card(slot);

    if (c == NULL || frame < 0 || frame >= MEMCARD_FRAMES)
    {
        return -1;
    }
    memcpy(c->image + frame * MEMCARD_FRAME, buf, MEMCARD_FRAME);
    c->is_new = 0;
    return save(c);
}

int memcard_format(int slot)
{
    CARD *c = card(slot);

    if (c == NULL)
    {
        return -1;
    }
    memcard_format_image(c->image);
    return save(c);
}

// --- directory ------------------------------------------------------------------------------

static uint8_t *entry(CARD *c, int block)
{
    return c->image + block * MEMCARD_FRAME;
}

static uint32_t get32(const uint8_t *p)
{
    return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24);
}

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

static int next_block(CARD *c, int block)
{
    const uint8_t *e = entry(c, block);
    int next         = e[8] | (e[9] << 8);

    return next == NEXT_NONE || next > 14 ? -1 : next + 1;
}

static void fill_file(CARD *c, int block, MEMCARD_FILE *out)
{
    const uint8_t *e = entry(c, block);

    if (out == NULL)
    {
        return;
    }
    memcpy(out->name, e + 0x0A, MEMCARD_NAME_MAX);
    out->name[MEMCARD_NAME_MAX] = 0;
    out->size                   = get32(e + 4);
    out->first                  = block;
}

int memcard_file_at(int slot, int index, MEMCARD_FILE *out)
{
    CARD *c = card(slot);
    int b;

    if (c == NULL)
    {
        return 0;
    }
    for (b = 1; b < MEMCARD_BLOCKS; b++)
    {
        if (get32(entry(c, b)) == ST_FIRST && index-- == 0)
        {
            fill_file(c, b, out);
            return 1;
        }
    }
    return 0;
}

int memcard_find(int slot, const char *name, MEMCARD_FILE *out)
{
    CARD *c = card(slot);
    int b;

    if (c == NULL)
    {
        return -1;
    }
    for (b = 1; b < MEMCARD_BLOCKS; b++)
    {
        const uint8_t *e = entry(c, b);

        if (get32(e) == ST_FIRST && strncmp((const char *)e + 0x0A, name, MEMCARD_NAME_MAX) == 0)
        {
            fill_file(c, b, out);
            return b;
        }
    }
    return -1;
}

static int is_free(uint32_t state)
{
    return state == ST_FREE || state == 0xA1 || state == 0xA2 || state == 0xA3;
}

int memcard_free_blocks(int slot)
{
    CARD *c = card(slot);
    int b, n = 0;

    if (c == NULL)
    {
        return 0;
    }
    for (b = 1; b < MEMCARD_BLOCKS; b++)
    {
        n += is_free(get32(entry(c, b)));
    }
    return n;
}

int memcard_create(int slot, const char *name, int blocks)
{
    CARD *c = card(slot);
    int list[MEMCARD_BLOCKS];
    int b, k, n = 0;

    if (c == NULL || blocks < 1 || blocks > 15 || memcard_find(slot, name, NULL) >= 0)
    {
        return -1;
    }
    for (b = 1; b < MEMCARD_BLOCKS && n < blocks; b++)
    {
        if (is_free(get32(entry(c, b))))
        {
            list[n++] = b;
        }
    }
    if (n < blocks)
    {
        return -1;
    }
    for (k = 0; k < blocks; k++)
    {
        uint8_t *e = entry(c, list[k]);
        int next   = k + 1 < blocks ? list[k + 1] - 1 : NEXT_NONE;

        memset(e, 0, MEMCARD_FRAME);
        put32(e, k == 0 ? ST_FIRST : k + 1 == blocks ? ST_LAST : ST_MIDDLE);
        if (k == 0)
        {
            put32(e + 4, (uint32_t)blocks * MEMCARD_BLOCK);
            strncpy((char *)e + 0x0A, name, MEMCARD_NAME_MAX);
        }
        e[8]    = (uint8_t)next;
        e[9]    = (uint8_t)(next >> 8);
        e[0x7F] = checksum(e);
    }
    return save(c) == 0 ? list[0] : -1;
}

int memcard_erase(int slot, const char *name)
{
    CARD *c = card(slot);
    int b   = memcard_find(slot, name, NULL);
    int guard;

    if (c == NULL || b < 0)
    {
        return -1;
    }
    for (guard = 0; b > 0 && guard < 15; guard++)
    {
        uint8_t *e = entry(c, b);

        put32(e, ST_FREE | (get32(e) & 0x0F));
        e[0x7F] = checksum(e);
        b       = next_block(c, b);
    }
    return save(c);
}

int memcard_file_io(int slot, int first, uint32_t offset, void *buf, uint32_t n, int write)
{
    CARD *c      = card(slot);
    uint8_t *p   = buf;
    int b        = first;
    uint32_t done = 0;
    int guard;

    if (c == NULL || first < 1 || first >= MEMCARD_BLOCKS)
    {
        return -1;
    }
    for (guard = 0; offset >= MEMCARD_BLOCK && b > 0 && guard < 15; guard++)
    {
        offset -= MEMCARD_BLOCK;
        b = next_block(c, b);
    }
    while (done < n)
    {
        uint32_t part = MEMCARD_BLOCK - offset;

        if (b <= 0 || ++guard > 15)
        {
            return -1;
        }
        if (part > n - done)
        {
            part = n - done;
        }
        if (write)
        {
            memcpy(c->image + b * MEMCARD_BLOCK + offset, p + done, part);
        }
        else
        {
            memcpy(p + done, c->image + b * MEMCARD_BLOCK + offset, part);
        }
        done += part;
        offset = 0;
        b      = next_block(c, b);
    }
    if (write && save(c) != 0)
    {
        return -1;
    }
    return (int)n;
}

int memcard_check_image(const uint8_t *image, char *why, int why_size)
{
    int b, seen[MEMCARD_BLOCKS] = {0};

    if (image[0] != 'M' || image[1] != 'C' || checksum(image) != image[0x7F])
    {
        snprintf(why, why_size, "no \"MC\" header");
        return -1;
    }
    for (b = 1; b < MEMCARD_BLOCKS; b++)
    {
        const uint8_t *e = image + b * MEMCARD_FRAME;

        if (checksum(e) != e[0x7F])
        {
            snprintf(why, why_size, "directory entry %d: bad checksum", b);
            return -1;
        }
    }
    for (b = 1; b < MEMCARD_BLOCKS; b++)
    {
        const uint8_t *e = image + b * MEMCARD_FRAME;
        uint32_t size;
        int k = b, count = 0;

        if (get32(e) != ST_FIRST)
        {
            continue;
        }
        size = get32(e + 4);
        while (k > 0)
        {
            const uint8_t *f = image + k * MEMCARD_FRAME;
            int next         = f[8] | (f[9] << 8);

            if (seen[k]++ || ++count > 15)
            {
                snprintf(why, why_size, "file at block %d: broken chain", b);
                return -1;
            }
            k = next == NEXT_NONE ? 0 : next + 1;
            if (k > 15)
            {
                snprintf(why, why_size, "file at block %d: next block out of range", b);
                return -1;
            }
        }
        if (size != (uint32_t)count * MEMCARD_BLOCK)
        {
            snprintf(why, why_size, "file at block %d: size %u for %d blocks", b, size, count);
            return -1;
        }
    }
    return 0;
}
