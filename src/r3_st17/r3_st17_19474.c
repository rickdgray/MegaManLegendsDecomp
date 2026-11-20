#include "common.h"
#include "st17.h"

void func_80119474(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;
    sint32 mask;

    switch (wp->routine_6)
    {
        case 0:
            mask = ~2; // one register for both clears (retail ands with -3)
            Player_work.flags_0 &= mask;
            wp->child_24->flags_0 &= mask;
            wp->child_24->routine_0++;
            obj                     = wp->child_28;
            obj->position.x         = -0x1000;
            obj->position.y         = -0x2800;
            obj->position.z         = 0x400;
            obj->position_fixed.v.x = -0x10000000;
            obj->position_fixed.v.y = -0x28000000;
            obj->position_fixed.v.z = 0x04000000;
            wp->routine_6++;
            break;
        case 1:
            if (wp->frame_10 == 80)
            {
                wp->reserved09[1] |= 0x80;
                func_80017C30(0xE);
                wp->routine_5 = 2;
                wp->routine_6++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(4, 0x80);
                wp->child_28 = NULL;
                wp->routine_6++;
            }
            break;
        case 3:
            if (wp->frame_10 >= 180)
            {
                wp->routine_6++;
            }
            break;
        case 4:
            Cd_read_comb(0xB1);
            wp->routine_6++;
            break;
        case 5:
            if (Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x20010007);
                wp->routine_6++;
            }
            break;
        case 6:
            if (func_8001D878() != 0)
            {
                wp->routine_6 = 0;
                func_80017C30(7);
                Sce_event_next();
            }
            break;
    }
}

void func_8011961C(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            func_8001EAE8(D_80122038);
            wp->routine_6++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                wp->routine_5 = 3;
                wp->reserved09[1] &= 0x7F;
            }
            break;
        case 2: // empty, but it shapes the compare chain
            break;
    }
}

void func_801196A8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child = wp->child_28;
        child->flags_0 &= 0xFD;
        func_8001EAE8(D_8012204C);
        func_80119838(D_800C3558, 0);
    }
}

void func_80119700(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8001EAE8(D_80122074);
    }
}

void func_80119738(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_8001EAE8(D_80122060);
    }
}

void func_80119770(void)
{
}

void func_80119778(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_2C);
        wp->child_2C = NULL;
        func_8003187C(wp->child_30);
        wp->child_30 = NULL;
        func_8003187C(wp->child_34);
        child                     = wp->child_28;
        wp->child_34              = NULL;
        child->position.y         = -0x100;
        child->position.x         = 0;
        child->position.z         = 0;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.y = -0x1000000;
        child->position_fixed.v.z = 0;
        child->flags_0 |= 2;
        func_80119838(D_800C3558, 3);
    }
    if (wp->frame_10 == 0xC8)
    {
        wp->reserved09[1] |= 0x80;
        func_80017C30(0xA);
    }
}

// Sets the script camera on the player.
void func_80119838(void *camera, uint8 mode)
{
    D_800C356F = mode;
    D_800C356C = -1;
    D_800C356E = 0x17;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C3560 = STAGE_PL_S16(0x438);
    D_800C3562 = STAGE_PL_S16(0x43A);
    D_800C3564 = STAGE_PL_S16(0x43C);
    D_800C356A = STAGE_PL_S16(0x442);
}

void func_801198BC(sint32 index)
{
    D_80122B88.shape_0 = D_80122B88.prev_1 = D_80122B88.index_2 = 0;
    D_80122B88.mouth_8                                          = D_801226AC[index];
}

void func_801198F4(sint32 index)
{
    D_80122B88.shape_3 = D_80122B88.prev_4 = D_80122B88.index_5 = 0;
    D_80122B88.eyes_C                                           = D_801226D0[index];
}

