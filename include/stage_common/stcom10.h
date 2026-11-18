#ifndef STCOM10_H
#define STCOM10_H

#include "common.h"
#include "stage_common/rock_neo.h"

// An object to spawn: copied into a work slot of the kind's pool (stcom10_func_05F4).
typedef struct
{
    sint8 flags_0;       // 00: -1 ends the list
    uint8 kind_1;        // 01: pool (0x20, 0x40, 0x60 or 0xE0, as func_8002FE74 returns)
    uint8 value_2;       // 02
    uint8 value_3;       // 03
    uint8 value_4;       // 04
    uint8 value_5;       // 05
    uint8 reserved06;    // 06
    uint8 rotation_7;    // 07: rotation.y / 16
    uint32 value_8;      // 08
    STCOM_SVECTOR pos_C; // 0C
    sint32 flag_14;      // 14: scene flag: set once the object is gone, and then not spawned
} STCOM10_SPAWN;

// An area of the room: a box of map cells (512 units) and the objects spawned in it.
typedef struct
{
    sint16 value_0;        // 00: -1 ends the table
    sint16 area_2;         // 02
    sint8 x_4;             // 04: first cell
    sint8 z_5;             // 05
    uint8 width_6;         // 06: cells
    uint8 depth_7;         // 07
    STCOM10_SPAWN *list_8; // 08
} STCOM10_AREA;

// Where the player is: the room's area table and the current area.
typedef struct
{
    STCOM10_AREA *table_0; // 00: this room's areas (stcom10_D_000C)
    STCOM10_AREA *area_4;  // 04: the area the player is in
    sint8 area_8;          // 08: its area_2
    sint8 value_9;         // 09: its value_0
} STCOM10_STATE;

// The work slot stcom10 runs on: watches the player's map cell against a per-room table and
// sets scene flags (stcom10_func_0134).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 reserved09[0xB]; // 09
    STCOM10_STATE state;   // 14
} STCOM10_WORK;

// A work slot as stcom10_func_05F4 sets it up (the 0x3C0, 0x5A4 and 0x10C pools).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 index_1;                          // 01: pool id and slot (func_80036294)
    uint8 kind_2;                           // 02: first index into the pool's handler table
    uint8 value_3;                          // 03
    uint8 handler_4;                        // 04: second index (two-level tables)
    uint8 value_5;                          // 05
    uint8 reserved06[2];                    // 06
    uint8 routine_0;                        // 08
    uint8 reserved09[3];                    // 09
    uint32 value_C;                         // 0C
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
} STCOM10_OBJ;

// A 0x50-byte slot (func_80031734).
typedef struct
{
    uint8 flags_0;          // 00
    uint8 index_1;          // 01
    uint8 kind_2;           // 02
    uint8 value_3;          // 03
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 reserved09[3];    // 09
    uint32 value_C;         // 0C
    uint8 reserved10[0xC];  // 10
    sint16 x_1C;            // 1C
    sint16 y_1E;            // 1E
    sint16 z_20;            // 20
    uint8 reserved22[0x16]; // 22
    STCOM_SVECTOR pos_38;   // 38
} STCOM10_OBJ50;

// A routine table (the pools' handlers, at fixed scratchpad addresses).
typedef void (*STCOM10_OBJ_FUNC)(void *wp);

// A pending entry: its index in the room table and a flag byte (0xFF ends the list).
typedef struct
{
    sint8 index;
    uint8 flag;
} STCOM10_PAIR;

typedef void (*STCOM10_FUNC)(STCOM10_WORK *wp);

extern STCOM10_FUNC stcom10_D_0000[];   // routine_0 handlers (stcom10_func_0000)
extern STCOM10_AREA **stcom10_D_000C[]; // tables by stage (Game_work.value_50) and room (value_51)
extern uint32 stcom10_E_0000;         // the pools' allocation masks at the last area change: 0x5A4
extern uint32 stcom10_E_0004;         // 0x3C0
extern uint32 stcom10_E_0008;         // 0x10C
extern uint32 stcom10_E_000C;         // 0x50
extern STCOM10_PAIR stcom10_E_0010[]; // the objects spawned in the area, ended by flag 0xFF

// The pools' handler tables (scratchpad).
#define STCOM10_TABLE_3C0 (*(STCOM10_OBJ_FUNC ***)0x1F800058)
#define STCOM10_TABLE_5A4 (*(STCOM10_OBJ_FUNC ***)0x1F80005C)
#define STCOM10_TABLE_10C (*(STCOM10_OBJ_FUNC **)0x1F800060)
#define STCOM10_TABLE_50  (*(STCOM10_OBJ_FUNC **)0x1F80006C)

// ROCK_NEO.EXE.
extern uint32 D_800987E8; // allocation masks: 0x3C0 slots
extern uint32 D_80098B20; // 0x5A4
extern uint32 D_800987CC; // 0x10C
extern uint32 D_800989CC; // 0x50
void Sce_flag_off(sint32 flag);
sint32 Sce_flag_test(sint32 flag);
sint32 func_8002FE74(uint8 id);
STCOM10_OBJ *func_80036294(uint8 id);
STCOM10_OBJ *func_80031418(void);
STCOM10_OBJ *func_80031498(void);
STCOM10_OBJ *func_80031518(void);
STCOM10_OBJ50 *func_80031734(void);

void stcom10_func_0134(STCOM10_WORK *wp);

#endif // STCOM10_H
