#include "common.h"
#include "st00.h"

void func_80118FB8(STAGE_OBJ *wp)
{
    D_8011CE74[wp->routine_0](wp);
}

void func_80118FF4(STAGE_EVENT *ep)
{
    ST00_CLUT_SCROLL *wp;
    uint32 i;
    uint32 set;

    wp = (ST00_CLUT_SCROLL *)ep;
    for (i = 0; i < 3; i++)
    {
        set = Stage_hed_model_get(D_8011CE7C[i]);
        if (set == 0)
        {
            Close_EVE_WORK(ep);
            return;
        }
        wp->set_18[i] = (ST00_TEX_SET *)(set & 0xFFFFFF);
    }
    wp->routine_0++;
    wp->scroll_C = 0;
    wp->value_14 = 0;
    wp->timer_B  = 0;
    Mem_copy32((void *)(wp->set_18[0]->clut_18->data_8 & 0xFFFFFF), D_80122640[0], 1);
    Mem_copy32((void *)(wp->set_18[0]->clut_1C->data_8 & 0xFFFFFF), D_80122640[1], 1);
    Mem_copy32((void *)(wp->set_18[1]->clut_18->data_8 & 0xFFFFFF), D_80122640[2], 1);
    Mem_copy32((void *)(wp->set_18[1]->clut_1C->data_8 & 0xFFFFFF), D_80122640[3], 1);
    Mem_copy32((void *)(wp->set_18[2]->clut_18->data_8 & 0xFFFFFF), D_80122640[4], 1);
    Mem_copy32((void *)(wp->set_18[2]->clut_1C->data_8 & 0xFFFFFF), D_80122640[5], 1);
}

// k holds the scroll step before it counts the CLUT loop (retail reuses its register). The second
// CLUT word is read through a pointer at k + 1 plus a byte offset, which keeps the row offset out
// of loop.c's induction pointer.
void func_8011917C(ST00_CLUT_SCROLL *wp)
{
    STAGE_UNPACK u;
    STAGE_UV4 uv;
    sint32 wrap;
    uint32 add;
    uint32 i;
    uint32 k;
    uint32 *dst;
    uint32 *src;

    wrap = 0;
    wp->scroll_C += 0x1000;
    if (wp->scroll_C > 0x3FFFF)
    {
        wp->scroll_C -= 0x40000;
        wrap = 1;
    }
    k = (wp->scroll_C >> 12) & 0x3F;
    if ((uint8)++wp->timer_B * 128 >= 0x800)
    {
        wp->timer_B = 0;
    }
    add = k | k << 16;
    for (i = 0; i < 3; i++)
    {
        dst = (uint32 *)(wp->set_18[i]->clut_18->data_8 & 0xFFFFFF);
        for (k = 0; k < 8; k += 2)
        {
            dst[k]     = D_80122640[i * 2][k] + add;
            src        = D_80122640[0] + k + 1;
            dst[k + 1] = *(uint32 *)((uint8 *)src + (i << 6)) + add;
        }
    }
    for (i = 0; i < 4; i++)
    {
        u = func_8002DC84((void *)Stage_hed_model_get(D_8011CE88[i].key), D_8011CE88[i].i, D_8011CE88[i].j);
        for (k = 0; k < D_8011CE88[i].count; k++)
        {
            uv = func_8002DD1C(u.c, k);
            uv.b[0]++;
            uv.b[2]++;
            uv.b[4]++;
            uv.b[6]++;
            if (wrap)
            {
                uv.b[0] -= 0x40;
                uv.b[2] -= 0x40;
                uv.b[4] -= 0x40;
                uv.b[6] -= 0x40;
            }
            func_8002DE04(u.c, k, uv.w);
        }
    }
}

void func_80119398(STAGE_OBJ *wp)
{
    D_8011CF48[wp->routine_0](wp);
}

void func_801193D4(STCOM02_WORK *wp)
{
    wp->script_1C = wp->step_20 = D_8011CF28[wp->index_3];
    wp->count_C                 = wp->step_20->count;
    wp->frame_D                 = 0;
    wp->dst_18                  = &Clut_buf[wp->script_1C->lo + (wp->script_1C->hi << 8)];
    if (func_8011974C(wp))
    {
        func_80031988(wp);
    }
    wp->routine_0 = 1;
}

void func_80119470(STCOM02_WORK *wp)
{
    STCOM02_STEP *step;

    step = wp->step_20;
    if (wp->count_C < ++wp->frame_D && func_8011974C(wp) != 0)
    {
        func_80031988(wp);
    }
    if (wp->index_3 == 1 && step->lo == 0x70)
    {
        wp->script_1C = wp->step_20 = D_8011CF28[1];
        wp->routine_0               = 2;
    }
    func_80119580(wp);
}

void func_80119518(STCOM02_WORK *wp)
{
    if (wp->count_C < ++wp->frame_D && func_8011974C(wp) != 0)
    {
        func_80031988(wp);
    }
    func_80119580(wp);
}

void func_80119580(STCOM02_WORK *wp)
{
    sint32 unused[2];
    sint32 src;
    sint32 dst;
    sint32 offset;
    sint32 i;
    sint32 r, g, b;
    sint32 dr, dg, db;

    offset = D_8011CF38[wp->index_3].offset;
    if (D_8011CF38[wp->index_3].blend != 0)
    {
        for (i = 0; i < 16; i++)
        {
            src = wp->src_14[i];
            dst = wp->dst_18[i];
            r   = src & 0x1F;
            dr  = ((dst & 0x1F) - r) * wp->frame_D / wp->count_C;
            g   = (src & 0x3E0) >> 5;
            // A one-pass block (perhaps a Capcom macro) weights these registers as retail does.
            do
            {
                dg = (((dst & 0x3E0) >> 5) - g) * wp->frame_D / wp->count_C;
                b  = (src & 0x7C00) >> 10;
                db = (((dst & 0x7C00) >> 10) - b) * wp->frame_D / wp->count_C;
            } while (0);
            Clut_buf[offset + i] = (r + dr) | (((g + dg) << 5) | 0x8000) | ((b + db) << 10);
        }
    }
    else if (wp->frame_D == 0)
    {
        Mem_copy32(wp->src_14, &Clut_buf[offset], 1);
    }
}

sint32 func_8011974C(STCOM02_WORK *wp)
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
