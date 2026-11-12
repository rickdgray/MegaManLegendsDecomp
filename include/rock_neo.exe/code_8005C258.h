#ifndef CODE_8005C258_H
#define CODE_8005C258_H

// code_8005C258.c's subsystem (not identified yet; rename with the file).

#include "common.h"

// Handlers for the 9-byte object at D_800BBD78, indexed by its byte at +4 (func_8005C720).
// The pointer stays untyped until that object's layout is known.
typedef void (*SLOT_FUNC)(uint8 *wp);

// Separate globals (each access has its own lui), used by code_8001F828, code_80027678, main
// and this file.
extern uint8 D_800BBD81;
extern uint8 D_800BBD84;
extern uint8 D_800BBD85;
extern uint8 D_800BBD87;
extern sint16 D_800BBD94;
extern sint16 D_800BBD96;
extern uint8 D_800BBDAB;
extern uint8 D_800BBE2C;
extern uint8 D_800BBE38;
extern uint8 D_800BBE39;
extern sint16 D_800BBE44;
extern sint16 D_800BBE46;

extern SLOT_FUNC D_8008D7B4[]; // 0x8008D7B4

void func_8005D528(void); // also called from player
void func_8005D9C4(void); // also called from sub_scrn

#endif // CODE_8005C258_H
