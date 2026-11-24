#include "common.h"
#include "stage_common/stcom17.h"

// Shared stage code, linked into 4 stages: r3_st0a, r3_st0c, r3_st10 and r3_st11. Each stage
// compiles this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the
// names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom17"

void stcom17_func_0000(STCOM17_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    stcom17_D_000C[wp->routine_0](wp);
    wp->ctl.hit_8 = 0;
}

void stcom17_func_00B0(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    if (STCOM_STAGE_ROOM == 0xA)
    {
        func_8002F9EC(wp, 0);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0] = 0x3000300;
    wp->scale.words[1] = 0x300;
    ctl->flags_4A      = 8;
    ctl->size_28.x     = 2;
    ctl->size_28.y     = 9;
    ctl->turn_44       = 0;
    ctl->hit_8         = 0;
    ctl->value_C       = 0;
    ctl->size_28.z     = 4;
    ctl->timer_50      = 0;
    ctl->timer_53      = 0;
    ctl->value_54      = 0;
    ctl->flags_4E      = 0;
    ctl->timer_48      = 0;
    ctl->timer_49      = 0;
    ctl->damage_40     = 0;
    switch (wp->variant_3)
    {
        case 0:
            break;
        case 1:
            wp->velocity.v.x = 0xA0;
            break;
    }
    ctl->power_42 = 0;
    Track_reset(ctl->track_18, 11, -0x60);
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 << 4;
    wp->anim_AC                                      = 0;
    wp->routine_0                                    = 1;
    wp->scale.v.pad                                  = 0x4210;
    wp->anim_prev_AD                                 = 0;
    wp->routine_1                                    = 0;
    wp->value_74                                     = 0;
    wp->data_78                                      = stcom17_D_0000;
    func_80032304(wp, wp->anim_AC, 0);
    Model_parts_mtx_set_y(wp);
}

