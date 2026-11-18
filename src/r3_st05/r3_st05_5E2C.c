#include "common.h"
#include "st05.h"

void func_80105E2C(sint8 index)
{
    STAGE_SPAWNED *obj;

    if (stcom36_D_0000 & (0x80000000 >> index))
    {
        obj = stcom36_E2_0000[index];
        switch (func_8002FE74(obj->index_1))
        {
            case 0x20:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_3C0[obj->kind_2][obj->handler_4](obj);
                break;
            case 0x60:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_10C[obj->kind_2](obj);
                break;
        }
        stcom36_D_0000 &= ~(0x80000000 >> index);
    }
}

void func_80105F2C(sint8 index)
{
    STAGE_SPAWNED *obj;

    if (stcom36_D_0000 & (0x80000000 >> index))
    {
        obj = stcom36_E2_0000[index];
        switch (func_8002FE74(obj->index_1))
        {
            case 0x20:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_3C0[obj->kind_2][obj->handler_4](obj);
                break;
            case 0x60:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_10C[obj->kind_2](obj);
                break;
        }
        stcom36_D_0000 &= ~(0x80000000 >> index);
    }
}

void func_8010602C(uint8 index, uint8 kind)
{
    STAGE_REC *rec;

    rec           = &D_80137E18[index];
    rec->active_0 = 1;
    rec->value_2  = 0;
    rec->value_3  = 0;
    rec->data_4   = D_80130638[kind];
}

void func_80106074(uint8 index)
{
    D_80137E18[index].active_0 = 0;
}

void func_80106098(void)
{
    STAGE_REC *rec;
    sint32 i;

    for (i = 0, rec = D_80137E18; i < 8; i++)
    {
        rec->active_0 = 0;
        rec->index_1  = i;
        rec->value_2  = 0;
        rec->value_3  = 0;
        rec++;
    }
    rec->active_0 = 0;
}

void func_801060D4(STAGE_ROOM *wp)
{
    STAGE_CAM *cam;
    sint32 angle;

    cam = &D_800BC730;
    switch (wp->routine_4)
    {
        case 0:
            Sce_flag_on(0x7E0);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(&Player_work) != 0)
            {
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.pos_438.x   = 0x400;
                STAGE_PL.pos_438.y   = -1;
                STAGE_PL.pos_438.z   = 0x1D1F;
                STAGE_PL.fixed_428.x = 0x4000000;
                STAGE_PL.fixed_428.y = 0xFFFF0000;
                STAGE_PL.fixed_428.z = 0x1D1F0000;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.value_448   = 0;
                STAGE_PL.flags_bd |= 0x10;
                func_8001E6C0(0, 0, 0);
                cam->rot_40 = (STAGE_PL.rotation.y + 0x800) << 16;
                angle       = (uint16)STAGE_PL.rotation.y;
                angle += 0x800;
                angle &= 0xFFF;
                cam->pos_10 = STAGE_PL.fixed_428.x - rsin(angle) * 0x3840;
                cam->pos_18 = STAGE_PL.fixed_428.z - rcos(angle) * 0x3840;
                cam->rot_44 = 0x800000;
                cam->rot_48 = 0x2000000;
                cam->pos_14 = STAGE_PL.fixed_428.y - 0x2BC0000;
                wp->routine_4++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            MojiTaskExec2(0, 0x2F);
            wp->routine_4++;
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0x31);
                wp->routine_4++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                func_80042314(&Player_work);
                D_80137E78 = rand() % 24;
                wp->routine_4++;
            }
            break;
        case 6:
            cam->rot_40 = (Player_work.rotation.y + 0x800) << 16;
            angle       = (uint16)Player_work.rotation.y;
            angle += 0x800;
            angle &= 0xFFF;
            cam->pos_10 = Player_work.position_fixed.x - rsin(angle) * 0x3840;
            cam->pos_18 = Player_work.position_fixed.z - rcos(angle) * 0x3840;
            cam->pos_14 = Player_work.position_fixed.y - 0x2BC0000;
            break;
        case 7:
            if (func_80042238(&Player_work) != 0)
            {
                MojiTaskExec2(0, 0x35);
                wp->routine_4++;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x08000000))
            {
                D_800C356C = 1;
                D_800C356E = 8;
                D_800C356F = 2;
                D_800C3560 = -0x21;
                D_800C3562 = -0x41;
                D_800C3564 = 0x20F;
                D_800C356A = 0x800;
                D_800C356D = 0;
                D_800C3571 = 0xA;
                D_800C3570 = 2;
                wp->routine_4++;
            }
            break;
        case 9:
            if (D_800C356C_A[0] == 2)
            {
                D_800C356C_A[0]++;
                Sce_flag_off(0x7E0);
                Sce_flag_off(0x208);
                func_80042314(&Player_work);
                D_800A395C = 1;
                func_80039820();
                wp->flags_0 = 0;
            }
            break;
    }
}

void func_80106514(void)
{
}

void func_8010651C(void)
{
}

void func_80106524(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80106564(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_80017C30(0xA);
            wp->routine_4++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 2:
            D_800C356C  = 2;
            D_800C356E  = 0xF;
            D_800C356F  = 1;
            D_800C3560  = -0x40;
            D_800C3562  = -1;
            D_800C3564  = 0xD0;
            D_800C356A  = 0x400;
            D_800C356D  = 0;
            D_800C3571  = 0xFF;
            D_800C3570  = 2;
            wp->flags_0 = 0;
            break;
    }
}

void func_80106670(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0)
    {
        MojiTaskExec2(0, 0x78);
    }
    if (!(Moji_flag & 0x08000000))
    {
        func_80017C30(9);
        wp->routine_2 = 0;
        func_8001F158();
    }
}

