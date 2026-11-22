#ifndef CODE_8001786C_H
#define CODE_8001786C_H

#include "common.h"
#include "psyq/libgpu.h"

typedef void (*CODE_8001786C_FUNC)(void);

// D_80082140[D_80098A68], run by func_80017E94: func_80017ED0 (entries 0 and 1) or
// func_80018050 (entry 2).
extern CODE_8001786C_FUNC D_80082140[3];
// The steps func_80018050 runs: D_800821BC[D_800821E0[D_80098A69][D_80098A6A]].
extern CODE_8001786C_FUNC D_800821BC[9];
extern uint8 D_800821E0[6][4];

// The CLUT rows of VRAM: { 0, 0xF0, 256, 16 } and { 0, 0x1F0, 256, 16 }.
extern RECT D_80097A28;
extern RECT D_80097A30;

// Three half rows (128 colors) of Clut_buf saved by func_80017994: rows 0, 0 (second half), 9
// (second half).
extern uint16 D_80098B70[3][128];

// Pool variables (lui-based here, so defined in another file; owners unknown).
// Two full-screen semi-transparent TILEs and their DR_MODEs (tpage from GetTPage), one per
// buffer; set up by func_8001326C (main) and func_80017C30, used by func_80017B24.
extern TILE D_80098A28[2];
extern DR_MODE D_80098A10[2];
extern sint8 D_80098A68;  // index into D_80082140
extern sint8 D_80098A69;  // row of D_800821E0
extern sint8 D_80098A6A;  // column of D_800821E0; stepped by func_800180D4/func_800181D4 when their sub-step ends
extern sint8 D_80098A6B;  // sub-step of func_800180D4/func_800181D4
extern sint16 D_80098A70; // while nonzero, func_80017B24 draws the D_80098A28 tile
extern uint16 D_80098A76; // the tile's gray level
extern sint32 D_80098810; // set to 1 by func_800180D4
extern sint32 D_80098824; // set to 1 by func_800180D4
extern sint32 D_80098864; // set to 1 by func_800180D4; main picks D_800806EC's row by it

// Ten textured quads per buffer, five across, two rows of 120 lines (uv set by func_800196A0).
extern POLY_FT4 D_80098E70[2][10];

void Clut_buf_load(void);    // called once per frame by main
void Clut_buf_stp_set(void); // called by scene's func_8001F23C
void func_80017B24(void);    // called once per frame by main
void func_80017C30(sint32 arg0);

#endif
