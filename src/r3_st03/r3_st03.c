#include "common.h"
#include "st03.h"

#ifdef __wasm32__
void Sce_flag_off(sint32 flag);
void stcom36_func_0028(sint8 room);
#endif

void func_801004BC(void)
{
    STAGE_TABLE_3C0 = D_80114350;
    STAGE_TABLE_5A4 = D_801144E4;
    STAGE_TABLE_10C = D_801144E8;
    STAGE_TABLE_48  = D_80114568;
    STAGE_TABLE_24  = D_8011458C;
    STAGE_TABLE_50  = D_801145E0;
}

void func_80100524(void)
{
    ST03_PL *pl;
    void *spawns;
    sint32 room;

    func_80022FD4(D_801146C4[Game_work.value_51]);
    room                      = Game_work.value_51;
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[room].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[room].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[room].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[room].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    STAGE_MAP_WORK_PTR->cells = STAGE_MAP_TBL[room].cells;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    pl                        = ST03_PL_PTR;
    if (STAGE_GAME_VALUE_52 == 0)
    {
        switch (room)
        {
            case 0:
            case 2:
                if (!Sce_flag_test(0x1A))
                {
                    pl->value_44E = 0;
                }
                else
                {
                    pl->value_44E = 1;
                }
                break;
            case 1:
                if (Sce_flag_test(0x1A))
                {
                    STAGE_GAME_BYTE(0x79) = 3;
                    STAGE_GAME_BYTE(0x7A) = 1;
                    STAGE_GAME_BYTE(0x7B) = 0;
                    STAGE_PL_BYTE(0x44E)  = 1;
                }
                else if (!Sce_flag_test(3))
                {
                    STAGE_PL_BYTE(0x44E) = 0;
                    pl->flags_0 |= 3;
                }
                break;
            default:
                pl->value_44E = 0;
                break;
        }
    }
    else
    {
        switch (room)
        {
            case 1:
                STAGE_GAME_BYTE(0x79) = 3;
                STAGE_GAME_BYTE(0x7A) = 1;
                STAGE_GAME_BYTE(0x7B) = 0;
                // fall through
            case 0:
            case 2:
                pl->value_44E = 1;
                break;
            default:
                pl->value_44E = 0;
                break;
        }
    }
    spawns                    = D_80114918[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_80114B7C[Game_work.value_51];
    func_8002EA50(spawns, D_800C356D);
    func_800371A0(D_80114D08[D_80114F08[Game_work.value_51]], D_80114BA0[Game_work.value_51]);
    func_8005DC10(0);
    func_801007B4();
}

void func_801007B4(void)
{
    func_8001DEE4();
    func_8001E4C4(D_801152E4, D_801152EC[STAGE_GAME_VALUE_52]);
    if (STAGE_GAME_VALUE_52 == 0)
    {
        if (Sce_flag_test(2))
        {
            func_8001E4C4(D_801152E4, D_801152EC[14]);
        }
        else if (Sce_flag_test(0xE))
        {
            func_8001E4C4(D_801152E4, D_801152EC[13]);
        }
        else if (Sce_flag_test(0))
        {
            func_8001E4C4(D_801152E4, D_801152EC[12]);
        }
    }
    *(uint32 *)&D_800989F8.routine_4 = 0;
    if (D_801152E0 == 1)
    {
        func_80101B2C();
    }
    D_801152E0 = 0;
}

void func_8010089C(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80115124[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_801150E4[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_8010093C(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(2) == 0))
    {
        stcom36_func_0028(0x11);
        wp->value_4 = 0xFF;
    }
}

#ifdef __wasm32__
void func_80101918(sint32 set);
#endif

void func_80100990(STAGE_ROOM *wp)
{
    sint32 dx;
    sint32 dz;

    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0xC))
            {
                stcom36_func_0028(5);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0xE))
            {
                stcom36_func_0028(4);
                wp->routine_4 = 0xFF;
                func_80101918(1);
            }
            else if (Sce_flag_test(0xD))
            {
                stcom36_func_0028(3);
                wp->routine_4 = 0xFF;
                func_80101918(1);
            }
            else if (Sce_flag_test(0))
            {
                stcom36_func_0028(2);
                wp->routine_4 = 0xFF;
                func_80101918(0);
            }
            else if (Sce_flag_test(4))
            {
                stcom36_func_0028(1);
                wp->routine_4 = 2;
                func_80101918(0);
            }
            else if (Sce_flag_test(3))
            {
                stcom36_func_0028(0);
                wp->routine_4 = 1;
                func_80101918(0);
            }
            else
            {
                stcom36_func_0028(0);
                func_8001DDE4(8);
                Scene_work.reserved00[4] = 0;
                wp->routine_4            = 1;
                func_80101918(0);
            }
            break;
        case 1:
            if (Sce_flag_test(3))
            {
                if (Sce_flag_test(4))
                {
                    wp->routine_4++;
                }
                else if (!Sce_flag_test(0x605))
                {
                    dx = (Player_work.position.x >> 9) - D_80114F2C;
                    dz = (Player_work.position.z >> 9) - D_80114F2D;
                    if ((uint32)dx < D_80114F2E && (uint32)dz < D_80114F2F)
                    {
                        func_8001DDE4(8);
                        Scene_work.reserved00[4] = 1;
                        Sce_flag_on(0x605);
                    }
                }
            }
            break;
        case 2:
            if (!Sce_flag_test(0))
            {
                if (Sce_flag_test(0x604))
                {
                    Sce_flag_off(0x604);
                    func_8001DDE4(8);
                    Scene_work.reserved00[4] = 2;
                }
                break;
            }
            wp->routine_4++;
            break;
    }
}

