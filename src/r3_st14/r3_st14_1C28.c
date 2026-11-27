#include "common.h"
#include "st14.h"

void func_80101C28(STAGE_OBJ *wp)
{
    D_801154B0[wp->routine_0](wp);
}

void func_80101C64(STAGE_SPIN *wp)
{
    STCOM_EFFECT *effect;
    STAGE_SPIN *child;
    uint32 i;
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, &wp->type);
    wp->color_40 = 0x2808080;
    wp->angle_4C = 0;
    if (wp->type == 0)
    {
        for (i = 0; i < 7; i++)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                D_801162E0[i]   = effect;
                effect->be_flag = MOVE;
                effect->id      = 0x18;
                effect->type    = 0;
                effect->value_C = wp->work_id;
            }
        }
    }
    child = (STAGE_SPIN *)func_80031734();
    if (child != NULL)
    {
        child->be_flag  = wp->be_flag;
        child->id       = wp->id;
        child->type     = 1;
        child->work_0   = 0;
        child->work_1   = 0;
        child->work_2   = 0;
        child->work_3   = 0;
        child->pos_38.x = wp->pos_38.x;
        child->pos_38.y = wp->pos_38.y;
        child->pos_38.z = wp->pos_38.z;
        Model_work_init(child, &child->type);
        child->color_40 = 0x2C808080;
        child->angle_4C = 0;
        child->routine_0++;
        wp->slot_48 = child;
        wp->work_1++;
    }
    wp->routine_0++;
}

void func_80101DCC(STAGE_SPIN *wp)
{
    wp->matrix_18.w[1] = 0;
    wp->matrix_18.w[3] = 0;
    wp->matrix_18.w[5] = 0;
    wp->matrix_18.w[6] = 0;
    wp->matrix_18.w[7] = 0;
    wp->angle_4C += 0x20;
    wp->matrix_18.w[0] = 0x1000;
    wp->matrix_18.w[2] = 0x1000;
    wp->matrix_18.w[4] = 0x1000;
    RotMatrixY(wp->angle_4C, &wp->matrix_18.m);
    ScaleMatrix(&wp->matrix_18.m, &D_801154A0);
}

void func_80101E40(STAGE_SPIN *wp)
{
    uint32 i;

    func_80031A4C(wp);
    if (wp->work_1 != 0)
    {
        func_80031A4C(wp->slot_48);
    }
    for (i = 0; i < 7; i++)
    {
        func_80031988(D_801162E0[i]);
    }
}
