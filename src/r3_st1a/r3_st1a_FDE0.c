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
    Track_reset(ctl->track_18, 7, -0x60);
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
    ctl->ground_60 = Obj_map_push_out(wp);
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
            Model_pose_unpack(wp);
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
            Pos_Shadow_Trans(&pos, 0x24, 0x200, 0);
        }
    }
}

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
