#include "common.h"
#include "sub_scrn.h"

void func_8005EC34(void)
{
    Sub_screen_back_ground_set();
    D_8008DBB0[D_800A38F0.routine_0](&D_800A38F0);
}

sint32 func_8005EC80(sint32 *wp)
{
    MojiTaskKill();
    MojiTaskExec(0, D_8008CB94, -1);
    func_80063FC0(0, 0x20006);
    Sub_screen_basic_param_set();
    *wp = 1;
    return 0;
}

sint32 func_8005ECE0(sint32 *wp)
{
    Sub_screen_basic_param_set();
    if (Moji_flag & 0x40000000)
    {
        switch (Moji_flag & 0xFF)
        {
            case 0:
                *wp = 2;
                break;
            case 1:
                *wp = 3;
                break;
            case 2:
                *wp = 4;
                break;
            case 3:
                *wp = 5;
                break;
            case 4:
                *wp = 6;
                break;
            case 5:
                *wp = 8;
                break;
        }
    }
    else if (D_800C0C2A & 1)
    {
        *wp = 7;
    }
    else if (D_800C0C2A & 8)
    {
        *wp = 8;
    }
    return 0;
}

// The parts record offset is written as slot << 3: slot * 8 makes GCC put the offset first in the
// addu (retail adds pl first).
sint32 func_8005ED9C(SUB_WORK *wp)
{
    sint32 slot;
    SUB_PLAYER *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCC);
            wp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                func_8001D7AC(0x16);
                MojiTaskExec(1, (uint8 *)0x801F2000, 0x14);
                wp->routine_1++;
            }
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                wp->reserved4[0] = *(uint8 *)&Moji_flag3;
                if (wp->reserved4[0] != 0xFF)
                {
                    Sound_call(0x82, 1, 0);
                    Moji_flag |= 0x4000;
                    wp->routine_1++;
                }
                else
                {
                    Sound_call(0x83, 1, 0);
                }
            }
            else if (Sub_screen_cancel_check() != 0)
            {
                wp->routine_1 += 5;
            }
            else
            {
                Sub_screen_shift_check(wp);
            }
            break;
        case 3:
            switch (wp->reserved4[0])
            {
                case 0x40:
                    if (func_8005D95C() == 0)
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x58);
                        wp->routine_1 += 2;
                        break;
                    }
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x50);
                    wp->routine_1++;
                    break;
                case 0x41:
                    slot = pl->value_172;
                    if (D_8008D7E8[D_8008DB08[slot]][1][((sint8 *)pl + (slot << 3))[0x4F5]] == 0xFF)
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x3B);
                        wp->routine_1 += 2;
                        break;
                    }
                    if (func_80037604(pl, slot) == *(sint16 *)((uint8 *)pl + (slot << 3) + 0x4FA))
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x3A);
                        wp->routine_1 += 2;
                        break;
                    }
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x52);
                    wp->routine_1++;
                    break;
                case 0x42:
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x54);
                    wp->routine_1++;
                    break;
                case 0x43:
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x56);
                    wp->routine_1++;
                    break;
                default:
                    if (wp->reserved4[0] < 0x58)
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x5A);
                    }
                    else
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x5B);
                    }
                    wp->routine_1 += 2;
                    break;
            }
            break;
        case 4:
            if (Moji_flag & 0x40000000)
            {
                if (!(Moji_flag & 0xFF))
                {
                    switch (wp->reserved4[0])
                    {
                        case 0x40:
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x51);
                            func_8005D9C4();
                            wp->flag_C = 0x540;
                            break;
                        case 0x41:
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x53);
                            func_80037594();
                            wp->flag_C = 0x541;
                            break;
                        case 0x42:
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x55);
                            func_8005EBB4(0x708);
                            wp->flag_C = 0x542;
                            break;
                        case 0x43:
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x57);
                            func_8005EBA4(0x384);
                            wp->flag_C = 0x543;
                            break;
                    }
                    wp->routine_1 += 2;
                }
                else
                {
                    wp->routine_1++;
                }
            }
            break;
        case 5:
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                if (wp->routine_1 == 6)
                {
                    Sce_flag_off(wp->flag_C);
                }
                Moji_flag &= ~0x4000;
                wp->routine_1 = 2;
            }
            break;
        case 7:
            if (Cd_read_sync2() == 0)
            {
                *(uint32 *)wp = 0;
            }
            break;
    }
    return 0;
}

sint32 func_8005F210(SUB_SEL *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCC);
            wp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                break;
            }
            func_8001D7AC(0x16);
            MojiTaskExec(1, (uint8 *)0x801F2000, 0x19);
            func_80063FC0(0, 0x20002);
            wp->routine_1++;
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                wp->routine_1++;
                wp->index_4 = D_80098B2E;
            }
            else
            {
                if (Sub_screen_cancel_check() != 0)
                {
                    *(uint32 *)wp = 0;
                    break;
                }
                Sub_screen_shift_check((SUB_WORK *)wp);
                break;
            }
            // fall through
        case 3:
            switch (wp->index_4)
            {
                case 0:
                    func_8005F3D0(wp);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    func_8005F608(wp);
                    break;
                case 5:
                    wp->arg_5 = 0x45;
                    func_8005FAE4(wp);
                    break;
                case 6:
                case 7:
                case 8:
                    wp->arg_5 = 0x46;
                    func_8005FAE4(wp);
                    break;
                case 9:
                case 10:
                case 11:
                case 13:
                    wp->arg_5 = 0x47;
                    func_8005FAE4(wp);
                    break;
                case 12:
                    func_8005FBB4(wp);
                    break;
                case 14:
                case 15:
                case 16:
                case 17:
                    func_8005FFBC(wp);
                    break;
            }
            break;
    }
    return 0;
}

