#include "common.h"
#include "st06.h"

void func_8010FF90(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    STCOM_SVECTOR pos;
    sint32 hit;
    sint32 count;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC     = 7;
                wp->ctl.timer_8 = 0x44;
                break;
            case 1:
                wp->anim_AC     = 8;
                wp->ctl.timer_8 = 0xE;
                Sound_call2(0xED, &wp->position);
                break;
            case 3:
                wp->anim_AC     = 9;
                wp->ctl.timer_8 = 0x1E;
                break;
            case 4:
                wp->anim_AC     = 0xA;
                wp->ctl.timer_8 = 0x14;
                break;
        }
        return;
    }
    wp->ctl.timer_8--;
    switch (wp->routine_2)
    {
        case 0:
            if (ctl->timer_8 == 0)
            {
                wp->value_44.half[0] = 0;
                wp->routine_3        = 0;
                wp->routine_2++;
                break;
            }
            wp->value_44.half[0] = -0x90;
            Obj_pos_set(wp, -0x90, 0, 0);
            if (func_80049C24(wp) != 0)
            {
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
            }
            break;
        case 1:
            if (ctl->timer_8 == 0)
            {
                wp->routine_2++;
                ctl->timer_8 = 0xF;
            }
            break;
        case 2:
            if (ctl->timer_8 == 0)
            {
                wp->routine_3        = 0;
                wp->value_44.half[0] = 0;
                wp->routine_2 += 2;
                break;
            }
            wp->value_44.half[0] = 0x400;
            Obj_pos_set(wp, 0x400, 0, 0);
            hit = func_80049C24(wp);
            if (hit != 0)
            {
                count = func_80037BB4((void *)hit);
                if (STAGE_SCENE_BYTE(0) == 0)
                {
                    func_80037738(hit, 0xF);
                    if (count != 0)
                    {
                        pos = wp->joint_180[0];
                        pos.x -= rsin(wp->rotation.y) >> 5;
                        pos.z -= rcos(wp->rotation.y) >> 5;
                        func_80110734(&pos);
                    }
                }
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
                wp->value_44.half[0] = -0x80;
                wp->routine_3        = 0;
                wp->routine_2++;
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                Sound_call2(0xEE, &wp->position);
            }
            break;
        case 3:
            if (ctl->timer_8 == 0)
            {
                wp->routine_3 = 0;
                wp->routine_2++;
            }
            if (wp->value_44.half[0] < 0)
            {
                wp->value_44.half[0] += 0x10;
            }
            else
            {
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
                wp->value_44.half[0] = 0;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            break;
        case 4:
            if (ctl->timer_8 == 0)
            {
                *(uint16 *)&wp->routine_2 = 0;
                ctl->flags_4 |= 0x801;
            }
            break;
    }
}

void func_80110398(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    sint32 done;

    done        = 0;
    ctl         = &wp->ctl;
    wp->anim_AC = 0;
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
        wp->rotation.y += wp->ctl.u_3C.a.turn_1 * 16;
    }
    else
    {
        done = 1;
    }
    if (done & 0xFF)
    {
        ctl->flags_4 |= 0x801;
    }
}

void func_80110400(ST06_CRAB *wp)
{
    sint16 turn;

    if (wp->routine_2 == 0)
    {
        wp->routine_2             = 1;
        wp->anim_AC               = 1;
        wp->ctl.u_3C.a.target_2.x = 0x200;
        wp->ctl.u_3C.a.target_2.y = -0x301;
        wp->ctl.u_3C.a.target_2.z = 0x1400;
        return;
    }
    turn           = Muku(&wp->position, &wp->ctl.u_3C.a.target_2, wp->rotation.y, 0x10);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0)
    {
        wp->ctl.flags_4 |= 1;
    }
}

void func_80110498(ST06_CRAB *wp)
{
    STAGE_OBJ *owner;

    owner                  = wp->ctl.owner_0;
    wp->position.x         = owner->position.x;
    wp->position.y         = owner->position.y;
    wp->position.z         = owner->position.z;
    wp->position_fixed.v.x = owner->position_fixed.v.x;
    wp->position_fixed.v.y = owner->position_fixed.v.y;
    wp->position_fixed.v.z = owner->position_fixed.v.z;
    wp->rotation.y         = owner->rotation.y;
    wp->value_44.half[0]   = owner->value_44.half[0];
    wp->value_44.half[1]   = 0;
    wp->anim_AC            = 0;
    wp->ctl.flags_4 &= ~8;
}

