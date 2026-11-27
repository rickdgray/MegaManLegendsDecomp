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
                pl->be_flag |= MOVE;
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
                pl->be_flag |= MOVE | TRANS;
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
        child->u_C.b.work_1 = 0;
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
            child->u_C.b.work_1 = 0;
            break;
        case 40:
            wp->child_28->u_C.b.work_1 = 0;
            break;
        case 50:
            wp->child_2C->u_C.b.work_1 = 0;
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
            fx->be_flag = MOVE;
            fx->id      = 5;
            fx->work_0  = 5;
            fx->frame_E = 2;
            fx->x_1C    = -0x1068;
            fx->y_1E    = -0x1CF;
            fx->timer_D = 0;
            fx->z_20    = -0x15EF;
        }
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->be_flag = MOVE;
            fx->id      = 5;
            fx->work_0  = 5;
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
        child->u_C.b.work_1 = 0;
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

void func_80101234(STAGE_ROOM *wp)
{
    D_80119D08[wp->routine_4](wp);
}

void func_80101270(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = ST0B_PL_PTR;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x7E, 0x80);
            func_8001E6C0(0, 0, 0);
            wp->reserved09[1] = 0x80;
            // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
            *(uint32 *)&wp->timer_C = 0;
            D_800BC7F0              = D_80119DDC;
            wp->tbl_A4              = D_8011A238;
            func_80101E2C(4);
            Cd_read_comb(0x7F);
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->be_flag &= ~(MOVE | TRANS);
                pl->flags_BD |= 0x10;
                wp->routine_5++;
            }
            break;
        case 2:
            pl->routine_1++;
            wp->routine_5++;
            break;
        case 3:
            if (Cd_read_sync2() == 0)
            {
                Scene_obj_ent_open(&D_80119D14[0]);
                Scene_obj_ent_open(&D_80119D14[1]);
                Scene_obj_ent_open(&D_80119D14[2]);
                Cd_xa_play_id(0x2000000C);
                wp->routine_5++;
            }
            break;
        case 4:
            if (func_8001D878() != 0)
            {
                Fade_start(2);
                Sce_event_timer_clear();
                D_800BC7F0 = D_80119E2C;
                wp->tbl_A4 = D_8011A248;
                wp->routine_5++;
            }
            break;
        case 5:
            if (D_80098A72 == 0)
            {
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->reserved09[1] &= 1;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80101480(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        Fade_start(0xA);
        wp->routine_4++;
        wp->routine_5 = 0;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if ((wp->routine_8 != 2 && func_8001DE84() != 0) || wp->reserved09[1] == 1)
        {
            Fade_start(8);
            wp->routine_4++;
            wp->routine_5 = 0;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

// registers: retail keeps the constant 2 of the camera stores in a0 (the call's first argument) and loads &Player_work into a1 before them
void func_80101524(STAGE_ROOM_WORK *wp)
{
    if (D_80098A72 == 0)
    {
        switch (wp->routine_5)
        {
            case 0:
                Cd_subcmd(0, 1, 0);
                Obj_work_flag_change(0x7E, 0x80);
                wp->routine_5++;
                break;
            case 1:
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_80042314(&Player_work);
                wp->routine_5++;
                break;
            case 2:
                D_800C356C          = 2;
                D_800C356F          = 2;
                D_800C356E          = 0xB;
                D_800C3560          = -0x200;
                D_800C3562          = -0x101;
                D_800C3564          = -0x300;
                D_800C356A          = 0x800;
                D_800C356D          = 0;
                D_800C3571          = 0xFF;
                D_800C3570          = 2;
                STAGE_PL.value_76   = 0;
                STAGE_GAME.value_83 = 0;
                Player_work.be_flag |= MOVE | TRANS;
                func_8001D974();
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

void func_801016A4(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0x1E:
            wp->child_24->u_C.b.work_1 = 0;
            wp->child_28->u_C.b.work_1 = 0;
            wp->child_3C->u_C.b.work_1 = 0;
            wp->routine_6++;
            break;
        case 0x23:
        case 0x3A:
        case 0x3E:
            wp->routine_7++;
            break;
        case 0x37:
        case 0x3B:
        case 0x3F:
            wp->routine_7 = 0;
            break;
    }
    if (wp->routine_6 != 0)
    {
        D_800BC7D4[0] = D_8011A2C0[STAGE_FRAME & 3] << 16;
    }
    if (wp->routine_7 != 0)
    {
        func_80101E90(0x80, 0x80, 0x80, 2);
    }
}

void func_8010179C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 0:
            wp->routine_6       = 0;
            D_800BC7D4[0]       = 0;
            child               = wp->child_24;
            child->routine_1    = 2;
            child->routine_2    = 0;
            child->u_C.b.work_1 = 0;
            break;
        case 0xB4:
            wp->routine_6++;
            break;
        case 0xFA:
            wp->routine_6 = 0;
            D_800BC7D4[0] = 0;
            break;
    }
    if (wp->routine_6 != 0)
    {
        D_800BC7D4[0] = D_8011A2C8[STAGE_FRAME & 3] << 16;
    }
}

void func_80101864(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 2;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80101890(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_3C;
        child->routine_1    = 2;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_801018BC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_24;
        child->routine_1    = 3;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_801018E8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_24;
        child->routine_1    = 4;
        child->routine_2    = 0;
        child->u_C.b.work_1 = 0;
    }
}

void func_80101914(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_24);
        func_8003187C(wp->child_28);
        func_80031824(wp->child_3C);
        Scene_obj_ent_open(&D_80119D14[3]);
        wp->child_24->routine_1 = 2;
        func_80101E2C(5);
    }
    if (wp->frame_10 == 0x46)
    {
        Fade_start(0xE);
    }
    func_80101FB4(wp);
}

void func_801019B0(STAGE_ROOM *wp)
{
    sint32 i;

    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Cd_subcmd(0, 1, 0);
                func_8003187C(wp->child_24);
                Obj_work_flag_change(0x7E, 0x80);
                wp->reserved09[1] = 0x80;
                Fade_start(7);
                Cd_read_comb(0x80);
                wp->routine_5++;
            }
            break;
        case 1:
            if (Cd_read_sync2() == 0 && D_80098A72 == 0)
            {
                Cd_xa_play_id(0x20000010);
                wp->frame_10 = 0;
                wp->routine_5++;
            }
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                if (wp->frame_10 == 0x14)
                {
                    for (i = 0; i < 4; i++)
                    {
                        Scene_obj_ent_open(&D_80119D64[i]);
                    }
                    Scene_obj_ent_open(&D_80119D3C[0]);
                    Scene_obj_ent_open(&D_80119D3C[7]);
                    wp->reserved09[1] &= 1;
                    wp->routine_5++;
                }
            }
            else
            {
                wp->frame_10 = 0;
            }
            break;
        case 3:
            if (wp->frame_10 == 500)
            {
                wp->routine_5 = 0;
                Sce_event_next();
                for (i = 0; i < 4; i++)
                {
                    func_80031824((&wp->child_24)[i]);
                }
                func_80031824(wp->child_3C);
                Close_SHL_WORK(wp->child_38);
                Scene_obj_ent_open(D_80119D14);
                func_80101E2C(1);
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
}

void func_80101BD0(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0x96:
            wp->child_24->u_C.b.work_1 = 0;
            break;
        case 0xB4:
            Scene_obj_ent_open(D_80119D28);
            break;
    }
}

void func_80101C24(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_24;
        child->u_C.b.work_1++;
    }
}

void func_80101C54(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_24);
        func_8003187C(wp->child_28);
        Scene_obj_ent_open(&D_80119D14[4]);
        Scene_obj_ent_open(&D_80119D14[2]);
        Scene_obj_ent_open(&D_80119D14[9]);
        func_80101E2C(5);
    }
}

