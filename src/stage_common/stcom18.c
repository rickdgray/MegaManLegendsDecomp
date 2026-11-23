#include "common.h"
#include "stage_common/stcom18.h"

// Shared stage code, linked into 7 stages: r3_st05, r3_st0a, r3_st0c, r3_st10, r3_st11, r3_st1a
// and r3_st1d. Each stage compiles this file against its own copy of the assembly (TARGET_ASM,
// set by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom18"

void stcom18_func_0000(STCOM18_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom18_D_0018[wp->routine_0](wp);
}

void stcom18_func_009C(STCOM18_WORK *wp)
{
    wp->sprite.value_12 = 0;
    wp->flags_0 |= 0x22;
    if (!(wp->flags_F & 1))
    {
        wp->sprite.value_E = 0x40;
        wp->sprite.value_F = 0x80;
        if (!(wp->flags_F & 0x10))
        {
            wp->sprite.color_4.word = 0x2C808080;
        }
        else
        {
            wp->sprite.color_4.word = 0x2C6060C0;
        }
        wp->sprite.mode_0 = 0x3D08000E;
    }
    else
    {
        if (!(wp->flags_F & 8))
        {
            wp->sprite.value_E = stcom18_D_0000[0].a;
            wp->sprite.value_F = stcom18_D_0000[0].b;
        }
        else
        {
            wp->sprite.value_E = stcom18_D_000C[0].a;
            wp->sprite.value_F = stcom18_D_000C[0].b;
        }
        wp->sprite.color_4.word = 0x2C808080;
        wp->sprite.mode_0       = 0x3D48000E;
    }
    wp->sprite.pos_8[0] = wp->position.x;
    wp->sprite.pos_8[1] = wp->position.y;
    wp->sprite.pos_8[2] = wp->position.z;
    if (!(wp->flags_F & 2))
    {
        wp->sprite.value_10 = 0x20;
        if (!(wp->flags_F & 0x10))
        {
            wp->kind_E = 4;
        }
        else
        {
            wp->kind_E = 0x20;
        }
    }
    else
    {
        wp->sprite.value_10 = 0x10;
        wp->kind_E          = 8;
    }
    if (!(wp->flags_F & 0x20))
    {
        wp->timer_B = 0xF0;
    }
    else
    {
        wp->timer_B = 0x4B;
    }
    wp->data_10  = NULL;
    wp->value_78 = 0;
    wp->hit_BC   = 0;
    func_800341BC(&wp->position, wp->sprite.value_10, 0, 0xA000, wp->value_1, &wp->hit_BC, wp->kind_E | 0x8000000, 0, 0x80);
    if (func_80049C24(wp))
    {
        wp->routine_0 = 2;
    }
    else
    {
        wp->routine_0++;
    }
}

void stcom18_func_0260(STCOM18_WORK *wp)
{
    sint32 frame;
    sint32 hit;

    wp->timer_B--;
    if (!(wp->flags_F & 1))
    {
        wp->sprite.value_12 = (wp->sprite.value_12 + 8) & 0x3F;
    }
    else
    {
        frame = (0xF0 - wp->timer_B) % 6;
        if (!(wp->flags_F & 8))
        {
            wp->sprite.value_E = stcom18_D_0000[frame].a;
            wp->sprite.value_F = stcom18_D_0000[frame].b;
        }
        else
        {
            wp->sprite.value_E = stcom18_D_000C[frame].a;
            wp->sprite.value_F = stcom18_D_000C[frame].b;
        }
        wp->sprite.color_4.word = 0x2C808080;
        Pos_Shadow_Trans(&wp->position, 0x30, 0x200, 0);
    }
    if (wp->timer_B != 0 && wp->position.y < 0)
    {
        wp->velocity.v.x += wp->accel.x;
        wp->velocity.v.y += wp->accel.y;
        wp->velocity.v.z += wp->accel.z;
        wp->position_fixed.x += wp->velocity.v.x << 8;
        wp->position_fixed.y += wp->velocity.v.y << 8;
        wp->position_fixed.z += wp->velocity.v.z << 8;
        func_80030150(&wp->position_fixed, &wp->position);
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
    }
    else
    {
        wp->flags_0 = 0;
        Close_SHL_WORK(wp);
    }
    if (wp->hit_BC & 0x2000000)
    {
        wp->hit_BC = 0;
        wp->routine_0++;
    }
    else
    {
        func_800341BC(&wp->position, wp->sprite.value_10, 0, 0xA000, wp->value_1, &wp->hit_BC, wp->kind_E | 0x8000000, 0, 0x80);
        wp->hit_BC = 0;
        hit        = func_80049C24(wp);
        if (hit)
        {
            wp->routine_0++;
        }
        if (!(wp->flags_F & 4))
        {
            func_80037738(hit, 0x28);
        }
    }
}

void stcom18_func_04C8(STCOM18_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        if (wp->flags_F & 1)
        {
            stcom18_func_0534(wp, effect);
        }
        else
        {
            stcom18_func_0574(wp, effect);
        }
    }
    wp->flags_0 = 0;
    Close_SHL_WORK(wp);
}

void stcom18_func_0534(STCOM18_WORK *wp, STCOM_EFFECT *effect)
{
    effect->flags_0         = 7;
    effect->kind_2          = 0x80;
    effect->variant_3       = 0x42;
    effect->sprite.position = wp->position;
}

void stcom18_func_0574(STCOM18_WORK *wp, STCOM_EFFECT *effect)
{
    effect->flags_0         = 3;
    effect->kind_2          = 0x83;
    effect->variant_3       = 0;
    effect->sprite.pos_8[0] = wp->position.x;
    effect->sprite.pos_8[1] = -1;
    effect->sprite.pos_8[2] = wp->position.z;
}
