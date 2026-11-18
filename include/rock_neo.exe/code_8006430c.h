#ifndef ROCK_CODE_8006430C_H
#define ROCK_CODE_8006430C_H

#include "common.h"
#include "psyq/libapi.h"
#include "psyq/libgpu.h"
#include "player.h"

// Memory card event classes and specs (PsyQ values).
#define SW_CARD      0xF4000001
#define HW_CARD      0xF0000011
#define EV_SP_IOE    0x0004
#define EV_SP_ERROR  0x8000
#define EV_SP_TIMOUT 0x0100
#define EV_SP_NEW    0x2000
#define EV_MD_NOINTR 0x2000

// Memory card / file screen work. Only the fields these helpers touch.
typedef struct MEM_WORK
{
    uint16 value_0;
    uint16 arg_2;
    sint8 mode_4;
    sint8 sub_5;
    sint8 step_6;
    sint8 step_7;
    uint16 pad_8;
    uint16 pad_a;
    sint32 timer_0c;
    sint32 timer_10;
} MEM_WORK;

// Saved record (16 bytes): an id, two values from a defaults table, and a cleared word.
typedef struct
{
    sint32 id;
    sint32 value_4;
    sint32 value_8;
    sint32 value_c;
} MEM_RECORD;

// Default values for a record (value_4, value_8).
typedef struct
{
    sint32 value_4;
    sint32 value_8;
} MEM_RECORD_INIT;

// Word view of a record: the defaults are copied as words (retail walks a pointer per
// word), while id and value_c are written as fields.
#define MEM_WORDS(x) ((sint32 *)&(x))

// Local view of Game_work: only the fields this file touches.
typedef struct
{
    uint8 reserved00[0xC];
    uint32 timer_0c;
    uint8 reserved10[4];
    uint32 timer_14;
    uint8 reserved18[4];
    uint32 words_1c[9];
    uint16 halves_40[6];
    uint32 word_4c;
    uint16 value_50;
    uint8 reserved52[8];
    uint8 flag_5a;
    uint8 reserved5b[5];
    sint16 value_60;
    sint16 value_62;
    uint32 word_64;
    uint8 reserved68[0x10];
    uint8 flags_78;
    sint8 flags_79;
    sint8 flags_7a;
    uint8 flags_7b;
    uint8 flags_7c;
    uint8 flags_7d;
    uint8 reserved7e[4];
    sint8 flags_82;
    uint8 reserved83;
    MEM_RECORD records_84[15];
} MEM_GAME_VIEW;

typedef struct
{
    uint8 reserved00[0x15];
    uint8 flag_15;
} MEM_ENTRY;

typedef sint32 (*MEM_FUNC)(MEM_WORK *wp);

// PsyQ directory entry (libapi); not yet in include/psyq/libapi.h.
struct DIRENTRY
{
    char name[20];
    long attr;
    long size;
    struct DIRENTRY *next;
    long head;
    char system[4];
};

// Status-screen icon (16 bytes). id's low byte is the grid slot (6 per row) and its
// high byte the icon kind; a negative id ends the list.
typedef struct
{
    uint16 id;
    sint16 flag;
    sint16 x;
    sint16 y;
    uint32 uv_clut;
    uint32 wh;
} CODE643_ICON;

typedef struct
{
    uint8 reserved00[5];
    sint8 layer;
    uint8 reserved06[2];
    CODE643_ICON *icons;
} CODE643_ICON_SET;

// Sprite packet in a 40-byte primitive slot.
typedef struct
{
    u_long tag;
    u_long code_rgb;
    u_long xy;
    u_long uv_clut;
    u_long wh;
    uint8 reserved14[0x14];
} CODE643_PRIM;

// Ordering-table head record; the per-layer tags start at +0x70.
typedef struct
{
    uint8 reserved00[0x70];
    u_long layer[8];
} CODE643_OT;

#define CODE643_PRIM_PTR (*(CODE643_PRIM **)0x1F800070)

extern CODE643_OT *D_80098934;
sint32 Sce_flag_test(sint32 flag);

