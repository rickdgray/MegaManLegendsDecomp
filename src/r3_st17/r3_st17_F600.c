#include "common.h"
#include "st17.h"

void func_8010F600(STAGE_OBJ *wp, ST17_RIG2 *rig)
{
    STAGE_MATRIX m;
    STCOM_FIXED_VECTOR scale = {0x1000, 0x1000, 0x1000, 0};
    sint8 i;

    STAGE_MATRIX_IDENTITY(m.w);
    RotMatrixYXZ(&wp->rotation, &m.m);
    ScaleMatrix(&m.m, &scale);
    for (i = 0; i < 18; i++)
    {
        ApplyMatrixSV(&m.m, &D_8011BEE8[i], &rig->pos_8[i]);
        rig->pos_8[i].x += wp->position.x;
        rig->pos_8[i].y += wp->position.y;
        rig->pos_8[i].z += wp->position.z;
    }
}

void func_8010F724(STAGE_OBJ *wp)
{
    D_8011BF78[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    func_80032538(wp);
    func_800334C4(wp);
}

void func_8010F7DC(STAGE_OBJ *wp)
{
    STCOM_SVECTOR pos[3] = {{-14000, -9000, 4000, 0}, {0, -8000, 0, 0}, {-4000, -8000, 0, 0}};
    sint32 i;

    wp->flags_0 |= 2;
    i = 0;
    switch (STAGE_SCENE_BYTE(8))
    {
        case 0:
            wp->rotation.y   = -0x30;
            wp->rotation.z   = 0x40;
            wp->u_C.b.byte_C = 0;
            break;
        case 9:
            i = 1;
            break;
        case 10:
            i              = 2;
            wp->rotation.z = 0x30;
            break;
    }
    wp->position.x = pos[i].x;
    wp->position.y = pos[i].y;
    wp->position.z = pos[i].z;
    wp->routine_1  = i + 1;
    func_8002F9EC(wp, (sint32)&wp->variant_3);
    wp->scale.words[0] = 0x0C000C00;
    wp->scale.words[1] = 0xC00;
    wp->scale.v.pad    = 0x4210;
    func_800322A8(wp, 0, 0);
}

void func_8010F944(STAGE_OBJ *wp)
{
    if (wp->u_C.b.byte_C == 1)
    {
        wp->position.x += 0x6E - ((Scene_work.value_10 - 0x186) / 20) * 0xF;
    }
    else if (wp->u_C.b.byte_C == 2)
    {
        wp->position.x += 8;
        wp->rotation.z -= 1;
    }
}

void func_8010F9C8(STAGE_OBJ *wp)
{
    if (Scene_work.value_10 < 0x30)
    {
        wp->rotation.z += 2;
        wp->position.x += 5;
    }
    else
    {
        wp->position.x += 0x18;
    }
}

void func_8010FA14(STAGE_OBJ *wp)
{
    if (Scene_work.value_10 < 0x64)
    {
        wp->position.x += 0x28;
    }
    else if (Scene_work.value_10 < 0x8C)
    {
        wp->rotation.z -= 2;
        wp->position.x += 0xC;
    }
    else
    {
        wp->position.y += D_800BBCF8[ST17_FRAME & 0x3F] >> 11;
    }
}

void func_8010FAA0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->rotation.z = 0;
        wp->position.x = 0;
        wp->position.y = -0xBB8;
        wp->position.z = 0;
        wp->routine_2++;
    }
    wp->position.z -= 0x30;
}

void func_8010FAE0(STAGE_OBJ *wp)
{
    D_8011C0E0[wp->routine_0](wp);
}

void func_8010FB1C(STCOM23_WORK *wp)
{
    STCOM_SVECTOR v;
    STCOM_FIXED_VECTOR n;
    STCOM_FIXED_VECTOR out;
    // Never used; it reserves retail's frame.
    STCOM_MATRIX unused;
    sint32 speed;

    wp->value_BC = 0;
    wp->value_C0 = 0;
    wp->hit_C4   = 0;
    wp->value_C8 = 0;
    wp->flags_0 |= 6;
    wp->model_78 = D_8011BF8C[wp->variant_3].model_10;
    v.x          = 0;
    v.y          = 0;
    v.z          = -0x1000;
    ApplyMatrix(&wp->matrix, &v, &out);
    VectorNormal(&out, &n);
    v.x        = n.x;
    v.y        = n.y;
    v.z        = n.z;
    wp->dir_CC = v;
    speed = wp->speed_6E = D_8011BF8C[wp->variant_3].speed_2;
    wp->velocity.x       = (v.x * speed) >> 4;
    wp->velocity.y       = (v.y * speed) >> 4;
    wp->velocity.z       = (v.z * speed) >> 4;
    speed                = D_8011BF8C[wp->variant_3].accel_4;
    wp->accel.x          = (v.x * speed) >> 4;
    wp->accel.y          = (v.y * speed) >> 4;
    wp->accel.z          = (v.z * speed) >> 4;
    wp->kind_2           = D_8011BF8C[wp->variant_3].kind_0;
    func_8002F9C4(wp, &D_8011BF8C[wp->variant_3].variant_1);
    wp->draw_pos.x         = wp->position.x;
    wp->draw_pos.y         = wp->position.y;
    wp->draw_pos.z         = wp->position.z;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->kind_2             = 0;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    wp->fixed_prev         = wp->position_fixed.v;
    wp->position_prev      = wp->position;
    wp->trail[0].v         = wp->position;
    wp->trail[1].v         = wp->trail[0].v;
    wp->trail[2].v         = wp->trail[1].v;
    wp->trail[3].v         = wp->trail[2].v;
    wp->color_B4           = 0x808080;
    wp->routine_0++;
    wp->life_B = D_8011BF8C[wp->variant_3].life_20;
    func_80110434(wp);
    D_8011C0C0[D_8011BF8C[wp->variant_3].type_1C](wp);
}

