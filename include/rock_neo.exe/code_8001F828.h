#ifndef CODE_8001F828_H
#define CODE_8001F828_H

#include "common.h"

// Draws one map block's model (data pointer, depth): D_80089890[kind][bit 31 of the block's word].
typedef void (*MAP_DRAW_FUNC)(uint32 *model, sint32 z);

extern MAP_DRAW_FUNC D_80089890[][4];

#endif
