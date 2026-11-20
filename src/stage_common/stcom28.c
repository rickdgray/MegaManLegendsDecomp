#include "common.h"
#include "stage_common/stcom28.h"

// Shared stage code, linked into 3 stages: r3_st09, r3_st0e and r3_st13. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom28"

// A bobbing creature that roams, turns back at walls, charges at the player and leaps.
void stcom28_func_0000(STCOM28_WORK *wp)
{
    stcom28_D_0000[wp->routine_0](wp);
}

void stcom28_func_003C(STCOM28_WORK *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->velocity.z = 0;
    wp->velocity.y = 0;
    wp->velocity.x = 0;
    wp->accel.z    = 0;
    wp->accel.y    = 0;
    wp->accel.x    = 0;
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    func_80036478(wp->ctl.track_C, 9, -0x60);
    wp->data_78       = stcom28_D_000C;
    wp->jump_74       = 0;
    wp->ctl.counter_0 = 0;
    wp->ctl.sees_1C   = 0;
    wp->ctl.flags_20  = 0;
    wp->ctl.hit_2C    = 0;
    wp->ctl.value_30  = 0;
    wp->ctl.kind_3C   = 0;
    wp->routine_0     = 1;
    wp->routine_1     = 0;
    wp->routine_2     = 0;
    wp->routine_3     = 0;
    stcom28_func_0294(wp);
}

void stcom28_func_00E8(STCOM28_WORK *wp)
{
    STCOM_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->color_B4            = 0x808080;
    wp->jump_prev_75        = wp->jump_74;
    stcom28_func_038C(wp);
    wp->ctl.sees_1C = func_8003648C(wp->ctl.track_C, wp);
    stcom28_D_0018[wp->routine_1](wp);
    if (wp->routine_0 != 2)
    {
        wp->pos_AC = wp->position;
        m          = &wp->matrix;
        wp->pos_AC.y += stcom28_D_0034[wp->ctl.counter_0++];
        wp->ctl.counter_0 &= 0x1F;
        RotMatrixYXZ(&wp->rotation, m);
        scale.x = 0x200;
        scale.y = 0x200;
        scale.z = 0x200;
        ScaleMatrix(m, &scale);
        stcom28_func_0468(wp);
        if (wp->routine_1 != 6)
        {
            stcom28_func_0574(wp);
        }
        if (wp->flags_0 & 2)
        {
            Model_Shadow_Trans(wp, 0x28, 0x200, 0);
        }
    }
}

// Picks the next move: mostly roaming for a while, sometimes waiting.
void stcom28_func_0294(STCOM28_WORK *wp)
{
    if ((rand() & 0xF) < 0xE)
    {
        wp->ctl.turn_1  = rand() & 1;
        wp->velocity.x  = 0x64;
        wp->velocity.y  = 0;
        wp->accel.y     = 0;
        wp->ctl.timer_2 = stcom28_D_0074[rand() & 7];
        wp->routine_1   = 0;
    }
    else
    {
        wp->ctl.timer_4 = stcom28_D_0074[rand() & 7];
        wp->routine_1   = 2;
    }
    wp->routine_2 = 0;
    stcom28_func_00E8(wp);
}

// Charges once it sees the player.
void stcom28_func_0344(STCOM28_WORK *wp)
{
    if (wp->ctl.sees_1C != 0)
    {
        wp->rotation.x  = 0x40;
        wp->velocity.x  = 0xC8;
        wp->ctl.step_3E = 0x20;
        wp->ctl.timer_6 = 0x5A;
        wp->velocity.y  = 0;
        wp->accel.y     = 0;
        wp->routine_1   = 4;
        wp->routine_2   = 0;
    }
}

// Takes a hit: knocked into the air, away from it.
void stcom28_func_038C(STCOM28_WORK *wp)
{
    STCOM28_CTL *ctl;
    sint32 angle;

    ctl = &wp->ctl;
    if (wp->routine_1 != 6 && (wp->ctl.hit_2C & 0x38000000))
    {
        wp->ctl.kind_3C = 0;
        angle           = func_80031F84(&wp->position, &wp->ctl.from_34, wp->rotation.y, 0);
        if (angle & 0xFFFF0000)
        {
            wp->rotation.y = (angle + 0x800) & 0xFFF;
        }
        else
        {
            wp->rotation.y = angle;
        }
        wp->velocity.x = 0x80;
        wp->velocity.y = -0x300;
        wp->accel.y    = 0x80;
        ctl->timer_8   = 8;
        wp->jump_74    = 1;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        wp->routine_1 = 6;
        wp->routine_2 = 0;
        wp->velocity.y += wp->accel.y;
    }
}

