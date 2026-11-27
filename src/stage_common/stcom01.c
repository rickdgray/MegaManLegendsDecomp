#include "common.h"
#include "stage_common/stcom01.h"

// Shared stage code, linked into 18 stages: r3_st03, r3_st04, r3_st05, r3_st06, r3_st08,
// r3_st0a, r3_st0b, r3_st0c, r3_st0d, r3_st0f, r3_st10, r3_st11, r3_st12, r3_st13, r3_st19,
// r3_st1a, r3_st1b and r3_st1c. Each stage compiles this file against its own copy of the
// assembly (TARGET_ASM, set by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom01"

void stcom01_func_0000(STCOM01_WORK *wp)
{
    stcom01_D_055C[wp->routine_0](wp);
}

void stcom01_func_003C(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    wp->be_flag |= 2;
    if (wp->type != 0)
    {
        Model_work_init(wp, &wp->type);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    if (wp->id == 0x26)
    {
        wp->scale.words[0] = 0x01D701D7;
        wp->scale.words[1] = 0x1D7;
    }
    else if (wp->id == 0x24 || wp->id == 0x30 || wp->id == 0x42 || wp->id == 0x53 || wp->id == 0x5C || wp->id == 0x44)
    {
        wp->scale.words[0] = 0x021A021A;
        wp->scale.words[1] = 0x21A;
    }
    else if (wp->id == 0x5E)
    {
        wp->scale.words[0] = 0x020001C0;
        wp->scale.words[1] = 0x180;
    }
    else
    {
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
    }
    wp->scale.v.pad = 0x4210;
    ctl->flags      = 2;
    ctl->timer      = 0;
    if (wp->param_D & 0x10)
    {
        ctl->range_20 = 10000;
    }
    else
    {
        ctl->range_20 = 5000;
    }
    ctl->pos_C     = wp->position;
    ctl->value_A   = wp->rotation.y;
    wp->data_10    = stcom01_D_0550;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->velocity.x = 0;
    wp->velocity.z = 0;
    wp->value_6E   = 0;
    wp->value_B0   = 0;
    wp->value_B2   = 0;
    wp->value_78   = 0;
    wp->routine_0  = 1;
    wp->routine_2  = 0;
    wp->routine_3  = 0;
    wp->routine_1  = wp->param_D & 7;
    func_800322A8(wp, 0, 0);
    stcom01_func_01FC(wp);
}

void stcom01_func_01FC(STCOM01_WORK *wp)
{
    STCOM01_PARAM3 *param;
    STCOM01_CTL *ctl;

    param = &stcom01_D_0000[wp->id];
    ctl   = &wp->ctl;
    if (stcom01_func_2968(wp, 0, ctl->range_20))
    {
        wp->anim_prev_AD        = wp->anim_AC;
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed;
        wp->rotation_prev       = wp->rotation;
        wp->scale.v.pad         = 0x4210;
        if (ctl->flags & 2)
        {
            stcom01_func_27C0(wp);
        }
        stcom01_D_0568[wp->routine_1](wp);
        if (!(wp->param_D & 0x20))
        {
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
        }
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
        if (wp->be_flag & 2)
        {
            Model_Shadow_Trans(wp, param->a, param->b, param->c);
        }
        if (ctl->flags & 2)
        {
            func_80051B68(wp, 1, -1, 0);
        }
        else
        {
            func_80051B68(wp, 3, -1, 0);
        }
    }
}

void stcom01_func_03B8(STCOM01_WORK *wp)
{
    func_80031824(wp);
}

void stcom01_func_03D8(STCOM01_WORK *wp)
{
    stcom01_D_058C[wp->routine_2](wp);
}

void stcom01_func_0414(STCOM01_WORK *wp)
{
    uint8 *tbl;

    tbl           = stcom01_D_059C[wp->param_E & 3];
    wp->anim_AC   = stcom01_func_28C8(wp->id);
    wp->ctl.timer = tbl[rand() & 0xF];
    wp->routine_2++;
}

void stcom01_func_0484(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        if (wp->id == 0x49)
        {
            wp->ctl.timer = 0x78;
        }
        else
        {
            wp->ctl.timer = 1;
        }
        wp->anim_AC = stcom01_func_2828(wp->id);
        wp->routine_2++;
    }
}

