#include "common.h"
#include "stage_common/stcom20.h"

// Shared stage code, linked into 5 stages: r3_st03, r3_st05, r3_st0e, r3_st14 and r3_st1a. Each
// stage compiles this file against its own copy of the assembly (TARGET_ASM, set by
// tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom20"

sint32 stcom20_func_0000(STCOM20_WORK *wp)
{
    return func_8003648C(wp->ctl.track_0, wp) != 0;
}

sint32 stcom20_func_0024(STCOM20_WORK *wp)
{
    return func_8003648C(wp->ctl.track_0, wp) == 0;
}

void stcom20_func_0048(STCOM20_WORK *wp)
{
    STCOM20_CTL *ctl;
    sint16 y;

    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, NULL);
    wp->data_78            = stcom20_D_0000;
    wp->value_74           = 1;
    wp->param_C            = 0;
    wp->velocity.v.x       = 0;
    wp->rotation.y         = rand() & 0xFFF;
    ctl                    = &wp->ctl;
    wp->color_B4           = 0x808080;
    wp->ctl.scale_18.value = 0x2000000;
    Track_reset(ctl->track_0, 1, -0x60);
    wp->ctl.value_20  = 0;
    wp->ctl.hit_1C    = 0;
    wp->ctl.angle_10  = rand() & 0xFFF;
    y                 = Obj_ceiling_height_get(wp);
    wp->ctl.ground_12 = y;
    if (y - 0x82 < wp->position.y)
    {
        wp->position.y    = y - 0x82;
        wp->ctl.height_14 = 0x82;
    }
    else
    {
        wp->ctl.height_14 = wp->position.y - y;
    }
    ctl->limit_16 = -0x82;
    wp->routine_0++;
}

void stcom20_func_0148(STCOM20_WORK *wp)
{
    STCOM20_CTL *ctl;
    sint16 y;
    sint16 d;

    ctl = &wp->ctl;
    if (stcom20_func_0000(wp))
    {
        wp->routine_1    = 1;
        wp->velocity.v.y = 0;
        wp->angle_66     = wp->rotation.y;
    }
    wp->ctl.angle_10 += 0x22;
    wp->position_fixed.y = ((wp->ctl.ground_12 + wp->ctl.height_14) << 16) + rsin(wp->ctl.angle_10) * 400;
    wp->rotation.y       = (wp->rotation.y + 0x14) & 0xFFF;
    wp->velocity.v.x -= 5;
    if (wp->velocity.v.x < 0)
    {
        wp->velocity.v.x = 0;
    }
    func_8002FFC4(&wp->position, &wp->position_fixed, wp->angle_66, wp->velocity.v.x, 0, 0);
    if (Obj_map_push_out(wp) == 0)
    {
        y = Obj_ceiling_height_get(wp);
        d = y - ctl->ground_12;
        if (STCOM_ABS(d) > 10)
        {
            if (d >= 0)
            {
                ctl->ground_12 += 10;
            }
            else
            {
                ctl->ground_12 -= 10;
            }
        }
        else
        {
            ctl->ground_12 = y;
        }
        wp->position_fixed.y = ((ctl->ground_12 + ctl->height_14) << 16) + rsin(ctl->angle_10) * 400;
        func_80030150(&wp->position_fixed, &wp->position);
    }
}

