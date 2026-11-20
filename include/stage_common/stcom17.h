#ifndef STCOM17_H
#define STCOM17_H

#include "common.h"
#include "stage_common/rock_neo.h"

// d = |a - b|, as a statement (the pitch helpers stcom17_func_22C8..23BC).
#define STCOM17_ABS_DIFF(d, a, b)                                                                  \
    do                                                                                             \
    {                                                                                              \
        (d) = (a) - (b);                                                                           \
        if ((d) < 0)                                                                               \
        {                                                                                          \
            (d) = -(d);                                                                            \
        }                                                                                          \
    } while (0)

// The 0x10C-byte slot stcom17 spawns (Open_SHL_WORK): a shell (kind 1) or a missile (kind 0x2E).
typedef struct
{
    uint8 flags_0;                     // 00
    uint8 reserved01;                  // 01
    uint8 kind_2;                      // 02
    uint8 variant_3;                   // 03
    uint8 value_4;                     // 04
    uint8 reserved05[0xA];             // 05
    uint8 value_F;                     // 0F
    uint8 reserved10[4];               // 10
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    sint16 value_66;                   // 66
    uint8 reserved68[0xA4];            // 68
} STCOM17_SHOT;

// The block at +0x2E8 of the tank's work slot (stcom17_func_0000..1470).
typedef struct
{
    STCOM_SVECTOR pos_0;         // 2E8: the hit box's center
    uint32 hit_8;                // 2F0: damage in the low 24 bits, kind bits above
    uint32 value_C;              // 2F4
    STCOM_SVECTOR target_10;     // 2F8: where the hit came from
    uint8 track_18[0x10];        // 300
    STCOM_SVECTOR size_28;       // 310: the player range box (func_80030418, func_80030628)
    STCOM_FIXED_VECTOR fixed_30; // 318
    uint16 damage_40;            // 328: damage taken lately (drains by one a frame)
    uint16 power_42;             // 32A: or'd into the hit block's kind bits
    sint16 turn_44;              // 32C: the turret's angle from rotation.y
    sint16 timer_46;             // 32E
    sint8 timer_48;              // 330: engine sound
    sint8 timer_49;              // 331: turret sound
    uint8 flags_4A;              // 332
    uint8 count_4B;              // 333
    uint8 routine_4C;            // 334: routine_1 to go back to
    uint8 routine_4D;            // 335: routine_2 to go back to
    uint8 flags_4E;              // 336
    uint8 count_4F;              // 337: missiles left
    uint8 timer_50;              // 338
    uint8 timer_51;              // 339
    uint8 value_52;              // 33A
    uint8 timer_53;              // 33B
    uint8 value_54;              // 33C: near the player (aims low)
    uint8 reserved55[0x83];      // 33D
} STCOM17_CTL;

// The 0x3C0-byte work slot of the tank (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03: mode in the low nibble
    uint8 value_4;                          // 04
    uint8 reserved05;                       // 05
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    sint8 param_D;                          // 0D: seconds of the first drive
    sint8 param_E;                          // 0E: turn per frame
    uint8 param_F;                          // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[4];                    // 70
    uint8 value_74;                         // 74
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
    STCOM_SVECTOR value_C4;                 // C4: a joint, for the player range tests
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x2D];         // 180: joint positions
    STCOM17_CTL ctl;                        // 2E8
} STCOM17_WORK;

// The block at +0x308 of the gun's work slot (stcom17_func_1690..23BC).
typedef struct
{
    STCOM_SVECTOR pos_0;         // 308: the hit box's center
    STCOM_SVECTOR_W vec_8;       // 310: 0x310..0x32F are copied to the scratchpad each frame
    STCOM_SVECTOR_W vec_10;      // 318
    STCOM_SVECTOR_W rot_18;      // 320: the barrel's rotation (y relative to rotation.y)
    sint16 angle_20;             // 328: the barrel's pitch
    sint16 reserved22;           // 32A
    uint32 value_24;             // 32C
    uint32 hit_28;               // 330: damage in the low 24 bits, kind bits above
    uint32 value_2C;             // 334
    uint8 track_30[0x10];        // 338
    uint32 dist_40;              // 348: value_80 when the pitch was last aimed
    STCOM_SVECTOR size_44;       // 34C: the player range box (func_80030628)
    STCOM_FIXED_VECTOR fixed_4C; // 354
    uint16 power_5C;             // 364: or'd into the hit block's kind bits
    sint16 speed_5E;             // 366: shell speed
    sint16 angle_60;             // 368: the pitch it aims at
    uint8 flags_62;              // 36A
    uint8 timer_63;              // 36B
    sint8 timer_64;              // 36C
    sint8 count_65;              // 36D: shots left in the burst
    uint8 timer_66;              // 36E
    uint8 reserved67;            // 36F
    sint8 timer_68;              // 370: turning sound
    uint8 reserved69[0x4F];      // 371
} STCOM17_GUN_CTL;

