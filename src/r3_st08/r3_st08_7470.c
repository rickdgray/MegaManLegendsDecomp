#include "common.h"
#include "st08.h"

void func_80107470(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_80113AF4[wp->routine_0](wp);
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_2 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_2++;
    }
}

void func_80107560(STAGE_ACTOR *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_1;
    switch (temp_v1)
    {
        case 0:
            func_80107620(wp);
            wp->routine_1++;
            return;
        case 1:
            if (D_80098A72 == 0)
            {
                MojiTaskExec2(0, 3);
                wp->routine_1++;
            }
        case 2:
            Obj_pos_set(wp, 0x90, 0, 0);
            return;
    }
}

void func_80107620(STAGE_ACTOR *wp)
{
    sint16 y;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->turn_64    = 0x80;
    wp->be_flag |= 2;
    Model_work_init(wp, &wp->type);
    wp->scale.words[0]   = 0x2000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    y                    = Obj_ceiling_height_get(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 16;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    func_800322A8(wp, 2, 0);
    wp->routine_2 = 0;
}

void func_801076BC(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_80113AF8[wp->routine_0](wp);
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_2 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_2++;
    }
}

void func_801077AC(STAGE_ACTOR *wp)
{
    STAGE_CAM *cam;
    STAGE_PL_VIEW *pl;
    uint16 turn;
    uint16 pl_turn;

    cam = &Sce_camera_work;
    pl  = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            func_80107AE4(wp);
            func_8001E6C0(0, 0, 0);
            cam->pos_10 = -0x93 << 16;
            cam->pos_14 = -0xE0 << 16;
            cam->pos_18 = 0x18A << 16;
            cam->rot_40 = 0x6F2 << 16;
            cam->rot_44 = 0xB6 << 16;
            cam->rot_48 = 0x200 << 16;
            wp->routine_1++;
            break;
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            pl->value_448   = 0x30;
            pl->pos_438.x   = 0x64;
            pl->pos_438.y   = -1;
            pl->pos_438.z   = -0xDE;
            pl->value_442   = 0x800;
            pl->fixed_428.x = pl->pos_438.x << 16;
            pl->fixed_428.y = pl->pos_438.y << 16;
            pl->fixed_428.z = pl->pos_438.z << 16;
            wp->routine_1++;
            // fall through
        case 3:
            if (D_80098A72 == 0)
            {
                func_800322A8(wp, 1, 0);
                wp->routine_2 = 0;
                wp->routine_1++;
            }
            break;
        case 4:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            pl_turn        = Muku(&pl->position, &wp->position, pl->rotation.y, wp->turn_64);
            pl->value_442  = (pl->rotation.y + pl_turn) & 0xFFF;
            if (turn + pl_turn == 0)
            {
                MojiTaskExec2(0, 0x2A);
                func_800322A8(wp, 2, 0);
                wp->routine_2 = 0;
                wp->timer_C   = 0x28;
                wp->routine_1++;
            }
            break;
        case 5:
            Obj_pos_set(wp, 0x80, 0, 0);
            if (--wp->timer_C == 0)
            {
                func_800322A8(wp, 0, 0);
                wp->routine_2 = 0;
                wp->routine_1++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0x2B);
                func_800322A8(wp, 8, 0);
                cam->pos_10 = 0;
                cam->pos_14 = -0x64 << 16;
                cam->pos_18 = 0;
                cam->rot_40 = 0xEEE << 16;
                cam->rot_44 = 0x30 << 16;
                cam->rot_48 = 0xFA << 16;
                pl->be_flag &= ~2;
                wp->routine_2 = 0;
                wp->routine_1++;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x8000000))
            {
                D_800A395C = 1;
                func_80039820();
                func_80042314(pl);
                pl->be_flag |= 2;
                wp->reserved04[0] = 0;
                wp->timer_C       = 0x2C;
                wp->value_D       = 0;
                wp->value_E       = 0;
                wp->reserved0F    = 0;
                wp->routine_0     = 0;
                wp->routine_1     = 0;
                wp->routine_2     = 0;
                wp->routine_3     = 0;
                Sce_flag_on(0x234);
                func_8001E390(0x2E9);
            }
            break;
    }
}

void func_80107AE4(STAGE_ACTOR *wp)
{
    sint16 temp_v0;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->turn_64    = 0x80;
    wp->be_flag |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    temp_v0              = Obj_ceiling_height_get(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_2 = 0;
}
