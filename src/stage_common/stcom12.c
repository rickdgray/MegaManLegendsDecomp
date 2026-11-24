#include "common.h"
#include "stage_common/stcom12.h"

// Shared stage code, linked into 6 stages: r3_st03, r3_st08, r3_st10, r3_st12, r3_st13 and
// r3_st1b. Each stage compiles this file against its own copy of the assembly (TARGET_ASM, set
// by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom12"

void stcom12_func_0000(STCOM12_WORK *wp)
{
    STCOM12_CTL *ctl;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    stcom12_D_0000[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->routine_3 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_3++;
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_0 != 7)
    {
        func_80051B68(wp, 2, -1, 0);
    }
    if (wp->routine_0 == 1)
    {
        ctl->pos_14 = wp->position;
        ctl->pos_14.y -= 30;
    }
    ctl->hit_C = 0;
}

void stcom12_func_0164(STCOM12_WORK *wp)
{
    uint16 scale;

    wp->rotation.x = 0;
    wp->rotation.y = 0;
    wp->rotation.z = 0;
    wp->turn_64    = 0x40;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    scale           = stcom12_D_0038[wp->param_E];
    wp->scale.v.pad = 0x4210;
    wp->data_78     = stcom12_D_002C;
    wp->scale.v.x = wp->scale.v.y = wp->scale.v.z = scale;
    wp->position.y                                = Obj_ceiling_height_get(wp);
    wp->position_fixed.y                          = wp->position.y << 16;
    wp->ctl.home_24                               = wp->position;
    wp->data_10                                   = stcom12_D_0020;
    wp->ctl.dist_8                                = 0x7FFFFFFF;
    wp->value_6E                                  = 0;
    wp->value_B0                                  = 0;
    wp->value_B2                                  = 0;
    wp->velocity.x                                = 0;
    wp->velocity.y                                = 0;
    wp->velocity.z                                = 0;
    wp->value_74                                  = 0;
    wp->param_E                                   = 0;
    wp->param_F                                   = 0;
    wp->routine_0                                 = 0;
    wp->routine_1                                 = 0;
    wp->routine_2                                 = 0;
    wp->routine_3                                 = 0;
    wp->ctl.counter_0                             = 0;
    wp->ctl.hit_C                                 = 0;
    wp->ctl.value_10                              = 0;
    switch (wp->variant_3)
    {
        case 0:
        default:
            func_800322A8(wp, 1, 0);
            wp->routine_0 = 1;
            break;
        case 1:
            func_800322A8(wp, 3, 0);
            wp->routine_0 = 3;
            break;
        case 2:
            func_800322A8(wp, 2, 0);
            wp->routine_0 = 7;
            wp->flags_0 &= ~2;
            break;
    }
}

void stcom12_func_02E4(STCOM12_WORK *wp)
{
    func_80031824(wp);
}

void stcom12_func_0304(STCOM12_WORK *wp)
{
    STCOM12_CTL *ctl;
    uint32 hit;
    sint16 step;

    ctl = &wp->ctl;
    if (ctl->hit_C & 0x20000000)
    {
        func_8001E3F0(2);
        wp->routine_0 = 6;
        wp->routine_1 = 0;
        return;
    }
    if (stcom12_func_0DE4(wp))
    {
        wp->routine_0 = 4;
        wp->routine_1 = 0;
        return;
    }
    ctl->dist_8 = Obj_distance_xyz(&Player_work, wp);
    switch (wp->routine_1)
    {
        case 0:
            ctl->timer_4 = rand() & 0xFF;
            wp->routine_1++;
            // fall through
        case 1:
            if (!stcom12_func_0F98(wp))
            {
                break;
            }
            if (ctl->dist_8 < 300)
            {
                wp->velocity.x = 0x80;
                if (wp->anim_AC != 2)
                {
                    func_800322A8(wp, 2, 0);
                }
            }
            else
            {
                wp->velocity.x = 0x40;
                if (wp->anim_AC != 1)
                {
                    func_800322A8(wp, 1, 0);
                }
            }
            Obj_pos_set(wp, wp->velocity.x, 0, 0);
            hit = Obj_map_push_out(wp);
            stcom12_func_0E9C(wp, hit);
            if (wp->param_D != 0 && wp->param_D < (Distance_xyz(&wp->position, &ctl->home_24) >> 7))
            {
                wp->velocity.x = 0x80;
                if (wp->anim_AC != 2)
                {
                    func_800322A8(wp, 2, 0);
                }
                ctl->timer_4  = wp->param_D << 2;
                wp->routine_1 = 10;
                break;
            }
            stcom12_func_0D68(wp, hit);
            wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            stcom12_func_0F28(wp, hit);
            if (wp->velocity.y != 0)
            {
                break;
            }
            if (ctl->timer_4 == 0)
            {
                wp->routine_1++;
                ctl->timer_4 = (rand() & 0x1F) + 1;
            }
            else
            {
                ctl->timer_4--;
            }
            break;
        case 2:
            if (wp->state_A7 < 0)
            {
                func_800322A8(wp, 0, 0);
                wp->velocity.x = 0;
                wp->velocity.y = 0;
                wp->routine_1++;
            }
            // fall through
        case 3:
            if (--ctl->timer_4 == 0)
            {
                wp->routine_1 = 0;
            }
            break;
        case 10:
            step           = Muku(&wp->position, &ctl->home_24, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0)
            {
                wp->routine_1++;
            }
            break;
        case 11:
            if (!stcom12_func_0F98(wp))
            {
                break;
            }
            // fall through
        case 15:
            Obj_pos_set(wp, wp->velocity.x, 0, 0);
            stcom12_func_0E9C(wp, Obj_map_push_out(wp));
            if (--ctl->timer_4 == 0)
            {
                wp->routine_1 = 0;
            }
            break;
        case 20:
            step           = Angle_diff_clamp(ctl->goal_2, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0)
            {
                wp->routine_1 = 1;
            }
            break;
    }
}

