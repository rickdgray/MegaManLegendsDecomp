#include "common.h"
#include "st0b.h"

ST0B_GRID_OBJ *func_80109CB0(STAGE_OBJ *owner, uint8 rows, STCOM_SVECTOR *origin)
{
    ST0B_GRID_OBJ *wp;
    ST0B_GRID6 *grid;
    ST0B_CELL *cell;
    uint8 i;
    uint8 j;
    wp = (ST0B_GRID_OBJ *)func_80031418();
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
    wp->flags_0 = 1;
    wp->kind_2  = 0x12;
    wp->value_4 = 0;
    wp->flags_6 |= 0x20;
    wp->value_C         = 0;
    wp->variant_3       = 2;
    wp->value_10        = 0;
    wp->grid.mode_0     = 3;
    wp->grid.mask_1     = 0x3F;
    wp->grid.reserved02 = owner->value_1;
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

ST0B_GRID_OBJ *func_80109DF4(STAGE_OBJ *owner, sint8 variant, STCOM_SVECTOR *origin)
{
    ST0B_GRID_OBJ *wp;
    ST0B_GRID6 *grid;
    ST0B_CELL *cell;
    uint8 i;
    uint8 j;
    wp = (ST0B_GRID_OBJ *)func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    grid          = &wp->grid;
    wp->flags_0   = 1;
    wp->kind_2    = 0x12;
    wp->value_4   = 0;
    wp->variant_3 = variant;
    wp->value_C   = 0;
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
    grid->reserved02 = owner->value_1;
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

// Nothing calls it.
void func_80109FA0(uint8 *wp, sint32 value)
{
    wp[0x89] = value & 0x3F;
}

void func_80109FAC(STAGE_OBJ *wp)
{
    D_8011B3A8[wp->variant_3](wp, &wp->model_88);
}

void func_80109FE8(STAGE_OBJ *wp, ST0B_GRID6 *grid)
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
            func_8010A558(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
}

void func_8010A110(STAGE_OBJ *wp, ST0B_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST0B_CELL *cell;

    on = 0;
    for (i = 0; i < 6; i++)
    {
        if (i < 3)
        {
            grid->mode_0 = 1;
        }
        else
        {
            grid->mode_0 = 2;
        }
        switch (i)
        {
            case 0:
                on = wp->u_C.b.byte_C & 1;
                break;
            case 1:
                on = (wp->u_C.b.byte_C >> 1) & 1;
                break;
            case 2:
                on = (wp->u_C.b.byte_C >> 2) & 1;
                break;
            case 3:
                on = wp->u_C.b.byte_D & 1;
                break;
            case 4:
                on = (wp->u_C.b.byte_D >> 1) & 1;
                break;
            case 5:
                on = (wp->u_C.b.byte_D >> 2) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_8010A558(grid, i, j);
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
                cell          = grid->cell_14[i] + j;
                cell->state_4 = 0;
                cell->shade_5 = 0;
                cell->frame_6 = 0;
            }
        }
    }
}

void func_8010A2D4(STAGE_OBJ *wp, ST0B_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST0B_CELL *cell;

    on = 0;
    for (i = 0; i < grid->rows_3; i++)
    {
        switch (i)
        {
            case 0:
                on = wp->u_C.b.byte_C & 1;
                break;
            case 1:
                on = (wp->u_C.b.byte_C >> 1) & 1;
                break;
            case 2:
                on = (wp->u_C.b.byte_C >> 2) & 1;
                break;
            case 3:
                on = (wp->u_C.b.byte_C >> 3) & 1;
                break;
            case 4:
                on = (wp->u_C.b.byte_C >> 4) & 1;
                break;
            case 5:
                on = (wp->u_C.b.byte_C >> 5) & 1;
                break;
        }
        if (on)
        {
            n = grid->count_4[i] >> 3;
            for (j = 0; j < n; j++)
            {
                func_8010A558(grid, i, j);
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
                cell          = grid->cell_14[i] + j;
                cell->state_4 = 0;
                cell->shade_5 = 0;
                cell->frame_6 = 0;
            }
        }
    }
}

void func_8010A490(STAGE_OBJ *wp, ST0B_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 6; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_8010A558(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
    grid->frame_C++;
}

void func_8010A558(ST0B_GRID6 *grid, uint8 row, uint8 col)
{
    ST0B_CELL *cell;

    cell = &grid->cell_14[row][col];
    D_8011B3B8[grid->mode_0](grid, cell);
    if ((grid->mask_1 >> row) & 1)
    {
        D_8011B3CC[grid->kind_B](cell, grid->value_10);
    }
}

void func_8010A604(ST0B_GRID6 *grid, ST0B_CELL *cell)
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

void func_8010A70C(ST0B_GRID6 *grid, ST0B_CELL *cell)
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

void func_8010A834(ST0B_GRID6 *grid, ST0B_CELL *cell)
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

void func_8010A95C(ST0B_GRID6 *grid, ST0B_CELL *cell)
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

void func_8010AA4C(ST0B_GRID6 *grid, ST0B_CELL *cell)
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

void func_8010AB6C(ST0B_CELL *cell, sint32 color)
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

void func_8010AC10(ST0B_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8011B3D8[cell->frame_6 >> 2];
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

void func_8010ACE0(ST0B_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_8011B3D8[cell->frame_6 >> 2];
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

void func_8010ADC4(ST0B_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    if (wp->routine_0 == 0)
    {
        func_8010AE94(wp, &wp->ctl);
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
    }
    else
    {
        func_8010AF98(wp, &wp->ctl);
        func_80032488(wp);
    }
}

// value_F is unsigned, but retail stores the -0x10 as a signed byte (li -16).
void func_8010AE94(ST0B_ACTOR *wp, ST0B_ACTOR_CTL *ctl)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x01000100;
    wp->scale.words[1] = 0x100;
    wp->scale.v.pad    = 0x4210;
    wp->value_D        = 5;
    wp->value_78       = 0;
    wp->value_E        = 0x14;
    if (wp->variant_3 != 0)
    {
        wp->timer_C            = 0x1C;
        *(sint8 *)&wp->value_F = -0x10;
    }
    else
    {
        wp->timer_C = 0x20;
        wp->value_F = 0x10;
    }
    ctl->flags_0 = wp->timer_C * 10;
    ctl->value_2 = wp->value_D * 10;
    ctl->timer_4 = wp->value_E * 10;
    ctl->value_6 = (sint8)wp->value_F;
    ctl->value_8 = 0;
    ctl->timer_A = wp->position.y;
}

void func_8010AF98(ST0B_BOBBER *wp, ST0B_BOB_B *bob)
{
    Obj_pos_set(wp, bob->speed_0, 0, 0);
    wp->rotation.y = (wp->rotation.y + bob->turn_6) & 0xFFF;
    if (bob->period_4 > 0)
    {
        wp->position.y       = bob->base_A + ((bob->height_2 * D_800BBCF8[(bob->phase_8 << 6) / bob->period_4]) >> 12);
        wp->position_fixed.y = wp->position.y << 16;
        bob->phase_8++;
        bob->phase_8 %= bob->period_4;
    }
}

void func_8010B0B8(STAGE_OBJ *wp)
{
    D_8011B3EC[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
}

void func_8010B118(STAGE_OBJ *wp)
{
    STAGE_SCENE_VIEW *scene;
    STAGE_OBJ *src;

    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    scene = &STAGE_SCENE;
    switch (Scene_work.u_8.byte[0])
    {
        case 0:
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x200;
            wp->scale.v.pad    = 0x4210;
            func_800322A8(wp, 2, 0);
            wp->routine_1 = 1;
            break;
        case 2:
        case 4:
        case 6:
            wp->scale.words[0] = 0x04000400;
            wp->scale.words[1] = 0x400;
            wp->scale.v.pad    = 0x4210;
            func_800322A8(wp, 0, 0);
            src          = scene->slot_24[0];
            wp->position = src->position;
            wp->position.y += 0x39A;
            wp->position_fixed.v = src->position_fixed.v;
            wp->position_fixed.v.y += 0x39A;
            func_80032488(wp);
            wp->routine_1 = 3;
            break;
    }
    wp->routine_2 = 0;
    wp->u_C.b.byte_D++;
}

void func_8010B288(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 2, 0);
        wp->routine_2++;
    }
}

void func_8010B2D4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 3, 0);
        wp->u_C.b.byte_D = 0;
        wp->routine_2++;
    }
}

