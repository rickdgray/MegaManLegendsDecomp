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

// One sum variable shared by the six money cases (a global pseudo, so each case's pointer is
// allocated first and takes v0, as in retail).
void func_8010E4C4(ST06_ACTOR *wp)
{
    sint32 *value1;
    sint32 *value2;
    sint32 *value3;
    sint32 *value4;
    sint32 *value5;
    sint32 *value6;
    sint32 sum;

    switch (wp->routine_1)
    {
        case 0:
            if (!(Moji_flag & 0x80000000))
            {
                if ((Moji_flag & 0xFF) == 1)
                {
                    MojiTaskExec2(0, 0x63);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 0xFF;
                }
                else if ((Moji_flag & 0xFF) == 0)
                {
                    if (Money_check(-1) == -1)
                    {
                        MojiTaskExec2(0, 0x68);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                    }
                    else
                    {
                        MojiTaskExec2(0, 0x58);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 1;
                    }
                }
                else if ((Moji_flag & 0xFF) == 2)
                {
                    func_8005C224(0x5DC);
                    MojiTaskExec2(0, 0x67);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 9;
                }
            }
            break;
        case 1:
            if (!(Moji_flag & 0x80000000))
            {
                switch (Moji_flag & 0xFF)
                {
                    case 0:
                        func_8005C224(500 - STAGE_GAME.value_28);
                        break;
                    case 1:
                        func_8005C224(200 - STAGE_GAME.value_2C);
                        break;
                    case 2:
                        func_8005C224(250 - STAGE_GAME.value_30);
                        break;
                    case 3:
                        func_8005C224(200 - STAGE_GAME.value_34);
                        break;
                    case 4:
                        func_8005C224(STAGE_GAME.value_67 * 180 - STAGE_GAME.value_3C);
                        break;
                    case 5:
                        func_8005C224(STAGE_GAME.value_66 * 150 - STAGE_GAME.value_38);
                        break;
                    case 6:
                        wp->routine_1 = 0xFF;
                        return;
                }
                MojiTaskExec2(0, (Moji_flag & 0xFF) + 0x6C);
                wp->value_E = 8;
                wp->value_D = 1;
                wp->routine_1 += 1 + Moji_flag;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value1 = &STAGE_GAME.value_28;
                    sum    = *value1;
                    sum += D_800987E0;
                    *value1 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value2 = &STAGE_GAME.value_2C;
                    sum    = *value2;
                    sum += D_800987E0;
                    *value2 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value3 = &STAGE_GAME.value_30;
                    sum    = *value3;
                    sum += D_800987E0;
                    *value3 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value4 = &STAGE_GAME.value_34;
                    sum    = *value4;
                    sum += D_800987E0;
                    *value4 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value5 = &STAGE_GAME.value_3C;
                    sum    = *value5;
                    sum += D_800987E0;
                    *value5 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x80000000))
            {
                if (D_800987E0 != 0)
                {
                    value6 = &STAGE_GAME.value_38;
                    sum    = *value6;
                    sum += D_800987E0;
                    *value6 = sum;
                    Money_add(-D_800987E0, 0, 1);
                    MojiTaskExec2(0, 0x73);
                }
                wp->routine_1 = 0xFF;
                wp->value_E   = 8;
                wp->value_D   = 1;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x80000000))
            {
                switch (Moji_flag & 0xFF)
                {
                    case 0:
                        MojiTaskExec2(0, 0x62);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                        break;
                    case 1:
                        MojiTaskExec2(0, 0x63);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                        break;
                    case 2:
                        func_8005C224(0x5DC);
                        MojiTaskExec2(0, 0x67);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 9;
                        break;
                }
            }
            break;
        case 9:
            if (!(Moji_flag & 0x80000000))
            {
                if (Moji_flag & 0xFF)
                {
                    MojiTaskExec2(0, 0x6A);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 0xFF;
                }
                else if (Money_check(-0x5DC) == -1)
                {
                    MojiTaskExec2(0, 0x68);
                    wp->value_E   = 8;
                    wp->value_D   = 1;
                    wp->routine_1 = 0xFF;
                }
                else
                {
                    MojiTaskExec2(0, 0x69);
                    wp->value_E = 8;
                    wp->value_D = 1;
                    Money_add(-0x5DC, 0, 1);
                    Sce_flag_on(0x233);
                    wp->routine_1 = 0xFF;
                }
            }
            break;
        case 10:
            if (!(Moji_flag & 0x80000000))
            {
                switch (Moji_flag & 0xFF)
                {
                    case 0:
                        if (Money_check(-1) == -1)
                        {
                            MojiTaskExec2(0, 0x68);
                            wp->value_E   = 8;
                            wp->value_D   = 1;
                            wp->routine_1 = 0xFF;
                        }
                        else
                        {
                            MojiTaskExec2(0, 0x58);
                            wp->value_E   = 8;
                            wp->value_D   = 1;
                            wp->routine_1 = 1;
                        }
                        break;
                    case 1:
                        MojiTaskExec2(0, 0x57);
                        wp->value_E   = 8;
                        wp->value_D   = 1;
                        wp->routine_1 = 0xFF;
                        break;
                }
            }
            break;
        case 0xFF:
            if (!(Moji_flag & 0x80000000))
            {
                func_80039E18();
                wp->value_E = 1;
                wp->value_D = 1;
                wp->routine_0++;
            }
            break;
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
}

void func_8010EA84(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    turn           = Angle_diff_clamp(wp->rotation_prev.y, wp->rotation.y, wp->turn_64);
    pl             = &Player_work;
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_3 = 0;
        Player_work.flags_bd &= ~0x80;
        pl->flags_0 |= 2;
        Sce_flag_off(0x23D);
        Sce_flag_off(0x23E);
        Sce_flag_off(0x23F);
        Sce_flag_off(0x240);
        Sce_flag_off(0x241);
        Sce_flag_off(0x242);
        wp->routine_0 = 1;
    }
    else
    {
        func_80032488(wp);
    }
}