void func_801066D4(STAGE_ROOM *wp)
{
    if (D_80098A72 == 0)
    {
        func_8001EAE8(D_80130774);
        STAGE_PL.pos_438.x   = -0x100;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = 0xB00;
        STAGE_PL.fixed_428.x = 0xFF000000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0x0B000000;
        STAGE_PL.value_442   = 0x200;
        wp->routine_7        = 1;
        func_8001E6C0(0, 0, 0);
        D_800BC7F0 = D_80130788;
        func_80017C30(1);
        func_8001F158();
    }
}

void func_801067A0(STAGE_OBJ *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_2 = 1;
        func_8001F158();
    }
}

void func_801067D0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 1)
    {
        MojiTaskExec2(0, 0x79);
        child               = wp->child_24;
        child->u_E.b.byte_E = 8;
        child               = wp->child_24;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x3D)
    {
        func_8001F158();
    }
}

void func_80106840(STAGE_OBJ *wp)
{
    if (!(Moji_flag & 0x08000000) && (wp->value_10 >= 0xB6))
    {
        func_80017C30(9);
        wp->routine_2 = 0;
        func_8001F158();
    }
}

void func_8010689C(void)
{
}

void func_801068A4(STAGE_ROOM *wp)
{
    wp->tbl_A4        = D_801307FC;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->routine_7     = 0;
    wp->reserved09[1] = 0; // stored twice in retail
    Obj_work_flag_change(0x56, 5);
    Sce_flag_off(0x246);
}

void func_801068F4(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80106934(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            func_801068A4(wp);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(pl))
            {
                STAGE_PL.routine_0 = 3;
                STAGE_PL.routine_1 = 0;
                pl->value_448      = 0x30;
                wp->routine_4++;
                func_80017C30(1);
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            if (wp->routine_8 == 0xFF)
            {
                goto next;
            }
            if (func_8001DE84() && wp->reserved09[1] == 1 && D_80098A72 == 0)
            {
                func_80053AA4(0);
                func_80017C30(9);
            next:
                wp->routine_4++;
                break;
            }
            func_801068F4((STAGE_ROOM_WORK *)wp);
            if (wp->routine_7 != 0)
            {
                func_8001EC0C();
            }
            func_8001F070();
            break;
        case 4:
            if (D_80098A72 == 0)
            {
                func_80017C30(1);
                D_800A395C = 1;
                func_80039820();
                wp->routine_4++;
                func_80031824(wp->child_24);
                Obj_work_flag_change(0x56, 0xA);
                func_8001E3F0(0xF);
                func_80039820();
            }
            break;
        case 5:
            if (D_80098A72 == 0)
            {
                func_80042314(&Player_work);
                wp->flags_0 = 0;
            }
            break;
    }
}

void func_80106B28(void)
{
    func_8001E4C4(D_801309B4, D_801309BC[STAGE_GAME_VALUE_52]);
    if (STAGE_GAME_VALUE_52 == 0)
    {
        if (Sce_flag_test(1))
        {
            func_8001E4C4(D_801309B4, D_801309BC[13]);
        }
        else if (Sce_flag_test(2))
        {
            func_8001E4C4(D_801309B4, D_801309BC[12]);
        }
    }
    if ((uint8)(STAGE_GAME_VALUE_52 - 9) < 2 && Game_work.value_51 == 0)
    {
        func_80107DB4();
    }
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_80106C08(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        if (STAGE_GAME_VALUE_52 != 0xB)
        {
            D_80130970[Game_work.value_51](&D_800989F8);
        }
        else
        {
            Sce_flag_on(0x1FF);
        }
    }
    if (Sce_flag_test(0x1FF))
    {
        D_80130930[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80106CCC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80107D68() != 0)
            {
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x208))
            {
                func_8001DDE4(0x50);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(2))
            {
                stcom36_func_0028(2);
                if (Sce_flag_test(1))
                {
                    func_80105E2C(1);
                    func_80105E2C(2);
                    wp->routine_4 = 0xFF;
                }
                else
                {
                    func_801016F0();
                    wp->routine_4 = 1;
                }
            }
            else if (Sce_flag_test(5))
            {
                stcom36_func_0028(1);
                wp->routine_4 = 0xFF;
            }
            else
            {
                func_8001DDE4(0xC);
                STAGE_SCENE_BYTE(4) = 0;
                wp->routine_4       = 0xFF;
            }
            break;
        case 1:
            if (Sce_flag_test(0x641) || Sce_flag_test(0x642))
            {
                func_8001DDE4(5);
                Sce_flag_on(1);
                func_8001E4C4(D_801309B4, D_80130A24);
                wp->routine_4 = 0xFF;
                func_80105E2C(1);
                func_80105E2C(2);
            }
            break;
        case 2:
            break;
    }
}

void func_80106E38(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8003AC9C(func_80048C60(&D_80130A3C), 0xB0E00);
            if (Sce_flag_test(0x59))
            {
                wp->routine_4 = 5;
            }
            else if (Sce_flag_test(9))
            {
                wp->routine_4 = 3;
            }
            else
            {
                func_8001DDE4(0xE);
                func_8001E4C4(D_801309B4, D_80130A2C);
                Scene_work.reserved00[4] = 1;
                func_80107CEC();
                wp->routine_4++;
            }
            break;
        case 1:
            if (Sce_flag_test(0x611))
            {
                func_8001DDE4(0xE);
                Scene_work.reserved00[4] = 2;
                wp->routine_4++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x620))
            {
                Sce_flag_on(0x621);
                func_8001DDE4(6);
                wp->routine_4++;
            }
            break;
        case 3:
            func_8001E4C4(D_801309B4, D_80130A2C);
            wp->routine_4++;
            break;
        case 4:
            if (Sce_flag_test(0x660))
            {
                Sce_flag_on(0x59);
                func_8001DDE4(7);
                wp->routine_4++;
            }
            break;
        case 5:
            stcom36_func_0028(6);
            func_8001E4C4(D_801309B4, D_80130A34);
            wp->routine_4 = 0xFF;
            break;
        case 0xFF:
            break;
    }
}

