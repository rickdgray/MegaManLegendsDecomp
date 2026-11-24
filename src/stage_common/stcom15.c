#include "common.h"
#include "stage_common/stcom15.h"

// Shared stage code, linked into 5 stages: r3_st00, r3_st09, r3_st14, r3_st1a and r3_st1d. Each
// stage compiles this file against its own copy of the assembly (TARGET_ASM, set by
// tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom15"

void stcom15_func_0000(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    stcom15_D_0000[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 4))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0x50, 0, 0x8000, wp->value_1, &ctl->hit_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void stcom15_func_01A4(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;
    sint16 life;

    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->velocity.words[0]   = 0;
    wp->velocity.words[1]   = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    ctl                = &wp->ctl;
    if (wp->variant_3 & 0x20)
    {
        ctl->flags_0 = 0;
    }
    else
    {
        ctl->flags_0 = 0xE;
    }
    *(uint32 *)&ctl->timer_4 = 0;
    if (wp->param_C & 0x10)
    {
        ctl->level_6 = 1;
    }
    *(uint32 *)&ctl->value_8 = 0;
    ctl->hit_14              = 0;
    ctl->value_18            = 0;
    Track_reset(ctl->track_24, D_80098844[wp->kind_2][ctl->level_6].track_F, -0x60);
    ctl->timer_34    = 0;
    ctl->timer_36    = 0;
    ctl->timer_38    = 4;
    ctl->flag_3A     = wp->position.pad;
    ctl->effect_40   = NULL;
    ctl->turn_44     = 0;
    ctl->hit_48      = 0;
    life             = (D_80098844[wp->kind_2][ctl->level_6].life_8 << 4) * ((wp->param_F & 0x7F) + 1);
    wp->data_10      = NULL;
    wp->data_78      = stcom15_D_0038;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = life;
    if (wp->variant_3 & 0x40)
    {
        wp->routine_0             = 1;
        wp->routine_1             = 8;
        *(uint16 *)&wp->routine_2 = 0;
        wp->position.y += 0x20;
        wp->position_fixed.y = wp->position.y << 16;
        func_800322A8(wp, 0xC, 0);
    }
    else
    {
        wp->position.y            = Obj_ceiling_height_get(wp);
        wp->position_fixed.y      = wp->position.y << 16;
        wp->routine_0             = 1;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        func_800322A8(wp, 0, 0);
    }
    wp->scale.v.pad = 0x4210;
}

void stcom15_func_0394(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    if (!(wp->variant_3 & 0x20) && func_8003648C(ctl->track_24, wp))
    {
        wp->ctl.flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 2)
    {
        stcom15_func_1F44(wp);
    }
    stcom15_D_000C[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 1:
                wp->routine_1 = wp->param_E;
                break;
            case 6:
                if (wp->life_6E <= 50)
                {
                    wp->routine_1 = 5;
                }
                else if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 9;
                }
                else
                {
                    stcom15_func_1D40(wp);
                }
                break;
            default:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 9;
                }
                else
                {
                    stcom15_func_1D40(wp);
                }
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        wp->variant_3 &= ~0x40;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_34 != 0)
    {
        ctl->timer_34--;
    }
    if (ctl->timer_36 != 0)
    {
        ctl->timer_36--;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if ((ctl->flags_0 & 0x40) && --ctl->timer_38 < 0)
    {
        ctl->effect_40 = func_80031618();
        if (ctl->effect_40 != NULL)
        {
            ctl->effect_40->flags_0         = 5;
            ctl->effect_40->kind_2          = 0x80;
            ctl->effect_40->variant_3       = 0x41;
            ctl->effect_40->sprite.position = wp->position;
        }
        func_80031824(wp);
        func_80047228(wp, &wp->joints_180[0], ctl->level_6);
        Sound_call2(0xA1, &wp->joints_180[0]);
    }
}

void stcom15_func_05F8(STCOM15_WORK *wp)
{
    func_80031824(wp);
}

