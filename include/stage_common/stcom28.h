#ifndef STCOM28_H
#define STCOM28_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The block at +0xCC of the work slot.
typedef struct
{
    uint8 counter_0;       // CC: bobbing step (0..0x1F)
    sint8 turn_1;          // CD: which way it turns while roaming
    uint16 timer_2;        // CE: until it picks a new move
    uint16 timer_4;        // D0: until it picks a new move (waiting)
    uint16 timer_6;        // D2: until it stops charging
    uint16 timer_8;        // D4: until it bursts
    sint16 angle_A;        // D6: the rotation.y it turns to
    uint8 track_C[0x10];   // D8: Track_reset/func_8003648C
    sint32 sees_1C;        // E8: nonzero while it sees the player (func_8003648C)
    sint32 flags_20;       // EC: 1 hit a wall, 2 on the ground, 4 at a ledge
    STCOM_SVECTOR pos_24;  // F0: the hit box's center
    uint32 hit_2C;         // F8: damage in the low 24 bits, kind bits above
    uint32 value_30;       // FC
    STCOM_SVECTOR from_34; // 100: where the hit came from
    uint16 kind_3C;        // 108: the hit box's kind bits
    sint16 step_3E;        // 10A: rotation.x step while charging
} STCOM28_CTL;

// The 0x10C-byte work slot stcom28 runs on (freed through ROCK_NEO's Close_SHL_WORK).
typedef struct
{
    uint8 be_flag;                          // 00
    uint8 slot;                             // 01
    uint8 id;                               // 02: index into D_80098928
    uint8 type;                             // 03
    uint8 reserved04[4];                    // 04
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 routine_2;                        // 0A
    uint8 routine_3;                        // 0B
    uint8 reserved0C[8];                    // 0C
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    STCOM_SVECTOR accel;                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    uint8 reserved64[0x10];                 // 64
    sint8 jump_74;                          // 74: set while it is in the air
    sint8 jump_prev_75;                     // 75
    uint8 reserved76[2];                    // 76
    void *data_78;                          // 78
    uint8 reserved7C[4];                    // 7C
    uint32 value_80;                        // 80: distance to the player (squared?)
    uint8 reserved84[8];                    // 84
    STCOM_MATRIX matrix;                    // 8C
    STCOM_SVECTOR pos_AC;                   // AC: where it is drawn
    uint32 color_B4;                        // B4
    uint8 reservedB8[0x14];                 // B8
    STCOM28_CTL ctl;                        // CC
} STCOM28_WORK;

// A ROCK_NEO record per kind (D_80098928).
typedef struct
{
    uint8 reserved00[0xA];
    uint8 value_A; // ctl.kind_3C while it bursts
} STCOM28_KIND;

typedef void (*STCOM28_FUNC)(STCOM28_WORK *wp);

extern STCOM28_FUNC stcom28_D_0000[]; // routine_0 handlers (stcom28_func_0000)
extern sint16 stcom28_D_000C[];       // data_78
extern STCOM28_FUNC stcom28_D_0018[]; // routine_1 handlers (stcom28_func_00E8)
extern uint16 stcom28_D_0034[];       // bobbing offsets, 32 steps
extern uint16 stcom28_D_0074[];       // move durations, 8 choices

void stcom28_func_00E8(STCOM28_WORK *wp);
void stcom28_func_0294(STCOM28_WORK *wp);
void stcom28_func_0344(STCOM28_WORK *wp);
void stcom28_func_038C(STCOM28_WORK *wp);
void stcom28_func_0468(STCOM28_WORK *wp);
void stcom28_func_0574(STCOM28_WORK *wp);
void stcom28_func_063C(STCOM28_WORK *wp);
void stcom28_func_0678(STCOM28_WORK *wp);
sint32 stcom28_func_0744(STCOM28_WORK *wp);
void stcom28_func_0794(STCOM28_WORK *wp);
void stcom28_func_07F4(STCOM28_WORK *wp);
void stcom28_func_0A14(STCOM28_WORK *wp);
void stcom28_func_0A88(STCOM28_WORK *wp);
void stcom28_func_0BF0(STCOM28_WORK *wp);
void stcom28_func_0CB8(STCOM28_WORK *wp);

// ROCK_NEO.EXE.
extern STCOM28_KIND **D_80098928;
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
sint32 func_80031F84(STCOM_SVECTOR *pos, STCOM_SVECTOR *from, sint32 rot, sint32 arg3);
sint32 func_80031DCC(STCOM_FIXED_VECTOR *pos, sint32 rot, sint32 range, STCOM_FIXED_VECTOR *target, sint32 target_rot, sint32 target_range);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Muku(STCOM_SVECTOR *pos, STCOM_SVECTOR *target, sint32 rot, sint32 speed);
sint32 Obj_ceiling_height_get(void *wp);

#endif // STCOM28_H