void stcom01_func_04F8(STCOM01_WORK *wp)
{
    sint32 unused[1]; // never used; retail reserves its 8-byte frame

    if (wp->ctl.timer == 0 || --wp->ctl.timer == 0)
    {
        if (wp->state_A7 < 0)
        {
            if (wp->id == 0x49)
            {
                wp->anim_AC = 9;
                wp->routine_2++;
            }
            else
            {
                wp->routine_2 = 0;
            }
        }
    }
}

void stcom01_func_0560(STCOM01_WORK *wp)
{
    if (wp->state_A7 < 0)
    {
        wp->routine_2 = 0;
    }
}

void stcom01_func_057C(STCOM01_WORK *wp)
{
    stcom01_D_05DC[wp->routine_2](wp);
}

void stcom01_func_05B8(STCOM01_WORK *wp)
{
    wp->ctl.value_14 = 0;
    wp->ctl.value_16 = wp->ctl.value_1E = wp->param_E * 8;
    wp->velocity.x                      = stcom01_func_2918(wp, 1);
    wp->velocity.y                      = 0;
    wp->velocity.z                      = 0;
    wp->routine_2++;
}

void stcom01_func_0610(STCOM01_WORK *wp)
{
    uint8 *tbl;
    uint8 *row;
    STCOM01_CTL *ctl;
    uint8 step;

    tbl  = stcom01_D_0648[0];
    row  = &stcom01_D_0608[wp->param_D & 0x30];
    step = row[rand() & 0xF];
    ctl  = &wp->ctl;
    switch (step)
    {
        case 0:
            wp->anim_AC    = stcom01_func_28D8(wp->id);
            wp->velocity.x = stcom01_func_2918(wp, 1);
            break;
        case 1:
            tbl += 16;
            wp->anim_AC = stcom01_func_28C8(wp->id);
            break;
        default:
            if (ctl->value_16 == ctl->value_1E)
            {
                step = 0xFF;
                break;
            }
            wp->anim_AC = stcom01_func_28D8(wp->id);
            if (ctl->value_14 != 0)
            {
                wp->rot_goal_64 = ctl->value_A;
            }
            else
            {
                wp->rot_goal_64 = (ctl->value_A + 0x800) & 0xFFF;
            }
            tbl = stcom01_D_0668;
            break;
    }
    ctl->timer = tbl[rand() & 0xF];
    if (step != 0xFF)
    {
        wp->routine_2 += step + 1;
    }
}

void stcom01_func_0774(STCOM01_WORK *wp)
{
    Obj_pos_set(wp, wp->velocity.x, 0, 0);
    if (--wp->ctl.value_16 == 0)
    {
        if (wp->ctl.value_14 != 0)
        {
            wp->rot_goal_64 = (wp->param_F & 0xF) << 8;
        }
        else
        {
            wp->rot_goal_64 = (wp->param_F >> 4) << 8;
        }
        wp->routine_2 = 5;
    }
    else if (--wp->ctl.timer == 0)
    {
        wp->routine_2 = 1;
    }
    else if (stcom01_func_2968(wp, 0x40, 0x64))
    {
        wp->anim_AC   = stcom01_func_28C8(wp->id);
        wp->ctl.timer = 0x3C;
        wp->routine_2 = 9;
    }
}

void stcom01_func_0858(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        wp->routine_2 = 1;
    }
}