void func_8010FEC4(STCOM23_WORK *wp)
{
    STCOM_SVECTOR dir;
    STCOM_SVECTOR unit;
    STCOM_FIXED_VECTOR d;
    sint32 speed;
    sint32 result;

    result = func_80037694(wp, D_8011BF8C[wp->variant_3].value_22);
    if (result != 0)
    {
        if (result != 0x7FFF)
        {
            goto destroyed;
        }
        if (wp->hit_C4 & D_8011BF8C[wp->variant_3].hit_mask_24)
        {
            D_8011C0D0[D_8011BF8C[wp->variant_3].type_1C](wp);
            func_800318D8(wp);
        }
    }
    wp->fixed_prev    = wp->position_fixed.v;
    wp->position_prev = wp->position;
    wp->trail[3].v    = wp->trail[2].v;
    wp->trail[2].v    = wp->trail[1].v;
    wp->trail[1].v    = wp->trail[0].v;
    wp->trail[0].v    = wp->position;
    if (wp->life_B-- != 0)
    {
        d.x = wp->target_B8->x - wp->position.x;
        d.y = wp->target_B8->y - wp->position.y;
        d.z = wp->target_B8->z - wp->position.z;
        if (d.x > 0x687E || d.x < -0x687E || d.y > 0x687E || d.y < -0x687E || d.z > 0x687E ||
            d.z < -0x687E)
        {
            d.x >>= 2;
            d.y >>= 2;
            d.z >>= 2;
        }
        VectorNormalS(&d, &unit);
        func_80033F04(&dir, &unit, &wp->dir_CC, D_8011BF8C[wp->variant_3].turn_8,
                      D_8011BF8C[wp->variant_3].turn_C);
        wp->dir_CC     = dir;
        speed          = wp->speed_6E;
        wp->velocity.x = (dir.x * speed) >> 4;
        wp->velocity.y = (dir.y * speed) >> 4;
        wp->velocity.z = (dir.z * speed) >> 4;
        speed          = wp->speed_6E + D_8011BF8C[wp->variant_3].accel_4;
        if (speed >= D_8011BF8C[wp->variant_3].speed_max_6)
        {
            wp->speed_6E = D_8011BF8C[wp->variant_3].speed_max_6;
        }
        else
        {
            wp->speed_6E = speed;
        }
        func_801104DC(wp);
        wp->position_fixed.v.x += wp->velocity.x << 8;
        wp->position_fixed.v.y += wp->velocity.y << 8;
        wp->position_fixed.v.z += wp->velocity.z << 8;
        wp->draw_pos.x = wp->position.x = wp->position_fixed.f.x.words.integer;
        wp->draw_pos.y = wp->position.y = wp->position_fixed.f.y.words.integer;
        wp->draw_pos.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    }
    else
    {
    destroyed:
        D_8011C0D0[D_8011BF8C[wp->variant_3].type_1C](wp);
        func_800318D8(wp);
        return;
    }
    func_80110434(wp);
    func_801105F8(wp);
    D_8011C0C8[D_8011BF8C[wp->variant_3].type_1C](wp);
}

void func_8011033C(void)
{
}

void func_80110344(STAGE_OBJ *wp)
{
    Sound_call2(0x144, &wp->position);
}

void func_80110368(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_C = 0xA;
    Sound_call2(0x141, &wp->position);
}

void func_80110398(void)
{
}

void func_801103A0(STAGE_OBJ *wp)
{
    if (wp->u_C.b.byte_C != 0)
    {
        if (wp->u_C.b.byte_C == 1)
        {
            Sound_call2(0x142, &wp->position);
        }
        wp->u_C.b.byte_C--;
    }
}

void func_801103F4(STAGE_FX *wp)
{
    func_8011058C(wp);
}

void func_80110414(STAGE_FX *wp)
{
    func_8011058C(wp);
}

// Registers the hit box.
void func_80110434(STCOM23_WORK *wp)
{
    func_800341BC(&wp->position, D_8011BF8C[wp->variant_3].size_1F, 0, 0x8000, wp->index_1,
                  &wp->hit_C4, D_8011BF8C[wp->variant_3].hit_kind_21 | 0x40A0000, 0, 0x80);
    wp->hit_C4 = 0;
}

// Points the model along the velocity.
void func_801104DC(STCOM23_WORK *wp)
{
    STCOM_SVECTOR rotation;
    STCOM_FIXED_VECTOR scale;
    sint32 x;
    sint32 z;

    x          = wp->velocity.x;
    z          = wp->velocity.z;
    rotation.x = ratan2(wp->velocity.y, SquareRoot0(x * x + z * z));
    rotation.y = ratan2(x, z) + 0x800;
    rotation.z = 0;
    scale.x = scale.y = scale.z = 0x200;
    RotMatrixYXZ(&rotation, &wp->matrix);
    ScaleMatrix(&wp->matrix, &scale);
}

// A puff of smoke where it was.
void func_8011058C(STCOM23_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0           = 5;
        effect->kind_2            = 0x80;
        effect->variant_3         = 0x42;
        effect->sprite.position.x = wp->position.x;
        effect->sprite.position.y = wp->position.y;
        effect->sprite.position.z = wp->position.z;
    }
}

// Draws the smoke trail.
void func_801105F8(STCOM23_WORK *wp)
{
    STCOM23_PACKET *p;
    sint32 i;
    uint32 u;
    uint32 v;

    for (i = 0; i < 4; i++)
    {
        u          = D_8011C0D8[i].u;
        v          = D_8011C0D8[i].v;
        p          = func_8002D464();
        p->code_4  = 0x2E808080;
        p->xy_8    = wp->trail[i].words[0];
        p->z_10    = wp->trail[i].words[1];
        p->uv_C    = (v << 8) | 0x3D480000 | u;
        p->uv_14   = (v << 8) | 0x2E0000 | (u + 0x1F);
        p->uv_1C   = ((v + 0x1F) << 8) | u;
        p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
        p->size_18 = 0x14;
    }
}

void func_801106D8(STCOM18_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8011C104[wp->routine_0](wp);
}

void func_80110774(STCOM18_WORK *wp)
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
            wp->sprite.value_E = D_8011C0EC[0].a;
            wp->sprite.value_F = D_8011C0EC[0].b;
        }
        else
        {
            wp->sprite.value_E = D_8011C0F8[0].a;
            wp->sprite.value_F = D_8011C0F8[0].b;
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

void func_80110938(STCOM18_WORK *wp)
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
            wp->sprite.value_E = D_8011C0EC[frame].a;
            wp->sprite.value_F = D_8011C0EC[frame].b;
        }
        else
        {
            wp->sprite.value_E = D_8011C0F8[frame].a;
            wp->sprite.value_F = D_8011C0F8[frame].b;
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

void func_80110BA0(STAGE_10C *wp)
{
    ST17_MARK *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        if (wp->value_F & 1)
        {
            func_80110C0C(wp, ep);
        }
        else
        {
            func_80110C4C(wp, ep);
        }
    }
    wp->flags_0 = 0;
    func_800318D8(wp);
}

