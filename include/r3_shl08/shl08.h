#ifndef SHL08_H
#define SHL08_H

#include "common.h"
#include "shl/shl.h"

// The homing shot: SHL_WORK's header and model data, a target and a four-point trail.
typedef struct
{
    uint8 flags_0; // 00
    uint8 value_1; // 01
    uint8 reserved02;
    uint8 type_3; // 03: 0x80 set while homing
    uint8 reserved04[2];
    uint8 flags_6; // 06
    uint8 reserved07;
    uint8 routine_0; // 08
    uint8 reserved09[2];
    uint8 timer_b; // 0B
    sint8 index_c; // 0C
    sint8 bit_d;   // 0D
    uint8 reserved0e[6];
    SVECTOR pos;        // 14
    SHL_FIXED fpos;     // 1C
    SVECTOR old_pos;    // 2C
    SHL_FIXED old_fpos; // 34
    SVECTOR vel;        // 44
    sint16 ax, ay, az;  // 4C
    uint8 reserved52[0x12];
    sint16 rot_y; // 64
    uint8 reserved66[0x12];
    SHL_BOX *box_78; // 78
    sint16 hit_7c;   // 7C
    uint8 reserved7e[0xA];
    SHL_MODEL mdl; // 88
    union
    {
        struct
        {
            uint32 w0, w1;
        } w;
        SVECTOR pos;
    } target;      // BC
    uint32 col_c4; // C4
    uint32 col_c8; // C8
    uint8 reservedcc[8];
    SVECTOR trail[4]; // D4
} SHL08_WORK;

// A coloured 3D line packet from Billboard_line_get.
typedef struct
{
    uint32 xy0;       // 00
    uint32 code_rgb0; // 04
    uint32 xy1;       // 08
    uint32 rgb1;      // 0C
    uint32 z0z1;      // 10
    uint32 reserved14;
    uint32 tpage; // 18
} SHL08_LINE;

typedef void (*SHL08_FUNC)(SHL08_WORK *wp);

extern SHL_BOX D_800D90CC;
extern uint16 D_800D90D8[];     // speed by Player_work.value_536
extern SHL08_FUNC D_800D90E8[]; // routine_0 handlers
extern uint8 D_800D90F0[];      // effect value by Player_work.value_534
extern uint32 D_800D90F8[];     // trail colours

SHL08_LINE *Billboard_line_get(void);

void func_800D8E38(SHL08_WORK *wp);
void func_800D8F0C(SHL08_WORK *wp);
void func_800D8F98(SHL08_WORK *wp);

#endif // SHL08_H
