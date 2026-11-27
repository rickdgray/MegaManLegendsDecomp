#include "common.h"
#include "st15.h"

// Installs the stage's slot routine tables.
void func_80100034(void)
{
    STAGE_TABLE_3C0 = D_80102480;
    STAGE_TABLE_5A4 = D_80102604;
    STAGE_TABLE_10C = D_80102634;
    STAGE_TABLE_48  = D_80102638;
    STAGE_TABLE_24  = D_8010263C;
    STAGE_TABLE_50  = D_80102650;
}

// Sets up the current room: models, map, spawns.
void func_8010009C(void)
{
    void *spawn;
    sint16 *cells;

    Room_model_init(D_80102654[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_PL_BYTE(0x44E)      = 0;
    spawn                     = D_801026C0[Game_work.value_51];
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    STAGE_MAP_WORK_PTR->exits = D_801026E0[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_80102738[D_80102760[Game_work.value_51]], D_801026E8[Game_work.value_51]);
    func_8005DC10(0);
    func_80100200();
}

void func_80100200(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script.
void func_80100210(void)
{
    D_80102778[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100264(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DDE4(0x4A);
        wp->routine_4++;
    }
}

void func_801002B0(void)
{
}

// Sets the script camera.
void func_801002B8(uint8 mode)
{
    D_800C356C = -1;
    D_800C356E = 0x15;
    D_800C356F = mode;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_8010031C(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_801002B8(1);
        child = wp->child_34;
        child->be_flag |= TRANS;
        child = wp->child_2C;
        child->be_flag |= TRANS;
        child = wp->child_38;
        child->be_flag |= TRANS;
    }
}

void func_801003A0(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;
    STAGE_WORK *object;

    if (wp->frame_10 == 0)
    {
        func_801002B8(0);
        child = wp->child_34;
        child->be_flag &= ~TRANS;
        child = wp->child_2C;
        child->be_flag &= ~TRANS;
        child            = wp->child_38;
        child->routine_1 = 1;
        child->be_flag &= ~TRANS;
        object                     = wp->child_24;
        object->position_fixed.v.x = 0xFF380000;
        object->routine_1          = 0;
        object->routine_2          = 0;
        object->position_fixed.v.z = 0xFF9C0000;
        object->be_flag |= TRANS;
        object = wp->child_28;
        object->be_flag |= TRANS;
        child = wp->child_30;
        child->be_flag |= TRANS;
    }
    if (wp->frame_10 == 0x96)
    {
        object            = wp->child_24;
        object->routine_1 = 1;
        object->routine_2 = 0;
    }
}

void func_801004A0(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;
    STAGE_WORK *other;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xD2)
    {
        other            = wp->child_30;
        other->routine_1 = 0;
        other->routine_2 = 0;
        other->value_110 = 9;
    }
}

void func_801004EC(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x29)
    {
        child            = wp->child_24;
        child->routine_1 = 3;
        child->routine_2 = 0;
    }
}

void func_80100534(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

void func_8010055C(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_801002B8(1);
        child = wp->child_24;
        child->be_flag &= ~TRANS;
        child = wp->child_28;
        child->be_flag &= ~TRANS;
        child = wp->child_30;
        child->be_flag &= ~TRANS;
        child = wp->child_34;
        child->be_flag |= TRANS;
        child = wp->child_2C;
        child->be_flag |= TRANS;
    }
}

void func_80100610(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_801002B8(0);
        child            = wp->child_24;
        child->routine_1 = 5;
        child->routine_2 = 0;
        child->rot_y_56  = 0xA28;
        child->be_flag |= TRANS;
        child = wp->child_28;
        child->be_flag |= TRANS;
        child = wp->child_30;
        child->be_flag |= TRANS;
        child = wp->child_34;
        child->be_flag &= ~TRANS;
        child = wp->child_2C;
        child->be_flag &= ~TRANS;
    }
    if (wp->frame_10 == 0x46)
    {
        child            = wp->child_24;
        child->routine_1 = 6;
        child->routine_2 = 0;
        child->be_flag |= TRANS;
    }
    if (wp->frame_10 == 0x73)
    {
        child            = wp->child_24;
        child->routine_1 = 7;
        child->routine_2 = 0;
        child->be_flag |= TRANS;
    }
    if (wp->frame_10 == 0xAA)
    {
        child            = wp->child_24;
        child->routine_1 = 8;
        child->routine_2 = 0;
        child->be_flag |= TRANS;
    }
}

void func_80100758(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child->work_1    = 1;
        child            = wp->child_30;
        child->be_flag &= 0xFD;
    }
    if (wp->frame_10 == 0xA)
    {
        child         = wp->child_28;
        child->work_1 = 0;
    }
}

void func_801007B8(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
}

void func_801007E0(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    if (wp->frame_10 == 0)
    {
        func_801002B8(1);
        child = wp->child_24;
        child->be_flag &= ~TRANS;
        child = wp->child_28;
        child->be_flag &= ~TRANS;
        child = wp->child_30;
        child->be_flag &= ~TRANS;
        child = wp->child_34;
        child->be_flag |= TRANS;
        child->routine_2++;
        child = wp->child_2C;
        child->be_flag |= TRANS;
        child->routine_2++;
    }
    if (wp->frame_10 == 0x352)
    {
        Fade_start(0xB);
    }
}

