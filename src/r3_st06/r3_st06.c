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
            obj->type                  = 1;
            obj->value_4               = 3;
            *(uint32 *)&obj->routine_0 = 0;
            *(uint32 *)&obj->u_C       = 0;
            obj                        = D_8012BE98;
            obj->value_4               = 3;
            obj->type                  = 0;
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
                    ev->be_flag = MOVE;
                    ev->id      = 8;
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
            obj->be_flag                = MOVE;
            obj->id                     = rec->kind_1;
            obj->value_4                = rec->handler_2;
            obj->type                   = 1;
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
        obj->be_flag                = MOVE;
        obj->id                     = rec->kind_1;
        obj->value_4                = rec->handler_2;
        obj->type                   = rec->variant_4;
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
            STAGE_PL.be_flag &= ~TRANS;
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
            STAGE_PL.be_flag |= TRANS;
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

void func_80101DAC(STAGE_REC_S *rec)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (rec->step_2)
    {
        case 0:
            rec->step_2++;
            // fall through
        case 1:
            pl->routine_0   = 3;
            pl->routine_1   = 1;
            pl->fixed_428.x = 0x2580000;
            pl->fixed_428.y = 0xFCFF0000;
            pl->fixed_428.z = 0x8340000;
            pl->flags_bd |= 0x10;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->value_442 = 0x990;
            pl->value_440 = 0;
            pl->value_444 = 0;
            pl->value_448 = 0x30;
            rec->step_2++;
            break;
        case 2:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                rec->timer_8 = 0x20;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                pl->value_448 = 0xD;
                rec->timer_8  = 0x10;
                rec->step_2++;
            }
            break;
        case 4:
            if (--rec->timer_8 == 0)
            {
                pl->value_448 = 0x30;
                Sce_flag_off(0x608);
                rec->step_2++;
            }
            else
            {
                pl->value_442 = (pl->value_442 - 0x30) & 0xFFF;
            }
            break;
        case 5:
            break;
    }
}

void func_80101F1C(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = D_8012BE94;
    switch (rec->step_2)
    {
        case 0:
            obj->rotation.y = 0x200;
            rec->step_2++;
            break;
        case 1:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                Sce_flag_on(0x607);
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.b.work_1          = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                Sce_flag_off(0x607);
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.b.work_1          = 1;
                obj->rotation.y            = 0;
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                MojiTaskExec2(0, 0xB);
                rec->step_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x604);
                rec->step_2++;
            }
            break;
    }
}

void func_8010205C(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = D_8012BE98;
    switch (rec->step_2)
    {
        case 0:
            rec->timer_8 = 0x258;
            rec->step_2++;
            // fall through
        case 1:
            if (--rec->timer_8 == 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                rec->step_2++;
            }
            break;
    }
}

void func_80102124(void)
{
    Sce_camera_update();
    Sce_event_update();
}

void func_8010214C(sint8 index)
{
    ST06_SPAWN_GROUP *group;
    sint16 i;
    uint32 slot;

    group = &D_80123194[index];
    for (i = 0; i < group->count_0; i++)
    {
        slot = group->list_4[i][0];
        Scene_obj_ent_open(group->list_4[i]);
        D_8012BE88[slot] = STAGE_SCENE_OBJ(slot);
        D_8012BE88[slot]->flags &= ~0x20;
        D_801228A4 |= 0x80000000 >> slot;
    }
}

void func_80102238(void)
{
    sint8 var_s0;

    var_s0 = 0;
    if (D_801228A4 != 0)
    {
        do
        {
            func_80102288(var_s0);
            var_s0++;
        } while (D_801228A4 != 0);
    }
}

void func_80102288(sint8 index)
{
    STAGE_SPAWNED *obj;

    if (D_801228A4 & (0x80000000 >> index))
    {
        obj = D_8012BE88[index];
        switch (func_8002FE74(obj->work_id))
        {
            case 0x20:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_3C0[obj->id][obj->handler](obj);
                break;
            case 0x60:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_10C[obj->id](obj);
                break;
        }
        D_801228A4 &= ~(0x80000000 >> index);
    }
}

void func_80102388(uint8 index, uint8 kind)
{
    STAGE_REC *rec;

    rec           = &D_8012B990[index];
    rec->active_0 = 1;
    rec->value_2  = 0;
    rec->value_3  = 0;
    rec->data_4   = D_80123188[kind];
}

void func_801023D0(uint8 index)
{
    D_8012B990[index].active_0 = 0;
}

void func_801023F4(void)
{
    STAGE_REC *rec;
    sint32 i;

    for (i = 0, rec = D_8012B990; i < 8; i++)
    {
        rec->active_0 = 0;
        rec->index_1  = i;
        rec->value_2  = 0;
        rec->value_3  = 0;
        rec++;
    }
    rec->active_0 = 0;
}

void func_80102430(STAGE_ROOM *wp)
{
    D_801231D4[wp->routine_4](wp);
}

void func_8010246C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0        = D_801231F4;
            wp->tbl_A4        = D_80123240;
            wp->timer_C       = 0;
            wp->reserved09[1] = 0;
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->pos_438.y = -1;
                pl->pos_438.z = -0x2580;
                pl->value_442 = 0x800;
                pl->pos_438.x = 0;
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->value_448 = 0x30;
                D_800C0F96[0] = 0;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                Scene_obj_ent_open(D_801231E0);
                wp->routine_5++;
            }
            break;
        case 2:
            pl->routine_1++;
            wp->routine_5++;
            break;
        case 3:
            Sound_work.volume_6 = 0x6E;
            pl->flags_bd |= 0x20;
            Cd_xa_play_id(0xB000A);
            wp->routine_5++;
            break;
        case 4:
            if (func_8001D878())
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_80123250;
                wp->tbl_A4    = D_80123468;
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_8010263C(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        if (func_8001DE84())
        {
            wp->reserved09[1] = 1;
            wp->routine_5     = 0;
            wp->routine_4++;
        }
        wp->tbl_A4[1](wp);
    }
    else
    {
        wp->routine_5 = 1;
        wp->routine_4++;
    }
    Sce_event_update();
}

void func_801026CC(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8003697C();
            Player_work.routine_0 = 3;
            Player_work.routine_1 = 1;
            STAGE_PL.pos_438.x    = -0x72D;
            STAGE_PL.pos_438.y    = -0x301;
            STAGE_PL.pos_438.z    = 0x9D;
            STAGE_PL.fixed_428.x  = 0xF8D30000;
            STAGE_PL.fixed_428.y  = 0xFCFF0000;
            STAGE_PL.fixed_428.z  = 0x9D0000;
            STAGE_PL.value_440    = 0;
            STAGE_PL.value_442    = 0xA08;
            STAGE_PL.value_444    = 0;
            STAGE_PL.value_448    = 0;
            STAGE_PL.flags_bd |= 0x10;
            wp->routine_5++;
            break;
        case 1:
            Cd_subcmd(0, 1, 0);
            func_80031824(wp->child_24);
            func_80042314(&Player_work);
            if (wp->reserved09[1] != 0)
            {
                D_800A395C = 1;
                func_80039820();
            }
            wp->routine_5++;
            break;
        case 2:
            if (Sound_fade_flags == 0)
            {
                MojiTaskExec2(0, 0xB);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                Sound_call(9, 0, 0);
                wp->routine_5++;
            }
            break;
        case 4:
            wp->flags_0 = 0;
            break;
    }
}

void func_80102878(void)
{
    Sce_camera_update();
}

void func_80102898(void)
{
    Sce_camera_update();
}

void func_801028B8(STAGE_ROOM *wp)
{
    D_800C0F96[0] = 0;
    if (wp->frame_10 >= 0x131)
    {
        D_800C0F96[0] = STAGE_PL.value_124;
    }
    Sce_camera_update();
}

