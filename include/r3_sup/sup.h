#ifndef SUP_H
#define SUP_H

#include "common.h"
#include "psyq/libgte.h"
#include "psyq/libgpu.h"

// The SUPPORT module (r3_sup.bin in SUPPORT.BIN and SUPPORT2.BIN), loaded at 0x801D8000.

// Work areas loaded with the module, outside the code chunk, by their fixed addresses.
typedef struct
{
    uint32 value_0;  // 00
    uint32 value_4;  // 04
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 routine_2; // 0A
    uint8 routine_3; // 0B
    uint8 reserved0c[8];
    SVECTOR pos;     // 14
    VECTOR fpos;     // 1C
    SVECTOR old_pos; // 2C
    VECTOR old_fpos; // 34
    uint8 reserved44[0x10];
    SVECTOR rot; // 54
    uint8 reserved5c[0xFC];
    uint32 value_158; // 158
    uint32 value_15c; // 15C
} SUP_OBJ;

// Sprite effects, 40 of them from 0x801EF000 (stride 0x50).
typedef struct
{
    uint8 value_0; // 00
    uint8 value_1; // 01
    uint8 value_2; // 02
    uint8 value_3; // 03
    uint8 reserved04[4];
    union
    {
        uint8 b[4];
        uint32 w;
    } routine; // 08
    uint8 reserved0c[8];
    uint8 *model_14; // 14: start of the object func_8002A160 draws
    union
    {
        MATRIX m;
        sint32 w[8];
    } mtx;           // 18
    SVECTOR pos;     // 38
    uint32 color_40; // 40
    uint8 reserved44[0xC];
} SUP_SPR;

#define SUP_SPR_TBL ((SUP_SPR *)0x801EF000)

#define SUP_OBJ_0 ((SUP_OBJ *)0x801EE000)
#define SUP_OBJ_1 ((SUP_OBJ *)0x801EE800)

typedef void (*SUP_FUNC)(void);
typedef void (*SUP_OBJ_FUNC)(SUP_OBJ *op);

// The module's state (0xA4 bytes at 0x801DC208; func_801D8130 clears the first 0xA0).
typedef struct
{
    uint8 routine_0; // 00
    uint8 routine_1; // 01
    uint8 routine_2; // 02
    uint8 routine_3; // 03
    uint8 reserved04[4];
    sint16 value_08; // 08
    sint16 value_0a; // 0A
    VECTOR vec_0c;   // 0C
    sint32 value_1c; // 1C
    sint32 value_20; // 20
    sint32 value_24; // 24
    VECTOR vec_28;   // 28
    sint32 value_38; // 38
    sint32 value_3c; // 3C
    sint32 value_40; // 40
    sint32 value_44; // 44
    sint32 value_48; // 48
    sint32 value_4c; // 4C
    uint8 reserved50[4];
    sint32 value_54; // 54
    sint32 value_58; // 58
    sint32 value_5c; // 5C
    sint32 value_60; // 60
    sint16 value_64; // 64
    uint16 value_66; // 66
    VECTOR scale_68; // 68: scale of every sprite's matrix
    VECTOR scale_78; // 78: scale of the selected part's model
    SVECTOR rot_88;  // 88: rotation of the selected part's model
    sint16 value_90; // 90
    sint16 value_92; // 92
    sint16 anim_94;  // 94
    sint16 value_96; // 96
    sint32 value_98; // 98
    sint16 value_9c; // 9C
    uint8 reserved9e[2];
    uint8 value_a0; // A0: not cleared by func_801D8130
    sint8 count_a1; // A1: countdown in func_801DB2AC
    sint8 found_a2; // A2: func_801DB43C's result
    uint8 reserveda3;
} SUP_WORK;

// D_801DC208.value_60 as a scalar of its own: func_801D952C reaches it by symbol each time.
extern sint32 D_801DC268;
// D_801DC208.anim_94 as a scalar of its own: func_801DB2AC's case 5 stores it by symbol, which lets
// the following routine_3 increment keep its address register.
extern sint16 D_801DC29C;

// The module's own globals (its .data).
extern SUP_FUNC D_801DC174[];     // D_801DC208.routine_0 handlers
extern SUP_OBJ_FUNC D_801DC19C[]; // SUP_OBJ_0 routine_0 handlers
extern SUP_OBJ_FUNC D_801DC1A8[]; // SUP_OBJ_1 routine_0 handlers
extern SUP_WORK D_801DC208;

// ROCK_NEO.EXE.
// The current drawing buffer, as far as its ordering-table link.
typedef struct
{
    uint8 reserved00[0x78];
    u_long ot_78; // 78
    uint8 reserved7c[4];
    u_long tag; // 80
} SUP_LINK;

#define SUP_DISPLAY_INDEX (*(uint8 *)0x1F800000)
#define SUP_SCRATCH_02    (*(uint16 *)0x1F800002)
#define SUP_OT            (*(u_long **)0x1F80003C)
#define SUP_PACKET_PTR    ((POLY_FT4 **)0x1F800070)

// Game_work, as this module reads it.
typedef struct
{
    uint8 reserved00[0x50];
    union
    {
        struct
        {
            sint8 stage;
            sint8 room;
        } b;
        uint16 h;
    } area_50; // 50
    uint8 reserved52[0x27];
    uint8 stage_79; // 79
    uint8 room_7a;  // 7A
} SUP_GAME;

