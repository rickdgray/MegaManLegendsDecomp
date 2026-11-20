#include "common.h"
#include "st16.h"

void func_80100F68(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (--wp->u_E.angle < -0x31F)
            {
                wp->routine_2++;
            }
            break;
        case 1:
            if (++wp->u_E.angle >= -0x30C)
            {
                wp->routine_2--;
            }
            break;
        case 2:
            wp->u_E.angle = -0x44C;
            wp->routine_2++;
            break;
        case 3:
            wp->u_E.angle -= 6;
            if (wp->u_E.angle < -0x12BF)
            {
                func_80017C30(0xB);
                wp->routine_2++;
            }
            break;
        case 4:
            wp->u_E.angle -= 6;
            if (wp->u_E.angle < -0x176F)
            {
                wp->routine_2 = 7;
            }
            break;
        case 5:
            wp->u_E.angle  = -0x4E2;
            wp->position.x = 0x3E8;
            wp->position.z = 0xAF0;
            wp->routine_2++;
            break;
        case 6:
            wp->position.z -= 8;
            if (wp->position.z < -0x12B)
            {
                wp->routine_2++;
            }
            break;
        case 7:
            break;
    }
}

void func_801010CC(void)
{
}

void func_801010D4(STAGE_WORK *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x2000200;
            wp->scale.words[1] = 0x200;
            wp->value_78       = 0;
            wp->value_10       = 0;
            wp->scale.v.pad    = 0x4210;
            wp->routine_0++;
            break;
        case 1:
            break;
        case 2:
            wp->position.y = wp->u_E.angle;
            D_80103B04[wp->routine_1](wp);
            break;
    }
    func_800322A8(wp, 0, 0);
}

void func_801011B4(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80033A28(wp);
    func_8003346C(wp);
}

void func_80101210(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80032488(wp);
}

void func_80101264(STAGE_OBJ *wp)
{
    D_80103BAC[wp->routine_1](wp);
}

void func_801012A0(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        face->value_2      = 0;
        face->timer_0      = 0;
        func_801014A4(wp, face, 0);
        func_801014CC(wp, face, 0);
        wp->routine_0++;
    }
    func_80101264(wp);
    if (STAGE_SCENE_BYTE(8) == 1)
    {
        switch (STAGE_SCENE_BYTE(9))
        {
            case 0:
                if (face->timer_0 == 0xA)
                {
                    if (STAGE_SCENE_BYTE(0xA) == 0)
                    {
                        func_801014CC(wp, face, 1);
                        func_801014A4(wp, face, 1);
                    }
                    else
                    {
                        func_801014CC(wp, face, 3);
                        func_801014A4(wp, face, 1);
                    }
                }
                break;
            case 1:
                switch (face->timer_0)
                {
                    case 0x32:
                        func_801014CC(wp, face, 0);
                        break;
                    case 0x3C:
                        func_801014A4(wp, face, 1);
                        break;
                }
                break;
        }
        func_801014F4(wp, face);
        face->timer_0++;
    }
}

void func_801014A4(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80103B8C[index];
}

void func_801014CC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80103B9C[index];
}

