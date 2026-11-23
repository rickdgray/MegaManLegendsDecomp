#include "common.h"
#include "st09.h"

void func_801143B4(ST09_PART *wp)
{
    D_8011E2D8[wp->routine_0](wp);
    wp->ctl.hit_14 = 0;
}

void func_80114400(ST09_PART *wp)
{
    wp->ctl.parent_34 = func_80036294(wp->parent_C);
    if (!(wp->flags_E & 1))
    {
        wp->flags_0 |= 2;
    }
    *(uint32 *)&wp->rotation.x  = 0;
    *(uint32 *)&wp->rotation.z  = 0;
    wp->value_64                = 0;
    wp->value_70                = 0;
    wp->value_74                = 0;
    wp->model_88                = ((STAGE_OBJ *)wp->ctl.parent_34)->model_88;
    wp->pos_AC.pad              = wp->index_D;
    wp->ctl.flags_0             = 0x10;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    *(uint32 *)&wp->ctl.value_8 = 0;
    wp->ctl.hit_14              = 0;
    func_80036470(wp->ctl.track_24);
    wp->ctl.scale_38.x        = 0x1000;
    wp->ctl.scale_38.y        = 0x1000;
    wp->ctl.scale_38.z        = 0x1000;
    wp->life_6E               = 0x400;
    wp->data_78               = (uint8 *)D_8011E2F8;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->color_B4              = 0x808080;
    func_801144E8(wp);
}

void func_801144E8(ST09_PART *wp)
{
    ST09_PART_CTL *ctl;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    ctl                     = &wp->ctl;
    if (wp->flags_E & 0x20)
    {
        wp->flags_E &= ~0x20;
        wp->color_B4 = 0xFFFFFF;
    }
    else
    {
        wp->color_B4 = 0x808080;
    }
    ctl->random_2 = rand();
    if ((wp->flags_0 & 2) && (ctl->flags_0 & 0x10))
    {
        wp->position         = ctl->parent_34->joint_180[wp->index_D];
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->position_fixed.z = wp->position.z << 16;
        wp->pos_AC           = wp->position;
        wp->matrix_8C        = ctl->parent_34->joint_240[wp->index_D];
        wp->pos_AC.pad       = wp->index_D;
    }
    if (ctl->flags_0 & 2)
    {
        func_801157F0(wp);
    }
    D_8011E2E4[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (!(ctl->flags_0 & 0x10))
    {
        wp->pos_AC      = wp->position;
        wp->pos_AC.pad  = wp->index_D;
        D_8011E988[0].x = wp->rotation.z;
        D_8011E988[0].y = wp->rotation.x;
        D_8011E988[0].z = wp->rotation.y;
        RotMatrix(D_8011E988, &wp->matrix_8C.m);
        D_8011E990[0].x = 0x200;
        D_8011E990[0].y = 0x200;
        D_8011E990[0].z = 0x200;
        ScaleMatrix(&wp->matrix_8C.m, D_8011E990);
    }
    if (ctl->flags_0 & 0x40)
    {
        D_8011E988[0] = wp->position;
        D_8011E990[0] = wp->position_fixed;
        Obj_pos_set(wp, 0x1800, 0, 0);
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
        wp->position       = D_8011E988[0];
        wp->position_fixed = D_8011E990[0];
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        D_8011E988[0] = wp->position;
        D_8011E990[0] = wp->position_fixed;
        Obj_pos_set(wp, 0x1800, 0, 0);
        ctl->pos_C         = wp->position;
        wp->position       = D_8011E988[0];
        wp->position_fixed = D_8011E990[0];
        func_8003430C(&ctl->pos_C, 0x50, &wp->position, 0x40, 0x200, 0xA000, wp->index_1, &ctl->hit_14, ctl->value_8 | 0x9880000, 0x800000,
                      0);
    }
}

void func_801149F0(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}

void func_80114A10(void)
{
}

// wp_pos is set once (unlike fx) so sched1 places it between the two argument moves.
void func_80114A18(ST09_PART *wp)
{
    STCOM_PL_WORK *pl;
    ST09_PART_CTL *ctl;
    STCOM_SVECTOR *pl_pos;
    STCOM_SVECTOR *wp_pos;
    sint16 rot;
    STCOM_EFFECT *fx;
    sint32 timer;
    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2          = 1;
            D_8011E9A0             = pl->position;
            D_8011E9A8             = Player_work.position_fixed;
            rot                    = Player_work.rotation.y;
            wp->rotation.x         = 0;
            wp->rotation.z         = 0xC00;
            pl_pos                 = &pl->position;
            wp_pos                 = &wp->position;
            Player_work.rotation.y = Angle_xz_svector(pl_pos, wp_pos);
            // A one-pass block (likely a macro body) weights wp_pos's references so it takes s1.
            do
            {
                if (wp->flags_E & 0x40)
                {
                    Obj_pos_set(pl, 0, 0, 0x800);
                }
                else
                {
                    Obj_pos_set(pl, 0, 0, -0x800);
                }
                wp->rotation.y = Angle_xz_svector(wp_pos, pl_pos);
            } while (0);
            wp->velocity.x     = (pl->position.x - wp->position.x) / 32;
            wp->velocity.z     = (pl->position.z - wp->position.z) / 32;
            pl->position       = D_8011E9A0;
            pl->position_fixed = D_8011E9A8;
            pl->rotation.y     = rot;
            ctl->timer_4       = 0x15;
            ctl->value_8       = 0;
            ctl->flags_0       = (ctl->flags_0 & ~0x10) | 0x40;
            // fall through
        case 1:
            timer          = ctl->timer_4 - 1;
            ctl->timer_4   = timer;
            wp->velocity.y = (0x10 - timer) * 2;
            wp->position.x += wp->velocity.x;
            wp->position.y += wp->velocity.y;
            wp->position.z += wp->velocity.z;
            wp->position_fixed.x = wp->position.x << 16;
            wp->position_fixed.y = wp->position.y << 16;
            wp->position_fixed.z = wp->position.z << 16;
            if (!(Obj_map_push_out(wp) & 0x3F00) && !(ctl->hit_14 & 0x2000000))
            {
                break;
            }
            wp->routine_2 = 2;
            // fall through
        case 2:
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0   = 7;
                fx->kind_2    = 0x80;
                fx->variant_3 = 0;
                Obj_pos_set(wp, 0x1000, 0, 0);
                fx->sprite.position = wp->position;
            }
            wp->flags_0 &= ~2;
            wp->flags_E |= 1;
            ctl->flags_0 = (ctl->flags_0 | 1) & ~0x5E;
            break;
    }
}

