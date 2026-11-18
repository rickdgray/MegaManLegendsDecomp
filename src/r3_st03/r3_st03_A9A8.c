#include "common.h"
#include "st03.h"

void func_8010A9A8(STAGE_OBJ *wp)
{
    sint32 temp_v1;
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    temp_v1 = temp_v0 & 0xFF;
    switch (temp_v1)
    {
        case 0:
            wp->routine_2 = temp_v0 + 1;
            wp->anim_AC   = 0;
        case 1:
            if (Sce_flag_test(0x609) != 0)
            {
                Sce_flag_off(0x609);
                wp->anim_AC = 0x10;
                wp->routine_2++;
            }
            return;
    }
}

void func_8010AA28(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 turn;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            // fall through
        case 1:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                wp->anim_AC = 0x14;
                wp->routine_2++;
                ctl->timer_4 = 0x46;
            }
            break;
        case 2:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0x15;
                wp->routine_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                wp->anim_AC    = 0x11;
                wp->rotation.y = 0x800;
                wp->routine_2++;
            }
            break;
        case 4:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                wp->anim_AC = 1;
                wp->routine_2++;
            }
            break;
        case 5:
            turn           = func_80031BEC(&wp->position, &D_8011709C, wp->rotation.y, 0x40);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if ((sint16)turn == 0)
            {
                Sce_flag_on(0x607);
                wp->anim_AC = 0x11;
                wp->routine_2++;
            }
            break;
    }
}

void func_8010AB8C(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    STCOM_SVECTOR *target;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            // fall through
        case 1:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                wp->anim_AC = 2;
                wp->routine_2++;
                ctl->timer_4 = 0x5A;
            }
            break;
        case 2:
            target = &D_801170A4;
            wp->rotation.y =
                (wp->rotation.y + func_80031BEC(&wp->position, target, wp->rotation.y, 0x50)) &
                0xFFF;
            func_8002FEA4(wp, 0x140, 0, 0);
            func_8004B414(wp);
            dx = wp->position.x - target->x;
            dz = wp->position.z - D_801170A8;
            if (dx * dx + dz * dz < 0x800)
            {
                Sce_flag_on(0x607);
                wp->routine_2++;
            }
            if (wp->value_A6 == 1)
            {
                Sound_call(0x10B, 0, 0);
            }
            break;
    }
}

void func_8010ACFC(ST03_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            if (pl->target_184 != wp)
            {
                break;
            }
            pl->target_184 = NULL;
            wp->routine_2  = 2;
            // fall through
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2--;
            }
            if (pl->target_184 != wp)
            {
                break;
            }
            pl->target_184 = NULL;
            wp->routine_2  = 2;
            // fall through
        case 2:
            Sce_flag_on(0x604);
            wp->routine_3 = 0x10;
            wp->anim_AC   = 0;
            wp->routine_2++;
            wp->turn_64 =
                (uint32)STCOM_ABS(func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
            wp->velocity.v.x = 0;
            wp->velocity.v.y = 0;
            wp->velocity.v.z = 0;
            break;
        case 3:
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &pl->position, wp->rotation.y,
                                                             wp->turn_64)) &
                             0xFFF;
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&wp->position, &pl->position, wp->rotation.y,
                                                             wp->turn_64)) &
                             0xFFF;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2--;
            }
            break;
        case 5:
            break;
    }
}

