#include "common.h"
#include "st1a.h"

void func_80124AB4(ST1A_50 *wp)
{
    D_80133234[wp->routine_0](wp, &Scene_work, &wp->rot_48);
    func_80125438(wp, &wp->rot_48);
}

void func_80124B18(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    wp->flags_0 |= 6;
    func_8002F9C4(wp, &wp->variant_3);
    wp->color_40  = 0x808080;
    rot->x        = 0;
    rot->y        = 0x1000;
    rot->z        = 0;
    rot->pad      = D_80133264[wp->variant_3];
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_80124BA8(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    D_8013323C[wp->variant_3](wp, scene, rot);
}

void func_80124BE4(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x3C)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            rot->z += 0xA;
            if (rot->z == 0x500)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0xD && scene->value_10 == 0x14)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->z -= 0xA;
            if (rot->z == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80124CBC(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x3C)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            rot->z -= 0xA;
            if (rot->z == -0x500)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 0xD && scene->value_10 == 0x14)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->z += 0xA;
            if (rot->z == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80124D94(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 3)
            {
                if (scene->value_10 >= 5 && scene->value_10 < 0x36)
                {
                    func_801254E8(wp, scene);
                }
                if (scene->value_10 == 0x3F)
                {
                    wp->routine_1++;
                }
            }
            break;
        case 1:
            rot->pad += 0x10;
            if (rot->pad == 0x400)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            break;
    }
}

void func_80124E50(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0xE)
            {
                func_801255CC(wp);
                wp->routine_1++;
            }
            break;
        case 1:
            rot->y -= 0x400;
            if (rot->y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x1E)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->y -= 0x80;
            if (rot->y == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80124F4C(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0xA)
            {
                func_801255CC(wp);
                wp->routine_1++;
            }
            break;
        case 1:
            rot->y -= 0x400;
            if (rot->y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x1E)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->y -= 0x80;
            if (rot->y == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80125048(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 5 && scene->value_10 == 8)
            {
                func_801255CC(wp);
                wp->routine_1++;
            }
            break;
        case 1:
            rot->y -= 0x400;
            if (rot->y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x1E)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->y -= 0x80;
            if (rot->y == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80125144(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0xC)
            {
                func_801255CC(wp);
                wp->routine_1++;
            }
            break;
        case 1:
            rot->y -= 0x400;
            if (rot->y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x1E)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->y -= 0x80;
            if (rot->y == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80125240(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 8)
            {
                func_801255CC(wp);
                wp->routine_1++;
            }
            break;
        case 1:
            rot->y -= 0x400;
            if (rot->y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x1E)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->y -= 0x80;
            if (rot->y == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_8012533C(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 8)
            {
                func_801255CC(wp);
                wp->routine_1++;
            }
            break;
        case 1:
            rot->y -= 0x400;
            if (rot->y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (scene->u_8.byte[1] == 6 && scene->value_10 == 0x1E)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            rot->y -= 0x80;
            if (rot->y == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            break;
    }
}

void func_80125438(ST1A_50 *wp, STCOM_SVECTOR *rot)
{
    STCOM_FIXED_VECTOR scale;

    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    if (wp->variant_3 == 2)
    {
        scale.x = scale.y = scale.z = 0x11A0;
    }
    else
    {
        scale.z = 0x1000;
        scale.x = 0x1000;
        scale.y = rot->y;
    }
    scale.pad = 0;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    RotMatrixY(rot->z, &wp->matrix_18.m);
    RotMatrixZ(rot->pad, &wp->matrix_18.m);
}

void func_801254E8(ST1A_50 *wp, STAGE_SCENE_WORK *scene)
{
    STCOM_SVECTOR *pos;
    uint32 step;
    STCOM23_PACKET *packet;

    pos    = &wp->pos_38;
    step   = (uint8)(scene->value_10 - 5);
    packet = func_8002D464();
    if (step < 0x10)
    {
        packet->code_4 = (step * 8) | 0x2E000000;
    }
    else if (step > 0x20)
    {
        packet->code_4 = ((0x30 - step) * 8) | 0x2E000000;
    }
    else
    {
        packet->code_4 = 0x2E000080;
    }
    packet->xy_8    = ((pos->x - 0x18) & 0xFFFF) | ((pos->y + 0x24) << 16);
    packet->z_10    = pos->z - 0x10;
    packet->uv_1C   = 0x7FA0;
    packet->uv_24   = 0x7FBF;
    packet->uv_C    = 0x3D4860A0;
    packet->uv_14   = 0x2E60BF;
    packet->size_18 = 8;
    packet->pad_20  = 8;
}

void func_801255CC(ST1A_50 *wp)
{
    STCOM_EFFECT *fx;

    fx = func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 0x1C;
        fx->variant_3 = 0;
        fx->value_C   = wp->value_1;
        fx->value_D   = wp->variant_3;
    }
}

void func_80125628(ST1A_HAND50 *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STCOM_SVECTOR out;
    ST1A_HAND_OWNER *owner;

    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 6;
            func_8002F9C4(wp, &wp->variant_3);
            wp->color_40 = 0x808080;
            wp->routine_0++;
            // fall through
        case 1:
            if (wp->routine_1 == 0)
            {
                owner         = func_80036294(wp->id_C);
                wp->matrix_18 = owner->matrix_1E8;
                rot.x         = 0;
                rot.y         = wp->angle_48 + 0x5DC;
                rot.z         = 0;
                ApplyMatrixSV(&owner->matrix_1E8, &rot, &out);
                wp->pos_38.x = out.x + owner->pos_180.x;
                wp->pos_38.y = out.y + owner->pos_180.y;
                wp->pos_38.z = out.z + owner->pos_180.z;
            }
            else if (wp->routine_1 == 1) // the same body as routine_1 2: cross-jumping merges them
            {
                rot.x = 0;
                rot.y = 0;
                rot.z = 0x200;
                RotMatrixYXZ(&rot, &wp->matrix_18);
                scale.x = 0x200;
                scale.y = 0x200;
                scale.z = 0x200;
                ScaleMatrix(&wp->matrix_18, &scale);
                rot.x = 0;
                rot.y = wp->angle_48;
                rot.z = 0;
                ApplyMatrixSV(&wp->matrix_18, &rot, &out);
                wp->pos_38.x = out.x;
                wp->pos_38.y = out.y;
                wp->pos_38.z = out.z;
            }
            else if (wp->routine_1 == 2)
            {
                rot.x = 0;
                rot.y = 0;
                rot.z = 0x200;
                RotMatrixYXZ(&rot, &wp->matrix_18);
                scale.x = 0x200;
                scale.y = 0x200;
                scale.z = 0x200;
                ScaleMatrix(&wp->matrix_18, &scale);
                rot.x = 0;
                rot.y = wp->angle_48;
                rot.z = 0;
                ApplyMatrixSV(&wp->matrix_18, &rot, &out);
                wp->pos_38.x = out.x;
                wp->pos_38.y = out.y;
                wp->pos_38.z = out.z;
            }
            else if (wp->routine_1 == 3)
            {
                rot.x = 0;
                rot.y = 0;
                rot.z = 0;
                RotMatrixYXZ(&rot, &wp->matrix_18);
                scale.x = 0x800;
                scale.y = 0x800;
                scale.z = 0x800;
                ScaleMatrix(&wp->matrix_18, &scale);
            }
            break;
    }
}
