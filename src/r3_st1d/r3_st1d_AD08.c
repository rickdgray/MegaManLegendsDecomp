#include "common.h"
#include "st1d.h"

void func_8010AD08(ST1D_ARM *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_46         = rand();
    wp->rotation.y          = (Angle_xz_svector(&func_80036294(wp->parent_C)->position, &wp->position) + 0x800) & 0xFFF;
    D_80114D50[wp->routine_0](wp);
    wp->ctl.hit_18[0].hit = 0;
    wp->ctl.hit_18[1].hit = 0;
    wp->ctl.hit_18[2].hit = 0;
    wp->ctl.hit_18[3].hit = 0;
}

void func_8010ADCC(ST1D_ARM *wp)
{
    ST1D_ARM_OWNER *owner;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x10001000;
    wp->scale.words[1] = 0x1000;
    wp->routine_0      = 1;
    wp->anim_prev_AD   = 0;
    wp->anim_AC        = 0;
    func_80032304(wp, 0, 0);
    owner          = (ST1D_ARM_OWNER *)func_80036294(wp->owner_D);
    wp->matrix_160 = *ST1D_BONE_MATRIX(owner, wp->variant_3);
    Model_parts_mtx_set(wp,
                        (STCOM_MATRIX *)((uint8 *)owner + (wp->variant_3 * 32 + 0x208))); // offset first
    wp->scale.v.pad  = 0x4210;
    wp->value_78     = 0;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 << 6;
    wp->power_73                                     = D_80098844[wp->kind_2]->value_A;
    wp->flags_E |= 2;
}

