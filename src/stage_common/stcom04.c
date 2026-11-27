#include "common.h"
#include "stage_common/stcom04.h"

// Shared stage code, linked into 10 stages: r3_st03, r3_st05, r3_st06, r3_st08, r3_st0a,
// r3_st0c, r3_st10, r3_st11, r3_st12 and r3_st1b. Each stage compiles this file against its own
// copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names are the same in every
// stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom04"

void stcom04_func_0000(STCOM04_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom04_D_0000[wp->type](wp);
    if (wp->be_flag & TRANS)
    {
        Model_Shadow_Trans(wp, 0xC, 0x200, 0);
    }
}

void stcom04_func_00CC(STCOM04_WORK *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->turn_64    = 0x40;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->data_78          = stcom04_D_0010;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->ctl.rot_speed.x  = 10;
    wp->velocity.x       = 0x80;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->value_10         = 0;
    wp->ctl.rot_speed.y  = 0;
    wp->ctl.rot_speed.z  = 0;
    wp->value_74         = 0;
    wp->ctl.value_0      = 0;
    wp->ctl.value_4      = 0;
    wp->velocity.y       = 0;
    wp->velocity.z       = 0;
    wp->ctl.value_8      = 0;
    wp->ctl.value_C      = 0x80;
    wp->routine_1        = 0;
    wp->count_C          = 0;
}

void stcom04_func_01A0(STCOM04_WORK *wp)
{
    uint32 hit;
    STCOM_PL_WORK *pl;
    STCOM04_CTL *ctl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            stcom04_func_00CC(wp);
            func_800322A8(wp, 1, 0);
            stcom04_func_08B8(wp, 0);
            stcom04_func_0898(wp, 1);
            wp->routine_0 = 1;
            break;
        case 1:
            wp->rotation.x = (wp->rotation.x + ctl->rot_speed.x) & 0xFFF;
            wp->rotation.y = (wp->rotation.y + ctl->rot_speed.y) & 0xFFF;
            wp->rotation.z = (wp->rotation.z + ctl->rot_speed.z) & 0xFFF;
            if (stcom04_func_0A84(wp, &hit))
            {
                return;
            }
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit)
            {
                stcom04_func_0748(wp, hit);
            }
            stcom04_func_07D0(wp);
            func_80032488(wp);
            if (wp->routine_1 == 0)
            {
                wp->routine_0 = 2;
            }
            else
            {
                wp->routine_1--;
            }
            break;
        case 2:
            if (wp->routine_1 == 10)
            {
                stcom04_func_0748(wp, 0);
                wp->routine_0 = 1;
                wp->routine_1 = rand() & 0x3F;
            }
            stcom04_func_07D0(wp);
            wp->routine_1++;
            break;
        case 3:
            hit            = Muku(&pl->position, &wp->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + hit) & 0xFFF;
            if (stcom04_func_0A84(wp, &hit))
            {
                return;
            }
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit)
            {
                stcom04_func_0748(wp, hit);
            }
            stcom04_func_07D0(wp);
            goto draw;
        case 4:
            if (wp->frame_A4 == 0 || wp->frame_A4 == 8)
            {
                Sound_call2(0x109, &wp->position);
                func_800322A8(wp, 4, 0);
                stcom04_func_08B8(wp, 1);
                stcom04_func_0898(wp, 1);
                wp->velocity.y = -0x100;
                wp->value_74   = 1;
                wp->routine_0++;
            }
            else
            {
                func_80032488(wp);
            }
            if (stcom04_func_0A84(wp, &hit))
            {
                return;
            }
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit)
            {
                stcom04_func_0748(wp, hit);
            }
            break;
        case 5:
            if (wp->state_A7 < 0)
            {
                func_800322A8(wp, 3, 0);
                stcom04_func_08B8(wp, 1);
                stcom04_func_0898(wp, 0);
                wp->routine_0++;
            }
            else
            {
                func_80032488(wp);
            }
            if (stcom04_func_0A84(wp, &hit))
            {
                return;
            }
            if (hit)
            {
                stcom04_func_0748(wp, hit);
            }
            break;
        case 6:
            wp->rotation.y = (wp->rotation.y + ctl->rot_speed.y) & 0xFFF;
            hit            = Obj_ceiling_height_get(wp) - 600;
            if (hit < wp->position.y)
            {
                wp->velocity.y = -0x100;
            }
            else if (wp->position.y < hit)
            {
                wp->velocity.y = 0x40;
            }
            else
            {
                wp->velocity.y = 0;
            }
            if (stcom04_func_0A84(wp, &hit))
            {
                return;
            }
            if (hit != 0 || (wp->routine_1 & 0x3F) == 0)
            {
                stcom04_func_0748(wp, hit);
            }
            stcom04_func_0A10(wp, hit);
            wp->routine_1++;
            goto draw;
        case 8:
            hit            = Angle_diff_clamp(wp->rot_goal_66, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + hit) & 0xFFF;
            if (hit == 0)
            {
                wp->routine_0 = 6;
            }
        draw:
            func_80032488(wp);
            break;
    }
    ctl->value_0 = 0;
}

