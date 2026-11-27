#ifndef STCOM07_H
#define STCOM07_H

#include "common.h"
#include "stage_common/rock_neo.h"

// One textured quad's UV block in a model (12 bytes): four (u, v) pairs, also written as words.
typedef struct
{
    union
    {
        uint32 words[2];
        uint8 uv[8]; // u0, v0, u1, v1, u2, v2, u3, v3
    } tex;
    uint8 reserved08[4];
} STCOM07_QUAD;

// A matrix whose identity setup writes its halfwords two at a time.
typedef union
{
    STCOM_MATRIX m;
    sint32 words[8];
} STCOM07_MATRIX;

// Per-quad v steps for the slide (stcom07_D_001C).
typedef struct
{
    uint8 v0, v1, v2, v3;
} STCOM07_STEP;

// The work slot stcom07 runs on: a door whose four quads slide by scrolling their texture.
typedef struct
{
    uint8 be_flag;          // 00
    uint8 work_id;          // 01
    uint8 reserved02;       // 02
    uint8 type;             // 03: picks the UV set (stcom07_func_003C)
    uint8 reserved04[4];    // 04
    uint8 routine_0;        // 08
    uint8 reserved09[2];    // 09
    uint8 timer_B;          // 0B: 0..24 slide frames
    sint8 rot_C;            // 0C: quarter turns
    uint8 reserved0D[7];    // 0D
    uint32 model_14;        // 14
    STCOM07_MATRIX matrix;  // 18
    STCOM_SVECTOR position; // 38
    uint32 color_40;        // 40
    STCOM07_QUAD *quad_44;  // 44
} STCOM07_WORK;

typedef void (*STCOM07_FUNC)(STCOM07_WORK *wp);

extern STCOM07_FUNC stcom07_D_0000[]; // routine_0 handlers (stcom07_func_0000)
extern STCOM07_STEP stcom07_D_001C[]; // v steps per quad

// ROCK_NEO.EXE.
STCOM07_QUAD *Model_face_get(uint32 model, sint32 arg);
sint32 Map_cell_get(STCOM_SVECTOR *pos);
sint32 Sce_flag_test(sint32 flag);
// PsyQ libgte.
STCOM_MATRIX *RotMatrixY(sint32 r, STCOM_MATRIX *m);

#endif // STCOM07_H
