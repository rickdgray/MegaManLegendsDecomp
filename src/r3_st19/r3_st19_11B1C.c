#include "common.h"
#include "st19.h"

#ifdef __wasm32__
void func_8001E3F0(sint32 arg);
#endif

void func_80111B1C(sint32 index, uint8 arg1)
{
    STCOM_SVECTOR pos[3] = {{0, 0, 0, 0}, {-340, 0, 200, 0x800}, {-3200, 0, -2200, 0x800}};

    ST19_CAM_REQ_PTR->mode_C   = -1;
    ST19_CAM_REQ_PTR->value_E  = 0x19;
    ST19_CAM_REQ_PTR->value_F  = arg1;
    ST19_CAM_REQ_PTR->value_D  = 0;
    ST19_CAM_REQ_PTR->value_11 = 0xFF;
    ST19_CAM_REQ_PTR->value_10 = 0xFF;
    ST19_CAM_REQ_PTR->x_0      = pos[index].x;
    ST19_CAM_REQ_PTR->y_2      = pos[index].y;
    ST19_CAM_REQ_PTR->z_4      = pos[index].z;
    ST19_CAM_REQ_PTR->angle_A  = pos[index].pad;
}

void func_80111C08(sint32 index)
{
    D_8011F4B8.shape_0 = D_8011F4B8.prev_1 = D_8011F4B8.index_2 = 0;
    D_8011F4B8.mouth_8                                          = D_80118FCC[index];
    D_8011F4B8.shape_3 = D_8011F4B8.prev_4 = D_8011F4B8.index_5 = 0;
    D_8011F4B8.eyes_C                                           = D_80119034[index];
}

// Steps the stage face's mouth and eye scripts and shows the shapes on the player.
void func_80111C6C(STAGE_PL_VIEW *pl)
{
    STAGE_FACE8 *face;

    face = &D_8011F4B8;
    switch (face->mouth_8[face->index_2 + 1])
    {
        case 0x7E:
            break;
        case 0x7F:
            face->index_2 = 0;
            break;
        default:
            face->index_2++;
            break;
    }
    face->prev_1 = face->shape_0 = face->mouth_8[face->index_2];
    switch (face->eyes_C[face->index_5 + 1])
    {
        case 0x7E:
            break;
        case 0x7F:
            face->index_5 = 0;
            break;
        default:
            face->index_5++;
            break;
    }
    face->prev_4 = face->shape_3 = face->eyes_C[face->index_5];
    pl->value_168                = face->shape_0;
    pl->value_169                = face->shape_3;
}

// Spawns object kind 0x41.
void func_80111D50(void)
{
    STAGE_OBJ *wp;

    wp = func_80031418();
    if (wp != NULL)
    {
        wp->flags_0            = 1;
        wp->kind_2             = 0x41;
        wp->position.x         = -1000;
        wp->position.y         = -1;
        wp->position.z         = -0x99C;
        wp->rotation.y         = 0x400;
        wp->value_4            = 0;
        wp->variant_3          = 0;
        wp->u_C.b.byte_C       = 0;
        wp->u_C.b.byte_D       = 0;
        wp->u_E.b.byte_E       = 0;
        wp->u_E.b.byte_F       = 0;
        wp->position_fixed.v.x = wp->position.x << 16;
        wp->position_fixed.v.y = wp->position.y << 16;
        wp->position_fixed.v.z = wp->position.z << 16;
    }
}

// Spawns the two kind 0x1F effects (variant `variant`).
void func_80111DE4(sint32 variant)
{
    STAGE_FX *fx;
    sint32 i;

    for (i = 0; i < 2; i++)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            D_8011F4A8[i] = fx;
            fx->flags_0   = 1;
            fx->kind_2    = 0x1F;
            fx->variant_3 = variant;
            fx->value_C   = i;
            fx->timer_D   = 0;
            fx->frame_E   = 0;
            fx->type_F    = 1;
            fx->routine_1 = i;
            fx->routine_2 = 0;
        }
    }
}

void func_80111E84(sint32 index)
{
    D_8011F4C8.index_E = 0;
    D_8011F4C8.shape_C = 0;
    D_8011F4C8.prev_D  = -1;
    D_8011F4C8.mouth_4 = D_801196B0[index];
}

