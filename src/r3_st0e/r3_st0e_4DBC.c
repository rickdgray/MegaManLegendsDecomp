#include "common.h"
#include "st0e.h"

void func_80104DBC(STAGE_OBJ *wp)
{
    D_80110398[wp->routine_0](wp);
}

void func_80104DF8(ST0E_ACTOR *wp)
{
    wp->scale.v.x  = 0x200;
    wp->scale.v.y  = 0x200;
    wp->scale.v.z  = 0x200;
    wp->scale.v.pad = 0x4210;
    wp->rotation.x = 0;
    wp->flags_0 |= 2;
    wp->rotation.y   = (rand() & 0x1F) << 7;
    wp->rotation.z   = 0;
    wp->velocity.v.x = wp->velocity.v.y = wp->velocity.v.z = 0;
    wp->value_4C = wp->value_4E = wp->value_50 = 0;
    func_8002F9C4(wp, NULL);
    func_80036478(&wp->ctl, 9, -0x60);
    wp->data_78          = D_801103A4;
    wp->value_6E = wp->value_B0 = D_80098844[wp->kind_2]->life_8 * 16;
    wp->position.y       = -0x200;
    wp->value_74         = 1;
    wp->ctl.value_10     = 0;
    wp->ctl.hit_14       = 0;
    wp->ctl.hit.flags_0      = 0;
    wp->ctl.hit.value_4      = 0;
    wp->ctl.hit.value_8      = 0;
    wp->position_fixed.y = -0x2000000;
    func_800322A8(wp, 3, 0);
    wp->routine_0 = 1;
    func_801056B8(wp);
}

void func_80104F10(ST0E_ACTOR *wp)
{
    ST0E_ACTOR_CTL *ctl;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    ctl                     = &wp->ctl;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->value_80 >= 2500 * 2500 && !(wp->flags_6 & 0x80))
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        return;
    }
    func_801050A0(wp);
    ctl->value_10 = func_8003648C(ctl, wp);
    D_801103B0[wp->routine_1](wp);
    if (wp->routine_0 != 2)
    {
        if (wp->anim_AC != wp->anim_prev_AD)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
        func_80105148(wp);
        if (wp->value_6E != 0)
        {
            func_801051B0(wp);
        }
        if (wp->flags_0 & 2)
        {
            func_8002C8CC(wp, 0x40, 0x200, 0);
        }
    }
}

void func_801050A0(ST0E_ACTOR *wp)
{
    uint32 hit;
    sint32 damage;
    if (wp->value_6E != 0)
    {
        hit = wp->ctl.hit.flags_0;
        if (hit & 0x38000000)
        {
            damage = hit & 0xFFFFFF;
            if (damage != 0)
            {
                wp->value_6E -= damage;
                Sound_call2(0xA0, &wp->position);
                wp->scale.v.pad = 0x7FFF;
                if (wp->value_6E <= 0)
                {
                    wp->anim_AC      = 4;
                    wp->velocity.v.y = -0x280;
                    wp->value_6E     = 0;
                    wp->velocity.v.x = 0;
                    wp->value_4E     = 0x40;
                    wp->value_74     = 1;
                    wp->routine_1    = 4;
                    wp->routine_2    = 0;
                }
            }
        }
    }
}

void func_80105148(ST0E_ACTOR *wp)
{
    wp->ctl.hit_14 = 0;
    if (func_8004B414(wp) & 0xF00)
    {
        wp->ctl.hit_14 |= 1;
    }
    if (wp->value_74 == 0)
    {
        wp->ctl.hit_14 |= 2;
    }
}

void func_801051B0(ST0E_ACTOR *wp)
{
    wp->ctl.hit.flags_0 = 0;
    wp->ctl.pos_18  = wp->position;
    func_800341BC(&wp->ctl.pos_18, 0x40, 0, 0x8000, wp->value_1, &wp->ctl.hit,
                  wp->ctl.hit.value_8 | 0x4000000, 0, 0);
}

void func_80105228(ST0E_ACTOR *wp)
{
    ST0E_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.value_10 != 0)
    {
        if (wp->routine_1 == 1)
        {
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x180;
            wp->velocity.v.y = -0xF0;
            wp->value_4E     = 0;
            Sound_call2(0x158, &wp->position);
            wp->routine_2 = 0;
        }
        else
        {
            wp->velocity.v.x    = 0x180;
            wp->velocity.v.y    = 0;
            wp->value_4E        = 0;
            wp->ctl.hit.value_8 = D_80098844[wp->kind_2]->value_A;
            wp->routine_2       = 1;
        }
        ctl->hit.timer_10 = 0x3C;
        wp->routine_1     = 3;
    }
}

void func_801052EC(STAGE_OBJ *wp)
{
    func_8002FEA4(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer,
                  (sint16)wp->value_48.words.fraction);
    func_8010576C(wp);
    if (wp->value_A7 != 0)
    {
        func_8010571C(wp);
    }
}

void func_80105344(ST0E_ACTOR *wp)
{
    if (--wp->ctl.hit.timer_E == 0)
    {
        func_80105738(wp);
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
        if (wp->ctl.hit.timer_E < 0x41)
        {
            func_80105228(wp);
        }
    }
}

