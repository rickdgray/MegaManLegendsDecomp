#include "common.h"
#include "cd.h"
#include "code_800133D8.h"
#include "code_8001786C.h"
#include "code_8002E7A8.h"
#include "code_80037534.h"
#include "code_8003AC24.h"
#include "code_800425FC.h"
#include "code_8005C258.h"
#include "code_8006430C.h"
#include "debug.h"
#include "display.h"
#include "game.h"
#include "moji.h"
#include "pad.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "sub_scrn.h"
#include "system.h"

// Pool common (see sub_scrn.h): Map_screen_init stores routine_0 through $gp.
MAP_SCREEN_WORK Map_screen_work;

// Called only from this file
void sub_screen_sort_sub(PL_WORK *pp, sint32 d0, sint32 d1);
void sub_screen_rb_parts_calc(SUB_SCREEN_WORK *subp);
void sub_screen_rb_parts_calc_sub00(SUB_SCREEN_WORK *subp, sint32 d0);
void sub_screen_rb_parts_calc_sub01(SUB_SCREEN_WORK *subp, sint32 d0);
void sub_screen_status_calc(SUB_SCREEN_WORK *subp, sint32 d0);
void func_8005F3D0(SUB_SCREEN_WORK *subp);
void func_8005F608(SUB_SCREEN_WORK *subp);
void func_8005FAE4(SUB_SCREEN_WORK *subp);
void func_8005FBB4(SUB_SCREEN_WORK *subp);
void func_8005FFBC(SUB_SCREEN_WORK *subp);
sint32 func_8005FDE4(GAME_WORK *gp);
void func_80060248(SUB_SCREEN_WORK *subp);
void func_800605DC(void);
sint32 sub_screen_cancel_check(void);
void sub_screen_shift_check(SUB_SCREEN_WORK *subp);
void map_screen_set(void);
void map_cursor_set(void);

// The sub screen, each frame: the background, then the current screen, whose result it returns.
sint32 Sub_screen_task(void)
{
    Sub_screen_back_ground_set();
    return Sub_screen_tbl[Sub_screen_work.routine_0](&Sub_screen_work);
}

// Sub screen 0, the entry: opens the top menu (message D_8008CB94[0]) and its logo, then goes to
// screen 1.
sint32 func_8005EC80(SUB_SCREEN_WORK *subp)
{
    MojiTaskKill();
    MojiTaskExec(0, D_8008CB94[0], -1);
    Game_logo_set(0, 0x20006);
    Sub_screen_basic_param_set();
    *(uint32 *)&subp->routine_0 = 1;
    return 0;
}

// Sub screen 1, the top menu: on a choice in the message task's menu (Moji_flag 0x40000000, the
// choice in the low byte), goes to screen 2 to 6 or 8; select goes to screen 7, start to 8.
sint32 func_8005ECE0(SUB_SCREEN_WORK *subp)
{
    Sub_screen_basic_param_set();
    if (Moji_flag & 0x40000000)
    {
        switch (Moji_flag & 0xFF)
        {
            case 0:
                *(uint32 *)&subp->routine_0 = 2;
                break;
            case 1:
                *(uint32 *)&subp->routine_0 = 3;
                break;
            case 2:
                *(uint32 *)&subp->routine_0 = 4;
                break;
            case 3:
                *(uint32 *)&subp->routine_0 = 5;
                break;
            case 4:
                *(uint32 *)&subp->routine_0 = 6;
                break;
            case 5:
                *(uint32 *)&subp->routine_0 = 8;
                break;
        }
    }
    else if (PAD_ON(Joy1) & PAD_SELECT)
    {
        *(uint32 *)&subp->routine_0 = 7;
    }
    else if (PAD_ON(Joy1) & PAD_START)
    {
        *(uint32 *)&subp->routine_0 = 8;
    }
    return 0;
}

// Sub screen 2: loads the message file and opens menu 0x14 in task 1; a choice (item_4, from
// Moji_flag3's low byte) of 0x40-0x43 asks a yes/no question and, on yes, uses that item.
sint32 func_8005ED9C(SUB_SCREEN_WORK *subp)
{
    sint32 slot;
    PL_WORK *pp;

    pp = &Player_work[0];
    switch (subp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCC);
            subp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                Cd_seek_file(EXIT_SUB_BIN);
                MojiTaskExec(1, Sub_mes_file, 0x14);
                subp->routine_1++;
            }
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                subp->item_4 = GET_PARTS_NO(0);
                if (subp->item_4 != 0xFF)
                {
                    Sound_call(SE_DECISION, 1, 0);
                    Moji_flag |= 0x4000;
                    subp->routine_1++;
                }
                else
                {
                    Sound_call(SE_CANCEL, 1, 0);
                }
            }
            else if (sub_screen_cancel_check() != 0)
            {
                subp->routine_1 += 5;
            }
            else
            {
                sub_screen_shift_check(subp);
            }
            break;
        case 3:
            switch (subp->item_4)
            {
                case 0x40:
                    if (func_8005D95C() == 0)
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x58);
                        subp->routine_1 += 2;
                        break;
                    }
                    MojiTaskExec(0, Sub_mes_file, 0x50);
                    subp->routine_1++;
                    break;
                case 0x41:
                    slot = pp->tbl_sel;
                    if (D_8008D7E8[D_8008DB08[slot]].energy[pp->rec[slot].idx[1]] == 0xFF)
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x3B);
                        subp->routine_1 += 2;
                        break;
                    }
                    if (Player_weapon_bullet_calc(pp, slot) == pp->rec[slot].val)
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x3A);
                        subp->routine_1 += 2;
                        break;
                    }
                    MojiTaskExec(0, Sub_mes_file, 0x52);
                    subp->routine_1++;
                    break;
                case 0x42:
                    MojiTaskExec(0, Sub_mes_file, 0x54);
                    subp->routine_1++;
                    break;
                case 0x43:
                    MojiTaskExec(0, Sub_mes_file, 0x56);
                    subp->routine_1++;
                    break;
                default:
                    if (subp->item_4 < 0x58)
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x5A);
                    }
                    else
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x5B);
                    }
                    subp->routine_1 += 2;
                    break;
            }
            break;
        case 4:
            if (Moji_flag & 0x40000000)
            {
                if (!(Moji_flag & 0xFF))
                {
                    switch (subp->item_4)
                    {
                        case 0x40:
                            MojiTaskExec(0, Sub_mes_file, 0x51);
                            func_8005D9C4();
                            subp->sce_flag_C = 0x540;
                            break;
                        case 0x41:
                            MojiTaskExec(0, Sub_mes_file, 0x53);
                            Player_weapon_bullet_set();
                            subp->sce_flag_C = 0x541;
                            break;
                        case 0x42:
                            MojiTaskExec(0, Sub_mes_file, 0x55);
                            func_8005EBB4(0x708);
                            subp->sce_flag_C = 0x542;
                            break;
                        case 0x43:
                            MojiTaskExec(0, Sub_mes_file, 0x57);
                            func_8005EBA4(0x384);
                            subp->sce_flag_C = 0x543;
                            break;
                    }
                    subp->routine_1 += 2;
                }
                else
                {
                    subp->routine_1++;
                }
            }
            break;
        case 5:
        case 6:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                if (subp->routine_1 == 6)
                {
                    Sce_flag_off(subp->sce_flag_C);
                }
                Moji_flag &= ~0x4000;
                subp->routine_1 = 2;
            }
            break;
        case 7:
            if (Cd_read_sync2() == 0)
            {
                *(uint32 *)&subp->routine_0 = 0;
            }
            break;
    }
    return 0;
}

// Sub screen 3, the item menu: loads the message file and opens menu 0x19 in task 1; a choice
// (item_4, GET_SELECT_NO(2)) goes to its handler, which runs each frame from then on.
sint32 func_8005F210(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCC);
            subp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                break;
            }
            Cd_seek_file(EXIT_SUB_BIN);
            MojiTaskExec(1, Sub_mes_file, 0x19);
            Game_logo_set(0, 0x20002);
            subp->routine_1++;
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                subp->routine_1++;
                subp->item_4 = GET_SELECT_NO(2);
            }
            else
            {
                if (sub_screen_cancel_check() != 0)
                {
                    *(uint32 *)&subp->routine_0 = 0;
                    break;
                }
                sub_screen_shift_check(subp);
                break;
            }
            // fall through
        case 3:
            switch (subp->item_4)
            {
                case 0:
                    func_8005F3D0(subp);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    func_8005F608(subp);
                    break;
                case 5:
                    subp->mes_no_5 = 0x45;
                    func_8005FAE4(subp);
                    break;
                case 6:
                case 7:
                case 8:
                    subp->mes_no_5 = 0x46;
                    func_8005FAE4(subp);
                    break;
                case 9:
                case 10:
                case 11:
                case 13:
                    subp->mes_no_5 = 0x47;
                    func_8005FAE4(subp);
                    break;
                case 12:
                    func_8005FBB4(subp);
                    break;
                case 14:
                case 15:
                case 16:
                case 17:
                    func_8005FFBC(subp);
                    break;
            }
            break;
    }
    return 0;
}

