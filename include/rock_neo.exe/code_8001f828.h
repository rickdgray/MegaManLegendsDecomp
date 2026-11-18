#ifndef CODE_8001F828_H
#define CODE_8001F828_H

#include "common.h"
#include "psyq/libgpu.h"
#include "rock_neo.exe/scene.h"

// Scratchpad work area
#define C8001F828_SCR_C8(i)  (*(uint32 *)(0x1F8001C8 + (i) * 4))
#define C8001F828_SCR_100(i) (*(uint32 *)(0x1F800100 + (i) * 4))

// Display-list header: low byte is the parameter word count, bits 8..13 the 8-byte entry count * 2
typedef struct
{
    uint32 head;
    uint32 param[3];
} C8001F828_LIST;

extern uint8 D_800BEAD8[];
extern uint8 *D_8009893C;
extern uint8 D_800987DC;
extern uint8 D_800BEF88[];

// Scrolling-layer record; position words at +4 and +8 are wrapped into [0, wrap << 21)
typedef struct
{
    uint8 reserved00;
    uint8 wrap_x_on;
    uint8 reserved02[2];
    union
    {
        sint32 w;
        struct
        {
            sint16 lo;
            sint16 hi;
        } h;
    } x;
    union
    {
        sint32 w;
        struct
        {
            sint16 lo;
            sint16 hi;
        } h;
    } y;
    sint16 prev_x;
    sint16 prev_y;
    uint8 reserved10[0x14];
    sint16 wrap_x;
    sint16 wrap_y;
} C8001F828_LAYER;

#define C8001F828_SCR_28  (*(sint16 *)0x1F800028)
#define C8001F828_SCR_2C  (*(sint16 *)0x1F80002C)
#define C8001F828_SCR_140 (*(sint16 *)0x1F800140)
#define C8001F828_SCR_144 (*(sint16 *)0x1F800144)
#define C8001F828_SCR_1BC (*(sint32 *)0x1F8001BC)
// Scratchpad block at 0x1F800100
typedef struct
{
    uint8 reserved00[0x40];
    uint16 w40;
    uint16 w42;
    uint16 w44;
    uint8 reserved46[0x82];
    uint32 copy[1];
} C8001F828_SCR100;

#define C8001F828_SCR_04 (*(uint16 *)0x1F800004)
#define C8001F828_SCR_76 (*(uint16 *)0x1F800076)
#define C8001F828_SCR_75 (*(uint8 *)0x1F800075)
#define C8001F828_BUF_A  ((void *)0x8015BC00)
#define C8001F828_BUF_B  ((void *)0x8015BD00)

extern uint8 D_80097C64[];

#define C8001F828_S16(a)   (*(sint16 *)(a))
#define C8001F828_U16(a)   (*(uint16 *)(a))
#define C8001F828_U8(a)    (*(uint8 *)(a))
#define C8001F828_TILE_PTR (*(sint16 **)0x1F800048)

// Packed 16-bit coordinate pair; halfword alignment makes GCC copy it with lwl/lwr
typedef struct
{
    sint16 x;
    sint16 y;
} C8001F828_XY;

typedef struct
{
    sint32 y_8;
    C8001F828_XY xy_c;
    sint32 x_10;
    sint32 y_14;
    C8001F828_XY xy_18;
    C8001F828_XY xy_1c;
    uint16 w20;
    uint16 w22;
    uint16 w24;
    uint16 w26;
    uint16 w28;
    uint16 w2a;
    union
    {
        uint32 w;
        struct
        {
            uint16 lo;
            uint16 hi;
        } h;
        struct
        {
            uint8 b0;
            uint8 b1;
            uint8 b2;
            uint8 layer;
        } b;
    } w2c;
    union
    {
        uint16 w;
        struct
        {
            uint8 lo;
            uint8 hi;
        } b;
    } w30;
    uint16 pad32;
    uint16 *next;
} C8001F828_MODEL_BODY;

