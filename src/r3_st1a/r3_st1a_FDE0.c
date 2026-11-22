#include "common.h"
#include "st1a.h"

void func_8010FDE0(ST1A_VIEW *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            wp->variant_3 = D_80131EFD[wp->value_C * 3];
            wp->kind_2    = D_80131EFC[wp->value_C * 3];
            Model_work_init(wp, &wp->variant_3);
            wp->kind_2           = 0x49;
            wp->rotation.x       = 0;
            wp->u_64.w[0]        = 0;
            wp->u_44.w[0]        = 0;
            wp->u_48.w[0]        = 0;
            wp->u_64.w[0]        = 0; // stored twice in retail
            wp->u_70.w[0]        = 0;
            wp->u_74.w[0]        = 0;
            wp->value_158        = 0x2000200;
            wp->u_15C.w[0]       = 0x42100200;
            wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
            wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
            wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
            func_800322A8(wp, 0, 0);
            if (wp->value_C == 4)
            {
                wp->value_D   = 0x40;
                wp->routine_0 = 2;
            }
            else
            {
                wp->routine_0++;
            }
            break;
        case 1:
            wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
            wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
            wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
            func_80032488(wp);
            Model_Shadow_Trans(wp, D_80131EFE[wp->value_C * 3], 0x200, 0);
            break;
        case 2:
            wp->value_D--;
            Obj_pos_set(wp, 0x20, 0, 0);
            if (wp->value_D == 0)
            {
                wp->routine_0 = 1;
            }
            func_80032488(wp);
            Model_Shadow_Trans(wp, D_80131EFE[wp->value_C * 3], 0x200, 0);
            break;
    }
}

void func_8010FFD8(ST1A_VIEW *wp)
{
    wp->position_prev           = wp->position;
    wp->position_fixed_prev.x   = wp->position_fixed.x;
    wp->position_fixed_prev.y   = wp->position_fixed.y;
    wp->position_fixed_prev.z   = wp->position_fixed.z;
    wp->position_fixed_prev.pad = wp->position_fixed.pad;
    wp->rotation_prev           = wp->rotation;
    wp->u_15C.h[1]              = 0x4210;
    wp->value_3B2               = rand();
    D_80131F14[wp->routine_0](wp);
    wp->u_350.w[0] = 0;
}

void func_80110090(ST1A_VIEW_H *wp)
{
    ST1A_CTL *ctl;
    STCOM16_STUN *stun;

    ctl            = ST1A_CTL_OF(wp);
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
    func_80036478(ctl->track_18, 7, -0x60);
    wp->value_B2 = wp->value_B0 = wp->value_6E = D_80098844[wp->kind_2]->life_8 << 5;
    wp->routine_1                              = 0;
    wp->routine_0                              = 1;
    wp->u_74.b[0]                              = 0;
    wp->u_15C.h[1]                             = 0x4210;
    wp->value_AC                               = 0;
    wp->data_78                                = D_80131F74;
    wp->u_44.h[0]                              = 0x140;
    wp->value_AD                               = 0;
    func_800322A8(wp, wp->value_AC, 0);
    ctl->ground_60 = func_8004B414(wp);
    ctl->angle_64  = (wp->rotation.y + 0x800) & 0xFFF;
}

void func_801101F4(ST1A_VIEW_I *wp)
{
    ST1A_CTL *ctl;
    STCOM16_STUN *stun;
    sint32 damage;

    ctl  = ST1A_CTL_OF(wp);
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
    D_80131F20[wp->routine_1](wp);
    func_80032488(wp);
    if (wp->value_A6 & 0x40)
    {
        Sound_call2(0x1BD, &wp->position);
    }
    ctl->ground_60       = func_8004B414(wp);
    wp->position.y       = func_80048E6C(wp);
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

void func_8011057C(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8011059C(ST1A_VIEW_J *wp)
{
    ST1A_CTL *ctl;
    STCOM16_STUN *stun;
    uint32 n;

    ctl  = ST1A_CTL_OF(wp);
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

void func_8011072C(ST1A_VIEW *wp)
{
    if (wp->rotation.y == wp->value_3AC)
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

void func_80110778(ST1A_VIEW_H *wp)
{
    ST1A_SHOT_B *shot;
    shot = (ST1A_SHOT_B *)&wp->value_1D8;
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
            D_80131F38[wp->variant_3 & 0xF](wp);
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
                            func_801110B4(wp, 0);
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
                            func_801110B4(wp, 1);
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
                                func_801110B4(wp, 2);
                                shot->count_2--;
                                shot->index_6++;
                                func_801110B4(wp, 2);
                                shot->count_2--;
                                shot->index_6++;
                                func_801110B4(wp, 2);
                                shot->count_2--;
                                shot->index_6++;
                                func_801110B4(wp, 2);
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

void func_80110C64(ST1A_VIEW *wp)
{
    uint32 n;

    if (wp->routine_3 == 0)
    {
        wp->value_1DC = 0;
        wp->value_E   = 0;
        n             = wp->value_3B2 & 7;
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

void func_80110CF4(ST1A_VIEW_D *wp)
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

void func_80110D8C(ST1A_VIEW_E *wp)
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

void func_80110E20(ST1A_VIEW_F *wp)
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

void func_80110EB8(ST1A_VIEW *wp)
{
    if ((wp->value_A7 == -1) || (wp->routine_2 == 1))
    {
        wp->routine_2 = 1;
        wp->value_3B4 &= 0xFB;
        if (wp->value_AD != 1)
        {
            wp->value_AC = 1;
            wp->value_AD = 1;
            func_800322A8(wp, wp->value_AC, 0);
        }
        wp->routine_1 = 2;
        wp->routine_3 = 0;
        wp->value_1D8 = 0;
        wp->value_3B4 |= 0x20;
    }
}

// ported from r3_st1d func_8010C84C
void func_80110F54(ST1A_VIEW_K *wp)
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
            joint = D_80131F44[wp->value_1DD].joint_0;
            fx    = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0           = 5;
                fx->kind_2            = 0x80;
                fx->variant_3         = 0x40;
                fx->value_D           = D_80131F44[wp->value_1DD].look_1;
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

void func_801110B4(ST1A_VIEW_H *wp, uint8 kind)
{
    ST1A_10C *slot;
    ST1A_SHOT_B *shot;
    ST1A_CTL *ctl;
    STAGE_PL_VIEW *pl;
    sint32 dist;
    sint32 c;
    sint32 s;
    sint16 spread;
    sint32 angle;

    spread = 0;
    dist   = SquareRoot0(wp->value_80);
    ctl    = ST1A_CTL_OF(wp);
    pl     = &STAGE_PL;
    slot   = Open_SHL_WORK();
    shot   = (ST1A_SHOT_B *)&wp->value_1D8;
    if (slot != NULL)
    {
        slot->flags_0 = 3;
        slot->kind_2  = 1;
        slot->value_4 = 0;
        if (!(kind & 2))
        {
            Sound_call2(0x1BE, &wp->position);
            slot->value_F = 0x10;
        }
        else
        {
            slot->value_F = 9;
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
            angle = spread + 0x800;
            c     = rcos(wp->rotation.y + angle);
            s     = rsin(wp->rotation.y + angle);
        }
        else if (kind == 1)
        {
            c = rcos(wp->rotation.y + 0x800);
            s = rsin(wp->rotation.y + 0x800);
        }
        else
        {
            c = rcos(wp->rotation.y + D_80131F54[shot->index_6]);
            s = rsin(wp->rotation.y + D_80131F54[shot->index_6]);
        }
        if (slot->value_F == 0x10)
        {
            slot->position.x         = wp->vec_180[0].x;
            slot->position.y         = wp->vec_180[0].y;
            slot->position.z         = wp->vec_180[0].z;
            slot->position_fixed.v.x = slot->position.x << 16;
            slot->position_fixed.v.y = slot->position.y << 16;
            slot->position_fixed.v.z = slot->position.z << 16;
            func_8002FFC4(&slot->position, &slot->position_fixed.v, wp->rotation.y & 0xFFF, 0x550, 0, 0);
            pl->value_C4.x = slot->position.x + ((s * dist) >> 12);
            if (kind == 0)
            {
                pl->value_C4.y = pl->value_3AA + ((ctl->rand_6A & 0x3F) - 0x20);
            }
            else
            {
                pl->value_C4.y = pl->value_3EA + 0x30;
            }
            pl->value_C4.z = slot->position.z + ((c * dist) >> 12);
            func_80030EE8(slot, &pl->value_C4, 0x30);
        }
        else
        {
            slot->position.x         = wp->vec_180[1].x;
            slot->position.y         = wp->vec_180[1].y;
            slot->position.z         = wp->vec_180[1].z;
            slot->position_fixed.v.x = slot->position.x << 16;
            slot->position_fixed.v.y = slot->position.y << 16;
            slot->position_fixed.v.z = slot->position.z << 16;
            func_8002FFC4(&slot->position, &slot->position_fixed.v, wp->rotation.y & 0xFFF, 0x550, 0, 0);
            pl->value_C4.x = slot->position.x + ((s * ((ctl->rand_6A & 0x3FF) + 0x80)) >> 12);
            pl->value_C4.y = slot->position.y;
            pl->value_C4.z = slot->position.z + ((c * ((ctl->rand_6A & 0x3FF) + 0x80)) >> 12);
            Obj_launch_set(slot, pl, 0x14, 0, 0xFF);
        }
    }
}

#ifdef __wasm32__
void func_80111C40(ST1A_TALKER3 *wp, ST1A_FACE *face);
#endif

void func_8011146C(ST1A_TALKER3 *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face_348;
    D_80131F80[wp->routine_0](wp, &Scene_work, face);
    func_80111C40(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face_348.value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0 && (wp->flags_0 & 2))
    {
        Model_Shadow_Trans(wp, 0x26, 0x200, 0);
    }
}

#ifdef __wasm32__
void func_80111BF0(ST1A_TALKER3 *wp, ST1A_FACE *face, sint32 index);
void func_80111C18(ST1A_TALKER3 *wp, ST1A_FACE *face, sint32 index);
#endif

void func_801115A0(ST1A_TALKER3 *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_78       = 0;
    wp->anim_AC        = 0;
    wp->anim_prev_AD   = 0xFF;
    face->value_2      = 0;
    face->timer_0      = 0;
    face->shadow_12    = 1;
    func_80111BF0(wp, face, 1);
    func_80111C18(wp, face, 1);
    wp->u_C.b.byte_C = 0;
    wp->routine_0    = 1;
    wp->routine_1    = 0;
    wp->routine_2    = 0;
    wp->routine_3    = 0;
}

#ifdef __wasm32__
void func_80111D88(ST1A_TALKER3 *wp);
#endif

void func_80111658(ST1A_TALKER3 *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 0x14)
            {
                wp->anim_AC   = 1;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0x10E:
                        wp->anim_AC   = 2;
                        face->value_2 = 0;
                        break;
                    case 0x22:
                    case 0x7A:
                    case 0xF0:
                    case 0x140:
                        func_80111C18(wp, face, 6);
                        break;
                    case 0x6E:
                    case 0xC8:
                    case 0x127:
                    case 0x181:
                        func_80111C18(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 7 && scene->value_10 == 1)
            {
                func_80111C18(wp, face, 7);
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 7)
            {
                switch (scene->value_10)
                {
                    case 0x67:
                    case 0xD5:
                    case 0x125:
                        func_80111C18(wp, face, 7);
                        break;
                    case 0x4A:
                    case 0xC3:
                    case 0x111:
                    case 0x193:
                        func_80111C18(wp, face, 5);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 9 && scene->value_10 == 1)
            {
                wp->anim_AC   = 3;
                face->value_2 = 0;
                func_80111C18(wp, face, 2);
                wp->routine_1++;
            }
            break;
        case 3:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                    case 0x41:
                    case 0x78:
                        func_80111C18(wp, face, 8);
                        break;
                    case 0xD2:
                    case 0xFA:
                        func_80111C18(wp, face, 9);
                        break;
                    case 0x13E:
                    case 0x186:
                        func_80111C18(wp, face, 0xA);
                        break;
                    case 0x30:
                    case 0x5A:
                    case 0xBE:
                    case 0xE1:
                    case 0x131:
                    case 0x172:
                    case 0x1AE:
                        func_80111C18(wp, face, 2);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xA && scene->value_10 == 1)
            {
                func_80111C18(wp, face, 2);
                wp->routine_1++;
            }
            break;
        case 4:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x11:
                case 0x3C:
                    func_80111C18(wp, face, 0xB);
                    break;
                case 0x2D:
                case 0x96:
                    func_80111C18(wp, face, 2);
                    break;
                case 0xAA:
                    func_80111C18(wp, face, 0xB);
                    wp->routine_1++;
                    break;
            }
            break;
        case 5:
            switch (scene->value_10)
            {
                case 0xF8:
                    func_80111C18(wp, face, 2);
                    break;
                case 0x118:
                    func_80111C18(wp, face, 0xB);
                    break;
                case 0x121:
                    func_80111BF0(wp, face, 2);
                    func_80111C18(wp, face, 4);
                    wp->routine_1++;
                    break;
            }
            break;
        case 6:
            if (scene->u_8.byte[1] == 0xB)
            {
                switch (scene->value_10)
                {
                    case 25:
                        func_80111D88(wp);
                        wp->u_C.b.byte_C++;
                        break;
                    case 30:
                        func_80111D88(wp);
                        wp->u_C.b.byte_C++;
                        break;
                    case 35:
                        func_80111D88(wp);
                        wp->u_C.b.byte_C++;
                        break;
                    case 40:
                        wp->flags_0 &= ~2;
                        face->shadow_12 = 0;
                        func_80111D88(wp);
                        wp->u_C.b.byte_C++;
                        break;
                    case 45:
                        func_80111D88(wp);
                        wp->u_C.b.byte_C++;
                        wp->routine_1++;
                        break;
                }
            }
            break;
    }
}

void func_80111BF0(ST1A_TALKER3 *wp, ST1A_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_801320F0[index];
}

void func_80111C18(ST1A_TALKER3 *wp, ST1A_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80132100[index];
}

void func_80111C40(ST1A_TALKER3 *wp, ST1A_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x50004, Model_uv_cell(face->shape_C, 0x3E, 0x3A, 4));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x70006, Model_uv_cell(face->shape_F, 0x3E, 0x3A, 4));
    }
    face->prev_10 = face->shape_F;
}

void func_80111D88(ST1A_TALKER3 *wp)
{
    STCOM_EFFECT *fx;

    fx = func_80031618();
    if (fx != NULL)
    {
        fx->flags_0           = 5;
        fx->kind_2            = 0x80;
        fx->variant_3         = 0x41;
        fx->value_D           = 3;
        fx->sprite.position.x = wp->position.x + D_80132130[wp->u_C.b.byte_C].x;
        fx->sprite.position.y = wp->position.y + D_80132130[wp->u_C.b.byte_C].y;
        fx->sprite.position.z = wp->position.z + D_80132130[wp->u_C.b.byte_C].z;
    }
}

void func_80111E44(ST1A_OBJ *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]     = 0x02000200;
            wp->scale.words[1]     = 0x42100200;
            wp->rotation.x         = 0;
            wp->value_64.value     = 0;
            wp->value_44.value     = 0;
            wp->value_48.value     = 0;
            wp->value_64.value     = 0;
            wp->value_70           = 0;
            wp->value_74           = 0;
            wp->position_fixed.v.x = wp->position_fixed_prev.x = wp->position.x << 16;
            wp->position_fixed.v.z = wp->position_fixed_prev.z = wp->position.z << 16;
            wp->position_fixed.v.y = wp->position_fixed_prev.y = wp->position.y << 16;
            func_800322A8(wp, 0, 0);
            wp->routine_0++;
            // fall through
        case 1:
            func_80033A28(wp);
            *(uint16 *)0x1F80012C = wp->rotation.z;
            Model_parts_mtx_set_y(wp);
            break;
    }
}

void func_80111F40(STAGE_FACE2 *face, sint32 index)
{
    face->shape_8 = 0;
    face->mouth_0 = D_80132164[index];
    face->prev_9  = 0;
}

void func_80111F60(STAGE_FACE2 *face, sint32 index)
{
    face->index_A = 0;
    face->eyes_4  = D_801321B8[index];
    face->shape_B = 0;
}

void func_80111F80(ST1A_TALKER *wp, STAGE_FACE2 *face)
{
    if (face->prev_9 == 0)
    {
        if (face->mouth_0[face->shape_8] != 0x7E)
        {
            if (face->mouth_0[face->shape_8] == 0x7F)
            {
                face->shape_8 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x50004, Model_uv_cell(face->mouth_0[face->shape_8], 0x3E, 0x3A, 4));
            face->prev_9 = face->mouth_0[face->shape_8 + 1];
            face->shape_8 += 2;
        }
    }
    else
    {
        face->prev_9--;
    }
    if (face->shape_B == 0)
    {
        if (face->eyes_4[face->index_A] != 0x7E)
        {
            if (face->eyes_4[face->index_A] == 0x7F)
            {
                face->index_A = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x70006, Model_uv_cell(face->eyes_4[face->index_A], 0x3E, 0x3A, 4));
            face->shape_B = face->eyes_4[face->index_A + 1];
            face->index_A += 2;
        }
    }
    else
    {
        face->shape_B--;
    }
}

void func_801120E4(STAGE_OBJ *wp)
{
    sint32 temp_v1;

    temp_v1                = 0xFED50000 - (rsin((*(uint16 *)0x1F800002 & 0x7C) << 6) << 6);
    wp->position_fixed.v.y = temp_v1;
    wp->position.y         = (sint16)(temp_v1 >> 0x10);
}

#ifdef __wasm32__
void func_801124D0(ST1A_TALKER *wp, STAGE_FACE2 *face);
#endif

void func_80112134(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_78       = 0;
    wp->routine_0++;
    func_801124D0(wp, face);
}

void func_801121AC(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_801120E4(wp);
    if (Scene_work.value_10 == 1)
    {
        func_800322A8(wp, 0, 0);
    }
    else
    {
        func_80032488(wp);
    }
    switch (Scene_work.value_10)
    {
        case 1:
            func_80111F60(face, 0);
            func_80111F40(face, 0);
            break;
        case 0x3C:
            func_80111F60(face, 4);
            break;
        case 0xAA:
            func_80111F60(face, 0);
            break;
    }
}