void func_80101CC8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_3C);
        Close_SHL_WORK(wp->child_38);
        func_80031824(wp->child_24);
        Scene_obj_ent_open(&D_80119D14[0]);
        Scene_obj_ent_open(&D_80119D14[1]);
        func_80101E2C(1);
    }
}

void func_80101D40(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 7;
        child            = wp->child_24;
        child->u_C.b.work_1++;
    }
    if (wp->frame_10 == 0x1E)
    {
        other               = wp->child_28;
        other->u_C.b.work_1 = 0;
    }
}

void func_80101D98(STAGE_ROOM *wp)
{
    sint32 i;

    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_24);
        func_8003187C(wp->child_28);
        Scene_obj_ent_open(&D_80119D14[2]);
        Scene_obj_ent_open(&D_80119D14[9]);
        for (i = 0; i < 5; i++)
        {
            Scene_obj_ent_open(&D_80119D14[4 + i]);
        }
        func_80101E2C(5);
    }
}

void func_80101E2C(uint8 arg0)
{
    D_800C356E = 0xB;
    D_800C356C = -1;
    D_800C356F = arg0;
    D_800C356D = 0;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

// Draws a translucent full-screen rectangle (abr: the blend mode).
void func_80101E90(uint8 r, uint8 g, uint8 b, uint16 abr)
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

void func_80101FB4(STAGE_ROOM *wp)
{
    ST0B_DUST *ep;
    STCOM_SVECTOR pos[8] = {{-0xB8, -0x64, -0x1F4, 0}, {0x64, -0x2BC, 0xC8, 0},   {0xDC, -0x78, -0xA, 0},     {-0xB4, -0xC8, 0xFA, 0},
                            {0x82, -0x96, -0x12C, 0},  {-0xDC, -0x1A4, -0xDC, 0}, {-0xC8, -0x190, -0x12C, 0}, {-0x29, -0x320, 0x78, 0}};

    switch (wp->frame_10)
    {
        case 0x14:
        case 0x1C:
        case 0x24:
        case 0x28:
        case 0x30:
        case 0x38:
        case 0x3C:
        case 0x44:
        case 0x4C:
            ep = (ST0B_DUST *)func_80031618();
            if (ep != NULL)
            {
                ep->be_flag  = MOVE | MODEL;
                ep->id       = 0x80;
                ep->type     = 0x41;
                ep->value_4  = 0;
                ep->value_C  = 0;
                ep->value_D  = 3;
                ep->pos_38.x = D_8011A2D0[wp->frame_10 / 20 - 1].x + (rand() & 0x1F);
                ep->pos_38.y = D_8011A2D0[wp->frame_10 / 20 - 1].y + (rand() & 0x1F);
                ep->pos_38.z = D_8011A2D0[wp->frame_10 / 20 - 1].z - 0x1F;
            }
            // fall through
        case 0xA:
        case 0x1E:
        case 0x34:
        case 0x46:
        case 0x50:
        case 0x58:
            ep = (ST0B_DUST *)func_80031618();
            if (ep != NULL)
            {
                ep->be_flag  = MOVE | MODEL;
                ep->id       = 0x80;
                ep->value_4  = 0;
                ep->type     = 0x40;
                ep->value_C  = 0;
                ep->value_D  = 0;
                ep->pos_38.x = pos[rand() & 7].x;
                ep->pos_38.y = pos[rand() & 7].y;
                ep->pos_38.z = pos[rand() & 7].z;
            }
            break;
    }
}

void func_80102234(STAGE_ROOM *wp)
{
    D_8011A2E8[wp->routine_4](wp);
}

void func_80102270(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                pl->be_flag &= ~TRANS;
                wp->routine_5++;
                D_8012034C = 0x190;
            }
            break;
        case 1:
            Obj_work_flag_change(0x56, 0x80);
            obj = Scene_obj_ent_open(D_8011A2F8);
            obj->flags &= ~0x20;
            Cd_xa_play_id(0x20010008);
            wp->routine_5++;
            break;
        case 2:
            func_8001E6C0(0, 0, 0);
            // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
            *(uint32 *)&wp->timer_C = 0;
            D_800BC7F0              = D_8011A3C4;
            wp->tbl_A4              = D_8011A410;
            Fade_start(2);
            Sce_camera_update();
            Sce_event_update();
            wp->routine_5++;
            // fall through
        case 3:
            Sce_camera_update();
            Sce_event_update();
            if (D_80098A72 == 0)
            {
                D_800BC7F0    = D_8011A30C;
                wp->tbl_A4    = D_8011A394;
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->routine_4++;
            }
            break;
    }
}

void func_80102430(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84() != 0 && !(wp->reserved09[1] & 0x80))
        {
            wp->reserved09[1] |= 1;
            Fade_start(0xA);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    else
    {
        wp->routine_5 = 0;
        wp->routine_4 += 2;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_801024DC(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (D_80098A72 == 0)
    {
        wp->routine_4++;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_8010255C(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            wp->routine_5++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x56, 0x80);
                if (wp->reserved09[1] & 1)
                {
                    func_8003697C();
                }
                Sce_event_next();
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                Cd_subcmd(0, 1, 0);
                wp->routine_5++;
            }
            break;
        case 2:
            D_800C356C        = 2;
            D_800C356E        = 0xD;
            D_800C3560        = 0x708;
            D_800C3562        = -0x81;
            D_800C356F        = 0;
            D_800C3564        = -0x28;
            D_800C356A        = 0;
            D_800C356D        = 0;
            D_800C3571        = 0xFF;
            D_800C3570        = 2;
            STAGE_PL.value_76 = 0;
            Player_work.be_flag |= MOVE | TRANS;
            STAGE_GAME.value_83 = 0;
            Sce_flag_off(0x1F);
            wp->flags_0 = 0;
            break;
    }
}

void func_801026E4(void)
{
    Sce_event_next();
}

void func_80102704(STAGE_ROOM *wp)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR move;
    STAGE_OBJ *obj;

    obj = wp->child_24;
    switch (wp->routine_6)
    {
        case 0:
            if (D_8012034C > 0xC8)
            {
                D_8012034C -= 8;
            }
            else if (wp->frame_10 >= 0x74)
            {
                wp->routine_6++;
            }
            break;
        case 1:
            if (D_8012034C < 0x3C0)
            {
                D_8012034C += 0x10;
            }
            break;
    }
    func_80030058(&fixed, obj->rotation.y, D_8012034C, 0, 0);
    func_80030150(&fixed, &move);
    obj->position.x += move.x;
    obj->position.z += move.z;
}

void func_801027F4(STAGE_ROOM *wp)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR move;
    STAGE_OBJ *obj;

    obj = wp->child_24;
    switch (wp->routine_6)
    {
        case 0:
        case 1:
            wp->routine_6++;
            break;
        case 2:
            Fade_start(0xA);
            wp->routine_6++;
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                Sce_event_next();
            }
            break;
    }
    func_80030058(&fixed, obj->rotation.y, D_8012034C, 0, 0);
    func_80030150(&fixed, &move);
    obj->position.x += move.x;
    obj->position.z += move.z;
}

void func_801028E8(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011A420[wp->routine_1](wp);
    if (wp->u_C.b.work_1 == 0)
    {
        func_80032488(wp);
    }
    func_80102DD8(wp, face);
}

