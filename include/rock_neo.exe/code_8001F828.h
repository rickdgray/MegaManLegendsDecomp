#ifndef CODE_8001F828_H
#define CODE_8001F828_H

#include "common.h"

// Draws one map block's model (data pointer, depth). Picked from Map_block_draw_tbl[kind][bit 31 of the
// model's LOD word].
typedef void (*MAP_DRAW_FUNC)(uint32 *model, sint32 z);

// [kind][bit 31 of the LOD word]: every entry is one of this file's draw functions.
extern MAP_DRAW_FUNC Map_block_draw_tbl[4][4];

// Pool variable (0x800987D4): cleared by func_8002037C and debug_mem_dump, tested by func_8001FE38.
extern sint8 D_800987D4;
// Pool variable (0x800987DC): cleared by func_8002037C, read and stepped by func_8001FE38 and
// func_800203A8.
extern sint8 D_800987DC;
// Pool variable (0x8009893C): write pointer into D_800BEAD8 (func_8001FE38 advances it;
// func_8002037C and func_800203A8 reset it to the start).
extern char *D_8009893C;
// Debug text queue: func_8001FE38 appends entries (position bytes, then the text) while
// D_8009893C is below D_800BEF88; func_800203A8 reads it each frame.
extern char D_800BEAD8[];

// func_8001FE38's position word: column (8-pixel units), row, and the bits from 17 up.
#define TEXT_POS(x, y, c) (((x) << 3) | ((y) << 12) | ((c) << 17))

void func_8001FE38(sint32 pos, char *fmt, ...); // printf-style debug text
void func_80020A40(void);                       // zeroes D_80097C3C
void func_8002037C(void);                       // called at the end of System_init
void func_800203A8(void);                       // called once per frame by main

#endif
