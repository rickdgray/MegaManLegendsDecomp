#include "common.h"
#include "st1a.h"

void func_80113460(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 9 && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x14:
                        func_801144A0(wp, face, 1);
                        break;
                    case 0x3C:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x64:
                        func_801144A0(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 0);
            }
            else if (scene->u_8.byte[1] == 0xE && scene->value_10 == 0x12C)
            {
                func_80114478(wp, face, 0xE);
                func_801144A0(wp, face, 0x12);
                wp->anim_AC   = 0x11;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0xF && scene->value_10 == 1)
            {
                func_80114478(wp, face, 3);
                func_801144A0(wp, face, 1);
                wp->anim_AC   = 0x12;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 0xF)
            {
                switch (scene->value_10)
                {
                    case 5:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x14:
                        func_801144A0(wp, face, 1);
                        break;
                    case 0x28:
                        func_801144A0(wp, face, 0x11);
                        break;
                    case 0x50:
                        func_801144A0(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x11 && scene->value_10 == 1)
            {
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 3);
                wp->routine_1++;
            }
            if (wp->value_A7 != -1)
            {
                Obj_pos_set(wp, 0x2A, 0, 0);
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 0x11)
            {
                if (scene->value_10 == 0xA)
                {
                    func_80114478(wp, face, 0xF);
                }
                else if (scene->value_10 == 0x1E)
                {
                    func_80114478(wp, face, 4);
                    func_801144A0(wp, face, 4);
                    wp->anim_AC   = 0x14;
                    face->value_2 = 0;
                }
            }
            else if (scene->u_8.byte[1] == 0x12 && scene->value_10 == 1)
            {
                wp->rotation.y = 0x700;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 2);
                wp->routine_1++;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 0x13 && scene->value_10 == 0xA)
            {
                func_80114478(wp, face, 5);
                func_801144A0(wp, face, 4);
                wp->anim_AC   = 0x15;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->u_8.byte[1] == 0x13)
            {
                switch (scene->value_10)
                {
                    case 0xF:
                        func_801144A0(wp, face, 0x13);
                        break;
                    case 0x1E:
                        func_801144A0(wp, face, 2);
                        break;
                    case 0x28:
                        func_801144A0(wp, face, 0x13);
                        break;
                    case 0x37:
                        func_801144A0(wp, face, 2);
                        break;
                    case 0x50:
                        func_801144A0(wp, face, 0x13);
                        break;
                    case 0x78:
                        func_801144A0(wp, face, 2);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 1)
            {
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 2);
                wp->anim_AC   = 0x16;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 0xA)
            {
                func_80114478(wp, face, 0xE);
                func_801144A0(wp, face, 0x13);
            }
            if (wp->value_A4 == 0xE)
            {
                wp->anim_AC      = 0x16;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0xE;
                wp->routine_1++;
            }
            break;
        case 8:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x15)
            {
                switch (scene->value_10)
                {
                    case 0x32:
                        func_80114478(wp, face, 3);
                        func_801144A0(wp, face, 0x15);
                        break;
                    case 0x46:
                        func_80114478(wp, face, 0x11);
                        func_801144A0(wp, face, 0x16);
                        face->value_2 = 0xE;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 9:
            if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 0x78)
            {
                func_80114478(wp, face, 7);
                func_801144A0(wp, face, 5);
            }
            else if (scene->u_8.byte[1] == 0x16 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x17;
                face->value_2 = 0;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 6);
                wp->routine_1++;
            }
            break;
        case 10:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 0x69)
            {
                func_801144A0(wp, face, 0x11);
                wp->routine_1++;
            }
            break;
        case 11:
            if (wp->value_A4 == 8)
            {
                wp->anim_AC      = 0x17;
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 8;
                func_801144A0(wp, face, 6);
                wp->routine_1++;
            }
            break;
        case 12:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x78:
                    func_801144A0(wp, face, 0x11);
                    break;
                case 0xBE:
                    func_801144A0(wp, face, 6);
                    break;
                case 0xD2:
                    func_801144A0(wp, face, 0x11);
                    break;
                case 0x104:
                    func_801144A0(wp, face, 6);
                    break;
                case 0x118:
                    func_80114478(wp, face, 8);
                    func_801144A0(wp, face, 0x17);
                    wp->routine_1++;
                    break;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 0x122)
            {
                func_801144A0(wp, face, 7);
            }
            else if (scene->u_8.byte[1] == 0x18 && scene->value_10 == 1)
            {
                wp->anim_AC              = 0x18;
                face->value_2            = 0;
                wp->u_F8.part[4].value_0 = 0x14;
                wp->u_F8.part[7].value_0 = 0x15;
                func_80114478(wp, face, 9);
                func_801144A0(wp, face, 9);
                wp->routine_1++;
            }
            break;
        case 14:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x19 && scene->value_10 == 5)
            {
                wp->routine_1++;
            }
            break;
        case 15:
            if (scene->u_8.byte[1] == 0x1D && scene->value_10 == 5)
            {
                wp->anim_AC   = 0x19;
                face->value_2 = 0;
                func_80114478(wp, face, 0xA);
                func_801144A0(wp, face, 0xA);
                wp->routine_1++;
            }
            break;
        case 16:
            if (scene->u_8.byte[1] == 0x20)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        wp->anim_AC   = 0x1A;
                        face->value_2 = 0;
                        func_80114478(wp, face, 0x12);
                        func_801144A0(wp, face, 0x18);
                        break;
                    case 0x28:
                        func_801144A0(wp, face, 0xB);
                        break;
                    case 0x3C:
                        func_801144A0(wp, face, 0x18);
                        break;
                    case 0x55:
                        func_801144A0(wp, face, 0xB);
                        break;
                }
            }
            break;
    }
    func_801144C8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x32, 0x200, 0);
    }
}