void func_80102908(STAGE_ROOM *wp)
{
    STAGE_PL_PAD *pad;
    uint16 held;

    pad = (STAGE_PL_PAD *)&Player_work;
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -0x804;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = -0xE20;
        STAGE_PL.fixed_428.x = 0xF7FC0000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0xF1E00000;
        STAGE_PL.value_440   = 0;
        STAGE_PL.value_442   = 0x800;
        STAGE_PL.value_444   = 0;
        STAGE_PL.flags_bd |= 0x10;
    }
    else if (wp->frame_10 == 1)
    {
        D_800A395C = 1;
        func_80039820();
    }
    D_800C0F96[0] = 0;
    if (wp->frame_10 < 0x78)
    {
        held          = pad->pad_124;
        D_800C0F96[0] = held;
        if ((uint32)(wp->frame_10 - 0x69) < 0xD)
        {
            D_800C0F96[0] = held | pad->pad_12A;
        }
    }
}

void func_80102A34(STAGE_ROOM *wp)
{
    D_80123490[wp->routine_4](wp);
}

void func_80102A70(STAGE_ROOM *wp)
{
    if (func_80042238(&Player_work))
    {
        if (Sce_flag_test(0x626))
        {
            wp->reserved09[2] = 4;
            wp->routine_4     = 4;
        }
        else
        {
            if (Sce_flag_test(0x622) && !Sce_flag_test(0x62A))
            {
                Sce_flag_on(0x62A);
                wp->reserved09[2] = 0;
            }
            else
            {
                if (Sce_flag_test(0x623))
                {
                    wp->reserved09[2] = 1;
                }
                if (Sce_flag_test(0x624))
                {
                    wp->reserved09[2] = 2;
                }
                if (Sce_flag_test(0x625))
                {
                    wp->reserved09[2] = 3;
                }
            }
            wp->routine_4 = 1;
        }
        wp->routine_5 = 0;
    }
}

void func_80102B3C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            Cd_xa_play_id(D_801238F4[wp->reserved09[2]]);
            wp->routine_5++;
            break;
        case 1:
            if (func_8001D878())
            {
                func_8001E6C0(0, 0, 0);
                D_800BC7F0            = D_801238CC[wp->reserved09[2]];
                wp->tbl_A4            = D_801238E0[wp->reserved09[2]];
                wp->timer_C           = 0;
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                pl->be_flag &= ~TRANS;
                wp->reserved09[1] = 0;
                Sce_camera_update();
                Sce_event_update();
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
}

void func_80102C5C(ST06_OBJ *wp)
{
    uint8 temp_v1;

    if (func_8001DE84() != 0)
    {
        wp->routine_2 |= 1;
    }
    if ((wp->routine_0 == 0xFF) || ((temp_v1 = wp->routine_2, ((temp_v1 & 1) != 0)) && !(temp_v1 & 0x80)))
    {
        wp->value_5 = 0;
        wp->value_4++;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80102CE8(sint8 *arg0)
{
    Cd_subcmd(0, 1, 0);
    func_8003697C();
    func_80042314((STCOM_PL_WORK *)&Player_work);
    D_800A395C = 1;
    func_80039820();
    Sce_flag_off(0x621);
    *arg0 = 0;
}

void func_80102D54(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    Obj_work_flag_change(0x1A, 0x80);
    func_8001E6C0(0, 0, 0);
    D_800BC7F0            = D_801238CC[wp->reserved09[2]];
    pl                    = &Player_work;
    wp->tbl_A4            = D_801238E0[wp->reserved09[2]];
    wp->timer_C           = 0;
    Player_work.routine_0 = 3;
    Player_work.routine_1 = 1;
    STAGE_PL.pos_438.x    = 0x200;
    STAGE_PL.pos_438.y    = -1;
    STAGE_PL.fixed_428.x  = 0x2000000;
    STAGE_PL.fixed_428.y  = 0xFFFF0000;
    STAGE_PL.pos_438.z    = 0;
    STAGE_PL.fixed_428.z  = 0;
    STAGE_PL.value_440    = 0;
    STAGE_PL.value_442    = 0x800;
    STAGE_PL.value_444    = 0;
    STAGE_PL.value_448    = 0;
    pl->be_flag &= ~TRANS;
    STAGE_PL.flags_bd |= 0x10;
    Scene_obj_ent_open(D_801234AC);
    wp->reserved09[1] = 0x80;
    func_8001F580(0x60, 0, 1);
    wp->routine_5 = 0;
    wp->routine_4++;
    Sce_camera_update();
    Sce_event_update();
}

void func_80102EB8(STAGE_ROOM *wp)
{
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    if (wp->routine_8 == 0xFF)
    {
        wp->routine_5 = 0;
        wp->routine_4++;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if ((wp->reserved09[1] & 1) && !(wp->reserved09[1] & 0x80))
        {
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80102F5C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    ST06_CRAB *crab;

    crab = (ST06_CRAB *)wp->child_24;
    Cd_subcmd(0, 1, 0);
    func_8003697C();
    D_800A395C = 1;
    if (wp->reserved09[1] & 1)
    {
        pl = &Player_work;
        pl->be_flag |= TRANS;
        crab->position.x         = 0x200;
        crab->position.y         = -0x4B0;
        crab->position.z         = 0x800;
        crab->rotation.y         = 0;
        crab->position_fixed.v.x = crab->position.x << 16;
        crab->position_fixed.v.y = crab->position.y << 16;
        crab->position_fixed.v.z = crab->position.z << 16;
        func_80039820();
    }
    else
    {
        func_8003A264();
    }
    func_80042314(&Player_work);
    Sce_flag_off(0x621);
    func_801188E4(crab);
    func_8003187C(crab);
    wp->flags_0 = 0;
}

void func_8010305C(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            if (Sound_fade_flags == 0)
            {
                Sound_call(0xA, 0, 0);
                wp->routine_6++;
            }
            break;
        case 1:
            if (Cd_read_sync2() == 0 && wp->frame_10 > 0x64)
            {
                Cd_xa_play_id(0x20000013);
                wp->routine_6++;
            }
            break;
        case 2:
            if (func_8001D878())
            {
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_8010313C(STAGE_OBJ *wp)
{
    if (wp->value_10 == 2)
    {
        wp->routine_2 &= 0x7F;
    }
}

void func_80103164(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.x         = -0x6E0;
        child->position.y         = -0x640;
        child->position.z         = 0x20D0;
        child->rotation.y         = 0xF80;
        child->position_fixed.v.x = child->position.x << 16;
        child->position_fixed.v.y = child->position.y << 16;
        child->position_fixed.v.z = child->position.z << 16;
    }
}

void func_801031C4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->be_flag |= TRANS;
        child                     = wp->child_24;
        child->position.x         = 0x200;
        child->position.y         = -0x708;
        child->position.z         = 0x800;
        child->rotation.y         = 0;
        child->position_fixed.v.x = child->position.x << 16;
        child->position_fixed.v.y = child->position.y << 16;
        child->position_fixed.v.z = child->position.z << 16;
    }
}

void func_80103238(void)
{
}

void func_80103240(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_0 = 2;
    }
    if (wp->frame_10 == 0x59)
    {
        child            = wp->child_24;
        child->routine_0 = 1;
    }
}

void func_80103280(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0xF)
    {
        child            = wp->child_2C;
        child->routine_0 = 2;
    }
    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_28;
        child->routine_0 = 5;
    }
    if (wp->frame_10 == 0x37)
    {
        child            = wp->child_28;
        child->routine_0 = 3;
    }
    if (wp->frame_10 == 0x3B)
    {
        child            = wp->child_2C;
        child->routine_0 = 1;
        child            = wp->child_28;
        child->routine_0 = 4;
    }
}