void func_8010AF10(ST1D_ARM *wp)
{
    ST1D_ARM_CTL *ctl;
    ST1D_ARM_OWNER *parent;
    ST1D_ARM_OWNER *owner;
    sint16 damage;
    ctl    = &wp->ctl;
    parent = (ST1D_ARM_OWNER *)func_80036294(wp->parent_C);
    owner  = (ST1D_ARM_OWNER *)func_80036294(wp->owner_D);
    if (wp->routine_1 != 2)
    {
        if (ctl->value_42 != 0)
        {
            ctl->value_42--;
        }
        if (!(wp->flags_E & 2))
        {
            damage = ctl->hit_18[1].hit;
            if (damage != 0)
            {
                wp->life_prev_B2 = wp->life_6E;
                wp->life_6E -= damage;
                parent->life_prev_B2 = parent->life_6E;
                parent->life_6E -= damage;
                if (wp->variant_3 != 0)
                {
                    parent->timer_F = 2;
                }
                else
                {
                    parent->timer_F = 1;
                }
                if (wp->life_6E < 0)
                {
                    parent         = (ST1D_ARM_OWNER *)func_80036294(wp->parent_C);
                    wp->routine_1  = 2;
                    ctl->timer_48  = 0x3C;
                    wp->matrix_160 = *ST1D_BONE_MATRIX(owner, wp->variant_3);
                    if (wp->variant_3 == 0)
                    {
                        parent->arm_D = -1;
                        owner->arm_D  = -1;
                    }
                    else
                    {
                        parent->arm_E = -1;
                        owner->arm_E  = -1;
                    }
                }
                else
                {
                    ctl->value_42 += damage;
                    if (ctl->value_42 >= D_80098844[wp->kind_2]->limit_9)
                    {
                        ctl->value_42 = 0;
                        parent->flags_C |= 0x40;
                        Sound_call2(0xA2, &wp->position);
                    }
                    else
                    {
                        Sound_call2(0xA0, &wp->position);
                    }
                }
                wp->scale.v.pad = 0x7FFF;
            }
            else
            {
                if (ctl->hit_18[0].hit & 0xFFFFFF)
                {
                    Sound_call2(0xA3, &wp->position);
                }
                if (ctl->hit_18[2].hit & 0xFFFFFF)
                {
                    Sound_call2(0xA3, &wp->position);
                }
                if (ctl->hit_18[3].hit & 0xFFFFFF)
                {
                    Sound_call2(0xA3, &wp->position);
                }
            }
        }
        else if (parent->timer_F != 0)
        {
            wp->scale.v.pad = 0x7FFF;
            parent->timer_F--;
        }
        else
        {
            if (ctl->hit_18[1].hit & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
            if (ctl->hit_18[0].hit & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
            if (ctl->hit_18[2].hit & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
            if (ctl->hit_18[3].hit & 0xFFFFFF)
            {
                Sound_call2(0xA3, &wp->position);
            }
        }
        if (wp->routine_1 != 2)
        {
            if (!(wp->flags_E & 0x40))
            {
                wp->routine_1 = 0;
            }
            else
            {
                wp->routine_1 = 1;
            }
        }
    }
    D_80114D5C[wp->routine_1](wp);
    if (wp->routine_1 != 2)
    {
        func_80032538(wp);
        wp->matrix_160 = *ST1D_BONE_MATRIX(owner, wp->variant_3);
        Model_parts_mtx_set(wp, (STCOM_MATRIX *)((uint8 *)owner + (wp->variant_3 * 32 + 0x208)));
        if (parent->flags_C & 0x80)
        {
            func_80032538(wp);
            wp->matrix_160 = *ST1D_BONE_MATRIX(owner, wp->variant_3);
            Model_parts_mtx_set(wp, (STCOM_MATRIX *)((uint8 *)owner + (wp->variant_3 * 32 + 0x208)));
        }
        ctl->pos_10.x = wp->joints_180[0].x;
        ctl->pos_10.y = wp->joints_180[0].y + 0x28;
        ctl->pos_10.z = wp->joints_180[0].z;
        ctl->pos_0.x  = ctl->pos_10.x << 16;
        ctl->pos_0.y  = ctl->pos_10.y << 16;
        ctl->pos_0.z  = ctl->pos_10.z << 16;
        func_8002FFC4(&ctl->pos_10, &ctl->pos_0, wp->rotation.y & 0xFFF, -0x320, 0, 0);
        func_800341BC(&ctl->pos_10, 0xC8, 0, 0x8000, wp->value_1, &ctl->hit_18[0], wp->power_73 | 0x04080000, 0, 0x80);
        ctl->pos_10.x = wp->joints_180[7].x;
        ctl->pos_10.y = wp->joints_180[7].y + 0x78;
        ctl->pos_10.z = wp->joints_180[7].z;
        ctl->pos_0.x  = ctl->pos_10.x << 16;
        ctl->pos_0.y  = ctl->pos_10.y << 16;
        ctl->pos_0.z  = ctl->pos_10.z << 16;
        func_8002FFC4(&ctl->pos_10, &ctl->pos_0, wp->rotation.y & 0xFFF, -0xF00, 0, 0x820);
        func_800341BC(&ctl->pos_10, 0x46, 0, 0x8000, wp->value_1, &ctl->hit_18[2], wp->power_73 | 0x04080000, 0, 0x80);
        ctl->pos_10.x = wp->joints_180[7].x;
        ctl->pos_10.y = wp->joints_180[7].y + 0x78;
        ctl->pos_10.z = wp->joints_180[7].z;
        ctl->pos_0.x  = ctl->pos_10.x << 16;
        ctl->pos_0.y  = ctl->pos_10.y << 16;
        ctl->pos_0.z  = ctl->pos_10.z << 16;
        func_8002FFC4(&ctl->pos_10, &ctl->pos_0, wp->rotation.y & 0xFFF, -0xF00, 0, -0x820);
        func_800341BC(&ctl->pos_10, 0x46, 0, 0x8000, wp->value_1, &ctl->hit_18[3], wp->power_73 | 0x04080000, 0, 0x80);
        ctl->pos_10.x = wp->joints_180[7].x;
        ctl->pos_10.y = wp->joints_180[7].y + 0x78;
        ctl->pos_10.z = wp->joints_180[7].z;
        ctl->pos_0.x  = ctl->pos_10.x << 16;
        ctl->pos_0.y  = ctl->pos_10.y << 16;
        ctl->pos_0.z  = ctl->pos_10.z << 16;
        func_8002FFC4(&ctl->pos_10, &ctl->pos_0, wp->rotation.y & 0xFFF, -0xF00, 0, 0);
        func_800341BC(&ctl->pos_10, 0x46, 0, 0x8000, wp->value_1, &ctl->hit_18[1], wp->power_73 | 0x04080000, 0, 0);
    }
    else
    {
        func_80032538(wp);
        Model_parts_mtx_set(wp, &wp->matrix_160);
    }
}

void func_8010B5B4(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010B5D4(ST1D_ARM *wp)
{
    if (!(((ST1D_ARM_OWNER *)func_80036294(wp->parent_C))->flags_C & 1))
    {
        ST1D_ARM_ANIM(wp, 1);
    }
    else if (wp->flags_E & 4)
    {
        ST1D_ARM_ANIM(wp, 0);
    }
    else if (wp->flags_E & 8)
    {
        ST1D_ARM_ANIM(wp, 3);
    }
    else if (wp->flags_E & 0x10)
    {
        ST1D_ARM_ANIM(wp, 4);
    }
    else if (wp->flags_E & 0x20)
    {
        ST1D_ARM_ANIM(wp, 5);
    }
}

void func_8010B6BC(STAGE_OBJ *wp)
{
    D_80114D68[wp->routine_2](wp);
}

void func_8010B6F8(STAGE_OBJ *wp)
{
    if (!((uint8)wp->u_E.b.byte_E & 4))
    {
        wp->anim_AC      = 5;
        wp->anim_prev_AD = 5;
        func_80032304(wp, (sint32)wp->anim_AC, 0);
        wp->routine_2++;
        return;
    }
    wp->routine_1 = 0;
}

void func_8010B75C(STAGE_OBJ *wp)
{
    if (wp->value_A7 == -1)
    {
        wp->routine_2 = 0;
        wp->routine_1 = 0;
    }
}

void func_8010B77C(ST1D_VIEW *wp)
{
    ST1D_SPARK2 *spark;
    STCOM_EFFECT *fx;
    uint8 joint;

    spark = (ST1D_SPARK2 *)&wp->reserved1E6[0x308 - 0x1E6];
    if (spark->timer_48 != 0)
    {
        if (!(spark->timer_48 & 3))
        {
            joint            = D_80114D70[spark->value_46 & 7].joint_0;
            spark->offset_38 = D_80114D70[(sint8)(spark->value_46 & 7)].offset_2; // indexed again, not reused
            fx               = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0           = 5;
                fx->kind_2            = 0x80;
                fx->variant_3         = 0x40;
                fx->value_D           = spark->value_46 & 3;
                fx->sprite.position.x = wp->vec_180[joint].x + spark->offset_38.x;
                fx->sprite.position.y = wp->vec_180[joint].y + spark->offset_38.y;
                fx->sprite.position.z = wp->vec_180[joint].z + spark->offset_38.z;
            }
        }
    }
    else
    {
        wp->routine_0 = 2;
    }
    spark->timer_48--;
}

void func_8010B8D0(ST1D_VIEW *wp)
{
    wp->position_prev           = wp->position;
    wp->position_fixed_prev.x   = wp->position_fixed.x;
    wp->position_fixed_prev.y   = wp->position_fixed.y;
    wp->position_fixed_prev.z   = wp->position_fixed.z;
    wp->position_fixed_prev.pad = wp->position_fixed.pad;
    wp->rotation_prev           = wp->rotation;
    wp->u_15C.h[1]              = 0x4210;
    wp->ext.value_8A            = rand();
    D_80114DC0[wp->routine_0](wp);
    wp->ext.u_24.w[1] = 0;
}

void func_8010B988(ST1D_VIEW *wp)
{
    ST1D_CTL *ctl;
    STCOM16_STUN *stun;

    ctl            = ST1D_CTL_OF(wp);
    stun           = (STCOM16_STUN *)&wp->value_1D8;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    wp->value_F = wp->variant_3 & 0xF;
    Model_work_init(wp, &wp->value_F);
    wp->value_158  = 0x02000200;
    wp->u_15C.w[0] = 0x200;
    ctl->hit_8     = 0;
    ctl->value_C   = 0;
    if (!(wp->variant_3 & 0xF0))
    {
        ctl->flags_6C = 0x28;
    }
    else
    {
        ctl->flags_6C = 8;
    }
    ctl->value_66  = 0;
    stun->damage_0 = 0;
    wp->u_70.b[3]  = D_80098844[wp->kind_2]->value_A;
    Track_reset(ctl->track_18, 7, -0x60);
    wp->value_B2 = wp->value_B0 = wp->value_6E = D_80098844[wp->kind_2]->life_8 << 5;
    wp->routine_1                              = 0;
    wp->routine_0                              = 1;
    wp->u_74.b[0]                              = 0;
    wp->u_15C.h[1]                             = 0x4210;
    wp->value_AC                               = 0;
    wp->data_78                                = D_80114E20;
    wp->u_44.h[0]                              = 0x140;
    wp->value_AD                               = 0;
    func_800322A8(wp, wp->value_AC, 0);
    ctl->ground_60 = Obj_map_push_out(wp);
    ctl->angle_64  = (wp->rotation.y + 0x800) & 0xFFF;
}

void func_8010BAEC(ST1D_VIEW *wp)
{
    ST1D_CTL *ctl;
    STCOM16_STUN *stun;
    sint32 damage;

    ctl  = ST1D_CTL_OF(wp);
    stun = (STCOM16_STUN *)&wp->value_1D8;
    if (func_8003648C(ctl->track_18, wp) == 0)
    {
        ctl->flags_6C &= ~0x10;
    }
    else
    {
        ctl->flags_6C |= 0x10;
    }
    if (ctl->value_66 != 0)
    {
        ctl->value_66--;
    }
    damage = ctl->hit_8 & 0xFFFFFF;
    if (damage != 0)
    {
        wp->value_B2 = wp->value_6E;
        wp->value_6E -= damage;
        if (wp->value_6E <= 0)
        {
            ctl->flags_6C &= ~8;
            wp->value_AC  = 9;
            wp->routine_1 = 5;
            wp->value_AD  = 9;
            func_800322A8(wp, wp->value_AC, 0);
            stun->damage_0 = 0;
            stun->timer_5  = 0;
        }
        else
        {
            ctl->value_66 += damage;
            if (!(ctl->flags_6C & 4) && ctl->value_66 >= D_80098844[wp->kind_2]->limit_9 * 16)
            {
                ctl->flags_6C |= 4;
                ctl->value_66 = 0;
                wp->value_AC  = 9;
                wp->routine_1 = 4;
                wp->routine_2 = 0;
                wp->value_AD  = 9;
                func_800322A8(wp, wp->value_AC, 0);
                Sound_call2(0xA2, &wp->position);
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
                if (wp->routine_1 != 2 && wp->routine_1 != 4)
                {
                    wp->routine_1 = 3;
                    if (wp->value_AC == 0)
                    {
                        wp->value_AC = 1;
                        wp->value_AD = 1;
                        func_800322A8(wp, wp->value_AC, 0);
                    }
                }
            }
            wp->u_15C.h[1] = 0x7FFF;
        }
    }
    if ((ctl->flags_6C & 8) && wp->routine_1 != 2 && ((ctl->ground_60 & 0xF00) || wp->routine_1 == 1))
    {
        wp->routine_1 = 1;
    }
    D_80114DCC[wp->routine_1](wp);
    func_80032488(wp);
    if (wp->value_A6 & 0x40)
    {
        Sound_call2(0x1BD, &wp->position);
    }
    ctl->ground_60       = Obj_map_push_out(wp);
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    if ((ctl->flags_6C & 8) && wp->routine_1 != 1 && (ctl->ground_60 & 0xF00))
    {
        ctl->angle_64 = (wp->rotation.y + 0x800) & 0xFFF;
        if (wp->rotation.y - wp->rotation_prev.y > 0)
        {
            wp->value_C = 0;
        }
        else
        {
            wp->value_C = 1;
        }
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0xA0, 0x200, 0);
    }
    if (ctl->flags_6C & 8)
    {
        ctl->pos_0.x = wp->vec_180[0].x;
        ctl->pos_0.y = wp->vec_180[0].y - 0x2E;
        ctl->pos_0.z = wp->vec_180[0].z;
        func_800341BC(&ctl->pos_0, 0xE0, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->u_70.b[3] | 0x04080000, 0, 0);
    }
}

void func_8010BE74(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010BE94(ST1D_VIEW *wp)
{
    ST1D_CTL *ctl;
    STCOM16_STUN *stun;
    uint32 n;

    ctl  = ST1D_CTL_OF(wp);
    stun = (STCOM16_STUN *)&wp->value_1D8;
    if (ctl->flags_6C & 0x20)
    {
        if (wp->value_1D8 == 0)
        {
            n = ctl->rand_6A & 0xF;
            if (n < 4)
            {
                wp->routine_2 = 1;
            }
            else if (n < 7)
            {
                wp->routine_2 = 2;
            }
            else if (n < 10)
            {
                wp->routine_2 = 3;
            }
            else
            {
                wp->routine_2 = 0;
                wp->value_AC  = 0;
                func_800322A8(wp, 0, 0);
            }
            stun->damage_0 = 0x78;
        }
        else
        {
            wp->value_1D8--;
        }
        if (wp->routine_2 != 0)
        {
            if (wp->value_AC != 1)
            {
                wp->value_AC = 1;
                func_800322A8(wp, 1, 0);
                wp->value_AD = wp->value_AC;
            }
            if (wp->routine_2 == 1)
            {
                wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
            }
            else if (wp->routine_2 == 2)
            {
                wp->rotation.y = (wp->rotation.y - 0x20) & 0xFFF;
            }
            Obj_pos_set(wp, wp->u_44.h[0], 0, 0);
        }
    }
    if (ctl->flags_6C & 0x10)
    {
        ctl->flags_6C |= 0x20;
        wp->routine_1  = 2;
        wp->routine_3  = 0;
        stun->damage_0 = 0;
    }
}

void func_8010C024(ST1D_VIEW *wp)
{
    if (wp->rotation.y == wp->ext.value_84)
    {
        wp->routine_1 = 0;
        wp->value_1D8 = 0;
    }
    else if (wp->value_C != 0)
    {
        wp->rotation.y = (wp->rotation.y - 0x20) & 0xFFF;
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
    }
}

void func_8010C070(ST1D_VIEW *wp)
{
    ST1D_SHOT *shot;
    shot = (ST1D_SHOT *)&wp->value_1D8;
    if ((wp->ext.value_8C & 0x10) || wp->routine_3 != 0)
    {
        if (wp->routine_3 < 2)
        {
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &STAGE_PL.position, wp->rotation.y & 0xFFF, 0x20)) & 0xFFF;
        }
        if (wp->routine_3 == 0)
        {
            Obj_pos_set(wp, wp->u_44.h[0], 0, 0);
        }
        if (wp->value_1D8 == 0)
        {
            D_80114DE4[wp->variant_3 & 0xF](wp);
            if (wp->routine_3 == 1)
            {
                if (wp->value_A6 & 1)
                {
                    wp->value_E = 1;
                }
                if (wp->value_E == 1)
                {
                    if (wp->value_A6 != 4)
                    {
                        if (wp->value_1DC == 0)
                        {
                            func_8010C9AC(wp, 0);
                            wp->value_1DC = 4 - (wp->variant_3 & 0xF);
                        }
                        else
                        {
                            wp->value_1DC--;
                        }
                    }
                    else
                    {
                        wp->value_E = 2;
                    }
                }
                else if (wp->value_A7 == -1)
                {
                    wp->value_AC = 1;
                    wp->value_AD = 1;
                    func_800322A8(wp, wp->value_AC, 0);
                    wp->value_1D8 = 0x2D;
                    wp->routine_3 = 0;
                }
            }
            if (wp->routine_3 == 2)
            {
                if (wp->value_E == 0)
                {
                    if (wp->value_A7 == -1)
                    {
                        wp->value_AC = 4;
                        wp->value_AD = 4;
                        func_800322A8(wp, wp->value_AC, 0);
                        wp->value_E   = 1;
                        shot->count_2 = 0x18;
                    }
                }
                else if (wp->value_E == 1)
                {
                    if (shot->count_2 != 0)
                    {
                        if (shot->delay_4 == 0)
                        {
                            func_8010C9AC(wp, 1);
                            shot->delay_4 = 3;
                        }
                        else
                        {
                            shot->delay_4--;
                        }
                        shot->count_2--;
                    }
                    else
                    {
                        wp->value_AC = 5;
                        wp->value_AD = 5;
                        func_800322A8(wp, wp->value_AC, 0);
                        wp->value_E = 2;
                    }
                }
                else if (wp->value_A7 == -1)
                {
                    wp->value_AC = 1;
                    wp->value_AD = 1;
                    func_800322A8(wp, wp->value_AC, 0);
                    shot->timer_0 = 0x2D;
                    wp->routine_3 = 0;
                }
            }
            if (wp->routine_3 == 3)
            {
                if (wp->value_A6 & 8)
                {
                    Sound_call2(0x1BF, &wp->position);
                }
                else if (wp->value_A6 & 0x10)
                {
                    Sound_call2(0x1C0, &wp->position);
                }
                else if (wp->value_A6 & 0x20)
                {
                    Sound_call2(0x1C1, &wp->position);
                }
                if (wp->value_E == 0)
                {
                    if (wp->value_A7 == -1)
                    {
                        wp->value_AC = 7;
                        wp->value_AD = 7;
                        func_800322A8(wp, wp->value_AC, 0);
                        wp->value_E   = 1;
                        shot->count_2 = ((wp->variant_3 & 0xF) + 4) * 4 + 1;
                        shot->index_6 = 0;
                    }
                }
                else if (wp->value_E == 1)
                {
                    if (shot->count_2 != 0)
                    {
                        if (shot->count_2 != 1)
                        {
                            if (shot->delay_4 == 0)
                            {
                                Sound_call2(0x1C2, &wp->position);
                                func_8010C9AC(wp, 2);
                                shot->count_2--;
                                shot->index_6++;
                                func_8010C9AC(wp, 2);
                                shot->count_2--;
                                shot->index_6++;
                                func_8010C9AC(wp, 2);
                                shot->count_2--;
                                shot->index_6++;
                                func_8010C9AC(wp, 2);
                                shot->delay_4 = 0x1E;
                                shot->index_6++;
                                shot->count_2--;
                                if (shot->index_6 >= 0x10)
                                {
                                    shot->index_6 = 0;
                                }
                            }
                            else
                            {
                                shot->delay_4--;
                            }
                        }
                        else if (shot->delay_4 == 0)
                        {
                            shot->count_2--;
                        }
                        else
                        {
                            shot->delay_4--;
                        }
                    }
                    else
                    {
                        wp->value_AC = 8;
                        wp->value_AD = 8;
                        func_800322A8(wp, wp->value_AC, 0);
                        wp->value_E = 2;
                    }
                }
                else if (wp->value_A7 == -1)
                {
                    wp->value_AC = 1;
                    wp->value_AD = 1;
                    func_800322A8(wp, wp->value_AC, 0);
                    shot->timer_0 = 0x2D;
                    wp->routine_3 = 0;
                }
            }
        }
        else
        {
            wp->value_1D8--;
        }
    }
    else
    {
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->value_1D8 = 0;
    }
}

void func_8010C55C(ST1D_VIEW *wp)
{
    uint32 n;

    if (wp->routine_3 == 0)
    {
        wp->value_1DC = 0;
        wp->value_E   = 0;
        n             = wp->ext.value_8A & 7;
        if (n == 0)
        {
            wp->value_AC  = 2;
            wp->routine_3 = 1;
            wp->value_AD  = 2;
            func_800322A8(wp, wp->value_AC, 0);
        }
        else if (n < 5)
        {
            wp->value_AC  = 3;
            wp->routine_3 = 2;
            wp->value_AD  = 3;
            func_800322A8(wp, wp->value_AC, 0);
        }
        else
        {
            wp->value_AC  = 6;
            wp->routine_3 = 3;
            wp->value_AD  = 6;
            func_800322A8(wp, wp->value_AC, 0);
        }
    }
}

void func_8010C5EC(ST1D_VIEW *wp)
{
    uint32 n;

    if (wp->routine_3 == 0)
    {
        wp->value_1DC = 0;
        wp->value_E   = 0;
        n             = wp->ext.value_8A;
        if ((n & 0xF) < 5)
        {
            wp->value_AC  = 2;
            wp->routine_3 = 1;
            wp->value_AD  = 2;
            func_800322A8(wp, wp->value_AC, 0);
        }
        else if ((n & 7) < 0xA)
        {
            wp->value_AC  = 3;
            wp->routine_3 = 2;
            wp->value_AD  = 3;
            func_800322A8(wp, wp->value_AC, 0);
        }
        else
        {
            wp->value_AC  = 6;
            wp->routine_3 = 3;
            wp->value_AD  = 6;
            func_800322A8(wp, wp->value_AC, 0);
        }
    }
}

void func_8010C684(ST1D_VIEW *wp)
{
    uint32 n;

    if (wp->routine_3 == 0)
    {
        wp->value_1DC = 0;
        wp->value_E   = 0;
        n             = wp->ext.value_8A & 7;
        if (n < 4)
        {
            wp->value_AC  = 2;
            wp->routine_3 = 1;
            wp->value_AD  = 2;
            func_800322A8(wp, wp->value_AC, 0);
        }
        else if (n < 6)
        {
            wp->value_AC  = 3;
            wp->routine_3 = 2;
            wp->value_AD  = 3;
            func_800322A8(wp, wp->value_AC, 0);
        }
        else
        {
            wp->value_AC  = 6;
            wp->routine_3 = 3;
            wp->value_AD  = 6;
            func_800322A8(wp, wp->value_AC, 0);
        }
    }
}

void func_8010C718(ST1D_VIEW *wp)
{
    sint32 turn;

    turn           = Muku(&wp->position, &STAGE_PL.position, wp->rotation.y & 0xFFF, 0x20);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (wp->ext.value_8C & 0x10)
    {
        wp->routine_1 = 2;
        wp->routine_3 = 0;
        wp->value_1D8 = 0;
        wp->ext.value_8C |= 0x20;
    }
    else if ((sint16)turn == 0)
    {
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->value_1D8 = 0;
    }
}

void func_8010C7B0(ST1D_VIEW *wp)
{
    if ((wp->value_A7 == -1) || (wp->routine_2 == 1))
    {
        wp->routine_2 = 1;
        wp->ext.value_8C &= 0xFB;
        if (wp->value_AD != 1)
        {
            wp->value_AC = 1;
            wp->value_AD = 1;
            func_800322A8(wp, wp->value_AC, 0);
        }
        wp->routine_1 = 2;
        wp->routine_3 = 0;
        wp->value_1D8 = 0;
        wp->ext.value_8C |= 0x20;
    }
}

void func_8010C84C(ST1D_VIEW *wp)
{
    STCOM16_STUN *stun;
    STCOM_EFFECT *fx;
    uint8 joint;

    stun = (STCOM16_STUN *)&wp->value_1D8;
    if (wp->value_1D8 == 0)
    {
        if (wp->value_1DD == 8)
        {
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0           = 5;
                fx->kind_2            = 0x80;
                fx->variant_3         = 0x40;
                fx->value_D           = 3;
                fx->sprite.position.x = wp->vec_180[0].x;
                fx->sprite.position.y = wp->vec_180[0].y;
                fx->sprite.position.z = wp->vec_180[0].z;
            }
            func_80047148_2(wp, wp->vec_180);
            wp->routine_0 = 2;
        }
        else
        {
            joint = D_80114DF0[wp->value_1DD].joint_0;
            fx    = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0           = 5;
                fx->kind_2            = 0x80;
                fx->variant_3         = 0x40;
                fx->value_D           = D_80114DF0[wp->value_1DD].look_1;
                fx->sprite.position.x = wp->vec_180[joint].x;
                fx->sprite.position.y = wp->vec_180[joint].y;
                fx->sprite.position.z = wp->vec_180[joint].z;
            }
        }
        stun->damage_0 = 4;
        stun->timer_5++;
    }
    else
    {
        wp->value_1D8--;
    }
}

