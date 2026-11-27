#include "common.h"
#include "st14.h"

void func_801053B4(ST14_SPLASH *wp)
{
    D_80115A58[wp->routine_0](wp);
}

void func_801053F0(ST14_SPLASH *wp)
{
    ST14_GROW *grow;
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;

    wp->be_flag |= TRANS;
    grow                   = &wp->u_18.s.grow;
    wp->u_18.s.grow.size_4 = 0;
    if (wp->value_C & 1)
    {
        wp->u_18.s.grow.speed_0 = D_801159F4[wp->type][1];
    }
    else
    {
        wp->u_18.s.grow.speed_0 = D_801159F4[wp->type][0];
    }
    grow->accel_2 = D_80115A0C[wp->type][0];
    grow->speed_6 = D_80115A24[wp->type][0];
    grow->accel_8 = D_80115A3C[wp->type][0];
    grow->size_A  = 0;
    Model_work_init(wp, &wp->type);
    rot.x = 0;
    rot.y = ((wp->value_C << 10) & 0x800) - 0x400;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->u_18.matrix);
    scale.x = scale.y = scale.z = grow->size_4;
    ScaleMatrix(&wp->u_18.matrix, &scale);
    wp->color_40  = 0x2808080;
    wp->alpha_A   = 0x80;
    wp->routine_1 = 0;
    wp->routine_0++;
    wp->timer_B = D_80115A54[wp->type];
}

void func_80105578(ST14_SPLASH *wp)
{
    ST14_GROW *grow;
    STCOM_EFFECT *effect;
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;
    sint32 level;
    sint32 timer;
    sint32 gray;

    wp->u_18.s.grow.speed_0 += wp->u_18.s.grow.accel_2;
    wp->u_18.s.grow.size_4 += wp->u_18.s.grow.speed_0;
    grow = &wp->u_18.s.grow;
    if (wp->type != 0)
    {
        timer = wp->timer_B;
        gray  = timer * 4;
        if (timer != 0)
        {
            wp->timer_B--;
        }
        wp->color_40 = 0x2000000 | (gray << 16) | (gray << 8) | gray;
        if (wp->u_18.s.grow.speed_0 < 0)
        {
            func_80031988(wp);
            return;
        }
        scale.x = scale.y = scale.z = wp->u_18.s.grow.size_4;
    }
    else
    {
        if (wp->u_18.s.grow.speed_6 > 0)
        {
            wp->u_18.s.grow.speed_6 += wp->u_18.s.grow.accel_8;
            wp->u_18.s.grow.size_A += wp->u_18.s.grow.speed_6;
            if (wp->u_18.s.grow.speed_6 == 0)
            {
                if (wp->value_C & 1)
                {
                    wp->u_18.s.grow.accel_2 = wp->u_18.s.grow.size_A * 3 / 4;
                }
                else
                {
                    wp->u_18.s.grow.accel_2 = wp->u_18.s.grow.size_A / 2;
                }
                effect = func_80031618();
                if (effect != NULL)
                {
                    effect->be_flag         = MOVE | MODEL;
                    effect->id              = 0x17;
                    effect->type            = 1;
                    effect->value_C         = wp->value_C;
                    effect->sprite.position = wp->pos_38;
                }
            }
            if (grow->speed_6 > 0)
            {
                goto rising;
            }
        }
        level = wp->alpha_A;
        if (level != 0)
        {
            wp->alpha_A -= 0x10;
        }
        wp->color_40 = 0x2000000 | (level << 16) | (level << 8) | level;
        grow->size_A -= 0x32;
        scale.x = scale.y = grow->accel_2 += 0x14;
        goto scaled;
    rising:
        if (wp->value_C & 1)
        {
            scale.x = scale.y = grow->size_A * 3 / 4;
        }
        else
        {
            scale.x = scale.y = grow->size_A / 2;
        }
    scaled:
        scale.z = grow->size_A * 2;
        if (grow->size_A < 0 || wp->alpha_A == 0)
        {
            func_80031988(wp);
            return;
        }
    }
    rot.x = 0;
    rot.y = ((wp->value_C << 10) & 0x800) - 0x400;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->u_18.matrix);
    ScaleMatrix(&wp->u_18.matrix, &scale);
}

void func_8010583C(ST14_SPLASH *wp)
{
    func_80031988(wp);
}
