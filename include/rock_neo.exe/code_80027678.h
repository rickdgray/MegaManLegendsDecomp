#ifndef CODE_80027678_H
#define CODE_80027678_H

// code_80027678.c (not identified yet; rename with the file).

#include "common.h"
#include "code_8002D9A0.h"
#include "code_8002E7A8.h"

// Colour c (0xBBGGRR) with each channel scaled by r, g, b (0x80 = unchanged).
#define RGB_SCALE(c, r, g, b)                                                                                                              \
    ((((((c)&0xFF) * (r)) >> 7) & 0xFF) | (((((c)&0xFF00) * (g)) >> 7) & 0xFF00) | (((((c)&0xFF0000) * (b)) >> 7) & 0xFF0000))

// A slot is drawn when bit 1 is set in both be_flag and flags (bit 0 is the update's; see
// Work_3C0_tbl); bits 2-4 of be_flag pick its draw function in D_800898D0.
#define WORK_DRAW 2

// Draw function of an EFC (D_800898D0), given the slot's be_flag as flags.
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

// A line queued by Billboard_line_get is 8 words in the same list, told apart from a BILLBOARD by
// the code byte (0x20-0x3F polygon, else line), and walked as words (billboard_queue_draw): a LINE_G2
// (0 tag, 1 colour and code, 2 xy0, 3 colour, 4 xy1) whose words 0, 2 and 4 hold the world x, y of
// the second end, of the first end, and the z of both until it is projected, followed by a
// two-word primitive (5 its tag, 6 and 7) linked ahead of it.

// Face of a PRIM_MESH: a primitive for each display buffer (Dbl_buff_idx), built ahead with its
// texture, CLUT and colour (prim_mesh_tri_draw only writes the screen positions and links it), then
// its vertex indices packed as bytes (corner n in bits 8n..8n+7; the fourth only for quads).
typedef struct
{
    POLY_FT3 prim[2];
    uint32 idx; // 0x40
} PRIM_TRI;     // 0x44 bytes

typedef struct
{
    POLY_FT4 prim[2];
    uint32 idx; // 0x50
} PRIM_QUAD;    // 0x54 bytes

// Mesh of pre-built primitives (prim_mesh_tri_draw, prim_mesh_quad_draw): pl_body_draw passes
// the entries of a table it puts in the scratchpad word 0x1F8000E8 (Scratch_mesh_tbl), and &vtx
// with each. The face tables are followed by a copy of themselves, the faces' original texture
// coordinates (prim_mesh_uv_copy).
typedef struct
{
    uint8 n_tri;  // 0x00
    uint8 n_quad; // 0x01
    uint8 pad_2[2];
    PRIM_TRI *tri;   // 0x04
    PRIM_QUAD *quad; // 0x08
    SVECTOR *vtx;    // 0x0C
} PRIM_MESH;         // 0x10 bytes

// The scratchpad word of Scratch_mesh_tbl (code_8002D9A0.h), holding the PRIM_MESH being drawn
// while pl_body_draw walks a body part's meshes.
#define Scratch_prim_mesh (*(PRIM_MESH **)0x1F8000E8)

// Shadow queued by Pos_Shadow_Trans / Model_Shadow_Trans (Shadow_tbl, counted by Shadow_num) and
// drawn by shadow_draw_all (shadow_draw).
typedef struct
{
    SVECTOR pos; // 0x00 on the ground; pad: angle (bits 0-11) and half spread >> 6 (12-15),
                 // replaced by the texture when drawn
    uint16 r;    // 0x08 radius (bits 0-13), texture (14-15)
    sint16 dist; // 0x0A height above the ground
} SHADOW;        // 0x0C bytes

#define SHADOW_MAX 64

// Two PRIM_MESHes at fixed addresses in the heap (outside the image), whose textures
// func_8002D004 picks from a grid of 6 columns of 42 x 51 cells.
#define D_800F7820 ((PRIM_MESH *)0x800F7820)
#define D_800F7830 ((PRIM_MESH *)0x800F7830)

extern PRIM_MESH *D_800898EC[3][5];          // by body variant: first mesh of each of the 5 body parts
extern uint8 D_80089928[3][5];               // by body variant: number of meshes of each body part
extern uint8 D_80089938[];                   // joint (PL_WORK.joint_mtx) of each mesh, in that order
extern EFC_DRAW_FUNC D_800898D0[7];          // by bits 2-4 of be_flag: sprite, model, ...
extern uint32 Shadow_num;                    // number of queued shadows (cleared by func_8002CFA4)
extern SHADOW Shadow_tbl[SHADOW_MAX];        // the queued shadows
extern uint32 D_800988FC;                    // number of queued billboards
extern BILLBOARD *D_800BE6D8[BILLBOARD_MAX]; // the queued billboards (and line primitives)

void Obj_draw_all(void);
void Model_draw_all(void); // draws the live objects of D_800C3580 and D_8009F108
void Model_parts_draw(MODEL_WORK *wp);
void Pl_Shadow_Trans(struct PL_WORK *pl, sint32 r, sint32 spread, sint32 tex);
void Model_Shadow_Trans(MODEL_WORK *obj, sint32 r, sint32 spread, sint32 tex);
void Pos_Shadow_Trans(SVECTOR *pos, sint32 r, sint32 spread, sint32 ang);
void func_8002CFA4(void);
void func_8002D004(struct PL_WORK *pl, uint32 a, uint32 b); // pl is unused
MESH_FACE *Model_face_get(PARTS_MODEL *model, uint32 id);
void Model_face_uv_set(PARTS_MODEL *model, uint32 id, MESH_UV *uv);
SVECTOR *Model_vertex_get(PARTS_MODEL *model, uint32 id);
void Model_mesh_uv_copy(PARTS_MODEL *model, uint32 parts, sint32 delta);
uint32 Model_uv_cell(uint32 cell, uint32 w, uint32 h, uint32 cols);
uint32 *Billboard_get(void);      // queues a 0x28-byte primitive (a BILLBOARD), or NULL
uint32 *Billboard_line_get(void); // queues a 0x20-byte line primitive (func_80047EC8), or NULL

#endif // CODE_80027678_H
