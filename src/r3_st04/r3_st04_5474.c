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
            step = Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64);
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
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position,
                                                             wp->rotation.y, wp->turn_64)) &
                             0xFFF;
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
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position,
                                                             wp->rotation.y, wp->turn_64)) &
                             0xFFF;
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
            step = Muku(&wp->position, &wp->value_C4, wp->rotation.y, wp->turn_64);
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
                step = Muku(&wp->position, &wp->value_C4, wp->rotation.y, wp->turn_64);
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
    temp_v0              = func_80048E6C(wp);
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

void func_801061D8(ST04_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 0x10 extra bytes
    ST04_PL_WORK *pl;
    STAGE_CAM *cam;
    sint16 step;

    cam = &Sce_camera_work;
    pl  = ST04_PL;
    if (wp->routine_0 >= 0x15 && func_8001DE84())
    {
        Sce_flag_on(0x618);
        Sce_flag_on(0x20);
        func_80053AA4(0);
        wp->routine_0 = 0x1D;
    }
    switch (wp->routine_0)
    {
        case 0:
            func_80106568(wp);
            wp->routine_0++;
            break;
        case 1:
            if (Sce_flag_test(0x60F))
            {
                wp->value_C4.x = -0xCB8;
                wp->value_C4.y = -1;
                wp->value_C4.z = 0x111D;
                wp->routine_0  = 0x14;
            }
            break;
        case 20:
            func_8001E6C0(0, 0, 0);
            cam->pos_10   = -0xDE80000;
            cam->pos_14   = -0xC80000;
            cam->pos_18   = 0xBDB0000;
            cam->rot_44   = 0x1800000;
            cam->rot_40   = 0;
            cam->rot_48   = 0x2000000;
            step          = Muku(&pl->position, &wp->position, pl->rotation.y, 0x800);
            pl->value_448 = 0x30;
            pl->rot_440.y = (pl->rot_440.y + step) & 0xFFF;
            wp->routine_0++;
            break;
        case 21:
            if (!func_8003A13C())
            {
                func_80063BC8(&wp->position, 2, 0, 0x48);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 1;
                wp->routine_0++;
            }
            break;
        case 22:
            if (D_800987B0[0] == 0)
            {
                Sce_flag_on(0x611);
                wp->routine_0++;
            }
            break;
        case 23:
            if (Sce_flag_test(0x615))
            {
                func_80063BC8(&wp->position, 2, 0, 0x4D);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 1;
                wp->routine_0++;
            }
            break;
        case 24:
            if (D_800987B0[0] == 0)
            {
                wp->routine_0++;
            }
            break;
        case 25:
            step = Muku(&wp->position, &wp->value_C4, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            if (step == 0)
            {
                wp->velocity.v.x = 0x140;
                wp->routine_2    = 0x14;
                wp->routine_0++;
                Sce_flag_on(0x20);
            }
            break;
        case 26:
            if (--wp->routine_2 == 0)
            {
                func_800322A8(wp, 2, 0);
                wp->routine_1 = 0;
                wp->routine_2 = 0x3C;
                wp->routine_0++;
            }
            break;
        case 27:
            if (--wp->routine_2 == 0)
            {
                wp->routine_2 = 0x1E;
                wp->flags_0 &= ~2;
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
        case 28:
            if (--wp->routine_2 == 0)
            {
                wp->routine_0++;
            }
            break;
        case 29:
            if (!func_8003A13C())
            {
                D_800A395C = 1;
                func_80039820();
                func_80042314(pl);
                pl->flags_0 |= 2;
                func_80031824(wp);
            }
            break;
    }
}

void func_80106568(ST04_ACTOR *wp)
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
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

void func_801065FC(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_8010CA34[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    ST04_SP_132 = ctl[1].value_1E;
    func_8003346C(wp);
    if (ctl->flags_0 & 8)
    {
        ctl->target_C = wp->value_180;
        func_800341BC(&ctl->target_C, 0x20, 0, 0x8000, wp->value_1, &ctl->at_14, ctl->value_8 | 0x4880000, 0x800000,
                      0x80);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    func_80051B68(wp, 1, -1, 0);
    ctl->at_14.hit = 0;
}

void func_801067A8(ST04_GUARD *wp)
{
    sint16 life;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->flags_0 |= 2;
    wp->rotation.y = (wp->u_C.b.byte_C << 9) & 0xE00;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->flags_348      = 0x1E;
    wp->value_34C      = 0;
    wp->value_350      = 0;
    wp->value_35C      = 0;
    func_80036478(wp->track_36C, 0, -0x60);
    wp->value_384    = 0;
    wp->value_386    = 0;
    life             = D_80098844[wp->kind_2]->life_8;
    wp->data_78      = D_8010CA64;
    wp->data_10      = D_8010CA70;
    wp->life_6E      = life;
    wp->life_max_B0  = life;
    wp->life_prev_B2 = life;
    switch (wp->variant_3)
    {
        case 0:
            wp->routine_0             = 1;
            wp->routine_1             = 2;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 1, 0);
            break;
        case 1:
            wp->routine_0             = 5;
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 2:
            wp->routine_0             = 4;
            wp->routine_1             = 3;
            *(uint16 *)&wp->routine_2 = 0;
            func_800322A8(wp, 0, 0);
            break;
    }
    wp->scale.v.pad = 0x4210;
}

void func_80106918(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.flags_0 & 0x10)
    {
        func_80107850(wp);
    }
    D_8010CA4C[wp->routine_1](wp);
    if (wp->ctl.timer_A != 0)
    {
        wp->ctl.timer_A--;
    }
    if (wp->ctl.flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 1:
                wp->routine_1 = 4;
                break;
            case 2:
            case 4:
                wp->routine_1 = 2;
                break;
            case 0:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
}

void func_80106A24(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.flags_0 & 0x10)
    {
        func_80107850(wp);
    }
    D_8010CA4C[wp->routine_1](wp);
    if (wp->ctl.timer_A != 0)
    {
        wp->ctl.timer_A--;
    }
    if (wp->ctl.flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 5:
                wp->routine_1 = 3;
                break;
            case 3:
            case 4:
                func_801076F0(wp);
                break;
            case 1:
                wp->routine_1 = 4;
                break;
            case 0:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
}

void func_80106B28(ST04_ACTOR *wp)
{
    if (wp->ctl.flags_0 & 0x10)
    {
        func_80107850(wp);
    }
    D_8010CA4C[wp->routine_1](wp);
    if (wp->ctl.timer_A != 0)
    {
        wp->ctl.timer_A--;
    }
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
}

void func_80106BCC(STAGE_FX *wp)
{
    func_80031824(wp);
}

void func_80106BEC(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0;
            ctl->timer_4  = 0x1E;
            ctl->value_8  = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80106C5C(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;
    uint16 idx;
    sint32 hit;
    sint32 dx;
    sint32 dz;
    sint16 y;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x31;
            ctl[1].at_14.goal.x =
                D_8010CA7C[wp->ctl2.value_1C].x + (D_8010CA7C[wp->ctl2.value_1C].w >> 1);
            ctl[1].at_14.goal.y = 0;
            ctl[1].at_14.goal.z =
                D_8010CA7C[wp->ctl2.value_1C].z + (D_8010CA7C[wp->ctl2.value_1C].d >> 1);
            ctl->value_8 = 0;
            // fall through
        case 1:
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &ctl[1].at_14.goal, wp->rotation.y, 8)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            hit                  = func_8004B414(wp);
            y                    = func_80048E6C(wp);
            wp->position.y       = y;
            wp->position_fixed.y = y << 16;
            if (STCOM_ABS(wp->position.y - wp->position_prev.y) > 0x20)
            {
                wp->rotation.y       = (wp->rotation.y + 0x800) & 0xFFF;
                wp->position.y       = wp->position_prev.y;
                wp->position_fixed.y = wp->position_fixed_prev.y;
                break;
            }
            if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            idx = ctl[1].value_1C;
            dx  = wp->position.x - D_8010CA7C[idx].x;
            dz  = wp->position.z - D_8010CA7C[idx].z;
            if ((uint32)dx < (uint32)D_8010CA7C[idx].w && (uint32)dz < (uint32)D_8010CA7C[idx].d)
            {
                if (++ctl[1].value_1C >= 4)
                {
                    ctl[1].value_1C = 0;
                }
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80106E84(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0x10;
            ctl->timer_4  = 0x14;
            ctl->value_8  = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = (ctl->value_2 & 3) * 0x17;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 0x17;
            ctl->timer_4  = 0x14;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80106F90(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2  = 1;
            wp->rotation.y = (wp->rotation.y + 0x10) & 0xF00;
            if (wp->ctl.flags_0 & 0x40)
            {
                wp->anim_AC = 0x12;
            }
            else
            {
                wp->anim_AC = 0x13;
            }
            ctl->timer_4   = 0x27;
            ctl->value_8   = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                if (ctl->flags_0 & 0x40)
                {
                    wp->rotation.y  = (wp->rotation.y + 0x400) & 0xFFF;
                    ctl[1].value_1E = 0xE53;
                }
                else
                {
                    wp->rotation.y  = (wp->rotation.y - 0x400) & 0xFFF;
                    ctl[1].value_1E = 0x1AD;
                }
                wp->routine_2    = 2;
                wp->anim_AC      = 0x14;
                wp->velocity.v.x = 0x26;
                ctl->timer_4 = ctl->value_6 = ((ctl->value_2 & 3) + 1) * 32;
            }
            else
            {
                if (ctl->flags_0 & 0x40)
                {
                    ctl[1].value_1E -= 0xB;
                }
                else
                {
                    ctl[1].value_1E += 0xB;
                }
                break;
            }
            // fall through
        case 2:
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            hit = func_8004B414(wp);
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2   = 3;
                if (ctl->flags_0 & 0x40)
                {
                    wp->anim_AC = 0x13;
                }
                else
                {
                    wp->anim_AC = 0x12;
                }
                ctl[1].value_1C = 0;
                ctl->timer_4    = 0x27;
            }
            if (hit & 0xF00)
            {
                wp->routine_2 = 3;
                if (ctl->flags_0 & 0x40)
                {
                    wp->anim_AC     = 0x13;
                    ctl[1].value_1C = 1;
                }
                else
                {
                    wp->anim_AC     = 0x12;
                    ctl[1].value_1C = 2;
                }
                ctl->timer_4 = 0x27;
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->anim_AC = 0;
                if (wp->ctl.flags_0 & 0x40)
                {
                    wp->rotation.y = (wp->rotation.y - 0x400) & 0xFFF;
                }
                else
                {
                    wp->rotation.y = (wp->rotation.y + 0x400) & 0xFFF;
                }
                ctl[1].value_1E = 0;
                ctl->flags_0 |= 1;
            }
            else
            {
                if (wp->ctl.flags_0 & 0x40)
                {
                    wp->ctl2.value_1E += 0xB;
                }
                else
                {
                    wp->ctl2.value_1E -= 0xB;
                }
            }
            break;
    }
}

void func_80107264(ST04_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    ST04_ACTOR_CTL *ctl;
    sint16 turn;
    uint32 dir;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            if (Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
            {
                dir = -Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
            }
            else
            {
                dir = Muku(&wp->position, &pl->position, wp->rotation.y, 0x800);
            }
            wp->turn_64 = dir >> 3;
            ctl[1].value_1E = 0;
            D_80111D60      = D_800A395A[0];
            pl->flags_0 &= ~2;
            D_80111D64      = D_800A395A[1];
            D_800A395A[0]   = 0x10;
            D_800A395A[1]   = 0xF0;
            D_800A39D0.x = wp->value_180.x;
            D_800A39D0.y = wp->value_180.y;
            D_800A39D0.z = wp->value_180.z;
            D_800A3988[0] = 0x100;
            D_800A398C = Angle_xz_svector(&pl->position, &wp->position) + 0x800;
            D_800A3990 = D_800A396C;
            break;
        case 1:
            if (D_800A395A[0] != 0)
            {
                D_800A395A[0]--;
            }
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && D_800A395A[0] == 1)
            {
                wp->routine_2 = 2;
                wp->anim_AC   = 8;
                MojiTaskExec2(0, wp->value_D);
                wp->ctl.timer_4 = 0x78;
            }
            break;
        case 2:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->anim_prev_AD = 0xFF;
                wp->ctl.timer_4  = 0x78;
            }
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_2 = 3;
            }
            break;
        case 3:
            if (D_800A395A[0] >= 0x10)
            {
                Player_work.target_184 = NULL;
                D_800A395A[0]          = D_80111D60;
                D_800A395A[1]          = D_80111D64;
                D_800A3988[0]             = D_800A3964;
                Player_work.flags_bd &= 0x7F;
                pl->flags_0 |= 2;
                wp->ctl.flags_0 |= 0x11;
            }
            else
            {
                D_800A395A[0]++;
            }
            break;
    }
}

