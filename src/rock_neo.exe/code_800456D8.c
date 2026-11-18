#include "common.h"
#include "code_800456d8.h"
#include "player.h"

// Small data reached through $gp
sint32 D_800986D0;

void func_800456D8(CODE456_WORK *wp)
{
    if (rand() & 1)
    {
        wp->routine_0 |= 2;
    }
    func_8002F9C4(wp, &wp->flag_3);
    wp->routine_8++;
    Sound_call2(0x9B, &wp->snd_38.args);
    func_80045AB4(wp);
    func_80045BC8(wp);
}

void func_80045750(CODE456_WORK *wp)
{
    PL_SHORT_VECTOR cur;
    PL_SHORT_VECTOR old;
    sint32 hit;

    old = wp->snd_38.pos;
    wp->mtx_18.tr.h.tx_lo += wp->mtx_18.tr.h.ty_hi;
    wp->snd_38.half[0] += wp->mtx_18.tr.h.tx_lo;
    wp->mtx_18.tr.h.value_2e += wp->mtx_18.tr.h.value_34;
    wp->snd_38.half[1] += wp->mtx_18.tr.h.value_2e;
    wp->mtx_18.tr.h.ty_lo += wp->mtx_18.tr.h.tz_hi;
    wp->snd_38.half[2] += wp->mtx_18.tr.h.ty_lo;
    cur = wp->snd_38.pos;
    func_80045AB4(wp);
    hit = func_8004B5CC(&cur, &old, 1, &D_8008A310[wp->value_a]);
    if (hit)
    {
        wp->snd_38.pos.x = cur.x;
        wp->snd_38.pos.y = cur.y;
        wp->snd_38.pos.z = cur.z;
        if (hit & 0x1000)
        {
            wp->snd_38.half[3] = (sint16)wp->snd_38.half[3] >> 1;
            if ((wp->mtx_18.tr.h.value_2e >> 1) < 2)
            {
                wp->timer_b = 1;
                wp->routine_8++;
                wp->mtx_18.tr.h.value_2e = 0;
                wp->mtx_18.m[2][1]       = 0;
                wp->mtx_18.m[2][0]       = 0;
                wp->mtx_18.m[1][2]       = 0;
                wp->mtx_18.m[1][0]       = 0;
                wp->mtx_18.m[0][2]       = 0;
                wp->mtx_18.m[0][1]       = 0;
                wp->mtx_18.m[0][0] = wp->mtx_18.m[1][1] = wp->mtx_18.m[2][2] = wp->snd_38.half[3];
                RotMatrixY(wp->rot_c, &wp->mtx_18);
            }
            wp->mtx_18.tr.h.value_2e >>= 1;
        }
        func_8004AC8C(&wp->mtx_18.tr.h.tx_lo, hit);
    }
    func_80045BC8(wp);
}

void func_80045918(CODE456_WORK *wp)
{
    if (--wp->timer_b == 0)
    {
        wp->routine_8 += 2;
    }
}

void func_8004594C(CODE456_WORK *wp)
{
    if (--wp->timer_b == 0)
    {
        wp->routine_8++;
    }
}

void func_80045980(CODE456_WORK *wp)
{
    func_80031988(wp);
}

void func_800459A0(CODE456_WORK *wp)
{
    wp->mtx_18.tr.h.value_2e = -0x28;
    wp->mtx_18.tr.h.value_34 = 5;
    wp->routine_8++;
}

void func_800459C0(CODE456_WORK *wp)
{
    wp->mtx_18.m[2][1] = 0;
    wp->mtx_18.m[2][0] = 0;
    wp->mtx_18.m[1][2] = 0;
    wp->mtx_18.m[1][0] = 0;
    wp->mtx_18.m[0][2] = 0;
    wp->mtx_18.m[0][1] = 0;
    wp->mtx_18.m[0][0] = wp->mtx_18.m[2][2] = (sint16)wp->snd_38.half[3] >> 1;
    wp->mtx_18.m[1][1]                      = wp->snd_38.half[3];
    RotMatrixY(0x180, &wp->mtx_18);
    wp->mtx_18.tr.h.value_2e += wp->mtx_18.tr.h.value_34;
    wp->snd_38.half[1] += wp->mtx_18.tr.h.value_2e;
    wp->snd_38.half[3] -= D_80097E64[wp->value_a] >> 3;
    if (wp->mtx_18.tr.h.value_2e >= 0)
    {
        wp->routine_8++;
    }
}

void func_80045A7C(CODE456_WORK *wp)
{
    Sound_call2(0xCF, &wp->snd_38.args);
    func_80031988(wp);
}

void func_80045AB4(CODE456_WORK *wp)
{
    CODE456_SVECTOR rot;
    CODE456_MTX m;
    CODE456_VECTOR scale;
    sint32 r;

    m      = wp->mtx_18;
    r      = rand();
    rot.vx = wp->rot_e += 0x80 + (r & 0x7F);
    rot.vy = wp->rot_c += 0x40 + (r & 0x3F);
    rot.vz = 0;
    RotMatrix(&rot, &m);
    scale.vx = scale.vy = scale.vz = (sint16)wp->snd_38.half[3];
    ScaleMatrix(&m, &scale);
    wp->mtx_18 = m;
}

