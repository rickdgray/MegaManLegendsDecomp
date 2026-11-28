#include "common.h"
#include "st1a.h"

void func_80117910(STAGE_FACE2 *face, sint32 index)
{
    face->shape_8 = 0;
    face->mouth_0 = D_80132B2C[index];
    face->prev_9  = 0;
}

void func_80117930(STAGE_FACE2 *face, sint32 index)
{
    face->index_A = 0;
    face->eyes_4  = D_80132BAC[index];
    face->shape_B = 0;
}

void func_80117950(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (face->prev_9 == 0)
    {
        if (face->mouth_0[face->shape_8] != 0x7E)
        {
            if (face->mouth_0[face->shape_8] == 0x7F)
            {
                face->shape_8 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0xE000D, Model_uv_cell(face->mouth_0[face->shape_8], 0x3E, 0x3A, 4));
            face->prev_9 = face->mouth_0[face->shape_8 + 1];
            face->shape_8 += 2;
        }
    }
    else
    {
        face->prev_9--;
    }
    if (face->shape_B == 0)
    {
        if (face->eyes_4[face->index_A] != 0x7E)
        {
            if (face->eyes_4[face->index_A] == 0x7F)
            {
                face->index_A = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->eyes_4[face->index_A], 0x3E, 0x3A, 4));
            face->shape_B = face->eyes_4[face->index_A + 1];
            face->index_A += 2;
        }
    }
    else
    {
        face->shape_B--;
    }
}

void func_80117AB4(STAGE_OBJ *wp, void *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->value_78       = 0;
}

void func_80117B0C(STAGE_OBJ *wp, void *face)
{
    func_80117AB4(wp, face);
    wp->routine_0++;
    func_80118138(wp, face);
}

void func_80117B58(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (wp->routine_1 == 0)
    {
        func_80117910(face, 0);
        func_80117930(face, 0);
        func_800322A8(wp, 0x11, 0);
        wp->routine_1++;
    }
}

void func_80117BCC(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x11, 0);
            wp->routine_1++;
            break;
        case 1:
            func_80032488(wp);
            wp->routine_1++;
            break;
        case 3:
            func_80117930(face, 9);
            func_80117910(face, 5);
            wp->routine_1++;
            // fall through
        case 4:
            func_80032488(wp);
            break;
        case 5:
            break;
    }
}

void func_80117C8C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_80117930(face, 1);
            func_80117910(face, 1);
            func_800322A8(wp, 0x12, 0);
            wp->routine_1++;
            break;
        case 1:
        case 3:
            func_80032488(wp);
            break;
        case 2:
            wp->rotation.y = 0;
            func_800322A8(wp, 0x13, 0);
            wp->routine_1++;
            break;
    }
    switch (Scene_work.value_10)
    {
        case 0x32:
            func_80117930(face, 4);
            break;
        case 0x78:
            func_80117930(face, 1);
            break;
    }
}

void func_80117D98(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x14, 0);
            wp->routine_1++;
            break;
        case 1:
        case 3:
            func_80032488(wp);
            break;
        case 2:
            func_800322A8(wp, 0, 0);
            wp->routine_1++;
            break;
    }
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 2);
            func_80117930(face, 5);
            break;
        case 0x96:
            func_80117930(face, 2);
            break;
    }
}

void func_80117E8C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_80032488(wp);
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 1);
            func_80117930(face, 4);
            break;
        case 0x78:
            func_80117930(face, 1);
            break;
        case 0x82:
            func_80117930(face, 4);
            break;
        case 0xBE:
            func_80117930(face, 1);
            break;
    }
}

void func_80117F2C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_80032488(wp);
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 1);
            func_80117930(face, 1);
            break;
        case 0x28:
            func_80117930(face, 4);
            break;
        case 0x6E:
            func_80117930(face, 1);
            break;
        case 0x78:
            func_80117930(face, 4);
            break;
        case 0xE6:
            func_80117930(face, 1);
            break;
        case 0x104:
            func_80117930(face, 4);
            break;
        case 0x17C:
            func_80117930(face, 1);
            break;
    }
}

void func_8011801C(STAGE_OBJ *wp)
{
    func_80032488(wp);
}

void func_8011803C(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x15, 0);
            wp->routine_1++;
            break;
        case 1:
            func_80032488(wp);
            break;
        case 2:
            break;
    }
    switch (Scene_work.value_10)
    {
        case 0:
            func_80117910(face, 3);
            func_80117930(face, 3);
            break;
        case 0x14:
            func_80117930(face, 6);
            break;
        case 0x28:
            func_80117930(face, 3);
            break;
        case 0x3C:
            func_80117930(face, 6);
            break;
        case 0x91:
            func_80117930(face, 3);
            break;
    }
}

void func_80118138(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (D_80132BD4[Scene_work.u_8.byte[1]] != NULL)
    {
        wp->position_prev           = wp->position;
        wp->position_fixed_prev.x   = wp->position_fixed.v.x;
        wp->position_fixed_prev.y   = wp->position_fixed.v.y;
        wp->position_fixed_prev.z   = wp->position_fixed.v.z;
        wp->position_fixed_prev.pad = wp->position_fixed.v.pad;
        wp->rotation_prev           = wp->rotation;
        D_80132BD4[Scene_work.u_8.byte[1]](wp, face);
        func_80117950(wp, face);
        Model_Shadow_Trans(wp, 0x64, 0x200, 0);
    }
}

void func_80118234(STAGE_OBJ *wp)
{
    D_80132C18[wp->routine_0](wp, &wp->u_4E0.face);
}

void func_80118270(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    func_80117AB4(wp, face);
    ST1A_FACE_SCRIPTS(face, 4, 7);
    func_800322A8(wp, 0x16, 0);
    wp->routine_0++;
}

void func_801182DC(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    if (STAGE_SCENE_BYTE(4) == 1)
    {
        switch (Scene_work.value_10)
        {
            case 0x46:
            case 0x73:
                func_80117930(face, 8);
                break;
            case 0x64:
            case 0xAF:
                func_80117930(face, 7);
                break;
            case 0xE6:
                STAGE_SCENE_BYTE(6)++;
                break;
        }
    }
    func_80032488(wp);
}

void func_801183A4(STAGE_OBJ *wp, STAGE_FACE2 *face)
{
    D_80132C20[wp->routine_0](wp, &wp->u_4E0.face);
    func_80117950(wp, face);
}

void func_80118404(STAGE_OBJ *wp)
{
    D_80132C28[wp->variant_3](wp, &wp->u_4E0.face);
}

void func_80118440(ST1A_OBJ *wp)
{
    ST1A_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->face;
    D_80132C30[wp->routine_0](wp, &Scene_work, face);
    func_80119114(wp, face);
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
        Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    }
}