void func_80113E04(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    wp->anim_AC              = 0x1A;
    wp->anim_prev_AD         = 0xFF;
    wp->value_78             = 0;
    face->shadow_12          = 1;
    face->value_2            = 0;
    wp->u_F8.part[4].value_0 = 0x14;
    wp->u_F8.part[7].value_0 = 0x15;
    func_80114478(wp, face, 0xB);
    func_801144A0(wp, face, 0xC);
    func_801144C8(wp, face);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0++;
    func_800322A8(wp, wp->anim_AC, face->value_2);
}

void func_80113EE8(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x1B;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x1C;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0xA0)
            {
                wp->anim_AC = 0x1D;
                func_80114478(wp, face, 0x13);
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                func_801144A0(wp, face, 0xD);
                wp->routine_1++;
            }
            break;
        case 4:
            wp->anim_AC   = 0x1E;
            face->value_2 = 0;
            wp->routine_1++;
            break;
        case 5:
            if (scene->u_8.byte[1] == 6)
            {
                switch (scene->value_10)
                {
                    case 0xC8:
                        func_80114478(wp, face, 0x10);
                        func_801144A0(wp, face, 0x19);
                        break;
                    case 0xE6:
                        func_80114478(wp, face, 0xC);
                        func_801144A0(wp, face, 0xD);
                        break;
                    case 0xFA:
                        func_801144A0(wp, face, 0x19);
                        break;
                    case 0x113:
                        func_801144A0(wp, face, 0xD);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 7 && scene->value_10 == 1)
            {
                wp->anim_AC              = 0x1F;
                face->value_2            = 0;
                wp->u_F8.part[4].value_0 = 4;
                wp->u_F8.part[7].value_0 = 7;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 4);
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0xA)
            {
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->value_10 == 0x32)
            {
                func_801144A0(wp, face, 0x13);
            }
            else if (scene->value_10 == 0x41)
            {
                func_801144A0(wp, face, 4);
                wp->routine_1++;
            }
            break;
        case 8:
            wp->anim_AC   = 0x20;
            face->value_2 = 0;
            wp->routine_1++;
            break;
        case 9:
            if (scene->u_8.byte[1] == 0xA && scene->value_10 == 1)
            {
                wp->anim_AC   = 0x21;
                face->value_2 = 0;
                func_80114478(wp, face, 0xD);
                func_801144A0(wp, face, 0xE);
                wp->routine_1++;
            }
            break;
        case 10:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xA)
            {
                if (scene->value_10 == 0xA)
                {
                    func_80114478(wp, face, 6);
                    func_801144A0(wp, face, 0x1A);
                }
                else if (scene->value_10 == 0x1E)
                {
                    func_801144A0(wp, face, 0xF);
                }
                else if (scene->value_10 == 0x3C)
                {
                    func_801144A0(wp, face, 0x1A);
                    wp->routine_1++;
                }
            }
            break;
        case 11:
            if (wp->value_A4 == 0xD)
            {
                wp->anim_AC              = 0x21;
                wp->u_F8.part[7].value_0 = 0x16;
                face->value_2            = 0xD;
                wp->routine_1++;
            }
            break;
        case 12:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xA && scene->value_10 == 0x55)
            {
                func_801144A0(wp, face, 0xF);
            }
            else if (scene->u_8.byte[1] == 0xB && scene->value_10 == 1)
            {
                wp->u_F8.part[7].value_0 = 7;
                func_80114478(wp, face, 2);
                func_801144A0(wp, face, 0x10);
                wp->routine_1++;
            }
            break;
        case 13:
            if (wp->value_A4 == 0x12)
            {
                wp->routine_1++;
            }
            break;
        case 14:
            Obj_pos_set(wp, 0x200, 0, 0);
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 15:
            Obj_pos_set(wp, 0x200, 0, 0);
            wp->anim_AC   = 1;
            face->value_2 = 0;
            wp->routine_1++;
            break;
        case 16:
            Obj_pos_set(wp, 0x200, 0, 0);
            if (wp->value_A4 == 3 || wp->value_A4 == 0xB)
            {
                Sound_call2(0x91, &wp->position);
            }
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 17:
            break;
    }
    func_801144C8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x32, 0x200, 0);
    }
}

void func_80114478(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8013258C[index];
}

void func_801144A0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_801325DC[index];
}

