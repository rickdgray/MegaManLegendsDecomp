#include "common.h"
#include "st1c.h"

// Installs the stage's slot routine tables.
void func_8010001C(void)
{
    STAGE_TABLE_3C0      = D_80103650;
    STAGE_TABLE_5A4      = D_80103790;
    STAGE_TABLE_10C      = D_801037A4;
    STAGE_TABLE_48       = D_801037A8;
    STAGE_TABLE_24       = D_801037E0;
    STAGE_TABLE_50       = D_801037E4;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_8010008C(void)
{
    void *spawn;
    sint16 *cells;

    STAGE_MAP_WORK_PTR->w      = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h      = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0     = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0     = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1     = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1     = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E) = 0;
    spawn                = D_801038C0[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info   = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells  = cells;
    STAGE_MAP_WORK_PTR->exits  = D_80103940[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_80103998[D_80103A18[Game_work.value_51]], D_80103948[Game_work.value_51]);
    func_8005DC10(0);
    func_801001D0();
}

void func_801001D0(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_801001E0(void)
{
    D_80103C84[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100234(STAGE_ROOM_WORK *wp)
{
    sint32 level;

    level = func_80100360();
    if (wp->routine_4 == 0)
    {
        func_8001DF10(&D_80103C3C[level]);
        if (STAGE_GAME_VALUE_52 < 8)
        {
            func_8001E20C(0);
        }
        wp->routine_4++;
    }
}

void func_801002B0(STAGE_ROOM_WORK *wp)
{
    sint32 level;
    sint32 i;
    ST1C_OBJ50 *op;

    level = func_80100360();
    if (wp->routine_4 == 0)
    {
        func_8001DF10(&D_80103C5C[level]);
        for (i = 0; i < 8; i++)
        {
            if (Sce_flag_test(i + 0x38))
            {
                op = (ST1C_OBJ50 *)func_80031734();
                if (op != NULL)
                {
                    op->kind_2  = 0x22;
                    op->index_C = i;
                    op->flags_0 |= 1;
                }
            }
        }
        wp->routine_4 = 0xFF;
    }
}

// The level (0 to 3) from the scene flags 0x38 to 0x3F, weighted by D_80103C8C.
uint8 func_80100360(void)
{
    sint32 i;
    sint32 sum;

    sum = 0;
    for (i = 0x38; i < 0x40; i++)
    {
        if (Sce_flag_test(i))
        {
            sum += D_80103C8C[i];
        }
    }
    if (sum >= 0x2E)
    {
        return 3;
    }
    if (sum < 0x19)
    {
        return sum >= 0xA;
    }
    return 2;
}
