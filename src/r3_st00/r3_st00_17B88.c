#include "common.h"
#include "st00.h"

void func_80117B88(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;

    wp->z_34.value += 0x8000;
    wp->x_2C.half[1] += (wp->value_38.value -= 0x147A) >> 16;
    wp->x_2C.half[0] = (wp->x_2C.half[0] + (wp->z_34.value >> 16)) & 0xFFF;
    if (wp->x_2C.half[1] < 0)
    {
        func_80031988(wp);
        return;
    }
    v.x = (rcos(wp->x_2C.half[0]) * wp->x_2C.half[1]) >> 12;
    v.y = (rsin(wp->x_2C.half[0]) * wp->x_2C.half[1]) >> 12;
    v.z = 0;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY(wp->y_30.half[0], &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = wp->u_28.parent->x_1C + out.x;
    wp->y_1E = wp->u_28.parent->y_1E + out.y;
    wp->z_20 = wp->u_28.parent->z_20 + out.z;
}

void func_80117CCC(STAGE_FX *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->be_flag |= TRANS;
        wp->routine_0++;
    }
    func_80117B88(wp);
}

void func_80117D14(STAGE_FX *wp)
{

    wp->frame_E = 0;
    wp->be_flag |= TRANS;
    if (Game_work.value_50 == 0x16)
    {
        wp->mode_14 = 0x3CC80027;
    }
    else
    {
        wp->mode_14 = 0x3C880026;
    }
    wp->color_18       = 0x2E808080;
    wp->value_38.value = 0xA0000;
    wp->h_26           = 0;
    wp->z_34.value     = 0;
    wp->value_3C.value = -0x10000;
    wp->routine_0++;
}

void func_80117D80(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    STAGE_FX *ep;
    sint16 angle;
    sint16 radius;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = out.x + (parent->position_fixed.v.x >> 16);
    wp->y_1E = out.y + (parent->position_fixed.v.y >> 16);
    wp->z_20 = out.z + (parent->position_fixed.v.z >> 16);
    if (wp->z_34.value < 0x900000)
    {
        wp->z_34.value += 0x170A3;
        wp->value_38.value += 0x8000;
        wp->value_3C.value -= 0x147A;
    }
    wp->h_26 = (wp->h_26 + 1) & 3;
    wp->w_24 = wp->z_34.value >> 16;
    wp->u_22 = D_8011CE10[wp->h_26].u;
    wp->v_23 = D_8011CE10[wp->h_26].v;
    if (++wp->frame_E == 4)
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->be_flag        = MOVE;
            ep->id             = 6;
            ep->type           = 0;
            ep->work_0         = 6;
            ep->timer_D        = 1;
            angle              = rand() & 0xFFF;
            radius             = (rand() & 0x1F) + 0x64;
            ep->mode_14        = 0x3C48002E;
            ep->w_24           = 0x12;
            ep->u_22           = 0x80;
            ep->color_18       = 0x2E202020;
            ep->v_23           = 0xA0;
            ep->u_28.parent    = wp;
            ep->x_2C.half[0]   = angle;
            ep->x_2C.half[1]   = radius;
            ep->y_30.half[0]   = rot;
            ep->z_34.value     = wp->value_38.value;
            ep->value_38.value = wp->value_3C.value;
        }
        wp->frame_E = 0;
    }
}

void func_80117F94(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80117D14(wp);
        }
        func_80117D80(wp);
        return;
    }
    func_80117CCC(wp);
}

void func_80117FF8(STAGE_FX *wp)
{
    wp->be_flag |= TRANS;
    if (Game_work.value_50 == 0x16)
    {
        wp->mode_14 = 0x3CC80027;
    }
    else
    {
        wp->mode_14 = 0x3C880026;
    }
    wp->color_18 = 0x2E808080;
    wp->h_26     = 0;
    wp->routine_0++;
}

void func_80118050(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    wp->x_1C = out.x + (parent->position_fixed.v.x >> 16);
    wp->y_1E = out.y + (parent->position_fixed.v.y >> 16);
    wp->z_20 = out.z + (parent->position_fixed.v.z >> 16);
    if (++wp->h_26 == 4)
    {
        wp->h_26 = 0;
    }
    wp->u_22 = D_8011CE20[wp->h_26].u;
    wp->v_23 = D_8011CE20[wp->h_26].v;
    wp->w_24 = D_8011CE20[wp->h_26].w;
}