void func_8010B320(STAGE_OBJ *wp)
{
    STAGE_OBJ *pl;

    wp->u_C.b.byte_D = 0;
    pl               = STAGE_SCENE.slot_24[0];
    wp->position     = pl->position;
    wp->position.y += 0x39A;
    wp->position_fixed = pl->position_fixed;
    wp->position_fixed.v.y += 0x39A;
}

void func_8010B394(STAGE_OBJ *wp)
{
    D_8011B3FC[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
}

void func_8010B3F4(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    func_800322A8(wp, 1, 0);
    wp->routine_1 = 1;
    wp->routine_2 = 0;
    wp->u_C.b.byte_D++;
}

void func_8010B470(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_8010B4BC(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR ofs;
    ST0B_BOB *bob;
    STCOM_SVECTOR *rot;
    sint32 flag;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    bob                     = ST0B_OBJ_BOB(wp);
    bob->seed_16            = rand();
    func_8010B8D4((ST0B_OBJ *)wp, 0x4210);
    D_8011B404[wp->routine_0](wp, bob);
    if (wp->variant_3 == 0 && (bob->flags_14 & 4))
    {
        rot = ST0B_SP_ROT;
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        rot->y = (bob->angle_1A - (sint16)(wp->rotation.y - 0x800)) & 0xFFF;
        Model_parts_mtx_set_y(wp);
    }
    else if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    func_80030058(&ofs, wp->rotation.y, 0x400, 0, 0);
    func_80030150(&ofs, &bob->pos_2C);
    bob->pos_2C.x += wp->position.x;
    bob->pos_2C.z += wp->position.z;
    bob->pos_2C.y = wp->position.y - 0x80;
    flag          = (bob->flags_14 & 0xC00) != 0;
    func_800341BC(&bob->pos_2C, 0x100, 0, 0x8000, wp->value_1, &bob->hit_34, 0x04880000, 0, flag << 7);
    bob->hit_34 = 0;
}

void func_8010B6D8(ST0B_OBJ *wp, ST0B_BOB *bob)
{
    sint16 life;

    bob->flags_14 = 0;
    bob->value_18 = 0;
    bob->angle_1A = (wp->rotation.y + 0x800) & 0xFFF;
    bob->value_1E = wp->u_C.b.byte_C * 16;
    bob->value_1C = wp->u_C.b.byte_D * 100;
    if (wp->u_E.b.byte_E & 1)
    {
        bob->flags_14 |= 0x80;
    }
    else if (wp->u_E.b.byte_E & 2)
    {
        bob->flags_14 |= 0x100;
    }
    if (bob->flags_14 & 0x180)
    {
        if (wp->u_E.b.byte_E & 4)
        {
            bob->value_20 = 1;
            bob->value_22 = 0x200;
        }
        else
        {
            bob->value_20 = 2;
            bob->value_22 = 0x100;
        }
    }
    else
    {
        bob->value_20 = 0;
        bob->value_22 = 0;
    }
    bob->value_28 = wp->u_E.b.byte_F * 20;
    bob->timer_24 = 0x2D;
    bob->count_26 = 0;
    bob->hit_34   = 0;
    bob->value_38 = 0;
    bob->flags_14 |= 8;
    Track_set(bob->track_3C, 0xA, 0);
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->value_64       = 0;
    func_8010B8D4(wp, 0x4210);
    if (wp->variant_3 == 1)
    {
        wp->part_F8[3].value_3 = -1;
    }
    wp->anim_prev_AD     = 0xFF;
    wp->anim_AC          = 0;
    life                 = D_80098844[wp->kind_2]->life_8 * 4;
    wp->value_78         = 0;
    wp->value_44.half[0] = 0;
    wp->routine_1        = 0;
    wp->routine_2        = 0;
    wp->routine_3        = 0;
    wp->position.y += 0x100;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->routine_0          = 1;
    wp->value_6E           = life;
    wp->value_B0           = life;
    wp->value_B2           = life;
}

void func_8010B8D4(ST0B_OBJ *wp, sint32 color)
{
    sint32 i;

    i = 0;
    if (wp->variant_3 == 0)
    {
        wp->scale.v.pad = color;
        return;
    }
    wp->scale.v.pad = 0;
    for (; i < 3; i++)
    {
        wp->pal[i].color = color;
    }
    wp->pal[3].color = 0;
}

void func_8010B914(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    if (bob->flags_14 & 2)
    {
        if (bob->flags_14 & 0x40)
        {
            func_8010BBA0(wp, bob);
        }
        func_8010BAFC((ST0B_OBJ *)wp, bob);
    }
    if (wp->anim_AC == 0)
    {
        if (wp->variant_3 == 1 && (bob->flags_14 & 4))
        {
            wp->anim_AC = 1;
        }
    }
    else if (wp->anim_AC == 1)
    {
        if (wp->value_A7 == -1)
        {
            wp->anim_AC = 0;
        }
    }
    else
    {
        goto run;
    }
    if (bob->flags_14 & 0x800)
    {
        wp->anim_AC = 2;
    }
run:
    D_8011B410[wp->routine_1](wp, bob);
    if (bob->flags_14 & 1)
    {
        switch (wp->routine_1)
        {
            case 1:
                if (bob->flags_14 & 0x800)
                {
                    wp->routine_1 = 4;
                }
                else if (bob->flags_14 & 0x200)
                {
                    wp->routine_1 = 3;
                }
                else if (bob->flags_14 & 4)
                {
                    wp->routine_1 = 2;
                }
                break;
            case 2:
                if (bob->flags_14 & 0x800)
                {
                    wp->routine_1 = 4;
                }
                else if (bob->flags_14 & 0x200)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 1;
                    bob->timer_24 = 0x2D;
                    bob->flags_14 |= 8;
                }
                break;
            case 3:
                if (!(bob->flags_14 & 0x400))
                {
                    wp->routine_1 = 4;
                    break;
                }
                // fall through
            case 4:
                wp->routine_0 = 2;
                wp->routine_1 = 0;
                break;
        }
        wp->routine_2 = 0;
        bob->flags_14 &= ~1;
    }
}

void func_8010BAFC(ST0B_OBJ *wp, ST0B_BOB *bob)
{
    uint32 kind;
    sint32 damage;

    kind   = bob->hit_34;
    damage = kind & 0xFFFFFF;
    if (damage != 0)
    {
        if (kind & 0x18000000)
        {
            wp->value_B2 = wp->value_6E;
            wp->value_6E -= damage;
            if ((sint16)wp->value_6E <= 0)
            {
                bob->flags_14 = (bob->flags_14 & ~0x36) | 0x801;
            }
            Sound_call2(0xA0, &bob->pos_2C);
            func_8010B8D4(wp, 0x7FFF);
        }
        else
        {
            Sound_call2(0xA3, &bob->pos_2C);
        }
    }
}

void func_8010BBA0(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    STCOM_EFFECT *ep;
    sint32 speed;
    sint32 pace;
    sint32 angle;

    switch (wp->routine_3)
    {
        case 0:
            if (bob->value_1E == 0 || bob->value_1C == 0)
            {
                if (bob->flags_14 & 0x180)
                {
                    speed = 0x97;
                    bob->flags_14 |= 0x1000;
                    if (bob->value_20 == 1)
                    {
                        speed = 0xFB;
                    }
                    wp->value_44.half[0] = speed;
                    wp->routine_3        = 2;
                    break;
                }
                wp->value_44.half[0] = 0;
                wp->routine_3        = 4;
            }
            else
            {
                wp->value_44.half[0] = 8;
                bob->flags_14 |= 0x1000;
                wp->routine_3 = 1;
            }
            break;
        case 1:
            if (wp->value_44.half[0] < bob->value_1E)
            {
                wp->value_44.half[0] += 8;
            }
            else
            {
                wp->value_44.half[0] = bob->value_1E;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            bob->value_1C -= wp->value_44.half[0] >> 4;
            if (bob->value_1C <= 0)
            {
                speed = 0x97;
                if (bob->flags_14 & 0x180)
                {
                    if (bob->value_20 == 1)
                    {
                        speed = 0xFB;
                    }
                    wp->value_44.half[0] = speed;
                    wp->routine_3        = 2;
                }
                else
                {
                    wp->routine_3 = 3;
                }
            }
            break;
        case 2:
            pace = 0x97;
            if (bob->value_20 == 1)
            {
                pace = 0xFB;
            }
            wp->value_44.half[0] = pace;
            if (bob->value_22 > 0)
            {
                if (bob->flags_14 & 0x80)
                {
                    angle = wp->rotation.y;
                    if (bob->value_20 == 1)
                    {
                        wp->rotation.y = angle + 2;
                    }
                    else
                    {
                        wp->rotation.y = angle + 8;
                    }
                }
                else
                {
                    angle = wp->rotation.y;
                    if (bob->value_20 == 1)
                    {
                        wp->rotation.y = angle - 2;
                    }
                    else
                    {
                        wp->rotation.y = angle - 8;
                    }
                }
                wp->rotation.y &= 0xFFF;
                Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
                bob->value_22--;
            }
            else
            {
                wp->routine_3 = 3;
            }
            break;
        case 3:
            if (wp->value_44.half[0] <= 0)
            {
                wp->routine_3 = 4;
            }
            else
            {
                Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
                wp->value_44.half[0] -= 0x10;
            }
            break;
        case 4:
            bob->flags_14 = (bob->flags_14 & ~0x40) | 0x201;
            break;
    }
    if (bob->flags_14 & 0x1000)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->kind_2    = 0x15;
            ep->variant_3 = 0;
            ep->value_C   = wp->value_1;
            ep->value_D   = 1;
        }
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->kind_2    = 0x15;
            ep->variant_3 = 2;
            ep->value_C   = wp->value_1;
            ep->value_D   = 1;
        }
        bob->flags_14 &= ~0x1000;
    }
}

