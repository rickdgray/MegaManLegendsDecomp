#ifndef ROCK_NEO_CODE_800680BC_H
#define ROCK_NEO_CODE_800680BC_H

#include "common.h"
#include "psyq/libgpu.h"
#include "player.h"

// Local views: only the fields these routines touch.
typedef struct
{
    sint8 flags_0;
    uint8 reserved01[8];
    uint8 routine_9;
    uint8 routine_a;
    uint8 reserved0b[2];
    sint8 value_d;
    sint8 value_e;
    uint8 reserved0f[0xD];
    sint32 word_1c;
    sint32 word_20;
    sint32 word_24;
    uint8 reserved28[0x2E];
    sint16 angle_56;
    uint8 reserved58[0x10B - 0x58];
    sint8 value_10b;
    uint8 reserved10c[0x117 - 0x10C];
    sint8 value_117;
    uint8 reserved118[0x143 - 0x118];
    sint8 value_143;
    uint8 reserved144[3];
    sint8 value_147;
    uint8 reserved148[3];
    sint8 value_14b;
    uint8 reserved14c[3];
    sint8 value_14f;
    uint8 reserved150[0x18E - 0x150];
    sint16 color_18e;
    uint8 reserved190[0x19E - 0x190];
    sint16 color_19e;
    uint8 reserved1a0[6];
    sint16 color_1a6;
    uint8 reserved1a8[0x1B6 - 0x1A8];
    sint16 color_1b6;
    uint8 reserved1b8[6];
    sint16 color_1be;
    uint8 reserved1c0[0x1FE - 0x1C0];
    sint16 color_1fe;
    uint8 reserved200[6];
    sint16 color_206;
    uint8 reserved208[6];
    sint16 color_20e;
    uint8 reserved210[6];
    sint16 color_216;
    uint8 reserved218[6];
    sint16 color_21e;
    uint8 reserved220[8];
} CODE68_CHILD;

// Flat rectangle primitive (TILE).
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    short w, h;
} CODE68_TILE;

// Ordering-table heads kept in the display link record.
typedef struct
{
    uint8 reserved00[0x74];
    uint32 tag74;
} CODE68_LINK;

#define CODE68_PACKET_PTR ((POLY_FT4 **)0x1F800070)

extern CODE68_LINK *D_80098934;

typedef struct CODE68_WORK CODE68_WORK;
typedef void (*CODE68_FUNC)(CODE68_WORK *wp);

struct CODE68_WORK
{
    uint8 flags_0;
    uint8 reserved01[3];
    uint8 routine_4;
    uint8 reserved05[3];
    uint8 routine_8;
    uint8 reserved09[3];
    sint32 word_c;
    sint32 timer_10;
    sint32 word_14;
    uint8 reserved18[0xC];
    CODE68_CHILD *child_24;
    CODE68_CHILD *child_28;
    CODE68_CHILD *child_2c;
    CODE68_CHILD *child_30;
    uint8 reserved34[0x30];
    uint32 word_64;
    uint32 word_68;
    uint32 word_6c;
    uint32 word_70;
    uint32 word_74;
    uint8 reserved78[0x2C];
    CODE68_FUNC *tbl_a4;
};

// Palette-fade slots: eight bytes apart, the color halfword at +0x186.
typedef struct
{
    uint8 reserved00[0x186];
    sint16 color_186;
} CODE68_PAL;

typedef struct
{
    uint8 reserved00[0x14];
} CODE68_ENTRY;

extern CODE68_ENTRY D_8008FF88[];
extern uint8 D_8008FFD8[];
extern CODE68_FUNC D_8009039C[];
extern uint8 *D_800BC7F0;

extern sint8 D_800C356C;
extern sint8 D_800C356D;
extern uint8 D_800C356E;
extern uint8 D_800C356F;
extern uint8 D_800C3570;
extern uint8 D_800C3571;
extern sint16 D_800C3560;
extern sint16 D_800C3562;
extern sint16 D_800C3564;
extern sint16 D_800C356A;
extern sint16 D_80098A72;

void func_800680BC(sint32 arg);
void func_80068508(CODE68_CHILD *child, sint32 index);
void func_80068120(sint32 r, sint32 g, sint32 b, uint16 tpage);
void func_80101D94(void);
void func_8001E6C0(sint32 a0, sint32 a1, sint32 a2);
void func_8001EAE8(CODE68_ENTRY *entry);
void func_80068CE0(CODE68_WORK *wp);
void func_80068D64(CODE68_WORK *wp);
void func_80068DA4(void);
void func_80017C30(sint32 arg);
void func_8001D494(sint32 arg0, sint32 arg1, sint32 arg2);
void func_8001D58C(uint32 arg);
uint32 func_8001D878(void);
void func_8001D974(void);
uint32 func_8001DE84(void);
void func_8001E390(sint32 arg);
void func_8001EC0C(void);
void func_8001F070(void);
sint32 func_80042238(PL_WORK *pl);
void func_80042314(PL_WORK *pl);
void Sce_flag_on(sint32 flag);

#endif
