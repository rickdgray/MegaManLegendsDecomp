#ifndef STCOM13_H
#define STCOM13_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The block at +0x348 of the work slot.
typedef struct
{
    uint16 flags_0;        // 348
    uint16 rand_2;         // 34A: a new random number every frame
    sint16 timer_4;        // 34C
    uint8 reserved06[2];   // 34E
    sint16 value_8;        // 350
    sint16 damage_A;       // 352: damage taken while stunned
    STCOM_SVECTOR pos_C;   // 354: the hit box's center
    uint32 hit_14;         // 35C: damage in the low 24 bits, kind bits above
    uint32 value_18;       // 360
    STCOM_SVECTOR from_1C; // 364: where the hit came from
    uint8 track_24[0x10];  // 36C
    sint16 count_34;       // 37C: drops so far (stcom13_func_08B0)
    uint16 timer_36;       // 37E: frames before it may vanish off screen
} STCOM13_CTL;

// The 0x3C0-byte work slot stcom13 runs on (freed through ROCK_NEO's func_80031824): an enemy
// that can be stunned and knocked about, dropping effects from its joints.
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 variant_3;                        // 03
    uint8 reserved04[2];                    // 04
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 reserved0C[4];                    // 0C
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR_W velocity;               // 44
    uint8 reserved4C[2];                    // 4C
    sint16 gravity_4E;                      // 4E
    uint8 reserved50[4];                    // 50
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    sint16 turn_66;                         // 66: turn speed (stcom13_func_0C24)
    uint8 reserved68[6];                    // 68
    sint16 life_6E;                         // 6E
    uint8 reserved70[8];                    // 70
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: screen depth?
    uint8 reserved84[0x20];                 // 84
    uint8 value_A4;                         // A4
    uint8 reservedA5[7];                    // A5
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0x5C];                 // B4
    uint8 value_110;                        // 110
    uint8 reserved111[0x47];                // 111
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR joints_180[0x39];         // 180: joint positions
    STCOM13_CTL ctl;                        // 348
    uint8 reserved380[0x40];                // 380
} STCOM13_WORK;

// A ROCK_NEO record per kind (D_80098844).
typedef struct
{
    uint8 reserved00[0x18];
    uint8 life_18;
    uint8 stun_19; // damage that ends a stun
} STCOM13_KIND;

typedef void (*STCOM13_FUNC)(STCOM13_WORK *wp);

extern STCOM13_FUNC stcom13_D_0000[]; // routine_0 handlers (stcom13_func_0000)
extern STCOM13_FUNC stcom13_D_000C[]; // routine_1 handlers (stcom13_func_01D8)
extern uint8 stcom13_D_0020[];        // data_78
extern uint8 stcom13_D_002C[];        // drop times by routine_3 (stcom13_func_08B0)
extern uint8 stcom13_D_0030[4][4];    // joints to drop from, by routine_3
extern uint8 stcom13_D_0040[];        // joints to drop from when it dies

// ROCK_NEO.EXE.
extern STCOM13_KIND **D_80098844;
void func_80036478(void *track, uint8 arg1, uint32 arg2);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
void func_80047228(void *wp, STCOM_SVECTOR *pos, sint32 arg2);

void stcom13_func_01D8(STCOM13_WORK *wp);
sint32 stcom13_func_0DA8(STCOM13_WORK *wp);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 func_80031BEC(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint16 func_80048E6C(void *wp);

#endif // STCOM13_H
