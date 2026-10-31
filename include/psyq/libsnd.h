#ifndef PSYQ_LIBSND_H
#define PSYQ_LIBSND_H

/*
 * Self-written declarations for the PsyQ libsnd types and functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

void SsInit(void);
void SsQuit(void);
void SsSetSerialAttr(char s_num, char attr, char mode);
void SsSetSerialVol(char s_num, short voll, short volr);

#endif // PSYQ_LIBSND_H
