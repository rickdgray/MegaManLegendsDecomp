#ifndef CODE_8005C258_H
#define CODE_8005C258_H

// code_8005C258.c's subsystem (not identified yet; rename with the file).

#include "common.h"

// One of the six 0x24-byte slots at D_800BBD78 (func_8005C258 clears all six). func_8005C2B8 runs
// slot 1 through func_8005C868; slots 2-4 are opened by func_8005D574/func_8005D620 for an owner
// object and closed by func_8005D6E8.
typedef struct
{
    sint8 state_0; // 0x00: 0 = free; 3 when opened
    uint8 unk01[3];
    uint8 routine_4; // 0x04: handler index (func_8005C720, func_8005C868, func_8005C978)
    uint8 unk05[0xC - 0x5];
    uint8 kind_C; // 0x0C: set by the opener (overlays pass 0x50, 0x51, 0x60, 0x81)
    uint8 flag_D; // 0x0D: set to 1 when opened
    uint8 unk0E;
    uint8 count_F;   // 0x0F: frame counter (func_8005C8A4)
    uint32 color_10; // 0x10: code and colour word of a POLY_FT4 (func_8005D620's callers pass 0x2C......)
    uint8 unk14[4];
    sint16 x_18;
    sint16 y_1A;
    uint8 unk1C[4];
    void *owner_20; // 0x20: the object that opened the slot (func_8005D6E8 closes by owner)
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

// Record of D_8008D19C (12 bytes, ended by stage_no 0xFF): matched against Game_work's stage_no
// and area_no by func_8005DC10.
typedef struct
{
    uint8 stage_no;
    uint8 area_no;
    uint8 unk02[2];
    sint32 val_4; // 0x04: copied to D_8009882C on a match
    uint8 unk08[4];
} AREA_ENT;

// A rectangle in screen coordinates, read with lhu (unsigned, unlike PsyQ's RECT).
// func_8005E9F8 fills a POLY_F4 over it.
typedef struct
{
    uint16 x, y, w, h;
} SCREEN_RECT;

// The six slots func_8005C258 clears (Mem_clear up to the word at +0xD4); it sets slot 0's
// state_0 here and slot 1's as D_800BBD9C. The globals below lie inside the slots but are reached
// as separate symbols (each access has its own lui), by code_8001F828, code_80027678, main and
// this file.
extern SLOT_WORK D_800BBD78[6];

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

extern sint32 D_80098B18; // pool; bit 1 lets the player turn to the lock-on target (func_8003EEC0)

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
void func_8005DC10(sint32 arg0);                                               // also called from overlays

#endif // CODE_8005C258_H
