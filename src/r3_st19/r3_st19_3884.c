#include "common.h"
#include "st19.h"

void func_80103884(ST19_OBJ *wp)
{
    sint8 i;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0;
    wp->value_346           = rand();
    if (wp->u_E.b.byte_E == 0)
    {
        for (i = 0; i < 5; i++)
        {
            wp->pal[i].color = 0x4210;
        }
    }
    else
    {
        for (i = 0; i < 5; i++)
        {
            wp->pal[i].color = 0x7FFF;
        }
    }
    D_801179D8[wp->routine_0](wp);
    wp->u_E.b.byte_E = 0;
}

void func_801039B8(ST19_OBJ *wp)
{
    ST19_SPIN *spin;
    uint8 i;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 0x42;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->u_64.w[0]      = 0;
    wp->u_70.w[0]      = 0;
    wp->value_74       = 0;
    func_80036478(wp->track_300, 0, -0x60);
    wp->value_330   = 0;
    wp->value_332   = 0;
    wp->data_78     = D_801179CC;
    wp->u_70.b[3]   = D_80098844[0x41]->value_A;
    wp->u_32C.h[0]  = D_80098844[0x41]->life_C * 16;
    wp->u_32C.h[1]  = D_80098844[0x41]->life_C * 16;
    wp->value_34B   = 0;
    wp->value_34C   = 0;
    wp->value_2C8   = 0;
    wp->value_2CC   = 0;
    spin            = (ST19_SPIN *)&wp->value_2C8;
    wp->routine_0   = 1;
    wp->scale.v.pad = 0;
    for (i = 0; i < 5; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    wp->anim_AC = 0;
    func_800322A8(wp, 0, 0);
    spin->timer_6C = 0x960;
    spin->value_7C = 0xB4;
    spin->state_81 = 0;
    spin->flags_82 = 0;
    spin->value_6E = 0;
    spin->value_70 = 0;
    spin->value_72 = 0;
    spin->value_85 = 0;
    for (i = 0; i < 3; i++)
    {
        spin->hit_20[i][0] = 0;
    }
}

void func_80103B3C(ST19_OBJ *wp)
{
    ST19_SPIN *spin;
    ST19_OBJ *owner;
    uint8 i;

    func_80104B80(wp);
    func_8003648C(wp->track_300, wp);
    spin = (ST19_SPIN *)&wp->value_2C8;
    if (wp->variant_3 == 0)
    {
        D_801179E8[wp->value_349](wp);
    }
    if (!(wp->value_34D & 8))
    {
        D_801179FC[wp->routine_1](wp);
    }
    if (wp->variant_3 == 0)
    {
        D_801179F4[wp->value_34B](wp);
    }
    owner                  = (ST19_OBJ *)func_80036294(wp->u_C.b.byte_C);
    wp->position           = ST19_OBJ_JOINT(owner)[0];
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    func_80032538(wp);
    ST19_SP_ROT[1].x = wp->value_330;
    ST19_SP_ROT[3].x = wp->value_332;
    func_8003346C(wp);
    spin->pos_8 = ST19_OBJ_JOINT(wp)[0];
    spin->pos_8.y -= 0xB8;
    func_800341BC(&spin->pos_8, 0x118, 0, 0x8000, wp->value_1, spin->hit_20[0],
                  wp->u_70.b[3] | 0x5080000, 0, 0x80);
    spin->pos_8     = ST19_OBJ_JOINT(wp)[1];
    spin->step_4C.x = spin->pos_8.x << 16;
    spin->step_4C.y = spin->pos_8.y << 16;
    spin->step_4C.z = spin->pos_8.z << 16;
    func_8002FFC4(&spin->pos_8, &spin->step_4C, wp->rotation.y & 0xFFF, 0, 0x3C0, 0x3C0);
    func_800341BC(&spin->pos_8, 0xB4, 0, 0x8000, wp->value_1, spin->hit_20[0],
                  wp->u_70.b[3] | 0x5080000, 0, 0x80);
    spin->pos_8     = ST19_OBJ_JOINT(wp)[3];
    spin->step_4C.x = spin->pos_8.x << 16;
    spin->step_4C.y = spin->pos_8.y << 16;
    spin->step_4C.z = spin->pos_8.z << 16;
    func_8002FFC4(&spin->pos_8, &spin->step_4C, wp->rotation.y & 0xFFF, 0, 0x3C0, -0x3C0);
    func_800341BC(&spin->pos_8, 0xB4, 0, 0x8000, wp->value_1, spin->hit_20[0],
                  wp->u_70.b[3] | 0x5080000, 0, 0x80);
    spin->step_5C.x = 0;
    spin->step_5C.y = 0xC59;
    spin->step_5C.z = 0;
    ApplyMatrix(&ST19_OBJ_MATRIX(wp)[2].m, &spin->step_5C, &spin->step_4C);
    spin->pos_8.x = ST19_OBJ_JOINT(wp)[2].x + spin->step_4C.x;
    spin->pos_8.y = ST19_OBJ_JOINT(wp)[2].y + spin->step_4C.y;
    spin->pos_8.z = ST19_OBJ_JOINT(wp)[2].z + spin->step_4C.z;
    func_800341BC(&spin->pos_8, 0x118, 0, 0x8000, wp->value_1, spin->hit_20[0],
                  wp->u_70.b[3] | 0x5080000, 0, 0x80);
    spin->step_5C.x = 0;
    spin->step_5C.y = 0xC59;
    spin->step_5C.z = 0;
    ApplyMatrix(&ST19_OBJ_MATRIX(wp)[4].m, &spin->step_5C, &spin->step_4C);
    spin->pos_8.x = ST19_OBJ_JOINT(wp)[4].x + spin->step_4C.x;
    spin->pos_8.y = ST19_OBJ_JOINT(wp)[4].y + spin->step_4C.y;
    spin->pos_8.z = ST19_OBJ_JOINT(wp)[4].z + spin->step_4C.z;
    func_800341BC(&spin->pos_8, 0x118, 0, 0x8000, wp->value_1, spin->hit_20[0],
                  wp->u_70.b[3] | 0x5080000, 0, 0x80);
    spin->wheel_10[0] = ST19_OBJ_JOINT(wp)[1];
    spin->step_4C.x   = spin->wheel_10[0].x << 16;
    spin->step_4C.y   = spin->wheel_10[0].y << 16;
    spin->step_4C.z   = spin->wheel_10[0].z << 16;
    func_8002FFC4(&spin->wheel_10[0], &spin->step_4C, wp->rotation.y & 0xFFF, 0, -0xD40, -0x698);
    if (spin->life_64[0] >= 0)
    {
        func_800341BC(&spin->wheel_10[0], 0x8C, 0, 0x8000, wp->value_1, spin->hit_20[1],
                      wp->u_70.b[3] | 0x5080000, 0, 0);
    }
    spin->wheel_10[1] = ST19_OBJ_JOINT(wp)[3];
    spin->step_4C.x   = spin->wheel_10[1].x << 16;
    spin->step_4C.y   = spin->wheel_10[1].y << 16;
    spin->step_4C.z   = spin->wheel_10[1].z << 16;
    func_8002FFC4(&spin->wheel_10[1], &spin->step_4C, wp->rotation.y & 0xFFF, 0, -0xD40, 0x698);
    if (spin->life_64[1] >= 0)
    {
        func_800341BC(&spin->wheel_10[1], 0x8C, 0, 0x8000, wp->value_1, spin->hit_20[2],
                      wp->u_70.b[3] | 0x5080000, 0, 0);
    }
    for (i = 0; i < 3; i++)
    {
        spin->hit_20[i][0] = 0;
    }
}

void func_80104104(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

// The one-pass do/while (0) loops weight wp's and value_85's references for retail's registers.
// The joint reads after ApplyMatrix need the byte offset `(idx << 3) + 0x180` added to wp for
// retail's addu s2,s0.
void func_80104124(ST19_OBJ *wp)
{
    ST19_SPIN *spin;
    STCOM_PL_WORK *pl;
    ST19_HELD *held;
    STCOM_SVECTOR *joint;
    sint16 *angle;
    sint32 turn;
    uint8 idx;
    uint8 flags;

    spin = (ST19_SPIN *)&wp->value_2C8;
    pl   = &Player_work;
    if (spin->timer_6C == 0)
    {
        idx = 4;
        spin->value_85 |= 8;
        if (wp->routine_3 == 0)
        {
            idx = 2;
        }
        do
        {
            if (spin->flags_82 == 0 &&
                (wp->routine_3 != 0 ||
                 (wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &pl->position,
                                                                   wp->rotation.y, 0x20)) &
                                   0xFFF,
                  func_80031DCC(&wp->position_fixed.v, wp->rotation.y, 0x400, &pl->position_fixed,
                                pl->rotation.y, 0x800) != 0)))
            {
                held = (ST19_HELD *)func_80031518();
                if (held != NULL)
                {
                    spin->held_48   = held;
                    held->flags_0   = 1;
                    held->kind_2    = 2;
                    held->handler_4 = 0;
                    held->variant_3 = 0;
                    held->value_D   = 2;
                    flags           = spin->value_85;
                    spin->timer_86  = 10;
                    do
                    {
                        spin->value_85 = flags | 1;
                    } while (0);
                }
            }
        } while (0);

        if (spin->value_85 & 1)
        {
            if (idx == 2)
            {
                spin->held_48->position.x = -0x400;
            }
            else
            {
                spin->held_48->position.x = 0x400;
            }
            spin->held_48->position.y = 0x11E0;
            spin->held_48->position.z = -0x160;
            ApplyMatrix(&ST19_OBJ_MATRIX(wp)[idx].m, &spin->held_48->position,
                        &spin->held_48->position_fixed);
            spin->held_48->position.x = ((STCOM_SVECTOR *)((uint8 *)wp + (idx << 3) + 0x180))->x +
                                        spin->held_48->position_fixed.x;
            spin->held_48->position.y = ((STCOM_SVECTOR *)((uint8 *)wp + (idx << 3) + 0x180))->y +
                                        spin->held_48->position_fixed.y;
            spin->held_48->position.z = ((STCOM_SVECTOR *)((uint8 *)wp + (idx << 3) + 0x180))->z +
                                        spin->held_48->position_fixed.z;
            spin->held_48->position_fixed.x = spin->held_48->position.x << 16;
            spin->held_48->position_fixed.y = spin->held_48->position.y << 16;
            spin->held_48->position_fixed.z = spin->held_48->position.z << 16;
            if (spin->flags_82 != 0)
            {
                joint = &ST19_OBJ_JOINT(wp)[idx];
                wp->rotation.y =
                    (wp->rotation.y + func_80031BEC(joint, &Player_work.position,
                                                    func_80031198(joint, &spin->held_48->position),
                                                    0x20)) &
                    0xFFF;
                // the gun's heading: angle_68[idx / 2 - 1], reached by a byte offset
                angle = (sint16 *)((uint8 *)spin + idx + 0x66);
                turn  = func_80031CA4(joint, &Player_work.position, *angle, 0x20);
                if (*angle == 0 || *angle > 0xC00)
                {
                    *angle = (*angle + turn) & 0xFFF;
                }
                if (spin->held_48->value_C != 0)
                {
                    if (spin->timer_86 == 0)
                    {
                        spin->held_48->angle_64 =
                            func_80031198(&ST19_OBJ_JOINT(wp)[idx], &spin->held_48->position);
                        spin->held_48->value_C -= 0x80;
                        spin->flags_82 = 0;
                        if (wp->routine_3 != 0)
                        {
                            spin->timer_6C = 300;
                            spin->state_81 = 1;
                            spin->flags_82 = 0;
                            wp->routine_3  = 0;
                            spin->value_85 &= ~1;
                        }
                        else
                        {
                            wp->routine_3  = 1;
                            spin->timer_86 = 10;
                            spin->value_85 &= ~1;
                        }
                    }
                    else
                    {
                        spin->timer_86--;
                    }
                }
            }
            else
            {
                spin->flags_82 = 1;
            }
        }
    }
    else
    {
        spin->timer_6C--;
    }
}