void func_8005F3D0(SUB_SEL *wp)
{
    sint32 msg;

    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(0x524) == 0)
            {
                Sound_call(0x83, 1, 0);
                wp->routine_2 += 2;
                return;
            }
            if (SUB_PLAYER_WORK->value_6E == SUB_PLAYER_WORK->value_B0)
            {
                Sound_call(0x82, 1, 0);
                msg = 0x40;
                MojiTaskExec(0, (uint8 *)0x801F2000, msg);
                wp->routine_2 += 2;
                return;
            }
            if (SUB_GAME_WORK->value_7C == 0)
            {
                Sound_call(0x82, 1, 0);
                msg = 0x41;
                MojiTaskExec(0, (uint8 *)0x801F2000, msg);
                wp->routine_2 += 2;
                return;
            }
            MojiTaskExec(0, (uint8 *)0x801F2000, 0x42);
            wp->routine_2++;
            return;
        case 1:
            if (Moji_flag & 0x40000000)
            {
                if (!(Moji_flag & 0xFF))
                {
                    if (SUB_GAME_WORK->value_7C <
                        ((SUB_PLAYER_WORK->value_B0 - (SUB_PLAYER_WORK->value_6E & 0xF0)) >> 4))
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x44);
                        SUB_PLAYER_WORK->value_6E =
                            (SUB_PLAYER_WORK->value_6E & 0xF0) + SUB_GAME_WORK->value_7C * 0x10;
                        SUB_GAME_WORK->value_7C = 0;
                    }
                    else
                    {
                        MojiTaskExec(0, (uint8 *)0x801F2000, 0x43);
                        SUB_GAME_WORK->value_7C -=
                            (SUB_PLAYER_WORK->value_B0 - (SUB_PLAYER_WORK->value_6E & 0xF0)) >> 4;
                        SUB_PLAYER_WORK->value_6E = SUB_PLAYER_WORK->value_B0;
                    }
                }
                wp->routine_2++;
            }
            return;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_8005F608(SUB_SEL *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[wp->index_4] + 0x520) != 0)
            {
                switch (wp->index_4)
                {
                    case 1:
                        if (Player_work.value_16A != 0)
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x33);
                        }
                        else
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x32);
                        }
                        break;
                    case 2:
                        if ((Player_work.flags_16b & 2))
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x39);
                        }
                        else
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x38);
                        }
                        break;
                    case 3:
                        if ((Player_work.flags_16b & 1))
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x35);
                        }
                        else
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x34);
                        }
                        break;
                    case 4:
                        if (Player_work.value_16C != 0)
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x49);
                        }
                        else
                        {
                            MojiTaskExec(0, (uint8 *)0x801F2000, 0x48);
                        }
                        break;
                }
                wp->routine_2++;
                return;
            }
            Sound_call(0x83, 1, 0);
            wp->routine_2 += 2;
            return;
        case 1:
            if (Moji_flag & 0x40000000)
            {
                if (!(Moji_flag & 0xFF))
                {
                    switch (wp->index_4)
                    {
                        case 1:
                            if (Player_work.value_16A != 0)
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x3D);
                            }
                            else
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x3C);
                            }
                            Player_work.value_16A ^= 1;
                            break;
                        case 2:
                            if ((Player_work.flags_16b & 2))
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x3F);
                            }
                            else
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x3E);
                            }
                            Player_work.flags_16b ^= 2;
                            break;
                        case 3:
                            if ((Player_work.flags_16b & 1))
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x37);
                            }
                            else
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x36);
                            }
                            Player_work.flags_16b ^= 1;
                            break;
                        case 4:
                            if (Player_work.value_16C != 0)
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x4B);
                                Player_work.value_16C = 0;
                            }
                            else
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x4A);
                                Player_work.value_16C = Sce_flag_test(0x53A) +
                                                        Sce_flag_test(0x53B) + Sce_flag_test(0x53C);
                            }
                            break;
                    }
                }
                wp->routine_2++;
            }
            return;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_8005F9E8(SUB_SEL *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[wp->index_4] + 0x520))
            {
                if (Player_work.flags_16b & 2)
                {
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x3F);
                }
                else
                {
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x3E);
                }
                Player_work.flags_16b ^= 2;
            }
            else
            {
                Sound_call(0x83, 1, 0);
            }
            wp->routine_2++;
            break;
        case 1:
            if ((Moji_flag & 0x8000000) == 0)
            {
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_8005FAE4(SUB_SEL *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[wp->index_4] + 0x520))
            {
                Sound_call(0x82, 1, 0);
                MojiTaskExec(0, (uint8 *)0x801F2000, wp->arg_5);
            }
            else
            {
                Sound_call(0x83, 1, 0);
            }
            wp->routine_2++;
            break;
        case 1:
            if ((Moji_flag & 0x8000000) == 0)
            {
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_8005FBB4(SUB_SEL *wp)
{
    SUB_GAME *gw;

    gw = &Game_work;
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[wp->index_4] + 0x520) != 0)
            {
                Sound_call(0x82, 1, 0);
                MojiTaskExec(0, (uint8 *)0x801F2000, 0x4C);
                wp->routine_2++;
            }
            else
            {
                Sound_call(0x83, 1, 0);
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
        case 1:
            switch (func_8005FDE4(gw))
            {
                case 0:
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x4D);
                    wp->routine_2 += 2;
                    break;
                case 1:
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x4E);
                    wp->routine_2++;
                    break;
                case 2:
                    MojiTaskExec(0, (uint8 *)0x801F2000, 0x4F);
                    wp->routine_2++;
                    break;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_8003B140();
                gw->value_50 = gw->value_79;
                gw->value_51 = gw->value_7A;
                func_80017C30(0x17);
                func_8001D854(0x10);
                wp->routine_2++;
            }
            break;
        case 4:
            func_80016D64();
            func_8001B33C();
            func_8001B314();
            D_80098958 |= 0x800;
            func_80019C20();
            func_8001F23C();
            func_8001F3C8();
            Game_work.routine_0 = 5;
            Game_work.routine_1 = 2;
            break;
    }
}

sint32 func_8005FDE4(SUB_GAME *gw)
{
    if (gw->value_78 == 0)
    {
    fail:
        return 2;
    }
    switch (gw->value_50)
    {
        case 3:
        case 27:
            if (Sce_flag_test(0x318) == 0 || gw->value_51 >= 3)
            {
                goto fail;
            }
            if (Sce_flag_test(0x55) != 0)
            {
                gw->value_79 = 0x1B;
            }
            else
            {
                gw->value_79 = 3;
            }
            gw->value_7A = 1;
            return 0;
        case 5:
            if (Sce_flag_test(0x319) == 0)
            {
                goto fail;
            }
            gw->value_79 = 5;
            gw->value_7A = 0;
            return 0;
        case 6:
            if (Sce_flag_test(0x31A) == 0)
            {
                goto fail;
            }
            gw->value_79 = 6;
            gw->value_7A = 0;
            return 0;
        case 8:
            if (Sce_flag_test(0x31B) == 0)
            {
                goto fail;
            }
            if (gw->value_51 >= 3 && gw->value_51 != 5)
            {
                goto fail;
            }
            gw->value_79 = 8;
            gw->value_7A = 0;
            return 0;
        case 12:
            if (Sce_flag_test(0x31C) == 0 || gw->value_51 != 0)
            {
                goto fail;
            }
            gw->value_79 = 0xC;
            gw->value_7A = 0;
            return 0;
        case 15:
            if (Sce_flag_test(0x31A) == 0)
            {
                goto fail;
            }
            gw->value_79 = 6;
            gw->value_7A = 0;
            return 0;
        case 18:
            if (Sce_flag_test(0x31F) == 0)
            {
                goto fail;
            }
            gw->value_79 = 0x12;
            gw->value_7A = 0;
            return 0;
        case 25:
            if (Sce_flag_test(0x31D) == 0 || gw->value_51 < 2)
            {
                goto fail;
            }
            gw->value_79 = 0x19;
            gw->value_7A = 3;
            return 0;
        default:
            return 1;
    }
}

