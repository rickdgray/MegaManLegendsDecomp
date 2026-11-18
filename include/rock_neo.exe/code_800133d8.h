#ifndef ROCK_NEO_CODE_800133D8_H
#define ROCK_NEO_CODE_800133D8_H

#include "common.h"
#include "system.h"
#include "game.h"
#include "psyq/libgpu.h"

typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    sint16 timer;
    sint16 timer06;
    sint16 index08;
    uint16 value0a;
    sint8 menu_index;
    uint8 reserved0d;
    uint16 flags_0e;
} CODE800133D8_STATE;

typedef void (*CODE800133D8_FUNC)(CODE800133D8_STATE *wp);

typedef struct
{
    uint8 reserved00[0x74];
    uint32 tag74;
    uint32 tag78;
    uint32 tag7c;
    uint32 tag;
    uint32 tag84;
    uint32 tag88;
    uint32 tag8c;
} CODE800133D8_LINK;

#define CODE800133D8_PACKET_PTR    ((POLY_FT4 **)0x1F800070)
#define CODE800133D8_SCRATCH_TABLE ((uint32 **)0x1F800058)
#define CODE800133D8_DISPLAY_INDEX (*(uint8 *)0x1F800000)

#define CODE800133D8_SCRATCH_MODE (*(uint8 *)0x1F800001)

extern CODE800133D8_STATE Code800133D8_work;
extern sint32 D_80098810;
extern sint32 D_80098864;
extern uint32 D_800808A4[];
extern uint32 D_800808A8[];
extern uint32 D_800808D0[];
extern uint32 D_800979DC[];
extern uint32 D_800979EC[];
extern uint32 D_800A4D40[][0x1000];
extern uint32 D_800A4F50[][0x1000];
extern CODE800133D8_LINK *D_80098934;

extern CODE800133D8_FUNC Code800133D8_main_tbl[];
extern sint16 D_80098A70;
extern uint16 D_800C0C26;
extern uint16 D_800C0C2A;
extern uint8 *D_8008CB64[];
extern uint32 Moji_flag;

void func_80013420(void);
void func_800155A4(void);
void func_80015428(CODE800133D8_STATE *wp);
void func_80017C30(sint32 arg);
void func_8002E7A8(sint32 arg);
void func_8003697C(void);
void func_8002CFA4(void);
void func_800371A0(uint32 *arg0, uint32 *arg1);
void MojiTaskKill(void);
void func_80013FB8(void);
void func_80014394(void);
void func_80013F60(CODE800133D8_STATE *wp);
void func_80013F8C(CODE800133D8_STATE *wp);
void func_800175D8(void);
void func_80016FD4(void);
void func_80038370(uint32 *arg0, uint32 *arg1);
void func_800175FC(void);
void func_80028DE0(void);

void func_8005C258(void);
void Cd_read_comb(sint32 arg);
void func_8001D888(sint32 arg);
void func_80019FB4(void);
void func_80063BA8(void);
void func_80063EF0(void);
void func_80017994(void);
void func_80031AA4(void);
// Some sound commands use only the ID; other commands consume two payload words.
#ifdef __wasm32__
// WebAssembly calls require the callee's fixed parameter signature.
void Sound_call(sint16 id, uint32 arg1, uint32 arg2);
#else
void Sound_call(sint32 sound, ...);
#endif
void func_8001456C(sint32 index);
void func_800137D4(void);
void Sub_screen_back_ground_set(void);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);

#endif
