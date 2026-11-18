#include "common.h"
#include "stage_common/stcom33.h"

// Shared stage code, linked into 4 stages: r3_st09, r3_st0e, r3_st11 and r3_st14. Each stage
// compiles this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the
// names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom33"

// Scrolls a texture in VRAM (running water) once a scene flag is set.
void stcom33_func_0000(STCOM33_WORK *wp)
{
    stcom33_D_003C[wp->routine_0](wp);
}

void stcom33_func_003C(STCOM33_WORK *wp)
{
    wp->routine_1 = 0;
    wp->scroll_A  = 0;
    wp->reverse_B = 0;
    wp->routine_0++;
}

void stcom33_func_0058(STCOM33_WORK *wp)
{
    RECT rect;
    STCOM33_DR_MOVE *p;
    sint32 ofs;
    sint32 v;

    v   = wp->variant_3;
    ofs = wp->scroll_A;
    if (Sce_flag_test(stcom33_D_0000[v].flag_A) == 0)
    {
        return;
    }
    if (wp->strips_C != 2)
    {
        p      = STCOM33_PACKET_PTR++;
        rect.x = stcom33_D_0000[v].x0;
        rect.y = stcom33_D_0000[v].y0 + ofs;
        rect.w = 0x10;
        rect.h = 0x40 - ofs;
        SetDrawMove(p, &rect, stcom33_D_0000[v].x0, stcom33_D_0000[v].y0 - 0x40);
        addPrim(&D_80098934->ot_88, p);
        if (ofs != 0)
        {
            p      = STCOM33_PACKET_PTR++;
            rect.y = stcom33_D_0000[v].y0;
            rect.h = ofs;
            SetDrawMove(p, &rect, stcom33_D_0000[v].x0, stcom33_D_0000[v].y0 - ofs);
            addPrim(&D_80098934->ot_88, p);
        }
    }
    ofs >>= 1;
    if (wp->strips_C != 1)
    {
        p      = STCOM33_PACKET_PTR++;
        rect.x = stcom33_D_0000[v].x1;
        rect.y = stcom33_D_0000[v].y1 + ofs;
        rect.w = 8;
        rect.h = 0x20 - ofs;
        SetDrawMove(p, &rect, stcom33_D_0000[v].x1, stcom33_D_0000[v].y1 - 0x20);
        addPrim(&D_80098934->ot_88, p);
        if (ofs != 0)
        {
            p      = STCOM33_PACKET_PTR++;
            rect.y = stcom33_D_0000[v].y1;
            rect.h = ofs;
            SetDrawMove(p, &rect, stcom33_D_0000[v].x1, stcom33_D_0000[v].y1 - ofs);
            addPrim(&D_80098934->ot_88, p);
        }
    }
    if (wp->reverse_B != 0)
    {
        wp->scroll_A = (wp->scroll_A + stcom33_D_0000[v].speed_8) & 0x3F;
    }
    else
    {
        wp->scroll_A = (wp->scroll_A - stcom33_D_0000[v].speed_8) & 0x3F;
    }
}
