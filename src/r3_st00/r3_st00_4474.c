#include "common.h"
#include "st00.h"

void func_80104474(STAGE_OBJ *wp)
{
    if (wp->routine_0 != 0)
    {
        func_80104808(wp);
        return;
    }
    func_801044B4(wp);
}

void func_801044B4(STAGE_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.v.x = wp->scale.v.y = wp->scale.v.z = 0x200;
    wp->scale.v.pad                               = 0x4210;
    wp->anim_AC                                   = 0;
    wp->rotation.y                                = 0xC00;
    func_800322A8(wp, wp->anim_AC, 0);
    wp->routine_0++;
}

void func_80104524(void)
{
}

void func_8010452C(STAGE_OBJ *wp)
{
    wp->u_C.timer = 500;
    wp->routine_2++;
}

void func_80104544(STAGE_OBJ *wp)
{
    if (--wp->u_C.timer == 0)
    {
        wp->u_C.timer = 0x80;
        D_80122450    = func_801185BC(wp, 0x14A, 0xA, 0x244, 0);
        D_80122454    = func_801185BC(wp, -0x14A, 0xA, 0x244, 0);
        wp->routine_2++;
    }
    wp->position_fixed.v.y -= 0x30750;
}

void func_801045EC(STAGE_OBJ *wp)
{
    if (--wp->u_C.timer == 0x1C)
    {
        D_80122450->routine_0 = 2;
        D_80122454->routine_0 = 2;
        D_80122450            = func_801185BC(wp, 0x14A, 0xA, 0x244, 1);
        D_80122454            = func_801185BC(wp, -0x14A, 0xA, 0x244, 1);
    }
    if (wp->u_C.timer == 4)
    {
        func_801185BC(wp, 0x14A, 0xA, 0x208, 2);
        func_801185BC(wp, -0x14A, 0xA, 0x208, 2);
    }
    if (wp->u_C.timer == 0)
    {
        D_80122450->routine_0 = 2;
        D_80122454->routine_0 = 2;
        wp->routine_2++;
    }
    wp->position_fixed.v.y += -0x10750;
    wp->rotation.y += 3;
}

void func_80104730(STAGE_OBJ *wp)
{
    wp->rotation.y += 0xC;
    Obj_pos_set(wp, 0x900, -0xFA, 0);
}