// Player_work, as this module sets it.
typedef struct
{
    uint8 reserved00[0x14];
    SVECTOR pos;     // 14
    VECTOR fpos;     // 1C
    SVECTOR old_pos; // 2C
    VECTOR old_fpos; // 34
    uint8 reserved44[0x10];
    SVECTOR rot;     // 54
    SVECTOR old_rot; // 5C
    uint8 reserved64[0x10];
    uint8 value_74; // 74
    uint8 value_75; // 75
    uint8 value_76; // 76
    uint8 value_77; // 77
    uint8 reserved78[0xF8];
    sint8 value_170; // 170
    uint8 value_171; // 171
    sint8 value_172; // 172
    uint8 value_173; // 173
    uint8 reserved174[0x2DA];
    sint8 value_44e; // 44E
    uint8 value_44f; // 44F
    uint8 reserved450[0xA4];
    uint8 level_4f4[32][8]; // 4F4: part levels, eight per part kind
} SUP_PLAYER;

extern SUP_PLAYER Player_work;

extern SUP_GAME Game_work;
extern sint32 Moji_flag;
extern uint8 Sound_fade_flags;
extern sint16 D_80098A72;
// Joy1, as this module reads it.
typedef struct
{
    uint8 reserved00[0x26];
    uint16 held;     // 26
    uint16 previous; // 28
    uint16 pressed;  // 2A
} SUP_PAD;

extern SUP_PAD Joy1;
extern uint16 D_8008D8EC[]; // prices: [(kind * 5 + part) * 4 + level]
extern uint32 D_80098958;
extern uint8 D_800C356E;
extern uint8 D_800C356F;
extern uint32 D_800A4D40[][0x1000];
extern SUP_LINK *Disp_env_ptr;
extern uint32 D_801DC190[]; // routine word by Moji_flag
// Scenario flag combinations (flags 0x500 + n) and the flag (0x2F4 + n) they set.
typedef struct
{
    uint8 b[4];
} SUP_KEY;

typedef struct
{
    SUP_KEY key;
    sint32 flag;
} SUP_COMBO;

extern SUP_COMBO D_801DBE90[];

extern sint16 D_800BBCF8[];      // sine table
extern uint8 D_8008D7E8[][5][4]; // part values: [kind][part][level]
extern uint8 D_801DC158[][2];    // texture u, v by kind

// Camera offsets for func_801D8CC8.
typedef struct
{
    sint16 value_0, value_2, value_4, value_6, value_8, value_a;
} SUP_CAM;

extern SUP_CAM D_801DC1B4[];
extern SVECTOR D_801DC0E8[];
extern SVECTOR D_801DBF48[]; // sprite positions; pad holds value_3
extern uint16 D_801DC0A4[];  // value_60 by Player_work.value_172
extern uint16 D_801DC0C8[];  // per kind: scenario flags (minus 0x4C0) of sprites 13 to 25, part row
extern uint8 D_801DC088[][2]; // message by kind
extern uint8 D_801DC1E4[];    // message by kind
extern uint8 D_801DC1F4[];    // message by kind // player start position and direction
extern sint8 D_801DC138[];    // func_801DBC5C argument by Game_work.value_50

sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
void MojiTaskKill(void);
uint32 Sce_flag_test(uint32 flag);
void Sce_flag_off(uint32 flag);
void Sce_flag_on(uint32 flag);
sint32 func_800665FC(sint32 arg);
void Sound_call(sint32 sound, ...);
void func_8001B314(void);
void Sound_seq_stop_all(void);
void func_80016D64(void);
void func_80017C30(sint32 arg);
void Sound_fade_start(sint32 arg);
void Sound_stage_check(void);
void func_8001F23C(void);
void func_8001F3C8(void);
void func_8001F5E4(void);
void func_8002FA10(void *obj, void *arg);
void func_80037594(void);
void Model_work_init(void *obj, void *arg);

void Mem_clear(void *start, void *end);
void func_80023728(void *vec, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80028F90(void *rec);
void func_800322A8(void *obj, sint32 anim, sint32 arg);
void func_80032488(void *obj);
void Money_add(sint32 arg0, sint32 arg1, sint32 arg2);
void func_8002A160(void *obj, uint32 flags);

// Moji scripts loaded with the module.
#define SUP_SCRIPT ((uint8 *)0x801E4000)

// This module.
void func_801D8524(void);
void func_801DBC5C(sint32 arg);
void func_801DB2AC(void);
void func_801D9388(void);
void func_801D9504(void);
void func_801D952C(void);
sint32 Cd_read_sync2(void);
void func_801D8DC0(void);
void func_801D8E84(void);
void func_801DB1E0(void);
void func_801DB5B8(void);
void func_801D8B68(void);
void func_801DBBE0(void);
void func_801DB800(void);
void func_8003B140(void);
void func_80053AA4(sint32 arg);
void func_8005C224(sint32 price);
void func_8005C24C(sint32 kind);
void Obj_work_flag_change(sint32 a0, sint32 a1);
sint32 Money_check(sint32 amount);
void func_801D8F68(void);
void func_801DAB58(void);
sint32 func_801DB43C(void);
void func_801D8564(void);
void func_801D8594(void);
void func_801D86C4(void);
void func_801D8490(void);
void func_801D9C74(void);
void func_801D9794(void);
void func_801D99CC(void);
void func_801DB1C0(void);
void func_801DA7DC(sint32 w, sint32 y, sint32 v);

#endif // SUP_H
