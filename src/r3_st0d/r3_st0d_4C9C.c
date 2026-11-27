#include "common.h"
#include "st0d.h"

void func_80104C9C(ST0D_ACTOR *wp, uint16 *bob)
{
    sint32 msg;
    sint32 flag_on;
    sint32 flag;
    ST0D_CAM_SHOT *shot;
    STCOM_PL_WORK *pl;

    pl      = &Player_work;
    msg     = D_8010DC14[wp->work_1];
    flag_on = D_8010DC28[wp->work_1];
    flag    = D_8010DC74[wp->work_1];
    switch (wp->routine_1)
    {
        case 0:
            if (pl->target_184 == wp)
            {
                pl->target_184 = NULL;
                pl->flags_bd |= 0x40;
                wp->routine_1++;
            }
            break;
        case 1:
            if (msg != 0x7FFFFFFF)
            {
                MojiTaskExec2(0, msg);
            }
            wp->routine_1++;
            break;
        case 2:
            if (msg != 0x7FFFFFFF)
            {
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                if (flag != 0x7FFFFFFF)
                {
                    if (Sce_flag_test(flag))
                    {
                        Fade_start(10);
                        wp->routine_1 = 3;
                    }
                    else
                    {
                        wp->work_2    = 0;
                        wp->routine_1 = 4;
                    }
                }
                else
                {
                    wp->routine_1 = 4;
                }
            }
            else if (flag != 0x7FFFFFFF)
            {
                if (Sce_flag_test(flag))
                {
                    Fade_start(10);
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->work_2    = 0;
                    wp->routine_1 = 4;
                }
            }
            else
            {
                wp->routine_1 = 4;
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            pl->flags_bd &= ~0x40;
            wp->routine_1++;
            break;
        case 5:
            if (flag_on != 0x7FFFFFFF && (flag == 0x7FFFFFFF || Sce_flag_test(flag)))
            {
                Sce_flag_on(flag_on);
            }
            if (wp->work_2 == 1)
            {
                shot = D_8010DC60[wp->work_1];
                if (shot != (ST0D_CAM_SHOT *)0x7FFFFFFF)
                {
                    STAGE_CAM_REQ_PTR->mode_C   = shot->value_8;
                    STAGE_CAM_REQ_PTR->value_E  = shot->value_9;
                    STAGE_CAM_REQ_PTR->value_F  = shot->value_A;
                    STAGE_CAM_REQ_PTR->x_0      = shot->x_0;
                    STAGE_CAM_REQ_PTR->y_2      = shot->y_2;
                    STAGE_CAM_REQ_PTR->z_4      = shot->z_4;
                    STAGE_CAM_REQ_PTR->angle_A  = shot->value_6;
                    STAGE_CAM_REQ_PTR->value_D  = 0;
                    STAGE_CAM_REQ_PTR->value_11 = 0xFF;
                    if (wp->work_1 == 4)
                    {
                        STAGE_CAM_REQ_PTR->value_10 = 0xFF;
                    }
                    else
                    {
                        STAGE_CAM_REQ_PTR->value_10 = 2;
                    }
                }
                func_80052528(wp);
                Close_SHL_WORK(wp);
            }
            else
            {
                wp->work_2    = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_80104F40(STAGE_PROP *wp, uint16 *bob)
{
    STCOM_FIXED_VECTOR scale;
    scale                   = D_801000F0;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010DBF8[wp->routine_0](wp, bob);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
}

void func_80105058(STAGE_OBJ *wp, uint16 *bob)
{
    if (wp->u_C.b.work_0 == 0)
    {
        wp->position.y = bob[1] + ((D_800BBCF8[bob[0] & 0x3F] * 5) >> 12);
        bob[0]++;
    }
    else
    {
        wp->position.y = bob[1];
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

const STCOM_FIXED_VECTOR D_80100118 = {0x200, 0x200, 0x200, 0};

void func_801050E8(ST0D_ORBITER *wp)
{
    STCOM_FIXED_VECTOR scale;
    ST0D_ORBIT *orbit;
    scale = D_80100118;
    orbit = &wp->orbit;
    if (wp->routine_0 == 0)
    {
        wp->orbit.angle_8 = 0x800;
        wp->be_flag |= TRANS | MODEL;
        wp->rotation.x     = 0;
        wp->rotation.z     = 0;
        wp->orbit.x_0      = wp->position.x;
        wp->orbit.y_2      = wp->position.y;
        wp->orbit.z_4      = wp->position.z;
        wp->orbit.radius_C = wp->radius_D * 10;
        if (wp->reverse_F == 0)
        {
            wp->rotation.y    = 0x400;
            wp->orbit.speed_6 = wp->speed_E;
        }
        else
        {
            wp->rotation.y    = 0xC00;
            wp->orbit.speed_6 = -wp->speed_E;
        }
        wp->position.x  = orbit->x_0 + ((orbit->radius_C * rsin(0x800)) >> 12);
        wp->position.z  = orbit->z_4 + ((orbit->radius_C * rcos(0x800)) >> 12);
        wp->position_AC = wp->position;
        if (wp->value_C == 0)
        {
            Model_work_init(wp, NULL);
        }
        else
        {
            func_8002F9EC(wp, 0);
        }
        wp->color_B4 = 0x808080;
        wp->routine_0++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed;
        wp->rotation_prev       = wp->rotation;
        wp->orbit.angle_8       = (wp->orbit.angle_8 + wp->orbit.speed_6) & 0xFFF;
        wp->rotation.y          = (wp->rotation.y + wp->orbit.speed_6) & 0xFFF;
        wp->position.x          = wp->orbit.x_0 + ((wp->orbit.radius_C * rsin(wp->orbit.angle_8)) >> 12);
        wp->position.z          = wp->orbit.z_4 + ((wp->orbit.radius_C * rcos(wp->orbit.angle_8)) >> 12);
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    RotMatrixYXZ(&wp->rotation, &wp->matrix);
    ScaleMatrix(&wp->matrix, &scale);
    wp->position_AC = wp->position;
}

void func_801053C4(void)
{
}