void func_801044B4(ST19_OBJ *wp)
{
    ST19_SPIN *spin;

    spin = (ST19_SPIN *)&wp->value_2C8;
    if (spin->angle_68[0] > 0x800)
    {
        spin->angle_68[0] = (spin->angle_68[0] + 0x20) & 0xFFF;
    }
    else
    {
        spin->angle_68[0] = 0;
        spin->flags_82 |= 1;
    }
    if (spin->angle_68[1] > 0x800)
    {
        spin->angle_68[1] = (spin->angle_68[1] + 0x20) & 0xFFF;
    }
    else
    {
        spin->angle_68[1] = 0;
        spin->flags_82 |= 2;
    }
    if (spin->flags_82 == 3)
    {
        spin->flags_82 = 0;
        spin->state_81 = 2;
    }
}

void func_80104548(ST19_FOLLOWER *wp)
{
    STCOM_SVECTOR *target;
    STAGE_OBJ *owner;
    sint16 turn;

    target         = &wp->target_324;
    owner          = func_80036294(wp->u_C.b.byte_C);
    wp->target_324 = owner->position;
    wp->fixed_314  = owner->position_fixed.v;
    func_8002FFC4(target, &wp->fixed_314, owner->rotation.y, 0xC00, 0, 0);
    turn = func_80031BEC(&wp->position, target, wp->rotation.y, 0x20);
    if (turn == 0 && owner->routine_1 != 5)
    {
        wp->value_349    = 0;
        wp->u_C.b.byte_D = 0;
        wp->routine_2    = 0;
        wp->flags_34D &= ~8;
    }
    else
    {
        wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    }
}

void func_8010464C(ST19_OBJ *wp)
{
    if (wp->value_344 != 0)
    {
        wp->value_344--;
        return;
    }
    if (Player_work.position.y <= wp->position.y)
    {
        wp->value_344 = 0;
        wp->value_34B = 1;
        wp->value_34F = 0;
        wp->value_34D |= 2;
    }
}

void func_801046A0(ST19_OBJ *wp)
{
    ST19_SPIN *spin;
    ST19_SHELL *shell;
    STCOM_FIXED_VECTOR step;
    sint8 idx;
    sint8 i;
    sint32 joint;
    STCOM_SVECTOR *pt;
    uint16 turn;

    spin = (ST19_SPIN *)&wp->value_2C8;
    if (wp->value_34F >= 6)
    {
        idx = wp->value_34F - 6;
    }
    else
    {
        idx = wp->value_34F;
    }
    if (spin->value_7C == 0)
    {
        i = 1;
        Sound_call2(0x1B3, &wp->position);
        while (i >= 0)
        {
            if (spin->life_64[i] > 0)
            {
                shell = (ST19_SHELL *)func_80031518();
                if (shell != NULL)
                {
                    shell->flags_0   = 3;
                    shell->kind_2    = 1;
                    shell->handler_4 = 0;
                    shell->value_F   = 4;
                    if (i == 0)
                    {
                        turn = D_80117A14[idx].angle;
                    }
                    else
                    {
                        turn = (0xFFF - D_80117A14[idx].angle) & 0xFFF;
                    }
                    shell->angle_64 = (wp->rotation.y + turn) & 0xFFF;
                    joint           = 3;
                    if (i == 0)
                    {
                        joint = 1;
                    }
                    pt                      = (STCOM_SVECTOR *)((uint8 *)wp + joint * 8 + 0x180);
                    shell->position.x       = pt->x;
                    shell->position.z       = pt->z;
                    shell->position.y       = pt->y;
                    shell->position_fixed.x = shell->position.x << 16;
                    shell->position_fixed.z = shell->position.z << 16;
                    shell->position_fixed.y = shell->position.y << 16;
                    if (i == 0)
                    {
                        func_8002FFC4(&shell->position, &shell->position_fixed,
                                      wp->rotation.y & 0xFFF, D_80117A14[idx].x, D_80117A14[idx].y,
                                      D_80117A14[idx].z);
                    }
                    else
                    {
                        func_8002FFC4(&shell->position, &shell->position_fixed,
                                      wp->rotation.y & 0xFFF, D_80117A14[idx].x, D_80117A14[idx].y,
                                      -D_80117A14[idx].z);
                    }
                    func_80030058(&step, shell->angle_64, 0x600, 0, 0);
                    spin->step_4C = step;
                    func_80030150(&spin->step_4C, &spin->step_5C);
                    shell->speed_44 = spin->step_5C.x << 8;
                    shell->speed_48 = spin->step_5C.z << 8;
                    shell->speed_46 = 0;
                }
            }
            i--;
        }
        spin->value_7C = 6;
        spin->count_87++;
    }
    spin->value_7C--;
    if (spin->count_87 == 0xC)
    {
        spin->value_7C = 0xB4;
        spin->value_83 = 0;
    }
}

void func_80104954(ST19_FOLLOWER *wp)
{
    ST19_FOLLOW_CTL *trail;
    STAGE_OBJ *owner;

    trail = (ST19_FOLLOW_CTL *)wp->trail_2C8;
    if (wp->routine_2 == 0)
    {
        if (wp->u_C.b.byte_D & 4)
        {
            wp->routine_2++;
            trail->speed_74 = 0xC;
            trail->value_76 = 8;
            trail->count_6C = 0;
            trail->stage_80 = 0;
            return;
        }
        owner            = func_80036294(wp->u_C.b.byte_C);
        trail->target_5C = owner->position;
        trail->fixed_4C  = owner->position_fixed.v;
        func_8002FFC4(&trail->target_5C, &trail->fixed_4C, owner->rotation.y, 0xC00, 0, 0);
        wp->rotation.y = (wp->rotation.y +
                          func_80031BEC(&wp->position, &trail->target_5C, wp->rotation.y, 0x20)) &
                         0xFFF;
    }
    else if (wp->u_C.b.byte_D & 4)
    {
        trail->count_6C++;
        if (trail->stage_80 != 4 && trail->count_6C == D_80117A50[trail->stage_80])
        {
            trail->speed_74 = D_80117A44[trail->stage_80];
            trail->stage_80++;
        }
        owner            = func_80036294(wp->u_C.b.byte_C);
        trail->target_5C = owner->position;
        trail->fixed_4C  = owner->position_fixed.v;
        func_8002FFC4(&trail->target_5C, &trail->fixed_4C, owner->rotation.y, 0xC00, 0, 0);
        wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &trail->target_5C,
                                                         wp->rotation.y, trail->speed_74)) &
                         0xFFF;
        if (owner->rotation.y == wp->rotation.y)
        {
            wp->u_C.b.byte_D = 0;
            wp->routine_2    = 0;
        }
    }
}

