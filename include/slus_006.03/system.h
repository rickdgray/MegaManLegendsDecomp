#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"

// Initial stack pointer LoadExec gives ROCK_NEO.EXE: the top of 2 MB of RAM, minus 256 bytes.
#define ROCK_NEO_STACK 0x801FFF00

void System_init(void);
void Vsync_handler(void);

#endif // SYSTEM_H
