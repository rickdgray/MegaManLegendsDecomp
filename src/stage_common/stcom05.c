#include "common.h"
#include "stage_common/stcom05.h"

// Shared stage code, linked into 8 stages: r3_st03, r3_st05, r3_st06, r3_st08, r3_st0c,
// r3_st12, r3_st19 and r3_st1b. Each stage compiles this file against its own copy of the
// assembly (TARGET_ASM, set by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom05"

void stcom05_func_0000(STCOM05_WORK *wp)
{
    stcom05_D_0000[wp->type](wp);
}

void stcom05_func_003C(STCOM05_WORK *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom05_D_0008[wp->routine_0](wp);
    RotMatrixYXZ(&wp->rotation, &wp->matrix);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix, &scale);
    wp->pos_saved = wp->position;
    if (wp->be_flag & 1)
    {
        func_80051B68(wp, 1, -1, 0x1000008);
    }
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x104, 0x200, 1);
    }
}

void stcom05_func_0184(STCOM05_WORK *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->pos_saved         = wp->position;
    wp->rotation.x        = 0;
    wp->rotation.y        = 0;
    wp->rotation.z        = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->value_64          = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->accel_4C          = 2;
    Model_work_init(wp, NULL);
    wp->ctl.index_20 = 1;
    wp->ctl.value_1E = 0x140;
    RotMatrixYXZ(&wp->rotation, &wp->matrix);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix, &scale);
    wp->value_6E     = 0x400;
    wp->data_78      = stcom05_D_00B0;
    wp->data_10      = stcom05_D_00BC;
    wp->routine_0    = 1;
    wp->routine_1    = 0;
    wp->color_B4     = 0x808080;
    wp->ctl.flags_22 = 0xF;
    wp->ctl.value_23 = 0;
    wp->ctl.value_24 = 0;
    wp->ctl.value_25 = 0;
    wp->ctl.value_26 = 0;
    stcom05_func_029C(wp);
}

void stcom05_func_029C(STCOM05_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM05_CTL *ctl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (wp->param_C != 0)
    {
        return;
    }
    stcom05_func_0ED0(wp);
    stcom05_D_0018[wp->routine_1](wp);
    if (ctl->value_24 == 0 && Player_work.value_6E < Player_work.value_B0 / 2 && !(Moji_flag & 0x8000000))
    {
        MojiTaskExec2(0, 0x15);
        ctl->value_24 = 1;
    }
    if (ctl->value_25 != 0 && pl->flags_71 >= 0)
    {
        ctl->value_25 = 0;
    }
    if (pl->flags_71 < 0 && ctl->value_25 == 0 && !(Moji_flag & 0x8000000))
    {
        MojiTaskExec2(0, stcom05_D_00AC[ctl->value_26]);
        ctl->value_25 = 1;
        if (ctl->value_26 != 2)
        {
            ctl->value_26++;
        }
    }
    if (pl->target_184 == wp)
    {
        pl->target_184 = NULL;
        if (!(Moji_flag & 0x8000000))
        {
            pl->flags_bd |= 0x40;
            func_80042238(pl);
            MojiTaskExec2(0, 0x13);
            wp->routine_0 = 3;
            wp->routine_1 = 0;
        }
    }
}

void stcom05_func_0464(STCOM05_WORK *wp)
{
    Close_SHL_WORK(wp);
}

void stcom05_func_0484(STCOM05_WORK *wp)
{
    if (Moji_flag & 0x8000000)
    {
        return;
    }
    if (wp->routine_1 == 0)
    {
        Fade_start(10);
        wp->routine_1++;
    }
    else if (wp->routine_1 == 1)
    {
        D_800C356C         = 1;
        D_800C356E         = 3;
        D_800C3560         = -0xCA0;
        D_800C3562         = -1;
        D_800C3564         = 0x600;
        D_800C356A         = 0xC00;
        D_800C3571         = 0xFF;
        D_800C356F         = 1;
        D_800C356D         = 0;
        D_800C3570         = 2;
        Game_work.value_79 = 3;
        Game_work.value_7A = 1;
        wp->routine_1++;
    }
    else if (D_800C356C == 2 && D_80098A72 == 0)
    {
        D_800C356C++;
        func_80042314(&Player_work);
    }
}