void func_801014F4(STAGE_OBJ *wp, STAGE_FACE *face)
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
        func_8002D320(wp->model_88, 0x110010, func_8002D404(face->shape_C, 0x33, 0x37, 5));
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
        func_8002D320(wp->model_88, 0x130012, func_8002D404(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_8010163C(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->rotation.z     = 0;
    wp->rotation.x     = 0;
    wp->rotation.y     = 0;
    wp->value_78       = 0;
    wp->flags_0 |= 3;
    wp->routine_0++;
    func_801016B0(wp);
    wp->rotation.z = 0xB4;
}

void func_801016B0(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        if (STAGE_SCENE_BYTE(8) == 1)
        {
            if (STAGE_SCENE_BYTE(9) == STAGE_SCENE_BYTE(8) && STAGE_SCENE_WORD(0x10) == 8)
            {
                wp->u_C.b.byte_C = 1;
                Model_work_init(wp, &wp->u_C.b.byte_C);
                func_800322A8(wp, 1, 0);
                wp->rotation.z = 0;
                wp->routine_1++;
            }
        }
        else
        {
            wp->u_C.b.byte_C = 0;
            Model_work_init(wp, &wp->u_C.b.byte_C);
            func_800322A8(wp, 0, 0);
        }
    }
}

void func_80101770(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_80101790(STAGE_WORK *wp)
{
    D_80103BB8[wp->routine_0](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032538(wp);
    func_800334C4(wp);
}

void func_801017F4(void)
{
}

void func_801017FC(void)
{
}

void func_80101804(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->rotation.y += 4;
            if (wp->rotation.y >= 0xC42)
            {
                wp->routine_2++;
            }
            break;
        case 1:
            wp->rotation.x--;
            wp->rotation.y += 4;
            if (wp->rotation.x < -0x1D)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            wp->u_C.timer = 0x46;
            wp->routine_2++;
            break;
        case 3:
            if (--wp->u_C.timer == 0)
            {
                wp->u_C.timer = 0x40;
                D_8010E054    = func_80102CF4(wp, 0x14A, 0xA, 0x244, 0);
                D_8010E058    = func_80102CF4(wp, -0x14A, 0xA, 0x244, 0);
                wp->routine_2++;
            }
            break;
        case 4:
            if (--wp->u_C.timer == 0)
            {
                D_8010E054->routine_0 = 2;
                D_8010E058->routine_0 = 2;
                D_8010E054            = func_80102CF4(wp, 0x14A, 0xA, 0x244, 1);
                D_8010E058            = func_80102CF4(wp, -0x14A, 0xA, 0x244, 1);
                wp->u_C.timer         = 0x20;
                wp->routine_2++;
            }
            break;
        case 5:
            if (--wp->u_C.timer == 0)
            {
                wp->u_C.timer         = 0x28;
                D_8010E054->routine_0 = 2;
                D_8010E058->routine_0 = 2;
                D_8010E054            = func_80102CF4(wp, 0x14A, 0xA, 0x244, 2);
                D_8010E058            = func_80102CF4(wp, -0x14A, 0xA, 0x244, 2);
                wp->routine_2++;
                if (STAGE_GAME_VALUE_52 != 7 || Sce_flag_test(0x21) == 0)
                {
                    func_80017C30(0xB);
                }
            }
            break;
        case 6:
            wp->position.y -= 2;
            wp->position.x += 0x18;
            wp->rotation.z -= 0x10;
            Obj_pos_set(wp, 0x900, -0xFA, 0);
            if (--wp->u_C.timer == 0)
            {
                D_8010E054->routine_0 = 2;
                D_8010E058->routine_0 = 2;
                wp->position.x        = -0x12AC;
                wp->position.y        = -0x76C;
                wp->position.z        = 0x118;
                wp->routine_2++;
            }
            break;
        case 7:
            break;
    }
}

void func_80101B20(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->position.x  = -0x12AC;
            wp->position.y  = -0x76C;
            wp->rotation_54 = 0;
            wp->rot_y_56    = 0;
            wp->position.z  = 0x118;
            wp->routine_2++;
            break;
        case 1:
            wp->position.y += 3;
            break;
    }
}

void func_80101B88(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->rotation.z     = 0;
        wp->rotation.x     = 0;
        wp->rotation.y     = 0;
        wp->value_78       = 0;
        wp->value_10       = 0;
        wp->scale.v.pad    = 0x4210;
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        func_800322A8(wp, 0, 0);
        wp->rotation.y = 0x800;
        wp->routine_0++;
    }
    D_80103BC4[wp->routine_1](wp);
    func_80032488(wp);
}

void func_80101C4C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    if (STAGE_SCENE_BYTE(8) == 1)
    {
        if (STAGE_SCENE_BYTE(9) == STAGE_SCENE_BYTE(8))
        {
            func_80032488(wp);
        }
        else
        {
            func_80033A28(wp);
            func_8003346C(wp);
        }
    }
}

void func_80101CE0(void)
{
}

void func_80101CE8(STAGE_OBJ *wp)
{
    D_80103C5C[wp->routine_1](wp);
}

void func_80101D24(STAGE_OBJ *wp)
{
    STAGE_FACE *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    face                    = &wp->u_4E0.face;
    if (wp->routine_0 == 0)
    {
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        face->value_2      = 0;
        face->timer_0      = 0;
        func_80101F34(wp, face, 0);
        func_80101F5C(wp, face, 0);
        wp->routine_0++;
    }
    func_80101CE8(wp);
    if (STAGE_SCENE_BYTE(8) == 1)
    {
        switch (STAGE_SCENE_BYTE(9))
        {
            case 0:
                switch (face->timer_0)
                {
                    case 0x28:
                        func_80101F5C(wp, face, 1);
                        func_80101F34(wp, face, 1);
                        break;
                    case 0x78:
                        func_80101F5C(wp, face, 0);
                        break;
                }
                break;
            case 1:
                switch (face->timer_0)
                {
                    case 0xAA:
                        func_80101FAC(wp, face, 1);
                        func_80101F84(wp, face, 1);
                        break;
                    case 0xDC:
                        func_80101F5C(wp, face, 0);
                        break;
                }
                break;
        }
        func_80101FD4(wp, face);
        face->timer_0++;
    }
}

void func_80101F34(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80103C3C[index];
}