void func_80118560(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->timer_0      = 0;
    face->value_2      = 0;
    func_801190C4(wp, face, 0);
    func_801190EC(wp, face, 0);
    if (wp->variant_3 == 0)
    {
        wp->scale.v.pad = 0x421;
        wp->anim_AC     = 1;
        face->shadow_12 = 0;
        wp->routine_0   = 1;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
        wp->anim_AC     = 0;
        face->shadow_12 = 1;
        wp->routine_0   = 2;
    }
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_80118638(ST1A_OBJ *wp, STAGE_SCENE_WORK *scene, ST1A_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x3C)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            face->timer_0++;
            wp->scale.v.pad = ((face->timer_0 >> 3) + 1) * 0x421;
            if (wp->scale.v.pad == 0x4210)
            {
                face->timer_0 = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 8 && scene->value_10 == 0x1E)
            {
                func_801190C4(wp, face, 8);
            }
            else if (scene->u_8.byte[1] == 0xA && scene->value_10 == 0xA)
            {
                func_801190C4(wp, face, 9);
                func_801190EC(wp, face, 9);
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->u_8.byte[1] == 0xB && scene->value_10 == 0x1E)
            {
                wp->anim_AC   = 2;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 0xC && scene->value_10 == 1)
            {
                face->shadow_12 = 1;
                wp->position.z -= 0x100;
                wp->position_fixed.v.z = wp->position.z << 16;
            }
            if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 3;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 0xD && scene->value_10 == 1)
            {
                wp->anim_AC   = 4;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 6:
            if (scene->u_8.byte[1] == 0xD)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x69:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x7D:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xC0:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0xD2:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xEB:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x104:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x14D:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x16D:
                        func_801190C4(wp, face, 3);
                        func_801190EC(wp, face, 0xB);
                        break;
                    case 0x17C:
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x1AE:
                        func_801190EC(wp, face, 3);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0xF && scene->value_10 == 1)
            {
                func_801190C4(wp, face, 4);
                func_801190EC(wp, face, 4);
            }
            else if (scene->u_8.byte[1] == 0x10 && scene->value_10 == 1)
            {
                func_801190C4(wp, face, 3);
                func_801190EC(wp, face, 5);
                wp->routine_1++;
            }
            break;
        case 7:
            if (scene->u_8.byte[1] == 0x10)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x23:
                        func_801190EC(wp, face, 5);
                        break;
                    case 0x50:
                        func_801190C4(wp, face, 5);
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x64:
                        func_801190EC(wp, face, 3);
                        break;
                    case 0x82:
                        func_801190C4(wp, face, 5);
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0xB4:
                        func_801190EC(wp, face, 3);
                        break;
                    case 0xC8:
                        func_801190C4(wp, face, 6);
                        func_801190EC(wp, face, 0xC);
                        break;
                    case 0x122:
                        func_801190EC(wp, face, 6);
                        break;
                    case 0x12C:
                        wp->anim_AC   = 5;
                        face->value_2 = 0;
                        wp->routine_1++;
                        break;
                }
            }
            break;
        case 8:
            if (scene->u_8.byte[1] == 0x10)
            {
                if (scene->value_10 == 0x140)
                {
                    func_801190C4(wp, face, 4);
                    func_801190EC(wp, face, 0xD);
                }
                else if (scene->value_10 == 0x168)
                {
                    func_801190EC(wp, face, 7);
                }
            }
            else if (scene->u_8.byte[1] == 0x12 && scene->value_10 == 1)
            {
                wp->rotation.y = 0x100;
                func_801190C4(wp, face, 4);
                func_801190EC(wp, face, 4);
                wp->anim_AC   = 4;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 9:
            if (scene->u_8.byte[1] == 0x12)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_801190EC(wp, face, 0xD);
                        break;
                    case 0x78:
                        wp->anim_AC   = 6;
                        face->value_2 = 0;
                        break;
                    case 0xDC:
                        func_801190EC(wp, face, 4);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x14 && scene->value_10 == 1)
            {
                func_801190C4(wp, face, 1);
                func_801190EC(wp, face, 1);
                wp->routine_1++;
            }
            break;
        case 10:
            if (scene->u_8.byte[1] == 0x14)
            {
                switch (scene->value_10)
                {
                    case 0x14:
                        func_801190C4(wp, face, 4);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x87:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x9F:
                        func_801190C4(wp, face, 4);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xFE:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x116:
                        func_801190C4(wp, face, 4);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x1A4:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x1A9:
                        func_801190C4(wp, face, 7);
                        wp->anim_AC   = 7;
                        face->value_2 = 0;
                        break;
                    case 0x1AE:
                        func_801190EC(wp, face, 0xD);
                        break;
                    case 0x217:
                        func_801190EC(wp, face, 4);
                        break;
                    case 0x230:
                        func_801190EC(wp, face, 0xD);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x15 && scene->value_10 == 1)
            {
                wp->rotation.y = 0x400;
                wp->anim_AC    = 4;
                face->value_2  = 0;
                func_801190C4(wp, face, 4);
                func_801190EC(wp, face, 8);
                wp->routine_1++;
            }
            break;
        case 11:
            if (scene->u_8.byte[1] == 0x16)
            {
                switch (scene->value_10)
                {
                    case 0xA:
                        func_801190EC(wp, face, 0xE);
                        break;
                    case 0x28:
                        func_801190EC(wp, face, 8);
                        break;
                    case 0x3C:
                        func_801190EC(wp, face, 0xE);
                        break;
                    case 0x69:
                        func_801190EC(wp, face, 8);
                        break;
                    case 0x78:
                        func_801190EC(wp, face, 0xE);
                        break;
                    case 0xBE:
                        func_801190EC(wp, face, 8);
                        break;
                    case 0xC8:
                        func_801190EC(wp, face, 0xE);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x17 && scene->value_10 == 1)
            {
                wp->rotation.y = 0;
                wp->anim_AC    = 8;
                face->value_2  = 0;
                func_801190C4(wp, face, 1);
                func_801190EC(wp, face, 1);
                wp->routine_1++;
            }
            break;
        case 12:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x18 && scene->value_10 == 0xA)
            {
                wp->routine_1++;
            }
            break;
        case 13:
            if (scene->u_8.byte[1] == 0x19 && scene->value_10 == 1)
            {
                wp->anim_AC   = 9;
                face->value_2 = 0;
                wp->routine_1++;
            }
            break;
        case 14:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x1E)
            {
                switch (scene->value_10)
                {
                    case 0x1E:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x3C:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x5A:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0xDC:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0xFA:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x190:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                    case 0x19A:
                        func_801190C4(wp, face, 0xA);
                        func_801190EC(wp, face, 0xA);
                        break;
                    case 0x1D6:
                        func_801190C4(wp, face, 1);
                        func_801190EC(wp, face, 1);
                        break;
                }
            }
            else if (scene->u_8.byte[1] == 0x1F && scene->value_10 == 0xA)
            {
                func_801190C4(wp, face, 0xA);
                func_801190EC(wp, face, 0xA);
                wp->routine_1++;
            }
            break;
        case 15:
            if (scene->u_8.byte[1] == 0x1F && scene->value_10 == 0x14)
            {
                func_801190C4(wp, face, 1);
                func_801190EC(wp, face, 1);
            }
            if (wp->value_A4 == 0x27)
            {
                wp->anim_AC   = 9;
                face->value_2 = 0x27;
                wp->routine_1++;
            }
            break;
        case 16:
            wp->anim_prev_AD = 0xFF;
            if (scene->u_8.byte[1] == 0x21 && scene->value_10 == 1)
            {
                face->shadow_12 = 0;
                wp->routine_1++;
            }
            break;
        case 17:
            wp->anim_prev_AD = 0xFF;
            break;
    }
}

