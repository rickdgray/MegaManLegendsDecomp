#ifndef CODE_800425FC_H
#define CODE_800425FC_H

#include "common.h"

// Local view of a work record with two state bytes at +0x170 and +0x171
typedef struct
{
    uint8 reserved00[0x170];
    sint8 routine_170;
    sint8 routine_171;
} C800425FC_WORK;

// Same record seen as two 16-halfword colour banks at +0x124 and +0x144
typedef struct
{
    uint8 reserved00[0x124];
    uint16 src[16];
    uint16 out[16];
} C800425FC_COLORS;

typedef struct
{
    uint8 reserved00[6];
    sint16 h06;
} C800425FC_PART;

// Local view of the actor fields touched by the routines in this file
typedef struct
{
    uint8 reserved00[9];
    uint8 b009;
    uint8 reserved0a[0x3A];
    union
    {
        uint16 u;
        sint16 s;
    } h44;
    uint8 reserved46[0x2E];
    sint8 s074;
    uint8 reserved75[0x37];
    uint8 b0ac;
    uint8 reserved0ad[0x53];
    uint8 b100;
    uint8 reserved101[2];
    sint8 s103;
    uint8 b104;
    uint8 reserved105[0xB];
    sint8 b110;
    uint8 reserved111[0xB];
    uint16 h11c;
    uint8 reserved11e[0x1C];
    uint16 h13a;
    uint16 h13c;
    uint8 reserved13e[0x32];
    sint8 routine_170;
    sint8 routine_171;
    uint8 reserved172[2];
    uint8 b174;
    uint8 b175;
    uint8 reserved176;
    uint8 b177;
    uint8 b178;
    uint8 reserved179[0x1F];
    uint32 w198;
    uint8 reserved19c[0x2B0];
    sint8 s44c;
    uint8 reserved44d[0xA7];
    C800425FC_PART parts[16];
} C800425FC_ACT;

extern uint8 D_80089A84[];
extern uint8 Game_work[];
void func_80041E90(C800425FC_ACT *ap, sint32 b, sint32 c, sint32 d);
void func_80042A40(C800425FC_ACT *ap);
void func_80042DF8(C800425FC_ACT *ap);
extern uint8 D_80089A85[];
extern uint8 D_80089A86[];
extern uint8 D_80089A87[];

// Defined with the player's work type elsewhere; declared without parameters here.
void func_800320B8();
void func_800321C8();
sint32 func_80037664();
void Pl00_shot_enable_off();
uint8 func_80042458(C800425FC_ACT *ap);
uint8 func_800423DC(C800425FC_ACT *ap);

extern uint16 D_8008A04C[][16];

void func_800425FC(C800425FC_COLORS *wp, sint32 idx);

typedef void (*C800425FC_FUNC)(C800425FC_WORK *wp);

extern C800425FC_FUNC D_8008A08C[];
extern C800425FC_FUNC D_8008A0C4[];

void func_800426F8(C800425FC_WORK *wp);
void func_80042734(C800425FC_WORK *wp);

#endif // CODE_800425FC_H