void func_801144C8(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_80114610(STAGE_OBJ *wp, STAGE_FACE *face)
{
    STAGE_PL_VIEW *pl = &STAGE_PL;

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
    pl->value_168 = face->prev_D = face->shape_C = face->mouth_4[face->index_E];
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
    pl->value_169 = face->prev_10 = face->shape_F = face->eyes_8[face->index_11];
}

void func_801146D8(ST1A_OBJ *wp)
{
    STAGE_FACE *face;
    STAGE_SCENE_WORK *scene;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = (STAGE_FACE *)&wp->face;
    switch (wp->routine_0)
    {
        case 0:
            func_80114A7C(wp, face);
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x1B && scene->value_10 == 5)
            {
                func_80114B48(wp, face, 2);
                wp->routine_0++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0x1B)
            {
                switch (scene->value_10)
                {
                    case 0x64:
                        func_80114B20(wp, face, 1);
                        // fall through
                    case 0x1E:
                        func_80114B48(wp, face, 2);
                        break;
                    case 0xD7:
                        func_80114B20(wp, face, 0);
                        // fall through
                    case 0x14:
                    case 0x32:
                        func_80114B48(wp, face, 0);
                        break;
                    case 0x3C:
                    case 0xFA:
                        func_80114B20(wp, face, 3);
                        break;
                }
            }
            if (scene->u_8.byte[1] == 0x1D && scene->value_10 == 1)
            {
                func_80114B20(wp, face, 2);
                func_80114B48(wp, face, 1);
                wp->routine_0++;
            }
            break;
        case 3:
            if (scene->value_10 == 0x19)
            {
                wp->anim_AC   = 2;
                face->value_2 = 0;
                func_80114B48(wp, face, 3);
                wp->routine_0++;
            }
            break;
        case 4:
            if (wp->value_A4 == 0xF)
            {
                face->value_2 = 0xF;
                wp->routine_0++;
            }
            break;
        case 5:
            wp->anim_prev_AD = 0xFF;
            switch (scene->value_10)
            {
                case 0x82:
                    func_80114B48(wp, face, 3);
                    wp->routine_0++;
                    break;
                case 0x5F:
                    func_80114B48(wp, face, 1);
                    break;
                case 0x6E:
                    func_80114B20(wp, face, 4);
                    break;
            }
            break;
        case 6:
            switch (scene->value_10)
            {
                case 0x91:
                    func_80114B48(wp, face, 1);
                    break;
                case 0xA0:
                    func_80114B48(wp, face, 3);
                    break;
                case 0xC6:
                    func_80114B48(wp, face, 1);
                    wp->routine_0++;
                    break;
                case 0xF0:
                    func_80114B20(wp, face, 4);
                    break;
            }
            break;
        case 7:
            break;
    }
    func_80114B70(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80114A7C(STAGE_OBJ *wp, STAGE_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->anim_AC        = 1;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->value_2      = 0;
    func_80114B20(wp, face, 0);
    func_80114B48(wp, face, 0);
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80114B20(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_801326B4[index];
}

void func_80114B48(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_801326C8[index];
}

void func_80114B70(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_80114CB8(ST1A_OBJ *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face;
    D_801326D8[wp->routine_0](wp, &Scene_work, face);
    func_80115828(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
}

void func_80114DD8(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 1;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    talk->face.timer_0 = 0;
    talk->face.value_2 = 0;
    talk->b.value_12   = 0;
    func_801157D8(wp, &talk->face, 0);
    func_80115800(wp, &talk->face, 0);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0++;
}

void func_80114E90(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0 && scene->value_10 == 0xA)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 0x14:
                        func_80115800(wp, &talk->face, 0xB);
                        wp->anim_AC        = 2;
                        talk->face.value_2 = 0;
                        break;
                    case 0x28:
                        func_80115800(wp, &talk->face, 0);
                        break;
                    case 0x2D:
                        func_80115800(wp, &talk->face, 0xB);
                        break;
                    case 0x41:
                        func_80115800(wp, &talk->face, 0);
                        break;
                    case 0x122:
                        wp->anim_AC        = 3;
                        talk->face.value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 6);
                func_80115800(wp, &talk->face, 1);
                talk->b.value_12 = 1;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0x28:
                        func_801157D8(wp, &talk->face, 0xB);
                        func_80115800(wp, &talk->face, 0xC);
                        break;
                    case 0x3C:
                        func_80115800(wp, &talk->face, 1);
                        break;
                    case 0x46:
                        func_80115800(wp, &talk->face, 0xC);
                        break;
                    case 0x78:
                        func_80115800(wp, &talk->face, 1);
                        break;
                    case 0xDC:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                    case 0x15E:
                        wp->anim_AC        = 5;
                        talk->face.value_2 = 0;
                        func_801157D8(wp, &talk->face, 6);
                        func_80115800(wp, &talk->face, 0xC);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 4:
            if (wp->value_A4 == 0xE)
            {
                wp->anim_AC        = 5;
                talk->face.value_2 = 0xE;
                wp->routine_1++;
            }
            break;
        case 5:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0x186)
            {
                func_80115800(wp, &talk->face, 1);
            }
            else if (scene->value_10 == 0x1B3)
            {
                func_801157D8(wp, &talk->face, 1);
                func_80115800(wp, &talk->face, 0xC);
                wp->anim_AC        = 5;
                talk->face.value_2 = 0xE;
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->value_10 == 0x1EA)
            {
                func_80115800(wp, &talk->face, 1);
            }
            else if (scene->value_10 == 0x226)
            {
                func_801157D8(wp, &talk->face, 8);
            }
            else if (scene->value_10 == 0x27B)
            {
                func_801157D8(wp, &talk->face, 1);
                func_80115800(wp, &talk->face, 2);
                wp->anim_AC        = 6;
                talk->face.value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (wp->value_A4 >= 7)
            {
                wp->position.x += 10;
                wp->position_fixed.v.x = wp->position.x << 16;
                if (wp->value_A7 == -1)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 8:
            wp->anim_AC        = 7;
            talk->face.value_2 = 0;
            wp->rotation.y     = 0xC00;
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->routine_1++;
            break;
        case 9:
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            if (scene->value_10 == 0x2CE)
            {
                wp->routine_1++;
            }
            break;
        case 10:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 1)
            {
                wp->anim_AC        = 8;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 2);
                func_80115800(wp, &talk->face, 3);
                wp->routine_1++;
            }
            break;
        case 11:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 4)
            {
                if (scene->value_10 == 0xA)
                {
                    func_80115800(wp, &talk->face, 0xD);
                }
                else if (scene->value_10 == 0x32)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 12:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0x50)
            {
                func_80115800(wp, &talk->face, 3);
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC        = 7;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 3);
                func_80115800(wp, &talk->face, 6);
                wp->routine_1++;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC        = 9;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 3);
                func_80115800(wp, &talk->face, 6);
                wp->routine_1++;
            }
            else
            {
                Obj_pos_set(wp, 0xA4, 0, 0);
            }
            break;
        case 14:
            if (scene->u_8.byte[1] == 6)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_80115800(wp, &talk->face, 0xE);
                        break;
                    case 0x37:
                        func_80115800(wp, &talk->face, 6);
                        break;
                    case 0x41:
                        func_80115800(wp, &talk->face, 0xE);
                        break;
                    case 0x4B:
                        func_80115800(wp, &talk->face, 6);
                        break;
                    case 0x11D:
                        func_801157D8(wp, &talk->face, 0xA);
                        func_80115800(wp, &talk->face, 0x10);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 7 && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xA;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 4);
                func_80115800(wp, &talk->face, 7);
                wp->routine_1++;
            }
            break;
        case 15:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0x14)
            {
                wp->routine_1++;
            }
            break;
        case 16:
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0x46)
            {
                func_801157D8(wp, &talk->face, 5);
                func_80115800(wp, &talk->face, 8);
            }
            else if (scene->u_8.byte[1] == 9 && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xB;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 6);
                func_80115800(wp, &talk->face, 9);
                wp->routine_1++;
            }
            break;
        case 17:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 5:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                    case 0x14:
                        func_80115800(wp, &talk->face, 0xF);
                        break;
                    case 0x28:
                        func_80115800(wp, &talk->face, 9);
                        break;
                    case 0x32:
                        func_80115800(wp, &talk->face, 0xF);
                        break;
                    case 0x80:
                        func_80115800(wp, &talk->face, 9);
                        break;
                    case 0xA5:
                        func_80115800(wp, &talk->face, 0xF);
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 18:
            if (scene->u_8.byte[1] == 9)
            {
                switch (scene->value_10)
                {
                    case 0xF3:
                        func_80115800(wp, &talk->face, 9);
                        break;
                    case 0xFA:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                    case 0x104:
                        func_801157D8(wp, &talk->face, 0xB);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xC;
                talk->face.value_2 = 0;
                func_801157D8(wp, &talk->face, 7);
                func_80115800(wp, &talk->face, 0xA);
                wp->routine_1++;
            }
            break;
        case 19:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xC)
            {
                if (scene->value_10 == 0x5A)
                {
                    func_801157D8(wp, &talk->face, 0xC);
                }
                else if (scene->value_10 == 0xB9)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 20:
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 0xC8)
            {
                func_801157D8(wp, &talk->face, 0xC);
                wp->routine_1++;
            }
            break;
        case 21:
            break;
    }
}