void func_80100BF8(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;

    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(6))
            {
                stcom36_func_0028(0x10);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x17))
            {
                stcom36_func_0028(0xC);
                wp->routine_4 = 2;
            }
            else if (Sce_flag_test(1) && Sce_flag_test(2))
            {
                wp->routine_4 = 2;
                func_8001DDE4(8);
                Scene_work.reserved00[4] = 3;
            }
            else if (Sce_flag_test(0x1A))
            {
                stcom36_func_0028(0xA);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0xC))
            {
                stcom36_func_0028(9);
                if (Sce_flag_test(0x22) && !Sce_flag_test(0x45))
                {
                    func_80103CC4(0);
                    obj = func_8001EAE8(D_80116754);
                    obj->flags_6 &= ~0x20;
                }
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0xE))
            {
                stcom36_func_0028(8);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0xD))
            {
                stcom36_func_0028(7);
                Sce_flag_on(0x60A);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(4))
            {
                stcom36_func_0028(6);
                Sce_flag_on(0x60A);
                wp->routine_4 = 0xFF;
            }
            else
            {
                stcom36_func_0028(6);
                Sce_flag_on(0x60A);
                wp->routine_4 = 0xFF;
            }
            break;
        case 2:
            if (Sce_flag_test(6))
            {
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x604))
            {
                Sce_flag_off(0x604);
                func_8001DDE4(8);
                Scene_work.reserved00[4] = 4;
            }
            break;
        case 3:
            if (Sce_flag_test(0x1A))
            {
                MojiTaskExec2(0, 0x67);
                stcom36_func_0118(0);
                stcom36_func_0028(0xA);
                wp->routine_4 = 0xFF;
            }
            break;
        case 4:
            obj = ST03_SCENE_OBJ_0;
            func_8001DDE4(0x60);
            ST03_SCENE_OBJ_0 = obj;
            wp->routine_4    = 5;
            break;
        case 5:
            if (Sce_flag_test(0x45))
            {
                if (ST03_SCENE_OBJ_0->flags_0 != 0)
                {
                    func_80031824(ST03_SCENE_OBJ_0);
                }
                func_8001DDE4(0x61);
                Sce_flag_on(0x46);
                wp->routine_4 = 0xFF;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_80100ECC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x16);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F10(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x12);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F54(STAGE_ROOM *wp)
{
    sint32 dx;
    sint32 dz;

    switch (wp->routine_4)
    {
        case 0:
            stcom36_func_0028(0x14);
            wp->routine_4 = 1;
            // fall through
        case 1:
            if (Sce_flag_test(0x2C) && !Sce_flag_test(0x2D) && !Sce_flag_test(0x26) &&
                !Sce_flag_test(0x2E))
            {
                dx = (Player_work.position.x >> 8) - D_80114F30;
                dz = (Player_work.position.z >> 8) - D_80114F31;
                if ((uint32)dx < D_80114F32 && (uint32)dz < D_80114F33)
                {
                    func_8001DDE4(0x1C);
                    Sce_flag_on(0x2E);
                }
            }
            else
            {
                wp->routine_4 = 0xFF;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_80101064(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;
    if (wp->routine_4 == 0)
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            obj->flags_0 = 1;
            obj->kind_2  = 9;
            obj->value_4 = 2;
        }
        wp->routine_4 = 0xFF;
    }
}

void func_801010C8(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x13);
        stcom36_func_0028(0x25);
        wp->value_4 = 0xFF;
    }
}

void func_80101114(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x15);
        wp->routine_4 = 0xFF;
    }
}

void func_80101158(void)
{
}

void func_80101160(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x13);
        stcom36_func_0028(0x25);
        wp->value_4 = 0xFF;
    }
}

void func_801011AC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x15);
        wp->routine_4 = 0xFF;
    }
}

void func_801011F0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x17);
        wp->routine_4 = 0xFF;
    }
}

void func_80101234(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x18);
        wp->routine_4 = 0xFF;
    }
}

void func_80101278(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x19);
        wp->routine_4 = 0xFF;
    }
}

void func_801012BC(void)
{
}

void func_801012C4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x13);
        wp->routine_4 = 0xFF;
    }
}

void func_80101308(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x15);
        wp->routine_4 = 0xFF;
    }
}

void func_8010134C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1A);
        wp->routine_4 = 0xFF;
    }
}

void func_80101390(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1B);
        wp->routine_4 = 0xFF;
    }
}

