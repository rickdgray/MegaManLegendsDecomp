#ifndef ROCK_NEO_GAME_H
#define ROCK_NEO_GAME_H

#include "common.h"
#include "system.h"
#include "player.h"

#define GAME_TIMER_MAX 0xA4CB7F

typedef union
{
    uint32 value08;
    uint16 aperture;
    sint16 transition_aperture;
    struct
    {
        sint16 lo;
        sint16 value0a;
    } words;
} GAME_WORD08;

typedef union
{
    uint32 value04;
    struct
    {
        uint16 lo;
        sint16 timer06;
    } words;
} GAME_WORD04;

// Sound bank slot (eight-byte records from +0x1B8)
typedef struct
{
    sint16 vab; // PsyQ VAB id (-1 = none)
    uint8 id;
    uint8 reserved03[5];
} GAME_SOUND_SLOT;

// Only fields observed in this subsystem are described.
typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    GAME_WORD04 work04;
    GAME_WORD08 work08;
    uint32 timer_0c;
    uint32 value10;
    uint32 value14;
    uint16 flags_18;
    uint16 flags_1a;
    uint8 reserved1c[0x34];
    sint8 routine_50;
    uint8 routine_51;
    uint8 flags_52;
    uint8 flags_53;
    uint8 flags_54;
    uint8 flags_55;
    uint8 reserved56[2];
    uint8 flags_58;
    uint8 flags_59;
    uint8 reserved5a;
    sint8 option_5b;
    uint8 reserved5c[4];
    sint16 timer60;
    uint8 reserved62[6];
    sint16 value68;
    sint16 value6a;
    sint16 value6c;
    uint8 reserved6e[2];
    sint16 value70[4];
    uint8 reserved78;
    uint8 flags_79;
    uint8 flags_7a;
    uint8 reserved7b[6];
    sint8 flags_81;
    sint8 flags_82;
    uint8 flags_83;
    uint8 reserved84[0xF0];
    uint32 slots[16];
    uint8 reserved1b4[4];
    GAME_SOUND_SLOT sound_1b8[5];
    uint8 reserved1e0[0x30];
} GAME_WORK;

typedef struct
{
    uint8 reserved00[8];
    sint16 x, y, z;
    uint8 reserved0e[4];
    sint16 angle;
    sint8 flags14;
    sint8 flags15;
    uint8 stage;
    uint8 room;
    uint8 fade_in, fade_out;
    uint8 reserved1a[0xE];
} GAME_ENTRY_WORK;

// Dispatch records: observed common prefix and each array stride.
typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03;
    uint8 routine;
    uint8 reserved05;
    uint8 active;
    uint8 reserved07[0x3B9];
} GAME_WORK_3C0;
typedef void (*GAME_FUNC_3C0)(GAME_WORK_3C0 *wp);

typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03;
    uint8 routine;
    uint8 reserved05;
    uint8 active;
    uint8 reserved07[0x59D];
} GAME_WORK_5A4;
typedef void (*GAME_FUNC_5A4)(GAME_WORK_5A4 *wp);

typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03;
    uint8 routine;
    uint8 reserved05;
    uint8 active;
    uint8 reserved07[0x105];
} GAME_WORK_10C;
typedef void (*GAME_FUNC_10C)(GAME_WORK_10C *wp);
// The overflow table D_80089820 is called as returning a value (keeps its call distinct
// from the GAME_TABLE_10C call in func_80017210).
typedef sint32 (*GAME_FUNC_10C_RET)(GAME_WORK_10C *wp);

typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03;
    uint8 routine;
    uint8 reserved05;
    uint8 active;
    uint8 reserved07[0x41];
} GAME_WORK_48;
typedef void (*GAME_FUNC_48)(GAME_WORK_48 *wp);

typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03;
    uint8 routine;
    uint8 reserved05;
    uint8 active;
    uint8 reserved07[0x1D];
} GAME_WORK_24;
typedef void (*GAME_FUNC_24)(GAME_WORK_24 *wp);

typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03;
    uint8 routine;
    uint8 reserved05;
    uint8 active;
    uint8 reserved07[0x49];
} GAME_WORK_50;
typedef void (*GAME_FUNC_50)(GAME_WORK_50 *wp);

typedef void (*GAME_FUNC)(GAME_WORK *wp);

#define GAME_SCRATCH_MODE (*(uint8 *)0x1F800001)

#define GAME_TABLE_3C0 (*(GAME_FUNC_3C0 ***)0x1F800058)
#define GAME_TABLE_5A4 (*(GAME_FUNC_5A4 ***)0x1F80005C)
#define GAME_TABLE_10C (*(GAME_FUNC_10C **)0x1F800060)
#define GAME_TABLE_48  (*(GAME_FUNC_48 **)0x1F800064)
#define GAME_TABLE_24  (*(GAME_FUNC_24 **)0x1F800068)
#define GAME_TABLE_50  (*(GAME_FUNC_50 **)0x1F80006C)

