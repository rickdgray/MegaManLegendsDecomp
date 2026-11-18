#ifndef ROCK_NEO_CODE_8005C258_H
#define ROCK_NEO_CODE_8005C258_H

#include "common.h"
#include "player.h"
#include "psyq/libgpu.h"

// Repeat counter record: byte at +0xF counts frames.
typedef struct
{
    uint8 reserved00[0xF];
    uint8 count_0F;
} CODE5C_REPEAT;

// Idle watcher record.
typedef struct
{
    uint8 reserved00[0xA];
    uint8 idle_0A;
    uint8 still_0B;
    uint8 active_0C;
    uint8 mode_0D;
    uint8 reserved0E;
    uint8 done_0F;
    uint8 reserved10[8];
    uint16 count_18;
} CODE5C_WATCH;

typedef struct
{
    uint16 x, y, w, h;
} CODE5C_RECT;

// Gradient band: four corner colour words.
typedef struct
{
    uint32 color[4];
} CODE5C_COLOR;

// Sprite definition used by the quad drawers.
typedef struct
{
    uint32 color;
    sint16 x_off, y_off;
    sint16 width, height;
    uint8 u, v;
    uint16 clut;
    uint8 reserved10[2];
    uint16 tpage;
} CODE5C_SPRITE;

// Effect slot (0x24 bytes). D_800BBD78 holds five of them; the banked helpers above
// still reach slot 0's bytes through separate symbols (D_800BBD81, D_800BBD84, ...).
typedef struct
{
    sint8 active_00;
    uint8 reserved01[7];
    sint8 anim_08;
    sint8 timer_09;
    uint8 reserved0A[2];
    uint8 byte_0C;
    uint8 byte_0D;
    uint8 byte_0E;
    uint8 reserved0F;
    sint32 word_10;
    sint16 x_14;
    sint16 y_16;
    sint16 x_18;
    sint16 y_1A;
    uint8 reserved1C[4];
    PL_WORK *owner_20;
} CODE5C_SLOT;

// Stage/room map record (12 bytes, 0xFF-terminated): map size in cells, the
// visited-cell bitmap, and the room origin.
typedef struct
{
    uint8 stage;
    uint8 room;
    uint8 width;
    uint8 height;
    sint32 value;
    sint16 x;
    sint16 z;
} CODE5C_ROOM;

typedef struct
{
    sint16 x, y;
} CODE5C_POINT;

// Neighbour-cell offsets (3x3), copied to the stack as one 9-byte block.
typedef struct
{
    sint8 v[9];
} CODE5C_OFS9;

// Dispatch record: only the routine byte at +4 is used here.
typedef struct
{
    uint8 reserved00[4];
    uint8 routine_4;
} CODE5C_WORK;

typedef void (*CODE5C_FUNC)(CODE5C_WORK *wp);

// Words that are also touched through a narrower access.
typedef union
{
    uint32 word;
    uint8 byte;
} CODE5C_WORD_BYTE;

typedef union
{
    uint32 word;
    uint16 half;
} CODE5C_WORD_HALF;

extern CODE5C_COLOR D_8009806C[2];

extern CODE5C_FUNC D_8008D7B4[];
extern CODE5C_FUNC D_8008D7C0[];
extern CODE5C_FUNC D_8008D7C4[];

extern uint32 D_800A38F0;
extern uint8 D_800A38F8;
extern uint8 D_800A38F9;
extern uint8 D_800A38FA;
extern uint8 D_800A38FB;
extern uint8 D_800BBD81;
extern uint8 D_800BBD82;
extern uint8 D_800BBD83;
extern uint8 D_800BBD84[];
extern uint8 D_800BBD85;
extern uint16 D_800BBD90;
extern sint16 D_800BBD94;
extern sint16 D_800BBD96;
extern uint8 D_800BBDAB;
extern CODE5C_WORD_BYTE D_800BBE2C;
extern uint32 D_800BBE30;
extern uint32 D_800BBE34;
extern CODE5C_WORD_BYTE D_800BBE38;
extern uint8 D_800BBE39;
extern uint32 D_800BBE3C;
extern uint32 D_800BBE40;
extern CODE5C_WORD_HALF D_800BBE44;
extern sint16 D_800BBE46;
extern uint32 D_800BBE48;

