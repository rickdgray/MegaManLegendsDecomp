#include "common.h"
#include "st1a.h"

// Installs the stage's slot routine tables.
void func_801006F8(void)
{
    STAGE_TABLE_3C0      = D_8012D648;
    STAGE_TABLE_5A4      = D_8012D7C0;
    STAGE_TABLE_10C      = D_8012D81C;
    STAGE_TABLE_48       = D_8012D8FC;
    STAGE_TABLE_24       = D_8012D984;
    STAGE_TABLE_50       = D_8012DA0C;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_80100768(void)
{
    STAGE_MAP_WORK *mw;
    sint32 room;
    void *spawns;
    STAGE_PL_VIEW *pl;

    mw = STAGE_MAP_WORK_PTR;
    Room_model_init(D_8012DAFC[Game_work.value_51]);
    room      = Game_work.value_51;
    mw->w     = STAGE_MAP_TBL[room].w;
    mw->h     = STAGE_MAP_TBL[room].h;
    mw->x0    = STAGE_MAP_TBL[room].x0;
    mw->z0    = STAGE_MAP_TBL[room].z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = STAGE_MAP_TBL[room].cells;
    mw->info  = STAGE_CELL_INFO;
    pl        = &STAGE_PL;
    switch (room)
    {
        case 2:
        case 0xB:
        case 0xF:
            if (STAGE_SCENE_BYTE(0) != 0 && STAGE_SCENE_BYTE(1) != 0)
            {
                pl->value_44E = -1;
                pl->value_170 = 0;
                pl->value_171 = 1;
                Pl00_shot_enable_off(pl);
                Pl00_shot_enable_on(pl);
                break;
            }
            // fall through
        default:
            pl->value_44E = 1;
            break;
    }
    spawns                    = D_8012E0E0[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8012E4CC[Game_work.value_51];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_8012E7B8[D_8012E810[Game_work.value_51]], D_8012E510[Game_work.value_51]);
    func_8005DC10(D_8012CF28[Game_work.value_51]);
    func_8010097C();
}

void func_8010097C(void)
{
    D_800989FC = 0;
}

// Runs the current room's script.
void func_8010098C(void)
{
    D_8012E8DC[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_801009E0(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            if (Game_work.value_52 == 8)
            {
                wp->routine_4 = 1;
            }
            else
            {
                wp->routine_4 = 0xFF;
            }
            break;
        case 1:
            if (Sce_flag_test(0x56))
            {
                func_8001D974();
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100A80(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos = {0, 0, 0x200, 0};

    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x35))
            {
                Stage_idx_model_set(Map_cell_get(&pos), 0x31500);
                wp->routine_4 = 0xFF;
            }
            else
            {
                wp->routine_4 = 1;
            }
            break;
        case 1:
            if (Sce_flag_test(0x604))
            {
                Sce_flag_on(0x35);
                func_8001DDE4(0x43);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100B70(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x57))
            {
                wp->routine_4 = 0xFF;
            }
            else
            {
                Scene_obj_list_open(D_8012E944);
                wp->routine_4 = 1;
            }
            break;
        case 1:
            if (Sce_flag_test(0x57))
            {
                Sce_flag_on(0x57);
                func_8001DDE4(0x44);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100C24(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100C54(void)
{
}

void func_80100C5C(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100C8C(void)
{
}

void func_80100C94(void)
{
}

void func_80100C9C(void)
{
}
