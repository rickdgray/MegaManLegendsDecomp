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
            pl->flags_0 &= ~3;
            Sce_flag_on(0x604);
            break;
        case 1:
            pl->value_44E = 1;
            pl->flags_0 |= 3;
            break;
        case 2:
        case 3:
            pl->value_44E = 1;
            break;
        case 4:
            *(uint32 *)&pl->routine_0 = 0;
            pl->flags_0 &= ~3;
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
        ep            = (STAGE_FX *)func_80031618();
        ep->flags_0   = 1;
        ep->kind_2    = 2;
        ep->value_C   = 2;
        ep->x_1C      = 0x10;
        ep->variant_3 = 1;
        ep->y_1E      = -0x194;
        ep->timer_D   = 0;
        ep->frame_E   = 0;
        ep->z_20      = 0xDF0;
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
        ev            = Open_EVE_WORK();
        ev->flags_0   = 1;
        ev->kind_2    = 3;
        ev->value_4   = 0;
        ev->variant_3 = 2;
        ev->value_5   = 0;
        ev            = Open_EVE_WORK();
        ev->flags_0   = 1;
        ev->kind_2    = 3;
        ev->value_4   = 0;
        ev->variant_3 = 3;
        ev->value_5   = 0;
        ev            = Open_EVE_WORK();
        ev->flags_0   = 1;
        ev->kind_2    = 4;
        ev->value_4   = 0;
        ev->variant_3 = 0;
        ev->value_5   = 0;
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
        child->flags_0 &= 0xFD;
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
            ep->flags_0   = 1;
            ep->kind_2    = 0x83;
            ep->variant_3 = 0;
            ep->x_1C      = obj->position.x + (rand() & 0x3F) - 0x1F;
            ep->y_1E      = obj->position.y + (rand() & 0x1F) - 0xF;
            ep->z_20      = obj->position.z + (rand() & 0x3F) - 0x1F;
        }
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->kind_2    = 0x83;
            ep->variant_3 = 0;
            ep->x_1C      = obj->position.x + (rand() & 0x3F) - 0x1F;
            ep->y_1E      = obj->position.y + (rand() & 0x1F) - 0xF;
            ep->z_20      = obj->position.z + (rand() & 0x3F) - 0x1F;
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
    ep->flags_0                           = 1;
    ep->kind_2                            = 2;
    ep->value_C                           = 2;
    ep->y_1E                              = -0x194;
    ep->variant_3                         = 0;
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