void func_80110C0C(STAGE_10C *wp, ST17_MARK *ep)
{
    ep->flags_0   = 7;
    ep->kind_2    = 0x80;
    ep->variant_3 = 0x42;
    ep->pos_38    = wp->position;
}

void func_80110C4C(STAGE_10C *wp, ST17_MARK *ep)
{
    ep->flags_0   = 3;
    ep->kind_2    = 0x83;
    ep->variant_3 = 0;
    ep->x_1C      = wp->position.x;
    ep->y_1E      = -1;
    ep->z_20      = wp->position.z;
}

void func_80110C7C(STAGE_OBJ *wp)
{
    D_8011C128[wp->routine_0](wp);
}

void func_80110CB8(ST17_10C_B *wp)
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

void func_80110DAC(ST17_10C *wp)
{
    wp->count_CC++;
    wp->sprite.pos_8[0] = wp->position.x;
    wp->sprite.pos_8[1] = wp->position.y;
    wp->sprite.pos_8[2] = wp->position.z;
    if (wp->routine_3 == 0)
    {
        wp->byte_C = 1;
        wp->routine_0++;
        wp->sprite.dir_1C = func_8011134C(wp);
        Sound_call2(0xF1, &wp->position);
    }
    else
    {
        func_801114E4(wp);
    }
}

void func_80110E58(ST17_10C_B *wp)
{
    STCOM_SVECTOR dir;
    STCOM_SVECTOR target;
    sint32 hit;

    hit = func_80049C24(wp);
    if (hit != 0)
    {
        func_80037738(hit, D_8011C11C[wp->byte_D]);
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
        target = func_8011134C((ST17_10C *)wp);
        func_80033F04(&dir, &target, &wp->sprite.dir_1C, 0x32, 0xFFFB10B);
        wp->sprite.dir_1C    = dir;
        wp->value_44.half[0] = (dir.x * 25) >> 2;
        wp->value_44.half[1] = (dir.y * 25) >> 2;
        wp->value_48.half[0] = (dir.z * 25) >> 2;
        wp->position_fixed.v.x += wp->value_44.half[0] << 8;
        wp->position_fixed.v.y += wp->value_44.half[1] << 8;
        wp->position_fixed.v.z += wp->value_48.half[0] << 8;
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_8011142C((ST17_TRAIL *)wp);
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
                      D_8011C110[wp->byte_D] | 0x49000000, 0, 0x80);
    }
    wp->sprite.hit_14 = 0;
}

void func_80111298(ST17_10C *wp)
{
    uint8 c;
    uint8 g;

    if (wp->count_CC < 4)
    {
        c                       = 0x40 - wp->count_CC * 0x10;
        g                       = 0xE0 - wp->count_CC * 0x38;
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
        func_80111780(wp);
    }
}

STCOM_SVECTOR func_8011134C(ST17_10C *wp)
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

// code, xy, uv_1C, uv_24 first; this keeps source order and the other operand order.
void func_8011142C(ST17_TRAIL *wp)
{
    STCOM23_PACKET *p;
    uint8 i;

    for (i = 0; i < 6; i++)
    {
        p         = func_8002D464();
        p->code_4 = 0x2E80C080;
        // Index first: retail adds i * 8 to wp (not wp to it).
        p->xy_8    = (i + wp->point_D4)->xy_0;
        p->z_10    = (i + wp->point_D4)->z_4;
        p->uv_C    = 0x3D482080;
        p->uv_14   = 0x2E209F;
        p->uv_1C   = 0x3F80;
        p->uv_24   = 0x3F9F;
        p->size_18 = 0xC0 - i * 24;
        p->pad_20  = 0;
    }
}

void func_801114E4(ST17_10C *wp)
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
        if (D_8011C138[i].start_0 < t && t < D_8011C138[i].start_0 + 0x10)
        {
            p      = func_8002D464();
            t      = wp->count_CC - D_8011C138[i].start_0;
            angle  = (D_8011C138[i].angle_4 + t * 24) & 0xFFF;
            height = D_8011C138[i].height_6 - t * (D_8011C138[i].height_6 / 16);
            radius = D_8011C138[i].radius_2 - t * (D_8011C138[i].radius_2 / 16);
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
        if (t == D_8011C138[i].start_0 + 0x10)
        {
            wp->routine_3--;
            wp->sprite.value_10 += 8;
        }
    }
}

void func_80111780(ST17_10C *wp)
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
        if (wp->count_CC < D_8011C138[i].start_0 + 0x10)
        {
            p = func_8002D464();
            if (wp->count_CC < D_8011C138[i].start_0)
            {
                r      = 0x60;
                g      = 0xE0;
                b      = 0x60;
                angle  = D_8011C138[i].angle_4;
                height = (D_8011C138[i].height_6 / 16) * wp->count_CC;
                radius = (D_8011C138[i].radius_2 / 16) * wp->count_CC;
            }
            else
            {
                t      = wp->count_CC - D_8011C138[i].start_0;
                r      = 0x60 - t * 6;
                g      = -0x20 - t * 14;
                b      = r;
                angle  = D_8011C138[i].angle_4;
                height = D_8011C138[i].start_0 * (D_8011C138[i].height_6 / 16);
                radius = D_8011C138[i].start_0 * (D_8011C138[i].radius_2 / 16);
                height += t * (D_8011C138[i].height_6 / 32);
                radius += t * (D_8011C138[i].radius_2 / 32);
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
        if (wp->count_CC == D_8011C138[i].start_0 + 0x10)
        {
            wp->routine_3--;
        }
    }
}

void func_80111A7C(ST17_10C *wp)
{
    D_8011C1F8[wp->routine_0](wp, &wp->part_D0);
}

