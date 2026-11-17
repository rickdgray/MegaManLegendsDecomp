#ifndef CODE_80037534_H
#define CODE_80037534_H

// code_80037534.c (not identified yet; rename with the file).

#include "common.h"
#include "player.h"
#include "stage.h"

// D_80089EAC[n][pl->rec[n].idx[0]].val[0]. Returns sint32: func_80043E78 uses the result without
// re-extending it.
sint32 func_800375D4(PL_WORK *pl, sint32 n);
// D_80089EAC[n][pl->rec[n].idx[2]].val[2]. Returns sint32 for the same reason (func_80043A8C).
sint32 func_80037634(PL_WORK *pl, sint32 n);
// Tests the object against the stage's IDX entries: 0x7FFF when skipped (unkC4's top byte set),
// else the entry hit (0 for none).
sint32 func_80037694(STAGE_OBJ *obj, uint32 arg1);

#endif // CODE_80037534_H
