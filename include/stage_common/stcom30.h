#ifndef STCOM30_H
#define STCOM30_H

#include "common.h"
#include "stage_common/rock_neo.h"

// An object to spawn (a 0x14-byte record; flags_0 -1 ends the list).
typedef struct
{
    sint8 flags_0;       // 00: -1 ends the list
    uint8 kind_1;        // 01: pool (0x20, 0x60 or 0xE0)
    uint8 value_2;       // 02
    uint8 value_3;       // 03
    uint8 value_4;       // 04
    uint8 value_5;       // 05
    uint8 reserved06;    // 06
    uint8 rotation_7;    // 07: rotation.y / 16
    sint8 value_8;       // 08
    uint8 value_9;       // 09
    uint8 value_A;       // 0A
    uint8 value_B;       // 0B
    STCOM_SVECTOR pos_C; // 0C
} STCOM30_SPAWN;

// A work slot as stcom30 sets it up (func_80031418, Open_SHL_WORK).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 work_id;                     // 01
    uint8 id;                          // 02
    uint8 type;                        // 03
    uint8 handler;                     // 04
    uint8 value_5;                     // 05
    uint8 reserved06[6];               // 06
    uint8 value_C;                     // 0C
    uint8 value_D;                     // 0D
    uint8 value_E;                     // 0E
    uint8 value_F;                     // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x28];            // 2C
    STCOM_SVECTOR rotation;            // 54
} STCOM30_OBJ;

// A 0x50-byte slot (func_80031734).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 id;               // 02
    uint8 type;             // 03
    uint8 value_4;          // 04
    uint8 value_5;          // 05
    uint8 reserved06[6];    // 06
    uint8 value_C;          // 0C
    uint8 value_D;          // 0D
    uint8 value_E;          // 0E
    uint8 value_F;          // 0F
    uint8 reserved10[0x28]; // 10
    STCOM_SVECTOR pos_38;   // 38
} STCOM30_OBJ50;

// The 0x50-byte slot stcom30 runs on (freed through func_80031A4C).
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 reserved02[6];    // 02
    uint8 routine_0;        // 08
    uint8 spawned_9;        // 09: the room's objects are out
    uint8 reserved0A[0x22]; // 0A
    sint32 flag_2C[3];      // 2C: scene flags, one per switch
    uint8 reserved38[0x18]; // 38
} STCOM30_WORK;

extern STCOM30_SPAWN *stcom30_D_0000[]; // stage 0xE's objects by room
extern STCOM30_SPAWN *stcom30_D_000C[]; // stage 0x14's objects by room

void stcom30_func_02B4(STCOM30_WORK *wp, STCOM30_SPAWN *spawn);
void stcom30_func_0570(STCOM30_WORK *wp, STCOM30_SPAWN *spawn);

// ROCK_NEO.EXE.
sint32 Sce_flag_test(sint32 flag);
void Sce_flag_off(sint32 flag);
void func_80031A4C(STCOM30_WORK *wp);
STCOM30_OBJ *func_80031418(void);
STCOM30_OBJ *Open_SHL_WORK(void);
STCOM30_OBJ50 *func_80031734(void);

#endif // STCOM30_H
