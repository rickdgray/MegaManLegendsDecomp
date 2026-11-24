#ifndef STCOM09_H
#define STCOM09_H

#include "common.h"
#include "stage_common/rock_neo.h"

// The hit block at +0x308 of the work slot (registered through func_800341BC).
typedef struct
{
    uint16 flags_0;      // 308
    sint16 timer_2;      // 30A: set when hit
    uint32 value_4;      // 30C
    STCOM_SVECTOR pos_8; // 310: the hit box's center
    sint16 ofs_10;       // 318: its offset from the position, turned with rotation.y
    sint16 ofs_12;       // 31A
    sint16 ofs_14;       // 31C
    sint16 size_16;      // 31E
    uint32 hit_18;       // 320: damage in the low 24 bits, kind bits above
    uint8 reserved1C[4]; // 324
} STCOM09_HIT;

// The 0x10C-byte slot stcom09_func_0D28 spawns (stcom06's emitter, kind 6).
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
    uint8 reserved66[0x36];            // 66
    sint32 speed_9C;                   // 9C
    sint32 rise_A0;                    // A0
} STCOM09_SHOT;

// A matrix whose identity setup writes its halfwords two at a time.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STCOM09_MATRIX;

// The 0x3C0-byte work slot stcom09 runs on (freed through ROCK_NEO's func_80031824).
typedef struct
{
    uint8 flags_0;                          // 00
    uint8 value_1;                          // 01
    uint8 kind_2;                           // 02: index into D_80098844
    uint8 index_3;                          // 03: stcom09_D_0000 handler
    uint8 reserved04[2];                    // 04
    uint8 flags_6;                          // 06
    uint8 reserved07;                       // 07
    uint8 routine_0;                        // 08
    uint8 routine_1;                        // 09
    uint8 timer_A;                          // 0A
    uint8 reserved0B;                       // 0B
    sint8 flag_C;                           // 0C: scene flag 0x400 + this
    sint8 value_D;                          // 0D: message kind
    sint8 param_E;                          // 0E
    uint8 reserved0F;                       // 0F
    void *data_10;                          // 10
    STCOM_SVECTOR position;                 // 14
    STCOM_FIXED_VECTOR position_fixed;      // 1C: position as 16.16
    STCOM_SVECTOR position_prev;            // 2C
    STCOM_FIXED_VECTOR position_fixed_prev; // 34
    STCOM_SVECTOR velocity;                 // 44
    uint8 reserved4C[8];                    // 4C
    STCOM_SVECTOR rotation;                 // 54
    STCOM_SVECTOR rotation_prev;            // 5C
    sint16 turn_64;                         // 64
    uint8 reserved66[8];                    // 66
    sint16 life_6E;                         // 6E
    uint8 reserved70[4];                    // 70
    uint8 value_74;                         // 74
    uint8 reserved75[3];                    // 75
    void *data_78;                          // 78
    uint8 reserved7C[0x2B];                 // 7C
    sint8 flags_A7;                         // A7: sign bit set when the animation ends
    uint8 reservedA8[4];                    // A8
    uint8 anim_AC;                          // AC
    uint8 anim_prev_AD;                     // AD
    uint8 reservedAE[2];                    // AE
    sint16 life_max_B0;                     // B0
    sint16 life_prev_B2;                    // B2
    uint8 reservedB4[0x10];                 // B4
    STCOM_SVECTOR value_C4;                 // C4
    uint8 reservedCC[0x8C];                 // CC
    STCOM_SVECTOR_W scale;                  // 158: x, y, z and a color in pad
    uint8 reserved160[0x20];                // 160
    STCOM_SVECTOR value_180;                // 180
    uint8 reserved188[0x180];               // 188
    STCOM09_HIT hit;                        // 308
    uint8 track_328[0x98];                  // 328
} STCOM09_WORK;

// A ROCK_NEO record per kind (D_80098844): only the life byte.
typedef struct
{
    uint8 reserved00[8];
    uint8 life_8;
} STCOM09_KIND;

typedef void (*STCOM09_FUNC)(STCOM09_WORK *wp);

extern STCOM09_FUNC stcom09_D_0000[]; // handlers by index_3 (stcom09_func_0000)
extern STCOM09_FUNC stcom09_D_0008[]; // routine_0 handlers (stcom09_func_06A0)
extern uint8 stcom09_D_001C[];        // data_10
extern uint8 stcom09_D_0028[];        // data_78

// ROCK_NEO.EXE.
extern STCOM09_KIND **D_80098844;
extern uint8 *D_8008CE74; // a message script
STCOM09_SHOT *Open_SHL_WORK(void);
void Track_reset(void *track, uint8 arg1, uint32 arg2);
sint32 func_8003648C(void *track, void *wp);
void func_80047148(void *wp, STCOM_SVECTOR *pos, STCOM_EFFECT *effect);
sint32 func_80030418(void *a, void *b, STCOM_SVECTOR *size, STCOM_FIXED_VECTOR *out);
sint32 Sce_flag_test(sint32 flag);
sint32 MojiTaskExec(sint32 arg0, uint8 *script, sint32 arg2);
// PsyQ libgte.
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);
STCOM_SVECTOR *ApplyMatrixSV(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_SVECTOR *r);

STCOM_SVECTOR *stcom09_func_0C48(STCOM_SVECTOR *out, sint32 angle, sint32 x, sint32 y, sint32 z);
void stcom09_func_00CC(STCOM09_WORK *wp);
uint8 stcom09_func_0AFC(STCOM09_WORK *wp);
uint8 stcom09_func_0B48(STCOM09_WORK *wp);
void stcom09_func_0BE0(STCOM09_WORK *wp);
uint8 stcom09_func_0D28(STCOM09_WORK *wp);

// ROCK_NEO.EXE (see rock_neo.h).
sint16 Obj_ceiling_height_get(void *wp);

#endif // STCOM09_H
