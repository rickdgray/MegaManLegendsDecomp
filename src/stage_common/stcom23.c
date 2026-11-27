#include "common.h"
#include "stage_common/stcom23.h"

// Shared stage code, linked into 4 stages: r3_st06, r3_st0b, r3_st10 and r3_st19. Each stage
// compiles this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the
// names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom23"

// A homing missile.
void stcom23_func_0000(STCOM23_WORK *wp)
{
    stcom23_D_0154[wp->routine_0](wp);
}

void stcom23_func_003C(STCOM23_WORK *wp)
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
    wp->be_flag |= 6;
    wp->model_78 = stcom23_D_0000[wp->type].model_10;
    v.x          = 0;
    v.y          = 0;
    v.z          = -0x1000;
    ApplyMatrix(&wp->matrix, &v, &out);
    VectorNormal(&out, &n);
    v.x        = n.x;
    v.y        = n.y;
    v.z        = n.z;
    wp->dir_CC = v;
    speed = wp->speed_6E = stcom23_D_0000[wp->type].speed_2;
    wp->velocity.x       = (v.x * speed) >> 4;
    wp->velocity.y       = (v.y * speed) >> 4;
    wp->velocity.z       = (v.z * speed) >> 4;
    speed                = stcom23_D_0000[wp->type].accel_4;
    wp->accel.x          = (v.x * speed) >> 4;
    wp->accel.y          = (v.y * speed) >> 4;
    wp->accel.z          = (v.z * speed) >> 4;
    wp->id               = stcom23_D_0000[wp->type].kind_0;
    Model_work_init(wp, &stcom23_D_0000[wp->type].variant_1);
    wp->draw_pos.x         = wp->position.x;
    wp->draw_pos.y         = wp->position.y;
    wp->draw_pos.z         = wp->position.z;
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->id                 = 0;
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
    wp->life_B = stcom23_D_0000[wp->type].life_20;
    stcom23_func_0954(wp);
    stcom23_D_0134[stcom23_D_0000[wp->type].type_1C](wp);
}

void stcom23_func_03E4(STCOM23_WORK *wp)
{
    STCOM_SVECTOR dir;
    STCOM_SVECTOR unit;
    STCOM_FIXED_VECTOR d;
    sint32 speed;
    sint32 result;

    result = func_80037694(wp, stcom23_D_0000[wp->type].value_22);
    if (result != 0)
    {
        if (result != 0x7FFF)
        {
            goto destroyed;
        }
        if (wp->hit_C4 & stcom23_D_0000[wp->type].hit_mask_24)
        {
            stcom23_D_0144[stcom23_D_0000[wp->type].type_1C](wp);
            Close_SHL_WORK(wp);
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
        if (d.x > 0x687E || d.x < -0x687E || d.y > 0x687E || d.y < -0x687E || d.z > 0x687E || d.z < -0x687E)
        {
            d.x >>= 2;
            d.y >>= 2;
            d.z >>= 2;
        }
        VectorNormalS(&d, &unit);
        func_80033F04(&dir, &unit, &wp->dir_CC, stcom23_D_0000[wp->type].turn_8, stcom23_D_0000[wp->type].turn_C);
        wp->dir_CC     = dir;
        speed          = wp->speed_6E;
        wp->velocity.x = (dir.x * speed) >> 4;
        wp->velocity.y = (dir.y * speed) >> 4;
        wp->velocity.z = (dir.z * speed) >> 4;
        speed          = wp->speed_6E + stcom23_D_0000[wp->type].accel_4;
        if (speed >= stcom23_D_0000[wp->type].speed_max_6)
        {
            wp->speed_6E = stcom23_D_0000[wp->type].speed_max_6;
        }
        else
        {
            wp->speed_6E = speed;
        }
        stcom23_func_09FC(wp);
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
        stcom23_D_0144[stcom23_D_0000[wp->type].type_1C](wp);
        Close_SHL_WORK(wp);
        return;
    }
    stcom23_func_0954(wp);
    stcom23_func_0B18(wp);
    stcom23_D_013C[stcom23_D_0000[wp->type].type_1C](wp);
}

void stcom23_func_085C(STCOM23_WORK *wp)
{
}

void stcom23_func_0864(STCOM23_WORK *wp)
{
    Sound_call2(0x144, &wp->position);
}

void stcom23_func_0888(STCOM23_WORK *wp)
{
    wp->timer_C = 10;
    Sound_call2(0x141, &wp->position);
}

void stcom23_func_08B8(STCOM23_WORK *wp)
{
}

void stcom23_func_08C0(STCOM23_WORK *wp)
{
    if (wp->timer_C != 0)
    {
        if (wp->timer_C == 1)
        {
            Sound_call2(0x142, &wp->position);
        }
        wp->timer_C--;
    }
}

void stcom23_func_0914(STCOM23_WORK *wp)
{
    stcom23_func_0AAC(wp);
}

void stcom23_func_0934(STCOM23_WORK *wp)
{
    stcom23_func_0AAC(wp);
}

// Registers the hit box.
void stcom23_func_0954(STCOM23_WORK *wp)
{
    func_800341BC(&wp->position, stcom23_D_0000[wp->type].size_1F, 0, 0x8000, wp->slot, &wp->hit_C4,
                  stcom23_D_0000[wp->type].hit_kind_21 | 0x40A0000, 0, 0x80);
    wp->hit_C4 = 0;
}

// Points the model along the velocity.
void stcom23_func_09FC(STCOM23_WORK *wp)
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
void stcom23_func_0AAC(STCOM23_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->be_flag           = 5;
        effect->id                = 0x80;
        effect->type              = 0x42;
        effect->sprite.position.x = wp->position.x;
        effect->sprite.position.y = wp->position.y;
        effect->sprite.position.z = wp->position.z;
    }
}

// Draws the smoke trail.
void stcom23_func_0B18(STCOM23_WORK *wp)
{
    STCOM23_PACKET *p;
    sint32 i;
    uint32 u;
    uint32 v;

    for (i = 0; i < 4; i++)
    {
        u          = stcom23_D_014C[i].u;
        v          = stcom23_D_014C[i].v;
        p          = Billboard_get();
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
