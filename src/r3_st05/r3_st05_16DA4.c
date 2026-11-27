#include "common.h"
#include "st05.h"

void func_80116DA4(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;
    STAGE_PL_VIEW *pl;

    ctl = &wp->ctl;
    pl  = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            wp->turn_64 = *(sint16 *)&wp->timer_C; // timer_C and value_D as one halfword
            // fall through
        case 1:
            ctl->timer_A =
                (ctl->timer_A + Muku(&wp->position, &pl->position, (wp->rotation.y + ctl->timer_A) & 0xFFF, wp->turn_64)) & 0xFFF;
            break;
    }
    if (wp->value_F & 2)
    {
        if (Moji_flag & 0x200000)
        {
            wp->anim_AC = 8;
        }
        else if (wp->value_A7 < 0)
        {
            wp->anim_AC = 0;
        }
    }
}

void func_80116E8C(ST05_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_80131820[wp->variant_3](wp);
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

void func_80116F7C(ST05_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_80117130(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_801171D0(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0)
            {
                if (func_8003A13C() == 0)
                {
                    func_80063BC8(&wp->position, 3, 0, func_80117300());
                    func_800322A8(wp, 8, 0);
                    wp->routine_1 = 0;
                    wp->routine_0++;
                }
            }
            break;
        case 3:
            if (D_800987B0[0] == 0)
            {
                func_80039E18();
                if (D_800987B5 == 0x48)
                {
                    Sce_flag_off(0x546);
                    Sce_flag_off(0x235);
                    Sce_flag_on(0x213);
                    wp->routine_0 = 0xA;
                }
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x40;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_80117130(ST05_ACTOR *wp)
{
    sint16 y;

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x01D701D7;
    wp->scale.words[1]   = 0x1D7;
    wp->scale.v.pad      = 0x4210;
    wp->data_78          = NULL;
    y                    = Obj_ceiling_height_get(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 16;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_80131824;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

sint32 func_801171D0(ST05_ACTOR *wp)
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
        D_80137F68.x = wp->value_180.x;
        D_80137F68.y = wp->value_180.y - 0x20;
        D_80137F68.z = wp->value_180.z;
        func_80039FAC(&D_80137F68, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

sint32 func_80117300(void)
{
    sint32 id;

    if (!Sce_flag_test(0x679))
    {
        if (Sce_flag_test(0x546))
        {
            id = 0x48;
        }
        else
        {
            id = 0x46;
        }
    }
    else
    {
        id = 0x4A;
    }
    return id;
}

void func_80117344(STAGE_OBJ *wp)
{
    D_80131830[wp->routine_0](wp);
}

void func_80117380(ST05_ACTOR *wp)
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
    wp->data_78               = D_8013184C;
    wp->data_10               = NULL;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_80117490(wp);
}

void func_80117490(ST05_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl2.value_2        = rand();
    D_8013183C[wp->routine_1](wp);
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

void func_801175C8(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801175E8(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_80117608(ST05_ACTOR *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0x11;
            break;
        case 1:
            if (wp->value_A7 < 0)
            {
                wp->anim_AC = 0;
                wp->routine_2++;
                wp->ctl2.timer_4 = (wp->ctl2.value_2 & 0x1F) + 0x10;
            }
            break;
        case 2:
            if (--wp->ctl2.timer_4 < 0)
            {
                wp->anim_AC = 0x11;
                wp->routine_2--;
            }
            break;
    }
}

void func_801176C0(ST05_ACTOR *wp)
{
    sint32 turn;

    switch (wp->routine_2)
    {
        case 0:
            if (wp->value_A7 >= 0)
            {
                break;
            }
            wp->routine_2++;
            wp->anim_AC = 0x10;
            wp->turn_64 = 0x1E;
            // fall through
        case 1:
            turn = Muku(&wp->position, D_80131858, wp->rotation.y, wp->turn_64);
            if ((sint16)turn != 0)
            {
                wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            }
            else
            {
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}

void func_8011777C(ST05_ACTOR *wp)
{
    sint32 dx;
    sint32 dz;
    STCOM_SVECTOR *target;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 0x12;
            wp->ctl2.timer_4 = 0x10;
            break;
        case 1:
            if (--wp->ctl2.timer_4 < 0)
            {
                wp->anim_AC      = 1;
                wp->velocity.v.x = 0x38;
                wp->turn_64      = 0x20;
                wp->routine_2++;
            }
            break;
        case 2:
            if (wp->value_A6 != 0)
            {
                Sound_call(0x111, 0, 0);
            }
            target         = &D_80131858[1];
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, target, wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
            dx = wp->position.x - target->x;
            dz = wp->position.z - target->z;
            if (dx * dx + dz * dz < 0x800)
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->routine_2++;
            }
            break;
    }
}

void func_801178EC(ST05_ACTOR *wp)
{
    STCOM_SVECTOR unused; // unused: reserves the frame's 8 extra bytes

    wp->scale.v.pad         = 0x4210;
    wp->rotation_prev       = wp->rotation;
    wp->position_fixed_prev = wp->position_fixed;
    wp->position_prev       = wp->position;
    D_80131868[wp->routine_0](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x100, 0);
    }
    func_80051B68(wp, 3, -1, 0);
}

void func_801179D4(ST05_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_78          = D_801318CC;
    wp->data_10          = D_801318C0;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->scale.words[0]   = 0x02000200;
    wp->rotation.y       = 0x400;
    wp->scale.words[1]   = 0x200;
    wp->velocity.v.x     = 0;
    wp->velocity.v.y     = 0;
    wp->velocity.v.z     = 0;
    wp->accel_4C.x       = 0;
    wp->accel_4C.y       = 0;
    wp->accel_4C.z       = 0;
    wp->rotation.x       = 0;
    wp->rotation.z       = 0;
    wp->value_D          = 0;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->value_E          = D_80131890[0].value_4;
    func_800322A8(wp, (&D_80131890[wp->value_D])->anim_0, 0);
    D_8013808C = wp;
    wp->routine_0++;
}

void func_80117AD8(ST05_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (wp->value_E++ == D_80131894[wp->value_D * 2])
    {
        switch (wp->value_D)
        {
            case 0:
                if (!(rand() & 3))
                {
                    wp->value_D = 1;
                    func_800322A8(wp, D_80131894[1 * 2 - 1], 0);
                }
                else if (!(rand() & 3))
                {
                    wp->value_D   = 4;
                    wp->routine_0 = 2;
                    func_800322A8(wp, D_80131894[wp->value_D * 2 - 1], 0);
                }
                else
                {
                    Sound_call2(0x16F, &wp->position);
                }
                break;
            case 1:
                wp->value_D = 2;
                func_800322A8(wp, D_80131894[2 * 2 - 1], 0);
                break;
            case 2:
                if (!(rand() & 1))
                {
                    wp->value_D = 3;
                }
                func_800322A8(wp, D_80131894[wp->value_D * 2 - 1], 0);
                break;
            case 3:
                wp->value_D = 0;
                func_800322A8(wp, D_80131894[0 * 2 - 1], 0);
                Sound_call2(0x16F, &wp->position);
                break;
        }
        wp->value_E = 0;
    }
    else
    {
        if (wp->value_D == 2 && wp->value_E == 8)
        {
            Sound_call2(0x171, &wp->position);
        }
        func_80032488(wp);
    }
    if (pl->target_184 == wp)
    {
        pl->target_184 = NULL;
        wp->value_D    = 0;
        func_800322A8(wp, D_80131894[0 * 2 - 1], 0);
        if (Sce_flag_test(0x640))
        {
            wp->routine_0 = 4;
            wp->routine_3 = 0;
        }
        else
        {
            wp->routine_0 = 3;
            pl->flags_0 ^= 2;
        }
        wp->routine_1 = 0;
        pl->flags_bd |= 0x20;
    }
}

void func_80117CFC(ST05_ACTOR *wp)
{
    func_80032488(wp);
    wp->value_E++;
    wp->velocity.v.y += wp->accel_4C.y;
    wp->position.y += wp->velocity.v.y;
    if (wp->value_E == 8)
    {
        Sound_call2(0x171, &wp->position);
    }
    if (wp->value_E == D_80131894[wp->value_D * 2])
    {
        wp->value_D = 0;
        wp->value_E = 0;
        func_800322A8(wp, D_80131894[wp->value_D * 2 - 1], 0);
        wp->routine_0--;
    }
    if (wp->value_E == 3)
    {
        wp->velocity.v.y = -0x24;
        wp->accel_4C.y   = 8;
    }
    else if (wp->value_E == 0xB)
    {
        wp->velocity.v.y = 0;
        wp->accel_4C.y   = 0;
        wp->position.y   = Obj_ceiling_height_get(wp);
    }
}

void func_80117DFC(ST05_ACTOR *wp)
{
    STCOM_FIXED_VECTOR cam;
    STCOM_PL_WORK *pl;

    func_80032488(wp);
    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            Scene_work.reserved00[1] = 0xFF;
            Scene_work.reserved00[0] = 1;
            pl->flags_0 &= ~2;
            cam.x = wp->value_180.x;
            cam.y = wp->value_180.y - 0x20;
            cam.z = wp->value_180.z;
            func_80039FAC(&cam, 0x100, 0x400, D_800A396C + 0x40);
            wp->routine_1++;
            break;
        case 1:
            if (func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0xB);
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1++;
                func_80039E18();
            }
            break;
        case 3:
            if (func_8003A13C() == 0)
            {
                D_800A395A = D_80138084;
                D_800A395B = D_80138034;
                D_800A3988 = D_800A3964;
                STAGE_PL.flags_bd &= ~0x20;
                pl->flags_0 |= 2;
                wp->routine_0       = 1;
                wp->value_E         = D_80131890[wp->value_D].value_4;
                STAGE_SCENE_BYTE(1) = 0;
                STAGE_SCENE_BYTE(0) = 0;
            }
            break;
    }
}

void func_80117FC4(STAGE_OBJ *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                STAGE_PL.routine_0 = 3;
                STAGE_PL.routine_1 = 0;
                STAGE_PL.value_448 = 0;
                Sound_fade_start(0x10);
                Sound_work.volume_6 = 0x64;
                wp->routine_3++;
            }
            break;
        case 1:
            if (Sound_fade_flags == 0)
            {
                Sound_call(0xB, 0, 0);
                wp->routine_3 = 0;
                wp->routine_1++;
            }
            break;
    }
}

void func_80118090(ST05_ACTOR *wp)
{
    STCOM_FIXED_VECTOR cam;
    sint32 angle;
    sint32 back;

    Scene_work.reserved00[1] = 0xFF;
    Scene_work.reserved00[0] = 1;
    cam.x                    = (wp->value_180.x + STCOM_PLAYER_WORK_PTR->position.x) >> 1;
    cam.y                    = ((wp->value_180.y + STCOM_PLAYER_WORK_PTR->position.y) >> 1) - 0x60;
    cam.z                    = (wp->value_180.z + STCOM_PLAYER_WORK_PTR->position.z) >> 1;
    angle                    = Angle_xz_svector(&Player_work.position, &wp->position);
    // One-pass block preserves retail's register allocation and scheduling.
    do
    {
        back = Angle_xz_svector(&wp->position, &Player_work.position);
        func_80039FAC(&cam, 0x180, angle - 0x500, D_800A396C);
    } while (0);
    wp->turn_B4 = Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x80);
    func_800322A8(wp, 0x14, 0);
    if ((uint32)func_80118D74(&Player_work.position, &wp->position) < 0x80)
    {
        *(uint32 *)&wp->ctl.flags_0 = 1;
        D_801380AC                  = -(rcos(back) * 0xA8) >> 10;
        D_80138098                  = -(rsin(back) * 0xA8) >> 10;
    }
    else
    {
        *(uint32 *)&wp->ctl.flags_0 = 0;
    }
    wp->routine_1++;
}

void func_8011822C(ST05_ACTOR *wp)
{
    ST05_PL_VIEW *pl;
    sint32 angle;

    pl = &ST05_PL;
    if (func_8003A13C() == 0 && (uint32)func_80118D74(&pl->position, &wp->position) >= 0x80)
    {
        wp->routine_1++;
        pl->value_448 = 0x82;
        wp->value_F   = 0;
        func_800322A8(wp, D_80131890[0].anim_0, 0);
        angle          = Angle_xz_svector(&pl->position, &wp->position);
        pl->angle_442  = angle;
        wp->rotation.y = angle - 0x800;
        return;
    }
    if (func_8003A13C() != 0)
    {
        if ((ST05_ABS(wp->rotation.y - Angle_xz_svector(&wp->position, &pl->position)) & 0xFFF) < 0x83)
        {
            goto snap;
        }
        wp->rotation.y += wp->turn_B4;
    }
    else
    {
    snap:
        wp->rotation.y = Angle_xz_svector(&wp->position, &pl->position);
    }
    if ((uint32)func_80118D74(&pl->position, &wp->position) < 0x80)
    {
        pl->push_428.x += D_80138098 << 8;
        pl->push_428.z += D_801380AC << 8;
        func_80030150(&pl->push_428, &pl->push_438);
        pl->value_448 = 0xD;
        pl->angle_442 = Angle_xz_svector(&pl->position, &wp->position);
    }
}

void func_801183FC(STAGE_OBJ *wp)
{
    sint8 temp_v0;

    temp_v0          = (uint8)wp->u_E.b.byte_F + 1;
    wp->u_E.b.byte_F = temp_v0;
    if (temp_v0 == 8)
    {
        MojiTaskExec2(0, 4);
        wp->u_C.b.byte_C = 0;
        wp->u_E.b.byte_E = 0;
        wp->u_E.b.byte_F = 0;
        wp->routine_1++;
    }
}

void func_80118460(ST05_ACTOR *wp)
{
    if ((uint8)wp->value_F++ < 0xAA)
    {
        return;
    }
    wp->value_E++;
    switch (wp->timer_C)
    {
        case 0:
            wp->velocity.v.y += wp->accel_4C.y;
            wp->position.y += wp->velocity.v.y;
            if (wp->value_E == 0x13)
            {
                wp->value_D = 2;
                wp->timer_C = 1;
                wp->value_E = 0;
                func_800322A8(wp, D_80131890[wp->value_D].anim_0, 0);
            }
            if (wp->value_E == 3)
            {
                wp->velocity.v.y = -0x24;
                wp->accel_4C.y   = 8;
            }
            else if (wp->value_E == 0xB)
            {
                wp->velocity.v.y = 0;
                wp->accel_4C.y   = 0;
                wp->position.y   = Obj_ceiling_height_get(wp);
            }
            break;
        case 1:
            if (wp->value_E == 0xC)
            {
                ST05_PL.value_448 = 0x83;
                wp->timer_C = wp->value_D = 2;
                wp->value_E               = 0;
                func_800322A8(wp, D_80131890[wp->value_D].anim_0, 0);
            }
            break;
        case 2:
            if (wp->value_E == 0xC)
            {
                wp->timer_C = wp->value_D = 3;
                wp->value_E               = 0;
                func_800322A8(wp, D_80131890[wp->value_D].anim_0, 0);
            }
            break;
        case 3:
            if (wp->value_E == 6)
            {
                wp->value_D = 0;
                wp->timer_C = 4;
                wp->value_E = 0;
                func_800322A8(wp, D_80131890[wp->value_D].anim_0, 0);
                wp->routine_1++;
            }
            break;
    }
}

void func_80118640(STAGE_OBJ *wp)
{
    if (!(Moji_flag & 0x08000000))
    {
        wp->routine_1++;
        Sce_flag_on(0x641);
    }
}

void func_80118684(STAGE_OBJ *wp)
{
    if (!func_8003A13C())
    {
        STAGE_PL.flags_bd &= ~0x20;
        wp->routine_0       = 1;
        wp->u_E.b.byte_E    = D_80131890[wp->u_C.b.byte_D].value_4;
        STAGE_SCENE_BYTE(1) = 0;
        STAGE_SCENE_BYTE(0) = 0;
    }
}

void func_801186FC(STAGE_OBJ *wp)
{
    func_80032488(wp);
    D_801318D8[wp->routine_1](wp);
}

void func_80118748(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        wp->position_fixed.v.z = 0x105F0000;
        wp->position_fixed.v.x = 0x07900000;
        func_80030150(&wp->position_fixed.v, &wp->position);
        wp->rotation.y   = 0x800;
        wp->u_E.b.byte_F = 0;
        wp->flags_0 |= 2;
        wp->routine_1++;
        func_800322A8(wp, D_80131890[0].anim_0, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801187DC(ST05_ACTOR *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            func_800322A8(wp, 0x14, 0);
            wp->turn_B4 = -0x80;
            wp->routine_1++;
            break;
        case 1:
            func_80032488(wp);
            wp->rotation.y += wp->turn_B4;
            if (wp->rotation.y <= 0)
            {
                wp->rotation.y   = 0;
                wp->velocity.v.z = -0x719;
                wp->routine_1++;
            }
            break;
        case 2:
            func_80032488(wp);
            wp->position_fixed.z += wp->velocity.v.z << 8;
            func_80030150(&wp->position_fixed, &wp->position);
            break;
    }
}

void func_801188C0(ST05_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    ST05_SPARK *ep;
    sint32 hit;

    pl = &Player_work;
    switch (wp->value_F)
    {
        case 0:
            Sce_flag_on(0x42);
            func_800322A8(wp, 0x16, 0);
            wp->velocity.v.z = -(rcos(Player_work.rotation.y) << 10) >> 12;
            wp->velocity.v.x = -(rsin(Player_work.rotation.y) << 10) >> 12;
            wp->velocity.v.y = D_801318B8[0];
            wp->accel_4C.y   = 0x80;
            wp->value_E      = 0;
            wp->value_F++;
            STAGE_PL.flags_bd |= 0x20;
            Sound_fade_start(0x10);
            func_8001E3F0(3);
            Sound_work.volume_6 = 100;
            break;
        case 1:
            if (Sound_fade_flags == 0)
            {
                Sound_call(0xB, 0, 0);
                wp->value_F++;
            }
            break;
    }
    if (wp->value_F != 0)
    {
        wp->rotation.x += 0x200;
        wp->rotation.y += 0x100;
        func_80032538(wp);
        Model_pose_unpack(wp);
        ST05_SP_TILT->x = wp->rotation.x;
        Model_parts_mtx_set_y(wp);
        wp->velocity.v.y += wp->accel_4C.y;
        wp->position_fixed.x += wp->velocity.v.x << 12;
        wp->position_fixed.z += wp->velocity.v.z << 12;
        wp->position_fixed.y += wp->velocity.v.y << 12;
        func_80030150(&wp->position_fixed, &wp->position);
    }
    hit = Obj_map_push_out(wp);
    if (hit != 0)
    {
        Sound_call2(0x129, &wp->position);
        if (hit & 0x1000)
        {
            if (wp->value_E >= 2)
            {
                wp->value_E++;
                wp->velocity.v.x = 0;
                wp->velocity.v.y = 0;
                wp->velocity.v.z = 0;
                wp->accel_4C.x   = 0;
                wp->accel_4C.y   = 0;
                wp->accel_4C.z   = 0;
                wp->rotation.x   = 0;
                return;
            }
            wp->value_E++;
            wp->velocity.v.y = D_801318B8[wp->value_E];
            wp->velocity.v.x = (wp->velocity.v.x << 10) >> 12;
            wp->velocity.v.z = (wp->velocity.v.z << 10) >> 12;
            ep               = (ST05_SPARK *)func_80031618();
            if (ep != NULL)
            {
                ep->flags_0   = 1;
                ep->kind_2    = 0x83;
                ep->variant_3 = 0;
                ep->x_1C      = wp->position.x;
                ep->y_1E      = wp->position.y;
                ep->z_20      = wp->position.z;
            }
        }
        Wall_reflect_spd(&wp->velocity.v, hit);
    }
    if (wp->value_E >= 3 && wp->value_F >= 2)
    {
        Sce_flag_on(0x642);
        pl->flags_bd &= ~0x20;
    }
}

void func_80118BD0(ST05_ACTOR *wp)
{
    STCOM_EFFECT *fx;

    if (wp->value_F == 0x46)
    {
        wp->turn_B4 = 0x40;
    }
    if (wp->rotation.y > 0x400)
    {
        wp->turn_B4 = 0;
    }
    if (wp->value_F == 0)
    {
        wp->position_fixed.x = 0x5430000;
        wp->position_fixed.y = 0xFFFF0000;
        wp->position_fixed.z = 0x11A00000;
        func_80030150(&wp->position_fixed, &wp->position);
        wp->rotation.y = 0;
        wp->turn_B4    = 0;
        wp->value_F++;
    }
    else if (wp->value_F >= 0xA)
    {
        wp->rotation.y += wp->turn_B4;
        Obj_pos_set(wp, 0x500, 0, 0);
        fx = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0         = 1;
            fx->kind_2          = 0x83;
            fx->variant_3       = 0;
            fx->sprite.pos_8[0] = wp->position.x + (rand() & 0x1F) - 0xF;
            fx->sprite.pos_8[1] = wp->position.y - (rand() & 0xF);
            fx->sprite.pos_8[2] = wp->position.z + (rand() & 0x1F) - 0xF;
        }
    }
    func_80032488(wp);
    wp->value_F++;
}

void func_80118D1C(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        func_800322A8(wp, 0x11, 0);
        wp->routine_1++;
        return;
    }
    func_80032488(wp);
}

sint32 func_80118D74(STCOM_SVECTOR *a, STCOM_SVECTOR *b)
{
    sint32 dx;
    sint32 dy;
    sint32 dz;

    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;
    return SquareRoot0(dx * dx + dy * dy + dz * dz);
}

void func_80118DE0(ST05_BOAT *wp)
{
    ST05_BOAT_CTL *ctl;
    STCOM_SVECTOR *tilt;
    sint32 mask;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_2        = rand();
    ctl                     = &wp->ctl;
    D_801318F4[wp->routine_0](wp, ctl);
    if ((wp->ctl.flags_0 & 0x200) || wp->anim_AC == 1)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
    }
    else
    {
        tilt = ST05_SP_TILT;
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        tilt->x = wp->rotation.x;
        tilt->z = (wp->rotation.x == 0) ? wp->rotation.z : 0;
        Model_parts_mtx_set_y(wp);
    }
    ctl->ground_1C = 0;
    ctl->hit_18    = Obj_map_push_out(wp);
    if (!(ctl->hit_18 & 0x1000) && wp->position.y == (sint16)Obj_ceiling_height_get(wp))
    {
        ctl->ground_1C = 1;
    }
    mask = (ctl->flags_0 >> 2) & 0x80;
    func_800341BC(&wp->value_180, 0xC0, 0, 0x8000, wp->value_1, &ctl->hit_20, ctl->value_10 | 0x5880000, 0x800000, mask);
    ctl->hit_20 = 0;
}