void func_80111AB8(ST17_10C *wp, ST17_PART_D0 *part)
{
    uint32 r;
    sint16 r16;

    wp->flags_0 |= 2;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    part->flags_0           = 0;
    part->value_1           = 0;
    part->value_4           = 0;
    part->value_6           = 0;
    r                       = rand();
    r16                     = r; // case 2 reads a 16-bit copy (keeps its own register)
    switch (wp->variant_3)
    {
        case 0:
        case 1:
            if (wp->byte_C == 0)
            {
                part->value_A        = wp->position.x - ((r & 0xF) + 0x1900);
                wp->value_44.half[0] = -0x50 - (sint32)((r >> 2) & 3);
            }
            else
            {
                part->value_A        = wp->position.x + ((r & 0xF) + 0x1900);
                wp->value_44.half[0] = ((r >> 2) & 3) + 0x50;
            }
            wp->value_44.words.integer  = 0;
            wp->value_48.words.fraction = 0;
            wp->sprite.mode_0           = 0x3D08000E;
            wp->sprite.color_4.word     = 0x2C808080;
            wp->sprite.value_E          = D_8011C210[0];
            wp->sprite.value_F          = D_8011C211[0];
            break;
        case 2:
            switch (wp->byte_C)
            {
                case 0:
                case 7:
                    wp->value_4C.half[0] = -0x20 - (r16 & 0xF);
                    break;
                case 1:
                case 6:
                    wp->value_4C.half[0] = -0x10 - (r16 & 7);
                    break;
                case 2:
                case 5:
                    wp->value_4C.half[0] = (r16 & 7) + 0x10;
                    break;
                case 3:
                case 4:
                    wp->value_4C.half[0] = (r16 & 0xF) + 0x20;
                    break;
            }
            if (!(wp->byte_C & 1))
            {
                wp->value_4C.words.integer = -0x20 - (sint32)((r16 >> 3) & 0xF);
                wp->value_50               = -0x10;
            }
            else
            {
                wp->value_4C.words.integer = ((r16 >> 3) & 0xF) + 0x20;
                wp->value_50               = -0x10;
            }
            part->value_E           = (r16 >> 6) & 0xF;
            wp->sprite.mode_0       = 0x3C48000E;
            wp->sprite.color_4.word = 0x2C808080;
            wp->sprite.value_E      = D_8011C21C[0];
            wp->sprite.value_F      = D_8011C21D[0];
            break;
    }
    part->value_C       = wp->byte_F + wp->byte_D * 2;
    wp->sprite.value_10 = 0x40;
    wp->value_C8        = 0;
    wp->value_C4        = 0;
    wp->value_C0        = 0;
    wp->value_BC        = 0;
    wp->routine_0       = 1;
    wp->routine_1       = 0;
    wp->routine_2       = 0;
    wp->routine_3       = 0;
    wp->sprite.pos_8[0] = wp->position.x;
    wp->sprite.pos_8[1] = wp->position.y;
    wp->sprite.pos_8[2] = wp->position.z;
}

void func_80111D54(ST17_10C *wp, ST17_PART_D0 *part)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    part->random_2          = rand();
    D_8011C204[wp->variant_3](wp, part);
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    wp->sprite.pos_8[0]    = wp->position.x;
    wp->sprite.pos_8[1]    = wp->position.y;
    wp->sprite.pos_8[2]    = wp->position.z;
    func_80112748(wp, part);
    if (part->flags_0 & 1)
    {
        part->flags_0 &= ~1;
        wp->routine_0 = 2;
        wp->routine_1 = 0;
    }
}

void func_80111E80(ST17_10C *wp, ST17_PART_D0 *part)
{
    ST17_MARK *ep;

    switch (wp->routine_1)
    {
        case 0:
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 5;
                ep->kind_2    = 0x80;
                ep->variant_3 = 0x41;
                ep->pos_38    = wp->position;
                ep->value_D   = 0;
            }
            wp->routine_1++;
            break;
        case 1:
            func_800318D8(wp);
            break;
    }
}

void func_80111F2C(ST17_10C *wp, ST17_PART_D0 *part)
{
    uint8 frame;

    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    frame              = (part->value_1 >> 1) % 6;
    wp->sprite.value_E = D_8011C210[frame * 2];
    wp->sprite.value_F = D_8011C211[frame * 2];
    part->value_1++;
}

void func_80111FCC(ST17_10C *wp, ST17_PART_D0 *part)
{
    uint8 frame;

    switch (wp->routine_1)
    {
        case 0:
            part->value_8 = (rand() & 7) * 0x84 + 0x3A0;
            if (wp->byte_C == 1)
            {
                part->value_8 = -part->value_8;
            }
            wp->routine_1++;
            break;
        case 1:
            if (wp->byte_C == 0)
            {
                if (wp->position.x < part->value_8)
                {
                    wp->routine_1++;
                }
            }
            else if (wp->position.x > part->value_8)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (part->value_4 < 0x10)
            {
                if (wp->byte_C == 0)
                {
                    wp->value_44.half[0]++;
                }
                else
                {
                    wp->value_44.half[0]--;
                }
                wp->value_44.half[1]++;
                part->value_4++;
            }
            else
            {
                wp->routine_1++;
            }
            break;
    }
    wp->position.x += wp->value_44.half[0];
    wp->position.y += wp->value_44.half[1];
    wp->position.z += wp->value_48.half[0];
    frame              = (part->value_1 >> 1) % 6;
    wp->sprite.value_E = D_8011C210[frame * 2];
    wp->sprite.value_F = D_8011C211[frame * 2];
    part->value_1++;
}

