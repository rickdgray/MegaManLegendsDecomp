#include "common.h"
#include "st0a.h"

void func_8010F0F4(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_801162B0[wp->variant_3](wp, &Scene_work, (STAGE_FACE *)&wp->ext_3C0[0xC0]);
    func_8010FA88(wp, (STAGE_FACE *)&wp->ext_3C0[0xC0]);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

#ifdef __wasm32__
void func_8010FA0C(ST0A_VIEW *wp, STAGE_FACE *face, sint32 index);
#endif

void func_8010F1F0(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9C4(wp, NULL);
            wp->scale.words[0] = 0x01400140;
            wp->scale.words[1] = 0x140;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 1;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            func_8010FA0C(wp, face, 0);
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 10:
                        func_8010FA0C(wp, face, 1);
                        break;
                    case 40:
                        func_8010FA0C(wp, face, 2);
                        break;
                    case 45:
                        wp->routine_0++;
                        break;
                }
            }
            break;
        case 2:
            if (wp->value_A7 != -1 && wp->value_A4 >= 0x25)
            {
                func_8002FEA4(wp, 0x48, 0, 0);
            }
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 1)
            {
                func_8010FA0C(wp, face, 4);
                wp->routine_0++;
            }
            break;
        case 3:
            wp->anim_AC = 2;
            wp->routine_0++;
            break;
        case 4:
            func_8002FEA4(wp, 0x40, 0, 0);
            if (wp->value_A7 == -1)
            {
                wp->routine_0++;
            }
            break;
        case 5:
            wp->anim_AC = 7;
            wp->routine_0++;
            break;
        case 6:
            if (scene->u_8.byte[1] == 4)
            {
                switch (scene->value_10)
                {
                    case 0x3C:
                        func_8010FA0C(wp, face, 3);
                        break;
                    case 0x82:
                        func_8010FA0C(wp, face, 4);
                        break;
                    case 0x8C:
                        wp->routine_0++;
                        break;
                }
            }
            break;
        case 7:
            wp->anim_AC = 3;
            func_8010FA0C(wp, face, 5);
            wp->routine_0++;
            break;
        case 8:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0x96)
            {
                func_8010FA0C(wp, face, 6);
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                func_8010FA0C(wp, face, 8);
                wp->routine_0++;
            }
            break;
        case 9:
            wp->anim_AC      = 4;
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 0x6E)
            {
                wp->routine_0++;
            }
            break;
        case 10:
            if (scene->value_10 == 0x78)
            {
                func_8010FA0C(wp, face, 7);
            }
            func_8002FEA4(wp, 0xA0, 0, 0);
            if (wp->value_A7 == -1)
            {
                func_8010FA0C(wp, face, 8);
                wp->routine_0++;
            }
            break;
        case 11:
            wp->anim_AC = 8;
            wp->routine_0++;
            break;
        case 12:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC = 5;
                func_8010FA0C(wp, face, 0xA);
                wp->routine_0++;
            }
            break;
        case 13:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0xA:
                case 0x6E:
                case 0xC8:
                case 0x104:
                    func_8010FA0C(wp, face, 9);
                    break;
                case 0x15E:
                    func_8010FA0C(wp, face, 9);
                    wp->routine_0++;
                    break;
                case 0x64:
                case 0xAA:
                case 0xF0:
                case 0x136:
                    func_8010FA0C(wp, face, 0xA);
                    break;
            }
            break;
        case 14:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x168)
            {
                func_8010FA0C(wp, face, 0xA);
            }
            else if (scene->u_8.byte[1] == 7 && scene->value_10 == 0xA)
            {
                wp->routine_0++;
            }
            break;
        case 15:
            wp->anim_AC = 6;
            wp->routine_0++;
            break;
        case 16:
            if (wp->value_A4 >= 0x12)
            {
                wp->rotation.y += 0x14;
                func_8002FEA4(wp, -0xA0, 0, 0);
            }
            break;
    }
}

#ifdef __wasm32__
void func_8010FBD0(STAGE_OBJ *wp, ST0A_GRID_HOLDER *holder);
#endif

void func_8010F774(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9C4(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 0x10;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            func_8010FA0C(wp, face, 1);
            func_8010FBD0(wp, (ST0A_GRID_HOLDER *)face);
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            wp->routine_0++;
            break;
        case 1:
            if (scene->u_8.byte[1] == 0)
            {
                switch (scene->value_10)
                {
                    case 0x2D:
                    case 0x5F:
                        func_8010FA0C(wp, face, 0);
                        break;
                    case 0x41:
                    case 0xEB:
                        func_8010FA0C(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 1 && scene->reserved00[7] == 1)
            {
                func_8010FA0C(wp, face, 0);
                face->timer_0 = 0;
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_AC = 0x11;
            wp->routine_0++;
            // fall through
        case 3:
            if (scene->reserved00[7] == 2)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            face->timer_0 = 0;
            wp->anim_AC   = 0x12;
            wp->routine_0++;
            break;
        case 5:
            if (face->timer_0 >= 0x1F)
            {
                scene->reserved00[7] = 3;
            }
            face->timer_0++;
            if (wp->value_A7 == -1)
            {
                wp->routine_0++;
            }
            if (wp->value_A4 >= 0x10)
            {
                func_8002FEA4(wp, -0x37, 0, 0);
            }
            break;
        case 6:
            wp->anim_AC = 0x13;
            func_8010FA0C(wp, face, 2);
            wp->routine_0++;
            break;
        case 7:
            func_80031824(((ST0A_GRID_HOLDER *)face)->grid_14);
            wp->routine_0++;
            break;
        case 8: // done (retail's jump table has the entry)
            break;
    }
    if (wp->routine_0 < 6)
    {
        func_8002C8CC(wp, 0x40, 0x200, 0);
    }
}

void func_8010FA0C(ST0A_VIEW *wp, STAGE_FACE *face, sint32 index)
{
    face->shape_C = face->index_E = 0;
    face->shape_F = face->index_11 = 0;
    face->prev_D = face->prev_10 = -1;
    if (wp->variant_3 == 0)
    {
        face->mouth_4 = D_80116334[index];
        face->eyes_8  = D_80116360[index];
    }
    else
    {
        face->mouth_4 = D_8011638C[index];
        face->eyes_8  = D_80116398[index];
    }
}

void func_8010FA88(STAGE_OBJ *wp, STAGE_FACE *face)
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
        func_8002D320(wp->model_88, 0x110010, func_8002D404(face->shape_C, 0x2A, 0x40, 6));
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
        func_8002D320(wp->model_88, 0x130012, func_8002D404(face->shape_F, 0x2A, 0x40, 6));
    }
    face->prev_10 = face->shape_F;
}

void func_8010FBD0(STAGE_OBJ *wp, ST0A_GRID_HOLDER *holder)
{
    sint8 i;

    i                                   = 0;
    holder->grid_14                     = func_80108478(wp, 3, holder->origin_18);
    *(uint8 *)&holder->grid_14->value_C = 0x3F;
    for (; i < 6; i++)
    {
        holder->origin_18[i] = wp->position;
        holder->origin_18[i].x += D_801163A4[i].x;
        holder->origin_18[i].y += D_801163A4[i].y;
        holder->origin_18[i].z += D_801163A4[i].z;
    }
}
