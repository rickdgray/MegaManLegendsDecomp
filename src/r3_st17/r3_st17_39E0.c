#include "common.h"
#include "st17.h"

void func_801039E0(STAGE_OBJ *wp, ST17_PART28 *part)
{
    if (wp->routine_3 != 0 && wp->routine_3 < 6 && part->owner_0->u_E.b.byte_E > 0)
    {
        wp->routine_3 = 6;
    }
    switch (wp->routine_3)
    {
        case 0:
            wp->value_44.half[0] = 0;
            part->timer_E        = 0;
            part->value_10       = 0;
            wp->routine_3++;
            // fall through
        case 1:
            if (part->owner_0->routine_1 == 2)
            {
                wp->routine_3++;
            }
            break;
        case 2:
            wp->position.z -= 0x80;
            if (++part->timer_E == 0x60)
            {
                wp->position.y = 0;
                switch (wp->u_C.b.byte_C)
                {
                    case 1:
                        wp->position.z = 0xA00;
                        break;
                    case 0:
                        wp->position.z = 0x800;
                        break;
                    case 2:
                        wp->position.z = 0xA00;
                        break;
                    case 3:
                    case 4:
                        wp->position.z = 0xC00;
                        break;
                }
                if (wp->u_C.b.byte_C == 0)
                {
                    part->timer_E  = 0;
                    part->value_10 = 0x10;
                }
                else if (wp->u_C.b.byte_C == 1 || wp->u_C.b.byte_C == 2)
                {
                    part->timer_E  = 8;
                    part->value_10 = 8;
                }
                else
                {
                    part->timer_E  = 0x10;
                    part->value_10 = 0;
                }
                wp->routine_3++;
            }
            break;
        case 3:
            if (part->timer_E != 0)
            {
                part->timer_E--;
            }
            else
            {
                wp->routine_3++;
            }
            break;
        case 4:
            wp->position.y -= 0x10;
            if (wp->position.y < -0x7FF)
            {
                wp->position.y = -0x800;
                wp->routine_3++;
            }
            else if (wp->value_44.half[1] >= 3)
            {
                wp->value_44.half[1]--;
            }
            break;
        case 5:
            if (part->value_10 == 0)
            {
                wp->routine_3 = 8;
            }
            else
            {
                part->value_10--;
            }
            break;
        case 6:
            if (part->owner_0->u_E.b.byte_E == 2)
            {
                wp->routine_3++;
            }
            break;
        case 7:
            wp->position.y = 0;
            switch (wp->u_C.b.byte_C)
            {
                case 1:
                    wp->position.z = 0xA00;
                    break;
                case 0:
                    wp->position.z = 0x800;
                    break;
                case 2:
                    wp->position.z = 0xA00;
                    break;
                case 3:
                case 4:
                    wp->position.z = 0xC00;
                    break;
            }
            wp->position.y = -0x800;
            wp->routine_3++;
            break;
        case 8:
            if (part->owner_0->routine_1 == 3)
            {
                part->timer_E        = 0x80;
                wp->value_44.half[1] = 4;
                switch (wp->u_C.b.byte_C)
                {
                    case 0:
                        wp->value_44.half[0] = 0;
                        wp->value_48.half[0] = 0;
                        break;
                    case 1:
                        wp->value_44.half[0] = 4;
                        wp->value_48.half[0] = 0;
                        break;
                    case 2:
                        wp->value_44.half[0] = -4;
                        wp->value_48.half[0] = 4;
                        break;
                    case 3:
                        wp->value_44.half[0] = 8;
                        wp->value_48.half[0] = 4;
                        break;
                    case 4:
                        wp->value_44.half[0] = -8;
                        wp->value_48.half[0] = 8;
                        break;
                }
                wp->routine_3++;
            }
            break;
        case 9:
            if (part->timer_E == 0)
            {
                wp->value_44.half[0] = 0;
                wp->value_48.half[0] = 0;
                wp->value_44.half[1] = 0;
                wp->routine_3++;
            }
            else
            {
                wp->position.x += wp->value_44.half[0];
                wp->position.y += wp->value_44.half[1];
                wp->position.z += wp->value_48.half[0];
                part->timer_E--;
            }
            break;
        case 10:
            part->flags_4 |= 2;
            wp->value_48.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_44.half[0] = 0;
            part->vz_16          = 0;
            part->vy_14          = 0;
            part->vx_12          = 0;
            part->timer_E        = 0;
            part->value_10       = wp->u_C.b.byte_C * 64;
            wp->routine_3++;
            break;
        case 11:
            if (part->value_10 == 0)
            {
                Sound_call2(0x1A0, &wp->position);
                wp->value_48.half[0] = 0;
                part->value_1C       = part->random_6 & 0xF00;
                wp->routine_3        = 0;
                wp->routine_2++;
            }
            else
            {
                wp->value_48.half[0] = -8;
                part->value_10--;
            }
            wp->position.z += wp->value_48.half[0];
            break;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_80103E6C(STAGE_OBJ *wp, ST17_PART28 *part)
{
    sint16 dir;

    switch (wp->routine_3)
    {
        case 0:
            part->timer_E  = 0;
            part->value_10 = 0;
            part->value_1A = 0;
            part->vz_16    = 0;
            part->value_18 = 0;
            if (part->random_6 & 1)
            {
                part->value_1E = (part->random_6 >> 2) & 7;
            }
            else
            {
                part->value_1E = -((part->random_6 >> 4) & 7);
            }
            wp->routine_3++;
            // fall through
        case 1:
            if (part->timer_E < 0x140)
            {
                switch (part->timer_E)
                {
                    case 0:
                        part->vz_16    = -1;
                        part->value_18 = 0x14;
                        break;
                    case 0x20:
                        part->vz_16 = 0;
                        break;
                    case 0x40:
                        part->value_18 = 0;
                        break;
                    case 0x60:
                        part->value_18 = -0x14;
                        break;
                    case 0x80:
                        part->vz_16 = 1;
                        break;
                    case 0xA0:
                        part->flags_4 |= 0x40;
                        break;
                    case 0xC0:
                        part->vz_16 = 0;
                        break;
                    case 0xE0:
                        part->value_18 = 0;
                        break;
                    case 0x100:
                        part->value_18 = 0x14;
                        break;
                    case 0x120:
                        part->vz_16 = -1;
                        break;
                }
                part->value_1C += part->value_1E;
                part->timer_E++;
            }
            else
            {
                part->vz_16    = 0;
                part->value_18 = 0;
                part->flags_4 |= 0x40;
                if (wp->u_E.b.byte_E < 3 && wp->u_E.b.byte_F != 0)
                {
                    wp->routine_2++;
                }
                wp->routine_3 = 0;
            }
            break;
    }
    wp->value_48.half[0] += part->vz_16;
    wp->position.z += wp->value_48.half[0];
    part->value_1A += part->value_18;
    wp->position.x = (part->value_1A * rsin(part->value_1C)) >> 12;
    wp->position.y = ((part->value_1A * rcos(part->value_1C)) >> 12) - 0x600;
    dir            = -1;
    if (wp->position_prev.x < wp->position.x)
    {
        dir = 1;
    }
    wp->value_44.half[0] = dir;
    if (part->flags_4 & 0x40)
    {
        if (part->timer_E == 0xA1)
        {
            wp->position.y = -0x600;
            wp->position.x = 0;
            wp->position.z = -0x800;
        }
        else
        {
            wp->position.y = -0x600;
            wp->position.x = 0;
            wp->position.z = 0x800;
        }
        part->flags_4 &= ~0x40;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (wp->position.z < 0x300)
    {
        part->flags_4 &= ~8;
    }
    else if ((part->random_6 & 1) && wp->position.y < -0x600)
    {
        part->flags_4 |= 8;
    }
    if (ST17_DIST(wp) < 0x90000)
    {
        if (!(part->flags_4 & 0x80))
        {
            part->flags_4 |= 0x80;
            Sound_call2(0x150, &wp->position);
        }
    }
    if (ST17_DIST(wp) > 0x240000)
    {
        part->flags_4 &= ~0x80;
    }
}

void func_8010421C(STAGE_OBJ *wp, ST17_PART28 *part)
{
    switch (wp->routine_3)
    {
        case 0:
            part->value_10 = 0;
            part->timer_E  = 0;
            part->flags_4 &= ~8;
            wp->value_48.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_44.half[0] = 0;
            wp->routine_3++;
            // fall through
        case 1:
            if (part->timer_E < 0x40)
            {
                switch (part->timer_E)
                {
                    case 0:
                        part->vx_12 = (wp->u_C.b.byte_D == 0) ? -1 : 1;
                        part->vy_14 = -1;
                        part->vz_16 = 2;
                        break;
                    case 0xC:
                        part->vz_16 = 0;
                        break;
                    case 0x10:
                        part->vx_12 = 0;
                        part->vy_14 = 0;
                        break;
                    case 0x20:
                        part->vy_14 = 1;
                        break;
                    case 0x30:
                        part->vx_12 = (wp->u_C.b.byte_D == 0) ? 1 : -1;
                        part->vy_14 = 0;
                        break;
                    case 0x34:
                        part->vz_16 = -2;
                        break;
                }
                part->timer_E++;
            }
            else
            {
                part->vx_12 = 0;
                part->vy_14 = 0;
                part->vz_16 = 0;
                part->owner_0->u_E.b.byte_F--;
                wp->routine_3++;
            }
            break;
        case 2:
            if (part->owner_0->u_E.b.byte_F <= 0)
            {
                part->timer_E = 0;
                wp->routine_3++;
            }
            break;
        case 3:
            if (part->timer_E < 0x28)
            {
                switch (part->timer_E)
                {
                    case 0:
                        part->vy_14 = (wp->u_C.b.byte_D == 0) ? 1 : -1;
                        break;
                    case 8:
                        part->vy_14 = 0;
                        break;
                    case 0x20:
                        part->vy_14 = (wp->u_C.b.byte_D == 0) ? -1 : 1;
                        break;
                }
                part->timer_E++;
            }
            else
            {
                part->vy_14 = 0;
                wp->routine_3++;
            }
            break;
        case 4:
            wp->routine_3 = 0;
            wp->routine_2++;
            break;
    }
    wp->value_44.half[0] += part->vx_12;
    wp->value_44.half[1] += part->vy_14;
    wp->value_48.half[0] += part->vz_16;
    wp->position.x += wp->value_44.half[0];
    wp->position.z += wp->value_48.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position_fixed.v.z = wp->position.z << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.x = wp->position.x << 16;
}

void func_80104498(STAGE_OBJ *wp, ST17_PART28 *part)
{
    switch (wp->routine_3)
    {
        case 0:
            part->timer_E = 0;
            part->vx_12   = 0;
            part->vy_14   = 0;
            part->vz_16   = 0;
            if (wp->position.x < 0)
            {
                part->value_20 = 0x300;
                part->value_22 = wp->position.y - 0x200;
            }
            else
            {
                part->value_20 = -0x300;
                part->value_22 = wp->position.y + 0x200;
            }
            part->value_24 = wp->position.z;
            part->value_1A = part->random_6 & 1;
            wp->routine_3++;
            // fall through
        case 1:
            if (part->value_1A == 0)
            {
                func_80104BBC(wp, part);
            }
            else
            {
                func_80104D78(wp, part);
            }
            break;
        case 2:
            if (part->timer_E < 0x50)
            {
                switch (part->timer_E)
                {
                    case 0:
                        if (wp->position.x < 0)
                        {
                            part->vx_12    = 1;
                            part->vy_14    = 0;
                            part->value_20 = 0x300;
                            part->value_22 = wp->position.y - 0x200;
                        }
                        else
                        {
                            part->vx_12    = -1;
                            part->vy_14    = 0;
                            part->value_20 = -0x300;
                            part->value_22 = wp->position.y + 0x200;
                        }
                        part->value_24 = wp->position.z;
                        break;
                    case 8:
                        part->flags_4 |= 8;
                        break;
                    case 0x20:
                        part->vx_12 = 0;
                        if (wp->position.x < 0)
                        {
                            part->vy_14 = -1;
                        }
                        else
                        {
                            part->vy_14 = 1;
                        }
                        break;
                    case 0x30:
                        if (wp->position.x < 0)
                        {
                            part->vx_12 = 1;
                        }
                        else
                        {
                            part->vx_12 = -1;
                        }
                        part->vy_14 = 0;
                        break;
                    case 0x40:
                        if (wp->position.x < 0)
                        {
                            part->vy_14 = -1;
                        }
                        else
                        {
                            part->vy_14 = 1;
                        }
                        break;
                    case 0x48:
                        part->flags_4 &= ~8;
                        break;
                }
                part->timer_E++;
            }
            else
            {
                part->vx_12   = 0;
                part->vy_14   = 0;
                part->vz_16   = 0;
                part->timer_E = 0;
                part->flags_4 |= 0x40;
                wp->routine_3 = 0;
            }
            break;
    }
    wp->value_44.half[0] += part->vx_12;
    wp->value_44.half[1] += part->vy_14;
    wp->value_48.half[0] += part->vz_16;
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (part->flags_4 & 0x40)
    {
        wp->position.x = part->value_20;
        wp->position.y = part->value_22;
        wp->position.z = part->value_24;
        part->flags_4 &= ~0x40;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    if (ST17_DIST(wp) < 0x90000)
    {
        if (!(part->flags_4 & 0x80))
        {
            part->flags_4 |= 0x80;
            Sound_call2(0x150, &wp->position);
        }
    }
    if (ST17_DIST(wp) > 0x240000)
    {
        part->flags_4 &= ~0x80;
    }
}

void func_8010483C(STAGE_OBJ *wp, ST17_PART28 *part)
{
    uint32 hit;
    sint32 damage;

    hit    = part->hit_28.value_0;
    damage = hit & 0xFFFFFF;
    if (damage != 0)
    {
        if (hit & 0x18000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                part->flags_4 = (part->flags_4 & ~0xA) | 0x11;
            }
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
        part->flags_4 |= 4;
    }
    else
    {
        part->flags_4 &= ~4;
    }
}

void func_80104900(STAGE_OBJ *wp, ST17_PART28 *part)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR v;
    STCOM_FIXED_VECTOR offset;
    ST17_SHOT *shot;
    sint32 spawned;

    spawned = 0;
    func_80030058(&fixed, wp->rotation.y, 0x600, 0, 0);
    func_80030150(&fixed, &v);
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0 = 3;
        shot->kind_2  = 1;
        shot->value_4 = 0;
        shot->value_F = 0x34;
        func_80030058(&offset, wp->rotation.y, 0xC80, 0xD00, 0x440);
        shot->position_fixed.v = offset;
        shot->position_fixed.v.x += wp->position_fixed.v.x;
        shot->position_fixed.v.y += wp->position_fixed.v.y;
        shot->position_fixed.v.z += wp->position_fixed.v.z;
        func_80030150(&shot->position_fixed.v, &shot->position);
        spawned                = 1;
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = 0;
        shot->value_48.half[0] = v.z << 8;
        shot->value_48.half[1] = 0;
        shot->value_50         = 0;
        shot->value_4C.half[1] = 0;
        shot->value_4C.half[0] = 0;
        func_80104B34((STAGE_XYZ *)&shot->position);
    }
    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0 = 3;
        shot->kind_2  = 1;
        shot->value_4 = 0;
        shot->value_F = 0x34;
        func_80030058(&offset, wp->rotation.y, 0xC80, 0xD00, -0x440);
        shot->position_fixed.v = offset;
        shot->position_fixed.v.x += wp->position_fixed.v.x;
        shot->position_fixed.v.y += wp->position_fixed.v.y;
        shot->position_fixed.v.z += wp->position_fixed.v.z;
        func_80030150(&shot->position_fixed.v, &shot->position);
        spawned                = 1;
        shot->value_44.half[0] = v.x << 8;
        shot->value_44.half[1] = 0;
        shot->value_48.half[0] = v.z << 8;
        shot->value_48.half[1] = 0;
        shot->value_50         = 0;
        shot->value_4C.half[1] = 0;
        shot->value_4C.half[0] = 0;
        func_80104B34((STAGE_XYZ *)&shot->position);
    }
    if (spawned)
    {
        Sound_call2(0xD0, &shot->position);
    }
}

void func_80104B34(STAGE_XYZ *pos)
{
    STCOM23_PACKET *p;

    p          = Billboard_get();
    p->code_4  = 0x2C808080;
    p->xy_8    = (uint16)pos->x | (pos->y << 16);
    p->z_10    = pos->z;
    p->uv_1C   = 0x5FC0;
    p->uv_24   = 0x5FDF;
    p->size_18 = 0x40;
    p->uv_C    = 0x3D0840C0;
    p->uv_14   = 0xE40DF;
    p->pad_20  = 8;
}

void func_80104BBC(STAGE_OBJ *wp, ST17_PART28 *part)
{
    if (part->timer_E < 0x8A)
    {
        switch (part->timer_E)
        {
            case 0:
                part->vx_12 = 0;
                part->vy_14 = 0;
                part->vz_16 = -4;
                break;
            case 0x15:
                part->vz_16 = 0;
                break;
            case 0x30:
                part->vz_16 = 4;
                part->flags_4 |= 8;
                break;
            case 0x5A:
                part->vz_16 = 0;
                part->flags_4 &= ~8;
                part->vy_14 = (wp->position.x < 0) ? 1 : -1;
                break;
            case 0x75:
                part->vz_16 = -4;
                break;
            case 0x31:
                part->vx_12 = (wp->position.x < 0) ? 4 : -4;
                break;
            case 0x49:
                part->vx_12 = (wp->position.x > 0) ? -4 : 4;
                break;
            case 0x41:
            case 0x59:
                part->vx_12 = 0;
                break;
            case 0x6A:
                part->vy_14 = 0;
                break;
            case 0x7A:
                part->vy_14 = (wp->position.x < 0) ? -1 : 1;
                break;
        }
        part->timer_E++;
    }
    else
    {
        part->vx_12   = 0;
        part->vy_14   = 0;
        part->vz_16   = 0;
        part->timer_E = 0;
        part->flags_4 |= 0x40;
        wp->routine_3++;
    }
}

void func_80104D78(STAGE_OBJ *wp, ST17_PART28 *part)
{
    if (part->timer_E < 0x8A)
    {
        switch (part->timer_E)
        {
            case 0:
                part->vx_12 = 0;
                part->vy_14 = 0;
                part->vz_16 = -3;
                break;
            case 0x20:
                part->vz_16 = 0;
                break;
            case 0x25:
                part->vz_16 = 3;
                part->flags_4 |= 8;
                break;
            case 0x65:
                part->vz_16 = 0;
                part->flags_4 &= ~8;
                break;
            case 0x6A:
                part->vy_14 = 0;
                part->vz_16 = -3;
                break;
            case 0x31:
                part->vx_12 = (wp->position.x < 0) ? 4 : -4;
                break;
            case 0x49:
                part->vx_12 = (wp->position.x > 0) ? -4 : 4;
                break;
            case 0x41:
            case 0x59:
                part->vx_12 = 0;
                break;
            case 0x5A:
                part->vy_14 = (wp->position.x < 0) ? 1 : -1;
                break;
            case 0x7A:
                part->vy_14 = (wp->position.x < 0) ? -1 : 1;
                break;
        }
        part->timer_E++;
    }
    else
    {
        part->vx_12   = 0;
        part->vy_14   = 0;
        part->vz_16   = 0;
        part->timer_E = 0;
        part->flags_4 |= 0x40;
        wp->routine_3++;
    }
}

void func_80104F38(STAGE_OBJ *wp)
{
    D_8011B0A8[wp->routine_1](wp);
    if (wp->u_C.b.byte_C != 0)
    {
        func_80032488(wp);
    }
}

void func_80104F98(STAGE_OBJ *wp)
{
    STCOM_EFFECT *fx;
    uint8 i;
    uint8 j;

    if (wp->routine_2 == 0)
    {
        wp->u_C.b.byte_C   = 0;
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 2; j++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0   = 1;
                    fx->kind_2    = 0x1A;
                    fx->variant_3 = 0;
                    fx->value_C   = wp->value_1;
                    fx->value_D   = i + 1;
                }
            }
        }
    }
    if (Scene_work.value_10 == 0xF)
    {
        wp->u_C.b.byte_C++;
    }
}