void func_80104B80(ST19_WHEELS *wp)
{
    ST19_WHEEL_CTL *ctl;
    STCOM_EFFECT *fx;
    uint32 damage;
    uint8 i;
    sint16 *life;
    sint32 offset;

    ctl = &wp->ctl;
    for (i = 1; i < 3; i++)
    {
        damage = ctl->hit_20[i].hit & 0xFFFFFF;
        if (damage != 0)
        {
            Sound_call2(0xA0, &wp->joint_180[i * 2 - 1]);
            offset = i * sizeof(*life);
            life   = (sint16 *)((uint8 *)ctl + offset + ST19_WHEEL_LIFE_OFFSET);
            *life -= damage;
            wp->joint_180[i * 2 - 1].pad = 0x7FFF;
        }
        life = ctl->life_62;
        if (life[i] < 0)
        {
            if (ctl->spark_0[i - 1] == NULL)
            {
                ctl->spark_0[i - 1] =
                    func_8010E99C(&ctl->wheel_10[i - 1], D_80117A5C.width, D_80117A5C.type,
                                  D_80117A5C.count, D_80117A5C.rise, 0);
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 0x40;
                    fx->value_D           = 1;
                    fx->sprite.position.x = ctl->wheel_10[i - 1].x;
                    fx->sprite.position.y = ctl->wheel_10[i - 1].y;
                    fx->sprite.position.z = ctl->wheel_10[i - 1].z;
                }
            }
            else
            {
                ctl->spark_0[i - 1]->x_1C = ctl->wheel_10[i - 1].x;
                ctl->spark_0[i - 1]->y_1E = ctl->wheel_10[i - 1].y;
                ctl->spark_0[i - 1]->z_20 = ctl->wheel_10[i - 1].z;
            }
        }
    }
}

void func_80104D38(ST19_WHEELS *wp)
{
    func_80104B80(wp);
    D_80117A00[wp->routine_1](wp);
    wp->ctl.wheel_10[0] = wp->joint_180[1];
    wp->ctl.fixed_4C.x  = wp->ctl.wheel_10[0].x << 16;
    wp->ctl.fixed_4C.y  = wp->ctl.wheel_10[0].y << 16;
    wp->ctl.fixed_4C.z  = wp->ctl.wheel_10[0].z << 16;
    func_8002FFC4(&wp->ctl.wheel_10[0], &wp->ctl.fixed_4C, wp->rotation.y & 0xFFF, 0, -0xD40,
                  -0x698);
    wp->ctl.wheel_10[1] = wp->joint_180[3];
    wp->ctl.fixed_4C.x  = wp->ctl.wheel_10[1].x << 16;
    wp->ctl.fixed_4C.y  = wp->ctl.wheel_10[1].y << 16;
    wp->ctl.fixed_4C.z  = wp->ctl.wheel_10[1].z << 16;
    func_8002FFC4(&wp->ctl.wheel_10[1], &wp->ctl.fixed_4C, wp->rotation.y & 0xFFF, 0, -0xD40,
                  0x698);
    func_80032538(wp);
    STAGE_WHEEL_SP->wheel_138 = wp->ctl.wheel_68;
    STAGE_WHEEL_SP->wheel_148 = wp->ctl.wheel_6A;
    func_8003346C(wp);
}

void func_80104E94(ST19_OBJ *wp)
{
    wp->anim_AC = 1;
    func_800322A8(wp, 1, 0);
    wp->routine_1++;
    Sound_call2(0x1B4, &wp->position);
    if (wp->value_34D & 1)
    {
        func_800318D8((void *)wp->value_310);
    }
}

void func_80104F04(ST19_OBJ *wp)
{
    if (wp->value_A6 & 1)
    {
        wp->value_44.words.integer = 0;
        wp->value_4C.words.integer = 0x40;
        wp->routine_1++;
    }
}

void func_80104F34(ST19_OBJ *wp)
{
    STCOM_SVECTOR *temp_s0;

    func_8002FEA4(wp, 0, wp->value_44.words.integer, 0);
    wp->value_44.words.integer =
        (uint16)wp->value_44.words.integer + (uint16)wp->value_4C.words.integer;
    if (func_8004B414(wp) & 0x3000)
    {
        temp_s0 = &wp->position;
        Sound_call2(0x1B5, temp_s0);
        wp->anim_AC = 2;
        wp->routine_1++;
        func_800322A8(wp, 2, 0);
        Swing_Camera2(0xF, 0x7D0, 0x1388, temp_s0);
        wp->value_334 = 0;
        wp->position.y += 0x120;
    }
}

void func_80104FE8(ST19_SPARKER *wp)
{
    STCOM_EFFECT *ep;
    uint8 joint;
    uint8 idx;

    if (wp->value_A7 == -1)
    {
        if (wp->timer_334 == 0)
        {
            // The offset recomputes the index rather than reusing idx: retail multiplies twice.
            idx           = wp->random_346 & 7;
            joint         = D_80117A64[idx].joint_0;
            wp->spark_324 = D_80117A64[wp->random_346 & 7].ofs_2;
            ep            = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0           = 5;
                ep->kind_2            = 0x80;
                ep->variant_3         = 0x40;
                ep->value_D           = wp->random_346 & 3;
                ep->sprite.position.x = wp->joint_180[joint].x + wp->spark_324.x;
                ep->sprite.position.y = wp->joint_180[joint].y + wp->spark_324.y;
                ep->sprite.position.z = wp->joint_180[joint].z + wp->spark_324.z;
            }
            wp->timer_334 = 4;
        }
        else
        {
            wp->timer_334--;
        }
        if (Sce_flag_test(0x52))
        {
            wp->routine_1++;
        }
    }
}

void func_8010514C(void)
{
}

void func_80105154(STAGE_OBJ *wp)
{
    D_80117AB4[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_80033A28(wp);
        func_8003346C(wp);
    }
}

void func_8010522C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->rotation.y     = 0x400;
        wp->flags_0 |= 2;
        func_8002F9C4(wp, &wp->variant_3);
        func_800322A8(wp, 8, 0);
        func_80032538(wp);
        func_800334C4(wp);
        wp->u_C.b.byte_D++;
        wp->routine_2++;
        if (STAGE_SCENE_BYTE(8) == 5)
        {
            wp->routine_1 = 4;
            wp->routine_2 = 0;
        }
    }
}

void func_801052E8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = -0x82;
        func_80032538(wp);
        func_800334C4(wp);
        wp->routine_2++;
    }
}

void func_8010533C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = 0x46;
        func_80032538(wp);
        func_800334C4(wp);
        wp->routine_2++;
    }
}

void func_80105390(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
}

void func_801053B8(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.x = -0x6A4;
        wp->position.y = -0x14;
        wp->position.z = -0x9F6;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 0x2D)
    {
        wp->u_C.b.byte_D = 0;
    }
}

void func_80105408(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 9, 0);
        wp->u_C.b.byte_D++;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 5)
    {
        wp->u_C.b.byte_D = 0;
    }
}