void func_80111EC0(sint32 index)
{
    D_8011F4C8.index_11 = 0;
    D_8011F4C8.shape_F  = 0;
    D_8011F4C8.prev_10  = -1;
    D_8011F4C8.eyes_8   = D_801197A8[index];
}

// Steps the stage face's mouth and eye scripts and shows the shapes on the player.
void func_80111EFC(void)
{
    STAGE_PL_VIEW *pl;
    STAGE_FACE *face;

    pl   = &STAGE_PL;
    face = &D_8011F4C8;
    switch (face->mouth_4[face->index_E + 1])
    {
        case 0x7E:
            break;
        case 0x7F:
            face->index_E = 0;
            break;
        default:
            face->index_E++;
            break;
    }
    face->prev_D = face->shape_C = face->mouth_4[face->index_E];
    switch (face->eyes_8[face->index_11 + 1])
    {
        case 0x7E:
            break;
        case 0x7F:
            face->index_11 = 0;
            break;
        default:
            face->index_11++;
            break;
    }
    face->prev_10 = face->shape_F = face->eyes_8[face->index_11];
    pl->value_168                 = face->shape_C;
    pl->value_169                 = face->shape_F;
}

void func_80111FE4(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356E = 7;
    D_800C356F = arg0;
    D_800C3564 = 0;
    D_800C3562 = 0;
    D_800C3560 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80112048(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0;
        child->flags_0 |= 2;
        child            = wp->child_2C;
        child->routine_1 = 0;
        child->flags_0 |= 2;
        child            = wp->child_30;
        child->routine_1 = 0;
        child->flags_0 |= 2;
    }
    if (wp->frame_10 == 0x28)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x32)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x46)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x50)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x5A)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x64)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x6E)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x78)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x82)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x8C)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x96)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xA0)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xB4)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xC8)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xD2)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xDC)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xE6)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xF0)
    {
        child            = wp->child_2C;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xFA)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
}

void func_80112328(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *child;

    pl = &STAGE_PL;
    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child            = wp->child_2C;
        child->flags_0 &= ~2;
        child = wp->child_30;
        child->flags_0 &= ~2;
        STAGE_PL.fixed_428.x = 0x104 << 16;
        func_80030150(&pl->fixed_428, &pl->pos_438);
    }
    if (wp->frame_10 == 10)
    {
        child            = wp->child_28;
        child->routine_1 = 1;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x1E)
    {
        child            = wp->child_28;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
}

void func_801123F8(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0)
    {
        func_80111E84(0);
        func_80111EC0(0);
    }
    if (wp->value_10 == 0x1E)
    {
        func_80111E84(0);
        func_80111EC0(0);
    }
    func_80111EFC();
}

void func_80112464(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_OBJ *child;

    pl = &STAGE_PL;
    if (wp->frame_10 == 0)
    {
        child              = wp->child_28;
        child->routine_1   = 3;
        child->routine_2   = 0;
        STAGE_PL.value_448 = 0x81;
    }
    if (wp->frame_10 < 12)
    {
        STAGE_PL.fixed_428.x += -3 << 16;
        func_80030150(&pl->fixed_428, &pl->pos_438);
    }
    if (wp->frame_10 == 12)
    {
        func_80111E84(1);
        STAGE_PL.value_448 = 0x82;
    }
    func_80111EFC();
}

void func_8011251C(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
}

void func_80112544(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 10)
    {
        func_80111E84(2);
    }
    if (wp->frame_10 == 25)
    {
        func_80111EC0(2);
        STAGE_PL.value_448 = 0x83;
    }
    func_80111EFC();
}

void func_801125AC(STAGE_ROOM *wp)
{
    ST19_OBJ *child;

    if (wp->frame_10 == 10)
    {
        func_80111E84(1);
        func_80111EC0(0);
    }
    if (wp->frame_10 == 0x19)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xAA)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 2;
    }
    if (wp->frame_10 == 0xB6)
    {
        child                      = (ST19_OBJ *)wp->child_28;
        child->part_100[3].value_0 = 0x14;
        child->part_100[6].value_0 = 0x15;
    }
    if (wp->frame_10 == 0xDC)
    {
        child                      = (ST19_OBJ *)wp->child_28;
        child->part_100[3].value_0 = 5;
        child->part_100[6].value_0 = 8;
    }
    if (wp->frame_10 == 0x15E)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 3;
    }
    if (wp->frame_10 == 0x1B8)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 8;
        child->routine_2 = 4;
    }
    func_80111EFC();
}