void func_80107010(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(7);
        wp->routine_4 = 0xFF;
    }
}

void func_80107054(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(8);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(3);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_801070D0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(7);
        stcom36_func_0028(0x18);
        wp->routine_4 = 0xFF;
    }
}

void func_8010711C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(9);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(7);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80107198(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xB);
        wp->routine_4 = 0xFF;
    }
}

void func_801071DC(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(9);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(7);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80107258(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xB);
        wp->routine_4 = 0xFF;
    }
}

void func_8010729C(void)
{
}

void func_801072A4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(0xA);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(8);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80107320(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xC);
        wp->routine_4 = 0xFF;
    }
}

void func_80107364(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(10);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(8);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_801073E0(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xC);
        stcom36_func_0028(0x19);
        wp->routine_4 = 0xFF;
    }
}

void func_8010742C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(0xD);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(0);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_801074A8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xE);
        stcom36_func_0028(0x19);
        wp->routine_4 = 0xFF;
    }
}

void func_801074F4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(0xD);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(0);
            }
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80107570(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0xE);
        wp->routine_4 = 0xFF;
    }
}

void func_801075B4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(0xF);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(0);
            }
        }
        if (Sce_flag_test(0x209) && !Sce_flag_test(0x211))
        {
            func_80105E2C(5);
            func_80105E2C(6);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80107660(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x10);
        wp->routine_4 = 0xFF;
    }
}

void func_801076A4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1A);
        wp->routine_4 = 0xFF;
    }
}

void func_801076E8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(0x11);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(0);
            }
        }
        if (Sce_flag_test(0x209) && !Sce_flag_test(0x211))
        {
            func_80105E2C(5);
            func_80105E2C(6);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80107794(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x12);
        wp->routine_4 = 0xFF;
    }
}

void func_801077D8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1A);
        wp->routine_4 = 0xFF;
    }
}

void func_8010781C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (func_80107D68() == 0)
        {
            stcom36_func_0028(0x13);
            if (func_80048E18(D_80130984) == 0x100)
            {
                func_80105E2C(0);
            }
        }
        if (Sce_flag_test(0x209) && !Sce_flag_test(0x211))
        {
            func_80105E2C(5);
            func_80105E2C(6);
        }
        wp->routine_4 = 0xFF;
    }
}

void func_801078C8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x14);
        wp->routine_4 = 0xFF;
    }
}

void func_8010790C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x1B);
        wp->routine_4 = 0xFF;
    }
}

void func_80107950(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        stcom36_func_0028(0x15);
        if (Sce_flag_test(0x234))
        {
            func_80105E2C(5);
            func_80105E2C(7);
        }
        else
        {
            func_80105E2C(4);
            func_80105E2C(6);
        }
        Sce_flag_on(0x6F);
        wp->routine_4 = 0xFF;
    }
}

sint32 func_801079D0(STAGE_ROOM *wp)
{
    ST05_OBJ *obj;

    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x200) != 0)
            {
                break;
            }
            if (Sce_flag_test(0x204) != 0 && Sce_flag_test(0x206) == 0)
            {
                func_8001EB98(D_8013776C);
                func_8001EB98(&D_80137780[STAGE_FRAME & 3]);
                func_8001EB98(&D_801377D0[(STAGE_FRAME & 0x30) >> 4]);
                stcom36_func_0028(0x16);
                Sce_flag_on(0x7E0);
                wp->routine_4 = 0xFE;
                return 1;
            }
            if (Sce_flag_test(0x212) != 0 && Sce_flag_test(0x213) == 0)
            {
                obj            = func_8001EB98(&D_8013232C[0]);
                obj->u_B8.part = func_8001EB98(&D_8013232C[1]);
                stcom36_func_0028(0x17);
                Sce_flag_on(0x235);
                Sce_flag_on(0x7E0);
                wp->routine_4 = 0xA;
                return 1;
            }
            if (Sce_flag_test(0x209) != 0 && Sce_flag_test(0x211) == 0)
            {
                func_8001EB98(&D_8013098C[0]);
                if (Sce_flag_test(0x20D) != 0)
                {
                    func_8001EB98(&D_8013098C[1]);
                }
                wp->routine_4 = 0xFF;
                break;
            }
            if (Sce_flag_test(0x246) != 0 && Sce_flag_test(0x200) == 0 && STAGE_GAME.value_52 < 0xB)
            {
                func_8001DDE4(0x58);
                return 1;
            }
            break;
        case 0xA:
            if (Sce_flag_test(0x679) != 0)
            {
                if (Moji_flag & 0x08000000)
                {
                    return 1;
                }
                if (!(Moji_flag & 0xFF))
                {
                    Sce_flag_off(0x7E0);
                    Sce_flag_off(0x235);
                    Sce_flag_on(0x24A);
                    Sce_flag_on(0x213);
                    Sce_flag_on(0x214);
                    func_8001E390(0x2E4);
                    func_8001E3F0(6);
                    STAGE_GAME.value_78 = 1;
                }
                else
                {
                    Sce_flag_off(0x679);
                    return 1;
                }
            }
            else
            {
                if (Sce_flag_test(0x213) == 0)
                {
                    return 1;
                }
                func_8001DDE4(0x52);
            }
            wp->routine_4 = 0xFE;
            return 1;
        case 0xFE:
            return 1;
        case 0xFF:
            Sce_flag_on(0x1FF);
            break;
    }
    wp->routine_4 = 0;
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80107CC8(STAGE_ROOM *wp)
{
    wp->routine_4 = 0;
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80107CEC(void)
{
    STAGE_OBJ *op;
    sint8 i;

    for (i = 0; i < 2; i++)
    {
        op = func_80031418();
        if (op != NULL)
        {
            op->flags_0      = 1;
            op->kind_2       = 0x32;
            op->value_4      = 0;
            op->variant_3    = 0;
            op->u_C.b.byte_C = i;
        }
    }
}

uint8 func_80107D68(void)
{
    STAGE_50 *slot;

    if (!Sce_flag_test(0x200))
    {
        return 0;
    }
    slot = func_80031734();
    if (slot != NULL)
    {
        slot->flags_0 = 1;
        slot->kind_2  = 0x32;
    }
    return 1;
}

void func_80107DB4(void)
{
    STCOM_SVECTOR pos = {-0x100, 0, 0x1B00, 0};

    func_8003AC9C(func_80048C60(&pos), 0x80100000);
}

void func_80107E08(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    if (STCOM_STAGE_ROOM == 5)
    {
        stcom01_func_0000((ST05_ACTOR_B *)wp);
        return;
    }
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_80130A44[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if ((wp->flags_0 & 2) && !(ctl->flags_0 & 0x20))
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 2))
    {
        ctl->pos_C = wp->position;
        ctl->pos_C.y -= 0x28;
        func_800341BC(&ctl->pos_C, 0x28, 0, 0x8000, wp->value_1, &ctl->hit_14,
                      ctl->value_8 | 0x4000000, 0x800000, 0x80);
    }
    ctl->hit_14 = 0;
}

