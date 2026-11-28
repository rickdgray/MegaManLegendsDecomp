#include "common.h"
#include "st00.h"

void func_8010A68C(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_8011C178[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    ST00_SP_13C = ctl->timer_38;
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0x50, 0, 0x8000, wp->value_1, &ctl->hit_14, ctl->value_8 | 0x5880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

// NON_MATCHING: only the copy of the ground height (move v1,v0) is scheduled before the call arguments here; retail puts it after them.
void func_8010A844(STAGE_STCOM15_WORK_4E0 *wp)
{
    sint32 life;
    sint16 ground;
    sint16 floor;

    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]          = 0x02000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_0             = 0x2E;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    *(uint32 *)&wp->ctl.value_8 = 0;
    wp->ctl.hit_14              = 0;
    wp->ctl.value_18            = 0;
    Track_reset(wp->ctl.track_24, D_8009884C[wp->kind_2][wp->param_D].value_F, -0x60);
    *(uint32 *)&wp->ctl.timer_34 = 0;
    *(uint32 *)&wp->ctl.timer_38 = 0;
    wp->ctl.u_3C.flag            = wp->position.pad;
    life                         = D_8009884C[wp->kind_2][wp->param_D].life_8 << 4;
    wp->data_78                  = D_8011C1B4;
    wp->data_10                  = NULL;
    wp->life_6E                  = life;
    wp->life_max_B0              = life;
    wp->life_prev_B2             = life;
    if ((wp->variant_3 & 0x7F) == 0)
    {
        ground                    = Obj_floor_height_get(wp);
        (&wp->ctl.u_3C.flag)[1]   = ground;
        wp->position.y            = ground;
        wp->position_fixed.y      = ground << 16;
        wp->routine_0             = 1;
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
        func_800322A8(wp, 1, 0);
    }
    else
    {
        floor                     = Obj_ceiling_height_get(wp);
        (&wp->ctl.u_3C.flag)[1]   = floor;
        wp->position.y            = floor;
        wp->position_fixed.y      = floor << 16;
        wp->routine_0             = 1;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        func_800322A8(wp, 0, 0);
    }
    wp->scale.v.pad = 0x4210;
}

void func_8010A9C8(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    uint32 dx;
    uint32 dz;

    ctl = &wp->ctl;
    if ((wp->ctl.flags_0 & 0x20) && func_8003648C(wp->ctl.track_24, wp) != 0)
    {
        wp->ctl.flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if ((ctl->flags_0 & 2) && ((wp->variant_3 & 0x80) || Sce_flag_test(ctl->u_3C.flag)))
    {
        func_8010C35C(wp);
    }
    if (Game_work.value_50 == 0)
    {
        dx = wp->position.x - D_8011C1C0;
        dz = wp->position.z - D_8011C1C2;
        if (!(ctl->flags_0 & 0x40) && wp->life_6E > 0 && (dx >= D_8011C1C4 || dz >= D_8011C1C6))
        {
            wp->routine_1             = 0xB;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->flags_0 |= 0x40;
        }
    }
    D_8011C184[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 5:
                wp->routine_1 = 3;
                break;
            case 4:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 5;
                }
                else
                {
                    wp->routine_1 = 0xA;
                }
                break;
            case 11:
                wp->routine_1 = 1;
                break;
            case 0:
            case 10:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 5;
                }
                else
                {
                    wp->routine_1 = 0;
                }
                break;
            case 6:
            case 7:
            case 8:
                if (wp->life_6E > 0)
                {
                    wp->routine_1 = 5;
                }
                else
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0         = 5;
                        fx->kind_2          = 0x80;
                        fx->variant_3       = 0x40;
                        fx->sprite.position = wp->position;
                    }
                    func_8003187C(wp);
                    func_80047228(wp, &wp->position, wp->param_D);
                    Sound_call2(0xA1, &wp->position);
                }
                break;
            default:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    func_8010C294(wp);
                }
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->timer_34 != 0)
    {
        ctl->timer_34--;
    }
    if (ctl->timer_36 != 0)
    {
        ctl->timer_36--;
    }
}

void func_8010ACE8(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_8010AD08(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0;
            wp->ctl.value_8 = 0;
            wp->ctl.timer_4 = 0xF;
            // fall through
        case 1:
            if ((wp->variant_3 & 0x80) || Sce_flag_test(ctl->u_3C.flag))
            {
                if ((ctl->hit_14 & 0xFFFFFF) || (ctl->timer_4 < 0 && wp->value_80 <= 0x3BD07))
                {
                    wp->routine_1             = 0xA;
                    *(uint16 *)&wp->routine_2 = 0;
                    break;
                }
                if (ctl->timer_4 >= 0)
                {
                    ctl->timer_4--;
                }
                if (ctl->flags_0 & 0x10)
                {
                    ctl->flags_0 |= 1;
                }
            }
            break;
    }
}

void func_8010AE00(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 shift;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            shift           = wp->ctl.rand_2 & 1;
            wp->ctl.timer_4 = wp->ctl.level_6 = (8 >> shift) + (2 >> shift);
            wp->ctl.flag_3A                   = ((wp->ctl.rand_2 & 2) ? 0x200 : -0x200) << shift;
            ctl->value_8                      = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                wp->routine_2 = 2;
                wp->routine_3++;
                ctl->timer_4 = 8;
            }
            ctl->timer_38 = (ctl->timer_38 + ctl->flag_3A) & 0xFFF;
            break;
        case 2:
            if (--wp->ctl.timer_4 < 0)
            {
                if (wp->routine_3 >= 4 && ((wp->variant_3 & 0x80) || Sce_flag_test(wp->ctl.u_3C.flag)))
                {
                    wp->ctl.flags_0 |= 1;
                }
                wp->routine_2 = 1;
                ctl->timer_4  = ctl->level_6;
            }
            break;
    }
    if (((wp->variant_3 & 0x80) || Sce_flag_test(ctl->u_3C.flag)) && (wp->value_80 <= 0x1FFFF || (ctl->hit_14 & 0xFFFFFF)))
    {
        wp->routine_1             = 4;
        *(uint16 *)&wp->routine_2 = 0;
        wp->anim_AC               = wp->anim_prev_AD;
        ctl->flags_0 &= ~1;
    }
}

