#ifndef STCOM23_H
#define STCOM23_H

#include "common.h"
#include "stage_common/rock_neo.h"

// A 16.16 position also read by its integer halves.
typedef union
{
    STCOM_FIXED_VECTOR v;
    struct
    {
        STCOM_FIXED x, y, z, pad;
    } f;
} STCOM23_FIXED_VECTOR;

// A missile's parameters, by type (stcom23_D_0000, 0x2C bytes each).
typedef struct
{
    uint8 kind_0;        // 00: id while it sets up
    uint8 variant_1;     // 01
    uint16 speed_2;      // 02: starting speed
    sint16 accel_4;      // 04
    uint16 speed_max_6;  // 06
    sint32 turn_8;       // 08: func_80033F04's limits
    sint32 turn_C;       // 0C
    uint32 model_10[3];  // 10
    uint8 type_1C;       // 1C: index into the stcom23_D_0134/013C/0144 tables
    uint8 reserved1D[2]; // 1D
    uint8 size_1F;       // 1F: hit box
    uint8 life_20;       // 20: frames
    uint8 hit_kind_21;   // 21
    uint8 value_22;      // 22: func_80037694's argument
    uint8 reserved23;    // 23
    uint32 hit_mask_24;  // 24: hits that destroy it
    uint8 reserved28[4]; // 28
} STCOM23_PARAM;

// The 0x10C-byte work slot (freed through Close_SHL_WORK) of a homing missile with a smoke
// trail.
typedef struct
{
    uint8 be_flag;                       // 00
    uint8 slot;                          // 01
    uint8 id;                            // 02
    uint8 type;                          // 03
    uint8 reserved04[4];                 // 04
    uint8 routine_0;                     // 08
    uint8 reserved09[2];                 // 09
    uint8 life_B;                        // 0B
    sint8 timer_C;                       // 0C
    uint8 reserved0D[7];                 // 0D
    STCOM_SVECTOR position;              // 14
    STCOM23_FIXED_VECTOR position_fixed; // 1C
    STCOM_SVECTOR position_prev;         // 2C
    STCOM_FIXED_VECTOR fixed_prev;       // 34
    STCOM_SVECTOR velocity;              // 44
    STCOM_SVECTOR accel;                 // 4C
    uint8 reserved54[0x1A];              // 54
    sint16 speed_6E;                     // 6E
    uint8 reserved70[8];                 // 70
    uint32 *model_78;                    // 78
    uint8 reserved7C[0x10];              // 7C
    STCOM_MATRIX matrix;                 // 8C
    STCOM_SVECTOR draw_pos;              // AC
    uint32 color_B4;                     // B4
    STCOM_SVECTOR *target_B8;            // B8
    sint32 value_BC;                     // BC
    sint32 value_C0;                     // C0
    sint32 hit_C4;                       // C4
    sint32 value_C8;                     // C8
    STCOM_SVECTOR dir_CC;                // CC
    STCOM_SVECTOR_W trail[4];            // D4: the last positions, newest first
    uint8 reservedF4[0x18];              // F4
} STCOM23_WORK;

typedef void (*STCOM23_FUNC)(STCOM23_WORK *wp);

// A smoke puff's sprite packet (Billboard_get).
typedef struct
{
    uint32 tag_0;   // 00
    uint32 code_4;  // 04
    uint32 xy_8;    // 08
    uint32 uv_C;    // 0C: and the palette
    uint32 z_10;    // 10
    uint32 uv_14;   // 14: and the texture page
    uint32 size_18; // 18
    uint32 uv_1C;   // 1C
    uint32 pad_20;  // 20
    uint32 uv_24;   // 24
} STCOM23_PACKET;

// A puff's texture corner.
typedef struct
{
    uint8 u, v;
} STCOM23_UV;

extern STCOM23_PARAM stcom23_D_0000[];
extern STCOM23_FUNC stcom23_D_0134[]; // by type_1C: set up
extern STCOM23_FUNC stcom23_D_013C[]; // by type_1C: each frame
extern STCOM23_FUNC stcom23_D_0144[]; // by type_1C: destroyed
extern STCOM23_UV stcom23_D_014C[];   // the four puffs' textures
extern STCOM23_FUNC stcom23_D_0154[]; // routine_0

void stcom23_func_0954(STCOM23_WORK *wp);
void stcom23_func_09FC(STCOM23_WORK *wp);
void stcom23_func_0AAC(STCOM23_WORK *wp);
void stcom23_func_0B18(STCOM23_WORK *wp);

// ROCK_NEO.EXE.
void ApplyMatrix(STCOM_MATRIX *m, STCOM_SVECTOR *v, STCOM_FIXED_VECTOR *out);
void VectorNormal(STCOM_FIXED_VECTOR *v0, STCOM_FIXED_VECTOR *v1);
sint32 VectorNormalS(STCOM_FIXED_VECTOR *v0, STCOM_SVECTOR *v1);
sint32 SquareRoot0(sint32 v);
sint32 ratan2(sint32 y, sint32 x);
sint32 func_80037694(STCOM23_WORK *wp, sint32 arg);
void func_80033F04(STCOM_SVECTOR *out, STCOM_SVECTOR *dir, STCOM_SVECTOR *cur, sint32 a3, sint32 a4);
STCOM23_PACKET *Billboard_get(void);

#endif // STCOM23_H
