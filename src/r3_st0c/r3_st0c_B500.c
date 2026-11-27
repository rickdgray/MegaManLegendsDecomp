#include "common.h"
#include "st0c.h"

void func_8010B500(void)
{
}

void func_8010B508(STAGE_FX *wp)
{
    wp->value_38.half[0] += 2;
    if (--wp->value_38.half[1] == -100)
    {
        wp->routine_1++;
    }
}

void func_8010B54C(void)
{
}

void func_8010B554(STAGE_FX *wp)
{
    wp->value_38.half[0] -= 2;
    if (++wp->value_38.half[1] == 0)
    {
        wp->routine_1 = 0;
    }
}

void func_8010B580(STAGE_OBJ *wp)
{
    D_8010D81C[wp->routine_1](wp);
}

void func_8010B5BC(void)
{
}

void func_8010B5C4(STAGE_FX *wp)
{
    wp->value_38.half[0] -= 2;
    if (++wp->value_38.half[1] == 100)
    {
        wp->routine_1++;
    }
}

void func_8010B608(void)
{
}

void func_8010B610(STAGE_FX *wp)
{
    wp->value_38.words.fraction += 2;
    wp->value_38.words.integer--;
    if ((sint16)wp->value_38.words.fraction == 0)
    {
        wp->routine_1 = 0;
    }
}

void func_8010B640(STAGE_OBJ *wp)
{
    D_8010D82C[wp->routine_1](wp);
}

void func_8010B67C(void)
{
}

void func_8010B684(STAGE_OBJ *wp)
{
    wp->u_C.timer += 0x11;
}

void func_8010B698(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        func_8010B67C();
        return;
    }
    func_8010B684(wp);
}

void func_8010B6D8(ST0C_WHEEL *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR unused_sv; // unused: retail's frame has room for it and the two matrices below
    STAGE_PANEL_MATRIX rot;
    STAGE_PANEL_MATRIX unused_m[2];
    if (wp->routine_0 == 0)
    {
        wp->be_flag |= MODEL;
        Model_work_init(wp, &wp->type);
        wp->value_10 = 0;
        wp->color_40 = 0x808080;
        wp->routine_0++;
    }
    D_8010D83C[wp->type](wp);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    scale.x = scale.y = scale.z = 0x1000;
    ScaleMatrix(&wp->matrix.m, &scale);
    rot.words[0] = 0x1000;
    rot.words[2] = 0x1000;
    rot.words[4] = 0x1000;
    rot.words[1] = 0;
    rot.words[3] = 0;
    rot.words[5] = 0;
    rot.words[6] = 0;
    rot.words[7] = 0;
    RotMatrixZ(wp->angle_C, &rot.m);
    MulMatrix(&wp->matrix.m, &rot.m);
}
