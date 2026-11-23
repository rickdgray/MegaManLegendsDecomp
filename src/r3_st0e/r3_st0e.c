#include "common.h"
#include "st0e.h"

void func_8010010C(void)
{
    STAGE_TABLE_3C0 = D_8010F508;
    STAGE_TABLE_5A4 = D_8010F608;
    STAGE_TABLE_10C = D_8010F624;
    STAGE_TABLE_48  = D_8010F6E4;
    STAGE_TABLE_24  = D_8010F748;
    STAGE_TABLE_50  = D_8010F7D0;
}

#ifdef __wasm32__
void func_8010030C(void);
#endif

void func_80100174(void)
{
    void *spawn;

    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->cells = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_PL_BYTE(0x44E)      = 1;
    if (STAGE_GAME.value_78 != 0 && !Sce_flag_test(0x1E))
    {
        STAGE_GAME.value_79 = 0xC;
        STAGE_GAME.value_7A = 0;
    }
    spawn                     = D_8010FC8C[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8010FE18[Game_work.value_51];
    Obj_spawn_tbl_set(spawn, D_800C356D);
    func_800371A0(D_8010FE9C[D_8010FED4[Game_work.value_51]], D_8010FE24[Game_work.value_51]);
    func_8005DC10(D_8010F294[Game_work.value_51]);
    func_8010030C();
}

void func_8010030C(void)
{
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_8010031C(void)
{
    D_8010FF04[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
}

void func_80100370(STAGE_ROOM *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        func_8001DDE4(0);
        return;
    }
    switch (wp->routine_4)
    {
        case 0:
            STAGE_GAME.value_194 = 0;
            wp->routine_4        = 1;
            break;
        case 1:
            if (!Sce_flag_test(0x43))
            {
                func_8001E460(3, 1, 0);
                wp->routine_4 = 2;
            }
            else
            {
                wp->routine_4 = 3;
            }
            break;
        case 2:
            if (Sce_flag_test(0x43))
            {
                func_8001E460(3, 0, 0);
                wp->routine_4 = 3;
            }
            break;
        case 3:
            if (Sce_flag_test(0x1E))
            {
                func_8001DDE4(0x19);
                wp->routine_4 = 0xFF;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_80100474(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_801004A4(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_801004D4(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100504(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100534(void)
{
    if (Sce_flag_test(0x7B0) != 0)
    {
        func_8001DDE4(0);
    }
}

void func_80100564(STAGE_ROOM *wp)
{
    D_8010FF44[wp->routine_4](wp);
}

void func_801005A0(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                Sound_fade_start(0x10);
                wp->routine_5++;
            }
            break;
        case 1:
            if (Sound_fade_flags == 0)
            {
                Player_work.flags_0 &= ~3;
                Obj_work_flag_change(0x56, 5);
                Obj_work_flag_change(0x28, 0x80);
                func_8001E6C0(0, 0, 0);
                wp->reserved09[1] = 2;
                // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
                *(uint32 *)&wp->timer_C = 0;
                D_800BC7F0              = D_8010FF78;
                wp->tbl_A4              = D_80110118;
                Scene_obj_ent_open(&D_8010FF50[0]);
                Scene_obj_ent_open(&D_8010FF50[1]);
                Sce_camera_update();
                Sce_event_update();
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_5++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 3:
            Cd_xa_play_id(0x20000016);
            Fade_start(1);
            Sce_camera_update();
            Sce_event_update();
            wp->routine_5++;
            break;
        case 4:
            if (func_8001D878() != 0 && D_80098A72 == 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_8010FFC8;
                wp->tbl_A4    = D_80110128;
                wp->routine_5 = 0;
                wp->reserved09[1] &= 3;
                wp->routine_4++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
}

void func_801007A8(STAGE_ROOM *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        Fade_start(20);
        wp->routine_5 = 0;
        wp->routine_4++;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (wp->reserved09[1] == 3)
        {
            wp->child_28->routine_0 = 2;
            Fade_start(8);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
        else if (func_8001DE84())
        {
            if (wp->reserved09[1] & 2)
            {
                wp->child_28->routine_0 = 2;
            }
            Fade_start(8);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80100870(STAGE_ROOM *wp)
{
    if (D_80098A72 == 0)
    {
        switch (wp->routine_5)
        {
            case 0:
                func_8003187C(wp->child_24);
                wp->routine_5++;
                break;
            case 1:
                Cd_subcmd(0, 1, 0);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_80042314(&Player_work);
                Player_work.flags_0 |= 3;
                wp->routine_5++;
                break;
            case 2:
                Obj_work_flag_change(0x56, 0xA);
                Sce_flag_on(0x528);
                func_8001E3F0(0xD);
                func_8001D974();
                Sound_fade_start(0x20);
                wp->flags_0 = 0;
                Fade_start(2);
                break;
        }
    }
    if (wp->reserved09[1] != 0)
    {
        Sce_camera_update();
        Sce_event_update();
    }
}

void func_801009AC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 5:
            child            = wp->child_24;
            child->routine_1 = 1;
            child->routine_2 = 0;
            break;
        case 0x43:
            child            = wp->child_24;
            child->routine_1 = 2;
            child->routine_2 = 0;
            break;
        case 0x8D:
            child            = wp->child_24;
            child->routine_1 = 3;
            child->routine_2 = 0;
            break;
        case 0xCD:
            wp->reserved09[1] &= 1;
            wp->child_28->routine_0 = 2;
            break;
        case 0x9:
        case 0x19:
        case 0x29:
        case 0x39:
        case 0x48:
        case 0x55:
            child = wp->child_24;
            Sound_call2(0x90, &child->position);
            break;
    }
}

void func_80100AB8(void)
{
}

void func_80100AC0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_24;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

void func_80100AE8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 5;
        child->routine_2 = 0;
        child->u_C.b.byte_D++;
    }
    if (wp->frame_10 == 0x32)
    {
        child               = wp->child_24;
        child->u_C.b.byte_D = 0;
    }
}

void func_80100B38(ST0E_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    D_80110150[wp->routine_1](wp);
    if (wp->value_D == 0)
    {
        func_80032488(wp);
    }
    func_801010D8((STAGE_OBJ *)wp, face);
}

void func_80100BAC(ST0E_TALKER *wp)
{
    STAGE_FACE16 *face;
    uint32 i;

    face = &wp->face_500;
    wp->flags_0 |= 2;
    wp->rotation.x = 0;
    if (wp->variant_3 == 0)
    {
        wp->rotation.y = 0xC00;
    }
    else
    {
        wp->rotation.y = 0x800;
    }
    wp->scale.words[0] = 0x02000200;
    wp->rotation.z     = 0;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 24; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    wp->pal[21].color |= 0x8000;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 0, 0);
    func_80101090(wp, face, 0);
    wp->part_100[2].value_3  = 0;
    wp->part_100[5].value_3  = 0;
    wp->part_100[16].value_3 = -1;
    wp->part_100[17].value_3 = -1;
    wp->part_100[18].value_3 = -1;
    wp->part_100[19].value_3 = -1;
    wp->routine_2            = 0;
    wp->value_D++;
}

void func_80100CA8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (wp->variant_3 == 0)
    {
        wp->position.x += 3;
    }
    else
    {
        wp->position.z += 3;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
}

void func_80100D88(ST0E_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x10, 0);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x4B)
    {
        func_80101090(wp, face, 1);
    }
}

void func_80100E00(ST0E_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x11, 0);
        wp->part_100[2].value_3  = -1;
        wp->part_100[5].value_3  = -1;
        wp->part_100[16].value_3 = 0;
        wp->part_100[17].value_3 = 0;
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0xBF:
            func_80101090(wp, face, 2);
            break;
        case 0xC9:
            func_80101090(wp, face, 3);
            break;
        case 0xCD:
            func_80101090(wp, face, 4);
            wp->part_100[18].value_3 = 0;
            wp->part_100[19].value_3 = 0;
            break;
    }
}

void func_80100EE8(ST0E_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x12, 0);
        func_80101090(wp, face, 5);
        wp->routine_2++;
    }
}

void func_80100F50(ST0E_TALKER *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE16 *face;

    scene = &Scene_work;
    face  = &wp->face_500;
    if (wp->routine_2 == 0)
    {
        if (wp->variant_3 == 0)
        {
            wp->rotation.y = 0x100;
        }
        else
        {
            wp->rotation.y = 0x400;
        }
        func_800322A8(wp, 0x14, 0);
        wp->part_100[5].value_3  = 0;
        wp->part_100[2].value_3  = 0;
        wp->part_100[18].value_3 = -1;
        wp->part_100[17].value_3 = -1;
        wp->part_100[16].value_3 = -1;
        wp->part_100[19].value_3 = -1;
        func_80101090(wp, face, 8);
        wp->routine_2++;
    }
    switch (scene->value_10)
    {
        case 0x1E:
        case 0xA0:
            func_80101090(wp, face, 6);
            break;
        case 0x46:
        case 0x7C:
            func_80101090(wp, face, 7);
            break;
        case 0x5A:
        case 0x8C:
            func_80101090(wp, face, 8);
            break;
    }
}

void func_80101090(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011024C[index];
    face->eyes_10               = D_80110270[index];
}

void func_801010D8(STAGE_OBJ *wp, STAGE_FACE16 *face)
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
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_0, 0x2A, 0x33, 6));
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
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_6, 0x2A, 0x33, 6));
    }
    face->prev_8 = face->shape_6;
}