void func_80118FF8(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    STCOM_SVECTOR *start;
    sint16 life;

    start          = &D_80131910[wp->index_C];
    ctl->flags_0   = 0xA;
    ctl->timer_4   = 0;
    ctl->timer_6   = 0;
    ctl->count_8   = 0;
    ctl->roll_C    = -1;
    ctl->value_10  = D_80098844[wp->kind_2]->life_A[0];
    ctl->hit_20    = 0;
    ctl->rise_14   = 8;
    ctl->value_24  = 0;
    ctl->sink_12   = 8;
    ctl->hit_18    = 0;
    ctl->ground_1C = 0;
    Track_reset(ctl->track_28, 0xB, 0);
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->rotation.x       = 0;
    wp->rotation.y       = start->pad;
    wp->rotation.z       = 0;
    wp->position.x       = start->x;
    wp->position.y       = start->y;
    wp->position.z       = start->z;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->anim_prev_AD     = 0xFF;
    wp->turn_64.w        = 0;
    wp->anim_AC          = 0;
    life                 = D_80098844[wp->kind_2]->life_8 * 16;
    wp->data_78          = D_80131920;
    wp->routine_0        = 1;
    wp->routine_1        = 0;
    wp->routine_2        = 0;
    wp->life_6E          = life;
    wp->life_max_B0      = life;
    wp->life_prev_B2     = life;
}