void stcom05_func_05B8(STCOM05_WORK *wp)
{
    wp->rotation.y  = Angle_xz_svector(&wp->position, &stcom05_D_003C[wp->ctl.index_20]) & 0xFFF;
    wp->routine_1   = 1;
    wp->ctl.dist_14 = wp->ctl.dist_10 = Distance_xyz(&stcom05_D_003C[wp->ctl.index_20 - 1], &stcom05_D_003C[wp->ctl.index_20]);
}

void stcom05_func_0630(STCOM05_WORK *wp)
{
    sint32 diff;

    if (wp->velocity.v.x != wp->ctl.value_1E)
    {
        wp->velocity.v.x += wp->accel_4C;
    }
    Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    stcom05_func_0E64(wp);
    wp->ctl.dist_14 = wp->ctl.dist_10;
    wp->ctl.dist_10 = Distance_xyz(&wp->position, &stcom05_D_003C[wp->ctl.index_20]);
    if (wp->ctl.dist_14 < wp->ctl.dist_10)
    {
        wp->ctl.index_20++;
        if (wp->ctl.index_20 == 13)
        {
            wp->routine_1 = 3;
            wp->accel_4C  = 0x200;
            Sound_call2(0x180, &wp->position);
        }
        else
        {
            wp->routine_1       = 2;
            wp->ctl.rot_goal_18 = Angle_xz_svector(&wp->position, &stcom05_D_003C[wp->ctl.index_20]) & 0xFFF;
            diff                = wp->rotation.y - wp->ctl.rot_goal_18;
            wp->ctl.rot_diff_1A = STCOM_ABS(diff) & 0xFFF;
            if (wp->ctl.rot_diff_1A >= 0x800)
            {
                wp->ctl.rot_diff_1A = 0x1000 - wp->ctl.rot_diff_1A;
            }
            wp->ctl.rot_half_1C = wp->ctl.rot_diff_1A / 2;
        }
    }
}

void stcom05_func_0790(STCOM05_WORK *wp)
{
    STCOM05_CTL *ctl;

    ctl = &wp->ctl;
    if (abs(wp->rotation.y - wp->ctl.rot_goal_18) >= 0x800)
    {
        if (wp->ctl.rot_goal_18 < wp->rotation.y)
        {
            wp->rotation.y = (wp->rotation.y + 20) & 0xFFF;
            if (abs(wp->rotation.y - wp->ctl.rot_goal_18) < 0x800 && wp->rotation.y >= wp->ctl.rot_goal_18)
            {
                wp->rotation.y = wp->ctl.rot_goal_18;
                wp->routine_1  = 3;
                stcom05_func_0938(wp);
            }
        }
        else
        {
            wp->rotation.y = (wp->rotation.y - 20) & 0xFFF;
            if (abs(wp->rotation.y - wp->ctl.rot_goal_18) < 0x800 && wp->rotation.y <= wp->ctl.rot_goal_18)
            {
                wp->rotation.y = wp->ctl.rot_goal_18;
                wp->routine_1  = 3;
                stcom05_func_0938(wp);
            }
        }
    }
    else if (wp->ctl.rot_goal_18 < wp->rotation.y)
    {
        wp->rotation.y = (wp->rotation.y - 20) & 0xFFF;
        if (wp->rotation.y <= wp->ctl.rot_goal_18)
        {
            wp->rotation.y = wp->ctl.rot_goal_18;
            wp->routine_1  = 3;
            stcom05_func_0938(wp);
        }
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + 20) & 0xFFF;
        if (wp->rotation.y >= wp->ctl.rot_goal_18)
        {
            wp->rotation.y = wp->ctl.rot_goal_18;
            wp->routine_1  = 3;
            stcom05_func_0938(wp);
        }
    }
    if (ctl->rot_diff_1A > ctl->rot_half_1C)
    {
        wp->velocity.v.x -= wp->accel_4C;
    }
    else
    {
        wp->velocity.v.x += wp->accel_4C;
    }
    Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    stcom05_func_0E64(wp);
    ctl->rot_goal_18 = Angle_xz_svector(&wp->position, &stcom05_D_003C[ctl->index_20]) & 0xFFF;
}

