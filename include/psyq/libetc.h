#ifndef PSYQ_LIBETC_H
#define PSYQ_LIBETC_H

/*
 * Self-written declarations for the PsyQ libetc functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

typedef void (*VSYNC_FUNC)(void);

void ResetCallback(void);
long SetVideoMode(long mode);
int VSync(int mode);
int VSyncCallback(VSYNC_FUNC func);

#endif // PSYQ_LIBETC_H