void func_8005FFBC(SUB_SEL *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[wp->index_4] + 0x520) ||
                Sce_flag_test(D_8008DAF4[wp->index_4] + 0x521) ||
                Sce_flag_test(D_8008DAF4[wp->index_4] + 0x522))
            {
                Sound_call(0x82, 1, 0);
                MojiTaskExec(0, (uint8 *)0x801F2000, 0x47);
            }
            else
            {
                Sound_call(0x83, 1, 0);
            }
            wp->routine_2++;
            break;
        case 1:
            if ((Moji_flag & 0x8000000) == 0)
            {
                wp->routine_1 = 2;
                wp->routine_2 = 0;
            }
            break;
    }
}

sint32 func_800600CC(SUB_WORK *wp)
{

    switch (wp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCD);
            wp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            func_8001D7AC(0x16);
            MojiTaskExec(0, (uint8 *)0x801F2000, 0x1D);
            func_80063FC0(2, 0x20007);
            func_800605DC();
            wp->routine_1++;
            break;
        case 2:
            if ((Moji_flag & 0x480000FF) == 0x48000002)
            {
                Cd_read_comb(0x16);
                wp->routine_1++;
                break;
            }
            if ((Moji_flag & 0x8000000) == 0)
            {
                if (Moji_flag3 & 0x10000)
                {
                    if (Moji_flag3 & 0x40000)
                    {
                        func_80060248(wp);
                    }
                }
                else if (Moji_flag3 & 0x80000)
                {
                    func_80060248(wp);
                }
            }
            func_800605DC();
            Sub_screen_shift_check(wp);
            return 0;
        case 3:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            *(uint32 *)wp = 0;
            break;
    }
    return 0;
}

void func_80060248(SUB_WORK *wp)
{
    wp->mode_6         = 3;
    wp->entry[0].dst_0 = wp->entry[0].src_2;
    wp->entry[0].dst_3 = wp->entry[0].src_5;
    wp->entry[1].dst_0 = wp->entry[1].src_2;
    wp->entry[1].dst_3 = wp->entry[1].src_5;
    wp->entry[2].dst_0 = wp->entry[2].src_2;
    wp->entry[2].dst_3 = wp->entry[2].src_5;
    wp->entry[3].dst_0 = wp->entry[3].src_2;
    wp->entry[3].dst_3 = wp->entry[3].src_5;
    wp->entry[4].dst_0 = wp->entry[4].src_2;
    wp->entry[4].dst_3 = wp->entry[4].src_5;
}

void func_800602A4(SUB_WORK *wp, sint32 arg)
{
    sint8 step;

    step = wp->mode_6;
    if (step != 0)
    {
        wp->entry[0].src_2 = wp->entry[0].val_1 -
                             (((wp->entry[0].val_1 - wp->entry[0].dst_0) * (sint8)wp->mode_6) >> 2);
        wp->entry[0].src_5 = wp->entry[0].val_4 -
                             (((wp->entry[0].val_4 - wp->entry[0].dst_3) * (sint8)wp->mode_6) >> 2);
        wp->entry[1].src_2 = wp->entry[1].val_1 -
                             (((wp->entry[1].val_1 - wp->entry[1].dst_0) * (sint8)wp->mode_6) >> 2);
        wp->entry[1].src_5 = wp->entry[1].val_4 -
                             (((wp->entry[1].val_4 - wp->entry[1].dst_3) * (sint8)wp->mode_6) >> 2);
        wp->entry[2].src_2 = wp->entry[2].val_1 -
                             (((wp->entry[2].val_1 - wp->entry[2].dst_0) * (sint8)wp->mode_6) >> 2);
        wp->entry[2].src_5 = wp->entry[2].val_4 -
                             (((wp->entry[2].val_4 - wp->entry[2].dst_3) * (sint8)wp->mode_6) >> 2);
        wp->entry[3].src_2 = wp->entry[3].val_1 -
                             (((wp->entry[3].val_1 - wp->entry[3].dst_0) * (sint8)wp->mode_6) >> 2);
        wp->entry[3].src_5 = wp->entry[3].val_4 -
                             (((wp->entry[3].val_4 - wp->entry[3].dst_3) * (sint8)wp->mode_6) >> 2);
        wp->entry[4].src_2 = wp->entry[4].val_1 -
                             (((wp->entry[4].val_1 - wp->entry[4].dst_0) * (sint8)wp->mode_6) >> 2);
        wp->entry[4].src_5 = wp->entry[4].val_4 -
                             (((wp->entry[4].val_4 - wp->entry[4].dst_3) * (sint8)wp->mode_6) >> 2);
        wp->mode_6--;
    }
    else
    {
        wp->entry[0].src_2 = wp->entry[0].val_1;
        wp->entry[0].src_5 = wp->entry[0].val_4;
        wp->entry[1].src_2 = wp->entry[1].val_1;
        wp->entry[1].src_5 = wp->entry[1].val_4;
        wp->entry[2].src_2 = wp->entry[2].val_1;
        wp->entry[2].src_5 = wp->entry[2].val_4;
        wp->entry[3].src_2 = wp->entry[3].val_1;
        wp->entry[3].src_5 = wp->entry[3].val_4;
        wp->entry[4].src_2 = wp->entry[4].val_1;
        wp->entry[4].src_5 = wp->entry[4].val_4;
    }
    if (arg == 0)
    {
        Sub_screen_gauge_set(0xCB, 0x28, wp->entry[0].src_2, 0);
        Sub_screen_gauge_set(0xCB, 0x28, wp->entry[0].src_5, 1);
        Sub_screen_gauge_set(0xCB, 0x32, wp->entry[1].src_2, 0);
        Sub_screen_gauge_set(0xCB, 0x32, wp->entry[1].src_5, 1);
        Sub_screen_gauge_set(0xCB, 0x3C, wp->entry[2].src_2, 0);
        Sub_screen_gauge_set(0xCB, 0x3C, wp->entry[2].src_5, 1);
        Sub_screen_gauge_set(0xCB, 0x46, wp->entry[3].src_2, 0);
        Sub_screen_gauge_set(0xCB, 0x46, wp->entry[3].src_5, 1);
        return;
    }
    Sub_screen_gauge_set2(0xA4, 0x9E, wp->entry[0].src_2, wp->entry[0].flag_6);
    Sub_screen_gauge_set2(0xA4, 0xA8, wp->entry[1].src_2, wp->entry[1].flag_6);
    Sub_screen_gauge_set2(0xA4, 0xB2, wp->entry[2].src_2, wp->entry[2].flag_6);
    Sub_screen_gauge_set2(0xA4, 0xBC, wp->entry[3].src_2, wp->entry[3].flag_6);
    Sub_screen_gauge_set2(0xA4, 0xC6, wp->entry[4].src_2, wp->entry[4].flag_6);
    if (wp->reserved4[1] != 0)
    {
        Sub_screen_status_param_set(wp->reserved4[1]);
    }
}