void func_801126CC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 2;
        child->routine_2 = 0;
        child->flags_0 |= 2;
        child            = wp->child_28;
        child->routine_1 = 0xA;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 5)
    {
        child            = wp->child_28;
        child->routine_2 = 2;
        child            = wp->child_2C;
        child->routine_2 = 2;
    }
}

void func_80112738(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0xB;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xA)
    {
        child            = wp->child_28;
        child->routine_2 = 2;
    }
}

void func_8011277C(STAGE_ROOM *wp)
{
    ST19_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 0xC;
        child->routine_2 = 0;
        child            = (ST19_OBJ *)wp->child_2C;
        child->routine_1 = 3;
        child->routine_2 = 0;
        child            = (ST19_OBJ *)wp->child_30;
        child->routine_1 = 1;
        child->routine_2 = 0;
        child->flags_0 |= 2;
    }
    if (wp->frame_10 == 8)
    {
        child                      = (ST19_OBJ *)wp->child_28;
        child->part_100[3].value_0 = 0x14;
        child->part_100[6].value_0 = 0x15;
    }
    if (wp->frame_10 == 0x50)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 0xD;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x55)
    {
        child            = (ST19_OBJ *)wp->child_2C;
        child->routine_1 = 4;
        child->routine_2 = 0;
        child            = (ST19_OBJ *)wp->child_30;
        child->routine_2 = 2;
    }
    if (wp->frame_10 == 0x58)
    {
        child                      = (ST19_OBJ *)wp->child_28;
        child->part_100[3].value_0 = 5;
        child->part_100[6].value_0 = 8;
    }
    if (wp->frame_10 == 0x62)
    {
        child            = (ST19_OBJ *)wp->child_2C;
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x6D)
    {
        child            = (ST19_OBJ *)wp->child_28;
        child->routine_1 = 0xE;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x82)
    {
        child            = (ST19_OBJ *)wp->child_2C;
        child->routine_1 = 6;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x98)
    {
        child            = (ST19_OBJ *)wp->child_30;
        child->routine_1 = 2;
        child->routine_2 = 0;
    }
}

void func_801128E8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        STAGE_PL.value_448 = 0x80;
    }
    if (wp->frame_10 == 1)
    {
        func_80111E84(3);
        func_80111EC0(0);
    }
    if (wp->frame_10 == 10)
    {
        func_80111E84(4);
    }
    if (wp->frame_10 == 0x28)
    {
        func_80111EC0(4);
        STAGE_PL.value_448 = 0x84;
    }
    if (wp->frame_10 == 0x190)
    {
        child            = wp->child_28;
        child->routine_1 = 0xF;
        child->routine_2 = 0;
        child            = wp->child_2C;
        child->routine_1 = 7;
        child->routine_2 = 0;
        child            = wp->child_30;
        child->routine_1 = 3;
        child->routine_2 = 0;
    }
    func_80111EFC();
}

void func_801129C8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0xF;
        child->routine_2 = 0;
        child            = wp->child_2C;
        child->routine_1 = 7;
        child->routine_2 = 0;
        child            = wp->child_30;
        child->routine_1 = 3;
        child->routine_2 = 0;
    }
}

void func_80112A10(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 8;
        child->routine_2 = 0;
    }
}

void func_80112A38(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0x10;
        child->routine_2 = 0;
    }
}

void func_80112A60(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 9;
        child->routine_2 = 0;
    }
}

void func_80112A88(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0x11;
        child->routine_2 = 0;
        child            = wp->child_30;
        child->routine_1 = 4;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0x6E)
    {
        child            = wp->child_30;
        child->routine_2 = 2;
    }
}

void func_80112ADC(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_2C;
        child->routine_1 = 0xA;
        child->routine_2 = 0;
    }
}

