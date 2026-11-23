#ifndef STCOM38_H
#define STCOM38_H

#include "common.h"

// The room script work (ROCK_NEO's CODE68_WORK at D_800989F8): only the field used here.
typedef struct
{
    uint8 flags_0;       // 00
    uint8 reserved01[3]; // 01
    uint8 started_4;     // 04: 0xFF once the room's script has been started
} STCOM38_ROOM_WORK;

extern uint8 stcom38_D_0000[]; // room scripts
extern uint8 stcom38_E_0000[];
extern uint8 stcom38_E2_0000[];

// ROCK_NEO.EXE.
void Scene_obj_list_open(uint8 *script);

#endif // STCOM38_H