void func_801013D4(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x1C);
        wp->value_4 = 0xFF;
    }
}

void func_80101418(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x1D);
        wp->value_4 = 0xFF;
    }
}

void func_8010145C(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x1E);
        wp->value_4 = 0xFF;
    }
}

void func_801014A0(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x1F);
        wp->value_4 = 0xFF;
    }
}

void func_801014E4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x20);
        wp->routine_4 = 0xFF;
    }
}

void func_80101528(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x21);
        wp->value_4 = 0xFF;
    }
}

void func_8010156C(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x22);
        wp->value_4 = 0xFF;
    }
}

void func_801015B0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x23);
        wp->routine_4 = 0xFF;
    }
}

void func_801015F4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x24);
        wp->routine_4 = 0xFF;
    }
}

void func_80101638(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        stcom36_func_0028(0x22);
        wp->value_4 = 0xFF;
    }
}

void func_8010167C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x23);
        wp->routine_4 = 0xFF;
    }
}

void func_801016C0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x24);
        wp->routine_4 = 0xFF;
    }
}

sint32 func_80101704(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x235) != 0)
            {
                Sce_flag_on(0x7E2);
                Sce_flag_on(0x7E3);
                Sce_flag_on(0x7E4);
                Sce_flag_on(0x7E8);
            }
            break;
        case 0xFF:
            return 1;
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101778(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x235) != 0))
    {
        Sce_flag_on(0x7E2);
        Sce_flag_on(0x7E3);
        Sce_flag_on(0x7E4);
        Sce_flag_on(0x7E8);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_801017D8(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x235) != 0))
    {
        Sce_flag_on(0x7E2);
        Sce_flag_on(0x7E3);
        Sce_flag_on(0x7E4);
        Sce_flag_on(0x7E8);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101838(ST03_VIEW *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x238) != 0))
    {
        if (Sce_flag_test(0x239) != 0)
        {
            func_80101B70();
        }
        else
        {
            Sce_flag_on(0x239);
            func_8001EB98(D_801151DC);
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_801018B0(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x239) != 0))
    {
        func_80101B70();
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_801018F8(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80101918(sint32 set)
{
    ST03_EMIT *emit;

    D_801152E0 = 1;
    switch (set)
    {
        case 0:
            emit = D_80115148;
            D_8011CA70[0] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[0][0].width_8, ST03_EMIT_TBL[0][0].growth_9,
                              ST03_EMIT_TBL[0][0].count_A, ST03_EMIT_TBL[0][0].rise_C, 0);
            emit++;
            D_8011CA70[1] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[0][1].width_8, ST03_EMIT_TBL[0][1].growth_9,
                              ST03_EMIT_TBL[0][1].count_A, ST03_EMIT_TBL[0][1].rise_C, 0);
            emit++;
            D_8011CA70[2] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[0][2].width_8, ST03_EMIT_TBL[0][2].growth_9,
                              ST03_EMIT_TBL[0][2].count_A, ST03_EMIT_TBL[0][2].rise_C, 0);
            emit++;
            D_8011CA70[3] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[0][3].width_8, ST03_EMIT_TBL[0][3].growth_9,
                              ST03_EMIT_TBL[0][3].count_A, ST03_EMIT_TBL[0][3].rise_C, 0);
            break;
        case 1:
            emit = D_80115188;
            D_8011CA70[0] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[1][0].width_8, ST03_EMIT_TBL[1][0].growth_9,
                              ST03_EMIT_TBL[1][0].count_A, ST03_EMIT_TBL[1][0].rise_C, 0);
            emit++;
            D_8011CA70[1] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[1][1].width_8, ST03_EMIT_TBL[1][1].growth_9,
                              ST03_EMIT_TBL[1][1].count_A, ST03_EMIT_TBL[1][1].rise_C, 0);
            emit++;
            D_8011CA70[2] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[1][2].width_8, ST03_EMIT_TBL[1][2].growth_9,
                              ST03_EMIT_TBL[1][2].count_A, ST03_EMIT_TBL[1][2].rise_C, 0);
            emit++;
            D_8011CA70[3] =
                func_8010FD1C(&emit->pos, ST03_EMIT_TBL[1][3].width_8, ST03_EMIT_TBL[1][3].growth_9,
                              ST03_EMIT_TBL[1][3].count_A, ST03_EMIT_TBL[1][3].rise_C, 0);
            break;
    }
}

void func_80101B2C(void)
{
    sint16 i;
    for (i = 0; i < 4; i++)
    {
        D_8011CA70[i]->routine_0 = 2;
    }
}

