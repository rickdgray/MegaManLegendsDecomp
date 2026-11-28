#include "common.h"
#include "st17.h"

void func_80109334(STAGE_OBJ *wp)
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
            wp->anim_AC        = 1;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            face->value_2      = 0;
            func_8010971C(wp, face, 5);
            func_80109744(wp, face, 5);
            wp->routine_0++;
            break;
        case 1:
            if (wp->value_A4 == 0x1D)
            {
                func_8010971C(wp, face, 6);
                wp->anim_prev_AD = 0xFF;
                face->value_2    = 0x1D;
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_prev_AD = 0xFF;
            if (scene->value_10 == 0x32)
            {
                func_80109744(wp, face, 0xA);
            }
            else if (scene->value_10 == 0x5A)
            {
                func_8010971C(wp, face, 0);
                func_80109744(wp, face, 6);
                wp->routine_0++;
            }
            else if (scene->value_10 == 0xA0)
            {
                wp->routine_0++;
            }
            break;
        case 3:
            switch (scene->u_8.byte[1])
            {
                case 1:
                    break;
                case 2:
                    if (scene->value_10 == 1)
                    {
                        wp->anim_AC   = 2;
                        face->value_2 = 0;
                        func_80109744(wp, face, 0);
                        wp->routine_0++;
                    }
                    break;
            }
            break;
        case 4:
            switch (scene->value_10)
            {
                case 0xA:
                    func_8010971C(wp, face, 7);
                    func_80109744(wp, face, 7);
                    break;
                case 0x3C:
                    func_8010971C(wp, face, 8);
                    func_80109744(wp, face, 8);
                    break;
                case 0x82:
                    func_8010971C(wp, face, 2);
                    func_80109744(wp, face, 2);
                    wp->anim_AC   = 3;
                    face->value_2 = 0;
                    wp->routine_0++;
                    break;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 2)
            {
                if (scene->value_10 == 0x96)
                {
                    func_8010971C(wp, face, 8);
                    func_80109744(wp, face, 8);
                }
                else if (scene->value_10 == 0xC8)
                {
                    func_8010971C(wp, face, 2);
                    func_80109744(wp, face, 2);
                }
            }
            else if (scene->u_8.byte[1] == 3)
            {
                if (scene->value_10 == 1)
                {
                    wp->anim_AC   = 4;
                    face->value_2 = 0;
                    wp->routine_0++;
                }
            }
            break;
        case 6:
            if (scene->value_10 == 1)
            {
                func_8010971C(wp, face, 9);
                func_80109744(wp, face, 9);
            }
            else if (scene->value_10 == 0x3C)
            {
                func_8010971C(wp, face, 4);
                func_80109744(wp, face, 4);
            }
            break;
    }
    func_8010976C(wp, face);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, face->value_2);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010971C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_8011BA68[index];
}

void func_80109744(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_8011BA90[index];
}

void func_8010976C(STAGE_OBJ *wp, STAGE_FACE *face)
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

void func_801098B4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_4 = 0;
    lips->mouth_8 = D_8011BACC[index];
    lips->count_5 = 0;
}

void func_801098D4(STAGE_LIPS *lips, sint32 index)
{
    lips->index_6 = 0;
    lips->eyes_C  = D_8011BAEC[index];
    lips->count_7 = 0;
}

void func_801098F4(STAGE_OBJ *wp, STAGE_LIPS *lips)
{
    if (lips->count_5 == 0)
    {
        if (lips->mouth_8[lips->index_4] != 0x7E)
        {
            if (lips->mouth_8[lips->index_4] == 0x7F)
            {
                lips->index_4 = 0;
            }
            Model_mesh_uv_copy(wp->model_88, 0x110010, Model_uv_cell(lips->mouth_8[lips->index_4], 0x2A, 0x40, 6));
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
            Model_mesh_uv_copy(wp->model_88, 0x130012, Model_uv_cell(lips->eyes_C[lips->index_6], 0x2A, 0x40, 6));
            lips->count_7 = lips->eyes_C[lips->index_6 + 1];
            lips->index_6 += 2;
        }
    }
    else
    {
        lips->count_7--;
    }
}

