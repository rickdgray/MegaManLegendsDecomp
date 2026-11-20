#include "common.h"
#include "st0e.h"

void func_8010BC64(STAGE_OBJ *wp)
{
    D_801106A0[wp->variant_3](wp);
}

void func_8010BCA0(STAGE_OBJ *wp)
{
    D_801106B0[wp->routine_0](wp);
}

void func_8010BCDC(ST0E_LEVER *wp)
{
    STAGE_MATRIX_IDENTITY(wp->matrix.words);
    wp->matrix.f.rot.x = 0;
    wp->matrix.f.rot.y = 0;
    wp->matrix.f.rot.z = 0;
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->color_40  = 0x2C808080;
    if (wp->value_5 == 0)
    {
        wp->matrix.f.flag_1C = 0x605;
    }
    else if (wp->value_5 == 1)
    {
        wp->matrix.f.flag_1C = 0x606;
    }
    else
    {
        wp->matrix.f.flag_1C = 0x604;
    }
    func_8010BD90(wp);
}

void func_8010BD90(ST0E_LEVER *wp)
{
    STCOM_FIXED_VECTOR scale;
    D_801106BC[wp->routine_1](wp);
    RotMatrixYXZ(&wp->matrix.f.rot, &wp->matrix.m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(&wp->matrix.m, &scale);
}

void func_8010BE04(STAGE_OBJ *wp)
{
    func_80031A4C(wp);
}

void func_8010BE24(ST0E_LEVER *wp)
{
    if (!Sce_flag_test(wp->matrix.f.flag_1C))
    {
        if (wp->routine_2 != 0)
        {
            if (wp->routine_3 == 0)
            {
                wp->color_40  = 0x2C808080;
                wp->routine_2 = 0;
                wp->routine_3 = 0x80;
            }
            else
            {
                wp->routine_3--;
            }
        }
        else if (wp->routine_3 == 0)
        {
            if (wp->value_5 == 0)
            {
                wp->color_40 = 0x2C108010;
            }
            else if (wp->value_5 == 1)
            {
                wp->color_40 = 0x2C108080;
            }
            else
            {
                wp->color_40 = 0x2C101080;
            }
            wp->routine_2 = 1;
            wp->routine_3 = 2;
        }
        else
        {
            wp->routine_3--;
        }
    }
    else
    {
        wp->routine_1 = 1;
        if (wp->value_5 == 0)
        {
            wp->color_40 = 0x2C108010;
        }
        else if (wp->value_5 == 1)
        {
            wp->color_40 = 0x2C108080;
        }
        else
        {
            wp->color_40 = 0x2C101080;
        }
    }
}

void func_8010BF34(STAGE_FX *wp)
{
    if (Sce_flag_test((sint32)wp->z_34.words.fraction) == 0)
    {
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        wp->routine_3 = 0;
    }
}

void func_8010BF78(STAGE_OBJ *wp)
{
    D_801106C4[wp->routine_0](wp);
}

void func_8010BFB4(ST0E_PANEL *wp)
{
    ST0E_UV8 uv;
    ST0E_PART_REC *rec;
    uint32 i;

    wp->matrix_18.f.value_18 = 0x400;
    wp->matrix_18.f.lit_1C   = 0;
    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->variant_3);
    wp->color_40 = 0x02808080;
    if (Sce_flag_test(0x62D))
    {
        for (i = 0; i < 16; i++)
        {
            uv = D_80110CF4[wp->variant_3][i];
            func_8002D27C(wp->model_14, i | 0x10000, &uv);
        }
    }
    if (wp->variant_3 == 3)
    {
        Sce_flag_on(0x62D);
    }
    for (i = 0; i < 16; i++)
    {
        D_80110CF4[wp->variant_3][i] = *func_8002D22C(wp->model_14, i | 0x10000);
    }
    rec = wp->model_14->parts_70->recs_24;
    for (i = 0; i < 25; i++)
    {
        D_80110F42[wp->variant_3][i] = rec->value_2;
        rec++;
    }
    wp->value_A            = (wp->variant_3 - 1) * 16;
    wp->cell_44            = func_80048C60(&wp->pos_38);
    wp->cell_C             = STAGE_CELLS[wp->cell_44].value;
    wp->matrix_18.f.key_14 = func_8003AC24(D_80110698[0]);
    wp->routine_0          = 1;
    wp->routine_1          = 0;
    wp->routine_3          = 0;
}

