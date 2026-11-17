#ifndef PSYQ_LIBPRESS_H
#define PSYQ_LIBPRESS_H

/*
 * Self-written declarations for the PsyQ libpress functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

// DecDCToutCallback's callback. Ours, not PsyQ's: the Library Reference types it `long (*func)()`,
// but the game's callback (the shim's Movie_dct_out_callback) returns nothing.
typedef void (*DecDCTCB)(void);

void DecDCTReset(long mode);
void DecDCTin(u_long *runlevel, long mode);
int DecDCTvlc(u_long *bs, u_long *buf);
void DecDCTout(u_long *cell, long size);
long DecDCToutCallback(DecDCTCB func);

#endif // PSYQ_LIBPRESS_H
