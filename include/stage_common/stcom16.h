#ifndef STCOM16_H
#define STCOM16_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The fading color of variant 2 (5 bits a channel, written into scale.v.pad).
typedef struct
{
    sint8 r_0;  // 64
    sint8 g_1;  // 65
    sint8 b_2;  // 66
    sint8 on_3; // 67: set while it is visible (the fade sounds play on the change)
} STCOM16_FADE;

// The ground block at +0xC4 of the work slot.
typedef struct
{
    uint32 hit_0;   // C4: ground hit flags (Obj_map_push_out)
    uint16 value_4; // C8: the claws' hit kind bits, from the kind's record (value_B, value_C)
    uint8 flags_6;  // CA
    uint8 count_7;  // CB: frames chasing the player
} STCOM16_GROUND;

// The stun block at +0x1D8.
typedef struct
{
    uint16 damage_0; // 1D8: damage taken lately (drains by one a frame)
    uint16 rand_2;   // 1DA: a new random number every frame
    uint8 hits_4;    // 1DC
    uint8 timer_5;   // 1DD
    uint8 timer_6;   // 1DE
    uint8 reserved7; // 1DF
} STCOM16_STUN;

// The hit block at +0x348 of the work slot (registered through func_800341BC).
typedef struct
{
    STCOM_SVECTOR pos_0;       // 348: the hit box's center
    uint32 hit_8;              // 350: damage in the low 24 bits, kind bits above
    uint8 reserved0C[4];       // 354
    STCOM_SVECTOR target_10;   // 358: where the hit came from
    uint32 hit_18[2];          // 360: the claws' hit results
    uint8 track_20[0x10];      // 368
    STCOM_SVECTOR position_30; // 378: saved position
    sint16 angle_38;           // 380: the rotation.y it turns to
    sint16 turn_3A;            // 382: turn speed toward the player
    uint8 count_3C;            // 384
    sint8 timer_3D;            // 385
    sint8 timer_3E;            // 386
    sint8 timer_3F;            // 387
    uint8 reserved40[0xD];     // 388
    uint8 value_4D;            // 395
    uint8 reserved4E[0x2A];    // 396
} STCOM16_CTL;

// The 0x3C0-byte work slot stcom16 runs on (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03: 2 fades in and out
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    sint8 param_D;                          // 0D
    sint8 param_E;                          // 0E: turning left (1) or right (0)
    sint8 param_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    STCOM16_FADE fade;                      // 64
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 value_70[3];                      // 70: cleared with power_73 as one word
    sint8 power_73;                         // 73: the hit block's kind bits
    uint8 jump_74;                          // 74: set while it jumps (cleared as a word)
    uint8 reserved75[3];                    // 75
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: distance to the player (squared?)
    uint8 reserved84[0x22];                 // 84
    sint8 value_A6;                         // A6: animation frame
    sint8 flags_A7;                         // A7: -1 when the animation ends
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM16_GROUND ground;                  // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0xB];          // 180: joint positions
    STCOM16_STUN stun;                      // 1D8
    uint8 reserved1E0[8];                   // 1E0
    STCOM_MATRIX mats_1E8[0xB];             // 1E8: joint matrices
    STCOM16_CTL ctl;                        // 348
} STCOM16_WORK;

// A ROCK_NEO record per kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // times 16
    uint8 limit_9; // damage that stuns it (stun.damage_0)
    uint8 value_A; // power_73
    uint8 value_B; // ground.value_4
    uint8 value_C; // ground.value_4 while it bites
} STCOM16_KIND;

typedef void (*STCOM16_FUNC)(STCOM16_WORK *wp);

extern uint8 stcom16_D_0000[];        // data_78
extern STCOM16_FUNC stcom16_D_000C[]; // routine_0 handlers (stcom16_func_0000)
extern STCOM16_FUNC stcom16_D_001C[]; // routine_1 handlers (stcom16_func_0370)
extern STCOM16_FUNC stcom16_D_0040[]; // routine_2 handlers (stcom16_func_0D60)
extern STCOM16_FUNC stcom16_D_005C[]; // routine_2 handlers (stcom16_func_12D0)
extern STCOM16_FUNC stcom16_D_0070[]; // routine_2 handlers (stcom16_func_18E4)
extern STCOM16_FUNC stcom16_D_008C[]; // routine_2 handlers (stcom16_func_1DA0)
extern STCOM16_FUNC stcom16_D_0098[]; // routine_2 handlers (stcom16_func_2434)

// ROCK_NEO.EXE.
extern STCOM16_KIND **D_80098844;
void func_8003354C(void *wp);
void Track_set(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
// PsyQ libgte.
void ApplyMatrix(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_FIXED_VECTOR *out);

void stcom16_func_0370(STCOM16_WORK *wp);
void stcom16_func_0FB4(STCOM16_WORK *wp);
void stcom16_func_1128(STCOM16_WORK *wp);
void stcom16_func_11C4(STCOM16_WORK *wp);
void stcom16_func_1668(STCOM16_WORK *wp);
void stcom16_func_1790(STCOM16_WORK *wp);
void stcom16_func_27E8(STCOM16_WORK *wp);

// ROCK_NEO.EXE (see rock_neo.h).
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 Obj_ceiling_height_get(void *wp);

#endif // STCOM16_H
