#include "common.h"
#include "st08.h"

void func_8010A6F0(ST08_10C *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX *m;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    D_80113FE0[wp->routine_0](wp);
    m = &wp->matrix;
    RotMatrixYXZ(&wp->rotation.v, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    func_80051B68(wp, 1, -1, 0x1000008);
}

void func_8010A7E4(ST08_10C *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX *m;

    wp->pos_AC            = wp->position;
    wp->kind_2            = 4;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->turn_64           = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->rotation.v.x      = 0;
    wp->rotation.v.z      = 0;
    wp->flags_0 |= 6;
    wp->rotation.v.y = (wp->value_C << 9) & 0xE00;
    func_8002F9C4(wp, &wp->variant_3);
    m          = &wp->matrix;
    wp->kind_2 = 0x2F;
    RotMatrixYXZ(&wp->rotation.v, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    wp->value_6E = 0x400;
    wp->data_78  = D_80113FEC;
    wp->data_10  = NULL;
    wp->color_B4 = 0x808080;
    wp->routine_0++;
}

void func_8010A8E8(void)
{
}

void func_8010A8F0(STAGE_FX *wp)
{
    func_800318D8(wp);
}
