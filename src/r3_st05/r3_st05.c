#include "common.h"
#include "st05.h"


// Installs the stage's slot routine tables.
void func_8010088C(void)
{
    STAGE_TABLE_3C0 = D_8012D9C4;
    STAGE_TABLE_5A4 = D_8012DB04;
    STAGE_TABLE_10C = D_8012DB2C;
    STAGE_TABLE_48  = D_8012DBEC;
    STAGE_TABLE_24  = D_8012DC1C;
    STAGE_TABLE_50  = D_8012DC30;
}

// Sets up the current room: models, map, spawns.
void func_801008F4(void)
{
    STAGE_MAP_WORK *mw;
    sint32 room;
    void *spawns;
    STCOM_SVECTOR *pos;

    mw = STAGE_MAP_WORK_PTR;
    Room_model_init(D_8012DCFC[Game_work.value_51]);
    room      = Game_work.value_51;
    mw->w     = STAGE_MAP_TBL[room].w;
    mw->h     = STAGE_MAP_TBL[room].h;
    mw->x0    = STAGE_MAP_TBL[room].x0;
    mw->z0    = STAGE_MAP_TBL[room].z0;
    mw->x1    = mw->x0 + mw->w;
    mw->z1    = mw->z0 + mw->h;
    mw->cells = STAGE_MAP_TBL[room].cells;
    mw->info  = STAGE_CELL_INFO;
    switch (room)
    {
        case 0:
            if (Sce_flag_test(0x208))
            {
                STAGE_PL.value_170 = 4;
                STAGE_PL.value_171 = 0;
                STAGE_PL.value_44E = -1;
            }
            else if (Sce_flag_test(0x235))
            {
                STAGE_PL.value_171 = 1;
                STAGE_PL.value_170 = 0;
                STAGE_PL.value_44E = -1;
            }
            else
            {
                STAGE_PL.value_44E = 0;
            }
            if (Sce_flag_test(0x214) && !Sce_flag_test(0x24A))
            {
                pos = D_8012E44C;
                Stage_idx_model_set(Map_cell_get(&pos[0]), 0xF0000);
                Stage_idx_model_set(Map_cell_get(&pos[1]), 0xF0100);
            }
            break;
        case 1:
            if (!Sce_flag_test(9))
            {
                STAGE_PL.value_44E = 1;
            }
            break;
    }
    spawns                    = D_8012DFB8[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8012E1F4[Game_work.value_51];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_8012E2D0[D_8012E438[Game_work.value_51]], D_8012E208[Game_work.value_51]);
    func_8005DC10(0);
    func_80106B28();
}

void func_80100B5C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_28->routine_0 = 5;
        wp->child_28->routine_1 = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        wp->child_28->routine_0 = 9;
        wp->child_28->routine_1 = 0;
    }
    if (wp->frame_10 == 0x5A)
    {
        wp->child_28->routine_0 = 6;
        wp->child_28->routine_1 = 0;
    }
}

void func_80100BDC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_28);
        wp->reserved09[1] |= 0x20;
        D_80137DA0->fixed_428.x = 0x072C0000;
        D_80137DA0->fixed_428.y = 0xFFFF0000;
        D_80137DA0->fixed_428.z = 0x137B0000;
        D_80137DA0->pos_438.x   = 0x72C;
        D_80137DA0->pos_438.y   = -1;
        D_80137DA0->pos_438.z   = 0x137B;
        D_80137DA0->value_442   = 0xC00;
        D_80137DA0->value_448   = 0x30;
    }
    if (wp->frame_10 == 0xF)
    {
        D_80137DA0->value_448 = 0x80;
        MojiTaskExec2(0, 7);
    }
}

void func_80100C9C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        D_80137DA0->value_442 = 0x800;
        D_80137DA0->flags_0 ^= 2;
        D_80137DA0->value_448      = 0x30;
        wp->child_24->routine_0    = 2;
        wp->child_24->u_C.b.byte_D = 9;
        wp->child_24->u_E.b.byte_E = 0xF;
    }
    if (wp->frame_10 == 0xAC)
    {
        Model_mesh_uv_copy(wp->child_24->model_88, 0x10000F, Model_uv_cell(D_8012E45E, 0x33, 0x37, 5));
        Model_mesh_uv_copy(wp->child_24->model_88, 0x120011, Model_uv_cell(D_8012E45F, 0x33, 0x37, 5));
    }
}

void func_80100D90(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->position.z -= 0x40;
        D_80137DA0->flags_0 |= 2;
    }
    if (((ST05_OBJ *)wp->child_24)->value_A6 == 1)
    {
        Sound_call2(0x111, &wp->child_24->position);
    }
}

void func_80100E08(STAGE_ROOM *wp)
{
    sint32 i;

    if (wp->frame_10 == 0)
    {
        D_80137DA0->flags_0 ^= 2;
        wp->reserved09[1] = 0;
    }
    if (wp->frame_10 >= 3 && wp->frame_10 < 6)
    {
        Model_mesh_uv_copy(wp->child_24->model_88, 0x10000F, Model_uv_cell(D_8012E45C[(wp->frame_10 - 1) << 1], 0x33, 0x37, 5));
        Model_mesh_uv_copy(wp->child_24->model_88, 0x120011, Model_uv_cell(D_8012E45D[(wp->frame_10 - 1) << 1], 0x33, 0x37, 5));
    }
    if (wp->frame_10 == 0xF)
    {
        Model_mesh_uv_copy(wp->child_24->model_88, 0x10000F, Model_uv_cell(D_8012E466, 0x33, 0x37, 5));
        Model_mesh_uv_copy(wp->child_24->model_88, 0x120011, Model_uv_cell(D_8012E467, 0x33, 0x37, 5));
    }
    if (wp->frame_10 == 0x1E)
    {
        MojiTaskExec2(0, 9);
    }
    if (wp->frame_10 >= 0x2D && wp->frame_10 < 0x89)
    {
        i = wp->reserved09[1];
        if (D_8012E468[i] == -1)
        {
            wp->reserved09[1] = 0;
        }
        else if (D_8012E468[i] == 0)
        {
            wp->reserved09[1] = i - D_8012E468[i + 1];
        }
        Model_mesh_uv_copy(wp->child_24->model_88, 0x120011, Model_uv_cell(D_8012E468[wp->reserved09[1]], 0x33, 0x37, 5));
        wp->reserved09[1]++;
    }
    if (wp->frame_10 == 0x89)
    {
        Model_mesh_uv_copy(wp->child_24->model_88, 0x120011, Model_uv_cell(D_8012E467, 0x33, 0x37, 5));
    }
}

void func_8010105C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_80137DA0->flags_0 |= 2;
        D_80137DA0->value_448 = 0x30;
        wp->child_24->position.x -= 0x80;
        wp->child_24->position_fixed.v.x = wp->child_24->position.x << 16;
        wp->child_24->position_fixed.v.y = wp->child_24->position.y << 16;
        wp->child_24->position_fixed.v.z = wp->child_24->position.z << 16;
    }
    if (wp->frame_10 < 0xA)
    {
        wp->child_24->rotation.y += 0xB4;
    }
    if (wp->frame_10 == 0xA)
    {
        wp->child_24->rotation.y   = 0x708;
        wp->child_24->routine_0    = 3;
        wp->child_24->u_C.b.byte_D = 0;
        wp->child_24->u_E.b.byte_F = 0;
    }
    D_80137DA0->value_442 = Angle_xz_svector(&D_80137DA0->position, &wp->child_24->position);
}

void func_801011A0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        D_80137DA0->value_448 = 0x81;
        MojiTaskExec2(0, 5);
        child = wp->child_24;
        if (child->flags_0 & 1)
        {
            func_8003187C(child);
            wp->reserved09[1] |= 0x10;
        }
    }
}

void func_80101220(void)
{
}

void func_80101228(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        MojiTaskExec2(0, 0xEU);
        wp->child_28->routine_0    = 8;
        wp->child_28->u_E.b.byte_F = 0;
    }
}

