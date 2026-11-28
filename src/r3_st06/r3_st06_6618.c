#include "common.h"
#include "st06.h"

void func_80106618(STAGE_PL_SCRIPT *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    switch (wp->routine_D)
    {
        case 0:
            wp->value_448 = 0x30;
            wp->routine_D++;
            break;
        case 1:
            if (scene->u_8.byte[1] == 1)
            {
                wp->routine_D++;
            }
            break;
        case 2:
            wp->value_448 = 0xC;
            wp->timer_E   = 0;
            wp->routine_D++;
            break;
        case 3:
            wp->timer_E++;
            wp->fixed_428.z += 0x50000;
            if (wp->timer_E == 0x3C)
            {
                wp->routine_D++;
            }
            break;
        case 4:
            wp->value_442 = 0x700;
            wp->value_448 = 0x30;
            wp->fixed_428.x += 0x64;
            wp->routine_D++;
            break;
        case 5:
            if (scene->u_8.byte[1] == 5)
            {
                wp->value_442 = 0x800;
                wp->routine_D++;
            }
            break;
        case 6:
            break;
    }
}

void func_80106720(STAGE_PL_SCRIPT *wp)
{
    D_801245AC[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_80106780(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.fixed_428.z = -450 << 16;
        STAGE_PL.fixed_428.x = 0;
        STAGE_PL.fixed_428.y = 0;
        STAGE_PL.value_442   = 0x800;
    }
}

void func_801067BC(void)
{
}

void func_801067C4(void)
{
}

void func_801067CC(STAGE_ROOM *wp)
{
    STAGE_SPAWNED *obj;
    sint32 i;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80124484;
    wp->tbl_A4 = D_801245B0;
    for (i = 0; i < 2; i++)
    {
        // One-pass block preserves retail's register allocation and scheduling.
        do
        {
            obj = Scene_obj_ent_open(D_80124434[i]);
        } while (0);
        obj->flags_6 &= ~0x20;
    }
    Player_work.routine_0 = 3;
    Player_work.routine_1 = 1;
    STAGE_PL.value_C      = 0;
}

void func_8010687C(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801068BC(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_801067CC(wp);
                Sce_camera_update();
                wp->routine_4++;
            }
            break;
        case 1:
        case 2:
            wp->routine_4++;
            break;
        case 3:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_4++;
            }
            if (func_8001DE84() != 0)
            {
                wp->routine_4 = 10;
            }
            // fall through
        case 4:
            func_8010687C((STAGE_ROOM_WORK *)wp);
            func_80106720((STAGE_PL_SCRIPT *)&Player_work);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 4)
            {
                wp->routine_4 = 11;
            }
            break;
        case 10:
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
            D_800A395C = 1;
            func_80039820();
            Sce_flag_on(0x52B);
            wp->routine_4++;
            break;
        case 11:
            func_80042314(&Player_work);
            D_800A395C = 1;
            func_8003A264();
            D_800989F8.routine_5 = 1;
            wp->flags_0          = 0;
            func_8001E3F0(0x16);
            func_8001D974();
            break;
    }
}

void func_80106A44(sint16 arg0, sint16 arg1, sint16 arg2, sint16 arg3)
{
    D_800C356C = 1;
    D_800C356E = 6;
    D_800C3571 = 0xA;
    D_800C356F = 0;
    D_800C3560 = arg0;
    D_800C3562 = arg1;
    D_800C3564 = arg2;
    D_800C356A = arg3;
    D_800C356D = 0;
    D_800C3570 = 2;
}

void func_80106AAC(STAGE_ROOM *wp)
{
    STAGE_ACTOR *slot;
    sint32 i;

    if (func_80042238(&Player_work))
    {
        for (i = 0, slot = D_8009F108; i < 16; i++, slot++)
        {
            if (slot->flags_0 != 0 && slot->kind_2 == 5)
            {
                break;
            }
        }
        wp->child_24        = (STAGE_OBJ *)slot;
        STAGE_GAME.value_78 = 1;
        STAGE_GAME.value_79 = 6;
        STAGE_GAME.value_7A = 0;
        STAGE_PL.flags_bd   = (STAGE_PL.flags_bd | 0x20) & ~0x40;
        Sce_flag_on(0x318);
        Sce_flag_on(0x319);
        Sce_flag_on(0x31A);
        D_8012BA00    = 0;
        wp->routine_5 = 0;
        wp->routine_6 = 0;
        wp->routine_7 = 0;
        wp->routine_4++;
    }
}

