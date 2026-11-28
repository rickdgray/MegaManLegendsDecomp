#include "common.h"
#include "st06.h"

// Installs the stage's slot routine tables.
void func_801004B4(void)
{
    STAGE_TABLE_3C0 = D_80121BD8;
    STAGE_TABLE_5A4 = D_80121D14;
    STAGE_TABLE_10C = D_80121D4C;
    STAGE_TABLE_48  = D_80121E0C;
    STAGE_TABLE_24  = D_80121E40;
    STAGE_TABLE_50  = D_80121E64;
}

// Sets up the current room: models, map, spawns.
void func_8010051C(void)
{
    STAGE_MAP_WORK *mw;
    sint32 room;
    void *spawns;

    mw = STAGE_MAP_WORK_PTR;
    Room_model_init(D_80121EE4[Game_work.value_51]);
    room      = Game_work.value_51;
    mw->w     = STAGE_MAP_TBL[room].w;
    mw->h     = STAGE_MAP_TBL[room].h;
    mw->x0    = STAGE_MAP_TBL[room].x0;
    mw->z0    = STAGE_MAP_TBL[room].z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = STAGE_MAP_TBL[room].cells;
    mw->info  = STAGE_CELL_INFO;
    if (STAGE_GAME_VALUE_52 == 0 && room == 2)
    {
        STAGE_PL_BYTE(0x44E) = 1;
    }
    else
    {
        STAGE_PL_BYTE(0x44E) = 0;
    }
    spawns                    = D_801220A0[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_80122208[Game_work.value_51];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_80122310[D_801224F0[Game_work.value_51]], D_80122220[Game_work.value_51]);
    func_8005DC10(0);
    func_801006B8();
}

void func_801006B8(void)
{
    func_8001DEE4();
    func_8001E4C4(D_801226A4, D_801226AC[STAGE_GAME_VALUE_52]);
    if (STAGE_GAME_VALUE_52 == 0)
    {
        if (Sce_flag_test(1))
        {
            func_8001E4C4(D_801226A4, D_801226AC[13]);
        }
        else if (Sce_flag_test(2))
        {
            func_8001E4C4(D_801226A4, D_801226AC[12]);
        }
    }
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script (the second set once scene flag 0x1FF is set).
void func_80100764(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80122650[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_80122610[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100804(STAGE_ROOM_WORK *wp)
{
    STAGE_OBJ *obj;

    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x47))
            {
                func_8010214C(1);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(2))
            {
                func_8001DDE4(0x62);
                Sce_flag_on(0x47);
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_8010214C(0);
                wp->routine_4 = 1;
            }
            break;
        case 1:
            obj                        = D_8012BE94;
            obj->variant_3             = 1;
            obj->value_4               = 3;
            *(uint32 *)&obj->routine_0 = 0;
            *(uint32 *)&obj->u_C       = 0;
            obj                        = D_8012BE98;
            obj->value_4               = 3;
            obj->variant_3             = 0;
            *(uint32 *)&obj->routine_0 = 0;
            *(uint32 *)&obj->u_C       = 0;
            wp->routine_4              = 2;
            break;
        case 2:
            if (Sce_flag_test(0x605))
            {
                func_8001DDE4(0xD);
                STAGE_SCENE_BYTE(4) = 0;
                wp->routine_4       = 3;
            }
            break;
    }
}

void func_80100928(ST06_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        if (Sce_flag_test(0x2C) == 0)
        {
            if (Sce_flag_test(2) != 0)
            {
                func_801010E4(D_8012271C);
            }
            else
            {
                Sce_flag_on(2);
                func_8001DDE4(0xB);
            }
        }
        wp->value_4 = 0xFF;
    }
}

