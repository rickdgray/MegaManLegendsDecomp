#include "common.h"
#include "st13.h"

void func_80111814(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_801185D0[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    ST13_SP_13C = ctl->timer_38;
    func_8003346C(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0x50, 0, 0x8000, wp->value_1, &ctl->hit_14,
                      ctl->value_8 | 0x5880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_801119CC(STAGE_STCOM15_WORK_4E0 *wp)
{
    sint16 ground;
    sint16 floor;

    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_0             = 0x2E;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    *(uint32 *)&wp->ctl.value_8 = 0;
    wp->ctl.hit_14              = 0;
    wp->ctl.value_18            = 0;
    func_80036478(wp->ctl.track_24, D_8009884C[wp->kind_2][wp->param_D].track_F, -0x60);
    *(uint32 *)&wp->ctl.timer_34 = 0;
    *(uint32 *)&wp->ctl.timer_38 = 0;
    wp->ctl.u_3C.flag            = wp->position.pad;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_8009884C[wp->kind_2][wp->param_D].life_8
                                                       << 4;
    wp->data_78                                      = D_8011860C;
    wp->data_10                                      = NULL;
    if (!(wp->variant_3 & 0x7F))
    {
        ground                    = func_80049448(wp);
        (&wp->ctl.u_3C.flag)[1]   = ground; // the union's second halfword
        wp->position.y            = ground;
        wp->position_fixed.y      = ground << 16;
        wp->routine_0             = 1;
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
        func_800322A8(wp, 1, 0);
    }
    else
    {
        floor                     = func_80048E6C(wp);
        (&wp->ctl.u_3C.flag)[1]   = floor; // the union's second halfword
        wp->position.y            = floor;
        wp->position_fixed.y      = floor << 16;
        wp->routine_0             = 1;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        func_800322A8(wp, 0, 0);
    }
    wp->scale.v.pad = 0x4210;
}

void func_80111B50(STAGE_STCOM15_WORK_4E0 *wp)
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
        func_801134E4(wp);
    }
    if (Game_work.value_50 == 0)
    {
        dx = wp->position.x - D_80118618;
        dz = wp->position.z - D_8011861A;
        if (!(ctl->flags_0 & 0x40) && wp->life_6E > 0 && (dx >= D_8011861C || dz >= D_8011861E))
        {
            wp->routine_1             = 0xB;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->flags_0 |= 0x40;
        }
    }
    D_801185DC[wp->routine_1](wp);
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
                    func_8011341C(wp);
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

void func_80111E70(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80111E90(STAGE_STCOM15_WORK_4E0 *wp)
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

void func_80111F88(STAGE_STCOM15_WORK_4E0 *wp)
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
                if (wp->routine_3 >= 4 &&
                    ((wp->variant_3 & 0x80) || Sce_flag_test(wp->ctl.u_3C.flag)))
                {
                    wp->ctl.flags_0 |= 1;
                }
                wp->routine_2 = 1;
                ctl->timer_4  = ctl->level_6;
            }
            break;
    }
    if (((wp->variant_3 & 0x80) || Sce_flag_test(ctl->u_3C.flag)) &&
        (wp->value_80 <= 0x1FFFF || (ctl->hit_14 & 0xFFFFFF)))
    {
        wp->routine_1             = 4;
        *(uint16 *)&wp->routine_2 = 0;
        wp->anim_AC               = wp->anim_prev_AD;
        ctl->flags_0 &= ~1;
    }
}

void func_80112180(STAGE_STCOM15_WORK_4E0 *wp)
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
            if (func_8004B414(wp) & 0xF00)
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

void func_80112348(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    ST13_SHOT *shot;
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
                shot = (ST13_SHOT *)Open_SHL_WORK();
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
                if (wp->routine_3 < D_8009884C[wp->kind_2][wp->param_D].value_B)
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
            hit = func_8004B414(wp);
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

void func_80112638(STAGE_STCOM15_WORK_4E0 *wp)
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
            (&ctl->u_3C.flag)[1] = func_80048E6C(wp);
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
            hit                  = func_8004B414(wp);
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

void func_80112850(STAGE_STCOM15_WORK_4E0 *wp)
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
            (&ctl->u_3C.flag)[1] = func_80049448(wp); // the union's second halfword: the ground
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
            hit                  = func_8004B414(wp);
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

void func_80112A54(STAGE_STCOM15_WORK_4E0 *wp)
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

void func_80112B64(STAGE_STCOM15_WORK_4E0 *wp)
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
            (&ctl->u_3C.flag)[1] = func_80048E6C(wp);
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
            hit                  = func_8004B414(wp);
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

void func_80112D7C(STAGE_STCOM15_WORK_4E0 *wp)
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
            (&ctl->u_3C.flag)[1] = func_80048E6C(wp);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->velocity.v.y = 4 - ctl->timer_4;
                Obj_pos_set(wp, 0, wp->velocity.v.y << 7, 0);
                if (!(func_8004B414(wp) & 0x2000))
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
            hit = func_8004B414(wp);
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

void func_80112F78(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STAGE_PL_VIEW *pl;
    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 4;
            wp->turn_66   = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 4;
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

void func_8011305C(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    uint16 ground;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 7;
            wp->turn_66   = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 4;
            wp->velocity.v.y = -0x200;
            wp->accel.y      = 0x40;
            ctl->timer_4     = 0x10;
            ctl->value_8     = 0;
            Sound_call2(0xD1, &wp->position);
            (&ctl->u_3C.flag)[1] = func_80048E6C(wp); // the union's second halfword: the ground
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            Obj_pos_set(wp, 0, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel.y;
            if (!(func_8004B414(wp) & 0x1000) && wp->position.y < (sint16)(&ctl->u_3C.flag)[1])
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

void func_801131F8(STAGE_STCOM15_WORK_4E0 *wp)
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
            D_80118D2C.y    = 0;
            D_80118D2C.x    = D_80118620.x + (D_80118624.x >> 1);
            D_80118D2C.z    = D_80118620.z + (D_80118624.z >> 1);
            wp->ctl.timer_4 = 0x10;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~4;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y = (wp->rotation.y +
                                  Muku(&wp->position, &D_80118D2C, wp->rotation.y, 0x80)) &
                                 0xFFF;
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 3;
            ctl->value_8  = 0;
            ctl->timer_4  = 300;
            // fall through
        case 2:
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &D_80118D2C, wp->rotation.y, 0x20)) &
                0xFFF;
            Obj_pos_set(wp, 0x70, 0, 0);
            func_8004B414(wp);
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD5, &wp->position);
            }
            dx = wp->position.x - D_80118620.x;
            dz = wp->position.z - D_80118620.z;
            if (--ctl->timer_4 < 0 || ((uint32)dx < D_80118624.x && (uint32)dz < D_80118624.z))
            {
                ctl->flags_0 = (ctl->flags_0 | 5) & ~0x40;
            }
            break;
    }
}