void func_80105474(ST19_OBJ *wp)
{
    ST19_CTL *ctl;
    sint8 i;

    ctl                     = (ST19_CTL *)&wp->reserved2E6[2];
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0;
    for (i = 0; i < 8; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    ctl->random_78 = rand();
    D_80117B38[wp->routine_0](wp);
}

void func_8010556C(ST19_OBJ *wp)
{
    ST19_CTL *ctl;
    STAGE_OBJ *child;
    sint8 i;

    wp->flags_0 |= 0x42;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    wp->u_64.w[0]      = 0;
    wp->u_70.w[0]      = 0;
    wp->value_74       = 0;
    wp->data_78        = D_80117ACC;
    func_80036478(ST19_OBJ_CTL(wp)->track_4C, 0, -0x60);
    ctl           = ST19_OBJ_CTL(wp);
    wp->u_70.b[3] = D_80098844[wp->kind_2]->value_A;
    wp->value_B2 = wp->value_B0 = wp->value_6E = D_80098844[wp->kind_2]->value_8 << 6;
    ctl->life_70[0]                            = D_80098844[wp->kind_2]->value_B << 4;
    ctl->life_70[1]                            = D_80098844[wp->kind_2]->value_B << 4;
    wp->routine_0                              = 1;
    wp->routine_1                              = 0;
    wp->scale.v.pad                            = 0;
    for (i = 0; i < 8; i++)
    {
        wp->pal[i].color = 0x4210;
    }
    ctl->flags_7B |= 4;
    wp->anim_AC      = 3;
    wp->anim_prev_AD = 3;
    func_80032304(wp, wp->anim_AC, 0);
    func_8003346C(wp);
    child = func_80031418();
    if (child != NULL)
    {
        child->flags_0            = 1;
        child->kind_2             = 0x40;
        child->variant_3          = 0;
        child->value_4            = 0;
        child->reserved05         = 0;
        child->rotation.y         = wp->rotation.y;
        child->u_C.b.byte_C       = wp->value_1;
        child->u_C.b.byte_D       = 0;
        child->u_E.b.byte_E       = 0;
        child->u_E.b.byte_F       = 0;
        child->position.x         = wp->value_180;
        child->position.y         = wp->value_182;
        child->position.z         = wp->value_184;
        child->position_fixed.v.x = child->position.x << 16;
        child->position_fixed.v.y = child->position.y << 16;
        child->position_fixed.v.z = child->position.z << 16;
    }
    wp->u_C.b.byte_C   = child->value_1;
    wp->data_78        = D_80117ACC;
    ctl->timer_7C      = 0x14;
    ctl->value_80      = 0xC;
    ctl->value_81      = 8;
    ctl->turn_68[2]    = 0;
    ctl->turn_68[0]    = 0;
    ctl->turn_68[2]    = 0xF0;
    ctl->turn_68[1]    = 0;
    ctl->gun_7E        = 0;
    ctl->value_82      = 0;
    ctl->turn_68[3]    = 0;
    ctl->cell_7F       = 0;
    ctl->hit_2C.hit    = 0;
    ctl->hit_34[0].hit = 0;
    ctl->hit_34[1].hit = 0;
    ctl->count_7D      = 0;
    ctl->hit_34[2].hit = 0;
    ctl->spark_8       = NULL;
    ctl->spark_0[0]    = NULL;
    ctl->spark_0[1]    = NULL;
    ctl->life_70[2]    = 0;
    ctl->turn_68[3]    = 0x68;
    func_8005D620(wp, 0, 0, 0x60, 0x2C786060);
}

void func_80105818(ST19_TURRET *wp)
{
    ST19_CTL *ctl;

    func_80106CF4(wp);
    ctl = &wp->ctl;
    if (wp->routine_0 != 3)
    {
        if (ctl->flags_7B & 4)
        {
            func_80107040(wp);
        }
        func_8003648C(ctl->track_4C, wp);
        D_80117B50[wp->routine_1](wp);
        if (ctl->gun_7E != -1 && (ctl->flags_7B & 4))
        {
            D_80117B48[ctl->count_7D](wp);
        }
        func_80032538(wp);
        ST19_SP_ROT[3].y = ctl->turn_68[0];
        ST19_SP_ROT[6].y = ctl->turn_68[1];
        func_8003346C(wp);
        ctl->pos_1C = wp->joint_180[0];
        ctl->pos_1C.y += 0x40;
        func_800341BC(&ctl->pos_1C, 0xB4, 0, 0x8000, wp->value_1, &ctl->hit_2C,
                      wp->hit_kind_73 | 0x5080000, 0, 0);
        ctl->pos_1C = wp->joint_180[1];
        ctl->pos_1C.y += 0x14;
        func_800341BC(&ctl->pos_1C, 0xA0, 0, 0x8000, wp->value_1, &ctl->hit_34[2],
                      wp->hit_kind_73 | 0x5080000, 0, 0x80);
        ctl->pos_1C = wp->joint_180[2];
        ctl->pos_1C.y += 0x59;
        func_800341BC(&ctl->pos_1C, 0xA0, 0, 0x8000, wp->value_1, &ctl->hit_34[2],
                      wp->hit_kind_73 | 0x5080000, 0, 0x80);
        ctl->pos_1C = wp->joint_180[5];
        ctl->pos_1C.y += 0x59;
        func_800341BC(&ctl->pos_1C, 0xA0, 0, 0x8000, wp->value_1, &ctl->hit_34[2],
                      wp->hit_kind_73 | 0x5080000, 0, 0x80);
        ctl->pos_1C = wp->joint_180[3];
        ctl->pos_1C.y += 0xA0;
        ctl->fixed_C.x = ctl->pos_1C.x << 16;
        ctl->fixed_C.y = ctl->pos_1C.y << 16;
        ctl->fixed_C.z = ctl->pos_1C.z << 16;
        func_8002FFC4(&ctl->pos_1C, &ctl->fixed_C, wp->rotation.y & 0xFFF, 0x2C0, 0, 0);
        func_800341BC(&ctl->pos_1C, 0xA3, 0, 0x8000, wp->value_1, &ctl->hit_34[2],
                      wp->hit_kind_73 | 0x5080000, 0, 0x80);
        ctl->pos_1C = wp->joint_180[6];
        ctl->pos_1C.y += 0xA0;
        ctl->fixed_C.x = ctl->pos_1C.x << 16;
        ctl->fixed_C.y = ctl->pos_1C.y << 16;
        ctl->fixed_C.z = ctl->pos_1C.z << 16;
        func_8002FFC4(&ctl->pos_1C, &ctl->fixed_C, wp->rotation.y & 0xFFF, 0x2C0, 0, 0);
        func_800341BC(&ctl->pos_1C, 0xA3, 0, 0x8000, wp->value_1, &ctl->hit_34[2],
                      wp->hit_kind_73 | 0x5080000, 0, 0x80);
        if (ctl->life_70[0] > 0)
        {
            ctl->pos_1C = wp->joint_180[4];
            ctl->pos_1C.y -= 0x20;
            func_800341BC(&ctl->pos_1C, 0x24, 0, 0x8000, wp->value_1, &ctl->hit_34[0],
                          wp->hit_kind_73 | 0x4080000, 0, 0);
        }
        if (ctl->life_70[1] > 0)
        {
            ctl->pos_1C = wp->joint_180[7];
            ctl->pos_1C.y -= 0x20;
            func_800341BC(&ctl->pos_1C, 0x24, 0, 0x8000, wp->value_1, &ctl->hit_34[1],
                          wp->hit_kind_73 | 0x4080000, 0, 0);
        }
        if ((wp->flags_A6 & 1) || (ctl->flags_7B & 1))
        {
            ctl->flags_7B &= ~2;
            if (ctl->flags_7B & 1)
            {
                if (D_800A395F == 0)
                {
                    Swing_Camera2(0xF, 0x7D0, 0x1388, &wp->position);
                }
            }
            else
            {
                Sound_call2(0x1B0, &wp->position);
                Swing_Camera2(0xF, 0x7D0, 0x1388, &wp->position);
            }
            ctl->flags_7B |= 1;
        }
        if (wp->flags_A6 & 4)
        {
            ctl->flags_7B = (ctl->flags_7B & ~1) | 2;
        }
    }
    else
    {
        func_80032538(wp);
        func_8003346C(wp);
    }
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 300, 0x200, 1);
    }
    ctl->hit_2C.hit    = 0;
    ctl->hit_34[0].hit = 0;
    ctl->hit_34[1].hit = 0;
    ctl->hit_34[2].hit = 0;
}

void func_80105E10(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80105E30(ST19_TURRET *wp)
{
    ST19_CTL *ctl;
    STCOM_PL_WORK *pl;
    sint32 joint;

    pl  = &Player_work;
    ctl = &wp->ctl;
    if (pl->position.y >= func_80036294(wp->owner_C)->position.y &&
        func_80031DCC(&wp->position_fixed, wp->rotation.y, 0x400, &pl->position_fixed,
                      pl->rotation.y, 0x800) != 0)
    {
        joint = 7;
        if (ctl->gun_7E == 0)
        {
            joint = 4;
        }
        if (ctl->life_70[ctl->gun_7E] > 0)
        {
            ctl->turn_68[ctl->gun_7E] =
                (ctl->turn_68[ctl->gun_7E] +
                 func_80031BEC(&wp->joint_180[joint], &pl->position,
                               (wp->rotation.y + ctl->turn_68[ctl->gun_7E]) & 0xFFF, 0xC)) &
                0xFFF;
        }
        if (ctl->timer_7C == 0)
        {
            if (ctl->life_70[ctl->gun_7E] > 0)
            {
                if (wp->dist_80 <= 0x7FFFFF)
                {
                    ctl->fixed_C.x = wp->joint_180[joint].x << 16;
                    ctl->fixed_C.y = wp->joint_180[joint].y << 16;
                    ctl->fixed_C.z = wp->joint_180[joint].z << 16;
                    if (func_80031DCC(&ctl->fixed_C,
                                      (wp->rotation.y + ctl->turn_68[ctl->gun_7E]) & 0xFFF, 0x10,
                                      &pl->position_fixed, pl->rotation.y, 0x800) != 0)
                    {
                        ctl->count_7D++;
                    }
                }
            }
            else
            {
                ctl->count_7D++;
            }
        }
        else
        {
            ctl->timer_7C--;
        }
    }
}

void func_8010601C(ST19_TURRET *wp)
{
    STCOM_PL_WORK *pl;
    ST19_CTL *ctl;
    ST19_SHELL *shell;
    STAGE_FX *fx;
    sint32 joint;
    sint32 life;
    STCOM_SVECTOR *target;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (wp->ctl.gun_7E == 0)
    {
        life = wp->ctl.life_70[0];
    }
    else if (wp->ctl.gun_7E == 1)
    {
        life = wp->ctl.life_70[1];
    }
    else
    {
        return;
    }
    if (life <= 0)
    {
        wp->ctl.timer_7C = 0x14;
        wp->ctl.count_7D = 0;
        wp->ctl.gun_7E ^= 1;
        return;
    }
    joint = 4;
    if (ctl->gun_7E != 0)
    {
        joint = 7;
    }
    shell = (ST19_SHELL *)func_80031518();
    if (shell != NULL)
    {
        target = &pl->position;
        Sound_call2(0x1B1, &wp->position);
        shell->flags_0          = 3;
        shell->kind_2           = 1;
        shell->handler_4        = 0;
        shell->value_F          = 1;
        shell->position.x       = wp->joint_180[joint].x;
        shell->position.y       = wp->joint_180[joint].y - 0x20;
        shell->position.z       = wp->joint_180[joint].z;
        shell->position_fixed.y = shell->position.y << 16;
        shell->position_fixed.z = shell->position.z << 16;
        shell->position_fixed.x = shell->position.x << 16;
        func_8002FFC4(&shell->position, &shell->position_fixed,
                      (wp->rotation.y + ctl->turn_68[ctl->gun_7E]) & 0xFFF, 0x770, 0, 0);
        // A one-pass block (perhaps a Capcom macro): its loop weight gives pl retail's register.
        do
        {
            func_800302E4(target, &wp->joint_180[joint]);
            pl->value_C4.x = pl->position.x;
            pl->value_C4.y = pl->position.y;
            pl->value_C4.z = pl->position.z;
            func_80030EE8(shell, &pl->value_C4, 0x62);
        } while (0);
    }
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 3;
        fx->kind_2    = 0xF;
        fx->variant_3 = 3;
        fx->value_C   = 1;
        fx->x_1C      = shell->position.x;
        fx->y_1E      = shell->position.y;
        fx->z_20      = shell->position.z;
    }
    ctl->timer_7C = 0x14;
    ctl->count_7D = 0;
    ctl->gun_7E ^= 1;
    if (ctl->life_70[0] <= 0 && ctl->life_70[1] <= 0)
    {
        ctl->gun_7E = -1;
    }
}

