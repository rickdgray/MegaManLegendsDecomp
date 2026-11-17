#ifndef SCRATCH_H
#define SCRATCH_H

// ROCK_NEO's scratchpad (0x1F800000, 1 KB of fast RAM), addressed by literal address like the
// shim's (see CLAUDE.md, "Literal addresses"). The map window is in stage.h.

#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"

// Same names and layout as the shim's: the current double buffer (0/1; moji indexes D_80097F50's
// draw areas by it) and vsyncs per frame (code_800133D8's func_80013420 sets 2).
#define Dbl_buff_idx (*(uint8 *)0x1F800000)
#define Vsync_wait   (*(uint8 *)0x1F800001)

// Frame counter (also in symbol_addrs, absolute, for the assembly).
#define System_timer (*(uint16 *)0x1F800002)

// World-to-screen matrix: loaded into the GTE before projecting world positions (func_80035508).
#define Scratch_view_mtx (*(MATRIX *)0x1F800008)

// The frame's ordering table: primitives are linked at Scratch_ot[z / 8] (billboard_draw).
#define Scratch_ot (*(u_long **)0x1F80003C)

// Next free byte of the frame's primitive buffer. Capcom's name and type (sub_scrn.c in
// disc/tcrf.txt: `Map_prim_ptr = (POLY_FT4 *)ft4_buff_ptr2;`). Code that takes one POLY_FT4-sized
// slot per primitive steps it with ++ (screen_tile_draw: a TILE, then a DR_MODE); mesh_draw steps it
// by each primitive's own size (0x20 for a POLY_FT3).
#define Map_prim_ptr (*(POLY_FT4 **)0x1F800070)

// Scratchpad scene scale and fog parameters (written by func_8003697C / func_800369C0).
#define Scratch_scale_shift                                                                                                                \
    (*(uint8 *)0x1F800074) // 0 normal, 1 = coordinates doubled, fog distances halved (func_800369C0); also a table index (0-2)

#define Scratch_fog_0 (*(uint16 *)0x1F800006)
#define Scratch_fog_1 (*(uint16 *)0x1F800076)
#define Scratch_fog_2 (*(uint8 *)0x1F800078) // byte +0x23 of the fog block (func_800371A0)

// Bits OR'd into a textured primitive's uv0/CLUT word: the fog CLUT row offset (<< 16) that
// billboard_draw picks by depth.
#define Scratch_clut_bits (*(u_long *)0x1F8000E0)

// Color and code word given to the primitives mesh_draw builds (code OR'd in).
#define Scratch_rgbc (*(u_long *)0x1F8000E4)

// Depth-cueing value (GTE IR0) of the object being drawn, stored after projecting its position
// (parts_model_draw).
#define Scratch_dp (*(long *)0x1F8000EC)

// Translation loaded with Scratch_view_mtx's rotation to project an object's position
// (parts_model_draw).
#define Scratch_trans (*(VECTOR *)0x1F800030)

// Per-vertex screen XY and Z of the mesh mesh_draw is drawing (vertex index).
#define Scratch_sxy ((long *)0x1F800100)
#define Scratch_sz  ((uint16 *)0x1F800300)

// Scratchpad working matrix (func_80033D80).
#define Scratch_mtx (*(MATRIX *)0x1F8000C0)

// Scratchpad pose unpacking (func_80033A28): 0x20 packed words at 0x1F800180 become 25 SVECTORs
// of 12-bit values at 0x1F800120.
#define Scratch_pose_packed ((uint32 *)0x1F800180)

#define Scratch_pose_vtx ((sint16 *)0x1F800120)

#endif // SCRATCH_H
