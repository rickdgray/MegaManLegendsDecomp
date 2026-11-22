#ifndef CODE_8006430C_H
#define CODE_8006430C_H

#include "common.h"
#include "code_800456D8.h"
#include "game.h"
#include "cd.h"

// State of this file's module: the global D_80098910, a pool common owned by this file
// (func_800665E8 reaches offset 0 through $gp; maspsx keeps a common with an offset lui-based).
// func_800665FC copies the pad into it, sets mode_2 from its argument and runs
// D_8008FD10[routine_0] on it; routines 1 and 2 (func_800666D8, func_80066714, the same code) both
// run D_8008FD20[routine_1]. Also read by game (func_80016BF4: no soft reset while active_0 is set)
// and moji (func_8005BC90: mode_2). Size at least 0xC; the pool's next label is at 0x80098924.
typedef struct
{
    uint16 active_0;  // 0x0: set to 1 by func_80066664 (routine 0), cleared by func_80066750 (routine 3)
    uint16 mode_2;    // 0x2: func_800665FC's argument; 0 selects routine 2, else routine 1
    sint8 routine_0;  // 0x4: lb; index of D_8008FD10
    sint8 routine_1;  // 0x5: lb; index of D_8008FD20
    uint16 unk_6;     // 0x6: cleared (sh) by func_80066664; func_80066750 clears 0x4-0x7 with one sw
    uint16 pad_now_8; // 0x8: copy of PAD_NOW(Joy1), taken by func_800665FC
    uint16 pad_on_A;  // 0xA: copy of PAD_ON(Joy1), taken by func_800665FC
} CODE_8006430C_WORK;

// One of the five save slots in D_800BAF38 (0x180 bytes each). func_80067884 resets them;
// func_8006689C and func_80067174 also read and write them.
typedef struct
{
    uint8 header[0x100]; // 0x000: the memory card file header sector (card_header_set)
    uint8 unk_100;       // 0x100: row of D_8008CE94 copied into the slot's text (D_8008D168)
    uint8 unk_101[8];    // 0x101: copied with D_8008D184's text; reset from D_80097FFC
    uint8 unk_109;       // 0x109
    uint8 pad_10A[0x76]; // 0x10A
} CARD_SLOT;

// The save image, 0x1F00 bytes at the start of Cd_ring_buf (Save_image). Six checksummed
// blocks of words, each followed by a key and three sums (save_sum_set sets them, save_sum_check
// checks them): words 0x000-0x05B (key 0x05C), 0x060-0x06B (0x06C), 0x070-0x07B (0x07C),
// 0x080-0x0DB (0x0DC), 0x0E0-0x74B (0x74C), 0x750-0x7B7 (0x7B8); words 0x7BC-0x7BF check the
// keys and sums. Other files keep their own blocks in it: code_8003AC24 at 0x480, code_8005C258
// at 0x1280. Fields are named after the Game_work fields Save_image_restore restores from them.
typedef struct
{
    uint8 unk000[0x128];
    uint32 unk010;   // 0x128
    uint32 timer_14; // 0x12C
    uint16 unk018;   // 0x130
    sint16 unk01A;   // 0x132
    uint8 unk134[0x180 - 0x134];
    uint32 timer_0c; // 0x180
    uint32 money;    // 0x184
    uint32 unk020;   // 0x188
    uint32 unk024;   // 0x18C
    uint32 unk04C;   // 0x190
    sint8 stage_no;  // 0x194
    sint8 area_no;   // 0x195
    sint8 sce_no;    // 0x196
    sint8 unk053;    // 0x197
    uint8 unk054;    // 0x198
    uint8 unk055;    // 0x199
    sint8 unk056;    // 0x19A
    uint8 unk19B;
    sint8 mono;   // 0x19C
    uint8 unk059; // 0x19D
    sint8 unk05A; // 0x19E
    sint8 unk05B; // 0x19F
    uint8 unk1A0[0x1C0 - 0x1A0];
    SVECTOR pos;  // 0x1C0: D_800C3558.pos
    sint16 ang_y; // 0x1C8: D_800C3558.ang_y
    uint8 unk1CA[0x1D0 - 0x1CA];
    sint16 unk060; // 0x1D0
    uint16 unk062; // 0x1D2: Game_work 0x62
    uint8 unk1D4[0x1E0 - 0x1D4];
    uint32 unk064; // 0x1E0: Game_work 0x64-0x67
    uint8 unk1E4[0x200 - 0x1E4];
    uint8 unk07C; // 0x200
    uint8 unk07D; // 0x201
    uint8 unk202[2];
    sint8 unk078; // 0x204: Game_work.unk078.b.flag
    sint8 unk079; // 0x205
    sint8 unk07A; // 0x206
    uint8 unk07B; // 0x207
    uint8 unk208[0x1D00 - 0x208];
    uint32 unk028[6]; // 0x1D00
    uint16 unk040[6]; // 0x1D18
    uint8 unk1D24[0x1D40 - 0x1D24];
    GAME_RECORD records_84[15]; // 0x1D40 (func_80067E6C)
    uint8 unk1E30[0x1F00 - 0x1E30];
} SAVE_IMAGE;

#define Save_image (*(SAVE_IMAGE *)Cd_ring_buf)
#define Save_words ((uint32 *)Cd_ring_buf) // the save image as words (the checksums)

