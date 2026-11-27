#include "common.h"
#include "st05.h"

void func_801169F0(STAGE_OBJ *wp)
{
    D_801317FC[wp->routine_0](wp);
}

void func_80116A2C(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    wp->be_flag |= 2;
    ctl = &wp->ctl;
    if (wp->type != 0)
    {
        Model_work_init(wp, &wp->type);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0]       = 0x021A021A;
    wp->scale.words[1]       = 0x21A;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 0;
    *(uint32 *)&ctl->timer_4 = 0;
    D_80137F58               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_80137F58, wp->rotation.y, 0x100, 0, 0);
    ctl->timer_A              = 0;
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->value_78              = (sint32)D_80131814;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->data_10               = NULL;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_80116B70(wp);
}

void func_80116B70(ST05_VILLAGER *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_80131808[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    *(uint16 *)0x1F800132 = wp->ctl.timer_A;
    Model_parts_mtx_set_y(wp);
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    func_80051B68(wp, 3, -1, 0);
}
