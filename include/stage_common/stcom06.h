#ifndef STCOM06_H
#define STCOM06_H

#include "common.h"
#include "stage_common/rock_neo.h"

// Two bytes from a table of halfword pairs (stcom06_func_0594).
typedef struct
{
    uint16 a;
    uint16 b;
} STCOM06_PAIR;

// The 0x10C-byte work slot stcom06 runs on (freed through ROCK_NEO's Close_SHL_WORK).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 reserved02;                       // 02
    uint8 type;                             // 03: bit 7 picks stcom06_D_0018 over stcom06_D_0000
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 count_C;                          // 0C: frames in flight
    sint8 timer_D;                          // 0D
    uint8 flags_E;                          // 0E
    sint8 index_F;                          // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    uint8 reserved54[0x10];                 // 54
    sint16 angle_64;                        // 64
    uint8 reserved66[0xE];                  // 66
    uint8 value_74;                         // 74
    uint8 reserved75;                       // 75
    uint8 value_76;                         // 76
    uint8 reserved77;                       // 77
    uint32 value_78;                        // 78
    sint16 value_7C;                        // 7C
    uint8 reserved7E[0xA];                  // 7E
    STCOM_SPRITE sprite;                    // 88
    uint8 reservedBC[0x50];                 // BC
} STCOM06_WORK;

typedef void (*STCOM06_FUNC)(STCOM06_WORK *wp);

extern STCOM06_PAIR stcom06_D_0000[];
extern STCOM06_PAIR stcom06_D_0018[];
extern STCOM06_FUNC stcom06_D_0030[]; // routine_0 handlers (stcom06_func_0000)

void stcom06_func_0E10(STCOM06_WORK *wp, STCOM_EFFECT *effect);
void stcom06_func_0E68(STCOM06_WORK *wp, STCOM_EFFECT *effect);
sint16 stcom06_func_0A80(STCOM06_WORK *wp);
void stcom06_func_0D1C(STCOM06_WORK *wp);

#endif // STCOM06_H
