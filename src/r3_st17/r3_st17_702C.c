#include "common.h"
#include "st17.h"

void func_8010702C(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
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
            wp->anim_AC        = 6;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            face->value_2      = 0x37;
            face->timer_0      = 0;
            func_801072E0(wp, face, 0);
            func_80107308(wp, face, 0);
            wp->routine_0++;
            // fall through
        case 1:
            if (face->timer_0 == 0x92)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_AC   = 7;
            face->value_2 = 0;
            wp->routine_0++;
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            wp->anim_AC = 8;
            wp->routine_0++;
            break;
        case 5:
            break;
    }
    face->timer_0++;
    switch (Scene_work.value_10)
    {
        case 0x1E:
            func_80107308(wp, face, 1);
            break;
        case 0x37:
            func_80107308(wp, face, 1);
            break;
        case 0x87:
            func_801072E0(wp, face, 1);
            func_80107308(wp, face, 0);
            break;
        case 0x91:
            func_80107308(wp, face, 1);
            break;
        case 0x2D:
        case 0xAF:
            func_80107308(wp, face, 0);
            break;
    }
    func_80107330(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801072E0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B5F8[index];
}

void func_80107308(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B600[index];
}

void func_80107330(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_80107478(STAGE_LIPS *lips, sint32 index)
{
    lips->index_4 = 0;
    lips->mouth_8 = D_8011B618[index];
    lips->count_5 = 0;
}

void func_80107498(STAGE_LIPS *lips, sint32 index)
{
    lips->index_6 = 0;
    lips->eyes_C  = D_8011B63C[index];
    lips->count_7 = 0;
}

void func_801074B8(STAGE_OBJ *wp, STAGE_LIPS *lips)
{
    if (lips->count_5 == 0)
    {
        if (lips->mouth_8[lips->index_4] != 0x7E)
        {
            if (lips->mouth_8[lips->index_4] == 0x7F)
            {
                lips->index_4 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(lips->mouth_8[lips->index_4], 0x33, 0x37, 5));
            lips->count_5 = lips->mouth_8[lips->index_4 + 1];
            lips->index_4 += 2;
        }
    }
    else
    {
        lips->count_5--;
    }
    if (lips->count_7 == 0)
    {
        if (lips->eyes_C[lips->index_6] != 0x7E)
        {
            if (lips->eyes_C[lips->index_6] == 0x7F)
            {
                lips->index_6 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(lips->eyes_C[lips->index_6], 0x33, 0x37, 5));
            lips->count_7 = lips->eyes_C[lips->index_6 + 1];
            lips->index_6 += 2;
        }
    }
    else
    {
        lips->count_7--;
    }
}

void func_8010761C(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_LIPS *lips;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    lips                    = &wp->u_4E0.lips;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]          = 0x2000200;
            wp->scale.words[1]          = 0x200;
            wp->scale.v.pad             = 0x4210;
            wp->value_78                = 0;
            wp->value_44.words.fraction = 0;
            wp->value_44.words.integer  = 0;
            wp->value_48.words.fraction = 0;
            wp->u_C.b.byte_C            = 0;
            wp->u_C.b.byte_D            = 0;
            func_80107478(lips, 0);
            func_80107498(lips, 0);
            func_800322A8(wp, 1, 0);
            wp->routine_0++;
            break;
        case 2:
            wp->value_48.words.fraction = 0x20;
            wp->routine_0++;
            // fall through
        case 3:
            Obj_pos_set(wp, (sint16)wp->value_48.words.fraction, 0, 0);
            func_80032488(wp);
            break;
        case 1:
        case 4:
            Model_pose_unpack(wp);
            Model_parts_mtx_set_y(wp);
            break;
    }
    if (scene->u_8.byte[1] == 6)
    {
        if (scene->value_10 == 0x2D)
        {
            func_80107478(lips, 1);
        }
        else if (scene->value_10 == 0x35)
        {
            func_80107478(lips, 0);
        }
        else if (scene->value_10 == 0x41)
        {
            func_80107498(lips, 2);
        }
        else if (scene->value_10 == 0x96)
        {
            func_80107498(lips, 0);
        }
        else if (scene->value_10 == 0xA0)
        {
            func_80107478(lips, 1);
        }
        else if (scene->value_10 == 0xA8)
        {
            func_80107478(lips, 0);
        }
        else if (scene->value_10 == 0xC8)
        {
            func_80107478(lips, 1);
        }
        else if (scene->value_10 == 0xD0)
        {
            func_80107478(lips, 0);
        }
        else if (scene->value_10 == 0xDA)
        {
            func_80107498(lips, 1);
        }
        else if (scene->value_10 == 0xE6)
        {
            func_80107498(lips, 0);
        }
        func_801074B8(wp, lips);
    }
}