// 0x38-byte record built from a model header by func_80022FD4
typedef struct
{
    union
    {
        uint16 w;
        struct
        {
            uint8 lo;
            uint8 flag;
        } b;
    } id;
    uint16 pad02;
    sint32 x_4;
    C8001F828_MODEL_BODY body;
} C8001F828_MODEL;

extern C8001F828_MODEL D_800BBA90[11];
extern sint32 D_80098970;
extern sint32 D_80098A78;
extern sint8 D_800C356C;

// Short vector as stored on the stack before a GTE load (vx, vy, vz, pad)
typedef struct
{
    sint16 vx;
    sint16 vy;
    sint16 vz;
    sint16 pad;
} C8001F828_SVEC;

// Scratchpad layout at 0x1F800100 used by the quad splitters: vertex index lists at +0x20
// (four quads of four, then four triangles of three), the packet-chain tail at +0x3C, the
// tpage words at +0x50/+0x54/+0x5C, nine screen XY words at +0x60 and their UV halfwords at +0x88
typedef struct
{
    uint8 reserved00[0x20];
    uint8 idx_20[0x1C];
    uint32 *link_3c;
    uint8 reserved40[0x10];
    uint32 tpage_50;
    uint32 tpage_54;
    uint32 clut_58;
    uint32 tpage_5c;
    sint32 xy_60[10];
    uint16 uv_88[9];
} C8001F828_SPLIT;

#define C8001F828_SPLIT_PTR ((C8001F828_SPLIT *)0x1F800100)
// Corner vertices of the quad being split (a, b, c, d) and its UV bytes, as literal addresses
#define C8001F828_SPLIT_V  ((C8001F828_SVEC *)0x1F800198)
#define C8001F828_SPLIT_UV ((uint8 *)0x1F800188)
// Normal clip with the two-nop interlock before nclip; MAC0 is stored separately
#define C8001F828_GTE_NCLIP_NOP(a, b, c)                                                           \
    __asm__ volatile("mtc2 %0, $12; mtc2 %2, $14; mtc2 %1, $13; nop; nop; nclip"                   \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c))
#define C8001F828_GTE_STMAC0(p) __asm__ volatile("swc2 $24, 0(%0)" : : "r"(p) : "memory")
// Absolute value as a macro: an argument with a call in it is evaluated twice
#define C8001F828_ABS(x) ((x) < 0 ? -(x) : (x))

// The same split work area as laid out for func_80022A94, based at 0x1F800130
typedef struct
{
    uint8 reserved00[0x10];
    uint32 tpage_10;
    uint32 tpage_14;
    uint8 reserved18[8];
    sint32 xy_20[10];
    uint32 *link_48;
    uint8 reserved4c[4];
    uint16 uv_50[9];
    uint8 reserved62[0x2E];
    uint32 clut_90;
    uint32 tpage_94;
} C8001F828_SPLIT2;

#define C8001F828_SPLIT2_PTR ((C8001F828_SPLIT2 *)0x1F800130)
// The same area as the tile model renderers use it: fog CLUT bits at +8, the model's CLUT word at
// +0xC, the colour word at +0x14, screen XY of the corners at +0x20, the chain slot at +0x48, UV words for the quad splitter at
// +0x50, four model-space corners at +0x70 and the split CLUT/tpage words at +0x90
typedef struct
{
    uint8 reserved00[8];
    uint32 fog_08;
    uint32 clut_0c;
    uint32 tpage_10;
    uint32 rgbc_14;
    uint8 reserved18[8];
    sint32 xy_20[10];
    uint32 *link_48;
    uint8 reserved4c[4];
    uint32 uv_50[2];
    uint8 reserved58[0x18];
    C8001F828_SVEC v_70[4];
    uint32 clut_90;
    uint32 tpage_94;
} C8001F828_TILE_WORK;
#define C8001F828_TILEW_PTR ((C8001F828_TILE_WORK *)0x1F800130)
#define C8001F828_SPLIT2_V  ((C8001F828_SVEC *)0x1F8001A0)
#define C8001F828_SPLIT2_UV ((uint8 *)0x1F800180)