void func_80112284(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_801120E4(wp);
    func_80032488(wp);
    switch (Scene_work.value_10)
    {
        case 1:
            func_80111F60(face, 4);
            func_80111F40(face, 0);
            break;
        case 0x32:
            func_80111F60(face, 0);
            break;
        case 0x3C:
            func_80111F60(face, 4);
            break;
        case 0x8C:
            func_80111F60(face, 0);
            break;
        case 0x96:
            func_80111F60(face, 4);
            break;
        case 0xD2:
            func_80111F60(face, 0);
            break;
        case 0xDC:
            func_80111F60(face, 4);
            break;
        case 0x122:
            func_80111F60(face, 0);
            break;
        case 0x140:
            func_80111F60(face, 4);
            break;
    }
}

void func_801123AC(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (Scene_work.value_10 == 1)
    {
        func_80111F60(face, 5);
        func_80111F40(face, 1);
    }
    Obj_pos_set(wp, 0, wp->value_44.half[1], 0);
    func_80032488(wp);
}

void func_80112420(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (Scene_work.value_10 == 1)
    {
        func_80111F60(face, 1);
        func_80111F40(face, 1);
    }
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
    func_80032488(wp);
}

void func_80112494(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, 0);
    func_80032488(wp);
}

void func_801124D0(ST1A_TALKER *wp, STAGE_FACE2 *face)
{
    if (D_801321D0[Scene_work.u_8.byte[1]] != NULL)
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        D_801321D0[Scene_work.u_8.byte[1]](wp, face);
    }
}

void func_8011259C(ST1A_TALKER *wp)
{
    STAGE_FACE2 *face;

    face = &wp->face_348;
    D_801321F8[wp->routine_0](wp, face);
    func_80111F80(wp, face);
}

#ifdef __wasm32__
void func_801130D0(ST1A_WATCHER *wp, ST1A_EYES *face);
#endif

void func_801125F8(ST1A_WATCHER *wp)
{
    ST1A_EYES *face;
    STCOM_SVECTOR pos;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face_348;
    D_80132200[wp->routine_0](wp, &Scene_work, face);
    func_801130D0(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face_348.speed_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->flags_0 & 2)
    {
        if (face->mode_B == 1)
        {
            Model_Shadow_Trans(wp, 0x24, 0x200, 0);
        }
        else if (face->mode_B == 2)
        {
            pos = wp->position;
            pos.z -= 0x70;
            func_8002CA10(&pos, 0x24, 0x200, 0);
        }
    }
}

#ifdef __wasm32__
void func_801130A8(void *wp, ST1A_EYES *face, sint32 index);
#endif

void func_8011277C(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_78       = 0;
    wp->anim_AC        = 1;
    wp->anim_prev_AD   = 0xFF;
    face->speed_2      = 0;
    face->value_0      = 0;
    face->mode_B       = 1;
    func_801130A8(wp, face, 1);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80112818(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    D_80132208[wp->routine_1](wp, scene, face);
}

void func_80112854(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    wp->anim_prev_AD = 0xFF;
    if (scene->u_8.byte[1] == 0x15)
    {
        switch (scene->value_10)
        {
            case 0x6E:
                func_801130A8(wp, face, 1);
                break;
            case 0x3C:
            case 0xA0:
                func_801130A8(wp, face, 8);
                break;
            case 0xA:
            case 0xE6:
                func_801130A8(wp, face, 9);
                break;
        }
    }
    else if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 1)
    {
        func_801130A8(wp, face, 2);
        wp->routine_1 = 1;
        wp->routine_2 = 0;
    }
}

void func_80112954(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    wp->anim_prev_AD = 0xFF;
    if (scene->u_8.byte[1] == 0x17)
    {
        switch (scene->value_10)
        {
            case 0x32:
            case 0x46:
            case 0x8C:
            case 0xDC:
                func_801130A8(wp, face, 0xA);
                break;
            case 0x3C:
            case 0x73:
            case 0xD2:
            case 0x102:
                func_801130A8(wp, face, 2);
                break;
            case 0x14:
            case 0x113:
                func_801130A8(wp, face, 0xB);
                break;
        }
    }
    else if (scene->u_8.byte[1] == 0x18 && scene->value_10 == 1)
    {
        func_801130A8(wp, face, 1);
        wp->routine_1 = 2;
        wp->routine_2 = 0;
    }
}

void func_80112AA0(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x32:
                case 0x7D:
                case 0xA0:
                case 0xE6:
                case 0x122:
                case 0x172:
                case 0x19F:
                    func_801130A8(wp, face, 8);
                    break;
                case 0x6E:
                case 0x82:
                case 0xCA:
                case 0x110:
                case 0x154:
                case 0x186:
                case 0x1D1:
                    func_801130A8(wp, face, 1);
                    break;
                case 0x262:
                    wp->anim_AC = 2;
                    func_801130A8(wp, face, 0xC);
                    wp->routine_2++;
                    break;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 0x1A && scene->value_10 == 1)
            {
                wp->anim_AC = 3;
                func_801130A8(wp, face, 3);
                wp->routine_1 = 3;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_80112C98(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    switch (wp->routine_2)
    {
        case 0:
            if (wp->value_A7 == -1)
            {
                func_801130A8(wp, face, 4);
                wp->routine_2++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 0x1A && scene->value_10 == 0x1E)
            {
                func_801130A8(wp, face, 0xD);
            }
            else if (scene->u_8.byte[1] == 0x1F && scene->value_10 == 1)
            {
                func_801130A8(wp, face, 2);
                wp->routine_1 = 4;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_80112D7C(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    if (scene->u_8.byte[1] == 0x20 && scene->value_10 == 1)
    {
        wp->anim_AC   = 6;
        face->speed_2 = 0;
        func_801130A8(wp, face, 2);
        face->mode_B  = 2;
        wp->routine_1 = 5;
        wp->routine_2 = 0;
    }
}

void func_80112DF0(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0xA:
                    func_801130A8(wp, face, 0x10);
                    break;
                case 0x1E:
                    func_801130A8(wp, face, 2);
                    break;
                case 0x3C:
                    wp->routine_2++;
                    break;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 0x20 && scene->value_10 == 0x47)
            {
                face->mode_B = 0;
            }
            else if (scene->u_8.byte[1] == 0x21 && scene->value_10 == 1)
            {
                wp->scale.words[0] = 0x01990199;
                wp->scale.words[1] = 0x42100199;
                wp->anim_AC        = 6;
                wp->anim_prev_AD   = 0xFF;
                face->speed_2      = 0;
                func_801130A8(wp, face, 5);
                wp->routine_1 = 6;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_80112F48(ST1A_WATCHER *wp, STAGE_SCENE_WORK *scene, ST1A_EYES *face)
{
    switch (wp->routine_2)
    {
        case 0:
            if (scene->value_10 == 0x3F)
            {
                wp->anim_AC   = 7;
                face->speed_2 = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (wp->value_A4 == 0xD)
            {
                wp->anim_AC   = 7;
                face->speed_2 = 0xD;
                wp->routine_2++;
            }
            break;
        case 2:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x50:
                    func_801130A8(wp, face, 0xE);
                    break;
                case 0x7D:
                    func_801130A8(wp, face, 5);
                    break;
                case 0x8C:
                    func_801130A8(wp, face, 0xF);
                    break;
                case 0xA4:
                    wp->routine_2++;
                    break;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 0x22 && scene->value_10 == 1)
            {
                wp->routine_1 = 7;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_801130A0(void)
{
}

void func_801130A8(void *wp, ST1A_EYES *face, sint32 index)
{
    face->index_A = 0;
    face->shape_8 = 0;
    face->prev_9  = -1;
    face->eyes_4  = D_8013231C[index];
}

void func_801130D0(ST1A_WATCHER *wp, ST1A_EYES *face)
{
    if (face->eyes_4[face->index_A + 1] != 0x7E)
    {
        if (face->eyes_4[face->index_A + 1] == 0x7F)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_8 = face->eyes_4[face->index_A];
    if (face->shape_8 != face->prev_9)
    {
        Model_mesh_uv_copy(wp->model_88, 0x80007, Model_uv_cell(face->shape_8, 0x2D, 0x3C, 5));
    }
    face->prev_9 = face->shape_8;
}

void func_8011318C(STAGE_OBJ *wp)
{
    D_80132370[wp->variant_3][wp->routine_0](wp, &Scene_work, &wp->u_4E0.face);
}

#ifdef __wasm32__
void func_80114478(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801144A0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_80114610(STAGE_OBJ *wp, STAGE_FACE *face);
#endif

void func_801131DC(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            face->shadow_12 = 0;
            func_80114478(wp, face, 0);
            func_801144A0(wp, face, 0);
            func_80114610(wp, face);
            wp->routine_1++;
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 0x23:
                        func_801144A0(wp, face, 0);
                        break;
                    case 1:
                        func_801144A0(wp, face, 0x11);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0x41:
                    case 0x87:
                    case 0xE6:
                        func_801144A0(wp, face, 0);
                        break;
                    case 0x14:
                    case 0x50:
                    case 0xD2:
                    case 0xFF:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x12C:
                        func_801144A0(wp, face, 0);
                        wp->routine_1++;
                        break;
                }
            }
            func_80114610(wp, face);
            break;
        case 2:
            if (scene->u_8.byte[1] == 8)
            {
                wp->flags_0 |= 2;
                Model_work_init(wp, NULL);
                wp->scale.words[0] = 0x02000200;
                wp->scale.words[1] = 0x200;
                wp->scale.v.pad    = 0x4210;
                wp->anim_AC        = 0x10;
                wp->value_78       = 0;
                wp->anim_prev_AD   = 0xFF;
                face->value_2      = 0;
                func_80114478(wp, face, 1);
                func_801144A0(wp, face, 0);
                func_801144C8(wp, face);
                face->shadow_12 = 1;
                wp->routine_1   = 0;
                wp->routine_2   = 0;
                wp->routine_3   = 0;
                wp->routine_0++;
                func_800322A8(wp, wp->anim_AC, face->value_2);
            }
            break;
    }
}

void func_80113460(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 9 && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x14:
                        func_801144A0(wp, face, 1);
                        break;
                    case 0x3C:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x64:
                        func_801144A0(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 0);
            }
            else if (scene->u_8.byte[1] == 0xE && scene->value_10 == 0x12C)
            {
                func_80114478(wp, face, 0xE);
                func_801144A0(wp, face, 0x12);
                wp->anim_AC   = 0x11;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0xF && scene->value_10 == 1)
            {
                func_80114478(wp, face, 3);
                func_801144A0(wp, face, 1);
                wp->anim_AC   = 0x12;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 0xF)
            {
                switch (scene->value_10)
                {
                    case 5:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x14:
                        func_801144A0(wp, face, 1);
                        break;
                    case 0x28:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x50:
                        func_801144A0(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x11 && scene->value_10 == 1)
            {
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 3);
                wp->routine_1++;
            }
            if (wp->value_A7 != -1)
            {
                Obj_pos_set(wp, 0x2A, 0, 0);
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 0x11)
            {
                if (scene->value_10 == 0xA)
                {
                    func_80114478(wp, face, 0xF);
                }
                else if (scene->value_10 == 0x1E)
                {
                    func_80114478(wp, face, 4);
                    func_801144A0(wp, face, 4);
                    wp->anim_AC   = 0x14;
                    face->value_2 = 0;
                }
            }
            else if (scene->u_8.byte[1] == 0x12 && scene->value_10 == 1)
            {
                wp->rotation.y = 0x700;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 2);
                wp->routine_1++;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 0x13 && scene->value_10 == 0xA)
            {
                func_80114478(wp, face, 5);
                func_801144A0(wp, face, 4);
                wp->anim_AC   = 0x15;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->u_8.byte[1] == 0x13)
            {
                switch (scene->value_10)
                {
                    case 0xF:
                        func_801144A0(wp, face, 0x13);
                        break;
                    case 0x1E:
                        func_801144A0(wp, face, 2);
                        break;
                    case 0x28:
                        func_801144A0(wp, face, 0x13);
                        break;
                    case 0x37:
                        func_801144A0(wp, face, 2);
                        break;
                    case 0x50:
                        func_801144A0(wp, face, 0x13);
                        break;
                    case 0x78:
                        func_801144A0(wp, face, 2);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 1)
            {
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 2);
                wp->anim_AC   = 0x16;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 0xA)
            {
                func_80114478(wp, face, 0xE);
                func_801144A0(wp, face, 0x13);
            }
            if (wp->value_A4 == 0xE)
            {
                wp->anim_AC      = 0x16;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xE;
                wp->routine_1++;
            }
            break;
        case 8:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x15)
            {
                switch (scene->value_10)
                {
                    case 0x32:
                        func_80114478(wp, face, 3);
                        func_801144A0(wp, face, 0x15);
                        break;
                    case 0x46:
                        func_80114478(wp, face, 0x11);
                        func_801144A0(wp, face, 0x16);
                        face->value_2 = 0xE;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 9:
            if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 0x78)
            {
                func_80114478(wp, face, 7);
                func_801144A0(wp, face, 5);
            }
            else if (scene->u_8.byte[1] == 0x16 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x17;
                face->value_2 = 0;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 6);
                wp->routine_1++;
            }
            break;
        case 10:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 0x69)
            {
                func_801144A0(wp, face, 0x11);
                wp->routine_1++;
            }
            break;
        case 11:
            if (wp->value_A4 == 8)
            {
                wp->anim_AC      = 0x17;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 8;
                func_801144A0(wp, face, 6);
                wp->routine_1++;
            }
            break;
        case 12:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x78:
                    func_801144A0(wp, face, 0x11);
                    break;
                case 0xBE:
                    func_801144A0(wp, face, 6);
                    break;
                case 0xD2:
                    func_801144A0(wp, face, 0x11);
                    break;
                case 0x104:
                    func_801144A0(wp, face, 6);
                    break;
                case 0x118:
                    func_80114478(wp, face, 8);
                    func_801144A0(wp, face, 0x17);
                    wp->routine_1++;
                    break;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 0x122)
            {
                func_801144A0(wp, face, 7);
            }
            else if (scene->u_8.byte[1] == 0x18 && scene->value_10 == 1)
            {
                wp->anim_AC              = 0x18;
                face->value_2            = 0;
                wp->u_F8.part[4].value_0 = 0x14;
                wp->u_F8.part[7].value_0 = 0x15;
                func_80114478(wp, face, 9);
                func_801144A0(wp, face, 9);
                wp->routine_1++;
            }
            break;
        case 14:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x19 && scene->value_10 == 5)
            {
                wp->routine_1++;
            }
            break;
        case 15:
            if (scene->u_8.byte[1] == 0x1D && scene->value_10 == 5)
            {
                wp->anim_AC   = 0x19;
                face->value_2 = 0;
                func_80114478(wp, face, 0xA);
                func_801144A0(wp, face, 0xA);
                wp->routine_1++;
            }
            break;
        case 16:
            if (scene->u_8.byte[1] == 0x20)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        wp->anim_AC   = 0x1A;
                        face->value_2 = 0;
                        func_80114478(wp, face, 0x12);
                        func_801144A0(wp, face, 0x18);
                        break;
                    case 0x28:
                        func_801144A0(wp, face, 0xB);
                        break;
                    case 0x3C:
                        func_801144A0(wp, face, 0x18);
                        break;
                    case 0x55:
                        func_801144A0(wp, face, 0xB);
                        break;
                }
            }
            break;
    }
    func_801144C8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x32, 0x200, 0);
    }
}

void func_80113E04(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    wp->anim_AC              = 0x1A;
    wp->anim_prev_AD         = 0xFF;
    wp->value_78             = 0;
    face->shadow_12          = 1;
    face->value_2            = 0;
    wp->u_F8.part[4].value_0 = 0x14;
    wp->u_F8.part[7].value_0 = 0x15;
    func_80114478(wp, face, 0xB);
    func_801144A0(wp, face, 0xC);
    func_801144C8(wp, face);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0++;
    func_800322A8(wp, wp->anim_AC, face->value_2);
}

void func_80113EE8(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x1B;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x1C;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0xA0)
            {
                wp->anim_AC = 0x1D;
                func_80114478(wp, face, 0x13);
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                func_801144A0(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 4:
            wp->anim_AC   = 0x1E;
            face->value_2 = 0;
            wp->routine_1++;
            break;
        case 5:
            if (scene->u_8.byte[1] == 6)
            {
                switch (scene->value_10)
                {
                    case 0xC8:
                        func_80114478(wp, face, 0x10);
                        func_801144A0(wp, face, 0x19);
                        break;
                    case 0xE6:
                        func_80114478(wp, face, 0xC);
                        func_801144A0(wp, face, 0xD);
                        break;
                    case 0xFA:
                        func_801144A0(wp, face, 0x19);
                        break;
                    case 0x113:
                        func_801144A0(wp, face, 0xD);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 7 && scene->value_10 == 1)
            {
                wp->anim_AC              = 0x1F;
                face->value_2            = 0;
                wp->u_F8.part[4].value_0 = 4;
                wp->u_F8.part[7].value_0 = 7;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 4);
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0xA)
            {
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->value_10 == 0x32)
            {
                func_801144A0(wp, face, 0x13);
            }
            else if (scene->value_10 == 0x41)
            {
                func_801144A0(wp, face, 4);
                wp->routine_1++;
            }
            break;
        case 8:
            wp->anim_AC   = 0x20;
            face->value_2 = 0;
            wp->routine_1++;
            break;
        case 9:
            if (scene->u_8.byte[1] == 0xA && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x21;
                face->value_2 = 0;
                func_80114478(wp, face, 0xD);
                func_801144A0(wp, face, 0xE);
                wp->routine_1++;
            }
            break;
        case 10:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xA)
            {
                if (scene->value_10 == 0xA)
                {
                    func_80114478(wp, face, 6);
                    func_801144A0(wp, face, 0x1A);
                }
                else if (scene->value_10 == 0x1E)
                {
                    func_801144A0(wp, face, 0xF);
                }
                else if (scene->value_10 == 0x3C)
                {
                    func_801144A0(wp, face, 0x1A);
                    wp->routine_1++;
                }
            }
            break;
        case 11:
            if (wp->value_A4 == 0xD)
            {
                wp->anim_AC              = 0x21;
                wp->u_F8.part[7].value_0 = 0x16;
                face->value_2            = 0xD;
                wp->routine_1++;
            }
            break;
        case 12:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xA && scene->value_10 == 0x55)
            {
                func_801144A0(wp, face, 0xF);
            }
            else if (scene->u_8.byte[1] == 0xB && scene->value_10 == 1)
            {
                wp->u_F8.part[7].value_0 = 7;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 0x10);
                wp->routine_1++;
            }
            break;
        case 13:
            if (wp->value_A4 == 0x12)
            {
                wp->routine_1++;
            }
            break;
        case 14:
            Obj_pos_set(wp, 0x200, 0, 0);
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 15:
            Obj_pos_set(wp, 0x200, 0, 0);
            wp->anim_AC   = 1;
            face->value_2 = 0;
            wp->routine_1++;
            break;
        case 16:
            Obj_pos_set(wp, 0x200, 0, 0);
            if (wp->value_A4 == 3 || wp->value_A4 == 0xB)
            {
                Sound_call2(0x91, &wp->position);
            }
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 17:
            break;
    }
    func_801144C8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x32, 0x200, 0);
    }
}