void func_8010754C(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            if (wp->variant_3 == 0)
            {
                ctl[1].at_14.goal.x =
                    D_8010CA7C[wp->ctl2.value_1C].x + (D_8010CA7C[wp->ctl2.value_1C].w >> 1);
                ctl[1].at_14.goal.y = 0;
                ctl[1].at_14.goal.z =
                    D_8010CA7C[wp->ctl2.value_1C].z + (D_8010CA7C[wp->ctl2.value_1C].d >> 1);
            }
            else
            {
                ctl[1].at_14.goal.y = 0;
                ctl[1].at_14.goal.x = wp->position.x;
                ctl[1].at_14.goal.z = wp->position.z - 0x100;
            }
            if (Muku(&wp->position, &ctl[1].at_14.goal, wp->rotation.y, 0x800) < 0)
            {
                wp->turn_64 = (uint32)-Muku(&wp->position, &ctl[1].at_14.goal, wp->rotation.y, 0x800) >> 3;
            }
            else
            {
                wp->turn_64 = (uint32)Muku(&wp->position, &ctl[1].at_14.goal, wp->rotation.y, 0x800) >> 3;
            }
            ctl->timer_4 = 8;
            ctl->value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 <= 0)
            {
                ctl->flags_0 |= 1;
            }
            wp->rotation.y =
                (wp->rotation.y + Muku(&wp->position, &ctl[1].at_14.goal, wp->rotation.y, wp->turn_64)) & 0xFFF;
            break;
    }
}

