#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

/*
 * Self-written declarations for the PsyQ libapi functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

void InitPAD(u_char *buf0, long len0, u_char *buf1, long len1);
void StartPAD(void);
void ChangeClearPAD(int mode);
void StopPAD(void);
void _96_init(void);
void LoadExec(char *name, u_long stack, u_long size);

#endif // PSYQ_LIBAPI_H
