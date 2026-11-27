#ifndef SHL09_H
#define SHL09_H

#include "common.h"
#include "shl/shl.h"

// Sprite scales by bit_d.
typedef struct
{
    uint8 scale_96;
    uint8 scale_97;
} SHL09_SCALE;

// Beam scale by level: length, then width.
typedef struct
{
    sint32 len;
    sint32 width;
} SHL09_SIZE;

extern SHL_BOX D_800D96F8;
extern sint32 D_800D9704[];      // hit flags by Player_work.value_53c
extern SHL09_SCALE D_800D9724[]; // type 2 sprite scales
extern SHL_FUNC D_800D9730[];    // handlers by type
extern SHL_FUNC D_800D973C[];    // type 0 routine_0 handlers
extern SHL_FUNC D_800D9744[];    // type 1 routine_0 handlers
extern SHL_FUNC D_800D9750[];    // type 2 routine_0 handlers
extern sint32 D_800D9758[];      // beam reach by level
extern sint32 D_800D9778[];      // beam hit size by level
extern SHL09_SIZE D_800D9798[];  // beam scale by level
extern sint32 D_800D97D8[];      // hit size by level

void func_800D8F50(SHL_WORK *wp);
void func_800D922C(SHL_WORK *wp);
void func_800D9398(SHL_WORK *wp);
void func_800D942C(SHL_WORK *wp);
void func_800D947C(SHL_WORK *wp);
void func_800D9570(SHL_WORK *wp);
void func_800D9608(SVECTOR *out, sint32 speed);

#endif // SHL09_H
