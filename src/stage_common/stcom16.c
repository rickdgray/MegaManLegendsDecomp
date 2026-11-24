#include "common.h"
#include "stage_common/stcom16.h"

// Shared stage code, linked into 4 stages: r3_st09, r3_st0e, r3_st14 and r3_st1d. Each stage
// compiles this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the
// names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom16"

void stcom16_func_0000(STCOM16_WORK *wp)
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
    stcom16_D_000C[wp->routine_0](wp);
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

void stcom16_func_01D8(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;

    func_8003354C(wp);
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]      = 0x1000100;
    wp->scale.words[1]      = 0x100;
    wp->data_78             = stcom16_D_0000;
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
    Track_set(wp->ctl.track_20, 5, -0x60);
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 << 4;
    ctl                                              = &wp->ctl;
    wp->routine_0                                    = 1;
    if (wp->variant_3 == 0)
    {
        wp->velocity.v.x = 0x50;
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
        wp->velocity.v.x = 0x1E0;
        wp->anim_AC      = 0;
        wp->ctl.timer_3D = 120;
        wp->ctl.count_3C = 0;
    }
    wp->scale.v.pad = 0x4210;
    wp->accel.y     = 0x30;
    func_800322A8(wp, wp->anim_AC, 0);
    ctl->hit_8 = 0;
    stcom16_func_0370(wp);
}

void stcom16_func_0370(STCOM16_WORK *wp)
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
                    wp->velocity.v.x = 0xC0;
                    wp->velocity.v.y = -0xC0;
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
                    if (wp->value_80 > 0x80000)
                    {
                        wp->routine_1 = 1;
                        wp->routine_2 = 0;
                    }
                    else if (wp->value_80 <= 0x1E847 && wp->ctl.timer_3E == 0)
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
                    if (wp->value_80 <= 0x1E847 && wp->ctl.timer_3E == 0)
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
                wp->velocity.v.x = 0x50;
                wp->routine_2    = 0;
                wp->param_F      = 0;
                wp->ctl.timer_3D = 120;
                wp->ctl.count_3C = 0;
                wp->ground.flags_6 &= ~0x81;
            }
        }
    }
    stcom16_D_001C[wp->routine_1](wp);
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
        stcom16_func_27E8(wp);
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
            func_800341BC(&ctl->pos_0, 0x50, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->power_73 | 0x4080000, 0x800000, 0x80);
        }
        else
        {
            ctl->pos_0 = wp->joints_180[0];
            func_800341BC(&ctl->pos_0, 0x50, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->power_73 | 0x4080000, 0x800000, 0);
        }
    }
    else
    {
        ctl->pos_0 = wp->joints_180[0];
        func_800341BC(&ctl->pos_0, 0x50, 0, 0x8000, wp->value_1, &ctl->hit_8, wp->power_73 | 0x4080000, 0x800000, 0);
    }
    if (ground->flags_6 & 2)
    {
        claw.y = 0x4D0;
        claw.x = 0;
        claw.z = -0x20;
        ApplyMatrix(&wp->mats_1E8[2], &claw, &ofs);
        ctl->pos_0.x = wp->joints_180[2].x + ofs.x;
        ctl->pos_0.y = wp->joints_180[2].y + ofs.y;
        ctl->pos_0.z = wp->joints_180[2].z + ofs.z;
        func_800341BC(&ctl->pos_0, 0x28, 0, 0x8000, wp->value_1, ctl->hit_18, ground->value_4 | 0x5080000, 0, 0x80);
        ApplyMatrix(&wp->mats_1E8[4], &claw, &ofs);
        ctl->pos_0.x = wp->joints_180[4].x + ofs.x;
        ctl->pos_0.y = wp->joints_180[4].y + ofs.y;
        ctl->pos_0.z = wp->joints_180[4].z + ofs.z;
        func_800341BC(&ctl->pos_0, 0x28, 0, 0x8000, wp->value_1, ctl->hit_18, ground->value_4 | 0x5080000, 0, 0x80);
    }
    if (wp->variant_3 != 2 && (wp->flags_0 & 2))
    {
        Model_Shadow_Trans(wp, 0xA0, 0x200, 0);
    }
}

