#include "common.h"
#include "st06.h"

void func_80115F34(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_801255A0[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    func_80116AD4(wp, face);
}

void func_80115FA8(STAGE_OBJ *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->position.z = -0x32;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    func_80116A8C(wp, &wp->u_4E0.face16, 0);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_1      = 1;
    wp->u_C.b.byte_D++;
    wp->routine_2++;
}

void func_80116048(ST06_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face16_4E0;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        func_80116A8C(wp, face, 0);
        wp->value_10C = 0x14;
        wp->routine_2++;
    }
}

void func_801160B4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        func_80116A8C(wp, face, 1);
        wp->routine_2++;
    }
}

void func_8011611C(ST06_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face16_4E0;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->value_10C = 5;
        func_80116A8C(wp, face, 2);
        wp->routine_2++;
    }
    switch (Scene_work.value_10)
    {
        case 0x78:
            func_80116A8C(wp, face, 4);
            break;
        case 0xF0:
            func_80116A8C(wp, face, 5);
            break;
        case 0x73:
        case 0x91:
        case 0x172:
            func_80116A8C(wp, face, 3);
            break;
    }
}

void func_8011620C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        func_80116A8C(wp, face, 6);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x23A)
    {
        func_80116A8C(wp, face, 7);
    }
}

void func_80116294(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        func_80116A8C(wp, face, 8);
        wp->u_C.b.byte_D++;
        wp->routine_2++;
    }
}

void func_80116304(ST06_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face16_4E0;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->value_118 = 0x16;
        func_80116A8C(wp, face, 9);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x1E)
    {
        func_80116A8C(wp, face, 0xA);
    }
}

void func_80116394(ST06_TALKER *wp)
{
    STAGE_FACE16 *face;

    face = &wp->face16_4E0;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->value_118 = 0x15;
        func_80116A8C(wp, face, 0xB);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0xF2)
    {
        func_80116A8C(wp, face, 0);
    }
}

void func_80116424(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        wp->position.x = -0x39;
        wp->position.y = 0x1D;
        wp->position.z = -0x352;
        func_80116A8C(wp, face, 0xC);
        wp->routine_2++;
    }
}

void func_80116488(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        wp->position.x = 0;
        wp->position.y = 0;
        wp->position.z = -0x32;
        func_800322A8(wp, 7, 0);
        func_80116A8C(wp, face, 0xD);
        wp->routine_2++;
    }
    if (Scene_work.value_10 == 0x78)
    {
        func_80116A8C(wp, face, 0xE);
    }
}

void func_80116520(ST06_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        wp->part_100[6].value_0 = 8;
        wp->routine_2++;
    }
}

void func_80116570(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 9, 0);
        func_80116A8C(wp, face, 0xF);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0x4B)
    {
        wp->u_C.b.byte_D++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0x5C)
    {
        func_80116A8C(wp, face, 0x11);
    }
}

void func_8011661C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xA, 0);
        func_80116A8C(wp, face, 6);
        D_8012BA98     = 0x400;
        wp->rotation.y = 0x400;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_PTR->value_10)
    {
        case 0x10E:
            func_80116A8C(wp, face, 0x13);
            break;
        case 0x15E:
            func_80116A8C(wp, face, 7);
            break;
    }
    if (wp->rotation.y == 0)
    {
        wp->rotation.y = 0xFF0;
    }
    else
    {
        wp->rotation.y -= 0x10;
    }
    if (D_8012BA98 == 0x1000)
    {
        D_8012BA98 = 0;
    }
    else
    {
        D_8012BA98 += 0x10;
    }
    wp->position.x = ((rcos(D_8012BA98) << 7) >> 12) + 0x32;
    wp->position.z = ((rsin(D_8012BA98) << 7) >> 12) - 0xFA;
}

void func_80116760(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xB, 0);
        wp->position.x = 0x28;
        wp->position.z = -0x78;
        wp->position.y = 0;
        wp->rotation.y = 0x400;
        func_80116A8C(wp, face, 0x15);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 < 0xA)
    {
        wp->position.x -= 4;
    }
}

void func_8011680C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xC, 0);
        wp->position.x = 0x14;
        wp->rotation.x = 0;
        wp->rotation.y = 0;
        wp->rotation.z = 0;
        wp->position.y = 0;
        wp->position.z = -0x46;
        func_80116A8C(wp, face, 0x17);
        func_80032488(wp);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0x8E)
    {
        func_80116A8C(wp, face, 0x1A);
    }
    if (STAGE_SCENE_PTR->value_10 == 0xA5)
    {
        func_80116A8C(wp, face, 0x17);
    }
}

void func_801168E0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xDU, 0);
        wp->routine_2++;
    }
}

void func_8011692C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x10, 0);
        func_80116A8C(wp, face, 0);
        wp->routine_2++;
    }
}

void func_80116994(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x11, 0);
        func_80116A8C(wp, face, 0x18);
        wp->routine_2++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0x23A)
    {
        wp->u_C.b.byte_D++;
    }
    if (STAGE_SCENE_PTR->value_10 == 0x258)
    {
        func_80116A8C(wp, face, 0x19);
    }
}

