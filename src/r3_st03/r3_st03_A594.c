#include "common.h"
#include "st03.h"

void func_8010A594(STAGE_OBJ *wp)
{
    D_80117060[wp->routine_0](wp);
}

void func_8010A5D0(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x01D701D7;
    wp->scale.words[1]       = 0x1D7;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 0;
    *(uint32 *)&ctl->timer_4 = 0;
    D_8011CA98               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_8011CA98, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E          = 0x80;
    wp->value_B0          = 0x80;
    wp->value_B2          = 0x80;
    wp->value_78          = (sint32)D_80117084;
    wp->rotation.x        = 0;
    wp->rotation.z        = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->data_10           = D_80117090;
    switch (wp->variant_3)
    {
        case 0:
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 1:
            wp->routine_0             = 1;
            wp->routine_1             = 2;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 2:
            wp->routine_0             = 1;
            wp->routine_1             = 3;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0x10, 0x1d);
            break;
        case 3:
            wp->routine_0             = 1;
            wp->routine_1             = 4;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 4:
            wp->routine_0             = 1;
            wp->routine_1             = 5;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
    }
    func_8010A788(wp);
}

void func_8010A788(ST03_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_8011706C[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
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
    func_80051B68(wp, 1, -1, 0);
}
