#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "psyq/libgte.h"

// Scratchpad map window: origin (0x40, 0x41), size (0x44, 0x46), cell data at 0x48.
#define Map_org_x (*(uint8 *)0x1F800040)
#define Map_org_y (*(uint8 *)0x1F800041)
#define Map_w     (*(uint16 *)0x1F800044)
#define Map_h     (*(uint16 *)0x1F800046)
#define Map_cells (*(uint16 **)0x1F800048)

// The stage's IDX file, loaded at 0x8015C000 (notes/disc.md): 12-byte entries, position in
// 1/512 units. Addressed by literal address, like the scratchpad: the target builds it with
// lui/ori, and maspsx gives `addu at,idx,at` only for a constant (notes/rock_neo.md).
#define Stage_idx_tbl ((IDX_ENT *)0x8015C000)

// EBD files (notes/disc.md): a count word, then that many 16-byte entries that bind an object's
// kind and id to its model data (searched by func_8002FA38). The stage has two, SUPPORT one.
#define Stage_ebd_0 ((sint32 *)0x8016C000)
#define Stage_ebd_1 ((sint32 *)0x80190000)
#define Support_ebd ((sint32 *)0x801F2000)

// Shape data an entry points to (partial).
typedef struct
{
    sint32 head; // 0x00: negative selects func_80037818's path in func_8003777C
    uint8 unk04[8];
    SVECTOR ofs; // 0x0C
    uint32 size; // 0x14: low half width, high half >> 1 spread
} IDX_SHAPE;

typedef struct
{
    sint16 x; // 0x00
    uint8 unk02[2];
    sint16 y;       // 0x04
    uint16 val;     // 0x06: low 12 bits value (counted down by func_8003777C), high 4 bits shift
    IDX_SHAPE *ptr; // 0x08
} IDX_ENT;

// An object tested against the IDX entries (func_80037694, func_80049C24); type unknown (partial).
typedef struct
{
    uint8 unk00[0xC4];
    uint32 unkC4; // top byte nonzero: skip
} STAGE_OBJ;

// Collision box passed to func_8004B5CC/func_80048EA4: three (min, max) halfword pairs, each
// -n, +n in the tables (D_8008A310, D_8008A618). max_A is the half-height kept clear above the
// ground (func_80046438).
typedef struct
{
    sint16 min_0;
    sint16 max_2;
    sint16 min_4;
    sint16 max_6;
    sint16 min_8;
    sint16 max_A;
} HIT_ENT;

// Stack of packed map cells (x | y << 8); Cell_stack_idx (code_80037534's .sdata) is the count.
extern uint16 D_8009A376[];
extern uint16 Cell_stack[];

// Neighbour offsets for func_80037CD8: 8 around a cell (x, y), then 4 edge-adjacent (x, y).
extern sint8 D_80089EEC[8];
extern sint8 D_80089EF4[8];
extern sint8 D_80089EFC[4];
extern sint8 D_80089F00[4];

// code_80048620
sint32 func_80049C24(STAGE_OBJ *obj); // the IDX entry obj touches, or 0
void func_8004B414(STAGE_OBJ *obj);
sint32 func_8004920C(SVECTOR *v); // defined in code_80048620.c
// Moves pos along the ground; returns the height of the surface below it.
sint32 func_80048EA4(SVECTOR *pos, HIT_ENT *ent, sint32 angle, uint32 mask);
// Collides the move old -> pos against ent; returns hit flags (0x1000 = floor).
sint32 func_8004B5CC(SVECTOR *pos, SVECTOR *old, sint32 n, HIT_ENT *ent);
void func_8004AC8C(void *vel, sint32 hit);

#endif // STAGE_H
