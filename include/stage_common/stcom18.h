#ifndef STCOM18_H
#define STCOM18_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A frame's sprite bytes (value_E, value_F) in stcom18_D_0000 and stcom18_D_000C.
typedef struct
{
    uint8 a;
    uint8 b;
} STCOM18_PAIR;

// The 0x10C-byte work slot of a flame (freed through ROCK_NEO's Close_SHL_WORK).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 reserved02[6];                    // 02
    uint8 routine_0;                        // 08
    uint8 reserved09[2];                    // 09
    uint8 timer_B;                          // 0B: frames left
    uint8 reserved0C[2];                    // 0C
    sint8 kind_E;                           // 0E: the hit block's kind bits
    uint8 flags_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x14];                 // 64
    uint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    STCOM_SPRITE sprite;                    // 88
    uint32 hit_BC;                          // BC
    uint8 reservedC0[0x4C];                 // C0
} STCOM18_WORK;

typedef void (*STCOM18_FUNC)(STCOM18_WORK *wp);

extern STCOM18_PAIR stcom18_D_0000[6]; // frames (flags_F bit 0 without bit 3)
extern STCOM18_PAIR stcom18_D_000C[6]; // frames (flags_F bits 0 and 3)
extern STCOM18_FUNC stcom18_D_0018[];  // routine_0 handlers (stcom18_func_0000)

// ROCK_NEO.EXE.
void func_8002CA10(STCOM_SVECTOR *pos, sint32 a1, sint32 a2, sint32 a3);

void stcom18_func_0534(STCOM18_WORK *wp, STCOM_EFFECT *effect);
void stcom18_func_0574(STCOM18_WORK *wp, STCOM_EFFECT *effect);

#endif // STCOM18_H
