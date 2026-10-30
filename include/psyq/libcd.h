#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

/*
 * Self-written declarations for the PsyQ libcd functions this project uses.
 * Not a copy of Sony's header.
 */

#include "common.h"

// CdControl command codes.
#define CdlSetmode 0x0e

typedef void (*CdlCB)(u_char, u_char *);

int CdInit(void);
int CdSync(int mode, u_char *result);
int CdControlB(u_char com, u_char *param, u_char *result);
int CdReset(int mode);
CdlCB CdSyncCallback(CdlCB func);
CdlCB CdReadyCallback(CdlCB func);

#endif // PSYQ_LIBCD_H
