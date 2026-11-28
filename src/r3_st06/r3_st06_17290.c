#include "common.h"
#include "st06.h"

void func_80117290(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    STAGE_OBJ *obj;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->body.random_2       = rand();
    func_8005D4C0();
    body = &wp->body;
    if (wp->body.flags_0 & 4)
    {
        func_80118B2C(wp);
    }
    if (!(wp->body.flags_0 & 0x400) && func_80118884(wp) != 0 && func_8003B360(wp->body.area_8C) > 0)
    {
        wp->body.timer_E = 0xB4;
        wp->body.flags_0 |= 0x400;
    }
    D_80125890[wp->routine_1](wp);
    if (body->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 4:
                func_8003187C(wp);
                func_8005D6E8(wp);
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->flags_0            = 1;
                    obj->kind_2             = 0x2F;
                    obj->variant_3          = 0;
                    obj->u_C.b.byte_C       = -1;
                    obj->position_fixed.v.x = wp->position_fixed.v.x;
                    obj->position_fixed.v.y = wp->position_fixed.v.y - 0x800000;
                    obj->position_fixed.v.z = wp->position_fixed.v.z;
                    func_80030150(&obj->position_fixed.v, &wp->position);
                    body->probe_38.v.x = -0xB39;
                    body->probe_38.v.y = -1;
                    body->probe_38.v.z = -0x198A;
                    obj->rotation.y    = Angle_xz_svector(&wp->position, &body->probe_38.v);
                }
                break;
            case 6:
                wp->routine_1 = wp->u_C.b.byte_D;
                break;
            case 0:
                wp->routine_1 = 0;
                break;
            case 1:
                wp->routine_1 = wp->u_C.b.byte_D;
                break;
            case 2:
            case 3:
            case 5:
            default:
                wp->routine_1 = 6;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        body->flags_0 &= ~1;
    }
    if (body->timer_C != 0)
    {
        body->timer_C--;
    }
    if (body->u_8.h.timer_A != 0)
    {
        body->u_8.h.timer_A--;
    }
    if (body->timer_E != 0)
    {
        body->timer_E--;
    }
    if (body->timer_82 != 0)
    {
        body->timer_82--;
    }
    if (body->flags_0 & 0x20)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
    }
    else
    {
        Model_pose_unpack(wp);
        Model_parts_mtx_set_y(wp);
    }
    wp->value_44.half[0] = (wp->position.x - wp->position_prev.x) << 4;
    wp->value_44.half[1] = (wp->position.y - wp->position_prev.y) << 4;
    wp->value_48.half[0] = (wp->position.z - wp->position_prev.z) << 4;
    if (wp->flags_0 & 2)
    {
        Pos_Shadow_Trans(&wp->position, 0x80, 0x200, wp->rotation.y);
    }
    if (wp->flags_0 & 1)
    {
        if (body->flags_0 & 2)
        {
            body->hit_pos_10 = wp->position;
            func_800341BC(&body->hit_pos_10, 0xA0, 0, 0x8000, wp->value_1, &body->hit_18, 0x4080000, 0, 0);
        }
        if (body->flags_0 & 0x40)
        {
            body->hit_pos_68 = wp->joint_180[10];
            func_800341BC(&body->hit_pos_68, 0x60, 0, 0x8000, wp->value_1, &body->hit_70, D_8009884C[wp->kind_2]->value_A | 0x5000000, 0,
                          0x80);
        }
        if (body->flags_0 & 0x80)
        {
            body->hit_pos_58 = wp->joint_180[5];
            func_800341BC(&body->hit_pos_58, 0x60, 0, 0x8000, wp->value_1, &body->hit_60, D_8009884C[wp->kind_2]->value_A | 0x5000000, 0,
                          0x80);
        }
    }
    body->ground_78 = Obj_map_push_out(wp);
}

void func_80117784(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_801177A4(ST06_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
        wp->value_440 |= 0x20;
    }
}

