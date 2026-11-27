#include "common.h"
#include "st00.h"

// Installs the stage's slot routine tables.
void func_80100324(void)
{
    STAGE_TABLE_3C0 = D_8011A4D0;
    STAGE_TABLE_5A4 = D_8011A5B0;
    STAGE_TABLE_10C = D_8011A5D4;
    STAGE_TABLE_48  = D_8011A604;
    STAGE_TABLE_24  = D_8011A644;
    STAGE_TABLE_50  = D_8011A6CC;
}

void func_8010038C(void)
{
    STAGE_PL_VIEW *pl;
    void *spawns;
    sint32 room;

    Room_model_init(D_8011A6F0[Game_work.value_51]);
    room                      = Game_work.value_51;
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[room].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[room].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[room].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[room].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    STAGE_MAP_WORK_PTR->cells = STAGE_MAP_TBL[room].cells;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    pl                        = &STAGE_PL;
    switch (room)
    {
        case 0:
            D_8009888C                = 0x80000000;
            *(uint32 *)&pl->routine_0 = 0;
            pl->be_flag &= ~(MOVE | TRANS);
            Sce_flag_on(0x604);
            break;
        case 1:
            pl->value_44E = 1;
            pl->be_flag |= MOVE | TRANS;
            break;
        case 2:
        case 3:
            pl->value_44E = 1;
            break;
        case 4:
            *(uint32 *)&pl->routine_0 = 0;
            pl->be_flag &= ~(MOVE | TRANS);
            Sce_flag_on(0x605);
            break;
    }
    spawns                    = D_8011AB3C[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8011AC40[Game_work.value_51];
    Obj_spawn_tbl_set(spawns, D_800C356D);
    func_800371A0(D_8011AD1C[D_8011ADE4[Game_work.value_51]], D_8011AC54[Game_work.value_51]);
    func_8005DC10(D_8011A0FC[Game_work.value_51]);
}

void func_80100598(void)
{
    ST00_FLAG_MUSIC *p;

    for (p = D_8011ADF8; p->flag_0 != 0xFFFF; p++)
    {
        if (Sce_flag_test(p->flag_0))
        {
            func_8001DDE4(p->id_2);
            return;
        }
    }
}

// Draws a translucent full-screen rectangle (abr: the blend mode).
void func_80100614(uint8 r, uint8 g, uint8 b, uint16 abr)
{
    ST00_TILE *tile;
    DR_MODE *mode;

    tile = (ST00_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->g0   = g;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->r0   = r;
    tile->b0   = b;
    tile->code |= 2;
    mode = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(mode, 0, 0, (abr << 5) | 0xF, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, mode);
}

void func_80100738(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_80122428                            = 1;
        D_80122434                            = 0x40;
        D_80122430                            = 0x40;
        D_8012242C                            = 0x40;
        wp->child_24->scale.v.pad             = 0x4210;
        D_80122438                            = 2;
        wp->child_30->position_fixed_prev.pad = 0x808080;
    }
    if (wp->frame_10 == 0x1A9)
    {
        wp->child_24->routine_1 = 6;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x1D1)
    {
        wp->child_30->routine_1 = 2;
        wp->child_30->routine_2 = 0;
    }
}

void func_801007F0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        D_80122428                                   = 0;
        wp->child_24->position_fixed.v.x             = 0;
        wp->child_24->rotation.y                     = 0x800;
        wp->child_24->routine_1                      = 1;
        wp->child_24->routine_2                      = 0;
        wp->child_30->routine_1                      = 0;
        wp->child_30->routine_2                      = 0;
        ((STAGE_MATRIX_OBJ *)wp->child_30)->pos_38.x = 0;
        ((STAGE_MATRIX_OBJ *)wp->child_30)->color_40 = 0x808080;
    }
}

void func_8010086C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0x1E)
    {
        wp->child_24->routine_1 = 2;
        wp->child_24->routine_2 = 0;
    }
}

void func_8010089C(void)
{
}

void func_801008A4(STAGE_ROOM *wp)
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

void func_801008D4(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        child->routine_1          = 2;
        child->position_fixed.v.y = -0x01100000;
        child->routine_2          = 0;
        child->position_fixed.v.x = 0;
        child->position_fixed.v.z = 0x0D590000;
    }
    if (wp->frame_10 == 0x14)
    {
        child->routine_2 = 0;
        child->routine_1 = 0;
    }
}