void func_801009AC(STAGE_ROOM_WORK *wp)
{
    STAGE_EVENT *ev;

    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x641))
            {
                wp->routine_4 = 2;
            }
            else
            {
                func_8001E460(5, 1, 0);
                func_8001E460(0, 1, 0);
                Sce_flag_on(0x620);
                func_8001DDE4(0xF);
                ev = Open_EVE_WORK();
                if (ev != NULL)
                {
                    ev->flags_0 = 1;
                    ev->kind_2  = 8;
                }
                wp->routine_4 = 1;
            }
            break;
        case 1:
            if (Sce_flag_test(0x621))
            {
                func_8001DDE4(0x10);
            }
            else if (Sce_flag_test(0x640))
            {
                if (Sce_flag_test(0x630))
                {
                    wp->routine_4 = 2;
                }
                else
                {
                    Sce_flag_on(0x641);
                    func_8001DDE4(0x11);
                    wp->routine_4 = 2;
                }
            }
            break;
        case 2:
            func_8001DDE4(0x13);
            wp->routine_4 = 0xFF;
            break;
    }
}

void func_80100ADC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (Sce_flag_test(0x630) == 0)
        {
            Sce_flag_on(0x630);
            func_8001DDE4(0x12);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100B38(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8010214C(2);
        wp->routine_4 = 0xFF;
        func_80102288(func_80048E18(D_80122668) == 0x4B ? 3 : 2);
    }
}

