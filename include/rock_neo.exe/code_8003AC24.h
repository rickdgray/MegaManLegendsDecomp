#ifndef CODE_8003AC24_H
#define CODE_8003AC24_H

#include "common.h"
#include "stage.h"

// Rows of D_800BD3B8: one per stage that has one (D_80089F04).
#define IDX_STATE_ROWS 7
// One 2-bit state per Stage_idx_tbl entry: 16 in each word, 0x800 entries in a row.
#define IDX_STATE_WORDS 0x80

// Stage number (Game_work.stage_no) -> row of D_800BD3B8, or -1 for none.
extern sint8 D_80089F04[0x20];
// HED ids (Stage_hed_tbl) of the replacement shapes func_8003AD14 gives entries in state 1 ([x][0])
// and 2 ([x][1]): [0] for stages 5 and 6's entries of kind 0x8100, [1] for the rest, picked by
// bits 14-15 of the shape's first unk18 word.
extern uint32 D_80089F24[2][2][4];
// The 2-bit states of each stage's Stage_idx_tbl entries (func_8003B2D4, func_8003B540). Saved to
// and restored from Cd_ring_buf + 0x480 (func_8003B278).
extern uint32 D_800BD3B8[IDX_STATE_ROWS][IDX_STATE_WORDS];
// Shape kinds (the high half of IDX_SHAPE.head) that func_8003B5B4 passes to func_8003B8B0 and
// func_8003BA58 (D_80089F64 for stage 5; D_80089F6C to D_80089F74 for stage 6), and the kinds of
// the entries it then counts down (D_80089F68 for stage 5, D_80089F78 for stage 6).
extern uint32 D_80089F64;
extern uint32 D_80089F68;
extern uint32 D_80089F6C;
extern uint32 D_80089F70;
extern uint32 D_80089F74;
extern uint32 D_80089F78;
// Shape kinds (the high half of IDX_SHAPE.head) that func_8003BC44 passes to func_8003BD0C and
// func_8003BDC0: D_80089F7C/F80 for stage 5, D_80089F84 to D_80089F90 for stage 6.
extern uint32 D_80089F7C;
extern uint32 D_80089F80;
extern uint32 D_80089F84;
extern uint32 D_80089F88;
extern uint32 D_80089F8C;
extern uint32 D_80089F90;
// The state func_8003BA58 gives each of its seven entries, by its overall state (0..3).
extern uint8 D_80097D74[4][7];

uint32 Stage_hed_model_get(uint32 id);
IDX_SHAPE *Stage_idx_model_set(sint32 idx, uint32 id);
void func_8003ACF4(sint32 idx, IDX_SHAPE *ptr);
void func_8003AD14(void); // applies the state rows to Stage_idx_tbl
void func_8003B140(void);
void func_8003B278(sint32 mode);
sint32 func_8003B2D4(sint32 stage, sint32 idx);
sint32 func_8003B360(sint32 idx);
sint32 func_8003B420(sint32 idx);
sint32 func_8003B4BC(sint32 stage, sint32 idx);
sint32 func_8003B540(sint32 stage, sint32 idx, uint32 state);
void func_8003B5B4(void);
void func_8003B8B0(uint32 *remain, uint32 amount, uint32 kind, sint32 stage, sint32 flag);
void func_8003BA58(uint32 *remain, uint32 amount, uint32 kind, sint32 unused);
void func_8003BC44(void);
void func_8003BD0C(uint32 *flag, uint32 kind);
void func_8003BDC0(uint8 *count, uint32 kind0, uint32 kind1);

#endif // CODE_8003AC24_H