void stcom15_func_0618(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            if (wp->variant_3 & 0x80)
            {
                wp->routine_2 = 2;
            }
            wp->anim_AC     = 0;
            wp->ctl.timer_4 = 30;
            wp->ctl.value_8 = 0;
            wp->variant_3 &= ~0x80;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
        case 2:
            wp->ctl.flags_0 |= 0x20;
            if (wp->variant_3 & 0x20)
            {
                if (Sce_flag_test(wp->ctl.flag_3A))
                {
                    wp->routine_1             = 3;
                    *(uint16 *)&wp->routine_2 = 0;
                }
            }
            else if (wp->value_80 <= 0x31FFFF || (wp->ctl.hit_14 & 0xFFFFFF))
            {
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void stcom15_func_0748(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            wp->turn_66   = (uint32)STCOM_ABS(Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800)) >> 3;
            ctl->timer_4  = 8;
            ctl->value_8  = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            ctl->turn_44   = Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->turn_66);
            wp->rotation.y = (wp->rotation.y + ctl->turn_44) & 0xFFF;
            break;
    }
}

void stcom15_func_0874(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (wp->value_A6 == 1)
            {
                Sound_call2(0xB0, &wp->position);
            }
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            Obj_pos_set(wp, 0x34, 0, 0);
            ctl->hit_48          = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                if (ctl->flags_0 & 0x10)
                {
                    wp->param_E = 4;
                }
                else
                {
                    wp->param_E = 2;
                }
            }
            else if (ctl->hit_48 & 0xF00)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                if (ctl->flags_0 & 0x10)
                {
                    wp->param_E = 4;
                }
                else
                {
                    wp->param_E = 2;
                }
            }
            else if (ctl->flags_0 & 0x10)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void stcom15_func_0A30(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.hit_14 & 0x2000000)
    {
        wp->ctl.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 2;
            wp->turn_64   = 0;
            ctl->timer_4  = 5;
            ctl->value_8  = D_80098844[wp->kind_2][ctl->level_6].value_A;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            ctl->timer_4  = 5;
            // fall through
        case 2:
            if (--ctl->timer_4 <= 0)
            {
                wp->routine_2 = 3;
                Sound_call2(0xB4, &wp->position);
                if (ctl->flags_0 & 0x20)
                {
                    ctl->timer_4 = wp->param_D;
                    ctl->flags_0 &= ~0x20;
                }
                else
                {
                    ctl->timer_4 = 45;
                }
            }
            break;
        case 3:
            if (ctl->timer_4 < 4)
            {
                wp->routine_2 = 4;
                wp->turn_64   = 0x100;
            }
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 5;
                wp->anim_AC++;
                ctl->timer_4 = 10;
                ctl->value_8 = 0;
            }
            else
            {
                if (ctl->hit_14 & 0x2000000)
                {
                    wp->routine_1             = 6;
                    *(uint16 *)&wp->routine_2 = 0;
                    break;
                }
                ctl->turn_44   = Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->turn_64);
                wp->rotation.y = (wp->rotation.y + ctl->turn_44) & 0xFFF;
                Obj_pos_set(wp, 0x300, 0, 0);
                ctl->hit_48          = Obj_map_push_out(wp);
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
                {
                    wp->routine_1             = 8;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->variant_3 |= 0x40;
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                    ctl->timer_4       = -1;
                }
                if (ctl->hit_48 & 0xF00)
                {
                    ctl->timer_4 = -1;
                }
                break;
            }
            // fall through
        case 5:
            if (wp->variant_3 & 0x20)
            {
                func_80031824(wp);
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->timer_34 = 30;
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void stcom15_func_0D54(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 21;
            ctl->timer_4  = 13;
            ctl->value_8  = 0;
            Sound_call2(0xB1, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                if (ctl->level_6 != 0)
                {
                    ctl->timer_4 = 0;
                }
                else
                {
                    ctl->timer_4 = 16;
                }
            }
            else
            {
                Obj_pos_set(wp, -0x70, 0, 0);
                Obj_map_push_out(wp);
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
                {
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 <= 0)
            {
                wp->routine_2 = 3;
                wp->anim_AC++;
                ctl->timer_4 = 11;
                stcom15_func_1E0C(wp);
            }
            break;
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 4;
                ctl->timer_4  = 6;
            }
            else
            {
                Obj_pos_set(wp, -ctl->timer_4 * 32, 0, 0);
                Obj_map_push_out(wp);
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
                {
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                }
                break;
            }
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->timer_34 = D_80098844[wp->kind_2][ctl->level_6].value_C;
                ctl->flags_0 |= 1;
            }
            else
            {
                Obj_pos_set(wp, 0xE0, 0, 0);
                Obj_map_push_out(wp);
                wp->position.y       = Obj_ceiling_height_get(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
                {
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                }
            }
            break;
    }
}

