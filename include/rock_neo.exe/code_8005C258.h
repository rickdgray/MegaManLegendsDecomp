#ifndef CODE_8005C258_H
#define CODE_8005C258_H

// code_8005C258.c's subsystem (not identified yet; rename with the file).

#include "common.h"
#include "psyq/libgpu.h"
#include "player.h"

// One of the six 0x24-byte slots at D_800BBD78 (func_8005C258 clears all six). Gauge_update runs
// slot 1 through func_8005C868; slots 2-4 are opened by func_8005D574/func_8005D620 for an owner
// object and closed by func_8005D6E8.
typedef struct
{
    sint8 state_0; // 0x00: 0 = free; 3 when opened
    uint8 unk01[3];
    uint8 routine_4; // 0x04: handler index (func_8005C720, func_8005C868, func_8005C978)
    uint8 unk05[0x8 - 0x5];
    sint8 anim_8;  // 0x08: life_gauge_draw: blink frame, 0-11
    sint8 timer_9; // 0x09: life_gauge_draw: frames left of the face animation (flag_D 2 and 3)
    sint8 idle_A;  // 0x0A: slot 0: frames with kind_C set (func_8005C75C)
    sint8 still_B; // 0x0B: slot 0: frames the player has not moved (func_8005C75C)
    // 0x0C: set by the opener (overlays pass 0x50, 0x51, 0x60, 0x81). The gauges read it as a
    // shift: units per cell (func_8005D0FC; owner_life_gauge_draw: shift << 4 | sprite set).
    uint8 kind_C;
    uint8 flag_D;    // 0x0D: set to 1 when opened; the gauges add (x_18, y_1A) while it is set
    uint8 has_pos_E; // 0x0E: the gauges draw at (x_14, y_16) instead of their default place
    uint8 count_F;   // 0x0F: frame counter (func_8005C8A4)
    uint32 color_10; // 0x10: code and colour word of a POLY_FT4 (func_8005D620's callers pass 0x2C......)
    sint16 x_14;
    sint16 y_16;
    sint16 x_18; // 0x18: slot 0: frame counter (func_8005C75C)
    sint16 y_1A;
    uint8 unk1C[4];
    // 0x20: the object that opened the slot (func_8005D6E8 closes by owner). owner_life_gauge_draw draws
    // its life out of life_max, at PL_WORK's offsets; the overlays pass their own objects.
    PL_WORK *owner_20;
} SLOT_WORK;

// Handlers for a SLOT_WORK, indexed by its routine_4 (func_8005C720).
typedef void (*SLOT_FUNC)(SLOT_WORK *wp);

// Sprite drawn as a POLY_FT4 by func_8005D298 and func_8005D39C (0x14 bytes).
typedef struct
{
    u_long color; // 0x00: code and colour word of the POLY_FT4
    sint16 x_off; // 0x04: offset from the drawing position
    sint16 y_off;
    sint16 w; // 0x08: size in the texture (and on screen unless the caller gives one)
    sint16 h;
    uint8 u; // 0x0C: copied to the primitive as one word with v and clut
    uint8 v;
    uint16 clut;
    uint8 unk10[2];
    uint16 tpage; // 0x12
} SLOT_SPRITE;

// Record of D_8008D19C (12 bytes, ended by stage_no 0xFF): an area's map, matched against
// Game_work's stage_no and area_no by func_8005DC10. The map is a grid of cells of 0x200 world
// units from (x, z).
typedef struct
{
    uint8 stage_no;
    uint8 area_no;
    uint8 width;     // 0x02: in cells
    uint8 height;    // 0x03
    uint8 *hidden_4; // 0x04: one bit per cell (0x80 first), set while the cell is unexplored; points into
                     // D_800BC9B8. Copied to D_8009882C on a match.
    sint16 x;        // 0x08: world x and z of cell (0, 0)
    sint16 z;
} AREA_ENT;

// The 3x3 cells around a cell, as offsets (D_80098038: x, D_80098044: z); copied to the stack whole.
typedef struct
{
    sint8 d[9];
} CELL_OFS;

