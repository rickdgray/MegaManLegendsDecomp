#ifndef ROCK_NEO_PLAYER_H
#define ROCK_NEO_PLAYER_H

#include "common.h"

// Position/rotation snapshots used when entering a room.
typedef struct
{
    sint16 x, y, z, pad;
} PL_SHORT_VECTOR;

typedef struct
{
    sint32 x, y, z, pad;
} PL_FIXED_VECTOR;
typedef struct
{
    uint8 b[8];
} PL_BYTES8;

typedef struct
{
    uint8 value00;
    uint8 reserved01;
    uint8 value02, value03;
    uint8 reserved04[0x34];
    PL_BYTES8 value38;
} PL_CMD;

typedef struct
{
    sint8 current;
    sint8 selected;
    sint8 value02;
    sint8 value03;
    sint8 value04;
    uint8 reserved05;
    sint16 value06;
} PL_PART_STATE;

typedef struct
{
    sint16 value0, value2, value4, value6, value8;
    sint16 value0a;
} PL_HEIGHT_INFO;

typedef struct
{
    uint8 routine_0;
    uint8 reserved01;
    uint8 value02, value03;
    uint8 reserved04[0x18];
    PL_SHORT_VECTOR position;
} PL_EFFECT;

typedef struct
{
    uint16 mask_a, dir_a;
    uint16 mask_b, dir_b;
} PL_PAD_ENTRY;

typedef struct PL_WORK
{
    uint8 routine_0;
    uint8 value01;
    uint8 reserved02[4];
    uint8 flags06;
    uint8 reserved07;
    uint8 kind;
    uint8 routine_1;
    uint8 value0a;
    uint8 value0b;
    uint8 reservedC[0x8];
    PL_SHORT_VECTOR position;
    PL_FIXED_VECTOR position_fixed;
    PL_SHORT_VECTOR position_prev;
    PL_FIXED_VECTOR position_fixed_prev;
    sint16 value44, value46, value48;
    uint8 reserved4A[0x4];
    sint16 value4e;
    uint8 reserved50[0x4];
    PL_SHORT_VECTOR rotation;
    PL_SHORT_VECTOR rotation_prev;
    uint8 reserved64[0x8];
    sint16 value6c;
    sint16 value6e;
    uint8 reserved70;
    uint8 value71;
    uint8 reserved72;
    uint8 value73;
    sint8 value74;
    sint8 value75;
    sint8 value76;
    uint8 value77;
    PL_HEIGHT_INFO *info78;
    uint16 value7c;
    uint8 reserved7E[0x26];
    uint8 value_a4;
    uint8 reservedA5[0x1];
    sint8 value_a6;
    sint8 value_a7;
    uint8 reserveda8[4];
    uint8 value_ac;
    uint8 value_ad;
    uint8 reservedAE[0x4];
    uint16 value_b2;
    sint16 value_b4;
    sint16 value_b6;
    uint8 reservedb8[5];
    uint8 flags_bd;
    uint8 reservedbe[2];
    uint32 value_c0;
    uint32 value_c4;
    uint8 reservedc8[0x38];
    uint8 value100;
    uint8 reserved101[3];
    uint8 value104;
    uint8 value105;
    uint8 reserved106[0x2];
    sint16 value108;
    uint16 value10a;
    sint16 value10c;
    sint16 value10e;
    sint8 value110;
    uint8 value111;
    uint8 value112, value113;
    uint16 value114;
    uint16 value116;
    uint16 value118;
    uint8 reserved11A[0x2];
    uint16 pad_cur;
    uint16 value11e;
    uint16 value120;
    uint16 value122;
    uint16 value124;
    uint16 value126;
    uint16 value128, value12a;
    uint16 value12c, value12e;
    uint16 value130, value132;
    uint16 value134;
    uint16 value136;
    uint16 value138;
    uint16 value13a, value13c;
    uint16 value13e, value140;
    uint8 reserved142[0x2];
    PL_PAD_ENTRY pad_tbl[4];
    sint16 value164;
    uint8 reserved166[0x2];
    sint8 value168, value169;
    uint8 reserved16a;
    uint8 flags16b;
    uint8 reserved16c[4];
    sint8 value170, value171;
    sint8 part_index;
    uint8 reserved173;
    sint8 value174;
    uint8 value175, value176;
    sint8 value177;
    uint16 value178;
    uint8 reserved17a[0x6];
    PL_SHORT_VECTOR table180[1];
    uint32 value188, value18c, value190, value194;
    uint8 reserved198[0x210];
    PL_BYTES8 table3a8[16];
    PL_FIXED_VECTOR position_saved_fixed;
    PL_SHORT_VECTOR position_saved;
    PL_SHORT_VECTOR rotation_saved;
    uint8 value448;
    sint8 value449;
    uint8 value44a, value44b;
    uint8 reserved44C[0x1];
    uint8 value44d;
    uint8 reserved44E[0xA6];
    PL_PART_STATE parts[16];
    uint8 reserved574[0xE0];
} PL_WORK;