void func_8010BE88(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    wp->position.y         = ((D_800BBCF8[bob->count_26 & 0x3F] * 5) >> 12) - 1;
    wp->position_fixed.v.y = wp->position.y << 16;
    bob->count_26++;
}

void func_8010BED8(ST0B_OBJ *wp, ST0B_BOB *bob)
{
    sint32 i;
    sint32 red;
    sint32 half;

    wp->scale.v.pad = 0;
    for (i = 0; i < 4; i++)
    {
        wp->pal[i].color = 0x8210;
        if (ST0B_OBJ_JOINT(wp)[i].y > 0)
        {
            red  = 0x1F - (ST0B_OBJ_JOINT(wp)[i].y >> 5);
            half = red >> 1;
            if (red < 0)
            {
                red = 0;
            }
            wp->pal[i].color = (red << 10) | ((half << 5) | 0x8000) | half;
        }
    }
    switch (wp->routine_2)
    {
        case 0:
            wp->flags_0 |= 2;
            bob->effect_4[0] = func_80031618();
            if (bob->effect_4[0] != NULL)
            {
                bob->effect_4[0]->flags_0           = 5;
                bob->effect_4[0]->kind_2            = 0x10;
                bob->effect_4[0]->variant_3         = 5;
                bob->effect_4[0]->sprite.position.x = wp->position.x;
                bob->effect_4[0]->sprite.position.y = 0;
                bob->effect_4[0]->sprite.position.z = wp->position.z;
                Sound_call2(0x149, &wp->position);
            }
            wp->routine_2++;
            // fall through
        case 1:
            wp->position.y -= 0x10;
            if (wp->position.y < 0)
            {
                bob->flags_14 |= 0x42;
                wp->position.y  = -1;
                wp->routine_1   = 1;
                wp->routine_2   = 0;
                wp->scale.v.pad = 0x4210;
            }
            wp->position_fixed.v.y = wp->position.y << 16;
            break;
    }
}

