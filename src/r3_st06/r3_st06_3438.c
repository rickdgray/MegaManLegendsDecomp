#include "common.h"
#include "st06.h"

void func_80103438(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            func_8010338C(wp);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(pl))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                pl->value_448         = 0;
                Scene_obj_ent_open(&D_80123908[0]);
                Scene_obj_ent_open(&D_80123908[2]);
                Cd_xa_play_id(0x2000000B);
                wp->routine_4++;
            }
            break;
        case 2:
            if (func_8001D878())
            {
                wp->reserved09[1] |= 1;
                func_8005D7C0();
                wp->timer_C = 0;
                wp->routine_4++;
            }
            break;
        case 3:
            if (++wp->timer_C == 0x20)
            {
                wp->routine_4++;
                Player_work.flags_0 ^= 2;
                Scene_obj_ent_open(D_8012391C);
            }
            break;
        case 4:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
            }
            else if (func_8001DE84() && wp->reserved09[1] == 1 && D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                Fade_start(0xA);
                wp->routine_4++;
            }
            else
            {
                func_801033F8((STAGE_ROOM_WORK *)wp);
                Sce_camera_update();
                Sce_event_update();
            }
            break;
        case 5:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                D_800A395C = 1;
                func_80039820();
                wp->routine_4++;
                if (!Sce_flag_test(0x629))
                {
                    func_8001E3F0(0x12);
                }
            }
            break;
        case 6:
            if (!(Moji_flag & 0x08000000))
            {
                Cd_subcmd(0, 1, 0);
                Player_work.routine_1++;
                func_80039820();
                Obj_work_flag_change(0x56, 0x80);
                D_800C356C = -1;
                D_800C356E = 6;
                D_800C356F = 5;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 2;
                Player_work.flags_0 &= ~3;
                Player_work.value_76 = 0;
                wp->flags_0          = 0;
            }
            break;
    }
}

void func_80103710(STAGE_ROOM *wp)
{
    D_801239E8[wp->routine_4](wp);
}

