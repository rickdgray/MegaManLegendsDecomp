#include "common.h"
#include "st0b.h"

void func_8010F498(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_8011B634[wp->routine_0](wp);
}

void func_8010F534(STCOM18_WORK *wp)
{
    wp->sprite.value_12 = 0;
    wp->flags_0 |= 0x22;
    if (!(wp->flags_F & 1))
    {
        wp->sprite.value_E = 0x40;
        wp->sprite.value_F = 0x80;
        if (!(wp->flags_F & 0x10))
        {
            wp->sprite.color_4.word = 0x2C808080;
        }
        else
        {
            wp->sprite.color_4.word = 0x2C6060C0;
        }
        wp->sprite.mode_0 = 0x3D08000E;
    }
    else
    {
        if (!(wp->flags_F & 8))
        {
            wp->sprite.value_E = D_8011B61C[0].a;
            wp->sprite.value_F = D_8011B61C[0].b;
        }
        else
        {
            wp->sprite.value_E = D_8011B628[0].a;
            wp->sprite.value_F = D_8011B628[0].b;
        }
        wp->sprite.color_4.word = 0x2C808080;
        wp->sprite.mode_0       = 0x3D48000E;
    }
    wp->sprite.pos_8[0] = wp->position.x;
    wp->sprite.pos_8[1] = wp->position.y;
    wp->sprite.pos_8[2] = wp->position.z;
    if (!(wp->flags_F & 2))
    {
        wp->sprite.value_10 = 0x20;
        if (!(wp->flags_F & 0x10))
        {
            wp->kind_E = 4;
        }
        else
        {
            wp->kind_E = 0x20;
        }
    }
    else
    {
        wp->sprite.value_10 = 0x10;
        wp->kind_E          = 8;
    }
    if (!(wp->flags_F & 0x20))
    {
        wp->timer_B = 0xF0;
    }
    else
    {
        wp->timer_B = 0x4B;
    }
    wp->data_10  = NULL;
    wp->value_78 = 0;
    wp->hit_BC   = 0;
    func_800341BC(&wp->position, wp->sprite.value_10, 0, 0xA000, wp->value_1, &wp->hit_BC,
                  wp->kind_E | 0x8000000, 0, 0x80);
    if (func_80049C24(wp))
    {
        wp->routine_0 = 2;
    }
    else
    {
        wp->routine_0++;
    }
}

void func_8010F6F8(STCOM18_WORK *wp)
{
    sint32 frame;
    sint32 hit;

    wp->timer_B--;
    if (!(wp->flags_F & 1))
    {
        wp->sprite.value_12 = (wp->sprite.value_12 + 8) & 0x3F;
    }
    else
    {
        frame = (0xF0 - wp->timer_B) % 6;
        if (!(wp->flags_F & 8))
        {
            wp->sprite.value_E = D_8011B61C[frame].a;
            wp->sprite.value_F = D_8011B61C[frame].b;
        }
        else
        {
            wp->sprite.value_E = D_8011B628[frame].a;
            wp->sprite.value_F = D_8011B628[frame].b;
        }
        wp->sprite.color_4.word = 0x2C808080;
        func_8002CA10(&wp->position, 0x30, 0x200, 0);
    }
    if (wp->timer_B != 0 && wp->position.y < 0)
    {
        wp->velocity.v.x += wp->accel.x;
        wp->velocity.v.y += wp->accel.y;
        wp->velocity.v.z += wp->accel.z;
        wp->position_fixed.x += wp->velocity.v.x << 8;
        wp->position_fixed.y += wp->velocity.v.y << 8;
        wp->position_fixed.z += wp->velocity.v.z << 8;
        func_80030150(&wp->position_fixed, &wp->position);
        wp->sprite.pos_8[0] = wp->position.x;
        wp->sprite.pos_8[1] = wp->position.y;
        wp->sprite.pos_8[2] = wp->position.z;
    }
    else
    {
        wp->flags_0 = 0;
        func_800318D8(wp);
    }
    if (wp->hit_BC & 0x2000000)
    {
        wp->hit_BC = 0;
        wp->routine_0++;
    }
    else
    {
        func_800341BC(&wp->position, wp->sprite.value_10, 0, 0xA000, wp->value_1, &wp->hit_BC,
                      wp->kind_E | 0x8000000, 0, 0x80);
        wp->hit_BC = 0;
        hit        = func_80049C24(wp);
        if (hit)
        {
            wp->routine_0++;
        }
        if (!(wp->flags_F & 4))
        {
            func_80037738(hit, 0x28);
        }
    }
}

// Spawns its effect (kind 0x80 variant 0x42 or kind 0x83) and frees the slot.
void func_8010F960(STAGE_OBJ *wp)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        if (wp->u_E.b.byte_F & 1)
        {
            func_8010F9CC(wp, fx);
        }
        else
        {
            func_8010FA0C(wp, fx);
        }
    }
    wp->flags_0 = 0;
    func_800318D8(wp);
}