void func_800605DC(void)
{
    Sub_screen_rb_parts_calc(&D_800A38F0);
    func_800602A4(&D_800A38F0, 0);
}

// Case 2's menu switch sits one loop level deeper in retail (do { } while (0), likely a
// Capcom macro): the doubled weight of pl's uses there gives pl s1 and slot s2.
sint32 func_80060618(SUB_WORK *wp)
{
    SUB_PLAYER *pl;
    uint16 pad;
    sint32 slot;
    uint32 n;

    pl  = &Player_work;
    pad = D_800C0C2A;
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCD);
            wp->reserved4[1] = 0;
            wp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                break;
            }
            func_8001D7AC(0x16);
            if (pl->value_170 != 0)
            {
                MojiTaskExec(0, (uint8 *)0x801F2000, 0x5C);
            }
            else
            {
                MojiTaskExec(0, (uint8 *)0x801F2000, 0x5D);
            }
            if (!(Moji_flag & 0x04000000))
            {
                MojiTaskExec(1, (uint8 *)0x801F2000, 0x2F);
                if (pl->value_172 == 0)
                {
                    func_80063FC0(0, 0x2001C);
                }
                func_80063FC0(1, 0x20009);
                func_80063FC0(2, 0x20017);
                func_80063FC0(3, 0x20008);
                Sub_screen_status_calc(wp, 0);
            }
            func_800602A4(wp, 1);
            wp->routine_1++;
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                do
                {
                    switch (Moji_flag & 0xFF)
                    {
                        case 0:
                            Sound_call(0x82, 1, 0);
                            wp->routine_1++;
                            break;
                        case 1:
                            if (pl->value_172 == 0)
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x61);
                            }
                            else if (pl->value_44E <= 0)
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x60);
                            }
                            else if (pl->value_44F == 0)
                            {
                                func_8005C218(pl->value_172 + 0x80);
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x5E);
                                pl->value_44F = 1;
                                pl->value_170 = pl->value_172;
                            }
                            else
                            {
                                MojiTaskExec(0, (uint8 *)0x801F2000, 0x5F);
                                pl->value_44F = 0;
                                pl->value_170 = 0;
                            }
                            wp->routine_1 += 3;
                            break;
                        case 2:
                            Sound_call(0x83, 1, 0);
                            MojiTaskKill();
                            Game_logo_kill(-1);
                            Cd_read_comb(0x16);
                            wp->routine_1 += 4;
                            break;
                    }
                } while (0);
            }
            else
            {
                Sub_screen_shift_check(wp);
            }
            func_800602A4(wp, 1);
            break;
        case 3:
            n                = D_80098B2D;
            wp->reserved4[0] = n;
            if ((wp->reserved4[1] = n) != 0)
            {
                wp->reserved4[1] = n + 1;
            }
            slot = wp->reserved4[1];
            if (wp->reserved4[0] < 0xD && Sce_flag_test(slot + 0x4C0) != 0)
            {
                func_80063FC0(1, (wp->reserved4[0] + 9) | 0x20000);
                if (pl->value_172 == slot)
                {
                    func_80063FC0(0, 0x2001C);
                }
                else
                {
                    Game_logo_kill(0);
                }
                Sub_screen_status_calc(wp, slot);
            }
            else
            {
                wp->reserved4[1] = 0;
                func_80063FC0(1, 0x20016);
                Game_logo_kill(0);
                Sub_screen_status_calc(wp, -1);
            }
            if (Moji_flag3 & 0x40000)
            {
                func_80060248(wp);
            }
            if (Moji_flag & 0x40000000)
            {
                if (wp->reserved4[0] == 0xD)
                {
                    Sound_call(0x82, 1, 0);
                    wp->routine_1 += 2;
                }
                else if (Sce_flag_test(slot + 0x4C0) != 0)
                {
                    Sound_call(0x82, 1, 0);
                    MojiTaskExec(0, (uint8 *)0x801F2000, wp->reserved4[0] + 0xE4);
                    wp->routine_1++;
                }
                else
                {
                    Sound_call(0x83, 1, 0);
                }
            }
            else if (pad & 0x1008)
            {
                Sound_call(0x83, 1, 0);
                wp->routine_1 += 2;
            }
            else
            {
                Sub_screen_shift_check(wp);
            }
            func_800602A4(wp, 1);
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1 = 3;
                wp->routine_2 = 0;
            }
            func_800602A4(wp, 1);
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1 = 1;
                wp->routine_2 = 0;
            }
            func_800602A4(wp, 1);
            break;
        case 6:
            if (Cd_read_sync2() == 0)
            {
                *(uint32 *)wp = 0;
            }
            break;
    }
    return 0;
}

sint32 func_80060B00(SUB_WORK *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCC);
            wp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            func_8001D7AC(0x16);
            MojiTaskExec(0, D_8008CB64, -1);
            wp->routine_1++;
            break;
        case 2:
            if ((Moji_flag & 0x40000000) || (D_800C0C2A & 8))
            {
                if (D_800C0C2A & 8)
                {
                    Sound_call(0x83, 1, 0);
                }
                MojiTaskKill();
                func_800425FC(&Player_work, Game_work.value_54);
                Cd_read_comb(0x16);
                wp->routine_1++;
            }
            else
            {
                Sub_screen_shift_check(wp);
                return 0;
            }
            break;
        case 3:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            *(uint32 *)wp = 0;
            break;
    }
    return 0;
}

