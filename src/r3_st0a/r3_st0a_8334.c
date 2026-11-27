#include "common.h"
#include "st0a.h"

ST0A_GRID_OBJ *func_80108334(STAGE_OBJ *owner, uint8 rows, STCOM_SVECTOR *origin)
{
    ST0A_GRID_OBJ *wp;
    ST0A_GRID6 *grid;
    ST0A_CELL *cell;
    uint8 i;
    uint8 j;
    wp = (ST0A_GRID_OBJ *)func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    if (rows == 0 || rows > 6)
    {
        func_80031824(wp);
        return NULL;
    }
    grid        = &wp->grid;
    wp->be_flag = MOVE;
    wp->id      = 0x12;
    wp->value_4 = 0;
    wp->flags |= 0x20;
    wp->value_C         = 0;
    wp->type            = 2;
    wp->value_10        = 0;
    wp->grid.mode_0     = 3;
    wp->grid.mask_1     = 0x3F;
    wp->grid.reserved02 = owner->work_id;
    wp->grid.rows_3     = rows;
    wp->grid.kind_B     = 0;
    wp->grid.value_10   = 0x2E808080;
    wp->grid.frame_C    = 0;
    for (i = 0; i < rows; i++)
    {
        grid->count_4[i] = 7;
        for (j = 0; j < 8; j++)
        {
            cell           = &grid->cell_14[i][j];
            cell->origin_0 = (STAGE_XYZ *)origin;
            cell->state_4  = 0;
            cell->shade_5  = 0;
            cell->frame_6  = 0;
        }
        origin++;
    }
    return wp;
}

ST0A_GRID_OBJ *func_80108478(STAGE_OBJ *owner, sint8 variant, STCOM_SVECTOR *origin)
{
    ST0A_GRID_OBJ *wp;
    ST0A_GRID6 *grid;
    ST0A_CELL *cell;
    uint8 i;
    uint8 j;
    wp = (ST0A_GRID_OBJ *)func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    grid        = &wp->grid;
    wp->be_flag = MOVE;
    wp->id      = 0x12;
    wp->value_4 = 0;
    wp->type    = variant;
    wp->value_C = 0;
    switch (variant)
    {
        case 0:
            grid->mode_0   = 0;
            grid->rows_3   = 3;
            grid->kind_B   = 1;
            grid->value_10 = 0x2E808080;
            break;
        case 1:
            grid->mode_0   = 1;
            grid->rows_3   = 6;
            grid->kind_B   = 1;
            grid->value_10 = 0x2E404040;
            break;
        case 3:
            grid->mode_0   = 4;
            grid->rows_3   = 6;
            grid->kind_B   = 2;
            grid->value_10 = 0x2E404040;
            break;
        default:
            func_80031824(wp);
            return NULL;
    }
    grid->mask_1     = 0x3F;
    grid->reserved02 = owner->work_id;
    grid->frame_C    = 0;
    for (i = 0; i < grid->rows_3; i++)
    {
        grid->count_4[i] = 7;
        for (j = 0; j < 8; j++)
        {
            cell           = &grid->cell_14[i][j];
            cell->origin_0 = (STAGE_XYZ *)origin;
            cell->state_4  = 0;
            cell->shade_5  = 0;
            cell->frame_6  = 0;
        }
        origin++;
    }
    return wp;
}

void func_80108624(uint8 *wp, sint32 value)
{
    wp[0x89] = value & 0x3F;
}

void func_80108630(STAGE_OBJ *wp)
{
    D_80116144[wp->type](wp, &wp->model_88);
}

