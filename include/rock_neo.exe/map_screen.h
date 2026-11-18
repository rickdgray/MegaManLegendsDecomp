#ifndef ROCK_NEO_MAP_SCREEN_H
#define ROCK_NEO_MAP_SCREEN_H

#include "common.h"
#include "code_800133d8.h"

// Scratchpad frame counter; its low bits animate the map cursor.
#define MAP_SCREEN_FRAME (*(uint16 *)0x1F800002)

typedef struct
{
    sint16 x;
    sint16 y;
} MAP_POS;

// Map screen state (8 bytes, $gp small data owned by map_screen in retail).
typedef struct
{
    sint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    sint8 mode_4;
    sint8 cursor_5;
    uint8 reserved6[2];
} MAP_SCREEN_WORK;

extern MAP_POS D_8008DB34[];
extern MAP_SCREEN_WORK Map_screen_work;
extern sint16 D_8008DB28[];
extern sint16 D_8008DB2C[];

void map_screen_set(void);
void map_cursor_set(void);

#endif