void func_801121CC(ST17_10C *wp, ST17_PART_D0 *part)
{
    sint16 d;
    uint8 index;

    part->dx_10 = ST17_TARGET_CC(wp)->x - wp->position.x;
    part->dy_12 = ST17_TARGET_CC(wp)->y - wp->position.y;
    part->dz_14 = ST17_TARGET_CC(wp)->z - wp->position.z;
    switch (wp->routine_1)
    {
        case 0:
            if (part->value_4 < 0x10)
            {
                wp->value_44.half[0] = (wp->value_4C.half[0] / 16) * (0x10 - part->value_4);
                wp->value_44.half[1] = (wp->value_4C.half[1] / 16) * (0x10 - part->value_4);
                wp->value_48.half[0] = (wp->value_50 / 16) * (0x10 - part->value_4);
                part->value_4++;
            }
            else
            {
                part->value_4        = 0;
                wp->value_44.half[0] = 0;
                wp->value_44.half[1] = 0;
                wp->value_48.half[0] = 0;
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = 0;
                wp->value_50         = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            if (part->value_4 < 0x40)
            {
                switch (part->value_4 >> 2)
                {
                    case 6:
                        wp->value_4C.half[1] = -1;
                        break;
                    case 2:
                    case 10:
                        wp->value_4C.half[1] = 0;
                        break;
                    case 0:
                    case 14:
                        wp->value_4C.half[1] = 1;
                        break;
                }
                part->value_4++;
                wp->value_44.half[1] += wp->value_4C.half[1];
            }
            else
            {
                part->value_4        = 0;
                wp->value_44.half[0] = 0;
                wp->value_44.half[1] = 0;
                wp->value_48.half[0] = 0;
                wp->value_4C.half[0] = 0;
                wp->value_4C.half[1] = 0;
                wp->value_50         = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            d = part->dx_10 >> 6;
            if (part->dx_10 > 0)
            {
                wp->value_44.half[0] = d + 4;
            }
            else
            {
                wp->value_44.half[0] = d - 4;
            }
            d = part->dy_12 >> 6;
            if (part->dy_12 > 0)
            {
                wp->value_44.half[1] = d + 4;
            }
            else
            {
                wp->value_44.half[1] = d - 4;
            }
            d = part->dz_14 >> 6;
            if (part->dz_14 > 0)
            {
                wp->value_48.half[0] = d + 4;
            }
            else
            {
                wp->value_48.half[0] = d - 4;
            }
            if (STCOM_ABS(part->dx_10) < 0x400 || STCOM_ABS(part->dy_12) < 0x400 ||
                STCOM_ABS(part->dz_14) < 0x400)
            {
                part->value_4 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (part->value_E == 0)
            {
                d = part->dx_10 >> 4;
                if (part->dx_10 > 0)
                {
                    wp->value_44.half[0] = d + 0xC;
                }
                else
                {
                    wp->value_44.half[0] = d - 0xC;
                }
                d = part->dy_12 >> 4;
                if (part->dy_12 > 0)
                {
                    wp->value_44.half[1] = d + 0xC;
                }
                else
                {
                    wp->value_44.half[1] = d - 0xC;
                }
                d = part->dz_14 >> 4;
                if (part->dz_14 > 0)
                {
                    wp->value_48.half[0] = d + 0xC;
                }
                else
                {
                    wp->value_48.half[0] = d - 0xC;
                }
            }
            else
            {
                d = part->dx_10 >> 5;
                if (part->dx_10 > 0)
                {
                    wp->value_44.half[0] = d + 8;
                }
                else
                {
                    wp->value_44.half[0] = d - 8;
                }
                d = part->dy_12 >> 5;
                if (part->dy_12 > 0)
                {
                    wp->value_44.half[1] = d + 8;
                }
                else
                {
                    wp->value_44.half[1] = d - 8;
                }
                d = part->dz_14 >> 5;
                if (part->dz_14 > 0)
                {
                    wp->value_48.half[0] = d + 8;
                }
                else
                {
                    wp->value_48.half[0] = d - 8;
                }
            }
            if (part->value_4 < 0x100)
            {
                part->value_4++;
            }
            else
            {
                part->value_4 = 0;
                part->flags_0 |= 1;
            }
            if (STCOM_ABS(part->dx_10) < 0x28 && STCOM_ABS(part->dy_12) < 0x28 &&
                STCOM_ABS(part->dz_14) < 0x28)
            {
                part->value_4 = 0;
                part->flags_0 |= 1;
            }
            break;
    }
    wp->position.x += wp->value_44.half[0] + ((part->random_2 >> 2) & 3);
    wp->position.y += wp->value_44.half[1] + ((part->random_2 >> 4) & 3);
    wp->position.z += wp->value_48.half[0];
    if (wp->routine_1 == 0)
    {
        wp->sprite.value_E = D_8011C21C[0];
        wp->sprite.value_F = D_8011C21D[0];
    }
    else
    {
        index              = part->value_1 & 0x1E;
        wp->sprite.value_E = D_8011C21C[index];
        wp->sprite.value_F = D_8011C21D[index];
        part->value_1++;
    }
}

void func_80112748(ST17_10C *wp, ST17_PART_D0 *part)
{
    sint32 flag;
    sint32 variant;

    if (wp->value_BC & 0x0A000000)
    {
        part->flags_0 |= 1;
    }
    else
    {
        flag    = (wp->byte_E != 0) << 7;
        variant = wp->variant_3;
        if (variant >= 0)
        {
            if (variant < 2)
            {
                if ((wp->byte_C == 0 && wp->position.x < part->value_A) ||
                    (wp->byte_C == 1 && wp->position.x > part->value_A))
                {
                    part->flags_0 |= 1;
                }
            }
        }
        func_800341BC(&wp->position, 0x40, 0, 0x8000, wp->reserved01, &wp->value_BC,
                      part->value_C | 0x04000000, 0, flag);
    }
    wp->value_BC = 0;
    if (func_80049C24(wp) != 0)
    {
        part->flags_0 |= 1;
    }
}

void func_80112874(STAGE_OBJ *wp)
{
    D_8011C248[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_801128C4(ST17_SHL *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR v;

    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = D_8011C23C;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    if (wp->type_3 & 0x40)
    {
        rot.x = wp->rot_x;
    }
    else
    {
        func_800354E0(wp->bit_d);
        rot.x = func_80039B80();
    }
    rot.y = wp->rot_y & 0xFFF;
    rot.z = 0;
    if (wp->type_3 & 0x40)
    {
        rot.x += ((rand() & 7) - 4) * 2;
        rot.y += ((rand() & 7) - 4) * 2;
    }
    else
    {
        switch (ST17_PL_SBYTE(0x508))
        {
            case 0:
                rot.x += ((rand() & 3) - 2) * 2;
                rot.y += ((rand() & 3) - 2) * 2;
                break;
            case 1:
                rot.x += ((rand() & 7) - 4) * 2;
                rot.y += ((rand() & 7) - 4) * 2;
                break;
            case 2: // shares default; listing it gives retail's compare tree
            default:
                rot.x += ((rand() & 0xF) - 8) * 2;
                rot.y += ((rand() & 0xF) - 8) * 2;
                break;
        }
    }
    RotMatrixYXZ(&rot, &wp->mtx_8c);
    v.y = 0x1000;
    v.z = 0x1000;
    v.x = 0x1000;
    ScaleMatrix(&wp->mtx_8c, &v);
    rot.x = 0;
    rot.y = 0;
    rot.z = -0x1000;
    ApplyMatrix(&wp->mtx_8c, &rot, &v);
    if (!(wp->type_3 & 0x40) && ST17_PL_SBYTE(0x507) >= 3)
    {
        wp->vel.x = (uint32)(v.x * 15) >> 1;
        wp->vel.y = (uint32)(v.y * 15) >> 1;
        wp->vel.z = (uint32)(v.z * 15) >> 1;
    }
    else
    {
        wp->vel.x = (uint32)(v.x * 25) >> 2;
        wp->vel.y = (uint32)(v.y * 25) >> 2;
        wp->vel.z = (uint32)(v.z * 25) >> 2;
    }
    wp->ax     = 0;
    wp->ay     = 0;
    wp->az     = 0;
    wp->hit_7c = 0;
    if (wp->type_3 & 0x40)
    {
        wp->fpos.v.x += wp->vel.x * 0x1C0;
        wp->fpos.v.y += wp->vel.y * 0x1C0;
        wp->fpos.v.z += wp->vel.z * 0x1C0;
    }
    wp->mpos.x = wp->pos.x = wp->fpos.f.x.words.integer;
    wp->mpos.y = wp->pos.y = wp->fpos.f.y.words.integer;
    wp->mpos.z = wp->pos.z = wp->fpos.f.z.words.integer;
    wp->old_fpos           = wp->fpos;
    wp->old_pos            = wp->pos;
    wp->color_b4           = 0x02808080;
    wp->kind_2             = 0x82;
    func_8002F9C4(wp, 0);
    wp->kind_2  = 0x2E;
    wp->timer_b = func_80037634(&Player_work, 2);
    wp->routine_0++;
    func_80112F88(wp, 0);
    func_80112E44(wp);
    Sound_call2(0x120, &wp->pos);
}

void func_80112CCC(ST17_SHL *wp)
{
    if (func_80037694((STCOM23_WORK *)wp, 0) || wp->hit_7c)
    {
        if (wp->type_3 & 0x40)
        {
            func_800318D8(wp);
        }
        else
        {
            func_80031930(wp);
        }
        func_80112F88(wp, 1);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    if (wp->timer_b-- != 0)
    {
        wp->fpos.v.x += wp->vel.x << 8;
        wp->fpos.v.y += wp->vel.y << 8;
        wp->fpos.v.z += wp->vel.z << 8;
        wp->mpos.x = wp->pos.x = wp->fpos.f.x.words.integer;
        wp->mpos.y = wp->pos.y = wp->fpos.f.y.words.integer;
        wp->mpos.z = wp->pos.z = wp->fpos.f.z.words.integer;
    }
    else
    {
        if (wp->type_3 & 0x40)
        {
            func_800318D8(wp);
        }
        else
        {
            func_80031930(wp);
        }
        return;
    }
    func_80112E44(wp);
}

void func_80112E44(ST17_SHL *wp)
{
    STCOM_SVECTOR p;
    sint32 flags;

    flags = func_800375D4(&Player_work, 2);
    p.x   = wp->pos.x * 2 - wp->old_pos.x;
    p.y   = wp->pos.y * 2 - wp->old_pos.y;
    p.z   = wp->pos.z * 2 - wp->old_pos.z;
    if (ST17_PL_SBYTE(0x171) == 0)
    {
        flags = 0x1000;
    }
    if (wp->type_3 & 0x40)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0xA000, wp->value_1, &wp->col_c4, 0x8000005,
                      0, 0x80);
    }
    else if (wp->index_c)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x6000, wp->value_1, &wp->col_c4,
                      flags | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x4000, wp->value_1, &wp->col_c4,
                      flags | 0x8000000, 0, 0x80);
    }
}

void func_80112F88(ST17_SHL *wp, sint32 arg)
{
    ST17_SHL_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->routine_0 = 1;
        fx->kind_2    = 0x85;
        fx->x_1c      = wp->pos.x;
        fx->y_1e      = wp->pos.y;
        fx->z_20      = wp->pos.z;
        fx->vx_30     = wp->vel.x;
        fx->vy_32     = wp->vel.y;
        fx->vz_34     = wp->vel.z;
        if (wp->type_3 == 0x40)
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type_3 == 0x41)
        {
            fx->value_40 = (wp->rot_y - 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type_3 == 0x42)
        {
            fx->value_40 = 0xFFFF;
            fx->flag_3   = arg + 0x10;
        }
        else
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg;
        }
    }
}