void func_8010C060(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    STCOM_PL_WORK *pl;

    func_8010BE88(wp, bob);
    pl = &Player_work;
    if (wp->routine_2 == 0)
    {
        bob->angle_1A = (wp->rotation.y + 0x800) & 0xFFF;
        bob->value_18 = 0;
        wp->routine_2++;
    }
    if (bob->flags_14 & 0x800)
    {
        return;
    }
    if (bob->flags_14 & 8)
    {
        Track_stop(bob->track_3C);
        if (--bob->timer_24 <= 0)
        {
            bob->value_18 = 0;
            bob->flags_14 &= ~8;
        }
    }
    else if (wp->variant_3 == 0)
    {
        if (func_800364B0(bob->track_3C, wp, bob->angle_1A) != 0)
        {
            bob->value_18 = 0;
            if (Muku(&wp->position, &pl->position, bob->angle_1A, 0x800) > 0)
            {
                bob->flags_14 |= 0x15;
            }
            else
            {
                bob->flags_14 |= 0x25;
            }
        }
    }
    else if (func_8003648C(bob->track_3C, wp) != 0)
    {
        if (!(bob->value_18 & 0xF) && !(bob->seed_16 & 3))
        {
            bob->flags_14 |= 5;
        }
        bob->value_18++;
    }
}

void func_8010C1EC(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    uint8 *track;

    func_8010BE88(wp, bob);
    track = bob->track_3C;
    if (wp->variant_3 == 0)
    {
        func_800364B0(track, wp, bob->angle_1A);
        func_8010C3B0(wp, bob);
        return;
    }
    func_8003648C(track, wp);
    func_8010C264(wp, bob);
}

void func_8010C264(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    STAGE_PROP *slot;
    sint32 i;
    sint32 turn;

    switch (wp->routine_2)
    {
        case 0:
            if (wp->value_A4 == 9)
            {
                wp->routine_2++;
            }
            break;
        case 1:
            for (i = 0; i < 2; i++)
            {
                turn = i * 0x200 - 0x100;
                slot = (STAGE_PROP *)Open_SHL_WORK();
                if (slot != NULL)
                {
                    slot->flags_0    = 1;
                    slot->kind_2     = 0x20;
                    slot->position   = wp->position;
                    slot->rotation.y = wp->rotation.y + turn;
                }
            }
            Sound_call2(0x14A, &wp->position);
            wp->routine_2++;
            break;
        case 2:
            if (wp->value_A7 == -1)
            {
                bob->flags_14 = (bob->flags_14 & ~4) | 1;
            }
            break;
    }
}

void func_8010C3B0(STAGE_OBJ *wp, ST0B_BOB *bob)
{
    STCOM_FIXED_VECTOR pos;
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    ST0B_10C *shot;
    sint32 target;
    ST0B_PL *pl;

    pl = ST0B_PL_PTR;
    switch (wp->routine_2)
    {
        case 0:
            if (bob->value_18 < 0x30)
            {
                if (bob->flags_14 & 0x10)
                {
                    bob->angle_1A = (bob->angle_1A + 0x20) & 0xFFF;
                }
                else
                {
                    bob->angle_1A = (bob->angle_1A - 0x20) & 0xFFF;
                }
                pos.x = ST0B_OBJ_JOINT(wp)[3].x << 16;
                pos.y = ST0B_OBJ_JOINT(wp)[3].y << 16;
                pos.z = ST0B_OBJ_JOINT(wp)[3].z << 16;
                if (ST0B_ABS(bob->angle_1A - Angle_xz_vector(&pos, &pl->position_fixed)) < 0x20)
                {
                    bob->value_18 = 0;
                    wp->routine_2 = 1;
                }
                else
                {
                    bob->value_18++;
                }
            }
            else
            {
                bob->value_18 = 0;
                wp->routine_2 = 2;
            }
            break;
        case 1:
            if (bob->value_18 == 0)
            {
                shot = (ST0B_10C *)Open_SHL_WORK();
                if (shot != NULL)
                {
                    shot->flags_0    = 1;
                    shot->kind_2     = 0;
                    shot->variant_3  = 0;
                    shot->target_B8  = &pl->pos_3A8;
                    shot->position.x = ST0B_OBJ_JOINT(wp)[3].x;
                    shot->position.y = ST0B_OBJ_JOINT(wp)[3].y - 0x28;
                    shot->position.z = ST0B_OBJ_JOINT(wp)[3].z;
                    rot.z            = 0;
                    rot.x            = 0;
                    rot.y            = bob->angle_1A;
                    RotMatrixYXZ(&rot, &shot->matrix_8C.m);
                    scale.z = 0x200;
                    scale.y = 0x200;
                    scale.x = 0x200;
                    ScaleMatrix(&shot->matrix_8C.m, &scale);
                    Sound_call2(0x14C, &ST0B_OBJ_JOINT(wp)[3]);
                }
            }
            if (++bob->value_18 == 0x3C)
            {
                bob->value_18 = 0;
                wp->routine_2 = 2;
            }
            break;
        case 2:
            if (bob->flags_14 & 0x10)
            {
                bob->angle_1A = (bob->angle_1A - 0x20) & 0xFFF;
            }
            else
            {
                bob->angle_1A = (bob->angle_1A + 0x20) & 0xFFF;
            }
            target = (wp->rotation.y + 0x800) & 0xFFF;
            if (ST0B_ABS(target - bob->angle_1A) < 0x20)
            {
                bob->angle_1A = (wp->rotation.y + 0x800) & 0xFFF;
                wp->routine_2 = 3;
            }
            break;
        case 3:
            bob->flags_14 = (bob->flags_14 & ~0x34) | 1;
            break;
    }
}

void func_8010C69C(ST0B_OBJ *wp, ST0B_BOB *bob)
{
    sint32 i;
    sint32 red;
    sint32 half;

    switch (wp->routine_2)
    {
        case 0:
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            if (bob->value_28 > 0)
            {
                bob->value_28--;
            }
            else
            {
                wp->routine_2++;
            }
            break;
        case 1:
            if ((uint32)wp->value_80 > 0x240000)
            {
                bob->flags_14        = (bob->flags_14 | 0x400) & ~2;
                wp->value_44.half[1] = 0x12;
                wp->routine_2++;
            }
            break;
        case 2:
            bob->effect_4[0] = func_80031618();
            if (bob->effect_4[0] != NULL)
            {
                bob->effect_4[0]->flags_0           = 5;
                bob->effect_4[0]->kind_2            = 0x10;
                bob->effect_4[0]->variant_3         = 5;
                bob->effect_4[0]->sprite.position.x = wp->position.x;
                bob->effect_4[0]->sprite.position.y = 0;
                bob->effect_4[0]->sprite.position.z = wp->position.z;
            }
            wp->routine_2++;
            // fall through
        case 3:
            if (wp->position.y > 600)
            {
                bob->flags_14 |= 1;
            }
            break;
    }
    if (wp->routine_2 != 0)
    {
        wp->scale.v.pad = 0;
        for (i = 0; i < 4; i++)
        {
            wp->pal[i].color = 0x4210;
            if (ST0B_OBJ_JOINT(wp)[i].y > D_8011B424[i])
            {
                red = 0x1F - (ST0B_OBJ_JOINT(wp)[i].y - 0x6A) / 16;
                if (red < 0)
                {
                    red = 0;
                }
                half             = red >> 1;
                wp->pal[i].color = (red << 10) | ((half << 5) | 0x8000) | half;
            }
        }
        wp->position.y += wp->value_44.half[1];
        wp->position_fixed.v.y = wp->position.y << 16;
    }
}

