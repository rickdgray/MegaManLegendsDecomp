#include "common.h"
#include "code_80043f34.h"

// Small data reached through $gp
uint8 D_80097DE4[4];
uint8 D_80097DE8[4];
uint8 D_80097DEC[4];

void func_80043F34(CODE43_WORK *wp)
{
    D_8008A208[wp->routine_8](wp);
}

// The 4..6 range test is a switch: retail compares i < 7 and i < 4 separately.
void func_80043F70(CODE43_WORK *wp)
{
    sint32 st;
    uint32 i;
    CODE43_WORK *n;

    if (wp->value_3 == 0xFE)
    {
        wp->sound_flag_c = 0;
        wp->value_3      = 0xC2;
    }
    else
    {
        wp->sound_flag_c = 1;
    }
    if (wp->sel_e != 0)
    {
        wp->flags_0 |= 0x82;
    }
    else
    {
        wp->flags_0 |= 2;
    }
    st                 = wp->value_3 & 0xF;
    CODE43_H(wp, 0x44) = D_8008A138[st][wp->sel_d].a;
    CODE43_H(wp, 0x46) = D_8008A138[st][wp->sel_d].b;
    wp->word_40        = 0x2808080;
    wp->index_a        = 0;
    wp->pos_38.w       = 0;
    CODE43_W(wp, 0x18) = 0x1000;
    CODE43_W(wp, 0x1C) = 0;
    CODE43_W(wp, 0x20) = 0x1000;
    CODE43_W(wp, 0x24) = 0;
    CODE43_W(wp, 0x28) = 0x1000;
    CODE43_W(wp, 0x2C) = 0;
    CODE43_W(wp, 0x30) = 0;
    CODE43_W(wp, 0x34) = 0;
    CODE43_H(wp, 0x28) = 0;
    CODE43_H(wp, 0x20) = 0;
    CODE43_H(wp, 0x18) = 0;
    if (wp->value_3 & 0x80)
    {
        st = 0;
    }
    else if (wp->value_3 & 0x20)
    {
        Sound_call2(0xA4, &wp->pos_38);
        wp->sound_flag_c = 0;
        st               = 2;
        func_800398E0(0x1E);
        n = func_80031618();
        if (n != 0)
        {
            n->flags_0               = 5;
            n->value_2               = 0x80;
            n->value_3               = 5;
            *(CODE43_B8 *)&n->pos_38 = *(CODE43_B8 *)&wp->pos_38;
        }
        n = func_80031618();
        if (n != 0)
        {
            n->flags_0               = 0x45;
            n->value_2               = 0x80;
            n->value_3               = 6;
            *(CODE43_B8 *)&n->pos_38 = *(CODE43_B8 *)&wp->pos_38;
        }
    }
    else
    {
        i  = wp->value_3 & 0xF;
        st = i;
        switch (i)
        {
            case 4:
            case 5:
            case 6:
                break;
            default:
                if (func_8004920C(&wp->pos_38) - wp->pos_38.y < 0x1E)
                {
                    st = 0;
                }
                else
                {
                    st = 1;
                }
                break;
        }
    }
    wp->value_2 = D_80097DE0[wp->sel_e];
    func_8002F9C4(wp, &st);
    wp->value_2 = 0x80;
    wp->routine_8++;
    wp->timer_b = 0;
    if (wp->sound_flag_c != 0)
    {
        Sound_call2(0xA1, &wp->pos_38);
    }
}