void func_80119188(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    if (ctl->flags_0 & 2)
    {
        func_801193C8(wp, ctl);
    }
    func_8011948C(wp, ctl);
    if (!(ctl->flags_0 & 0x200))
    {
        func_80119718(wp, ctl);
        func_80119A90(wp, ctl);
        func_80119BE0(wp, ctl);
    }
    switch (wp->anim_AC)
    {
        case 0:
            if (ctl->flags_0 & 4)
            {
                wp->anim_AC = 1;
            }
            if (ctl->flags_0 & 0x400)
            {
                wp->anim_AC = 2;
            }
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                if (ctl->flags_0 & 4)
                {
                    wp->anim_AC      = 1;
                    wp->anim_prev_AD = 0xFF;
                }
                else
                {
                    wp->anim_AC = 0;
                }
            }
            if (ctl->flags_0 & 0x400)
            {
                wp->anim_AC = 2;
            }
            break;
        case 2:
            if (wp->value_A7 == -1)
            {
                wp->anim_AC = 3;
            }
            break;
    }
    D_80131900[wp->routine_1](wp, ctl);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                if (ctl->flags_0 & 0x200)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 1;
                }
                break;
            case 1:
                if (ctl->flags_0 & 0x200)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 2;
                }
                break;
            case 2:
                if (ctl->flags_0 & 0x200)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 1;
                }
                break;
            case 3:
                wp->routine_0 = 2;
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
}

