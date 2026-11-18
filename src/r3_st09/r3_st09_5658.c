#include "common.h"
#include "st09.h"

void func_80105658(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_FIXED_VECTOR *scale;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_8011DEB0[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (ctl->flags_0 & 0x20)
    {
        // The joint matrices at +0x208, +0x228 and +0x248, scaled by the vector at the block's +0x34.
        scale = &ST09_STCOM15_SCALE(ctl);
        ScaleMatrix((STCOM_MATRIX *)&wp->joints_180[0x11], scale);
        ScaleMatrix((STCOM_MATRIX *)&wp->joints_180[0x15], scale);
        ScaleMatrix((STCOM_MATRIX *)&wp->joints_180[0x19], scale);
    }
    if (wp->flags_0 & 2)
    {
        wp->position.y += ctl->turn_44;
        wp->position_fixed.y = wp->position.y << 16;
        func_8002C8CC(wp, 0x30, 0x200, 0);
        wp->position.y -= ctl->turn_44;
        wp->position_fixed.y = wp->position.y << 16;
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 4))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0x30, 0, 0x8000, wp->value_1, &ctl->hit_14,
                      ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_80105870(STAGE_STCOM15_WORK_348 *wp)
{
    sint32 life;

    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->flags_0 |= 2;
    D_8011E948[wp->param_D * 2] = *(uint8 *)0x1F800000;
    D_8011E949[wp->param_D * 2] = 0;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0]           = 0x02000200;
    wp->scale.words[1]           = 0x200;
    *(uint32 *)&wp->ctl.timer_38 = 1;
    wp->ctl.hit_14               = 0;
    wp->ctl.value_18             = 0;
    *(uint32 *)&wp->ctl.timer_34 = 0x1000;
    wp->ctl.flags_0              = 0xEE;
    *(uint32 *)&wp->ctl.u_3C     = 0x1000;
    *(uint32 *)&wp->ctl.timer_4  = 0;
    *(uint32 *)&wp->ctl.value_8  = 0;
    func_80036478(wp->ctl.track_24, D_80098844[wp->kind_2]->value_F, -0x60);
    life                      = D_80098844[wp->kind_2]->life_8;
    wp->data_78               = D_8011DEE4;
    wp->data_10               = NULL;
    wp->life_6E               = life;
    wp->life_max_B0           = life;
    wp->life_prev_B2          = life;
    wp->position.y            = func_80048E6C(wp) + 0x32;
    wp->ctl.turn_44           = -0x32;
    wp->routine_0             = 1;
    wp->routine_1             = 1;
    *(uint16 *)&wp->routine_2 = 0;
    wp->position_fixed.y      = wp->position.y << 16;
    func_800322A8(wp, 0xC, 0);
    wp->scale.v.pad = 0x4210;
}

void func_801059D4(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    uint8 frame;
    sint32 i;

    ctl = &wp->ctl;
    if ((ctl->flags_0 & 0x100) && func_8003648C(wp->ctl.track_24, wp) != 0)
    {
        ctl->flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 2)
    {
        func_80106D1C(wp);
    }
    if (ctl->flags_0 & 0x40)
    {
        if (wp->routine_1 >= 2 && wp->routine_1 != 6 && wp->value_80 <= 0xAFC8)
        {
            wp->routine_1             = 5;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->flags_0 &= ~0xC0;
            D_8011E949[wp->param_D * 2] = 0x96;
        }
    }
    if ((ctl->flags_0 & 0x80) && D_8011E949[wp->param_D * 2] != 0)
    {
        if (wp->routine_1 >= 2)
        {
            wp->routine_1             = 7;
            *(uint16 *)&wp->routine_2 = 0;
        }
        ctl->flags_0 &= ~0x80;
    }
    D_8011DEBC[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 1:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 7;
                }
                else
                {
                    wp->routine_1 = 0;
                }
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 4:
            case 5:
            case 8:
                func_80047148(wp, &wp->joints_180[0]);
                func_80031824(wp);
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 6:
            case 9:
                wp->routine_1             = 7;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            default:
                if (D_8011E949[wp->param_D * 2] != 0 || (ctl->flags_0 & 0x10))
                {
                    wp->routine_1 = 7;
                }
                else
                {
                    func_80106C44((ST09_ACTOR *)wp);
                }
                *(uint16 *)&wp->routine_2 = 0;
                break;
        }
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    frame = *(uint8 *)0x1F800000;
    i     = wp->param_D * 2;
    if (D_8011E948[i] != frame && D_8011E949[i] != 0)
    {
        D_8011E948[i] = frame;
        i             = wp->param_D * 2;
        D_8011E949[i] = D_8011E949[i] - 1;
    }
    if (ctl->flags_0 & 0x200)
    {
        if (ctl->level_6++ & 3)
        {
            *((uint8 *)wp + 0x108) = 5; // a byte past the named fields
            wp->scale.v.pad        = 0x1F;
            return;
        }
        *((uint8 *)wp + 0x108) = 6;
    }
}

