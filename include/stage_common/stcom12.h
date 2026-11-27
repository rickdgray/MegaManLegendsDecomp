#ifndef STCOM12_H
#define STCOM12_H

#include "common.h"
#include "stage_common/rock_neo.h"

// Positive test first: GCC 2.7 reserves a stack temporary for each use.
#define STCOM12_ABS(x) ((x) >= 0 ? (x) : -(x))

// A scratchpad halfword that seeds the random turn (stcom12_func_0D68).
#define STCOM12_SCRATCH_2 (*(uint16 *)0x1F800002)

// The block at +0x348 of the work slot.
typedef struct
{
    uint16 counter_0;      // 348: frames spent bumping into walls (stcom12_func_0F28)
    sint16 goal_2;         // 34A: angle to turn to (routine_1 20)
    sint16 timer_4;        // 34C: countdown
    uint8 reserved06[2];   // 34E
    uint32 dist_8;         // 350: distance to the player
    uint32 hit_C;          // 354: hit flags, cleared every frame
    uint32 value_10;       // 358
    STCOM_SVECTOR pos_14;  // 35C: the position, 30 units up (routine_0 1)
    sint16 decel_1C;       // 364: slows velocity.x (stcom12_func_08F8)
    sint16 value_1E;       // 366
    sint16 value_20;       // 368
    uint8 reserved22[2];   // 36A
    STCOM_SVECTOR home_24; // 36C: where it started
} STCOM12_CTL;

// The 0x3C0-byte work slot stcom12 runs on (freed through ROCK_NEO's func_80031824): a creature
// that wanders near its home, flees from the player and can be picked up.
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 reserved02;                       // 02
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    sint8 param_C;                          // 0C: message
    sint8 param_D;                          // 0D: how far it may wander (units of 128)
    sint8 param_E;                          // 0E: size (stcom12_D_0038)
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
    sint16 turn_64;                         // 64: turn speed
    uint16 turn_66;                         // 66: turn per frame while wandering
    uint8 reserved68[6];                    // 68
    sint16 value_6E;                        // 6E
    uint8 reserved70[4];                    // 70
    uint8 value_74;                         // 74
    uint8 reserved75[3];                    // 75
    void *data_78;                          // 78
    uint8 reserved7C[0x2B];                 // 7C
    sint8 state_A7;                         // A7: negative when the animation ends
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 value_B0;                        // B0
    sint16 value_B2;                        // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180
    uint8 reserved188[0x1C0];               // 188
    STCOM12_CTL ctl;                        // 348
    uint8 reserved374[0x4C];                // 374
} STCOM12_WORK;

typedef void (*STCOM12_FUNC)(STCOM12_WORK *wp);

extern STCOM12_FUNC stcom12_D_0000[];     // routine_0 handlers (stcom12_func_0000)
extern uint8 stcom12_D_0020[];            // data_10
extern uint8 stcom12_D_002C[];            // data_78
extern uint16 stcom12_D_0038[];           // scale by param_E
extern STCOM_FIXED_VECTOR stcom12_E_0000; // another object's data: where the player is put

// ROCK_NEO.EXE.
sint16 Angle_diff_clamp(sint32 goal, sint32 rot, sint32 speed);
sint32 func_80030418(void *a, void *b, STCOM_SVECTOR *size, STCOM_FIXED_VECTOR *out);
void func_8001E3F0(sint32 arg);

uint8 stcom12_func_0F98(STCOM12_WORK *wp);
sint32 stcom12_func_0DE4(STCOM12_WORK *wp);
void stcom12_func_0D68(STCOM12_WORK *wp, uint32 hit);
void stcom12_func_0E9C(STCOM12_WORK *wp, uint32 hit);
void stcom12_func_0F28(STCOM12_WORK *wp, uint32 hit);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint16 Obj_ceiling_height_get(void *wp);

#endif // STCOM12_H