void func_8010295C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    wp->be_flag |= TRANS;
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    Model_work_init(wp, &wp->type);
    switch (Scene_work.u_8.byte[0])
    {
        case 0:
            func_800322A8(wp, 8, 0);
            func_80102D90(wp, face, 3);
            wp->routine_1 = 1;
            break;
        case 3:
            func_800322A8(wp, 0xA, 0);
            func_80102D90(wp, face, 4);
            wp->position.x = 0x104;
            wp->position.y = 0x14;
            wp->position.z = 0xD2;
            wp->routine_1  = 3;
            break;
        case 5:
            func_800322A8(wp, 0xB, 0);
            func_80102D90(wp, face, 7);
            wp->position.x = 0x104;
            wp->position.y = 0x14;
            wp->position.z = 0xD2;
            wp->routine_1  = 4;
            break;
    }
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
}

void func_80102AA8(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        func_80102D90(wp, face, 3);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x1E)
    {
        func_80102D90(wp, face, 0);
    }
}

void func_80102B30(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 9, 0);
        func_80102D90(wp, face, 1);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0x19)
    {
        func_80102D90(wp, face, 2);
    }
    if (STAGE_SCENE_PTR->value_10 == 0x91)
    {
        func_80102D90(wp, face, 5);
    }
}

void func_80102BDC(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xA, 0);
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 1:
            func_80102D90(wp, face, 4);
            wp->u_C.b.work_1 = 0;
            break;
        case 0x55:
            func_80102D90(wp, face, 4);
            break;
        case 0x48:
        case 0xAA:
            func_80102D90(wp, face, 6);
            break;
    }
}

void func_80102CB4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xB, 0);
        func_80102D90(wp, face, 7);
        wp->routine_2++;
    }
    if (STAGE_SCENE_BYTE(9) == 1)
    {
        switch (Scene_work.value_10)
        {
            case 0x20:
                func_80102D90(wp, face, 8);
                break;
            case 0x12C:
            case 0x15E:
                func_80102D90(wp, face, 9);
                break;
        }
    }
}

void func_80102D90(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011A520[index];
    face->eyes_10               = D_8011A548[index];
}

void func_80102DD8(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_0, 0x33, 0x37, 5));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_6, 0x33, 0x37, 5));
    }
    face->prev_8 = face->shape_6;
}

void func_80102F24(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011A570[wp->routine_1](wp);
    if (wp->u_C.b.work_1 == 0)
    {
        func_80032488(wp);
    }
    func_80103410(wp, face);
}

void func_80102F98(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    func_801033C8(wp, &wp->u_4E0.face, 0);
    wp->routine_1 = 1;
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
}

void func_80103020(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0x28:
            func_801033C8(wp, face, 1);
            break;
        case 0x41:
            func_801033C8(wp, face, 0);
            break;
    }
}

void func_801030BC(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 2, 0);
    func_801033C8(wp, &wp->u_4E0.face, 0xB);
    wp->routine_1 = 3;
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
}

void func_80103144(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        func_801033C8(wp, face, 2);
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0xA:
        case 0x2D:
        case 0x96:
            func_801033C8(wp, face, 3);
            break;
        case 0x1E:
        case 0x87:
        case 0xC0:
            func_801033C8(wp, face, 0xB);
            break;
    }
}

void func_80103238(void)
{
}

void func_80103240(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        func_801033C8(wp, face, 5);
        wp->u_C.b.work_1 = 0;
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0x64:
            func_801033C8(wp, face, 6);
            break;
        case 0x50:
        case 0x91:
            func_801033C8(wp, face, 7);
            break;
        case 0x9B:
        case 0xD2:
            func_801033C8(wp, face, 0xC);
            break;
        case 0xB4:
        case 0x11D:
            func_801033C8(wp, face, 5);
            break;
        case 0x12C:
            func_801033C8(wp, face, 8);
            break;
        case 0x140:
            func_801033C8(wp, face, 0xD);
            break;
        case 0x16D:
            func_801033C8(wp, face, 0xE);
            break;
        case 0x190:
            func_801033C8(wp, face, 0xA);
            break;
    }
}

void func_801033C8(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011A6E4[index];
    face->eyes_10               = D_8011A720[index];
}

void func_80103410(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_0, 0x33, 0x37, 5));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_6, 0x33, 0x37, 5));
    }
    face->prev_8 = face->shape_6;
}

void func_8010355C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011A75C[wp->routine_1](wp);
    if (wp->u_C.b.work_1 == 0)
    {
        func_80032488(wp);
    }
    func_80103C10(wp, face);
}

void func_801035D0(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    face = &wp->u_4E0.face16;
    switch (Scene_work.u_8.byte[0])
    {
        case 0:
            func_800322A8(wp, 8, 0);
            func_80103BC8(wp, face, 1);
            wp->routine_1 = 1;
            break;
        case 3:
            func_800322A8(wp, 0xC, 0);
            func_80103BC8(wp, face, 6);
            wp->position.x = 0xFF;
            wp->position.y = 0;
            wp->position.z = 0x190;
            func_80032488(wp);
            wp->routine_1 = 5;
            break;
        case 5:
            func_800322A8(wp, 0xD, 0);
            func_80103BC8(wp, face, 8);
            wp->position.x = 0xFF;
            wp->position.y = 0;
            wp->position.z = 0x190;
            func_80032488(wp);
            wp->routine_1 = 6;
            break;
    }
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
}

void func_80103724(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        func_80103BC8(wp, face, 1);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x1E)
    {
        func_80103BC8(wp, face, 0);
    }
}

void func_801037AC(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 9, 0);
        func_80103BC8(wp, face, 1);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0xA)
    {
        func_80103BC8(wp, face, 2);
    }
    if (STAGE_SCENE_PTR->value_10 == 0x23)
    {
        func_80103BC8(wp, face, 1);
    }
}

void func_80103858(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xA, 0);
        func_80103BC8(wp, face, 3);
        wp->routine_2++;
    }
}

void func_801038C0(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xB, 0);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 == 7)
    {
        func_80103BC8(wp, face, 4);
    }
    if (STAGE_SCENE_PTR->value_10 == 0x4B)
    {
        func_80103BC8(wp, face, 5);
    }
}

void func_8010395C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xC, 0);
        func_80103BC8(wp, face, 6);
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 5:
        case 0x8C:
            func_80103BC8(wp, face, 7);
            break;
        case 0x80:
            func_80103BC8(wp, face, 6);
            break;
    }
}

void func_80103A1C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xD, 0);
        func_80103BC8(wp, face, 8);
        wp->routine_2++;
    }
    if (Scene_work.u_8.byte[1] == 0)
    {
        switch (Scene_work.value_10)
        {
            case 0x14:
            case 0x46:
                func_80103BC8(wp, face, 0xB);
                break;
            case 0x32:
                func_80103BC8(wp, face, 8);
                wp->u_C.b.work_1 = 0;
                break;
            case 0x50:
                func_80103BC8(wp, face, 9);
                break;
            case 0x10E:
                func_80103BC8(wp, face, 9);
                wp->u_C.b.work_1 = 0;
                break;
            case 0x39:
            case 0x11D:
                wp->u_C.b.work_1++;
                break;
            case 0xF0:
            case 0x172:
                func_80103BC8(wp, face, 0xC);
                break;
            case 0x190:
                func_80103BC8(wp, face, 0xA);
                wp->u_C.b.work_1 = 0;
                break;
        }
    }
}

void func_80103BC0(void)
{
}

void func_80103BC8(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011A8D0[index];
    face->eyes_10               = D_8011A904[index];
}

void func_80103C10(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_0, 0x2A, 0x40, 6));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_6, 0x2A, 0x40, 6));
    }
    face->prev_8 = face->shape_6;
}

void func_80103D5C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011A938[wp->routine_1](wp);
    if (wp->u_C.b.work_1 == 0)
    {
        func_80032488(wp);
    }
    if (STAGE_SCENE_BYTE(7) == 0)
    {
        func_8010444C(wp, face);
    }
}

void func_80103DE0(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    func_80104404(wp, &wp->u_4E0.face, 0);
    wp->routine_1 = 1;
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
}