void stcom01_func_0880(STCOM01_WORK *wp)
{
    sint16 step;

    step = Angle_diff_clamp(wp->rot_goal_64, wp->rotation.y, 0x40);
    if (step == 0)
    {
        wp->routine_2    = 1;
        wp->ctl.value_14 = 1 - wp->ctl.value_14;
        wp->ctl.value_16 = wp->ctl.value_1E - wp->ctl.value_16;
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
}

void stcom01_func_08FC(STCOM01_WORK *wp)
{
    sint16 step;

    step = Angle_diff_clamp(wp->rot_goal_64, wp->rotation.y, 0x40);
    if (step == 0)
    {
        wp->ctl.timer = 0x14;
        wp->anim_AC   = stcom01_func_28C8(wp->id);
        wp->routine_2++;
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
}

void stcom01_func_0978(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        wp->anim_AC   = stcom01_func_2828(wp->id);
        wp->ctl.timer = 0x46;
        wp->routine_2++;
    }
}

void stcom01_func_09DC(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->state_A7 < 0 && wp->id != 0x49)
    {
        wp->anim_AC = stcom01_func_28C8(wp->id);
    }
    if (--ctl->timer == 0)
    {
        if (wp->id == 0x49)
        {
            wp->anim_AC   = 9;
            wp->routine_2 = 10;
        }
        else
        {
            wp->anim_AC = stcom01_func_28D8(wp->id);
            wp->routine_2++;
        }
        if (ctl->value_14 != 0)
        {
            wp->rot_goal_64 = ctl->value_A;
        }
        else
        {
            wp->rot_goal_64 = (ctl->value_A + 0x800) & 0xFFF;
        }
        ctl->value_16 = ctl->value_1E;
    }
}

void stcom01_func_0AC4(STCOM01_WORK *wp)
{
    sint16 step;

    step           = Angle_diff_clamp(wp->rot_goal_64, wp->rotation.y, 0x40);
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
    if (step == 0)
    {
        wp->routine_2 = 1;
        if (wp->ctl.value_14 != 0)
        {
            wp->position         = wp->ctl.pos_C;
            wp->position_fixed.x = wp->position.x << 16;
            wp->position_fixed.y = wp->position.y << 16;
            wp->position_fixed.z = wp->position.z << 16;
            wp->rotation.y       = wp->ctl.value_A;
        }
        wp->ctl.value_14 = 1 - wp->ctl.value_14;
    }
}

void stcom01_func_0B80(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        if (stcom01_func_2968(wp, 0x40, 0x64))
        {
            if (wp->ctl.value_16 >= wp->ctl.value_1E - 5)
            {
                wp->ctl.timer = 0x3C;
            }
            else
            {
                wp->anim_AC     = stcom01_func_28D8(wp->id);
                wp->routine_2   = 4;
                wp->rot_goal_64 = (wp->rotation.y + 0x800) & 0xFFF;
            }
        }
        else
        {
            wp->routine_2 = 1;
        }
    }
}

void stcom01_func_0C24(STCOM01_WORK *wp)
{
    if (wp->state_A7 < 0)
    {
        wp->routine_2 = 8;
        wp->anim_AC   = stcom01_func_28D8(wp->id);
    }
}

void stcom01_func_0C68(STCOM01_WORK *wp)
{
    stcom01_D_0678[wp->routine_2](wp);
}

void stcom01_func_0CA4(STCOM01_WORK *wp)
{
    wp->ctl.value_14 = 0;
    wp->ctl.value_16 = 0;
    wp->ctl.value_1A = 0;
    wp->velocity.y   = 0;
    wp->velocity.z   = 0;
    wp->ctl.value_1E = wp->param_E * 8;
    wp->ctl.value_18 = wp->ctl.value_1E;
    wp->routine_2++;
}

void stcom01_func_0CD8(STCOM01_WORK *wp)
{
    uint8 *tbl;
    STCOM01_CTL *ctl;

    tbl = stcom01_D_06A4[0];
    ctl = &wp->ctl;
    switch (stcom01_D_0694[rand() & 0xF])
    {
        case 0:
            if (ctl->value_16 == 0)
            {
                wp->routine_2 += 1;
            }
            else
            {
                wp->routine_2 += 2;
            }
            if (wp->param_D & 8)
            {
                wp->velocity.x = stcom01_func_2918(wp, 2);
                wp->anim_AC    = 2;
            }
            else
            {
                wp->velocity.x = stcom01_func_2918(wp, 1);
                wp->anim_AC    = stcom01_func_28D8(wp->id);
            }
            tbl = stcom01_D_06A4[0];
            break;
        case 1:
            tbl += 16;
            wp->anim_AC = stcom01_func_28C8(wp->id);
            wp->routine_2 += 3;
            break;
        case 2:
            tbl += 32;
            wp->anim_AC   = stcom01_func_28D8(wp->id);
            ctl->value_1C = (wp->rotation.y + 0x800) & 0xFFF;
            wp->routine_2 += 4;
            break;
    }
    ctl->timer = tbl[rand() & 0xF];
}

