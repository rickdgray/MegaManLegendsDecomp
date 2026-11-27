#include "common.h"
#include "st00.h"

void func_801076E8(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_8011C054[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->ctl.flags_0 & 0x10)
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
        Model_pose_unpack(wp);
        Model_parts_mtx_set_y(wp);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x100, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0xD0, 0, 0x8000, wp->value_1, &ctl->hit_14, ctl->value_8 | 0x4880008, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_801078B8(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 life;

    ctl = &wp->ctl;
    if ((((ST00_PAIR_CTL *)&wp->ctl)->part_34 = Open_SHL_WORK()) != NULL)
    {
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->flags_0      = 0x25;
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->kind_2       = 0xA;
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->variant_3    = 0;
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->u_C.b.byte_C = wp->value_1;
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->u_C.b.byte_D = 2;
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->u_E.b.byte_E = 0x40;
        ((ST00_PAIR_CTL *)&wp->ctl)->part_34->u_E.b.byte_F = 1;
    }
    else
    {
        func_8003187C(wp);
    }
    if ((((ST00_PAIR_CTL *)ctl)->part_38 = Open_SHL_WORK()) != NULL)
    {
        ((ST00_PAIR_CTL *)ctl)->part_38->flags_0      = 0x25;
        ((ST00_PAIR_CTL *)ctl)->part_38->kind_2       = 0xA;
        ((ST00_PAIR_CTL *)ctl)->part_38->variant_3    = 1;
        ((ST00_PAIR_CTL *)ctl)->part_38->u_C.b.byte_C = wp->value_1;
        ((ST00_PAIR_CTL *)ctl)->part_38->u_C.b.byte_D = 4;
        if (wp->variant_3 != 0)
        {
            ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E = 1;
        }
        else
        {
            ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E = 0;
        }
    }
    else
    {
        func_8003187C(wp);
        Close_SHL_WORK(((ST00_PAIR_CTL *)ctl)->part_34);
    }
    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    ctl->flags_0             = 0x1E;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    ctl->hit_14              = 0;
    ctl->value_18            = 0;
    Track_reset(ctl->track_24, D_8009884C[wp->kind_2][wp->variant_3].value_F, -0x60);
    life                 = D_8009884C[wp->kind_2][wp->variant_3].life_8 << 5;
    wp->data_78          = D_8011C0A4;
    wp->data_10          = NULL;
    wp->life_6E          = life;
    wp->life_max_B0      = life;
    wp->life_prev_B2     = life;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    if (wp->variant_3 != 0)
    {
        ((ST00_10C *)wp)->value_107 = -1;
        wp->routine_0               = 1;
        wp->routine_1               = 0;
        *(uint16 *)&wp->routine_2   = 0;
        func_800322A8(wp, 0, 0);
        func_8005D620(wp, 0, 0, 0x51, 0x203050);
    }
    else
    {
        wp->routine_0             = 4;
        wp->routine_1             = 0xE;
        *(uint16 *)&wp->routine_2 = 0;
        func_800322A8(wp, 1, 0);
    }
    wp->scale.v.pad = 0x4210;
}

void func_80107B48(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    if (func_8003648C(ctl->track_24, wp) != 0)
    {
        wp->ctl.flags_0 |= 0x20;
    }
    else
    {
        wp->ctl.flags_0 &= ~0x20;
    }
    if (ctl->flags_0 & 2)
    {
        func_8010A448(wp);
    }
    D_8011C068[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        if (wp->life_6E <= 0)
        {
            wp->routine_1 = 0;
            if (Game_work.value_50 == 0 && !(ctl->flags_0 & 0x40))
            {
                ctl->flags_0 |= 0x40;
                Sce_flag_on(0x606);
                func_8005D6E8(wp);
            }
        }
        else
        {
            switch (wp->routine_1)
            {
                case 3:
                    wp->routine_1 = wp->param_D;
                    break;
                case 0:
                case 4:
                    wp->routine_1 = 3;
                    wp->param_D   = 1;
                    break;
                case 2:
                    wp->routine_1 = 1;
                    break;
                default:
                    if (ctl->flags_0 & 0x20)
                    {
                        wp->routine_1 = 1;
                    }
                    else
                    {
                        wp->routine_1 = 0;
                    }
                    break;
            }
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
}

void func_80107D04(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    if (func_8003648C(ctl->track_24, wp) != 0)
    {
        wp->ctl.flags_0 |= 0x20;
    }
    else
    {
        wp->ctl.flags_0 &= ~0x20;
    }
    if (ctl->flags_0 & 2)
    {
        func_8010A448(wp);
    }
    D_8011C068[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 3:
            case 10:
                wp->routine_1 = wp->param_D;
                break;
            case 4:
                if (wp->life_6E <= 0)
                {
                    wp->routine_1 = 5;
                    break;
                }
                // fall through
            default:
                wp->routine_1 = 8;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (*(sint16 *)&ctl->u_3C != 0) // a signed timer here
    {
        (*(sint16 *)&ctl->u_3C)--;
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x100, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0xD0, 0, 0x8000, wp->value_1, &ctl->hit_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_80107F00(ST00_PAIR_OBJ *wp)
{
    func_8003187C(wp);
    Close_SHL_WORK(wp->child_514);
    Close_SHL_WORK(wp->child_518);
}

void func_80107F40(ST00_GLOW_OBJ *wp)
{
    ST00_GLOW *glow;

    glow = &wp->glow_4E0;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2        = 1;
            wp->anim_AC          = 0;
            wp->glow_4E0.value_8 = 0;
            // fall through
        case 1:
            if ((glow->flags_0 & 0x20) || (glow->color_14 & 0xFFFFFF))
            {
                glow->flags_0 |= 1;
            }
            break;
    }
}

void func_80107FAC(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STAGE_PL_VIEW *pl;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.timer_4 = 0x50;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (wp->value_80 < 0xC8000)
            {
                wp->anim_AC = wp->anim_prev_AD;
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x80, &pl->position_fixed, pl->rotation.y, 0x800) != 0)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 3;
                    wp->param_D   = 6;
                }
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (--ctl->timer_4 < 0)
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x80, &pl->position_fixed, pl->rotation.y, 0x800) != 0)
                {
                    wp->routine_1 = 2;
                }
                else
                {
                    wp->routine_1 = 3;
                    wp->param_D   = 2;
                }
                *(uint16 *)&wp->routine_2 = 0;
                ctl->level_6              = 0x3C;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x20)) & 0xFFF;
            Obj_pos_set(wp, 0x100, 0, 0);
            hit = Obj_map_push_out(wp);
            if (!(((STAGE_OBJ *)wp)->value_A4 & 3))
            {
                Sound_call2(0xC8, &wp->position);
            }
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 3;
                wp->param_D               = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->routine_1             = 3;
                wp->param_D               = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
            }
            break;
    }
}