// Keeps it on the ground: back to its last position at a ledge.
void stcom28_func_0468(STCOM28_WORK *wp)
{
    STCOM28_CTL *ctl;
    sint32 ground;
    sint16 rot;

    rot              = wp->rotation.x;
    wp->rotation.x   = 0;
    wp->ctl.flags_20 = 0;
    ctl              = &wp->ctl;
    if (func_8004B414(wp) & 0xF00)
    {
        wp->ctl.flags_20 |= 1;
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
                wp->ctl.flags_20 |= 4;
            }
        }
        else
        {
            wp->position.y            = ground;
            wp->position_fixed_prev.y = ground << 16; // not position_fixed
        }
        ctl->flags_20 |= 2;
    }
    wp->rotation.x = rot;
}

// Registers the hit box.
void stcom28_func_0574(STCOM28_WORK *wp)
{
    wp->ctl.hit_2C = 0;
    wp->ctl.pos_24 = wp->position;
    wp->ctl.pos_24.y -= 0x28;
    func_800341BC(&wp->ctl.pos_24, 0x28, 0, 0x8000, wp->index_1, &wp->ctl.hit_2C,
                  wp->ctl.kind_3C | 0x4080000, 0x800000, 0);
}

void stcom28_func_05FC(STCOM28_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        stcom28_func_063C(wp);
    }
    else
    {
        stcom28_func_0678(wp);
    }
}

// Raises its head before it roams.
void stcom28_func_063C(STCOM28_WORK *wp)
{
    if (wp->rotation.x == 0xC0)
    {
        wp->routine_2++;
    }
    else
    {
        wp->rotation.x += 0x20;
    }
}

// Roams, turning now and then.
void stcom28_func_0678(STCOM28_WORK *wp)
{
    if (stcom28_func_0744(wp) != 0)
    {
        return;
    }
    if (--wp->ctl.timer_2 == 0)
    {
        stcom28_func_0294(wp);
        return;
    }
    if ((rand() & 0xF) >= 0xA)
    {
        if (wp->ctl.turn_1 != 0)
        {
            wp->rotation.y = wp->rotation.y + 0x40;
        }
        else
        {
            wp->rotation.y = wp->rotation.y - 0x40;
        }
        wp->rotation.y &= 0xFFF;
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    stcom28_func_0344(wp);
}

// Turns back at a wall (1), leaps at a ledge (-1).
sint32 stcom28_func_0744(STCOM28_WORK *wp)
{
    if (wp->ctl.flags_20 & 1)
    {
        stcom28_func_0794(wp);
        return 1;
    }
    if (wp->ctl.flags_20 & 4)
    {
        stcom28_func_07F4(wp);
        return -1;
    }
    return 0;
}

void stcom28_func_0794(STCOM28_WORK *wp)
{
    wp->position       = wp->position_prev;
    wp->position_fixed = wp->position_fixed_prev;
    wp->routine_1      = 1;
    wp->routine_2      = 0;
    wp->ctl.angle_A    = (wp->rotation.y + 0x800) & 0xFFF;
}

// Leaps.
void stcom28_func_07F4(STCOM28_WORK *wp)
{
    wp->velocity.x = 0x180;
    wp->velocity.y = -0x200;
    wp->accel.y    = 0x50;
    wp->rotation.x = 0xE80;
    Sound_call2(0x15C, &wp->position);
    wp->jump_74 = 1;
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    wp->velocity.y += wp->accel.y;
    wp->ctl.kind_3C = D_80098928[wp->kind_2]->value_A;
    wp->routine_1   = 5;
    wp->routine_2   = 0;
}

// Turns around.
void stcom28_func_08A4(STCOM28_WORK *wp)
{
    STCOM28_CTL *ctl;
    sint16 x;

    ctl = &wp->ctl;
    if (wp->rotation.y == wp->ctl.angle_A)
    {
        stcom28_func_0294(wp);
        return;
    }
    x = wp->rotation.x;
    if (x != 0)
    {
        if (x >= 0x800)
        {
            wp->rotation.x = x + 0x20;
        }
        else
        {
            wp->rotation.x = x - 0x20;
        }
        wp->rotation.x &= 0xFFF;
    }
    if (ctl->angle_A < wp->rotation.y)
    {
        wp->rotation.y = wp->rotation.y - 0x40;
    }
    else
    {
        wp->rotation.y = wp->rotation.y + 0x40;
    }
    wp->rotation.y &= 0xFFF;
}

// Waits.
void stcom28_func_094C(STCOM28_WORK *wp)
{
    STCOM28_CTL *ctl;
    sint16 x;

    x   = wp->rotation.x;
    ctl = &wp->ctl;
    if (x != 0)
    {
        if (x >= 0x800)
        {
            wp->rotation.x = x + 0x20;
        }
        else
        {
            wp->rotation.x = x - 0x20;
        }
        wp->rotation.x &= 0xFFF;
    }
    if (ctl->timer_4 == 0)
    {
        stcom28_func_0294(wp);
        return;
    }
    ctl->timer_4--;
    if (wp->routine_1 == 2)
    {
        stcom28_func_0344(wp);
    }
}

void stcom28_func_09D4(STCOM28_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        stcom28_func_0A14(wp);
    }
    else
    {
        stcom28_func_0A88(wp);
    }
}