void func_801190BC(void)
{
}

void func_801190C4(ST1A_OBJ *wp, ST1A_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80132D38[index];
}

void func_801190EC(ST1A_OBJ *wp, ST1A_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80132D64[index];
}

void func_80119114(ST1A_OBJ *wp, ST1A_FACE *face)
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
        Model_mesh_uv_copy(wp->model_88, 0xE000D, Model_uv_cell(face->shape_C, 0x3E, 0x3A, 4));
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
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_F, 0x3E, 0x3A, 4));
    }
    face->prev_10 = face->shape_F;
}

void func_8011925C(ST1A_OBJ *wp)
{
    ST1A_HIT *hit;

    hit = &wp->hit_440;
    D_80132DA0[wp->routine_0](wp);
    if (wp->value_4BA < 2)
    {
        if (Player_work.value_6E <= 0)
        {
            if (!(wp->hit_440.flags_0.word & 0x10200))
            {
                wp->value_4BA = 2;
                wp->value_4B8 = 0x3C;
                Sound_call2(0x1E9, &wp->position);
            }
            wp->hit_440.flags_0.half |= 0x200;
        }
        else
        {
            wp->hit_440.flags_0.half &= ~0x200;
        }
    }
    hit->value_18 = 0;
}

void func_80119320(ST1A_OBJ *wp)
{
    ST1A_BOSS *bp;
    sint32 i;

    bp = (ST1A_BOSS *)&wp->hit_440;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0;
    for (i = 0; i < 16; i++)
    {
        wp->part_180[i].pad = 0x4210;
    }
    wp->rotation.x     = 0;
    wp->rotation.z     = 0;
    wp->value_64.value = 0;
    wp->value_44.value = 0;
    wp->value_48.value = 0;
    bp->flags_0        = 0x26;
    bp->value_4        = 0;
    bp->value_8        = 0;
    bp->value_18       = 0;
    bp->value_1C       = 0;
    Track_reset(bp->track_28, 0, -0x60);
    bp->value_C    = 0;
    bp->value_52   = 0;
    bp->value_53   = 0;
    bp->value_54   = 0;
    bp->value_70   = 0;
    bp->value_72   = 0;
    bp->value_73   = 0;
    bp->value_7A   = -1;
    bp->value_78   = 0;
    bp->value_7E   = 0;
    bp->value_7C   = 0;
    bp->value_7D   = 0;
    bp->value_7F   = 0;
    bp->part_58[0] = Open_SHL_WORK();
    if (bp->part_58[0] != NULL)
    {
        bp->part_58[0]->flags_0  = 1;
        bp->part_58[0]->kind_2   = 0x34;
        bp->part_58[0]->value_C  = wp->value_1;
        bp->part_58[0]->value_D  = 5;
        wp->u_F8.part[5].value_3 = -1;
        bp->part_58[0]->value_6 |= 0x20;
    }
    bp->part_58[1] = Open_SHL_WORK();
    if (bp->part_58[1] != NULL)
    {
        bp->part_58[1]->flags_0   = 1;
        bp->part_58[1]->kind_2    = 0x34;
        bp->part_58[1]->value_C   = wp->value_1;
        bp->part_58[1]->value_D   = 0xA;
        wp->u_F8.part[10].value_3 = -1;
        bp->part_58[1]->value_6 |= 0x20;
    }
    bp->part_58[2] = Open_SHL_WORK();
    if (bp->part_58[2] != NULL)
    {
        bp->part_58[2]->flags_0  = 1;
        bp->part_58[2]->kind_2   = 0x34;
        bp->part_58[2]->value_C  = wp->value_1;
        bp->part_58[2]->value_D  = 6;
        wp->u_F8.part[6].value_3 = -1;
        bp->part_58[2]->value_6 |= 0x20;
    }
    bp->part_58[3] = Open_SHL_WORK();
    if (bp->part_58[3] != NULL)
    {
        bp->part_58[3]->flags_0   = 1;
        bp->part_58[3]->kind_2    = 0x34;
        bp->part_58[3]->value_C   = wp->value_1;
        bp->part_58[3]->value_D   = 0xB;
        wp->u_F8.part[11].value_3 = -1;
        bp->part_58[3]->value_6 |= 0x20;
    }
    wp->value_B2 = wp->value_B0 = wp->value_6E = D_8009884C[wp->kind_2]->life_8 << 7;
    wp->value_78                               = 0;
    wp->value_10                               = 0;
    D_80139738.life_0[0]                       = (sint16)(wp->value_6E / 10) * 9;
    D_80139738.life_0[1]                       = (sint16)(wp->value_6E / 10) * 6;
    D_80139738.life_0[2]                       = (sint16)(wp->value_6E / 10) * 4;
    D_80139738.life_0[3]                       = (sint16)(wp->value_6E / 10);
    D_80139738.end_10                          = -1;
    bp->life_74                                = D_80139738.life_0;
    wp->routine_0                              = 1;
    wp->routine_1                              = 0;
    *(uint16 *)&wp->routine_2                  = 0;
    func_800322A8(wp, 0, 0);
    func_8005D620(wp, 0, 0, 0x81, 0x805058);
    func_80119714(wp);
}

