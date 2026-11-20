#include "common.h"
#include "stage_common/stcom11.h"

// Shared stage code, linked into 6 stages: r3_st09, r3_st0a, r3_st13, r3_st14, r3_st1a and
// r3_st1d. Each stage compiles this file against its own copy of the assembly (TARGET_ASM, set
// by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom11"

void stcom11_func_0000(STCOM11_WORK *wp)
{
    stcom11_D_0000[wp->routine_0](wp);
}

void stcom11_func_003C(STCOM11_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl                      = &Player_work;
    wp->sprite.mode_0       = 0x3D08000E;
    wp->sprite.color_4.word = 0x2C808080;
    wp->value_10            = 0;
    wp->value_78            = 0;
    wp->flags_0 |= 0x22;
    wp->sprite.pos_8[0] = wp->position.x = wp->position_fixed.x >> 16;
    wp->sprite.pos_8[1] = wp->position.y = wp->position_fixed.y >> 16;
    wp->sprite.pos_8[2] = wp->position.z = wp->position_fixed.z >> 16;
    wp->position_fixed_prev              = wp->position_fixed;
    wp->position_prev                    = wp->position;
    wp->sprite.value_E                   = 0xE0;
    wp->sprite.value_F                   = 0x20;
    wp->sprite.value_10                  = 0x20;
    wp->param_D                          = 20;
    wp->sprite.value_12                  = 0;
    switch (wp->type_3)
    {
        case 3:
            wp->sprite.value_10     = 0x30;
            wp->sprite.color_4.word = 0x2C8080FF;
            wp->param_D             = 40;
            // fall through
        case 0:
            wp->routine_0  = 1;
            wp->routine_1  = 0;
            wp->routine_2  = 0;
            wp->routine_3  = 120;
            wp->timer_E    = 0;
            wp->velocity.x = (uint32)(-rsin(wp->angle_64) * 9) >> 10;
            wp->velocity.y =
                (pl->value_3EA - wp->position.y) / (((sint32)func_80030254(wp, pl) + 36) / 36);
            wp->velocity.z = (uint32)(-rcos(wp->angle_64) * 9) >> 10;
            wp->accel.x    = 0;
            wp->accel.y    = 0;
            wp->accel.z    = 0;
            break;
        case 1:
            wp->routine_0  = 2;
            wp->routine_3  = 60;
            wp->routine_1  = 0;
            wp->routine_2  = 0;
            wp->timer_E    = 0;
            wp->velocity.x = 0x200;
            wp->velocity.y = 0;
            wp->velocity.z = 0;
            wp->accel.x    = 0;
            wp->accel.y    = 0;
            wp->accel.z    = 0;
            wp->rotation.x = 0;
            wp->rotation.z = 0;
            wp->rotation.y = wp->angle_64;
            break;
        case 2:
            wp->routine_0  = 3;
            wp->routine_3  = 60;
            wp->routine_1  = 0;
            wp->routine_2  = 0;
            wp->timer_E    = 0;
            wp->velocity.y = 0;
            wp->velocity.z = 0;
            wp->accel.x    = 0;
            wp->accel.y    = 0;
            wp->accel.z    = 0;
            wp->rotation.x = 0;
            wp->rotation.z = 0;
            wp->velocity.x = (sint8)wp->param_C << 4;
            wp->rotation.y = wp->angle_64;
            break;
    }
    if (func_80049C24(wp))
    {
        Close_SHL_WORK(wp);
    }
    wp->sprite.hit_14 = 0;
    Sound_call2(0x1AF, &wp->position);
}

void stcom11_func_0308(STCOM11_WORK *wp)
{
    STCOM_EFFECT *effect;
    sint32 frame;

    wp->position_fixed_prev = wp->position_fixed;
    wp->position_prev       = wp->position;
    if (--wp->routine_3 == 0)
    {
        Close_SHL_WORK(wp);
    }
    else
    {
        if (wp->routine_2 == 6)
        {
            frame = 0;
        }
        else
        {
            frame = wp->routine_2 + 2;
        }
        wp->routine_2       = frame;
        wp->sprite.value_E  = stcom11_D_0014[wp->routine_2];
        wp->sprite.value_F  = stcom11_D_0014[wp->routine_2 + 1];
        wp->sprite.value_12 = (wp->sprite.value_12 + 8) & 0x3F;
        wp->position_fixed.x += (wp->velocity.x + wp->accel.x) << 16;
        wp->position_fixed.y += wp->velocity.y << 16;
        wp->position_fixed.z += (wp->velocity.z + wp->accel.z) << 16;
        func_80030150(&wp->position_fixed, &wp->position);
        if (wp->timer_E == 0 || --wp->timer_E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 1;
                effect->kind_2          = 0xF;
                effect->variant_3       = 4;
                effect->value_C         = 0;
                effect->sprite.pos_8[0] = wp->sprite.pos_8[0];
                effect->sprite.pos_8[1] = wp->sprite.pos_8[1];
                effect->sprite.pos_8[2] = wp->sprite.pos_8[2];
                wp->timer_E             = 2;
            }
        }
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
    }
    if (func_80049C24(wp) || (wp->sprite.hit_14 & 0x2000000))
    {
        wp->routine_0      = 4;
        wp->sprite.value_E = 0;
        wp->sprite.value_F = 0x40;
    }
    else if (wp->flags_0 & 1)
    {
        func_800341BC(&wp->position, wp->sprite.value_10 + 0x10, 0, 0xA000, wp->value_1,
                      &wp->sprite.hit_14, wp->param_D | 0x8000000, 0, 0x80);
    }
    wp->sprite.hit_14 = 0;
}

