#include "common.h"
#include "st00.h"

void func_801010C4(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_80042238(&Player_work) != 0)
            {
                Player_work.flags_0 &= ~3;
                wp->routine_4++;
            }
            break;
        case 2:
            Sound_seq_stop_all();
            Cd_xa_play_id(0x20000003);
            wp->routine_4++;
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x37;
                wp->routine_4++;
            }
            break;
        case 4:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
                Fade_start(2);
            }
            break;
        case 5:
            func_80100EFC((ST00_ROOM_FX *)wp);
            wp->routine_4++;
            break;
        case 6:
            func_8010102C(wp);
            Sce_camera_update();
            Sce_event_update();
            if (D_80098A72 == 0 && ((wp->reserved09[0] == 0x13 && wp->frame_10 == 0x2C) || func_8001DE84() != 0))
            {
                Fade_start(0xA);
                wp->routine_4++;
            }
            if (D_80122428 != 0)
            {
                func_80100614(D_8012242C, D_80122430, D_80122434, D_80122438);
            }
            break;
        case 7:
            func_8010102C(wp);
            Sce_camera_update();
            Sce_event_update();
            if (D_80098A72 == 0)
            {
                D_800C356C = 2;
                D_800C356E = 0;
                D_800C356F = 1;
                D_800C3560 = 0xB06;
                D_800C3562 = -1;
                D_800C3564 = -0x12E1;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 2;
                Sce_flag_off(0x604);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
            }
            if (D_80122428 != 0)
            {
                func_80100614(D_8012242C, D_80122430, D_80122434, D_80122438);
            }
            break;
    }
}

void func_80101364(STAGE_ROOM *wp)
{
    STCOM_SVECTOR unused;
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        child->scale.v.pad = 0x2108;
    }
    if (wp->frame_10 == 0x14A)
    {
        wp->child_2C->u_C.b.byte_C = wp->child_30->u_C.b.byte_C = 1;
    }
    if (wp->frame_10 == 0x1AE)
    {
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x1B8)
    {
        child->routine_3 = 1;
    }
    if (wp->frame_10 == 0x1EF)
    {
        wp->child_2C->u_C.b.byte_C = wp->child_30->u_C.b.byte_C = 2;
    }
    if (wp->frame_10 == 0x219)
    {
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
}

void func_8010141C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->flags_0 |= 2;
        wp->child_24->routine_1 = 3;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x82)
    {
        wp->child_2C->u_C.b.byte_C = wp->child_30->u_C.b.byte_C = 1;
    }
}

void func_8010148C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 4;
        wp->child_24->routine_2 = 0;
    }
}

void func_801014BC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 5;
        wp->child_24->routine_2 = 0;
    }
}

void func_801014EC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position_fixed.v.x = 0x01F40000;
        child->position_fixed.v.y = -0x1C010000;
        child->position_fixed.v.z = 0x01800000;
        child->scale.v.pad        = 0x4210;
    }
}

void func_80101528(STAGE_ROOM *wp)
{
    STAGE_FX *fx;

    if (wp->frame_10 == 0)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->x_1C    = 0x1F4;
            fx->y_1E    = -0x1D50;
            fx->timer_D = 0;
            fx->z_20    = 0xEC;
        }
    }
}

void func_80101598(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 6;
        wp->child_24->routine_2 = 0;
    }
}

void func_801015C8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child             = wp->child_24;
        child->rotation.y = 0x800;
        child->routine_1  = 7;
        child->routine_2  = 0;
    }
    if (wp->frame_10 == 0x2D)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80101618(void)
{
}

void func_80101620(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_24;
        child->routine_1          = 8;
        child->routine_2          = 0;
        child->position_fixed.v.z = -0x03E00000;
        child                     = wp->child_28;
        child->routine_1          = 0;
        child->routine_2          = 0;
    }
}

void func_80101660(void)
{
}

void func_80101668(void)
{
}

void func_80101670(void)
{
}

void func_80101678(void)
{
}