extern uint8 D_800B7030;
extern CODE5C_ROOM D_8008D19C[];
// Map view clip rectangles, one per display buffer.
extern RECT D_80098050[];
extern sint32 D_80098008;
extern sint32 D_80098014;
extern sint32 D_80098018;
extern sint32 D_80098034;
extern sint32 D_8009800C;
extern sint32 D_8009801C;
extern sint16 D_800986F8;
extern sint16 D_800986FC;
extern sint32 D_8009878C;
extern sint32 D_80098794;
extern sint32 D_8009882C;
extern sint32 D_80098AF0;
extern sint32 D_80098B18;
extern CODE5C_SPRITE D_8008D750[5];
extern CODE5C_SPRITE D_8008D688[][5];
extern CODE5C_SPRITE D_8008D37C[][5];
extern CODE5C_SPRITE D_8008D570[];
extern CODE5C_SPRITE D_8008D5E8;
extern CODE5C_SPRITE D_8008D5FC;
extern uint8 D_8008D7C8[];
extern uint8 D_80098020[];
extern uint8 D_8009802C[];
extern CODE5C_SPRITE D_8008D610;
extern CODE5C_SPRITE D_8008D624;
extern CODE5C_SPRITE D_8008D638[2];
extern CODE5C_SPRITE D_8008D660;
extern CODE5C_SPRITE D_8008D674;
// Per-weapon gauge record (12 bytes); only the shift byte is read here.
typedef struct
{
    uint8 shift;
    uint8 reserved01[11];
} CODE5C_GAUGE;
extern CODE5C_GAUGE D_80089A8C[];
extern CODE5C_SLOT D_800BBD78[5];
// The weapon gauge slot after the five 0x24-byte slots (0x20 bytes; the banked helpers
// reach its words as D_800BBE2C...D_800BBE48).
#define CODE5C_GAUGE_SLOT (*(CODE5C_SLOT *)&D_800BBE2C)
// Word views of POLY_G4 and POLY_FT4 (colour, position and texture words written whole).
typedef struct
{
    u_long tag;
    u_long rgb0;
    u_long xy0;
    u_long rgb1;
    u_long xy1;
    u_long rgb2;
    u_long xy2;
    u_long rgb3;
    u_long xy3;
} CODE5C_G4_WORDS;

typedef struct
{
    u_long tag;
    u_long rgb0;
    u_long xy0;
    u_long uv0;
    u_long xy1;
    u_long uv1;
    u_long xy2;
    u_long uv2;
    u_long xy3;
    u_long uv3;
} CODE5C_FT4_WORDS;

// Next free primitive, in the scratchpad.
#define CODE5C_PRIM(type) (*(type **)0x1F800070)
extern sint32 D_80098010;
extern CODE5C_OFS9 D_80098038; // {-1, 0, 1, -1, 0, 1, -1, 0, 1}
extern CODE5C_OFS9 D_80098044; // {-1, -1, -1, 0, 0, 0, 1, 1, 1}
extern uint8 D_800BBD9C;
extern sint32 D_800BC9B8[0x280];

sint32 func_80037604(PL_WORK *wp, sint32 index);
// Hand-written 32-byte block copy in asm_fastmem.s.
void func_800176DC(void *src, void *dst, sint32 blocks);
void func_800177CC(void *start, void *end);
void func_8005D298(CODE5C_SPRITE *spr, sint16 x, sint16 y, uint16 size);
void func_8005D39C(CODE5C_SPRITE *spr, sint16 x, sint16 y, uint16 size, sint32 color);
void func_8005C720(CODE5C_WORK *wp);
void func_8005C868(CODE5C_WORK *wp);
void func_8005C978(CODE5C_WORK *wp);
void func_8005C9BC(CODE5C_SLOT *wp);
void func_8005CCF4(CODE5C_SLOT *wp);
void func_8005CEFC(CODE5C_SLOT *wp);
void func_8005D0FC(CODE5C_SLOT *wp);
void func_8005D4F8(void);
void func_8005D528(void);
void func_8005D9C4(void);
void func_8005DCDC(void);
void func_8005DE28(void);
void func_8005E144(CODE5C_POINT *pos, CODE5C_POINT *size, CODE5C_POINT *cell, CODE5C_RECT *rect);
void func_8005E9F8(CODE5C_RECT *rect);
void func_8005EAA8(CODE5C_RECT *rect);

#endif
