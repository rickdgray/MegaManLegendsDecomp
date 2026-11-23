#include "common.h"
#include "st05.h"

void func_8010FE10(STAGE_OBJ *wp)
{
    D_80131320[wp->routine_0](wp);
}

void func_8010FE4C(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;
    STCOM_FIXED_VECTOR fixed; // copied but never read

    wp->flags_0 |= 2;
    ctl = &wp->ctl2;
    if (wp->variant_3 != 0)
    {
        Model_work_init(wp, &wp->variant_3);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0]        = 0x02000200;
    wp->scale.words[1]        = 0x200;
    wp->scale.v.pad           = 0x4210;
    ctl->flags_0              = 0;
    *(sint32 *)&ctl->timer_4  = 0;
    fixed                     = wp->position_fixed;
    ctl->target_C.x           = -0xDFC;
    ctl->target_C.z           = 0x190;
    ctl->target_C.y           = 0;
    ctl->timer_A              = 0;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->value_6E              = 0;
    wp->value_B0              = 0;
    wp->value_B2              = 0;
    wp->data_78               = NULL;
    wp->data_10               = NULL;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 2, 0);
    func_8010FF58(wp);
}

void func_8010FF58(ST05_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl2.value_2        = rand();
    D_8013132C[wp->routine_1](wp);
    if (wp->ctl2.flags_0 & 1)
    {
        func_80031824(wp);
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl2.flags_0 &= ~1;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    *(uint16 *)0x1F800132 = wp->ctl2.timer_A;
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801100BC(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801100DC(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_801100FC(ST05_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0x13;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void func_80110154(ST05_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0x11;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                wp->anim_AC = 0;
                Sce_flag_on(0x61F);
            }
            break;
        case 2:
            break;
    }
}

void func_801101C0(ST05_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0x12;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->routine_2++;
                wp->anim_AC = 0;
            }
            break;
        case 2:
            break;
    }
}

void func_80110214(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;
    STAGE_PL_VIEW *pl;

    ctl = &wp->ctl2;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 1;
            wp->turn_64 = 0x20;
            wp->routine_2++;
            ctl->timer_4 = 0x28;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (--ctl->timer_4 == 0)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            wp->anim_AC = 0;
            wp->routine_2++;
            ctl->timer_4 = 0x14;
            break;
        case 3:
            ctl->timer_A =
                (ctl->timer_A + Muku(&wp->position, &pl->position, (wp->rotation.y + ctl->timer_A) & 0xFFF, wp->turn_64)) & 0xFFF;
            if (--ctl->timer_4 == 0)
            {
                wp->routine_2++;
            }
            break;
        case 4:
            break;
    }
}

void func_80110344(ST05_OBJ *wp)
{
    sint32 temp_v1;
    uint8 temp_a1;

    temp_a1 = wp->routine_2;
    temp_v1 = temp_a1 & 0xFF;
    switch (temp_v1)
    {
        case 0:
            wp->routine_2 = temp_a1 + 1;
            wp->anim_AC   = 0;
        case 1:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
                return;
            }
            return;
        case 2:
            if (wp->value_A7 < 0)
            {
                wp->routine_2 = temp_a1 - 1;
                wp->anim_AC   = 0;
            }
            break;
    }
}

void func_801103D8(ST05_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_80131344[wp->routine_0](wp, &Scene_work, &wp->fall_348);
    Model_Shadow_Trans(wp, 0x100, 0x200, 0);
}

void func_8011049C(ST05_OBJ *wp, STAGE_SCENE_WORK *scene, ST05_FALL *fall)
{
    sint16 y;

    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]     = 0x02000200;
    wp->scale.words[1]     = 0x200;
    wp->scale.v.pad        = 0x4210;
    wp->value_78           = 0;
    y                      = wp->position.y + Obj_ceiling_height_get(wp) - 0x4C0;
    wp->position.y         = y;
    wp->position_fixed.v.y = y << 16;
    fall->speed_4.value    = 0x88000;
    fall->count_0          = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_80110550(ST05_OBJ *wp, STAGE_SCENE_WORK *scene, ST05_FALL *fall)
{
    if (fall->speed_4.value > 0x8000)
    {
        wp->position.y += fall->speed_4.value >> 16;
        wp->position_fixed.v.y += fall->speed_4.value;
        if (++fall->count_0 == 0x10)
        {
            fall->count_0 = 0;
            fall->speed_4.value -= 0x8000;
        }
    }
    else if (scene->u_8.byte[1] == 4 && scene->value_10 >= 0x79)
    {
        fall->value_8 = 0;
        fall->step_A  = 0xE;
        fall->count_C = 0;
        wp->routine_0++;
    }
    func_80032488(wp);
}