void func_80109A58(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;
    STAGE_LIPS *lips;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    lips                    = &wp->u_4E0.lips;
    if (Scene_work.u_8.byte[1] != 2)
    {
        return;
    }
    if (Scene_work.value_10 == 1)
    {
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
        func_801098B4(lips, 0);
        func_801098D4(lips, 0);
        func_800322A8(wp, 5, 0);
    }
    else if ((Scene_work.value_10 >= 0x16 && Scene_work.value_10 < 0x3E) || Scene_work.value_10 >= 0x1AF)
    {
        func_80032488(wp);
    }
    switch (scene->value_10)
    {
        case 0x14:
        case 0x69:
        case 0x12C:
        case 0x1AE:
        case 0xB4:
            func_801098D4(lips, 1);
            break;
        case 0x10E:
        case 0x4B:
        case 0x1F4:
            func_801098B4(lips, 1);
            // fall through
        case 0xA5:
        case 0x17C:
            func_801098D4(lips, 0);
            break;
        case 0x19A:
            func_801098B4(lips, 1);
            break;
    }
    func_801098F4(wp, lips);
}

void func_80109CA4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    D_8011BAF4[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    func_8010A3A8(wp, face);
}

void func_80109D18(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    face = &wp->u_4E0.face16;
    switch (Scene_work.u_8.byte[0])
    {
        case 2:
            func_800322A8(wp, 1, 0);
            wp->routine_1 = 1;
            break;
        case 4:
            wp->position.z = 0xFA;
            func_800322A8(wp, 3, 0);
            wp->routine_1 = 3;
            break;
        case 8:
            wp->position.z = 0xF0;
            func_800322A8(wp, 4, 0);
            wp->routine_1 = 4;
            break;
        case 0xB:
            func_800322A8(wp, 7, 0);
            wp->routine_1 = 5;
            wp->u_C.b.byte_D++;
            break;
    }
    func_8010A364(wp, face, 0);
    wp->routine_2 = 0;
    wp->u_C.b.byte_D++;
}

void func_80109E5C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
        func_8010A364(wp, face, 0);
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x14:
            wp->u_C.b.byte_D++;
            break;
        case 0x23:
            func_8010A364(wp, face, 1);
            break;
        case 0x122:
            func_8010A364(wp, face, 2);
            break;
    }
}

void func_80109F28(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        func_8010A364(wp, face, 3);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x19:
            func_8010A364(wp, face, 4);
            break;
        case 0x55:
            func_8010A364(wp, face, 5);
            break;
    }
}

void func_80109FD4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    if (wp->routine_2 == 0)
    {
        func_8010A364(wp, face, 6);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 0x37)
    {
        func_8010A364(wp, face, 7);
    }
}

void func_8010A04C(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    switch (Scene_work.value_10)
    {
        case 0x2D:
        case 1:
            func_8010A364(wp, face, 8);
            break;
        case 5:
            func_8010A364(wp, face, 9);
            wp->u_C.b.byte_D = 0;
            break;
        case 0x50:
            func_800322A8(wp, 5, 0);
            wp->u_C.b.byte_D = 0;
            break;
        case 0x78:
            func_800322A8(wp, 6, 0);
            func_8010A364(wp, face, 8);
            wp->u_C.b.byte_D = 0;
            break;
        case 0xB4:
            func_8010A364(wp, face, 9);
            wp->u_C.b.byte_D++;
            break;
    }
}

void func_8010A168(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_8010A364(wp, &wp->u_4E0.face16, 10);
        wp->routine_2++;
    }
}

void func_8010A1B4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = &wp->u_4E0.face16;
    switch (Scene_work.value_10)
    {
        case 0x32:
        case 0xA5:
        case 0x1E0:
            func_8010A364(wp, face, 0xC);
            break;
        case 0x5A:
            func_8010A364(wp, face, 0xD);
            break;
        case 0xB9:
            func_800322A8(wp, 7, 0);
            wp->u_C.b.byte_D = 0;
            break;
        case 0xC8:
            func_8010A364(wp, face, 0xE);
            break;
        case 0x104:
            func_8010A364(wp, face, 0xE);
            break;
        case 0xEB:
        case 0x136:
            func_8010A364(wp, face, 0xF);
            break;
        case 0x140:
            func_800322A8(wp, 8, 0);
            func_8010A364(wp, face, 0xA);
            wp->u_C.b.byte_D = 0;
            break;
        case 0x168:
            func_8010A364(wp, face, 0xD);
            break;
        case 1:
        case 0x1AE:
            func_8010A364(wp, face, 0xB);
            break;
    }
}