void func_80114478(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8013258C[index];
}

void func_801144A0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_801325DC[index];
}

void func_801144C8(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x2A, 0x33, 6));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x2A, 0x33, 6));
    }
    face->prev_10 = face->shape_F;
}

void func_80114610(STAGE_OBJ *wp, STAGE_FACE *face)
{
    STAGE_PL_VIEW *pl = &STAGE_PL;

    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    pl->value_168 = face->prev_D = face->shape_C = face->mouth_4[face->index_E];
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    pl->value_169 = face->prev_10 = face->shape_F = face->eyes_8[face->index_11];
}

#ifdef __wasm32__
void func_80114A7C(STAGE_OBJ *wp, STAGE_FACE *face);
#endif

void func_801146D8(ST1A_OBJ *wp)
{
    STAGE_FACE *face;
    STAGE_SCENE_WORK *scene;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = (STAGE_FACE *)&wp->face;
    switch (wp->routine_0)
    {
        case 0:
            func_80114A7C(wp, face);
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x1B && scene->value_10 == 5)
            {
                func_80114B48(wp, face, 2);
                wp->routine_0++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0x1B)
            {
                switch (scene->value_10)
                {
                    case 0x64:
                        func_80114B20(wp, face, 1);
                        // fall through
                    case 0x1E:
                        func_80114B48(wp, face, 2);
                        break;
                    case 0xD7:
                        func_80114B20(wp, face, 0);
                        // fall through
                    case 0x14:
                    case 0x32:
                        func_80114B48(wp, face, 0);
                        break;
                    case 0x3C:
                    case 0xFA:
                        func_80114B20(wp, face, 3);
                        break;
                }
            }
            if (scene->u_8.byte[1] == 0x1D && scene->value_10 == 1)
            {
                func_80114B20(wp, face, 2);
                func_80114B48(wp, face, 1);
                wp->routine_0++;
            }
            break;
        case 3:
            if (scene->value_10 == 0x19)
            {
                wp->anim_AC   = 2;
                face->value_2 = 0;
                func_80114B48(wp, face, 3);
                wp->routine_0++;
            }
            break;
        case 4:
            if (wp->value_A4 == 0xF)
            {
                face->value_2 = 0xF;
                wp->routine_0++;
            }
            break;
        case 5:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x82:
                    func_80114B48(wp, face, 3);
                    wp->routine_0++;
                    break;
                case 0x5F:
                    func_80114B48(wp, face, 1);
                    break;
                case 0x6E:
                    func_80114B20(wp, face, 4);
                    break;
            }
            break;
        case 6:
            switch (scene->value_10)
            {
                case 0x91:
                    func_80114B48(wp, face, 1);
                    break;
                case 0xA0:
                    func_80114B48(wp, face, 3);
                    break;
                case 0xC6:
                    func_80114B48(wp, face, 1);
                    wp->routine_0++;
                    break;
                case 0xF0:
                    func_80114B20(wp, face, 4);
                    break;
            }
            break;
        case 7:
            break;
    }
    func_80114B70(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80114A7C(STAGE_OBJ *wp, STAGE_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->anim_AC        = 1;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->value_2      = 0;
    func_80114B20(wp, face, 0);
    func_80114B48(wp, face, 0);
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80114B20(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_801326B4[index];
}

void func_80114B48(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_801326C8[index];
}

void func_80114B70(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x3F)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x3F)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_80114CB8(ST1A_OBJ *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face;
    D_801326D8[wp->routine_0](wp, &Scene_work, face);
    func_80115828(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
}

void func_80114DD8(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 1;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    talk->face.timer_0 = 0;
    talk->face.value_2 = 0;
    talk->b.value_12   = 0;
    func_801157D8(wp, &talk->face, 0);
    func_80115800(wp, &talk->face, 0);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0++;
}

void func_80114E90(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0 && scene->value_10 == 0xA)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 0x14:
                        func_80115800(wp, &talk->face, 0xB);
                        wp->anim_AC        = 2;
                        talk->face.value_2 = 0;
                        break;
                    case 0x28:
                        func_80115800(wp, &talk->face, 0);
                        break;
                    case 0x2D:
                        func_80115800(wp, &talk->face, 0xB);
                        break;
                    case 0x41:
                        func_80115800(wp, &talk->face, 0);
                        break;
                    case 0x122:
                        wp->anim_AC        = 3;
                        talk->face.value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 6);
                func_80115800(wp, &talk->face, 1);
                talk->b.value_12 = 1;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0x28:
                        func_801157D8(wp, &talk->face, 0xB);
                        func_80115800(wp, &talk->face, 0xC);
                        break;
                    case 0x3C:
                        func_80115800(wp, &talk->face, 1);
                        break;
                    case 0x46:
                        func_80115800(wp, &talk->face, 0xC);
                        break;
                    case 0x78:
                        func_80115800(wp, &talk->face, 1);
                        break;
                    case 0xDC:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                    case 0x15E:
                        wp->anim_AC        = 5;
                        talk->face.value_2 = 0;
                        func_801157D8(wp, &talk->face, 6);
                        func_80115800(wp, &talk->face, 0xC);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 4:
            if (wp->value_A4 == 0xE)
            {
                wp->anim_AC        = 5;
                talk->face.value_2 = 0xE;
                wp->routine_1++;
            }
            break;
        case 5:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0x186)
            {
                func_80115800(wp, &talk->face, 1);
            }
            else if (scene->value_10 == 0x1B3)
            {
                func_801157D8(wp, &talk->face, 1);
                func_80115800(wp, &talk->face, 0xC);
                wp->anim_AC        = 5;
                talk->face.value_2 = 0xE;
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->value_10 == 0x1EA)
            {
                func_80115800(wp, &talk->face, 1);
            }
            else if (scene->value_10 == 0x226)
            {
                func_801157D8(wp, &talk->face, 8);
            }
            else if (scene->value_10 == 0x27B)
            {
                func_801157D8(wp, &talk->face, 1);
                func_80115800(wp, &talk->face, 2);
                wp->anim_AC        = 6;
                talk->face.value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (wp->value_A4 >= 7)
            {
                wp->position.x += 10;
                wp->position_fixed.v.x = wp->position.x << 16;
                if (wp->value_A7 == -1)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 8:
            wp->anim_AC        = 7;
            talk->face.value_2 = 0;
            wp->rotation.y     = 0xC00;
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->routine_1++;
            break;
        case 9:
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            if (scene->value_10 == 0x2CE)
            {
                wp->routine_1++;
            }
            break;
        case 10:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 1)
            {
                wp->anim_AC        = 8;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 2);
                func_80115800(wp, &talk->face, 3);
                wp->routine_1++;
            }
            break;
        case 11:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 4)
            {
                if (scene->value_10 == 0xA)
                {
                    func_80115800(wp, &talk->face, 0xD);
                }
                else if (scene->value_10 == 0x32)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 12:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0x50)
            {
                func_80115800(wp, &talk->face, 3);
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC        = 7;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 3);
                func_80115800(wp, &talk->face, 6);
                wp->routine_1++;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC        = 9;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 3);
                func_80115800(wp, &talk->face, 6);
                wp->routine_1++;
            }
            else
            {
                Obj_pos_set(wp, 0xA4, 0, 0);
            }
            break;
        case 14:
            if (scene->u_8.byte[1] == 6)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_80115800(wp, &talk->face, 0xE);
                        break;
                    case 0x37:
                        func_80115800(wp, &talk->face, 6);
                        break;
                    case 0x41:
                        func_80115800(wp, &talk->face, 0xE);
                        break;
                    case 0x4B:
                        func_80115800(wp, &talk->face, 6);
                        break;
                    case 0x11D:
                        func_801157D8(wp, &talk->face, 0xA);
                        func_80115800(wp, &talk->face, 0x10);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 7 && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xA;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 4);
                func_80115800(wp, &talk->face, 7);
                wp->routine_1++;
            }
            break;
        case 15:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0x14)
            {
                wp->routine_1++;
            }
            break;
        case 16:
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0x46)
            {
                func_801157D8(wp, &talk->face, 5);
                func_80115800(wp, &talk->face, 8);
            }
            else if (scene->u_8.byte[1] == 9 && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xB;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 6);
                func_80115800(wp, &talk->face, 9);
                wp->routine_1++;
            }
            break;
        case 17:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 5:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                    case 0x14:
                        func_80115800(wp, &talk->face, 0xF);
                        break;
                    case 0x28:
                        func_80115800(wp, &talk->face, 9);
                        break;
                    case 0x32:
                        func_80115800(wp, &talk->face, 0xF);
                        break;
                    case 0x80:
                        func_80115800(wp, &talk->face, 9);
                        break;
                    case 0xA5:
                        func_80115800(wp, &talk->face, 0xF);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 18:
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 0xF3:
                        func_80115800(wp, &talk->face, 9);
                        break;
                    case 0xFA:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                    case 0x104:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xC;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 7);
                func_80115800(wp, &talk->face, 0xA);
                wp->routine_1++;
            }
            break;
        case 19:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xC)
            {
                if (scene->value_10 == 0x5A)
                {
                    func_801157D8(wp, &talk->face, 0xC);
                }
                else if (scene->value_10 == 0xB9)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 20:
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 0xC8)
            {
                func_801157D8(wp, &talk->face, 0xC);
                wp->routine_1++;
            }
            break;
        case 21:
            break;
    }
}

void func_801157D8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_801327F8[index];
}

void func_80115800(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8013282C[index];
}

void func_80115828(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_80115970(ST1A_OBJ *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face;
    D_80132870[wp->routine_0](wp, &Scene_work, face);
    func_801165FC(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x40, 0x200, 0);
    }
}

#ifdef __wasm32__
void func_801165AC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
void func_801165D4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index);
#endif

void func_80115A90(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 1;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    talk->face.timer_0 = 0;
    talk->face.value_2 = 0;
    talk->b.value_12   = 0;
    func_801165AC(wp, &talk->face, 0);
    func_801165D4(wp, &talk->face, 0);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0++;
}

void func_80115B48(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR pos;

    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0 && scene->value_10 == 0x14)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 1:
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x28:
                        func_801165AC(wp, &talk->face, 0xA);
                        break;
                    case 0x5A:
                        func_801165AC(wp, &talk->face, 0xB);
                        func_801165D4(wp, &talk->face, 9);
                        wp->anim_AC        = 2;
                        talk->face.value_2 = 0;
                        break;
                    case 0xA:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x6E:
                        func_801165AC(wp, &talk->face, 0xB);
                        func_801165D4(wp, &talk->face, 9);
                        break;
                    case 0x96:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0xAA:
                        func_801165AC(wp, &talk->face, 0xB);
                        func_801165D4(wp, &talk->face, 9);
                        break;
                    case 0x107:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x125:
                        wp->anim_AC        = 3;
                        talk->face.value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0;
                talk->b.value_12   = 1;
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A4 == 0x15)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0x15;
                wp->routine_1++;
            }
            break;
        case 4:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 0x9B)
            {
                func_801165AC(wp, &talk->face, 0xC);
                func_801165D4(wp, &talk->face, 0xA);
                wp->routine_1++;
            }
            break;
        case 5:
            if (wp->value_A4 == 0x2A)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0x2A;
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0xB4:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0xC8:
                        func_801165AC(wp, &talk->face, 0xC);
                        func_801165D4(wp, &talk->face, 0xA);
                        break;
                    case 0x136:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x1EA:
                        func_801165AC(wp, &talk->face, 1);
                        func_801165D4(wp, &talk->face, 2);
                        break;
                    case 0x1F4:
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 7:
            switch (scene->value_10)
            {
                case 0x212:
                    func_801165AC(wp, &talk->face, 0xA);
                    break;
                case 0x21C:
                    func_801165AC(wp, &talk->face, 0xC);
                    func_801165D4(wp, &talk->face, 0xA);
                    break;
                case 0x244:
                    func_801165AC(wp, &talk->face, 2);
                    func_801165D4(wp, &talk->face, 3);
                    break;
                case 0x24E:
                    func_801165AC(wp, &talk->face, 8);
                    func_801165D4(wp, &talk->face, 0xB);
                    wp->anim_AC        = 5;
                    talk->face.value_2 = 0;
                    wp->routine_1++;
                    break;
            }
            break;
        case 8:
            if (wp->value_A4 == 0x1F)
            {
                wp->anim_AC        = 5;
                talk->face.value_2 = 0x1F;
                func_801165AC(wp, &talk->face, 3);
                func_801165D4(wp, &talk->face, 3);
                wp->routine_1++;
            }
            break;
        case 9:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0x28F)
            {
                func_801165AC(wp, &talk->face, 3);
                func_801165D4(wp, &talk->face, 4);
                wp->routine_1++;
            }
            break;
        case 10:
            if (wp->value_A4 >= 0x25)
            {
                func_80030058(&fixed, 0xC00, 0xA4, 0, 0);
                func_80030150(&fixed, &pos);
                wp->position.x += pos.x;
                wp->position.z += pos.z;
                wp->position_fixed.v.x += fixed.x;
                wp->position_fixed.v.z += fixed.z;
                if (wp->value_A7 == -1)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 11:
            wp->anim_AC        = 6;
            talk->face.value_2 = 0;
            wp->rotation.y     = 0xC00;
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->routine_1++;
            break;
        case 12:
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            if (scene->value_10 == 0x2CE)
            {
                wp->routine_1++;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xB;
                talk->face.value_2 = 0x14;
                Obj_pos_set(wp, 0x2E, 0, 0);
                wp->routine_1++;
            }
            break;
        case 14:
            Obj_pos_set(wp, 0x2E, 0, 0);
            if (wp->value_A4 == 0x27)
            {
                wp->anim_AC        = 7;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 0xC);
                func_801165D4(wp, &talk->face, 0xA);
                wp->routine_1++;
            }
            break;
        case 15:
            if (wp->value_A4 < 0x28)
            {
                Obj_pos_set(wp, 0x2E, 0, 0);
            }
            if (wp->value_A7 == -1)
            {
                func_801165AC(wp, &talk->face, 4);
                func_801165D4(wp, &talk->face, 8);
                wp->routine_1++;
            }
            break;
        case 16:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x73)
            {
                wp->anim_AC        = 8;
                talk->face.value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 17:
            if (scene->u_8.byte[1] == 3)
            {
                switch (scene->value_10)
                {
                    case 0xA5:
                        func_801165AC(wp, &talk->face, 0xD);
                        func_801165D4(wp, &talk->face, 0xC);
                        break;
                    case 0xB9:
                        func_801165AC(wp, &talk->face, 5);
                        func_801165D4(wp, &talk->face, 5);
                        break;
                    case 0xC8:
                        func_801165AC(wp, &talk->face, 0xD);
                        func_801165D4(wp, &talk->face, 0xC);
                        break;
                    case 0xF0:
                        func_801165AC(wp, &talk->face, 5);
                        func_801165D4(wp, &talk->face, 5);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC        = 6;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 2);
                func_801165D4(wp, &talk->face, 3);
                wp->routine_1++;
            }
            break;
        case 18:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC        = 9;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 6);
                func_801165D4(wp, &talk->face, 6);
                wp->routine_1++;
            }
            else
            {
                Obj_pos_set(wp, 0xA4, 0, 0);
            }
            break;
        case 19:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 7 && scene->value_10 == 0x14)
            {
                func_801165AC(wp, &talk->face, 0xE);
                func_801165D4(wp, &talk->face, 0xD);
                wp->routine_1++;
            }
            break;
        case 20:
            if (scene->u_8.byte[1] == 7)
            {
                switch (scene->value_10)
                {
                    case 0x28:
                        func_801165AC(wp, &talk->face, 6);
                        func_801165D4(wp, &talk->face, 6);
                        break;
                    case 0x3C:
                        func_801165AC(wp, &talk->face, 0xE);
                        func_801165D4(wp, &talk->face, 0xD);
                        break;
                    case 0x5F:
                        func_801165AC(wp, &talk->face, 6);
                        func_801165D4(wp, &talk->face, 6);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xA;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 7);
                func_801165D4(wp, &talk->face, 7);
                wp->routine_1++;
            }
            break;
        case 21:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 0x1E)
            {
                func_801165AC(wp, &talk->face, 0xF);
                func_801165D4(wp, &talk->face, 0xE);
                wp->routine_1++;
            }
            break;
        case 22:
            switch (scene->value_10)
            {
                case 0x49:
                    func_801165AC(wp, &talk->face, 7);
                    func_801165D4(wp, &talk->face, 7);
                    break;
                case 0x64:
                    func_801165AC(wp, &talk->face, 0xF);
                    func_801165D4(wp, &talk->face, 0xE);
                    break;
                case 0x96:
                    func_801165AC(wp, &talk->face, 7);
                    func_801165D4(wp, &talk->face, 7);
                    break;
            }
            break;
    }
}

void func_801165AC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80132A58[index];
}

void func_801165D4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80132A98[index];
}

void func_801165FC(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x2A, 0x40, 6));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x2A, 0x40, 6));
    }
    face->prev_10 = face->shape_F;
}

void func_80116744(STAGE_OBJ *wp)
{
    D_80132AD4[wp->routine_0](wp);
}

