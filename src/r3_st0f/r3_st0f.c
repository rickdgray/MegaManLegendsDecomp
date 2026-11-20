#include "common.h"
#include "st0f.h"

// Installs the stage's slot routine tables.
void func_8010005C(void)
{
    STAGE_TABLE_3C0      = D_80104840;
    STAGE_TABLE_5A4      = D_801049C0;
    STAGE_TABLE_10C      = D_801049DC;
    STAGE_TABLE_48       = D_80104A24;
    STAGE_TABLE_24       = D_80104A28;
    STAGE_TABLE_50       = D_80104A2C;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_801000CC(void)
{
    void *spawn;
    sint16 *cells;

    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 0;
    spawn                     = D_80104B24[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_80104C54[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_80104D04[D_80104D14[Game_work.value_51]], D_80104C64[Game_work.value_51]);
    func_8005DC10(0);
    func_80100210();
}

void func_80100210(void)
{
    func_8001DEE4();
    func_8001E4C4(D_801058F8, D_80105900[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script (the second set once scene flag 0x1FF is set).
void func_8010025C(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80104E24[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_80104DE4[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_801002FC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105860);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100354(void)
{
}

void func_8010035C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105848);
        wp->routine_4 = 0xFF;
    }
}

void func_801003A8(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105868);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100400(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105888);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100458(void)
{
}

void func_80100460(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105850);
        wp->routine_4 = 0xFF;
    }
}

void func_801004AC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_801004D4(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058A0);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_8010052C(void)
{
}

void func_80100534(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105858);
        wp->routine_4 = 0xFF;
    }
}

void func_80100580(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105870);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_801005D8(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058A0);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100630(void)
{
}

void func_80100638(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105858);
        wp->routine_4 = 0xFF;
    }
}

void func_80100684(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105870);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_801006DC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058A0);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100734(void)
{
}

void func_8010073C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105890);
        wp->routine_4 = 0xFF;
    }
}

void func_80100788(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105878);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_801007E0(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058A0);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100838(void)
{
}

void func_80100840(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105890);
        wp->routine_4 = 0xFF;
    }
}

void func_8010088C(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105878);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_801008E4(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058A8);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_8010093C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105898);
        wp->routine_4 = 0xFF;
    }
}

void func_80100988(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105880);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_801009E0(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058A8);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100A38(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80105898);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A84(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_80105880);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100ADC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058B0);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100B34(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_801058C8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100B80(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058E0);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100BD8(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058B8);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100C30(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_801058D0);
        wp->routine_4 = 0xFF;
    }
}

void func_80100C7C(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058E8);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100CD4(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058C0);
            wp->routine_4 = 0xE1;
            break;
    }
}

void func_80100D2C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_801058D8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100D78(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
        case 1:
            func_8001DF10(D_801058F0);
            wp->routine_4 = 0xFF;
            break;
    }
}

sint32 func_80100DD0(void)
{
    if (D_800989F8.routine_4 == 0 && Sce_flag_test(0x27) && Sce_flag_test(0x207) && !Sce_flag_test(0x545))
    {
        func_8001EB98(D_80106104);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100E3C(STAGE_ROOM_WORK *wp)
{
    ST0F_SCENE_SLOT *slot;

    switch (wp->routine_4)
    {
        case 0:
            if (STAGE_GAME_VALUE_52 >= 2)
            {
                slot = func_8001EB98(D_80106144);
                wp->routine_4++;
                if (Sce_flag_test(0x212) && !Sce_flag_test(0x214))
                {
                    STAGE_PL_BYTE(0xBD) |= 0x40;
                    slot->value_3 = 2;
                    return 1;
                }
                if (Sce_flag_test(0x209) && !Sce_flag_test(0x211) && Sce_flag_test(0x545))
                {
                    func_8001EB98(D_80106118);
                }
                return 1;
            }
            break;
        case 1:
            return 1;
        case 2: // the empty case shapes retail's compare tree
            break;
    }
    wp->routine_4 = 0;
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80100F54(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}