void func_8010A364(STAGE_OBJ *wp, STAGE_FACE16 *face, sint32 index)
{
    face->prev_2 = face->prev_8 = -1;
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->mouth_C                 = D_8011BC88[index];
    face->eyes_10                 = D_8011BC88[index];
}

void func_8010A3A8(STAGE_OBJ *wp, STAGE_FACE16 *face)
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

void func_8010A4F4(STAGE_OBJ *wp)
{
    D_8011BCD4[wp->routine_0](wp);
}

void func_8010A530(STAGE_OBJ *wp)
{
    ST17_HW *hw;
    sint16 life;
    uint32 i;

    wp->scale.v.x        = 0x200;
    wp->scale.v.y        = 0x200;
    wp->scale.v.z        = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->rotation.x       = 0;
    wp->rotation.y       = 0x400;
    wp->rotation.z       = 0;
    wp->value_48.half[0] = 0;
    wp->value_44.half[1] = 0;
    wp->value_44.half[0] = 0;
    wp->value_50         = 0;
    wp->value_4C.half[1] = 0;
    wp->value_4C.half[0] = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    hw = ST17_HW_OF(wp);
    func_8005D4D4();
    wp->u_C.b.byte_C       = 0;
    wp->value_78           = 0;
    life                   = D_8009884C[wp->kind_2]->life_8 * 16;
    wp->life_prev_B2       = 0;
    ST17_VALUE_74(wp)      = 1;
    hw->vec_8.x            = 0;
    hw->vec_8.y            = 0;
    hw->vec_8.z            = 0;
    wp->life_max_B0        = life;
    wp->life_6E            = life;
    hw->vec_10             = hw->vec_8;
    hw->value_0            = wp->rotation.y + 0x400;
    wp->position.x         = hw->vec_8.x;
    wp->position.z         = hw->vec_8.z - 0xE00;
    wp->position.y         = hw->vec_8.y - 0x800;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    for (i = 0; i < 8; i++)
    {
        D_80122AC8[i].value_0 = 0;
        D_80122AC8[i].value_4 = 0;
    }
    hw->timer_2 = 0x80;
    hw->value_4 = 0x3C;
    hw->value_6 = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_8010A6D0(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    func_8010A7E4(wp);
    D_8011BCE0[wp->routine_1](wp);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->routine_0 != 2 && wp->routine_1 != 3)
    {
        func_8010A884(wp);
    }
}

void func_8010A7E4(STAGE_OBJ *wp)
{
    sint32 i;
    sint32 damage;

    if (wp->routine_1 == 3)
    {
        return;
    }
    for (i = 0; i < 8; i++)
    {
        damage = D_80122AC8[i].value_0 & 0xFFFFFF;
        if (damage != 0)
        {
            goto hit;
        }
    }
    return;
hit:
    wp->life_6E -= damage;
    Sound_call(0xA0, 0, 0);
    wp->scale.v.pad = 0x7FFF;
    if (wp->life_6E <= 0)
    {
        func_8010B68C(wp);
    }
}

void func_8010A884(STAGE_OBJ *wp)
{
    uint32 i;

    for (i = 0; i < 8; i++)
    {
        D_80122AC8[i].value_0 = 0;
        D_80122A88[i]         = ST17_JOINT(wp)[D_8011BCF0[i]];
        if (i == 0)
        {
            func_800341BC(&D_80122A88[0], D_8011BCF8[0], 0, 0x8000, wp->value_1, &D_80122AC8[0], 0x4080000, 0, 0);
        }
        else
        {
            func_800341BC(&D_80122A88[i], D_8011BCF8[i], 0, 0x8000, wp->value_1, &D_80122AC8[i], 0x4080000, 0, 0x80);
        }
    }
}