sint16 func_8010EB68(void)
{
    sint16 changed;

    changed = 0;
    if (func_8003B2D4(6, 0x205) != 3 && STAGE_GAME.value_28 != 500)
    {
        changed = 1;
        Sce_flag_on(0x23D);
    }
    if (func_8003B2D4(6, 0xFC) != 3 && STAGE_GAME.value_2C != 200)
    {
        changed = 1;
        Sce_flag_on(0x23E);
    }
    if (func_8003B2D4(6, 0x120) != 3 && STAGE_GAME.value_30 != 250)
    {
        changed = 1;
        Sce_flag_on(0x23F);
    }
    if (func_8003B2D4(5, 0x26) != 3 && STAGE_GAME.value_34 != 200)
    {
        changed = 1;
        Sce_flag_on(0x240);
    }
    if (STAGE_GAME.value_3C != STAGE_GAME.value_67 * 180)
    {
        changed = 1;
        Sce_flag_on(0x241);
    }
    if (STAGE_GAME.value_38 != STAGE_GAME.value_66 * 150)
    {
        changed = 1;
        Sce_flag_on(0x242);
    }
    return changed;
}

void func_8010ECE8(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_801251F0[wp->variant_3](wp);
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
    wp->anim_prev_AD = wp->anim_AC;
}

void func_8010EDEC(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_8010EF94(wp);
        wp->routine_0++;
    }
}

void func_8010EE38(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_0)
    {
        case 0:
            func_8010EF94(wp);
            wp->routine_0++;
            break;
        case 1:
            if (func_8010F024(wp))
            {
                wp->routine_0++;
            }
            break;
        case 2:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                MojiTaskExec2(0, 0x14);
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

void func_8010EF94(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = Obj_ceiling_height_get(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->data_10          = D_801251F8;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->anim_AC          = 0;
    wp->anim_prev_AD     = 0xFF;
}

sint32 func_8010F024(ST06_ACTOR *wp)
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
        D_8012BA40.x = wp->value_180.x;
        D_8012BA40.y = wp->value_180.y - 0x20;
        D_8012BA40.z = wp->value_180.z;
        func_80039FAC(&D_8012BA40, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}

void func_8010F154(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_6        = rand();
    D_80125204[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->ctl.flags_4 & 0x10)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        if (wp->routine_0 != 4)
        {
            if (ctl->flags_4 & 0x100)
            {
                ctl->u_38.h.lo = (ctl->u_38.h.lo + ctl->u_3C.a.turn_1 * 40) & 0xFFF;
                ctl->u_38.h.hi = (ctl->u_38.h.hi - ctl->u_3C.a.turn_1 * 40) & 0xFFF;
            }
            else
            {
                ctl->u_38.h.lo = (ctl->u_38.h.lo + (wp->value_44.half[0] >> 1)) & 0xFFF;
                ctl->u_38.h.hi = (ctl->u_38.h.hi + (wp->value_44.half[0] >> 1)) & 0xFFF;
            }
            ST06_SP->angle_150 = ctl->u_38.h.lo;
            ST06_SP->angle_158 = ctl->u_38.h.hi;
        }
        Model_parts_mtx_set_y(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_AC, wp->value_A4);
    }
    if (ctl->flags_4 & 8)
    {
        func_80110A54(wp);
    }
    Pos_Shadow_Trans(&wp->joint_180[0], 0xC0, 0x200, 0);
}

void func_8010F35C(ST06_CRAB *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_4             = 0x5E;
    *(sint32 *)&wp->ctl.timer_8 = 0;
    *(sint32 *)&wp->ctl.kind_C  = 0;
    wp->ctl.hit_18              = 0;
    wp->ctl.value_1C            = 0;
    wp->ctl.value_2C            = 0;
    wp->ctl.u_38.h.hi           = 0;
    wp->ctl.u_38.h.lo           = 0;
    if (wp->variant_3 == 0)
    {
        wp->life_6E = D_80098844[wp->kind_2]->life_8 * 16;
    }
    else
    {
        wp->life_6E = D_80098844[wp->kind_2]->life_8 * 8;
    }
    wp->data_78      = D_80125240;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E;
    if (wp->u_C.b.byte_C & 2)
    {
        wp->routine_0 = 4;
        wp->routine_1 = 0;
    }
    else if (wp->u_C.b.byte_C & 0x10)
    {
        wp->routine_0 = 3;
        wp->routine_1 = 0;
    }
    else
    {
        wp->routine_0 = 1;
        wp->routine_1 = 0;
    }
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    wp->scale.v.pad = 0x4210;
}

void func_8010F490(ST06_CRAB *wp)
{
    if (wp->ctl.flags_4 & 2)
    {
        func_80110AF0(wp);
    }
    D_80125218[wp->routine_1](wp);
    if (wp->ctl.flags_4 & 1)
    {
        func_801107A0(wp);
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_4 &= ~1;
    }
    func_80051B68(wp, 1, 0, 0x1000008);
    wp->ctl.hit_18 = 0;
}

void func_8010F53C(ST06_CRAB *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_8 = 0xF;
            if (wp->routine_1 != 0)
            {
                wp->anim_AC = 0xB;
            }
            wp->routine_2++;
            break;
        case 1:
            if (!(--wp->ctl.timer_8 & 3))
            {
                func_80110734(&wp->joint_180[wp->ctl.timer_8 >> 2]);
            }
            if (wp->ctl.timer_8 == 0)
            {
                func_80052528(wp);
                func_80047148(wp, &wp->joint_180[0]);
                wp->u_C.b.byte_C |= 1;
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}

void func_8010F618(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->u_C.b.byte_D)
    {
        case 0:
            wp->anim_AC = 1;
            break;
        case 1:
            wp->anim_AC = 1;
            switch (wp->routine_2)
            {
                case 0:
                    wp->value_44.half[0] = 0x80;
                    Obj_pos_set(wp, 0x80, 0, 0);
                    if (wp->position.x < 0)
                    {
                        wp->ctl.timer_8 = 0x80;
                        wp->routine_2++;
                    }
                    break;
                case 1:
                    wp->ctl.u_3C.a.turn_1 = 1;
                    wp->rotation.y        = (wp->rotation.y + 0x10) & 0xFFF;
                    if (--wp->ctl.timer_8 == 0)
                    {
                        wp->routine_2++;
                    }
                    break;
                case 2:
                    wp->value_44.half[0] = 0x80;
                    Obj_pos_set(wp, 0x80, 0, 0);
                    break;
            }
            if (ctl->value_A == 1000)
            {
                wp->flags_0 &= ~2;
            }
            break;
        case 2:
            func_80110498(wp);
            if (wp->ctl.value_A == 0 || wp->ctl.value_A == 1400)
            {
                wp->flags_0 &= ~2;
            }
            if (ctl->value_A == 1000)
            {
                wp->flags_0 |= 2;
            }
            break;
        case 3:
            wp->flags_0 &= ~2;
            break;
    }
    ctl->value_A++;
}

void func_8010F7E8(ST06_CRAB *wp)
{
    if (wp->ctl.flags_4 & 2)
    {
        func_80110AF0(wp);
    }
    D_80125234[wp->routine_1](wp);
    wp->ctl.hit_18 = 0;
}

void func_8010F850(ST06_CRAB *wp)
{
    wp->anim_AC = 0;
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
        return;
    }
    wp->position.y         = Obj_ceiling_height_get(wp);
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->ctl.flags_4 |= 0x81;
}