void func_8010787C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011B648[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    func_80107AEC(wp, face);
}

void func_801078F0(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->flags_0        = (uint8)wp->flags_0 | 2;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    func_80107AA4(wp, &wp->u_4E0.face16, 6);
    wp->u_C.b.byte_D = 0;
    wp->routine_1++;
}

void func_80107970(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    switch (Scene_work.value_10)
    {
        case 0x1E:
            func_800322A8(wp, 2, 0);
            func_80107AA4(wp, face, 0);
            break;
        case 0x2D:
            func_80107AA4(wp, face, 1);
            break;
        case 0x5F:
            func_80107AA4(wp, face, 2);
            break;
        case 0x64:
            func_80107AA4(wp, face, 3);
            break;
        case 0x78:
            func_800322A8(wp, 3, 0);
            break;
        case 0x8C:
            func_80107AA4(wp, face, 4);
            break;
        case 0xBE:
            func_80107AA4(wp, face, 5);
            break;
    }
}

void func_80107AA4(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_8011B700[index];
    face->eyes_10               = D_8011B71C[index];
}

void func_80107AEC(STAGE_OBJ *wp, STAGE_FACE16 *face)
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
        Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(face->shape_0, 0x33, 0x37, 5));
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
        Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(face->shape_6, 0x33, 0x37, 5));
    }
    face->prev_8 = face->shape_6;
}

void func_80107C38(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]     = 0x02000200;
            wp->scale.words[1]     = 0x200;
            wp->scale.v.pad        = 0x4210;
            wp->anim_AC            = 1;
            wp->value_78           = 0;
            wp->anim_prev_AD       = 0xFF;
            wp->u_4E0.face.value_2 = 0;
            func_80107EA8(wp, face, 0);
            func_80107ED0(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (Scene_work.u_8.byte[1] == 3 && Scene_work.value_10 == 0xA)
            {
                func_80107EA8(wp, face, 2);
                wp->routine_0++;
            }
            break;
        case 2:
            switch (Scene_work.value_10)
            {
                case 0x1E:
                    func_80107ED0(wp, face, 2);
                    break;
                case 0x32:
                    func_80107EA8(wp, face, 2);
                    break;
                case 0x46:
                    func_80107ED0(wp, face, 2);
                    break;
                case 0x8C:
                    func_80107EA8(wp, face, 2);
                    // fall through
                case 0x3C:
                    func_80107ED0(wp, face, 1);
                    break;
            }
            break;
    }
    func_80107EF8(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80107EA8(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B774[index];
}

void func_80107ED0(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B780[index];
}

void func_80107EF8(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_80108040(STAGE_OBJ *wp)
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
            wp->scale.words[0]     = 0x02000200;
            wp->scale.words[1]     = 0x200;
            wp->scale.v.pad        = 0x4210;
            wp->anim_AC            = 1;
            wp->value_78           = 0;
            wp->anim_prev_AD       = 0xFF;
            wp->u_4E0.face.value_2 = 0;
            func_8010832C(wp, face, 1);
            func_80108354(wp, face, 0);
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (Scene_work.u_8.byte[1] == 3)
            {
                if (Scene_work.value_10 == 0x37)
                {
                    func_8010832C(wp, face, 3);
                }
                else if (Scene_work.value_10 == 0x41)
                {
                    func_80108354(wp, face, 2);
                    wp->routine_0++;
                }
            }
            break;
        case 2:
            if (Scene_work.u_8.byte[1] == 3 && Scene_work.value_10 == 0x73)
            {
                func_80108354(wp, face, 0);
            }
            else if (scene->u_8.byte[1] == 4 && scene->value_10 == 1)
            {
                wp->anim_AC = 2;
                func_8010832C(wp, face, 1);
                func_80108354(wp, face, 1);
                wp->routine_0++;
            }
            break;
        case 3:
            switch (Scene_work.value_10)
            {
                case 0xA:
                case 0x28:
                    func_80108354(wp, face, 3);
                    break;
                case 0x1E:
                case 0x4B:
                    func_80108354(wp, face, 1);
                    break;
                case 0x5A:
                    func_8010832C(wp, face, 3);
                    break;
            }
            break;
    }
    func_8010837C(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010832C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011B7F4[index];
}

void func_80108354(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011B804[index];
}

void func_8010837C(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_801084C4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_4 = 0;
    lips->mouth_8 = D_8011B820[index];
    lips->count_5 = 0;
}

void func_801084E4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_6 = 0;
    lips->eyes_C  = D_8011B83C[index];
    lips->count_7 = 0;
}

