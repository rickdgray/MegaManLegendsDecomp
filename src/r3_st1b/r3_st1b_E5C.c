#include "common.h"
#include "st1b.h"

void func_80100E5C(void)
{
}

void func_80100E64(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        if ((Sce_flag_test(0x33) == 0) && (Sce_flag_test(0x21) != 0))
        {
            func_8001DDE4(0x56);
            Sce_flag_on(0x33);
        }
        else
        {
            func_8001DF10(&D_8010D920);
        }
        wp->value_4 = 0xFF;
    }
}

void func_80100EE8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D928);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F34(void)
{
}

void func_80100F3C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D8C8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100F88(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D8E8);
        wp->routine_4 = 0xFF;
    }
}

void func_80100FD4(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D908);
        wp->routine_4 = 0xFF;
    }
}

void func_80101020(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D8D0);
        wp->routine_4 = 0xFF;
    }
}

void func_8010106C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D8F0);
        wp->routine_4 = 0xFF;
    }
}

void func_801010B8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D910);
        wp->routine_4 = 0xFF;
    }
}

void func_80101104(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        wp->routine_4 = 0xFF;
    }
}

void func_80101120(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D928);
        wp->routine_4 = 0xFF;
    }
}

void func_8010116C(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D8D8);
        wp->routine_4 = 0xFF;
    }
}

void func_801011B8(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D8F8);
        wp->routine_4 = 0xFF;
    }
}

void func_80101204(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D918);
        wp->routine_4 = 0xFF;
    }
}

sint32 func_80101250(ST1B_VIEW *wp)
{
    if (wp->value_4 == 0)
    {
        if (Sce_flag_test(0x235) != 0)
        {
            Sce_flag_on(0x7E2);
            Sce_flag_on(0x7E3);
            Sce_flag_on(0x7E4);
            Sce_flag_on(0x7E8);
        }
        else if (Sce_flag_test(0x22D) == 0)
        {
            if ((Sce_flag_test(0x22C) != 0) && (Sce_flag_test(0x22E) == 0))
            {
                func_8001EB98(D_8010D974);
            }
        }
        else if ((Sce_flag_test(0x22C) != 0) && (Sce_flag_test(0x22E) == 0))
        {
            func_8001DDE4(0x54);
            wp->value_4 = 0xFF;
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101340(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x235) != 0))
    {
        Sce_flag_on(0x7E2);
        Sce_flag_on(0x7E3);
        Sce_flag_on(0x7E4);
        Sce_flag_on(0x7E8);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_801013A0(STAGE_OBJ *wp)
{
    if ((wp->value_4 == 0) && (Sce_flag_test(0x235) != 0))
    {
        Sce_flag_on(0x7E2);
        Sce_flag_on(0x7E3);
        Sce_flag_on(0x7E4);
        Sce_flag_on(0x7E8);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101400(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (Sce_flag_test(0x239))
            {
                func_8010157C();
            }
            if (Sce_flag_test(0x2A) && !Sce_flag_test(0x249))
            {
                func_8001EB98(D_8010DA8C);
                Sce_flag_on(0x249);
                wp->routine_4 = 0xFF;
            }
            else if (Sce_flag_test(0x238) && !Sce_flag_test(0x239))
            {
                Sce_flag_on(0x239);
                func_8001EB98(D_8010D988);
            }
            break;
        case 0xFF:
            return 1;
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_801014E4(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        if ((Sce_flag_test(0x2A) != 0) && (Sce_flag_test(0x249) == 0))
        {
            Sce_flag_off(0x22D);
        }
        else if (Sce_flag_test(0x239) != 0)
        {
            func_8010157C();
        }
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_8010155C(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_8010157C(void)
{
    uint8 state;
    uint8 *count;
    uint8 base;
    uint8 i;
    state = (Sce_flag_test(0x23B) << 1) | Sce_flag_test(0x23A);
    switch (state)
    {
        case 0:
            if (STAGE_GAME_COUNT_62 >= 11)
            {
                Sce_flag_on(0x23A);
                Sce_flag_off(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
        case 1:
            if (STAGE_GAME_COUNT_62 >= 21)
            {
                Sce_flag_off(0x23A);
                Sce_flag_on(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
        case 2:
            if (STAGE_GAME_COUNT_62 >= 31)
            {
                Sce_flag_on(0x23A);
                Sce_flag_on(0x23B);
                STAGE_GAME_COUNT_62 = 0;
            }
            break;
    }
    if (Game_work.value_51 == 8)
    {
        count = &D_8010DB0C[state];
        base  = 0xA;
    }
    else
    {
        count = &D_8010DB08[state];
        base  = 2;
    }
    for (i = 0; i < *count; i++)
    {
        func_8001EB98(&D_8010D974[base + i]);
    }
}

void func_80101724(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 5;
        child->routine_2 = 0;
        child            = wp->child_38;
        child->flags_0 &= 0xFD;
    }
    if (wp->frame_10 == 0xC8)
    {
        child = wp->child_2C;
        child->routine_2++;
    }
    if (wp->frame_10 == 0x15F)
    {
        child                     = wp->child_2C;
        child->routine_1          = 0;
        child->routine_2          = 0;
        child->position_fixed.v.y = 0;
    }
}

void func_801017B0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_2C;
        child->routine_1          = 1;
        child->position_fixed.v.x = -0x0FBE0000;
        child->routine_2          = 0;
        child->position_fixed.v.z = -0xC80000;
    }
}

void func_801017E8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_2C;
        child->routine_1          = 2;
        child->position_fixed.v.x = -0x0F6E0000;
        child->routine_2          = 0;
        child->position_fixed.v.z = -0x02EE0000;
    }
    if (wp->frame_10 == 0x64)
    {
        child               = wp->child_30;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x19)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 1;
    }
    if (wp->frame_10 == 0x82)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 0x8C)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 1;
    }
    if (wp->frame_10 == 0x13B)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 0;
    }
}

void func_801018AC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_34;
        child->rotation.y         = 0xA8C;
        child->position_fixed.v.x = -0x10680000;
        child->routine_1          = 0;
        child->routine_2          = 0;
        child->position_fixed.v.z = -0x03520000;
    }
}

