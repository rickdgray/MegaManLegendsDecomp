#include "common.h"
#include "stage_common/stcom09.h"

// Shared stage code, linked into 7 stages: r3_st00, r3_st09, r3_st0e, r3_st13, r3_st14, r3_st1a
// and r3_st1d. Each stage compiles this file against its own copy of the assembly (TARGET_ASM,
// set by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom09"

void stcom09_func_0000(STCOM09_WORK *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    stcom09_D_0000[wp->index_3](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0xC, 0x200, 0);
    }
}

void stcom09_func_00CC(STCOM09_WORK *wp)
{
    STCOM_SVECTOR ofs;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->turn_64    = 0x40;
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->data_78          = stcom09_D_0028;
    wp->data_10          = stcom09_D_001C;
    wp->velocity.x       = 10;
    wp->velocity.y       = 0;
    wp->velocity.z       = 0;
    wp->value_74         = 0;
    wp->hit.flags_0      = 0;
    wp->hit.pos_8        = wp->position;
    wp->hit.ofs_10       = -0x30;
    wp->hit.ofs_12       = -0x48;
    wp->hit.size_16      = 0x48;
    wp->hit.ofs_14       = 0;
    wp->hit.value_4      = 0x8880000;
    wp->hit.timer_2      = 0;
    func_80036478(wp->track_328, 0, -0x60);
    stcom09_func_0C48(&ofs, wp->rotation.y, wp->hit.ofs_10, wp->hit.ofs_12, wp->hit.ofs_14);
    wp->hit.pos_8 = ofs;
    wp->hit.pos_8.x += wp->position.x;
    wp->hit.pos_8.y += wp->position.y;
    wp->hit.pos_8.z += wp->position.z;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8;
    wp->routine_1                                    = 0;
}

void stcom09_func_0268(STCOM09_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM09_HIT *hit;
    sint32 id;

    hit = &wp->hit;
    pl  = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            stcom09_func_00CC(wp);
            wp->routine_0++;
            // fall through
        case 1:
            if (stcom09_func_0AFC(wp))
            {
                func_800322A8(wp, 0, 0);
            }
            else
            {
                func_800322A8(wp, 2, 0x10);
                hit->flags_0 |= 2;
            }
            wp->routine_0++;
            // fall through
        case 2:
            if (pl->target_184 == wp)
            {
                if (stcom09_func_0B48(wp))
                {
                    wp->routine_0++;
                }
                else
                {
                    pl->target_184 = NULL;
                }
            }
            break;
        case 3:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_448 = 0x30;
                pl->value_C   = 0;
                Obj_work_flag_change(0x3FE, 1);
                wp->flags_0 |= 1;
                wp->flags_6 |= 1;
                wp->routine_0++;
            }
            break;
        case 4:
            wp->routine_0++;
            break;
        case 5:
            if (!(hit->flags_0 & 2))
            {
                func_800322A8(wp, 1, 0);
                Sound_call2(0x103, &wp->position);
            }
            else
            {
                wp->routine_0++;
            }
            wp->routine_0++;
            break;
        case 7:
            if (stcom09_func_0AFC(wp))
            {
                if (wp->value_D == 0)
                {
                    func_80063BC8(&wp->position, 2, 0, wp->param_E);
                }
                else if (wp->value_D == 1)
                {
                    func_80063BC8(&wp->position, 2, 0, 0);
                }
                else if (wp->value_D & 0x80)
                {
                    id = (((wp->value_D & 0x7F) << 8) | (uint8)wp->param_E) * 10;
                    func_8005C150(2, 1, id / 10, 0);
                    Sce_flag_on(wp->flag_C + 0x400);
                }
                else if (wp->param_E != -1)
                {
                    if (wp->flag_C == 0x40 || wp->flag_C == 0x42)
                    {
                        func_80063BC8(&wp->position, 2, 0, 0xC);
                    }
                    else
                    {
                        func_8005C150(2, 0, (uint8)wp->param_E, 0);
                    }
                    Sce_flag_on(wp->flag_C + 0x400);
                    pl->value_448 = 0x35;
                }
                else
                {
                    func_8005C150(2, 2, 0, 0);
                }
            }
            else
            {
                func_8005C150(2, 2, 0, 0);
            }
            wp->routine_0++;
            break;
        case 8:
            if (Moji_flag & 0x8000000)
            {
                break;
            }
            if (!(hit->flags_0 & 2))
            {
                func_800322A8(wp, 2, 0);
                Sound_call2(0x104, &wp->position);
            }
            else
            {
                wp->routine_0++;
            }
            wp->routine_0++;
            break;
        case 6:
        case 9:
            if (wp->flags_A7 < 0)
            {
                wp->routine_0++;
            }
            func_80032488(wp);
            break;
        case 10:
            Obj_work_flag_change(0x3FE, 2);
            func_80042314(pl);
            pl->target_184 = NULL;
            pl->flags_0 |= 2;
            hit->flags_0 &= ~2;
            wp->routine_0 = 1;
            break;
    }
    func_80051B68(wp, 1, 0, 0);
    func_800341BC(&wp->position, 0x28, 0, 0x8000, wp->value_1, &hit->hit_18, 0x4000000, 0, 0x80);
    hit->hit_18 = 0;
}