void func_8010F8B0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    STCOM_SVECTOR probe;
    sint32 hit;
    sint32 count;
    sint16 front;
    sint16 side;
    uint8 done;

    done        = 0;
    wp->anim_AC = 1;
    ctl         = &wp->ctl;
    if (wp->ctl.value_A == 0)
    {
        Sound_call2(0xEA, &wp->position);
        wp->ctl.value_A = 9;
    }
    else
    {
        wp->ctl.value_A--;
    }
    if (ctl->timer_8 != 0)
    {
        ctl->timer_8--;
        wp->rotation.y = (wp->rotation.y + ctl->u_3C.a.turn_1 * 4) & 0xFFF;
        if (wp->variant_3 == 0)
        {
            wp->value_44.half[0] = 0x100;
        }
        else
        {
            wp->value_44.half[0] = 0x200;
        }
        Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
        hit = func_80049C24(wp);
        if (hit != 0)
        {
            count = func_80037BB4((void *)hit);
            if (count > 0)
            {
                done = 1;
                ctl->flags_4 |= 0x200;
                goto stop;
            }
            if (count == -1)
            {
                done = 1;
                ctl->flags_4 |= 0x1000;
                goto stop;
            }
        }
        if (wp->position.x < -0x275F || wp->position.x > 0x2B60)
        {
            done = 1;
            ctl->flags_4 |= 0x1000;
        }
        else if (wp->position.x >= -0x1BFF && wp->position.x <= -0xC00 && wp->position.z > 0xF60)
        {
            done = 1;
            ctl->flags_4 |= 0x1000;
        }
        else if (wp->position.x >= -0x275F && wp->position.x <= -0x1C00 && wp->position.z > 0x400 &&
                 wp->position.z - wp->position.x > 0x2B60)
        {
            done = 1;
            ctl->flags_4 |= 0x1000;
        }
        else if (ctl->flags_4 & 0x80)
        {
            probe = wp->position;
            if ((uint16)wp->rotation.y < 0x400 || (uint16)wp->rotation.y >= 0xC00)
            {
                probe.z -= 0x6C;
            }
            else
            {
                probe.z += 0x6C;
            }
            front = func_80048EA4(&probe, NULL, wp->value_44.half[1], wp->value_1);
            if ((front - wp->position_prev.y < 0 ? wp->position_prev.y - front : front - wp->position_prev.y) > 0)
            {
                done = 1;
                ctl->flags_4 |= 0x1000;
            }
            else
            {
                probe = wp->position;
                if ((uint16)wp->rotation.y < 0x800)
                {
                    probe.x -= 0x6C;
                }
                else
                {
                    probe.x += 0x6C;
                }
                side = func_80048EA4(&probe, NULL, wp->value_44.half[1], wp->value_1);
                if ((side - wp->position_prev.y < 0 ? wp->position_prev.y - side : side - wp->position_prev.y) > 0)
                {
                    done = 1;
                    ctl->flags_4 |= 0x1000;
                }
                else if (!done)
                {
                    wp->position.y         = (front <= side) ? front : side;
                    wp->position_fixed.v.y = wp->position.y << 16;
                }
            }
        }
    }
    else
    {
        wp->value_44.half[0] = 0;
        ctl->flags_4 |= 1;
    }
stop:
    if (done)
    {
        ctl->value_A         = 0;
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        wp->value_44.half[0] = 0;
        wp->anim_AC          = 0;
        ctl->flags_4         = (ctl->flags_4 & ~0x40) | 1;
    }
}

void func_8010FCB4(ST06_CRAB *wp)
{
    wp->anim_AC = 0;
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
        wp->value_44.half[0] = 0;
        wp->rotation.y       = (wp->rotation.y + wp->ctl.u_3C.a.turn_1 * 16) & 0xFFF;
        return;
    }
    wp->ctl.flags_4 |= 0x41;
}

void func_8010FD0C(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    void *hit;
    sint32 count;
    uint8 done;

    done = 0;
    ctl  = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC     = 4;
                wp->ctl.timer_8 = 0x8D;
                wp->ctl.value_A = 0;
                break;
            case 1:
                if (wp->ctl.value_A & 1)
                {
                    wp->anim_AC = 5;
                }
                else
                {
                    wp->anim_AC = 6;
                }
                break;
        }
        return;
    }
    switch (wp->routine_2)
    {
        case 0:
            if (--wp->ctl.timer_8 != 0)
            {
                if (wp->value_A6 == 1)
                {
                    wp->ctl.value_A++;
                    if (wp->variant_3 == 0)
                    {
                        wp->value_44.half[0] = 0x100;
                    }
                    else
                    {
                        wp->value_44.half[0] = 0x200;
                    }
                    Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
                    hit = (void *)func_80049C24(wp);
                    if (hit != NULL)
                    {
                        count = func_80037BB4(hit);
                        if (STAGE_SCENE_BYTE(0) == 0)
                        {
                            func_80037738((sint32)hit, 5);
                            if (count != 0)
                            {
                                if (ctl->value_A & 1)
                                {
                                    func_80110734(&wp->joint_180[2]);
                                }
                                else
                                {
                                    func_80110734(&wp->joint_180[4]);
                                }
                                if (count >= 6)
                                {
                                    if (ctl->value_A == 9)
                                    {
                                        ctl->flags_4 |= 0x400;
                                    }
                                }
                                else
                                {
                                    done = 1;
                                }
                                Sound_call2(0xEC, &wp->position);
                            }
                            else
                            {
                                done = 1;
                            }
                        }
                    }
                    else
                    {
                        done = 1;
                    }
                    wp->position         = wp->position_prev;
                    wp->position_fixed.v = wp->position_fixed_prev;
                    wp->value_44.half[0] = 0;
                }
            }
            else
            {
                done = 1;
            }
            if (done)
            {
                wp->routine_3 = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                *(uint16 *)&wp->routine_2 = 0;
                wp->ctl.value_A           = 0;
                wp->ctl.timer_8           = 0;
                wp->ctl.flags_4 |= 0x801;
            }
            break;
    }
}

