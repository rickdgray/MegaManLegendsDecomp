#include "common.h"
#include "st17.h"

void func_80106B70(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 4;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            face->value_2      = 0;
            func_80106E94(wp, face, 0);
            func_80106EBC(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0xA)
            {
                func_80106EBC(wp, face, 2);
                wp->routine_0++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x2D)
            {
                func_80106E94(wp, face, 2);
                func_80106EBC(wp, face, 0);
            }
            else if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                func_80106E94(wp, face, 1);
                func_80106EBC(wp, face, 1);
                wp->anim_AC = 5;
                wp->routine_0++;
            }
            break;
        case 3:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0xA)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 5)
            {
                if (scene->value_10 == 1)
                {
                    func_80106EBC(wp, face, 3);
                }
                else if (scene->value_10 == 0x1E)
                {
                    func_80106E94(wp, face, 3);
                }
            }
            switch (wp->value_A4)
            {
                case 3:
                    ST17_SCENE_BYTE(scene, 7) = 1;
                    break;
                case 0x11:
                    ST17_SCENE_BYTE(scene, 7) = 2;
                    break;
                case 0x19:
                    ST17_SCENE_BYTE(scene, 7) = 3;
                    break;
                case 0x20:
                    ST17_SCENE_BYTE(scene, 7) = 4;
                    break;
            }
            break;
    }
    func_80106EE4(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80106E94(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B5A4[index];
}

void func_80106EBC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B5B4[index];
}

void func_80106EE4(STAGE_OBJ *wp, STAGE_FACE *face)
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
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_C, 0x33, 0x37, 5));
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
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}
