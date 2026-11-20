#include "common.h"
#include "st12.h"

void func_801018E0(void)
{
}

void func_801018E8(ST12_OBJ50 *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->value_C = 0;
            wp->routine_2++;
            break;
        case 1:
            wp->value_C -= 2;
            if (wp->value_C < -0x383)
            {
                wp->routine_2++;
            }
            break;
        case 10:
            wp->pos_38.y += 2;
            if (wp->pos_38.y >= 0x370)
            {
                wp->routine_2 = 2;
            }
            break;
        case 20:
            wp->pos_38.y -= 2;
            if (wp->pos_38.y >= 0x96)
            {
                wp->routine_2 = 2;
            }
            break;
        case 21:
            wp->pos_38.x -= 2;
            if (wp->pos_38.x < -0x95)
            {
                wp->routine_2 = 2;
            }
            break;
        case 22:
            wp->pos_38.x += 2;
            if (wp->pos_38.x >= 0x96)
            {
                wp->routine_2 = 2;
            }
            break;
    }
}

void func_801019E4(void)
{
}

void func_801019EC(ST12_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // never used; it reserves retail's frame
    STCOM_SVECTOR rot;
    ST12_MATRIX m;
    uint8 variant;

    switch (wp->routine_0)
    {
        case 0:
            variant = wp->variant_3;
            Model_work_init(wp, &variant);
            wp->color_40 = 0x808080;
            wp->routine_0++;
            break;
        case 1:
            ST12_IDENTITY(&wp->matrix);
            rot.x      = wp->value_C;
            rot.y      = D_80108BA0[wp->variant_3];
            m.words[0] = 0x1000;
            rot.z      = 0;
            m.words[1] = 0;
            m.words[2] = 0x1000;
            m.words[3] = 0;
            m.words[4] = 0x1000;
            m.words[5] = 0;
            m.words[6] = 0;
            m.words[7] = 0;
            RotMatrixYXZ(&rot, &m.m);
            MulMatrix(&wp->matrix.m, &m.m);
            D_80108B94[wp->routine_1](wp);
            break;
        case 2: // the empty case shapes retail's compare tree
            break;
    }
}
