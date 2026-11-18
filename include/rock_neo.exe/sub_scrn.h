#ifndef ROCK_SUB_SCRN_H
#define ROCK_SUB_SCRN_H

#include "common.h"
#include "psyq/libgpu.h"

// Byte read both signed and unsigned by different helpers.
typedef union
{
    sint8 s;
    uint8 u;
} SUB_BYTE;

// Sub-screen (status/parts menu) work. Only the fields these helpers touch.
typedef struct
{
    uint8 dst_0;
    uint8 val_1;
    uint8 src_2;
    uint8 dst_3;
    uint8 val_4;
    uint8 src_5;
    uint8 flag_6;
    uint8 reserved7;
} SUB_ENTRY;

typedef struct
{
    sint8 routine_0;
    sint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    uint8 reserved4[2];
    uint8 mode_6;
    uint8 reserved7[5];
    uint16 flag_C;
    uint8 reservedE[2];
    SUB_ENTRY entry[5];
} SUB_WORK;

// Local view of Player_work: only the fields the sub-screen touches.
typedef struct
{
    uint8 reserved00[0x6E];
    sint16 value_6E;
    uint8 reserved70[0xB0 - 0x70];
    sint16 value_B0;
    uint8 reserved_B2[0x110 - 0xB2];
    uint8 value_110;
    uint8 reserved111[0x59];
    sint8 value_16A;
    uint8 flags_16b;
    sint8 value_16C;
    uint8 reserved16d[3];
    sint8 value_170;
    uint8 reserved171;
    sint8 value_172;
    uint8 reserved173[0x2DB];
    sint8 value_44E;
    sint8 value_44F;
    union
    {
        struct
        {
            uint16 half_0;
            uint8 byte_2;
            uint8 reserved3;
        } v;
        uint8 b[4];
    } slot;
    uint8 order[0x20];
    uint8 reserved474[0x88];
    SUB_BYTE sum[4];
} SUB_PLAYER;

// Entry-select work (+2 state byte, +4 table index, +5 arg).
typedef struct
{
    uint8 reserved0;
    sint8 routine_1;
    sint8 routine_2;
    uint8 reserved3;
    uint8 index_4;
    uint8 arg_5;
} SUB_SEL;

typedef struct
{
    uint8 reserved00[8];
    uint16 slot_8;
    uint8 slot_a;
    uint8 slot_b;
} SUB_PARTS;

// Player view for the sound re-init check.
typedef struct
{
    uint8 reserved00[8];
    uint32 flags_8;
    uint8 reserved0c[0x164];
    sint8 value_170;
    uint8 reserved171[3];
    sint8 value_174;
    uint8 reserved175[3];
    sint8 value_178;
    uint8 reserved179[0x24F];
    uint8 args_3c8[1];
} SUB_SND;

typedef struct
{
    uint16 value_0;
} SUB_CODE_STATE;

typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 reserved02[0xA];
    uint32 timer_0c; // frame counter (60 per second)
    uint8 reserved10[0xC];
    sint32 value_1C;
    uint8 reserved20[0x30];
    sint8 value_50;
    sint8 value_51;
    uint8 reserved52[2];
    sint8 value_54;
    uint8 reserved55[0x78 - 0x55];
    sint8 value_78;
    uint8 value_79;
    uint8 value_7A;
    uint8 reserved7B;
    uint8 value_7C;
} SUB_GAME;

// Sprite primitive as five raw words (tag, rgb+code, xy, uv+clut, wh)
typedef struct
{
    uint32 tag;
    uint32 rgbc;
    sint32 xy;
    uint32 uv_clut;
    uint32 wh;
} SUB_PRIM;

// Ordering table slot view (tag word at +0x8C)
typedef struct
{
    uint8 reserved00[0x8C];
    uint32 tag_8C;
} SUB_OT;

// Same OT type seen at the +0x78 slot
typedef struct
{
    uint8 reserved00[0x78];
    uint32 tag_78;
} SUB_OT78;

#ifdef __wasm32__
typedef sint32 (*SUB_FUNC)(SUB_WORK *wp);
#else
typedef void (*SUB_FUNC)(SUB_WORK *wp);
#endif

// Player_work and Game_work reached through their fixed addresses. GCC 2.7 keeps a
// symbol's address in a saved register across calls, but rebuilds a literal address
// with lui at each access, as retail does in some functions (func_8005F3D0).
#define SUB_PLAYER_WORK ((SUB_PLAYER *)0x800B51B0)
#define SUB_GAME_WORK   ((SUB_GAME *)0x800C1B10)