// The item menu's item 0 (key item 4): refills life, one gauge cell (0x10) per unit of
// Game_work.unk07C, after a yes/no question.
#ifdef NON_MATCHING
// Only case 1 differs: GCC keeps &Game_work.unk07C and &Player_work[0].life_max in saved registers
// across MojiTaskExec (the target rebuilds each address with lui). Literal addresses for the two
// works (((GAME_WORK *)0x800C1B10)->unk07C, ...), as the fork's draft has, match.
void func_8005F3D0(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_2)
    {
        case 0:
            if (!Sce_flag_test(PL_KEY_ITEM_04))
            {
                Sound_call(SE_CANCEL, 1, 0);
                subp->routine_2 += 2;
                return;
            }
            if (Player_work[0].life == Player_work[0].life_max)
            {
                Sound_call(SE_DECISION, 1, 0);
                MojiTaskExec(0, Sub_mes_file, 0x40);
                subp->routine_2 += 2;
                return;
            }
            if (Game_work.unk07C == 0)
            {
                Sound_call(SE_DECISION, 1, 0);
                MojiTaskExec(0, Sub_mes_file, 0x41);
                subp->routine_2 += 2;
                return;
            }
            MojiTaskExec(0, Sub_mes_file, 0x42);
            subp->routine_2++;
            return;

        case 1:
            if (Moji_flag & 0x40000000)
            {
                if (!(Moji_flag & 0xFF))
                {
                    if (Game_work.unk07C < ((Player_work[0].life_max - (Player_work[0].life & 0xF0)) >> 4))
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x44);
                        Player_work[0].life = (Player_work[0].life & 0xF0) + Game_work.unk07C * 0x10;
                        Game_work.unk07C    = 0;
                    }
                    else
                    {
                        MojiTaskExec(0, Sub_mes_file, 0x43);
                        Game_work.unk07C -= (Player_work[0].life_max - (Player_work[0].life & 0xF0)) >> 4;
                        Player_work[0].life = Player_work[0].life_max;
                    }
                }
                subp->routine_2++;
            }
            return;

        case 2:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005F3D0);
#endif

// The item menu's items 1 to 4: each toggles a player setting after a yes/no question.
void func_8005F608(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00))
            {
                switch (subp->item_4)
                {
                    case 1:
                        if (Player_work[0].unk16A)
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x33);
                        }
                        else
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x32);
                        }
                        break;

                    case 2:
                        if (Player_work[0].unk16B & 2)
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x39);
                        }
                        else
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x38);
                        }
                        break;

                    case 3:
                        if (Player_work[0].unk16B & 1)
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x35);
                        }
                        else
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x34);
                        }
                        break;

                    case 4:
                        if (Player_work[0].unk16C)
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x49);
                        }
                        else
                        {
                            MojiTaskExec(0, Sub_mes_file, 0x48);
                        }
                        break;
                }
                subp->routine_2++;
                return;
            }
            Sound_call(SE_CANCEL, 1, 0);
            subp->routine_2 += 2;
            return;

        case 1:
            if (Moji_flag & 0x40000000)
            {
                if (!(Moji_flag & 0xFF))
                {
                    switch (subp->item_4)
                    {
                        case 1:
                            if (Player_work[0].unk16A)
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x3D);
                            }
                            else
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x3C);
                            }
                            Player_work[0].unk16A ^= 1;
                            break;

                        case 2:
                            if (Player_work[0].unk16B & 2)
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x3F);
                            }
                            else
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x3E);
                            }
                            Player_work[0].unk16B ^= 2;
                            break;

                        case 3:
                            if (Player_work[0].unk16B & 1)
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x37);
                            }
                            else
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x36);
                            }
                            Player_work[0].unk16B ^= 1;
                            break;

                        case 4:
                            if (Player_work[0].unk16C)
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x4B);
                                Player_work[0].unk16C = 0;
                            }
                            else
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x4A);
                                Player_work[0].unk16C = Sce_flag_test(0x53A) + Sce_flag_test(0x53B) + Sce_flag_test(0x53C);
                            }
                            break;
                    }
                }
                subp->routine_2++;
            }
            return;

        case 2:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;
    }
}

// func_8005F608's item 2 without the question: toggles Player_work[0].unk16B bit 1 when item
// item_4 is owned. Nothing calls it.
void func_8005F9E8(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00))
            {
                if (Player_work[0].unk16B & 2)
                {
                    MojiTaskExec(0, Sub_mes_file, 0x3F);
                }
                else
                {
                    MojiTaskExec(0, Sub_mes_file, 0x3E);
                }
                Player_work[0].unk16B ^= 2;
            }
            else
            {
                Sound_call(SE_CANCEL, 1, 0);
            }
            subp->routine_2++;
            break;

        case 1:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;
    }
}

// The item menu's items 5 to 11 and 13: shows message mes_no_5 when item item_4 is owned.
void func_8005FAE4(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00))
            {
                Sound_call(SE_DECISION, 1, 0);
                MojiTaskExec(0, Sub_mes_file, subp->mes_no_5);
            }
            else
            {
                Sound_call(SE_CANCEL, 1, 0);
            }
            subp->routine_2++;
            break;

        case 1:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;
    }
}

// The item menu's item 12: when item item_4 is owned and func_8005FDE4 records a place, fades out
// and moves the game to stage unk079, area unk07A (Game_work.routine_0 5).
void func_8005FBB4(SUB_SCREEN_WORK *subp)
{
    GAME_WORK *gp;

    gp = &Game_work;
    switch (subp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00))
            {
                Sound_call(SE_DECISION, 1, 0);
                MojiTaskExec(0, Sub_mes_file, 0x4C);
                subp->routine_2++;
            }
            else
            {
                Sound_call(SE_CANCEL, 1, 0);
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;

        case 1:
            switch (func_8005FDE4(gp))
            {
                case 0:
                    MojiTaskExec(0, Sub_mes_file, 0x4D);
                    subp->routine_2 += 2;
                    break;

                case 1:
                    MojiTaskExec(0, Sub_mes_file, 0x4E);
                    subp->routine_2++;
                    break;

                case 2:
                    MojiTaskExec(0, Sub_mes_file, 0x4F);
                    subp->routine_2++;
                    break;
            }
            break;

        case 2:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;

        case 3:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                func_8003B140();
                gp->stage_no = gp->unk078.b.unk079;
                gp->area_no  = gp->unk078.b.unk07A;
                Fade_start(0x17);
                Sound_fade_start(0x10);
                subp->routine_2++;
            }
            break;

        case 4:
            func_80016D64();
            Sound_seq_stop_all();
            func_8001B314();
            D_80098958 |= 0x800;
            Sound_stage_check();
            func_8001F23C();
            func_8001F3C8();
            Game_work.routine_0 = 5;
            Game_work.routine_1 = 2;
            break;
    }
}

// For func_8005FBB4 (the item menu's item 12): whether the current stage and area can be recorded
// in Game_work.unk078 (bytes 0x79 and 0x7A: stage and area, set here). Returns 0 when recorded, 1
// in a stage that has no such place, 2 when the flag is clear or the stage's scene flag or area
// doesn't allow it.
sint32 func_8005FDE4(GAME_WORK *gp)
{
    if (!gp->unk078.b.flag)
    {
    fail:
        return 2;
    }
    switch (gp->stage_no)
    {
        case 0x03:
        case 0x1B:
            if (!Sce_flag_test(0x318) || gp->area_no >= 3)
            {
                goto fail;
            }
            if (Sce_flag_test(0x55))
            {
                gp->unk078.b.unk079 = 0x1B;
            }
            else
            {
                gp->unk078.b.unk079 = 0x03;
            }
            gp->unk078.b.unk07A = 1;
            return 0;

        case 0x05:
            if (!Sce_flag_test(0x319))
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x05;
            gp->unk078.b.unk07A = 0;
            return 0;

        case 0x06:
            if (!Sce_flag_test(0x31A))
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x06;
            gp->unk078.b.unk07A = 0;
            return 0;

        case 0x08:
            if (!Sce_flag_test(0x31B))
            {
                goto fail;
            }
            if (gp->area_no >= 3 && gp->area_no != 5)
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x08;
            gp->unk078.b.unk07A = 0;
            return 0;

        case 0x0C:
            if (!Sce_flag_test(0x31C) || gp->area_no != 0)
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x0C;
            gp->unk078.b.unk07A = 0;
            return 0;

        case 0x0F:
            if (!Sce_flag_test(0x31A))
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x06;
            gp->unk078.b.unk07A = 0;
            return 0;

        case 0x12:
            if (!Sce_flag_test(0x31F))
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x12;
            gp->unk078.b.unk07A = 0;
            return 0;

        case 0x19:
            if (!Sce_flag_test(0x31D) || gp->area_no < 2)
            {
                goto fail;
            }
            gp->unk078.b.unk079 = 0x19;
            gp->unk078.b.unk07A = 3;
            return 0;

        default:
            return 1;
    }
}