sint32 func_8011341C(STAGE_STCOM15_WORK_4E0 *wp)
{
    sint16 sum;
    sint16 i;
    uint8 *chance;
    chance = D_80118628;
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

sint32 func_801134E4(STAGE_STCOM15_WORK_4E0 *wp)
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
                damage          = D_8009884C[wp->kind_2][wp->param_D].value_9 << 4;
            }
            if (wp->ctl.flags_0 & 4)
            {
                wp->ctl.timer_A += damage;
                if (wp->ctl.timer_A < D_8009884C[wp->kind_2][wp->param_D].value_9 << 4)
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
                            if (wp->position.y == func_80048E6C(wp))
                            {
                                wp->routine_1 = 6;
                                break;
                            }
                            if (wp->position.y == func_80049448(wp))
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
                Sound_call2((wp->ctl.timer_A >= D_8009884C[wp->kind_2][wp->param_D].value_9 << 4)
                                ? 0xA2
                                : 0xA0,
                            &wp->position);
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

void func_80113758(sint32 index)
{
    D_80118D34.index_E = 0;
    D_80118D34.shape_C = 0;
    D_80118D34.prev_D  = -1;
    D_80118D34.mouth_4 = D_801186E0[index];
}

void func_80113794(sint32 index)
{
    D_80118D34.index_11 = 0;
    D_80118D34.shape_F  = 0;
    D_80118D34.prev_10  = -1;
    D_80118D34.eyes_8   = D_801186F0[index];
}

void func_801137D0(void)
{
    STAGE_PL_VIEW *pl;
    STAGE_FACE *face;

    pl   = &STAGE_PL;
    face = &D_80118D34;
    switch (face->mouth_4[face->index_E + 1])
    {
        case 0x7E:
            break;
        case 0x7F:
            face->index_E = 0;
            break;
        default:
            face->index_E++;
            break;
    }
    face->prev_D = face->shape_C = face->mouth_4[face->index_E];
    switch (face->eyes_8[face->index_11 + 1])
    {
        case 0x7E:
            break;
        case 0x7F:
            face->index_11 = 0;
            break;
        default:
            face->index_11++;
            break;
    }
    face->prev_10 = face->shape_F = face->eyes_8[face->index_11];
    pl->value_168                 = face->shape_C;
    pl->value_169                 = face->shape_F;
}

void func_801138B8(void)
{
}

void func_801138C0(STAGE_ROOM *wp)
{
    uint8 a;
    uint8 b;

    if (wp->frame_10 == 1)
    {
        a                  = STAGE_PL.value_170;
        b                  = STAGE_PL.value_171;
        STAGE_PL.value_448 = 0x81;
        STAGE_PL.value_171 = 0;
        STAGE_PL.value_170 = 0;
        D_80118D48         = a;
        D_80118D4C         = b;
    }
}

void func_80113910(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        STAGE_PL.value_448 = 0x82;
        func_80113758(0);
        func_80113794(0);
    }
    func_801137D0();
}

void func_80113958(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_8011862C;
    wp->tbl_A4 = D_801186F4;
}

void func_801139A8(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801139E8(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->fixed_428.x = 0x1040000;
                pl->fixed_428.y = 0xFF9F0000;
                pl->fixed_428.z = 0xF00000;
                pl->flags_bd |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->value_440             = 0;
                pl->value_444             = 0;
                *(sint16 *)&pl->value_442 = -0x800; // a signed store (addiu)
                wp->routine_4++;
            }
            break;
        case 1:
            wp->routine_4++;
            Cd_xa_play_id(0x20010020);
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 5;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 4:
            func_80017C30(3);
            func_80113958(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(10);
                Sce_flag_on(0x21);
                wp->routine_4 = 10;
            }
            // fall through
        case 10:
            func_801139A8((STAGE_ROOM_WORK *)wp);
            func_8001EC0C();
            Sce_event_update();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                D_800C356C    = 2;
                D_800C356E    = 0x12;
                D_800C356F    = 0;
                D_800C3560    = 0;
                D_800C3562    = 0;
                D_800C3564    = 0;
                D_800C356A    = 0;
                D_800C356D    = 0;
                wp->flags_0   = 0;
                D_800C3571    = 0xFF;
                D_800C3570    = 0xFF;
                pl->value_170 = D_80118D48;
                pl->value_171 = D_80118D4C;
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
                wp->routine_4 = 0;
            }
            break;
    }
}
