#ifndef MOJI_H
#define MOJI_H

#include "common.h"
#include "player.h"
#include "psyq/libgpu.h"
#include "display.h"

// Text/message task: only the fields these helpers touch.
typedef struct MOJI_WORK
{
    uint32 flags_0;
    sint16 val_4;
    sint16 index_6;
    uint16 val_8;
    sint16 val_A;
    sint16 val_C;
    sint16 val_E;
    uint16 pos_10;
    uint16 pos_12;
    uint8 *pos_14;
    uint32 jump_tbl_18[1];
    uint8 unk_1C[0x1C];
    uint16 val_38;
    sint8 val_3A;
    uint8 count_3B;
    uint8 val_3C;
    uint8 val_3D;
    uint8 val_3E;
    uint8 val_3F;
    uint32 val_40;
    uint8 *base_44;
    uint8 *pos_48;
    uint32 jump_tbl_4C[1];
    uint8 unk_50[0x1C];
    uint8 *pos_6C;
    uint8 val_70;
    uint8 val_71;
    union
    {
        sint8 skip;
        uint8 count;
    } v_72;
    uint8 val_73;
    uint8 *pos_74;
    uint8 val_78;
    uint8 val_79;
    uint8 unk_7A[2];
    uint8 val_7C;
    uint8 val_7D;
    uint8 val_7E;
    uint8 val_7F;
    uint32 val_80;
    uint8 unk_84;
    uint8 val_85;
    uint8 unk_86[2];
    sint16 val_88, val_8A, val_8C, val_8E;
    sint16 val_90, val_92, val_94, val_96;
    POLY_F4 *prim_98;
    POLY_F4 *prim_9C;
    POLY_G4 *prim_A0[4];
    uint8 val_B0, val_B1, val_B2;
    uint8 unk_B3;
    uint16 val_B4;
    uint16 val_B6;
    uint16 val_B8;
    uint16 val_BA;
    uint16 val_BC;
    uint16 depth_BE;
    uint16 depth_C0;
    uint16 val_C2;
} MOJI_WORK;

// Local view of Game_work: only the fields the moji commands read.
typedef struct
{
    uint8 reserved00[0x1C];
    uint32 value1C;
    uint8 reserved20[8];
    uint32 value28, value2C, value30, value34, value38, value3C;
    uint8 reserved40[0x20];
    sint16 value60;
    uint8 reserved62[4];
    uint8 value66, value67;
    uint8 reserved68[0x14];
    uint8 value7C;
    uint8 value7D;
    uint8 reserved7E[6];
    struct
    {
        uint32 value0;
        uint16 value4[6];
    } value84[1];
} MOJI_WORK_G;

#define MOJI_GAME ((MOJI_WORK_G *)Game_work)

typedef struct
{
    sint16 x, y, z, pad;
} MOJI_POS;

typedef void (*MOJI_FUNC)(MOJI_WORK *);

typedef MOJI_WORK MOJI_WORK2;

#define MOJI_FLAG_08000000 0x08000000
#define MOJI_FLAG_20000000 0x20000000

extern uint32 D_800989EC;
extern uint16 D_80098912;
extern MOJI_FUNC D_8008AB08[];
extern uint8 *D_8008D0D4[];
extern uint8 *D_8008CBA4[];
extern uint8 *D_8008CE5C[];
extern uint8 D_800BE2F8[];
extern sint32 D_8008AF00[];
extern uint8 D_800BE3DB[];
extern uint8 *D_8008CE10[];
extern uint8 *D_8008CACC[];
extern uint8 D_8008D028[];
extern MOJI_FUNC D_8008AAC0[];
extern MOJI_WORK Moji_work[];
extern uint8 *D_8008BAA4[];
extern uint8 *D_8008CE58;
extern uint8 *D_8008CAC8[];
extern uint32 Game_work[];

