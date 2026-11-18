#include "common.h"
#include "st19.h"

// Installs the stage's slot routine tables.
void func_8010055C(void)
{
    STAGE_TABLE_3C0      = D_80116514;
    STAGE_TABLE_5A4      = D_801166A4;
    STAGE_TABLE_10C      = D_801166D4;
    STAGE_TABLE_48       = D_8011671C;
    STAGE_TABLE_24       = D_8011679C;
    STAGE_TABLE_50       = D_801167A0;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_801005CC(void)
{
    STAGE_MAP_WORK *mw;
    STAGE_MAP *map;
    void *spawns;
    STAGE_PL_VIEW *pl;

    mw  = STAGE_MAP_WORK_PTR;
    map = &STAGE_MAP_TBL[Game_work.value_51];
    func_80022FD4(D_80116820[Game_work.value_51]);
    mw->w     = map->w;
    mw->h     = map->h;
    mw->x0    = map->x0;
    mw->z0    = map->z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = map->cells;
    mw->info  = STAGE_CELL_INFO;
    pl        = &STAGE_PL;
    switch (Game_work.value_51)
    {
        case 0:
            STAGE_PL.value_44E = 1;
            break;
        case 3:
            Sce_flag_on(0x31D);
            // fall through
        default:
            pl->value_44E = 0;
            break;
    }
    spawns                    = D_80116970[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_80116A88[Game_work.value_51];
    func_8002EA50(spawns, D_800C356D);
    func_800371A0(D_80116B38[D_80116B90[Game_work.value_51]], D_80116A98[Game_work.value_51]);
    func_8005DC10(0);
    func_80100780();
}

// Sets up the room's scene flags and restarts its script.
void func_80100780(void)
{
    func_8001DEE4();
    func_8001E4C4(D_801171D0, D_801171D8[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_801007CC(void)
{
    D_80116C20[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100820(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x52))
            {
                Player_work.flags_bd |= 0x40;
                wp->routine_4++;
            }
            break;
        case 1:
            func_8001D854(0x10);
            func_80017C30(0xD);
            wp->routine_4++;
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                func_8001DDE4(0x42);
                wp->routine_4++;
            }
            break;
    }
}

void func_801008F0(STAGE_ROOM *wp)
{
    if ((wp->routine_4 == 0) && (Sce_flag_test(0x34) != 0))
    {
        func_8001DDE4(0x41);
        wp->routine_4++;
    }
}