void func_80107FF0(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint16 life;

    ctl = &wp->ctl;
    wp->flags_0 |= 2;
    if ((wp->variant_3 & 0xF0) != 0x50)
    {
        wp->rotation.x = 0;
        wp->rotation.z = 0;
        wp->rotation.y = (wp->timer_C << 9) & 0xE00;
    }
    *(uint32 *)&wp->turn_64 = 0;
    wp->timer_C &= 0xF0;
    func_8002F9C4(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    ctl->flags_0             = 0xE;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    ctl->hit_14              = 0;
    ctl->value_18            = 0;
    func_80036478(ctl->track_24, 0, -0x60);
    ctl->range_34 = 0x7FFFFFFF;
    life          = D_80098844[wp->kind_2]->life_8;
    wp->value_78  = 0;
    wp->value_6E  = life;
    wp->value_B0  = life;
    wp->value_B2  = life;
    if ((wp->variant_3 & 0xF0) != 0x50)
    {
        wp->position.y       = func_80048E6C(wp);
        wp->position_fixed.y = wp->position.y << 16;
    }
    wp->routine_0 = 1;
    switch (wp->variant_3 & 0xF0)
    {
        case 0:
            wp->routine_1 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 0x10:
            wp->routine_1 = 0xE;
            func_800322A8(wp, 1, 0);
            break;
        case 0x20:
            wp->routine_1 = 0xD;
            func_800322A8(wp, 0xC, 0);
            break;
        case 0x30:
            wp->routine_1 = 0x10;
            wp->flags_0 &= ~2;
            ctl->flags_0 = (ctl->flags_0 & ~6) | 0x20;
            func_800322A8(wp, 0xA, 0);
            break;
        case 0x40:
            wp->routine_1 = 0xF;
            wp->value_D   = 0;
            wp->flags_0 &= ~2;
            ctl->flags_0 = (ctl->flags_0 & ~6) | 0x20;
            func_800322A8(wp, 0, 0);
            break;
        case 0x50:
            wp->routine_1 = 0xB;
            func_800322A8(wp, 0x25, 0);
            break;
    }
    *(uint16 *)&wp->routine_2 = 0;
    wp->variant_3 &= 0xF;
    if (wp->timer_C != 0)
    {
        ctl->other_38 = (ST05_HELD *)func_80031518();
        if (ctl->other_38 != NULL)
        {
            ctl->other_38->flags_0          = 1;
            ctl->other_38->kind_2           = 6;
            ctl->other_38->variant_3        = 0x80;
            ctl->other_38->position.x       = wp->position.x;
            ctl->other_38->position.y       = wp->position.y - 0x64;
            ctl->other_38->position.z       = wp->position.z;
            ctl->other_38->position_fixed.x = ctl->other_38->position.x << 16;
            ctl->other_38->position_fixed.y = ctl->other_38->position.y << 16;
            ctl->other_38->position_fixed.z = ctl->other_38->position.z << 16;
            ctl->other_38->routine_0        = 4;
            ctl->other_38->value_9C         = 0x20;
            ctl->other_38->value_A0         = 0x10;
        }
    }
    wp->scale.v.pad = 0x4210;
}

void func_80108324(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;

    ctl = &wp->ctl;
    if (ctl->flags_0 & 4)
    {
        func_8010A608(wp);
    }
    D_80130A50[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 8:
                func_80031824(wp);
                break;
            case 5:
            case 6:
            case 7:
                if (wp->variant_3 < 2 && wp->timer_C == 0)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 2;
                }
                break;
            case 9:
            case 10:
            case 11:
                if (wp->value_6E > 0)
                {
                    wp->spin_66   = 0x80;
                    wp->routine_1 = 5;
                }
                else
                {
                    ctl->flags_0 &= ~4;
                    wp->routine_1 = 8;
                }
                break;
            case 13:
            case 14:
                if (wp->value_D != 0)
                {
                    wp->value_D--;
                    break;
                }
                // fall through
            default:
                if (ctl->flags_0 & 0x10)
                {
                    if (wp->variant_3 < 2 && wp->timer_C == 0)
                    {
                        wp->routine_1 = 3;
                    }
                    else
                    {
                        wp->routine_1 = 2;
                    }
                }
                else if (wp->variant_3 & 1)
                {
                    wp->routine_1 = 0;
                }
                else
                {
                    wp->routine_1 = 1;
                    func_8010A508(wp);
                }
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (wp->timer_C != 0)
    {
        ctl->other_38->position.x       = wp->position.x;
        ctl->other_38->position.y       = wp->position.y - 0x64;
        ctl->other_38->position.z       = wp->position.z;
        ctl->other_38->position_fixed.x = ctl->other_38->position.x << 16;
        ctl->other_38->position_fixed.y = ctl->other_38->position.y << 16;
        ctl->other_38->position_fixed.z = ctl->other_38->position.z << 16;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
}

void func_80108590(ST05_OBJ *wp)
{
    if (wp->u_C.b.byte_C != 0)
    {
        wp->value_380->routine_0 = 0;
    }
    func_80031824(wp);
}

void func_801085CC(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    ST05_SPARK *ep;
    sint16 i;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->ctl.timer_4 = 0x40;
            wp->accel_4C.y  = 0x40;
            wp->ctl.value_6 = 0;
            wp->timer_C     = 0;
            wp->anim_AC     = 0;
            wp->accel_4C.x  = 0x30;
            wp->ctl.flags_0 &= ~2;
            for (i = 0; i < 6; i++)
            {
                ep = func_80031618();
                if (ep == NULL)
                {
                    break;
                }
                ep->flags_0 = 3;
                ep->kind_2  = 0x83;
                ep->x_1C    = wp->value_180[i].x;
                ep->y_1E    = wp->value_180[i].y;
                ep->z_20    = wp->value_180[i].z;
            }
            wp->value_FB  = -1;
            wp->value_103 = -1;
            wp->value_107 = -1;
            wp->value_10B = -1;
            wp->value_10F = -1;
            func_80047148(wp, wp->value_180);
            // fall through
        case 1:
            t            = (uint16)ctl->timer_4 - 1;
            ctl->timer_4 = t;
            if ((sint16)t <= 0)
            {
                wp->routine_2 = 2;
            }
            else
            {
                wp->velocity.v.y = ((uint16)wp->accel_4C.x - t) * 2;
            }
            // fall through
        case 2:
            wp->flags_0 |= 2;
            ctl->value_6 = (ctl->value_6 + 1) & 3;
            if (wp->value_6E <= 0 && ctl->value_6 == 0)
            {
                wp->flags_0 &= ~2;
            }
            func_8002FEA4(wp, 0, wp->velocity.v.y << 4, 0);
            wp->position.y -= 0x34;
            wp->position_fixed.y = wp->position.y << 16;
            if (func_8004B414(wp) & 0x1000)
            {
                if (++wp->routine_3 == 3)
                {
                    ctl->timer_4  = 0x16;
                    wp->routine_2 = 3;
                }
                else
                {
                    wp->routine_2 = 1;
                    wp->flags_0 |= 2;
                    wp->accel_4C.x >>= 1;
                    wp->accel_4C.y >>= 1;
                    ctl->timer_4 = wp->accel_4C.y;
                }
            }
            wp->position.y += 0x34;
            wp->position_fixed.y = wp->position.y << 16;
            break;
        case 3:
            wp->flags_0 ^= 2;
            if (--wp->ctl.timer_4 < 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
    }
}

void func_80108888(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 0x78;
            wp->routine_2   = 1;
            wp->anim_AC     = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801088F4(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.timer_4 = 0x5A;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                break;
            }
            wp->rotation.y = (wp->rotation.y + wp->spin_66) & 0xFFF;
            func_8002FEA4(wp, 0x30, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            break;
    }
}

void func_80108A54(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0xA;
            wp->ctl.timer_4 = 0xF;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                break;
            }
            func_8002FEA4(wp, 0x80, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            break;
    }
}

void func_80108BA4(ST05_VILLAGER *wp)
{
    STCOM_PL_WORK *pl;
    ST05_VILLAGER_CTL *ctl;
    sint16 turn;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.x = 8;
            wp->spin_66      = 0x10;
            if (wp->timer_C != 0)
            {
                ctl->range_34 = 0x80000;
                wp->anim_AC   = 9;
            }
            else
            {
                ctl->range_34 = 0x8000;
                wp->anim_AC   = 2;
            }
            // fall through
        case 1:
            if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 |= 1;
                break;
            }
            if (func_80031E60(&pl->position_fixed, pl->rotation.y, 0x800, &wp->position_fixed,
                              wp->rotation.y, 0x400))
            {
                wp->spin_66               = 0x80;
                wp->routine_1             = 5;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            turn = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, wp->spin_66);
            if (STCOM_ABS(turn) < 0x10 && wp->value_80 < ctl->range_34)
            {
                if (wp->timer_C != 0)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 7;
                }
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            func_8002FEA4(wp, wp->velocity.v.x * 16, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            break;
    }
}

