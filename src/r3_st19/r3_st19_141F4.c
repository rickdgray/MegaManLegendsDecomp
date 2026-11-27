#include "common.h"
#include "st19.h"

void func_801141F4(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    scene                   = &Scene_work;
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        face->value_2      = 0;
        face->timer_0      = 0;
        func_80114668(wp, face, 0);
        func_80114690(wp, face, 0);
        wp->routine_0++;
    }
    func_801141B8(wp);
    switch (Scene_work.u_8.byte[0])
    {
        case 0:
            if (scene->value_10 == 1)
            {
                func_80114690(wp, face, 0);
                func_80114668(wp, face, 0);
            }
            break;
        case 7:
            if (scene->value_10 == 1)
            {
                func_80114668(wp, face, 1);
            }
            if (scene->value_10 == 0x14)
            {
                func_80114690(wp, face, 1);
                func_80114668(wp, face, 2);
            }
            break;
        case 9:
            if (scene->value_10 == 1)
            {
                func_80114668(wp, face, 3);
            }
            if (scene->value_10 == 0x18)
            {
                func_80114668(wp, face, 4);
            }
            if (scene->value_10 == 0x20)
            {
                func_80114668(wp, face, 0xC);
            }
            break;
        case 11:
            if (scene->value_10 == 1)
            {
                func_80114690(wp, face, 3);
                func_80114668(wp, face, 5);
            }
            if (scene->value_10 == 0x14)
            {
                func_80114668(wp, face, 5);
            }
            if (scene->value_10 == 0x32)
            {
                func_80114668(wp, face, 5);
            }
            break;
        case 12:
            if (scene->value_10 == 1)
            {
                func_80114668(wp, face, 5);
                func_80114690(wp, face, 3);
            }
            if (scene->value_10 == 0x32)
            {
                func_80114668(wp, face, 5);
            }
            if (scene->value_10 == 0x8C)
            {
                func_80114668(wp, face, 7);
            }
            break;
        case 14:
            if (scene->value_10 == 1)
            {
                func_80114668(wp, face, 8);
                func_80114690(wp, face, 4);
            }
            if (scene->value_10 == 0xA)
            {
                func_80114668(wp, face, 9);
                func_80114690(wp, face, 5);
            }
            break;
        case 16:
            if (scene->value_10 == 0xA)
            {
                func_80114668(wp, face, 0xA);
                func_80114690(wp, face, 2);
            }
            if (scene->value_10 == 0x29)
            {
                func_80114668(wp, face, 0xA);
                func_80114690(wp, face, 2);
            }
            if (scene->value_10 == 0x32)
            {
                func_80114668(wp, face, 0xA);
            }
            if (scene->value_10 == 0x46)
            {
                func_80114668(wp, face, 0xA);
                func_80114690(wp, face, 7);
            }
            break;
        case 17:
            if (scene->value_10 == 1)
            {
                func_80114668(wp, face, 0xB);
                func_80114690(wp, face, 6);
            }
            break;
    }
    func_801146B8(wp, face);
    face->timer_0++;
}

void func_80114668(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80119CCC[index];
}

void func_80114690(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80119D00[index];
}

void func_801146B8(STAGE_OBJ *wp, STAGE_FACE *face)
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
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
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
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_80114800(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->rotation.y = -0x600;
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    Model_pose_unpack(wp);
    Model_parts_mtx_set_y(wp);
}

void func_80114864(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x50;
            wp->position.y = -1;
            wp->position.z = 0x258;
            wp->rotation.y = -0x300;
            func_800322A8(wp, 2, 0);
            wp->routine_2++;
        case 1:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_80114920(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x50;
            wp->position.y = -1;
            wp->position.z = 0x258;
            wp->rotation.y = 0x480;
            func_800322A8(wp, 3, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            wp->position.x -= 2;
            return;
    }
}

void func_801149BC(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x514;
            func_80032488(wp);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            wp->position.x--;
            return;
    }
}

void func_80114A38(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x672;
            wp->position.y = -0xA;
            wp->position.z = 0x28A;
            func_800322A8(wp, 4, 0);
            wp->routine_2++;
        case 1:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_80114AEC(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x9F6;
            wp->position.z = 0x186;
            wp->rotation.y = 0x200;
            func_800322A8(wp, 5, 0);
            wp->routine_2++;
        case 1:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_80114BA0(STAGE_OBJ *wp)
{
    D_80119D50[wp->routine_1](wp);
}

void func_80114BDC(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        wp->routine_0++;
    }
    func_80114BA0(wp);
}

void func_80114CC0(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    D_80119D68[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        Model_pose_unpack(wp);
        Model_parts_mtx_set_y(wp);
    }
    func_80115008(wp, face);
}

void func_80114DAC(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        wp->rotation.x     = 0;
        wp->rotation.y     = 0x400;
        wp->rotation.z     = 0;
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->be_flag |= 2;
        Model_work_init(wp, NULL);
        func_800322A8(wp, 1, 0);
        func_80114FC4(wp, face, 1);
        wp->u_C.b.byte_D = 0;
        wp->routine_1++;
        wp->routine_2++;
    }
}

