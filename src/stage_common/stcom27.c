#include "common.h"
#include "stage_common/stcom27.h"

// Shared stage code, linked into 3 stages: r3_st09, r3_st14 and r3_st1a. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom27"

// A creature that roams, then charges at the player and is knocked over by hits.
void stcom27_func_0000(STCOM27_WORK *wp)
{
    stcom27_D_0000[wp->routine_0](wp);
}

void stcom27_func_003C(STCOM27_WORK *wp)
{
    wp->scale.v.x   = 0x200;
    wp->scale.v.y   = 0x200;
    wp->scale.v.z   = 0x200;
    wp->scale.v.pad = 0x4210;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->velocity.z  = 0;
    wp->velocity.y  = 0;
    wp->velocity.x  = 0;
    wp->accel.z     = 0;
    wp->accel.y     = 0;
    wp->accel.x     = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    func_80036478(wp->ctl.track_0, 4, -0x60);
    wp->data_78 = stcom27_D_000C;
    wp->life_6E = wp->life_max_B0 = D_80098844[wp->kind_2]->life_8 << 4;
    wp->jump_74                   = 0;
    wp->damage_B2                 = 0;
    wp->ctl.sees_10               = 0;
    wp->ctl.flags_14              = 0;
    wp->ctl.hit_20                = 0;
    wp->ctl.value_24              = 0;
    wp->ctl.kind_30               = D_80098844[wp->kind_2]->value_B | 0x1000000;
    wp->ctl.timer_34              = 0x100;
    wp->ctl.timer_36              = 0x40;
    func_800322A8(wp, 0, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void stcom27_func_0168(STCOM27_WORK *wp)
{
    STCOM27_CTL *ctl;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->jump_prev_75        = wp->jump_74;
    ctl                     = &wp->ctl;
    stcom27_func_02B4(wp);
    if (wp->routine_0 != 2)
    {
        ctl->sees_10 = func_8003648C(ctl->track_0, wp);
        stcom27_D_0018[wp->routine_1](wp);
        if (wp->anim_AC != wp->anim_prev_AD)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
        stcom27_func_0600(wp);
        stcom27_func_0578(wp);
        if (wp->flags_0 & 2)
        {
            Model_Shadow_Trans(wp, 0x78, 0x200, 0);
        }
    }
}

// Takes hits: knocked over when the damage adds up, killed while it is down.
void stcom27_func_02B4(STCOM27_WORK *wp)
{
    STCOM_EFFECT *effect;
    STCOM_SVECTOR *pos;
    uint32 damage;
    sint32 stun;
    uint8 limit;

    if (wp->damage_B2 != 0)
    {
        wp->damage_B2--;
    }
    damage = wp->ctl.hit_20 & 0xFFFFFF;
    if (damage == 0)
    {
        return;
    }
    stun = wp->routine_1 == 6;
    if (wp->routine_1 == 8)
    {
        stun = 1;
    }
    if (stun)
    {
        Sound_call2(0xA3, &wp->position);
        return;
    }
    limit = D_80098844[wp->kind_2]->limit_9;
    if (wp->routine_1 == 7)
    {
        pos = &wp->position;
        wp->life_6E -= damage;
        Sound_call2(0xA0, pos);
        wp->scale.v.pad = 0x7FFF;
        if (wp->life_6E <= 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0;
                effect->sprite.position = wp->position;
            }
#ifdef __wasm32__
            func_80047148(wp, pos);
#else
            func_80047148(wp, pos, effect);
#endif
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            return;
        }
        wp->ctl.damage_3E += damage;
        if ((wp->ctl.hit_20 & 0x20000000) || (sint16)wp->ctl.damage_3E >= limit * 16)
        {
            wp->anim_AC = 5;
            stcom27_func_04E4(wp);
            wp->routine_1 = 8;
            wp->routine_2 = 0;
        }
        return;
    }
    wp->damage_B2 += damage;
    if ((wp->ctl.hit_20 & 0x20000000) || wp->damage_B2 >= limit * 16)
    {
        wp->anim_AC       = 3;
        wp->damage_B2     = 0;
        wp->ctl.damage_3E = 0;
        wp->ctl.kind_30   = D_80098844[wp->kind_2]->value_B | 0x1000000;
        stcom27_func_04E4(wp);
        wp->routine_1 = 6;
        wp->routine_2 = 0;
        return;
    }
    Sound_call2(0xA3, &wp->position);
}

// Knocked into the air, away from the hit.
void stcom27_func_04E4(STCOM27_WORK *wp)
{
    STCOM_SVECTOR *pos;
    sint32 angle;

    pos = &wp->position;
    Sound_call2(0x197, pos);
    angle = func_80031F84(pos, &wp->ctl.from_28, wp->rotation.y, 0);
    if (angle & 0xFFFF0000)
    {
        wp->rotation.y = (angle + 0x800) & 0xFFF;
    }
    else
    {
        wp->rotation.y = angle;
    }
    wp->velocity.x = 0x80;
    wp->velocity.y = -0x280;
    wp->accel.y    = 0x40;
    stcom27_func_0DDC(wp);
}

// Registers the hit box.
void stcom27_func_0578(STCOM27_WORK *wp)
{
    wp->ctl.hit_20 = 0;
    wp->ctl.pos_18 = wp->position;
    wp->ctl.pos_18.y -= 0x50;
    func_800341BC(&wp->ctl.pos_18, 0x50, 0, 0x8000, wp->index_1, &wp->ctl.hit_20, wp->ctl.kind_30 | 0x4080000, 0x800000, 0);
}

// Keeps it on the ground: back to its last position at a ledge.
void stcom27_func_0600(STCOM27_WORK *wp)
{
    STCOM27_CTL *ctl;
    sint32 ground;

    wp->ctl.flags_14 = 0;
    ctl              = &wp->ctl;
    if (func_8004B414(wp) & 0xF00)
    {
        wp->ctl.flags_14 |= 1;
    }
    if (wp->jump_74 == 0)
    {
        ground = func_80048E6C(wp);
        if (ground != wp->position_prev.y)
        {
            if (wp->jump_prev_75 == 0)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->ctl.flags_14 |= 4;
            }
        }
        else
        {
            wp->position.y       = ground;
            wp->position_fixed.y = ground << 16;
        }
        ctl->flags_14 |= 2;
    }
}

