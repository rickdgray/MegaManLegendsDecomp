#ifndef PSYQ_LIBSN_H
#define PSYQ_LIBSN_H

/*
 * Self-written declarations for the PsyQ libsn host file I/O (development
 * leftovers: they reach the PC through the debugger's break calls).
 * Not a copy of Sony's header.
 */

#include "common.h"

int PCopen(char *name, int flags, int perms);
int PCread(int fd, char *buff, int len);
int PCclose(int fd);

// Breakpoint trap for the SN debugger: the instruction 0x0001000D (break code 1 in the upper
// field; maspsx encodes `break 1024` as `break 0x1,0x0`). Our name; PsyQ's libsn may have
// a macro for it (pollhost?), unconfirmed.
#define DEBUG_BREAK() __asm__ volatile("break 1024")

#endif // PSYQ_LIBSN_H