void stcom05_func_0938(STCOM05_WORK *wp)
{
    STCOM05_CTL *ctl;

    ctl = &wp->ctl;
    switch (ctl->index_20)
    {
        case 2:
            if (wp->routine_2 == 0)
            {
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                MojiTaskExec2(0, 0x17);
                wp->velocity.v.x = 0;
                wp->routine_2++;
            }
            else if (wp->routine_2 == 1)
            {
                if (ctl->flags_22 & 1)
                {
                    break;
                }
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                wp->routine_2++;
                Cd_xa_seek_id(0x140006);
            }
            else if (wp->routine_2 == 2)
            {
                MojiTaskExec2(0, 0x16);
                wp->routine_2++;
            }
            else if (wp->routine_2 == 3)
            {
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                wp->routine_1 = 0;
                Sound_call2(0x17C, &wp->position);
                wp->velocity.v.x = 0;
                stcom05_func_05B8(wp);
                wp->routine_2 = 0;
            }
            break;
        case 5:
            if (!(ctl->flags_22 & 2))
            {
                wp->routine_2++;
            }
            else
            {
                if (ctl->value_23 == 0)
                {
                    Sound_call2(0x17D, &wp->position);
                    ctl->value_23 = 1;
                }
                wp->velocity.v.x = 0;
            }
            if (wp->routine_2 != 0)
            {
                wp->routine_1 = 0;
                if (wp->velocity.v.x == 0)
                {
                    Sound_call2(0x17C, &wp->position);
                }
                ctl->value_23 = 0;
                stcom05_func_05B8(wp);
                wp->routine_2 = 0;
            }
            break;
        case 7:
            if (!(ctl->flags_22 & 4))
            {
                wp->routine_2++;
            }
            else
            {
                if (ctl->value_23 == 0)
                {
                    Sound_call2(0x17D, &wp->position);
                    ctl->value_23 = 1;
                }
                wp->velocity.v.x = 0;
            }
            if (wp->routine_2 != 0)
            {
                wp->routine_1 = 0;
                if (wp->velocity.v.x == 0)
                {
                    Sound_call2(0x17C, &wp->position);
                }
                ctl->value_23 = 0;
                stcom05_func_05B8(wp);
                wp->routine_2 = 0;
            }
            break;
        case 10:
            if (!(ctl->flags_22 & 8))
            {
                wp->routine_2++;
            }
            else
            {
                if (ctl->value_23 == 0)
                {
                    Sound_call2(0x17D, &wp->position);
                    ctl->value_23 = 1;
                }
                wp->velocity.v.x = 0;
            }
            if (wp->routine_2 != 0)
            {
                wp->routine_1 = 0;
                if (wp->velocity.v.x == 0)
                {
                    Sound_call2(0x17C, &wp->position);
                }
                ctl->value_23 = 0;
                stcom05_func_05B8(wp);
                wp->routine_2 = 0;
                Cd_xa_seek_id(0x140009);
            }
            break;
        case 12:
            if (wp->routine_2 == 0)
            {
                if (ctl->value_23 == 0)
                {
                    Sound_call2(0x17D, &wp->position);
                    ctl->value_23 = 1;
                }
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                wp->routine_2++;
                MojiTaskExec2(0, 0x18);
                ctl->dist_14 = ctl->dist_10 = Distance_xyz(&stcom05_D_003C[ctl->index_20 - 1], &stcom05_D_003C[ctl->index_20 + 1]);
                wp->velocity.v.x            = 0;
            }
            else if (wp->routine_2 == 1)
            {
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                wp->routine_1 = 4;
                Sound_call2(0x17B, &wp->position);
                wp->routine_2++;
            }
            else if (ctl->timer_21 != 0)
            {
                ctl->timer_21--;
            }
            else
            {
                wp->routine_1 = 1;
                wp->accel_4C  = 0xF;
                Sound_call2(0x17E, &wp->position);
                wp->routine_2 = 0;
            }
            break;
        case 13:
            if (wp->velocity.v.x > 0)
            {
                Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
                wp->velocity.v.x -= wp->accel_4C;
            }
            else
            {
                wp->type           = 1;
                wp->velocity.v.x   = 0;
                wp->routine_0      = 0;
                wp->routine_1      = 0;
                wp->routine_2      = 0;
                Game_work.value_79 = 12;
                Game_work.value_7A = 0;
            }
            break;
        default:
            wp->routine_1 = 0;
            stcom05_func_05B8(wp);
            break;
    }
}

