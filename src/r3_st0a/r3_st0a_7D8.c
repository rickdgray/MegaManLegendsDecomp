#include "common.h"
#include "st0a.h"

void func_801007D8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80114EE0);
        wp->routine_4 = 0xFF;
    }
}

void func_80100824(STAGE_ROOM *wp)
{
    D_80114F50[wp->routine_4](wp);
}

void func_80100860(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_SCRIPT_ENTRY *tbl;
    sint8 i;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0  = D_80114FE8;
            wp->tbl_A4  = D_80115034;
            wp->timer_C = 0;
            Obj_work_flag_change(0xA, 0x80);
            tbl = D_80114F5C;
            func_8001EAE8(&tbl[0]);
            func_8001EAE8(&tbl[1]);
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->pos_438.x = -0xD00;
                pl->pos_438.y = -0x601;
                pl->pos_438.z = 0x2600;
                pl->value_440 = 0;
                pl->value_442 = 0;
                pl->value_444 = 0;
                pl->value_448 = 0;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                wp->routine_5++;
            }
            break;
        case 2:
            for (i = 2; i < 7; i++)
            {
                func_8001EAE8(&D_80114F5C[i]);
            }
            pl->routine_1++;
            wp->routine_5++;
            break;
        case 3:
            D_800C0F96[0] = 0;
            STAGE_PL.flags_bd |= 0x20;
            wp->reserved09[1] = 0x80;
            wp->reserved09[2] = 0;
            wp->routine_6     = 0;
            Cd_xa_play_id(0x2000000A);
            wp->routine_5 = 0;
            wp->routine_4++;
            break;
    }
    func_8001EC0C();
    Sce_event_update();
}

void func_80100A7C(STAGE_ROOM *wp)
{
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    switch (wp->routine_5)
    {
        case 0:
            func_8001EC0C();
            if (func_8001D878() != 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_80115044;
                wp->tbl_A4 = D_80115470;
                wp->reserved09[1] &= 0x7F;
                wp->routine_5++;
            }
            break;
        case 1:
            if (wp->routine_8 != 0xFF)
            {
                wp->tbl_A4[1](wp);
                if ((wp->reserved09[1] & 1) && !(wp->reserved09[1] & 0x80))
                {
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            func_8001EC0C();
            break;
    }
    Sce_event_update();
}

void func_80100B98(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if ((wp->reserved09[1] & 1) && wp->reserved09[2] == 0)
            {
                func_8003187C(wp->child_28);
                func_80031824(wp->child_2C);
                func_80031824(wp->child_30);
            }
            func_8003697C();
            Cd_subcmd(0, 1, 0);
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = -0xD00;
            STAGE_PL.pos_438.y   = -1;
            STAGE_PL.pos_438.z   = 0x1A00;
            STAGE_PL.fixed_428.x = -0xD00 << 16;
            STAGE_PL.fixed_428.y = -1 << 16;
            STAGE_PL.fixed_428.z = 0x1A00 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0x400;
            STAGE_PL.value_444   = 0;
            STAGE_PL.value_448   = 0;
            STAGE_PL.flags_bd |= 0x10;
            wp->routine_5++;
            break;
        case 1:
            func_80042314(&Player_work);
            D_800A395C = 1;
            if (wp->reserved09[1] & 1)
            {
                func_80039820();
            }
            else
            {
                func_8003A264();
            }
            func_8010EB40();
            func_8003187C(wp->child_24);
            MojiTaskExec2(0, 0xA);
            wp->routine_5++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_5++;
            }
            break;
        case 3:
            if (Sound_fade_flags == 0)
            {
                Sound_call(0xC, 0, 0);
                Sound_work.volume_6 = 0x73;
                wp->flags_0         = 0;
            }
            break;
    }
}
