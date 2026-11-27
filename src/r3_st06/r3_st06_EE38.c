#include "common.h"
#include "st06.h"

void func_8010EE38(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_8010EF94(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_8010F024(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x14);
                wp->anim_AC = 8;
                wp->routine_0++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x80;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010EF94(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->data_10          = D_801251F8;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->anim_AC          = 0;
    wp->anim_prev_AD     = 0xFF;
}

sint32 func_8010F024(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (Player_work.target_184 == wp)
    {
        if ((sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
        {
            wp->turn_64 = (uint32) - (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        else
        {
            wp->turn_64 = (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x80;
        D_8012BA40.x = wp->value_180.x;
        D_8012BA40.y = wp->value_180.y - 0x20;
        D_8012BA40.z = wp->value_180.z;
        func_80039FAC(&D_8012BA40, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void func_8010F154(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_6        = rand();
    D_80125204[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->ctl.flags_4 & 0x10)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        if (wp->routine_0 != 4)
        {
            if (ctl->flags_4 & 0x100)
            {
                ctl->u_38.h.lo = (ctl->u_38.h.lo + ctl->u_3C.a.turn_1 * 40) & 0xFFF;
                ctl->u_38.h.hi = (ctl->u_38.h.hi - ctl->u_3C.a.turn_1 * 40) & 0xFFF;
            }
            else
            {
                ctl->u_38.h.lo = (ctl->u_38.h.lo + (wp->value_44.half[0] >> 1)) & 0xFFF;
                ctl->u_38.h.hi = (ctl->u_38.h.hi + (wp->value_44.half[0] >> 1)) & 0xFFF;
            }
            ST06_SP->angle_150 = ctl->u_38.h.lo;
            ST06_SP->angle_158 = ctl->u_38.h.hi;
        }
        Model_parts_mtx_set_y(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_AC, wp->value_A4);
    }
    if (ctl->flags_4 & 8)
    {
        func_80110A54(wp);
    }
    Pos_Shadow_Trans(&wp->joint_180[0], 0xC0, 0x200, 0);
}

void func_8010F35C(ST06_CRAB *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_4             = 0x5E;
    *(sint32 *)&wp->ctl.timer_8 = 0;
    *(sint32 *)&wp->ctl.kind_C  = 0;
    wp->ctl.hit_18              = 0;
    wp->ctl.value_1C            = 0;
    wp->ctl.value_2C            = 0;
    wp->ctl.u_38.h.hi           = 0;
    wp->ctl.u_38.h.lo           = 0;
    if (wp->variant_3 == 0)
    {
        wp->life_6E = D_80098844[wp->kind_2]->life_8 * 16;
    }
    else
    {
        wp->life_6E = D_80098844[wp->kind_2]->life_8 * 8;
    }
    wp->data_78      = D_80125240;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E;
    if (wp->u_C.b.byte_C & 2)
    {
        wp->routine_0 = 4;
        wp->routine_1 = 0;
    }
    else if (wp->u_C.b.byte_C & 0x10)
    {
        wp->routine_0 = 3;
        wp->routine_1 = 0;
    }
    else
    {
        wp->routine_0 = 1;
        wp->routine_1 = 0;
    }
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    wp->scale.v.pad = 0x4210;
}

void func_8010F490(ST06_CRAB *wp)
{
    if (wp->ctl.flags_4 & 2)
    {
        func_80110AF0(wp);
    }
    D_80125218[wp->routine_1](wp);
    if (wp->ctl.flags_4 & 1)
    {
        func_801107A0(wp);
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_4 &= ~1;
    }
    func_80051B68(wp, 1, 0, 0x1000008);
    wp->ctl.hit_18 = 0;
}

void func_8010F53C(ST06_CRAB *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_8 = 0xF;
            if (wp->routine_1 != 0)
            {
                wp->anim_AC = 0xB;
            }
            wp->routine_2++;
            break;
        case 1:
            if (!(--wp->ctl.timer_8 & 3))
            {
                func_80110734(&wp->joint_180[wp->ctl.timer_8 >> 2]);
            }
            if (wp->ctl.timer_8 == 0)
            {
                func_80052528(wp);
                func_80047148(wp, &wp->joint_180[0]);
                wp->u_C.b.byte_C |= 1;
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}

void func_8010F618(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->u_C.b.byte_D)
    {
        case 0:
            wp->anim_AC = 1;
            break;
        case 1:
            wp->anim_AC = 1;
            switch (wp->routine_2)
            {
                case 0:
                    wp->value_44.half[0] = 0x80;
                    Obj_pos_set(wp, 0x80, 0, 0);
                    if (wp->position.x < 0)
                    {
                        wp->ctl.timer_8 = 0x80;
                        wp->routine_2++;
                    }
                    break;
                case 1:
                    wp->ctl.u_3C.a.turn_1 = 1;
                    wp->rotation.y        = (wp->rotation.y + 0x10) & 0xFFF;
                    if (--wp->ctl.timer_8 == 0)
                    {
                        wp->routine_2++;
                    }
                    break;
                case 2:
                    wp->value_44.half[0] = 0x80;
                    Obj_pos_set(wp, 0x80, 0, 0);
                    break;
            }
            if (ctl->value_A == 1000)
            {
                wp->flags_0 &= ~2;
            }
            break;
        case 2:
            func_80110498(wp);
            if (wp->ctl.value_A == 0 || wp->ctl.value_A == 1400)
            {
                wp->flags_0 &= ~2;
            }
            if (ctl->value_A == 1000)
            {
                wp->flags_0 |= 2;
            }
            break;
        case 3:
            wp->flags_0 &= ~2;
            break;
    }
    ctl->value_A++;
}

void func_8010F7E8(ST06_CRAB *wp)
{
    if (wp->ctl.flags_4 & 2)
    {
        func_80110AF0(wp);
    }
    D_80125234[wp->routine_1](wp);
    wp->ctl.hit_18 = 0;
}

void func_8010F850(ST06_CRAB *wp)
{
    wp->anim_AC = 0;
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
        return;
    }
    wp->position.y         = Obj_ceiling_height_get(wp);
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->ctl.flags_4 |= 0x81;
}

void func_8010F8B0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    STCOM_SVECTOR probe;
    sint32 hit;
    sint32 count;
    sint16 front;
    sint16 side;
    uint8 done;

    done        = 0;
    wp->anim_AC = 1;
    ctl         = &wp->ctl;
    if (wp->ctl.value_A == 0)
    {
        Sound_call2(0xEA, &wp->position);
        wp->ctl.value_A = 9;
    }
    else
    {
        wp->ctl.value_A--;
    }
    if (ctl->timer_8 != 0)
    {
        ctl->timer_8--;
        wp->rotation.y = (wp->rotation.y + ctl->u_3C.a.turn_1 * 4) & 0xFFF;
        if (wp->variant_3 == 0)
        {
            wp->value_44.half[0] = 0x100;
        }
        else
        {
            wp->value_44.half[0] = 0x200;
        }
        Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
        hit = func_80049C24(wp);
        if (hit != 0)
        {
            count = func_80037BB4((void *)hit);
            if (count > 0)
            {
                done = 1;
                ctl->flags_4 |= 0x200;
                goto stop;
            }
            if (count == -1)
            {
                done = 1;
                ctl->flags_4 |= 0x1000;
                goto stop;
            }
        }
        if (wp->position.x < -0x275F || wp->position.x > 0x2B60)
        {
            done = 1;
            ctl->flags_4 |= 0x1000;
        }
        else if (wp->position.x >= -0x1BFF && wp->position.x <= -0xC00 && wp->position.z > 0xF60)
        {
            done = 1;
            ctl->flags_4 |= 0x1000;
        }
        else if (wp->position.x >= -0x275F && wp->position.x <= -0x1C00 && wp->position.z > 0x400 &&
                 wp->position.z - wp->position.x > 0x2B60)
        {
            done = 1;
            ctl->flags_4 |= 0x1000;
        }
        else if (ctl->flags_4 & 0x80)
        {
            probe = wp->position;
            if ((uint16)wp->rotation.y < 0x400 || (uint16)wp->rotation.y >= 0xC00)
            {
                probe.z -= 0x6C;
            }
            else
            {
                probe.z += 0x6C;
            }
            front = func_80048EA4(&probe, NULL, wp->value_44.half[1], wp->value_1);
            if ((front - wp->position_prev.y < 0 ? wp->position_prev.y - front : front - wp->position_prev.y) > 0)
            {
                done = 1;
                ctl->flags_4 |= 0x1000;
            }
            else
            {
                probe = wp->position;
                if ((uint16)wp->rotation.y < 0x800)
                {
                    probe.x -= 0x6C;
                }
                else
                {
                    probe.x += 0x6C;
                }
                side = func_80048EA4(&probe, NULL, wp->value_44.half[1], wp->value_1);
                if ((side - wp->position_prev.y < 0 ? wp->position_prev.y - side : side - wp->position_prev.y) > 0)
                {
                    done = 1;
                    ctl->flags_4 |= 0x1000;
                }
                else if (!done)
                {
                    wp->position.y         = (front <= side) ? front : side;
                    wp->position_fixed.v.y = wp->position.y << 16;
                }
            }
        }
    }
    else
    {
        wp->value_44.half[0] = 0;
        ctl->flags_4 |= 1;
    }
stop:
    if (done)
    {
        ctl->value_A         = 0;
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        wp->value_44.half[0] = 0;
        wp->anim_AC          = 0;
        ctl->flags_4         = (ctl->flags_4 & ~0x40) | 1;
    }
}

void func_8010FCB4(ST06_CRAB *wp)
{
    wp->anim_AC = 0;
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
        wp->value_44.half[0] = 0;
        wp->rotation.y       = (wp->rotation.y + wp->ctl.u_3C.a.turn_1 * 16) & 0xFFF;
        return;
    }
    wp->ctl.flags_4 |= 0x41;
}

void func_8010FD0C(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    void *hit;
    sint32 count;
    uint8 done;

    done = 0;
    ctl  = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC     = 4;
                wp->ctl.timer_8 = 0x8D;
                wp->ctl.value_A = 0;
                break;
            case 1:
                if (wp->ctl.value_A & 1)
                {
                    wp->anim_AC = 5;
                }
                else
                {
                    wp->anim_AC = 6;
                }
                break;
        }
        return;
    }
    switch (wp->routine_2)
    {
        case 0:
            if (--wp->ctl.timer_8 != 0)
            {
                if (wp->value_A6 == 1)
                {
                    wp->ctl.value_A++;
                    if (wp->variant_3 == 0)
                    {
                        wp->value_44.half[0] = 0x100;
                    }
                    else
                    {
                        wp->value_44.half[0] = 0x200;
                    }
                    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
                    hit = (void *)func_80049C24(wp);
                    if (hit != NULL)
                    {
                        count = func_80037BB4(hit);
                        if (STAGE_SCENE_BYTE(0) == 0)
                        {
                            func_80037738((sint32)hit, 5);
                            if (count != 0)
                            {
                                if (ctl->value_A & 1)
                                {
                                    func_80110734(&wp->joint_180[2]);
                                }
                                else
                                {
                                    func_80110734(&wp->joint_180[4]);
                                }
                                if (count >= 6)
                                {
                                    if (ctl->value_A == 9)
                                    {
                                        ctl->flags_4 |= 0x400;
                                    }
                                }
                                else
                                {
                                    done = 1;
                                }
                                Sound_call2(0xEC, &wp->position);
                            }
                            else
                            {
                                done = 1;
                            }
                        }
                    }
                    else
                    {
                        done = 1;
                    }
                    wp->position         = wp->position_prev;
                    wp->position_fixed.v = wp->position_fixed_prev;
                    wp->value_44.half[0] = 0;
                }
            }
            else
            {
                done = 1;
            }
            if (done)
            {
                wp->routine_3 = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                *(uint16 *)&wp->routine_2 = 0;
                wp->ctl.value_A           = 0;
                wp->ctl.timer_8           = 0;
                wp->ctl.flags_4 |= 0x801;
            }
            break;
    }
}