sint32 func_80060C70(SUB_SEL *wp)
{
    Sub_screen_basic_param_set();
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskExec(0, D_8008CE78, -1);
            wp->routine_1++;
            break;
        case 1:
            if (Moji_flag & 0x40000000)
            {
                if ((Moji_flag & 0xFF) != 0)
                {
                    *(uint32 *)wp = 0;
                }
                else
                {
                    MojiTaskExec(0, D_8008CE84, -1);
                    wp->routine_1++;
                }
            }
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                if ((Moji_flag & 0xFF) != 0)
                {
                    *(uint32 *)wp = 0;
                }
                else
                {
                    MojiTaskKill();
                    func_80063BA8();
                    func_80063EF0();
                    func_800665E8();
                    func_8001B314();
                    func_8001B33C();
                    func_8001D494(0, 1, 0);
                    Sce_flag_off(0x1FE);
                    Code800133D8_work.value_0 = 1;
                    func_80012F78(func_80013420);
                }
            }
            break;
    }
    return 0;
}

sint32 func_80060DB8(SUB_PARTS *wp)
{
    SUB_PLAYER *pl;

    pl = &Player_work;
    if (wp->slot_b != Player_work.value_170 || wp->slot_8 != Player_work.slot.v.half_0 ||
        wp->slot_a != Player_work.slot.v.byte_2)
    {
        Pl00_shot_enable_off(pl);
        Pl00_shot_enable_on(pl);
        if (wp->slot_b != pl->value_170)
        {
            Obj_work_flag_change(8, 0x80);
        }
        pl->value_110 = 0;
    }
    return 1;
}

sint32 Sub_screen_cancel_check(void)
{
    if (D_800C0C2A & 0x1008)
    {
        Sound_call(0x83, 1, 0);
        MojiTaskKill();
        Game_logo_kill(-1);
        Cd_read_comb(0x16);
        return 1;
    }
    return 0;
}

void Sub_screen_shift_check(SUB_WORK *wp)
{
    uint16 pad;

    pad = D_800C0C2A;
    if (pad & 0xC00)
    {
        Sound_call(0x82, 1, 0);
        MojiTaskKill();
        Game_logo_kill(-1);
        if (pad & 0x400)
        {
            wp->routine_0--;
            if (wp->routine_0 < 2)
            {
                wp->routine_0 = 6;
            }
        }
        else
        {
            wp->routine_0++;
            if (wp->routine_0 >= 7)
            {
                wp->routine_0 = 2;
            }
        }
        wp->routine_1 = 0;
        // One halfword store clears routine_2 and routine_3.
        *(uint16 *)&wp->routine_2 = 0;
    }
}

void Sub_screen_sort_attack(void)
{
    sint32 i;
    sint32 j;
    SUB_PLAYER *wp;

    wp = &Player_work;
    for (i = 0; i < 0x1F; i++)
    {
        for (j = 0; j < 0x1F - i; j++)
        {
            if (wp->order[j + 1] != 0)
            {
                if (wp->order[j] == 0 || Rock_buster_parts_tbl[wp->order[j] - 1][0].s <
                                             Rock_buster_parts_tbl[wp->order[j + 1] - 1][0].s)
                {
                    Sub_screen_sort_sub(wp, j, j + 1);
                }
            }
        }
    }
}

void Sub_screen_sort_energy(void)
{
    sint32 i;
    sint32 j;
    SUB_PLAYER *wp;

    wp = &Player_work;
    for (i = 0; i < 0x1F; i++)
    {
        for (j = 0; j < 0x1F - i; j++)
        {
            if (wp->order[j + 1] != 0)
            {
                if (wp->order[j] == 0 ||
                    D_8008FE65[wp->order[j] - 1][0].s < D_8008FE65[wp->order[j + 1] - 1][0].s)
                {
                    Sub_screen_sort_sub(wp, j, j + 1);
                }
            }
        }
    }
}

void Sub_screen_sort_range(void)
{
    sint32 i;
    sint32 j;
    SUB_PLAYER *wp;

    wp = &Player_work;
    for (i = 0; i < 0x1F; i++)
    {
        for (j = 0; j < 0x1F - i; j++)
        {
            if (wp->order[j + 1] != 0)
            {
                if (wp->order[j] == 0 ||
                    D_8008FE66[wp->order[j] - 1][0].s < D_8008FE66[wp->order[j + 1] - 1][0].s)
                {
                    Sub_screen_sort_sub(wp, j, j + 1);
                }
            }
        }
    }
}

void Sub_screen_sort_rapid(void)
{
    sint32 i;
    sint32 j;
    SUB_PLAYER *wp;

    wp = &Player_work;
    for (i = 0; i < 0x1F; i++)
    {
        for (j = 0; j < 0x1F - i; j++)
        {
            if (wp->order[j + 1] != 0)
            {
                if (wp->order[j] == 0 ||
                    D_8008FE67[wp->order[j] - 1][0].s < D_8008FE67[wp->order[j + 1] - 1][0].s)
                {
                    Sub_screen_sort_sub(wp, j, j + 1);
                }
            }
        }
    }
}

void Sub_screen_sort_sub(SUB_PLAYER *wp, sint32 a, sint32 b)
{
    uint8 tmp;

    tmp          = wp->order[a];
    wp->order[a] = wp->order[b];
    wp->order[b] = tmp;
}

void Sub_screen_rb_parts_set(void)
{
    SUB_PLAYER *pl;
    sint32 i;
    sint32 n;
    sint32 slot;

    pl                   = &Player_work;
    n                    = Sce_flag_test(0x526) ? 3 : 2;
    Player_work.sum[0].u = 0;
    Player_work.sum[1].u = 0;
    Player_work.sum[2].u = 0;
    Player_work.sum[3].u = 0;
    for (i = 0; i < n; i++)
    {
        slot = pl->slot.b[i];
        if (slot != 0)
        {
            slot--;
            pl->sum[0].u += Rock_buster_parts_tbl[slot][0].u;
            pl->sum[1].u += D_8008FE65[slot][0].u;
            pl->sum[2].u += D_8008FE66[slot][0].u;
            pl->sum[3].u += D_8008FE67[slot][0].u;
        }
    }
    if (pl->sum[0].s > 7)
    {
        pl->sum[0].s = 7;
    }
    if (pl->sum[1].s > 7)
    {
        pl->sum[1].s = 7;
    }
    if (pl->sum[2].s > 7)
    {
        pl->sum[2].s = 7;
    }
    if (pl->sum[3].s > 7)
    {
        pl->sum[3].s = 7;
    }
}