void func_8010AFF8(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 3;
            ctl->timer_4  = 0x5A;
            ctl->value_8  = 0;
            // fall through
        case 1:
            if (wp->value_80 <= 0x1FFFF || (ctl->hit_14 & 0xFFFFFF))
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            Obj_pos_set(wp, 0x70, 0, 0);
            if (Obj_map_push_out(wp) & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
            }
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD5, &wp->position);
            }
            break;
    }
}

void func_8010B1C0(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    ST00_SHOT *shot;
    uint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->routine_3 = 0;
            wp->anim_AC   = 4;
            ctl->value_8  = 0;
            // fall through
        case 1:
            if (!(ctl->flags_0 & 0x10))
            {
                wp->anim_AC = wp->anim_prev_AD;
                ctl->flags_0 |= 1;
                break;
            }
            if (ctl->timer_34 == 0 && wp->value_80 <= 0x1FFFFF)
            {
                shot = (ST00_SHOT *)Open_SHL_WORK();
                if (shot != NULL)
                {
                    shot->flags_0  = 1;
                    shot->kind_2   = 6;
                    shot->position = wp->joints_180[0];
                    shot->position.y += 0x60;
                    shot->position_fixed.x = shot->position.x << 16;
                    shot->position_fixed.z = shot->position.z << 16;
                    shot->position_fixed.y = shot->position.y << 16;
                    shot->angle_64         = ctl->rand_2 & 0xFFF;
                    shot->value_9C         = 0;
                    shot->value_A0         = 0;
                    Sound_call2(0xB2, &wp->position);
                }
                if (wp->routine_3 < D_8009884C[wp->kind_2][wp->param_D].count_B)
                {
                    wp->routine_3++;
                    ctl->timer_34 = 0x1E;
                }
                else
                {
                    wp->routine_3 = 0;
                    ctl->timer_34 = 0x78;
                }
            }
            else if (ctl->timer_36 == 0 && wp->value_80 <= 0x1FFFF)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            wp->turn_66    = Muku(&wp->position, &pl->position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            Obj_pos_set(wp, 0x100, 0, 0);
            hit = Obj_map_push_out(wp);
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD5, &wp->position);
            }
            if (hit & 0xF00)
            {
                wp->routine_1             = 9;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            break;
    }
}

void func_8010B4B0(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 prev;
    uint16 ground;
    uint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2        = 1;
            wp->anim_AC          = 6;
            wp->velocity.v.y     = 0x100;
            wp->accel.y          = 0x100;
            ctl->timer_4         = 0x14;
            ctl->value_8         = D_8009884C[wp->kind_2][wp->param_D].value_A;
            (&ctl->u_3C.flag)[1] = Obj_ceiling_height_get(wp);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 7;
            wp->position.y += 0xC8;
            wp->joints_180[0].y += 0xC8;
            wp->position_fixed.y = wp->position.y << 16;
            break;
        case 2:
            Obj_pos_set(wp, 0, wp->velocity.v.y, 0);
            prev                 = wp->position.y;
            wp->position.y       = wp->joints_180[0].y + (wp->velocity.v.y >> 4);
            wp->position_fixed.y = wp->position.y << 16;
            hit                  = Obj_map_push_out(wp);
            wp->velocity.v.y += wp->accel.y;
            if ((hit & 0x1000) || prev >= (sint16)(&ctl->u_3C.flag)[1])
            {
                ground               = (&ctl->u_3C.flag)[1];
                wp->routine_2        = 3;
                wp->anim_AC          = 8;
                wp->position.y       = ground;
                wp->position_fixed.y = ground << 16;
                ctl->timer_4         = 3;
                Sound_call2(0xD3, &wp->position);
            }
            else
            {
                wp->position.y       = prev;
                wp->position_fixed.y = prev << 16;
                break;
            }
            // fall through
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 4;
            ctl->timer_4  = 0x19;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->timer_36 = 0x78;
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_8010B6C8(STAGE_STCOM15_WORK_4E0 *wp)
{
    sint32 y;
    STAGE_STCOM15_CTL *ctl;
    uint16 ground;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2        = 1;
            wp->anim_AC          = 0xA;
            wp->velocity.v.y     = -0x100;
            wp->accel.y          = -0x100;
            ctl->timer_4         = 0xA;
            ctl->value_8         = 0;
            (&ctl->u_3C.flag)[1] = Obj_floor_height_get(wp); // the union's second halfword: the ground
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC   = 0xB;
                wp->position.y -= 0x15E;
                wp->joints_180[0].y -= 0x15E;
                wp->position_fixed.y = wp->position.y << 16;
                Sound_call2(0xD1, &wp->position);
            }
            break;
        case 2:
            Obj_pos_set(wp, 0, wp->velocity.v.y, 0);
            y                    = wp->position.y;
            wp->position.y       = wp->joints_180[0].y - (wp->velocity.v.y >> 4);
            wp->position_fixed.y = wp->position.y << 16;
            hit                  = Obj_map_push_out(wp);
            wp->velocity.v.y += wp->accel.y;
            if ((hit & 0x2000) || (sint16)(&wp->ctl.u_3C.flag)[1] >= y)
            {
                wp->routine_2        = 3;
                wp->anim_AC          = 0xC;
                ground               = (&wp->ctl.u_3C.flag)[1];
                wp->ctl.timer_4      = 0x2D;
                wp->position.y       = ground;
                wp->position_fixed.y = ground << 16;
                Sound_call2(0xD2, &wp->position);
            }
            else
            {
                wp->position.y       = y;
                wp->position_fixed.y = y << 16;
                break;
            }
            // fall through
        case 3:
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD4, &wp->position);
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_8010B8CC(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0xE;
            wp->ctl.timer_4 = 3;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~4;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 0x10;
            ctl->timer_4  = 0x11;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            if (wp->life_6E > 0)
            {
                wp->routine_2 = 3;
                wp->anim_AC   = 0x13;
                ctl->timer_4  = 0x13;
            }
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 5;
            }
            break;
    }
}

