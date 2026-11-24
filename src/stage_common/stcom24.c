#include "common.h"
#include "stage_common/stcom24.h"

// Shared stage code, linked into 3 stages: r3_st09, r3_st13 and r3_st1a. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom24"

// A creature that shoots, leaps at the player and is knocked back by hits.
void stcom24_func_0000(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;
    STCOM_SVECTOR *pos;
    sint16 ground;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->jump_prev_75        = wp->jump_74;
    wp->ctl.rand_2          = rand();
    stcom24_D_000C[wp->routine_0](wp);
    ctl                  = &wp->ctl;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    if (func_8003648C(ctl->track_40, wp) != 0)
    {
        ctl->flags_0 |= 0x20;
    }
    else
    {
        ctl->flags_0 &= ~0x20;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    Obj_map_push_out(wp);
    ground = Obj_ceiling_height_get(wp);
    if (wp->jump_74 == 0)
    {
        if (STCOM_ABS(wp->position.y - ground) > 0x100)
        {
            wp->variant_3 = 0;
        }
        if (wp->position.y >= ground || (wp->position.y += 0x28) > ground)
        {
            wp->position.y = ground;
        }
    }
    Model_Shadow_Trans(wp, 0x80, 0x200, 0);
    pos = &ctl->pos_18;
    if (ctl->flags_0 & 1)
    {
        ctl->pos_18 = wp->joints_180[0];
        func_800341BC(pos, 0x6E, 0, 0x8000, wp->index_1, &ctl->body_20, ctl->kind_10 | 0x4880000, 0x800000, 0);
        if (ctl->flags_0 & 2)
        {
            ctl->pos_18.x += (rsin(wp->rotation.y + 0x800) * 100) >> 12;
            ctl->pos_18.z += (rcos(wp->rotation.y + 0x800) * 100) >> 12;
            func_800341BC(pos, 0x50, 0, 0x8000, wp->index_1, &ctl->claw_30, ctl->kind_14 | 0x4880000, 0x800000, 0);
        }
    }
    ctl->body_20.hit_0 = 0;
    ctl->claw_30.hit_0 = 0;
}

void stcom24_func_033C(STCOM24_WORK *wp)
{
    wp->rotation.x   = 0;
    wp->rotation.z   = 0;
    wp->value_64     = 0;
    wp->value_66     = 0;
    wp->jump_74      = 0;
    wp->jump_prev_75 = 0;
    wp->flags_0 |= 2;
    wp->rotation.y = (wp->param_C << 9) & 0xE00;
    Model_work_init(wp, NULL);
    wp->scale.v.x = 0x200;
    wp->scale.v.y = 0x200;
    wp->scale.v.z = 0x200;
    Track_set(wp->ctl.track_40, 3, -200);
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 << 4;
    wp->data_78                                      = stcom24_D_0000;
    wp->position.y                                   = Obj_ceiling_height_get(wp);
    wp->position_fixed.y                             = wp->position.y << 16;
    wp->routine_0                                    = 1;
    wp->routine_1                                    = 0;
    wp->routine_2                                    = 0;
    wp->routine_3                                    = 0;
    wp->scale.v.pad                                  = 0x4210;
    func_800322A8(wp, 5, 0);
    wp->ctl.timer_4 = 180;
    wp->ctl.timer_6 = 0;
    wp->ctl.flags_0 |= 1;
    wp->ctl.kind_10         = D_80098844[wp->kind_2]->value_B;
    wp->ctl.kind_14         = D_80098844[wp->kind_2]->value_C;
    wp->ctl.damage_12       = 0;
    wp->ctl.damage_16       = 0;
    wp->ctl.body_20.hit_0   = 0;
    wp->ctl.body_20.value_4 = 0;
    wp->ctl.claw_30.hit_0   = 0;
    wp->ctl.claw_30.value_4 = 0;
    wp->ctl.timer_8         = 0;
    wp->ctl.home_50         = wp->position;
}

void stcom24_func_04CC(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;
    sint8 hit;

    ctl = &wp->ctl;
    if (wp->variant_3 != 0 && Distance_xyz(&wp->position, &ctl->home_50) >= 11)
    {
        wp->routine_0 = 6;
        wp->routine_1 = 0;
        return;
    }
    hit = stcom24_func_1468(wp);
    if (hit != 0)
    {
        if (hit < 0)
        {
            wp->routine_0 = 5;
            wp->routine_1 = 0;
            return;
        }
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->anim_AC   = 0;
        return;
    }
    if (ctl->flags_0 & 0x20)
    {
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x34)) & 0xFFF;
        if (wp->flags_A7 < 0)
        {
            wp->anim_AC = 0;
            wp->routine_0++;
        }
    }
}

