#ifndef STCOM27_H
#define STCOM27_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The block at +0x348 of the work slot.
typedef struct
{
    uint8 track_0[0x10];    // 348: Track_reset/func_8003648C
    sint32 sees_10;         // 358: nonzero while it sees the player (func_8003648C)
    sint32 flags_14;        // 35C: 1 hit a wall, 2 on the ground, 4 at a ledge
    STCOM_SVECTOR pos_18;   // 360: the hit box's center
    uint32 hit_20;          // 368: damage in the low 24 bits, kind bits above
    uint32 value_24;        // 36C
    STCOM_SVECTOR from_28;  // 370: where the hit came from
    uint32 kind_30;         // 378: the hit box's kind bits
    uint16 timer_34;        // 37C: until it stops roaming
    uint16 timer_36;        // 37E: until it turns
    uint16 timer_38;        // 380
    uint16 timer_3A;        // 382
    sint16 angle_3C;        // 384: the rotation.y it turns to
    uint16 damage_3E;       // 386: damage taken while stunned
    uint8 reserved40[0x38]; // 388
} STCOM27_CTL;

// The 0x3C0-byte work slot stcom27 runs on (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 work_id;                          // 01
    uint8 id;                               // 02: index into D_80098844
    uint8 type;                             // 03
    uint8 reserved04[2];                    // 04
    uint8 flags;                            // 06: 0x80 shakes the camera when it hits a wall
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 work_0;                           // 0C
    uint8 work_1;                           // 0D
    uint8 work_2;                           // 0E
    uint8 work_3;                           // 0F
    uint8 reserved10[4];                    // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[4];                    // 70
    sint8 jump_74;                          // 74: set while it is in the air
    sint8 jump_prev_75;                     // 75
    uint8 reserved76[2];                    // 76
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: distance to the player (squared?)
    uint8 reserved84[0x20];                 // 84
    uint8 frame_A4;                         // A4: animation frame
    uint8 reservedA5[7];                    // A5
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 damage_B2;                       // B2: damage taken lately (drains by one a frame)
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x1E8];               // 160
    STCOM27_CTL ctl;                        // 348
} STCOM27_WORK;

// A ROCK_NEO record per kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // times 16
    uint8 limit_9; // damage (times 16) that knocks it over
    uint8 value_A; // ctl.kind_30 while it charges
    uint8 value_B; // ctl.kind_30
} STCOM27_KIND;

typedef void (*STCOM27_FUNC)(STCOM27_WORK *wp);

extern STCOM27_FUNC stcom27_D_0000[]; // routine_0 handlers (stcom27_func_0000)
extern sint16 stcom27_D_000C[];       // data_78
extern STCOM27_FUNC stcom27_D_0018[]; // routine_1 handlers (stcom27_func_0168)
extern STCOM27_FUNC stcom27_D_003C[]; // routine_2 handlers (stcom27_func_0954)

void stcom27_func_02B4(STCOM27_WORK *wp);
void stcom27_func_04E4(STCOM27_WORK *wp);
void stcom27_func_0578(STCOM27_WORK *wp);
void stcom27_func_0600(STCOM27_WORK *wp);
void stcom27_func_06F8(STCOM27_WORK *wp);
void stcom27_func_0CC4(STCOM27_WORK *wp);
void stcom27_func_0D44(STCOM27_WORK *wp);
void stcom27_func_0DB8(STCOM27_WORK *wp);
void stcom27_func_0DDC(STCOM27_WORK *wp);
void stcom27_func_0E34(STCOM27_WORK *wp);
void stcom27_func_0E4C(STCOM27_WORK *wp);
void stcom27_func_0E78(STCOM27_WORK *wp);
void stcom27_func_0EAC(STCOM27_WORK *wp);

// ROCK_NEO.EXE.
extern STCOM27_KIND **D_80098844;
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
void Swing_Camera2(sint32 a0, sint32 a1, sint32 a2, STCOM_SVECTOR *pos);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 Obj_ceiling_height_get(void *wp);

#endif // STCOM27_H
