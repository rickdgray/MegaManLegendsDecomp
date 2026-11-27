#ifndef STCOM01_H
#define STCOM01_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The block at +0x348 of the work slot; routines take its address for its routine byte.
typedef struct
{
    uint16 flags;        // 348
    uint8 value_2;       // 34A
    uint8 routine;       // 34B
    sint16 value_4;      // 34C
    sint16 turn;         // 34E: turn speed
    sint16 timer;        // 350: countdown
    sint16 value_A;      // 352
    STCOM_SVECTOR pos_C; // 354
    sint16 value_14;     // 35C
    sint16 value_16;     // 35E
    sint16 value_18;     // 360
    sint16 value_1A;     // 362
    sint16 value_1C;     // 364
    sint16 value_1E;     // 366
    uint16 range_20;     // 368: how near the player must come (stcom01_func_01FC)
} STCOM01_CTL;

// The work slot stcom01's routines run on. Freed through ROCK_NEO.EXE's func_80031824, so it is
// one of the 0x3C0-byte slots at D_8009F108 there (GAME_WORK_3C0 in ROCK_NEO's game.h, which
// names other fields; the two views aren't reconciled yet). Only the fields used so far.
typedef struct STCOM01_WORK
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    uint8 param_D;                          // 0D
    uint8 param_E;                          // 0E
    uint8 param_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 rot_goal_64;                     // 64: angle the slot turns toward
    uint8 reserved66[8];                    // 66
    sint16 value_6E;                        // 6E
    uint8 reserved70[8];                    // 70
    uint32 value_78;                        // 78
    uint8 reserved7C[0x2B];                 // 7C
    sint8 state_A7;                         // A7: negative ends routine_2's step
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC: animation (stcom01_func_28D8 picks it)
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x1E8];               // 160
    STCOM01_CTL ctl;                        // 348
    uint8 reserved36A[0x56];                // 36A
} STCOM01_WORK;

typedef void (*STCOM01_FUNC)(STCOM01_WORK *wp);

typedef struct
{
    sint32 a, b, c;
} STCOM01_PARAM3;

extern uint8 stcom01_D_0550[];          // data_10 (stcom01_func_003C)
extern STCOM01_FUNC stcom01_D_0568[];   // routine_1 handlers (stcom01_func_01FC)
extern STCOM01_FUNC stcom01_D_055C[];   // routine_0 handlers (stcom01_func_0000)
extern STCOM01_FUNC stcom01_D_058C[];   // routine_2 handlers (stcom01_func_03D8)
extern STCOM01_FUNC stcom01_D_05DC[];   // routine_2 handlers (stcom01_func_057C)
extern STCOM01_FUNC stcom01_D_0678[];   // routine_2 handlers (stcom01_func_0C68)
extern STCOM01_FUNC stcom01_D_06D4[];   // routine_2 handlers (stcom01_func_12A4)
extern STCOM01_FUNC stcom01_D_0740[];   // ctl.routine handlers (stcom01_func_1888)
extern STCOM01_FUNC stcom01_D_0750[];   // ctl.routine handlers (stcom01_func_1C70)
extern STCOM01_FUNC stcom01_D_075C[];   // ctl.routine handlers (stcom01_func_1F30)
extern STCOM01_FUNC stcom01_D_0774[];   // ctl.routine handlers (stcom01_func_2174)
extern STCOM01_FUNC stcom01_D_0788[];   // ctl.routine handlers (stcom01_func_257C)
extern STCOM01_PARAM3 stcom01_D_0000[]; // by id: Model_Shadow_Trans's arguments
extern uint8 stcom01_D_04E0[];          // speed by id (stcom01_func_2918)
extern uint8 stcom01_D_059C[4][16];     // random wait times (stcom01_func_0414)
extern uint8 stcom01_D_0608[];          // 4 x 16 random steps, row by param_D bits 4-5
extern uint8 stcom01_D_0648[2][16];     // random wait times (stcom01_func_0610)
extern uint8 stcom01_D_0668[16];        // random wait times (stcom01_func_0610)
extern uint8 stcom01_D_0694[16];        // random choice (stcom01_func_0CD8)
extern uint8 stcom01_D_06A4[3][16];     // random wait times (stcom01_func_0CD8)
extern uint8 stcom01_D_06F0[16];        // random choice (stcom01_func_133C)
extern uint8 stcom01_D_0700[16];        // random choice, kind 0x2A (stcom01_func_133C)
extern uint8 stcom01_D_0710[16];        // random flags (stcom01_func_133C)
extern uint8 stcom01_D_0720[16];        // random flags, kind 0x2A (stcom01_func_133C)
extern uint8 stcom01_D_0730[16];        // random wait times (stcom01_func_133C)

// ROCK_NEO.EXE: steps the angle `rot` toward `goal` by at most `speed`; returns the step (0 when
// there). See rock_neo.h.
sint16 Angle_diff_clamp(sint32 goal, sint32 rot, sint32 speed);

sint32 stcom01_func_2828(uint8 kind);
sint32 stcom01_func_28C8(uint8 kind);
sint32 stcom01_func_28D8(uint8 kind);
uint8 stcom01_func_1B28(STCOM01_WORK *wp);
void stcom01_func_01FC(STCOM01_WORK *wp);
void stcom01_func_27C0(STCOM01_WORK *wp);
sint32 stcom01_func_2918(STCOM01_WORK *wp, uint8 mode);
uint8 stcom01_func_2968(STCOM01_WORK *wp, sint32 a1, sint32 a2);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint16 Obj_ceiling_height_get(void *wp);

#endif // STCOM01_H
