#include "common.h"
#include "st0d.h"

void func_80107DDC(ST0D_VILLAGER *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->routine_0 == 0)
    {
        func_80107EF8(wp, &wp->talk);
    }
    else
    {
        func_80108040(wp, &wp->talk);
    }
    func_80051B68(wp, 1, -1, 0);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
}

void func_80107EF8(ST0D_VILLAGER *wp, ST0D_TALK *talk)
{
    wp->flags_0 |= 2;
    if (wp->value_C == 0)
    {
        Model_work_init(wp, &wp->variant_3);
    }
    else
    {
        func_8002F9EC(wp, (sint32)&wp->variant_3);
    }
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    wp->position.y       = func_80048E6C(wp);
    wp->position_fixed.y = wp->position.y << 16;
    wp->data_10          = D_8010E41C;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    wp->anim_AC          = 0;
    wp->anim_prev_AD     = 0xFF;
    talk->msg_0          = D_8010E428[wp->value_D];
    talk->flag_on_4      = D_8010E43C[wp->value_D];
    talk->flag_8         = D_8010E47C[wp->value_D];
    talk->first_C        = 1;
    talk->shot_10        = D_8010E468[wp->value_D];
    wp->routine_1        = 0;
    wp->routine_0++;
}

void func_80108040(ST0D_VILLAGER *wp, ST0D_TALK *talk)
{
    STCOM_PL_WORK *pl;
    STCOM_FIXED_VECTOR cam;
    sint16 turn;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (pl->target_184 == wp)
            {
                wp->turn_64    = STCOM_ABS(Muku(&wp->position, &pl->position, wp->rotation.y, 0x800)) >> 3;
                pl->target_184 = NULL;
                pl->flags_0 &= ~2;
                pl->flags_bd |= 0x80;
                cam.x = wp->value_180.x;
                cam.y = wp->value_180.y - 0x20;
                cam.z = wp->value_180.z;
                func_80039FAC(&cam, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
                wp->routine_1++;
            }
            break;
        case 1:
            turn           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn == 0 && func_8003A13C() == 0)
            {
                if (talk->msg_0 != 0x7FFFFFFF)
                {
                    MojiTaskExec2(0, talk->msg_0);
                    wp->anim_AC = 8;
                }
                wp->routine_1++;
            }
            break;
        case 2:
            if (talk->msg_0 != 0x7FFFFFFF)
            {
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                switch (wp->value_E)
                {
                    case 0:
                        func_80039E18();
                        wp->routine_1 = 4;
                        break;
                    case 1:
                        func_80017C30(10);
                        wp->routine_1 = 3;
                        break;
                    case 2:
                        if (talk->flag_8 != 0x7FFFFFFF)
                        {
                            if (Sce_flag_test(talk->flag_8))
                            {
                                func_80017C30(10);
                                wp->routine_1 = 3;
                                break;
                            }
                            talk->first_C = 0;
                        }
                        func_80039E18();
                        wp->routine_1 = 4;
                        break;
                }
            }
            else
            {
                switch (wp->value_E)
                {
                    case 0:
                        func_80039E18();
                        wp->routine_1 = 4;
                        break;
                    case 1:
                        func_80017C30(10);
                        wp->routine_1 = 3;
                        break;
                    case 2:
                        if (talk->flag_8 != 0x7FFFFFFF)
                        {
                            if (Sce_flag_test(talk->flag_8))
                            {
                                func_80017C30(10);
                                wp->routine_1 = 3;
                                break;
                            }
                            talk->first_C = 0;
                        }
                        func_80039E18();
                        wp->routine_1 = 4;
                        break;
                }
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                func_80039E18();
                wp->routine_1++;
            }
            break;
        case 4:
            if (func_8003A13C() == 0)
            {
                pl->flags_bd &= ~0x80;
                pl->flags_0 |= 2;
                wp->routine_1++;
            }
            break;
        case 5:
            if (talk->flag_on_4 != 0x7FFFFFFF)
            {
                if (talk->flag_8 != 0x7FFFFFFF)
                {
                    if (Sce_flag_test(talk->flag_8))
                    {
                        Sce_flag_on(talk->flag_on_4);
                    }
                }
                else
                {
                    Sce_flag_on(talk->flag_on_4);
                }
            }
            if (talk->first_C == 1)
            {
                if (talk->shot_10 != (ST0D_CAM_SHOT *)0x7FFFFFFF)
                {
                    STAGE_CAM_REQ_PTR->mode_C   = talk->shot_10->value_8;
                    STAGE_CAM_REQ_PTR->value_E  = talk->shot_10->value_9;
                    STAGE_CAM_REQ_PTR->value_F  = talk->shot_10->value_A;
                    STAGE_CAM_REQ_PTR->x_0      = talk->shot_10->x_0;
                    STAGE_CAM_REQ_PTR->y_2      = talk->shot_10->y_2;
                    STAGE_CAM_REQ_PTR->z_4      = talk->shot_10->z_4;
                    STAGE_CAM_REQ_PTR->angle_A  = talk->shot_10->value_6;
                    STAGE_CAM_REQ_PTR->value_11 = 0xFF;
                    STAGE_CAM_REQ_PTR->value_D  = 0;
                    STAGE_CAM_REQ_PTR->value_10 = 2;
                }
                func_80031824(wp);
            }
            else
            {
                talk->first_C = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

ST0D_GRID_OBJ *func_80108468(STAGE_OBJ *owner, uint8 rows, STCOM_SVECTOR *origin)
{
    ST0D_GRID_OBJ *wp;
    ST0D_GRID6 *grid;
    ST0D_CELL *cell;
    uint8 i;
    uint8 j;
    wp = (ST0D_GRID_OBJ *)func_80031418();
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
    wp->u_C.word        = 0;
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

ST0D_GRID_OBJ *func_801085AC(STAGE_OBJ *owner, sint8 variant, STCOM_SVECTOR *origin)
{
    ST0D_GRID_OBJ *wp;
    ST0D_GRID6 *grid;
    ST0D_CELL *cell;
    uint8 i;
    uint8 j;
    wp = (ST0D_GRID_OBJ *)func_80031418();
    if (wp == NULL)
    {
        return NULL;
    }
    grid          = &wp->grid;
    wp->flags_0   = 1;
    wp->kind_2    = 0x12;
    wp->value_4   = 0;
    wp->variant_3 = variant;
    wp->u_C.word  = 0;
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

void func_80108758(uint8 *wp, sint32 value)
{
    wp[0x89] = value & 0x3F;
}

void func_80108764(STAGE_OBJ *wp)
{
    D_8010E490[wp->variant_3](wp, &wp->model_88);
}

void func_801087A0(STAGE_OBJ *wp, ST0D_GRID6 *grid)
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
            func_80108D10(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
}

void func_801088C8(STAGE_OBJ *wp, ST0D_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST0D_CELL *cell;

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
                func_80108D10(grid, i, j);
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

void func_80108A8C(STAGE_OBJ *wp, ST0D_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;
    uint8 on;
    ST0D_CELL *cell;

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
                func_80108D10(grid, i, j);
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

void func_80108C48(STAGE_OBJ *wp, ST0D_GRID6 *grid)
{
    uint8 i;
    uint8 j;
    uint8 n;

    for (i = 0; i < 6; i++)
    {
        n = grid->count_4[i] >> 3;
        for (j = 0; j < n; j++)
        {
            func_80108D10(grid, i, j);
        }
        if (grid->count_4[i] < 0x40)
        {
            grid->count_4[i]++;
        }
    }
    grid->frame_C++;
}

void func_80108D10(ST0D_GRID6 *grid, uint8 row, uint8 col)
{
    ST0D_CELL *cell;

    cell = &grid->cell_14[row][col];
    D_8010E4A0[grid->mode_0](grid, cell);
    if ((grid->mask_1 >> row) & 1)
    {
        D_8010E4B4[grid->kind_B](cell, grid->value_10);
    }
}

void func_80108DBC(ST0D_GRID6 *grid, ST0D_CELL *cell)
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

void func_80108EC4(ST0D_GRID6 *grid, ST0D_CELL *cell)
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

void func_80108FEC(ST0D_GRID6 *grid, ST0D_CELL *cell)
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

void func_80109114(ST0D_GRID6 *grid, ST0D_CELL *cell)
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

void func_80109204(ST0D_GRID6 *grid, ST0D_CELL *cell)
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

void func_80109324(ST0D_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;

    p          = func_8002D464();
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

void func_801093C8(ST0D_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    u          = D_8010E4C0[cell->frame_6 >> 2];
    p          = func_8002D464();
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

void func_80109498(ST0D_CELL *cell, sint32 color)
{
    STCOM23_PACKET *p;
    sint32 u;

    if (cell->state_4 < 2)
    {
        u          = D_8010E4C0[cell->frame_6 >> 2];
        p          = func_8002D464();
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

void func_8010957C(ST0D_BOBBER *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    if (wp->routine_0 == 0)
    {
        func_8010964C(wp, &wp->bob);
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
    }
    else
    {
        func_80109714(wp, &wp->bob);
        func_80032488(wp);
    }
}

void func_8010964C(ST0D_BOBBER *wp, ST0D_BOB *bob)
{
    wp->flags_0 |= 2;
    func_8002F9EC(wp, 0);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    wp->value_78       = 0;
    bob->speed_0       = wp->speed_C * 10;
    bob->height_2      = wp->height_D * 10;
    bob->period_4      = wp->period_E * 10;
    bob->turn_6        = (sint8)wp->turn_F;
    bob->phase_8       = 0;
    bob->base_A        = wp->position.y;
}

void func_80109714(ST0D_BOBBER *wp, ST0D_BOB *bob)
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

void func_80109834(STAGE_OBJ *wp)
{
    uint8 temp_a1;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        Model_work_init(wp, NULL);
        wp->scale.words[0] = 0x02000200;
        wp->scale.words[1] = 0x42100200;
        wp->value_78       = 0;
        wp->anim_AC        = 0;
        wp->anim_prev_AD   = 0xFF;
        wp->routine_0++;
    }
    temp_a1 = wp->anim_AC;
    if (temp_a1 != wp->anim_prev_AD)
    {
        func_800322A8(wp, temp_a1, 0);
        return;
    }
    func_80032488(wp);
}

void func_80109944(ST0D_MARKER *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->position.x        = -0x4B0;
    wp->value_64          = 0;
    wp->rotation.words[0] = 0;
    wp->rotation.words[1] = 0;
    wp->value_44          = 0;
    wp->value_48          = 0;
    wp->value_64          = 0;
    wp->value_70          = 0;
    wp->value_74          = 0;
    wp->position.z        = -0xED;
    wp->position.y        = func_80048E6C(wp);
    wp->scale.words[0]    = 0x02000200;
    wp->rotation.v.y      = 0xC00;
    wp->scale.words[1]    = 0x200;
    wp->scale.v.pad       = 0x4210;
    wp->rotation.v.x      = 0;
    wp->rotation.v.z      = 0;
    wp->anim_360          = 0;
    wp->position_fixed.x = wp->position_fixed_prev.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = wp->position.y << 16;
    func_800322A8(wp, 0, 0);
    wp->value_350 = 0;
    wp->routine_0++;
}

void func_80109A38(ST0D_MARKER *wp)
{
    if (D_800C0C2A & 0x2000)
    {
        if (++wp->anim_360 >= 4)
        {
            wp->anim_360 = 0;
        }
        func_800322A8(wp, wp->anim_360, 0);
        return;
    }
    if (D_800C0C26 & 0x10)
    {
        wp->position.x -= 10;
    }
    if (D_800C0C26 & 0x40)
    {
        wp->position.x += 10;
    }
    if (D_800C0C26 & 0x80)
    {
        wp->position.z -= 10;
    }
    if (D_800C0C26 & 0x20)
    {
        wp->position.z += 10;
    }
    if (D_800C0C26 & 0x400)
    {
        wp->position.y -= 10;
    }
    if (D_800C0C26 & 0x100)
    {
        wp->position.y += 10;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->position_fixed.y = wp->position.y << 16;
    func_80032488(wp);
}

void func_80109BB0(STAGE_OBJ *wp)
{
    D_8010E4D4[wp->routine_0](wp);
}
