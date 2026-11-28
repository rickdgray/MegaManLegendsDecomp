#include "common.h"
#include "st06.h"

void func_8010D1F8(ST06_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_80125184[wp->variant_3](wp);
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

void func_8010D2E8(ST06_ACTOR *wp)
{
    ST06_SCENE *scene;
    STCOM_PL_WORK *pl;
    sint16 turn;

    scene = (ST06_SCENE *)&Scene_work;
    pl    = &Player_work;
    if (scene->routine_0 == 0)
    {
        wp->routine_0 = 0x1B;
    }
    switch (wp->routine_0)
    {
        case 0:
            func_8010D7E8(wp);
            wp->routine_0++;
            break;
        case 1:
            if (scene->flag_9 == 2)
            {
                pl->flags_0 &= ~2;
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x2A);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 3:
        case 5:
        case 9:
        case 16:
        case 18:
        case 20:
        case 22:
        case 24:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_0++;
            }
            break;
        case 4:
            MojiTaskExec2(0, 0x2B);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 6:
            MojiTaskExec2(0, 0x2C);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 7:
        case 13:
        case 26:
            if (!(Moji_flag & 0x8000000))
            {
                Sce_event_next();
                pl->flags_0 |= 2;
                wp->routine_0++;
            }
            break;
        case 8:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x2D);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 10:
            MojiTaskExec2(0, 0x2E);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 11:
            if (!(Moji_flag & 0x8000000))
            {
                if (scene->work_1C >= 0x103)
                {
                    wp->routine_0++;
                    Sce_event_next();
                    pl->flags_0 |= 2;
                }
                else if (scene->work_1C < 0x100)
                {
                    scene->work_1C = 0x100;
                }
            }
            break;
        case 12:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                pl->flags_0 &= ~2;
                MojiTaskExec2(0, 0x2F);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 14:
            if (scene->flag_9 == 6)
            {
                wp->routine_0++;
            }
            break;
        case 15:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x32);
                pl->flags_0 &= ~2;
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 17:
            MojiTaskExec2(0, 0x59);
            wp->routine_0++;
            break;
        case 19:
            MojiTaskExec2(0, 0x33);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 21:
            MojiTaskExec2(0, 0x34);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 23:
            MojiTaskExec2(0, 0x35);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 25:
            MojiTaskExec2(0, 0x36);
            func_800322A8(wp, 8, 0);
            wp->routine_1 = 0;
            wp->routine_0++;
            break;
        case 27:
            wp->kind_2                = 0x14;
            wp->value_4               = 2;
            wp->variant_3             = 0x80;
            *(uint32 *)&wp->timer_C   = 0;
            *(uint32 *)&wp->routine_0 = 0;
            break;
    }
}

void func_8010D680(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_8010D7E8(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_8010D8A4(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x48);
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

void func_8010D7E8(ST06_ACTOR *wp)
{
    wp->rotation.x   = 0;
    wp->rotation.y   = -0xC8;
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
    wp->data_10          = D_8012518C;
    func_800322A8(wp, 0, 0);
    wp->routine_1 = 0;
}

sint32 func_8010D8A4(ST06_ACTOR *wp)
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
        D_8012BA20.x = wp->value_180.x;
        D_8012BA20.y = wp->value_180.y - 0x20;
        D_8012BA20.z = wp->value_180.z;
        func_80039FAC(&D_8012BA20, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void func_8010D9D4(ST06_ACTOR *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    D_801251B8[wp->variant_3](wp);
    if (wp->routine_1 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_8010DA68(STAGE_OBJ *wp)
{
    D_80125198[wp->routine_0](wp);
}

void func_8010DAA4(STAGE_OBJ *wp)
{
    D_801251A4[wp->routine_0](wp);
}

void func_8010DAE0(ST06_ACTOR *wp)
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
    wp->turn_64               = 0x80;
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_8010DBF4(ST06_ACTOR *wp)
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
        D_8012BA30    = Angle_xz_svector(&wp->position, &pl->position);
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

void func_8010DD0C(STAGE_OBJ *wp)
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

void func_8010DD70(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_10               = D_801251C0;
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

void func_8010DE88(ST06_ACTOR *wp)
{
    sint16 turn;

    turn           = Angle_diff_clamp(D_8012BA30, wp->rotation.y, wp->turn_64);
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

void func_8010DF30(STAGE_OBJ *wp)
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

void func_8010DF94(ST06_ACTOR *wp)
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

void func_8010E048(STAGE_OBJ *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    D_801251E0[wp->variant_3 & 0xF](wp);
    if (wp->routine_3 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_8010E0E0(STAGE_OBJ *wp)
{
    D_801251CC[wp->routine_0](wp);
}

void func_8010E11C(ST06_ACTOR *wp)
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
        D_8012BA38    = Angle_xz_svector(&wp->position, &pl->position);
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

void func_8010E234(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->data_10               = D_801251E4;
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

void func_8010E34C(ST06_ACTOR *wp)
{
    sint16 turn;

    turn           = Angle_diff_clamp(D_8012BA38, wp->rotation.y, wp->turn_64);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        if (wp->variant_3 & 0x80)
        {
            if (func_8010EB68())
            {
                MojiTaskExec2(0, 0x48);
                wp->routine_1 = 0xA;
            }
            else
            {
                MojiTaskExec2(0, 0x7C);
                wp->routine_1 = 0xFF;
            }
        }
        else if (func_8010EB68())
        {
            if (Sce_flag_test(0x232) && !Sce_flag_test(0x233))
            {
                MojiTaskExec2(0, 0x66);
            }
            else
            {
                MojiTaskExec2(0, 0x65);
            }
            wp->routine_1 = 0;
        }
        else
        {
            if (Sce_flag_test(0x232) && !Sce_flag_test(0x233))
            {
                MojiTaskExec2(0, 0x61);
            }
            else
            {
                MojiTaskExec2(0, 0x60);
            }
            wp->routine_1 = 8;
        }
        func_800322A8(wp, 8, 0);
        wp->value_E   = 8;
        wp->value_D   = 1;
        wp->routine_3 = 1;
        wp->routine_0++;
    }
    else
    {
        func_80032488(wp);
    }
}
