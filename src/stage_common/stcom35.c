#include "common.h"
#include "stage_common/stcom35.h"

// Shared stage code, linked into 5 stages: r3_st00, r3_st0b, r3_st0c, r3_st12 and r3_st19.
// Each stage compiles this file against its own copy of the assembly (TARGET_ASM, set by
// tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom35"

// An emitter (value_D 0) that puts out a glowing puff (value_D 1) every 16 frames for 16 frames.
void stcom35_func_0000(STCOM_EFFECT *wp)
{
    if (wp->value_D == 0)
    {
        stcom35_D_0008[wp->variant_3](wp);
    }
    else
    {
        stcom35_D_0000[wp->routine_0](wp);
    }
}

void stcom35_func_006C(STCOM_EFFECT *wp)
{
    STCOM_EFFECT *fx;

    if (!(wp->timer_B & 0xF))
    {
        fx                  = func_80031618();
        fx->flags_0         = 3;
        fx->kind_2          = wp->value_C;
        fx->variant_3       = wp->variant_3;
        fx->value_C         = wp->value_C;
        fx->value_D         = 1;
        fx->timer_E         = wp->timer_E;
        fx->sprite.pos_8[0] = wp->sprite.pos_8[0];
        fx->sprite.pos_8[1] = wp->sprite.pos_8[1];
        fx->sprite.pos_8[2] = wp->sprite.pos_8[2];
        if (fx->timer_E == 7)
        {
            fx->sprite.mode_0 = 0x3D48000E;
        }
        else
        {
            fx->sprite.mode_0 = 0x3D48002E;
        }
        fx->sprite.color_4.word = 0x2E000000;
        fx->sprite.value_E      = 0xA0;
        fx->sprite.value_F      = 0x60;
        fx->sprite.value_10     = 0x10;
        if (fx->variant_3 == 0)
        {
            fx->timer_B = 0x4E;
        }
        else
        {
            fx->timer_B = 0xF0;
        }
    }
    if (wp->timer_B >= 0x10)
    {
        func_80031988(wp);
    }
    wp->timer_B++;
}

// A puff: brightens, holds, then fades.
void stcom35_func_0190(STCOM_EFFECT *wp)
{
    switch (wp->variant_3)
    {
        case 0:
            if (wp->timer_B >= 0x3F)
            {
                wp->sprite.color_4.word += stcom35_D_0010[wp->timer_E] * 8;
            }
            else if (wp->timer_B <= 0x20)
            {
                wp->sprite.color_4.word -= stcom35_D_0010[wp->timer_E] * 4;
            }
            break;
        case 1:
            if (wp->timer_B >= 0xE1)
            {
                wp->sprite.color_4.word += stcom35_D_0010[wp->timer_E] * 8;
            }
            break;
    }
    if (--wp->timer_B == 0)
    {
        wp->routine_0++;
    }
}

void stcom35_func_0264(STCOM_EFFECT *wp)
{
    func_80031988(wp);
}
