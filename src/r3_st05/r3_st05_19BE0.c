#include "common.h"
#include "st05.h"

void func_80119BE0(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    STCOM_FIXED_VECTOR ofs;
    STCOM_SVECTOR pos;
    sint16 floor;

    if (ctl->flags_0 & 0x60)
    {
        func_80030058(&ofs, wp->rotation.y + 0x80, 0x300, 0, 0);
    }
    else
    {
        func_80030058(&ofs, wp->rotation.y, 0x1800, 0, 0);
    }
    ofs.x += wp->position_fixed.x;
    ofs.z += wp->position_fixed.z;
    func_80030150(&ofs, &pos);
    if (func_80048EA4(&pos, D_80131920, 0, 0xFFFF) >= -0x27F)
    {
        floor = -0x340;
    }
    else
    {
        floor = -0x4C0;
    }
    if (wp->position.y > floor)
    {
        if (ctl->sink_12 < 0x18)
        {
            ctl->sink_12 += 8;
        }
        ctl->rise_14 = 8;
        wp->position.y -= ctl->sink_12;
        if (wp->position.y < floor)
        {
            wp->position.y = floor;
        }
    }
    else if (wp->position.y < floor)
    {
        if (ctl->rise_14 < 0x18)
        {
            ctl->rise_14 += 8;
        }
        ctl->sink_12 = 8;
        wp->position.y += ctl->rise_14;
        if (wp->position.y > floor)
        {
            wp->position.y = floor;
        }
    }
    else
    {
        ctl->rise_14 = 8;
        ctl->sink_12 = 8;
    }
    wp->position_fixed.y = wp->position.y << 16;
}

sint32 func_80119D90(ST05_BOAT *wp)
{
    if (STCOM_ABS(wp->rotation.y - Angle_xz_vector(&wp->position_fixed, &Player_work.position_fixed)) < 0x50)
    {
        return 1;
    }
    return 0;
}

void func_80119E3C(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    if (Sce_flag_test(0x610) == 0)
    {
        wp->position.y = ((D_800BBCF8[ctl->timer_4 & 0x3F] * 3) >> 9) - 0x400;
        ctl->timer_4++;
    }
    else
    {
        wp->position.y = -0x400;
        ctl->timer_4   = 0;
        ctl->flags_0 |= 1;
    }
    wp->position_fixed.y = wp->position.y << 16;
}

void func_80119EE8(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    STCOM_PL_WORK *pl;
    sint32 track;

    pl = &Player_work;
    if (wp->routine_2 == 0)
    {
        ctl->timer_4 = (sint16)ctl->random_2 % 40 + 0x5A;
        wp->routine_2++;
    }
    if (ctl->flags_0 & 8)
    {
        track = func_8003648C(ctl->track_28, wp);
        Obj_pos_set(wp, 0x200, 0, 0);
        if (!(ctl->flags_0 & 0x10))
        {
            if (track != 0)
            {
                ctl->flags_0 |= 0x80;
            }
            else if (ctl->timer_4 < 0)
            {
                ctl->flags_0 &= ~0x80;
                if ((sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) > 0)
                {
                    ctl->flags_0 |= 0x41;
                }
                else
                {
                    ctl->flags_0 |= 0x21;
                }
            }
        }
        if (!(ctl->flags_0 & 0x80))
        {
            ctl->timer_4--;
        }
    }
    else
    {
        Track_stop(ctl->track_28);
        Obj_pos_set(wp, 0xC0, 0, 0);
        ctl->flags_0 &= ~0x80;
        if (ctl->random_2 & 1)
        {
            ctl->flags_0 |= 0x41;
        }
        else
        {
            ctl->flags_0 |= 0x21;
        }
    }
}

void func_8011A094(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    if (wp->routine_2 == 0)
    {
        ctl->timer_4 = (ctl->random_2 & 0x1F) + 0x40;
        wp->routine_2++;
    }
    Obj_pos_set(wp, 0xC0, 0, 0);
    if (ctl->flags_0 & 8)
    {
        func_8003648C(ctl->track_28, wp);
        if (func_80119D90(wp) != 0 || ctl->timer_4 == 0)
        {
            ctl->flags_0 = (ctl->flags_0 & ~0x60) | 1;
        }
    }
    else
    {
        Track_stop(ctl->track_28);
        if (ctl->timer_4 == 0)
        {
            ctl->timer_6 = 0x20;
            ctl->flags_0 = (ctl->flags_0 & ~0x60) | 0x19;
        }
    }
    ctl->timer_4--;
}

void func_8011A194(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR pos;
    STCOM_EFFECT *fx;
    STAGE_OBJ *piece;

    switch (wp->routine_2)
    {
        case 0:
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 5;
                fx->kind_2          = 0x80;
                fx->variant_3       = 0x41;
                fx->sprite.position = wp->position;
            }
            Sound_call2(0xA1, &wp->position);
            ctl->timer_4 = 0x78;
            ctl->rise_16 = 8;
            ctl->count_A = 0;
            ctl->flags_0 |= 4;
            func_80030058(&vec, wp->rotation.y, 0x3C00, 0, 0);
            vec.x += wp->position_fixed.x;
            vec.z += wp->position_fixed.z;
            func_80030150(&vec, &pos);
            wp->routine_2 = (func_8011953C(pos.x, pos.z, ((wp->rotation.y + 0x200) & 0xFFF) / 0x400) != 0) ? 1 : 2;
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
            Obj_pos_set(wp, 0xC0, 0, 0);
            func_80030058(&vec, wp->rotation.y, 0x3C00, 0, 0);
            vec.x += wp->position_fixed.x;
            vec.z += wp->position_fixed.z;
            func_80030150(&vec, &pos);
            if (func_8011953C(pos.x, pos.z, ((wp->rotation.y + 0x200) & 0xFFF) / 0x400) == 0)
            {
                ctl->timer_4 = 0x78;
                ctl->flags_0 |= 8;
                wp->routine_2++;
            }
            else if (ctl->timer_4 <= 0)
            {
                ctl->timer_4  = 0;
                wp->routine_2 = 4;
            }
            else
            {
                ctl->timer_4--;
            }
            break;
        case 2:
            Obj_pos_set(wp, 0x100, 0, 0);
            func_80030058(&vec, wp->rotation.y, 0x3C00, 0, 0);
            vec.x += wp->position_fixed.x;
            vec.z += wp->position_fixed.z;
            func_80030150(&vec, &pos);
            if (func_8011953C(pos.x, pos.z, ((wp->rotation.y + 0x200) & 0xFFF) / 0x400) == 0)
            {
                if (func_80048EA4(&pos, D_80131920, 0, 0xFFFF) >= -0x27F)
                {
                    ctl->count_A = 0;
                    ctl->flags_0 |= 0x400;
                    wp->routine_2++;
                    break;
                }
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
                Obj_pos_set(wp, 0xC0, 0, 0);
            }
            if (ctl->timer_4 <= 0)
            {
                ctl->timer_4  = 0;
                wp->routine_2 = 4;
            }
            else
            {
                ctl->timer_4--;
            }
            break;
        case 3:
            if (ctl->count_A == 0xA)
            {
                ctl->rise_16 = 8;
            }
            if (ctl->count_A == 0x1E)
            {
                ctl->rise_16 = 0xC;
            }
            else if (ctl->count_A == 0x32)
            {
                ctl->rise_16 = 0x10;
            }
            if (ctl->count_A < 0x3C)
            {
                Obj_pos_set(wp, 0x100, 0, 0);
            }
            wp->position.y += ctl->rise_16;
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y >= -0xBF || (ctl->hit_18 & 0x1000) || ctl->ground_1C == 1)
            {
                ctl->timer_4 = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->position.y += ctl->rise_16;
            wp->position_fixed.y = wp->position.y << 16;
            if (ctl->timer_4 == 4)
            {
                wp->flags_0 &= ~2;
                piece = func_80031418();
                if (piece != NULL)
                {
                    piece->flags_0               = 1;
                    piece->kind_2                = 0;
                    piece->value_4               = 1;
                    piece->variant_3             = 1;
                    *(uint32 *)&piece->routine_0 = 0;
                    *(uint32 *)&piece->u_C       = 0;
                    piece->position              = wp->position;
                    piece->position_fixed.v.y -= 0xC8;
                    piece->position_fixed.v.x = piece->position.x << 16;
                    piece->position_fixed.v.y = piece->position.y << 16;
                    piece->position_fixed.v.z = piece->position.z << 16;
                    piece->rotation           = wp->rotation;
                    Obj_pos_set(piece, -0x300, -0x400, 0);
                }
                func_80047148(wp, &wp->position);
            }
            if (!(ctl->timer_4 & 3))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 0x42;
                    fx->sprite.position.x = wp->position.x + (rand() & 0x3F);
                    fx->sprite.position.y = wp->position.y + (rand() & 0x3F);
                    fx->sprite.position.z = wp->position.z + (rand() & 0x3F);
                }
                Sound_call2(0xA1, &fx->sprite.position);
            }
            if (ctl->timer_4 == 9)
            {
                wp->routine_2++;
            }
            else
            {
                ctl->timer_4++;
            }
            break;
        case 5:
            ctl->flags_0 |= 1;
            break;
    }
    if (wp->routine_2 < 4)
    {
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0         = 1;
            fx->kind_2          = 0xB;
            fx->variant_3       = 3;
            fx->timer_E         = 0x14;
            fx->value_C         = 0;
            fx->value_D         = 0;
            fx->value_F         = 8;
            fx->sprite.pos_8[0] = wp->position.x;
            fx->sprite.pos_8[1] = wp->position.y;
            fx->sprite.pos_8[2] = wp->position.z;
            fx->routine_1       = ctl->random_2 & 0xF;
        }
    }
    ctl->count_A++;
}

