#ifndef STCOM11_H
#define STCOM11_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The 0x10C-byte work slot stcom11 runs on (freed through ROCK_NEO's func_800318D8): a sprite
// thrown in one of four ways (type_3).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 reserved02;                       // 02
    uint8 type_3;                           // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A: animation frame (0, 2, 4, 6)
    uint8 routine_3;                        // 0B: frames left
    uint8 param_C;                          // 0C: signed speed for type 2
    sint8 param_D;                          // 0D
    sint8 timer_E;                          // 0E: frames to the next trail effect
    uint8 reserved0F;                       // 0F
    uint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    uint8 reserved5C[8];                    // 5C
    sint16 angle_64;                        // 64
    uint8 reserved66[0x12];                 // 66
    uint32 value_78;                        // 78
    uint8 reserved7C[0xC];                  // 7C
    STCOM_SPRITE sprite;                    // 88
    uint8 reservedBC[0x50];                 // BC
} STCOM11_WORK;

typedef void (*STCOM11_FUNC)(STCOM11_WORK *wp);

extern STCOM11_FUNC stcom11_D_0000[]; // routine_0 handlers (stcom11_func_0000)
extern uint8 stcom11_D_0014[];        // (u, v) per animation frame

#endif // STCOM11_H
