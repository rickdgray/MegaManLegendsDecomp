#ifndef SHL05_H
#define SHL05_H

#include "common.h"
#include "shl/shl.h"

// Per-level weapon values in ROCK_NEO.EXE (8-byte records).
typedef struct
{
    sint16 flags_0; // 00
    sint16 value_2; // 02
    sint16 speed_4; // 04
    sint16 value_6; // 06
} SHL05_LEVEL;

// Sprite scales, cycled by routine_1.
typedef struct
{
    sint32 scale_96;
    sint32 scale_97;
} SHL05_SCALE;

// An effect slot carrying a copy of the shot's sprite.
typedef struct
{
    sint8 routine_0; // 00
    uint8 reserved01;
    uint8 kind_2; // 02
    uint8 flag_3; // 03
    uint8 reserved04[0x10];
    SHL_SPRITE spr; // 14
} SHL05_FX;

extern SHL05_LEVEL D_80089C6C[];

extern SHL_BOX D_800D95B0;
extern SHL05_SCALE D_800D95BC[6];
extern SHL_FUNC D_800D95EC[]; // routine_0 handlers
extern uint32 D_800D9600;     // distance to the player, scaled to 0x80

sint16 func_800D90B0(SHL_WORK *wp);
void func_800D935C(SHL_WORK *wp);
void func_800D9450(SHL_WORK *wp, SHL_FX *fx);
void func_800D94C0(SHL_WORK *wp);
sint32 func_800D9508(SVECTOR *a, SVECTOR *b);
void func_800D9574(SHL_WORK *wp, SHL_FX *fx);

#endif // SHL05_H
