#include "common.h"
#include "st06.h"

void func_8011227C(ST06_ACTOR *wp)
{
    sint16 turn;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC = 0;
            wp->turn_64 = 0x20;
            // fall through
        case 1:
            turn            = Muku(&wp->position, &D_801253AC, (wp->rotation.y + wp->ctl.timer_A) & 0xFFF, wp->turn_64);
            wp->ctl.timer_A = (wp->ctl.timer_A + turn) & 0xFFF;
            if (turn == 0)
            {
                wp->anim_AC = 0;
                wp->routine_2++;
                Sce_flag_on(0x609);
            }
            break;
        case 2:
            break;
    }
}

void func_8011232C(ST06_ACTOR *wp)
{
    sint32 dx;
    sint32 dz;

    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2++;
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x2C;
            wp->turn_64      = D_8012539C[wp->value_D].pad;
            break;
        case 1:
            if (wp->value_A6 != 0)
            {
                Sound_call(0xD7, 0, 0);
            }
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &D_8012539C[wp->value_D], wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, wp->velocity.v.z);
            dx = wp->position.x - D_8012539C[wp->value_D].x;
            dz = wp->position.z - D_8012539C[wp->value_D].z;
            if (dx * dx + dz * dz < D_801253B4[wp->value_D])
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->routine_2++;
                Sce_flag_on(0x608);
            }
            break;
        case 2:
            break;
    }
}

sint32 func_80112488(ST06_ACTOR *wp)
{
    if (STAGE_PL.target_184 == wp)
    {
        Sce_flag_on(0x605);
        Player_work.target_184 = NULL;
    }
    return 1;
}

void func_801124BC(ST06_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_801253BC[wp->variant_3](wp);
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

void func_801125AC(ST06_ACTOR *wp)
{
    ST06_SCENE *scene;
    STCOM_PL_WORK *pl;
    sint16 turn;

    scene = (ST06_SCENE *)&Scene_work;
    pl    = &Player_work;
    if (scene->routine_0 == 0)
    {
        wp->routine_0 = 0xA;
    }
    switch (wp->routine_0)
    {
        case 0:
            func_801129A4(wp);
            wp->routine_0++;
            break;
        case 1:
            if (STAGE_GAME.value_1 == 2)
            {
                MojiTaskExec2(0, 0x29);
                func_800322A8(wp, 8, 0);
                wp->routine_0++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                Sce_event_next();
                wp->routine_0++;
            }
            break;
        case 3:
            if (scene->flag_9 == 1)
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64)) & 0xFFF;
            }
            else
            {
                wp->routine_0++;
            }
            break;
        case 4:
            if (scene->flag_9 == 3)
            {
                wp->position.x = 0xA0;
                wp->position.z = -0x12C;
                wp->rotation.y = 0x700;
                wp->routine_0++;
            }
            break;
        case 5:
            if (scene->flag_9 == 5)
            {
                wp->routine_0++;
            }
            break;
        case 6:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x30);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x8000000))
            {
                if (!(Moji_flag & 0xFF))
                {
                    Sce_event_next();
                    wp->routine_0 = 0xA;
                }
                else
                {
                    turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
                    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
                    if (turn == 0 && func_8003A13C() == 0)
                    {
                        MojiTaskExec2(0, 0x31);
                        func_800322A8(wp, 8, 0);
                        wp->routine_1 = 0;
                        wp->routine_0++;
                    }
                }
            }
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_0 = 6;
            }
            break;
        case 10:
            wp->variant_3 = 1;
            wp->routine_0 = 1;
            wp->routine_1 = 0;
            break;
    }
}