void func_80119714(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    sint32 i;

    bp                      = (ST1A_BLOCK *)&wp->hit_440;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    for (i = 0; i < 16; i++)
    {
        wp->part_180[i].pad = 0x4210;
    }
    bp->hit_0.flags_0.h[1] = rand();
    func_8005D4C0();
    wp->u_E.b.byte_E &= 0xF8;
    wp->u_E.b.byte_F &= 0x11;
    if (bp->hit_0.flags_0.half & 4)
    {
        func_8011C260(wp);
    }
    D_80132DAC[wp->routine_1](wp);
    wp->value_78 = D_80132DE4[bp->value_53];
    if (wp->value_78 != 0)
    {
        bp->hit_0.value_C = Obj_map_push_out(wp);
    }
    else
    {
        bp->hit_0.value_C = 0;
    }
    if (bp->hit_0.flags_0.half & 1)
    {
        switch (wp->routine_1)
        {
            case 5:
                if (wp->value_6E > 0 && --bp->value_70 != 0)
                {
                    *(uint16 *)&wp->routine_2 = 0;
                    break;
                }
                // fall through
            case 0:
            case 2:
            case 3:
            case 4:
            case 6:
                if (wp->value_6E > 0)
                {
                    func_8011C080(wp);
                }
                else
                {
                    wp->routine_1 = 7;
                }
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 1:
                wp->routine_1             = 2;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            default:
                wp->routine_1             = 0;
                *(uint16 *)&wp->routine_2 = 0;
                break;
        }
        bp->hit_0.flags_0.half &= ~1;
    }
    if (bp->hit_0.value_A != 0)
    {
        bp->hit_0.value_A--;
    }
    if (bp->value_78 != 0)
    {
        bp->value_78--;
    }
    else
    {
        bp->value_7A = -1;
    }
    if (bp->hit_0.flags_0.half & 0x20)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
    }
    else
    {
        Model_pose_unpack(wp);
        Model_parts_mtx_set_y(wp);
    }
    wp->value_44.half[0] = (wp->position.x - wp->position_prev.x) << 4;
    wp->value_44.half[1] = (wp->position.y - wp->position_prev.y) << 4;
    wp->value_48.half[0] = (wp->position.z - wp->position_prev.z) << 4;
    if ((wp->flags_0 & 2) && wp->part_180[0].pad == 0x4210)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (bp->hit_0.flags_0.half & 2))
    {
        bp->target_38.x = 0;
        if (bp->hit_0.flags_0.half & 0x400)
        {
            bp->target_38.y = -0x200;
        }
        else
        {
            bp->target_38.y = 0x200;
        }
        bp->target_38.z = 0;
        ApplyMatrix(&wp->matrix_240.m, &bp->target_38, &bp->fixed_40);
        bp->hit_0.pos_10.x = wp->part_180[0].x + bp->fixed_40.x;
        bp->hit_0.pos_10.y = wp->part_180[0].y + bp->fixed_40.y;
        bp->hit_0.pos_10.z = wp->part_180[0].z + bp->fixed_40.z;
        func_800341BC(&bp->hit_0.pos_10, 0x68, 0, 0x8000, wp->value_1, &bp->hit_0.value_18, D_80132DF0[bp->value_52] | bp->hit_0.value_8, 0,
                      0);
    }
}

void func_80119AF8(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_80119B18(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    ST1A_FLASH *fp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->hit_440.flags_0.half |= 0x20;
            wp->value_490       = -0x60;
            wp->anim_AC         = 0;
            wp->hit_440.value_4 = 0;
            wp->hit_440.value_8 = D_8009884C[wp->kind_2]->value_A;
            wp->value_493       = 0;
            wp->value_492       = 0;
            fp                  = (ST1A_FLASH *)Open_SHL_WORK();
            if (fp != NULL)
            {
                fp->flags_0      = 1;
                fp->kind_2       = 0x33;
                fp->variant_3    = 0xFD;
                fp->size_2C.x    = 0xC8;
                fp->size_2C.y    = 0xC8;
                fp->size_2C.z    = 0xC8;
                fp->size_2C.pad  = 0x700;
                fp->position.y   = 0x10;
                fp->position.z   = 0x10;
                fp->position.pad = 0x500;
                fp->position.x   = 0;
                fp->routine_3    = 0x3C;
                fp->routine_2    = 0;
            }
            // fall through
        case 1:
            wp->value_4C.words.integer = bp->value_50 + Obj_ceiling_height_get(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 8) >> 16) + wp->value_4C.words.integer, 0);
            if (bp->hit_0.value_4 == 0x3F)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 1) & 0x3F;
            break;
    }
}

void func_80119CA0(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0xD;
            wp->routine_2++;
            bp->hit_0.value_4 = 0;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_B;
            bp->value_53      = 1;
            bp->value_52      = 0;
            if (bp->value_7A <= 0 && !(bp->hit_0.flags_0.h[1] & 3))
            {
                bp->value_7A = 1;
                bp->value_78 = 0x3C;
                Sound_call2(0x1E4, &wp->position);
            }
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0xE;
                wp->routine_2++;
                bp->hit_0.value_4 = 0x10;
                bp->value_50      = -0x100;
                bp->value_52      = 1;
            }
            break;
        case 2:
            wp->rotation.y             = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x100)) & 0xFFF;
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + Obj_ceiling_height_get(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                wp->anim_AC = 0xF;
                wp->routine_2++;
                bp->value_54      = 0x78;
                bp->value_50      = 0xC0;
                bp->hit_0.value_4 = 0;
                bp->hit_0.value_6 = 0;
                bp->value_52      = 1;
                Sound_call2(0x1D3, &wp->position);
                bp->hit_0.flags_0.half |= 0x400;
            }
            break;
        case 3:
            wp->rotation.y             = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 8)) & 0xFFF;
            wp->value_4C.words.integer = STAGE_PL.value_3AA + bp->value_50 - wp->position.y;
            Obj_pos_set(wp, wp->value_4C.half[0], ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 22) + wp->value_4C.words.integer, 0);
            if (wp->value_4C.half[0] < 0x600)
            {
                wp->value_4C.half[0] += 0x60;
            }
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 2) & 0x3F;
            if (bp->hit_0.value_6 < 0x40)
            {
                bp->hit_0.value_6 += 4;
            }
            if ((bp->hit_0.value_C & 0xF00) || --bp->value_54 < 0)
            {
                wp->anim_AC = 0x10;
                wp->routine_2++;
                bp->hit_0.value_4 = 0x10;
                bp->value_50      = -0x180;
                bp->value_52      = 0;
                bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
                Sound_call2(0x1D4, &wp->position);
            }
            break;
        case 4:
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + Obj_ceiling_height_get(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half = (bp->hit_0.flags_0.half | 1) & ~0x400;
            }
            break;
    }
}

void func_8011A080(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    sint32 i;
    uint16 c;
    sint16 turn;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC                = 0xD;
            wp->value_64.words.integer = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
            if (wp->value_64.words.integer < 0)
            {
                turn = -0x40;
            }
            else
            {
                turn = 0x40;
            }
            wp->value_64.half[0]       = turn >> 2;
            wp->value_64.words.integer = turn;
            bp->value_50               = 0x60;
            bp->hit_0.value_4          = 0x10;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
            bp->value_53      = 2;
            bp->value_52      = 0;
            bp->hit_0.flags_0.half &= ~2;
            Sound_call2(0x1DC, &wp->position);
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer += wp->value_64.half[0];
            wp->value_4C.words.integer = bp->value_50 + Obj_ceiling_height_get(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = bp->hit_0.value_4 & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            wp->u_E.b.byte_F |= 2;
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                wp->flags_0 &= ~2;
                bp->hit_0.value_4 = 0xF;
            }
            break;
        case 2:
            if (--bp->hit_0.value_4 >= 0)
            {
                break;
            }
            bp->hit_0.value_4 = 0x10;
            bp->value_50      = -0x60;
            bp->fixed_40.y    = 0xFF3F0000;
            bp->fixed_40.z    = 0x4000000;
            wp->anim_AC       = 0;
            bp->fixed_40.x    = 0;
            wp->flags_0 |= 2;
            wp->routine_2++;
            func_80030150(&bp->fixed_40, &bp->target_38);
            func_8002FFC4(&bp->target_38, &bp->fixed_40, Angle_xz_svector(&bp->target_38, &wp->position_prev) & 0xFFF, 0x3000, 0, 0);
            wp->position         = bp->target_38;
            wp->position_fixed.v = bp->fixed_40;
            wp->rotation.y       = Angle_xz_svector(&wp->position, &Player_work.position) & 0xFFF;
            Sound_call2(0x20B, &wp->position);
            // fall through
        case 3:
            wp->value_4C.words.integer = bp->value_50 + Obj_ceiling_height_get(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = (0x10 - bp->hit_0.value_4) & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            wp->u_E.b.byte_F |= 2;
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half |= 3;
            }
            break;
    }
}