// One temporary `t` serves three values (the player x, the y difference and the squared
// radius); that reuse gives retail's load order and registers for the distance terms and the
// squares. Loading the raw w before the (sint16) / 2 gives retail's lhu and radius register.
void func_800441CC(CODE43_WORK *wp)
{
    uint32 add;
    uint32 dist;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 r;
    sint32 t;

    D_8008A214[wp->count_9](wp);
    add = D_80097DDC[wp->sel_d];
    switch (wp->sel_e)
    {
        case 0:
            if (wp->value_3 & 0x40)
            {
                func_800341BC(&wp->pos_38, (sint16)wp->pos_38.w / 2, 0, 0xA000, wp->byte_1,
                              D_800986C0, add | 0x10000000, 0, 0x80);
            }
            else if (wp->value_3 == 6)
            {
                if (wp->sel_f != 0)
                {
                    t    = CODE43_PLAYER_H(0x14);
                    dx   = t - wp->pos_38.x;
                    t    = CODE43_PLAYER_H(0x16) - wp->pos_38.y;
                    dy   = t;
                    dz   = CODE43_PLAYER_H(0x18) - wp->pos_38.z;
                    dist = dx * dx + dy * dy + dz * dz;
                    r    = (uint16)wp->pos_38.w;
                    r    = (sint16)r / 2;
                    t    = r * r;
                    if (t >= dist && CODE43_PLAYER_B(0x74) == 0)
                    {
                        CODE43_PLAYER_W(0x188) |= 0x10000000;
                        switch (wp->sel_f)
                        {
                            case 1:
                            default:
                                add = 0x20;
                                break;
                            case 2:
                                add = 0x30;
                                break;
                            case 3:
                                add = 0x40;
                                break;
                        }
                        CODE43_PLAYER_W(0x188) = (CODE43_PLAYER_W(0x188) & 0xFF000000) |
                                                 ((CODE43_PLAYER_W(0x188) & 0xFFFFFF) + add) |
                                                 0x01000000;
                    }
                }
                else
                {
                    func_800341BC(&wp->pos_38, (sint16)wp->pos_38.w / 2, 0, 0xC000, wp->byte_1,
                                  D_800986C0, 0x31000000, 0, 0x80);
                }
            }
            else
            {
                func_800341BC(&wp->pos_38, (sint16)wp->pos_38.w / 2, 0, 0xC000, wp->byte_1,
                              D_800986C0, add | 0x10000000, 0, 0x80);
            }
            break;
        case 1:
            func_800341BC(&wp->pos_38, (sint16)wp->pos_38.w / 2, 0, 0x4000, wp->byte_1, D_800986C0,
                          add | 0x10000000, 0, 0x80);
            break;
        case 2:
        default:
            break;
    }
}

