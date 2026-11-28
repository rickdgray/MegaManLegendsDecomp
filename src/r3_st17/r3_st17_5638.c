#include "common.h"
#include "st17.h"

void func_80105638(STAGE_FX *wp)
{
    STCOM_SVECTOR v;
    ST17_PUFF *puff;
    STCOM23_PACKET *p;
    uint32 shade;
    sint32 u;
    sint32 i;

    switch (wp->routine_0)
    {
        case 0:
            wp->u_28.count = 0;
            wp->routine_0++;
            // fall through
        case 1:
            wp->u_28.count++;
            for (i = 0; i < 32; i++)
            {
                puff  = &D_8011B0B8[i];
                v.x   = (uint32)(puff->pos_0.x + puff->step_8.x * wp->u_28.count) >> 4;
                v.y   = ((uint32)(puff->pos_0.y + puff->step_8.y * wp->u_28.count) >> 4) - 0x1B1C;
                v.z   = (uint32)(puff->pos_0.z + puff->step_8.z * wp->u_28.count) >> 4;
                v.pad = (uint32)(puff->pos_0.pad + puff->step_8.pad * wp->u_28.count) >> 4;
                shade = (uint32)(puff->shade_10 + puff->fade_12 * wp->u_28.count) >> 4;
                if (shade < 0x80)
                {
                    p          = Billboard_get();
                    p->code_4  = 0x2E808080 - shade * 0x10101;
                    p->xy_8    = (uint16)v.x | (v.y << 16);
                    p->z_10    = v.z;
                    u          = ((puff->tile_14 << 5) + 0x20) & 0xFF;
                    p->pad_20  = 0;
                    p->uv_C    = u | 0x3D480000;
                    p->uv_14   = (u + 0x1F) | 0x4E0000;
                    p->uv_1C   = u | 0x1F00;
                    p->uv_24   = (u + 0x1F) | 0x1F00;
                    p->size_18 = v.pad;
                }
            }
            break;
    }
}

void func_80105830(ST17_PIECE *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;
    ST17_PIECE_DATA *data;
    uint16 frame;
    sint16 size;

    data = &D_8011B3B8[wp->index_C];
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 6;
            wp->variant_3 = data->variant_20;
            Model_work_init(wp, &wp->variant_3);
            wp->color_40 = 0x808080;
            wp->frame_E  = 0;
            wp->value_D  = 0;
            wp->routine_0++;
            // fall through
        case 1:
            frame        = ++wp->frame_E;
            wp->pos_38.x = (data->pos_0.x + data->step_8.x * frame) >> 4;
            wp->pos_38.y = ((data->pos_0.y + data->step_8.y * frame) >> 4) - 0x1B1C;
            wp->pos_38.z = (data->pos_0.z + data->step_8.z * frame) >> 4;
            rot.x        = data->rot_10.x + ((data->spin_18.x * frame) << 7);
            rot.y        = data->rot_10.y + ((data->spin_18.y * frame) << 7);
            rot.z        = data->rot_10.z + ((data->spin_18.z * frame) << 7);
            RotMatrixYXZ(&rot, &wp->matrix.m);
            size = (data->pos_0.pad + data->step_8.pad * frame) >> 4;
            if (size < 0)
            {
                size = 0;
            }
            scale.x = size;
            scale.y = size;
            scale.z = size;
            ScaleMatrix(&wp->matrix.m, &scale);
            break;
    }
}

