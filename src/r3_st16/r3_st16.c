#include "common.h"
#include "st16.h"

// The stage id word (0x29): the first object's rodata starts with it, which sets its jump tables'
// 8-byte alignment. Top-level asm, so that cc1 emits it before the jump tables.
INCLUDE_RODATA("asm/r3_st16/nonmatchings/r3_st16", D_80100000);

// Installs the stage's slot routine tables.
void func_8010009C(void)
{
    STAGE_TABLE_3C0      = D_801033D0;
    STAGE_TABLE_5A4      = D_80103470;
    STAGE_TABLE_10C      = D_8010348C;
    STAGE_TABLE_48       = D_80103490;
    STAGE_TABLE_24       = D_801034AC;
    STAGE_TABLE_50       = D_801034C0;
    STAGE_PL_BYTE(0x170) = 0;
}

// Sets up the current room: models, map, spawns.
void func_8010010C(void)
{
    void *spawn;
    sint16 *cells;

    Room_model_init(D_801034C4[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 0;
    spawn                     = D_80103570[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_80103594[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_80103618[D_80103698[Game_work.value_51]], D_801035A0[Game_work.value_51]);
    func_8005DC10(0);
    func_80100270();
}

void func_80100270(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_80100280(void)
{
    D_801036BC[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_801002D4(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DDE4(0x31);
        wp->routine_4++;
    }
}

void func_80100320(void)
{
}

void func_80100328(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DDE4(0x32);
        wp->routine_4++;
    }
}

// Sets the script camera.
void func_80100374(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 0x10;
    D_800C356F = mode;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_801003D8(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;
    STAGE_WORK *other;
    sint32 mask = ~2;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->be_flag &= mask;
        other = wp->child_24;
        child->be_flag &= mask; // repeated in retail after loading child_24
        other->routine_1 = 1;
        other->routine_2 = 0;
    }
}

void func_80100424(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_80100374(1);
        wp->child_24->be_flag &= ~(MOVE | TRANS);
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 1;
        child->be_flag |= TRANS;
    }
}

void func_80100498(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 8)
    {
        child            = wp->child_28;
        child->routine_1 = 2;
        child->routine_2 = 1;
        child->be_flag |= TRANS;
    }
}

void func_801004D0(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_80100374(0);
        wp->child_28->be_flag &= ~(MOVE | TRANS);
        child = wp->child_2C;
        child->be_flag &= ~TRANS;
        child            = wp->child_24;
        child->routine_0 = 2;
        child->routine_1 = 1;
        child->routine_2 = 2;
        child->be_flag |= MOVE | TRANS;
    }
}

void func_80100560(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->routine_5 == 0 && D_80098A72 == 0)
    {
        Fade_start(3);
        func_80100374(2);
        child            = wp->child_24;
        child->routine_0 = 2;
        child->routine_1 = 1;
        child->routine_2 = 5;
        wp->routine_5++;
    }
}

void func_801005E4(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80103738;
    wp->tbl_A4 = D_801038C8;
    for (i = 0; i < 3; i++)
    {
        Scene_obj_ent_open(&D_801036FC[i]);
    }
}

void func_80100668(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801006A8(STAGE_ROOM_WORK *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            Sound_seq_stop_all();
            D_8010E050     = (rand() >> 8) & 3;
            scene->value_A = 0;
            switch (D_8010E050)
            {
                case 0:
                    Cd_xa_play_id(0x20010010);
                    break;
                case 2:
                    scene->value_A = 0xFF;
                    Cd_xa_play_id(0x20010012);
                    break;
                case 1:
                case 3:
                    Cd_xa_play_id(0x20010011);
                    break;
            }
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 2;
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
            Fade_start(2);
            wp->routine_4++;
            // fall through
        case 5:
            func_801005E4(wp);
            wp->routine_4++;
            // fall through
        case 6:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(10);
                wp->routine_4 = 10;
                Sce_flag_on(0x25);
            }
            // fall through
        case 10:
            func_80100668(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                D_800C356C            = 2;
                D_800C356E            = 0x13;
                D_800C356F            = 0xB;
                D_800C3560            = -0x40;
                D_800C3562            = -1;
                D_800C3564            = 0xC0;
                D_800C356A            = 0x800;
                D_800C3571            = 0xFF;
                D_800C356D            = 0;
                D_800C3570            = 2;
                wp->flags_0           = 0;
                STAGE_GAME_BYTE(0x7B) = 1;
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
            }
            break;
    }
}

// Sets the script camera.
void func_80100970(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 0xA;
    D_800C356F = mode;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_801009D4(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child->be_flag |= MOVE | TRANS;
    }
}

void func_80100A08(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_80100970(1);
        child = wp->child_24;
        child->be_flag &= ~(MOVE | TRANS);
        child = wp->child_28;
        child->be_flag |= TRANS;
    }
}

void func_80100A74(void)
{
}

void func_80100A7C(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (wp->frame_10 == 0)
    {
        func_80100970(2);
        child            = wp->child_24;
        child->routine_1 = 2;
        child->routine_2 = 0;
        child->be_flag |= MOVE | TRANS;
        wp->child_28->be_flag &= ~TRANS;
        child = wp->child_2C;
        child->be_flag &= ~TRANS;
        pl->be_flag &= 0xFE;
    }
}

void func_80100B24(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->routine_5 == 0)
    {
        if (STAGE_GAME_VALUE_52 == 7 && Sce_flag_test(0x21) != 0)
        {
            *(uint8 *)wp->tbl_A4 = 0xFF;
            return;
        }
        if (D_80098A72 == 0)
        {
            Fade_start(3);
            func_80100970(0);
            child            = wp->child_24;
            child->routine_1 = 3;
            child->routine_2 = 0;
            child->be_flag |= MOVE | TRANS;
            wp->routine_5++;
        }
    }
}

void func_80100BDC(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    D_800BC7F0 = D_80103934;
    wp->tbl_A4 = D_80103AD4;
    for (i = 0; i < 3; i++)
    {
        Scene_obj_ent_open(&D_801038F8[i]);
    }
}

void func_80100C44(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80100C84(STAGE_ROOM_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            Sound_seq_stop_all();
            switch ((rand() >> 8) & 1)
            {
                case 0:
                    Cd_xa_play_id(0x2001001C);
                    break;
                case 1:
                    Cd_xa_play_id(0x2001001D);
                    break;
            }
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 2;
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
            Fade_start(2);
            wp->routine_4++;
            // fall through
        case 5:
            func_80100BDC(wp);
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
            func_80100C44(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                if (STAGE_GAME_VALUE_52 == 7 && Sce_flag_test(0x21) != 0)
                {
                    D_800C356E = 0x17;
                    D_800C356F = 3;
                    D_800C3560 = 0;
                    D_800C3562 = 0;
                    D_800C3564 = 0;
                    D_800C356A = 0;
                }
                else
                {
                    D_800C356E = 0x1B;
                    D_800C356F = 6;
                    D_800C3560 = -0x40;
                    D_800C3562 = -1;
                    D_800C3564 = 0xC0;
                    D_800C356A = 0x800;
                }
                D_800C356C            = 2;
                D_800C356D            = 0;
                D_800C3571            = 0xFF;
                D_800C3570            = 2;
                wp->flags_0           = 0;
                STAGE_GAME_BYTE(0x7B) = 0;
                pl->be_flag |= MOVE;
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
            }
            break;
    }
}

void func_80100F60(void)
{
}
