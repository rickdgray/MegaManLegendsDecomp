#ifndef STCOM19_H
#define STCOM19_H

#include "common.h"
#include "stage_common/rock_neo.h"
#include "stage_common/gte.h"

// A matrix whose identity setup writes its halfwords two at a time.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STCOM19_MATRIX;

// The 0x50-byte work slot of a floor panel that turns over (func_80031734).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01;      // 01
    uint8 kind_2;          // 02
    uint8 value_3;         // 03: 0xFF for the spawner
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 reserved09[2];   // 09
    uint8 timer_B;         // 0B
    sint8 dir_C;           // 0C: rotation.y / 0x400
    uint8 value_D;         // 0D
    uint8 reserved0E[0xA]; // 0E
    STCOM19_MATRIX matrix; // 18: words[5] and words[6] hold the cell values to restore
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    sint32 cell_44;        // 44: index into the room's cell table
    uint8 reserved48[8];   // 48
} STCOM19_WORK;

// A room cell (ROCK_NEO's table at 0x8015C000, 12 bytes each), seen from its value word.
typedef struct
{
    uint32 value;
    uint8 reserved4[8];
} STCOM19_CELL;

// The cells at their fixed address: GCC adds the index before the base, as retail does.
#define STCOM19_CELLS ((STCOM19_CELL *)0x8015C008)

// A room cell's record (ROCK_NEO's table at 0x8015C000): its position and its attribute.
typedef struct
{
    STCOM_SVECTOR pos;
    uint32 *info;
} STCOM19_CELL_REC;

#define STCOM19_CELL_TBL ((STCOM19_CELL_REC *)0x8015C000)

// A panel to spawn on every cell whose attribute is type_4: two panels, one per byte of spawn_E
// (variant in the high nibble, direction in the low one).
typedef struct
{
    uint32 key_0;     // 00: 0 ends the list
    uint32 type_4;    // 04
    sint16 x_8;       // 08
    sint16 y_A;       // 0A
    sint16 z_C;       // 0C
    uint8 spawn_E[2]; // 0E
} STCOM19_SPAWN;

// The rooms that have panels: stage 0xFF ends the table.
typedef struct
{
    uint8 stage;
    uint8 room;
    uint8 reserved2[2];
    STCOM19_SPAWN *list;
} STCOM19_ROOM;

// A panel's offset from its cell, per direction.
typedef struct
{
    sint16 x, z;
} STCOM19_OFFSET;

// The scratchpad's view of the current room's map.
#define STCOM19_MAP_X0    (*(uint8 *)0x1F800040)
#define STCOM19_MAP_Z0    (*(uint8 *)0x1F800041)
#define STCOM19_MAP_X1    (*(uint8 *)0x1F800042)
#define STCOM19_MAP_Z1    (*(uint8 *)0x1F800043)
#define STCOM19_MAP_W     (*(uint16 *)0x1F800044)
#define STCOM19_MAP_CELLS (*(sint16 **)0x1F800048)

// Game_work's panel count at +0x7E.
#define STCOM19_GAME_COUNT (*((uint8 *)&Game_work + 0x7E))

typedef void (*STCOM19_FUNC)(STCOM19_WORK *wp);

extern STCOM19_ROOM stcom19_D_0000[];
extern STCOM19_FUNC stcom19_D_0150[];
extern STCOM19_OFFSET stcom19_D_0140[];

void stcom19_func_0640(void);

// ROCK_NEO.EXE.
sint32 Sce_flag_test(sint32 flag);
void Sce_flag_off(sint32 flag);
void Sound_call(sint32 id, sint32 a1, sint32 a2);
sint32 func_80048C60(STCOM_SVECTOR *pos);
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);
STCOM19_WORK *func_80031734(void);
void func_80031A4C(STCOM19_WORK *wp);
void ApplyMatrix(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_FIXED_VECTOR *out);
uint32 func_8003AC24(uint32 key);

#endif // STCOM19_H