void func_8010FF90(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    STCOM_SVECTOR pos;
    sint32 hit;
    sint32 count;

    ctl = &wp->ctl;
    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        switch (wp->routine_2)
        {
            case 0:
                wp->anim_AC     = 7;
                wp->ctl.timer_8 = 0x44;
                break;
            case 1:
                wp->anim_AC     = 8;
                wp->ctl.timer_8 = 0xE;
                Sound_call2(0xED, &wp->position);
                break;
            case 3:
                wp->anim_AC     = 9;
                wp->ctl.timer_8 = 0x1E;
                break;
            case 4:
                wp->anim_AC     = 0xA;
                wp->ctl.timer_8 = 0x14;
                break;
        }
        return;
    }
    wp->ctl.timer_8--;
    switch (wp->routine_2)
    {
        case 0:
            if (ctl->timer_8 == 0)
            {
                wp->value_44.half[0] = 0;
                wp->routine_3        = 0;
                wp->routine_2++;
                break;
            }
            wp->value_44.half[0] = -0x90;
            Obj_pos_set(wp, -0x90, 0, 0);
            if (func_80049C24(wp) != 0)
            {
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
            }
            break;
        case 1:
            if (ctl->timer_8 == 0)
            {
                wp->routine_2++;
                ctl->timer_8 = 0xF;
            }
            break;
        case 2:
            if (ctl->timer_8 == 0)
            {
                wp->routine_3        = 0;
                wp->value_44.half[0] = 0;
                wp->routine_2 += 2;
                break;
            }
            wp->value_44.half[0] = 0x400;
            Obj_pos_set(wp, 0x400, 0, 0);
            hit = func_80049C24(wp);
            if (hit != 0)
            {
                count = func_80037BB4((void *)hit);
                if (STAGE_SCENE_BYTE(0) == 0)
                {
                    func_80037738(hit, 0xF);
                    if (count != 0)
                    {
                        pos = wp->joint_180[0];
                        pos.x -= rsin(wp->rotation.y) >> 5;
                        pos.z -= rcos(wp->rotation.y) >> 5;
                        func_80110734(&pos);
                    }
                }
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
                wp->value_44.half[0] = -0x80;
                wp->routine_3        = 0;
                wp->routine_2++;
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                Sound_call2(0xEE, &wp->position);
            }
            break;
        case 3:
            if (ctl->timer_8 == 0)
            {
                wp->routine_3 = 0;
                wp->routine_2++;
            }
            if (wp->value_44.half[0] < 0)
            {
                wp->value_44.half[0] += 0x10;
            }
            else
            {
                wp->position         = wp->position_prev;
                wp->position_fixed.v = wp->position_fixed_prev;
                wp->value_44.half[0] = 0;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            break;
        case 4:
            if (ctl->timer_8 == 0)
            {
                *(uint16 *)&wp->routine_2 = 0;
                ctl->flags_4 |= 0x801;
            }
            break;
    }
}

void func_80110398(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    sint32 done;

    done        = 0;
    ctl         = &wp->ctl;
    wp->anim_AC = 0;
    if (wp->ctl.timer_8 != 0)
    {
        wp->ctl.timer_8--;
        wp->rotation.y += wp->ctl.u_3C.a.turn_1 * 16;
    }
    else
    {
        done = 1;
    }
    if (done & 0xFF)
    {
        ctl->flags_4 |= 0x801;
    }
}

void func_80110400(ST06_CRAB *wp)
{
    sint16 turn;

    if (wp->routine_2 == 0)
    {
        wp->routine_2             = 1;
        wp->anim_AC               = 1;
        wp->ctl.u_3C.a.target_2.x = 0x200;
        wp->ctl.u_3C.a.target_2.y = -0x301;
        wp->ctl.u_3C.a.target_2.z = 0x1400;
        return;
    }
    turn           = Muku(&wp->position, &wp->ctl.u_3C.a.target_2, wp->rotation.y, 0x10);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0)
    {
        wp->ctl.flags_4 |= 1;
    }
}

void func_80110498(ST06_CRAB *wp)
{
    STAGE_OBJ *owner;

    owner                  = wp->ctl.owner_0;
    wp->position.x         = owner->position.x;
    wp->position.y         = owner->position.y;
    wp->position.z         = owner->position.z;
    wp->position_fixed.v.x = owner->position_fixed.v.x;
    wp->position_fixed.v.y = owner->position_fixed.v.y;
    wp->position_fixed.v.z = owner->position_fixed.v.z;
    wp->rotation.y         = owner->rotation.y;
    wp->value_44.half[0]   = owner->value_44.half[0];
    wp->value_44.half[1]   = 0;
    wp->anim_AC            = 0;
    wp->ctl.flags_4 &= ~8;
}

