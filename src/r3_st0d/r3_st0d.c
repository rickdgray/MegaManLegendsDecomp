#include "common.h"
#include "st0d.h"

void func_80100184(void)
{
    STAGE_TABLE_3C0 = D_8010BC98;
    STAGE_TABLE_5A4 = D_8010BDF0;
    STAGE_TABLE_10C = D_8010BE2C;
    STAGE_TABLE_48  = D_8010BEC4;
    STAGE_TABLE_24  = D_8010BF1C;
    STAGE_TABLE_50  = D_8010BF30;
}

void func_801001EC(void)
{
    void *spawn;
    sint16 *cells;
    Room_model_init(D_8010BFA4[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 0;
    spawn                     = D_8010C0D4[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_8010C1DC[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_8010C2E4[D_8010C2F4[Game_work.value_51]], D_8010C1F4[Game_work.value_51]);
    func_8005DC10(0);
    *(uint32 *)&D_800989F8.routine_4 = 0;
    func_80100358();
}

void func_80100358(void)
{
    func_8001DEE4();
    func_8001E4C4(D_8010C7D8, D_8010C7E0[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_801003A4(void)
{
    D_8010C3FC[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_801003F8(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C770);
        func_80100BA4(0);
        wp->value_4++;
    }
}

void func_80100454(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C778);
        if (Sce_flag_test(0x31) == 0)
        {
            Sce_flag_on(0x7E1);
        }
        if (Sce_flag_test(0x32) == 0)
        {
            Sce_flag_on(0x7E3);
        }
        wp->routine_5++;
    }
}

void func_801004D8(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C770);
        func_80100BA4(0);
        wp->value_4++;
    }
}

void func_80100534(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C778);
        if (Sce_flag_test(0x31) == 0)
        {
            Sce_flag_on(0x7E1);
        }
        if (Sce_flag_test(0x32) == 0)
        {
            Sce_flag_on(0x7E3);
        }
        wp->routine_5++;
    }
}

void func_801005B8(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            Scene_obj_list_open(D_8010C780);
            func_80100BA4(1);
            wp->routine_4++;
            break;
        case 1:
            if (!(Moji_flag & 0x8000000) && Sce_flag_test(0x606))
            {
                Sce_flag_off(0x606);
                func_80100D54(0xD, 4);
                wp->routine_4++;
            }
            break;
    }
}

void func_80100668(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C778);
        if (Sce_flag_test(0x31) == 0)
        {
            Sce_flag_on(0x7E1);
        }
        if (Sce_flag_test(0x32) == 0)
        {
            Sce_flag_on(0x7E3);
        }
        wp->routine_5++;
    }
}

void func_801006EC(void)
{
    if (Sce_flag_test(0x11) == 0)
    {
        Sce_flag_on(0x11);
        func_8001DDE4(0x20);
        func_8001E390(0x2EA);
    }
}

void func_8010072C(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            Scene_obj_list_open(D_8010C788);
            func_80100BA4(2);
            wp->routine_4 = 1;
            break;
        case 1:
            if (Sce_flag_test(0x605))
            {
                func_8001DDE4(0x22);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_801007B0(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C790);
        if (Sce_flag_test(0x31) == 0)
        {
            Sce_flag_on(0x7E1);
        }
        if (Sce_flag_test(0x32) == 0)
        {
            Sce_flag_on(0x7E3);
        }
        wp->routine_5++;
    }
}

void func_80100834(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C798);
        func_80100BA4(3);
        wp->value_4++;
    }
}

void func_80100890(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C7A0);
        wp->routine_5++;
    }
}

void func_801008E4(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C798);
        func_80100BA4(3);
        wp->value_4++;
    }
}

void func_80100940(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C7A0);
        wp->routine_5++;
    }
}

void func_80100994(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C7A8);
        func_80100BA4(3);
        wp->value_4++;
    }
}

void func_801009F0(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C7B0);
        wp->routine_5++;
    }
}

void func_80100A44(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C7B8);
        func_80100BA4(3);
        wp->value_4++;
    }
}

void func_80100AA0(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C7C0);
        wp->routine_5++;
    }
}

void func_80100AF4(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        Scene_obj_list_open(&D_8010C7C8);
        func_80100BA4(3);
        wp->value_4++;
    }
}

void func_80100B50(STAGE_ROOM *wp)
{
    if (wp->routine_5 == 0)
    {
        Scene_obj_list_open(&D_8010C7D0);
        wp->routine_5++;
    }
}

void func_80100BA4(sint32 arg)
{
    uint32 key        = 0x1100;
    STCOM_SVECTOR pos = {0x100, 0, 0, 0};
    ST0D_ACTOR *obj;

    switch (arg)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            key = 0x1200;
            obj = (ST0D_ACTOR *)Open_SHL_WORK();
            if (obj != NULL)
            {
                obj->be_flag          = MOVE;
                obj->id               = 0x12;
                obj->type             = 3;
                obj->position.x       = 0x700;
                obj->position.y       = -1;
                obj->position_fixed.x = obj->position.x << 16;
                obj->rotation.z       = 0;
                obj->rotation.x       = 0;
                obj->position.z       = -0x4AA;
                obj->position_fixed.y = obj->position.y << 16;
                obj->timer_C          = 0;
                obj->position_fixed.z = obj->position.z << 16;
                if (Sce_flag_test(0x12))
                {
                    obj->work_1 = 0;
                }
                else
                {
                    obj->work_1 = 1;
                }
                obj->rotation.y = 0;
            }
            break;
        case 3:
            key = 0x1200;
            obj = (ST0D_ACTOR *)Open_SHL_WORK();
            if (obj != NULL)
            {
                obj->be_flag          = MOVE;
                obj->id               = 0x12;
                obj->rotation.z       = 0;
                obj->type             = 3;
                obj->position.x       = 0x700;
                obj->position.y       = -1;
                obj->position_fixed.x = obj->position.x << 16;
                obj->position_fixed.y = obj->position.y << 16;
                obj->rotation.x       = 0;
                obj->rotation.y       = 0;
                obj->position.z       = -0x4AA;
                obj->timer_C          = 0;
                obj->work_1           = 2;
                obj->position_fixed.z = obj->position.z << 16;
            }
            break;
    }
    Stage_idx_model_set(Map_cell_get(&pos), key);
}

