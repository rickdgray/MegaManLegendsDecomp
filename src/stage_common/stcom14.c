#include "common.h"
#include "stage_common/stcom14.h"

// Shared stage code, linked into 6 stages: r3_st05, r3_st06, r3_st08, r3_st0b, r3_st10 and
// r3_st19. Each stage compiles this file against its own copy of the assembly (TARGET_ASM, set
// by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom14"

void stcom14_func_0000(STCOM_EFFECT *wp)
{
    if (wp->value_D == 0)
    {
        stcom14_D_0000[wp->variant_3](wp);
    }
    else
    {
        stcom14_D_0010[wp->variant_3](wp);
    }
}

void stcom14_func_006C(STCOM_EFFECT *wp)
{
    STCOM_EFFECT *puff;

    if (wp->routine_1 < 7)
    {
        if (!(wp->routine_1 & 3))
        {
            puff = func_80031618();
            if (puff != NULL)
            {
                puff->flags_0             = 3;
                puff->kind_2              = wp->kind_2;
                puff->variant_3           = wp->variant_3;
                puff->value_C             = wp->value_C;
                puff->value_D             = 1;
                puff->timer_E             = 8;
                puff->sprite.pos_8[2]     = wp->sprite.pos_8[2];
                puff->sprite.pos_8[0]     = wp->sprite.pos_8[0];
                puff->sprite.pos_8[1]     = wp->sprite.pos_8[1];
                puff->sprite.mode_0       = STCOM14_MODE;
                puff->sprite.color_4.word = STCOM14_COLOR;
                puff->sprite.value_E      = 0x20;
                puff->sprite.value_F      = 0;
                puff->sprite.value_10     = (rand() & 1) + 1;
            }
        }
        wp->routine_1 += rand() & 1;
    }
    else
    {
        func_80031988(wp);
    }
}

void stcom14_func_0164(STCOM_EFFECT *wp)
{
    if (wp->timer_E > 0)
    {
        if (wp->timer_E % 3 == 0 && wp->sprite.value_E < 0x80)
        {
            wp->sprite.value_E += 0x20;
        }
        wp->sprite.pos_8[0] += rand() & 1;
        wp->sprite.pos_8[2] += rand() & 1;
        if (!(wp->timer_E & 1))
        {
            wp->sprite.pos_8[1] -= 2 + (rand() & 1);
        }
        else
        {
            wp->sprite.pos_8[1] -= 1 + (rand() & 1);
        }
        if (!(wp->timer_E & 1))
        {
            wp->sprite.value_10++;
        }
        wp->sprite.color_4.word -= 0x20202;
        wp->timer_E--;
    }
    else
    {
        func_80031988(wp);
    }
}

void stcom14_func_02A0(STCOM_EFFECT *wp)
{
    STCOM_EFFECT *puff;

    if (wp->routine_1 < 0x30)
    {
        if (!(wp->routine_1 & 0xF))
        {
            puff = func_80031618();
            if (puff != NULL)
            {
                puff->flags_0             = 3;
                puff->kind_2              = wp->kind_2;
                puff->variant_3           = wp->variant_3;
                puff->value_C             = wp->value_C;
                puff->value_D             = 1;
                puff->timer_E             = 0x10;
                puff->sprite.pos_8[2]     = wp->sprite.pos_8[2] + (rand() & 3);
                puff->sprite.pos_8[0]     = wp->sprite.pos_8[0] + (rand() & 3);
                puff->sprite.pos_8[1]     = wp->sprite.pos_8[1] + (rand() & 3);
                puff->sprite.mode_0       = STCOM14_MODE;
                puff->sprite.color_4.word = STCOM14_COLOR;
                puff->sprite.value_E      = 0x20;
                puff->sprite.value_F      = 0;
                puff->sprite.value_10     = (rand() & 1) + 2;
            }
        }
        wp->routine_1 += rand() & 3;
    }
    else
    {
        func_80031988(wp);
    }
}

