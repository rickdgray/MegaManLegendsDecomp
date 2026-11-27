#ifndef SHL_H
#define SHL_H

#include "common.h"
#include "psyq/libgte.h"

// Shared by the special-weapon (SHL) modules r3_shl02 ... r3_shl0d, each loaded at 0x800D8800
// when its weapon is equipped. ROCK_NEO.EXE's SHL table (0x80089A28) points every weapon at the
// module's first function (0x800D8804), which runs one shot object per call: it dispatches on
// routine_0 through the module's own table.

// A 16.16 fixed-point position; the halfword view reads the integer parts.
typedef union
{
    struct
    {
        sint32 x, y, z, pad;
    } w;
    struct
    {
        uint16 x_lo;
        sint16 x;
        uint16 y_lo;
        sint16 y;
        uint16 z_lo;
        sint16 z;
        uint16 pad_lo;
        sint16 pad;
    } h;
} SHL_FIXED;

// A collision box, as offsets from the object's position.
typedef struct
{
    sint16 x0, x1, z0, z1, y0, y1;
} SHL_BOX;

// Draw description of a sprite (billboard) shot.
typedef struct
{
    uint32 code_88;  // 88
    uint32 color_8c; // 8C
    sint16 x_90;     // 90
    sint16 y_92;     // 92
    sint16 z_94;     // 94
    uint8 scale_96;  // 96
    uint8 scale_97;  // 97
    uint16 size_98;  // 98
    sint16 value_9a; // 9A
    uint32 value_9c; // 9C
    uint8 reserveda0[4];
    SVECTOR pos_a4; // A4
    uint8 reservedac[0x10];
} SHL_SPRITE;

// Draw description of a model shot.
typedef struct
{
    uint32 word_88;  // 88
    MATRIX mtx_8c;   // 8C
    SVECTOR pos;     // AC
    uint32 color_b4; // B4
    uint8 reservedb8[4];
} SHL_MODEL;

// A player slot (Player_work, or func_80036294's record for ids 0 to 0xF; stride 0x5F4), as the
// weapons see it.
typedef struct
{
    uint8 reserved000[0x14];
    SVECTOR pos;    // 14
    SHL_FIXED fpos; // 1C
    uint8 reserved02c[0x28];
    SVECTOR rot; // 54
    uint8 reserved05c[0xA4];
    uint8 value_100; // 100
    uint8 reserved101[0x1B];
    uint16 pad_11c; // 11C
    uint8 reserved11e[0x1E];
    uint16 value_13c; // 13C
    uint8 reserved13e[0x32];
    sint8 state_170; // 170
    sint8 value_171; // 171
    uint8 reserved172[2];
    sint8 value_174; // 174
    uint8 reserved175[0xB3];
    MATRIX mtx_228; // 228
    MATRIX mtx_248; // 248
    uint8 reserved268[0x140];
    SVECTOR pos_3a8; // 3A8
    uint8 reserved3b0[0x10];
    SVECTOR pos_3c0; // 3C0
    SVECTOR pos_3c8; // 3C8
    uint8 reserved3d0[0x7C];
    uint8 value_44c; // 44C
    uint8 reserved44d[0xBA];
    sint8 value_507; // 507
    sint8 value_508; // 508
    uint8 reserved509[3];
    sint8 value_50c; // 50C
    uint8 reserved50d[0xD];
    sint16 timer_51a; // 51A
    sint8 value_51c;  // 51C
    uint8 reserved51d;
    sint8 value_51e; // 51E
    uint8 reserved51f[5];
    sint8 value_524; // 524
    uint8 reserved525[3];
    sint8 value_528; // 528
    uint8 reserved529[7];
    sint8 value_530; // 530
    uint8 reserved531;
    sint16 timer_532; // 532
    sint8 value_534;  // 534
    uint8 reserved535;
    sint8 value_536; // 536
    uint8 reserved537[5];
    sint8 value_53c; // 53C
    uint8 reserved53d;
    sint8 value_53e; // 53E
    uint8 reserved53f[5];
    sint8 value_544; // 544
    uint8 reserved545[7];
    sint8 value_54c; // 54C
    uint8 reserved54d[0xB];
    uint8 value_558; // 558
    uint8 reserved559;
    sint16 timer_55a; // 55A
    uint8 reserved55c[2];
    uint8 value_55e; // 55E
    uint8 reserved55f[3];
    sint16 timer_562; // 562
    uint8 reserved564[0x90];
} SHL_PLAYER;

extern SHL_PLAYER Player_work;

// Player_work by its fixed address: GCC rebuilds a literal address at each access instead of
// sharing the symbol's address with a later &Player_work.
#define PLAYER_WORK_PTR ((SHL_PLAYER *)0x800B51B0)