void func_80045BC8(CODE456_WORK *wp)
{
    uint32 r = D_80097E70[wp->value_a];

    if (Player_work.position.x - wp->snd_38.pos.x + r + 0x32 <= r * 2 + 0x64 &&
        Player_work.position.z - wp->snd_38.pos.z + r + 0x32 <= r * 2 + 0x64 &&
        Player_work.position.y - wp->snd_38.pos.y + r <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
    }
    if (Player_work2.position.x - wp->snd_38.pos.x + r + 0x32 <= r * 2 + 0x64 &&
        Player_work2.position.z - wp->snd_38.pos.z + r + 0x32 <= r * 2 + 0x64 &&
        Player_work2.position.y - wp->snd_38.pos.y + r <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
    }
}

// The clamp copies the parameter into count in its else arm; that puts count's entry copy
// after weights' and kind's, as in retail's prologue.
void func_80045CE8(PL_SHORT_VECTOR *pos, uint32 num, uint32 weights, uint32 kind)
{
    CODE456_WORK *wp;
    uint32 i;
    uint32 angle;
    uint32 step;
    uint32 r;
    uint32 sum;
    uint8 size;
    uint32 pick;
    uint32 count;

    if (num > 16)
    {
        count = 16;
    }
    else
    {
        count = num;
    }
    if (kind > 5)
    {
        kind = 5;
    }
    step  = D_80097E7A[count];
    angle = rand() & 0xFFF;
    for (i = 0; i < count; i++, angle += step)
    {
        wp = func_80031618();
        if (wp == NULL)
        {
            continue;
        }
        wp->routine_0 = 5;
        wp->flag_3    = 0;
        wp->index_2   = 0x86;
        pick          = rand() & 0xFF;
        sum           = weights >> 24;
        if (pick < sum)
        {
            wp->model_44  = D_8009A5A0;
            wp->routine_9 = 0;
        }
        else if (pick < (sum += (weights >> 16) & 0xFF))
        {
            wp->model_44  = D_8009A5D0;
            wp->routine_9 = 1;
        }
        else if (pick < (sum += (weights >> 8) & 0xFF))
        {
            wp->model_44  = D_8009A600;
            wp->routine_9 = 2;
        }
        else if (pick < (sum += weights & 0xFF))
        {
            wp->model_44  = D_8009A630;
            wp->routine_9 = 3;
        }
        else
        {
            wp->flag_3    = 1;
            wp->model_44  = D_8009A660;
            wp->routine_9 = 4;
        }
        wp->snd_38.pos           = *pos;
        r                        = rand();
        size                     = D_8008A2B0[kind][r & 0xF];
        wp->value_a              = size;
        wp->snd_38.half[3]       = D_80097E64[size];
        wp->rot_c                = r & 0xFFF;
        wp->rot_e                = r >> 4;
        wp->mtx_18.tr.h.tx_lo    = (rcos(angle) * (D_80097E9C[size] + (r & 3))) >> 12;
        wp->mtx_18.tr.h.value_2e = D_80097EA8[size] + (r & 3);
        wp->mtx_18.tr.h.ty_lo    = (rsin(angle) * (D_80097E9C[size] + (r & 3))) >> 12;
        wp->mtx_18.tr.h.ty_hi    = 0;
        wp->mtx_18.tr.h.tz_hi    = 0;
        wp->mtx_18.tr.h.value_34 = 5;
        switch (rand() & 3)
        {
            case 0:
                wp->color_40 = 0x606060;
                break;
            case 1:
                wp->color_40 = 0x8080;
                break;
            case 2:
                wp->color_40 = 0x20;
                break;
            case 3:
                wp->color_40 = 0x200000;
                break;
        }
    }
}

// The table entry is selected and never used; only the switch's copy of the
// result (move v1,v0) survives in retail.
void func_80045FE4(CODE456_WORK *wp)
{
    CODE456_ENTRY *ent;

    switch (func_8002FE74(wp->id_1))
    {
        case 0x40:
            ent = D_8009884C[wp->index_2];
            break;
        case 0x20:
            ent = D_80098844[wp->index_2];
            break;
        case 0x60:
            ent = D_80098928[wp->index_2];
            break;
        case 0xE0:
            ent = D_8009892C[wp->index_2];
            break;
    }
}

// The table entry is selected and never used; only the switch's copy of the
// result (move v1,v0) survives in retail.
void func_80046008(CODE456_WORK *wp)
{
    CODE456_ENTRY *ent;

    switch (func_8002FE74(wp->id_1))
    {
        case 0x40:
            ent = D_8009884C[wp->index_2];
            break;
        case 0x20:
            ent = D_80098844[wp->index_2];
            break;
        case 0x60:
            ent = D_80098928[wp->index_2];
            break;
        case 0xE0:
            ent = D_8009892C[wp->index_2];
            break;
    }
}

void func_8004602C(CODE456_WORK *wp)
{
    uint16 uv0;
    uint16 uv1;
    uint16 uv2;
    uint16 uv3;
    uint32 xy1;
    uint32 *p;

    if (D_800986D0 != CODE456_FRAME)
    {
        func_80046F38();
    }
    D_8008A6A8[wp->routine_8](wp);
    if (wp->flag_3 != 0 && (wp->routine_0 & 2) && wp->routine_8 < 5)
    {
        if (++wp->routine_9 >= 4)
        {
            wp->routine_9 = 0;
        }
        uv0  = D_80097EC0[wp->routine_9][0];
        uv1  = D_80097EC0[wp->routine_9][1];
        uv2  = D_80097EC0[wp->routine_9][2];
        uv3  = D_80097EC0[wp->routine_9][3];
        p    = func_8002D464();
        p[1] = 0x2C808080;
        p[2] = wp->snd_38.word[0];
        xy1  = wp->snd_38.word[1];
        p[3] = uv0 | 0x3D080000;
        p[5] = uv1 | 0xE0000;
        p[7] = uv2;
        p[9] = uv3;
        p[4] = xy1;
        p[6] = D_80097EE8[wp->value_a];
        p[8] = 0;
    }
}

