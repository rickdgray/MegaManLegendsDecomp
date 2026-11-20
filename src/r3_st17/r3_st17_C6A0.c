#include "common.h"
#include "st17.h"

void func_8010C6A0(STAGE_OBJ *wp)
{
    D_8011BE00[wp->variant_3](wp, wp->ext_3C0);
}

void func_8010C6DC(STAGE_OBJ *wp)
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
        func_8002F9EC(wp, 0);
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
        if (wp->position.z > step * 0x540 + 0x1E00)
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

void func_8010C880(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    uint8 anim;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    ext->random_16          = rand();
    func_8010EBC0(wp, ext, 0xC, 0x4210);
    D_8011BE08[wp->routine_0](wp, ext);
    anim = wp->anim_AC;
    if (anim != wp->anim_prev_AD)
    {
        func_800322A8(wp, anim, 0);
    }
    else
    {
        func_80032488(wp);
    }
    ext->frame_142++;
}

void func_8010C994(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    ST17_BOSS_DATA *data;
    sint16 i;
    sint16 life;
    STCOM_SVECTOR *pos;

    wp->flags_0 |= 0x42;
    func_8002F9EC(wp, 0);
    wp->scale.words[0] = 0x0C000C00;
    wp->scale.words[1] = 0xC00;
    data               = D_8009884C[wp->kind_2];
    for (i = 0; i < 12; i++)
    {
        switch (i)
        {
            case 9:
                ext->life_A0[i] = data->life_8 * 16;
                break;
            case 0:
            case 10:
                ext->life_A0[i] = data->life_A * 16;
                break;
            case 1:
            case 11:
                ext->life_A0[i] = data->life_B * 16;
                break;
            case 2:
                ext->life_A0[i] = data->life_C * 16;
                break;
            default:
                ext->life_A0[i] = data->life_D * 16;
                break;
        }
        ext->life_max_B8[i]    = ext->life_A0[i];
        ext->hit_D0[i].value_4 = 0;
        ext->hit_D0[i].value_0 = 0;
        ext->timer_130[i]      = 0xFF;
    }
    life             = ext->life_max_B8[9] + ext->life_max_B8[0] + ext->life_max_B8[1] + ext->life_max_B8[2];
    wp->life_max_B0  = life;
    wp->life_prev_B2 = life;
    wp->life_6E      = life;
    func_8010EBC0(wp, ext, 0xC, 0x4210);
    for (i = 0; i < 16; i++)
    {
        pos    = &ext->pos_20[i];
        pos->x = D_8011BE40[i].x + wp->position.x;
        pos->y = D_8011BE40[i].y + wp->position.y;
        pos->z = D_8011BE40[i].z + wp->position.z;
    }
    ext->value_1E  = data->value_9;
    ext->model_C   = func_80105A0C(wp, 0, &ext->pos_20[0]);
    ext->model_10  = func_80101B58(wp, 1, &ext->pos_20[3]);
    ext->flags_14  = 2;
    ext->timer_18  = 0;
    ext->timer_1A  = 0;
    ext->arm_4     = NULL;
    ext->arm_8     = NULL;
    ext->phase_1F  = 0;
    ext->count_13C = 0;
    ext->count_13D = 0;
    ext->count_13E = 0;
    ext->value_13F = 0;
    ext->flags_141 = 0;
    ext->flags_140 = 0;
    ext->frame_142 = 0;
    ext->count_144 = 0;
    func_80036478(ext->track_148, 0, 0);
    wp->anim_prev_AD     = 0xFF;
    wp->u_C.b.byte_C     = 0;
    wp->value_48.half[0] = 0;
    wp->value_44.half[1] = 0;
    wp->value_44.half[0] = 0;
    wp->value_50         = 0;
    wp->value_4C.half[1] = 0;
    wp->value_4C.half[0] = 0;
    wp->value_78         = 0;
    wp->anim_AC          = 0;
    wp->routine_0        = 1;
    wp->routine_1        = 0;
    wp->routine_2        = 0;
    wp->routine_3        = 0;
}