void func_801177D0(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    STCOM_PL_WORK *pl;

    body = &wp->body;
    pl   = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 7;
            wp->routine_2++;
            body->u_4.h.timer_4 = 0x1E;
            body->flags_0 |= 0x20;
            Sound_call2(0xFD, &wp->position);
            body->value_88 = 0;
            // fall through
        case 1:
            if (--body->u_4.h.timer_4 < 0)
            {
                wp->routine_2++;
                body->u_4.h.timer_4 = 0x10;
                body->flags_0 &= ~0x20;
            }
            break;
        case 2:
            wp->rotation.y       = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x40)) & 0xFFF;
            body->probe_38.v     = pl->position;
            body->probe_fixed_40 = pl->position_fixed;
            func_8002FFC4(&body->probe_38.v, &body->probe_fixed_40, Angle_xz_svector(&pl->position, &wp->position) & 0xFFF, 0x1100, 0, 0);
            wp->value_4C.half[0] = Distance_xz(&wp->position.x, &body->probe_38.v.x) / (body->u_4.h.timer_4 + 1);
            wp->value_4C.half[0] = (wp->value_4C.half[0] > 0x40) ? 0x40 : wp->value_4C.half[0];
            wp->value_4C.half[1] = pl->position.y - (sint16)(wp->position.y + 0x40);
            Obj_pos_set(wp, wp->value_4C.half[0] << 4, (D_800BBCF8[body->u_4.h.timer_4] * wp->value_4C.half[1]) >> 12, 0);
            if (func_80118708(wp))
            {
                wp->routine_2 = 5;
                body->flags_0 |= 0x20;
            }
            else if (--body->u_4.h.timer_4 < 0)
            {
                wp->routine_2++;
                body->flags_0 |= 0x20;
                body->u_4.h.timer_4 = 0x10;
                body->flags_0 |= 0xC0;
            }
            break;
        case 3:
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xFE, &wp->position);
            }
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2++;
                body->u_4.h.timer_4 = 0x10;
                body->flags_0 &= ~0xC0;
            }
            break;
        case 4:
            if (body->flags_0 & 0x400)
            {
                body->target_50 = D_801258B8;
            }
            else
            {
                body->target_50 = pl->position;
            }
            wp->rotation.y       = (wp->rotation.y + Muku(&wp->position, &body->target_50, wp->rotation.y, 0x20)) & 0xFFF;
            wp->value_4C.half[1] = (sint16)(wp->position.y + 0x400) - Obj_ceiling_height_get(wp);
            Obj_pos_set(wp, 0, (D_800BBD38[body->u_4.h.timer_4] * wp->value_4C.half[1]) >> 12, 0);
            if (--body->u_4.h.timer_4 < 0)
            {
                wp->u_C.b.byte_D = 6;
                body->timer_C    = 0x1E;
                body->flags_0 |= 1;
            }
            break;
        case 5:
            if (wp->value_A7 < 0)
            {
                wp->u_C.b.byte_D = 5;
                body->timer_C    = 0x1E;
                body->flags_0 |= 1;
            }
            break;
    }
}

void func_80117BF0(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;
    sint16 turn;

    body = &wp->body;
    pl   = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 4;
            body->flags_0 |= 0x20;
            body->value_88++;
            Sound_call2(0x141, &wp->position);
            break;
        case 1:
            if (wp->value_A6 != 0)
            {
                Sound_call2(0x154, &wp->position);
            }
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, 0x40);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if ((turn < 0 ? -turn : turn) < 0x40 && wp->value_A7 < 0)
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    body->child_84    = obj;
                    obj->flags_0      = 1;
                    obj->kind_2       = 0x2E;
                    obj->value_4      = 0;
                    obj->position     = wp->joint_180[1];
                    obj->rotation     = wp->rotation;
                    obj->u_C.b.byte_C = 0;
                }
                wp->anim_AC = 5;
                wp->routine_2++;
            }
            break;
        case 2:
            if (body->child_84->u_C.b.byte_C != 0)
            {
                wp->anim_AC = 6;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                body->timer_C = 0x3C;
                body->flags_0 |= 1;
            }
            break;
    }
}

void func_80117DF4(ST06_CRAB *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC       = 1;
            wp->body.value_88 = 0;
            wp->body.flags_0 |= 0x20;
            break;
        case 1:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, 0x40);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if ((turn < 0 ? -turn : turn) < 0x40 && wp->value_A7 < 0)
            {
                wp->anim_AC = 2;
                wp->routine_2++;
            }
            break;
        case 2:
            if (wp->value_A7 < 0)
            {
                func_801189B4(wp);
                wp->anim_AC = 3;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                wp->body.timer_C = 0x5A;
                wp->body.flags_0 |= 1;
            }
            break;
    }
}