void func_800461A4(CODE456_WORK *wp)
{
    wp->routine_0 |= 2;
    func_8002F9C4(wp, &wp->flag_3);
    wp->routine_8++;
    Sound_call2(0x9B, &wp->snd_38.args);
    if (wp->flag_3)
    {
        func_80046890(wp);
    }
    else
    {
        func_800469A4(wp);
    }
    func_80046A0C(wp);
    wp->timer_b = 0xFF;
}

void func_8004622C(CODE456_WORK *wp)
{
    PL_SHORT_VECTOR cur;
    PL_SHORT_VECTOR old;
    sint32 hit;

    old = wp->snd_38.pos;
    wp->mtx_18.tr.h.tx_lo += wp->mtx_18.tr.h.ty_hi;
    wp->snd_38.half[0] += wp->mtx_18.tr.h.tx_lo;
    wp->mtx_18.tr.h.value_2e += wp->mtx_18.tr.h.value_34;
    wp->snd_38.half[1] += wp->mtx_18.tr.h.value_2e;
    wp->mtx_18.tr.h.ty_lo += wp->mtx_18.tr.h.tz_hi;
    wp->snd_38.half[2] += wp->mtx_18.tr.h.ty_lo;
    cur = wp->snd_38.pos;
    if (wp->flag_3)
    {
        func_80046890(wp);
    }
    else
    {
        func_800469A4(wp);
    }
    hit = func_8004B5CC(&cur, &old, 1, &D_8008A618[wp->flag_3][wp->value_a]);
    if (hit)
    {
        wp->snd_38.pos.x = cur.x;
        wp->snd_38.pos.y = cur.y;
        wp->snd_38.pos.z = cur.z;
        if ((hit & 0x1000) || --wp->timer_b == 0)
        {
            if ((wp->mtx_18.tr.h.value_2e >> 1) < 2)
            {
                wp->timer_b = 150;
                wp->routine_8++;
                wp->mtx_18.tr.h.value_2e = 0;
                wp->mtx_18.m[2][1]       = 0;
                wp->mtx_18.m[2][0]       = 0;
                wp->mtx_18.m[1][2]       = 0;
                wp->mtx_18.m[1][0]       = 0;
                wp->mtx_18.m[0][2]       = 0;
                wp->mtx_18.m[0][1]       = 0;
                wp->mtx_18.m[0][0] = wp->mtx_18.m[1][1] = wp->mtx_18.m[2][2] = wp->snd_38.half[3];
                RotMatrixY(wp->rot_c, &wp->mtx_18);
            }
            wp->mtx_18.tr.h.value_2e >>= 1;
        }
        func_8004AC8C(&wp->mtx_18.tr.h.tx_lo, hit);
    }
    func_80046A0C(wp);
}

// The difference gets its own variable (it then takes r's register), computed before the
// position copy.
void func_80046438(CODE456_WORK *wp)
{
    PL_SHORT_VECTOR old;
    sint32 r;
    sint32 lim;
    sint32 diff;

    if (--wp->timer_b == 0)
    {
        wp->routine_8++;
        wp->timer_b = (rand() & 7) + 30;
    }
    r   = func_80048EA4(&wp->snd_38, &D_8008A618[wp->flag_3][wp->value_a], wp->mtx_18.tr.h.value_2e,
                        0xFFFF);
    lim = D_8008A618[wp->flag_3][wp->value_a].h[5];
    lim++;
    diff = r - lim;
    old  = wp->snd_38.pos;
    if (diff > wp->snd_38.pos.y)
    {
        wp->mtx_18.tr.h.value_2e += wp->mtx_18.tr.h.value_34;
        wp->snd_38.pos.y += wp->mtx_18.tr.h.value_2e;
    }
    func_8004B5CC(&wp->snd_38, &old, 1, &D_8008A618[wp->flag_3][wp->value_a]);
    func_80046A0C(wp);
    if (wp->flag_3 == 0)
    {
        func_800469A4(wp);
    }
}

// Same difference form as func_80046438.
void func_800465C8(CODE456_WORK *wp)
{
    PL_SHORT_VECTOR old;
    sint32 r;
    sint32 lim;
    sint32 diff;

    wp->routine_0 ^= 2;
    if (--wp->timer_b == 0)
    {
        wp->routine_8++;
    }
    r   = func_80048EA4(&wp->snd_38, &D_8008A618[wp->flag_3][wp->value_a], wp->mtx_18.tr.h.value_2e,
                        0xFFFF);
    lim = D_8008A618[wp->flag_3][wp->value_a].h[5];
    lim++;
    diff = r - lim;
    old  = wp->snd_38.pos;
    if (diff > wp->snd_38.pos.y)
    {
        wp->mtx_18.tr.h.value_2e += wp->mtx_18.tr.h.value_34;
        wp->snd_38.pos.y += wp->mtx_18.tr.h.value_2e;
    }
    func_8004B5CC(&wp->snd_38, &old, 1, &D_8008A618[wp->flag_3][wp->value_a]);
    func_80046A0C(wp);
    if (wp->flag_3 == 0)
    {
        func_800469A4(wp);
    }
}

void func_8004674C(CODE456_WORK *wp)
{
    func_80031988(wp);
}

void func_8004676C(CODE456_WORK *wp)
{
    wp->mtx_18.tr.h.value_2e = -0x28;
    wp->mtx_18.tr.h.value_34 = 5;
    wp->routine_8++;
}