void func_80114D5C(ST09_PART *wp)
{
    ST09_PART_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 timer;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2  = 1;
            wp->velocity.z = 0;
            wp->rotation.x = 0;
            wp->rotation.y = ctl->parent_34->rotation.y;
            wp->rotation.z = 0xC00;
            ctl->timer_4   = 0x20;
            ctl->value_8   = 0;
            ctl->flags_0   = (ctl->flags_0 & ~0x10) | 0x40;
            // fall through
        case 1:
            timer        = ctl->timer_4 - 1;
            ctl->timer_4 = timer;
            if ((sint16)timer >= 0)
            {
                wp->velocity.y = (0x20 - timer) * 2;
                wp->position.y += wp->velocity.y;
                wp->position_fixed.y = wp->position.y << 16;
                if (!(Obj_map_push_out(wp) & 0x3F00) && !(ctl->hit_14 & 0x2000000))
                {
                    break;
                }
            }
            wp->routine_2 = 2;
            // fall through
        case 2:
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 7;
                fx->kind_2          = 0x80;
                fx->variant_3       = 0;
                fx->sprite.position = wp->position;
            }
            wp->flags_0 &= ~2;
            wp->flags_E |= 1;
            ctl->flags_0 = (ctl->flags_0 | 1) & ~0x5E;
            break;
    }
}

void func_80114EE0(ST09_PART *wp)
{
    ST09_PART_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            ctl->timer_4    = 10;
            ctl->value_8    = 0;
            ctl->scale_38.x = 0x1000;
            ctl->scale_38.y = 0x1000;
            ctl->scale_38.z = 0x1000;
            // fall through
        case 1:
            if ((sint16)--ctl->timer_4 >= 0)
            {
                ctl->scale_38.y += 0x199;
                break;
            }
            wp->routine_2   = 2;
            ctl->timer_4    = 0x1E;
            ctl->scale_38.y = 0x2000;
            // fall through
        case 2:
            if ((sint16)--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            ctl->timer_4  = 0xF;
            // fall through
        case 3:
            if ((sint16)--ctl->timer_4 < 0)
            {
                ctl->scale_38.y = 0x1000;
                ctl->flags_0 |= 1;
            }
            else
            {
                ctl->scale_38.y -= 0x111;
            }
            break;
    }
    ScaleMatrix(&wp->matrix_8C.m, &ctl->scale_38);
}

