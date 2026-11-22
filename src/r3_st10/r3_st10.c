#include "common.h"
#include "st10.h"

void func_801002EC(void)
{
    STAGE_TABLE_3C0 = D_8010F048;
    STAGE_TABLE_5A4 = D_8010F1D4;
    STAGE_TABLE_10C = D_8010F1F0;
    STAGE_TABLE_48  = D_8010F2AC;
    STAGE_TABLE_24  = D_8010F2EC;
    STAGE_TABLE_50  = D_8010F2F0;
}

#ifdef __wasm32__
void func_801006B0(void);
#endif

void func_80100354(void)
{
    STAGE_PL_VIEW *pl;
    void *spawn;
    sint16 *cells;
    func_80022FD4(D_8010F394[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    pl                        = &STAGE_PL;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    if (!Sce_flag_test(0x21B) && Sce_flag_test(0x21A) && STAGE_GAME_COUNT_62 >= 11)
    {
        Sce_flag_on(0x21B);
    }
    if (!Sce_flag_test(0x218) && Sce_flag_test(0x217) && STAGE_GAME_COUNT_62 >= 11)
    {
        Sce_flag_on(0x218);
    }
    if (Game_work.value_51 == 0)
    {
        if (Sce_flag_test(0x21B))
        {
            D_8010F5D4 = D_8010F604;
            Stage_idx_model_set(Map_cell_get(&D_8010F90C), 0x180300);
        }
        else if (Sce_flag_test(0x218))
        {
            D_8010F5D4 = D_8010F5EC;
            Stage_idx_model_set(Map_cell_get(&D_8010F90C), 0x180200);
        }
        pl->value_44E = 1;
    }
    else
    {
        pl->value_44E = 0;
    }
    spawn                     = D_8010F58C[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8010F754[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_8010F85C[D_8010F8F4[Game_work.value_51]], D_8010F76C[Game_work.value_51]);
    func_8005DC10(0);
    func_801006B0();
}

void func_801006B0(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
    func_8001DEE4();
    func_8001E4C4(D_80110094, D_8011009C[STAGE_GAME_VALUE_52]);
}

void func_801006FC(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_8010FA44[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_8010FA04[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_8010079C(STAGE_ROOM *wp)
{
    STAGE_OBJ *slot;

    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8011004C);
        if (!Sce_flag_test(0x48))
        {
            func_8001DDE4(0x63);
            Sce_flag_on(0x48);
        }
        else
        {
            slot = func_8001EAE8(D_801101B4);
            slot->flags_6 &= ~0x20;
        }
        wp->routine_4++;
    }
}

void func_80100838(void)
{
}

void func_80100840(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8011005C);
        wp->routine_4++;
    }
}

void func_80100894(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80110084);
        wp->routine_4++;
    }
}

void func_801008E8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80110054);
        wp->routine_4++;
    }
}