void func_80105D20(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80105D40(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0xB;
            ctl->value_8  = 0;
            ctl->timer_4  = 0xB;
            ctl->flags_0 &= ~8;
            Sound_call2(0xBC, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2             = 2;
            ctl->timer_4              = 4;
            ST09_STCOM15_SCALE(ctl).y = 0x1000;
            ctl->flags_0 |= 0x20;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                wp->position.y += D_8011DEF8[ctl->timer_4];
                wp->position_fixed.y = wp->position.y << 16;
                ctl->turn_44 -= D_8011DEF8[ctl->timer_4];
                ST09_STCOM15_SCALE(ctl).y = D_8011DEF0[ctl->timer_4];
                break;
            }
            wp->routine_2 = 3;
            ctl->timer_4  = 3;
            Sound_call2(0xBB, &wp->position);
            // fall through
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                wp->position.y += 0x11;
                wp->position_fixed.y = wp->position.y << 16;
                ctl->turn_44 -= 0x11;
                ST09_STCOM15_SCALE(ctl).y -= 0x555;
                break;
            }
            wp->routine_2             = 4;
            *((uint8 *)wp + 0x108)    = 4; // a byte past the named fields
            ST09_STCOM15_SCALE(ctl).y = 1;
            ctl->timer_4              = 0;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                wp->position.y       = func_80048E6C(wp) + 0x32;
                wp->position_fixed.y = wp->position.y << 16;
                ctl->turn_44         = -0x32;
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80105F58(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            ctl->value_8 = 0;
            ctl->flags_0 = (ctl->flags_0 & ~8) | 0x400;
            if (D_8011E949[wp->param_D * 2] == 0 && wp->value_80 > 0x20000)
            {
                break;
            }
            wp->routine_2          = 1;
            *((uint8 *)wp + 0x108) = 5; // a byte past the named fields
            ctl->timer_4           = 3;
            ctl->flags_0 |= 0x100;
            func_80036470(ctl->track_24);
            Sound_call2(0xBB, &wp->position);
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->position.y -= 0x11;
                wp->position_fixed.y = wp->position.y << 16;
                ctl->turn_44 += 0x11;
                ST09_STCOM15_SCALE(ctl).y += 0x555;
                break;
            }
            wp->routine_2             = 2;
            *((uint8 *)wp + 0x108)    = 6;
            ctl->timer_4              = 4;
            ST09_STCOM15_SCALE(ctl).y = 0x1000;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                wp->position.y += D_8011DF04[ctl->timer_4];
                wp->position_fixed.y = wp->position.y << 16;
                ctl->turn_44 -= D_8011DF04[ctl->timer_4];
                ST09_STCOM15_SCALE(ctl).y = D_8011DEFC[ctl->timer_4];
                break;
            }
            wp->routine_2 = 3;
            ctl->timer_4  = 5;
            // fall through
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 4;
            ctl->timer_4  = 0xB;
            wp->anim_AC   = 0;
            Sound_call2(0xBC, &wp->position);
            ctl->flags_0 = (ctl->flags_0 | 8) & ~0x420;
            // fall through
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y =
                    (wp->rotation.y +
                     func_80031BEC(&wp->position, &Player_work.position, wp->rotation.y, 0x80)) &
                    0xFFF;
                break;
            }
            wp->routine_2        = 5;
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            ctl->turn_44         = 0;
            ctl->timer_4         = 0x3C;
            // fall through
        case 5:
            if (--ctl->timer_4 < 0 || (ctl->flags_0 & 0x10))
            {
                ctl->flags_0 = (ctl->flags_0 | 1) & ~0x100;
            }
            break;
    }
}

void func_80106238(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.timer_4 = 0x40;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            func_8002FEA4(wp, 0x48, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            ctl->turn_44         = 0;
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21) ||
                (hit & 0xF00))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            break;
    }
}

void func_801063A4(STAGE_ACTOR *wp)
{
    STAGE_ACTOR_CTL *ctl;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 2;
            wp->ctl.timer_4 = 4;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_80106424(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 timer;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 3;
            wp->velocity.v.x = 0x100;
            wp->ctl.timer_4  = 0xC;
            wp->ctl.value_8  = 0;
            wp->ctl.flags_0  = (wp->ctl.flags_0 & ~0xC2) | 0x200;
            wp->rotation.y &= 0xFFF;
            // fall through
        case 1:
            timer            = ctl->timer_4 - 1;
            ctl->timer_4     = timer;
            wp->velocity.v.y = (5 - timer) << 6;
            func_8002FEA4(wp, wp->velocity.v.x, (sint16)((5 - timer) << 6), 0);
            if (func_8004B414(wp) != 0)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 2;
                    fx->sprite.position = wp->value_180;
                }
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_80106550(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            ctl->timer_4  = 0x3C;
            ctl->value_8  = 0;
            ctl->flags_0 |= 0x200;
            // fall through
        case 1:
            func_8005D4C0();
            if (wp->value_A6 == 1)
            {
                Sound_call2(0xBD, &wp->position);
            }
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &Player_work.position,
                                                             wp->rotation.y, 0x20)) &
                             0xFFF;
            func_8002FEA4(wp, 0x80, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            ctl->turn_44         = 0;
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21) ||
                (hit & 0xF00))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 >= 0 && !(ctl->hit_14 & 0x2000000))
            {
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 4;
            ctl->timer_4  = 0xA;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 2;
                    fx->sprite.position = wp->joints_180[0];
                }
                ctl->flags_0 |= 9;
                break;
            }
            if (wp->value_A6 == 1)
            {
                Sound_call2(0xBE, &wp->position);
            }
            func_8002FEA4(wp, 0, 0x200, 0);
            func_8004B414(wp);
            break;
    }
}

void func_801067E4(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    sint32 timer;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 6;
            wp->velocity.v.x = 0x100;
            wp->ctl.timer_4  = 0xC;
            wp->ctl.value_8  = 0;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            timer            = ctl->timer_4 - 1;
            ctl->timer_4     = timer;
            wp->velocity.v.y = (7 - timer) << 6;
            func_8002FEA4(wp, wp->velocity.v.x, (sint16)((7 - timer) << 6), 0);
            if (!(func_8004B414(wp) & 0x1000))
            {
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 7;
            ctl->timer_4  = 5;
            // fall through
        case 2:
            if ((sint16)--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_80106904(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.timer_4 = 0x78;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            func_8005D4C0();
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &Player_work.position,
                                                             wp->rotation.y, 0x20)) &
                             0xFFF;
            func_8002FEA4(wp, 0x80, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            ctl->turn_44         = 0;
            if (wp->position.y - wp->position_prev.y > 0x20)
            {
                wp->routine_1             = 6;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                break;
            }
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21) ||
                (hit & 0xF00))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 0x81;
            }
            break;
    }
}

void func_80106AFC(ST09_ACTOR *wp)
{
    STCOM_EFFECT *fx;

    wp->ctl.value_8 = 0;
    fx              = func_80031618();
    if (fx != NULL)
    {
        fx->flags_0         = 5;
        fx->kind_2          = 0x80;
        fx->variant_3       = 2;
        fx->sprite.position = wp->value_180;
    }
    wp->ctl.flags_0 |= 1;
}