void func_80101B70(void)
{
    uint8 state;
    uint8 *count;
    uint8 base;
    uint8 i;
    state = (Sce_flag_test(0x23B) << 1) | Sce_flag_test(0x23A);
    switch (state)
    {
        case 0:
            if (STAGE_GAME_COUNT_62 >= 11)
            {
                Sce_flag_on(0x23A);
                Sce_flag_off(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
        case 1:
            if (STAGE_GAME_COUNT_62 >= 21)
            {
                Sce_flag_off(0x23A);
                Sce_flag_on(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
        case 2:
            if (STAGE_GAME_COUNT_62 >= 31)
            {
                Sce_flag_on(0x23A);
                Sce_flag_on(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
    }
    if (Game_work.value_51 == 8)
    {
        count = &D_80115368[state];
        base  = 0xA;
    }
    else
    {
        count = &D_80115364[state];
        base  = 2;
    }
    for (i = 0; i < *count; i++)
    {
        func_8001EB98(&D_801151C8[base + i]);
    }
}

void func_80101D18(STAGE_ROOM *wp)
{
    D_80115370[wp->routine_4](wp);
}

void func_80101D54(STAGE_ROOM_WORK *wp)
{
    ST03_PL *pl;
    ST03_ACTOR *obj;

    pl = ST03_PL_PTR;
    switch (wp->routine_6)
    {
        case 0:
            wp->routine_6++;
            // fall through
        case 1:
            if (!func_80042238(pl))
            {
                break;
            }
            Sce_event_timer_clear();
            func_8001E6C0(0, 0, 0);
            D_800BC7F0 = D_80115FC4;
            wp->tbl_A4 = (STAGE_ROOM_FUNC *)D_80115FB4;
            wp->routine_6++;
            // fall through
        case 2:
            pl->routine_8   = 3;
            pl->routine_9   = 1;
            pl->fixed_428.x = 0xEE180000;
            pl->fixed_428.y = 0xFFFF0000;
            pl->fixed_428.z = 0x05970000;
            pl->flags_BD |= 0x10;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->anim_448    = 0x30;
            pl->rot_440.x   = 0;
            pl->rot_440.y   = 0;
            pl->rot_440.z   = 0;
            obj             = ST03_SPAWNED_0;
            obj->value_4    = 2;
            obj->routine_0  = 0;
            obj->rotation.y = 0xE77;
            obj             = D_8011CB34[0];
            obj->value_4    = 1;
            obj->routine_0  = 0;
            obj->rotation.y = 0xECE;
            wp->routine_6++;
            break;
        case 3:
            if (ST03_GAME_1 != 2)
            {
                break;
            }
            wp->routine_7 = 1;
            wp->routine_6++;
            Sce_event_timer_clear();
            func_8001E6C0(0, 0, 0);
            D_800BC7F0 = D_80116034;
            wp->tbl_A4 = (STAGE_ROOM_FUNC *)D_8011600C;
            // fall through
        case 4:
            if (((uint8 *)wp->tbl_A4)[1] == 1)
            {
                wp->routine_6++;
                pl->fixed_428.x = 0xEE180000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x05970000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y = 0x4E7;
                wp->timer_C   = 0xF;
            }
            break;
        case 5:
            if (--wp->timer_C < 0)
            {
                MojiTaskExec2(0, 1);
                wp->routine_6++;
                obj                        = D_8011CB34[0];
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 2);
                wp->routine_6++;
                obj                        = ST03_SPAWNED_0;
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                obj                        = D_8011CB34[0];
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
            }
            // fall through
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_next();
                MojiTaskExec2(0, 3);
                wp->routine_6++;
                obj                        = ST03_SPAWNED_0;
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                obj                        = D_8011CB34[0];
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
            }
            // fall through
        case 8:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_next();
                wp->routine_6++;
                obj                        = D_8011CB34[0];
                obj->routine_1             = 4;
                *(uint16 *)&obj->routine_2 = 0;
            }
            // fall through
        case 9:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                MojiTaskExec2(0, 4);
                wp->routine_6++;
            }
            break;
        case 10:
            if (!(Moji_flag & 0x08000000))
            {
                wp->timer_C = 8;
                wp->routine_6++;
            }
            break;
        case 11:
            if (--wp->timer_C == 0)
            {
                func_80042314(pl);
                wp->flags_0 = 0;
                D_800A395C  = 1;
                Sce_flag_on(3);
                stcom36_func_0118();
                stcom36_func_0028(0);
            }
            break;
    }
    if (wp->routine_6 >= 2 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if ((uint32)(wp->routine_6 - 3) < 8 && func_8001DE84())
    {
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        Sound_call(0x108, 0, 0);
        wp->routine_6 = 0xB;
        wp->timer_C   = 1;
        Sce_flag_on(0xA);
        pl->fixed_428.x = 0xEE180000;
        pl->fixed_428.y = 0xFFFF0000;
        pl->fixed_428.z = 0x05970000;
        func_80030150(&pl->fixed_428, &pl->pos_438);
        pl->rot_440.y = 0x4E7;
    }
}

void func_80102224(STAGE_ROOM_WORK *wp)
{
    ST03_PL *pl;
    sint32 turn;
    sint16 y;

    pl = ST03_PL_PTR;
    switch (wp->routine_6)
    {
        case 0:
        case 1:
            if (!func_80042238(pl))
            {
                break;
            }
            wp->routine_7 = 0xA;
            wp->routine_6 += 2;
            pl->routine_8 = 3;
            pl->routine_9 = 1;
            pl->flags_BD |= 0x10;
            pl->pos_438   = pl->position;
            pl->fixed_428 = pl->position_fixed;
            pl->rot_440   = pl->rotation;
            pl->anim_448  = 0x30;
            // fall through
        case 2:
            if (wp->routine_7 != 0)
            {
                wp->routine_7--;
                break;
            }
            y = pl->position.y;
            if (y != func_80048E6C(pl))
            {
                break;
            }
            turn = Muku(&pl->position, &D_801164DC, pl->rotation.y, 0x20);
            if ((sint16)turn == 0)
            {
                pl->anim_448 = 0x30;
                wp->routine_6++;
                MojiTaskExec2(0, 0x1F);
            }
            else
            {
                pl->anim_448  = 0xD;
                pl->rot_440.y = (pl->rot_440.y + turn) & 0xFFF;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                Sound_call(0x10E, 0, 0);
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0      = D_80116164;
                wp->tbl_A4      = D_8011614C;
                pl->fixed_428.x = 0xF6400000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x13C90000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y                        = 0x8C0;
                D_8011CB34[2]->routine_1             = 1;
                *(uint16 *)&D_8011CB34[2]->routine_2 = 0;
                D_8011CB34[2]->rotation.y            = 0x600;
                wp->routine_7                        = 0xA;
                wp->routine_6++;
            }
            break;
        case 4:
            if (((uint8 *)wp->tbl_A4)[1] == 1)
            {
                if (wp->routine_7 == 0)
                {
                    pl->rot_440.y = (pl->rot_440.y + 0x20) & 0xFFF;
                }
                else
                {
                    wp->routine_7--;
                }
            }
            else if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x20);
            }
            break;
        case 5:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_6 += 2;
                pl->rot_440.y = 0;
                D_800A395C    = 1;
                Sce_flag_on(4);
                stcom36_func_0118();
                stcom36_func_0028(1);
            }
            break;
        case 6:
            wp->routine_6++;
            pl->rot_440.y = 0;
            Sce_flag_on(4);
            stcom36_func_0118();
            stcom36_func_0028(1);
            break;
        case 7:
            wp->flags_0 = 0;
            func_80042314(pl);
            break;
    }
    if (wp->routine_6 == 4 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if ((uint32)(wp->routine_6 - 2) < 4 && func_8001DE84())
    {
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        Sound_call(0x108, 0, 0);
        if (wp->routine_6 < 4)
        {
            wp->routine_6 = 6;
        }
        else
        {
            wp->routine_6 = 5;
        }
        pl->fixed_428.x = 0xF6400000;
        pl->fixed_428.y = 0xFFFF0000;
        pl->fixed_428.z = 0x13C90000;
        func_80030150(&pl->fixed_428, &pl->pos_438);
    }
}

void func_8010263C(STAGE_ROOM_WORK *wp)
{
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR pos;
    ST03_PL *pl;
    ST03_ACTOR *obj;

    pl = ST03_PL_PTR;
    switch (wp->routine_6)
    {
        case 0:
            obj   = D_8011CB34[0];
            pos   = obj->position;
            vec.x = obj->position.x;
            vec.y = obj->position.y - 0x50;
            vec.z = obj->position.z;
            func_80039FFC(&vec, 0x12C, Angle_xz_svector(&pos, &pl->position) + 0x20,
                          D_800A396C + 0x61);
            pl->flags_BD |= 0x40;
            pl->flags_0 &= ~2;
            wp->routine_6++;
            break;
        case 1:
            if (func_8003A13C() == 0)
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x2D);
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000) && func_80042238(pl))
            {
                func_80039E50();
                pl->flags_BD &= ~0x40;
                wp->routine_6++;
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0 = D_801161F8;
                wp->tbl_A4 = (STAGE_ROOM_FUNC *)D_801161D0;
                MojiTaskExec2(0, 0x2E);
                pl->routine_8   = 3;
                pl->routine_9   = 1;
                pl->fixed_428.x = 0xF4940000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x048C0000;
                pl->flags_BD |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y = 0x82C;
                pl->rot_440.x = 0;
                pl->rot_440.z = 0;
                pl->anim_448  = 0x30;
                stcom36_func_0118();
                stcom36_func_0028(1);
                Sce_flag_off(0x606);
                Sce_flag_off(0x607);
                obj            = D_8011CB34[2];
                obj->value_4   = 1;
                obj->routine_0 = 0;
                obj            = D_8011CB34[3];
                obj->value_4   = 1;
                obj->routine_0 = 0;
                obj            = D_8011CB34[0];
                obj->value_4   = 1;
                obj->routine_0 = 0;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_6++;
                pl->flags_0 |= 2;
                Sce_event_next();
                obj                        = D_8011CB34[2];
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                obj                        = D_8011CB34[0];
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->timer_C               = D_8011CB34[2]->value_1;
            }
            break;
        case 4:
            if (Sce_flag_test(0x606))
            {
                Sce_flag_off(0x606);
                wp->routine_6++;
                MojiTaskExec2(0, 0x2F);
                obj                        = D_8011CB34[2];
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                obj                        = D_8011CB34[0];
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x31);
                obj                        = D_8011CB34[2];
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                obj                        = D_8011CB34[3];
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x33);
                obj                        = D_8011CB34[2];
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                obj                        = D_8011CB34[3];
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_6++;
                obj                        = D_8011CB34[2];
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->timer_C               = D_8011CB34[3]->value_1;
                obj->value_D               = D_8011CB34[4]->value_1;
                wp->timer_C                = 0xC8;
            }
            break;
        case 8:
            if (--wp->timer_C == 0x8C)
            {
                obj                        = D_8011CB34[0];
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                obj->timer_C               = D_8011CB34[4]->value_1;
            }
            if (wp->timer_C == 0x50)
            {
                wp->routine_6++;
                obj                        = D_8011CB34[3];
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                obj->timer_C               = D_8011CB34[4]->value_1;
            }
            break;
        case 9:
            if (--wp->timer_C < 0)
            {
                Sce_event_next();
                wp->routine_6++;
                pl->fixed_428.x = 0xF5D70000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x04540000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rotation.y = 0x6CC;
                func_80103CC4(3);
                func_80103CC4(4);
                func_80103CC4(1);
                wp->timer_C = 0xB4;
                Sound_call(0x10F, 0, 0);
                D_8011CB34[4]->rotation.y = 0x800;
                D_8011CB34[4]->value_F |= 0x40;
                D_8011CB34[4]->routine_1 = 1;
                D_8011CB34[4]->routine_2 = 0;
                D_8011CB34[4]->routine_3 = 0;
            }
            break;
        case 10:
            if (--wp->timer_C < 0)
            {
                pl->rot_440.y = 0x800;
                wp->routine_6++;
            }
            break;
        case 11:
            func_80042314(pl);
            D_800A395C = 1;
            func_80039820();
            func_80103CC4(5);
            wp->flags_0 = 0;
            Sce_flag_on(0);
            break;
        case 12:
            func_80039E50();
            func_80042314(pl);
            wp->flags_0 = 0;
            Sce_flag_on(0);
            pl->flags_BD &= ~0x40;
            pl->flags_0 |= 2;
            break;
    }
    if ((uint32)(wp->routine_6 - 3) < 8 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (wp->routine_6 < 11 && func_8001DE84())
    {
        func_80103CC4(3);
        func_80103CC4(4);
        func_80103CC4(1);
        func_80103CC4(5);
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        Sound_call(0x108, 0, 0);
        if (wp->routine_6 >= 2)
        {
            wp->routine_6 = 0xB;
        }
        else
        {
            wp->routine_6 = 0xC;
        }
        pl->routine_8   = 3;
        pl->routine_9   = 1;
        pl->fixed_428.x = 0xF5D70000;
        pl->fixed_428.y = 0xFFFF0000;
        pl->fixed_428.z = 0x04540000;
        pl->flags_BD |= 0x10;
        func_80030150(&pl->fixed_428, &pl->pos_438);
        pl->rot_440.x = 0;
        pl->rot_440.y = 0x800;
        pl->rot_440.z = 0;
        pl->anim_448  = 0;
    }
}