// Fires a shot (kind 0: aimed with a spread, 1: straight back, 2: one of 16 directions).
void func_8010C9AC(ST1D_VIEW *wp, uint8 kind)
{
    ST1D_CTL *ctl;
    ST1D_SHOT *shot;
    STAGE_PL_VIEW *pl;
    ST1D_SHOT_OBJ *obj;
    sint32 dist;
    sint16 spread;
    sint32 c;
    sint32 s;
    sint32 offset;
    spread = 0;
    dist   = SquareRoot0(wp->value_80);
    ctl    = ST1D_CTL_OF(wp);
    pl     = &STAGE_PL;
    obj    = (ST1D_SHOT_OBJ *)Open_SHL_WORK();
    shot   = (ST1D_SHOT *)&wp->value_1D8;
    if (obj != NULL)
    {
        obj->flags_0 = 3;
        obj->kind_2  = 1;
        obj->value_4 = 0;
        if (!(kind & 2))
        {
            Sound_call2(0x1BE, &wp->position);
            obj->type_F = 0x10;
        }
        else
        {
            obj->type_F = 9;
        }
        if (kind == 0)
        {
            switch (wp->variant_3 & 0xF)
            {
                case 0:
                    spread = (ctl->rand_6A & 0x3F) - 0x20;
                    break;
                case 1:
                    spread = (ctl->rand_6A & 0x7F) - 0x40;
                    break;
                case 2:
                    spread = (ctl->rand_6A & 0x3FF) - 0x200;
                    break;
            }
            offset = spread + 0x800;
            c      = rcos(wp->rotation.y + offset);
            s      = rsin(wp->rotation.y + offset);
        }
        else if (kind == 1)
        {
            c = rcos(wp->rotation.y + 0x800);
            s = rsin(wp->rotation.y + 0x800);
        }
        else
        {
            c = rcos(wp->rotation.y + D_80114E00[shot->index_6]);
            s = rsin(wp->rotation.y + D_80114E00[shot->index_6]);
        }
        if (obj->type_F == 0x10)
        {
            obj->position.x       = wp->vec_180[0].x;
            obj->position.y       = wp->vec_180[0].y;
            obj->position.z       = wp->vec_180[0].z;
            obj->position_fixed.x = obj->position.x << 16;
            obj->position_fixed.y = obj->position.y << 16;
            obj->position_fixed.z = obj->position.z << 16;
            func_8002FFC4(&obj->position, &obj->position_fixed, wp->rotation.y & 0xFFF, 0x550, 0, 0);
            pl->value_C4.x = obj->position.x + (s * dist >> 12);
            if (kind == 0)
            {
                pl->value_C4.y = pl->value_3AA + ((ctl->rand_6A & 0x3F) - 0x20);
            }
            else
            {
                pl->value_C4.y = pl->value_3EA + 0x30;
            }
            pl->value_C4.z = obj->position.z + (c * dist >> 12);
            func_80030EE8(obj, &pl->value_C4, 0x30);
        }
        else
        {
            obj->position.x       = wp->vec_180[1].x;
            obj->position.y       = wp->vec_180[1].y;
            obj->position.z       = wp->vec_180[1].z;
            obj->position_fixed.x = obj->position.x << 16;
            obj->position_fixed.y = obj->position.y << 16;
            obj->position_fixed.z = obj->position.z << 16;
            func_8002FFC4(&obj->position, &obj->position_fixed, wp->rotation.y & 0xFFF, 0x550, 0, 0);
            pl->value_C4.x = obj->position.x + (s * ((ctl->rand_6A & 0x3FF) + 0x80) >> 12);
            pl->value_C4.y = obj->position.y;
            pl->value_C4.z = obj->position.z + (c * ((ctl->rand_6A & 0x3FF) + 0x80) >> 12);
            Obj_launch_set(obj, pl, 0x14, 0, 0xFF);
        }
    }
}