void stcom16_func_0C84(STCOM16_WORK *wp)
{
    func_80031824(wp);
}

void stcom16_func_0CA4(STCOM16_WORK *wp)
{
    STCOM16_FADE *fade;

    fade = &wp->fade;
    if (wp->value_80 <= 0x80000 || STCOM_STAGE_ROOM == 0x21D)
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

void stcom16_func_0D60(STCOM16_WORK *wp)
{
    stcom16_D_0040[wp->routine_2](wp);
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

void stcom16_func_0E4C(STCOM16_WORK *wp)
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
        stcom16_func_1128(wp);
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

void stcom16_func_0FB4(STCOM16_WORK *wp)
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

void stcom16_func_103C(STCOM16_WORK *wp)
{
    if (--wp->ctl.timer_3D == 0)
    {
        wp->velocity.v.x = 0x50;
        wp->ctl.timer_3D = 120;
        wp->routine_2    = 0;
        wp->anim_AC      = 1;
        wp->ground.flags_6 &= ~1;
        func_800322A8(wp, 1, 0);
    }
}

void stcom16_func_10A0(STCOM16_WORK *wp)
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

void stcom16_func_10F8(STCOM16_WORK *wp)
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

void stcom16_func_1128(STCOM16_WORK *wp)
{
    if (wp->rotation.y == wp->ctl.angle_38)
    {
        wp->velocity.v.x = 0x50;
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

void stcom16_func_11C4(STCOM16_WORK *wp)
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

void stcom16_func_12D0(STCOM16_WORK *wp)
{
    stcom16_D_005C[wp->routine_2](wp);
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

void stcom16_func_13E0(STCOM16_WORK *wp)
{
    wp->anim_AC = 0;
    func_800322A8(wp, 0, 0);
    wp->ctl.timer_3D = 10;
    wp->stun.timer_6 = 90;
    wp->routine_2    = 1;
    wp->ctl.timer_3F = 1;
}

void stcom16_func_1430(STCOM16_WORK *wp)
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
        wp->velocity.v.x = 0x1E0;
        wp->routine_2    = 2;
        wp->ctl.turn_3A  = 0x10;
    }
}

void stcom16_func_14F8(STCOM16_WORK *wp)
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
            stcom16_func_1668(wp);
        }
    }
    else
    {
        wp->stun.timer_6--;
        if (wp->value_80 <= 0x1387F)
        {
            wp->anim_AC   = 4;
            wp->routine_1 = 2;
            wp->ground.flags_6 |= 2;
            func_800322A8(wp, wp->anim_AC, 0);
            Sound_call2(0x15B, &wp->position);
            wp->ground.value_4 = D_80098844[wp->kind_2]->value_C;
            stcom16_func_1790(wp);
        }
        else
        {
            stcom16_func_11C4(wp);
        }
    }
}

void stcom16_func_1668(STCOM16_WORK *wp)
{
    if (wp->ground.hit_0 & 0xF00)
    {
        wp->velocity.v.x = 0x50;
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
        stcom16_func_1128(wp);
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
        wp->velocity.v.x = 0x50;
    }
}

void stcom16_func_175C(STCOM16_WORK *wp)
{
    if (wp->ctl.timer_3D != 0)
    {
        wp->ctl.timer_3D--;
    }
    else
    {
        wp->routine_1    = 0;
        wp->velocity.v.x = 0x50;
    }
}