void stcom15_func_0FE0(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.hit_14 & 0x2000000)
    {
        wp->ctl.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 4;
            wp->velocity.v.x = (-rsin(wp->rotation.y) * 0x20) >> 12;
            wp->velocity.v.y = 0x20;
            wp->accel.y      = 0x10;
            wp->velocity.v.z = (-rcos(wp->rotation.y) * 0x20) >> 12;
            wp->ctl.timer_4  = 115;
            wp->ctl.value_8  = D_80098844[wp->kind_2][wp->ctl.level_6].value_A;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            if (wp->value_A6 == 1)
            {
                Sound_call2(0xB5, &wp->position);
            }
            if (--ctl->timer_4 < 0 || (ctl->hit_14 & 0x2000000))
            {
                ctl->value_8  = 0;
                wp->routine_2 = 2;
                ctl->timer_4  = 2;
            }
            else
            {
                if (wp->life_6E <= 0)
                {
                    ctl->flags_0 |= 1;
                    break;
                }
                if (ctl->timer_4 < 100)
                {
                    wp->position_fixed.x += wp->velocity.v.x << 16;
                    if (wp->position.y != Obj_ceiling_height_get(wp))
                    {
                        wp->position_fixed.y += wp->velocity.v.y << 16;
                        wp->velocity.v.y += wp->accel.y;
                    }
                    else
                    {
                        wp->velocity.v.y = 0x20;
                    }
                    wp->position_fixed.z += wp->velocity.v.z << 16;
                    func_80030150(&wp->position_fixed, &wp->position);
                }
                ctl->hit_48 = Obj_map_push_out(wp);
                if (ctl->hit_48 != 0)
                {
                    if (ctl->hit_48 & 0xF00)
                    {
                        Sound_call2(0xDE, &wp->position);
                    }
                    if (ctl->hit_48 & 0x100)
                    {
                        wp->velocity.v.x = -STCOM_ABS(wp->velocity.v.x);
                    }
                    else if (ctl->hit_48 & 0x200)
                    {
                        wp->velocity.v.x = STCOM_ABS(wp->velocity.v.x);
                    }
                    if (ctl->hit_48 & 0x400)
                    {
                        wp->velocity.v.z = -STCOM_ABS(wp->velocity.v.z);
                    }
                    else if (ctl->hit_48 & 0x800)
                    {
                        wp->velocity.v.z = STCOM_ABS(wp->velocity.v.z);
                    }
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->life_6E   = 0;
                ctl->timer_38 = 0;
                ctl->flags_0 |= 0x41;
            }
            break;
    }
}