void func_8011A7C8(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8011A7E8(ST05_ACTOR *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    D_80131974[wp->routine_0](wp);
    if (wp->routine_1 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_8011A87C(ST05_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->data_78               = NULL;
    wp->data_10               = NULL;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->position_fixed.x      = wp->position.x << 16;
    wp->position_fixed.y      = wp->position.y << 16;
    wp->position_fixed.z      = wp->position.z << 16;
    wp->scale.v.pad           = 0x4210;
    wp->position_fixed_prev.x = wp->position_fixed.x;
    wp->position_fixed_prev.y = wp->position_fixed.y;
    wp->position_fixed_prev.z = wp->position_fixed.z;
    wp->position_prev.x       = wp->position.x;
    wp->position_prev.y       = wp->position.y;
    wp->position_prev.z       = wp->position.z;
    wp->rotation_prev.x       = wp->rotation.x;
    wp->rotation_prev.y       = wp->rotation.y;
    wp->rotation_prev.z       = wp->rotation.z;
    wp->velocity.v.z          = 0;
    wp->accel_4C.x            = 0;
    wp->accel_4C.y            = 0;
    wp->accel_4C.z            = 0;
    wp->routine_1             = 0;
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_8011A988(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->u_E.b.byte_E, 0);
        wp->u_C.b.byte_D = 0;
    }
}

void func_8011A9EC(ST05_BOSS *wp)
{
    STCOM_PL_WORK *pl;
    ST05_BOSS_CTL *ctl;
    STCOM_SVECTOR pos;
    sint16 i;

    pl                      = &Player_work;
    ctl                     = &wp->ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    for (i = 0; i < 14; i++)
    {
        wp->joint_180[i].pad = 0x4210;
    }
    ctl->random_2 = rand();
    ctl->dist_E0  = SquareRoot0(wp->value_80);
    D_80131988[wp->routine_0](wp);
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else if (ctl->flags_0 & 0x10)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_AC, wp->value_A4);
    }
    if (ctl->flags_0 & 8)
    {
        func_8011D830(wp);
    }
    for (i = 0; i < 16; i++)
    {
        if ((pl->position.x >> 9) >= D_801319D4[i][0] && (pl->position.x >> 9) < D_801319D4[i][2] &&
            (pl->position.z >> 9) >= D_801319D4[i][1] && (pl->position.z >> 9) < D_801319D4[i][3])
        {
            break;
        }
    }
    ctl->value_EC = i;
    for (i = 0; i < 4; i++)
    {
        if ((wp->position.x >> 9) >= D_801319D4[i][0] && (wp->position.x >> 9) < D_801319D4[i][2] &&
            (wp->position.z >> 9) >= D_801319D4[i][1] && (wp->position.z >> 9) < D_801319D4[i][3])
        {
            break;
        }
    }
    if (i == 4)
    {
        i = 3;
    }
    ctl->value_ED = i;
    if (ctl->flags_0 & 0x100)
    {
        pos = wp->joint_180[0];
        pos.y += 0x1E0;
        Pos_Shadow_Trans(&pos, 0x12C, 0x200, 0);
    }
    if (ctl->flags_0 & 0x80)
    {
        for (i = 3; i < 13; i += 3)
        {
            pos = wp->joint_180[i];
            pos.y += 0xA0;
            Pos_Shadow_Trans(&pos, 0xC8, 0x155, wp->rotation.y);
        }
    }
}

void func_8011ADB4(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint16 i;

    wp->flags_0 |= 2;
    ctl            = &wp->ctl;
    wp->rotation.x = 0;
    if (wp->variant_3 == 0)
    {
        wp->rotation.y = (wp->u_C.b.byte_C << 9) & 0xE00;
    }
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->u_C.b.byte_C &= 0xF0;
    if (wp->variant_3 == 1)
    {
        func_8002F9EC(wp, 0);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0]       = 0x4000400;
    wp->scale.words[1]       = 0x400;
    ctl->flags_0             = 0x19E;
    *(sint32 *)&ctl->timer_4 = 0;
    *(sint32 *)&ctl->value_8 = 0;
    for (i = 0; i < 9; i++)
    {
        ctl->hit_10[i].hit_0   = 0;
        ctl->hit_10[i].value_4 = 0;
    }
    Track_reset(ctl->track_A0, 0xA, -0x1F4);
    wp->value_B2 = wp->value_B0 = wp->value_6E = D_8009884C[wp->kind_2]->life_8 << 6;
    wp->value_78                               = (sint32)D_801319C8;
    switch (wp->variant_3)
    {
        case 0:
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            break;
        case 1:
            wp->routine_0             = 3;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            break;
        case 2:
            wp->routine_0             = 3;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
    func_800322A8(wp, 0, 0);
    for (i = 0; i < 14; i++)
    {
        wp->joint_180[i].pad = 0x4210;
    }
    wp->scale.v.pad = 0;
    ctl->value_ED   = 1;
    ctl->value_EE   = 1;
    ctl->value_EB   = 0;
    ctl->value_EA   = 0;
    ctl->timer_4    = 0xF;
}

void func_8011AFA0(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint32 i;

    if (wp->ctl.dist_E0 < 0x1801)
    {
        func_8005D4C0();
    }
    if (wp->ctl.flags_0 & 2)
    {
        func_8011DA0C(wp);
    }
    D_80131998[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        func_8011D1E0(wp);
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
    if (wp->ctl.timer_A != 0)
    {
        wp->ctl.timer_A--;
    }
    func_80051B68(wp, 1, 0, 0x1000008);
    ctl = &wp->ctl;
    for (i = 8; i >= 0; i--)
    {
        ctl->hit_10[i].hit_0 = 0;
    }
}

void func_8011B094(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_8011B0B4(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint16 i;

    ctl = &wp->ctl;
    switch (wp->routine_1)
    {
        case 0:
            break;
        case 1:
            wp->anim_AC = 0x10;
            if (wp->value_A4 == 4)
            {
                ctl->timer_4 = 0x78;
                ctl->flags_0 &= ~0x10;
                wp->routine_1++;
            }
            break;
        case 2:
            if (ctl->timer_4 & 1)
            {
                func_8011CF8C(wp);
            }
            if (--ctl->timer_4 == 2)
            {
                ctl->flags_0 |= 0x10;
            }
            if (ctl->timer_4 == 0)
            {
                wp->value_44.half[1] = -0x1000;
                wp->routine_1++;
            }
            wp->rotation.y = (wp->rotation.y + 6) & 0xFFF;
            break;
        case 3:
            wp->anim_AC = 0x11;
            wp->value_44.half[1] += 0x80;
            Obj_pos_set(wp, 0, wp->value_44.half[1], 0);
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->routine_2 != 0)
            {
                for (i = 0; i < 14; i++)
                {
                    wp->joint_180[i].pad = 0x2108;
                }
            }
            break;
        case 4:
            ctl->flags_0           = (ctl->flags_0 & ~0x180) | 0x10;
            wp->position.x         = 0x800;
            wp->position.y         = -1;
            wp->position.z         = 0x2A00;
            wp->value_44.half[1]   = -0x1400;
            wp->anim_prev_AD       = 0;
            wp->rotation.y         = 0;
            wp->routine_1          = 3;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            break;
        case 5:
            ctl->flags_0 |= 0x180;
            wp->position.x         = 0x400;
            wp->position.y         = -0x2800;
            wp->position.z         = 0x2100;
            wp->anim_prev_AD       = 0;
            wp->value_44.half[1]   = 0;
            wp->routine_1          = 3;
            wp->routine_2          = 1;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            for (i = 0; i < 14; i++)
            {
                wp->joint_180[i].pad = 0x2108;
            }
            break;
        case 6:
            wp->value_44.half[1] += 0x80;
            Obj_pos_set(wp, 0, wp->value_44.half[1], 0);
            if (wp->position.y >= 0)
            {
                wp->position.y       = -1;
                wp->value_48.half[0] = 0;
                wp->value_44.half[1] = 0;
                wp->value_44.half[0] = 0;
                wp->anim_AC          = 0x13;
                wp->routine_1        = 0;
                func_8011CF8C(wp);
            }
            wp->position_fixed.v.y = wp->position.y << 16;
            break;
        case 7:
            ctl->flags_0 &= ~0x180;
            wp->routine_1 = 0;
            break;
    }
}

void func_8011B3CC(ST05_BOSS *wp)
{
    sint16 temp_v0;

    temp_v0 = wp->ctl.timer_4;
    if (temp_v0 != 0)
    {
        wp->ctl.timer_4 = temp_v0 - 1;
        return;
    }
    wp->routine_1 = 1;
}

void func_8011B3FC(ST05_BOSS *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (--wp->ctl.timer_4 <= 0)
            {
                wp->anim_AC = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            wp->routine_2++;
            wp->ctl.timer_4 = 0x96;
            wp->ctl.value_8 = 0;
            break;
        case 2:
            if (wp->ctl.flags_0 & 0x200)
            {
                if (wp->ctl.value_ED != 1)
                {
                    wp->ctl.value_EE = 1;
                    wp->ctl.flags_0 |= 1;
                    break;
                }
            }
            else if (func_8011D580(wp))
            {
                wp->ctl.flags_0 |= 1;
                break;
            }
            else if (--wp->ctl.timer_4 <= 0)
            {
                wp->ctl.value_EE = 1;
                wp->ctl.flags_0 |= 1;
                break;
            }
            func_8011D6F8(wp);
            break;
    }
}

void func_8011B52C(void)
{
}

void func_8011B534(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    STCOM_PL_WORK *pl;
    sint32 side;
    uint16 angle;
    sint16 diff;
    uint16 rot;
    uint16 turn;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC = 2;
                break;
            case 1:
                wp->anim_AC = 3;
                Sound_call2(0xCB, &wp->position);
                break;
            case 3:
                wp->anim_AC = 4;
                break;
        }
        return;
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->rotation.y = (wp->ctl.timer_4 * wp->ctl.target_C0.pad + (14 - wp->ctl.timer_4) * wp->ctl.home_B8.pad) / 14;
            wp->ctl.timer_4++;
            if (wp->value_A7 == -1)
            {
                wp->routine_2++;
                wp->routine_3   = 0;
                wp->rotation.y  = wp->ctl.target_C0.pad;
                wp->ctl.timer_4 = D_80131A14[wp->ctl.value_EE].pad + D_80131A14[wp->ctl.value_ED].pad;
            }
            break;
        case 1:
            if (wp->ctl.timer_4 & 1)
            {
                func_8011CF8C(wp);
            }
            wp->value_44.half[0] = 0x400;
            Obj_pos_set(wp, 0x400, 0, 0);
            if (--wp->ctl.timer_4 == 0)
            {
                wp->value_44.half[0] = 0;
                wp->position         = D_80131A14[wp->ctl.value_EE];
                Player_work.value_C4 = pl->position;
                wp->value_C4         = wp->position;
                wp->ctl.size_C8.x    = 2;
                wp->ctl.size_C8.y    = 9;
                wp->ctl.size_C8.z    = 4;
                side                 = func_80030418(wp, pl, &wp->ctl.size_C8, &wp->ctl.out_D0);
                angle                = (Angle_xz_svector(&wp->position, &pl->position) + 0x1000) & 0xFFF;
                if (side & 1)
                {
                    // The two one-pass loops order the rotation load first and give it
                    // retail's register (loop depth weights its references).
                    wp->ctl.value_EF = -1;
                    do
                    {
                        rot = wp->rotation.y;
                    } while (0);
                    turn = angle - 0x1000;
                    do
                    {
                        diff = rot - turn;
                    } while (0);
                }
                else
                {
                    wp->ctl.value_EF = 1;
                    diff             = angle - ((uint16)wp->rotation.y - 0x1000);
                }
                ctl->timer_4 = (diff & 0xFFF) / 64;
                wp->routine_2++;
            }
            break;
        case 2:
            if (wp->ctl.timer_4 & 1)
            {
                func_8011CF8C(wp);
            }
            wp->rotation.y = (wp->rotation.y + wp->ctl.value_EF * 64) & 0xFFF;
            if (--wp->ctl.timer_4 <= 0)
            {
                wp->routine_3 = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
    }
}

void func_8011B8F0(void)
{
}

void func_8011B8F8(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint16 steps;
    sint16 from;
    sint16 to;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC = 0x10;
                break;
            case 1:
                wp->anim_AC = 0x11;
                Sound_call2(0xC9, &wp->position);
                break;
            case 2:
                wp->anim_AC = 0x12;
                break;
        }
    }
    else
    {
        switch (wp->routine_2)
        {
            case 0:
                if (wp->value_A7 == -1)
                {
                    wp->routine_2++;
                    wp->routine_3 = 0;
                    wp->jump_74   = 1;
                    if (wp->ctl.value_E8 == 0)
                    {
                        wp->value_44.half[1] = -0x700;
                    }
                    else
                    {
                        wp->value_44.half[1] = -0xE00;
                    }
                    ctl->timer_4 = 0;
                }
                break;
            case 1:
                if (wp->value_A7 == -1)
                {
                    wp->routine_2++;
                    wp->routine_3 = 0;
                }
                break;
            case 3:
                if (wp->value_A7 == -1)
                {
                    wp->ctl.flags_0 |= 1;
                }
                break;
        }
    }
    if (wp->jump_74 != 0)
    {
        if (ctl->value_E8 == 0)
        {
            steps = 0x1C;
        }
        else
        {
            steps = 0x38;
        }
        wp->value_44.half[1] += 0x80;
        Obj_pos_set(wp, 0, wp->value_44.half[1], 0);
        wp->position.x = (ctl->timer_4 * ctl->target_C0.x + (steps - ctl->timer_4) * ctl->home_B8.x) / steps;
        wp->position.z = (ctl->timer_4 * ctl->target_C0.z + (steps - ctl->timer_4) * ctl->home_B8.z) / steps;
        from           = ctl->home_B8.pad;
        to             = ctl->target_C0.pad;
        if (to - ctl->home_B8.pad >= 0x800)
        {
            from += 0x1000;
        }
        else if (ctl->home_B8.pad - to >= 0x800)
        {
            to += 0x1000;
        }
        wp->rotation.y = (ctl->timer_4 * to + (steps - ctl->timer_4) * from) / steps;
        ctl->timer_4++;
        if (wp->position.y >= 0)
        {
            wp->position         = ctl->target_C0;
            wp->position.pad     = 0;
            wp->rotation.y       = ctl->target_C0.pad;
            ctl->home_B8         = ctl->target_C0;
            wp->routine_2        = 3;
            wp->value_48.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_44.half[0] = 0;
            wp->jump_74          = 0;
            wp->anim_AC          = 0x13;
            Sound_call2(0xCA, &wp->position);
            func_8011CF8C(wp);
            Swing_Camera2(0x1E, 0x400, 0x2800, &wp->position);
        }
        wp->position_fixed.v.x = wp->position.x << 16;
        wp->position_fixed.v.y = wp->position.y << 16;
        wp->position_fixed.v.z = wp->position.z << 16;
    }
}

