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

// CdlSetmode mode bits
#define CdlModeDA 0x01       // CD-DA playback on
#define CdlModeAP 0x02       // autopause
#define CdlModeRept 0x04     // report mode
#define CdlModeSF 0x08       // subheader filter
#define CdlModeSize0 0x10    // sector size 2328 bytes
#define CdlModeSize1 0x20    // sector size 2340 bytes
#define CdlModeRT 0x40       // XA-ADPCM playback on
#define CdlModeSpeed 0x80    // double speed
#define CdlModeStream 0x100  // normal streaming
#define CdlModeStream2 0x120 // streaming, subheader information included

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

// Header at the start of every movie (STR) sector, 32 bytes. PsyQ's names; field meanings from
// the File Formats manual, "STR: Streaming (Movie) Data".
typedef struct
{
    u_short id;        // 0x00  StSTATUS: format id and version, 0x0160
    u_short type;      // 0x02  StTYPE: top bit set = system format; 0x8001 = MDEC movie
    u_short secCount;  // 0x04  StSECTOR_OFFSET: this sector's index within the frame
    u_short nSectors;  // 0x06  StSECTOR_SIZE: sectors in the frame
    u_long frameCount; // 0x08  StFRAME_NO: frame number, starting from 1
    u_long frameSize;  // 0x0C  StFRAME_SIZE: frame size in long words
    u_short width;     // 0x10  StMOVIE_WIDTH
    u_short height;    // 0x12  StMOVIE_HEIGHT
    u_long dummy1;     // 0x14  StMOVIE_HEADM: reserved
    u_long dummy2;     // 0x18  StMOVIE_HEADV: reserved
    CdlLOC loc;        // 0x1C  file location
} StHEADER;

typedef void (*CdlCB)(u_char, u_char *);

// CD-DA / XA audio volume mix (CdMix argument).
typedef struct
{
    u_char val0;
    u_char val1;
    u_char val2;
    u_char val3;
} CdlATV;

// Differs from official PsyQ 4.4 docs; either a typo in the docs or a change in the library.
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
