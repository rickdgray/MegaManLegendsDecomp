#include "common.h"
#include "st0a.h"

void func_8011025C(STAGE_OBJ *wp)
{
    D_80116410[wp->routine_0](wp);
}

void func_80110298(ST0A_10C_B *wp)
{
    wp->routine_0           = 1;
    wp->routine_3           = 0x18;
    wp->sprite.value_E      = 0x60;
    wp->sprite.value_F      = 0x20;
    wp->sprite.value_10     = 8;
    wp->sprite.mode_0       = 0x3D48002E;
    wp->sprite.color_4.word = 0x2E40E040;
    wp->routine_1           = 0;
    wp->routine_2           = 0;
    wp->byte_C              = 0;
    wp->byte_E              = 0;
    wp->byte_F              = 0;
    wp->count_CC            = 0;
    wp->flags_0 |= 2;
    wp->sprite.pos_8[0] = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->sprite.pos_8[1] = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->sprite.pos_8[2] = wp->position.z = wp->position_fixed.f.z.words.integer;
    wp->position_fixed_prev              = wp->position_fixed.v;
    wp->position_prev                    = wp->position;
    wp->sprite.hit_14                    = 0;
    Sound_call2(0xF0, &wp->position);
}

void func_8011038C(ST0A_10C *wp)
{
    wp->count_CC++;
    wp->sprite.pos_8[0] = wp->position.x;
    wp->sprite.pos_8[1] = wp->position.y;
    wp->sprite.pos_8[2] = wp->position.z;
    if (wp->routine_3 == 0)
    {
        wp->byte_C = 1;
        wp->routine_0++;
        wp->sprite.dir_1C = func_8011092C(wp);
        Sound_call2(0xF1, &wp->position);
    }
    else
    {
        func_80110AC4(wp);
    }
}

void func_80110438(ST0A_10C_B *wp)
{
    STCOM_SVECTOR dir;
    STCOM_SVECTOR target;
    sint32 hit;

    hit = func_80049C24(wp);
    if (hit != 0)
    {
        func_80037738(hit, D_80116404[wp->byte_D]);
        wp->routine_3 = 0x18;
        wp->count_CC  = 0;
        wp->routine_0++;
        Sound_call2(0xF2, &wp->position);
        return;
    }
    if (wp->sprite.hit_14 & 0x2000000)
    {
        wp->routine_3 = 0x18;
        wp->count_CC  = 0;
        wp->routine_0++;
        Sound_call2(0xF2, &wp->position);
        return;
    }
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    if (wp->byte_C >= 0)
    {
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
        wp->trail_D4[0]     = wp->position;
        wp->trail_D4[1]     = wp->trail_D4[0];
        wp->trail_D4[2]     = wp->trail_D4[1];
        wp->trail_D4[3]     = wp->trail_D4[2];
        wp->trail_D4[4]     = wp->trail_D4[3];
        wp->trail_D4[5]     = wp->trail_D4[4];
        return;
    }
    if (--wp->routine_3 == 0)
    {
        Close_SHL_WORK(wp);
    }
    else
    {
        target = func_8011092C((ST0A_10C *)wp);
        func_80033F04(&dir, &target, &wp->sprite.dir_1C, 0x32, 0xFFFB10B);
        wp->sprite.dir_1C    = dir;
        wp->value_44.half[0] = (dir.x * 25) >> 2;
        wp->value_44.half[1] = (dir.y * 25) >> 2;
        wp->value_48.half[0] = (dir.z * 25) >> 2;
        wp->position_fixed.v.x += wp->value_44.half[0] << 8;
        wp->position_fixed.v.y += wp->value_44.half[1] << 8;
        wp->position_fixed.v.z += wp->value_48.half[0] << 8;
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80110A0C(wp);
        wp->trail_D4[5]     = wp->trail_D4[4];
        wp->trail_D4[4]     = wp->trail_D4[3];
        wp->trail_D4[3]     = wp->trail_D4[2];
        wp->trail_D4[2]     = wp->trail_D4[1];
        wp->trail_D4[1]     = wp->trail_D4[0];
        wp->trail_D4[0]     = wp->position;
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
    }
    if (wp->flags_0 & 1)
    {
        func_800341BC(&wp->position, 0xC0, 0, 0xA000, wp->reserved01, &wp->sprite.hit_14,
                      D_801163F8[wp->byte_D] | 0x49000000, 0, 0x80);
    }
    wp->sprite.hit_14 = 0;
}