void func_801008BC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                D_800BBA90[0].flags_0 &= 0xFC;
                D_800BBAC8 |= 3;
                Obj_work_flag_change(0x56, 0x80);
                Fade_start(2);
                wp->timer_C = 0;
                wp->routine_5++;
            }
            break;
        case 1:
            if (wp->timer_C == 0x12C)
            {
                Fade_start(10);
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                D_800BBA90[1].flags_0 &= 0xFC; // model 1's flags
                D_800BBB00 |= 3;
                Fade_start(2);
                wp->timer_C = 0;
                wp->routine_5++;
                func_80067B7C();
                MojiTaskExec(0, D_8008CE90, -1);
            }
            break;
        case 3:
            if (wp->timer_C == 0x12C)
            {
                wp->routine_5++;
            }
            break;
        case 4:
            if (wp->timer_C == 0x5DC || (D_800C0C2A & 8))
            {
                Fade_start(11);
                wp->routine_5++;
            }
            break;
        case 5:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
                MojiTaskKill();
            }
            break;
    }
    wp->timer_C++;
}

void func_80100A84(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    Sce_event_set(D_80102A78, D_801027B8);
    for (i = 0; i < 7; i++)
    {
        Scene_obj_ent_open(&D_80102A00[i]);
    }
}

void func_80100AF4(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80100B34(STAGE_ROOM_WORK *wp)
{
    STCOM_PL_WORK *pl;

    switch (wp->routine_4)
    {
        case 0:
            pl = &Player_work;
            if (func_80042238(pl) != 0)
            {
                pl->be_flag &= 0xFC;
                Cd_xa_play_id(0x2001000A);
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 1;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                Fade_start(2);
                wp->routine_4++;
            }
            break;
        case 3:
            func_80100A84(wp);
            wp->routine_4++;
            // fall through
        case 4:
        case 5:
            func_80100AF4(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 5 && D_80098A72 == 0)
            {
                Cd_subcmd(0, 1, 0);
                wp->flags_0 = 0;
                Player_work.be_flag |= MOVE;
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                *(uint32 *)&D_80098AA8[0] = 0;
                STAGE_GAME_FLAGS_82 &= 0x7F;
                func_80012F78(D_80013420);
            }
            break;
    }
}

void func_80100CC8(STAGE_WORK *wp)
{
    D_801084F8[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(D_801084F4[0]->id, 0x33, 0x37, 5));
}

void func_80100D24(STAGE_WORK *wp)
{
    D_80108500[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(D_801084FC[0]->id, 0x33, 0x37, 5));
}

void func_80100D80(STAGE_WORK *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_801084F4_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801084F4[0] += count;
            func_80100CC8(wp);
        }
        else if (++D_801084F8[0] == p->count)
        {
            D_801084F4_S = p + 1;
            func_80100CC8(wp);
        }
    }
    p     = D_801084FC_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_801084FC[0] += count;
            func_80100D24(wp);
        }
        else if (++D_80108500[0] == p->count)
        {
            D_801084FC_S = p + 1;
            func_80100D24(wp);
        }
    }
}

void func_80100EA8(STAGE_WORK *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_80108504.cue_0->u.end != 0xFF && D_80108504.cue_0->u.scene == scene->u_8.value_8 && D_80108504.cue_0->line == scene->value_1C)
    {
        D_801084F4[0] = D_80102BFC[D_80108504.cue_0->index];
        func_80100CC8(wp);
        D_80108504.cue_0++;
    }
    if (D_80108504.cue_4->u.end != 0xFF && D_80108504.cue_4->u.scene == scene->u_8.value_8 && D_80108504.cue_4->line == scene->value_1C)
    {
        D_801084FC[0] = D_80102C20[D_80108504.cue_4->index];
        func_80100D24(wp);
        D_80108504.cue_4++;
    }
    func_80100D80(wp);
}

void func_80100FF0(STAGE_WORK *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    D_80108504.cue_0   = D_80102C54;
    D_80108504.cue_4   = D_80102C8C;
    wp->routine_0++;
}

void func_80101064(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801010B0(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_801010FC(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
}

void func_80101148(STAGE_WORK *wp)
{
    D_80102CE8[wp->routine_1](wp);
    if (wp->work_1 == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_80100EA8(wp);
}

void func_801011B8(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80100FF0(wp);
    }
    func_80101148(wp);
}

void func_801011FC(STAGE_WORK *wp)
{
    D_80108510[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(D_8010850C[0]->id, 0x2A, 0x40, 6));
}

void func_80101258(STAGE_WORK *wp)
{
    D_80108518[0] = 0;
    Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(D_80108514[0]->id, 0x2A, 0x40, 6));
}

void func_801012B4(STAGE_WORK *wp)
{
    STAGE_MOUTH *p;
    sint16 count;

    p     = D_8010850C_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_8010850C[0] += count;
            func_801011FC(wp);
        }
        else if (++D_80108510[0] == p->count)
        {
            D_8010850C_S = p + 1;
            func_801011FC(wp);
        }
    }
    p     = D_80108514_S;
    count = p->count;
    if (count != 0)
    {
        if (count < 0)
        {
            D_80108514[0] += count;
            func_80101258(wp);
        }
        else if (++D_80108518[0] == p->count)
        {
            D_80108514_S = p + 1;
            func_80101258(wp);
        }
    }
}