void func_80110514(ST06_CRAB *wp)
{
    sint16 ground;

    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC          = 2;
            wp->ctl.timer_8      = 5;
            wp->value_44.half[1] = 0;
            wp->ctl.flags_4 |= 8;
            wp->routine_3++;
            break;
        case 1:
            wp->anim_AC = 2;
            if (wp->ctl.timer_8 != 0)
            {
                wp->ctl.timer_8--;
            }
            else
            {
                wp->value_44.half[1] += 0x30;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            ground = Obj_ceiling_height_get(wp);
            if (ground < wp->position.y)
            {
                wp->position_fixed.v.y = ground << 16;
                wp->position.y         = ground;
                wp->anim_AC            = 3;
                wp->value_44.half[1]   = 0;
                wp->value_44.half[0]   = 0;
                wp->routine_3++;
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                Sound_call2(0xEF, &wp->position);
            }
            break;
        case 2:
            wp->anim_AC = 3;
            if (wp->value_A7 == -1)
            {
                if (wp->u_C.b.byte_C & 0x10)
                {
                    wp->routine_0 = 3;
                    wp->routine_1 = 0;
                }
                else
                {
                    wp->routine_0   = 1;
                    wp->routine_1   = 0;
                    wp->ctl.timer_8 = 0xF;
                }
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void func_801106A4(ST06_CRAB *wp)
{
    wp->anim_AC = 0xC;
    wp->value_44.half[1] += 0x30;
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
    if (Obj_ceiling_height_get(wp) < wp->position.y)
    {
        wp->value_44.half[1]      = 0;
        wp->value_44.half[0]      = 0;
        wp->routine_0             = 2;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
    }
}

void func_80110734(STCOM_SVECTOR *pos)
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

void func_801107A0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl             = &wp->ctl;
    wp->ctl.timer_8 = 0;
    switch (wp->routine_1)
    {
        case 3:
            if (ctl->flags_4 & 0x400)
            {
                ctl->flags_4 &= ~0x400;
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            // fall through
        case 0:
        case 1:
        case 4:
        case 5:
        case 6:
            if (ctl->flags_4 & 0x200)
            {
                ctl->flags_4 &= ~0x200;
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (ctl->flags_4 & 0x1000)
            {
                ctl->flags_4       = (ctl->flags_4 & ~0x1000) | 0x100;
                ctl->u_3C.a.turn_1 = -1;
                wp->routine_1      = 5;
                wp->variant_3      = 0;
                ctl->timer_8       = ctl->random_6 % 112 + 16;
                break;
            }
            if (wp->variant_3 == 0)
            {
                if (ctl->flags_4 & 0x800)
                {
                    ctl->flags_4 &= ~0x900;
                    wp->routine_1      = 1;
                    ctl->timer_8       = 0x78;
                    ctl->u_3C.a.turn_1 = 0;
                    break;
                }
                wp->routine_2 = (uint8)ctl->random_6 & 7;
                if (wp->routine_2 < 6 && (ctl->flags_4 & 0x40))
                {
                    ctl->flags_4 &= ~0x100;
                    wp->routine_1 = 1;
                    ctl->timer_8  = 0x78;
                    if (wp->routine_2 & 2)
                    {
                        ctl->u_3C.a.turn_1 = 1;
                    }
                    else if (wp->routine_2 & 4)
                    {
                        ctl->u_3C.a.turn_1 = -1;
                    }
                    else
                    {
                        ctl->u_3C.a.turn_1 = 0;
                    }
                }
                else
                {
                    ctl->flags_4 |= 0x100;
                    wp->routine_1 = 2;
                    ctl->timer_8  = ctl->random_6 % 63 + 16;
                    if (wp->routine_2 & 1)
                    {
                        ctl->u_3C.a.turn_1 = 1;
                    }
                    else
                    {
                        ctl->u_3C.a.turn_1 = -1;
                    }
                }
            }
            else if (wp->routine_1 == 0)
            {
                wp->routine_1             = 6;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->u_3C.a.turn_1        = 1;
                ctl->flags_4 |= 0x100;
            }
            else
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->timer_8              = 0x4000;
                ctl->u_3C.a.turn_1        = 0;
                ctl->flags_4 &= ~0x100;
            }
            break;
        case 2:
            wp->routine_2 = (uint8)ctl->random_6 % 6;
            ctl->flags_4 &= ~0x100;
            wp->routine_1 = 1;
            ctl->timer_8  = 0x78;
            if (wp->routine_2 & 2)
            {
                ctl->u_3C.a.turn_1 = 1;
            }
            else if (wp->routine_2 & 4)
            {
                ctl->u_3C.a.turn_1 = -1;
            }
            else
            {
                ctl->u_3C.a.turn_1 = 0;
            }
            break;
    }
}

sint32 func_80110A54(ST06_CRAB *wp)
{
    wp->ctl.kind_C     = D_80098844[wp->kind_2]->value_A;
    wp->ctl.hit_pos_10 = wp->joint_180[0];
    func_800341BC(&wp->ctl.hit_pos_10, 0x80, 0, 0x8000, wp->value_1, &wp->ctl.hit_18, wp->ctl.kind_C | 0x4880000, 0x800000, 0);
    return 1;
}

sint32 func_80110AF0(ST06_CRAB *wp)
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
        wp->routine_0             = 2;
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
    }
    return 1;
}

void func_80110BA4(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_6        = rand();
    wp->ctl.u_38.dist       = SquareRoot0(wp->dist_80);
    D_8012524C[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else if (wp->ctl.flags_4 & 0x10)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_prev_AD, wp->value_A4);
    }
    if (ctl->flags_4 & 8)
    {
        func_80111D54(wp);
    }
    Pos_Shadow_Trans(&wp->position, 0x100, 0x200, 0);
}