void func_80103E68(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        func_80104404(wp, face, 0);
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0x50:
        case 0xAA:
            func_80104404(wp, face, 1);
            break;
        case 0x96:
        case 0x104:
            func_80104404(wp, face, 2);
            break;
    }
}

void func_80103F3C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        func_80104404(wp, face, 3);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x28)
    {
        func_80104404(wp, face, 2);
    }
}

void func_80103FC4(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 3, 0);
    wp->routine_1 = 4;
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
}

void func_8010403C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        func_80104404(wp, face, 4);
        wp->u_C.b.work_1 = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x14:
            func_80104404(wp, face, 5);
            break;
        case 0xC3:
            func_80104404(wp, face, 4);
            break;
    }
}

void func_801040E8(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        func_80104404(wp, face, 7);
        wp->u_C.b.work_1 = 0;
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0x19:
        case 0xAA:
            func_80104404(wp, face, 6);
            break;
        case 0x28:
            func_80104404(wp, face, 7);
            break;
    }
}

void func_801041A8(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        func_80104404(wp, face, 8);
        wp->u_C.b.work_1 = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0xA:
            func_80104404(wp, face, 9);
            break;
        case 0x4B:
            func_80104404(wp, face, 10);
            break;
    }
}

void func_80104254(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        func_80104404(wp, face, 9);
        wp->u_C.b.work_1 = 0;
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0xDC)
    {
        func_80104404(wp, face, 0xA);
    }
}

void func_801042DC(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        func_80104404(wp, face, 9);
        wp->u_C.b.work_1 = 0;
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x127)
    {
        func_80104404(wp, face, 0xB);
    }
}

void func_80104364(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->be_flag |= TRANS;
        func_8002F9EC(wp, 0);
        func_800322A8(wp, 0, 0);
        func_80104404(wp, face, 0);
        wp->u_C.b.work_1++;
        wp->routine_2++;
    }
}

void func_80104404(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011AA90[index];
    face->eyes_10               = D_8011AAC0[index];
}

void func_8010444C(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_0, 0x2A, 0x40, 6));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_6, 0x2A, 0x40, 6));
    }
    face->prev_8 = face->shape_6;
}

void func_80104598(ST0B_OBJ *wp)
{
    D_8011AAF8[wp->routine_0](wp);
    wp->value_464 = 0;
    wp->value_418 = 0;
    wp->value_398 = 0;
    wp->value_3AC = 0;
    wp->value_3F0 = 0;
    wp->value_404 = 0;
}

void func_801045F8(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    STAGE_OBJ *child;
    sint32 i;
    sint16 life;

    ctl = (ST0B_CTL *)&wp->value_380;
    wp->be_flag |= TRANS;
    wp->flags |= 0x20;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2800280;
    wp->scale.words[1] = 0x280;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 9; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    wp->rotation.x           = 0;
    wp->rotation.z           = 0;
    wp->value_64             = 0;
    wp->value_44.value       = 0;
    wp->value_48.value       = 0;
    wp->u_C.b.work_1         = 0;
    ctl->flags_0             = 0x467C;
    ctl->msg_D8              = 0;
    *(uint32 *)&ctl->index_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    Track_reset(ctl->track_38, 0, -0x60);
    ctl->timer_C               = 0;
    ctl->slot_60               = func_80036294(wp->u_C.b.work_0);
    ctl->index_E               = 0;
    *(uint32 *)&ctl->act_A4[0] = 0;
    *(uint32 *)&ctl->act_A4[1] = 0;
    ctl->toggle_F              = 0;
    *(uint32 *)&ctl->act_A4[2] = 0;
    ctl->time_64               = 0;
    ctl->wave_CC               = 0;
    ctl->value_E4              = 0;
    ctl->value_E8              = 0;
    ctl->hit_90.hit_8          = 0;
    ctl->hit_90.value_C        = 0;
    ctl->hit_90.size_10 = ctl->hit_90.size_12 = wp->value_B0;
    ctl->count_DC                             = 0;
    ctl->data_E0                              = D_8011AAF0;
    for (i = 0; i < 2; i++)
    {
        ctl->hit_10[i].hit_8   = 0;
        ctl->hit_10[i].value_C = 0;
        ctl->hit_68[i].hit_8   = 0;
        ctl->hit_68[i].value_C = 0;
        ctl->hit_10[i].size_10 = ctl->hit_10[i].size_12 = D_8009884C[wp->id]->size_A << 5;
        ctl->hit_68[i].size_10 = ctl->hit_68[i].size_12 = D_8009884C[wp->id]->size_B << 5;
    }
    life         = D_8009884C[wp->id]->life_8 << 5;
    wp->value_78 = (sint32)D_8011AB48;
    wp->value_10 = 0;
    wp->value_B2 = wp->value_B0 = wp->value_6E = life;
    switch (wp->type)
    {
        case 0:
            wp->routine_0             = 3;
            wp->routine_1             = 1;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            wp->u_E.b.work_2 = 0;
            ctl->base_DA     = -1;
            break;
        case 1:
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, wp->anim_AC, wp->reservedA4[0]);
            ctl->base_DA = -1;
            ctl->flags_0 |= 0x2000;
            break;
    }
    child = func_80031418();
    if (child != NULL)
    {
        ctl->child_D0         = child;
        child->be_flag        = MOVE;
        child->id             = 0x31;
        child->value_4        = 0;
        child->type           = 0;
        child->position       = wp->position;
        child->position_fixed = wp->position_fixed;
        child->rotation       = wp->rotation;
        child->u_C.b.work_0   = wp->work_id;
    }
    else
    {
        func_8003187C(wp);
    }
    func_801048FC(wp);
}