void func_8010A9CC(STAGE_OBJ *wp)
{
    STAGE_FACE *face;
    sint16 rot;
    sint16 angle;

    face                   = &wp->u_4E0.face;
    rot                    = (wp->rotation.y - 0xC) & 0xFFF;
    angle                  = (rot - 0x400) & 0xFFF;
    wp->rotation.y         = rot;
    wp->u_4E0.face.timer_0 = angle;
    wp->position.x         = (uint32)(rsin(angle) * 7) >> 3;
    wp->position.y         = wp->u_4E0.face16.index_A - 0x800;
    wp->position.z         = (uint32)(rcos(wp->u_4E0.face.timer_0) * 7) >> 3;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (wp->u_4E0.face16.index_4 == 0)
    {
        if (wp->u_4E0.face16.shape_6 == 2)
        {
            wp->u_4E0.face16.index_4 = 0xC8;
            wp->u_4E0.face16.shape_6 = 0;
        }
        else
        {
            wp->u_4E0.face16.index_4 = 0xF;
            wp->u_4E0.face16.shape_6++;
        }
        func_8010BE04(wp);
        Sound_call(0x1A3, 0, 0);
    }
    else
    {
        wp->u_4E0.face16.index_4--;
    }
    if (face->value_2 == 0)
    {
        if (!(rand() & 0x3F))
        {
            if (rand() & 1)
            {
                func_8010B5DC(wp);
            }
            else
            {
                func_8010B58C(wp);
            }
        }
    }
    else
    {
        face->value_2--;
    }
}

void func_8010AB3C(STAGE_OBJ *wp)
{
    D_8011BD08[wp->routine_2](wp);
}

void func_8010AB78(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR fixed;

    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (ST17_HW_OF(wp)->timer_2 == 0)
    {
        wp->anim_AC              = 1;
        ST17_HW_OF(wp)->vec_1A   = wp->position;
        ST17_HW_OF(wp)->angle_22 = (wp->rotation.y - 0x400) & 0xFFF;
        fixed.x                  = ST17_HW_OF(wp)->vec_1A.x << 16;
        fixed.y                  = ST17_HW_OF(wp)->vec_1A.y << 16;
        fixed.z                  = ST17_HW_OF(wp)->vec_1A.z << 16;
        func_8002FFC4(&ST17_HW_OF(wp)->vec_1A, &fixed, ST17_HW_OF(wp)->angle_22, 0x7000, 0, 0);
        ST17_HW_OF(wp)->timer_2  = 0x40;
        ST17_HW_OF(wp)->value_4  = 0;
        ST17_HW_OF(wp)->angle_22 = (ST17_HW_OF(wp)->angle_22 + 0x800) & 0xFFF;
        wp->routine_2++;
    }
    else
    {
        ST17_HW_OF(wp)->timer_2--;
    }
}

void func_8010AC6C(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR fixed;
    ST17_HW *hw;

    hw = ST17_HW_OF(wp);
    if (wp->anim_AC == 1 && wp->value_A7 != 0)
    {
        wp->anim_AC = 3;
    }
    if (hw->timer_2 == 0x14)
    {
        wp->anim_AC = 2;
    }
    if (wp->anim_AC == 2 && wp->value_A7 != 0)
    {
        wp->anim_AC = 0;
    }
    if (hw->timer_2 == 0)
    {
        wp->anim_AC = 0;
        Sound_call(0x1A4, 0, 0);
        hw->timer_2 = 0x58;
        hw->value_4 = 0;
        wp->routine_2++;
        return;
    }
    pos     = hw->vec_1A;
    fixed.x = pos.x << 16;
    fixed.y = pos.y << 16;
    fixed.z = pos.z << 16;
    func_8002FFC4(&pos, &fixed, hw->angle_22, 0x7000, 0, 0);
    hw->angle_22         = (hw->angle_22 - 0x20) & 0xFFF;
    wp->position         = pos;
    wp->position_fixed.v = fixed;
    wp->rotation.y       = (wp->rotation.y - 0x20) & 0xFFF;
    hw->timer_2--;
}

