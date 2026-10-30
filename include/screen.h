#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"

/* One intro screen, called once per frame by RunIntroSequence. */
typedef void (*ScreenFunc)(void);

extern ScreenFunc g_screenFuncs[4];         /* 0x8001df94 */

/* Possibly fields of one struct: InitIntro writes them with a single sw. */
extern u8 g_screenIndex;                    /* 0x80059c50 */
extern u8 g_screenState;                    /* 0x80059c51 */

void RunIntroSequence(void);

#endif /* SCREEN_H */