void func_801157D8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_801327F8[index];
}

void func_80115800(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8013282C[index];
}

void func_80115828(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_80115970(ST1A_OBJ *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face;
    D_80132870[wp->routine_0](wp, &Scene_work, face);
    func_801165FC(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
    if (face->shadow_12 != 0)
    {
        Model_Shadow_Trans(wp, 0x40, 0x200, 0);
    }
}

void func_80115A90(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 1;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    talk->face.timer_0 = 0;
    talk->face.value_2 = 0;
    talk->b.value_12   = 0;
    func_801165AC(wp, &talk->face, 0);
    func_801165D4(wp, &talk->face, 0);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0++;
}

void func_80115B48(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_TALK *talk)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR pos;

    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0 && scene->value_10 == 0x14)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                switch (scene->value_10)
                {
                    case 1:
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x28:
                        func_801165AC(wp, &talk->face, 0xA);
                        break;
                    case 0x5A:
                        func_801165AC(wp, &talk->face, 0xB);
                        func_801165D4(wp, &talk->face, 9);
                        wp->anim_AC        = 2;
                        talk->face.value_2 = 0;
                        break;
                    case 0xA:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x6E:
                        func_801165AC(wp, &talk->face, 0xB);
                        func_801165D4(wp, &talk->face, 9);
                        break;
                    case 0x96:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0xAA:
                        func_801165AC(wp, &talk->face, 0xB);
                        func_801165D4(wp, &talk->face, 9);
                        break;
                    case 0x107:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x125:
                        wp->anim_AC        = 3;
                        talk->face.value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 1)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0;
                talk->b.value_12   = 1;
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->value_A4 == 0x15)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0x15;
                wp->routine_1++;
            }
            break;
        case 4:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 2 && scene->value_10 == 0x9B)
            {
                func_801165AC(wp, &talk->face, 0xC);
                func_801165D4(wp, &talk->face, 0xA);
                wp->routine_1++;
            }
            break;
        case 5:
            if (wp->value_A4 == 0x2A)
            {
                wp->anim_AC        = 4;
                talk->face.value_2 = 0x2A;
                wp->routine_1++;
            }
            break;
        case 6:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 2)
            {
                switch (scene->value_10)
                {
                    case 0xB4:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0xC8:
                        func_801165AC(wp, &talk->face, 0xC);
                        func_801165D4(wp, &talk->face, 0xA);
                        break;
                    case 0x136:
                        func_801165AC(wp, &talk->face, 9);
                        func_801165D4(wp, &talk->face, 1);
                        break;
                    case 0x1EA:
                        func_801165AC(wp, &talk->face, 1);
                        func_801165D4(wp, &talk->face, 2);
                        break;
                    case 0x1F4:
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 7:
            switch (scene->value_10)
            {
                case 0x212:
                    func_801165AC(wp, &talk->face, 0xA);
                    break;
                case 0x21C:
                    func_801165AC(wp, &talk->face, 0xC);
                    func_801165D4(wp, &talk->face, 0xA);
                    break;
                case 0x244:
                    func_801165AC(wp, &talk->face, 2);
                    func_801165D4(wp, &talk->face, 3);
                    break;
                case 0x24E:
                    func_801165AC(wp, &talk->face, 8);
                    func_801165D4(wp, &talk->face, 0xB);
                    wp->anim_AC        = 5;
                    talk->face.value_2 = 0;
                    wp->routine_1++;
                    break;
            }
            break;
        case 8:
            if (wp->value_A4 == 0x1F)
            {
                wp->anim_AC        = 5;
                talk->face.value_2 = 0x1F;
                func_801165AC(wp, &talk->face, 3);
                func_801165D4(wp, &talk->face, 3);
                wp->routine_1++;
            }
            break;
        case 9:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0x28F)
            {
                func_801165AC(wp, &talk->face, 3);
                func_801165D4(wp, &talk->face, 4);
                wp->routine_1++;
            }
            break;
        case 10:
            if (wp->value_A4 >= 0x25)
            {
                func_80030058(&fixed, 0xC00, 0xA4, 0, 0);
                func_80030150(&fixed, &pos);
                wp->position.x += pos.x;
                wp->position.z += pos.z;
                wp->position_fixed.v.x += fixed.x;
                wp->position_fixed.v.z += fixed.z;
                if (wp->value_A7 == -1)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 11:
            wp->anim_AC        = 6;
            talk->face.value_2 = 0;
            wp->rotation.y     = 0xC00;
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->routine_1++;
            break;
        case 12:
            wp->position.x += 10;
            wp->position_fixed.v.x = wp->position.x << 16;
            if (scene->value_10 == 0x2CE)
            {
                wp->routine_1++;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xB;
                talk->face.value_2 = 0x14;
                Obj_pos_set(wp, 0x2E, 0, 0);
                wp->routine_1++;
            }
            break;
        case 14:
            Obj_pos_set(wp, 0x2E, 0, 0);
            if (wp->value_A4 == 0x27)
            {
                wp->anim_AC        = 7;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 0xC);
                func_801165D4(wp, &talk->face, 0xA);
                wp->routine_1++;
            }
            break;
        case 15:
            if (wp->value_A4 < 0x28)
            {
                Obj_pos_set(wp, 0x2E, 0, 0);
            }
            if (wp->value_A7 == -1)
            {
                func_801165AC(wp, &talk->face, 4);
                func_801165D4(wp, &talk->face, 8);
                wp->routine_1++;
            }
            break;
        case 16:
            if (scene->u_8.byte[1] == 3 && scene->value_10 == 0x73)
            {
                wp->anim_AC        = 8;
                talk->face.value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 17:
            if (scene->u_8.byte[1] == 3)
            {
                switch (scene->value_10)
                {
                    case 0xA5:
                        func_801165AC(wp, &talk->face, 0xD);
                        func_801165D4(wp, &talk->face, 0xC);
                        break;
                    case 0xB9:
                        func_801165AC(wp, &talk->face, 5);
                        func_801165D4(wp, &talk->face, 5);
                        break;
                    case 0xC8:
                        func_801165AC(wp, &talk->face, 0xD);
                        func_801165D4(wp, &talk->face, 0xC);
                        break;
                    case 0xF0:
                        func_801165AC(wp, &talk->face, 5);
                        func_801165D4(wp, &talk->face, 5);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 5 && scene->value_10 == 1)
            {
                wp->anim_AC        = 6;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 2);
                func_801165D4(wp, &talk->face, 3);
                wp->routine_1++;
            }
            break;
        case 18:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 1)
            {
                wp->anim_AC        = 9;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 6);
                func_801165D4(wp, &talk->face, 6);
                wp->routine_1++;
            }
            else
            {
                Obj_pos_set(wp, 0xA4, 0, 0);
            }
            break;
        case 19:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 7 && scene->value_10 == 0x14)
            {
                func_801165AC(wp, &talk->face, 0xE);
                func_801165D4(wp, &talk->face, 0xD);
                wp->routine_1++;
            }
            break;
        case 20:
            if (scene->u_8.byte[1] == 7)
            {
                switch (scene->value_10)
                {
                    case 0x28:
                        func_801165AC(wp, &talk->face, 6);
                        func_801165D4(wp, &talk->face, 6);
                        break;
                    case 0x3C:
                        func_801165AC(wp, &talk->face, 0xE);
                        func_801165D4(wp, &talk->face, 0xD);
                        break;
                    case 0x5F:
                        func_801165AC(wp, &talk->face, 6);
                        func_801165D4(wp, &talk->face, 6);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                wp->anim_AC        = 0xA;
                talk->face.value_2 = 0;
                func_801165AC(wp, &talk->face, 7);
                func_801165D4(wp, &talk->face, 7);
                wp->routine_1++;
            }
            break;
        case 21:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 0x1E)
            {
                func_801165AC(wp, &talk->face, 0xF);
                func_801165D4(wp, &talk->face, 0xE);
                wp->routine_1++;
            }
            break;
        case 22:
            switch (scene->value_10)
            {
                case 0x49:
                    func_801165AC(wp, &talk->face, 7);
                    func_801165D4(wp, &talk->face, 7);
                    break;
                case 0x64:
                    func_801165AC(wp, &talk->face, 0xF);
                    func_801165D4(wp, &talk->face, 0xE);
                    break;
                case 0x96:
                    func_801165AC(wp, &talk->face, 7);
                    func_801165D4(wp, &talk->face, 7);
                    break;
            }
            break;
    }
}

