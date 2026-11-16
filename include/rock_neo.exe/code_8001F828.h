#ifndef CODE_8001F828_H
#define CODE_8001F828_H

#include "common.h"

// Draws one map block's model (data pointer, depth). Picked from Map_block_draw_tbl[kind][bit 31 of the
// model's LOD word].
typedef void (*MAP_DRAW_FUNC)(uint32 *model, sint32 z);

// [kind][bit 31 of the LOD word]: every entry is one of this file's draw functions.
extern MAP_DRAW_FUNC Map_block_draw_tbl[4][4];

#endif