// Starts charging once it sees the player.
void stcom27_func_06F8(STCOM27_WORK *wp)
{
    if (wp->ctl.sees_10 != 0)
    {
        wp->anim_AC    = 1;
        wp->velocity.x = 0x20;
        wp->velocity.y = 0;
        wp->accel.y    = 0;
        wp->routine_1  = 3;
        wp->routine_2  = 0;
    }
}

void stcom27_func_0730(STCOM27_WORK *wp)
{
    if (--wp->ctl.timer_34 == 0)
    {
        stcom27_func_0E4C(wp);
        return;
    }
    stcom27_func_06F8(wp);
}

void stcom27_func_077C(STCOM27_WORK *wp)
{
    if (wp->ctl.flags_14 & 5)
    {
        stcom27_func_0E78(wp);
        return;
    }
    if (--wp->ctl.timer_36 == 0)
    {
        stcom27_func_0E34(wp);
        return;
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    stcom27_func_06F8(wp);
}

void stcom27_func_080C(STCOM27_WORK *wp)
{
    if (wp->rotation.y == wp->ctl.angle_3C)
    {
        stcom27_func_0E4C(wp);
        return;
    }
    if (wp->ctl.angle_3C >= wp->rotation.y)
    {
        wp->rotation.y = wp->rotation.y + 0x10;
    }
    else
    {
        wp->rotation.y = wp->rotation.y - 0x10;
    }
    wp->rotation.y &= 0xFFF;
    stcom27_func_06F8(wp);
}

void stcom27_func_0870(STCOM27_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (wp->ctl.flags_14 & 5)
    {
        stcom27_func_0E78(wp);
        return;
    }
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x40)) & 0xFFF;
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed, Player_work.rotation.y, 0x800) != 0 &&
        wp->value_80 <= 1000000)
    {
        wp->ctl.timer_38 = 0x10;
        wp->anim_AC      = 2;
        wp->routine_1    = 4;
        wp->routine_2    = 0;
    }
}

void stcom27_func_0954(STCOM27_WORK *wp)
{
    stcom27_D_003C[wp->routine_2](wp);
}

void stcom27_func_0990(STCOM27_WORK *wp)
{
    STCOM_SVECTOR *pos;
    sint32 step;

    pos            = &wp->position;
    wp->rotation.y = (wp->rotation.y + Muku(pos, &Player_work.position, wp->rotation.y, 0x40)) & 0xFFF;
    step           = wp->frame_A4 == 0;
    if (wp->frame_A4 == 4)
    {
        step = 1;
    }
    if (step)
    {
        Sound_call2(0x196, pos);
    }
    if (--wp->ctl.timer_38 == 0)
    {
        wp->ctl.timer_38 = 0x3C;
        wp->velocity.x   = 0x200;
        wp->velocity.y   = 0;
        wp->accel.y      = 0;
        wp->ctl.kind_30  = D_80098844[wp->kind_2]->value_A | 0x1000000;
        wp->routine_2++;
    }
}

