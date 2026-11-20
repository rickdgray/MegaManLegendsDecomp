#include "common.h"
#include "st0b.h"

void func_801147FC(STAGE_OBJ *wp)
{
    D_8011BD50[wp->routine_0](wp);
}

void func_80114838(ST0B_SPLASH *wp)
{
    sint32 arg;

    wp->flags_0 |= 2;
    if (wp->variant_3 >= 2)
    {
        wp->routine_0 = 3;
        switch (wp->variant_3 - 2)
        {
            case 0:
            case 1:
                arg = 0;
                break;
            case 2:
                arg = 1;
                break;
            case 3:
                arg           = 0;
                wp->routine_0 = 4;
                break;
        }
        Model_work_init(wp, (uint8 *)&arg);
        wp->matrix.s.w[0]    = 0x1000;
        wp->matrix.s.w[1]    = 0;
        wp->matrix.s.w[2]    = 0x1000;
        wp->matrix.s.w[3]    = 0;
        wp->matrix.s.w[4]    = 0x1000;
        wp->matrix.m.m[0][0] = wp->matrix.m.m[1][1] = wp->matrix.m.m[2][2] = 0;
        wp->color_40                                                       = 0x02808080;
        return;
    }
    wp->matrix.s.size[2] = 0;
    wp->matrix.s.size[0] = D_8011BCD0[wp->variant_3][wp->value_C];
    wp->matrix.s.size[1] = D_8011BCE8[wp->variant_3][wp->value_C];
    if (wp->variant_3 == 0)
    {
        wp->matrix.s.size[3] = D_8011BD00[wp->value_C];
        wp->matrix.s.size[4] = D_8011BD18[wp->variant_3][wp->value_C];
        wp->matrix.s.size[5] = 0;
        Sound_call2(0x14F, &wp->pos_38);
    }
    Model_work_init(wp, &wp->variant_3);
    wp->matrix.s.w[0]    = 0x1000;
    wp->matrix.s.w[2]    = 0x1000;
    wp->matrix.s.w[4]    = 0x1000;
    wp->color_40         = 0x02808080;
    wp->matrix.s.w[1]    = 0;
    wp->matrix.s.w[3]    = 0;
    wp->matrix.m.m[0][0] = wp->matrix.m.m[1][1] = wp->matrix.m.m[2][2] = 0;
    wp->routine_1                                                      = 0;
    wp->routine_2                                                      = 0;
    wp->routine_3                                                      = 0x20;
    wp->routine_0++;
}

void func_80114A14(ST0B_SPLASH *wp)
{
    sint16 *size;
    uint32 c;

    size = wp->matrix.s.size;
    size[0] += size[1];
    size[2] += size[0];
    if (wp->variant_3 == 0)
    {
        size[3] += size[4];
        size[5] += size[3];
    }
    else
    {
        // Refresh color at zero as well as during the fade.
        c = wp->routine_3 << 2;
        if (wp->routine_3 != 0)
        {
            wp->routine_3--;
        }
        wp->color_40 = ((c << 16) | 0x2000000) | (c << 8) | c;
    }
    if (size[5] < 0 || size[0] < 0)
    {
        func_80031988(wp);
        return;
    }
    wp->matrix.s.w[0]    = 0x1000;
    wp->matrix.s.w[2]    = 0x1000;
    wp->matrix.s.w[4]    = 0x1000;
    wp->matrix.s.w[1]    = 0;
    wp->matrix.s.w[3]    = 0;
    wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = size[2];
    wp->matrix.m.m[1][1]                        = size[5];
    RotMatrixY(++wp->routine_1 << 7, &wp->matrix.m);
}

