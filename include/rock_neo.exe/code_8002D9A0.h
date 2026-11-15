#ifndef CODE_8002D9A0_H
#define CODE_8002D9A0_H

// code_8002D9A0.c's subsystem (not identified yet; rename with the file).

#include "common.h"
#include "psyq/libgte.h"

// Get/set accessors used only by the stage overlays (func_8002DD1C ... func_8002DE34): they
// copy whole words in and out of tables the caller passes. The tables are word-aligned; the
// getters return a struct with less than word alignment (copied out with lwl/lwr), filled
// through a sint32 pointer. What the words hold is not known yet; the return types may well
// be PsyQ's DVECTOR/SVECTOR or similar 2-aligned structs.

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

// Object func_8002DC84 reads (passed in by the stage overlays; origin unknown): a table of
// block pointers at +0x18.
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

// Textured mesh drawn by func_8002E3D0 (origin unknown).
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

extern MATRIX D_80097CD4; // identity rotation, zero translation (.sdata, owner not known)

BLK_ENT func_8002DC84(BLK_SRC *src, sint32 blk, sint32 idx);
BYTES8 func_8002DD1C(WORDS2 *tbl, sint32 idx);
BYTES4 func_8002DD68(WORDS4 *tbl, sint32 idx);
BYTES12 func_8002DDA0(WORDS4 *tbl, sint32 idx);
void func_8002DE04(WORDS2 *tbl, sint32 idx, WORDS2 *val);
void func_8002DE20(WORDS4 *tbl, sint32 idx, sint32 *val);
void func_8002DE34(WORDS4 *tbl, sint32 idx, WORDS3 *val);

#endif
