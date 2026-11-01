#ifndef PSYQ_LIBCD_H
#define PSYQ_LIBCD_H

/*
 * Self-written declarations for the PsyQ libcd functions this project uses.
 * Not a copy of Sony's header.
 */

#include "common.h"

// CdControl command codes.
#define CdlSetloc 0x02
#define CdlPause 0x09
#define CdlSetmode 0x0e
#define CdlSetfilter 0x0d
#define CdlReadS 0x1b

// CdSyncCallback / CdReadyCallback status codes.
#define CdlDataReady 1
#define CdlComplete 2

// CD position (minute, second, sector, track), BCD.
typedef struct
{
    u_char minute;
    u_char second;
    u_char sector;
    u_char track;
} CdlLOC;

// CdlSetfilter parameter.
typedef struct
{
    u_char file;
    u_char chan;
    u_short pad;
} CdlFILTER;

typedef void (*CdlCB)(u_char, u_char *);

// CD-DA / XA audio volume mix (CdMix argument).
typedef struct
{
    u_char val0;
    u_char val1;
    u_char val2;
    u_char val3;
} CdlATV;

int CdInit(void);
int CdSync(int mode, u_char *result);
int CdControl(u_char com, u_char *param, u_char *result);
int CdControlB(u_char com, u_char *param, u_char *result);
int CdReset(int mode);
CdlCB CdSyncCallback(CdlCB func);
CdlCB CdReadyCallback(CdlCB func);
int CdMix(CdlATV *vol);
CdlLOC *CdIntToPos(int i, CdlLOC *p);
int CdGetSector(void *madr, int size);

#endif // PSYQ_LIBCD_H
