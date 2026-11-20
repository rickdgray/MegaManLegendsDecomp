#include "common.h"
#include "st0e.h"

void func_801085B4(STAGE_OBJ *wp)
{
    func_80107C58(wp);
}

void func_801085D4(STAGE_OBJ *wp)
{
    D_80110508[wp->routine_0](wp);
}

void func_80108610(ST0E_VIEW *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_48.h[0]  = 0;
    wp->u_44.h[1]  = 0;
    wp->u_44.h[0]  = 0;
    wp->value_50   = 0;
    wp->u_4C.h[1]  = 0;
    wp->u_4C.h[0]  = 0;
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->value_78  = 0;
    wp->value_6E  = 0;
    wp->u_74.b[0] = 0;
    wp->value_E8  = 0;
    wp->value_EC  = 0;
    wp->value_F0  = 0;
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80108694(ST0E_VIEW *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR *rot;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->value_B4            = 0x808080;
    func_80108820(wp);
    rot = &wp->rotation;
    if (wp->routine_0 != 2)
    {
        func_80108980(wp);
        wp->value_E8 = 0;
        wp->vec_E0   = wp->position;
        wp->vec_E0.y -= 0x80;
        func_800341BC(&wp->vec_E0, 0x80, 0, 0x8000, wp->value_1, &wp->value_E8, 0x04080000, 0, 0);
        wp->vec_AC = wp->position;
        RotMatrix(rot, &wp->matrix_8C);
        scale.x = 0x200;
        scale.y = 0x200;
        scale.z = 0x200;
        ScaleMatrix(&wp->matrix_8C, &scale);
        if (wp->flags_0 & 2)
        {
            Model_Shadow_Trans(wp, 0x80, 0x200, 0);
        }
    }
}

void func_80108820(ST0E_VIEW *wp)
{
    STCOM_EFFECT *fx;
    sint32 damage;

    damage = wp->value_E8 & 0xFFFFFF;
    if (damage != 0)
    {
        wp->value_6E += damage;
        Sound_call2(0xA0, &wp->position);
        wp->value_B4 = 0xFFFFFF;
        if (wp->value_6E >= D_80098928[wp->kind_2]->life_8 * 16)
        {
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 5;
                fx->kind_2          = 0x80;
                fx->variant_3       = 0;
                fx->sprite.position = wp->position;
            }
#ifdef __wasm32__
            func_80047148(wp, &wp->position);
#else
            func_80047148(wp, &wp->position, fx);
#endif
            while (D_80110504 < 8)
            {
                func_80108A44(wp);
                D_80110504++;
            }
            func_80108AE4(wp);
            func_80108AE4(wp);
            Sound_call2(0x157, &wp->position);
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
        }
    }
}

void func_80108980(ST0E_VIEW *wp)
{
    uint16 temp_v0;

    if (((uint32)wp->value_80 <= 0x22550FU) && ((uint16)D_80110504 < 8))
    {
        temp_v0 = wp->value_F0;
        if (temp_v0 == 0)
        {
            wp->value_F0 = D_80110514[rand() & 7];
            Sound_call2(0x157, &wp->position);
            func_80108A44(wp);
            func_80108AE4(wp);
            D_80110504++;
            return;
        }
        wp->value_F0 = temp_v0 - 1;
    }
}

void func_80108A44(ST0E_VIEW *wp)
{
    STAGE_OBJ *obj;
    obj = func_80031418();
    if (obj != NULL)
    {
        obj->flags_0          = 1;
        obj->kind_2           = 0x3E;
        obj->variant_3        = 0;
        obj->routine_0        = 0;
        obj->routine_1        = 0;
        obj->routine_2        = 0;
        obj->routine_3        = 0;
        obj->position         = wp->position;
        obj->position_fixed.v = wp->position_fixed;
        obj->rotation.x       = 0;
        obj->rotation.y       = 0;
        obj->rotation.z       = 0;
    }
}