void func_801013DC(STAGE_WORK *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (D_8010851C.cue_0->u.end != 0xFF && D_8010851C.cue_0->u.scene == scene->u_8.value_8 && D_8010851C.cue_0->line == scene->value_1C)
    {
        D_8010850C[0] = D_80102DD0[D_8010851C.cue_0->index];
        func_801011FC(wp);
        D_8010851C.cue_0++;
    }
    if (D_8010851C.cue_4->u.end != 0xFF && D_8010851C.cue_4->u.scene == scene->u_8.value_8 && D_8010851C.cue_4->line == scene->value_1C)
    {
        D_80108514[0] = D_80102DD0[D_8010851C.cue_4->index];
        func_80101258(wp);
        D_8010851C.cue_4++;
    }
    func_801012B4(wp);
}

void func_80101524(STAGE_WORK *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    D_8010851C.cue_0   = D_80102E04;
    D_8010851C.cue_4   = D_80102E04;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_801015A0(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801015EC(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_80101638(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->timer_C = 0;
            func_800322A8(wp, 3, 0);
            wp->routine_2++;
            break;
        case 1:
            if (++wp->timer_C == 0x18)
            {
                wp->routine_2++;
            }
            Obj_pos_set(wp, 0x1A, 0, 0);
            break;
    }
}

void func_801016E4(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
}

void func_80101730(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
    }
}

void func_8010177C(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->routine_2++;
    }
}

void func_801017C8(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        wp->routine_2++;
    }
}

void func_80101814(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 8, 0);
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 == 4)
            {
                func_800322A8(wp, 9, 0);
                wp->routine_2++;
            }
            break;
    }
}

void func_80101898(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0xA, 0);
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 == 0x1F)
            {
                func_800322A8(wp, 0xB, 0);
                wp->routine_2++;
            }
            break;
    }
}

void func_8010191C(STAGE_WORK *wp)
{
    D_80102E88[wp->routine_1](wp);
    if (wp->work_1 == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
    func_801013DC(wp);
}

void func_8010198C(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80101524(wp);
    }
    func_8010191C(wp);
}

void func_801019D0(STAGE_WORK *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_80101A20(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x10, 0);
        wp->routine_2++;
    }
}

void func_80101A6C(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}

void func_80101AB8(STAGE_WORK *wp)
{
    D_80102EAC[wp->routine_1](wp);
    if (wp->work_1 == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_80101B20(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_801019D0(wp);
    }
    func_80101AB8(wp);
}

void func_80101B64(STAGE_WORK *wp)
{
    Obj_pos_set(wp, 0x100, 0, 0);
}

void func_80101B8C(void)
{
}

void func_80101B94(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0xC800C8;
        wp->scale.words[1] = 0x421000C8;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
    }
    D_80102EB4[wp->routine_1](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_80101C40(STAGE_WORK *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_80101C90(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 1, 0);
            wp->routine_2++;
            break;
        case 1:
            break;
        case 2:
            wp->position_fixed.v.z += -0x10000;
            break;
    }
    wp->position_fixed.v.y = rsin(++wp->timer_C << 5) * 0xA0;
}

void func_80101D4C(STAGE_WORK *wp)
{
    D_80102EBC[wp->routine_1](wp);
    if (wp->work_1 == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_80101DB4(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80101C40(wp);
    }
    func_80101D4C(wp);
}

void func_80101DF8(STAGE_WORK *wp)
{
    sint32 i;
    sint32 color;

    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    func_800322A8(wp, 0, 0);
    color = 0x4210;
    for (i = 5; i >= 0; i--)
    {
        wp->pal[i].color = color;
    }
    wp->u_E.angle = 0;
    wp->pal[3].color |= 0x8000;
    wp->routine_0++;
}

void func_80101E80(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0, 0);
            wp->routine_2++;
            break;
        case 1:
            break;
        case 2:
            wp->position_fixed.v.z += -0x10000;
            break;
    }
    wp->position_fixed.v.y = rsin(++wp->timer_C << 5) * 0xA0;
}

void func_80101F3C(STAGE_WORK *wp)
{
    D_80102EC0[wp->routine_1](wp);
    if (wp->work_1 == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_80101FA4(STAGE_WORK *wp)
{
    STAGE_MATRIX m;
    STAGE_MATRIX copy;

    if (wp->routine_0 == 0)
    {
        func_80101DF8(wp);
    }
    func_80101F3C(wp);
    wp->u_E.angle += 4;
    STAGE_MATRIX_IDENTITY(m.w);
    RotMatrixY(wp->u_E.angle, &m.m);
    copy = m;
    MulMatrix(&wp->matrix_248.m, &copy.m);
    MulMatrix(&wp->matrix_288.m, &m.m);
}