void func_80100D54(uint8 arg0, uint8 arg1)
{
    D_800C356C = 2;
    D_800C356E = arg0;
    D_800C356F = arg1;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xA;
    D_800C3570 = 2;
}

void func_80100DB4(STAGE_ROOM *wp)
{
    D_8010C840[wp->routine_4](wp);
}

void func_80100DF0(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0  = D_8010C8B0;
            wp->tbl_A4  = D_8010C8FC;
            wp->timer_C = 0;
            Scene_obj_ent_open(D_8010C84C);
            Scene_obj_ent_open(D_8010C84C + 0x14);
            Sound_fade_start(0x10);
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(&Player_work))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                Player_work.be_flag &= ~TRANS;
                wp->reserved09[1] = 0;
                Cd_xa_play_id(0x20000012);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80100F00(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            Sce_camera_update();
            if (func_8001D878())
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_8010C90C;
                wp->tbl_A4 = D_8010CEEC;
                wp->routine_5++;
            }
            break;
        case 1:
            if (wp->routine_8 != 0xFF)
            {
                wp->tbl_A4[1](wp);
                if (func_8001DE84() && !(wp->reserved09[1] & 0x80) && Sound_fade_flags == 0 && D_80098A72 == 0)
                {
                    wp->reserved09[1] |= 1;
                    func_80101548(1, 0);
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            Sce_camera_update();
            break;
    }
    Sce_event_update();
}

void func_80101034(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x56, 0x80);
            func_8003697C();
            Cd_subcmd(0, 1, 0);
            wp->routine_5++;
            break;
        case 1:
            if (D_800C356C_A[0] == 2)
            {
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                func_8001D974();
                wp->flags_0 = 0;
                D_800C356C_A[0]++;
            }
            break;
    }
}

void func_80101110(void)
{
}

void func_80101118(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.x         = 0xAE;
        child->position.y         = -0x18A;
        child->position.z         = -0x105;
        child->position_fixed.v.x = 0xAE0000;
        child->position_fixed.v.y = -0x018A0000;
        child->position_fixed.v.z = -0x01050000;
        child->rotation.y         = 0x400;
        child                     = wp->child_28;
        child->position.x         = 0x56;
        child->position.y         = -0x1DD;
        child->position.z         = -0x14B;
        child->position_fixed.v.x = 0x560000;
        child->position_fixed.v.y = -0x01DD0000;
        child->position_fixed.v.z = -0x014B0000;
        child->rotation.y         = 0x400;
        func_80101548(0, 2);
    }
}

void func_801011BC(void)
{
}

void func_801011C4(void)
{
}

void func_801011CC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.x         = 0x84;
        child->position.y         = -0x1DD;
        child->position.z         = -0x104;
        child->position_fixed.v.x = 0x84 << 16;
        child->position_fixed.v.y = -0x1DD << 16;
        child->position_fixed.v.z = -0x104 << 16;
        child->rotation.y         = 0x5C7;
        Scene_obj_ent_open(D_8010C874);
    }
    if (wp->frame_10 == 0x5A)
    {
        Scene_obj_ent_open(D_8010C89C);
    }
}

void func_80101268(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0)
    {
        func_80031824(wp->position_fixed_prev.x);
    }
}

void func_8010129C(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0x1E)
    {
        wp->routine_2 |= 0x80;
        Fade_start(0xA);
    }
}

void func_801012DC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        Scene_obj_ent_open(D_8010C888);
        Fade_start(2);
    }
    if (D_80098A72 == 0)
    {
        wp->reserved09[1] &= 0x7F;
    }
}

void func_8010134C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.x         = 0x30;
        child->position.z         = -0x122;
        child->position_fixed.v.x = 0x300000;
        child->position_fixed.v.z = -0x01220000;
        child->position.y         = -0x1DD;
        child->position_fixed.v.y = -0x01DD0000;
        child->rotation.y         = 0x4E3;
        child                     = wp->child_28;
        child->position.y         = -0x17D;
        child->position.z         = -0xA0;
        child->position_fixed.v.y = -0x017D0000;
        child->position_fixed.v.z = -0xA00000;
        child->position.x         = 0;
        child->position_fixed.v.x = 0;
        child->rotation.y         = 0xC00;
        child                     = wp->child_2C;
        child->position.x         = -0x16;
        child->position.z         = -0x14C;
        child->position_fixed.v.x = -0x160000;
        child->position_fixed.v.z = -0x014C0000;
        child->position.y         = -0x1DD;
        child->position_fixed.v.y = -0x01DD0000;
        child->rotation.y         = 0x7D0;
        Close_SHL_WORK(wp->child_30);
    }
    if (wp->frame_10 == 0x82)
    {
        child                     = wp->child_28;
        child->position.y         = -0x1DD;
        child->position.z         = -0x7A;
        child->position_fixed.v.y = -0x01DD0000;
        child->position.x         = 0;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.z = -0x7A0000;
        child->rotation.y         = 0;
    }
}

void func_8010146C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->be_flag &= 0xFD;
        child             = wp->child_2C;
        child->rotation.y = 0x872;
    }
}

