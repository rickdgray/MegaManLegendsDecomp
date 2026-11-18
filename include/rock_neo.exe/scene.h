#ifndef ROCK_NEO_SCENE_H
#define ROCK_NEO_SCENE_H

#include "common.h"

// Two bytes written one at a time and read back as one halfword
typedef union
{
    sint16 half;
    uint8 byte[2];
} SCENE_HALF_BYTES;

// Script command record (0x14 bytes).
typedef struct
{
    uint8 slot_0;
    uint8 kind_1;
    uint8 value_2;
    uint8 type_3;
    uint8 value_4;
    uint8 reserved05[3];
    uint32 word_8;
    uint32 word_C;
    uint8 reserved10[4];
} SCENE_CMD;

// Slot record returned by func_8001E968.
typedef struct
{
    uint8 flags_0;
    uint8 id_1;
    uint8 kind_2;
    uint8 value_3;
    uint8 value_4;
    uint8 reserved05;
    uint8 flags_6;
    uint8 reserved07;
    uint8 routine_8;
    uint8 reserved09[3];
    uint32 word_C;
    uint8 reserved10[4];
    uint32 word_14;
    uint16 half_18;
    uint8 reserved1A[2];
    sint32 pos_1C;
    sint32 pos_20;
    sint32 pos_24;
    uint8 reserved28[0x10];
    uint32 word_38;
    uint32 word_3C;
    uint8 reserved40[0x14];
    uint16 half_54;
    uint16 half_56;
    uint16 half_58;
} SCENE_SLOT;

// Position record passed to func_8001E968
typedef struct
{
    sint16 x_0;
    sint16 y_2;
    sint16 z_4;
    sint16 w_6;
} SCENE_POS;

// Script command list: count, then the records.
typedef struct
{
    uint32 count;
    SCENE_CMD *cmds_4;
} SCENE_CMD_LIST;

// Local views: only the fields the scene helpers touch.
typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    SCENE_CMD *cmds_4;
    uint8 flag_8;
    uint8 flag_9;
    uint8 reserved0a[2];
    uint32 work_C;
    uint32 work_10;
    uint32 work_14;
    uint32 work_18;
    uint32 work_1C;
    uint8 reserved20[4];
    SCENE_SLOT *slot_24[32];
    uint8 *script_A4;
} SCENE_WORK;

typedef struct
{
    uint8 reserved00[0x50];
    sint8 routine_50;
    sint8 routine_51;
    uint8 reserved52;
    uint8 flags_53;
    uint8 reserved54[6];
    sint8 option_5A;
    uint8 reserved5b[5];
    sint16 value_60;
    uint16 value_62;
    uint8 flag_64;
    uint8 flag_65;
    uint8 reserved66[2];
    sint16 value_68;
    sint16 value_6A;
    uint8 reserved6c[4];
    sint16 value_70;
    sint16 value_72;
    sint16 value_74;
    uint8 reserved76[0xC];
    uint8 flags_82;
} SCENE_GAME_VIEW;

typedef struct
{
    sint32 count;
    uint16 *src;
    uint16 *dst;
} SCENE_COPY;

typedef struct
{
    uint8 reserved00[0x6E];
    sint16 value_6E;
    uint8 reserved70[0x16A - 0x70];
    sint8 value_16A;
    uint8 value_16B;
    uint8 reserved16c[6];
    sint8 value_172;
    uint8 reserved173[0x450 - 0x173];
    uint8 slots_450[3];
    uint8 reserved453;
    uint8 slots_454[0x20];
} SCENE_PLAYER_VIEW;

typedef void (*SCENE_FUNC)(void);
typedef void (*SCENE_WORK_FUNC)(SCENE_WORK *work);

extern SCENE_WORK Scene_work;
extern SCENE_GAME_VIEW Game_work;
extern SCENE_PLAYER_VIEW Player_work;
extern uint8 Sce_flag[];
extern SCENE_FUNC D_8008980C[];
extern uint8 D_80098788;
extern uint8 D_80098AB8;
extern uint16 D_800C0C2A;
extern uint32 D_800988E8;
extern uint32 D_800ACDBC[];
extern uint32 D_800BE438[];
extern uint32 D_800989F8;
extern uint32 D_800989FC;
extern uint32 D_80098A00;
extern sint32 D_800BC740;
extern sint32 D_800BC744;
extern sint32 D_800BC748;
extern sint32 D_800BC770;
extern sint32 D_800BC774;
extern sint32 D_800BC778;
extern uint32 D_800BC7F0;

