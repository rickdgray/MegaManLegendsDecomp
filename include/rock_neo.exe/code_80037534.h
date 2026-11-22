#ifndef CODE_80037534_H
#define CODE_80037534_H

// code_80037534.c (not identified yet; rename with the file).

#include "common.h"
#include "player.h"
#include "stage.h"
#include "code_8002E7A8.h"

void func_80037534(PL_WORK *pl); // resets the 16 TBL_IDX records
void func_80037594(void);        // refreshes Player_work[0]'s active record's val

// D_80089EAC[n][pl->rec[n].idx[0]].val[0]. Returns sint32: func_80043E78 uses the result without
// re-extending it.
sint32 func_800375D4(PL_WORK *pl, sint32 n);
// Weapon n's bullet maximum, D_80089EAC[n][pl->rec[n].idx[1]].val[1] (0x7FFF: unlimited);
// Capcom's name (sub_scrn.c). Returns sint32 for the same reason (Sub_screen_status_param_set).
sint32 Player_weapon_bullet_calc(PL_WORK *pl, sint32 n);
// D_80089EAC[n][pl->rec[n].idx[2]].val[2]. Returns sint32 for the same reason (func_80043A8C).
sint32 func_80037634(PL_WORK *pl, sint32 n);
// D_80089EAC[n][pl->rec[n].idx[3]].val[3]. Returns sint32 for the same reason (func_80042770).
sint32 func_80037664(PL_WORK *pl, sint32 n);
// Tests the object against the stage's IDX entries: 0x7FFF when skipped (unkC4's top byte set),
// else the entry hit (0 for none).
sint32 func_80037694(MODEL_WORK *obj, uint32 arg1);

#endif // CODE_80037534_H