void func_801014A8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->be_flag |= TRANS;
        child = wp->child_2C;
        child->be_flag &= 0xFD;
    }
}

void func_801014F0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->be_flag &= 0xFD;
    }
    if (wp->frame_10 == 0x3C)
    {
        func_80101548(2, 0);
    }
}

void func_80101548(sint32 mode, uint8 arg)
{
    ST0D_CAMERA *cam;

    cam = &D_800C3558;
    switch (mode)
    {
        case 0:
            D_800C356C = -1;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            break;
        case 1:
            D_800C356C = 1;
            D_800C3571 = 8;
            D_800C3570 = 2;
            break;
        case 2:
            D_800C356C = 1;
            D_800C3571 = 0xA;
            D_800C3570 = 2;
            break;
    }
    cam->mode_16  = 0xD;
    cam->x_8      = 0x708;
    cam->y_A      = -0x81;
    cam->value_17 = arg;
    cam->z_C      = -0x28;
    cam->value_12 = 0;
    cam->value_15 = 0;
}

void func_80101608(STAGE_ROOM *wp)
{
    D_8010CF54[wp->routine_4](wp);
}

void func_80101644(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            Sound_fade_start(0x10);
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_5++;
            }
            break;
        case 2:
            Obj_work_flag_change(0x56, 0x80);
            wp->reserved09[1] = 0x80;
            if (!Sce_flag_test(0x12))
            {
                wp->reserved09[2] = 0;
                Sce_flag_on(0x12);
            }
            else
            {
                wp->reserved09[2] = 1;
            }
            Sce_flag_off(0x604);
            Scene_obj_ent_open(D_8010CF60);
            func_80101E04(5);
            wp->routine_5++;
            break;
        case 3:
            pl->routine_0 = 3;
            pl->value_440 = 0;
            pl->routine_1 = 1;
            pl->value_442 = 0;
            pl->value_444 = 0;
            pl->value_448 = 0;
            pl->pos_438.x = 0x700;
            pl->pos_438.y = -0x25C;
            pl->flags_bd |= 0x10;
            pl->pos_438.z   = -0x4AA;
            pl->fixed_428.x = pl->pos_438.x << 16;
            pl->fixed_428.y = pl->pos_438.y << 16;
            pl->value_74    = 0;
            pl->fixed_428.z = pl->pos_438.z << 16;
            pl->value_76    = 1;
            pl->value_C0    = wp->child_24;
            func_8001E6C0(0, 0, 0);
            wp->timer_C = 0;
            if (wp->reserved09[2] == 0)
            {
                D_800BC7F0 = D_8010D000;
                wp->tbl_A4 = D_8010D04C;
                Scene_obj_ent_open(D_8010CF88);
                Scene_obj_ent_open(D_8010CF88 + 0x14);
                Cd_read_comb(0x8A);
            }
            else
            {
                D_800BC7F0 = D_8010D278;
                wp->tbl_A4 = D_8010D04C;
            }
            Fade_start(2);
            Sce_camera_update();
            Sce_event_update();
            wp->routine_5++;
            break;
        case 4:
            if (func_8001DE84() != 0)
            {
                wp->reserved09[1] |= 1;
            }
            Sce_camera_update();
            Sce_event_update();
            if (wp->reserved09[2] == 0)
            {
                if (D_80098A72 == 0 && Cd_read_sync2() == 0)
                {
                    Cd_xa_play_id(0x20000014);
                    wp->routine_5++;
                }
            }
            else if (D_80098A72 == 0)
            {
                Cd_xa_play_id(0x20000015);
                wp->routine_5++;
            }
            break;
        case 5:
            if (func_8001DE84() != 0)
            {
                wp->reserved09[1] |= 1;
            }
            pl->flags_bd |= 0x20;
            Sce_camera_update();
            Sce_event_update();
            if (func_8001D878() != 0)
            {
                Sce_event_timer_clear();
                if (wp->reserved09[2] == 0)
                {
                    D_800BC7F0 = D_8010D05C;
                    wp->tbl_A4 = D_8010D258;
                }
                else
                {
                    D_800BC7F0 = D_8010D2C4;
                    wp->tbl_A4 = D_8010D430;
                }
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->reserved09[1] &= 0x7F;
                wp->routine_4++;
            }
            break;
    }
}

void func_801019B4(STAGE_ROOM *wp)
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
            Fade_start(8);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80101A60(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x56, 0x80);
            Cd_subcmd(0, 1, 0);
            if (wp->reserved09[1] & 1)
            {
                func_8003697C();
            }
            wp->routine_5++;
            break;
        case 1:
            if (Sound_fade_flags == 0 && D_80098A72 == 0)
            {
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                wp->routine_5++;
            }
            break;
        case 2:
            D_800C356C        = 2;
            D_800C356E        = 0xB;
            D_800C3560        = 0x3200;
            D_800C3562        = -0x262;
            D_800C356F        = 2;
            D_800C3564        = 0x400;
            D_800C356A        = 0x400;
            D_800C356D        = 0;
            D_800C3571        = 0xFF;
            D_800C3570        = 2;
            STAGE_PL.value_76 = 0;
            STAGE_PL.be_flag &= 0xFC;
            wp->flags_0 = 0;
            break;
    }
}

void func_80101BE0(void)
{
}

void func_80101BE8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag &= ~TRANS;
        func_80031824(wp->child_2C);
        func_80031824(wp->child_30);
        Scene_obj_ent_open(D_8010CF74);
        func_80101E04(3);
    }
}