void func_80108220(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    uint32 dx;
    uint32 dz;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            ctl->value_8  = 0;
            // fall through
        case 1:
            dx = pl->position.x - ST00_AREA_TBL[0].x;
            dz = pl->position.z - ST00_AREA_TBL[0].z;
            if (dx < ST00_AREA_TBL[0].w && dz < ST00_AREA_TBL[0].d)
            {
                wp->routine_1 = 10;
                wp->param_D   = 9;
            }
            else
            {
                dx = Player_work.position.x - ST00_AREA_TBL[10].x;
                dz = Player_work.position.z - ST00_AREA_TBL[10].z;
                if (dx > ST00_AREA_TBL[10].w || dz > ST00_AREA_TBL[10].d)
                {
                    wp->anim_AC               = wp->anim_prev_AD;
                    wp->routine_1             = 0;
                    *(uint16 *)&wp->routine_2 = 0;
                    break;
                }
                if (wp->value_80 <= 0xC7FFF)
                {
                    wp->anim_AC = wp->anim_prev_AD;
                    if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x80, &pl->position_fixed, pl->rotation.y, 0x800) == 0)
                    {
                        wp->routine_1 = 3;
                        wp->param_D   = 0xD;
                    }
                    else
                    {
                        wp->routine_1 = 0xD;
                    }
                }
                else if ((sint16)ctl->u_3C.flag == 0 && wp->value_80 > 0x200000)
                {
                    if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, pl->rotation.y, 0x800) == 0)
                    {
                        wp->routine_1 = 3;
                        wp->param_D   = 0xC;
                    }
                    else
                    {
                        wp->routine_1 = 0xC;
                    }
                }
                else
                {
                    Obj_pos_set(wp, 0x100, 0, 0);
                    Obj_map_push_out(wp);
                    if (!(((STAGE_OBJ *)wp)->value_A4 & 3))
                    {
                        Sound_call2(0xC8, &wp->position);
                    }
                    wp->position.y       = Obj_ceiling_height_get(wp);
                    wp->position_fixed.y = wp->position.y << 16;
                    dx                   = wp->position.x - ST00_AREA_TBL[1].x;
                    dz                   = wp->position.z - ST00_AREA_TBL[1].z;
                    if (dx <= ST00_AREA_TBL[1].w && dz <= ST00_AREA_TBL[1].d)
                    {
                        break;
                    }
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                    wp->routine_1      = 0xB;
                }
            }
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
}