void func_8010CD64(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->scale.v.pad         = 0x4210;
    D_80114E2C[wp->routine_0](wp);
}

void func_8010CDE4(ST1D_VIEW *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *owner;
    sint8 i;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158  = 0x02000200;
    wp->u_15C.w[0] = 0x200;
    wp->u_15C.h[1] = 0x4210;
    wp->data_78    = NULL;
    wp->value_AC   = 0;
    func_800322A8(wp, 0, 0);
    for (i = 0; i < 2; i++)
    {
        child = func_80031418();
        if (child != NULL)
        {
            if (i == 0)
            {
                wp->value_D = child->value_1;
            }
            else
            {
                wp->value_E = child->value_1;
            }
            child->flags_0            = 1;
            child->kind_2             = 0x48;
            child->variant_3          = i;
            child->value_4            = 0;
            child->reserved05         = 0;
            child->rotation.y         = wp->rotation.y;
            child->u_C.b.byte_C       = wp->value_C;
            child->u_C.b.byte_D       = wp->value_1;
            child->u_E.b.byte_E       = 0;
            child->u_E.b.byte_F       = 0;
            child->position           = wp->vec_180[i + 1];
            child->position_fixed.v.x = child->position.x << 16;
            child->position_fixed.v.y = child->position.y << 16;
            child->position_fixed.v.z = child->position.z << 16;
        }
    }
    owner               = func_80036294(wp->value_C);
    owner->u_C.b.byte_D = wp->value_D;
    owner->u_E.b.byte_E = wp->value_E;
    wp->routine_0       = 1;
}

void func_8010CF78(ST1D_VIEW *wp)
{
    STAGE_OBJ *owner;
    STAGE_OBJ *part[2];

    owner = func_80036294(wp->value_C);
    if (owner->life_6E >= 0)
    {
        if (!(owner->u_C.b.byte_C & 1))
        {
            func_80032488(wp);
        }
        if (wp->value_D > 0)
        {
            part[0] = func_80036294(wp->value_D);
            if (part[0]->life_6E >= 0)
            {
                part[0]->position = wp->vec_180[1];
            }
        }
        if (wp->value_E > 0)
        {
            part[1] = func_80036294(wp->value_E);
            if (part[1]->life_6E >= 0)
            {
                part[1]->position = wp->vec_180[2];
            }
        }
    }
    else
    {
        wp->routine_0 = 2;
    }
}

