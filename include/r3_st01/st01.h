#ifndef ST01_H
#define ST01_H

#include "common.h"
#include "stage_common/stage.h"

extern STAGE_SLOT_FUNC *D_80100C88[];
extern STAGE_SLOT_FUNC *D_80100CC8[];
extern STAGE_SLOT_FUNC D_80100CCC[];
extern STAGE_SLOT_FUNC D_80100CD0[];
extern STAGE_SLOT_FUNC D_80100CD4[];
extern STAGE_SLOT_FUNC D_80100D58[];
extern void *D_80100D5C[];       // model table by room (func_80022FD4)
extern void *D_80100D88[];       // spawn list by room
extern void *D_80100DA4[];       // exit list by room
extern uint8 D_80100DA8[][0x28]; // by room (func_800371A0)
extern uint8 D_80100E20[][8];    // by D_80100EF8[room]
extern sint32 D_80100EF8[];
extern STAGE_ROOM_FUNC D_80100F08[]; // room scripts by room
extern uint8 D_80100F1C[];
extern uint8 D_80100F30[];
extern STAGE_ROOM_FUNC D_80100F7C[];
extern STAGE_FUNC D_80100F8C[]; // routine_1 handlers (func_8010080C)
extern STAGE_FUNC D_80101094[]; // routine_0 handlers (func_801008C0)

// Room model 0's x (STAGE_MODEL_TBL[0]), reached through its own symbol.
extern sint16 D_800BBA9C[];

void func_80100400(STAGE_ROOM_WORK *wp);
void func_8010045C(STAGE_ROOM_WORK *wp);
void func_80100A70(void *wp, sint32 a1, sint32 y, uint32 color);

#endif // ST01_H