void func_80118190(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_80117FF8(wp);
        }
        func_80118050(wp);
    }
}

void func_801181E4(STAGE_FX *wp)
{
    sint8 frame;

    frame = ++wp->type_F;
    if (frame == 8)
    {
        func_80031988(wp);
        return;
    }
    wp->color_18 = D_8011CE30[frame];
    wp->w_24 += 0x10;
    if (wp->w_24 > 0x120)
    {
        wp->w_24 = 0x120;
    }
}

void func_80118264(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->be_flag |= TRANS;
        wp->routine_0++;
    }
    func_801181E4(wp);
}

void func_801182AC(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_801182C0(STAGE_FX *wp)
{
    STAGE_MATRIX m;
    STCOM_SVECTOR v;
    STCOM_SVECTOR out;
    STAGE_OBJ *parent;
    STAGE_FX *ep;
    uint16 rot;

    parent = wp->u_28.object;
    rot    = parent->rotation.y;
    v.x    = wp->x_2C.words.fraction;
    v.y    = wp->x_2C.words.integer;
    v.z    = wp->y_30.words.fraction;
    STAGE_MATRIX_IDENTITY_SCALAR(m.w);
    RotMatrixY((sint16)rot, &m.m);
    ApplyMatrixSV(&m.m, &v, &out);
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag = MOVE;
        ep->id      = 6;
        ep->type    = 2;
        ep->work_0  = 6;
        ep->timer_D = 1;
        ep->frame_E = 0;
        ep->type_F  = 0;
        if (Game_work.value_50 == 0x16)
        {
            ep->mode_14 = 0x3CC80027;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->w_24     = 0x90;
        ep->u_22     = 0xA0;
        ep->v_23     = 0x20;
        ep->x_1C     = out.x + (parent->position_fixed.v.x >> 16);
        ep->y_1E     = out.y + (parent->position_fixed.v.y >> 16);
        ep->z_20     = out.z + (parent->position_fixed.v.z >> 16);
        ep->color_18 = 0x2E808080;
    }
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag = MOVE;
        ep->id      = 6;
        ep->type    = 2;
        ep->work_0  = 6;
        ep->timer_D = 1;
        ep->frame_E = 1;
        ep->type_F  = 0;
        if (Game_work.value_50 == 0x16)
        {
            ep->mode_14 = 0x3CC80027;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->w_24     = 0x24;
        ep->u_22     = 0xA0;
        ep->v_23     = 0x20;
        ep->x_1C     = out.x + (parent->position_fixed.v.x >> 16);
        ep->y_1E     = out.y + (parent->position_fixed.v.y >> 16);
        ep->z_20     = out.z + (parent->position_fixed.v.z >> 16);
        ep->color_18 = 0x2E808080;
    }
}

void func_801184B4(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        if (wp->routine_0 == 0)
        {
            func_801182AC(wp);
        }
        func_801182C0(wp);
        return;
    }
    func_80118264(wp);
}

void func_80118518(void)
{
}

void func_80118520(STAGE_OBJ *wp)
{
    if (wp->u_C.b.work_1 == 0)
    {
        func_80118518();
        return;
    }
    func_80118264(wp);
}

void func_80118560(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 2)
    {
        func_80031988((STCOM_EFFECT *)wp);
        return;
    }
    D_8011CE50[wp->type](wp);
}

STAGE_FX *func_801185BC(STAGE_OBJ *owner, sint32 x, sint32 y, sint32 z, uint8 variant)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag      = MOVE;
        fx->id           = 6;
        fx->type         = variant;
        fx->timer_D      = 0;
        fx->u_28.object  = owner;
        fx->x_2C.half[0] = x;
        fx->x_2C.half[1] = y;
        fx->y_30.half[0] = z;
        return fx;
    }
    return NULL;
}