// The flags load sits in a one-pass loop between ctl and pl (prologue order). The first lookup's
// `next = cell` is the else arm, which reorg moves into the branch delay slot.
void func_80106238(ST19_TURRET *wp)
{
    uint32 dir;
    ST19_CTL *ctl;
    uint8 cell;
    STAGE_PL_VIEW *pl;
    uint32 hit;
    sint16 angle;
    sint16 next;
    uint8 flags;

    dir = 0;
    ctl = &wp->ctl;
    do
    {
        flags = wp->ctl.flags_7B;
    } while (0);
    pl = &STAGE_PL;
    if (flags & 4)
    {
        angle = func_80031198(&wp->position, &pl->position);
        if (((angle - 0x600) & 0xFFF) < 0x400)
        {
            dir = ((angle + 0x800) & 0xFFF) | 0x20000;
        }
        else if (((angle - 0x200) & 0xFFF) < 0x400)
        {
            dir = ((angle - 0x400) & 0xFFF) | 0x10000;
        }
        else if (((angle + 0x200) & 0xFFF) < 0x400)
        {
            dir = (angle & 0xFFF) | 0x30000;
        }
        else if (((angle + 0x600) & 0xFFF) < 0x400)
        {
            dir = (angle + 0x400) & 0xFFF;
        }
        cell = ((uint8 *)D_80117B04)[ctl->cell_7F * 4 + ((sint32)dir >> 16)];
        if (cell == 0xFF)
        {
            ctl->rot_24.x = 2;
            ctl->rot_24.y = 9;
            ctl->rot_24.z = 2;
            wp->value_C4  = wp->position;
            pl->value_C4  = pl->position;
            hit           = func_80030628(wp, pl, &ctl->rot_24, &ctl->fixed_C, 0x800);
            if (((uint8 *)D_80117B04)[ctl->cell_7F * 4 + (hit & 1)] == cell)
            {
                next = ((uint8 *)D_80117B04)[ctl->cell_7F * 4 + 2 + ((hit & 0x10) >> 4)];
            }
            else
            {
                next = 0xFF;
            }
        }
        else
        {
            next = cell;
        }
        wp->value_44.half[0] = 0x7C;
        ctl->value_80        = 0xC;
        ctl->value_81        = 8;
        if (next == 0xFF)
        {
            for (dir = 0; dir < 4;)
            {
                next = ((uint8 *)D_80117B04)[ctl->cell_7F * 4 + dir];
                dir++;
                if (next != 0xFF)
                {
                    dir = 4;
                }
            }
        }
        ctl->cell_7F  = next;
        wp->routine_1 = 5;
        ctl->flags_7B &= ~1;
    }
}

void func_801064A0(ST19_TURRET *wp)
{
    ST19_CTL *ctl;
    ST19_10C *shell;
    STAGE_FX *fx;
    sint8 i;

    ctl = &wp->ctl;
    if (wp->value_A7 == -1)
    {
        wp->anim_prev_AD = 0xFF;
        wp->anim_AC      = 1;
        wp->routine_1++;
        func_80032304(wp, 1, 0);
        Sound_call2(0x1B2, &wp->position);
        for (i = 0; i < 2; i++)
        {
            shell = func_80031518();
            if (shell != NULL)
            {
                shell->variant_3          = 5;
                shell->flags_0            = 1;
                shell->kind_2             = 0;
                shell->target_B8          = &STAGE_PL.value_3A8;
                shell->position.x         = wp->joint_180[i * 3 + 2].x;
                shell->position.y         = wp->joint_180[i * 3 + 2].y - 0x50;
                shell->position.z         = wp->joint_180[i * 3 + 2].z;
                shell->position_fixed.v.x = shell->position.x << 16;
                shell->position_fixed.v.y = shell->position.y << 16;
                shell->position_fixed.v.z = shell->position.z << 16;
                if (i == 0)
                {
                    func_8002FFC4(&shell->position, &shell->position_fixed.v,
                                  wp->rotation.y & 0xFFF, 0xA30, 0, 0xB0);
                }
                else
                {
                    func_8002FFC4(&shell->position, &shell->position_fixed.v,
                                  wp->rotation.y & 0xFFF, 0xA30, 0, -0xB0);
                }
                ctl->rot_24.z = 0;
                ctl->rot_24.x = -(rand() & 0x3FF);
                ctl->rot_24.y = rand() & 0xFFF;
                RotMatrixYXZ(&ctl->rot_24, &shell->matrix_8C.m);
                ctl->fixed_C.z = 0x200;
                ctl->fixed_C.y = 0x200;
                ctl->fixed_C.x = 0x200;
                ScaleMatrix(&shell->matrix_8C.m, &ctl->fixed_C);
            }
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0   = 3;
                fx->kind_2    = 0xF;
                fx->variant_3 = 3;
                fx->value_C   = 1;
                fx->x_1C      = shell->position.x;
                fx->y_1E      = shell->position.y;
                fx->z_20      = shell->position.z;
            }
        }
    }
}

void func_801066C0(ST19_MOVER *wp)
{
    if (wp->flags_363 & 2)
    {
        func_8002FEA4(wp, wp->value_44.half[0], 0, 0);
        wp->target_30C.x = D_80117AD8[wp->point_367][0];
        wp->target_30C.z = D_80117AD8[wp->point_367][1];
        wp->target_30C.y = wp->position.y;
        if (wp->flags_363 & 8)
        {
            wp->dist_344 = func_800302E4(&wp->position, &wp->target_30C);
            wp->flags_363 &= ~8;
        }
        wp->dist_prev_348 = wp->dist_344;
        wp->dist_344      = func_800302E4(&wp->position, &wp->target_30C);
        if (wp->dist_prev_348 - wp->dist_344 < 0)
        {
            wp->position.x = D_80117AD8[wp->point_367][0];
            wp->position.z = D_80117AD8[wp->point_367][1];
            wp->routine_1++;
        }
    }
}

void func_801067D0(ST19_OBJ *wp)
{
    if (wp->value_A6 & 0x10)
    {
        wp->anim_AC = 5;
        func_80032304(wp, 5, 0);
        wp->routine_1++;
    }
    if (wp->value_A6 & 0x20)
    {
        wp->anim_AC = 4;
        func_80032304(wp, 4, 0);
        wp->routine_1++;
    }
}

void func_80106860(ST19_MOVER *wp)
{
    ST19_CTL *ctl;
    sint16 turn;

    ctl = (ST19_CTL *)wp->ctl_2E8;
    if (ctl->flags_7B & 4)
    {
        wp->target_30C.x = D_80117AD8[ctl->cell_7F][0];
        wp->target_30C.z = D_80117AD8[ctl->cell_7F][1];
        wp->target_30C.y = wp->position.y;
        turn = func_80031BEC(&wp->position, &wp->target_30C, wp->rotation.y, ctl->value_80);
        if (!(ctl->flags_7B & 0x10))
        {
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
        }
        if (turn != 0 && wp->anim_AC != wp->anim_prev_AD)
        {
            if (turn > 0)
            {
                wp->anim_AC      = 2;
                wp->anim_prev_AD = 2;
            }
            else
            {
                wp->anim_AC      = 3;
                wp->anim_prev_AD = 3;
            }
            func_80032304(wp, wp->anim_AC, 0);
        }
        if (wp->flags_A6 & 8)
        {
            func_80036294(wp->u_C.b.byte_C)->u_C.b.byte_D = 4;
        }
        ctl->value_81 += 8;
        ctl->value_80 = ctl->value_81 / 10 + 0xC;
        ctl->value_81 %= 10;
        if (turn == 0)
        {
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
                ctl->flags_7B = (ctl->flags_7B | 8) & ~0x10;
            }
        }
        else if (wp->value_A7 == -1)
        {
            ctl->flags_7B &= ~0x10;
            func_80032304(wp, wp->anim_AC, 0);
            ctl->value_80 = 0xC;
            ctl->value_81 = 8;
        }
        else if (wp->flags_A6 & 0x40)
        {
            ctl->value_80 = 0xC;
            ctl->value_81 = 8;
            ctl->flags_7B |= 0x10;
        }
    }
}

