// One window across the boot shim's LoadExec.
//
// On the console LoadExec replaces the running program; the port's `mml_boot` runs the game as
// another program (`mml`). To keep a single window, the shim's process keeps it: at LoadExec it
// becomes the window host, forks, and the child execs `mml` with a shared-memory block named in
// the environment (MML_WINDOW = "<memfd>,<eventfd>"). The game then renders headlessly into the
// block (VRAM and the display area at every frame end; its sound into a ring) and reads its pads
// from it; the host shows the frames, plays the sound, polls the keyboard and gamepads, and ends
// when the game does. `mml` started alone opens its own window as before.
#ifndef PORT_REMOTE_H
#define PORT_REMOTE_H

#include "pad.h"
#include "port_overlay.h"

#include <stdint.h>

#define PORT_REMOTE_ENV        "MML_WINDOW"
#define PORT_REMOTE_MAGIC      0x4D4D4C57u // "MMLW"
#define PORT_REMOTE_AUDIO_SIZE (1u << 14)  // stereo frames, a power of two

typedef struct
{
    uint32_t magic;
    // game -> host: the picture, under a sequence lock (odd while being written)
    volatile uint32_t frame_seq;
    int32_t disp_x, disp_y, disp_w, disp_h, disp_24;
    uint16_t vram[1024 * 512];
    PORT_OVERLAY overlay; // the port's text layer over the picture (port_overlay.h)
    // host -> game
    PSX_PAD_STATE pads[2];
    volatile uint32_t quit; // the window was closed: stop
    // game -> host: sound (port_audio.c's ring, indices shared)
    uint32_t audio_head, audio_tail;
    int16_t audio[PORT_REMOTE_AUDIO_SIZE][2];
} PORT_REMOTE;

// Game side. port_remote_attach maps the block named by MML_WINDOW; returns 1 when attached,
// 0 when the variable is absent, -1 on error.
int port_remote_attach(void);
PORT_REMOTE *port_remote(void); // NULL unless attached (or created, on the host side)
void port_remote_present(void);
// Copies the host's pads; returns 0 once the host asks the game to stop.
int port_remote_poll(PSX_PAD_STATE pads[2]);

// Host side: creates the block and sets MML_WINDOW for the child. Returns 0 or -1.
int port_remote_create(void);
int port_remote_event_fd(void);
// Copies a new frame into vram/display and the text layer (returns 1), or returns 0 when there
// is none.
int port_remote_take_frame(uint16_t *vram, int32_t disp[5], PORT_OVERLAY *overlay);

#endif