void stcom15_func_12E8(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 6;
            wp->ctl.timer_4 = 10;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
            }
            else
            {
                wp->velocity.v.y = 10 - ctl->timer_4;
            }
            // fall through
        case 2:
            Obj_pos_set(wp, 0, wp->velocity.v.y << 7, 0);
            if ((Obj_map_push_out(wp) & 0x1000) && ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void stcom15_func_13E8(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 7;
            wp->velocity.v.x = -16;
            wp->ctl.timer_4  = stcom15_D_0044[0];
            wp->ctl.value_8  = 0;
            wp->ctl.flags_0 &= ~8;
            if (wp->life_6E <= 0)
            {
                wp->ctl.flags_0 &= ~4;
            }
            // fall through
        case 1:
            if (ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
            }
            // fall through
        case 2:
            ctl->timer_4--;
            wp->velocity.v.y = (stcom15_D_0044[wp->routine_3 + 1] - ctl->timer_4) << 3;
            Obj_pos_set(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            ctl->hit_48 = Obj_map_push_out(wp);
            if (ctl->hit_48 != 0)
            {
                if (ctl->hit_48 & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if (ctl->hit_48 & 0x1000)
                {
                    Sound_call2(0xDE, &wp->position);
                    wp->routine_3 += 2;
                    if (wp->routine_3 < 10)
                    {
                        wp->routine_2    = 1;
                        wp->velocity.v.x = -16;
                        wp->anim_AC++;
                        ctl->timer_4 = stcom15_D_0044[wp->routine_3];
                        ctl->flags_0 |= 8;
                    }
                    else if (wp->life_6E <= 0)
                    {
                        ctl->flags_0 |= 1;
                    }
                    else
                    {
                        wp->routine_2 = 3;
                        wp->anim_AC   = 17;
                        ctl->timer_4  = 18;
                    }
                }
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->ctl.flags_0 |= 9;
            }
            else
            {
                wp->ctl.turn_44 = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80);
                wp->rotation.y  = (wp->rotation.y + wp->ctl.turn_44) & 0xFFF;
            }
            break;
    }
}

void stcom15_func_1620(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 12;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~8;
            if (wp->variant_3 & 0x40)
            {
                wp->velocity.v.x = 8;
                wp->ctl.steps_3C = stcom15_D_005C;
                wp->ctl.timer_4  = wp->ctl.steps_3C[0];
                wp->ctl.rand_2   = 7;
                wp->ctl.value_8  = D_80098844[wp->kind_2][wp->ctl.level_6].value_B;
            }
            else
            {
                wp->velocity.v.x = 16;
                wp->ctl.steps_3C = stcom15_D_0050;
                wp->ctl.timer_4  = wp->ctl.steps_3C[0];
            }
            if (wp->life_6E <= 0)
            {
                ctl->flags_0 &= ~4;
            }
            // fall through
        case 1:
            if (ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
            }
            // fall through
        case 2:
            ctl->timer_4--;
            wp->velocity.v.y = (ctl->steps_3C[wp->routine_3 + 1] - ctl->timer_4) << 3;
            Obj_pos_set(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            ctl->hit_48 = Obj_map_push_out(wp);
            if (ctl->hit_48 != 0)
            {
                if (ctl->hit_48 & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if (ctl->hit_48 & 0x1000)
                {
                    Sound_call2(0xDE, &wp->position);
                    wp->routine_3 += 2;
                    if (wp->routine_3 < 10)
                    {
                        wp->routine_2 = 1;
                        wp->anim_AC++;
                        if (wp->variant_3 & 0x40)
                        {
                            wp->velocity.v.x = 8;
                        }
                        else
                        {
                            wp->velocity.v.x = 16;
                        }
                        ctl->timer_4 = ctl->steps_3C[wp->routine_3];
                        ctl->flags_0 |= 8;
                    }
                    else if (wp->life_6E <= 0)
                    {
                        ctl->flags_0 |= 1;
                    }
                    else
                    {
                        wp->routine_2 = 3;
                        wp->anim_AC   = 17;
                        ctl->timer_4  = 18;
                    }
                }
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->ctl.flags_0 |= 9;
            }
            else
            {
                wp->ctl.turn_44 = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80);
                wp->rotation.y  = (wp->rotation.y + wp->ctl.turn_44) & 0xFFF;
            }
            break;
    }
}

void stcom15_func_18EC(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    wp->ctl.angle_46 = Angle_xz_svector(&Player_work.position, &wp->position) - Player_work.rotation.y;
    ctl              = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.timer_4 = 90;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (wp->value_80 > 0x480000 && (ctl->flags_0 & 0x10))
            {
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            ctl->turn_44   = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + ctl->turn_44) & 0xFFF;
            Obj_pos_set(wp, 0x34, 0, 0);
            ctl->hit_48 = Obj_map_push_out(wp);
            if (wp->value_A6 == 1)
            {
                Sound_call2(0xB0, &wp->position);
            }
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->param_E               = 4;
            }
            else if (ctl->hit_48 & 0xF00)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->param_E               = 4;
            }
            else if (ctl->timer_36 == 0 && wp->value_80 <= 0x11FFF)
            {
                wp->routine_1             = 10;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->flags_0 &= ~1;
            }
            else if (ctl->timer_34 == 0 && wp->value_80 <= 0x11FFFF && STCOM_ABS(ctl->turn_44) < 16 &&
                     ((ctl->angle_46 + 0x400) & 0xFFF) < 0x800)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
            }
            else if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void stcom15_func_1B90(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 4;
            wp->ctl.timer_4 = 45;
            wp->ctl.value_8 = D_80098844[wp->kind_2][wp->ctl.level_6].value_A;
            // fall through
        case 1:
            if (wp->value_A6 == 1)
            {
                Sound_call2(0xB5, &wp->position);
            }
            if (--ctl->timer_4 <= 0)
            {
                ctl->timer_36 = 45;
                ctl->flags_0 |= 1;
            }
            ctl->turn_44   = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + ctl->turn_44) & 0xFFF;
            Obj_pos_set(wp, 0x34, 0, 0);
            ctl->hit_48          = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 32)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            break;
    }
}