extern uint16 D_800891B4[];
void Sce_flag_on(uint32 flag);
void Sce_flag_off(uint32 flag);
#ifdef __wasm32__
void func_800179FC(void);
#else
void func_800179FC(sint32 arg, sint16 *value);
#endif
void func_8002FBF4(void);
void Cd_read_comb(sint32 arg);
extern SCENE_SLOT *D_800ACD40[];
extern SCENE_FUNC D_80088FA8[];
extern SCENE_WORK_FUNC D_80089024[];
extern sint8 D_800C356C;
extern uint8 D_800C356E;
extern uint8 D_800C356F;
extern sint16 *D_800893BC[];
extern SCENE_COPY D_80089248[];
extern uint8 D_800A395C;
extern sint32 D_800A3964;
extern sint32 D_800A3968;
extern sint32 D_800A396C;
extern sint32 D_800A39A0;
extern sint32 D_800A39A4;
extern sint32 D_800A39A8;
extern sint32 D_800BC7D0;
extern sint32 D_800BC7D4;
extern sint32 D_800BC7D8;
extern sint32 D_800BC750;
extern sint32 D_800BC754;
extern sint32 D_800BC758;
extern sint32 D_800BC780;
extern sint32 D_800BC784;
extern sint32 D_800BC788;
extern sint32 D_800BC7B0;
extern sint32 D_800BC7B4;
extern sint32 D_800BC7B8;
extern uint8 D_800BC738;
void func_800398E0(sint32 arg);
void func_8001D7AC(sint32 index);
extern sint32 D_800891F0[];
sint32 catan(sint32 x);
extern sint16 D_80089200[];
extern sint16 D_80089204[];
extern sint16 D_80089208[];
SCENE_SLOT *func_8001E968(sint32 index, sint32 kind, sint32 type, SCENE_POS *pos);
SCENE_SLOT *func_8001EAE8(SCENE_CMD *cmd);
uint32 Sce_flag_test(uint32 flag);
void func_8001F798(sint32 arg);

// 16.16 fixed-point word, also read as its integer half.
typedef union
{
    sint32 w;
    struct
    {
        uint16 frac;
        sint16 i;
    } h;
} SCENE_FIX;

// Local view of the camera block at 0x800BC730
typedef struct
{
    uint8 reserved00[3];
    uint8 flag_3;
    uint8 reserved04[4];
    uint8 mode_8;
    uint8 index_9;
    uint8 reserved0a[6];
    sint32 pos_10;
    sint32 pos_14;
    sint32 pos_18;
    uint8 reserved1c[4];
    sint32 vel_20;
    sint32 vel_24;
    sint32 vel_28;
    uint8 reserved2c[0x14];
    SCENE_FIX rot_40;
    SCENE_FIX rot_44;
    SCENE_FIX rot_48;
    uint8 reserved4c[4];
    sint32 rot_vel_50;
    sint32 rot_vel_54;
    sint32 rot_vel_58;
    uint8 reserved5c[0x14];
    sint32 pos_70;
    sint32 pos_74;
    sint32 pos_78;
    uint8 reserved7c[4];
    sint32 vel_80;
    sint32 vel_84;
    sint32 vel_88;
    uint8 reserved8c[0x14];
    sint32 off_A0;
    sint32 off_A4;
    sint32 off_A8;
    uint8 reservedac[4];
    sint32 value_B0;
    sint32 value_B4;
    sint32 value_B8;
    uint8 reservedbc[4];
    uint32 *cmd_C0;
} SCENE_CAM;

extern SCENE_CAM D_800BC730;
SCENE_SLOT *func_80031418(void);
SCENE_SLOT *func_80031498(void);
SCENE_SLOT *func_80031518(void);
SCENE_SLOT *func_80031734(void);
extern uint8 D_800BC733;
extern uint8 D_800BC739;
extern sint32 D_800BC7E0;
extern sint32 D_800BC7E4;
extern sint32 D_800BC7E8;
void func_80038324(sint32 *pos, sint16 a, sint16 b, sint16 c);
#ifdef __wasm32__
void func_800384A4(sint32 *pos, sint32 *target);
#else
void func_800384A4(sint32 *pos, sint32 *pos2, sint32 w, SCENE_CAM *cam);
#endif

typedef void (*SCENE_SLOT_FUNC)(SCENE_SLOT *slot);
// Dispatch tables kept in scratchpad RAM: pointer to an array of pointers to function arrays
#define SCENE_TBL_58 (*(SCENE_SLOT_FUNC ***)0x1F800058)
#define SCENE_TBL_5C (*(SCENE_SLOT_FUNC ***)0x1F80005C)
#define SCENE_TBL_60 (*(SCENE_SLOT_FUNC **)0x1F800060)
#define SCENE_TBL_6C (*(SCENE_SLOT_FUNC **)0x1F80006C)
uint32 func_8002FE74(uint8 id);
void func_80031824(SCENE_SLOT *slot);

extern uint16 D_800896D4[];
extern SCENE_FUNC D_80089714[];
extern SCENE_FUNC D_80089790[];
void func_8001F740(void);
void func_80019F94(uint16 arg);
void func_800177CC(void *a, void *b);
void func_8001D928(sint32 arg);
void func_8003A3B4(void);
void func_8003AD14(void);
void func_80017944(void);
extern uint8 *D_80098B60;
extern uint8 D_800B6130[];
void func_80067E18(void);
void func_80067E4C(void);
// Hand-written block copy entry inside func_80017618 (not yet in the registry).
void func_800176DC(void *src, void *dst, sint32 count);
void func_8003697C(void);
void func_800369C0(void);
void func_80036A1C(void);
#define GAME_WORK_CLEAR_174 ((uint32 *)((uint8 *)&Game_work + 0x174))
// Scene_work through its fixed address: GCC gives each access its own lui
// (no shared base register), as the script-step helpers need.
#define SCENE_WORK_FIXED (*(SCENE_WORK *)0x800C4C48)

// func_800384A4 as func_8001E550 calls it: retail passes only the two vectors.
typedef void (*SCENE_CAM_FUNC)(sint32 *pos, sint32 *target);

// Game_work through its fixed address (same view type). The stage-load helpers read
// routine_50/51 and value_6A this way, so GCC keeps each access on its own lui and does
// not fold them into the &Game_work register the rest of the function uses.
#define SCENE_GAME_FIXED (*(SCENE_GAME_VIEW *)0x800C1B10)

void func_8001F5E4(void);

#endif
