#include "common.h"
#include "stage_common/stcom31.h"

// Shared stage code, linked into 3 stages: r3_st03, r3_st04 and r3_st06. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom31"

// A vehicle that drives along one of two courses of waypoints, puffing exhaust.
void stcom31_func_0000(STCOM31_WORK *wp)
{
    STCOM_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation.v;
    m                       = &wp->matrix;
    wp->ctl.random_2        = rand();
    stcom31_D_0000[wp->routine_0](wp);
    RotMatrixYXZ(&wp->rotation.v, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    func_80051B68(wp, 1, -1, 0x1000008);
}

void stcom31_func_00F8(STCOM31_WORK *wp)
{
    STCOM_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    wp->pos_AC            = wp->position;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->value_64          = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->rotation.v.x      = 0;
    wp->rotation.v.z      = 0;
    wp->flags_0 |= 4;
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
    wp->value_6E              = 0x400;
    wp->data_78               = stcom31_D_0014;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    wp->color_B4              = 0x808080;
}

void stcom31_func_01F8(STCOM31_WORK *wp)
{
    if (Sce_flag_test(4) != 0)
    {
        wp->flags_0 |= 2;
    }
    stcom31_D_000C[wp->routine_1](wp);
    wp->pos_AC = wp->position;
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
}

void stcom31_func_02A8(STCOM31_WORK *wp)
{
    func_800318D8(wp);
}

// Waits.
void stcom31_func_02C8(STCOM31_WORK *wp)
{
    STCOM31_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->ctl.timer_4  = 0x1E;
            wp->velocity.v.x = 0;
            wp->velocity.v.y = 0;
            wp->velocity.v.z = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

// Drives to the next waypoint, slowing down near it.
void stcom31_func_033C(STCOM31_WORK *wp)
{
    STCOM31_CTL *ctl;
    STCOM31_WAYPOINT *point;
    STCOM_EFFECT *effect;
    sint32 step;
    sint32 dx;
    sint32 dz;
    sint16 i;
    sint16 set;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->ctl.timer_4 = 0x1E;
            wp->flags_0 |= 2;
            if (wp->param_F & 0x40)
            {
                wp->velocity.v.x = 0;
                stcom31_E_0020   = 4;
            }
            else
            {
                wp->velocity.v.x = 0x240;
                stcom31_E_0020   = 5;
            }
            wp->accel.x      = 0x16;
            wp->velocity.v.z = 0;
            ctl->waypoint_8  = 1;
            // fall through
        case 1:
            if (wp->param_F & 0x40)
            {
                point = &stcom31_D_0050[ctl->waypoint_8];
            }
            else
            {
                point = &stcom31_D_0020[ctl->waypoint_8];
            }
            stcom31_E_0010[0].x = point->x;
            stcom31_E_0010[0].y = 0;
            stcom31_E_0010[0].z = point->z;
            step             = func_80031BEC(&wp->position, stcom31_E_0010, wp->rotation.v.y, 0x20);
            wp->velocity.v.z = step * 4;
            wp->rotation.v.z = (uint16)(step << 3) >> 4;
            wp->rotation.v.y = (wp->rotation.v.y + step) & 0xFFF;
            func_8002FEA4(wp, wp->velocity.v.x, 0, wp->velocity.v.z);
            dx = wp->position.x - (point->x - (point->width >> 1));
            dz = wp->position.z - (point->z - (point->depth >> 1));
            if ((uint32)dx < point->width && (uint32)dz < point->depth)
            {
                if (ctl->waypoint_8 == stcom31_E_0020)
                {
                    ctl->flags_0 |= 1;
                    wp->velocity.v.x = 0;
                    wp->velocity.v.y = 0;
                    wp->velocity.v.z = 0;
                    wp->rotation.v.x = 0;
                    wp->rotation.v.z = 0;
                }
                ctl->waypoint_8++;
            }
            stcom31_E_0010[0].x -= wp->position.x;
            stcom31_E_0010[0].z -= wp->position.z;
            if (stcom31_E_0010[0].x * stcom31_E_0010[0].x +
                    stcom31_E_0010[0].z * stcom31_E_0010[0].z >
                0x4000)
            {
                if (wp->velocity.v.x < 0x320)
                {
                    wp->velocity.v.x += wp->accel.x;
                }
            }
            else if (wp->velocity.v.x > 0x160)
            {
                wp->velocity.v.x -= wp->accel.x;
            }
            break;
    }
    if (!(STCOM31_FRAME & 3))
    {
        for (i = 0; i < 4; i++)
        {
            effect = func_80031618();
            if (effect == NULL)
            {
                break;
            }
            effect->flags_0   = 1;
            effect->kind_2    = 0x83;
            effect->variant_3 = 1;
            stcom31_E_0018[0] = wp->position;
            stcom31_E_0000    = wp->position_fixed;
            set               = ctl->random_2 & 3;
            func_8002FFC4(stcom31_E_0018, &stcom31_E_0000, wp->rotation.v.y,
                          stcom31_D_0078[set][i].x, stcom31_D_0078[set][i].y,
                          stcom31_D_0078[set][i].z);
            effect->sprite.pos_8[0] = stcom31_E_0018[0].x;
            effect->sprite.pos_8[1] = stcom31_E_0018[0].y;
            effect->sprite.pos_8[2] = stcom31_E_0018[0].z;
        }
    }
}
