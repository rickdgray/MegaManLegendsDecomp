#include "common.h"
#include "st1a.h"

void func_8010523C(STAGE_ROOM *wp)
{
    D_80130514[wp->routine_4](wp);
}

void func_80105278(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_5++;
            }
            break;
        case 1:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                func_8001F580(0xC0, 1, 1);
                func_8005D7C0();
                wp->reserved09[1] = 0x80;
                wp->routine_5++;
            }
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x2000001F);
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                func_8001E6C0(0, 0, 0);
                D_800BC7F0      = D_80130674;
                wp->tbl_A4      = D_80131270;
                wp->timer_C     = 0;
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->pos_438.x   = 0x80;
                pl->pos_438.y   = -1;
                pl->pos_438.z   = 0x580;
                pl->fixed_428.x = 0x80 << 16;
                pl->fixed_428.y = -1 << 16;
                pl->fixed_428.z = 0x580 << 16;
                pl->value_442   = 0x800;
                pl->value_440   = 0;
                pl->value_444   = 0;
                pl->value_448   = 0x30;
                pl->value_170   = 0;
                pl->flags_bd |= 0x10;
                func_80106FBC(0);
                func_80106FF4(0);
                Sce_camera_update();
                Sce_event_update();
                wp->routine_5++;
            }
            break;
        case 4:
            Fade_start(6);
            func_8010702C();
            Sce_camera_update();
            Sce_event_update();
            wp->routine_4 = 1;
            wp->routine_5 = 0;
            wp->routine_6 = 0;
            wp->routine_7 = 0;
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
}

void func_80105488(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 1:
            wp->tbl_A4[1](wp);
            break;
        case 2:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4 = 2;
                wp->routine_5 = 0;
                break;
            }
            // fall through
        case 0:
            wp->tbl_A4[1](wp);
            if (!(wp->reserved09[1] & 0x80) && (wp->reserved09[1] & 1))
            {
                Fade_start(8);
                wp->routine_4 = 2;
                wp->routine_5 = 0;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8010702C();
    Sce_camera_update();
    Sce_event_update();
}

void func_80105598(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x156, 0x80);
                func_80042314(&Player_work);
                STAGE_PL.value_AC  = 0;
                STAGE_PL.value_168 = 0;
                STAGE_PL.value_169 = 0;
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                Cd_subcmd(0, 1, 0);
                Sound_work_view.volume_4 = 0x7F;
                wp->routine_5++;
            }
            break;
        case 1:
            D_800C356C = 2;
            D_800C356E = 0x1B;
            D_800C356F = 1;
            D_800C3560 = 0;
            D_800C3562 = 0;
            D_800C3564 = 0;
            D_800C356A = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            func_8001D974();
            wp->flags_0 = 0;
            break;
    }
}

void func_801056D4(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                wp->reserved09[1] &= 0x7F;
                wp->routine_6++;
            }
            break;
        case 1:
            if (wp->frame_10 == 0x5A)
            {
                func_80106FBC(0xD);
            }
            if (wp->frame_10 >= 0x78)
            {
                Scene_obj_ent_open(D_80130520);
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_8010578C(void)
{
}

void func_80105794(void)
{
}

void func_8010579C(STAGE_ROOM *wp)
{
    sint32 mask;

    mask = ~2; // retail ands with -3 held in a register
    if (wp->frame_10 == 0)
    {
        STAGE_PL.flags_0 &= mask;
        wp->child_24->flags_0 &= mask;
        Scene_obj_ent_open(&D_80130534[0]);
        D_800BBB38 = 3;
        func_80106F38(0xD);
    }
    func_80107110(3);
}

void func_80105818(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        wp->child[1]->flags_0 &= ~2;
        for (i = 2; i < 11; i++)
        {
            Scene_obj_ent_open(&D_80130520[i]);
        }
        D_80139734    = 0;
        wp->routine_6 = 0;
    }
    if (wp->routine_6 == 0)
    {
        if (func_80107110(0) != 0)
        {
            wp->routine_6++;
        }
    }
    else
    {
        func_80107110(1);
    }
}

void func_801058F8(void)
{
    func_80107110(1);
}

void func_80105918(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 2; i < 11; i++)
        {
            wp->child[i]->flags_0 &= ~2;
        }
        D_800BBB38 = 0;
        Scene_obj_ent_open(&D_801305FC[0]);
        func_80106F38(0xC);
    }
}

