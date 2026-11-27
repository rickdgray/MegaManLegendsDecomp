#include "common.h"
#include "st06.h"

void func_8011335C(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_801134B8(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_80113548(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x13);
                wp->anim_AC = 8;
                wp->routine_0++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                func_80039E18();
                wp->routine_0++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x80;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801134B8(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->data_10          = D_8012540C;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->anim_AC          = 0;
    wp->anim_prev_AD     = 0xFF;
}

sint32 func_80113548(ST06_ACTOR *wp)
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
        pl->flags_bd |= 0x80;
        D_8012BA78.x = wp->value_180.x;
        D_8012BA78.y = wp->value_180.y - 0x20;
        D_8012BA78.z = wp->value_180.z;
        func_80039FAC(&D_8012BA78, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void func_80113678(ST06_ACTOR *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    D_80125438[wp->variant_3](wp);
    if (wp->routine_1 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_8011370C(STAGE_OBJ *wp)
{
    D_80125418[wp->routine_0](wp);
}

void func_80113748(STAGE_OBJ *wp)
{
    D_80125424[wp->routine_0](wp);
}

void func_80113784(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_10               = D_80125440;
    wp->scale.words[0]        = 0x1D701D7;
    wp->scale.words[1]        = 0x1D7;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->value_78              = 0;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->position_fixed.x      = wp->position.x << 16;
    wp->position_fixed.y      = wp->position.y << 16;
    wp->position_fixed.z      = wp->position.z << 16;
    wp->scale.v.pad           = 0x4210;
    wp->position_fixed_prev.x = wp->position_fixed.x;
    wp->position_fixed_prev.y = wp->position_fixed.y;
    wp->position_fixed_prev.z = wp->position_fixed.z;
    wp->position_prev.x       = wp->position.x;
    wp->position_prev.y       = wp->position.y;
    wp->position_prev.z       = wp->position.z;
    wp->rotation_prev.x       = wp->rotation.x;
    wp->rotation_prev.y       = wp->rotation.y;
    wp->rotation_prev.z       = wp->rotation.z;
    wp->velocity.v.z          = 0;
    wp->accel_4C.x            = 0;
    wp->accel_4C.y            = 0;
    wp->accel_4C.z            = 0;
    wp->routine_1             = 0;
    wp->turn_64               = 0x80;
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_801138A0(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_FIXED_VECTOR cam;

    pl = &Player_work;
    if (Player_work.target_184 == wp)
    {
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x80;
        cam.x = wp->value_180.x;
        cam.y = wp->value_180.y - 0x20;
        cam.z = wp->value_180.z;
        func_80039FAC(&cam, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        func_800322A8(wp, 1, 0);
        D_8012BA88    = Angle_xz_svector(&wp->position, &pl->position);
        wp->routine_0 = 2;
        return;
    }
    if (wp->value_D == 0)
    {
        func_80032488(wp);
        return;
    }
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
}

void func_801139B8(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->u_E.b.byte_E, 0);
        wp->u_C.b.byte_D = 0;
    }
}

void func_80113A1C(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_10               = D_80125440;
    wp->scale.words[0]        = 0x1D701D7;
    wp->scale.words[1]        = 0x1D7;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->value_78              = 0;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->position_fixed.x      = wp->position.x << 16;
    wp->position_fixed.y      = wp->position.y << 16;
    wp->position_fixed.z      = wp->position.z << 16;
    wp->scale.v.pad           = 0x4210;
    wp->position_fixed_prev.x = wp->position_fixed.x;
    wp->position_fixed_prev.y = wp->position_fixed.y;
    wp->position_fixed_prev.z = wp->position_fixed.z;
    wp->position_prev.x       = wp->position.x;
    wp->position_prev.y       = wp->position.y;
    wp->position_prev.z       = wp->position.z;
    wp->rotation_prev.x       = wp->rotation.x;
    wp->rotation_prev.y       = wp->rotation.y;
    wp->rotation_prev.z       = wp->rotation.z;
    wp->velocity.v.z          = 0;
    wp->accel_4C.x            = 0;
    wp->accel_4C.y            = 0;
    wp->accel_4C.z            = 0;
    wp->turn_64               = 0x80;
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_80113B34(ST06_ACTOR *wp)
{
    sint16 turn;

    turn           = Angle_diff_clamp(D_8012BA88, wp->rotation.y, wp->turn_64);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_80063BC8(&wp->position, 1, 0, wp->timer_C);
        func_800322A8(wp, 8, 0);
        wp->routine_1 = 1;
        wp->routine_0++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80113BDC(STAGE_OBJ *wp)
{
    if ((sint8)*D_800987B0 == 0)
    {
        func_80039E18();
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
        return;
    }
    func_80032488(wp);
}

void func_80113C40(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    turn           = Angle_diff_clamp(wp->rotation_prev.y, wp->rotation.y, wp->turn_64);
    pl             = &Player_work;
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_1 = 0;
        pl->flags_bd &= ~0x80;
        pl->flags_0 |= 2;
        wp->routine_0 = 1;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80113CF4(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8012544C[wp->routine_0](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_2 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_2++;
    }
}

void func_80113DE4(ST06_ACTOR *wp)
{
    STCOM_FIXED_VECTOR unused; // retail's frame has room for it

    wp->turn_64 = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
    wp->scale.v.pad           = 0x4210;
    wp->position.y            = Obj_ceiling_height_get(wp);
    wp->position_fixed.y      = wp->position.y << 16;
    wp->value_78              = D_80125458;
    wp->value_6E              = 0;
    wp->value_B0              = 0;
    wp->value_B2              = 0;
    wp->data_10               = NULL;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->velocity.words[0]     = 0;
    wp->velocity.words[1]     = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 2, 0);
}