void func_8011283C(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_801129A4(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_80112A60(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x49);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
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
                pl->flags_bd &= ~0x40;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
            }
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_801129A4(ST06_ACTOR *wp)
{
    wp->rotation.x   = 0;
    wp->rotation.y   = 0x12C;
    wp->rotation.z   = 0;
    wp->turn_64      = 0x80;
    wp->velocity.v.z = 0;
    wp->velocity.v.y = 0;
    wp->velocity.v.x = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->data_10          = D_801253C4;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

sint32 func_80112A60(ST06_ACTOR *wp)
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
        D_8012BA60.x = wp->value_180.x;
        D_8012BA60.y = wp->value_180.y - 0x20;
        D_8012BA60.z = wp->value_180.z;
        func_80039FAC(&D_8012BA60, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void func_80112B90(ST06_ACTOR *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    D_801253F0[wp->variant_3](wp);
    if (wp->routine_1 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_80112C24(STAGE_OBJ *wp)
{
    D_801253D0[wp->routine_0](wp);
}

void func_80112C60(STAGE_OBJ *wp)
{
    D_801253DC[wp->routine_0](wp);
}

void func_80112C9C(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_10               = D_801253F8;
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
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

void func_80112DB8(ST06_ACTOR *wp)
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
        D_8012BA70    = Angle_xz_svector(&wp->position, &pl->position);
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

void func_80112ED0(STAGE_OBJ *wp)
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

void func_80112F34(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_10               = D_801253F8;
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
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

void func_8011304C(ST06_ACTOR *wp)
{
    sint16 turn;

    turn           = Angle_diff_clamp(D_8012BA70, wp->rotation.y, wp->turn_64);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_80063BC8(&wp->position, 3, 0, wp->timer_C);
        func_800322A8(wp, 8, 0);
        wp->routine_1 = 1;
        wp->routine_0++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_801130F4(STAGE_OBJ *wp)
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

void func_80113158(ST06_ACTOR *wp)
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

void func_8011320C(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_80125404[wp->variant_3](wp);
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
        Model_Shadow_Trans(wp, 0x50, 0x200, 0);
    }
    wp->anim_prev_AD = wp->anim_AC;
}

void func_80113310(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_801134B8(wp);
        wp->routine_0++;
    }
}

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

void func_80113EA0(ST06_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                MojiTaskExec2(0, 0x12);
                wp->routine_1++;
                Sound_call(0x16F, 0, 0);
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                wp->value_44.half[0] = 0x200;
                wp->u_C.b.byte_C     = -0x60;
                wp->routine_1++;
            }
            break;
        case 2:
            if (--wp->u_C.b.byte_C == 0)
            {
                Sce_event_next();
                wp->u_C.b.byte_C     = 3;
                wp->value_44.half[0] = 0;
                wp->routine_1++;
            }
            if (wp->value_A6 != 0)
            {
                Sound_call2(0x112, &wp->position);
                if (!(rand() & 3))
                {
                    Sound_call2(0x171, &wp->position);
                }
            }
            // fall through
        case 3:
            if (STAGE_SCENE_PTR->u_8.byte[1] == 2)
            {
                MojiTaskExec2(0, 0x14);
                wp->position.x         = 0x1EA;
                wp->position.y         = -1;
                wp->position.z         = -0x1371;
                wp->value_44.half[0]   = 0x140;
                wp->u_C.b.byte_C       = -0x22;
                wp->rotation.y         = 0;
                wp->position_fixed.v.x = wp->position.x << 16;
                wp->position_fixed.v.y = wp->position.y << 16;
                wp->position_fixed.v.z = wp->position.z << 16;
                wp->routine_1++;
            }
            break;
        case 4:
            if (--wp->u_C.b.byte_C == 0)
            {
                wp->routine_0 = 2;
                wp->routine_1 = 0;
            }
            if (wp->value_A6 != 0)
            {
                Sound_call(0x112, 0, 0);
                if (!(rand() & 3))
                {
                    Sound_call(0x171, 0, 0);
                }
            }
            break;
    }
    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
}

void func_801140DC(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801140FC(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_80125464[wp->routine_0](wp);
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

void func_801141EC(ST06_ACTOR *wp)
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
    wp->value_78              = D_80125470;
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

void func_801142A8(ST06_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                wp->value_44.half[0] = 0x200;
                wp->u_C.b.byte_C     = -0x60;
                wp->routine_1++;
            }
            break;
        case 2:
            if (--wp->u_C.b.byte_C == 0)
            {
                wp->u_C.b.byte_C     = 3;
                wp->value_44.half[0] = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            if (STAGE_SCENE_PTR->u_8.byte[1] == 2)
            {
                wp->position.x         = 0x1EA;
                wp->position.y         = -1;
                wp->position.z         = -0x130D;
                wp->value_44.half[0]   = 0x140;
                wp->u_C.b.byte_C       = -0x22;
                wp->rotation.y         = 0;
                wp->position_fixed.v.x = wp->position.x << 16;
                wp->position_fixed.v.y = wp->position.y << 16;
                wp->position_fixed.v.z = wp->position.z << 16;
                wp->routine_1++;
            }
            break;
        case 4:
            if (--wp->u_C.b.byte_C == 0)
            {
                wp->routine_0 = 2;
                wp->routine_1 = 0;
            }
            break;
    }
    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
}

void func_80114430(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80114450(STAGE_OBJ *wp)
{
    D_8012547C[wp->variant_3](wp);
}

void func_8011448C(STAGE_OBJ *wp)
{
    D_80125480[wp->routine_0](wp);
    func_80114880(wp);
}

void func_801144DC(ST06_OBJ *wp)
{
    ST06_ANIM *anim;

    if (wp->routine_1 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        wp->data_78        = NULL;
        wp->position.y += Obj_ceiling_height_get(wp);
        wp->position_fixed.v.y = wp->position.y << 16;
        anim                   = &D_801254A4[wp->routine_0];
        func_800322A8(wp, anim->anim_0, anim->arg_1);
        wp->u_C.b.byte_D = 0;
        wp->u_E.b.byte_E = 1;
        wp->u_E.b.byte_F = 0;
        wp->routine_1++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        func_80032488(wp);
        if (STAGE_SCENE_PTR->u_8.byte[1] == 1)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
        }
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80114648(ST06_OBJ *wp)
{
    ST06_ANIM *anim;

    if (wp->routine_1 == 0)
    {
        anim = &D_801254A4[wp->routine_0];
        func_800322A8(wp, anim->anim_0, anim->arg_1);
        wp->u_C.b.byte_C = anim->loops_2;
        wp->routine_1++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        if (wp->routine_0 == 2 && wp->value_A4 == 0x17)
        {
            wp->part_100[3].value_0 = 0xC;
        }
        if (wp->value_A7 == -1)
        {
            if (wp->u_C.ub.byte_C == 0)
            {
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            else
            {
                wp->u_C.ub.byte_C--;
            }
        }
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80114798(STAGE_OBJ *wp)
{
    ST06_ANIM *anim;

    if (wp->routine_1 == 0)
    {
        anim = &D_801254A4[wp->routine_0];
        func_800322A8(wp, anim->anim_0, anim->arg_1);
        wp->routine_1++;
    }
    else
    {
        wp->position_prev       = wp->position;
        wp->position_fixed_prev = wp->position_fixed.v;
        wp->rotation_prev       = wp->rotation;
        func_80032488(wp);
    }
    Model_Shadow_Trans(wp, 0x30, 0x200, 0);
}

void func_80114880(ST06_ACTOR *wp)
{
    ST06_CUE *cue;

    cue = &D_801254C8[wp->value_D];
    if (cue->scene_0 != 0xFF && Scene_work.u_8.byte[1] == cue->scene_0 && Scene_work.value_10 == cue->frame_2)
    {
        wp->value_D++;
        wp->value_F = 0;
        wp->value_E = wp->value_E == 0;
    }
    if (wp->value_E != 0)
    {
        if (wp->value_F == 0)
        {
            wp->value_FC = (wp->value_FC == 0xB) ? 1 : 0xB;
        }
        wp->value_F = (wp->value_F + 1) & 3;
    }
    else
    {
        wp->value_FC = 0xB;
        wp->value_F  = 0;
    }
}

void func_8011494C(STAGE_OBJ *wp)
{
    D_8012551C[wp->routine_0](wp);
}

void func_80114988(ST06_BEAM *wp)
{
    STCOM_SVECTOR ahead;
    STCOM_FIXED_VECTOR unused; // retail's frame has room for it
    STCOM_FIXED_VECTOR dir;

    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->data_78        = NULL;
    wp->value_10       = 0;
    wp->scale.words[0] = 0x2000200;
    wp->scale.words[1] = 0x42100200;
    wp->data_78        = NULL;
    wp->value_10       = 0;
    wp->rotation.z     = 0;
    wp->rotation.y &= 0xFFF;
    wp->rotation.x &= 0xFFF;
    wp->rotation.y += Muku(&wp->position, ST06_PL_JOINT, wp->rotation.y, 0x200);
    wp->rotation.x += func_80031CA4(&wp->position, ST06_PL_JOINT, 0xC00, 0x400);
    wp->parts_2C8.origin_0 = wp->position;
    wp->parts_2C8.mask_10  = 0;
    wp->parts_2C8.lit_14   = 0;
    wp->parts_2C8.hit_8    = 0;
    wp->parts_2C8.value_C  = 0;
    wp->routine_3          = 0;
    wp->routine_0++;
    func_80032304(wp, 0, 0);
    Model_parts_mtx_set_yxz(wp);
    ahead.x = 0;
    ahead.y = 0;
    ahead.z = -0x1000;
    ApplyMatrix(&wp->matrix_160, &ahead, &dir);
    VectorNormalS(&dir, &wp->dir_44);
}

void func_80114AE8(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_80114AFC(STAGE_OBJ *wp)
{
    wp->routine_0++;
    Sound_call2(0xFF, &wp->position);
}

void func_80114B30(ST06_BEAM *wp)
{
    sint32 d;

    wp->position_prev = wp->position;
    func_80114FA8(wp, wp->routine_3);
    d              = ++wp->routine_3 * 100;
    wp->position.x = wp->parts_2C8.origin_0.x + ((wp->dir_44.x * d) >> 12);
    wp->position.y = wp->parts_2C8.origin_0.y + ((wp->dir_44.y * d) >> 12);
    wp->position.z = wp->parts_2C8.origin_0.z + ((wp->dir_44.z * d) >> 12);
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
    if (func_80114F10(wp))
    {
        Sound_key_off_voice(0x12);
        Sound_call2(0x140, &wp->position);
        wp->position_prev = wp->position;
        wp->routine_0 += 2;
        func_80032304(wp, 2, 0);
        Model_parts_mtx_set_yxz(wp);
        wp->routine_3 *= 2;
        return;
    }
    if (wp->routine_3 >= 0x14)
    {
        Sound_key_off_voice(0x12);
        wp->routine_0++;
        func_80032304(wp, 1, 0);
        Model_parts_mtx_set_yxz(wp);
        wp->routine_2 = 0xF;
    }
    func_80114F48(wp);
    wp->parts_2C8.lit_14 = wp->routine_3 * 2;
}

void func_80114CFC(ST06_BEAM *wp)
{
    if (wp->value_A7 < 0 && --wp->routine_2 == 0)
    {
        Sound_call2(0x140, &wp->position);
        wp->position_prev = wp->position;
        wp->routine_0++;
        func_80032304(wp, 2, 0);
        Model_parts_mtx_set_yxz(wp);
        wp->routine_3 *= 2;
    }
    else
    {
        func_80032538(wp);
        Model_parts_mtx_set_yxz(wp);
        func_80114F48(wp);
    }
}

void func_80114DC4(ST06_BEAM *wp)
{
    ST06_PARTS *parts;
    sint32 d;

    parts = &wp->parts_2C8;
    if (wp->value_A7 < 0)
    {
        wp->position_prev = wp->position;
        func_8011505C(wp, wp->routine_3 >> 1);
        d              = --wp->routine_3 * 0x32;
        wp->position.x = wp->parts_2C8.origin_0.x + ((wp->dir_44.x * d) >> 12);
        wp->position.y = wp->parts_2C8.origin_0.y + ((wp->dir_44.y * d) >> 12);
        wp->position.z = wp->parts_2C8.origin_0.z + ((wp->dir_44.z * d) >> 12);
        if (wp->routine_3 == 0)
        {
            wp->routine_0++;
        }
    }
    parts->lit_14 = wp->routine_3;
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

void func_80114EE4(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_C = 1;
    func_80031824(wp);
    Sound_key_off_voice(0x12);
}

sint32 func_80114F10(ST06_BEAM *wp)
{
    if (!(wp->parts_2C8.hit_8 & 0xFF000000))
    {
        return func_80049C24(wp) != 0;
    }
    return 1;
}

void func_80114F48(ST06_BEAM *wp)
{
    func_800341BC(&wp->pos_1A0, 0x20, 0, 0xA000, wp->value_1, &wp->parts_2C8.hit_8, 0x64000010, 0, 0);
    wp->parts_2C8.hit_8 = 0;
}

void func_80114FA8(ST06_BEAM *wp, uint8 index)
{
    ST06_10C *part;

    part = (ST06_10C *)Open_SHL_WORK();
    if (part != NULL)
    {
        part->flags_0     = 1;
        part->kind_2      = 0x16;
        part->variant_3   = index;
        part->owner_B8    = wp;
        part->position_AC = wp->position;
        part->rotation    = wp->rotation;
        part->color_B4    = 0x808080;
        wp->parts_2C8.mask_10 |= 1 << index;
    }
}

void func_8011505C(ST06_BEAM *wp, sint32 arg1)
{
    wp->parts_2C8.mask_10 &= ~(1 << arg1);
}

void func_80115078(ST06_OBJ *wp)
{
    sint8 temp_v0;
    uint8 temp_v0_2;

    if ((uint8)wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x100, 0);
    }
    D_80125538[wp->routine_0](wp);
    temp_v0          = (uint8)wp->u_E.b.byte_E + 1;
    wp->u_E.b.byte_E = temp_v0;
    if (temp_v0 >= 3)
    {
        wp->u_E.b.byte_E = 0;
        temp_v0_2        = wp->value_FC + 1;
        wp->value_FC     = temp_v0_2;
        if ((uint32)(temp_v0_2 & 0xFF) >= 5)
        {
            wp->value_FC = 1;
        }
    }
}

void func_80115128(STAGE_OBJ *wp)
{
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->value_10         = 0;
    wp->value_44.half[0] = 0;
    wp->value_44.half[1] = 0;
    wp->value_48.half[0] = 0;
    wp->value_4C.half[0] = 0;
    wp->value_4C.half[1] = 0;
    wp->value_50         = 0;
    func_800322A8(wp, 0x10, 0);
    if ((uint8)wp->u_C.b.byte_C != 0xFF)
    {
        wp->routine_0++;
    }
    else
    {
        *(uint32 *)&wp->routine_0 = 0;
        wp->routine_0             = 6;
    }
    *(uint32 *)&wp->u_C = 0;
}

void func_801151D8(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    func_80032488(wp);
    Obj_pos_set(wp, 0x61, 0, 0);
    temp_v0          = (uint8)wp->u_E.b.byte_F;
    wp->u_E.b.byte_F = temp_v0 + 1;
    if ((sint8)temp_v0 == 0x2D)
    {
        wp->routine_0++;
    }
}

void func_80115248(STAGE_OBJ *wp)
{
    func_80032488(wp);
}

void func_80115268(STAGE_OBJ *wp)
{
    wp->position_fixed.v.y -= 0x400000;
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_801152B0(STAGE_OBJ *wp)
{
    STAGE_OBJ *obj;

    obj                    = STAGE_SCENE.slot_24[0];
    wp->position           = obj->position;
    wp->position_fixed.v.x = obj->position_fixed.v.x;
    wp->position_fixed.v.y = obj->position_fixed.v.y + 0x02600000;
    wp->position_fixed.v.z = obj->position_fixed.v.z;
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_80115330(STAGE_OBJ *wp)
{
    STAGE_OBJ *obj;

    obj                    = STAGE_SCENE_OBJ(0);
    wp->position_fixed.v.x = obj->position_fixed.v.x;
    wp->position_fixed.v.z = obj->position_fixed.v.z;
    wp->u_E.b.byte_F ^= 1;
    if (wp->u_E.b.byte_F & 1)
    {
        wp->position_fixed.v.x += -0x80000;
    }
    else
    {
        wp->position_fixed.v.x += 0x80000;
    }
    func_80030150(&wp->position_fixed.v, &wp->position);
    func_80032488(wp);
}

void func_801153B0(STAGE_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->routine_1++;
            wp->routine_2        = 0x1E;
            wp->routine_3        = 3;
            wp->value_44.half[1] = -0x40;
            wp->value_44.half[0] = 0;
            wp->value_4C.half[1] = 2;
            // fall through
        case 1:
            Obj_pos_set(wp, (sint16)(wp->value_44.half[0] << 4), (sint16)(wp->value_44.half[1] << 4), 0);
            wp->value_44.half[1] += wp->value_4C.half[1];
            if (Obj_map_push_out(wp) & 0x1000)
            {
                Sound_call2(0x155, &wp->position);
                wp->value_44.half[1] = -0x40;
                wp->value_4C.half[1] <<= 1;
                if (--wp->routine_3 == 0)
                {
                    wp->routine_1++;
                }
            }
            if (wp->routine_2 == 0)
            {
                Sce_flag_on(0x640);
                Sce_flag_on(0x51);
                wp->routine_2++;
            }
            else
            {
                wp->routine_2--;
            }
            break;
        case 2:
            break;
    }
    func_80032488(wp);
}

void func_801154E4(STAGE_OBJ *wp)
{
    wp->scale.v.pad = 0x4210;
    D_80125554[wp->routine_0](wp);
}

void func_80115524(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->rotation.y       = 0xC00;
    wp->scale.words[1]   = 0x200;
    wp->value_44.half[0] = 0x1640;
    wp->value_44.half[1] = -0x10B0;
    wp->value_4C.half[0] = -0x40;
    wp->value_78         = 0;
    wp->value_10         = 0;
    wp->scale.words[0]   = 0x2000200;
    wp->value_48.half[0] = 0;
    wp->value_4C.half[1] = 0x30;
    wp->value_50         = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_801155C8(STAGE_OBJ *wp)
{
    func_80032488(wp);
}

void func_801155E8(STAGE_OBJ *wp)
{
    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
    wp->position_fixed.v.y -= wp->value_44.half[1] << 12;
    wp->position.y = wp->position_fixed.v.y >> 16;
    wp->value_44.half[0] += wp->value_4C.half[0];
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    func_80032488(wp);
}

void func_80115670(ST06_10C *wp)
{
    wp->value_4C  = -0x40;
    wp->routine_0 = 4;
    func_80032488(wp);
}

void func_8011569C(STAGE_OBJ *wp)
{
    STAGE_OBJ *obj;

    wp->value_44.half[0] += wp->value_4C.half[0];
    wp->value_44.half[1] += wp->value_4C.half[1];
    wp->value_48.half[0] += wp->value_50;
    Obj_pos_set(wp, (sint16)-wp->value_44.half[0], 0, 0);
    wp->position_fixed.v.y -= wp->value_44.half[1] << 12;
    wp->position.y = wp->position_fixed.v.y >> 16;
    func_80032488(wp);
    obj                     = STAGE_SCENE_OBJ(1);
    obj->position_fixed.v.x = wp->position_fixed.v.x;
    obj->position_fixed.v.y = wp->position_fixed.v.y + 0x2600000;
    obj->position_fixed.v.z = wp->position_fixed.v.z;
    func_80030150(&obj->position_fixed.v, &obj->position);
}

void func_80115764(STAGE_OBJ *wp)
{
    D_80125568[wp->variant_3](wp);
}

void func_801157A0(ST06_ACTOR *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x4000400;
        wp->scale.words[1] = 0x400;
        wp->scale.v.pad    = 0x4210;
        wp->rotation.y     = 0x8C0;
        func_800322A8(wp, 3, 0);
        wp->routine_0++;
    }
    if ((Scene_work.value_10 & 7) < 4)
    {
        wp->value_FC = 1;
    }
    else
    {
        wp->value_FC = 0xB;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    func_80032488(wp);
}

void func_801158B8(ST06_ACTOR *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    D_8012556C[wp->routine_0](wp);
    if (wp->routine_1 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_8011594C(ST06_ACTOR_B *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->value_78              = 0;
    wp->data_10               = NULL;
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
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_80115A58(STAGE_OBJ *wp)
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