void func_80103304(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_0 = 4;
        child            = wp->child_28;
        child->routine_0 = 2;
    }
    if (wp->frame_10 == 0x3B)
    {
        Fade_start(0xA);
    }
    if (wp->frame_10 == 0x59)
    {
        child            = wp->child_24;
        child->routine_0 = 1;
    }
}

void func_80103384(void)
{
}

void func_8010338C(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    D_800BC7F0        = D_80123944;
    wp->tbl_A4        = D_801239C0;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->reserved09[1] = 0; // stored twice in retail
    Obj_work_flag_change(0x56, 0x80);
}

void func_801033F8(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80103438(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            func_8010338C(wp);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(pl))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                pl->value_448         = 0;
                Scene_obj_ent_open(&D_80123908[0]);
                Scene_obj_ent_open(&D_80123908[2]);
                Cd_xa_play_id(0x2000000B);
                wp->routine_4++;
            }
            break;
        case 2:
            if (func_8001D878())
            {
                wp->reserved09[1] |= 1;
                func_8005D7C0();
                wp->timer_C = 0;
                wp->routine_4++;
            }
            break;
        case 3:
            if (++wp->timer_C == 0x20)
            {
                wp->routine_4++;
                Player_work.be_flag ^= TRANS;
                Scene_obj_ent_open(D_8012391C);
            }
            break;
        case 4:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
            }
            else if (func_8001DE84() && wp->reserved09[1] == 1 && D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                Fade_start(0xA);
                wp->routine_4++;
            }
            else
            {
                func_801033F8((STAGE_ROOM_WORK *)wp);
                Sce_camera_update();
                Sce_event_update();
            }
            break;
        case 5:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                D_800A395C = 1;
                func_80039820();
                wp->routine_4++;
                if (!Sce_flag_test(0x629))
                {
                    func_8001E3F0(0x12);
                }
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                Cd_subcmd(0, 1, 0);
                Player_work.routine_1++;
                func_80039820();
                Obj_work_flag_change(0x56, 0x80);
                D_800C356C = -1;
                D_800C356E = 6;
                D_800C356F = 5;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 2;
                Player_work.be_flag &= ~(MOVE | TRANS);
                Player_work.value_76 = 0;
                wp->flags_0          = 0;
            }
            break;
    }
}

void func_80103710(STAGE_ROOM *wp)
{
    D_801239E8[wp->routine_4](wp);
}

void func_8010374C(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            wp->reserved09[1] = 0x80;
            // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
            *(uint32 *)&wp->timer_C = 0;
            D_800BC7F0              = D_80123A30;
            wp->tbl_A4              = D_80123E70;
            Scene_obj_ent_open(D_801239F4);
            D_800BBA90[0].flags_0  = D_80123EF0;
            D_800BBA90[0].value_20 = D_80123EF2;
            D_800BBA90[0].value_22 = D_80123EF4;
            wp->routine_5++;
            break;
        case 1:
            Fade_start(3);
            Cd_read_comb(0x62);
            wp->routine_5++;
            break;
        case 2:
            if (D_80098A72 == 0 && Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x20000007);
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878())
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_80123A80;
                wp->tbl_A4    = D_80123E80;
                wp->routine_5 = 0;
                wp->reserved09[1] &= 1;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84())
    {
        wp->reserved09[1] |= 1;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80103904(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        Fade_start(0x14);
        wp->routine_4++;
        wp->routine_5 = 0;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84() != 0 || wp->reserved09[1] == 1)
        {
            Fade_start(8);
            wp->routine_4++;
            wp->routine_5 = 0;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80103998(ST06_OBJ *wp)
{
    uint8 temp_v1;

    if (D_80098A72 == 0)
    {
        temp_v1 = wp->value_5;
        switch (temp_v1)
        {
            case 0:
                Cd_subcmd(0, 1, 0);
                Obj_work_flag_change(0x7E, 0x80);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_80103ED0(2);
                D_800C356C = 2;
                wp->value_5++;
                break;
            case 1:
                *(uint8 *)D_800BBA90 |= 3;
                wp->be_flag = 0;
                break;
        }
    }
    if (wp->routine_2 != 0)
    {
        Sce_camera_update();
        Sce_event_update();
    }
}

void func_80103A84(void)
{
}

void func_80103A8C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        D_800BBA90[0].flags_0 = 0;
        func_80031824(wp->child_24);
        Scene_obj_ent_open(&D_80123A08[0]);
        func_80103ED0(3);
    }
    if (wp->frame_10 == 1)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80103B0C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        wp->routine_5    = 0;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x32)
    {
        child               = wp->child_28;
        child->u_C.b.work_1 = 0;
    }
    if (wp->frame_10 == 0x78)
    {
        child               = wp->child_28;
        child->routine_1    = 3;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
    if (wp->frame_10 == 0x1C2)
    {
        child               = wp->child_28;
        child->routine_1    = 4;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103B98(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x1E)
    {
        child               = wp->child_28;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103BDC(void)
{
}

void func_80103BE4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 6;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
    if (wp->frame_10 == 0x1E)
    {
        child               = wp->child_28;
        child->routine_1    = 7;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103C34(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        Scene_obj_ent_open(D_80123A1C);
        child            = wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 0;
        for (i = 1; i < 5; i++)
        {
            D_800BBA90[i].flags_0  = D_80123EF6[0].flags_0;
            D_800BBA90[i].value_20 = D_80123EF6[0].value_2;
            D_800BBA90[i].value_22 = D_80123EF6[0].value_4;
        }
    }
}

void func_80103CD8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 var_a0;
    sint32 var_v1;

    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_2C);
        var_a0 = 1;
        var_v1 = 0x38;
        do
        {
            ((uint8 *)D_800BBA90)[var_v1] = 0;
            var_a0++;
            var_v1 += 0x38;
        } while (var_a0 < 5);
        child            = wp->child_28;
        child->routine_1 = 9;
        child->routine_2 = 0;
        child->u_C.b.work_1++;
    }
    if (wp->frame_10 == 0x6E)
    {
        child               = wp->child_28;
        child->u_C.b.work_1 = 0;
    }
    if (wp->frame_10 == 0xBE)
    {
        child               = wp->child_28;
        child->routine_1    = 0xA;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
    if (wp->frame_10 == 0xFA)
    {
        child               = wp->child_28;
        child->routine_1    = 0xB;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103DC0(void)
{
}

void func_80103DC8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 0xC;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103DF4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 0xD;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103E20(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 0:
            child               = wp->child_28;
            child->routine_1    = 0xE;
            child->routine_2    = 0;
            child->u_C.b.work_1 = 0;
            break;
        case 0x168:
            child               = wp->child_28;
            child->routine_1    = 0xF;
            child->routine_2    = 0;
            child->u_C.b.work_1 = 0;
            break;
        case 0x190:
            child               = wp->child_28;
            child->routine_1    = 0x10;
            child->routine_2    = 0;
            child->u_C.b.work_1 = 0;
            break;
        case 0x1E0:
            child               = wp->child_28;
            child->routine_1    = 0x11;
            child->routine_2    = 0;
            child->u_C.b.work_1 = 0;
            break;
    }
}

void func_80103EA4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0x50)
    {
        child               = wp->child_28;
        child->routine_1    = 0x12;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80103ED0(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 6;
    D_800C356F = arg0;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80103F34(void)
{
}

void func_80103F3C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        MojiTaskExec2(0, 1);
        Player_work.value_448 = 0x35;
    }
    if (!(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80103F98(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        MojiTaskExec2(0, 5);
    }
    if (wp->frame_10 == 0x29)
    {
        Player_work.value_448 = 0x2D;
    }
    if (wp->frame_10 >= 0x34)
    {
        Sce_event_next();
    }
}

void func_8010400C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        Scene_obj_ent_open(D_80123EFC);
        wp->child_24->type         = 0;
        wp->child_24->u_E.b.work_2 = 0;
        wp->child_24->u_C.b.work_1 = 1;
        wp->child_24->rotation.y   = 0x800;
        Sce_event_next();
    }
}

void func_80104084(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x140;
        wp->child_24->u_E.b.work_2     = 2;
        wp->child_24->u_C.b.work_1     = 1;
        wp->child_24->routine_0        = 2;
    }
    if (wp->frame_10 == 0x5B)
    {
        wp->child_24->value_44.half[0] = 0;
    }
    if (wp->frame_10 >= 0x5B && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x329;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x498;
        STAGE_PL.fixed_428.x             = 0x3290000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x4980000;
        STAGE_PL.value_442               = 0x4F6;
        STAGE_PL.value_448               = 0x30;
        wp->child_24->position.x         = 0x2CE;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x4C0;
        wp->child_24->position_fixed.v.x = 0x2CE0000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x4C00000;
        wp->child_24->rotation.y         = 0xCF6;
        wp->child_24->u_E.b.work_2       = 0;
        wp->child_24->u_C.b.work_1       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Sce_event_next();
    }
}

