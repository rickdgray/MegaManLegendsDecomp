#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"
#include "psyq/libgpu.h"

// One of the two double buffers.
typedef struct
{
    DISPENV disp;
    DRAWENV draw;
    u_long ot[8];
} DISP_ENV;

extern DISP_ENV Disp_env[2];
extern DISP_ENV *Disp_env_ptr;
extern short disp_width_tbl[2];

void Disp_env_set(int mode);
void Disp_env_init(DISP_ENV *buf);

#endif // DISPLAY_H