void func_8010D084(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010D0A4(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_FADE *fade;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    ctl                     = &wp->ctl;
    wp->stun.rand_2         = rand();
    fade                    = &wp->fade;
    if (wp->variant_3 == 2 && wp->routine_0 != 0)
    {
        wp->flags_0 |= 2;
    }
    D_80114E44[wp->routine_0](wp);
    if (wp->variant_3 == 2)
    {
        if (wp->routine_0 != 0)
        {
            if (fade->on_3 != 0 && fade->r_0 == 0)
            {
                Sound_call2(0x190, &wp->position);
                fade->on_3 = 0;
            }
            if (fade->on_3 == 0 && fade->r_0 > 0)
            {
                Sound_call2(0x191, &wp->position);
                fade->on_3 = 1;
            }
            if ((wp->scale.v.pad & 0x8000) && fade->b_2 == 0)
            {
                wp->flags_0 &= ~2;
            }
        }
    }
    if (wp->variant_3 == 2 && (ctl->hit_8 & 0xFFFFFF))
    {
        wp->scale.v.pad = 0x7FFF;
    }
    ctl->hit_8 = 0;
}

void func_8010D27C(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    func_8003354C(wp);
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->kind_2     = 0x37;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->kind_2              = 0x67;
    wp->scale.words[0]      = 0x1800180;
    wp->scale.words[1]      = 0x180;
    wp->data_78             = D_80114E38;
    *(uint32 *)&wp->fade    = 0;
    *(uint32 *)wp->value_70 = 0;
    *(uint32 *)&wp->jump_74 = 0;
    wp->ctl.timer_3E        = 0;
    wp->power_73            = D_80098844[wp->kind_2]->value_A;
    wp->ground.value_4      = D_80098844[wp->kind_2]->value_B;
    wp->stun.hits_4         = 0;
    wp->stun.damage_0       = 0;
    wp->stun.timer_5        = 30;
    wp->fade.on_3           = 0;
    wp->ground.flags_6      = 0;
    Track_reset(wp->ctl.track_20, 5, -0x60);
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 << 4;
    ctl                                              = &wp->ctl;
    wp->routine_0                                    = 1;
    if (wp->variant_3 == 0)
    {
        wp->velocity.v.x = 0x80;
        wp->routine_1    = 0;
        wp->routine_2    = 0;
        wp->param_F      = 0;
        wp->anim_AC      = 1;
        wp->ctl.timer_3D = 120;
        wp->ctl.count_3C = 0;
    }
    else
    {
        wp->routine_0    = 3;
        wp->velocity.v.x = 0x2D0;
        wp->anim_AC      = 0;
        wp->ctl.timer_3D = 120;
        wp->ctl.count_3C = 0;
    }
    wp->scale.v.pad = 0x4210;
    wp->accel.y     = 0x60;
    func_800322A8(wp, wp->anim_AC, 0);
    ctl->hit_8 = 0;
    func_8010D424(wp);
}

void func_8010D424(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_GROUND *ground;
    STCOM16_STUN *stun;
    STCOM16_FADE *fade;
    STCOM_PL_WORK *pl;
    uint32 damage;
    sint32 dir;
    STCOM_SVECTOR claw;
    STCOM_FIXED_VECTOR ofs;
    ctl    = &wp->ctl;
    ground = &wp->ground;
    stun   = &wp->stun;
    fade   = &wp->fade;
    pl     = &Player_work;
    wp->ground.flags_6 &= ~8;
    if (func_8003648C(wp->ctl.track_20, wp))
    {
        wp->ground.flags_6 |= 8;
    }
    if (wp->stun.timer_5 != 0)
    {
        wp->stun.timer_5--;
    }
    if (wp->stun.damage_0 != 0)
    {
        wp->stun.damage_0--;
    }
    damage = wp->ctl.hit_8 & 0xFFFFFF;
    if (damage != 0)
    {
        if (wp->routine_1 == 1)
        {
            wp->stun.hits_4++;
        }
        wp->life_prev_B2 = wp->life_6E;
        wp->life_6E -= damage;
        wp->stun.damage_0 += damage;
        if (wp->life_6E <= 0)
        {
            wp->routine_1 = 7;
            wp->ground.flags_6 &= ~2;
        }
        else
        {
            wp->scale.v.pad = 0x7FFF;
            if ((!(wp->ground.flags_6 & 0x10) && wp->stun.damage_0 >= D_80098844[wp->kind_2]->limit_9) || (wp->ctl.hit_8 & 0x20000000))
            {
                if (wp->routine_1 != 5)
                {
                    Sound_call2(0xA2, &wp->position);
                    ground->flags_6  = (ground->flags_6 | 0x10) & ~0x20;
                    stun->damage_0   = 0;
                    stun->hits_4     = 0;
                    stun->timer_5    = 30;
                    wp->routine_1    = 6;
                    dir              = func_80031F84(&wp->position, &ctl->target_10, wp->rotation.y, 0);
                    wp->velocity.v.x = 0x120;
                    wp->velocity.v.y = -0x120;
                    ground->flags_6 &= ~2;
                    wp->rotation.y = (dir + 0x800) & 0xFFF;
                    if (!(dir & 0xFFFF0000))
                    {
                        wp->routine_2 = 0;
                        wp->anim_AC   = 8;
                        func_800322A8(wp, 8, 0);
                    }
                    else
                    {
                        wp->routine_2 = 1;
                        wp->anim_AC   = 10;
                        func_800322A8(wp, 10, 0);
                    }
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
                if (wp->stun.timer_5 != 0)
                {
                    if (wp->stun.hits_4 == 2 && wp->routine_1 != 5)
                    {
                        wp->routine_1 = 5;
                        wp->routine_2 = 0;
                        wp->anim_AC   = 6;
                        func_800322A8(wp, 6, 0);
                        wp->ground.flags_6 |= 0x40;
                    }
                }
                else
                {
                    wp->stun.timer_5 = 30;
                    wp->stun.hits_4  = 0;
                    if (!func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, Player_work.rotation.y, 0x400) &&
                        wp->routine_1 != 8)
                    {
                        wp->routine_1 = 6;
                        wp->routine_2 = 4;
                        Muku(&wp->position, &pl->position, wp->rotation.y, wp->ctl.turn_3A);
                        wp->anim_AC = 13;
                        func_800322A8(wp, 13, 0);
                    }
                }
            }
        }
    }
    else if (!(wp->routine_1 == 2 || wp->routine_1 == 3 || wp->routine_1 == 4 || wp->routine_1 == 5 || (wp->ground.flags_6 & 0x10) ||
               wp->routine_1 == 8))
    {
        if (wp->ctl.timer_3E != 0)
        {
            wp->ctl.timer_3E--;
        }
        if (wp->ground.flags_6 & 8)
        {
            if (wp->routine_1 != 1)
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, Player_work.rotation.y, 0x400))
                {
                    if (wp->value_80 > 0x120000)
                    {
                        wp->routine_1 = 1;
                        wp->routine_2 = 0;
                    }
                    else if (wp->value_80 <= 0x44AA1 && wp->ctl.timer_3E == 0)
                    {
                        if (wp->variant_3 != 2)
                        {
                            wp->routine_1 = 3;
                            wp->routine_2 = 0;
                        }
                        else
                        {
                            wp->routine_1 = 3;
                            wp->routine_2 = 5;
                            wp->fade.r_0 = wp->fade.g_1 = wp->fade.b_2 = 0;
                        }
                        ctl->turn_3A = 0x80;
                    }
                    else
                    {
                        wp->routine_1 = 0;
                        wp->routine_2 = 6;
                        if (!(ground->flags_6 & 0x80))
                        {
                            ground->count_7 = 0;
                            ground->flags_6 |= 0x80;
                        }
                        ctl->turn_3A = 0x10;
                        if (wp->variant_3 != 2 && !(ground->flags_6 & 1))
                        {
                            wp->routine_1   = 4;
                            wp->anim_AC     = 5;
                            ground->flags_6 = (ground->flags_6 | 3) & ~0x80;
                            func_800322A8(wp, wp->anim_AC, 0);
                        }
                    }
                }
                else
                {
                    wp->routine_1 = 0;
                    wp->routine_2 = 6;
                    if (!(wp->ground.flags_6 & 0x80))
                    {
                        wp->ground.count_7 = 0;
                        wp->ground.flags_6 |= 0x80;
                    }
                    wp->ctl.turn_3A = 0x10;
                    if (wp->value_80 <= 0x44AA1 && wp->ctl.timer_3E == 0)
                    {
                        if (wp->variant_3 != 2)
                        {
                            wp->routine_1 = 3;
                            wp->routine_2 = 0;
                        }
                        else
                        {
                            wp->routine_1 = 3;
                            wp->routine_2 = 5;
                            wp->fade.r_0 = wp->fade.g_1 = wp->fade.b_2 = 0;
                        }
                        ground->flags_6 &= ~0x80;
                        ctl->turn_3A = 0x80;
                    }
                }
            }
            if (wp->routine_1 == 0 && wp->routine_2 == 6 && wp->anim_AC != 1)
            {
                wp->anim_AC = 1;
                func_800322A8(wp, 1, 0);
            }
        }
        else if (wp->routine_1 == 0)
        {
            if (wp->routine_2 == 6)
            {
                wp->velocity.v.x = 0x80;
                wp->routine_2    = 0;
                wp->param_F      = 0;
                wp->ctl.timer_3D = 120;
                wp->ctl.count_3C = 0;
                wp->ground.flags_6 &= ~0x81;
            }
        }
    }
    D_80114E54[wp->routine_1](wp);
    if (wp->value_A6 & 4)
    {
        Sound_call2(0x159, &wp->position);
    }
    else if (wp->value_A6 & 8)
    {
        Sound_call2(0x15A, &wp->position);
    }
    if (wp->routine_1 != 5 && wp->routine_1 != 6 && wp->routine_1 != 7)
    {
        func_8010F890(wp);
    }
    if (wp->variant_3 == 2)
    {
        if ((wp->scale.v.pad & 0x8000) && fade->b_2 == 0)
        {
            wp->flags_0 &= ~2;
        }
        if (!(wp->flags_0 & 2))
        {
            ctl->pos_0 = wp->joints_180[0];
            func_800341BC(&ctl->pos_0, 0x78, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->power_73 | 0x4080000, 0x800000, 0x80);
        }
        else
        {
            ctl->pos_0 = wp->joints_180[0];
            func_800341BC(&ctl->pos_0, 0x78, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->power_73 | 0x4080000, 0x800000, 0);
        }
    }
    else
    {
        ctl->pos_0 = wp->joints_180[0];
        func_800341BC(&ctl->pos_0, 0x78, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->power_73 | 0x4080000, 0x800000, 0);
    }
    if (ground->flags_6 & 2)
    {
        claw.y = 0x738;
        claw.x = 0;
        claw.z = -0x30;
        ApplyMatrix(&wp->mats_1E8[2], &claw, &ofs);
        ctl->pos_0.x = wp->joints_180[2].x + ofs.x;
        ctl->pos_0.y = wp->joints_180[2].y + ofs.y;
        ctl->pos_0.z = wp->joints_180[2].z + ofs.z;
        func_800341BC(&ctl->pos_0, 0x3C, 0, 0x8000, wp->value_1, ctl->hit_18, ground->value_4 | 0x5080000, 0, 0x80);
        ApplyMatrix(&wp->mats_1E8[4], &claw, &ofs);
        ctl->pos_0.x = wp->joints_180[4].x + ofs.x;
        ctl->pos_0.y = wp->joints_180[4].y + ofs.y;
        ctl->pos_0.z = wp->joints_180[4].z + ofs.z;
        func_800341BC(&ctl->pos_0, 0x3C, 0, 0x8000, wp->value_1, ctl->hit_18, ground->value_4 | 0x5080000, 0, 0x80);
    }
    if (wp->variant_3 != 2 && (wp->flags_0 & 2))
    {
        Model_Shadow_Trans(wp, 0xA0, 0x200, 0);
    }
}

