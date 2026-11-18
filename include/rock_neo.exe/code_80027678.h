#ifndef CODE_80027678_H
#define CODE_80027678_H

#include "common.h"
#include "gte_inline.h"

// Scratchpad work area
#define C80027678_PRIM_PTR   ((uint8 **)0x1F800070)
#define C80027678_SCRATCH_04 (*(uint16 *)0x1F800004)
#define C80027678_SCRATCH_06 (*(uint16 *)0x1F800006)
#define C80027678_SCRATCH_75 (*(uint8 *)0x1F800075)
#define C80027678_SCRATCH_76 (*(uint16 *)0x1F800076)

typedef struct
{
    uint8 reserved00[0x70];
    uint8 *block[1];
} C80027678_TBL;

// Entity slots of 0x48, 0x50 and 0x10C bytes; a state routine gets the payload
#define C80027678_SLOT(NAME, WORK_OFF, SIZE)                                                       \
    typedef struct                                                                                 \
    {                                                                                              \
        sint8 flags;                                                                               \
        uint8 reserved01[5];                                                                       \
        uint8 mask;                                                                                \
        uint8 reserved07[WORK_OFF - 7];                                                            \
        uint8 work[SIZE - WORK_OFF];                                                               \
    } NAME

C80027678_SLOT(C80027678_SLOT48, 0x14, 0x48);
C80027678_SLOT(C80027678_SLOT50, 0x14, 0x50);
C80027678_SLOT(C80027678_SLOT10C, 0x88, 0x10C);

typedef struct
{
    uint16 f0;
    sint16 f2;
    uint16 f4;
    sint16 f6;
    uint16 f8;
    sint16 fA;
} C80027678_ENT12;

typedef struct
{
    sint16 v;
    uint8 reserved02[10];
} C80027678_VAL12;

typedef struct
{
    uint16 v;
    uint8 reserved02[10];
} C80027678_UVAL12;

// One ordering-table entry, reached as a struct field.
typedef struct
{
    uint32 tag;
} C80027678_OT_ENTRY;

typedef void (*C80027678_FUNC)(void *work, sint32 flags);

extern C80027678_FUNC D_800898D0[];
extern C80027678_SLOT48 D_800A3B40[0x40];
extern C80027678_SLOT50 D_800BF118[0x20];
extern C80027678_SLOT10C D_800BFB20[0x10];
extern C80027678_SLOT10C D_8009CF88[0x20];
extern C80027678_ENT12 D_800ACE00[];
extern C80027678_UVAL12 D_800ACE08[];
extern C80027678_VAL12 D_800ACE0A[];
extern sint32 D_800987D8;
extern uint32 D_800988FC;
extern uint8 *D_800BE6D8[];

// Model with a table of 0x14-byte part records at +0x70
typedef struct
{
    uint8 pad00[0x14];
    uint32 hdr; // vertex counts: buffer a in bits 0-7, buffer b in bits 8-15
    sint32 *buf_a;
    sint32 *buf_b;
} C80027678_PART;

typedef struct
{
    uint8 reserved00[0x70];
    uint8 *parts;
} C80027678_MODEL;

// Queue record at D_800ACE00 (12 bytes, six halfwords) and its source record
typedef struct
{
    uint16 f0;
    sint16 f2;
    uint16 f4;
    uint16 f6;
    uint16 f8;
    sint16 fA;
} C80027678_REC;

typedef struct
{
    uint16 f0;
    sint16 f2;
    uint16 f4;
    uint16 f6;
} C80027678_SRC;

sint16 func_80048EA4(C80027678_SRC *p, sint32 a, sint32 b, sint32 c);
// Model object fields used for the shadow queue
typedef struct
{
    uint8 reserved00[0x14];
    uint16 f14;
    sint16 f16;
    uint16 f18;
    uint8 reserved1A[0x3C];
    uint16 f56;
    uint8 reserved58[0x1E];
    sint8 f76;
    uint8 reserved77[0x9F];
    uint16 f116;
} C80027678_MODEL_OBJ;