void func_8011BCF4(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC = 0x40;
                break;
            case 0xFF:
                wp->anim_AC = 0x42;
                break;
            default:
                wp->anim_AC = 0x41;
                break;
        }
    }
    else
    {
        switch (wp->routine_2)
        {
            case 0:
                if (wp->value_A7 == -1)
                {
                    wp->routine_2++;
                    wp->routine_3 = 0;
                    if (wp->ctl.random_2 & 1)
                    {
                        if (wp->ctl.value_EA != 3 && !(wp->ctl.flags_0 & 0x400))
                        {
                            wp->ctl.value_E8 = 0;
                            wp->ctl.value_E9 = 8;
                        }
                        else
                        {
                            ctl->value_E8 = 2;
                            ctl->value_E9 = 0x20;
                        }
                        ctl->value_EA = (ctl->value_EA + 1) & 3;
                    }
                    else
                    {
                        if (wp->ctl.value_EB != 3 && !(wp->ctl.flags_0 & 0x400))
                        {
                            wp->ctl.value_E8 = 1;
                            wp->ctl.value_E9 = 4;
                        }
                        else
                        {
                            ctl->value_E8 = 3;
                            ctl->value_E9 = 8;
                        }
                        ctl->value_EB = (ctl->value_EB + 1) & 3;
                    }
                }
                break;
            case 0xFF:
                if (wp->value_A7 == -1)
                {
                    wp->ctl.flags_0 |= 1;
                }
                break;
            default:
                if (ctl->value_E8 == 2 || wp->value_A7 == -1)
                {
                    ctl->value_E6 = 0;
                    func_8011C9B0(wp);
                    if (wp->routine_2 < ctl->value_E9)
                    {
                        wp->routine_2++;
                    }
                    else
                    {
                        wp->routine_2 = 0xFF;
                    }
                    wp->routine_3    = 0;
                    wp->anim_prev_AD = 0xFF;
                }
                break;
        }
    }
    func_8011D0E8(wp, 2, !(ctl->flags_0 & 0x400) ? 8 : 0x18);
}

void func_8011BF0C(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint32 turn;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC = 8;
                break;
            case 0xFF:
                wp->anim_AC = 0xA;
                break;
            case 1:
                Sound_call2(0xCF, &wp->position);
                // fall through
            default:
                wp->anim_AC = 9;
                break;
        }
    }
    else
    {
        switch (wp->routine_2)
        {
            case 0:
                if (wp->value_A7 == -1)
                {
                    wp->routine_2++;
                    wp->routine_3   = 0;
                    wp->ctl.timer_4 = 0;
                    wp->ctl.flags_0 |= 0x40;
                }
                break;
            case 0xFF:
                if (wp->value_A7 == -1)
                {
                    wp->ctl.flags_0 |= 1;
                }
                break;
            default:
                wp->routine_2++;
                if (!(++ctl->timer_4 & 1))
                {
                    func_8011CC64(wp);
                    if (!(ctl->flags_0 & 0x40))
                    {
                        wp->routine_2 = 0xFF;
                        wp->routine_3 = 0;
                    }
                }
                break;
        }
    }
    turn = 6;
    if (!(ctl->flags_0 & 0x400))
    {
        turn = 2;
    }
    func_8011D0E8(wp, 2, turn);
}

void func_8011C09C(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint32 turn;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        wp->anim_AC   = 0x43;
    }
    else
    {
        switch (wp->routine_2)
        {
            case 0:
                if (wp->value_A4 == 0x10)
                {
                    wp->routine_2++;
                    wp->ctl.timer_4 = 0;
                }
                break;
            case 1:
                if (!(++wp->ctl.timer_4 & 3))
                {
                    func_8011CE1C(wp);
                }
                if (wp->ctl.timer_4 >= 0x3D)
                {
                    wp->ctl.flags_0 |= 1;
                }
                break;
        }
    }
    turn = 0x10;
    if (!(ctl->flags_0 & 0x400))
    {
        turn = 4;
    }
    func_8011D0E8(wp, 2, turn);
}

void func_8011C198(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC = 2;
                break;
            case 1:
                wp->anim_AC = 3;
                Sound_call2(0xCC, &wp->position);
                break;
            case 3:
                wp->anim_AC = 4;
                break;
        }
        return;
    }
    switch (wp->routine_2)
    {
        case 0:
            if (wp->value_A7 == -1)
            {
                ctl->value_EE = ctl->value_ED;
                if (!(ctl->flags_0 & 0x400))
                {
                    ctl->timer_4  = 0x3C;
                    ctl->value_E9 = ctl->random_2 & 3;
                }
                else
                {
                    ctl->timer_4  = 0x78;
                    ctl->value_E9 = 0;
                }
                wp->value_52  = 0;
                wp->routine_2 = 1;
                wp->routine_3 = 0;
            }
            break;
        case 1:
            if (ctl->timer_4 & 1)
            {
                func_8011CF8C(wp);
            }
            if (--ctl->timer_4 == 0)
            {
                wp->routine_2 = 2;
                ctl->value_E8 = ctl->random_2 & 1;
                if (ctl->value_E8 != 0)
                {
                    ctl->timer_4 = 0x70;
                }
                else
                {
                    ctl->timer_4 = 0x90;
                }
            }
            if ((func_8011D0E8(wp, 2, !(ctl->flags_0 & 0x400) ? 8 : 0x10) & 2) && ctl->value_E9 == 0)
            {
                ctl->timer_4  = 0x40;
                ctl->value_E8 = 0;
                wp->routine_2 = 4;
            }
            break;
        case 2:
            if (ctl->timer_4 & 1)
            {
                func_8011CF8C(wp);
            }
            if (ctl->timer_4 % 10 == 0)
            {
                Sound_call2(0xCD, &wp->position);
            }
            if (ctl->timer_4-- == 0)
            {
                wp->value_44.half[0] = 0;
                wp->value_52         = 0;
                wp->routine_2        = 3;
                wp->routine_3        = 0;
                break;
            }
            if (ctl->value_E8 != 0)
            {
                if (wp->value_52 < 0x80)
                {
                    wp->value_52 += 4;
                }
                else
                {
                    if (!(ctl->flags_0 & 0x200))
                    {
                        wp->value_44.half[0] = ctl->random_2 & 0x3FF;
                    }
                    else
                    {
                        wp->value_44.half[0] = 0;
                    }
                    if (ctl->timer_4 >= 0x30 && ctl->dist_E0 >= 0x300)
                    {
                        ctl->value_E6 = 5;
                        func_8011C9B0(wp);
                    }
                }
            }
            else
            {
                if (wp->value_52 < 0x40)
                {
                    wp->value_52 += 2;
                }
                else
                {
                    if (!(ctl->flags_0 & 0x200))
                    {
                        wp->value_44.half[0] = ctl->random_2 & 0x1FF;
                    }
                    else
                    {
                        wp->value_44.half[0] = 0;
                    }
                    if (ctl->timer_4 >= 0x30 && ctl->timer_4 <= 0x50 && ctl->dist_E0 >= 0x300)
                    {
                        func_8011C9B0(wp);
                    }
                }
            }
            wp->rotation.y = (wp->rotation.y + wp->value_52) & 0xFFF;
            Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            break;
        case 3:
            if (wp->value_A7 == -1)
            {
                ctl->flags_0 |= 1;
            }
            break;
        case 4:
            if (ctl->timer_4 & 1)
            {
                func_8011CF8C(wp);
            }
            func_8011D0E8(wp, 2, !(ctl->flags_0 & 0x400) ? 0x10 : 0x20);
            if (ctl->timer_4-- != 0)
            {
                if ((ctl->timer_4 & 3) == 0)
                {
                    func_8011C9B0(wp);
                }
            }
            else
            {
                wp->value_44.half[0] = 0;
                wp->value_52         = 0;
                wp->routine_2        = 3;
                wp->routine_3        = 0;
            }
            break;
    }
}