void func_8011A488(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 6;
            wp->routine_2++;
            bp->value_50      = 0x60;
            bp->hit_0.value_4 = 0;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
            bp->value_53      = 0;
            bp->value_52      = 0;
            bp->value_72[0]   = 0;
            bp->value_72[1]   = 0;
            Sound_call2(0x1D7, &wp->position);
            if (bp->value_7A <= 0)
            {
                bp->value_7A = 1;
                bp->value_78 = 0x3C;
                Sound_call2(0x1E3, &wp->position);
            }
            break;
        case 1:
            wp->rotation.y             = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) & 0xFFF;
            wp->value_4C.words.integer = STAGE_PL.value_3AA + bp->value_50 - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 22) + wp->value_4C.words.integer, 0);
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 2) & 0x3F;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 7;
                wp->routine_2++;
                bp->hit_0.flags_0.half &= ~0x180;
                if (func_8011BD08(wp, 0) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x80;
                }
                if (func_8011BD08(wp, 1) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x100;
                }
                if (bp->hit_0.flags_0.half & 0x180)
                {
                    Sound_call2(0x1D8, &wp->position);
                }
                wp->value_64.words.integer = 0;
                wp->value_64.half[0]       = (bp->hit_0.flags_0.h[1] & 1) ? 2 : -2;
                wp->u_E.b.byte_F |= 0x40;
            }
            func_8011BDD8(wp, 0);
            func_8011BDD8(wp, 1);
            bp->value_72[0]++;
            bp->value_72[1]++;
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer += wp->value_64.half[0];
            if (bp->value_72[0] != 0)
            {
                func_8011BDD8(wp, 0);
                bp->value_72[0]--;
            }
            if (bp->value_72[1] != 0)
            {
                func_8011BDD8(wp, 1);
                bp->value_72[1]--;
            }
            if (wp->value_A7 < 0)
            {
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    bp->slot_68[0]->value_E = 1;
                }
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    bp->slot_68[1]->value_E = 1;
                }
                wp->routine_2++;
                wp->u_E.b.byte_F = (wp->u_E.b.byte_F & ~0x10) | 0x80;
            }
            break;
        case 3:
            if (wp->u_E.b.byte_F & 0x10)
            {
                wp->u_E.b.byte_F &= ~0x10;
                wp->anim_AC = 8;
                wp->routine_2++;
                bp->hit_0.value_4 = 0x10;
                bp->value_50      = -0x180;
            }
            break;
        case 4:
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + Obj_ceiling_height_get(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011A8A8(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    STCOM_EFFECT *fx;
    sint32 i;
    uint16 c;
    sint16 turn;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0;
            wp->routine_2++;
            bp->hit_0.value_4 = 0x10;
            bp->value_50      = -0x180;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_E;
            bp->value_53      = 0;
            bp->value_52      = 0;
            break;
        case 1:
            wp->value_4C.words.integer = wp->position.y - (bp->value_50 + Obj_ceiling_height_get(wp));
            Obj_pos_set(wp, 0, (D_800BBD38[bp->hit_0.value_4] * wp->value_4C.words.integer) >> 12, 0);
            if (--bp->hit_0.value_4 < 0)
            {
                wp->anim_AC = 0xD;
                wp->routine_2++;
                wp->value_64.words.integer = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
                if (wp->value_64.words.integer < 0)
                {
                    turn = -0x40;
                }
                else
                {
                    turn = 0x40;
                }
                wp->value_64.half[0]       = turn >> 2;
                wp->value_64.words.integer = turn;
                bp->value_53               = 2;
                bp->hit_0.value_4          = 0x10;
                bp->value_50               = 0x60;
                bp->hit_0.flags_0.half &= ~2;
                Sound_call2(0x1DC, &wp->position);
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer += wp->value_64.half[0];
            wp->value_4C.words.integer = bp->value_50 + Obj_ceiling_height_get(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = bp->hit_0.value_4 & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            wp->u_E.b.byte_F |= 2;
            if (--bp->hit_0.value_4 < 0)
            {
                wp->flags_0 &= ~2;
                wp->routine_2++;
                bp->hit_0.value_4      = 0x40;
                bp->hit_0.value_6      = 0;
                wp->position_fixed.v.y = 0xFFBF0000;
                wp->position_fixed.v.x = 0;
                wp->position_fixed.v.z = 0x4000000;
                func_80030150(&wp->position_fixed.v, &wp->position);
                Sound_call2(0x1DD, &wp->position);
            }
            break;
        case 3:
            if (bp->hit_0.value_4 % 3 == 0)
            {
                Swing_Camera2(++bp->hit_0.value_6, 0x800, 0xC00, &wp->position);
            }
            if (!(bp->hit_0.value_6 & 1))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x1D;
                    fx->variant_3       = 0x42;
                    fx->value_C         = 1;
                    fx->value_D         = 1;
                    fx->timer_E         = 0;
                    fx->sprite.position = wp->position;
                    fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.y = Obj_ceiling_height_get(wp);
                    fx->sprite.position.z += (rand() & 0xFF) - 0x80;
                }
            }
            if (--bp->hit_0.value_4 >= 0)
            {
                break;
            }
            wp->anim_AC = 0xB;
            wp->flags_0 |= 2;
            wp->routine_2++;
            bp->hit_0.value_4 = 0x10;
            bp->value_50      = -0x100;
            wp->rotation.y    = Angle_xz_svector(&wp->position, &Player_work.position) & 0xFFF;
            wp->u_E.b.byte_F |= 4;
            wp->value_64.words.integer = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800);
            if (wp->value_64.words.integer < 0)
            {
                turn = -0x80;
            }
            else
            {
                turn = 0x80;
            }
            wp->value_64.words.integer = turn;
            wp->value_64.half[0]       = turn >> 3;
            Sound_call2(0x20A, &wp->position);
            Sound_call2(0x1DE, &wp->position);
            // fall through
        case 4:
            if (bp->hit_0.value_4 % 3 == 0)
            {
                Swing_Camera2(++bp->hit_0.value_6, 0x800, 0xC00, &wp->position);
            }
            if (!(bp->hit_0.value_6 & 3))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x1D;
                    fx->variant_3       = 0x42;
                    fx->value_C         = 1;
                    fx->value_D         = 1;
                    fx->timer_E         = 0;
                    fx->sprite.position = wp->position;
                    fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.y = Obj_ceiling_height_get(wp);
                    fx->sprite.position.z += (rand() & 0xFF) - 0x80;
                }
            }
            wp->rotation.y = (wp->rotation.y + wp->value_64.words.integer) & 0xFFF;
            wp->value_64.words.integer -= wp->value_64.half[0];
            wp->value_4C.words.integer = bp->value_50 + Obj_ceiling_height_get(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 24) + wp->value_4C.words.integer, 0);
            for (i = 0; i < 16; i++)
            {
                c                   = (0x10 - bp->hit_0.value_4) & 0x1F;
                wp->part_180[i].pad = c | (c << 5) | (c << 10) | 0x8000;
            }
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                bp->hit_0.flags_0.half |= 2;
                wp->u_E.b.byte_F = (wp->u_E.b.byte_F | 8) & ~0x10;
                Sound_call2(0x1DF, &wp->position);
            }
            break;
        case 5:
            if (wp->u_E.b.byte_F & 0x10)
            {
                wp->u_E.b.byte_F &= ~0x10;
                wp->anim_AC = 0xC;
                wp->routine_2++;
                if (bp->value_7A <= 0)
                {
                    bp->value_7A = 1;
                    bp->value_78 = 0x3C;
                    Sound_call2(0x1E8, &wp->position);
                }
            }
            break;
        case 6:
            if (wp->value_A7 < 0)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011B000(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    STCOM_EFFECT *fx;
    sint32 angle;
    sint16 ground;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC       = 1;
            wp->value_490     = -0x60;
            bp->hit_0.value_4 = 0x1E;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
            wp->value_493     = 0;
            wp->value_492     = 0;
            if (func_8011E9E8(&Player_work.position) != 0)
            {
                bp->target_38 = Player_work.position;
            }
            else
            {
                bp->fixed_40.y = 0xFF3F0000;
                bp->fixed_40.x = 0;
                bp->fixed_40.z = 0x4000000;
                func_80030150(&bp->fixed_40, &bp->target_38);
                angle = Angle_xz_svector(&bp->target_38, &Player_work.position) & 0xFFF;
                func_8002FFC4(&bp->target_38, &bp->fixed_40, angle, (Distance_xz(&bp->target_38, &Player_work.position) - 0x100) * 16, 0,
                              0);
            }
            wp->rotation.y       = (wp->rotation.y + Muku(&wp->position, &bp->target_38, wp->rotation.y, 0x800)) & 0xFFF;
            wp->value_4C.half[0] = Distance_xz(&wp->position, &bp->target_38) / (bp->hit_0.value_4 + 2);
            Sound_call2(0x1D5, &wp->position);
            break;
        case 1:
            wp->value_4C.words.integer = (0x10 - bp->hit_0.value_4) << 2;
            bp->hit_0.value_4--;
            Obj_pos_set(wp, wp->value_4C.half[0] * 16, wp->value_4C.words.integer * 16, 0);
            if (wp->value_A7 < 0 && wp->anim_AC != 4 && ++wp->anim_AC == 4)
            {
                bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_C;
                wp->value_492     = 1;
            }
            ground = Obj_ceiling_height_get(wp);
            if (ground < wp->position.y)
            {
                wp->position_fixed.v.y = ground << 16;
                wp->position.y         = ground;
                wp->anim_AC            = 5;
                wp->routine_2++;
                bp->hit_0.value_4 = 0;
                bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_A;
                bp->value_52      = 0;
                fx                = func_80031618();
                if (fx != NULL)
                {
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 6;
                    fx->flags_0           = 5;
                    fx->value_F           = 2;
                    fx->sprite.position   = wp->position;
                    fx->sprite.position.y = Obj_ceiling_height_get(wp);
                    Sound_call2(0x1E0, &wp->position);
                    Sound_call2(0x1D6, &wp->position);
                }
            }
            break;
        case 2:
            if (!(bp->hit_0.value_4 & 3))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x1D;
                    fx->variant_3       = 0x41;
                    fx->value_C         = 1;
                    fx->value_D         = 2;
                    fx->timer_E         = 0;
                    fx->sprite.position = wp->position;
                    fx->sprite.position.x += (rand() & 0x1FF) - 0x100;
                    fx->sprite.position.y = Obj_ceiling_height_get(wp);
                    fx->sprite.position.z += (rand() & 0x1FF) - 0x100;
                    Swing_Camera2(0x1E, 0x800, 0xC00, &fx->sprite.position);
                }
            }
            bp->hit_0.value_4++;
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                bp->hit_0.value_4 = 0xA;
            }
            break;
        case 3:
            if (--bp->hit_0.value_4 < 0)
            {
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011B4B4(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 0;
            wp->routine_2++;
            bp->value_50      = -0x180;
            bp->hit_0.value_4 = 0;
            bp->hit_0.value_6 = 0x10;
            bp->hit_0.flags_0.half |= 0x20;
            bp->hit_0.value_8 = D_8009884C[wp->kind_2]->value_D;
            bp->value_53      = 0;
            bp->value_52      = 0;
            wp->u_C.b.byte_C  = 0;
            if (bp->value_7A <= 0)
            {
                bp->value_7A = 1;
                bp->value_78 = 0x3C;
                Sound_call2(0x1E2, &wp->position);
            }
            break;
        case 1:
            wp->value_4C.words.integer = STAGE_PL.value_3AA + bp->value_50 - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 16) >> 22) + wp->value_4C.words.integer, 0);
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 2) & 0x3F;
            if (--bp->hit_0.value_6 < 0)
            {
                wp->anim_AC = 9;
                wp->routine_2++;
                bp->hit_0.value_4          = 0x15;
                bp->hit_0.value_6          = 7;
                bp->value_72[0]            = 0;
                bp->value_72[1]            = 0;
                wp->value_64.words.integer = 0;
                Sound_call2(0x1D9, &wp->position);
            }
            break;
        case 2:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[5], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            if (bp->hit_0.value_6 == 0)
            {
                func_8011BDD8(wp, 0);
                bp->value_72[0]++;
                if (bp->hit_0.value_4 == 0)
                {
                    wp->routine_2++;
                    bp->hit_0.value_4 = 6;
                    bp->value_72[0] += bp->value_72[0] & 1;
                }
                else
                {
                    bp->hit_0.value_4--;
                }
            }
            else
            {
                bp->hit_0.value_6--;
            }
            break;
        case 3:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[5], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            if (bp->value_72[0] < 0)
            {
                func_8011BDD8(wp, 0);
                bp->value_72[0] -= 4;
            }
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                wp->u_E.b.byte_E |= 2;
                bp->hit_0.flags_0.half &= ~0x80;
                if (func_8011BD08(wp, 0) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x80;
                }
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    Sound_call2(0x1D8, &wp->position);
                }
            }
            break;
        case 4:
            if (wp->u_C.b.byte_C == 2)
            {
                Sound_call2(0x1D9, &wp->position);
                wp->routine_2++;
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    bp->slot_68[0]->value_E = 1;
                }
                bp->hit_0.value_4          = 0x15;
                wp->value_64.words.integer = 0;
            }
            break;
        case 5:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[10], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            func_8011BDD8(wp, 1);
            bp->value_72[1]++;
            if (bp->hit_0.value_4 == 0)
            {
                wp->anim_AC = 0xA;
                wp->routine_2++;
                bp->hit_0.value_4 = 6;
                bp->value_72[1] += bp->value_72[1] & 1;
            }
            else
            {
                bp->hit_0.value_4--;
            }
            break;
        case 6:
            if (wp->value_64.words.integer < 0x80)
            {
                wp->value_64.words.integer += 0x10;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->part_180[10], &Player_work.position, wp->rotation.y, wp->value_64.words.integer)) & 0xFFF;
            if (bp->value_72[1] < 0)
            {
                func_8011BDD8(wp, 1);
                bp->value_72[1] -= 4;
            }
            if (--bp->hit_0.value_4 < 0)
            {
                wp->routine_2++;
                wp->u_E.b.byte_E |= 1;
                bp->hit_0.flags_0.half &= ~0x100;
                if (func_8011BD08(wp, 1) != 0)
                {
                    bp->hit_0.flags_0.half |= 0x100;
                }
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    Sound_call2(0x1D8, &wp->position);
                }
            }
            break;
        case 7:
            if (wp->u_C.b.byte_C == 4)
            {
                wp->routine_2++;
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    bp->slot_68[1]->value_E = 1;
                }
                wp->anim_AC = 0;
                wp->u_E.b.byte_E |= 4;
                bp->hit_0.value_4 = 8;
            }
            break;
        case 8:
            if (--bp->hit_0.value_4 < 0)
            {
                wp->u_E.b.byte_F &= ~0x10;
                bp->hit_0.flags_0.half |= 1;
            }
            break;
    }
}