void func_80115014(ST09_PART *wp)
{
    ST09_PART_CTL *ctl;
    STCOM_PL_WORK *pl;
    STAGE_FX *fx;
    STCOM_SVECTOR pos;
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR fixed;
    sint16 turn;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (ctl->hit_14 & 0x2000000)
    {
        ctl->value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2  = 1;
            wp->rotation.x = 0;
            wp->rotation.y = ctl->parent_34->rotation.y;
            wp->rotation.z = 0xC00;
            wp->flags_E |= 0x10;
            ctl->timer_4 = 10;
            ctl->count_6 = 0;
            ctl->flags_0 = (ctl->flags_0 & ~0x10) | 0x48;
            Sound_call2(0xC5, &wp->position);
            // fall through
        case 1:
            if ((sint16)--ctl->timer_4 < 0)
            {
                wp->routine_2  = 2;
                wp->velocity.x = 0x100;
                ctl->value_8   = 0x20;
                ctl->timer_4   = 0x14;
            }
            else
            {
                if (ctl->timer_4 & 1)
                {
                    Obj_pos_set(wp, 0x40, 0, 0);
                }
                else
                {
                    Obj_pos_set(wp, -0x40, 0, 0);
                }
                break;
            }
            // fall through
        case 2:
            if ((sint16)--ctl->timer_4 >= 0)
            {
                wp->velocity.x >>= 1;
                Obj_pos_set(wp, (wp->velocity.x + 8) << 4, 0xA0, 0);
                break;
            }
            wp->routine_2  = 3;
            wp->velocity.y = 0xC;
            wp->accel.y    = 4;
            wp->velocity.x = 0x30;
            wp->accel.x    = 0x10;
            ctl->timer_4   = 8;
            // fall through
        case 3:
            if ((sint16)ctl->timer_4 != 0)
            {
                wp->velocity.x += wp->accel.x;
                ctl->timer_4--;
            }
            Obj_pos_set(wp, wp->velocity.x << 4, 0, 0);
            if ((Obj_map_push_out(wp) & 0x3F00) || (ctl->hit_14 & 0x2000000))
            {
                if ((sint16)ctl->timer_4 == 0)
                {
                    wp->routine_2 = 5;
                    wp->flags_E |= 4;
                    func_800398E0(0xA);
                    Sound_call2(0xC6, &wp->position);
                }
            }
            if (func_80031E60(&pl->position_fixed, pl->rotation.y, 0x800, &wp->position_fixed, wp->rotation.y, 0x400))
            {
                wp->routine_2 = 4;
            }
            break;
        case 4:
            Obj_pos_set(wp, (wp->velocity.x + 8) << 4, 0, 0);
            hit = Obj_map_push_out(wp);
            wp->velocity.x >>= 1;
            if (hit & 0x3F00)
            {
                wp->routine_2 = 5;
                wp->flags_E |= 4;
                func_800398E0(0xA);
                Sound_call2(0xC6, &wp->position);
            }
            if (wp->velocity.x == 0)
            {
                wp->routine_2 = 5;
                wp->flags_E |= 4;
            }
            break;
        case 5:
            if (!(wp->flags_E & 8))
            {
                break;
            }
            turn           = Muku(&ctl->parent_34->joint_180[wp->index_D], &wp->position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn != 0)
            {
                break;
            }
            wp->routine_2        = 6;
            pos                  = wp->position;
            fixed                = wp->position_fixed;
            rot                  = wp->rotation;
            wp->rotation         = ctl->parent_34->rotation;
            wp->position         = ctl->parent_34->joint_180[wp->index_D];
            wp->position_fixed.x = wp->position.x << 16;
            wp->position_fixed.y = wp->position.y << 16;
            wp->position_fixed.z = wp->position.z << 16;
            Obj_pos_set(wp, 0x400, 0, 0);
            wp->velocity.x     = (wp->position.x - pos.x) / 32;
            wp->velocity.y     = (wp->position.y - pos.y) / 32;
            wp->velocity.z     = (wp->position.z - pos.z) / 32;
            wp->position       = pos;
            wp->position_fixed = fixed;
            wp->rotation       = rot;
            ctl->timer_4       = 0x20;
            // fall through
        case 6:
            if ((sint16)--ctl->timer_4 >= 0)
            {
                wp->position.x += wp->velocity.x;
                wp->position.y += wp->velocity.y;
                wp->position.z += wp->velocity.z;
                wp->position_fixed.x = wp->position.x << 16;
                wp->position_fixed.y = wp->position.y << 16;
                wp->position_fixed.z = wp->position.z << 16;
                break;
            }
            wp->routine_2  = 7;
            wp->velocity.x = (ctl->parent_34->joint_180[wp->index_D].x - wp->position.x) / 16;
            wp->velocity.y = (ctl->parent_34->joint_180[wp->index_D].y - wp->position.y) / 16;
            wp->velocity.z = (ctl->parent_34->joint_180[wp->index_D].z - wp->position.z) / 16;
            ctl->timer_4   = 0x10;
            // fall through
        case 7:
            if ((sint16)--ctl->timer_4 >= 0)
            {
                wp->position.x += wp->velocity.x;
                wp->position.y += wp->velocity.y;
                wp->position.z += wp->velocity.z;
                wp->position_fixed.x = wp->position.x << 16;
                wp->position_fixed.y = wp->position.y << 16;
                wp->position_fixed.z = wp->position.z << 16;
                break;
            }
            wp->routine_2 = 8;
            ctl->timer_4  = 4;
            Sound_call2(0xC7, &wp->position);
            // fall through
        case 8:
            if ((sint16)--ctl->timer_4 < 0)
            {
                ctl->flags_0 = (ctl->flags_0 | 0x11) & ~0x48;
                wp->flags_E  = (wp->flags_E | 2) & ~0x18;
            }
            else if (ctl->timer_4 & 1)
            {
                Obj_pos_set(wp, 0x40, 0, 0);
            }
            else
            {
                Obj_pos_set(wp, -0x40, 0, 0);
            }
            break;
    }
    if (wp->routine_2 < 5 && !(ctl->count_6++ & 1))
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            pos   = wp->position;
            fixed = wp->position_fixed;
            Obj_pos_set(wp, -0x300, 0, 0);
            fx->flags_0        = 9;
            fx->kind_2         = 0xF;
            fx->variant_3      = 0;
            fx->x_1C           = wp->position.x;
            fx->y_1E           = wp->position.y;
            fx->z_20           = wp->position.z;
            wp->position       = pos;
            wp->position_fixed = fixed;
        }
    }
}