void Sub_screen_rb_parts_calc(SUB_WORK *wp)
{
    SUB_PLAYER *pl;
    sint32 i;
    sint32 n;
    sint32 slot;

    pl                 = &Player_work;
    n                  = Sce_flag_test(0x526) ? 3 : 2;
    wp->entry[0].val_4 = 0;
    wp->entry[0].val_1 = 0;
    wp->entry[1].val_4 = 0;
    wp->entry[1].val_1 = 0;
    wp->entry[2].val_4 = 0;
    wp->entry[2].val_1 = 0;
    wp->entry[3].val_4 = 0;
    wp->entry[3].val_1 = 0;
    if (Moji_flag & 0x8000000)
    {
        for (i = 0; i < n; i++)
        {
            slot = pl->slot.b[i];
            if (slot != 0)
            {
                slot--;
                Sub_screen_rb_parts_calc_sub00(wp, slot);
                Sub_screen_rb_parts_calc_sub01(wp, slot);
            }
        }
    }
    else if (Moji_flag3 & 0x10000)
    {
        for (i = 0; i < n; i++)
        {
            slot = pl->slot.b[i];
            if (slot != 0)
            {
                Sub_screen_rb_parts_calc_sub00(wp, slot - 1);
            }
            if (i != D_80098B2D && slot != 0)
            {
                Sub_screen_rb_parts_calc_sub01(wp, slot - 1);
            }
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            slot = pl->slot.b[i];
            if (slot != 0)
            {
                Sub_screen_rb_parts_calc_sub00(wp, slot - 1);
            }
            if (i == D_80098B2D)
            {
                slot = D_80098B31;
            }
            if (slot != 0)
            {
                Sub_screen_rb_parts_calc_sub01(wp, slot - 1);
            }
        }
    }
}

void Sub_screen_rb_parts_calc_sub00(SUB_WORK *wp, sint32 idx)
{
    wp->entry[0].val_1 += Rock_buster_parts_tbl[idx][0].s * 10;
    wp->entry[1].val_1 += D_8008FE65[idx][0].s * 10;
    wp->entry[2].val_1 += D_8008FE66[idx][0].s * 10;
    wp->entry[3].val_1 += D_8008FE67[idx][0].s * 10;
    if (wp->entry[0].val_1 > 0x46)
    {
        wp->entry[0].val_1 = 0x46;
    }
    if (wp->entry[1].val_1 > 0x46)
    {
        wp->entry[1].val_1 = 0x46;
    }
    if (wp->entry[2].val_1 > 0x46)
    {
        wp->entry[2].val_1 = 0x46;
    }
    if (wp->entry[3].val_1 > 0x28)
    {
        wp->entry[3].val_1 = 0x28;
    }
}

void Sub_screen_rb_parts_calc_sub01(SUB_WORK *wp, sint32 idx)
{
    wp->entry[0].val_4 += Rock_buster_parts_tbl[idx][0].s * 10;
    wp->entry[1].val_4 += D_8008FE65[idx][0].s * 10;
    wp->entry[2].val_4 += D_8008FE66[idx][0].s * 10;
    wp->entry[3].val_4 += D_8008FE67[idx][0].s * 10;
    if (wp->entry[0].val_4 > 0x46)
    {
        wp->entry[0].val_4 = 0x46;
    }
    if (wp->entry[1].val_4 > 0x46)
    {
        wp->entry[1].val_4 = 0x46;
    }
    if (wp->entry[2].val_4 > 0x46)
    {
        wp->entry[2].val_4 = 0x46;
    }
    if (wp->entry[3].val_4 > 0x28)
    {
        wp->entry[3].val_4 = 0x28;
    }
}

void Sub_screen_status_calc(SUB_WORK *arg, sint32 slot)
{
    SUB_PLAYER *pl;
    SUB_WORK *wp;

    wp = arg;
    pl = &Player_work;
    if (slot < 0)
    {
        wp->entry[0].flag_6 = 0;
        wp->entry[0].val_1  = 0;
        wp->entry[1].flag_6 = 0;
        wp->entry[1].val_1  = 0;
        wp->entry[2].flag_6 = 0;
        wp->entry[2].val_1  = 0;
        wp->entry[3].flag_6 = 0;
        wp->entry[3].val_1  = 0;
        wp->entry[4].flag_6 = 0;
        wp->entry[4].val_1  = 0;
        return;
    }
    wp->entry[0].val_1 = D_8008D7E8[D_8008DB08[slot]][0][((sint8 *)pl)[slot * 8 + 0x4F4 + 0]];
    wp->entry[1].val_1 = D_8008D7E8[D_8008DB08[slot]][1][((sint8 *)pl)[slot * 8 + 0x4F4 + 1]];
    wp->entry[2].val_1 = D_8008D7E8[D_8008DB08[slot]][2][((sint8 *)pl)[slot * 8 + 0x4F4 + 2]];
    wp->entry[3].val_1 = D_8008D7E8[D_8008DB08[slot]][3][((sint8 *)pl)[slot * 8 + 0x4F4 + 3]];
    wp->entry[4].val_1 = D_8008D7E8[D_8008DB08[slot]][4][((sint8 *)pl)[slot * 8 + 0x4F4 + 4]];
    if (wp->entry[0].val_1 == 0xFF)
    {
        wp->entry[0].val_1  = 0x58;
        wp->entry[0].flag_6 = 1;
    }
    else
    {
        wp->entry[0].flag_6 = 0;
    }
    if (wp->entry[1].val_1 == 0xFF)
    {
        wp->entry[1].val_1  = 0x58;
        wp->entry[1].flag_6 = 1;
    }
    else
    {
        wp->entry[1].flag_6 = 0;
    }
    if (wp->entry[2].val_1 == 0xFF)
    {
        wp->entry[2].val_1  = 0x58;
        wp->entry[2].flag_6 = 1;
    }
    else
    {
        wp->entry[2].flag_6 = 0;
    }
    if (wp->entry[3].val_1 == 0xFF)
    {
        wp->entry[3].val_1  = 0x58;
        wp->entry[3].flag_6 = 1;
    }
    else
    {
        wp->entry[3].flag_6 = 0;
    }
    if (wp->entry[4].val_1 == 0xFF)
    {
        wp->entry[4].val_1  = 0x58;
        wp->entry[4].flag_6 = 1;
    }
    else
    {
        wp->entry[4].flag_6 = 0;
    }
}

