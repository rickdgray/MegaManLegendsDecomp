#ifndef ST16_H
#define ST16_H

#include "common.h"
#include "stage_common/stage.h"

extern void *D_801034C4[];       // model table by room (Room_model_init)
extern void *D_80103570[];       // spawn list by room
extern void *D_80103594[];       // exit list by room
extern uint8 D_801035A0[][0x28]; // by room (func_800371A0)
extern uint8 D_80103618[][8];    // by D_80103698[room]
extern sint32 D_80103698[];
void func_80100270(void);
extern STAGE_SLOT_FUNC *D_801033D0[];
extern STAGE_SLOT_FUNC *D_80103470[];
extern STAGE_SLOT_FUNC D_8010348C[];
extern STAGE_SLOT_FUNC D_80103490[];
extern STAGE_SLOT_FUNC D_801034AC[];
extern STAGE_SLOT_FUNC D_801034C0[];
extern STAGE_ROOM_FUNC *D_801036BC[];
extern STAGE_SCRIPT_ENTRY D_801036FC[];
extern uint8 D_80103738[];
extern STAGE_ROOM_FUNC D_801038C8[];
extern STAGE_SCRIPT_ENTRY D_801038F8[];
extern uint8 D_80103934[];
extern STAGE_ROOM_FUNC D_80103AD4[];
extern STAGE_FUNC D_80103B04[];
extern STAGE_OBJ_FUNC D_80103BAC[];
extern STAGE_FUNC D_80103BB8[];
extern sint16 D_8010E050;
extern sint8 *D_80103B8C[]; // mouth scripts (func_801014A4)
extern sint8 *D_80103B9C[]; // eye scripts (func_801014CC)
extern sint8 *D_80103C3C[];
extern sint8 *D_80103C44[];
extern sint8 *D_80103C4C[];
extern sint8 *D_80103C54[];
extern STAGE_OBJ_FUNC D_80103C5C[];
extern STAGE_FUNC D_80103C64[];
extern STAGE_FX_FUNC D_80103CB0[];
extern STAGE_OBJ_FUNC D_80103BC4[]; // routine_1 handlers (func_80101B88)
extern STAGE_UVW D_80103C70[];
extern STAGE_UVW D_80103C80[];
extern uint32 D_80103C90[]; // colors by frame (func_8010291C)
extern STAGE_FX *D_8010E054;
extern STAGE_FX *D_8010E058;

void func_80100374(uint8 mode);
void func_801005E4(STAGE_ROOM_WORK *wp);
void func_80100668(STAGE_ROOM_WORK *wp);
void func_80100970(uint8 mode);
void func_80100BDC(STAGE_ROOM_WORK *wp);
void func_80100C44(STAGE_ROOM_WORK *wp);
void func_80101264(STAGE_OBJ *wp);
void func_801014A4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801014CC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801014F4(STAGE_OBJ *wp, STAGE_FACE *face);
void func_801016B0(STAGE_OBJ *wp);
void func_80101CE8(STAGE_OBJ *wp);
void func_80101F34(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80101F5C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80101F84(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80101FAC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80101FD4(STAGE_OBJ *wp, STAGE_FACE *face);
void func_80102190(STAGE_OBJ *wp);
void func_801022C0(STAGE_FX *wp);
void func_8010244C(STAGE_FX *wp);
void func_801024B8(STAGE_FX *wp);
void func_80102730(STAGE_FX *wp);
void func_80102788(STAGE_FX *wp);
void func_8010291C(STAGE_FX *wp);
void func_801029F8(STAGE_FX *wp);
STAGE_FX *func_80102CF4(STAGE_OBJ *parent, sint16 angle, sint16 radius, sint16 height, uint8 variant);

#endif // ST16_H