void func_801050C8(STAGE_OBJ *wp)
{
    sint8 step;
    uint8 anim;
    sint16 z;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 0x42;
        Model_work_init(wp, NULL);
        wp->scale.words[0]   = 0x0C000C00;
        wp->scale.words[1]   = 0xC00;
        wp->scale.v.pad      = 0x4210;
        wp->value_78         = 0;
        wp->anim_AC          = 0;
        wp->anim_prev_AD     = 0xFF;
        wp->value_48.half[0] = 0;
        wp->routine_1        = 0;
        wp->routine_0++;
    }
    step = wp->u_C.b.byte_C;
    if (step < 5)
    {
        if (wp->position.z > step * 0x3B0 + 0x1E00)
        {
            wp->value_48.half[0] = -((5 - step) * 4);
        }
        else if (wp->value_48.half[0] < 0)
        {
            wp->value_48.half[0] += 8;
            if (wp->value_48.half[0] > 0)
            {
                wp->value_48.half[0] = 0;
            }
        }
    }
    z                      = wp->position.z + wp->value_48.half[0];
    wp->position.z         = z;
    wp->position_fixed.v.z = z << 16;
    anim                   = wp->anim_AC;
    if (anim != wp->anim_prev_AD)
    {
        func_800322A8(wp, anim, 0);
        return;
    }
    func_80032488(wp);
}

