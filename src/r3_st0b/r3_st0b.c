#include "common.h"
#include "st0b.h"

// Installs the stage's slot routine tables.
void func_8010037C(void)
{
    STAGE_TABLE_3C0 = D_801190DC;
    STAGE_TABLE_5A4 = D_801191A8;
    STAGE_TABLE_10C = D_801191DC;
    STAGE_TABLE_48  = D_80119260;
    STAGE_TABLE_24  = D_801192C8;
    STAGE_TABLE_50  = D_801192FC;
}

// Sets up the current room: models, map, spawns.
void func_801003E4(void)
{
    STAGE_MAP_WORK *mw;
    sint32 room;
    void *spawns;

    mw = STAGE_MAP_WORK_PTR;
    Room_model_init(D_80119354[Game_work.value_51]);
    room                 = Game_work.value_51;
    mw->w                = STAGE_MAP_TBL[room].w;
    mw->h                = STAGE_MAP_TBL[room].h;
    mw->x0               = STAGE_MAP_TBL[room].x0;
    mw->z0               = STAGE_MAP_TBL[room].z0;
    mw->x1               = mw->x0 + mw->w;
    mw->z1               = mw->z0 + mw->h;
    mw->cells            = STAGE_MAP_TBL[room].cells;
    mw->info             = STAGE_CELL_INFO;
    STAGE_PL_BYTE(0x44E) = 1;
    if (STAGE_GAME.value_78)
    {
        STAGE_GAME.value_79 = 8;
        STAGE_GAME.value_7A = 0;
    }
    spawns    = D_80119554[room];
    mw->exits = D_801195EC[room];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_8011974C[D_80119774[Game_work.value_51]], D_8011960C[Game_work.value_51]);
    func_8005DC10(0);
    func_80100570();
}

void func_80100570(void)
{
    func_8001DEE4();
    D_800989FC = 0;
}

// Runs the current room's script.
void func_80100598(void)
{
    D_80119814[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_801005EC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x1C))
            {
                wp->routine_4 = 2;
            }
            else
            {
                wp->routine_4 = 1;
            }
            break;
        case 1:
            if (Sce_flag_test(0x1B))
            {
                func_8001DDE4(0x21);
                wp->routine_4 = 0xFF;
            }
            break;
        case 2:
            if (Sce_flag_test(0x1F))
            {
                func_8001DDE4(0x26);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_8010069C(STAGE_ROOM *wp)
{
    if ((wp->routine_5 == 0) && (Sce_flag_test(0x1D) != 0))
    {
        func_8001DDE4(0x23);
        wp->routine_5 = 0xFF;
    }
}

void func_801006F0(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x27))
            {
                Scene_obj_list_open(Sce_flag_test(0x54) ? &D_80119890 : D_80119898);
                wp->routine_4 = 0xFF;
            }
            else
            {
                Scene_obj_list_open(&D_80119890);
                if (Sce_flag_test(0x29))
                {
                    wp->routine_4 = 0xFF;
                }
                else
                {
                    wp->routine_4 = 1;
                }
            }
            break;
        case 1:
            if (Sce_flag_test(0x29))
            {
                func_8001DDE4(0x27);
                wp->routine_4 = 0xFF;
            }
            break;
        case 2: // idle: the switch needs it for retail's compare tree
            break;
    }
}

void func_801007BC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(&D_80119890);
        wp->routine_4 = 0xFF;
    }
}

void func_80100808(STAGE_ROOM *wp)
{
    D_801198A0[wp->routine_4](wp);
}

void func_80100844(STAGE_ROOM *wp)
{
    ST0B_PL *pl;
    STAGE_OBJ *child;

    pl = ST0B_PL_PTR;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x7E, 0x80);
            func_8001E6C0(0, 0, 0);
            wp->reserved09[1] = 0x80;
            // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
            *(uint32 *)&wp->timer_C = 0;
            D_800BC7F0              = D_80119960;
            wp->tbl_A4              = D_80119C9C;
            Scene_obj_ent_open(&D_801198AC[0]);
            child            = wp->child_24;
            child->routine_1 = 9;
            child->routine_2 = 0;
            func_80101070(0, 0);
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->flags_0 |= 1;
                pl->flags_BD |= 0x10;
                wp->routine_5++;
            }
            break;
        case 2:
            Fade_start(2);
            Cd_read_comb(0x7D);
            wp->routine_5++;
            break;
        case 3:
            if (D_80098A72 == 0 && Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x2000000D);
                func_8003187C(wp->child_24);
                Scene_obj_ent_open(&D_801198AC[0]);
                Scene_obj_ent_open(&D_801198AC[1]);
                Scene_obj_ent_open(&D_801198AC[2]);
                wp->routine_5++;
            }
            break;
        case 4:
            if (func_8001D878() != 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_801199B0;
                wp->tbl_A4    = D_80119CAC;
                wp->routine_5 = 0;
                wp->reserved09[1] &= 1;
                wp->routine_4++;
            }
            break;
    }
    func_80101110(D_80119D04, D_80119D04, D_80119D04, 2);
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80100A64(STAGE_ROOM_WORK *wp)
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