void func_80108AE4(ST0E_VIEW *wp)
{
    STCOM_SVECTOR pos;
    uint32 i;

    for (i = 0; i < 3; i++)
    {
        pos = wp->position;
        pos.x += (sint8)D_80110524[rand() & 7];
        pos.y += (sint8)D_80110524[rand() & 7];
        pos.z += (sint8)D_80110524[rand() & 7];
        func_8010D9F8(0, i + 7, 1, &pos);
        pos = wp->position;
        pos.x += (sint8)D_80110524[rand() & 7];
        pos.y += (sint8)D_80110524[rand() & 7];
        pos.z += (sint8)D_80110524[rand() & 7];
        func_8010D9F8(0, i + 7, 1, &pos);
    }
}

void func_80108C94(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}

void func_80108CB4(ST0E_10C *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    D_8011052C[wp->routine_0](wp);
}

void func_80108D30(ST0E_ITEM *wp)
{
    ST0E_ITEM_HIT *hit;

    wp->flags_0 |= 2;
    wp->code_88    = 0x3DC8000B;
    wp->rotation.x = 0;
    wp->scale_96   = 0xA0;
    wp->scale_97   = 0xC0;
    wp->rotation.y = 0;
    wp->rotation.z = 0;
    wp->u_44.w     = 0;
    wp->size_98    = 0x18;
    wp->color_8C   = 0x2C808080;
    wp->u_48.w     = 0;
    wp->routine_0++;
    hit          = &wp->hit;
    wp->value_64 = 0;
    wp->value_70 = 0;
    wp->value_74 = 0;
    if (wp->variant_3 != 0)
    {
        wp->routine_1 = 0;
    }
    else
    {
        wp->routine_1 = 1;
    }
    wp->u_44.h[0] = -0x28;
    wp->u_44.h[1] = -0x50;
    wp->u_48.h[0] = -0x28;
    wp->u_4C.h[1] = 0xC;
    wp->value_6E  = 1;
    wp->value_78  = 0;
    wp->x_90      = wp->position.x;
    wp->y_92      = wp->position.y;
    wp->z_94      = wp->position.z;
    hit->flags_8  = 0;
}

void func_80108E00(ST0E_ITEM *wp)
{
    ST0E_ITEM_HIT *hit;

    hit = &wp->hit;
    if (wp->hit.flags_8 == 0)
    {
        if (wp->routine_1 == 0)
        {
            wp->position.x += wp->u_44.h[0];
            wp->position.y += wp->u_44.h[1];
            wp->position.z += wp->u_48.h[0];
            wp->u_44.h[1] += wp->u_4C.h[1];
            wp->position_fixed.x = wp->position.x << 16;
            wp->position_fixed.y = wp->position.y << 16;
            wp->position_fixed.z = wp->position.z << 16;
            if (wp->position.y >= 0)
            {
                wp->position.y = -0x10;
                wp->routine_1++;
            }
        }
        wp->x_90   = wp->position.x;
        wp->y_92   = wp->position.y;
        wp->z_94   = wp->position.z;
        hit->pos_0 = wp->position;
        hit->pos_0.y -= 0x20;
        func_800341BC(hit, 0x20, 0, 0xA000, wp->value_1, &hit->flags_8, 0x04080000, 0, 0x80);
        hit->flags_8 = 0;
        return;
    }
    if (wp->flag_C == 1)
    {
        Sce_flag_on(0x52F);
    }
    else if (wp->flag_C == 2)
    {
        Sce_flag_on(0x52E);
    }
    else if (wp->flag_C == 3)
    {
        Sce_flag_on(0x530);
    }
    switch (wp->routine_2)
    {
        case 0:
            if (!Sce_flag_test(0x609))
            {
                Sce_flag_on(0x609);
                hit->msg_10   = 0xB;
                wp->routine_2 = 1;
            }
            else if (!Sce_flag_test(0x60A))
            {
                Sce_flag_on(0x60A);
                hit->msg_10   = 0xC;
                wp->routine_2 = 1;
            }
            else if (!Sce_flag_test(0x60B))
            {
                Sce_flag_on(0x60B);
                hit->msg_10   = 0xD;
                wp->routine_2 = 1;
            }
            break;
        case 1:
            MojiTaskKill();
            MojiTaskExec2(4, hit->msg_10);
            wp->routine_0++;
            break;
    }
}

void func_80109038(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}