sint32 func_801076F0(ST04_ACTOR *wp)
{
    ST04_ACTOR_CTL *ctl;
    sint16 sum;
    sint16 i;

    ctl = &wp->ctl;
    sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += D_8010CA9C[wp->ctl2.value_1C][i];
        if ((ctl->value_2 & 0xF) < sum)
        {
            break;
        }
    }
    switch (i)
    {
        case 0:
            wp->routine_1 = 3;
            break;
        case 1:
            wp->routine_1 = 5;
            ctl->flags_0 |= 0x40;
            break;
        case 2:
            wp->routine_1 = 5;
            ctl->flags_0 &= ~0x40;
            break;
    }
    return 1;
}

sint32 func_801077E8(ST04_ACTOR *wp)
{
    uint32 hit;
    uint32 damage;

    hit    = wp->ctl.at_14.hit;
    damage = hit & 0xFFFFFF;
    if (damage != 0 && (hit & 0x18000000))
    {
        wp->value_B2 = wp->value_6E;
        wp->value_6E -= damage;
        if (wp->value_6E <= 0)
        {
            wp->ctl.flags_0 = (wp->ctl.flags_0 & ~2) | 4;
        }
        wp->scale.v.pad = 0x7FFF;
    }
    return 1;
}

sint32 func_80107850(ST04_ACTOR *wp)
{
    if (Player_work.target_184 == wp)
    {
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
        Player_work.flags_bd |= 0x80;
        wp->ctl.flags_0 &= ~0x10;
    }
    return 1;
}