typedef struct
{
    uint8 pad00[0x18];
    uint8 *data;
} C8001F828_MODEL_HDR;

#define C8001F828_TR_A       ((sint32 *)0x1F80001C)
#define C8001F828_TR_B       ((sint32 *)0x1F800030)
#define C8001F828_SCR_130(i) (*(sint32 *)(0x1F800130 + (i) * 4))

extern uint32 D_8009886C;
extern uint32 D_800BBE50[];
typedef struct
{
    C8001F828_MODEL_HDR *hdr;
    uint32 reserved;
} C8001F828_MODEL_SLOT;
// Model entry table at 0x80139F00 (D_80139F04 is the first entry's hdr). Reached through its
// fixed address: the load expands as lui at / addu at,reg,at.
typedef struct
{
    uint32 word_0;
    C8001F828_MODEL_HDR *hdr;
} C8001F828_MODEL_ENTRY;
#define C8001F828_MODEL_ENTRIES ((C8001F828_MODEL_ENTRY *)0x80139F00)

extern C8001F828_MODEL_SLOT D_80139F04[];
extern uint8 D_800C0DC0[];

void func_8002235C(uint8 *data, C8001F828_SVEC *pos, uint32 id);
// Ordering-table head record; the per-layer tags start at +0x70
typedef struct
{
    uint8 reserved00[0x70];
    uint32 layer[8];
} C8001F828_OT;

extern sint16 D_800BAEB8[];
extern sint16 D_800BBD00[];
extern C8001F828_OT *D_80098934;
sint32 rsin(sint32 angle);
void func_800272D0(sint32 cx, sint32 cy, sint32 r0, sint32 r1);
extern sint32 D_80098824;
extern sint32 D_800D9BD8;
sint32 SquareRoot0(sint32 v);
sint32 ratan2(sint32 x, sint32 y);
sint32 VSync(sint32 mode);
void func_8002366C(C8001F828_LAYER *lp);
void func_80023144(void);
uint32 *func_8002466C(void);
uint32 *func_8002626C(void);
extern uint32 D_800BADB0[];
uint32 *func_80022A94(void);
extern sint32 D_80097C78[];
extern sint32 D_80097C84[];
sint32 rcos(sint32 angle);
void func_8001782C(uint32 a, uint32 b);
void func_80020BB4(void);
void func_800221E0(void);
void func_8002196C(sint32 x, sint32 y, uint16 id);
void func_80021B14(uint8 *data, C8001F828_SVEC *pos, uint32 id);
void func_80022FD4(uint16 **tbl);
void func_80021834(sint32 x, sint32 y, sint32 tile, sint16 *pos);
void func_80021258(sint32 x0, sint32 x1, sint32 y0, sint32 y1);
void func_80021548(sint32 x0, sint32 x1, sint32 y0, sint32 y1);