// The item menu's items 14 to 17: shows message 0x47 when any of the three items from item_4's
// on is owned.
void func_8005FFBC(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_2)
    {
        case 0:
            if (Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00) || Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00 + 1) ||
                Sce_flag_test(D_8008DAF4[subp->item_4] + PL_KEY_ITEM_00 + 2))
            {
                Sound_call(SE_DECISION, 1, 0);
                MojiTaskExec(0, Sub_mes_file, 0x47);
            }
            else
            {
                Sound_call(SE_CANCEL, 1, 0);
            }
            subp->routine_2++;
            break;

        case 1:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 2;
                subp->routine_2 = 0;
            }
            break;
    }
}

// Sub screen 4, the buster parts: loads file 0xCD and opens message 0x1D with the buster's gauges
// (func_800605DC), until the menu returns choice 2 (exit).
sint32 func_800600CC(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCD);
            subp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            Cd_seek_file(EXIT_SUB_BIN);
            MojiTaskExec(0, Sub_mes_file, 0x1D);
            Game_logo_set(2, 0x20007);
            func_800605DC();
            subp->routine_1++;
            break;
        case 2:
            if ((Moji_flag & 0x480000FF) == 0x48000002)
            {
                Cd_read_comb(EXIT_SUB_BIN);
                subp->routine_1++;
                break;
            }
            if ((Moji_flag & MOJI_TASK0_ON) == 0)
            {
                if (Moji_flag3 & MOJI3_PARTS_TASK)
                {
                    if (Moji_flag3 & 0x40000)
                    {
                        func_80060248(subp);
                    }
                }
                else if (Moji_flag3 & 0x80000)
                {
                    func_80060248(subp);
                }
            }
            func_800605DC();
            sub_screen_shift_check(subp);
            return 0;
        case 3:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            *(uint32 *)&subp->routine_0 = 0;
            break;
    }
    return 0;
}

void func_80060248(SUB_SCREEN_WORK *subp)
{
    subp->mode_6        = 3;
    subp->attack.old_0  = subp->attack.disp_0;
    subp->attack.old_1  = subp->attack.disp_1;
    subp->bullet.old_0  = subp->bullet.disp_0;
    subp->bullet.old_1  = subp->bullet.disp_1;
    subp->dist.old_0    = subp->dist.disp_0;
    subp->dist.old_1    = subp->dist.disp_1;
    subp->repeat.old_0  = subp->repeat.disp_0;
    subp->repeat.old_1  = subp->repeat.disp_1;
    subp->special.old_0 = subp->special.disp_0;
    subp->special.old_1 = subp->special.disp_1;
}

// The five stat gauges, each frame: while mode_6 counts down from 3, each shown value (disp_0,
// disp_1) steps from old_ to end_ by quarters; then it is end_. flag 0 draws the buster's four
// compared gauge pairs, otherwise the weapon's five gauges and slot mes_no_5's counter.
void sub_screen_gauge_update(SUB_SCREEN_WORK *subp, sint32 flag)
{
    if (subp->mode_6 != 0)
    {
        subp->attack.disp_0  = subp->attack.end_0 - (((subp->attack.end_0 - subp->attack.old_0) * subp->mode_6) >> 2);
        subp->attack.disp_1  = subp->attack.end_1 - (((subp->attack.end_1 - subp->attack.old_1) * subp->mode_6) >> 2);
        subp->bullet.disp_0  = subp->bullet.end_0 - (((subp->bullet.end_0 - subp->bullet.old_0) * subp->mode_6) >> 2);
        subp->bullet.disp_1  = subp->bullet.end_1 - (((subp->bullet.end_1 - subp->bullet.old_1) * subp->mode_6) >> 2);
        subp->dist.disp_0    = subp->dist.end_0 - (((subp->dist.end_0 - subp->dist.old_0) * subp->mode_6) >> 2);
        subp->dist.disp_1    = subp->dist.end_1 - (((subp->dist.end_1 - subp->dist.old_1) * subp->mode_6) >> 2);
        subp->repeat.disp_0  = subp->repeat.end_0 - (((subp->repeat.end_0 - subp->repeat.old_0) * subp->mode_6) >> 2);
        subp->repeat.disp_1  = subp->repeat.end_1 - (((subp->repeat.end_1 - subp->repeat.old_1) * subp->mode_6) >> 2);
        subp->special.disp_0 = subp->special.end_0 - (((subp->special.end_0 - subp->special.old_0) * subp->mode_6) >> 2);
        subp->special.disp_1 = subp->special.end_1 - (((subp->special.end_1 - subp->special.old_1) * subp->mode_6) >> 2);
        subp->mode_6--;
    }
    else
    {
        subp->attack.disp_0  = subp->attack.end_0;
        subp->attack.disp_1  = subp->attack.end_1;
        subp->bullet.disp_0  = subp->bullet.end_0;
        subp->bullet.disp_1  = subp->bullet.end_1;
        subp->dist.disp_0    = subp->dist.end_0;
        subp->dist.disp_1    = subp->dist.end_1;
        subp->repeat.disp_0  = subp->repeat.end_0;
        subp->repeat.disp_1  = subp->repeat.end_1;
        subp->special.disp_0 = subp->special.end_0;
        subp->special.disp_1 = subp->special.end_1;
    }
    if (flag == 0)
    {
        Sub_screen_gauge_set(0xCB, 0x28, subp->attack.disp_0, 0);
        Sub_screen_gauge_set(0xCB, 0x28, subp->attack.disp_1, 1);
        Sub_screen_gauge_set(0xCB, 0x32, subp->bullet.disp_0, 0);
        Sub_screen_gauge_set(0xCB, 0x32, subp->bullet.disp_1, 1);
        Sub_screen_gauge_set(0xCB, 0x3C, subp->dist.disp_0, 0);
        Sub_screen_gauge_set(0xCB, 0x3C, subp->dist.disp_1, 1);
        Sub_screen_gauge_set(0xCB, 0x46, subp->repeat.disp_0, 0);
        Sub_screen_gauge_set(0xCB, 0x46, subp->repeat.disp_1, 1);
        return;
    }
    Sub_screen_gauge_set2(0xA4, 0x9E, subp->attack.disp_0, subp->attack.infi_0);
    Sub_screen_gauge_set2(0xA4, 0xA8, subp->bullet.disp_0, subp->bullet.infi_0);
    Sub_screen_gauge_set2(0xA4, 0xB2, subp->dist.disp_0, subp->dist.infi_0);
    Sub_screen_gauge_set2(0xA4, 0xBC, subp->repeat.disp_0, subp->repeat.infi_0);
    Sub_screen_gauge_set2(0xA4, 0xC6, subp->special.disp_0, subp->special.infi_0);
    if (subp->mes_no_5 != 0)
    {
        Sub_screen_status_param_set(subp->mes_no_5);
    }
}

void func_800605DC(void)
{
    sub_screen_rb_parts_calc(&Sub_screen_work);
    sub_screen_gauge_update(&Sub_screen_work, 0);
}