void func_8010127C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        Model_mesh_uv_copy(wp->child_24->model_88, 0x10000FU, Model_uv_cell(D_8012E45C[0], 0x33, 0x37, 5));
        Model_mesh_uv_copy(wp->child_24->model_88, 0x120011, Model_uv_cell(D_8012E45D[0], 0x33, 0x37, 5));
        MojiTaskExec2(0, 8);
        wp->child_24->u_E.b.byte_F = 0;
        wp->child_24->routine_0    = 4;
    }
}

void func_80101330(STAGE_ROOM *wp)
{
    STCOM_SVECTOR unused; // unused: reserves the frame's 8 extra bytes

    func_8001E6C0(0, 0, 0);
    if (Sce_flag_test(0x641) != 0)
    {
        D_800BC7F0 = D_8012E4DC;
        wp->tbl_A4 = D_8012E740;
    }
    else
    {
        D_800BC7F0 = D_8012E60C;
        wp->tbl_A4 = D_8012E790;
    }
    wp->child_24      = D_80138088[0];
    wp->child_28      = D_80138088[1];
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->reserved09[1] = 1;
}

void func_801013E0(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101420(STAGE_ROOM *wp)
{
    STCOM_FIXED_VECTOR cam;

    D_80137DA0 = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            func_80101330(wp);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(D_80137DA0) != 0)
            {
                D_80137DA0->routine_0 = 3;
                D_80137DA0->routine_1 = 0;
                D_80137DA0->value_448 = 0x30;
                wp->routine_4++;
            }
            break;
        case 2:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
                break;
            }
            if (func_8001DE84() != 0 && (wp->reserved09[1] & 1))
            {
                func_80053AA4(0);
                Cd_subcmd(0, 1, 0);
                wp->routine_4++;
                break;
            }
            func_801013E0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                Sound_fade_start(0x10);
                wp->routine_4++;
            }
            break;
        case 4:
            if (Sound_fade_flags == 0)
            {
                Sound_call(7, 0, 0);
                wp->routine_4++;
            }
            break;
        case 5:
            D_800A395C                   = 1;
            D_80137DA0->fixed_428.x      = 0x7380000;
            D_80137DA0->fixed_428.y      = 0xFFFF0000;
            D_80137DA0->fixed_428.z      = 0x12E30000;
            D_80137DA0->value_442        = 0x64;
            D_80137DA0->position_fixed.x = 0x7380000;
            D_80137DA0->position_fixed.y = 0xFFFF0000;
            D_80137DA0->position_fixed.z = 0x12E30000;
            D_80137DA0->rotation.y       = 0x64;
            func_80030150(&D_80137DA0->fixed_428, &D_80137DA0->pos_438);
            func_80030150(&D_80137DA0->position_fixed, &D_80137DA0->position);
            Player_work.routine_1++;
            D_80137DA0->flags_0 |= 2;
            cam.x = Player_work.position.x;
            cam.y = Player_work.position.y - 0x96;
            cam.z = Player_work.position.z;
            func_80039E18();
            func_80039C54(&cam, 0x258, (Player_work.rotation.y - 0x824) & 0xFFF, 0);
            wp->flags_0 = 0;
            if (!(wp->reserved09[1] & 0x10))
            {
                func_8003187C(wp->child_24);
            }
            if (!(wp->reserved09[1] & 0x20))
            {
                func_80031824(wp->child_28);
            }
            Sound_work.volume_6 = 0x7F;
            func_80042314(&Player_work);
            break;
    }
}

void func_801016E8(void)
{
}

void func_801016F0(void)
{
    STAGE_OBJ *obj;

    obj = func_80031498();
    if (obj != NULL)
    {
        obj->flags_0            = 1;
        obj->kind_2             = 9;
        obj->value_4            = 5;
        obj->position_fixed.v.x = 0x72C0000;
        obj->position_fixed.v.y = -0x10000;
        obj->variant_3          = 0;
        obj->u_C.b.byte_C       = 0;
        obj->u_C.b.byte_D       = 0;
        obj->u_E.b.byte_E       = 0;
        obj->u_E.b.byte_F       = 0;
        obj->position_fixed.v.z = 0x145F0000;
        func_80030150(&obj->position_fixed.v, &obj->position);
    }
    obj = func_80031418();
    if (obj != NULL)
    {
        obj->flags_0            = 1;
        obj->kind_2             = 0x2A;
        obj->position_fixed.v.x = 0x7EC0000;
        obj->position_fixed.v.y = -0x10000;
        obj->value_4            = 0;
        obj->variant_3          = 0;
        obj->u_C.b.byte_C       = 0;
        obj->u_C.b.byte_D       = 0;
        obj->u_E.b.byte_E       = 0;
        obj->u_E.b.byte_F       = 0;
        obj->position_fixed.v.z = 0x145F0000;
        func_80030150(&obj->position_fixed.v, &obj->position);
    }
}