void func_8011C5D8(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2        = 1;
            wp->anim_AC          = 0x20;
            wp->value_44.half[0] = 0;
            wp->ctl.timer_4      = 0x1C;
            wp->ctl.value_8      = 0;
            wp->ctl.flags_0 &= ~4;
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 5;
            }
            Obj_pos_set(wp, wp->value_44.half[0] * 8, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y         = Obj_ceiling_height_get(wp);
            wp->position_fixed.v.y = wp->position.y << 16;
            if (((wp->position.y - wp->position_prev.y >= 0) ? wp->position.y - wp->position_prev.y
                                                             : wp->position_prev.y - wp->position.y) > 0x20)
            {
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
            }
            break;
    }
}

void func_8011C720(ST05_BOSS *wp)
{
    STCOM_SVECTOR pos;
    STCOM_EFFECT *fx;
    uint8 joint;

    if (Player_work.value_6E >= 0)
    {
        Sce_flag_on(0x660);
        Sound_seq_stop_all();
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->position           = D_80131A14[1];
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            wp->routine_2++;
            break;
        case 1:
            wp->anim_AC = 0x20;
            if (!(wp->routine_3 & 3))
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0                = 7;
                    fx->kind_2                 = 0x80;
                    fx->variant_3              = 2;
                    joint                      = D_80131A4C[wp->routine_3 >> 2];
                    pos                        = wp->joint_180[joint];
                    fx->sprite.position        = pos;
                    wp->part_F8[joint].value_1 = -1;
                }
            }
            if (++wp->routine_3 >= 0x30)
            {
                wp->routine_3        = 0;
                wp->value_44.half[1] = 0;
                wp->routine_2++;
            }
            break;
        case 2:
            wp->value_44.half[1] += 0x80;
            Obj_pos_set(wp, 0, wp->value_44.half[1], 0);
            if (wp->joint_180[0].y >= -0x64)
            {
                wp->routine_2++;
            }
            break;
        case 3:
            pos   = wp->position;
            pos.y = -1;
            fx    = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 7;
                fx->kind_2          = 0x80;
                fx->variant_3       = 0x24;
                fx->sprite.position = pos;
            }
            wp->routine_0             = 2;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_80052528(wp);
            break;
    }
}

void func_8011C9B0(ST05_BOSS *wp)
{
    ST05_SPRAY *shot;
    ST05_BOSS_CTL *ctl;
    ST05_PL_VIEW *pl;
    sint16 spread;
    sint32 angle;
    sint32 c;
    sint32 s;

    ctl  = &wp->ctl;
    pl   = &ST05_PL;
    shot = (ST05_SPRAY *)Open_SHL_WORK();
    if (shot == NULL)
    {
        return;
    }
    shot->flags_0 = 3;
    shot->kind_2  = 1;
    shot->value_4 = 0;
    shot->type_F  = wp->ctl.value_E8 & 1;
    if (shot->type_F == 0)
    {
        if (!(wp->ctl.value_E8 & 2))
        {
            spread = (wp->ctl.random_2 & 0x1F) - 0x10;
        }
        else
        {
            spread = (wp->ctl.random_2 & 0x7F) - 0x40;
        }
    }
    else
    {
        spread = 0;
    }
    angle          = spread + 0x800;
    c              = rcos(wp->rotation.y + angle);
    s              = rsin(wp->rotation.y + angle);
    wp->value_C4.x = wp->position.x + ((uint32)(s * ctl->dist_E0) >> 12);
    if (shot->type_F == 1)
    {
        wp->value_C4.y = pl->joint_3A8[0].y + 0x50;
    }
    else
    {
        wp->value_C4.y = pl->joint_3A8[0].y;
    }
    wp->value_C4.z = wp->position.z + ((uint32)(c * ctl->dist_E0) >> 12);
    if (shot->type_F == 1)
    {
        shot->position_fixed.x = wp->joint_180[0].x + ((s * 3) >> 5);
        shot->position_fixed.y = wp->joint_180[0].y - 0x3C;
        shot->position_fixed.z = wp->joint_180[0].z + ((c * 3) >> 5);
    }
    else
    {
        shot->position_fixed.x = wp->joint_180[0].x + (s >> 4);
        shot->position_fixed.y = wp->joint_180[0].y + 0x100;
        shot->position_fixed.z = wp->joint_180[0].z + (c >> 4);
    }
    shot->position_fixed.x <<= 16;
    shot->position_fixed.y <<= 16;
    shot->position_fixed.z <<= 16;
    func_80030150(&shot->position_fixed, &shot->position);
    pl->value_C4.x = wp->value_C4.x;
    pl->value_C4.y = wp->value_C4.y;
    pl->value_C4.z = wp->value_C4.z;
    if (shot->type_F != 0)
    {
        func_80030934(shot, pl, (ctl->value_E8 & 2) ? 0x78 : 0x28, ctl->value_E6 << 9);
        Sound_call2(0xCE, &wp->position);
    }
    else
    {
        func_80030EE8(shot, &pl->value_C4, (ctl->value_E8 & 2) ? 0x80 : 0x60);
        Sound_call2(0xE3, &wp->position);
    }
    func_8011D044(shot, ctl->value_E8 & 1);
}

void func_8011CC64(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    STCOM_EFFECT *fx;
    STCOM_SVECTOR pos;
    sint32 work; // the cosine, then the sprite's address (one variable, as in retail)
    sint32 hit;

    work = 0;
    fx   = func_80031618();
    ctl  = &wp->ctl;
    if (fx != NULL)
    {
        fx->flags_0                      = 7;
        fx->kind_2                       = 0x80;
        fx->variant_3                    = 0xFE;
        work                             = rcos(wp->rotation.y + 0x800);
        pos.x                            = wp->position.x + ((rsin(wp->rotation.y + 0x800) * (wp->routine_2 + 4)) >> 6);
        pos.y                            = -1;
        pos.z                            = wp->position.z + ((work * (wp->routine_2 + 4)) >> 6);
        work                             = (sint32)&fx->sprite;
        ((STCOM_SPRITE *)work)->position = pos;
    }
    if (Distance_xyz(&wp->position, &((STCOM_SPRITE *)work)->position) > wp->ctl.dist_E0 + 0x200 && wp->routine_2 >= 0x3D)
    {
        wp->ctl.flags_0 &= ~0x40;
    }
    hit = func_80049C54(&((STCOM_SPRITE *)work)->position, &((STCOM_SPRITE *)work)->position, NULL, 0xFFFF);
    if (hit != 0)
    {
        if ((sint16)func_80037BB4((void *)hit) != 0)
        {
            func_80037738(hit, 0x190);
            ctl->flags_0 &= ~0x40;
        }
        else if (func_80048EA4(&((STCOM_SPRITE *)work)->position, NULL, 0, fx->reserved01) < -0x80)
        {
            ctl->flags_0 &= ~0x40;
        }
    }
}

void func_8011CE1C(ST05_BOSS *wp)
{
    STAGE_10C *obj;
    sint32 angle;
    sint32 c;
    uint16 r;

    obj = Open_SHL_WORK();
    if (obj != NULL)
    {
        obj->flags_0            = 3;
        obj->kind_2             = 1;
        obj->reserved04[0]      = 0;
        obj->value_F            = 1;
        r                       = wp->ctl.random_2;
        angle                   = r & 0xFFF;
        c                       = rcos(angle);
        wp->value_C4.x          = STAGE_PL.position.x + ((rsin(angle) * (((uint16)(r << 2) >> 6) + 0x80)) >> 12);
        wp->value_C4.y          = STAGE_PL.position.y;
        wp->value_C4.z          = STAGE_PL.position.z + ((c * (((uint16)(r << 2) >> 6) + 0x80)) >> 12);
        obj->position_fixed.v.x = wp->joint_180[0].x;
        obj->position_fixed.v.y = wp->joint_180[0].y - 0x104;
        obj->position_fixed.v.z = wp->joint_180[0].z;
        obj->position_fixed.v.x <<= 16;
        obj->position_fixed.v.y <<= 16;
        obj->position_fixed.v.z <<= 16;
        func_80030150(&obj->position_fixed.v, &obj->position);
        STAGE_PL.value_C4.x = wp->value_C4.x;
        STAGE_PL.value_C4.y = wp->value_C4.y;
        STAGE_PL.value_C4.z = wp->value_C4.z;
        func_80030934(obj, &Player_work, 0x32, 0);
        Sound_call2(0xCE, &wp->position);
    }
}

