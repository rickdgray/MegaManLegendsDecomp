#ifndef PSYQ_LIBETC_H
#define PSYQ_LIBETC_H

/*
 * Self-written declarations for the PsyQ libetc functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

#define MODE_NTSC 0
#define MODE_PAL  1

// VSyncCallback's callback, typed as the Library Reference writes it: void (*func)().
typedef void (*VSYNC_FUNC)();

void ResetCallback(void);
void StopCallback(void);
long SetVideoMode(long mode);
int VSync(int mode);
void VSyncCallback(VSYNC_FUNC func);

#endif // PSYQ_LIBETC_H
