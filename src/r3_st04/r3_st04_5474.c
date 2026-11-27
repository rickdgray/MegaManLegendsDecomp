#include "common.h"
#include "st04.h"

void func_80105474(STAGE_WORK *wp)
{
    D_8010C9AC[wp->routine_0](wp);
}

void func_801054B0(ST04_ACTOR *wp)
{
    STCOM_FIXED_VECTOR fixed;
    ST04_ACTOR_CTL *ctl;

    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    if (wp->variant_3 != 0)
    {
        Model_work_init(wp, &wp->variant_3);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 2;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    fixed                    = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &fixed, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->data_10               = D_8010C9C0;
    wp->value_78              = 0;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->velocity.v.z          = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_801055F0(wp);
}

void func_801055F0(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    ctl                     = &wp->ctl;
    if (ctl->flags_0 & 2)
    {
        func_80105A8C(wp);
    }
    D_8010C9B8[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
            case 1:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
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
    if (wp->flags_0 & 1)
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_80105794(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_801057B4(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;
    sint32 step;
    uint8 routine;

    ctl     = &wp->ctl;
    routine = wp->routine_2;
    switch (routine)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            if (Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x800) < 0)
            {
                step = -Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x800);
            }
            else
            {
                step = Muku(&wp->position, &ctl->target_C, wp->rotation.y, 0x800);
            }
            wp->turn_64  = (uint32)step >> 3;
            ctl->timer_4 = 0x1E;
            // fall through
        case 1:
            step           = Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if ((sint16)step == 0)
            {
                ctl->flags_0 |= 2;
                wp->routine_2++;
            }
            break;
        case 2: // empty: gives retail's compare chain
            break;
    }
}

void func_801058CC(ST04_ACTOR *wp)
{
    STAGE_PL_VIEW *pl;
    ST04_ACTOR_CTL *ctl;
    uint32 turn;
    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            if (Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
            {
                turn = -Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
            }
            else
            {
                turn = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
            }
            turn >>= 3;
            wp->turn_64  = turn;
            ctl->timer_4 = (ctl->value_2 & 0x3F) + 8;
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (--wp->ctl.timer_4 < 0)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            if (Scene_work.reserved00[0] == 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2--;
                wp->ctl.timer_4 = (wp->ctl.value_2 & 0x3F) + 8;
            }
            if (Scene_work.reserved00[0] == 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
    }
}

sint32 func_80105A8C(ST04_ACTOR *wp)
{
    ST04_ACTOR *target;

    if (Player_work.target_184 == wp)
    {
        target                        = Player_work.target_184;
        target->routine_1             = 1;
        *(uint16 *)&target->routine_2 = 0;
        target->ctl.flags_0 &= ~2;
        STCOM_PLAYER_WORK_PTR->target_184 = NULL;
        if (Game_work.value_50 == 4)
        {
            func_8001DDE4(9);
            STAGE_SCENE_BYTE(4) = 1;
        }
        else
        {
            func_8001DDE4(0x1D);
            STAGE_SCENE_BYTE(4) = 0;
        }
    }
    return 1;
}

void func_80105B18(ST04_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010C9CC[wp->variant_3](wp);
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

void func_80105C08(ST04_ACTOR *wp)
{
    STCOM_SVECTOR pos;
    STCOM_FIXED_VECTOR cam;
    ST04_PL_WORK *pl;
    sint16 step;

    pl = ST04_PL;
    if (Sce_flag_test(0x618))
    {
        wp->routine_0 = 0x1A;
    }
    switch (wp->routine_0)
    {
        case 0:
            func_80106048(wp);
            wp->routine_0++;
            break;
        case 1:
            if (Sce_flag_test(0x610))
            {
                cam.x = wp->value_180.x;
                cam.y = wp->value_180.y - 0x20;
                cam.z = wp->value_180.z;
                pos.x = -0xE10;
                pos.y = -1;
                pos.z = 0xE10;
                func_80039FAC(&cam, 0x100, Angle_xz_svector(&pos, &wp->position) + 0x800, D_800A396C);
                pl->flags_0 &= ~2;
                wp->routine_0 = 0xA;
            }
            else if (Sce_flag_test(0x60F))
            {
                wp->value_C4.x = -0xE80;
                wp->value_C4.y = -1;
                wp->value_C4.z = 0x111D;
                wp->routine_0  = 0x14;
            }
            break;
        case 10:
            pos.x          = -0xE10;
            pos.y          = -1;
            pos.z          = 0x10CC;
            step           = Muku(&wp->position, &pos, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0 && !func_8003A13C())
            {
                MojiTaskExec2(0, 0x4E);
                func_800322A8(wp, 8, 0);
                pl->pos_438.x   = -0xE10;
                pl->pos_438.y   = -1;
                pl->pos_438.z   = 0xE10;
                pl->target_184  = NULL;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                wp->routine_1   = 1;
                wp->routine_0++;
            }
            break;
        case 11:
            if (!(Moji_flag & 0x8000000))
            {
                func_80039E18();
                pl->flags_0 |= 2;
                wp->routine_0++;
            }
            break;
        case 12:
            step           = Muku(&wp->position, &wp->value_C4, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0 && !func_8003A13C())
            {
                func_80042314(pl);
                Sce_flag_off(0x610);
                Sce_flag_on(0x60E);
                wp->routine_0 = 1;
            }
            break;
        case 20:
            if (Sce_flag_test(0x612))
            {
                func_80063BC8(&wp->position, 2, 0, 0x4A);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 1;
                wp->routine_0++;
            }
            break;
        case 21:
            if (D_800987B0[0] == 0)
            {
                Sce_flag_on(0x613);
                wp->routine_0++;
            }
            break;
        case 22:
            if (Sce_flag_test(0x614))
            {
                func_80063BC8(&wp->position, 2, 0, 0x4C);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 1;
                wp->routine_0++;
            }
            break;
        case 23:
            if (D_800987B0[0] == 0)
            {
                Sce_flag_on(0x615);
                wp->routine_0++;
            }
            break;
        case 24:
            if (Sce_flag_test(0x20))
            {
                step           = Muku(&wp->position, &wp->value_C4, wp->rotation.y, wp->turn_64);
                wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
                if (step == 0)
                {
                    func_800322A8(wp, 2, 0);
                    wp->velocity.v.x = 0x140;
                    wp->routine_1    = 1;
                    wp->routine_2    = 0x28;
                    wp->routine_0++;
                }
            }
            break;
        case 25:
            if (--wp->routine_2 == 0)
            {
                wp->routine_0++;
            }
            else
            {
                Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
                if (wp->value_A4 == 3 || wp->value_A4 == 10)
                {
                    Sound_call2(0x10C, &wp->position);
                }
            }
            break;
        case 26:
            func_80031824(wp);
            break;
    }
}

void func_80106048(ST04_ACTOR *wp)
{
    sint16 temp_v0;

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    temp_v0              = Obj_ceiling_height_get(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_8010C9D0;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

void func_801060E8(ST04_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010CA2C[wp->variant_3](wp);
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