void func_801053AC(STAGE_OBJ *wp)
{
    func_8002FEA4(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer,
                  (sint16)wp->value_48.words.fraction);
    func_80105798(wp);
    if (wp->routine_2 == 0)
    {
        func_80105414(wp);
        return;
    }
    func_80105490(wp);
}

void func_80105414(ST0E_ACTOR *wp)
{
    if (wp->value_A7 != 0)
    {
        wp->anim_AC = 2;
        if (wp->routine_1 == 3)
        {
            wp->ctl.hit.value_8 = D_80098844[wp->kind_2]->value_A;
        }
        wp->velocity.v.y = 0;
        wp->routine_2++;
    }
    else if (wp->value_A4 == 9)
    {
        wp->velocity.v.y = 0xF0;
    }
}

void func_80105490(ST0E_ACTOR *wp)
{
    if ((wp->ctl.hit_14 & 1) || --wp->ctl.hit.timer_10 == 0)
    {
        func_801056B8(wp);
    }
    else
    {
        func_80105228(wp);
    }
}

void func_801054F0(STAGE_OBJ *wp)
{
    wp->rotation.y = (wp->rotation.y +
                      func_80031BEC(&wp->position, &Player_work.position, wp->rotation.y, 0x60)) &
                     0xFFF;
    func_8002FEA4(wp, (sint16)wp->value_44.words.fraction, wp->value_44.words.integer,
                  (sint16)wp->value_48.words.fraction);
    func_80105798(wp);
    if (wp->routine_2 == 0)
    {
        func_80105414(wp);
        return;
    }
    func_80105580(wp);
}

void func_80105580(ST0E_ACTOR *wp)
{
    sint32 done;

    done = wp->ctl.hit_14 & 1;
    if (wp->ctl.hit.flags_0 & 0x2000000)
    {
        done = 1;
    }
    if (wp->ctl.hit.flags_0 & 0x4000000)
    {
        done = 1;
    }
    if (--wp->ctl.hit.timer_10 == 0)
    {
        done = 1;
    }
    if (done)
    {
        wp->ctl.hit.value_8 = 0;
        func_801056B8(wp);
    }
}

void func_801055F8(ST0E_ACTOR *wp)
{
    STCOM_EFFECT *effect;

    if (wp->ctl.hit_14 != 0)
    {
        effect = func_80031618();
        if (effect != NULL)
        {
            effect->flags_0         = 5;
            effect->kind_2          = 0x80;
            effect->variant_3       = 0;
            effect->sprite.position = wp->position;
        }
        func_80047148(wp, &wp->position, effect);
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
    }
    else
    {
        func_8002FEA4(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
        wp->velocity.v.y += wp->value_4E;
    }
}

void func_801056B8(ST0E_ACTOR *wp)
{
    wp->anim_AC      = 3;
    wp->velocity.v.x = 0x100;
    wp->velocity.v.y = -0xF0;
    wp->value_4E     = 0;
    wp->ctl.hit.value_C  = D_801103C4[rand() & 3];
    wp->routine_1    = 0;
    wp->routine_2    = 0;
}

void func_8010571C(ST0E_ACTOR *wp)
{
    wp->ctl.hit.timer_E = 0x80;
    wp->anim_AC     = 0;
    wp->routine_1   = 1;
    wp->routine_2   = 0;
}

void func_80105738(ST0E_ACTOR *wp)
{
    wp->anim_AC      = 1;
    wp->velocity.v.y = -0xF0;
    wp->ctl.hit.timer_10 = 0x3C;
    wp->value_4E     = 0;
    wp->routine_1    = 2;
    wp->routine_2    = 0;
    wp->velocity.v.x = wp->ctl.hit.value_C;
}

void func_8010576C(STAGE_OBJ *wp)
{
    if (wp->position.y < -0x32C)
    {
        wp->position.y             = -0x32C;
        wp->position_fixed.v.y     = -0x032C0000;
        wp->value_44.words.integer = 0;
    }
}

void func_80105798(STAGE_OBJ *wp)
{
    if (wp->position.y >= -0x1FF)
    {
        wp->position.y             = -0x200;
        wp->position_fixed.v.y     = -0x02000000;
        wp->value_44.words.integer = 0;
    }
}

void func_801057C4(STAGE_OBJ *wp)
{
    D_80110504--;
    func_80031824(wp);
}

void func_801057F8(ST0E_PROP *wp)
{
    STCOM_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    m                       = &wp->matrix;
    wp->ctl.random_2        = rand();
    D_801103CC[wp->routine_0](wp);
    RotMatrixYXZ(&wp->rotation.v, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x32 - (wp->rotation.v.z >> 6), 0x2C0 - (wp->rotation.v.z >> 4) * 3, 0);
    }
    if ((wp->flags_0 & 1) && (wp->ctl.flags_0 & 2))
    {
        wp->position.y -= 0x20;
        wp->position_fixed.y = wp->position.y << 16;
        func_800341BC(&wp->position, 0x20, 0, 0x8000, wp->value_1, &wp->ctl.hit_8, 0x4880000, 0,
                      0x80);
        wp->position.y += 0x20;
        wp->position_fixed.y = wp->position.y << 16;
    }
}