void func_8010374C(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            wp->reserved09[1] = 0x80;
            // A plain (non-struct) store: retail keeps it before D_800BC7F0's.
            *(uint32 *)&wp->timer_C = 0;
            D_800BC7F0              = D_80123A30;
            wp->tbl_A4              = D_80123E70;
            Scene_obj_ent_open(D_801239F4);
            D_800BBA90[0].flags_0  = D_80123EF0;
            D_800BBA90[0].value_20 = D_80123EF2;
            D_800BBA90[0].value_22 = D_80123EF4;
            wp->routine_5++;
            break;
        case 1:
            Fade_start(3);
            Cd_read_comb(0x62);
            wp->routine_5++;
            break;
        case 2:
            if (D_80098A72 == 0 && Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x20000007);
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878())
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_80123A80;
                wp->tbl_A4    = D_80123E80;
                wp->routine_5 = 0;
                wp->reserved09[1] &= 1;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84())
    {
        wp->reserved09[1] |= 1;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80103904(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        Fade_start(0x14);
        wp->routine_4++;
        wp->routine_5 = 0;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84() != 0 || wp->reserved09[1] == 1)
        {
            Fade_start(8);
            wp->routine_4++;
            wp->routine_5 = 0;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80103998(ST06_OBJ *wp)
{
    uint8 temp_v1;

    if (D_80098A72 == 0)
    {
        temp_v1 = wp->value_5;
        switch (temp_v1)
        {
            case 0:
                Cd_subcmd(0, 1, 0);
                Obj_work_flag_change(0x7E, 0x80);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                func_80103ED0(2);
                D_800C356C = 2;
                wp->value_5++;
                break;
            case 1:
                *(uint8 *)D_800BBA90 |= 3;
                wp->flags_0 = 0;
                break;
        }
    }
    if (wp->routine_2 != 0)
    {
        Sce_camera_update();
        Sce_event_update();
    }
}

void func_80103A84(void)
{
}

void func_80103A8C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        D_800BBA90[0].flags_0 = 0;
        func_80031824(wp->child_24);
        Scene_obj_ent_open(&D_80123A08[0]);
        func_80103ED0(3);
    }
    if (wp->frame_10 == 1)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80103B0C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        wp->routine_5    = 0;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x32)
    {
        child               = wp->child_28;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x78)
    {
        child               = wp->child_28;
        child->routine_1    = 3;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x1C2)
    {
        child               = wp->child_28;
        child->routine_1    = 4;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103B98(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x1E)
    {
        child               = wp->child_28;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103BDC(void)
{
}

void func_80103BE4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 6;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0x1E)
    {
        child               = wp->child_28;
        child->routine_1    = 7;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103C34(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 i;

    if (wp->frame_10 == 0)
    {
        Scene_obj_ent_open(D_80123A1C);
        child            = wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 0;
        for (i = 1; i < 5; i++)
        {
            D_800BBA90[i].flags_0  = D_80123EF6[0].flags_0;
            D_800BBA90[i].value_20 = D_80123EF6[0].value_2;
            D_800BBA90[i].value_22 = D_80123EF6[0].value_4;
        }
    }
}

void func_80103CD8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    sint32 var_a0;
    sint32 var_v1;

    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_2C);
        var_a0 = 1;
        var_v1 = 0x38;
        do
        {
            ((uint8 *)D_800BBA90)[var_v1] = 0;
            var_a0++;
            var_v1 += 0x38;
        } while (var_a0 < 5);
        child            = wp->child_28;
        child->routine_1 = 9;
        child->routine_2 = 0;
        child->u_C.b.byte_D++;
    }
    if (wp->frame_10 == 0x6E)
    {
        child               = wp->child_28;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0xBE)
    {
        child               = wp->child_28;
        child->routine_1    = 0xA;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
    if (wp->frame_10 == 0xFA)
    {
        child               = wp->child_28;
        child->routine_1    = 0xB;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103DC0(void)
{
}

void func_80103DC8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 0xC;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103DF4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child               = wp->child_28;
        child->routine_1    = 0xD;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103E20(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    switch (wp->frame_10)
    {
        case 0:
            child               = wp->child_28;
            child->routine_1    = 0xE;
            child->routine_2    = 0;
            child->u_C.b.byte_D = 0;
            break;
        case 0x168:
            child               = wp->child_28;
            child->routine_1    = 0xF;
            child->routine_2    = 0;
            child->u_C.b.byte_D = 0;
            break;
        case 0x190:
            child               = wp->child_28;
            child->routine_1    = 0x10;
            child->routine_2    = 0;
            child->u_C.b.byte_D = 0;
            break;
        case 0x1E0:
            child               = wp->child_28;
            child->routine_1    = 0x11;
            child->routine_2    = 0;
            child->u_C.b.byte_D = 0;
            break;
    }
}

void func_80103EA4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0x50)
    {
        child               = wp->child_28;
        child->routine_1    = 0x12;
        child->routine_2    = 0;
        child->u_C.b.byte_D = 0;
    }
}

void func_80103ED0(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 6;
    D_800C356F = arg0;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80103F34(void)
{
}

void func_80103F3C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        MojiTaskExec2(0, 1);
        Player_work.value_448 = 0x35;
    }
    if (!(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80103F98(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        MojiTaskExec2(0, 5);
    }
    if (wp->frame_10 == 0x29)
    {
        Player_work.value_448 = 0x2D;
    }
    if (wp->frame_10 >= 0x34)
    {
        Sce_event_next();
    }
}

void func_8010400C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        Scene_obj_ent_open(D_80123EFC);
        wp->child_24->variant_3    = 0;
        wp->child_24->u_E.b.byte_E = 0;
        wp->child_24->u_C.b.byte_D = 1;
        wp->child_24->rotation.y   = 0x800;
        Sce_event_next();
    }
}