void *func_80105A0C(STAGE_OBJ *wp, sint8 kind, STCOM_SVECTOR *rot)
{
    ST17_MODEL_SLOT *slot;
    ST17_MODEL_REC *model;
    ST17_JOINT_KEY *key;
    uint8 i;
    uint8 j;

    slot = func_80031498();
    if (slot == NULL)
    {
        return NULL;
    }
    slot->flags_0   = 1;
    slot->kind_2    = 3;
    slot->value_4   = 0;
    slot->variant_3 = kind;
    slot->value_C   = 0;
    slot->value_10  = 0;
    slot->flags_6 |= 0x20;
    model = &slot->model_88;
    switch (kind)
    {
        case 0:
            model->color_14 = 0x2E404040;
            model->id_0     = 0;
            model->value_E  = 1;
            model->count_2  = 9;
            break;
        case 1:
            model->color_14 = 0x2E404040;
            model->id_0     = 3;
            model->value_E  = 1;
            model->count_2  = 9;
            break;
        case 2:
            model->id_0     = 4;
            model->value_E  = 2;
            model->color_14 = 0x2E808080;
            model->count_2  = 9;
            break;
        case 3:
            model->id_0     = 5;
            model->color_14 = 0x2E808080;
            model->value_E  = 3;
            model->count_2  = 9;
            break;
        default:
            func_8003187C(slot);
            return NULL;
    }
    model->value_C  = 0x3FF;
    model->value_1  = wp->value_1;
    model->value_12 = 0;
    if (kind == 0)
    {
        for (i = 0; i < model->count_2; i++)
        {
            model->mode_3[i] = 7;
            for (j = 0; j < 8; j++)
            {
                key = &model->key_18[i][j];
                switch (i)
                {
                    case 0:
                        key->rot_0 = &rot[2];
                        break;
                    case 3:
                        key->rot_0 = &rot[14];
                        break;
                    case 6:
                        key->rot_0 = &rot[15];
                        break;
                    case 1:
                        key->rot_0 = &rot[0];
                        break;
                    case 4:
                        key->rot_0 = &rot[10];
                        break;
                    case 7:
                        key->rot_0 = &rot[12];
                        break;
                    case 2:
                        key->rot_0 = &rot[1];
                        break;
                    case 5:
                        key->rot_0 = &rot[11];
                        break;
                    case 8:
                        key->rot_0 = &rot[13];
                        break;
                }
                key->value_4 = 0;
                key->value_5 = 0;
                key->value_6 = 0;
            }
        }
    }
    else
    {
        for (i = 0; i < model->count_2; i++)
        {
            model->mode_3[i] = 7;
            for (j = 0; j < 8; j++)
            {
                key          = &model->key_18[i][j];
                key->rot_0   = rot;
                key->value_4 = 0;
                key->value_5 = 0;
                key->value_6 = 0;
            }
            rot++;
        }
    }
    return slot;
}

void func_80105CF8(STAGE_10C *wp, sint32 angle)
{
    wp->matrix_8C.m.m[1][1] = angle & 0x3FF;
}

void func_80105D04(STAGE_OBJ *wp)
{
    D_8011B4FC[wp->variant_3](wp, &wp->model_88);
}

void func_80105D40(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;

    on = 0;
    for (i = 0; i < 9; i++)
    {
        switch (i % 3)
        {
            case 0:
                on           = wp->u_C.b.byte_C & 1;
                grid->mode_0 = 0;
                break;
            case 1:
                on           = ((uint8)wp->u_C.b.byte_C >> 1) & 1;
                grid->mode_0 = 1;
                break;
            case 2:
                on           = ((uint8)wp->u_C.b.byte_C >> 2) & 1;
                grid->mode_0 = 2;
                break;
        }
        if (on)
        {
            n = grid->count_3[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_80106120(grid, i, j);
            }
            if (grid->count_3[i] < 0x40)
            {
                grid->count_3[i]++;
            }
        }
    }
    grid->frame_12++;
}

void func_80105EC8(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 9; i++)
    {
        n = grid->count_3[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80106120(grid, i, j);
        }
        if (grid->count_3[i] < 0x40)
        {
            grid->count_3[i]++;
        }
    }
    grid->frame_12++;
}

void func_80105F90(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 9; i++)
    {
        n = grid->count_3[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80106120(grid, i, j);
        }
        if (grid->count_3[i] < 0x40)
        {
            grid->count_3[i]++;
        }
    }
    grid->frame_12++;
}

void func_80106058(STAGE_OBJ *wp, ST17_GRID *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 7; i++)
    {
        n = grid->count_3[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80106120(grid, i, j);
        }
        if (grid->count_3[i] < 0x40)
        {
            grid->count_3[i]++;
        }
    }
    grid->frame_12++;
}

void func_80106120(ST17_GRID *grid, uint8 row, uint8 col)
{
    ST17_CELL *cell;

    cell = &grid->cell_18[row][col];
    D_8011B50C[grid->mode_0](grid, cell);
    if ((grid->mask_C >> row) & 1)
    {
        D_8011B524[grid->kind_E](cell, grid->value_14);
    }
}