void func_801193C8(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    uint32 hit;
    sint32 damage;

    hit    = ctl->hit_20;
    damage = hit & 0xFFFFFF;
    if (damage != 0)
    {
        if (hit & 0x18000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                ctl->flags_0 = (ctl->flags_0 & ~0xE2) | 0x201;
            }
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
        ctl->flags_0 |= 4;
    }
    else
    {
        ctl->flags_0 &= ~4;
    }
}

void func_8011948C(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    if (ctl->flags_0 & 0x10)
    {
        if (ctl->timer_6 > 0)
        {
            ctl->timer_6--;
            return;
        }
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 8)
    {
        if (func_8011953C(wp->position.x, wp->position.z, ((wp->rotation.y + 0x200) & 0xFFF) / 0x400) != 0)
        {
            ctl->flags_0 &= ~8;
        }
    }
}

sint32 func_8011953C(sint16 x, sint16 z, sint16 side)
{
    if (x < 0x200)
    {
        switch (side)
        {
            case 0:
                if (x < -0x848 || z < 0x1000)
                {
                    return 1;
                }
                break;
            case 1:
                if (x < -0x848 || z < 0x1000 || z > 0x20B4)
                {
                    return 1;
                }
                break;
            case 2:
                if (x < -0x848 || z > 0x20B4)
                {
                    return 1;
                }
                break;
            case 3:
                if (z < 0x1000 || z > 0x20B4)
                {
                    return 1;
                }
                break;
        }
    }
    else if (z > 0x1000)
    {
        switch (side)
        {
            case 0:
                if (x > 0x1A00)
                {
                    return 1;
                }
                break;
            case 1:
                if (z > 0x20B4)
                {
                    return 1;
                }
                break;
            case 2:
                if (x > 0x1A00 || z > 0x20B4)
                {
                    return 1;
                }
                break;
            case 3:
                if (x > 0x1A00 || z > 0x20B4)
                {
                    return 1;
                }
                break;
        }
    }
    else
    {
        switch (side)
        {
            case 0:
                if (x < 0x200 || x > 0x1A00 || z < -0x200)
                {
                    return 1;
                }
                break;
            case 1:
                if (z < -0x200)
                {
                    return 1;
                }
                break;
            case 2:
                if (x < 0x200 || x > 0x1A00)
                {
                    return 1;
                }
                break;
            case 3:
                if (x > 0x1A00 || z < -0x200)
                {
                    return 1;
                }
                break;
        }
    }
    return 0;
}