void func_80104084(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x140;
        wp->child_24->u_E.b.byte_E     = 2;
        wp->child_24->u_C.b.byte_D     = 1;
        wp->child_24->routine_0        = 2;
    }
    if (wp->frame_10 == 0x5B)
    {
        wp->child_24->value_44.half[0] = 0;
    }
    if (wp->frame_10 >= 0x5B && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x329;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x498;
        STAGE_PL.fixed_428.x             = 0x3290000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x4980000;
        STAGE_PL.value_442               = 0x4F6;
        STAGE_PL.value_448               = 0x30;
        wp->child_24->position.x         = 0x2CE;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x4C0;
        wp->child_24->position_fixed.v.x = 0x2CE0000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x4C00000;
        wp->child_24->rotation.y         = 0xCF6;
        wp->child_24->u_E.b.byte_E       = 0;
        wp->child_24->u_C.b.byte_D       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Sce_event_next();
    }
}

void func_801041FC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        wp->child_24->u_E.b.byte_E = 8;
        wp->child_24->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 6);
    }
    if (wp->frame_10 >= 0x33 && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x269;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x382;
        STAGE_PL.fixed_428.x             = 0x2690000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x3820000;
        STAGE_PL.value_442               = 0x800;
        STAGE_PL.value_448               = 0xC;
        wp->child_24->position.x         = 0x1A1;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x385;
        wp->child_24->position_fixed.v.x = 0x1A10000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x3850000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.byte_E       = 1;
        wp->child_24->u_C.b.byte_D       = 1;
        Sce_event_next();
    }
}

void func_80104344(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x40;
    }
    STAGE_PL.fixed_428.z += 0x50000;
    STAGE_PL.pos_438.z = STAGE_PL.fixed_428.z >> 16;
    if (wp->frame_10 == 0x96)
    {
        D_800C356C        = 1;
        D_800C356E        = 6;
        D_800C356F        = 1;
        D_800C356D        = 0;
        D_800C3571        = 0xA;
        D_800C3570        = 0xFF;
        wp->reserved09[2] = 1;
        wp->reserved09[1] = 0;
        Sce_event_next();
    }
}

void func_801043F4(void)
{
}

void func_801043FC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -0x4E;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = -0x51;
        STAGE_PL.fixed_428.x = 0xFFB20000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0xFFAF0000;
        STAGE_PL.value_442   = 0x800;
        STAGE_PL.value_448   = 0x30;
        Scene_obj_ent_open(&D_80123EFC[0]);
        wp->child_24->variant_3          = 0;
        wp->child_24->position.x         = 0x51;
        wp->child_24->position.y         = -1;
        wp->child_24->position.z         = -0x51;
        wp->child_24->position_fixed.v.x = 0x510000;
        wp->child_24->position_fixed.v.y = 0xFFFF0000;
        wp->child_24->position_fixed.v.z = 0xFFAF0000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.byte_E       = 0;
        wp->child_24->u_C.b.byte_D       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Scene_obj_ent_open(&D_80123EFC[1]);
        Scene_obj_ent_open(&D_80123EFC[2]);
        Scene_obj_ent_open(&D_80123EFC[3]);
        wp->child_28->rotation.y       = 0;
        wp->child_28->value_44.half[0] = 0;
        wp->child_2C->rotation.y       = 0;
        wp->child_2C->value_44.half[0] = 0;
        wp->child_30->rotation.y       = 0x800;
        wp->child_30->value_44.half[0] = 0;
    }
}

void func_801045AC(void)
{
}

void func_801045B4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_28;
    if (child->routine_0 == 1)
    {
        child->routine_0        = 2;
        wp->child_2C->routine_0 = 2;
        wp->child_30->routine_0 = 2;
    }
    if (wp->frame_10 == 0x3D)
    {
        Sce_event_next();
        STAGE_PL_OBJ->flags_0 &= ~2;
        wp->child_24->flags_0 &= ~2;
    }
}