void func_801061CC(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x100 - ((r >> 2) & 7);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        if (cell->frame_6 > 0x34)
        {
            cell->y_C += 8 + ((r >> 4) & 3);
        }
        cell->z_E += 0x10 + ((r >> 6) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801062CC(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x100 - ((r >> 2) & 7);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A -= 0xC + (r & 7);
        cell->y_C -= 0xC + ((r >> 2) & 7);
        cell->z_E += 0x10 + ((r >> 4) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801063D8(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x100 - ((r >> 2) & 7);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A += 0xC + (r & 7);
        cell->y_C -= 0xC + ((r >> 2) & 7);
        cell->z_E += 0x10 + ((r >> 4) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801064E4(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0x12C - ((r >> 2) & 0x1F);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x + ((r >> 4) & 0xF);
        cell->y_C     = cell->origin_0->y - ((r >> 6) & 0x1F);
        cell->z_E     = cell->origin_0->z + ((r >> 8) & 0x1F);
    }
    else
    {
        cell->shade_5 += 1;
        cell->frame_6--;
        cell->size_8 += 3;
        cell->x_A += 0xA + ((r >> 2) & 7);
        cell->y_C -= 0xA + ((r >> 4) & 7);
        cell->z_E += 0x2A + ((r >> 6) & 0xF);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80106618(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0xC8 - ((r >> 2) & 0x1F);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y - ((r >> 6) & 0x1F);
        cell->z_E     = cell->origin_0->z - ((r >> 8) & 0x1F);
    }
    else if (cell->state_4 == 1)
    {
        cell->shade_5 += 2;
        cell->frame_6--;
        cell->size_8 += 2;
        cell->y_C -= 2 + ((r >> 4) & 7);
        cell->z_E += 0x18 + ((r >> 6) & 0xF);
        if (cell->frame_6 == 0)
        {
            if (grid->frame_12 > 0xB4)
            {
                cell->state_4 = 2;
            }
            else
            {
                cell->state_4 = 0;
            }
        }
    }
}

void func_80106760(ST17_GRID *grid, ST17_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->shade_5 = 0;
        cell->size_8  = 0x50 - ((r >> 2) & 0x1F);
        cell->x_A     = cell->origin_0->x;
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z;
    }
    else
    {
        cell->shade_5 += 2;
        cell->frame_6 -= 1;
        cell->size_8 += 4;
        cell->y_C -= 2 + ((r >> 4) & 7);
        cell->z_E += 0x18;
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80106848(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;

    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = 0x3D480040;
    p->uv_14   = 0x4E005F;
    p->uv_1C   = 0x1F40;
    p->uv_24   = 0x1F5F;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_801068EC(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011B534[cell->frame_6 >> 2];
    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = u | 0x3D480000;
    p->uv_14   = (u + 0x1F) | 0x4E0000;
    p->uv_1C   = u | 0x1F00;
    p->uv_24   = (u + 0x1F) | 0x1F00;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}

void func_801069BC(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_8011B534[cell->frame_6 >> 2];
        p          = Billboard_get();
        p->code_4  = color - cell->shade_5 * 0x10101;
        p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
        p->z_10    = cell->z_E;
        p->uv_C    = u | 0x3D480000;
        p->uv_14   = (u + 0x1F) | 0x4E0000;
        p->uv_1C   = u | 0x1F00;
        p->uv_24   = (u + 0x1F) | 0x1F00;
        p->size_18 = cell->size_8;
        p->pad_20  = 8;
    }
}

void func_80106AA0(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011B534[cell->frame_6 >> 2];
    p          = Billboard_get();
    p->code_4  = color - cell->shade_5 * 0x10101;
    p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
    p->z_10    = cell->z_E;
    p->uv_C    = u | 0x3D480000;
    p->uv_14   = (u + 0x1F) | 0x4E0000;
    p->uv_1C   = u | 0x1F00;
    p->uv_24   = (u + 0x1F) | 0x1F00;
    p->size_18 = cell->size_8;
    p->pad_20  = 8;
}
