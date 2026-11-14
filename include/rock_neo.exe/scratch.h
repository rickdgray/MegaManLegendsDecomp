#ifndef SCRATCH_H
#define SCRATCH_H

// ROCK_NEO's scratchpad (0x1F800000, 1 KB of fast RAM), addressed by literal address like the
// shim's (see CLAUDE.md, "Literal addresses"). The map window is in stage.h.

#include "common.h"
#include "psyq/libgte.h"

// Frame counter (also in symbol_addrs, absolute, for the assembly).
#define System_timer (*(uint16 *)0x1F800002)

// World-to-screen matrix: loaded into the GTE before projecting world positions (func_80035508).
#define Scratch_view_mtx (*(MATRIX *)0x1F800008)

// Scratchpad scene scale and fog parameters (written by func_8003697C / func_800369C0).
#define Scratch_scale_shift                                                                                                                \
    (*(uint8 *)0x1F800074) // 0 normal, 1 = coordinates doubled, fog distances halved (func_800369C0); also a table index (0-2)

#define Scratch_fog_0 (*(uint16 *)0x1F800006)
#define Scratch_fog_1 (*(uint16 *)0x1F800076)
#define Scratch_fog_2 (*(uint8 *)0x1F800078) // byte +0x23 of the fog block (func_800371A0)

// Scratchpad working matrix (func_80033D80).
#define Scratch_mtx (*(MATRIX *)0x1F8000C0)

// Scratchpad pose unpacking (func_80033A28): 0x20 packed words at 0x1F800180 become 25 SVECTORs
// of 12-bit values at 0x1F800120.
#define Scratch_pose_packed ((uint32 *)0x1F800180)

#define Scratch_pose_vtx ((sint16 *)0x1F800120)

#endif // SCRATCH_H
