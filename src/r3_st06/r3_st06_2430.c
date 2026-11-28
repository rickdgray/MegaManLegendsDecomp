#include "common.h"
#include "st06.h"

void func_80102430(STAGE_ROOM *wp)
{
    D_801231D4[wp->routine_4](wp);
}

void func_8010246C(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            func_8001E6C0(0, 0, 0);
            D_800BC7F0        = D_801231F4;
            wp->tbl_A4        = D_80123240;
            wp->timer_C       = 0;
            wp->reserved09[1] = 0;
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->pos_438.y = -1;
                pl->pos_438.z = -0x2580;
                pl->value_442 = 0x800;
                pl->pos_438.x = 0;
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->value_448 = 0x30;
                D_800C0F96[0] = 0;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                Scene_obj_ent_open(D_801231E0);
                wp->routine_5++;
            }
            break;
        case 2:
            pl->routine_1++;
            wp->routine_5++;
            break;
        case 3:
            Sound_work.volume_6 = 0x6E;
            pl->flags_bd |= 0x20;
            Cd_xa_play_id(0xB000A);
            wp->routine_5++;
            break;
        case 4:
            if (func_8001D878())
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_80123250;
                wp->tbl_A4    = D_80123468;
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_8010263C(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        if (func_8001DE84())
        {
            wp->reserved09[1] = 1;
            wp->routine_5     = 0;
            wp->routine_4++;
        }
        wp->tbl_A4[1](wp);
    }
    else
    {
        wp->routine_5 = 1;
        wp->routine_4++;
    }
    Sce_event_update();
}

void func_801026CC(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8003697C();
            Player_work.routine_0 = 3;
            Player_work.routine_1 = 1;
            STAGE_PL.pos_438.x    = -0x72D;
            STAGE_PL.pos_438.y    = -0x301;
            STAGE_PL.pos_438.z    = 0x9D;
            STAGE_PL.fixed_428.x  = 0xF8D30000;
            STAGE_PL.fixed_428.y  = 0xFCFF0000;
            STAGE_PL.fixed_428.z  = 0x9D0000;
            STAGE_PL.value_440    = 0;
            STAGE_PL.value_442    = 0xA08;
            STAGE_PL.value_444    = 0;
            STAGE_PL.value_448    = 0;
            STAGE_PL.flags_bd |= 0x10;
            wp->routine_5++;
            break;
        case 1:
            Cd_subcmd(0, 1, 0);
            func_80031824(wp->child_24);
            func_80042314(&Player_work);
            if (wp->reserved09[1] != 0)
            {
                D_800A395C = 1;
                func_80039820();
            }
            wp->routine_5++;
            break;
        case 2:
            if (Sound_fade_flags == 0)
            {
                MojiTaskExec2(0, 0xB);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                Sound_call(9, 0, 0);
                wp->routine_5++;
            }
            break;
        case 4:
            wp->flags_0 = 0;
            break;
    }
}

void func_80102878(void)
{
    Sce_camera_update();
}

void func_80102898(void)
{
    Sce_camera_update();
}

void func_801028B8(STAGE_ROOM *wp)
{
    D_800C0F96[0] = 0;
    if (wp->frame_10 >= 0x131)
    {
        D_800C0F96[0] = STAGE_PL.value_124;
    }
    Sce_camera_update();
}

void func_80102908(STAGE_ROOM *wp)
{
    STAGE_PL_PAD *pad;
    uint16 held;

    pad = (STAGE_PL_PAD *)&Player_work;
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -0x804;
        STAGE_PL.pos_438.y   = -1;
        STAGE_PL.pos_438.z   = -0xE20;
        STAGE_PL.fixed_428.x = 0xF7FC0000;
        STAGE_PL.fixed_428.y = 0xFFFF0000;
        STAGE_PL.fixed_428.z = 0xF1E00000;
        STAGE_PL.value_440   = 0;
        STAGE_PL.value_442   = 0x800;
        STAGE_PL.value_444   = 0;
        STAGE_PL.flags_bd |= 0x10;
    }
    else if (wp->frame_10 == 1)
    {
        D_800A395C = 1;
        func_80039820();
    }
    D_800C0F96[0] = 0;
    if (wp->frame_10 < 0x78)
    {
        held          = pad->pad_124;
        D_800C0F96[0] = held;
        if ((uint32)(wp->frame_10 - 0x69) < 0xD)
        {
            D_800C0F96[0] = held | pad->pad_12A;
        }
    }
}