void func_801017C4(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_801019DC(wp);
                wp->routine_4++;
            }
            break;
        case 1:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
                wp->routine_5++;
                break;
            }
            if (func_8001DE84() != 0)
            {
                wp->routine_4             = 6;
                wp->routine_5             = 0;
                *(uint16 *)&wp->routine_6 = 0;
            }
            func_80101BE4((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            Cd_xa_play_id(0x20000000);
            wp->routine_4++;
            break;
        case 4:
            if (func_8001D878() == 0)
            {
                break;
            }
            func_8003187C(wp->child_28);
            func_80101A70(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
                break;
            }
            if (func_8001DE84() != 0)
            {
                wp->routine_4             = 6;
                *(uint16 *)&wp->routine_6 = 0;
            }
            func_80101BE4((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            if (D_80137DBC != 0)
            {
                func_80102944();
            }
            switch (D_80137DF8)
            {
                case 0:
                    D_800BC7D4 = 0;
                    break;
                case 1:
                    D_800BC7D4 = D_8012EF00[STAGE_FRAME & 3] << 16;
                    break;
            }
            Sce_event_update();
            break;
        case 6:
            func_80101C24(wp);
            break;
    }
}

void func_801019DC(STAGE_ROOM *wp)
{
    wp->reserved09[2] = D_800A395A;
    wp->reserved09[1] = D_800A395B;
    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_8012E874;
    Scene_obj_ent_open(&D_8012E7FC[0]);
    wp->tbl_A4        = D_8012EE28;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    D_80137DF8        = 0;
    D_80137DBC        = 0;
}

void func_80101A70(STAGE_ROOM *wp)
{
    wp->word_14 = 0;
    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_8012E8E8;
    Scene_obj_ent_open(D_8012E7E8);
    Scene_obj_ent_open(D_8012E7E8 + 0x28);
    Scene_obj_ent_open(D_8012E7E8 + 0x3C);
    Scene_obj_ent_open(D_8012E7E8 + 0x50);
    Scene_obj_ent_open(D_8012E7E8 + 0x64);
    Scene_obj_ent_open(D_8012E7E8 + 0x78);
    SetTile(&D_80137DC0[0]);
    SetTile(&D_80137DC0[1]);
    D_80137DC0[0].r0 = D_80137DC0[1].r0 = 8;
    D_80137DC0[0].g0 = D_80137DC0[1].g0 = 8;
    D_80137DC0[0].b0 = D_80137DC0[1].b0 = 8;
    D_80137DC0[0].w = D_80137DC0[1].w = 0x140;
    D_80137DC0[0].h = D_80137DC0[1].h = 0xF0;
    D_80137DC0[0].x0 = D_80137DC0[1].x0 = 0;
    D_80137DC0[0].y0 = D_80137DC0[1].y0 = 0;
    D_80137DC0[0].code |= 2;
    D_80137DC0[1].code |= 2;
    wp->tbl_A4        = D_8012EE38;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->routine_8     = 1;
    D_80137DF8        = 0;
    D_80137DBC        = 0;
}

void func_80101BE4(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101C24(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;

    pl = &STAGE_PL;
    switch (wp->routine_6)
    {
        case 0:
            if (wp->routine_5 == 0)
            {
                if (wp->routine_7 == 0)
                {
                    wp->routine_7 = 1;
                    Fade_start(0xA);
                    Sound_fade_start(0x40);
                }
                if (D_80098A72 != 0 || Sound_fade_flags != 0 || Cd_read_sync2() != 0)
                {
                    break;
                }
                func_801028D0(1);
                Fade_start(2);
            }
            else
            {
                func_801028D0(1);
                Cd_subcmd(0, 1, 0);
            }
            wp->routine_6++;
            // fall through
        case 1:
            Obj_work_flag_change(0x156, 0x80);
            D_800BC7F0 = D_8012EDE0;
            Sce_camera_update();
            Sce_event_update();
            pl->pos_438.x = 0x400;
            pl->pos_438.y = -1;
            pl->pos_438.z = 0x1BE0;
            pl->value_442 = 0x800;
            pl->value_440 = 0;
            pl->value_444 = 0;
            pl->flags_0 |= 2;
            pl->fixed_428.x = pl->pos_438.x << 16;
            pl->fixed_428.y = pl->pos_438.y << 16;
            pl->fixed_428.z = pl->pos_438.z << 16;
            pl->routine_1++;
            pl->flags_bd |= 0x10;
            wp->routine_6++;
            break;
        case 2:
            obj = func_80031498();
            if (obj != NULL)
            {
                obj->flags_0               = 1;
                *(uint32 *)&obj->u_C       = 0;
                obj->u_E.b.byte_F          = 1;
                obj->position.x            = 0x400;
                obj->position.y            = -1;
                obj->position.z            = 0x2100;
                obj->kind_2                = 0;
                obj->value_4               = 0;
                obj->variant_3             = 0;
                *(uint32 *)&obj->routine_0 = 0;
                obj->value_44.value        = 0;
                obj->value_48.value        = 0;
                obj->position_fixed.v.x    = obj->position.x << 16;
                obj->position_fixed.v.y    = obj->position.y << 16;
                obj->position_fixed.v.z    = obj->position.z << 16;
            }
            obj->life_max_B0 = 0;
            obj->life_6E     = 0;
            func_8005D620(obj, 0, 0, 0x60, 0x2C203080);
            func_80042314(pl);
            D_800A395C = 1;
            func_80039820();
            D_800A395A  = wp->reserved09[2];
            D_800A395B  = wp->reserved09[1];
            wp->flags_0 = 0;
            Sound_call(6, 0, 0);
            break;
    }
}

void func_80101ED0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (wp->frame_10 == 0)
    {
        *(uint16 *)&Player_work.routine_0 = 3;
        pl->flags_0 &= ~2;
        func_8002FBF4(pl);
        Cd_read_comb(0x55);
    }
}

void func_80101F1C(STAGE_ROOM *wp)
{
    STAGE_OBJ *a;
    STAGE_OBJ *b;
    STAGE_OBJ *c;

    a = wp->child_34;
    b = wp->child_38;
    c = wp->child_3C;
    if (wp->frame_10 == 0)
    {
        *(uint16 *)&a->routine_2 = 0;
        *(uint16 *)&b->routine_2 = 0;
        *(uint16 *)&c->routine_2 = 0;
        D_80137DBC               = 1;
        D_80137DC4               = 0x40;
        D_80137DC5               = 0x40;
        D_80137DC6               = 0x10;
        D_80137DD4               = 0x48;
        D_80137DD5               = 0x48;
        D_80137DD6               = 0x12;
    }
    if (wp->frame_10 == 0x64)
    {
        *(uint16 *)&b->routine_2 = 1;
    }
    if (wp->frame_10 == 0x6C)
    {
        *(uint16 *)&a->routine_2 = 1;
        *(uint16 *)&c->routine_2 = 1;
    }
}

void func_80101FC0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        func_801028D0(3);
        child->routine_1             = 0;
        *(uint16 *)&child->routine_2 = 0;
        D_80137DBC                   = 0;
    }
}

void func_80102008(STAGE_ROOM *wp)
{
    STAGE_OBJ *a;
    STAGE_OBJ *b;
    STAGE_OBJ *c;

    a = wp->child_34;
    b = wp->child_38;
    c = wp->child_3C;
    if (wp->frame_10 == 0)
    {
        func_801028D0(1);
        *(uint16 *)&a->routine_2 = 2;
        *(uint16 *)&b->routine_2 = 2;
        *(uint16 *)&c->routine_2 = 2;
        D_80137DBC               = 1;
        D_80137DC4               = 0x40;
        D_80137DC5               = 0x40;
        D_80137DC6               = 0x10;
        D_80137DD4               = 0x48;
        D_80137DD5               = 0x48;
        D_80137DD6               = 0x12;
    }
}

void func_801020B4(STAGE_ROOM *wp)
{
    STAGE_OBJ *a;
    STAGE_OBJ *b;
    STAGE_OBJ *c;
    STAGE_OBJ *d;

    a = wp->child_34;
    b = wp->child_38;
    c = wp->child_3C;
    d = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        func_801028D0(3);
        a->routine_0             = 2;
        b->routine_0             = 2;
        c->routine_0             = 2;
        *(uint16 *)&d->routine_2 = 1;
        D_80137DBC               = 0;
    }
}

void func_80102130(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        child->routine_1             = 0;
        *(uint16 *)&child->routine_2 = 2;
    }
}

void func_80102150(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        *(uint16 *)&child->routine_2 = 3;
    }
}

void func_8010216C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        *(uint16 *)&child->routine_2 = 4;
    }
}

void func_80102188(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    child = wp->child_24;
    other = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        other->flags_0 &= ~2;
        child->routine_1             = 1;
        *(uint16 *)&child->routine_2 = 0;
        func_801028D0(1);
    }
}

void func_801021D4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0x19)
    {
        child->routine_1 = 4;
    }
}

void func_801021F4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;

    pl    = &Player_work;
    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        child->routine_1     = 0;
        STAGE_PL.pos_438.x   = 0x400;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = 0x1F00;
        STAGE_PL.fixed_428.x = 0x4000000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0x1F000000;
        STAGE_PL.value_442   = 0xC00;
        STAGE_PL.value_448   = 0x80;
        STAGE_PL.value_440   = 0;
        STAGE_PL.value_444   = 0;
        D_80137DBC           = 1;
        D_80137DC4 = D_80137DD4 = 8;
        D_80137DC5 = D_80137DD5 = 8;
        D_80137DC6 = D_80137DD6 = 8;
        pl->flags_0 |= 2;
    }
    else if (wp->frame_10 < 0x1A)
    {
        D_80137DC4 = D_80137DD4 += 3;
        D_80137DC5 = D_80137DD5 += 3;
        D_80137DC6 = D_80137DD6 += 3;
    }
    if (wp->frame_10 <= 0x40)
    {
        STAGE_PL.value_168 = 0;
        STAGE_PL.value_169 = 0;
    }
    else
    {
        STAGE_PL.value_168 = 0xC;
        STAGE_PL.value_169 = 0xC;
    }
}

void func_80102374(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        D_80137DBC       = 0;
        child->routine_1 = 5;
    }
    else
    {
        STAGE_PL.value_168 = 0;
        STAGE_PL.value_169 = 0;
    }
}

void func_801023AC(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *child;

    pl    = &STAGE_PL;
    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        child->routine_1   = 6;
        child->routine_2   = 0;
        STAGE_PL.value_442 = 0x800;
        wp->routine_7      = 0;
    }
    if (wp->routine_7 == 0)
    {
        if (child->position.y == -1)
        {
            wp->routine_7      = 1;
            D_80137DA8         = -0x160;
            STAGE_PL.value_448 = 0x22;
            STAGE_PL.value_74  = 1;
            D_80137DF8         = 1;
            wp->routine_6      = 4;
        }
    }
    else
    {
        if (wp->routine_6 != 0)
        {
            wp->routine_6--;
        }
        else
        {
            D_80137DF8 = 0;
        }
        pl->fixed_428.y += D_80137DA8 << 12;
        pl->pos_438.y = pl->fixed_428.y >> 16;
        D_80137DA8 += 0x30;
        pl->pos_438.z -= 0x14;
    }
}

void func_8010249C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;

    pl    = &Player_work;
    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        STAGE_PL.value_448 = 0;
        pl->flags_0 &= ~2;
        STAGE_PL.fixed_428.z      = STAGE_PL.pos_438.z << 16;
        *(uint16 *)&wp->routine_6 = 0;
    }
    if (wp->frame_10 == 0x46)
    {
        child->routine_1 = 7;
    }
}

