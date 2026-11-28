#include "common.h"
#include "st03.h"

void func_8010C66C(STAGE_OBJ *wp)
{
    D_801170E0[wp->routine_0](wp);
}

void func_8010C6A8(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
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
    wp->scale.words[0]       = 0x021A021A;
    wp->scale.words[1]       = 0x21A;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 0;
    *(uint32 *)&ctl->timer_4 = 0;
    D_8011CAB8               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_8011CAB8, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->value_78              = (sint32)D_801170F8;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->data_10               = NULL;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8010C7E8(wp);
}

void func_8010C7E8(ST03_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_801170EC[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
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
    func_80051B68(wp, 3, -1, 0);
}

void func_8010C934(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010C954(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_8010C974(ST03_ACTOR *wp)
{
    sint32 dx;
    sint32 dz;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x2C;
            wp->turn_64      = 0x20;
            wp->ctl.target_C = func_80036294(wp->timer_C)->position;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &wp->ctl.target_C, wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A6 == 1)
            {
                Sound_call(0x10A, 0, 0);
            }
            dx = wp->position.x - wp->ctl.target_C.x;
            dz = wp->position.z - wp->ctl.target_C.z;
            if (dx * dx + dz * dz < 0x800)
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->turn_64      = 0;
                wp->routine_2++;
                Sce_flag_on(0x606);
            }
            break;
        case 2:
            break;
    }
}

void func_8010CAB8(ST03_OBJ *wp)
{
    sint32 temp_v1;
    uint8 temp_a1;

    temp_a1 = wp->routine_2;
    temp_v1 = temp_a1 & 0xFF;
    switch (temp_v1)
    {
        case 0:
            wp->routine_2 = temp_a1 + 1;
            wp->anim_AC   = 0;
        case 1:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
                return;
            }
            return;
        case 2:
            if (wp->value_A7 < 0)
            {
                wp->routine_2 = temp_a1 - 1;
                wp->anim_AC   = 0;
            }
            break;
    }
}

void func_8010CB4C(ST03_ACTOR *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0] = 0x021A021A;
            wp->scale.words[1] = 0x21A;
            wp->value_78       = 0;
            wp->data_10        = NULL;
            wp->scale.v.pad    = 0x4210;
            wp->velocity.v.x   = 0;
            wp->velocity.v.y   = 0;
            wp->velocity.v.z   = 0;
            wp->accel_4C.x     = 0;
            wp->accel_4C.y     = 0;
            wp->accel_4C.z     = 0;
            func_800322A8(wp, wp->value_E, 0);
            wp->value_D = 0;
            wp->routine_0++;
            break;
        case 1:
            if (wp->velocity.v.x != 0)
            {
                if (!(ST03_FRAME & 7))
                {
                    Sound_call2(0x10B, &wp->position);
                }
                Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
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
            Model_Shadow_Trans(wp, 0x30, 0x200, 0);
            break;
    }
}

void func_8010CC94(ST03_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    func_8010CD68(wp);
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

void func_8010CD68(ST03_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // never used: retail's frame reserves it
    sint16 turn;

    switch (wp->routine_0)
    {
        case 0:
            func_8010D020(wp);
            func_800322A8(wp, 1, 0);
            wp->routine_1 = 0;
            wp->routine_2 = 0x46;
            wp->routine_0++;
            break;
        case 1:
            Obj_pos_set(wp, 0x50, 0, 0);
            func_8010D0B4(wp);
            if (--wp->routine_2 == 0)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB1);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB2);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                Sce_event_next();
                wp->routine_0++;
            }
            break;
        case 4:
            if (Scene_work.u_8.byte[1] == 2)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB4);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x8000000))
            {
                Sce_event_next();
                wp->routine_0++;
            }
            break;
        case 6:
            if (Scene_work.u_8.byte[1] == 4)
            {
                func_800322A8(wp, 8, 0);
                MojiTaskExec2(0, 0xB6);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x8000000))
            {
                func_800322A8(wp, 1, 0);
                wp->routine_1 = 0;
                wp->routine_2 = 0x3C;
                wp->routine_0++;
            }
            break;
        case 8:
            turn           = Angle_diff_clamp(0x834, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0)
            {
                wp->routine_0++;
            }
            // fall through
        case 9:
            Obj_pos_set(wp, 0x50, 0, 0);
            func_8010D0B4(wp);
            if (--wp->routine_2 == 0)
            {
                Sce_event_next();
                wp->routine_0 = 0xA;
            }
            break;
        case 10:
            func_80031824(wp);
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010D020(ST03_ACTOR *wp)
{
    sint16 y;

    wp->turn_64 = 0x40;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]   = 0x021A021A;
    wp->scale.words[1]   = 0x21A;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    y                    = Obj_ceiling_height_get(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 0x10;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

void func_8010D0B4(ST03_ACTOR *wp)
{
    if (wp->value_A4 == 7 || wp->value_A4 == 0x17)
    {
        Sound_call2(0x10C, &wp->position);
    }
}

void func_8010D0F4(STAGE_OBJ *wp)
{
    D_80117104[wp->routine_0](wp);
}

void func_8010D130(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 0;
    *(uint32 *)&ctl->timer_4 = 0;
    D_8011CAC8               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_8011CAC8, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E          = 0x80;
    wp->value_B0          = 0x80;
    wp->value_B2          = 0x80;
    wp->value_78          = (sint32)D_80117128;
    wp->rotation.x        = 0;
    wp->rotation.z        = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->data_10           = D_80117134;
    if (wp->variant_3 == 0)
    {
        wp->routine_0 = 1;
        wp->routine_1 = 0;
    }
    else
    {
        wp->routine_0 = 1;
        wp->routine_1 = 5;
    }
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8010D268(wp);
}

void func_8010D268(ST03_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_80117110[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        if (wp->routine_1 == 0)
        {
            wp->routine_1 = 0;
        }
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
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
    func_80051B68(wp, 3, -1, 0);
}

void func_8010D3C4(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010D3E4(ST03_ACTOR *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->routine_2++;
        wp->anim_AC = 0;
    }
}

void func_8010D404(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            wp->turn_64 = 0x20;
            // fall through
        case 1:
            ctl->target_C  = func_80036294(wp->timer_C)->position;
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64)) & 0xFFF;
            break;
    }
}