void func_8010B9DC(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 prev;
    uint16 ground;
    uint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 0xF;
            wp->velocity.v.y = 0x100;
            wp->accel.y      = 0x100;
            ctl->timer_4     = 3;
            ctl->value_8     = 0;
            ctl->flags_0 &= ~4;
            (&ctl->u_3C.flag)[1] = Obj_ceiling_height_get(wp);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 0x11;
            wp->position.y += 0xC8;
            wp->joints_180[0].y += 0xC8;
            wp->position_fixed.y = wp->position.y << 16;
            // fall through
        case 2:
            Obj_pos_set(wp, 0, wp->velocity.v.y, 0);
            prev                 = wp->position.y;
            wp->position.y       = wp->joints_180[0].y + (wp->velocity.v.y >> 4);
            wp->position_fixed.y = wp->position.y << 16;
            hit                  = Obj_map_push_out(wp);
            wp->velocity.v.y += wp->accel.y;
            if ((hit & 0x1000) || prev >= (sint16)(&ctl->u_3C.flag)[1])
            {
                ground               = (&ctl->u_3C.flag)[1];
                wp->position.y       = ground;
                wp->position_fixed.y = ground << 16;
                if (wp->life_6E <= 0)
                {
                    ctl->flags_0 |= 5;
                    Sound_call2(0xD3, &wp->position);
                    break;
                }
                wp->routine_2 = 3;
                wp->anim_AC   = 0x10;
                ctl->timer_4  = 0x11;
            }
            else
            {
                wp->position.y       = prev;
                wp->position_fixed.y = prev << 16;
                break;
            }
            // fall through
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 4;
            wp->anim_AC   = 0x13;
            ctl->timer_4  = 0x13;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 5;
            }
            break;
    }
}

void func_8010BBF4(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    uint16 ground;
    uint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0x12;
            ctl->timer_4  = 9;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~4;
            (&ctl->u_3C.flag)[1] = Obj_ceiling_height_get(wp);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->velocity.v.y = 4 - ctl->timer_4;
                Obj_pos_set(wp, 0, wp->velocity.v.y << 7, 0);
                if (!(Obj_map_push_out(wp) & 0x2000))
                {
                    break;
                }
            }
            wp->routine_2    = 2;
            wp->anim_AC      = 0x11;
            wp->velocity.v.y = 0x100;
            wp->accel.y      = 0x100;
            // fall through
        case 2:
            Obj_pos_set(wp, 0, wp->velocity.v.y, 0);
            hit = Obj_map_push_out(wp);
            wp->velocity.v.y += wp->accel.y;
            if (!(hit & 0x1000) && wp->position.y < (sint16)(&ctl->u_3C.flag)[1])
            {
                break;
            }
            ground               = (&ctl->u_3C.flag)[1];
            wp->position.y       = ground;
            wp->position_fixed.y = ground << 16;
            if (wp->life_6E <= 0)
            {
                wp->joints_180[0].y = wp->position.y;
                ctl->flags_0 |= 5;
                Sound_call2(0xD3, &wp->position);
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 0x10;
            ctl->timer_4  = 0x11;
            // fall through
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 4;
            wp->anim_AC   = 0x13;
            ctl->timer_4  = 0x13;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 5;
            }
            break;
    }
}

void func_8010BDF0(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STAGE_PL_VIEW *pl;
    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 4;
            wp->turn_66     = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 4;
            wp->ctl.timer_4 = 0x10;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD5, &wp->position);
            }
            break;
    }
}

void func_8010BED4(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    uint16 ground;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 7;
            wp->turn_66      = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 4;
            wp->velocity.v.y = -0x200;
            wp->accel.y      = 0x40;
            ctl->timer_4     = 0x10;
            ctl->value_8     = 0;
            Sound_call2(0xD1, &wp->position);
            (&ctl->u_3C.flag)[1] = Obj_ceiling_height_get(wp); // the union's second halfword: the ground
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            Obj_pos_set(wp, 0, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel.y;
            if (!(Obj_map_push_out(wp) & 0x1000) && wp->position.y < (sint16)(&ctl->u_3C.flag)[1])
            {
                break;
            }
            ground               = (&ctl->u_3C.flag)[1];
            wp->routine_2        = 2;
            wp->anim_AC          = 8;
            wp->position.y       = ground;
            wp->position_fixed.y = ground << 16;
            ctl->timer_4         = 13;
            Sound_call2(0xD3, &wp->position);
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_8010C070(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 4;
            D_80122458.y    = 0;
            D_80122458.x    = D_8011C1C8.x + (D_8011C1CC.x >> 1);
            D_80122458.z    = D_8011C1C8.z + (D_8011C1CC.z >> 1);
            wp->ctl.timer_4 = 0x10;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~4;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &D_80122458, wp->rotation.y, 0x80)) & 0xFFF;
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 3;
            ctl->value_8  = 0;
            ctl->timer_4  = 300;
            // fall through
        case 2:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &D_80122458, wp->rotation.y, 0x20)) & 0xFFF;
            Obj_pos_set(wp, 0x70, 0, 0);
            Obj_map_push_out(wp);
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD5, &wp->position);
            }
            dx = wp->position.x - D_8011C1C8.x;
            dz = wp->position.z - D_8011C1C8.z;
            if (--ctl->timer_4 < 0 || ((uint32)dx < D_8011C1CC.x && (uint32)dz < D_8011C1CC.z))
            {
                ctl->flags_0 = (ctl->flags_0 | 5) & ~0x40;
            }
            break;
    }
}

