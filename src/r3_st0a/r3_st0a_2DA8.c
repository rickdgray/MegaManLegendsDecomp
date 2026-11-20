#include "common.h"
#include "st0a.h"

#ifdef __wasm32__
void func_80036478(void *track, uint8 arg1, uint32 arg2);
#endif

void func_80102DA8(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    D_80115938[wp->variant_3](wp, &Scene_work, (STCOM_SVECTOR *)&wp->reserved30C[0x3C]);
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80102E8C(STAGE_OBJ *wp, STAGE_OBJ *arg1)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 0x19;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            wp->routine_0++;
            break;
        case 1:
            wp->anim_prev_AD = 0xFF;
            if (arg1->routine_1 == 5)
            {
                wp->routine_0++;
            }
            break;
        case 0xFF:
            break;
    }
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_80102F58(STAGE_OBJ *wp, STAGE_OBJ *arg1)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_0;
    switch (temp_v1)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 9;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            wp->routine_0++;
            break;
        case 1:
            if (arg1->routine_1 == 5)
            {
                Obj_pos_set(wp, 0x80, 0, 0);
            }
            break;
    }
    Model_Shadow_Trans(wp, 0x28, 0x200, 0);
}

void func_80103028(STAGE_OBJ *wp, sint32 arg, STCOM_SVECTOR *hit)
{
    D_80115948[wp->routine_0](wp, arg, hit);
    if (hit->y != 0)
    {
        Model_Shadow_Trans(wp, 0x28, 0x200, 0);
    }
}

void func_80103098(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *hit)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 0x10;
            wp->value_78       = 0;
            wp->anim_prev_AD   = 0xFF;
            hit->y             = 0;
            wp->routine_1++;
            break;
        case 1:
            if (scene->reserved00[6] == 4)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_80103168(STAGE_OBJ *wp, STAGE_ROOM *arg1, sint16 *arg2)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_AC = 2;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 1:
            if (arg2[0] < 6)
            {
                wp->rotation.y += 0x20;
                arg2[0] = (uint16)arg2[0] + 1;
            }
            else
            {
                wp->routine_1++;
            }
            Obj_pos_set(wp, 0x80, 0, 0);
            break;
        case 2:
            wp->anim_AC = 7;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 3:
            if (arg2[0] < 8)
            {
                Obj_pos_set(wp, 0x30, 0x40, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 4:
            wp->anim_AC                  = 8;
            wp->position.y               = -0x34;
            wp->position_fixed.v.y = -0x340000;
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 5:
            wp->anim_AC = 2;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 6:
            if (arg2[0] < 0x14)
            {
                Obj_pos_set(wp, 0x80, 0, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 7:
            wp->anim_AC = 7;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 8:
            if (arg2[0] == 5)
            {
                arg2[1] = 1;
            }
            if (arg2[0] < 0xD)
            {
                Obj_pos_set(wp, 0x30, 0x40, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 9:
            wp->anim_AC            = 8;
            wp->position.y         = -1;
            wp->position_fixed.v.y = -0x10000;
            if (wp->value_A7 == -1)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_80103384(STAGE_OBJ *wp, STAGE_ROOM *arg1, sint16 *arg2)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_AC = 2;
            *arg2       = 0;
            wp->routine_1++;
            // fall through
        case 1:
            if (*arg2 < 0xC)
            {
                Obj_pos_set(wp, 0x80, 0, 0);
                *arg2 = (uint16)*arg2 + 1;
                return;
            }
            wp->routine_1++;
            return;
        case 2:
            wp->anim_AC = 1;
            *arg2       = 0;
            wp->routine_1++;
            // fall through
        case 3:
            if (*arg2 < 6)
            {
                wp->rotation.y -= 0x80;
                Obj_pos_set(wp, 0x40, 0, 0);
                *arg2 = (uint16)*arg2 + 1;
                return;
            }
            arg1->routine_7 = 1;
            *arg2           = 0;
            wp->routine_1   = 0;
            wp->routine_0++;
            return;
    }
}

void func_801034B4(ST0A_VIEW *wp, sint32 arg, sint16 *timer)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->u_AC.b[0] = 0x12;
            wp->value_110 = 8;
            wp->routine_1++;
            // fall through
        case 1:
            if (*timer < 0x39)
            {
                (*timer)++;
                break;
            }
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
    }
}

void func_80103530(STAGE_OBJ *wp, STAGE_ROOM *arg1, sint16 *arg2)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_1;
    switch (temp_v1)
    {
        case 0:
            *arg2       = 0;
            wp->anim_AC = 0x13;
            wp->routine_1++;
        case 1:
            if (*arg2 < 3)
            {
                wp->rotation.y += 0xC0;
                Obj_pos_set(wp, -0x30, 0, 0);
                *arg2 = (uint16)*arg2 + 1;
                return;
            }
            arg1->routine_7 = 2;
            wp->routine_1++;
            return;
        case 2:
            if (arg1->routine_7 == 3)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
                return;
            }
            Obj_pos_set(wp, -0x37, 0, 0);
            return;
    }
}

