#include "common.h"
#include "st17.h"

STAGE_OBJ *func_80101A14(STAGE_OBJ *owner, uint8 count, STCOM_SVECTOR *pos)
{
    STAGE_OBJ *wp;
    ST17_RIBBON *rb;
    ST17_STRAND *st;
    uint8 i;
    uint8 j;

    wp = func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    if (count == 0 || count > 6)
    {
        func_80031824(wp);
        return NULL;
    }
    wp->flags_0 = 1;
    wp->flags_6 |= 0x20;
    wp->value_4         = 0;
    *(uint32 *)&wp->u_C = 0;
    wp->kind_2          = 0x12;
    wp->variant_3       = 2;
    wp->value_10        = 0;
    rb                  = ST17_RIBBON_OF(wp);
    rb->type_0          = 3;
    rb->value_1         = 0x3F;
    rb->value_2         = owner->value_1;
    rb->count_3         = count;
    rb->value_B         = 0;
    rb->color_10        = 0x2E808080;
    rb->value_C         = 0;
    for (i = 0; i < count; i++)
    {
        rb->value_4[i] = 7;
        for (j = 0, st = &rb->strand_14[i]; j < 8; j++)
        {
            st->pt[j].pos_0   = pos;
            st->pt[j].value_4 = 0;
            st->pt[j].value_5 = 0;
            st->pt[j].value_6 = 0;
        }
        pos++;
    }
    return wp;
}

STAGE_OBJ *func_80101B58(STAGE_OBJ *owner, sint8 kind, STCOM_SVECTOR *pos)
{
    STAGE_OBJ *wp;
    ST17_RIBBON *rb;
    ST17_STRAND *st;
    uint8 i;
    uint8 j;

    wp = func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    rb                  = ST17_RIBBON_OF(wp);
    wp->flags_0         = 1;
    wp->kind_2          = 0x12;
    wp->value_4         = 0;
    wp->variant_3       = kind;
    *(uint32 *)&wp->u_C = 0;
    switch (kind)
    {
        case 0:
            rb->type_0   = 0;
            rb->count_3  = 3;
            rb->value_B  = 1;
            rb->color_10 = 0x2E808080;
            break;
        case 1:
            rb->type_0   = 1;
            rb->count_3  = 6;
            rb->value_B  = 1;
            rb->color_10 = 0x2E404040;
            break;
        case 3:
            rb->type_0   = 4;
            rb->count_3  = 6;
            rb->value_B  = 2;
            rb->color_10 = 0x2E404040;
            break;
        default:
            func_80031824(wp);
            return NULL;
    }
    rb->value_1 = 0x3F;
    rb->value_2 = owner->value_1;
    rb->value_C = 0;
    for (i = 0; i < rb->count_3; i++)
    {
        rb->value_4[i] = 7;
        for (j = 0, st = &rb->strand_14[i]; j < 8; j++)
        {
            st->pt[j].pos_0   = pos;
            st->pt[j].value_4 = 0;
            st->pt[j].value_5 = 0;
            st->pt[j].value_6 = 0;
        }
        pos++;
    }
    return wp;
}

// Nothing calls it.
void func_80101D04(uint8 *wp, sint32 value)
{
    wp[0x89] = value & 0x3F;
}

void func_80101D10(STAGE_OBJ *wp)
{
    D_8011AF14[wp->variant_3](wp, &wp->model_88);
}

void func_80101D4C(STAGE_OBJ *wp, ST17_GRID6 *grid)
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
            func_801022BC(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
}

void func_80101E74(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST17_CELL *cell;

    on = 0;
    for (i = 0; i < 6; i++)
    {
        grid->mode_0 = (i < 3) ? 1 : 2;
        switch (i)
        {
            case 0:
                on = wp->u_C.b.byte_C & 1;
                break;
            case 1:
                on = ((uint8)wp->u_C.b.byte_C >> 1) & 1;
                break;
            case 2:
                on = ((uint8)wp->u_C.b.byte_C >> 2) & 1;
                break;
            case 3:
                on = wp->u_C.b.byte_D & 1;
                break;
            case 4:
                on = ((uint8)wp->u_C.b.byte_D >> 1) & 1;
                break;
            case 5:
                on = ((uint8)wp->u_C.b.byte_D >> 2) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_801022BC(grid, i, j);
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

void func_80102038(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST17_CELL *cell;

    on = 0;
    for (i = 0; i < grid->rows_3; i++)
    {
        switch (i)
        {
            case 0:
                on = wp->u_C.b.byte_C & 1;
                break;
            case 1:
                on = ((uint8)wp->u_C.b.byte_C >> 1) & 1;
                break;
            case 2:
                on = ((uint8)wp->u_C.b.byte_C >> 2) & 1;
                break;
            case 3:
                on = ((uint8)wp->u_C.b.byte_C >> 3) & 1;
                break;
            case 4:
                on = ((uint8)wp->u_C.b.byte_C >> 4) & 1;
                break;
            case 5:
                on = ((uint8)wp->u_C.b.byte_C >> 5) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_801022BC(grid, i, j);
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

void func_801021F4(STAGE_OBJ *wp, ST17_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 6; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_801022BC(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
    grid->frame_C++;
}

void func_801022BC(ST17_GRID6 *grid, uint8 row, uint8 col)
{
    ST17_CELL *cell;

    cell = &grid->cell_14[row][col];
    D_8011AF24[grid->mode_0](grid, cell);
    if ((grid->mask_1 >> row) & 1)
    {
        D_8011AF38[grid->kind_B](cell, grid->value_10);
    }
}

void func_80102368(ST17_GRID6 *grid, ST17_CELL *cell)
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

void func_80102470(ST17_GRID6 *grid, ST17_CELL *cell)
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

void func_80102598(ST17_GRID6 *grid, ST17_CELL *cell)
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

void func_801026C0(ST17_GRID6 *grid, ST17_CELL *cell)
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

void func_801027B0(ST17_GRID6 *grid, ST17_CELL *cell)
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

void func_801028D0(ST17_CELL *cell, sint32 color)
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

void func_80102974(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011AF44[cell->frame_6 >> 2];
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

void func_80102A44(ST17_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_8011AF44[cell->frame_6 >> 2];
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

void func_80102B28(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene                   = &Scene_work;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            wp->variant_3 = 1;
            wp->flags_0 |= 2;
            Model_work_init(wp, &wp->variant_3);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->anim_prev_AD   = 0xFF;
            wp->value_78       = 0;
            wp->anim_AC        = 0;
            wp->rotation.z     = -0x13F;
            wp->routine_0++;
            break;
        case 1:
            if (ST17_SCENE_BYTE(scene, 7) == 1)
            {
                wp->routine_0++;
            }
            break;
        case 2:
            wp->rotation.z += 0x3F;
            if (ST17_SCENE_BYTE(scene, 7) == 2)
            {
                wp->routine_0++;
            }
            break;
        case 3:
            wp->rotation.z = 0x1F4;
            if (ST17_SCENE_BYTE(scene, 7) == 3)
            {
                wp->routine_0++;
            }
            break;
        case 4:
            wp->rotation.z -= 0xAB;
            if (ST17_SCENE_BYTE(scene, 7) == 4)
            {
                wp->routine_0++;
            }
            break;
        case 5:
            wp->variant_3 = 0;
            Model_work_init(wp, &wp->variant_3);
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            wp->value_78       = 0;
            wp->anim_AC        = 0;
            wp->anim_prev_AD   = 0xFF;
            wp->routine_0++;
            // fall through
        case 6:
            wp->rotation.z -= 0xAB;
            break;
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    Model_parts_mtx_set_yxz(wp);
}
