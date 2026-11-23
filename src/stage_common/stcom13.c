#include "common.h"
#include "stage_common/stcom13.h"

// Shared stage code, linked into 6 stages: r3_st05, r3_st06, r3_st0a, r3_st0c, r3_st10 and
// r3_st11. Each stage compiles this file against its own copy of the assembly (TARGET_ASM, set
// by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom13"

void stcom13_func_0000(STCOM13_WORK *wp)
{
    stcom13_D_0000[wp->routine_0](wp);
    wp->ctl.hit_14 = 0;
}

void stcom13_func_004C(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;
    sint16 life;

    ctl = &wp->ctl;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x2000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    wp->rotation.x           = 0;
    wp->rotation.z           = 0;
    *(uint32 *)&wp->turn_64  = 0;
    wp->velocity.words[0]    = 0;
    wp->velocity.words[1]    = 0;
    ctl->flags_0             = 0x10E;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    ctl->hit_14              = 0;
    ctl->value_18            = 0;
    ctl->count_34            = 0;
    func_80036478(ctl->track_24, 0, -0x60);
    ctl->timer_36    = 300;
    life             = D_80098844[wp->kind_2]->life_18;
    wp->data_78      = stcom13_D_0020;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = life;
    wp->data_10                                      = NULL;
    switch (wp->variant_3)
    {
        case 0:
            wp->routine_0             = 1;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 1:
            wp->routine_0             = 1;
            wp->routine_1             = 2;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            ctl->flags_0 &= ~0x100;
            break;
        case 2:
            wp->routine_0             = 1;
            wp->routine_1             = 3;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
    }
    stcom13_func_01D8(wp);
}

// The identical arms (merged by jump2 after allocation) keep the hit box call's arguments
// after the pos_C.y store, as retail; the matched siblings hoist them above it.
void stcom13_func_01D8(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    ctl                     = &wp->ctl;
    if ((ctl->flags_0 & 0x104) == 0x104)
    {
        stcom13_func_0DA8(wp);
    }
    stcom13_D_000C[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
            case 1:
            case 2:
            case 4:
                wp->routine_1 = 4;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_36 == 0 && wp->value_80 > 0x800000 && !(wp->flags_6 & 0x80))
    {
        func_80031824(wp);
    }
    if (ctl->damage_A != 0)
    {
        ctl->damage_A--;
    }
    if (ctl->timer_36 != 0)
    {
        ctl->timer_36--;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 2))
    {
        ctl->pos_C = wp->position;
        if (wp != NULL)
        {
            ctl->pos_C.y -= 40;
        }
        else
        {
            ctl->pos_C.y -= 40;
        }
        func_800341BC(&ctl->pos_C, 0x28, 0, 0x8000, wp->value_1, &ctl->hit_14, 0x4000000, 0x800000, 0x80);
    }
}

void stcom13_func_045C(STCOM13_WORK *wp)
{
    func_80031824(wp);
}

void stcom13_func_047C(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            // fall through
        case 1:
            if ((ctl->flags_0 & 0x10) || (ctl->hit_14 & 0xFFFFFF))
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void stcom13_func_04E8(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;
    uint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 0x21;
            wp->velocity.v.x = 13;
            wp->velocity.v.y = -24;
            wp->value_110    = 7;
            ctl->timer_4     = 4;
            ctl->value_8     = 0;
            ctl->flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    Obj_map_push_out(wp);
                }
                break;
            }
            ctl->timer_4 = 7;
            wp->anim_AC  = 0x22;
            wp->routine_2++;
            // fall through
        case 2:
            wp->velocity.v.y = (4 - --ctl->timer_4) << 3;
            Obj_pos_set(wp, wp->velocity.v.x * 16, wp->velocity.v.y * 16, 0);
            hit = Obj_map_push_out(wp);
            if (hit)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if ((hit & 0x1000) && ctl->timer_4 <= 0)
                {
                    ctl->timer_4 = 0x12;
                    wp->anim_AC  = 0x23;
                    wp->routine_2++;
                }
            }
            break;
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->value_110 = 6;
                ctl->flags_0 |= 0x109;
            }
            break;
    }
}

void stcom13_func_06B8(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;
    uint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC      = 0x25;
            wp->velocity.v.x = -11;
            wp->velocity.v.y = -24;
            wp->value_110    = 7;
            wp->routine_2++;
            ctl->timer_4 = 4;
            ctl->value_8 = 0;
            ctl->flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    Obj_map_push_out(wp);
                }
                break;
            }
            ctl->timer_4 = 11;
            wp->anim_AC  = 0x26;
            wp->routine_2++;
            // fall through
        case 2:
            wp->velocity.v.y = (8 - --ctl->timer_4) << 3;
            Obj_pos_set(wp, wp->velocity.v.x * 16, wp->velocity.v.y * 16, 0);
            hit = Obj_map_push_out(wp);
            if (hit)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if ((hit & 0x1000) && ctl->timer_4 <= 0)
                {
                    ctl->timer_4 = 0x26;
                    wp->anim_AC  = 0x27;
                    wp->routine_2++;
                }
            }
            break;
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4 = 0x11;
            wp->anim_AC  = 0x28;
            wp->routine_2++;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 0x109;
                wp->value_110 = 6;
            }
            break;
    }
}