// Sub screen 5, the weapon screen: a menu (message 0x2F in task 1) to equip or remove the special
// weapon (tbl_sel), or browse the weapons (mes_no_5: slot GET_SELECT_NO(1) + 1, 0 for none) with
// their gauges.
sint32 func_80060618(SUB_SCREEN_WORK *subp)
{
    PL_WORK *pp;
    uint16 joy_trg;
    sint32 slot;
    uint32 n;

    pp      = &Player_work[0];
    joy_trg = PAD_ON(Joy1);
    switch (subp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCD);
            subp->mes_no_5 = 0;
            subp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                break;
            }
            Cd_seek_file(EXIT_SUB_BIN);
            if (pp->weapon_right_no != 0)
            {
                MojiTaskExec(0, Sub_mes_file, 0x5C);
            }
            else
            {
                MojiTaskExec(0, Sub_mes_file, 0x5D);
            }
            if (!(Moji_flag & 0x04000000))
            {
                MojiTaskExec(1, Sub_mes_file, 0x2F);
                if (pp->tbl_sel == 0)
                {
                    Game_logo_set(0, 0x2001C);
                }
                Game_logo_set(1, 0x20009);
                Game_logo_set(2, 0x20017);
                Game_logo_set(3, 0x20008);
                sub_screen_status_calc(subp, 0);
            }
            sub_screen_gauge_update(subp, 1);
            subp->routine_1++;
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                // The extra loop level is in the target: it changes register allocation.
                do
                {
                    switch (Moji_flag & 0xFF)
                    {
                        case 0:
                            Sound_call(SE_DECISION, 1, 0);
                            subp->routine_1++;
                            break;
                        case 1:
                            if (pp->tbl_sel == 0)
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x61);
                            }
                            else if (pp->unk44E <= 0)
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x60);
                            }
                            else if (pp->unk44F == 0)
                            {
                                func_8005C218(pp->tbl_sel + 0x80);
                                MojiTaskExec(0, Sub_mes_file, 0x5E);
                                pp->unk44F          = 1;
                                pp->weapon_right_no = pp->tbl_sel;
                            }
                            else
                            {
                                MojiTaskExec(0, Sub_mes_file, 0x5F);
                                pp->unk44F          = 0;
                                pp->weapon_right_no = 0;
                            }
                            subp->routine_1 += 3;
                            break;
                        case 2:
                            Sound_call(SE_CANCEL, 1, 0);
                            MojiTaskKill();
                            Game_logo_kill(-1);
                            Cd_read_comb(EXIT_SUB_BIN);
                            subp->routine_1 += 4;
                            break;
                    }
                } while (0);
            }
            else
            {
                sub_screen_shift_check(subp);
            }
            sub_screen_gauge_update(subp, 1);
            break;
        case 3:
            n            = GET_SELECT_NO(1);
            subp->item_4 = n;
            if ((subp->mes_no_5 = n) != 0)
            {
                subp->mes_no_5 = n + 1;
            }
            slot = subp->mes_no_5;
            if (subp->item_4 < 0xD && Sce_flag_test(slot + 0x4C0) != 0)
            {
                Game_logo_set(1, (subp->item_4 + 9) | 0x20000);
                if (pp->tbl_sel == slot)
                {
                    Game_logo_set(0, 0x2001C);
                }
                else
                {
                    Game_logo_kill(0);
                }
                sub_screen_status_calc(subp, slot);
            }
            else
            {
                subp->mes_no_5 = 0;
                Game_logo_set(1, 0x20016);
                Game_logo_kill(0);
                sub_screen_status_calc(subp, -1);
            }
            if (Moji_flag3 & 0x40000)
            {
                func_80060248(subp);
            }
            if (Moji_flag & 0x40000000)
            {
                if (subp->item_4 == 0xD)
                {
                    Sound_call(SE_DECISION, 1, 0);
                    subp->routine_1 += 2;
                }
                else if (Sce_flag_test(slot + 0x4C0) != 0)
                {
                    Sound_call(SE_DECISION, 1, 0);
                    MojiTaskExec(0, Sub_mes_file, subp->item_4 + 0xE4);
                    subp->routine_1++;
                }
                else
                {
                    Sound_call(SE_CANCEL, 1, 0);
                }
            }
            else if (joy_trg & (PAD_TRIANGLE | PAD_START))
            {
                Sound_call(SE_CANCEL, 1, 0);
                subp->routine_1 += 2;
            }
            else
            {
                sub_screen_shift_check(subp);
            }
            sub_screen_gauge_update(subp, 1);
            break;
        case 4:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 3;
                subp->routine_2 = 0;
            }
            sub_screen_gauge_update(subp, 1);
            break;
        case 5:
            if (!(Moji_flag & MOJI_TASK0_ON))
            {
                subp->routine_1 = 1;
                subp->routine_2 = 0;
            }
            sub_screen_gauge_update(subp, 1);
            break;
        case 6:
            if (Cd_read_sync2() == 0)
            {
                *(uint32 *)&subp->routine_0 = 0;
            }
            break;
    }
    return 0;
}

// Sub screen 6: loads file 0xCC and shows message D_8008CB64[0]; when it ends (or on start),
// applies key row Game_work.unk054 to the player (func_800425FC) and loads the exit file.
sint32 func_80060B00(SUB_SCREEN_WORK *subp)
{
    switch (subp->routine_1)
    {
        case 0:
            MojiTaskKill();
            Game_logo_kill(-1);
            Cd_read_comb(0xCC);
            subp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            Cd_seek_file(EXIT_SUB_BIN);
            MojiTaskExec(0, D_8008CB64[0], -1);
            subp->routine_1++;
            break;
        case 2:
            if ((Moji_flag & 0x40000000) || (PAD_ON(Joy1) & PAD_START))
            {
                if (PAD_ON(Joy1) & PAD_START)
                {
                    Sound_call(SE_CANCEL, 1, 0);
                }
                MojiTaskKill();
                func_800425FC(&Player_work[0], (sint8)Game_work.unk054);
                Cd_read_comb(EXIT_SUB_BIN);
                subp->routine_1++;
            }
            else
            {
                sub_screen_shift_check(subp);
                return 0;
            }
            break;
        case 3:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            *(uint32 *)&subp->routine_0 = 0;
            break;
    }
    return 0;
}

// Sub screen 7 (select on the top menu): two yes/no questions (messages D_8008CE78[0] and
// D_8008CE84[0]); "no" to either returns to the top menu, "yes" to both closes the sub screen
// and its work, stops the sound and the CD, and restarts code_800133D8's module at routine 1.
sint32 func_80060C70(SUB_SCREEN_WORK *subp)
{
    Sub_screen_basic_param_set();
    switch (subp->routine_1)
    {
        case 0:
            MojiTaskExec(0, D_8008CE78[0], -1);
            subp->routine_1++;
            break;
        case 1:
            if (Moji_flag & 0x40000000)
            {
                if ((Moji_flag & 0xFF) != 0)
                {
                    *(uint32 *)&subp->routine_0 = 0;
                }
                else
                {
                    MojiTaskExec(0, D_8008CE84[0], -1);
                    subp->routine_1++;
                }
            }
            break;
        case 2:
            if (Moji_flag & 0x40000000)
            {
                if ((Moji_flag & 0xFF) != 0)
                {
                    *(uint32 *)&subp->routine_0 = 0;
                }
                else
                {
                    MojiTaskKill();
                    func_80063BA8();
                    func_80063EF0();
                    func_800665E8();
                    func_8001B314();
                    Sound_seq_stop_all();
                    Cd_subcmd(0, CD_SUBCMD_XA_STOP, 0);
                    Sce_flag_off(0x1FE);
                    // routine_0 = 1, routine_1 = 0 in one store.
                    *(uint16 *)&D_80098AA8.routine_0 = 1;
                    func_80012F78(func_80013420);
                }
            }
            break;
    }
    return 0;
}

// Sub screen 8, the exit: if the equipped buster parts or the weapon changed since the entry
// (func_8005EBE4's copies), resets the player's shots, closing them all if the weapon changed.
sint32 func_80060DB8(SUB_SCREEN_WORK *subp)
{
    PL_WORK *pp;

    pp = &Player_work[0];
    if (subp->weapon_no != pp->weapon_right_no || *(uint16 *)&subp->rb_parts_no[0] != *(uint16 *)&pp->rb_parts_equip_data[0] ||
        subp->rb_parts_no[2] != pp->rb_parts_equip_data[2])
    {
        Pl00_shot_enable_off(pp);
        Pl00_shot_enable_on(pp);
        if (subp->weapon_no != pp->weapon_right_no)
        {
            Obj_work_flag_change(WORK_PL_SHL, WORK_KILL);
        }
        pp->unk110 = 0;
    }
    return 1;
}

// Triangle or start leaves the sub screen: returns 1 after loading the exit code.
sint32 sub_screen_cancel_check(void)
{
    uint32 joy_trg;

    joy_trg = PAD_ON(Joy1);
    if (joy_trg & (PAD_TRIANGLE | PAD_START))
    {
        Sound_call(SE_CANCEL, 1, 0);
        MojiTaskKill();
        Game_logo_kill(-1);
        Cd_read_comb(EXIT_SUB_BIN);
        return 1;
    }
    else
    {
        return 0;
    }
}

