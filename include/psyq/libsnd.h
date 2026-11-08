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

#define SS_IMEDIATE       0
#define SS_WAIT_COMPLETED 1

void SsInit(void);
void SsQuit(void);
void SsSetSerialAttr(char s_num, char attr, char mode);
void SsSetSerialVol(char s_num, short voll, short volr);
void SsVabClose(short vab_id);
short SsVabOpenHeadSticky(u_char *addr, short vab_id, u_long sbaddr);
short SsVabTransBodyPartly(u_char *addr, u_long bufsize, short vab_id);
short SsVabTransCompleted(short immediate_flag);

#endif // PSYQ_LIBSND_H