void func_8010D4C0(ST03_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    ST03_ACTOR_CTL *ctl;
    sint32 turn;

    pl  = &Player_work;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            wp->turn_64 = 0x20;
            // fall through
        case 1:
            ctl->target_C  = pl->position;
            turn           = Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if ((sint16)turn != 0)
            {
                break;
            }
            wp->anim_AC = 0;
            wp->routine_2++;
            // fall through
        case 2:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                wp->routine_2--;
                wp->anim_AC = 0;
            }
            break;
    }
}

void func_8010D5EC(ST03_ACTOR *wp)
{
    sint32 dx;
    sint32 dz;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x30;
            wp->turn_64      = 0x20;
            wp->ctl.target_C = func_80036294(wp->timer_C)->position;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &wp->ctl.target_C, wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A6 == 1)
            {
                Sound_call(0x10D, 0, 0);
            }
            dx = wp->position.x - wp->ctl.target_C.x;
            dz = wp->position.z - wp->ctl.target_C.z;
            if (dx * dx + dz * dz < 0x800)
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->turn_64      = 0;
                wp->routine_2++;
                Sce_flag_on(0x606);
            }
            break;
        case 2:
            break;
    }
}

void func_8010D730(ST03_OBJ *wp)
{
    sint32 temp_v1;
    uint8 temp_a1;

    temp_a1 = wp->routine_2;
    temp_v1 = temp_a1 & 0xFF;
    switch (temp_v1)
    {
        case 0:
            wp->routine_2 = temp_a1 + 1;
            wp->anim_AC   = 0;
        case 1:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
                return;
            }
            return;
        case 2:
            if (wp->value_A7 < 0)
            {
                wp->routine_2 = temp_a1 - 1;
                wp->anim_AC   = 0;
            }
            break;
    }
}

void func_8010D7C4(ST03_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            if (Player_work.target_184 == wp)
            {
                Sce_flag_on(0x604);
                Player_work.target_184 = NULL;
                wp->routine_3          = 0x10;
                wp->anim_AC            = 0;
                wp->routine_2++;
                wp->turn_64      = (uint32)STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
                wp->velocity.v.x = 0;
                wp->velocity.v.y = 0;
                wp->velocity.v.z = 0;
            }
            break;
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
            }
            break;
        case 2:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2--;
            }
            break;
    }
}

void func_8010D968(STAGE_OBJ *wp)
{
    D_80117140[wp->routine_0](wp);
}

void func_8010D9A4(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
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
    wp->scale.words[0]       = 0x01D701D7;
    wp->scale.words[1]       = 0x1D7;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 0;
    *(uint32 *)&ctl->timer_4 = 0;
    D_8011CAD8               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_8011CAD8, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E              = 0x80;
    wp->value_B0              = 0x80;
    wp->value_B2              = 0x80;
    wp->value_78              = (sint32)D_8011715C;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->data_10               = NULL;
    wp->routine_0             = 1;
    wp->routine_1             = 3;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8010DAE8(wp);
}

void func_8010DAE8(ST03_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    D_8011714C[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
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
    func_80051B68(wp, 3, -1, 0);
}

void func_8010DC34(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010DC54(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_8010DC74(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC        = 1;
            wp->velocity.v.x   = 0x3C;
            wp->turn_64        = 0x20;
            wp->ctl.target_C.x = -0xBBB;
            wp->ctl.target_C.y = -1;
            wp->ctl.target_C.z = 0x53B;
            // fall through
        case 1:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A6 == 1)
            {
                Sound_call(0x10C, 0, 0);
            }
            dx = wp->position.x - ctl->target_C.x;
            dz = wp->position.z - ctl->target_C.z;
            if (dx * dx + dz * dz < 0x800)
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->turn_64      = 0;
                wp->routine_2++;
                Sce_flag_on(0x606);
            }
            break;
        case 2:
            if (Moji_flag & 0x200000)
            {
                wp->routine_2++;
                wp->anim_AC = 8;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                wp->routine_2--;
                wp->anim_AC = 0;
            }
            break;
    }
}