// POLY_G4 and POLY_FT4 as words: this file writes their color, position and texture words whole.
// A struct field, not a cast through a byte field (*(u_long *)&p->r1): GCC 2.7 gives struct
// fields their own alias class, and the scheduler's order depends on it (func_8005EAA8).
typedef struct
{
    u_long tag;
    u_long rgbc0; // r0, g0, b0, code
    u_long xy0;
    u_long rgb1;
    u_long xy1;
    u_long rgb2;
    u_long xy2;
    u_long rgb3;
    u_long xy3;
} POLY_G4_WORDS;

typedef struct
{
    u_long tag;
    u_long rgbc0; // r0, g0, b0, code
    u_long xy0;
    u_long uv0_clut;
    u_long xy1;
    u_long uv1_tpage;
    u_long xy2;
    u_long uv2;
    u_long xy3;
    u_long uv3;
} POLY_FT4_WORDS;

#define G4_WORDS(p) ((POLY_G4_WORDS *)(p))

// Map_prim_ptr (scratch.h) stepped by a DR_AREA (area_map_draw: `area = Map_area_ptr++;`).
#define Map_area_ptr (*(DR_AREA **)0x1F800070)

// Texture of a map cell (area_map_draw): the 6x6 texels at (u, v) of the map's texture page, which
// sits at VRAM x 832 with its CLUT at (832, 249).
#define MAP_CELL_UV(p, u, v)                                                                                                               \
    ((p)->uv0_clut  = (getClut(832, 249) << 16) | ((v) << 8) | (u),                                                                        \
     (p)->uv1_tpage = (getTPage(0, 0, 832, 0) << 16) | ((v) << 8) | ((u) + 6), (p)->uv2 = (((v) + 6) << 8) | (u),                          \
     (p)->uv3 = (((v) + 6) << 8) | ((u) + 6))

// The six slots func_8005C258 clears (Mem_clear up to the word at +0xD4); it sets slot 0's
// state_0 here and slot 1's as D_800BBD9C. The globals below lie inside the slots but are reached
// as separate symbols (each access has its own lui), by code_8001F828, code_80027678, main and
// this file.
extern SLOT_WORK D_800BBD78[6];

// .sdata: 3 while the current stage and area have a D_8008D19C record (func_8005DC10); nonzero
// lets SELECT open the area map from game's func_800158F0.
extern sint32 D_80098004;

extern uint8 D_800BBD81;
// Bytes 0x800BBD84-0x800BBD87 as one array: func_8005DA1C reaches [3] through a base register
// (lui+addiu), which GCC emits for an element of an array of unknown size, but not for a scalar
// or an array declared with its size. [0]: 0/1/2 (func_8005D4C0..D4E8); [1]: state set with
// D_800BBD81; [3]: flag (func_8005D98C sets, func_8005D9C4 clears).
extern uint8 D_800BBD84[];
extern uint8 D_800BBD82;
extern uint8 D_800BBD83;
extern uint16 D_800BBD90;
extern sint16 D_800BBD94;
extern sint16 D_800BBD96;
extern uint8 D_800BBD9C;
extern uint8 D_800BBDAB;
// 0x800BBE2C-0x800BBE4B: eight words, cleared one by one by func_8005D87C; func_8005D844 sets
// bytes and halves inside them.
extern uint8 D_800BBE2C;
extern sint32 D_800BBE30;
extern sint32 D_800BBE34;
extern uint8 D_800BBE38;
extern uint8 D_800BBE39;
extern sint32 D_800BBE3C;
extern sint32 D_800BBE40;
extern sint16 D_800BBE44;
extern sint16 D_800BBE46;
extern sint32 D_800BBE48;

// Saved to and restored from Cd_ring_buf + 0x1280 (func_8005DBB4), after code_8003AC24's
// D_800BD3B8 at + 0x480.
extern sint32 D_800BC9B8[0x280];