// ported from r3_st13 func_80100BAC
void func_80116780(ST1A_STCOM27_WORK_C *wp)
{
    wp->scale.v.x   = 0x200;
    wp->scale.v.y   = 0x200;
    wp->scale.v.z   = 0x200;
    wp->scale.v.pad = 0x4210;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->velocity.z  = 0;
    wp->velocity.y  = 0;
    wp->velocity.x  = 0;
    wp->accel.z     = 0;
    wp->accel.y     = 0;
    wp->accel.x     = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    func_80036478(wp->ctl.track_0, 7, -0x60);
    wp->data_78 = D_80132AE0;
    wp->life_6E = wp->life_max_B0 = D_8009884C[wp->kind_2]->life_8 << 4;
    wp->damage_B2                 = 0;
    wp->jump_74                   = 0;
    wp->ctl.sees_10               = 0;
    wp->ctl.flags_14              = 0;
    wp->ctl.hit_20                = 0;
    wp->ctl.value_24              = 0;
    wp->ctl.kind_30               = 0;
    func_800322A8(wp, 3, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80116874(ST1A_STCOM27_WORK_B *wp)
{
    ST1A_STCOM27_CTL_B *ctl;

    ctl                     = &wp->ctl;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->jump_prev_75        = wp->jump_74;
    func_801169B0(wp);
    if (wp->value_C == 0)
    {
        ctl->sees_10 = 1;
    }
    else
    {
        ctl->sees_10 = func_8003648C(ctl->track_0, wp);
    }
    D_80132AEC[wp->routine_1](wp);
    if (wp->routine_0 != 2)
    {
        func_80116C10(wp);
        func_80116B78(wp);
        if (wp->flags_0 & 2)
        {
            Model_Shadow_Trans(wp, 0x118, 0x200, 0);
        }
    }
}

// ported from r3_st13 func_80100DDC
void func_801169B0(ST1A_STCOM27_WORK_D *wp)
{
    ST1A_STCOM27_CTL_D *ctl;
    sint32 damage;
    sint32 knock;
    sint32 dir;

    ctl = &wp->ctl;
    if (wp->value_D != 0)
    {
        if (!(STAGE_FRAME & 3) && wp->damage_B2 != 0)
        {
            wp->damage_B2--;
        }
        damage = ctl->hit_20 & 0xFFFFFF;
        if (damage != 0)
        {
            knock = 0;
            if (wp->routine_1 == 6)
            {
                Sound_call2(0xA3, &wp->position);
                return;
            }
            wp->life_6E -= damage;
            wp->damage_B2 += damage;
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
            if (wp->life_6E <= 0)
            {
                wp->life_6E = 0;
                knock       = 1;
            }
            else if (wp->damage_B2 >= D_8009884C[wp->kind_2]->value_9 * 16)
            {
                knock = 1;
            }
            if (knock)
            {
                func_800322A8(wp, 0xB, 0);
                wp->damage_B2 = 0;
                ctl->kind_30  = 0;
                dir           = func_80031F84(&wp->position, &ctl->from_28, wp->rotation.y, 0);
                if (dir & 0xFFFF0000)
                {
                    wp->rotation.y = dir;
                }
                else
                {
                    wp->rotation.y = (dir + 0x800) & 0xFFF;
                }
                wp->velocity.x = -0x400;
                wp->velocity.y = -0x100;
                wp->accel.y    = 0x40;
                wp->jump_74    = 1;
                Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
                wp->routine_1 = 6;
                wp->routine_2 = 0;
                wp->velocity.y += wp->accel.y;
            }
        }
    }
}

void func_80116B78(ST1A_STCOM27_WORK *wp)
{
    if (wp->value_D != 0)
    {
        wp->ctl.hit_20 = 0;
        wp->ctl.pos_18 = wp->position;
        wp->ctl.pos_18.y -= 0x80;
        func_800341BC(&wp->ctl.pos_18, 0x80, 0, 0x8000, wp->index_1, &wp->ctl.hit_20, wp->ctl.kind_30 | 0x4080000, 0x800000, 0);
    }
}

void func_80116C10(ST1A_STCOM27_WORK *wp)
{
    ST1A_STCOM27_CTL *ctl;
    sint32 ground;
    wp->ctl.flags_14 = 0;
    ctl              = &wp->ctl;
    if (func_8004B414(wp) & 0xF00)
    {
        wp->ctl.flags_14 |= 1;
    }
    if (wp->jump_74 == 0)
    {
        ground = func_80048E6C(wp);
        if (ground != wp->position_prev.y)
        {
            if (wp->jump_prev_75 == 0)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->ctl.flags_14 |= 4;
            }
        }
        else
        {
            wp->position.y            = ground;
            wp->position_fixed_prev.y = ground << 16; // retail stores the saved copy here
        }
        ctl->flags_14 |= 2;
    }
}

void func_80116D08(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80116D48(wp);
        return;
    }
    func_80116DD0(wp);
}

void func_80116D48(ST1A_VIEW_B *wp)
{
    sint32 change;

    change = 0;
    if (wp->u_C.b[1] != 0)
    {
        change = wp->value_4F0 != 0;
    }
    if (wp->value_6E != wp->value_B0)
    {
        change = 1;
    }
    if (change)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80116DD0(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_801177AC(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80116E10(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80116E50(wp);
        return;
    }
    func_80116EBC(wp);
}

void func_80116E50(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
}

// ported from r3_st13 func_801012E8
#ifdef __wasm32__
void func_801177CC(ST1A_OBJ *wp);
void func_80117868(ST1A_OBJ *wp);
#endif

void func_80116EBC(ST1A_STCOM27_WORK_D *wp)
{
    STCOM_PL_WORK *pl;
    ST1A_STCOM27_CTL_D *ctl;
    sint32 seen;
    sint16 turn;

    pl             = &Player_work;
    ctl            = &wp->ctl;
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x20)) & 0xFFF;
    seen           = func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, pl->rotation.y, 0x800);
    if (wp->flags_6 & 0x80)
    {
        if (ctl->count_38 < 30)
        {
            ctl->count_38++;
        }
    }
    else
    {
        ctl->count_38 = 0;
    }
    if (ctl->timer_36 != 0)
    {
        ctl->timer_36--;
    }
    else if (ctl->count_38 >= 30 && wp->dist_80 <= 0x9C400 && seen)
    {
        if ((rand() & 0xF) < 7)
        {
            func_80117820((STAGE_OBJ *)wp);
        }
        else
        {
            func_80117868((ST1A_OBJ *)wp);
        }
        return;
    }
    if (--ctl->timer_34 == 0)
    {
        if (ctl->sees_10 == 0)
        {
            func_801177CC((ST1A_OBJ *)wp);
            Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
            return;
        }
        ctl->timer_34 = 0x3C;
    }
    turn = wp->rotation.y - wp->rotation_prev.y;
    if (turn < 0)
    {
        turn = -turn;
    }
    if (turn <= 0x10)
    {
        func_801176FC((STAGE_OBJ *)wp, 2);
    }
    else if (wp->rotation.y > wp->rotation_prev.y)
    {
        func_801176FC((STAGE_OBJ *)wp, 7);
    }
    else
    {
        func_801176FC((STAGE_OBJ *)wp, 8);
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    if (wp->value_A4 == 2)
    {
        Sound_call2(0x1B8, &wp->position);
    }
}

void func_801170E0(STAGE_OBJ *wp)
{
    sint32 step;
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x40)) & 0xFFF;
    if (wp->u_4E0.face16.eyes_10 != NULL && (wp->flags_6 & 0x80))
    {
        if (rand() & 1)
        {
            func_80117820(wp);
            return;
        }
        func_801177AC((ST1A_OBJ_B *)wp);
        Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
        return;
    }
    func_80032488(wp);
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
    step = wp->value_A4 == 5;
    if (wp->value_A4 == 0x13)
    {
        step = 1;
    }
    if (step)
    {
        Sound_call2(0x1B7, &wp->position);
    }
}

void func_801171E0(void)
{
}

#ifdef __wasm32__
void func_801173B0(ST1A_OBJ *wp);
#endif

void func_801171E8(ST1A_ACTOR *wp)
{
    STAGE_10C *slot;

    switch (wp->routine_2)
    {
        case 0:
            func_801172D8(wp);
            break;
        case 1:
            slot = Open_SHL_WORK();
            if (slot != NULL)
            {
                slot->flags_0            = 1;
                slot->kind_2             = 5;
                slot->variant_3          = 0;
                slot->value_F            = wp->value_1;
                slot->position           = wp->value_188;
                slot->position_fixed.v.x = slot->position.x << 16;
                slot->position_fixed.v.y = slot->position.y << 16;
                slot->position_fixed.v.z = slot->position.z << 16;
            }
            Sound_call2(0x1BA, &wp->position);
            wp->routine_2++;
            break;
        case 2:
        default:
            func_801173B0(wp);
            break;
    }
}

void func_801172D8(ST1A_ACTOR *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
        return;
    }
    if (wp->value_A4 == 3)
    {
        wp->velocity.v.x = -0x600;
    }
    if (wp->value_A4 == 9)
    {
        wp->velocity.v.x = -0x400;
    }
    if (wp->value_A4 == 0xB)
    {
        wp->velocity.v.x = 0;
    }
    func_80032488(wp);
    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
}

void func_801173B0(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_801177AC(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801173F0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80117430(wp);
        return;
    }
    func_801174B8(wp);
}

void func_80117430(ST1A_VIEW_C *wp)
{
    if (wp->u_A4.b[3] != 0)
    {
        func_800322A8(wp, 0xA, 0);
        wp->value_510 = 0;
        if (rand() & 1)
        {
            wp->u_518.h[1] = 0x20;
        }
        else
        {
            wp->u_518.h[1] = -0x20;
        }
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
        Obj_pos_set(wp, wp->value_44, wp->value_46, wp->value_48);
    }
}

void func_801174B8(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_80117758(wp);
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + wp->value_51A) & 0xFFF;
        func_80032488(wp);
    }
}

void func_8011750C(STAGE_OBJ *wp)
{
    D_80132B08[wp->routine_2](wp);
}

void func_80117548(ST1A_STCOM27_WORK *wp)
{
    STCOM_EFFECT *effect;
    if (wp->jump_74 == 0)
    {
        Sound_call2(0x1BC, &wp->position);
        if (wp->life_6E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0;
                effect->sprite.position = wp->position;
            }
#ifdef __wasm32__
            func_80047148(wp, &wp->position);
#else
            func_80047148(wp, &wp->position, effect);
#endif
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
        }
        else
        {
            func_800322A8(wp, 0xC, 0);
            wp->routine_2++;
        }
    }
    else
    {
        wp->jump_74 = 1;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        wp->velocity.y += wp->accel.y;
        func_80032488(wp);
    }
}

void func_80117658(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 0xDU, 0);
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
}

void func_801176B0(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        wp->rotation.y -= 0x400;
        func_801177AC(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801176FC(STAGE_OBJ *wp, sint32 anim)
{
    if (wp->anim_prev_AD != anim)
    {
        func_800322A8(wp, anim, wp->value_A4);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80117758(ST1A_OBJ *wp)
{
    func_800322A8(wp, 0xF, 0);
    wp->value_514        = 0x3C;
    wp->value_44.half[0] = 0x200;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    wp->routine_1        = 1;
    wp->routine_2        = 0;
}

void func_801177AC(ST1A_OBJ *wp)
{
    wp->value_516 = 0;
    func_80117758(wp);
}

void func_801177CC(ST1A_OBJ *wp)
{
    func_800322A8(wp, 1, 0);
    wp->value_514        = 0x78;
    wp->value_44.half[0] = 0x100;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    wp->routine_1        = 2;
    wp->routine_2        = 0;
}

void func_80117820(STAGE_OBJ *wp)
{
    func_800322A8(wp, 6, 0);
    wp->value_44.words.fraction = 0;
    wp->value_44.words.integer  = 0;
    wp->value_4C.words.integer  = 0;
    wp->routine_1               = 4;
    wp->routine_2               = 0;
}

void func_80117868(ST1A_OBJ *wp)
{
    func_800322A8(wp, 9, 0);
    wp->value_510        = D_8009884C[wp->kind_2]->value_A | 0x1000000;
    wp->value_516        = 0x3C;
    wp->value_44.half[0] = 0x400;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    Sound_call2(0x1B9, &wp->position);
    wp->routine_1 = 5;
    wp->routine_2 = 0;
}

void func_801178F0(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80117910(STAGE_FACE2 *face, sint32 index)
{
    face->shape_8 = 0;
    face->mouth_0 = D_80132B2C[index];
    face->prev_9  = 0;
}

void func_80117930(STAGE_FACE2 *face, sint32 index)
{
    face->index_A = 0;
    face->eyes_4  = D_80132BAC[index];
    face->shape_B = 0;
}

void func_80117950(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (face->prev_9 == 0)
    {
        if (face->mouth_0[face->shape_8] != 0x7E)
        {
            if (face->mouth_0[face->shape_8] == 0x7F)
            {
                face->shape_8 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0xE000D, Model_uv_cell(face->mouth_0[face->shape_8], 0x3E, 0x3A, 4));
            face->prev_9 = face->mouth_0[face->shape_8 + 1];
            face->shape_8 += 2;
        }
    }
    else
    {
        face->prev_9--;
    }
    if (face->shape_B == 0)
    {
        if (face->eyes_4[face->index_A] != 0x7E)
        {
            if (face->eyes_4[face->index_A] == 0x7F)
            {
                face->index_A = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->eyes_4[face->index_A], 0x3E, 0x3A, 4));
            face->shape_B = face->eyes_4[face->index_A + 1];
            face->index_A += 2;
        }
    }
    else
    {
        face->shape_B--;
    }
}

void func_80117AB4(STAGE_OBJ *wp, void *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->value_78       = 0;
}

void func_80117B0C(STAGE_OBJ *wp, void *face)
{
    func_80117AB4(wp, face);
    wp->routine_0++;
    func_80118138(wp, face);
}

void func_80117B58(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (wp->routine_1 == 0)
    {
        func_80117910(face, 0);
        func_80117930(face, 0);
        func_800322A8(wp, 0x11, 0);
        wp->routine_1++;
    }
}

void func_80117BCC(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x11, 0);
            wp->routine_1++;
            break;
        case 1:
            func_80032488(wp);
            wp->routine_1++;
            break;
        case 3:
            func_80117930(face, 9);
            func_80117910(face, 5);
            wp->routine_1++;
            // fall through
        case 4:
            func_80032488(wp);
            break;
        case 5:
            break;
    }
}

void func_80117C8C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_80117930(face, 1);
            func_80117910(face, 1);
            func_800322A8(wp, 0x12, 0);
            wp->routine_1++;
            break;
        case 1:
        case 3:
            func_80032488(wp);
            break;
        case 2:
            wp->rotation.y = 0;
            func_800322A8(wp, 0x13, 0);
            wp->routine_1++;
            break;
    }
    switch (Scene_work.value_10)
    {
        case 0x32:
            func_80117930(face, 4);
            break;
        case 0x78:
            func_80117930(face, 1);
            break;
    }
}

void func_80117D98(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x14, 0);
            wp->routine_1++;
            break;
        case 1:
        case 3:
            func_80032488(wp);
            break;
        case 2:
            func_800322A8(wp, 0, 0);
            wp->routine_1++;
            break;
    }
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 2);
            func_80117930(face, 5);
            break;
        case 0x96:
            func_80117930(face, 2);
            break;
    }
}

void func_80117E8C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_80032488(wp);
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 1);
            func_80117930(face, 4);
            break;
        case 0x78:
            func_80117930(face, 1);
            break;
        case 0x82:
            func_80117930(face, 4);
            break;
        case 0xBE:
            func_80117930(face, 1);
            break;
    }
}

void func_80117F2C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_80032488(wp);
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 1);
            func_80117930(face, 1);
            break;
        case 0x28:
            func_80117930(face, 4);
            break;
        case 0x6E:
            func_80117930(face, 1);
            break;
        case 0x78:
            func_80117930(face, 4);
            break;
        case 0xE6:
            func_80117930(face, 1);
            break;
        case 0x104:
            func_80117930(face, 4);
            break;
        case 0x17C:
            func_80117930(face, 1);
            break;
    }
}

void func_8011801C(STAGE_OBJ *wp)
{
    func_80032488(wp);
}

void func_8011803C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x15, 0);
            wp->routine_1++;
            break;
        case 1:
            func_80032488(wp);
            break;
        case 2:
            break;
    }
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 3);
            func_80117930(face, 3);
            break;
        case 0x14:
            func_80117930(face, 6);
            break;
        case 0x28:
            func_80117930(face, 3);
            break;
        case 0x3C:
            func_80117930(face, 6);
            break;
        case 0x91:
            func_80117930(face, 3);
            break;
    }
}

void func_80118138(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (D_80132BD4[Scene_work.u_8.byte[1]] != NULL)
    {
        wp->position_prev           = wp->position;
        wp->position_fixed_prev.x   = wp->position_fixed.v.x;
        wp->position_fixed_prev.y   = wp->position_fixed.v.y;
        wp->position_fixed_prev.z   = wp->position_fixed.v.z;
        wp->position_fixed_prev.pad = wp->position_fixed.v.pad;
        wp->rotation_prev           = wp->rotation;
        D_80132BD4[Scene_work.u_8.byte[1]](wp, face);
        func_80117950(wp, face);
        Model_Shadow_Trans(wp, 0x64, 0x200, 0);
    }
}

void func_80118234(STAGE_OBJ *wp)
{
    D_80132C18[wp->routine_0](wp, &wp->u_4E0.face);
}

void func_80118270(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_80117AB4(wp, face);
    ST1A_FACE_SCRIPTS(face, 4, 7);
    func_800322A8(wp, 0x16, 0);
    wp->routine_0++;
}

void func_801182DC(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (STAGE_SCENE_BYTE(4) == 1)
    {
        switch (Scene_work.value_10)
        {
            case 0x46:
            case 0x73:
                func_80117930(face, 8);
                break;
            case 0x64:
            case 0xAF:
                func_80117930(face, 7);
                break;
            case 0xE6:
                STAGE_SCENE_BYTE(6)++;
                break;
        }
    }
    func_80032488(wp);
}

void func_801183A4(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    D_80132C20[wp->routine_0](wp, &wp->u_4E0.face);
    func_80117950(wp, face);
}

void func_80118404(STAGE_OBJ *wp)
{
    D_80132C28[wp->variant_3](wp, &wp->u_4E0.face);
}

#ifdef __wasm32__
void func_80119114(ST1A_OBJ *wp, ST1A_FACE *face);
#endif

void func_80118440(ST1A_OBJ *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face;
    D_80132C30[wp->routine_0](wp, &Scene_work, face);
    func_80119114(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    }
}

