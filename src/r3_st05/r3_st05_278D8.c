#include "common.h"
#include "st05.h"

void func_801278D8(STAGE_OBJ *wp)
{
    D_80137644[wp->routine_0](wp);
}

void func_80127914(STAGE_MATRIX_OBJ *wp)
{
    STCOM_FIXED_VECTOR scale;

    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    wp->be_flag |= 6;
    scale.z = 0x200;
    scale.y = 0x200;
    scale.x = 0x200;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    Model_work_init(wp, NULL);
    wp->color_40 = 0x808080;
    wp->routine_0++;
}

void func_801279A8(STAGE_OBJ *wp)
{
    func_80051B68(wp, 7, 0, 0);
}

void func_801279D0(STAGE_OBJ *wp)
{
    D_8013764C[wp->routine_0](wp);
}

void func_80127A0C(STAGE_OBJ50 *wp)
{
    if (wp->value_F != 0)
    {
        wp->matrix.words[0] = 0x1000;
        wp->matrix.words[2] = 0x1000;
        wp->matrix.words[4] = 0x1000;
        wp->matrix.words[1] = 0;
        wp->matrix.words[3] = 0;
        wp->matrix.words[5] = 0;
        wp->matrix.words[6] = 0;
        wp->matrix.words[7] = 0;
        wp->be_flag |= 6;
        D_80137FA8   = 0x400;
        D_80137FA4   = 0x400;
        D_80137FA0.x = 0x400;
        ScaleMatrix(&wp->matrix.m, &D_80137FA0);
        Model_work_init(wp, NULL);
        D_80137FB0    = 0;
        wp->color_40  = 0x808080;
        wp->value_E   = 0x10;
        wp->value_F   = 0;
        wp->routine_1 = 0;
        wp->routine_0++;
    }
}

void func_80127AD0(STAGE_OBJ50 *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (wp->value_E != 0)
            {
                wp->value_E--;
                D_80137FB0 -= 0x40;
            }
            else
            {
                wp->routine_1 = 1;
            }
            break;
        case 1:
            if (wp->value_F != 0)
            {
                wp->routine_1 = 2;
                wp->value_E   = 8;
                wp->value_F   = 0;
            }
            break;
        case 2:
            if (wp->value_E != 0)
            {
                wp->value_E--;
                D_80137FB0 += 0x80;
            }
            else
            {
                wp->routine_0++;
            }
            break;
    }
    STAGE_MATRIX_IDENTITY_SCALAR(wp->matrix.words);
    RotMatrixX(D_80137FB0, &wp->matrix.m);
    ScaleMatrix(&wp->matrix.m, &D_80137FA0);
}

void func_80127C28(STAGE_50 *wp)
{
    func_80031A4C(wp);
}