void func_8010AE0C(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR fixed;

    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (ST17_HW_OF(wp)->timer_2 == 0)
    {
        wp->anim_AC              = 1;
        ST17_HW_OF(wp)->vec_1A   = wp->position;
        ST17_HW_OF(wp)->angle_22 = (wp->rotation.y - 0x400) & 0xFFF;
        fixed.x                  = ST17_HW_OF(wp)->vec_1A.x << 16;
        fixed.y                  = ST17_HW_OF(wp)->vec_1A.y << 16;
        fixed.z                  = ST17_HW_OF(wp)->vec_1A.z << 16;
        func_8002FFC4(&ST17_HW_OF(wp)->vec_1A, &fixed, ST17_HW_OF(wp)->angle_22, 0x7000, 0, 0);
        ST17_HW_OF(wp)->timer_2  = 0x40;
        ST17_HW_OF(wp)->angle_22 = (ST17_HW_OF(wp)->angle_22 + 0x800) & 0xFFF;
        wp->routine_2++;
    }
    else
    {
        func_8010B968(wp);
        ST17_HW_OF(wp)->timer_2--;
    }
}

void func_8010AF08(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR fixed;
    ST17_HW *hw;

    hw = ST17_HW_OF(wp);
    if (wp->anim_AC == 1 && wp->value_A7 != 0)
    {
        wp->anim_AC = 3;
    }
    if (hw->timer_2 == 0x14)
    {
        wp->anim_AC = 2;
    }
    if (wp->anim_AC == 2 && wp->value_A7 != 0)
    {
        wp->anim_AC = 0;
    }
    if (hw->timer_2 == 0)
    {
        wp->anim_AC = 0;
        hw->timer_2 = 0x18;
        wp->routine_2++;
        return;
    }
    pos     = hw->vec_1A;
    fixed.x = pos.x << 16;
    fixed.y = pos.y << 16;
    fixed.z = pos.z << 16;
    func_8002FFC4(&pos, &fixed, hw->angle_22, 0x7000, 0, 0);
    hw->angle_22         = (hw->angle_22 - 0x20) & 0xFFF;
    wp->position         = pos;
    wp->position_fixed.v = fixed;
    wp->rotation.y       = (wp->rotation.y - 0x20) & 0xFFF;
    hw->timer_2--;
}

void func_8010B094(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    temp_v0 = wp->u_4E0.hw.timer_2;
    if (temp_v0 == 0)
    {
        func_8010B520(wp);
        return;
    }
    wp->u_4E0.hw.timer_2 = temp_v0 - 1;
}

void func_8010B0F4(STAGE_OBJ *wp)
{
    D_8011BD1C[wp->routine_2](wp);
}

void func_8010B130(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (wp->value_A7 != 0)
    {
        wp->anim_AC          = 4;
        wp->u_4E0.hw.timer_2 = 0x22;
        wp->routine_2++;
    }
}

void func_8010B190(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.timer_2 == 0)
    {
        wp->anim_AC = 7;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (wp->u_4E0.hw.timer_2 >= 3)
    {
        wp->rotation.y = ((uint16)wp->rotation.y - 0x20) & 0xFFF;
    }
    wp->u_4E0.hw.timer_2 = (uint16)wp->u_4E0.hw.timer_2 - 1;
}

void func_8010B224(STAGE_OBJ *wp)
{
    if (wp->value_A7 != 0)
    {
        wp->value_44.words.fraction = 0x400;
        wp->value_44.words.integer  = 0x900;
        wp->value_48.words.fraction = 0;
        wp->u_4E0.hw.timer_2        = 0x20;
        Sound_call(0x1A7, 0, 0);
        wp->routine_2++;
    }
}

void func_8010B290(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.timer_2 == 0)
    {
        wp->u_4E0.hw.timer_2 = 0x5A;
        wp->u_4E0.hw.value_4 = 0;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    wp->u_4E0.hw.timer_2 = (uint16)wp->u_4E0.hw.timer_2 - 1;
}

void func_8010B300(STAGE_OBJ *wp)
{
    sint16 count;
    sint16 y;

    count = wp->u_4E0.hw.timer_2;
    if (count == 0)
    {
        wp->value_44.words.fraction = 0x500;
        wp->value_44.words.integer  = 0x180;
        wp->u_4E0.hw.timer_2        = 0x40;
        Sound_call(0x1A8, 0, 0);
        wp->routine_2++;
        return;
    }
    y                      = wp->position.y + D_8011BD38[count & 0xF];
    wp->position.y         = y;
    wp->position_fixed.v.y = y << 16;
    func_8010BC00(wp);
    wp->u_4E0.hw.timer_2--;
}

void func_8010B3B4(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.timer_2 == 0)
    {
        wp->anim_AC = 8;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    wp->u_4E0.hw.timer_2 = (uint16)wp->u_4E0.hw.timer_2 - 1;
}