void func_801018E8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0x78)
    {
        child            = wp->child_34;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_30;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80101920(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position_fixed.v.x = -0x0F6E0000;
        child->position_fixed.v.z = -0x02EE0000;
        child->routine_1          = 0;
        child->routine_2          = 0;
        child->rotation.y         = 0x320;
        child                     = wp->child_2C;
        child->routine_1          = 2;
        child->position_fixed.v.x = -0x0FA00000;
        child->position_fixed.v.z = -0x02BC0000;
        child->routine_2          = 0;
        child->rotation.y         = 0x258;
    }
}

void func_80101984(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_30;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x22)
    {
        child               = wp->child_30;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x3C)
    {
        child               = wp->child_30;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0xF)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 1;
    }
    if (wp->frame_10 == 0x9F)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 0;
    }
}

void func_80101A1C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_34;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x19)
    {
        child               = wp->child_34;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x37)
    {
        child               = wp->child_34;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0xC8)
    {
        child            = wp->child_34;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

void func_80101A9C(STAGE_ROOM *wp)
{
    ST1B_VIEW *child;
    if (wp->frame_10 == 0)
    {
        child            = (ST1B_VIEW *)wp->child_30;
        child->routine_1 = 3;
        child->routine_2 = 0;
        child->value_FC  = 0xC;
        child            = (ST1B_VIEW *)wp->child_30;
        child->u_C.b[0]  = 1;
        child->u_C.b[2]  = 1;
    }
    if (wp->frame_10 == 0x55)
    {
        child           = (ST1B_VIEW *)wp->child_30;
        child->u_C.b[0] = 0;
    }
}

void func_80101AF8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_2C;
        child->routine_1 = 3;
        child->routine_2 = 0;
    }
}

void func_80101B30(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->routine_1          = 2;
        child->position_fixed.v.x = -0x0F6E0000;
        child->position_fixed.v.z = -0x03200000;
        child->routine_2          = 0;
        child->rotation.y         = 0x514;
        child                     = wp->child_2C;
        child->position_fixed.v.x = -0x0F3C0000;
        child->position_fixed.v.z = -0x02BC0000;
        child->rotation.y         = 0x258;
        child                     = wp->child_34;
        child->u_C.b.byte_D       = 1;
        child->routine_1          = 3;
        child->routine_2          = 0;
    }
    if (wp->frame_10 == 5)
    {
        child            = wp->child_2C;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        child               = wp->child_34;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x41)
    {
        child            = wp->child_30;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

void func_80101C00(STAGE_ROOM_WORK *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    func_8001F20C(D_8010DD68, D_8010DB10);
    for (i = 0; i < 7; i++)
    {
        func_8001EAE8(&D_8010DCF0[i]);
    }
}

void func_80101C70(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80101CB0(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                STAGE_PL.routine_0   = 3;
                STAGE_PL.routine_1   = 1;
                STAGE_PL.fixed_428.x = -0xE400000;
                STAGE_PL.fixed_428.y = -0x10000;
                STAGE_PL.fixed_428.z = -0x870000;
                STAGE_PL.pos_438.x   = -0xE40;
                STAGE_PL.pos_438.y   = -1;
                STAGE_PL.pos_438.z   = -0x87;
                STAGE_PL.value_442   = 0x800;
                STAGE_PL.flags_0 &= ~2;
                func_8001D58C(0x20010009);
                wp->routine_4++;
            }
            break;
        case 1:
            wp->timer_C = 0x32;
            wp->routine_4++;
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                func_80017C30(2);
                wp->routine_4++;
            }
            break;
        case 3:
            func_80101C00((STAGE_ROOM_WORK *)wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(0xA);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80101C70(wp);
            func_8001EC0C();
            func_8001F070();
            if (wp->routine_4 == 5 && D_80098A72 == 0)
            {
                func_8001D494(0, 1, 0);
                D_800A395C = 1;
                func_80039820();
                STAGE_PL.flags_0 |= 2;
                func_80042314(&Player_work);
                STAGE_PL.value_6E = STAGE_PL.value_B0;
                func_8005D9C4();
                Obj_work_flag_change(0x56, 0x80);
                wp->routine_4++;
            }
            break;
        case 6:
            wp->flags_0 = 0;
            break;
    }
}

