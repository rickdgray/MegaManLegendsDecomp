#include "common.h"
#include "st19.h"

void func_8010E6D8(STAGE_SPARK *wp)
{
    STAGE_OBJ *owner;

    owner = wp->owner_2C;
    if (--wp->timer_D == 0 || owner->routine_0 == 2)
    {
        wp->timer_D = 0;
        wp->routine_0++;
    }
    wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
    wp->w_24 += wp->type_F;
    wp->y_1E += wp->rise_28;
}

void func_8010E764(STAGE_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_8010E6D8(wp);
}

void func_8010E798(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_8010E7B8(STAGE_OBJ *wp)
{
    D_801182EC[wp->routine_0](wp);
}

void func_8010E7F4(ST19_SPARK *wp)
{
    ST19_SPARK *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->variant_3 = 1;
            ep->flags_6   = wp->flags_6;
            ep->value_C   = 0;
            ep->timer_D   = (rand() & 7) * 2 + 0x40;
            ep->x_1C      = wp->x_1C + (rand() & 0xF);
            ep->y_1E      = wp->y_1E;
            ep->z_20      = wp->z_20 + (rand() & 0xF);
            ep->mode_14   = 0x3D48004E;
            ep->u_22      = ((rand() & 3) << 5) + 0x20;
            ep->v_23      = 0;
            ep->w_24      = wp->width_E;
            ep->type_F    = wp->type_F;
            ep->rise_28   = wp->rise_28;
            ep->owner_2C  = wp;
            for (i = 0; i < wp->count_26; i++)
            {
                func_8010E7B8(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_8010E93C(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 1)
    {
        func_8010E7B8(wp);
        return;
    }
    if (wp->routine_0 != 2)
    {
        func_8010E7F4(wp);
        return;
    }
    func_80031988((STCOM_EFFECT *)wp);
}

ST19_SPARK *func_8010E99C(STCOM_SVECTOR *pos, sint32 width, sint32 type, sint32 count, sint32 rise,
                          uint8 hide)
{
    ST19_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0;
        ep->variant_3 = 0;
        ep->value_C   = 0;
        ep->width_E   = width;
        ep->type_F    = type;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->count_26  = count;
        if (hide)
        {
            ep->flags_6 |= 0x20;
        }
        else
        {
            ep->flags_6 &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < (sint16)count; i++)
        {
            func_8010E7F4(ep);
        }
    }
    return ep;
}
