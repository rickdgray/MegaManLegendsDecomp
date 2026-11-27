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
            turn           = Muku(&wp->position, &D_8011709C, wp->rotation.y, 0x40);
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
            target         = &D_801170A4;
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, target, wp->rotation.y, 0x50)) & 0xFFF;
            Obj_pos_set(wp, 0x140, 0, 0);
            Obj_map_push_out(wp);
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
            wp->turn_64      = (uint32)STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
            wp->velocity.v.x = 0;
            wp->velocity.v.y = 0;
            wp->velocity.v.z = 0;
            break;
        case 3:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
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
                pl->target_184       = NULL;
                D_800989F8.routine_4 = 4;
                wp->routine_2        = 5;
                wp->routine_0++;
            }
            break;
        case 2:
            if (wp->routine_2 == 0)
            {
                turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
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
                Sce_event_next();
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
                Sce_event_next();
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
                Sce_event_next();
                wp->routine_0++;
            }
            break;
        case 13:
        {
            // Initialized here, not at the top: retail copies it in this case only.
            STCOM_SVECTOR target = {0x1637, -1, 0x4E3A, 0};

            turn           = Muku(&wp->position, &target, wp->rotation.y, wp->turn_64);
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
                Obj_pos_set(wp, 0x50, 0, 0);
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
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    y                    = Obj_ceiling_height_get(wp);
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