void func_8011992C(void)
{
    ST17_PL_FACE *pl;
    ST17_FACE2 *face;

    pl   = (ST17_PL_FACE *)&Player_work;
    face = &D_80122B88;
    if (face->mouth_8[face->index_2 + 1] != 0x7E)
    {
        if (face->mouth_8[face->index_2 + 1] == 0x7F)
        {
            face->index_2 = 0;
        }
        else
        {
            face->index_2++;
        }
    }
    face->prev_1 = face->shape_0 = face->mouth_8[face->index_2];
    if (face->eyes_C[face->index_5 + 1] != 0x7E)
    {
        if (face->eyes_C[face->index_5 + 1] == 0x7F)
        {
            face->index_5 = 0;
        }
        else
        {
            face->index_5++;
        }
    }
    face->prev_4 = face->shape_3 = face->eyes_C[face->index_5];
    pl->mouth_168                = face->shape_0;
    pl->eyes_169                 = face->shape_3;
}

void func_80119A14(uint8 value)
{
    D_800C356C = -1;
    D_800C356E = 0x17;
    D_800C356F = value;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

// Draws a translucent full-screen rectangle whose red flickers with the frame count.
void func_80119A78(void)
{
    ST17_TILE *tile;
    DR_MODE *mode;

    tile = (ST17_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    if (ST17_FRAME & 0x10)
    {
        if (ST17_FRAME & 7)
        {
            tile->r0 = 0;
        }
        else
        {
            tile->r0 = 100;
        }
    }
    else if (ST17_FRAME & 3)
    {
        tile->r0 = 0;
    }
    else
    {
        tile->r0 = 100;
    }
    tile->g0 = 100;
    tile->b0 = 100;
    tile->code |= 2;
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(mode, 0, 0, 0x4F, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
}

void func_80119BD4(void)
{
}

void func_80119BDC(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_80119A14(0);
            wp->child_24->flags_0 &= ~2;
            wp->child_24->routine_0++;
            func_8001EAE8(D_801226F0);
            Obj_work_flag_change(0x60, 0x80);
            break;
        case 1:
            func_80105530(&D_80122A04[0], 4, 1, 0x14, -3, 0);
            func_80105530(&D_80122A04[1], 5, 2, 0x14, -4, 0);
            func_80105530(&D_80122A04[2], 0xA, 3, 0x14, -6, 0);
            break;
        case 21:
        case 31:
            wp->child_28->routine_0++;
            break;
    }
    func_80119A78();
}

void func_80119D28(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_8003187C(wp->child_28);
            func_8001EAE8(D_80122704);
            Obj_work_flag_change(0x60, 0x80);
            break;
        case 1:
            func_80105530(&D_80122A1C[0], 0xA, 3, 0x14, -5, 0);
            func_80105530(&D_80122A1C[1], 5, 1, 0x14, -6, 0);
            break;
        case 2: // empty, but it shapes the compare chain
            break;
    }
    func_80119A78();
}

void func_80119DE8(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            func_8003187C(wp->child_2C);
            func_8001EAE8(D_80122718);
            Obj_work_flag_change(0x60, 0x80);
            break;
        case 1:
            func_80105530(D_80122A2C, 0xA, 3, 0x14, -5, 0);
            break;
        case 20:
            wp->child_30->routine_0++;
            break;
    }
    func_80119A78();
}

void func_80119EB8(STAGE_ROOM *wp)
{
    switch (wp->routine_6)
    {
        case 0:
            func_8003187C(wp->child_30);
            func_80119A14(3);
            wp->child_24->flags_0 |= 2;
            wp->child_24->routine_0++;
            Obj_work_flag_change(0x60, 0x80);
            wp->routine_6++;
            break;
        case 1:
            if (wp->frame_10 == 170)
            {
                D_80122B98 |= 0x80;
                func_80017C30(0xF);
                wp->routine_6++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                func_8003187C(wp->child_24);
                wp->reserved09[1] = 30;
                wp->routine_6++;
            }
            break;
        case 3:
            if (wp->reserved09[1] != 0)
            {
                wp->reserved09[1]--;
            }
            else
            {
                func_8001EAE8(&D_80122740[0]);
                func_8001EAE8(&D_80122740[1]);
                func_80017C30(7);
                wp->routine_6 = 0;
                Sce_event_next();
            }
            break;
    }
}

