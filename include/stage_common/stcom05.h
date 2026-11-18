#ifndef STCOM05_H
#define STCOM05_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The first bytes of another work slot (stcom05_func_0ED0 reads its kind).
typedef struct
{
    uint8 flags_0;
    uint8 reserved01;
    uint8 kind_2;
} STCOM05_HEAD;

// The block at +0xCC of the work slot.
typedef struct
{
    STCOM05_HEAD *link[4]; // CC
    sint32 dist_10;        // DC
    sint32 dist_14;        // E0
    sint16 rot_goal_18;    // E4: heading to the next waypoint
    sint16 rot_diff_1A;    // E6: |rotation.y - rot_goal_18|, folded to 0..0x800
    sint16 rot_half_1C;    // E8: rot_diff_1A / 2
    sint16 value_1E;       // EA
    uint8 index_20;        // EC: current waypoint in stcom05_D_0034
    sint8 timer_21;        // ED
    uint8 flags_22;        // EE: one bit per link still not kind 0x33
    uint8 value_23;        // EF
    uint8 value_24;        // F0
    uint8 value_25;        // F1
    uint8 value_26;        // F2
} STCOM05_CTL;

// The 0x10C-byte work slot stcom05 runs on (freed through ROCK_NEO's func_800318D8).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 reserved01[2];                    // 01
    uint8 index_3;                          // 03: stcom05_D_0000 handler
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 reserved0B;                       // 0B
    sint8 param_C;                          // 0C
    sint8 param_D;                          // 0D
    uint8 reserved0E[2];                    // 0E
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    sint16 accel_4C;                        // 4C
    uint8 reserved4E[6];                    // 4E
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint32 value_64;                        // 64
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint32 value_70;                        // 70
    uint32 value_74;                        // 74
    void *data_78;                          // 78
    uint8 reserved7C[0x10];                 // 7C
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR pos_saved;                // AC
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    STCOM05_CTL ctl;                        // CC
    uint8 reservedF3[0x19];                 // F3
} STCOM05_WORK;

typedef void (*STCOM05_FUNC)(STCOM05_WORK *wp);

extern STCOM05_FUNC stcom05_D_0000[];  // handlers by index_3 (stcom05_func_0000)
extern STCOM05_FUNC stcom05_D_0008[];  // routine_0 handlers (stcom05_func_003C)
extern STCOM05_FUNC stcom05_D_0018[];  // routine_1 handlers (stcom05_func_029C)
extern STCOM05_FUNC stcom05_D_002C[];  // routine_0 handlers (stcom05_func_0F78)
extern STCOM_SVECTOR stcom05_D_003C[]; // waypoints (index_20 - 1 is the one behind)
extern STCOM_SVECTOR stcom05_D_0044[]; // the same waypoints, one ahead
extern uint8 stcom05_D_00AC[];         // message numbers by ctl.value_26
extern uint8 stcom05_D_00B0[];         // data_78
extern uint8 stcom05_D_00BC[];         // data_10

void stcom05_func_029C(STCOM05_WORK *wp);
void stcom05_func_0E64(STCOM05_WORK *wp);
void stcom05_func_0ED0(STCOM05_WORK *wp);
void stcom05_func_0938(STCOM05_WORK *wp);
void stcom05_func_05B8(STCOM05_WORK *wp);

#endif // STCOM05_H