void func_801024FC(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    pl    = &Player_work;
    child = wp->child_2C;
    other = wp->child_30;
    if (wp->frame_10 == 0)
    {
        child->position.x            = 0x400;
        *(uint32 *)&child->routine_0 = 0;
        child->position.y            = -0x400;
        child->u_C.timer             = 0;
        child->routine_1             = 1;
        child->position.z            = 0x2108;
        child->u_E.b.byte_F          = 1;
        child->position_fixed.v.x    = child->position.x << 16;
        child->value_44.value        = 0;
        child->value_48.value        = 0;
        child->position_fixed.v.y    = child->position.y << 16;
        child->position_fixed.v.z    = child->position.z << 16;
        other->u_E.b.byte_F          = 1;
        pl->flags_0 |= 2;
    }
}

void func_80102588(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *child;

    pl    = &STAGE_PL;
    child = wp->child_2C;
    if (wp->frame_10 == 0)
    {
        child->u_C.b.byte_D = 1;
        child->u_E.b.byte_E++;
    }
    else if (wp->frame_10 == 1)
    {
        D_80137DAC = 0;
        D_80137DB0 = 0;
        D_80137DB4 = 0;
        D_80137DB8 = 0;
    }
    if (wp->reserved09[0] == 2)
    {
        if (wp->frame_10 == 0)
        {
            pl->value_448 = 0x81;
        }
        D_80137DB4 = 6;
        if (wp->frame_10 == 0xF || wp->frame_10 == 0x2D)
        {
            D_80137DB0 = 1;
        }
        else if (wp->frame_10 == 0x19)
        {
            D_80137DB0 = 0;
            D_80137DAC = 0;
            D_80137DB8 = 0;
        }
        else if (wp->frame_10 == 0x7D)
        {
            D_80137DB0 = 0;
            D_80137DAC = 0;
            D_80137DB8 = 6;
        }
        if (D_80137DB0 != 0)
        {
            switch ((D_80137DAC / 3) & 7)
            {
                case 2:
                case 5:
                    D_80137DB8 = 6;
                    break;
                case 0:
                case 4:
                case 6:
                    D_80137DB8 = 0xA;
                    break;
                case 1:
                case 3:
                case 7:
                    D_80137DB8 = 0;
                    break;
            }
            D_80137DAC++;
        }
    }
    else if (wp->reserved09[0] == 4)
    {
        D_80137DB4 = 6;
        D_80137DB8 = 6;
    }
    else if (wp->reserved09[0] == 7)
    {
        if (wp->frame_10 == 0)
        {
            pl->value_448 = 0x82;
        }
        D_80137DB4 = 4;
        if (wp->frame_10 == 0xA)
        {
            D_80137DB0 = 1;
        }
        if (wp->frame_10 == 0x3C)
        {
            D_80137DB0 = 0;
            D_80137DAC = 0;
            D_80137DB8 = 0;
        }
        if (D_80137DB0 != 0)
        {
            switch ((D_80137DAC / 3) & 7)
            {
                case 0:
                case 4:
                case 6:
                    D_80137DB8 = 0x16;
                    break;
                case 2:
                case 5:
                    D_80137DB8 = 0xA;
                    break;
                case 1:
                case 3:
                case 7:
                    D_80137DB8 = 0;
                    break;
            }
            D_80137DAC++;
        }
    }
    STAGE_PL.value_168 = D_80137DB4;
    STAGE_PL.value_169 = D_80137DB8;
}

void func_80102854(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    child = wp->child_2C;
    other = wp->child_30;
    if (wp->frame_10 == 0)
    {
        child->u_C.b.byte_D = 1;
        child->u_E.b.byte_E++;
    }
    if (wp->frame_10 == 0x122)
    {
        func_8003187C(child);
        other->u_E.b.byte_F = 1;
    }
}

void func_801028B8(void)
{
    STAGE_PL.value_168 = 0;
    STAGE_PL.value_169 = 0;
}

void func_801028D0(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 5;
    D_800C3560 = 0x400;
    D_800C3562 = -1;
    D_800C3564 = 0x1BE0;
    D_800C356A = 0x800;
    D_800C356F = arg0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80102944(void)
{
    POLY_FT4 *poly;
    DR_MODE *mode;

    poly              = *STAGE_PACKET_PTR;
    *STAGE_PACKET_PTR = poly + 2;
    Mem_copy32(&D_80137DC0[ST05_BUFFER_INDEX], poly, 4);
    mode = (DR_MODE *)(poly + 1);
    Mem_copy32(&D_80137DE0[ST05_BUFFER_INDEX], mode, 3);
    SetDrawMode(mode, 0, 0, GetTPage(2, 2, 0, 0), NULL);
    addPrim(&Disp_env_ptr->ot_74, poly);
    addPrim(&Disp_env_ptr->ot_74, mode);
}

void func_80102A6C(STAGE_ROOM *wp)
{
    D_8012EF08[wp->routine_4](wp);
}

void func_80102AA8(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(8, 0x80);
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl))
            {
                func_8001E6C0(0, 0, 0);
                D_800BC7F0    = D_8012EF50;
                wp->tbl_A4    = D_8012F144;
                wp->timer_C   = 0;
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->pos_438.x = 0x400;
                pl->pos_438.y = -1;
                pl->pos_438.z = 0x1900;
                pl->value_442 = 0x800;
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->value_448 = 0;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                wp->routine_5   = 0;
                wp->routine_7   = 0;
                wp->routine_4++;
                Sce_camera_update();
                Sce_event_update();
            }
            break;
    }
}


void func_80102BDC(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *child;

    pl = &STAGE_PL;
    if (func_8001DE84())
    {
        wp->routine_6 = 1;
    }
    switch (wp->routine_5)
    {
        case 0:
            pl->routine_1++;
            wp->routine_5++;
            break;
        case 1:
            func_8005D7C0();
            pl->flags_bd |= 0x20;
            wp->routine_6     = 0;
            wp->reserved09[1] = 0;
            wp->reserved09[2] = 0;
            wp->routine_5++;
            break;
        case 2:
            func_8010301C(wp);
            func_801032A0(wp);
            if (wp->routine_6 == 1)
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
        case 3:
            if (func_8001D878())
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_8012F154;
                wp->tbl_A4    = D_8012F3B8;
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->pos_438.x = -0x200;
                pl->pos_438.z = 0x1900;
                pl->value_442 = 0x940;
                pl->pos_438.y = -1;
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->value_448 = 0x30;
                pl->flags_0 &= ~2;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x           = pl->pos_438.x << 16;
                pl->fixed_428.y           = pl->pos_438.y << 16;
                pl->fixed_428.z           = pl->pos_438.z << 16;
                child                     = wp->child_24;
                child->position.x         = -0x1C0;
                child->position.z         = 0x1978;
                child->position.y         = -1;
                child->position_fixed.v.x = child->position.x << 16;
                child->position_fixed.v.y = child->position.y << 16;
                child->position_fixed.v.z = child->position.z << 16;
                child->rotation.x         = 0;
                child->rotation.y         = 0x140;
                child->rotation.z         = 0;
                wp->routine_7             = 0;
                wp->routine_5++;
            }
            break;
        case 4:
            if (wp->routine_8 != 0xFF)
            {
                wp->tbl_A4[1](wp);
                if (wp->routine_6 == 1)
                {
                    wp->routine_6 = 2;
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
        default:
            Sce_event_update();
            return;
    }
    Sce_camera_update();
    Sce_event_update();
}


void func_80102E3C(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            func_80031824(wp->child_28);
            func_80042314(&Player_work);
            D_800A395C = 1;
            func_80039820();
            wp->flags_0 = 0;
            break;
        case 1:
            switch (wp->routine_5)
            {
                case 0:
                    func_8003697C();
                    Obj_work_flag_change(0x76, 0x80);
                    Cd_subcmd(0, 1, 0);
                    STAGE_PL.routine_0   = 3;
                    STAGE_PL.routine_1   = 1;
                    STAGE_PL.pos_438.x   = -0x200;
                    STAGE_PL.pos_438.y   = -1;
                    STAGE_PL.pos_438.z   = 0x1900;
                    STAGE_PL.fixed_428.x = -0x200 << 16;
                    STAGE_PL.fixed_428.y = -1 << 16;
                    STAGE_PL.fixed_428.z = 0x1900 << 16;
                    STAGE_PL.value_440   = 0;
                    STAGE_PL.value_442   = 0x940;
                    STAGE_PL.value_444   = 0;
                    STAGE_PL.value_448   = 0;
                    STAGE_PL.flags_bd |= 0x10;
                    wp->routine_5++;
                    break;
                case 1:
                    func_80042314(&Player_work);
                    D_800A395C = 1;
                    func_80039820();
                    wp->flags_0 = 0;
                    break;
            }
            break;
        case 2:
            switch (wp->routine_5)
            {
                case 0:
                    func_8003697C();
                    Obj_work_flag_change(0x56, 0x80);
                    Cd_subcmd(0, 1, 0);
                    func_80103768(0);
                    func_801037CC(&STAGE_PL);
                    wp->routine_5++;
                    break;
                case 1:
                    func_80042314(&Player_work);
                    D_800A395C = 1;
                    func_80039820();
                    wp->flags_0 = 0;
                    break;
            }
            break;
    }
}