void func_8011CF8C(ST05_BOSS *wp)
{
    STCOM_EFFECT *fx;
    sint16 i;

    for (i = 0; i < 4; i++)
    {
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0         = 3;
            fx->reserved04[0]   = 0;
            fx->variant_3       = 3;
            fx->kind_2          = 0x83;
            fx->sprite.pos_8[0] = wp->joint_180[(i + 1) * 3].x;
            fx->sprite.pos_8[1] = -0x14;
            fx->sprite.pos_8[2] = wp->joint_180[(i + 1) * 3].z;
        }
    }
}

void func_8011D044(ST05_SPRAY *wp, uint8 big)
{
    STCOM_EFFECT *fx;

    fx = func_80031618();
    if (fx != NULL)
    {
        if (big == 0)
        {
            fx->flags_0       = 1;
            fx->kind_2        = 0x84;
            fx->variant_3     = 1;
            fx->reserved04[0] = 0;
            fx->value_C       = 0x20;
        }
        else
        {
            fx->flags_0       = 1;
            fx->kind_2        = 0x83;
            fx->reserved04[0] = 0;
            fx->variant_3     = 3;
        }
        fx->sprite.pos_8[0] = wp->position.x;
        fx->sprite.pos_8[1] = wp->position.y;
        fx->sprite.pos_8[2] = wp->position.z;
    }
}

sint32 func_8011D0E8(ST05_BOSS *wp, sint16 width, sint32 turn)
{
    sint32 side;

    ST05_PL.value_C4  = ST05_PL.joint_3A8[0];
    wp->value_C4      = wp->joint_180[0];
    wp->ctl.size_C8.y = 9;
    wp->ctl.size_C8.x = width;
    wp->ctl.size_C8.z = 4;
    side              = func_80030418(wp, &Player_work, &wp->ctl.size_C8, &wp->ctl.out_D0);
    if (!(side & 2))
    {
        if (side & 1)
        {
            wp->rotation.y = wp->rotation.y - turn;
        }
        else
        {
            wp->rotation.y = wp->rotation.y + turn;
        }
        wp->rotation.y &= 0xFFF;
    }
    return side;
}

void func_8011D1E0(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    STCOM_PL_WORK *pl;
    sint16 angle;

    ctl             = &wp->ctl;
    pl              = &Player_work;
    wp->ctl.timer_4 = 0;
    switch (wp->routine_1)
    {
        case 1:
            if (ctl->value_ED != ctl->value_EE)
            {
                angle = (ctl->value_ED - ctl->value_EE + 4) << 10;
                if (ctl->value_EE == 3)
                {
                    angle += 0x800;
                }
                angle &= 0xFFF;
                if (angle - (wp->rotation.y - 0x1000) < ST05_ABS(angle - wp->rotation.y))
                {
                    angle += 0x1000;
                }
                ctl->home_B8       = wp->position;
                ctl->target_C0     = D_80131A14[ctl->value_ED];
                ctl->home_B8.pad   = wp->rotation.y;
                ctl->target_C0.pad = angle;
                if (wp->position.x == D_80131A14[ctl->value_ED].x && wp->position.z == D_80131A14[ctl->value_ED].z)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 5;
                    ctl->value_E8 = 0;
                    ctl->flags_0 |= 0x40;
                }
            }
            break;
        case 5:
            if (ctl->flags_0 & 0x40)
            {
                wp->routine_1 = 3;
                ctl->flags_0 &= ~0x40;
            }
            else
            {
                wp->routine_1 = 1;
                ctl->timer_4  = 0x1E;
            }
            break;
        case 3:
            ctl->timer_4 = 0xA;
            func_8011D6F8(wp);
            break;
        case 6:
            wp->routine_1 = 1;
            ctl->timer_4  = 0xF;
            break;
        case 7:
            wp->routine_1 = 1;
            ctl->timer_4  = 0x1E;
            break;
        case 8:
            wp->routine_1 = 1;
            ctl->timer_4  = 0x5A;
            break;
        case 9:
            if ((ctl->flags_0 & 0x200) && wp->position.x == D_80131A14[1].x && wp->position.z == D_80131A14[1].z)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->timer_4              = 0xA;
                break;
            }
            ctl->home_B8       = wp->position;
            ctl->target_C0     = D_80131A14[ctl->value_EE];
            angle              = Angle_xz_svector(&ctl->target_C0, &pl->position);
            ctl->home_B8.pad   = wp->rotation.y;
            ctl->target_C0.pad = angle;
            ctl->value_E8      = 0;
            wp->routine_1      = 5;
            break;
        case 10:
            ctl->flags_0 &= ~0x40;
            if (wp->value_6E <= 0)
            {
                ctl->flags_0 &= ~0x80;
                wp->routine_1             = 0xB;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (ctl->value_ED == ctl->value_EE)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->timer_4              = 1;
                break;
            }
            ctl->home_B8       = wp->position;
            ctl->target_C0     = D_80131A14[ctl->value_ED];
            angle              = Angle_xz_svector(&ctl->target_C0, &pl->position);
            ctl->home_B8.pad   = wp->rotation.y;
            ctl->target_C0.pad = angle;
            ctl->value_E8      = 0;
            wp->routine_1      = 5;
            break;
    }
}

sint32 func_8011D580(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint32 found;
    sint32 r;
    sint32 r2;
    uint8 from;
    uint8 to;

    found = 0;
    ctl   = &wp->ctl;
    from  = wp->ctl.value_ED;
    to    = wp->ctl.value_EC;
    r     = wp->ctl.random_2 & 3;
    r2    = r;
    switch (from)
    {
        case 0:
            if (to == 1 || to == 5 || to == 8 || (to == 4 && r == 0))
            {
                ctl->value_EE = 1;
                found         = 1;
            }
            break;
        case 1:
            if (to == 0 || (to == 4 && r == 0))
            {
                wp->ctl.value_EE = 0;
                found            = 1;
            }
            else if (to == 2 || (to == 5 && r2 == 0))
            {
                ctl->value_EE = 2;
                found         = 1;
            }
            else if (to == 3 || to == 0xE || (to == 8 && r2 == 0))
            {
                ctl->value_EE = 3;
                found         = 1;
            }
            break;
        case 2:
            if (to == 1 || to == 4 || to == 8 || (to == 5 && r == 0))
            {
                ctl->value_EE = 1;
                found         = 1;
            }
            break;
        case 3:
            if (to == 1 || to == 4 || to == 5 || (to == 8 && r == 0))
            {
                ctl->value_EE = 1;
                found         = 1;
            }
            break;
    }
    return found;
}

void func_8011D6F8(ST05_BOSS *wp)
{
    STCOM_PL_WORK *pl;
    sint32 range;

    pl    = &Player_work;
    range = (sint32)(wp->ctl.dist_E0 << 6) >> 16;
    if (range >= 6)
    {
        wp->routine_1 = 1;
        return;
    }
    wp->routine_1             = D_80131A34[range][wp->ctl.random_2 & 3];
    *(uint16 *)&wp->routine_2 = 0;
    if (wp->routine_1 != 9 && !(func_8011D0E8(wp, 9, 0) & 2))
    {
        wp->ctl.home_B8           = wp->position;
        wp->ctl.target_C0         = D_80131A14[wp->ctl.value_EE];
        wp->ctl.target_C0.pad     = Angle_xz_svector(&wp->ctl.target_C0, &pl->position);
        wp->ctl.value_E8          = 0;
        wp->routine_1             = 5;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.home_B8.pad       = wp->rotation.y;
    }
}