void func_80101F5C(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80103C4C[index];
}

void func_80101F84(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_E = 0;
    face->shape_C = 0;
    face->prev_D  = -1;
    face->mouth_4 = D_80103C44[index];
}

void func_80101FAC(STAGE_OBJ *wp, STAGE_FACE *face, sint32 index)
{
    face->index_11 = 0;
    face->shape_F  = 0;
    face->prev_10  = -1;
    face->eyes_8   = D_80103C54[index];
}

void func_80101FD4(STAGE_OBJ *wp, STAGE_FACE *face)
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
        func_8002D320(wp->model_88, 0x110010, func_8002D404(face->shape_C, 0x33, 0x37, 5));
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
        func_8002D320(wp->model_88, 0x130012, func_8002D404(face->shape_F, 0x33, 0x37, 5));
    }
    face->prev_10 = face->shape_F;
}

void func_8010211C(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->rotation.z     = 0;
    wp->rotation.x     = 0;
    wp->rotation.y     = 0;
    wp->value_78       = 0;
    wp->flags_0 |= 3;
    wp->routine_0++;
    func_80102190(wp);
    wp->rotation.z = 0xB4;
}

void func_80102190(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        if (STAGE_SCENE_BYTE(8) == 1)
        {
            if (STAGE_SCENE_BYTE(9) == STAGE_SCENE_BYTE(8))
            {
                wp->u_C.b.byte_C = 1;
                Model_work_init(wp, &wp->u_C.b.byte_C);
                func_800322A8(wp, 1, 0);
                wp->rotation.z = 0;
                wp->routine_1++;
            }
        }
        else
        {
            wp->u_C.b.byte_C = 0;
            Model_work_init(wp, &wp->u_C.b.byte_C);
            func_800322A8(wp, 0, 0);
        }
    }
}

void func_8010223C(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_8010225C(STAGE_WORK *wp)
{
    D_80103C64[wp->routine_0](wp);
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032538(wp);
    func_800334C4(wp);
}

void func_801022C0(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;

    wp->z_34.value += 0x8000;
    wp->x_2C.half[1] += (wp->value_38.value -= 0x147A) >> 16;
    wp->x_2C.half[0] = (wp->x_2C.half[0] + (wp->z_34.value >> 16)) & 0xFFF;
    if (wp->x_2C.half[1] < 0)
    {
        func_80031988(wp);
        return;
    }
    v.x = (rcos(wp->x_2C.half[0]) * wp->x_2C.half[1]) >> 12;
    v.y = (rsin(wp->x_2C.half[0]) * wp->x_2C.half[1]) >> 12;
    v.z = 0;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY(wp->y_30.half[0], &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = wp->u_28.parent->x_1C + out.x;
    wp->y_1E = wp->u_28.parent->y_1E + out.y;
    wp->z_20 = wp->u_28.parent->z_20 + out.z;
}

void func_80102404(STAGE_FX *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->routine_0++;
    }
    func_801022C0(wp);
}

void func_8010244C(STAGE_FX *wp)
{
    wp->frame_E = 0;
    wp->flags_0 |= 2;
    if (Game_work.value_50 == 0x16)
    {
        wp->mode_14 = 0x3CC80027;
    }
    else
    {
        wp->mode_14 = 0x3C880026;
    }
    wp->color_18       = 0x2E808080;
    wp->value_38.value = 0xA0000;
    wp->h_26           = 0;
    wp->z_34.value     = 0;
    wp->value_3C.value = 0xFFFF0000;
    wp->routine_0++;
}

void func_801024B8(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    STAGE_FX *ep;
    sint16 angle;
    sint16 radius;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = out.x + (parent->position_fixed.v.x >> 16);
    wp->y_1E = out.y + (parent->position_fixed.v.y >> 16);
    wp->z_20 = out.z + (parent->position_fixed.v.z >> 16);
    if (wp->z_34.value < 0x900000)
    {
        wp->z_34.value += 0x170A3;
        wp->value_38.value += 0x8000;
        wp->value_3C.value -= 0x147A;
    }
    wp->h_26 = (wp->h_26 + 1) & 3;
    wp->w_24 = wp->z_34.value >> 16;
    wp->u_22 = D_80103C70[wp->h_26].u;
    wp->v_23 = D_80103C70[wp->h_26].v;
    if (++wp->frame_E == 4)
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0        = 1;
            ep->kind_2         = 6;
            ep->variant_3      = 0;
            ep->value_C        = 6;
            ep->timer_D        = 1;
            angle              = rand() & 0xFFF;
            radius             = (rand() & 0x1F) + 0x64;
            ep->mode_14        = 0x3C48002E;
            ep->w_24           = 0x12;
            ep->u_22           = 0x80;
            ep->color_18       = 0x2E202020;
            ep->v_23           = 0xA0;
            ep->u_28.parent    = wp;
            ep->x_2C.half[0]   = angle;
            ep->x_2C.half[1]   = radius;
            ep->y_30.half[0]   = rot;
            ep->z_34.value     = wp->value_38.value;
            ep->value_38.value = wp->value_3C.value;
        }
        wp->frame_E = 0;
    }
}

