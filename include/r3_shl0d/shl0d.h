#ifndef SHL0D_H
#define SHL0D_H

#include "common.h"
#include "shl/shl.h"

// The beam's own data, after the model description.
typedef struct
{
    uint8 value_bc;  // BC
    uint8 len_bd;    // BD: length in segments, eight per hit record
    sint8 value_be;  // BE
    sint8 value_bf;  // BF: speed
    sint32 size_c0;  // C0
    uint32 flags_c4; // C4
    sint32 scale_c8; // C8
    uint32 hit[16];  // CC: hit accumulators, a pair per eight segments (func_800D8D08 passes
                     // &hit[i] for pair i)
} SHL0D_BEAM;

// The beam object: SHL_WORK's header and model data, with the beam data from 0xBC.
typedef struct
{
    uint8 flags_0; // 00
    uint8 value_1; // 01
    uint8 reserved02[4];
    uint8 flags_6; // 06
    uint8 reserved07;
    uint8 routine_0; // 08
    uint8 routine_1; // 09
    uint8 mode_a;    // 0A
    uint8 timer_b;   // 0B
    sint8 index_c;   // 0C
    sint8 bit_d;     // 0D
    sint8 value_e;   // 0E
    sint8 value_f;   // 0F
    uint8 reserved10[4];
    SVECTOR pos;        // 14
    SHL_FIXED fpos;     // 1C
    SVECTOR old_pos;    // 2C
    SHL_FIXED old_fpos; // 34
    sint16 vx, vy, vz;  // 44
    uint8 reserved4a[0x2E];
    SHL_BOX *box_78; // 78
    uint8 reserved7c[0x10];
    MATRIX mtx_8c;   // 8C
    SVECTOR pos_ac;  // AC
    uint32 color_b4; // B4
    uint8 reservedb8[4];
    SHL0D_BEAM beam; // BC
} SHL0D_WORK;

typedef void (*SHL0D_FUNC)(SHL0D_WORK *wp);

extern uint8 D_800D9258[];  // beam value_bf by level
extern uint8 D_800D9260[];  // beam value_be by level
extern sint32 D_800D9268[]; // beam size by level
extern sint32 D_800D9288[]; // beam scale by level
extern SHL_BOX D_800D92A8;
extern SHL0D_FUNC D_800D92B4[]; // routine_0 handlers

sint32 func_80049C54(SVECTOR *a, SVECTOR *b, SHL_BOX *box, sint32 mask);

uint8 func_800D8A6C(SHL0D_WORK *wp);
void func_800D8AB8(SHL0D_WORK *wp);
void func_800D8D08(SHL0D_WORK *wp);
sint32 func_800D9010(SHL0D_WORK *wp);
sint32 func_800D91FC(SHL0D_WORK *wp);

#endif // SHL0D_H