void stcom11_func_0564(STCOM11_WORK *wp)
{
    STCOM_EFFECT *effect;
    sint32 frame;

    wp->position_fixed_prev = wp->position_fixed;
    wp->position_prev       = wp->position;
    if (--wp->routine_3 == 0)
    {
        Close_SHL_WORK(wp);
    }
    else
    {
        if (wp->routine_2 == 6)
        {
            frame = 0;
        }
        else
        {
            frame = wp->routine_2 + 2;
        }
        wp->routine_2       = frame;
        wp->sprite.value_E  = stcom11_D_0014[wp->routine_2];
        wp->sprite.value_F  = stcom11_D_0014[wp->routine_2 + 1];
        wp->sprite.value_12 = (wp->sprite.value_12 + 8) & 0x3F;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        if (wp->timer_E == 0 || --wp->timer_E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 1;
                effect->kind_2          = 0xF;
                effect->variant_3       = 4;
                effect->value_C         = 0;
                effect->sprite.pos_8[0] = wp->sprite.pos_8[0];
                effect->sprite.pos_8[1] = wp->sprite.pos_8[1];
                effect->sprite.pos_8[2] = wp->sprite.pos_8[2];
                wp->timer_E             = 2;
            }
        }
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
    }
    if (func_80049C24(wp) || (wp->sprite.hit_14 & 0x2000000))
    {
        wp->routine_0      = 4;
        wp->sprite.value_E = 0;
        wp->sprite.value_F = 0x40;
    }
    else if (wp->flags_0 & 1)
    {
        func_800341BC(&wp->position, wp->sprite.value_10 + 0x10, 0, 0xA000, wp->value_1,
                      &wp->sprite.hit_14, wp->param_D | 0x8000000, 0, 0x80);
    }
    wp->sprite.hit_14 = 0;
}

void stcom11_func_077C(STCOM11_WORK *wp)
{
    STCOM_EFFECT *effect;
    sint32 frame;

    wp->position_fixed_prev = wp->position_fixed;
    wp->position_prev       = wp->position;
    if (--wp->routine_3 == 0)
    {
        Close_SHL_WORK(wp);
    }
    else
    {
        if (wp->routine_2 == 6)
        {
            frame = 0;
        }
        else
        {
            frame = wp->routine_2 + 2;
        }
        wp->routine_2       = frame;
        wp->sprite.value_E  = stcom11_D_0014[wp->routine_2];
        wp->sprite.value_F  = stcom11_D_0014[wp->routine_2 + 1];
        wp->sprite.value_12 = (wp->sprite.value_12 + 8) & 0x3F;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        if (wp->timer_E == 0 || --wp->timer_E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 1;
                effect->kind_2          = 0xF;
                effect->variant_3       = 4;
                effect->value_C         = 0;
                effect->sprite.pos_8[0] = wp->sprite.pos_8[0];
                effect->sprite.pos_8[1] = wp->sprite.pos_8[1];
                effect->sprite.pos_8[2] = wp->sprite.pos_8[2];
                wp->timer_E             = 2;
            }
        }
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
    }
    if (func_80049C24(wp) || (wp->sprite.hit_14 & 0x2000000))
    {
        wp->routine_0      = 4;
        wp->sprite.value_E = 0;
        wp->sprite.value_F = 0x40;
    }
    else if (wp->flags_0 & 1)
    {
        func_800341BC(&wp->position, wp->sprite.value_10 + 0x10, 0, 0xA000, wp->value_1,
                      &wp->sprite.hit_14, wp->param_D | 0x8000000, 0, 0x80);
    }
    wp->sprite.hit_14 = 0;
}

void stcom11_func_0994(STCOM11_WORK *wp)
{
    Close_SHL_WORK(wp);
}