void stcom17_func_021C(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;
    STCOM_PL_WORK *pl;
    uint32 damage;
    uint32 dir;
    sint32 held;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (!func_8003648C(wp->ctl.track_18, wp))
    {
        wp->ctl.flags_4A &= ~0x10;
    }
    else
    {
        wp->ctl.flags_4A |= 0x10;
    }
    if (ctl->damage_40 != 0)
    {
        ctl->damage_40--;
    }
    damage = ctl->hit_8 & 0xFFFFFF;
    if (damage != 0)
    {
        wp->life_prev_B2 = wp->life_6E;
        wp->life_6E -= damage;
        if (wp->life_6E <= 0)
        {
            ctl->flags_4A &= ~8;
            wp->routine_1 = 6;
        }
        else
        {
            if (pl->value_76 == 0)
            {
                held = 0;
            }
            else
            {
                held = pl->value_C0 == wp;
            }
            if (!held)
            {
                ctl->damage_40 += damage;
                if (!(ctl->flags_4A & 4) && ctl->damage_40 >= D_80098844[wp->kind_2]->limit_9)
                {
                    ctl->flags_4A |= 4;
                    ctl->damage_40  = 0;
                    ctl->routine_4C = wp->routine_1;
                    wp->routine_1   = 5;
                    dir             = (uint32)func_80031F84(&wp->position, &ctl->target_10, wp->rotation.y, 1) >> 16;
                    switch (dir)
                    {
                        case 0:
                        case 1:
                            wp->routine_2    = dir;
                            ctl->count_4B    = 8;
                            wp->velocity.v.x = 0x8C;
                            break;
                        case 2:
                            wp->routine_2 = 2;
                            wp->anim_AC   = 3;
                            break;
                        case 3:
                            wp->routine_2 = 2;
                            wp->anim_AC   = 2;
                            break;
                    }
                    Sound_call2(0xA2, &wp->position);
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
        }
    }
    if (Scene_work == 0)
    {
        stcom17_D_0018[wp->routine_1](wp);
    }
    func_80032538(wp);
    *(uint16 *)0x1F800132 = ctl->turn_44;
    Model_parts_mtx_set_y(wp);
    if (ctl->flags_4A & 8)
    {
        func_80051B68(wp, 1, -1, 0x1000008);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0xA0, 0x200, 0);
    }
    if (ctl->flags_4A & 8)
    {
        ctl->pos_0.x = wp->joints_180[0].x;
        ctl->pos_0.y = wp->joints_180[0].y - 0x8C;
        ctl->pos_0.z = wp->joints_180[0].z;
        func_800341BC(&ctl->pos_0, 0x118, 0, 0x8000, wp->value_1, &ctl->hit_8, ctl->power_42 | 0x4080000, 0x800000, 0);
    }
}

void stcom17_func_0510(STCOM17_WORK *wp)
{
    func_80031824(wp);
}

void stcom17_func_0530(STCOM17_WORK *wp)
{
    if (!(wp->variant_3 & 0xF0))
    {
        if (wp->ctl.flags_4A & 0x10)
        {
            wp->routine_1 = 1;
        }
    }
    else if (wp->ctl.flags_4A & 0x10)
    {
        wp->routine_1    = 2;
        wp->ctl.timer_46 = wp->param_D * 60;
    }
}

void stcom17_func_0594(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;
    sint16 turn;
    sint16 aim;
    sint32 hit;
    sint32 mode;

    ctl  = &wp->ctl;
    mode = wp->variant_3 & 0xF;
    if (mode == 0)
    {
        if (wp->ctl.flags_4A & 0x10)
        {
            turn           = Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 6);
            aim            = Muku(&wp->position, &Player_work.position, (wp->rotation.y + wp->ctl.turn_44) & 0xFFF, 12);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn != 0)
            {
                if (wp->ctl.timer_48 == 0)
                {
                    Sound_call2(0xDB, &wp->position);
                    wp->ctl.timer_48 = 24;
                }
                else
                {
                    wp->ctl.timer_48--;
                }
            }
            else
            {
                wp->ctl.timer_48 = 0;
            }
            if (aim != 0)
            {
                if (ctl->timer_49 == 0)
                {
                    Sound_call2(0xDC, &wp->position);
                    ctl->timer_49 = 8;
                }
                else
                {
                    ctl->timer_49--;
                }
            }
            else
            {
                ctl->timer_49 = 0;
            }
            if (aim * turn > 0)
            {
                aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 6);
            }
            else
            {
                aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 24);
            }
            ctl->turn_44 = (ctl->turn_44 + aim) & 0xFFF;
            stcom17_func_1278(wp);
        }
    }
    else if (mode == 1)
    {
        if (wp->ctl.flags_4A & 0x10)
        {
            if (!(wp->ctl.flags_4E & 8))
            {
                turn           = Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 12);
                wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            }
            else
            {
                turn = 0;
            }
            aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 12);
            if (turn != 0)
            {
                if (ctl->timer_48 == 0)
                {
                    Sound_call2(0xDB, &wp->position);
                    ctl->timer_48 = 24;
                }
                else
                {
                    ctl->timer_48--;
                }
            }
            else
            {
                ctl->timer_48 = 0;
            }
            if (aim != 0)
            {
                if (ctl->timer_49 == 0)
                {
                    Sound_call2(0xDC, &wp->position);
                    ctl->timer_49 = 8;
                }
                else
                {
                    ctl->timer_49--;
                }
            }
            else
            {
                ctl->timer_49 = 0;
            }
            if (turn != 0)
            {
                if (turn * aim > 0)
                {
                    aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 6);
                }
                else
                {
                    aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 24);
                }
            }
            ctl->turn_44     = (ctl->turn_44 + aim) & 0xFFF;
            wp->velocity.v.x = 0xA0;
            if (ctl->timer_48 == 0)
            {
                Sound_call2(0xDB, &wp->position);
                ctl->timer_48 = 16;
            }
            else
            {
                ctl->timer_48--;
            }
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            hit = Obj_map_push_out(wp);
            if (!(hit & 0x3000))
            {
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
            }
            if (hit & 0xF00)
            {
                wp->routine_1 = 4;
                ctl->timer_46 = 60;
                return;
            }
            stcom17_func_1278(wp);
        }
    }
    else if (mode == 2)
    {
        wp->rotation.y = (wp->rotation.y + wp->param_E) & 0xFFF;
        aim            = Muku(&wp->position, &Player_work.position, (wp->rotation.y + wp->ctl.turn_44) & 0xFFF, 12);
        if (aim != 0)
        {
            if (wp->ctl.timer_49 == 0)
            {
                Sound_call2(0xDC, &wp->position);
                wp->ctl.timer_49 = 8;
            }
            else
            {
                wp->ctl.timer_49--;
            }
        }
        else
        {
            wp->ctl.timer_49 = 0;
        }
        if (aim * wp->param_E > 0)
        {
            aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 6);
        }
        else
        {
            aim = Muku(&wp->position, &Player_work.position, (wp->rotation.y + ctl->turn_44) & 0xFFF, 24);
        }
        ctl->turn_44     = (ctl->turn_44 + aim) & 0xFFF;
        wp->velocity.v.x = 0xA0;
        if (ctl->timer_48 == 0)
        {
            Sound_call2(0xDB, &wp->position);
            ctl->timer_48 = 24;
        }
        else
        {
            ctl->timer_48--;
        }
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
        stcom17_func_1278(wp);
    }
}