void func_80117F4C(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    STCOM_EFFECT *fx;

    body = &wp->body;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC          = 0xB;
            wp->value_4C.half[1] = 0x10;
            body->u_4.h.timer_4  = 0x10;
            wp->data_78          = NULL;
            body->flags_0 |= 0x20;
            break;
        case 1:
            wp->value_44.half[0] = wp->value_44.half[0] >> 1;
            wp->value_44.half[1] += wp->value_4C.half[1];
            wp->value_48.half[0] = wp->value_48.half[0] >> 1;
            wp->value_4C.half[1] += 0x10;
            if (--body->u_4.h.timer_4 < 0)
            {
                wp->routine_2++;
            }
            // fall through
        case 2:
            if (wp->anim_AC != 0xC && wp->value_A7 < 0)
            {
                wp->anim_AC = 0xC;
            }
            if (body->ground_78 & 0x1000)
            {
                body->flags_0 |= 1;
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 0x42;
                    fx->value_C         = 1;
                    fx->value_D         = 2;
                    fx->sprite.position = wp->position;
                }
            }
            else
            {
                Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], wp->value_48.half[0]);
            }
            break;
    }
}

void func_801180F8(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    STCOM_PL_WORK *pl;

    body = &wp->body;
    pl   = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 8;
            wp->routine_2++;
            body->flags_0 |= 0x20;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 9;
                wp->routine_2++;
                break;
            }
            if (wp->value_A6 != 0)
            {
                if ((body->flags_0 & 0x800) || func_80118708(wp) == 0)
                {
                    wp->anim_AC = 0xA;
                    wp->routine_2 += 2;
                }
                else
                {
                    Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                    func_80037738(body->hit_7C, D_8009884C[wp->kind_2]->value_B);
                    func_801187D4(wp);
                }
            }
            break;
        case 2:
            if (wp->value_A6 != 0)
            {
                if ((body->flags_0 & 0x800) || func_80118708(wp) == 0)
                {
                    wp->anim_AC = 0xA;
                    wp->routine_2++;
                    body->u_4.h.timer_4 = 0x10;
                    body->flags_0 |= 0xC0;
                }
                else
                {
                    Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                    func_80037738(body->hit_7C, D_8009884C[wp->kind_2]->value_B);
                    func_801187D4(wp);
                }
            }
            break;
        case 3:
            wp->rotation.y       = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x20)) & 0xFFF;
            wp->value_4C.half[1] = (sint16)(wp->position.y + 0x400) - Obj_ceiling_height_get(wp);
            Obj_pos_set(wp, 0, (D_800BBD38[body->u_4.h.timer_4] * wp->value_4C.half[1]) >> 12, 0);
            if (--body->u_4.h.timer_4 < 0)
            {
                wp->routine_2++;
            }
            break;
        case 4:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, 0x20)) & 0xFFF;
            if (wp->value_A7 < 0)
            {
                body->flags_0 |= 1;
                body->flags_0 &= ~0x8C0;
                if (body->timer_E == 0)
                {
                    body->flags_0 &= ~0x400;
                }
            }
            break;
    }
}

