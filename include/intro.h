#ifndef INTRO_H
#define INTRO_H

#include "common.h"

// One intro screen, called once per frame by Intro_task.
typedef void (*INTRO_FUNC)(void);

extern INTRO_FUNC intro_tbl[4];

// Intro_init sets both with one 32-bit store.
extern uint8 Intro_routine_0; // 0x80059C50 current screen (index into intro_tbl)
extern uint8 Intro_routine_1; // 0x80059C51 current screen's state

void Intro_task(void);

#endif // INTRO_H