void func_80106B98(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_CAM *cam;
    STAGE_OBJ *obj;
    STAGE_OBJ *piece;
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR *pos;
    STCOM_SVECTOR *target;
    sint32 i;
    sint16 turn;

    pl  = &STAGE_PL;
    cam = &Sce_camera_work;
    obj = wp->child_24;
    switch (wp->routine_5)
    {
        case 0:
            MojiTaskExec2(0, 0x15);
            wp->routine_5++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                vec.x = obj->position.x;
                vec.y = obj->position.y - 0x80;
                vec.z = obj->position.z - 0x102;
                func_80039FFC(&vec, 0, 0, 0);
                D_8012BA00 = 1;
                wp->routine_5++;
            }
            break;
        case 2:
            if (func_8003A13C() == 0)
            {
                obj->u_E.b.byte_E = 8;
                obj->u_C.b.byte_D = 1;
                MojiTaskExec2(0, 0x16);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                func_80106A44(0x200, -0x300, 0x9E1, 0);
                wp->routine_5++;
            }
            break;
        case 4:
            if (D_800C356C_A[0] == 2)
            {
                D_800C356C_A[0]++;
                func_80039E50();
                D_8012BA00 = 0;
                wp->routine_5++;
            }
            break;
        case 5:
            if (D_800C356C == 0)
            {
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->flags_0            = 1;
                    obj->kind_2             = 5;
                    obj->value_4            = 5;
                    obj->position.x         = 0x2C2;
                    obj->position.y         = -0x301;
                    obj->position.z         = 0x7D0;
                    obj->variant_3          = 0;
                    obj->u_E.b.byte_E       = 0;
                    obj->rotation.y         = 0x800;
                    obj->position_fixed.v.x = obj->position.x << 16;
                    obj->position_fixed.v.y = obj->position.y << 16;
                    obj->position_fixed.v.z = obj->position.z << 16;
                    wp->child_24            = obj;
                }
                func_8001E6C0(0, 0, 0);
                cam->pos_10 = obj->position.x << 16;
                cam->pos_14 = (obj->position.y - 0x84) << 16;
                cam->pos_18 = (obj->position.z + 0x120) << 16;
                cam->rot_40 = 0x8000000;
                cam->rot_44 = 0;
                cam->rot_48 = 0xFFE00000;
                wp->routine_5++;
            }
            break;
        case 6:
            if (D_80098A72 == 0)
            {
                obj->u_E.b.byte_E = 8;
                obj->u_C.b.byte_D = 1;
                MojiTaskExec2(0, 0x6C);
                wp->routine_5++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x08000000))
            {
                cam->pos_10 = 0x9300000;
                cam->pos_14 = 0xF8EB0000;
                cam->pos_18 = 0x6DB0000;
                cam->rot_40 = 0x6100000;
                cam->rot_44 = 0x1540000;
                cam->rot_48 = 0xFFE00000;
                for (i = 0; i < 2; i++)
                {
                    piece = Open_SHL_WORK();
                    if (piece != NULL)
                    {
                        piece->position.x         = 0x1DDF + i * 0x35C;
                        piece->flags_0            = 1;
                        piece->kind_2             = 0x29;
                        piece->position.y         = -0x301;
                        piece->position.z         = -0x3E8;
                        piece->rotation.y         = 0x400;
                        piece->value_44.half[0]   = 0x500;
                        piece->position_fixed.v.x = piece->position.x << 16;
                        piece->position_fixed.v.y = piece->position.y << 16;
                        piece->position_fixed.v.z = piece->position.z << 16;
                        (&wp->child_28)[i]        = piece;
                    }
                }
                obj->u_E.b.byte_E = 0;
                obj->u_C.b.byte_D = 1;
                Sound_call(0x18E, 1, 0);
                wp->routine_5++;
            }
            break;
        case 8:
            if (wp->child_28->position.x < 0xBB8)
            {
                cam->pos_10   = 0x2FA0000;
                cam->pos_14   = 0xFC720000;
                cam->pos_18   = 0x8C60000;
                cam->rot_40   = 0x8D00000;
                cam->rot_44   = 0x340000;
                cam->rot_48   = 0xFFE00000;
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                pl->pos_438.x   = obj->position.x - 0x64;
                pl->pos_438.y   = pl->position.y;
                pl->pos_438.z   = obj->position.z + 0x64;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->value_440   = 0;
                pl->value_442   = Angle_xz_svector(&pl->pos_438, &obj->position);
                pl->value_444   = 0;
                pl->value_448   = 0x30;
                Sound_call(0x18F, 1, 0);
                wp->child_24->rotation.y = 0;
                wp->routine_5++;
            }
            break;
        case 9:
            pos    = &obj->position;
            target = &wp->child_28->position;
            Muku(pos, target, obj->rotation.y, 0x40);
            if (obj->rotation.y < 0x200)
            {
                turn = Muku(pos, target, obj->rotation.y, 0x40);
                if (turn > 0)
                {
                    obj->rotation.y += turn;
                }
            }
            else
            {
                MojiTaskExec2(0, 0x6D);
                wp->routine_5++;
            }
            break;
        case 10:
            if (!(Moji_flag & 0x08000000))
            {
                wp->frame_10 = 0x10;
                wp->routine_5++;
            }
            break;
        case 11:
            if (wp->frame_10 != 0)
            {
                wp->frame_10--;
                cam->pos_10 += 880640.0;
                cam->pos_18 += -802816.0;
                cam->rot_40 += 3223552.0;
                cam->rot_44 += 0x20000;
            }
            turn = Muku(&obj->position, &pl->position, obj->rotation.y, 0x40);
            obj->rotation.y += turn;
            if (wp->frame_10 == 0 && turn == 0)
            {
                MojiTaskExec2(0, 0x6E);
                pl->value_448 = 0x32;
                wp->routine_5++;
            }
            break;
        case 12:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x6F);
                obj->u_E.b.byte_E = 8;
                obj->u_C.b.byte_D = 1;
                wp->routine_5++;
            }
            break;
        case 13:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x70);
                pl->value_448 = 0x32;
                wp->routine_5++;
            }
            break;
        case 14:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x71);
                obj->u_E.b.byte_E = 8;
                obj->u_C.b.byte_D = 1;
                wp->routine_5++;
            }
            break;
        case 15:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x72);
                pl->value_448 = 0x32;
                wp->routine_5++;
            }
            break;
        case 16:
            if (!(Moji_flag & 0x08000000))
            {
                pl->value_448 = 0xD;
                wp->frame_10  = 0x10;
                wp->routine_5++;
            }
            break;
        case 17:
            if (wp->frame_10 != 0)
            {
                wp->frame_10--;
                pl->value_442 += 0x80;
            }
            else
            {
                pl->value_448 = 1;
                wp->frame_10  = 0x1E;
                wp->routine_5++;
            }
            break;
        case 18:
            if (wp->frame_10 != 0)
            {
                wp->frame_10--;
                pl->flags_bd |= 0x10;
                pl->pos_438.x -= 0x14;
                pl->pos_438.z += 0x14;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0 && D_800C356C == 0 && D_80098A72 == 0 && wp->routine_4 == 1)
    {
        func_80053AA4(0);
        Cd_subcmd(0, 1, 0);
        wp->routine_5 = 0;
        wp->routine_4++;
    }
}