void stcom12_func_0660(STCOM12_WORK *wp)
{
    uint32 dist;

    dist           = Obj_distance_xyz(&Player_work, wp);
    wp->ctl.dist_8 = dist;
    switch (wp->routine_1)
    {
        case 0:
            if (dist < 300)
            {
                func_800322A8(wp, 4, 0);
                wp->routine_3 = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            if (wp->state_A7 < 0)
            {
                func_800322A8(wp, 0, 0);
                wp->routine_0 = 1;
                wp->routine_1 = 0;
                wp->routine_3 = 0;
            }
            break;
    }
}

void stcom12_func_0710(STCOM12_WORK *wp)
{
    STCOM_PL_WORK *pl;
    sint16 step;

    step = 0;
    pl   = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (wp->anim_AC != 3)
            {
                func_800322A8(wp, 0, 0);
                wp->routine_3 = 0;
                wp->routine_1++;
            }
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step != 0 || func_8003A13C())
            {
                break;
            }
            MojiTaskExec2(0, wp->param_C);
            wp->routine_1++;
            break;
        case 2:
            if (Moji_flag & 0x8000000)
            {
                break;
            }
            if (Game_work.value_50 == 0x12 && wp->param_C == 0 && (Moji_flag & 0xFF) == 0)
            {
                wp->routine_1 = 20;
                break;
            }
            wp->routine_1++;
            break;
        case 4:
            if (func_8003A13C())
            {
                break;
            }
            pl->flags_bd &= ~0x40;
            pl->flags_0 |= 2;
            if (wp->anim_AC != 3)
            {
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
        case 20:
            wp->flags_0 &= ~2;
            wp->routine_1++;
            break;
        case 3:
        case 21:
            func_80039E18();
            wp->routine_1++;
            break;
        case 22:
            if (func_8003A13C())
            {
                break;
            }
            pl->flags_bd &= ~0x40;
            Sce_flag_on(0x238);
            pl->flags_0 |= 2;
            func_80031824(wp);
            break;
    }
}

void stcom12_func_08E8(STCOM12_WORK *wp)
{
    wp->routine_0 = 1;
    wp->routine_1 = 0;
}

void stcom12_func_08F8(STCOM12_WORK *wp)
{
    STCOM12_CTL *ctl;
    uint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_1)
    {
        case 0:
            wp->rotation.y = Player_work.rotation.y;
            wp->velocity.x = wp->velocity.y = 0x200;
            ctl->decel_1C                   = 0x18;
            ctl->value_1E = ctl->value_20 = 0;
            func_800322A8(wp, 4, 0);
            wp->routine_3 = 0;
            wp->routine_1++;
            // fall through
        case 1:
            if (ctl->hit_C & 0x2000000)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                if (wp->anim_AC != 0)
                {
                    func_800322A8(wp, 0, 0);
                    wp->routine_3 = 0;
                }
                break;
            }
            Obj_pos_set(wp, wp->velocity.x, 0, 0);
            hit = Obj_map_push_out(wp);
            if (hit)
            {
                Wall_reflect_spd(&wp->velocity, hit);
            }
            if (STCOM12_ABS(wp->velocity.x) <= STCOM12_ABS(ctl->decel_1C))
            {
                ctl->decel_1C  = 0;
                wp->velocity.x = 0;
            }
            else
            {
                wp->velocity.x = (wp->velocity.x >= 0) ? wp->velocity.x - ctl->decel_1C : wp->velocity.x + ctl->decel_1C;
            }
            if (Distance_xyz(&wp->position, &ctl->home_24) > 0x1000)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            stcom12_func_0E9C(wp, hit);
            if (wp->state_A7 < 0)
            {
                func_800322A8(wp, 0, 0);
                wp->velocity.x = wp->velocity.y = wp->velocity.z = 0;
                wp->routine_0                                    = 1;
                wp->routine_1                                    = 0;
                wp->routine_3                                    = 0;
            }
            break;
    }
}

