#include "common.h"
#include "st03.h"

void func_80111F98(STAGE_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->rand_BE             = rand();
    D_80117414[wp->routine_0](wp);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    if (wp->flags_0 & 1)
    {
        ((ST03_DRAW3_FUNC)func_80051B68)(wp, 1, -1);
    }
}

void func_80112098(STAGE_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->position_AC = wp->position;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->value_44    = 0;
    wp->value_48    = 0;
    wp->value_64    = 0;
    wp->value_70    = 0;
    wp->value_74    = 0;
    wp->flags_0 |= 6;
    func_8002F9C4(wp, NULL);
    wp->flags_BC = 0;
    wp->u_C0.w   = 0;
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->value_6E              = 0x400;
    wp->data_78               = D_80117424;
    wp->data_10               = D_80117430;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->color_B4              = 0x808080;
    func_80112190(wp);
}

void func_80112190(STAGE_PROP *wp)
{
    D_80117420[wp->routine_1](wp);
    wp->position_AC = wp->position;
    if (wp->flags_BC & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->flags_BC &= ~1;
    }
}

void func_80112220(STAGE_OBJ *wp)
{
    func_800318D8(wp);
}

void func_80112240(STAGE_PROP *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->u_C0.h[0] = 0;
            wp->value_44  = 0;
            wp->value_48  = 0;
            // fall through
        case 1:
            if (pl->target_184 == wp)
            {
                func_80063BC8(&wp->position, 0, 0, wp->value_C);
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_800987B0[0] == 0)
            {
                wp->routine_2--;
            }
            break;
    }
}