void func_80106A8C(ST19_OBJ *wp)
{
    if (wp->value_A7 == -1)
    {
        if (wp->routine_1 == 6)
        {
            wp->routine_1 = 1;
        }
        else
        {
            wp->routine_1++;
        }
    }
}

void func_80106AC0(ST19_OBJ *wp)
{
    if (wp->value_A7 == -1)
    {
        wp->routine_1 = 0;
    }
}

void func_80106ADC(ST19_TURRET *wp)
{
    ST19_CTL *ctl;
    ST19_10C *shell;
    STAGE_FX *fx;
    sint8 i;

    ctl = &wp->ctl;
    if (wp->value_A7 == -1)
    {
        wp->routine_1 = 0;
        if (ctl->life_70[2] == 0) // here a timer: frames to the next pair of shells
        {
            Sound_call2(0x1B2, &wp->position);
            for (i = 0; i < 2; i++)
            {
                shell = func_80031518();
                if (shell != NULL)
                {
                    shell->variant_3          = 5;
                    shell->flags_0            = 1;
                    shell->kind_2             = 0;
                    shell->target_B8          = &STAGE_PL.value_3A8;
                    shell->position.x         = wp->joint_180[i * 3 + 2].x;
                    shell->position.y         = wp->joint_180[i * 3 + 2].y - 0x50;
                    shell->position.z         = wp->joint_180[i * 3 + 2].z;
                    shell->position_fixed.v.x = shell->position.x << 16;
                    shell->position_fixed.v.y = shell->position.y << 16;
                    shell->position_fixed.v.z = shell->position.z << 16;
                    if (i == 0)
                    {
                        func_8002FFC4(&shell->position, &shell->position_fixed.v,
                                      wp->rotation.y & 0xFFF, 0xA30, 0, 0xB0);
                    }
                    else
                    {
                        func_8002FFC4(&shell->position, &shell->position_fixed.v,
                                      wp->rotation.y & 0xFFF, 0xA30, 0, -0xB0);
                    }
                    ctl->rot_24.z = 0;
                    ctl->rot_24.x = -(rand() & 0x3FF);
                    ctl->rot_24.y = rand() & 0xFFF;
                    RotMatrixYXZ(&ctl->rot_24, &shell->matrix_8C.m);
                    ctl->fixed_C.z = 0x200;
                    ctl->fixed_C.y = 0x200;
                    ctl->fixed_C.x = 0x200;
                    ScaleMatrix(&shell->matrix_8C.m, &ctl->fixed_C);
                }
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0   = 3;
                    fx->kind_2    = 0xF;
                    fx->variant_3 = 3;
                    fx->value_C   = 1;
                    fx->x_1C      = shell->position.x;
                    fx->y_1E      = shell->position.y;
                    fx->z_20      = shell->position.z;
                }
            }
            ctl->life_70[2] = 0xB4;
        }
        else
        {
            ctl->life_70[2]--;
        }
    }
}

void func_80106CF4(ST19_TURRET *wp)
{
    ST19_CTL *ctl;
    STAGE_OBJ *owner;
    STCOM_EFFECT *fx;
    uint32 damage;
    uint8 i;

    ctl    = &wp->ctl;
    damage = ctl->hit_2C.hit & 0xFFFFFF;
    if (damage != 0)
    {
        owner = func_80036294(wp->owner_C);
        wp->life_6E -= damage;
        if (wp->life_6E >= 0)
        {
            for (i = 0; i < 8; i++)
            {
                wp->joint_180[i].pad = 0x7FFF;
            }
            owner->u_E.b.byte_E = 1;
            Sound_call2(0xA0, &wp->position);
        }
    }
    if (wp->life_6E < 0)
    {
        if (wp->routine_0 != 3)
        {
            owner            = func_80036294(wp->owner_C);
            wp->routine_0    = 3;
            wp->routine_1    = 0;
            wp->routine_2    = 0;
            owner->routine_0 = 3;
            owner->routine_1 = 0;
            owner->routine_2 = 0;
            wp->anim_AC      = 6;
            func_80032304(wp, 6, 0);
        }
        if (ctl->spark_8 == NULL)
        {
            ctl->spark_8 = ST19_SPARK_NEW(&wp->joint_180[0], D_80117B30.width, D_80117B30.type,
                                          D_80117B30.count, D_80117B30.rise);
        }
        else
        {
            ctl->spark_8->x_1C = wp->joint_180[0].x;
            ctl->spark_8->y_1E = wp->joint_180[0].y;
            ctl->spark_8->z_20 = wp->joint_180[0].z;
        }
    }
    for (i = 0; i < 2; i++)
    {
        damage = ctl->hit_34[i].hit & 0xFFFFFF;
        if (damage != 0)
        {
            if (ctl->life_70[i] >= 0)
            {
                Sound_call2(0xA0, &wp->joint_180[i * 2 + 4]);
                ctl->life_70[i] -= damage;
                wp->joint_180[i * 3 + 4].pad = 0x7FFF;
            }
        }
        if (ctl->life_70[i] < 0)
        {
            if (ctl->spark_0[i] == NULL)
            {
                ctl->spark_0[i] =
                    ST19_SPARK_NEW(&wp->joint_180[i * 3 + 4], D_80117B30.width, D_80117B30.type,
                                   D_80117B30.count, D_80117B30.rise);
                wp->part_F8[i * 3 + 4].value_3 = -1;
                fx                             = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 0x40;
                    fx->value_D           = 1;
                    fx->sprite.position.x = wp->joint_180[i * 3 + 4].x;
                    fx->sprite.position.y = wp->joint_180[i * 3 + 4].y - 0x20;
                    fx->sprite.position.z = wp->joint_180[i * 3 + 4].z;
                }
            }
            else
            {
                ctl->spark_0[i]->x_1C = wp->joint_180[i * 3 + 4].x;
                ctl->spark_0[i]->y_1E = wp->joint_180[i * 3 + 4].y - 0x20;
                ctl->spark_0[i]->z_20 = wp->joint_180[i * 3 + 4].z;
            }
        }
    }
}

void func_80107040(STCOM_PL_WORK *arg0)
{
    sint32 temp_v0;

    temp_v0 = func_80049C24(arg0);
    if (temp_v0 != 0)
    {
        func_80037BB4(arg0);
        func_80037738(temp_v0, 0x8000);
    }
}

void func_80107090(ST19_TURRET *wp)
{
    func_80106CF4(wp);
    D_80117B70[wp->routine_1](wp);
    func_80032538(wp);
    func_8003346C(wp);
    wp->ctl.hit_2C.hit    = 0;
    wp->ctl.hit_34[0].hit = 0;
    wp->ctl.hit_34[1].hit = 0;
    wp->ctl.hit_34[2].hit = 0;
}

void func_801070FC(STAGE_OBJ *wp)
{
    wp->anim_AC = 6;
    func_80032304(wp, 6, 0);
    wp->routine_1++;
    Sound_call2(0x1B4, &wp->position);
}

void func_8010714C(ST19_OBJ *wp)
{
    if (wp->value_A6 & 1)
    {
        wp->value_44.words.fraction = 0x4C;
        wp->routine_1++;
    }
}

void func_80107178(ST19_OBJ *wp)
{
    if (wp->value_A7 != -1)
    {
        if (wp->value_A6 & 2)
        {
            wp->value_44.words.fraction = 0x6C;
        }
        func_8002FFC4(&wp->position, &wp->position_fixed.v, (wp->rotation.y + 0x800) & 0xFFF,
                      (sint32)(sint16)wp->value_44.words.fraction, 0, 0);
        return;
    }
    wp->routine_1++;
    func_8005D6E8(wp);
    wp->value_35E = 0x78;
}