void func_80108DFC(ST05_VILLAGER *wp)
{
    STCOM_PL_WORK *pl;
    ST05_VILLAGER_CTL *ctl;
    sint16 turn;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.x = 0xC;
            wp->spin_66      = 0x18;
            wp->anim_AC      = 9;
            if (wp->timer_C != 0)
            {
                ctl->range_34 = 0x80000;
            }
            else
            {
                ctl->range_34 = 0x8000;
            }
            // fall through
        case 1:
            if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 |= 1;
                break;
            }
            turn = func_80031BEC(&wp->position, &pl->position, wp->rotation.y, wp->spin_66);
            turn = STCOM_ABS(turn);
            if (turn < 0x10 && wp->value_80 < ctl->range_34)
            {
                if (wp->timer_C != 0)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 7;
                }
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            wp->rotation.y = (wp->rotation.y + func_80031BEC(&pl->position, &wp->position,
                                                             wp->rotation.y, wp->spin_66)) &
                             0xFFF;
            func_8002FEA4(wp, wp->velocity.v.x << 4, 0, 0);
            hit                  = func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            else if (!(ctl->value_2 & 0x1FF))
            {
                wp->routine_1             = 0xA;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void func_80109028(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + wp->spin_66) & 0xFFF;
            }
            break;
    }
}