void stcom09_func_06A0(STCOM09_WORK *wp)
{
    STCOM09_HIT *hit;

    wp->anim_prev_AD = wp->anim_AC;
    hit              = &wp->hit;
    wp->scale.v.pad  = 0x4210;
    if (wp->routine_0 != 0)
    {
        if (func_8003648C(wp->track_328, wp))
        {
            hit->flags_0 |= 1;
        }
        else
        {
            hit->flags_0 &= ~1;
        }
    }
    stcom09_D_0008[wp->routine_0](wp);
    if (wp->routine_0 == 0)
    {
        func_80051B68(wp, 1, -1, 0x1000000);
    }
    else
    {
        func_800341BC(&hit->pos_8, hit->size_16, 0, 0x8000, wp->value_1, &hit->hit_18, hit->value_4, 0, 0);
    }
    if (wp->anim_prev_AD == wp->anim_AC)
    {
        func_80032488(wp);
    }
    hit->hit_18 = 0;
}

void stcom09_func_07B8(STCOM09_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM09_HIT *hit;

    pl  = &Player_work;
    hit = &wp->hit;
    switch (wp->routine_1)
    {
        case 0:
            stcom09_func_00CC(wp);
            func_800322A8(wp, 0, 0);
            wp->routine_1++;
            break;
        case 1:
            if (pl->target_184 == wp)
            {
                if (stcom09_func_0B48(wp))
                {
                    wp->routine_1++;
                }
                else
                {
                    pl->target_184 = NULL;
                }
            }
            break;
        case 2:
            wp->routine_1++;
            break;
        case 3:
            MojiTaskExec(4, D_8008CE74, -1);
            func_800322A8(wp, 1, 0);
            Sound_call2(0x103, &wp->position);
            wp->routine_1++;
            // fall through
        case 4:
            pl->target_184 = NULL;
            wp->timer_A    = 1;
            wp->routine_1++;
            break;
        case 5:
            if (--wp->timer_A == 0)
            {
                wp->routine_0 = 1;
                wp->routine_1 = 0;
                wp->timer_A   = 45;
                hit->value_4  = 0x48C0002;
            }
            break;
    }
}

void stcom09_func_0918(STCOM09_WORK *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->routine_1++;
            // fall through
        case 1:
            if (--wp->timer_A == 0)
            {
                wp->routine_0 = 3;
                wp->routine_1 = 0;
            }
            break;
    }
    stcom09_func_0BE0(wp);
}