void func_80114B24(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

// Retail keeps the angle (routine_1 << 7) in a1 and copies it to a0 in a delay slot; GCC builds it
// in a0 directly.
void func_80114B44(ST0B_SPLASH *wp)
{
    sint32 h;
    sint32 angle;
    sint32 turn;

    wp->matrix.s.w[0] = 0x1000;
    wp->matrix.s.w[2] = 0x1000;
    wp->matrix.s.w[4] = 0x1000;
    wp->matrix.s.w[1] = 0;
    wp->matrix.s.w[3] = 0;
    if (wp->routine_2 == 0x80)
    {
        h = 0x80;
    }
    else
    {
        h = wp->routine_2 + (0x10 - wp->routine_1);
        if (h >= 0x80)
        {
            h = 0x80;
        }
        wp->routine_2 = h;
    }
    wp->routine_1++;
    angle = wp->routine_1 << 7;
    turn  = angle; // a second variable: retail keeps the angle in a1 and copies it to a0
    switch (wp->variant_3 - 2)
    {
        case 0:
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x300;
            wp->matrix.m.m[1][1]                        = h * 12 + rsin(turn) / 32;
            break;
        case 1:
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x200;
            wp->matrix.m.m[1][1]                        = h * 16 + rcos(turn) / 16;
            break;
        case 2:
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x300;
            break;
    }
    RotMatrixY(wp->routine_1 << 7, &wp->matrix.m);
}

void func_80114C94(ST0B_SPLASH *wp)
{
    uint32 frame;
    uint8 step;

    frame             = wp->routine_1 + 1;
    wp->matrix.s.w[0] = 0x1000;
    wp->matrix.s.w[2] = 0x1000;
    wp->matrix.s.w[4] = 0x1000;
    step              = wp->routine_2;
    wp->matrix.s.w[1] = 0;
    wp->matrix.s.w[3] = 0;
    wp->routine_1     = frame;
    frame             = (uint8)frame;
    switch (wp->variant_3 - 2)
    {
        case 0:
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x300;
            wp->matrix.m.m[1][1]                        = step * 12;
            break;
        case 1:
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x200;
            wp->matrix.m.m[1][1]                        = step << 4;
            break;
        case 2:
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x300;
            break;
        case 3:
            if (frame >= 0x20)
            {
                func_80031988(wp);
                return;
            }
            wp->matrix.m.m[0][0] = wp->matrix.m.m[2][2] = 0x300;
            wp->matrix.m.m[1][1]                        = D_8011BD30[wp->routine_1] << 4;
            break;
    }
    RotMatrixY(wp->routine_1 << 7, &wp->matrix.m);
}

void func_80114DAC(ST0B_RING *wp)
{
    sint32 level;
    sint32 c;
    sint16 size;

    wp->routine_1++;
    level = --wp->routine_2;
    if (level == 0)
    {
        func_80031988(wp);
        return;
    }
    c = level * 8;
    if (wp->variant_3 == 4)
    {
        size        = (wp->routine_1 + 0xC) << 6;
        wp->size_28 = size;
        wp->size_18 = size;
    }
    wp->color_40 = (2 << 24) | (c << 16) | (c << 8) | c;
}

void func_80114E3C(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80114E5C(ST0B_DRIFT *wp)
{
    STCOM23_PACKET *p;
    uint32 uv;

    D_8011BE20[wp->routine_0](wp);
    if (wp->variant_3 != 0)
    {
        p          = func_8002D464();
        p->code_4  = wp->color_18;
        p->xy_8    = *(uint32 *)&wp->x_1C;
        p->z_10    = *(uint32 *)&wp->z_20;
        p->uv_C    = wp->uv_34;
        p->uv_14   = wp->uv_38;
        uv         = wp->uv_3C;
        p->uv_1C   = uv & 0xFFFF;
        p->uv_24   = uv >> 16;
        p->size_18 = wp->size_24;
    }
}

void func_80114F1C(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 0)
    {
        wp->flags_0 |= 2;
    }
    wp->position_prev.z = 0x10;
    wp->routine_0++;
}

void func_80114F54(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    wp->position_fixed.f.x.words.fraction += wp->position_fixed.f.pad.words.fraction;
    temp_v0                                = (uint16)wp->position_fixed.f.pad.words.integer + (uint16)wp->position_prev.y;
    wp->position_fixed.f.pad.words.integer = temp_v0;
    wp->position_fixed.f.x.words.integer += temp_v0;
    wp->position_fixed.f.y.words.fraction += (uint16)wp->position_prev.x;
    if (wp->position_fixed.f.pad.words.integer >= 0)
    {
        wp->routine_0++;
    }
}

void func_80114FB4(ST0B_DRIFT *wp)
{
    sint32 c;

    if (--wp->timer_30 == 0)
    {
        wp->routine_0++;
    }
    c            = wp->timer_30 * 8;
    wp->color_18 = (0x2E << 24) | (c << 16) | (c << 8) | c;
    wp->x_1C += wp->vx_28;
    wp->vy_2A += wp->ay_2E;
    wp->y_1E += wp->vy_2A;
    wp->z_20 += wp->vz_2C;
}

void func_80115048(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80115068(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos)
{
    ST0B_GLOW *fx;
    ST0B_SPARK_B *spark;
    sint32 angle;
    sint32 step;
    sint32 i;

    angle = rand() & 0xFFF;
    step  = 0x1000 / count;
    for (i = 0; i < count; i++)
    {
        fx = (ST0B_GLOW *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0   = 1;
            fx->kind_2    = 0x11;
            fx->variant_3 = textured;
            fx->value_C   = type;
            fx->color_18  = 0x2E808080;
            fx->xy_1C.h.x = pos->x;
            fx->xy_1C.h.y = pos->y;
            fx->z_20.z    = pos->z;
            if (textured != 0)
            {
                spark     = (ST0B_SPARK_B *)&D_8011BE0C[type];
                fx->uv_34 = spark->tex.uv_8;
                fx->uv_38 = spark->tex.uv_C;
                fx->uv_3C = spark->tex.uv_10;
            }
            else
            {
                spark        = (ST0B_SPARK_B *)&D_8011BD6C[type];
                fx->mode_14  = spark->flat.mode_8;
                fx->z_20.b.u = spark->flat.u_C;
                fx->z_20.b.v = spark->flat.v_D;
            }
            fx->vx_28   = (rsin(angle) * spark->head.speed_0) >> 12;
            fx->vz_2C   = (rcos(angle) * spark->head.speed_0) >> 12;
            fx->vy_2A   = spark->head.vy_2;
            fx->ay_2E   = spark->head.ay_4;
            fx->size_24 = spark->head.size_6;
        }
        angle += step + (rand() & 0x3F);
    }
}

void func_80115270(sint32 textured, sint32 type, sint32 count, STCOM_SVECTOR *pos, sint32 start, sint32 end)
{
    ST0B_GLOW *fx;
    ST0B_SPARK_B *spark;
    sint32 angle;
    sint32 step;
    sint32 i;

    angle = start;
    step  = (end - angle) / count;
    for (i = 0; i < count; i++)
    {
        fx = (ST0B_GLOW *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0   = 1;
            fx->kind_2    = 0x11;
            fx->variant_3 = textured;
            fx->value_C   = type;
            fx->color_18  = 0x2E808080;
            fx->xy_1C.h.x = pos->x;
            fx->xy_1C.h.y = pos->y;
            fx->z_20.z    = pos->z;
            if (textured != 0)
            {
                spark     = (ST0B_SPARK_B *)&D_8011BE0C[type];
                fx->uv_34 = spark->tex.uv_8;
                fx->uv_38 = spark->tex.uv_C;
                fx->uv_3C = spark->tex.uv_10;
            }
            else
            {
                spark        = (ST0B_SPARK_B *)&D_8011BD6C[type];
                fx->mode_14  = spark->flat.mode_8;
                fx->z_20.b.u = spark->flat.u_C;
                fx->z_20.b.v = spark->flat.v_D;
            }
            fx->vx_28   = (rsin(angle) * spark->head.speed_0) >> 12;
            fx->vz_2C   = (rcos(angle) * spark->head.speed_0) >> 12;
            fx->vy_2A   = spark->head.vy_2;
            fx->ay_2E   = spark->head.ay_4;
            fx->size_24 = spark->head.size_6;
        }
        angle += step + (rand() & 0x3F);
    }
}

void func_80115478(STAGE_OBJ *wp)
{
    STAGE_OBJ *owner;

    owner = func_80036294(wp->u_C.b.byte_C);
    if (STAGE_GAME.value_50 != 0xD || owner->u_C.b.byte_C != 0)
    {
        D_8011BE48[wp->variant_3](wp);
    }
}

void func_801154F4(STAGE_OBJ *wp)
{
    D_8011BE54[wp->routine_0](wp);
}

void func_80115530(ST0B_PAIRS *wp)
{
    uint8 *pair;
    uint32 i;

    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->value_F   = 0;
    for (i = 0, pair = wp->pair_28[0]; i < 16; i++)
    {
        pair[0] = 0;
        pair[1] = 0;
        pair += 2;
    }
}

void func_80115570(ST0B_FLAMES *wp)
{
    STAGE_OBJ *owner;
    ST0B_FLAME *flame;
    uint32 dist;
    uint32 i;

    flame = wp->flame_28;
    owner = func_80036294(wp->value_C);
    if (wp->timer_D == 0)
    {
        if (!(owner->flags_0 & 1))
        {
            wp->routine_0++;
            return;
        }
    }
    else if (wp->timer_D == 1)
    {
        if (owner->value_44.half[0] == 0)
        {
            wp->routine_0++;
            return;
        }
    }
    if (wp->count_F < 0x40)
    {
        wp->count_F++;
    }
    wp->x_1C = owner->position.x;
    wp->y_1E = owner->position.y;
    wp->z_20 = owner->position.z;
    dist     = D_8011BE30[wp->timer_D];
    wp->x_1C += (rsin((owner->rotation.y + 0x800) & 0xFFF) * dist) >> 12;
    wp->z_20 += (rcos((owner->rotation.y + 0x800) & 0xFFF) * dist) >> 12;
    wp->y_1E -= D_8011BE40[wp->timer_D];
    for (i = 0; i < 6; i++)
    {
        if (flame[i].flags_0 & 1)
        {
            func_80115780(wp, (owner->rotation.y + 0x800) & 0xFFF, flame[i].frame_1);
            if (++flame[i].frame_1 >= 25)
            {
                flame[i].frame_1 = 0;
            }
        }
        else if (i < (wp->count_F >> 2))
        {
            flame[i].flags_0 |= 1;
        }
    }
}

void func_80115760(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

// len is a sint16: as a sint32 it swaps s1/s2 with frame's extension. The position words are
// read through casts: scalar stack loads may move above the packet's struct stores, as in retail.
// The local copy of frame orders the spill slots (rot at 0x18, frame at 0x20), and the (sint16)
// casts stop fold-const reassociating the constants.
void func_80115780(ST0B_FLAMES *wp, sint16 angle, sint8 arg)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    sint16 rot;
    sint32 bob;
    sint16 len;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 u;
    uint8 v;
    sint8 frame;

    frame = arg;
    rot   = (angle + (sint16)(frame * 16 + 0x400)) & 0xFFF;
    b     = 0xF0;
    bob   = (frame << 7) & 0xFFF;
    g     = 0xA0;
    r     = 0xA0;
    len   = frame * 15;
    u     = 0x80;
    pos.x = wp->x_1C + ((rsin(rot) * len) >> 12);
    pos.z = wp->z_20 + ((rcos(rot) * len) >> 12);
    v     = 0x40;
    if (frame <= 16)
    {
        pos.y = wp->y_1E - ((rsin(bob) * 40) >> 12);
    }
    else
    {
        pos.y = wp->y_1E;
    }
    p          = func_8002D464();
    p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
    p->uv_C    = 0x3D480000 | (v << 8) | u;
    p->uv_14   = 0xE0000 | (v << 8) | (u + 0x1F);
    p->uv_1C   = ((v + 0x1F) << 8) | u;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
    p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
    p->size_18 = D_8011BE38[wp->timer_D] - frame * 2;
    rot        = ((sint16)(rot - 0x800) - (frame << 5)) & 0xFFF;
    p->pad_20  = 0;
    pos.x      = wp->x_1C + ((rsin(rot) * len) >> 12);
    pos.z      = wp->z_20 + ((rcos(rot) * len) >> 12);
    p          = func_8002D464();
    p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
    p->uv_C    = 0x3D480000 | (v << 8) | u;
    p->uv_14   = 0xE0000 | (v << 8) | (u + 0x1F);
    p->uv_1C   = ((v + 0x1F) << 8) | u;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
    p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
    p->size_18 = D_8011BE38[wp->timer_D] - frame * 2;
    p->pad_20  = 0;
}

void func_801159EC(STAGE_OBJ *wp)
{
    D_8011BE60[wp->routine_0](wp);
}

void func_80115A28(ST0B_FLAMES *wp)
{
    STAGE_OBJ *owner;
    ST0B_FLAME *flame;
    uint32 i;

    flame = wp->flame_28;
    owner = func_80036294(wp->value_C);
    if (!(owner->flags_0 & 1))
    {
        wp->routine_0++;
        return;
    }
    if (wp->count_F < 0x40)
    {
        wp->count_F++;
    }
    wp->x_1C = owner->position.x;
    wp->y_1E = owner->position.y;
    wp->z_20 = owner->position.z;
    wp->x_1C += (rsin(owner->rotation.y & 0xFFF) * 500) >> 12;
    wp->z_20 += (rcos(owner->rotation.y & 0xFFF) * 500) >> 12;
    wp->y_1E -= 0x60;
    for (i = 0; i < 6; i++)
    {
        if (flame[i].flags_0 & 1)
        {
            func_80115BCC(wp, owner->rotation.y & 0xFFF, flame[i].frame_1);
            if (++flame[i].frame_1 >= 13)
            {
                flame[i].frame_1 = 0;
            }
        }
        else if (i < (wp->count_F >> 1))
        {
            flame[i].flags_0 |= 1;
        }
    }
}

// Retail keeps the raw angle in s0 and updates it in place after the first rcos ((angle + 0x400), then (- 0x800)), with (sint16)angle in s2; rsin * 30 in a temporary stops GCC sharing frame * 30 (the 8011602C problem). Here the side angle takes its own register (score 32).
void func_80115BCC(ST0B_FLAMES *wp, sint32 angle, sint32 frame)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    sint16 side;
    sint32 size;
    sint32 t;

    t     = rsin((sint16)angle) * 30;
    pos.x = wp->x_1C + ((t * (sint8)frame) >> 12);
    t     = rcos((sint16)angle) * 30;
    pos.z = wp->z_20 + ((t * (sint8)frame) >> 12);
    pos.y = wp->y_1E + (sint8)frame * 4;
    side  = (angle + 0x400) & 0xFFF;
    pos.x += (rsin(side) * 100) >> 12;
    pos.z += (rcos(side) * 100) >> 12;
    p          = func_8002D464();
    p->uv_1C   = 0x5F80;
    p->code_4  = 0x2EF0A0A0;
    p->uv_C    = 0x3D484080;
    p->uv_14   = 0xE409F;
    p->uv_24   = 0x5F9F;
    size       = 0x80 - (sint8)frame * 4;
    p->size_18 = size;
    p->pad_20  = 0;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
    t          = rsin((sint16)angle) * 30;
    pos.x      = wp->x_1C + ((t * (sint8)frame) >> 12);
    t          = rcos((sint16)angle) * 30;
    pos.z      = wp->z_20 + ((t * (sint8)frame) >> 12);
    side       = (side - 0x800) & 0xFFF;
    pos.x += (rsin(side) * 100) >> 12;
    pos.z += (rcos(side) * 100) >> 12;
    p          = func_8002D464();
    p->uv_1C   = 0x5F80;
    p->code_4  = 0x2EF0A0A0;
    p->uv_C    = 0x3D484080;
    p->uv_14   = 0xE409F;
    p->uv_24   = 0x5F9F;
    p->size_18 = size;
    p->pad_20  = 0;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
}

void func_80115E60(STAGE_OBJ *wp)
{
    D_8011BE6C[wp->routine_0](wp);
}

void func_80115E9C(ST0B_FLAMES *wp)
{
    STAGE_OBJ *owner;
    ST0B_FLAME *flame;
    uint32 i;
    flame = wp->flame_28;
    owner = func_80036294(wp->value_C);
    if (owner->value_44.half[0] == 0)
    {
        wp->routine_0++;
        return;
    }
    if (wp->count_F < 0x40)
    {
        wp->count_F++;
    }
    wp->x_1C = owner->position.x;
    wp->y_1E = owner->position.y;
    wp->z_20 = owner->position.z;
    wp->x_1C += (rsin(owner->rotation.y & 0xFFF) * 0x140) >> 12;
    wp->z_20 += (rcos(owner->rotation.y & 0xFFF) * 0x140) >> 12;
    wp->y_1E -= 0x10;
    for (i = 0; i < 4; i++)
    {
        if (flame[i].flags_0 & 1)
        {
            func_8011602C(wp, owner->rotation.y & 0xFFF, flame[i].frame_1);
            if (++flame[i].frame_1 >= 9)
            {
                flame[i].frame_1 = 0;
            }
        }
        else if (i < (wp->count_F >> 1))
        {
            flame[i].flags_0 |= 1;
        }
    }
}

void func_8011602C(ST0B_FLAMES *wp, sint16 angle, sint32 frame)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    sint32 t;

    t          = rsin(angle) * 30;
    pos.x      = wp->x_1C + ((t * (sint8)frame) >> 12);
    t          = rcos(angle) * 30;
    pos.z      = wp->z_20 + ((t * (sint8)frame) >> 12);
    pos.y      = wp->y_1E + (sint8)frame * 4;
    p          = func_8002D464();
    p->code_4  = 0x2EF0A0A0;
    p->uv_C    = 0x3D484080;
    p->uv_14   = 0xE409F;
    p->uv_1C   = 0x5F80;
    p->uv_24   = 0x5F9F;
    p->size_18 = 0x40 - (sint8)frame * 4;
    p->pad_20  = 0;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
}