void func_801090AC(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;
    sint32 turn;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC     = 1;
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (wp->variant_3 < 2 && wp->timer_C == 0)
            {
                turn =
                    func_80031BEC(&STAGE_PL.position, &wp->position, wp->rotation.y, wp->spin_66);
            }
            else
            {
                turn =
                    func_80031BEC(&wp->position, &STAGE_PL.position, wp->rotation.y, wp->spin_66);
            }
            if ((sint16)turn == 0)
            {
                ctl->flags_0 |= 1;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            }
            break;
    }
}

void func_80109198(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 15;
            wp->anim_AC     = 0x30;
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->other_38->routine_0 = 0;
            ctl->other_38->turn_64   = wp->rotation.y;
            ctl->other_38->value_9C  = 0x20;
            ctl->other_38->value_A0  = 0x10;
            wp->timer_C              = 0;
            ctl->timer_4             = 8;
            wp->routine_2            = 2;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80109288(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    if (wp->ctl.hit_14 & 0x2000000)
    {
        wp->ctl.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            ctl->timer_4  = 0xF;
            wp->anim_AC   = 0x15;
            wp->routine_2 = 1;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2    = 2;
            wp->anim_AC      = 0x18;
            wp->velocity.v.x = 0xF;
            ctl->timer_4     = 0xF;
            ctl->value_8     = D_80098844[wp->kind_2]->life_A[0];
            // fall through
        case 2:
            ctl->timer_4--;
            if (ctl->hit_14 & 0x2000000)
            {
                wp->velocity.v.x = 0;
            }
            t                = 8 - (uint16)ctl->timer_4;
            wp->velocity.v.y = t * 4;
            func_8002FEA4(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if (hit & 0x1000)
                {
                    ctl->timer_4  = 0xF;
                    ctl->value_8  = 0;
                    wp->anim_AC   = 0x17;
                    wp->routine_2 = 3;
                }
            }
            break;
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 4;
                ctl->timer_4  = 0x12;
                wp->anim_AC   = 0x23;
            }
            else if (wp->velocity.v.x != 0)
            {
                wp->velocity.v.x--;
            }
            func_8002FEA4(wp, wp->velocity.v.x << 4, 0, 0);
            func_8004B414(wp);
            wp->position.y       = func_80048E6C(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            break;
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80109510(ST05_ACTOR *wp)
{
    ST05_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 10;
            wp->routine_2   = 1;
            wp->anim_AC     = 0x20;
            wp->ctl.value_8 = 0;
            wp->frame_110   = 7;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->timer_4  = 10;
                wp->anim_AC   = 8;
                wp->frame_110 = 6;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_801095E0(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.value_8  = 0;
            wp->ctl.timer_4  = 4;
            wp->routine_2    = 1;
            wp->anim_AC      = 0x21;
            wp->velocity.v.x = 0xD;
            wp->velocity.v.y = -0x18;
            wp->value_110    = 7;
            wp->ctl.flags_0 &= ~8;
            wp->rotation.y &= 0xFFF;
            if (wp->timer_C != 0)
            {
                wp->ctl.other_38->routine_0 = 0;
                wp->ctl.other_38->turn_64   = wp->rotation.y;
                wp->ctl.other_38->value_9C  = 0x20;
                wp->ctl.other_38->value_A0  = 0x10;
                wp->timer_C                 = 0;
            }
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    func_8002FEA4(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    func_8004B414(wp);
                }
                break;
            }
            ctl->timer_4  = 7;
            wp->routine_2 = 2;
            wp->anim_AC   = 0x22;
            // fall through
        case 2:
            t = (uint16)ctl->timer_4;
            t--;
            ctl->timer_4     = t;
            wp->velocity.v.y = (4 - t) * 8;
            func_8002FEA4(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if ((hit & 0x1000) && ctl->timer_4 <= 0)
                {
                    ctl->timer_4  = 0x12;
                    wp->routine_2 = 3;
                    wp->anim_AC   = 0x23;
                }
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->ctl.flags_0 |= 1;
                wp->value_110 = 6;
                wp->ctl.flags_0 |= 8;
            }
            break;
    }
    wp->flags_0 |= 2;
    ctl->value_6 = (ctl->value_6 + 1) & 3;
    if (wp->value_6E <= 0 && ctl->value_6 == 0)
    {
        wp->flags_0 &= ~2;
    }
}

void func_8010984C(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            ctl->timer_4 = 4;
            ctl->value_6 = 0;
            ctl->value_8 = 0;
            ctl->flags_0 &= ~8;
            wp->routine_2    = 1;
            wp->anim_AC      = 0x25;
            wp->velocity.v.x = -0xB;
            wp->velocity.v.y = -0x18;
            wp->value_110    = 7;
            wp->rotation.y &= 0xFFF;
            if (wp->timer_C != 0)
            {
                ctl->other_38->routine_0 = 0;
                ctl->other_38->turn_64   = (wp->rotation.y + 0x800) & 0xFFF;
                ctl->other_38->value_9C  = 0x20;
                ctl->other_38->value_A0  = 0x10;
                wp->timer_C              = 0;
            }
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    func_8002FEA4(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    func_8004B414(wp);
                }
                break;
            }
            ctl->timer_4  = 0xB;
            wp->routine_2 = 2;
            wp->anim_AC   = 0x26;
            // fall through
        case 2:
            t = (uint16)ctl->timer_4;
            t--;
            ctl->timer_4     = t;
            wp->velocity.v.y = (8 - t) * 8;
            func_8002FEA4(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if ((hit & 0x1000) && ctl->timer_4 <= 0)
                {
                    ctl->timer_4  = 0x26;
                    wp->routine_2 = 3;
                    wp->anim_AC   = 0x27;
                }
            }
            break;
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = 0x11;
            wp->routine_2 = 4;
            wp->anim_AC   = 0x28;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                wp->value_110 = 6;
                ctl->flags_0 |= 8;
            }
            break;
    }
    wp->flags_0 |= 2;
    ctl->value_6 = (ctl->value_6 + 1) & 3;
    if (wp->value_6E <= 0 && ctl->value_6 == 0)
    {
        wp->flags_0 &= ~2;
    }
}

