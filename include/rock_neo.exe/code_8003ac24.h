#ifndef CODE_8003AC24_H
#define CODE_8003AC24_H

#include "common.h"

// Entry of the 12-byte slot table whose first word is D_8015C008
typedef struct
{
    uint32 v;
    uint32 reserved04;
    uint16 reserved08;
    sint16 h0A;
} C8003AC24_SLOT;

#define C8003AC24_SLOTS ((C8003AC24_SLOT *)0x8015C008)
extern uint32 D_8013A004;
extern C8003AC24_SLOT D_8015C008[];
// Same table viewed two bytes earlier: the halfword before each slot
typedef struct
{
    uint16 h;
    uint16 reserved02[5];
} C8003AC24_PREV;
extern C8003AC24_PREV D_8015C006[];
#define C8003AC24_PREV_SLOTS ((C8003AC24_PREV *)0x8015C006)
// The same table as whole 12-byte records from 0x8015C000 (D_8015C006 is the first record's
// halfword, D_8015C008 its word). With nonzero field offsets the literal-address loads expand
// as lui at / addu at,reg,at, as retail does.
typedef struct
{
    uint32 reserved00;
    uint16 reserved04;
    uint16 h06;
    uint32 v08;
} C8003AC24_ENTRY;
#define C8003AC24_ENTRIES ((C8003AC24_ENTRY *)0x8015C000)
extern sint8 D_80089F04[];
extern uint32 D_800BD3B8[][0x80];

extern uint8 Game_work[];
#define C8003AC24_GAME_ROW (*(sint8 *)(Game_work + 0x50))

sint32 func_8003B2D4(sint32 row, sint32 bit);
sint32 func_8003B360(sint32 bit);
sint32 func_8003B420(sint32 bit);
sint32 func_8003B4BC(sint32 row, sint32 bit);
void func_8003BD0C(uint32 *out, uint32 key);
extern uint32 D_80089F7C;
extern uint32 D_80089F80;
extern uint32 D_80089F84;
extern uint32 D_80089F88;
extern uint32 D_80089F8C;
extern uint32 D_80089F90;

void func_8003BC44(void);
void Sce_flag_on(sint32 flag);
void Sce_flag_off(sint32 flag);
void func_8003B8B0(uint32 *remain, uint32 amount, uint32 key, sint32 row, sint32 flag);
extern uint8 D_80097D74[][7];
void func_8003BA58(uint32 *remain, uint32 amount, uint32 key, sint32 unused);
extern uint32 D_80089F64;
extern uint32 D_80089F68;
extern uint32 D_80089F6C;
extern uint32 D_80089F70;
extern uint32 D_80089F74;
extern uint32 D_80089F78;
#define C8003AC24_GAME32(off) (*(uint32 *)(Game_work + (off)))
#define C8003AC24_GAME_FLAG64 (*(uint16 *)(Game_work + 0x64))
extern uint32 D_80089F24[2][2][4];
extern sint16 D_8015D554;
extern sint16 D_8015D556;
extern sint16 D_8015D558;
extern sint16 D_8015D7A0;
extern sint16 D_8015D7A2;
extern sint16 D_8015D7A4;
extern uint32 D_800B6230[];
void func_800176DC(void *src, void *dst, sint32 count);
void func_8003B5B4(void);
uint32 func_8003AC24(uint32 key);
uint32 func_8003AC9C(sint32 idx, uint32 key);
void func_8003ACF4(sint32 idx, uint32 val);
sint32 func_8003B540(sint32 a0, sint32 bit, uint32 val);
void func_8003BDC0(uint8 *count, uint32 a1, uint32 a2);
void func_8003BE38(void);

#endif // CODE_8003AC24_H