extern PL_WORK Player_work;
extern PL_WORK Player_work2;

#define PL_ABS(x) (((x) < 0) ? -(x) : (x))

// Position snapshots stored as 8-byte records in table3a8.
#define PL_TABLE_VEC(pl, i) ((PL_SHORT_VECTOR *)&(pl)->table3a8[i])
extern uint8 D_80089A84[];
// Weapon records, 12 bytes each; only the first byte (reload) is read through this symbol.
typedef struct
{
    uint8 reload;
    uint8 reserved01[0xB];
} PL_RELOAD_TBL;
extern PL_RELOAD_TBL D_80089A88[];
extern uint8 D_80089A89[];
extern uint8 D_80089A8A[];

// Local views of bytes inside Game_work.
#define PL_GAME_FLAG55 (*(sint8 *)((uint8 *)&Game_work + 0x55))
#define PL_GAME_FLAG56 (*(sint8 *)((uint8 *)&Game_work + 0x56))

void func_8003BE6C(PL_WORK *pl, sint32 arg);
sint32 func_80040764(PL_WORK *pl);
sint32 rand(void);
void func_8003F3E8(PL_WORK *pl);
void func_80041EF4(PL_WORK *pl, sint32 a1, sint32 a2);
void func_80041DDC(PL_WORK *pl, uint8 id, sint16 arg2, uint8 flag);
sint32 func_80042154(PL_WORK *pl, sint32 a1, sint32 a2, sint32 mask);
void Pl00_shot_enable_on(PL_WORK *pl);
sint32 func_80040B68(PL_WORK *pl, sint32 arg);
sint32 func_800402C4(PL_WORK *pl);
sint32 func_8004030C(PL_WORK *pl, sint32 arg);
void func_800394AC(void);
sint32 func_800406A8(PL_WORK *pl);
void func_80041A44(PL_WORK *pl, uint32 flags);
sint32 func_80040818(PL_WORK *pl);
sint32 func_80040710(PL_WORK *pl);
sint32 func_800404FC(PL_WORK *pl, sint32 arg);
sint32 func_80040630(PL_WORK *pl, sint32 arg);
void func_8002D004(PL_WORK *pl, sint32 a1, sint32 a2);
sint32 func_80040574(PL_WORK *pl);
sint32 func_800410D4(PL_WORK *pl);
sint32 func_80041158(PL_WORK *pl);
void func_80042314(PL_WORK *pl);
sint32 func_80041044(PL_WORK *pl);
sint32 func_800403D4(PL_WORK *pl, sint32 arg);
sint32 func_80040468(PL_WORK *pl, sint32 arg);
void func_8003F188(PL_WORK *pl, sint32 dir, sint32 arg);
sint32 func_80040E00(PL_WORK *pl, sint32 a1, sint16 a2, sint16 a3);
void func_80040E9C(PL_WORK *pl, sint16 arg);
sint32 func_80040FA8(PL_WORK *pl);
void func_80040178(PL_WORK *pl);
sint32 func_80048E6C(PL_WORK *pl);
typedef void (*PL_FUNC)(PL_WORK *pl);

extern PL_FUNC D_80089F94[];
void func_800321C8(PL_WORK *pl, sint32 a1, sint32 a2, sint32 a3);
void func_800323FC(PL_WORK *pl, sint32 a1, sint32 a2);
void func_800320B8(PL_WORK *pl, sint32 a1, sint32 a2);
void func_8003234C(); // signature differs between callers; see code_8002e7a8.h
uint32 func_8004324C(PL_WORK *pl);
sint32 func_8004B414(PL_WORK *pl);
sint32 func_80042044(PL_WORK *pl, sint32 a1, sint32 a2);
sint32 func_800341BC(void *pos, sint32 half, sint32 arg2, sint32 arg3, sint32 id, void *tbl,
                     uint32 flags, sint32 arg7, sint32 arg8);
