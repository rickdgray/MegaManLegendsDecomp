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
// The 2-bit states of each stage's Stage_idx_tbl entries (func_8003B2D4, func_8003B540). Saved to
// and restored from Cd_ring_buf + 0x480 (func_8003B278).
extern uint32 D_800BD3B8[IDX_STATE_ROWS][IDX_STATE_WORDS];

uint32 Stage_hed_model_get(uint32 id);
IDX_SHAPE *Stage_idx_model_set(sint32 idx, uint32 id);
void func_8003ACF4(sint32 idx, IDX_SHAPE *ptr);
void func_8003B278(sint32 mode);
sint32 func_8003B2D4(sint32 stage, sint32 idx);
sint32 func_8003B360(sint32 idx);
sint32 func_8003B420(sint32 idx);
sint32 func_8003B4BC(sint32 stage, sint32 idx);
sint32 func_8003B540(sint32 stage, sint32 idx, uint32 state);
void func_8003BD0C(uint32 *flag, uint32 kind);
void func_8003BDC0(uint8 *count, uint32 kind0, uint32 kind1);

#endif // CODE_8003AC24_H
