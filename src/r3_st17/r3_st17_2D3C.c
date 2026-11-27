#include "common.h"
#include "st17.h"

void func_80102D3C(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            wp->variant_3 = 1;
            wp->flags_0 |= 2;
            Model_work_init(wp, &wp->variant_3);
            wp->scale.words[0] = 0x2000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            wp->anim_AC        = 0;
            wp->u_C.b.byte_C   = 0;
            wp->u_C.b.byte_D   = 1;
            wp->u_E.b.byte_E   = 0x38;
            wp->u_E.b.byte_F   = 0;
            wp->routine_0++;
            // fall through
        case 1:
            wp->rotation.z = D_8011AF58[wp->u_E.b.byte_E] - 0x222;
            wp->u_E.b.byte_E++;
            if (wp->u_E.b.byte_F < 2)
            {
                if (wp->u_E.b.byte_E == 0x44)
                {
                    wp->u_E.b.byte_E = 0;
                    wp->u_E.b.byte_F++;
                }
            }
            else if (wp->u_E.b.byte_E == 0x67)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->anim_AC      = 8;
            wp->u_C.b.byte_C = 0;
            wp->u_C.b.byte_D = 0;
            wp->routine_0++;
            break;
        case 3:
            if (wp->value_A4 == 8)
            {
                wp->variant_3 = 0;
                Model_work_init(wp, &wp->variant_3);
                wp->scale.words[0] = 0x2000200;
                wp->scale.words[1] = 0x200;
                wp->scale.v.pad    = 0x4210;
                wp->value_78       = 0;
                wp->anim_AC        = 8;
                wp->anim_prev_AD   = 0xFF;
                wp->u_C.b.byte_C   = 8;
                wp->routine_0++;
            }
            break;
        case 4:
            break;
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        if (wp->u_C.b.byte_D == 0)
        {
            func_800322A8(wp, wp->anim_AC, wp->u_C.b.byte_C);
            return;
        }
        func_80032304(wp, wp->anim_AC, wp->u_C.b.byte_C);
    }
    else
    {
        if (wp->u_C.b.byte_D == 0)
        {
            func_80032488(wp);
            return;
        }
        func_80032538(wp);
    }
    Model_parts_mtx_set_yxz(wp);
}

void func_80102FD8(STAGE_OBJ *wp)
{
    D_8011B028[wp->routine_1](wp);
}

void func_80103014(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->flags_0        = (uint8)wp->flags_0 | 2;
    Model_work_init(wp, NULL);
    func_800322A8(wp, 1, 0);
    wp->routine_1++;
}

void func_80103084(STAGE_OBJ *wp)
{
    switch (Scene_work.value_10)
    {
        case 0x14:
        case 0x50:
            func_800322A8(wp, 2, 0);
            break;
        case 0x64:
            func_800322A8(wp, 3, 0);
            break;
    }
    func_80032488(wp);
}

void func_80103108(STAGE_OBJ *wp)
{
    ST17_PART28 *part;
    sint16 index;
    sint32 flag;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    part                    = (ST17_PART28 *)&wp->owner_308;
    part->random_6          = rand();
    D_8011B030[wp->routine_0](wp, part);
    if (wp->anim_AC == 0)
    {
        if (wp->value_44.half[0] == 0)
        {
            if (part->value_C == -1)
            {
                if (wp->rotation.z != 0)
                {
                    if (wp->rotation.z > 0)
                    {
                        wp->rotation.z -= 8;
                    }
                    else
                    {
                        wp->rotation.z += 8;
                    }
                }
                if (wp->rotation.z == 0)
                {
                    if (!(wp->u_C.b.byte_D & 1))
                    {
                        part->value_C = (part->random_6 >> 4) & 3;
                    }
                    else
                    {
                        part->value_C = ((part->random_6 >> 6) & 3) + 0x12;
                    }
                }
            }
            else
            {
                index          = part->value_C % 36;
                wp->rotation.z = D_8011B060[index];
                part->value_C  = (part->value_C + 1) & 0x7FFF;
            }
        }
        else
        {
            if (wp->value_44.half[0] < 0)
            {
                if (wp->rotation.z >= -0x5F)
                {
                    wp->rotation.z -= 8;
                }
            }
            else if (wp->rotation.z < 0x60)
            {
                wp->rotation.z += 8;
            }
            part->value_C = -1;
        }
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        Model_parts_mtx_set_yxz(wp);
    }
    else if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    flag = (part->flags_4 << 3) & 0x80;
    func_800341BC(ST17_JOINT(wp), 0xDC, 0, 0x8000, wp->value_1, &part->hit_28, part->value_8 | 0x5880000, 0x800000, flag);
    part->hit_28.value_0 = 0;
}

