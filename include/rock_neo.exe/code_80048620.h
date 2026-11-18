#ifndef ROCK_NEO_CODE_80048620_H
#define ROCK_NEO_CODE_80048620_H

#include "player.h"

// Scratchpad fields used by the collision-map helpers.
#define CODE486_MAP_X0     (*(uint8 *)0x1F800040)
#define CODE486_MAP_Z0     (*(uint8 *)0x1F800041)
#define CODE486_MAP_W      (*(uint16 *)0x1F800044)
#define CODE486_MAP_H      (*(uint16 *)0x1F800046)
#define CODE486_MAP_CELLS  (*(sint16 **)0x1F800048)
#define CODE486_MAP_TBL    ((CODE486_MAP *)0x80164004)
#define CODE486_MAP_INFO   (*(CODE486_CELL **)0x1F80004C)
#define CODE486_SP_D0      (*(sint16 *)0x1F8000D0)
#define CODE486_SP_C0      (*(uint16 *)0x1F8000C0)
#define CODE486_SP_C0      (*(uint16 *)0x1F8000C0)
#define CODE486_SP_C2      (*(uint16 *)0x1F8000C2)
#define CODE486_SP_C4      (*(uint16 *)0x1F8000C4)
#define CODE486_SP_CLIP_C0 (*(sint16 *)0x1F8000C0)
#define CODE486_SP_CLIP_C4 (*(sint16 *)0x1F8000C4)
#define CODE486_SP_F0      (*(sint16 *)0x1F8000F0)
#define CODE486_SP_F4      (*(sint16 *)0x1F8000F4)
#define CODE486_SP_F8      (*(sint16 *)0x1F8000F8)
#define CODE486_SP_FC      (*(sint16 *)0x1F8000FC)
#define CODE486_SP_OFS124  (*(uint16 *)0x1F800124)
#define CODE486_SP_OFS126  (*(uint16 *)0x1F800126)
#define CODE486_SP_OFS128  (*(uint16 *)0x1F800128)
#define CODE486_SP_OFS12A  (*(uint16 *)0x1F80012A)
#define CODE486_SP_F2      (*(uint16 *)0x1F8000F2)
#define CODE486_SP_FA      (*(uint16 *)0x1F8000FA)
#define CODE486_SP_102     (*(sint16 *)0x1F800102)
#define CODE486_SP_D2      (*(sint16 *)0x1F8000D2)
#define CODE486_SP_D4      (*(sint16 *)0x1F8000D4)
#define CODE486_MOVE_FLAGS (*(uint8 *)0x1F8000FF)
typedef struct
{
    sint32 a, b, c;
} CODE486_OFS;
#define CODE486_SP_OFS (*(CODE486_OFS *)0x1F800124)
// The same offsets as halfwords; as struct fields GCC keeps their loads after the stores
// through a rect pointer.
typedef struct
{
    uint16 h124, h126, h128, h12a;
    uint16 h12c, h12e; // As fields, their loads keep the constant address (lui/lhu) inside
                       // a loop; the scalar macros load it into a register loop.c can hoist.
} CODE486_OFSH4;
#define CODE486_SP_OFSH4 (*(CODE486_OFSH4 *)0x1F800124)
#define CODE486_SP_F6    (*(sint8 *)0x1F8000F6)
#define CODE486_SP_F7    (*(sint8 *)0x1F8000F7)
#define CODE486_ABS(x)   ((x) >= 0 ? (x) : -(x))
// The same with the negative test first; GCC 2.7 reserves no stack temporary for it.
#define CODE486_ABS_NEG(x)    ((x) < 0 ? -(x) : (x))
#define CODE486_SOLID_AT(key) ((CODE486_SOLID *)(key))

typedef struct CODE486_PROP CODE486_PROP;

// Collision request: the registering object (a prop for kinds 4-7), kind, index, argument.
typedef struct
{
    union
    {
        PL_WORK *pl;
        CODE486_PROP *prop;
    } obj;
    sint16 value4, value6;
    uint32 value8;
} CODE486_REQ;