typedef struct
{
    sint16 x, y, z;
} GAME_DELTA;

extern PL_FIXED_VECTOR D_800A39F0;
extern PL_FIXED_VECTOR D_800A3A00;
extern sint32 D_800A39F4;
extern sint32 D_800A39F8;
extern sint32 D_80098004;
extern uint8 D_800C0C24;
extern uint8 Scene_work;
extern GAME_WORK_3C0 D_8009F108[16];
extern GAME_WORK_3C0 *D_80098820;
extern GAME_WORK_5A4 D_800C3580[4];
extern GAME_WORK_5A4 *D_800989D0;
extern GAME_WORK_10C D_800BFB20[16];
extern GAME_WORK_10C D_8009CF88[32];
extern GAME_WORK_10C *D_800988F8;
extern GAME_FUNC_10C D_80089820[];
extern GAME_WORK_48 D_800A3B40[64];
extern GAME_WORK_48 *D_800988E4;
extern GAME_FUNC_48 D_80089858[];
extern GAME_WORK_24 D_800A2D08[16];
extern GAME_WORK_24 *D_800988F0;
extern GAME_WORK_50 D_800BF118[32];
extern GAME_WORK_50 *D_80098924;

extern GAME_FUNC Game_main_tbl[];
extern GAME_WORK Game_work;
extern GAME_ENTRY_WORK D_800C3558;
extern sint16 D_80098A72;
extern uint8 D_80098788;
extern uint16 D_80098910;
extern sint16 D_800C3560;
extern sint16 D_800C3562;
extern sint16 D_800C3564;
extern sint16 D_800C356A;
extern sint8 D_800C356C;
extern sint8 D_800C356D;
extern uint8 D_800C356E;
extern uint8 D_800C356F;
extern uint8 D_800C3570;

sint32 func_800665FC(sint32 arg);
void func_80015DB4(void);
void func_8001B314(void);
void func_80031AA4(void);
void func_80016BC0(void);
void func_80016BF4(void);

void func_80016D64(void);
void func_80015EE8(PL_WORK *wp, GAME_ENTRY_WORK *entry, sint32 reset);
void Sce_flag_on(sint32 flag);
void func_8001F23C(void);
void func_8001F3C8(void);
void func_80038648(void);
void func_8001D8C0(sint32 mode);
void func_8003B278(sint32 mode);
void func_8003BE40(sint32 mode);
void func_8005DBB4(sint32 mode);
void func_80067E6C(sint32 mode);
void func_8006471C(void);
void func_80065AA8(void);
void func_800664BC(void);
void func_8002E7A8(sint32 mode);
void func_80063BA8(void);
void func_80019FB4(void);

void func_8001B33C(void);
void func_800665E8(void);
void Sce_flag_off(sint32 flag);
void func_8001D494(sint32 arg0, sint32 arg1, sint32 arg2);

void func_8005DF3C(void);
void func_8005DF4C(void);
void Sound_key_off_voice(sint32 voice);
void Sub_screen_sound_reinit(PL_WORK *wp);
void Game_logo_kill(sint32 index);

void func_8005EBE4(void);
sint32 func_8005EC34(void);
void func_8001F5E4(void);

void func_800175D8(void);
void func_800679B8(void);
void func_80017478(void);
void func_8003C07C(void);
void func_8003606C(void);
void func_8005C2B8(void);
void func_80017094(void);
void func_80016FD4(void);
void func_80017210(void);
void func_800172F4(void);
void func_80017528(void);
void func_80051BE4(void);
void func_8003C2D8(void);
void func_80017154(void);
void func_800173B4(void);
void func_80038894(void);
void func_8003450C(void);
void func_80037F60(void);
void func_8005DCB4(void);
void func_800238B4(void);
void func_80023144(void);
void func_80027678(void);
void func_800175FC(void);
void func_80028DE0(void);
void Map_screen_init(void);
sint32 Map_screen_task(void);

void func_8001D854(sint32 arg);
sint32 func_8001A0A8(sint32 arg);
void func_80016DAC(void);
void func_80016E90(void);
void func_80016D0C(GAME_WORK *wp);
void func_80016D38(GAME_WORK *wp);
void func_80016434(sint32 mode);
void func_80019D18(void);
void func_8003A744(void);
void func_801D8130(void);
sint32 func_801D816C(void);

void func_8001D990(void);
void func_80063C30(void);
void func_80039D38(GAME_DELTA *delta);
void Obj_work_flag_change(sint32 mask, sint32 flags);
void func_8002F420(sint32 flag, GAME_DELTA *delta);
void func_80019C20(void);
void func_8003B140(void);

// Game_work by its fixed address: GCC 2.7 rebuilds a literal address with lui at each
// access instead of keeping the symbol's address in a register (func_80019D18).
#define GAME_WORK_PTR ((GAME_WORK *)0x800C1B10)

#endif
