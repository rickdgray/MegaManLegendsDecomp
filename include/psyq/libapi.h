#ifndef PSYQ_LIBAPI_H
#define PSYQ_LIBAPI_H

/*
 * Self-written declarations for the PsyQ libapi functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

#define EvSpTRAP 0x1000
#define EvMdINTR 0x1000

typedef long (*EVENT_FUNC)(void);
typedef void (*THREAD_ENTRY_FUNC)(void);

// Differs from official PsyQ 4.4 docs; either a typo in the docs or a change in the library.
void InitPAD(u_char *buf0, long len0, u_char *buf1, long len1);

void StartPAD(void);
void ChangeClearPAD(int mode);
void StopPAD(void);
void _96_init(void);
long ChangeTh(long handle);
long CloseTh(long handle);
long OpenTh(THREAD_ENTRY_FUNC entry, void *stack, u_long gp);
long OpenEvent(u_long desc, long spec, long mode, EVENT_FUNC func);
long EnableEvent(long event);
long PCopen(char *name, long flags, long mode);
long PCread(long handle, void *buf, long size);
long func_8007699C(long handle);
void FlushCache(void);
long func_8007FF70(void);
long func_8007FF80(void);
void LoadExec(char *name, u_long stack, u_long size);

#endif // PSYQ_LIBAPI_H