void func_801041FC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        wp->child_24->u_E.b.work_2 = 8;
        wp->child_24->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 6);
    }
    if (wp->frame_10 >= 0x33 && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x269;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x382;
        STAGE_PL.fixed_428.x             = 0x2690000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x3820000;
        STAGE_PL.value_442               = 0x800;
        STAGE_PL.value_448               = 0xC;
        wp->child_24->position.x         = 0x1A1;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x385;
        wp->child_24->position_fixed.v.x = 0x1A10000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x3850000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.work_2       = 1;
        wp->child_24->u_C.b.work_1       = 1;
        Sce_event_next();
    }
}

void func_80104344(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x40;
    }
    STAGE_PL.fixed_428.z += 0x50000;
    STAGE_PL.pos_438.z = STAGE_PL.fixed_428.z >> 16;
    if (wp->frame_10 == 0x96)
    {
        D_800C356C        = 1;
        D_800C356E        = 6;
        D_800C356F        = 1;
        D_800C356D        = 0;
        D_800C3571        = 0xA;
        D_800C3570        = 0xFF;
        wp->reserved09[2] = 1;
        wp->reserved09[1] = 0;
        Sce_event_next();
    }
}

void func_801043F4(void)
{
}

void func_801043FC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -0x4E;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = -0x51;
        STAGE_PL.fixed_428.x = 0xFFB20000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0xFFAF0000;
        STAGE_PL.value_442   = 0x800;
        STAGE_PL.value_448   = 0x30;
        Scene_obj_ent_open(&D_80123EFC[0]);
        wp->child_24->type               = 0;
        wp->child_24->position.x         = 0x51;
        wp->child_24->position.y         = -1;
        wp->child_24->position.z         = -0x51;
        wp->child_24->position_fixed.v.x = 0x510000;
        wp->child_24->position_fixed.v.y = 0xFFFF0000;
        wp->child_24->position_fixed.v.z = 0xFFAF0000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.work_2       = 0;
        wp->child_24->u_C.b.work_1       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Scene_obj_ent_open(&D_80123EFC[1]);
        Scene_obj_ent_open(&D_80123EFC[2]);
        Scene_obj_ent_open(&D_80123EFC[3]);
        wp->child_28->rotation.y       = 0;
        wp->child_28->value_44.half[0] = 0;
        wp->child_2C->rotation.y       = 0;
        wp->child_2C->value_44.half[0] = 0;
        wp->child_30->rotation.y       = 0x800;
        wp->child_30->value_44.half[0] = 0;
    }
}

void func_801045AC(void)
{
}

void func_801045B4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_28;
    if (child->routine_0 == 1)
    {
        child->routine_0        = 2;
        wp->child_2C->routine_0 = 2;
        wp->child_30->routine_0 = 2;
    }
    if (wp->frame_10 == 0x3D)
    {
        Sce_event_next();
        STAGE_PL_OBJ->be_flag &= ~TRANS;
        wp->child_24->be_flag &= ~TRANS;
    }
}

void func_80104654(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x1F)
    {
        child               = wp->child_28;
        child->u_E.b.work_2 = 8;
        child               = wp->child_28;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x37);
    }
    if ((wp->frame_10 >= 0x33) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801046DC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        child = wp->child_24;
        child->be_flag |= TRANS;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_24;
        child->u_E.b.work_2 = 8;
        child               = wp->child_24;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x38);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_8010478C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        Player_work.be_flag |= TRANS;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x39);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_8010483C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_28;
        child->u_E.b.work_2 = 8;
        child               = wp->child_28;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3AU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801048C4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3BU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_8010494C(STAGE_ROOM *wp)
{
    uint16 *spin;

    if (wp->frame_10 == 0x10)
    {
        Sound_call(0x18C, 0, 0);
    }
    if (wp->frame_10 == 0x1F)
    {
        Sound_call(0x18D, 0, 0);
        wp->child_30->u_E.b.work_2 = 8;
        wp->child_30->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3C);
        wp->child_24->u_E.b.work_2 = 1;
        wp->child_24->u_C.b.work_1 = 1;
        Player_work.value_448      = 0xC;
    }
    if (wp->frame_10 >= 0x20 && wp->frame_10 < 0x3F)
    {
        spin = &STAGE_PL.value_442;
        *spin += 0x40;
        wp->child_24->rotation.y -= 0x40;
    }
    if (wp->frame_10 == 0x3F)
    {
        wp->child_24->u_E.b.work_2 = 0;
        wp->child_24->u_C.b.work_1 = 1;
        Player_work.value_448      = 0x30;
    }
    if ((wp->frame_10 >= 0x4A) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104AAC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_30->u_E.b.work_2            = 1;
        wp->child_30->u_C.b.work_1            = 1;
        wp->child_30->value_44.words.fraction = 0x3C;
        MojiTaskExec2(0, 0x3DU);
    }
    if (wp->frame_10 >= 0x56)
    {
        wp->child_30->u_E.b.work_2            = 0;
        wp->child_30->u_C.b.work_1            = 1;
        wp->child_30->value_44.words.fraction = 0;
    }
    if ((wp->frame_10 >= 0x57) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104B74(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3EU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104BFC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_28->u_E.b.work_2 = 8;
        wp->child_28->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3F);
    }
    if (wp->frame_10 >= 0x20 && !(Moji_flag & 0x08000000))
    {
        Player_work.be_flag &= ~TRANS;
        Sce_event_next();
    }
}

void func_80104C98(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x40);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104D20(void)
{
}

void func_80104D28(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        Player_work.value_448 = 0x82;
        MojiTaskExec2(0, 2);
    }
    if (!(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104D84(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        MojiTaskExec2(0, 7);
    }
    if (wp->frame_10 == 0x29)
    {
        Player_work.value_448 = 0x2D;
    }
    if (wp->frame_10 >= 0x34)
    {
        Sce_event_next();
    }
}

void func_80104DF8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        Scene_obj_ent_open(D_80123EFC);
        wp->child_24->type         = 0;
        wp->child_24->u_E.b.work_2 = 0;
        wp->child_24->u_C.b.work_1 = 1;
        wp->child_24->rotation.y   = 0x800;
        Sce_event_next();
    }
}

void func_80104E70(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x140;
        wp->child_24->u_E.b.work_2     = 2;
        wp->child_24->u_C.b.work_1     = 1;
        wp->child_24->routine_0        = 2;
    }
    if (wp->frame_10 == 0x5B)
    {
        wp->child_24->value_44.half[0] = 0;
    }
    if (wp->frame_10 >= 0x5B && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x329;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x498;
        STAGE_PL.fixed_428.x             = 0x3290000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x4980000;
        STAGE_PL.value_442               = 0x4F6;
        STAGE_PL.value_448               = 0x30;
        wp->child_24->position.x         = 0x2CE;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x4C0;
        wp->child_24->position_fixed.v.x = 0x2CE0000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x4C00000;
        wp->child_24->rotation.y         = 0xCF6;
        wp->child_24->u_E.b.work_2       = 0;
        wp->child_24->u_C.b.work_1       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Sce_event_next();
    }
}