void func_80102A34(STAGE_ROOM *wp)
{
    D_80123490[wp->routine_4](wp);
}

void func_80102A70(STAGE_ROOM *wp)
{
    if (func_80042238(&Player_work))
    {
        if (Sce_flag_test(0x626))
        {
            wp->reserved09[2] = 4;
            wp->routine_4     = 4;
        }
        else
        {
            if (Sce_flag_test(0x622) && !Sce_flag_test(0x62A))
            {
                Sce_flag_on(0x62A);
                wp->reserved09[2] = 0;
            }
            else
            {
                if (Sce_flag_test(0x623))
                {
                    wp->reserved09[2] = 1;
                }
                if (Sce_flag_test(0x624))
                {
                    wp->reserved09[2] = 2;
                }
                if (Sce_flag_test(0x625))
                {
                    wp->reserved09[2] = 3;
                }
            }
            wp->routine_4 = 1;
        }
        wp->routine_5 = 0;
    }
}

void func_80102B3C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            Cd_xa_play_id(D_801238F4[wp->reserved09[2]]);
            wp->routine_5++;
            break;
        case 1:
            if (func_8001D878())
            {
                func_8001E6C0(0, 0, 0);
                D_800BC7F0            = D_801238CC[wp->reserved09[2]];
                wp->tbl_A4            = D_801238E0[wp->reserved09[2]];
                wp->timer_C           = 0;
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                pl->flags_0 &= ~2;
                wp->reserved09[1] = 0;
                Sce_camera_update();
                Sce_event_update();
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
}