// Register only: retail loads routine_1 into v1 for the 0/2 toggle (li v0,2 in the delay slot); here v0 (score 2).
void func_801048FC(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *child;
    sint32 i;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    ctl                     = (ST0B_CTL *)&wp->value_380;
    pl                      = &STAGE_PL;
    if (wp->value_380 & 0x4000)
    {
        for (i = 0; i < 9; i++)
        {
            wp->pal[i].color = 0x4210;
        }
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    ctl->child_D0->scale.v.pad = 0x4210;
    ctl->rand_2                = rand();
    func_8005D4C0();
    if (ctl->flags_0 & 0x40)
    {
        func_80106550(wp);
    }
    if ((ctl->flags_0 & 0x1000) && func_80031EF0(&wp->position, wp->rotation.y, 0x20, &pl->position, pl->rotation.y, 0x800) != 0)
    {
        ctl->flags_0 = (ctl->flags_0 & ~0x1000) | 2;
    }
    wp->rotation.y         = (wp->rotation.y - 2) & 0xFFF;
    wp->position.y         = (D_800BBCF8[ctl->wave_CC++] >> 8) - 1;
    wp->position_fixed.v.y = wp->position.y << 16;
    ctl->wave_CC &= 0x3F;
    D_8011AB08[wp->routine_1](wp);
    for (i = 0; i < 2; i++)
    {
        ctl->index_E = i;
        if (ctl->flags_0 & (0x10 << i))
        {
            D_8011AB30[ctl->act_A4[i].index_0](wp);
        }
    }
    if (ctl->flags_0 & 2)
    {
        D_8011AB40[ctl->act_A4[3].index_0](wp);
    }
    if (ctl->flags_0 & 0x400)
    {
        D_8011AB38[ctl->act_A4[2].index_0](wp);
    }
    if (ctl->flags_0 & 1)
    {
        // Toggle between states 0 and 2; case 2 has its own body in retail's compare chain.
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1 = 2;
                break;
            case 2:
                wp->routine_1 = 0;
                break;
            default:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_C != 0)
    {
        ctl->timer_C--;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->flags_0 & 0x200)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        ST0B_SP_160->value_A = ctl->act_A4[0].angle_4;
        ST0B_SP_160->value_2 = ctl->act_A4[1].angle_4;
        Model_parts_mtx_set_y(wp);
    }
    else
    {
        Model_pose_unpack(wp);
        Model_parts_mtx_set_y(wp);
    }
    func_80051B68(wp, 1, 0, 0);
    if (wp->be_flag & MOVE)
    {
        if (ctl->flags_0 & 2)
        {
            ctl->child_D0->be_flag |= TRANS;
            ctl->child_D0->position       = wp->position;
            ctl->child_D0->position_fixed = wp->position_fixed;
            ctl->child_D0->rotation.y     = wp->rotation.y;
            func_8002FFC4(&ctl->child_D0->position, &ctl->child_D0->position_fixed.v, wp->rotation.y, D_8011AB54.x * 16, D_8011AB54.y * 16,
                          D_8011AB54.z * 16);
            ctl->hit_90.pos_0   = ctl->child_D0->position;
            ctl->hit_90.pos_0.y = ctl->child_D0->position.y - 0x40;
            func_800341BC(&ctl->hit_90, 0x60, 0, 0x8000, wp->work_id, &ctl->hit_90.hit_8, 0x04080000, 0, 0x80);
        }
        else
        {
            ctl->child_D0->be_flag &= ~TRANS;
            ctl->child_D0->position       = wp->position;
            ctl->child_D0->position_fixed = wp->position_fixed;
        }
        if (ctl->flags_0 & 4)
        {
            ctl->hit_10[0].pos_0 = ST0B_OBJ_JOINT(wp)[4];
            func_800341BC(&ctl->hit_10[0], 0xA0, 0, 0x8000, wp->work_id, &ctl->hit_10[0].hit_8, 0x04080000, 0, 0);
        }
        if (ctl->flags_0 & 8)
        {
            ctl->hit_10[1].pos_0 = ST0B_OBJ_JOINT(wp)[6];
            func_800341BC(&ctl->hit_10[1], 0xA0, 0, 0x8000, wp->work_id, &ctl->hit_10[1].hit_8, 0x04080000, 0, 0);
        }
        if (ctl->flags_0 & 0x10)
        {
            ctl->hit_68[0].pos_0 = ST0B_OBJ_JOINT(wp)[8];
            ctl->hit_68[0].pos_0.y -= 0x40;
            func_800341BC(&ctl->hit_68[0], 0x60, 0, 0x8000, wp->work_id, &ctl->hit_68[0].hit_8, 0x04080000, 0, 0);
        }
        if (ctl->flags_0 & 0x20)
        {
            ctl->hit_68[1].pos_0 = ST0B_OBJ_JOINT(wp)[7];
            ctl->hit_68[1].pos_0.y -= 0x40;
            func_800341BC(&ctl->hit_68[1], 0x60, 0, 0x8000, wp->work_id, &ctl->hit_68[1].hit_8, 0x04080000, 0, 0);
        }
    }
    if (wp->u_E.b.work_2 != 0 && (sint32)Moji_flag >= 0)
    {
        if (!(ctl->msg_D8 & 8) && wp->u_C.b.work_1 >= 4)
        {
            ctl->msg_D8 |= 0xF;
            MojiTaskExec2(4, 0x10);
            ctl->flags_0 &= ~0x2000;
        }
        if (!(ctl->msg_D8 & 4) && wp->u_C.b.work_1 == 3)
        {
            ctl->msg_D8 |= 7;
            MojiTaskExec2(4, 0xE);
        }
        if (!(ctl->msg_D8 & 2) && wp->u_C.b.work_1 == 1)
        {
            ctl->msg_D8 |= 3;
            MojiTaskExec2(4, 0xA);
        }
        if (!(ctl->msg_D8 & 1) && wp->u_C.b.work_1 == 0)
        {
            ctl->msg_D8 |= 1;
            MojiTaskExec2(4, 0xD);
        }
    }
    func_80106E4C(wp);
}

void func_80105118(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    sint32 i;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    ctl                     = (ST0B_CTL *)&wp->value_380;
    if (wp->value_380 & 0x4000)
    {
        for (i = 0; i < 9; i++)
        {
            wp->pal[i].color = 0x4210;
        }
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    ctl->child_D0->scale.v.pad = 0x4210;
    ctl->rand_2                = rand();
    func_8005D4C0();
    wp->position.y         = ctl->base_DA + (D_800BBCF8[ctl->wave_CC++] >> 8);
    wp->position_fixed.v.y = wp->position.y << 16;
    ctl->wave_CC &= 0x3F;
    D_8011AB08[wp->routine_1](wp);
    if (ctl->flags_0 & 0x400)
    {
        D_8011AB38[ctl->act_A4[2].index_0](wp);
    }
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 1:
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 3:
                wp->routine_0             = 0;
                wp->type                  = 1;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            default:
                *(uint16 *)&wp->routine_2 = 0;
                break;
        }
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_C != 0)
    {
        ctl->timer_C--;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->flags_0 & 0x200)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
    }
    else
    {
        Model_pose_unpack(wp);
    }
    Model_parts_mtx_set_y(wp);
    func_80051B68(wp, 1, 0, 0);
    func_80106E4C(wp);
}

void func_801053B0(ST0B_OBJ *wp)
{
    func_8003187C(wp);
    func_80031824(wp->value_450);
}

void func_801053E4(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_80105404(ST0B_OBJ *wp)
{
    STAGE_PL_VIEW *pl;
    uint16 *flags;

    flags = &wp->value_380;
    pl    = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 3;
            *flags      = (*flags | 0x200) & ~0x400;
            // fall through
        case 1:
            if (*flags & 0xC)
            {
                if (func_80031EF0(&wp->position, wp->rotation.y, 0x100, &pl->position, pl->rotation.y, 0x800) != 0)
                {
                    *flags |= 1;
                }
            }
            else if (!(*flags & 0x3C))
            {
                *flags |= 0x400;
            }
            break;
    }
    if ((*flags & 4) && wp->frame_A6 == 1)
    {
        Sound_call2(0x143, &wp->position);
    }
    if ((*flags & 8) && wp->frame_A6 == 2)
    {
        Sound_call2(0x146, &wp->position);
    }
}

void func_8010552C(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    STCOM_EFFECT *ep;
    STCOM_PL_WORK *pl;
    sint32 joint;

    pl  = &Player_work;
    ctl = (ST0B_CTL *)&wp->value_380;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            ctl->flags_0 |= 0x600;
            // fall through
        case 1:
            if ((ctl->flags_0 & 0xC) == 0xC)
            {
                wp->anim_AC = ctl->toggle_F + 1;
                ctl->toggle_F ^= 1;
            }
            else if (ctl->flags_0 & 4)
            {
                wp->anim_AC = 1;
            }
            else
            {
                wp->anim_AC = 2;
            }
            wp->routine_2++;
            break;
        case 2:
            joint = (wp->frame_A6 & 0xF0) >> 4;
            if (wp->frame_A6 & 0xF0)
            {
                ep = func_80031618();
                if (ep != NULL)
                {
                    ep->be_flag         = 9;
                    ep->id              = 0xF;
                    ep->type            = 3;
                    ep->value_C         = 0;
                    ep->sprite.pos_8[0] = ((STCOM_SVECTOR *)((uint8 *)wp + (joint << 3) + 0x180))->x;
                    ep->sprite.pos_8[1] = ((STCOM_SVECTOR *)((uint8 *)wp + (joint << 3) + 0x180))->y;
                    ep->sprite.pos_8[2] = ((STCOM_SVECTOR *)((uint8 *)wp + (joint << 3) + 0x180))->z;
                }
                func_80106C90(wp);
                wp->routine_2++;
                func_800341BC(&pl->position, 0x60, 0, 0x8000, wp->work_id, &wp->value_464, D_8009884C[wp->id]->hit_E | 0x04000000, 0, 0x80);
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                if (func_80031EF0(&wp->position, wp->rotation.y, 0x100, &pl->position, Player_work.rotation.y, 0x800) == 0)
                {
                    ctl->flags_0 |= 1;
                }
                else
                {
                    wp->routine_2 = 1;
                    wp->anim_AC   = 0;
                }
            }
            break;
    }
    if ((wp->frame_A6 & 0xF) == 1)
    {
        Sound_call2(0x152, &wp->position);
    }
    if ((wp->frame_A6 & 0xF) == 2)
    {
        Sound_call2(0x153, &wp->position);
    }
}

