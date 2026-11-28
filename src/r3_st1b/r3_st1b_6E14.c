#include "common.h"
#include "st1b.h"

void func_80106E14(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010E7B0[wp->routine_0](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_2 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_2++;
    }
}

void func_80106F04(ST1B_ACTOR *wp)
{
    STAGE_PL_VIEW *pl;
    pl = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            func_8010706C(wp);
            wp->routine_1++;
            break;
        case 1:
            if (func_80107114(wp) == 0)
            {
                break;
            }
            wp->routine_1++;
            break;
        case 2:
            if (func_8003A13C() != 0)
            {
                break;
            }
            func_80063BC8(&wp->position, 5, 0, wp->timer_C);
            wp->routine_1++;
            break;
        case 3:
            if (Moji_flag & 0x8000000)
            {
                break;
            }
            func_80039E18();
            wp->routine_1++;
            break;
        case 4:
            if (func_8003A13C() != 0)
            {
                break;
            }
            if (*(uint8 *)&Moji_flag == 0)
            {
                wp->routine_1++;
                D_800989F8.routine_4 = 0;
                Sce_flag_off(0x1FF);
            }
            else
            {
                pl->flags_bd &= ~0x40;
                wp->routine_1 = 0;
            }
            pl->flags_0 |= 2;
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010706C(ST1B_VIEW *wp)
{
    sint16 temp_v0;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158        = 0x02000200;
    wp->u_15C.w[0]       = 0x200;
    wp->u_15C.h[1]       = 0x4210;
    wp->value_78         = 0;
    temp_v0              = Obj_ceiling_height_get(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
    wp->value_6E         = 0;
    wp->vec_AC.z         = 0;
    wp->vec_AC.pad       = 0;
    wp->value_10         = (sint32)D_8010E7B4;
    func_800322A8(wp, 3, 0);
    wp->routine_2 = 0;
}

sint32 func_80107114(ST1B_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (Player_work.target_184 == wp)
    {
        if ((sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
        {
            wp->turn_64 = (uint32) - (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        else
        {
            wp->turn_64 = (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x40;
        D_80113E74.x = wp->value_180.x;
        D_80113E74.y = wp->value_180.y - 0x20;
        D_80113E74.z = wp->value_180.z;
        func_80039FAC(&D_80113E74, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}
