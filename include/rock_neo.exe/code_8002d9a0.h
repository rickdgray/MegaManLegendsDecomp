#ifndef CODE_8002D9A0_H
#define CODE_8002D9A0_H

#include "common.h"

// Byte-aligned records returned by value (copied with lwl/lwr/swl/swr)
typedef struct
{
    sint32 w[1];
} C8002D9A0_W4;

typedef struct
{
    uint8 b[4];
} C8002D9A0_B4;

typedef struct
{
    sint32 w[2];
} C8002D9A0_W8;

typedef struct
{
    uint8 b[8];
} C8002D9A0_B8;

typedef struct
{
    sint32 w[3];
} C8002D9A0_W12;

typedef struct
{
    uint8 b[12];
} C8002D9A0_B12;

// Word-aligned table entries
typedef struct
{
    sint32 w[2];
} C8002D9A0_ENT8;

typedef struct
{
    sint32 w[4];
} C8002D9A0_ENT16;

// Face record: texture coordinates, then the packed vertex indices.
typedef struct C8002D9A0_FACE
{
    uint16 uv[4];
    uint32 index;
} C8002D9A0_FACE;

// Mesh at one detail level (0x14 bytes): triangle, quad and vertex counts, their lists,
// the texture page/CLUT word and the vertex array.
typedef struct
{
    uint8 n_tri;
    uint8 n_quad;
    uint8 n_verts;
    uint8 reserved03;
    struct C8002D9A0_FACE *tri;
    struct C8002D9A0_FACE *quad;
    uint32 tex;
    uint32 *verts;
} C8002D9A0_LOD;

typedef struct
{
    uint8 reserved00[0x70];
    uint8 *lod[3];
} C8002D9A0_MODEL;

typedef struct
{
    uint8 index;
    sint8 count;
    uint8 reserved02;
    sint8 hidden;
} C8002D9A0_PART;

// 0x560-byte work records; the first byte holds state flags
typedef struct
{
    uint8 flags;
    uint8 reserved01[0xB];
    sint16 pos[4];
    uint8 reserved14[0x6C];
    C8002D9A0_MODEL *model;
    uint8 reserved84[0xB4];
    uint8 mats[24][0x20];
    sint16 offsets[24][4];
    C8002D9A0_PART parts[25];
    uint16 reserved55C;
    sint16 color;
} C8002D9A0_REC;

#define C8002D9A0_FOG_TBL ((uint8 *)0x800C0DC0)
#define C8002D9A0_ROT_A   ((uint8 *)0x1F800008)
#define C8002D9A0_TRANS_A ((sint32 *)0x1F80001C)
#define C8002D9A0_TRANS_V ((uint8 *)0x1F800030)
#define C8002D9A0_SHIFT   (*(uint8 *)0x1F800074)
#define C8002D9A0_MAT_C   ((uint8 *)0x1F8000C0)
#define C8002D9A0_TRANS_C ((sint32 *)0x1F8000D4)
#define C8002D9A0_TPAGE   (*(uint32 *)0x1F8000E0)
#define C8002D9A0_COLOR   (*(uint32 *)0x1F8000E4)
#define C8002D9A0_LOD_PTR (*(C8002D9A0_LOD **)0x1F8000E8)
#define C8002D9A0_DEPTH   ((sint32 *)0x1F8000EC)
#define C8002D9A0_SXY     ((uint32 *)0x1F800100)
#define C8002D9A0_SZ      ((uint16 *)0x1F800300)
#define C8002D9A0_PRIM    (*(uint32 **)0x1F800070)
#define C8002D9A0_OT      (*(uint32 **)0x1F80003C)
#define C8002D9A0_FAR_Z   (*(uint16 *)0x1F800006)
// A scratchpad word reached at a byte offset from a base pointer
#define C8002D9A0_REL(base, off, type) (*(type *)((uint8 *)(base) + (off)))

// 15-bit colour to a 24-bit colour word
#define C8002D9A0_RGB24(c)                                                                         \
    ((((c) & 0x1F) << 3) | (((c) & 0x3E0) << 6) | (((c) & 0x7C00) << 9) | (((c) & 0x8000) << 10))

#define C8002D9A0_GTE_SET_ROT(p)                                                                   \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); ctc2 $12, $0; ctc2 $13, $1;"                   \
                     "lw $12, 8(%0); lw $13, 12(%0); lw $14, 16(%0);"                              \
                     "ctc2 $12, $2; ctc2 $13, $3; ctc2 $14, $4"                                    \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")
#define C8002D9A0_GTE_SET_TRANS_V(p)                                                               \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); lw $14, 8(%0); ctc2 $12, $5; ctc2 $13, $6;"    \
                     "ctc2 $14, $7"                                                                \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")