void func_80101C64(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag |= TRANS;
        func_8003187C(wp->child_28);
        Scene_obj_ent_open(&D_8010CFB0[0]);
        Scene_obj_ent_open(&D_8010CFB0[1]);
        wp->child_24->routine_1 = 1;
        func_80101E04(5);
    }
    else if (wp->frame_10 == 0x5A)
    {
        Scene_obj_ent_open(&D_8010CFD8[0]);
        Scene_obj_ent_open(&D_8010CFD8[1]);
    }
    else if (wp->frame_10 == 0xFE)
    {
        wp->reserved09[1] |= 0x80;
        Fade_start(0xA);
    }
}

void func_80101D3C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.be_flag |= TRANS;
        Scene_obj_ent_open(&D_8010CFB0[0]);
        Scene_obj_ent_open(&D_8010CFB0[1]);
        wp->child_24->routine_1 = 1;
        func_80101E04(5);
    }
    else if (wp->frame_10 == 0x5A)
    {
        Scene_obj_ent_open(&D_8010CFD8[0]);
        Scene_obj_ent_open(&D_8010CFD8[1]);
    }
    else if (wp->frame_10 == 0xDD)
    {
        wp->reserved09[1] |= 0x80;
        Fade_start(0xA);
    }
}

void func_80101E04(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 0xD;
    D_800C3560 = 0x700;
    D_800C3562 = -0x25C;
    D_800C3564 = -0x4AA;
    D_800C356F = arg0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80101E74(void)
{
    STAGE_PL.routine_0   = 3;
    STAGE_PL.routine_1   = 1;
    STAGE_PL.pos_438.x   = -0x19F;
    STAGE_PL.pos_438.y   = -0x81;
    STAGE_PL.pos_438.z   = -0xED;
    STAGE_PL.fixed_428.x = -0x19F << 16;
    STAGE_PL.fixed_428.y = -0x81 << 16;
    STAGE_PL.fixed_428.z = -0xED << 16;
    STAGE_PL.value_440   = 0;
    STAGE_PL.value_442   = 0x400;
    STAGE_PL.value_444   = 0;
    STAGE_PL.value_448   = 0;
    STAGE_PL.flags_bd |= 0x10;
}

void func_80101F14(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;

    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                Fade_start(9);
                wp->routine_4++;
            }
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->be_flag = MOVE;
                    obj->id      = 0x55;
                }
                func_80101E74();
                func_8001E6C0(0, 0, 0);
                D_800BC740 = -0x19F << 16;
                D_800BC744 = -0x117 << 16;
                D_800BC748 = -0xED << 16;
                D_800BC770 = 0xC00 << 16;
                D_800BC774 = 0x150 << 16;
                D_800BC778 = 0x200 << 16;
                Fade_start(1);
                wp->routine_4++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
    }
}

void func_80102068(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    D_8010D440[wp->routine_0](wp, &Scene_work, face);
    func_8010288C(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_4E0.face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80102168(STAGE_OBJ *wp, sint32 arg, STAGE_FACE *face)
{
    wp->be_flag = (uint8)wp->be_flag | 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 0x10;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->value_2      = 0;
    func_8010283C(wp, face, 0);
    func_80102864(wp, face, 0);
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80102210(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (ST0D_SCENE_HALF_4(scene) == 0x101)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            Obj_pos_set(wp, 0, -0x24, 0);
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x11;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            if (wp->value_A4 < 0x37)
            {
                Obj_pos_set(wp, 8, -0x18, 0);
            }
            if (scene->u_8.byte[1] == 1)
            {
                if (scene->value_10 == 0x4B)
                {
                    func_8010283C(wp, face, 8);
                }
                else if (scene->value_10 == 0xAA)
                {
                    func_8010283C(wp, face, 9);
                    func_80102864(wp, face, 1);
                    wp->anim_AC   = 0x12;
                    face->value_2 = 0;
                    wp->routine_1++;
                }
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x2D)
            {
                func_8010283C(wp, face, 2);
                func_80102864(wp, face, 2);
                wp->anim_AC   = 0x13;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 3)
            {
                if (scene->value_10 == 0x55)
                {
                    func_80102864(wp, face, 6);
                }
                else if (scene->value_10 == 0xB4)
                {
                    func_8010283C(wp, face, 0xA);
                    func_80102864(wp, face, 2);
                }
            }
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                func_8010283C(wp, face, 0xB);
                func_80102864(wp, face, 9);
                wp->anim_AC   = 0x14;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 5:
            if (wp->value_A4 == 0x19)
            {
                wp->anim_AC      = 0x14;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0x19;
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            face->value_2    = 0x19;
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0x28)
            {
                func_8010283C(wp, face, 3);
                func_80102864(wp, face, 8);
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0x46)
            {
                func_80102864(wp, face, 3);
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                func_8010283C(wp, face, 1);
                func_80102864(wp, face, 4);
                wp->anim_AC   = 0x15;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 8:
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 0x14)
            {
                func_8010283C(wp, face, 0xC);
            }
            else if (scene->u_8.byte[1] == 6 && scene->value_10 == 2)
            {
                wp->anim_AC   = 0;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 9:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0xA)
            {
                wp->anim_AC   = 2;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 10:
            Obj_pos_set(wp, 0x30, 0, 0);
            if (scene->u_8.byte[0] == 1)
            {
                func_8010283C(wp, face, 0);
                func_80102864(wp, face, 0);
                wp->anim_AC   = 0x16;
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_80102628(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->routine_1++;
            break;
        case 1:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                func_8010283C(wp, face, 5);
                func_80102864(wp, face, 5);
                wp->anim_AC = 0x17;
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x14)
            {
                func_80102864(wp, face, 0xB);
                wp->anim_AC = 0x18;
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A4 == 0xB)
            {
                wp->anim_AC      = 0x18;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xB;
                wp->routine_1++;
            }
            break;
        case 4:
            wp->anim_prev_AD = 0xFF;
            face->value_2    = 0xB;
            if (scene->u_8.byte[1] == 3)
            {
                if (scene->value_10 == 0x50)
                {
                    func_80102864(wp, face, 5);
                }
                else if (scene->value_10 == 0x64)
                {
                    func_8010283C(wp, face, 0xD);
                    wp->routine_1++;
                }
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0xA0)
            {
                wp->anim_AC   = 0x1A;
                face->value_2 = 0;
                func_8010283C(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                func_8010283C(wp, face, 7);
                func_80102864(wp, face, 4);
                wp->anim_AC = 0x19;
                wp->routine_1++;
            }
            break;
        case 7:
            break;
    }
}

void func_8010283C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8010D570[index];
}

void func_80102864(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8010D5A8[index];
}

void func_8010288C(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x2A, 0x33, 6));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x7E)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x2A, 0x33, 6));
    }
    face->prev_10 = face->shape_F;
}