void func_80116134(STAGE_OBJ *wp)
{
    D_8011BE94[wp->routine_0](wp);
}

void func_80116170(STAGE_FX *wp)
{
    wp->mode_14  = 0x3DC8000A;
    wp->color_18 = 0x2E808080;
    wp->flags_0 |= 2;
    wp->u_22      = D_8011BE78[0];
    wp->v_23      = D_8011BE79[0];
    wp->w_24      = D_8011BE8C[0];
    wp->routine_3 = D_8011BE84[0];
    wp->routine_2 = 0;
    wp->routine_0++;
    wp->routine_1 = 0;
    if (wp->value_C != 0)
    {
        Sound_call2(0x9B, &wp->x_1C);
    }
    wp->timer_D = wp->y_1E;
}

void func_80116228(STAGE_FX *wp)
{
    STCOM_SVECTOR unused;
    uint8 i;

    wp->routine_1++;
    if (--wp->routine_3 == 0)
    {
        i = ++wp->routine_2;
        if (i >= 6)
        {
            func_80031988(wp);
            return;
        }
        wp->routine_3 = D_8011BE84[i];
        wp->u_22      = D_8011BE78[i * 2];
        wp->v_23      = D_8011BE79[i * 2];
        wp->w_24      = D_8011BE8C[wp->routine_1];
        wp->y_1E      = wp->timer_D - (D_8011BE8C[wp->routine_1] >> 1);
    }
}