void func_8010DD38(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010DD58(STCOM16_WORK *wp)
{
    STCOM16_FADE *fade;

    fade = &wp->fade;
    if (wp->value_80 <= 0x120000 || STCOM_STAGE_ROOM == 0x21D)
    {
        wp->routine_0 = 1;
        wp->routine_1 = 5;
        wp->routine_2 = 0;
        wp->anim_AC   = 6;
        func_800322A8(wp, 6, 0);
        wp->ground.flags_6 |= 0x40;
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->variant_3 == 2)
    {
        wp->scale.v.pad = -0x8000;
        fade->r_0 = fade->g_1 = fade->b_2 = 0;
    }
}

void func_8010DE14(STCOM16_WORK *wp)
{
    D_80114E78[wp->routine_2](wp);
    if (wp->variant_3 == 2)
    {
        wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
        wp->fade.r_0 -= 4;
        wp->fade.g_1 -= 4;
        if (wp->fade.r_0 < 0)
        {
            wp->fade.r_0 = 0;
            wp->fade.g_1 = 0;
            wp->scale.v.pad |= 0x8000;
        }
        if (wp->scale.v.pad & 0x8000)
        {
            if (--wp->fade.b_2 < 0)
            {
                wp->fade.b_2 = 0;
            }
        }
    }
}

void func_8010DF00(STCOM16_WORK *wp)
{
    if (wp->ground.hit_0 & 0xF00)
    {
        wp->ctl.angle_38 = (wp->rotation.y + 0x800) & 0xFFF;
        wp->routine_2    = 5;
        if (wp->rotation.y > wp->ctl.angle_38)
        {
            wp->anim_AC = 14;
        }
        else
        {
            wp->anim_AC = 13;
        }
        func_800322A8(wp, wp->anim_AC, 0);
        func_8010E1DC(wp);
    }
    else
    {
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
        if (wp->ctl.timer_3D == 0)
        {
            if (wp->value_A6 == 1)
            {
                if (!(wp->stun.rand_2 & 1))
                {
                    if (wp->param_F == 0)
                    {
                        wp->ctl.count_3C++;
                    }
                    if (wp->ctl.count_3C != 1)
                    {
                        wp->ctl.timer_3D = 120;
                        wp->param_F      = 0;
                        return;
                    }
                }
                wp->routine_2       = 3;
                wp->param_D         = -0x80;
                wp->param_E         = 0;
                wp->param_F         = 3;
                wp->ctl.position_30 = wp->position;
                wp->ctl.timer_3D    = 10;
                wp->ctl.count_3C    = 0;
                wp->ctl.angle_38    = wp->rotation.y;
            }
        }
        else
        {
            wp->ctl.timer_3D--;
        }
    }
}

void func_8010E068(STCOM16_WORK *wp)
{
    if (wp->param_E == 0)
    {
        if (wp->rotation.y == ((wp->ctl.angle_38 - 0x400) & 0xFFF))
        {
            wp->routine_2    = 2;
            wp->ctl.timer_3D = 5;
        }
        else
        {
            wp->rotation.y -= 0x40;
        }
    }
    else if (wp->rotation.y == ((wp->ctl.angle_38 + 0x400) & 0xFFF))
    {
        wp->routine_2    = 2;
        wp->ctl.timer_3D = 5;
    }
    else
    {
        wp->rotation.y += 0x40;
    }
    wp->rotation.y &= 0xFFF;
}

void func_8010E0F0(ST1D_VIEW *wp)
{
    sint8 temp_v0;

    temp_v0                = (uint8)wp->ext.u_5C.b.value_1 - 1;
    wp->ext.u_5C.b.value_1 = temp_v0;
    if ((temp_v0 << 0x18) == 0)
    {
        wp->u_44.h[0]          = 0x80;
        wp->ext.u_5C.b.value_1 = 0x78;
        wp->routine_2          = 0;
        wp->value_AC           = 1;
        wp->value_CA &= 0xFE;
        func_800322A8(wp, 1, 0);
    }
}

void func_8010E154(STCOM16_WORK *wp)
{
    wp->routine_2    = 1;
    wp->ctl.timer_3D = 10;
    if (wp->stun.rand_2 & 1)
    {
        wp->param_E = 0;
        wp->anim_AC = 13;
    }
    else
    {
        wp->param_E = 1;
        wp->anim_AC = 14;
    }
    func_800322A8(wp, wp->anim_AC, 0);
}

void func_8010E1AC(STCOM16_WORK *wp)
{
    if (wp->ctl.timer_3D == 0)
    {
        wp->routine_2 = 1;
    }
    else
    {
        wp->ctl.timer_3D--;
    }
}

void func_8010E1DC(STCOM16_WORK *wp)
{
    if (wp->rotation.y == wp->ctl.angle_38)
    {
        wp->velocity.v.x = 0x80;
        wp->routine_2    = 0;
        wp->param_F      = 0;
        wp->ctl.count_3C = 0;
        wp->anim_AC      = 1;
        wp->ground.flags_6 &= ~1;
        func_800322A8(wp, 1, 0);
    }
    else if (wp->ctl.angle_38 < wp->rotation.y)
    {
        wp->rotation.y -= 0x80;
    }
    else
    {
        wp->rotation.y += 0x80;
    }
    wp->rotation.y &= 0xFFF;
}

void func_8010E278(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->variant_3 == 2 && wp->routine_1 == 0 && wp->routine_2 == 6)
    {
        if (wp->ground.count_7 < 180)
        {
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn_3A)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            wp->ground.count_7++;
        }
        else
        {
            wp->ground.count_7 = 0;
            wp->routine_1      = 1;
            wp->routine_2      = 0;
            wp->ground.flags_6 &= ~0x80;
        }
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, ctl->turn_3A)) & 0xFFF;
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    }
}

void func_8010E384(STCOM16_WORK *wp)
{
    D_80114E94[wp->routine_2](wp);
    if (wp->variant_3 == 2)
    {
        if (wp->ctl.timer_3F == 0)
        {
            wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
            wp->fade.b_2++;
            wp->scale.v.pad |= 0x8000;
            if (wp->fade.b_2 >= 16)
            {
                wp->scale.v.pad &= 0x7FFF;
                wp->fade.b_2 = 16;
                if (wp->fade.r_0 != 16)
                {
                    wp->fade.r_0 += 4;
                    wp->fade.g_1 += 4;
                }
            }
        }
        else
        {
            wp->ctl.timer_3F--;
            wp->scale.v.pad = -0x8000;
            wp->fade.r_0 = wp->fade.g_1 = wp->fade.b_2 = 0;
        }
    }
}

void func_8010E494(STCOM16_WORK *wp)
{
    wp->anim_AC = 0;
    func_800322A8(wp, 0, 0);
    wp->ctl.timer_3D = 10;
    wp->stun.timer_6 = 90;
    wp->routine_2    = 1;
    wp->ctl.timer_3F = 1;
}