// The 0x3C0-byte work slot of the gun (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03
    uint8 value_4;                          // 04
    uint8 reserved05[3];                    // 05
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    uint8 reserved0D[3];                    // 0D
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C: the barrel's last rotation (ctl.rot_18)
    uint8 reserved64[0xA];                  // 64
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: distance to the player (squared?)
    uint8 reserved84[0x2C];                 // 84
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4: a joint, for the player range tests
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x31];         // 180: joint positions
    STCOM17_GUN_CTL ctl;                    // 308
} STCOM17_GUN_WORK;

// A ROCK_NEO record per kind (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // times 16
    uint8 limit_9; // damage that knocks it back (ctl.damage_40)
    uint8 value_A; // power
} STCOM17_KIND;

typedef void (*STCOM17_FUNC)(STCOM17_WORK *wp);

extern uint8 stcom17_D_0000[];        // data_78
extern STCOM17_FUNC stcom17_D_000C[]; // routine_0 handlers (stcom17_func_0000)
extern STCOM17_FUNC stcom17_D_0018[]; // routine_1 handlers (stcom17_func_021C)

typedef void (*STCOM17_GUN_FUNC)(STCOM17_GUN_WORK *wp);

extern STCOM17_GUN_FUNC stcom17_D_0034[]; // routine_0 handlers (stcom17_func_1690)
extern STCOM17_GUN_FUNC stcom17_D_0040[]; // routine_1 handlers (stcom17_func_1990)

// ROCK_NEO.EXE.
extern STCOM17_KIND **D_80098844;
extern uint8 Scene_work; // nonzero while a scene runs
STCOM17_SHOT *Open_SHL_WORK(void);
void func_80036478(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
void func_8002F9EC(void *wp, sint32 arg);
void func_80032304(void *wp, sint32 anim, sint32 arg);
void func_8003346C(void *wp);
uint32 func_80030628(void *wp, void *other, STCOM_SVECTOR *range, STCOM_FIXED_VECTOR *out,
                     sint32 angle);
sint32 func_80030418(void *a, void *b, STCOM_SVECTOR *size, STCOM_FIXED_VECTOR *out);
void func_80030EE8(void *wp, STCOM_SVECTOR *target, sint32 speed);
#ifdef __wasm32__
void func_80047148(void *wp, STCOM_SVECTOR *pos);
#else
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
#endif
void func_80052528(void *wp);
sint32 func_800364B0(void *track, void *wp, sint32 angle);
sint16 func_80030D30(STCOM_SVECTOR *from, STCOM_SVECTOR *to, sint32 speed, sint32 arg3,
                     sint32 arg4);
void func_80030968(void *shot, void *target, sint32 speed, sint32 arg3, sint32 arg4);
sint32 SquareRoot0(sint32 v);
// Hand-written: copies `count` words.
void Mem_copy4(void *src, void *dst, sint32 count);

void stcom17_func_0530(STCOM17_WORK *wp);
void stcom17_func_0594(STCOM17_WORK *wp);
void stcom17_func_0BE4(STCOM17_WORK *wp);
void stcom17_func_1278(STCOM17_WORK *wp);
void stcom17_func_1470(STCOM17_WORK *wp);
void stcom17_func_2100(STCOM17_GUN_WORK *wp);
void stcom17_func_22C8(STCOM17_GUN_WORK *wp, sint16 angle, sint16 goal);
void stcom17_func_2320(STCOM17_GUN_WORK *wp, sint16 angle, sint16 goal);
void stcom17_func_2378(STCOM17_GUN_WORK *wp, sint32 angle, sint32 goal);
void stcom17_func_23BC(STCOM17_GUN_WORK *wp, sint32 angle, sint32 goal);

// ROCK_NEO.EXE (see rock_neo.h).
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 func_80048E6C(void *wp);

#endif // STCOM17_H
