#include "common.h"
#include "st08.h"

void func_8010BCBC(ST08_10C *wp, sint16 scale)
{
    STCOM_FIXED_VECTOR v;

    wp->pos_AC = wp->position;
    RotMatrixYXZ(&wp->rotation.v, &wp->matrix);
    v.x = scale;
    v.y = scale;
    v.z = scale;
    ScaleMatrix(&wp->matrix, &v);
}

void func_8010BD3C(ST08_10C *wp)
{
    STCOM_SVECTOR pos;

    pos = wp->position;
    func_800341BC(&pos, 0x1E, 0, 0x8000, wp->value_1, &wp->hit_BC, 0xC800000, 0x800000, 0x80);
    wp->hit_BC = 0;
}

void func_8010BDC0(ST08_10C *wp)
{
    wp->position.x        = 0x1F4;
    wp->position.y        = -0x10;
    wp->position.z        = -0xA0;
    wp->variant_3         = 0;
    wp->turn_64           = 0;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->turn_64           = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->flags_0 |= 6;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->position_prev                                = wp->position;
    wp->rotation_prev                                = wp->rotation.v;
    wp->color_B4                                     = 0x808080;
    func_8010BCBC(wp, 0x200);
    Model_work_init(wp, NULL);
    wp->hit_BC = 0;
    wp->routine_0++;
}