void func_80107418(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_80106A44(0x1A9, -0x301, 0x1940, 0x800);
            wp->routine_5++;
            break;
        case 1:
            if (D_800C356C_A[0] == 2)
            {
                if (D_8012BA00 != 0)
                {
                    func_80039E50();
                }
                D_800C356C_A[0]++;
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                wp->flags_0 = 0;
            }
            break;
    }
}

void func_801074F0(STAGE_ROOM *wp)
{
    D_801245F0[wp->routine_4](wp);
}

void func_8010752C(ST06_OBJ *wp)
{
    if (wp->value_10 == 0)
    {
        Sce_flag_off(wp->value_6 + 0x243);
        MojiTaskExec2(0, 0x49);
    }
    if (!(Moji_flag & 0x08000000))
    {
        Fade_start(9);
        wp->routine_2 = 0;
        Sce_event_next();
    }
}

void func_801075A0(ST06_OBJ *wp)
{
    if (D_80098A72 == 0)
    {
        Scene_obj_ent_open(&D_80124634[wp->value_6]);
        STAGE_PL.pos_438.x   = D_801245FC[wp->value_6].x;
        STAGE_PL.pos_438.y   = D_801245FC[wp->value_6].y;
        STAGE_PL.pos_438.z   = D_801245FC[wp->value_6].z;
        STAGE_PL.fixed_428.x = D_801245FC[wp->value_6].x << 16;
        STAGE_PL.fixed_428.y = D_801245FC[wp->value_6].y << 16;
        STAGE_PL.fixed_428.z = D_801245FC[wp->value_6].z << 16;
        STAGE_PL.value_442   = D_801245FC[wp->value_6].angle;
        wp->value_7          = 1;
        func_8001E6C0(0, 0, 0);
        D_800BC7F0 = D_801247D8[wp->value_6];
        Fade_start(1);
        Sce_event_next();
    }
}