void func_8011BA74(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    ST1A_FLASH *fp;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->hit_440.flags_0.half |= 0x20;
            wp->value_490       = -0x60;
            wp->anim_AC         = 0;
            wp->hit_440.value_4 = 0;
            wp->hit_440.value_8 = D_8009884C[wp->kind_2]->value_A;
            wp->value_493       = 0;
            wp->value_492       = 0;
            fp                  = (ST1A_FLASH *)Open_SHL_WORK();
            if (fp != NULL)
            {
                fp->flags_0      = 1;
                fp->kind_2       = 0x33;
                fp->variant_3    = 0xFD;
                fp->position.x   = 0xC8;
                fp->position.y   = 0xC8;
                fp->position.z   = 0xC8;
                fp->position.pad = 0x700;
                fp->size_2C.y    = 0x10;
                fp->size_2C.z    = 0x10;
                fp->size_2C.pad  = 0x500;
                fp->size_2C.x    = 0;
                fp->routine_3    = 0x3C;
                fp->routine_2    = 0;
            }
            Sound_fade_start(0x10);
            // fall through
        case 1:
            wp->value_4C.words.integer = bp->value_50 + Obj_ceiling_height_get(wp) - wp->position.y;
            Obj_pos_set(wp, 0, ((D_800BBCF8[bp->hit_0.value_4] << 8) >> 16) + wp->value_4C.words.integer, 0);
            if (bp->hit_0.value_4 == 0x3F)
            {
                if (bp->hit_0.flags_0.half & 0x80)
                {
                    bp->slot_68[0]->value_E = 1;
                }
                if (bp->hit_0.flags_0.half & 0x100)
                {
                    bp->slot_68[1]->value_E = 1;
                }
                bp->hit_0.flags_0.half &= ~0x180;
                func_8003187C(wp);
                Close_SHL_WORK(bp->part_58[0]);
                Close_SHL_WORK(bp->part_58[1]);
                Close_SHL_WORK(bp->part_58[2]);
                Close_SHL_WORK(bp->part_58[3]);
                Sce_flag_on(0x58);
            }
            bp->hit_0.value_4 = (bp->hit_0.value_4 + 1) & 0x3F;
            break;
    }
}