void func_80110878(ST0A_10C_B *wp)
{
    uint8 c;
    uint8 g;

    if (wp->count_CC < 4)
    {
        c                       = 0x40 - wp->count_CC * 16;
        g                       = 0xE0 - wp->count_CC * 56;
        wp->sprite.color_4.word = 0x2E000000 | (c << 16) | (g << 8) | c;
    }
    else
    {
        wp->sprite.color_4.word = 0x2E000000;
        wp->flags_0 &= ~2;
    }
    wp->count_CC++;
    if (wp->routine_3 == 0)
    {
        Close_SHL_WORK(wp);
    }
    else
    {
        func_80110D60(wp);
    }
}

STCOM_SVECTOR func_8011092C(ST0A_10C *wp)
{
    STCOM_SVECTOR dir;
    STCOM_FIXED_VECTOR d;

    d.x = Player_work.position.x - wp->position.x;
    d.y = Player_work.position.y - wp->position.y;
    d.z = Player_work.position.z - wp->position.z;
    if (d.x > 0x687E || d.x < -0x687E || d.y > 0x687E || d.y < -0x687E || d.z > 0x687E ||
        d.z < -0x687E)
    {
        d.x >>= 2;
        d.y >>= 2;
        d.z >>= 2;
    }
    VectorNormalS(&d, &dir);
    return dir;
}

void func_80110A0C(ST0A_10C_B *wp)
{
    STCOM23_PACKET *p;
    uint8 i;

    for (i = 0; i < 6; i++)
    {
        p          = func_8002D464();
        p->code_4  = 0x2E80C080;
        p->xy_8    = *(uint32 *)&wp->trail_D4[i].x;
        p->z_10    = *(uint32 *)&wp->trail_D4[i].z;
        p->uv_C    = 0x3D482080;
        p->uv_14   = 0x2E209F;
        p->uv_1C   = 0x3F80;
        p->uv_24   = 0x3F9F;
        p->size_18 = 0xC0 - i * 24;
        p->pad_20  = 0;
    }
}

void func_80110AC4(ST0A_10C *wp)
{
    STCOM23_PACKET *p;
    STCOM_SVECTOR pos;
    sint16 t;
    sint16 angle;
    sint16 radius;
    sint16 height;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 i;

    for (i = 0; i < 24; i++)
    {
        t = wp->count_CC;
        if (D_80116420[i].start_0 < t && t < D_80116420[i].start_0 + 0x10)
        {
            p      = func_8002D464();
            t      = wp->count_CC - D_80116420[i].start_0;
            angle  = (D_80116420[i].angle_4 + t * 24) & 0xFFF;
            height = D_80116420[i].height_6 - t * (D_80116420[i].height_6 / 16);
            radius = D_80116420[i].radius_2 - t * (D_80116420[i].radius_2 / 16);
            if (t < 8)
            {
                r = (t + 1) * 12;
                g = (t + 1) * 28;
                b = r;
            }
            else
            {
                r = 0x60;
                g = 0xE0;
                b = 0x60;
            }
            pos.x      = wp->position.x + ((rsin(angle) * radius) >> 12);
            pos.z      = wp->position.z + ((rcos(angle) * radius) >> 12);
            pos.y      = wp->position.y + height;
            p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
            p->xy_8    = (pos.y << 16) + pos.x;
            p->z_10    = pos.z;
            p->uv_C    = 0x3D482040;
            p->uv_1C   = 0x3F40;
            p->uv_24   = 0x3F5F;
            p->uv_14   = 0x2E205F;
            p->size_18 = 0x40;
            p->pad_20  = 0;
        }
        if (t == D_80116420[i].start_0 + 0x10)
        {
            wp->routine_3--;
            wp->sprite.value_10 += 8;
        }
    }
}