void func_80104FE8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x1F)
    {
        child               = wp->child_24;
        child->u_E.b.work_2 = 8;
        child               = wp->child_24;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 8);
    }
    if ((wp->frame_10 >= 0x33) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105070(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        Player_work.value_448 = 0x32;
        MojiTaskExec2(0, 9);
    }
    if (wp->frame_10 >= 0x33 && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801050EC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        wp->child_24->u_E.b.work_2 = 0x12;
        wp->child_24->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0xA);
    }
    if (wp->frame_10 >= 0x33 && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x269;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x382;
        STAGE_PL.fixed_428.x             = 0x2690000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x3820000;
        STAGE_PL.value_442               = 0x800;
        STAGE_PL.value_448               = 0xC;
        wp->child_24->position.x         = 0x1A1;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x385;
        wp->child_24->position_fixed.v.x = 0x1A10000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x3850000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.work_2       = 1;
        wp->child_24->u_C.b.work_1       = 1;
        Sce_event_next();
    }
}

void func_80105234(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x40;
    }
    STAGE_PL.fixed_428.z += 0x50000;
    STAGE_PL.pos_438.z = STAGE_PL.fixed_428.z >> 16;
    if (wp->frame_10 == 0x96)
    {
        D_800C356C        = 1;
        D_800C356E        = 6;
        D_800C356F        = 4;
        D_800C3571        = 0xA;
        D_800C356D        = 0;
        D_800C3570        = 0xFF;
        wp->reserved09[2] = 1;
        wp->reserved09[1] = 0;
        Sce_event_next();
    }
}

void func_801052E8(void)
{
}

void func_801052F0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -0x4E;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = -0x51;
        STAGE_PL.fixed_428.x = 0xFFB20000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0xFFAF0000;
        STAGE_PL.value_442   = 0x800;
        STAGE_PL.value_448   = 0x30;
        Scene_obj_ent_open(&D_80123EFC[0]);
        wp->child_24->type               = 0;
        wp->child_24->position.x         = 0x51;
        wp->child_24->position.y         = -1;
        wp->child_24->position.z         = -0x51;
        wp->child_24->position_fixed.v.x = 0x510000;
        wp->child_24->position_fixed.v.y = 0xFFFF0000;
        wp->child_24->position_fixed.v.z = 0xFFAF0000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.work_2       = 0;
        wp->child_24->u_C.b.work_1       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Scene_obj_ent_open(&D_80123EFC[1]);
        Scene_obj_ent_open(&D_80123EFC[2]);
        Scene_obj_ent_open(&D_80123EFC[3]);
        wp->child_28->rotation.y       = 0;
        wp->child_28->value_44.half[0] = 0;
        wp->child_2C->rotation.y       = 0;
        wp->child_2C->value_44.half[0] = 0;
        wp->child_30->rotation.y       = 0x800;
        wp->child_30->value_44.half[0] = 0;
    }
}

void func_801054A0(void)
{
}

void func_801054A8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_28;
    if (child->routine_0 == 1)
    {
        child->routine_0        = 2;
        wp->child_2C->routine_0 = 2;
        wp->child_30->routine_0 = 2;
    }
    if (wp->frame_10 == 0x3D)
    {
        Sce_event_next();
        STAGE_PL_OBJ->be_flag &= ~TRANS;
        wp->child_24->be_flag &= ~TRANS;
    }
}

void func_80105548(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x1F)
    {
        child               = wp->child_28;
        child->u_E.b.work_2 = 8;
        child               = wp->child_28;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x37);
    }
    if ((wp->frame_10 >= 0x33) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801055D0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        child = wp->child_24;
        child->be_flag |= TRANS;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_24;
        child->u_E.b.work_2 = 8;
        child               = wp->child_24;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x38);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105680(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        Player_work.be_flag |= TRANS;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x41);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105730(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_28;
        child->u_E.b.work_2 = 8;
        child               = wp->child_28;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x42);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801057B8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x43);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105840(STAGE_ROOM *wp)
{
    uint16 *spin;

    if (wp->frame_10 == 0x10)
    {
        Sound_call(0x18C, 0, 0);
    }
    if (wp->frame_10 == 0x1F)
    {
        Sound_call(0x18D, 0, 0);
        wp->child_30->u_E.b.work_2 = 8;
        wp->child_30->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3C);
        wp->child_24->u_E.b.work_2 = 1;
        wp->child_24->u_C.b.work_1 = 1;
        Player_work.value_448      = 0xC;
    }
    if (wp->frame_10 >= 0x20 && wp->frame_10 < 0x3F)
    {
        spin = &STAGE_PL.value_442;
        *spin += 0x40;
        wp->child_24->rotation.y -= 0x40;
    }
    if (wp->frame_10 == 0x3F)
    {
        wp->child_24->u_E.b.work_2 = 0;
        wp->child_24->u_C.b.work_1 = 1;
        Player_work.value_448      = 0x30;
    }
    if ((wp->frame_10 >= 0x4A) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801059A0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_30->u_E.b.work_2            = 1;
        wp->child_30->u_C.b.work_1            = 1;
        wp->child_30->value_44.words.fraction = 0x3C;
        MojiTaskExec2(0, 0x3DU);
    }
    if (wp->frame_10 >= 0x56)
    {
        wp->child_30->u_E.b.work_2            = 0;
        wp->child_30->u_C.b.work_1            = 1;
        wp->child_30->value_44.words.fraction = 0;
    }
    if ((wp->frame_10 >= 0x57) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105A68(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3EU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105AF0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_28->u_E.b.work_2 = 8;
        wp->child_28->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x3F);
    }
    if (wp->frame_10 >= 0x20 && !(Moji_flag & 0x08000000))
    {
        Player_work.be_flag &= ~TRANS;
        Sce_event_next();
    }
}

void func_80105B8C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.work_2 = 8;
        child               = wp->child_2C;
        child->u_C.b.work_1 = 1;
        MojiTaskExec2(0, 0x40);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105C14(void)
{
    Sce_event_next();
}

void func_80105C34(void)
{
}

void func_80105C3C(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    if (Sce_flag_test(0x629))
    {
        D_800BC7F0 = D_8012411C;
        wp->tbl_A4 = D_80124374;
        func_8001E390(0x2E1);
    }
    else
    {
        D_800BC7F0 = D_80123F74;
        wp->tbl_A4 = D_801242C4;
    }
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    Sce_flag_on(0x52C);
}

