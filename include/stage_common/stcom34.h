#ifndef STCOM34_H
#define STCOM34_H

#include "common.h"
#include "stage_common/rock_neo.h"

// One spark: a short line flying out from the owner.
typedef struct
{
    uint8 yaw_0;    // 0: direction / 0x80
    uint8 pitch_1;  // 1: elevation / 0x100
    sint8 delay_2;  // 2: frames before it starts
    uint8 length_3; // 3
    uint8 speed_4;  // 4: slows down to 2
    uint8 reserved5;
    sint16 dist_6; // 6: from the owner; it starts over below 8
} STCOM34_SPARK;

// A spark's settings by variant_3.
typedef struct
{
    uint8 length_0; // 0: plus 0..0x1F
    uint8 reserved1;
    uint16 speed_2; // 2
    uint16 dist_4;  // 4: plus 0..0x3F
    uint16 reserved6;
} STCOM34_KIND;

// The 0x48-byte effect slot (freed through ROCK_NEO's func_80031988).
typedef struct
{
    uint8 flags_0;             // 00
    uint8 reserved01[2];       // 01
    uint8 variant_3;           // 03
    uint8 reserved04[4];       // 04
    uint8 routine_0;           // 08
    uint8 routine_1;           // 09
    uint8 routine_2;           // 0A
    uint8 routine_3;           // 0B
    sint8 owner_C;             // 0C: the work slot the sparks fly from (func_80036294)
    uint8 value_D;             // 0D
    uint8 value_E;             // 0E
    uint8 value_F;             // 0F
    uint8 reserved10[0x18];    // 10
    STCOM34_SPARK spark_28[4]; // 28
} STCOM34_WORK;

// The work slot the sparks come from: only its position.
typedef struct
{
    uint8 reserved00[0x38];
    STCOM_SVECTOR pos_38; // 38
} STCOM34_OWNER;

// A 3D line packet from Billboard_line_get, drawn later by ROCK_NEO.
typedef struct
{
    uint32 xy1_0;   // 00: the far end's x and y
    uint32 color_4; // 04: code 0x52 and the color
    uint32 xy0_8;   // 08: the near end's x and y
    uint32 color_C; // 0C: the far end's color
    uint32 z_10;    // 10: the near end's z, the far end's z << 16
    uint32 reserved14;
    uint32 mode_18; // 18: draw mode
} STCOM34_LINE;

// The x and y halves of an STCOM_SVECTOR read as one word.
typedef struct
{
    uint32 xy;
} STCOM34_XY;

typedef void (*STCOM34_FUNC)(STCOM34_WORK *wp);

extern STCOM34_KIND stcom34_D_0000[]; // by variant_3
extern STCOM34_FUNC stcom34_D_0010[]; // routine_0 handlers (stcom34_func_0000)

void stcom34_func_04CC(STCOM_SVECTOR a, STCOM_SVECTOR b, uint8 shade);

// ROCK_NEO.EXE.
STCOM34_OWNER *func_80036294(sint32 id);
STCOM34_LINE *Billboard_line_get(void);
void func_80031988(STCOM34_WORK *wp);

// The scratchpad's frame counter.
#define STCOM34_FRAME (*(uint16 *)0x1F800002)

#endif // STCOM34_H