sint32 func_8010C294(STAGE_STCOM15_WORK_4E0 *wp)
{
    sint16 sum;
    sint16 i;
    uint8 *chance;
    chance = D_8011C1D0;
    sum    = 0;
    for (i = 0; i < 4; i++, chance++)
    {
        sum += *chance;
        if ((wp->ctl.rand_2 & 0xF) < sum)
        {
            break;
        }
    }
    wp->routine_1 = 2;
    switch (i)
    {
        case 0:
            wp->turn_66 = 0;
            break;
        case 1:
            wp->turn_66 = 6;
            break;
        case 2:
            wp->turn_66 = -6;
            break;
        default:
            wp->routine_1 = 1;
            break;
    }
    return 1;
}

sint32 func_8010C35C(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 damage;

    ctl    = &wp->ctl;
    damage = wp->ctl.hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (wp->ctl.hit_14 & 0x38000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                wp->ctl.flags_0 = (wp->ctl.flags_0 & ~2) | 4;
                damage          = D_8009884C[wp->kind_2][wp->param_D].limit_9 << 4;
            }
            if (wp->ctl.flags_0 & 4)
            {
                wp->ctl.timer_A += damage;
                if (wp->ctl.timer_A < D_8009884C[wp->kind_2][wp->param_D].limit_9 << 4)
                {
                    Sound_call2(0xA0, &wp->position);
                }
                else
                {
                    Sound_call2(0xA2, &wp->position);
                    switch (wp->routine_1)
                    {
                        case 0:
                            wp->routine_1 = 6;
                            break;
                        case 1:
                        case 2:
                        case 3:
                        case 9:
                        case 11:
                            wp->routine_1 = 7;
                            break;
                        case 4:
                        case 5:
                        case 10:
                            if (wp->position.y == Obj_ceiling_height_get(wp))
                            {
                                wp->routine_1 = 6;
                                break;
                            }
                            if (wp->position.y == Obj_floor_height_get(wp))
                            {
                                wp->routine_1 = 7;
                                break;
                            }
                            fx = func_80031618();
                            if (fx != NULL)
                            {
                                fx->flags_0         = 5;
                                fx->kind_2          = 0x80;
                                fx->variant_3       = 0x40;
                                fx->sprite.position = wp->position;
                            }
                            func_8003187C(wp);
                            func_80047228(wp, &wp->position, wp->param_D);
                            Sound_call2(0xA1, &wp->position);
                            break;
                    }
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->timer_A              = 0;
                }
            }
            else
            {
                Sound_call2((wp->ctl.timer_A >= D_8009884C[wp->kind_2][wp->param_D].limit_9 << 4) ? 0xA2 : 0xA0, &wp->position);
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

void func_8010C5D0(STAGE_OBJ *wp, sint32 index)
{
    D_80122460[0] = D_8011C2A8[index];
    D_80122464[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80122460[0]->id, 0x2A, 0x33, 6));
}

void func_8010C644(STAGE_OBJ *wp, sint32 index)
{
    D_80122468[0] = D_8011C2E0[index];
    D_8012246C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80122468[0]->id, 0x2A, 0x33, 6));
}

void func_8010C6B8(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    sint16 count;
    sint16 *cnt;

    count = D_80122460_S->count;
    if (count <= 0)
    {
        D_80122464[0] = 0;
        D_80122460[0] += count;
    }
    cnt = D_80122464;
    (*cnt)++;
    p = D_80122460[0];
    if (*cnt == p->count)
    {
        D_80122460_S = p + 1;
        *cnt         = 0;
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(p[1].id, 0x2A, 0x33, 6));
    }
    count = D_80122468_S->count;
    if (count <= 0)
    {
        D_8012246C[0] = 0;
        D_80122468[0] += count;
    }
    cnt = D_8012246C;
    (*cnt)++;
    p = D_80122468[0];
    if (*cnt == p->count)
    {
        D_80122468_S = p + 1;
        *cnt         = 0;
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(p[1].id, 0x2A, 0x33, 6));
    }
}

void func_8010C820(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80122470.cue_0->u.end != 0xFF && D_80122470.cue_0->u.scene == scene->u_8.value_8 && D_80122470.cue_0->line == scene->value_1C)
    {
        func_8010C5D0(wp, D_80122470.cue_0->index);
        D_80122470.cue_0++;
    }
    if (D_80122470.cue_4->u.end != 0xFF && D_80122470.cue_4->u.scene == scene->u_8.value_8 && D_80122470.cue_4->line == scene->value_1C)
    {
        func_8010C644(wp, D_80122470.cue_4->index);
        D_80122470.cue_4++;
    }
    func_8010C6B8(wp);
}

void func_8010C930(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.v.z  = 0x200;
    wp->scale.v.y  = 0x200;
    wp->scale.v.x  = 0x200;
    wp->anim_AC    = 0;
    wp->value_78   = 0;
    wp->rotation.y = 0x8A5;
    func_800322A8(wp, wp->anim_AC, 0);
    D_80122470.cue_0 = D_8011C338;
    D_80122470.cue_4 = D_8011C3A4;
    wp->routine_0++;
}

void func_8010C9C8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0;
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_8010CA18(STAGE_OBJ *wp)
{
    wp->anim_AC      = 0x10;
    wp->u_E.b.byte_E = 0;
    func_800322A8(wp, wp->anim_AC, 0);
    wp->routine_2++;
}

void func_8010CA64(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x32)
    {
        STAGE_SCENE.slot_24[3]->routine_1 = 1;
        STAGE_SCENE.slot_24[3]->routine_2 = 0;
    }
    if (*wp->anim_98 == 0x3D)
    {
        wp->routine_2++;
    }
}

void func_8010CACC(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x3D)
    {
        wp->routine_2++;
    }
}