void func_8004678C(CODE456_WORK *wp)
{
    wp->mtx_18.m[2][1] = 0;
    wp->mtx_18.m[2][0] = 0;
    wp->mtx_18.m[1][2] = 0;
    wp->mtx_18.m[1][0] = 0;
    wp->mtx_18.m[0][2] = 0;
    wp->mtx_18.m[0][1] = 0;
    wp->mtx_18.m[0][0] = wp->mtx_18.m[2][2] = (sint16)wp->snd_38.half[3] >> 1;
    wp->mtx_18.m[1][1]                      = wp->snd_38.half[3];
    RotMatrixY(0x180, &wp->mtx_18);
    wp->mtx_18.tr.h.value_2e += wp->mtx_18.tr.h.value_34;
    wp->snd_38.half[1] += wp->mtx_18.tr.h.value_2e;
    wp->snd_38.half[3] -= D_80097EE0[wp->value_a] >> 3;
    if (wp->mtx_18.tr.h.value_2e >= 0)
    {
        wp->routine_8++;
    }
}

void func_80046848(CODE456_WORK *wp)
{
    Sound_call2(wp->flag_3 ? 0x9E : 0x9D, &wp->snd_38.args);
    func_80031988(wp);
}

void func_80046890(CODE456_WORK *wp)
{
    CODE456_SVECTOR rot;
    CODE456_MTX m;
    CODE456_VECTOR scale;
    sint32 r;

    m      = wp->mtx_18;
    r      = rand();
    rot.vx = wp->rot_e += 0x80 + (r & 0x7F);
    rot.vy = wp->rot_c += 0x40 + (r & 0x3F);
    rot.vz = 0;
    RotMatrix(&rot, &m);
    scale.vx = scale.vy = scale.vz = (sint16)wp->snd_38.half[3];
    ScaleMatrix(&m, &scale);
    wp->mtx_18 = m;
}

void func_800469A4(CODE456_WORK *wp)
{
    wp->mtx_18.m[2][1] = 0;
    wp->mtx_18.m[2][0] = 0;
    wp->mtx_18.m[1][2] = 0;
    wp->mtx_18.m[1][0] = 0;
    wp->mtx_18.m[0][2] = 0;
    wp->mtx_18.m[0][1] = 0;
    wp->mtx_18.m[0][0] = wp->mtx_18.m[1][1] = wp->mtx_18.m[2][2] = wp->snd_38.half[3];
    RotMatrixY(wp->rot_c, &wp->mtx_18);
    wp->rot_c += 0x100;
}

void func_80046A0C(CODE456_WORK *wp)
{
    uint32 r;
    uint8 idx = wp->value_a;

    r = D_80097EEC[wp->flag_3][idx];

    if (Player_work.position.x - wp->snd_38.pos.x + r + 0x32 <= r * 2 + 0x64 &&
        Player_work.position.z - wp->snd_38.pos.z + r + 0x32 <= r * 2 + 0x64 &&
        Player_work.position.y - wp->snd_38.pos.y + r <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
        if (wp->flag_3 == 0)
        {
            func_80043294(D_8008A678[Game_work.option_5b][idx], 0, 0);
        }
        else
        {
            func_80043340(D_8008A680[Game_work.option_5b][idx], 0);
        }
    }
}

// The count's mask is written in the test and again in the assignment: CSE keeps it in v0 and
// copies it to s7, as retail does (a plain count = arg & 0xFF folds the andi into s7).
void func_80046B34(PL_SHORT_VECTOR *pos, uint32 arg)
{
    uint32 count;
    CODE456_WORK *wp;
    uint32 kind;
    uint32 count2;
    uint32 kind2;
    uint32 i;
    uint32 angle;
    uint32 step;
    uint32 size;
    uint32 r;

    kind   = (arg >> 8) & 0xFF;
    count2 = (arg >> 16) & 0xFF;
    kind2  = arg >> 24;
    if ((arg & 0xFF) > 16)
    {
        count = 16;
    }
    else
    {
        count = arg & 0xFF;
    }
    step  = D_80097EFA[count];
    angle = rand() & 0xFFF;
    for (i = 0; i < count; i++, angle += step)
    {
        wp = func_80031618();
        if (wp == NULL)
        {
            continue;
        }
        wp->routine_0 = 0x15;
        wp->flag_3    = 0;
        wp->index_2   = 0x87;
        rand();
        wp->routine_9  = 0;
        wp->snd_38.pos = *pos;
        wp->snd_38.half[1] -= 20;
        r    = rand();
        size = D_8008A5A8[kind][r & 0xF];
        if (size >= 5)
        {
            func_80031988(wp);
            continue;
        }
        wp->model_44             = D_8009A6C0[size];
        wp->value_a              = size;
        wp->snd_38.half[3]       = D_80097EE0[size];
        wp->rot_c                = r & 0xFFF;
        wp->rot_e                = r >> 4;
        wp->mtx_18.tr.h.tx_lo    = (rcos(angle) * (D_80097F1C[size] + (r & 3))) >> 12;
        wp->mtx_18.tr.h.value_2e = D_80097F24[size] + (r & 3);
        wp->mtx_18.tr.h.ty_lo    = (rsin(angle) * (D_80097F1C[size] + (r & 3))) >> 12;
        wp->mtx_18.tr.h.value_34 = 5;
        wp->mtx_18.tr.h.ty_hi    = 0;
        wp->mtx_18.tr.h.tz_hi    = 0;
        wp->color_40             = 0x2808080;
        wp->mtx_18.m[2][1]       = 0;
        wp->mtx_18.m[2][0]       = 0;
        wp->mtx_18.m[1][2]       = 0;
        wp->mtx_18.m[1][0]       = 0;
        wp->mtx_18.m[0][2]       = 0;
        wp->mtx_18.m[0][1]       = 0;
        wp->mtx_18.m[0][0] = wp->mtx_18.m[1][1] = wp->mtx_18.m[2][2] = wp->snd_38.half[3];
    }
    count = count2;
    if (count > 16)
    {
        count = 16;
    }
    step  = D_80097EFA[count];
    angle = (angle + 0x800) & 0xFFF;
    for (i = 0; i < count; i++, angle += step)
    {
        wp = func_80031618();
        if (wp == NULL)
        {
            continue;
        }
        wp->routine_0 = 0x19;
        wp->flag_3    = 1;
        wp->index_2   = 0x87;
        rand();
        wp->model_44   = D_8009A710;
        wp->routine_9  = 0;
        wp->snd_38.pos = *pos;
        r              = rand();
        size           = D_8008A5A8[kind2][r & 0xF];
        if (size >= 5)
        {
            func_80031988(wp);
            continue;
        }
        wp->value_a              = size;
        wp->snd_38.half[3]       = D_80097EE0[size];
        wp->rot_c                = r & 0xFFF;
        wp->rot_e                = r >> 4;
        wp->mtx_18.tr.h.tx_lo    = (rcos(angle) * (D_80097F1C[size] + (r & 3))) >> 12;
        wp->mtx_18.tr.h.value_2e = D_80097F24[size] + (r & 3);
        wp->mtx_18.tr.h.ty_lo    = (rsin(angle) * (D_80097F1C[size] + (r & 3))) >> 12;
        wp->mtx_18.tr.h.ty_hi    = 0;
        wp->mtx_18.tr.h.tz_hi    = 0;
        wp->mtx_18.tr.h.value_34 = 5;
        wp->color_40             = 0x2202020;
    }
}