void func_80104764(STAGE_OBJ *wp)
{
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010478C(ST00_MOVER *wp)
{
    wp->position_fixed_prev.x  = wp->position_fixed.v.x;
    wp->position_fixed_prev.y  = wp->position_fixed.v.y;
    wp->position_fixed_prev.z  = wp->position_fixed.v.z;
    wp->rotation_prev.words[0] = wp->rotation.words[0];
    wp->rotation_prev.words[1] = wp->rotation.words[1];
    D_8011BF10[wp->routine_2](wp);
    Ride_move(STAGE_SCENE.slot_24[0], wp);
}

void func_80104808(STAGE_OBJ *wp)
{
    D_8011BF24[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_80104864(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_8011BF2C[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if ((wp->be_flag & 1) && (ctl->flags_0 & 4))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0x30, 0, 0x8000, wp->slot, &ctl->hit_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

// ported from r3_st09 func_801088B0
void func_80104A08(STAGE_STCOM15_WORK_348 *wp)
{
    sint32 life;

    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]          = 0x02000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_0             = 0xE;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    *(uint32 *)&wp->ctl.value_8 = 0;
    wp->ctl.hit_14              = 0;
    wp->ctl.value_18            = 0;
    Track_reset(wp->ctl.track_24, D_80098844[wp->id]->value_F, -0x60);
    wp->ctl.timer_36 = 4;
    wp->ctl.timer_34 = wp->position.pad;
    wp->position.pad = 0;
    life             = D_80098844[wp->id]->life_8;
    wp->data_78      = D_8011BF50;
    wp->data_10      = NULL;
    wp->life_6E      = life;
    wp->life_max_B0  = life;
    wp->life_prev_B2 = life;
    switch (wp->type)
    {
        case 0:
            wp->position.y            = Obj_ceiling_height_get(wp);
            wp->position_fixed.y      = wp->position.y << 16;
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 1:
            if (!Sce_flag_test((uint16)wp->ctl.timer_34))
            {
                wp->routine_0 = 1;
                wp->routine_1 = 4;
                wp->routine_2 = 0xFF;
                wp->routine_3 = 0;
                wp->be_flag &= ~2;
                func_800322A8(wp, 0, 0);
                wp->ctl.flags_0 = (wp->ctl.flags_0 | 0x40) & ~6;
                break;
            }
            // fall through
        default:
            wp->position.y            = Obj_ceiling_height_get(wp);
            wp->position_fixed.y      = wp->position.y << 16;
            wp->routine_0             = 1;
            wp->routine_1             = 1;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            wp->turn_66 = 0;
            break;
    }
    wp->scale.v.pad = 0x4210;
}

void func_80104BE4(ST00_ACTOR_B *wp)
{
    ST00_ACTOR_CTL_B *ctl;
    STCOM_EFFECT *fx;

    ctl = &wp->ctl;
    if (wp->ctl.flags_0 & 0x20)
    {
        if (func_8003648C(ctl->track_24, wp))
        {
            wp->ctl.flags_0 |= 0x10;
        }
        else
        {
            wp->ctl.flags_0 &= ~0x10;
        }
    }
    if (ctl->flags_0 & 2)
    {
        func_80105DEC(wp);
    }
    D_8011BF38[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 4:
                wp->routine_1 = 3;
                break;
            case 5:
                wp->routine_1 = 3;
                break;
            case 3:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 2;
                    break;
                }
                // fall through
            default:
                func_80105D10(wp);
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->flags_0 & 0x80)
    {
        if (--ctl->u_34.timer[1] < 0)
        {
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->be_flag         = 5;
                fx->id              = 0x80;
                fx->type            = 0x41;
                fx->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80047148(wp, &wp->value_180);
            Sound_call2(0xA1, &wp->value_180);
        }
    }
}

void func_80104DC8(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80104DE8(ST00_ACTOR *wp)
{
    STAGE_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0;
            wp->ctl.timer_4 = 0x3C;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~0x20;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80104E64(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x30;
            wp->accel.x      = 4;
            ctl->timer_4     = 0x32;
            ctl->level_6     = 0x19;
            ctl->value_8     = 0;
            ctl->flags_0 &= ~0x20;
            // fall through
        case 1:
            if (--ctl->level_6 < 0)
            {
                ctl->level_6     = 0x19;
                wp->velocity.v.x = 0x30;
            }
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            wp->velocity.v.x += wp->accel.x;
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit & 0xF00)
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (wp->position.y - wp->position_prev.y > 0x20)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (!(((wp->position.y - wp->position_prev.y < 0) ? wp->position_prev.y - wp->position.y
                                                              : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801050E8(STAGE_STCOM15_WORK_348 *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 2;
            wp->velocity.v.x = 0x100;
            wp->accel.x      = 0x10;
            ctl->timer_4     = 0xC;
            ctl->value_8     = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->velocity.v.x = 0x100;
                ctl->timer_4     = 0xC;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x30)) & 0xFFF;
            Obj_pos_set(wp, (uint8)wp->value_A6, 0, 0);
            wp->velocity.v.x += wp->accel.x;
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit & 0xF00)
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (wp->position.y - wp->position_prev.y > 0x20)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            if (!(((wp->position.y - wp->position_prev.y < 0) ? wp->position_prev.y - wp->position.y
                                                              : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (wp->value_80 < 0x1E848)
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x40, &pl->position_fixed, pl->rotation.y, 0x400))
                {
                    wp->routine_1             = 5;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->anim_AC               = wp->anim_prev_AD;
                    break;
                }
            }
            if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 = (ctl->flags_0 | 1) & ~0x20;
            }
            break;
    }
}

void func_801053B8(STAGE_STCOM15_WORK_348 *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 7;
            ctl->timer_4  = 0xC;
            ctl->value_8  = 0;
            Track_stop(ctl->track_24);
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC   = (ctl->rand_2 & 1) + 0xC;
                ctl->timer_4  = 6;
                ctl->flags_0 |= 0x20;
            }
            else
            {
                if (ctl->timer_4 < 3)
                {
                    break;
                }
                Obj_pos_set(wp, -0x50, 0, 0);
                Obj_map_push_out(wp);
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (!(((wp->position.y - wp->position_prev.y < 0) ? wp->position_prev.y - wp->position.y
                                                                  : wp->position.y - wp->position_prev.y) < 0x21))
                {
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC += 2;
            ctl->timer_4 = (ctl->rand_2 & 7) + 8;
            if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, pl->rotation.y, 0x800))
            {
                ctl->level_6 = (ctl->rand_2 & 3) + 1;
            }
            else
            {
                ctl->level_6 = (ctl->rand_2 & 7) + 3;
            }
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                if (--ctl->level_6 < 0)
                {
                    wp->routine_2 = 4;
                    wp->anim_AC += 2;
                    ctl->timer_4 = 0xD;
                }
                else
                {
                    wp->anim_AC ^= 1;
                    ctl->timer_4 = (ctl->rand_2 & 7) + 7;
                    break;
                }
            }
            else
            {
                if (ctl->flags_0 & 0x10)
                {
                    ctl->level_6 = 0;
                }
                break;
            }
            // fall through
        case 4:
            Obj_pos_set(wp, 0x33, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (!(((wp->position.y - wp->position_prev.y < 0) ? wp->position_prev.y - wp->position.y
                                                              : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80105740(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0xFF:
            if (!Sce_flag_test((uint16)ctl->timer_34))
            {
                break;
            }
            wp->be_flag |= 2;
            ctl->flags_0 |= 6;
            // fall through
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 4;
            if (ctl->flags_0 & 0x40)
            {
                wp->velocity.v.x = (ctl->rand_2 & 3) << 7;
                wp->velocity.v.y = (-(ctl->rand_2 & 0x30) + 1) * 16;
                wp->accel.y      = (((ctl->rand_2 >> 3) & 6) + 1) * 16;
                ctl->flags_0 &= ~0x40;
            }
            else
            {
                wp->velocity.v.x = 0x200;
                wp->velocity.v.y = -0x100;
                wp->accel.y      = 0x40;
                wp->rotation.y &= 0xFFF;
            }
            ctl->timer_4 = 0x10;
            ctl->level_6 = 0;
            ctl->value_8 = 0;
            ctl->flags_0 &= ~0x28;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2    = 1;
                wp->velocity.v.x = 0x88;
                wp->velocity.v.y = -0xF0;
                wp->accel.y      = 0x30;
            }
            // fall through
        case 1:
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel.y;
            hit = Obj_map_push_out(wp);
            if (hit & 0xF00)
            {
                wp->velocity.v.x = 0;
            }
            if (hit & 0x1000)
            {
                if (++ctl->level_6 == 1)
                {
                    wp->routine_2    = 2;
                    wp->anim_AC      = 5;
                    wp->velocity.v.x = 0xF0;
                    wp->velocity.v.y = 0;
                    wp->accel.y      = 0;
                    ctl->timer_4     = 2;
                    break;
                }
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_80105974(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    if (ctl->hit_14 & 0x2000000)
    {
        ctl->value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 7;
            ctl->timer_4  = 9;
            ctl->value_8  = D_80098844[wp->id]->value_A;
            ctl->flags_0 &= ~0x20;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC   = 8;
                ctl->timer_4  = 0xB;
            }
            else
            {
                Obj_pos_set(wp, -0x50, 0, 0);
                Obj_map_push_out(wp);
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (!(((wp->position.y - wp->position_prev.y < 0) ? wp->position_prev.y - wp->position.y
                                                                  : wp->position.y - wp->position_prev.y) < 0x21))
                {
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 9;
            ctl->timer_4  = -3;
            Obj_pos_set(wp, 0x640, -0x5A0, 0);
            Obj_map_push_out(wp);
            Sound_call2(0xBA, &wp->position);
            break;
        case 3:
            if (++ctl->timer_4 < 0)
            {
                wp->position.y -= ctl->timer_4 * ctl->timer_4 * 4;
            }
            else
            {
                wp->position.y += ctl->timer_4 * ctl->timer_4 * 4;
            }
            wp->position_fixed.y = wp->position.y << 16;
            Obj_pos_set(wp, 0x370, 0, 0);
            hit = Obj_map_push_out(wp);
            if (hit & 0xF00)
            {
                wp->velocity.v.x = 0;
            }
            if (hit & 0x1000)
            {
                wp->routine_2 = 4;
                wp->anim_AC   = 0xA;
                ctl->timer_4  = 0xA;
                ctl->value_8  = 0;
            }
            if (ctl->hit_14 & 0x2000000)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                wp->rotation.y            = (wp->rotation.y + 0x800) & 0xFFF;
                ctl->value_8              = 0;
            }
            break;
        case 4:
            Obj_pos_set(wp, 0xA0, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (!(((wp->position.y - wp->position_prev.y < 0) ? wp->position_prev.y - wp->position.y
                                                              : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

sint32 func_80105D10(ST00_ACTOR *wp)
{
    sint16 i;
    sint16 sum;

    sum = 0;
    for (i = 0; i < 4; i++)
    {
        sum += D_8011BF5C[i];
        if ((wp->ctl.value_2 & 0xF) < sum)
        {
            break;
        }
    }
    wp->routine_1 = 1;
    switch (i)
    {
        case 0:
            wp->routine_1 = 3;
            break;
        case 1:
            wp->value_66 = 0;
            // fall through
        case 2:
            wp->value_66 = 0x10;
            break;
        case 3:
            wp->value_66 = -0x10;
            break;
    }
    return 1;
}

sint32 func_80105DEC(ST00_ACTOR_B *wp)
{
    STCOM_SVECTOR origin = {0, 0, 0, 0};
    ST00_ACTOR_CTL_B *ctl;
    sint32 damage;
    sint16 angle;

    ctl    = &wp->ctl;
    damage = wp->ctl.hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (wp->ctl.hit_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                wp->ctl.flags_0 = (wp->ctl.flags_0 & ~2) | 0x88;
                damage          = D_80098844[wp->id]->limit_9;
            }
            if (wp->ctl.flags_0 & 8)
            {
                wp->ctl.timer_A += damage;
                if ((wp->ctl.hit_14 & 0x20000000) || wp->ctl.timer_A >= D_80098844[wp->id]->limit_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    if (wp->ctl.target_1C.pad & 1)
                    {
                        angle = Angle_xz_svector(&wp->position, &wp->ctl.target_1C);
                        if (((wp->rotation.y - angle + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->rotation.y = angle;
                        }
                        else
                        {
                            wp->rotation.y = (angle + 0x800) & 0xFFF;
                        }
                    }
                    else
                    {
                        angle          = Angle_xz_svector(&origin, &wp->ctl.target_1C);
                        wp->rotation.y = angle;
                    }
                    wp->routine_1             = 4;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->timer_A              = 0;
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
            else
            {
                Sound_call2(((wp->ctl.hit_14 & 0x20000000) || wp->ctl.timer_A >= D_80098844[wp->id]->limit_9) ? 0xA2 : 0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_8010602C(STAGE_OBJ *wp)
{
    if (wp->routine_0 != 0)
    {
        func_80106218(wp);
        return;
    }
    func_8010606C(wp);
}

void func_8010606C(ST00_SWAY *wp)
{
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->position_fixed.x = D_8011BF60[wp->type].x << 16;
    wp->position_fixed.y = D_8011BF60[wp->type].y << 16;
    wp->position_fixed.z = D_8011BF60[wp->type].z << 16;
    func_80030150(&wp->position_fixed, &wp->position);
    wp->value_44.half[0] = D_8011BF60[wp->type].speed_8;
    wp->value_44.half[1] = 0;
    wp->value_48         = 0;
    wp->rotation.y       = D_8011BF60[wp->type].rot_6;
    wp->anim_AC          = 0;
    func_800322A8(wp, 0, 0);
    wp->scale.v.x = wp->scale.v.y = wp->scale.v.z = 0x200;
    wp->scale.v.pad                               = 0x4210;
    wp->count_1E0                                 = 0;
    wp->period_1E2                                = D_8011BF60[wp->type].period_E;
    wp->step_1E4                                  = 0x1000 / wp->period_1E2;
    wp->height_1E6                                = D_8011BF60[wp->type].height_C;
    wp->spin_1D8                                  = D_8011BF60[wp->type].spin_A;
    wp->base_1DA                                  = D_8011BF60[wp->type].y;
    wp->routine_0++;
}

void func_80106218(ST00_SWAY *wp)
{
    STCOM_SVECTOR unused;

    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
    wp->rotation.y = (wp->rotation.y + wp->spin_1D8) & 0xFFF;
    wp->position.y = wp->base_1DA + ((wp->height_1E6 * rsin(wp->step_1E4 * wp->count_1E0)) >> 12);
    wp->count_1E0  = ++wp->count_1E0 % wp->period_1E2;
    func_80032488(wp);
}

void func_801062EC(ST00_ACTOR_B *wp)
{
    ST00_ACTOR_CTL_B *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_8011C000[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (ctl->flags_0 & 0x20)
    {
        ScaleMatrix(&wp->matrix_208, &ctl->u_34.scale);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    if (ctl->flags_0 & 8)
    {
        ctl->pos_C = wp->value_180;
        func_800341BC(&ctl->pos_C, 0x50, 0, 0x8000, wp->slot, &ctl->hit_14, ctl->value_8 | 0x4880000, 0x800000, 0x80);
    }
    ctl->hit_14 = 0;
}

void func_8010648C(ST00_OBJ *wp)
{
    sint16 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_64.word  = 0;
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->value_37C      = 0x1000;
    wp->value_380      = 0x1000;
    wp->value_384      = 0;
    wp->value_348      = 0x2C;
    wp->value_34C      = 0;
    wp->value_350      = 0;
    wp->value_35C      = 0;
    wp->value_360      = 0;
    Track_reset(wp->track_36C, 0, -0x60);
    life                      = D_80098844[wp->id]->life_8;
    wp->value_78              = D_8011C014;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->value_6E              = life;
    wp->value_B0              = life;
    wp->value_B2              = life;
    func_800322A8(wp, 0, 0);
    wp->scale.v.pad = 0x4210;
    wp->value_FF    = -1;
}

void func_80106584(ST00_ACTOR_B *wp)
{
    ST00_ACTOR_CTL_B *ctl;

    ctl = &wp->ctl;
    if ((wp->ctl.flags_0 & 0x40) && func_8003648C(wp->ctl.track_24, wp) != 0)
    {
        wp->ctl.flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 2)
    {
        func_80106800(wp);
    }
    D_8011C00C[wp->routine_1](wp);
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1 = 1;
                break;
            case 1:
                wp->id                    = 3;
                wp->type                  = 0x40;
                *(uint32 *)&wp->routine_0 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
}

void func_801066B8(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801066D8(ST00_ACTOR *wp)
{
    STAGE_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (wp->dist_80 <= 0x4E200)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_8010673C(ST00_SPINNER *wp)
{
    ST00_SPIN *spin;

    spin = &wp->spin;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 0;
            wp->value_FF     = 0;
            wp->spin.timer_4 = 8;
            wp->spin.value_8 = 0;
            // fall through
        case 1:
            if (--spin->timer_4 < 0)
            {
                Obj_pos_set(wp, 0x200, 0, 0);
                spin->angle_3C += 0x800;
                spin->flags_0 |= 1;
            }
            else
            {
                Obj_pos_set(wp, 0x40, 0, 0);
                spin->angle_3C += 0x100;
            }
            break;
    }
}

sint32 func_80106800(ST00_ACTOR *wp)
{
    uint32 hit;
    sint32 damage;

    hit    = wp->ctl.hit_14;
    damage = hit & 0xFFFFFF;
    if (damage != 0)
    {
        if (hit & 0x18000000)
        {
            Sound_call2(0xA3, &wp->position);
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->ctl.flags_0           = (wp->ctl.flags_0 & ~2) | 4;
            }
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