void func_8010301C(STAGE_ROOM *wp)
{
    ST05_PL_VIEW *pl;
    sint16 angle;

    D_800C0F96[0] = 0;
    pl            = &ST05_PL;
    switch (wp->reserved09[1])
    {
        case 0:
            if (wp->frame_10 == 0x3C)
            {
                wp->reserved09[1]++;
            }
            break;
        case 1:
            if ((pl->rotation.y & 0xFFF) < 0x400)
            {
                pl->push_438.y = -1;
                angle = pl->push_438.x = 0x400;
                pl->push_438.z         = 0x1900;
                pl->angle_442          = angle;
                pl->value_440          = 0;
                pl->value_444          = 0;
                pl->flags_bd |= 0x10;
                pl->push_428.x = pl->push_438.x << 16;
                pl->push_428.y = pl->push_438.y << 16;
                pl->push_428.z = pl->push_438.z << 16;
                wp->reserved09[1]++;
            }
            else
            {
                D_800C0F96[0] = pl->pad_128;
            }
            break;
        case 2:
            D_800C0F96[0] = 0;
            if (wp->frame_10 == 0x82)
            {
                wp->reserved09[1]++;
            }
            break;
        case 3:
            if (pl->position.x < -0x1C0)
            {
                pl->push_438.x = -0x1C0;
                pl->push_438.y = -1;
                pl->push_438.z = 0x1900;
                pl->angle_442  = 0x400;
                pl->value_440  = 0;
                pl->value_444  = 0;
                pl->flags_bd |= 0x10;
                pl->push_428.x = pl->push_438.x << 16;
                pl->push_428.y = pl->push_438.y << 16;
                pl->push_428.z = pl->push_438.z << 16;
                wp->reserved09[1]++;
            }
            else
            {
                D_800C0F96[0] = pl->value_124;
            }
            break;
        case 4:
            if ((pl->rotation.y & 0xFFF) > 0x800)
            {
                pl->push_438.x = -0x1C0;
                pl->push_438.y = -1;
                pl->push_438.z = 0x1900;
                pl->angle_442  = 0x800;
                pl->value_440  = 0;
                pl->value_444  = 0;
                pl->flags_bd |= 0x10;
                pl->push_428.x = pl->push_438.x << 16;
                pl->push_428.y = pl->push_438.y << 16;
                pl->push_428.z = pl->push_438.z << 16;
                wp->reserved09[1]++;
            }
            else
            {
                D_800C0F96[0] = pl->pad_12A;
            }
            break;
        case 5:
            pl->routine_1++;
            wp->reserved09[1]++;
            break;
        case 6:
            if (pl->routine_1 == 0 && wp->reserved09[2] == 5)
            {
                pl->flags_bd = (pl->flags_bd & ~0x20) | 0x40;
                Cd_xa_play_id(0x20000006);
                wp->routine_5++;
            }
            break;
    }
}

void func_801032A0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 t;

    child = wp->child_24;
    switch (wp->reserved09[2])
    {
        case 0:
            if (wp->frame_10 == 0x3C)
            {
                Scene_obj_ent_open(D_8012EF14);
                wp->reserved09[2]++;
            }
            break;
        case 1:
            t                         = wp->frame_10 - 0x3C;
            child->position.x         = (t * 0x8C + (0x20 - t) * 0x400) / 32;
            child->position.z         = (t * 0x1C7B + (0x20 - t) * 0x2100) / 32;
            child->position.y         = Obj_ceiling_height_get(child) + (-(D_800BBCF8[t] << 9) >> 12);
            child->position_fixed.v.x = child->position.x << 16;
            child->position_fixed.v.y = child->position.y << 16;
            child->position_fixed.v.z = child->position.z << 16;
            if (wp->frame_10 == 0x5C)
            {
                child->routine_2 = 0;
                child->routine_1++;
                wp->reserved09[2]++;
            }
            break;
        case 2:
            t                         = wp->frame_10 - 0x5C;
            child->position.x         = (t * -0x1C0 + (0x14 - t) * 0x8C) / 20;
            child->position.z         = (t * 0x1978 + (0x14 - t) * 0x1C7B) / 20;
            child->position.y         = Obj_ceiling_height_get(child);
            child->position_fixed.v.x = child->position.x << 16;
            child->position_fixed.v.z = child->position.z << 16;
            child->position_fixed.v.y = child->position.y << 16;
            if (wp->frame_10 == 0x70)
            {
                child->routine_2 = 0;
                child->routine_1++;
                wp->reserved09[2]++;
            }
            break;
        case 3:
            if (wp->frame_10 == 0xE6)
            {
                child->routine_2 = 0;
                child->routine_1++;
                wp->reserved09[2]++;
            }
            break;
        case 4:
            if (wp->frame_10 == 0x104)
            {
                wp->reserved09[2]++;
            }
            break;
        case 5:
            break;
    }
}

void func_80103558(void)
{
}

void func_80103560(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    if (wp->frame_10 == 0)
    {
        STAGE_PL.value_448 = 0x88;
        pl->flags_0 |= 2;
        func_80103768(1);
    }
    if (wp->frame_10 == 0x14 || wp->frame_10 == 0x32 || wp->frame_10 == 0x50)
    {
        func_80103768(2);
    }
    else if (wp->frame_10 == 0x28 || wp->frame_10 == 0x46 || wp->frame_10 == 0x64)
    {
        func_80103768(1);
    }
    func_801037CC(pl);
}

void func_80103610(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl                 = &Player_work;
        STAGE_PL.value_168 = 0;
        STAGE_PL.value_169 = 0;
        pl->flags_0 &= ~2;
        func_80103744(wp);
    }
}

void func_80103660(STAGE_ROOM *wp)
{
    sint32 i;

    if (wp->frame_10 == 0)
    {
        for (i = 0; i < 0x40; i++)
        {
            func_80031988(&D_800A3B40[i]);
        }
        Scene_obj_ent_open(D_8012EF28);
    }
}

void func_801036C8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80103744(wp);
    }
    if (wp->routine_7 == 1)
    {
        Scene_obj_ent_open(D_8012EF3C);
        wp->routine_7++;
    }
}

void func_80103734(void)
{
}

void func_8010373C(void)
{
}

void func_80103744(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    child = wp->child_24;
    child->routine_0++;
    other            = wp->child_24;
    other->routine_1 = 0;
}

void func_80103768(sint32 index)
{
    D_80137E00.shape_0 = D_80137E00.prev_2 = D_80137E00.index_4 = 0;
    D_80137E00.shape_6 = D_80137E00.prev_8 = D_80137E00.index_A = 0;
    D_80137E00.mouth_C                                          = D_8012F43C[index];
    D_80137E00.eyes_10                                          = D_8012F448[index];
}