sint32 func_801157F0(ST09_PART *wp)
{
    uint32 hit;
    uint32 damage;

    hit    = wp->ctl.hit_14;
    damage = hit & 0xFFFFFF;
    if (damage != 0)
    {
        if (hit & 0x38000000)
        {
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                Sound_call2(0xA2, &wp->position);
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->color_B4 = 0xFFFFFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_80115898(ST09_SLIDER *wp)
{
    D_8011E304[wp->routine_0](wp);
    wp->hit_BC = 0;
}

void func_801158E4(ST09_SLIDER *wp)
{
    STCOM_FIXED_VECTOR scale;
    uint8 variant;

    variant = 0;
    wp->flags_0 |= 6;
    wp->pos_AC     = wp->position;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->value_70   = 0;
    wp->value_74   = 0;
    Model_work_init(wp, &variant);
    wp->life_6E               = 0x400;
    wp->color_B4              = 0x808080;
    wp->routine_0             = 1;
    wp->ctl.value_0           = 0;
    wp->ctl.angle_C           = 0;
    wp->data_78               = NULL;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->hit_BC                = 0;
    wp->ctl.delay_4           = wp->param_C;
    wp->ctl.count_6           = wp->param_D;
    wp->ctl.wait_8            = wp->param_E;
    wp->ctl.speed_A           = wp->param_F;
    wp->ctl.rot_E             = wp->rotation.y;
    RotMatrix(&wp->rotation, &wp->matrix_8C.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    func_80115A0C(wp);
}

void func_80115A0C(ST09_SLIDER *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->color_B4            = 0x808080;
    wp->ctl.random_2        = rand();
    if (wp->hit_BC & 0x39000000)
    {
        Sound_call2(0xA3, &wp->position);
    }
    D_8011E310[wp->routine_1](wp);
    wp->pos_AC = wp->position;
    RotMatrix(&wp->rotation, &wp->matrix_8C.m);
    D_8011E9B8[0].x = 0x200;
    D_8011E9BC      = 0x200;
    D_8011E9C0      = 0x200;
    ScaleMatrix(&wp->matrix_8C.m, D_8011E9B8);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x50, 0x200, 0);
    }
    if (wp->flags_0 & 1)
    {
        func_800341BC(&wp->position, 0x50, 0, 0xE000, wp->index_1, &wp->hit_BC, ((wp->variant_3 & 0x7F) * 2) | 0x29000000, 0, 0x80);
    }
}

void func_80115BD0(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}

void func_80115BF0(ST09_SLIDER *wp)
{
    ST09_SLIDER_CTL *ctl;

    wp->rotation.y = wp->ctl.rot_E;
    ctl            = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            if (--wp->ctl.delay_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 1;
            // fall through
        case 1:
            if (wp->hit_BC & 0x4000000)
            {
                ctl->speed_A = -ctl->speed_A;
                ctl->count_6 = (wp->param_D - ctl->count_6 < 0) ? ctl->count_6 - wp->param_D : wp->param_D - ctl->count_6;
            }
            if (--ctl->count_6 >= 0)
            {
                Obj_pos_set(wp, ctl->speed_A * 16, 0, 0);
                break;
            }
            wp->routine_2 = 2;
            // fall through
        case 2:
            if (--ctl->wait_8 < 0)
            {
                wp->routine_2 = 1;
                ctl->count_6  = wp->param_D;
                ctl->wait_8   = wp->param_E;
                ctl->speed_A  = -ctl->speed_A;
            }
            break;
    }
    wp->rotation.y = ctl->angle_C;
    ctl->angle_C   = (ctl->angle_C + (wp->variant_3 & 0x7F) * 16) & 0xFFF;
}
