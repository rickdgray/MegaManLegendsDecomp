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
