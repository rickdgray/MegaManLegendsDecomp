#ifndef STCOM20_H
#define STCOM20_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A matrix whose identity setup writes its halfwords two at a time.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STCOM20_MATRIX;

// The block at +0xCC of the work slot.
typedef struct
{
    uint8 track_0[0x10];         // CC
    sint16 angle_10;             // DC: bobbing phase
    sint16 ground_12;            // DE: the ground height under it
    sint16 height_14;            // E0: its height above the ground
    sint16 limit_16;             // E2: highest height_14 (-0x82)
    STCOM_FIXED scale_18;        // E4: grows when it bursts
    uint32 hit_1C;               // E8: damage in the low 24 bits, kind bits above
    uint32 value_20;             // EC
    sint16 x_24;                 // F0: where the hit came from
    sint16 reserved26;           // F2
    sint16 z_28;                 // F4
    sint16 reserved2A;           // F6
    STCOM_FIXED_VECTOR scale_2C; // F8
} STCOM20_CTL;

// The 0x10C-byte work slot of a floating mine (freed through ROCK_NEO's func_800318D8).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 reserved02[6];                    // 02
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 reserved0A[2];                    // 0A
    sint8 param_C;                          // 0C: 1 once hit
    uint8 reserved0D[7];                    // 0D
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[2];                    // 64
    sint16 angle_66;                        // 66: heading
    uint8 reserved68[0xC];                  // 68
    uint8 value_74;                         // 74
    uint8 reserved75[3];                    // 75
    void *data_78;                          // 78
    uint8 reserved7C[0x10];                 // 7C
    STCOM20_MATRIX matrix;                  // 8C
    STCOM_SVECTOR pos_AC;                   // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    STCOM20_CTL ctl;                        // CC
} STCOM20_WORK;

typedef void (*STCOM20_FUNC)(STCOM20_WORK *wp);

extern uint8 stcom20_D_0000[];        // data_78
extern STCOM20_FUNC stcom20_D_000C[]; // routine_1 handlers (stcom20_func_06E8)
extern STCOM20_FUNC stcom20_D_0018[]; // routine_0 handlers (stcom20_func_0818)

// ROCK_NEO.EXE.
void func_80036478(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
void func_8002CA10(STCOM_SVECTOR *pos, sint32 a1, sint32 a2, sint32 a3);
sint32 func_8001E83C(sint16 x0, sint16 z0, sint16 x1, sint16 z1);
void func_8004AE88(sint16 *angle, sint32 hit);
#ifdef __wasm32__
void func_80047148(void *wp, STCOM_SVECTOR *pos);
#else
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
#endif
// PsyQ libgte.
STCOM_MATRIX *RotMatrix(STCOM_SVECTOR *r, STCOM_MATRIX *m);
STCOM_MATRIX *MulMatrix(STCOM_MATRIX *m0, STCOM_MATRIX *m1);

sint32 stcom20_func_0000(STCOM20_WORK *wp);
sint32 stcom20_func_0024(STCOM20_WORK *wp);

// ROCK_NEO.EXE (see rock_neo.h).
sint32 func_80031BEC(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 func_80048E6C(void *wp);

#endif // STCOM20_H