void Sub_screen_gauge_set(sint32 x, sint32 y, sint32 width, sint32 row)
{
    POLY_FT4 *start;
    POLY_FT4 *p;
    sint32 sx;

    p                 = *(POLY_FT4 **)0x1F800070;
    p->tag            = (((uint32)(p + 1)) & 0xFFFFFF) | 0x09000000;
    *(uint32 *)&p->r0 = 0x2C808080;
    p->x0 = p->x2 = x;
    p->x1 = p->x3 = x + width + 6;
    p->y0 = p->y1 = y + row * 2;
    p->y2 = p->y3     = y + row * 2 + 5;
    p->tpage          = 0xC;
    p->clut           = 0x3E83;
    *(uint16 *)&p->u0 = ((row * 8 + 0x90) << 8) | 0x60;
    *(uint16 *)&p->u1 = ((row * 8 + 0x90) << 8) | 0x61;
    *(uint16 *)&p->u2 = ((row * 8 + 0x95) << 8) | 0x60;
    *(uint16 *)&p->u3 = ((row * 8 + 0x95) << 8) | 0x61;
    start             = p;
    p++;
    p->tag            = (((uint32)(p + 1)) & 0xFFFFFF) | 0x09000000;
    *(uint16 *)&p->u0 = ((row * 8 + 0x90) << 8) | 0x6F;
    *(uint32 *)&p->r0 = 0x2C808080;
    p->x0 = p->x2 = x + width + 6;
    p->x1 = p->x3 = x + width + 0xA;
    p->y0 = p->y1 = y + row * 2;
    p->y2 = p->y3     = y + row * 2 + 5;
    p->tpage          = 0xC;
    p->clut           = 0x3E83;
    *(uint16 *)&p->u1 = ((row * 8 + 0x90) << 8) | 0x73;
    *(uint16 *)&p->u2 = ((row * 8 + 0x95) << 8) | 0x6F;
    *(uint16 *)&p->u3 = ((row * 8 + 0x95) << 8) | 0x73;
    p++;
    if (row == 0)
    {
        if ((y != 0x46 && width == 0x46) || (y == 0x46 && width == 0x28))
        {
            // The sprite is linked and advanced with the POLY_FT4 stride.
            ((SPRT *)p)->tag            = (((uint32)(p + 1)) & 0xFFFFFF) | 0x04000000;
            *(uint32 *)&((SPRT *)p)->r0 = 0x64808080;
            sx                          = x + 0xA;
            if (width == 0x46)
            {
                ((SPRT *)p)->x0 = x + 0x18;
            }
            else
            {
                ((SPRT *)p)->x0 = sx;
            }
            ((SPRT *)p)->y0             = y;
            *(uint32 *)&((SPRT *)p)->u0 = 0x3E82F028;
            *(uint32 *)&((SPRT *)p)->w  = 0x60018;
            p++;
        }
    }
    *(POLY_FT4 **)0x1F800070 = p;
    addPrims(&((SUB_OT78 *)D_80098934)->tag_78, start, p - 1);
}

void Sub_screen_gauge_set2(sint32 x, sint32 y, sint32 width, sint32 flag)
{
    POLY_FT4 *start;
    POLY_FT4 *p;
    SPRT *sp;

    p      = *(POLY_FT4 **)0x1F800070;
    p->tag = (((uint32)(p + 1)) & 0xFFFFFF) | 0x09000000;
    p->x0 = p->x2     = x;
    *(uint16 *)&p->u0 = 0x9048;
    *(uint16 *)&p->u1 = 0x9049;
    *(uint16 *)&p->u2 = 0x9848;
    *(uint32 *)&p->r0 = 0x2C808080;
    p->x1 = p->x3 = x + width;
    p->y0 = p->y1 = y;
    p->y2 = p->y3     = y + 8;
    p->tpage          = 0xC;
    p->clut           = 0x3E83;
    *(uint16 *)&p->u3 = 0x9849;
    start             = p;
    p++;
    p->tag            = (((uint32)(p + 1)) & 0xFFFFFF) | 0x09000000;
    *(uint16 *)&p->u0 = 0x904C;
    *(uint16 *)&p->u1 = 0x9050;
    *(uint16 *)&p->u2 = 0x984C;
    *(uint32 *)&p->r0 = 0x2C808080;
    p->x0 = p->x2 = x + width;
    p->x1 = p->x3 = x + width + 4;
    p->y0 = p->y1 = y;
    p->y2 = p->y3     = y + 8;
    p->tpage          = 0xC;
    p->clut           = 0x3E83;
    *(uint16 *)&p->u3 = 0x9850;
    p++;
    if (flag != 0 && width == 0x58)
    {
        // The sprite is linked and advanced with the POLY_FT4 stride.
        sp                 = (SPRT *)p;
        sp->tag            = (((uint32)(p + 1)) & 0xFFFFFF) | 0x04000000;
        *(uint32 *)&sp->r0 = 0x64808080;
        sp->x0             = x + 0x18;
        sp->y0             = y;
        *(uint32 *)&sp->u0 = 0x3E82F828;
        *(uint32 *)&sp->w  = 0x80028;
        p++;
    }
    *(POLY_FT4 **)0x1F800070 = p;
    addPrims(&((SUB_OT78 *)D_80098934)->tag_78, start, p - 1);
}

void Sub_screen_basic_param_set(void)
{
    SUB_PRIM *start;
    SUB_PRIM *p;
    sint32 i;
    sint32 n;
    sint32 cur;
    uint32 uv;

    p       = *(SUB_PRIM **)0x1F800070;
    n       = (Player_work.value_B0 - 1) >> 4;
    cur     = Player_work.value_6E;
    p->tag  = 0x02000000;
    p->rgbc = 0xE100000D;
    p->xy   = 0;
    p->tag  = (((uint32)(p + 1)) & 0xFFFFFF) | 0x02000000;
    start   = p;
    p++;
    for (i = 0; i <= n; i++)
    {
        p->tag  = (((uint32)(p + 1)) & 0xFFFFFF) | 0x04000000;
        p->rgbc = 0x64808080;
        p->xy   = (0x31 + i * 5) | 0x240000;
        p->wh   = 0x80008;
        if (i * 0x10 < cur)
        {
            if (i * 0x10 < cur - 0x10 || !(cur & 0xF))
            {
                uv = 0x3E75B870;
            }
            else
            {
                uv = 0x3E75B878;
            }
        }
        else
        {
            uv = 0x3E75B880;
        }
        p->uv_clut = uv;
        p++;
    }
    p = Sub_screen_basic_param_set_sub(p, 0x2400A4, Game_work.value_1C, 0x306);
    p = Sub_screen_basic_param_set_sub(p, 0x240106, Game_work.timer_0c / 108000, 2);
    p = Sub_screen_basic_param_set_sub(p, 0x24011A, (Game_work.timer_0c / 1800) % 60, 2);
    *(SUB_PRIM **)0x1F800070 = p;
    addPrims(&((SUB_OT78 *)D_80098934)->tag_78, start, p - 1);
}

