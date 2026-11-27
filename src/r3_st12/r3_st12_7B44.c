#include "common.h"
#include "st12.h"

void func_80107B44(ST12_ORBITER *wp)
{
    STCOM_FIXED_VECTOR scale = {0x200, 0x200, 0x200};
    ST12_ORBIT *orbit;
    orbit = &wp->orbit;
    if (wp->routine_0 == 0)
    {
        wp->orbit.angle_8 = 0x800;
        wp->be_flag |= 6;
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