void func_80113088(STAGE_OBJ *wp)
{
    D_8011C250[wp->variant_3](wp);
}

void func_801130C4(STAGE_FX *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->mode_14  = 0x3D48000E;
        wp->color_18 = 0x2E808080;
        wp->u_22     = D_8011C264[0];
        wp->v_23     = D_8011C265[0];
        wp->w_24     = 0x60;
        wp->value_C  = 0;
        wp->timer_D  = 0;
        wp->routine_0++;
    }
    if (wp->value_C < 12)
    {
        wp->timer_D = (wp->value_C >> 1) % 6;
        wp->u_22    = D_8011C264[wp->timer_D * 2];
        wp->v_23    = D_8011C265[wp->timer_D * 2];
        wp->y_1E -= 6 + (rand() & 7);
        wp->z_20 += 12 + (rand() & 7);
        wp->value_C++;
        wp->w_24 += 2;
        wp->color_18 -= 0x80808;
    }
    else
    {
        func_80031988(wp);
    }
}

void func_80113234(ST17_MARK *wp)
{
    ST17_MARK *ep;
    sint16 r;
    sint16 dx;
    sint16 dz;
    sint32 t;

    if (wp->value_E % 5 == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 5;
            ep->kind_2    = 0x80;
            ep->variant_3 = 0x41;
            ep->value_D   = 2;
            ep->pos_38    = *wp->target_44;
            r             = rand();
            t             = (r >> 2) & 0x1FF;
            dx            = t;
            if (!(r & 1))
            {
                dx = -t;
            }
            t  = (r >> 6) & 0x1FF;
            dz = t;
            if (!((r >> 4) & 1))
            {
                dz = -t;
            }
            ep->pos_38.x += dx;
            ep->pos_38.y += 0x400 - ((r >> 8) & 0xFF);
            ep->pos_38.z += dz;
        }
    }
    if (++wp->value_E == 41)
    {
        func_80031988(wp);
    }
}

