#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "psyq/libgte.h"

// Scratchpad map window: origin (0x40, 0x41), size (0x44, 0x46), cell data at 0x48.
#define Map_org_x (*(uint8 *)0x1F800040)
#define Map_org_y (*(uint8 *)0x1F800041)
#define Map_w     (*(uint16 *)0x1F800044)
#define Map_h     (*(uint16 *)0x1F800046)
#define Map_cells (*(sint16 **)0x1F800048)
// The block grid: 0x40 rows of 0x20 MAP_BLOCKs (map_blocks_draw draws the rows' set bits).
#define Map_blocks (*(MAP_BLOCK **)0x1F80004C)

// The stage's IDX file, loaded at 0x8015C000 (notes/disc.md): 12-byte entries, position in
// 1/512 units. Addressed by literal address, like the scratchpad: the target builds it with
// lui/ori, and maspsx gives `addu at,idx,at` only for a constant (notes/rock_neo.md).
#define Stage_idx_tbl ((IDX_ENT *)0x8015C000)

// The 0x400 bytes below Stage_idx_tbl, cleared by Work_pools_init. The first 0x200 are two row
// masks of the block grid (0x40 words each, one bit per MAP_BLOCK): func_80023C08 passes
// 0x8015BC00 and 0x8015BD00 to map_blocks_draw/map_blocks_draw2, which draw the set blocks. The rest's
// use is unknown.
#define D_8015BC00 ((uint8 *)0x8015BC00)

// EBD files (notes/disc.md): a count word, then that many 16-byte entries that bind an object's
// kind and id to its model data (searched by func_8002FA38). The stage has two, SUPPORT one.
#define Stage_ebd_0 ((sint32 *)0x8016C000)
#define Stage_ebd_1 ((sint32 *)0x80190000)
#define Support_ebd ((sint32 *)0x801F2000)

// The STG files (notes/disc.md): arrays of STG_MODEL. The stage's loads at 0x80194000, SUPPORT's at
// 0x801F6000. Record 0 has id 0xFFFFFFFF; func_8003A744 relights SUPPORT's record 1.
#define Support_stg ((STG_MODEL *)0x801F6000)

// The stage HED file, loaded at 0x8013A000 (notes/disc.md): HED_ENTs, ended by one whose model is
// 0. func_8003A3B4 searches at most HED_ENT_MAX of them.
#define Stage_hed_tbl ((HED_ENT *)0x8013A000)
#define HED_ENT_MAX   0x200

#define STG_LOD_NUM  6
#define STG_LOD_WORD 6 // word index of STG_MODEL.lod

// One model record of an STG file. lod[0..2] point to its near/mid/far LOD and lod[3..5] to a
// second set (MAP_BLOCK); the low 24 bits are the address, bit 31 picks the draw function's column
// in Map_block_draw_tbl. Each LOD starts with a header word: its length in words - 1 (low byte)
// and a part count (bits 8-13).
typedef struct
{
    uint32 id; // 0x00: matches HED_ENT.id
    uint8 unk04[0x14];
    uint32 lod[STG_LOD_NUM]; // 0x18
} STG_MODEL;                 // 0x30 bytes

// One entry of the stage HED file.
typedef struct
{
    uint32 id;    // 0x0: STG_MODEL.id
    uint32 model; // 0x4: the STG_MODEL in the low 24 bits; 0 ends the list
} HED_ENT;

// One block of the map grid (Map_blocks): its position, and its STG_MODEL in the low 24 bits. The
// draw uses lod[0..2] by distance, or lod[3..5] when pos.pad is 0.
typedef struct
{
    SVECTOR pos;  // 0x0
    uint32 model; // 0x8
} MAP_BLOCK;

// Shape data an entry points to (partial).
typedef struct
{
    sint32 head; // 0x00: negative selects func_80037818's path in func_8003777C
    uint8 unk04[8];
    SVECTOR ofs;   // 0x0C
    uint32 size;   // 0x14: low half width, high half >> 1 spread
    uint16 *unk18; // 0x18: element 1 is copied to IDX_ENT.val by func_8003A3B4
} IDX_SHAPE;

typedef struct
{
    sint16 x; // 0x00
    uint8 unk02[2];
    sint16 y;       // 0x04
    uint16 val;     // 0x06: low 12 bits value (counted down by func_8003777C), high 4 bits shift
    IDX_SHAPE *ptr; // 0x08
} IDX_ENT;

// Stack of packed map cells (x | y << 8); Cell_stack_idx (code_80037534's .sdata) is the count.
extern uint16 D_8009A376[];
extern uint16 Cell_stack[];

// Neighbour offsets for func_80037CD8: 8 around a cell (x, y), then 4 edge-adjacent (x, y).
extern sint8 D_80089EEC[8];
extern sint8 D_80089EF4[8];
extern sint8 D_80089EFC[4];
extern sint8 D_80089F00[4];

// Stage overlay code (loaded with the stage; notes/rock_neo.md, "References outside the image").
void func_80101D94(void);

#endif // STAGE_H