void func_80105CE0(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80105D20(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    ST06_ENTRY *entry;
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 16 extra bytes

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            Fade_start(2);
            func_80105C3C(wp);
            wp->routine_4++;
            pl->be_flag |= MOVE | TRANS;
            Sce_camera_update();
            Sce_event_update();
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->value_448   = 0x30;
                pl->pos_438.x   = 0x200;
                pl->pos_438.y   = -0x301;
                pl->pos_438.z   = 0x2E8;
                pl->fixed_428.x = 0x2000000;
                pl->fixed_428.y = 0xFCFF0000;
                pl->fixed_428.z = 0x2E80000;
                pl->value_440   = 0;
                pl->value_442   = 0x800;
                pl->value_444   = 0;
                pl->flags_bd |= 0x10;
                wp->routine_4++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 3:
            D_800C0F96[0] = 0;
            pl->flags_bd |= 0x20;
            wp->reserved09[1] = 1;
            Sce_event_next();
            wp->routine_4++;
            Sce_camera_update();
            Sce_event_update();
            break;
        case 4:
            if (wp->reserved09[2] != 0)
            {
                wp->routine_4++;
                break;
            }
            if (func_8001DE84() != 0 && wp->reserved09[1] == 1)
            {
                func_80053AA4(0);
                Cd_subcmd(0, 1, 0);
                wp->routine_4 = 0xC;
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 5:
            if (D_800C356C_A[0] == 2)
            {
                func_80031824(wp->child_24);
                wp->routine_4++;
                D_800C356C_A[0]++;
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 6:
            if (D_800C356C == 0)
            {
                Fade_start(2);
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
                Sce_event_next();
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 7:
            wp->routine_4++;
            Sce_event_next();
            break;
        case 8:
            if (D_80098A72 == 0)
            {
                wp->reserved09[1] = 1;
                wp->routine_4++;
                Sce_event_next();
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 9:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
                break;
            }
            if (func_8001DE84() != 0 && wp->reserved09[1] == 1)
            {
                func_80053AA4(0);
                Cd_subcmd(0, 1, 0);
                wp->routine_4 = 0x10;
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 10:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 11:
            if (!(Moji_flag & 0x08000000))
            {
                Player_work.be_flag |= TRANS;
                func_80042314(&Player_work);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                wp->child_24->type = wp->child_30->type = 1;
                wp->child_24->routine_0 = wp->child_30->routine_0 = 0;
                wp->child_24->u_C.b.work_0                        = 0x46;
                wp->child_30->u_C.b.work_0                        = 0x47;
                wp->child_24->position.x                          = 0x6F;
                wp->child_24->position.z -= 0x14;
                wp->child_30->position.x += 0xA;
                wp->child_30->position.z = -0x13D;
                func_80031824(wp->child_28);
                func_80031824(wp->child_2C);
                func_80031824(wp->child_30);
                Scene_obj_ent_open(&D_80123F4C[0]);
                Scene_obj_ent_open(&D_80123F4C[1]);
                Sce_flag_on(0x2C);
                Sce_flag_off(0x7E0);
                func_8001D974();
                wp->flags_0 = 0;
            }
            break;
        case 12:
            entry      = &D_800C3558;
            D_800C356C = 1;
            D_800C356E = 6;
            if (Sce_flag_test(0x629) != 0)
            {
                D_800C356F = 4;
            }
            else
            {
                D_800C356F = 1;
            }
            entry->fade_out = 9;
            entry->flags15  = 0;
            entry->fade_in  = 0xFF;
            wp->routine_4++;
            break;
        case 13:
            if (D_800C356C_A[0] == 2)
            {
                func_80031824(wp->child_24);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                wp->routine_4++;
                D_800C356C_A[0]++;
            }
            break;
        case 14:
            if (D_800C356C == 0)
            {
                pl->pos_438.x        = -0x4E;
                pl->position.x       = -0x4E;
                pl->pos_438.y        = -1;
                pl->position.y       = -1;
                pl->pos_438.z        = -0x51;
                pl->position.z       = -0x51;
                pl->fixed_428.x      = 0xFFB20000;
                pl->position_fixed.x = 0xFFB20000;
                pl->fixed_428.y      = 0xFFFF0000;
                pl->position_fixed.y = 0xFFFF0000;
                pl->fixed_428.z      = 0xFFAF0000;
                pl->position_fixed.z = 0xFFAF0000;
                pl->value_442        = 0x800;
                pl->rotation.y       = 0x800;
                pl->value_448        = 0x30;
                Player_work.be_flag |= TRANS;
                Scene_obj_ent_open(&D_80123EFC[0]);
                wp->child_24->position.x         = 0x6F;
                wp->child_24->position.y         = -1;
                wp->child_24->position.z         = -0x65;
                wp->child_24->position_fixed.v.x = 0x6F0000;
                wp->child_24->position_fixed.v.y = 0xFFFF0000;
                wp->child_24->position_fixed.v.z = 0xFF9B0000;
                wp->child_24->rotation.y         = 0;
                wp->child_24->u_E.b.work_2       = 0;
                wp->child_24->u_C.b.work_1       = 1;
                wp->child_24->value_44.half[0]   = 0;
                Scene_obj_ent_open(&D_80123EFC[4]);
                Scene_obj_ent_open(&D_80123EFC[5]);
                Scene_obj_ent_open(&D_80123EFC[3]);
                wp->child_24->type = wp->child_30->type = 1;
                wp->child_30->position.x += 0xA;
                wp->child_30->position.z = -0x13D;
                wp->child_24->routine_0 = wp->child_30->routine_0 = 0;
                wp->child_24->u_C.b.work_0                        = 0x46;
                wp->child_30->u_C.b.work_0                        = 0x47;
                wp->child_28->rotation.y                          = 0;
                wp->child_28->value_44.half[0]                    = 0;
                wp->child_2C->rotation.y                          = 0;
                wp->child_2C->value_44.half[0]                    = 0;
                wp->child_30->rotation.y                          = 0x800;
                wp->child_30->value_44.half[0]                    = 0;
                Fade_start(1);
                wp->routine_4++;
            }
            break;
        case 15:
            if (D_80098A72 == 0)
            {
                Sce_flag_on(0x2C);
                func_80042314(&Player_work);
                func_80031824(wp->child_34);
                func_80031824(wp->child_38);
                func_80031824(wp->child_30);
                Scene_obj_ent_open(&D_80123F4C[0]);
                Scene_obj_ent_open(&D_80123F4C[1]);
                Sce_flag_off(0x7E0);
                func_8001D974();
                wp->flags_0 = 0;
            }
            break;
        case 16:
            Player_work.be_flag |= TRANS;
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            wp->child_24->position.x         = 0x6F;
            wp->child_24->position.y         = -1;
            wp->child_24->position.z         = -0x65;
            wp->child_24->position_fixed.v.x = 0x6F0000;
            wp->child_24->position_fixed.v.y = 0xFFFF0000;
            wp->child_24->position_fixed.v.z = 0xFF9B0000;
            wp->child_24->rotation.y         = 0;
            wp->child_24->u_E.b.work_2       = 0;
            wp->child_24->u_C.b.work_1       = 1;
            wp->child_24->value_44.half[0]   = 0;
            wp->child_24->type = wp->child_30->type = 1;
            wp->child_30->position.x += 0xA;
            wp->child_30->position.z = -0x13D;
            func_80031824(wp->child_28);
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            Scene_obj_ent_open(&D_80123F4C[0]);
            Scene_obj_ent_open(&D_80123F4C[1]);
            wp->child_24->routine_0 = wp->child_30->routine_0 = 0;
            wp->child_24->u_C.b.work_0                        = 0x46;
            wp->child_30->u_C.b.work_0                        = 0x47;
            wp->child_30->rotation.y                          = 0x800;
            wp->child_30->value_44.half[0]                    = 0;
            Sce_flag_on(0x2C);
            func_80042314(&Player_work);
            func_80031824(wp->child_28);
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            Sce_flag_off(0x7E0);
            func_8001D974();
            wp->flags_0 = 0;
            break;
    }
}

void func_80106618(STAGE_PL_SCRIPT *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    switch (wp->routine_D)
    {
        case 0:
            wp->value_448 = 0x30;
            wp->routine_D++;
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                wp->routine_D++;
            }
            break;
        case 2:
            wp->value_448 = 0xC;
            wp->timer_E   = 0;
            wp->routine_D++;
            break;
        case 3:
            wp->timer_E++;
            wp->fixed_428.z += 0x50000;
            if (wp->timer_E == 0x3C)
            {
                wp->routine_D++;
            }
            break;
        case 4:
            wp->value_442 = 0x700;
            wp->value_448 = 0x30;
            wp->fixed_428.x += 0x64;
            wp->routine_D++;
            break;
        case 5:
            if (scene->u_8.byte[1] == 5)
            {
                wp->value_442 = 0x800;
                wp->routine_D++;
            }
            break;
        case 6:
            break;
    }
}

void func_80106720(STAGE_PL_SCRIPT *wp)
{
    D_801245AC[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_80106780(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.fixed_428.z = -450 << 16;
        STAGE_PL.fixed_428.x = 0;
        STAGE_PL.fixed_428.y = 0;
        STAGE_PL.value_442   = 0x800;
    }
}

void func_801067BC(void)
{
}

void func_801067C4(void)
{
}

void func_801067CC(STAGE_ROOM *wp)
{
    STAGE_SPAWNED *obj;
    sint32 i;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80124484;
    wp->tbl_A4 = D_801245B0;
    for (i = 0; i < 2; i++)
    {
        // One-pass block preserves retail's register allocation and scheduling.
        do
        {
            obj = Scene_obj_ent_open(D_80124434[i]);
        } while (0);
        obj->flags &= ~0x20;
    }
    Player_work.routine_0 = 3;
    Player_work.routine_1 = 1;
    STAGE_PL.value_C      = 0;
}

void func_8010687C(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801068BC(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_801067CC(wp);
                Sce_camera_update();
                wp->routine_4++;
            }
            break;
        case 1:
        case 2:
            wp->routine_4++;
            break;
        case 3:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_4++;
            }
            if (func_8001DE84() != 0)
            {
                wp->routine_4 = 10;
            }
            // fall through
        case 4:
            func_8010687C((STAGE_ROOM_WORK *)wp);
            func_80106720((STAGE_PL_SCRIPT *)&Player_work);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 4)
            {
                wp->routine_4 = 11;
            }
            break;
        case 10:
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
            D_800A395C = 1;
            func_80039820();
            Sce_flag_on(0x52B);
            wp->routine_4++;
            break;
        case 11:
            func_80042314(&Player_work);
            D_800A395C = 1;
            func_8003A264();
            D_800989F8.routine_5 = 1;
            wp->flags_0          = 0;
            func_8001E3F0(0x16);
            func_8001D974();
            break;
    }
}

void func_80106A44(sint16 arg0, sint16 arg1, sint16 arg2, sint16 arg3)
{
    D_800C356C = 1;
    D_800C356E = 6;
    D_800C3571 = 0xA;
    D_800C356F = 0;
    D_800C3560 = arg0;
    D_800C3562 = arg1;
    D_800C3564 = arg2;
    D_800C356A = arg3;
    D_800C356D = 0;
    D_800C3570 = 2;
}

void func_80106AAC(STAGE_ROOM *wp)
{
    STAGE_ACTOR *slot;
    sint32 i;

    if (func_80042238(&Player_work))
    {
        for (i = 0, slot = D_8009F108; i < 16; i++, slot++)
        {
            if (slot->be_flag != 0 && slot->id == 5)
            {
                break;
            }
        }
        wp->child_24        = (STAGE_OBJ *)slot;
        STAGE_GAME.value_78 = 1;
        STAGE_GAME.value_79 = 6;
        STAGE_GAME.value_7A = 0;
        STAGE_PL.flags_bd   = (STAGE_PL.flags_bd | 0x20) & ~0x40;
        Sce_flag_on(0x318);
        Sce_flag_on(0x319);
        Sce_flag_on(0x31A);
        D_8012BA00    = 0;
        wp->routine_5 = 0;
        wp->routine_6 = 0;
        wp->routine_7 = 0;
        wp->routine_4++;
    }
}

void func_80106B98(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_CAM *cam;
    STAGE_OBJ *obj;
    STAGE_OBJ *piece;
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR *pos;
    STCOM_SVECTOR *target;
    sint32 i;
    sint16 turn;

    pl  = &STAGE_PL;
    cam = &Sce_camera_work;
    obj = wp->child_24;
    switch (wp->routine_5)
    {
        case 0:
            MojiTaskExec2(0, 0x15);
            wp->routine_5++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                vec.x = obj->position.x;
                vec.y = obj->position.y - 0x80;
                vec.z = obj->position.z - 0x102;
                func_80039FFC(&vec, 0, 0, 0);
                D_8012BA00 = 1;
                wp->routine_5++;
            }
            break;
        case 2:
            if (func_8003A13C() == 0)
            {
                obj->u_E.b.work_2 = 8;
                obj->u_C.b.work_1 = 1;
                MojiTaskExec2(0, 0x16);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                func_80106A44(0x200, -0x300, 0x9E1, 0);
                wp->routine_5++;
            }
            break;
        case 4:
            if (D_800C356C_A[0] == 2)
            {
                D_800C356C_A[0]++;
                func_80039E50();
                D_8012BA00 = 0;
                wp->routine_5++;
            }
            break;
        case 5:
            if (D_800C356C == 0)
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->be_flag            = MOVE;
                    obj->id                 = 5;
                    obj->value_4            = 5;
                    obj->position.x         = 0x2C2;
                    obj->position.y         = -0x301;
                    obj->position.z         = 0x7D0;
                    obj->type               = 0;
                    obj->u_E.b.work_2       = 0;
                    obj->rotation.y         = 0x800;
                    obj->position_fixed.v.x = obj->position.x << 16;
                    obj->position_fixed.v.y = obj->position.y << 16;
                    obj->position_fixed.v.z = obj->position.z << 16;
                    wp->child_24            = obj;
                }
                func_8001E6C0(0, 0, 0);
                cam->pos_10 = obj->position.x << 16;
                cam->pos_14 = (obj->position.y - 0x84) << 16;
                cam->pos_18 = (obj->position.z + 0x120) << 16;
                cam->rot_40 = 0x8000000;
                cam->rot_44 = 0;
                cam->rot_48 = 0xFFE00000;
                wp->routine_5++;
            }
            break;
        case 6:
            if (D_80098A72 == 0)
            {
                obj->u_E.b.work_2 = 8;
                obj->u_C.b.work_1 = 1;
                MojiTaskExec2(0, 0x6C);
                wp->routine_5++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                cam->pos_10 = 0x9300000;
                cam->pos_14 = 0xF8EB0000;
                cam->pos_18 = 0x6DB0000;
                cam->rot_40 = 0x6100000;
                cam->rot_44 = 0x1540000;
                cam->rot_48 = 0xFFE00000;
                for (i = 0; i < 2; i++)
                {
                    piece = Open_SHL_WORK();
                    if (piece != NULL)
                    {
                        piece->position.x         = 0x1DDF + i * 0x35C;
                        piece->be_flag            = MOVE;
                        piece->id                 = 0x29;
                        piece->position.y         = -0x301;
                        piece->position.z         = -0x3E8;
                        piece->rotation.y         = 0x400;
                        piece->value_44.half[0]   = 0x500;
                        piece->position_fixed.v.x = piece->position.x << 16;
                        piece->position_fixed.v.y = piece->position.y << 16;
                        piece->position_fixed.v.z = piece->position.z << 16;
                        (&wp->child_28)[i]        = piece;
                    }
                }
                obj->u_E.b.work_2 = 0;
                obj->u_C.b.work_1 = 1;
                Sound_call(0x18E, 1, 0);
                wp->routine_5++;
            }
            break;
        case 8:
            if (wp->child_28->position.x < 0xBB8)
            {
                cam->pos_10   = 0x2FA0000;
                cam->pos_14   = 0xFC720000;
                cam->pos_18   = 0x8C60000;
                cam->rot_40   = 0x8D00000;
                cam->rot_44   = 0x340000;
                cam->rot_48   = 0xFFE00000;
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                pl->pos_438.x   = obj->position.x - 0x64;
                pl->pos_438.y   = pl->position.y;
                pl->pos_438.z   = obj->position.z + 0x64;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->value_440   = 0;
                pl->value_442   = Angle_xz_svector(&pl->pos_438, &obj->position);
                pl->value_444   = 0;
                pl->value_448   = 0x30;
                Sound_call(0x18F, 1, 0);
                wp->child_24->rotation.y = 0;
                wp->routine_5++;
            }
            break;
        case 9:
            pos    = &obj->position;
            target = &wp->child_28->position;
            Muku(pos, target, obj->rotation.y, 0x40);
            if (obj->rotation.y < 0x200)
            {
                turn = Muku(pos, target, obj->rotation.y, 0x40);
                if (turn > 0)
                {
                    obj->rotation.y += turn;
                }
            }
            else
            {
                MojiTaskExec2(0, 0x6D);
                wp->routine_5++;
            }
            break;
        case 10:
            if (!(Moji_flag & 0x08000000))
            {
                wp->frame_10 = 0x10;
                wp->routine_5++;
            }
            break;
        case 11:
            if (wp->frame_10 != 0)
            {
                wp->frame_10--;
                cam->pos_10 += 880640.0;
                cam->pos_18 += -802816.0;
                cam->rot_40 += 3223552.0;
                cam->rot_44 += 0x20000;
            }
            turn = Muku(&obj->position, &pl->position, obj->rotation.y, 0x40);
            obj->rotation.y += turn;
            if (wp->frame_10 == 0 && turn == 0)
            {
                MojiTaskExec2(0, 0x6E);
                pl->value_448 = 0x32;
                wp->routine_5++;
            }
            break;
        case 12:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x6F);
                obj->u_E.b.work_2 = 8;
                obj->u_C.b.work_1 = 1;
                wp->routine_5++;
            }
            break;
        case 13:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x70);
                pl->value_448 = 0x32;
                wp->routine_5++;
            }
            break;
        case 14:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x71);
                obj->u_E.b.work_2 = 8;
                obj->u_C.b.work_1 = 1;
                wp->routine_5++;
            }
            break;
        case 15:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x72);
                pl->value_448 = 0x32;
                wp->routine_5++;
            }
            break;
        case 16:
            if (!(Moji_flag & 0x08000000))
            {
                pl->value_448 = 0xD;
                wp->frame_10  = 0x10;
                wp->routine_5++;
            }
            break;
        case 17:
            if (wp->frame_10 != 0)
            {
                wp->frame_10--;
                pl->value_442 += 0x80;
            }
            else
            {
                pl->value_448 = 1;
                wp->frame_10  = 0x1E;
                wp->routine_5++;
            }
            break;
        case 18:
            if (wp->frame_10 != 0)
            {
                wp->frame_10--;
                pl->flags_bd |= 0x10;
                pl->pos_438.x -= 0x14;
                pl->pos_438.z += 0x14;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0 && D_800C356C == 0 && D_80098A72 == 0 && wp->routine_4 == 1)
    {
        func_80053AA4(0);
        Cd_subcmd(0, 1, 0);
        wp->routine_5 = 0;
        wp->routine_4++;
    }
}