// Collision map cell record (12 bytes): origin, flags, 24-bit pointer to its solids.
typedef struct
{
    sint16 x, y, z;
    uint16 flags6;
    uint32 value8;
} CODE486_CELL;

// Collision map headers (8 bytes each, from 0x80164004).
typedef struct
{
    uint8 x0, z0, w, h;
    sint16 *cells;
} CODE486_MAP;

extern CODE486_REQ D_800BC058[];
extern PL_WORK *D_800BC360[];
extern CODE486_REQ *D_80098894;
extern PL_WORK **D_80098898;

void func_80042314(PL_WORK *pl);
void func_80039820(void);
void Sce_flag_off(sint32 flag);
uint32 func_8002FE74(uint32 id);
sint32 func_800497CC(PL_SHORT_VECTOR *pos, PL_HEIGHT_INFO *info, sint32 dir, sint32 kind);
extern uint8 D_800A395C;
extern uint8 D_8008AA04[];
extern uint16 D_800C0F96[];
#define CODE486_GAME_BYTE50 (*(sint8 *)(Game_work + 0x50))

typedef struct
{
    uint8 reserved00[0x76];
    sint8 value76;
    uint8 reserved77[0x49];
    uint32 value_c0;
} CODE486_LINK;

typedef struct
{
    CODE486_LINK link;
    uint8 reserved[0x5F4 - 0xC4];
} PL_WORK5F4;

typedef struct
{
    CODE486_LINK link;
    uint8 reserved[0x3C0 - 0xC4];
} PL_WORK3C0;

typedef struct
{
    CODE486_LINK link;
    uint8 reserved[0x5A4 - 0xC4];
} PL_WORK5A4;

typedef struct
{
    CODE486_LINK link;
    uint8 reserved[0x10C - 0xC4];
} PL_WORK10C;

extern uint32 D_8009888C;
extern uint32 D_800987E8;
extern uint32 D_80098B20;
extern uint32 D_800987CC;
extern PL_WORK3C0 D_8009F108[];
extern PL_WORK5A4 D_800C3580[];
extern PL_WORK10C D_8009CF88[];
void func_80052644(sint32 key, CODE486_LINK *link);
extern uint32 D_8008A9D4[];
extern uint8 D_8008A9F4[];
// Current room-entry handler (scene.c sees it as a pointer); a one-element array here.
extern uint32 D_800BC7F0[1];
// Room-entry request at D_800C3558: where the player left, where to arrive.
typedef struct
{
    union
    {
        PL_BYTES8 b8;
        PL_SHORT_VECTOR v;
    } from;
    union
    {
        PL_BYTES8 b8;
        PL_SHORT_VECTOR v;
    } dest;
    sint16 rot_from;
    sint16 rot;
    sint8 flags14;
    sint8 flags15;
    uint8 stage, room;
    uint8 fade_in, fade_out;
    uint8 reserved1a[0xE];
} CODE486_ENTRY;
// Its size (over 32 bytes) keeps it out of $gp in this -G32 file.
extern CODE486_ENTRY D_800C3558;
#define CODE486_ENTRY_H(entry, off) (*(sint16 *)((entry) + (off)))
extern uint32 D_8008A9E4[];
void Obj_work_flag_change(sint32 mask, sint32 flags);
sint32 func_80042238(PL_WORK *pl);

typedef struct
{
    uint8 reserved00[4];
    uint8 routine_0;
    uint8 routine_1;
    uint8 reserved06[4];
    uint8 value0a;
    uint8 value0b;
    uint32 value0c;
    sint32 value10;
    uint8 reserved14[0x90];
    uint8 *value_a4;
} CODE486_TASK;
extern uint8 Game_work[];
#define CODE486_GAME_BYTE52 (*(sint8 *)(Game_work + 0x52))
void Sce_flag_on(sint32 flag);
void func_8001DDE4(sint32 id);
uint32 Sce_flag_test(uint32 flag);
void func_80063BC8(sint32 a0, sint32 a1, sint32 a2, sint32 a3);