void func_80110CFC(ST06_CRAB *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_4             = 0x5E;
    *(sint32 *)&wp->ctl.timer_8 = 0;
    *(sint32 *)&wp->ctl.kind_C  = 0;
    wp->ctl.hit_18              = 0;
    wp->ctl.value_1C            = 0;
    wp->ctl.value_2C            = 0;
    wp->ctl.u_3C.b.value_8      = 0;
    wp->ctl.u_3C.b.value_7      = 0;
    wp->ctl.u_3C.b.rec_0        = D_80125278[wp->variant_3];
    wp->ctl.u_3C.b.flag_6       = wp->ctl.random_6 & 1;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 * 16;
    wp->data_78                                      = D_8012526C;
    if (wp->u_C.b.byte_C & 0x10)
    {
        wp->routine_0 = 3;
    }
    else
    {
        wp->routine_0 = 1;
    }
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    func_800322A8(wp, 4, 0);
    wp->scale.v.pad = 0x4210;
}

void func_80110E20(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.flags_4 & 2)
    {
        func_80111DF0(wp);
    }
    D_8012525C[wp->routine_1](wp);
    if (!(wp->ctl.flags_4 & 0x200) && wp->routine_1 != 3)
    {
        if ((wp->ctl.flags_4 & 0x80) && wp->ctl.u_38.dist < 0x800)
        {
            func_80111A30(wp);
        }
        else
        {
            func_80111AFC(wp);
        }
    }
    if (ctl->flags_4 & 1)
    {
        func_80111CF8(wp);
        wp->routine_3 = 0;
        ctl->flags_4 &= ~1;
    }
    ctl->hit_18 = 0;
}