void func_801165AC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80132A58[index];
}

void func_801165D4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80132A98[index];
}

void func_801165FC(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_80116744(STAGE_OBJ *wp)
{
    D_80132AD4[wp->routine_0](wp);
}

// ported from r3_st13 func_80100BAC
void func_80116780(ST1A_STCOM27_WORK_C *wp)
{
    wp->scale.v.x   = 0x200;
    wp->scale.v.y   = 0x200;
    wp->scale.v.z   = 0x200;
    wp->scale.v.pad = 0x4210;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->velocity.z  = 0;
    wp->velocity.y  = 0;
    wp->velocity.x  = 0;
    wp->accel.z     = 0;
    wp->accel.y     = 0;
    wp->accel.x     = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    Track_reset(wp->ctl.track_0, 7, -0x60);
    wp->data_78 = D_80132AE0;
    wp->life_6E = wp->life_max_B0 = D_8009884C[wp->kind_2]->life_8 << 4;
    wp->damage_B2                 = 0;
    wp->jump_74                   = 0;
    wp->ctl.sees_10               = 0;
    wp->ctl.flags_14              = 0;
    wp->ctl.hit_20                = 0;
    wp->ctl.value_24              = 0;
    wp->ctl.kind_30               = 0;
    func_800322A8(wp, 3, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80116874(ST1A_STCOM27_WORK_B *wp)
{
    ST1A_STCOM27_CTL_B *ctl;

    ctl                     = &wp->ctl;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->jump_prev_75        = wp->jump_74;
    func_801169B0(wp);
    if (wp->value_C == 0)
    {
        ctl->sees_10 = 1;
    }
    else
    {
        ctl->sees_10 = func_8003648C(ctl->track_0, wp);
    }
    D_80132AEC[wp->routine_1](wp);
    if (wp->routine_0 != 2)
    {
        func_80116C10(wp);
        func_80116B78(wp);
        if (wp->flags_0 & 2)
        {
            Model_Shadow_Trans(wp, 0x118, 0x200, 0);
        }
    }
}

// ported from r3_st13 func_80100DDC
void func_801169B0(ST1A_STCOM27_WORK_D *wp)
{
    ST1A_STCOM27_CTL_D *ctl;
    sint32 damage;
    sint32 knock;
    sint32 dir;

    ctl = &wp->ctl;
    if (wp->value_D != 0)
    {
        if (!(STAGE_FRAME & 3) && wp->damage_B2 != 0)
        {
            wp->damage_B2--;
        }
        damage = ctl->hit_20 & 0xFFFFFF;
        if (damage != 0)
        {
            knock = 0;
            if (wp->routine_1 == 6)
            {
                Sound_call2(0xA3, &wp->position);
                return;
            }
            wp->life_6E -= damage;
            wp->damage_B2 += damage;
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
            if (wp->life_6E <= 0)
            {
                wp->life_6E = 0;
                knock       = 1;
            }
            else if (wp->damage_B2 >= D_8009884C[wp->kind_2]->value_9 * 16)
            {
                knock = 1;
            }
            if (knock)
            {
                func_800322A8(wp, 0xB, 0);
                wp->damage_B2 = 0;
                ctl->kind_30  = 0;
                dir           = func_80031F84(&wp->position, &ctl->from_28, wp->rotation.y, 0);
                if (dir & 0xFFFF0000)
                {
                    wp->rotation.y = dir;
                }
                else
                {
                    wp->rotation.y = (dir + 0x800) & 0xFFF;
                }
                wp->velocity.x = -0x400;
                wp->velocity.y = -0x100;
                wp->accel.y    = 0x40;
                wp->jump_74    = 1;
                Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
                wp->routine_1 = 6;
                wp->routine_2 = 0;
                wp->velocity.y += wp->accel.y;
            }
        }
    }
}

void func_80116B78(ST1A_STCOM27_WORK *wp)
{
    if (wp->value_D != 0)
    {
        wp->ctl.hit_20 = 0;
        wp->ctl.pos_18 = wp->position;
        wp->ctl.pos_18.y -= 0x80;
        func_800341BC(&wp->ctl.pos_18, 0x80, 0, 0x8000, wp->index_1, &wp->ctl.hit_20, wp->ctl.kind_30 | 0x4080000, 0x800000, 0);
    }
}

void func_80116C10(ST1A_STCOM27_WORK *wp)
{
    ST1A_STCOM27_CTL *ctl;
    sint32 ground;
    wp->ctl.flags_14 = 0;
    ctl              = &wp->ctl;
    if (Obj_map_push_out(wp) & 0xF00)
    {
        wp->ctl.flags_14 |= 1;
    }
    if (wp->jump_74 == 0)
    {
        ground = Obj_ceiling_height_get(wp);
        if (ground != wp->position_prev.y)
        {
            if (wp->jump_prev_75 == 0)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->ctl.flags_14 |= 4;
            }
        }
        else
        {
            wp->position.y            = ground;
            wp->position_fixed_prev.y = ground << 16; // retail stores the saved copy here
        }
        ctl->flags_14 |= 2;
    }
}

void func_80116D08(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80116D48(wp);
        return;
    }
    func_80116DD0(wp);
}

void func_80116D48(ST1A_VIEW_B *wp)
{
    sint32 change;

    change = 0;
    if (wp->u_C.b[1] != 0)
    {
        change = wp->value_4F0 != 0;
    }
    if (wp->value_6E != wp->value_B0)
    {
        change = 1;
    }
    if (change)
    {
        func_800322A8(wp, 4, 0);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80116DD0(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_801177AC(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80116E10(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80116E50(wp);
        return;
    }
    func_80116EBC(wp);
}

void func_80116E50(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
}

// ported from r3_st13 func_801012E8

void func_80116EBC(ST1A_STCOM27_WORK_D *wp)
{
    STCOM_PL_WORK *pl;
    ST1A_STCOM27_CTL_D *ctl;
    sint32 seen;
    sint16 turn;

    pl             = &Player_work;
    ctl            = &wp->ctl;
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x20)) & 0xFFF;
    seen           = func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, pl->rotation.y, 0x800);
    if (wp->flags_6 & 0x80)
    {
        if (ctl->count_38 < 30)
        {
            ctl->count_38++;
        }
    }
    else
    {
        ctl->count_38 = 0;
    }
    if (ctl->timer_36 != 0)
    {
        ctl->timer_36--;
    }
    else if (ctl->count_38 >= 30 && wp->dist_80 <= 0x9C400 && seen)
    {
        if ((rand() & 0xF) < 7)
        {
            func_80117820((STAGE_OBJ *)wp);
        }
        else
        {
            func_80117868((ST1A_OBJ *)wp);
        }
        return;
    }
    if (--ctl->timer_34 == 0)
    {
        if (ctl->sees_10 == 0)
        {
            func_801177CC((ST1A_OBJ *)wp);
            Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
            return;
        }
        ctl->timer_34 = 0x3C;
    }
    turn = wp->rotation.y - wp->rotation_prev.y;
    if (turn < 0)
    {
        turn = -turn;
    }
    if (turn <= 0x10)
    {
        func_801176FC((STAGE_OBJ *)wp, 2);
    }
    else if (wp->rotation.y > wp->rotation_prev.y)
    {
        func_801176FC((STAGE_OBJ *)wp, 7);
    }
    else
    {
        func_801176FC((STAGE_OBJ *)wp, 8);
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    if (wp->value_A4 == 2)
    {
        Sound_call2(0x1B8, &wp->position);
    }
}

void func_801170E0(STAGE_OBJ *wp)
{
    sint32 step;
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x40)) & 0xFFF;
    if (wp->u_4E0.face16.eyes_10 != NULL && (wp->flags_6 & 0x80))
    {
        if (rand() & 1)
        {
            func_80117820(wp);
            return;
        }
        func_801177AC((ST1A_OBJ_B *)wp);
        Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
        return;
    }
    func_80032488(wp);
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
    step = wp->value_A4 == 5;
    if (wp->value_A4 == 0x13)
    {
        step = 1;
    }
    if (step)
    {
        Sound_call2(0x1B7, &wp->position);
    }
}

