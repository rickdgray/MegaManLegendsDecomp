#ifndef CODE_80027678_H
#define CODE_80027678_H

// code_80027678.c (not identified yet; rename with the file).

#include "common.h"
#include "code_8002D9A0.h"
#include "code_8002E7A8.h"

// A slot is drawn when bit 1 is set in both routine_0 and flags (bit 0 is the update's; see
// Work_3C0_tbl); bits 2-4 of routine_0 pick its draw function in D_800898D0.
#define WORK_DRAW 2

// Draw function of an EFC (D_800898D0), given the slot's routine_0 as flags.
typedef void (*EFC_DRAW_FUNC)(EFC *efc, sint32 flags);

// Billboard sprite queued by Billboard_get (0x28 bytes from Map_prim_ptr, listed in
// D_800BE6D8, counted by D_800988FC): a POLY_FT4 whose vertex words hold the sprite's world
// position, half size and flags until billboard_draw projects it and links it into the
// ordering table. Billboard_get still returns it as a uint32 * (its user writes it by index).
typedef struct
{
    u_long tag;       // 0x00
    u_long rgbc;      // 0x04 r0, g0, b0, code
    sint32 xy0;       // 0x08 before: world x, y (two sint16)
    u_long uv0_clut;  // 0x0C
    sint32 xy1;       // 0x10 before: world z (sint16)
    u_long uv1_tpage; // 0x14
    sint32 xy2;       // 0x18 before: half size
    u_long uv2;       // 0x1C
    sint32 xy3;       // 0x20 before: flags (BILLBOARD_NO_FOG)
    u_long uv3;       // 0x24
} BILLBOARD;

#define BILLBOARD_NO_FOG 8 // xy3 flag: keep the color, no depth cue or fog CLUT

#define BILLBOARD_MAX 0x100

extern EFC_DRAW_FUNC D_800898D0[7];          // by bits 2-4 of routine_0: sprite, model, ...
extern uint32 D_800987D8;                    // cleared by func_8002CFA4
extern uint32 D_800988FC;                    // number of queued billboards
extern BILLBOARD *D_800BE6D8[BILLBOARD_MAX]; // the queued billboards (and line primitives)

void func_8002CFA4(void);
MESH_FACE *Model_face_get(PARTS_MODEL *model, uint32 id);
void Model_face_uv_set(PARTS_MODEL *model, uint32 id, MESH_UV *uv);
SVECTOR *Model_vertex_get(PARTS_MODEL *model, uint32 id);
void Model_mesh_uv_copy(PARTS_MODEL *model, uint32 parts, sint32 delta);
uint32 Model_uv_cell(uint32 cell, uint32 w, uint32 h, uint32 cols);
uint32 *Billboard_get(void);      // queues a 0x28-byte primitive (a BILLBOARD), or NULL
uint32 *Billboard_line_get(void); // queues a 0x20-byte line primitive (func_80047EC8), or NULL

#endif // CODE_80027678_H
