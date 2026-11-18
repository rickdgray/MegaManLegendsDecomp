#include "common.h"
#include "st0a.h"

void func_80114580(ST0A_PROP *wp)
{
    STCOM_FIXED_VECTOR scale = {0x200, 0x200, 0x200, 0};

    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 6;
        func_8002F9EC(wp, (sint32)&wp->variant_3);
        wp->color_40 = 0x808080;
        wp->routine_0++;
    }
    wp->matrix.w[0] = 0x1000;
    wp->matrix.w[1] = 0;
    wp->matrix.w[2] = 0x1000;
    wp->matrix.w[3] = 0;
    wp->matrix.w[4] = 0x1000;
    wp->matrix.w[5] = 0;
    wp->matrix.w[6] = 0;
    wp->matrix.w[7] = 0;
    ScaleMatrix(&wp->matrix.m, &scale);
    if (wp->variant_3 == 0)
    {
        func_8002CA10(&wp->position, 0x140, 0x200, 0);
    }
}