void func_80110514(ST06_CRAB *wp)
{
    sint16 ground;

    switch (wp->routine_3)
    {
        case 0:
            wp->anim_AC          = 2;
            wp->ctl.timer_8      = 5;
            wp->value_44.half[1] = 0;
            wp->ctl.flags_4 |= 8;
            wp->routine_3++;
            break;
        case 1:
            wp->anim_AC = 2;
            if (wp->ctl.timer_8 != 0)
            {
                wp->ctl.timer_8--;
            }
            else
            {
                wp->value_44.half[1] += 0x30;
            }
            Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
            ground = Obj_ceiling_height_get(wp);
            if (ground < wp->position.y)
            {
                wp->position_fixed.v.y = ground << 16;
                wp->position.y         = ground;
                wp->anim_AC            = 3;
                wp->value_44.half[1]   = 0;
                wp->value_44.half[0]   = 0;
                wp->routine_3++;
                Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
                Sound_call2(0xEF, &wp->position);
            }
            break;
        case 2:
            wp->anim_AC = 3;
            if (wp->value_A7 == -1)
            {
                if (wp->u_C.b.byte_C & 0x10)
                {
                    wp->routine_0 = 3;
                    wp->routine_1 = 0;
                }
                else
                {
                    wp->routine_0   = 1;
                    wp->routine_1   = 0;
                    wp->ctl.timer_8 = 0xF;
                }
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void func_801106A4(ST06_CRAB *wp)
{
    wp->anim_AC = 0xC;
    wp->value_44.half[1] += 0x30;
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
    if (Obj_ceiling_height_get(wp) < wp->position.y)
    {
        wp->value_44.half[1]      = 0;
        wp->value_44.half[0]      = 0;
        wp->routine_0             = 2;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
    }
}

void func_80110734(STCOM_SVECTOR *pos)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 5;
        ep->kind_2    = 0x80;
        ep->variant_3 = 0x42;
        ep->pos_38.x  = pos->x;
        ep->pos_38.y  = pos->y;
        ep->pos_38.z  = pos->z;
    }
}

void func_801107A0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl             = &wp->ctl;
    wp->ctl.timer_8 = 0;
    switch (wp->routine_1)
    {
        case 3:
            if (ctl->flags_4 & 0x400)
            {
                ctl->flags_4 &= ~0x400;
                wp->routine_1             = 4;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            // fall through
        case 0:
        case 1:
        case 4:
        case 5:
        case 6:
            if (ctl->flags_4 & 0x200)
            {
                ctl->flags_4 &= ~0x200;
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (ctl->flags_4 & 0x1000)
            {
                ctl->flags_4       = (ctl->flags_4 & ~0x1000) | 0x100;
                ctl->u_3C.a.turn_1 = -1;
                wp->routine_1      = 5;
                wp->variant_3      = 0;
                ctl->timer_8       = ctl->random_6 % 112 + 16;
                break;
            }
            if (wp->variant_3 == 0)
            {
                if (ctl->flags_4 & 0x800)
                {
                    ctl->flags_4 &= ~0x900;
                    wp->routine_1      = 1;
                    ctl->timer_8       = 0x78;
                    ctl->u_3C.a.turn_1 = 0;
                    break;
                }
                wp->routine_2 = (uint8)ctl->random_6 & 7;
                if (wp->routine_2 < 6 && (ctl->flags_4 & 0x40))
                {
                    ctl->flags_4 &= ~0x100;
                    wp->routine_1 = 1;
                    ctl->timer_8  = 0x78;
                    if (wp->routine_2 & 2)
                    {
                        ctl->u_3C.a.turn_1 = 1;
                    }
                    else if (wp->routine_2 & 4)
                    {
                        ctl->u_3C.a.turn_1 = -1;
                    }
                    else
                    {
                        ctl->u_3C.a.turn_1 = 0;
                    }
                }
                else
                {
                    ctl->flags_4 |= 0x100;
                    wp->routine_1 = 2;
                    ctl->timer_8  = ctl->random_6 % 63 + 16;
                    if (wp->routine_2 & 1)
                    {
                        ctl->u_3C.a.turn_1 = 1;
                    }
                    else
                    {
                        ctl->u_3C.a.turn_1 = -1;
                    }
                }
            }
            else if (wp->routine_1 == 0)
            {
                wp->routine_1             = 6;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->u_3C.a.turn_1        = 1;
                ctl->flags_4 |= 0x100;
            }
            else
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->timer_8              = 0x4000;
                ctl->u_3C.a.turn_1        = 0;
                ctl->flags_4 &= ~0x100;
            }
            break;
        case 2:
            wp->routine_2 = (uint8)ctl->random_6 % 6;
            ctl->flags_4 &= ~0x100;
            wp->routine_1 = 1;
            ctl->timer_8  = 0x78;
            if (wp->routine_2 & 2)
            {
                ctl->u_3C.a.turn_1 = 1;
            }
            else if (wp->routine_2 & 4)
            {
                ctl->u_3C.a.turn_1 = -1;
            }
            else
            {
                ctl->u_3C.a.turn_1 = 0;
            }
            break;
    }
}

sint32 func_80110A54(ST06_CRAB *wp)
{
    wp->ctl.kind_C     = D_80098844[wp->kind_2]->value_A;
    wp->ctl.hit_pos_10 = wp->joint_180[0];
    func_800341BC(&wp->ctl.hit_pos_10, 0x80, 0, 0x8000, wp->value_1, &wp->ctl.hit_18, wp->ctl.kind_C | 0x4880000, 0x800000, 0);
    return 1;
}

sint32 func_80110AF0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    sint32 hit;
    sint32 damage;

    ctl              = &wp->ctl;
    hit              = wp->ctl.hit_18;
    damage           = hit & 0xFFFFFF;
    wp->life_prev_B2 = wp->life_6E;
    if (damage != 0 && (hit & 0x18000000))
    {
        wp->scale.v.pad = 0x7FFF;
        wp->life_6E -= damage;
        Sound_call2(0xA0, &wp->position);
    }
    if (wp->life_6E <= 0)
    {
        ctl->flags_4              = (ctl->flags_4 & ~2) | 4;
        wp->routine_0             = 2;
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
    }
    return 1;
}

void func_80110BA4(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_6        = rand();
    wp->ctl.u_38.dist       = SquareRoot0(wp->dist_80);
    D_8012524C[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else if (wp->ctl.flags_4 & 0x10)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->anim_prev_AD, wp->value_A4);
    }
    if (ctl->flags_4 & 8)
    {
        func_80111D54(wp);
    }
    Pos_Shadow_Trans(&wp->position, 0x100, 0x200, 0);
}

