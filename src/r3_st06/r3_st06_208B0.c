#include "common.h"
#include "st06.h"

void func_801208B0(STAGE_OBJ *wp)
{
    D_8012B910[wp->routine_0](wp);
}

void func_801208EC(ST06_10C *wp)
{
    STCOM_MATRIX rot;

    wp->be_flag |= 6;
    Model_work_init(wp, NULL);
    wp->matrix_8C.w[0]      = 0x200;
    wp->matrix_8C.w[2]      = 0x200;
    wp->matrix_8C.w[4]      = 0x200;
    wp->matrix_8C.w[1]      = 0;
    wp->matrix_8C.w[3]      = 0;
    wp->matrix_8C.m.m[2][2] = 0x400;
    wp->routine_0++;
    RotMatrixYXZ(&wp->rotation, &rot);
    MulMatrix2(&rot, &wp->matrix_8C.m);
}

void func_80120968(ST06_10C *wp)
{
    ST06_PARTS *parts;
    STCOM_MATRIX rot;
    uint32 lit;

    lit   = wp->owner_B8->parts_2C8.lit_14;
    parts = &wp->owner_B8->parts_2C8;
    if (lit >> 1 == wp->type && (lit & 1))
    {
        wp->matrix_8C.w[0] = 0x200;
        wp->matrix_8C.w[1] = 0;
        wp->matrix_8C.w[2] = 0x200;
        wp->matrix_8C.w[3] = 0;
        wp->matrix_8C.w[4] = 0x200;
        RotMatrixYXZ(&wp->rotation, &rot);
        MulMatrix2(&rot, &wp->matrix_8C.m);
    }
    if (!(parts->mask_10 & (1 << wp->type)))
    {
        Close_SHL_WORK(wp);
    }
}

void func_80120A0C(STAGE_OBJ *wp)
{
    Close_SHL_WORK(wp);
}

void func_80120A2C(ST06_10C_B *wp, sint16 scale)
{
    STCOM_FIXED_VECTOR v;

    wp->pos_AC = wp->position;
    RotMatrixYXZ(&wp->rotation.v, &wp->matrix);
    v.x = scale;
    v.y = scale;
    v.z = scale;
    ScaleMatrix(&wp->matrix, &v);
}

void func_80120AAC(ST06_10C_B *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->value_C      = 0;
            wp->value_D      = 0;
            wp->turn_64      = 0;
            wp->rotation.v.x = 0;
            wp->rotation.v.z = 0;
            wp->turn_64      = 0;
            wp->value_70     = 0;
            wp->value_74     = 0;
            wp->color_B4     = 0x808080;
            wp->be_flag |= 6;
            func_80120A2C(wp, 0x200);
            wp->id   = 4;
            wp->type = 8;
            Model_work_init(wp, &wp->type);
            wp->id = 0x29;
            wp->routine_0++;
            break;
        case 1:
            if (wp->value_D == 0)
            {
                if (wp->rotation.v.y == 0x800)
                {
                    if (wp->position.z >= D_8012B91C[wp->value_C].limit_0)
                    {
                        wp->value_D = 8;
                    }
                }
                else if (wp->rotation.v.y == 0x400 && wp->position.x <= D_8012B91C[wp->value_C].limit_0)
                {
                    wp->value_D = 8;
                }
                if (wp->value_D == 8)
                {
                    if (D_8012B91C[wp->value_C].turn_2 == 0)
                    {
                        Close_SHL_WORK(wp);
                        break;
                    }
                    wp->value_C++;
                }
            }
            else
            {
                wp->rotation.v.y += D_8012B91C[wp->value_C - 1].turn_2;
                wp->value_D--;
            }
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            func_80120A2C(wp, 0x200);
            break;
    }
}
