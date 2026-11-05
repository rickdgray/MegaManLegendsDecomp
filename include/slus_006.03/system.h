#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"

#define VSYNC_60FPS 1
#define VSYNC_30FPS 2

void System_init(void);
void Vsync_handler(void);

#endif // SYSTEM_H