void stcom01_func_0E44(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    if (ctl->value_1A == 0 && ctl->value_14 == 0 && ctl->value_18 == ctl->value_1E)
    {
        wp->rotation.y       = ctl->value_A;
        wp->position         = ctl->pos_C;
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->position_fixed.z = wp->position.z << 16;
    }
    else if (ctl->value_1A != 0 && ctl->value_14 == 0 && ctl->value_18 == 1)
    {
        wp->rotation.y       = (ctl->value_A + 0x800) & 0xFFF;
        wp->position         = ctl->pos_C;
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.y = wp->position.y << 16;
        wp->position_fixed.z = wp->position.z << 16;
    }
    Obj_pos_set(wp, wp->velocity.x, 0, 0);
    if (--ctl->value_18 == 0)
    {
        wp->rot_goal_64 = (wp->rotation.y + 0x800) & 0xFFF;
        ctl->value_16   = 1 - ctl->value_16;
        wp->routine_2   = 1;
    }
    else if (--ctl->timer == 0)
    {
        wp->routine_2 = 1;
    }
    else if (stcom01_func_2968(wp, 0x40, 0x64))
    {
        wp->anim_AC   = stcom01_func_28C8(wp->id);
        ctl->timer    = 0x3C;
        wp->routine_2 = 6;
    }
}

void stcom01_func_1018(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;
    sint16 step;

    ctl  = &wp->ctl;
    step = Angle_diff_clamp(wp->rot_goal_64, wp->rotation.y, (sint8)wp->param_F);
    if ((ctl->value_1A == 0 && step < 0) || (ctl->value_1A != 0 && step > 0))
    {
        step = -step;
    }
    if (step == 0)
    {
        ctl->value_14 = 1 - ctl->value_14;
        ctl->value_18 = ctl->value_1E;
        ctl->value_16 = 1 - ctl->value_16;
        wp->routine_2 = 1;
    }
    else if (--ctl->timer == 0)
    {
        wp->routine_2 = 1;
    }
    else if (stcom01_func_2968(wp, 0x40, 0x64))
    {
        wp->anim_AC   = stcom01_func_28C8(wp->id);
        ctl->timer    = 0x3C;
        wp->routine_2 = 6;
        return;
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
    Obj_pos_set(wp, wp->velocity.x, 0, 0);
}

void stcom01_func_1148(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        wp->routine_2 = 1;
    }
}

void stcom01_func_1170(STCOM01_WORK *wp)
{
    sint16 step;

    step = Angle_diff_clamp(wp->ctl.value_1C, wp->rotation.y, wp->ctl.timer);
    if (step == 0)
    {
        if (wp->ctl.value_16 != 0)
        {
            wp->ctl.value_14 = 1 - wp->ctl.value_14;
        }
        wp->routine_2    = 1;
        wp->ctl.value_1A = 1 - wp->ctl.value_1A;
        wp->ctl.value_18 = wp->ctl.value_1E - wp->ctl.value_18 + 1;
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
}

void stcom01_func_1218(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        if (stcom01_func_2968(wp, 0x40, 0x64))
        {
            wp->anim_AC      = stcom01_func_28D8(wp->id);
            wp->ctl.timer    = 0x64;
            wp->routine_2    = 5;
            wp->ctl.value_1C = (wp->rotation.y + 0x800) & 0xFFF;
        }
        else
        {
            wp->routine_2 = 1;
        }
    }
}

void stcom01_func_12A4(STCOM01_WORK *wp)
{
    stcom01_D_06D4[wp->routine_2](wp);
}

void stcom01_func_12E0(STCOM01_WORK *wp)
{
    wp->velocity.x   = stcom01_func_2918(wp, 1);
    wp->velocity.y   = 0;
    wp->velocity.z   = 0;
    wp->ctl.value_14 = wp->param_E * 16;
    wp->ctl.value_16 = wp->param_F * 16;
    wp->routine_2++;
}