void func_80104654(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x1F)
    {
        child               = wp->child_28;
        child->u_E.b.byte_E = 8;
        child               = wp->child_28;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x37);
    }
    if ((wp->frame_10 >= 0x33) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801046DC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        child = wp->child_24;
        child->flags_0 |= 2;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_24;
        child->u_E.b.byte_E = 8;
        child               = wp->child_24;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x38);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_8010478C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        Player_work.flags_0 |= 2;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x39);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_8010483C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_28;
        child->u_E.b.byte_E = 8;
        child               = wp->child_28;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3AU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801048C4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3BU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_8010494C(STAGE_ROOM *wp)
{
    uint16 *spin;

    if (wp->frame_10 == 0x10)
    {
        Sound_call(0x18C, 0, 0);
    }
    if (wp->frame_10 == 0x1F)
    {
        Sound_call(0x18D, 0, 0);
        wp->child_30->u_E.b.byte_E = 8;
        wp->child_30->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3C);
        wp->child_24->u_E.b.byte_E = 1;
        wp->child_24->u_C.b.byte_D = 1;
        Player_work.value_448      = 0xC;
    }
    if (wp->frame_10 >= 0x20 && wp->frame_10 < 0x3F)
    {
        spin = &STAGE_PL.value_442;
        *spin += 0x40;
        wp->child_24->rotation.y -= 0x40;
    }
    if (wp->frame_10 == 0x3F)
    {
        wp->child_24->u_E.b.byte_E = 0;
        wp->child_24->u_C.b.byte_D = 1;
        Player_work.value_448      = 0x30;
    }
    if ((wp->frame_10 >= 0x4A) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104AAC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_30->u_E.b.byte_E            = 1;
        wp->child_30->u_C.b.byte_D            = 1;
        wp->child_30->value_44.words.fraction = 0x3C;
        MojiTaskExec2(0, 0x3DU);
    }
    if (wp->frame_10 >= 0x56)
    {
        wp->child_30->u_E.b.byte_E            = 0;
        wp->child_30->u_C.b.byte_D            = 1;
        wp->child_30->value_44.words.fraction = 0;
    }
    if ((wp->frame_10 >= 0x57) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104B74(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3EU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104BFC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_28->u_E.b.byte_E = 8;
        wp->child_28->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3F);
    }
    if (wp->frame_10 >= 0x20 && !(Moji_flag & 0x08000000))
    {
        Player_work.flags_0 &= ~2;
        Sce_event_next();
    }
}

void func_80104C98(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x40);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104D20(void)
{
}

void func_80104D28(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        Player_work.value_448 = 0x82;
        MojiTaskExec2(0, 2);
    }
    if (!(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80104D84(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        MojiTaskExec2(0, 7);
    }
    if (wp->frame_10 == 0x29)
    {
        Player_work.value_448 = 0x2D;
    }
    if (wp->frame_10 >= 0x34)
    {
        Sce_event_next();
    }
}

void func_80104DF8(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        Scene_obj_ent_open(D_80123EFC);
        wp->child_24->variant_3    = 0;
        wp->child_24->u_E.b.byte_E = 0;
        wp->child_24->u_C.b.byte_D = 1;
        wp->child_24->rotation.y   = 0x800;
        Sce_event_next();
    }
}

void func_80104E70(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x140;
        wp->child_24->u_E.b.byte_E     = 2;
        wp->child_24->u_C.b.byte_D     = 1;
        wp->child_24->routine_0        = 2;
    }
    if (wp->frame_10 == 0x5B)
    {
        wp->child_24->value_44.half[0] = 0;
    }
    if (wp->frame_10 >= 0x5B && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x329;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x498;
        STAGE_PL.fixed_428.x             = 0x3290000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x4980000;
        STAGE_PL.value_442               = 0x4F6;
        STAGE_PL.value_448               = 0x30;
        wp->child_24->position.x         = 0x2CE;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x4C0;
        wp->child_24->position_fixed.v.x = 0x2CE0000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x4C00000;
        wp->child_24->rotation.y         = 0xCF6;
        wp->child_24->u_E.b.byte_E       = 0;
        wp->child_24->u_C.b.byte_D       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Sce_event_next();
    }
}