void stcom17_func_0AC4(STCOM17_WORK *wp)
{
    if (wp->ctl.timer_46 != 0)
    {
        if ((wp->ctl.count_4B & 0x18) == 0x18)
        {
            Sound_call2(0xDB, &wp->position);
        }
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 12)) & 0xFFF;
        wp->ctl.turn_44 =
            (wp->ctl.turn_44 + Muku(&wp->position, &Player_work.position, (wp->rotation.y + wp->ctl.turn_44) & 0xFFF, 12)) & 0xFFF;
        wp->velocity.v.x = 0xA0;
        Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
        wp->ctl.timer_46--;
        if (wp->ctl.flags_4A & 0x10)
        {
            wp->routine_1 = 1;
            stcom17_func_0594(wp);
        }
    }
    else
    {
        wp->routine_1    = 0;
        wp->ctl.timer_48 = 0;
        stcom17_func_0530(wp);
    }
}

void stcom17_func_0BE4(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;
    STCOM_PL_WORK *pl;
    STCOM17_SHOT *shot;
    STCOM_EFFECT *effect;

    ctl              = &wp->ctl;
    pl               = &Player_work;
    wp->ctl.timer_48 = 0;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        if (wp->ctl.timer_53 == 0)
        {
            func_80032304(wp, wp->anim_AC, 0);
            wp->anim_prev_AD = wp->anim_AC;
            shot             = Open_SHL_WORK();
            if (shot != NULL)
            {
                Sound_call2(0xDD, &wp->position);
                shot->flags_0          = 3;
                shot->kind_2           = 1;
                shot->value_4          = 0;
                shot->value_F          = 3;
                shot->position.x       = wp->joints_180[1].x;
                shot->position.y       = wp->joints_180[1].y - 0x41;
                shot->position.z       = wp->joints_180[1].z;
                shot->position_fixed.y = shot->position.y << 16;
                shot->position_fixed.x = shot->position.x << 16;
                shot->position_fixed.z = shot->position.z << 16;
                func_8002FFC4(&shot->position, &shot->position_fixed, (wp->rotation.y + wp->ctl.turn_44) & 0xFFF, 0xC00, 0, 0);
                pl->value_C4       = shot->position;
                wp->ctl.fixed_30.x = pl->value_C4.x << 16;
                wp->ctl.fixed_30.y = Player_work.value_C4.y << 16;
                wp->ctl.fixed_30.z = Player_work.value_C4.z << 16;
                func_8002FFC4(&pl->value_C4, &wp->ctl.fixed_30, (wp->rotation.y + wp->ctl.turn_44) & 0xFFF, 0x2000, 0, 0);
                Player_work.value_C4.y += 0x50;
                func_80030EE8(shot, &pl->value_C4, 0x30);
                effect = func_80031618();
                if (effect != NULL)
                {
                    effect->flags_0         = 3;
                    effect->kind_2          = 0xF;
                    effect->variant_3       = 3;
                    effect->value_C         = 1;
                    effect->sprite.pos_8[0] = shot->position.x;
                    effect->sprite.pos_8[1] = shot->position.y;
                    effect->sprite.pos_8[2] = shot->position.z;
                }
            }
        }
        else
        {
            wp->ctl.timer_53--;
            if (!(func_80030628(wp, pl, &wp->ctl.size_28, &wp->ctl.fixed_30, wp->rotation.y + wp->ctl.turn_44) & 2))
            {
                wp->anim_AC = 0;
                func_80032304(wp, 0, 0);
                wp->ctl.timer_53 = 30;
                wp->anim_prev_AD = wp->anim_AC;
                wp->routine_1    = wp->ctl.routine_4C;
                wp->routine_2    = wp->ctl.routine_4D;
            }
        }
    }
    else if (wp->flags_A7 == -1)
    {
        if ((func_80030628(wp, pl, &wp->ctl.size_28, &wp->ctl.fixed_30, wp->rotation.y + wp->ctl.turn_44) & 2) && wp->ctl.value_52 == 0)
        {
            wp->anim_AC      = 1;
            wp->anim_prev_AD = 0;
            wp->ctl.flags_4E |= 4;
            wp->ctl.value_52--;
        }
        else
        {
            wp->anim_AC = 0;
            func_80032304(wp, 0, 0);
            wp->anim_prev_AD = wp->anim_AC;
            wp->routine_1    = ctl->routine_4C;
            wp->routine_2    = ctl->routine_4D;
            ctl->timer_53    = 30;
        }
    }
}