void func_80110D60(ST0A_10C *wp)
{
    STCOM23_PACKET *p;
    STCOM_SVECTOR pos;
    sint16 t;
    sint16 angle;
    sint16 radius;
    sint16 height;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 i;

    for (i = 0; i < 24; i++)
    {
        if (wp->count_CC < D_80116420[i].start_0 + 0x10)
        {
            p = func_8002D464();
            if (wp->count_CC < D_80116420[i].start_0)
            {
                r      = 0x60;
                g      = 0xE0;
                b      = 0x60;
                angle  = D_80116420[i].angle_4;
                height = (D_80116420[i].height_6 / 16) * wp->count_CC;
                radius = (D_80116420[i].radius_2 / 16) * wp->count_CC;
            }
            else
            {
                t      = wp->count_CC - D_80116420[i].start_0;
                r      = 0x60 - t * 6;
                g      = -0x20 - t * 14;
                b      = r;
                angle  = D_80116420[i].angle_4;
                height = D_80116420[i].start_0 * (D_80116420[i].height_6 / 16);
                radius = D_80116420[i].start_0 * (D_80116420[i].radius_2 / 16);
                height += t * (D_80116420[i].height_6 / 32);
                radius += t * (D_80116420[i].radius_2 / 32);
            }
            pos.x      = wp->position.x + ((rsin(angle) * radius) >> 12);
            pos.z      = wp->position.z + ((rcos(angle) * radius) >> 12);
            pos.y      = wp->position.y + height;
            p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
            p->xy_8    = (pos.y << 16) + pos.x;
            p->z_10    = pos.z;
            p->uv_C    = 0x3D482040;
            p->uv_1C   = 0x3F40;
            p->uv_24   = 0x3F5F;
            p->uv_14   = 0x2E205F;
            p->size_18 = 0x30;
            p->pad_20  = 0;
        }
        if (wp->count_CC == D_80116420[i].start_0 + 0x10)
        {
            wp->routine_3--;
        }
    }
}

void func_8011105C(ST0A_PIECE *wp)
{
    STCOM_SVECTOR pos;

    if (wp->routine_0 != 0)
    {
        func_80111788(wp);
    }
    D_801164EC[wp->routine_0](wp);
    func_80111864(wp);
    wp->model.model_0 = wp->models_CC[wp->routine_2];
    pos               = wp->position;
    pos.y += 0x320;
    func_8002CA10(&pos, 0x20, 0x200, 0);
}

void func_80111118(ST0A_PIECE *wp)
{
    ST0A_MODEL *model;
    STCOM_FIXED_VECTOR scale;
    uint8 variant;

    model     = &wp->model;
    wp->hit_C4 = 0;
    wp->hit_C8 = 0;
    wp->box_78 = D_801164E0;
    wp->flags_0 |= 6;
    for (variant = 0; variant < 4; variant++)
    {
        wp->variant_3 = variant;
        Model_work_init(wp, &variant);
        wp->models_CC[variant] = model->model_0;
    }
    wp->position.pad = 0;
    wp->fpos.w.x     = wp->position.x << 16;
    wp->fpos.w.y     = wp->position.y << 16;
    wp->fpos.w.z     = wp->position.z << 16;
    model->pos_24    = wp->position;
    model->color_2C  = 0x808080;
    RotMatrixYXZ(&wp->rotation, &model->mtx_4);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&wp->model.mtx_4, &scale);
    wp->vx = (uint32)(-rsin(wp->rotation.y) * 5) >> 2;
    wp->vy = 0;
    wp->vz = (uint32)(-rcos(wp->rotation.y) * 5) >> 2;
    wp->ax = 0;
    wp->ay = -0x180;
    wp->az = 0;
    wp->routine_2 = 0;
    wp->routine_0++;
    wp->timer_B = (rand() & 7) + 0x14;
    wp->range_C = (rand() & 0x1F) + 0xA;
    wp->hit_7C  = 0;
    func_80111864(wp);
    Sound_call2(0xF9, &wp->position);
}

void func_801112C0(ST0A_PIECE *wp)
{
    wp->fpos.w.x += wp->vx << 8;
    wp->fpos.w.y += wp->vy << 8;
    wp->fpos.w.z += wp->vz << 8;
    wp->model.pos_24.x = wp->position.x = wp->fpos.h.x;
    wp->model.pos_24.y = wp->position.y = wp->fpos.h.y;
    wp->model.pos_24.z = wp->position.z = wp->fpos.h.z;
    wp->vx += wp->ax;
    wp->vy += wp->ay;
    wp->vz += wp->az;
    if (--wp->timer_B == 0)
    {
        wp->routine_0++;
        wp->timer_B = (rand() & 0xF) + 0x28;
    }
    if (++wp->routine_2 >= 3)
    {
        wp->routine_2 = 0;
    }
}