void func_80101680(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        wp->child_24->routine_1 = 9;
        wp->child_24->routine_2 = 0;
    }
}

void func_801016B0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_28;
    if (wp->frame_10 == 0)
    {
        child->routine_1          = 3;
        child->routine_2          = 0;
        child->position_fixed.v.z = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        child->routine_1 = 0;
        child->routine_2 = 0;
    }
}

void func_801016EC(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;

    if (wp->frame_10 == 0)
    {
        pos.x = 0x260;
        pos.y = -0x1D70;
        pos.z = -0xF0;
        func_8011877C(&pos, 0x250, 0x50);
        pos.x = 0x1D0;
        pos.y = -0x1D70;
        pos.z = -0xB0;
        func_8011877C(&pos, 0x250, 0x8E0);
    }
}

void func_80101764(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        child->position_fixed.v.z = -0x03C80000;
        child->routine_1          = 0xA;
        child->routine_2          = 0;
    }
}

void func_8010178C(void)
{
}

void func_80101794(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0x3C)
    {
        child            = wp->child_24;
        child->routine_1 = 0xB;
        other            = wp->child_24;
        other->routine_2 = 0;
        child            = wp->child_34;
        child->flags_0 |= 2;
        child            = wp->child_34;
        child->routine_1 = 1;
    }
}

void func_801017E8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position_fixed.v.z = -0x01C00000;
    }
}

void func_8010180C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_28->routine_1 = 2;
        wp->child_28->routine_2 = 0;
    }
}

void func_8010183C(void)
{
}

void func_80101844(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0;
        child            = wp->child_28;
        child->routine_2 = 0;
        other            = wp->child_34;
        other->routine_2 = 2;
    }
}

void func_80101880(void)
{
}

void func_80101888(STAGE_ROOM *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_8011B4B4;
    for (i = 0; i < 14; i++)
    {
        Scene_obj_ent_open(&D_8011B388[i]);
    }
    wp->tbl_A4 = D_8011BA4C;
}

void func_8010190C(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_8010194C(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_80042238(&Player_work) != 0)
            {
                Player_work.flags_0 &= ~3;
                wp->routine_4++;
            }
            break;
        case 2:
            Sound_seq_stop_all();
            Cd_xa_play_id(0x20000002);
            wp->routine_4++;
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x1E;
                wp->routine_4++;
            }
            break;
        case 4:
            if (--wp->timer_C == 0)
            {
                Fade_start(2);
                wp->routine_4++;
            }
            break;
        case 5:
            func_80101888(wp);
            wp->routine_4++;
            break;
        case 6:
            if (D_80098A72 == 0 && (func_8001DE84() != 0 || wp->routine_8 == 0xFF))
            {
                Fade_start(0xA);
                wp->routine_4++;
            }
            // fall through
        case 7:
            func_8010190C(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 7 && D_80098A72 == 0)
            {
                D_800C356C = 2;
                D_800C356E = 2;
                D_800C356F = 0;
                D_800C3560 = 0;
                D_800C3562 = 0;
                D_800C3564 = 0;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 0xFF;
                Sce_flag_off(0x605);
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
            }
            break;
    }
}

void func_80101B6C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0xF)
    {
        wp->child_28->routine_1 = 1;
        wp->child_28->routine_2 = 0;
    }
}

