#ifndef PSYQ_LIBPRESS_H
#define PSYQ_LIBPRESS_H

/*
 * Self-written declarations for the PsyQ libpress functions this
 * project uses. Not a copy of Sony's header.
 */

#include "common.h"

typedef void (*DecDCTCB)(void);

void DecDCTReset(int mode);
void DecDCTin(u_long *buf, int mode);
int DecDCTvlc(u_long *bs, u_long *buf);
void DecDCTout(u_long *buf, int size);
DecDCTCB DecDCToutCallback(DecDCTCB func);

#endif // PSYQ_LIBPRESS_H