// Turns to face the player.
void stcom28_func_0A14(STCOM28_WORK *wp)
{
    sint16 step;

    step = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80);
    if (step != 0)
    {
        wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
    }
    else
    {
        wp->routine_2++;
    }
}

// Charges, nodding, and leaps at the player once close in front of it.
void stcom28_func_0A88(STCOM28_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (stcom28_func_0744(wp) != 0)
    {
        return;
    }
    wp->rotation.x += wp->ctl.step_3E;
    if (wp->rotation.x == 0x40)
    {
        wp->ctl.step_3E = 0x20;
    }
    if (wp->rotation.x == 0x180)
    {
        wp->ctl.step_3E = -0x20;
    }
    if (wp->ctl.timer_6 != 0)
    {
        wp->ctl.timer_6--;
        Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
        if (func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed,
                          Player_work.rotation.y, 0x800) != 0)
        {
            if (wp->value_80 <= 40000)
            {
                stcom28_func_07F4(wp);
            }
            return;
        }
        if (wp->value_80 < 250000)
        {
            return;
        }
    }
    wp->ctl.timer_4 = 0x1E;
    wp->routine_1   = 3;
    wp->routine_2   = 0;
}

void stcom28_func_0BB0(STCOM28_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        stcom28_func_0BF0(wp);
    }
    else
    {
        stcom28_func_0CB8(wp);
    }
}

// In the air after a leap; turns back when it lands on something.
void stcom28_func_0BF0(STCOM28_WORK *wp)
{
    if (wp->ctl.flags_20 & 1)
    {
        wp->velocity.x = 0;
    }
    if (wp->jump_74 == 0)
    {
        wp->ctl.timer_4 = 0x1E;
        wp->ctl.kind_3C = 0;
        wp->routine_1   = 3;
        wp->routine_2   = 0;
        return;
    }
    if (wp->ctl.hit_2C & 0x2000000)
    {
        wp->ctl.kind_3C = 0;
        wp->rotation.y  = (wp->rotation.y + 0x800) & 0xFFF;
        wp->routine_2++;
        return;
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    wp->velocity.y += wp->accel.y;
}

void stcom28_func_0CB8(STCOM28_WORK *wp)
{
    if (wp->ctl.flags_20 & 1)
    {
        wp->velocity.x = 0;
    }
    if (wp->jump_74 == 0)
    {
        wp->ctl.timer_4 = 0x1E;
        wp->routine_1   = 3;
        wp->routine_2   = 0;
        return;
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    wp->velocity.y += wp->accel.y;
}

// Knocked about until it lands or the timer runs out, then bursts.
void stcom28_func_0D40(STCOM28_WORK *wp)
{
    STCOM_EFFECT *effect;
    sint32 burst;

    wp->rotation.x = (wp->rotation.x + 0x200) & 0xFFF;
    burst          = --wp->ctl.timer_8 == 0;
    if (wp->ctl.flags_20 & 1)
    {
        burst = 1;
    }
    if (wp->jump_74 == 0)
    {
        burst = 1;
    }
    if (burst)
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
        func_80047148(wp, &wp->position);
#else
        func_80047148(wp, &wp->position, effect);
#endif
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        return;
    }
    Obj_pos_set(wp, wp->velocity.x, wp->velocity.y, wp->velocity.z);
    wp->velocity.y += wp->accel.y;
}

void stcom28_func_0E40(STCOM28_WORK *wp)
{
    Close_SHL_WORK(wp);
}
