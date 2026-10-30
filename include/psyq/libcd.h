#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

/*
 * Self-written declarations for the PsyQ libcd functions this project uses.
 * Not a copy of Sony's header.
 */

#include "common.h"

/* CdControl command codes. */
#define CdlSetmode 0x0e

int CdInit(void);

#endif /* PSYQ_LIBCD_H */