void stcom04_func_05E0(STCOM04_WORK *wp)
{
    STCOM_PL_WORK *pl;
    sint16 step;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            stcom04_func_00CC(wp);
            wp->routine_0++;
            break;
        case 1:
            if (stcom04_func_08E0(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            step           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x2A);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x40;
                pl->be_flag |= TRANS;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void stcom04_func_0748(STCOM04_WORK *wp, sint32 hit)
{
    STCOM04_CTL *ctl;
    sint32 speed;

    ctl   = &wp->ctl;
    speed = (uint16)ctl->rot_speed.y;
    if (hit == 0)
    {
        speed = (((rand() * *(uint16 *)0x1F800002) & 0xF) - 8) * 4;
    }
    else
    {
        hit >>= 12;
        if (hit & 1)
        {
            speed = 0x10;
        }
        if (hit & 2)
        {
            speed = -(sint16)speed;
        }
    }
    ctl->rot_speed.x = 0;
    ctl->rot_speed.y = speed;
    ctl->rot_speed.z = 0;
}

void stcom04_func_07D0(STCOM04_WORK *wp)
{
    uint32 dist;

    dist = Obj_distance_xyz(&Player_work, wp);
    if (dist < 600)
    {
        if (dist < 400)
        {
            if (wp->routine_0 != 4)
            {
                wp->routine_0 = 4;
            }
        }
        else if (wp->routine_0 != 3)
        {
            wp->routine_0 = 3;
            func_800322A8(wp, 2, 0);
            stcom04_func_08B8(wp, 0);
            stcom04_func_0898(wp, 1);
        }
    }
    else if (wp->routine_0 != 1 && wp->routine_0 != 2)
    {
        wp->routine_0 = 1;
        func_800322A8(wp, 1, 0);
        stcom04_func_08B8(wp, 0);
        stcom04_func_0898(wp, 1);
    }
}

void stcom04_func_0898(STCOM04_WORK *wp, uint8 on)
{
    if (on)
    {
        wp->value_107 = 0;
    }
    else
    {
        wp->value_107 = -1;
    }
}

void stcom04_func_08B8(STCOM04_WORK *wp, uint8 on)
{
    if (on)
    {
        wp->value_FF  = 0;
        wp->value_103 = 0;
    }
    else
    {
        wp->value_FF  = -1;
        wp->value_103 = -1;
    }
}

sint32 stcom04_func_08E0(STCOM04_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (pl->target_184 == wp)
    {
        wp->turn_64    = STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
        pl->target_184 = NULL;
        pl->be_flag &= ~TRANS;
        pl->flags_bd |= 0x40;
        stcom04_E_0000.x = wp->value_180.x;
        stcom04_E_0000.y = wp->value_180.y - 0x20;
        stcom04_E_0000.z = wp->value_180.z;
        func_80039FAC(&stcom04_E_0000, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void stcom04_func_0A10(STCOM04_WORK *wp, sint32 hit)
{
    if (hit != 0 && ++wp->count_C >= 0x3D)
    {
        wp->count_C     = 0;
        wp->rot_goal_66 = (wp->rotation.y + 2000 + (rand() & 0x3F)) & 0xFFF;
        wp->routine_0   = 8;
    }
}

uint8 stcom04_func_0A84(STCOM04_WORK *wp, uint32 *hit)
{
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, 0);
    if (Map_area_check(&wp->position) != 0)
    {
        func_80031824(wp);
        return 1;
    }
    *hit = Obj_map_push_out(wp);
    return 0;
}

void stcom04_func_0AF4(STCOM04_WORK *wp)
{
    wp->velocity.y += 4;
    wp->rotation.x += 0x20;
    if (wp->rotation.x > 0x400)
    {
        wp->rotation.x = 0x400;
    }
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void stcom04_func_0B58(STCOM04_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom04_D_0008[wp->routine_0](wp);
}

void stcom04_func_0BF4(STCOM04_WORK *wp)
{
    stcom04_func_00CC(wp);
    func_800322A8(wp, 3, rand() & 3);
    stcom04_func_08B8(wp, 1);
    stcom04_func_0898(wp, 0);
    wp->velocity.y = -0x10;
    wp->value_74   = 1;
    wp->position.y -= 0x50;
    wp->position_fixed.y = wp->position.y << 16;
    wp->routine_0++;
    Sound_call2(0x109, &wp->position);
}

void stcom04_func_0C88(STCOM04_WORK *wp)
{
    uint32 hit;

    hit = Obj_ceiling_height_get(wp) - 2000;
    if (wp->position.y < hit)
    {
        func_80031824(wp);
    }
    wp->velocity.y -= 0x10;
    if (!stcom04_func_0A84(wp, &hit))
    {
        func_80032488(wp);
    }
}