void func_8010720C(ST19_TURRET *wp)
{
    ST19_CTL *ctl;
    STCOM_EFFECT *ep;
    sint32 joint;
    uint16 idx;

    ctl = &wp->ctl;
    if (wp->value_A7 != -1)
    {
        return;
    }
    if (ctl->value_82 == 0)
    {
        Sound_call2(0x1B5, &wp->position);
        ctl->value_82 = 1;
    }
    if (ctl->life_70[3] != 0)
    {
        if (!(ctl->life_70[3] & 3))
        {
            // The offset recomputes the index rather than reusing idx: retail multiplies twice.
            idx         = (uint8)ctl->random_78 & 7;
            joint       = D_80117B84[idx].joint_0;
            ctl->rot_24 = D_80117B84[(uint8)ctl->random_78 & 7].offset_2;
            ep          = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0           = 5;
                ep->kind_2            = 0x80;
                ep->variant_3         = 0x40;
                ep->value_D           = ctl->random_78 & 3;
                ep->sprite.position.x = wp->joint_180[joint].x + ctl->rot_24.x;
                ep->sprite.position.y = wp->joint_180[joint].y + ctl->rot_24.y;
                ep->sprite.position.z = wp->joint_180[joint].z + ctl->rot_24.z;
            }
        }
        ctl->life_70[3]--;
    }
    else if (func_80042208() != 0)
    {
        Sce_flag_on(0x52);
        Sound_call2(0xA4, &wp->position);
        wp->routine_1++;
    }
    else
    {
        ctl->life_70[3] = 0x78;
    }
}

void func_801073C4(void)
{
}

void func_801073CC(STAGE_OBJ *wp)
{
    D_80117BD4[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_80033A28(wp);
        func_8003346C(wp);
    }
}

void func_801074A4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->rotation.y     = 0x400;
        wp->flags_0 |= 2;
        func_8002F9C4(wp, &wp->variant_3);
        func_800322A8(wp, 8, 0);
        func_80032538(wp);
        func_800334C4(wp);
        wp->u_C.b.byte_D++;
        wp->routine_2++;
        if (STAGE_SCENE_BYTE(8) == 5)
        {
            wp->routine_1 = 4;
            wp->routine_2 = 0;
        }
    }
}

void func_80107560(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = -0x50;
        func_80032538(wp);
        func_800334C4(wp);
        wp->routine_2++;
    }
}

void func_801075B4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = 0;
        func_80032538(wp);
        func_800334C4(wp);
        wp->routine_2++;
    }
}

void func_80107608(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
}

void func_80107630(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.x = -0x6A4;
        wp->position.y = 0;
        wp->position.z = -0x9F6;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 0x2D)
    {
        wp->u_C.b.byte_D = 0;
    }
}

void func_8010767C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 9, 0);
        wp->u_C.b.byte_D++;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 5)
    {
        wp->u_C.b.byte_D = 0;
    }
}

void func_801076E8(STAGE_OBJ *wp)
{
    D_80117EBC[wp->routine_0](wp);
}

void func_80107724(ST19_OBJ *wp)
{
    ST19_HOME *home;
    ST19_GAME_78 *g;

    home = (ST19_HOME *)&wp->reserved348;
    wp->flags_0 |= 2;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->value_35C      = 0;
    wp->value_35E      = 0;
    wp->value_360      = 0;
    wp->value_35D      = 1;
    wp->value_388      = 0;
    wp->value_38C      = 0;
    wp->value_37C      = 0x04800000;
    wp->data_358       = D_80117BF6;
    wp->data_354       = D_80117C94[wp->variant_3];
    g                  = (ST19_GAME_78 *)&STAGE_GAME.value_78;
    if (g->value_0 != 0 && g->value_1 == 0x19 && g->value_2 == 3)
    {
        D_8011F494 = 1;
    }
    home->pos_0          = wp->position;
    home->rot_8          = wp->rotation.y;
    wp->rotation.x       = 0;
    wp->rotation.z       = 0;
    wp->value_44.half[0] = 0;
    wp->value_48.half[0] = 0;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_78          = D_80117EB0;
    wp->value_10         = 0;
    wp->routine_1        = 0;
    wp->routine_2        = 0;
    wp->routine_3        = 0;
    wp->anim_AC          = 0;
    wp->routine_0++;
    func_800322A8(wp, 0, 0);
    func_80107DD4(wp);
}

void func_80107898(ST19_OBJ *wp)
{
    ST19_HOME *home;
    STCOM_PL_WORK *pl;
    uint8 op;

    home = (ST19_HOME *)&wp->reserved348;
    pl   = &Player_work;
    do
    {
        op = *home->data_10++;
        if (!(op & 0x80))
        {
            wp->routine_1 = op;
        }
        switch (op)
        {
            case 1:
                wp->anim_AC    = *home->data_10++;
                home->timer_16 = *home->data_10++ << 4;
                wp->routine_1  = 1;
                break;
            case 2:
                if (*home->data_10 != 3 || wp->anim_AC == 0)
                {
                    wp->anim_AC = *home->data_10;
                }
                home->data_10 += 2;
                home->sound_2C  = D_80117E8C[home->data_10[-1]];
                home->frames_30 = 1;
                wp->routine_1   = 2;
                home->timer_16  = 0;
                break;
            case 3:
                if (func_80108CAC(pl->position, wp->position, 100, 100))
                {
                    home->data_10 += 5;
                    func_80107898(wp);
                    return;
                }
                wp->anim_AC          = *home->data_10++;
                wp->value_44.half[0] = (sint8)*home->data_10++ << 4;
                home->x_1C           = home->pos_0.x + ((sint8)*home->data_10++ << 4);
                home->z_1E           = home->pos_0.z + ((sint8)*home->data_10++ << 4);
                wp->routine_1        = 3;
                break;
            case 9:
                wp->anim_AC          = *home->data_10++;
                wp->value_44.half[0] = (sint8)*home->data_10++ << 4;
                home->x_1C           = pl->position.x + ((sint8)*home->data_10++ << 4);
                home->z_1E           = pl->position.z + ((sint8)*home->data_10++ << 4);
                wp->routine_1        = 3;
                break;
            case 4:
                wp->anim_AC          = *home->data_10++;
                wp->value_44.half[0] = (sint8)*home->data_10++ << 4;
                home->timer_16       = *home->data_10++ << 3;
                wp->routine_1        = 4;
                break;
            case 5:
                Sound_call2(0x1AD, &wp->position);
                Sound_call2(0x1AE, &wp->position);
                wp->routine_1 = 5;
                wp->routine_2 = 0;
                break;
            case 6:
                wp->routine_1 = 6;
                wp->routine_2 = 0;
                break;
            case 7:
                wp->anim_AC   = *home->data_10++;
                wp->u_64.h[0] = *home->data_10++;
                wp->routine_1 = 7;
                break;
            case 8:
                wp->anim_AC          = *home->data_10++;
                wp->value_44.half[0] = (sint8)*home->data_10++ << 4;
                home->x_1C           = *home->data_10++ << 3;
                home->z_1E           = rand() & 0x3F;
                home->value_20       = rand() & 0x3F;
                home->sound_2C       = D_80117E8C[*home->data_10++];
                home->frames_30      = 1;
                wp->routine_1        = 8;
                wp->routine_2        = 0;
                break;
            case 0x90:
                home->data_10 += (sint8)*home->data_10;
                break;
            case 0x92:
                home->hit_kind_34 = 0x4800001;
                home->flags_14 |= 2;
                break;
            case 0x93:
                home->hit_kind_34 = 0x5800001;
                home->flags_14 |= 2;
                break;
            case 0x94:
                home->hit_kind_34 = 0x4800000;
                home->flags_14 &= ~2;
                break;
            case 0x95:
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                break;
            case 0x91:
                home->data_10 = ((uint8 **)home->data_C)[rand() & 3];
                break;
        }
    } while (!(*home->data_10 & 0x40));
    home->data_10++;
    wp->routine_0++;
    func_80107DD4(wp);
}

void func_80107DD4(ST19_OBJ *wp)
{
    ST19_HOME *home;

    home = (ST19_HOME *)&wp->reserved348;
    if (func_80108CAC(Player_work.position, wp->position, 0x1F40, 0x1F40))
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        wp->scale.v.pad         = 0x4210;
        D_80117ECC[wp->routine_1](wp);
        func_8010896C(wp);
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
        wp->anim_prev_AD = wp->anim_AC;
        home->hitpos_38  = *(STCOM_SVECTOR *)&wp->value_180;
        if (home->hit_15 != 0)
        {
            func_800341BC(&home->hitpos_38, 0x3C, 0, 0x8000, wp->value_1, &home->hit_40,
                          home->hit_kind_34, 0, 0);
        }
        if (!(home->flags_14 & 2))
        {
            func_80051B68(wp, 3, -1, 0);
        }
        home->hit_40   = 0;
        home->value_18 = func_8004B414(wp);
        if (D_8011F494 != 0)
        {
            home->value_18 |= func_80108DB4(wp);
        }
        if (wp->flags_0 & 2)
        {
            func_8002C8CC(wp, 0x30, 0x200, 0);
        }
    }
}