void func_8010B420(STAGE_OBJ *wp)
{
    wp->rotation.y = (wp->rotation.y - 0x20) & 0xFFF;
    if (wp->value_A7 != 0)
    {
        func_8010B520(wp);
    }
}

void func_8010B458(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    func_8010B7A4(wp);
    face = &wp->u_4E0.face;
    if (wp->routine_2 == 0 && Sound_fade_flags == 0)
    {
        Sound_fade_start(0x10);
        func_8005D4E8();
        wp->routine_2++;
    }
    if (face->value_2 == 0)
    {
        if (wp->routine_2 != 0 && Sound_fade_flags == 0)
        {
            wp->u_C.b.byte_C = 1;
            wp->routine_0    = 2;
            wp->routine_1    = 0;
            wp->routine_2    = 0;
        }
    }
    else
    {
        face->value_2--;
    }
}

void func_8010B520(STAGE_OBJ *wp)
{
    wp->position           = wp->u_4E0.hw.vec_10;
    wp->rotation.y         = wp->u_4E0.hw.value_18;
    wp->u_4E0.hw.timer_2   = 0x80;
    wp->u_4E0.hw.value_4   = 0x1E;
    wp->u_4E0.hw.value_6   = 0;
    wp->routine_1          = 0;
    wp->routine_2          = 0;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010B58C(STAGE_OBJ *wp)
{
    wp->u_4E0.hw.vec_10         = wp->position;
    wp->u_4E0.hw.timer_2        = 0x40;
    wp->value_44.words.fraction = 0x600;
    wp->value_44.words.integer  = 0;
    wp->value_48.words.fraction = 0;
    wp->routine_1               = 1;
    wp->routine_2               = 0;
    wp->u_4E0.hw.value_18       = wp->rotation.y;
}

void func_8010B5DC(STAGE_OBJ *wp)
{
    sint16 angle;

    angle                 = (wp->rotation.y + 0x800) & 0xFFF;
    wp->u_4E0.hw.value_18 = angle;
    wp->u_4E0.hw.value_0  = (angle - 0x400) & 0xFFF;
    wp->u_4E0.hw.vec_10.x = (uint32)(rsin(wp->u_4E0.hw.value_0) * 7) >> 3;
    wp->u_4E0.hw.vec_10.y = wp->u_4E0.hw.vec_8.y - 0x800;
    wp->u_4E0.hw.vec_10.z = (uint32)(rcos(wp->u_4E0.hw.value_0) * 7) >> 3;
    wp->anim_AC           = 5;
    Sound_call(0x1A6, 0, 0);
    wp->value_44.words.integer  = -0x600;
    wp->value_44.words.fraction = 0;
    wp->value_48.words.fraction = 0;
    wp->routine_1               = 2;
    wp->routine_2               = 0;
}

void func_8010B68C(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    ST17_HW *ext;
    uint32 i;

    func_800322A8(wp, 9, 0);
    ext                         = (ST17_HW *)&wp->u_4E0;
    wp->u_4E0.hw.timer_2        = 0x96;
    wp->value_44.words.fraction = 0x280;
    wp->u_4E0.hw.value_4        = 0;
    wp->value_44.words.integer  = 1;
    Sound_key_off_voice(0x11);
    Sound_key_off_voice(0x13);
    for (i = 0; i < 4; i++)
    {
        pos = ST17_JOINT(wp)[D_8011BCC8[i].joint];
        pos.y -= D_8011BCC8[i].drop;
        ext->sparks_24[i] = ((ST17_SPARK5_FUNC)func_80105530)(&pos, 0x80, 1, 0x10, -8);
    }
    wp->routine_1 = 3;
    wp->routine_2 = 0;
}

void func_8010B7A4(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos;
    ST17_HW *ext;
    STCOM_EFFECT *fx;
    uint8 joint;
    uint32 i;

    ext = (ST17_HW *)&wp->u_4E0;
    Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer, (sint16)wp->value_48.words.fraction);
    if (wp->u_4E0.hw.value_4 == 0)
    {
        wp->u_4E0.hw.value_4 = D_8011BD48[rand() & 7];
        for (i = 0; i < 3; i++)
        {
            joint = D_8011BD50[rand() & 0xF];
            fx    = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 5;
                fx->kind_2          = 0x80;
                fx->variant_3       = 2;
                fx->sprite.position = ST17_JOINT(wp)[joint];
                fx->value_D         = 2;
            }
        }
    }
    else
    {
        wp->u_4E0.hw.value_4--;
    }
    for (i = 0; i < 4; i++)
    {
        pos = ST17_JOINT(wp)[D_8011BCC8[i].joint];
        pos.y -= D_8011BCC8[i].drop;
        ext->sparks_24[i]->x_1C = pos.x;
        ext->sparks_24[i]->y_1E = pos.y;
        ext->sparks_24[i]->z_20 = pos.z;
    }
}