void stcom27_func_0A70(STCOM27_WORK *wp)
{
    STCOM27_CTL *ctl;
    sint32 stop;
    sint32 step;

    stop = 0;
    ctl  = &wp->ctl;
    if (wp->ctl.flags_14 & 1)
    {
        stop = 1;
        if (wp->flags_6 & 0x80)
        {
            Swing_Camera2(0x1E, 1000, 5000, &wp->position);
        }
    }
    step = wp->frame_A4 == 0;
    if (wp->frame_A4 == 4)
    {
        step = 1;
    }
    if (step)
    {
        Sound_call2(0x196, &wp->position);
    }
    if (ctl->flags_14 & 4)
    {
        stop = 1;
    }
    if (--ctl->timer_38 == 0)
    {
        stop = 1;
    }
    if (stop)
    {
        wp->anim_AC   = 0;
        ctl->kind_30  = D_80098844[wp->kind_2]->value_B | 0x1000000;
        ctl->timer_38 = 0x30;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
}

void stcom27_func_0BA8(STCOM27_WORK *wp)
{
    if (--wp->ctl.timer_38 == 0)
    {
        stcom27_func_0EAC(wp);
    }
}

void stcom27_func_0BE4(STCOM27_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (wp->ctl.flags_14 & 5)
    {
        wp->velocity.x = 0;
    }
    if (--wp->ctl.timer_3A == 0)
    {
        stcom27_func_0E4C(wp);
        return;
    }
    wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x80)) & 0xFFF;
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
}

void stcom27_func_0C84(STCOM27_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        stcom27_func_0CC4(wp);
        return;
    }
    stcom27_func_0D44(wp);
}

void stcom27_func_0CC4(STCOM27_WORK *wp)
{
    stcom27_func_0DB8(wp);
    if (wp->jump_74 == 0)
    {
        if (wp->routine_1 == 6)
        {
            wp->velocity.x = 0x40;
            wp->velocity.y = -0xE0;
            wp->accel.y    = 0x20;
        }
        else
        {
            wp->velocity.x = 0x40;
            wp->velocity.y = -0xA0;
            wp->accel.y    = 0x20;
        }
        wp->routine_2++;
    }
    stcom27_func_0DDC(wp);
}

void stcom27_func_0D44(STCOM27_WORK *wp)
{
    stcom27_func_0DB8(wp);
    if (wp->jump_74 == 0)
    {
        if (wp->routine_1 == 6)
        {
            wp->anim_AC   = 4;
            wp->routine_1 = 7;
            wp->routine_2 = 0;
            return;
        }
        stcom27_func_0E78(wp);
        return;
    }
    stcom27_func_0DDC(wp);
}

void stcom27_func_0DB8(STCOM27_WORK *wp)
{
    if (wp->ctl.flags_14 & 1)
    {
        wp->velocity.x = 0;
        wp->velocity.z = 0;
    }
}

// In the air: moves and falls.
void stcom27_func_0DDC(STCOM27_WORK *wp)
{
    wp->jump_74 = 1;
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    wp->velocity.y += wp->accel.y;
}

void stcom27_func_0E2C(void)
{
}

void stcom27_func_0E34(STCOM27_WORK *wp)
{
    wp->ctl.timer_34 = 0x100;
    wp->anim_AC      = 0;
    wp->routine_1    = 0;
    wp->routine_2    = 0;
}

void stcom27_func_0E4C(STCOM27_WORK *wp)
{
    wp->anim_AC      = 1;
    wp->velocity.x   = 0x18;
    wp->velocity.y   = 0;
    wp->accel.y      = 0;
    wp->ctl.timer_36 = 0x40;
    wp->routine_1    = 1;
    wp->routine_2    = 0;
}

void stcom27_func_0E78(STCOM27_WORK *wp)
{
    if (wp->anim_AC != 1)
    {
        wp->anim_AC = 1;
    }
    wp->routine_1    = 2;
    wp->routine_2    = 0;
    wp->ctl.angle_3C = (wp->rotation.y + 0x800) & 0xFFF;
}

void stcom27_func_0EAC(STCOM27_WORK *wp)
{
    wp->anim_AC      = 2;
    wp->velocity.x   = -0x80;
    wp->ctl.timer_3A = 0xC;
    wp->velocity.y   = 0;
    wp->accel.y      = 0;
    wp->routine_1    = 5;
    wp->routine_2    = 0;
}

void stcom27_func_0EDC(STCOM27_WORK *wp)
{
    func_80031824(wp);
}