sint32 func_800207F8(uint32 flags, sint32 val, uint8 *out, sint32 width);
void func_80023EA8(void *p);
typedef void (*C8001F828_DRAW_FUNC)(uint32 data, sint32 z);
extern C8001F828_DRAW_FUNC D_80089890[][4];
// Scratchpad block at 0x1F800100 as used by the tile draw loops (vector at +0x40, flags at +0x46)
typedef struct
{
    uint8 reserved00[0x40];
    uint32 vxy;
    union
    {
        uint32 w;
        struct
        {
            uint16 z;
            uint16 flag;
        } h;
    } vz;
} C8001F828_SCRVEC;
#define C8001F828_SCRV  ((C8001F828_SCRVEC *)0x1F800100)
#define C8001F828_SHIFT (*(uint8 *)0x1F800074)
// Scratchpad work area at 0x1F800100 as the quad list renderers use it: depth-cue table bytes at
// +0, the chain slot handed to the quad splitter at +0x3C, the fog CLUT bits at +0x48, the
// colour word at +0x54, CLUT and tpage words at +0x58/+0x5C, screen XY of the corners at +0x60,
// the face's UV words at +0x88 and its four model-space corners at +0x98
typedef struct
{
    uint8 fog_tbl[0x3C];
    uint32 *link_3c;
    uint8 reserved40[8];
    uint32 fog_48;
    uint32 flags_4c;
    uint32 tpage_50;
    uint32 rgbc_54;
    uint32 clut_58;
    uint32 tpage_5c;
    union
    {
        sint32 w[10];
        struct
        {
            uint16 x;
            uint16 y;
        } h[10];
    } xy_60;
    uint32 uv_88[2];
    uint8 reserved90[8];
    C8001F828_SVEC v_98[4];
} C8001F828_QUAD_WORK;
#define C8001F828_QUAD_PTR ((C8001F828_QUAD_WORK *)0x1F800100)
// Normal clip and single-vertex transform with their two-nop interlock
#define C8001F828_GTE_NCLIP() __asm__ volatile("nop; nop; nclip")
#define C8001F828_GTE_RTPS()  __asm__ volatile("nop; nop; rtps")
#define C8001F828_GTE_DPCS()  __asm__ volatile("nop; nop; dpcs")
// Screen XY FIFO to the first three vertex slots of a POLY_FT4 (+8, +0x10, +0x18), and to
// three consecutive words
#define C8001F828_GTE_STSXY3_FT(p)                                                                 \
    __asm__ volatile("swc2 $12, 8(%0); swc2 $13, 16(%0); swc2 $14, 24(%0)" : : "r"(p) : "memory")
#define C8001F828_GTE_STSXY3C(p)                                                                   \
    __asm__ volatile("swc2 $12, 0(%0); swc2 $13, 4(%0); swc2 $14, 8(%0)" : : "r"(p) : "memory")
// Load vertices 0-2 from three short vectors at p, with no memory clobber (values held in
// registers stay live across it)
#define C8001F828_GTE_LDV3C(p)                                                                     \
    __asm__ volatile("lwc2 $0, 0(%0); lwc2 $1, 4(%0); lwc2 $2, 8(%0); lwc2 $3, 12(%0); "           \
                     "lwc2 $4, 16(%0); lwc2 $5, 20(%0)"                                            \
                     :                                                                             \
                     : "r"(p))
// Screen Z FIFO entries SZ1-SZ3 to three words
#define C8001F828_GTE_STSZ3(a, b, c)                                                               \
    __asm__ volatile("swc2 $17, 0(%0); swc2 $18, 0(%1); swc2 $19, 0(%2)"                           \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c)                                                      \
                     : "memory")
// Screen Z FIFO (SZ0-SZ3) to four words
#define C8001F828_GTE_STSZ4(a, b, c, d)                                                            \
    __asm__ volatile("swc2 $16, 0(%0); swc2 $17, 0(%1); swc2 $18, 0(%2); swc2 $19, 0(%3)"          \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c), "r"(d)                                              \
                     : "memory")
// Flag bit n of a face word tested through the sign of a shift, as retail does
#define C8001F828_BIT(f, n) ((sint32)((f) << (31 - (n))) < 0)
void func_80024BAC(void *p, sint32 mode);
void func_800267AC(void *p, sint32 mode);
void func_80025900(void *p);
void func_80026B04(void *p);
void func_80024F30(void *p);

// Signed byte at Game_work + 0x52 (scene.h's view leaves it reserved)
#define C8001F828_GAME_52 (*(sint8 *)((uint8 *)&Game_work + 0x52))

// Small data ($gp-addressed in retail; still defined in generated assembly)
extern sint32 D_80097C3C;
extern sint16 D_80098208, D_8009820A, D_8009820C, D_8009820E;
extern sint16 D_80098212, D_80098236, D_8009824C, D_8009825A, D_80098276;
extern sint16 D_8009827C, D_8009827E, D_8009828C, D_8009828E;
extern sint16 D_800982FA, D_800982FC, D_800982FE;
extern sint16 D_800981D0, D_800981D2, D_800981E2;
extern sint16 D_800981BC, D_800981BE, D_800981C0, D_800981C2;
extern sint16 D_800981EE, D_800981F2, D_8009823A, D_8009823E, D_80098240;