void func_8010B968(STAGE_OBJ *wp)
{
    sint32 level;

    if (ST17_DIST(wp) <= 0xF42400)
    {
        if (wp->u_4E0.hw.value_4 == 0)
        {
            wp->u_4E0.hw.value_4 = 2;
            level                = ST17_DIST(wp) <= 0x53EC60;
            if (ST17_DIST(wp) <= 0x557300)
            {
                level = 2;
            }
            if (ST17_DIST(wp) <= 0x225510)
            {
                level = 3;
            }
            func_8010BA40(wp, 0, level);
            func_8010BA40(wp, 1, level);
            Sound_call(0x1A5, 0, 0);
        }
        else
        {
            wp->u_4E0.hw.value_4--;
        }
    }
}

void func_8010BA40(STAGE_OBJ *wp, sint32 side, sint32 level)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR v;
    ST17_SHOT *shot;

    if (side == 0)
    {
        func_80030058(&fixed, (wp->rotation.y - D_8011BD64[level]) & 0xFFF, 0x400, 0, 0);
    }
    else
    {
        func_80030058(&fixed, (wp->rotation.y + D_8011BD64[level]) & 0xFFF, 0x400, 0, 0);
    }
    func_80030150(&fixed, &v);
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0            = 3;
        shot->kind_2             = 1;
        shot->value_4            = 0;
        shot->value_F            = 4;
        shot->position.x         = ST17_JOINT(wp)[D_8011BD60[side]].x;
        shot->position.y         = ST17_JOINT(wp)[D_8011BD60[side]].y - 8;
        shot->position.z         = ST17_JOINT(wp)[D_8011BD60[side]].z;
        shot->position_fixed.v.x = shot->position.x << 16;
        shot->position_fixed.v.y = shot->position.y << 16;
        shot->position_fixed.v.z = shot->position.z << 16;
        func_8002FFC4(&shot->position, &shot->position_fixed.v, wp->rotation.y, D_8011BD6C[side].x, 0, D_8011BD6C[side].z);
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = 0x3000;
        shot->value_48.half[0] = v.z << 8;
        shot->value_4C.half[0] = 0;
        shot->value_4C.half[1] = 0;
        shot->value_50         = 0;
    }
}

void func_8010BC00(STAGE_OBJ *wp)
{
    if (wp->u_4E0.hw.value_4 == 0)
    {
        wp->u_4E0.hw.value_4 = 2;
        func_8010BC84(wp, wp->u_4E0.hw.value_6);
        func_8010BC84(wp, wp->u_4E0.hw.value_6 + 4);
        wp->u_4E0.hw.value_6 = (wp->u_4E0.hw.value_6 + 1) & 3;
        Sound_call(0x1A9, 0, 0);
    }
    else
    {
        wp->u_4E0.hw.value_4--;
    }
}

void func_8010BC84(STAGE_OBJ *wp, sint32 index)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR v;
    ST17_SHOT *shot;

    func_80030058(&fixed, (wp->rotation.y + D_8011BD9C[rand() & 7]) & 0xFFF, 0x400, 0, 0);
    func_80030150(&fixed, &v);
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0            = 3;
        shot->kind_2             = 1;
        shot->value_4            = 0;
        shot->value_F            = 4;
        shot->position.x         = ST17_JOINT(wp)[5].x;
        shot->position.y         = ST17_JOINT(wp)[5].y - D_8011BD94[index & 3];
        shot->position.z         = ST17_JOINT(wp)[5].z;
        shot->position_fixed.v.x = shot->position.x << 16;
        shot->position_fixed.v.y = shot->position.y << 16;
        shot->position_fixed.v.z = shot->position.z << 16;
        func_8002FFC4(&shot->position, &shot->position_fixed.v, wp->rotation.y, D_8011BD74[index].x, 0, D_8011BD74[index].z);
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = D_8011BDAC[rand() & 7];
        shot->value_48.half[0] = v.z << 8;
        shot->value_4C.half[0] = 0;
        shot->value_4C.half[1] = 0;
        shot->value_50         = 0;
    }
}

