#include "common.h"
#include "st03.h"

void func_8010FA58(STAGE_SPARK *wp)
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

void func_8010FAE4(STAGE_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_8010FA58(wp);
}

void func_8010FB18(STAGE_OBJ *wp)
{
    func_80031988(wp);
}

void func_8010FB38(STAGE_OBJ *wp)
{
    D_801171D8[wp->routine_0](wp);
}

void func_8010FB74(ST03_SPARK *wp)
{
    ST03_SPARK *ep;
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
                func_8010FB38(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_8010FCBC(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 1)
    {
        func_8010FB38(wp);
        return;
    }
    if (wp->routine_0 != 2)
    {
        func_8010FB74(wp);
        return;
    }
    func_80031988((STCOM_EFFECT *)wp);
}

ST03_SPARK *func_8010FD1C(STAGE_XYZ *pos, sint32 width, sint32 growth, sint16 count, sint32 rise,
                          uint8 flag)
{
    ST03_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0;
        ep->variant_3 = 0;
        ep->value_C   = 0;
        ep->width_E   = width;
        ep->type_F    = growth;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->count_26  = count;
        if (flag)
        {
            ep->flags_6 |= 0x20;
        }
        else
        {
            ep->flags_6 &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < count; i++)
        {
            func_8010FB74(ep);
        }
    }
    return ep;
}

void func_8010FE24(ST03_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->color_B4            = 0x808080;
    wp->hit_BC.h[1]             = rand();
    D_801171E4[wp->routine_0](wp);
    RotMatrix(&wp->rotation, &wp->matrix_8C.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x80, 0x200, 0);
    }
    func_80051B68(wp, 1, -1, 0x1000008);
}

void func_8010FF4C(ST03_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;
    uint8 variant;

    variant = 0;
    wp->flags_0 |= 6;
    wp->position_AC = wp->position;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->speed_44.w  = 0;
    wp->value_48    = 0;
    func_8002F9C4(wp, &variant);
    wp->value_6E = 0x400;
    wp->hit_BC.h[0] = 0;
    wp->data_78  = NULL;
    switch (wp->variant_3)
    {
        case 0:
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            break;
        case 1:
            wp->routine_0             = 1;
            wp->routine_1             = 1;
            *(uint16 *)&wp->routine_2 = 0;
            break;
        case 2:
            wp->routine_0             = 1;
            wp->routine_1             = 1;
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
    wp->color_B4              = 0x808080;
    wp->hit_BC.w = 0;
    RotMatrix(&wp->rotation, &wp->matrix_8C.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    func_8011006C(wp);
}

void func_8011006C(ST03_PROP *wp)
{
    uint32 *hit;

    hit = &wp->hit_BC.w;
    D_801171F0[wp->routine_1](wp);
    wp->position_AC = wp->position;
    if (wp->hit_BC.h[0] & 2)
    {
        func_800341BC(&wp->position, 0x30, 0, 0x8000, wp->id_1, hit, 0x500000A, 0, 0x80);
    }
    wp->hit_BC.w = 0;
}

void func_80110128(STAGE_OBJ *wp)
{
    func_800318D8(wp);
}

void func_80110148(ST03_PROP *wp)
{
    uint16 *bob;

    bob = wp->hit_BC.h;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            bob[2]            = 0x40;
            wp->speed_44.h[1] = -0x40;
            wp->accel_4C.h[1] = 1;
            bob[3]            = 0;
            // fall through
        case 1:
            if (wp->speed_44.h[1] != 0)
            {
                wp->speed_44.h[1] += wp->accel_4C.h[1];
                wp->position_fixed.y += wp->speed_44.h[1] << 12;
                func_80030150(&wp->position_fixed, &wp->position);
                break;
            }
            wp->routine_2++;
            bob[2] = 0;
            // fall through
        case 2:
            if ((sint16)--bob[2] < 0)
            {
                bob[3]            = (bob[3] + 1) & 3;
                wp->accel_4C.h[1] = D_80117200[bob[3]];
                bob[2]            = 0x1F;
            }
            wp->speed_44.h[1] += wp->accel_4C.h[1];
            wp->position_fixed.y += wp->speed_44.h[1] << 12;
            func_80030150(&wp->position_fixed, &wp->position);
            break;
    }
}

void func_8011027C(void)
{
}

void func_80110284(ST03_PROP *wp)
{
    sint32 dx;
    sint32 dz;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->speed_44.h[0] = D_80117204[wp->path_D].target.pad;
            wp->target_CA.x   = D_80117204[wp->path_C].target.x;
            wp->target_CA.y   = D_80117204[wp->path_C].target.y;
            wp->target_CA.z   = D_80117204[wp->path_C].target.z;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &wp->target_CA, wp->rotation.y,
                                                             D_80117204[wp->path_C].turn_C)) &
                             0xFFF;
            func_8002FEA4(wp, wp->speed_44.h[0], 0, 0);
            dx = wp->position.x - wp->target_CA.x;
            dz = wp->position.z - wp->target_CA.z;
            if (dx * dx + dz * dz < D_80117204[wp->path_C].reach_8)
            {
                wp->routine_2++;
            }
            break;
        case 2: // arrived (an empty case keeps retail's compare tree)
            break;
    }
}

void func_801103F0(ST03_PROP *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->hit_BC.h[2]   = 0x82;
            wp->speed_44.h[1] = -0x10;
            wp->accel_4C.h[1] = -4;
            Sound_call(0x156, 0, 0);
            // fall through
        case 1:
            wp->speed_44.h[1] += wp->accel_4C.h[1];
            wp->position_fixed.y += wp->speed_44.h[1] << 12;
            func_80030150(&wp->position_fixed, &wp->position);
            if ((sint16)--wp->hit_BC.h[2] < 0)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}
