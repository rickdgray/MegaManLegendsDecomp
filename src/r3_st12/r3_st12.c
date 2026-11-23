#include "common.h"
#include "st12.h"

// Installs the stage's slot routine tables.
void func_801001D4(void)
{
    STAGE_TABLE_3C0 = D_80107E38;
    STAGE_TABLE_5A4 = D_80107FC4;
    STAGE_TABLE_10C = D_80107FE0;
    STAGE_TABLE_48  = D_80108034;
    STAGE_TABLE_24  = D_8010804C;
    STAGE_TABLE_50  = D_80108050;
}

// Sets up the current room: models, map, spawns.
void func_8010023C(void)
{
    Room_model_init(D_801080D4[Game_work.value_51]);
    STAGE_MAP_AREA_SP.w  = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_AREA_SP.h  = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_AREA_SP.x0 = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_AREA_SP.z0 = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_AREA_SP.x1 = STAGE_MAP_AREA_SP.x0 + STAGE_MAP_AREA_SP.w;
    STAGE_MAP_AREA_SP.z1 = STAGE_MAP_AREA_SP.z0 + STAGE_MAP_AREA_SP.h;
    STAGE_MAP_INFO       = STAGE_CELL_INFO;
    STAGE_MAP_CELLS      = STAGE_MAP_TBL[Game_work.value_51].cells;
    if (Game_work.value_51 == 0)
    {
        Sce_flag_on(0x31F);
    }
    STAGE_PL_BYTE(0x44E) = 0;
    STAGE_MAP_EXITS      = D_801081D4[Game_work.value_51];
    Obj_spawn_tbl_set(D_80108160[Game_work.value_51], D_800C356D);
    func_800371A0(D_801082B0[D_80108330[Game_work.value_51]], D_801081E8[Game_work.value_51]);
    func_8005DC10(0);
    func_801003B8();
}

void func_801003B8(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script (the second set once scene flag 0x1FF is set).
void func_801003C8(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80108410[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_801083D0[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100468(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_80108798);
        wp->routine_4++;
    }
}

void func_801004BC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        Scene_obj_list_open(D_801087A0);
        wp->routine_4++;
    }
}

void func_80100510(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            Scene_obj_list_open(D_801087A0);
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x21) && !Sce_flag_test(0x6A))
            {
                func_8001E20C(0);
                func_8001DDE4(0x33);
                wp->routine_4++;
                Sce_flag_on(0x6A);
            }
            break;
        case 2: // done (the empty case shapes retail's compare tree)
            break;
    }
}

void func_801005BC(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    if (wp->routine_4 == 0)
    {
        for (i = 0; i < 4; i++)
        {
            Stage_idx_model_set(Map_cell_get(&D_801087C0[i]), D_801087E0[i]);
        }
        Scene_obj_list_open(D_801087A8);
        wp->routine_4++;
    }
}

void func_80100664(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    if (wp->routine_4 == 0)
    {
        for (i = 0; i < 4; i++)
        {
            Stage_idx_model_set(Map_cell_get(&D_801087C0[i]), D_801087E0[i]);
        }
        Scene_obj_list_open(D_801087B0);
        wp->routine_4++;
    }
}

void func_8010070C(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    if (wp->routine_4 == 0)
    {
        for (i = 0; i < 4; i++)
        {
            Stage_idx_model_set(Map_cell_get(&D_801087C0[i]), D_801087E0[i]);
        }
        Scene_obj_list_open(D_801087B8);
        wp->routine_4++;
    }
}