sint32 func_8011D830(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint16 i;

    ctl             = &wp->ctl;
    wp->ctl.value_8 = D_8009884C[wp->kind_2]->life_A[0];
    for (i = 0; i < 8; i++)
    {
        if (i < 4)
        {
            ctl->hit_pos_B0 = wp->joint_180[(i + 1) * 3];
        }
        else
        {
            ctl->hit_pos_B0 = wp->joint_180[(i - 4) * 3 + 2];
        }
        func_800341BC(&ctl->hit_pos_B0, 0xC8, 0, 0x8000, wp->value_1, &ctl->hit_10[i], ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_pos_B0 = wp->joint_180[0];
    ctl->hit_pos_B0.x += rsin(wp->rotation.y + 0x800) >> 5;
    ctl->hit_pos_B0.z += rcos(wp->rotation.y + 0x800) >> 5;
    func_800341BC(&ctl->hit_pos_B0, 0xC8, 0, 0x8000, wp->value_1, &ctl->hit_10[8], ctl->value_8 | 0x4880000, 0x800000, 0);
    return 1;
}

sint32 func_8011DA0C(ST05_BOSS *wp)
{
    ST05_BOSS_CTL *ctl;
    sint32 total;
    sint32 hit;
    sint16 i;

    total        = 0;
    wp->value_B2 = wp->value_6E;
    ctl          = &wp->ctl;
    if (wp->routine_1 != 3)
    {
        for (i = 0; i < 4; i++)
        {
            hit = ctl->hit_10[i].hit_0 & 0xFFFFFF;
            if (hit != 0 && (ctl->hit_10[i].hit_0 & 0x18000000))
            {
                wp->value_6E -= hit;
                wp->joint_180[i * 3 + 1].pad = 0x7FFF;
                wp->joint_180[i * 3 + 2].pad = 0x7FFF;
                wp->joint_180[i * 3 + 3].pad = 0x7FFF;
                if (i == 0)
                {
                    total += hit;
                    Sound_call2(0xA2, &wp->position);
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
        }
        for (i = 4; i < 8; i++)
        {
            hit = ctl->hit_10[i].hit_0 & 0xFFFFFF;
            if (hit != 0 && (ctl->hit_10[i].hit_0 & 0x18000000))
            {
                wp->value_6E -= hit;
                wp->joint_180[(i - 4) * 3 + 1].pad = 0x7FFF;
                wp->joint_180[(i - 4) * 3 + 2].pad = 0x7FFF;
                wp->joint_180[(i - 4) * 3 + 3].pad = 0x7FFF;
                if (i == 4)
                {
                    total += hit;
                    Sound_call2(0xA2, &wp->position);
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
            }
        }
        hit = ctl->hit_10[8].hit_0 & 0xFFFFFF;
        if (hit != 0 && (ctl->hit_10[8].hit_0 & 0x18000000))
        {
            wp->joint_180[0].pad  = 0x7FFF;
            wp->joint_180[13].pad = 0x7FFF;
            wp->value_6E -= hit;
            Sound_call2(0xA0, &wp->position);
        }
        if (wp->jump_74 == 1)
        {
            total = 0;
        }
    }
    else
    {
        for (i = 0; i < 9; i++)
        {
            hit = ctl->hit_10[i].hit_0 & 0xFFFFFF;
            if (hit != 0 && (ctl->hit_10[i].hit_0 & 0x18000000))
            {
                Sound_call2(0xA3, &wp->position);
            }
        }
    }
    if (wp->value_B2 != wp->value_6E)
    {
        if (wp->value_6E <= 0)
        {
            if (ctl->value_ED == 1)
            {
                ctl->flags_0              = (ctl->flags_0 | 4) & ~0x82;
                wp->routine_1             = 0xB;
                *(uint16 *)&wp->routine_2 = 0;
                return 1;
            }
            wp->value_6E = 1;
        }
        if (ctl->flags_0 & 4)
        {
            ctl->timer_A += total;
            if (ctl->timer_A >= D_8009884C[wp->kind_2]->limit_9 * 4)
            {
                wp->routine_1             = 0xA;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->timer_A              = 0;
            }
        }
        if (wp->value_6E <= D_8009884C[wp->kind_2]->life_A[1] << 6)
        {
            ctl->flags_0 |= 0x200;
        }
        if (wp->value_6E <= D_8009884C[wp->kind_2]->life_A[2] << 6)
        {
            ctl->flags_0 |= 0x400;
        }
    }
    return 1;
}

void func_8011DDF8(ST05_HOLDER *wp)
{
    D_80131A5C[wp->routine_0](wp);
    if ((wp->flags_0 & 2) && wp->value_524 != 0)
    {
        Model_Shadow_Trans(wp, 0x20, 0x200, 0);
    }
}

void func_8011DE74(ST05_HOLDER *wp)
{
    sint16 i;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    wp->rotation.y = wp->u_C.b.byte_C * 16;
    D_8013807C     = 0;
    Model_work_init(wp, NULL);
    wp->scale.words[0]     = 0x2000200;
    wp->scale.words[1]     = 0x200;
    wp->scale.v.pad        = 0x4210;
    wp->value_78           = 0;
    wp->data_10            = D_80131B04;
    wp->position.y         = Obj_ceiling_height_get(wp);
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->u_C.b.byte_D       = 0;
    wp->u_E.b.byte_E       = D_80131A74[0];
    func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
    for (i = 0; i < 16; i++)
    {
        if ((D_8009F108[i].flags_0 & 1) && D_8009F108[i].kind_2 == 0x2A)
        {
            wp->target_520 = &D_8009F108[i];
        }
    }
    wp->routine_1 = 0;
    wp->value_524 = 0;
    D_80138088[0] = (STAGE_OBJ *)wp;
    wp->routine_0++;
}

// Keep the separate step-advance cases: their bodies and order reproduce retail's jump table.
void func_8011DFD4(ST05_HOLDER *wp)
{
    STCOM_PL_WORK *pl;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    pl                      = &Player_work;
    if (wp->u_E.b.byte_E++ == D_80131A74[wp->u_C.b.byte_D * 2])
    {
        switch (wp->u_C.b.byte_D)
        {
            case 0:
                wp->u_C.b.byte_D++;
                func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
                break;
            case 1:
                wp->u_C.b.byte_D++;
                func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
                break;
            case 2:
                wp->u_C.b.byte_D = 9;
                break;
            case 4:
                D_8013807C = 0;
                wp->u_C.b.byte_D++;
                func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
                break;
            case 3:
            case 5:
                wp->u_C.b.byte_D++;
                break;
            case 7:
                wp->u_C.b.byte_D++;
                func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
                break;
            case 8:
                D_8013807C       = 1;
                wp->u_C.b.byte_D = 3;
                func_800322A8(wp, D_80131A88, 0);
                break;
            case 6:
            case 9:
                wp->u_C.b.byte_D = 0;
                func_800322A8(wp, D_80131A74[-1], 0);
                break;
        }
        wp->u_E.b.byte_E = 0;
    }
    else if (wp->target_520->routine_0 == 2 && D_8013807C != 1)
    {
        D_8013807C       = 1;
        wp->u_C.b.byte_D = 3;
        wp->u_E.b.byte_E = 0;
        func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
    }
    else if (D_80131A74[wp->u_C.b.byte_D * 2 - 1] != -1)
    {
        func_80032488(wp);
    }
    Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(D_80131B00[D_8013807C * 2], 0x33, 0x37, 5));
    Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(D_80131B01[D_8013807C * 2], 0x33, 0x37, 5));
    if (pl->target_184 == wp)
    {
        wp->routine_1    = 1;
        wp->routine_2    = 0;
        wp->u_E.b.byte_F = 0;
        pl->target_184   = NULL;
        pl->flags_bd |= 0x20;
        pl->flags_0 ^= 2;
    }
    if (wp->routine_1 == 1)
    {
        func_8011E750((ST05_OBJ *)wp);
    }
}

void func_8011E334(ST05_HOLDER *wp)
{
    if (wp->u_E.b.byte_E++ == D_80131A74[wp->u_C.b.byte_D * 2])
    {
        switch (wp->u_C.b.byte_D)
        {
            case 9:
                wp->u_C.b.byte_D = 0xA;
                func_800322A8(wp, D_80131AC0, 0);
                break;
            case 10:
            case 11:
            case 13:
                wp->u_C.b.byte_D++;
                func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
                break;
            case 15:
                wp->u_C.b.byte_D++;
                func_800322A8(wp, D_80131A74[wp->u_C.b.byte_D * 2 - 1], 0);
                wp->value_524 = 1;
                break;
            case 12:
            case 14:
            case 16:
                wp->u_C.b.byte_D++;
                break;
            case 17:
                break;
        }
        wp->u_E.b.byte_E = 0;
    }
    else if (D_80131A74[wp->u_C.b.byte_D * 2 - 1] != -1)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_AC, wp->value_A4);
    }
}

void func_8011E490(ST05_HOLDER *wp)
{
    ST05_SPARK *ep;

    if (wp->value_A4 == 4 || wp->value_A4 == 0xA)
    {
        Sound_call2(0x112, &wp->position);
    }
    switch (wp->u_C.b.byte_D)
    {
        case 0:
            func_800322A8(wp, 6, 4);
            Obj_pos_set(wp, 0x166, 0, 0);
            ep = (ST05_SPARK *)func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->kind_2    = 0x83;
                ep->variant_3 = 0;
                ep->x_1C      = wp->position.x + (rand() & 0x3F) - 0x1F;
                ep->y_1E      = wp->position.y + (rand() & 0x1F) - 0xF;
                ep->z_20      = wp->position.z + (rand() & 0x3F) - 0x1F;
            }
            wp->u_E.b.byte_F++;
            wp->u_C.b.byte_D++;
            break;
        case 1:
            func_80032488(wp);
            if (++wp->u_E.b.byte_F == 0x3C)
            {
                wp->u_E.b.byte_F = 0;
                wp->u_C.b.byte_D++;
                break;
            }
            Obj_pos_set(wp, 0x166, 0, 0);
            ep = (ST05_SPARK *)func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->kind_2    = 0x83;
                ep->variant_3 = 0;
                ep->x_1C      = wp->position.x + (rand() & 0x3F) - 0x1F;
                ep->y_1E      = wp->position.y + (rand() & 0x1F) - 0xF;
                ep->z_20      = wp->position.z + (rand() & 0x3F) - 0x1F;
            }
            break;
        case 2:
            func_80032488(wp);
            if (++wp->u_E.b.byte_F == 0x3C)
            {
                wp->u_E.b.byte_F = 0;
                wp->u_C.b.byte_D += 2;
                break;
            }
            wp->rotation.y = (wp->rotation.y - 0x10) & 0xFFF;
            Obj_pos_set(wp, 0x166, 0, 0);
            ep = (ST05_SPARK *)func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->kind_2    = 0x83;
                ep->variant_3 = 0;
                ep->x_1C      = wp->position.x + (rand() & 0x3F) - 0x1F;
                ep->y_1E      = wp->position.y + (rand() & 0x1F) - 0xF;
                ep->z_20      = wp->position.z + (rand() & 0x3F) - 0x1F;
            }
            break;
        case 3:
            func_80032488(wp);
            if (++wp->u_E.b.byte_F == 0x78)
            {
                wp->u_C.b.byte_D++;
                break;
            }
            wp->rotation.y = (wp->rotation.y - 0x10) & 0xFFF;
            Obj_pos_set(wp, 0x166, 0, 0);
            ep = (ST05_SPARK *)func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->kind_2    = 0x83;
                ep->variant_3 = 0;
                ep->x_1C      = wp->position.x + (rand() & 0x3F) - 0x1F;
                ep->y_1E      = wp->position.y + (rand() & 0x1F) - 0xF;
                ep->z_20      = wp->position.z + (rand() & 0x3F) - 0x1F;
            }
            break;
        case 4:
            break;
    }
}

void func_8011E704(STAGE_OBJ *wp)
{
    if (wp->u_E.b.byte_F == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->u_E.b.byte_F++;
    }
}

void func_8011E750(ST05_OBJ *wp)
{
    STCOM_FIXED_VECTOR cam;
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            Scene_work.reserved00[1] = 0xFF;
            Scene_work.reserved00[0] = 1;
            pl->flags_0 &= ~2;
            cam.x = wp->joint_180[0].x;
            cam.y = wp->joint_180[0].y + 0x10;
            cam.z = wp->joint_180[0].z;
            func_80039FAC(&cam, 0x100, 0xC00, D_800A396C);
            wp->u_E.b.byte_F = 0;
            wp->routine_2++;
            break;
        case 1:
            if (func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 1);
                wp->routine_2++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                wp->u_E.b.byte_F = 0;
                wp->routine_2++;
                cam.x = D_8013808C->value_180.x;
                cam.y = D_8013808C->value_180.y;
                cam.z = D_8013808C->value_180.z;
                func_80039FAC(&cam, 0x100, 0x400, 0x100);
            }
            break;
        case 3:
            if (func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0xB);
                wp->routine_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_2++;
                func_80039E18();
            }
            break;
        case 5:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x20;
                pl->flags_0 |= 2;
                wp->routine_1       = 0;
                STAGE_SCENE_BYTE(1) = 0;
                STAGE_SCENE_BYTE(0) = 0;
            }
            break;
    }
}