void func_8010CAFC(STAGE_OBJ *wp)
{
    wp->anim_AC      = 0x11;
    wp->u_E.b.byte_E = 1;
    func_800322A8(wp, wp->anim_AC, 0);
    wp->routine_2++;
}

void func_8010CB4C(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x17)
    {
        wp->u_C.b.byte_C = 0x1E;
        wp->routine_2++;
    }
}

void func_8010CB7C(STAGE_OBJ *wp)
{
    sint8 temp_v0;

    temp_v0          = (uint8)wp->u_C.b.byte_C - 1;
    wp->u_C.b.byte_C = temp_v0;
    if ((temp_v0 << 0x18) == 0)
    {
        wp->routine_2++;
    }
}

void func_8010CBB0(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x15D17;
    if (*wp->anim_98 == 0x2C)
    {
        wp->routine_2++;
    }
}

void func_8010CBF4(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x3D)
    {
        wp->anim_AC      = 0x12;
        wp->u_E.b.byte_E = 2;
        func_800322A8(wp, wp->anim_AC, 0);
        wp->routine_2++;
    }
}

void func_8010CC58(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x20)
    {
        wp->u_C.b.byte_D = 0x1E;
        wp->routine_2++;
    }
}

void func_8010CC88(STAGE_OBJ *wp)
{
    if (--wp->u_C.b.byte_D == 0)
    {
        STAGE_SCENE.slot_24[3]->routine_1 = 0;
        STAGE_SCENE.slot_24[3]->routine_2 = 0;
        wp->anim_AC                       = 0x13;
        func_800322A8(wp, 0x13, 0);
        wp->routine_2++;
    }
}

void func_8010CD04(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x2D)
    {
        wp->anim_AC = 0x14;
        func_800322A8(wp, 0x14, 0);
        wp->routine_2++;
    }
}

void func_8010CD60(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x30000;
    if (*wp->anim_98 == 0x3B)
    {
        wp->routine_2++;
    }
}

void func_8010CDA0(void)
{
}

void func_8010CDA8(STAGE_OBJ *wp)
{
    D_8011C440[wp->routine_2](wp);
}

void func_8010CDE4(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x15;
    func_800322A8(wp, 0x15, 0);
    wp->routine_2++;
}

void func_8010CE2C(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x50000;
}

void func_8010CE40(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    D_8011C474[wp->routine_2](wp);
    temp_v1 = *wp->anim_98;
    if ((temp_v1 == 2) || (temp_v1 == 0x16))
    {
        Sound_call(0x90, 0, 0x64);
    }
}

void func_8010CEB8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x16;
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_8010CF0C(ST00_OBJ *wp)
{
    wp->anim_AC = 0x17;
    func_800322A8(wp, 0x17, 0);
    wp->part_100[2].value_0 = 0x14;
    wp->part_100[5].value_0 = 0x15;
    wp->routine_2++;
}

void func_8010CF60(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x78)
    {
        STAGE_SCENE.slot_24[1]->routine_1  = 1;
        STAGE_SCENE.slot_24[15]->routine_1 = 1;
        func_80031988(STAGE_SCENE.slot_24[16]);
    }
    if (*wp->anim_98 == 0x7F)
    {
        wp->anim_AC = 0x18;
        func_800322A8(wp, 0x18, 0);
    }
}

void func_8010CFF8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_8010CF0C(wp);
        return;
    }
    func_8010CF60(wp);
}

void func_8010D038(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x19;
        func_800322A8(wp, 0x19, 0);
        STAGE_SCENE.slot_24[1]->routine_1 = 2;
        wp->routine_2++;
    }
}

void func_8010D09C(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x30;
    func_800322A8(wp, 0x30, 0);
    wp->routine_2++;
}

void func_8010D0E4(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x26)
    {
        wp->anim_AC = 0x22;
        func_800322A8(wp, 0x22, 0);
        wp->u_C.b.byte_D = 0x2F;
        wp->routine_2++;
    }
}

void func_8010D144(STAGE_OBJ *wp)
{
    sint8 temp_v0;

    temp_v0          = (uint8)wp->u_C.b.byte_D - 1;
    wp->u_C.b.byte_D = temp_v0;
    if ((temp_v0 << 0x18) == 0)
    {
        wp->routine_2++;
    }
    wp->position_fixed.v.x += 0xFFFE4C42;
}

void func_8010D184(void)
{
}

void func_8010D18C(STAGE_OBJ *wp)
{
    D_8011C47C[wp->routine_2](wp);
}

void func_8010D1C8(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x1A;
    func_800322A8(wp, 0x1AU, 0);
    wp->routine_2++;
}

void func_8010D210(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFF8DB6E;
    if (*wp->anim_98 == 0x15)
    {
        wp->routine_2++;
    }
}

void func_8010D254(void)
{
}

void func_8010D25C(STAGE_OBJ *wp)
{
    D_8011C48C[wp->routine_2](wp);
}

void func_8010D298(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x1B;
        func_800322A8(wp, 0x1BU, 0);
        wp->routine_2++;
    }
}

void func_8010D2EC(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x1C;
    func_800322A8(wp, 0x1CU, 0);
    wp->routine_2++;
}

void func_8010D334(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 9)
    {
        wp->routine_2++;
    }
}

void func_8010D364(STAGE_OBJ *wp)
{
    sint32 temp_a1;

    temp_a1                = wp->position_fixed.v.x;
    wp->position_fixed.v.x = temp_a1 + 0xFFFD8000;
    if (*wp->anim_98 == 0x20)
    {
        wp->position_fixed.v.x = temp_a1;
        wp->routine_2++;
    }
}

void func_8010D3A4(void)
{
}

void func_8010D3AC(STAGE_OBJ *wp)
{
    D_8011C498[wp->routine_2](wp);
}

void func_8010D3E8(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x1D;
    func_800322A8(wp, 0x1DU, 0);
    wp->routine_2++;
}

void func_8010D430(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 8)
    {
        wp->routine_2++;
    }
}

