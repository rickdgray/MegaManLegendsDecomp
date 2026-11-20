#include "common.h"
#include "st04.h"

void func_80104B6C(STAGE_WORK *wp)
{
    D_8010C974[wp->routine_0](wp);
}

void func_80104BA8(ST04_ACTOR *wp)
{
    STCOM_FIXED_VECTOR fixed;
    ST04_ACTOR_CTL *ctl;

    wp->flags_0 |= 2;
    ctl = &wp->ctl2;
    if (wp->variant_3 != 0)
    {
        Model_work_init(wp, &wp->variant_3);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0]        = 0x02000200;
    wp->scale.words[1]        = 0x200;
    wp->scale.v.pad           = 0x4210;
    ctl->flags_0              = 0;
    *(uint32 *)&ctl->timer_4  = 0;
    fixed                     = wp->position_fixed; // unused, but retail copies it
    ctl->target_C.x           = -0xDFC;
    ctl->target_C.z           = 0xB90;
    ctl->target_C.y           = 0;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->value_6E              = 0;
    wp->value_B0              = 0;
    wp->value_B2              = 0;
    wp->value_78              = 0;
    wp->data_10               = NULL;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 2, 0);
    Sce_flag_on(0xF);
    func_80104CB8(wp);
}

void func_80104CB8(ST04_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl2.value_2        = rand();
    D_8010C980[wp->routine_1](wp);
    if (wp->ctl2.flags_0 & 1)
    {
        func_80031824(wp);
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
    func_80051B68(wp, 1, -1, 0x1000000);
}

void func_80104E08(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_80104E28(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl2;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->velocity.v.x = 0x1C0;
            func_80063BC8(&wp->position, 2, 0, wp->timer_C);
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x20)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            dx = wp->position.x - ctl->target_C.x;
            dz = wp->position.z - ctl->target_C.z;
            if (dx * dx + dz * dz < 0x800)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
    if (wp->value_A6 == 1)
    {
        Sound_call(0x112, 0, 0);
    }
    if (Player_work.flags_71 < 0 && !(ctl->flags_0 & 2))
    {
        ctl->flags_0 |= 2;
        MojiTaskExec2(0, 0);
    }
}

void func_80104F7C(ST04_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010C984[wp->variant_3](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_1 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_1++;
    }
}

void func_8010506C(ST04_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint32 step;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_801051EC(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_8010528C(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            step           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if ((sint16)step == 0 && !func_8003A13C())
            {
                func_80063BC8(&wp->position, 3, 0, func_801053BC());
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (!func_8003A13C())
            {
                pl->flags_bd &= ~0x40;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801051EC(ST04_ACTOR *wp)
{
    sint16 temp_v0;

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    temp_v0              = func_80048E6C(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_8010C98C;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

sint32 func_8010528C(ST04_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (Player_work.target_184 == wp)
    {
        if ((sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
        {
            wp->turn_64 = (uint32) - (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        else
        {
            wp->turn_64 = (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x40;
        D_80111D50.x = wp->value_180.x;
        D_80111D50.y = wp->value_180.y - 0x20;
        D_80111D50.z = wp->value_180.z;
        func_80039FAC(&D_80111D50, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

sint32 func_801053BC(void)
{
    sint32 script;

    script = 0;
    switch (STAGE_GAME_VALUE_52)
    {
        case 0:
            if (!Sce_flag_test(0x20))
            {
                if (Sce_flag_test(0x60E))
                {
                    script = 0x3F;
                }
                else
                {
                    script = 0x3E;
                }
            }
            else
            {
                script = 0x40;
            }
            break;
        case 1:
        case 2:
            break;
        case 3:
            if (Sce_flag_test(0x211))
            {
                script = 0;
            }
            else if (Sce_flag_test(0x20B))
            {
                script = 0x20;
                Sce_flag_on(0x20C);
            }
            else
            {
                script = 0;
            }
            break;
        case 4:
        case 5:
            break;
    }
    return script;
}