void func_8010772C(STAGE_OBJ *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_2 = 1;
        Sce_event_next();
    }
}

void func_8010775C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        MojiTaskExec2(0, 0x4A);
        (&wp->child_24)[wp->routine_6]->u_E.b.byte_E = 8;
        (&wp->child_24)[wp->routine_6]->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x3D)
    {
        Sce_event_next();
    }
}

void func_801077EC(STAGE_OBJ *wp)
{
    if (!(Moji_flag & 0x08000000) && (wp->value_10 >= 0xB6))
    {
        Sce_event_next();
    }
}

void func_80107834(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        if ((sint8)func_80107DB0() != -1)
        {
            MojiTaskExec2(0, 0x4B);
            (&wp->child_24)[wp->routine_6]->u_E.b.byte_E = 8;
            (&wp->child_24)[wp->routine_6]->u_C.b.byte_D = 1;
        }
        else
        {
            Fade_start(9);
            wp->reserved09[1] = 0;
            wp->routine_4     = 4;
        }
    }
    else if (!(Moji_flag & 0x08000000))
    {
        Fade_start(9);
        wp->reserved09[1] = 0;
        Sce_event_next();
    }
}

void func_80107908(STAGE_ROOM *wp)
{
    if (D_80098A72 == 0)
    {
        func_80031824((&wp->child_24)[wp->routine_6]);
        wp->routine_6 = func_80107DB0();
        Scene_obj_ent_open(&D_80124634[wp->routine_6]);
        STAGE_PL.pos_438.x   = D_801245FC[wp->routine_6].x;
        STAGE_PL.pos_438.y   = D_801245FC[wp->routine_6].y;
        STAGE_PL.pos_438.z   = D_801245FC[wp->routine_6].z;
        STAGE_PL.fixed_428.x = D_801245FC[wp->routine_6].x << 16;
        STAGE_PL.fixed_428.y = D_801245FC[wp->routine_6].y << 16;
        STAGE_PL.fixed_428.z = D_801245FC[wp->routine_6].z << 16;
        STAGE_PL.value_442   = D_801245FC[wp->routine_6].angle;
        Sce_event_timer_clear();
        func_8001E6C0(0, 0, 0);
        D_800BC7F0 = D_801247D8[wp->routine_6];
        Fade_start(1);
        wp->routine_4     = 3;
        wp->routine_8     = 1;
        wp->frame_10      = 0;
        wp->reserved09[0] = 0;
        wp->tbl_A4        = D_801247F4;
        Sce_flag_off(wp->routine_6 + 0x243);
    }
}

void func_80107AE8(void)
{
}

void func_80107AF0(STAGE_ROOM *wp)
{
    wp->tbl_A4        = D_801247E4;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->routine_7     = 0;
    wp->reserved09[1] = 0; // stored twice in retail
    Obj_work_flag_change(0x56, 5);
    wp->routine_6 = func_80107DB0();
    func_80107E08(wp);
}

void func_80107B54(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}