void func_8010C8C0(ST0B_OBJ *wp, ST0B_BOB *bob)
{
    sint32 i;
    sint32 red;
    sint32 half;

    switch (wp->routine_2)
    {
        case 0:
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            bob->effect_4[0]     = func_80031618();
            if (bob->effect_4[0] != NULL)
            {
                bob->effect_4[0]->flags_0         = 5;
                bob->effect_4[0]->kind_2          = 0x10;
                bob->effect_4[0]->variant_3       = 2;
                bob->effect_4[0]->sprite.position = wp->position;
            }
            bob->effect_4[1] = func_80031618();
            if (bob->effect_4[1] != NULL)
            {
                bob->effect_4[1]->flags_0         = 5;
                bob->effect_4[1]->kind_2          = 0x10;
                bob->effect_4[1]->variant_3       = 3;
                bob->effect_4[1]->sprite.position = wp->position;
            }
            bob->effect_4[2] = func_80031618();
            if (bob->effect_4[2] != NULL)
            {
                bob->effect_4[2]->flags_0         = 5;
                bob->effect_4[2]->kind_2          = 0x10;
                bob->effect_4[2]->variant_3       = 4;
                bob->effect_4[2]->sprite.position = wp->position;
            }
            Sound_call2(0x14D, &wp->position);
            wp->routine_2++;
            break;
        case 1:
            if (wp->value_A7 == -1 && (uint32)wp->value_80 > 0x240000)
            {
                Sound_call2(0x14E, &wp->position);
                wp->value_44.half[1] = 8;
                wp->routine_2++;
            }
            break;
        case 2:
            if ((uint32)wp->value_80 <= 0x240000)
            {
                wp->value_44.half[1] = 0x10;
            }
            if (wp->position.y > 0x258)
            {
                wp->routine_2++;
            }
            else if (wp->position.y > 0x12C)
            {
                for (i = 0; i < 3; i++)
                {
                    if (bob->effect_4[i] != NULL)
                    {
                        bob->effect_4[i]->routine_0 = 4;
                        bob->effect_4[i]->routine_2 = ((0x258 - wp->position.y) << 7) / 300;
                    }
                }
            }
            break;
        case 3:
            for (i = 0; i < 3; i++)
            {
                if (bob->effect_4[i] != NULL)
                {
                    bob->effect_4[i]->routine_0 = 5;
                    bob->effect_4[i]->routine_1 = 0;
                    bob->effect_4[i]->routine_2 = 0x10;
                }
            }
            bob->flags_14 |= 1;
            break;
    }
    wp->scale.v.pad = 0;
    for (i = 0; i < 4; i++)
    {
        wp->pal[i].color = 0x4210;
        if (ST0B_OBJ_JOINT(wp)[i].y > 0x20)
        {
            red = 0x1F - (ST0B_OBJ_JOINT(wp)[i].y - 0x6A) / 16;
            if (red < 0)
            {
                red = 0;
            }
            half             = red >> 1;
            wp->pal[i].color = (red << 10) | ((half << 5) | 0x8000) | half;
        }
    }
    wp->position.y += wp->value_44.half[1];
    wp->position_fixed.v.y = wp->position.y << 16;
}