void func_80109AE4(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            ctl->timer_4     = 5;
            ctl->value_8     = 0;
            wp->routine_2    = 1;
            wp->anim_AC      = 0x10;
            wp->velocity.v.x = 8;
            wp->velocity.v.y = -0xE;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = 0xE;
            wp->routine_2 = 2;
            wp->anim_AC   = 0x11;
            // fall through
        case 2:
            t            = (uint16)ctl->timer_4 - 1;
            ctl->timer_4 = t;
            if ((sint16)t < 0)
            {
                wp->routine_2    = 3;
                wp->velocity.v.x = 0;
            }
            else
            {
                wp->velocity.v.y = (7 - t) * 2;
            }
            // fall through
        case 3:
            if (wp->routine_2 == 3)
            {
                t = (uint16)ctl->timer_4;
                t--;
                ctl->timer_4     = t;
                wp->velocity.v.y = (7 - t) * 2;
            }
            func_8002FEA4(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = func_8004B414(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if (hit & 0x1000)
                {
                    if (!(ctl->value_2 & 0xF))
                    {
                        ctl->timer_4  = 0xE;
                        wp->routine_2 = 4;
                        wp->anim_AC += 3;
                        if (wp->timer_C != 0)
                        {
                            ctl->other_38->routine_0 = 0;
                            ctl->other_38->turn_64   = (wp->rotation.y + 0x800) & 0xFFF;
                            ctl->other_38->value_9C  = 0x20;
                            ctl->other_38->value_A0  = 0x10;
                            wp->timer_C              = 0;
                        }
                        wp->value_110 = 7;
                    }
                    else
                    {
                        ctl->timer_4  = 7;
                        wp->routine_2 = 5;
                        wp->anim_AC += 2;
                    }
                }
            }
            break;
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->value_110 = 6;
            ctl->timer_4  = 0x26;
            wp->routine_2 = 5;
            wp->anim_AC   = 0x28;
            // fall through
        case 5:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80109D44(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 14;
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            wp->anim_AC     = 0xC;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = (ctl->value_2 & 0x1F) + 8;
            wp->routine_2 = 2;
            wp->anim_AC   = 0xD;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = 7;
            wp->routine_2 = 3;
            wp->anim_AC   = 0xE;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
    if (ctl->flags_0 & 0x10)
    {
        wp->value_D = 0;
        ctl->flags_0 |= 1;
    }
}

void func_80109E70(uint8 *arg0)
{
    *arg0 &= 0xFD;
}

void func_80109E84(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            break;
        case 1:
            wp->routine_2 = 2;
            wp->anim_AC   = 0x11;
            wp->flags_0 |= 2;
            ctl->timer_4  = 8;
            ctl->value_8  = 0;
            wp->value_10B = -1;
            wp->value_10F = -1;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 3;
                wp->anim_AC   = 0xA;
            }
            else
            {
                wp->position.y -= 4;
            }
            break;
        case 3:
            break;
        case 4:
            wp->routine_2 = 5;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = 8;
            // fall through
        case 5:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 6;
                wp->flags_0 &= ~2;
            }
            else
            {
                wp->position.y += 8;
            }
            break;
    }
}

void func_80109F84(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->value_D      = 0;
            wp->ctl.other_38 = (ST05_HELD *)func_80031518();
            if (wp->ctl.other_38 == NULL)
            {
                wp->routine_1             = 0xF;
                *(uint16 *)&wp->routine_2 = 0;
                wp->value_D               = 1;
                break;
            }
            wp->ctl.other_38->flags_0   = 1;
            wp->ctl.other_38->routine_0 = 4;
            wp->ctl.other_38->kind_2    = 6;
            wp->ctl.other_38->variant_3 = 0x80;
            wp->anim_AC                 = 0x30;
            wp->ctl.timer_4             = 0xF;
            wp->routine_2               = 1;
            wp->ctl.value_8             = 0;
            wp->value_10B               = -1;
            wp->value_10F               = -1;
            wp->flags_0 |= 2;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y =
                    (wp->rotation.y +
                     func_80031BEC(&wp->position, &Player_work.position, wp->rotation.y, 0x40)) &
                    0xFFF;
                wp->position.y -= 4;
                wp->position_fixed.y            = wp->position.y << 16;
                ctl->other_38->position.x       = wp->position.x;
                ctl->other_38->position.y       = wp->position.y - 0x64;
                ctl->other_38->position.z       = wp->position.z;
                ctl->other_38->position_fixed.x = ctl->other_38->position.x << 16;
                ctl->other_38->position_fixed.y = ctl->other_38->position.y << 16;
                ctl->other_38->position_fixed.z = ctl->other_38->position.z << 16;
                break;
            }
            ctl->other_38->routine_0 = 0;
            ctl->other_38->turn_64   = wp->rotation.y;
            ctl->other_38->value_9C  = 0x18;
            ctl->other_38->value_A0  = 8;
            wp->timer_C              = 0;
            ctl->timer_4             = 8;
            wp->routine_2            = 2;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = 8;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_1             = 0xF;
                *(uint16 *)&wp->routine_2 = 0;
                wp->value_D               = 1;
                wp->flags_0 &= ~2;
            }
            else
            {
                wp->position.y += 8;
                wp->position_fixed.y = wp->position.y << 16;
            }
            break;
    }
}

