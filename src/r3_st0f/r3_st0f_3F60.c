#include "common.h"
#include "st0f.h"

void func_80103F60(ST0F_OBJ *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_801043CC(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_80104490(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->value_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0)
            {
                if (func_8003A13C() == 0)
                {
                    func_80063BC8(&wp->position, 3, 0, func_801045C0());
                    func_800322A8(wp, 8, 0);
                    wp->routine_1 = 0;
                    wp->routine_0++;
                }
            }
            break;
        case 3:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x40;
                pl->be_flag |= TRANS;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801040E0(ST0F_OBJ *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_801043CC(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_80104490(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->value_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0)
            {
                if (func_8003A13C() == 0)
                {
                    func_80063BC8(&wp->position, 3, 0, 1);
                    func_800322A8(wp, 8, 0);
                    wp->routine_1 = 0;
                    wp->routine_0++;
                }
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x40;
                pl->be_flag |= TRANS;
                wp->routine_0 = 1;
                wp->type      = 0;
                Sce_flag_on(0x204);
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80104264(ST0F_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_801043CC(wp);
            wp->routine_0++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            func_8005C224(0x7D0);
            func_80063BC8(&wp->position, 2, 0, 0x21);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x40;
                pl->be_flag |= TRANS;
                Sce_flag_on(0x223);
                Sce_flag_on(0x214);
                Sce_flag_on(0x24C);
                func_8001E390(0x2E3);
                STAGE_GAME_BYTE(0x78) = 1;
                func_8001E3F0(0xA);
                wp->routine_0 = 1;
                wp->type      = 0;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801043CC(ST0F_OBJ *wp)
{
    wp->rotation.y = 0xC00;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0x80;
    wp->velocity.z = 0;
    wp->velocity.y = 0;
    wp->velocity.x = 0;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x1D701D7;
    wp->scale.words[1]   = 0x1D7;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_80106138;
    Sce_flag_off(0x223);
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

sint32 func_80104490(ST0F_OBJ *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (pl->target_184 == wp)
    {
        wp->value_64   = STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
        pl->target_184 = NULL;
        pl->be_flag &= ~TRANS;
        pl->flags_bd |= 0x40;
        D_801061B0.x = wp->value_180.x;
        D_801061B0.y = wp->value_180.y - 0x20;
        D_801061B0.z = wp->value_180.z;
        func_80039FAC(&D_801061B0, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

// The scene for the next talk, from the story flags.
sint32 func_801045C0(void)
{
    sint32 r;

    r = 0x23;
    if (!Sce_flag_test(0x222))
    {
        Sce_flag_on(0x222);
        return 0x22;
    }
    if (!func_80104798())
    {
        return 0x23;
    }
    if (Sce_flag_test(0x207))
    {
        if (Sce_flag_test(0x223))
        {
            return 0x24;
        }
    }
    else
    {
        if (Sce_flag_test(0x206))
        {
            if (Sce_flag_test(0x205))
            {
                r = 4;
            }
            else
            {
                r = 3;
                Sce_flag_on(0x24B);
            }
            Sce_flag_on(0x207);
            Sce_flag_on(0x223);
            return r;
        }
        if (Sce_flag_test(0x204))
        {
            return 2;
        }
        Sce_flag_on(0x204);
        Sce_flag_on(0x236);
        STAGE_GAME_BYTE(0x78) = 0;
        return 1;
    }
    if (!func_801047D8())
    {
        return 0x23;
    }
    if (Sce_flag_test(0x211))
    {
        if (Sce_flag_test(0x223))
        {
            return 0xB;
        }
    }
    else
    {
        if (Sce_flag_test(0x545))
        {
            Sce_flag_off(0x20A);
            Sce_flag_off(0x20B);
            Sce_flag_off(0x20C);
            Sce_flag_off(0x20D);
            Sce_flag_off(0x20E);
            Sce_flag_off(0x545);
            func_8001E390(0x2E7);
            func_8001E3F0(9);
            Sce_flag_on(0x211);
            Sce_flag_on(0x223);
            Sce_flag_on(0x568);
            return 9;
        }
        Sce_flag_on(0x209);
        return 6;
    }
    if (Sce_flag_test(0x214) && Sce_flag_test(0x223))
    {
        r = 0xB;
    }
    return r;
}

uint8 func_80104798(void)
{
    if (Sce_flag_test(0x1E))
    {
        return func_8003B2D4(6, 0x120) == 3;
    }
    return 0;
}

uint8 func_801047D8(void)
{
    if (Sce_flag_test(0x27))
    {
        return func_8003B2D4(5, 0x26) == 3;
    }
    return 0;
}