void func_8004B3C0(sint32 *arg);
void func_80048A9C(CODE486_TASK *task);
void func_8001E6C0(sint32 a0, sint32 a1, sint32 a2);
void func_8001EC0C(void);
void func_8001F070(void);
sint32 rsin(sint32 angle);
sint32 rcos(sint32 angle);
extern sint8 D_800C356C;
extern uint8 D_800C3570;
extern uint8 D_800C3571;
sint32 func_8004B6AC(PL_SHORT_VECTOR *out, PL_SHORT_VECTOR *in, sint32 arg2, sint32 arg3);
sint32 func_80052674(PL_WORK *pl, sint32 a0, PL_FIXED_VECTOR *pos, sint32 a3, sint32 slide);
void func_800534E0(sint32 a0, PL_WORK *pl, PL_FIXED_VECTOR *a2, PL_FIXED_VECTOR *a3,
                   PL_FIXED_VECTOR *a4, PL_FIXED_VECTOR *a5);
sint32 func_80052B04(sint32 a0, PL_FIXED_VECTOR *a1, PL_FIXED_VECTOR *a2, PL_FIXED_VECTOR *a3,
                     sint32 a4, sint32 slide);
void func_80030150(PL_FIXED_VECTOR *fixed, PL_SHORT_VECTOR *pos);
void func_800536B0(PL_WORK *pl, PL_FIXED_VECTOR *pos, PL_FIXED_VECTOR *prev, sint32 index);
sint32 func_80048CEC(sint32 index);
sint32 func_80048BEC(PL_SHORT_VECTOR *pos);
sint32 func_80048C60(PL_SHORT_VECTOR *pos);
sint32 func_80049470(PL_SHORT_VECTOR *pos, PL_HEIGHT_INFO *info, sint32 kind);
sint32 func_80049C54(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, PL_HEIGHT_INFO *info,
                     sint32 kind);
sint32 func_80048EA4(PL_SHORT_VECTOR *pos, PL_HEIGHT_INFO *info, sint32 dy, sint32 kind);

// Moving-platform object that the player rides (pl->value_c0).
typedef struct
{
    uint8 reserved00;
    uint8 value01;
    uint8 reserved02[0x1A];
    PL_FIXED_VECTOR origin;
    uint8 reserved2C[8];
    PL_FIXED_VECTOR pivot;
    uint8 reserved44[0x10];
    union
    {
        uint32 word;
        PL_SHORT_VECTOR vec;
    } rot;
    PL_SHORT_VECTOR rot_inv;
} CODE486_PLAT;

typedef struct
{
    sint16 vx, vy, vz, pad;
} CODE486_SVECTOR;

// Local view of a GTE rotation matrix (0x20 bytes).
typedef struct
{
    sint16 m[3][3];
    sint16 pad12;
    sint32 t[3];
} CODE486_MTX;

void RotMatrix(CODE486_SVECTOR *r, CODE486_MTX *m);
void RotMatrixYXZ(CODE486_SVECTOR *r, CODE486_MTX *m);
#define CODE486_PLAT_AT(a) (*(CODE486_PLAT *)(a))
void func_800301A8(CODE486_MTX *mtx, PL_FIXED_VECTOR *pos, PL_FIXED_VECTOR *origin);

// Solid-object collision: a list of x/z areas (ended by a null hit list), each with
// height ranges.
typedef struct
{
    sint16 y0, y1;
    uint16 kind;
    uint16 pad;
} CODE486_HIT;

typedef struct
{
    sint16 x0, x1, z0, z1;
    CODE486_HIT *hits;
    sint32 count;
} CODE486_AREA;

// Solid object as the collision routines see it: an object work prefix plus its area list.
typedef struct
{
    uint8 reserved00[0x14];
    PL_SHORT_VECTOR position;
    PL_FIXED_VECTOR position_fixed;
    PL_SHORT_VECTOR position_prev;
    PL_FIXED_VECTOR position_fixed_prev;
    sint16 value44, value46, value48;
    uint8 reserved4A[0xA];
    CODE486_SVECTOR rot;
    uint8 reserved5C[0x1C];
    PL_HEIGHT_INFO *info78;
    uint8 reserved7C[0xC];
    CODE486_AREA **areas;
} CODE486_SOLID;

