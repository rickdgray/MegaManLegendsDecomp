#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"
#include "psyq/libgpu.h"

#define DISP_MODE_320 0
#define DISP_MODE_640 1

// One of the two double buffers.
typedef struct
{
    DISPENV disp;
    DRAWENV draw;
    u_long ot[8];
} DISP_ENV;

extern DISP_ENV Disp_env[2];
extern DISP_ENV *Disp_env_ptr;
extern sint16 disp_width_tbl[2];
extern volatile uint32 Vsync_count; // 0x80059BC0 incremented once per vblank by Vsync_handler
extern RECT Clear_rect;             // cleared with ClearImage at init
extern sint32 D_80059BBC;           // zeroed at init

void Disp_env_set(sint32 mode);
void Disp_env_init(DISP_ENV *buf);

#endif // DISPLAY_H