void func_80119718(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    if (wp->anim_AC == 1)
    {
        ctl->flags_0 &= ~0x80;
    }
    if (ctl->flags_0 & 0x80)
    {
        if (ctl->flags_0 & 0x100)
        {
            if (!(ctl->count_8 & 3))
            {
                func_8011986C(wp, ctl);
            }
            ctl->count_8++;
        }
        else if (wp->rotation.x >= 0x200)
        {
            wp->rotation.x = 0x200;
            ctl->flags_0 |= 0x100;
        }
        else
        {
            wp->rotation.x += 0x20;
        }
    }
    else
    {
        ctl->count_8 = 0;
        ctl->flags_0 &= ~0x100;
        if (wp->rotation.x > 0)
        {
            wp->rotation.x -= 0x20;
        }
    }
    if (wp->dist_80 < 0x90000 && !(ctl->flags_0 & 0x800))
    {
        ctl->flags_0 |= 0x800;
        Sound_call2(0x150, &wp->position);
    }
    if (wp->dist_80 > 0x240000)
    {
        ctl->flags_0 &= ~0x800;
    }
}

void func_8011986C(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    STCOM_FIXED_VECTOR dir;
    STCOM_SVECTOR step;
    STCOM_FIXED_VECTOR ofs;
    ST05_SPRAY *fx;
    sint32 spawned;

    spawned = 0;
    func_80030058(&dir, wp->rotation.y, 0x600, 0, 0);
    func_80030150(&dir, &step);
    fx = (ST05_SPRAY *)Open_SHL_WORK();
    if (fx != NULL)
    {
        fx->flags_0 = 3;
        fx->kind_2  = 1;
        fx->value_4 = 0;
        fx->type_F  = 0x24;
        func_80030058(&ofs, wp->rotation.y, 0xC80, 0x1900, 0x480);
        fx->position_fixed = ofs;
        fx->position_fixed.x += wp->position_fixed.x;
        fx->position_fixed.y += wp->position_fixed.y;
        fx->position_fixed.z += wp->position_fixed.z;
        func_80030150(&fx->position_fixed, &fx->position);
        fx->velocity.x   = step.x << 8;
        fx->velocity.y   = 0x6000;
        fx->velocity.z   = step.z << 8;
        fx->velocity.pad = 0;
        fx->accel.z      = 0;
        fx->accel.y      = 0;
        fx->accel.x      = 0;
        spawned          = 1;
    }
    fx = (ST05_SPRAY *)Open_SHL_WORK();
    if (fx != NULL)
    {
        fx->flags_0 = 3;
        fx->kind_2  = 1;
        fx->value_4 = 0;
        fx->type_F  = 0x24;
        func_80030058(&ofs, wp->rotation.y, 0xC80, 0x1900, -0x480);
        fx->position_fixed = ofs;
        fx->position_fixed.x += wp->position_fixed.x;
        fx->position_fixed.y += wp->position_fixed.y;
        fx->position_fixed.z += wp->position_fixed.z;
        func_80030150(&fx->position_fixed, &fx->position);
        fx->velocity.x   = step.x << 8;
        fx->velocity.y   = 0x6000;
        fx->velocity.z   = step.z << 8;
        fx->velocity.pad = 0;
        fx->accel.z      = 0;
        fx->accel.y      = 0;
        fx->accel.x      = 0;
        spawned          = 1;
    }
    if (spawned)
    {
        Sound_call2(0xD0, &fx->position);
    }
}

void func_80119A90(ST05_BOAT *wp, ST05_BOAT_CTL *ctl)
{
    if (ctl->flags_0 & 0x40)
    {
        wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
        if (wp->rotation.z >= -0x7F)
        {
            wp->rotation.z -= 8;
        }
        ctl->roll_C = -1;
    }
    else if (ctl->flags_0 & 0x20)
    {
        wp->rotation.y = (wp->rotation.y - 0x20) & 0xFFF;
        if (wp->rotation.z < 0x80)
        {
            wp->rotation.z += 8;
        }
        ctl->roll_C = -1;
    }
    else if (ctl->roll_C == -1)
    {
        if (wp->rotation.z != 0)
        {
            if (wp->rotation.z > 0)
            {
                wp->rotation.z -= 8;
            }
            else
            {
                wp->rotation.z += 8;
            }
            if (wp->rotation.z != 0)
            {
                return;
            }
        }
        ctl->roll_C = (ctl->random_2 >> 4) & 3;
    }
    else
    {
        wp->rotation.z = D_8013192C[ctl->roll_C % 36];
        ctl->roll_C    = (ctl->roll_C + 1) & 0x7FFF;
    }
}