void func_8011338C(ST17_MARK *wp)
{
    ST17_MARK *ep;
    STCOM_SVECTOR *pos;
    sint16 r;
    sint16 dx;
    sint16 dy;
    sint16 dz;

    if (wp->value_E % 5 == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 5;
            ep->kind_2    = 0x80;
            ep->variant_3 = 0x41;
            ep->value_D   = 2;
            ep->pos_38    = *wp->target_44;
            pos           = &ep->pos_38;
            r             = rand();
            if (r & 1)
            {
                dx = ((r >> 2) & 0xFF) - 0x300;
            }
            else
            {
                dx = -0x300 - ((r >> 2) & 0x1FF);
            }
            if ((r >> 4) & 1)
            {
                dy = 0x180 - ((r >> 6) & 0xFF);
            }
            else
            {
                dy = ((r >> 6) & 0xFF) - 0x180;
            }
            if ((r >> 8) & 1)
            {
                dz = 0x100 - ((r >> 10) & 0xFF);
            }
            else
            {
                dz = ((r >> 10) & 0xFF) - 0x100;
            }
            pos->x += dx;
            pos->y += dy;
            pos->z += dz;
        }
    }
    if (++wp->value_E == 41)
    {
        func_80031988(wp);
    }
}

void func_80113528(ST17_MARK *wp)
{
    ST17_MARK *ep;
    STCOM_SVECTOR *pos;
    sint16 r;
    sint16 dx;
    sint16 dy;
    sint16 dz;

    if (wp->value_E % 5 == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 5;
            ep->kind_2    = 0x80;
            ep->variant_3 = 0x41;
            ep->value_D   = 2;
            ep->pos_38    = *wp->target_44;
            pos           = &ep->pos_38;
            r             = rand();
            if (r & 1)
            {
                dx = 0x300 - ((r >> 2) & 0xFF);
            }
            else
            {
                dx = ((r >> 2) & 0x1FF) + 0x300;
            }
            if ((r >> 4) & 1)
            {
                dy = 0x180 - ((r >> 6) & 0xFF);
            }
            else
            {
                dy = ((r >> 6) & 0xFF) - 0x180;
            }
            if ((r >> 8) & 1)
            {
                dz = 0x100 - ((r >> 10) & 0xFF);
            }
            else
            {
                dz = ((r >> 10) & 0xFF) - 0x100;
            }
            pos->x += dx;
            pos->y += dy;
            pos->z += dz;
        }
    }
    if (++wp->value_E == 41)
    {
        func_80031988(wp);
    }
}

void func_801136C4(ST17_MARK *wp)
{
    ST17_MARK *ep;
    sint16 r;
    sint16 dx;
    sint16 dy;
    sint32 t;

    if (wp->value_E % 5 == 0)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 5;
            ep->kind_2    = 0x80;
            ep->variant_3 = 0x41;
            ep->value_D   = 2;
            ep->pos_38    = *wp->target_44;
            r             = rand();
            t             = (r >> 2) & 0x1FF;
            dx            = t;
            if (!(r & 1))
            {
                dx = -t;
            }
            t  = (r >> 6) & 0x1FF;
            dy = t;
            if (!((r >> 4) & 1))
            {
                dy = -t;
            }
            ep->pos_38.x += dx;
            ep->pos_38.y += dy;
            ep->pos_38.z += -0x280 + ((r >> 8) & 0xFF);
        }
    }
    if (++wp->value_E == 51)
    {
        func_80031988(wp);
    }
}

void func_8011381C(STAGE_OBJ *wp)
{
    D_8011C288[wp->variant_3](wp);
}

void func_80113858(STAGE_OBJ *wp)
{
    D_8011C290[wp->routine_0](wp);
}

void func_80113894(STAGE_FX *wp)
{
    STCOM_SVECTOR v;
    STCOM_SVECTOR joint;
    STCOM_FIXED_VECTOR out;
    STCOM_MATRIX m;
    ST17_JOINT_OWNER *owner;

    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->routine_0 = 1;
    wp->flags_6 |= 0x20;
    wp->type_F   = 0;
    wp->color_18 = 0x2E404040;
    wp->mode_14  = 0x3D080029;
    wp->frame_E  = 2;
    wp->u_22     = D_8011C270[wp->type_F * 2];
    wp->v_23     = D_8011C271[wp->type_F * 2];
    wp->w_24     = 0x30;
    owner        = func_80036294(wp->value_C);
    m            = owner->matrix_1E8[wp->timer_D];
    v.x          = D_8011C2A4[wp->timer_D - 1].x;
    v.y          = 0;
    v.z          = D_8011C2A4[wp->timer_D - 1].z;
    ApplyMatrix(&m, &v, &out);
    joint = owner->joint_180[wp->timer_D];
    out.x += joint.x;
    out.y += joint.y;
    out.z += joint.z;
    wp->x_1C       = out.x;
    wp->y_1E       = out.y;
    wp->z_20       = out.z;
    wp->u_28.count = wp->timer_D * 10 + 0xA0;
}

void func_80113A70(STAGE_OBJ *wp)
{
    if (--wp->position_fixed.v.pad == 0)
    {
        wp->routine_0            = 2;
        wp->position_fixed.v.pad = 4;
    }
}

void func_80113A9C(STAGE_FX *wp)
{
    func_80114250(wp->u_28.count);
    if (--wp->u_28.count == 0)
    {
        wp->routine_0 = 3;
        wp->flags_0 |= 2;
    }
}

void func_80113AF4(STAGE_FX *wp)
{
    if (--wp->frame_E == 0)
    {
        wp->frame_E = 2;
        wp->type_F++;
        wp->u_22 = D_8011C270[wp->type_F * 2];
        wp->v_23 = D_8011C271[wp->type_F * 2];
        if (wp->type_F == 2)
        {
            wp->color_18 = 0x2E808080;
        }
        wp->mode_14 = 0x3D480009;
    }
    wp->w_24++;
    if (wp->type_F == 0xB)
    {
        wp->routine_0 = 4;
    }
}

void func_80113BA4(STAGE_FX *wp)
{
    sint8 temp_v0;

    temp_v0     = (uint8)wp->frame_E - 1;
    wp->frame_E = temp_v0;
    if ((temp_v0 << 0x18) == 0)
    {
        func_80031988(wp);
    }
}