sint32 stcom15_func_1D40(STCOM15_WORK *wp)
{
    sint16 i;
    sint16 sum;
    sint32 r;

    sum = 0;
    r   = wp->ctl.rand_2 & 0xF;
    for (i = 0; i < 4; i++)
    {
        sum += stcom15_D_0068[i];
        if (r < sum)
        {
            break;
        }
    }
    wp->routine_1             = 2;
    *(uint16 *)&wp->routine_2 = 0;
    switch (i)
    {
        case 0:
            wp->turn_66 = 0;
            break;
        case 1:
            wp->turn_66 = 0x10;
            break;
        case 2:
            wp->turn_66 = -0x10;
            break;
        default:
            wp->routine_1 = 0;
            break;
    }
    return 1;
}

void stcom15_func_1E0C(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;

    ctl             = &wp->ctl;
    wp->ctl.shot_4C = Open_SHL_WORK();
    if (wp->ctl.shot_4C != NULL)
    {
        wp->ctl.shot_4C->flags_0 = 1;
        if (wp->ctl.level_6 == 0)
        {
            wp->ctl.shot_4C->kind_2           = 6;
            wp->ctl.shot_4C->variant_3        = 0;
            wp->ctl.shot_4C->position_fixed.y = wp->position_fixed.y - 0x3C0000;
            wp->ctl.shot_4C->speed_9C         = 0x20;
            wp->ctl.shot_4C->rise_A0          = 0x10;
            Sound_call2(0xB2, &wp->position);
        }
        else
        {
            wp->ctl.shot_4C->kind_2           = 9;
            wp->ctl.shot_4C->variant_3        = 3;
            wp->ctl.shot_4C->position_fixed.y = wp->position_fixed.y - 0x500000;
        }
        ctl->shot_4C->position_fixed.x = wp->position_fixed.x;
        ctl->shot_4C->position_fixed.z = wp->position_fixed.z;
        ctl->shot_4C->angle_64         = wp->rotation.y;
        func_80030150(&ctl->shot_4C->position_fixed, &ctl->shot_4C->position);
        func_8002FFC4(&ctl->shot_4C->position, &ctl->shot_4C->position_fixed, ctl->shot_4C->angle_64, 0x6E0, 0, 0);
    }
}

sint32 stcom15_func_1F44(STCOM15_WORK *wp)
{
    STCOM15_CTL *ctl;
    uint32 damage;

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
                wp->ctl.flags_0 = (wp->ctl.flags_0 & ~2) | 0x48;
                damage          = D_80098844[wp->kind_2][wp->ctl.level_6].limit_9;
            }
            if (wp->ctl.flags_0 & 8)
            {
                wp->ctl.timer_A += damage;
                if (!(wp->ctl.hit_14 & 0x20000000) && wp->ctl.timer_A < D_80098844[wp->kind_2][wp->ctl.level_6].limit_9)
                {
                    if (wp->ctl.level_6 == 0)
                    {
                        if (wp->routine_1 != 6)
                        {
                            *(uint16 *)&wp->routine_2 = 0;
                        }
                        wp->routine_1 = 6;
                    }
                    Sound_call2(0xA0, &wp->position);
                }
                else if (wp->routine_1 == 5)
                {
                    Sound_call2(0xA0, &wp->position);
                }
                else
                {
                    Sound_call2(0xA2, &wp->position);
                    if (ctl->target_1C.pad & 1)
                    {
                        ctl->turn_44 = Angle_xz_svector(&wp->position, &ctl->target_1C);
                        if (((wp->rotation.y - ctl->turn_44 + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->routine_1  = 7;
                            wp->rotation.y = ctl->turn_44;
                        }
                        else
                        {
                            wp->routine_1  = 8;
                            wp->rotation.y = (ctl->turn_44 + 0x800) & 0xFFF;
                        }
                    }
                    else
                    {
                        ctl->turn_44 = Angle_xz_svector(&stcom15_D_006C, &ctl->target_1C);
                        if (((ctl->turn_44 - wp->rotation.y + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->routine_1  = 8;
                            wp->rotation.y = ctl->turn_44;
                        }
                        else
                        {
                            wp->routine_1  = 7;
                            wp->rotation.y = (ctl->turn_44 + 0x800) & 0xFFF;
                        }
                    }
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->timer_A              = 0;
                }
            }
            else if (!(wp->ctl.hit_14 & 0x20000000) && wp->ctl.timer_A < D_80098844[wp->kind_2][wp->ctl.level_6].limit_9)
            {
                Sound_call2(0xA0, &wp->position);
            }
            else if (wp->routine_1 != 5)
            {
                Sound_call2(0xA2, &wp->position);
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
            wp->variant_3 &= ~0x40;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