void func_8010599C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_50;
        child->flags_0 &= ~2;
        pl = &Player_work;
        pl->flags_0 |= 2;
        child = wp->child_24;
        child->flags_0 |= 2;
        func_80106F38(0xF);
    }
}

void func_80105A10(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;

    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = 0x80;
            STAGE_PL.pos_438.y   = -1;
            STAGE_PL.pos_438.z   = 0x6C0;
            STAGE_PL.fixed_428.x = 0x80 << 16;
            STAGE_PL.fixed_428.y = -1 << 16;
            STAGE_PL.fixed_428.z = 0x6C0 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.value_444   = 0;
            STAGE_PL.flags_bd |= 0x10;
            func_80106FBC(0);
            func_80106FF4(1);
            obj                     = wp->child_24;
            obj->position.y         = 8;
            obj->position.z         = 0x740;
            obj->position_fixed.v.y = 8 << 16;
            obj->position_fixed.v.z = 0x740 << 16;
            obj->position.x         = 0x80;
            obj->position_fixed.v.x = 0x80 << 16;
            obj->rotation.z         = 0;
            obj->rotation.x         = 0;
            obj->rotation.y         = 0xCE0;
            break;
        case 10:
            STAGE_PL.value_448 = 0x80;
            func_80106FBC(1);
            func_80106FF4(0xB);
            break;
        case 25:
            func_80106FF4(1);
            break;
        case 30:
            STAGE_PL.value_448 = 0x81;
            func_80106FF4(0xB);
            break;
        case 60:
            func_80106FF4(1);
            break;
    }
}

void func_80105BA8(void)
{
}

void func_80105BB0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->flags_0 &= ~2;
    }
}

void func_80105BE0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->flags_0 |= 2;
    }
}

void func_80105C10(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80106FBC(0);
            func_80106FF4(0);
            STAGE_PL.value_448 = 0x82;
            break;
        case 0x32:
            STAGE_PL.value_448 = 0x83;
            func_80106FBC(0xE);
            func_80106FF4(0xC);
            break;
        case 0xBE:
        case 0x15E:
            func_80106FBC(0xF);
            break;
        case 0x1F4:
            STAGE_PL.value_448 = 0x84;
            func_80106FBC(3);
            func_80106FF4(0xD);
            break;
        case 0x1FE:
            func_80106FF4(3);
            break;
        case 0x208:
            func_80106FF4(0xD);
            break;
        case 0x21E:
            func_80106FF4(3);
            break;
    }
}

void func_80105D30(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0x32:
            Player_work.value_448 = 0x85;
            func_80106FBC(0x16);
            func_80106FF4(0xE);
            break;
        case 0x78:
            Player_work.value_448 = 0x86;
            func_80106FBC(0x17);
            func_80106FF4(0x14);
            break;
    }
}

void func_80105DA0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        Scene_obj_ent_open(D_80130610);
    }
}

void func_80105DD8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    sint32 mask;

    if (wp->frame_10 == 0)
    {
        pl                 = &Player_work;
        STAGE_PL.value_448 = 0x30;
        mask               = ~2;
        pl->flags_0 &= mask;
        wp->child_54->flags_0 &= mask;
        wp->child_28->flags_0 |= 2;
        D_800BBB38 = 3;
        func_80106F38(0xD);
    }
    func_80107110(3);
}

void func_80105E70(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 2; i < 11; i++)
        {
            wp->child[i]->flags_0 |= 2;
        }
        D_80139734    = 0;
        wp->routine_6 = 0;
    }
    if (wp->routine_6 == 0 && func_80107110(2) != 0)
    {
        wp->routine_6++;
    }
}

void func_80105F18(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_80139734    = 0;
        wp->routine_6 = 0;
    }
    if ((wp->routine_6 == 0) && (func_80107110(2) != 0))
    {
        wp->routine_6++;
    }
}

void func_80105F88(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        for (i = 1; i < 11; i++)
        {
            wp->child[i]->flags_0 &= ~2;
        }
        D_800BBA90[3].flags_0 = 0;
        wp->child[11]->flags_0 |= 2;
        func_80106F38(0xC);
    }
}

void func_80106010(void)
{
}

