#include "common.h"
#include "st1b.h"

void func_80104EF4(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_8010E6EC[wp->routine_0](wp, (sint16 *)&wp->reserved30C[0x1C]);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80104FE4(STAGE_OBJ *wp, uint16 *arg1)
{
    wp->be_flag |= 0x42;
    Model_work_init(wp, NULL);
    wp->scale.words[0]          = 0x02000200;
    wp->scale.words[1]          = 0x42100200;
    wp->value_78                = 0;
    wp->anim_AC                 = 0;
    wp->anim_prev_AD            = 0xFF;
    wp->u_C.b.byte_C            = 0;
    wp->value_48.words.fraction = 0;
    wp->value_44.words.integer  = 0;
    wp->value_44.words.fraction = 0;
    *arg1                       = (uint16)wp->position.y;
    wp->routine_1               = 0;
    wp->routine_0++;
}

void func_80105078(STAGE_OBJ *wp, sint16 *base)
{
    wp->position_fixed.v.y = rsin(++wp->u_C.b.byte_C << 6) * 0x140 + (*base << 16);
    func_80030150(&wp->position_fixed.v, &wp->position);
}

void func_801050E8(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80105108(STAGE_WORK *wp)
{
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_80105178(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->timer_C = 0;
        wp->routine_2++;
    }
    else
    {
        wp->position_fixed.v.y = rsin(++wp->timer_C << 6) * 0x140 + 0xFC180000;
    }
}

void func_801051F4(STAGE_OBJ *wp)
{
    sint16 temp_v0;
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position_fixed.v.y = -0x03E80000;
            return;
        case 1:
            wp->position_fixed.v.y += 0xFFFF0000;
            return;
        case 2:
            wp->value_44.words.integer = -0x2000;
            wp->routine_2++;
        case 3:
            temp_v0                    = (uint16)wp->value_44.words.integer - 0x88;
            wp->value_44.words.integer = temp_v0;
            wp->position_fixed.v.y += (sint32)(temp_v0 << 0x10) >> 0xC;
            return;
    }
}

void func_80105290(STAGE_OBJ *wp)
{
    D_8010E6F8[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_801052F8(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80105108(wp);
    }
    func_80105290(wp);
}
