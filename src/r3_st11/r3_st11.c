#include "common.h"
#include "st11.h"

// Installs the stage's slot routine tables.
void func_801000B4(void)
{
    STAGE_TABLE_3C0 = D_8010945C;
    STAGE_TABLE_5A4 = D_80109568;
    STAGE_TABLE_10C = D_80109584;
    STAGE_TABLE_48  = D_80109644;
    STAGE_TABLE_24  = D_80109684;
    STAGE_TABLE_50  = D_801096C4;
}

// Sets up the current room: models, map, spawns.
void func_8010011C(void)
{
    void *spawn;
    sint16 *cells;

    func_80022FD4(D_80109768[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w      = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h      = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0     = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0     = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1     = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1     = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E) = 1;
    spawn                = D_801097BC[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info   = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells  = cells;
    STAGE_MAP_WORK_PTR->exits  = D_80109820[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_8010984C[D_801098E4[Game_work.value_51]], D_80109824[Game_work.value_51]);
    func_8005DC10(0);
    func_80100284();
}

void func_80100284(void)
{
    func_8001DEE4();
    func_8001E4C4(D_80109BB4, D_80109BBC[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script (the second set once scene flag 0x1FF is set).
void func_801002D0(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80109944[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_80109904[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100370(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80109B8C);
        wp->routine_4++;
    }
}

void func_801003C4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80109B94);
        func_8001E20C(0);
        func_8001E20C(1);
        wp->routine_4++;
    }
}

void func_80100428(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80109B94);
        wp->routine_4++;
    }
}

void func_8010047C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80109B9C);
        wp->routine_4++;
    }
}

void func_801004D0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80109BA4);
        wp->routine_4++;
    }
}

void func_80100524(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80109BAC);
        wp->routine_4++;
    }
}

sint32 func_80100578(void)
{
    if (D_800989F8.routine_4 == 0)
    {
        if (Sce_flag_test(0x21B) && !Sce_flag_test(0x22B))
        {
            func_8001EB98(D_8010E1B8);
        }
        if (!Sce_flag_test(0x23C))
        {
            func_8001EB98(D_8010E1CC);
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}