#ifdef __wasm32__
void func_801190C4(ST1A_OBJ *wp, ST1A_FACE *face, sint32 index);
void func_801190EC(ST1A_OBJ *wp, ST1A_FACE *face, sint32 index);
#endif

void func_80118560(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->timer_0      = 0;
    face->value_2      = 0;
    func_801190C4(wp, face, 0);
    func_801190EC(wp, face, 0);
    if (wp->variant_3 == 0)
    {
        wp->scale.v.pad = 0x421;
        wp->anim_AC     = 1;
        face->shadow_12 = 0;
        wp->routine_0   = 1;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
        wp->anim_AC     = 0;
        face->shadow_12 = 1;
        wp->routine_0   = 2;
    }
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80118638(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x3C)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            face->timer_0++;
            wp->scale.v.pad = ((face->timer_0 >> 3) + 1) * 0x421;
            if (wp->scale.v.pad == 0x4210)
            {
                face->timer_0 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0x1E)
            {
                func_801190C4(wp, face, 8);
            }
            else if (scene->u_8.byte[1] == 0xA && scene->value_10 == 0xA)
            {
                func_801190C4(wp, face, 9);
                func_801190EC(wp, face, 9);
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 0xB && scene->value_10 == 0x1E)
            {
                wp->anim_AC   = 2;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                face->shadow_12 = 1;
                wp->position.z -= 0x100;
                wp->position_fixed.v.z = wp->position.z << 16;
            }
            if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 3;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 0xD && scene->value_10 == 1)
            {
                wp->anim_AC   = 4;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->u_8.byte[1] == 0xD)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x69:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x7D:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xC0:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0xD2:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xEB:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x104:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x14D:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x16D:
                        func_801190C4(wp, face, 3);
                        func_801190EC(wp, face, 0xB);
                        break;
                    case 0x17C:
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x1AE:
                        func_801190EC(wp, face, 3);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xF && scene->value_10 == 1)
            {
                func_801190C4(wp, face, 4);
                func_801190EC(wp, face, 4);
            }
            else if (scene->u_8.byte[1] == 0x10 && scene->value_10 == 1)
            {
                func_801190C4(wp, face, 3);
                func_801190EC(wp, face, 5);
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 0x10)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x23:
                        func_801190EC(wp, face, 5);
                        break;
                    case 0x50:
                        func_801190C4(wp, face, 5);
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x64:
                        func_801190EC(wp, face, 3);
                        break;
                    case 0x82:
                        func_801190C4(wp, face, 5);
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0xB4:
                        func_801190EC(wp, face, 3);
                        break;
                    case 0xC8:
                        func_801190C4(wp, face, 6);
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x122:
                        func_801190EC(wp, face, 6);
                        break;
                    case 0x12C:
                        wp->anim_AC   = 5;
                        face->value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 8:
            if (scene->u_8.byte[1] == 0x10)
            {
                if (scene->value_10 == 0x140)
                {
                    func_801190C4(wp, face, 4);
                    func_801190EC(wp, face, 0xD);
                }
                else if (scene->value_10 == 0x168)
                {
                    func_801190EC(wp, face, 7);
                }
            }
            else if (scene->u_8.byte[1] == 0x12 && scene->value_10 == 1)
            {
                wp->rotation.y = 0x100;
                func_801190C4(wp, face, 4);
                func_801190EC(wp, face, 4);
                wp->anim_AC   = 4;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 9:
            if (scene->u_8.byte[1] == 0x12)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_801190EC(wp, face, 0xD);
                        break;
                    case 0x78:
                        wp->anim_AC   = 6;
                        face->value_2 = 0;
                        break;
                    case 0xDC:
                        func_801190EC(wp, face, 4);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x14 && scene->value_10 == 1)
            {
                func_801190C4(wp, face, 1);
                func_801190EC(wp, face, 1);
                wp->routine_1++;
            }
            break;
        case 10:
            if (scene->u_8.byte[1] == 0x14)
            {
                switch (scene->value_10)
                {
                    case 0x14:
                        func_801190C4(wp, face, 4);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x87:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x9F:
                        func_801190C4(wp, face, 4);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xFE:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x116:
                        func_801190C4(wp, face, 4);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x1A4:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x1A9:
                        func_801190C4(wp, face, 7);
                        wp->anim_AC   = 7;
                        face->value_2 = 0;
                        break;
                    case 0x1AE:
                        func_801190EC(wp, face, 0xD);
                        break;
                    case 0x217:
                        func_801190EC(wp, face, 4);
                        break;
                    case 0x230:
                        func_801190EC(wp, face, 0xD);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 1)
            {
                wp->rotation.y = 0x400;
                wp->anim_AC    = 4;
                face->value_2  = 0;
                func_801190C4(wp, face, 4);
                func_801190EC(wp, face, 8);
                wp->routine_1++;
            }
            break;
        case 11:
            if (scene->u_8.byte[1] == 0x16)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_801190EC(wp, face, 0xE);
                        break;
                    case 0x28:
                        func_801190EC(wp, face, 8);
                        break;
                    case 0x3C:
                        func_801190EC(wp, face, 0xE);
                        break;
                    case 0x69:
                        func_801190EC(wp, face, 8);
                        break;
                    case 0x78:
                        func_801190EC(wp, face, 0xE);
                        break;
                    case 0xBE:
                        func_801190EC(wp, face, 8);
                        break;
                    case 0xC8:
                        func_801190EC(wp, face, 0xE);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 1)
            {
                wp->rotation.y = 0;
                wp->anim_AC    = 8;
                face->value_2  = 0;
                func_801190C4(wp, face, 1);
                func_801190EC(wp, face, 1);
                wp->routine_1++;
            }
            break;
        case 12:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x18 && scene->value_10 == 0xA)
            {
                wp->routine_1++;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 0x19 && scene->value_10 == 1)
            {
                wp->anim_AC   = 9;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 14:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x1E)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x3C:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x5A:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xDC:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0xFA:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x190:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x19A:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x1D6:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x1F && scene->value_10 == 0xA)
            {
                func_801190C4(wp, face, 0xA);
                func_801190EC(wp, face, 0xA);
                wp->routine_1++;
            }
            break;
        case 15:
            if (scene->u_8.byte[1] == 0x1F && scene->value_10 == 0x14)
            {
                func_801190C4(wp, face, 1);
                func_801190EC(wp, face, 1);
            }
            if (wp->value_A4 == 0x27)
            {
                wp->anim_AC   = 9;
                face->value_2 = 0x27;
                wp->routine_1++;
            }
            break;
        case 16:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x21 && scene->value_10 == 1)
            {
                face->shadow_12 = 0;
                wp->routine_1++;
            }
            break;
        case 17:
            wp->anim_prev_AD = 0xFF;
            break;
    }
}

void func_801190BC(void)
{
}

void func_801190C4(ST1A_OBJ *wp, ST1A_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80132D38[index];
}

void func_801190EC(ST1A_OBJ *wp, ST1A_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80132D64[index];
}

void func_80119114(ST1A_OBJ *wp, ST1A_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0xE000D, Model_uv_cell(face->shape_C, 0x3E, 0x3A, 4));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_F, 0x3E, 0x3A, 4));
    }
    face->prev_10 = face->shape_F;
}

void func_8011925C(ST1A_OBJ *wp)
{
    ST1A_HIT *hit;

    hit = &wp->hit_440;
    D_80132DA0[wp->routine_0](wp);
    if (wp->value_4BA < 2)
    {
        if (Player_work.value_6E <= 0)
        {
            if (!(wp->hit_440.flags_0.word & 0x10200))
            {
                wp->value_4BA = 2;
                wp->value_4B8 = 0x3C;
                Sound_call2(0x1E9, &wp->position);
            }
            wp->hit_440.flags_0.half |= 0x200;
        }
        else
        {
            wp->hit_440.flags_0.half &= ~0x200;
        }
    }
    hit->value_18 = 0;
}

void func_80119320(ST1A_OBJ *wp)
{
    ST1A_BOSS *bp;
    sint32 i;

    bp = (ST1A_BOSS *)&wp->hit_440;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 16; i++)
    {
        wp->part_180[i].pad = 0x4210;
    }
    wp->rotation.x     = 0;
    wp->rotation.z     = 0;
    wp->value_64.value = 0;
    wp->value_44.value = 0;
    wp->value_48.value = 0;
    bp->flags_0        = 0x26;
    bp->value_4        = 0;
    bp->value_8        = 0;
    bp->value_18       = 0;
    bp->value_1C       = 0;
    func_80036478(bp->track_28, 0, -0x60);
    bp->value_C    = 0;
    bp->value_52   = 0;
    bp->value_53   = 0;
    bp->value_54   = 0;
    bp->value_70   = 0;
    bp->value_72   = 0;
    bp->value_73   = 0;
    bp->value_7A   = -1;
    bp->value_78   = 0;
    bp->value_7E   = 0;
    bp->value_7C   = 0;
    bp->value_7D   = 0;
    bp->value_7F   = 0;
    bp->part_58[0] = Open_SHL_WORK();
    if (bp->part_58[0] != NULL)
    {
        bp->part_58[0]->flags_0  = 1;
        bp->part_58[0]->kind_2   = 0x34;
        bp->part_58[0]->value_C  = wp->value_1;
        bp->part_58[0]->value_D  = 5;
        wp->u_F8.part[5].value_3 = -1;
        bp->part_58[0]->value_6 |= 0x20;
    }
    bp->part_58[1] = Open_SHL_WORK();
    if (bp->part_58[1] != NULL)
    {
        bp->part_58[1]->flags_0   = 1;
        bp->part_58[1]->kind_2    = 0x34;
        bp->part_58[1]->value_C   = wp->value_1;
        bp->part_58[1]->value_D   = 0xA;
        wp->u_F8.part[10].value_3 = -1;
        bp->part_58[1]->value_6 |= 0x20;
    }
    bp->part_58[2] = Open_SHL_WORK();
    if (bp->part_58[2] != NULL)
    {
        bp->part_58[2]->flags_0  = 1;
        bp->part_58[2]->kind_2   = 0x34;
        bp->part_58[2]->value_C  = wp->value_1;
        bp->part_58[2]->value_D  = 6;
        wp->u_F8.part[6].value_3 = -1;
        bp->part_58[2]->value_6 |= 0x20;
    }
    bp->part_58[3] = Open_SHL_WORK();
    if (bp->part_58[3] != NULL)
    {
        bp->part_58[3]->flags_0   = 1;
        bp->part_58[3]->kind_2    = 0x34;
        bp->part_58[3]->value_C   = wp->value_1;
        bp->part_58[3]->value_D   = 0xB;
        wp->u_F8.part[11].value_3 = -1;
        bp->part_58[3]->value_6 |= 0x20;
    }
    wp->value_B2 = wp->value_B0 = wp->value_6E = D_8009884C[wp->kind_2]->life_8 << 7;
    wp->value_78                               = 0;
    wp->value_10                               = 0;
    D_80139738.life_0[0]                       = (sint16)(wp->value_6E / 10) * 9;
    D_80139738.life_0[1]                       = (sint16)(wp->value_6E / 10) * 6;
    D_80139738.life_0[2]                       = (sint16)(wp->value_6E / 10) * 4;
    D_80139738.life_0[3]                       = (sint16)(wp->value_6E / 10);
    D_80139738.end_10                          = -1;
    bp->life_74                                = D_80139738.life_0;
    wp->routine_0                              = 1;
    wp->routine_1                              = 0;
    *(uint16 *)&wp->routine_2                  = 0;
    func_800322A8(wp, 0, 0);
    func_8005D620(wp, 0, 0, 0x81, 0x805058);
    func_80119714(wp);
}

void func_80119714(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    sint32 i;

    bp                      = (ST1A_BLOCK *)&wp->hit_440;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    for (i = 0; i < 16; i++)
    {
        wp->part_180[i].pad = 0x4210;
    }
    bp->hit_0.flags_0.h[1] = rand();
    func_8005D4C0();
    wp->u_E.b.byte_E &= 0xF8;
    wp->u_E.b.byte_F &= 0x11;
    if (bp->hit_0.flags_0.half & 4)
    {
        func_8011C260(wp);
    }
    D_80132DAC[wp->routine_1](wp);
    wp->value_78 = D_80132DE4[bp->value_53];
    if (wp->value_78 != 0)
    {
        bp->hit_0.value_C = func_8004B414(wp);
    }
    else
    {
        bp->hit_0.value_C = 0;
    }
    if (bp->hit_0.flags_0.half & 1)
    {
        switch (wp->routine_1)
        {
            case 5:
                if (wp->value_6E > 0 && --bp->value_70 != 0)
                {
                    *(uint16 *)&wp->routine_2 = 0;
                    break;
                }
                // fall through
            case 0:
            case 2:
            case 3:
            case 4:
            case 6:
                if (wp->value_6E > 0)
                {
                    func_8011C080(wp);
                }
                else
                {
                    wp->routine_1 = 7;
                }
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 1:
                wp->routine_1             = 2;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            default:
                wp->routine_1             = 0;
                *(uint16 *)&wp->routine_2 = 0;
                break;
        }
        bp->hit_0.flags_0.half &= ~1;
    }
    if (bp->hit_0.value_A != 0)
    {
        bp->hit_0.value_A--;
    }
    if (bp->value_78 != 0)
    {
        bp->value_78--;
    }
    else
    {
        bp->value_7A = -1;
    }
    if (bp->hit_0.flags_0.half & 0x20)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
    }
    else
    {
        func_80033A28(wp);
        Model_parts_mtx_set_y(wp);
    }
    wp->value_44.half[0] = (wp->position.x - wp->position_prev.x) << 4;
    wp->value_44.half[1] = (wp->position.y - wp->position_prev.y) << 4;
    wp->value_48.half[0] = (wp->position.z - wp->position_prev.z) << 4;
    if ((wp->flags_0 & 2) && wp->part_180[0].pad == 0x4210)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (bp->hit_0.flags_0.half & 2))
    {
        bp->target_38.x = 0;
        if (bp->hit_0.flags_0.half & 0x400)
        {
            bp->target_38.y = -0x200;
        }
        else
        {
            bp->target_38.y = 0x200;
        }
        bp->target_38.z = 0;
        ApplyMatrix(&wp->matrix_240.m, &bp->target_38, &bp->fixed_40);
        bp->hit_0.pos_10.x = wp->part_180[0].x + bp->fixed_40.x;
        bp->hit_0.pos_10.y = wp->part_180[0].y + bp->fixed_40.y;
        bp->hit_0.pos_10.z = wp->part_180[0].z + bp->fixed_40.z;
        func_800341BC(&bp->hit_0.pos_10, 0x68, 0, 0x8000, wp->value_1, &bp->hit_0.value_18, D_80132DF0[bp->value_52] | bp->hit_0.value_8, 0,
                      0);
    }
}

void func_80119AF8(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80119B18(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    ST1A_FLASH *fp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->hit_440.flags_0.half |= 0x20;
            wp->value_490       = -0x60;
            wp->anim_AC         = 0;
            wp->hit_440.value_4 = 0;
            wp->hit_440.value_8 = D_8009884C[wp->kind_2]->value_A;
            wp->value_493       = 0;
            wp->value_492       = 0;
            fp                  = (ST1A_FLASH *)Open_SHL_WORK();
            if (fp != NULL)
            {
                fp->flags_0      = 1;
                fp->kind_2       = 0x33;
                fp->variant_3    = 0xFD;
                fp->size_2C.x    = 0xC8;
                fp->size_2C.y    = 0xC8;
                fp->size_2C.z    = 0xC8;
                fp->size_2C.pad  = 0x700;
                fp->position.y   = 0x10;
                fp->position.z   = 0x10;
                fp->position.pad = 0x500;
                fp->position.x   = 0;
                fp->routine_3    = 0x3C;
                fp->routine_2    = 0;
            }
            // fall through
        case 1:
            wp->value_4C.words.integer = bp->value_50 + func_80048E6C(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 8) >> 16) + wp->value_4C.words.integer, 0);
            if (bp->hit_0.value_4 == 0x3F)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 1) & 0x3F;
            break;
    }
}

void func_80119CA0(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0xD;
            wp->routine_2++;
            bp->hit_0.value_4 = 0;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_B;
            bp->value_53      = 1;
            bp->value_52      = 0;
            if (bp->value_7A <= 0 && !(bp->hit_0.flags_0.h[1] & 3))
            {
                bp->value_7A = 1;
                bp->value_78 = 0x3C;
                Sound_call2(0x1E4, &wp->position);
            }
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0xE;
                wp->routine_2++;
                bp->hit_0.value_4 = 0x10;
                bp->value_50      = -0x100;
                bp->value_52      = 1;
            }
            break;
        case 2:
            wp->rotation.y             = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x100)) & 0xFFF;
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + func_80048E6C(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                wp->anim_AC = 0xF;
                wp->routine_2++;
                bp->value_54      = 0x78;
                bp->value_50      = 0xC0;
                bp->hit_0.value_4 = 0;
                bp->hit_0.value_6 = 0;
                bp->value_52      = 1;
                Sound_call2(0x1D3, &wp->position);
                bp->hit_0.flags_0.half |= 0x400;
            }
            break;
        case 3:
            wp->rotation.y             = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 8)) & 0xFFF;
            wp->value_4C.words.integer = STAGE_PL.value_3AA + bp->value_50 - wp->position.y;
            Obj_pos_set(wp, wp->value_4C.half[0], ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 22) + wp->value_4C.words.integer, 0);
            if (wp->value_4C.half[0] < 0x600)
            {
                wp->value_4C.half[0] += 0x60;
            }
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 2) & 0x3F;
            if (bp->hit_0.value_6 < 0x40)
            {
                bp->hit_0.value_6 += 4;
            }
            if ((bp->hit_0.value_C & 0xF00) || --bp->value_54 < 0)
            {
                wp->anim_AC = 0x10;
                wp->routine_2++;
                bp->hit_0.value_4 = 0x10;
                bp->value_50      = -0x180;
                bp->value_52      = 0;
                bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
                Sound_call2(0x1D4, &wp->position);
            }
            break;
        case 4:
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + func_80048E6C(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half = (bp->hit_0.flags_0.half | 1) & ~0x400;
            }
            break;
    }
}

