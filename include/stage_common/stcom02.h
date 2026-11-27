#ifndef STCOM02_H
#define STCOM02_H

#include "common.h"
#include "stage_common/rock_neo.h"

// One step of a palette fade script: the target palette at Clut_buf[lo | hi << 8], reached in
// `count` frames, then `next`: >= 0 goes on to the next step, -1 holds, -0x80 | n loops to step n.
typedef struct
{
    uint8 lo;
    uint8 hi;
    uint8 count;
    sint8 next;
} STCOM02_STEP;

// A palette range: Clut_buf[offset], `count` colors; `blend` 0 copies whole steps instead of
// blending between them.
typedef struct
{
    uint16 offset;
    uint16 count;
    uint16 blend;
} STCOM02_RANGE;

// The 0x24-byte event slot stcom02 runs on (freed through Close_EVE_WORK).
typedef struct
{
    uint8 be_flag;           // 00
    uint8 work_id;           // 01
    uint8 reserved02;        // 02
    uint8 type;              // 03: which script and range
    uint8 reserved04[4];     // 04
    uint8 routine_0;         // 08
    uint8 reserved09[3];     // 09
    sint8 count_C;           // 0C: frames in this step
    sint8 frame_D;           // 0D: frames done
    uint8 reserved0E[6];     // 0E
    uint16 *src_14;          // 14: palette blended from
    uint16 *dst_18;          // 18: palette blended to
    STCOM02_STEP *script_1C; // 1C: first step
    STCOM02_STEP *step_20;   // 20: current step
} STCOM02_WORK;

typedef void (*STCOM02_FUNC)(STCOM02_WORK *wp);

extern STCOM02_STEP *stcom02_D_0000[]; // scripts, by type
extern STCOM02_RANGE stcom02_D_006C[]; // palette ranges, by type
extern STCOM02_FUNC stcom02_D_0110[];  // routine_0 handlers (stcom02_func_0000)

void stcom02_func_0140(STCOM02_WORK *wp);
sint32 stcom02_func_0334(STCOM02_WORK *wp);

#endif // STCOM02_H