void func_8011837C(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    sint16 turn;

    body = &wp->body;
    if (wp->body.flags_0 & 0x400)
    {
        wp->body.target_50 = D_801258B8;
    }
    else
    {
        wp->body.target_50 = Player_work.position;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC          = 0;
            wp->value_4C.half[0] = 0;
            body->flags_0 |= 0x20;
            // fall through
        case 1:
            turn           = Muku(&wp->position, &body->target_50, wp->rotation.y, 0x60);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn < 0x60)
            {
                if ((body->random_2 & 1) && body->timer_C == 0)
                {
                    wp->u_C.b.byte_D = 3;
                    body->flags_0 |= 1;
                }
                else
                {
                    wp->routine_2++;
                    body->u_4.h.timer_4 = 0;
                }
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &body->target_50, wp->rotation.y, 0x20)) & 0xFFF;
            if (body->timer_C == 0 && !(body->flags_0 & 0x400) && wp->dist_80 <= 0x7FFFF)
            {
                wp->u_C.b.byte_D = 1;
                body->flags_0 |= 1;
            }
            else if (body->timer_C == 0 && (body->flags_0 & 0x100) && !(body->flags_0 & 0x400))
            {
                if (wp->dist_80 <= 0x7FFFF)
                {
                    wp->u_C.b.byte_D = 1;
                }
                else if (body->value_88 == 2)
                {
                    wp->u_C.b.byte_D = 3;
                }
                else if (wp->dist_80 <= 0x1FFFFF)
                {
                    wp->u_C.b.byte_D = 2;
                }
                else
                {
                    wp->u_C.b.byte_D = 3;
                }
                body->flags_0 |= 1;
            }
            else if (func_80118708(wp))
            {
                wp->u_C.b.byte_D = 5;
                body->flags_0 |= 1;
            }
            else
            {
                if (body->ground_78 & 0xF00)
                {
                    body->flags_0 &= ~0x400;
                    body->timer_80++;
                }
                else
                {
                    body->timer_80 = 0;
                }
                wp->value_4C.half[1] = (sint16)(Obj_ceiling_height_get(wp) - 0x200) - body->timer_80 * 8 - wp->position.y;
                if ((wp->value_4C.half[1] < 0 ? -wp->value_4C.half[1] : wp->value_4C.half[1]) > 0x40)
                {
                    if (wp->value_4C.half[1] < 0)
                    {
                        if (wp->value_4C.half[1] < -8)
                        {
                            wp->value_4C.half[1] = -0x80;
                        }
                        else
                        {
                            wp->value_4C.half[1] <<= 4;
                        }
                    }
                    else
                    {
                        wp->value_4C.half[1] = (wp->value_4C.half[1] > 8) ? 0x80 : wp->value_4C.half[1] << 4;
                    }
                }
                Obj_pos_set(wp, wp->value_4C.half[0] + 0x100, ((D_800BBCF8[body->u_4.h.timer_4] * 5) >> 7) + wp->value_4C.half[1], 0);
                body->u_4.h.timer_4 = (body->u_4.h.timer_4 + 1) & 0x3F;
                if (wp->value_4C.half[0] < 0x80)
                {
                    wp->value_4C.half[0] += 0x10;
                }
            }
            break;
    }
}

sint32 func_80118708(ST06_CRAB *wp)
{
    if (wp->body.timer_82 != 0)
    {
        return 0;
    }
    wp->body.probe_38.v     = wp->position;
    wp->body.probe_fixed_40 = wp->position_fixed.v;
    func_8002FFC4(&wp->body.probe_38.v, &wp->body.probe_fixed_40, wp->rotation.y, 0x800, 0, 0);
    wp->body.hit_7C = func_80049C54(&wp->body.probe_38.v, &wp->position, wp->data_78, wp->value_1);
    if (wp->body.hit_7C != 0 && func_80037BB4((void *)wp->body.hit_7C) > 0)
    {
        return 1;
    }
    return 0;
}

sint32 func_801187D4(ST06_CRAB *wp)
{
    STCOM_EFFECT *fx;

    fx = func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 5;
        fx->kind_2    = 0x80;
        fx->variant_3 = 0x42;
        fx->value_C   = 1;
        fx->value_D   = 1;
        if (wp->value_A6 == 1)
        {
            fx->sprite.position = wp->joint_180[5];
            return 0;
        }
        fx->sprite.position = wp->joint_180[10];
    }
    return 0;
}

sint32 func_80118884(ST06_CRAB *wp)
{
    sint32 dx;
    sint32 dz;

    dx = (wp->position.x >> 9) - D_801258C0;
    dz = (wp->position.z >> 9) - D_801258C2;
    if ((uint32)dx < D_801258C4 && (uint32)dz < D_801258C6)
    {
        return 0;
    }
    return 1;
}

sint32 func_801188E4(ST06_CRAB *wp)
{
    STAGE_OBJ *obj;

    obj = func_80031498();
    if (obj != NULL)
    {
        obj->flags_0            = 1;
        obj->kind_2             = 0xD;
        obj->value_4            = 1;
        obj->variant_3          = 0;
        obj->u_C.b.byte_C       = wp->value_A4;
        obj->u_E.b.byte_F       = 1;
        obj->position_fixed.v.x = wp->position.x << 16;
        obj->position_fixed.v.y = wp->position.y << 16;
        obj->position_fixed.v.z = wp->position.z << 16;
        obj->rotation.y         = wp->rotation.y;
        func_80030150(&obj->position_fixed.v, &obj->position);
        obj->life_max_B0 = 0;
        obj->life_6E     = 0;
        func_8005D620(obj, 0, 0, 0x50, 0x305880);
        return 0;
    }
    return 1;
}

