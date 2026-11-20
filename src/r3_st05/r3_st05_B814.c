#include "common.h"
#include "st05.h"

#ifdef __wasm32__
void func_80047228(void *wp, void *obj, sint32 n);
#endif

void func_8010B814(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_80130AF0[wp->routine_0](wp);
}

void func_8010B8B0(ST05_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0]      = 0x2000200;
        wp->scale.words[1]      = 0x200;
        wp->u_C.b.byte_C        = 0;
        wp->scale.v.pad         = 0x4210;
        wp->value_78            = 0;
        wp->position.y          = wp->position.y + func_80048E6C(wp);
        wp->position_fixed.v.y  = wp->position.y << 16;
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        func_800322A8(wp, 0xC, 0);
        wp->routine_1++;
    }
    else
    {
        if (wp->value_A7 == -1)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
        }
        func_80032488(wp);
    }
}

void func_8010B9E4(STAGE_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0xD, 0);
            wp->routine_1++;
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            func_80032488(wp);
            break;
        case 2:
            func_800322A8(wp, 0x2A, 0);
            wp->routine_1++;
            break;
        case 3:
            if (++wp->u_C.b.byte_C == 0x20)
            {
                wp->u_C.b.byte_C = 0;
                wp->routine_1    = 0;
                wp->routine_0++;
            }
            func_80032488(wp);
            break;
    }
}

void func_8010BAD0(STAGE_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x2A, 7);
            if (++wp->u_C.b.byte_C == 3)
            {
                STAGE_SCENE_BYTE(7) = 3;
            }
            if (wp->u_C.b.byte_C == 0xF)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            func_800322A8(wp, 0xE, 0);
            wp->routine_1++;
            break;
        case 2:
            if (wp->value_A7 == -1)
            {
                func_80031824(wp);
            }
            func_80032488(wp);
            break;
    }
}

void func_8010BBC0(STAGE_OBJ *wp)
{
    D_80130AFC[wp->routine_0](wp);
}

void func_8010BBFC(ST05_ACTOR *wp)
{
    STCOM_FIXED_VECTOR fixed;

    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]           = 0x02000200;
    wp->scale.words[1]           = 0x200;
    wp->scale.v.pad              = 0x4210;
    wp->ctl2.flags_0             = 0;
    *(sint32 *)&wp->ctl2.timer_4 = 0;
    fixed                        = wp->position_fixed;
    wp->ctl2.target_C            = wp->position;
    func_8002FFC4(&wp->ctl2.target_C, &fixed, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->data_78               = D_80130B18;
    wp->data_10               = NULL;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8010BD0C(wp);
}

void func_8010BD0C(ST05_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl2.value_2        = rand();
    D_80130B08[wp->routine_1](wp);
    if (wp->ctl2.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl2.flags_0 &= ~1;
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
}

void func_8010BE44(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010BE64(ST05_ACTOR *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->frame_110    = 9;
            wp->anim_AC      = 0;
            wp->ctl2.timer_4 = 0xA;
            break;
        case 1:
            if (--wp->ctl2.timer_4 < 0)
            {
                wp->frame_110    = 0xA;
                wp->ctl2.timer_4 = 5;
                wp->routine_2++;
            }
            break;
        case 2:
            if (--wp->ctl2.timer_4 < 0)
            {
                wp->frame_110    = 9;
                wp->ctl2.timer_4 = (wp->ctl2.value_2 & 0x3F) + 0x10;
                wp->routine_2--;
            }
            break;
    }
}

void func_8010BF3C(ST05_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC             = 0x13;
            wp->part_100[4].value_0 = 0xA;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC             = 0;
                wp->part_100[4].value_0 = 9;
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}

void func_8010BFA4(ST05_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0x21;
        Sound_call2(0xDA, &wp->position);
        wp->part_100[4].value_0 = 7;
    }
}