void func_8010E4E4(STCOM16_WORK *wp)
{
    wp->ctl.timer_3F = 1;
    if (wp->ctl.timer_3D != 0)
    {
        wp->ctl.timer_3D--;
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
    }
    else
    {
        wp->anim_AC = 2;
        func_800322A8(wp, 2, 0);
        if (wp->variant_3 == 2)
        {
            wp->ctl.timer_3F = 7;
            wp->fade.r_0     = 0;
            wp->fade.g_1     = 0;
            wp->fade.b_2     = 0;
        }
        wp->velocity.v.x = 0x2D0;
        wp->routine_2    = 2;
        wp->ctl.turn_3A  = 0x10;
    }
}

void func_8010E5AC(STCOM16_WORK *wp)
{
    if (!func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &Player_work.position_fixed, Player_work.rotation.y, 0x400) ||
        wp->stun.timer_6 == 0)
    {
        if (wp->variant_3 == 2 && wp->stun.timer_6 == 0)
        {
            wp->routine_1 = 5;
            wp->routine_2 = 0;
            wp->anim_AC   = 6;
            func_800322A8(wp, 6, 0);
            wp->ground.flags_6 |= 0x40;
        }
        else
        {
            wp->routine_2      = 3;
            wp->ctl.timer_3D   = 20;
            wp->ground.count_7 = 0;
            wp->ground.flags_6 |= 0x80;
            func_8010E710(wp);
        }
    }
    else
    {
        wp->stun.timer_6--;
        if (wp->value_80 <= 0x2BF1F)
        {
            wp->anim_AC   = 4;
            wp->routine_1 = 2;
            wp->ground.flags_6 |= 2;
            func_800322A8(wp, wp->anim_AC, 0);
            wp->ground.value_4 = D_80098844[wp->kind_2]->value_C;
            func_8010E838(wp);
        }
        else
        {
            func_8010E278(wp);
        }
    }
}

void func_8010E710(STCOM16_WORK *wp)
{
    if (wp->ground.hit_0 & 0xF00)
    {
        wp->velocity.v.x = 0x80;
        wp->routine_2    = 5;
        wp->routine_1    = 0;
        wp->ctl.angle_38 = (wp->rotation.y + 0x800) & 0xFFF;
        if (wp->ctl.angle_38 < wp->rotation.y)
        {
            wp->anim_AC = 14;
        }
        else
        {
            wp->anim_AC = 13;
        }
        func_800322A8(wp, wp->anim_AC, 0);
        func_8010E1DC(wp);
    }
    else if (wp->ctl.timer_3D != 0)
    {
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
        wp->ctl.timer_3D--;
    }
    else if (wp->value_A6 != 1)
    {
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    }
    else
    {
        wp->routine_1    = 0;
        wp->velocity.v.x = 0x80;
    }
}

void func_8010E804(ST1D_VIEW *wp)
{
    sint8 temp_v0;

    temp_v0 = wp->ext.u_5C.b.value_1;
    if (temp_v0 != 0)
    {
        wp->ext.u_5C.b.value_1 = temp_v0 - 1;
        return;
    }
    wp->routine_1 = 0;
    wp->u_44.h[0] = 0x80;
}

void func_8010E838(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_GROUND *ground;

    ctl    = &wp->ctl;
    ground = &wp->ground;
    if (wp->value_A6 == 0)
    {
        wp->ctl.turn_3A = 0x20;
        func_8010E278(wp);
    }
    if (wp->variant_3 == 2)
    {
        wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
        wp->fade.b_2++;
        wp->scale.v.pad |= 0x8000;
        if (wp->fade.b_2 >= 16)
        {
            wp->scale.v.pad &= 0x7FFF;
            wp->fade.b_2 = 16;
            if (wp->fade.r_0 != 16)
            {
                wp->fade.r_0 += 4;
                wp->fade.g_1 += 4;
            }
        }
    }
    if (wp->flags_A7 == -1)
    {
        if (wp->variant_3 != 2)
        {
            ground->flags_6 &= ~2;
            wp->velocity.v.x = 0x80;
            wp->routine_1    = 0;
            ctl->turn_3A     = 0x10;
            ctl->timer_3E    = 60;
            ground->count_7  = 0;
            ground->flags_6 |= 0x80;
        }
        else
        {
            wp->routine_1 = 8;
            wp->routine_2 = 0;
        }
    }
}

void func_8010E98C(STAGE_OBJ *wp)
{
    D_80114EA8[wp->routine_2](wp);
}

void func_8010E9C8(STCOM16_WORK *wp)
{
    sint16 turn;

    turn           = Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn_3A);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0)
    {
        wp->anim_AC = 3;
        wp->ground.flags_6 |= 2;
        func_800322A8(wp, wp->anim_AC, 0);
        wp->ground.value_4 = D_80098844[wp->kind_2]->value_B;
        wp->routine_2      = 1;
    }
}

void func_8010EA70(STCOM16_WORK *wp)
{
    if (wp->value_A6 == 2)
    {
        wp->routine_2 = 2;
    }
}

void func_8010EA8C(STCOM16_WORK *wp)
{
    wp->ctl.value_4D += 8;
    if (wp->value_A6 == 1)
    {
        wp->routine_2 = 3;
    }
}

void func_8010EAB4(STCOM16_WORK *wp)
{
    wp->ctl.value_4D -= 8;
    if (wp->ctl.value_4D <= 32)
    {
        wp->routine_2 = 4;
        wp->ground.flags_6 &= ~2;
    }
}

void func_8010EAEC(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_GROUND *ground;

    ctl    = &wp->ctl;
    ground = &wp->ground;
    if (wp->flags_A7 == -1)
    {
        wp->ctl.timer_3E = 60;
        if (wp->variant_3 != 2)
        {
            wp->routine_1 = 0;
            wp->routine_2 = 6;
        }
        else
        {
            wp->routine_1 = 8;
            wp->routine_2 = 0;
        }
        if (ground->flags_6 & 0x80)
        {
            ground->count_7 = 0;
            ground->flags_6 |= 0x80;
        }
        ctl->turn_3A = 0x10;
        wp->anim_AC  = 1;
        func_800322A8(wp, 1, 0);
    }
}

void func_8010EB88(STCOM16_WORK *wp)
{
    wp->anim_AC = 5;
    func_800322A8(wp, 5, 0);
    wp->routine_2   = 6;
    wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
    wp->fade.b_2++;
    wp->scale.v.pad |= 0x8000;
    if (wp->fade.b_2 >= 16)
    {
        wp->scale.v.pad &= 0x7FFF;
        wp->fade.b_2 = 16;
        if (wp->fade.r_0 != 16)
        {
            wp->fade.r_0 += 4;
            wp->fade.g_1 += 4;
        }
    }
}

void func_8010EC50(STCOM16_WORK *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn_3A)) & 0xFFF;
    if (wp->flags_A7 == -1)
    {
        wp->routine_2 = 0;
    }
    wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
    wp->fade.b_2++;
    wp->scale.v.pad |= 0x8000;
    if (wp->fade.b_2 >= 16)
    {
        wp->scale.v.pad &= 0x7FFF;
        wp->fade.b_2 = 16;
        if (wp->fade.r_0 != 16)
        {
            wp->fade.r_0 += 4;
            wp->fade.g_1 += 4;
        }
    }
}

void func_8010ED3C(STCOM16_WORK *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn_3A)) & 0xFFF;
    if (wp->flags_A7 == -1)
    {
        wp->routine_1 = 1;
        wp->routine_2 = 0;
    }
    if (wp->variant_3 == 2)
    {
        wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
        wp->fade.r_0 -= 4;
        wp->fade.g_1 -= 4;
        if (wp->fade.r_0 < 0)
        {
            wp->fade.r_0 = 0;
            wp->fade.g_1 = 0;
            wp->scale.v.pad |= 0x8000;
        }
        if (wp->scale.v.pad & 0x8000)
        {
            if (--wp->fade.b_2 < 0)
            {
                wp->fade.b_2 = 0;
            }
        }
    }
}

void func_8010EE48(STCOM16_WORK *wp)
{
    STCOM16_GROUND *ground;
    sint32 y;

    ground = &wp->ground;
    D_80114EC4[wp->routine_2](wp);
    if (wp->variant_3 == 2)
    {
        if (wp->fade.b_2 == 0)
        {
            wp->scale.v.pad = -0x8000;
            wp->fade.r_0 = wp->fade.g_1 = wp->fade.b_2 = 0;
        }
        else
        {
            wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
            wp->fade.r_0 -= 4;
            wp->fade.g_1 -= 4;
            if (wp->fade.r_0 < 0)
            {
                wp->fade.r_0 = 0;
                wp->fade.g_1 = 0;
                wp->scale.v.pad |= 0x8000;
            }
            if (wp->scale.v.pad & 0x8000)
            {
                if (--wp->fade.b_2 < 0)
                {
                    wp->fade.b_2 = 0;
                }
            }
        }
    }
    func_80032488(wp);
    ground->hit_0 = Obj_map_push_out(wp);
    y             = Obj_ceiling_height_get(wp);
    if (!(ground->flags_6 & 0x40))
    {
        if (y - wp->position_prev.y >= 16)
        {
            if (wp->routine_1 != 5)
            {
                wp->routine_1 = 5;
                wp->routine_2 = 0;
                wp->anim_AC   = 6;
                func_800322A8(wp, 6, 0);
            }
        }
        else
        {
            if (wp->routine_1 == 5)
            {
                if (wp->routine_2 != 2)
                {
                    wp->routine_2 = 2;
                    wp->anim_AC   = 7;
                    func_800322A8(wp, 7, 0);
                    wp->jump_74 = 0;
                }
            }
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
        }
    }
}

