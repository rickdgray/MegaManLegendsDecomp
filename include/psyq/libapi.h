#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

/*
 * Self-written declarations for the PsyQ libapi functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

// Differs from official PsyQ 4.4 docs; either a typo in the docs or a change in the library.
void InitPAD(u_char *buf0, long len0, u_char *buf1, long len1);

void StartPAD(void);
void ChangeClearPAD(int mode);
void StopPAD(void);
void _96_init(void);
void LoadExec(char *name, u_long stack, u_long size);

// Threads and events. The Library Reference types both start functions as `long (*func)()` /
// `unsigned long (*func)()`; the game's handlers return nothing, so these typedefs (ours, not
// PsyQ's) return void.
typedef void (*TH_FUNC)(void);
typedef void (*EVENT_FUNC)(void);

u_long OpenTh(TH_FUNC func, u_long sp, u_long gp);
long CloseTh(u_long thread);
long ChangeTh(u_long thread);
long OpenEvent(u_long desc, long spec, long mode, EVENT_FUNC func);
long EnableEvent(u_long event);
void EnterCriticalSection(void);
void ExitCriticalSection(void);

#endif // PSYQ_LIBAPI_H
