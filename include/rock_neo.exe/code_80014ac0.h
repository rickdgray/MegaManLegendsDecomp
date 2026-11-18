#ifndef ROCK_NEO_CODE_80014AC0_H
#define ROCK_NEO_CODE_80014AC0_H

#include "game.h"
#include "code_800133d8.h"

typedef struct
{
    sint16 *commands;
    uint16 index;
    sint16 timer;
    sint16 turn;
    sint16 scale_x, scale_y, scale_z;
    uint8 reserved10[2];
    uint8 fixed_motion;
    uint8 frame, frame_prev;
    uint8 reserved15[3];
} CODE14_SCRIPT;

typedef union
{
    sint32 value;
    struct
    {
        uint16 fraction;
        sint16 integer;
    } words;
} CODE14_FIXED;

typedef struct
{
    CODE14_FIXED x, y, z, pad;
} CODE14_VECTOR;

typedef struct CODE14_WORK
{
    uint8 flags;
    uint8 reserved01;
    uint8 kind;
    uint8 variant;
    uint16 routine04;
    uint8 reserved06[2];
    uint8 routine08;
    uint8 reserved09[3];
    sint8 script_kind;
    sint8 sound_enabled;
    sint8 sound_kind;
    sint8 sound_timer;
    uint32 value10;
    PL_SHORT_VECTOR position;
    CODE14_VECTOR position_fixed;
    PL_SHORT_VECTOR position_prev;
    CODE14_VECTOR position_fixed_prev;
    uint16 velocity_x, velocity_y, velocity_z, velocity_pad;
    uint16 acceleration_x, acceleration_y, acceleration_z, acceleration_pad;
    PL_SHORT_VECTOR rotation;
    PL_SHORT_VECTOR rotation_prev;
    uint32 value64;
    uint8 reserved68[0x10];
    uint32 *table78;
    uint8 reserved7c[0x30];
    uint8 anim, anim_prev;
    uint8 reservedae[0x62];
    uint8 frame;
    uint8 reserved111[0x47];
    PL_SHORT_VECTOR scale;
    uint8 reserved160[0x1E8];
    CODE14_SCRIPT script;
    uint8 reserved360[0x60];
} CODE14_WORK;

typedef void (*CODE14_FUNC)(CODE14_WORK *wp, CODE14_SCRIPT *script);

extern CODE14_FUNC D_80082104[];
extern sint16 **D_800820E0[];
extern uint32 D_800979FC[];

void func_80031824(GAME_WORK_3C0 *wp);
void func_8002F9C4(CODE14_WORK *wp, sint32 arg);
void func_800150E0(CODE14_WORK *wp, CODE14_SCRIPT *script);
void func_80014BCC(CODE14_WORK *wp, CODE14_SCRIPT *script);
CODE14_WORK *func_80031418(void);
void func_8002FEA4(CODE14_WORK *wp, sint16 x, sint16 y, sint16 z);
void func_800322A8(CODE14_WORK *wp, uint8 anim, sint32 arg);
void func_80032488(CODE14_WORK *wp);

#endif