void stcom24_func_05B4(STCOM24_WORK *wp)
{
    if (stcom24_func_1468(wp) < 0)
    {
        wp->routine_0 = 5;
        wp->routine_1 = 0;
        return;
    }
    stcom24_D_002C[wp->routine_1](wp);
    if (wp->ctl.timer_4 != 0)
    {
        wp->ctl.timer_4--;
    }
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
    }
}

void stcom24_func_0648(STCOM24_WORK *wp)
{
    if (wp->flags_A7 < 0)
    {
        wp->anim_AC     = 1;
        wp->ctl.timer_8 = 0;
        wp->ctl.timer_4 = (wp->ctl.rand_2 & 0x1F) + 30;
        wp->routine_1++;
    }
}

void stcom24_func_0684(STCOM24_WORK *wp)
{
    sint16 turn;

    if (wp->flags_A7 < 0)
    {
        turn = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x400);
        if (STCOM_ABS(turn) > 0x68)
        {
            wp->anim_AC = 0x10;
        }
        wp->routine_1++;
    }
}

void stcom24_func_0714(STCOM24_WORK *wp)
{
    STCOM_SVECTOR *pos;
    sint16 turn;

    pos            = &wp->position;
    turn           = Muku(pos, &Player_work.position, wp->rotation.y, 0x34);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (wp->frame_A4 == 5 || wp->frame_A4 == 0x14)
    {
        Sound_call2(0x1B6, pos);
    }
    if (STCOM_ABS(turn) < 0x34)
    {
        wp->anim_AC = 3;
        wp->routine_1++;
    }
}

void stcom24_func_07E4(STCOM24_WORK *wp)
{
    STCOM24_SHOT *shot;

    if (wp->flags_A7 < 0 && wp->ctl.timer_8 == 0)
    {
        shot = Open_SHL_WORK();
        if (shot != NULL)
        {
            shot->flags_0          = 1;
            shot->kind_2           = 9;
            shot->variant_3        = 3;
            shot->position         = wp->joints_180[1];
            shot->position_fixed.x = shot->position.x << 16;
            shot->position_fixed.y = shot->position.y << 16;
            shot->position_fixed.z = shot->position.z << 16;
            func_8002FFC4(&shot->position, &shot->position_fixed, wp->rotation.y & 0xFFF, 0x800, 0x140, 0);
            shot->angle_64 = wp->rotation.y;
        }
        wp->ctl.timer_8 = 15;
        wp->anim_AC     = 4;
        wp->routine_1++;
    }
}

void stcom24_func_08E8(STCOM24_WORK *wp)
{
    if (wp->flags_A7 < 0)
    {
        wp->anim_AC = 2;
        wp->routine_1++;
    }
}

void stcom24_func_0910(STCOM24_WORK *wp)
{
    if (wp->flags_A7 < 0)
    {
        wp->anim_AC   = 1;
        wp->routine_1 = 1;
        if (wp->ctl.timer_4 == 0)
        {
            if (wp->variant_3 != 0)
            {
                wp->routine_0 = 3;
            }
            else
            {
                wp->routine_0 = 6;
            }
            wp->routine_1 = 0;
        }
    }
}

void stcom24_func_0954(STCOM24_WORK *wp)
{
    sint8 hit;

    hit = stcom24_func_15E8(wp);
    if (hit != 0)
    {
        if (hit < 0)
        {
            wp->routine_0   = 4;
            wp->routine_1   = 0;
            wp->anim_AC     = 9;
            wp->ctl.timer_4 = 0;
            wp->ctl.flags_0 &= ~2;
            return;
        }
    }
    else if (stcom24_func_1468(wp) < 0)
    {
        wp->routine_0 = 5;
        wp->routine_1 = 0;
        return;
    }
    stcom24_D_0044[wp->routine_1](wp);
}

