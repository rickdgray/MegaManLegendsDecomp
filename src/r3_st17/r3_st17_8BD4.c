#include "common.h"
#include "st17.h"

void func_80108BD4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            if (wp->value_A4 == 0xE)
            {
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xE;
                wp->routine_1++;
            }
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0)
            {
                switch (scene->value_10)
                {
                    case 0x14:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0x28:
                        func_801091C4(wp, face, 0xB);
                        break;
                    case 0x5F:
                        func_801091C4(wp, face, 0);
                        break;
                    case 0x78:
                        func_8010919C(wp, face, 1);
                        func_801091C4(wp, face, 0xA);
                        break;
                    case 0x8C:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0x96:
                        func_801091C4(wp, face, 0xA);
                        break;
                    case 0xC8:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0xDC:
                        func_8010919C(wp, face, 3);
                        func_801091C4(wp, face, 2);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 1 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0xA;
                face->value_2 = 0;
                func_8010919C(wp, face, 2);
                func_801091C4(wp, face, 6);
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                if (face->timer_0 < 0x1E)
                {
                    face->timer_0++;
                }
                else
                {
                    face->timer_0 = 0;
                    wp->routine_1++;
                }
            }
            break;
        case 4:
            wp->anim_AC   = 0xB;
            face->value_2 = 0;
            func_8010919C(wp, face, 0);
            func_801091C4(wp, face, 0xB);
            wp->routine_1++;
            break;
        case 5:
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_8010919C(wp, face, 8);
                        func_801091C4(wp, face, 4);
                        break;
                    case 0x19:
                        func_801091C4(wp, face, 0xB);
                        break;
                    case 0x30:
                        func_801091C4(wp, face, 4);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0xC;
                face->value_2 = 0;
                func_8010919C(wp, face, 2);
                func_801091C4(wp, face, 0xC);
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (face->timer_0 < 0xA)
            {
                face->timer_0++;
            }
            else
            {
                func_8010919C(wp, face, 4);
                face->timer_0 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 4)
            {
                switch (scene->value_10)
                {
                    case 0x19:
                        func_801091C4(wp, face, 1);
                        break;
                    case 0x37:
                        func_801091C4(wp, face, 0xC);
                        break;
                    case 0x55:
                        func_8010919C(wp, face, 2);
                        func_801091C4(wp, face, 5);
                        break;
                    case 0x7D:
                        func_801091C4(wp, face, 0xC);
                        break;
                    case 0xC3:
                        func_801091C4(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0xD;
                face->value_2 = 0;
                func_8010919C(wp, face, 5);
                func_801091C4(wp, face, 7);
                wp->routine_1++;
            }
            break;
        case 8:
            if (wp->value_A4 == 0xE)
            {
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xE;
                func_8010919C(wp, face, 7);
                func_801091C4(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 9:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x32:
                    func_8010919C(wp, face, 5);
                    func_801091C4(wp, face, 7);
                    break;
                case 0x3C:
                    func_801091C4(wp, face, 0xD);
                    break;
                case 0x64:
                    func_801091C4(wp, face, 7);
                    break;
                case 0x78:
                    func_8010919C(wp, face, 7);
                    func_801091C4(wp, face, 0xD);
                    wp->routine_1++;
                    break;
            }
            break;
        case 10:
            if (wp->value_A4 == 0x20)
            {
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0x20;
                wp->routine_1++;
            }
            break;
        case 11:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0xAA)
            {
                func_8010919C(wp, face, 5);
                func_801091C4(wp, face, 7);
            }
            else if (scene->value_10 == 0xC8)
            {
                func_8010919C(wp, face, 7);
                func_801091C4(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 12:
            if (scene->value_10 == 0xF3)
            {
                func_8010919C(wp, face, 5);
                func_801091C4(wp, face, 8);
            }
            break;
    }
}

void func_8010919C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B954[index];
}

void func_801091C4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B978[index];
}

void func_801091EC(STAGE_OBJ *wp, STAGE_FACE *face)
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