void func_80046F38(void)
{
    uint32 frame;
    uint32 i;
    uint32 *dst;

    dst        = D_8009A6C0[0];
    frame      = CODE456_FRAME;
    D_800986D0 = frame;
    dst[0]     = D_8008A378[0][frame & 0x1F];
    dst[1]     = D_8008A378[0][(frame + 10) & 0x1F];
    dst[2]     = D_8008A378[0][(frame + 20) & 0x1F];
    dst[3]     = D_8008A378[0][(frame + 30) & 0x1F];
    dst[4]     = D_8008A378[0][(frame + 40) & 0x1F];
    dst += 5;
    dst[0] = D_8008A378[1][frame & 0x1F];
    dst[1] = D_8008A378[1][(frame + 10) & 0x1F];
    dst[2] = D_8008A378[1][(frame + 20) & 0x1F];
    dst[3] = D_8008A378[1][(frame + 30) & 0x1F];
    dst[4] = D_8008A378[1][(frame + 40) & 0x1F];
    dst += 5;
    dst[0] = D_8008A378[2][frame & 0x1F];
    dst[1] = D_8008A378[2][(frame + 10) & 0x1F];
    dst[2] = D_8008A378[2][(frame + 20) & 0x1F];
    dst[3] = D_8008A378[2][(frame + 30) & 0x1F];
    dst[4] = D_8008A378[2][(frame + 40) & 0x1F];
    dst += 5;
    dst[0] = D_8008A378[3][frame & 0x1F];
    dst[1] = D_8008A378[3][(frame + 10) & 0x1F];
    dst[2] = D_8008A378[3][(frame + 20) & 0x1F];
    dst[3] = D_8008A378[3][(frame + 30) & 0x1F];
    dst[4] = D_8008A378[3][(frame + 40) & 0x1F];
    dst    = D_8009A710[0];
    for (i = 0; i < 6; i++)
    {
        dst[0] = D_8008A578[i];
        dst[1] = D_8008A578[i];
        dst[2] = D_8008A578[i];
        dst[3] = D_8008A578[i];
        dst += 4;
    }
}

void func_80047148(CODE456_WORK *wp, void *obj)
{
    switch (func_8002FE74(wp->id_1))
    {
        case 0x40:
            func_80046B34(obj, D_8009884C[wp->index_2][0].word);
            break;
        case 0x20:
            func_80046B34(obj, D_80098844[wp->index_2][0].word);
            break;
        case 0x60:
            func_80046B34(obj, D_80098928[wp->index_2][0].word);
            break;
        case 0xE0:
            func_80046B34(obj, D_8009892C[wp->index_2][0].word);
            break;
    }
}

void func_80047228(CODE456_WORK *wp, void *obj, sint32 n)
{
    CODE456_ENTRY *ent;

    switch (func_8002FE74(wp->id_1))
    {
        case 0x40:
            ent = D_8009884C[wp->index_2] + n;
            break;
        case 0x20:
            ent = D_80098844[wp->index_2] + n;
            break;
        case 0x60:
            ent = D_80098928[wp->index_2] + n;
            break;
        case 0xE0:
            ent = D_8009892C[wp->index_2] + n;
            break;
        default:
            return;
    }
    func_80046B34(obj, ent->word);
}

void func_80047318(CODE456_WORK *wp)
{
    D_8008A708[wp->routine_8](wp);
}