// L1 and R1 step through screens 2 to 6, wrapping around.
void sub_screen_shift_check(SUB_SCREEN_WORK *subp)
{
    uint32 joy_trg;

    joy_trg = PAD_ON(Joy1);
    if (joy_trg & (PAD_L1 | PAD_R1))
    {
        Sound_call(SE_DECISION, 1, 0);
        MojiTaskKill();
        Game_logo_kill(-1);
        if (joy_trg & PAD_L1)
        {
            if (--subp->routine_0 < 2)
            {
                subp->routine_0 = 6;
            }
        }
        else
        {
            if (++subp->routine_0 > 6)
            {
                subp->routine_0 = 2;
            }
        }
        subp->routine_1 = 0;
        // One store clears routine_2 and routine_3.
        *(uint16 *)&subp->routine_2 = 0;
    }
}

// Sorts the owned buster parts by attack level, highest first, empty entries last.
void Sub_screen_sort_attack(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].attack_level < Rock_buster_parts_tbl[sort_dist - 1].attack_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

// Sub_screen_sort_attack by energy level.
void Sub_screen_sort_energy(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].bullet_level < Rock_buster_parts_tbl[sort_dist - 1].bullet_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

// Sub_screen_sort_attack by range level.
void Sub_screen_sort_range(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].dist_level < Rock_buster_parts_tbl[sort_dist - 1].dist_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

// Sub_screen_sort_attack by rapid level.
void Sub_screen_sort_rapid(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].repeat_level < Rock_buster_parts_tbl[sort_dist - 1].repeat_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

void sub_screen_sort_sub(PL_WORK *pp, sint32 d0, sint32 d1)
{
    uint8 sort_buff;

    sort_buff                  = pp->rb_parts_sort_data[d0];
    pp->rb_parts_sort_data[d0] = pp->rb_parts_sort_data[d1];
    pp->rb_parts_sort_data[d1] = sort_buff;
}

// The buster's levels (Player_work[0].rec[1]): the sum of its equipped parts' levels, up to
// RB_LEVEL_MAX each.
void Sub_screen_rb_parts_set(void)
{
    sint32 d0;
    sint32 d1;
    sint32 d2;
    PL_WORK *pp;

    pp = &Player_work[0];

    if (Sce_flag_test(PL_KEY_ITEM_06))
    {
        d0 = 3;
    }
    else
    {
        d0 = 2;
    }

    pp->rec[1].idx[0] = 0;
    pp->rec[1].idx[1] = 0;
    pp->rec[1].idx[2] = 0;
    pp->rec[1].idx[3] = 0;

    for (d1 = 0; d1 < d0; d1++)
    {
        if (!(d2 = pp->rb_parts_equip_data[d1]))
        {
            continue;
        }
        pp->rec[1].idx[0] += Rock_buster_parts_tbl[d2 - 1].attack_level;
        pp->rec[1].idx[1] += Rock_buster_parts_tbl[d2 - 1].bullet_level;
        pp->rec[1].idx[2] += Rock_buster_parts_tbl[d2 - 1].dist_level;
        pp->rec[1].idx[3] += Rock_buster_parts_tbl[d2 - 1].repeat_level;
    }
    if (pp->rec[1].idx[0] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[0] = RB_LEVEL_MAX;
    }
    if (pp->rec[1].idx[1] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[1] = RB_LEVEL_MAX;
    }
    if (pp->rec[1].idx[2] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[2] = RB_LEVEL_MAX;
    }
    if (pp->rec[1].idx[3] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[3] = RB_LEVEL_MAX;
    }
}

// The buster gauges' end values: _0 for the equipped parts, _1 for them with the part under the
// cursor of message task 1 (GET_PARTS_NO(1)) in slot GET_SELECT_NO(1), or without that slot's part
// while the parts list (MOJI3_PARTS_TASK) is open; both the same while task 0 runs.
void sub_screen_rb_parts_calc(SUB_SCREEN_WORK *subp)
{
    sint32 d0;
    sint32 d1;
    sint32 d2;
    PL_WORK *pp;

    pp = &Player_work[0];

    if (Sce_flag_test(PL_KEY_ITEM_06))
    {
        d0 = 3;
    }
    else
    {
        d0 = 2;
    }

    subp->attack.end_0 = subp->attack.end_1 = 0;
    subp->bullet.end_0 = subp->bullet.end_1 = 0;
    subp->dist.end_0 = subp->dist.end_1 = 0;
    subp->repeat.end_0 = subp->repeat.end_1 = 0;

    if (Moji_flag & MOJI_TASK0_ON)
    {
        for (d1 = 0; d1 < d0; d1++)
        {
            if (!(d2 = pp->rb_parts_equip_data[d1]))
            {
                continue;
            }
            sub_screen_rb_parts_calc_sub00(subp, d2 - 1);
            sub_screen_rb_parts_calc_sub01(subp, d2 - 1);
        }
    }
    else
    {
        if (Moji_flag3 & MOJI3_PARTS_TASK)
        {
            for (d1 = 0; d1 < d0; d1++)
            {
                if ((d2 = pp->rb_parts_equip_data[d1]))
                {
                    sub_screen_rb_parts_calc_sub00(subp, d2 - 1);
                }

                if (d1 == GET_SELECT_NO(1))
                {
                    continue;
                }
                if (d2)
                {
                    sub_screen_rb_parts_calc_sub01(subp, d2 - 1);
                }
            }
        }
        else
        {
            for (d1 = 0; d1 < d0; d1++)
            {
                if ((d2 = pp->rb_parts_equip_data[d1]))
                {
                    sub_screen_rb_parts_calc_sub00(subp, d2 - 1);
                }

                if (d1 == GET_SELECT_NO(1))
                {
                    d2 = GET_PARTS_NO(1);
                }
                if (d2)
                {
                    sub_screen_rb_parts_calc_sub01(subp, d2 - 1);
                }
            }
        }
    }
}

void sub_screen_rb_parts_calc_sub00(SUB_SCREEN_WORK *subp, sint32 d0)
{
    subp->attack.end_0 += Rock_buster_parts_tbl[d0].attack_level * 10;
    subp->bullet.end_0 += Rock_buster_parts_tbl[d0].bullet_level * 10;
    subp->dist.end_0 += Rock_buster_parts_tbl[d0].dist_level * 10;
    subp->repeat.end_0 += Rock_buster_parts_tbl[d0].repeat_level * 10;

    if (subp->attack.end_0 > RB_LEVEL_MAX * 10)
    {
        subp->attack.end_0 = RB_LEVEL_MAX * 10;
    }
    if (subp->bullet.end_0 > RB_LEVEL_MAX * 10)
    {
        subp->bullet.end_0 = RB_LEVEL_MAX * 10;
    }
    if (subp->dist.end_0 > RB_LEVEL_MAX * 10)
    {
        subp->dist.end_0 = RB_LEVEL_MAX * 10;
    }
    if (subp->repeat.end_0 > RB_REPEAT_LEVEL_MAX * 10)
    {
        subp->repeat.end_0 = RB_REPEAT_LEVEL_MAX * 10;
    }
}

// Same as sub_screen_rb_parts_calc_sub00, on the _1 values.
void sub_screen_rb_parts_calc_sub01(SUB_SCREEN_WORK *subp, sint32 d0)
{
    subp->attack.end_1 += Rock_buster_parts_tbl[d0].attack_level * 10;
    subp->bullet.end_1 += Rock_buster_parts_tbl[d0].bullet_level * 10;
    subp->dist.end_1 += Rock_buster_parts_tbl[d0].dist_level * 10;
    subp->repeat.end_1 += Rock_buster_parts_tbl[d0].repeat_level * 10;

    if (subp->attack.end_1 > RB_LEVEL_MAX * 10)
    {
        subp->attack.end_1 = RB_LEVEL_MAX * 10;
    }
    if (subp->bullet.end_1 > RB_LEVEL_MAX * 10)
    {
        subp->bullet.end_1 = RB_LEVEL_MAX * 10;
    }
    if (subp->dist.end_1 > RB_LEVEL_MAX * 10)
    {
        subp->dist.end_1 = RB_LEVEL_MAX * 10;
    }
    if (subp->repeat.end_1 > RB_REPEAT_LEVEL_MAX * 10)
    {
        subp->repeat.end_1 = RB_REPEAT_LEVEL_MAX * 10;
    }
}