void stcom17_func_0F08(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.timer_46 != 0)
    {
        if (wp->ctl.timer_48 == 0)
        {
            Sound_call2(0xDB, &wp->position);
            wp->ctl.timer_48 = 0x30;
        }
        else
        {
            wp->ctl.timer_48--;
        }
        func_8002FFC4(&wp->position, &wp->position_fixed, wp->rotation.y + 0x800, wp->velocity.v.x, 0, 0);
        if (!(Obj_map_push_out(wp) & 0x3000))
        {
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
        }
        ctl->timer_46--;
    }
    else
    {
        wp->routine_1    = 1;
        wp->ctl.flags_4E = 0;
        wp->ctl.timer_53 = 0;
    }
}

void stcom17_func_0FDC(STCOM17_WORK *wp)
{
    wp->ctl.timer_48 = 0;
    switch (wp->routine_2)
    {
        case 0:
            if (wp->ctl.count_4B != 0)
            {
                wp->ctl.count_4B--;
                func_8002FFC4(&wp->position, &wp->position_fixed, wp->rotation.y + 0x800, wp->velocity.v.x, 0, 0);
                wp->velocity.v.x -= 10;
            }
            else
            {
                wp->routine_1    = 1;
                wp->ctl.flags_4E = 0;
                wp->ctl.timer_53 = 0;
                wp->ctl.flags_4A &= ~4;
            }
            break;
        case 1:
            if (wp->ctl.count_4B != 0)
            {
                wp->ctl.count_4B--;
                func_8002FFC4(&wp->position, &wp->position_fixed, wp->rotation.y, wp->velocity.v.x, 0, 0);
                wp->velocity.v.x -= 10;
            }
            else
            {
                wp->routine_1    = 1;
                wp->ctl.flags_4E = 0;
                wp->ctl.timer_53 = 0;
                wp->ctl.flags_4A &= ~4;
            }
            break;
        case 2:
            if (wp->anim_prev_AD != wp->anim_AC)
            {
                func_80032304(wp, wp->anim_AC, 0);
                wp->anim_prev_AD = wp->anim_AC;
            }
            else if (wp->flags_A7 == -1)
            {
                wp->routine_1    = 1;
                wp->ctl.flags_4E = 0;
                wp->ctl.timer_53 = 0;
                wp->anim_AC      = 0;
                wp->ctl.flags_4A &= ~4;
                func_80032304(wp, 0, 0);
                wp->anim_prev_AD = wp->anim_AC;
            }
            break;
    }
    if (!(Obj_map_push_out(wp) & 0x3000))
    {
        wp->position.y       = Obj_ceiling_height_get(wp);
        wp->position_fixed.y = wp->position.y << 16;
    }
}

void stcom17_func_1168(STCOM17_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0         = 5;
        effect->kind_2          = 0x80;
        effect->variant_3       = 0x40;
        effect->sprite.position = wp->joints_180[1];
        func_80047148(wp, &wp->joints_180[0], effect);
    }
    func_80052528(wp);
    wp->flags_0               = 1;
    wp->kind_2                = 0;
    wp->variant_3             = 1;
    wp->value_4               = 1;
    *(uint32 *)&wp->routine_0 = 0;
    *(uint32 *)&wp->param_C   = 0;
    wp->position              = wp->joints_180[2];
    wp->position_fixed.x      = wp->joints_180[1].x << 16;
    wp->position_fixed.y      = wp->joints_180[1].y << 16;
    wp->position_fixed.z      = wp->joints_180[1].z << 16;
    Obj_pos_set(wp, -0x300, -0x400, 0);
    wp->rotation = wp->rotation; // a copy onto itself, in retail too
}