void func_80105790(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    STAGE_PL_VIEW *pl;

    ctl = (ST0B_CTL *)&wp->value_380;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC          = 3;
            wp->value_44.half[0] = 0x80;
            wp->value_4C.half[0] = 0x20;
            wp->value_3E4        = 0;
            wp->value_380 |= 0x200;
            // fall through
        case 1:
            if (Dist_xz_sq(&wp->position, &pl->position) <= 0x7FFFFF)
            {
                if (wp->value_44.half[0] != 0)
                {
                    wp->value_44.half[0] -= 0x20;
                }
            }
            else if (wp->value_44.half[0] < 0x100)
            {
                wp->value_44.half[0] += 0x10;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x40)) & 0xFFF;
            Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            if (ctl->time_64 >= 0x5AB)
            {
                ctl->flags_0 = (ctl->flags_0 | 1) & ~0x400;
            }
            break;
    }
    ctl->time_64++;
}

void func_801058E4(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    STAGE_PL_VIEW *pl;
    STCOM_SVECTOR *pt;
    uint32 dx;
    uint32 dz;

    ctl = (ST0B_CTL *)&wp->value_380;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC          = 3;
            wp->value_44.half[0] = 0x180;
            wp->value_4C.half[0] = 0x40;
            ctl->index_4         = 0;
            ctl->count_6         = 0;
            ctl->base_DA         = 0x45F;
            ctl->flags_0 |= 0x200;
            ctl->data_E0 += 2;
            ctl->flags_0 &= ~0x400;
            wp->position.x         = D_8011AB5C[0];
            wp->position.y         = D_8011AB5C[1];
            wp->position.z         = D_8011AB5C[2];
            wp->position_fixed.v.x = D_8011AB5C[0] << 16;
            wp->position_fixed.v.y = D_8011AB5C[1] << 16;
            wp->position_fixed.v.z = D_8011AB5C[2] << 16;
            wp->rotation.y         = D_8011AB5C[3];
            wp->part_F8[0].value_3 = -1;
            wp->part_F8[1].value_3 = -1;
            wp->part_F8[3].value_3 = -1;
            wp->part_F8[4].value_3 = -1;
            wp->part_F8[5].value_3 = -1;
            wp->part_F8[6].value_3 = -1;
            wp->part_F8[7].value_3 = -1;
            wp->part_F8[8].value_3 = -1;
            // fall through
        case 1:
            ctl->path_D4   = &D_8011AB24[Game_work.value_51][ctl->index_4];
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, ctl->path_D4, wp->rotation.y, 0x40)) & 0xFFF;
            if (Dist_xz_sq(&wp->position, &pl->position) <= 0x7FFFFF)
            {
                if (wp->value_44.half[0] != 0)
                {
                    wp->value_44.half[0] -= 0x40;
                }
            }
            else if (wp->value_44.half[0] < 0x300)
            {
                wp->value_44.half[0] += 0x20;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            pt = ctl->path_D4;
            dx = wp->position.x - (pt->x - 0x200);
            dz = wp->position.z - (pt->z - 0x200);
            if (dx < 0x400 && dz < 0x400)
            {
                ctl->index_4++;
                if (ctl->path_D4[1].pad < 0)
                {
                    ctl->path_D4 += 1;
                    wp->routine_3 = 0;
                    wp->routine_2++;
                    ctl->index_4 = D_8011ABA4[0][0];
                }
            }
            else if (ctl->index_4 == 2)
            {
                if (ctl->count_6 == 0)
                {
                    func_80106C90(wp);
                }
                ctl->count_6 = (ctl->count_6 + 1) & 0x3F;
                ctl->flags_0 |= 0x400;
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, wp->target_454, wp->rotation.y, 0x40)) & 0xFFF;
            if (Dist_xz_sq(&wp->position, wp->target_454) <= 0x1FFFF)
            {
                if (wp->value_44.half[0] != 0)
                {
                    wp->value_44.half[0] -= 0x40;
                }
            }
            else if (wp->value_44.half[0] < 0x300)
            {
                wp->value_44.half[0] += 0x20;
            }
            if (wp->value_44.half[0] != 0)
            {
                Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            }
            if (wp->routine_3 != 4)
            {
                ctl->base_DA -= 0x20;
                if ((*(uint16 *)0x1F800002 & 0xF) < 8)
                {
                    func_80106F6C(wp);
                }
                if (wp->routine_3 != 4 && --ctl->index_4 == 0)
                {
                    // dx doubles as the index (retail reuses its register)
                    for (dx = 0; D_8011ABA6[wp->routine_3][dx] != 0xFF; dx++)
                    {
                        wp->part_F8[D_8011ABA6[wp->routine_3][dx]].value_3 = 0;
                    }
                    if (++wp->routine_3 < 4)
                    {
                        ctl->index_4 = D_8011ABA4[wp->routine_3][0];
                    }
                }
            }
            if (wp->value_44.half[0] == 0 && wp->routine_3 == 4)
            {
                wp->routine_2++;
                ctl->flags_0 |= 1;
                ctl->data_E0 += 2;
            }
            break;
    }
    ctl->time_64++;
}

void func_80105DC8(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    ST0B_ACT *act;

    ctl = ST0B_OBJ_CTL(wp);
    act = &ctl->act_A4[ctl->index_E];
    act->index_0++;
    act->angle_4 = 0;
    act->step_6  = 0;
}

void func_80105DF4(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    ST0B_ACT *act;
    STAGE_PL_VIEW *pl;
    ST0B_SHELL *shell;
    sint16 turn;

    ctl = (ST0B_CTL *)&wp->value_380;
    act = &ctl->act_A4[ctl->index_E];
    pl  = &STAGE_PL;
    switch (act->state_1)
    {
        case 0:
            act->state_1++;
            act->step_6  = (sint8)D_8011ABC4[ctl->rand_2 & 7];
            act->timer_2 = 0;
            act->count_3 = (rand() & 0x1F) + 0x10;
            // fall through
        case 1:
            if (act->timer_2 != 0)
            {
                act->timer_2--;
            }
            if (act->count_3 == 0)
            {
                if (((act->angle_4 + act->step_6 + 0x190) & 0xFFF) < 0x320)
                {
                    act->angle_4 = (act->angle_4 + act->step_6) & 0xFFF;
                    turn =
                        Muku(&ST0B_OBJ_JOINT(wp)[8 - ctl->index_E], &pl->position, (wp->rotation.y + act->angle_4 + 0x800) & 0xFFF, 0x800);
                    if (act->timer_2 == 0 && (uint16)(turn + 0x9F) < 0x7F)
                    {
                        shell = (ST0B_SHELL *)Open_SHL_WORK();
                        if (shell != NULL)
                        {
                            act->timer_2            = 0x14;
                            shell->be_flag          = MOVE | TRANS;
                            shell->id               = 6;
                            shell->type             = 0x80;
                            shell->position         = ST0B_OBJ_JOINT(wp)[8 - ctl->index_E];
                            shell->position_fixed.x = shell->position.x << 16;
                            shell->position_fixed.y = shell->position.y << 16;
                            shell->position_fixed.z = shell->position.z << 16;
                            shell->angle_64         = (wp->rotation.y + act->angle_4 + 0x800) & 0xFFF;
                            func_8002FFC4(&shell->position, &shell->position_fixed, shell->angle_64, D_8011ABCC.x * 16, D_8011ABCC.y * 16,
                                          D_8011ABCC.z * 16);
                            shell->dist_9C = Distance_xz(&pl->position.x, &wp->position.x) / 24;
                            shell->height_A0 =
                                (pl->position.y - wp->position.y >= 0 ? pl->position.y - wp->position.y : wp->position.y - pl->position.y) /
                                20;
                            Sound_call2(0x145, &shell->position);
                        }
                    }
                }
                else
                {
                    act->state_1 = 0;
                }
            }
            else
            {
                act->count_3--;
            }
            break;
    }
}