void func_8010BFF8(ST05_ACTOR *wp)
{
    sint32 dx;
    sint32 dz;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 2;
            wp->velocity.v.x = 0x80;
            wp->turn_64      = D_80130B24[wp->variant_3].pad;
            wp->frame_110    = 9;
            wp->ctl2.timer_4 = 0xA;
            break;
        case 1:
            if (--wp->ctl2.timer_4 < 0)
            {
                if (wp->frame_110 == 9)
                {
                    wp->frame_110    = 0xA;
                    wp->ctl2.timer_4 = 5;
                }
                else
                {
                    wp->frame_110    = 9;
                    wp->ctl2.timer_4 = (wp->ctl2.value_2 & 0x1F) + 0x10;
                }
            }
            if (wp->value_A6 != 0)
            {
                Sound_call2(0xD7, &wp->position);
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &D_80130B24[wp->variant_3], wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
            dx = wp->position.x - D_80130B24[wp->variant_3].x;
            dz = wp->position.z - D_80130B24[wp->variant_3].z;
            if (dx * dx + dz * dz < 0x800)
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->routine_2++;
                Sce_flag_on(wp->variant_3 + 0x61A);
            }
            break;
        case 2:
            break;
    }
}

void func_8010C1A8(ST05_OBJ *wp)
{
    D_80130B3C[wp->routine_0](wp);
    wp->value_35C = 0;
}

void func_8010C1F4(ST05_GUARD *wp)
{
    sint32 life;

    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]           = 0x2000200;
    wp->scale.words[1]           = 0x200;
    wp->scale.v.pad              = 0x4210;
    wp->rotation.x               = 0;
    wp->rotation.z               = 0;
    *(sint32 *)&wp->turn_64      = 0;
    wp->velocity.words[0]        = 0;
    wp->velocity.words[1]        = 0;
    wp->ctl.flags_0              = 0xE;
    *(sint32 *)&wp->ctl.timer_4  = 0;
    *(sint32 *)&wp->ctl.value_8  = 0;
    wp->ctl.hit_14               = 0;
    *(sint32 *)&wp->ctl.value_18 = 0;
    wp->ctl.sparks_34            = 0;
    func_80036478(wp->ctl.track_24, 0, -0x60);
    life         = D_80098844[wp->kind_2]->life_18;
    wp->data_78  = D_80130B60;
    wp->value_6E = life;
    wp->value_B0 = life;
    wp->value_B2 = life;
    wp->data_10  = NULL;
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
            break;
        case 2:
            wp->routine_0             = 1;
            wp->routine_1             = 3;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 3:
            wp->routine_0             = 1;
            wp->routine_1             = 5;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0x21, 0);
            break;
    }
    func_8010C37C(wp);
}

void func_8010C37C(ST05_GUARD *wp)
{
    ST05_GUARD_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    ctl                     = &wp->ctl;
    if (!(wp->ctl.flags_0 & 0x20) && func_8003648C(wp->ctl.track_24, wp))
    {
        wp->ctl.flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 4)
    {
        func_8010D1A8(wp);
    }
    D_80130B48[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
            case 1:
            case 2:
            case 4:
            case 5:
                wp->routine_1 = 4;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
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
        ctl->target_C = wp->position;
        ctl->target_C.y -= 0x28;
        if (ctl->flags_0 & 0x20)
        {
            func_800341BC(&ctl->target_C, 0x28, 0, 0x8000, wp->value_1, &ctl->hit_14, 0x4000000, 0x800000, 0x80);
        }
        else
        {
            func_800341BC(&ctl->target_C, 0x28, 0, 0x8000, wp->value_1, &ctl->hit_14, 0x4000000, 0x800000, 0);
        }
    }
}