void func_80102DBC(STAGE_ROOM_WORK *wp)
{
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR pos;
    ST03_PL *pl;
    ST03_ACTOR *obj;
    ST03_ACTOR *spawned;

    pl = ST03_PL_PTR;
    switch (wp->routine_6)
    {
        case 0:
            spawned = ST03_SPAWNED_0;
            pos     = spawned->position;
            vec.x   = spawned->position.x;
            vec.y   = spawned->position.y - 0x80;
            vec.z   = spawned->position.z;
            func_80039FFC(&vec, 0x140, Angle_xz_svector(&pos, &pl->position), D_800A396C - 0x30);
            pl->flags_BD |= 0x40;
            pl->flags_0 &= ~2;
            wp->routine_6++;
            break;
        case 1:
            if (func_8003A13C() == 0)
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x5F);
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000) && func_80042238(pl))
            {
                func_80039E50();
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0      = D_8011644C;
                wp->tbl_A4      = (STAGE_ROOM_FUNC *)D_8011642C;
                pl->routine_8   = 3;
                pl->routine_9   = 1;
                pl->fixed_428.x = 0x18BD0000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x50290000;
                pl->flags_0 |= 2;
                pl->flags_BD |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y = 0xDE8;
                pl->rot_440.x = 0;
                pl->rot_440.z = 0;
                pl->anim_448  = 0x30;
                stcom36_func_0118();
                stcom36_func_0028(0xD);
                wp->routine_6++;
            }
            break;
        case 3:
            obj                        = D_8011CB34[0];
            obj->routine_1             = 2;
            *(uint16 *)&obj->routine_2 = 0;
            Sound_call(0x150, 0, 0);
            wp->timer_C = 0x5A;
            wp->routine_6++;
            // fall through
        case 4:
            if (--wp->timer_C < 0)
            {
                Sound_call(0x150, 0, 0);
                wp->timer_C = 0x28;
                wp->routine_6++;
            }
            break;
        case 5:
            if (--wp->timer_C < 0)
            {
                obj                        = D_8011CB34[1];
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x609);
                wp->timer_C = 0x14;
                wp->routine_6++;
            }
            break;
        case 6:
            if (--wp->timer_C < 0)
            {
                MojiTaskExec2(0, 0x35);
                wp->routine_6++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                pl->fixed_428.x = 0x18220000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x4F7C0000;
                pl->flags_0 &= ~2;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y = 0x9B2;
                Sce_event_next();
                Sound_call(0x150, 0, 0);
                Sound_call(0x150, 0, 0);
                stcom36_func_0118();
                stcom36_func_0028(0xE);
                wp->routine_6++;
            }
            break;
        case 8:
            obj                        = D_8011CB34[0];
            obj->routine_1             = 2;
            *(uint16 *)&obj->routine_2 = 0;
            obj                        = D_8011CB34[1];
            obj->routine_1             = 2;
            *(uint16 *)&obj->routine_2 = 0;
            obj                        = D_8011CB34[2];
            obj->routine_1             = 2;
            *(uint16 *)&obj->routine_2 = 0;
            wp->timer_C                = 0x14;
            wp->routine_6++;
            break;
        case 9:
            if (--wp->timer_C < 0)
            {
                Sce_flag_on(0x609);
                wp->timer_C = 0x168;
                wp->routine_6++;
                D_8011CA80 = D_801164E4;
            }
            break;
        case 10:
            if (wp->timer_C != 0)
            {
                if (--wp->timer_C != 0 && wp->timer_C == D_8011CA80->time_0)
                {
                    Sound_call2(D_8011CA80->se_2, &pl->position);
                    D_8011CA80++;
                }
            }
            if (wp->timer_C == 0x96)
            {
                MojiTaskExec2(0, 0x36);
                Sce_flag_on(0x609);
                Sound_call(0x15, 0, 0);
            }
            if (wp->timer_C <= 0x5A && !(Moji_flag & 0x08000000))
            {
                wp->routine_6++;
                Sce_flag_on(0x609);
            }
            break;
        case 11:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                MojiTaskExec2(0, 0x37);
                wp->routine_6++;
            }
            break;
        case 12:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_next();
                stcom36_func_0118();
                stcom36_func_0028(0xF);
                wp->timer_C = 0x1E;
                wp->routine_6++;
                pl->flags_0 |= 2;
            }
            break;
        case 13:
            if (--wp->timer_C < 0)
            {
                Sce_flag_on(0x609);
                wp->timer_C = 0x14;
                wp->routine_6++;
            }
            break;
        case 14:
            if (--wp->timer_C < 0)
            {
                pl->anim_448 = 1;
                wp->timer_C  = 0xC;
                wp->routine_6++;
            }
            break;
        case 15:
            spawned       = ST03_SPAWNED_0;
            D_8011CA84    = Muku(&pl->pos_438, &spawned->position, pl->rot_440.y, 0x50);
            pl->rot_440.y = (pl->rot_440.y + D_8011CA84) & 0xFFF;
            func_8002FF34(pl, 0x200, 0, 0);
            if (--wp->timer_C < 0)
            {
                MojiTaskExec2(0, 0x39);
                pl->anim_448  = 0x32;
                pl->rot_440.y = 0x800;
                wp->routine_6++;
            }
            break;
        case 16:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                func_80042314(pl);
                wp->flags_0 = 0;
                D_800A395C  = 1;
                func_80039820();
                stcom36_func_0118();
                Sce_flag_on(6);
                Sce_flag_on(0xB);
                stcom36_func_0028(0x10);
            }
            break;
        case 17:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                func_80039E50();
                func_80042314(pl);
                wp->flags_0 = 0;
                stcom36_func_0118();
                Sce_flag_on(6);
                Sce_flag_on(0xB);
                stcom36_func_0028(0x10);
            }
            break;
    }
    if ((uint32)(wp->routine_6 - 3) < 13 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (wp->routine_6 < 16 && func_8001DE84())
    {
        Sce_flag_on(0x607);
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        Sound_call(0x108, 0, 0);
        if (wp->routine_6 >= 2)
        {
            wp->routine_6 = 0x10;
        }
        else
        {
            wp->routine_6 = 0x11;
        }
        pl->routine_8   = 3;
        pl->routine_9   = 1;
        pl->fixed_428.x = 0x18820000;
        pl->fixed_428.y = 0xFFFF0000;
        pl->fixed_428.z = 0x510A0000;
        pl->flags_BD |= 0x10;
        func_80030150(&pl->fixed_428, &pl->pos_438);
        pl->rot_440.x = 0;
        pl->rot_440.y = 0x800;
        pl->rot_440.z = 0;
    }
}

