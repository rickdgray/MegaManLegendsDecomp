#ifndef ROCK_DISPLAY_H
#define ROCK_DISPLAY_H

#include "common.h"
#include "psyq/libgpu.h"

#define OT_LEN           8
#define DISPLAY_WIDTH    320
#define DISPLAY_HEIGHT   240
#define DISPLAY_BUFFER_Y 256

// The native port's hook for the main loop's wait for the vertical blank (it advances its
// game-paced clock there; port/include/port_prelude.h). Nothing on the console.
#ifndef VSYNC_IDLE
#define VSYNC_IDLE()
#endif

typedef struct
{
    DISPENV disp;
    DRAWENV draw;
    u_long ot[OT_LEN];
} DISP_ENV;

extern volatile uint32 Vsync_count;

void Vsync_handler(void);
void Disp_env_init(DISP_ENV *buf);

#endif // ROCK_DISPLAY_H