extern SUB_PLAYER Player_work;
extern SUB_OT *D_80098934;
extern SUB_WORK D_800A38F0;
extern SUB_FUNC D_8008DBB0[];
extern SUB_BYTE Rock_buster_parts_tbl[][8];
extern SUB_BYTE D_8008FE65[][8];
extern SUB_BYTE D_8008FE66[][8];
extern SUB_BYTE D_8008FE67[][8];
extern uint16 D_800C0C2A;
extern uint8 D_80098B2D;
extern uint8 D_80098B31;
extern uint8 D_80098B2E;
extern SUB_GAME Game_work;
extern uint32 Moji_flag3;
extern uint8 *D_8008CB64;
extern SUB_CODE_STATE Code800133D8_work;
extern uint8 *D_8008CE78;
extern uint8 *D_8008CE84;
extern uint32 Moji_flag;
extern uint8 D_8008DAF4[];
extern uint8 *D_8008CB94;

uint32 Sce_flag_test(uint32 flag);
sint32 Cd_read_sync2(void);
void func_8001D7AC(sint32 arg);
void func_800425FC(SUB_PLAYER *pl, sint32 arg);
void func_800605DC(void);
void func_80060248(SUB_WORK *wp);
void Sub_screen_shift_check(SUB_WORK *wp);
void Sub_screen_rb_parts_calc_sub00(SUB_WORK *wp, sint32 idx);
void Sub_screen_rb_parts_calc_sub01(SUB_WORK *wp, sint32 idx);
void func_80063BA8(void);
void func_80063EF0(void);
void func_800665E8(void);
void func_8001B314(void);
void func_8001B33C(void);
void func_8001D494(sint32 arg0, sint32 arg1, sint32 arg2);
void Sce_flag_off(uint32 flag);
void func_8005C218(sint32 value);
void func_80013420(void);
void func_80012F78(void (*entry)(void));
void Pl00_shot_enable_off(SUB_PLAYER *wp);
void Pl00_shot_enable_on(SUB_PLAYER *wp);
void Obj_work_flag_change(sint32 mask, sint32 flags);
void Sub_screen_sort_sub(SUB_PLAYER *wp, sint32 a, sint32 b);
void Sub_screen_rb_parts_calc(SUB_WORK *wp);
void Sub_screen_back_ground_set(void);
void Sub_screen_status_param_set(sint32 slot);
void func_8005F608(SUB_SEL *wp);
void func_8005F3D0(SUB_SEL *wp);
void func_8005FAE4(SUB_SEL *wp);
void func_8005FBB4(SUB_SEL *wp);
void func_8005FFBC(SUB_SEL *wp);
sint32 Sub_screen_cancel_check(void);
sint32 func_8005FDE4(SUB_GAME *gw);
#ifdef __wasm32__
// WebAssembly calls require the callee's fixed parameter signature.
void Sound_call(sint16 id, uint32 arg1, uint32 arg2);
#else
void Sound_call(sint32 sound, ...);
#endif
void func_8003B140(void);
void func_80017C30(sint32 arg);
void func_8001D854(sint32 arg);
void func_80016D64(void);
void func_8001B33C(void);
void func_8001B314(void);
void func_80019C20(void);
#ifdef __wasm32__
sint32 func_8001F23C(void);
#else
void func_8001F23C(void);
#endif
#ifdef __wasm32__
sint32 func_8001F3C8(void);
#else
void func_8001F3C8(void);
#endif
extern uint32 D_80098958;
void Sub_screen_gauge_set(sint32 x, sint32 y, sint32 width, sint32 row);
void Sub_screen_status_calc(SUB_WORK *wp, sint32 slot);
extern uint8 D_8008D7E8[][5][4];
extern uint16 D_8008DB08[];
extern uint8 D_8008D7EC[];
// Defined as uint8 in code_8005C258.c; func_8005ED9C tests v0 without an andi, so it saw int.
sint32 func_8005D95C(void);
void func_8005D9C4(void);
void func_80037594(void);
void func_8005EBA4(sint32 arg);
void func_8005EBB4(sint32 arg);
#define SUB_PLAYER_BYTE_4F4(slot, i) (*((sint8 *)&Player_work + 0x4F4 + (slot) * 8 + (i)))
void Sub_screen_gauge_set2(sint32 x, sint32 y, sint32 width, sint32 flag);
sint32 func_80037604(SUB_PLAYER *pl, sint32 slot);
#define SUB_PLAYER_HALF_4FA(i) (*(sint16 *)((uint8 *)&Player_work + 0x4FA + (i) * 8))
void Sub_screen_basic_param_set(void);
SUB_PRIM *Sub_screen_status_param_set_sub(SUB_PRIM *prim, sint32 x, sint32 value, sint32 flags);
SUB_PRIM *Sub_screen_basic_param_set_sub(SUB_PRIM *prim, sint32 x, sint32 value, sint32 flags);
void func_800602A4(SUB_WORK *wp, sint32 arg);
#ifdef __wasm32__
// WebAssembly calls require the callee's fixed parameter signature.
void Sound_call(sint16 id, uint32 arg1, uint32 arg2);
#else
void Sound_call(sint32 sound, ...);
#endif
void Sound_call2(sint16 id, void *args);
void MojiTaskKill(void);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
void Game_logo_kill(sint32 index);
void Cd_read_comb(sint32 arg);
void func_80063FC0(sint32 index, sint32 arg);

#endif // ROCK_SUB_SCRN_H