void stcom20_func_02F8(STCOM20_WORK *wp)
{
    STCOM20_CTL *ctl;
    STCOM_PL_WORK *pl;
    STCOM_SVECTOR pos;         // set but never used
    STCOM_FIXED_VECTOR unused; // never used; reserves retail's frame
    sint32 step;
    sint32 hit;
    sint16 y;
    sint16 d;

    ctl = &wp->ctl;
    pl  = &Player_work;
    if (stcom20_func_0024(wp))
    {
        wp->routine_1 = 0;
    }
    wp->ctl.angle_10 += 0x22;
    wp->position_fixed.y = (wp->ctl.ground_12 + wp->ctl.height_14) << 16;
    step                 = 5;
    if (Player_work.position_fixed.y - wp->position_fixed.y < 0)
    {
        step = -5;
    }
    wp->velocity.v.y += step;
    if (STCOM_ABS(wp->velocity.v.y) > 0xA0)
    {
        if (wp->velocity.v.y > 0)
        {
            wp->velocity.v.y = 0xA0;
        }
        else
        {
            wp->velocity.v.y = -0xA0;
        }
    }
    ctl->height_14 += wp->velocity.v.y >> 4;
    if (ctl->height_14 > ctl->limit_16)
    {
        ctl->height_14   = ctl->limit_16;
        wp->velocity.v.y = 0;
    }
    wp->position_fixed.y = (ctl->ground_12 + ctl->height_14) << 16;
    wp->position_fixed.y += rsin(ctl->angle_10) * 400;
    wp->rotation.y = (wp->rotation.y + 0x14) & 0xFFF;
    pos.x          = wp->position_fixed.x >> 16;
    pos.y          = wp->position_fixed.y >> 16;
    pos.z          = wp->position_fixed.z >> 16;
    wp->angle_66   = (wp->angle_66 + Muku(&wp->position, &pl->position, wp->angle_66, 0x20)) & 0xFFF;
    wp->velocity.v.x += 5;
    if (wp->velocity.v.x > 0xA0)
    {
        wp->velocity.v.x = 0xA0;
    }
    func_8002FFC4(&wp->position, &wp->position_fixed, wp->angle_66, wp->velocity.v.x, 0, 0);
    hit = Obj_map_push_out(wp);
    if (hit == 0)
    {
        y = Obj_ceiling_height_get(wp);
        if (y != ctl->ground_12)
        {
            d = y - ctl->ground_12;
            if (STCOM_ABS(d) > 10)
            {
                if (d >= 0)
                {
                    ctl->ground_12 += 10;
                }
                else
                {
                    ctl->ground_12 -= 10;
                }
            }
            else
            {
                ctl->ground_12 = y;
            }
            wp->position_fixed.y = (ctl->ground_12 + ctl->height_14) << 16;
            wp->position_fixed.y += rsin(ctl->angle_10) * 400;
            func_80030150(&wp->position_fixed, &wp->position);
        }
    }
    else
    {
        func_8004AE88(&wp->angle_66, hit);
    }
}

void stcom20_func_05FC(STCOM20_WORK *wp)
{
    STCOM_EFFECT *effect;
    sint16 angle;

    if (wp->param_C == 1)
    {
        angle          = wp->rotation.y + 400;
        wp->rotation.y = angle;
        angle          = wp->rotation.x + 400;
        wp->rotation.x = angle;
        func_8002FFC4(&wp->position, &wp->position_fixed, wp->angle_66, 0x200, 0, 0);
    }
    wp->ctl.scale_18.value += 0x330000;
    if (wp->ctl.scale_18.value > 0x2FFFFFF)
    {
        effect = func_80031618();
        if (effect != NULL)
        {
            effect->be_flag         = MOVE | MODEL;
            effect->id              = 0x80;
            effect->type            = 0x42;
            effect->sprite.position = wp->position;
        }
        wp->routine_0 = 2;
        func_80047148(wp, &wp->position, effect);
    }
    Obj_map_push_out(wp);
}

void stcom20_func_06E8(STCOM20_WORK *wp)
{
    STCOM20_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.hit_1C != 0)
    {
        if (wp->ctl.hit_1C & 0x20000000)
        {
            wp->param_C   = 1;
            wp->routine_1 = 2;
            wp->angle_66  = Angle_xz(0, 0, wp->ctl.x_24, wp->ctl.z_28);
        }
        if (wp->ctl.hit_1C & 0x2000000)
        {
            wp->routine_1 = 2;
        }
        if ((wp->ctl.hit_1C & 0x8000000) && (wp->ctl.hit_1C & 0xFFFFFF))
        {
            wp->routine_1 = 2;
        }
    }
    stcom20_D_000C[wp->routine_1](wp);
    func_800341BC(&wp->position, 0x20, 0, 0x8000, wp->work_id, &ctl->hit_1C, 0x4080000, 0x800000, 0);
    ctl->hit_1C = 0;
}

void stcom20_func_07F8(STCOM20_WORK *wp)
{
    Close_SHL_WORK(wp);
}

void stcom20_func_0818(STCOM20_WORK *wp)
{
    STCOM20_MATRIX *m;
    STCOM20_MATRIX rot;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom20_D_0018[wp->routine_0](wp);
    wp->pos_AC          = wp->position;
    m                   = &wp->matrix;
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    wp->ctl.scale_2C.x = wp->ctl.scale_2C.y = wp->ctl.scale_2C.z = wp->ctl.scale_18.words.integer;
    ScaleMatrix(&m->m, &wp->ctl.scale_2C);
    rot.words[0] = 0x1000;
    rot.words[1] = 0;
    rot.words[2] = 0x1000;
    rot.words[3] = 0;
    rot.words[4] = 0x1000;
    rot.words[5] = 0;
    rot.words[6] = 0;
    rot.words[7] = 0;
    RotMatrix(&wp->rotation, &rot.m);
    MulMatrix(&m->m, &rot.m);
    if (wp->be_flag & TRANS)
    {
        Pos_Shadow_Trans(&wp->pos_AC, 0x30, 0x200, wp->rotation.y);
    }
}
