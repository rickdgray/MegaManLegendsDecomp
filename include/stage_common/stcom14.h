#ifndef STCOM14_H
#define STCOM14_H

#include "common.h"
#include "stage_common/rock_neo.h"

// Smoke: emitters on 0x48-byte effect slots that spawn puffs (more effect slots) drifting up and
// fading out.

#define STCOM14_MODE  0x3D48004E // a puff's draw mode word
#define STCOM14_COLOR 0x2E404040 // its GPU code and starting color

typedef void (*STCOM14_FUNC)(STCOM_EFFECT *wp);

extern STCOM14_FUNC stcom14_D_0000[]; // handlers by type while value_D is 0
extern STCOM14_FUNC stcom14_D_0010[]; // handlers by type otherwise

// ROCK_NEO.EXE: frees a 0x48-byte work slot.
void func_80031988(STCOM_EFFECT *wp);

#endif // STCOM14_H