sint32 func_80048E6C(C80027678_MODEL_OBJ *o);
void func_8002C8CC(C80027678_MODEL_OBJ *o, sint32 a1, sint32 a2, sint32 a3);
void Model_Shadow_Trans(C80027678_MODEL_OBJ *o, sint32 a1, sint32 a2, sint32 a3);
void func_8002CA10(C80027678_SRC *p, sint32 a1, sint32 a2, sint32 a3);
typedef struct
{
    uint32 counts;
    uint8 *tbl_a;
    uint8 *tbl_b;
} C80027678_COUNTS;

void func_8002D0D0(C80027678_COUNTS *c, sint32 delta);
// An update record (flags at +0, mask at +6). Its full 0x5A4-byte size matters: as a 7-byte
// struct it counted as small data (-G8) and GCC folded wp->flags to an absolute address.
typedef struct
{
    sint8 flags;
    uint8 reserved01[5];
    uint8 mask;
    uint8 reserved07[0x59D];
} C80027678_UPD;

typedef struct
{
    sint8 flags;
    uint8 reserved01[5];
    uint8 mask;
    uint8 reserved07[0x59D];
} C80027678_REC5A4;

typedef struct
{
    sint8 flags;
    uint8 reserved01[5];
    uint8 mask;
    uint8 reserved07[0x3B9];
} C80027678_REC3C0;
extern C80027678_REC5A4 D_800C3580[];
extern C80027678_REC3C0 D_8009F108[];

extern uint32 D_80098824;
extern sint32 D_800D9BFC;
extern sint32 D_800D9C00;
extern uint8 Game_work[];
#define C80027678_ROOM (*(sint8 *)(Game_work + 0x50))

sint32 VSync(sint32 mode);
void func_8002831C(void *rec);
void func_80028F90(void *rec);
extern C80027678_UPD Player_work;
extern C80027678_UPD Player_work2;
extern uint8 D_8009BF88[];
extern uint8 D_8009AE48[];
extern sint32 D_800D9BE8;
extern sint32 D_800D9BEC;
extern sint32 D_800D9BF0;
extern sint32 D_800D9BF4;
extern sint32 D_800D9BF8;
#define C80027678_SCRATCH_00 (*(uint8 *)0x1F800000)
#define C80027678_VSYNC_MARK (*(sint32 *)0x800D9BE4)

sint32 func_80027F78(void *work, void *arg);
void func_8002786C(void *work, void *arg);
void func_80029A38(void);
void func_80029B10(void);
void func_80029B94(void);
void func_8002CB18(void);
void func_8002D50C(void);
void func_80027678(void);
void func_80028DE0(void);
void func_8002D320(C80027678_MODEL *m, uint32 idx, sint32 delta);
void func_800177CC(void *, void *);

// Mesh header: triangle and quad counts, then their double-buffered primitive blocks.
// Each triangle record is two 0x20-byte primitives and a packed vertex-index word;
// each quad record is two 0x28-byte primitives and the index word.
typedef struct
{
    uint8 n_tri;
    uint8 n_quad;
    uint8 reserved02[2];
    uint8 *tri;
    uint8 *quad;
    uint8 *verts;
} C80027678_MESH;

// Model work: part rotation matrices at +0x1C8 and part offsets at +0x3A8.
typedef struct
{
    uint8 reserved00[0x170];
    sint8 f170;
    sint8 f171;
    uint8 reserved172[0x1C8 - 0x172];
    uint8 mats[15][0x20];
    uint8 offsets[16][8];
} C80027678_BODY;

// Part draw tables: per body pose, five groups of mesh lists, counts and part indices.
extern C80027678_MESH *D_800898EC[][5];
extern uint8 D_80089928[][5];
extern uint8 D_80089938[];

#define C80027678_MESH_PTR (*(C80027678_MESH **)0x1F8000E8)
#define C80027678_ROT_A    ((uint8 *)0x1F800008)
#define C80027678_MAT_C    ((uint8 *)0x1F8000C0)
#define C80027678_TRANS_A  ((sint32 *)0x1F80001C)
#define C80027678_TRANS_C  ((sint32 *)0x1F8000D4)

// Rotation part of a MATRIX into control registers 0-4.
#define C80027678_GTE_SET_ROT(p)                                                                   \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); ctc2 $12, $0; ctc2 $13, $1;"                   \
                     "lw $12, 8(%0); lw $13, 12(%0); lw $14, 16(%0);"                              \
                     "ctc2 $12, $2; ctc2 $13, $3; ctc2 $14, $4"                                    \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")