void func_801084D4(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 hit;
    sint32 i;
    STAGE_PL_VIEW *pl;

    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 2;
            wp->ctl.value_8 = 0;
            wp->ctl.timer_4 = wp->ctl.level_6;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0 || (ctl->hit_14 & 0x2000000) || wp->value_80 < 0x48000)
            {
                ctl->flags_0 |= 1;
                break;
            }
            Obj_pos_set(wp, 0x200, 0, 0);
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->routine_1             = 3;
                wp->param_D               = 2;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                ctl->level_6              = ctl->timer_4;
            }
            else if (hit & 0xF00)
            {
                wp->routine_1             = 3;
                wp->param_D               = 2;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                ctl->level_6              = ctl->timer_4;
            }
            else if (func_80031E60(&pl->position_fixed, pl->rotation.y, 0x800, &wp->position_fixed, wp->rotation.y, 0x400) != 0)
            {
                wp->routine_1             = 3;
                wp->param_D               = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                ctl->level_6              = ctl->timer_4;
            }
            else if (wp->value_A6 == 1)
            {
                for (i = 0; i < 3; i++)
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0   = 5;
                        fx->kind_2    = 0x80;
                        fx->variant_3 = 0x42;
                        Obj_pos_set(wp, D_8011C14C[i], 0, 0);
                        fx->sprite.position   = wp->position;
                        fx->sprite.position.y = Obj_ceiling_height_get(wp);
                        wp->position          = wp->position_prev;
                        wp->position_fixed    = wp->position_fixed_prev;
                    }
                }
                Swing_Camera2(0x1E, 0x7D0, 0x1388, &wp->position);
                Sound_call2(0xC2, &wp->position);
            }
            break;
    }
}

