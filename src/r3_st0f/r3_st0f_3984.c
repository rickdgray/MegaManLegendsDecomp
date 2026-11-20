#include "common.h"
#include "st0f.h"

void func_80103984(ST0F_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_801060F4[wp->routine_0](wp);
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

void func_80103A74(ST0F_OBJ *wp)
{
    STCOM_PL_WORK *pl;
    ST0F_CTL *ctl;
    sint16 turn;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            func_80103C28(wp);
            wp->routine_1++;
            break;
        case 1:
            if (func_80103CD8(wp))
            {
                wp->routine_1++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->value_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0)
            {
                if (func_8003A13C() == 0)
                {
                    func_80063BC8(&wp->position, 3, 0, func_80103E08());
                    func_800322A8(wp, 8, 0);
                    wp->routine_2 = 0;
                    wp->routine_1++;
                }
            }
            break;
        case 3:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                wp->routine_1++;
            }
            break;
        case 4:
            turn           = Angle_diff_clamp(ctl->angle_0, wp->rotation.y, wp->value_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0)
            {
                if (func_8003A13C() == 0)
                {
                    pl->flags_bd &= ~0x40;
                    pl->flags_0 |= 2;
                    wp->routine_1 = 1;
                }
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80103C28(ST0F_OBJ *wp)
{
    wp->value_64   = 0x80;
    wp->rotation.z = 0;
    wp->rotation.x = 0;
    wp->flags_0 |= 2;
    wp->ctl.angle_0 = wp->rotation.y;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = func_80048E6C(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_801060F8;
    func_800322A8(wp, 0, 0);
    wp->routine_2 = 0;
}

sint32 func_80103CD8(ST0F_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (pl->target_184 == wp)
    {
        wp->value_64   = STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x40;
        D_801061A0.x = wp->value_180.x;
        D_801061A0.y = wp->value_180.y - 0x20;
        D_801061A0.z = wp->value_180.z;
        func_80039FAC(&D_801061A0, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

sint32 func_80103E08(void)
{
    sint32 r;

    if (Sce_flag_test(0x211))
    {
        r = 0xA;
    }
    else if (Sce_flag_test(0x545))
    {
        r = 8;
    }
    else if (Sce_flag_test(0x209))
    {
        r = 7;
        Sce_flag_on(0x20A);
    }
    else
    {
        r = 5;
    }
    return r;
}

void func_80103E70(ST0F_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010612C[wp->variant_3](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_1 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_1++;
    }
}
