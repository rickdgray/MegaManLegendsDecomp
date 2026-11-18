#ifndef ST07_H
#define ST07_H

#include "common.h"
#include "stage_common/stage.h"

extern void *D_80105658[];       // model table by room (func_80022FD4)
extern void *D_80105728[];       // spawn list by room
extern void *D_80105760[];       // exit list by room
extern uint8 D_80105780[][0x28]; // by room (func_800371A0)
extern uint8 D_801058C0[][8];    // by D_80105B00[room]
extern sint32 D_80105B00[];
void func_8010020C(void);
extern STAGE_SLOT_FUNC *D_801054D4[];
extern STAGE_SLOT_FUNC *D_80105584[];
extern STAGE_SLOT_FUNC D_801055B4[];
extern STAGE_SLOT_FUNC D_801055B8[];
extern STAGE_SLOT_FUNC D_801055F0[];
extern STAGE_SLOT_FUNC D_80105604[];
extern STAGE_ROOM2_FUNC *D_80105B40[];
extern STAGE_OBJ_FUNC D_801066C4[];
extern STAGE_OBJ_FUNC D_801066D8[];
extern STAGE_OBJ_FUNC D_801066E8[];
extern STAGE_MOUTH *D_80108C10[];
// The lip-sync script pointers also read and written as scalars (the same symbols): retail
// reaches them by lui/%lo there, and through their address only for the jump back (+=).
#ifdef PORT
#define D_80108C10_S (D_80108C10[0]) // native: one object (see st00.h)
#else
extern STAGE_MOUTH *D_80108C10_S __asm__("D_80108C10");
#endif
extern sint16 D_80108C14[];
extern STAGE_MOUTH *D_80108C18[];
#ifdef PORT
#define D_80108C18_S (D_80108C18[0]) // native: one object (see st00.h)
#else
extern STAGE_MOUTH *D_80108C18_S __asm__("D_80108C18");
#endif
extern sint16 D_80108C1C[];
extern STAGE_OBJ_FUNC D_80106908[];
extern STAGE_MOUTH *D_80108C28[];
#ifdef PORT
#define D_80108C28_S (D_80108C28[0]) // native: one object (see st00.h)
#else
extern STAGE_MOUTH *D_80108C28_S __asm__("D_80108C28");
#endif
extern sint16 D_80108C2C[];
extern STAGE_MOUTH *D_80108C30[];
#ifdef PORT
#define D_80108C30_S (D_80108C30[0]) // native: one object (see st00.h)
#else
extern STAGE_MOUTH *D_80108C30_S __asm__("D_80108C30");
#endif
extern sint16 D_80108C34[];
extern STAGE_OBJ_FUNC D_80106BFC[];

// A room-script object with a position at +0x38 (child_48 of func_801012A0; func_801043F8).
typedef struct
{
    uint8 flags_0;         // 00
    uint8 reserved01[7];   // 01
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 routine_3;       // 0B
    sint16 timer_C;        // 0C
    sint16 angle_E;        // 0E
    sint16 value_10;       // 10
    uint8 reserved12[6];   // 12
    STAGE_MATRIX_W matrix; // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    sint16 value_44;       // 44
    sint16 value_46;       // 46
} ST07_MOVER;

typedef void (*ST07_MOVER_FUNC)(ST07_MOVER *wp);
extern ST07_MOVER_FUNC D_80106C08[];

// A talking face (at a work slot's +0x4E0).
typedef struct
{
    sint8 *mouth_0; // 0: shape, then a byte 0x7E (hold) or 0x7F (loop)
    sint8 *eyes_4;  // 4
    sint8 shape_8;  // 8
    sint8 prev_9;   // 9
    sint8 index_A;  // A
    sint8 shape_B;  // B
    sint8 prev_C;   // C
    sint8 index_D;  // D
} ST07_FACE;