void func_8010CC38(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010CC58(STAGE_OBJ *wp)
{
    D_8011B42C[wp->routine_0](wp);
}

void func_8010CC94(ST0B_OBJ *wp)
{
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->value_348      = 0;
    wp->value_34C      = 0;
    D_80120350         = wp->position_fixed.v;
    wp->pos_354        = wp->position;
    func_8002FFC4(&wp->pos_354, &D_80120350, wp->rotation.y, 0x100, 0, 0);
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->value_44.value        = 0;
    wp->value_48.value        = 0;
    wp->value_6E              = 0;
    wp->value_B0              = 0;
    wp->value_B2              = 0;
    wp->value_78              = 0;
    wp->value_10              = 0;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    func_800322A8(wp, 0, 0);
    func_8010CD90(wp);
}

void func_8010CD90(ST0B_OBJ *wp)
{
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->value_34A           = rand();
    D_8011B438[wp->routine_1](wp);
    if (wp->value_348 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        wp->value_348 &= ~1;
    }
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010CEA0(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010CEC0(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0 = wp->routine_2;
    if (temp_v0 == 0)
    {
        wp->routine_2 = temp_v0 + 1;
        wp->anim_AC   = 0;
    }
}

void func_8010CEE0(ST0B_OBJ *wp)
{
    ST0B_HIT_B *ctl;
    STCOM_SVECTOR *tilt;
    sint16 ground;
    sint32 hit;
    sint32 flag;

    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    ctl                     = ST0B_OBJ_HIT_B(wp);
    ctl->rand_16            = rand();
    D_8011B43C[wp->routine_0]((STAGE_OBJ *)wp, ctl);
    if ((ctl->flags_14 & 0x80) || wp->anim_AC == 1)
    {
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_800322A8(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032488(wp);
        }
    }
    else
    {
        tilt = ST0B_SP_TILT;
        if (wp->anim_prev_AD != wp->anim_AC)
        {
            func_80032304(wp, wp->anim_AC, 0);
        }
        else
        {
            func_80032538(wp);
        }
        tilt->x = wp->rotation.x;
        tilt->z = wp->rotation.x == 0 ? wp->rotation.z : 0;
        Model_parts_mtx_set_y(wp);
    }
    ground        = Obj_ceiling_height_get(wp);
    ctl->value_30 = 0;
    hit           = Obj_map_push_out(wp);
    ctl->value_2C = hit;
    if (!(hit & 0x1000) && wp->position.y == ground)
    {
        ctl->value_30 = 1;
    }
    flag          = ctl->flags_14 & 0x80;
    ctl->value_34 = ground != -1;
    func_800341BC(ST0B_OBJ_POS_180(wp), 0xC0, 0, 0x8000, wp->value_1, &ctl->hit_38, ctl->life_1E | 0x05880000, 0x800000, flag);
    ctl->hit_38 = 0;
}

// One store: retail stores value_64 between anim_prev_AD and anim_AC (after the kind_2 load); here it sinks below routine_1 (score 1; byte_D * 512 gives retail's lb, the early height and life loads its order).
void func_8010D118(ST0B_OBJ *wp, ST0B_HIT_B *ctl)
{
    sint16 life;

    ctl->flags_14 = 2;
    ctl->timer_18 = 0;
    ctl->value_1A = 0;
    ctl->life_1E  = D_80098844[wp->kind_2]->value_A;
    if (wp->u_C.b.byte_C == 1)
    {
        ctl->angle_26 = wp->u_C.b.byte_D * 512;
    }
    else
    {
        ctl->angle_26 = 0;
    }
    ctl->fall_22   = 8;
    ctl->rise_20   = 8;
    ctl->height_28 = wp->u_E.b.byte_E * 200 - 0x6A4;
    ctl->value_2C  = 0;
    ctl->value_30  = 0;
    ctl->value_34  = 0;
    ctl->index_2A  = -1;
    ctl->hit_38    = 0;
    ctl->value_3C  = 0;
    Track_set(ctl->track_40, 0xB, 0);
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    wp->scale.v.pad          = 0x4210;
    wp->anim_prev_AD         = 0xFF;
    *(uint32 *)&wp->value_64 = 0; // a cast word store (0x64 is a pair of halfwords elsewhere)
    wp->anim_AC              = 0;
    life                     = D_80098844[wp->kind_2]->life_B * 16;
    wp->value_78             = (sint32)D_8011B454;
    wp->routine_0            = 1;
    wp->routine_1            = 0;
    wp->routine_2            = 0;
    wp->value_6E             = life;
    wp->value_B0             = life;
    wp->value_B2             = life;
}

void func_8010D288(STAGE_OBJ *wp, ST0B_HIT_B *ctl)
{
    if (ctl->flags_14 & 2)
    {
        func_8010D494(wp, ctl);
    }
    if (!(ctl->flags_14 & 0x80))
    {
        func_8010D558((ST0B_BOAT *)wp, (ST0B_BOAT_CTL *)ctl);
        func_8010D8D0(wp, ctl);
        func_8010DA20((ST0B_OBJ *)wp, ctl);
    }
    switch (wp->anim_AC)
    {
        case 0:
            if (ctl->flags_14 & 4)
            {
                wp->anim_AC = 1;
            }
            if (ctl->flags_14 & 0x100)
            {
                wp->anim_AC = 2;
            }
            break;
        case 1:
            if (wp->value_A7 == -1)
            {
                if (ctl->flags_14 & 4)
                {
                    wp->anim_AC      = 1;
                    wp->anim_prev_AD = 0xFF;
                }
                else
                {
                    wp->anim_AC = 0;
                }
            }
            if (ctl->flags_14 & 0x100)
            {
                wp->anim_AC = 2;
            }
            break;
        case 2:
            if (wp->value_A7 == -1)
            {
                wp->anim_AC = 3;
            }
            break;
    }
    D_8011B448[wp->routine_1](wp, ctl);
    if (ctl->flags_14 & 1)
    {
        switch (wp->routine_1)
        {
            case 0:
                if (ctl->flags_14 & 0x80)
                {
                    wp->routine_1 = 2;
                }
                else
                {
                    wp->routine_1 = 1;
                }
                break;
            case 1:
                if (ctl->flags_14 & 0x80)
                {
                    wp->routine_1 = 2;
                }
                else
                {
                    wp->routine_1 = 0;
                }
                break;
            case 2:
                wp->routine_0 = 2;
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_14 &= ~1;
    }
}

void func_8010D494(STAGE_OBJ *wp, ST0B_HIT_B *hit)
{
    uint32 kind;
    sint32 damage;

    kind   = hit->hit_38;
    damage = kind & 0xFFFFFF;
    if (damage != 0)
    {
        if (kind & 0x18000000)
        {
            wp->life_prev_B2 = wp->life_6E;
            wp->life_6E -= damage;
            if (wp->life_6E <= 0)
            {
                hit->flags_14 = (hit->flags_14 & ~0x3A) | 0x81;
            }
            Sound_call2(0xA0, &wp->position);
            wp->scale.v.pad = 0x7FFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
        hit->flags_14 |= 4;
    }
    else
    {
        hit->flags_14 &= ~4;
    }
}

void func_8010D558(ST0B_BOAT *wp, ST0B_BOAT_CTL *ctl)
{
    if (wp->anim_AC == 1)
    {
        ctl->flags_14 &= ~0x20;
    }
    if (ctl->flags_14 & 0x20)
    {
        if (ctl->flags_14 & 0x40)
        {
            if (!(ctl->u_18.h[1] & 3))
            {
                func_8010D6AC(wp, ctl);
            }
            ctl->u_18.h[1]++;
        }
        else if (wp->rotation.x >= 0x200)
        {
            wp->rotation.x = 0x200;
            ctl->flags_14 |= 0x40;
        }
        else
        {
            wp->rotation.x += 0x20;
        }
    }
    else
    {
        ctl->u_18.h[1] = 0;
        ctl->flags_14 &= ~0x40;
        if (wp->rotation.x > 0)
        {
            wp->rotation.x -= 0x20;
        }
    }
    if (wp->dist_80 < 0x90000)
    {
        if (!(ctl->flags_14 & 0x200))
        {
            ctl->flags_14 |= 0x200;
            Sound_call2(0x150, &wp->position);
        }
    }
    if (wp->dist_80 > 0x240000)
    {
        ctl->flags_14 &= ~0x200;
    }
}

void func_8010D6AC(ST0B_BOAT *wp, ST0B_BOAT_CTL *ctl)
{
    STCOM_FIXED_VECTOR dir;
    STCOM_SVECTOR step;
    STCOM_FIXED_VECTOR ofs;
    ST0B_SPRAY *fx;
    sint32 spawned;

    spawned = 0;
    func_80030058(&dir, wp->rotation.y, 0x600, 0, 0);
    func_80030150(&dir, &step);
    fx = (ST0B_SPRAY *)Open_SHL_WORK();
    if (fx != NULL)
    {
        fx->flags_0 = 3;
        fx->kind_2  = 1;
        fx->value_4 = 0;
        fx->type_F  = 0x24;
        func_80030058(&ofs, wp->rotation.y, 0xC80, 0x1900, 0x480);
        fx->position_fixed = ofs;
        fx->position_fixed.x += wp->position_fixed.x;
        fx->position_fixed.y += wp->position_fixed.y;
        fx->position_fixed.z += wp->position_fixed.z;
        func_80030150(&fx->position_fixed, &fx->position);
        fx->velocity.x   = step.x << 8;
        fx->velocity.y   = 0x6000;
        fx->velocity.z   = step.z << 8;
        fx->velocity.pad = 0;
        fx->accel.z      = 0;
        fx->accel.y      = 0;
        fx->accel.x      = 0;
        spawned          = 1;
    }
    fx = (ST0B_SPRAY *)Open_SHL_WORK();
    if (fx != NULL)
    {
        fx->flags_0 = 3;
        fx->kind_2  = 1;
        fx->value_4 = 0;
        fx->type_F  = 0x24;
        func_80030058(&ofs, wp->rotation.y, 0xC80, 0x1900, -0x480);
        fx->position_fixed = ofs;
        fx->position_fixed.x += wp->position_fixed.x;
        fx->position_fixed.y += wp->position_fixed.y;
        fx->position_fixed.z += wp->position_fixed.z;
        func_80030150(&fx->position_fixed, &fx->position);
        fx->velocity.x   = step.x << 8;
        fx->velocity.y   = 0x6000;
        fx->velocity.z   = step.z << 8;
        fx->velocity.pad = 0;
        fx->accel.z      = 0;
        fx->accel.y      = 0;
        fx->accel.x      = 0;
        spawned          = 1;
    }
    if (spawned)
    {
        Sound_call2(0xD0, &fx->position);
    }
}

void func_8010D8D0(STAGE_OBJ *wp, ST0B_HIT_B *ctl)
{
    sint16 index;

    if (ctl->flags_14 & 0x10)
    {
        wp->rotation.y = (wp->rotation.y + 0x20) & 0xFFF;
        if (wp->rotation.z > -0x80)
        {
            wp->rotation.z -= 8;
        }
        ctl->index_2A = -1;
        return;
    }
    else if (ctl->flags_14 & 8)
    {
        wp->rotation.y = (wp->rotation.y - 0x20) & 0xFFF;
        if (wp->rotation.z < 0x80)
        {
            wp->rotation.z += 8;
        }
        ctl->index_2A = -1;
        return;
    }
    index = ctl->index_2A;
    if (index == -1)
    {
        if (wp->rotation.z != 0)
        {
            if (wp->rotation.z > 0)
            {
                wp->rotation.z -= 8;
            }
            else
            {
                wp->rotation.z += 8;
            }
        }
        if (wp->rotation.z == 0)
        {
            ctl->index_2A = (ctl->rand_16 >> 4) & 3;
        }
    }
    else
    {
        wp->rotation.z = D_8011B460[index % 36];
        ctl->index_2A  = (ctl->index_2A + 1) & 0x7FFF;
    }
}

// retail loads the height with lhu and sign-extends it after the join; ours loads it with lh (score 3)
void func_8010DA20(ST0B_OBJ *wp, ST0B_HIT_B *ctl)
{
    sint16 h;

    if (ST0B_ABS(wp->position.x - 0x1200) < 0x2C00 && ST0B_ABS(wp->position.z + 0x600) < 0x2A00)
    {
        h = ctl->height_28;
    }
    else
    {
        h = -2000;
    }
    if (wp->position.y > h)
    {
        if (ctl->rise_20 < 0x20)
        {
            ctl->rise_20 += 8;
        }
        ctl->fall_22 = 8;
        wp->position.y -= ctl->rise_20;
        if (wp->position.y < h)
        {
            wp->position.y = h;
        }
    }
    else if (wp->position.y < h)
    {
        if (ctl->fall_22 < 0x20)
        {
            ctl->fall_22 += 8;
        }
        ctl->rise_20 = 8;
        wp->position.y += ctl->fall_22;
        if (wp->position.y > h)
        {
            wp->position.y = h;
        }
    }
    else
    {
        ctl->fall_22 = 8;
        ctl->rise_20 = 8;
    }
    wp->position_fixed.v.y = wp->position.y << 16;
}

sint32 func_8010DB7C(STAGE_OBJ *wp)
{
    if (STCOM_ABS(wp->rotation.y - Angle_xz_vector(&wp->position_fixed, &Player_work.position_fixed)) < 0x50)
    {
        return 1;
    }
    return 0;
}

void func_8010DC28(STAGE_OBJ *wp, ST0B_HIT_B *ctl)
{
    STCOM_PL_WORK *pl;
    sint32 arrived;

    pl = &Player_work;
    if (wp->routine_2 == 0)
    {
        ctl->timer_18 = (sint16)ctl->rand_16 % 40 + 0x5A;
        wp->routine_2++;
    }
    arrived = func_8003648C(ctl->track_40, wp);
    Obj_pos_set(wp, 0x300, 0, 0);
    if (ctl->angle_26 >= 0)
    {
        ctl->angle_26 -= 0x30;
    }
    if (arrived != 0)
    {
        ctl->flags_14 |= 0x20;
    }
    else
    {
        ctl->flags_14 &= ~0x20;
        if (wp->u_C.b.byte_C == 2 && ctl->timer_18 < 0 && wp->u_E.b.byte_F == 0)
        {
            if (Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) > 0)
            {
                ctl->flags_14 |= 0x11;
            }
            else
            {
                ctl->flags_14 |= 9;
            }
        }
    }
    if (wp->u_C.b.byte_C == 1 && ctl->angle_26 < 0)
    {
        ctl->flags_14 = (ctl->flags_14 & ~0x20) | 9;
    }
    ctl->timer_18--;
}

void func_8010DDD8(STAGE_OBJ *wp, ST0B_HIT_B *ctl)
{
    if (wp->routine_2 == 0)
    {
        if (wp->u_C.b.byte_C == 1)
        {
            ctl->timer_18 = 0x40;
        }
        else
        {
            ctl->timer_18 = (ctl->rand_16 & 0x1F) + 0x40;
        }
        wp->routine_2++;
    }
    Obj_pos_set(wp, 0x120, 0, 0);
    if (wp->u_C.b.byte_C == 1 || wp->u_E.b.byte_F == 1)
    {
        Track_stop(ctl->track_40);
        if (ctl->timer_18 == 0)
        {
            wp->u_C.b.byte_C = 0;
            ctl->flags_14    = (ctl->flags_14 & ~0x18) | 1;
        }
    }
    else if (wp->u_C.b.byte_C == 2)
    {
        func_8003648C(ctl->track_40, wp);
        if (func_8010DB7C(wp) != 0 || ctl->timer_18 == 0)
        {
            ctl->flags_14 = (ctl->flags_14 & ~0x18) | 1;
        }
    }
    ctl->timer_18--;
}

void func_8010DEF4(STAGE_OBJ *wp, ST0B_HIT_B *ctl)
{
    STCOM_EFFECT *ep;
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR pos;

    switch (wp->routine_2)
    {
        case 0:
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0         = 5;
                ep->kind_2          = 0x80;
                ep->variant_3       = 0x41;
                ep->sprite.position = wp->position;
            }
            Sound_call2(0xA1, &wp->position);
            ctl->timer_18 = 0x78;
            ctl->speed_24 = 8;
            ctl->count_1C = 0;
            ctl->flags_14 |= 0x100;
            func_80030058(&fixed, wp->rotation.y, 0x3C00, 0, 0);
            fixed.x += wp->position_fixed.v.x;
            fixed.z += wp->position_fixed.v.z;
            func_80030150(&fixed, &pos);
            wp->routine_2++;
            break;
        case 1:
            if (ctl->count_1C == 0xA)
            {
                ctl->speed_24 = 8;
            }
            if (ctl->count_1C == 0x1E)
            {
                ctl->speed_24 = 0xC;
            }
            else if (ctl->count_1C == 0x32)
            {
                ctl->speed_24 = 0x10;
            }
            if (ctl->count_1C < 0x3C)
            {
                Obj_pos_set(wp, 0x100, 0, 0);
            }
            wp->position.y += ctl->speed_24;
            wp->position_fixed.v.y = wp->position.y << 16;
            if ((ctl->value_2C & 0x1000) || ctl->value_30 == 1)
            {
                ctl->timer_18 = 0;
                wp->routine_2++;
            }
            break;
        case 2:
            if (ctl->value_34 == 1)
            {
                if (!(ctl->timer_18 & 3))
                {
                    ep = func_80031618();
                    if (ep != NULL)
                    {
                        ep->flags_0           = 5;
                        ep->kind_2            = 0x80;
                        ep->variant_3         = 0x42;
                        ep->sprite.position.x = wp->position.x + (rand() & 0x3F);
                        ep->sprite.position.y = wp->position.y + (rand() & 0x3F);
                        ep->sprite.position.z = wp->position.z + (rand() & 0x3F);
                    }
                    Sound_call2(0xA1, &ep->sprite.position);
                }
            }
            else if (ctl->timer_18 == 0)
            {
                ep = func_80031618();
                if (ep != NULL)
                {
                    ep->flags_0           = 5;
                    ep->kind_2            = 0x80;
                    ep->variant_3         = 0x42;
                    ep->sprite.position.x = wp->position.x + (rand() & 0x3F);
                    ep->sprite.position.y = wp->position.y + (rand() & 0x3F);
                    ep->sprite.position.z = wp->position.z + (rand() & 0x3F);
                }
                ctl->effect_4 = func_80031618();
                if (ctl->effect_4 != NULL)
                {
                    ctl->effect_4->flags_0           = 5;
                    ctl->effect_4->kind_2            = 0x10;
                    ctl->effect_4->variant_3         = 5;
                    ctl->effect_4->sprite.position.x = wp->position.x;
                    ctl->effect_4->sprite.position.y = 0;
                    ctl->effect_4->sprite.position.z = wp->position.z;
                }
                Sound_call2(0x14D, &ep->sprite.position);
            }
            if (ctl->timer_18 == 2)
            {
                wp->flags_0 &= ~2;
            }
            else if (ctl->timer_18 == 7)
            {
                wp->routine_2++;
            }
            ctl->timer_18++;
            break;
        case 3:
            ctl->flags_14 |= 1;
            break;
    }
    if (wp->routine_2 < 2)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0         = 1;
            ep->kind_2          = 0xB;
            ep->variant_3       = 3;
            ep->timer_E         = 0x14;
            ep->value_C         = 0;
            ep->value_D         = 0;
            ep->value_F         = 8;
            ep->sprite.pos_8[0] = wp->position.x;
            ep->sprite.pos_8[1] = wp->position.y;
            ep->sprite.pos_8[2] = wp->position.z;
            ep->routine_1       = ctl->rand_16 & 0xF;
        }
    }
    ctl->count_1C++;
}

void func_8010E34C(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_8010E36C(STAGE_OBJ *wp)
{
    sint16 height[5] = {-2197, -3000, -3400, -2800, -3500};

    if (wp->routine_1 == 0)
    {
        func_8010E574(wp);
    }
    D_8011B4A8[wp->u_C.b.byte_C](wp);
    if (wp->u_C.b.byte_C != 0)
    {
        if (wp->u_C.b.byte_D != 0)
        {
            wp->position.y -= wp->u_E.b.byte_E;
            wp->position.z -= wp->u_E.b.byte_F;
        }
        wp->position.y = height[wp->u_C.b.byte_C] + ((D_800BBCF8[(wp->routine_3 + wp->u_C.b.byte_C * 7) & 0x3F] << 8) >> 16);
    }
    else if (wp->u_C.b.byte_D != 0)
    {
        wp->position.y -= wp->u_E.b.byte_E;
        wp->position.z -= wp->u_E.b.byte_F;
    }
    else
    {
        wp->position.y = height[0] + ((D_800BBCF8[wp->routine_3 & 0x3F] << 8) >> 16);
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->routine_3++;
    func_80032488(wp);
}

void func_8010E574(STAGE_OBJ *wp)
{
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->flags_0 |= 2;
    Model_work_init(wp, &wp->variant_3);
    func_800322A8(wp, 0, 0);
    wp->u_C.b.byte_D = 0;
    wp->routine_2    = 0;
    wp->routine_3    = 0;
    wp->routine_1++;
}

void func_8010E5F0(STAGE_OBJ *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        if (Scene_work.u_8.byte[0] == 2)
        {
            wp->u_C.b.byte_D++;
        }
        else
        {
            wp->u_C.b.byte_D = 0;
        }
        wp->routine_2++;
    }
    if (scene->u_8.byte[0] == 2 && scene->value_10 == 0xDE)
    {
        wp->u_C.b.byte_D = 0;
    }
}

void func_8010E698(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
    if (Scene_work.u_8.byte[0] == 2)
    {
        if (Scene_work.value_10 == 0x64)
        {
            wp->u_C.b.byte_D++;
        }
        else if (Scene_work.value_10 == 0x17C)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
}

void func_8010E72C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
    if (Scene_work.u_8.byte[0] == 2)
    {
        if (Scene_work.value_10 == 0x64)
        {
            wp->u_C.b.byte_D++;
        }
        else if (Scene_work.value_10 == 0x118)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
}

void func_8010E7C0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
    if (Scene_work.u_8.byte[0] == 2)
    {
        if (Scene_work.value_10 == 0x1E)
        {
            wp->u_C.b.byte_D++;
        }
        else if (Scene_work.value_10 == 0x8C)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
}

void func_8010E854(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_2++;
    }
}
