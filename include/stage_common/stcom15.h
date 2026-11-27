#ifndef STCOM15_H
#define STCOM15_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The 0x10C-byte slot stcom15_func_1E0C spawns (stcom06's emitter: kind 6 or 9).
typedef struct
{
    uint8 be_flag;                     // 00
    uint8 slot;                        // 01
    uint8 id;                          // 02
    uint8 type;                        // 03
    uint8 reserved04[0x10];            // 04
    STCOM_SVECTOR position;            // 14
    STCOM_FIXED_VECTOR position_fixed; // 1C
    uint8 reserved2C[0x38];            // 2C
    sint16 angle_64;                   // 64
    uint8 reserved66[0x36];            // 66
    sint32 speed_9C;                   // 9C
    sint32 rise_A0;                    // A0
} STCOM15_SHOT;

// The block at +0x328 of the work slot.
typedef struct
{
    uint16 flags_0;          // 328
    uint16 rand_2;           // 32A: a new random number every frame
    sint16 timer_4;          // 32C
    sint16 level_6;          // 32E: row of the kind's table (D_80098844)
    uint16 value_8;          // 330: or'd into the hit block's kind bits
    sint16 timer_A;          // 332
    STCOM_SVECTOR pos_C;     // 334: the hit box's center
    uint32 hit_14;           // 33C: damage in the low 24 bits, kind bits above
    uint32 value_18;         // 340
    STCOM_SVECTOR target_1C; // 344: the attacker's position (pad bit 0: from the player?)
    uint8 track_24[0x10];    // 34C
    sint16 timer_34;         // 35C
    sint16 timer_36;         // 35E
    sint16 timer_38;         // 360: frames before it bursts (flags_0 0x40)
    uint16 flag_3A;          // 362: scene flag (from position.pad)
    uint8 *steps_3C;         // 364: frames per hop (stcom15_D_0050, stcom15_D_005C)
    STCOM_EFFECT *effect_40; // 368
    sint16 turn_44;          // 36C
    sint16 angle_46;         // 36E: its bearing from the player, relative to the player's facing
    uint32 hit_48;           // 370: ground hit flags (Obj_map_push_out)
    STCOM15_SHOT *shot_4C;   // 374
} STCOM15_CTL;

// The 0x3C0-byte work slot stcom15 runs on (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02: index into D_80098844
    uint8 type;                             // 03: flags
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 param_C;                          // 0C
    sint8 param_D;                          // 0D: frames before it charges again
    uint8 param_E;                          // 0E: routine_1 to go back to
    uint8 param_F;                          // 0F: life multiplier - 1 (low 7 bits)
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 turn_66;                         // 66
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: screen depth?
    uint8 reserved84[0x22];                 // 84
    sint8 value_A6;                         // A6: animation frame
    uint8 reservedA7[5];                    // A7
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0xA4];                 // B4
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x35];         // 180: joint positions
    STCOM15_CTL ctl;                        // 328
    uint8 reserved378[0x48];                // 378
} STCOM15_WORK;

// A ROCK_NEO record per kind and level (D_80098844).
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;  // times 16
    uint8 limit_9; // damage that knocks it back (timer_A)
    uint8 value_A; // value_8 while it charges (stcom15_func_1B90)
    uint8 value_B; // value_8 while it hops (stcom15_func_1620)
    uint8 value_C; // timer_34 after it shoots (stcom15_func_0D54)
    uint8 reserved0D[2];
    uint8 track_F;
} STCOM15_LEVEL;

typedef void (*STCOM15_FUNC)(STCOM15_WORK *wp);

extern STCOM15_FUNC stcom15_D_0000[]; // routine_0 handlers (stcom15_func_0000)
extern STCOM15_FUNC stcom15_D_000C[]; // routine_1 handlers (stcom15_func_0394)
extern uint8 stcom15_D_0038[];        // data_78
extern uint8 stcom15_D_0044[];        // frames per hop (stcom15_func_13E8)
extern uint8 stcom15_D_0050[];        // frames per hop
extern uint8 stcom15_D_005C[];        // frames per hop (type 0x40)
extern uint8 stcom15_D_0068[4];       // turn chances out of 16 (stcom15_func_1D40)
extern STCOM_SVECTOR stcom15_D_006C;  // a fixed point it turns from

// ROCK_NEO.EXE.
extern STCOM15_LEVEL **D_80098844;
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
void func_80047228(void *wp, STCOM_SVECTOR *pos, sint32 arg2);
sint32 Sce_flag_test(sint32 flag);

STCOM15_SHOT *Open_SHL_WORK(void);

sint32 stcom15_func_1D40(STCOM15_WORK *wp);
void stcom15_func_1E0C(STCOM15_WORK *wp);
sint32 stcom15_func_1F44(STCOM15_WORK *wp);

// ROCK_NEO.EXE (see rock_neo.h).
sint32 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 Obj_ceiling_height_get(void *wp);

#endif // STCOM15_H