void stcom24_func_09FC(STCOM24_WORK *wp)
{
    wp->anim_AC = 5;
    wp->ctl.flags_0 |= 2;
    wp->ctl.timer_4 = (wp->ctl.rand_2 & 0x1F) + 30;
    wp->routine_1++;
}

void stcom24_func_0A30(STCOM24_WORK *wp)
{
    if (wp->flags_A7 < 0)
    {
        if (--wp->ctl.timer_4 == 0)
        {
            wp->anim_AC = 0;
            wp->routine_1++;
        }
    }
}

void stcom24_func_0A74(STCOM24_WORK *wp)
{
    if (wp->flags_A7 < 0)
    {
        wp->routine_0 = 1;
        wp->routine_1 = 0;
        wp->ctl.flags_0 &= ~2;
    }
}

void stcom24_func_0AA0(STCOM24_WORK *wp)
{
    sint16 t;
    sint16 speed;

    if (stcom24_func_1468(wp) < 0)
    {
        wp->routine_0 = 5;
        wp->routine_1 = 0;
        return;
    }
    t     = ++wp->ctl.timer_4;
    speed = 0;
    if (t < 27)
    {
        speed = 3;
    }
    if (t < 21)
    {
        speed = 6;
    }
    if (t < 15)
    {
        speed = 9;
    }
    if (t < 9)
    {
        speed = 7;
    }
    if (t < 4)
    {
        speed = 0;
    }
    wp->position.x += (rsin(wp->ctl.angle_C + 0x800) * speed) >> 12;
    wp->position.z += (rcos(wp->ctl.angle_C + 0x800) * speed) >> 12;
    if (wp->flags_A7 < 0)
    {
        if (wp->variant_3 != 0)
        {
            wp->routine_0 = 6;
        }
        else
        {
            wp->routine_0 = 2;
        }
        wp->routine_1 = 0;
    }
}

void stcom24_func_0BA0(STCOM24_WORK *wp)
{
    stcom24_D_0050[wp->routine_1](wp);
}

void stcom24_func_0BDC(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;

    ctl = &wp->ctl;
    if (ctl->flags_0 & 8)
    {
        wp->anim_AC = 0xD;
    }
    else
    {
        wp->anim_AC = 0xA;
    }
    wp->jump_74  = 1;
    ctl->timer_4 = 0;
    ctl->timer_6 = 0;
    wp->routine_1++;
}

void stcom24_func_0C24(STCOM24_WORK *wp)
{
    sint16 speed;
    sint16 rise;

    rise  = 0;
    speed = 0;
    if (wp->ctl.timer_4 < 9)
    {
        speed = 0x18;
    }
    if (wp->ctl.timer_4 < 5)
    {
        speed = 0x38;
    }
    if (wp->ctl.timer_6 < 9)
    {
        rise = 0x15;
    }
    if (wp->ctl.timer_6 < 5)
    {
        rise = -0x15;
    }
    wp->ctl.timer_4++;
    wp->ctl.timer_6++;
    wp->position.x += (rsin(wp->ctl.angle_C + 0x800) * speed) >> 12;
    wp->position.z += (rcos(wp->ctl.angle_C + 0x800) * speed) >> 12;
    wp->position.y += rise;
    if (wp->flags_A7 < 0)
    {
        if (wp->ctl.flags_0 & 8)
        {
            wp->anim_AC = 0xE;
        }
        else
        {
            wp->anim_AC = 0xB;
        }
        wp->jump_74 = 0;
        wp->routine_1++;
    }
}