void func_80106B78(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    sint16 turn;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            ctl->value_8  = 0;
            // fall through
        case 1:
            turn = func_80031BEC(&wp->position, &Player_work.position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (((turn < 0) ? -turn : turn) < 0x20)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

sint32 func_80106C44(ST09_ACTOR *wp)
{
    sint16 sum;
    sint16 i;

    sum = 0;
    for (i = 0; i < 4; i++)
    {
        sum += D_8011DF08[i];
        if ((wp->ctl.value_2 & 0xF) < sum)
        {
            break;
        }
    }
    wp->routine_1 = 2;
    switch (i)
    {
        case 0:
            wp->routine_1 = 0;
            break;
        case 1:
            wp->spin_66 = 0;
            // fall through
        case 2:
            wp->spin_66 = 0x10;
            break;
        case 3:
            wp->spin_66 = -0x10;
            break;
    }
    return 1;
}

sint32 func_80106D1C(STAGE_STCOM15_WORK_348 *wp)
{
    STCOM_SVECTOR origin = {0, 0, 0, 0};
    STAGE_STCOM15_CTL *ctl;
    uint32 damage;
    sint16 turn;
    sint16 id;

    damage = wp->ctl.hit_14 & 0xFFFFFF;
    ctl    = &wp->ctl;
    if (damage != 0)
    {
        if (!(wp->ctl.flags_0 & 0x400) && (wp->ctl.hit_14 & 0x38000000))
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                wp->ctl.flags_0 = (wp->ctl.flags_0 & ~2) | 8;
                damage          = D_80098844[wp->kind_2]->limit_9;
            }
            if (wp->ctl.flags_0 & 8)
            {
                wp->ctl.timer_A += damage;
                if (!(wp->ctl.flags_0 & 0x200) && !(wp->ctl.hit_14 & 0x20000000) &&
                    wp->ctl.timer_A < D_80098844[wp->kind_2]->limit_9)
                {
                    Sound_call2(0xA0, &wp->position);
                    if (wp->routine_1 != 3)
                    {
                        wp->routine_1             = 3;
                        *(uint16 *)&wp->routine_2 = 0;
                    }
                }
                else
                {
                    Sound_call2(0xA2, &wp->position);
                    if (ctl->target_1C.pad & 1)
                    {
                        turn = func_80031198(&wp->position, &ctl->target_1C);
                        if (((wp->rotation.y - turn + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->rotation.y = turn;
                        }
                        else
                        {
                            wp->rotation.y = (turn + 0x800) & 0xFFF;
                        }
                    }
                    else
                    {
                        turn = func_80031198(&origin, &ctl->target_1C);
                        if (((turn - wp->rotation.y + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->rotation.y = (turn + 0x800) & 0xFFF;
                        }
                        else
                        {
                            wp->rotation.y = turn;
                        }
                    }
                    wp->routine_1             = 4;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->timer_A              = 0;
                }
            }
            else
            {
                id = 0xA2;
                if (!(wp->ctl.flags_0 & 0x200) && !(wp->ctl.hit_14 & 0x20000000) &&
                    wp->ctl.timer_A < D_80098844[wp->kind_2]->limit_9)
                {
                    id = 0xA0;
                }
                Sound_call2(id, &wp->position);
            }
            wp->scale.v.pad        = 0x7FFF;
            *((uint8 *)wp + 0x108) = 6; // a byte past the named fields
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

// From r3_st1d (func_80107788).
void func_80106FCC(ST09_VIEW_B *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_SVECTOR *save;
    sint16 i;
    sint16 rot;

    ext                     = &wp->ext;
    wp->value_AD            = wp->value_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_15C.h[1]          = 0x4210;
    wp->ext.u_2.h           = rand();
    D_8011DF0C[wp->routine_0](wp);
    func_80017684(&wp->ext.u_34, (void *)0x1F800120, 6);
    func_8003346C(wp);
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ext->flags_0 & 4))
    {
        ext->pos_C = wp->vec_180[1];
        func_800341BC(&ext->pos_C, 0x50, 0, 0x8000, wp->value_1, &ext->value_14,
                      ext->value_8 | 0x4880000, 0x800000, 0);
    }
    if ((wp->flags_0 & 1) && !((uint8)wp->value_F & 0x40))
    {
        if (!((uint8)wp->value_F & 2))
        {
            func_80100DF4(ext->u_4C.p);
        }
        if ((uint8)wp->value_F & 1)
        {
            if (!((uint8)wp->value_F & 4))
            {
                ((STAGE_OBJ *)ext->effect_50)->routine_1 = 0;
                ((STAGE_OBJ *)ext->piece_54)->routine_1  = 0;
            }
            wp->value_F &= ~1;
        }
        for (i = 0, save = D_8011E950; i < 2; i++)
        {
            *save          = wp->position;
            *D_8011E958    = wp->position_fixed;
            rot            = wp->rotation.y;
            wp->rotation.y = (ext->u_44.h[1] + rot) & 0xFFF;
            func_8002FEA4(wp, D_8011DF30[i], -0x8A0, 0);
            ((STAGE_FX **)&ext->effect_50)[i]->x_1C = wp->position.x;
            ((STAGE_FX **)&ext->effect_50)[i]->y_1E = wp->position.y;
            ((STAGE_FX **)&ext->effect_50)[i]->z_20 = wp->position.z;
            wp->position                            = *save;
            wp->position_fixed                      = *D_8011E958;
            wp->rotation.y                          = rot;
        }
    }
    ext->value_14 = 0;
}

// From r3_st1d (func_80107AF0).
void func_80107334(ST09_VIEW_B *wp)
{
    STAGE_ACTOR_EXT *ext;
    STAGE_OBJ *fx;
    STAGE_OBJ *obj;
    ST09_SPAWN_REC *rec;
    sint16 ground;
    sint16 life;
    sint16 i;

    ext = &wp->ext;
    if (!((uint8)wp->value_F & 0x40))
    {
        for (i = 0; i < 4; i++)
        {
            fx                                 = (STAGE_OBJ *)func_80031618();
            ((STAGE_OBJ **)&ext->effect_50)[i] = fx;
            if (fx != NULL)
            {
                ((STAGE_OBJ **)&ext->effect_50)[i]->flags_0      = 9;
                ((STAGE_OBJ **)&ext->effect_50)[i]->kind_2       = 0xF;
                ((STAGE_OBJ **)&ext->effect_50)[i]->variant_3    = 1;
                ((STAGE_OBJ **)&ext->effect_50)[i]->u_C.b.byte_C = wp->variant_3 >> 4;
            }
            else
            {
                func_80031824(wp);
                // Frees the effects taken so far only when the first one failed (then [-1]).
                while (i == 0)
                {
                    i--;
                    func_80031988(((STAGE_OBJ **)&ext->effect_50)[i]);
                }
                return;
            }
        }
        wp->value_D = ((STAGE_OBJ *)ext->u_58.obj)->value_1;
        wp->value_E = ((STAGE_OBJ *)ext->u_5C.p)->value_1;
        obj         = func_80031418();
        ext->u_4C.p = obj;
        if (obj != NULL)
        {
            rec                                         = &D_8011C9A0[wp->value_C];
            ((STAGE_OBJ *)ext->u_4C.p)->flags_0         = rec->flags_0;
            ((STAGE_OBJ *)ext->u_4C.p)->kind_2          = rec->kind_2;
            ((STAGE_OBJ *)ext->u_4C.p)->variant_3       = rec->variant_3;
            ((STAGE_OBJ *)ext->u_4C.p)->value_4         = rec->value_4;
            ((STAGE_OBJ *)ext->u_4C.p)->reserved05      = rec->value_5;
            *(sint32 *)&((STAGE_OBJ *)ext->u_4C.p)->u_C = rec->value_8;
            ((STAGE_OBJ *)ext->u_4C.p)->position = ((STAGE_OBJ *)ext->u_4C.p)->position_prev =
                rec->position;
            ((STAGE_OBJ *)ext->u_4C.p)->position_fixed.v.x =
                ((STAGE_OBJ *)ext->u_4C.p)->position_fixed_prev.x =
                    ((STAGE_OBJ *)ext->u_4C.p)->position.x << 16;
            ((STAGE_OBJ *)ext->u_4C.p)->position_fixed.v.y =
                ((STAGE_OBJ *)ext->u_4C.p)->position_fixed_prev.y =
                    ((STAGE_OBJ *)ext->u_4C.p)->position.y << 16;
            ((STAGE_OBJ *)ext->u_4C.p)->position_fixed.v.z =
                ((STAGE_OBJ *)ext->u_4C.p)->position_fixed_prev.z =
                    ((STAGE_OBJ *)ext->u_4C.p)->position.z << 16;
            ((STAGE_OBJ *)ext->u_4C.p)->rotation.x = ((STAGE_OBJ *)ext->u_4C.p)->rotation_prev.x =
                0;
            ((STAGE_OBJ *)ext->u_4C.p)->rotation.y = ((STAGE_OBJ *)ext->u_4C.p)->rotation_prev.y =
                rec->rotation_7 << 4;
            ((STAGE_OBJ *)ext->u_4C.p)->rotation.z = ((STAGE_OBJ *)ext->u_4C.p)->rotation_prev.z =
                0;
            ((STAGE_OBJ *)ext->u_4C.p)->u_C.b.byte_D = wp->value_1;
        }
        else
        {
            func_80031824(wp);
            for (i = 0; i < 4; i++)
            {
                func_80031988(((STAGE_OBJ **)&ext->effect_50)[i]);
            }
            return;
        }
    }
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->u_64.w[0]  = 0;
    wp->flags_0 |= 2;
    func_8002F9C4(wp, NULL);
    wp->value_158            = 0x02000200;
    wp->u_15C.w[0]           = 0x200;
    ext->u_34.w              = 0;
    ext->u_38.w              = 0;
    ext->u_3C.w              = 0;
    ext->obj_40              = NULL;
    ext->u_44.fx[0]          = NULL;
    ext->u_44.fx[1]          = NULL;
    ext->flags_0             = 6;
    *(sint32 *)&ext->u_4     = 0;
    *(sint32 *)&ext->value_8 = 0;
    ext->value_14            = 0;
    ext->value_18            = 0;
    ext->u_24.w[1]           = 0;
    life                     = D_80098844[wp->kind_2]->life_8 << 4;
    wp->data_78              = D_8011DF24;
    wp->value_6E             = life;
    wp->value_B0             = life;
    wp->value_B2             = life;
    ground                   = func_80048E6C(wp);
    wp->position.y           = ground;
    wp->position_fixed.y     = ground << 16;
    wp->routine_0            = 1;
    if ((uint8)wp->value_F & 0x40)
    {
        wp->routine_1 = 2;
    }
    else
    {
        wp->routine_1 = 0;
    }
    *(uint16 *)&wp->routine_2 = 0;
    wp->u_15C.h[1]            = 0x4210;
}

void func_801076FC(ST09_VIEW *wp)
{
    sint16 temp_v0;

    if (wp->ext.flags_0 & 2)
    {
        func_80107C28(wp);
    }
    D_8011DF18[wp->routine_1](wp);
    temp_v0 = wp->ext.value_A;
    if (temp_v0 != 0)
    {
        wp->ext.value_A = temp_v0 - 1;
    }
    if (!(wp->ext.flags_0 & 8))
    {
        func_80051B68(wp, 3, -1, 0);
    }
}

void func_8010779C(ST09_VIEW *wp)
{
    func_80031824(wp);
    if (!((uint8)wp->u_C.b[3] & 0x40))
    {
        func_80031988(wp->ext.effect_50);
        func_80031988(wp->ext.piece_54);
        if (!((uint8)wp->u_C.b[3] & 2))
        {
            func_80031824(wp->ext.u_4C.p);
            func_80031988(wp->ext.u_58.obj);
            func_80031988(wp->ext.u_5C.p);
        }
    }
}

void func_80107828(ST09_VIEW *wp)
{
    sint16 temp_v0;

    wp->ext.value_8      = 0;
    wp->ext.u_44.h[1]    = (wp->ext.u_44.h[1] + 0x40) & 0xFFF;
    temp_v0              = func_80048E6C(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
}

void func_80107870(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STAGE_PIECE *piece;
    sint16 i;
    sint16 y;

    ext             = &wp->ext;
    wp->ext.value_8 = 0;
    switch (wp->routine_2)
    {
        case 0:
            wp->ext.u_44.h[1] = (wp->ext.u_44.h[1] + 0x40) & 0xFFF;
            if ((wp->rotation.y + wp->ext.u_44.h[1]) & 0x3FF)
            {
                break;
            }
            wp->routine_2    = 1;
            wp->ext.u_4.h[0] = 15;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                i = 0;
                do
                {
                    piece = (STAGE_PIECE *)func_80031518();
                    if (piece != NULL)
                    {
                        piece->flags_0        = 1;
                        piece->kind_2         = 9;
                        piece->variant_3      = 1;
                        piece->position       = wp->position;
                        piece->position_fixed = wp->position_fixed;
                        piece->angle_64       = (i ? wp->rotation.y + ext->u_44.h[1] + 0x800
                                                   : wp->rotation.y + ext->u_44.h[1]) &
                                                0xFFF;
                        func_8002FFC4(&piece->position, &piece->position_fixed, piece->angle_64,
                                      0x600, -0x7C0, 0);
                    }
                    i++;
                } while (i < 2);
                wp->routine_2 = 0;
            }
            break;
    }
    y                    = func_80048E6C(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 16;
}

void func_80107A14(ST09_VIEW *wp)
{
    STAGE_ACTOR_EXT *ext;
    STCOM_EFFECT *effect;
    ext = &wp->ext;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->u_44.h[1] = -30;
            wp->value_4E  = 3;
            effect        = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0x41;
                effect->sprite.position = wp->vec_180;
            }
            wp->u_F8.s[3]    = -1;
            wp->ext.value_8  = 0;
            wp->ext.u_4.h[0] = 10;
            wp->ext.flags_0  = (wp->ext.flags_0 & ~4) | 8;
            // fall through
        case 1:
            if (--ext->u_4.h[0] < 0)
            {
                wp->routine_2 = 2;
                wp->flags_0 &= ~2;
                wp->u_C.b[3] |= 4;
                effect = func_80031618();
                if (effect != NULL)
                {
                    effect->flags_0         = 5;
                    effect->kind_2          = 0x80;
                    effect->variant_3       = 0x40;
                    effect->sprite.position = wp->vec_188;
                }
                func_80047148(wp, &wp->vec_180, effect);
                if (!(wp->u_C.b[3] & 0x42))
                {
                    ((STAGE_OBJ *)ext->u_4C.p)->routine_0 = 4;
                }
            }
            else
            {
                func_8002FEA4(wp, 0, wp->u_44.h[1] << 4, 0);
                wp->u_44.h[1] += wp->value_4E;
                func_8004B414(wp);
                break;
            }
            // fall through
        case 2:
            if (!(wp->u_C.b[3] & 0x40))
            {
                if (wp->u_C.b[3] & 2)
                {
                    func_80031824(wp);
                    func_80031988(ext->effect_50);
                    func_80031988(ext->piece_54);
                }
            }
            else
            {
                func_80031824(wp);
            }
            break;
    }
}

sint32 func_80107C28(ST09_VIEW *wp)
{
    sint32 damage;

    damage = wp->ext.value_14 & 0xFFFFFF;
    if (damage)
    {
        if (wp->ext.value_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->ext.flags_0 &= ~2;
                Sound_call2(0xA2, &wp->position);
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->u_15C.h[1] = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_80107CDC(ST09_STCOM13_WORK *wp)
{
    D_8011DF34[wp->routine_0](wp);
    wp->ctl.hit_14 = 0;
}

void func_80107D28(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    STCOM_FIXED_VECTOR fixed;

    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    if (wp->variant_3 != 0)
    {
        func_8002F9C4(wp, &wp->variant_3);
    }
    else
    {
        func_8002F9C4(wp, NULL);
    }
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    ctl->hit_14              = 0;
    ctl->value_18            = 0;
    ctl->flags_0 |= 2;
    // Never used.
    fixed                     = wp->position_fixed;
    ctl->u_34.target.x        = 0x5905;
    ctl->u_34.target.z        = 0x26A2;
    ctl->u_34.target.y        = 0;
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->data_78               = D_8011DF4C;
    wp->data_10               = D_8011DF58;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->velocity.v.z          = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0x14, 0);
    func_80107E54(wp);
}

void func_80107E54(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_8011DF40[wp->routine_1](wp);
    ctl = &wp->ctl;
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 2:
                func_80031824(wp);
                Sce_flag_on(0xC);
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 1:
                wp->routine_1             = 2;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            case 0:
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            default:
                *(uint16 *)&wp->routine_2 = 0;
                break;
        }
        ctl->flags_0 &= ~1;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
    }
    if (wp->flags_0 & 1)
    {
        func_80051B68(wp, 3, -1, 0);
        if ((wp->flags_0 & 1) && (ctl->flags_0 & 2))
        {
            ctl->pos_C = wp->position;
            ctl->pos_C.y -= 0x50;
            func_800341BC(&ctl->pos_C, 0x50, 0, 0x8000, wp->index_1, &ctl->hit_14, 0x4000000,
                          0x800000, 0x80);
        }
    }
}

void func_80108098(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801080B8(ST09_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    ST09_ACTOR_CTL *ctl;
    STAGE_ACTOR *obj;
    sint16 i;
    sint32 dx;
    sint32 dz;

    pl  = &Player_work;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC  = 0x14;
            ctl->timer_4 = 0x3C;
            // fall through
        case 1:
            for (i = 0, obj = D_8009F108; i < 16; i++, obj++)
            {
                if ((D_800987E8 & (0x80000000 >> i)) && obj->kind_2 != 0x13 &&
                    (uint8)((obj->position.x >> 9) - D_8011DF64.x) < D_8011DF64.w &&
                    (uint8)((obj->position.z >> 9) - D_8011DF64.z) < D_8011DF64.d)
                {
                    break;
                }
            }
            if (i == 16)
            {
                ctl->flags_0 |= 8;
            }
            else
            {
                ctl->flags_0 &= ~8;
            }
            if ((sint16)ctl->timer_4 != 0)
            {
                ctl->timer_4--;
            }
            dx = (pl->position.x >> 9) - D_8011DF64.x;
            dz = (pl->position.z >> 9) - D_8011DF64.z;
            if (pl->target_184 == wp)
            {
                pl->target_184 = NULL;
                if (ctl->flags_0 & 8)
                {
                    if ((sint32)Moji_flag >= 0)
                    {
                        Sce_flag_on(0x60C);
                        wp->rotation.y = 0x5D4;
                    }
                }
                else if ((sint32)Moji_flag >= 0)
                {
                    ctl->timer_4 = 0x1C2;
                    MojiTaskExec2(4, wp->timer_C + 4);
                }
            }
            else if (ctl->hit_14 & 0xFFFFFF)
            {
                if ((sint32)Moji_flag >= 0)
                {
                    ctl->timer_4 = 0x1C2;
                    MojiTaskExec2(4, wp->timer_C + 5);
                }
            }
            else if ((uint32)dx >= D_8011DF64.w || (uint32)dz >= D_8011DF64.d)
            {
                if ((sint16)ctl->timer_4 == 0)
                {
                    ctl->timer_4 = 0x1C2;
                    ctl->flags_0 &= ~4;
                    MojiTaskExec2(4, wp->timer_C);
                }
            }
            else if (!(ctl->flags_0 & 4))
            {
                ctl->flags_0 |= 4;
                Sce_flag_off(0x60A);
                Sce_flag_off(0x60B);
                MojiTaskExec2(4, wp->timer_C);
            }
            break;
        case 2: // an empty case: retail's compare chain tests 1, then < 2
            break;
    }
}

void func_80108384(ST09_ACTOR *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (wp->frame_A4 == 0xF || wp->frame_A4 == 0x23)
            {
                wp->routine_2++;
                wp->anim_AC = 0x15;
                func_80063BC8(&wp->position, 2, 0, wp->timer_C + 6);
            }
            break;
        case 1:
            if ((sint32)Moji_flag >= 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
    }
}

void func_80108430(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    STCOM_EFFECT *fx;
    sint32 hit;
    sint32 dx;
    sint32 dz;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 2;
            wp->velocity.v.x = 0x180;
            wp->velocity.v.y = 0x180;
            wp->accel.y      = 0xC0;
            ctl->timer_4     = 8;
            Sce_flag_on(0x60D);
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &ctl->u_34.target,
                                                             wp->rotation.y, 0x60)) &
                             0xFFF;
            func_8002FEA4(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            hit = func_8004B414(wp);
            if (wp->position.y != wp->position_prev.y)
            {
                wp->velocity.v.y += wp->accel.y;
            }
            if (hit & 0x1000)
            {
                if (wp->velocity.v.y != 0x180)
                {
                    Sound_call(0x117, 0, 0);
                }
                wp->velocity.v.y = 0x180;
            }
            dx = wp->position.x - ctl->u_34.target.x;
            dz = wp->position.z - ctl->u_34.target.z;
            // timer_4 counts as a signed halfword here
            if ((sint16)ctl->timer_4 == 0 || --*(sint16 *)&ctl->timer_4 == 0)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0   = 3;
                    fx->kind_2    = 0x83;
                    fx->variant_3 = 0;
                    D_8011E968[0] = wp->position;
                    D_8011E970[0] = wp->position_fixed;
                    func_8002FFC4(D_8011E968, D_8011E970, (wp->rotation.y + 0x800) & 0xFFF,
                                  D_8011DF68[(ctl->value_2 & 3) * 4], -((rand() & 0x1F) * 16),
                                  D_8011DF6C[(ctl->value_2 & 3) * 4]);
                    fx->sprite.pos_8[0] = D_8011E968[0].x;
                    fx->sprite.pos_8[1] = D_8011E968[0].y;
                    fx->sprite.pos_8[2] = D_8011E968[0].z;
                }
            }
            if (dx * dx + dz * dz < 0x800)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
    if (wp->value_A6 == 1)
    {
        Sound_call(0x116, 0, 0);
    }
}

void func_8010870C(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_8011DF88[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 4))
    {
        ctl->pos_C = wp->joints_180[0];
        func_800341BC(&ctl->pos_C, 0x30, 0, 0x8000, wp->value_1, &ctl->hit_14,
                      ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_801088B0(STAGE_STCOM15_WORK_348 *wp)
{
    sint32 life;

    wp->rotation.x          = 0;
    wp->rotation.z          = 0;
    *(uint32 *)&wp->turn_64 = 0;
    wp->flags_0 |= 2;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0]          = 0x02000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_0             = 0xE;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    *(uint32 *)&wp->ctl.value_8 = 0;
    wp->ctl.hit_14              = 0;
    wp->ctl.value_18            = 0;
    func_80036478(wp->ctl.track_24, D_80098844[wp->kind_2]->value_F, -0x60);
    wp->ctl.timer_36 = 4;
    wp->ctl.timer_34 = wp->position.pad;
    wp->position.pad = 0;
    life             = D_80098844[wp->kind_2]->life_8;
    wp->data_78      = D_8011DFAC;
    wp->data_10      = NULL;
    wp->life_6E      = life;
    wp->life_max_B0  = life;
    wp->life_prev_B2 = life;
    switch (wp->variant_3)
    {
        case 0:
            wp->position.y            = func_80048E6C(wp);
            wp->position_fixed.y      = wp->position.y << 16;
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 1:
            if (!Sce_flag_test((uint16)wp->ctl.timer_34))
            {
                wp->routine_0 = 1;
                wp->routine_1 = 4;
                wp->routine_2 = 0xFF;
                wp->routine_3 = 0;
                wp->flags_0 &= ~2;
                func_800322A8(wp, 0, 0);
                wp->ctl.flags_0 = (wp->ctl.flags_0 | 0x40) & ~6;
                break;
            }
            // fall through
        default:
            wp->position.y            = func_80048E6C(wp);
            wp->position_fixed.y      = wp->position.y << 16;
            wp->routine_0             = 1;
            wp->routine_1             = 1;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            wp->turn_66 = 0;
            break;
    }
    wp->scale.v.pad = 0x4210;
}

void func_80108A8C(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    STCOM_EFFECT *fx;

    ctl = &wp->ctl;
    if (wp->ctl.flags_0 & 0x20)
    {
        if (func_8003648C(ctl->track_24, wp))
        {
            wp->ctl.flags_0 |= 0x10;
        }
        else
        {
            wp->ctl.flags_0 &= ~0x10;
        }
    }
    if (ctl->flags_0 & 2)
    {
        func_80109C94(wp);
    }
    D_8011DF94[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 4:
                wp->routine_1 = 3;
                break;
            case 5:
                wp->routine_1 = 3;
                break;
            case 3:
                if (ctl->flags_0 & 0x10)
                {
                    wp->routine_1 = 2;
                    break;
                }
                // fall through
            default:
                func_80109BB8(wp);
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->flags_0 & 0x80)
    {
        if (--ctl->u_34.timer[1] < 0)
        {
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 5;
                fx->kind_2          = 0x80;
                fx->variant_3       = 0x41;
                fx->sprite.position = wp->position;
            }
            func_80031824(wp);
            func_80047148(wp, &wp->value_180);
            Sound_call2(0xA1, &wp->value_180);
        }
    }
}

void func_80108C70(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80108C90(STAGE_ACTOR *wp)
{
    STAGE_ACTOR_CTL *ctl;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0;
            wp->ctl.timer_4 = 60;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 &= ~0x20;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80108D0C(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x30;
            wp->accel.x      = 4;
            ctl->timer_4     = 0x32;
            ctl->level_6     = 0x19;
            ctl->value_8     = 0;
            ctl->flags_0 &= ~0x20;
            // fall through
        case 1:
            if (--ctl->level_6 < 0)
            {
                ctl->level_6     = 0x19;
                wp->velocity.v.x = 0x30;
            }
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            func_8002FEA4(wp, wp->velocity.v.x, 0, 0);
            wp->velocity.v.x += wp->accel.x;
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit & 0xF00)
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (wp->position.y - wp->position_prev.y > 0x20)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80108F90(STAGE_STCOM15_WORK_348 *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 2;
            wp->velocity.v.x = 0x100;
            wp->accel.x      = 0x10;
            ctl->timer_4     = 0xC;
            ctl->value_8     = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->velocity.v.x = 0x100;
                ctl->timer_4     = 0xC;
            }
            wp->rotation.y = (wp->rotation.y +
                              func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x30)) &
                             0xFFF;
            func_8002FEA4(wp, (uint8)wp->value_A6, 0, 0);
            wp->velocity.v.x += wp->accel.x;
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (hit & 0xF00)
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (wp->position.y - wp->position_prev.y > 0x20)
            {
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (wp->value_80 < 0x1E848)
            {
                if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x40, &pl->position_fixed,
                                  pl->rotation.y, 0x400))
                {
                    wp->routine_1             = 5;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->anim_AC               = wp->anim_prev_AD;
                    break;
                }
            }
            if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 = (ctl->flags_0 | 1) & ~0x20;
            }
            break;
    }
}