void stcom17_func_1278(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;
    STCOM_PL_WORK *pl;

    ctl                  = &wp->ctl;
    pl                   = &Player_work;
    Player_work.value_C4 = Player_work.position;
    wp->value_C4         = wp->joints_180[1];
    if (wp->value_80 <= 0x7FFFFF && (wp->flags_6 & 0x80))
    {
        if ((func_80030628(wp, pl, &wp->ctl.size_28, &wp->ctl.fixed_30, wp->rotation.y + wp->ctl.turn_44) & 2) && wp->ctl.timer_53 == 0)
        {
            wp->ctl.routine_4C = wp->routine_1;
            wp->ctl.routine_4D = wp->routine_2;
            wp->routine_1      = 3;
            wp->ctl.flags_4E |= 4;
        }
        else if (wp->ctl.timer_53 != 0)
        {
            ctl->timer_53--;
        }
    }
    if (wp->routine_1 != 3)
    {
        wp->value_C4 = wp->joints_180[0];
        if ((func_80030418(wp, pl, &ctl->size_28, &ctl->fixed_30) & 2) && !(ctl->flags_4E & 0xA))
        {
            ctl->flags_4E |= 2;
            ctl->timer_50 = 20;
            ctl->count_4F = 3;
            ctl->timer_51 = 0;
        }
    }
    if (wp->routine_1 == 3)
    {
        wp->anim_AC   = 1;
        ctl->value_52 = 3;
        ctl->timer_53 = 0;
        ctl->flags_4E &= ~0xA;
        stcom17_func_0BE4(wp);
    }
    else
    {
        stcom17_func_1470(wp);
    }
}

void stcom17_func_1470(STCOM17_WORK *wp)
{
    STCOM17_CTL *ctl;
    STCOM17_SHOT *shot;
    sint8 i;
    sint16 y;

    ctl = &wp->ctl;
    if (wp->value_80 <= 0x1FFFFF)
    {
        wp->ctl.value_54 = 1;
    }
    else
    {
        wp->ctl.value_54 = 0;
    }
    if (ctl->flags_4E & 0xA)
    {
        if (ctl->timer_50 == 0)
        {
            ctl->flags_4E |= 8;
            if (ctl->timer_51 == 0)
            {
                ctl->timer_51 = 5;
                if (ctl->count_4F != 0)
                {
                    i = 1;
                    do
                    {
                        shot = Open_SHL_WORK();
                        if (shot != NULL)
                        {
                            Sound_call2(0xEB, &wp->position);
                            shot->flags_0          = 1;
                            shot->kind_2           = 0x2E;
                            shot->variant_3        = 0x42;
                            shot->angle_64         = wp->rotation.y;
                            shot->position.x       = wp->joints_180[1].x;
                            shot->position.z       = wp->joints_180[1].z;
                            shot->position_fixed.x = shot->position.x << 16;
                            shot->position_fixed.z = shot->position.z << 16;
                            if (ctl->value_54 == 0)
                            {
                                y                      = wp->joints_180[1].y + 0x22;
                                shot->value_66         = 0x80;
                                shot->position.y       = y;
                                shot->position_fixed.y = y << 16;
                                // The side offsets are 20-bit values (0xFF710 is -0x8F0).
                                if (i != 0)
                                {
                                    func_8002FFC4(&shot->position, &shot->position_fixed, wp->rotation.y & 0xFFF, 0x800, 0, 0x8F0);
                                }
                                else
                                {
                                    func_8002FFC4(&shot->position, &shot->position_fixed, wp->rotation.y & 0xFFF, 0x800, 0, 0xFF710);
                                }
                            }
                            else
                            {
                                y                      = wp->joints_180[1].y + 0x78;
                                shot->value_66         = 0;
                                shot->position.y       = y;
                                shot->position_fixed.y = y << 16;
                                if (i != 0)
                                {
                                    func_8002FFC4(&shot->position, &shot->position_fixed, wp->rotation.y & 0xFFF, 0x800, 0, 0x280);
                                }
                                else
                                {
                                    func_8002FFC4(&shot->position, &shot->position_fixed, wp->rotation.y & 0xFFF, 0x800, 0, 0xFFD80);
                                }
                            }
                        }
                    } while (--i >= 0);
                    ctl->count_4F--;
                }
                else
                {
                    ctl->flags_4E &= ~0xA;
                }
            }
            else
            {
                ctl->timer_51--;
            }
        }
        else
        {
            ctl->timer_50--;
        }
    }
}

void stcom17_func_1690(STCOM17_GUN_WORK *wp)
{
    STCOM17_GUN_CTL *ctl;

    ctl                     = &wp->ctl;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->ctl.rot_18.v;
    wp->scale.v.pad         = 0x4210;
    stcom17_D_0034[wp->routine_0](wp);
    Mem_copy4(&wp->ctl.vec_8, (void *)0x1F800120, 8);
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x50, 0x200, 0);
    }
    if (wp->ctl.flags_62 & 8)
    {
        if (wp->rotation_prev.x != wp->ctl.rot_18.v.x || wp->rotation_prev.y != wp->ctl.rot_18.v.y)
        {
            if (wp->ctl.timer_68 == 0)
            {
                Sound_call2(0x147, &wp->position);
                wp->ctl.timer_68 = 10;
            }
            else
            {
                wp->ctl.timer_68--;
            }
        }
        else
        {
            wp->ctl.timer_68 = 0;
        }
        ctl->pos_0 = wp->joints_180[2];
        func_800341BC(&ctl->pos_0, 0xA0, 0, 0x8000, wp->value_1, &ctl->hit_28, ctl->power_5C | 0x4080000, 0, 0);
    }
    ctl->hit_28 = 0;
}

