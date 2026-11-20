#include "common.h"
#include "st03.h"

void func_801132BC(STAGE_OBJ *wp)
{
    D_8011748C[wp->routine_0](wp);
}

void func_801132F8(ST03_MODEL *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->variant_3);
    STAGE_MATRIX_IDENTITY(wp->matrix.w);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&wp->matrix.m, &scale);
    RotMatrixY(wp->angle_C << 5, &wp->matrix.m);
    wp->color_40 = 0x808080;
    wp->value_48 = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void func_801133AC(void)
{
}