void func_80109260(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 7;
            ctl->timer_4  = 0xC;
            ctl->value_8  = 0;
            func_80036470(ctl->track_24);
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC   = (ctl->rand_2 & 1) + 0xC;
                ctl->timer_4  = 6;
                ctl->flags_0 |= 0x20;
            }
            else
            {
                if (ctl->timer_4 >= 3)
                {
                    func_8002FEA4(wp, -0x50, 0, 0);
                    func_8004B414(wp);
                    wp->position.y       = func_80048E6C(wp);
                    wp->position_fixed.y = wp->position.y << 16;
                    if (!(((wp->position.y - wp->position_prev.y < 0)
                               ? wp->position_prev.y - wp->position.y
                               : wp->position.y - wp->position_prev.y) < 0x21))
                    {
                        wp->position       = wp->position_prev;
                        wp->position_fixed = wp->position_fixed_prev;
                    }
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC += 2;
            ctl->timer_4 = (ctl->rand_2 & 7) + 8;
            if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed,
                              pl->rotation.y, 0x800) != 0)
            {
                ctl->level_6 = (ctl->rand_2 & 3) + 1;
            }
            else
            {
                ctl->level_6 = (ctl->rand_2 & 7) + 3;
            }
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                if (--ctl->level_6 < 0)
                {
                    wp->routine_2 = 4;
                    wp->anim_AC += 2;
                    ctl->timer_4 = 0xD;
                }
                else
                {
                    wp->anim_AC ^= 1;
                    ctl->timer_4 = (ctl->rand_2 & 7) + 7;
                    break;
                }
            }
            else
            {
                if (ctl->flags_0 & 0x10)
                {
                    ctl->level_6 = 0;
                }
                break;
            }
            // fall through
        case 4:
            func_8002FEA4(wp, 0x33, 0, 0);
            func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801095E8(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0xFF:
            if (!Sce_flag_test((uint16)ctl->timer_34))
            {
                break;
            }
            wp->flags_0 |= 2;
            ctl->flags_0 |= 6;
            // fall through
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 4;
            if (ctl->flags_0 & 0x40)
            {
                wp->velocity.v.x = (ctl->rand_2 & 3) << 7;
                wp->velocity.v.y = (-(ctl->rand_2 & 0x30) + 1) * 16;
                wp->accel.y      = (((ctl->rand_2 >> 3) & 6) + 1) * 16;
                ctl->flags_0 &= ~0x40;
            }
            else
            {
                wp->velocity.v.x = 0x200;
                wp->velocity.v.y = -0x100;
                wp->accel.y      = 0x40;
                wp->rotation.y &= 0xFFF;
            }
            ctl->timer_4 = 0x10;
            ctl->level_6 = 0;
            ctl->value_8 = 0;
            ctl->flags_0 &= ~0x28;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2    = 1;
                wp->velocity.v.x = 0x88;
                wp->velocity.v.y = -0xF0;
                wp->accel.y      = 0x30;
            }
            // fall through
        case 1:
            func_8002FEA4(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel.y;
            hit = func_8004B414(wp);
            if (hit & 0xF00)
            {
                wp->velocity.v.x = 0;
            }
            if (hit & 0x1000)
            {
                if (++ctl->level_6 == 1)
                {
                    wp->routine_2    = 2;
                    wp->anim_AC      = 5;
                    wp->velocity.v.x = 0xF0;
                    wp->velocity.v.y = 0;
                    wp->accel.y      = 0;
                    ctl->timer_4     = 2;
                    break;
                }
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_8010981C(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    sint32 hit;
    sint16 t;

    ctl = &wp->ctl;
    if (wp->ctl.hit_14 & 0x2000000)
    {
        wp->ctl.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 7;
            ctl->timer_4  = 9;
            ctl->value_8  = D_80098844[wp->kind_2]->value_A;
            ctl->flags_0 &= ~0x20;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 2;
                wp->anim_AC   = 8;
                ctl->timer_4  = 0xB;
            }
            else
            {
                func_8002FEA4(wp, -0x50, 0, 0);
                func_8004B414(wp);
                wp->position.y       = func_80048E6C(wp);
                wp->position_fixed.y = wp->position.y << 16;
                if (!(((wp->position.y - wp->position_prev.y < 0)
                           ? wp->position_prev.y - wp->position.y
                           : wp->position.y - wp->position_prev.y) < 0x21))
                {
                    wp->position       = wp->position_prev;
                    wp->position_fixed = wp->position_fixed_prev;
                }
                break;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 3;
                wp->anim_AC   = 9;
                ctl->timer_4  = -3;
                func_8002FEA4(wp, 0x640, -0x5A0, 0);
                func_8004B414(wp);
                Sound_call2(0xBA, &wp->position);
            }
            break;
        case 3:
            t = ++ctl->timer_4;
            if (t < 0)
            {
                wp->position.y -= t * t * 4;
            }
            else
            {
                wp->position.y += t * t * 4;
            }
            wp->position_fixed.y = wp->position.y << 16;
            func_8002FEA4(wp, 0x370, 0, 0);
            hit = func_8004B414(wp);
            if (hit & 0xF00)
            {
                wp->velocity.v.x = 0;
            }
            if (hit & 0x1000)
            {
                wp->routine_2 = 4;
                wp->anim_AC   = 0xA;
                ctl->timer_4  = 0xA;
                ctl->value_8  = 0;
            }
            if (ctl->hit_14 & 0x2000000)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                wp->rotation.y            = (wp->rotation.y + 0x800) & 0xFFF;
                ctl->value_8              = 0;
            }
            break;
        case 4:
            func_8002FEA4(wp, 0xA0, 0, 0);
            func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (!(((wp->position.y - wp->position_prev.y < 0)
                       ? wp->position_prev.y - wp->position.y
                       : wp->position.y - wp->position_prev.y) < 0x21))
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

sint32 func_80109BB8(ST09_ACTOR *wp)
{
    sint16 sum;
    sint16 i;

    sum = 0;
    for (i = 0; i < 4; i++)
    {
        sum += D_8011DFB8[i];
        if ((wp->ctl.value_2 & 0xF) < sum)
        {
            break;
        }
    }
    wp->routine_1 = 1;
    switch (i)
    {
        case 0:
            wp->routine_1 = 3;
            break;
        case 1:
            wp->spin_66 = 0;
            // fall through
        case 2:
            wp->spin_66 = 0x10;
            break;
        case 3:
            wp->spin_66 = -0x10;
            break;
    }
    return 1;
}

sint32 func_80109C94(ST09_ACTOR *wp)
{
    ST09_ACTOR_CTL *ctl;
    STCOM_SVECTOR origin = {0}; // not {0, 0, 0, 0}: a separate constant from func_80106D1C's
    STCOM_SVECTOR *from;
    uint32 damage;
    sint16 turn;
    sint16 id;
    from   = &origin;
    ctl    = &wp->ctl;
    damage = wp->ctl.hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (wp->ctl.hit_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if (wp->value_6E <= 0)
            {
                wp->ctl.flags_0 = (wp->ctl.flags_0 & ~2) | 0x88;
                damage          = D_80098844[wp->kind_2]->limit_9;
            }
            if (wp->ctl.flags_0 & 8)
            {
                wp->ctl.timer_A += damage;
                if (!(wp->ctl.hit_14 & 0x20000000) &&
                    wp->ctl.timer_A < D_80098844[wp->kind_2]->limit_9)
                {
                    Sound_call2(0xA0, &wp->position);
                }
                else
                {
                    Sound_call2(0xA2, &wp->position);
                    if (wp->ctl.target_1C.pad & 1)
                    {
                        turn = func_80031198(&wp->position, &wp->ctl.target_1C);
                        if (((wp->rotation.y - turn + 0x400) & 0xFFF) < 0x800)
                        {
                            wp->rotation.y = turn;
                        }
                        else
                        {
                            wp->rotation.y = (turn + 0x800) & 0xFFF;
                        }
                    }
                    else
                    {
                        turn           = func_80031198(from, &wp->ctl.target_1C);
                        wp->rotation.y = turn;
                    }
                    wp->routine_1             = 4;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->timer_A              = 0;
                }
            }
            else
            {
                id = 0xA2;
                if (!(wp->ctl.hit_14 & 0x20000000))
                {
                    id = 0xA0;
                    if (wp->ctl.timer_A >= D_80098844[wp->kind_2]->limit_9)
                    {
                        id = 0xA2;
                    }
                }
                Sound_call2(id, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
