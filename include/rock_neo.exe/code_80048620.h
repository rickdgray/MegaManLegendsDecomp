#ifndef CODE_80048620_H
#define CODE_80048620_H

// code_80048620.c (not identified yet; rename with the file): the stage collision services. They
// take any model object (MODEL_WORK) and its collision box (HIT_ENT), both in code_8002E7A8.h.

#include "common.h"
#include "psyq/libgte.h"
#include "code_8002E7A8.h"

// Scratchpad byte of per-axis bits the collision code writes: x 1/2 (func_80050B74), z 4/8
// (func_80050BB4), y 0x10/0x20 (func_80050BF4), the low bit of each pair when the move was
// positive. func_80050A24/A90/AFC test them.
#define D_1F8000FF (*(uint8 *)0x1F8000FF)

// Scratchpad vector the collision code keeps; func_80050A24/A90/AFC test its vx/vz/vy.
#define D_1F8000D0 (*(SVECTOR *)0x1F8000D0)

// Scratchpad halfwords per axis (x, y, z); func_80050B74 clears x and func_80050BB4 clears z
// when their axis's bits in D_1F8000FF were set.
#define D_1F800106 ((sint16 *)0x1F800106)

// Scratchpad offset vector func_8004B3C0 sets (from its argument, or zero).
#define D_1F800124 (*(VECTOR *)0x1F800124)

// 12-byte entry pushed on the D_80098894 list by func_80051B68 (an object and its three
// arguments); D_800BC058 holds 0x40 of them.
typedef struct
{
    MODEL_WORK *obj;
    sint16 arg_4;
    sint16 arg_6;
    sint32 arg_8;
} OBJ_REQ;

// Two lists that func_80051BE4 walks and func_80051B40 resets: write pointers (pool small data)
// and their buffers.
extern OBJ_REQ *D_80098894;
extern MODEL_WORK **D_80098898;
extern OBJ_REQ D_800BC058[0x40];
extern MODEL_WORK *D_800BC360[];

// Per stage (Game_work.stage_no), the frame count of func_80048A9C's second wait.
extern uint8 D_8008AA04[];

sint32 func_80049C24(MODEL_WORK *obj); // the IDX entry obj touches, or 0
void func_8004B414(MODEL_WORK *obj);
sint32 func_8004920C(SVECTOR *v);
// Moves pos along the ground; returns the height of the surface below it.
sint32 func_80048EA4(SVECTOR *pos, HIT_ENT *ent, sint32 angle, uint32 mask);
// Collides the move old -> pos against ent; returns hit flags (0x1000 = floor).
sint32 func_8004B5CC(SVECTOR *pos, SVECTOR *old, sint32 n, HIT_ENT *ent);
void func_8004AC8C(void *vel, sint32 hit);
sint32 func_80049C54(SVECTOR *a, SVECTOR *b, sint32 arg2, sint32 arg3);
// If obj's routine_0 has bit 0 or 1 set, pushes obj on the list at D_80098898; clears +0x7C.
// Called with player objects, SHL_WORK shots and the stage overlays' objects.
void func_80051BAC(MODEL_WORK *obj);
sint32 func_80048CEC(sint32 index); // Map_cells[index]
sint32 func_80050B68(SVECTOR *v);   // v->vy != 0
sint32 func_80050BF4(SVECTOR *v);
void func_80051B40(void);
// Map_cells at pos, or 0 outside the map window.
sint32 Map_cell_get(SVECTOR *pos);
// 0 if pos is inside the map window, -1 outside.
sint32 Map_area_check(SVECTOR *pos);
// The cell of room map's map (Stage_map_tbl) at pos, or 0 outside it.
sint32 Stage_map_cell_get(sint32 map, SVECTOR *pos);
// The low 12 bits of the pad of the map block under pos, or 0.
sint32 func_80048E18(SVECTOR *pos);
// Reflects *angle off the walls in hit; 1 if there were any.
sint32 func_8004AE88(sint16 *angle, uint32 hit);
void func_8004B3C0(VECTOR *ofs);
sint32 func_80050A24(SVECTOR *v);
sint32 func_80050A90(SVECTOR *v);
sint32 func_80050AFC(SVECTOR *v);
void func_80050B74(SVECTOR *v);
void func_80050BB4(SVECTOR *v);
// If obj's routine_0 has bit 0 or 1 set, pushes obj and the three values on the D_80098894 list.
void func_80051B68(MODEL_WORK *obj, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80052644(sint32 key, MODEL_WORK *obj);

#endif // CODE_80048620_H
