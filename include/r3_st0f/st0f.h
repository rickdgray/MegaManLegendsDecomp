#ifndef ST0F_H
#define ST0F_H

#include "common.h"
#include "stage_common/stage.h"

// A 0x3C0-byte work slot as this stage's objects use it (STAGE_OBJ, with more fields named).
typedef struct ST0F_OBJ ST0F_OBJ;
typedef void (*ST0F_OBJ_FUNC)(ST0F_OBJ *wp);

// The block at +0x348 of ST0F_OBJ.
typedef struct
{
    sint16 angle_0;         // 348: the facing to turn back to
    uint8 reserved02[0x76]; // 34A
} ST0F_CTL;

// A scene slot as func_8001EB98 returns it (ROCK_NEO's SCENE_SLOT).
typedef struct
{
    uint8 reserved00[3]; // 00
    uint8 value_3;       // 03
} ST0F_SCENE_SLOT;

struct ST0F_OBJ
{
    sint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 reserved0C[4];                    // 0C
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    sint32 value_78;                        // 78
    uint8 reserved7C[0x34];                 // 7C
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180
    uint8 reserved188[0x1C0];               // 188
    ST0F_CTL ctl;                           // 348
};

extern STAGE_SLOT_FUNC *D_80104840[];
extern STAGE_SLOT_FUNC *D_801049C0[];
extern STAGE_SLOT_FUNC D_801049DC[];
extern STAGE_SLOT_FUNC D_80104A24[];
extern STAGE_SLOT_FUNC D_80104A28[];
extern STAGE_SLOT_FUNC D_80104A2C[];
void func_8010005C(void);

sint32 func_80100F54(void);

extern uint8 D_80105848[];
extern uint8 D_80105850[];
extern uint8 D_80105858[];
extern uint8 D_80105860[];
extern uint8 D_80105868[];
extern uint8 D_80105870[];
extern uint8 D_80105878[];
extern uint8 D_80105880[];
extern uint8 D_80105888[];
extern uint8 D_80105890[];
extern uint8 D_80105898[];
extern uint8 D_801058A0[];
extern uint8 D_801058A8[];
extern uint8 D_801058B0[];
extern uint8 D_801058B8[];
extern uint8 D_801058C0[];
extern uint8 D_801058C8[];
extern uint8 D_801058D0[];
extern uint8 D_801058D8[];
extern uint8 D_801058E0[];
extern uint8 D_801058E8[];
extern uint8 D_801058F0[];
extern uint8 D_801058F8[];
extern uint8 D_801060F8[];
extern uint8 D_80106104[];
extern uint8 D_80106118[];
extern uint8 D_80106138[];

void Scene_obj_list_open(uint8 *);
void func_8010035C(STAGE_ROOM *wp);

void func_80100460(STAGE_ROOM *wp);

void func_80100534(STAGE_ROOM *wp);

void func_80100638(STAGE_ROOM *wp);

void func_8010073C(STAGE_ROOM *wp);

void func_80100840(STAGE_ROOM *wp);

void func_8010093C(STAGE_ROOM *wp);

void func_80100A38(STAGE_ROOM *wp);

void func_80100B34(STAGE_ROOM *wp);

void func_80100C30(STAGE_ROOM *wp);

void func_80100D2C(STAGE_ROOM *wp);

void func_801002FC(STAGE_ROOM_WORK *wp);
void func_801003A8(STAGE_ROOM_WORK *wp);
void func_80100580(STAGE_ROOM_WORK *wp);
void func_80100684(STAGE_ROOM_WORK *wp);
void func_80100788(STAGE_ROOM_WORK *wp);
void func_8010088C(STAGE_ROOM_WORK *wp);
void func_80100988(STAGE_ROOM_WORK *wp);
void func_80100A84(STAGE_ROOM_WORK *wp);
void func_80100B80(STAGE_ROOM_WORK *wp);
void func_80100C7C(STAGE_ROOM_WORK *wp);
void func_80100D78(STAGE_ROOM_WORK *wp);

extern STAGE_ROOM_FUNC *D_80104DE4[];
extern STAGE_ROOM_FUNC D_80104E24[];
ST0F_SCENE_SLOT *func_8001EB98(void *entry);
void func_80100400(STAGE_ROOM_WORK *wp);
void func_801004D4(STAGE_ROOM_WORK *wp);
void func_801005D8(STAGE_ROOM_WORK *wp);
void func_801006DC(STAGE_ROOM_WORK *wp);
void func_801007E0(STAGE_ROOM_WORK *wp);
void func_801008E4(STAGE_ROOM_WORK *wp);
void func_801009E0(STAGE_ROOM_WORK *wp);
void func_80100ADC(STAGE_ROOM_WORK *wp);
void func_80100BD8(STAGE_ROOM_WORK *wp);
void func_80100CD4(STAGE_ROOM_WORK *wp);
void func_801004AC(STAGE_ROOM_WORK *wp);
sint32 func_80100DD0(void);
void func_8010025C(void);

sint32 func_8003B2D4(sint32 row, sint32 bit);
void func_8001DEE4(void);
void func_8001E4C4(void *a, void *b);
extern uint8 D_80105900[][8];
sint16 Obj_ceiling_height_get(void *wp);
void Sce_flag_off(sint32 flag);
extern ST0F_OBJ_FUNC D_801060F4[];
extern ST0F_OBJ_FUNC D_8010612C[];
uint8 func_80104798(void);
uint8 func_801047D8(void);
void func_80100210(void);
sint32 func_80103E08(void);
sint32 func_80104490(ST0F_OBJ *wp);
void func_801043CC(ST0F_OBJ *wp);
void func_80103C28(ST0F_OBJ *wp);
void func_801043CC(ST0F_OBJ *wp);
void func_80103984(ST0F_OBJ *wp);
void func_80103E70(ST0F_OBJ *wp);

extern uint8 D_80106144[];
extern STCOM_FIXED_VECTOR D_801061A0; // position for func_80039FAC
extern STCOM_FIXED_VECTOR D_801061B0; // position for func_80039FAC
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 func_80103CD8(ST0F_OBJ *wp);

sint32 func_80104490(ST0F_OBJ *wp);
sint32 func_801045C0(void);
sint16 Angle_diff_clamp(sint32 goal, sint32 rot, sint32 speed);
sint32 func_80103CD8(ST0F_OBJ *wp);
void func_80103C28(ST0F_OBJ *wp);
sint32 func_80103E08(void);
sint32 func_80104490(ST0F_OBJ *wp);
void func_801043CC(ST0F_OBJ *wp);
void func_8005C224(sint32 arg);
void func_8001E390(sint32 arg);

extern void *D_80104B24[];       // spawn list by room
extern void *D_80104C54[];       // exit list by room
extern uint8 D_80104C64[][0x28]; // by room (func_800371A0)
extern uint8 D_80104D04[][8];    // by D_80104D14[room]
extern sint32 D_80104D14[];      // by room
#endif                           // ST0F_H