void func_8010526C(ST17_SPARK *wp)
{
    ST17_SPARK *owner;

    owner = wp->owner_2C;
    if (--wp->timer_D == 0 || owner->routine_0 == 2)
    {
        wp->timer_D = 0;
        wp->routine_0++;
    }
    wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
    wp->w_24 += wp->type_F;
    wp->y_1E += wp->rise_28;
}

void func_801052F8(ST17_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_8010526C(wp);
}

void func_8010532C(STAGE_FX *wp)
{
    func_80031988(wp);
}

void func_8010534C(ST17_SPARK *wp)
{
    D_8011B0AC[wp->routine_0](wp);
}

void func_80105388(ST17_SPARK *wp)
{
    ST17_SPARK *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->variant_3 = 1;
            ep->flags_6   = wp->flags_6;
            ep->value_C   = 0;
            ep->timer_D   = (rand() & 7) * 2 + 0x40;
            ep->x_1C      = wp->x_1C + (rand() & 0xF);
            ep->y_1E      = wp->y_1E;
            ep->z_20      = wp->z_20 + (rand() & 0xF);
            ep->mode_14   = 0x3D48004E;
            ep->u_22      = ((rand() & 3) << 5) + 0x20;
            ep->v_23      = 0;
            ep->w_24      = wp->width_E;
            ep->type_F    = wp->type_F;
            ep->rise_28   = wp->rise_28;
            ep->owner_2C  = wp;
            for (i = 0; i < wp->count_26; i++)
            {
                func_8010534C(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_801054D0(ST17_SPARK *wp)
{
    if (wp->variant_3 == 1)
    {
        func_8010534C(wp);
    }
    else if (wp->routine_0 != 2)
    {
        func_80105388(wp);
    }
    else
    {
        func_80031988(wp);
    }
}

ST17_SPARK *func_80105530(STCOM_SVECTOR *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag)
{
    ST17_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0;
        ep->variant_3 = 0;
        ep->value_C   = 0;
        ep->width_E   = width;
        ep->type_F    = growth;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->count_26  = count;
        if (flag)
        {
            ep->flags_6 |= 0x20;
        }
        else
        {
            ep->flags_6 &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < count; i++)
        {
            func_80105388(ep);
        }
    }
    return ep;
}
