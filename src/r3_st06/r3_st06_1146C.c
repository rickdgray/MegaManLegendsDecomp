#include "common.h"
#include "st06.h"

void func_8011146C(ST06_CRAB *wp)
{
    STCOM_SVECTOR pts[2];
    STCOM_SVECTOR pt;
    ST06_CRAB_CTL *ctl;

    ctl                  = &wp->ctl;
    wp->value_44.half[0] = 0;
    wp->value_44.half[1] = 0;
    if (wp->ctl.u_3C.b.flag_6 == 0)
    {
        pts[0] = wp->ctl.u_3C.b.rec_0[0];
        pts[1] = wp->ctl.u_3C.b.rec_0[1];
    }
    else
    {
        pts[0] = wp->ctl.u_3C.b.rec_0[1];
        pts[1] = wp->ctl.u_3C.b.rec_0[0];
    }
    switch (wp->routine_3)
    {
        case 0:
            wp->rotation.y       = Angle_xz_svector(&wp->position, &pts[1]);
            wp->value_44.half[0] = 0x180;
            if (ctl->owner_0 == NULL)
            {
                if (wp->anim_AC != 3 && wp->anim_AC != 4)
                {
                    wp->anim_AC = 0xC;
                }
                wp->routine_3       = 6;
                ctl->u_3C.b.value_7 = ctl->random_6 & 7;
            }
            else
            {
                wp->anim_AC         = 0;
                wp->routine_3       = 1;
                ctl->u_3C.b.value_7 = (ctl->u_3C.b.flag_6 == 0) ? 7 : 0;
                ctl->flags_4 |= 0x200;
            }
            ctl->flags_4 |= 0x400;
            Sound_call2(0xE6, &wp->position);
            break;
        case 1:
            wp->value_44.half[0] = 0x180;
            if (ctl->owner_0 == NULL)
            {
                wp->anim_AC   = 1;
                wp->routine_3 = 5;
                break;
            }
            pt = ctl->u_3C.b.rec_0[ctl->u_3C.b.value_7 + 2];
            if (ctl->u_3C.b.flag_6 == 0)
            {
                if (wp->position.x < pt.x)
                {
                    break;
                }
            }
            else
            {
                if (wp->position.x > pt.x)
                {
                    break;
                }
            }
            wp->position.x       = pts[1].x;
            wp->value_44.half[0] = 0;
            wp->anim_AC          = 1;
            wp->routine_3++;
            break;
        case 2:
            wp->anim_AC = 1;
            if (wp->value_A7 == -1)
            {
                wp->u_C.ub.byte_C = 8;
                wp->anim_AC       = 2;
                wp->routine_3++;
                Sound_call2(0xE5, &wp->position);
            }
            break;
        case 3:
            ctl->flags_4 &= ~0x400;
            wp->anim_AC = 2;
            if (wp->value_A7 == -1)
            {
                ctl->u_3C.b.value_7 = ctl->random_6 & 7;
                if (ctl->u_3C.b.value_7 == ctl->u_3C.b.value_8)
                {
                    ctl->u_3C.b.value_7 = 7 - ctl->u_3C.b.value_7;
                }
                ctl->u_3C.b.value_8 = ctl->u_3C.b.value_7;
                wp->anim_AC         = 3;
                wp->routine_3++;
            }
            break;
        case 4:
            wp->anim_AC = 3;
            if (wp->value_A7 == -1)
            {
                ctl->flags_4 = (ctl->flags_4 & ~0x200) | 1;
                wp->routine_3 += 2;
            }
            break;
        case 5:
            wp->anim_AC = 1;
            if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 2;
                wp->routine_3 = 3;
                Sound_call2(0xE5, &wp->position);
            }
            break;
        case 6:
            ctl->flags_4 |= 0x400;
            wp->value_44.half[0] = 0x300;
            if (ctl->u_3C.b.flag_6 == 0)
            {
                if (wp->position.x >= pts[1].x)
                {
                    wp->position.x       = pts[1].x;
                    wp->value_44.half[0] = 0;
                    wp->routine_3++;
                }
            }
            else if (pts[1].x >= wp->position.x)
            {
                wp->position.x       = pts[1].x;
                wp->value_44.half[0] = 0;
                wp->routine_3++;
            }
            break;
        case 7:
            ctl->flags_4 |= 0x200;
            wp->value_44.half[1] = 0x100;
            if (wp->position.y >= pts[1].y)
            {
                wp->position.y = pts[1].y;
                ctl->u_3C.b.flag_6 ^= 1;
                if (ctl->owner_0 == NULL)
                {
                    wp->anim_AC = 0;
                    wp->u_C.ub.byte_C |= 2;
                    Sound_call2(0xE7, &wp->position);
                }
                wp->routine_3++;
            }
            break;
        case 8:
            wp->rotation.y = Angle_xz_svector(&wp->position, &pts[1]);
            wp->routine_3++;
            break;
        case 9:
            wp->value_44.half[1] = -0x100;
            if (wp->position.y < -0x63F)
            {
                wp->position.y = -0x640;
                wp->routine_3  = 1;
            }
            break;
    }
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
}

