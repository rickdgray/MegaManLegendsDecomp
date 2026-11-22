#ifndef VRAM_H
#define VRAM_H

#include "common.h"

// A RAM copy of the CLUT rows of VRAM: rows 0xF0-0xFF and 0x1F0-0x1FF, 256 colors each.
// Writers set the row's bit in Clut_buf_dirty; func_80017734 copies the dirty rows to
// the second copy, 0x4000 bytes on.
#define CLUT_BUF_ROWS 32
#define CLUT_BUF_COLS 256

// Row of the CLUT buffer for VRAM row y (0xF0-0xFF -> 0-15, 0x1F0-0x1FF -> 16-31), computed
// into row. Two steps: as one expression, GCC folds 0xF0 into the last subtraction. The
// original seems to use a fresh variable for each use (a block-local temporary in its macro?):
// sharing one variable across uses changes register allocation.
#define CLUT_BUF_ROW(row, y) ((row) = (y) + (((y)&0x100) >> 4) - 0xF0, (row) -= (y)&0x100)

extern uint32 Clut_buf_dirty;

// Index of the second copy (0x800B1168, 0x4000 bytes on). clut_buf_dirty_copy copies the dirty
// rows there through the same base as the first; Clut_buf_stp_set walks it as Clut_buf[0x2000..
// 0x3FFF] and Clut_buf_load uploads it to VRAM. So it is one array holding both copies.
#define CLUT_BUF_COPY (CLUT_BUF_ROWS * CLUT_BUF_COLS)

extern uint16 Clut_buf[2 * CLUT_BUF_ROWS * CLUT_BUF_COLS];

#endif // VRAM_H
