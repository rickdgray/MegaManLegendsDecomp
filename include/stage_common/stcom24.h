#ifndef STCOM24_H
#define STCOM24_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A hit record filled by func_800341BC.
typedef struct
{
    uint32 hit_0;         // 00: damage in the low 24 bits, kind bits above
    uint32 value_4;       // 04
    STCOM_SVECTOR from_8; // 08: where the hit came from
} STCOM24_HIT;

// The block at +0x348 of the work slot.
typedef struct
{
    uint16 flags_0;         // 348: 1 body hit box, 2 claw hit box, 8/0x10 knocked back, 0x20 sees
                            //      the player
    uint16 rand_2;          // 34A: a new random number every frame
    sint16 timer_4;         // 34C
    sint16 timer_6;         // 34E
    sint16 timer_8;         // 350: until it may shoot again
    uint8 reserved0A[2];    // 352
    sint32 angle_C;         // 354: the direction it is knocked to
    uint16 kind_10;         // 358: the body hit box's kind bits (the kind's value_B)
    uint16 damage_12;       // 35A: body damage taken since the last knock-back
    sint16 kind_14;         // 35C: the claw hit box's kind bits (the kind's value_C)
    sint16 damage_16;       // 35E: claw damage taken since the last knock-back
    STCOM_SVECTOR pos_18;   // 360: the hit boxes' center
    STCOM24_HIT body_20;    // 368
    STCOM24_HIT claw_30;    // 378
    uint8 track_40[0x10];   // 388: Track_reset/func_8003648C
    STCOM_SVECTOR home_50;  // 398: where it started
    uint8 reserved58[0x20]; // 3A0
} STCOM24_CTL;

// The 0x3C0-byte work slot stcom24 runs on (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 index_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03: nonzero: stays near home
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C: the starting direction in its low three bits
    uint8 reserved0D[7];                    // 0D
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    uint8 reserved44[0x10];                 // 44
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 value_64;                        // 64
    sint16 value_66;                        // 66
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[4];                    // 70
    sint8 jump_74;                          // 74: set while it leaps
    uint8 jump_prev_75;                     // 75
    uint8 reserved76[2];                    // 76
    void *data_78;                          // 78
    uint8 reserved7C[0x28];                 // 7C
    uint8 frame_A4;                         // A4: animation frame
    uint8 reservedA5[2];                    // A5
    sint8 flags_A7;                         // A7: -1 when the animation ends
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[2];            // 180: joint positions
    uint8 reserved190[0x1B8];               // 190
    STCOM24_CTL ctl;                        // 348
} STCOM24_WORK;

// The 0x10C-byte slot stcom24_func_07E4 spawns (kind 9, variant 3).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 reserved04[0x10];            // 04
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    uint8 reserved66[0xA6];            // 66
} STCOM24_SHOT;

// A ROCK_NEO record per kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // times 16
    uint8 limit_9; // body damage that knocks it back (ctl.damage_12)
    uint8 limit_A; // claw damage that knocks it back (ctl.damage_16)
    uint8 value_B; // ctl.kind_10
    uint8 value_C; // ctl.kind_14
} STCOM24_KIND;

typedef void (*STCOM24_FUNC)(STCOM24_WORK *wp);

extern sint16 stcom24_D_0000[];       // data_78
extern STCOM24_FUNC stcom24_D_000C[]; // routine_0 handlers (stcom24_func_0000)
extern STCOM24_FUNC stcom24_D_002C[]; // routine_1 handlers (stcom24_func_05B4)
extern STCOM24_FUNC stcom24_D_0044[]; // routine_1 handlers (stcom24_func_0954)
extern STCOM24_FUNC stcom24_D_0050[]; // routine_1 handlers (stcom24_func_0BA0)
extern STCOM24_FUNC stcom24_D_0060[]; // routine_1 handlers (stcom24_func_0F20)

sint8 stcom24_func_1468(STCOM24_WORK *wp);
sint8 stcom24_func_15E8(STCOM24_WORK *wp);

// ROCK_NEO.EXE.
extern STCOM24_KIND **D_80098844;
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
STCOM24_SHOT *Open_SHL_WORK(void);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint16 Obj_ceiling_height_get(void *wp);

#endif // STCOM24_H