// The draw test recomputes the first index ((flags & 0xFF) - 1) inside the loop. The larger
// loop body keeps loop.c from hoisting the primitive constants, as in retail.
SUB_PRIM *Sub_screen_basic_param_set_sub(SUB_PRIM *prim, sint32 x, sint32 value, sint32 flags)
{
    sint32 i;
    sint32 digit;

    for (i = (flags & 0xFF) - 1; i >= 0; i--)
    {
        digit = value % 10;
        if ((i == (flags & 0xFF) - 1 && !(flags & 0x200)) || value != 0 || !(flags & 0x100))
        {
            prim->tag     = (((uint32)(prim + 1)) & 0xFFFFFF) | 0x04000000;
            prim->rgbc    = 0x64808080;
            prim->xy      = x + i * 7;
            prim->wh      = 0x80008;
            prim->uv_clut = ((digit * 8) + 0x60) | 0x3E75B000;
            prim++;
        }
        value /= 10;
    }
    return prim;
}

void Sub_screen_status_param_set(sint32 slot)
{
    SUB_PRIM *start;
    SUB_PRIM *p;
    sint32 cur;
    sint32 max;

    p     = *(SUB_PRIM **)0x1F800070;
    cur   = SUB_PLAYER_HALF_4FA(slot);
    start = p;
    max   = func_80037604(&Player_work, slot);
    if (max < 0x7FFF)
    {
        p->tag  = 0x02000000;
        p->rgbc = 0xE100000C;
        p->tag  = ((uint32)(p + 1) & 0xFFFFFF) | 0x02000000;
        p->xy   = 0;
        p++;
        p->tag     = ((uint32)(p + 1) & 0xFFFFFF) | 0x04000000;
        p->rgbc    = 0x64808080;
        p->xy      = 0x8C00D1;
        p->wh      = 0x80006;
        p->uv_clut = 0x3E82F040;
        p          = Sub_screen_status_param_set_sub(
            Sub_screen_status_param_set_sub(p + 1, 0x8C00B4, cur, 4), 0x8C00D8, max, 4);
        p[-1].tag = (p[-1].tag & 0xFF000000) | (((SUB_OT78 *)D_80098934)->tag_78 & 0xFFFFFF);
        ((SUB_OT78 *)D_80098934)->tag_78 =
            (((SUB_OT78 *)D_80098934)->tag_78 & 0xFF000000) | ((uint32)start & 0xFFFFFF);
        *(SUB_PRIM **)0x1F800070 = p;
    }
}

// The draw test recomputes the first index ((flags & 0xFF) - 1) inside the loop. The larger
// loop body keeps loop.c from hoisting the primitive constants, as in retail.
SUB_PRIM *Sub_screen_status_param_set_sub(SUB_PRIM *prim, sint32 x, sint32 value, sint32 flags)
{
    sint32 i;
    sint32 digit;

    for (i = (flags & 0xFF) - 1; i >= 0; i--)
    {
        digit = value % 10;
        if ((i == (flags & 0xFF) - 1 && !(flags & 0x200)) || value != 0 || !(flags & 0x100))
        {
            prim->tag     = (((uint32)(prim + 1)) & 0xFFFFFF) | 0x04000000;
            prim->rgbc    = 0x64808080;
            prim->xy      = x + i * 7;
            prim->wh      = 0x80006;
            prim->uv_clut = (digit * 8) | 0x3E82C000;
            prim++;
        }
        value /= 10;
    }
    return prim;
}

void Sub_screen_back_ground_set(void)
{
    SUB_PRIM *start;
    SUB_PRIM *p;
    sint32 row;
    sint32 col;
    sint32 x;
    sint32 y;
    sint32 shift;

    p       = *(SUB_PRIM **)0x1F800070;
    p->tag  = 0x02000000;
    p->rgbc = 0xE100000D;
    p->xy   = 0;
    p->tag  = (((uint32)(p + 1)) & 0xFFFFFF) | 0x02000000;
    start   = p;
    p++;
    for (row = 0; row < 5; row++)
    {
        y = row * 0x40 - 0x40;
        for (col = 0; col < 7; col++)
        {
            x          = col * 0x40 - 0x40;
            p->tag     = (((uint32)(p + 1)) & 0xFFFFFF) | 0x04000000;
            p->rgbc    = 0x64808080;
            shift      = *(uint16 *)0x1F800002 & 0x3F;
            p->uv_clut = 0x3E7788C0;
            p->wh      = 0x400040;
            p->xy      = ((x + shift) & 0xFFFF) | ((y + shift) << 16);
            p++;
        }
    }
    *(SUB_PRIM **)0x1F800070 = p;
    addPrims(&D_80098934->tag_8C, start, p - 1);
}

void Sub_screen_sound_reinit(SUB_SND *wp)
{
    if ((wp->flags_8 & 0xFFFF00) == 0x40300)
    {
        Sound_call(0x8C, 0, 0);
    }
    if (wp->value_174 & 0xC0)
    {
        if ((wp->value_174 & 0xC0) == 0x40)
        {
            if (wp->value_170 == 4)
            {
                if (wp->value_178 == 2)
                {
                    Sound_call2(0x123, wp->args_3c8);
                }
            }
            if (wp->value_170 == 7)
            {
                if (wp->value_178 == 2)
                {
                    Sound_call2(0x12B, wp->args_3c8);
                }
            }
            if (wp->value_170 == 0xC)
            {
                if (wp->value_178 == 2)
                {
                    Sound_call2(0x134, wp->args_3c8);
                }
            }
            if (wp->value_170 == 0xD)
            {
                if (wp->value_178 == 2)
                {
                    Sound_call2(0x136, wp->args_3c8);
                }
            }
        }
    }
}