void func_8010BE04(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    ST17_SHOT *shot;

    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0            = 1;
        shot->variant_3          = 6;
        shot->kind_2             = 0;
        shot->target_B8          = &STAGE_PL_BYTE(0x3A8);
        shot->position.x         = ST17_JOINT(wp)[10].x;
        shot->position.y         = ST17_JOINT(wp)[10].y - 0x100;
        shot->position.z         = ST17_JOINT(wp)[10].z;
        shot->position_fixed.v.x = shot->position.x << 16;
        shot->position_fixed.v.y = shot->position.y << 16;
        shot->position_fixed.v.z = shot->position.z << 16;
        rot.z                    = 0;
        rot.x                    = -(rand() & 0x3FF);
        rot.y                    = rand() & 0xFFF;
        RotMatrixYXZ(&rot, &shot->matrix_8C.m);
        scale.x = scale.y = scale.z = 0x200;
        ScaleMatrix(&shot->matrix_8C.m, &scale);
    }
}

void func_8010BEF0(STAGE_OBJ *wp)
{
    func_8010B7A4(wp);
    func_80032488(wp);
}

void func_8010BF20(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_8011BDBC[wp->routine_0](wp, &Scene_work, (ST17_RIG *)&wp->ext_3C0[0x80]);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, wp->u_C.b.byte_D);
    }
    else
    {
        func_80032488(wp);
    }
    func_8010C30C(wp, (ST17_RIG *)&wp->ext_3C0[0x80]);
}

void func_8010C014(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->anim_prev_AD     = 0xFF;
    wp->value_78         = 0;
    wp->anim_AC          = 0;
    wp->value_44.half[0] = 0x300;
    wp->value_44.half[1] = 0;
    wp->value_48.half[0] = 0;
    wp->u_C.b.byte_C     = 0;
    wp->u_C.b.byte_D     = 0;
    rig->slot_0          = func_80105A0C(wp, 2, rig->rot_4);
    wp->routine_1        = 0;
    wp->routine_0++;
}

void func_8010C0C0(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 0 && scene->value_10 >= 0x3C)
            {
                Obj_pos_set(wp, 0x100, 0, 0);
            }
            else if (scene->u_8.byte[1] == 1 && scene->value_10 == 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            func_8003187C(rig->slot_0);
            wp->routine_1++;
            break;
        case 2:
            if (scene->u_8.byte[1] == 5)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_8010C1C4(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, ST17_RIG *rig)
{
    switch (wp->routine_1)
    {
        case 0:
            if (wp->u_C.b.byte_C < 0x20)
            {
                wp->u_C.b.byte_C++;
            }
            else
            {
                wp->u_C.b.byte_C = 0;
                wp->routine_1++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            break;
        case 1:
            if (wp->u_C.b.byte_C > 0x10)
            {
                wp->anim_AC = 5;
            }
            if (wp->u_C.b.byte_C < 0x40)
            {
                wp->value_44.half[0] -= 0xC;
                wp->value_44.half[1] -= 0xC;
                wp->u_C.b.byte_C++;
            }
            else
            {
                wp->routine_1++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            break;
        case 2:
            wp->anim_AC      = 4;
            wp->u_C.b.byte_C = 0;
            wp->u_C.b.byte_D = 0;
            wp->routine_1++;
            break;
        case 3:
            if (scene->value_10 < 0x97)
            {
                wp->value_44.half[1] = 0;
            }
            else
            {
                wp->value_44.half[1] = -0x400;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            break;
    }
}

// form gives index first.
void func_8010C30C(STAGE_OBJ *wp, ST17_RIG *rig)
{
    sint8 i;

    for (i = 0; i < 9; i++)
    {
        rig->rot_4[i] = ST17_JOINT(wp)[i + 1];
    }
}