sint32 func_801189B4(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    ST06_HOMER *shot;
    sint32 i;

    body = &wp->body;
    for (i = 0; i < 6; i++)
    {
        shot = (ST06_HOMER *)Open_SHL_WORK();
        if (shot != NULL)
        {
            shot->flags_0           = 1;
            shot->variant_3         = 3;
            shot->kind_2            = 0;
            shot->target_B8         = &STAGE_PL_BYTE(0x3A8);
            shot->position.x        = wp->joint_180[D_801258D4[i]].x;
            shot->position.y        = wp->joint_180[D_801258D4[i]].y;
            shot->position.z        = wp->joint_180[D_801258D4[i]].z;
            body->probe_38.words[0] = 0;
            body->probe_38.words[1] = 0;
            body->probe_38.v.x      = (wp->rotation.x + D_801258C8[i]) & 0xFFF;
            if (i < 3)
            {
                body->probe_38.v.y = (wp->rotation.y + 0x400) & 0xFFF;
            }
            else
            {
                body->probe_38.v.y = (wp->rotation.y - 0x400) & 0xFFF;
            }
            RotMatrixYXZ(&body->probe_38.v, &shot->matrix_8C.m);
            body->probe_fixed_40.x   = 0x200;
            body->probe_fixed_40.y   = 0x200;
            body->probe_fixed_40.z   = 0x200;
            body->probe_fixed_40.pad = 0;
            ScaleMatrix(&shot->matrix_8C.m, &body->probe_fixed_40);
        }
    }
    return 0;
}

sint32 func_80118B2C(ST06_CRAB *wp)
{
    ST06_CRAB_BODY *body;
    uint32 hit;
    sint32 damage;

    body   = &wp->body;
    hit    = wp->body.hit_18;
    damage = hit & 0xFFFFFF;
    wp->body.flags_0 &= ~0x900;
    if (damage != 0)
    {
        if (hit & 0x38000000)
        {
            wp->body.timer_C = 0;
            if (wp->body.timer_E == 0)
            {
                wp->body.flags_0 &= ~0x400;
            }
            wp->body.flags_0 |= 0x900;
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                if (wp->routine_1 != 2 && func_80042208() != 0)
                {
                    wp->body.flags_0 &= ~0xC;
                    wp->life_prev_B2          = 0;
                    wp->life_6E               = 0;
                    damage                    = D_8009884C[wp->kind_2]->limit_9;
                    wp->routine_1             = 4;
                    *(uint16 *)&wp->routine_2 = 0;
                }
                else
                {
                    wp->life_6E = 1;
                }
            }
            if (body->flags_0 & 8)
            {
                body->u_8.h.timer_A += damage;
                if ((body->hit_18 & 0x20000000) || body->u_8.h.timer_A >= D_8009884C[wp->kind_2]->limit_9)
                {
                    Sound_call2(0xA2, &wp->position);
                    body->u_8.h.timer_A = 0;
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

void func_80118CE4(STAGE_OBJ *wp)
{
    D_801258DC[wp->routine_0](wp);
}

void func_80118D20(ST06_MATRIX_OBJ *wp)
{
    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->color_40 = 0x02808080;
    wp->index_C  = 0;
    wp->value_D  = 0;
    wp->routine_0++;
}

void func_80118D9C(ST06_MATRIX_OBJ *wp)
{
    uint8 *uv;
    sint32 i;
    sint32 wrap;

    wrap = 0;
    wp->index_C++;
    wp->value_D += 4;
    for (i = 0; i < 0x20; i++)
    {
        uv = Model_face_get(wp->model_14, i + 0x10000);
        if (wrap != 0 || (i == 0 && uv[0] >= 0xA0))
        {
            wrap = 1;
            uv[0] -= 0x1C;
            uv[2] -= 0x1C;
            uv[4] -= 0x1C;
            uv[6] -= 0x1C;
        }
        else
        {
            uv[0] += 4;
            uv[2] += 4;
            uv[4] += 4;
            uv[6] += 4;
        }
    }
}

void func_80118E90(STAGE_50 *wp)
{
    func_80031A4C(wp);
}