sint32 func_801007B4(void)
{
    if (!Sce_flag_test(0x21) || Sce_flag_test(0x6A) || STAGE_GAME_VALUE_52 != 7)
    {
        if (!Sce_flag_test(0x238))
        {
            func_8001EB98(D_801087F0);
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80100828(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 0xC;
    D_800C356F = arg0;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
}

void func_80100878(void)
{
}

void func_80100880(STAGE_ROOM *wp)
{
    STAGE_FX *fx;

    if (wp->frame_10 == 0)
    {
        func_80100828(1);
    }
    if (wp->frame_10 == 0xB)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->y_1E    = -0x14D;
            fx->timer_D = 0;
            fx->x_1C    = 0;
            fx->z_20    = -0x370;
        }
    }
}

void func_80100910(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_80100828(2);
        child = wp->child_2C;
        child->flags_0 |= 6;
        child = wp->child_30;
        child->flags_0 |= 6;
        child = wp->child_34;
        child->flags_0 |= 6;
        child = wp->child_38;
        child->flags_0 |= 6;
        child = wp->child_44;
        child->flags_0 |= 6;
        child = wp->child_40;
        child->flags_0 |= 6;
        child = wp->child_3C;
        child->flags_0 |= 6;
    }
    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_30;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_34;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_38;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_44;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_40;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_3C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80100A74(void)
{
}

void func_80100A7C(void)
{
}

void func_80100A84(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_80100828(3);
        child          = wp->child_2C;
        child->flags_0 = 0;
        child          = wp->child_30;
        child->flags_0 = 0;
        child          = wp->child_34;
        child->flags_0 = 0;
        child          = wp->child_38;
        child->flags_0 = 0;
        child          = wp->child_44;
        child->flags_0 = 0;
        child          = wp->child_40;
        child->flags_0 = 0;
        child          = wp->child_3C;
        child->flags_0 = 0;
        if (wp->frame_10 == 0)
        {
            child            = wp->child_24;
            child->routine_1 = 1;
            child->routine_2 = 0xA;
            child->flags_0 |= 6;
            child            = wp->child_28;
            child->routine_1 = 1;
            child->routine_2 = 0xA;
            child->flags_0 |= 6;
        }
    }
}

void func_80100B60(STAGE_ROOM *wp)
{
    uint32 i;

    if (wp->frame_10 == 0)
    {
        wp->child_24->flags_0 = 0;
        wp->child_28->flags_0 = 0;
        for (i = 0; i < 4; i++)
        {
            Stage_idx_model_set(Stage_map_cell_get(0, &D_80108AC0[i]), D_80108AE0[i]);
        }
        func_80100828(0);
    }
}

void func_80100BF8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_80100828(4);
        child = wp->child_48;
        child->flags_0 |= 6;
        child = wp->child_4C;
        child->flags_0 |= 6;
        child = wp->child_50;
        child->flags_0 |= 6;
    }
}

void func_80100C7C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0xA)
    {
        child            = wp->child_48;
        child->routine_1 = 1;
        child->routine_2 = 0x14;
        child            = wp->child_4C;
        child->routine_1 = 1;
        child->routine_2 = 0x15;
        child            = wp->child_50;
        child->routine_1 = 1;
        child->routine_2 = 0x16;
    }
}

void func_80100CC4(STAGE_ROOM *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_801088F4;
    wp->tbl_A4 = D_80108AF0;
    for (i = 0; i < 0xC; i++)
    {
        Scene_obj_ent_open(&D_80108804[i]);
    }
}

void func_80100D48(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80100D88(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
                pl->flags_0 ^= 2;
            }
            break;
        case 1:
            Sound_seq_stop_all();
            func_8001B314();
            Cd_xa_play_id(0x20010015);
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 5;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 4:
            Fade_start(3);
            wp->routine_4++;
            // fall through
        case 5:
            func_80100CC4(wp);
            wp->routine_4++;
            // fall through
        case 6:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(10);
                wp->routine_4 = 10;
            }
            // fall through
        case 10:
            func_80100D48((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                D_800C356C      = 2;
                D_800C356E      = 0x13;
                D_800C356F      = 2;
                D_800C3560      = 0x100;
                D_800C3562      = -0x61;
                D_800C3564      = 0x80;
                D_800C356A      = 0x800;
                D_800C356D      = 0;
                D_800C3571      = 0xFF;
                D_800C3570      = 2;
                wp->flags_0     = 0;
                pl->fixed_428.x = 0xFE << 16;
                pl->fixed_428.y = -0x61 << 16;
                pl->fixed_428.z = 0xBF << 16;
                pl->flags_0 |= 3;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->value_440 = 0;
                pl->value_442 = 0x804;
                pl->value_444 = 0;
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
            }
            break;
    }
}