void func_80114E60(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0xBA:
            func_800322A8(wp, 2, 0);
            func_80114FC4(wp, face, 4);
            break;
        case 0xEB:
            func_80114FC4(wp, face, 5);
            break;
        case 0x104:
            func_800322A8(wp, 3, 0);
            func_80114FC4(wp, face, 6);
            break;
        case 0x17C:
            func_80114FC4(wp, face, 7);
            break;
        case 0x1F4:
            func_800322A8(wp, 4, 0);
            break;
        case 0x168:
        case 0x214:
            func_80114FC4(wp, face, 8);
            break;
        case 0x258:
            func_800322A8(wp, 5, 0);
            break;
    }
}

void func_80114FC4(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index)
{
    face->prev_2 = face->prev_8 = -1;
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->mouth_C                 = D_80119E68[index];
    face->eyes_10                 = D_80119E68[index];
}

void func_80115008(STAGE_OBJ *wp, STAGE_FACE16 *face)
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

void func_80115154(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->rotation.y = -0x380;
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    Model_pose_unpack(wp);
    Model_parts_mtx_set_y(wp);
}

void func_801151B8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80032488(wp);
}

void func_8011520C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
    func_80032488(wp);
}

void func_80115260(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->rotation.y = -0x400;
        func_800322A8(wp, 3, 0);
        wp->routine_2++;
    }
    func_80032488(wp);
}

void func_801152BC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
    func_80032488(wp);
}

void func_80115310(void)
{
}

void func_80115318(void)
{
}

void func_80115320(void)
{
}

void func_80115328(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 5, 0);
            wp->routine_2 = 1;
            break;
        case 2:
            func_800322A8(wp, 6, 0);
            wp->routine_2 = 1;
            break;
        case 3:
            func_800322A8(wp, 7, 0);
            wp->routine_2 = 1;
            break;
        case 4:
            func_800322A8(wp, 8, 0);
            wp->routine_2 = 1;
            break;
        case 5:
            func_800322A8(wp, 9, 0);
            wp->routine_2 = 1;
            break;
        case 6:
            func_800322A8(wp, 10, 0);
            wp->routine_2 = 1;
            break;
    }
    func_80032488(wp);
}

void func_801153D4(void)
{
}

