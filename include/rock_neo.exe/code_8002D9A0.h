#ifndef CODE_8002D9A0_H
#define CODE_8002D9A0_H

// code_8002D9A0.c's subsystem (not identified yet; rename with the file).

#include "common.h"
#include "psyq/libgte.h"

// Get/set accessors used only by the stage overlays (func_8002DD1C ... func_8002DE34): they
// copy whole words in and out of tables the caller passes. The tables are word-aligned; the
// getters return a struct with less than word alignment (copied out with lwl/lwr), filled
// through a sint32 pointer. What the words hold is not known yet; the return types may well
// be PsyQ's DVECTOR/SVECTOR or similar 2-aligned structs. The tables come from the stage
// overlays (the only callers, not disassembled), so they stay views until those are read.

// 4-, 8- and 12-byte values as the getters return them.
typedef struct
{
    uint8 b[4];
} BYTES4;

typedef struct
{
    uint8 b[8];
} BYTES8;

typedef struct
{
    uint8 b[12];
} BYTES12;

// Entry of the 8-byte tables (func_8002DD1C, func_8002DE04).
typedef struct
{
    sint32 w[2];
} WORDS2;

// Entry of the 16-byte tables: one word, then three (func_8002DD68, func_8002DDA0,
// func_8002DE20, func_8002DE34).
typedef struct
{
    sint32 w[3];
} WORDS3;

typedef struct
{
    sint32 head;
    WORDS3 body;
} WORDS4;

// Object func_8002DC84 reads: a table of block pointers at +0x18. Origin unknown: its only
// callers are stage overlays (ST00 ... ST1E, per tools/callers.py), which aren't disassembled,
// and nothing in ROCK_NEO's own code or data reaches func_8002DC84.
typedef struct
{
    uint8 pad_0[0x18];
    uint32 *blk_tbl[1]; // [blk]; real length unknown
} BLK_SRC;

// Entry func_8002DC84 returns from a block: the block's first word (its low byte is the
// header length in words, before the 8-byte entries), and one entry's two words with their
// low 24 bits turned into KSEG0 addresses (0x80000000 | offset).
typedef struct
{
    uint32 head;  // block word 0
    uint32 hi;    // top byte of the entry's word 1
    uint32 addr0; // entry word 0 as an address
    uint32 addr1; // entry word 1 as an address
} BLK_ENT;

// Face of a MESH: texture coordinates (u, v byte pairs) of its corners, then its vertex
// indices packed as bytes (corner n in bits 8n..8n+7; the fourth only for quads).
typedef struct
{
    uint16 uv[4];
    uint32 idx;
} MESH_FACE;

// Textured mesh drawn by mesh_draw. Its only caller, parts_model_draw (assembly), passes
// entry n of the MESH array whose address is in the scratchpad word 0x1F8000E8, n being a byte
// at +0x4F8 of the object parts_model_draw is given. That word is set to model data + 0x14 by
// code_80027678 (func_8002786C, func_8002831C, func_80028F90, all assembly), from tables and
// object fields with no C type yet; no existing type describes the mesh.
typedef struct
{
    uint8 n_tri;       // 0x00
    uint8 n_quad;      // 0x01
    uint8 n_vtx;       // 0x02 a multiple of 3 (projected three at a time)
    uint8 pad_3;       // 0x03
    MESH_FACE *tri;    // 0x04
    MESH_FACE *quad;   // 0x08
    uint32 clut_tpage; // 0x0C CLUT in the high half, texture page in the low half
    SVECTOR *vtx;      // 0x10
} MESH;

// Model data of a PARTS_WORK: three levels of detail, each a MESH array whose entry 0 is skipped
// (parts_model_draw uses &lod[n][1], entry 1 for part mesh 0).
typedef struct
{
    uint8 pad_0[0x70];
    MESH *lod[3]; // 0x70: near (z <= 0x2BC), middle (z <= 0x708), far
} PARTS_MODEL;

// Part entry of a PARTS_WORK.
typedef struct
{
    uint8 mesh;   // mesh index in the chosen level of detail
    sint8 n_part; // entry 0 only: number of parts drawn
    uint8 pad_2;
    sint8 hide; // < 0: part not drawn
} PART_ENT;

// 0x560-byte object drawn part by part by parts_model_draw. Its caller, parts_model_draw_all, walks two
// arrays of these with a 0x560 stride: 4 from D_800C3580 and 16 from D_8009F108 (where
// code_8002E7A8.h has WORK_5A4 and WORK_3C0, which don't fit that stride; not resolved yet),
// drawing those with bit 1 of byte 0 set. It reaches both arrays by constant address
// (Parts_work_tbl0, Parts_work_tbl1).
typedef struct
{
    uint8 flags; // bit 1: drawn by parts_model_draw_all
    uint8 pad_1[0xB];
    SVECTOR pos; // 0x0C: projected to choose the level of detail and cull the object
    uint8 pad_14[0x6C];
    PARTS_MODEL *model_80;
    uint8 pad_84[0xB4];
    MATRIX part_mtx[24];  // 0x138: rotation of each part (relative to the view)
    SVECTOR part_pos[24]; // 0x438: position of each part; pad: RGB555 colour (when col_55E is 0)
    PART_ENT part[24];    // 0x4F8
    uint8 pad_558[6];
    sint16 col_55E; // RGB555 colour of the whole object; 0: each part's own
} PARTS_WORK;       // 0x560 bytes

// The two PARTS_WORK arrays parts_model_draw_all draws, addressed by constant in the source (lui/ori);
// the same memory as D_800C3580 and D_8009F108.
#define Parts_work_tbl0 ((PARTS_WORK *)0x800C3580) // [4]
#define Parts_work_tbl1 ((PARTS_WORK *)0x8009F108) // [16]

// RGB555 colour (bit 15: semi-transparency) to a primitive's colour and code word: 8-bit R, G, B
// and the code's semi-transparency bit (0x02000000).
#define RGB555_TO_RGBC(c) ((((c)&0x1F) << 3) | (((c)&0x3E0) << 6) | (((c)&0x7C00) << 9) | (((c)&0x8000) << 10))

// Scratchpad: the MESH array mesh_draw's caller indexes (set to a model's mesh table by
// parts_model_draw and by code_80027678).
#define Scratch_mesh_tbl (*(MESH **)0x1F8000E8)

extern MATRIX D_80097CD4; // identity rotation, zero translation (.sdata, owner not known)

BLK_ENT func_8002DC84(BLK_SRC *src, sint32 blk, sint32 idx);
BYTES8 func_8002DD1C(WORDS2 *tbl, sint32 idx);
BYTES4 func_8002DD68(WORDS4 *tbl, sint32 idx);
BYTES12 func_8002DDA0(WORDS4 *tbl, sint32 idx);
void func_8002DE04(WORDS2 *tbl, sint32 idx, WORDS2 *val);
void func_8002DE20(WORDS4 *tbl, sint32 idx, sint32 *val);
void func_8002DE34(WORDS4 *tbl, sint32 idx, WORDS3 *val);

#endif
