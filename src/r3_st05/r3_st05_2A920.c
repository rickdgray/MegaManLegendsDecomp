#include "common.h"
#include "st05.h"

void func_8012A920(STAGE_OBJ *wp)
{
    D_80137754[wp->routine_0](wp);
    wp->value_48.value = 0;
}

void func_8012A96C(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;
    sint32 y;

    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[3] = 0;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    scale.x = scale.y = scale.z = 0x400;
    ScaleMatrix(&wp->matrix.m, &scale);
    y             = func_80048EA4(&wp->pos_38, NULL, 0, wp->index_1);
    wp->color_40  = 0x808080;
    wp->pos_38.y  = y - 0xA;
    wp->model_10  = D_80137760;
    wp->value_48  = 0;
    wp->value_4C  = 0;
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_8012AA30(STAGE_OBJ50 *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (!Sce_flag_test(0x670))
    {
        if (wp->u_C.b.hi != 0)
        {
            wp->u_C.b.hi--;
        }
        else if (wp->u_C.b.lo == 0)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
            Sce_flag_on(0x670);
            return;
        }
        else
        {
            wp->u_C.b.lo--;
            wp->u_C.b.hi = 0x3C;
        }
    }
    if (pl->target_184 == wp)
    {
        wp->routine_1 = 0xA;
        wp->routine_0++;
        Sce_flag_on(0x670);
        return;
    }
    func_800341BC(&wp->pos_38, 0x28, 0, 0x8000, wp->index_1, &wp->value_48, 0x4000000, 0, 0x80);
}

void func_8012AB24(ST05_PRIZE *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_CAM *cam;
    STCOM_EFFECT *fx;

    cam = &Sce_camera_work;
    pl  = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl) != 0 && func_8003A13C() == 0)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            func_8001E6C0(0, 0, 0);
            cam->pos_10 = wp->pos_38.x << 16;
            cam->pos_14 = wp->pos_38.y << 16;
            cam->pos_18 = wp->pos_38.z << 16;
            cam->rot_40 = D_80137840[wp->variant_3][wp->value_E].x << 16;
            cam->rot_44 = D_80137840[wp->variant_3][wp->value_E].y << 16;
            cam->rot_48 = D_80137840[wp->variant_3][wp->value_E].z << 16;
            wp->routine_1++;
            break;
        case 2:
            if (func_8003A13C() == 0)
            {
                wp->timer_C = 0x1E;
                wp->routine_1++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0           = 5;
                fx->kind_2            = 0x80;
                fx->variant_3         = 0x41;
                fx->sprite.position   = wp->pos_38;
                fx->sprite.position.y = wp->pos_38.y - 0x32;
                Sound_call(0xA4, 0, 0);
                if (wp->variant_3 == 0)
                {
                    func_80037738(Map_cell_get(&wp->pos_38) | 0xF0000, 10000);
                }
                else if (wp->variant_3 == 1)
                {
                    func_80037738(Map_cell_get(&wp->pos_38) | 0xF0000, 10000);
                    Sce_flag_on(0x671);
                }
                else if (wp->variant_3 == 2)
                {
                    func_80037738(Map_cell_get(&D_80137820[wp->value_E]) | 0xF0000, 10000);
                    Sce_flag_on(0x672);
                }
                func_8012AFA0();
                wp->fx_44 = fx;
                wp->flags_0 &= ~2;
                wp->routine_1++;
            }
            break;
        case 5:
            fx = wp->fx_44;
            if ((sint8)fx->flags_0 == 0) // a signed byte test (lb)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->variant_3 != 0 ? 0x41 : 0x3E);
                wp->routine_1++;
            }
            break;
        case 6:
            if (D_800987B0[0] == 0)
            {
                D_800A395C = 1;
                func_80039820();
                wp->routine_1++;
            }
            break;
        case 10:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_448 = 0x30;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 11:
            pl->value_448 = 0x34;
            wp->timer_C   = 0x10;
            wp->routine_1++;
            break;
        case 12:
            if (wp->timer_C != 0)
            {
                wp->timer_C--;
            }
            else
            {
                wp->flags_0 &= ~2;
            }
            if (pl->flags_A7 < 0)
            {
                wp->routine_1++;
            }
            break;
        case 13:
            func_80063BC8(&wp->pos_38, 2, 0, (Sce_flag_test(0x671) || Sce_flag_test(0x672)) ? 0x40 : 0x3F);
            wp->routine_1++;
            break;
        case 14:
            if (!(Moji_flag & 0x08000000))
            {
                if (wp->variant_3 == 1)
                {
                    Sce_flag_on(0x671);
                }
                else if (wp->variant_3 == 2)
                {
                    Sce_flag_on(0x672);
                }
                func_8012AFA0();
                wp->routine_1++;
            }
            break;
        case 7:
        case 15:
            if (func_8003A13C() == 0)
            {
                func_80042314(pl);
                pl->flags_0 |= 2;
                func_80031A4C(wp);
                Sce_flag_off(0x670);
            }
            break;
        case 20:
            break;
    }
}

sint32 func_8012AFA0(void)
{
    if (Sce_flag_test(0x671) && Sce_flag_test(0x672))
    {
        if (!Sce_flag_test(0x575) || !Sce_flag_test(0x576))
        {
            if (Sce_flag_test(0x575))
            {
                func_8001E3F0(4);
            }
            else if (!Sce_flag_test(0x576))
            {
                func_8001E3F0(5);
            }
            else
            {
                func_8001E3F0(4);
            }
            Sce_flag_on(0x205);
            func_8001E390(0x2E6);
        }
        else
        {
            func_8001E3F0(8);
            func_8001E390(0x2E5);
        }
        Sce_flag_off(0x7E0);
        Sce_flag_off(0x236);
        Sce_flag_on(0x206);
        Game_work.value_78 = 1;
        return 1;
    }
    return 0;
}