void stcom17_func_1854(STCOM17_GUN_WORK *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    *(uint32 *)&wp->ctl.angle_20 = 0;
    wp->scale.words[0]           = 0x2000200;
    wp->scale.words[1]           = 0x200;
    wp->ctl.flags_62             = 8;
    wp->ctl.speed_5E             = 0x28;
    wp->ctl.size_44.x            = 2;
    wp->ctl.size_44.y            = 9;
    wp->ctl.size_44.z            = 4;
    wp->ctl.vec_8.words[0]       = 0;
    wp->ctl.vec_8.words[1]       = 0;
    wp->ctl.vec_10.words[0]      = 0;
    wp->ctl.vec_10.words[1]      = 0;
    wp->ctl.rot_18.words[0]      = 0;
    wp->ctl.rot_18.words[1]      = 0;
    wp->ctl.value_24             = 0;
    wp->ctl.hit_28               = 0;
    wp->ctl.value_2C             = 0;
    wp->ctl.timer_64             = 0;
    wp->ctl.timer_63             = 0;
    wp->ctl.timer_68             = 0;
    wp->ctl.angle_60             = wp->ctl.angle_20;
    wp->ctl.dist_40              = wp->value_80;
    wp->ctl.power_5C             = D_80098844[wp->kind_2]->value_A;
    Track_reset(wp->ctl.track_30, 12, -0x60);
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 << 4;
    wp->routine_0                                    = 1;
    wp->routine_1                                    = 0;
    wp->routine_2                                    = 0;
    wp->scale.v.pad                                  = 0x4210;
    wp->data_78                                      = NULL;
}

void stcom17_func_1990(STCOM17_GUN_WORK *wp)
{
    STCOM17_GUN_CTL *ctl;
    uint32 damage;

    ctl = &wp->ctl;
    if (!func_800364B0(wp->ctl.track_30, wp, wp->rotation.y + wp->ctl.rot_18.v.y))
    {
        wp->ctl.flags_62 &= ~0x10;
    }
    else
    {
        wp->ctl.flags_62 = (wp->ctl.flags_62 | 0x10) & ~4;
    }
    damage = ctl->hit_28 & 0xFFFFFF;
    if (damage != 0)
    {
        wp->scale.v.pad  = 0x7FFF;
        wp->life_prev_B2 = wp->life_6E;
        wp->life_6E -= damage;
        ctl->flags_62 |= 4;
        if (wp->life_6E <= 0)
        {
            wp->routine_1 = 3;
            wp->routine_2 = 0;
            ctl->flags_62 &= ~8;
        }
        else
        {
            Sound_call2(0xA0, &wp->position);
        }
    }
    stcom17_D_0040[wp->routine_1](wp);
}

void stcom17_func_1A9C(STCOM17_GUN_WORK *wp)
{
    func_80031824(wp);
}

void stcom17_func_1ABC(STCOM17_GUN_WORK *wp)
{
    STCOM17_GUN_CTL *ctl;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (wp->ctl.timer_64 != 0)
    {
        wp->ctl.timer_64--;
    }
    if (!(wp->ctl.flags_62 & 0x10))
    {
        if (wp->ctl.timer_63 == 0)
        {
            wp->ctl.flags_62 &= ~0x10;
        }
        else
        {
            wp->ctl.timer_63--;
            wp->ctl.flags_62 |= 0x10;
        }
    }
    else
    {
        wp->ctl.timer_63 = 180;
        if (wp->value_80 > 0x8000 && wp->value_80 < 0xA20000)
        {
            Player_work.value_C4 = Player_work.position;
            wp->value_C4         = wp->joints_180[2];
            if ((func_80030628(wp, pl, &wp->ctl.size_44, &wp->ctl.fixed_4C, wp->rotation.y + wp->ctl.rot_18.v.y) & 2) &&
                wp->ctl.timer_64 == 0)
            {
                wp->routine_1    = 1;
                wp->ctl.timer_66 = 0;
                wp->ctl.count_65 = 3;
            }
        }
    }
    if (ctl->flags_62 & 0x14)
    {
        ctl->rot_18.v.y = (ctl->rot_18.v.y + Muku(&wp->position, &pl->position, (wp->rotation.y + ctl->rot_18.v.y) & 0xFFF, 16)) & 0xFFF;
        stcom17_func_2100(wp);
    }
}