extern STAGE_ROOM2_FUNC D_80105B80[]; // routine_4 handlers (func_80100330)
extern STAGE_SCRIPT_ENTRY D_80105BA0[];
extern STAGE_SCRIPT_ENTRY D_80105C18[];
extern STAGE_SCRIPT_ENTRY D_80105C7C[];
extern STAGE_SCRIPT_ENTRY D_80105BDC[];
extern STAGE_SCRIPT_ENTRY D_80105CB8[];
extern STAGE_SCRIPT_ENTRY D_80106164[];
extern STAGE_SCRIPT_ENTRY D_80106394[];
extern uint8 D_8010622C[];
extern uint8 D_80106448[];
extern STAGE_ROOM2_FUNC D_80106354[];
extern STAGE_ROOM2_FUNC D_801065E4[];
extern STAGE_FX D_800A3B40[]; // ROCK_NEO's effect slots
extern STAGE_OBJ_FUNC D_8010663C[];
extern STAGE_OBJ_FUNC D_801066A0[];
extern STAGE_OBJ_FUNC D_801066D0[];
extern STAGE_OBJ_FUNC D_801066D4[];
extern STAGE_OBJ_FUNC D_801066E4[];
extern STAGE_OBJ_FUNC D_801068E8[];
extern STAGE_OBJ_FUNC D_80106BCC[];
extern STAGE_FX_FUNC D_80106C14[];
extern STAGE_FX_FUNC D_80106C1C[];
extern STAGE_FX_FUNC D_80106C24[];
extern STAGE_FX_FUNC D_80106C30[];
extern sint8 *D_80106944[]; // mouth scripts (func_80103A24)
extern sint8 *D_80106950[]; // eye scripts
void func_80100CD4(uint8 mode);
void func_80100D38(uint8 mode);
void func_80101678(uint8 mode);
void func_80103A24(STAGE_OBJ *wp, ST07_FACE *face, sint32 index);
void func_80103A6C(STAGE_OBJ *wp, ST07_FACE *face);
STAGE_FX *func_80104E7C(STCOM_SVECTOR *pos);
void func_8003697C(void);

extern STAGE_LIP_CUES D_80108C20;
extern STAGE_LIP_CUES D_80108C38;
extern STAGE_MOUTH *D_80106720[];
extern STAGE_MOUTH *D_801067F4[];
extern STAGE_MOUTH *D_80106A38[];
extern STAGE_MOUTH *D_80106AC8[];
extern STAGE_MOUTH_CUE D_8010682C[];
extern STAGE_MOUTH_CUE D_80106844[];
extern STAGE_MOUTH_CUE D_8010687C[];
extern STAGE_MOUTH_CUE D_801068AC[];
extern STAGE_MOUTH_CUE D_80106B0C[];
extern STAGE_MOUTH_CUE D_80106B20[];
extern STAGE_MOUTH_CUE D_80106B7C[];
void func_80103138(STAGE_OBJ *wp);
void func_80103194(STAGE_OBJ *wp);
void func_80103BB4(STAGE_OBJ *wp);
void func_80103C10(STAGE_OBJ *wp);