// Every path makes its own func_8002F9C4 call, the default's in each arm of its test.
// Cross-jumping then merges the calls into the default's last one and leaves each path its own
// argument store (retail's separate "j; sw" blocks for the 0x80 path and cases 4, 5 and 6).
void func_80047354(CODE456_BOX *wp)
{
    CODE456_BOX *child;
    sint32 arg;
    sint16 *size;

    if (wp->flag_3 == 0xFF)
    {
        wp->routine_0 = 3;
        wp->m18.w[0]  = 0x2C808080;
        wp->routine_8 = 3;
        wp->m18.w[1]  = wp->snd_38.word[0];
        wp->m18.h[4]  = wp->snd_38.half[2];
        func_80047C84((CODE456_ANIM *)wp);
        func_80045CE8(&wp->snd_38.pos, 3, 0x40404040, 1);
        return;
    }
    if (wp->flag_3 == 0xFE)
    {
        wp->sound_c = 0;
        wp->flag_3  = 0xC2;
    }
    else
    {
        wp->sound_c = 1;
    }
    wp->routine_0 |= 2;
    size = wp->size_44;
    switch (wp->flag_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            size[0]      = 0x37;
            size[1]      = -5;
            wp->color_40 = 0x2808080;
            break;
        case 1:
            size[0]      = 0x37;
            size[1]      = -5;
            wp->color_40 = 0x2808080;
            break;
        case 2:
            size[0]      = 0x46;
            size[1]      = -5;
            wp->color_40 = 0x2808080;
            break;
        case 4:
            size[0]      = 0x8C;
            size[1]      = -5;
            wp->color_40 = 0x2808080;
            break;
        case 5:
            size[0]      = 0xAE;
            size[1]      = -6;
            wp->color_40 = 0x2808080;
            break;
        case 6:
            size[0]      = 0x118;
            size[1]      = 0;
            wp->color_40 = 0x2808080;
            break;
    }
    wp->value_a        = 0;
    wp->snd_38.half[3] = 0;
    wp->m18.w[0]       = 0x1000;
    wp->m18.w[1]       = 0;
    wp->m18.w[2]       = 0x1000;
    wp->m18.w[3]       = 0;
    wp->m18.w[4]       = 0x1000;
    wp->m18.w[5]       = 0;
    wp->m18.w[6]       = 0;
    wp->m18.w[7]       = 0;
    wp->m18.h[8]       = 0;
    wp->m18.h[4]       = 0;
    wp->m18.h[0]       = 0;
    if (wp->flag_3 & 0x80)
    {
        arg = 0;
        func_8002F9C4(wp, (uint8 *)&arg);
    }
    else if (wp->flag_3 & 0x20)
    {
        arg = 2;
        func_8002F9C4(wp, (uint8 *)&arg);
        func_800398E0(0x1E);
        child = (CODE456_BOX *)func_80031618();
        if (child != NULL)
        {
            child->routine_0  = 5;
            child->index_2    = 0x80;
            child->flag_3     = 5;
            child->snd_38.pos = wp->snd_38.pos;
        }
        child = (CODE456_BOX *)func_80031618();
        if (child != NULL)
        {
            child->routine_0  = 5;
            child->index_2    = 0x80;
            child->flag_3     = 6;
            child->snd_38.pos = wp->snd_38.pos;
        }
    }
    else
    {
        switch (wp->flag_3 & 0xF)
        {
            case 4:
                arg = 4;
                func_8002F9C4(wp, (uint8 *)&arg);
                break;
            case 5:
                arg = 5;
                func_8002F9C4(wp, (uint8 *)&arg);
                break;
            case 6:
                arg = 6;
                func_8002F9C4(wp, (uint8 *)&arg);
                break;
            default:
                if (func_8004920C(&wp->snd_38) - wp->snd_38.pos.y < 30)
                {
                    arg = 0;
                    func_8002F9C4(wp, (uint8 *)&arg);
                }
                else
                {
                    arg = 1;
                    func_8002F9C4(wp, (uint8 *)&arg);
                }
                break;
        }
    }
    wp->routine_8++;
    wp->timer_b = 0;
    arg = func_80047BF8((CODE456_SVECTOR *)&wp->snd_38, (CODE456_SVECTOR *)&Player_work.position);
    if (wp->sound_c)
    {
        Sound_call2(0xA1, &wp->snd_38.args);
    }
}

void func_800476A4(CODE456_WORK *wp)
{
    D_8008A718[wp->routine_9](wp);
    if (wp->flag_3 & 0x40)
    {
        func_800341BC(&wp->snd_38, (sint16)wp->snd_38.half[3] / 2, 0, 0xA000, wp->id_1, D_800986D8,
                      0x10000008, 0, 0x80);
    }
    else if (wp->flag_3 == 6)
    {
        func_800341BC(&wp->snd_38, (sint16)wp->snd_38.half[3] / 2, 0, 0xC000, wp->id_1, D_800986D8,
                      0x30000000, 0, 0x80);
    }
    else
    {
        func_800341BC(&wp->snd_38, (sint16)wp->snd_38.half[3] / 2, 0, 0xC000, wp->id_1, D_800986D8,
                      0x10000008, 0, 0x80);
    }
}