void func_80110F18(ST06_CRAB *wp)
{
    STCOM_SVECTOR pos;
    STAGE_OBJ *part;

    switch (wp->routine_1)
    {
        case 0:
            wp->ctl.timer_8 = 3;
            func_80111BE0(&wp->joint_180[0]);
            wp->routine_1++;
            break;
        case 1:
            wp->ctl.timer_8--;
            func_80111BE0(&wp->joint_180[3 - wp->ctl.timer_8]);
            func_80111BE0(&wp->joint_180[6 - wp->ctl.timer_8]);
            if (wp->ctl.timer_8 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            part = func_80031418();
            if (part != NULL)
            {
                part->flags_0               = 1;
                part->kind_2                = 0;
                part->variant_3             = 1;
                part->value_4               = 1;
                *(uint32 *)&part->routine_0 = 0;
                *(uint32 *)&part->u_C       = 0;
                part->position.x            = wp->joint_180[0].x;
                part->position.y            = wp->joint_180[0].y - 0xC0;
                part->position.z            = wp->joint_180[0].z;
                part->position_fixed.v.x    = wp->joint_180[0].x << 16;
                part->position_fixed.v.y    = wp->joint_180[0].y << 16;
                part->position_fixed.v.z    = wp->joint_180[0].z << 16;
                part->rotation              = wp->rotation;
            }
            pos.x = wp->joint_180[0].x;
            pos.y = wp->joint_180[0].y - 0x80;
            pos.z = wp->joint_180[0].z;
            func_80047148(wp, &pos);
            wp->u_C.b.byte_C |= 1;
            break;
    }
}

void func_801110D8(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->u_C.b.byte_D)
    {
        case 0:
            if (wp->routine_2 == 0)
            {
                wp->routine_2++;
                wp->anim_AC = 0xA;
            }
            else
            {
                wp->value_44.half[0] = 0x100;
                Obj_pos_set(wp, 0x100, 0, 0);
                wp->rotation.y++;
            }
            if (ctl->value_A == 600)
            {
                wp->flags_0 &= ~2;
            }
            break;
        case 1:
            wp->anim_AC          = 0;
            wp->value_44.half[0] = 0xC0;
            Obj_pos_set(wp, 0xC0, 0, 0);
            if (wp->ctl.value_A == 0 || wp->ctl.value_A == 1400)
            {
                wp->flags_0 &= ~2;
            }
            if (ctl->value_A == 1000)
            {
                wp->flags_0 |= 2;
            }
            break;
        case 2:
            wp->anim_AC          = 0xA;
            wp->value_44.half[0] = 0xC0;
            Obj_pos_set(wp, 0xC0, 0, 0);
            if (wp->ctl.value_A == 1100)
            {
                wp->flags_0 &= ~2;
            }
            break;
    }
    ctl->value_A++;
}

void func_80111250(ST06_CRAB *wp)
{
    wp->ctl.flags_4 |= 1;
}

void func_80111264(ST06_CRAB *wp)
{
    STCOM_FIXED_VECTOR out;
    STCOM_SVECTOR size;
    ST06_CRAB_CTL *ctl;
    sint32 side;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_3)
    {
        case 0:
            if (wp->anim_AC != 5)
            {
                wp->anim_AC = 5;
                Sound_call2(0xE9, &wp->position);
            }
            else if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 0xA;
                wp->routine_3 = 1;
            }
            break;
        case 1:
            wp->value_C4 = wp->joint_180[0];
            pl->value_C4 = pl->position;
            size.x       = 2;
            size.y       = 9;
            size.z       = 4;
            side         = func_80030418(wp, pl, &size, &out);
            if (side & 1)
            {
                wp->rotation.y = (sint16)(wp->rotation.y - 0x10) - ((wp->u_C.ub.byte_D << 24) >> 22);
            }
            else if (!(side & 2))
            {
                wp->rotation.y = (sint16)(wp->rotation.y + 0x10) + ((wp->u_C.ub.byte_D << 24) >> 22);
            }
            wp->value_44.half[0] = 0x200;
            wp->rotation.y &= 0xFFF;
            Obj_pos_set(wp, 0x200, 0, 0);
            if (ctl->timer_8 != 0)
            {
                ctl->timer_8--;
            }
            else
            {
                ctl->timer_8 = (ctl->random_6 & 0xF) + 0x18;
                if (ctl->u_38.dist < 0x400 && wp->routine_2 == 0 && *(uint8 *)&Scene_work == 0)
                {
                    func_80111C4C(wp);
                }
            }
            if (ctl->flags_4 & 0x100)
            {
                ctl->flags_4 |= 1;
            }
            break;
    }
}
