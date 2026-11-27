#include "common.h"
#include "st04.h"

void func_801083E4(ST04_ROCK *wp)
{
    STCOM_SVECTOR unused; // unused: reserves the frame's 8 extra bytes

    D_8010CBB0[wp->routine_0](wp);
    wp->hit_BC[0] = 0;
    wp->pos_AC    = wp->position;
    func_800341BC(&wp->position, 0x20, 0, 0x8000, wp->slot, wp->hit_BC, 0x4000000, 0, 0x80);
    Model_Shadow_Trans(wp, 0x14, 0x200, 0);
}

void func_8010849C(ST04_ROCK *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->be_flag |= 6;
    Model_work_init(wp, NULL);
    wp->rotation.x      = 0x400;
    wp->rotation.z      = 0;
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    wp->rotation.y      = wp->value_F * 16;
    RotMatrixYXZ(&wp->rotation, &wp->matrix.m);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&wp->matrix.m, &scale);
    wp->spin_64             = 0x200;
    wp->velocity.v.x        = 0;
    wp->velocity.v.y        = 0;
    wp->velocity.v.z        = 0;
    wp->accel.x             = 0;
    wp->accel.y             = 0;
    wp->accel.z             = 0;
    wp->spin_66             = 0x80;
    wp->hit_BC[3]           = 0;
    wp->hit_BC[2]           = 0;
    wp->hit_BC[1]           = 0;
    wp->hit_BC[0]           = 0;
    wp->color_B4            = 0x808080;
    wp->position_fixed_prev = wp->position_fixed;
    wp->position_prev       = wp->position;
    wp->data_78             = D_8010CBA4;
    Obj_map_push_out(wp);
    wp->value_74 = 0;
    wp->routine_0++;
}

void func_801085EC(ST04_ROCK *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR unused; // unused: reserves the frame's 8 extra bytes
    sint32 speed;
    sint32 rise;

    wp->position_fixed_prev = wp->position_fixed;
    wp->position_prev       = wp->position;
    func_801088BC(wp);
    if (wp->routine_2 != 0)
    {
        wp->value_74   = 1;
        wp->rotation.x = (wp->rotation.x + wp->spin_64) & 0xFFF;
        wp->rotation.y = (wp->rotation.y + wp->spin_66) & 0xFFF;
        wp->rotation.z = 0;
    }
    else
    {
        wp->value_74 = 0;
    }
    RotMatrixYXZ(&wp->rotation, &wp->matrix.m);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&wp->matrix.m, &scale);
    func_80108794(wp);
    if (wp->hit_BC[0] & 0x20000000)
    {
        speed            = (rand() & 0xF) + 0x20;
        rise             = (rand() & 0xF) + 0x28;
        wp->velocity.v.x = (-rsin(Player_work.rotation.y) * speed) >> 4;
        wp->velocity.v.y = -rise << 8;
        wp->velocity.v.z = (-rcos(Player_work.rotation.y) * speed) >> 4;
        wp->accel.y      = 0x300;
        wp->routine_2    = 1;
        Sound_call2(0x138, &wp->position);
    }
    func_80030150(&wp->position_fixed, &wp->position);
}

// Retail's bounce branch starts with the velocity reload; GCC schedules the sound id and
// position argument earlier and fills the delay slots differently.
sint32 func_80108794(ST04_ROCK *wp)
{
    sint32 hit;
    sint32 landed;
    sint32 bounce;

    landed = 0;
    hit    = Obj_map_push_out(wp);
    if (hit != 0)
    {
        if (hit & 0x1000)
        {
            if ((wp->velocity.v.y < 0 ? -wp->velocity.v.y : wp->velocity.v.y) < 0xA01)
            {
                landed           = 1;
                wp->velocity.v.x = 0;
                wp->velocity.v.y = 0;
                wp->velocity.v.z = 0;
                wp->accel.x      = 0;
                wp->accel.y      = 0;
                wp->accel.z      = 0;
                wp->routine_2    = 0;
                wp->rotation.x   = 0x400;
                Sound_call2(0x13A, &wp->position);
            }
            else
            {
                bounce = wp->velocity.v.y * 0xA0;
                if (bounce < 0)
                {
                    bounce = -bounce;
                }
                bounce           = (uint32)bounce >> 8;
                wp->velocity.v.y = bounce;
                wp->velocity.v.x = wp->velocity.v.x >> 1;
                wp->velocity.v.z = wp->velocity.v.z >> 1;
                Sound_call2(0x139, &wp->position);
            }
        }
        else
        {
            Sound_call2(0x13B, &wp->position);
        }
        Wall_reflect_spd(&wp->velocity.v, hit);
    }
    return landed;
}

void func_801088BC(ST04_ROCK *wp)
{
    wp->velocity.v.x += wp->accel.x;
    wp->velocity.v.y += wp->accel.y;
    wp->velocity.v.z += wp->accel.z;
    if (wp->velocity.v.x < -0x6000)
    {
        wp->velocity.v.x = -0x6000;
    }
    else if (wp->velocity.v.x > 0x6000)
    {
        wp->velocity.v.x = 0x6000;
    }
    if (wp->velocity.v.y < -0x6000)
    {
        wp->velocity.v.y = -0x6000;
    }
    else if (wp->velocity.v.y > 0x6000)
    {
        wp->velocity.v.y = 0x6000;
    }
    if (wp->velocity.v.z < -0x6000)
    {
        wp->velocity.v.z = -0x6000;
    }
    else if (wp->velocity.v.z > 0x6000)
    {
        wp->velocity.v.z = 0x6000;
    }
    wp->position_fixed.x += wp->velocity.v.x << 8;
    wp->position_fixed.y += wp->velocity.v.y << 8;
    wp->position_fixed.z += wp->velocity.v.z << 8;
    func_80030150(&wp->position_fixed, &wp->position);
}