void func_8011A080(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    sint32 i;
    uint16 c;
    sint16 turn;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC                = 0xD;
            wp->value_64.words.integer = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
            if (wp->value_64.words.integer < 0)
            {
                turn = -0x40;
            }
            else
            {
                turn = 0x40;
            }
            wp->value_64.half[0]       = turn >> 2;
            wp->value_64.words.integer = turn;
            bp->value_50               = 0x60;
            bp->hit_0.value_4          = 0x10;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
            bp->value_53      = 2;
            bp->value_52      = 0;
            bp->hit_0.flags_0.half &= ~2;
            Sound_call2(0x1DC, &wp->position);
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer += wp->value_64.half[0];
            wp->value_4C.words.integer = bp->value_50 + func_80048E6C(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = bp->hit_0.value_4 & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            wp->u_E.b.byte_F |= 2;
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                wp->flags_0 &= ~2;
                bp->hit_0.value_4 = 0xF;
            }
            break;
        case 2:
            if (--bp->hit_0.value_4 >= 0)
            {
                break;
            }
            bp->hit_0.value_4 = 0x10;
            bp->value_50      = -0x60;
            bp->fixed_40.y    = 0xFF3F0000;
            bp->fixed_40.z    = 0x4000000;
            wp->anim_AC       = 0;
            bp->fixed_40.x    = 0;
            wp->flags_0 |= 2;
            wp->routine_2++;
            func_80030150(&bp->fixed_40, &bp->target_38);
            func_8002FFC4(&bp->target_38, &bp->fixed_40, Angle_xz_svector(&bp->target_38, &wp->position_prev) & 0xFFF, 0x3000, 0, 0);
            wp->position         = bp->target_38;
            wp->position_fixed.v = bp->fixed_40;
            wp->rotation.y       = Angle_xz_svector(&wp->position, &Player_work.position) & 0xFFF;
            Sound_call2(0x20B, &wp->position);
            // fall through
        case 3:
            wp->value_4C.words.integer = bp->value_50 + func_80048E6C(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = (0x10 - bp->hit_0.value_4) & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            wp->u_E.b.byte_F |= 2;
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half |= 3;
            }
            break;
    }
}

void func_8011A488(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 6;
            wp->routine_2++;
            bp->value_50      = 0x60;
            bp->hit_0.value_4 = 0;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
            bp->value_53      = 0;
            bp->value_52      = 0;
            bp->value_72[0]   = 0;
            bp->value_72[1]   = 0;
            Sound_call2(0x1D7, &wp->position);
            if (bp->value_7A <= 0)
            {
                bp->value_7A = 1;
                bp->value_78 = 0x3C;
                Sound_call2(0x1E3, &wp->position);
            }
            break;
        case 1:
            wp->rotation.y             = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
            wp->value_4C.words.integer = STAGE_PL.value_3AA + bp->value_50 - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 22) + wp->value_4C.words.integer, 0);
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 2) & 0x3F;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 7;
                wp->routine_2++;
                bp->hit_0.flags_0.half &= ~0x180;
                if (func_8011BD08(wp, 0) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x80;
                }
                if (func_8011BD08(wp, 1) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x100;
                }
                if (bp->hit_0.flags_0.half & 0x180)
                {
                    Sound_call2(0x1D8, &wp->position);
                }
                wp->value_64.words.integer = 0;
                wp->value_64.half[0]       = (bp->hit_0.flags_0.h[1] & 1) ? 2 : -2;
                wp->u_E.b.byte_F |= 0x40;
            }
            func_8011BDD8(wp, 0);
            func_8011BDD8(wp, 1);
            bp->value_72[0]++;
            bp->value_72[1]++;
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer += wp->value_64.half[0];
            if (bp->value_72[0] != 0)
            {
                func_8011BDD8(wp, 0);
                bp->value_72[0]--;
            }
            if (bp->value_72[1] != 0)
            {
                func_8011BDD8(wp, 1);
                bp->value_72[1]--;
            }
            if (wp->value_A7 < 0)
            {
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    bp->slot_68[0]->value_E = 1;
                }
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    bp->slot_68[1]->value_E = 1;
                }
                wp->routine_2++;
                wp->u_E.b.byte_F = (wp->u_E.b.byte_F & ~0x10) | 0x80;
            }
            break;
        case 3:
            if (wp->u_E.b.byte_F & 0x10)
            {
                wp->u_E.b.byte_F &= ~0x10;
                wp->anim_AC = 8;
                wp->routine_2++;
                bp->hit_0.value_4 = 0x10;
                bp->value_50      = -0x180;
            }
            break;
        case 4:
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + func_80048E6C(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011A8A8(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    STCOM_EFFECT *fx;
    sint32 i;
    uint16 c;
    sint16 turn;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0;
            wp->routine_2++;
            bp->hit_0.value_4 = 0x10;
            bp->value_50      = -0x180;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_E;
            bp->value_53      = 0;
            bp->value_52      = 0;
            break;
        case 1:
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + func_80048E6C(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                wp->anim_AC = 0xD;
                wp->routine_2++;
                wp->value_64.words.integer = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
                if (wp->value_64.words.integer < 0)
                {
                    turn = -0x40;
                }
                else
                {
                    turn = 0x40;
                }
                wp->value_64.half[0]       = turn >> 2;
                wp->value_64.words.integer = turn;
                bp->value_53               = 2;
                bp->hit_0.value_4          = 0x10;
                bp->value_50               = 0x60;
                bp->hit_0.flags_0.half &= ~2;
                Sound_call2(0x1DC, &wp->position);
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer += wp->value_64.half[0];
            wp->value_4C.words.integer = bp->value_50 + func_80048E6C(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = bp->hit_0.value_4 & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            wp->u_E.b.byte_F |= 2;
            if (--bp->hit_0.value_4 < 0)
            {
                wp->flags_0 &= ~2;
                wp->routine_2++;
                bp->hit_0.value_4      = 0x40;
                bp->hit_0.value_6      = 0;
                wp->position_fixed.v.y = 0xFFBF0000;
                wp->position_fixed.v.x = 0;
                wp->position_fixed.v.z = 0x4000000;
                func_80030150(&wp->position_fixed.v, &wp->position);
                Sound_call2(0x1DD, &wp->position);
            }
            break;
        case 3:
            if (bp->hit_0.value_4 % 3 == 0)
            {
                Swing_Camera2(++bp->hit_0.value_6, 0x800, 0xC00, &wp->position);
            }
            if (!(bp->hit_0.value_6 & 1))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x1D;
                    fx->variant_3       = 0x42;
                    fx->value_C         = 1;
                    fx->value_D         = 1;
                    fx->timer_E         = 0;
                    fx->sprite.position = wp->position;
                    fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.y = func_80048E6C(wp);
                    fx->sprite.position.z += (rand() & 0xFF) - 0x80;
                }
            }
            if (--bp->hit_0.value_4 >= 0)
            {
                break;
            }
            wp->anim_AC = 0xB;
            wp->flags_0 |= 2;
            wp->routine_2++;
            bp->hit_0.value_4 = 0x10;
            bp->value_50      = -0x100;
            wp->rotation.y    = Angle_xz_svector(&wp->position, &Player_work.position) & 0xFFF;
            wp->u_E.b.byte_F |= 4;
            wp->value_64.words.integer = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
            if (wp->value_64.words.integer < 0)
            {
                turn = -0x80;
            }
            else
            {
                turn = 0x80;
            }
            wp->value_64.words.integer = turn;
            wp->value_64.half[0]       = turn >> 3;
            Sound_call2(0x20A, &wp->position);
            Sound_call2(0x1DE, &wp->position);
            // fall through
        case 4:
            if (bp->hit_0.value_4 % 3 == 0)
            {
                Swing_Camera2(++bp->hit_0.value_6, 0x800, 0xC00, &wp->position);
            }
            if (!(bp->hit_0.value_6 & 3))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x1D;
                    fx->variant_3       = 0x42;
                    fx->value_C         = 1;
                    fx->value_D         = 1;
                    fx->timer_E         = 0;
                    fx->sprite.position = wp->position;
                    fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.y = func_80048E6C(wp);
                    fx->sprite.position.z += (rand() & 0xFF) - 0x80;
                }
            }
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer -= wp->value_64.half[0];
            wp->value_4C.words.integer = bp->value_50 + func_80048E6C(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = (0x10 - bp->hit_0.value_4) & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                bp->hit_0.flags_0.half |= 2;
                wp->u_E.b.byte_F = (wp->u_E.b.byte_F | 8) & ~0x10;
                Sound_call2(0x1DF, &wp->position);
            }
            break;
        case 5:
            if (wp->u_E.b.byte_F & 0x10)
            {
                wp->u_E.b.byte_F &= ~0x10;
                wp->anim_AC = 0xC;
                wp->routine_2++;
                if (bp->value_7A <= 0)
                {
                    bp->value_7A = 1;
                    bp->value_78 = 0x3C;
                    Sound_call2(0x1E8, &wp->position);
                }
            }
            break;
        case 6:
            if (wp->value_A7 < 0)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011B000(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    STCOM_EFFECT *fx;
    sint32 angle;
    sint16 ground;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC       = 1;
            wp->value_490     = -0x60;
            bp->hit_0.value_4 = 0x1E;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
            wp->value_493     = 0;
            wp->value_492     = 0;
            if (func_8011E9E8(&Player_work.position) != 0)
            {
                bp->target_38 = Player_work.position;
            }
            else
            {
                bp->fixed_40.y = 0xFF3F0000;
                bp->fixed_40.x = 0;
                bp->fixed_40.z = 0x4000000;
                func_80030150(&bp->fixed_40, &bp->target_38);
                angle = Angle_xz_svector(&bp->target_38, &Player_work.position) & 0xFFF;
                func_8002FFC4(&bp->target_38, &bp->fixed_40, angle, (Distance_xz(&bp->target_38, &Player_work.position) - 0x100) * 16, 0,
                              0);
            }
            wp->rotation.y       = (wp->rotation.y + Muku(&wp->position, &bp->target_38, wp->rotation.y, 0x800)) & 0xFFF;
            wp->value_4C.half[0] = Distance_xz(&wp->position, &bp->target_38) / (bp->hit_0.value_4 + 2);
            Sound_call2(0x1D5, &wp->position);
            break;
        case 1:
            wp->value_4C.words.integer = (0x10 - bp->hit_0.value_4) << 2;
            bp->hit_0.value_4--;
            Obj_pos_set(wp, wp->value_4C.half[0] * 16, wp->value_4C.words.integer * 16, 0);
            if (wp->value_A7 < 0 && wp->anim_AC != 4 && ++wp->anim_AC == 4)
            {
                bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_C;
                wp->value_492     = 1;
            }
            ground = func_80048E6C(wp);
            if (ground < wp->position.y)
            {
                wp->position_fixed.v.y = ground << 16;
                wp->position.y         = ground;
                wp->anim_AC            = 5;
                wp->routine_2++;
                bp->hit_0.value_4 = 0;
                bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
                bp->value_52      = 0;
                fx                = func_80031618();
                if (fx != NULL)
                {
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 6;
                    fx->flags_0           = 5;
                    fx->value_F           = 2;
                    fx->sprite.position   = wp->position;
                    fx->sprite.position.y = func_80048E6C(wp);
                    Sound_call2(0x1E0, &wp->position);
                    Sound_call2(0x1D6, &wp->position);
                }
            }
            break;
        case 2:
            if (!(bp->hit_0.value_4 & 3))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x1D;
                    fx->variant_3       = 0x41;
                    fx->value_C         = 1;
                    fx->value_D         = 2;
                    fx->timer_E         = 0;
                    fx->sprite.position = wp->position;
                    fx->sprite.position.x += (rand() & 0x1FF) - 0x100;
                    fx->sprite.position.y = func_80048E6C(wp);
                    fx->sprite.position.z += (rand() & 0x1FF) - 0x100;
                    Swing_Camera2(0x1E, 0x800, 0xC00, &fx->sprite.position);
                }
            }
            bp->hit_0.value_4++;
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                bp->hit_0.value_4 = 0xA;
            }
            break;
        case 3:
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011B4B4(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0;
            wp->routine_2++;
            bp->value_50      = -0x180;
            bp->hit_0.value_4 = 0;
            bp->hit_0.value_6 = 0x10;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_D;
            bp->value_53      = 0;
            bp->value_52      = 0;
            wp->u_C.b.byte_C  = 0;
            if (bp->value_7A <= 0)
            {
                bp->value_7A = 1;
                bp->value_78 = 0x3C;
                Sound_call2(0x1E2, &wp->position);
            }
            break;
        case 1:
            wp->value_4C.words.integer = STAGE_PL.value_3AA + bp->value_50 - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 22) + wp->value_4C.words.integer, 0);
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 2) & 0x3F;
            if (--bp->hit_0.value_6 < 0)
            {
                wp->anim_AC = 9;
                wp->routine_2++;
                bp->hit_0.value_4          = 0x15;
                bp->hit_0.value_6          = 7;
                bp->value_72[0]            = 0;
                bp->value_72[1]            = 0;
                wp->value_64.words.integer = 0;
                Sound_call2(0x1D9, &wp->position);
            }
            break;
        case 2:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[5], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            if (bp->hit_0.value_6 == 0)
            {
                func_8011BDD8(wp, 0);
                bp->value_72[0]++;
                if (bp->hit_0.value_4 == 0)
                {
                    wp->routine_2++;
                    bp->hit_0.value_4 = 6;
                    bp->value_72[0] += bp->value_72[0] & 1;
                }
                else
                {
                    bp->hit_0.value_4--;
                }
            }
            else
            {
                bp->hit_0.value_6--;
            }
            break;
        case 3:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[5], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            if (bp->value_72[0] < 0)
            {
                func_8011BDD8(wp, 0);
                bp->value_72[0] -= 4;
            }
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                wp->u_E.b.byte_E |= 2;
                bp->hit_0.flags_0.half &= ~0x80;
                if (func_8011BD08(wp, 0) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x80;
                }
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    Sound_call2(0x1D8, &wp->position);
                }
            }
            break;
        case 4:
            if (wp->u_C.b.byte_C == 2)
            {
                Sound_call2(0x1D9, &wp->position);
                wp->routine_2++;
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    bp->slot_68[0]->value_E = 1;
                }
                bp->hit_0.value_4          = 0x15;
                wp->value_64.words.integer = 0;
            }
            break;
        case 5:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[10], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            func_8011BDD8(wp, 1);
            bp->value_72[1]++;
            if (bp->hit_0.value_4 == 0)
            {
                wp->anim_AC = 0xA;
                wp->routine_2++;
                bp->hit_0.value_4 = 6;
                bp->value_72[1] += bp->value_72[1] & 1;
            }
            else
            {
                bp->hit_0.value_4--;
            }
            break;
        case 6:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[10], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            if (bp->value_72[1] < 0)
            {
                func_8011BDD8(wp, 1);
                bp->value_72[1] -= 4;
            }
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                wp->u_E.b.byte_E |= 1;
                bp->hit_0.flags_0.half &= ~0x100;
                if (func_8011BD08(wp, 1) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x100;
                }
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    Sound_call2(0x1D8, &wp->position);
                }
            }
            break;
        case 7:
            if (wp->u_C.b.byte_C == 4)
            {
                wp->routine_2++;
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    bp->slot_68[1]->value_E = 1;
                }
                wp->anim_AC = 0;
                wp->u_E.b.byte_E |= 4;
                bp->hit_0.value_4 = 8;
            }
            break;
        case 8:
            if (--bp->hit_0.value_4 < 0)
            {
                wp->u_E.b.byte_F &= ~0x10;
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011BA74(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    ST1A_FLASH *fp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->hit_440.flags_0.half |= 0x20;
            wp->value_490       = -0x60;
            wp->anim_AC         = 0;
            wp->hit_440.value_4 = 0;
            wp->hit_440.value_8 = D_8009884C[wp->kind_2]->value_A;
            wp->value_493       = 0;
            wp->value_492       = 0;
            fp                  = (ST1A_FLASH *)Open_SHL_WORK();
            if (fp != NULL)
            {
                fp->flags_0      = 1;
                fp->kind_2       = 0x33;
                fp->variant_3    = 0xFD;
                fp->position.x   = 0xC8;
                fp->position.y   = 0xC8;
                fp->position.z   = 0xC8;
                fp->position.pad = 0x700;
                fp->size_2C.y    = 0x10;
                fp->size_2C.z    = 0x10;
                fp->size_2C.pad  = 0x500;
                fp->size_2C.x    = 0;
                fp->routine_3    = 0x3C;
                fp->routine_2    = 0;
            }
            Sound_fade_start(0x10);
            // fall through
        case 1:
            wp->value_4C.words.integer = bp->value_50 + func_80048E6C(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 8) >> 16) + wp->value_4C.words.integer, 0);
            if (bp->hit_0.value_4 == 0x3F)
            {
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    bp->slot_68[0]->value_E = 1;
                }
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    bp->slot_68[1]->value_E = 1;
                }
                bp->hit_0.flags_0.half &= ~0x180;
                func_8003187C(wp);
                Close_SHL_WORK(bp->part_58[0]);
                Close_SHL_WORK(bp->part_58[1]);
                Close_SHL_WORK(bp->part_58[2]);
                Close_SHL_WORK(bp->part_58[3]);
                Sce_flag_on(0x58);
            }
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 1) & 0x3F;
            break;
    }
}

sint32 func_8011BC80(void)
{
    STAGE_OBJ *op;

    op = func_80031498();
    if (op != NULL)
    {
        op->flags_0            = 1;
        op->kind_2             = 0x13;
        op->value_4            = 2;
        op->variant_3          = 0;
        op->position_fixed.v.y = -0xC10000;
        op->u_E.b.byte_F       = 1;
        op->position_fixed.v.x = 0;
        op->position_fixed.v.z = 0x08FC0000;
        op->rotation.y         = 0;
        func_80030150(&op->position_fixed.v, &op->position);
        op->flags_6 |= 0x20;
        return 0;
    }
    return 1;
}

sint32 func_8011BD08(ST1A_OBJ *wp, sint32 i)
{
    ST1A_BLOCK *bp = (ST1A_BLOCK *)&wp->hit_440;

    bp->slot_68[i] = (ST1A_10C *)Open_SHL_WORK();
    if (bp->slot_68[i] != NULL)
    {
        bp->slot_68[i]->flags_0   = 1;
        bp->slot_68[i]->kind_2    = 0x30;
        bp->slot_68[i]->value_4   = 0;
        bp->slot_68[i]->variant_3 = 0;
        bp->slot_68[i]->value_C   = wp->table_4A0[i].value_1;
        bp->slot_68[i]->value_D   = i;
        bp->slot_68[i]->value_E   = 0;
        bp->slot_68[i]->value_F   = 0;
        return 1;
    }
    return 0;
}