#define C8002D9A0_GTE_LDCLMV(p)                                                                    \
    __asm__ volatile("lhu $12, 0(%0); lhu $13, 6(%0); lhu $14, 12(%0);"                            \
                     "mtc2 $12, $9; mtc2 $13, $10; mtc2 $14, $11"                                  \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")
#define C8002D9A0_GTE_RTIR() __asm__ volatile("nop; nop; mvmva 1, 0, 3, 3, 0")
#define C8002D9A0_GTE_STCLMV(p)                                                                    \
    __asm__ volatile("mfc2 $12, $9; mfc2 $13, $10; mfc2 $14, $11;"                                 \
                     "sh $12, 0(%0); sh $13, 6(%0); sh $14, 12(%0)"                                \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14", "memory")
#define C8002D9A0_GTE_RTV0() __asm__ volatile("nop; nop; mvmva 1, 0, 0, 3, 0")
#define C8002D9A0_GTE_STSZOTZ(p)                                                                   \
    __asm__ volatile("mfc2 $12, $19; nop; sra $12, $12, 2; sw $12, 0(%0)"                          \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "memory")
#define C8002D9A0_GTE_DPCS(p)                                                                      \
    __asm__ volatile("lwc2 $6, 0(%0); nop; nop; dpcs; swc2 $22, 0(%0)" : : "r"(p) : "memory")

// Screen XY of three vertices from three pointers (SXY0, SXY2, SXY1 load order)
#define C8002D9A0_GTE_LDSXY3(a, b, c)                                                              \
    __asm__ volatile("lwc2 $12, 0(%0); lwc2 $14, 0(%2); lwc2 $13, 0(%1)"                           \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c)                                                      \
                     : "memory")
// Screen Z of three or four vertices (SZ1..SZ3 or SZ0..SZ3)
#define C8002D9A0_GTE_LDSZ3(a, b, c)                                                               \
    __asm__ volatile("mtc2 %0, $17; mtc2 %1, $18; mtc2 %2, $19" : : "r"(a), "r"(b), "r"(c))
#define C8002D9A0_GTE_LDSZ4(a, b, c, d)                                                            \
    __asm__ volatile("mtc2 %0, $16; mtc2 %1, $17; mtc2 %2, $18; mtc2 %3, $19"                      \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c), "r"(d))
#define C8002D9A0_GTE_NCLIP()       __asm__ volatile("nop; nop; nclip")
#define C8002D9A0_GTE_AVSZ3()       __asm__ volatile("nop; nop; avsz3")
#define C8002D9A0_GTE_AVSZ4()       __asm__ volatile("nop; nop; avsz4")
#define C8002D9A0_GTE_GET(n, v)     __asm__ volatile("mfc2 %0, $" #n : "=r"(v))
#define C8002D9A0_GTE_GET_NOP(n, v) __asm__ volatile("mfc2 %0, $" #n "; nop" : "=r"(v))

// The scratchpad as func_8002E3D0 reaches it: one symbol, so GCC relates every field address to
// the screen-XY table's (retail keeps 0x1F800100 in one register and reaches the rest from it).
typedef struct
{
    uint8 reserved00[0x3C];
    uint32 *ot; // 3C
    uint8 reserved40[0x30];
    uint32 *prim; // 70
    uint8 reserved74[0x6C];
    uint32 tpage; // E0
    uint32 color; // E4
    uint8 reservedE8[0x18];
    uint32 sxy[0x80]; // 100
    uint16 sz[0x100]; // 300
} C8002D9A0_SCRATCH;

extern C8002D9A0_SCRATCH D_1F800000;

void func_8002E3D0(C8002D9A0_LOD *lod);

// Unpacked primitive header returned by value
typedef struct
{
    uint32 head;
    uint32 b;
    uint32 c;
    uint32 d;
} C8002D9A0_UNPACK;

// Object whose +0x18 table holds pointers to packed lists
typedef struct
{
    uint8 reserved00[0x18];
    uint32 *list[1];
} C8002D9A0_OBJ;

// Polygon record rewritten in place by func_8002D9A0 (input fields reused as output)
typedef struct
{
    uint32 tag;
    uint32 rgb;
    uint32 w8;
    uint32 wC;
    uint32 w10;
    uint32 w14;
    uint32 w18;
    uint32 w1C;
    uint32 w20;
} C8002D9A0_POLY;

// Local scratch for func_8002D9A0: three short vertices, then the screen XY readback
typedef union
{
    sint16 h[12];
    sint32 w[6];
} C8002D9A0_VERTS;

extern uint32 D_800988FC;
extern C8002D9A0_POLY *D_800BE6D8[];
extern sint32 D_80097CD4[];
extern uint8 D_800C0DC0[];

C8002D9A0_UNPACK func_8002DC84(C8002D9A0_OBJ *obj, sint32 i, sint32 j);
void func_8002DEEC(C8002D9A0_REC *rec);
void func_8002DE5C(void);
void func_8002DE20(C8002D9A0_ENT16 *tbl, sint32 idx, sint32 *src);
void func_8002DE04(C8002D9A0_ENT8 *tbl, sint32 idx, sint32 *src);
void func_8002DE34(C8002D9A0_ENT16 *tbl, sint32 idx, sint32 *src);
C8002D9A0_B4 func_8002DD68(C8002D9A0_ENT16 *tbl, sint32 idx);
C8002D9A0_B8 func_8002DD1C(C8002D9A0_ENT8 *tbl, sint32 idx);
C8002D9A0_B12 func_8002DDA0(C8002D9A0_ENT16 *tbl, sint32 idx);

#endif // CODE_8002D9A0_H
