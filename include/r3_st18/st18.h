#ifndef ST18_H
#define ST18_H

#include "common.h"
#include "stage_common/stage.h"

extern STAGE_SLOT_FUNC *D_80101DF0[];
extern STAGE_SLOT_FUNC *D_80101E1C[];
extern STAGE_SLOT_FUNC D_80101E38[];
extern STAGE_SLOT_FUNC D_80101E3C[];
extern STAGE_SLOT_FUNC D_80101E78[];
extern STAGE_SLOT_FUNC D_80101EA8[];
extern void *D_80101F18[];       // model table by room
extern void *D_80101F9C[];       // spawn list by room
extern void *D_80101FC0[];       // exit list by room
extern uint8 D_80101FCC[][0x28]; // by room (func_800371A0)
extern uint8 D_80102044[][8];    // by D_801020C4[room]
extern sint32 D_801020C4[];
extern STAGE_ROOM_FUNC *D_801020E8[];  // room scripts by script set, then room
extern STAGE_EFFECT_FUNC D_80102128[]; // routine_1 handlers (func_801004C8)
extern uint16 D_8010214C[];
extern uint8 *D_80102164[];            // (u, v) frames by type_F
extern uint8 D_80102174[];             // frame counts by type_F
extern STAGE_EFFECT_FUNC D_80102178[]; // routine_0 handlers (func_801006C0, work_0 0)
extern STAGE_EFFECT_FUNC D_80102184[]; // routine_0 handlers (func_801006C0, work_0 1)
extern uint16 D_8010219E[];
extern uint16 D_801021C8[];
extern STAGE_MOUTH *D_80102348[];
extern STAGE_MOUTH *D_80102378[];
extern STAGE_MOUTH_CUE D_801023C8[];
extern STAGE_MOUTH_CUE D_80102418[];
extern STAGE_FUNC D_801024A8[]; // routine_1 handlers (func_801010FC)
extern STAGE_MOUTH *D_80102618[];
extern STAGE_MOUTH *D_8010264C[];
extern STAGE_MOUTH_CUE D_80102688[];
extern STAGE_MOUTH_CUE D_801026DC[];
extern STAGE_FUNC D_801027C8[]; // routine_1 handlers (func_80101918)
extern STAGE_FUNC D_801027E8[]; // routine_1 handlers (func_80101B60)
extern sint32 D_801027F4[][2];
// Lip-sync state: arrays, as GCC keeps their addresses in registers for a read-modify-write.
extern STAGE_MOUTH *D_801078B4[];
// The lip-sync script pointers also read and written as scalars (the same symbols): retail
// reaches them by lui/%lo there, and through their address only for the jump back (+=).
extern STAGE_MOUTH *D_801078B4_S __asm__("D_801078B4");
extern sint16 D_801078B8[];
extern STAGE_MOUTH *D_801078BC[];
extern STAGE_MOUTH *D_801078BC_S __asm__("D_801078BC");
extern sint16 D_801078C0[];
extern STAGE_LIP_CUES D_801078C4;
extern STAGE_MOUTH *D_801078CC[];
extern STAGE_MOUTH *D_801078CC_S __asm__("D_801078CC");
extern sint16 D_801078D0[];
extern STAGE_MOUTH *D_801078D4[];
extern STAGE_MOUTH *D_801078D4_S __asm__("D_801078D4");
extern sint16 D_801078D8[];
extern STAGE_LIP_CUES D_801078DC;

void func_801001D8(void);
void func_801004C8(STAGE_EFFECT *wp);
STAGE_EFFECT *func_8010072C(STCOM_SVECTOR *pos, sint16 value, uint8 variant);
void func_801007C0(STAGE_WORK *wp);
void func_8010081C(STAGE_WORK *wp);
void func_80100878(STAGE_WORK *wp);
void func_801009A0(STAGE_WORK *wp);
void func_80100AE8(STAGE_WORK *wp);
void func_801010FC(STAGE_WORK *wp);
void func_8010131C(STAGE_WORK *wp);
void func_80101378(STAGE_WORK *wp);
void func_801013D4(STAGE_WORK *wp);
void func_801014FC(STAGE_WORK *wp);
void func_80101644(STAGE_WORK *wp);
void func_80101918(STAGE_WORK *wp);
void func_801019CC(STAGE_WORK *wp);
void func_80101B60(STAGE_WORK *wp);

#endif // ST18_H