void stcom01_func_133C(STCOM01_WORK *wp)
{
    uint8 *choice_tbl;
    STCOM01_CTL *ctl;
    uint8 *flag_tbl;
    uint8 *wait_tbl;
    uint8 step;
    uint16 dx;
    uint16 dz;

    ctl = &wp->ctl;
    if (wp->id == 0x2A)
    {
        choice_tbl = stcom01_D_0700;
        flag_tbl   = stcom01_D_0720;
        wait_tbl   = stcom01_D_0730;
    }
    else
    {
        choice_tbl = stcom01_D_06F0;
        flag_tbl   = stcom01_D_0710;
        wait_tbl   = stcom01_D_0730;
    }
    step = choice_tbl[rand() & 0xF];
    switch (step)
    {
        case 0:
            if ((wp->param_D & 8) || flag_tbl[rand() & 0xF])
            {
                wp->anim_AC    = 2;
                wp->velocity.x = stcom01_func_2918(wp, 2);
            }
            else
            {
                wp->anim_AC    = stcom01_func_28D8(wp->id);
                wp->velocity.x = stcom01_func_2918(wp, 1);
            }
            break;
        case 1:
            wp->anim_AC = stcom01_func_28C8(wp->id);
            break;
        case 2:
            dx = wp->position.x - ctl->pos_C.x + (ctl->value_14 >> 1);
            dz = wp->position.z - ctl->pos_C.z + (ctl->value_16 >> 1);
            if (dx < ctl->value_14 && dz < ctl->value_16)
            {
                wp->velocity.x = stcom01_func_2918(wp, 1);
                wp->anim_AC    = 2;
            }
            else
            {
                step = 0xFF;
            }
            break;
        default:
            wp->rot_goal_64 = rand() & 0xFFF;
            wp->anim_AC     = stcom01_func_28D8(wp->id);
            ctl->value_1E   = 1;
            break;
    }
    ctl->timer = wait_tbl[rand() & 0xF];
    if (step != 0xFF)
    {
        wp->routine_2 += step + 1;
    }
}

void stcom01_func_1564(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    if (stcom01_func_2968(wp, 0x40, 0x64))
    {
        if (wp->id == 0x2A)
        {
            ctl->value_18 = wp->routine_2;
            ctl->value_1A = wp->anim_AC;
            wp->routine_2 = 6;
            return;
        }
        wp->routine_2 = 1;
        return;
    }
    Obj_pos_set(wp, wp->velocity.x, 0, 0);
    if (ctl->pos_C.x + ctl->value_14 < wp->position.x)
    {
        wp->position.x  = ctl->pos_C.x + ctl->value_14;
        wp->routine_2   = 5;
        ctl->value_1E   = 2;
        wp->rot_goal_64 = 0x1000 - wp->rotation.y;
        ctl->timer += 10;
    }
    else if (wp->position.x < ctl->pos_C.x - ctl->value_14)
    {
        wp->position.x  = ctl->pos_C.x - ctl->value_14;
        wp->routine_2   = 5;
        ctl->value_1E   = 2;
        wp->rot_goal_64 = 0x1000 - wp->rotation.y;
        ctl->timer += 10;
    }
    if (ctl->pos_C.z + ctl->value_16 < wp->position.z)
    {
        wp->position.z  = ctl->pos_C.z + ctl->value_16;
        wp->routine_2   = 5;
        wp->rot_goal_64 = (0x800 - wp->rotation.y) & 0xFFF;
        ctl->value_1E   = 2;
        ctl->timer += 10;
    }
    else if (wp->position.z < ctl->pos_C.z - ctl->value_16)
    {
        wp->position.z  = ctl->pos_C.z - ctl->value_16;
        wp->routine_2   = 5;
        wp->rot_goal_64 = (0x800 - wp->rotation.y) & 0xFFF;
        ctl->value_1E   = 2;
        ctl->timer += 10;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    if (--ctl->timer == 0)
    {
        wp->routine_2 = 1;
    }
}

void stcom01_func_1704(STCOM01_WORK *wp)
{
    if (--wp->ctl.timer == 0)
    {
        wp->routine_2 = 1;
    }
}

void stcom01_func_172C(STCOM01_WORK *wp)
{
    if (stcom01_func_2968(wp, 0x40, 0x64))
    {
        wp->ctl.value_18 = wp->routine_2;
        wp->ctl.value_1A = wp->anim_AC;
        wp->routine_2    = 6;
        wp->anim_AC      = stcom01_func_28C8(wp->id);
    }
    else
    {
        if (--wp->ctl.timer == 0)
        {
            wp->routine_2 = 1;
        }
        Obj_pos_set(wp, wp->velocity.x, 0, 0);
        wp->rotation.y = (wp->rotation.y + 0x80) & 0xFFF;
    }
}

void stcom01_func_17D4(STCOM01_WORK *wp)
{
    sint16 step;

    step = Angle_diff_clamp(wp->rot_goal_64, wp->rotation.y, 0x40);
    if (step == 0)
    {
        wp->routine_2 = wp->ctl.value_1E;
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
}

void stcom01_func_1838(STCOM01_WORK *wp)
{
    wp->rot_goal_64  = (wp->rotation.y + 0x800) & 0xFFF;
    wp->anim_AC      = stcom01_func_28D8(wp->id);
    wp->ctl.value_1E = 1;
    wp->routine_2    = 5;
}

void stcom01_func_1888(STCOM01_WORK *wp)
{
    stcom01_D_0740[wp->ctl.routine](wp);
}

void stcom01_func_18C4(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    ctl->routine++;
    ctl->value_4 = wp->rotation.y;
    ctl->value_2 = wp->anim_AC;
    wp->anim_AC  = stcom01_func_28C8(wp->id);
    ctl->turn    = STCOM_ABS(Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800)) >> 3;
    func_80063BC8(&wp->position, 0, 0, wp->param_C);
}

void stcom01_func_19B0(STCOM01_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (!(wp->param_D & 0x40))
    {
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, ctl->turn)) & 0xFFF;
        if (Moji_flag & 0x200000)
        {
            wp->anim_AC = stcom01_func_2828(wp->id);
            ctl->routine++;
        }
    }
    if (D_800987B0[0] == 0)
    {
        ctl->routine = 3;
        ctl->flags &= ~4;
        wp->anim_AC = stcom01_func_28C8(wp->id);
    }
}

