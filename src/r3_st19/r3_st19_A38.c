#include "common.h"
#include "st19.h"

void func_80100A38(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_80117190);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A84(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_801171B8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100AD0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_80117198);
        func_8001E20C(0xA);
        func_8001E20C(0xB);
        wp->routine_4 = 0xFF;
    }
}

void func_80100B2C(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x52))
            {
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x34))
            {
                func_8001E068();
                func_8001E460(0, 1, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x52))
            {
                Player_work.flags_bd |= 0x40;
                wp->routine_4++;
            }
            break;
        case 2:
            Sound_fade_start(0x10);
            Fade_start(0xD);
            MojiTaskKill();
            wp->routine_4++;
            break;
        case 3:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                func_8001DDE4(0x42);
                func_8001E460(0, 0, 0);
                wp->routine_4++;
            }
            break;
        case 4:
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100C6C(STAGE_ROOM *wp)
{
    if ((wp->routine_4 == 0) && (Sce_flag_test(0x34) == 0))
    {
        Sce_flag_on(0x34);
        func_8001DDE4(0x41);
        wp->routine_4++;
    }
}

void func_80100CD0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (Sce_flag_test(0x52))
        {
            Scene_obj_list_open(D_801171C0);
        }
        else
        {
            Scene_obj_list_open(D_801171B8);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100D34(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_80117198);
        if (Sce_flag_test(0x52))
        {
            func_8001E20C(0);
            func_8001E20C(1);
            func_8001E20C(6);
            func_8001E20C(7);
            func_8001E20C(8);
            func_8001E20C(9);
        }
        else
        {
            func_8001E20C(10);
            func_8001E20C(11);
            func_8001E20C(6);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100DDC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_801171C8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100E28(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_801171A0);
        wp->routine_4 = 0xFF;
    }
}