void func_80107418(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_80106A44(0x1A9, -0x301, 0x1940, 0x800);
            wp->routine_5++;
            break;
        case 1:
            if (D_800C356C_A[0] == 2)
            {
                if (D_8012BA00 != 0)
                {
                    func_80039E50();
                }
                D_800C356C_A[0]++;
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                wp->flags_0 = 0;
            }
            break;
    }
}

void func_801074F0(STAGE_ROOM *wp)
{
    D_801245F0[wp->routine_4](wp);
}

void func_8010752C(ST06_OBJ *wp)
{
    if (wp->value_10 == 0)
    {
        Sce_flag_off(wp->value_6 + 0x243);
        MojiTaskExec2(0, 0x49);
    }
    if (!(Moji_flag & 0x08000000))
    {
        Fade_start(9);
        wp->routine_2 = 0;
        Sce_event_next();
    }
}

void func_801075A0(ST06_OBJ *wp)
{
    if (D_80098A72 == 0)
    {
        Scene_obj_ent_open(&D_80124634[wp->value_6]);
        STAGE_PL.pos_438.x   = D_801245FC[wp->value_6].x;
        STAGE_PL.pos_438.y   = D_801245FC[wp->value_6].y;
        STAGE_PL.pos_438.z   = D_801245FC[wp->value_6].z;
        STAGE_PL.fixed_428.x = D_801245FC[wp->value_6].x << 16;
        STAGE_PL.fixed_428.y = D_801245FC[wp->value_6].y << 16;
        STAGE_PL.fixed_428.z = D_801245FC[wp->value_6].z << 16;
        STAGE_PL.value_442   = D_801245FC[wp->value_6].angle;
        wp->value_7          = 1;
        func_8001E6C0(0, 0, 0);
        D_800BC7F0 = D_801247D8[wp->value_6];
        Fade_start(1);
        Sce_event_next();
    }
}