void func_8010CC54(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    uint8 next;

    if (ext->flags_14 & 2)
    {
        func_8010DD10(wp, ext);
    }
    func_8010E164(wp, ext);
    D_8011BE14[wp->routine_1](wp, ext);
    if (ext->flags_14 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1 = 9;
                break;
            case 3:
            case 5:
                next = 7;
                if (ext->flags_14 & 0x40)
                {
                    next = 2;
                }
                wp->routine_1 = next;
                break;
            case 1:
            case 6:
                next = 8;
                if (ext->flags_14 & 0x40)
                {
                    next = 4;
                }
                wp->routine_1 = next;
                break;
            case 2:
            case 4:
                next = 9;
                if (ext->flags_14 & 0x40)
                {
                    next = 0xA;
                }
                wp->routine_1 = next;
                break;
            case 7:
                if (ext->flags_14 & 0x40)
                {
                    wp->routine_1 = 2;
                }
                else if (ext->flags_14 & 0x10)
                {
                    wp->routine_1 = 1;
                }
                else if (ext->flags_14 & 0x20)
                {
                    wp->routine_1 = 2;
                }
                break;
            case 8:
                if (ext->flags_14 & 0x40)
                {
                    wp->routine_1 = 4;
                }
                else if (ext->flags_14 & 8)
                {
                    wp->routine_1 = 3;
                }
                else if (ext->flags_14 & 0x20)
                {
                    wp->routine_1 = 4;
                }
                break;
            case 9:
                if (ext->flags_14 & 0x40)
                {
                    wp->routine_1 = 0xA;
                }
                else if (ext->flags_14 & 8)
                {
                    wp->routine_1 = 5;
                }
                else if (ext->flags_14 & 0x10)
                {
                    wp->routine_1 = 6;
                }
                break;
            case 10:
                wp->routine_0 = 2;
                wp->routine_1 = 0;
                break;
        }
        wp->routine_2 = 0;
        ext->flags_14 &= 0xFFC6;
    }
    if (ext->flags_14 & 2)
    {
        func_8010E514(wp, ext);
    }
    func_8010E660(wp, ext);
    ext->phase_1F = (ext->phase_1F + 2) & 0x1F;
}