void func_8010C644(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010C664(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;

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

void func_8010C6D0(ST05_GUARD *wp)
{
    ST05_GUARD_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 0x21;
            wp->velocity.v.x = 0xD;
            wp->velocity.v.y = -0x18;
            wp->frame_110    = 7;
            wp->ctl.timer_4  = 4;
            wp->ctl.value_8  = 0;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    func_8004B414(wp);
                }
                break;
            }
            ctl->timer_4 = 7;
            wp->anim_AC  = 0x22;
            wp->routine_2++;
            // fall through
        case 2:
            t                = (uint16)ctl->timer_4 - 1;
            ctl->timer_4     = t;
            wp->velocity.v.y = (4 - t) * 8;
            Obj_pos_set(wp, wp->velocity.v.x * 16, wp->velocity.v.y * 16, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
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
            if (--wp->ctl.timer_4 < 0)
            {
                wp->frame_110 = 6;
                wp->ctl.flags_0 |= 9;
            }
            break;
    }
}

void func_8010C8A0(ST05_GUARD *wp)
{
    ST05_GUARD_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC      = 0x25;
            wp->velocity.v.x = -0xB;
            wp->velocity.v.y = -0x18;
            wp->frame_110    = 7;
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
                    func_8004B414(wp);
                }
                break;
            }
            ctl->timer_4 = 0xB;
            wp->anim_AC  = 0x26;
            wp->routine_2++;
            // fall through
        case 2:
            t                = (uint16)ctl->timer_4 - 1;
            ctl->timer_4     = t;
            wp->velocity.v.y = (8 - t) * 8;
            Obj_pos_set(wp, wp->velocity.v.x * 16, wp->velocity.v.y * 16, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
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
                ctl->flags_0 |= 9;
                wp->frame_110 = 6;
            }
            break;
    }
}

void func_8010CA98(ST05_GUARD *wp)
{
    ST05_GUARD_CTL *ctl;
    STAGE_EFFECT *fx;
    sint32 i;
    sint32 rot;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 4:
            if (!(ctl->hit_14 & 0x20000000))
            {
                if (ctl->timer_4 == D_80130B6C[wp->routine_3] && ctl->sparks_34 < 3)
                {
                    for (i = 0; i < 4; i++)
                    {
                        fx = func_80031618();
                        if (fx == NULL)
                        {
                            break;
                        }
                        fx->flags_0   = 3;
                        fx->kind_2    = 0x83;
                        fx->variant_3 = 0;
                        fx->x_1C      = wp->joint_180[D_80130B70[wp->routine_3][i]].x;
                        fx->y_1E      = wp->joint_180[D_80130B70[wp->routine_3][i]].y - i * 12;
                        fx->z_20      = wp->joint_180[D_80130B70[wp->routine_3][i]].z;
                    }
                    wp->routine_3 = (wp->routine_3 + 1) & 3;
                }
                ctl->timer_4 = (ctl->timer_4 + 1) & 0x3F;
                break;
            }
            rot = func_80031F84(&wp->position, &ctl->from_1C, wp->rotation.y, 0);
            if (rot & 0xFFFF0000)
            {
                wp->rotation.y = (rot + 0x800) & 0xFFF;
            }
            else
            {
                wp->rotation.y = rot;
            }
            *(uint16 *)&wp->routine_2 = 0;
            // fall through
        case 0:
            wp->anim_AC      = 4;
            wp->velocity.v.x = -0x100;
            wp->velocity.v.y = 0x300;
            wp->routine_3    = 0;
            wp->frame_110    = 7;
            wp->routine_2++;
            ctl->value_8     = 0;
            ctl->timer_4     = 0;
            ctl->flags_0     = (ctl->flags_0 | 0x20) & ~0x4C;
            wp->velocity.v.x = 0x100;
            wp->velocity.v.y = -0x300;
            wp->accel_4C.y   = 0x80;
            Sound_call2(0xA2, &wp->position);
            // fall through
        case 1:
        case 2:
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
            wp->velocity.v.y += wp->accel_4C.y;
            hit = func_8004B414(wp);
            if (hit != 0)
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
                        if ((ctl->flags_0 & 0x80) && ctl->sparks_34 < 3)
                        {
                            ctl->sparks_34++;
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
    if (wp->value_80 > 0x800000 && !(wp->flags_6 & 0x80))
    {
        func_80031824(wp);
    }
}

void func_8010CE38(ST05_GUARD *wp)
{
    STCOM_PL_WORK *pl;
    ST05_ACTOR_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.x = 0xC0;
            wp->spin_66      = 0x18;
            wp->anim_AC      = 9;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&pl->position, &wp->position, wp->rotation.y, 0x18)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if ((hit & 0xF00) || wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
                wp->rotation.y     = (wp->rotation.y + 0x800) & 0xFFF;
            }
            if (!(ctl->value_2 & 0x1FF))
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
    if (wp->value_A4 == 0 || wp->value_A4 == 8)
    {
        Sound_call2(0xD7, &wp->position);
    }
}

