#ifndef ST15_H
#define ST15_H

#include "common.h"
#include "stage_common/stage.h"

extern STAGE_SLOT_FUNC *D_80102480[];
extern STAGE_SLOT_FUNC *D_80102604[];
extern STAGE_SLOT_FUNC D_80102634[];
extern STAGE_SLOT_FUNC D_80102638[];
extern STAGE_SLOT_FUNC D_8010263C[];
extern STAGE_SLOT_FUNC D_80102650[];
extern void *D_80102654[];       // model table by room
extern void *D_801026C0[];       // spawn list by room
extern void *D_801026E0[];       // exit list by room
extern uint8 D_801026E8[][0x28]; // by room (func_800371A0)
extern uint8 D_80102738[][8];    // by D_80102760[room]
extern sint32 D_80102760[];
extern STAGE_ROOM_FUNC *D_80102778[];
extern STAGE_FUNC D_80102CE8[];
void func_80100EA8(STAGE_WORK *wp);
void func_80100FF0(STAGE_WORK *wp);
void func_80101148(STAGE_WORK *wp);
extern STAGE_FUNC D_80102E88[];
void func_801013DC(STAGE_WORK *wp);
void func_80101524(STAGE_WORK *wp);
void func_8010191C(STAGE_WORK *wp);
void func_801019D0(STAGE_WORK *wp);
void func_80101AB8(STAGE_WORK *wp);
void func_80101C40(STAGE_WORK *wp);
void func_80101D4C(STAGE_WORK *wp);
extern uint8 D_801027B8[];
extern STAGE_SCRIPT_ENTRY D_80102A00[];
extern STAGE_ROOM_FUNC D_80102A78[];
extern STAGE_FUNC D_80102EAC[];
extern STAGE_FUNC D_80102EB4[];
extern STAGE_FUNC D_80102EBC[];
extern STAGE_FUNC D_80102EC0[];

// Lip-sync state.
extern STAGE_MOUTH *D_801084F4[];
// The lip-sync script pointers also read and written as scalars (the same symbols): retail
// reaches them by lui/%lo there, and through their address only for the jump back (+=).
extern STAGE_MOUTH *D_801084F4_S __asm__("D_801084F4");
extern sint16 D_801084F8[];
extern STAGE_MOUTH *D_801084FC[];
extern STAGE_MOUTH *D_801084FC_S __asm__("D_801084FC");
extern sint16 D_80108500[];
extern STAGE_MOUTH *D_8010850C[];
extern STAGE_MOUTH *D_8010850C_S __asm__("D_8010850C");
extern sint16 D_80108510[];
extern STAGE_MOUTH *D_80108514[];
extern STAGE_MOUTH *D_80108514_S __asm__("D_80108514");
extern sint16 D_80108518[];

extern STAGE_MOUTH_CUE D_80102C54[];
extern STAGE_MOUTH_CUE D_80102C8C[];
extern STAGE_LIP_CUES D_80108504;
extern STAGE_LIP_CUES D_8010851C;
extern STAGE_MOUTH *D_80102BFC[];
extern STAGE_MOUTH *D_80102C20[];
extern STAGE_MOUTH *D_80102DD0[];
extern STAGE_MOUTH_CUE D_80102E04[];

void func_80100200(void);
void func_801002B8(uint8 mode);
void func_80100A84(STAGE_ROOM_WORK *wp);
void func_80100AF4(STAGE_ROOM_WORK *wp);
void func_80101DF8(STAGE_WORK *wp);
void func_80101F3C(STAGE_WORK *wp);

#endif // ST15_H