void stcom05_func_0D44(STCOM05_WORK *wp)
{
    STCOM05_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->velocity.v.x != 0x140)
    {
        wp->velocity.v.x += wp->accel_4C;
    }
    if (wp->rotation.y != 0x800)
    {
        wp->rotation.y -= 10;
        if (wp->rotation.y < 0x800)
        {
            wp->rotation.y = 0x800;
        }
    }
    func_8002FFC4(&wp->position, &wp->position_fixed, wp->rotation.y + 0x800, wp->velocity.v.x, 0, 0);
    stcom05_func_0E64(wp);
    ctl->dist_10 = Distance_xyz(&wp->position, &stcom05_D_0044[ctl->index_20]);
    if (ctl->dist_10 < 0x25D)
    {
        ctl->dist_14 = ctl->dist_10 = Distance_xyz(&wp->position, &stcom05_D_0044[ctl->index_20 - 1]);
        wp->routine_1               = 3;
        ctl->timer_21               = 0x3C;
        ctl->value_1E               = 0x400;
        wp->velocity.v.x            = 0;
    }
}

void stcom05_func_0E64(STCOM05_WORK *wp)
{
    sint32 value;

    value = func_80049C24(wp);
    if (value != 0)
    {
        func_80037BB4(wp);
        func_80037738(value, 0x8000);
        Sce_flag_on(0x30);
        Sce_flag_on(0x31C);
        Sound_call2(0x17F, &wp->position);
    }
}

void stcom05_func_0ED0(STCOM05_WORK *wp)
{
    if (wp->ctl.link[0]->id != 0x33)
    {
        wp->ctl.flags_22 &= ~1;
    }
    if (wp->ctl.link[1]->id != 0x33)
    {
        wp->ctl.flags_22 &= ~2;
    }
    if (wp->ctl.link[2]->id != 0x33)
    {
        wp->ctl.flags_22 &= ~4;
    }
    if (wp->ctl.link[3]->id != 0x33)
    {
        wp->ctl.flags_22 &= ~8;
    }
}

void stcom05_func_0F78(STCOM05_WORK *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom05_D_002C[wp->routine_0](wp);
    RotMatrixYXZ(&wp->rotation, &wp->matrix);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix, &scale);
    wp->pos_saved = wp->position;
    if (wp->be_flag & 1)
    {
        func_80051B68(wp, 1, -1, 0x20000008);
    }
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x104, 0x200, 1);
    }
}

void stcom05_func_10C0(STCOM05_WORK *wp)
{
    wp->pos_saved         = wp->position;
    wp->rotation.x        = 0;
    wp->rotation.z        = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->value_64          = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->be_flag |= 6;
    Model_work_init(wp, NULL);
    wp->data_78 = stcom05_D_00B0;
    wp->data_10 = stcom05_D_00BC;
    if (wp->param_D != 0)
    {
        wp->routine_0 = 3;
    }
    else
    {
        wp->routine_0 = 1;
    }
    wp->routine_2 = 0;
    wp->color_B4  = 0x808080;
}

void stcom05_func_1178(STCOM05_WORK *wp)
{
    if (Game_work.value_50 == 0x1B)
    {
        if (wp->routine_2 == 0)
        {
            if (STCOM_PLAYER_WORK_PTR->target_184 == wp)
            {
                STCOM_PLAYER_WORK_PTR->target_184 = NULL;
                if ((((STCOM_PLAYER_WORK_PTR->rotation.y & 0xFFF) - (wp->rotation.y & 0xFFF) + 0x180) & 0xFFF) < 0x300 &&
                    !(Moji_flag & 0x8000000))
                {
                    func_80063BC8(&Player_work, 0, 0, 0xD2);
                    wp->routine_2 = 1;
                }
            }
        }
        else if (!(Moji_flag & 0x8000000))
        {
            if ((Moji_flag & 0xFF) == 0)
            {
                Game_work.value_81 = 1;
                wp->routine_2      = 0;
            }
            else if ((Moji_flag & 0xFF) == 1)
            {
                wp->routine_2 = 0;
            }
        }
    }
    else if (STCOM_PLAYER_WORK_PTR->target_184 == wp)
    {
        STCOM_PLAYER_WORK_PTR->target_184 = NULL;
        if ((((STCOM_PLAYER_WORK_PTR->rotation.y & 0xFFF) - (wp->rotation.y & 0xFFF) + 0x180) & 0xFFF) < 0x300)
        {
            Game_work.value_81 = 1;
        }
    }
}

void stcom05_func_12D0(STCOM05_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->velocity.words[0] = 0;
            wp->velocity.words[1] = 0;
            // fall through
        case 1:
            if (pl->target_184 == wp)
            {
                func_80063BC8(&wp->position, 0, 0, wp->param_C);
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_800987B0[0] == 0)
            {
                wp->routine_2 = 1;
            }
            break;
    }
}

void stcom05_func_138C(STCOM05_WORK *wp)
{
    Close_SHL_WORK(wp);
}
