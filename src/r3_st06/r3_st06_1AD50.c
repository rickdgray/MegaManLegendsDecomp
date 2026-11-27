#include "common.h"
#include "st06.h"

void func_8011AD50(STAGE_OBJ *wp)
{
    D_80125A6C[wp->routine_0](wp);
}

void func_8011AD8C(STAGE_OBJ *wp)
{
    uint32 temp_v0;

    temp_v0                = Stage_hed_model_get(0x200000);
    D_8012BB18             = 0;
    wp->position_fixed.v.x = (sint32)temp_v0;
    wp->routine_0++;
}

void func_8011ADD0(ST06_EVENT *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK unpack;
    sint16 i;
    sint16 wrap;

    wrap = 0;
    D_8012BB18++;
    unpack = func_8002DC84(wp->slot_1C, 0, 2);
    for (i = 0; i < 8; i++)
    {
        uv = func_8002DD1C(unpack.c, i);
        if (wrap || (i == 0 && uv.b[0] >= 0xA0))
        {
            wrap = 1;
            uv.b[0] -= 0x1F;
            uv.b[2] -= 0x1F;
            uv.b[4] -= 0x1F;
            uv.b[6] -= 0x1F;
        }
        else
        {
            uv.b[0]++;
            uv.b[2]++;
            uv.b[4]++;
            uv.b[6]++;
        }
        func_8002DE04(unpack.c, i, uv.w);
    }
    unpack = func_8002DC84(wp->slot_1C, 1, 2);
    for (i = 0; i < 4; i++)
    {
        uv = func_8002DD1C(unpack.c, i);
        if (wrap)
        {
            uv.b[0] -= 0x1F;
            uv.b[2] -= 0x1F;
            uv.b[4] -= 0x1F;
            uv.b[6] -= 0x1F;
        }
        else
        {
            uv.b[0]++;
            uv.b[2]++;
            uv.b[4]++;
            uv.b[6]++;
        }
        func_8002DE04(unpack.c, i, uv.w);
    }
}

void func_8011AFD0(STAGE_OBJ *wp)
{
    D_80125A74[wp->routine_0](wp);
}

void func_8011B00C(ST06_EVENT *wp)
{
    ST06_SLOT50 *slot;
    ST06_SHOT *shot;
    STCOM_EFFECT *fx;
    sint32 i;

    if (Sce_flag_test(0x640))
    {
        wp->routine_0 = 2;
        return;
    }
    slot = (ST06_SLOT50 *)func_80031734();
    if (slot != NULL)
    {
        slot->be_flag = 1;
        slot->id      = 0x13;
        slot->value_4 = 0;
        slot->type    = 0;
        slot->value_C = 0;
        wp->slot_1C   = slot;
    }
    shot = (ST06_SHOT *)Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->be_flag = 1;
        shot->id      = 0xF;
        shot->type    = 0;
        shot->value_C = 0;
    }
    for (i = 0; i < 6; i++)
    {
        fx = func_80031618();
        if (fx != NULL)
        {
            D_8012BB20[i] = fx;
            fx->be_flag   = 1;
            fx->id        = 0xC;
            fx->type      = 0;
            fx->value_C   = 0;
            fx->value_D   = 0;
            fx->timer_E   = i;
            fx->value_F   = 0;
            fx->routine_1 = 6 - i * 2;
            fx->routine_2 = 0;
        }
    }
    for (i = 0; i < 7; i++)
    {
        D_8012BB3C[i] = func_80037C14(Map_cell_get(&D_80125A80[i]));
    }
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_8011B164(ST06_EVENT *wp)
{
    sint32 level;

    level = func_8011B444();
    func_8011B4E0(level);
    if (wp->routine_1 == 0)
    {
        if (STAGE_SCENE_BYTE(0) == 0)
        {
            if (Sce_flag_test(0x627) && !Sce_flag_test(0x622) && func_80042208())
            {
                Sce_flag_on(0x621);
                Sce_flag_on(0x622);
            }
            else if (level < 0x7E && !Sce_flag_test(0x623) && !Sce_flag_test(0x624) && !Sce_flag_test(0x625) && func_80042208())
            {
                Sce_flag_on(0x621);
                Sce_flag_on(0x623);
            }
            else if (level < 0x3F && Sce_flag_test(0x623) && !Sce_flag_test(0x624) && !Sce_flag_test(0x625) && func_80042208())
            {
                Sce_flag_on(0x621);
                Sce_flag_on(0x624);
            }
            else if (level == 0 && Sce_flag_test(0x623) && Sce_flag_test(0x624) && !Sce_flag_test(0x625) && func_80042208())
            {
                Sce_flag_on(0x621);
                Sce_flag_on(0x625);
                if (!Sce_flag_test(0x629))
                {
                    Sce_flag_on(0x629);
                }
            }
            else if (Sce_flag_test(0x628) && !Sce_flag_test(0x626) && func_80042208())
            {
                Sce_flag_on(0x621);
                Sce_flag_on(0x626);
                wp->routine_1++;
            }
        }
    }
    else
    {
        if (!Sce_flag_test(0x629) && level == 0)
        {
            Sce_flag_on(0x629);
        }
        if (Sce_flag_test(0x640))
        {
            Sound_fade_start(0x10);
            wp->routine_1 = 0;
            wp->routine_0++;
        }
    }
}

void func_8011B3E0(STAGE_EVENT *wp)
{
    sint32 i;

    for (i = 0; i < 6; i++)
    {
        func_80031988(D_8012BB20[i]);
    }
    Close_EVE_WORK(wp);
}

sint32 func_8011B444(void)
{
    sint32 i;
    sint32 best;
    sint32 d;

    i    = 0;
    best = 0xBB;
    for (; i < 7; i++)
    {
        d = func_80037C14(Map_cell_get(&D_80125A80[i]));
        if (d < D_8012BB3C[i] && d < best)
        {
            best = d;
        }
        D_8012BB3C[i] = d;
    }
    return best;
}

void func_8011B4E0(sint32 level)
{
    sint32 i;

    if (level < 0x9C)
    {
        D_8012BB20[0]->value_F = 1;
    }
    if (level < 0x7D)
    {
        D_8012BB20[1]->value_F = 1;
    }
    if (level < 0x5E)
    {
        D_8012BB20[2]->value_F = 1;
    }
    if (level < 0x3E)
    {
        D_8012BB20[3]->value_F = 1;
    }
    if (level < 0x1F)
    {
        D_8012BB20[4]->value_F = 1;
    }
    if (level == 0)
    {
        D_8012BB20[5]->value_F = 1;
        for (i = 0; i < 6; i++)
        {
            D_8012BB20[i]->sprite.value_12 = 1;
        }
    }
}