void func_8010D460(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFF70000;
    if (*wp->anim_98 == 0xD)
    {
        wp->routine_2++;
    }
}

void func_8010D4A0(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFF70000;
    wp->position_fixed.v.y += 0x73333;
    if (*wp->anim_98 == 0x26)
    {
        wp->routine_2++;
    }
}

void func_8010D4F4(void)
{
}

void func_8010D4FC(STAGE_OBJ *wp)
{
    D_8011C4A8[wp->routine_2](wp);
}

void func_8010D538(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x1E;
    func_800322A8(wp, 0x1E, 0);
    wp->routine_2++;
    STAGE_SCENE.slot_24[1]->routine_1 = 3;
}

void func_8010D590(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFE00000;
}

void func_8010D5A4(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    D_8011C4BC[wp->routine_2](wp);
    temp_v1 = *wp->anim_98;
    if ((temp_v1 == 3) || (temp_v1 == 0xB))
    {
        Sound_call(0x91, 0, 0x64);
    }
}

void func_8010D61C(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x1F;
    func_800322A8(wp, 0x1FU, 0);
    wp->routine_2++;
}

void func_8010D664(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFDF8000;
    if (*wp->anim_98 == 0x28)
    {
        wp->routine_2++;
    }
}

void func_8010D6A8(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFEC0000;
    if (*wp->anim_98 == 0x3C)
    {
        wp->routine_2++;
    }
}

void func_8010D6E8(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x3F)
    {
        wp->routine_2++;
    }
}

void func_8010D718(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x20;
    func_800322A8(wp, 0x20, 0);
    wp->routine_2++;
}

void func_8010D760(void)
{
}

void func_8010D768(STAGE_OBJ *wp)
{
    D_8011C4C4[wp->routine_2](wp);
}

void func_8010D7A4(STAGE_OBJ *wp)
{
    D_8011C4DC[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    if (wp->u_C.b.byte_C == 0)
    {
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}

void func_8010D824(STAGE_OBJ *wp)
{
    STAGE_PL.value_2C = wp->position.x;
    STAGE_PL.value_2E = wp->position.y;
    STAGE_PL.value_30 = wp->position.z;
    if (wp->routine_0 != 0)
    {
        func_8010D7A4(wp);
        func_8010C820(wp);
    }
    else
    {
        func_8010C930(wp);
    }
    STAGE_PL.position.x = wp->position.x;
    STAGE_PL.position.y = wp->position.y;
    STAGE_PL.position.z = wp->position.z;
}

void func_8010D8C0(STAGE_OBJ *wp, sint32 index)
{
    D_80122478[0] = D_8011C5CC[index];
    D_8012247C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80122478[0]->id, 0x2A, 0x33, 6));
}

void func_8010D934(STAGE_OBJ *wp, sint32 index)
{
    D_80122480[0] = D_8011C5F4[index];
    D_80122484[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80122480[0]->id, 0x2A, 0x33, 6));
}

void func_8010D9A8(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    STAGE_MOUTH *step;
    sint16 *cnt;

    cnt = D_8012247C;
    (*cnt)++;
    p = D_80122478_S;
    if (*cnt == p->count)
    {
        D_80122478_S = p + 1;
        if (D_80122478_S->count <= 0)
        {
            D_80122478_S += D_80122478_S->count;
        }
        step = D_80122478_S;
        *cnt = 0;
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(step->id, 0x2A, 0x33, 6));
    }
    cnt = D_80122484;
    (*cnt)++;
    p = D_80122480_S;
    if (*cnt == p->count)
    {
        D_80122480_S = p + 1;
        if (D_80122480_S->count <= 0)
        {
            D_80122480_S += D_80122480_S->count;
        }
        step = D_80122480_S;
        *cnt = 0;
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(step->id, 0x2A, 0x33, 6));
    }
}

void func_8010DAE0(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80122488.cue_0->u.end != 0xFF && D_80122488.cue_0->u.scene == scene->u_8.value_8 && D_80122488.cue_0->line == scene->value_1C)
    {
        func_8010D8C0(wp, D_80122488.cue_0->index);
        D_80122488.cue_0++;
    }
    if (D_80122488.cue_4->u.end != 0xFF && D_80122488.cue_4->u.scene == scene->u_8.value_8 && D_80122488.cue_4->line == scene->value_1C)
    {
        func_8010D934(wp, D_80122488.cue_4->index);
        D_80122488.cue_4++;
    }
    func_8010D9A8(wp);
}

void func_8010DBF0(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->anim_AC = 0;
    func_800322A8(wp, 0, 0);
    wp->scale.v.z    = 0x200;
    wp->scale.v.y    = 0x200;
    wp->scale.v.x    = 0x200;
    D_80122488.cue_0 = D_8011C630;
    D_80122488.cue_4 = D_8011C684;
    wp->scale.v.pad  = 0x2108;
    wp->value_78     = 0;
    wp->routine_0++;
}

void func_8010DC84(STAGE_OBJ *wp)
{
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010DCAC(STAGE_OBJ *wp)
{
    wp->anim_AC = 2;
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_800322A8(wp, wp->anim_AC, 0);
    wp->routine_2++;
}

void func_8010DD04(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, 0x50, 0, 0);
}

void func_8010DD2C(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    D_8011C6EC[wp->routine_2](wp);
    temp_v1 = *wp->anim_98;
    if ((temp_v1 == 6) || (temp_v1 == 0x16))
    {
        Sound_call(0x90, 0, 0x64);
    }
}

void func_8010DDA4(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x12;
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_800322A8(wp, wp->anim_AC, 0);
    wp->routine_2++;
}