void func_80110CFC(ST06_CRAB *wp)
{
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    wp->ctl.flags_4             = 0x5E;
    *(sint32 *)&wp->ctl.timer_8 = 0;
    *(sint32 *)&wp->ctl.kind_C  = 0;
    wp->ctl.hit_18              = 0;
    wp->ctl.value_1C            = 0;
    wp->ctl.value_2C            = 0;
    wp->ctl.u_3C.b.value_8      = 0;
    wp->ctl.u_3C.b.value_7      = 0;
    wp->ctl.u_3C.b.rec_0        = D_80125278[wp->variant_3];
    wp->ctl.u_3C.b.flag_6       = wp->ctl.random_6 & 1;
    wp->life_prev_B2 = wp->life_max_B0 = wp->life_6E = D_80098844[wp->kind_2]->life_8 * 16;
    wp->data_78                                      = D_8012526C;
    if (wp->u_C.b.byte_C & 0x10)
    {
        wp->routine_0 = 3;
    }
    else
    {
        wp->routine_0 = 1;
    }
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    func_800322A8(wp, 4, 0);
    wp->scale.v.pad = 0x4210;
}

void func_80110E20(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->ctl.flags_4 & 2)
    {
        func_80111DF0(wp);
    }
    D_8012525C[wp->routine_1](wp);
    if (!(wp->ctl.flags_4 & 0x200) && wp->routine_1 != 3)
    {
        if ((wp->ctl.flags_4 & 0x80) && wp->ctl.u_38.dist < 0x800)
        {
            func_80111A30(wp);
        }
        else
        {
            func_80111AFC(wp);
        }
    }
    if (ctl->flags_4 & 1)
    {
        func_80111CF8(wp);
        wp->routine_3 = 0;
        ctl->flags_4 &= ~1;
    }
    ctl->hit_18 = 0;
}

void func_80110F18(ST06_CRAB *wp)
{
    STCOM_SVECTOR pos;
    STAGE_OBJ *part;

    switch (wp->routine_1)
    {
        case 0:
            wp->ctl.timer_8 = 3;
            func_80111BE0(&wp->joint_180[0]);
            wp->routine_1++;
            break;
        case 1:
            wp->ctl.timer_8--;
            func_80111BE0(&wp->joint_180[3 - wp->ctl.timer_8]);
            func_80111BE0(&wp->joint_180[6 - wp->ctl.timer_8]);
            if (wp->ctl.timer_8 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            part = func_80031418();
            if (part != NULL)
            {
                part->flags_0               = 1;
                part->kind_2                = 0;
                part->variant_3             = 1;
                part->value_4               = 1;
                *(uint32 *)&part->routine_0 = 0;
                *(uint32 *)&part->u_C       = 0;
                part->position.x            = wp->joint_180[0].x;
                part->position.y            = wp->joint_180[0].y - 0xC0;
                part->position.z            = wp->joint_180[0].z;
                part->position_fixed.v.x    = wp->joint_180[0].x << 16;
                part->position_fixed.v.y    = wp->joint_180[0].y << 16;
                part->position_fixed.v.z    = wp->joint_180[0].z << 16;
                part->rotation              = wp->rotation;
            }
            pos.x = wp->joint_180[0].x;
            pos.y = wp->joint_180[0].y - 0x80;
            pos.z = wp->joint_180[0].z;
            func_80047148(wp, &pos);
            wp->u_C.b.byte_C |= 1;
            break;
    }
}

void func_801110D8(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->u_C.b.byte_D)
    {
        case 0:
            if (wp->routine_2 == 0)
            {
                wp->routine_2++;
                wp->anim_AC = 0xA;
            }
            else
            {
                wp->value_44.half[0] = 0x100;
                Obj_pos_set(wp, 0x100, 0, 0);
                wp->rotation.y++;
            }
            if (ctl->value_A == 600)
            {
                wp->flags_0 &= ~2;
            }
            break;
        case 1:
            wp->anim_AC          = 0;
            wp->value_44.half[0] = 0xC0;
            Obj_pos_set(wp, 0xC0, 0, 0);
            if (wp->ctl.value_A == 0 || wp->ctl.value_A == 1400)
            {
                wp->flags_0 &= ~2;
            }
            if (ctl->value_A == 1000)
            {
                wp->flags_0 |= 2;
            }
            break;
        case 2:
            wp->anim_AC          = 0xA;
            wp->value_44.half[0] = 0xC0;
            Obj_pos_set(wp, 0xC0, 0, 0);
            if (wp->ctl.value_A == 1100)
            {
                wp->flags_0 &= ~2;
            }
            break;
    }
    ctl->value_A++;
}

void func_80111250(ST06_CRAB *wp)
{
    wp->ctl.flags_4 |= 1;
}

void func_80111264(ST06_CRAB *wp)
{
    STCOM_FIXED_VECTOR out;
    STCOM_SVECTOR size;
    ST06_CRAB_CTL *ctl;
    sint32 side;
    STCOM_PL_WORK *pl;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_3)
    {
        case 0:
            if (wp->anim_AC != 5)
            {
                wp->anim_AC = 5;
                Sound_call2(0xE9, &wp->position);
            }
            else if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 0xA;
                wp->routine_3 = 1;
            }
            break;
        case 1:
            wp->value_C4 = wp->joint_180[0];
            pl->value_C4 = pl->position;
            size.x       = 2;
            size.y       = 9;
            size.z       = 4;
            side         = func_80030418(wp, pl, &size, &out);
            if (side & 1)
            {
                wp->rotation.y = (sint16)(wp->rotation.y - 0x10) - ((wp->u_C.ub.byte_D << 24) >> 22);
            }
            else if (!(side & 2))
            {
                wp->rotation.y = (sint16)(wp->rotation.y + 0x10) + ((wp->u_C.ub.byte_D << 24) >> 22);
            }
            wp->value_44.half[0] = 0x200;
            wp->rotation.y &= 0xFFF;
            Obj_pos_set(wp, 0x200, 0, 0);
            if (ctl->timer_8 != 0)
            {
                ctl->timer_8--;
            }
            else
            {
                ctl->timer_8 = (ctl->random_6 & 0xF) + 0x18;
                if (ctl->u_38.dist < 0x400 && wp->routine_2 == 0 && *(uint8 *)&Scene_work == 0)
                {
                    func_80111C4C(wp);
                }
            }
            if (ctl->flags_4 & 0x100)
            {
                ctl->flags_4 |= 1;
            }
            break;
    }
}