void func_8010F02C(ST1D_VIEW *wp)
{
    if (wp->value_A6 == 1)
    {
        wp->u_44.h[1] = -0x300;
        wp->routine_2 = 1;
        wp->u_74.b[0] = 1;
        Sound_call2(0x15F, &wp->position);
    }
}

void func_8010F074(STCOM16_WORK *wp)
{
    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
    wp->velocity.v.y += wp->accel.y;
    if (wp->velocity.v.y >= 0)
    {
        if (wp->stun.hits_4 == 2)
        {
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x10)) & 0xFFF;
        }
        wp->ground.flags_6 &= ~0x40;
    }
}

void func_8010F110(ST1D_VIEW *wp)
{
    if (wp->value_A7 == -1)
    {
        wp->value_AC = 1;
        func_800322A8(wp, 1, 0);
        wp->u_44.h[0]          = 0x80;
        wp->routine_1          = 0;
        wp->routine_2          = 0;
        wp->value_F            = 0;
        wp->ext.u_5C.b.value_1 = 0x78;
        wp->ext.u_5C.b.value_0 = 0;
        wp->value_CA &= 0xFC;
    }
}

void func_8010F180(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_GROUND *ground;
    sint32 y;

    ctl    = &wp->ctl;
    ground = &wp->ground;
    if (wp->variant_3 == 2)
    {
        wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
        wp->fade.b_2++;
        wp->scale.v.pad |= 0x8000;
        if (wp->fade.b_2 >= 16)
        {
            wp->scale.v.pad &= 0x7FFF;
            wp->fade.b_2 = 16;
            if (wp->fade.r_0 != 16)
            {
                wp->fade.r_0 += 4;
                wp->fade.g_1 += 4;
            }
        }
    }
    switch (wp->routine_2)
    {
        case 0:
            func_8002FFC4(&wp->position, &wp->position_fixed, (wp->rotation.y + 0x800) & 0xFFF, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel.y;
            break;
        case 1:
            func_8002FFC4(&wp->position, &wp->position_fixed, wp->rotation.y & 0xFFF, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel.y;
            break;
        case 2:
            if (wp->flags_A7 == -1)
            {
                wp->anim_AC = 12;
                func_800322A8(wp, 12, 0);
                wp->routine_2 = 3;
            }
            break;
        case 3:
        case 4:
            if (wp->flags_A7 == -1)
            {
                if (wp->variant_3 == 2 && (ground->flags_6 & 0x10))
                {
                    wp->routine_1 = 8;
                    wp->routine_2 = 0;
                }
                else
                {
                    wp->anim_AC = 1;
                    func_800322A8(wp, 1, 0);
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                }
                wp->velocity.v.x = 0x80;
                wp->param_F      = 0;
                ctl->timer_3D    = 120;
                ctl->count_3C    = 0;
                ground->flags_6  = 0;
                wp->ctl.value_4D = 32;
            }
            if (wp->routine_2 == 4)
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
            }
            break;
    }
    func_80032488(wp);
    ground->hit_0 = Obj_map_push_out(wp);
    y             = Obj_ceiling_height_get(wp);
    if ((ground->flags_6 & 0x10) && !(ground->flags_6 & 0x20) && y == wp->position.y)
    {
        if (wp->routine_2 == 0)
        {
            wp->anim_AC = 9;
            func_800322A8(wp, 9, 0);
        }
        else
        {
            wp->anim_AC = 11;
            func_800322A8(wp, 11, 0);
        }
        wp->routine_2 = 2;
        ground->flags_6 |= 0x20;
    }
}

void func_8010F454(STCOM16_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0         = 5;
        effect->kind_2          = 0x80;
        effect->variant_3       = 0x40;
        effect->sprite.position = wp->joints_180[0];
        func_80047148(wp, &wp->joints_180[0], effect);
    }
    wp->routine_0 = 2;
    wp->flags_0 &= ~2;
}

void func_8010F4DC(STCOM16_WORK *wp)
{
    D_80114ED0[wp->routine_2](wp);
    if (wp->ctl.timer_3F == 0)
    {
        wp->scale.v.pad = (wp->fade.r_0 & 0x1F) | ((wp->fade.g_1 & 0x1F) << 5) | ((wp->fade.b_2 & 0x1F) << 10);
        wp->fade.r_0 -= 4;
        wp->fade.g_1 -= 4;
        if (wp->fade.r_0 < 0)
        {
            wp->fade.r_0 = 0;
            wp->fade.g_1 = 0;
            wp->scale.v.pad |= 0x8000;
        }
        if (wp->scale.v.pad & 0x8000)
        {
            if (--wp->fade.b_2 < 0)
            {
                wp->fade.b_2 = 0;
            }
        }
    }
    else
    {
        wp->ctl.timer_3F--;
        wp->scale.v.pad = 0x4210;
    }
}

void func_8010F5DC(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_FADE *fade;

    ctl  = &wp->ctl;
    fade = &wp->fade;
    if (wp->stun.rand_2 & 1)
    {
        wp->anim_AC = 13;
        func_800322A8(wp, 13, 0);
        wp->param_E      = 0;
        wp->ctl.angle_38 = wp->rotation.y;
    }
    else
    {
        wp->anim_AC = 14;
        func_800322A8(wp, 14, 0);
        wp->param_E      = 1;
        wp->ctl.angle_38 = wp->rotation.y;
    }
    wp->routine_2 = 1;
    ctl->timer_3F = 1;
    fade->r_0     = 16;
    fade->g_1     = 16;
    fade->b_2     = 16;
}

void func_8010F690(STCOM16_WORK *wp)
{
    func_8010E068(wp);
    wp->ctl.timer_3F = 1;
    wp->fade.r_0     = 16;
    wp->fade.g_1     = 16;
    wp->fade.b_2     = 16;
}

void func_8010F6D0(ST1D_VIEW *wp)
{
    wp->value_AC = 2;
    func_800322A8(wp, 2, 0);
    wp->routine_2          = 3;
    wp->u_44.h[0]          = 0x2D0;
    wp->ext.u_58.h[1]      = 0x10;
    wp->ext.u_5C.b.value_3 = 0xF;
    wp->u_64.b[0]          = 0x10;
    wp->u_64.b[1]          = 0x10;
    wp->u_64.b[2]          = 0x10;
}

void func_8010F738(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;

    ctl = &wp->ctl;
    if ((wp->ground.hit_0 & 0xF00) || wp->value_80 > 0x480000)
    {
        wp->ctl.angle_38 = (wp->rotation.y + 0x800) & 0xFFF;
        if (wp->ctl.angle_38 < wp->rotation.y)
        {
            wp->anim_AC = 14;
        }
        else
        {
            wp->anim_AC = 13;
        }
        func_800322A8(wp, wp->anim_AC, 0);
        wp->routine_2 = 4;
        ctl->angle_38 = (wp->rotation.y + 0x800) & 0xFFF;
    }
    else
    {
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    }
}

void func_8010F7F0(STCOM16_WORK *wp)
{
    if (wp->rotation.y == wp->ctl.angle_38)
    {
        wp->velocity.v.x = 0x80;
        wp->routine_1    = 0;
        wp->routine_2    = 0;
        wp->param_F      = 0;
        wp->ctl.count_3C = 0;
        wp->anim_AC      = 1;
        wp->ground.flags_6 &= ~1;
        func_800322A8(wp, 1, 0);
    }
    else if (wp->ctl.angle_38 < wp->rotation.y)
    {
        wp->rotation.y -= 0x80;
    }
    else
    {
        wp->rotation.y += 0x80;
    }
    wp->rotation.y &= 0xFFF;
}

void func_8010F890(STCOM16_WORK *wp)
{
    sint32 y;

    func_80032488(wp);
    wp->ground.hit_0 = Obj_map_push_out(wp);
    y                = Obj_ceiling_height_get(wp);
    if (y - wp->position_prev.y >= 16)
    {
        wp->routine_1 = 5;
        wp->routine_2 = 0;
        wp->anim_AC   = 6;
        func_800322A8(wp, 6, 0);
    }
    else
    {
        wp->position.y       = y;
        wp->position_fixed.y = y << 16;
    }
}