// The gauges' end values (_0) for weapon slot d0 (Player_work[0].rec[d0]), from its levels;
// a negative d0 clears them. A table value of 0xFF is drawn as a full gauge marked "infinite".
void sub_screen_status_calc(SUB_SCREEN_WORK *subp, sint32 d0)
{
    PL_WORK *pp;

    pp = &Player_work[0];

    if (d0 < 0)
    {
        subp->attack.end_0 = subp->attack.infi_0 = 0;
        subp->bullet.end_0 = subp->bullet.infi_0 = 0;
        subp->dist.end_0 = subp->dist.infi_0 = 0;
        subp->repeat.end_0 = subp->repeat.infi_0 = 0;
        subp->special.end_0 = subp->special.infi_0 = 0;
    }
    else
    {
        subp->attack.end_0  = D_8008D7E8[D_8008DB08[d0]].attack[pp->rec[d0].idx[0]];
        subp->bullet.end_0  = D_8008D7E8[D_8008DB08[d0]].energy[pp->rec[d0].idx[1]];
        subp->dist.end_0    = D_8008D7E8[D_8008DB08[d0]].range[pp->rec[d0].idx[2]];
        subp->repeat.end_0  = D_8008D7E8[D_8008DB08[d0]].rapid[pp->rec[d0].idx[3]];
        subp->special.end_0 = D_8008D7E8[D_8008DB08[d0]].special[pp->rec[d0].sp_perform];

        if (subp->attack.end_0 == 0xFF)
        {
            subp->attack.end_0  = 88;
            subp->attack.infi_0 = 1;
        }
        else
        {
            subp->attack.infi_0 = 0;
        }
        if (subp->bullet.end_0 == 0xFF)
        {
            subp->bullet.end_0  = 88;
            subp->bullet.infi_0 = 1;
        }
        else
        {
            subp->bullet.infi_0 = 0;
        }
        if (subp->dist.end_0 == 0xFF)
        {
            subp->dist.end_0  = 88;
            subp->dist.infi_0 = 1;
        }
        else
        {
            subp->dist.infi_0 = 0;
        }
        if (subp->repeat.end_0 == 0xFF)
        {
            subp->repeat.end_0  = 88;
            subp->repeat.infi_0 = 1;
        }
        else
        {
            subp->repeat.infi_0 = 0;
        }
        if (subp->special.end_0 == 0xFF)
        {
            subp->special.end_0  = 88;
            subp->special.infi_0 = 1;
        }
        else
        {
            subp->special.infi_0 = 0;
        }
    }
}

