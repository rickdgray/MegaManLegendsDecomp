#include "common.h"
#include "st10.h"

void func_80104D48(STAGE_OBJ *wp)
{
    D_8011465C[wp->routine_0](wp);
}


void func_80104D84(ST10_ACTOR *wp)
{
    STCOM_FIXED_VECTOR fixed;
    ST10_ACTOR_CTL *ctl;
    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    if (wp->variant_3 != 0)
    {
        Model_work_init(wp, &wp->variant_3);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 2;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    fixed                    = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &fixed, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->data_10               = D_80114670;
    wp->value_78              = 0;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->velocity.v.z          = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_80104EC4(wp);
}

void func_80104EC4(ST10_ACTOR *wp)
{
    ST10_ACTOR_CTL *ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    ctl                     = &wp->ctl;
    if (wp->ctl.flags_0 & 2)
    {
        func_80105360(wp);
    }
    D_80114668[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
            case 1:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
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
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->flags_0 & 1)
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_80105068(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80105088(ST10_ACTOR *wp)
{
    ST10_ACTOR_CTL *ctl;
    sint32 step;
    uint8 routine;

    ctl     = &wp->ctl;
    routine = wp->routine_2;
    switch (routine)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            if (Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x800) < 0)
            {
                step = -Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x800);
            }
            else
            {
                step = Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x800);
            }
            wp->turn_64  = (uint32)step >> 3;
            ctl->timer_4 = 0x1E;
            // fall through
        case 1:
            step           = Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if ((sint16)step == 0)
            {
                ctl->flags_0 |= 2;
                wp->routine_2++;
            }
            break;
        case 2: // empty: gives retail's compare chain
            break;
    }
}

void func_801051A0(ST10_ACTOR *wp)
{
    STAGE_PL_VIEW *pl;
    ST10_ACTOR_CTL *ctl;
    uint32 turn;
    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            if (Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
            {
                turn = -Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
            }
            else
            {
                turn = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
            }
            turn >>= 3;
            wp->turn_64  = turn;
            ctl->timer_4 = (ctl->value_2 & 0x3F) + 8;
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (--wp->ctl.timer_4 < 0)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            if (Scene_work.reserved00[0] == 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2--;
                wp->ctl.timer_4 = (wp->ctl.value_2 & 0x3F) + 8;
            }
            if (Scene_work.reserved00[0] == 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
    }
}

sint32 func_80105360(ST10_ACTOR *wp)
{
    ST10_ACTOR *target;

    target = STAGE_PL.target_184;
    if (target == wp)
    {
        target->routine_1             = 1;
        *(uint16 *)&target->routine_2 = 0;
        target->ctl.flags_0 &= ~2;
        STAGE_PL.target_184 = NULL;
        if (STAGE_GAME.value_50 == 4)
        {
            func_8001DDE4(9);
            ST10_SCENE_BYTE_4 = 1;
        }
        else
        {
            func_8001DDE4(0x1D);
            ST10_SCENE_BYTE_4 = 0;
        }
    }
    return 1;
}