void func_8010BECC(ST08_10C *wp)
{
    STAGE_OBJ *obj;
    STAGE_10C *shot;
    sint32 angle;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    if (wp->hit_BC & 0x20000000)
    {
        Sound_call2(0x160, &wp->position);
        if (++STAGE_SCENE_WORD(0x10) % 5 == 0)
        {
            obj = func_80031418();
            if (obj != NULL)
            {
                obj->flags_0   = 1;
                obj->kind_2    = 8;
                obj->routine_0 = 1;
            }
        }
        else
        {
            shot = Open_SHL_WORK();
            if (shot != NULL)
            {
                shot->flags_0 = 1;
                shot->kind_2  = 0x21;
            }
        }
        STAGE_SCENE_BYTE(0xB) = 0;
        angle                 = Angle_xz_svector(&wp->position, &Player_work.position);
        wp->velocity.v.x      = (uint32)(rsin(angle) * 25) >> 11;
        wp->velocity.v.y      = -0x10;
        wp->velocity.v.z      = (uint32)(rcos(angle) * 15) >> 9;
        wp->routine_0++;
    }
    else if (wp->position.x > 0)
    {
        wp->rotation.v.z -= 0x100;
        wp->position.x -= 0x14;
    }
    else
    {
        wp->position.x = 0;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position.y << 16;
    func_8010BCBC(wp, 0x200);
    func_8010BD3C(wp);
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_8010C0E4(ST08_10C *wp)
{
    sint16 id;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    wp->position.x += wp->velocity.v.x;
    wp->position.y += wp->velocity.v.y;
    wp->position.z += wp->velocity.v.z;
    wp->rotation.v.x -= 0x100;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    if (wp->position.z >= 0x400 || (wp->hit_BC & 0x4000000))
    {
        id = 0x161;
        if (wp->hit_BC & 0x4000000)
        {
            id = 0x162;
        }
        Sound_call2(id, &wp->position);
        if (wp->velocity.v.x < 0)
        {
            wp->velocity.v.x = -0x50;
        }
        else
        {
            wp->velocity.v.x = 0x50;
        }
        wp->velocity.v.z = 0;
        wp->velocity.v.y = -0x3C;
        wp->routine_0++;
    }
    else
    {
        func_8010BD3C(wp);
    }
    func_8010BCBC(wp, 0x200);
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_8010C268(ST08_10C *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    wp->position.x += wp->velocity.v.x;
    wp->position.y += wp->velocity.v.y;
    wp->position.z += wp->velocity.v.z;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    if (wp->position.y < -0x257)
    {
        Close_SHL_WORK(wp);
        return;
    }
    func_8010BCBC(wp, 0x200);
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_8010C37C(STAGE_10C *wp)
{
    if (STAGE_SCENE_BYTE(4) == 0xB)
    {
        Close_SHL_WORK(wp);
    }
    else
    {
        D_801140C0[wp->routine_0](wp);
    }
}

void func_8010C3D8(ST08_10C *wp)
{
    ST08_SCALE_SIZES size = D_801001D8;
    STCOM_FIXED_VECTOR scale;

    wp->pos_AC = wp->position;
    RotMatrixYXZ(&wp->rotation.v, &wp->matrix);
    scale.x = size.value[wp->value_D];
    scale.y = size.value[wp->value_D];
    scale.z = size.value[wp->value_D];
    ScaleMatrix(&wp->matrix, &scale);
}

void func_8010C4AC(ST08_10C *wp)
{
    STCOM_SVECTOR pos;

    pos = wp->position;
    func_800341BC(&pos, 0x78 - wp->value_D * 0x1E, 0, 0x8000, wp->value_1, &wp->hit_BC, 0x4880000, 0x800000, 0x80);
    wp->hit_BC = 0;
}

// Spawns a kind-0x26 slot at wp's position, thrown toward `angle` - 0x400.
void func_8010C544(ST08_10C *wp, sint32 angle)
{
    ST08_10C *obj;
    sint32 dir;

    obj = (ST08_10C *)Open_SHL_WORK();
    if (obj != NULL)
    {
        obj->flags_0  = 1;
        obj->kind_2   = 0x26;
        obj->value_C  = wp->value_C;
        obj->value_D  = wp->value_D;
        obj->value_E  = 1;
        obj->value_F  = wp->value_F;
        obj->position = wp->position;
        if (obj->value_C != 0)
        {
            obj->speed_CC = (rand() & 3) * 10 + 100;
        }
        else
        {
            obj->speed_CC = (rand() & 3) * 10 + 50;
        }
        dir               = angle - 0x400;
        obj->velocity.v.x = (uint32)(rsin(dir) * obj->speed_CC) >> 12;
        obj->velocity.v.z = (uint32)(rcos(dir) * obj->speed_CC) >> 12;
    }
}

void func_8010C670(ST08_10C *wp)
{
    wp->turn_64           = 0;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->turn_64           = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->rotation.v.y      = 0x400;
    wp->flags_0 |= 6;
    wp->position_prev    = wp->position;
    wp->value_4E         = 0x10;
    wp->velocity.v.y     = 0;
    wp->value_4C         = 0;
    wp->value_50         = 0;
    wp->color_B4         = 0x808080;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    wp->data_78                                      = D_801140D0[wp->value_D];
    func_8010C3D8(wp);
    wp->variant_3 = wp->value_C * 4;
    Model_work_init(wp, &wp->variant_3);
    func_8010C4AC(wp);
    wp->routine_0++;
}

void func_8010C784(ST08_10C *wp, STAGE_OBJ50 *owner)
{
    sint32 hit;
    sint32 ground;
    sint32 angle;
    sint32 dir;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    if (wp->value_E != 0 && !(STAGE_FRAME & 3))
    {
        if (++wp->variant_3 > wp->value_C * 4 + 3)
        {
            wp->variant_3 = wp->value_C * 4;
            wp->value_E   = 0;
        }
        Model_work_init(wp, &wp->variant_3);
    }
    hit = wp->hit_BC;
    if (hit & 0x20000000)
    {
        wp->speed_CC     = (rand() & 3) * 10 + 300;
        angle            = Angle_xz_svector(&wp->position, &Player_work.position);
        wp->velocity.v.x = (uint32)(rsin(angle) * wp->speed_CC) >> 12;
        wp->velocity.v.z = (uint32)(rcos(angle) * wp->speed_CC) >> 12;
        wp->value_E      = 1;
    }
    else if (hit & 0x2000000)
    {
        angle            = Angle_xz_svector(&wp->position, &Player_work.position);
        wp->velocity.v.x = (uint32)(rsin(angle) * wp->speed_CC) >> 12;
        wp->velocity.v.z = (uint32)(rcos(angle) * wp->speed_CC) >> 12;
        wp->value_E      = 1;
    }
    else if (hit & 0x8000000)
    {
        if (wp->value_C != 0)
        {
            Sound_call2(0x16B, &wp->position);
        }
        else
        {
            Sound_call2(0x16C, &wp->position);
        }
        if (wp->value_D == 2)
        {
            if (wp->value_C != 0)
            {
                owner->u_C.b.lo++;
            }
            else
            {
                owner->value_48 += 30;
                MojiTaskExec2(4, 0x2C);
            }
            Close_SHL_WORK(wp);
            return;
        }
        wp->value_D++;
        wp->value_E      = 1;
        wp->data_78      = D_801140D0[wp->value_D];
        angle            = Angle_xz_svector(&wp->position, &Player_work.position);
        dir              = angle + 0x400;
        wp->velocity.v.x = (uint32)(rsin(dir) * wp->speed_CC) >> 12;
        wp->velocity.v.z = (uint32)(rcos(dir) * wp->speed_CC) >> 12;
        func_8010C544(wp, angle);
    }
    else if (hit & 0x4000000)
    {
        angle            = Angle_xz_svector(&wp->position, &wp->value_C4);
        wp->velocity.v.x = (uint32)(rsin(angle) * wp->speed_CC) >> 12;
        wp->velocity.v.z = (uint32)(rcos(angle) * wp->speed_CC) >> 12;
        wp->value_E      = 1;
    }
    wp->rotation.v.y = (wp->rotation.v.y + 8) & 0xFFF;
    wp->velocity.v.y += wp->value_4E;
    wp->position_fixed.x += wp->velocity.v.x << 12;
    wp->position_fixed.z += wp->velocity.v.z << 12;
    wp->position_fixed.y += wp->velocity.v.y << 12;
    func_80030150(&wp->position_fixed, &wp->position);
    ground = Obj_map_push_out(wp);
    if (ground != 0)
    {
        wp->value_E = 1;
        Wall_reflect_spd(&wp->velocity.v, ground);
    }
    func_8010C3D8(wp);
    func_8010C4AC(wp);
    Model_Shadow_Trans(wp, 100 - wp->value_D * 20, 0x200, 0);
}

void func_8010CB24(STAGE_FX *wp)
{
    D_801140F4[wp->routine_0](wp, func_80036294((uint8)wp->type_F));
}