void func_801033E4(STAGE_OBJ *wp, ST17_PART28 *part)
{
    sint16 life;

    part->flags_4  = 0;
    part->timer_E  = 0;
    part->value_10 = 0;
    part->timer_A  = 0;
    part->value_C  = -1;
    part->value_8  = D_80098844[wp->kind_2]->value_A;
    part->vx_12 = part->vy_14 = part->vz_16 = part->value_18 = 0;
    part->value_1A                                           = 0;
    part->value_1C                                           = 0;
    part->value_1E                                           = 0;
    part->value_20 = part->value_22 = part->value_24 = 0;
    part->hit_28.value_0                             = 0;
    part->hit_28.value_4                             = 0;
    Track_reset(part->track_30, 0, 0);
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]      = 0x02000200;
    wp->scale.words[1]      = 0x42100200;
    wp->anim_prev_AD        = 0xFF;
    ST17_OBJ_WORD(wp, 0x64) = 0;
    wp->anim_AC             = 0;
    wp->value_48.half[0]    = 0;
    wp->value_44.half[1]    = 0;
    wp->value_44.half[0]    = 0;
    life                    = D_80098844[wp->kind_2]->life_C * 16;
    wp->value_78            = (sint32)D_8011B054;
    wp->routine_0           = 1;
    wp->routine_1           = 0;
    wp->routine_2           = 0;
    wp->routine_3           = 0;
    wp->life_6E             = life;
    wp->life_max_B0         = life;
    wp->life_prev_B2        = life;
}

void func_80103520(STAGE_OBJ *wp, ST17_PART28 *part)
{
    uint16 flags;

    if (part->flags_4 & 2)
    {
        func_8010483C(wp, part);
    }
    switch (wp->anim_AC)
    {
        case 0:
            if (part->flags_4 & 0x20)
            {
                wp->anim_AC = 2;
            }
            else if (part->flags_4 & 4)
            {
                wp->anim_AC = 1;
            }
            break;
        case 1:
            flags = part->flags_4;
            if (flags & 0x10)
            {
                part->flags_4 = flags & ~4;
                wp->anim_AC   = 0;
            }
            else if (flags & 0x20)
            {
                wp->anim_AC = 2;
            }
            else if (wp->value_A7 == -1)
            {
                if (flags & 4)
                {
                    wp->anim_AC      = 1;
                    wp->anim_prev_AD = 0xFF;
                }
                else
                {
                    wp->anim_AC = 0;
                }
            }
            break;
        case 2:
            if (wp->value_A7 == -1)
            {
                wp->anim_AC = 3;
            }
            break;
    }
    D_8011B03C[wp->routine_1](wp, part);
    if (part->flags_4 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1 = 1;
                break;
            case 1:
                wp->routine_0 = 2;
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        part->flags_4 &= ~1;
    }
}

// The second argument is the work slot's +0x308, which starts with the owner's pointer.
void func_801036B4(STAGE_OBJ *wp, STAGE_OBJ **owner)
{
    (*owner)->u_C.b.byte_C |= 1 << wp->u_C.b.byte_C;
    func_80031824(wp);
}

void func_801036EC(STAGE_OBJ *wp, ST17_PART28 *part)
{
    func_8003648C(part->track_30, wp);
    D_8011B044[wp->routine_2](wp, part);
    if (wp->anim_AC == 1)
    {
        part->flags_4 &= ~8;
    }
    if (part->flags_4 & 8)
    {
        if (!(part->timer_A & 3))
        {
            func_80104900(wp, part);
        }
        part->timer_A++;
    }
    else
    {
        part->timer_A = 0;
    }
}

void func_801037B4(STAGE_OBJ *wp, ST17_PART28 *part)
{
    ST17_MARK *ep;

    switch (wp->routine_2)
    {
        case 0:
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 5;
                ep->kind_2    = 0x80;
                ep->variant_3 = 0x41;
                ep->pos_38    = wp->position;
            }
            part->timer_E = 0;
            if (wp->position.z < 0x400)
            {
                wp->value_44.half[1] = 0;
                if (wp->position.x < 0)
                {
                    wp->value_44.half[0] = -0x100;
                }
                else
                {
                    wp->value_44.half[0] = 0x100;
                }
                wp->value_48.half[0] = -0x80;
                wp->value_44.half[1] = 0;
                wp->routine_2        = 1;
            }
            else
            {
                part->flags_4 |= 0x20;
                wp->value_44.half[1] = 0x80;
                wp->value_48.half[0] = -0x200;
                wp->value_44.half[0] = 0;
                wp->routine_2        = 2;
            }
            break;
        case 1:
            Obj_pos_set(wp, wp->value_48.half[0], 0, wp->value_44.half[0]);
            if (STCOM_ABS(wp->position.x) > 0x600 || wp->position.z >= 0x400)
            {
                ep = func_80031618();
                if (ep != NULL)
                {
                    ep->flags_0   = 5;
                    ep->kind_2    = 0x80;
                    ep->variant_3 = 0x41;
                    ep->pos_38    = wp->position;
                }
                part->flags_4 |= 0x20;
                wp->value_44.half[1] = 0x80;
                wp->value_48.half[0] = -0x200;
                wp->value_44.half[0] = 0;
                wp->routine_2        = 2;
            }
            break;
        case 2:
            wp->value_44.half[1] += 4;
            if (part->timer_E == 0x3C)
            {
                wp->value_48.half[0] = -0x400;
            }
            part->timer_E++;
            Obj_pos_set(wp, wp->value_48.half[0], wp->value_44.half[1], 0);
            if (wp->position.y >= -0x7F)
            {
                part->flags_4 |= 1;
            }
            break;
    }
}