void func_80102C5C(ST06_OBJ *wp)
{
    uint8 temp_v1;

    if (func_8001DE84() != 0)
    {
        wp->routine_2 |= 1;
    }
    if ((wp->routine_0 == 0xFF) || ((temp_v1 = wp->routine_2, ((temp_v1 & 1) != 0)) && !(temp_v1 & 0x80)))
    {
        wp->value_5 = 0;
        wp->value_4++;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80102CE8(sint8 *arg0)
{
    Cd_subcmd(0, 1, 0);
    func_8003697C();
    func_80042314((STCOM_PL_WORK *)&Player_work);
    D_800A395C = 1;
    func_80039820();
    Sce_flag_off(0x621);
    *arg0 = 0;
}

void func_80102D54(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    Obj_work_flag_change(0x1A, 0x80);
    func_8001E6C0(0, 0, 0);
    D_800BC7F0            = D_801238CC[wp->reserved09[2]];
    pl                    = &Player_work;
    wp->tbl_A4            = D_801238E0[wp->reserved09[2]];
    wp->timer_C           = 0;
    Player_work.routine_0 = 3;
    Player_work.routine_1 = 1;
    STAGE_PL.pos_438.x    = 0x200;
    STAGE_PL.pos_438.y    = -1;
    STAGE_PL.fixed_428.x  = 0x2000000;
    STAGE_PL.fixed_428.y  = 0xFFFF0000;
    STAGE_PL.pos_438.z    = 0;
    STAGE_PL.fixed_428.z  = 0;
    STAGE_PL.value_440    = 0;
    STAGE_PL.value_442    = 0x800;
    STAGE_PL.value_444    = 0;
    STAGE_PL.value_448    = 0;
    pl->flags_0 &= ~2;
    STAGE_PL.flags_bd |= 0x10;
    Scene_obj_ent_open(D_801234AC);
    wp->reserved09[1] = 0x80;
    func_8001F580(0x60, 0, 1);
    wp->routine_5 = 0;
    wp->routine_4++;
    Sce_camera_update();
    Sce_event_update();
}

void func_80102EB8(STAGE_ROOM *wp)
{
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    if (wp->routine_8 == 0xFF)
    {
        wp->routine_5 = 0;
        wp->routine_4++;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if ((wp->reserved09[1] & 1) && !(wp->reserved09[1] & 0x80))
        {
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80102F5C(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    ST06_CRAB *crab;

    crab = (ST06_CRAB *)wp->child_24;
    Cd_subcmd(0, 1, 0);
    func_8003697C();
    D_800A395C = 1;
    if (wp->reserved09[1] & 1)
    {
        pl = &Player_work;
        pl->flags_0 |= 2;
        crab->position.x         = 0x200;
        crab->position.y         = -0x4B0;
        crab->position.z         = 0x800;
        crab->rotation.y         = 0;
        crab->position_fixed.v.x = crab->position.x << 16;
        crab->position_fixed.v.y = crab->position.y << 16;
        crab->position_fixed.v.z = crab->position.z << 16;
        func_80039820();
    }
    else
    {
        func_8003A264();
    }
    func_80042314(&Player_work);
    Sce_flag_off(0x621);
    func_801188E4(crab);
    func_8003187C(crab);
    wp->flags_0 = 0;
}

void func_8010305C(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            if (Sound_fade_flags == 0)
            {
                Sound_call(0xA, 0, 0);
                wp->routine_6++;
            }
            break;
        case 1:
            if (Cd_read_sync2() == 0 && wp->frame_10 > 0x64)
            {
                Cd_xa_play_id(0x20000013);
                wp->routine_6++;
            }
            break;
        case 2:
            if (func_8001D878())
            {
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_8010313C(STAGE_OBJ *wp)
{
    if (wp->value_10 == 2)
    {
        wp->routine_2 &= 0x7F;
    }
}

void func_80103164(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->position.x         = -0x6E0;
        child->position.y         = -0x640;
        child->position.z         = 0x20D0;
        child->rotation.y         = 0xF80;
        child->position_fixed.v.x = child->position.x << 16;
        child->position_fixed.v.y = child->position.y << 16;
        child->position_fixed.v.z = child->position.z << 16;
    }
}

void func_801031C4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        pl = &Player_work;
        pl->flags_0 |= 2;
        child                     = wp->child_24;
        child->position.x         = 0x200;
        child->position.y         = -0x708;
        child->position.z         = 0x800;
        child->rotation.y         = 0;
        child->position_fixed.v.x = child->position.x << 16;
        child->position_fixed.v.y = child->position.y << 16;
        child->position_fixed.v.z = child->position.z << 16;
    }
}

void func_80103238(void)
{
}

void func_80103240(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_0 = 2;
    }
    if (wp->frame_10 == 0x59)
    {
        child            = wp->child_24;
        child->routine_0 = 1;
    }
}

void func_80103280(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0xF)
    {
        child            = wp->child_2C;
        child->routine_0 = 2;
    }
    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_28;
        child->routine_0 = 5;
    }
    if (wp->frame_10 == 0x37)
    {
        child            = wp->child_28;
        child->routine_0 = 3;
    }
    if (wp->frame_10 == 0x3B)
    {
        child            = wp->child_2C;
        child->routine_0 = 1;
        child            = wp->child_28;
        child->routine_0 = 4;
    }
}

void func_80103304(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_0 = 4;
        child            = wp->child_28;
        child->routine_0 = 2;
    }
    if (wp->frame_10 == 0x3B)
    {
        Fade_start(0xA);
    }
    if (wp->frame_10 == 0x59)
    {
        child            = wp->child_24;
        child->routine_0 = 1;
    }
}

void func_80103384(void)
{
}

void func_8010338C(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    D_800BC7F0        = D_80123944;
    wp->tbl_A4        = D_801239C0;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
    wp->reserved09[1] = 0; // stored twice in retail
    Obj_work_flag_change(0x56, 0x80);
}

void func_801033F8(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}