void func_801171E0(void)
{
}

void func_801171E8(ST1A_ACTOR *wp)
{
    STAGE_10C *slot;

    switch (wp->routine_2)
    {
        case 0:
            func_801172D8(wp);
            break;
        case 1:
            slot = Open_SHL_WORK();
            if (slot != NULL)
            {
                slot->flags_0            = 1;
                slot->kind_2             = 5;
                slot->variant_3          = 0;
                slot->value_F            = wp->value_1;
                slot->position           = wp->value_188;
                slot->position_fixed.v.x = slot->position.x << 16;
                slot->position_fixed.v.y = slot->position.y << 16;
                slot->position_fixed.v.z = slot->position.z << 16;
            }
            Sound_call2(0x1BA, &wp->position);
            wp->routine_2++;
            break;
        case 2:
        default:
            func_801173B0(wp);
            break;
    }
}

void func_801172D8(ST1A_ACTOR *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 5, 0);
        wp->routine_2++;
        return;
    }
    if (wp->value_A4 == 3)
    {
        wp->velocity.v.x = -0x600;
    }
    if (wp->value_A4 == 9)
    {
        wp->velocity.v.x = -0x400;
    }
    if (wp->value_A4 == 0xB)
    {
        wp->velocity.v.x = 0;
    }
    func_80032488(wp);
    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
}