void func_8010DDFC(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 5)
    {
        wp->anim_AC = 0;
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010DE60(void)
{
}

void func_8010DE68(STAGE_OBJ *wp)
{
    D_8011C6F4[wp->routine_2](wp);
}

void func_8010DEA4(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x13;
    func_800322A8(wp, 0x13, 0);
    wp->routine_2++;
}

void func_8010DEEC(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x59)
    {
        wp->anim_AC = 0x14;
        func_800322A8(wp, 0x14, 0);
        wp->u_E.b.byte_E = 9;
        wp->u_E.b.byte_F = 5;
        wp->routine_2++;
    }
}

void func_8010DF54(void)
{
}

void func_8010DF5C(STAGE_OBJ *wp)
{
    D_8011C700[wp->routine_2](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010DFB0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x15;
        func_800322A8(wp, 0x15, 0);
        wp->routine_2++;
    }
}

void func_8010E004(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x16;
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_8010E058(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x17;
        func_800322A8(wp, 0x17, 0);
        wp->routine_2++;
    }
}

void func_8010E0AC(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x18;
        func_800322A8(wp, 0x18, 0);
        wp->routine_2++;
    }
    Obj_pos_set(wp, -0x17, 0, 0);
    temp_v1 = *wp->anim_98;
    if ((temp_v1 == 2) || (temp_v1 == 0x25))
    {
        Sound_call(0x90, 0, 0x64);
    }
}

void func_8010E144(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x19;
    func_800322A8(wp, 0x19, 0);
    func_80030150(&wp->position_fixed.v, &wp->position);
    wp->routine_2++;
}

void func_8010E198(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x1A)
    {
        wp->routine_2++;
    }
    Obj_pos_set(wp, -0x17, 0, 0);
}

void func_8010E1E4(STAGE_OBJ *wp)
{
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010E20C(STAGE_OBJ *wp)
{
    D_8011C70C[wp->routine_2](wp);
}

void func_8010E248(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->anim_AC = 0x1C;
        func_800322A8(wp, 0x1CU, 0);
        wp->routine_2++;
    }
}

void func_8010E29C(STAGE_OBJ *wp)
{
    wp->anim_AC = 0x1A;
    func_800322A8(wp, 0x1AU, 0);
    wp->u_C.b.byte_C = 0x2C;
    wp->routine_2++;
}

void func_8010E2E8(STAGE_OBJ *wp)
{
    sint8 temp_v0;

    temp_v0          = (uint8)wp->u_C.b.byte_C - 1;
    wp->u_C.b.byte_C = temp_v0;
    if ((temp_v0 << 0x18) == 0)
    {
        wp->routine_2++;
    }
}

void func_8010E31C(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0xF)
    {
        wp->routine_2++;
    }
}

void func_8010E34C(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0xFFEC0000;
    if (*wp->anim_98 == 0x1A)
    {
        wp->position_fixed.v.y += 0x300000;
        wp->routine_2++;
    }
}

void func_8010E394(STAGE_OBJ *wp)
{
    wp->position_fixed.v.y += 0x300000;
}

void func_8010E3A8(STAGE_OBJ *wp)
{
    D_8011C718[wp->routine_2](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010E3FC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position_fixed.v.x = 0x01F40000;
        wp->position_fixed.v.y = 0xE5EA0000;
        wp->position_fixed.v.z = 0xFB2C0000;
        wp->anim_AC            = 0x1B;
        func_800322A8(wp, 0x1B, 0);
        wp->routine_2++;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_8010E474(STAGE_OBJ *wp)
{
    D_8011C72C[wp->routine_1](wp);
    if (wp->u_C.b.byte_C == 0)
    {
        func_80032488(wp);
    }
    else
    {
        Model_pose_unpack(wp);
        Model_parts_mtx_set_y(wp);
    }
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}

void func_8010E500(STAGE_OBJ *wp)
{
    STAGE_PL.value_2C = wp->position.x;
    STAGE_PL.value_2E = wp->position.y;
    STAGE_PL.value_30 = wp->position.z;
    if (wp->routine_0 != 0)
    {
        func_8010E474(wp);
        func_8010DAE0(wp);
    }
    else
    {
        func_8010DBF0(wp);
    }
    switch (wp->routine_3)
    {
        case 0:
            break;
        case 1:
            if (++wp->u_C.b.byte_D == 4)
            {
                wp->u_C.b.byte_D = 0;
                wp->scale.v.pad += 0x421;
                if (wp->scale.v.pad == 0x4210)
                {
                    wp->routine_3 = 0;
                }
            }
            break;
    }
    STAGE_PL.position.x = wp->position.x;
    STAGE_PL.position.y = wp->position.y;
    STAGE_PL.position.z = wp->position.z;
}

void func_8010E5F8(STAGE_OBJ *wp, sint32 index)
{
    D_80122490[0] = D_8011C784[index];
    D_80122494[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_80122490[0]->id, 0x2A, 0x33, 6));
}

void func_8010E66C(STAGE_OBJ *wp, sint32 index)
{
    D_80122498[0] = D_8011C790[index];
    D_8012249C[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80122498[0]->id, 0x2A, 0x33, 6));
}

void func_8010E6E0(STAGE_OBJ *wp)
{
    STAGE_MOUTH *p;
    STAGE_MOUTH *step;
    sint16 *cnt;

    cnt = D_80122494;
    (*cnt)++;
    p = D_80122490_S;
    if (*cnt == p->count)
    {
        D_80122490_S = p + 1;
        if (D_80122490_S->count <= 0)
        {
            D_80122490_S += D_80122490_S->count;
        }
        step = D_80122490_S;
        *cnt = 0;
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(step->id, 0x2A, 0x33, 6));
    }
    cnt = D_8012249C;
    (*cnt)++;
    p = D_80122498_S;
    if (*cnt == p->count)
    {
        D_80122498_S = p + 1;
        if (D_80122498_S->count <= 0)
        {
            D_80122498_S += D_80122498_S->count;
        }
        step = D_80122498_S;
        *cnt = 0;
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(step->id, 0x2A, 0x33, 6));
    }
}