void func_801087D0(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    ST00_ROUTE *rec;
    sint32 dx;
    sint32 dz;
    sint32 i;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2                         = 1;
            wp->anim_AC                           = 2;
            wp->ctl.timer_4                       = 0x20;
            wp->ctl.value_8                       = 0;
            ((ST00_ROUTE_CTL *)&wp->ctl)->step_3E = 0;
            wp->ctl.flags_0 &= ~4;
            if (wp->rotation.y > 0x800)
            {
                ((ST00_ROUTE_CTL *)&wp->ctl)->route_40 = D_8011C0C8;
            }
            else
            {
                ((ST00_ROUTE_CTL *)&wp->ctl)->route_40 = D_8011C0F8;
            }
            // fall through
        case 1:
            rec = (ST00_ROUTE *)(((ST00_ROUTE_CTL *)ctl)->step_3E * sizeof(ST00_ROUTE) +
                                 (uint32)((ST00_ROUTE_CTL *)ctl)->route_40); // offset first, as retail adds
            dx  = wp->position.x - rec->x_4;
            dz  = wp->position.z - rec->z_6;
            if ((uint32)dx < (uint32)rec->w_8 && (uint32)dz < (uint32)rec->d_A)
            {
                if (--ctl->timer_4 < 0)
                {
                    ctl->timer_4 = 0x20;
                    if (++((ST00_ROUTE_CTL *)ctl)->step_3E < 4)
                    {
                        goto puff;
                    }
                    wp->routine_2 = 2;
                    wp->anim_AC   = 2;
                    ctl->timer_4  = 0x20;
                    goto walk;
                }
                wp->anim_AC    = 3;
                wp->rotation.y = (wp->rotation.y + ((ST00_ROUTE_CTL *)ctl)->route_40[((ST00_ROUTE_CTL *)ctl)->step_3E].turn_0) & 0xFFF;
                break;
            }
            wp->anim_AC = 2;
            Obj_pos_set(wp, 0x200, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
        puff:
            if (wp->value_A6 & 1)
            {
                for (i = 0; i < 3; i++)
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0   = 5;
                        fx->kind_2    = 0x80;
                        fx->variant_3 = 0x42;
                        fx->value_D   = 2;
                        Obj_pos_set(wp, D_8011C154[i], 0, 0);
                        fx->sprite.position   = wp->position;
                        fx->sprite.position.y = Obj_ceiling_height_get(wp);
                        wp->position          = wp->position_prev;
                        wp->position_fixed    = wp->position_fixed_prev;
                    }
                }
                Swing_Camera2(0x1E, 0x7D0, 0x1388, &wp->position);
                Sound_call2(0xC2, &wp->position);
            }
            break;
        case 2:
        walk:
            Obj_pos_set(wp, 0x200, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->value_A6 & 1)
            {
                for (i = 0; i < 3; i++)
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0   = 5;
                        fx->kind_2    = 0x80;
                        fx->variant_3 = 0x42;
                        fx->value_D   = 2;
                        Obj_pos_set(wp, D_8011C154[i], 0, 0);
                        fx->sprite.position = wp->position;
                        wp->position        = wp->position_prev;
                        wp->position_fixed  = wp->position_fixed_prev;
                    }
                }
                Swing_Camera2(0x1E, 0x7D0, 0x1388, &wp->position);
                Sound_call2(0xC2, &wp->position);
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 5;
            }
            break;
    }
}

void func_80108C18(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STAGE_PL_VIEW *pl;
    sint16 turn;

    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 3;
            turn          = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) / 12;
            ctl->timer_4  = 0xC;
            ctl->value_8  = 0;
            wp->turn_66   = STCOM_ABS(turn);
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_66)) & 0xFFF;
            if (((STAGE_OBJ *)wp)->value_A4 & 1)
            {
                Sound_call2(0xC8, &wp->position);
            }
            break;
    }
}

void func_80108D48(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STAGE_PL_VIEW *pl;
    STCOM_SVECTOR target;

    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 3;
            if (wp->rotation.y > 0x800)
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, STAGE_PL.rotation.y, 0x800) == 0)
                {
                    target.x = D_8011C0F0 + ((sint16)D_8011C0F4 >> 1);
                    target.y = 0;
                    target.z = D_8011C0F2 + ((sint16)D_8011C0F6 >> 1);
                }
                else
                {
                    target.x = D_8011C0CC + ((sint16)D_8011C0D0 >> 1);
                    target.y = 0;
                    target.z = D_8011C0CE + ((sint16)D_8011C0D2 >> 1);
                }
            }
            else
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, STAGE_PL.rotation.y, 0x800) != 0)
                {
                    target.x = D_8011C0F0 + ((sint16)D_8011C0F4 >> 1);
                    target.y = 0;
                    target.z = D_8011C0F2 + ((sint16)D_8011C0F6 >> 1);
                }
                else
                {
                    target.x = D_8011C0CC + ((sint16)D_8011C0D0 >> 1);
                    target.y = 0;
                    target.z = D_8011C0CE + ((sint16)D_8011C0D2 >> 1);
                }
            }
            wp->turn_66  = Muku(&wp->position, &target, wp->rotation.y, 0x800) / 12;
            ctl->timer_4 = 0xC;
            ctl->value_8 = 0;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            if (((STAGE_OBJ *)wp)->value_A4 & 1)
            {
                Sound_call2(0xC8, &wp->position);
            }
            if (--ctl->timer_4 <= 0)
            {
                if (wp->rotation.y > 0x800)
                {
                    wp->rotation.y = 0xC00;
                }
                else
                {
                    wp->rotation.y = 0x400;
                }
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80108F80(STAGE_OBJ *wp)
{
    STAGE_OBJ_HW *hw;

    hw = &wp->u_4E0.hw;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 3;
            hw->value_4   = 0x10;
            hw->vec_8.x   = 0;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + 0x80) & 0xFFF;
            if (wp->value_A4 & 1)
            {
                Sound_call2(0xC8, &wp->position);
            }
            if (--hw->value_4 <= 0)
            {
                hw->value_0 |= 1;
            }
            break;
    }
}