void func_801026CC(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_8010244C(wp);
        }
        func_801024B8(wp);
    }
    else
    {
        func_80102404(wp);
    }
}

void func_80102730(STAGE_FX *wp)
{
    wp->flags_0 |= 2;
    if (Game_work.value_50 == 0x16)
    {
        wp->mode_14 = 0x3CC80027;
    }
    else
    {
        wp->mode_14 = 0x3C880026;
    }
    wp->color_18 = 0x2E808080;
    wp->h_26     = 0;
    wp->routine_0++;
}

void func_80102788(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = out.x + (parent->position_fixed.v.x >> 16);
    wp->y_1E = out.y + (parent->position_fixed.v.y >> 16);
    wp->z_20 = out.z + (parent->position_fixed.v.z >> 16);
    if (++wp->h_26 == 4)
    {
        wp->h_26 = 0;
    }
    wp->u_22 = D_80103C80[wp->h_26].u;
    wp->v_23 = D_80103C80[wp->h_26].v;
    wp->w_24 = D_80103C80[wp->h_26].w;
}

void func_801028C8(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80102730(wp);
        }
        func_80102788(wp);
    }
}

void func_8010291C(STAGE_FX *wp)
{
    sint8 frame;

    frame = ++wp->type_F;
    if (frame == 8)
    {
        func_80031988(wp);
        return;
    }
    wp->color_18 = D_80103C90[frame];
    wp->w_24 += 0x10;
    if (wp->w_24 > 0x120)
    {
        wp->w_24 = 0x120;
    }
}

void func_8010299C(STAGE_FX *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->routine_0++;
    }
    func_8010291C(wp);
}

void func_801029E4(STAGE_FX *wp)
{
    wp->routine_0++;
}

void func_801029F8(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    uint16 rot;
    STAGE_FX *ep;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 6;
        ep->variant_3 = 2;
        ep->value_C   = 6;
        ep->timer_D   = 1;
        ep->frame_E   = 0;
        ep->type_F    = 0;
        if (Game_work.value_50 == 0x16)
        {
            ep->mode_14 = 0x3CC80027;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->w_24     = 0x90;
        ep->u_22     = 0xA0;
        ep->v_23     = 0x20;
        ep->x_1C     = out.x + (parent->position_fixed.v.x >> 16);
        ep->y_1E     = out.y + (parent->position_fixed.v.y >> 16);
        ep->z_20     = out.z + (parent->position_fixed.v.z >> 16);
        ep->color_18 = 0x2E808080;
    }
    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 6;
        ep->variant_3 = 2;
        ep->value_C   = 6;
        ep->timer_D   = 1;
        ep->frame_E   = 1;
        ep->type_F    = 0;
        if (Game_work.value_50 == 0x16)
        {
            ep->mode_14 = 0x3CC80027;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->w_24     = 0x24;
        ep->u_22     = 0xA0;
        ep->v_23     = 0x20;
        ep->x_1C     = out.x + (parent->position_fixed.v.x >> 16);
        ep->y_1E     = out.y + (parent->position_fixed.v.y >> 16);
        ep->z_20     = out.z + (parent->position_fixed.v.z >> 16);
        ep->color_18 = 0x2E808080;
    }
}

void func_80102BEC(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_801029E4(wp);
        }
        func_801029F8(wp);
    }
    else
    {
        func_8010299C(wp);
    }
}

void func_80102C50(void)
{
}

void func_80102C58(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        func_80102C50();
    }
    else
    {
        func_8010299C(wp);
    }
}

void func_80102C98(STAGE_FX *wp)
{
    if (wp->routine_0 == 2)
    {
        func_80031988(wp);
    }
    else
    {
        D_80103CB0[wp->variant_3](wp);
    }
}

STAGE_FX *func_80102CF4(STAGE_OBJ *parent, sint16 angle, sint16 radius, sint16 height,
                        uint8 variant)
{
    STAGE_FX *ep;

    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0             = 1;
        ep->kind_2              = 6;
        ep->variant_3           = variant;
        ep->timer_D             = 0;
        ep->u_28.object         = parent;
        ep->x_2C.words.fraction = angle;
        ep->x_2C.words.integer  = radius;
        ep->y_30.words.fraction = height;
        return ep;
    }
    return NULL;
}
