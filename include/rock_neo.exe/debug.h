#ifndef DEBUG_H
#define DEBUG_H

#include "common.h"
#include "psyq/libgte.h"
#include "code_8001F828.h"

// One row of the debug menu (five of them in DEBUG_WORK).
typedef struct
{
    sint8 state_0; // 3 at init, 2 when the row is (re)selected
    uint8 pad1[3];
    sint8 value_4;
    uint8 pad5;
    sint16 index_6;
} DEBUG_ENTRY; // 0x8

// The debug menu's state (Debug_work).
typedef struct
{
    uint8 routine_0;
    uint8 routine_1;
    uint8 routine_2;
    uint8 routine_3;
    uint16 on_4;  // 0x04: buttons pressed this frame (Joy1's PAD_ON), copied by func_800629F0
    uint16 now_6; // 0x06: buttons held (Joy1's PAD_NOW)
    sint8 mode_8; // 0x08: index of D_8008DBD4
    sint8 sel_9;  // 0x09: selected row
    uint8 pad_a[2];
    sint8 sel_c; // 0x0C
    sint8 value_d;
    uint8 pad_e[2];
    DEBUG_ENTRY entry[5]; // 0x10
} DEBUG_WORK;             // 0x38

typedef sint32 (*DEBUG_FUNC)(DEBUG_WORK *wp);

// One line of a debug menu row's option list, printed with Print(pos, text).
typedef struct
{
    uint32 pos;    // Print's position word (XYC); DEBUG_MENU_CUR marks the current setting
    char text[12]; // text[0] is the cursor column: '>' on the selected line, ' ' otherwise
} DEBUG_MENU_LINE; // 0x10

// Colour bit of a menu line's position word: set on the line of the current setting.
#define DEBUG_MENU_CUR XYC(0, 0, 2)

// A sprite's screen position: copied as a word (func_800640F0) or read as x and y (func_8006430C).
typedef union
{
    uint32 word;
    struct
    {
        sint16 x;
        sint16 y;
    } s;
} LOGO_XY;

// One sprite of a logo (0x10 bytes); a negative head ends the list.
typedef struct
{
    // High byte = type: for func_800640F0, 1 blinks with System_timer, 2 blinks with
    // Game_work.timer_0c, 3 grows with Player_work's life_max; for func_8006430C, 0-13 picks how the
    // scene flags at flag_2 choose the image (low byte = the slot in a grid of 6 columns).
    uint16 head_0;
    sint16 flag_2; // 0x02: first of three scene flags (func_8006430C)
    LOGO_XY xy_4;
    uint32 uv_8;
    uint32 wh_c;
} LOGO_SPRITE;

// One logo slot (D_800C3528[4]).
typedef struct
{
    sint8 active_0;
    sint8 flag_1;
    sint8 kind_2; // index of D_8008DD64
    uint8 pad3;
    sint8 value_4; // 0x04: low byte of the GPU code word that func_800640F0 puts in the draw-mode primitive
    sint8 value_5; // 0x05: ordering table index
    uint8 pad6[2];
    LOGO_SPRITE *sprites_8; // 0x08: list of sprite records
} LOGO_WORK;                // 0xC

typedef void (*LOGO_FUNC)(LOGO_WORK *wp);

// One entry of D_8008ECDC, the logos Game_logo_set can open (picked by its argument's low byte).
typedef struct
{
    uint16 kind_0;          // LOGO_WORK.kind_2
    uint16 value_2;         // LOGO_WORK.value_4
    LOGO_SPRITE *sprites_4; // LOGO_WORK.sprites_8
} LOGO_DEF;

// A raw primitive in the scratchpad's primitive buffer: tag, rgb + code, xy, uv + clut, wh.
typedef struct
{
    uint32 tag;
    uint32 rgbc;
    uint32 xy;
    uint32 uv_clut;
    uint32 wh;
} DEBUG_PRIM;

// Next free byte of the primitive buffer, stepped by DEBUG_PRIM (see Map_prim_ptr in scratch.h).
#define Debug_prim_ptr (*(DEBUG_PRIM **)0x1F800070)

// The fade request (D_800987B0). func_80063BA8 clears the word at +0 and D_800987B4/B8.
typedef union
{
    uint32 word;
    sint8 flag;
} DEBUG_FADE_HEAD;

// The same request viewed through a pointer (func_80063BC8).
typedef struct
{
    uint8 flag_0; // nonzero while the screen is fading
    uint8 mode_1; // bit 0: keep Player_work's unk00 bit 1 clear; bits 2-4: what func_80063C30 does
                  // when the message ends
    uint8 pad2[2];
    uint8 task_no_4; // 0x04: Moji task the message runs in (also D_800987B4's low byte)
    uint8 mess_no_5; // 0x05: message number (also D_800987B5), started by func_80063C30
    sint16 value_6;
    SVECTOR *pos_8; // also D_800987B8: moji's func_80055868 aims the camera at it
} DEBUG_FADE;

extern DEBUG_FADE_HEAD D_800987B0;
extern uint8 D_800987B1;
extern sint16 D_800987B2;
extern uint32 D_800987B4;
extern uint8 D_800987B5;
extern uint32 D_8008DD54[]; // Moji_flag bit of each Moji task (func_80063C30)
extern SVECTOR *D_800987B8; // DEBUG_FADE.pos_8 by its own label
extern DEBUG_WORK Debug_work;
extern DEBUG_FUNC D_8008DBD4[];        // debug menu modes
extern DEBUG_FUNC D_8008DBE0[];        // per-row handlers
extern DEBUG_MENU_LINE D_8008DBF4[14]; // row 1's options: Player_work[0].weapon_right_no (func_80062CF0)
extern DEBUG_MENU_LINE D_8008DCD4[2];  // row 0's options: Player_work[0].unk171 (func_80063058)
extern DEBUG_MENU_LINE D_8008DCF4[2];  // row 2's options: Player_work[0].unk16A (func_80063334)
extern DEBUG_MENU_LINE D_8008DD14[2];  // row 3's options: Game_work.unk054 (func_80063604)
extern DEBUG_MENU_LINE D_8008DD34[2];  // row 4's options: Player_work[0].unk16B (func_800638D8)
extern LOGO_FUNC D_8008DD64[];         // logo kinds
extern LOGO_WORK D_800C3528[4];
extern LOGO_DEF D_8008ECDC[];

void func_800629E0(void);
void func_800629F0(void);
sint32 func_80062A50(DEBUG_WORK *wp);
sint32 func_80062B04(DEBUG_WORK *wp);
sint32 func_80062C6C(DEBUG_WORK *wp);
sint32 func_80062CF0(DEBUG_WORK *wp);
sint32 func_80063058(DEBUG_WORK *wp);
sint32 func_80063334(DEBUG_WORK *wp);
sint32 func_80063604(DEBUG_WORK *wp);
sint32 func_800638D8(DEBUG_WORK *wp);
void func_80063BA8(void);
void func_80063BC8(void *pos, sint32 mode, sint32 value_4, sint32 value_5);
void func_80063C30(void);
void func_80063EF0(void); // clears D_800C3528's four 12-byte entries
void Game_logo_kill(sint32 index);
void Game_logo_set(sint32 index, sint32 arg);
void func_80064060(void); // called once per frame by main
void func_800640F0(LOGO_WORK *wp);

#endif