void func_801060E0(ST0B_OBJ *wp)
{
    wp->value_438 = 0;
    wp->value_43A = 0;
    wp->value_434++;
}

void func_801060F8(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    ST0B_STEP *st;
    uint8 count;

    ctl = (ST0B_CTL *)&wp->value_380;
    st  = (ST0B_STEP *)&wp->value_434;
    switch (wp->value_435)
    {
        case 0:
            wp->value_435++;
            wp->value_436 = 0;
            // fall through
        case 1:
            if (ctl->timer_C == 0)
            {
                st->step_1++;
                st->count_3  = ctl->data_E0[0] + 1;
                st->timer_4  = ctl->data_E0[1];
                st->reload_6 = ctl->data_E0[1];
            }
            break;
        case 2:
            if ((sint16)--wp->value_438 < 0)
            {
                count = --wp->value_437;
                if (count == 0)
                {
                    wp->value_435 = 1;
                    wp->value_38C = 0x78;
                }
                else
                {
                    func_80106B08(wp, count & 1);
                }
                st->timer_4 = st->reload_6;
            }
            break;
    }
}

void func_80106228(ST0B_OBJ *wp)
{
    wp->scale.v.pad = 0x4210;
    wp->value_440   = 0;
    wp->value_442   = 0;
    wp->value_43C++;
    wp->u_C.b.work_1++;
    wp->value_380 &= ~0x4000;
    wp->value_450->be_flag |= TRANS;
    wp->value_45E = 0;
}

void func_80106278(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    ST0B_SHOOT *st;
    ST0B_10C *shot;
    STCOM_PL_WORK *pl;

    ctl = (ST0B_CTL *)&wp->value_380;
    pl  = &Player_work;
    st  = (ST0B_SHOOT *)&wp->value_43C;
    switch (wp->value_43D)
    {
        case 0:
            wp->value_43D++;
            wp->value_43E = 0;
            // fall through
        case 1:
            if (func_80031EF0(&ctl->child_D0->position, (wp->rotation.y + 0x800) & 0xFFF, 0x400, &pl->position, pl->rotation.y, 0x800) != 0)
            {
                ctl->slot_60 = (ST0B_10C *)Open_SHL_WORK();
                if (ctl->slot_60 != NULL)
                {
                    shot                 = ctl->slot_60;
                    shot->be_flag        = MOVE;
                    shot->id             = 2;
                    shot->value_4        = 0;
                    shot->type           = 0;
                    shot->work_1         = 1;
                    shot->position       = wp->position;
                    shot->position_fixed = wp->position_fixed;
                    func_8002FFC4(&shot->position, &shot->position_fixed.v, wp->rotation.y, D_8011ABD4 << 4, D_8011ABD6 << 4,
                                  D_8011ABD8 << 4);
                    ctl->flags_0 |= 0x800;
                    st->step_1++;
                }
            }
            break;
        case 2:
            shot = wp->slot_3E0;
            if (wp->value_380 & 0x800)
            {
                if (shot->work_0 != 0)
                {
                    wp->value_43D++;
                    shot->work_0 -= 0x80;
                    wp->value_442 = D_8009884C[wp->id]->value_D;
                    wp->value_380 &= ~0x800;
                }
                shot->position       = wp->position;
                shot->position_fixed = wp->position_fixed;
                func_8002FFC4(&shot->position, &shot->position_fixed.v, wp->rotation.y, D_8011ABD4 << 4, D_8011ABD6 << 4, D_8011ABD8 << 4);
            }
            else
            {
                wp->value_43D++;
                wp->value_442 = D_8009884C[wp->id]->value_D;
            }
            break;
        case 3:
            if ((sint16)--wp->value_442 < 0)
            {
                wp->value_43D = 0;
                wp->value_43E = 0;
                wp->value_45E = 0;
            }
            break;
    }
}

sint32 func_80106550(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    ST0B_HITBOX *hit;
    sint32 i;
    sint32 damage;
    ST0B_HITBOX *hits[5] = {&ST0B_OBJ_CTL(wp)->hit_90, &ST0B_OBJ_CTL(wp)->hit_10[0], &ST0B_OBJ_CTL(wp)->hit_10[1],
                            &ST0B_OBJ_CTL(wp)->hit_68[0], &ST0B_OBJ_CTL(wp)->hit_68[1]};

    ctl = ST0B_OBJ_CTL(wp);
    for (i = 0; i < 5; i++)
    {
        hit = hits[i];
        if (hit->size_10 > 0 && (damage = hit->hit_8 & 0xFFFFFF) != 0)
        {
            if (hit->hit_8 & 0x38000000)
            {
                hit->size_10 -= damage;
                if (hit->size_10 <= 0)
                {
                    hit->size_10 = 0;
                    damage       = D_8009884C[wp->id]->value_9;
                    ctl->flags_0 &= ~(2 << i);
                    D_8011AB1C[i](wp);
                    ctl->count_DE = D_8009884C[wp->id]->value_C;
                }
                if (ctl->flags_0 & 0x800)
                {
                    if (++ctl->count_DE >= D_8009884C[wp->id]->value_C)
                    {
                        ctl->count_DE = 0;
                        Close_SHL_WORK(ctl->slot_60);
                        ctl->flags_0 &= ~0x800;
                    }
                }
                if (ctl->flags_0 & 0x80)
                {
                    ctl->timer_A += damage;
                    if ((hit->hit_8 & 0x20000000) || ctl->timer_A >= D_8009884C[wp->id]->value_9)
                    {
                        Sound_call2(0xA2, &wp->position);
                        ctl->timer_A = 0;
                    }
                    else
                    {
                        Sound_call2(0xA0, &wp->position);
                    }
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
                if (i != 0)
                {
                    if (!(ctl->flags_0 & 0x3C))
                    {
                        ctl->flags_0 |= 0x1000;
                    }
                    wp->pal[D_8011ABDC[i]].color = 0x7FFF;
                    if (i < 3)
                    {
                        wp->pal[D_8011ABDC[i] - 1].color = 0x7FFF;
                    }
                }
                else
                {
                    ctl->child_D0->scale.v.pad = 0x7FFF;
                    wp->scale.v.pad            = 0x7FFF;
                    wp->value_6E               = ctl->hit_90.size_10;
                }
            }
            else
            {
                Sound_call2(0xA3, &wp->position);
            }
        }
    }
    return 1;
}

void func_80106838(ST0B_JOINTED *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag         = MOVE | MODEL;
        ep->id              = 0x80;
        ep->type            = 0x42;
        ep->value_C         = 1;
        ep->value_D         = 2;
        ep->sprite.position = wp->joint_180[4];
    }
    wp->part_100[1].value_3 = -1;
    wp->part_100[2].value_3 = -1;
    wp->u_C.b.work_1++;
}

