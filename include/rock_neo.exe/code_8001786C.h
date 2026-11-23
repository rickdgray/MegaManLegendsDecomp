#ifndef CODE_8001786C_H
#define CODE_8001786C_H

#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"

typedef void (*CODE_8001786C_FUNC)(void);

// A position in CLUT coordinates: column x of VRAM row y (rows 0xF0 up hold Clut_buf).
typedef struct
{
    uint16 x;
    uint16 y;
} CLUT_POS;

// The screen fade (pool, 0x80098A68), set up by Fade_start and run by the thread it opens
// (func_80017E94: D_80082140[routine_0]).
typedef struct
{
    sint8 routine_0; // 0x00 0: black fade (subtractive tile), 1: white (additive), both by
                     // Fade_main; 2: a wipe (func_80018050), which ends black
    sint8 routine_1; // 0x01 Fade_main's state; for a wipe, its row of D_800821E0
    sint8 routine_2; // 0x02 a wipe's column of D_800821E0 (its current step)
    sint8 routine_3; // 0x03 sub-step of a wipe's step
    sint8 timer;     // 0x04 frame counter of the wipe steps
    uint8 pad_5[3];
    sint16 draw;  // 0x08 while nonzero, func_80017B24 draws the fade tile
    sint16 busy;  // 0x0A nonzero while a fade runs: 1 fades in, -1 out (D_80097A44); -1 for a wipe; also
                  // read as D_80098A72 (game.h)
    sint16 speed; // 0x0C level change per frame (D_80097A48), then frames to hold at the end
    sint16 level; // 0x0E the tile's gray level, 0-255
} FADE_WORK;

// D_80082140[Fade_work.routine_0], run by func_80017E94: Fade_main (entries 0 and 1) or
// func_80018050 (entry 2).
extern CODE_8001786C_FUNC D_80082140[3];
// The steps func_80018050 runs: D_800821BC[D_800821E0[routine_1][routine_2]].
extern CODE_8001786C_FUNC D_800821BC[9];
extern uint8 D_800821E0[6][4];
// The 18 points func_80019760 rotates into D_80099190.
extern DVECTOR D_8008214C[18];
// The corners (indices into D_80099190) of Wipe_zoom's ten quads.
extern uint8 D_80082194[10][4];

// The CLUT rows of VRAM: { 0, 0xF0, 256, 16 } and { 0, 0x1F0, 256, 16 }.
extern RECT D_80097A28;
extern RECT D_80097A30;
// Three half rows of the CLUT: { 0, 0xF0 }, { 0x80, 0xF0 }, { 0x80, 0xF9 } (the rows
// func_80017994 saves); func_800179FC darkens the first two.
extern CLUT_POS D_80097A38[3];
extern sint16 D_80097A44[2]; // FADE_WORK.busy by Fade_start's argument bit 3: 1, -1
extern uint16 D_80097A48[4]; // FADE_WORK.speed by Fade_start's argument bits 0-1
// Wipe_zoom's quad colors (code and RGB words), two per routine_3 alternating every 4
// frames, and its tpage bits by routine_3.
extern uint32 D_80097A60[3][2];
extern uint32 D_80097A78[3];

// A CLUT image laid out like Clut_buf (two copies of 0x2000 colors); func_800179FC writes the
// second copy from the first.
extern uint16 D_8008F168[];

// A full-screen TILE (drawn by the wipe Wipe_dim) and a DR_MODE per buffer (drawn after
// every wipe's primitives).
extern DR_MODE D_80098160[2];
extern TILE D_80098178[2];

// Three half rows (128 colors) of Clut_buf saved by func_80017994: rows 0, 0 (second half), 9
// (second half).
extern uint16 D_80098B70[3][128];

// Pool variables (lui-based here, so defined in another file; owners unknown).
// Two full-screen semi-transparent TILEs and their DR_MODEs (tpage from GetTPage), one per
// buffer; set up by func_8001326C (main) and Fade_start, used by func_80017B24.
extern TILE D_80098A28[2];
extern DR_MODE D_80098A10[2];
extern FADE_WORK Fade_work;
extern sint32 D_80098810; // set to 1 by func_800180D4
extern sint32 D_80098824; // set to 1 by func_800180D4
extern sint32 D_80098864; // set to 1 by func_800180D4; main picks D_800806EC's row by it

// Ten textured quads per buffer, five across, two rows of 120 lines (uv set by func_800196A0).
extern POLY_FT4 D_80098E70[2][10];
extern DVECTOR D_80099190[18]; // D_8008214C rotated by func_80019760
// Gouraud quads per buffer for the wipes: 32 fan segments (Wipe_spot, Wipe_iris) or
// two bands (Wipe_bands).
extern POLY_G4 D_800991D8[2][32];
extern DVECTOR D_80099AD8[32]; // (rcos, rsin) of 32 angles round the circle, by the wipes

void Clut_buf_load(void);    // called once per frame by main
void Clut_buf_stp_set(void); // called by scene's func_8001F23C
void func_80017B24(void);    // called once per frame by main
void func_80017994(void);    // saves three half rows of Clut_buf; also called from code_800133D8
void func_800179FC(void);    // called by scene
void Fade_start(sint32 arg);

#endif