void func_8010A21C(ST05_VILLAGER *wp)
{
    ST05_VILLAGER *held;
    ST05_VILLAGER_CTL *ctl;

    held = (ST05_VILLAGER *)D_80138094;
    ctl  = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0x30;
            wp->value_10B   = -1;
            wp->value_10F   = -1;
            wp->ctl.timer_4 = 0xF;
            wp->value_D     = 0;
            wp->ctl.value_8 = 0;
            wp->flags_0 |= 2;
            held->routine_1             = 5;
            *(uint16 *)&held->routine_2 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y =
                    (wp->rotation.y + func_80031BEC(&wp->position,
                                                    &ST05_VILLAGERS[wp->value_E]->position,
                                                    wp->rotation.y, 0x40)) &
                    0xFFF;
                wp->position.y -= 4;
                wp->position_fixed.y   = wp->position.y << 16;
                held->position.x       = wp->position.x;
                held->position.y       = wp->position.y - 0x50;
                held->position.z       = wp->position.z;
                held->position_fixed.x = held->position.x << 16;
                held->position_fixed.y = held->position.y << 16;
                held->position_fixed.z = held->position.z << 16;
                held->rotation.y       = wp->rotation.y;
                break;
            }
            wp->routine_2                         = 2;
            wp->timer_C                           = 0;
            ctl->timer_4                          = 8;
            held->routine_1                       = 2;
            *(uint16 *)&held->routine_2           = 0;
            ST05_VILLAGERS[wp->value_E]->value_C4 = ST05_VILLAGERS[wp->value_E]->value_180[0];
            ST05_VILLAGERS[wp->value_E]->value_C4.y -= 0x140;
            func_80030934(held, ST05_VILLAGERS[wp->value_E], 0x18, 0);
            ST05_VILLAGERS[ST05_VILLAGERS[wp->value_E]->value_D]->value_F &= ~0x40;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = 8;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_1             = 0xF;
                *(uint16 *)&wp->routine_2 = 0;
                wp->value_D               = 1;
                wp->flags_0 &= ~2;
            }
            else
            {
                wp->position.y += 8;
                wp->position_fixed.y = wp->position.y << 16;
            }
            break;
    }
}

sint32 func_8010A508(ST05_VILLAGER *wp)
{
    ST05_VILLAGER_CTL *ctl;
    uint8 *tbl;
    sint16 sum;
    sint16 i;

    ctl = &wp->ctl;
    tbl = D_80130AA4;
    if (wp->variant_3 & 1)
    {
        tbl = D_80130A9C;
    }
    sum = 0;
    for (i = 0; i < 6; i++)
    {
        sum += *tbl;
        if ((wp->ctl.value_2 & 0xF) < sum)
        {
            break;
        }
        tbl++;
    }
    switch (i)
    {
        case 0:
            wp->spin_66 = 0;
            break;
        case 1:
            wp->spin_66 = 6;
            break;
        case 2:
            wp->spin_66 = -6;
            break;
        case 3:
            wp->routine_1             = 4;
            wp->spin_66               = 0x10;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->timer_4              = 0x40;
            break;
        case 4:
            wp->routine_1             = 4;
            wp->spin_66               = -0x10;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->timer_4              = 0x40;
            break;
        default:
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
    return 1;
}

sint32 func_8010A608(ST05_VILLAGER *wp)
{
    STCOM_SVECTOR origin = {0, 0, 0, 0};
    ST05_VILLAGER_CTL *ctl;
    uint32 damage;
    sint16 turn;

    damage = wp->ctl.hit_14 & 0xFFFFFF;
    ctl    = &wp->ctl;
    if (damage == 0)
    {
        return 1;
    }
    if (!(wp->ctl.hit_14 & 0x38000000))
    {
        return 1;
    }
    if (wp->value_6E <= 0)
    {
        wp->ctl.flags_0 = (wp->ctl.flags_0 & ~4) | 8;
        damage          = D_80098844[wp->kind_2]->limit_9;
    }
    if (wp->ctl.flags_0 & 8)
    {
        wp->ctl.timer_A += damage;
        if ((wp->ctl.hit_14 & 0x20000000) || wp->ctl.timer_A >= D_80098844[wp->kind_2]->limit_9 ||
            wp->position.y != func_80048E6C(wp))
        {
            if (ctl->from_1C.pad & 1)
            {
                turn = func_80031198(&wp->position, &ctl->from_1C);
                if (((wp->rotation.y - turn + 0x400) & 0xFFF) < 0x800)
                {
                    wp->routine_1  = 0xB;
                    wp->rotation.y = turn;
                }
                else
                {
                    wp->routine_1  = 0xA;
                    wp->rotation.y = (turn + 0x800) & 0xFFF;
                }
            }
            else
            {
                turn = func_80031198(&origin, &ctl->from_1C);
                if (((turn - wp->rotation.y + 0x400) & 0xFFF) < 0x800)
                {
                    wp->routine_1  = 0xA;
                    wp->rotation.y = turn;
                }
                else
                {
                    wp->routine_1  = 0xB;
                    wp->rotation.y = (turn + 0x800) & 0xFFF;
                }
            }
            ctl->timer_A = 0;
        }
        else
        {
            wp->routine_1 = 9;
        }
        *(uint16 *)&wp->routine_2 = 0;
    }
    wp->scale.v.pad = 0x7FFF;
    return 1;
}