sint32 func_8011BC80(void)
{
    STAGE_OBJ *op;

    op = func_80031498();
    if (op != NULL)
    {
        op->flags_0            = 1;
        op->kind_2             = 0x13;
        op->value_4            = 2;
        op->variant_3          = 0;
        op->position_fixed.v.y = -0xC10000;
        op->u_E.b.byte_F       = 1;
        op->position_fixed.v.x = 0;
        op->position_fixed.v.z = 0x08FC0000;
        op->rotation.y         = 0;
        func_80030150(&op->position_fixed.v, &op->position);
        op->flags_6 |= 0x20;
        return 0;
    }
    return 1;
}

sint32 func_8011BD08(ST1A_OBJ *wp, sint32 i)
{
    ST1A_BLOCK *bp = (ST1A_BLOCK *)&wp->hit_440;

    bp->slot_68[i] = (ST1A_10C *)Open_SHL_WORK();
    if (bp->slot_68[i] != NULL)
    {
        bp->slot_68[i]->flags_0   = 1;
        bp->slot_68[i]->kind_2    = 0x30;
        bp->slot_68[i]->value_4   = 0;
        bp->slot_68[i]->variant_3 = 0;
        bp->slot_68[i]->value_C   = wp->table_4A0[i].value_1;
        bp->slot_68[i]->value_D   = i;
        bp->slot_68[i]->value_E   = 0;
        bp->slot_68[i]->value_F   = 0;
        return 1;
    }
    return 0;
}

void func_8011BDD8(ST1A_OBJ *wp, uint8 side)
{
    ST1A_BLOCK *bp;
    STCOM23_PACKET *p;
    STCOM_SVECTOR pos;
    sint16 angle;
    sint16 t;
    sint16 dist;
    sint16 dy;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 i;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    for (i = 0; i < 24; i++)
    {
        t = bp->value_72[side];
        if (D_80132DFC[i].start_0 < t && t < D_80132DFC[i].start_0 + 16)
        {
            p     = Billboard_get();
            t     = bp->value_72[side] - D_80132DFC[i].start_0;
            angle = (D_80132DFC[i].angle_4 + t * 24) & 0xFFF;
            dy    = D_80132DFC[i].dy_6 - t * (D_80132DFC[i].dy_6 / 16);
            dist  = D_80132DFC[i].dist_2 - t * (D_80132DFC[i].dist_2 / 16);
            if (t < 16)
            {
                r = (t + 1) * 8;
                g = r;
                b = r;
            }
            else
            {
                r = 0x80;
                g = 0x80;
                b = 0x80;
            }
            pos.x      = bp->part_58[2][side].position.x + ((rsin(angle) * dist) >> 12);
            pos.z      = bp->part_58[2][side].position.z + ((rcos(angle) * dist) >> 12);
            pos.y      = bp->part_58[2][side].position.y + dy;
            p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
            p->xy_8    = (pos.y << 16) + pos.x;
            p->z_10    = pos.z;
            p->uv_C    = 0x3D482040;
            p->uv_1C   = 0x3F40;
            p->uv_24   = 0x3F5F;
            p->uv_14   = 0x2E205F;
            p->size_18 = t + 8;
            p->pad_20  = 0;
        }
    }
}