void func_801037CC(STAGE_PL_VIEW *pl)
{
    STAGE_FACE16 *face;

    face       = &D_80137E00;
    D_80137E02 = face->shape_0;
    if (D_80137E0C[D_80137E04 + 1] != 0x3FFF)
    {
        if (D_80137E0C[D_80137E04 + 1] == 0x7FFF)
        {
            D_80137E04 = 0;
        }
        else
        {
            D_80137E04++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    face->prev_8  = face->shape_6;
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
    pl->value_168 = face->shape_0;
    pl->value_169 = face->shape_6;
}

void func_801038C4(STAGE_ROOM *wp)
{
    ST05_PL_SAVE *pl;

    pl = (ST05_PL_SAVE *)&Player_work;
    switch (wp->routine_6)
    {
        case 0:
            if (!func_80042238(pl))
            {
                break;
            }
            Sce_event_timer_clear();
            wp->routine_6++;
            // fall through
        case 1:
            pl->routine_8 = 3;
            pl->routine_9 = 1;
            pl->flags_BD |= 0x10;
            pl->pos_438   = pl->position;
            pl->fixed_428 = pl->position_fixed;
            pl->rot_440   = pl->rotation;
            pl->anim_448  = 0x35;
            Sce_flag_off(0x60A);
            wp->timer_C = 0x2D;
            wp->routine_6++;
            func_8005D7C0();
            MojiTaskExec2(0, 0x28);
            break;
        case 2:
            if (!(Moji_flag & 0x80000000))
            {
                wp->routine_6++;
            }
            break;
        case 3:
            func_80042314(pl);
            wp->flags_0 = 0;
            Sce_flag_on(0x620);
            Sce_flag_on(0x52D);
            break;
    }
}

void func_80103A58(STAGE_ROOM_WORK *wp)
{
    STAGE_REC *rec;

    D_8012F458[wp->routine_4](wp);
    for (rec = D_80137E18; rec < &D_80137E18[8]; rec++)
    {
        if (rec->active_0 & 1)
        {
            ((STAGE_SLOT_FUNC)rec->data_4)(rec);
        }
    }
    Sce_flag_off(0x619);
    Sce_flag_off(0x61A);
    Sce_flag_off(0x61B);
    Sce_flag_off(0x61C);
}

void func_80103B10(STAGE_ROOM_WORK *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_6)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                Sce_event_timer_clear();
                func_8001E6C0(0, 0, 0);
                D_800BC7F0 = D_801302AC;
                wp->tbl_A4 = D_80130224;
                stcom36_func_0028(3);
                func_80106098();
                func_8010602C(0, 4);
                func_8010602C(1, 5);
                func_8010602C(2, 6);
                func_8010602C(3, 7);
                wp->routine_6++;
            }
            break;
        case 1:
            if (STAGE_GAME.value_1 == 2)
            {
                wp->routine_6++;
                Sce_flag_on(0x60C);
            }
            break;
        case 2:
            if (Sce_flag_test(0x60F) != 0)
            {
                Sound_call(3, 0, 0);
                func_80106074(0);
                func_80106074(1);
                func_80106074(2);
                func_80106074(3);
                func_8010602C(0, 8);
                Sce_flag_off(0x60F);
                stcom36_func_0118();
                stcom36_func_0028(4);
                wp->routine_6++;
                Sce_event_next();
            }
            break;
        case 3:
            if (((uint8 *)wp->tbl_A4)[1] == 9)
            {
                Sce_flag_on(0x607);
                wp->routine_6++;
            }
            break;
        case 4:
            if (Sce_flag_test(0x60F) != 0)
            {
                Sce_flag_off(0x60F);
                wp->timer_C = 0x1E;
                wp->routine_6++;
            }
            break;
        case 5:
            if (--wp->timer_C == 0)
            {
                wp->routine_6++;
                D_800A395C = 1;
                func_80105F2C(3);
                func_80105F2C(4);
                func_80105F2C(5);
                stcom36_func_0118();
                pl->fixed_428.x = 0x3F80000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0x1DA30000;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->value_440 = 0;
                pl->value_442 = 0x800;
                pl->value_444 = 0;
                pl->value_448 = 0;
                func_80106098();
            }
            break;
        case 6:
            stcom36_func_0028(5);
            wp->routine_6++;
            break;
        case 7:
            MojiTaskExec2(0, 4);
            wp->flags_0 = 0;
            func_80042314(pl);
            Sce_flag_on(9);
            break;
    }
    if (wp->routine_6 != 0 && wp->routine_6 < 5 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (wp->routine_6 >= 2 && wp->routine_6 < 5 && func_8001DE84() != 0)
    {
        Sce_flag_off(0x60F);
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        wp->routine_6 = 5;
        wp->timer_C   = 1;
    }
}

void func_80103E68(STAGE_REC_S *rec)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (rec->step_2)
    {
        case 0:
            pl->fixed_428.x = 0x3F80000;
            pl->fixed_428.y = 0xFFFF0000;
            pl->fixed_428.z = 0x17EA0000;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->value_442 = 0x800;
            pl->value_448 = 1;
            rec->timer_8  = 0xA0;
            rec->step_2++;
            break;
        case 1:
            if (--rec->timer_8 == 0)
            {
                rec->timer_8 = 0xA0;
                rec->step_2++;
            }
            break;
        case 2:
            if (--rec->timer_8 != 0x7C)
            {
                func_8002FF34(pl, 0x200, 0, 0);
                break;
            }
            rec->step_2++;
            pl->value_448 = 0x30;
            // fall through
        case 3:
            if (--rec->timer_8 != 0x64)
            {
                break;
            }
            rec->step_2++;
            pl->value_448 = 0xC;
            // fall through
        case 4:
            if (--rec->timer_8 == 0x1E)
            {
                rec->step_2++;
                pl->value_448 = 0x30;
                func_8010602C(1, 9);
            }
            else
            {
                func_8002FF34(pl, 0x50, 0, 0);
            }
            break;
        case 5:
            break;
    }
}

void func_80104000(STAGE_REC_S *rec)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;
    STAGE_OBJ *src;

    pl = &Player_work;
    switch (rec->step_2)
    {
        case 0:
            ((STAGE_OBJ *)stcom36_E2_0000[5])->u_E.b.byte_F |= 8;
            rec->timer_8 = 0x23;
            rec->step_2++;
            break;
        case 1:
            if (--rec->timer_8 == 0)
            {
                Sce_event_next();
                func_8010602C(2, 0xA);
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x607) != 0)
            {
                Sce_flag_off(0x607);
                ((STAGE_OBJ *)stcom36_E2_0000[5])->u_E.b.byte_F |= 0x10;
                rec->timer_8 = 0x10;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                obj                 = (STAGE_OBJ *)stcom36_E2_0000[0];
                src                 = (STAGE_OBJ *)stcom36_E2_0000[5];
                obj->routine_2      = 1;
                obj->position       = src->position;
                obj->position_fixed = src->position_fixed;
                obj->position.y -= 0x18C;
                obj->position_fixed.v.y = obj->position.y << 16;
                obj->rotation.y         = Angle_xz_svector(&obj->position, &pl->position);
                rec->timer_8            = 0x10;
                rec->step_2++;
            }
            break;
        case 4:
            if (--rec->timer_8 == 0)
            {
                MojiTaskExec2(0, 0);
                rec->step_2++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_next();
                Sce_flag_on(0x608);
                rec->step_2++;
            }
            break;
        case 6:
            if (Sce_flag_test(0x607) != 0)
            {
                ((STAGE_OBJ *)stcom36_E2_0000[0])->routine_2 = 4;
                ((STAGE_OBJ *)stcom36_E2_0000[5])->u_E.b.byte_F |= 0x10;
                func_80106074(1);
            }
            break;
    }
}