void func_80109038(STAGE_OBJ *wp)
{
    STAGE_OBJ_HW *hw;

    hw = &wp->u_4E0.hw;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2        = 1;
            wp->anim_AC          = 4;
            wp->value_44.half[0] = 0;
            wp->u_4E0.hw.value_4 = 0x1C;
            wp->u_4E0.hw.vec_8.x = 0;
            wp->u_4E0.hw.value_0 &= ~4;
            // fall through
        case 1:
            if (--hw->value_4 <= 0)
            {
                hw->value_0 |= 5;
            }
            Obj_pos_set(wp, wp->value_44.half[0] << 3, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y         = Obj_ceiling_height_get(wp);
            wp->position_fixed.v.y = wp->position.y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
            }
            break;
    }
}

void func_80109180(STAGE_STCOM15_WORK_4E0 *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR fixed;
    sint16 i;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->routine_3 = 0;
            ctl->timer_4  = 0x12;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2    = 2;
                wp->anim_AC      = 4;
                wp->anim_prev_AD = 0xFF;
                ctl->timer_4     = 4;
            }
            else
            {
                if ((ctl->timer_4 & 3) == 0)
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0    = 5;
                        fx->kind_2     = 0x80;
                        fx->variant_3  = 0x40;
                        pos            = wp->position;
                        fixed          = wp->position_fixed;
                        wp->rotation.y = (wp->rotation.y + D_8011C15C[wp->routine_3]) & 0xFFF;
                        wp->position   = wp->joints_180[wp->routine_3];
                        Obj_pos_set(wp, 0xB40, 0, 0);
                        fx->sprite.position = wp->position;
                        wp->position        = pos;
                        wp->position_fixed  = fixed;
                        wp->rotation.y      = (wp->rotation.y - D_8011C15C[wp->routine_3]) & 0xFFF;
                    }
                    wp->routine_3++;
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2    = 3;
            wp->velocity.v.y = 0;
            wp->accel.y      = 4;
            for (i = 6; i < 12; i++)
            {
                ST00_PART_FLAGS_F8(wp)[i].hide_3 = -1;
            }
            // fall through
        case 3:
            Obj_pos_set(wp, 0, wp->velocity.v.y << 4, 0);
            wp->velocity.v.y += wp->accel.y;
            wp->position.y -= 0x46;
            wp->position_fixed.y = wp->position.y << 16;
            if (Obj_map_push_out(wp) & 0x1000)
            {
                wp->flags_0 &= ~2;
                i = func_80031E60(&pl->position_fixed, pl->rotation.y, 0x800, &wp->position_fixed, wp->rotation.y, 0x400);
                if (!(((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 1))
                {
                    if ((((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 0x10) || i != 0)
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_34->routine_1 = 2;
                    }
                    else
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_34->routine_1 = 1;
                    }
                }
                if (!(((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 1))
                {
                    if ((((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 0x10) || i != 0)
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_38->routine_1 = 2;
                    }
                    else
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_38->routine_1 = 1;
                    }
                }
                *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_34->routine_2 = 0;
                *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_38->routine_2 = 0;
                for (i = 0; i < 6; i++)
                {
                    fx = func_80031618();
                    if (fx == NULL)
                    {
                        break;
                    }
                    fx->flags_0                      = 5;
                    fx->kind_2                       = 0x80;
                    fx->variant_3                    = 0x40;
                    fx->sprite.position              = wp->joints_180[i];
                    ST00_PART_FLAGS_F8(wp)[i].hide_3 = -1;
                }
                wp->routine_2 = 4;
            }
            wp->position.y += 0x46;
            wp->position_fixed.y = wp->position.y << 16;
            break;
        case 4:
            if ((((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 1) && (((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 1))
            {
                func_8005D6E8(wp);
                func_8003187C(wp);
                Close_SHL_WORK(((ST00_PAIR_CTL *)ctl)->part_34);
                Close_SHL_WORK(((ST00_PAIR_CTL *)ctl)->part_38);
                func_80047228(wp, &wp->joints_180[0], wp->variant_3);
            }
            break;
    }
}

void func_80109638(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 i;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0xB;
            ctl->timer_4  = 0xD;
            ctl->value_8  = 0;
            Sound_call2(0xBF, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2                                          = 2;
            ctl->timer_4                                           = 10;
            ((ST00_PAIR_CTL *)ctl)->part_34->routine_1             = 3;
            ((ST00_PAIR_CTL *)ctl)->part_38->routine_1             = 3;
            *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_34->routine_2 = 0;
            *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_38->routine_2 = 0;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC++;
            ctl->timer_4 = 0x14;
            Sound_call2(0xC0, &wp->position);
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 4;
                ctl->timer_4  = 10;
            }
            else
            {
                if (ctl->timer_4 == 3)
                {
                    for (i = 0; i < 3; i++)
                    {
                        fx = func_80031618();
                        if (fx != NULL)
                        {
                            fx->flags_0   = 5;
                            fx->kind_2    = 0x80;
                            fx->variant_3 = 0x42;
                            Obj_pos_set(wp, D_8011C168[i], 0, 0);
                            fx->sprite.position = wp->position;
                            wp->position        = wp->position_prev;
                            wp->position_fixed  = wp->position_fixed_prev;
                        }
                    }
                    Swing_Camera2(0x1E, 0x7D0, 0x1388, &wp->position);
                    Sound_call2(0xC1, &wp->position);
                }
                break;
            }
            // fall through
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 5;
            wp->anim_AC++;
            ctl->timer_4 = 0xF;
            // fall through
        case 5:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801098F0(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 i;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0xB;
            ctl->timer_4  = 0xD;
            ctl->value_8  = 0;
            Sound_call2(0xBF, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2                                          = 2;
            ctl->timer_4                                           = 10;
            ((ST00_PAIR_CTL *)ctl)->part_34->routine_1             = 3;
            ((ST00_PAIR_CTL *)ctl)->part_38->routine_1             = 3;
            *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_34->routine_2 = 0;
            *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_38->routine_2 = 0;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC++;
            ctl->timer_4 = 0x14;
            Sound_call2(0xC0, &wp->position);
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 4;
                ctl->timer_4  = 10;
            }
            else
            {
                if (ctl->timer_4 == 3)
                {
                    for (i = 0; i < 3; i++)
                    {
                        fx = func_80031618();
                        if (fx != NULL)
                        {
                            fx->flags_0   = 5;
                            fx->kind_2    = 0x80;
                            fx->variant_3 = 0x42;
                            fx->value_D   = 2;
                            Obj_pos_set(wp, D_8011C170[i], 0, 0);
                            fx->sprite.position = wp->position;
                            wp->position        = wp->position_prev;
                            wp->position_fixed  = wp->position_fixed_prev;
                        }
                    }
                    Swing_Camera2(0x1E, 0x7D0, 0x1388, &wp->position);
                    Sound_call2(0xC1, &wp->position);
                }
                break;
            }
            // fall through
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 5;
            wp->anim_AC++;
            ctl->timer_4 = 0xF;
            // fall through
        case 5:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            if (wp->value_80 <= 0xC7FFF)
            {
                wp->routine_1             = 3;
                wp->param_D               = 0xD;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
            }
            else
            {
                wp->routine_1             = 0xA;
                wp->param_D               = 8;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
            }
            break;
    }
}

void func_80109BD8(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    sint32 mask;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 6;
            ctl->timer_4  = 0x32;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~4;
            Sound_call2(0xC3, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC++;
                ctl->timer_4 = 0x14;
            }
            else
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x100, &pl->position_fixed, pl->rotation.y, 0x800) == 0)
                {
                    wp->routine_2 = 4;
                    wp->anim_AC   = 9;
                    ctl->timer_4  = 0xB;
                }
                else if (ctl->timer_4 == 8)
                {
                    if (!(((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 1))
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_34->routine_1 = 4;
                    }
                    if (!(((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 1))
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_38->routine_1 = 4;
                    }
                    *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_34->routine_2 = 0;
                    *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_38->routine_2 = 0;
                    Sound_call2(0xC4, &wp->position);
                }
                break;
            }
            // fall through
        case 2:
            if (ctl->timer_4 == 0 && (((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 5) &&
                (((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 5))
            {
                wp->routine_2 = 3;
                wp->anim_AC++;
                ctl->timer_4 = 10;
                mask         = ~4;
                ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E &= mask;
                ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E &= mask;
            }
            else
            {
                if (ctl->timer_4 != 0)
                {
                    ctl->timer_4--;
                }
                break;
            }
            // fall through
        case 3:
            if (ctl->timer_4 == 0 && (((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 3) &&
                (((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 3))
            {
                wp->routine_2 = 4;
                wp->anim_AC++;
                ctl->timer_4 = 0xB;
                mask         = ~2;
                ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E &= mask;
                ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E &= mask;
            }
            else
            {
                if (ctl->timer_4 != 0)
                {
                    ctl->timer_4--;
                }
                else
                {
                    ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E |= 8;
                    ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E |= 8;
                }
                break;
            }
            // fall through
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x80, &pl->position_fixed, pl->rotation.y, 0x800) != 0)
            {
                wp->routine_1 = 2;
            }
            else
            {
                wp->routine_1 = 3;
                wp->param_D   = 2;
            }
            *(uint16 *)&wp->routine_2 = 0;
            ctl->level_6              = 0x3C;
            ctl->flags_0 |= 4;
            break;
    }
}

void func_80109F6C(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    sint32 mask;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 6;
            ctl->timer_4  = 0x32;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~4;
            Sound_call2(0xC3, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC++;
                ctl->timer_4 = 0x14;
            }
            else
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x100, &pl->position_fixed, pl->rotation.y, 0x800) == 0)
                {
                    wp->routine_2 = 4;
                    wp->anim_AC   = 9;
                    ctl->timer_4  = 0xB;
                }
                else if (ctl->timer_4 == 8)
                {
                    if (!(((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 1))
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_34->routine_1 = 4;
                    }
                    if (!(((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 1))
                    {
                        ((ST00_PAIR_CTL *)ctl)->part_38->routine_1 = 4;
                    }
                    *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_34->routine_2 = 0;
                    *(uint16 *)&((ST00_PAIR_CTL *)ctl)->part_38->routine_2 = 0;
                    Sound_call2(0xC4, &wp->position);
                }
                break;
            }
            // fall through
        case 2:
            if (ctl->timer_4 == 0 && (((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 5) &&
                (((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 5))
            {
                wp->routine_2 = 3;
                wp->anim_AC++;
                ctl->timer_4 = 10;
                mask         = ~4;
                ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E &= mask;
                ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E &= mask;
            }
            else
            {
                if (ctl->timer_4 != 0)
                {
                    ctl->timer_4--;
                }
                break;
            }
            // fall through
        case 3:
            if (ctl->timer_4 == 0 && (((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E & 3) &&
                (((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E & 3))
            {
                wp->routine_2 = 4;
                wp->anim_AC++;
                ctl->timer_4 = 0xB;
                mask         = ~2;
                ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E &= mask;
                ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E &= mask;
            }
            else
            {
                if (ctl->timer_4 != 0)
                {
                    ctl->timer_4--;
                }
                else
                {
                    ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E |= 8;
                    ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E |= 8;
                }
                break;
            }
            // fall through
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_1             = 0xA;
            wp->param_D               = 8;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->level_6              = 0x3C;
            ctl->u_3C.flag            = 0x78;
            ctl->flags_0 |= 4;
            break;
    }
}

// One pass of do { } while (0) around the player pointer doubles its weighted references so it
// outranks area for t0, as in retail; reading the state first keeps its load ahead of that block.
void func_8010A2D4(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;
    ST00_AREA *area;
    uint32 dx;
    uint32 dz;
    sint32 r;

    ctl = &wp->ctl;
    r   = wp->routine_2;
    do
    {
        pl = &Player_work;
    } while (0);
    switch (r)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0;
            ctl->value_8  = 0;
            // fall through
        case 1:
            area = &ST00_AREA_TBL[11];
            dx   = pl->position.x - area->x;
            dz   = pl->position.z - area->z;
            if (dx < area->w && dz < area->d)
            {
                wp->routine_1 = 9;
                wp->routine_2 = 1;
                wp->anim_AC   = 2;
                ctl->timer_4  = 0x20;
                ctl->flags_0 &= ~4;
                wp->rotation.y       = 0;
                (&ctl->u_3C.flag)[1] = 3;
                ctl->effect_40       = (STCOM_EFFECT *)&ST00_AREA_TBL[1].a;
                break;
            }
            area = &ST00_AREA_TBL[12];
            dx   = pl->position.x - area->x;
            dz   = pl->position.z - area->z;
            if (dx < area->w && dz < area->d)
            {
                wp->routine_1 = 9;
                wp->routine_2 = 1;
                wp->anim_AC   = 2;
                wp->position.z += 0x200;
                wp->position_fixed.z = wp->position.z << 16;
                ctl->timer_4         = 0x20;
                ctl->flags_0 &= ~4;
                wp->rotation.y       = 0x800;
                (&ctl->u_3C.flag)[1] = 1;
                ctl->effect_40       = (STCOM_EFFECT *)&ST00_AREA_TBL[5].a;
            }
            break;
    }
}

sint32 func_8010A448(STAGE_STCOM15_WORK_4E0 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 damage;
    sint32 limit;

    ctl    = &wp->ctl;
    damage = wp->ctl.hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (wp->ctl.hit_14 & 0x18000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                if (Game_work.value_50 != 0)
                {
                    wp->life_6E               = 0;
                    wp->ctl.flags_0           = (wp->ctl.flags_0 & ~2) | 4;
                    damage                    = D_8009884C[wp->kind_2][wp->variant_3].limit_9;
                    wp->routine_1             = 4;
                    *(uint16 *)&wp->routine_2 = 0;
                }
                else if (func_80042208() != 0)
                {
                    wp->life_6E = 0;
                    wp->ctl.flags_0 &= ~2;
                }
                else
                {
                    wp->life_6E = 1;
                }
            }
            if (ctl->flags_0 & 4)
            {
                ctl->timer_A += (damage < 10) ? 10 : damage;
                limit = D_8009884C[wp->kind_2][wp->variant_3].limit_9 * 4;
                if (damage < limit && ctl->timer_A < limit)
                {
                    Sound_call2(0xA0, &wp->position);
                }
                else
                {
                    Sound_call2(0xA2, &wp->position);
                    wp->routine_1             = 4;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->timer_A              = 0;
                }
            }
            else
            {
                limit = D_8009884C[wp->kind_2][wp->variant_3].limit_9 * 4;
                Sound_call2((damage >= limit || ctl->timer_A >= limit) ? 0xA2 : 0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
            ((ST00_PAIR_CTL *)ctl)->part_34->u_E.b.byte_E |= 0x20;
            ((ST00_PAIR_CTL *)ctl)->part_38->u_E.b.byte_E |= 0x20;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