void func_80112B04(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child            = wp->child_28;
        child->routine_1 = 0x12;
        child->routine_2 = 0;
        child            = wp->child_2C;
        child->routine_1 = 0xB;
        child->routine_2 = 0;
        child            = wp->child_30;
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
    if (wp->frame_10 == 0xA0)
    {
        child            = wp->child_28;
        child->routine_2 = 1;
        child            = wp->child_2C;
        child->routine_2 = 3;
    }
    if (wp->frame_10 == 0xB9)
    {
        child            = wp->child_28;
        child->routine_2 = 2;
        child            = wp->child_2C;
        child->routine_2 = 1;
    }
    if (wp->frame_10 == 0xC8)
    {
        child            = wp->child_30;
        child->routine_2 = 2;
    }
    if (wp->frame_10 == 0xE6)
    {
        child            = wp->child_30;
        child->routine_1 = 5;
        child->routine_2 = 0;
    }
}

void func_80112BD8(STAGE_ROOM *wp)
{
    STAGE_FX *fx;
    sint32 i;

    D_800BC7F0 = D_801190D8;
    wp->tbl_A4 = D_801197C0;
    for (i = 0; i < 9; i++)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0   = 1;
            fx->kind_2    = 0x1B;
            fx->variant_3 = 0;
            fx->value_C   = i;
        }
    }
    for (i = 0; i < 12; i++)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0   = 1;
            fx->kind_2    = 0x1B;
            fx->variant_3 = 1;
            fx->value_C   = i;
        }
    }
    for (i = 0; i < 3; i++)
    {
        func_8001EAE8(&D_8011909C[i]);
    }
}

void func_80112CC0(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80112D00(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            if (D_80098788 == 0 && func_80042238(&Player_work) != 0)
            {
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->fixed_428.x = 0x230 << 16;
                pl->fixed_428.y = -1 << 16;
                pl->fixed_428.z = 0x17C << 16;
                pl->flags_bd |= 0x10;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->value_442 = 0x400;
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->value_448 = 0x30;
                D_8011F4DC    = pl->value_170;
                D_8011F4E0    = pl->value_171;
                pl->value_171 = 0;
                pl->value_170 = 0;
                func_8001E3F0(0xF);
                func_8001E6C0(0, 0, 0);
                Obj_work_flag_change(0x56, 0x80);
                MojiTaskKill();
                wp->routine_4++;
            }
            break;
        case 1:
            func_8001F580(0xB6, 1, 1);
            wp->routine_4++;
            break;
        case 2:
            if (Cd_read_sync2() == 0)
            {
                func_8001D58C(0x20010014);
                wp->routine_4++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 5;
                wp->routine_4++;
            }
            break;
        case 4:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 5:
            func_80017C30(5);
            pl->flags_0 |= 2;
            wp->routine_4++;
            // fall through
        case 6:
            func_80112BD8(wp);
            wp->routine_4++;
            // fall through
        case 7:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(0xB);
                wp->routine_4 = 10;
            }
            // fall through
        case 10:
            func_80112CC0(wp);
            func_8001EC0C();
            func_8001F070();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                D_800C356C      = 2;
                D_800C356E      = 0x19;
                D_800C356F      = 3;
                D_800C3560      = 0;
                D_800C3562      = 0;
                D_800C3564      = 0;
                D_800C356A      = 0;
                D_800C356D      = 0;
                D_800C3571      = 0xFF;
                D_800C3570      = 2;
                wp->flags_0     = 0;
                pl->fixed_428.x = 0x104 << 16;
                pl->fixed_428.y = -1 << 16;
                pl->fixed_428.z = 0x17C << 16;
                pl->value_170   = D_8011F4DC;
                pl->value_171   = D_8011F4E0;
                func_80030150(&pl->fixed_428, &pl->pos_438);
                pl->value_440 = 0;
                pl->value_444 = 0;
                pl->value_442 = 0;
                Obj_work_flag_change(0x56, 0x80);
                func_8001D494(0, 1, 0);
                func_80042314(&Player_work);
            }
            break;
    }
}

void func_80113048(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    D_80119858[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_80033A28(wp);
        func_8003346C(wp);
    }
    func_80113A2C(wp, face);
}