void func_8010AEEC(ST03_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    func_8010AFC0(wp);
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
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

void func_8010AFC0(ST03_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // never used: retail's frame reserves it
    STCOM_PL_WORK *pl;
    sint32 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_8010B2CC(wp);
            wp->routine_0++;
            break;
        case 1:
            if (pl->target_184 == wp)
            {
                pl->target_184        = NULL;
                D_800989F8.routine_4  = 4;
                wp->routine_2         = 5;
                wp->routine_0++;
            }
            break;
        case 2:
            if (wp->routine_2 == 0)
            {
                turn           = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
                wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
                if ((sint16)turn == 0)
                {
                    wp->routine_0++;
                }
            }
            else
            {
                wp->routine_2--;
            }
            break;
        case 3:
            MojiTaskExec2(0, 0xD);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 4:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001F158();
                wp->routine_0++;
            }
            break;
        case 5:
            MojiTaskExec2(0, 0xE);
            wp->routine_0++;
            break;
        case 6:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_0++;
            }
            break;
        case 7:
            MojiTaskExec2(0, 0xF);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_0++;
            }
            break;
        case 9:
            MojiTaskExec2(0, 0x10);
            wp->routine_0++;
            break;
        case 10:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001F158();
                wp->routine_0++;
            }
            break;
        case 11:
            MojiTaskExec2(0, 0x11);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 12:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001F158();
                wp->routine_0++;
            }
            break;
        case 13:
        {
            // Initialized here, not at the top: retail copies it in this case only.
            STCOM_SVECTOR target = {0x1637, -1, 0x4E3A, 0};

            turn           = func_80031BEC(&wp->position, &target, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if ((sint16)turn == 0)
            {
                func_800322A8(wp, 1, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        }
        case 14:
            if (!Sce_flag_test(0x1A))
            {
                func_8002FEA4(wp, 0x50, 0, 0);
                if (wp->value_A6 != 0)
                {
                    Sound_call2(0x111, &wp->position);
                }
            }
            break;
    }
    if (Sce_flag_test(0x1A))
    {
        func_80031824(wp);
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010B2CC(ST03_ACTOR *wp)
{
    sint16 y;

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    func_8002F9C4(wp, &wp->variant_3);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    y                    = func_80048E6C(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 0x10;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_801170AC;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
    wp->routine_2 = 0;
}

void func_8010B370(ST03_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    func_8010B444(wp);
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
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

void func_8010B444(ST03_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // never used: retail's frame reserves it
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_8010B63C(wp);
            wp->routine_0++;
            wp->rotation.y += func_80031BEC(&wp->position, &((STAGE_OBJ *)STAGE_SCENE_OBJ(0))->position,
                                            wp->rotation.y, 0x800);
            break;
        case 1:
            if (Scene_work.u_8.byte[1] == 3)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB5);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            if (Scene_work.u_8.byte[1] == 5)
            {
                wp->rotation.y += func_80031BEC(&wp->position, &pl->position, wp->rotation.y, 0x800);
                wp->routine_0++;
            }
            break;
        case 4:
            func_800322A8(wp, 8, 0);
            MojiTaskExec2(0, 0xB7);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 6:
            if (Scene_work.u_8.byte[1] == 7)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB9);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 2:
        case 5:
        case 7:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001F158();
                wp->routine_0++;
            }
            break;
        case 8:
            if (Scene_work.reserved00[0] == 0)
            {
                wp->routine_0 = wp->routine_1 = wp->routine_2 = wp->routine_3 = 0;
                wp->timer_C                                              = 0x5C;
                wp->value_D = wp->value_E = wp->value_F = 0;
                wp->value_4                                              = 0;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010B63C(ST03_ACTOR *wp)
{
    sint16 temp_v0;

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    func_8002F9C4(wp, &wp->variant_3);
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

void func_8010B6D0(ST03_OBJ *wp)
{
    wp->variant_3                  = 1;
    wp->scale.words[1]             = 0x200;
    wp->scale.words[0]             = 0x02000200;
    wp->value_64                   = 0;
    *(uint32 *)&wp->rotation.x     = 0;
    *(uint32 *)&wp->rotation.z     = 0;
    wp->value_44.value             = 0;
    wp->value_48.value             = 0;
    wp->value_64                   = 0;
    wp->value_70                   = 0;
    wp->value_74                   = 0;
    wp->rotation.y                 = 0x800;
    wp->flags_0 |= 2;
    wp->rotation_prev = wp->rotation;
    wp->position.x    = -0x9C0;
    wp->position.y    = -1;
    wp->position.z    = -0x5277;
    wp->scale.v.pad   = 0x4210;
    wp->position_fixed.v.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.v.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.v.y = wp->position_fixed_prev.y = wp->position.y << 16;
    func_8002F9C4(wp, &wp->variant_3);
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_8010B7DC(STAGE_OBJ *wp)
{
    if (Player_work.position.z < -0x5153)
    {
        func_8001DDE4(0x1F);
        wp->routine_0++;
    }
    func_80032488(wp);
    func_8002C8CC(wp, 0x30, 0x200, 0);
    func_80051B68(wp, 1, -1, 0);
}

void func_8010B858(ST03_ACTOR *wp)
{
    if (wp->velocity.v.x != 0)
    {
        if (!(ST03_FRAME & 7))
        {
            Sound_call2(0x10D, &wp->position);
        }
        func_8002FEA4(wp, wp->velocity.v.x, 0, 0);
        wp->position.y         = func_80048E6C(wp);
        wp->position_fixed.y = wp->position.y << 0x10;
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
    if (wp->value_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->value_E, 0);
        wp->value_D = 0;
    }
    func_8002C8CC(wp, 0x30, 0x200, 0);
}

void func_8010B930(STAGE_OBJ *wp)
{
    D_801170B8[wp->routine_0](wp);
}