// Scheduling of the shot's position stores and of the Player_work.value_C4 writes differs.
void stcom17_func_1C60(STCOM17_GUN_WORK *wp)
{
    STCOM17_GUN_CTL *ctl;
    STCOM_PL_WORK *pl;
    STCOM17_SHOT *shot;
    STCOM_EFFECT *effect;
    sint32 c;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (wp->ctl.count_65 != 0)
    {
        wp->ctl.rot_18.v.y =
            (wp->ctl.rot_18.v.y + Muku(&wp->position, &pl->position, (wp->rotation.y + wp->ctl.rot_18.v.y) & 0xFFF, 16)) & 0xFFF;
        shot = Open_SHL_WORK();
        if (shot != NULL)
        {
            Sound_call2(0x148, &wp->position);
            shot->flags_0          = 3;
            shot->kind_2           = 1;
            shot->value_4          = 0;
            shot->value_F          = 3;
            shot->position.x       = wp->joints_180[3].x;
            shot->position.y       = wp->joints_180[3].y;
            shot->position.z       = wp->joints_180[3].z;
            shot->position_fixed.x = shot->position.x << 16;
            shot->position_fixed.y = shot->position.y << 16;
            shot->position_fixed.z = shot->position.z << 16;
            Player_work.value_C4   = pl->position;
            wp->value_C4           = wp->joints_180[2];
            if (func_80030628(wp, pl, &wp->ctl.size_44, &wp->ctl.fixed_4C, wp->rotation.y + wp->ctl.rot_18.v.y) & 2)
            {
                Player_work.value_C4.x = pl->position.x;
                Player_work.value_C4.y = Player_work.position.y - 0x50;
                Player_work.value_C4.z = pl->position.z;
            }
            else
            {
                wp->value_80           = SquareRoot0(wp->value_80);
                c                      = rcos((wp->rotation.y + 0x800) + ctl->rot_18.v.y);
                Player_work.value_C4.x = wp->position.x + ((rsin((wp->rotation.y + 0x800) + ctl->rot_18.v.y) * wp->value_80) >> 12);
                Player_work.value_C4.y = Player_work.position.y - 0x50;
                Player_work.value_C4.z = wp->position.z + ((c * wp->value_80) >> 12);
            }
            Obj_launch_set(shot, pl, ctl->speed_5E, 0, 0xAC);
            stcom17_func_2100(wp);
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 3;
                effect->kind_2          = 0x83;
                effect->variant_3       = 0;
                effect->sprite.pos_8[0] = wp->joints_180[3].x;
                effect->sprite.pos_8[1] = wp->joints_180[3].y;
                effect->sprite.pos_8[2] = wp->joints_180[3].z;
            }
        }
        ctl->timer_66 = 70;
        ctl->count_65--;
        wp->routine_1 = 2;
    }
}

void stcom17_func_1F2C(STCOM17_GUN_WORK *wp)
{
    STCOM17_GUN_CTL *ctl;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if ((wp->ctl.flags_62 & 0x14) && wp->ctl.timer_66 < 60)
    {
        wp->ctl.rot_18.v.y =
            (wp->ctl.rot_18.v.y + Muku(&wp->position, &pl->position, (wp->rotation.y + wp->ctl.rot_18.v.y) & 0xFFF, 16)) & 0xFFF;
        stcom17_func_2100(wp);
    }
    if (ctl->timer_66 == 0)
    {
        if (ctl->count_65 != 0)
        {
            wp->routine_1 = 1;
        }
        else
        {
            ctl->count_65 = 3;
            ctl->timer_64 = 60;
            wp->routine_1 = 0;
        }
    }
    else
    {
        ctl->timer_66--;
    }
}

// gun is set in identical arms (merged by jump2) after the position copy: the call's argument
// then comes from gun, so local-alloc doesn't readdress the fixed stores through a0.
void stcom17_func_1FFC(STCOM17_GUN_WORK *wp)
{
    STCOM_EFFECT *effect;
    STCOM17_GUN_WORK *gun;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0         = 5;
        effect->kind_2          = 0x80;
        effect->variant_3       = 0x40;
        effect->sprite.position = wp->joints_180[2];
        func_80047148(wp, &wp->joints_180[0], effect);
    }
    if (wp->variant_3 == 0)
    {
        wp->flags_0               = 1;
        wp->kind_2                = 0;
        wp->variant_3             = 1;
        wp->value_4               = 1;
        *(uint32 *)&wp->routine_0 = 0;
        *(uint32 *)&wp->param_C   = 0;
        wp->position              = wp->joints_180[2];
        if (wp->variant_3 != 0)
        {
            gun = wp;
        }
        else
        {
            gun = wp;
        }
        wp->position_fixed.x = wp->joints_180[2].x << 16;
        wp->position_fixed.y = wp->joints_180[2].y << 16;
        wp->position_fixed.z = wp->joints_180[2].z << 16;
        Obj_pos_set(gun, -0x300, -0x400, 0);
    }
    else
    {
        wp->routine_0 = 2;
    }
}