// Static prop registered for collision (request kinds 4-7).
struct CODE486_PROP
{
    uint8 reserved00[0x14];
    CODE486_AREA **areas;
    uint8 reserved18[0x20];
    sint16 x, y, z;
    uint8 reserved3E[6];
    PL_HEIGHT_INFO *info;
};

// Stand-in solid that props are copied into before the shared tests run.
extern CODE486_SOLID D_8009A770;
sint32 func_80051F08(sint32 key, PL_WORK *pl, PL_WORK *obj, sint32 index, uint32 value8,
                     sint32 flag);
sint32 func_80052970(sint32 arg0, PL_WORK *pl, sint32 index, sint32 arg3);

typedef sint32 (*CODE486_TEST_FUNC)(sint16 *box, uint16 kind);
// The same tests called with the box alone (func_800514FC leaves a1 unset).
typedef sint32 (*CODE486_BOX_TEST_FUNC)(sint16 *box);

#define CODE486_SP_POS_C0 ((PL_SHORT_VECTOR *)0x1F8000C0)
#define CODE486_SP_POS_E0 ((PL_SHORT_VECTOR *)0x1F8000E0)
#define CODE486_SP_POS_C8 ((PL_SHORT_VECTOR *)0x1F8000C8)
// Movement delta C0 - C8 (D0/D2/D4) written as one vector; the scalar CODE486_SP_D2 reads
// it back without sharing the store's address register.
#define CODE486_SP_POS_D0 ((PL_SHORT_VECTOR *)0x1F8000D0)
#define CODE486_SP_PUSH   ((sint16 *)0x1F800100)
#define CODE486_SP_D0     (*(sint16 *)0x1F8000D0)
#define CODE486_SP_C8     (*(sint16 *)0x1F8000C8)
#define CODE486_SP_OFSH   ((uint16 *)0x1F800124)
// The same three offset words as plain scalars (GCC 2.7 lets a load through a struct
// pointer move above these stores, unlike the CODE486_SP_OFS fields).
#define CODE486_SP_OFS_A (*(sint32 *)0x1F800124)
#define CODE486_SP_OFS_B (*(sint32 *)0x1F800128)
#define CODE486_SP_OFS_C (*(sint32 *)0x1F80012C)
#define CODE486_SP_CC    (*(sint16 *)0x1F8000CC)
#define CODE486_SP_D4    (*(sint16 *)0x1F8000D4)
#define CODE486_SP_D8    (*(sint16 *)0x1F8000D8)
#define CODE486_SP_DA    (*(sint16 *)0x1F8000DA)
#define CODE486_SP_DC    (*(sint16 *)0x1F8000DC)

extern CODE486_TEST_FUNC D_8008AA24[];

// A cell's two area lists (picked by the cell flags), reached through value8's low 24 bits.
typedef struct
{
    uint32 reserved0;
    CODE486_AREA *areas_a;
    CODE486_AREA *areas_b;
} CODE486_CELL_SOLID;

#define CODE486_SP_CELLS ((sint16 *)0x1F800118)
#define CODE486_SP_12E   (*(sint16 *)0x1F80012E)
#define CODE486_SP_FE    (*(sint8 *)0x1F8000FE)
#define CODE486_SP_12C   (*(sint16 *)0x1F80012C)
sint32 func_8004B1E0(PL_SHORT_VECTOR *pos, sint32 keep_empty);

// Event trigger found in front of an object.
typedef struct
{
    sint16 x, y, z;
    sint16 rot;
    uint16 kind;
    uint16 flags;
} CODE486_EVENT;

void RotMatrixY(sint32 angle, CODE486_MTX *m);
void ApplyMatrixSV(CODE486_MTX *m, CODE486_SVECTOR *v, CODE486_SVECTOR *out);
extern PL_FIXED_VECTOR D_80098AC0;
void func_8004A060(sint16 *box, uint16 kind);
sint32 func_8004BDC8(sint16 *box, uint16 kind, sint32 test);

