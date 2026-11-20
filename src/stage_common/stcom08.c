#include "common.h"
#include "stage_common/stcom08.h"

// Shared stage code, linked into 9 stages: r3_st03, r3_st05, r3_st06, r3_st08, r3_st0a,
// r3_st0c, r3_st10, r3_st12 and r3_st1b. Each stage compiles this file against its own copy of
// the assembly (TARGET_ASM, set by tools/cc.sh); the names are the same in every stage's
// registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom08"

void stcom08_func_0000(STCOM08_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom08_D_0000[wp->routine_0](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0xC, 0x200, 0);
    }
    if (wp->routine_3 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_3++;
    }
}

void stcom08_func_00F0(STCOM08_WORK *wp)
{
    wp->rotation.x = 0;
    wp->rotation.y = 0;
    wp->rotation.z = 0;
    wp->turn_64    = 0x80;
    wp->flags_0 |= 2;
    wp->rot_speed_66 = (rand() & 0xF) - 8;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x1800180;
    wp->scale.words[1]   = 0x180;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = func_80048E6C(wp) - 100;
    wp->position_fixed.y = wp->position.y << 16;
    wp->home             = wp->position;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->velocity.x       = 0x10;
    wp->velocity.y       = 0;
    wp->velocity.z       = 0;
    wp->timer_34C        = (rand() & 0x7F) | 1;
    func_800322A8(wp, 0, 0);
    wp->routine_0 = 1;
    wp->routine_3 = 0;
}

void stcom08_func_01F0(STCOM08_WORK *wp)
{
    wp->rotation.y = (wp->rotation.y + wp->rot_speed_66) & 0xFFF;
    if (--wp->timer_34C == 0)
    {
        wp->routine_0 = 3;
        wp->routine_1 = 0;
    }
    stcom08_func_0348(wp);
}

void stcom08_func_0248(STCOM08_WORK *wp)
{
    wp->dist_350 = Distance_xyz(&wp->position, &wp->home) >> 7;
    switch (wp->routine_1)
    {
        case 0:
            if (wp->dist_350 >= wp->range_D && wp->range_D != 0)
            {
                wp->routine_1++;
            }
            else
            {
                stcom08_func_0424(wp);
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &wp->home, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (wp->dist_350 < 2)
            {
                stcom08_func_0424(wp);
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
    }
    stcom08_func_0348(wp);
}

void stcom08_func_0328(STCOM08_WORK *wp)
{
    func_80031824(wp);
}

void stcom08_func_0348(STCOM08_WORK *wp)
{
    sint16 ground;
    uint16 wobble;

    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, 0);
    if (func_80048DAC(&wp->position))
    {
        func_80031824(wp);
        return;
    }
    ground = func_80048E6C(wp);
    wobble = stcom08_D_0010[STCOM08_FRAME & 7];
    if (wp->position.y > ground - 100)
    {
        wp->position.y = ground - 100 + wobble;
        wp->velocity.y = -0x10;
    }
    else if (wp->position.y < ground - 400)
    {
        wp->position.y = ground - 400 + wobble;
        wp->velocity.y = 0x10;
    }
    else
    {
        wp->position.y += wobble;
    }
}

void stcom08_func_0424(STCOM08_WORK *wp)
{
    wp->timer_34C    = (rand() & 0x7F) | 1;
    wp->velocity.y   = (rand() & 0xF) + 8;
    wp->rot_speed_66 = (rand() & 0xF) - 8;
}