void func_80100920(STAGE_ROOM *wp)
{
    STAGE_FX *ep;

    if (wp->frame_10 == 0x1E)
    {
        wp->child_24->routine_1 = 3;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x60)
    {
        ep          = (STAGE_FX *)func_80031618();
        ep->be_flag = MOVE;
        ep->id      = 2;
        ep->work_0  = 2;
        ep->x_1C    = 0x10;
        ep->type    = 1;
        ep->y_1E    = -0x194;
        ep->timer_D = 0;
        ep->frame_E = 0;
        ep->z_20    = 0xDF0;
    }
}

void func_801009B0(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    child = wp->child_24;
    if (wp->frame_10 == 0)
    {
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x78)
    {
        D_800A2D0B = 1;
    }
    if (wp->frame_10 == 0xD2)
    {
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x136)
    {
        child->routine_1 = 7;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x172)
    {
        other            = wp->child_2C;
        other->routine_1 = 1;
    }
}

void func_80100A3C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_24;
    if (wp->frame_10 == 0x32)
    {
        child->routine_1 = 8;
        child->routine_2 = 0;
        child->position_fixed.v.y += 0x500000;
    }
}

void func_80100A70(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    child = wp->child_2C;
    if (wp->frame_10 == 0x3C)
    {
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
}

void func_80100A94(STAGE_ROOM *wp)
{
    ST00_EVENT *ev;

    if (wp->frame_10 == 0)
    {
        ev          = Open_EVE_WORK();
        ev->be_flag = MOVE;
        ev->id      = 3;
        ev->value_4 = 0;
        ev->type    = 2;
        ev->value_5 = 0;
        ev          = Open_EVE_WORK();
        ev->be_flag = MOVE;
        ev->id      = 3;
        ev->value_4 = 0;
        ev->type    = 3;
        ev->value_5 = 0;
        ev          = Open_EVE_WORK();
        ev->be_flag = MOVE;
        ev->id      = 4;
        ev->value_4 = 0;
        ev->type    = 0;
        ev->value_5 = 0;
    }
    if (wp->frame_10 == 0x1A)
    {
        wp->child_44->routine_1 = 1;
        wp->child_44->routine_2 = 0;
    }
    if (wp->frame_10 == 0x21)
    {
        wp->child_48->routine_1 = 1;
        wp->child_48->routine_2 = 0;
    }
    if (wp->frame_10 == 0x28)
    {
        wp->child_40->routine_1 = 1;
        wp->child_40->routine_2 = 0;
    }
    if (wp->frame_10 == 0x31)
    {
        wp->child_24->routine_1 = 9;
        wp->child_24->routine_2 = 0;
        D_80122424              = 1;
    }
}

void func_80100BE8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_OBJ *other;

    if (wp->frame_10 == 0)
    {
        child = wp->child_2C;
        child->be_flag &= 0xFD;
        child            = wp->child_24;
        child->routine_1 = 0xA;
        other            = wp->child_24;
        other->routine_2 = 0;
    }
}

void func_80100C30(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_v0;

    if (wp->frame_10 == 0)
    {
        temp_v0                     = wp->child_24;
        temp_v0->routine_1          = 0xB;
        temp_v0->routine_2          = 0;
        temp_v0->position_fixed.v.x = 0;
        temp_v0->position_fixed.v.y = 0;
        temp_v0->rotation.y         = 0;
    }
    if (wp->frame_10 == 1)
    {
        wp->child_34->routine_1 = 1;
        wp->child_34->routine_2 = 0;
    }
    if (wp->frame_10 == 0xD)
    {
        wp->child_38->routine_1 = 1;
        wp->child_38->routine_2 = 0;
    }
    if (wp->frame_10 == 0x19)
    {
        wp->child_3C->routine_1 = 1;
        wp->child_3C->routine_2 = 0;
    }
    if (wp->frame_10 == 0x44)
    {
        wp->child_30->routine_1 = 3;
        wp->child_30->routine_2 = 0;
    }
}