void func_801173B0(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_801177AC(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801173F0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_80117430(wp);
        return;
    }
    func_801174B8(wp);
}

void func_80117430(ST1A_VIEW_C *wp)
{
    if (wp->u_A4.b[3] != 0)
    {
        func_800322A8(wp, 0xA, 0);
        wp->value_510 = 0;
        if (rand() & 1)
        {
            wp->u_518.h[1] = 0x20;
        }
        else
        {
            wp->u_518.h[1] = -0x20;
        }
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
        Obj_pos_set(wp, wp->value_44, wp->value_46, wp->value_48);
    }
}

void func_801174B8(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_80117758(wp);
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + wp->value_51A) & 0xFFF;
        func_80032488(wp);
    }
}

void func_8011750C(STAGE_OBJ *wp)
{
    D_80132B08[wp->routine_2](wp);
}

void func_80117548(ST1A_STCOM27_WORK *wp)
{
    STCOM_EFFECT *effect;
    if (wp->jump_74 == 0)
    {
        Sound_call2(0x1BC, &wp->position);
        if (wp->life_6E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0;
                effect->sprite.position = wp->position;
            }
            func_80047148(wp, &wp->position, effect);
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
        }
        else
        {
            func_800322A8(wp, 0xC, 0);
            wp->routine_2++;
        }
    }
    else
    {
        wp->jump_74 = 1;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        wp->velocity.y += wp->accel.y;
        func_80032488(wp);
    }
}