extern MEM_GAME_VIEW Game_work;
extern MEM_ENTRY D_800C3558;
extern uint8 D_800C3570;
// The memory card work (MEM_WORK, 0x14 bytes) starts here; retail reaches its first
// halfword through $gp, so this file owns it as a small object.
extern uint16 D_80098910;
extern sint16 D_80098912;
extern sint8 D_80098914;
extern uint16 D_80098918[2];
extern MEM_FUNC D_8008FD10[];
extern MEM_FUNC D_8008FD20[];
extern char *D_8008FA5C[];
extern uint16 D_800C0C2A;
extern uint16 D_800C0C26;
extern sint32 D_800BE428;
extern sint32 D_800BE42C;
extern sint32 D_800BE430;
extern sint32 D_800BE434;

extern uint8 D_8009AB30[];
extern uint8 D_8009AB31;
extern uint8 D_8008F9BC[];
extern uint8 D_8008FA3C[];

// Memory card event descriptors (small data owned by this file in retail).
extern sint32 D_80098708;
extern sint32 D_8009870C;
extern sint32 D_80098710;
extern sint32 D_80098714;
extern sint32 D_80098718;
extern sint32 D_8009871C;
extern sint32 D_80098720;
extern sint32 D_80098724;

long TestEvent(long event);
void func_8007FC88(long val);
void func_8007FCE0(void);
void _bu_init(void);
void MojiTaskKill(void);
void Sound_call(sint32 sound, ...);
void func_80065064(void);
sint32 rand(void);
void func_80065384(void);
sint32 func_80065E08(void);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
extern uint32 Moji_flag;
// Message script pointers for the memory card screens.
extern uint8 *D_8008CAD8;
extern uint8 *D_8008CADC;
extern uint8 *D_8008CAEC;
extern uint8 *D_8008CAF0;
extern uint8 *D_8008CAF4;
extern uint8 *D_8008CAF8[];
extern uint8 *D_8008CB04;
extern uint8 *D_8008CB00;
extern uint8 *D_8008CB08;
extern uint8 *D_8008CB20;
extern uint8 *D_8008CB24;
extern uint8 *D_8008CB28;
extern uint8 *D_8008CB2C;
extern uint8 *D_8008CB30;
extern uint8 *D_8008CB34;
extern uint8 *D_8008CB38;
extern uint8 *D_8008CB4C;
extern uint8 *D_8008CB50;
extern uint8 *D_8008CB54;
extern uint8 *D_8008CB58;
extern uint8 *D_8008CB10;
extern uint8 *D_8008CB14;
extern uint8 *D_8008CB18;
extern uint8 *D_8008CB1C;
extern uint8 *D_8008CB5C;
extern uint8 *D_8008CB40;
extern uint8 *D_8008CB44;
extern uint8 *D_8008CB48;
extern uint8 D_80098A48;
extern uint8 D_80097FAC[];
extern uint8 D_80097FC0[];
extern char *D_800980AC[];
extern sint16 D_80098728;
extern uint8 D_80098A04;
// Digit glyph codes, and the glyph slots of the play-time text they fill.
extern uint16 D_80098124[];
extern uint16 D_8008FA84[];
struct DIRENTRY *firstfile(char *name, struct DIRENTRY *dir);
struct DIRENTRY *nextfile(struct DIRENTRY *dir);
sint32 _card_info(sint32 chan);
sint32 format(char *path);
sint32 _new_card(void);
sint32 _card_write(sint32 chan, sint32 block, uint8 *buf);
void func_80064A34(void);
void func_800649EC(void);
sint32 _card_clear(sint32 chan);
sint32 _card_load(sint32 chan);
uint32 func_80064C08(sint32 port);
sint32 VSync(sint32 mode);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
sint32 open(char *name, sint32 flags);
sint32 read(sint32 fd, void *buf, uint32 size);
sint32 close(sint32 fd);
sint32 write(sint32 fd, void *buf, uint32 size);
sint32 func_80064984(void);
void func_80067884(void);
sint32 func_80066714(MEM_WORK *wp);
sint32 func_800666D8(MEM_WORK *wp);
void Sce_flag_on(sint32 flag);
// Save slot buffer (0x180 bytes)
typedef struct
{
    uint8 reserved00[0x100];
    uint8 index_100;
    uint8 data_101[8];
    uint8 byte_109;
    uint8 reserved10A[0x76];
} MEM_SLOT;

