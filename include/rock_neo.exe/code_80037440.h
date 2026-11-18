#ifndef ROCK_NEO_CODE_80037440_H
#define ROCK_NEO_CODE_80037440_H

#include "player.h"

typedef struct
{
    sint16 value0, value1, value2, value3;
} CODE374_VALUES;

typedef struct
{
    uint16 flags;
    uint8 reserved02[10];
} CODE374_STATUS;

#define CODE374_STATUS_PTR  ((CODE374_STATUS *)0x8015C006)
#define CODE374_STATUS_MASK 0x0FFF
#define CODE374_GROUP_MASK  0x000F0000

extern CODE374_VALUES *D_80089EAC[];
extern CODE374_STATUS D_8015C006[];
extern uint8 D_8015C008[];

// Map object record (12 bytes): position, then the status word at +6.
typedef struct
{
    sint16 x;
    sint16 y;
    sint16 z;
    uint16 flags;
    sint32 *data;
} CODE374_ENTRY;

extern CODE374_ENTRY D_8015C000[];
#define CODE374_ENTRY_PTR ((CODE374_ENTRY *)0x8015C000)

// Small data ($gp-addressed in retail).
extern uint16 D_80097D24;

extern uint16 D_8009A378[];
// Neighbour offsets: eight x/z pairs, then four.
extern sint8 D_80089EEC[8];
extern sint8 D_80089EF4[8];
extern sint8 D_80089EFC[4];
extern sint8 D_80089F00[4];
extern uint8 D_800899E0[][16];

#define CODE374_MAP_W (*(uint16 *)0x1F800044)
#define CODE374_MAP_H (*(uint16 *)0x1F800046)
#define CODE374_MAP   (*(sint16 **)0x1F800048)
#define CODE374_MAP_X (*(uint8 *)0x1F800040)
#define CODE374_MAP_Z (*(uint8 *)0x1F800041)

// Map object the slot table points at: an offset vector and a packed size word.
typedef struct
{
    uint8 reserved00[0xC];
    CODE374_VALUES ofs;
    uint32 size;
} CODE374_OBJ;

// Effect record from func_80031618 (fields this file sets).
typedef struct
{
    uint8 kind_0;
    uint8 reserved01;
    uint8 value_2;
    uint8 value_3;
    uint8 reserved04[0x18];
    sint16 x_1c;
    sint16 y_1e;
    sint16 z_20;
    uint8 reserved22[0x16];
    sint16 x_38;
    sint16 y_3a;
    sint16 z_3c;
} CODE374_FX;

#define CODE374_STATUS_PTR2(status) (*(sint32 **)((uint8 *)(status) + 2))

sint32 func_80049C24(PL_WORK *wp);
sint32 func_8004B414(PL_WORK *wp);
void func_80037818(uint16 index);
void func_80037C50(uint16 index);
void func_80037CD8(uint16 cell);
void func_8003777C(uint16 index, uint32 amount);
void func_80037890(sint32 mode, sint32 count, uint16 index);
sint32 rsin(sint32 a);
sint32 rcos(sint32 a);

#endif
