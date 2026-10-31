#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

/*
 * Self-written declarations for the PsyQ libapi/libetc functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

void StopPAD(void);
void _96_init(void);
void LoadExec(char *name, u_long stack, u_long size);

#endif // PSYQ_LIBAPI_H