void stcom09_func_0988(STCOM09_WORK *wp)
{
    STCOM09_HIT *hit;

    hit = &wp->hit;
    switch (wp->routine_1)
    {
        case 0:
            if (hit->flags_0 & 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
        case 3:
        case 5:
            if (stcom09_func_0D28(wp))
            {
                wp->timer_A = 4;
                wp->routine_1++;
            }
            break;
        case 2:
        case 4:
        case 6:
            if (--wp->timer_A == 0)
            {
                wp->routine_1++;
            }
            break;
        case 7:
            wp->routine_0 = 1;
            wp->routine_1 = 0;
            wp->timer_A   = 30;
            break;
    }
    stcom09_func_0BE0(wp);
}

void stcom09_func_0A64(STCOM09_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0         = 5;
        effect->kind_2          = 0x80;
        effect->variant_3       = 0;
        effect->sprite.position = wp->hit.pos_8;
#ifdef __wasm32__
        func_80047148(wp, &wp->position);
#else
        func_80047148(wp, &wp->position, effect);
#endif
        func_80031824(wp);
    }
}

void stcom09_func_0ADC(STCOM09_WORK *wp)
{
    func_80031824(wp);
}

uint8 stcom09_func_0AFC(STCOM09_WORK *wp)
{
    if (Sce_flag_test(wp->flag_C + 0x400) == 0)
    {
        if (wp->param_E != -1)
        {
            return 1;
        }
    }
    else
    {
        // Keep this early failure arm: merging the returns changes the branch code.
        return 0;
    }
    return 0;
}

uint8 stcom09_func_0B48(STCOM09_WORK *wp)
{
    STCOM_FIXED_VECTOR out;
    STCOM_SVECTOR size;
    STCOM_PL_WORK *pl;
    sint32 mask;

    wp->value_C4         = wp->value_180;
    pl                   = &Player_work;
    Player_work.value_C4 = pl->position;
    size.x               = 2;
    size.y               = 9;
    size.z               = 4;
    mask                 = 0x10;
    return (func_80030418(wp, &Player_work, &size, &out) & mask) == 0;
}

void stcom09_func_0BE0(STCOM09_WORK *wp)
{
    uint32 hit;
    uint32 damage;

    hit    = wp->hit.hit_18;
    damage = hit & 0xFFFFFF;
    if (damage != 0 && (hit & 0x38000000))
    {
        wp->life_prev_B2 = wp->life_6E;
        wp->life_6E -= damage;
        wp->hit.timer_2 = 10;
        if (wp->life_6E <= 0)
        {
            wp->routine_0 = 4;
            wp->routine_1 = 0;
        }
        wp->scale.v.pad = 0x7FFF;
    }
}

STCOM_SVECTOR *stcom09_func_0C48(STCOM_SVECTOR *out, sint32 angle, sint32 x, sint32 y, sint32 z)
{
    STCOM_SVECTOR v;
    STCOM_SVECTOR r;
    STCOM09_MATRIX m;
    sint16 vx;
    sint16 vy;
    sint16 vz;

    vx = x;
    vy = y;
    vz = z;
    if ((sint16)x < 0)
    {
        vx = -x;
        vz = -z;
        angle += 0x800;
    }
    m.words[0] = 0x1000;
    m.words[1] = 0;
    m.words[2] = 0x1000;
    m.words[3] = 0;
    m.words[4] = 0x1000;
    m.words[5] = 0;
    m.words[6] = 0;
    m.words[7] = 0;
    RotMatrixY(angle, &m.m);
    v.x = vz;
    v.y = vy;
    v.z = -vx;
    ApplyMatrixSV(&m.m, &v, &r);
    *out = r;
    return out;
}

uint8 stcom09_func_0D28(STCOM09_WORK *wp)
{
    STCOM09_SHOT *shot;

    shot = Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0   = 3;
        shot->kind_2    = 6;
        shot->variant_3 = 0;
        Obj_pos_set(wp, 0x6E, 0, 0);
        wp->position.y -= 60;
        shot->position         = wp->position;
        shot->position_fixed.x = shot->position.x << 16;
        shot->position_fixed.y = shot->position.y << 16;
        shot->position_fixed.z = shot->position.z << 16;
        shot->angle_64         = wp->rotation.y;
        shot->speed_9C         = 0x20;
        shot->rise_A0          = 0x10;
        wp->position           = wp->position_prev;
        wp->position_fixed     = wp->position_fixed_prev;
        Sound_call2(0xB2, &wp->position);
    }
    return shot != NULL;
}