extern MEM_SLOT D_800BAF38[5];
// Save image buffer (0x1F00 bytes): the CD sector buffer, declared as bytes as in
// cd_local.h and viewed here as a slot header and as words.
extern uint8 D_800B5DB0[];
#define MEM_SAVE       (*(MEM_SLOT *)D_800B5DB0)
#define MEM_SAVE_WORDS ((uint32 *)D_800B5DB0)

// Save-image checksum over words [first, seed): a rotated sum and two keyed sums,
// alternating by word index; save[seed] holds the key.
#define MEM_SUM_BLOCK(first, seed)                                                                 \
    for (i = 0; i < 3; i++)                                                                        \
    {                                                                                              \
        sum[i] = 0;                                                                                \
    }                                                                                              \
    for (i = (first); i < (seed); i++)                                                             \
    {                                                                                              \
        w = save[i];                                                                               \
        sum[0] += (w << 16) | (w >> 16);                                                           \
        if (i & 1)                                                                                 \
        {                                                                                          \
            sum[1] += w ^ (save[(seed)] + i);                                                      \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            sum[2] += w ^ (save[(seed)] + i);                                                      \
        }                                                                                          \
    }
extern uint8 *D_8008D168[];
extern uint8 *D_8008D184[];
extern uint8 D_8008CE94[][13];
extern uint8 D_8008D029[];
extern uint8 D_80097FFC[];
extern uint8 D_8008FA64[];
extern uint8 D_8008D028[];
extern uint8 D_80097FF4;
extern uint8 D_80097FF5;
extern uint8 D_80097FF7;
extern uint8 D_80097FF8;
extern uint8 D_80097FFA;
extern uint8 D_80097FFB;
extern uint8 D_80097FD4;
extern uint8 D_80097FD5;
extern uint8 D_80097FD7;
extern uint8 D_80097FD8;
extern uint8 D_80097FDA;
extern uint8 D_80097FDB;
extern sint8 D_80098800;
extern sint8 D_80098801;
extern sint8 D_80098802;
extern sint8 D_80098803;
extern sint8 D_80098804;
extern sint8 D_80098805;
typedef struct
{
    uint8 b[8];
} MEM_BYTES8;
// Save image layout (0x1F00 bytes at D_800B5DB0), as func_80065064 fills it.
typedef struct
{
    uint8 reserved000[0x101];
    uint8 data_101[8];
    uint8 reserved109[0x1F];
    uint32 gw_10;
    uint32 gw_14;
    uint16 gw_18;
    uint16 gw_1a;
    uint8 reserved134[0x4C];
    uint32 gw_0c;
    uint32 gw_1c[3];
    uint32 gw_4c;
    uint8 gw_50[4];
    uint8 gw_54[3];
    uint8 reserved19b;
    uint8 gw_58[4];
    uint8 reserved1a0[0x20];
    MEM_BYTES8 pl_position;
    uint16 pl_56;
    uint8 reserved1ca[2];
    uint16 pl_6e;
    uint16 pl_b0;
    uint16 gw_60;
    uint16 gw_62;
    uint8 pl_16a[3];
    uint8 reserved1d7;
    uint8 pl_170[4];
    uint8 pl_44c;
    uint8 reserved1dd;
    uint8 pl_44e[2];
    uint32 gw_64;
    uint8 reserved1e4[0x1C];
    uint8 gw_7c[2];
    uint8 reserved202[2];
    uint8 gw_78[4];
    uint32 pl_450;
    uint8 pl_454[0x20];
    uint8 pl_4f4[0x100];
    uint8 reserved32c[0x54];
    uint8 sce_flag[0x100];
    uint8 block_480[0xE00];
    uint8 block_1280[0xA00];
    uint8 pl_474[0x80];
    uint32 gw_28[6];
    uint16 gw_40[6];
    uint8 reserved1d24[0x1C];
    MEM_RECORD records[15];
    uint8 reserved1e30[0xD0];
} MEM_IMAGE;