void func_801059A8(ST0E_PROP *wp)
{
    STCOM_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    wp->pos_AC            = wp->position;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->spin_64.w         = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->rotation.v.x      = 0x400;
    wp->rotation.v.z      = 0;
    wp->flags_0 |= 6;
    wp->rotation.v.y = (wp->param_C << 9) & 0xE00;
    func_8002F9C4(wp, NULL);
    m                = &wp->matrix;
    wp->ctl.flags_0  = 0;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    RotMatrixYXZ(&wp->rotation.v, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    wp->data_78               = D_801103F0;
    wp->value_6E              = 0x400;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 1;
    *(uint16 *)&wp->routine_2 = 0;
    wp->color_B4              = 0x808080;
}

void func_80105AB0(ST0E_PROP *wp)
{
    D_801103D8[wp->routine_1](wp);
    wp->pos_AC = wp->position;
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
}

void func_80105B40(STAGE_OBJ *wp)
{
    func_800318D8(wp);
}

void func_80105B60(ST0E_PROP *wp)
{
    STCOM_PL_WORK *pl;
    ST0E_PROP_CTL *ctl;
    sint32 dx;
    sint32 dy;
    sint32 dz;

    pl  = &Player_work;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 0x3C;
            wp->flags_0 |= 2;
            wp->routine_2++;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->velocity.v.y = 0x10;
                wp->routine_2++;
                wp->accel.y  = wp->position.y;
                ctl->timer_4 = 0;
                goto start2;
            }
            wp->position.y -= 2;
            wp->position_fixed.y = wp->velocity.v.y << 12;
            break;
        case 2:
            // The loop note keeps start2 apart from the case label, so jump.c
            // doesn't swap case 1's arms (retail keeps the timer-out block first).
            do
            {
            start2:
                if (ctl->timer_4 == 0x40)
                {
                    ctl->timer_4 = 0;
                }
                if (wp->rotation.v.x != 0)
                {
                    wp->rotation.v.x = (wp->rotation.v.x - 0x10) & 0xFFF;
                }
                wp->rotation.v.y = (wp->rotation.v.y + 0x20) & 0xFFF;
                if (wp->rotation.v.z != 0x400)
                {
                    wp->rotation.v.z = (wp->rotation.v.z + 0x10) & 0xFFF;
                }
                wp->position.y = wp->accel.y + (wp->velocity.v.y * D_800BBCF8[ctl->timer_4] >> 12);
                wp->position_fixed.y = wp->velocity.v.y << 12;
                ctl->timer_4         = (ctl->timer_4 + 1) & 0x3F;
            } while (0);
            break;
    }
    dx = wp->position.x - pl->position.x;
    dy = wp->position.y - pl->position.y;
    dz = wp->position.z - pl->position.z;
    if (ST0E_ABS(dy) < 0x80 && dx * dx + dz * dz < 0x400)
    {
        Sound_call(5, 0, 0);
        wp->routine_1             = 4;
        *(uint16 *)&wp->routine_2 = 0;
    }
}

void func_80105D6C(uint8 *arg0)
{
    *arg0 &= 0xFD;
}

void func_80105D80(uint8 *arg0)
{
    *arg0 |= 2;
}

void func_80105D94(ST0E_PROP *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->spin_64.h[1] = 0x400;
            wp->flags_0 |= 2;
            // fall through
        case 1:
            wp->velocity.v.x += wp->accel.x;
            wp->velocity.v.y += wp->accel.y;
            wp->velocity.v.z += wp->accel.z;
            wp->position_fixed.x += wp->velocity.v.x << 8;
            wp->position_fixed.y += wp->velocity.v.y << 8;
            wp->position_fixed.z += wp->velocity.v.z << 8;
            func_80030150(&wp->position_fixed, &wp->position);
            if (func_8004B414(wp) & 0x1000)
            {
                if (wp->spin_64.h[1] == 0)
                {
                    wp->ctl.flags_0 |= 1;
                }
                wp->accel.x = 0;
                wp->accel.z = 0;
                wp->velocity.v.x >>= 1;
                wp->velocity.v.z >>= 1;
                wp->rotation.v.y = (wp->rotation.v.y + wp->spin_64.h[1]) & 0xFFF;
                wp->spin_64.h[1] -= 0x20;
                wp->ctl.flags_0 |= 2;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_80105EF0(ST0E_PROP *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.y = -0x32;
            wp->accel.y      = 4;
            wp->flags_0 |= 2;
            // fall through
        case 1:
            wp->position.y += wp->velocity.v.y;
            wp->position_fixed.y = wp->position.y << 16;
            wp->velocity.v.y += wp->accel.y;
            if (func_8004B414(wp) & 0x1000)
            {
                wp->routine_2 = 2;
                wp->ctl.flags_0 |= 1;
            }
            break;
        case 0xFF:
            break;
    }
}

void func_80105FA0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800318D8(wp);
        Sce_flag_on(0x611);
        wp->routine_2++;
    }
}