void func_8011193C(ST06_CRAB *wp)
{
    STCOM_EFFECT *fx;

    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        wp->anim_AC   = 9;
        fx            = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0           = 5;
            fx->kind_2            = 0x80;
            fx->variant_3         = 0x42;
            fx->sprite.position.x = wp->joint_180[0].x;
            fx->sprite.position.y = wp->joint_180[0].y;
            fx->sprite.position.z = wp->joint_180[0].z;
        }
        return;
    }
    wp->value_44.half[1] += 0x18;
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
    if (Obj_ceiling_height_get(wp) < wp->position.y - 0x140)
    {
        wp->value_44.half[1]      = 0;
        wp->value_44.half[0]      = 0;
        wp->routine_0             = 2;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
    }
}

void func_80111A30(ST06_CRAB *wp)
{
    sint16 ground;
    sint32 dy;

    ground = Obj_ceiling_height_get(wp);
    dy     = ground - wp->position.y;
    if (dy < -0x10)
    {
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        wp->value_44.half[0] = 0;
        wp->position.y -= 0x10;
    }
    else if (dy > 0x10 && wp->position.y < Player_work.position.y)
    {
        wp->position.y += 0x10;
    }
    wp->position_fixed.v.y = wp->position.y << 16;
}

void func_80111AFC(ST06_CRAB *wp)
{
    sint16 ground;
    sint16 step;
    sint16 y;

    ground = Obj_ceiling_height_get(wp);
    step   = 0;
    y      = wp->position.y;
    if (y >= -0x62F)
    {
        step = -0x10;
    }
    else if (y < -0x650)
    {
        step = 0x10;
    }
    if (ground < y)
    {
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        wp->value_44.half[0] = 0;
        wp->position.y -= 0x10;
    }
    else
    {
        wp->position.y += step;
    }
    wp->position_fixed.v.y = wp->position.y << 16;
}

void func_80111BE0(STCOM_SVECTOR *pos)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 5;
        ep->kind_2    = 0x80;
        ep->variant_3 = 0x42;
        ep->pos_38.x  = pos->x;
        ep->pos_38.y  = pos->y;
        ep->pos_38.z  = pos->z;
    }
}

void func_80111C4C(ST06_CRAB *wp)
{
    ST06_SHOT *shot;

    shot = (ST06_SHOT *)Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0          = 1;
        shot->kind_2           = 6;
        shot->variant_3        = 0x80;
        shot->routine_8        = 0;
        shot->value_C          = 0;
        shot->position         = wp->joint_180[0];
        shot->angle_64         = 0;
        shot->speed_9C         = 0;
        shot->rise_A0          = 0;
        shot->position_fixed.x = shot->position.x << 16;
        shot->position_fixed.y = shot->position.y << 16;
        shot->position_fixed.z = shot->position.z << 16;
        Sound_call2(0xE8, &wp->position);
    }
}

void func_80111CF8(ST06_CRAB *wp)
{
    sint32 next;

    switch (wp->routine_1)
    {
        case 0:
        case 1:
        case 2:
            if (wp->ctl.flags_4 & 0x80)
            {
                wp->ctl.flags_4 &= ~0x200;
                next = 1;
            }
            else if (wp->ctl.flags_4 & 0x100)
            {
                next = 2;
            }
            else
            {
                break;
            }
            wp->ctl.timer_8           = 0;
            wp->routine_1             = next;
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
}

sint32 func_80111D54(ST06_CRAB *wp)
{
    wp->ctl.kind_C     = D_80098844[wp->kind_2]->value_A;
    wp->ctl.hit_pos_10 = wp->joint_180[0];
    func_800341BC(&wp->ctl.hit_pos_10, 0x80, 0, 0x8000, wp->value_1, &wp->ctl.hit_18, wp->ctl.kind_C | 0x4880000, 0x800000, 0);
    return 1;
}

sint32 func_80111DF0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    sint32 hit;
    sint32 damage;

    ctl              = &wp->ctl;
    hit              = wp->ctl.hit_18;
    damage           = hit & 0xFFFFFF;
    wp->life_prev_B2 = wp->life_6E;
    if (damage != 0 && (hit & 0x18000000))
    {
        wp->scale.v.pad = 0x7FFF;
        wp->life_6E -= damage;
        Sound_call2(0xA0, &wp->position);
    }
    if (wp->life_6E <= 0)
    {
        ctl->flags_4              = (ctl->flags_4 & ~2) | 4;
        wp->routine_1             = 3;
        *(uint16 *)&wp->routine_2 = 0;
        wp->u_C.b.byte_C |= 4;
    }
    return 1;
}

void func_80111EA8(STAGE_OBJ *wp)
{
    D_80125368[wp->routine_0](wp);
}

void func_80111EE4(ST06_ACTOR *wp)
{
    ST06_ACTOR_CTL *ctl;

    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x21A021A;
    wp->scale.words[1]       = 0x21A;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 2;
    *(uint32 *)&ctl->timer_4 = 0;
    D_8012BA50               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_8012BA50, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E          = 0x80;
    wp->value_B0          = 0x80;
    wp->value_B2          = 0x80;
    wp->value_78          = D_80125384;
    ctl->timer_A          = 0;
    wp->rotation.x        = 0;
    wp->rotation.z        = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->data_10           = D_80125390;
    if (wp->variant_3 != 0)
    {
        wp->routine_1 = 1;
    }
    else
    {
        wp->routine_1 = 0;
    }
    wp->routine_0             = 1;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8011201C(wp);
}

void func_8011201C(ST06_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    if (wp->ctl.flags_0 & 2)
    {
        func_80112488(wp);
    }
    D_80125374[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    *(uint16 *)0x1F800132 = wp->ctl.timer_A;
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 1)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
}