void func_801029D4(STAGE_OBJ *wp)
{
    STAGE_FACE *face;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    D_8010D5D8[wp->type](wp, &Scene_work, face);
    func_801036E0(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_4E0.face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

// Called through D_8010D5D8 with (wp, scene, face); face passes through to the second table.
void func_80102AD4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    D_8010D5E0[wp->routine_0](wp, &Scene_work, face);
}

void func_80102B14(STAGE_OBJ *wp, sint32 arg, STAGE_FACE *face)
{
    sint8 i;

    wp->be_flag |= TRANS;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 0x12; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    wp->pal[0x12].color = 0x4210;
    wp->pal[0x13].color = 0xC210;
    wp->anim_AC         = 1;
    wp->value_78        = 0;
    wp->anim_prev_AD    = 0xFF;
    face->value_2       = 0;
    face->timer_0       = 0;
    func_80103690(wp, face, 0);
    func_801036B8(wp, face, 0);
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80102C00(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (ST0D_SCENE_HALF_4(scene) == 0x101)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 1:
                        func_80103690(wp, face, 4);
                        break;
                    case 10:
                        func_801036B8(wp, face, 7);
                        break;
                    case 0x28:
                        func_801036B8(wp, face, 0);
                        break;
                    case 0x32:
                        func_801036B8(wp, face, 7);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 0x6E:
                        func_801036B8(wp, face, 0);
                        break;
                    case 0x78:
                        func_80103690(wp, face, 1);
                        func_801036B8(wp, face, 2);
                        break;
                    case 0x96:
                        wp->anim_AC   = 2;
                        face->value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->value_44.half[0] = 0;
                wp->value_48.half[0] = 0;
                wp->anim_AC          = 3;
                face->value_2        = 0;
                wp->routine_1++;
            }
            break;
        case 4:
            if (wp->value_A4 == 4)
            {
                func_80103690(wp, face, 0);
                func_801036B8(wp, face, 7);
                wp->anim_AC      = 3;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 4;
                wp->routine_1++;
            }
            break;
        case 5:
            wp->anim_prev_AD = 0xFF;
            face->value_2    = 4;
            if (scene->u_8.byte[1] == 1)
            {
                if (scene->value_10 == 0xAF)
                {
                    func_801036B8(wp, face, 0);
                }
            }
            else if (scene->u_8.byte[1] == 3)
            {
                if (scene->value_10 == 1)
                {
                    func_801036B8(wp, face, 0);
                }
                else if (scene->value_10 == 10)
                {
                    func_80103690(wp, face, 5);
                    wp->routine_1++;
                }
            }
            break;
        case 6:
            if (wp->value_A4 == 5)
            {
                wp->value_44.half[0] = 0x56;
                wp->value_48.half[0] = -0x6B;
            }
            else if (wp->value_A4 == 0x14)
            {
                wp->value_44.half[0] = 0;
                wp->value_48.half[0] = 0;
            }
            else if (wp->value_A4 == 0x34)
            {
                wp->value_44.half[0] = 0;
                wp->value_48.half[0] = -0x80;
            }
            else if (wp->value_A7 == -1)
            {
                ST0D_OBJ_SBYTE(wp, 0x143) = -1;
                ST0D_OBJ_SBYTE(wp, 0x147) = -1;
                wp->be_flag &= ~TRANS;
                wp->routine_1++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, wp->value_48.half[0]);
            break;
        case 7:
            if (scene->u_8.value_8 == 1)
            {
                wp->anim_AC = 5;
                wp->be_flag |= TRANS;
                face->value_2 = 0;
                func_80103690(wp, face, 2);
                func_801036B8(wp, face, 3);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_80102F88(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (wp->value_A4 >= 0x11 && wp->value_A7 != -1)
            {
                wp->position.z--;
                wp->position_fixed.v.z = wp->position.z << 16;
            }
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 5:
                        func_801036B8(wp, face, 8);
                        break;
                    case 0x28:
                        func_801036B8(wp, face, 6);
                        break;
                    case 0x32:
                        func_80103690(wp, face, 6);
                        func_801036B8(wp, face, 9);
                        break;
                    case 0x82:
                        func_80103690(wp, face, 3);
                        func_801036B8(wp, face, 4);
                        wp->anim_AC   = 6;
                        face->value_2 = 9;
                        face->timer_0 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (face->timer_0 < 0x26)
            {
                Obj_pos_set(wp, 0x21, 0, 0);
                face->timer_0++;
            }
            else
            {
                wp->anim_AC   = 7;
                face->value_2 = 0;
                face->timer_0 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 0xD7)
            {
                wp->anim_AC   = 8;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 0x19A)
            {
                wp->anim_AC   = 9;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 5:
            if (wp->value_A4 == 0xA)
            {
                func_80103690(wp, face, 7);
                wp->anim_AC      = 9;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xA;
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            face->value_2    = 0xA;
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 0x1C7)
            {
                func_80103690(wp, face, 7);
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 1 && (scene->value_10 == 0x203 || scene->value_10 == 0x230))
            {
                func_80103690(wp, face, 7);
            }
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                func_80103690(wp, face, 2);
                func_801036B8(wp, face, 3);
                wp->anim_AC   = 0xA;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 8:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x64)
            {
                func_80103690(wp, face, 8);
                wp->routine_1++;
            }
            break;
        case 9:
            if (scene->value_10 == 0x78)
            {
                func_801036B8(wp, face, 0xA);
            }
            if (wp->value_A4 == 0x23)
            {
                wp->anim_AC      = 0xA;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0x23;
                wp->routine_1++;
            }
            break;
        case 10:
            wp->anim_prev_AD = 0xFF;
            face->value_2    = 0x23;
            if (scene->u_8.byte[1] == 3)
            {
                switch (scene->value_10)
                {
                    case 0x9B:
                        func_801036B8(wp, face, 3);
                        break;
                    case 0xA5:
                        func_80103690(wp, face, 8);
                        break;
                    case 0xAF:
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 11:
            switch (scene->value_10)
            {
                case 0xB4:
                    func_801036B8(wp, face, 0xA);
                    break;
                case 0xF5:
                    func_801036B8(wp, face, 3);
                    break;
                case 0xFF:
                    func_801036B8(wp, face, 0xA);
                    break;
                case 0x12C:
                    func_801036B8(wp, face, 3);
                    break;
                case 0x145:
                    func_80103690(wp, face, 8);
                    break;
                case 0x140:
                    func_801036B8(wp, face, 0xA);
                    break;
                case 0x159:
                    func_801036B8(wp, face, 3);
                    break;
            }
            break;
    }
}

void func_80103474(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->be_flag |= TRANS;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 1;
            wp->value_78       = 0;
            face->value_2      = 0;
            wp->anim_prev_AD   = 0xFF;
            func_80103690(wp, face, 9);
            func_801036B8(wp, face, 0xB);
            wp->routine_0++;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_AC   = 2;
            face->value_2 = 0;
            wp->routine_0++;
            break;
    }
    switch (scene->value_10)
    {
        case 0x14:
            func_801036B8(wp, face, 0xE);
            break;
        case 0x23:
            func_801036B8(wp, face, 0xB);
            break;
        case 0x32:
            func_801036B8(wp, face, 0xE);
            break;
        case 0x4B:
            func_801036B8(wp, face, 0xB);
            break;
        case 0x4D:
            func_80103690(wp, face, 0xB);
            break;
        case 0x78:
            func_80103690(wp, face, 0xC);
            func_801036B8(wp, face, 0xF);
            break;
        case 0x82:
            func_801036B8(wp, face, 0xD);
            break;
    }
}

void func_80103690(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8010D714[index];
}

void func_801036B8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8010D748[index];
}

void func_801036E0(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x3F)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
    }
    face->prev_D = face->shape_C;
    if (face->eyes_8[face->index_11 + 1] != 0x3F)
    {
        if (face->eyes_8[face->index_11 + 1] == 0x7F)
        {
            face->index_11 = 0;
        }
        else
        {
            face->index_11++;
        }
    }
    face->shape_F = face->eyes_8[face->index_11];
    if (face->shape_F != face->prev_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_80103828(STAGE_OBJ *wp)
{
    STAGE_FACE *face;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    func_8010390C(wp, &Scene_work, face);
    func_80103CB8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010390C(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    STCOM_FIXED_VECTOR step;
    STCOM_SVECTOR move;

    switch (wp->routine_0)
    {
        case 0:
            wp->be_flag |= TRANS;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 1;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            func_80103C90(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            Obj_pos_set(wp, 0x2E, 0, 0);
            if (scene->value_10 >= 0xD)
            {
                wp->rotation.y -= 0x16;
            }
            if (scene->value_10 == 0x20)
            {
                wp->anim_AC = 2;
                wp->routine_0++;
            }
            break;
        case 2:
            if (wp->value_A4 < 0x11)
            {
                func_80030058(&step, wp->rotation.y - 0x1B8, 0x2E, 0, 0);
                func_80030150(&step, &move);
                wp->position.x += move.x;
                wp->position.z += move.z;
                wp->position_fixed.v.x += step.x;
                wp->position_fixed.v.z += step.z;
            }
            if (scene->u_8.byte[1] == 4)
            {
                if (scene->value_10 == 0x69)
                {
                    func_80103C90(wp, face, 1);
                }
                else if (scene->value_10 == 0xB4)
                {
                    wp->anim_AC = 3;
                    wp->routine_0++;
                }
            }
            break;
        case 3:
            if (wp->value_A4 == 0x19)
            {
                func_80103C90(wp, face, 2);
            }
            else if (wp->value_A4 == 0x1A)
            {
                func_80103C90(wp, face, 3);
            }
            if (scene->u_8.value_8 == 1)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 0x78:
                    case 0xB4:
                    case 0x10E:
                        func_80103C90(wp, face, 4);
                        break;
                    case 0x118:
                        wp->routine_0++;
                        break;
                }
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                wp->anim_AC   = 6;
                face->value_2 = 0;
                wp->routine_0++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 2)
            {
                if (scene->value_10 == 0x23 || scene->value_10 == 0x46)
                {
                    func_80103C90(wp, face, 4);
                }
                else if (scene->value_10 == 0x96)
                {
                    wp->routine_0++;
                }
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 0xE6)
            {
                wp->anim_AC   = 4;
                face->value_2 = 0;
                func_80103C90(wp, face, 5);
                wp->routine_0++;
            }
            break;
        case 8:
            if (wp->value_A7 == -1)
            {
                wp->routine_0++;
            }
            break;
        case 9:
            func_80103C90(wp, face, 5);
            wp->routine_0++;
            break;
        case 10:
            break;
    }
}

void func_80103C90(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8010D7B8[index];
}

void func_80103CB8(STAGE_OBJ *wp, STAGE_FACE *face)
{
    if (face->mouth_4[face->index_E + 1] != 0x7E)
    {
        if (face->mouth_4[face->index_E + 1] == 0x7F)
        {
            face->index_E = 0;
        }
        else
        {
            face->index_E++;
        }
    }
    face->shape_C = face->mouth_4[face->index_E];
    if (face->shape_C != face->prev_D)
    {
        Model_mesh_uv_copy(wp->model_88, 0xC000B, Model_uv_cell(face->shape_C, 0x1F, 0x21, 8));
    }
    face->prev_D = face->shape_C;
}

void func_80103D74(STAGE_10C *wp)
{
    D_8010DBCC[wp->type](wp, &wp->x_CC);
}

const STCOM_FIXED_VECTOR D_801000F0 = {0x200, 0x200, 0x200, 0};

void func_80103DB0(STAGE_PROP *wp, uint16 *bob)
{
    STCOM_FIXED_VECTOR scale;

    scale                   = D_801000F0;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010DBE0[wp->routine_0](wp, bob);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
}

void func_80103EDC(ST0D_ACTOR *wp, uint16 *bob)
{
    STAGE_FX *fx;

    wp->be_flag = (uint8)wp->be_flag | 6;
    if (STAGE_GAME.value_50 == 0xD)
    {
        func_8002F9EC(wp, 0);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->color_B4     = 0x808080;
    wp->data_10      = NULL;
    bob[0]           = 0;
    bob[1]           = wp->position.y;
    wp->velocity.v.x = 0;
    wp->velocity.v.y = 0;
    wp->velocity.v.z = 0;
    fx               = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag = MOVE;
        fx->id      = 0x15;
        fx->type    = 0;
        fx->work_0  = wp->work_id;
        fx->timer_D = 0;
        fx->flags |= 0x20;
    }
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag = MOVE;
        fx->id      = 0x15;
        fx->type    = 1;
        fx->work_0  = wp->work_id;
        fx->flags |= 0x20;
    }
    wp->routine_0++;
}

void func_80103FF4(ST0D_ACTOR *wp, uint16 *bob)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    switch (wp->routine_1)
    {
        case 0:
            wp->position.y = bob[1] + ((D_800BBCF8[bob[0] & 0x3F] * 5) >> 12);
            bob[0]++;
            wp->position_fixed.y = wp->position.y << 16;
            break;
        case 1:
            wp->timer_C          = 1;
            wp->position.y       = bob[1];
            wp->position_fixed.y = wp->position.y << 16;
            wp->routine_1++;
            // fall through
        case 2:
            if (wp->velocity.v.x < 0x190)
            {
                wp->velocity.v.x += 8;
            }
            if ((uint32)(scene->value_10 - 0x14) < 0x64)
            {
                wp->rotation.y += 8;
            }
            else if (scene->value_10 == 0x78)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->velocity.v.x < 0x300)
            {
                wp->velocity.v.x += 0x10;
            }
            break;
    }
    Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_80104184(ST0D_LIFT *wp, ST0D_PATH *path)
{
    STCOM_FIXED_VECTOR scale;

    scale                   = D_801000F0;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_8010DBE8[wp->routine_0](wp, &wp->path);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
    func_8010494C(wp, &wp->path);
    wp->hit_BC = 0;
    wp->hit_C4 = 0;
}

