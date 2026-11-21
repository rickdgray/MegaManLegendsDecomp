#ifndef SUB_SCRN_H
#define SUB_SCRN_H

// The sub screen (status, buster parts, map) and its map screen: sub_scrn.c, whose end Capcom's
// source shows (disc/tcrf.txt). Names follow that source.

#include "common.h"
#include "psyq/libgpu.h"
#include "psyq/libgte.h"

// Flags of Sub_screen_basic_param_set_sub / Sub_screen_status_param_set_sub, over the digit
// count in the low byte. Digits are drawn from the units leftwards.
#define NUM_DIGITS_MASK  0xFF
#define NUM_NO_LEAD_ZERO 0x100 // leave out the zeros left of the number
#define NUM_NO_ZERO      0x200 // with NUM_NO_LEAD_ZERO, leave out the units digit of 0 too

// Whole-word primitive stores, as Capcom's sub_scrn.c writes them (one sw each).
// The tag with no link yet: only the length in words.
#define SET_TAG_LEN(p, len) (*(u_long *)(p) = (len) << 24)
// The tag: link to the primitive right after p, and the length in words.
#define SET_TAG_NEXT(p, len) (*(u_long *)(p) = ((u_long)((p) + 1) & 0xFFFFFF) | ((len) << 24))
// The code and color word (r0, g0, b0, code).
#define SET_CODE_RGB(p, code, r, g, b) (*(u_long *)&(p)->r0 = ((code) << 24) | ((b) << 16) | ((g) << 8) | (r))
// x0 and y0, given packed (x | y << 16).
#define SET_XY0_WORD(p, xy) (*(u_long *)&(p)->x0 = (xy))
// w and h.
#define SET_WH_WORD(p, _w, _h) (*(u_long *)&(p)->w = ((_h) << 16) | (_w))
// u0, v0 and the CLUT.
#define SET_UV0_CLUT(p, u, v, clut) (*(u_long *)&(p)->u0 = (u) | ((v) << 8) | ((clut) << 16))
// A halfword u, v pair (POLY_FT4's u1..u3, which have no CLUT/tpage beside them to pack).
#define SET_UV_HALF(uv, u, v) (*(u_short *)&(uv) = (u) | ((v) << 8))

// The highest stat level the buster parts can add up to (the gauges show level * 10).
#define RB_LEVEL_MAX        7
#define RB_REPEAT_LEVEL_MAX 4 // rapid

// Draw mode command (GP0 0xE1) for a texture page.
#define DRAW_MODE_CODE(tpage) (0xE1000000 | (tpage))

// One stat line of the sub screen (attack, energy, range, rapid, special). The _0 fields are the
// values of what is equipped, the _1 fields those with the parts or weapon under the cursor
// (sub_screen_rb_parts_calc_sub00 / _sub01).
typedef struct
{
    uint8 now_0;  // 0x0: set to val_2 by func_80060248
    uint8 end_0;  // 0x1: Capcom's attack_end_0, ...
    uint8 val_2;  // 0x2
    uint8 now_1;  // 0x3: set to val_5 by func_80060248
    uint8 end_1;  // 0x4: Capcom's attack_end_1, ...
    uint8 val_5;  // 0x5
    uint8 infi_0; // 0x6: end_0 is "infinite" (the table held 0xFF; end_0 is then 88)
    uint8 val_7;  // 0x7
} SUB_STATUS;

// The sub screen's state. Passed in by its callers (func_800600CC, func_80060618); where it lives
// is not traced yet. Only the fields decompiled code uses are named.
typedef struct
{
    uint8 routine_0; // 0x0
    uint8 routine_1; // 0x1
    uint8 routine_2; // 0x2
    uint8 routine_3; // 0x3
    uint8 unk4[2];
    uint8 mode_6; // 0x6: set to 3 by func_80060248
    uint8 unk7[0x10 - 0x7];
    SUB_STATUS attack;  // 0x10
    SUB_STATUS bullet;  // 0x18: energy
    SUB_STATUS dist;    // 0x20: range
    SUB_STATUS repeat;  // 0x28: rapid
    SUB_STATUS special; // 0x30
} SUB_SCREEN_WORK;

// One buster part: the levels it adds to the buster's stats (times 10 on the sub screen's gauges).
typedef struct
{
    sint8 attack_level; // 0x0
    sint8 bullet_level; // 0x1: energy
    sint8 dist_level;   // 0x2: range
    sint8 repeat_level; // 0x3: rapid
    uint8 unk4[4];
} RB_PARTS;

// The map screen's state (Map_screen_init, Map_screen_task).
typedef struct
{
    sint8 routine_0; // 0x0: lb (Map_screen_task)
    uint8 routine_1; // 0x1
    uint8 routine_2; // 0x2
    uint8 routine_3; // 0x3
    sint8 type;      // 0x4: which map set: 0 before scenario 9, 1 from it on
    sint8 type2;     // 0x5: the map shown within the set
    uint8 pad6[2];
} MAP_SCREEN_WORK;

// Pool common (0x800987F0), tentative in sub_scrn.c: Map_screen_init reaches routine_0 through $gp.
extern MAP_SCREEN_WORK Map_screen_work;

// Buster parts by id - 1 (Player_work[0].rb_parts_sort_data / rb_parts_equip_data). Defining
// file unknown: it is in the small tables after code_8006430C's .data (notes/rock_neo_files.md),
// and Capcom's sub_scrn.c declares it extern.
extern RB_PARTS Rock_buster_parts_tbl[];

// The cursor's place on the map screen, per stage (vx, vy).
extern DVECTOR D_8008DB34[];

SPRT *Sub_screen_basic_param_set_sub(SPRT *ptr, uint32 pos, sint32 num, sint32 flag);
SPRT *Sub_screen_status_param_set_sub(SPRT *ptr, uint32 pos, sint32 num, sint32 flag);
void Sub_screen_back_ground_set(void);
void Map_screen_init(void);

#endif // SUB_SCRN_H