void func_8011E92C(ST05_OBJ *wp)
{
    ST05_TALK *talk;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    talk                    = &wp->talk_500;
    if (wp->routine_1 == 0)
    {
        if (!(STAGE_FRAME & 1))
        {
            wp->scale.v.pad = 0x3547;
        }
        else
        {
            wp->scale.v.pad = 0x3126;
        }
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    talk->prev_2        = talk->flags_0;
    talk->random_14     = rand();
    talk->eyes_prev_E   = talk->eyes_C;
    talk->mouth_prev_12 = talk->mouth_10;
    D_80137F88          = D_80137F80;
    D_80137F8C          = D_80137F84;
    D_80131B10[wp->routine_0](wp);
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else if (talk->flags_0 & 1)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_AC, wp->value_A4);
    }
    if (talk->eyes_prev_E != talk->eyes_C)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(talk->eyes_C, 0x33, 0x37, 5));
    }
    if (talk->mouth_prev_12 != talk->mouth_10)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(talk->mouth_10, 0x33, 0x37, 5));
    }
}

void func_8011EB14(ST05_OBJ *wp)
{
    wp->rotation.x       = 0;
    wp->rotation.z       = 0;
    wp->value_64         = 0;
    wp->talk_500.flags_0 = wp->talk_500.prev_2 = 1;
    *(uint32 *)&wp->talk_500.timer_4           = 0;
    *(uint32 *)&wp->talk_500.value_8           = 0;
    *(uint32 *)&wp->talk_500.eyes_C            = 0;
    *(uint32 *)&wp->talk_500.mouth_10          = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x200;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
    func_8011EBAC(wp);
}

void func_8011EBAC(ST05_OBJ *wp)
{
    D_80131B1C[wp->routine_1](wp);
    func_8011F5A0(wp);
}

void func_8011EBFC(STAGE_OBJ *wp)
{
    func_8003187C(wp);
}

void func_8011EC1C(ST05_OBJ *wp)
{
    ST05_TALK *talk;

    talk = &wp->talk_500;
    if (wp->routine_3 == 0)
    {
        wp->routine_3        = 1;
        wp->talk_500.timer_4 = 0;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC = 1;
                talk->flags_0 &= ~1;
                D_80137F84     = D_80131B84_T[3];
                talk->mouth_10 = 0xC;
                talk->eyes_C   = 7;
                break;
            case 1:
                wp->anim_AC = 1;
                talk->flags_0 &= ~1;
                D_80137F84     = D_80131B84_T[0];
                talk->mouth_10 = 3;
                talk->eyes_C   = 0;
                break;
            case 2:
                wp->anim_AC = 1;
                talk->flags_0 &= ~1;
                D_80137F84     = D_80131B84_T[0];
                talk->mouth_10 = 3;
                talk->eyes_C   = 1;
                break;
            case 3:
                talk->flags_0 |= 1;
                D_80137F84     = D_80131B84_T[1];
                talk->mouth_10 = 4;
                talk->eyes_C   = 4;
                break;
            case 4:
                wp->anim_AC    = 2;
                D_80137F84     = D_80131B84_T[2];
                talk->mouth_10 = 9;
                talk->eyes_C   = 6;
                break;
        }
    }
    else
    {
        wp->talk_500.timer_4++;
        switch (wp->routine_2)
        {
            case 0:
                switch (talk->timer_4)
                {
                    case 0xA:
                        talk->flags_0 |= 4;
                        break;
                    case 0xD2:
                        talk->mouth_10 = 0xC;
                        talk->flags_0 &= ~4;
                        break;
                }
                break;
            case 1:
                switch (talk->timer_4)
                {
                    case 0x28:
                        talk->flags_0 |= 4;
                        break;
                    case 0x46:
                        talk->mouth_10 = 3;
                        talk->flags_0 &= ~4;
                        break;
                }
                break;
            case 2:
                switch (talk->timer_4)
                {
                    case 0xF:
                    case 0x73:
                        talk->flags_0 |= 4;
                        break;
                    case 0x55:
                    case 0xC3:
                        talk->mouth_10 = 3;
                        talk->flags_0 &= ~4;
                        break;
                    case 0xDD:
                        talk->eyes_C = 3;
                        break;
                    case 0xDC:
                    case 0xE0:
                        talk->eyes_C = 2;
                        break;
                }
                break;
            case 3:
                switch (talk->timer_4)
                {
                    case 0x14:
                    case 0x64:
                        talk->flags_0 |= 4;
                        break;
                    case 0x50:
                    case 0xD2:
                        talk->mouth_10 = 4;
                        talk->flags_0 &= ~4;
                        break;
                }
                if (talk->timer_4 == 0xFF)
                {
                    talk->mouth_10 = talk->eyes_C = 5;
                }
                break;
            case 4:
                switch (talk->timer_4)
                {
                    case 0xA:
                        talk->mouth_10 = 7;
                        break;
                    case 0x23:
                        talk->mouth_10 = 8;
                        break;
                    case 0x2D:
                        talk->flags_0 |= 4;
                        break;
                    case 0x64:
                        talk->mouth_10 = 9;
                        talk->flags_0 &= ~4;
                        break;
                    case 0x73:
                    case 0xBE:
                        talk->flags_0 |= 4;
                        break;
                    case 0xAA:
                    case 0x17E:
                        talk->mouth_10 = 0xC;
                        talk->flags_0 &= ~4;
                        break;
                }
                if (talk->timer_4 == 0x6E)
                {
                    wp->anim_AC    = 3;
                    D_80137F84     = D_80131B84_T[3];
                    talk->mouth_10 = 0xC;
                    talk->eyes_C   = 7;
                }
                break;
        }
    }
}

void func_8011EFF8(ST05_OBJ *wp)
{
    ST05_TALK *talk;

    talk = &wp->talk_500;
    if (wp->u_C.b.byte_D != 0)
    {
        wp->u_C.b.byte_D = 0;
        wp->routine_3    = 0;
        wp->routine_2    = wp->u_E.b.byte_E;
    }
    if (wp->routine_3 == 0)
    {
        wp->routine_3        = 1;
        wp->talk_500.timer_4 = 0;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC  = 4;
                talk->eyes_C = 7;
                talk->flags_0 &= ~1;
                D_80137F84          = D_80131B84_T[3];
                talk->mouth_10      = 0xC;
                talk->eyes_prev_E   = 0xFF;
                talk->mouth_prev_12 = 0xFF;
                break;
            case 3:
                wp->anim_AC  = 5;
                talk->eyes_C = 8;
                break;
            case 5:
                wp->anim_AC             = 6;
                wp->part_100[2].value_0 = 0x13;
                D_80137F84              = D_80131B84_T[4];
                talk->mouth_10          = 0xF;
                talk->eyes_C            = 9;
                break;
            case 6:
                wp->anim_AC             = 7;
                wp->part_100[2].value_0 = 4;
                break;
            case 8:
                D_80137F84     = D_80131B84_T[3];
                talk->mouth_10 = 4;
                talk->eyes_C   = 0xB;
                break;
            case 9:
                talk->eyes_C = 7;
                D_80137F84   = D_80131B84_T[2];
                talk->flags_0 |= 4;
                break;
        }
    }
    else
    {
        wp->talk_500.timer_4++;
        switch (wp->routine_2)
        {
            case 0:
                switch (talk->timer_4)
                {
                    case 0x28:
                        talk->flags_0 |= 4;
                        break;
                    case 0x4B:
                        talk->mouth_10 = 0xC;
                        talk->flags_0 &= ~4;
                        break;
                }
                if (talk->timer_4 == 0x10)
                {
                    talk->flags_0 |= 1;
                    wp->routine_1 = 1;
                }
                break;
            case 1:
                switch (talk->timer_4)
                {
                    case 0xA:
                        talk->flags_0 |= 4;
                        break;
                    case 0x50:
                        talk->mouth_10 = 0xC;
                        talk->flags_0 &= ~4;
                        break;
                }
                break;
            case 3:
                switch (talk->timer_4)
                {
                    case 0x5:
                    case 0x32:
                    case 0x5A:
                        talk->flags_0 |= 4;
                        break;
                    case 0x1E:
                    case 0x55:
                    case 0x94:
                        talk->mouth_10 = 0xC;
                        talk->flags_0 &= ~4;
                        break;
                }
                break;
            case 5:
                switch (talk->timer_4)
                {
                    case 0xA:
                        talk->flags_0 |= 4;
                        break;
                    case 0xAA:
                        talk->mouth_10 = 0xF;
                        talk->flags_0 &= ~4;
                        break;
                    case 0x32:
                    case 0xB4:
                        talk->eyes_C = 0xA;
                        break;
                    case 0x36:
                    case 0xB8:
                        talk->eyes_C = 9;
                        break;
                }
                break;
            case 6:
                switch (talk->timer_4)
                {
                    case 0x5:
                    case 0xAA:
                        talk->flags_0 |= 4;
                        break;
                    case 0x87:
                    case 0xFF:
                        talk->mouth_10 = 0xF;
                        talk->flags_0 &= ~4;
                        break;
                    case 0x28:
                    case 0xC8:
                        talk->eyes_C = 0xA;
                        break;
                    case 0x2C:
                    case 0xCC:
                        talk->eyes_C = 9;
                        break;
                }
                break;
            case 8:
                switch (talk->timer_4)
                {
                    case 0x1E:
                    case 0x46:
                    case 0x78:
                    case 0xC8:
                        talk->flags_0 |= 4;
                        break;
                    case 0x41:
                    case 0x73:
                    case 0xB9:
                    case 0xFF:
                        talk->mouth_10 = 0xC;
                        talk->flags_0 &= ~4;
                        break;
                }
                switch (talk->timer_4)
                {
                    case 0x1E:
                        wp->anim_AC  = 8;
                        talk->eyes_C = 7;
                        break;
                    case 0x46:
                        wp->anim_AC = 9;
                        break;
                    case 0x5A:
                    case 0x7D:
                        wp->anim_prev_AD = 0;
                        break;
                    case 0xD2:
                        wp->anim_AC = 0xA;
                        break;
                }
                break;
            case 9:
                switch (talk->timer_4)
                {
                    case 0x1:
                        wp->anim_AC = 0xB;
                        break;
                    case 0xBE:
                    case 0x113:
                        wp->anim_AC = 0xC;
                        break;
                    case 0xF5:
                        wp->anim_AC    = 0xD;
                        talk->eyes_C   = 0xC;
                        talk->mouth_10 = 0x10;
                        talk->flags_0 &= ~4;
                        break;
                }
                break;
        }
    }
}

