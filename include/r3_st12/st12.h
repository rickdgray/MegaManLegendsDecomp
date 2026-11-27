#ifndef ST12_H
#define ST12_H

#include "common.h"
#include "stage_common/stage.h"

// A matrix whose identity setup writes it as eight words.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} ST12_MATRIX;

#define ST12_IDENTITY(mw)                                                                                                                  \
    ((mw)->words[0] = 0x1000, (mw)->words[1] = 0, (mw)->words[2] = 0x1000, (mw)->words[3] = 0, (mw)->words[4] = 0x1000,                    \
     (mw)->words[5] = 0, (mw)->words[6] = 0, (mw)->words[7] = 0)

// A 0x50-byte slot (func_80031734) as this stage's objects use it (STCOM21_WORK's layout).
typedef struct ST12_OBJ50 ST12_OBJ50;
typedef void (*ST12_OBJ50_FUNC)(ST12_OBJ50 *wp);

struct ST12_OBJ50
{
    uint8 be_flag;         // 00
    uint8 work_id;         // 01
    uint8 id;              // 02
    uint8 type;            // 03
    uint8 reserved04[4];   // 04
    uint8 routine_0;       // 08
    uint8 routine_1;       // 09
    uint8 routine_2;       // 0A
    uint8 reserved0B;      // 0B
    sint16 value_C;        // 0C
    uint8 reserved0E[2];   // 0E
    void *model_10;        // 10
    uint8 reserved14[4];   // 14
    ST12_MATRIX matrix;    // 18
    STCOM_SVECTOR pos_38;  // 38
    uint32 color_40;       // 40
    uint8 reserved44[0xC]; // 44
};

extern STAGE_SLOT_FUNC *D_80107E38[];
extern STAGE_SLOT_FUNC *D_80107FC4[];
extern STAGE_SLOT_FUNC D_80107FE0[];
extern STAGE_SLOT_FUNC D_80108034[];
extern STAGE_SLOT_FUNC D_8010804C[];
extern STAGE_SLOT_FUNC D_80108050[];
void func_801001D4(void);
void func_80100D48(STAGE_ROOM_WORK *wp);

void func_80100828(uint8 arg0);

void func_80100C7C(STAGE_ROOM *wp);

void func_80100BF8(STAGE_ROOM *wp);

void func_80100A84(STAGE_ROOM *wp);

void func_80100910(STAGE_ROOM *wp);

extern uint8 D_80108798[];
extern uint8 D_801087A0[];
extern uint8 D_801087A8[];
extern uint8 D_801087B0[];
extern uint8 D_801087B8[];
extern uint8 D_801087F0[];

void Scene_obj_list_open(uint8 *);
void func_801004BC(STAGE_ROOM *wp);

void func_80100468(STAGE_ROOM *wp);

extern STAGE_ROOM_FUNC D_80108410[];  // room scripts by room (scene flag 0x1FF clear)
extern STAGE_ROOM_FUNC *D_801083D0[]; // room scripts by script set, then room
void func_8001EB98(void *entry);
extern STCOM_SVECTOR D_80108AC0[];
extern uint32 D_80108AE0[];
sint32 Stage_map_cell_get(sint32 a0, STCOM_SVECTOR *pos);
uint32 Stage_idx_model_set(sint32 idx, uint32 key);
extern uint8 D_801088F4[];
extern STAGE_ROOM2_FUNC D_80108AF0[];
extern STAGE_SCRIPT_ENTRY D_80108804[];
void func_801003B8(void);
void func_801003C8(void);
sint32 func_801007B4(void);
void func_80100880(STAGE_ROOM *wp);
void func_80100B60(STAGE_ROOM *wp);
void func_80100CC4(STAGE_ROOM *wp);

extern STCOM_SVECTOR D_801087C0[];
extern uint32 D_801087E0[];
sint32 Map_cell_get(STCOM_SVECTOR *pos);
void func_8001E20C(sint32 arg);
void func_801005BC(STAGE_ROOM_WORK *wp);

void func_80100664(STAGE_ROOM_WORK *wp);

void func_8010070C(STAGE_ROOM_WORK *wp);

void func_80100510(STAGE_ROOM_WORK *wp);
extern sint32 D_80108BA0[];          // y rotation by type (func_801019EC)
extern ST12_OBJ50_FUNC D_80108B94[]; // routine_1 handlers (func_801019EC)
STCOM_MATRIX *MulMatrix(STCOM_MATRIX *m0, STCOM_MATRIX *m1);
extern void *D_801080D4[];       // model table by room
extern void *D_801081D4[];       // exit list by room
extern void *D_80108160[];       // spawn list by room
extern uint8 D_801081E8[][0x28]; // by room (func_800371A0)
extern uint8 D_801082B0[][8];    // by D_80108330[room]
extern sint32 D_80108330[];
// The circle a ST12_ORBITER runs round (+0xCC).
typedef struct
{
    sint16 x_0;         // CC: center
    sint16 y_2;         // CE
    sint16 z_4;         // D0
    sint16 speed_6;     // D2: added to the angle every frame
    sint16 angle_8;     // D4
    uint8 reservedA[2]; // D6
    sint32 radius_C;    // D8
} ST12_ORBIT;

// A 0x10C-byte slot (Open_SHL_WORK) whose model runs round a circle (func_801050E8).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 reserved02[6];                    // 02
    uint8 routine_0;                        // 08
    uint8 reserved09[3];                    // 09
    sint8 value_C;                          // 0C: nonzero: func_8002F9EC sets it up
    sint8 radius_D;                         // 0D: radius / 10
    sint8 speed_E;                          // 0E
    sint8 reverse_F;                        // 0F: runs the other way round
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x28];                 // 64
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR position_AC;              // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    ST12_ORBIT orbit;                       // CC
    uint8 reservedDC[0x30];                 // DC
} ST12_ORBITER;

void func_80107B44(ST12_ORBITER *wp);

#endif // ST12_H
