#ifndef STCOM08_H
#define STCOM08_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A scratchpad frame counter (ROCK_NEO's CODE456_FRAME).
#define STCOM08_FRAME (*(uint16 *)0x1F800002)

// The 0x3C0-byte work slot stcom08 runs on (freed through ROCK_NEO's func_80031824): something
// that drifts near its home position at a wobbling height above the ground.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 reserved0A;                       // 0A
    uint8 routine_3;                        // 0B: 0 on the first frame
    uint8 reserved0C;                       // 0C
    sint8 range_D;                          // 0D: how far it may stray (in 128ths), 0 for no limit
    uint8 reserved0E[6];                    // 0E
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64: turn speed
    sint16 rot_speed_66;                    // 66: added to rotation.y each frame
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint32 value_78;                        // 78
    uint8 reserved7C[0x34];                 // 7C
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x1EC];               // 160
    sint16 timer_34C;                       // 34C: frames until it turns home
    uint8 reserved34E[2];                   // 34E
    uint32 dist_350;                        // 350: distance from home, in 128ths
    uint8 reserved354[0x10];                // 354
    STCOM_SVECTOR home;                     // 364
    uint8 reserved36C[0x54];                // 36C
} STCOM08_WORK;

typedef void (*STCOM08_FUNC)(STCOM08_WORK *wp);

extern STCOM08_FUNC stcom08_D_0000[]; // routine_0 handlers (stcom08_func_0000)
extern uint16 stcom08_D_0010[];       // height wobble, by frame & 7

void stcom08_func_0348(STCOM08_WORK *wp);
void stcom08_func_0424(STCOM08_WORK *wp);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint16 func_80048E6C(void *wp);

#endif // STCOM08_H
