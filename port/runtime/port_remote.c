// The shared window block. See port_remote.h.
#define _GNU_SOURCE
#include "port_remote.h"

#include "gpu.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <unistd.h>

static PORT_REMOTE *shared;
static int event_fd = -1;
static uint32_t last_seq;

PORT_REMOTE *port_remote(void)
{
    return shared;
}

int port_remote_event_fd(void)
{
    return event_fd;
}

int port_remote_attach(void)
{
    const char *v = getenv(PORT_REMOTE_ENV);
    int mfd, efd;
    void *p;

    if (v == NULL || sscanf(v, "%d,%d", &mfd, &efd) != 2)
    {
        return 0;
    }
    unsetenv(PORT_REMOTE_ENV); // not for anything this program starts
    p = mmap(NULL, sizeof(PORT_REMOTE), PROT_READ | PROT_WRITE, MAP_SHARED, mfd, 0);
    if (p == MAP_FAILED || ((PORT_REMOTE *)p)->magic != PORT_REMOTE_MAGIC)
    {
        fprintf(stderr, "port: %s names no window block\n", PORT_REMOTE_ENV);
        return -1;
    }
    close(mfd);
    fcntl(efd, F_SETFD, FD_CLOEXEC);
    shared   = p;
    event_fd = efd;
    return 1;
}

void port_remote_present(void)
{
    const GPU_DISPLAY *d = gpu_display();
    uint64_t one         = 1;

    if (shared == NULL)
    {
        return;
    }
    __atomic_add_fetch(&shared->frame_seq, 1, __ATOMIC_ACQ_REL); // odd: writing
    memcpy(shared->vram, gpu_vram(), sizeof(shared->vram));
    memcpy(&shared->overlay, port_overlay(), sizeof(shared->overlay));
    shared->disp_x  = d->x;
    shared->disp_y  = d->y;
    shared->disp_w  = d->w;
    shared->disp_h  = d->h;
    shared->disp_24 = d->is24;
    __atomic_add_fetch(&shared->frame_seq, 1, __ATOMIC_ACQ_REL);
    if (write(event_fd, &one, sizeof(one)) < 0)
    {
        // the host is gone; its death signal ends this process
    }
}

int port_remote_poll(PSX_PAD_STATE pads[2])
{
    if (shared == NULL)
    {
        return 1;
    }
    memcpy(pads, shared->pads, 2 * sizeof(PSX_PAD_STATE));
    return !shared->quit;
}

int port_remote_create(void)
{
    char v[32];
    int mfd = memfd_create("mml-window", 0); // inherited by the child (no close-on-exec)
    void *p;

    if (mfd < 0 || ftruncate(mfd, sizeof(PORT_REMOTE)) != 0)
    {
        perror("memfd");
        return -1;
    }
    p = mmap(NULL, sizeof(PORT_REMOTE), PROT_READ | PROT_WRITE, MAP_SHARED, mfd, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }
    event_fd = eventfd(0, EFD_NONBLOCK);
    if (event_fd < 0)
    {
        perror("eventfd");
        return -1;
    }
    shared = p;
    memset(shared, 0, sizeof(*shared));
    shared->magic = PORT_REMOTE_MAGIC;
    psx_pad_reset(&shared->pads[0]);
    psx_pad_reset(&shared->pads[1]);
    shared->pads[1].connected = 0;
    snprintf(v, sizeof(v), "%d,%d", mfd, event_fd);
    setenv(PORT_REMOTE_ENV, v, 1);
    return 0;
}

int port_remote_take_frame(uint16_t *vram, int32_t disp[5], PORT_OVERLAY *overlay)
{
    uint32_t s1, s2;
    uint64_t n;

    if (shared == NULL)
    {
        return 0;
    }
    if (read(event_fd, &n, sizeof(n)) < 0)
    {
        // nothing signalled; the sequence number below still tells
    }
    s1 = __atomic_load_n(&shared->frame_seq, __ATOMIC_ACQUIRE);
    if ((s1 & 1) != 0 || s1 == last_seq)
    {
        return 0;
    }
    memcpy(vram, shared->vram, sizeof(shared->vram));
    memcpy(overlay, &shared->overlay, sizeof(*overlay));
    disp[0] = shared->disp_x;
    disp[1] = shared->disp_y;
    disp[2] = shared->disp_w;
    disp[3] = shared->disp_h;
    disp[4] = shared->disp_24;
    s2      = __atomic_load_n(&shared->frame_seq, __ATOMIC_ACQUIRE);
    if (s1 != s2)
    {
        return 0; // torn: the next one comes soon
    }
    last_seq = s1;
    return 1;
}