// One shot object: ROCK_NEO.EXE's generic object layout up to 0x88, then the draw data.
typedef struct SHL_WORK
{
    uint8 be_flag; // 00
    uint8 slot;    // 01
    uint8 value_2; // 02
    uint8 type;    // 03: 0x40 set for a shot fired by another object
    uint8 reserved04[2];
    uint8 flags; // 06
    uint8 reserved07;
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 mode_a;    // 0A
    uint8 timer_b;   // 0B
    sint8 index_c;   // 0C
    sint8 bit_d;     // 0D
    sint8 value_e;   // 0E
    sint8 value_f;   // 0F
    uint8 reserved10[4];
    SVECTOR pos;        // 14
    SHL_FIXED fpos;     // 1C
    SVECTOR old_pos;    // 2C
    SHL_FIXED old_fpos; // 34
    SVECTOR vel;        // 44
    sint16 ax, ay, az;  // 4C
    uint8 reserved52[2];
    SVECTOR rot; // 54
    uint8 reserved5c[8];
    sint16 rot_y; // 64
    sint16 rot_x; // 66
    uint8 reserved68[0xC];
    sint8 value_74;
    uint8 reserved75[3];
    SHL_BOX *box_78; // 78
    sint16 hit_7c;   // 7C
    uint8 reserved7e[0xA];
    union
    {
        SHL_SPRITE spr;
        SHL_MODEL mdl;
    } draw;          // 88
    uint32 col_bc;   // BC: second hit accumulator (func_800341BC)
    uint32 col_c0;   // C0
    uint32 col_c4;   // C4: hit accumulator (func_8003430C, func_800341BC)
    uint32 col_c8;   // C8
    sint32 value_cc; // CC
    sint32 value_d0; // D0
    uint32 value_d4; // D4
} SHL_WORK;

typedef void (*SHL_FUNC)(SHL_WORK *wp);

// Game_work, as the SHL modules read it.
typedef struct
{
    uint8 reserved00[0x50];
    sint8 value_50; // 50
} SHL_GAME;

extern SHL_GAME Game_work;

// A GPU colour word: command byte and RGB.
#define SHL_RGB(code, r, g, b) (((code) << 24) | ((b) << 16) | ((g) << 8) | (r))

// Frame counter in the scratchpad.
#define SHL_FRAME (*(uint16 *)0x1F800002)

// Effect slot (ROCK_NEO's CODE456_WORK, seen from the SHL modules): func_80031618 returns a
// free one from the 64-slot table D_800A3B40.
typedef struct
{
    sint8 be_flag; // 00
    uint8 slot;
    uint8 id;     // 02
    uint8 flag_3; // 03
    uint8 reserved04[4];
    uint8 routine_0; // 08
    uint8 reserved09;
    uint8 index_a; // 0A
    uint8 reserved0b;
    uint8 value_c; // 0C
    uint8 value_d; // 0D
    uint8 value_e; // 0E
    uint8 reserved0f[0xD];
    sint16 x_1c; // 1C
    sint16 y_1e; // 1E
    sint16 z_20; // 20
    uint8 reserved22[0xE];
    sint16 vx_30; // 30
    sint16 vy_32; // 32
    sint16 vz_34; // 34
    uint8 reserved36[2];
    SVECTOR pos_38;  // 38
    uint32 value_40; // 40
    uint8 reserved44[4];
} SHL_FX;

extern SHL_FX D_800A3B40[64];

// ROCK_NEO.EXE functions, as the SHL modules call them. The object routines are generic (players,
// enemies, effects), so they take any object.
void Sound_call(sint32 sound, ...);
void Sound_call2(sint16 id, void *pos);
sint32 rand(void);
void *func_80036294(sint32 id);
void *func_80031618(void); // a free effect slot (SHL_FX, or a module's own view)
SHL_WORK *Open_PL_SHL_WORK(void);
void Close_PL_SHL_WORK(void *obj);
void Close_SHL_WORK(void *obj);
void Model_work_init(void *obj, void *arg);
void func_80033F04(SVECTOR *out, SVECTOR *dir, SVECTOR *cur, sint32 a3, sint32 a4);
void func_80030150(SHL_FIXED *fpos, SVECTOR *pos);
void Model_Shadow_Trans(void *obj, sint32 a1, sint32 a2, sint32 a3);
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, SVECTOR *pos);
sint32 func_800341BC(SVECTOR *pos, sint32 half, sint32 arg2, sint32 arg3, sint32 id, uint32 *col, uint32 flags, sint32 arg7, sint32 arg8);
sint32 Obj_map_push_out(void *obj);
void Wall_reflect_spd(SVECTOR *vel, sint32 flags);
sint32 Map_cell_get(SVECTOR *pos);
sint32 Obj_ceiling_height_get(void *obj);
sint32 Front_hit_event(void *obj);
sint32 func_8004324C(SHL_PLAYER *pl);
void func_800354E0(sint32 bit);
sint32 func_80037634(void *pl, sint32 arg);
sint32 func_80037694(void *obj, sint32 arg);
sint32 func_800375D4(void *pl, sint32 arg);
sint16 func_80039B80(void);
void func_80051BAC(void *obj);
void func_8003430C(void *pos_a, sint32 a1, void *pos_b, sint32 a3, sint32 a4, sint32 a5, sint32 a6, uint32 *a7, sint32 a8, sint32 a9,
                   sint32 a10);

#endif // SHL_H