void func_80113134(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        wp->rotation.x     = 0;
        wp->rotation.y     = 0;
        wp->rotation.z     = 0;
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->flags_0 |= 2;
        func_8002F9C4(wp, &wp->variant_3);
        func_800322A8(wp, 2, 0);
        func_801139E4(wp, face, 0);
        wp->u_C.b.byte_D = 0;
        wp->u_E.b.byte_E++;
        wp->routine_1++;
        wp->routine_2++;
    }
}

void func_801131F0(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x5A:
            func_801139E4(wp, face, 1);
            wp->u_E.b.byte_E = 0;
            break;
        case 0x9B:
            func_800322A8(wp, 3, 0);
            break;
    }
    if (wp->u_E.b.byte_E != 0)
    {
        wp->position.z -= 3;
    }
}

void func_8011327C(ST19_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 4, 0);
        func_801139E4(wp, face, 4);
        wp->part_100[2].value_0 = 0x13;
        wp->position.x          = -100;
        wp->position.z          = 100;
        wp->rotation.y          = 0x400;
        wp->u_C.b.byte_D        = 0;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 10)
    {
        func_801139E4(wp, face, 8);
    }
    if (STAGE_SCENE_WORD(0x10) == 0x16)
    {
        func_801139E4(wp, face, 7);
    }
}

void func_80113350(ST19_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 5, 0);
        wp->part_100[2].value_0 = 4;
        func_801139E4(wp, face, 7);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 10)
    {
        func_801139E4(wp, face, 8);
    }
}

void func_801133E0(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 5:
        case 0x28:
            func_801139E4(wp, face, 0xB);
            break;
        case 0x14:
            func_801139E4(wp, face, 0xC);
            break;
        case 0x5A:
            func_801139E4(wp, face, 0xD);
            break;
        case 0x69:
            func_801139E4(wp, face, 0xE);
            break;
    }
}

void func_80113460(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 6, 0);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 10:
        case 0x1E:
            func_801139E4(wp, face, 0xF);
            break;
    }
}

void func_801134E4(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 1:
        case 0x1E:
        case 0x32:
        case 0x50:
            func_801139E4(wp, face, 0x11);
            break;
    }
}

void func_80113548(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 7, 0);
        func_801139E4(wp, face, 0x12);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    if (STAGE_SCENE_WORD(0x10) == 5)
    {
        func_801139E4(wp, face, 0x13);
    }
    if (STAGE_SCENE_WORD(0x10) == 0x3C)
    {
        func_801139E4(wp, face, 0x12);
    }
}

void func_801135FC(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 8, 0);
        func_801139E4(wp, face, 0x14);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x1E:
            func_801139E4(wp, face, 0x15);
            break;
        case 0x87:
            func_801139E4(wp, face, 0x16);
            break;
        case 0x8C:
        case 0x96:
            func_801139E4(wp, face, 0x17);
            break;
    }
}

void func_801136DC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.z   = 0x12C;
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
}

void func_80113708(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 9, 0);
        func_801139E4(wp, face, 0x18);
        wp->position.z   = 100;
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 10:
        case 0x69:
            func_801139E4(wp, face, 0x19);
            break;
        case 0x50:
            func_801139E4(wp, face, 0x1A);
            break;
        case 0xAA:
            func_801139E4(wp, face, 0x18);
            break;
    }
}

void func_801137F0(STAGE_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->u_4E0.face;
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 10:
            func_800322A8(wp, 10, 0);
            func_801139E4(wp, face, 0x19);
            break;
        case 0x69:
            func_801139E4(wp, face, 0x18);
            break;
    }
}

void func_80113874(ST19_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->face;
    switch (STAGE_SCENE_WORD(0x10))
    {
        case 0x9B:
            func_800322A8(wp, 0xB, 0);
            wp->part_100[5].value_0 = 0x14;
            func_801139E4(wp, face, 0x1B);
            wp->u_C.b.byte_D = 0;
            break;
        case 0xAA:
            func_801139E4(wp, face, 0x1C);
            break;
        case 0xC8:
            func_801139E4(wp, face, 0x1D);
            break;
    }
}