void func_8011BDD8(ST1A_OBJ *wp, uint8 side)
{
    ST1A_BLOCK *bp;
    STCOM23_PACKET *p;
    STCOM_SVECTOR pos;
    sint16 angle;
    sint16 t;
    sint16 dist;
    sint16 dy;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 i;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    for (i = 0; i < 24; i++)
    {
        t = bp->value_72[side];
        if (D_80132DFC[i].start_0 < t && t < D_80132DFC[i].start_0 + 16)
        {
            p     = Billboard_get();
            t     = bp->value_72[side] - D_80132DFC[i].start_0;
            angle = (D_80132DFC[i].angle_4 + t * 24) & 0xFFF;
            dy    = D_80132DFC[i].dy_6 - t * (D_80132DFC[i].dy_6 / 16);
            dist  = D_80132DFC[i].dist_2 - t * (D_80132DFC[i].dist_2 / 16);
            if (t < 16)
            {
                r = (t + 1) * 8;
                g = r;
                b = r;
            }
            else
            {
                r = 0x80;
                g = 0x80;
                b = 0x80;
            }
            pos.x      = bp->part_58[2][side].position.x + ((rsin(angle) * dist) >> 12);
            pos.z      = bp->part_58[2][side].position.z + ((rcos(angle) * dist) >> 12);
            pos.y      = bp->part_58[2][side].position.y + dy;
            p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
            p->xy_8    = (pos.y << 16) + pos.x;
            p->z_10    = pos.z;
            p->uv_C    = 0x3D482040;
            p->uv_1C   = 0x3F40;
            p->uv_24   = 0x3F5F;
            p->uv_14   = 0x2E205F;
            p->size_18 = t + 8;
            p->pad_20  = 0;
        }
    }
}

// Register allocation: the one-pass loop pins the flags load after ai's set, so ai lives 84 insns
// and ties sum's priority; sum, declared first, has the lower pseudo number and wins the tie (t1).
// The loop around the routine stores weights i's reference so i outranks its extended copies.
sint32 func_8011C080(ST1A_OBJ *wp)
{
    sint16 sum;
    ST1A_AI *ai;
    uint8 *tbl;
    sint16 i;
    sint16 acc;
    uint16 flags;
    uint8 c;
    sint32 lt;

    ai = (ST1A_AI *)&wp->hit_440;
    do
    {
        flags = wp->hit_440.flags_0.half;
    } while (0);
    if (!(flags & 0x40))
    {
        wp->hit_440.flags_0.half = flags | 0x40;
        tbl                      = D_80132EBC;
    }
    else
    {
        do
        {
            lt = wp->value_6E < wp->value_B0 >> 1;
        } while (0);
        tbl = D_80132ECC;
        if (!lt)
        {
            tbl = D_80132EC4;
        }
        wp->hit_440.flags_0.half = flags & ~0x40;
    }
    for (sum = 0, i = 0; i < 5; i++)
    {
        if (ai->last_7C == D_80132EDC[i] && ai->count_7D >= 2)
        {
            D_80132ED4[i] = 0;
        }
        else
        {
            c = tbl[i];
            sum += c;
            D_80132ED4[i] = c;
        }
    }
    acc = 0;
    for (i = 0; i < 5; i++)
    {
        acc += tbl[i];
        if (ai->rand_2 % sum < acc)
        {
            break;
        }
    }
    do
    {
        wp->routine_1             = D_80132EDC[i];
        *(uint16 *)&wp->routine_2 = 0;
    } while (0);
    if (wp->routine_1 == 5)
    {
        ai->value_70 = 1;
    }
    if (ai->last_7C == wp->routine_1)
    {
        ai->count_7D++;
    }
    else
    {
        ai->count_7D = 0;
    }
    ai->last_7C = wp->routine_1;
    return 1;
}