void func_8011A030(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_FX *fx;
    sint32 i;

    switch (wp->routine_6)
    {
        case 0:
            pl                   = &Player_work;
            STAGE_PL.routine_0   = 3;
            STAGE_PL.routine_1   = 1;
            STAGE_PL.pos_438.x   = 0xA40;
            STAGE_PL.pos_438.y   = -0x186B;
            STAGE_PL.pos_438.z   = -0xB3C;
            STAGE_PL.fixed_428.x = 0x0A400000;
            STAGE_PL.fixed_428.y = 0xE7950000;
            STAGE_PL.fixed_428.z = 0xF4C40000;
            STAGE_PL.value_442   = 0x800;
            STAGE_PL.value_440   = 0;
            STAGE_PL.value_444   = 0;
            STAGE_PL.value_448   = 0x84;
            STAGE_PL.value_76    = 1;
            STAGE_PL.value_74    = 0;
            pl->flags_0 |= 3;
            STAGE_PL.flags_bd |= 0x10;
            STAGE_PL.value_C0    = wp->child_28;
            STAGE_PL_BYTE(0x170) = 0;
            func_801198BC(0);
            func_801198F4(0);
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0 = 1;
                fx->kind_2  = 0x12;
            }
            for (i = 0; i < 9; i++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0 = 1;
                    fx->kind_2  = 0x16;
                    fx->value_C = i;
                }
            }
            wp->routine_6++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                D_80122B98 &= ~0x80;
                wp->routine_6++;
            }
            break;
        case 2:
            break;
    }
    func_8011992C();
}

void func_8011A210(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            wp->child_28->routine_0++;
            wp->child_2C->routine_0++;
            break;
        case 10:
            func_801198BC(3);
            break;
        case 30:
            wp->child_2C->routine_0++;
            break;
        case 160:
            STAGE_PL_BYTE(0x448) = 0x83;
            func_801198BC(1);
            func_801198F4(1);
            break;
        case 210:
            func_801198BC(2);
            func_801198F4(2);
            break;
    }
    func_8011992C();
}

void func_8011A2F4(void)
{
}

void func_8011A2FC(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            pl->flags_0 &= ~2;
            D_80122B9C           = STAGE_PL_BYTE(0x170);
            STAGE_PL_BYTE(0x170) = 0;
            Obj_work_flag_change(0x7E, 0x80);
            func_8001E6C0(0, 0, 0);
            D_800BC7F0  = D_80122768;
            wp->tbl_A4  = D_801227C4;
            wp->timer_C = 0;
            func_8001EAE8(D_801226DC);
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                func_80017C30(1);
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                D_80122B98 = 0;
                Cd_xa_play_id(0x20010005);
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->routine_4++;
            }
            break;
    }
    func_8001EC0C();
    Sce_event_update();
}

void func_8011A44C(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            func_8001EC0C();
            if (func_8001D878() != 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0 = D_801227D4;
                wp->tbl_A4 = D_80122A34;
                wp->routine_5++;
            }
            break;
        case 1:
            if (wp->routine_8 != 0xFF)
            {
                if (func_8001DE84() != 0 && !(D_80122B98 & 0x80))
                {
                    D_80122B98    = 1;
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
                wp->tbl_A4[1](wp);
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            func_8001EC0C();
            break;
    }
    Sce_event_update();
}

void func_8011A574(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    switch (wp->routine_5)
    {
        case 0:
            Cd_subcmd(0, 1, 0);
            wp->routine_5++;
            break;
        case 1:
            D_800C356C = 1;
            D_800C356E = 0x1B;
            D_800C356F = 8;
            D_800C3560 = 0x70;
            D_800C3562 = -1;
            D_800C3564 = 0xD8;
            D_800C356A = 0xC00;
            D_800C3571 = 0xA;
            D_800C356D = 0;
            D_800C3570 = 2;
            wp->routine_5++;
            break;
        case 2:
            if (D_800C356C_A[0] == 2)
            {
                func_8003697C();
                pl = &Player_work;
                func_80042314(pl);
                STAGE_PL_BYTE(0x168) = 0;
                STAGE_PL_BYTE(0x169) = 0;
                D_800A395C           = 1;
                pl->flags_0 |= 3;
                STAGE_PL_BYTE(0x170) = D_80122B9C;
                func_80039820();
                D_800C356C_A[0]++;
                func_8001D974();
                Sce_flag_on(0x2A);
                wp->flags_0 = 0;
            }
            break;
    }
}

void func_8011A710(STAGE_ROOM *wp)
{
    D_80122A7C[wp->routine_4](wp);
}