// A buster stat gauge power wide at (x0, y0) and its end cap, into OT 2: flag 0 is the equipped
// value's gauge, 1 the compared one's, drawn 2 lower in its own colour row. A flag 0 gauge at its
// maximum (70, or 40 for the rapid gauge at y0 0x46) gets the "MAX" label.
void Sub_screen_gauge_set(sint32 x0, sint32 y0, sint32 power, sint32 flag)
{
    POLY_FT4 *ft4_buff_ptr1;
    POLY_FT4 *ft4_buff_ptr2;

    ft4_buff_ptr2 = Map_prim_ptr;

    SET_TAG_NEXT(ft4_buff_ptr2, 9);
    SET_CODE_RGB(ft4_buff_ptr2, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr2->x0 = ft4_buff_ptr2->x2 = x0;
    ft4_buff_ptr2->x1 = ft4_buff_ptr2->x3 = x0 + power + 6;
    ft4_buff_ptr2->y0 = ft4_buff_ptr2->y1 = y0 + flag * 2;
    ft4_buff_ptr2->y2 = ft4_buff_ptr2->y3 = y0 + flag * 2 + 5;

    ft4_buff_ptr2->tpage = getTPage(0, 0, 768, 0);
    ft4_buff_ptr2->clut  = getClut(48, 250);

    SET_UV_HALF(ft4_buff_ptr2->u0, 0x60, 0x90 + flag * 8);
    SET_UV_HALF(ft4_buff_ptr2->u1, 0x61, 0x90 + flag * 8);
    SET_UV_HALF(ft4_buff_ptr2->u2, 0x60, 0x95 + flag * 8);
    SET_UV_HALF(ft4_buff_ptr2->u3, 0x61, 0x95 + flag * 8);

    ft4_buff_ptr1 = ft4_buff_ptr2;
    ft4_buff_ptr2++;

    SET_TAG_NEXT(ft4_buff_ptr2, 9);
    SET_CODE_RGB(ft4_buff_ptr2, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr2->x0 = ft4_buff_ptr2->x2 = x0 + power + 6;
    ft4_buff_ptr2->x1 = ft4_buff_ptr2->x3 = x0 + power + 10;
    ft4_buff_ptr2->y0 = ft4_buff_ptr2->y1 = y0 + flag * 2;
    ft4_buff_ptr2->y2 = ft4_buff_ptr2->y3 = y0 + flag * 2 + 5;

    ft4_buff_ptr2->tpage = getTPage(0, 0, 768, 0);
    ft4_buff_ptr2->clut  = getClut(48, 250);

    SET_UV_HALF(ft4_buff_ptr2->u0, 0x6F, 0x90 + flag * 8);
    SET_UV_HALF(ft4_buff_ptr2->u1, 0x73, 0x90 + flag * 8);
    SET_UV_HALF(ft4_buff_ptr2->u2, 0x6F, 0x95 + flag * 8);
    SET_UV_HALF(ft4_buff_ptr2->u3, 0x73, 0x95 + flag * 8);

    ft4_buff_ptr2++;

    if (!flag && ((y0 != 0x46 && power == RB_LEVEL_MAX * 10) || (y0 == 0x46 && power == RB_REPEAT_LEVEL_MAX * 10)))
    {
        // A SPRT in a POLY_FT4-sized slot: linked and stepped as a POLY_FT4.
        SET_TAG_NEXT(ft4_buff_ptr2, 4);
        SET_CODE_RGB(ft4_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
        ((SPRT *)ft4_buff_ptr2)->x0 = x0 + 10 + (power == RB_LEVEL_MAX * 10) * 14;
        ((SPRT *)ft4_buff_ptr2)->y0 = y0;
        SET_UV0_CLUT((SPRT *)ft4_buff_ptr2, 0x28, 0xF0, getClut(32, 250));
        SET_WH_WORD((SPRT *)ft4_buff_ptr2, 0x18, 6);

        ft4_buff_ptr2++;
    }
    Map_prim_ptr = ft4_buff_ptr2;
    addPrims(&Disp_env_ptr->ot[2], ft4_buff_ptr1, ft4_buff_ptr2 - 1);
}

// A stat gauge power wide at (x0, y0), and its end cap, into OT 2; an "infinite" gauge (infi, at
// full length 88) gets its label over it.
void Sub_screen_gauge_set2(sint32 x0, sint32 y0, sint32 power, sint32 infi)
{
    POLY_FT4 *ft4_buff_ptr1;
    POLY_FT4 *ft4_buff_ptr2;

    ft4_buff_ptr2 = Map_prim_ptr;

    SET_TAG_NEXT(ft4_buff_ptr2, 9);
    SET_CODE_RGB(ft4_buff_ptr2, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr2->x0 = ft4_buff_ptr2->x2 = x0;
    ft4_buff_ptr2->x1 = ft4_buff_ptr2->x3 = x0 + power;
    ft4_buff_ptr2->y0 = ft4_buff_ptr2->y1 = y0;
    ft4_buff_ptr2->y2 = ft4_buff_ptr2->y3 = y0 + 8;

    ft4_buff_ptr2->tpage = getTPage(0, 0, 768, 0);
    ft4_buff_ptr2->clut  = getClut(48, 250);

    SET_UV_HALF(ft4_buff_ptr2->u0, 0x48, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u1, 0x49, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u2, 0x48, 0x98);
    SET_UV_HALF(ft4_buff_ptr2->u3, 0x49, 0x98);

    ft4_buff_ptr1 = ft4_buff_ptr2;
    ft4_buff_ptr2++;

    SET_TAG_NEXT(ft4_buff_ptr2, 9);
    SET_CODE_RGB(ft4_buff_ptr2, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr2->x0 = ft4_buff_ptr2->x2 = x0 + power;
    ft4_buff_ptr2->x1 = ft4_buff_ptr2->x3 = x0 + power + 4;
    ft4_buff_ptr2->y0 = ft4_buff_ptr2->y1 = y0;
    ft4_buff_ptr2->y2 = ft4_buff_ptr2->y3 = y0 + 8;

    ft4_buff_ptr2->tpage = getTPage(0, 0, 768, 0);
    ft4_buff_ptr2->clut  = getClut(48, 250);

    SET_UV_HALF(ft4_buff_ptr2->u0, 0x4C, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u1, 0x50, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u2, 0x4C, 0x98);
    SET_UV_HALF(ft4_buff_ptr2->u3, 0x50, 0x98);

    ft4_buff_ptr2++;

    if (infi && power == 88)
    {
        // A SPRT in a POLY_FT4-sized slot: linked and stepped as a POLY_FT4.
        SET_TAG_NEXT(ft4_buff_ptr2, 4);
        SET_CODE_RGB(ft4_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
        ((SPRT *)ft4_buff_ptr2)->x0 = x0 + 0x18;
        ((SPRT *)ft4_buff_ptr2)->y0 = y0;
        SET_UV0_CLUT((SPRT *)ft4_buff_ptr2, 0x28, 0xF8, getClut(32, 250));
        SET_WH_WORD((SPRT *)ft4_buff_ptr2, 0x28, 8);

        ft4_buff_ptr2++;
    }
    Map_prim_ptr = ft4_buff_ptr2;
    addPrims(&Disp_env_ptr->ot[2], ft4_buff_ptr1, ft4_buff_ptr2 - 1);
}

// The basic values, into OT 2: the life gauge (one cell per 0x10 of life_max: full, half or empty),
// the money, and the play time's hours and minutes.
void Sub_screen_basic_param_set(void)
{
    sint32 d0;
    sint32 d1;
    sint32 d2;
    sint32 x0;
    SPRT *sprt_buff_ptr1;
    SPRT *sprt_buff_ptr2;

    sprt_buff_ptr2 = (SPRT *)Map_prim_ptr;

    d0 = (Player_work[0].life_max - 1) >> 4;
    d1 = Player_work[0].life;

    SET_TAG_LEN(sprt_buff_ptr2, 2);
    ((DR_MODE *)sprt_buff_ptr2)->code[0] = DRAW_MODE_CODE(getTPage(0, 0, 832, 0));
    ((DR_MODE *)sprt_buff_ptr2)->code[1] = 0;
    SET_TAG_NEXT(sprt_buff_ptr2, 2);
    sprt_buff_ptr1 = sprt_buff_ptr2;
    sprt_buff_ptr2++;

    for (x0 = 0; x0 <= d0; x0++)
    {
        SET_TAG_NEXT(sprt_buff_ptr2, 4);
        SET_CODE_RGB(sprt_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
        SET_XY0_WORD(sprt_buff_ptr2, (x0 * 5 + 0x31) | (0x24 << 16));
        SET_WH_WORD(sprt_buff_ptr2, 8, 8);

        if (d1 > x0 * 0x10)
        {
            if (d1 - 0x10 > x0 * 0x10 || !(d1 % 0x10))
            {
                d2 = 0x70 | (0xB8 << 8) | (getClut(848, 249) << 16);
            }
            else
            {
                d2 = 0x78 | (0xB8 << 8) | (getClut(848, 249) << 16);
            }
        }
        else
        {
            d2 = 0x80 | (0xB8 << 8) | (getClut(848, 249) << 16);
        }
        *(u_long *)&sprt_buff_ptr2->u0 = d2;
        sprt_buff_ptr2++;
    }

    sprt_buff_ptr2 =
        Sub_screen_basic_param_set_sub(sprt_buff_ptr2, 0xA4 | (0x24 << 16), Game_work.money, 6 | NUM_NO_LEAD_ZERO | NUM_NO_ZERO);
    sprt_buff_ptr2 = Sub_screen_basic_param_set_sub(sprt_buff_ptr2, 0x106 | (0x24 << 16), Game_work.timer_0c / (30 * 60 * 60), 2);
    sprt_buff_ptr2 = Sub_screen_basic_param_set_sub(sprt_buff_ptr2, 0x11A | (0x24 << 16), Game_work.timer_0c / (30 * 60) % 60, 2);

    Map_prim_ptr = (POLY_FT4 *)sprt_buff_ptr2;
    addPrims(&Disp_env_ptr->ot[2], sprt_buff_ptr1, sprt_buff_ptr2 - 1);
}

// Draws num as (flag & NUM_DIGITS_MASK) digits from pos (x | y << 16) in the large digit font, one
// SPRT per digit drawn, linked after one another; returns the next free SPRT.
SPRT *Sub_screen_basic_param_set_sub(SPRT *ptr, uint32 pos, sint32 num, sint32 flag)
{
    sint32 d0;
    sint32 d1;

    for (d0 = (flag & NUM_DIGITS_MASK) - 1; d0 >= 0; d0--)
    {
        d1 = num % 10;
        if (((d0 == (flag & NUM_DIGITS_MASK) - 1) && !(flag & NUM_NO_ZERO)) || num || !(flag & NUM_NO_LEAD_ZERO))
        {
            SET_TAG_NEXT(ptr, 4);
            SET_CODE_RGB(ptr, 0x64, 0x80, 0x80, 0x80);
            SET_XY0_WORD(ptr, d0 * 7 + pos);
            SET_WH_WORD(ptr, 8, 8);
            SET_UV0_CLUT(ptr, d1 * 8 + 0x60, 0xB0, getClut(848, 249));
            ptr++;
        }
        num /= 10;
    }
    return ptr;
}

// Weapon slot d0's "now / max" counter (Player_work[0].rec[d0].val and Player_weapon_bullet_calc), into OT 2;
// none when max is 0x7FFF (unlimited).
void Sub_screen_status_param_set(sint32 d0)
{
    sint32 d1;
    sint32 d2;
    PL_WORK *pp;
    SPRT *sprt_buff_ptr1;
    SPRT *sprt_buff_ptr2;

    pp             = &Player_work[0];
    sprt_buff_ptr1 = sprt_buff_ptr2 = (SPRT *)Map_prim_ptr;

    d1 = pp->rec[d0].val;
    if ((d2 = Player_weapon_bullet_calc(pp, d0)) < 0x7FFF)
    {
        SET_TAG_LEN(sprt_buff_ptr2, 2);
        ((DR_MODE *)sprt_buff_ptr2)->code[0] = DRAW_MODE_CODE(getTPage(0, 0, 768, 0));
        SET_TAG_NEXT(sprt_buff_ptr2, 2);
        ((DR_MODE *)sprt_buff_ptr2)->code[1] = 0;
        sprt_buff_ptr2++;

        // The slash between the two numbers.
        SET_TAG_NEXT(sprt_buff_ptr2, 4);
        SET_CODE_RGB(sprt_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
        SET_XY0_WORD(sprt_buff_ptr2, 0xD1 | (0x8C << 16));
        SET_WH_WORD(sprt_buff_ptr2, 6, 8);
        SET_UV0_CLUT(sprt_buff_ptr2, 0x40, 0xF0, getClut(32, 250));
        sprt_buff_ptr2++;

        sprt_buff_ptr2 = Sub_screen_status_param_set_sub(sprt_buff_ptr2, 0xB4 | (0x8C << 16), d1, 4);
        sprt_buff_ptr2 = Sub_screen_status_param_set_sub(sprt_buff_ptr2, 0xD8 | (0x8C << 16), d2, 4);

        addPrims(&Disp_env_ptr->ot[2], sprt_buff_ptr1, sprt_buff_ptr2 - 1);
        Map_prim_ptr = (POLY_FT4 *)sprt_buff_ptr2;
    }
}

// Sub_screen_basic_param_set_sub in the small digit font (6x8).
SPRT *Sub_screen_status_param_set_sub(SPRT *ptr, uint32 pos, sint32 num, sint32 flag)
{
    sint32 d0;
    sint32 d1;

    for (d0 = (flag & NUM_DIGITS_MASK) - 1; d0 >= 0; d0--)
    {
        d1 = num % 10;
        if (((d0 == (flag & NUM_DIGITS_MASK) - 1) && !(flag & NUM_NO_ZERO)) || num || !(flag & NUM_NO_LEAD_ZERO))
        {
            SET_TAG_NEXT(ptr, 4);
            SET_CODE_RGB(ptr, 0x64, 0x80, 0x80, 0x80);
            SET_XY0_WORD(ptr, d0 * 7 + pos);
            SET_WH_WORD(ptr, 6, 8);
            SET_UV0_CLUT(ptr, d1 * 8, 0xC0, getClut(32, 250));
            ptr++;
        }
        num /= 10;
    }
    return ptr;
}

// The sub screen's background: a 7x5 grid of 64x64 tiles scrolling diagonally with System_timer,
// after a draw mode for its texture page, into OT 7.
void Sub_screen_back_ground_set(void)
{
    sint32 x0;
    sint32 y0;
    SPRT *sprt_buff_ptr1;
    SPRT *sprt_buff_ptr2;

    sprt_buff_ptr1 = sprt_buff_ptr2 = (SPRT *)Map_prim_ptr;

    SET_TAG_LEN(sprt_buff_ptr2, 2);
    ((DR_MODE *)sprt_buff_ptr2)->code[0] = DRAW_MODE_CODE(getTPage(0, 0, 832, 0));
    ((DR_MODE *)sprt_buff_ptr2)->code[1] = 0;
    SET_TAG_NEXT(sprt_buff_ptr2, 2);
    sprt_buff_ptr2++;

    for (y0 = 0; y0 <= 4; y0++)
    {
        for (x0 = 0; x0 <= 6; x0++)
        {
            SET_TAG_NEXT(sprt_buff_ptr2, 4);
            SET_CODE_RGB(sprt_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
            SET_XY0_WORD(sprt_buff_ptr2,
                         (((x0 - 1) * 64 + (System_timer & 0x3F)) & 0xFFFF) | (((y0 - 1) * 64 + (System_timer & 0x3F)) << 16));
            SET_UV0_CLUT(sprt_buff_ptr2, 0xC0, 0x88, getClut(880, 249));
            SET_WH_WORD(sprt_buff_ptr2, 64, 64);
            sprt_buff_ptr2++;
        }
    }

    addPrims(&Disp_env_ptr->ot[7], sprt_buff_ptr1, sprt_buff_ptr2 - 1);
    Map_prim_ptr = (POLY_FT4 *)sprt_buff_ptr2;
}

// Called with Player_work by game.c on the way back from a screen: calls sound 0x8C when the
// player is in state 3, step 4, and, with unk174's top bits 0x40 and unk178 at 2, sound 0x123,
// 0x12B, 0x134 or 0x136 at joint 4 for weapon_right_no 4, 7, 0xC or 0xD.
void Sub_screen_sound_reinit(PL_WORK *pp)
{
    if ((*(uint32 *)&pp->routine_8 & 0xFFFF00) == 0x40300)
    {
        Sound_call(0x8C, 0, 0);
    }
    if (pp->unk174 & 0xC0)
    {
        if ((pp->unk174 & 0xC0) == 0x40)
        {
            if (pp->weapon_right_no == 4)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x123, &pp->joint_pos[4]);
                }
            }
            if (pp->weapon_right_no == 7)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x12B, &pp->joint_pos[4]);
                }
            }
            if (pp->weapon_right_no == 0xC)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x134, &pp->joint_pos[4]);
                }
            }
            if (pp->weapon_right_no == 0xD)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x136, &pp->joint_pos[4]);
                }
            }
        }
    }
}