// Byte, halfword and word access at an offset from a work pointer (fields the local
// views don't name).
#define MEM_B(p, off) (((uint8 *)(p))[off])
#define MEM_H(p, off) (*(uint16 *)((uint8 *)(p) + (off)))
#define MEM_W(p, off) (*(uint32 *)((uint8 *)(p) + (off)))

extern uint8 D_800B5EB0;
extern uint8 Sce_flag[];
extern uint32 D_800BD3B8[][0x80];
extern sint32 D_800BC9B8[0x280];
void func_80064CB8(uint8 *buf, uint8 *src);
void func_80067D10(void);
void func_8003B140(void);
extern uint32 D_800B5ED8;
extern uint32 D_800B5EDC;
extern uint16 D_800B5EE0;
extern uint16 D_800B5EE2;
extern uint32 D_800B5F30;
extern uint32 D_800B5F34;
extern uint32 D_800B5F38;
extern uint32 D_800B5F3C;
extern uint32 D_800B5F40;
extern uint32 D_800B7AB0;
extern uint32 D_800B7AB4;
extern uint32 D_800B7AB8;
extern uint32 D_800B7ABC;
extern uint32 D_800B7AC0;
extern uint32 D_800B7AC4;
extern uint16 D_800B7AC8;
extern uint16 D_800B7ACA;
extern uint16 D_800B7ACC;
extern uint16 D_800B7ACE;
extern uint16 D_800B7AD0;
extern uint16 D_800B7AD2;
extern uint16 D_800B5F80;
extern uint16 D_800B5F82;
extern uint16 D_800B5F78;
extern uint32 D_800B5F90;
extern uint8 D_800B5F44;
extern uint8 D_800B5F45;
extern uint8 D_800B5F46;
extern uint8 D_800B5F47;
extern uint8 D_800B5F48;
extern uint8 D_800B5F49;
extern uint8 D_800B5F4A;
extern uint8 D_800B5F4C;
extern uint8 D_800B5F4D;
extern uint8 D_800B5F4E;
extern uint8 D_800B5F4F;
extern uint8 D_800B5FB0;
extern uint8 D_800B5FB1;
extern uint8 D_800B5FB4;
extern uint8 D_800B5FB5;
extern uint8 D_800B5FB6;
extern uint8 D_800B5FB7;
extern MEM_BYTES8 D_800B5F70;
extern MEM_BYTES8 D_800C3560;
extern uint8 D_800C356E;
extern uint8 D_800C356F;
extern uint8 D_800C356D;
extern sint16 D_800C356A;
#define MEM_GWB(off) (*((uint8 *)&Game_work + (off)))
sint32 func_8006491C(void);
extern sint32 D_8008FF64[9];
extern MEM_RECORD_INIT D_8008D034[9];
extern sint32 D_8009813C[3];
extern sint32 D_80098148[3];
extern MEM_RECORD_INIT D_8008D07C[6];
extern MEM_RECORD D_800B7AF0[15];
// Hand-written 16-byte block copy in asm_fastmem.s.
void func_800176A4(void *src, void *dst, sint32 count);
// Entry tables chosen by stage (CODE456_ENTRY * in code_800456d8.h, which this file
// can't include: its Game_work type differs).
extern void **D_80098844;
extern void **D_8009884C;
extern void **D_80098928;
extern void **D_8009892C;
extern void *D_8008EDC4[];
extern void *D_8008EF64[];
extern void *D_8008EFC4[];
extern void *D_8008F048[];
extern void *D_8008F060[];
extern void *D_8008F200[];
extern void *D_8008F260[];
extern void *D_8008F2E4[];
sint32 func_80064A7C(sint32 port);
sint32 func_80064B60(sint32 port);
sint32 func_80064F8C(sint32 port);

#endif // ROCK_CODE_8006430C_H