void func_8010F9CC(STAGE_OBJ *wp, STAGE_FX *fx)
{
    fx->flags_0                     = 7;
    fx->kind_2                      = 0x80;
    fx->variant_3                   = 0x42;
    *(STCOM_SVECTOR *)&fx->value_38 = wp->position;
}

void func_8010FA0C(STAGE_OBJ *wp, STAGE_FX *fx)
{
    fx->flags_0   = 3;
    fx->kind_2    = 0x83;
    fx->variant_3 = 0;
    fx->x_1C      = wp->position.x;
    fx->y_1E      = -1;
    fx->z_20      = wp->position.z;
}

void func_8010FA3C(STAGE_OBJ *wp)
{
    D_8011B658[wp->routine_0](wp);
}

void func_8010FA78(ST0B_10C_B *wp)
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

void func_8010FB6C(ST0B_10C_B *wp)
{
    wp->count_CC++;
    wp->sprite.pos_8[0] = wp->position.x;
    wp->sprite.pos_8[1] = wp->position.y;
    wp->sprite.pos_8[2] = wp->position.z;
    if (wp->routine_3 == 0)
    {
        wp->byte_C = 1;
        wp->routine_0++;
        wp->sprite.dir_1C = func_8011010C(wp);
        Sound_call2(0xF1, &wp->position);
    }
    else
    {
        func_801102A4(wp);
    }
}

void func_8010FC18(ST0B_10C_B *wp)
{
    STCOM_SVECTOR dir;
    STCOM_SVECTOR target;
    sint32 hit;

    hit = func_80049C24(wp);
    if (hit != 0)
    {
        func_80037738(hit, D_8011B64C[wp->byte_D]);
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
        func_800318D8(wp);
    }
    else
    {
        target = func_8011010C((ST0B_10C_H *)wp);
        func_80033F04(&dir, &target, &wp->sprite.dir_1C, 0x32, 0xFFFB10B);
        wp->sprite.dir_1C    = dir;
        wp->value_44.half[0] = (dir.x * 25) >> 2;
        wp->value_44.half[1] = (dir.y * 25) >> 2;
        wp->value_48.half[0] = (dir.z * 25) >> 2;
        wp->position_fixed.v.x += wp->value_44.half[0] << 8;
        wp->position_fixed.v.y += wp->value_44.half[1] << 8;
        wp->position_fixed.v.z += wp->value_48.half[0] << 8;
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_801101EC(wp);
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
                      D_8011B640[wp->byte_D] | 0x49000000, 0, 0x80);
    }
    wp->sprite.hit_14 = 0;
}

void func_80110058(ST0B_10C_B *wp)
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
        func_800318D8(wp);
    }
    else
    {
        func_80110540(wp);
    }
}

STCOM_SVECTOR func_8011010C(ST0B_10C_B *wp)
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

void func_801101EC(ST0B_10C_B *wp)
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

void func_801102A4(ST0B_10C_F *wp)
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
        if (D_8011B668[i].start_0 < t && t < D_8011B668[i].start_0 + 0x10)
        {
            p      = func_8002D464();
            t      = wp->count_CC - D_8011B668[i].start_0;
            angle  = (D_8011B668[i].angle_4 + t * 24) & 0xFFF;
            height = D_8011B668[i].height_6 - t * (D_8011B668[i].height_6 / 16);
            radius = D_8011B668[i].radius_2 - t * (D_8011B668[i].radius_2 / 16);
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
        if (t == D_8011B668[i].start_0 + 0x10)
        {
            wp->routine_3--;
            wp->sprite.value_10 += 8;
        }
    }
}

void func_80110540(ST0B_10C_G *wp)
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
        if (wp->count_CC < D_8011B668[i].start_0 + 0x10)
        {
            p = func_8002D464();
            if (wp->count_CC < D_8011B668[i].start_0)
            {
                r      = 0x60;
                g      = 0xE0;
                b      = 0x60;
                angle  = D_8011B668[i].angle_4;
                height = (D_8011B668[i].height_6 / 16) * wp->count_CC;
                radius = (D_8011B668[i].radius_2 / 16) * wp->count_CC;
            }
            else
            {
                t      = wp->count_CC - D_8011B668[i].start_0;
                r      = 0x60 - t * 6;
                g      = -0x20 - t * 14;
                b      = r;
                angle  = D_8011B668[i].angle_4;
                height = D_8011B668[i].start_0 * (D_8011B668[i].height_6 / 16);
                radius = D_8011B668[i].start_0 * (D_8011B668[i].radius_2 / 16);
                height += t * (D_8011B668[i].height_6 / 32);
                radius += t * (D_8011B668[i].radius_2 / 32);
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
        if (wp->count_CC == D_8011B668[i].start_0 + 0x10)
        {
            wp->routine_3--;
        }
    }
}