void stcom13_func_08B0(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;
    STCOM_EFFECT *effect;
    STCOM_SVECTOR *joint;
    uint32 hit;
    sint32 angle;
    sint32 i;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 4:
            if (!(ctl->hit_14 & 0x20000000))
            {
                if (ctl->timer_4 == stcom13_D_002C[wp->routine_3] && ctl->count_34 < 3)
                {
                    for (i = 0; i < 4; i++)
                    {
                        effect = func_80031618();
                        if (effect == NULL)
                        {
                            break;
                        }
                        effect->flags_0         = 3;
                        effect->kind_2          = 0x83;
                        effect->variant_3       = 0;
                        effect->sprite.pos_8[0] = wp->joints_180[stcom13_D_0030[wp->routine_3][i]].x;
                        effect->sprite.pos_8[1] = wp->joints_180[stcom13_D_0030[wp->routine_3][i]].y - i * 12;
                        effect->sprite.pos_8[2] = wp->joints_180[stcom13_D_0030[wp->routine_3][i]].z;
                    }
                    wp->routine_3 = (wp->routine_3 + 1) & 3;
                }
                ctl->timer_4 = (ctl->timer_4 + 1) & 0x3F;
                break;
            }
            angle = func_80031F84(&wp->position, &ctl->from_1C, wp->rotation.y, 0);
            if (angle & 0xFFFF0000)
            {
                wp->rotation.y = (angle + 0x800) & 0xFFF;
            }
            else
            {
                wp->rotation.y = angle;
            }
            *(uint16 *)&wp->routine_2 = 0;
            // fall through
        case 0:
            wp->anim_AC      = 4;
            wp->velocity.v.x = -0x100;
            wp->velocity.v.y = 0x300;
            wp->routine_3    = 0;
            wp->value_110    = 7;
            wp->routine_2++;
            ctl->value_8     = 0;
            ctl->timer_4     = 0;
            ctl->flags_0     = (ctl->flags_0 | 0x20) & ~0x4C;
            wp->velocity.v.x = 0x100;
            wp->velocity.v.y = -0x300;
            wp->gravity_4E   = 0x80;
            Sound_call2(0xA2, &wp->position);
            // fall through
        case 1:
        case 2:
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->gravity_4E;
            hit = Obj_map_push_out(wp);
            if (hit)
            {
                if (hit & 0xF00)
                {
                    wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
                }
                if (hit & 0x1000)
                {
                    if (!(ctl->flags_0 & 0x40))
                    {
                        ctl->flags_0 |= 0x40;
                        if ((ctl->flags_0 & 0x80) && ctl->count_34 < 3)
                        {
                            ctl->count_34++;
                            func_80047228(wp, &wp->position, 1);
                        }
                        ctl->flags_0 |= 0x80;
                    }
                    Sound_call2(0xDA, &wp->position);
                    wp->velocity.v.x = 0x60;
                    wp->velocity.v.y = -0x200;
                    wp->routine_2++;
                }
            }
            break;
        case 3:
            if (wp->value_A4 == 0)
            {
                wp->routine_3 = 0;
                wp->anim_AC   = 5;
                wp->routine_2++;
            }
            break;
    }
    wp->scale.v.pad = 0x190C;
}

void stcom13_func_0C24(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;
    STCOM_PL_WORK *pl;
    uint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.x = 0xC0;
            wp->turn_66      = 0x18;
            wp->anim_AC      = 9;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&pl->position, &wp->position, wp->rotation.y, 0x18)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if ((hit & 0xF00) || STCOM_ABS(wp->position.y - wp->position_prev.y) > 16)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
            }
            if (!(ctl->rand_2 & 0x1FF))
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

sint32 stcom13_func_0DA8(STCOM13_WORK *wp)
{
    STCOM13_CTL *ctl;
    STCOM_EFFECT *effect;
    sint32 damage;
    sint32 angle;
    sint16 i;

    ctl    = &wp->ctl;
    damage = wp->ctl.hit_14 & 0xFFFFFF;
    if (damage)
    {
        if (wp->ctl.hit_14 & 0x38000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                wp->life_6E = wp->life_prev_B2 = -1;
                wp->ctl.flags_0 &= ~0xC;
                damage = D_80098844[wp->kind_2]->stun_19;
                for (i = 0; i < 4; i++)
                {
                    effect = func_80031618();
                    if (effect == NULL)
                    {
                        break;
                    }
                    effect->flags_0         = 1;
                    effect->kind_2          = 0x83;
                    effect->variant_3       = 3;
                    effect->sprite.pos_8[0] = wp->joints_180[stcom13_D_0040[i]].x;
                    effect->sprite.pos_8[1] = wp->joints_180[stcom13_D_0040[i]].y - i * 12;
                    effect->sprite.pos_8[2] = wp->joints_180[stcom13_D_0040[i]].z;
                }
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
            }
            if (ctl->flags_0 & 8)
            {
                ctl->damage_A += damage;
                if ((ctl->hit_14 & 0x20000000) || ctl->damage_A >= D_80098844[wp->kind_2]->stun_19)
                {
                    Sound_call2(0xA2, &wp->position);
                    angle          = func_80031F84(&wp->position, &ctl->from_1C, wp->rotation.y, 0);
                    wp->rotation.y = angle + 0x800;
                    if (angle & 0xFFFF0000)
                    {
                        wp->routine_1 = 1;
                    }
                    else
                    {
                        wp->routine_1 = 2;
                    }
                    ctl->damage_A = 0;
                }
                *(uint16 *)&wp->routine_2 = 0;
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}