// Register allocation: the one-pass loop pins the flags load after ai's set, so ai lives 84 insns
// and ties sum's priority; sum, declared first, has the lower pseudo number and wins the tie (t1).
// The loop around the routine stores weights i's reference so i outranks its extended copies.
sint32 func_8011C080(ST1A_OBJ *wp)
{
    sint16 sum;
    ST1A_AI *ai;
    uint8 *tbl;
    sint16 i;
    sint16 acc;
    uint16 flags;
    uint8 c;
    sint32 lt;

    ai = (ST1A_AI *)&wp->hit_440;
    do
    {
        flags = wp->hit_440.flags_0.half;
    } while (0);
    if (!(flags & 0x40))
    {
        wp->hit_440.flags_0.half = flags | 0x40;
        tbl                      = D_80132EBC;
    }
    else
    {
        do
        {
            lt = wp->value_6E < wp->value_B0 >> 1;
        } while (0);
        tbl = D_80132ECC;
        if (!lt)
        {
            tbl = D_80132EC4;
        }
        wp->hit_440.flags_0.half = flags & ~0x40;
    }
    for (sum = 0, i = 0; i < 5; i++)
    {
        if (ai->last_7C == D_80132EDC[i] && ai->count_7D >= 2)
        {
            D_80132ED4[i] = 0;
        }
        else
        {
            c = tbl[i];
            sum += c;
            D_80132ED4[i] = c;
        }
    }
    acc = 0;
    for (i = 0; i < 5; i++)
    {
        acc += tbl[i];
        if (ai->rand_2 % sum < acc)
        {
            break;
        }
    }
    do
    {
        wp->routine_1             = D_80132EDC[i];
        *(uint16 *)&wp->routine_2 = 0;
    } while (0);
    if (wp->routine_1 == 5)
    {
        ai->value_70 = 1;
    }
    if (ai->last_7C == wp->routine_1)
    {
        ai->count_7D++;
    }
    else
    {
        ai->count_7D = 0;
    }
    ai->last_7C = wp->routine_1;
    return 1;
}

sint32 func_8011C260(ST1A_OBJ *wp)
{
    ST1A_DAMAGE *dm;
    sint32 damage;
    sint32 i;

    dm     = (ST1A_DAMAGE *)&wp->hit_440;
    damage = dm->hit_18 & 0xFFFFFF;
    if (damage != 0)
    {
        if (dm->hit_18 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                if (func_80042208() != 0)
                {
                    dm->flags_0 &= ~0xC;
                    wp->value_B2 = 0;
                    wp->value_6E = 0;
                    damage       = D_8009884C[wp->kind_2]->value_9;
                }
                else
                {
                    wp->value_6E = 1;
                }
            }
            if (dm->timer_7A < 0)
            {
                if (wp->value_6E < *dm->life_74)
                {
                    dm->timer_7A = 0;
                    dm->value_78 = 0x3C;
                    dm->life_74++;
                    Sound_call2(0x1E1, &wp->position);
                }
            }
            if (dm->timer_7A < 3)
            {
                if (wp->value_6E < (sint16)(wp->value_B0 / 10) * 7 && !(dm->flags_0 & 0x800))
                {
                    dm->timer_7A = 3;
                    dm->value_78 = 0x3C;
                    dm->flags_0 |= 0x800;
                    Sound_call2(0x1E5, &wp->position);
                }
                else if (wp->value_6E < (sint16)(wp->value_B0 / 10) * 5 && !(dm->flags_0 & 0x1000))
                {
                    dm->timer_7A = 3;
                    dm->value_78 = 0x3C;
                    dm->flags_0 |= 0x1000;
                    Sound_call2(0x1E6, &wp->position);
                }
                else if (wp->value_6E < (sint16)(wp->value_B0 / 10) * 2 && !(dm->flags_0 & 0x2000))
                {
                    dm->timer_7A = 3;
                    dm->value_78 = 0x3C;
                    dm->flags_0 |= 0x2000;
                    Sound_call2(0x1E7, &wp->position);
                }
            }
            if (dm->flags_0 & 8)
            {
                dm->stagger_A += damage;
                if ((dm->hit_18 & 0x20000000) || dm->stagger_A >= D_8009884C[wp->kind_2]->value_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    dm->stagger_A = 0;
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            for (i = 0; i < 16; i++)
            {
                wp->part_180[i].pad = 0x7FFF;
            }
            wp->u_E.b.byte_F |= 2;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_8011C5C4(STAGE_OBJ *wp)
{
    D_80132EE4[wp->routine_0](wp);
    Model_Shadow_Trans(wp, 0x100, 0x200, 0);
}

void func_8011C620(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    wp->flags_0 |= 0x42;
    Model_work_init(wp, NULL);
    func_80033500(wp);
    bp = (ST1A_BLOCK *)&wp->hit_440;
    Mem_clear(bp, &wp->value_520);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->value_51C      = 0;
    if (STAGE_GAME.value_5B >= 2)
    {
        wp->value_520 = 1;
    }
    else
    {
        wp->value_520 = 0;
    }
    wp->position.y          = -0x33;
    wp->position.x          = 0;
    wp->position.z          = 0x400;
    wp->position_prev       = wp->position;
    wp->position_fixed.v.y  = -0x330000;
    wp->position_fixed.v.x  = 0;
    wp->position_fixed.v.z  = 0x4000000;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->routine_0           = 1;
    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    wp->value_64.value      = 0;
    wp->value_44.value      = 0;
    wp->value_48.value      = 0;
    wp->rotation.y          = 0;
    wp->value_78            = 0;
    wp->value_10            = 0;
    wp->routine_1           = 0;
    bp->value_98            = 1;
    bp->value_9A            = 0;
    bp->value_9B            = 0;
    if (bp->value_98 > 0)
    {
        bp->value_98 = 0;
        func_800322A8(wp, bp->value_9A, bp->value_9B);
    }
    else if (bp->value_98 == 0)
    {
        func_80032488(wp);
    }
}

void func_8011C790(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    func_8011ED6C(wp);
    D_80132EF0[wp->routine_1](wp);
    bp = (ST1A_BLOCK *)&wp->hit_440;
    if (wp->value_4D8 > 0)
    {
        wp->value_4D8 = 0;
        func_800322A8(wp, wp->value_4DA, wp->value_4DB);
    }
    else if (wp->value_4D8 == 0)
    {
        func_80032488(wp);
    }
    func_8011EAFC(wp, bp->value_9C);
}