void func_8011146C(ST06_CRAB *wp)
{
    STCOM_SVECTOR pts[2];
    STCOM_SVECTOR pt;
    ST06_CRAB_CTL *ctl;

    ctl                  = &wp->ctl;
    wp->value_44.half[0] = 0;
    wp->value_44.half[1] = 0;
    if (wp->ctl.u_3C.b.flag_6 == 0)
    {
        pts[0] = wp->ctl.u_3C.b.rec_0[0];
        pts[1] = wp->ctl.u_3C.b.rec_0[1];
    }
    else
    {
        pts[0] = wp->ctl.u_3C.b.rec_0[1];
        pts[1] = wp->ctl.u_3C.b.rec_0[0];
    }
    switch (wp->routine_3)
    {
        case 0:
            wp->rotation.y       = Angle_xz_svector(&wp->position, &pts[1]);
            wp->value_44.half[0] = 0x180;
            if (ctl->owner_0 == NULL)
            {
                if (wp->anim_AC != 3 && wp->anim_AC != 4)
                {
                    wp->anim_AC = 0xC;
                }
                wp->routine_3       = 6;
                ctl->u_3C.b.value_7 = ctl->random_6 & 7;
            }
            else
            {
                wp->anim_AC         = 0;
                wp->routine_3       = 1;
                ctl->u_3C.b.value_7 = (ctl->u_3C.b.flag_6 == 0) ? 7 : 0;
                ctl->flags_4 |= 0x200;
            }
            ctl->flags_4 |= 0x400;
            Sound_call2(0xE6, &wp->position);
            break;
        case 1:
            wp->value_44.half[0] = 0x180;
            if (ctl->owner_0 == NULL)
            {
                wp->anim_AC   = 1;
                wp->routine_3 = 5;
                break;
            }
            pt = ctl->u_3C.b.rec_0[ctl->u_3C.b.value_7 + 2];
            if (ctl->u_3C.b.flag_6 == 0)
            {
                if (wp->position.x < pt.x)
                {
                    break;
                }
            }
            else
            {
                if (wp->position.x > pt.x)
                {
                    break;
                }
            }
            wp->position.x       = pts[1].x;
            wp->value_44.half[0] = 0;
            wp->anim_AC          = 1;
            wp->routine_3++;
            break;
        case 2:
            wp->anim_AC = 1;
            if (wp->value_A7 == -1)
            {
                wp->u_C.ub.byte_C = 8;
                wp->anim_AC       = 2;
                wp->routine_3++;
                Sound_call2(0xE5, &wp->position);
            }
            break;
        case 3:
            ctl->flags_4 &= ~0x400;
            wp->anim_AC = 2;
            if (wp->value_A7 == -1)
            {
                ctl->u_3C.b.value_7 = ctl->random_6 & 7;
                if (ctl->u_3C.b.value_7 == ctl->u_3C.b.value_8)
                {
                    ctl->u_3C.b.value_7 = 7 - ctl->u_3C.b.value_7;
                }
                ctl->u_3C.b.value_8 = ctl->u_3C.b.value_7;
                wp->anim_AC         = 3;
                wp->routine_3++;
            }
            break;
        case 4:
            wp->anim_AC = 3;
            if (wp->value_A7 == -1)
            {
                ctl->flags_4 = (ctl->flags_4 & ~0x200) | 1;
                wp->routine_3 += 2;
            }
            break;
        case 5:
            wp->anim_AC = 1;
            if (wp->value_A7 == -1)
            {
                wp->anim_AC   = 2;
                wp->routine_3 = 3;
                Sound_call2(0xE5, &wp->position);
            }
            break;
        case 6:
            ctl->flags_4 |= 0x400;
            wp->value_44.half[0] = 0x300;
            if (ctl->u_3C.b.flag_6 == 0)
            {
                if (wp->position.x >= pts[1].x)
                {
                    wp->position.x       = pts[1].x;
                    wp->value_44.half[0] = 0;
                    wp->routine_3++;
                }
            }
            else if (pts[1].x >= wp->position.x)
            {
                wp->position.x       = pts[1].x;
                wp->value_44.half[0] = 0;
                wp->routine_3++;
            }
            break;
        case 7:
            ctl->flags_4 |= 0x200;
            wp->value_44.half[1] = 0x100;
            if (wp->position.y >= pts[1].y)
            {
                wp->position.y = pts[1].y;
                ctl->u_3C.b.flag_6 ^= 1;
                if (ctl->owner_0 == NULL)
                {
                    wp->anim_AC = 0;
                    wp->u_C.ub.byte_C |= 2;
                    Sound_call2(0xE7, &wp->position);
                }
                wp->routine_3++;
            }
            break;
        case 8:
            wp->rotation.y = Angle_xz_svector(&wp->position, &pts[1]);
            wp->routine_3++;
            break;
        case 9:
            wp->value_44.half[1] = -0x100;
            if (wp->position.y < -0x63F)
            {
                wp->position.y = -0x640;
                wp->routine_3  = 1;
            }
            break;
    }
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
}

void func_8011193C(ST06_CRAB *wp)
{
    STCOM_EFFECT *fx;

    if (wp->routine_3 == 0)
    {
        wp->routine_3 = 1;
        wp->anim_AC   = 9;
        fx            = func_80031618();
        if (fx != NULL)
        {
            fx->flags_0           = 5;
            fx->kind_2            = 0x80;
            fx->variant_3         = 0x42;
            fx->sprite.position.x = wp->joint_180[0].x;
            fx->sprite.position.y = wp->joint_180[0].y;
            fx->sprite.position.z = wp->joint_180[0].z;
        }
        return;
    }
    wp->value_44.half[1] += 0x18;
    Obj_pos_set(wp, wp->value_44.half[0], wp->value_44.half[1], 0);
    if (Obj_ceiling_height_get(wp) < wp->position.y - 0x140)
    {
        wp->value_44.half[1]      = 0;
        wp->value_44.half[0]      = 0;
        wp->routine_0             = 2;
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        Swing_Camera2(0x10, 0x400, 0x2000, &wp->position);
    }
}