void stcom12_func_0B24(STCOM12_WORK *wp)
{
    STCOM12_CTL *ctl;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            pl->value_448 = 0x30;
            wp->routine_1++;
            // fall through
        case 2:
            if (D_80098A72 != 0)
            {
                break;
            }
            func_80063BC8(&wp->position, 2, 0, 5);
            wp->velocity.x = 0x200;
            wp->rotation.y = 0xA8C;
            wp->flags_0 |= 2;
            ctl->timer_4 = 180;
            ctl->home_24 = wp->position_prev = wp->position = pl->position;
            wp->position_fixed_prev = wp->position_fixed = pl->position_fixed;
            wp->position.y -= 50;
            wp->routine_1++;
            break;
        case 3:
            if (--ctl->timer_4 == 0)
            {
                wp->routine_1++;
            }
            // fall through
        case 4:
            Obj_pos_set(wp, wp->velocity.x, 0, 0);
            stcom12_func_0E9C(wp, Obj_map_push_out(wp));
            if (D_800987B0[0] != 0)
            {
                break;
            }
            func_80042314(pl);
            pl->flags_0 |= 2;
            Sce_flag_on(0x239);
            wp->routine_0 = 1;
            wp->routine_1 = 0;
            break;
    }
}

void stcom12_func_0D68(STCOM12_WORK *wp, uint32 hit)
{
    sint32 turn;

    turn = wp->turn_66;
    if (hit == 0)
    {
        turn = (((rand() * STCOM12_SCRATCH_2) & 0xF) - 8) << 2;
    }
    else
    {
        if (hit & 0x500)
        {
            turn = 0x10;
        }
        if (hit & 0xA00)
        {
            turn = -(sint16)turn;
        }
    }
    wp->turn_66 = turn;
}

sint32 stcom12_func_0DE4(STCOM12_WORK *wp)
{
    STCOM12_WORK *target;
    STCOM_PL_WORK *pl;

    pl     = &Player_work;
    target = pl->target_184;
    if (target == wp)
    {
        Player_work.target_184 = NULL;
        pl->flags_0 &= ~2;
        Player_work.flags_bd |= 0x40;
        stcom12_E_0000.x = target->value_180.x;
        stcom12_E_0000.y = target->value_180.y - 0x20;
        stcom12_E_0000.z = target->value_180.z;
        func_80039FAC(&stcom12_E_0000, 0x100, Angle_xz_svector(&pl->position, &target->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void stcom12_func_0E9C(STCOM12_WORK *wp, uint32 hit)
{
    sint16 ground;

    ground = Obj_ceiling_height_get(wp);
    if (hit & 0x1000)
    {
        wp->position.y = ground;
        wp->velocity.y = 0;
    }
    else
    {
        wp->velocity.y += 4;
        wp->position.y += wp->velocity.y;
        if (wp->position.y > ground)
        {
            wp->position.y = ground;
            wp->velocity.y = 0;
        }
    }
    wp->position_fixed.y = wp->position.y << 16;
}

void stcom12_func_0F28(STCOM12_WORK *wp, uint32 hit)
{
    if (hit && ++wp->ctl.counter_0 > 60)
    {
        wp->ctl.counter_0 = 0;
        wp->ctl.goal_2    = (wp->rotation.y + 2000 + (rand() & 0x3F)) & 0xFFF;
        wp->routine_1     = 20;
    }
}

uint8 stcom12_func_0F98(STCOM12_WORK *wp)
{
    STCOM_FIXED_VECTOR out;
    STCOM_SVECTOR size;
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (wp->ctl.dist_8 < 100)
    {
        wp->value_C4 = wp->value_180;
        pl->value_C4 = pl->position;
        size.x       = 2;
        size.y       = 9;
        size.z       = 4;
        if (func_80030418(wp, pl, &size, &out) & 0x10)
        {
            return 1;
        }
        wp->position       = wp->position_prev;
        wp->position_fixed = wp->position_fixed_prev;
        if (wp->anim_AC != 0)
        {
            func_800322A8(wp, 0, 0);
            wp->routine_3 = 0;
        }
        else if (++wp->routine_3 > 60)
        {
            func_800322A8(wp, 1, 0);
            wp->routine_1  = 20;
            wp->ctl.goal_2 = (wp->rotation.y + 0x800) & 0xFFF;
        }
        return 0;
    }
    return 1;
}
