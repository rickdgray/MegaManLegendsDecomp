#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"

// One intro screen, called once per frame by Intro_task.
typedef void (*INTRO_FUNC)(void);

extern INTRO_FUNC intro_tbl[4];

// Possibly fields of one struct: Intro_init writes them with a single sw.
extern u8 g_screenIndex;
extern u8 g_screenState;

void Intro_task(void);

#endif // SCREEN_H