void func_8010CE88(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    switch (wp->routine_1)
    {
        case 0:
            ext->timer_18        = 0;
            wp->value_4C.half[0] = 0;
            wp->value_4C.half[1] = 0;
            wp->value_50         = 0;
            wp->routine_1++;
            // fall through
        case 1:
            if (ext->timer_18 < 0x1FC)
            {
                switch (ext->timer_18)
                {
                    case 0:
                        wp->value_4C.half[0] = -1;
                        wp->value_4C.half[1] = -1;
                        break;
                    case 0x10:
                        wp->value_4C.half[0] = 0;
                        wp->value_4C.half[1] = 0;
                        wp->u_C.b.byte_C     = 1;
                        break;
                    case 0x30:
                        wp->value_4C.half[1] = 1;
                        break;
                    case 0x40:
                        wp->value_4C.half[1] = 0;
                        break;
                    case 0x88:
                        wp->value_50 = -1;
                        break;
                }
                ext->timer_18++;
            }
            else
            {
                ext->timer_18        = 0;
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = 0;
                wp->value_50         = 0;
                wp->routine_1++;
            }
            break;
    }
    wp->value_44.half[0] += wp->value_4C.half[0];
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (ext->flags_14 & 4)
    {
        wp->position.x = -0x1000;
        wp->position.y = -0x400;
        wp->position.z = 0x400;
        ext->flags_14 &= ~4;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010D04C(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    switch (wp->routine_2)
    {
        case 0:
            ext->timer_18        = 0;
            wp->value_4C.half[0] = 0;
            wp->value_4C.half[1] = 0;
            wp->value_50         = 0;
            wp->routine_2++;
            break;
        case 1:
            if (ext->timer_18 < 0xD0)
            {
                switch (ext->timer_18)
                {
                    case 0:
                        wp->value_50 = -1;
                        break;
                    case 0x10:
                        wp->value_50 = 0;
                        break;
                    case 0xC0:
                        wp->value_50 = 1;
                        break;
                }
                ext->timer_18++;
            }
            else
            {
                ext->timer_18 = 0;
                ext->flags_14 |= 4;
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = 0;
                wp->value_50         = 0;
            }
            break;
        case 2:
            if (ext->timer_18 < 0x1F0)
            {
                switch (ext->timer_18)
                {
                    case 0:
                        wp->value_50 = 1;
                        break;
                    case 0x10:
                        wp->value_50 = 0;
                        break;
                    case 0x100:
                        wp->value_4C.half[1] = 1;
                        break;
                    case 0x110:
                        wp->value_4C.half[1] = 0;
                        break;
                    case 0x1E0:
                        wp->value_4C.half[1] = -1;
                        wp->value_50         = -1;
                        break;
                }
                ext->timer_18++;
            }
            else
            {
                ext->timer_18 = 0;
                ext->flags_14 |= 5;
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = 0;
                wp->value_50         = 0;
                ext->flags_140 |= 1;
            }
            break;
    }
    wp->value_44.half[0] += wp->value_4C.half[0];
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (ext->flags_14 & 4)
    {
        if (wp->routine_2 == 1)
        {
            wp->position.y = -0x1A00;
            wp->position.x = 0;
            wp->position.z = -0x600;
            wp->routine_2++;
        }
        else
        {
            wp->position.y = -0xC00;
            wp->position.x = 0;
            wp->position.z = 0x1800;
        }
        ext->flags_14 &= ~4;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010D2CC(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint16 step;
    sint16 x;

    if (wp->routine_2 == 0)
    {
        ext->timer_18        = 0;
        wp->value_4C.half[0] = 0;
        wp->value_4C.half[1] = 0;
        wp->value_50         = 0;
        wp->routine_2++;
    }
    if (ext->timer_18 < 0x2F8)
    {
        switch (ext->timer_18)
        {
            case 0:
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = -1;
                break;
            case 0x74:
                step = -1;
                if (wp->routine_1 == 1)
                {
                    step = 1;
                }
                wp->value_4C.half[0] = step;
                break;
            case 0x16C:
                wp->value_4C.half[1] = 1;
                break;
            case 0x17C:
                ext->flags_14 |= 4;
                break;
            case 0x10:
            case 0x18C:
                wp->value_4C.half[1] = 0;
                break;
            case 0x274:
                step = 1;
                if (wp->routine_1 == 1)
                {
                    step = -1;
                }
                wp->value_4C.half[0] = step;
                break;
            case 0x84:
            case 0x284:
                wp->value_4C.half[0] = 0;
                break;
            case 0x2E8:
                wp->value_4C.half[1] = -1;
                break;
        }
        ext->timer_18++;
    }
    else
    {
        ext->timer_18 = 0;
        ext->flags_14 |= 5;
        wp->value_4C.half[0] = 0;
        wp->value_4C.half[1] = 0;
    }
    wp->value_44.half[0] += wp->value_4C.half[0];
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (ext->flags_14 & 4)
    {
        if (wp->routine_2 == 1)
        {
            wp->position.x = 0;
            wp->position.y = -0x1A00;
            wp->routine_2++;
        }
        else
        {
            x = -0x1000;
            if (wp->routine_1 == 1)
            {
                x = 0x1000;
            }
            wp->position.x = x;
            wp->position.y = -0x340;
        }
        ext->flags_14 &= ~4;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010D534(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    if (wp->routine_2 == 0)
    {
        ext->timer_18        = 0;
        wp->value_4C.half[0] = 0;
        wp->value_4C.half[1] = 0;
        wp->value_50         = 0;
        wp->routine_2++;
    }
    if (wp->routine_1 == 2 || wp->routine_1 == 4)
    {
        func_8010E7F8(wp, ext);
    }
    else
    {
        func_8010E924(wp, ext);
    }
    wp->value_44.half[0] += wp->value_4C.half[0];
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (ext->flags_14 & 4)
    {
        switch (wp->routine_1)
        {
            case 5:
                wp->position.x = -0x1000;
                wp->position.y = -0x340;
                wp->position.z = 0x600;
                break;
            case 6:
                wp->position.x = 0x1000;
                wp->position.y = -0x340;
                wp->position.z = 0x600;
                break;
            case 4:
            case 2:
                wp->position.y = -0xC00;
                wp->position.x = 0;
                wp->position.z = 0x1800;
                break;
        }
        ext->flags_14 &= ~4;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010D6EC(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint32 shot;
    sint32 shift;
    sint16 y;

    shot  = -1;
    shift = 6; // a variable shift keeps retail's lh/sra; a constant one is done in 16 bits
    if (wp->routine_2 == 0)
    {
        ext->count_144 = 0;
        if (wp->routine_1 == 7)
        {
            ext->count_13C++;
        }
        else
        {
            ext->count_13D++;
        }
        ext->y_1C     = wp->position.y;
        ext->timer_18 = 0;
        if (ext->flags_14 & 0x40)
        {
            ext->flags_14 |= 1;
            return;
        }
        wp->routine_2++;
    }
    if (ext->timer_18 < 0xC0)
    {
        switch (ext->timer_18)
        {
            case 0x14:
            case 0x74:
                shot = 0;
                break;
            case 0x28:
            case 0x88:
                shot = 1;
                break;
            case 0x3C:
            case 0x9C:
                shot = 2;
                break;
        }
        ext->timer_18++;
    }
    else
    {
        ext->timer_18 = 0;
        func_8010ECD4(wp, ext);
    }
    if (shot != -1)
    {
        func_8010EE0C(wp, ext, shot);
    }
    if (ext->timer_18 == 0xC0 && !(ext->flags_140 & 4) && ext->count_144 != 0)
    {
        ext->flags_140 |= 4;
    }
    if ((ext->flags_14 & 0x40) && !(ext->timer_18 & 0x3F))
    {
        ext->timer_18 = 0;
        ext->flags_14 |= 1;
    }
    y                      = ext->y_1C + (D_800BBCF8[ext->timer_18 & 0x3F] >> shift);
    wp->position.y         = y;
    wp->position_fixed.v.y = y << 16;
}

void func_8010D908(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint32 shot;
    sint32 shift;
    sint16 y;

    shot  = -1;
    shift = 6; // a variable shift keeps retail's lh/sra; a constant one is done in 16 bits
    if (wp->routine_2 == 0)
    {
        ext->y_1C     = wp->position.y;
        ext->timer_18 = 0;
        ext->count_13E++;
        if (ext->flags_14 & 0x40)
        {
            ext->flags_14 |= 1;
            return;
        }
        wp->routine_2++;
    }
    if (ext->timer_18 < 0x100)
    {
        if (ext->timer_18 < 0xC0 && ext->timer_18 % 24 == 0)
        {
            shot = ext->timer_18 / 24;
        }
        ext->timer_18++;
    }
    else
    {
        ext->timer_18 = 0;
        func_8010ECD4(wp, ext);
    }
    if (shot != -1)
    {
        func_8010EFC8(wp, ext, shot);
    }
    if ((ext->flags_14 & 0x40) && !(ext->timer_18 & 0x3F))
    {
        ext->timer_18 = 0;
        ext->flags_14 |= 1;
    }
    y                      = ext->y_1C + (D_800BBCF8[ext->timer_18 & 0x3F] >> shift);
    wp->position.y         = y;
    wp->position_fixed.v.y = y << 16;
}

void func_8010DA94(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint16 y;
    sint32 shift;

    shift = 6; // a variable shift keeps retail's lh/sra; a constant one is done in 16 bits
    switch (wp->routine_2)
    {
        case 0:
            ext->timer_18        = 0;
            ext->timer_1A        = 0;
            wp->value_4C.half[1] = 0;
            wp->value_50         = 0;
            wp->routine_2++;
            // fall through
        case 1:
            func_8010EA58(wp, ext);
            break;
        case 2:
            ext->flags_140 |= 0x40;
            func_8010F0D8(wp, ext);
            wp->routine_2++;
            break;
        case 3:
            if ((ext->arm_4 != NULL && ext->arm_4->value_C != 0) || (ext->arm_8 != NULL && ext->arm_8->value_C != 0))
            {
                ext->timer_18 = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            if (ext->timer_18 < 0x5A)
            {
                if (ext->timer_18 == 0)
                {
                    if (ext->arm_4 != NULL)
                    {
                        ext->arm_4->value_C |= 0x80;
                        ext->arm_4 = NULL;
                    }
                    if (ext->arm_8 != NULL)
                    {
                        ext->arm_8->value_C |= 0x80;
                        ext->arm_8 = NULL;
                    }
                }
                ext->timer_18++;
            }
            else
            {
                wp->routine_2 = 2;
            }
            break;
    }
    if (wp->routine_2 >= 2)
    {
        y                      = ext->y_1C + (D_800BBCF8[ext->timer_1A & 0x3F] >> shift);
        wp->position.y         = y;
        wp->position_fixed.v.y = y << 16;
        if (ext->arm_4 != NULL)
        {
            ext->arm_4->position.y = wp->position.y + D_8011BEC8.y;
        }
        if (ext->arm_8 != NULL)
        {
            ext->arm_8->position.y = wp->position.y + D_8011BEC8.y;
        }
        ext->timer_1A++;
        if ((ext->flags_14 & 0x100) && !(ext->timer_1A & 0x3F))
        {
            if (ext->arm_4 != NULL)
            {
                Close_SHL_WORK(ext->arm_4);
            }
            if (ext->arm_8 != NULL)
            {
                Close_SHL_WORK(ext->arm_8);
            }
            ext->flags_14 |= 1;
        }
    }
}

void func_8010DD10(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    STCOM_SVECTOR *pos;
    sint16 i;
    sint32 damage;
    sint32 damage_0;
    sint32 damage_1;
    sint32 damage_9;
    uint32 hit;
    sint32 sound;
    STCOM_SVECTOR *at;

    pos      = ext->pos_20;
    i        = 0;
    damage_9 = 0;
    damage_0 = 0;
    damage_1 = 0;
    while (i < 12)
    {
        hit    = ext->hit_D0[i].value_0;
        damage = hit & 0xFFFFFF;
        if (damage != 0)
        {
            pos = &ext->pos_20[i];
            if (ext->timer_130[i] == 0xFF && (hit & 0x18000000))
            {
                switch (i)
                {
                    case 9:
                        damage_9 = damage;
                        break;
                    case 0:
                    case 10:
                        damage_0 = damage;
                        break;
                    case 1:
                    case 11:
                        damage_1 = damage;
                        break;
                    default:
                        ext->life_A0[i] -= damage;
                        if (ext->life_A0[i] <= 0)
                        {
                            ext->life_A0[i]   = 0;
                            ext->timer_130[i] = 0;
                            switch (i)
                            {
                                case 2:
                                    ext->model_C->u_C.b.byte_C |= 1;
                                    break;
                                case 3:
                                    ext->model_10->u_C.b.byte_C |= 1;
                                    break;
                                case 4:
                                    ext->model_10->u_C.b.byte_C |= 2;
                                    break;
                                case 5:
                                    ext->model_10->u_C.b.byte_C |= 4;
                                    break;
                                case 6:
                                    ext->model_10->u_C.b.byte_D |= 1;
                                    break;
                                case 7:
                                    ext->model_10->u_C.b.byte_D |= 2;
                                    break;
                                case 8:
                                    ext->model_10->u_C.b.byte_D |= 4;
                                    break;
                            }
                        }
                        Sound_call2(0xA0, pos);
                        func_8010EBC0(wp, ext, i, 0x7FFF);
                        break;
                }
            }
            else
            {
                Sound_call2(0x9B, pos);
            }
        }
        i++;
    }
    if (damage_0 != 0)
    {
        ext->life_A0[0] -= damage_0;
        if (ext->life_A0[0] <= 0)
        {
            ext->life_A0[0]    = 0;
            ext->timer_130[10] = 0;
            ext->timer_130[0]  = 0;
            ext->model_C->u_C.b.byte_C |= 2;
        }
        ext->life_A0[10] = ext->life_A0[0];
        Sound_call2(0xA0, &ext->pos_20[10]);
        func_8010EBC0(wp, ext, 0, 0x7FFF);
    }
    if (damage_1 != 0)
    {
        ext->life_A0[1] -= damage_1;
        if (ext->life_A0[1] <= 0)
        {
            ext->life_A0[1]    = 0;
            ext->timer_130[11] = 0;
            ext->timer_130[1]  = 0;
            ext->model_C->u_C.b.byte_C |= 4;
        }
        ext->life_A0[11] = ext->life_A0[1];
        Sound_call2(0xA0, &ext->pos_20[11]);
        func_8010EBC0(wp, ext, 1, 0x7FFF);
    }
    if (damage_9 != 0)
    {
        sound = 0x9B;
        if (ext->flags_14 & 0x80)
        {
            ext->life_A0[9] -= damage_9;
            if (ext->life_A0[9] <= 0)
            {
                ext->life_A0[9]   = 0;
                ext->timer_130[9] = 0;
                ext->flags_141 |= 0x70;
                ext->flags_14 |= 0x100;
            }
            func_8010EBC0(wp, ext, 9, 0x7FFF);
            sound = 0xA0;
            at    = &ext->pos_20[9];
        }
        else
        {
            at = pos;
        }
        Sound_call2(sound, at);
    }
    wp->life_prev_B2 = wp->life_6E;
    wp->life_6E      = ext->life_A0[9] + ext->life_A0[0] + ext->life_A0[1] + ext->life_A0[2];
    if ((ext->flags_141 & 1) && !(ext->flags_141 & 2) && wp->life_prev_B2 != wp->life_6E)
    {
        ext->flags_140 |= 2;
        ext->flags_141 |= 4;
    }
    if (!(ext->flags_14 & 0x40) && (*(uint32 *)ext->timer_130 & 0xFFFFFF) == 0x10101)
    {
        ext->flags_141 |= 0xF;
        ext->flags_14 |= 0x40;
    }
}

void func_8010E164(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    ST17_MARK *ep;
    sint16 i;
    sint16 count;

    count = 0;
    for (i = 0; i < 10; i++)
    {
        if (ext->timer_130[i] == 0)
        {
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0 = 1;
                ep->value_4 = 0;
                switch (i)
                {
                    case 2:
                        ep->kind_2    = 0x14;
                        ep->variant_3 = 1;
                        ep->value_E   = 0;
                        ep->target_44 = &ext->pos_20[2];
                        break;
                    case 0:
                        ep->kind_2    = 0x14;
                        ep->variant_3 = 2;
                        ep->value_E   = 0;
                        ep->target_44 = &ext->pos_20[0];
                        break;
                    case 1:
                        ep->kind_2    = 0x14;
                        ep->variant_3 = 3;
                        ep->value_E   = 0;
                        ep->target_44 = &ext->pos_20[1];
                        break;
                    case 9:
                        ep->kind_2    = 0x14;
                        ep->variant_3 = 4;
                        ep->value_E   = 0;
                        ep->target_44 = &ext->pos_20[9];
                        break;
                    default:
                        ep->flags_0                      = 5;
                        ep->kind_2                       = 0x80;
                        ep->variant_3                    = 0x41;
                        ep->pos_38                       = ext->pos_20[i];
                        ep->value_D                      = 1;
                        ST17_HITBOX_TBL(wp)[i + 1].off_3 = -1;
                        Sound_call2(0xA1, &ext->pos_20[i]);
                        break;
                }
            }
            ext->timer_130[i] = 1;
        }
        else if (ext->timer_130[i] == 1 && (i == 2 || i == 0 || i == 1))
        {
            count++;
        }
    }
    if (count == 3 && !(ext->flags_141 & 0x10))
    {
        ext->flags_140 |= 0x10;
    }
    else if (count == 1 && !(ext->flags_141 & 8))
    {
        ext->flags_140 |= 8;
    }
    if (ext->frame_142 & 1)
    {
        i = 3;
        while (i < 9)
        {
            if (ext->timer_130[i] != 0xFF)
            {
                ext->timer_130[i]++;
                if (ext->timer_130[i] == 0xFF)
                {
                    ST17_HITBOX_TBL(wp)[i + 1].off_3 = 0;
                    ext->life_A0[i]                  = ext->life_max_B8[i];
                    switch (i)
                    {
                        case 3:
                            ext->model_10->u_C.b.byte_C &= ~1;
                            break;
                        case 4:
                            ext->model_10->u_C.b.byte_C &= ~2;
                            break;
                        case 5:
                            ext->model_10->u_C.b.byte_C &= ~4;
                            break;
                        case 6:
                            ext->model_10->u_C.b.byte_D &= ~1;
                            break;
                        case 7:
                            ext->model_10->u_C.b.byte_D &= ~2;
                            break;
                        case 8:
                            ext->model_10->u_C.b.byte_D &= ~4;
                            break;
                    }
                }
            }
            i++;
        }
    }
}

void func_8010E514(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint16 i;
    STCOM_SVECTOR *pos;

    for (i = 0; i < 16; i++)
    {
        pos    = &ext->pos_20[i];
        pos->x = D_8011BE40[i].x + wp->position.x;
        pos->y = D_8011BE40[i].y + wp->position.y;
        pos->z = D_8011BE40[i].z + wp->position.z;
        if (i < 12)
        {
            ext->hit_D0[i].value_0 = 0;
        }
    }
    for (i = 0; i < 12; i++)
    {
        func_800341BC(&ext->pos_20[i], D_8011BE40[i].pad, 0, 0x8000, wp->value_1, &ext->hit_D0[i], 0x04880000, 0, 0x80);
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010E660(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    switch (wp->routine_3)
    {
        case 0:
            if (ext->flags_141 == 0x7F)
            {
                wp->routine_3 = 3;
                break;
            }
            for (ext->value_13F = 0; ext->value_13F < 7; ext->value_13F++)
            {
                if (((ext->flags_140 >> ext->value_13F) & 1) && !((ext->flags_141 >> ext->value_13F) & 1))
                {
                    wp->routine_3 = 1;
                    break;
                }
            }
            break;
        case 1:
            if (!(Moji_flag & 0x800000))
            {
                MojiTaskExec2(4, D_8011BED0[ext->value_13F]);
                ext->flags_141 |= 1 << ext->value_13F;
                wp->routine_3 = 2;
            }
            else if ((ext->flags_141 >> ext->value_13F) & 1)
            {
                func_80053AA4(4);
                Cd_subcmd(0, 1, 0);
                wp->routine_3 = 0;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x800000))
            {
                wp->routine_3 = 0;
            }
            break;
    }
}

void func_8010E7F8(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint16 step;

    if (ext->timer_18 < 0x1BC)
    {
        switch (ext->timer_18)
        {
            case 0:
                wp->value_50 = 1;
                break;
            case 0xAC:
                step = -1;
                if (wp->routine_1 == 2)
                {
                    step = 1;
                }
                wp->value_4C.half[0] = step;
                break;
            case 0xBC:
                wp->value_4C.half[0] = 0;
                break;
            case 0x120:
                wp->value_4C.half[1] = -1;
                wp->value_50         = -1;
                break;
            case 0x130:
                wp->value_4C.half[1] = 0;
                // fall through
            case 0x10:
                wp->value_50 = 0;
                break;
            case 0x1AC:
                step = 1;
                if (wp->routine_1 == 2)
                {
                    step = -1;
                }
                wp->value_4C.half[0] = step;
                wp->value_4C.half[1] = 1;
                break;
        }
        ext->timer_18++;
    }
    else
    {
        ext->timer_18 = 0;
        ext->flags_14 |= 5;
        wp->value_4C.half[0] = 0;
        wp->value_4C.half[1] = 0;
        wp->value_50         = 0;
    }
}

void func_8010E924(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint16 step;

    if (ext->timer_18 < 0x1BC)
    {
        switch (ext->timer_18)
        {
            case 0:
                step = -1;
                if (wp->routine_1 == 6)
                {
                    step = 1;
                }
                wp->value_4C.half[0] = step;
                wp->value_4C.half[1] = 1;
                break;
            case 0x10:
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = 0;
                break;
            case 0x8C:
                wp->value_4C.half[1] = -1;
                wp->value_50         = -1;
                break;
            case 0x9C:
                wp->value_4C.half[1] = 0;
                wp->value_50         = 0;
                break;
            case 0x100:
                step = 1;
                if (wp->routine_1 == 6)
                {
                    step = -1;
                }
                wp->value_4C.half[0] = step;
                break;
            case 0x110:
                wp->value_4C.half[0] = 0;
                break;
            case 0x1AC:
                wp->value_50 = 1;
                break;
        }
        ext->timer_18++;
    }
    else
    {
        ext->timer_18 = 0;
        ext->flags_14 |= 5;
        wp->value_4C.half[0] = 0;
        wp->value_4C.half[1] = 0;
        wp->value_50         = 0;
    }
}

void func_8010EA58(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    if (ext->timer_18 < 0xB0)
    {
        switch (ext->timer_18)
        {
            case 0:
                ext->flags_140 |= 0x20;
                wp->value_4C.half[1] = 1;
                wp->value_50         = 1;
                break;
            case 0x10:
                wp->value_4C.half[1] = 0;
                // fall through
            case 0x30:
                wp->value_50 = 0;
                break;
            case 0x20:
                wp->value_50 = -1;
                break;
            case 0xA0:
                wp->value_4C.half[1] = -1;
                break;
        }
        ext->timer_18++;
    }
    else
    {
        ext->timer_18 = 0;
        ext->flags_14 |= 0x84;
        wp->value_4C.half[1] = 0;
        wp->value_50         = 0;
        wp->routine_2++;
    }
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    if (ext->flags_14 & 4)
    {
        wp->position.x = 0;
        wp->position.y = ext->y_1C = -0x200;
        wp->position.z             = 0x1A00;
        ext->flags_14 &= ~4;
    }
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_8010EBC0(STAGE_OBJ *wp, ST17_BOSS *ext, sint16 part, sint32 color)
{
    sint16 i;

    if (part == 12)
    {
        for (i = 0; i < 12; i++)
        {
            if (wp->life_6E > 0 && i < 4)
            {
                if (i > 0)
                {
                    if (ext->life_A0[i - 1] > 0)
                    {
                        wp->pal[i].color = color;
                    }
                    else if (ext->phase_1F < 0x10)
                    {
                        wp->pal[i].color = ext->phase_1F + 0x4210;
                    }
                    else
                    {
                        wp->pal[i].color = 0x422F - ext->phase_1F;
                    }
                    continue;
                }
            }
            wp->pal[i].color = color;
        }
    }
    else if (part == 9)
    {
        for (i = 0; i < 12; i++)
        {
            wp->pal[i].color = color;
        }
    }
    else
    {
        wp->pal[part + 1].color = color;
    }
}

void func_8010ECD4(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    sint32 random;

    random = (ext->random_16 >> 5) & 7;
    switch (wp->routine_1)
    {
        case 7:
            if (ext->count_13D <= ext->count_13E)
            {
                if (random == 0)
                {
                    ext->flags_14 |= 0x21;
                }
                else
                {
                    ext->flags_14 |= 0x11;
                }
            }
            else if (random != 0)
            {
                ext->flags_14 |= 0x21;
            }
            else
            {
                ext->flags_14 |= 0x11;
            }
            break;
        case 8:
            if (ext->count_13C <= ext->count_13E)
            {
                if (random == 0)
                {
                    ext->flags_14 |= 0x21;
                }
                else
                {
                    ext->flags_14 |= 9;
                }
            }
            else if (random == 0)
            {
                ext->flags_14 |= 9;
            }
            else
            {
                ext->flags_14 |= 0x21;
            }
            break;
        case 9:
            if (ext->count_13C <= ext->count_13D)
            {
                if (random != 0)
                {
                    ext->flags_14 |= 9;
                }
                else
                {
                    ext->flags_14 |= 0x11;
                }
            }
            else if (random == 0)
            {
                ext->flags_14 |= 9;
            }
            else
            {
                ext->flags_14 |= 0x11;
            }
            break;
    }
}

void func_8010EE0C(STAGE_OBJ *wp, ST17_BOSS *ext, sint32 index)
{
    ST17_SHOT *shot;
    ST17_MARK *ep;
    sint32 part;

    if (wp->routine_1 == 8)
    {
        part = index + 3;
    }
    else
    {
        part = index + 6;
    }
    if (ext->timer_130[part] == 0xFF)
    {
        shot = Open_SHL_WORK();
        if (shot != NULL)
        {
            shot->flags_0   = 1;
            shot->kind_2    = 7;
            shot->value_4   = 0;
            shot->variant_3 = ext->random_16 & 1;
            if (wp->routine_1 == 8)
            {
                shot->value_C = 0;
            }
            else
            {
                shot->value_C = 1;
            }
            shot->value_D            = (sint16)(ext->random_16 >> 4) % 3;
            shot->value_E            = 1;
            shot->value_F            = ext->value_1E;
            shot->position           = ext->pos_20[part];
            shot->position_fixed.v.x = shot->position.x << 16;
            shot->position_fixed.v.y = shot->position.y << 16;
            shot->position_fixed.v.z = shot->position.z << 16;
            ep                       = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->kind_2    = 0x14;
                ep->value_4   = 0;
                ep->variant_3 = 0;
                ep->x_1C      = shot->position.x;
                ep->y_1E      = shot->position.y;
                ep->z_20      = shot->position.z;
            }
            Sound_call2(0x1A2, &shot->position);
            ext->count_144++;
        }
    }
}

void func_8010EFC8(STAGE_OBJ *wp, ST17_BOSS *ext, sint32 index)
{
    ST17_SHOT *shot;

    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0    = 1;
        shot->kind_2     = 7;
        shot->variant_3  = 2;
        shot->value_C    = index;
        shot->value_D    = (ext->random_16 >> 2) & 1;
        shot->value_E    = 1;
        shot->value_F    = ext->value_1E;
        shot->target_CC  = &STAGE_PL_BYTE(0x3A8);
        shot->position.x = wp->position.x + D_8011BEC0.x + (sint16)(index % 4) * 200;
        shot->position.y = wp->position.y + D_8011BEC0.y;
        shot->position.z = wp->position.z + D_8011BEC0.z;
        Sound_call2(0x1A1, &shot->position);
    }
}

void func_8010F0D8(STAGE_OBJ *wp, ST17_BOSS *ext)
{
    ST17_SHOT *arm;

    ext->arm_4 = NULL;
    ext->arm_8 = NULL;
    arm        = Open_SHL_WORK();
    if (arm != NULL)
    {
        ext->arm_4              = arm;
        arm->flags_0            = 1;
        arm->kind_2             = 2;
        arm->value_4            = 0;
        arm->variant_3          = 0;
        arm->value_D            = 0;
        arm->position.x         = wp->position.x - D_8011BEC8.x;
        arm->position.y         = wp->position.y + D_8011BEC8.y;
        arm->position.z         = wp->position.z + D_8011BEC8.z;
        arm->position_fixed.v.x = arm->position.x << 16;
        arm->position_fixed.v.y = arm->position.y << 16;
        arm->position_fixed.v.z = arm->position.z << 16;
    }
    arm = Open_SHL_WORK();
    if (arm != NULL)
    {
        ext->arm_8              = arm;
        arm->flags_0            = 1;
        arm->kind_2             = 2;
        arm->value_4            = 0;
        arm->variant_3          = 0;
        arm->value_D            = 0;
        arm->position.x         = wp->position.x + D_8011BEC8.x;
        arm->position.y         = wp->position.y + D_8011BEC8.y;
        arm->position.z         = wp->position.z + D_8011BEC8.z;
        arm->position_fixed.v.x = arm->position.x << 16;
        arm->position_fixed.v.y = arm->position.y << 16;
        arm->position_fixed.v.z = arm->position.z << 16;
    }
}

void func_8010F23C(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        func_8002F9EC(wp, 0);
        wp->scale.words[0] = 0x0C000C00;
        wp->scale.words[1] = 0xC00;
        wp->scale.v.pad    = 0x4210;
        wp->value_78       = 0;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
        return;
    }
    if (wp->routine_1 == 1)
    {
        wp->position.z -= 0x18;
        wp->position_fixed.v.x = wp->position.x << 0x10;
    }
    func_80032488(wp);
}

void func_8010F35C(STAGE_OBJ *wp)
{
    ST17_RIG2 *rig;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    rig                     = (ST17_RIG2 *)&wp->ext_3C0[0x40];
    D_8011BED8[wp->routine_0](wp, rig);
    func_8010F600(wp, rig);
}

void func_8010F41C(STAGE_OBJ *wp, ST17_RIG2 *rig)
{
    wp->flags_0 |= 2;
    func_8002F9EC(wp, 0);
    wp->scale.words[0]   = 0x0C000C00;
    wp->scale.words[1]   = 0xC00;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->u_C.b.byte_C     = 0;
    wp->value_44.half[0] = 0;
    wp->value_48.half[0] = 0;
    rig->slot_0          = func_80105A0C(wp, 1, &rig->pos_8[0]);
    rig->slot_4          = func_80105A0C(wp, 1, &rig->pos_8[9]);
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_8010F4D4(STAGE_OBJ *wp)
{
    func_80032488(wp);
    if (STAGE_SCENE_BYTE(9) == 1)
    {
        wp->routine_0++;
    }
}

void func_8010F520(STAGE_OBJ *wp)
{
    sint16 y;

    if (STAGE_SCENE_BYTE(9) == 1 || STAGE_SCENE_BYTE(9) == 3)
    {
        if (wp->u_C.b.byte_C < 0x78)
        {
            wp->rotation.x++;
            wp->u_C.b.byte_C++;
        }
        y                      = wp->position.y + 8;
        wp->position.y         = y;
        wp->position_fixed.v.y = y << 16;
    }
    else if (STAGE_SCENE_BYTE(9) == 4)
    {
        wp->u_C.b.byte_C = 0;
        wp->routine_0++;
    }
    func_80032538(wp);
    func_800334C4(wp);
}

void func_8010F5D0(STAGE_OBJ *wp)
{
    func_80032538(wp);
    func_800334C4(wp);
}