// One matrix column (three halfwords 6 bytes apart) in and out of IR1-IR3, and rtir.
#define C80027678_GTE_LDCLMV(p)                                                                    \
    __asm__ volatile("lhu $12, 0(%0); lhu $13, 6(%0); lhu $14, 12(%0);"                            \
                     "mtc2 $12, $9; mtc2 $13, $10; mtc2 $14, $11"                                  \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")
#define C80027678_GTE_RTIR() __asm__ volatile("nop; nop; mvmva 1, 0, 3, 3, 0")
#define C80027678_GTE_STCLMV(p)                                                                    \
    __asm__ volatile("mfc2 $12, $9; mfc2 $13, $10; mfc2 $14, $11;"                                 \
                     "sh $12, 0(%0); sh $13, 6(%0); sh $14, 12(%0)"                                \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14", "memory")
// Object drawn by distance: a model with three detail levels, rotation, position.
// Unaligned vertex (copied with lwl/lwr) and a face record whose last bytes index it.
typedef struct
{
    uint8 b[8];
} C80027678_VTX8;

typedef struct
{
    uint16 uv[4];
    union
    {
        uint32 word;
        uint8 b[4];
    } index;
} C80027678_FACE;

typedef struct
{
    uint8 n_tri;
    uint8 n_quad;
    uint8 n_verts;
    uint8 reserved03;
    C80027678_FACE *tri;
    C80027678_FACE *quad;
    uint32 tex;
    C80027678_VTX8 *verts;
} C80027678_LOD;

typedef struct
{
    uint8 reserved00[0x70];
    uint8 *lod[3];
} C80027678_LOD_MODEL;

typedef struct
{
    C80027678_LOD_MODEL *model;
    uint8 rot[0x20];
    sint16 pos[3];
    sint16 part;
    uint32 tex2;
    uint32 *tex;
} C80027678_OBJ;

extern uint8 D_800C0DC0[];

#define C80027678_LOD_PTR (*(C80027678_LOD **)0x1F8000E8)
#define C80027678_VTX_BUF ((C80027678_VTX8 *)0x1F800100)
#define C80027678_SXY     ((uint32 *)0x1F800100)
#define C80027678_SZ      ((uint16 *)0x1F800300)

// Screen XY of three vertices from three words (SXY0, SXY2, SXY1 order), nclip, SZ1-3.
#define C80027678_GTE_LDSXY3(a, b, c)                                                              \
    __asm__ volatile("mtc2 %0, $12; mtc2 %2, $14; mtc2 %1, $13" : : "r"(a), "r"(b), "r"(c))
#define C80027678_GTE_LDSZ3(a, b, c)                                                               \
    __asm__ volatile("mtc2 %0, $17; mtc2 %1, $18; mtc2 %2, $19" : : "r"(a), "r"(b), "r"(c))
#define C80027678_GTE_LDSZ4(a, b, c, d)                                                            \
    __asm__ volatile("mtc2 %0, $16; mtc2 %1, $17; mtc2 %2, $18; mtc2 %3, $19"                      \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c), "r"(d))
#define C80027678_GTE_STSZ3(p)                                                                     \
    __asm__ volatile("swc2 $17, 0(%0); swc2 $18, 4(%0); swc2 $19, 8(%0)" : : "r"(p) : "memory")
#define C80027678_PRIM  (*(uint32 **)0x1F800070)
#define C80027678_FAR_Z (*(uint16 *)0x1F800006)

void func_8002AEE4(C80027678_LOD *lod, uint32 *attr);
void func_800289A0(C80027678_LOD *lod);
void func_80029608(C80027678_LOD *lod);
void func_8002A6E8(C80027678_LOD *lod, uint32 color, uint32 flags);
void func_8002B644(C80027678_LOD *lod, uint32 *colors, uint32 rgb);
void func_8002C0C4(C80027678_LOD *lod, uint32 *colors, uint32 rgb);

// Small data ($gp-addressed in retail; not yet owned by this file).
extern sint32 D_80098554;

extern uint8 Scene_work;            // same as game.h
extern uint32 D_800A4D40[][0x1000]; // same as code_800133d8.h
extern sint16 D_800BBCF8[];         // sine table, 64 entries (same as main.h)
extern sint16 D_800BAEB0[];         // cosine table, 64 entries (same as main.h)
sint32 func_8005EBC4(void);
sint32 func_8005EBD4(void);

#define C80027678_SCRATCH_02 (*(uint16 *)0x1F800002)

// Depth-cue the colour word at p in place.
#define C80027678_GTE_DPCS(p)                                                                      \
    __asm__ volatile("lwc2 $6, 0(%0); nop; nop; dpcs; swc2 $22, 0(%0)" : : "r"(p) : "memory")

// Store SZ3 / 4 (the OT z of rtps) to p.
#define C80027678_GTE_STSZOTZ(p)                                                                   \
    __asm__ volatile("mfc2 $12, $19; nop; sra $12, $12, 2; sw $12, 0(%0)"                          \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "memory")
#define C80027678_GTE_RTV0() __asm__ volatile("nop; nop; mvmva 1, 0, 0, 3, 0")

// Small data ($gp-addressed in retail; not yet owned by this file).
extern sint32 D_80098550;

#define C80027678_SCRATCH_E0 (*(uint32 *)0x1F8000E0)
#define C80027678_SCRATCH_E4 (*(uint32 *)0x1F8000E4)

// Load vertices 0-2 from three separate short vectors.
#define C80027678_GTE_LDV3(a, b, c)                                                                \
    __asm__ volatile("lwc2 $0, 0(%0); lwc2 $1, 4(%0); lwc2 $2, 0(%1); lwc2 $3, 4(%1);"             \
                     "lwc2 $4, 0(%2); lwc2 $5, 4(%2)"                                              \
                     :                                                                             \
                     : "r"(a), "r"(b), "r"(c)                                                      \
                     : "memory")
#define C80027678_GTE_NCLIP() __asm__ volatile("nclip")
// GTE commands with their two leading nops in one statement (PsyQ gte_nclip() style).
#define C80027678_GTE_NCLIP_NOP() __asm__ volatile("nop; nop; nclip")
#define C80027678_GTE_RTPS_NOP()  __asm__ volatile("nop; nop; rtps")
#define C80027678_GTE_AVSZ4_NOP() __asm__ volatile("nop; nop; avsz4")
#define C80027678_GTE_AVSZ3()     __asm__ volatile("avsz3")
#define C80027678_GTE_AVSZ4()     __asm__ volatile("avsz4")

void func_80027BE0(uint32 *prim, uint32 *ot, uint8 **verts);
// The mesh pointer argument is reused as the primitive cursor (one register in retail).
void func_80027D94(uint32 *prim, uint32 *ot, uint8 **verts);
// Shadow record: position and a flag that picks the texture half.
typedef struct
{
    sint16 x, y, z, flag;
} C80027678_SHADOW;

// Textured quad (0x28 bytes, PsyQ POLY_FT4 layout).
typedef struct
{
    uint32 tag;
    uint32 rgbc;
    sint16 x0, y0;
    uint8 u0, v0;
    uint16 clut;
    sint16 x1, y1;
    uint8 u1, v1;
    uint16 tpage;
    sint16 x2, y2;
    uint8 u2, v2;
    uint16 pad1;
    sint16 x3, y3;
    uint8 u3, v3;
    uint16 pad2;
} C80027678_FT4;

#define C80027678_PRIM_NEXT (*(uint8 **)0x1F800070)
#define C80027678_TRANS_V   ((uint8 *)0x1F800030)
#define C80027678_OT        (*(uint32 **)0x1F80003C)
#define C80027678_SHIFT     (*(uint8 *)0x1F800074)

// Translation vector (three words at p) into control registers 5-7.
#define C80027678_GTE_SET_TRANS_V(p)                                                               \
    __asm__ volatile("lw $12, 0(%0); lw $13, 4(%0); lw $14, 8(%0); ctc2 $12, $5; ctc2 $13, $6;"    \
                     "ctc2 $14, $7"                                                                \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")
// Translation part of a MATRIX into control registers 5-7.
#define C80027678_GTE_SET_TRANS(p)                                                                 \
    __asm__ volatile("lw $12, 20(%0); lw $13, 24(%0); ctc2 $12, $5; lw $14, 28(%0);"               \
                     "ctc2 $13, $6; ctc2 $14, $7"                                                  \
                     :                                                                             \
                     : "r"(p)                                                                      \
                     : "$12", "$13", "$14")

void func_8002CBDC(C80027678_SHADOW *rec, sint32 r, uint32 da, uint32 ang, sint32 dist);
extern sint32 rsin(sint32 a);
extern sint32 rcos(sint32 a);

// Local copy of an object's rotation (MATRIX layout; the word member keeps the copy aligned).
typedef struct
{
    sint16 m[3][3];
    sint16 pad;
    sint32 t[3];
} C80027678_MATRIX;

#define C80027678_VIEW_TR ((sint32 *)0x1F800030)

void func_8002A160(C80027678_OBJ *obj, uint32 flags);

// Camera-facing sprite: texture word, colour, position, uv, half size and roll angle.
typedef struct
{
    uint32 tex;
    uint32 color;
    sint16 pos[3];
    uint16 uv;
    uint16 size;
    uint16 angle;
} C80027678_SPRITE;

typedef struct
{
    sint16 vx, vy, vz, pad;
} C80027678_SVEC;

typedef struct
{
    sint16 x, y;
} C80027678_DVEC;

// Screen XY FIFO (data registers 12-14) to three consecutive words at p.
#define C80027678_GTE_STSXY3C(p)                                                                   \
    __asm__ volatile("swc2 $12, 0(%0); swc2 $13, 4(%0); swc2 $14, 8(%0)" : : "r"(p) : "memory")

// Screen XY FIFO into the first three vertex slots of a primitive in one statement:
// FT3/FT4 layout (+8, +0x10, +0x18) and GT3/GT4 layout (+8, +0x14, +0x20).
#define C80027678_GTE_STSXY3_FT(p)                                                                 \
    __asm__ volatile("swc2 $12, 8(%0); swc2 $13, 16(%0); swc2 $14, 24(%0)" : : "r"(p) : "memory")
#define C80027678_GTE_STSXY3_GT(p)                                                                 \
    __asm__ volatile("swc2 $12, 8(%0); swc2 $13, 20(%0); swc2 $14, 32(%0)" : : "r"(p) : "memory")

void func_80029C18(C80027678_SPRITE *obj, uint32 flags);

// Multi-part model work (enemy records of 0x3C0 and 0x5A4 bytes): parts drawn with their own
// rotation (two matrix tables, picked by kind) and offset, each part a LOD model entry.
typedef struct
{
    uint8 lod;
    sint8 count; // first record only: number of parts
    uint8 reserved02;
    sint8 hide;
} C80027678_PART_REF;

typedef struct
{
    uint8 flags;
    uint8 kind;
    uint8 reserved02[4];
    uint8 draw;
    uint8 reserved07[0xD];
    sint16 pos[4];
    uint8 reserved1C[0x6C];
    C80027678_LOD_MODEL *model;
    uint8 reserved8C[0x6C];
    C80027678_PART_REF parts[0x19];
    uint8 reserved15C[2];
    sint16 color;
    uint8 reserved160[0x20];
    C80027678_SVEC offs[0xD]; // pad holds a 15-bit part colour
    union
    {
        C80027678_MATRIX mats[6];
        struct
        {
            uint8 reserved00[0x58];
            C80027678_MATRIX mats[6];
        } kind40;
    } rot;
} C80027678_MULTI;

#define C80027678_LOD_MODE (*(uint8 *)0x1F800078)
#define C80027678_IR0_SAVE ((uint32 *)0x1F8000EC)

// Queued billboard packet (0x28 bytes): before drawing, the vertex words hold the world
// position (x/y in xy0, z in xy1), the half size in xy2 and flags in xy3.
typedef struct
{
    uint32 tag;
    union
    {
        uint32 word;
        struct
        {
            uint8 r, g, b, code;
        } c;
    } rgbc;
    uint32 xy0;
    uint32 uv0;
    uint32 xy1;
    uint32 uv1;
    uint32 xy2;
    uint32 uv2;
    uint32 xy3;
    uint32 uv3;
} C80027678_BB;

// Identity matrix built in the scratchpad vertex buffer.
#define C80027678_MAT_ID ((sint32 *)0x1F800100)

#endif