// Routines of this module (parameter types from their bodies and callers).
void func_80101BB8(STAGE_ROOM *wp);
void func_80101BE0(STAGE_ROOM *wp);
void func_80101C08(STAGE_ROOM *wp);
void func_80100834(STAGE_ROOM *wp);
void func_80100330(STAGE_ROOM *wp);
void func_80102AEC(STAGE_OBJ *wp);
void func_80101A54(STAGE_ROOM *wp);
void func_8010117C(STAGE_ROOM *wp);
void func_80101258(STAGE_ROOM *wp);
void func_80102854(STAGE_OBJ *wp);
void func_80100270(STAGE_ROOM *wp);
void func_801021DC(STAGE_OBJ *wp);
void func_801027F8(STAGE_OBJ *wp);
void func_80102CCC(STAGE_OBJ *wp);
void func_80103080(STAGE_OBJ *wp);
void func_801002CC(STAGE_ROOM *wp);
void func_80101A98(STAGE_ROOM *wp);
void func_801026F8(STAGE_OBJ *wp);
void func_80102C18(STAGE_OBJ *wp);
void func_80102FCC(STAGE_OBJ *wp);
void func_80102A24(STAGE_OBJ *wp);
void func_80100944(STAGE_ROOM *wp);
void func_8010377C(STAGE_OBJ *wp);
void func_80104320(STAGE_OBJ *wp);
void func_80100C4C(STAGE_ROOM *wp);
void func_80102238(STAGE_OBJ *wp);
void func_8010239C(STAGE_OBJ *wp);
void func_80102678(STAGE_OBJ *wp);
void func_80100B14(STAGE_ROOM *wp);
void func_8010136C(STAGE_ROOM *wp);
void func_80101D5C(STAGE_ROOM *wp);
void func_80102500(STAGE_OBJ *wp);
void func_801011C4(STAGE_ROOM *wp);
void func_8010212C(STAGE_OBJ *wp);
void func_80100B98(STAGE_ROOM *wp);
void func_80103EDC(STAGE_OBJ *wp);
void func_80100ED0(STAGE_ROOM *wp);
void func_80101810(STAGE_ROOM *wp);
void func_80101AFC(STAGE_ROOM *wp);
void func_80103460(STAGE_OBJ *wp);
void func_80104D34(STAGE_OBJ *wp);
void func_801049F4(STAGE_FX *wp);
void func_801012A0(STAGE_ROOM *wp);
void func_8010205C(STAGE_OBJ *wp);
void func_8010470C(STAGE_OBJ *wp);
void func_8010086C(STAGE_ROOM *wp);
void func_801022B8(STAGE_OBJ *wp);
void func_8010241C(STAGE_OBJ *wp);
void func_80102590(STAGE_OBJ *wp);
void func_80102B28(STAGE_OBJ *wp);
void func_80104904(STAGE_OBJ *wp);
void func_801006D8(STAGE_ROOM *wp);
void func_80102D84(STAGE_OBJ *wp);
void func_80102EA8(STAGE_OBJ *wp);
void func_801047E0(STAGE_FX *wp);
void func_801031F0(STAGE_OBJ *wp);
void func_80103C6C(STAGE_OBJ *wp);
void func_80101C30(STAGE_ROOM *wp);
void func_80100D9C(STAGE_ROOM *wp);
void func_801016DC(STAGE_ROOM *wp);
void func_80100598(STAGE_ROOM *wp);
void func_80103318(STAGE_OBJ *wp);
void func_80103D94(STAGE_OBJ *wp);
void func_801009B8(STAGE_ROOM *wp);
void func_8010453C(ST07_MOVER *wp);
void func_801018CC(STAGE_ROOM *wp);
void func_80104B34(STAGE_FX *wp);
void func_8010384C(STAGE_OBJ *wp);
void func_80100F8C(STAGE_ROOM *wp);
void func_8010036C(STAGE_ROOM *wp);
void func_80101E20(STAGE_ROOM *wp);
void func_80101430(STAGE_ROOM *wp);

extern sint32 D_80108C0C;
extern uint8 D_800BBB38;
extern uint8 D_800BBC18;
extern sint16 D_800BBAB0;
extern sint16 D_800BBB20;
extern sint8 D_800BBB70;
extern sint16 D_800BBB90;
extern sint8 D_800BBBA8;
extern sint16 D_800BBBC8;
extern sint8 D_800BBBE0;
extern sint16 D_800BBC00;

// A room model's starting flags and position (func_8010036C copies eight into D_800BBA90).
typedef struct
{
    uint8 flags_0;       // 0
    uint8 reserved01[3]; // 1
    sint16 value_4;      // 4: to the model's value_20
    sint16 value_6;      // 6: to the model's value_22
} ST07_MODEL_INIT;

extern ST07_MODEL_INIT D_80106124[];
extern STAGE_SCRIPT_ENTRY D_80105B8C;
extern uint8 D_80105DD0[];
extern uint8 D_80105E2C[];
extern STAGE_ROOM2_FUNC D_80105E1C[];
extern STAGE_ROOM2_FUNC D_801060D4[];
void func_8001F1DC(void);
sint32 func_8003B2D4(sint32 row, sint32 bit);
#endif // ST07_H