void func_80104250(STAGE_REC_S *rec)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;
    STAGE_OBJ *src;

    pl = &Player_work;
    switch (rec->step_2)
    {
        case 0:
            rec->timer_8 = 0xF;
            rec->step_2++;
            // fall through
        case 1:
            if (--rec->timer_8 == 0)
            {
                ((STAGE_OBJ *)stcom36_E2_0000[3])->u_E.b.byte_F |= 8;
                rec->timer_8 = 0x14;
                rec->step_2++;
            }
            break;
        case 2:
            if (--rec->timer_8 == 0)
            {
                Sce_event_next();
                func_8010602C(3, 0xB);
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x608) != 0)
            {
                Sce_flag_off(0x608);
                ((STAGE_OBJ *)stcom36_E2_0000[3])->u_E.b.byte_F |= 0x10;
                rec->timer_8 = 0x10;
                rec->step_2++;
            }
            break;
        case 4:
            if (--rec->timer_8 == 0)
            {
                obj                 = (STAGE_OBJ *)stcom36_E2_0000[1];
                src                 = (STAGE_OBJ *)stcom36_E2_0000[3];
                obj->routine_2      = 1;
                obj->position       = src->position;
                obj->position_fixed = src->position_fixed;
                obj->position.y -= 0x18C;
                obj->position_fixed.v.y = obj->position.y << 16;
                obj->rotation.y         = Angle_xz_svector(&obj->position, &pl->position);
                rec->timer_8            = 0x10;
                rec->step_2++;
            }
            break;
        case 5:
            if (--rec->timer_8 == 0)
            {
                MojiTaskExec2(0, 1);
                rec->step_2++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_next();
                Sce_flag_on(0x609);
                rec->step_2++;
            }
            break;
        case 7:
            if (Sce_flag_test(0x608) != 0)
            {
                rec->timer_8 = 0xA;
                rec->step_2++;
            }
            break;
        case 8:
            if (--rec->timer_8 == 0)
            {
                ((STAGE_OBJ *)stcom36_E2_0000[1])->routine_2 = 4;
                ((STAGE_OBJ *)stcom36_E2_0000[3])->u_E.b.byte_F |= 0x10;
                func_80106074(2);
            }
            break;
    }
}

void func_801044F4(STAGE_REC_S *rec)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;
    STAGE_OBJ *src;

    pl = &Player_work;
    switch (rec->step_2)
    {
        case 0:
            ((STAGE_OBJ *)stcom36_E2_0000[4])->u_E.b.byte_F |= 8;
            rec->step_2++;
            break;
        case 1:
            if (Sce_flag_test(0x609) != 0)
            {
                Sce_flag_off(0x609);
                ((STAGE_OBJ *)stcom36_E2_0000[4])->u_E.b.byte_F |= 0x10;
                rec->timer_8 = 0x10;
                rec->step_2++;
            }
            break;
        case 2:
            if (--rec->timer_8 == 0)
            {
                obj                 = (STAGE_OBJ *)stcom36_E2_0000[2];
                src                 = (STAGE_OBJ *)stcom36_E2_0000[4];
                obj->routine_2      = 1;
                obj->position       = src->position;
                obj->position_fixed = src->position_fixed;
                obj->position.y -= 0x18C;
                obj->position_fixed.v.y = obj->position.y << 16;
                obj->rotation.y         = Angle_xz_svector(&obj->position, &pl->position);
                rec->timer_8            = 0x10;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                MojiTaskExec2(0, 2);
                rec->step_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_event_next();
                MojiTaskExec2(0, 3);
                rec->step_2++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x607);
                Sce_flag_on(0x608);
                Sce_flag_on(0x609);
                rec->step_2++;
            }
            break;
        case 6:
            if (Sce_flag_test(0x609) != 0)
            {
                rec->timer_8 = 0xF;
                rec->step_2++;
            }
            break;
        case 7:
            if (--rec->timer_8 == 0)
            {
                ((STAGE_OBJ *)stcom36_E2_0000[2])->routine_2 = 4;
                ((STAGE_OBJ *)stcom36_E2_0000[4])->u_E.b.byte_F |= 0x10;
                func_80106074(3);
                Sce_flag_on(0x60F);
            }
            break;
    }
}

void func_80104774(STAGE_REC_S *rec)
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
            pl->fixed_428.x = 0x16020000;
            pl->fixed_428.y = 0xFFFF0000;
            pl->fixed_428.z = 0xF9C10000;
            pl->flags_bd |= 0x10;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->value_442 = 0x800;
            pl->value_440 = 0;
            pl->value_444 = 0;
            pl->value_448 = 0x30;
            rec->step_2++;
            break;
        case 2:
            if (Sce_flag_test(0x60A) != 0)
            {
                Sce_flag_off(0x60A);
                pl->value_448 = 0xC;
                rec->timer_8  = 0xC;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                pl->value_448 = 0x30;
                MojiTaskExec2(0, 8);
                rec->step_2++;
            }
            func_8002FF34(pl, 0x50, 0, 0);
            break;
        case 4:
            if (Moji_flag & 0x200000)
            {
                pl->value_448 = 0x32;
            }
            if (!(Moji_flag & 0x08000000) && pl->flags_A7 < 0)
            {
                Sce_event_next();
                rec->step_2++;
            }
            break;
        case 5:
            pl->fixed_428.x = 0x16020000;
            pl->fixed_428.y = 0xFFFF0000;
            pl->fixed_428.z = 0xFA610000;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->value_442 = 0x6D0;
            Sce_flag_on(0x60B);
            Sce_flag_on(0x60D);
            rec->step_2++;
            break;
        case 6:
            if (Sce_flag_test(0x60A) != 0)
            {
                Sce_flag_off(0x60A);
                MojiTaskExec2(0, 0xB);
                rec->step_2++;
            }
            break;
        case 7:
            if (Moji_flag & 0x200000)
            {
                pl->value_448 = 0x32;
            }
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x60C);
                rec->step_2++;
            }
            break;
        case 8:
            if (Sce_flag_test(0x60A) != 0)
            {
                Sce_flag_off(0x60A);
                MojiTaskExec2(0, 0xD);
                rec->step_2++;
            }
            break;
        case 9:
            if (Moji_flag & 0x200000)
            {
                pl->value_448 = 0x32;
            }
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x60B);
                rec->step_2++;
            }
            break;
        case 10:
            if (Sce_flag_test(0x60A) != 0)
            {
                Sce_flag_off(0x60A);
                MojiTaskExec2(0, 0x17);
                rec->step_2++;
            }
            break;
        case 11:
            if (Moji_flag & 0x200000)
            {
                pl->value_448 = 0x32;
            }
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x60B);
                rec->step_2++;
            }
            break;
        case 12:
            if (Sce_flag_test(0x60A) != 0)
            {
                pl->value_448 = 0xD;
                rec->timer_8  = 0xC;
                Sce_flag_off(0x60A);
                rec->step_2++;
            }
            break;
        case 13:
            if (--rec->timer_8 != 0)
            {
                pl->value_442 = (pl->value_442 - 0x30) & 0xFFF;
                break;
            }
            Sce_flag_on(0x60B);
            pl->value_448 = 1;
            rec->timer_8  = 0x6C;
            rec->step_2++;
            Sce_flag_on(0x60C);
            Sce_flag_on(0x60D);
            // fall through
        case 14:
            if (--rec->timer_8 != 0)
            {
                func_8002FF34(pl, 0x200, 0, 0);
                break;
            }
            rec->timer_8 = 0x5A;
            rec->step_2++;
            // fall through
        case 15:
            if (--rec->timer_8 == 0)
            {
                rec->step_2++;
                break;
            }
            pl->value_442 = (pl->value_442 + 0xA) & 0xFFF;
            func_8002FF34(pl, 0x200, 0, 0);
            break;
        case 16:
            break;
    }
}

void func_80104BD0(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[0];
    switch (rec->step_2)
    {
        case 0:
            if (Sce_flag_test(0x60B) != 0)
            {
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_off(0x60B);
                MojiTaskExec2(0, 6);
                rec->step_2++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_event_next();
                Sce_flag_on(0x60C);
                Sce_flag_on(0x60D);
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x60B) != 0)
            {
                obj->rotation.y = 0xE08;
                Sce_flag_off(0x60B);
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x60B) != 0)
            {
                obj->routine_1             = 4;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_off(0x60B);
                MojiTaskExec2(0, 0x16);
                rec->step_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x60A);
                rec->step_2++;
            }
            break;
        case 5:
            if (Sce_flag_test(0x60B) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_off(0x60B);
                Sce_flag_off(0x619);
                Sce_flag_off(0x61F);
                MojiTaskExec2(0, 0x18);
                rec->step_2++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000) && Sce_flag_test(0x61F) != 0)
            {
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                MojiTaskExec2(0, 0x19);
                Sce_flag_off(0x61F);
                rec->step_2++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x60A);
                Sce_flag_on(0x60C);
                rec->step_2++;
            }
            break;
        case 8:
            if (Sce_flag_test(0x60B) != 0)
            {
                obj->routine_1             = 5;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 9:
            break;
    }
}