void stcom01_func_1A84(STCOM01_WORK *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn)) & 0xFFF;
    if (wp->state_A7 < 0)
    {
        wp->anim_AC = stcom01_func_28C8(wp->id);
        wp->ctl.routine--;
    }
    if (D_800987B0[0] == 0)
    {
        wp->ctl.routine = 3;
        wp->ctl.flags &= ~4;
        wp->anim_AC = stcom01_func_28C8(wp->id);
    }
}

uint8 stcom01_func_1B28(STCOM01_WORK *wp)
{
    switch (wp->ctl.value_2)
    {
        case 1:
            switch (wp->routine_2)
            {
                case 4:
                case 5:
                case 8:
                    return 1;
            }
            break;
        case 3:
            switch (wp->routine_2)
            {
                case 4:
                case 5:
                    return 1;
            }
            break;
    }
    return 0;
}

void stcom01_func_1BAC(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;
    sint16 step;

    ctl  = &wp->ctl;
    step = Angle_diff_clamp(ctl->value_4, wp->rotation.y, ctl->turn);
    if (step == 0 || (wp->param_D & 0x80) || stcom01_func_1B28(wp))
    {
        wp->anim_AC = ctl->value_2;
        ctl->flags |= 2;
        wp->routine_1 = wp->param_D & 7;
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
    }
}

void stcom01_func_1C70(STCOM01_WORK *wp)
{
    stcom01_D_0750[wp->ctl.routine](wp);
}

void stcom01_func_1CAC(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    ctl->routine++;
    ctl->value_4 = wp->rotation.y;
    ctl->value_2 = wp->anim_AC;
    wp->anim_AC  = stcom01_func_28C8(wp->id);
    ctl->turn    = STCOM_ABS(Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800)) >> 3;
    func_80063BC8(&wp->position, 0, 0, wp->param_C);
}

void stcom01_func_1D98(STCOM01_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (!(wp->param_D & 0x40))
    {
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, ctl->turn)) & 0xFFF;
        if (Moji_flag & 0x200000)
        {
            wp->anim_AC = stcom01_func_2828(wp->id);
            ctl->routine++;
        }
    }
    if (D_800987B0[0] == 0)
    {
        ctl->routine = 3;
        ctl->flags &= ~4;
        wp->anim_AC = stcom01_func_28C8(wp->id);
    }
}

