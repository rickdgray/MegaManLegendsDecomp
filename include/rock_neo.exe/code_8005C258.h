#ifndef CODE_8005C258_H
#define CODE_8005C258_H

// code_8005C258.c's subsystem (not identified yet; rename with the file).

#include "common.h"

// Handlers for the 9-byte object at D_800BBD78, indexed by its byte at +4 (func_8005C720).
// The pointer stays untyped until that object's layout is known.
typedef void (*SLOT_FUNC)(uint8 *wp);

// A rectangle in screen coordinates, read with lhu (unsigned, unlike PsyQ's RECT).
// func_8005E9F8 fills a POLY_F4 over it.
typedef struct
{
    uint16 x, y, w, h;
} SCREEN_RECT;

// The block func_8005C258 clears (Mem_clear up to the word at +0xD4): apparently six 0x24-byte
// slots, whose first bytes func_8005C258 sets (slot 0 here, slot 1 as D_800BBD9C). The globals
// below lie inside it but are reached as separate symbols (each access has its own lui), by
// code_8001F828, code_80027678, main and this file.
extern uint8 D_800BBD78[0xD8];

extern uint8 D_800BBD81;
// Bytes 0x800BBD84-0x800BBD87 as one array: func_8005DA1C reaches [3] through a base register
// (lui+addiu), which GCC emits for an element of an array of unknown size, but not for a scalar
// or an array declared with its size. [0]: 0/1/2 (func_8005D4C0..D4E8); [1]: state set with
// D_800BBD81; [3]: flag (func_8005D98C sets, func_8005D9C4 clears).
extern uint8 D_800BBD84[];
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

void func_8005D528(void);          // also called from player
void func_8005D9C4(void);          // also called from sub_scrn
void func_8005D97C(void);          // clears D_800BBDAB; also called from code_8004324C
sint32 func_8005DA1C(sint32 arg0); // also called from moji
sint32 func_8005DA78(sint32 arg0); // also called from moji

#endif // CODE_8005C258_H