void stcom16_func_1790(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;
    STCOM16_GROUND *ground;

    ctl    = &wp->ctl;
    ground = &wp->ground;
    if (wp->value_A6 == 0)
    {
        wp->ctl.turn_3A = 0x20;
        stcom16_func_11C4(wp);
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
            wp->velocity.v.x = 0x50;
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

void stcom16_func_18E4(STCOM16_WORK *wp)
{
    stcom16_D_0070[wp->routine_2](wp);
}

void stcom16_func_1920(STCOM16_WORK *wp)
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

void stcom16_func_19C8(STCOM16_WORK *wp)
{
    if (wp->value_A6 == 2)
    {
        wp->routine_2 = 2;
    }
}

void stcom16_func_19E4(STCOM16_WORK *wp)
{
    wp->ctl.value_4D += 8;
    if (wp->value_A6 == 1)
    {
        wp->routine_2 = 3;
    }
}

void stcom16_func_1A0C(STCOM16_WORK *wp)
{
    wp->ctl.value_4D -= 8;
    if (wp->ctl.value_4D <= 32)
    {
        wp->routine_2 = 4;
        wp->ground.flags_6 &= ~2;
    }
}

void stcom16_func_1A44(STCOM16_WORK *wp)
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

void stcom16_func_1AE0(STCOM16_WORK *wp)
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

void stcom16_func_1BA8(STCOM16_WORK *wp)
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

void stcom16_func_1C94(STCOM16_WORK *wp)
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

void stcom16_func_1DA0(STCOM16_WORK *wp)
{
    STCOM16_GROUND *ground;
    sint32 y;

    ground = &wp->ground;
    stcom16_D_008C[wp->routine_2](wp);
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

void stcom16_func_1F84(STCOM16_WORK *wp)
{
    if (wp->value_A6 == 1)
    {
        wp->velocity.v.y = -0x200;
        wp->routine_2    = 1;
        wp->jump_74      = 1;
        Sound_call2(0x15F, &wp->position);
    }
}

void stcom16_func_1FCC(STCOM16_WORK *wp)
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

void stcom16_func_2068(STCOM16_WORK *wp)
{
    if (wp->flags_A7 == -1)
    {
        wp->anim_AC = 1;
        func_800322A8(wp, 1, 0);
        wp->velocity.v.x = 0x50;
        wp->routine_1    = 0;
        wp->routine_2    = 0;
        wp->param_F      = 0;
        wp->ctl.timer_3D = 120;
        wp->ctl.count_3C = 0;
        wp->ground.flags_6 &= ~3;
    }
}

void stcom16_func_20D8(STCOM16_WORK *wp)
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
                wp->velocity.v.x = 0x50;
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

void stcom16_func_23AC(STCOM16_WORK *wp)
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

void stcom16_func_2434(STCOM16_WORK *wp)
{
    stcom16_D_0098[wp->routine_2](wp);
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

void stcom16_func_2534(STCOM16_WORK *wp)
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

void stcom16_func_25E8(STCOM16_WORK *wp)
{
    stcom16_func_0FB4(wp);
    wp->ctl.timer_3F = 1;
    wp->fade.r_0     = 16;
    wp->fade.g_1     = 16;
    wp->fade.b_2     = 16;
}

void stcom16_func_2628(STCOM16_WORK *wp)
{
    wp->anim_AC = 2;
    func_800322A8(wp, 2, 0);
    wp->routine_2    = 3;
    wp->velocity.v.x = 0x1E0;
    wp->ctl.turn_3A  = 0x10;
    wp->ctl.timer_3F = 15;
    wp->fade.r_0     = 16;
    wp->fade.g_1     = 16;
    wp->fade.b_2     = 16;
}

void stcom16_func_2690(STCOM16_WORK *wp)
{
    STCOM16_CTL *ctl;

    ctl = &wp->ctl;
    if ((wp->ground.hit_0 & 0xF00) || wp->value_80 > 0x200000)
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

void stcom16_func_2748(STCOM16_WORK *wp)
{
    if (wp->rotation.y == wp->ctl.angle_38)
    {
        wp->velocity.v.x = 0x50;
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

void stcom16_func_27E8(STCOM16_WORK *wp)
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