void func_8010772C(STAGE_OBJ *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_2 = 1;
        Sce_event_next();
    }
}

void func_8010775C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        MojiTaskExec2(0, 0x4A);
        (&wp->child_24)[wp->routine_6]->u_E.b.work_2 = 8;
        (&wp->child_24)[wp->routine_6]->u_C.b.work_1 = 1;
    }
    if (wp->frame_10 == 0x3D)
    {
        Sce_event_next();
    }
}

void func_801077EC(STAGE_OBJ *wp)
{
    if (!(Moji_flag & 0x08000000) && (wp->value_10 >= 0xB6))
    {
        Sce_event_next();
    }
}

void func_80107834(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        if ((sint8)func_80107DB0() != -1)
        {
            MojiTaskExec2(0, 0x4B);
            (&wp->child_24)[wp->routine_6]->u_E.b.work_2 = 8;
            (&wp->child_24)[wp->routine_6]->u_C.b.work_1 = 1;
        }
        else
        {
            Fade_start(9);
            wp->reserved09[1] = 0;
            wp->routine_4     = 4;
        }
    }
    else if (!(Moji_flag & 0x08000000))
    {
        Fade_start(9);
        wp->reserved09[1] = 0;
        Sce_event_next();
    }
}

void func_80107908(STAGE_ROOM *wp)
{
    if (D_80098A72 == 0)
    {
        func_80031824((&wp->child_24)[wp->routine_6]);
        wp->routine_6 = func_80107DB0();
        Scene_obj_ent_open(&D_80124634[wp->routine_6]);
        STAGE_PL.pos_438.x   = D_801245FC[wp->routine_6].x;
        STAGE_PL.pos_438.y   = D_801245FC[wp->routine_6].y;
        STAGE_PL.pos_438.z   = D_801245FC[wp->routine_6].z;
        STAGE_PL.fixed_428.x = D_801245FC[wp->routine_6].x << 16;
        STAGE_PL.fixed_428.y = D_801245FC[wp->routine_6].y << 16;
        STAGE_PL.fixed_428.z = D_801245FC[wp->routine_6].z << 16;
        STAGE_PL.value_442   = D_801245FC[wp->routine_6].angle;
        Sce_event_timer_clear();
        func_8001E6C0(0, 0, 0);
        D_800BC7F0 = D_801247D8[wp->routine_6];
        Fade_start(1);
        wp->routine_4     = 3;
        wp->routine_8     = 1;
        wp->frame_10      = 0;
        wp->reserved09[0] = 0;
        wp->tbl_A4        = D_801247F4;
        Sce_flag_off(wp->routine_6 + 0x243);
    }
}

void func_80107AE8(void)
{
}

void func_80107AF0(STAGE_ROOM *wp)
{
    wp->tbl_A4        = D_801247E4;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->routine_7     = 0;
    wp->reserved09[1] = 0; // stored twice in retail
    Obj_work_flag_change(0x56, 5);
    wp->routine_6 = func_80107DB0();
    func_80107E08(wp);
}

void func_80107B54(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

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