void func_80100BA0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (Sce_flag_test(0x13))
        {
            func_801010E4(D_8012271C);
        }
        else if (Sce_flag_test(0x10))
        {
            Sce_flag_on(0x13);
            func_8001DDE4(0x1A);
        }
        else if (Sce_flag_test(0x2C))
        {
            func_801010E4(D_80123F4C);
        }
        else
        {
            func_801010E4(D_8012271C);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100C44(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (Sce_flag_test(0x13))
        {
            func_801010E4(D_8012271C);
        }
        else if (Sce_flag_test(0x10))
        {
            Sce_flag_on(0x13);
            func_8001DDE4(0x1A);
        }
        else if (Sce_flag_test(0x2C))
        {
            func_801010E4(D_80123F4C);
        }
        else
        {
            func_801010E4(D_8012271C);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100CE8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8010214C(3);
        if (func_80048E18(D_80122668) == 0x4B)
        {
            func_80102288(3);
        }
        else
        {
            func_80102288(2);
        }
        if (func_80048E18(D_80122678) != 0x4B)
        {
            func_80102288(5);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100D78(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        wp->routine_4 = 0xFF;
    }
}

void func_80100D94(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8010214C(4);
        if (func_80048E18(D_80122668) == 0x4B)
        {
            func_80102288(5);
        }
        else
        {
            func_80102288(1);
        }
        if (func_80048E18(D_80122680) != 0x4B)
        {
            func_80102288(3);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100E24(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8010214C(5);
        if (func_80048E18(D_80122668) == 0x4B)
        {
            func_80102288(5);
        }
        else
        {
            func_80102288(1);
        }
        if (func_80048E18(D_80122680) != 0x4B)
        {
            func_80102288(3);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100EB4(ST06_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8010214C(6);
        if (func_80048E18(D_80122668) == 0x4B)
        {
            func_80102288(5);
        }
        else
        {
            func_80102288(1);
        }
        if (func_80048E18(D_80122680) != 0x4B)
        {
            func_80102288(3);
        }
        wp->value_4 = 0xFF;
    }
}

void func_80100F44(ST06_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8010214C(7);
        if (func_80048E18(D_80122668) == 0x4B)
        {
            func_80102288(5);
        }
        else
        {
            func_80102288(1);
        }
        if (func_80048E18(D_80122680) != 0x4B)
        {
            func_80102288(3);
        }
        wp->value_4 = 0xFF;
    }
}

sint32 func_80100FD4(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_4 == 0)
    {
        if (Sce_flag_test(0x236))
        {
            Sce_flag_on(0x7E1);
            Sce_flag_on(0x7E3);
            Sce_flag_on(0x7E4);
            Sce_flag_on(0x7E5);
        }
        if ((Sce_flag_test(0x245) || Sce_flag_test(0x243) || Sce_flag_test(0x244)) && STAGE_GAME_VALUE_52 < 0xB)
        {
            func_8001DDE4(0x59);
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101084(void)
{
    if (STAGE_GAME_VALUE_52 >= 2)
    {
        func_801011D8(D_80122688);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_801010C4(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_801010E4(ST06_SPAWN *rec)
{
    STAGE_OBJ *obj;
    sint32 i;

    for (i = 0; i < 2; rec++, i++)
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            D_8012BEC8[i]               = obj;
            obj->flags_0                = 1;
            obj->kind_2                 = rec->kind_1;
            obj->value_4                = rec->handler_2;
            obj->variant_3              = 1;
            *(sint32 *)&obj->position.x = *(sint32 *)&rec->pos_C.x; // x and y
            *(sint32 *)&obj->u_C        = rec->value_8;
            obj->position.z             = rec->pos_C.z;
            obj->rotation.y             = rec->pos_C.pad;
            obj->position_fixed.v.x     = rec->pos_C.x << 16;
            obj->position_fixed.v.y     = rec->pos_C.y << 16;
            obj->position_fixed.v.z     = rec->pos_C.z << 16;
        }
    }
}

void func_801011D8(ST06_SPAWN *rec)
{
    STAGE_OBJ *obj;

    obj = func_80031418();
    if (obj != NULL)
    {
        obj->flags_0                = 1;
        obj->kind_2                 = rec->kind_1;
        obj->value_4                = rec->handler_2;
        obj->variant_3              = rec->variant_4;
        *(sint32 *)&obj->position.x = *(sint32 *)&rec->pos_C.x; // x and y
        *(sint32 *)&obj->u_C        = rec->value_8;
        obj->position.z             = rec->pos_C.z;
        obj->rotation.y             = rec->pos_C.pad;
        obj->position_fixed.v.x     = rec->pos_C.x << 16;
        obj->position_fixed.v.y     = rec->pos_C.y << 16;
        obj->position_fixed.v.z     = rec->pos_C.z << 16;
    }
}

void func_80101294(void)
{
    func_80031824(D_8012BEC8[0]);
    func_80031824(D_8012BECC);
}

void func_801012CC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8010130C(wp);
        return;
    }
    func_80101470(wp);
}

void func_8010130C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0_A[0] = D_80122894;
            wp->tbl_A4      = D_80122744;
            Scene_obj_ent_open(&D_8012271C[0]);
            Scene_obj_ent_open(&D_8012271C[1]);
            D_8012BEC8[0]     = wp->child_24;
            D_8012BEC8[1]     = wp->child_28;
            wp->reserved09[1] = 0;
            wp->reserved09[2] = 0;
            wp->timer_C       = 0;
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->pos_438.y = -1;
                pl->pos_438.z = -0x8C;
                pl->value_442 = 0x800;
                pl->value_448 = 0x30;
                pl->pos_438.x = 0;
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                wp->routine_5   = 0;
                wp->routine_4++;
            }
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80101470(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            wp->tbl_A4[1](wp);
            if (STAGE_GAME.value_1 == 2 && wp->child_24->routine_0 != 0 && wp->child_28->routine_0 != 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_80122894;
                wp->tbl_A4 = D_80122754;
                wp->routine_5++;
            }
            break;
        case 1:
            wp->tbl_A4[1](wp);
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_5++;
            }
            break;
        case 2:
            MojiTaskExec2(0, 0xC);
            wp->reserved09[1] = 1;
            wp->routine_5++;
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_80122898;
                wp->tbl_A4 = D_80122754;
                wp->routine_5++;
            }
            break;
        case 4:
            STAGE_PL.flags_0 &= ~2;
            wp->tbl_A4[1](wp);
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_5++;
            }
            break;
        case 5:
            MojiTaskExec2(0, 0xD);
            wp->reserved09[1] = 2;
            wp->routine_5++;
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_8012289C;
                wp->tbl_A4 = D_80122754;
                wp->routine_5++;
            }
            break;
        case 7:
            STAGE_PL.flags_0 |= 2;
            wp->tbl_A4[1](wp);
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_5++;
            }
            break;
        case 8:
            MojiTaskExec2(0, 0xE);
            wp->reserved09[1] = 1;
            wp->routine_5++;
            break;
        case 9:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_5++;
            }
            break;
        case 10:
            MojiTaskExec2(0, 0xF);
            wp->reserved09[1] = 2;
            wp->routine_5++;
            break;
        case 11:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_5++;
            }
            break;
        case 12:
            MojiTaskExec2(0, 0x10);
            wp->reserved09[1] = 1;
            wp->routine_5++;
            break;
        case 13:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_801228A0;
                wp->tbl_A4 = D_80122754;
                wp->routine_5++;
            }
            break;
        case 14:
            wp->tbl_A4[1](wp);
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_5++;
            }
            break;
        case 15:
            MojiTaskExec2(0, 0x11);
            wp->reserved09[1] = 2;
            wp->routine_5++;
            break;
        case 16:
            if (!(Moji_flag & 0x08000000))
            {
                STAGE_PL.value_448 = 0;
                Sce_event_timer_clear();
                D_800BC7F0 = D_80122894;
                wp->tbl_A4 = D_80122754;
                wp->routine_5++;
            }
            break;
        case 17:
            wp->tbl_A4[1](wp);
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_5++;
            }
            break;
        case 18:
            MojiTaskExec2(0, 0x12);
            wp->reserved09[1] = 1;
            wp->routine_5++;
            break;
        case 19:
            wp->reserved09[2] |= 0x80;
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_5 = 0x15;
            }
            break;
        case 20:
            if (D_80098A72 == 0)
            {
                Fade_start(1);
                wp->routine_5++;
            }
            break;
        case 21:
            if (D_80098A72 == 0)
            {
                wp->routine_5++;
            }
            break;
        case 22:
            func_80042314(&Player_work);
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            func_80031824(wp->child_24);
            func_80031824(wp->child_28);
            func_801010E4(D_8012271C);
            wp->flags_0 = 0;
            break;
    }
    if (Moji_flag & 0x200000)
    {
        if (wp->reserved09[1] == 1)
        {
            wp->child_24->anim_AC      = 8;
            wp->child_24->anim_prev_AD = 0xFF;
        }
        else if (wp->reserved09[1] == 2)
        {
            wp->child_28->anim_AC      = 8;
            wp->child_28->anim_prev_AD = 0xFF;
        }
    }
    if (func_8001DE84() != 0 && !(wp->reserved09[2] & 0x80))
    {
        Fade_start(9);
        if (Moji_flag & 0x08000000)
        {
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
        }
        wp->routine_5 = 0x14;
        wp->reserved09[2] |= 0x81;
    }
}