void func_80103630(STAGE_OBJ *wp, STAGE_ROOM *arg1, sint16 *arg2)
{
    switch (wp->routine_1)
    {
        case 0:
            arg2[0]     = 0;
            wp->anim_AC = 1;
            wp->routine_1++;
            // fall through
        case 1:
            if (arg2[0] < 0xF)
            {
                Obj_pos_set(wp, -0x30, 0, -0x30);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            arg2[0] = 0;
            wp->routine_1++;
            break;
        case 2:
            if (arg2[0] < 0xC)
            {
                wp->rotation.y -= 0x80;
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            arg2[0]       = 0;
            wp->value_110 = 6;
            wp->routine_1++;
            break;
        case 3:
            if (arg2[0] < 4)
            {
                Obj_pos_set(wp, 0x40, 0, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 4:
            arg2[0]     = 0;
            wp->anim_AC = 0x15;
            wp->routine_1++;
            break;
        case 5:
            if (wp->value_A4 == 0x12)
            {
                arg2[1] = 0;
            }
            if (wp->value_A4 >= 0xA && wp->value_A4 < 0x1B)
            {
                Obj_pos_set(wp, 0x30, -0x30, 0);
            }
            else if (wp->value_A4 == 0x1B)
            {
                wp->position.y         = -0x34;
                wp->position_fixed.v.y = -0x340000;
            }
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 6:
            arg2[0]     = 0;
            wp->anim_AC = 1;
            wp->routine_1++;
            // fall through
        case 7:
            if (arg2[0] < 0x20)
            {
                wp->rotation.y -= 0x20;
                Obj_pos_set(wp, 0x38, 0, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 8:
            arg2[0]     = 0;
            wp->anim_AC = 1;
            wp->routine_1++;
            // fall through
        case 9:
            if (arg2[0] < 4)
            {
                wp->rotation.y -= 0x100;
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 10:
            wp->anim_AC = 0x16;
            break;
    }
}

void func_8010387C(STAGE_OBJ *wp, sint32 arg, STCOM_SVECTOR *hit)
{
    D_80115960[wp->routine_0](wp, arg, hit);
    if (hit->y != 0)
    {
        Model_Shadow_Trans(wp, 0x28, 0x200, 0);
    }
}

void func_801038EC(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *hit)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_AC        = 9;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            wp->value_110      = 7;
            hit->y             = 0;
            wp->routine_1++;
            break;
        case 1:
            wp->rotation.y += 0x80;
            if (scene->reserved00[6] == 3)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            wp->rotation.y += 0x80;
            if ((wp->rotation.y & 0xFFF) > 0xC00)
            {
                wp->rotation.y = 0xC00;
                wp->routine_1++;
            }
            break;
        case 3:
            if (scene->reserved00[6] == 4)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_80103A3C(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, sint16 *arg2)
{
    switch (wp->routine_1)
    {
        case 0:
            arg2[0]     = 0;
            wp->anim_AC = 9;
            wp->routine_1++;
            // fall through
        case 1:
            if (arg2[0] < 0xC)
            {
                arg2[0]++;
            }
            else
            {
                wp->routine_1++;
            }
            Obj_pos_set(wp, 0x80, 0, 0);
            break;
        case 2:
            wp->anim_AC = 7;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 3:
            if (arg2[0] < 8)
            {
                Obj_pos_set(wp, 0x30, 0x40, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 4:
            wp->anim_AC            = 8;
            wp->position.y         = -0x34;
            wp->position_fixed.v.y = -0x340000;
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 5:
            wp->anim_AC = 9;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 6:
            if (arg2[0] < 0x18)
            {
                wp->rotation.y += 8;
                arg2[0] = (uint16)arg2[0] + 1;
            }
            else
            {
                wp->routine_1++;
            }
            Obj_pos_set(wp, 0x80, 0, 0);
            break;
        case 7:
            wp->anim_AC = 7;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 8:
            if (arg2[0] == 5)
            {
                arg2[1] = 1;
            }
            if (arg2[0] < 0xD)
            {
                Obj_pos_set(wp, 0x30, 0x40, 0);
                arg2[0] = (uint16)arg2[0] + 1;
                break;
            }
            wp->routine_1++;
            break;
        case 9:
            wp->anim_AC            = 8;
            wp->position.y         = -1;
            wp->position_fixed.v.y = -0x10000;
            if (wp->value_A7 == -1)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_80103C58(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, sint16 *arg2)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->anim_AC = 9;
            *arg2       = 0;
            wp->routine_1++;
            // fall through
        case 1:
            if (*arg2 < 4)
            {
                wp->rotation.y += 8;
                *arg2 = (uint16)*arg2 + 1;
            }
            else
            {
                wp->routine_1++;
            }
            Obj_pos_set(wp, 0x80, 0, 0);
            break;
        case 2:
            wp->anim_AC = 5;
            *arg2       = 0;
            wp->routine_1++;
            break;
        case 3:
            if (wp->value_A7 != -1)
            {
                Obj_pos_set(wp, 0x40, 0, 0);
                break;
            }
            wp->routine_1++;
            break;
        case 4:
            if (*arg2 < 0x32)
            {
                (*arg2)++;
                break;
            }
            wp->routine_1++;
            break;
        case 5:
            wp->anim_AC   = 0x23;
            wp->value_110 = 8;
            *arg2         = 0;
            wp->routine_1++;
            break;
        case 6:
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 7:
            wp->anim_AC = 0x14;
            *arg2       = 0;
            wp->routine_1++;
            // fall through
        case 8:
            if (*arg2 < 0x10)
            {
                wp->rotation.y += 0x72;
                *arg2 = (uint16)*arg2 + 1;
                break;
            }
            *arg2 = 0;
            wp->routine_1++;
            break;
        case 9:
            if (*arg2 < 0x2E)
            {
                (*arg2)++;
            }
            else
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            Obj_pos_set(wp, 0x30, 0, 0);
            break;
    }
}

void func_80103E24(STAGE_OBJ *wp, STAGE_SCENE_WORK *scene, sint16 *arg2)
{
    switch (wp->routine_1)
    {
        case 0:
            arg2[0]     = 0;
            wp->anim_AC = 0x15;
            wp->routine_1++;
            break;
        case 1:
            if (wp->value_A4 == 0x12)
            {
                arg2[1] = 0;
            }
            if (wp->value_A4 >= 0xA && wp->value_A4 < 0x1B)
            {
                Obj_pos_set(wp, 0x30, -0x30, 0);
            }
            else if (wp->value_A4 == 0x1B)
            {
                wp->position.y         = -0x34;
                wp->position_fixed.v.y = -0x340000;
            }
            if (wp->value_A7 == -1)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            wp->anim_AC = 0x14;
            arg2[0]     = 0;
            wp->routine_1++;
            // fall through
        case 3:
            if (arg2[0] < 0x10)
            {
                arg2[0]++;
            }
            else
            {
                arg2[0] = 0;
                wp->routine_1++;
            }
            wp->rotation.y -= 0x38;
            Obj_pos_set(wp, 0x10, 0, 0);
            break;
        case 4:
            if (arg2[0] < 0xA)
            {
                arg2[0]++;
            }
            else
            {
                arg2[0] = 0;
                wp->routine_1++;
            }
            Obj_pos_set(wp, 0x40, 0, 0);
            break;
        case 5:
            wp->rotation.y = 0xC00;
            wp->anim_AC    = 0x17;
            break;
    }
}

void func_80103FE4(ST0A_EN *wp)
{
    D_80115970[wp->routine_0](wp);
    wp->ctl.hit_14 = 0;
}

void func_80104030(ST0A_EN *wp)
{
    sint16 life;

    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]           = 0x2000200;
    wp->scale.words[1]           = 0x200;
    wp->scale.v.pad              = 0x4210;
    wp->rotation.x               = 0;
    wp->rotation.z               = 0;
    *(uint32 *)&wp->turn_64      = 0;
    wp->velocity.words[0]        = 0;
    wp->velocity.words[1]        = 0;
    wp->ctl.flags_0              = 0xE;
    *(uint32 *)&wp->ctl.timer_4  = 0;
    *(uint32 *)&wp->ctl.value_8  = 0;
    wp->ctl.hit_14               = 0;
    wp->ctl.value_18             = 0;
    func_80036478(wp->ctl.track_24, 0, -0x60);
    wp->ctl.home_34  = wp->position;
    wp->ctl.held_3C  = NULL;
    wp->ctl.owner_40 = func_80036294(wp->byte_C);
    life             = D_80098844[wp->kind_2]->life_28;
    wp->data_78      = D_80115988;
    wp->routine_0    = 1;
    wp->data_10      = NULL;
    wp->routine_1    = 2;
    *(uint16 *)&wp->routine_2 = 0;
    wp->life_6E      = life;
    wp->life_max_B0  = life;
    wp->life_prev_B2 = life;
    func_800322A8(wp, 0, 0);
    func_80104154(wp);
}

void func_80104154(ST0A_EN *wp)
{
    ST0A_EN_CTL *ctl;

    ctl                     = &wp->ctl;
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    ctl->rand_2          = rand();
    if (func_8003648C(ctl->track_24, wp))
    {
        ctl->flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 4)
    {
        func_8010490C(wp);
    }
    D_8011597C[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                wp->routine_1 = 0;
                break;
            case 1:
            case 2:
                func_80031824(wp);
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->damage_A != 0)
    {
        ctl->damage_A--;
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
        ctl->pos_C.y -= 0x28;
        func_800341BC(&ctl->pos_C, 0x28, 0, 0x8000, wp->value_1, &ctl->hit_14, 0x4000000, 0x800000, 0);
    }
}

void func_801043B8(ST0A_EN *wp)
{
    func_80031824(wp);
}

void func_801043D8(ST0A_EN *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_801043F8(ST0A_EN *wp)
{
    ST0A_EN_CTL *ctl;
    STAGE_PL_VIEW *pl;
    sint16 step;

    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC = 9;
            wp->routine_2++;
            ctl->timer_4 = 0xA;
            ctl->timer_6 = 0;
            ctl->held_3C = (ST0A_HELD *)Open_SHL_WORK();
            if (ctl->held_3C != NULL)
            {
                ctl->held_3C->flags_0   = 1;
                ctl->held_3C->kind_2    = 6;
                ctl->held_3C->variant_3 = 0x81;
                ctl->held_3C->routine_0 = 4;
                ctl->flags_0 |= 0x20;
            }
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2++;
            }
            ctl->timer_6++;
            Obj_pos_set(wp, 0xC0, 0, 0);
            ctl->held_3C->position_fixed   = wp->position_fixed;
            ctl->held_3C->position_fixed.y = (wp->position.y - 0x64) << 16;
            func_80030150(&ctl->held_3C->position_fixed, &ctl->held_3C->position);
            break;
        case 2:
            step           = Muku(&wp->position, &pl->position, wp->rotation.y, 0x80);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (ST0A_ABS(step) < 0x80)
            {
                wp->anim_AC = 0x30;
                wp->routine_2++;
                ctl->timer_4 = 0xF;
            }
            break;
        case 3:
            if (--ctl->timer_4 == 0)
            {
                if (ctl->flags_0 & 0x20)
                {
                    ctl->held_3C->variant_3 = 0x80;
                    ctl->held_3C->routine_0 = 0;
                    ctl->held_3C->angle_64  = wp->rotation.y;
                    ctl->held_3C->speed_9C  = 0x20;
                    ctl->held_3C->value_A0  = 0xC;
                    ctl->flags_0 &= ~0x20;
                }
                wp->anim_AC = 9;
                wp->routine_2++;
            }
            break;
        case 4:
            step           = Muku(&wp->position, &ctl->home_34, wp->rotation.y, 0x80);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0)
            {
                wp->routine_2++;
                ctl->timer_4 = 0xA;
            }
            break;
        case 5:
            ctl->timer_6--;
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2++;
            }
            Obj_pos_set(wp, 0xC0, 0, 0);
            break;
        case 6:
            ctl->flags_0 |= 1;
            ctl->owner_40->u_E.b.byte_F |= 2;
            break;
    }
    if (wp->value_A6 != 0)
    {
        Sound_call2(0xD7, &wp->position);
    }
}

void func_80104740(ST0A_EN *wp)
{
    ST0A_EN_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0x25;
            wp->rotation.y = (ctl->owner_40->rotation.y + 0x800) & 0xFFF;
            wp->value_110  = 7;
            ctl->flags_0 &= ~8;
            ctl->timer_4   = 4;
            Sound_call2(0xDA, &wp->position);
            break;
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->anim_AC = 0x26;
                wp->routine_2++;
                if (ctl->flags_0 & 0x20)
                {
                    ctl->held_3C->routine_0 = 0;
                    ctl->held_3C->angle_64  = ctl->owner_40->rotation.y;
                    ctl->held_3C->speed_9C  = 0x20;
                    ctl->held_3C->value_A0  = 4;
                }
            }
            break;
        case 2:
            if (--ctl->timer_6 < 0)
            {
                wp->routine_2++;
                if (ctl->flags_0 & 0x20)
                {
                    Close_SHL_WORK(ctl->held_3C);
                    ctl->flags_0 &= ~0x20;
                    ctl->owner_40->u_E.b.byte_F |= 4;
                }
            }
            Obj_pos_set(wp, -0xB0, 0, 0);
            break;
        case 3:
            ctl->flags_0 |= 9;
            ctl->owner_40->u_E.b.byte_F |= 2;
            break;
    }
}

sint32 func_8010490C(ST0A_EN *wp)
{
    sint32 damage;

    damage = wp->ctl.hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (wp->ctl.hit_14 & 0x38000000)
        {
            if (wp->ctl.flags_0 & 8)
            {
                wp->ctl.damage_A += damage;
                if ((wp->ctl.hit_14 & 0x20000000) || wp->ctl.damage_A >= D_80098844[wp->kind_2]->stun_29)
                {
                    Sound_call2(0xA2, &wp->position);
                    wp->rotation.y            = (wp->ctl.owner_40->rotation.y + 0x800) & 0xFFF;
                    wp->routine_1             = 1;
                    *(uint16 *)&wp->routine_2 = 0;
                    wp->ctl.damage_A          = 0;
                }
                else
                {
                    Sound_call2(0xA0, &wp->position);
                }
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