void stcom14_func_03C4(STCOM_EFFECT *wp)
{
    if (wp->timer_E > 0)
    {
        if (wp->timer_E % 6 == 0 && wp->sprite.value_E < 0x80)
        {
            wp->sprite.value_E += 0x20;
        }
        wp->sprite.pos_8[0] += rand() & 1;
        wp->sprite.pos_8[2] += rand() & 1;
        if (!(wp->timer_E & 1))
        {
            wp->sprite.pos_8[1] -= 2 + (rand() & 1);
        }
        else
        {
            wp->sprite.pos_8[1] -= 1 + (rand() & 1);
        }
        if (!(wp->timer_E & 1))
        {
            wp->sprite.value_10++;
        }
        wp->sprite.color_4.word -= 0x20202;
        wp->timer_E--;
    }
    else
    {
        func_80031988(wp);
    }
}

void stcom14_func_0504(STCOM_EFFECT *wp)
{
    STCOM_EFFECT *puff;

    if (wp->value_F == 1)
    {
        if (!(wp->routine_1 & 7))
        {
            puff = func_80031618();
            if (puff != NULL)
            {
                puff->flags_0             = 3;
                puff->kind_2              = wp->kind_2;
                puff->variant_3           = wp->variant_3;
                puff->value_C             = wp->value_C;
                puff->value_D             = 1;
                puff->timer_E             = 0x40 - (rand() & 0xF);
                puff->value_F             = wp->value_F;
                puff->sprite.pos_8[0]     = wp->sprite.pos_8[0] - (rand() & 0x7F);
                puff->sprite.pos_8[2]     = wp->sprite.pos_8[2] - (rand() & 0x7F);
                puff->sprite.pos_8[1]     = wp->sprite.pos_8[1];
                puff->sprite.mode_0       = STCOM14_MODE;
                puff->sprite.color_4.word = STCOM14_COLOR;
                puff->sprite.value_E      = 0x20;
                puff->sprite.value_F      = 0;
                puff->sprite.value_10     = (rand() & 0x3F) + 0xDC;
            }
        }
        wp->routine_1 += rand() & 3;
    }
}

void stcom14_func_062C(STCOM_EFFECT *wp)
{
    if (wp->timer_E > 0)
    {
        wp->sprite.pos_8[0] -= rand() & 7;
        wp->sprite.pos_8[2] -= rand() & 7;
        wp->sprite.pos_8[1] -= 10 + (rand() & 7);
        wp->timer_E--;
        wp->sprite.value_10 += 2;
        wp->sprite.color_4.word -= 0x10101;
    }
    else
    {
        func_80031988(wp);
    }
}

void stcom14_func_06DC(STCOM_EFFECT *wp)
{
    STCOM_EFFECT *puff;

    if (wp->routine_1 < 7)
    {
        if (!(wp->routine_1 & 3))
        {
            puff = func_80031618();
            if (puff != NULL)
            {
                puff->flags_0             = 3;
                puff->kind_2              = wp->kind_2;
                puff->variant_3           = wp->variant_3;
                puff->value_C             = wp->value_C;
                puff->value_D             = 1;
                puff->timer_E             = wp->timer_E - (rand() & 0xF);
                puff->value_F             = wp->value_F;
                puff->sprite.pos_8[0]     = wp->sprite.pos_8[0] - (rand() & 0x3F);
                puff->sprite.pos_8[2]     = wp->sprite.pos_8[2] - (rand() & 0x3F);
                puff->sprite.pos_8[1]     = wp->sprite.pos_8[1];
                puff->sprite.mode_0       = STCOM14_MODE;
                puff->sprite.color_4.word = STCOM14_COLOR;
                puff->sprite.value_E      = 0x20;
                puff->sprite.value_F      = 0;
                puff->sprite.value_10     = (rand() & 0x1F) + 0xA0;
            }
        }
        wp->routine_1 += rand() & 1;
    }
    else
    {
        func_80031988(wp);
    }
}

void stcom14_func_0808(STCOM_EFFECT *wp)
{
    if (wp->timer_E > 0)
    {
        wp->sprite.pos_8[0] -= rand() & 3;
        wp->sprite.pos_8[2] -= rand() & 3;
        wp->sprite.pos_8[1] -= wp->value_F + (rand() & 3);
        wp->timer_E--;
        wp->sprite.value_10 += 2;
        wp->sprite.color_4.word -= 0x10101;
    }
    else
    {
        func_80031988(wp);
    }
}
