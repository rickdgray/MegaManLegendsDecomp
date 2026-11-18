#include "common.h"
#include "st04.h"

#ifdef __wasm32__
void stcom36_func_0028(sint8 room);
#endif

// Installs the stage's slot routine tables.
void func_80100200(void)
{
    STAGE_TABLE_3C0 = D_8010A570;
    STAGE_TABLE_5A4 = D_8010A6F0;
    STAGE_TABLE_10C = D_8010A6F4;
    STAGE_TABLE_48  = D_8010A7A8;
    STAGE_TABLE_24  = D_8010A7AC;
    STAGE_TABLE_50  = D_8010A808;
}

// Sets up the current room: models, map, spawns.
void func_80100268(void)
{
    ST04_PL_WORK *pl;
    void *spawn;
    sint16 *cells;

    func_80022FD4(D_8010A8C8[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells               = STAGE_MAP_TBL[Game_work.value_51].cells;
    pl                  = ST04_PL;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    if (Game_work.value_51 == 0)
    {
        if (Sce_flag_test(6) && !Sce_flag_test(0x2C))
        {
            D_8010AABB = 1;
        }
        else
        {
            D_8010AABB = 0;
        }
        if (STAGE_GAME_VALUE_52 < 7)
        {
            D_8010AAA2 = 3;
        }
        else
        {
            D_8010AAA2 = 0x1B;
        }
    }
    pl->value_44E       = 0;
    spawn               = D_8010AA84[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8010AC4C[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_8010AD54[D_8010AD9C[Game_work.value_51]], D_8010AC64[Game_work.value_51]);
    func_8005DC10(0);
    func_8010044C();
}

void func_8010044C(void)
{
    func_8001E4C4(D_8010AF44, D_8010AF4C[STAGE_GAME_VALUE_52]);
    if (STAGE_GAME_VALUE_52 == 0)
    {
        if (Sce_flag_test(2))
        {
            func_8001E4C4(D_8010AF44, D_8010AF4C[13]);
        }
        else if (Sce_flag_test(0x46))
        {
            func_8001E4C4(D_8010AF44, D_8010AF4C[12]);
        }
    }
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script (the second set once scene flag 0x1FF is set).
void func_801004F4(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_8010AF2C[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_8010AEEC[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100594(STAGE_ROOM *wp)
{
    ST04_ACTOR *lead;
    ST04_ACTOR *ep;

    switch (wp->routine_4)
    {
        case 0:
            Sce_flag_on(0xD);
            Sce_flag_off(0x16);
            if (Sce_flag_test(0xC))
            {
                Sce_flag_on(0x609);
                Sce_flag_on(0x60A);
                Sce_flag_on(0x60B);
                Sce_flag_on(0x60C);
                Sce_flag_on(0x60D);
            }
            if (Sce_flag_test(9))
            {
                stcom36_func_0028(4);
                wp->routine_4 = 0xFF;
                func_8010207C(1);
            }
            else if (Sce_flag_test(0xF))
            {
                stcom36_func_0028(4);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(6))
            {
                stcom36_func_0028(3);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(1))
            {
                stcom36_func_0028(0x21);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x20))
            {
                stcom36_func_0028(0x22);
                func_8010207C(2);
                func_8010207C(3);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x46))
            {
                stcom36_func_0028(2);
                if (!Sce_flag_test(0x20))
                {
                    lead            = func_8001EB98(&D_8010C9DC[0]);
                    ep              = func_8001EB98(&D_8010C9DC[1]);
                    ep->value_C4    = lead->position;
                    ep              = func_8001EB98(&D_8010C9DC[2]);
                    ep->value_C4    = lead->position;
                    func_8001EB98(&D_8010C9DC[3]);
                    wp->routine_4 = 10;
                }
                else
                {
                    wp->routine_4 = 0xFF;
                }
            }
            else if (Sce_flag_test(0xC))
            {
                stcom36_func_0028(1);
                wp->routine_4 = 0xFF;
            }
            else
            {
                stcom36_func_0028(0);
                wp->routine_4 = 0xFF;
            }
            break;
        case 10:
            if (Player_work.position.z < 0xE00)
            {
                wp->routine_4 = 0xB;
                wp->routine_5 = Player_work.routine_1 != 1;
            }
            break;
        case 11:
            if (func_80042238(&Player_work))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                Player_work.value_448 = 0x30;
                Player_work.value_C   = 0;
                if (wp->routine_5 == 0)
                {
                    Sce_flag_on(0x60F);
                }
                else
                {
                    Sce_flag_on(0x610);
                }
                wp->routine_4 = 0xC;
            }
            break;
        case 12:
            if (!Sce_flag_test(0x60F) && !Sce_flag_test(0x610))
            {
                wp->routine_4 = 10;
                wp->routine_5 = 0;
            }
            else if (Sce_flag_test(0x20))
            {
                func_8010207C(2);
                func_8010207C(3);
                stcom36_func_0028(0x1C);
                wp->routine_4 = 0xFF;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_80100890(STAGE_ROOM *wp)
{
    sint32 set;

    if (wp->routine_4 == 0)
    {
        if (Sce_flag_test(1))
        {
            stcom36_func_0028(7);
            func_8010207C(1);
            func_8010207C(2);
        }
        else
        {
            if (Sce_flag_test(0x46))
            {
                set = 7;
            }
            else if (Sce_flag_test(0xC))
            {
                set = 6;
            }
            else
            {
                set = 5;
            }
            stcom36_func_0028(set);
        }
        if (Sce_flag_test(0x22))
        {
            stcom36_func_0028(0x36);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100948(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x18);
        wp->routine_4 = 0xFF;
    }
}

void func_8010098C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xB);
        wp->routine_4 = 0xFF;
    }
}

void func_801009D0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xC);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A14(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x2F);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A58(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A9C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xD);
        wp->routine_4 = 0xFF;
    }
}

void func_80100AE0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        wp->routine_4 = 0xFF;
    }
}