void func_80116A40(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0xFU, 0);
        wp->routine_2++;
    }
}

void func_80116A8C(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_801257A4[index];
    face->eyes_10               = D_80125810[index];
}

void func_80116AD4(STAGE_OBJ *wp, STAGE_FACE16 *face)
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

void func_80116C20(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_8012587C[wp->routine_0](wp, &Scene_work, (ST06_FLOAT *)&wp->ext_3C0[0x80]);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->position.y >= -0x7FF)
    {
        Model_Shadow_Trans(wp, 0x100, 0x200, 0);
    }
}

void func_80116D28(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST06_FLOAT *fl)
{
    wp->flags_0 |= 2;
    func_8002F9EC(wp, 0);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->value_78       = 0;
    wp->anim_AC        = 0;
    wp->anim_prev_AD   = 0xFF;
    fl->count_0        = 0;
    wp->position.y += Obj_ceiling_height_get(wp);
    fl->base_2             = wp->position.y;
    wp->routine_1          = 0;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->routine_0++;
}

void func_80116DD4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST06_FLOAT *fl)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0 && scene->value_10 == 0x5B)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            wp->position.y         = ((D_800BBCF8[fl->count_0 & 0x3F] * 16) >> 12) + fl->base_2;
            wp->position_fixed.v.y = wp->position.y << 16;
            fl->count_0++;
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 0x3C)
            {
                wp->value_44.words.integer = 4;
                fl->count_0                = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            wp->position.y -= wp->value_44.words.integer;
            wp->position_fixed.v.y = wp->position.y << 16;
            if (fl->count_0 < 6)
            {
                wp->value_44.words.integer += 2;
            }
            else if (fl->count_0 >= 0x55)
            {
                wp->value_44.words.integer -= 2;
            }
            fl->count_0++;
            if (scene->value_10 == 0x78)
            {
                fl->count_0 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->value_10 == 0x96)
            {
                fl->count_0                 = 0;
                wp->value_44.words.fraction = 8;
                wp->routine_1++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 1 && scene->value_10 > 0)
            {
                Obj_pos_set(wp, (sint16)(wp->value_44.words.fraction * 16), 0, 0);
                if (fl->count_0 < 0xA)
                {
                    wp->value_44.words.fraction += 2;
                }
                fl->count_0++;
            }
            else if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                fl->count_0 = 0;
                wp->routine_1++;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 2)
            {
                if (scene->value_10 > 0 && scene->value_10 <= 0x14)
                {
                    Obj_pos_set(wp, 0x280, 0, 0);
                    wp->position.y -= 0x20;
                }
                else
                {
                    Obj_pos_set(wp, 0x380, 0, 0);
                    wp->position.y = -0x8C0;
                }
                wp->position_fixed.v.y = wp->position.y << 16;
            }
            else if (scene->u_8.byte[1] == 3 && scene->value_10 == 1)
            {
                wp->value_44.words.integer = 0x10;
                wp->routine_1++;
            }
            break;
        case 6:
            wp->position.y += wp->value_44.words.integer;
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_44.words.integer >= 9)
            {
                wp->value_44.words.integer -= 4;
            }
            if (wp->position.y >= -0x4B0)
            {
                wp->position.y = -0x4B0;
                wp->routine_1++;
            }
            break;
    }
}

void func_8011710C(ST06_OBJ *wp)
{
    D_80125884[wp->routine_0](wp);
    wp->value_458 = 0;
    wp->value_4A0 = 0;
    wp->value_4B0 = 0;
}

void func_80117160(ST06_CRAB *wp)
{
    sint16 life;

    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->rotation.x     = 0;
    wp->rotation.z     = 0;
    wp->value_64       = 0;
    wp->value_44.value = 0;
    wp->value_48.value = 0;
    wp->body.flags_0   = 0x26;
    wp->body.u_4.word  = 0;
    wp->body.u_8.word  = 0;
    wp->body.hit_18    = 0;
    wp->body.value_1C  = 0;
    Track_reset(wp->body.track_28, 0, -0x60);
    wp->body.hit_60           = 0;
    wp->body.value_64         = 0;
    wp->body.hit_70           = 0;
    wp->body.value_74         = 0;
    wp->body.ground_78        = 0;
    wp->body.timer_C          = 0;
    wp->body.timer_E          = 0;
    wp->body.timer_80         = 0;
    wp->body.timer_82         = 0;
    wp->body.value_88         = 0;
    wp->body.area_8C          = Map_cell_get(&D_801258B8);
    life                      = D_8009884C[wp->kind_2]->life_8 << 5;
    wp->data_78               = D_801258AC;
    wp->routine_0             = 1;
    wp->value_10              = 0;
    wp->routine_1             = 6;
    *(uint16 *)&wp->routine_2 = 0;
    wp->life_6E               = life;
    wp->life_max_B0           = life;
    wp->life_prev_B2          = life;
    func_800322A8(wp, 0, wp->u_C.b.byte_C);
    func_80117290(wp);
}
