#include "common.h"
#include "stage_common/stcom02.h"

// Shared stage code, linked into 16 stages: r3_st00, r3_st02, r3_st03, r3_st05, r3_st07,
// r3_st08, r3_st0b, r3_st0d, r3_st13, r3_st14, r3_st15, r3_st16, r3_st17, r3_st1a, r3_st1d and
// r3_st1e. Each stage compiles this file against its own copy of the assembly (TARGET_ASM, set
// by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom02"

void stcom02_func_0000(STCOM02_WORK *wp)
{
    stcom02_D_0110[wp->routine_0](wp);
}

void stcom02_func_003C(STCOM02_WORK *wp)
{
    wp->script_1C = wp->step_20 = stcom02_D_0000[wp->type];
    wp->count_C                 = wp->step_20->count;
    wp->frame_D                 = 0;
    wp->dst_18                  = &Clut_buf[wp->script_1C->lo + (wp->script_1C->hi << 8)];
    if (stcom02_func_0334(wp))
    {
        Close_EVE_WORK(wp);
    }
    wp->routine_0 = 1;
}

void stcom02_func_00D8(STCOM02_WORK *wp)
{
    if (wp->count_C < ++wp->frame_D)
    {
        if (stcom02_func_0334(wp))
        {
            Close_EVE_WORK(wp);
        }
    }
    stcom02_func_0140(wp);
}

void stcom02_func_0140(STCOM02_WORK *wp)
{
    sint32 unused[4];
    sint32 src;
    sint32 dst;
    sint32 offset;
    sint32 count;
    sint32 i;
    sint32 r, g, b;
    sint32 dr, dg, db;

    offset = stcom02_D_006C[wp->type].offset;
    count  = stcom02_D_006C[wp->type].count;
    if (stcom02_D_006C[wp->type].blend != 0)
    {
        for (i = 0; i < count; i++)
        {
            src = wp->src_14[i];
            dst = wp->dst_18[i];
            r   = src & 0x1F;
            dr  = ((dst & 0x1F) - r) * wp->frame_D / wp->count_C;
            g   = (src & 0x3E0) >> 5;
            dg  = (((dst & 0x3E0) >> 5) - g) * wp->frame_D / wp->count_C;
            b   = (src & 0x7C00) >> 10;
            db  = (((dst & 0x7C00) >> 10) - b) * wp->frame_D / wp->count_C;
            r += dr;
            g += dg;
            b += db;
            Clut_buf[offset + i] = r | ((g << 5) | 0x8000) | (b << 10);
        }
    }
    else if (wp->frame_D == 0)
    {
        Mem_copy32(wp->src_14, &Clut_buf[offset], count / 16);
    }
}

sint32 stcom02_func_0334(STCOM02_WORK *wp)
{
    sint32 unused[1]; // never used; retail reserves its 8-byte frame
    STCOM02_STEP *step;
    sint8 next;

    step       = wp->step_20;
    wp->src_14 = wp->dst_18;
    next       = step->next;
    if (next < 0)
    {
        if (next == -1)
        {
            if (wp->count_C == wp->frame_D)
            {
                return -1;
            }
        }
        else
        {
            wp->step_20 = wp->script_1C + (next & 0x7F);
        }
    }
    else
    {
        wp->step_20++;
    }
    step        = wp->step_20;
    wp->count_C = step->count;
    wp->frame_D = 0;
    wp->dst_18  = &Clut_buf[step->lo + (step->hi << 8)];
    return 0;
}