void func_80100AFC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x20);
        wp->routine_4 = 0xFF;
    }
}

void func_80100B40(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xC);
        wp->routine_4 = 0xFF;
    }
}

void func_80100B84(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(9);
        wp->routine_4 = 0xFF;
    }
}

void func_80100BC8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xE);
        wp->routine_4 = 0xFF;
    }
}

void func_80100C0C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x19);
        wp->routine_4 = 0xFF;
    }
}

void func_80100C50(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x10);
        wp->routine_4 = 0xFF;
    }
}

void func_80100C94(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x13);
        wp->routine_4 = 0xFF;
    }
}

void func_80100CD8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x30);
        wp->routine_4 = 0xFF;
    }
}

void func_80100D1C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(9);
        wp->routine_4++;
    }
}

void func_80100D68(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xE);
        wp->routine_4 = 0xFF;
    }
}

void func_80100DAC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x19);
        wp->routine_4 = 0xFF;
    }
}

void func_80100DF0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x10);
        wp->routine_4 = 0xFF;
    }
}

void func_80100E34(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x13);
        wp->routine_4 = 0xFF;
    }
}

void func_80100E78(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x30);
        wp->routine_4 = 0xFF;
    }
}

void func_80100EBC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xA);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F00(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xF);
        stcom36_func_0028(0x37);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F4C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1A);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F90(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x11);
        wp->routine_4 = 0xFF;
    }
}

void func_80100FD4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x14);
        wp->routine_4 = 0xFF;
    }
}

void func_80101018(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x31);
        wp->routine_4 = 0xFF;
    }
}

void func_8010105C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xA);
        wp->routine_4 = 0xFF;
    }
}

void func_801010A0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xF);
        stcom36_func_0028(0x37);
        wp->routine_4 = 0xFF;
    }
}

void func_801010EC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1A);
        wp->routine_4 = 0xFF;
    }
}

void func_80101130(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x11);
        wp->routine_4 = 0xFF;
    }
}

void func_80101174(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x14);
        wp->routine_4 = 0xFF;
    }
}

void func_801011B8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x31);
        wp->routine_4 = 0xFF;
    }
}

void func_801011FC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x15);
        wp->routine_4 = 0xFF;
    }
}

void func_80101240(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x17);
        wp->routine_4 = 0xFF;
    }
}

void func_80101284(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1B);
        wp->routine_4 = 0xFF;
    }
}

void func_801012C8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x12);
        wp->routine_4 = 0xFF;
    }
}

void func_8010130C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x16);
        wp->routine_4 = 0xFF;
    }
}

void func_80101350(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x32);
        wp->routine_4 = 0xFF;
    }
}

void func_80101394(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x15);
        wp->routine_4 = 0xFF;
    }
}

void func_801013D8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x17);
        wp->routine_4 = 0xFF;
    }
}

void func_8010141C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1B);
        wp->routine_4 = 0xFF;
    }
}