void func_8003C4EC(PL_WORK *pl);
sint32 func_800411DC();
sint32 func_80040AEC(PL_WORK *pl);
sint32 func_800405F4(PL_WORK *pl);
sint32 func_80040380(PL_WORK *pl);
void func_800395E8(void);
void Pl00_shot_enable_off(PL_WORK *pl);
void func_80051BAC(PL_WORK *pl);
extern uint16 D_800C0C26, D_800C0C2A, D_800C0C2C, D_800C0C2E;
extern uint16 D_800C0F96[];
extern uint16 D_800C0F9A, D_800C0F9C, D_800C0F9E;
extern uint16 D_800C0FE6, D_800C0FEA, D_800C0FEC, D_800C0FEE;
void func_8003C418(PL_WORK *pl);
extern PL_FUNC D_80089FF8[];
extern PL_FUNC D_80089FA4[];
void func_8004174C(PL_WORK *pl);
void func_800426F8(PL_WORK *pl);
void func_80042734(PL_WORK *pl);
sint32 func_8004AF28(PL_SHORT_VECTOR *pos, uint16 a1, uint8 a2, uint8 a3);
sint32 func_80037440();
void func_80053158(PL_WORK *pl, uint32 arg);
void func_8005331C(PL_WORK *pl, uint32 arg);
sint32 func_80050C2C(PL_WORK *pl);
#ifdef __wasm32__
void func_800329D4(void *arg, sint32 unused);
#else
void func_800329D4(); // signature differs between callers; see code_8002e7a8.h
#endif
void func_800325D4(); // signature differs between callers; see code_8002e7a8.h
void Model_Shadow_Trans(PL_WORK *pl, sint32 a1, sint32 a2, sint32 a3);
extern uint8 D_80097D9C[];
void func_80039A38(void *data);
sint32 func_8004976C(PL_WORK *pl);
void func_80041E90(PL_WORK *pl, sint32 x, sint32 y, sint32 z);
void func_80041F54(PL_WORK *pl, sint32 a1, sint32 a2, uint16 mask);
sint32 func_800423DC(PL_WORK *pl);
sint32 func_80042458(PL_WORK *pl);
void func_800425FC(); // signature differs between callers
void func_80037534(PL_WORK *wp);
void func_80037594(void);
void func_800177CC(void *start, void *end);
extern uint32 D_8009888C;
extern PL_HEIGHT_INFO D_80097D90;
extern uint8 D_800B5DB0[]; // same as cd_local.h
// Generic effect allocator; CODE456_WORK is its full layout (code_800456d8.h).
struct CODE456_WORK *func_80031618(void);
void func_8003E068(PL_WORK *pl, sint32 index);
void func_8005D528(void);
void func_8003D124(PL_WORK *pl, sint32 dir);
void func_8003EE68(PL_WORK *pl);
sint32 func_80048EA4(); // signature differs between callers; see code_80048620.h
sint32 func_8005D8C4(sint32 arg);
void Swing_Camera2(); // takes a CAM_DELTA pointer; see code_80037fb4.h
void func_80042528(PL_WORK *pl, PL_EFFECT *fx, sint32 arg);
void func_80030150(); // signature differs between callers; see code_8002e7a8.h
// Hand-written copy entry in asm_fastmem.s; not in the symbol registry yet.
void func_800176DC(void *src, void *dst, sint32 count);

// Player_work by its fixed address: GCC 2.7 rebuilds a literal address with lui at
// each access instead of keeping the symbol's address in a register (func_80016528).
#define PLAYER_WORK_PTR ((PL_WORK *)0x800B51B0)

// 3x3 rotation plus translation, PsyQ MATRIX layout.
typedef struct
{
    sint16 m[3][3];
    sint16 pad;
    sint32 t[3];
} PL_MATRIX;

// Collision box extents: x0..x1, z0..z1, then y0..y1.
typedef struct
{
    sint16 x0, x1;
    sint16 z0, z1;
    sint16 y0, y1;
} PL_BOUNDS;

void RotMatrixYXZ();  // argument types differ between callers
void func_800301A8(); // signature differs between callers; see code_8002e7a8.h
sint32 func_80030374(sint16 *a, sint16 *b);

extern sint32 D_80097D08; // same as code_8002e7a8.h
extern sint32 D_80098B18; // same as code_8005c258.h

// Common head of the 0x3C0, 0x5A4 and 0x10C entity records as the lock-on search
// (func_800411DC) reads it: collision bounds, then position and rotation.
typedef struct
{
    sint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 reserved03[0xD];
    PL_BOUNDS *bounds;
    PL_SHORT_VECTOR position;
    uint8 reserved1C[0x38];
    PL_SHORT_VECTOR rotation;
} PL_TARGET;

// The 0x50-byte records: bounds and two candidate positions.
typedef struct
{
    sint8 flags;
    uint8 reserved01[0xF];
    PL_BOUNDS *bounds;
    uint8 reserved14[0x8];
    sint16 x1c, y1e, z20;
    uint8 reserved22[0x16];
    sint16 x38, y3a, z3c;
    uint8 reserved3E[0x12];
} PL_TARGET50;

sint32 rsin(sint32 angle);
sint32 rcos(sint32 angle);
sint32 func_800414F0(PL_WORK *pl, PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *rot, PL_BOUNDS *box);

#endif