void func_8011061C(ST05_OBJ *wp, STAGE_SCENE_WORK *scene, ST05_FALL *fall)
{
    sint16 value;

    if (scene->reserved00[7] == 0)
    {
        value = fall->value_8;
        if (value < 0x600)
        {
            fall->value_8 = value + fall->step_A;
            if (!(++fall->count_C % 4))
            {
                fall->step_A += 0x14;
            }
        }
        else
        {
            fall->value_8        = 0x600;
            fall->step_A         = 0xE;
            fall->count_C        = 0;
            scene->reserved00[7] = 1;
        }
    }
    if (scene->u_8.byte[1] == 6 && scene->value_10 >= 0xB)
    {
        wp->routine_0++;
    }
    func_80032538(wp);
    *(uint16 *)0x1F800130 = fall->value_8;
    Model_parts_mtx_set_y(wp);
}

void func_8011070C(ST05_OBJ *wp, STAGE_SCENE_WORK *scene, ST05_FALL *fall)
{
    sint16 value;

    value = fall->value_8;
    if (value > 0)
    {
        fall->value_8 = value - fall->step_A;
        if (!(++fall->count_C % 4))
        {
            fall->step_A += 0x14;
        }
    }
    else
    {
        fall->value_8 = 0;
    }
    if (scene->u_8.byte[1] == 6 && scene->value_10 >= 0x33)
    {
        fall->count_0       = 0;
        fall->speed_4.value = 0x10000;
        wp->routine_0++;
    }
    func_80032538(wp);
    *(uint16 *)0x1F800130 = fall->value_8;
    Model_parts_mtx_set_y(wp);
}

void func_801107D8(STAGE_OBJ *wp, void *arg1, ST05_FALL *fall)
{
    wp->position.y -= fall->speed_4.value >> 16;
    wp->position_fixed.v.y -= fall->speed_4.value;
    if (++fall->count_0 == 5)
    {
        fall->count_0 = 0;
        fall->speed_4.value += 0x8000;
    }
    func_80032488(wp);
}

void func_80110850(ST05_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_80131358[wp->routine_0](wp);
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else if (wp->ctl.flags_0 & 1)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_AC, wp->value_A4);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80110970(ST05_ACTOR *wp)
{
    wp->kind_2 = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->kind_2                  = 0xC;
    wp->scale.v.z               = 0x200;
    wp->rotation.x              = 0;
    wp->rotation.z              = 0;
    *(sint32 *)&wp->turn_64     = 0;
    wp->scale.words[0]          = 0x02000200;
    wp->ctl.flags_0             = 1;
    *(sint32 *)&wp->ctl.timer_4 = 0;
    func_800322A8(wp, 9, 0);
    wp->routine_0++;
}

void func_80110A00(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3   = 1;
        wp->ctl.timer_4 = 0;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC      = 9;
                wp->frame_110    = 7;
                wp->velocity.v.x = 0xC0;
                Obj_pos_set(wp, 0xC0, 0, 0);
                break;
            case 1:
                wp->anim_AC      = 0;
                wp->frame_110    = 6;
                wp->velocity.v.x = 0;
                break;
            case 2:
                wp->anim_AC   = 9;
                wp->frame_110 = 7;
                break;
        }
    }
    else
    {
        wp->ctl.timer_4++;
        switch (wp->routine_2)
        {
            case 0:
                Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
                break;
            case 1:
                if (wp->ctl.timer_4 == 5 || wp->ctl.timer_4 == 15)
                {
                    wp->frame_110 = 7;
                }
                if (ctl->timer_4 == 10 || ctl->timer_4 == 20)
                {
                    wp->frame_110 = 6;
                }
                break;
            case 2:
                wp->rotation.y = (wp->rotation.y + 0x100) & 0xFFF;
                break;
        }
    }
}

void func_80110B78(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}