void func_80101460(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x12);
        wp->routine_4 = 0xFF;
    }
}

void func_801014A4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x16);
        wp->routine_4 = 0xFF;
    }
}

void func_801014E8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x32);
        wp->routine_4 = 0xFF;
    }
}

void func_8010152C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1D);
        if (Sce_flag_test(0x22E) != 0)
        {
            func_8010207C(3);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80101588(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x23);
        wp->routine_4 = 0xFF;
    }
}

void func_801015CC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x26);
        wp->routine_4 = 0xFF;
    }
}

void func_80101610(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x29);
        wp->routine_4 = 0xFF;
    }
}

void func_80101654(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x2C);
        wp->routine_4 = 0xFF;
    }
}

void func_80101698(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x33);
        wp->routine_4 = 0xFF;
    }
}

void func_801016DC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1E);
        if (Sce_flag_test(0x22E) != 0)
        {
            func_8010207C(3);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80101738(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x24);
        wp->routine_4 = 0xFF;
    }
}

void func_8010177C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x27);
        wp->routine_4 = 0xFF;
    }
}

void func_801017C0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x2A);
        wp->routine_4 = 0xFF;
    }
}

void func_80101804(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x2D);
        wp->routine_4 = 0xFF;
    }
}

void func_80101848(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x34);
        wp->routine_4 = 0xFF;
    }
}

void func_8010188C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1F);
        if (Sce_flag_test(0x22E) != 0)
        {
            func_8010207C(3);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_801018E8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x25);
        wp->routine_4 = 0xFF;
    }
}

void func_8010192C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x28);
        wp->routine_4 = 0xFF;
    }
}

void func_80101970(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x2B);
        wp->routine_4 = 0xFF;
    }
}

void func_801019B4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x2E);
        wp->routine_4 = 0xFF;
    }
}

void func_801019F8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x35);
        wp->routine_4 = 0xFF;
    }
}

void func_80101A3C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x38);
        wp->routine_4 = 0xFF;
    }
}

void func_80101A80(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x39);
        wp->routine_4 = 0xFF;
    }
}

sint32 func_80101AC4(void)
{
    if (Sce_flag_test(0x235) != 0)
    {
        Sce_flag_on(0x7E2);
        Sce_flag_on(0x7E3);
        Sce_flag_on(0x7E4);
        Sce_flag_on(0x7E5);
        Sce_flag_on(0x7E6);
        Sce_flag_on(0x7E7);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101B24(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80101B44(STAGE_ROOM *wp)
{
    D_8010AFC0[wp->routine_4](wp);
}

void func_80101B80(STAGE_ROOM *wp)
{
    if (wp->routine_6 == 0)
    {
        func_8001F1DC();
        func_8001E6C0(0, 0, 0);
        D_800BC7F0 = D_8010BFD4;
        wp->tbl_A4 = D_8010BFCC;
        wp->routine_6++;
    }
    if (*(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101C1C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_6)
    {
        case 0:
            if (func_80042238(pl))
            {
                func_8001F1DC();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0               = D_8010BFE8;
                wp->tbl_A4               = D_8010BFD8;
                STAGE_PL.routine_0       = 3;
                STAGE_PL.routine_1       = 1;
                STAGE_PL.fixed_428.x     = -0x20 << 16;
                STAGE_PL.fixed_428.y     = -1 << 16;
                STAGE_PL.fixed_428.z     = 0x130 << 16;
                STAGE_PL.flags_bd       |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                STAGE_PL.value_440 = 0;
                STAGE_PL.value_442 = 0;
                STAGE_PL.value_444 = 0;
                STAGE_PL.value_448 = 0x30;
                wp->timer_C        = 10;
                wp->routine_6++;
                MojiTaskExec2(1, 0);
            }
            break;
        case 1:
            if (--wp->timer_C < 0)
            {
                STAGE_PL.value_448 = 0x32;
                wp->routine_6++;
            }
            if (!(Moji_flag & 0x80000000))
            {
                D_800A395C  = 1;
                wp->flags_0 = 0;
                func_80042314(pl);
            }
            break;
        case 2:
            if (STAGE_PL.flags_A7 < 0)
            {
                wp->timer_C = (rand() & 0x1F) + 0x10;
                wp->routine_6--;
            }
            if (!(Moji_flag & 0x80000000))
            {
                D_800A395C  = 1;
                wp->flags_0 = 0;
                func_80042314(pl);
            }
            break;
    }
    if (wp->routine_6 != 0 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}
