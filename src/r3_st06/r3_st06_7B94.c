#include "common.h"
#include "st06.h"

void func_80107B94(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            func_80107AF0(wp);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(pl))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                pl->value_448         = 0x30;
                wp->routine_4++;
                Fade_start(1);
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
            }
            else if (func_8001DE84() && wp->reserved09[1] == 1 && D_80098A72 == 0)
            {
                func_80053AA4(0);
                Fade_start(9);
                wp->routine_4++;
            }
            else
            {
                func_80107B54((STAGE_ROOM_WORK *)wp);
                if (wp->routine_7 != 0)
                {
                    Sce_camera_update();
                }
                Sce_event_update();
            }
            break;
        case 4:
            if (D_80098A72 == 0)
            {
                Sce_flag_off(0x243);
                Sce_flag_off(0x244);
                Sce_flag_off(0x245);
                Fade_start(1);
                D_800A395C = 1;
                func_80039820();
                wp->routine_4++;
                func_80031824((&wp->child_24)[wp->routine_6]);
                Obj_work_flag_change(0x56, 0xA);
                func_80107E8C(wp);
                func_80039820();
            }
            break;
        case 5:
            if (D_80098A72 == 0)
            {
                func_80042314(&Player_work);
                wp->flags_0 = 0;
            }
            break;
    }
}

sint32 func_80107DB0(void)
{
    if (Sce_flag_test(0x243) != 0)
    {
        return 0;
    }
    if (Sce_flag_test(0x244) != 0)
    {
        return 1;
    }
    if (Sce_flag_test(0x245) != 0)
    {
        return 2;
    }
    return -1;
}

void func_80107E08(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x243) != 0)
    {
        wp->routine_5 |= 1;
    }
    if (Sce_flag_test(0x244) != 0)
    {
        wp->routine_5 |= 2;
    }
    if (Sce_flag_test(0x245) != 0)
    {
        wp->routine_5 |= 4;
    }
}

void func_80107E8C(STAGE_ROOM *wp)
{
    if (wp->routine_5 & 1)
    {
        func_8001E3F0((sint32)D_8012462C);
    }
    if (wp->routine_5 & 2)
    {
        func_8001E3F0((sint32)D_8012462E);
    }
    if (wp->routine_5 & 4)
    {
        func_8001E3F0((sint32)D_80124630);
    }
}

void func_80107F1C(void)
{
}

void func_80107F24(ST06_PL_SCRIPT *wp)
{
    ST06_SCENE *scene;

    scene = (ST06_SCENE *)&Scene_work;
    switch (wp->routine_D)
    {
        case 0:
            wp->pos_438.x   = 0x206;
            wp->pos_438.y   = -0x301;
            wp->pos_438.z   = 0x90F;
            wp->value_448   = 0x30;
            wp->value_440   = 0;
            wp->value_442   = 0;
            wp->value_444   = 0;
            wp->target_184  = NULL;
            wp->fixed_428.x = wp->pos_438.x << 16;
            wp->fixed_428.y = wp->pos_438.y << 16;
            wp->fixed_428.z = wp->pos_438.z << 16;
            wp->routine_D++;
            break;
        case 1:
            if (scene->flag_9 == 1)
            {
                wp->routine_D++;
            }
            break;
        case 2:
            MojiTaskExec2(0, 0x13);
            wp->value_448 = 0x32;
            wp->routine_D++;
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                Cd_xa_seek_id(0x70003);
                wp->timer_E = 0xA;
                wp->routine_D++;
            }
            break;
        case 4:
            if (--wp->timer_E == 0)
            {
                Sce_event_next();
                wp->routine_D++;
            }
            break;
    }
}

void func_80108074(STAGE_PL_SCRIPT *wp)
{
    D_80124954[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_801080D4(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80124824;
    wp->tbl_A4 = D_80124934;
    Scene_obj_ent_open(&D_801248E4[0]);
    Scene_obj_ent_open(&D_801248E4[1]);
    Scene_obj_ent_open(&D_801248E4[2]);
    Scene_obj_ent_open(&D_801248E4[3]);
    Player_work.routine_0 = 3;
    Player_work.routine_1 = 0;
    Player_work.value_C   = 0;
}

void func_80108170(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801081B0(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_801080D4(wp);
                Sce_camera_update();
                wp->routine_4++;
            }
            break;
        case 1:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_4++;
            }
            if (func_8001DE84())
            {
                wp->routine_4 = 0xA;
            }
            // fall through
        case 2:
            func_80108170((STAGE_ROOM_WORK *)wp);
            func_80108074((STAGE_PL_SCRIPT *)&Player_work);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 2)
            {
                wp->routine_4 = 0xB;
            }
            break;
        case 10:
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
            func_8003697C();
            wp->routine_4++;
            func_80031824(wp->child_24);
            func_80031824(wp->child_28);
            break;
        case 11:
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            func_80042314(&Player_work);
            D_800A395C = 1;
            func_80039820();
            wp->flags_0 = 0;
            D_800989FC  = 0;
            break;
    }
}