void func_8011F5A0(ST05_OBJ *wp)
{
    ST05_TALK *talk;

    talk = &wp->talk_500;
    if (D_80137F84 != D_80137F8C || ((wp->talk_500.flags_0 ^ wp->talk_500.prev_2) & 4))
    {
        wp->talk_500.count_A = 0;
    }
    if (talk->flags_0 & 4)
    {
        if ((sint16)(talk->count_A % 3) == 0)
        {
            talk->mouth_10 = D_80137F84[(sint16)(talk->count_A / 3)];
        }
        talk->count_A = (talk->count_A + 1) & 0xF;
    }
}

void func_8011F660(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    face                    = &wp->u_4E0.face16;
    D_80131B9C[wp->routine_0](wp, face);
    func_80120120(wp, face);
}

void func_8011F720(ST05_OBJ *wp, ST05_FACE *face)
{
    switch (wp->routine_1)
    {
        case 0:
            if (wp->routine_2 == 0)
            {
                wp->flags_0 |= 2;
                Model_work_init(wp, &wp->variant_3);
                wp->scale.words[0]     = 0x2000200;
                wp->scale.words[1]     = 0x200;
                wp->scale.v.pad        = 0x4210;
                wp->value_78           = 0;
                wp->position.y         = wp->position.y + Obj_ceiling_height_get(wp);
                wp->position_fixed.v.y = wp->position.y << 16;
                face->count_15         = 0;
                func_801200DC(&face->face, 0);
                func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
                func_80120268(wp);
                wp->routine_2++;
            }
            else
            {
                if (!(wp->value_A4 & 1))
                {
                    func_80120268(wp);
                }
                func_80032488(wp);
            }
            break;
        case 1:
            if (wp->routine_2 == 0)
            {
                func_800322A8(wp, 0x19, 0);
                func_80120268(wp);
                wp->routine_2++;
            }
            else
            {
                if (!(wp->value_A4 & 1))
                {
                    func_80120268(wp);
                }
                func_80032488(wp);
            }
            break;
        case 2:
            if (face->count_15 & 1)
            {
                func_80120268(wp);
            }
            face->count_15++;
            func_800322A8(wp, 0x1A, 0);
            break;
        case 3:
            if (wp->routine_2 == 0)
            {
                func_800322A8(wp, 0x1A, 0);
                wp->routine_2++;
                break;
            }
            if (wp->value_A4 == 9)
            {
                func_80120348(wp);
            }
            func_80032488(wp);
            if (Scene_work.reserved00[5] == 4 && Scene_work.u_8.byte[1] == 0 && Scene_work.value_10 == 1)
            {
                wp->routine_1 = 0;
                wp->routine_2 = 0;
                wp->routine_0++;
            }
            break;
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_8011F988(ST05_OBJ *wp, ST05_FACE *face)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (wp->routine_1 == 0)
    {
        face->count_15 = 0;
        face->value_14 = 0;
        func_801200DC(&face->face, 0);
        func_80120348(wp);
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
        wp->routine_1++;
    }
    else
    {
        func_80032488(wp);
    }
    if (scene->u_8.byte[1] == 0 && (scene->value_10 == 0xE || scene->value_10 == 0x18 || scene->value_10 == 0x28))
    {
        func_801200DC(&face->face, 1);
        func_80120434(wp);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_8011FA7C(ST05_OBJ *wp, ST05_FACE *face)
{
    if (wp->routine_1 == 0)
    {
        func_801200DC(&face->face, 5);
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
        face->timer_16 = 0;
        wp->routine_1++;
    }
    else
    {
        switch (face->timer_16)
        {
            case 5:
            case 0x14:
            case 0x50:
                func_801200DC(&face->face, 2);
                break;
            case 0xA:
            case 0x46:
            case 0x87:
                func_801200DC(&face->face, 5);
                break;
        }
        func_80032488(wp);
        face->timer_16++;
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_8011FBA4(ST05_OBJ *wp, STAGE_FACE16 *face)
{
    if (STAGE_SCENE_PTR->reserved00[7] == 3)
    {
        wp->routine_1++;
        STAGE_SCENE_PTR->reserved00[7]++;
    }
    if (wp->routine_1 == 0)
    {
        func_801200DC(face, 3);
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
    }
    else
    {
        if (wp->value_A7 == -1)
        {
            wp->routine_1 = 0;
            wp->rotation.y += 0x80;
            wp->routine_0++;
        }
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_8011FC88(ST05_OBJ *wp, ST05_FACE *face)
{
    if (wp->routine_1 == 0)
    {
        wp->rotation.y = 0x800;
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
        face->value_14 = 0;
        wp->routine_1++;
    }
    else
    {
        if ((wp->value_A7 & 0x80) && face->value_14 != 0)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
        }
        else
        {
            if (wp->value_A7 & 0x80)
            {
                face->value_14++;
            }
            wp->position_fixed.v.z += 0x43E1D;
            wp->position.z += 4;
        }
        func_80032488(wp);
    }
    if (wp->value_A6 != 0)
    {
        Sound_call(0x111, 0, 0);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_8011FD90(ST05_OBJ *wp, ST05_FACE *face)
{
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
        face->count_15 = 0;
        wp->routine_1++;
    }
    else
    {
        if (wp->value_A7 == -1)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
        }
        else
        {
            if (face->count_15 < 0x28)
            {
                if (!(face->count_15 & 1))
                {
                    wp->position_fixed.v.y -= 0x40000;
                    wp->position.y -= 4;
                }
                else
                {
                    wp->position_fixed.v.y -= 0x68000;
                    wp->position.y -= 3;
                }
                wp->position_fixed.v.x += 0x30000;
                wp->position.x += 3;
            }
            face->count_15++;
        }
        func_80032488(wp);
    }
    if (face->count_15 < 8)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
}

void func_8011FEC8(ST05_OBJ *wp, ST05_FACE *face)
{
    if (wp->routine_1 == 0)
    {
        wp->rotation.y += 0x200;
        func_801200DC(&face->face, 6);
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
        face->count_15 = 0;
        face->timer_16 = 0;
        wp->routine_1++;
        return;
    }
    if (wp->value_A7 == -1)
    {
        wp->routine_1 = 0;
        wp->routine_0++;
    }
    switch (face->timer_16)
    {
        case 0:
        case 0x41:
        case 0xAA:
            func_801200DC(&face->face, 4);
            break;
        case 0x3C:
        case 0xA5:
        case 0xFF:
            func_801200DC(&face->face, 6);
            break;
    }
    face->timer_16++;
    if (face->count_15 < 0xAA && wp->value_A4 == 0xE)
    {
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0xE);
        face->count_15++;
        return;
    }
    func_80032488(wp);
}

void func_80120050(ST05_OBJ *wp, STAGE_FACE16 *face)
{
    if (wp->routine_1 == 0)
    {
        func_801200DC(face, 3);
        func_800322A8(wp, D_80131BBC[wp->routine_0], 0);
        wp->routine_1++;
    }
    else
    {
        if (wp->value_A7 == -1)
        {
            func_8003187C(wp);
        }
        func_80032488(wp);
    }
}

void func_801200DC(STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->prev_2 = face->index_4 = 0;
    face->shape_6 = face->prev_8 = face->index_A = 0;
    face->mouth_C                                = D_80131C64[index];
    face->eyes_10                                = D_80131C80[index];
}

void func_80120120(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    face->prev_2 = face->shape_0;
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        Model_mesh_uv_copy(wp->model_88, 0x10000F, Model_uv_cell(face->shape_0, 0x33, 0x37, 5));
    }
    face->prev_8 = face->shape_6;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        Model_mesh_uv_copy(wp->model_88, 0x120011, Model_uv_cell(face->shape_6, 0x33, 0x37, 5));
    }
}

void func_80120268(ST05_OBJ *wp)
{
    STCOM_EFFECT *fx;
    sint32 i;

    for (i = 0; i < 8; i++)
    {
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0         = 1;
            fx->kind_2          = 0xB;
            fx->variant_3       = 1;
            fx->value_C         = 0;
            fx->value_D         = 0;
            fx->sprite.pos_8[0] = wp->position.x + (sint8)D_80131C9C[i];
            fx->sprite.pos_8[1] = wp->position.y + (rand() & 0x3F) - 0x20;
            fx->sprite.pos_8[2] = wp->position.z + (sint8)D_80131CA4[i];
            fx->routine_1       = rand() & 0xF;
        }
    }
}

void func_80120348(ST05_OBJ *wp)
{
    STCOM_EFFECT *fx;
    sint32 i;

    for (i = 0; i < 8; i++)
    {
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0         = 1;
            fx->kind_2          = 0xB;
            fx->variant_3       = 1;
            fx->value_C         = 0;
            fx->value_D         = 0;
            fx->sprite.pos_8[0] = wp->position.x + (sint8)D_80131CAC[i];
            fx->sprite.pos_8[1] = wp->position.y + (sint8)D_80131CB4[i] - 0x78;
            fx->sprite.pos_8[2] = wp->position.z + (sint8)D_80131CBC[i];
            fx->routine_1       = rand() & 0xF;
        }
    }
}

void func_80120434(ST05_OBJ *wp)
{
    STCOM_EFFECT *fx;
    sint32 dx;
    sint32 dz;

    fx = func_80031618();
    if (fx != NULL)
    {
        fx->flags_0         = 1;
        fx->kind_2          = 0xB;
        fx->variant_3       = 0;
        fx->value_C         = 0;
        fx->value_D         = 0;
        dx                  = (rand() & 1) - 8;
        fx->sprite.pos_8[0] = wp->position.x + dx;
        fx->sprite.pos_8[1] = -0x84;
        dz                  = (rand() & 1) - 0xF;
        fx->sprite.pos_8[2] = wp->position.z + dz;
        fx->routine_1       = 0;
    }
}