void func_80113930(ST19_OBJ *wp)
{
    STAGE_FACE16 *face;

    face = (STAGE_FACE16 *)&wp->face;
    if (wp->routine_2 == 0)
    {
        wp->position.x = 0x3C;
        wp->position.y = 0;
        wp->position.z = 0x96;
        wp->rotation.y = 0;
        func_800322A8(wp, 1, 0);
        wp->part_100[5].value_0 = 7;
        func_801139E4(wp, face, 0x1F);
        wp->u_C.b.byte_D = 0;
        wp->u_E.b.byte_E++;
        wp->routine_2++;
    }
    if (wp->u_E.b.byte_E != 0)
    {
        wp->position.z -= 8;
    }
}

void func_801139E4(void *wp, STAGE_FACE16 *face, sint32 index)
{
    face->shape_0 = face->index_4 = 0;
    face->shape_6 = face->index_A = 0;
    face->prev_2 = face->prev_8 = -1;
    face->mouth_C               = D_80119AE0[index];
    face->eyes_10               = D_80119B60[index];
}

void func_80113A2C(STAGE_OBJ *wp, STAGE_FACE16 *face)
{
    if (face->mouth_C[face->index_4 + 1] != 0x3FFF)
    {
        if (face->mouth_C[face->index_4 + 1] == 0x7FFF)
        {
            face->index_4 = 0;
        }
        else
        {
            face->index_4++;
        }
    }
    face->shape_0 = face->mouth_C[face->index_4];
    if (face->shape_0 != face->prev_2)
    {
        func_8002D320(wp->model_88, 0x10000F, func_8002D404(face->shape_0, 0x33, 0x37, 5));
    }
    face->prev_2 = face->shape_0;
    if (face->eyes_10[face->index_A + 1] != 0x3FFF)
    {
        if (face->eyes_10[face->index_A + 1] == 0x7FFF)
        {
            face->index_A = 0;
        }
        else
        {
            face->index_A++;
        }
    }
    face->shape_6 = face->eyes_10[face->index_A];
    if (face->shape_6 != face->prev_8)
    {
        func_8002D320(wp->model_88, 0x120011, func_8002D404(face->shape_6, 0x33, 0x37, 5));
    }
    face->prev_8 = face->shape_6;
}

void func_80113B78(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->rotation.y = -0x600;
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80033A28(wp);
    func_8003346C(wp);
}

void func_80113BDC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
    func_80032488(wp);
}

void func_80113C30(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x5A;
            wp->position.y = -0x23;
            wp->position.z = 0x154;
            wp->rotation.y = -0x1C0;
            func_800322A8(wp, 2, 0);
            wp->routine_2++;
        case 1:
            func_80033A28(wp);
            func_8003346C(wp);
            return;
        case 2:
            func_80032488(wp);
            return;
    }
}

void func_80113CEC(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x1E;
            wp->position.y = -1;
            wp->position.z = 0x122;
            wp->rotation.y = -0x200;
            func_800322A8(wp, 3, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_80113D78(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x1E;
            wp->position.y = -1;
            wp->position.z = 0x122;
            wp->rotation.y = -0x3C0;
            func_800322A8(wp, 4, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_80113E04(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x1E;
            wp->position.y = -1;
            wp->position.z = 0x122;
            wp->rotation.y = 0x400;
            func_800322A8(wp, 5, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_80113E90(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x1E;
            wp->position.y = -1;
            wp->position.z = 0x122;
            func_800322A8(wp, 6, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            wp->position.x -= 2;
            return;
    }
}

void func_80113F24(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0x4B0;
            func_80032488(wp);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            wp->position.x--;
            return;
    }
}

void func_80113FA0(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            func_800322A8(wp, 7, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_8011400C(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            func_800322A8(wp, 8, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_80114078(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            func_800322A8(wp, 9, 0);
            wp->routine_2++;
        case 1:
            func_80032488(wp);
            return;
    }
}

void func_801140E4(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            wp->position.x = -0xA5A;
            wp->rotation.y = 0x4FC;
            wp->position.z = 0x15E;
            func_800322A8(wp, 0xAU, 0);
            wp->routine_2 = 2;
            return;
        case 1:
            func_800322A8(wp, 0xBU, 0);
            wp->routine_2 = 3;
            return;
        case 2:
            func_80033A28(wp);
            func_8003346C(wp);
            return;
        case 3:
            func_80032488(wp);
            return;
    }
}

void func_801141B8(STAGE_OBJ *wp)
{
    D_80119D20[wp->routine_1](wp);
}