void func_80108504(STAGE_OBJ *wp, STAGE_LIPS *lips)
{
    if (lips->count_5 == 0)
    {
        if (lips->mouth_8[lips->index_4] != 0x7E)
        {
            if (lips->mouth_8[lips->index_4] == 0x7F)
            {
                lips->index_4 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(lips->mouth_8[lips->index_4], 0x33, 0x37, 5));
            lips->count_5 = lips->mouth_8[lips->index_4 + 1];
            lips->index_4 += 2;
        }
    }
    else
    {
        lips->count_5--;
    }
    if (lips->count_7 == 0)
    {
        if (lips->eyes_C[lips->index_6] != 0x7E)
        {
            if (lips->eyes_C[lips->index_6] == 0x7F)
            {
                lips->index_6 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(lips->eyes_C[lips->index_6], 0x33, 0x37, 5));
            lips->count_7 = lips->eyes_C[lips->index_6 + 1];
            lips->index_6 += 2;
        }
    }
    else
    {
        lips->count_7--;
    }
}

void func_80108668(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_LIPS *lips;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    lips                    = &wp->u_4E0.lips;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_78         = 0;
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_48.half[0] = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            func_801084C4(lips, 0);
            func_801084E4(lips, 0);
            func_800322A8(wp, 3, 0);
            wp->routine_0++;
            break;
        case 1:
        case 3:
            func_80032488(wp);
            break;
        case 2:
            break;
    }
    if (scene->value_10 == 0xA)
    {
        func_801084E4(lips, 1);
    }
    else if (scene->value_10 == 0x55)
    {
        func_801084E4(lips, 0);
        func_801084C4(lips, 1);
    }
    else if (scene->value_10 == 0x69)
    {
        func_801084E4(lips, 1);
    }
    else if (scene->value_10 == 0x96)
    {
        func_801084E4(lips, 0);
    }
    else if (scene->value_10 == 0xA0 || scene->value_10 == 0xAA)
    {
        func_801084C4(lips, 1);
    }
    func_80108504(wp, lips);
}

void func_80108864(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    temp_v1                 = wp->routine_0;
    switch (temp_v1)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]          = 0x02000200;
            wp->scale.words[1]          = 0x200;
            wp->scale.v.pad             = 0x4210;
            wp->value_78                = 0;
            wp->value_44.words.fraction = 0;
            wp->value_44.words.integer  = 0;
            wp->value_48.words.fraction = 0;
            wp->u_C.b.byte_C            = 0;
            wp->u_C.b.byte_D            = 0;
            func_800322A8(wp, 1, 0);
            wp->routine_0++;
            return;
        case 2:
            func_80032488(wp);
        case 1:
            return;
    }
}

void func_80108998(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 = (uint8)wp->flags_0 | 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->value_78       = 0;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
        return;
    }
    func_80032488(wp);
}

void func_80108A28(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    D_8011B844[wp->routine_0](wp, &Scene_work, face);
    func_801091EC(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_4E0.face.value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80108B28(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STAGE_FACE *face)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->anim_AC        = 9;
    wp->value_78       = 0;
    wp->anim_prev_AD   = 0xFF;
    face->timer_0      = 0;
    face->value_2      = 0;
    func_8010919C(wp, face, 6);
    func_801091C4(wp, face, 9);
    wp->routine_1 = 0;
    wp->routine_0++;
}