void func_80104FE8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x1F)
    {
        child               = wp->child_24;
        child->u_E.b.byte_E = 8;
        child               = wp->child_24;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 8);
    }
    if ((wp->frame_10 >= 0x33) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105070(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        Player_work.value_448 = 0x32;
        MojiTaskExec2(0, 9);
    }
    if (wp->frame_10 >= 0x33 && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801050EC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1F)
    {
        wp->child_24->u_E.b.byte_E = 0x12;
        wp->child_24->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0xA);
    }
    if (wp->frame_10 >= 0x33 && !(Moji_flag & 0x08000000))
    {
        STAGE_PL.pos_438.x               = 0x269;
        STAGE_PL.pos_438.y               = -0x301;
        STAGE_PL.pos_438.z               = 0x382;
        STAGE_PL.fixed_428.x             = 0x2690000;
        STAGE_PL.fixed_428.y             = 0xFCFF0000;
        STAGE_PL.fixed_428.z             = 0x3820000;
        STAGE_PL.value_442               = 0x800;
        STAGE_PL.value_448               = 0xC;
        wp->child_24->position.x         = 0x1A1;
        wp->child_24->position.y         = -0x301;
        wp->child_24->position.z         = 0x385;
        wp->child_24->position_fixed.v.x = 0x1A10000;
        wp->child_24->position_fixed.v.y = 0xFCFF0000;
        wp->child_24->position_fixed.v.z = 0x3850000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.byte_E       = 1;
        wp->child_24->u_C.b.byte_D       = 1;
        Sce_event_next();
    }
}

void func_80105234(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        wp->child_24->value_44.half[0] = 0x40;
    }
    STAGE_PL.fixed_428.z += 0x50000;
    STAGE_PL.pos_438.z = STAGE_PL.fixed_428.z >> 16;
    if (wp->frame_10 == 0x96)
    {
        D_800C356C        = 1;
        D_800C356E        = 6;
        D_800C356F        = 4;
        D_800C3571        = 0xA;
        D_800C356D        = 0;
        D_800C3570        = 0xFF;
        wp->reserved09[2] = 1;
        wp->reserved09[1] = 0;
        Sce_event_next();
    }
}

void func_801052E8(void)
{
}

void func_801052F0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -0x4E;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = -0x51;
        STAGE_PL.fixed_428.x = 0xFFB20000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0xFFAF0000;
        STAGE_PL.value_442   = 0x800;
        STAGE_PL.value_448   = 0x30;
        Scene_obj_ent_open(&D_80123EFC[0]);
        wp->child_24->variant_3          = 0;
        wp->child_24->position.x         = 0x51;
        wp->child_24->position.y         = -1;
        wp->child_24->position.z         = -0x51;
        wp->child_24->position_fixed.v.x = 0x510000;
        wp->child_24->position_fixed.v.y = 0xFFFF0000;
        wp->child_24->position_fixed.v.z = 0xFFAF0000;
        wp->child_24->rotation.y         = 0x800;
        wp->child_24->u_E.b.byte_E       = 0;
        wp->child_24->u_C.b.byte_D       = 1;
        wp->child_24->value_44.half[0]   = 0;
        Scene_obj_ent_open(&D_80123EFC[1]);
        Scene_obj_ent_open(&D_80123EFC[2]);
        Scene_obj_ent_open(&D_80123EFC[3]);
        wp->child_28->rotation.y       = 0;
        wp->child_28->value_44.half[0] = 0;
        wp->child_2C->rotation.y       = 0;
        wp->child_2C->value_44.half[0] = 0;
        wp->child_30->rotation.y       = 0x800;
        wp->child_30->value_44.half[0] = 0;
    }
}