void func_80101EFC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_30;
        child->routine_1    = 6;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x64)
    {
        child               = wp->child_30;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0xA)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 1;
    }
    if (wp->frame_10 == 0x5A)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 0;
    }
    if (wp->frame_10 == 0x69)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 1;
        child->u_E.b.byte_E = 1;
    }
    if (wp->frame_10 == 0xA3)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 0;
    }
}

void func_80101FBC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 3;
        child->routine_2    = 0;
        child               = wp->child_2C;
        child->routine_1    = 6;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 1;
        child               = wp->child_34;
        child->routine_1    = 5;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 1;
    }
    if (wp->frame_10 == 0x20)
    {
        child               = wp->child_2C;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x34)
    {
        child               = wp->child_34;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x6E)
    {
        child            = wp->child_38;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xAF)
    {
        func_80017C30(0xA);
    }
}

void func_8010208C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_80017C30(2);
        func_8003187C(wp->child_28);
        func_8003187C(wp->child_2C);
        func_80031824(wp->child_34);
        func_80031824(wp->child_38);
        child             = wp->child_30;
        child->rotation.y = 0x65E;
        child->routine_1  = 7;
        child->routine_2  = 0;
        child             = wp->child_24;
        child->routine_1  = 1;
        child->routine_2  = 0;
    }
    if (wp->frame_10 == 0x4B)
    {
        child = wp->child_24;
        child->routine_2++;
    }
}

void func_80102148(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 5)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 1;
        child->u_E.b.byte_E = 0;
    }
    if (wp->frame_10 == 0x32)
    {
        child               = wp->child_30;
        child->u_C.b.byte_C = 0;
    }
}

void func_8010218C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_24;
        child->routine_2++;
    }
}

void func_801021BC(STAGE_ROOM *wp)
{
    sint32 i;
    func_8001E068();
    func_8001E6C0(0, 0, 0);
    func_8001F20C(D_8010DF28, D_8010DDC8);
    for (i = 0; i < 6; i++)
    {
        func_8001EAE8(&D_8010DEB0[i]);
    }
    if (ST1B_GAME_COUNT_18 != 0xFFFF)
    {
        ST1B_GAME_COUNT_18++;
    }
    ST1B_GAME_TIME_14 = ST1B_GAME_TIME_C;
    if (ST1B_GAME_TIME_C <= 0x4F19F || ST1B_GAME_VALUE_5B == 2)
    {
        ST1B_GAME_FLAG_1A = 1;
    }
}

void func_80102294(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_801022D4(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_80017C30(0xA);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(&Player_work) != 0)
            {
                Player_work.flags_0 &= ~3;
                Obj_work_flag_change(0x56, 0x80);
                func_8001D58C(0x20000020);
                wp->routine_4++;
            }
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x14;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                func_80017C30(2);
                wp->routine_4++;
            }
            break;
        case 4:
            func_801021BC(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (D_80098A72 == 0 && *(uint8 *)wp->tbl_A4 == 0xFF)
            {
                func_80017C30(0xB);
                wp->routine_4++;
            }
            // fall through
        case 6:
            func_80102294(wp);
            func_8001EC0C();
            func_8001F070();
            if (wp->routine_4 == 6 && D_80098A72 == 0)
            {
                D_800C356C  = 2;
                D_800C356E  = 0x1E;
                D_800C356F  = 0;
                D_800C3560  = 0;
                D_800C3562  = 0;
                D_800C3564  = 0;
                D_800C356A  = 0;
                D_800C356D  = 0;
                D_800C3571  = 0xFF;
                D_800C3570  = 0xFF;
                wp->flags_0 = 0;
                func_8001D494(0, 1, 0);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}