void stcom01_func_1E6C(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;
    sint16 step;

    ctl  = &wp->ctl;
    step = Angle_diff_clamp(ctl->value_4, wp->rotation.y, ctl->turn);
    if (step == 0 || (wp->param_D & 0x80) || stcom01_func_1B28(wp))
    {
        wp->anim_AC = ctl->value_2;
        ctl->flags |= 2;
        wp->routine_1 = wp->param_D & 7;
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
    }
}

void stcom01_func_1F30(STCOM01_WORK *wp)
{
    stcom01_D_075C[wp->ctl.routine](wp);
}

void stcom01_func_1F6C(STCOM01_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM01_CTL *ctl;
    uint8 param;

    ctl          = &wp->ctl;
    ctl->value_4 = wp->rotation.y;
    ctl->value_2 = wp->anim_AC;
    pl           = &Player_work;
    if (stcom01_func_2968(wp, 0xFA, 0xC8))
    {
        wp->anim_AC = stcom01_func_28C8(wp->id);
        ctl->turn   = STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
        ctl->routine++;
        param = wp->param_C;
    }
    else
    {
        ctl->turn = Muku(&wp->position, &pl->position, wp->rotation.y, 0x20) > 0;
        if (ctl->turn)
        {
            wp->anim_AC = 3;
        }
        else
        {
            wp->anim_AC = 4;
        }
        ctl->routine = 4;
        param        = wp->param_C + 1;
    }
    func_80063BC8(&wp->position, 0, 0, param);
}

void stcom01_func_20C0(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    if (D_800987B0[0] == 0)
    {
        ctl->flags &= ~4;
        if (wp->ctl.turn != 0)
        {
            wp->anim_AC = 5;
        }
        else
        {
            wp->anim_AC = 6;
        }
        ctl->routine++;
    }
}

void stcom01_func_2110(STCOM01_WORK *wp)
{
    if (wp->state_A7 < 0)
    {
        wp->anim_AC = stcom01_func_28C8(wp->id);
        wp->anim_AC = wp->ctl.value_2;
        wp->ctl.flags |= 2;
        wp->routine_1 = wp->param_D & 7;
    }
}

void stcom01_func_2174(STCOM01_WORK *wp)
{
    stcom01_D_0774[wp->ctl.routine](wp);
}

void stcom01_func_21B0(STCOM01_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM01_CTL *ctl;
    STCOM_FIXED_VECTOR v;
    STCOM_SVECTOR pos;

    ctl           = &wp->ctl;
    ctl->value_4  = wp->rotation.y;
    ctl->value_2  = wp->anim_AC;
    pl            = &Player_work;
    pl->routine_1 = 0x10;
    pl->value_0a  = 0;
    pl->be_flag &= ~2;
    pos = wp->position;
    v.x = wp->position.x;
    v.y = wp->position.y - 0x30;
    v.z = wp->position.z;
    func_80039FAC(&v, 0x100, Angle_xz_svector(&pos, &pl->position), D_800A396C + 0x6C);
    wp->anim_AC = stcom01_func_28C8(wp->id);
    ctl->turn   = STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
    ctl->routine++;
}

void stcom01_func_2310(STCOM01_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (func_8003A13C() == 0)
    {
        func_80063BC8(&wp->position, 0xD, 0, wp->param_C);
        wp->ctl.routine++;
    }
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->ctl.turn)) & 0xFFF;
}

void stcom01_func_2398(STCOM01_WORK *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn)) & 0xFFF;
    if (D_800987B0[0] == 0)
    {
        wp->ctl.flags &= ~4;
        wp->ctl.routine += 2;
        wp->anim_AC = stcom01_func_28C8(wp->id);
        func_80039E18();
    }
    else if (Game_work.mode_0 == 6)
    {
        wp->ctl.routine++;
    }
}

void stcom01_func_2450(STCOM01_WORK *wp)
{
    if (Game_work.mode_0 == 3)
    {
        MojiTaskKill();
        MojiTaskExec2(0, 0xDC);
        wp->ctl.routine--;
    }
}