void func_801054A0(void)
{
}

void func_801054A8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_28;
    if (child->routine_0 == 1)
    {
        child->routine_0        = 2;
        wp->child_2C->routine_0 = 2;
        wp->child_30->routine_0 = 2;
    }
    if (wp->frame_10 == 0x3D)
    {
        Sce_event_next();
        STAGE_PL_OBJ->flags_0 &= ~2;
        wp->child_24->flags_0 &= ~2;
    }
}

void func_80105548(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x1F)
    {
        child               = wp->child_28;
        child->u_E.b.byte_E = 8;
        child               = wp->child_28;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x37);
    }
    if ((wp->frame_10 >= 0x33) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801055D0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        child = wp->child_24;
        child->flags_0 |= 2;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_24;
        child->u_E.b.byte_E = 8;
        child               = wp->child_24;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x38);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105680(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 1)
    {
        Player_work.flags_0 |= 2;
    }
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x41);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105730(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_28;
        child->u_E.b.byte_E = 8;
        child               = wp->child_28;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x42);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801057B8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x43);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105840(STAGE_ROOM *wp)
{
    uint16 *spin;

    if (wp->frame_10 == 0x10)
    {
        Sound_call(0x18C, 0, 0);
    }
    if (wp->frame_10 == 0x1F)
    {
        Sound_call(0x18D, 0, 0);
        wp->child_30->u_E.b.byte_E = 8;
        wp->child_30->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3C);
        wp->child_24->u_E.b.byte_E = 1;
        wp->child_24->u_C.b.byte_D = 1;
        Player_work.value_448      = 0xC;
    }
    if (wp->frame_10 >= 0x20 && wp->frame_10 < 0x3F)
    {
        spin = &STAGE_PL.value_442;
        *spin += 0x40;
        wp->child_24->rotation.y -= 0x40;
    }
    if (wp->frame_10 == 0x3F)
    {
        wp->child_24->u_E.b.byte_E = 0;
        wp->child_24->u_C.b.byte_D = 1;
        Player_work.value_448      = 0x30;
    }
    if ((wp->frame_10 >= 0x4A) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_801059A0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_30->u_E.b.byte_E            = 1;
        wp->child_30->u_C.b.byte_D            = 1;
        wp->child_30->value_44.words.fraction = 0x3C;
        MojiTaskExec2(0, 0x3DU);
    }
    if (wp->frame_10 >= 0x56)
    {
        wp->child_30->u_E.b.byte_E            = 0;
        wp->child_30->u_C.b.byte_D            = 1;
        wp->child_30->value_44.words.fraction = 0;
    }
    if ((wp->frame_10 >= 0x57) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105A68(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3EU);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105AF0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x10)
    {
        wp->child_28->u_E.b.byte_E = 8;
        wp->child_28->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x3F);
    }
    if (wp->frame_10 >= 0x20 && !(Moji_flag & 0x08000000))
    {
        Player_work.flags_0 &= ~2;
        Sce_event_next();
    }
}

void func_80105B8C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0x10)
    {
        child               = wp->child_2C;
        child->u_E.b.byte_E = 8;
        child               = wp->child_2C;
        child->u_C.b.byte_D = 1;
        MojiTaskExec2(0, 0x40);
    }
    if ((wp->frame_10 >= 0x20) && !(Moji_flag & 0x08000000))
    {
        Sce_event_next();
    }
}

void func_80105C14(void)
{
    Sce_event_next();
}

void func_80105C34(void)
{
}

void func_80105C3C(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    if (Sce_flag_test(0x629))
    {
        D_800BC7F0 = D_8012411C;
        wp->tbl_A4 = D_80124374;
        func_8001E390(0x2E1);
    }
    else
    {
        D_800BC7F0 = D_80123F74;
        wp->tbl_A4 = D_801242C4;
    }
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    Sce_flag_on(0x52C);
}

void func_80105CE0(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}