void func_801042D0(ST0D_LIFT *wp, ST0D_PATH *path)
{
    STAGE_FX *fx;
    STCOM_SVECTOR *origin[2];

    wp->be_flag = (uint8)wp->be_flag | 6;
    Model_work_init(wp, NULL);
    wp->velocity.v.x = 0x100;
    wp->color_B4     = 0x808080;
    wp->data_10      = NULL;
    wp->velocity.v.y = 0;
    wp->velocity.v.z = 0;
    path->x_10       = wp->velocity.v.x << 16;
    path->z_14       = wp->velocity.v.z << 16;
    path->rot_20     = wp->rotation.y << 16;
    if (wp->type == 1)
    {
        path->step_2C = D_8010D7D0;
    }
    else
    {
        path->step_2C = D_8010DA34;
    }
    func_80104800(wp, path);
    wp->hit_BC   = 0;
    wp->value_C0 = 0;
    wp->hit_C4   = 0;
    wp->value_C8 = 0;
    fx           = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag = MOVE;
        fx->id      = 0x15;
        fx->type    = 0;
        fx->work_0  = wp->work_id;
        fx->timer_D = 0;
        fx->flags |= 0x20;
    }
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag = MOVE;
        fx->id      = 0x15;
        fx->type    = 1;
        fx->work_0  = wp->work_id;
        fx->flags |= 0x20;
    }
    origin[1]     = &wp->position;
    origin[0]     = &wp->position;
    path->grid_28 = func_80108468((STAGE_OBJ *)wp, 2, origin[0]);
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80104444(ST0D_LIFT *wp, ST0D_PATH *path)
{
    sint32 dx;
    sint32 dz;
    sint32 damage;
    sint32 damage2;

    damage  = 0;
    damage2 = 0;
    if (--path->timer_4 <= 0)
    {
        if (path->timer_4 == 0)
        {
            path->x_10   = path->x_6 << 16;
            path->z_14   = path->z_8 << 16;
            path->rot_20 = path->rot_A << 16;
            if (path->next_C < 0)
            {
                if (path->next_C != -1)
                {
                    path->step_2C = &D_8010DB90[path->next_C & 0x7F];
                }
            }
            else
            {
                path->step_2C++;
            }
        }
        if (path->step_2C->flag_0 != 0)
        {
            dx = (path->step_2C->x_2 - wp->position.x) << 16;
            dz = (path->step_2C->z_4 - wp->position.z) << 16;
            wp->position_fixed.v.x += dx;
            wp->position_fixed.v.z += dz;
            wp->position_fixed_prev.x += dx;
            wp->position_fixed_prev.z += dz;
            func_80030150(&wp->position_fixed.v, &wp->position);
            func_80030150(&wp->position_fixed_prev, &wp->position_prev);
            Player_work_obj.position_fixed.v.x += dx;
            Player_work_obj.position_fixed.v.z += dz;
            Player_work_obj.position_fixed_prev.x += dx;
            Player_work_obj.position_fixed_prev.z += dz;
            func_80030150(&Player_work_obj.position_fixed.v, &Player_work_obj.position);
            func_80030150(&Player_work_obj.position_fixed_prev, &Player_work_obj.position_prev);
            path->step_2C++;
        }
        func_80104800(wp, path);
    }
    path->x_10 += path->dx_18;
    wp->velocity.v.x = path->x_10 >> 16;
    path->z_14 += path->dz_1C;
    wp->velocity.v.z = path->z_14 >> 16;
    path->rot_20 += path->drot_24;
    wp->rotation.y = path->rot_20 >> 16;
    Obj_pos_set(wp, wp->velocity.v.x, 0, wp->velocity.v.z);
    if (wp->routine_1 == 0 && Distance_xz(&wp->position.x, &D_8010DC00.x) < 0x40U)
    {
        path->step_2C = D_8010DB90;
        if (D_8010DB90[0].flag_0 != 0)
        {
            path->timer_4 = D_8010DB98;
        }
        else
        {
            func_80104800(wp, path);
        }
        wp->routine_1++;
    }
    if ((wp->hit_BC & 0xFFFFFF) && (wp->hit_BC & 0x1C000000))
    {
        damage = wp->hit_BC & 0xFFFFFF;
    }
    if ((wp->hit_C4 & 0xFFFFFF) && (wp->hit_C4 & 0x1C000000))
    {
        damage2 = wp->hit_C4 & 0xFFFFFF;
    }
    if (damage < damage2)
    {
        damage = damage2;
    }
    if (damage != 0 && STAGE_GAME.value_174 == 0)
    {
        Swing_Camera2(0x1E, 0x400, 0x2800, &wp->position);
        STAGE_GAME.value_5C -= damage;
        if (STAGE_GAME.value_5C < 0)
        {
            STAGE_GAME.value_5C = 0;
        }
        if ((sint16)STAGE_GAME.value_5E / 2 >= STAGE_GAME.value_5C)
        {
            path->grid_28->u_C.flags |= 1;
        }
    }
}