void func_801068C8(ST0B_JOINTED *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag         = MOVE | MODEL;
        ep->id              = 0x80;
        ep->type            = 0x42;
        ep->value_C         = 1;
        ep->value_D         = 2;
        ep->sprite.position = wp->joint_180[6];
    }
    wp->part_100[3].value_3 = -1;
    wp->part_100[4].value_3 = -1;
    wp->u_C.b.work_1++;
}

void func_80106958(ST0B_JOINTED *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag         = MOVE | MODEL;
        ep->id              = 0x80;
        ep->type            = 0x42;
        ep->value_C         = 1;
        ep->value_D         = 2;
        ep->sprite.position = wp->joint_180[8];
    }
    wp->part_100[6].value_3 = -1;
    wp->u_C.b.work_1++;
}

void func_801069E4(ST0B_JOINTED *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag         = MOVE | MODEL;
        ep->id              = 0x80;
        ep->type            = 0x42;
        ep->value_C         = 1;
        ep->value_D         = 2;
        ep->sprite.position = wp->joint_180[7];
    }
    wp->part_100[5].value_3 = -1;
    wp->u_C.b.work_1++;
}

void func_80106A70(ST0B_OBJ *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag         = MOVE | MODEL;
        ep->id              = 0x80;
        ep->type            = 0x42;
        ep->value_C         = 1;
        ep->value_D         = 2;
        ep->sprite.position = wp->value_450->position;
    }
    wp->value_450->be_flag &= ~TRANS;
}

sint32 func_80106B08(ST0B_OBJ *wp, sint32 side)
{
    ST0B_10C *fx;
    ST0B_CTL *ctl;

    fx  = (ST0B_10C *)Open_SHL_WORK();
    ctl = (ST0B_CTL *)&wp->value_380;
    if (fx != NULL)
    {
        fx->be_flag            = MOVE;
        fx->type               = 4;
        fx->id                 = 0;
        fx->target_B8          = &STAGE_PL.value_3A8;
        fx->position           = ST0B_OBJ_JOINT(wp)[2];
        fx->position_fixed.v.x = fx->position.x << 16;
        fx->position_fixed.v.y = fx->position.y << 16;
        fx->position_fixed.v.z = fx->position.z << 16;
        if (side != 0)
        {
            func_8002FFC4(&fx->position, &fx->position_fixed.v, wp->rotation.y, D_8011ABE4 << 4, D_8011ABE6 << 4, D_8011ABE8 << 4);
        }
        else
        {
            func_8002FFC4(&fx->position, &fx->position_fixed.v, wp->rotation.y, D_8011ABE4 << 4, D_8011ABE6 << 4, -D_8011ABE8 << 4);
        }
        ctl->rot_48.words[0] = 0;
        ctl->rot_48.words[1] = 0;
        ctl->rot_48.v.x      = 0xC00;
        ctl->rot_48.v.y      = wp->rotation.y;
        ctl->rot_48.v.z      = 0;
        RotMatrixYXZ(&ctl->rot_48.v, &fx->matrix_8C.m);
        ctl->scale_50.x   = 0x200;
        ctl->scale_50.y   = 0x200;
        ctl->scale_50.z   = 0x200;
        ctl->scale_50.pad = 0;
        ScaleMatrix(&fx->matrix_8C.m, &ctl->scale_50);
        Sound_call2(0x144, &wp->position);
        return 1;
    }
    return 0;
}

void func_80106C90(ST0B_OBJ *wp)
{
    STCOM_EFFECT *ep;
    sint32 dist;
    sint32 angle;
    STCOM_PL_WORK *pl;

    pl = &Player_work;

    wp->pos_3C8   = pl->position;
    wp->fixed_3D0 = Player_work.position_fixed;
    dist          = ((rand() & 3) << 7) + 0x100;
    angle         = Angle_xz_svector(&pl->position, &wp->position);
    func_8002FFC4(&wp->pos_3C8, &wp->fixed_3D0, (angle + ((rand() & 3) << 5)) & 0xFFF, dist << 4, 0, 0);
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag           = MOVE | MODEL;
        ep->id                = 0x10;
        ep->type              = 0;
        ep->value_C           = 0;
        ep->sprite.position   = wp->pos_3C8;
        ep->sprite.position.y = -1;
    }
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag           = MOVE | MODEL;
        ep->id                = 0x10;
        ep->type              = 1;
        ep->value_C           = 0;
        ep->sprite.position   = wp->pos_3C8;
        ep->sprite.position.y = -1;
    }
    Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
    func_80115068(1, 0, 8, &wp->pos_3C8);
}

void func_80106E4C(ST0B_OBJ *wp)
{
    ST0B_CTL *ctl;
    STCOM_EFFECT *ep;

    ctl = (ST0B_CTL *)&wp->value_380;
    if (wp->value_45C == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            wp->pos_3C8   = wp->position;
            wp->fixed_3D0 = wp->position_fixed.v;
            func_8002FFC4(&wp->pos_3C8, &wp->fixed_3D0, wp->rotation.y, 0x1000, 0, 0);
            ep->be_flag = MOVE | MODEL;
            ep->id      = 0x10;
            ep->type    = 1;
            if (wp->value_45A != -1)
            {
                ep->value_C = 1;
            }
            else
            {
                ep->value_C = 2;
            }
            ep->sprite.position   = wp->position;
            ep->sprite.position.y = -1;
        }
    }
    ctl->count_DC = (ctl->count_DC + 1) & 0xF;
}

void func_80106F6C(ST0B_OBJ *wp)
{
    STCOM_EFFECT *ep;

    wp->pos_3C8   = wp->position;
    wp->fixed_3D0 = wp->position_fixed.v;
    func_8002FFC4(&wp->pos_3C8, &wp->fixed_3D0, wp->rotation.y, 0x1000, 0, 0);
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag           = MOVE | MODEL;
        ep->id                = 0x10;
        ep->type              = 0;
        ep->value_C           = 0;
        ep->sprite.position   = wp->pos_3C8;
        ep->sprite.position.y = -1;
    }
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag           = MOVE | MODEL;
        ep->id                = 0x10;
        ep->type              = 1;
        ep->value_C           = 0;
        ep->sprite.position   = wp->pos_3C8;
        ep->sprite.position.y = -1;
    }
    func_80115068(1, 0, 8, &wp->pos_3C8);
}

void func_801070B0(ST0B_OBJ *wp)
{
    func_801053B0(wp);
}

void func_801070D0(ST0B_PROP *wp)
{
    D_8011ABEC[wp->routine_1](wp, &wp->value_380);
    if (wp->u_C.b.work_1 == 0)
    {
        func_80032488(wp);
    }
}

void func_80107130(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, &wp->type);
    func_800322A8(wp, 0, 0);
    wp->u_C.b.work_1 = 0;
    wp->routine_1    = 1;
    wp->routine_2    = 0;
}

void func_801071A0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.x = (uint16)wp->position.x + 2;
        wp->position.y = (uint16)wp->position.y - 1;
    }
}

// The origin array occupies the local stack area; only its first entry is used.
void func_801071D0(STAGE_OBJ *wp, ST0B_GRID_OBJ **out)
{
    uint32 i;
    STCOM_SVECTOR *origin[4];
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->be_flag |= TRANS;
    Model_work_init(wp, &wp->type);
    func_800322A8(wp, 0, 0);
    for (i = 3; i < 9; i++)
    {
        ((ST0B_OBJ *)wp)->part_F8[i].value_3 = -1;
    }
    wp->routine_1 = 3;
    wp->routine_2 = 0;
    wp->u_C.b.work_1++;
    origin[0]                  = (STCOM_SVECTOR *)D_8011ABFC;
    *out                       = func_80109CB0(wp, 3, origin[0]);
    *(uint8 *)&(*out)->value_C = 7;
}

void func_80107298(void)
{
}