void func_8010C1C0(ST0E_PANEL *wp)
{
    STAGE_PL_VIEW *pl;
    STCOM_SVECTOR vec;
    ST0E_UV8 uv;
    ST0E_PART_REC *rec;
    uint32 anim;
    uint32 i;
    sint8 lit;

    pl = &STAGE_PL;
    if (wp->variant_3 == 1)
    {
        if (Sce_flag_test(0x604))
        {
            lit           = 1;
            wp->routine_3 = 0;
        }
        else
        {
            lit = 0;
            if (++wp->routine_3 == 0x18)
            {
                Sound_call2(0x11D, &wp->pos_38);
                wp->routine_3 = 0;
            }
        }
    }
    else if (wp->variant_3 == 2)
    {
        if ((!Sce_flag_test(0x604) || !Sce_flag_test(0x605) || !Sce_flag_test(0x606)) && wp->matrix_18.f.lit_1C != 0)
        {
            vec.x = -0x2100;
            vec.y = -0xC81;
            vec.z = 0x1500;
            func_8003AC9C(func_80048D08(0, &vec), 0x71202);
            wp->matrix_18.f.lit_1C = 0;
        }
        if (Sce_flag_test(0x606))
        {
            lit           = 1;
            wp->routine_3 = 0;
        }
        else
        {
            lit = 0;
            if (++wp->routine_3 == 0x18)
            {
                Sound_call2(0x11B, &wp->pos_38);
                wp->routine_3 = 0;
            }
        }
    }
    else if (Sce_flag_test(0x605))
    {
        lit           = 1;
        wp->routine_3 = 0;
    }
    else
    {
        lit = 0;
        if (++wp->routine_3 == 0x18)
        {
            Sound_call2(0x11A, &wp->pos_38);
            wp->routine_3 = 0;
        }
    }
    if (lit == 0)
    {
        wp->color_40 = 0x02808080;
        wp->value_A += 2;
        if ((uint8)wp->value_A >= 0x40)
        {
            wp->value_A = 0;
        }
        anim = (uint8)wp->value_A;
        for (i = 0; i < 16; i++)
        {
            uv      = D_80110EF4[i];
            uv.b[0] = D_80110D74[wp->variant_3 - 1][i].b[0] + anim;
            uv.b[2] = D_80110D74[wp->variant_3 - 1][i].b[2] + anim;
            uv.b[4] = D_80110D74[wp->variant_3 - 1][i].b[4] + anim;
            uv.b[6] = D_80110D74[wp->variant_3 - 1][i].b[6] + anim;
            uv.b[1] = D_80110D74[wp->variant_3 - 1][i].b[1] - (wp->variant_3 - 1) * 16;
            uv.b[3] = D_80110D74[wp->variant_3 - 1][i].b[3] - (wp->variant_3 - 1) * 16;
            uv.b[5] = D_80110D74[wp->variant_3 - 1][i].b[5] - (wp->variant_3 - 1) * 16;
            uv.b[7] = D_80110D74[wp->variant_3 - 1][i].b[7] - (wp->variant_3 - 1) * 16;
            func_8002D27C(wp->model_14, i | 0x10000, &uv);
        }
        rec = wp->model_14->parts_70->recs_24;
        for (i = 0; i < 25; i++)
        {
            rec->value_2 = D_80110F42[wp->variant_3][i] - ((rand() & 7) - 4);
            rec++;
        }
    }
    else
    {
        wp->color_40 = 0x02000000;
        if (wp->variant_3 == 2 && Sce_flag_test(0x604) && Sce_flag_test(0x605) && Sce_flag_test(0x606) && wp->variant_3 == 2 &&
            wp->matrix_18.f.lit_1C == 0)
        {
            wp->matrix_18.f.lit_1C = 1;
            vec.x                  = -0x2100;
            vec.y                  = -0xC81;
            vec.z                  = 0x1500;
            func_8003AC9C(func_80048D08(0, &vec), 0x70202);
        }
    }
    if (pl->position.x >= -0x211F)
    {
        vec.x = 0;
        vec.y = 0x800;
    }
    else
    {
        vec.x = 0;
        vec.y = 0;
    }
    vec.z = 0;
    RotMatrixYXZ(&vec, &wp->matrix_18.m);
}

void func_8010C694(STAGE_OBJ *wp)
{
    func_80031A4C(wp);
}