typedef union
{
    PL_BYTES8 b8;
    PL_SHORT_VECTOR v;
} PL_SHORT_BYTES;

// The real arguments are (step, dx, adx, vec); the callees only read step.
void func_80050B74();
void func_80050BB4();
sint32 func_80050A24(PL_SHORT_VECTOR *vec);
sint32 func_80050A90(PL_SHORT_VECTOR *vec);
sint32 func_80050AFC(PL_SHORT_VECTOR *vec);
sint32 func_80050BF4(PL_SHORT_VECTOR *vec);
sint32 func_80050808(PL_SHORT_VECTOR *vec);
sint32 func_800508BC(PL_SHORT_VECTOR *vec);
sint32 func_80050970(PL_SHORT_VECTOR *vec);
sint32 func_80050B68(PL_SHORT_VECTOR *vec);
sint32 func_80050400(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 mode);

// The scratchpad offsets as signed halfwords plus the two adjustments after them, as one
// struct so GCC keeps the adjustment loads after the box stores (func_8004A060).
typedef struct
{
    sint16 h124, h126, h128, h12a;
    uint16 h12c, h12e;
} CODE486_OFSH6;
#define CODE486_SP_OFSH6 (*(CODE486_OFSH6 *)0x1F800124)

// Scratchpad fields read by the box tests (func_8004BDC8).
#define CODE486_SP_POS_F0 ((PL_SHORT_VECTOR *)0x1F8000F0)
#define CODE486_SP_POS_F8 ((PL_SHORT_VECTOR *)0x1F8000F8)
#define CODE486_SP_F6W    (*(sint16 *)0x1F8000F6)
#define CODE486_SP_FF     (*(sint8 *)0x1F8000FF)
#define CODE486_SP_106    (*(uint16 *)0x1F800106)
#define CODE486_SP_108    (*(uint16 *)0x1F800108)
#define CODE486_SP_10A    (*(uint16 *)0x1F80010A)
#define CODE486_SP_112    (*(uint16 *)0x1F800112)
#define CODE486_SP_116    (*(uint16 *)0x1F800116)
#define CODE486_SP_H124   (*(sint16 *)0x1F800124)
#define CODE486_SP_H126   (*(sint16 *)0x1F800126)
#define CODE486_SP_H128   (*(sint16 *)0x1F800128)
#define CODE486_SP_H12A   (*(sint16 *)0x1F80012A)
sint32 func_8004F44C(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 mode);
sint32 func_8004F8BC(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 side);
sint32 func_8004FBE8(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 side);
sint32 func_8004FF14(PL_SHORT_VECTOR *pos, sint32 corner);
sint32 func_800501E8(PL_SHORT_VECTOR *pos, sint32 corner);

// Room-exit record (0x18 bytes) in the list at *0x1F800050, ended by id -1.
typedef struct
{
    sint16 id;
    sint16 value2;
    sint16 value4;
    uint8 stage, room;
    sint16 x, y, z, rot;
    union
    {
        PL_BYTES8 b8;
        PL_SHORT_VECTOR v;
    } dest;
} CODE486_EXIT;
#define CODE486_EXIT_LIST (*(CODE486_EXIT **)0x1F800050)

extern uint8 D_8008AA44[];
extern uint8 D_8008AA50[];
extern uint8 D_8008AA58[];
extern uint8 D_8008AA60[];
extern uint8 D_8008AA68[];
extern uint8 D_8008AA6C[];
extern uint8 D_8008AA70[];
#define CODE486_GAME_WORD174 (*(uint32 *)(Game_work + 0x174))
#define CODE486_GAME_HALF17A (*(uint16 *)(Game_work + 0x17A))
sint32 func_800514FC(PL_WORK *pl, sint32 *ofs, CODE486_EVENT *out);
sint32 func_80051970(PL_WORK *pl);
sint32 func_800519E4(CODE486_EXIT *exit);
sint32 func_80051A78(CODE486_EXIT *exit);
void func_8001F6C4(void);

#endif