// The checksum of save image words [first, key) into sum[0..2]: sum[0] adds each word with its
// halves swapped, sum[1] (odd words) and sum[2] (even words) add the word xor (key word + its
// index). Uses the caller's locals save (Save_words), i, w and sum[3].
#define SAVE_SUM(first, key)                                                                                                               \
    for (i = 0; i < 3; i++)                                                                                                                \
    {                                                                                                                                      \
        sum[i] = 0;                                                                                                                        \
    }                                                                                                                                      \
    for (i = (first); i < (key); i++)                                                                                                      \
    {                                                                                                                                      \
        w = save[i];                                                                                                                       \
        sum[0] += (w << 16) | (w >> 16);                                                                                                   \
        if (i & 1)                                                                                                                         \
        {                                                                                                                                  \
            sum[1] += w ^ (save[(key)] + i);                                                                                               \
        }                                                                                                                                  \
        else                                                                                                                               \
        {                                                                                                                                  \
            sum[2] += w ^ (save[(key)] + i);                                                                                               \
        }                                                                                                                                  \
    }

// A sprite primitive (debug.h's DEBUG_PRIM words) in a POLY_FT4-sized slot of the scratchpad's
// primitive buffer (Map_prim_ptr), as func_8006430C lays them out.
typedef struct
{
    uint32 tag;
    uint32 rgbc;
    uint32 xy;
    uint32 uv_clut;
    uint32 wh;
    uint8 pad14[0x14];
} ICON_PRIM; // 0x28

#define Icon_prim_ptr (*(ICON_PRIM **)0x1F800070)

// func_8006430C: uv and clut of the image shown in place of a sprite whose flags aren't set.
#define ICON_UV_CLUT_NONE 0x3C484080

typedef void (*CODE_8006430C_FUNC)(CODE_8006430C_WORK *wp);
// routine_0 handlers (D_8008FD10); func_800665FC returns their result.
typedef sint32 (*CODE_8006430C_ROUTINE_FUNC)(CODE_8006430C_WORK *wp);

extern CODE_8006430C_WORK D_80098910;           // the module's state
extern CODE_8006430C_ROUTINE_FUNC D_8008FD10[]; // routine_0 handlers
extern CODE_8006430C_FUNC D_8008FD20[];         // routine_1 steps of routines 1 and 2

// The four SPEC_ENT tables (code_800456D8.h's D_80098844, D_8009884C, D_80098928, D_8009892C)
// func_8006471C selects: one set when Game_work.unk05B is 2, the other otherwise.
extern SPEC_ENT *D_8008EDC4[];
extern SPEC_ENT *D_8008EF64[];
extern SPEC_ENT *D_8008EFC4[];
extern SPEC_ENT *D_8008F048[];
extern SPEC_ENT *D_8008F060[];
extern SPEC_ENT *D_8008F200[];
extern SPEC_ENT *D_8008F260[];
extern SPEC_ENT *D_8008F2E4[];

// Set by func_80067E18 (0x3F00, 0x18, 0x80, 0).
extern sint32 D_800BE428;
extern sint32 D_800BE42C;
extern sint32 D_800BE430;
extern sint32 D_800BE434;

// func_80067D10 fills entries 0, 2, 3, 5, 6, 8 and 9 of D_8008FA84 from D_80098124, indexed by
// D_80098A04 + 1 and by the bytes D_80098800-D_80098805.
extern uint16 D_8008FA84[];
extern uint16 D_80098124[];
extern uint8 D_80098800;
extern uint8 D_80098801;
extern uint8 D_80098802;
extern uint8 D_80098803;
extern uint8 D_80098804;
extern uint8 D_80098805;

// Memory card save header pieces card_header_set copies into a block's first sector: the icon's
// 16x16 4-bit image (0x80 bytes, sector offset 0x80) and its CLUT (0x20 bytes, offset 0x60).
extern uint8 D_8008F9BC[0x80];
extern uint8 D_8008FA3C[0x20];

// The five save slots, and what func_80067884 resets them from: the card header's title
// D_8008FA64, D_8008CE94's 13-byte rows and D_80097FFC's 8 bytes. D_8008D168 and D_8008D184
// point to each slot's place in the encoded text (D_8008B304, ...); the byte two before
// D_8008D168[i] is the slot's number glyph.
extern CARD_SLOT D_800BAF38[5];
extern uint8 D_8008FA64[];
extern uint8 D_8008CE94[][13];
extern uint8 D_80097FFC[8];
extern uint8 *D_8008D168[5];
extern uint8 *D_8008D184[5];

// A new game's Game_work.records_84 (func_80067E6C): ids and data of entries 0-8, then of
// entries 9-11 and 12-14.
extern sint32 D_8008FF64[9];
extern uint16 D_8008D034[9][4];
extern sint32 D_8009813C[3];
extern sint32 D_80098148[3];
extern uint16 D_8008D07C[6][4];

// Memory card device names by port: "bu00:", "bu10:" (in .sdata, D_800980A4 and D_8009809C).
extern char *D_8008FA5C[2];

// A 128-byte memory card sector buffer; func_80064FF0 writes block 0 from it with the first two
// bytes (D_8009AB31 is the second, reached by its own label) set to 0xFF.
extern uint8 D_8009AB30[];
extern uint8 D_8009AB31;

void Card_init(void);          // opens and enables the memory card events, starts the card BIOS and file system
void func_800665E8(void);      // clears active_0 and the word at 0x4
void Save_image_restore(void); // copies the loaded save image into Game_work and the area entry

#endif