void func_80101B9C(STAGE_ROOM *wp)
{
    STCOM_SVECTOR pos;
    sint16 x;
    sint16 y;
    sint16 z;

    x = wp->child_28->position.x;
    y = wp->child_28->position.y;
    z = wp->child_28->position.z;
    if (wp->frame_10 == 0)
    {
        wp->child_28->routine_1 = 3;
        wp->child_28->routine_2 = 0;
    }
    if (wp->frame_10 == 0xE6)
    {
        pos.x      = x - 0x40;
        pos.y      = y - 0x174;
        pos.z      = z + 0x58;
        D_8012243C = func_80116D60(&pos, 1, 1, 0, -2, 0);
        pos.x      = -0x15E;
        pos.y      = -0x226;
        pos.z      = -0x384;
        D_8012244C = func_80116D60(&pos, 1, 1, 0, -2, 0);
    }
    if (wp->frame_10 == 0xF0)
    {
        pos.x      = x + 0x7E;
        pos.y      = y - 0x180;
        pos.z      = z + 0x28;
        D_80122440 = func_80116D60(&pos, 1, 1, 0, -2, 0);
    }
    if (wp->frame_10 == 0xF5)
    {
        pos.x      = x + 0x38;
        pos.y      = y - 0xE8;
        pos.z      = z + 0x78;
        D_80122444 = func_80116D60(&pos, 1, 1, 0, -2, 0);
    }
    if (wp->frame_10 == 0x104)
    {
        pos.x      = x - 0x28;
        pos.y      = y - 0x128;
        pos.z      = z + 0xC4;
        D_80122448 = func_80116D60(&pos, 1, 1, 0, -2, 0);
    }
}

void func_80101D80(void)
{
}

void func_80101D88(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x23)
    {
        ((ST00_OBJ *)wp->child_28)->part_100[10].value_0 = 0xC;
    }
}

void func_80101DAC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 1;
        wp->child_24->routine_2 = 0;
    }
}

void func_80101DDC(void)
{
}

void func_80101DE4(STAGE_ROOM *wp)
{
    STAGE_FX *ep;

    if (wp->frame_10 == 0)
    {
        wp->child_28->routine_1 = 0;
        wp->child_28->routine_2 = 0;
        wp->child_24->routine_1 = 0;
        wp->child_24->routine_2 = 0;
        func_80031988(D_8012243C);
        func_80031988(D_80122440);
        func_80031988(D_80122444);
        func_80031988(D_80122448);
        func_80031988(D_8012244C);
    }
    if (wp->frame_10 == 0x3C)
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0 = 1;
            ep->kind_2  = 5;
            ep->value_C = 5;
            ep->frame_E = 2;
            ep->x_1C    = -0x100;
            ep->y_1E    = -0x2D8;
            ep->timer_D = 0;
            ep->z_20    = -0x370;
        }
    }
}

void func_80101EF0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_28->routine_1                          = 2;
        wp->child_28->routine_2                          = 0;
        ((ST00_OBJ *)wp->child_28)->part_100[10].value_0 = 0xD;
        Obj_work_flag_change(0x40, 0x80);
    }
}

void func_80101F44(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_24;
        child->routine_1 = 0;
        child            = wp->child_24;
        child->routine_2 = 0;
    }
}

void func_80101F74(void)
{
}

void func_80101F7C(STAGE_ROOM *wp)
{
    STCOM_SVECTOR unused;

    Player_work.flags_0 &= ~3;
    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_8011BB3C;
    D_800C3588 = 2;
    Scene_obj_ent_open(&D_8011BB14[0]);
    Scene_obj_ent_open(&D_8011BB14[1]);
    wp->tbl_A4        = D_8011BE44;
    wp->reserved09[2] = 0;
    wp->reserved09[1] = 0;
    wp->timer_C       = 0;
}

void func_80102018(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80102058(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    switch (wp->routine_4)
    {
        case 0:
            func_8005D7C0();
            if (func_80042238(&Player_work) != 0)
            {
                wp->routine_4++;
            }
            break;
        case 1:
            Sound_seq_stop_all();
            Cd_xa_play_id(0x20000001);
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x1E;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 4:
            func_80101F7C(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (D_80098A72 == 0 && (wp->routine_8 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(0xA);
                wp->routine_4++;
            }
            // fall through
        case 6:
            func_80102018(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 6 && D_80098A72 == 0)
            {
                func_8005D9EC();
                D_800C356C = 2;
                D_800C356F = 4;
                D_800C356E = 0;
                D_800C3560 = 0;
                D_800C3562 = 0;
                D_800C3564 = 0;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 0xFF;
                Sce_flag_off(0x606);
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                pl = &Player_work;
                pl->flags_0 |= 1;
                func_80042314(pl);
            }
            break;
    }
}