void func_8010866C(STAGE_OBJ *wp, ST0A_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 rows;

    if (STAGE_GAME_S16(0x5E) / 4 >= STAGE_GAME_S16(0x5C))
    {
        rows = 3;
    }
    else if (STAGE_GAME_S16(0x5E) / 2 >= STAGE_GAME_S16(0x5C))
    {
        rows = 2;
    }
    else
    {
        rows = STAGE_GAME_S16(0x5E) / 4 * 3 >= STAGE_GAME_S16(0x5C);
    }
    for (i = 0; i < rows; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80108BDC(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
}

void func_80108794(STAGE_OBJ *wp, ST0A_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST0A_CELL *cell;

    on = 0;
    for (i = 0; i < 6; i++)
    {
        grid->mode_0 = (i < 3) ? 1 : 2;
        switch (i)
        {
            case 0:
                on = wp->u_C.b.work_0 & 1;
                break;
            case 1:
                on = ((uint8)wp->u_C.b.work_0 >> 1) & 1;
                break;
            case 2:
                on = ((uint8)wp->u_C.b.work_0 >> 2) & 1;
                break;
            case 3:
                on = wp->u_C.b.work_1 & 1;
                break;
            case 4:
                on = ((uint8)wp->u_C.b.work_1 >> 1) & 1;
                break;
            case 5:
                on = ((uint8)wp->u_C.b.work_1 >> 2) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_80108BDC(grid, i, j);
            }
            if (grid->count_4[i] < 0x40)
            {
                grid->count_4[i]++;
            }
        }
        else if (grid->count_4[i] >= 8)
        {
            grid->count_4[i] = 7;
            for (j = 0; j < 8; j++)
            {
                cell          = &grid->cell_14[i][j];
                cell->state_4 = 0;
                cell->shade_5 = 0;
                cell->frame_6 = 0;
            }
        }
    }
}

void func_80108958(STAGE_OBJ *wp, ST0A_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST0A_CELL *cell;

    on = 0;
    for (i = 0; i < grid->rows_3; i++)
    {
        switch (i)
        {
            case 0:
                on = wp->u_C.b.work_0 & 1;
                break;
            case 1:
                on = ((uint8)wp->u_C.b.work_0 >> 1) & 1;
                break;
            case 2:
                on = ((uint8)wp->u_C.b.work_0 >> 2) & 1;
                break;
            case 3:
                on = ((uint8)wp->u_C.b.work_0 >> 3) & 1;
                break;
            case 4:
                on = ((uint8)wp->u_C.b.work_0 >> 4) & 1;
                break;
            case 5:
                on = ((uint8)wp->u_C.b.work_0 >> 5) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_80108BDC(grid, i, j);
            }
            if (grid->count_4[i] < 0x40)
            {
                grid->count_4[i]++;
            }
        }
        else if (grid->count_4[i] >= 8)
        {
            grid->count_4[i] = 7;
            for (j = 0; j < 8; j++)
            {
                cell          = &grid->cell_14[i][j];
                cell->state_4 = 0;
                cell->shade_5 = 0;
                cell->frame_6 = 0;
            }
        }
    }
}

void func_80108B14(STAGE_OBJ *wp, ST0A_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 6; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80108BDC(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
    grid->frame_C++;
}

void func_80108BDC(ST0A_GRID6 *grid, uint8 row, uint8 col)
{
    ST0A_CELL *cell;

    cell = &grid->cell_14[row][col];
    D_80116154[grid->mode_0](grid, cell);
    if ((grid->mask_1 >> row) & 1)
    {
        D_80116168[grid->kind_B](cell, grid->value_10);
    }
}

void func_80108C88(ST0A_GRID6 *grid, ST0A_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0x40 - ((r >> 2) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 4) & 0x1F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 6) & 0x1F);
    }
    else
    {
        cell->shade_5 += 2;
        cell->frame_6--;
        cell->size_8 += 2;
        cell->y_C -= 8 + (r & 7);
        cell->z_E += 0x10 + ((r >> 2) & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_80108D90(ST0A_GRID6 *grid, ST0A_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0xC4 - ((r >> 1) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 2) & 0x3F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 4) & 0x3F);
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

void func_80108EB8(ST0A_GRID6 *grid, ST0A_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0xC4 - ((r >> 2) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x + ((r >> 4) & 0x3F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 6) & 0x3F);
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

void func_80108FE0(ST0A_GRID6 *grid, ST0A_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 7);
        cell->size_8  = 0x40 - ((r >> 2) & 7);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 4) & 0x1F);
        cell->y_C     = cell->origin_0->y;
        cell->z_E     = cell->origin_0->z - ((r >> 6) & 0x1F);
    }
    else
    {
        cell->shade_5 += 2;
        cell->frame_6--;
        cell->size_8 += 2;
        cell->y_C -= 8 + (r & 7);
        if (cell->frame_6 == 0)
        {
            cell->state_4 = 0;
        }
    }
}

void func_801090D0(ST0A_GRID6 *grid, ST0A_CELL *cell)
{
    sint16 r;

    r = rand();
    if (cell->state_4 == 0)
    {
        cell->state_4++;
        cell->frame_6 = 0x40 - (r & 3);
        cell->size_8  = 7 - ((r >> 2) & 1);
        cell->shade_5 = 0;
        cell->x_A     = cell->origin_0->x - ((r >> 4) & 3);
        cell->y_C     = cell->origin_0->y - ((r >> 6) & 3);
        cell->z_E     = cell->origin_0->z - ((r >> 8) & 3);
    }
    else if (cell->state_4 == 1)
    {
        cell->shade_5 += 1;
        cell->frame_6 -= 1;
        cell->y_C -= 1;
        if (cell->frame_6 == 0)
        {
            if (grid->frame_C > 0x12C)
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

void func_801091F0(ST0A_CELL *cell, sint32 color)
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

void func_80109294(ST0A_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_80116174[cell->frame_6 >> 2];
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

void func_80109364(ST0A_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_80116174[cell->frame_6 >> 2];
        p          = Billboard_get();
        p->code_4  = color - cell->shade_5 * 0x10101;
        p->xy_8    = (uint16)cell->x_A | (cell->y_C << 16);
        p->z_10    = cell->z_E;
        p->uv_C    = u | 0x3D480000;
        p->uv_14   = (u + 0x1F) | 0x2E0000;
        p->uv_1C   = u | 0x1F00;
        p->uv_24   = (u + 0x1F) | 0x1F00;
        p->size_18 = cell->size_8;
        p->pad_20  = 8;
    }
}
