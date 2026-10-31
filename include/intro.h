#ifndef INTRO_H
#define INTRO_H

#include "common.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"

// One intro screen, called once per frame by Intro_task.
typedef void (*INTRO_FUNC)(void);

extern INTRO_FUNC intro_tbl[4];

// Intro_init sets both with one 32-bit store.
extern uint8 Intro_routine_0;      // 0x80059C50 current screen (index into intro_tbl)
extern uint8 Intro_routine_1;      // 0x80059C51 current screen's state
extern uint8 Intro_bright;         // 0x80059C54 fade brightness (intro_copyright)
extern uint8 Intro_timer;          // 0x80059C55 hold counter (intro_copyright)
extern SPRT copyright_sprt[2][80]; // 0x80059C78 copyright image sprites, one set per buffer
extern DR_MODE copyright_dr_mode[2]
                                [5]; // 0x8005A8F8 copyright image texture pages, one set per buffer
extern SPRT loading_sprt[2];         // 0x8005A970 loading banner sprites, one per buffer
extern DR_MODE loading_dr_mode[2];   // 0x80059B40 loading banner texture page, one per buffer

// HACK: aliases D_80059B40[1]. The target reaches the second draw mode through a separate
// symbol (a fresh lui), which the array alone doesn't reproduce. Revisit.
extern DR_MODE D_80059B4C;   // 0x80059B4C second element of loading_dr_mode
extern u_long loading_tim[]; // 0x800461C4 loading banner image (CLUT at +0x14, pixels at +0x40)
extern char rock_neo_path[]; // 0x80059B24 "cdrom:\\ROCK_NEO.EXE;1"
extern u_long D_8001DFA4[];  // 0x8001DFA4 copyright image (CLUT at +0x14, pixels at +0x220)

void Intro_task(void);

#endif // INTRO_H
