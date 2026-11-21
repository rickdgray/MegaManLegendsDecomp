#ifndef DEBUG_H
#define DEBUG_H

#include "common.h"

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

// One sprite of a logo (0x10 bytes); a negative head ends the list.
typedef struct
{
    uint16 head_0; // high byte = type (1 blinks with System_timer, 2 blinks with Game_work.timer_0c, 3 grows with Player_work's unkB0)
    uint8 pad2[2];
    uint32 xy_4;
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
    uint8 flag;
} DEBUG_FADE_HEAD;

// The same request viewed through a pointer (func_80063BC8).
typedef struct
{
    uint8 flag_0; // nonzero while the screen is fading
    uint8 mode_1;
    uint8 pad2[2];
    sint8 value_4;
    sint8 value_5;
    sint16 value_6;
    void *pos_8;
} DEBUG_FADE;

extern DEBUG_FADE_HEAD D_800987B0;
extern uint8 D_800987B1;
extern sint16 D_800987B2;
extern uint32 D_800987B4;
extern uint32 D_800987B8;
extern DEBUG_WORK Debug_work;
extern DEBUG_FUNC D_8008DBD4[]; // debug menu modes
extern DEBUG_FUNC D_8008DBE0[]; // per-row handlers
extern LOGO_FUNC D_8008DD64[];  // logo kinds
extern LOGO_WORK D_800C3528[4];

void func_800629E0(void);
void func_800629F0(void);
sint32 func_80062B04(DEBUG_WORK *wp);
sint32 func_80062C6C(DEBUG_WORK *wp);
void func_80063BA8(void);
void func_80063BC8(void *pos, sint32 mode, sint32 value_4, sint32 value_5);
void func_80063EF0(void); // clears D_800C3528's four 12-byte entries
void func_80064060(void); // called once per frame by main
void func_800640F0(LOGO_WORK *wp);

#endif
