#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.h"
#include "psyq/libgpu.h"

/* One of the two double buffers. */
typedef struct {
    DISPENV disp;                           /* 0x00 */
    DRAWENV draw;                           /* 0x14 */
    u_long  ot[8];                          /* 0x70 */
} DisplayBuffer;                            /* 0x90 */

extern DisplayBuffer  g_displayBuffers[2];  /* 0x8005b5a8 */
extern DisplayBuffer *g_curBuffer;          /* 0x80059bcc */
extern short          g_screenWidths[2];    /* 0x8001d3d8: {320, 640} */

void SetupDisplay(int mode);
void InitDisplayBuffer(DisplayBuffer *buf);

#endif /* DISPLAY_H */