void stcom24_func_0D38(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;
    STCOM_EFFECT *effect;

    ctl = &wp->ctl;
    wp->position.x += (rsin(ctl->angle_C + 0x800) * 5) >> 12;
    wp->position.z += (rcos(ctl->angle_C + 0x800) * 5) >> 12;
    if (wp->flags_A7 < 0)
    {
        if (wp->life_6E == 0)
        {
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 5;
                effect->kind_2          = 0x80;
                effect->variant_3       = 0x41;
                effect->sprite.position = wp->position;
            }
            wp->routine_0 = 7;
            wp->routine_1 = 0;
            return;
        }
        if (ctl->flags_0 & 8)
        {
            wp->anim_AC = 0xF;
        }
        else
        {
            wp->anim_AC = 0xC;
        }
        ctl->timer_4 = 0;
        wp->routine_1++;
    }
}

void stcom24_func_0E54(STCOM24_WORK *wp)
{
    sint16 speed;

    speed = 0;
    if (wp->ctl.timer_4 < 14)
    {
        speed = 10;
    }
    if (wp->ctl.timer_4 < 11)
    {
        speed = 0x15;
    }
    if (wp->ctl.timer_4 < 5)
    {
        speed = 0;
    }
    wp->ctl.timer_4++;
    wp->position.x += (rsin(wp->ctl.angle_C) * speed) >> 12;
    wp->position.z += (rcos(wp->ctl.angle_C) * speed) >> 12;
    if (wp->flags_A7 < 0)
    {
        if (wp->variant_3 != 0)
        {
            wp->routine_0 = 6;
        }
        else
        {
            wp->routine_0 = 2;
        }
        wp->routine_1 = 0;
    }
}

void stcom24_func_0F20(STCOM24_WORK *wp)
{
    sint8 hit;

    if (wp->variant_3 != 0)
    {
        if (wp->ctl.body_20.hit_0 & 0x38000000)
        {
            Sound_call2(0xA3, &wp->position);
        }
        if (wp->ctl.claw_30.hit_0 & 0x38000000)
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    else
    {
        hit = stcom24_func_15E8(wp);
        if (hit != 0)
        {
            if (hit < 0)
            {
                wp->routine_0   = 4;
                wp->routine_1   = 0;
                wp->anim_AC     = 9;
                wp->ctl.timer_4 = 0;
                wp->ctl.flags_0 &= ~2;
                return;
            }
        }
        else if (stcom24_func_1468(wp) < 0)
        {
            wp->routine_0 = 5;
            wp->routine_1 = 0;
            return;
        }
    }
    stcom24_D_0060[wp->routine_1](wp);
}

void stcom24_func_1024(STCOM24_WORK *wp)
{
    if (wp->variant_3 != 0)
    {
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &wp->ctl.home_50, wp->rotation.y, 0x100)) & 0xFFF;
    }
    wp->anim_AC = 6;
    wp->ctl.flags_0 |= 2;
    wp->routine_1++;
}

void stcom24_func_109C(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;
    sint16 step;
    sint16 tx;
    sint16 tz;
    sint32 d;

    ctl = &wp->ctl;
    if (wp->variant_3 != 0)
    {
        wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->home_50, wp->rotation.y, 0x100)) & 0xFFF;
    }
    if (wp->flags_A7 < 0)
    {
        tz = 0;
        if (wp->variant_3 != 0)
        {
            tx   = 0;
            step = STCOM_ABS((rsin(wp->rotation.y + 0x800) * 6) >> 12);
            if (step != 0)
            {
                d  = STCOM_ABS(wp->position.x - ctl->home_50.x);
                tx = d / step;
            }
            step = STCOM_ABS((rcos(wp->rotation.y + 0x800) * 6) >> 12);
            if (step != 0)
            {
                d  = STCOM_ABS(wp->position.z - ctl->home_50.z);
                tz = d / step;
            }
            if (tx < tz)
            {
                ctl->timer_4 = tz;
            }
            else
            {
                ctl->timer_4 = tx;
            }
        }
        else
        {
            wp->ctl.timer_4 = (wp->ctl.rand_2 & 0x1F) + 30;
        }
        wp->anim_AC = 8;
        wp->routine_1++;
    }
}

