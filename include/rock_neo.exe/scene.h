#ifndef SCENE_H
#define SCENE_H

#include "common.h"

// Scene work, 0xA8 bytes (fields still unknown).
typedef struct
{
    uint8 unk00;
    uint8 unk01;
    uint8 unk02[0xA8 - 2];
} SCENE_WORK;

extern SCENE_WORK Scene_work; // 0x800C4C48

void Sound_fade_start(sint32 fade);                             // starts a sound fade (Sound_fade_flags) unless one is running
sint32 func_8001E83C(sint16 x, sint16 z, sint16 dx, sint16 dz); // angle to a point

#endif // SCENE_H