void func_80100AF8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (D_80098A72 == 0)
    {
        switch (wp->routine_5)
        {
            case 0:
                Cd_subcmd(0, 1, 0);
                Obj_work_flag_change(0x7E, 0x80);
                Cd_read_comb(0x7E);
                wp->routine_5++;
                break;
            case 1:
                if (Cd_read_sync2() == 0)
                {
                    func_8003697C();
                    wp->routine_5++;
                }
                break;
            case 2:
                D_800A395C = 1;
                func_80039820();
                pl = &Player_work;
                func_80042314(pl);
                STAGE_PL.value_76 = 0;
                pl->flags_0 |= 3;
                wp->routine_5++;
                break;
            case 3:
                func_80101070(1, 2);
                wp->flags_0 = 0;
                break;
        }
    }
    if (wp->reserved09[1] != 0)
    {
        Sce_camera_update();
        Sce_event_update();
    }
}

void func_80100C34(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (D_80119D04 != 0)
    {
        func_80101110(D_80119D04, D_80119D04, D_80119D04, 2);
        D_80119D04--;
    }
    if (wp->frame_10 == 0x64)
    {
        child               = wp->child_24;
        child->u_C.b.byte_D = 0;
    }
}

void func_80100CAC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 0:
            child               = wp->child_24;
            child->routine_1    = 2;
            child->routine_2    = 0;
            child->u_C.b.byte_D = 0;
            break;
        case 40:
            wp->child_28->u_C.b.byte_D = 0;
            break;
        case 50:
            wp->child_2C->u_C.b.byte_D = 0;
            break;
    }
}

void func_80100D10(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_24);
        func_8003187C(wp->child_28);
        func_80031824(wp->child_2C);
        func_80101070(0, 2);
    }
}

void func_80100D74(STAGE_ROOM *wp)
{
    STAGE_FX *fx;

    if (wp->frame_10 == 0x1E)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->x_1C    = -0x1068;
            fx->y_1E    = -0x1CF;
            fx->timer_D = 0;
            fx->z_20    = -0x15EF;
        }
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->x_1C    = -0x1068;
            fx->y_1E    = -0x1CF;
            fx->timer_D = 0;
            fx->z_20    = -0x1630;
        }
    }
}

void func_80100E2C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        Scene_obj_ent_open(&D_801198FC[0]);
        Scene_obj_ent_open(&D_801198FC[1]);
        Scene_obj_ent_open(&D_801198FC[2]);
        Scene_obj_ent_open(&D_801198FC[3]);
        Scene_obj_ent_open(&D_801198FC[4]);
    }
}

void func_80100E8C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *obj;

    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_28);
        func_80031824(wp->child_2C);
        func_80031824(wp->child_30);
        func_80031824(wp->child_34);
        func_80031824(wp->child_38);
        func_80101070(0, 0);
        wp->routine_6 = 0;
    }
    if (wp->routine_6 == 0)
    {
        Scene_obj_ent_open(&D_801198AC[0]);
        child            = wp->child_24;
        child->routine_1 = 3;
        child->routine_2 = 0;
        Scene_obj_ent_open(&D_801198AC[1]);
        child            = wp->child_28;
        child->routine_1 = 2;
        child->routine_2 = 0;
        Scene_obj_ent_open(&D_801198AC[2]);
        obj            = wp->child_2C;
        obj->routine_1 = 0;
        obj->routine_2 = 0;
        wp->routine_6++;
    }
}

void func_80100F84(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0xA)
    {
        child               = wp->child_28;
        child->u_C.b.byte_D = 0;
    }
}

void func_80100FA8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 5;
        child->routine_2 = 0;
        child            = wp->child_28;
        child->routine_1 = 4;
    }
}

void func_80100FDC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 0:
            child            = wp->child_24;
            child->routine_1 = 6;
            child->routine_2 = 0;
            break;
        case 0x50:
            child            = wp->child_24;
            child->routine_1 = 7;
            child->routine_2 = 0;
            break;
        case 0x104:
            child            = wp->child_24;
            child->routine_1 = 8;
            child->routine_2 = 0;
            break;
    }
}

void func_80101048(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
}

void func_80101070(sint32 arg0, uint8 arg1)
{
    D_800C356C = -1;
    D_800C356E = 0xB;
    D_800C356F = arg1;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    if (arg0 != 0)
    {
        D_800C3560 = 0xA00;
        D_800C3562 = -0x262;
        D_800C3564 = -0x2000;
        D_800C356A = 0x600;
        return;
    }
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
}

// Draws a translucent full-screen rectangle (abr: the blend mode).
void func_80101110(uint8 r, uint8 g, uint8 b, uint16 abr)
{
    ST0B_TILE *tile;
    DR_MODE *mode;

    tile = (ST0B_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->g0   = g;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->r0   = r;
    tile->b0   = b;
    tile->code |= 2;
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(mode, 0, 0, (abr << 5) | 0xF, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
}
