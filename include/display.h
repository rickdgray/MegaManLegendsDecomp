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
extern sint16 disp_width_tbl[2];
extern uint8 Dbl_buff_idx; // 0x1F800000 (scratchpad) current buffer index, toggles 0/1

void Disp_env_set(sint32 mode);
void Disp_env_init(DISP_ENV *buf);

#endif // DISPLAY_H