void func_801153DC(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->rotation.y = -0x200;
            func_800322A8(wp, 0xBU, 0);
            wp->routine_2++;
        case 1:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_80115480(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            func_800322A8(wp, 0xCU, 0);
            wp->routine_2++;
        case 1:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_8011551C(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->rotation.y = -0x300;
            func_800322A8(wp, 0xDU, 0);
            wp->routine_2++;
        case 1:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_801155C0(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->rotation.y = -0x300;
            func_800322A8(wp, 0xEU, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_80115634(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->rotation.y = 0x480;
            func_800322A8(wp, 0xFU, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            wp->position.x -= 2;
            return;
    }
}

void func_801156B8(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x4E2;
            func_80032488(wp);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            wp->position.x--;
            return;
    }
}

void func_80115734(STAGE_OBJ *wp)
{
    Model_pose_unpack(wp);
    Model_parts_mtx_set_y(wp);
}

void func_80115764(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            func_800322A8(wp, 0x10, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_801157D0(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->position.x = -0xAF0;
            wp->rotation.y = -0x400;
            func_800322A8(wp, 0x11, 0);
            wp->routine_2 = 3;
            break;
        case 1:
            func_800322A8(wp, 0x12, 0);
            wp->routine_2 = 3;
            break;
        case 2:
            func_800322A8(wp, 0x13, 0);
            wp->routine_2 = 3;
            break;
        case 3:
            func_80032488(wp);
            break;
    }
}

void func_80115888(STAGE_OBJ *wp)
{
    D_8011A3A8[wp->routine_1](wp);
}

void func_801158C4(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    scene                   = &Scene_work;
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        face->value_2      = 0;
        face->timer_0      = 0;
        func_80116060(wp, face, 0);
        func_80116038(wp, face, 0x1B);
        wp->routine_0++;
    }
    func_80115888(wp);
    switch (Scene_work.u_8.byte[0])
    {
        case 0:
            if (scene->value_10 == 1)
            {
                func_80116060(wp, face, 0);
            }
            if (scene->value_10 == 0x32)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0x46)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0x5A)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0x6E)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0x82)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0x96)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0xD2)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0xE6)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0xFA)
            {
                func_80116038(wp, face, 0);
            }
            break;
        case 1:
            if (scene->value_10 == 1)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0xA)
            {
                func_80116038(wp, face, 0);
            }
            if (scene->value_10 == 0x1E)
            {
                func_80116038(wp, face, 1);
                func_80116060(wp, face, 2);
            }
            break;
        case 3:
            if (scene->value_10 == 1)
            {
                func_80116060(wp, face, 3);
                func_80116038(wp, face, 2);
            }
            break;
        case 4:
            if (scene->value_10 == 1)
            {
                func_80116038(wp, face, 2);
                func_80116060(wp, face, 3);
            }
            if (scene->value_10 == 0xA)
            {
                func_80116038(wp, face, 3);
            }
            if (scene->value_10 == 0x14)
            {
                func_80116038(wp, face, 4);
                func_80116060(wp, face, 4);
            }
            break;
        case 6:
            if (scene->value_10 == 1)
            {
                func_80116060(wp, face, 5);
            }
            if (scene->value_10 == 0x14)
            {
                func_80116038(wp, face, 6);
            }
            if (scene->value_10 == 0x3C)
            {
                func_80116038(wp, face, 0x11);
            }
            if (scene->value_10 == 0x5A)
            {
                func_80116038(wp, face, 0x11);
            }
            if (scene->value_10 == 0xC8)
            {
                func_80116038(wp, face, 0x12);
            }
            if (scene->value_10 == 0x118)
            {
                func_80116038(wp, face, 0x12);
            }
            if (scene->value_10 == 0x145)
            {
                func_80116038(wp, face, 0x13);
            }
            if (scene->value_10 == 0x186)
            {
                func_80116038(wp, face, 0x14);
            }
            break;
        case 7:
            if (scene->value_10 == 1)
            {
                func_80116060(wp, face, 3);
            }
            if (scene->value_10 == 5)
            {
                func_80116038(wp, face, 2);
            }
            break;
        case 8:
            if (scene->value_10 == 1)
            {
                func_80116060(wp, face, 6);
            }
            if (scene->value_10 == 5)
            {
                func_80116038(wp, face, 7);
            }
            if (scene->value_10 == 0x14)
            {
                func_80116038(wp, face, 8);
            }
            if (scene->value_10 == 0x46)
            {
                func_80116038(wp, face, 0x15);
            }
            if (scene->value_10 == 0xAA)
            {
                func_80116038(wp, face, 0x16);
            }
            if (scene->value_10 == 0xFA)
            {
                func_80116038(wp, face, 0x17);
            }
            if (scene->value_10 == 0x12C)
            {
                func_80116038(wp, face, 0x17);
            }
            if (scene->value_10 == 0x17C)
            {
                func_80116038(wp, face, 0x18);
            }
            break;
        case 9:
            if (scene->value_10 == 1)
            {
                func_80116038(wp, face, 9);
                func_80116060(wp, face, 7);
            }
            if (scene->value_10 == 0xA)
            {
                func_80116038(wp, face, 0xA);
            }
            if (scene->value_10 == 0x20)
            {
                func_80116038(wp, face, 0xC);
                func_80116060(wp, face, 8);
            }
            if (scene->value_10 == 0x32)
            {
                func_80116038(wp, face, 0xD);
                func_80116060(wp, face, 9);
            }
            break;
        case 15:
            if (scene->value_10 == 1)
            {
                func_80116038(wp, face, 0xC);
                func_80116060(wp, face, 7);
            }
            if (scene->value_10 == 0x28)
            {
                func_80116038(wp, face, 0xE);
                func_80116060(wp, face, 0xA);
            }
            if (scene->value_10 == 0x46)
            {
                func_80116038(wp, face, 0xE);
            }
            if (scene->value_10 == 0x6E)
            {
                func_80116038(wp, face, 0x1A);
            }
            break;
        case 17:
            if (scene->value_10 == 1)
            {
                func_80116038(wp, face, 0xF);
                func_80116060(wp, face, 0xB);
            }
            if (scene->value_10 == 0xE6)
            {
                func_80116038(wp, face, 5);
            }
            break;
    }
    func_80116088(wp, face);
    face->timer_0++;
}

void func_80116038(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011A308[index];
}

void func_80116060(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011A378[index];
}

void func_80116088(STAGE_OBJ *wp, STAGE_FACE *face)
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
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x2A, 0x40, 6));
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
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x2A, 0x40, 6));
    }
    face->prev_10 = face->shape_F;
}
