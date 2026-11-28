#include "common.h"
#include "st08.h"

void func_80101FA4(STAGE_ROOM *wp)
{
    D_80113228[wp->routine_4](wp);
}

void func_80101FE0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_EV *slot;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            slot = Scene_obj_ent_open(D_80113238);
            slot->flags_6 &= ~0x20;
            func_8001E6C0(0, 0, 0);
            D_800BC7F0 = D_8011324C;
            wp->tbl_A4 = (STAGE_ROOM2_FUNC *)D_801132EC;
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->flags_0 &= ~2;
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->routine_4++;
                Sce_event_next();
            }
            break;
    }
}

void func_801020C4(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84())
        {
            Fade_start(0xA);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    else
    {
        wp->routine_5 = 0;
        wp->routine_4 += 2;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80102158(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (D_80098A72 == 0)
    {
        wp->routine_4++;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_801021D8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            wp->routine_5++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                func_8003697C();
                func_80042314(pl);
                D_800A395C = 1;
                func_80039820();
                wp->routine_5++;
            }
            break;
        case 2:
            D_800C356C = 2;
            D_800C356E = 8;
            D_800C356F = 1;
            D_800C3560 = -0x100;
            D_800C3562 = -1;
            D_800C3564 = 0x80;
            D_800C356A = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 2;
            pl->flags_0 |= 3;
            Sce_flag_on(0x22E);
            wp->flags_0 = 0;
            break;
    }
}

void func_80102320(void)
{
}

void func_80102328(STAGE_FX *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->flags_6;
    switch (temp_v1)
    {
        case 0:
            Fade_start(0xA);
            wp->flags_6++;
            return;
        case 1:
            if (D_80098A72 == 0)
            {
                Sce_event_next();
            }
            return;
    }
}

void func_801023A4(STAGE_ROOM *wp)
{
    if (func_80042238(&Player_work))
    {
        ST08_PL->routine_1 = 0x10;
        ST08_PL->flags_bd |= 0x10;
        ST08_PL->rot_440.x   = 0;
        ST08_PL->rot_440.z   = 0;
        ST08_PL->value_A     = 0;
        D_80118514           = 0;
        ST08_PL->pos_438.x   = ST08_PL->position.x;
        ST08_PL->pos_438.y   = ST08_PL->position.y;
        ST08_PL->pos_438.z   = ST08_PL->position.z;
        ST08_PL->fixed_428.x = ST08_PL->pos_438.x << 16;
        ST08_PL->fixed_428.y = ST08_PL->pos_438.y << 16;
        ST08_PL->fixed_428.z = ST08_PL->pos_438.z << 16;
        ST08_PL->rot_440.y   = ST08_PL->rotation.y;
        wp->routine_5        = 0;
        wp->routine_6        = 0;
        wp->routine_7        = 0;
        wp->routine_4++;
    }
}

void func_80102498(STAGE_ROOM *wp)
{
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR pos;
    ST08_PL_WORK *pl;
    STAGE_CAM *cam;
    ST08_ACTOR *actor;
    STAGE_OBJ *other;
    sint16 turn;

    pl    = ST08_PL;
    cam   = &Sce_camera_work;
    actor = (ST08_ACTOR *)wp->child_24;
    other = wp->child_28;
    switch (wp->routine_5)
    {
        case 0:
            pos   = actor->position;
            vec.x = actor->position.x;
            vec.y = actor->position.y - 0x92;
            vec.z = actor->position.z;
            func_80039FFC(&vec, 0xD4, Angle_xz_svector(&pos, &pl->position), 0);
            pl->flags_0 &= ~2;
            wp->routine_5++;
            break;
        case 1:
            turn = Muku(&actor->position, &pl->pos_438, actor->rotation.v.y, 0x80);
            actor->rotation.v.y += turn;
            if (!func_8003A13C() && turn == 0)
            {
                actor->value_D = 9;
                actor->value_E = 1;
                wp->frame_10   = 0x10;
                wp->routine_5++;
            }
            break;
        case 2:
            if (--wp->frame_10 == 0)
            {
                MojiTaskExec2(0, 0x1B);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                actor->value_D = 5;
                actor->value_E = 1;
                wp->frame_10   = 0x22;
                wp->routine_5++;
            }
            break;
        case 4:
            if (--wp->frame_10 == 0)
            {
                func_80039E50();
                actor->rotation.v.y     = 0xA78;
                actor->value_D          = 6;
                actor->value_E          = 1;
                actor->position.x       = -0x4CE;
                actor->position.z       = 0x71C;
                actor->position_fixed.x = actor->position_fixed_prev.x = actor->position.x << 16;
                actor->position_fixed.z = actor->position_fixed_prev.z = actor->position.z << 16;
                pl->pos_438.x                                          = -0x514;
                pl->pos_438.z                                          = 0x692;
                pl->flags_0 |= 2;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                pl->rot_440.y   = Angle_xz_svector(&pl->pos_438, &actor->position);
                func_8001E6C0(0, 0, 0);
                cam->pos_10  = -0x365 << 16;
                cam->pos_14  = -0x2D1 << 16;
                cam->pos_18  = 0x73C << 16;
                cam->rot_40  = 0xBA9 << 16;
                cam->rot_44  = 0xF0 << 16;
                cam->rot_48  = 0;
                wp->frame_10 = 0x3C;
                wp->routine_5++;
            }
            break;
        case 5:
            if (--wp->frame_10 == 0)
            {
                actor->value_D = 7;
                actor->value_E = 1;
                wp->frame_10   = 0x2D;
                wp->routine_5++;
            }
            break;
        case 6:
            if (--wp->frame_10 == 0)
            {
                actor->value_D = 9;
                actor->value_E = 1;
                wp->frame_10   = 0x14;
                wp->routine_5++;
            }
            break;
        case 7:
            if (--wp->frame_10 == 0)
            {
                MojiTaskExec2(0, 0x1C);
                actor->value_D = 10;
                actor->value_E = 1;
                wp->routine_5++;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                actor->value_D = 0xD;
                actor->value_E = 1;
                wp->frame_10   = 10;
                wp->routine_5++;
            }
            break;
        case 9:
            turn = Muku(&actor->position, &pl->pos_438, actor->rotation.v.y, 0x80);
            actor->rotation.v.y += turn;
            if (turn == 0)
            {
                MojiTaskExec2(0, 0x24);
                actor->value_D = 8;
                actor->value_E = 1;
                wp->routine_5++;
            }
            break;
        case 10:
            if (!(Moji_flag & 0x8000000))
            {
                func_80031824(other);
                cam->pos_10             = -0x52E << 16;
                cam->pos_14             = -0x271 << 16;
                cam->pos_18             = 0x6A1 << 16;
                cam->rot_40             = 0x9F9 << 16;
                cam->rot_44             = 0x40 << 16;
                cam->rot_48             = 0x150 << 16;
                actor->position.x       = -0x4B0;
                actor->position.z       = 0x5DC;
                actor->position_fixed.x = actor->position.x << 16;
                actor->position_fixed.z = actor->position.z << 16;
                pos.x                   = -0xF9E;
                pos.y                   = -0x2F0;
                pos.z                   = -0x1E0;
                actor->rotation.v.y     = Angle_xz_svector(&actor->position, &pos);
                actor->velocity.v.x     = 0x320;
                actor->value_D          = 2;
                actor->value_E          = 1;
                pl->flags_bd |= 0x10;
                pl->rot_440.y = Angle_xz_svector(&pl->pos_438, &actor->position);
                wp->routine_5++;
            }
            break;
        case 11:
            if (actor->position.x < -0xC1C)
            {
                actor->rotation.v.y = 0;
                wp->routine_5++;
            }
            else
            {
                pl->flags_bd |= 0x10;
                pl->rot_440.y = Angle_xz_svector(&pl->pos_438, &actor->position);
            }
            break;
        case 12:
            if (actor->position.z < -0x190)
            {
                actor->rotation.v.y = 0xC00;
                wp->routine_5++;
            }
            break;
        case 13:
            if (actor->position.x >= -0x7CF)
            {
                func_80031824(actor);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() && wp->routine_4 == 1)
    {
        if (wp->routine_5 < 5)
        {
            func_80039E50();
        }
        func_80053AA4(0);
        D_80118514    = 1;
        wp->routine_5 = 0;
        wp->routine_4++;
    }
}

void func_80102A24(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            ST08_PL->flags_bd |= 0x10;
            if (D_80118514 != 0)
            {
                ST08_PL->pos_438.x   = -0x514;
                ST08_PL->pos_438.z   = 0x692;
                ST08_PL->fixed_428.x = -0x514 << 16;
                ST08_PL->fixed_428.z = 0x692 << 16;
                func_80031824(wp->child_24);
                func_80031824(wp->child_28);
            }
            ST08_PL->rot_440.y = 0x400;
            wp->routine_5++;
            break;
        case 1:
            Cd_subcmd(0, 1, 0);
            Sce_flag_off(0x549);
            Sce_flag_on(0x37);
            func_8001E3F0(0x18);
            func_8001E390(0x2E8);
            func_80042314(&Player_work);
            D_800A395C = 1;
            ST08_PL->value_A++;
            func_80039820();
            wp->flags_0 = 0;
            break;
    }
}

void func_80102B58(STAGE_ROOM *wp)
{
    D_8011330C[wp->routine_4](wp);
}