void func_80113BE0(STAGE_OBJ *wp)
{
    D_8011C2B0[wp->routine_0](wp);
}

void func_80113C1C(STAGE_FX *wp)
{
    wp->routine_1 = 0;
    wp->routine_0 = 1;
    wp->routine_3 = wp->timer_D;
    wp->color_18  = 0x2EC0C0C0;
    wp->mode_14   = 0x3D08002E;
    wp->frame_E   = 0x10;
    wp->u_22      = 0xE0;
    wp->routine_2 = 0;
    wp->type_F    = 0;
    wp->timer_D   = wp->timer_D * 6 + 8;
    wp->v_23      = 0x60;
}

void func_80113C84(ST17_BURST *wp)
{
    uint32 i;
    uint32 j;
    sint16 d;
    ST17_JOINT_OWNER *owner;
    uint32 h;
    uint8 *pairs;
    uint8 *pair;

    pairs = wp->pair_28[0];
    if (--wp->timer_D == 0)
    {
        wp->routine_0 = 2;
        wp->flags_0 |= 2;
        if (STAGE_SCENE_BYTE(8) == 5 || STAGE_SCENE_BYTE(8) != 7)
        {
            i        = ((rand() & 0xF) + 0x10) << 6;
            d        = ((rand() & 7) + 0xD) << 7;
            h        = (uint32)(rsin(d) * 75) >> 8;
            d        = (uint32)(rcos(d) * 75) >> 8;
            wp->w_24 = 50;
        }
        else
        {
            i        = (rand() & 0x1F) << 6;
            d        = ((rand() & 7) + 0xC) << 7;
            h        = (uint32)(rsin(d) * 25) >> 6;
            d        = (uint32)(rcos(d) * 25) >> 6;
            wp->w_24 = 100;
        }
        owner    = func_80036294(wp->value_C);
        wp->x_1C = owner->position.x + ((rcos(i) * d) >> 12);
        wp->z_20 = owner->position.z + ((rsin(i) * d) >> 12);
        wp->y_1E = owner->position.y + h;
        j        = 0;
        pair     = pairs;
        do
        {
            j++;
            pair[0] = rand() & 0x1F;
            pair[1] = (rand() & 7) + 0xC;
            pair += 2;
        } while (j < 12);
        if (wp->routine_3 & 1)
        {
            if (rand() & 1)
            {
                Sound_call(0xA4, 0, 0);
            }
            else
            {
                Sound_call(0xA5, 0, 0);
            }
        }
        else if (!(rand() & 0xF))
        {
            Sound_call(0xA4, 0, 0);
        }
    }
}

void func_80113EC8(STAGE_FX *wp)
{
    sint32 c;

    wp->x_1C += (rcos(0) * 10) >> 12;
    wp->z_20 += (rsin(0) * 10) >> 12;
    wp->frame_E--;
    c            = wp->frame_E * 12;
    wp->color_18 = 0x2E000000 + (c << 16) + (c << 8) + c;
    wp->w_24 += 8;
    wp->timer_D++;
    wp->type_F++;
    func_80114060(wp);
    if (wp->frame_E == 0)
    {
        wp->routine_0 = 3;
        wp->flags_0 &= ~2;
    }
}

void func_80113FBC(STAGE_FX *wp)
{
    wp->x_1C += (rcos(0) * 10) >> 12;
    wp->z_20 += (rsin(0) * 10) >> 12;
    wp->timer_D++;
    wp->type_F--;
    func_80114060(wp);
    if (wp->type_F == 0)
    {
        func_80031988(wp);
    }
}

// Draws the burst's twelve sparks. The code constant is assigned inside the colour expression
// so loop.c keeps it in the loop (a literal is associated with c << 16 and hoisted), and the
// first uv word is computed before it so the u/v invariants are hoisted first.
void func_80114060(STAGE_FX *wp)
{
    STCOM_SVECTOR_W pos;
    uint8 *pairs;
    STCOM23_PACKET *p;
    uint8 *pair;
    sint32 latitude;
    sint32 longitude;
    sint32 h;
    sint16 dist;
    uint8 i;
    uint8 c;
    sint32 r;
    uint8 u;
    uint32 color;
    uint8 v;
    uint32 uv;

    pairs = ((ST17_BURST *)wp)->pair_28[0];
    i     = 0;
    c     = (uint8)(wp->type_F * 6);
    u     = 0x40;
    v     = 0;
    r     = wp->timer_D * 2 + 100;
    do
    {
        pair      = (uint8 *)(i * 2 + (uint32)pairs);
        latitude  = pair[1] << 7;
        h         = (rsin(latitude) * r) >> 12;
        dist      = (rcos(latitude) * r) >> 12;
        longitude = pair[0] << 7;
        pos.v.x   = wp->x_1C + ((rcos(longitude) * dist) >> 12);
        pos.v.z   = wp->z_20 + ((rsin(longitude) * dist) >> 12);
        pos.v.y   = wp->y_1E + h;
        p         = func_8002D464();
        uv        = 0x3D480000 | (v << 8) | u;
        p->code_4 = (c << 16) | ((c << 8) | (color = 0x2E000000)) | c;
        p->uv_C   = uv;
        p->uv_14  = 0x4E0000 | (v << 8) | (u + 0x1F);
        p->uv_1C  = ((v + 0x1F) << 8) | u;
        p->uv_24  = ((v + 0x1F) << 8) | (u + 0x1F);
        p->xy_8   = *(uint32 *)&pos.v.x;
        p->z_10   = *(uint32 *)&pos.v.z;
        if (STAGE_SCENE_BYTE(8) == 5 || STAGE_SCENE_BYTE(8) != 7)
        {
            p->size_18 = wp->timer_D + 0x50;
        }
        else
        {
            p->size_18 = wp->timer_D + 0x82;
        }
        i++;
        p->pad_20 = 0;
    } while (i < 12);
}

// Draws a translucent grey full-screen rectangle (level: its brightness in steps of 32).
void func_80114250(uint8 level)
{
    ST17_TILE *tile;
    DR_MODE *mode;
    sint32 c;

    c    = level << 5;
    tile = (ST17_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->code |= 2;
    tile->b0 = tile->g0 = tile->r0 = c;
    mode                           = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(mode, 0, 0, 0x2F, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&D_80098934->ot_74, tile);
    addPrim(&D_80098934->ot_74, mode);
}