void func_80103578(STAGE_ROOM_WORK *wp)
{
    ST03_PL *pl;
    ST03_ACTOR *spawned;
    ST03_ACTOR *obj;
    sint16 turn;
    sint32 value; // the angle, then the timer: one variable keeps both in v0

    obj     = ST03_SPAWNED_0;
    spawned = obj;
    pl      = ST03_PL_PTR;
    switch (wp->routine_6)
    {
        case 0:
            if (!func_80042238(pl))
            {
                break;
            }
            stcom36_func_0028(0xB);
            Sce_event_timer_clear();
            func_8001E6C0(0, 0, 0);
            if (Sce_flag_test(0x16))
            {
                D_800BC7F0 = D_8011639C;
            }
            else
            {
                D_800BC7F0 = D_8011630C;
            }
            wp->tbl_A4 = (STAGE_ROOM_FUNC *)D_801162EC;
            wp->routine_6++;
            MojiTaskExec2(0, 0x5E);
            // fall through
        case 1:
            pl->routine_8 = 3;
            pl->routine_9 = 1;
            pl->flags_BD |= 0x10;
            if (Sce_flag_test(0x16))
            {
                pl->fixed_428.x = 0x1CDC0000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x50400000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                value         = 0x59C;
                pl->rot_440.y = value;
                value         = 0xA;
            }
            else
            {
                pl->fixed_428.x = 0x170B0000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x5E9F0000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                value         = 0x1D1;
                pl->rot_440.y = value;
                value         = 0xC;
            }
            pl->rot_440.x = 0;
            pl->rot_440.z = 0;
            wp->timer_C   = value;
            pl->anim_448  = 0x30;
            wp->routine_6++;
            break;
        case 2:
            if (ST03_GAME_1 != 2)
            {
                break;
            }
            wp->routine_6++;
            pl->anim_448 = 1;
            // fall through
        case 3:
            func_8002FF34(pl, 0x200, 0, 0);
            if (wp->timer_C == 5)
            {
                Sce_event_next();
                spawned->routine_1             = 3;
                *(uint16 *)&spawned->routine_2 = 0;
            }
            if (--wp->timer_C == 0)
            {
                pl->anim_448 = 0x30;
                wp->routine_6++;
            }
            break;
        case 4:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                MojiTaskExec2(0, 0x47);
                stcom36_func_0118();
                stcom36_func_0028(0xC);
                obj = ST03_SPAWNED_0;
                if (Sce_flag_test(0x16))
                {
                    obj->rotation.y = 0xBB8;
                }
                else
                {
                    obj->rotation.y = 0x767;
                }
                obj = D_8011CB34[0];
                if (Sce_flag_test(0x16))
                {
                    obj->rotation.y = 0x800;
                }
                else
                {
                    obj->rotation.y = 0x727;
                }
                D_800A395C  = 1;
                wp->timer_C = 0x1E;
                wp->routine_6++;
            }
            break;
        case 5:
            if (--wp->timer_C == 0)
            {
                pl->anim_448 = 0xD;
                wp->routine_6++;
            }
            break;
        case 6:
            turn          = Muku(&pl->pos_438, &obj->position, pl->rot_440.y, 0x20);
            pl->rot_440.y = (pl->rot_440.y + turn) & 0xFFF;
            if (turn == 0)
            {
                pl->anim_448 = 0x31;
                wp->timer_C  = 0x1E;
                wp->routine_6++;
            }
            break;
        case 7:
            if ((wp->timer_C == 0 || --wp->timer_C == 0) && !(Moji_flag & 0x08000000))
            {
                func_80042314(pl);
                wp->flags_0 = 0;
                Sce_flag_on(0x17);
            }
            break;
    }
    if (wp->routine_6 != 0)
    {
        if (wp->routine_6 < 5 && *(uint8 *)wp->tbl_A4 != 0xFF)
        {
            wp->tbl_A4[1](wp);
        }
        if (wp->routine_6 != 0 && wp->routine_6 < 7 && func_8001DE84())
        {
            if (wp->routine_6 < 5)
            {
                D_800A395C = 1;
            }
            MojiTaskKill();
            func_80063BA8();
            Cd_subcmd(0, 1, 0);
            func_8001B314();
            Sound_call(0x108, 0, 0);
            wp->routine_6 = 7;
            wp->timer_C   = 0;
            pl->routine_8 = 3;
            pl->routine_9 = 1;
            pl->flags_BD |= 0x10;
            if (Sce_flag_test(0x16))
            {
                pl->fixed_428.x = 0x1BDA0000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x50FD0000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y = 0x315;
            }
            else
            {
                pl->fixed_428.x = 0x16100000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x5D7D0000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->rot_440.y = 0xFCF;
            }
            pl->rot_440.x = 0;
            pl->rot_440.z = 0;
            stcom36_func_0118();
            stcom36_func_0028(0xC);
            obj = ST03_SPAWNED_0;
            if (Sce_flag_test(0x16))
            {
                obj->rotation.y = 0xBB8;
            }
            else
            {
                obj->rotation.y = 0x767;
            }
            obj = D_8011CB34[0];
            if (Sce_flag_test(0x16))
            {
                obj->rotation.y = 0x800;
            }
            else
            {
                obj->rotation.y = 0x727;
            }
        }
    }
}