void Map_screen_init(void)
{
    *(uint32 *)&Map_screen_work.routine_0 = 0;
    *(uint32 *)&Map_screen_work.type      = 0;
    if (Game_work.sce_no < 9)
    {
        Map_screen_work.type = 0;
    }
    else
    {
        Map_screen_work.type = 1;
    }
}

// The map screen, each frame: draws the map and cursor, and pages through the set's maps with
// L1/left and R1/right/cross (loading the next one). Returns 1 when closed (triangle, start or
// select), 0 otherwise.
sint32 Map_screen_task(void)
{
    uint32 joy_trg;
    MAP_SCREEN_WORK *mp;

    joy_trg = PAD_ON(Joy1);
    mp      = &Map_screen_work;

    switch (mp->routine_0)
    {
        case 0:
            map_cursor_set();
            map_screen_set();

            // Start cancels first.
            if (joy_trg & (PAD_SELECT | PAD_START | PAD_TRIANGLE))
            {
                Sound_call(SE_CANCEL, 1, 0);
                return 1;
            }

            if (((joy_trg & (PAD_R1 | PAD_RIGHT | PAD_START | PAD_CROSS)) == 0) != ((joy_trg & (PAD_L1 | PAD_LEFT)) == 0))
            {
                if (joy_trg & (PAD_L1 | PAD_LEFT))
                {
                    if (--mp->type2 < 0)
                    {
                        mp->type2 = (mp->type > 0) + 1;
                    }
                }
                else
                {
                    if (++mp->type2 > (mp->type > 0) + 1)
                    {
                        mp->type2 = 0;
                    }
                }

                Sound_call(SE_DECISION, 1, 0);
                mp->routine_0++;
                break;
            }
            break;

        case 1:
            if (!mp->type)
            {
                Cd_read_comb(map_a_file_code[mp->type2]);
            }
            else
            {
                Cd_read_comb(map_b_file_code[mp->type2]);
            }

            mp->routine_0++;
            break;

        case 2:
            if (!Cd_read_sync2())
            {
                mp->routine_0 = 0;
            }
            break;
    }
    return 0;
}

// The map image: one 256x240 POLY_FT4 at x 32, into OT 2.
void map_screen_set(void)
{
    POLY_FT4 *ft4_buff_ptr;

    ft4_buff_ptr = Map_prim_ptr++;

    SET_TAG_LEN(ft4_buff_ptr, 9);
    SET_CODE_RGB(ft4_buff_ptr, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr->x0 = ft4_buff_ptr->x2 = 32;
    ft4_buff_ptr->x1 = ft4_buff_ptr->x3 = 287;
    ft4_buff_ptr->y0 = ft4_buff_ptr->y1 = 0;
    ft4_buff_ptr->y2 = ft4_buff_ptr->y3 = 240;

    ft4_buff_ptr->tpage = getTPage(1, 0, 768, 0);
    ft4_buff_ptr->clut  = getClut(0, 250);

    SET_UV_HALF(ft4_buff_ptr->u0, 0x00, 0x00);
    SET_UV_HALF(ft4_buff_ptr->u1, 0xFF, 0x00);
    SET_UV_HALF(ft4_buff_ptr->u2, 0x00, 0xF0);
    SET_UV_HALF(ft4_buff_ptr->u3, 0xFF, 0xF0);

    AddPrim(&Disp_env_ptr->ot[2], ft4_buff_ptr);
}

// The blinking cursor on the map: a 16x16 POLY_FT4 at map_cursor_pos's place for the current stage
// (the area within stages 3 and 0x1B; none in stages 0x17 and 0x1D), animated by System_timer.
void map_cursor_set(void)
{
    sint32 d0;
    sint32 d1;
    sint32 x0;
    sint32 y0;
    GAME_WORK *gp;
    POLY_FT4 *ft4_buff_ptr;

    gp = &Game_work;

    switch (gp->stage_no)
    {
        case 0x17:
        case 0x1D:
            return;

        case 0x03:
        case 0x1B:
            if (gp->area_no < 3)
            {
                d0 = gp->area_no;
            }
            else
            {
                d0 = 3;
            }
            break;

        case 0x0F:
            d0 = 6;
            break;

        case 0x13:
            d0 = 10;
            break;

        case 0x1C:
            d0 = 8;
            break;

        default:
            d0 = gp->stage_no;
            break;
    }

    x0           = map_cursor_pos[d0].vx + 32;
    y0           = map_cursor_pos[d0].vy;
    d1           = (System_timer & 7) * 16;
    ft4_buff_ptr = Map_prim_ptr++;

    SET_TAG_LEN(ft4_buff_ptr, 9);
    SET_CODE_RGB(ft4_buff_ptr, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr->x0 = ft4_buff_ptr->x2 = x0 - 8;
    ft4_buff_ptr->x1 = ft4_buff_ptr->x3 = x0 + 7;
    ft4_buff_ptr->y0 = ft4_buff_ptr->y1 = y0 - 8;
    ft4_buff_ptr->y2 = ft4_buff_ptr->y3 = y0 + 7;

    ft4_buff_ptr->tpage = getTPage(1, 0, 768, 0);
    ft4_buff_ptr->clut  = getClut(0, 250);

    SET_UV_HALF(ft4_buff_ptr->u0, d1, 0xF0);
    SET_UV_HALF(ft4_buff_ptr->u1, d1 + 15, 0xF0);
    SET_UV_HALF(ft4_buff_ptr->u2, d1, 0xFF);
    SET_UV_HALF(ft4_buff_ptr->u3, d1 + 15, 0xFF);

    AddPrim(&Disp_env_ptr->ot[2], ft4_buff_ptr);
}
