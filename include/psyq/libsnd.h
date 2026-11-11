#ifndef PSYQ_LIBSND_H
#define PSYQ_LIBSND_H

/*
 * Self-written declarations for the PsyQ libsnd types and functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

#define SS_SERIAL_A 0
#define SS_SERIAL_B 1
#define SS_MIX      0
#define SS_REV      1
#define SS_SOFF     0
#define SS_SON      1
#define SS_VOL_MAX  0x7f

#define SS_TICK60 1

#define SSPLAY_PAUSE    0
#define SSPLAY_PLAY     1
#define SSPLAY_INFINITY 0

#define SS_IMEDIATE       0
#define SS_WAIT_COMPLETED 1

// Bank header, 0x20 bytes
typedef struct VabHdr
{
    long form;         // 0x00: always 'VABp'
    long ver;          // 0x04
    long id;           // 0x08
    u_long fsize;      // 0x0C
    u_short reserved0; // 0x10
    u_short ps;        // 0x12: number of programs
    u_short ts;        // 0x14: number of tones
    u_short vs;        // 0x16: number of VAGs
    u_char mvol;       // 0x18
    u_char pan;        // 0x19
    u_char attr1;      // 0x1A
    u_char attr2;      // 0x1B
    u_long reserved1;  // 0x1C
} VabHdr;

// Program header, 0x10 bytes
typedef struct ProgAtr
{
    u_char tones;     // 0x0: number of VagAtr in the program
    u_char mvol;      // 0x1
    u_char prior;     // 0x2
    u_char mode;      // 0x3
    u_char mpan;      // 0x4
    char reserved0;   // 0x5
    short attr;       // 0x6
    u_long reserved1; // 0x8
    u_long reserved2; // 0xC
} ProgAtr;

// Tone (waveform) header, 0x20 bytes
typedef struct VagAtr
{
    u_char prior;      // 0x00: priority (0-15)
    u_char mode;       // 0x01: 0 normal, 4 reverb
    u_char vol;        // 0x02
    u_char pan;        // 0x03
    u_char center;     // 0x04: center note
    u_char shift;      // 0x05: center note fine tune
    u_char min;        // 0x06: lowest note
    u_char max;        // 0x07: highest note
    u_char vibW;       // 0x08
    u_char vibT;       // 0x09
    u_char porW;       // 0x0A
    u_char porT;       // 0x0B
    u_char pbmin;      // 0x0C
    u_char pbmax;      // 0x0D
    u_char reserved1;  // 0x0E
    u_char reserved2;  // 0x0F
    u_short adsr1;     // 0x10
    u_short adsr2;     // 0x12
    short prog;        // 0x14
    short vag;         // 0x16
    short reserved[4]; // 0x18
} VagAtr;

void SsInit(void);
void SsQuit(void);
void SsSetMVol(short voll, short volr);
void SsSetRVol(short voll, short volr);
char SsSetReservedVoice(char voices);
short SsUtSetReverbType(short type);
void SsUtSetReverbDepth(short ldepth, short rdepth);
short SsSeqOpen(unsigned long *addr, short vab_id);
void SsSeqPlay(short seq_access_num, char play_mode, short l_count);
void SsSeqClose(short seq_access_num);
short SsSepOpen(unsigned long *addr, short vab_id, short seq_num);
void SsSepPlay(short seq_access_num, short seq_num, char play_mode, short l_count);
void SsSepClose(short seq_access_num);
void SsSetSerialAttr(char s_num, char attr, char mode);
void SsSetSerialVol(char s_num, short voll, short volr);
void SsVabClose(short vab_id);
short SsVabOpenHeadSticky(u_char *addr, short vab_id, u_long sbaddr);
short SsVabTransBodyPartly(u_char *addr, u_long bufsize, short vab_id);
short SsVabTransCompleted(short immediate_flag);
short SsUtKeyOffV(short voice);
void SsStart(void);
void SsSetTableSize(char *table, short s_max, short t_max);
void SsSetTickMode(long tick_mode);
long SsUtGetVagAddr(short vab_id, short vag_num);
short SsIsEos(short access_num, short seq_num);
void SsInit(void);
void SsSeqStop(short seq_access_num);
void SsSepStop(short sep_access_num, short seq_num);
void SsSeqSetVol(short seq_access_num, short voll, short volr);
void SsSepSetVol(short sep_access_num, short seq_num, short voll, short volr);
void SsUtAllKeyOff(short mode);
void SsUtReverbOn(void);
void SsSetMono(void);
void SsSetStereo(void);

#endif // PSYQ_LIBSND_H