void func_80118648(STCOM_SVECTOR *pos, sint16 a1, sint16 a2, ST00_POINT_FX *owner, uint8 variant)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag  = MOVE;
        fx->id       = 9;
        fx->type     = variant;
        fx->work_0   = 9;
        fx->timer_D  = 1;
        fx->frame_E  = 0x1E;
        fx->mode_14  = 0x3D48002E;
        fx->u_22     = (rand() & 3) * 32 + 0x20;
        fx->v_23     = 0;
        fx->color_18 = 0x2E202020;
        fx->w_24     = 6;
        pos->x += rand() & 3;
        pos->y += rand() & 3;
        pos->z += rand() & 3;
        fx->u_28.count       = pos->x << 16;
        fx->x_2C.value       = pos->y << 16;
        fx->y_30.value       = pos->z << 16;
        fx->value_38.half[0] = a1;
        fx->value_38.half[1] = a2;
        fx->value_3C.value   = (sint32)owner;
    }
}

void func_8011877C(STCOM_SVECTOR *pos, sint32 a1, sint32 a2)
{
    ST00_POINT_FX *fx;

    fx = (ST00_POINT_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag    = MOVE;
        fx->id         = 9;
        fx->work_0     = 9;
        fx->work_1     = 0;
        fx->work_2     = 0;
        fx->x_28.value = pos->x << 16;
        fx->y_2C.value = pos->y << 16;
        fx->z_30.value = pos->z << 16;
        fx->value_38   = a1;
        fx->value_3A   = a2;
    }
}

void func_80118814(ST00_POINT_FX *wp)
{
    STCOM_MATRIX m;
    STCOM_FIXED_VECTOR v;
    STCOM_FIXED_VECTOR move;

    if (wp->routine_0 == 0)
    {
        wp->be_flag |= TRANS;
    }
    if (--wp->work_2 == 0)
    {
        func_80031988(wp);
        return;
    }
    wp->color_18 += 0xFFFEFEFF;
    wp->w_24++;
    if (wp->type != 0)
    {
        v.x               = 0;
        v.y               = 0;
        v.z               = wp->owner_3C->speed_34.value;
        ((sint32 *)&m)[0] = 0x1000;
        ((sint32 *)&m)[1] = 0;
        ((sint32 *)&m)[2] = 0x1000;
        ((sint32 *)&m)[3] = 0;
        ((sint32 *)&m)[4] = 0x1000;
        ((sint32 *)&m)[5] = 0;
        ((sint32 *)&m)[6] = 0;
        ((sint32 *)&m)[7] = 0;
        RotMatrixX(wp->value_38, &m);
        RotMatrixY(wp->value_3A, &m);
        ApplyMatrixLV(&m, &v, &move);
        wp->x_28.value += move.x;
        wp->y_2C.value += move.y;
        wp->z_30.value += move.z;
    }
    wp->x_1C = wp->x_28.value >> 16;
    wp->y_1E = wp->y_2C.value >> 16;
    wp->z_20 = wp->z_30.value >> 16;
}

void func_80118960(ST00_POINT_FX *wp)
{
    STCOM_SVECTOR pos;
    sint32 step;

    if (wp->routine_0 == 0)
    {
        wp->speed_34.value = 0x10000;
        wp->routine_0++;
    }
    pos.x = wp->x_28.value >> 16;
    pos.y = wp->y_2C.value >> 16;
    pos.z = wp->z_30.value >> 16;
    step  = wp->routine_1;
    switch (wp->routine_1)
    {
        case 0:
            if (++wp->work_2 == 0xF)
            {
                wp->routine_1++;
            }
            func_80118648(&pos, wp->value_38, wp->value_3A, wp, step);
            break;
        case 1:
            func_80118648(&pos, wp->value_38, wp->value_3A, wp, step);
            func_80118648(&pos, wp->value_38, wp->value_3A, wp, step);
            wp->work_2++;
            wp->speed_34.value += 0x10000;
            if (wp->work_2 == 0x1E)
            {
                func_80031988(wp);
            }
            break;
    }
}

void func_80118AA0(STAGE_OBJ *wp)
{
    if (wp->u_C.b.work_1 == 0)
    {
        func_80118960(wp);
        return;
    }
    func_80118814(wp);
}