void func_80108018(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80108038(STAGE_OBJ *wp)
{
    wp->routine_0 = 1;
}

void func_80108044(ST19_OBJ *wp)
{
    sint16 temp_v0;

    temp_v0       = (uint16)wp->value_35E - 1;
    wp->value_35E = temp_v0;
    if (!(temp_v0 & 0xFFFF))
    {
        wp->routine_0 = 1;
    }
}

void func_8010806C(ST19_OBJ *wp)
{
    uint16 temp_v1;

    temp_v1       = (uint16)wp->value_35E;
    wp->value_35E = temp_v1 + 1;
    if (temp_v1 != 0)
    {
        func_80108D18(wp);
        if (wp->value_A7 < 0)
        {
            wp->routine_0 = 1;
        }
    }
}

void func_801080C0(ST19_OBJ *wp)
{
    STCOM_SVECTOR target;
    STCOM_PL_WORK *pl;
    ST19_HOME *home;
    uint8 speed;

    speed = 0x20;
    home  = (ST19_HOME *)&wp->reserved348;
    pl    = &Player_work;
    if (wp->anim_AC == 2)
    {
        speed = 0xC8;
    }
    target.x = wp->value_364;
    target.z = wp->value_366;
    wp->rotation.y =
        (wp->rotation.y + func_80031BEC(&wp->position, &target, wp->rotation.y, speed)) & 0xFFF;
    wp->position.y         = func_80048E6C(wp);
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    func_8002FEA4(wp, wp->value_44.half[0], 0, 0);
    if (ST19_ABS(wp->position.x - home->x_1C) <= 0x28 &&
        ST19_ABS(wp->position.z - home->z_1E) <= 0x28)
    {
        wp->routine_0 = 1;
    }
    if (home->value_18 != 0 || func_80108CAC(pl->position, wp->position, 100, 100))
    {
        wp->routine_0 = 1;
    }
}

void func_80108270(ST19_OBJ *wp)
{
    wp->position.y         = func_80048E6C(wp);
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    func_8002FEA4(wp, wp->value_44.half[0], 0, 0);
    if (--wp->value_35E == 0)
    {
        wp->routine_0 = 1;
    }
    if (wp->value_360 != 0 || func_80108CAC(Player_work.position, wp->position, 100, 100))
    {
        wp->routine_0 = 1;
    }
}

void func_80108374(ST19_OBJ *wp)
{
    STCOM_PL_WORK *pl;
    sint32 turn;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            turn = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x800);
            wp->value_44.half[1] = -0x21C;
            wp->value_48.half[0] = 0x5A;
            wp->anim_AC          = 5;
            wp->rotation.y += turn;
            if (wp->value_35D != 0)
            {
                wp->value_35D--;
            }
            wp->routine_2++;
            break;
        case 1:
            wp->routine_2++;
            wp->position.y--;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            break;
        case 2:
            if (wp->position.y >= (sint16)func_80048E6C(wp))
            {
                wp->anim_AC            = 6;
                wp->value_48.half[0]   = 0;
                wp->value_44.half[1]   = 0;
                wp->position.y         = func_80048E6C(wp);
                wp->value_35E          = 0x14;
                wp->position_fixed.v.x = wp->position.x << 16;
                wp->position_fixed.v.y = wp->position.y << 16;
                wp->position_fixed.v.z = wp->position.z << 16;
                wp->routine_2++;
            }
            func_8002FEA4(wp, -0xA0, wp->value_44.half[1], 0);
            if (wp->position.y >= 0)
            {
                wp->position.y = -1;
            }
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            wp->value_44.half[1] += wp->value_48.half[0];
            break;
        case 3:
            wp->position.y         = func_80048E6C(wp);
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            func_8002FEA4(wp, -0x20, 0, 0);
            if (wp->value_A7 < 0)
            {
                wp->routine_0 = 1;
            }
            break;
    }
}

void func_801085A4(ST19_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC            = 9;
            wp->value_44.half[0]   = 0x1E0;
            wp->value_44.half[1]   = 0;
            wp->position.y         = func_80048E6C(wp);
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            break;
        case 7:
            wp->anim_AC          = 0xA;
            wp->value_44.half[0] = 0x1E0;
            wp->value_44.half[1] = -0x120;
            break;
        case 8:
            wp->value_44.half[1] = -0x40;
            break;
        case 12:
            wp->value_44.half[1] = -0xC0;
            break;
        case 13:
            wp->value_44.half[1] = 0x170;
            break;
        case 15:
            wp->value_44.half[1]   = 0;
            wp->value_44.half[0]   = 0xB0;
            wp->position.y         = -1;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->anim_AC            = 0xB;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            break;
        case 26:
            wp->routine_0          = 1;
            wp->position.y         = func_80048E6C(wp);
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            break;
    }
    wp->routine_2++;
    func_8002FEA4(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
}

void func_801086F0(ST19_OBJ *wp)
{
    sint16 turn;

    turn = func_80031BEC(&wp->position, &Player_work.position, wp->rotation.y, wp->u_64.h[0]);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0)
    {
        wp->routine_0 = 1;
    }
}

void func_80108750(ST19_OBJ *wp)
{
    STCOM_SVECTOR target;
    ST19_HOME *home;
    sint32 speed;
    sint32 dx;
    sint32 dz;

    home   = (ST19_HOME *)&wp->reserved348;
    target = Player_work.position;
    target.x += wp->value_366;
    target.z += wp->value_368;
    speed = 0x20;
    if (wp->anim_AC == 2)
    {
        speed = 0xC8;
    }
    wp->rotation.y =
        (wp->rotation.y + func_80031BEC(&wp->position, &target, wp->rotation.y, speed)) & 0xFFF;
    wp->position.y         = func_80048E6C(wp);
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    func_8002FEA4(wp, wp->value_44.half[0], 0, 0);
    func_80108D18(wp);
    dx = wp->position.x - target.x;
    dz = wp->position.z - target.z;
    if (dx * dx + dz * dz < wp->value_364 * wp->value_364)
    {
        wp->routine_0 = 1;
        return;
    }
    if (!func_80108CAC(wp->position, home->pos_0, D_80117CC4[wp->variant_3][0],
                       D_80117CC4[wp->variant_3][1]))
    {
        wp->data_358  = D_80117C64;
        wp->routine_0 = 1;
        wp->data_354  = D_80117C94[wp->variant_3];
    }
}

void func_8010896C(ST19_OBJ *wp)
{
    ST19_HOME *home;

    home = (ST19_HOME *)&wp->reserved348;
    if (wp->value_388 & 0x08000000)
    {
        home->data_10 = D_80117C74;
        if (home->hit_15 < 2)
        {
            home->data_C = &D_80117C94[wp->variant_3][0x20];
        }
        wp->routine_0 = 1;
        return;
    }
    if (wp->routine_1 == 5)
    {
        return;
    }
    if (wp->routine_1 == 6)
    {
        return;
    }
    if (!(home->flags_14 & 1))
    {
        if (func_80108CAC(STAGE_PL.position, home->pos_0, D_80117CC4[wp->variant_3][0],
                          D_80117CC4[wp->variant_3][1]) &&
            func_80108CAC(STAGE_PL.position, wp->position, D_80117CC4[wp->variant_3][2],
                          D_80117CC4[wp->variant_3][3]) &&
            (wp->anim_AC != 0 || STAGE_PL.routine_1 >= 7 ||
             (STAGE_PL.routine_1 >= 2 && STAGE_PL.routine_1 < 4)))
        {
            home->flags_14 |= 1;
            if (home->hit_15 != 0)
            {
                home->data_C  = &D_80117C94[wp->variant_3][0x10];
                home->data_10 = D_80117C54;
                wp->routine_0 = 1;
            }
        }
    }
    else if (!func_80108CAC(STAGE_PL.position, home->pos_0, D_80117CC4[wp->variant_3][0],
                            D_80117CC4[wp->variant_3][1]))
    {
        home->flags_14 &= ~1;
        home->data_C = D_80117C94[wp->variant_3];
    }
}

// Tests whether a is within w of b in x and d in z.
uint8 func_80108CAC(STCOM_SVECTOR a, STCOM_SVECTOR b, sint16 w, sint16 d)
{
    if ((uint16)((a.x - b.x) + w) < w * 2 && (uint16)((a.z - b.z) + d) < d * 2)
    {
        return 1;
    }
    return 0;
}

// Steps a sound script of (id, delay) pairs; 0xFFFF jumps back. Retail calls Sound_call2
// without a prototype (ST19_SOUND_CALL2): the shared sint16 prototype would sign-extend the id.
void func_80108D18(ST19_OBJ *wp)
{
    if (--wp->value_378 == 0)
    {
        if (wp->value_374[0] != 0)
        {
            ST19_SOUND_CALL2(wp->value_374[0], &wp->position);
        }
        wp->value_378 = wp->value_374[1];
        wp->value_374 += 2;
        if (wp->value_374[0] == 0xFFFF)
        {
            wp->value_374 -= wp->value_374[1] * 2;
        }
    }
}

uint8 func_80108DB4(ST19_OBJ *wp)
{
    STCOM_SVECTOR pos;
    uint8 hit;

    hit   = 0;
    pos.x = wp->position.x;
    pos.z = wp->position_prev.z;
    if (func_80108CAC_box(D_80117EF0_S, pos, 0xAA, 0xFA))
    {
        hit                    = 1;
        wp->position.x         = wp->position_prev.x;
        wp->position_fixed.v.x = wp->position_fixed_prev.x;
    }
    pos.x = wp->position_prev.x;
    pos.z = wp->position.z;
    if (func_80108CAC_box(D_80117EF0_S, pos, 0xAA, 0xFA))
    {
        wp->position.z         = wp->position_prev.z;
        wp->position_fixed.v.z = wp->position_fixed_prev.z;
        hit |= 2;
    }
    return hit;
}