sint32 func_8011C260(ST1A_OBJ *wp)
{
    ST1A_DAMAGE *dm;
    sint32 damage;
    sint32 i;

    dm     = (ST1A_DAMAGE *)&wp->hit_440;
    damage = dm->hit_18 & 0xFFFFFF;
    if (damage != 0)
    {
        if (dm->hit_18 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                if (func_80042208() != 0)
                {
                    dm->flags_0 &= ~0xC;
                    wp->value_B2 = 0;
                    wp->value_6E = 0;
                    damage       = D_8009884C[wp->kind_2]->value_9;
                }
                else
                {
                    wp->value_6E = 1;
                }
            }
            if (dm->timer_7A < 0)
            {
                if (wp->value_6E < *dm->life_74)
                {
                    dm->timer_7A = 0;
                    dm->value_78 = 0x3C;
                    dm->life_74++;
                    Sound_call2(0x1E1, &wp->position);
                }
            }
            if (dm->timer_7A < 3)
            {
                if (wp->value_6E < (sint16)(wp->value_B0 / 10) * 7 && !(dm->flags_0 & 0x800))
                {
                    dm->timer_7A = 3;
                    dm->value_78 = 0x3C;
                    dm->flags_0 |= 0x800;
                    Sound_call2(0x1E5, &wp->position);
                }
                else if (wp->value_6E < (sint16)(wp->value_B0 / 10) * 5 && !(dm->flags_0 & 0x1000))
                {
                    dm->timer_7A = 3;
                    dm->value_78 = 0x3C;
                    dm->flags_0 |= 0x1000;
                    Sound_call2(0x1E6, &wp->position);
                }
                else if (wp->value_6E < (sint16)(wp->value_B0 / 10) * 2 && !(dm->flags_0 & 0x2000))
                {
                    dm->timer_7A = 3;
                    dm->value_78 = 0x3C;
                    dm->flags_0 |= 0x2000;
                    Sound_call2(0x1E7, &wp->position);
                }
            }
            if (dm->flags_0 & 8)
            {
                dm->stagger_A += damage;
                if ((dm->hit_18 & 0x20000000) || dm->stagger_A >= D_8009884C[wp->kind_2]->value_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    dm->stagger_A = 0;
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            for (i = 0; i < 16; i++)
            {
                wp->part_180[i].pad = 0x7FFF;
            }
            wp->u_E.b.byte_F |= 2;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_8011C5C4(STAGE_OBJ *wp)
{
    D_80132EE4[wp->routine_0](wp);
    Model_Shadow_Trans(wp, 0x100, 0x200, 0);
}

void func_8011C620(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    wp->flags_0 |= 0x42;
    Model_work_init(wp, NULL);
    func_80033500(wp);
    bp = (ST1A_BLOCK *)&wp->hit_440;
    Mem_clear(bp, &wp->value_520);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_51C      = 0;
    if (STAGE_GAME.value_5B >= 2)
    {
        wp->value_520 = 1;
    }
    else
    {
        wp->value_520 = 0;
    }
    wp->position.y          = -0x33;
    wp->position.x          = 0;
    wp->position.z          = 0x400;
    wp->position_prev       = wp->position;
    wp->position_fixed.v.y  = -0x330000;
    wp->position_fixed.v.x  = 0;
    wp->position_fixed.v.z  = 0x4000000;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->routine_0           = 1;
    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    wp->value_64.value      = 0;
    wp->value_44.value      = 0;
    wp->value_48.value      = 0;
    wp->rotation.y          = 0;
    wp->value_78            = 0;
    wp->value_10            = 0;
    wp->routine_1           = 0;
    bp->value_98            = 1;
    bp->value_9A            = 0;
    bp->value_9B            = 0;
    if (bp->value_98 > 0)
    {
        bp->value_98 = 0;
        func_800322A8(wp, bp->value_9A, bp->value_9B);
    }
    else if (bp->value_98 == 0)
    {
        func_80032488(wp);
    }
}

void func_8011C790(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    func_8011ED6C(wp);
    D_80132EF0[wp->routine_1](wp);
    bp = (ST1A_BLOCK *)&wp->hit_440;
    if (wp->value_4D8 > 0)
    {
        wp->value_4D8 = 0;
        func_800322A8(wp, wp->value_4DA, wp->value_4DB);
    }
    else if (wp->value_4D8 == 0)
    {
        func_80032488(wp);
    }
    func_8011EAFC(wp, bp->value_9C);
}

void func_8011C870(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    ST1A_FLASH *fp;
    STCOM_EFFECT *fx;
    sint32 i;
    sint32 first;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_1)
    {
        case 0:
        default:
            fp = (ST1A_FLASH *)Open_SHL_WORK();
            if (fp != NULL)
            {
                fp->flags_0      = 1;
                fp->kind_2       = 0x33;
                fp->variant_3    = 0xFC;
                fp->position.x   = 0xC8;
                fp->position.y   = 0xC8;
                fp->position.z   = 0xC8;
                fp->position.pad = 0x700;
                fp->routine_3    = 0x20;
                fp->routine_2    = 0;
            }
            Sound_call(0x20C, 0, 0);
            func_8005D4E8();
            bp->count_CE  = 0;
            wp->routine_3 = 0x5A;
            wp->routine_1++;
            break;
        case 1:
            first = bp->count_CE * 3;
            for (i = first; i < first + 3; i++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 2;
                    fx->sprite.position = wp->part_180[i];
                    fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.y += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.z += (rand() & 0xFF) - 0x80;
                }
            }
            if (++bp->count_CE >= 5)
            {
                bp->count_CE = 0;
            }
            // One-pass loops (here and in cases 2-7) weight wp's references so it outranks i for s1.
            do
            {
                if (--wp->routine_3 == 0)
                {
                    wp->routine_1++;
                }
                if (wp->routine_3 == 0xA)
                {
                    Sce_flag_on(0x6C);
                }
            } while (0);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            do
            {
                wp->routine_1++;
            } while (0);
            break;
        case 8:
            break;
    }
}

void func_8011CAB4(ST1A_OBJ *wp)
{
    STAGE_10C *slot;

    switch (wp->routine_2)
    {
        case 0:
        default:
            slot = Open_SHL_WORK();
            if (slot != NULL)
            {
                slot->flags_0      = 1;
                slot->kind_2       = 0x33;
                slot->variant_3    = 0xFC;
                slot->position.y   = 0x10;
                slot->position.z   = 0x10;
                slot->position.pad = 0x500;
                slot->position.x   = 0;
                slot->routine_3    = 0x1E;
                slot->routine_2    = 0;
            }
            wp->routine_3 = 0x1E;
            wp->routine_2++;
            break;
        case 1:
            if (--wp->routine_3 == 0)
            {
                wp->value_4DE = 0;
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            break;
    }
}

void func_8011CB80(ST1A_OBJ *wp)
{
    ST1A_PICK *pick;
    uint32 r;
    uint32 tries;

    tries         = 0;
    pick          = (ST1A_PICK *)&wp->hit_440;
    pick->move_A3 = pick->move_A2;
    pick->move_A2 = pick->move_A1;
    pick->move_A1 = pick->move_A0;
    switch (pick->phase_9E)
    {
        case 0:
            r = rand() & 0xF;
            if (r < 8)
            {
                pick->move_A0 = 2;
                wp->routine_1 = 2;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            else
            {
                pick->move_A0 = 3;
                wp->routine_1 = 3;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            if (wp->value_6E < wp->value_B0 / 2)
            {
                pick->phase_9E = 2;
            }
            else
            {
                pick->phase_9E = 1;
            }
            break;
        case 1:
        retry1:
            r = rand() & 0xF;
            if (r < 2)
            {
                pick->move_A0 = 2;
                wp->routine_1 = 2;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
                if (wp->value_6E < wp->value_B0 / 2)
                {
                    pick->phase_9E = 2;
                }
                else
                {
                    pick->phase_9E = 1;
                }
            }
            else if (r < 3)
            {
                pick->move_A0 = 3;
                wp->routine_1 = 3;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
                if (wp->value_6E < wp->value_B0 / 2)
                {
                    pick->phase_9E = 2;
                }
                else
                {
                    pick->phase_9E = 1;
                }
            }
            else
            {
                if (r < 9)
                {
                    pick->move_A0  = 4;
                    wp->routine_1  = 4;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
                else
                {
                    pick->move_A0  = 5;
                    wp->routine_1  = 5;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
            }
            if (pick->move_A1 == pick->move_A0 && pick->move_A2 == pick->move_A1 && ++tries < 16)
            {
                goto retry1;
            }
            break;
        case 2:
        retry2:
            r = rand() & 0xF;
            if (r < 3)
            {
                pick->move_A0 = 2;
                wp->routine_1 = 2;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
                if (wp->value_6E < wp->value_B0 / 2)
                {
                    pick->phase_9E = 2;
                }
                else
                {
                    pick->phase_9E = 1;
                }
            }
            else
            {
                if (r < 8)
                {
                    pick->move_A0  = 4;
                    wp->routine_1  = 4;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
                else if (r < 10)
                {
                    pick->move_A0  = 5;
                    wp->routine_1  = 5;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
                else
                {
                    pick->move_A0  = 6;
                    wp->routine_1  = 6;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
            }
            if (pick->move_A1 == pick->move_A0 && pick->move_A2 == pick->move_A1 && ++tries < 16)
            {
                goto retry2;
            }
            break;
    }
}

void func_8011CE4C(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    STCOM_EFFECT *fx;
    STCOM_SVECTOR target;
    sint32 turn;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            aim->value_98 = 1;
            aim->value_9A = 1;
            aim->value_9B = 0;
            if (!(rand() & 3))
            {
                Sound_call2(0x1FC, &wp->position);
            }
            Sound_call2(0x1EB, &wp->position);
            wp->routine_2++;
            break;
        case 2:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            wp->position.y += (sint8)D_80132F10[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 2;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                Sound_call2(0x1EC, &wp->position);
                aim->value_98 = 1;
                aim->value_9A = 3;
                aim->value_9B = 0;
                aim->value_9C = 1;
                aim->timer_C8 = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            if (++aim->timer_C8 < 0xA)
            {
                wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x20);
            }
            Obj_pos_set(wp, 0x400, 0, 0);
            if (func_8011E9E8(&wp->position) == 0)
            {
                Sound_call2(0x1ED, &wp->position);
                wp->routine_2++;
            }
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0   = 5;
                fx->kind_2    = 0x1D;
                fx->timer_E   = 1;
                fx->value_D   = 0;
                fx->variant_3 = 0x22;
                if (STAGE_FRAME & 1)
                {
                    fx->sprite.position = wp->part_180[11];
                }
                else
                {
                    fx->sprite.position = wp->part_180[15];
                }
                fx->sprite.position.y = -0x1F;
            }
            break;
        case 5:
            aim->value_98 = 1;
            aim->value_9A = 4;
            aim->value_9B = 0;
            aim->value_9C = 0;
            wp->routine_2++;
            break;
        case 6:
            wp->position.y -= 0xA;
            if (wp->position.y < -0x32)
            {
                wp->position.y = -0x33;
            }
            wp->position_fixed.v.y = wp->position.y << 16;
            target.x               = wp->position.x * 2;
            target.y               = wp->position.y;
            target.z               = wp->position.z * 2 - 0x400;
            turn                   = Muku(&wp->position, &target, wp->rotation.y & 0xFFF, 0x80);
            if (wp->value_A7 < 0 && turn == 0 && wp->position.y == -0x33)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
                break;
            }
            wp->rotation.y += turn;
            break;
        case 7:
            Obj_pos_set(wp, -0x1E0, 0, 0);
            if (func_8011EAC0(&wp->position) != 0)
            {
                wp->routine_2++;
            }
            break;
        case 8:
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

void func_8011D240(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    ST1A_10C *slot;
    STCOM_SVECTOR vec;
    sint32 turn;
    sint32 t;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->count_A4 = 0;
            aim->value_A6 = 0;
            wp->routine_2++;
            break;
        case 1:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 2:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            if (!(rand() & 3))
            {
                Sound_call2(0x200, &wp->position);
            }
            aim->value_98 = 1;
            aim->value_9A = 0x11;
            aim->value_9B = 0;
            wp->routine_2++;
            break;
        case 3:
            if (wp->value_A4 >= 0x10)
            {
                wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
                if (wp->value_A4 == 0x10)
                {
                    Sound_call2(0x1EE, &wp->position);
                    vec.x = aim->target_0.x - wp->position.x;
                    vec.y = aim->target_0.y - wp->position.y;
                    vec.z = aim->target_0.z - wp->position.z;
                    SquareRoot0(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
                    aim->start_A8 = wp->position;
                    aim->timer_C0 = 0;
                    aim->angle_C4 = wp->rotation.y + Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x800);
                    break;
                }
                if (++aim->timer_C0 >= 0x14)
                {
                    aim->count_A4++;
                    if (func_8011EAC0(&wp->position) != 0)
                    {
                        Sound_call2(0x1F0, &wp->position);
                        aim->value_98 = 1;
                        aim->value_9A = 0x12;
                        aim->value_9B = 0;
                        Swing_Camera2(0x28, 0x64, 0xFA0, &wp->position);
                        aim->value_9C = 2;
                        wp->routine_2++;
                    }
                    else if (aim->count_A4 == 2)
                    {
                        Sound_call2(0x1EF, &wp->position);
                        aim->value_98 = 1;
                        aim->value_9A = 0x13;
                        aim->value_9B = 0;
                        Swing_Camera2(0x28, 0x64, 0xFA0, &wp->position);
                        aim->value_9C = 2;
                        wp->routine_2 = 6;
                    }
                    else
                    {
                        Sound_call2(0x1EF, &wp->position);
                        aim->value_98 = 1;
                        aim->value_9A = 0x13;
                        aim->value_9B = 0;
                        Swing_Camera2(0x28, 0x64, 0xFA0, &wp->position);
                        aim->value_9C = 2;
                        wp->routine_2 = 5;
                    }
                }
                t                      = aim->timer_C0;
                wp->position_fixed.v.x = ((aim->target_0.x * t + aim->start_A8.x * (0x14 - t)) / 0x14) << 16;
                wp->position_fixed.v.z = ((aim->target_0.z * t + aim->start_A8.z * (0x14 - t)) / 0x14) << 16;
                wp->position_fixed.v.y = t * (t * 7 << 16) - (t * 140 << 16) - 0x10000;
                wp->position.x         = wp->position_fixed.v.x >> 16;
                wp->position.y         = wp->position_fixed.v.y >> 16;
                wp->position.z         = wp->position_fixed.v.z >> 16;
                break;
            }
            if (func_8011EA54(&Player_work.position) != 0)
            {
                aim->target_0 = Player_work.position;
            }
            else
            {
                aim->dir_B0.x = -Player_work.position.x;
                aim->dir_B0.y = Player_work.position.y;
                aim->dir_B0.z = 0x400 - Player_work.position.z;
                VectorNormalS(&aim->dir_B0, &vec);
                aim->target_0.x = Player_work.position.x + ((vec.x * 25) >> 10);
                aim->target_0.y = Player_work.position.y + ((vec.y * 25) >> 10);
                aim->target_0.z = Player_work.position.z + ((vec.z * 25) >> 10);
            }
            wp->position.y += (sint8)D_80132F20[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->rotation.y += Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            break;
        case 4:
            if (wp->value_A4 < 0x18)
            {
                slot = Open_SHL_WORK();
                if (slot != NULL)
                {
                    slot->flags_0         = 1;
                    slot->kind_2          = 0x33;
                    slot->variant_3       = 0xFF;
                    slot->model_88        = wp->model_88;
                    slot->position_AC     = wp->part_180[15];
                    slot->position_AC.pad = 0xF;
                    slot->matrix_8C       = wp->matrix_420;
                }
            }
            if (func_8011F150((STAGE_OBJ *)wp, -5) != 0 && wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                aim->value_9C = 0;
                wp->routine_2 = 0xF;
            }
            break;
        case 5:
            if (func_8011EA54(&Player_work.position) != 0)
            {
                aim->target_0 = Player_work.position;
            }
            else
            {
                aim->dir_B0.x = -Player_work.position.x;
                aim->dir_B0.y = Player_work.position.y;
                aim->dir_B0.z = 0x400 - Player_work.position.z;
                VectorNormalS(&aim->dir_B0, &vec);
                aim->target_0.x = Player_work.position.x + ((vec.x * 25) >> 10);
                aim->target_0.y = Player_work.position.y + ((vec.y * 25) >> 10);
                aim->target_0.z = Player_work.position.z + ((vec.z * 25) >> 10);
            }
            wp->rotation.y += Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            func_8011F150((STAGE_OBJ *)wp, 0);
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9B = 0x10;
                aim->value_9A = 0;
                wp->routine_2 = 3;
            }
            break;
        case 6:
            aim->target_0.y = -1;
            aim->target_0.x = 0;
            aim->target_0.z = 0x400;
            wp->rotation.y += Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            func_8011F150((STAGE_OBJ *)wp, 0);
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9B = 0x10;
                aim->value_9A = 0;
                wp->routine_2 = 3;
            }
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            break;
        case 15:
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

void func_8011DA38(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    ST1A_DEBRIS *shot;
    STCOM_FIXED_VECTOR dir;
    sint32 turn;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            Sound_call2(0x1F1, &wp->position);
            aim->value_98 = 1;
            aim->value_9A = 5;
            aim->value_9B = 0;
            wp->routine_2++;
            break;
        case 2:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            wp->position.y += (sint8)D_80132F3C[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_A7 < 0)
            {
                Sound_call2(0x1FF, &wp->position);
                Sound_call2(0x1F2, &wp->position);
                aim->value_98 = 1;
                aim->value_9A = 6;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A4 == 2)
            {
                Sound_call2(0x1F3, &wp->position);
            }
            if (wp->value_A4 >= 2 && wp->value_A4 <= 10 && !(wp->value_A4 & 1))
            {
                shot = (ST1A_DEBRIS *)Open_SHL_WORK();
                if (shot != NULL)
                {
                    shot->flags_0   = 1;
                    shot->kind_2    = 0x32;
                    shot->variant_3 = 3;
                    dir.x           = wp->part_180[11].x - wp->position.x;
                    dir.y           = 0;
                    dir.z           = wp->part_180[11].z - wp->position.z;
                    VectorNormalS(&dir, &shot->velocity);
                    shot->position   = wp->part_180[11];
                    shot->position.y = -2;
                }
            }
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 7;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 5:
            if (func_8011F150((STAGE_OBJ *)wp, -5) != 0)
            {
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            break;
        case 6:
        case 7:
        case 8:
            break;
    }
}

void func_8011DCD8(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    ST1A_SIGHT *sight;
    sint32 turn;
    STCOM_FIXED_VECTOR unused; // unused, but retail reserves its 16 bytes

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            aim->value_98 = 1;
            aim->value_9A = 0xF;
            aim->value_9B = 0;
            wp->routine_2++;
            sight = (ST1A_SIGHT *)Open_SHL_WORK();
            if (sight != NULL)
            {
                aim->sight_D8    = sight;
                sight->flags_0   = 1;
                sight->kind_2    = 0x33;
                sight->variant_3 = 1;
                sight->target_B8 = &STAGE_PL.value_3A8;
                sight->owner_D4  = wp;
            }
            break;
        case 2:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0x10;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A4 == 9)
            {
                Sound_call2(0x1FD, &wp->position);
                aim->sight_D8->fire_C = 1;
            }
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            break;
    }
}

void func_8011DE9C(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    STCOM_EFFECT *fx;
    STAGE_10C *slot;
    sint32 i;
    sint32 n;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        case 10:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            i = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (i != 0)
            {
                wp->rotation.y += i;
                break;
            }
            aim->fx_D0 = func_80031618();
            if (aim->fx_D0 != NULL)
            {
                aim->fx_D0->flags_0           = 5;
                aim->fx_D0->kind_2            = 0x1D;
                aim->fx_D0->value_D           = 0x80;
                aim->fx_D0->timer_E           = 1;
                aim->fx_D0->value_F           = 1;
                aim->fx_D0->variant_3         = 3;
                aim->fx_D0->sprite.position.x = (wp->part_180[11].x + wp->part_180[15].x) >> 1;
                aim->fx_D0->sprite.position.y = (wp->part_180[11].y + wp->part_180[15].y) >> 1;
                aim->fx_D0->sprite.position.z = (wp->part_180[11].z + wp->part_180[15].z) >> 1;
            }
            Sound_call2(0x1FE, &wp->position);
            Sound_call2(0x1F7, &wp->position);
            aim->value_98 = 1;
            aim->value_9A = 8;
            aim->value_9B = 0;
            wp->routine_2++;
            aim->count_CC = 0;
            break;
        case 2:
            aim->count_CC++;
            i = rand() & 0x3F;
            for (n = 0; n < 2; n++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x1D;
                    fx->value_D           = 3;
                    fx->timer_E           = 1;
                    fx->variant_3         = 0x22;
                    fx->sprite.position.x = wp->position.x + ((D_800BBCF8[i] << 16) >> 20);
                    fx->sprite.position.y = -0x1F - (rand() & 0x3F);
                    fx->sprite.position.z = wp->position.z + ((D_800BAEB0[i] << 16) >> 20);
                    i                     = (i + 0x15) & 0x3F;
                }
            }
            if (aim->value_E0 != 0 && aim->count_CC == 0x50)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 6;
                    fx->value_F           = 3;
                    fx->sprite.position   = wp->position;
                    fx->sprite.position.y = -1;
                }
            }
            if (wp->value_A4 >= 0x2B)
            {
                if (wp->value_A4 == 0x2B)
                {
                    Sound_call2(0x1F8, &wp->position);
                    slot = Open_SHL_WORK();
                    if (slot != NULL)
                    {
                        slot->flags_0      = 1;
                        slot->kind_2       = 0x33;
                        slot->variant_3    = 0xFC;
                        slot->position.x   = 0xFF;
                        slot->position.y   = 0x10;
                        slot->position.z   = 0x10;
                        slot->position.pad = 0x500;
                        slot->routine_3    = 0x1E;
                        slot->routine_2    = 0;
                    }
                }
                if (wp->value_A4 == 0x30)
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0           = 5;
                        fx->kind_2            = 0x80;
                        fx->variant_3         = 6;
                        fx->value_F           = 3;
                        fx->sprite.position   = wp->position;
                        fx->sprite.position.y = -1;
                    }
                }
                aim->fx_D0->sprite.position.x = (wp->part_180[11].x + wp->part_180[15].x) >> 1;
                aim->fx_D0->sprite.position.y = ((wp->part_180[11].y + wp->part_180[15].y) >> 1) - 0x64;
                aim->fx_D0->sprite.position.z = (wp->part_180[11].z + wp->part_180[15].z) >> 1;
                aim->fx_D0->value_F += 0xA;
                if ((uint8)aim->fx_D0->value_F >= 0xDC)
                {
                    aim->fx_D0->value_F = 0xDC;
                }
                if (STAGE_FRAME & 1)
                {
                    slot = Open_SHL_WORK();
                    if (slot != NULL)
                    {
                        slot->flags_0   = 1;
                        slot->kind_2    = 0x32;
                        slot->variant_3 = 0;
                        slot->position  = aim->fx_D0->sprite.position;
                    }
                }
            }
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            wp->position.y += (sint8)D_80132F58[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_A7 < 0 && aim->count_CC >= 0x5B)
            {
                slot = Open_SHL_WORK();
                if (slot != NULL)
                {
                    slot->flags_0      = 1;
                    slot->kind_2       = 0x33;
                    slot->variant_3    = 0xFC;
                    slot->position.y   = 0x10;
                    slot->position.z   = 0x10;
                    slot->position.pad = 0x3E8;
                    slot->position.x   = 0;
                    slot->routine_3    = 0x1E;
                    slot->routine_2    = 0;
                }
                Sound_call(0x20C, 0, 0);
                aim->value_98 = 1;
                aim->value_9A = 9;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A4 < 8)
            {
                aim->fx_D0->sprite.position.x = (wp->part_180[11].x + wp->part_180[15].x) >> 1;
                aim->fx_D0->sprite.position.y = ((wp->part_180[11].y + wp->part_180[15].y) >> 1) - 0x64;
                aim->fx_D0->sprite.position.z = (wp->part_180[11].z + wp->part_180[15].z) >> 1;
                aim->fx_D0->value_D -= 0x10;
            }
            else if (wp->value_A4 == 8)
            {
                func_80031988(aim->fx_D0);
            }
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xA;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 5:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 6:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 7:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 8:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 9:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 11:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 12:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 13:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 14:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0xE;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 15:
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 16:
            if (func_8011F150((STAGE_OBJ *)wp, -5) != 0)
            {
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            break;
    }
}

void func_8011E9D0(STAGE_OBJ *wp)
{
    wp->routine_0 = 2;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

sint32 func_8011E9E8(STCOM_SVECTOR *pos)
{
    sint32 x;
    sint32 z;
    sint32 nx;

    x = pos->x;
    z = pos->z - 0x400;
    if (x < 0x538 && z < 0x538 && x >= -0x537 && z >= -0x537)
    {
        nx = -x;
        if (z < x + 0x8E5 && z < nx + 0x8E5 && x - 0x8E5 < z)
        {
            if (nx - 0x8E5 < z)
            {
                return 1;
            }
        }
    }
    return 0;
}

sint32 func_8011EA54(STCOM_SVECTOR *pos)
{
    sint32 x;
    sint32 z;
    sint32 nx;

    x = pos->x;
    z = pos->z - 0x400;
    if (x < 0x59C && z < 0x59C && x >= -0x59B && z >= -0x59B)
    {
        nx = -x;
        if (z < x + 0x973 && z < nx + 0x973 && x - 0x973 < z)
        {
            if (nx - 0x973 < z)
            {
                return 1;
            }
        }
    }
    return 0;
}

sint32 func_8011EAC0(STCOM_SVECTOR *pos)
{
    return pos->x * pos->x + (pos->z - 0x400) * (pos->z - 0x400) <= 0xC5C0F;
}

void func_8011EAFC(ST1A_OBJ *wp, sint32 arg)
{
    ST1A_HITS *hits;
    STCOM_SVECTOR v;
    sint32 i;

    hits = (ST1A_HITS *)&wp->hit_440;
    for (i = 0; i < 8; i++)
    {
        ApplyMatrixSV(&(&wp->matrix_240)[D_80132F90[i].part_7].m, (STCOM_SVECTOR *)&D_80132F90[i], &v);
        v.x += wp->part_180[D_80132F90[i].part_7].x;
        v.y += wp->part_180[D_80132F90[i].part_7].y;
        v.z += wp->part_180[D_80132F90[i].part_7].z;
        func_800341BC(&v, D_80132F90[i].radius_6, 0, 0x8000, wp->value_1, &hits->hit_8[i], D_80133020[hits->kind_E0][arg], 0, 0);
    }
    for (i = 8; i < 18; i++)
    {
        ApplyMatrixSV(&(&wp->matrix_240)[D_80132F90[i].part_7].m, (STCOM_SVECTOR *)&D_80132F90[i], &v);
        v.x += wp->part_180[D_80132F90[i].part_7].x;
        v.y += wp->part_180[D_80132F90[i].part_7].y;
        v.z += wp->part_180[D_80132F90[i].part_7].z;
        func_800341BC(&v, D_80132F90[i].radius_6, 0, 0x8000, wp->value_1, &hits->hit_8[i], D_80133040[hits->kind_E0][arg], 0, 0x80);
    }
}

void func_8011ED6C(ST1A_OBJ *wp)
{
    ST1A_HITS *hits;
    sint32 damage;
    sint32 i;
    sint32 unit;

    hits         = (ST1A_HITS *)&wp->hit_440;
    wp->value_B2 = wp->value_6E;
    for (i = 0; i < 18; i++)
    {
        damage = hits->hit_8[i].damage_0 & 0xFFFFFF;
        if (damage != 0)
        {
            break;
        }
    }
    for (i = 0; i < 18; i++)
    {
        hits->hit_8[i].damage_0 = 0;
    }
    if (wp->value_6E < damage)
    {
        if (STAGE_PL.value_6E >= 0)
        {
            STAGE_PL.value_449 = 1;
            wp->value_6E       = 0;
            hits->value_98     = -1;
            wp->routine_1      = 7;
            wp->routine_2      = 0;
            wp->routine_3      = 0;
        }
        else
        {
            wp->value_6E = 0;
        }
    }
    else if (damage != 0)
    {
        Sound_call2(0xA0, &wp->position);
        wp->scale.v.pad = 0x7FFF;
        wp->value_6E -= damage;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    if (wp->value_6E != wp->value_B2)
    {
        unit = wp->value_B0 >> 6;
        if (wp->value_6E <= unit * 6)
        {
            if (!(hits->cried_DC & 1))
            {
                hits->cried_DC |= 1;
                Sound_call2(0x204, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 12)
        {
            if (!((hits->cried_DC >> 1) & 1))
            {
                hits->cried_DC |= 2;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 16)
        {
            if (!((hits->cried_DC >> 2) & 1))
            {
                hits->cried_DC |= 4;
                Sound_call2(0x203, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 19)
        {
            if (!((hits->cried_DC >> 3) & 1))
            {
                hits->cried_DC |= 8;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 25)
        {
            if (!((hits->cried_DC >> 4) & 1))
            {
                hits->cried_DC |= 0x10;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 32)
        {
            if (!((hits->cried_DC >> 5) & 1))
            {
                hits->cried_DC |= 0x20;
                Sound_call2(0x202, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 38)
        {
            if (!((hits->cried_DC >> 6) & 1))
            {
                hits->cried_DC |= 0x40;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 44)
        {
            if (!((hits->cried_DC >> 7) & 1))
            {
                hits->cried_DC |= 0x80;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 48)
        {
            if (!((hits->cried_DC >> 8) & 1))
            {
                hits->cried_DC |= 0x100;
                Sound_call2(0x201, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 51)
        {
            if (!((hits->cried_DC >> 9) & 1))
            {
                hits->cried_DC |= 0x200;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 57)
        {
            if (!((hits->cried_DC >> 10) & 1))
            {
                hits->cried_DC |= 0x400;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
    }
}

sint32 func_8011F150(STAGE_OBJ *wp, sint32 dy)
{
    sint32 landed;

    landed = 0;
    wp->position.y += dy;
    if (wp->position.y < -0x32)
    {
        wp->position.y = -0x33;
        landed         = 1;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    return landed;
}

sint32 func_8011F1AC(STAGE_OBJ *wp, sint32 dy)
{
    sint32 landed;

    landed = 0;
    wp->position.y += dy;
    if (wp->position.y >= -1)
    {
        wp->position.y = -1;
        landed         = 1;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    return landed;
}

void func_8011F208(void)
{
    STAGE_10C *slot;

    slot = Open_SHL_WORK();
    if (slot != NULL)
    {
        slot->flags_0   = 1;
        slot->kind_2    = 0x32;
        slot->variant_3 = 1;
        slot->position  = Player_work.position;
        slot->position.y -= 0x3E8;
    }
}

STAGE_OBJ *func_8011F27C(void)
{
    STAGE_OBJ *op;

    op = func_80031498();
    if (op != NULL)
    {
        op->flags_0    = 1;
        op->kind_2     = 0x16;
        op->position.y = -0x33;
        op->position.z = 0x400;
        op->position.x = 0;
        op->value_4    = 0;
        op->rotation.x = op->rotation.y = op->rotation.z = 0;
        op->value_44.half[0] = op->value_44.half[1] = op->value_48.half[0] = 0;
        op->flags_6 |= 0x20;
        op->position_fixed.v.x  = op->position.x << 16;
        op->position_fixed.v.y  = op->position.y << 16;
        op->position_fixed.v.z  = op->position.z << 16;
        op->position_prev       = op->position;
        op->position_fixed_prev = op->position_fixed.v;
        op->rotation_prev       = op->rotation;
        func_8005D7C0();
        op->life_prev_B2 = op->life_max_B0 = op->life_6E = D_8009884C[op->kind_2]->life_8 << 8;
        func_8005D620(op, 0, 0, 0x81, 0x806468);
        func_8005D4D4();
        return op;
    }
    return NULL;
}

void func_8011F3E0(ST1A_OBJ *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->value_44.value = 0;
            wp->value_48.value = 0;
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x42100200;
            wp->value_78       = 0;
            func_800322A8(wp, 0x14, 0);
            wp->u_C.b.byte_C = 0;
            wp->u_C.b.byte_D = 0;
            wp->u_E.b.byte_E = 0;
            wp->u_E.b.byte_F = 0;
            wp->routine_0++;
            break;
        case 1:
            if (wp->value_44.half[0] != 0)
            {
                Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            }
            if (wp->u_C.b.byte_C == 0)
            {
                func_80032488(wp);
            }
            else
            {
                func_800322A8(wp, wp->u_C.b.byte_D, 0);
                wp->u_C.b.byte_C = 0;
            }
            break;
    }
}