extern SLOT_FUNC D_8008D7B4[]; // 0x8008D7B4
extern SLOT_FUNC D_8008D7C0[]; // handlers of func_8005C868, same index
extern SLOT_FUNC D_8008D7C4[]; // handlers of func_8005C978, same index

extern AREA_ENT D_8008D19C[0x40];

// Corner colors (rgb0..rgb3 words) of func_8005EAA8's two screen bands, top then bottom.
extern u_long D_8009806C[2][4];

// Sprites of the gauges.
extern SLOT_SPRITE D_8008D37C[][5]; // life_gauge_draw: the life gauge, one set per face
extern SLOT_SPRITE D_8008D570[];    // life_gauge_draw: blink frames, picked through D_80098020
extern uint8 D_8008D7C8[];          // life_gauge_draw: face per timer_9 (flag_D 2)
extern SLOT_SPRITE D_8008D5E8;      // life_gauge_draw: a full life cell
extern SLOT_SPRITE D_8008D5FC;      // life_gauge_draw: a part-full life cell
extern SLOT_SPRITE D_8008D610;      // weapon_gauge_draw
extern SLOT_SPRITE D_8008D624;
extern SLOT_SPRITE D_8008D638[2];
extern SLOT_SPRITE D_8008D660;
extern SLOT_SPRITE D_8008D674;
extern SLOT_SPRITE D_8008D688[][5]; // owner_life_gauge_draw: the owner's gauge, one set per kind_C & 0xF
extern SLOT_SPRITE D_8008D750[5];   // func_8005D0FC: the Game_work.gauge_05C gauge

extern RECT D_80098050[2]; // draw area of each display buffer (area_map_draw)

extern CELL_OFS D_80098038; // {-1, 0, 1, -1, 0, 1, -1, 0, 1}
extern CELL_OFS D_80098044; // {-1, -1, -1, 0, 0, 0, 1, 1, 1}

extern sint32 D_80098B18; // pool; bit 1 lets the player turn to the lock-on target (func_8003EEC0)

void func_8005C258(void);                      // clears the six slots of D_800BBD78; also called from code_800133D8
void func_8005D528(void);                      // also called from player
void func_8005D9C4(void);                      // also called from sub_scrn
void func_8005D97C(void);                      // clears D_800BBDAB; also called from code_8004324C
sint32 func_8005DA1C(sint32 arg0);             // also called from moji
sint32 func_8005DA78(sint32 arg0);             // also called from moji
sint32 Player_weapon_bullet_fill(sint32 arg0); // also called from moji
sint32 func_8005D8C4(sint32 arg0);             // also called from player and moji
sint32 func_8005D938(void);                    // D_800BBD84[3]; also called from player
void func_8005D98C(void);                      // also called from player
void func_8005D574(void *owner, sint16 x, sint16 y, uint8 kind);
void func_8005D620(void *owner, sint16 x, sint16 y, uint8 kind, uint32 color); // also called from overlays
void func_8005D6E8(void *owner);                                               // also called from overlays
void func_8005D7C0(void);                                                      // also called from overlays
void Gauge_update(void);                                                       // called from game
void func_8005DF3C(void);                                                      // resets the area map's scroll (D_800986F8, D_800986FC)
void Area_map_screen_draw(void);                                               // called from game
void func_8005EBE4(void);                                                      // called from game
void func_8005DBB4(sint32 mode);
void func_8005DC10(sint32 arg0); // also called from overlays
// The two countdowns (D_800BBD94, D_800BBD96), as ints: their callers don't sign-extend the value
// (code_80027678, code_8002E7A8).
sint32 func_8005EBC4(void);
sint32 func_8005EBD4(void);
void func_8005EBA4(sint16 value); // sets D_800BBD94; called from sub_scrn
void func_8005EBB4(sint16 value); // sets D_800BBD96; called from sub_scrn
void func_8005D4C0(void);         // D_800BBD84[0] = 1
// D_800BBD84[3], as an int: sub_scrn's caller doesn't zero-extend the value.
sint32 func_8005D95C(void);
void func_8005DCB4(void); // per frame (game's game_frame_exec)

#endif // CODE_8005C258_H