void func_800477A0(CODE456_BOX *wp)
{
    sint16 *v;
    sint32 c;

    v = wp->size_44;
    switch (wp->flag_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            v[0] += v[1];
            wp->snd_38.half[3] += v[0];
            if (v[0] <= 0)
            {
                if ((sint16)wp->snd_38.half[3] < 100)
                {
                    wp->routine_8++;
                    wp->snd_38.half[3] = 0;
                }
                v[1] = 0;
                v[0] = -10;
                if ((sint16)wp->snd_38.half[3] >= 0x100)
                {
                    c = 0x80;
                }
                else
                {
                    c = (sint16)wp->snd_38.half[3] - 100;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->color_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 1:
            v[0] += v[1];
            wp->snd_38.half[3] += v[0];
            if ((sint16)wp->snd_38.half[3] < 0)
            {
                wp->routine_8++;
                wp->snd_38.half[3] = 0;
            }
            c = 0x80;
            if (v[0] <= 0 && (sint16)wp->snd_38.half[3] < 0x100)
            {
                c = (sint16)wp->snd_38.half[3] >> 1;
            }
            wp->color_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 2:
            v[0] += v[1];
            wp->snd_38.half[3] += v[0];
            if (v[0] <= 0)
            {
                wp->routine_8++;
                wp->snd_38.half[3] = 0;
            }
            if ((sint16)wp->snd_38.half[3] >= 0x10F)
            {
                wp->value_a += 14;
                if (wp->value_a <= 0x80)
                {
                    c = 0x80 - wp->value_a;
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
            wp->color_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 4:
            v[0] += v[1];
            wp->snd_38.half[3] += v[0];
            if (v[0] <= 0)
            {
                if ((sint16)wp->snd_38.half[3] < 100)
                {
                    wp->routine_8++;
                    wp->snd_38.half[3] = 0;
                }
                v[1] = 0;
                v[0] = -20;
                if ((sint16)wp->snd_38.half[3] > 0x400)
                {
                    c = 0x80;
                }
                else
                {
                    c = (sint16)wp->snd_38.half[3] >> 3;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->color_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 5:
            v[0] += v[1];
            wp->snd_38.half[3] += v[0];
            if (v[0] < 0x82)
            {
                wp->value_a++;
            }
            if (wp->value_a >= 8)
            {
                wp->value_a = 8;
                wp->routine_8++;
            }
            c            = (8 - wp->value_a) * 16;
            wp->color_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            break;
        case 6:
            v[0] += v[1];
            wp->snd_38.half[3] += v[0];
            if ((sint16)wp->snd_38.half[3] > 0x800)
            {
                wp->value_a += 10;
                if (wp->value_a <= 0x80)
                {
                    c = 0x80 - wp->value_a;
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
            wp->color_40 = (c | 0x2000000 | (c << 8)) | (c << 16);
            if (c == 0)
            {
                wp->routine_8++;
                wp->snd_38.half[3] = 0;
            }
            break;
    }
    wp->m18.w[0] = 0x1000;
    wp->m18.w[2] = 0x1000;
    wp->m18.w[4] = 0x1000;
    wp->m18.w[1] = 0;
    wp->m18.w[3] = 0;
    wp->m18.w[5] = 0;
    wp->m18.w[6] = 0;
    wp->m18.w[7] = 0;
    wp->m18.h[0] = wp->m18.h[4] = wp->m18.h[8] = wp->snd_38.half[3];
    RotMatrixY(++wp->timer_b << 7, &wp->m18.mtx);
}

void func_80047BC8(void)
{
}

void func_80047BD0(void)
{
}

void func_80047BD8(CODE456_WORK *wp)
{
    func_80031988(wp);
}

sint32 func_80047BF8(CODE456_SVECTOR *a, CODE456_SVECTOR *b)
{
    sint32 dx = a->vx - b->vx;
    sint32 dy = a->vy - b->vy;
    sint32 dz = a->vz - b->vz;

    return SquareRoot0(dx * dx + dy * dy + dz * dz);
}

void func_80047C64(CODE456_ANIM *wp)
{
    func_80047CD8(wp);
}

void func_80047C84(CODE456_ANIM *wp)
{
    wp->step_9   = 0;
    wp->timer_a  = D_8008A6C8[0].timer_5;
    wp->word_14  = D_8008A6C8[0].word;
    wp->value_22 = D_8008A6C8[0].value_6;
    wp->value_23 = D_8008A6C8[0].value_7;
    wp->value_24 = D_8008A6C8[0].value_4;
}

void func_80047CD8(CODE456_ANIM *wp)
{
    uint8 step;

    if (--wp->timer_a == 0)
    {
        wp->step_9++;
        step = wp->step_9;
        if ((wp->timer_a = D_8008A6C8[step].timer_5) == 0)
        {
            func_80031988(wp);
        }
        else
        {
            wp->word_14  = D_8008A6C8[step].word;
            wp->value_22 = D_8008A6C8[step].value_6;
            wp->value_23 = D_8008A6C8[step].value_7;
            wp->value_24 = D_8008A6C8[step].value_4;
        }
    }
}

void func_80047D9C(CODE456_WORK *wp)
{
    D_8008A724[wp->routine_8](wp);
}

void func_80047DD8(CODE456_SPARK *wp)
{
    PL_WORK *pl = &Player_work;
    CODE456_SPARK_DATA *d;
    uint8 i;

    if (func_800482A8(wp) == 0)
    {
        d = &wp->data;
        wp->flags_6 |= 0x20;
        for (i = 0; i < 8; i++)
        {
            d->index[i] = i;
            if (wp->flag_3)
            {
                d->angle[i] = ((uint16)pl->rotation.y + 0x80 + (rand() & 0xFF)) & 0xFFF;
            }
            else
            {
                d->angle[i] = ((sint16)(pl->rotation.y - 0x100) + (rand() & 0xFF)) & 0xFFF;
            }
        }
        Sound_call(0x8D, 0, 0);
        wp->routine_8 = 1;
    }
}

void func_80047EC8(CODE456_SPARK *wp)
{
    uint32 *prim;
    uint16 step;
    CODE456_SPARK_DATA *d;
    sint16 p0[4];
    sint16 p1[4];
    uint16 height;
    uint16 radius;
    sint32 rise;
    uint8 i;
    uint8 j;
    uint8 lit;

    d = &wp->data;
    if (func_800482A8(wp) != 0)
    {
        return;
    }
    if (wp->flag_3)
    {
        wp->x = PL_TABLE_VEC(&Player_work, 11)->x;
        wp->y = PL_TABLE_VEC(&Player_work, 11)->y;
        wp->z = PL_TABLE_VEC(&Player_work, 11)->z;
    }
    else
    {
        wp->x = PL_TABLE_VEC(&Player_work, 14)->x;
        wp->y = PL_TABLE_VEC(&Player_work, 14)->y;
        wp->z = PL_TABLE_VEC(&Player_work, 14)->z;
    }
    for (i = 0; i < 8; i++)
    {
        lit    = 0;
        radius = 5;
        rise   = 0;
        step   = (rand() & 7) | 0x10;
        height = (rand() & 0x3F) + 0x28;
        if (++d->index[i] >= 8)
        {
            d->index[i] = 0;
        }
        if (wp->flag_3)
        {
            d->angle[i] = ((uint16)Player_work.rotation.y + 0x80 + (rand() & 0xFF)) & 0xFFF;
        }
        else
        {
            d->angle[i] = ((sint16)(Player_work.rotation.y - 0x100) + (rand() & 0xFF)) & 0xFFF;
        }
        for (j = 0; j < d->index[i] * 2; j++)
        {
            p0[0] = wp->x + ((rsin(d->angle[i]) * radius) >> 12);
            p0[2] = wp->z + ((rcos(d->angle[i]) * radius) >> 12);
            p0[1] = wp->y - (sint16)(((rsin(rise) * height) >> 12) - 16);
            radius += step;
            rise  = (j + 1) << 6;
            p1[0] = wp->x + ((rsin(d->angle[i]) * radius) >> 12);
            p1[2] = wp->z + ((rcos(d->angle[i]) * radius) >> 12);
            p1[1] = wp->y - (sint16)(((rsin(rise) * height) >> 12) - 16);
            if (rand() & 1)
            {
                prim    = func_8002D4B8();
                prim[0] = (p0[1] << 16) + p0[0];
                prim[1] = 0x52104080;
                prim[2] = (p1[1] << 16) + p1[0];
                prim[3] = lit ? 0x104080 : 0x10101;
                prim[4] = (p0[2] << 16) + p1[2];
                prim[6] = 0xE1000020;
                lit     = 1;
            }
            else
            {
                lit = 0;
            }
        }
    }
    Sound_call(0x8D, 0, 0);
}

void func_80048268(CODE456_WORK *wp)
{
    Sound_call(0x8F, 0, 0);
    wp->routine_0 = 0;
    func_80031988(wp);
}

uint8 func_800482A8(void *vp)
{
    CODE456_WORK *wp = vp;
    uint16 pad;
    uint16 hit;

    if (Player_work.routine_1 == 3)
    {
        if (wp->flag_3)
        {
            pad = Player_work.pad_cur;
            if (!(pad & Player_work.value12a))
            {
                goto fail;
            }
            hit = Player_work.value128 & pad;
        }
        else
        {
            pad = Player_work.pad_cur;
            if (!(pad & Player_work.value128))
            {
                goto fail;
            }
            hit = Player_work.value12a & pad;
        }
        if (hit)
        {
            return 1;
        }
    }
    else
    {
    fail:
        wp->routine_8 = 2;
        return 1;
    }
    return 0;
}

void func_80048354(CODE456_WORK *wp)
{
    D_8008A76C[wp->routine_8](wp);
}

void func_80048390(CODE456_ANIM *wp)
{
    wp->value_24 = 0x20;
    wp->value_c  = -0x80;
    wp->word_14  = 0x3D48002C;
    wp->word_18  = 0x2EC06060;
    wp->index_d  = 0;
    wp->routine_0 |= 0x22;
    if (wp->flag_3)
    {
        wp->value_e  = D_8008A74C[0].v;
        wp->value_22 = D_8008A748[wp->index_d].v;
        wp->value_23 = D_8008A74A[wp->index_d].v;
    }
    else
    {
        wp->value_e  = D_8008A734[0].v;
        wp->value_22 = D_8008A730[wp->index_d].v;
        wp->value_23 = D_8008A732[wp->index_d].v;
    }
    wp->routine_8 = 1;
    wp->timer_b   = 0;
}

void func_80048484(CODE456_ANIM *wp)
{
    if (--wp->value_e == 0)
    {
        if (wp->flag_3)
        {
            wp->value_24 += 8;
            wp->index_d++;
            wp->value_e  = D_8008A74C[wp->index_d].v;
            wp->value_22 = D_8008A748[wp->index_d].v;
            wp->value_23 = D_8008A74A[wp->index_d].v;
        }
        else
        {
            wp->index_d++;
            wp->value_e  = D_8008A734[wp->index_d].v;
            wp->value_22 = D_8008A730[wp->index_d].v;
            wp->value_23 = D_8008A732[wp->index_d].v;
        }
    }
    if ((uint8)wp->value_e == 0x80)
    {
        wp->routine_8 = 2;
    }
}

void func_800485C4(CODE456_WORK *wp)
{
    func_80031988(wp);
}

void func_800485E4(CODE456_WORK *wp)
{
    D_8008A778[wp->routine_4](wp);
}