uint16 func_80054410(uint8 *p);
void func_8005BF10(sint32 mode, uint32 value, uint8 *out);
sint32 func_8005DA78(sint32 arg0);
sint32 func_8005DAEC(sint32 arg0);
sint32 func_8005DA1C(sint32 arg0);
sint32 Sce_flag_test(sint32 flag);
// Sce_flag_on, func_80039E18 and func_80043294 are void, but Capcom's moji code called them
// without prototypes (implicitly int): its calls keep the unused v0 result (call_value).
#ifdef __wasm32__
void Sce_flag_on(sint32 flag);
#else
sint32 Sce_flag_on(sint32 flag);
#endif
void Sce_flag_off(sint32 flag);
#ifdef __wasm32__
// WebAssembly calls require the callee's fixed parameter signature.
void Sound_call(sint16 id, uint32 arg1, uint32 arg2);
#else
void Sound_call(sint32 sound, ...);
#endif
void func_8005ACA8(MOJI_WORK *wp);
sint32 rand(void);
#ifdef __wasm32__
void func_80039E18(void);
#else
sint32 func_80039E18(void);
#endif
extern uint8 D_80097F6C[][6];
extern uint8 D_80097F79[];
extern uint8 D_80097F7A[];
extern uint8 D_80097F7B[];
sint32 func_80031198(MOJI_POS *pos, PL_SHORT_VECTOR *target);
void func_80039FAC(sint32 *vec, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80039FFC(sint32 *vec, sint32 arg1, sint32 arg2, sint32 arg3);
sint32 func_8003A13C(void);
extern MOJI_POS *D_800987B8;
extern uint8 D_800987B0[];
extern sint32 D_800A396C;
extern uint8 Scene_work;
void func_8001D494(sint32 arg0, sint32 arg1, sint32 arg2);
sint32 func_8004327C(sint32 arg0);
#ifdef __wasm32__
void func_80043294(sint32 arg0, sint32 arg1, sint32 arg2);
#else
sint32 func_80043294(sint32 arg0, sint32 arg1, sint32 arg2);
#endif
void Game_logo_kill(sint32 index);
void func_80063FC0(uint32 arg0, uint32 arg1);

sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);

// Small data ($gp) these functions use.
extern uint8 D_80098830;
extern sint32 D_80098AF4;
extern uint32 D_800989E0;
extern uint8 D_800989D4;
extern uint8 D_8009899C;
extern uint8 *D_8008CCA4[];
extern uint32 Moji_flag;
extern uint32 Moji_flag3;
extern uint8 D_80098851;
extern uint32 D_80098824;
extern uint8 D_800988F4;
extern uint16 D_80097F64[];
extern uint8 D_80097F68[];
extern uint16 D_8008FE40[];
extern uint16 D_8008FE44;
extern uint16 D_8008FE62;
extern uint8 Sce_flag[];
extern uint8 D_80098B2D;
extern uint8 D_800987D4;
extern char D_80097F60[];
void func_8001FE38(uint32 flags, const char *fmt, ...);
void Sub_screen_rb_parts_set(void);
void func_8005BFC0(uint32 frames, uint8 *out);
void func_8005C0E4(uint32 value, uint8 *out);
extern uint16 D_8008FD7C[];
extern uint8 D_80097FF4[];
extern uint16 D_8008D8EC[][5][4];
extern uint8 D_80097FEC[];
extern uint8 D_80097FE4[];
extern uint8 D_80097FDC[];
extern uint8 *D_8008CBA0[];
extern uint16 D_8008AF40[];
extern uint8 *D_8008CAD0[];
extern uint8 *D_8008CAD4[];
extern sint32 D_800989A8;
extern uint8 D_800BE420[];
uint32 func_80054424(uint8 *p);
uint32 func_8001D878(void);
extern sint32 D_800986F0;
extern uint8 D_80098930;
extern uint8 D_80098B6C;
extern uint32 D_8008AF24[];
extern uint8 D_8008AF3C[];
extern uint16 D_8008FD3C[];
extern uint8 D_80098850;
extern uint8 D_800987F8;
extern sint32 D_80098B2C;
extern uint32 D_80098960;

extern uint8 D_80097FE2; // byte 6 of the D_80097FDC script, written as its own symbol

extern DISP_ENV *D_80098934;
extern uint8 D_8008AF18[];
void func_8005BCE4(MOJI_WORK *wp, sint32 index);
sint32 func_80054E54(MOJI_WORK *wp);
void func_80056820(MOJI_WORK *wp);
sint32 func_80057FF8(MOJI_WORK *wp);
sint32 func_80059E74(MOJI_WORK *wp);
void Sub_screen_sort_attack(void);
void Sub_screen_sort_energy(void);
void Sub_screen_sort_range(void);
void Sub_screen_sort_rapid(void);
extern uint8 D_80098A64;
extern uint8 D_80098A65;
extern uint8 D_8008D0AC[];
extern uint8 D_800986E0;
extern uint8 D_800986E4;
extern uint8 D_800989D4;
extern uint8 D_800986E8;
extern uint8 D_800986EC;
extern uint32 D_800987E0;
typedef sint32 (*MOJI_CMD_FUNC)(MOJI_WORK *);
extern MOJI_CMD_FUNC D_8008A91C[];
extern MOJI_FUNC D_8008AAC4[];
extern MOJI_FUNC D_8008AAE4[];
extern RECT D_80097F50[];
extern uint16 D_80097F30[];
extern uint8 D_8008AE7C[];

#endif
