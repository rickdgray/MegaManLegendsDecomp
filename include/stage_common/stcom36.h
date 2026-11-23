#ifndef STCOM36_H
#define STCOM36_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A work slot as stcom36 sees it.
typedef struct STCOM36_OBJ STCOM36_OBJ;
typedef void (*STCOM36_OBJ_FUNC)(STCOM36_OBJ *wp);

struct STCOM36_OBJ
{
    uint8 flags_0;    // 00
    uint8 index_1;    // 01: pool id and slot
    uint8 kind_2;     // 02: first index into the pool's handler table
    uint8 value_3;    // 03
    uint8 handler_4;  // 04: second index (two-level tables)
    uint8 value_5;    // 05
    uint8 flags_6;    // 06: 0x20 cleared once the room's script has it
    uint8 reserved07; // 07
    uint8 routine_0;  // 08
};

// An object to spawn (a 0x14-byte record, Scene_obj_ent_open).
typedef struct
{
    uint8 index_0; // 00: its slot in Scene_work's object table
    uint8 reserved01[0x13];
} STCOM36_SPAWN;

// The objects a room's script spawns.
typedef struct
{
    uint32 count;
    STCOM36_SPAWN *list;
} STCOM36_ROOM;

// Scene_work (ROCK_NEO's SCENE_WORK): its object table.
typedef struct
{
    uint8 reserved00[0x24];
    STCOM36_OBJ *obj_24[32]; // 24
} STCOM36_SCENE_WORK;

// The pools' handler tables (scratchpad).
#define STCOM36_TABLE_3C0 (*(STCOM36_OBJ_FUNC ***)0x1F800058)
#define STCOM36_TABLE_10C (*(STCOM36_OBJ_FUNC **)0x1F800060)

extern uint32 stcom36_D_0000;          // the objects still to be ended, one bit per slot
extern STCOM36_ROOM stcom36_E_0000[];  // by room
extern STCOM36_OBJ *stcom36_E2_0000[]; // the spawned objects, by slot

// ROCK_NEO.EXE.
extern STCOM36_SCENE_WORK Scene_work;
#ifdef __wasm32__
void *Scene_obj_ent_open(STCOM36_SPAWN *entry);
#else
void Scene_obj_ent_open(STCOM36_SPAWN *entry);
#endif
void Sce_camera_update(void);
void Sce_event_update(void);
sint32 func_8002FE74(uint8 id);

#endif // STCOM36_H