void func_80117658(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        func_800322A8(wp, 0xDU, 0);
        wp->routine_2++;
        return;
    }
    func_80032488(wp);
}

void func_801176B0(ST1A_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        wp->rotation.y -= 0x400;
        func_801177AC(wp);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801176FC(STAGE_OBJ *wp, sint32 anim)
{
    if (wp->anim_prev_AD != anim)
    {
        func_800322A8(wp, anim, wp->value_A4);
        wp->routine_2++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80117758(ST1A_OBJ *wp)
{
    func_800322A8(wp, 0xF, 0);
    wp->value_514        = 0x3C;
    wp->value_44.half[0] = 0x200;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    wp->routine_1        = 1;
    wp->routine_2        = 0;
}

void func_801177AC(ST1A_OBJ *wp)
{
    wp->value_516 = 0;
    func_80117758(wp);
}

void func_801177CC(ST1A_OBJ *wp)
{
    func_800322A8(wp, 1, 0);
    wp->value_514        = 0x78;
    wp->value_44.half[0] = 0x100;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    wp->routine_1        = 2;
    wp->routine_2        = 0;
}

void func_80117820(STAGE_OBJ *wp)
{
    func_800322A8(wp, 6, 0);
    wp->value_44.words.fraction = 0;
    wp->value_44.words.integer  = 0;
    wp->value_4C.words.integer  = 0;
    wp->routine_1               = 4;
    wp->routine_2               = 0;
}

void func_80117868(ST1A_OBJ *wp)
{
    func_800322A8(wp, 9, 0);
    wp->value_510        = D_8009884C[wp->kind_2]->value_A | 0x1000000;
    wp->value_516        = 0x3C;
    wp->value_44.half[0] = 0x400;
    wp->value_44.half[1] = 0;
    wp->value_4C.half[1] = 0;
    Sound_call2(0x1B9, &wp->position);
    wp->routine_1 = 5;
    wp->routine_2 = 0;
}

void func_801178F0(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}
