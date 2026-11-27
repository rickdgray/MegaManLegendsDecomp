#include "common.h"
#include "st0b.h"

void func_801186E8(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356F = arg0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C356E = (uint8)Game_work.value_50;
}

void func_80118730(ST0B_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        wp->value_448 = 0;
        wp->u_C.b.byte_D++;
    }
}

void func_80118758(ST0B_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    switch (temp_v1)
    {
        case 0:
            wp->value_448    = 0xD;
            wp->u_E.b.byte_E = 0;
            wp->u_C.b.byte_D++;
            return;
        case 1:
            wp->u_E.b.byte_E++;
            wp->value_430 += 0xFFFB0000;
            if (wp->u_E.b.byte_E == 0x1E)
            {
                wp->u_C.b.byte_C = 0;
                wp->u_C.b.byte_D = 0;
            }
            return;
    }
}

void func_801187D4(ST0B_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    switch (temp_v1)
    {
        case 0:
            wp->value_448 = 0xC;
            wp->u_C.b.byte_D++;
            return;
        case 1:
            wp->value_430 += 0x50000;
            return;
    }
}

void func_80118824(ST0B_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        wp->value_448 = 0x80;
        wp->value_168 = 0;
        wp->value_169 = 0;
        wp->u_C.b.byte_D++;
    }
}

void func_80118854(STAGE_PL_SCRIPT *wp)
{
    D_80120314[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_801188B4(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(2);
            STAGE_PL.fixed_428.x = 0xFE000000;
            STAGE_PL.fixed_428.z = 0xFE000000;
            STAGE_PL.fixed_428.y = 0xFEFF0000;
        }
        else
        {
            func_801186E8(0);
            STAGE_PL.fixed_428.x = 0xC000000;
            STAGE_PL.fixed_428.z = 0x14000000;
            STAGE_PL.fixed_428.y = 0xFFFF0000;
        }
        pl->value_442 = 0x800;
    }
    if (wp->frame_10 == 0xA)
    {
        pl->routine_C = 1;
        pl->value_D   = 0;
    }
}

void func_80118978(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_FX *fx;

    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(6);
        }
        else
        {
            func_801186E8(1);
        }
        child          = wp->child_24;
        child->flags_0 = (uint8)child->flags_0 | 2;
    }
    if (wp->frame_10 == 5)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->x_1C    = 0x85;
            fx->y_1E    = -0x16E;
            fx->timer_D = 0;
            fx->z_20    = -0xC8;
        }
    }
    if (wp->frame_10 == 0x72)
    {
        child            = wp->child_24;
        child->routine_1 = 1;
    }
    if (wp->frame_10 == 0xAC)
    {
        child            = wp->child_24;
        child->routine_1 = 0;
    }
}

void func_80118A74(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(2);
        }
        else
        {
            func_801186E8(0);
        }
        wp->child_24->flags_0 &= ~2;
        pl->routine_C = 3;
        pl->value_D   = 0;
    }
    if (wp->frame_10 == 1)
    {
        pl->flags_0 &= ~1;
    }
    if (wp->frame_10 == 0x14)
    {
        pl->flags_0 |= 1;
    }
}

void func_80118B38(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        wp->child_28->flags_0 = (uint8)wp->child_28->flags_0 | 2;
        wp->child_2C->flags_0 = (uint8)wp->child_2C->flags_0 | 2;
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(7);
        }
        else
        {
            func_801186E8(2);
        }
        pl->fixed_428.x = 0;
        pl->fixed_428.z = 0;
        pl->fixed_428.y = 0;
        pl->value_D     = 0;
        pl->routine_C   = 0;
    }
    if (wp->frame_10 == 0xF)
    {
        wp->child_28->routine_1++;
        wp->child_2C->routine_1++;
    }
    if (wp->frame_10 == 0x46)
    {
        pl->routine_C = 2;
        pl->value_D   = 0;
    }
}

void func_80118C34(STAGE_ROOM *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    Obj_work_flag_change(0x56, 0x80);
    if (STAGE_GAME.value_50 == 0xB)
    {
        D_800BC7F0 = D_80120214;
    }
    else
    {
        D_800BC7F0 = D_80120114;
    }
    wp->tbl_A4 = D_80120324;
    for (i = 0; i < 10; i++)
    {
        Scene_obj_ent_open(&D_801200D8[i]);
    }
    STAGE_PL.routine_0 = 3;
    STAGE_PL.routine_1 = 1;
    STAGE_PL.value_C   = 0;
}

void func_80118D00(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80118D40(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                Sound_fade_start(0x10);
                func_8001B314();
                if (STAGE_GAME.value_50 == 0xB)
                {
                    Cd_xa_play_id(0x20010013);
                }
                else
                {
                    Cd_xa_play_id(0x2000000E);
                }
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x17;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            func_80118C34((STAGE_ROOM *)wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(0xA);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80118D00(wp);
            func_80118854((STAGE_PL_SCRIPT *)&Player_work);
            if (D_800C356C_A[0] == -1)
            {
                D_800C3560 = STAGE_PL.fixed_428.x >> 16;
                D_800C3562 = STAGE_PL.fixed_428.y >> 16;
                D_800C3564 = STAGE_PL.fixed_428.z >> 16;
                D_800C356A = STAGE_PL.value_442;
            }
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 5 && D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                if (STAGE_GAME.value_50 == 0xB)
                {
                    D_800C356C_A[0] = 2;
                    D_800C356E      = 0x14;
                    D_800C3560      = 0x100;
                    D_800C3562      = -1;
                    D_800C3564      = -0x7300;
                    D_800C356F      = 0;
                    D_800C356A      = 0;
                    D_800C356D      = 0;
                    D_800C3571      = 0xFF;
                    D_800C3570      = 2;
                }
                else
                {
                    D_800C356C_A[0] = 2;
                    D_800C356E      = 0xE;
                    D_800C3560      = -0xC6B;
                    D_800C3562      = -0x181;
                    D_800C3564      = 0xB00;
                    D_800C356A      = 0x400;
                    D_800C356F      = 0;
                    D_800C356D      = 0;
                    D_800C3571      = 0xFF;
                    D_800C3570      = 2;
                }
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}