void func_801078A0(ST04_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010CAA8[wp->variant_3](wp);
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

void func_80107990(ST04_ACTOR *wp)
{
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
            func_80107C24(wp);
            wp->routine_0++;
            break;
        case 1:
            if (Sce_flag_test(0x60F))
            {
                pl->pos_438.x   = -0xE10;
                pl->pos_438.y   = -1;
                pl->pos_438.z   = 0xE10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                wp->value_C4.x  = -0xD80;
                wp->value_C4.y  = -1;
                wp->value_C4.z  = 0x111D;
                wp->routine_0   = 0x14;
            }
            break;
        case 20:
            if (Sce_flag_test(0x611))
            {
                func_80063BC8(&wp->position, 2, 0, 0x49);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 1;
                wp->routine_0++;
            }
            break;
        case 21:
            if (D_800987B0[0] == 0)
            {
                Sce_flag_on(0x612);
                wp->routine_0++;
            }
            break;
        case 22:
            if (Sce_flag_test(0x613))
            {
                func_80063BC8(&wp->position, 2, 0, 0x4B);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 1;
                wp->routine_0++;
            }
            break;
        case 23:
            if (D_800987B0[0] == 0)
            {
                Sce_flag_on(0x614);
                wp->routine_0++;
            }
            break;
        case 24:
            if (Sce_flag_test(0x20))
            {
                step = Muku(&wp->position, &wp->value_C4, wp->rotation.y, wp->turn_64);
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

void func_80107C24(ST04_ACTOR *wp)
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
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}