void func_80106018(ST1A_ROOM *wp)
{
    sint8 i;

    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child[0]);
        func_80031A4C(wp->child[1]);
        func_80031824(wp->child[2]);
        func_80031824(wp->child[3]);
        for (i = 4; i < 10; i++)
        {
            Close_SHL_WORK(wp->child[i]);
        }
        func_80031824(wp->child[10]);
        func_80031824(wp->child[11]);
        func_80031824(wp->child[12]);
        for (i = 0; i < 13; i++)
        {
            wp->child[i] = NULL;
        }
        Scene_obj_ent_open(&D_80130624);
        wp->child[0]->routine_1      = 2;
        wp->child[0]->value_48.value = 0x500;
        D_800BBA90[2].flags_0        = 3;
        D_800BBA90[2].pos_C.x        = 0;
        D_800BBA90[2].pos_C.y        = 0;
        D_800BBA90[2].fpos_4.x       = 0;
        D_800BBA90[2].fpos_4.y       = 0;
        Cd_subcmd(0, 1, 0);
        wp->routine_6 = 0;
        wp->flags_A |= 0x80;
        func_80106F38(0xE);
    }
    else
    {
        wp->child[0]->value_48.value -= 8;
    }
    switch (wp->routine_6)
    {
        case 0:
            if (wp->frame_10 == 0xA)
            {
                Cd_read_comb(0xC1);
                wp->routine_5 = 1;
                wp->routine_6++;
            }
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                wp->routine_6++;
            }
            break;
        case 2:
            if (wp->frame_10 >= 0xA0)
            {
                Cd_xa_play_id(0x20000021);
                wp->routine_6++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                wp->routine_5 = 2;
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_80106278(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 1:
            wp->reserved09[1] &= 0x7F;
            func_80031A4C(wp->child_24);
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = 0x80;
            STAGE_PL.pos_438.y   = -1;
            STAGE_PL.pos_438.z   = 0x640;
            STAGE_PL.fixed_428.x = 0x80 << 16;
            STAGE_PL.fixed_428.y = -1 << 16;
            D_800BBB00           = 0;
            STAGE_PL.fixed_428.z = 0x640 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0;
            STAGE_PL.value_444   = 0;
            pl->flags_0 |= 2;
            STAGE_PL.flags_bd |= 0x10;
            func_80106FBC(4);
            func_80106FF4(4);
            STAGE_PL.value_448 = 0x87;
            Scene_obj_ent_open(&D_80130638);
            func_80106F38(0xF);
            break;
        case 0x2D:
            func_80106FF4(0xF);
            break;
        case 0x37:
            func_80106FF4(4);
            break;
        case 0x78:
            func_80106FBC(0x10);
            break;
    }
}

void func_80106400(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80106FBC(4);
            func_80106FF4(4);
            break;
        case 0x1E:
            func_80106FBC(0x10);
            break;
        case 0x2D:
            func_80106FF4(0xF);
            break;
        case 0x46:
            STAGE_PL.value_448 = 0x88;
            break;
        case 0x5F:
            func_80106FF4(4);
            break;
    }
}

void func_801064A8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->flags_0 &= ~2;
    }
}

void func_801064D8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            pl->flags_0 |= 2;
            func_80106FBC(4);
            func_80106FF4(4);
            break;
        case 0x78:
        case 0x136:
        case 0x1EA:
            func_80106FBC(0x10);
            break;
        case 0x262:
            Player_work.value_448 = 0x89;
            func_80106FBC(0x11);
            func_80106FF4(0x10);
            break;
    }
}

void func_8010658C(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80106FBC(5);
            func_80106FF4(5);
            break;
        case 15:
            STAGE_PL.value_448 = 0x8A;
            func_80106FBC(0x12);
            break;
        case 20:
            func_80106FBC(0xC);
            func_80106FF4(6);
            break;
    }
}

void func_80106620(void)
{
}

void func_80106628(STAGE_ROOM *wp)
{
    sint32 mask;

    mask = ~2; // retail ands with -3 held in a register
    if (wp->frame_10 == 0)
    {
        STAGE_PL.flags_0 &= mask;
        wp->child_24->flags_0 &= mask;
        Scene_obj_ent_open(&D_8013064C[0]);
        Scene_obj_ent_open(&D_8013064C[1]);
        func_80106F38(0x10);
    }
}