void stcom17_func_2100(STCOM17_GUN_WORK *wp)
{
    STCOM17_GUN_CTL *ctl;
    STCOM_PL_WORK *pl;
    sint16 angle;
    sint16 goal;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (wp->ctl.dist_40 == wp->value_80)
    {
        if (wp->ctl.angle_60 != wp->ctl.angle_20)
        {
            goal  = wp->ctl.angle_20 & 0xFFF;
            angle = wp->ctl.angle_60 & 0xFFF;
            if (angle >= 0 && angle < 0x800)
            {
                if (goal >= 0x800 && goal < 0xFFF)
                {
                    stcom17_func_22C8(wp, angle, goal);
                }
                else
                {
                    stcom17_func_2320(wp, angle, goal);
                }
            }
            if (angle >= 0x800 && angle < 0xFFF)
            {
                if (goal >= 0 && goal < 0x800)
                {
                    stcom17_func_22C8(wp, angle, goal);
                }
                else
                {
                    stcom17_func_2320(wp, angle, goal);
                }
            }
        }
    }
    else
    {
        angle        = wp->ctl.angle_20 & 0xFFF;
        pl->value_C4 = Player_work.position;
        goal = wp->ctl.angle_60 = func_80030D30(&wp->joints_180[3], &pl->value_C4, wp->ctl.speed_5E, 0, 0xAC) & 0xFFF;
        wp->ctl.angle_20        = goal;
        if (angle >= 0 && angle < 0x800)
        {
            if (goal >= 0x800 && goal < 0xFFF)
            {
                stcom17_func_2378(wp, angle, goal);
            }
            else
            {
                stcom17_func_23BC(wp, angle, goal);
            }
        }
        if (angle >= 0x800 && angle < 0xFFF)
        {
            if (goal >= 0 && goal < 0x800)
            {
                stcom17_func_2378(wp, angle, goal);
            }
            else
            {
                stcom17_func_23BC(wp, angle, goal);
            }
        }
    }
    ctl->dist_40 = wp->value_80;
}

void stcom17_func_22C8(STCOM17_GUN_WORK *wp, sint16 angle, sint16 goal)
{
    sint32 d;

    STCOM17_ABS_DIFF(d, angle, goal);
    if (d > 32)
    {
        if (goal < angle)
        {
            wp->ctl.angle_20 = goal - 32;
        }
        else
        {
            wp->ctl.angle_20 = goal + 32;
        }
    }
    else
    {
        wp->ctl.angle_20 = angle;
    }
}

void stcom17_func_2320(STCOM17_GUN_WORK *wp, sint16 angle, sint16 goal)
{
    sint32 d;

    STCOM17_ABS_DIFF(d, angle, goal);
    if (d > 32)
    {
        if (goal < angle)
        {
            wp->ctl.angle_20 = goal + 32;
        }
        else
        {
            wp->ctl.angle_20 = goal - 32;
        }
    }
    else
    {
        wp->ctl.angle_20 = angle;
    }
}

void stcom17_func_2378(STCOM17_GUN_WORK *wp, sint32 angle, sint32 goal)
{
    sint32 d;

    STCOM17_ABS_DIFF(d, (sint16)angle, (sint16)goal);
    if (d > 32)
    {
        if ((sint16)goal < (sint16)angle)
        {
            wp->ctl.angle_20 = angle + 32;
        }
        else
        {
            wp->ctl.angle_20 = angle - 32;
        }
    }
}

void stcom17_func_23BC(STCOM17_GUN_WORK *wp, sint32 angle, sint32 goal)
{
    sint32 d;

    STCOM17_ABS_DIFF(d, (sint16)angle, (sint16)goal);
    if (d > 32)
    {
        if ((sint16)goal < (sint16)angle)
        {
            wp->ctl.angle_20 = angle - 32;
        }
        else
        {
            wp->ctl.angle_20 = angle + 32;
        }
    }
}