// Player position halfwords (+0x14..+0x18); scene.h's Player_work view leaves them reserved
#define C8001F828_PL_POS(i) (*(uint16 *)((uint8 *)&Player_work + 0x14 + (i) * 2))
#define C8001F828_SCR_7C    (*(sint32 *)0x1F80007C)
#define C8001F828_SCR_1C0   (*(sint32 *)0x1F8001C0)
extern uint16 D_800C0DE6;
extern uint8 D_80097C90[];
// 32-byte block copy inside the hand-written asm_fastmem.s (0x800176DC, not in the registry yet)
void func_800176DC(void *src, void *dst, sint32 count);

// The 0x10C-byte pool at 0x8009CF88 (game.h's D_8009CF88, GAME_WORK_10C[32]; game.h cannot be
// included beside scene.h here).
typedef struct
{
    uint8 flags_0;
    uint8 reserved01;
    uint8 kind_2;
    uint8 sub_3;
    uint8 reserved04[6];
    uint8 w_a;
    uint8 h_b;
    uint8 reserved0C[0xAC - 0xC];
    C8001F828_SVEC pos_ac;
    uint8 reservedB4[0x10C - 0xB4];
} C8001F828_POOL_SLOT;
extern C8001F828_POOL_SLOT D_8009CF88[32];
#define C8001F828_TIME_START (*(sint32 *)0x800D9BE4)
#define C8001F828_TIME_A     (*(sint32 *)0x800D9BE8)
#define C8001F828_TIME_B     (*(sint32 *)0x800D9BEC)
extern sint32 D_80098A08, D_800989AC;
void func_80023C08(void);

// 8x8 sprite primitive (GPU code 0x74) used by the debug text drawer
typedef struct
{
    u_long tag;
    u_char r0, g0, b0, code;
    short x0, y0;
    u_char u0, v0;
    u_short clut;
} C8001F828_SPRT8;

#define C8001F828_PRIM_PTR (*(uint8 **)0x1F800070)
extern uint32 Moji_flag;
extern uint16 D_800C0D8E[];
extern uint8 D_80089888[];
extern uint16 D_80097C44[];
extern sint8 D_80097C40;
extern sint8 D_80098340, D_80098344, D_80098348, D_8009834C;

// Camera vector block (code_80037fb4.h's CAM_VEC; that header can't be co-included here)
typedef struct
{
    sint32 x, y, z, w;
} C8001F828_CAM_VEC;

// Camera setup; func_80023728 passes its own four arguments through unchanged
void func_80037FB4(C8001F828_CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3);
void func_80023728(C8001F828_CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3);

// Camera block D_800A3958 (code_80037fb4.h's CAM_BLOCK and CAM_WORK, which can't be co-included
// here): the fields this file reads. Reaching them through the block lets GCC relate their
// addresses, so retail keeps one field address in a register and reaches the others from it.
typedef struct
{
    sint16 vx;
    sint16 vy;
    sint16 vz;
    sint16 pad;
} C8001F828_CAM_ROT;

typedef struct
{
    uint8 reserved00[0x48];
    C8001F828_CAM_VEC pos_48; // 48
    uint8 reserved58[0x40];
    C8001F828_CAM_VEC pos_98; // 98
    C8001F828_CAM_VEC vec_A8; // A8
    C8001F828_CAM_ROT rot_B8; // B8
    uint8 reservedC0[0x24];
} C8001F828_CAM_WORK;

typedef union
{
    uint32 save[0x39];
    C8001F828_CAM_WORK work;
} C8001F828_CAM_BLOCK;

extern C8001F828_CAM_BLOCK D_800A3958;

void func_80024E94(uint32 *list, sint32 mode);

#endif // CODE_8001F828_H