void func_801066A0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *obj;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            wp->child_28->flags_0 &= ~2;
            wp->child_2C->flags_0 &= ~2;
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.z   = 0x640;
            STAGE_PL.pos_438.x   = 0x80;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.fixed_428.x = 0x80 << 16;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.fixed_428.z = 0x640 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0;
            STAGE_PL.value_444   = 0;
            pl->flags_0 |= 2;
            STAGE_PL.flags_bd |= 0x10;
            func_80106FBC(6);
            func_80106FF4(7);
            STAGE_PL.value_448      = 0x80;
            obj                     = wp->child_24;
            obj->position.x         = 0x80;
            obj->position.y         = -0xC1;
            obj->position_fixed.v.x = 0x80 << 16;
            obj->position_fixed.v.y = -0xC1 << 16;
            obj->rotation.z         = 0;
            obj->position.z         = 0x5C0;
            obj->flags_0 |= 2;
            obj->rotation.x         = 0;
            obj->position_fixed.v.z = 0x5C0 << 16;
            obj->rotation.y         = 0x800;
            func_80106F38(2);
            break;
        case 0x46:
        case 0xB4:
            func_80106FBC(0x13);
            break;
        case 0xFA:
            STAGE_PL.value_448 = 0x8B;
            break;
        case 0xFE:
            func_80106FBC(7);
            break;
        case 0x104:
            func_80106FBC(8);
            break;
        case 0x124:
            func_80106FF4(0x11);
            break;
        case 0x13B:
            func_80106FF4(7);
            break;
        case 0x14A:
            func_80106FBC(0x14);
            func_80106FF4(0x11);
            break;
        case 0x159:
            func_80106FF4(7);
            break;
        case 0x168:
            func_80106FF4(0x11);
            break;
        case 0x186:
            func_80106FF4(7);
            break;
    }
}

void func_8010693C(ST1A_ROOM *wp)
{
    sint32 mask;

    mask = ~2; // retail ands with -3 held in a register
    if (wp->frame_10 == 0)
    {
        STAGE_PL.flags_0 &= mask;
        wp->child[0]->flags_0 &= mask;
        wp->child[1]->flags_0 |= 2;
        wp->child[2]->flags_0 |= 2;
        func_80106F38(0x10);
    }
}

void func_801069CC(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->frame_10)
    {
        case 0:
            func_8003187C(wp->child_28);
            func_80031824(wp->child_2C);
            wp->child_28 = NULL;
            wp->child_2C = NULL;
            pl->flags_0 |= 2;
            func_80106FBC(6);
            func_80106FF4(8);
            STAGE_PL.value_448 = 0x80;
            wp->child_24->flags_0 |= 2;
            func_80106F38(2);
            break;
        case 0x2D:
        case 0x4B:
            func_80106FF4(0x11);
            break;
        case 0x3C:
        case 0x5F:
            func_80106FF4(8);
            break;
        case 0x69:
            func_80106FBC(0x13);
            break;
    }
}

void func_80106AFC(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 1:
            func_80106FBC(9);
            func_80106FF4(9);
            STAGE_PL.value_448 = 0x80;
            break;
        case 0x14:
            STAGE_PL.value_448 = 0x8C;
            break;
    }
}

void func_80106B50(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        STAGE_PL.flags_0 &= ~2;
        child                     = wp->child_24;
        child->position.y         = -0xC1;
        child->position.z         = 0x620;
        child->position_fixed.v.y = 0xFF3F0000;
        child->position_fixed.v.z = 0x06200000;
        child->position.x         = 0;
        child->position_fixed.v.x = 0;
        child->rotation.z         = 0;
        child->rotation.x         = 0;
        child->rotation.y         = 0x800;
        child->flags_0 |= 2;
    }
}

void func_80106BC8(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;

    pl = &STAGE_PL;
    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.y   = -0xC1;
            STAGE_PL.pos_438.z   = 0x640;
            STAGE_PL.fixed_428.y = -0xC1 << 16;
            STAGE_PL.pos_438.x   = 0;
            STAGE_PL.fixed_428.x = 0;
            STAGE_PL.fixed_428.z = 0x640 << 16;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_442   = 0;
            STAGE_PL.value_444   = 0;
            pl->flags_0 |= 2;
            STAGE_PL.flags_bd |= 0x10;
            wp->routine_6 = 0;
            break;
        case 0xB:
            STAGE_PL.value_448 = 0x8D;
            break;
        case 0x14:
            func_80106FBC(0x14);
            func_80106FF4(0x12);
            break;
        case 0x1E:
            func_80106FBC(0xA);
            func_80106FF4(0xA);
            break;
        case 0x3E:
            STAGE_PL.value_448 = 0x8E;
            break;
        case 0x50:
            func_80106FBC(0x15);
            break;
        case 0x8C:
            func_80106FBC(0x15);
            func_80106FF4(0x13);
            break;
        case 0x98:
            func_80106FF4(0xA);
            break;
        case 0xA4:
            func_80106FBC(0xB);
            STAGE_PL.value_448 = 0x8F;
            break;
        case 0xA9:
            wp->routine_6 = 1;
            break;
    }
    if (wp->routine_6 == 1)
    {
        pl->pos_438.z -= 0x10;
        pl->fixed_428.z = pl->pos_438.z << 16;
        obj             = wp->child_24;
        obj->position.z -= 0x10;
        obj->position_fixed.v.z = obj->position.z << 16;
    }
}

