#ifndef STCOM31_H
#define STCOM31_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The block at +0xBC of the work slot.
typedef struct
{
    uint16 flags_0;     // BC: 1 once it reaches the last waypoint
    uint16 random_2;    // BE: rand() each frame (picks the exhaust offsets)
    sint16 timer_4;     // C0
    uint16 reserved6;   // C2
    sint16 waypoint_8;  // C4: the waypoint it drives to
    uint8 reservedA[2]; // C6
} STCOM31_CTL;

// The 0x10C-byte work slot of a vehicle that drives along waypoints (freed through ROCK_NEO's
// func_800318D8).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[7];                    // 01
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C: heading / 0x200
    uint8 reserved0D[2];                    // 0D
    uint8 param_F;                          // 0F: 0x40 picks the second course
    uint32 value_10;                        // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR_W rotation;               // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint32 value_70;                        // 70
    uint32 value_74;                        // 74
    void *data_78;                          // 78
    uint8 reserved7C[0x10];                 // 7C
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR pos_AC;                   // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[4];                    // B8
    STCOM31_CTL ctl;                        // BC
} STCOM31_WORK;

// A waypoint: its center and the size of the box that counts as reaching it.
typedef struct
{
    sint16 x, z;
    sint16 width, depth;
} STCOM31_WAYPOINT;

typedef void (*STCOM31_FUNC)(STCOM31_WORK *wp);

extern STCOM31_FUNC stcom31_D_0000[];      // routine_0 handlers (stcom31_func_0000)
extern STCOM31_FUNC stcom31_D_000C[];      // routine_1 handlers (stcom31_func_01F8)
extern uint32 stcom31_D_0014[];            // data_78
extern STCOM31_WAYPOINT stcom31_D_0020[];  // the first course
extern STCOM31_WAYPOINT stcom31_D_0050[];  // the second course (param_F & 0x40)
extern STCOM_SVECTOR stcom31_D_0078[4][4]; // exhaust offsets: four sets of four
extern STCOM_FIXED_VECTOR stcom31_E_0000;  // an exhaust puff's position as 16.16
// Declared as arrays: an 8-byte struct is small data to GCC, which folds every field to an
// absolute address; retail reaches x through the address register it passes to calls.
extern STCOM_SVECTOR stcom31_E_0010[]; // the waypoint, then the distance to it
extern STCOM_SVECTOR stcom31_E_0018[]; // an exhaust puff's position
extern uint8 stcom31_E_0020;           // the last waypoint

// The scratchpad's frame counter.
#define STCOM31_FRAME (*(uint16 *)0x1F800002)

// ROCK_NEO.EXE.
sint32 Sce_flag_test(sint32 flag);

// ROCK_NEO.EXE (see rock_neo.h): the step is used unnarrowed here.
sint32 func_80031BEC(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);

#endif // STCOM31_H