void func_80101A38(void)
{
    Sce_camera_update();
    Sce_event_update();
}

void func_80101A60(STAGE_ROOM_WORK *wp)
{
    STAGE_REC *rec;

    rec = D_8012B990;
    D_801228A8[wp->routine_4](wp);
    for (; rec < &D_8012B990[8]; rec++)
    {
        if (rec->active_0 & 1)
        {
            ((STAGE_SLOT_FUNC)rec->data_4)(rec);
        }
    }
}

void func_80101AF4(STAGE_ROOM *wp)
{
    STAGE_ROOM2_FUNC *tbl;
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_6)
    {
        case 0:
            if (func_80042238(pl))
            {
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0 = D_80123140;
                wp->tbl_A4 = D_80123130;
                MojiTaskExec2(0, 0xA);
                Sce_flag_off(0x607);
                Sce_flag_off(0x608);
                Sce_flag_off(0x609);
                Sce_flag_off(0x604);
                func_801023F4();
                func_80102388(0, 0);
                func_80102388(1, 1);
                func_80102388(2, 2);
                wp->routine_6++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x608);
                wp->routine_6++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x604))
            {
                Sce_flag_off(0x604);
                Fade_start(0xA);
                wp->routine_6++;
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                func_801023D0(0);
                func_801023D0(1);
                func_801023D0(2);
                func_80102238();
                D_800C356C = 2;
                D_800C356E = 6;
                D_800C356F = 1;
                D_800C3560 = 0;
                D_800C3562 = 0;
                D_800C3564 = 0;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 2;
                D_800A395C = 1;
                func_80042314(pl);
                wp->flags_0 = 0;
            }
            break;
    }
    if (wp->routine_6 != 0)
    {
        tbl = wp->tbl_A4;
        if (*(uint8 *)tbl != 0xFF)
        {
            tbl[1](wp);
        }
        if (wp->routine_6 != 0 && wp->routine_6 < 3 && func_8001DE84())
        {
            MojiTaskKill();
            func_80063BA8();
            Cd_subcmd(0, 1, 0);
            func_8001B314();
            Sce_flag_on(0x604);
            wp->routine_6 = 2;
        }
    }
}