void func_80104800(ST0D_LIFT *wp, ST0D_PATH *path)
{
    ST0D_PATH_STEP *step;
    sint32 turn;

    step          = path->step_2C;
    path->timer_4 = step->frames_8;
    path->x_6     = step->x_2;
    path->z_8     = step->z_4;
    path->rot_A   = step->rot_6;
    path->next_C  = step->next_A;
    path->dx_18   = ((path->x_6 - wp->velocity.v.x) << 16) / path->timer_4;
    path->dz_1C   = ((path->z_8 - wp->velocity.v.z) << 16) / path->timer_4;
    turn          = (path->rot_A - wp->rotation.y) & 0xFFF;
    if (turn > 0x800)
    {
        turn -= 0x1000;
    }
    if (turn < -0x800)
    {
        turn = 0x1000 - turn;
    }
    path->drot_24 = (turn << 16) / path->timer_4;
}

void func_8010494C(ST0D_LIFT *wp, ST0D_PATH *path)
{
    if (wp->be_flag & MOVE)
    {
        path->box_38 = wp->position;
        path->box_30 = path->box_38;
        path->box_38.y -= 0x280;
        func_800341BC(&path->box_30, 0x100, 0, 0, wp->work_id, &wp->hit_BC, 0x2000000, 0, 0);
        func_800341BC(&path->box_38, 0x60, 0, 0, wp->work_id, &wp->hit_C4, 0x2000000, 0, 0);
    }
}

void func_80104A48(STAGE_PROP *wp, uint16 *bob)
{
    STCOM_FIXED_VECTOR scale;

    scale                   = D_801000F0;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010DBF0[wp->routine_0](wp, bob);
    wp->position.y = bob[1] + ((D_800BBCF8[bob[0] & 0x3F] * 5) >> 12);
    bob[0]++;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
}

void func_80104BE0(ST0D_ACTOR *wp, uint16 *bob)
{
    wp->be_flag = (uint8)wp->be_flag | 6;
    if (STAGE_GAME.value_50 == 0xD)
    {
        func_8002F9EC(wp, 0);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->color_B4     = 0x808080;
    wp->data_10      = D_8010DC08;
    wp->timer_C      = 0;
    wp->work_2       = 1;
    bob[0]           = 0;
    bob[1]           = wp->position.y;
    wp->velocity.v.x = 0;
    wp->velocity.v.y = 0;
    wp->velocity.v.z = 0;
    wp->routine_1    = 0;
    wp->routine_0++;
}