void func_801113CC(ST0A_PIECE *wp)
{
    STCOM_SVECTOR *pos;

    pos = &wp->position;
    wp->rotation.y += Muku(pos, (STCOM_SVECTOR *)&STAGE_PL.value_3A8, wp->rotation.y & 0xFFF, 0x40);
    if (--wp->timer_B == 0)
    {
        wp->routine_0++;
        wp->timer_B = (rand() & 0x1F) + 0x64;
        wp->rotation.y += Muku(pos, (STCOM_SVECTOR *)&STAGE_PL.value_3A8, wp->rotation.y & 0xFFF, 0x800);
    }
    if (++wp->routine_2 >= 3)
    {
        wp->routine_2 = 0;
    }
    if (STAGE_FRAME & 2)
    {
        Sound_call2(0xFA, pos);
    }
}

void func_801114D0(ST0A_PIECE *wp)
{
    STCOM_SVECTOR *pos;
    sint32 range;

    pos = &wp->position;
    wp->rotation.y += Muku(pos, (STCOM_SVECTOR *)&STAGE_PL.value_3A8, wp->rotation.y & 0xFFF, 0x20);
    wp->vx = (uint32)(-rsin(wp->rotation.y) * 5) >> 2;
    wp->vy = 0;
    wp->vz = (uint32)(-rcos(wp->rotation.y) * 5) >> 2;
    wp->fpos.w.x += wp->vx << 8;
    wp->fpos.w.y += wp->vy << 8;
    wp->fpos.w.z += wp->vz << 8;
    wp->model.pos_24.x = wp->position.x = wp->fpos.h.x;
    wp->model.pos_24.y = wp->position.y = wp->fpos.h.y;
    wp->model.pos_24.z = wp->position.z = wp->fpos.h.z;
    range = wp->range_C * 4;
    if (--wp->timer_B == 0 || wp->dist_80 < range * range)
    {
        wp->timer_B = 0xF0;
        wp->vx      = 0;
        wp->vy      = 0;
        wp->vz      = 0;
        wp->ax      = 0;
        wp->ay      = 0x180;
        wp->az      = 0;
        wp->routine_0++;
        Sound_call2(0xFB, pos);
    }
    if (++wp->routine_2 >= 3)
    {
        wp->routine_2 = 0;
    }
    if (STAGE_FRAME & 2)
    {
        Sound_call2(0xFA, &wp->position);
    }
}

void func_80111680(ST0A_PIECE *wp)
{
    sint32 max;

    wp->fpos.w.x += wp->vx << 8;
    wp->fpos.w.y += wp->vy << 8;
    wp->fpos.w.z += wp->vz << 8;
    wp->model.pos_24.x = wp->position.x = wp->fpos.h.x;
    wp->model.pos_24.y = wp->position.y = wp->fpos.h.y;
    wp->model.pos_24.z = wp->position.z = wp->fpos.h.z;
    wp->vx += wp->ax;
    wp->vy += wp->ay;
    wp->vz += wp->az;
    max = 0x3200;
    if (wp->vy > max)
    {
        wp->vy = max;
    }
    if (--wp->timer_B == 0)
    {
        func_801118B4(wp);
        Close_SHL_WORK(wp);
        return;
    }
    wp->routine_2 = 3;
    func_80051BAC(wp);
}

void func_80111788(ST0A_PIECE *wp)
{
    STCOM_FIXED_VECTOR scale;

    if ((wp->hit_C4 & 0x1A000000) || func_80049C24(wp) || wp->hit_7C != 0)
    {
        func_801118B4(wp);
        Close_SHL_WORK(wp);
        return;
    }
    wp->fpos_prev     = wp->fpos.w;
    wp->position_prev = wp->position;
    RotMatrixYXZ(&wp->rotation, &wp->model.mtx_4);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&wp->model.mtx_4, &scale);
}

void func_80111864(ST0A_PIECE *wp)
{
    func_800341BC(&wp->position, 0x20, 0, 0x8000, wp->value_1, &wp->hit_C4, 0x4000005, 0, 0);
}

void func_801118B4(ST0A_PIECE *wp)
{
    STCOM_EFFECT *effect;
    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0         = 5;
        effect->kind_2          = 0x80;
        effect->variant_3       = 0x42;
        effect->sprite.position = wp->position;
    }
}