void func_80100D04(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_30->routine_1 = 3;
        wp->child_30->routine_2 = 0;
    }
}

void func_80100D34(STAGE_ROOM *wp)
{
    STAGE_OBJ *temp_a0;

    if (wp->frame_10 == 0)
    {
        temp_a0            = wp->child_24;
        temp_a0->routine_1 = 0xC;
        temp_a0->routine_2 = 0;
        temp_a0->position_fixed.v.z += 0xC80000;
    }
}

void func_80100D6C(STAGE_ROOM *wp)
{
    STAGE_OBJ *obj;
    STAGE_FX *ep;

    if (wp->frame_10 == 6)
    {
        D_80122424 = 0;
    }
    if (wp->frame_10 < 0x1F)
    {
        obj = wp->child_24;
        ep  = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->be_flag = MOVE;
            ep->id      = 0x83;
            ep->type    = 0;
            ep->x_1C    = obj->position.x + (rand() & 0x3F) - 0x1F;
            ep->y_1E    = obj->position.y + (rand() & 0x1F) - 0xF;
            ep->z_20    = obj->position.z + (rand() & 0x3F) - 0x1F;
        }
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->be_flag = MOVE;
            ep->id      = 0x83;
            ep->type    = 0;
            ep->x_1C    = obj->position.x + (rand() & 0x3F) - 0x1F;
            ep->y_1E    = obj->position.y + (rand() & 0x1F) - 0xF;
            ep->z_20    = obj->position.z + (rand() & 0x3F) - 0x1F;
        }
    }
}

void func_80100E9C(STAGE_ROOM *wp)
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

void func_80100ECC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 0xB;
        wp->child_24->routine_2 = 0;
    }
}

void func_80100EFC(ST00_ROOM_FX *wp)
{
    STAGE_OBJ *obj;
    sint32 i;
    STAGE_FX *ep;

    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_8011AF4C;
    for (i = 0; i < 16; i++)
    {
        obj = Scene_obj_ent_open(&D_8011AE0C[i]);
        if (i != 0)
        {
            Model_work_init(obj, &D_8011B377[i]);
            obj->position_fixed_prev.pad = 0x808080;
        }
    }
    wp->child_28->position_fixed_prev.pad = 0x808080;
    wp->child_60->position_fixed_prev.pad = 0x02808080;
    wp->child_30->position_fixed_prev.pad = 0;
    ep                                    = (STAGE_FX *)func_80031618();
    ep->be_flag                           = MOVE;
    ep->id                                = 2;
    ep->work_0                            = 2;
    ep->y_1E                              = -0x194;
    ep->type                              = 0;
    ep->timer_D                           = 0;
    ep->frame_E                           = 0;
    ep->x_1C                              = 0;
    ep->z_20                              = 0xE00;
    wp->fx_64                             = ep;
    D_80122428                            = 0;
    wp->tbl_A4                            = D_8011B2E8;
}

void func_8010102C(STAGE_ROOM_WORK *wp)
{
    if (D_80122424 == 1)
    {
        if (STAGE_FRAME & 2)
        {
            D_800BC744[0] += 0x20000;
        }
        else
        {
            D_800BC744[0] -= 0x20000;
        }
    }
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

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
                Player_work.be_flag &= ~(MOVE | TRANS);
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
                Player_work.be_flag |= MOVE;
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
        wp->child_2C->u_C.b.work_0 = wp->child_30->u_C.b.work_0 = 1;
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
        wp->child_2C->u_C.b.work_0 = wp->child_30->u_C.b.work_0 = 2;
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
        child->be_flag |= TRANS;
        wp->child_24->routine_1 = 3;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x82)
    {
        wp->child_2C->u_C.b.work_0 = wp->child_30->u_C.b.work_0 = 1;
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
            fx->be_flag = MOVE;
            fx->id      = 5;
            fx->work_0  = 5;
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
        child->be_flag |= TRANS;
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
                Player_work.be_flag &= ~(MOVE | TRANS);
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
            ep->be_flag = MOVE;
            ep->id      = 5;
            ep->work_0  = 5;
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

    Player_work.be_flag &= ~(MOVE | TRANS);
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
                pl->be_flag |= MOVE;
                func_80042314(pl);
            }
            break;
    }
}