void func_80111A30(ST06_CRAB *wp)
{
    sint16 ground;
    sint32 dy;

    ground = Obj_ceiling_height_get(wp);
    dy     = ground - wp->position.y;
    if (dy < -0x10)
    {
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        wp->value_44.half[0] = 0;
        wp->position.y -= 0x10;
    }
    else if (dy > 0x10 && wp->position.y < Player_work.position.y)
    {
        wp->position.y += 0x10;
    }
    wp->position_fixed.v.y = wp->position.y << 16;
}

void func_80111AFC(ST06_CRAB *wp)
{
    sint16 ground;
    sint16 step;
    sint16 y;

    ground = Obj_ceiling_height_get(wp);
    step   = 0;
    y      = wp->position.y;
    if (y >= -0x62F)
    {
        step = -0x10;
    }
    else if (y < -0x650)
    {
        step = 0x10;
    }
    if (ground < y)
    {
        wp->position         = wp->position_prev;
        wp->position_fixed.v = wp->position_fixed_prev;
        wp->value_44.half[0] = 0;
        wp->position.y -= 0x10;
    }
    else
    {
        wp->position.y += step;
    }
    wp->position_fixed.v.y = wp->position.y << 16;
}

void func_80111BE0(STCOM_SVECTOR *pos)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 5;
        ep->kind_2    = 0x80;
        ep->variant_3 = 0x42;
        ep->pos_38.x  = pos->x;
        ep->pos_38.y  = pos->y;
        ep->pos_38.z  = pos->z;
    }
}

void func_80111C4C(ST06_CRAB *wp)
{
    ST06_SHOT *shot;

    shot = (ST06_SHOT *)Open_SHL_WORK();
    if (shot != NULL)
    {
        shot->flags_0          = 1;
        shot->kind_2           = 6;
        shot->variant_3        = 0x80;
        shot->routine_8        = 0;
        shot->value_C          = 0;
        shot->position         = wp->joint_180[0];
        shot->angle_64         = 0;
        shot->speed_9C         = 0;
        shot->rise_A0          = 0;
        shot->position_fixed.x = shot->position.x << 16;
        shot->position_fixed.y = shot->position.y << 16;
        shot->position_fixed.z = shot->position.z << 16;
        Sound_call2(0xE8, &wp->position);
    }
}

void func_80111CF8(ST06_CRAB *wp)
{
    sint32 next;

    switch (wp->routine_1)
    {
        case 0:
        case 1:
        case 2:
            if (wp->ctl.flags_4 & 0x80)
            {
                wp->ctl.flags_4 &= ~0x200;
                next = 1;
            }
            else if (wp->ctl.flags_4 & 0x100)
            {
                next = 2;
            }
            else
            {
                break;
            }
            wp->ctl.timer_8           = 0;
            wp->routine_1             = next;
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
}

sint32 func_80111D54(ST06_CRAB *wp)
{
    wp->ctl.kind_C     = D_80098844[wp->kind_2]->value_A;
    wp->ctl.hit_pos_10 = wp->joint_180[0];
    func_800341BC(&wp->ctl.hit_pos_10, 0x80, 0, 0x8000, wp->value_1, &wp->ctl.hit_18, wp->ctl.kind_C | 0x4880000, 0x800000, 0);
    return 1;
}

sint32 func_80111DF0(ST06_CRAB *wp)
{
    ST06_CRAB_CTL *ctl;
    sint32 hit;
    sint32 damage;

    ctl              = &wp->ctl;
    hit              = wp->ctl.hit_18;
    damage           = hit & 0xFFFFFF;
    wp->life_prev_B2 = wp->life_6E;
    if (damage != 0 && (hit & 0x18000000))
    {
        wp->scale.v.pad = 0x7FFF;
        wp->life_6E -= damage;
        Sound_call2(0xA0, &wp->position);
    }
    if (wp->life_6E <= 0)
    {
        ctl->flags_4              = (ctl->flags_4 & ~2) | 4;
        wp->routine_1             = 3;
        *(uint16 *)&wp->routine_2 = 0;
        wp->u_C.b.byte_C |= 4;
    }
    return 1;
}

void func_80111EA8(STAGE_OBJ *wp)
{
    D_80125368[wp->routine_0](wp);
}

void func_80111EE4(ST06_ACTOR *wp)
{
    ST06_ACTOR_CTL *ctl;

    wp->flags_0 |= 2;
    ctl = &wp->ctl;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x21A021A;
    wp->scale.words[1]       = 0x21A;
    wp->scale.v.pad          = 0x4210;
    ctl->flags_0             = 2;
    *(uint32 *)&ctl->timer_4 = 0;
    D_8012BA50               = wp->position_fixed;
    ctl->target_C            = wp->position;
    func_8002FFC4(&ctl->target_C, &D_8012BA50, wp->rotation.y, 0x100, 0, 0);
    wp->value_6E          = 0x80;
    wp->value_B0          = 0x80;
    wp->value_B2          = 0x80;
    wp->value_78          = D_80125384;
    ctl->timer_A          = 0;
    wp->rotation.x        = 0;
    wp->rotation.z        = 0;
    wp->velocity.words[0] = 0;
    wp->velocity.words[1] = 0;
    wp->data_10           = D_80125390;
    if (wp->variant_3 != 0)
    {
        wp->routine_1 = 1;
    }
    else
    {
        wp->routine_1 = 0;
    }
    wp->routine_0             = 1;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8011201C(wp);
}

void func_8011201C(ST06_ACTOR *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.value_2         = rand();
    if (wp->ctl.flags_0 & 2)
    {
        func_80112488(wp);
    }
    D_80125374[wp->routine_1](wp);
    if (wp->ctl.flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->ctl.flags_0 &= ~1;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    *(uint16 *)0x1F800132 = wp->ctl.timer_A;
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 1)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
}