void func_80104E08(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[1];
    switch (rec->step_2)
    {
        case 0:
            rec->step_2++;
            break;
        case 1:
            if (Sce_flag_test(0x60C) != 0)
            {
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_off(0x60C);
                MojiTaskExec2(0, 7);
                rec->step_2++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x60B);
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x60C) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x20;
                obj->u_E.b.byte_F &= ~2;
                Sce_flag_off(0x60C);
                rec->step_2++;
            }
            break;
        case 4:
            if (Sce_flag_test(0x60C) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x800;
                obj->u_E.b.byte_F |= 2;
                Sce_flag_off(0x60C);
                MojiTaskExec2(0, 0xC);
                rec->step_2++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x60A);
                rec->step_2++;
            }
            break;
        case 6:
            if (Sce_flag_test(0x60C) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x20;
                obj->u_E.b.byte_F |= 2;
                Sce_flag_off(0x60C);
                MojiTaskExec2(0, 0xE);
                rec->step_2++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x20;
                obj->u_E.b.byte_F &= ~2;
                Sce_flag_on(0x61D);
                rec->step_2++;
            }
            break;
        case 8:
            break;
    }
}

void func_80104FFC(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[2];
    switch (rec->step_2)
    {
        case 0:
            if (Sce_flag_test(0x60D) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x20;
                obj->u_E.b.byte_F |= 2;
                Sce_flag_off(0x60D);
                Sce_flag_off(0x619);
                rec->step_2++;
            }
            break;
        case 1:
            MojiTaskExec2(0, 9);
            rec->step_2++;
            // fall through
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x60A);
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x60D) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x800;
                obj->u_E.b.byte_F |= 2;
                Sce_flag_off(0x60D);
                MojiTaskExec2(0, 0xA);
                rec->step_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x60A);
                rec->step_2++;
            }
            break;
        case 5:
            if (Sce_flag_test(0x60D) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x20;
                obj->u_E.b.byte_F &= ~2;
                Sce_flag_off(0x60C);
                rec->step_2++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000) && Sce_flag_test(0x61D) != 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.timer             = 0x20;
                obj->u_E.b.byte_F |= 2;
                Sce_flag_off(0x61D);
                MojiTaskExec2(0, 0xF);
                rec->step_2++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                Sce_flag_on(0x60F);
            }
            break;
    }
}

void func_80105220(STAGE_ROOM_WORK *wp)
{
    STAGE_REC *rec;

    D_8012F458[wp->routine_4](wp);
    for (rec = D_80137E18; rec < &D_80137E18[8]; rec++)
    {
        if (rec->active_0 & 1)
        {
            ((STAGE_SLOT_FUNC)rec->data_4)(rec);
        }
    }
    Sce_flag_off(0x619);
    Sce_flag_off(0x61A);
    Sce_flag_off(0x61B);
    Sce_flag_off(0x61C);
}

void func_801052D8(STAGE_ROOM_WORK *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_6)
    {
        case 0:
            if (func_80042238(pl) == 0)
            {
                break;
            }
            Sound_fade_start(0x10);
            Sce_event_timer_clear();
            func_8001E6C0(0, 0, 0);
            D_800BC7F0 = D_80130194;
            wp->tbl_A4 = D_80130184;
            wp->routine_6++;
            Sound_work.volume_6 = 0x64;
            // fall through
        case 1:
            pl->routine_0   = 3;
            pl->routine_1   = 1;
            pl->fixed_428.x = 0x16160000;
            pl->fixed_428.y = 0xFFFF0000;
            pl->fixed_428.z = 0xFA800000;
            pl->flags_bd |= 0x10;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->value_442 = 0x494;
            pl->value_440 = 0;
            pl->value_444 = 0;
            pl->value_448 = 0x30;
            stcom36_func_0028(0);
            func_80106098();
            func_8010602C(0, 0);
            func_8010602C(1, 1);
            func_8010602C(2, 2);
            func_8010602C(3, 3);
            Sce_flag_off(0x606);
            Sce_flag_off(0x607);
            Sce_flag_off(0x608);
            Sce_flag_off(0x609);
            wp->timer_C = 0x1E;
            wp->routine_6++;
            break;
        case 2:
            if (STAGE_GAME.value_1 != 2)
            {
                break;
            }
            wp->routine_6++;
            // fall through
        case 3:
            if (--wp->timer_C < 0)
            {
                wp->routine_6++;
                Sce_flag_on(0x606);
                MojiTaskExec2(0, 0xF);
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                wp->timer_C = 7;
                wp->routine_6++;
                MojiTaskExec2(0, 0x10);
                Sce_flag_on(0x606);
                Sce_flag_on(0x607);
                Sce_flag_on(0x608);
                Sce_flag_on(0x609);
            }
            break;
        case 5:
            if (--wp->timer_C < 0)
            {
                wp->routine_6++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                wp->timer_C = 0x46;
                wp->routine_6++;
                Sce_flag_on(0x607);
                Sce_flag_on(0x608);
                Sce_flag_on(0x609);
            }
            break;
        case 7:
            if (--wp->timer_C == 0)
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x11);
            }
            break;
        case 8:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_6++;
                MojiTaskExec2(0, 0x12);
                Sce_flag_on(0x606);
                Sce_flag_on(0x60E);
            }
            break;
        case 9:
            if (!(Moji_flag & 0x08000000))
            {
                wp->timer_C = 0x88;
                wp->routine_6++;
            }
            break;
        case 10:
            if (Sound_fade_flags == 0 && --wp->timer_C < 0)
            {
                func_80106074(0);
                func_80106074(1);
                func_80106074(2);
                func_80106074(3);
                func_80042314(pl);
                wp->flags_0 = 0;
                D_800A395C  = 1;
                stcom36_func_0118();
                stcom36_func_0028(1);
                Sce_flag_on(5);
                Sound_fade_start(0x20);
                Sound_work.volume_6 = 0x7F;
            }
            break;
    }
    if (wp->routine_6 != 0 && wp->routine_6 < 10 && *(uint8 *)wp->tbl_A4 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (wp->routine_6 >= 3 && func_8001DE84() != 0)
    {
        MojiTaskKill();
        func_80063BA8();
        Cd_subcmd(0, 1, 0);
        func_8001B314();
        wp->routine_6 = 10;
        wp->timer_C   = 0;
        func_80106098();
    }
}

void func_8010573C(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[0];
    switch (rec->step_2)
    {
        case 0:
            if (Sce_flag_test(0x606))
            {
                Sce_flag_off(0x606);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x606))
            {
                Sce_flag_off(0x606);
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x606))
            {
                Sce_flag_off(0x606);
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x606))
            {
                Sce_flag_off(0x606);
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 4:
            break;
    }
}

void func_8010582C(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[1];
    switch (rec->step_2)
    {
        case 0:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x61A))
            {
                func_80105E2C(1);
                func_80106074(1);
                Sce_flag_on(0x61D);
            }
            break;
    }
}

void func_80105944(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[2];
    switch (rec->step_2)
    {
        case 0:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                rec->timer_8 = 0x3C;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                rec->timer_8               = 0xF0;
                rec->step_2++;
            }
            break;
        case 4:
            if (--rec->timer_8 == 0)
            {
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            else if (Sce_flag_test(0x60E))
            {
                rec->step_2++;
            }
            break;
        case 5:
            if (Sce_flag_test(0x61B))
            {
                obj->routine_1             = 0;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 6:
            break;
    }
}

void func_80105AA8(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)stcom36_E2_0000[3];
    switch (rec->step_2)
    {
        case 0:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                rec->timer_8 = 0x1E;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            // fall through
        case 4:
            if (Sce_flag_test(0x61C))
            {
                func_80105E2C(3);
                func_80106074(3);
                Sce_flag_on(0x61E);
            }
            break;
    }
}