void func_8010CFC4(ST05_GUARD *wp)
{
    ST05_GUARD_CTL *ctl;
    sint32 hit;
    sint32 t;
    sint32 wait; // retail loads 0xC before the switch

    ctl  = &wp->ctl;
    wait = 0xC;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 0x21;
            wp->velocity.v.x = 0x12;
            wp->velocity.v.y = -0x40;
            wp->frame_110    = 7;
            wp->ctl.timer_4  = 4;
            wp->ctl.value_8  = 0;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    func_8004B414(wp);
                }
                break;
            }
            ctl->timer_4 = wait;
            wp->anim_AC  = 0x22;
            wp->routine_2++;
            // fall through
        case 2:
            t                = (uint16)ctl->timer_4 - 1;
            ctl->timer_4     = t;
            wp->velocity.v.y = (4 - t) * 8;
            Obj_pos_set(wp, wp->velocity.v.x * 16, wp->velocity.v.y * 16, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
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
                    Sound_call(0xD8, 0, 0);
                }
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->frame_110 = 6;
                wp->ctl.flags_0 |= 9;
            }
            break;
    }
}

sint32 func_8010D1A8(ST05_GUARD *wp)
{
    ST05_GUARD_CTL *ctl;
    sint32 dmg;
    sint16 i;
    STCOM_EFFECT *fx;
    sint32 r;

    dmg = wp->ctl.hit_14 & 0xFFFFFF;
    ctl = &wp->ctl;
    if (dmg != 0)
    {
        if (wp->ctl.hit_14 & 0x38000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= dmg;
            if (wp->value_6E <= 0)
            {
                wp->value_6E = wp->value_B2 = -1;
                wp->ctl.flags_0 &= ~0xC;
                dmg = D_80098844[wp->kind_2]->limit_19;
                for (i = 0; i < 4; i++)
                {
                    fx = func_80031618();
                    if (fx == NULL)
                    {
                        break;
                    }
                    fx->flags_0         = 1;
                    fx->kind_2          = 0x83;
                    fx->variant_3       = 3;
                    fx->sprite.pos_8[0] = wp->joint_180[D_80130B88[i]].x;
                    fx->sprite.pos_8[1] = wp->joint_180[D_80130B88[i]].y - i * 12;
                    fx->sprite.pos_8[2] = wp->joint_180[D_80130B88[i]].z;
                }
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
            }
            if (ctl->flags_0 & 8)
            {
                ctl->timer_A += dmg;
                if ((ctl->hit_14 & 0x20000000) || ctl->timer_A >= D_80098844[wp->kind_2]->limit_19)
                {
                    Sound_call2(0xA2, &wp->position);
                    r              = func_80031F84(&wp->position, &ctl->from_1C, wp->rotation.y, 0);
                    wp->rotation.y = r + 0x800;
                    if (r & 0xFFFF0000)
                    {
                        wp->routine_1 = 1;
                    }
                    else
                    {
                        wp->routine_1 = 2;
                    }
                    ctl->timer_A = 0;
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
