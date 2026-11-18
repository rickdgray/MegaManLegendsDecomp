#include "common.h"
#include "st05.h"

void func_801228EC(ST05_PROP_B *wp)
{
    STCOM_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    m                       = &wp->matrix;
    wp->ctl.random_2        = rand();
    D_80132184[wp->routine_0](wp);
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

void func_80122A9C(ST05_PROP_B *wp)
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
    m                           = &wp->matrix;
    wp->ctl.flags_0             = 0;
    *(uint32 *)&wp->ctl.timer_4 = 0;
    RotMatrixYXZ(&wp->rotation.v, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    wp->data_78               = D_801321A8;
    wp->value_6E              = 0x400;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 1;
    *(uint16 *)&wp->routine_2 = 0;
    wp->color_B4              = 0x808080;
}

void func_80122BA4(STAGE_PROP *wp)
{
    D_80132190[wp->routine_1](wp);
    wp->position_AC = wp->position;
    if (wp->flags_BC & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->flags_BC &= ~1;
    }
}

void func_80122C34(STAGE_OBJ *wp)
{
    func_800318D8(wp);
}

void func_80122C54(ST05_PROP_B *wp)
{
    STCOM_PL_WORK *pl;
    ST05_PROP_CTL *ctl;
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
    if (ST05_ABS(dy) < 0x80 && dx * dx + dz * dz < 0x400)
    {
        Sound_call(5, 0, 0);
        wp->routine_1             = 4;
        *(uint16 *)&wp->routine_2 = 0;
    }
}

void func_80122E60(uint8 *arg0)
{
    *arg0 &= 0xFD;
}

void func_80122E74(uint8 *arg0)
{
    *arg0 |= 2;
}

void func_80122E88(ST05_PROP_B *wp)
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

void func_80122FE4(ST05_PROP_B *wp)
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

void func_80123094(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800318D8(wp);
        Sce_flag_on(0x611);
        wp->routine_2++;
    }
}
