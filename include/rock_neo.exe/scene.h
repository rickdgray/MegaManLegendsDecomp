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

#endif // SCENE_H