void func_80106E1C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *obj;

    pl  = &STAGE_PL;
    obj = wp->child_24;
    if (wp->frame_10 == 2)
    {
        STAGE_PL.value_448 = 1;
    }
    if (wp->frame_10 == 0x5A)
    {
        Fade_start(0xA);
        wp->reserved09[1] |= 0x80;
    }
    if (wp->frame_10 >= 0x5A && Sound_work_view.volume_4 > 0)
    {
        Sound_work_view.volume_4 -= 5;
        if (Sound_work_view.volume_4 < 0)
        {
            Sound_work_view.volume_4 = 0;
        }
    }
    pl->pos_438.z -= 0x10;
    pl->fixed_428.z         = pl->pos_438.z << 16;
    obj->position.y         = D_801315A0[(wp->frame_10 - 2) & 0xF] - 0xC1;
    obj->position_fixed.v.y = obj->position.y << 16;
    obj->position.z -= 0x10;
    obj->position_fixed.v.z = obj->position.z << 16;
}

void func_80106F38(sint32 index)
{
    D_800C356F = index;
    D_800C356C = -1;
    D_800C356E = 0x17;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C3560 = STAGE_PL.pos_438.x;
    D_800C3562 = STAGE_PL.pos_438.y;
    D_800C3564 = STAGE_PL.pos_438.z;
    D_800C356A = STAGE_PL.value_442;
}

void func_80106FBC(sint32 index)
{
    D_80139724.shape_8 = D_80139724.prev_9 = D_80139724.index_A = 0;
    D_80139724.mouth_0                                          = D_801314EC[index];
}

void func_80106FF4(sint32 index)
{
    D_80139724.shape_B = D_80139724.prev_C = D_80139724.index_D = 0;
    D_80139724.eyes_4                                           = D_8013154C[index];
}

void func_8010702C(void)
{
    STAGE_FACE2 *face;

    face = &D_80139724;
    if (face->mouth_0[face->index_A + 1] != 0x7E)
    {
        if (face->mouth_0[face->index_A + 1] == 0x7F)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_8 = face->mouth_0[face->index_A];
    face->prev_9  = face->shape_8;
    if (face->eyes_4[face->index_D + 1] != 0x7E)
    {
        if (face->eyes_4[face->index_D + 1] == 0x7F)
        {
            face->index_D = 0;
        }
        else
        {
            face->index_D++;
        }
    }
    face->shape_B = face->prev_C = face->eyes_4[face->index_D];
    STAGE_PL.value_168           = face->shape_8;
    STAGE_PL.value_169           = face->shape_B;
}

sint32 func_80107110(sint32 arg)
{
    ST1A_TILE *tile;
    DR_MODE *mode;
    sint32 done;

    tile = (ST1A_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->code |= 2;
    done = 0;
    switch (arg)
    {
        case 0:
            if (D_80139734 < 25)
            {
                tile->r0 = tile->g0 = tile->b0 = D_80139734 * 2;
            }
            else
            {
                done     = 1;
                tile->r0 = tile->g0 = tile->b0 = 0x32;
            }
            if (D_80139734 < 0xFF)
            {
                D_80139734++;
            }
            break;
        case 1:
            tile->r0 = tile->g0 = tile->b0 = 0x32;
            break;
        case 2:
            if (D_80139734 < 25)
            {
                tile->r0 = tile->g0 = tile->b0 = 0x32 - D_80139734 * 2;
            }
            else
            {
                done     = 1;
                tile->r0 = tile->g0 = tile->b0 = 0;
            }
            if (D_80139734 < 0xFF)
            {
                D_80139734++;
            }
            break;
        case 3:
            tile->r0 = tile->g0 = tile->b0 = 0x30;
            break;
    }
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    if (arg != 3)
    {
        SetDrawMode(mode, 0, 0, 0x4F, NULL);
    }
    else
    {
        SetDrawMode(mode, 0, 0, 0x2F, NULL);
    }
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
    return done;
}