void func_8010E818(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_801224A0.cue_0->u.end != 0xFF && D_801224A0.cue_0->u.scene == scene->u_8.value_8 && D_801224A0.cue_0->line == scene->value_1C)
    {
        func_8010E5F8(wp, D_801224A0.cue_0->index);
        D_801224A0.cue_0++;
    }
    if (D_801224A0.cue_4->u.end != 0xFF && D_801224A0.cue_4->u.scene == scene->u_8.value_8 && D_801224A0.cue_4->line == scene->value_1C)
    {
        func_8010E66C(wp, D_801224A0.cue_4->index);
        D_801224A0.cue_4++;
    }
    func_8010E6E0(wp);
}

void func_8010E928(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_78       = 0;
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    func_800322A8(wp, 0, 0);
    D_801224A0.cue_0 = D_8011C798;
    D_801224A0.cue_4 = D_8011C7B0;
    wp->routine_0++;
}

void func_8010E9BC(void)
{
}

void func_8010E9C4(STAGE_OBJ *wp)
{
    func_800322A8(wp, 0x10, 0);
    wp->routine_2++;
}

void func_8010EA04(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x18)
    {
        wp->routine_2++;
    }
}

void func_8010EA34(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x50000;
    if (*wp->anim_98 == 0x36)
    {
        func_800322A8(wp, 0x11, 0);
        wp->rotation.y += 0x800;
        wp->routine_2++;
    }
}

void func_8010EAA0(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x50000;
    if (*wp->anim_98 == 0xE)
    {
        wp->routine_2++;
    }
}

void func_8010EAE0(STAGE_OBJ *wp)
{
    wp->position_fixed.v.z += 0x200000;
    if (*wp->anim_98 == 0x1C)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_8010EB44(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = *wp->anim_98;
    if ((temp_v1 == 4) || (temp_v1 == 0xC))
    {
        Sound_call(0x91, 0, 0x64);
    }
    wp->position_fixed.v.z += 0x200000;
}

void func_8010EBA8(STAGE_OBJ *wp)
{
    D_8011C7C4[wp->routine_2](wp);
}

void func_8010EBE4(STAGE_OBJ *wp)
{
    D_8011C7DC[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}

void func_8010EC54(STAGE_OBJ *wp)
{
    STAGE_PL.value_2C = wp->position.x;
    STAGE_PL.value_2E = wp->position.y;
    STAGE_PL.value_30 = wp->position.z;
    if (wp->routine_0 != 0)
    {
        func_8010EBE4(wp);
    }
    else
    {
        func_8010E928(wp);
    }
    func_8010E818(wp);
    STAGE_PL.position.x = wp->position.x;
    STAGE_PL.position.y = wp->position.y;
    STAGE_PL.position.z = wp->position.z;
}

void func_8010ECF0(ST00_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->position_fixed.v.x = 0x02000000;
    wp->position_fixed.v.y = 0xE3FF0000;
    wp->anim_AC            = 0;
    wp->position_fixed.v.z = 0x03000000;
    func_800322A8(wp, wp->anim_AC, 0);
    wp->part_100[2].value_3  = -1;
    wp->part_100[1].value_3  = -1;
    wp->part_100[10].value_0 = 0xD;
    wp->scale.v.x = wp->scale.v.y = wp->scale.v.z = 0x200;
    wp->value_78                                  = 0;
    wp->part_100[0].value_3                       = 0;
    wp->scale.v.pad                               = 0x14A5;
    wp->routine_0++;
}

void func_8010ED88(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_8010EDD4(STAGE_OBJ *wp)
{
    func_800322A8(wp, 0x10, 0);
    wp->routine_2++;
}

void func_8010EE14(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x12)
    {
        func_800322A8(wp, 0x11, 0);
        wp->routine_2++;
    }
    Obj_pos_set(wp, 0x17, 0, 0);
}

void func_8010EE7C(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, 0x17, 0, 0);
}

void func_8010EEA4(STAGE_OBJ *wp)
{
    D_8011C7E4[wp->routine_2](wp);
}

void func_8010EEE0(STAGE_OBJ *wp)
{
    func_800322A8(wp, 0x12, 0);
    wp->routine_2++;
}

void func_8010EF20(STAGE_OBJ *wp)
{
    if (*wp->anim_98 == 0x77)
    {
        func_800322A8(wp, 0x14, 0);
        wp->routine_2++;
    }
}

void func_8010EF74(void)
{
}

void func_8010EF7C(STAGE_OBJ *wp)
{
    D_8011C7F0[wp->routine_2](wp);
}

void func_8010EFB8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x13, 0);
        wp->routine_2++;
    }
}

void func_8010F004(STAGE_OBJ *wp)
{
    D_8011C7FC[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    Model_Shadow_Trans(wp, 0x190, 0x200, 0);
    func_80032488(wp);
}

void func_8010F074(STAGE_OBJ *wp)
{
    if (wp->routine_0 != 0)
    {
        func_8010F004(wp);
        return;
    }
    func_8010ECF0((ST00_OBJ *)wp);
}

void func_8010F0B4(ST00_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_78             = 0;
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x42100200;
    wp->part_100[2].value_3  = -1;
    wp->part_100[1].value_3  = -1;
    wp->part_100[0].value_3  = 0;
    wp->part_100[10].value_0 = 0xD;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_8010F140(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
        return;
    }
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_8010F1A0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x15, 0);
        wp->routine_2++;
        return;
    }
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_8010F200(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
        return;
    }
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_8010F260(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_8010F2AC(STAGE_OBJ *wp)
{
    func_80030150(&wp->position_fixed.v, &wp->position);
    D_8011C80C[wp->routine_1](wp);
    Model_Shadow_Trans(wp, 0x190, 0x200, 0);
}

void func_8010F314(STAGE_OBJ *wp)
{
    if (wp->routine_0 != 0)
    {
        func_8010F2AC(wp);
        return;
    }
    func_8010F0B4(wp);
}
