#include "common.h"
#include "st06.h"

// One sum variable shared by the six money cases (a global pseudo, so each case's pointer is
// allocated first and takes v0, as in retail).
void func_8010E4C4(ST06_ACTOR *wp)
{
    sint32 *value1;
    sint32 *value2;
    sint32 *value3;
    sint32 *value4;
    sint32 *value5;
    sint32 *value6;
    sint32 sum;

    switch (wp->routine_1)
    {
        case 0:
            if (!(Moji_flag & 0x80000000))
            {
                if ((Moji_flag & 0xFF) == 1)
                {
                    MojiTaskExec2(0, 0x63);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 0xFF;
                }
                else if ((Moji_flag & 0xFF) == 0)
                {
                    if (Money_check(-1) == -1)
                    {
                        MojiTaskExec2(0, 0x68);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                    }
                    else
                    {
                        MojiTaskExec2(0, 0x58);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 1;
                    }
                }
                else if ((Moji_flag & 0xFF) == 2)
                {
                    func_8005C224(0x5DC);
                    MojiTaskExec2(0, 0x67);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 9;
                }
            }
            break;
        case 1:
            if (!(Moji_flag & 0x80000000))
            {
                switch (Moji_flag & 0xFF)
                {
                    case 0:
                        func_8005C224(500 - STAGE_GAME.value_28);
                        break;
                    case 1:
                        func_8005C224(200 - STAGE_GAME.value_2C);
                        break;
                    case 2:
                        func_8005C224(250 - STAGE_GAME.value_30);
                        break;
                    case 3:
                        func_8005C224(200 - STAGE_GAME.value_34);
                        break;
                    case 4:
                        func_8005C224(STAGE_GAME.value_67 * 180 - STAGE_GAME.value_3C);
                        break;
                    case 5:
                        func_8005C224(STAGE_GAME.value_66 * 150 - STAGE_GAME.value_38);
                        break;
                    case 6:
                        wp->routine_1 = 0xFF;
                        return;
                }
                MojiTaskExec2(0, (Moji_flag & 0xFF) + 0x6C);
                wp->value_E = 8;
                wp->value_D = 1;
                wp->routine_1 += 1 + Moji_flag;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value1 = &STAGE_GAME.value_28;
                    sum    = *value1;
                    sum += D_800987E0;
                    *value1 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value2 = &STAGE_GAME.value_2C;
                    sum    = *value2;
                    sum += D_800987E0;
                    *value2 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value3 = &STAGE_GAME.value_30;
                    sum    = *value3;
                    sum += D_800987E0;
                    *value3 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value4 = &STAGE_GAME.value_34;
                    sum    = *value4;
                    sum += D_800987E0;
                    *value4 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value5 = &STAGE_GAME.value_3C;
                    sum    = *value5;
                    sum += D_800987E0;
                    *value5 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value6 = &STAGE_GAME.value_38;
                    sum    = *value6;
                    sum += D_800987E0;
                    *value6 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x80000000))
            {
                switch (Moji_flag & 0xFF)
                {
                    case 0:
                        MojiTaskExec2(0, 0x62);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                        break;
                    case 1:
                        MojiTaskExec2(0, 0x63);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                        break;
                    case 2:
                        func_8005C224(0x5DC);
                        MojiTaskExec2(0, 0x67);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 9;
                        break;
                }
            }
            break;
        case 9:
            if (!(Moji_flag & 0x80000000))
            {
                if (Moji_flag & 0xFF)
                {
                    MojiTaskExec2(0, 0x6A);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 0xFF;
                }
                else if (Money_check(-0x5DC) == -1)
                {
                    MojiTaskExec2(0, 0x68);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 0xFF;
                }
                else
                {
                    MojiTaskExec2(0, 0x69);
                    wp->value_E = 8;
                    wp->value_D = 1;
                    Money_add(-0x5DC, 0, 1);
                    Sce_flag_on(0x233);
                    wp->routine_1 = 0xFF;
                }
            }
            break;
        case 10:
            if (!(Moji_flag & 0x80000000))
            {
                switch (Moji_flag & 0xFF)
                {
                    case 0:
                        if (Money_check(-1) == -1)
                        {
                            MojiTaskExec2(0, 0x68);
                            wp->value_E   = 8;
                            wp->value_D   = 1;
                            wp->routine_1 = 0xFF;
                        }
                        else
                        {
                            MojiTaskExec2(0, 0x58);
                            wp->value_E   = 8;
                            wp->value_D   = 1;
                            wp->routine_1 = 1;
                        }
                        break;
                    case 1:
                        MojiTaskExec2(0, 0x57);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                        break;
                }
            }
            break;
        case 0xFF:
            if (!(Moji_flag & 0x80000000))
            {
                func_80039E18();
                wp->value_E = 1;
                wp->value_D = 1;
                wp->routine_0++;
            }
            break;
    }
    if (wp->value_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->value_E, 0);
        wp->value_D = 0;
    }
}

void func_8010EA84(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    turn           = Angle_diff_clamp(wp->rotation_prev.y, wp->rotation.y, wp->turn_64);
    pl             = &Player_work;
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_3 = 0;
        Player_work.flags_bd &= ~0x80;
        pl->flags_0 |= 2;
        Sce_flag_off(0x23D);
        Sce_flag_off(0x23E);
        Sce_flag_off(0x23F);
        Sce_flag_off(0x240);
        Sce_flag_off(0x241);
        Sce_flag_off(0x242);
        wp->routine_0 = 1;
    }
    else
    {
        func_80032488(wp);
    }
}

sint16 func_8010EB68(void)
{
    sint16 changed;

    changed = 0;
    if (func_8003B2D4(6, 0x205) != 3 && STAGE_GAME.value_28 != 500)
    {
        changed = 1;
        Sce_flag_on(0x23D);
    }
    if (func_8003B2D4(6, 0xFC) != 3 && STAGE_GAME.value_2C != 200)
    {
        changed = 1;
        Sce_flag_on(0x23E);
    }
    if (func_8003B2D4(6, 0x120) != 3 && STAGE_GAME.value_30 != 250)
    {
        changed = 1;
        Sce_flag_on(0x23F);
    }
    if (func_8003B2D4(5, 0x26) != 3 && STAGE_GAME.value_34 != 200)
    {
        changed = 1;
        Sce_flag_on(0x240);
    }
    if (STAGE_GAME.value_3C != STAGE_GAME.value_67 * 180)
    {
        changed = 1;
        Sce_flag_on(0x241);
    }
    if (STAGE_GAME.value_38 != STAGE_GAME.value_66 * 150)
    {
        changed = 1;
        Sce_flag_on(0x242);
    }
    return changed;
}

void func_8010ECE8(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_801251F0[wp->variant_3](wp);
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    wp->anim_prev_AD = wp->anim_AC;
}

void func_8010EDEC(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_8010EF94(wp);
        wp->routine_0++;
    }
}