void stcom01_func_24A8(STCOM01_WORK *wp)
{
    STCOM_PL_WORK *pl;
    sint16 step;

    pl   = &Player_work;
    step = Angle_diff_clamp(wp->ctl.value_4, wp->rotation.y, wp->ctl.turn);
    if (step == 0 || (wp->param_D & 0x80))
    {
        if (func_8003A13C() == 0)
        {
            pl->routine_1 = 0;
            pl->value_0a  = 0;
            pl->be_flag |= 2;
            wp->anim_AC = wp->ctl.value_2;
            wp->ctl.flags |= 2;
            wp->routine_1 = wp->param_D & 7;
        }
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
}

void stcom01_func_257C(STCOM01_WORK *wp)
{
    stcom01_D_0788[wp->ctl.routine](wp);
}

void stcom01_func_25B8(STCOM01_WORK *wp)
{
    STCOM01_CTL *ctl;

    ctl = &wp->ctl;
    ctl->routine++;
    ctl->value_4 = wp->rotation.y;
    ctl->value_2 = wp->anim_AC;
    wp->anim_AC  = 8;
    ctl->turn    = STCOM_ABS(Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800)) >> 3;
    func_80063BC8(&wp->position, 0, 0, wp->param_C);
}

void stcom01_func_26A0(STCOM01_WORK *wp)
{
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->ctl.turn)) & 0xFFF;
    if (D_800987B0[0] == 0)
    {
        wp->anim_AC = 9;
        wp->ctl.flags &= ~4;
        wp->ctl.routine++;
    }
}

void stcom01_func_2720(STCOM01_WORK *wp)
{
    sint16 step;

    step = Angle_diff_clamp(wp->ctl.value_4, wp->rotation.y, wp->ctl.turn);
    if (wp->state_A7 < 0 && step == 0)
    {
        wp->anim_AC = stcom01_func_28C8(wp->id);
        wp->anim_AC = wp->ctl.value_2;
        wp->ctl.flags |= 2;
        wp->routine_1 = wp->param_D & 7;
    }
    wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
}

void stcom01_func_27C0(STCOM01_WORK *wp)
{
    STCOM01_WORK *p;
    STCOM01_CTL *ctl;

    p   = Player_work.target_184;
    ctl = &wp->ctl;
    if (p == wp)
    {
        if (p->id == 0x34)
        {
            p->routine_1 = 6;
        }
        else if (p->id == 0x11)
        {
            p->routine_1 = 7;
        }
        else if (p->id == 0x49)
        {
            p->routine_1 = 8;
        }
        else
        {
            p->routine_1 = 4;
        }
        ctl->routine = 0;
        ctl->flags   = (ctl->flags | 4) & ~2;
    }
}

sint32 stcom01_func_2828(uint8 kind)
{
    switch (kind)
    {
        case 0:
        case 0x39:
        case 0x50:
            return 0;
        case 0x11:
            return 1;
        case 0x2A:
            return 9;
        case 0x53:
            return (rand() & 1) | 8;
    }
    return 8;
}

sint32 stcom01_func_28C8(uint8 kind)
{
    return kind == 0x11;
}

sint32 stcom01_func_28D8(uint8 kind)
{
    switch (kind)
    {
        case 0x39:
        case 0x4C:
        case 0x4D:
            return 0;
    }
    return 1;
}

sint32 stcom01_func_2918(STCOM01_WORK *wp, uint8 mode)
{
    if (mode != 1)
    {
        if (wp->id == 0x2A)
        {
            return 0x40;
        }
        if (wp->id == 5)
        {
            return 0x140;
        }
        return 0x180;
    }
    return stcom01_D_04E0[wp->id];
}

uint8 stcom01_func_2968(STCOM01_WORK *wp, sint32 ofs, sint32 range)
{
    STCOM_FIXED_VECTOR v;
    uint16 dx;
    uint16 dz;

    func_80030058(&v, wp->rotation.y, ofs << 4, 0, 0);
    dx = range + ((wp->position.x + (v.x >> 16)) - Player_work.position.x);
    dz = range + ((wp->position.z + (v.z >> 16)) - Player_work.position.z);
    if (dx < (uint16)range * 2 && dz < (uint16)range * 2)
    {
        return 1;
    }
    return 0;
}