void func_8004441C(CODE43_WORK *wp)
{
    sint16 *v;
    sint32 c;
    sint32 w;
    sint32 lim;

    v = (sint16 *)&wp->word_44;
    switch (wp->value_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            v[0] += v[1];
            wp->pos_38.w += v[0];
            if (v[0] <= 0)
            {
                lim = D_8008A1A8[wp->sel_d].limit;
                if (wp->pos_38.w < lim)
                {
                    wp->routine_8++;
                    wp->pos_38.w = 0;
                    return;
                }
                v[1] = 0;
                v[0] = D_8008A1A8[wp->sel_d].speed;
                if (D_8008A1A8[wp->sel_d].high < wp->pos_38.w)
                {
                    c = 0x80;
                }
                else
                {
                    c = ((wp->pos_38.w - lim) << 7) / wp->pos_38.w;
                }
            }
            else
            {
                c = 0x80;
            }
            if (c < 0)
            {
                c = 0;
            }
            wp->word_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 1:
            v[0] += v[1];
            w = wp->pos_38.w += v[0];
            if (w <= 0)
            {
                wp->routine_8++;
                wp->pos_38.w = 0;
                return;
            }
            lim = D_8008A1C8[wp->sel_d].limit;
            if (v[0] <= 0 && w <= lim)
            {
                c = 0x60 - ((lim - w) << 7) / lim;
            }
            else
            {
                c = 0x80;
            }
            if (c >= 0x100)
            {
                c = 0xFF;
            }
            if (c < 0)
            {
                c = 0;
            }
            wp->word_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 2:
            v[0] += v[1];
            wp->pos_38.w += v[0];
            if (v[0] <= 0)
            {
                wp->routine_8++;
                wp->pos_38.w = 0;
                return;
            }
            if (D_8008A1E8[wp->sel_d].limit < wp->pos_38.w)
            {
                wp->index_a += D_8008A1E8[wp->sel_d].step;
                if (wp->index_a <= 0x80)
                {
                    c = 0x80 - wp->index_a;
                }
                else
                {
                    c = 0;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->word_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 4:
            v[0] += v[1];
            wp->pos_38.w += v[0];
            if (v[0] <= 0)
            {
                if (wp->pos_38.w < 100)
                {
                    wp->routine_8++;
                    wp->pos_38.w = 0;
                }
                v[1] = 0;
                v[0] = -20;
                if (wp->pos_38.w > 0x400)
                {
                    c = 0x80;
                }
                else
                {
                    c = wp->pos_38.w >> 3;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->word_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 5:
            v[0] += v[1];
            wp->pos_38.w += v[0];
            if (v[0] < 0x82)
            {
                wp->index_a++;
            }
            if (wp->index_a >= 8)
            {
                wp->index_a = 8;
                wp->routine_8++;
            }
            c           = (8 - wp->index_a) * 16;
            wp->word_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 6:
            v[0] += v[1];
            wp->pos_38.w += v[0];
            if (wp->pos_38.w > 0x800)
            {
                wp->index_a += 10;
                if (wp->index_a <= 0x80)
                {
                    c = 0x80 - wp->index_a;
                }
                else
                {
                    c = 0;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->word_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            if (c == 0)
            {
                wp->routine_8++;
                wp->pos_38.w = 0;
            }
            break;
    }
    CODE43_W(wp, 0x18) = 0x1000;
    CODE43_W(wp, 0x20) = 0x1000;
    CODE43_W(wp, 0x28) = 0x1000;
    CODE43_W(wp, 0x1C) = 0;
    CODE43_W(wp, 0x24) = 0;
    CODE43_W(wp, 0x2C) = 0;
    CODE43_W(wp, 0x30) = 0;
    CODE43_W(wp, 0x34) = 0;
    CODE43_H(wp, 0x18) = CODE43_H(wp, 0x20) = CODE43_H(wp, 0x28) = wp->pos_38.w;
    RotMatrixY(++wp->timer_b << 7, (uint8 *)wp + 0x18);
}

void func_8004492C(CODE43_WORK *wp)
{
}

void func_80044934(CODE43_WORK *wp)
{
}

void func_8004493C(CODE43_WORK *wp)
{
    func_80031988(wp);
}

void func_8004495C(CODE43_WORK *wp)
{
    D_8008A220[wp->routine_8](wp);
}

void func_80044998(CODE43_WORK *wp)
{
    wp->flags_0 |= 2;
    func_8002F9C4(wp, 0);
    wp->word_40 = 0x2808080;
    wp->word_44 = wp->u14.parent->inner_70->value_10;
    wp->routine_8++;
    wp->timer_b = 0x10;
}

void func_80044A00(CODE43_WORK *wp)
{
    CODE43_VEC scale;

    if (--wp->timer_b == 0)
    {
        wp->routine_8++;
    }
    scale.vx = scale.vy = scale.vz = 0x1115;
    ScaleMatrix(&wp->word_18, &scale);
    wp->word_40 += 0xFFF7F7F8;
}

void func_80044A80(CODE43_WORK *wp)
{
    wp->flags_0 = 0;
    func_80031988(wp);
}

void func_80044AA0(CODE43_WORK *wp)
{
}

void func_80044AA8(CODE43_WORK *wp)
{
}

void func_80044AB0(CODE43_WORK *wp)
{
    D_8008A250[wp->routine_8](wp);
}

void func_80044AEC(CODE43_WORK *wp)
{
    wp->u14.word = 0x3D48002E;
    wp->word_18  = 0x2E808080;
    wp->flags_0 |= 0x22;
    wp->value_22 = D_8008A234[0];
    wp->value_23 = D_8008A235[0];
    wp->value_24 = D_8008A248[0];
    wp->value_26 = rand() & 0x3F;
    wp->timer_b  = D_8008A240[0];
    wp->index_a  = 0;
    wp->count_9  = 0;
    wp->routine_8++;
    if (wp->sound_flag_c != 0)
    {
        Sound_call2(0x9B, wp->sound_1c);
    }
}

void func_80044BA0(CODE43_WORK *wp)
{
    uint8 i;
    uint32 unused[2];

    wp->count_9++;
    if (--wp->timer_b == 0)
    {
        i = ++wp->index_a;
        if (i >= 6)
        {
            func_80031988(wp);
        }
        else
        {
            wp->timer_b  = D_8008A240[i];
            wp->value_22 = D_8008A234[i * 2];
            wp->value_23 = D_8008A235[i * 2];
            wp->value_24 = D_8008A248[wp->count_9];
        }
    }
}

void func_80044C58(CODE43_WORK *wp)
{
    D_8008A258[wp->routine_8](wp);
}

void func_80044C94(CODE43_WORK *wp)
{
    wp->u14.word = 0x3D48002E;
    wp->word_18  = 0x2E404040;
    wp->value_22 = 0x20;
    wp->value_23 = 0;
    wp->flags_0 |= 2;
    wp->reserved04[2] |= 0x20;
    switch (wp->value_3)
    {
        case 0:
        default:
            wp->value_24 = 0xD;
            wp->timer_b  = D_80097DE4[0];
            wp->value_3  = 0;
            break;
        case 1:
            wp->value_24 = 0x20;
            wp->timer_b  = D_80097DE8[0];
            wp->value_3  = 1;
            break;
        case 2:
            wp->value_24 = 0x40;
            wp->timer_b  = D_80097DEC[0];
            wp->value_3  = 2;
            break;
        case 3:
            wp->value_24 = 0x80;
            wp->timer_b  = D_80097DE4[0];
            wp->value_3  = 0;
            break;
    }
    wp->index_a = 0;
    wp->routine_8++;
}

void func_80044D5C(CODE43_WORK *wp)
{
    uint8 t;

    switch (wp->value_3)
    {
        case 0:
            wp->value_1e--;
            wp->value_24++;
            wp->word_18 += 0xFFFBFBFC;
            break;
        case 1:
            wp->value_24--;
            wp->word_18 += 0xFFFBFBFC;
            break;
        case 2:
        default:
            wp->value_1e -= 5;
            wp->value_24 += 6;
            wp->word_18 += 0x40404;
            break;
    }
    if (--wp->timer_b == 0)
    {
        t = D_80097DE5[wp->value_3 * 4];
        wp->routine_8++;
        wp->value_22 = 0x40;
        wp->timer_b  = t;
    }
}

void func_80044E50(CODE43_WORK *wp)
{
    uint8 t;

    switch (wp->value_3)
    {
        case 0:
            wp->value_1e--;
            wp->value_24++;
            wp->word_18 += 0xFFFBFBFC;
            break;
        case 1:
            wp->value_24--;
            wp->word_18 += 0xFFFBFBFC;
            break;
        case 2:
        default:
            wp->value_1e -= 5;
            wp->value_24 -= 2;
            wp->word_18 += 0xFFFBFBFC;
            break;
    }
    if (--wp->timer_b == 0)
    {
        t = D_80097DE6[wp->value_3 * 4];
        wp->routine_8++;
        wp->value_22 = 0x60;
        wp->timer_b  = t;
    }
}

void func_80044F44(CODE43_WORK *wp)
{
    uint8 t;

    switch (wp->value_3)
    {
        case 0:
            wp->value_1e -= 2;
            wp->value_24++;
            wp->word_18 += 0xFFFBFBFC;
            break;
        case 1:
            wp->value_24--;
            wp->word_18 += 0xFFFBFBFC;
            break;
        case 2:
        default:
            wp->value_1e -= 5;
            wp->value_24 -= 2;
            wp->word_18 += 0xFFFBFBFC;
            break;
    }
    if (--wp->timer_b == 0)
    {
        t = D_80097DE7[wp->value_3 * 4];
        wp->routine_8++;
        wp->value_22 = 0x80;
        wp->timer_b  = t;
    }
}

void func_80045038(CODE43_WORK *wp)
{
    if (--wp->timer_b == 0)
    {
        wp->flags_0 = 0;
        func_80031988(wp);
    }
}

void func_80045074(CODE43_WORK *wp)
{
    D_8008A288[wp->routine_8](wp);
}

void func_800450B0(CODE43_WORK *wp)
{
    wp->u14.word = 0x3D48002E;
    wp->word_18  = 0x2E208080;
    wp->flags_0 |= 0x22;
    wp->value_22 = D_8008A26C[0];
    wp->value_23 = D_8008A26D[0];
    if (wp->value_3 == 0)
    {
        wp->sound_flag_c = 0xC;
    }
    wp->value_24 = (D_8008A280[0] * wp->sound_flag_c) >> 4;
    wp->value_26 = rand() & 0x3F;
    wp->timer_b  = D_8008A278[0];
    wp->index_a  = 0;
    wp->count_9  = 0;
    wp->routine_8++;
}

void func_80045170(CODE43_WORK *wp)
{
    uint8 i;
    uint32 unused[2];

    wp->count_9++;
    if (--wp->timer_b == 0)
    {
        i = ++wp->index_a;
        if (i >= 6)
        {
            func_80031988(wp);
        }
        else
        {
            wp->timer_b  = D_8008A278[i];
            wp->value_22 = D_8008A26C[i * 2];
            wp->value_23 = D_8008A26D[i * 2];
            wp->value_24 = (D_8008A280[wp->count_9] * wp->sound_flag_c) >> 4;
        }
    }
}

void func_80045238(CODE43_WORK *wp)
{
    D_8008A290[wp->routine_8](wp);
}

void func_80045274(CODE43_WORK *wp)
{
    uint32 i;

    wp->flags_0 |= 0x22;
    i = wp->value_3;
    if (i >= 0x10)
    {
        wp->value_24 = 0x40;
        i            = wp->value_3 -= 0x10;
    }
    else
    {
        wp->value_24 = D_80097DF0[i].value_24;
    }
    wp->u14.word  = D_80097DF0[i].word_14;
    wp->word_18   = D_80097DF0[i].word_18;
    wp->value_22  = D_80097DF0[i].value_22;
    wp->value_23  = D_80097DF0[i].value_23;
    wp->index_a   = 0;
    wp->routine_8 = D_80097DF0[i].routine_8;
}

void func_80045338(CODE43_WORK *wp)
{
    if (wp->word_40 == 0xFFFF)
    {
        func_80031988(wp);
        return;
    }
    wp->value_22 = 0xA0;
    wp->value_23 = 0x40;
    wp->routine_8++;
    if (wp->value_24 >= 0x40)
    {
        CODE43_HALF_1C(wp) -= wp->value_30 / 256;
        wp->value_1e -= wp->value_32 / 256;
        wp->value_20 -= wp->value_34 / 256;
    }
    wp->value_24 >>= 1;
}

void func_80045400(CODE43_WORK *wp)
{
    wp->value_26 = rand() & 0x3F;
    wp->index_a  = 0x10;
    wp->routine_8++;
    wp->value_30 = (uint32)-rsin(wp->word_40) >> 9;
    wp->value_32 = (rand() & 3) - 0x14;
    wp->value_34 = (uint32)-rcos(wp->word_40) >> 9;
    wp->value_2c = 0;
    wp->value_28 = 0;
    wp->value_2a = 5;
}

void func_8004548C(CODE43_WORK *wp)
{
    uint16 dx;
    uint16 dy;
    uint16 dz;

    if (func_80049C54(wp->sound_1c, wp->sound_1c, 0, wp->byte_1) == 0)
    {
        wp->u14.word = 0x3D48002E;
        wp->word_18  = 0x2E000000 | (wp->index_a << 3) | (wp->index_a << 11) | (wp->index_a << 19);
        if (wp->index_a-- != 0)
        {
            dx           = wp->value_30 + wp->value_28;
            dy           = wp->value_32 + wp->value_2a;
            wp->value_30 = dx;
            CODE43_HALF_1C(wp) += dx;
            dz = wp->value_34 + wp->value_2c;
            wp->value_1e += dy;
            wp->value_32 = dy;
            wp->value_34 = dz;
            wp->value_20 += dz;
            wp->value_26 += 8;
            return;
        }
    }
    wp->routine_8++;
}

void func_8004557C(CODE43_WORK *wp)
{
    func_80031988(wp);
}

void func_8004559C(CODE43_WORK *wp)
{
    wp->value_22 = D_80097E08[wp->routine_8 - 5].a;
    wp->value_23 = D_80097E08[wp->routine_8 - 5].b;
    wp->routine_8++;
    Sound_call2(0x121, wp->sound_1c);
}

void func_80045608(CODE43_WORK *wp)
{
    wp->value_22 = D_80097E08[wp->routine_8 - 5].a;
    wp->value_23 = D_80097E08[wp->routine_8 - 5].b;
    wp->routine_8++;
}

void func_80045650(CODE43_WORK *wp)
{
    wp->value_22  = D_80097E08[wp->routine_8 - 5].a;
    wp->value_23  = D_80097E08[wp->routine_8 - 5].b;
    wp->routine_8 = 4;
}

void func_8004569C(CODE43_WORK *wp)
{
    D_8008A358[wp->routine_8](wp);
}