void stcom24_func_1300(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->variant_3 == 0)
    {
        wp->position.x += (rsin(wp->rotation.y + 0x800) * 6) >> 12;
        wp->position.z += (rcos(wp->rotation.y + 0x800) * 6) >> 12;
    }
    else if (ctl->timer_4 != 0)
    {
        wp->position.x += (rsin(wp->rotation.y + 0x800) * 6) >> 12;
        wp->position.z += (rcos(wp->rotation.y + 0x800) * 6) >> 12;
    }
    if (ctl->timer_4 != 0)
    {
        ctl->timer_4--;
    }
    if (wp->frame_A4 == 5 || wp->frame_A4 == 0x14)
    {
        Sound_call2(0x1B6, &wp->position);
    }
    if (wp->flags_A7 < 0 && ctl->timer_4 == 0)
    {
        wp->anim_AC = 7;
        wp->routine_1++;
    }
}

void stcom24_func_1408(STCOM24_WORK *wp)
{
    if (wp->flags_A7 < 0)
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->ctl.flags_0 &= ~2;
    }
}

void stcom24_func_1434(STCOM24_WORK *wp)
{
    // Never set: func_80047148 gets whatever a2 holds.
    STCOM_EFFECT *effect;

    func_80047148(wp, wp->joints_180, effect);
    func_80031824(wp);
}

// The body hit box: -1 when it is knocked back (or killed), 1 when it is hurt, else 0.
sint8 stcom24_func_1468(STCOM24_WORK *wp)
{
    STCOM24_CTL *ctl;
    STCOM_SVECTOR *pos;
    sint8 result;
    uint32 damage;
    sint32 limit;

    result = 0;
    limit  = D_80098844[wp->kind_2]->limit_9;
    ctl    = &wp->ctl;
    damage = ctl->body_20.hit_0 & 0xFFFFFF;
    if (damage != 0 && (wp->ctl.body_20.hit_0 & 0x38000000))
    {
        wp->ctl.damage_12 += damage;
        wp->life_prev_B2 = wp->life_6E;
        wp->life_6E -= damage;
        if (wp->life_6E < 0)
        {
            wp->life_6E = 0;
        }
        pos             = &wp->position;
        wp->ctl.angle_C = func_80031F84(pos, &wp->ctl.body_20.from_8, wp->rotation.y, 0);
        wp->scale.v.pad = 0x7FFF;
        if (limit < wp->ctl.damage_12 || wp->life_6E == 0)
        {
            result            = -1;
            wp->ctl.damage_12 = 0;
            Sound_call2(0xA2, pos);
            if (wp->ctl.angle_C & 0xFFFF0000)
            {
                wp->ctl.flags_0 |= 0x10;
            }
            else
            {
                wp->ctl.flags_0 |= 8;
            }
        }
        else
        {
            result = 1;
            Sound_call2(0xA0, pos);
        }
        if (ctl->angle_C & 0xFFFF0000)
        {
            ctl->angle_C += 0x800;
        }
        ctl->angle_C = (uint16)ctl->angle_C;
    }
    return result;
}

// The claw hit box: -1 when it is knocked back, 1 when it is pushed, else 0.
sint8 stcom24_func_15E8(STCOM24_WORK *wp)
{
    sint8 result;
    uint32 damage;
    uint8 limit;

    result = 0;
    damage = wp->ctl.claw_30.hit_0 & 0xFFFFFF;
    limit  = D_80098844[wp->kind_2]->limit_A;
    if (damage != 0 && (wp->ctl.claw_30.hit_0 & 0x38000000))
    {
        wp->ctl.damage_16 += damage;
        wp->ctl.angle_C = func_80031F84(&wp->position, &wp->ctl.claw_30.from_8, wp->rotation.y, 0);
        if (wp->ctl.angle_C & 0xFFFF0000)
        {
            wp->ctl.angle_C += 0x800;
        }
        wp->ctl.angle_C = (uint16)wp->ctl.angle_C;
        if (limit < wp->ctl.damage_16 || (wp->ctl.claw_30.hit_0 & 0x20000000))
        {
            result            = -1;
            wp->ctl.damage_16 = 0;
        }
        else
        {
            result = 1;
            wp->position.x += (rsin(wp->ctl.angle_C + 0x800) * 25) >> 12;
            wp->position.z += (rcos(wp->ctl.angle_C + 0x800) * 25) >> 12;
        }
        Sound_call2(0xA3, &wp->position);
    }
    return result;
}
