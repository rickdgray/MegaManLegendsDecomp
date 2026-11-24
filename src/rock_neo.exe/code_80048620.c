#include "common.h"
#include "code_80048620.h"
#include "stage.h"
#include "player.h"
#include "scene.h"
#include "game.h"
#include "debug.h"
#include "code_8004324C.h"
#include "code_80037FB4.h"
#include "sound.h"

// Pool small data (reached through $gp; the assembly's definition is the one linked).
VECTOR D_80098AC0; // 16.16 position func_80052674 places on a solid's floor

// Called only from this file
void func_80048A9C(SCENE_WORK *sw);
sint32 func_80052674(MODEL_WORK *obj, MODEL_WORK *solid, VECTOR *pos, sint32 keep, sint32 slide);
sint32 map_push_out(SVECTOR *pos, SVECTOR *old, sint32 no_step, sint32 slide);
sint32 solid_push_out(MODEL_WORK *solid, VECTOR *now, VECTOR *cur, VECTOR *old, sint32 keep, sint32 slide);
void func_800536B0(MODEL_WORK *obj, VECTOR *pos, VECTOR *old, sint32 part);
sint32 front_hit_search(MODEL_WORK *obj, VECTOR *ofs, FRONT_HIT *out);
sint32 func_8004B1E0(SVECTOR *pos, sint32 keep_empty);
sint32 floor_height_get(SVECTOR *pos, VECTOR *ofs, sint32 kind);
void slope_fit(sint16 *box, uint16 kind);
sint32 block_push_out(SVECTOR *pos, SVECTOR *prev, sint32 mode);
sint32 func_80050808(SVECTOR *v);
sint32 func_800508BC(SVECTOR *v);
sint32 func_80050970(SVECTOR *v);
sint32 func_800497CC(SVECTOR *pos, HIT_ENT *ent, sint32 dir, sint32 kind);
sint32 func_8004BDC8(sint16 *box, uint16 kind, sint32 test);
sint32 func_8004F44C(SVECTOR *pos, SVECTOR *prev, sint32 mode);
sint32 func_8004F8BC(SVECTOR *pos, SVECTOR *prev, sint32 side);
sint32 func_8004FBE8(SVECTOR *pos, SVECTOR *prev, sint32 side);
sint32 func_8004FF14(SVECTOR *pos, sint32 corner);
sint32 func_800501E8(SVECTOR *pos, sint32 corner);
sint32 func_80051970(PL_WORK *pl);
sint32 func_800519E4(MAP_EXIT *exit);
sint32 func_80051A78(MAP_EXIT *exit);
sint32 func_80051F08(MODEL_WORK *solid, MODEL_WORK *obj, MODEL_WORK *owner, sint32 part, uint32 hit, sint32 keep);
sint32 obj_solid_push_out(MODEL_WORK *solid, MODEL_WORK *obj, sint32 part, sint32 keep);

// Scene step (routine_5): sets the player's flags 3 and closes the player's shots, waits for
// func_80042238, then starts the camera script for the area entry's facing (D_8008A9D4) and the
// event table D_8008A9F4, and advances routine_4.
void func_80048620(SCENE_WORK *sw)
{
    AREA_ENTRY *entry;

    entry = &D_800C3558;
    switch (sw->routine_5)
    {
        case 0:
            Player_work->flags_6 |= 3;
            Obj_work_flag_change(WORK_PL_SHL, WORK_KILL);
            sw->routine_5++;
            // fall through
        case 1:
            if (func_80042238(&Player_work[0]) != 0)
            {
                Sce_camera_work.arg_C0 = D_8008A9D4[entry->ang_y_10 >> 10];
                sw->ev_ptr_A4          = D_8008A9F4;
                sw->field_0C           = 0;
                sw->routine_5          = 0;
                sw->routine_4++;
            }
            break;
    }
}

// Scene step (routine_5), 14 states: puts the player in routine_8 3 with the saved position 0x40
// ahead of D_800C3558.pos_00 (camera reset there), waits through func_80048A9C, sets
// D_800C356C to 1 and waits for 2, then 3 and waits for 0, then does the same at D_800C3558.pos
// with the camera script for its facing (D_8008A9E4). Scene flag 0x7B1 is on around each
// func_80048A9C wait, and the steps hold while flag 0x7B2 is set; at the end flag 0x7B0 is
// cleared, 0x7B3 set, and routine_4 advances.
void func_80048704(SCENE_WORK *sw)
{
    PL_WORK *pl;
    AREA_ENTRY *entry;

    pl    = &Player_work[0];
    entry = &D_800C3558;
    switch (sw->routine_5)
    {
        case 0:
            func_8001E6C0(entry->pos_00.vx, entry->pos_00.vy, entry->pos_00.vz);
            pl->routine_8   = 3;
            pl->routine_9   = 1;
            pl->svec_438.vx = entry->pos_00.vx + ((rsin(entry->ang_y_10) << 6) >> 12);
            pl->svec_438.vy = pl->pos.vy;
            pl->svec_438.vz = entry->pos_00.vz + ((rcos(entry->ang_y_10) << 6) >> 12);
            pl->ang_440.vx  = 0;
            pl->ang_440.vz  = 0;
            pl->unk448      = 0x30;
            pl->pos_428.vx  = pl->svec_438.vx << 16;
            pl->pos_428.vy  = pl->svec_438.vy << 16;
            pl->pos_428.vz  = pl->svec_438.vz << 16;
            pl->ang_440.vy  = entry->ang_y_10;
            sw->routine_5++;
            break;
        case 2:
            if (Sce_flag_test(0x7B2) == 0)
            {
                pl->routine_9++;
                sw->step_0A = 0;
                sw->routine_5++;
            }
            break;
        case 5:
            if (Sce_flag_test(0x7B2) == 0)
            {
                D_800C356C = 1;
                D_800C3571 = 10;
                D_800C3570 = 2;
                sw->routine_5++;
            }
            break;
        case 6:
            if (D_800C356C == 2)
            {
                sw->routine_5++;
            }
            break;
        case 7:
            if (Sce_flag_test(0x7B2) == 0)
            {
                D_800C356C = 3;
                sw->routine_5++;
            }
            break;
        case 8:
            if (D_800C356C == 0)
            {
                Sce_camera_work.arg_C0 = D_8008A9E4[entry->ang_y >> 10];
                func_8001E6C0(entry->pos.vx, entry->pos.vy, entry->pos.vz);
                pl->routine_8   = 3;
                pl->routine_9   = 1;
                pl->svec_438.vx = entry->pos.vx + ((rsin(entry->ang_y) << 6) >> 12);
                pl->svec_438.vy = entry->pos.vy - 1;
                pl->svec_438.vz = entry->pos.vz + ((rcos(entry->ang_y) << 6) >> 12);
                pl->ang_440.vx  = 0;
                pl->ang_440.vz  = 0;
                pl->unk448      = 0x30;
                pl->pos_428.vx  = pl->svec_438.vx << 16;
                pl->pos_428.vy  = pl->svec_438.vy << 16;
                pl->pos_428.vz  = pl->svec_438.vz << 16;
                pl->ang_440.vy  = entry->ang_y;
                sw->routine_5++;
            }
            break;
        case 1:
        case 9:
            sw->routine_5++;
            Sce_flag_on(0x7B1);
            break;
        case 10:
            if (Sce_flag_test(0x7B2) == 0)
            {
                pl->routine_9++;
                sw->routine_5++;
            }
            break;
        case 3:
        case 11:
            func_80048A9C(sw);
            break;
        case 4:
        case 12:
            Sce_flag_off(0x7B1);
            sw->routine_5++;
            break;
        case 13:
            if (Sce_flag_test(0x7B2) == 0)
            {
                Sce_flag_off(0x7B0);
                Sce_flag_on(0x7B3);
                sw->routine_5 = 0;
                sw->routine_4++;
            }
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80048A40(WORK_48 *wp)
{
    func_80042314(&Player_work[0]);
    *(uint32 *)&Player_work[0].routine_8 = 0;
    D_800A395C                           = 1;
    func_80039820();
    Sce_flag_off(0x7B3);
    wp->routine_0 = 0;
}

// Feeds the player's pad bits to D_800C0F96 until timer_10 passes 0x24 frames (steps 0-1) or the
// stage's D_8008AA04 count (steps 2-3), then advances routine_5.
void func_80048A9C(SCENE_WORK *sw)
{
    PL_WORK *pl;

    pl            = &Player_work[0];
    D_800C0F96[0] = 0;
    switch (sw->step_0A)
    {
        case 0:
            sw->time_0B = D_8008AA04[Game_work.stage_no];
            Player_work[0].flags_BD |= 0x20;
            sw->step_0A++;
            // fall through
        case 1:
            D_800C0F96[0] = pl->keys_124[0];
            if (sw->timer_10 >= 0x25)
            {
                sw->routine_5++;
                sw->step_0A++;
                D_800C0F96[0] = 0;
                pl->flags_BD  = (pl->flags_BD & ~0x20) | 0x40;
            }
            break;
        case 2:
            Player_work[0].flags_BD |= 0x20;
            sw->step_0A++;
            // fall through
        case 3:
            D_800C0F96[0] = pl->keys_124[0];
            if (sw->time_0B < sw->timer_10)
            {
                sw->routine_5++;
                sw->step_0A++;
                D_800C0F96[0] = 0;
                pl->flags_BD  = (pl->flags_BD & ~0x20) | 0x40;
            }
            break;
    }
}

void func_80048BE4(void)
{
}

// The map cell index of pos (x + z * Map_w), or 0 outside the map window.
sint32 map_cell_index(SVECTOR *pos)
{
    sint32 x;
    sint32 z;

    if ((uint32)(x = ((pos->vx + 0x8000) >> 9) - Map_org_x) >= Map_w || (uint32)(z = ((pos->vz + 0x8000) >> 9) - Map_org_y) >= Map_h)
    {
        return 0;
    }
    return x + z * Map_w;
}

sint32 Map_cell_get(SVECTOR *pos)
{
    sint32 x;
    sint32 z;

    if ((uint32)(x = ((pos->vx + 0x8000) >> 9) - Map_org_x) >= Map_w || (uint32)(z = ((pos->vz + 0x8000) >> 9) - Map_org_y) >= Map_h)
    {
        return 0;
    }
    // Row offset added last: Map_cells[x + z * Map_w] adds the products in the other order.
    return (Map_cells + x)[z * Map_w];
}

sint32 func_80048CEC(sint32 index)
{
    return Map_cells[index];
}

// Map_cell_get on room map's map (Stage_map_tbl) instead of the current map window.
sint32 Stage_map_cell_get(sint32 map, SVECTOR *pos)
{
    sint32 x;
    sint32 z;
    STAGE_MAP *m;

    m = &Stage_map_tbl[map];
    if ((uint32)(x = ((pos->vx + 0x8000) >> 9) - m->x0) >= m->w || (uint32)(z = ((pos->vz + 0x8000) >> 9) - m->z0) >= m->h)
    {
        return 0;
    }
    return (m->cells + x)[z * m->w];
}

sint32 Map_area_check(SVECTOR *pos)
{
    if ((uint32)(((pos->vx + 0x8000) >> 9) - Map_org_x) >= Map_w || (uint32)(((pos->vz + 0x8000) >> 9) - Map_org_y) >= Map_h)
    {
        return -1;
    }
    return 0;
}

// The low 12 bits of pos.pad of the map block under pos, or 0 outside the map or on cell 0.
sint32 func_80048E18(SVECTOR *pos)
{
    sint32 cell;

    cell = Map_cell_get(pos);
    if (cell > 0)
    {
        return Map_blocks[cell].pos.pad & 0xFFF;
    }
    return 0;
}

// The lowest ceiling over obj (func_80048EA4 with its box and the height it moved by).
sint32 Obj_ceiling_height_get(MODEL_WORK *obj)
{
    return func_80048EA4(&obj->pos, obj->hit_78, obj->pos.vy - obj->old.vy, obj->kind_1);
}

// The lowest ceiling over pos among the map blocks around it (func_8004B1E0), with the box ent
// (func_8004B3C0): the smallest y0 (fitted by slope_fit) of the STG_HITs whose area holds pos and
// whose top is above pos, or, when dy >= 0, above the lowest ceiling found so far; repeated until
// it no longer changes. On pos's own empty cell, the complement of its step height. Hits whose
// flags bit 15 disagrees with kind's func_8002FE74 are skipped. Returns it plus ent's max_A.
sint32 func_80048EA4(SVECTOR *pos, HIT_ENT *ent, sint32 dy, sint32 kind)
{
    sint16 box[6];
    SVECTOR org;
    sint32 count;
    sint32 prev;
    sint32 best;
    sint32 skip;
    sint32 n;
    sint32 val;
    sint32 lim;
    sint32 left;
    sint32 top;
    uint32 type;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    best       = 0x7FFF;
    D_1F8000C0 = *pos;
    count      = func_8004B1E0(&D_1F8000C0, 0);
    func_8004B3C0((VECTOR *)ent);
    skip = (func_8002FE74(kind) == 0) << 15;
    do
    {
        prev = best;
        n    = count;
        while (n-- != 0)
        {
            val = func_80048CEC(D_1F800118[n]);
            if (val <= 0)
            {
                if (D_1F800118[n] == map_cell_index(&D_1F8000C0))
                {
                    lim = ~((val & 0x1F00) >> 1) - D_1F800124_box.max_A;
                    if (lim < best)
                    {
                        best = lim;
                    }
                }
            }
            else
            {
                block = &Map_blocks[val];
                model = (STG_MODEL *)(block->model & 0xFFFFFF);
                // The do/while (0)s are needed: they rank area above left in GCC's register
                // choice (references weigh by loop depth).
                if (block->pos.pad & 0xFFF)
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                area = model->areas;
                            } while (0);
                        } while (0);
                    } while (0);
                }
                else
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                area = model->areas_0;
                            } while (0);
                        } while (0);
                    } while (0);
                }
                org.vx = block->pos.vx;
                org.vy = block->pos.vy;
                org.vz = block->pos.vz;
                for (; area->hits != NULL; area++)
                {
                    do
                    {
                        do
                        {
                            box[0] = org.vx + area->x0;
                            box[1] = org.vx + area->x1;
                            box[2] = org.vz + area->z0;
                            box[3] = org.vz + area->z1;
                        } while (0);
                        hit = area->hits;
                    } while (0);
                    if ((type = hit->kind) < 0x100 && Block_test_tbl[(type & 0xF0) >> 4](box, type) != 0)
                    {
                        left = area->count;
                        do
                        {
                            if (!(hit->flags & (skip ^ 0x8000)))
                            {
                                box[4] = org.vy + hit->y0;
                                box[5] = org.vy + hit->y1;
                                slope_fit(box, hit->kind);
                                if (dy >= 0)
                                {
                                    if (box[4] < best)
                                    {
                                        top = D_1F8000C0.vy;
                                        if (best < top)
                                        {
                                            top = best;
                                        }
                                        if (top < box[5])
                                        {
                                            best = box[4];
                                        }
                                    }
                                }
                                else if (box[4] < best && D_1F8000C0.vy < box[5])
                                {
                                    best = box[4];
                                }
                            }
                            hit++;
                        } while (--left != 0);
                    }
                }
            }
        }
    } while (best != prev);
    return best + D_1F800124_box.max_A;
}

// The lowest ceiling above pos in its own map block: the bottom (y0, fitted by slope_fit) of each
// STG_HIT whose area's rectangle holds pos and whose top is above it. 0x7FFF if none; on an
// empty cell, the complement of its step height (bits 8-12 of the cell value, halved).
sint32 Ceiling_height_get(SVECTOR *pos)
{
    sint16 box[6];
    SVECTOR org;
    sint32 val;
    sint32 best;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    sint32 left;
    STG_HIT *hit;

    val  = Map_cell_get(pos);
    best = 0x7FFF;
    if (val <= 0)
    {
        return ~((val & 0x1F00) >> 1);
    }
    D_1F8000C0 = *pos;
    block      = &Map_blocks[val];
    model      = (STG_MODEL *)(block->model & 0xFFFFFF);
    if (block->pos.pad & 0xFFF)
    {
        area = model->areas;
    }
    else
    {
        area = model->areas_0;
    }
    org.vx          = block->pos.vx;
    org.vy          = block->pos.vy;
    org.vz          = block->pos.vz;
    D_1F800124_w[0] = 0;
    D_1F800124_w[1] = 0;
    D_1F800124_w[2] = 0;
    for (; area->hits != NULL; area++)
    {
        // The do/while (0) ranks the area pointer above left and hit in GCC's register choice
        // (references weigh by loop depth).
        do
        {
            box[0] = org.vx + area->x0;
            box[1] = org.vx + area->x1;
            box[2] = org.vz + area->z0;
            box[3] = org.vz + area->z1;
        } while (0);
        hit = area->hits;
        if (Block_test_tbl[(hit->kind & 0xF0) >> 4](box, hit->kind) != 0)
        {
            left = area->count;
            do
            {
                box[4] = org.vy + hit->y0;
                box[5] = org.vy + hit->y1;
                slope_fit(box, hit->kind);
                if (box[4] < best && D_1F8000C0.vy < box[5])
                {
                    best = box[4];
                }
                hit++;
            } while (--left != 0);
        }
    }
    return best;
}

// floor_height_get for obj at its position, with its collision box and pool kind.
sint32 Obj_floor_height_get(MODEL_WORK *obj)
{
    return floor_height_get(&obj->pos, (VECTOR *)obj->hit_78, obj->kind_1);
}

// The highest floor below pos among the map blocks around it (func_8004B1E0), less the height in
// D_1F800124_box (set from ofs): each block's STG_AREAs whose rectangle holds pos (its block test)
// and whose STG_HIT starts below pos; on an empty cell, pos's own cell's step height (bits 8-14
// of its value). Hits whose flags bit 15 disagrees with kind's func_8002FE74 are skipped.
// -0x7FFF if none.
sint32 floor_height_get(SVECTOR *pos, VECTOR *ofs, sint32 kind)
{
    sint16 box[6];
    SVECTOR org;
    sint32 best;
    sint32 skip;
    sint32 n;
    sint32 val;
    sint32 lim;
    uint32 type;
    sint32 left;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    best       = -0x7FFF;
    D_1F8000C0 = *pos;
    n          = func_8004B1E0(&D_1F8000C0, 0);
    func_8004B3C0(ofs);
    skip = (func_8002FE74(kind) == 0) << 15;
    while (n-- != 0)
    {
        val = func_80048CEC(D_1F800118[n]);
        if (val <= 0)
        {
            if (D_1F800118[n] == map_cell_index(&D_1F8000C0) && (val & 0x6000))
            {
                lim = -((val & 0x1F00) >> 1) - ((val & 0x6000) >> 13) * 0x180 + 1;
                lim -= D_1F800124_box.min_8;
                if (best < lim)
                {
                    best = lim;
                }
            }
        }
        else
        {
            block = &Map_blocks[val];
            model = (STG_MODEL *)(block->model & 0xFFFFFF);
            if (block->pos.pad & 0xFFF)
            {
                area = model->areas;
            }
            else
            {
                area = model->areas_0;
            }
            org.vx = block->pos.vx;
            org.vy = block->pos.vy;
            org.vz = block->pos.vz;
            for (; area->hits != NULL; area++)
            {
                // The do/while (0)s are needed: they rank the area pointer above hit in GCC's
                // register choice (references weigh by loop depth); without them s0/s1 swap.
                do
                {
                    do
                    {
                        box[0] = org.vx + area->x0;
                        box[1] = org.vx + area->x1;
                        box[2] = org.vz + area->z0;
                        box[3] = org.vz + area->z1;
                    } while (0);
                    hit = area->hits;
                } while (0);
                if ((type = hit->kind) < 0x100 && Block_test_tbl[(type & 0xF0) >> 4](box, type) != 0)
                {
                    left = area->count;
                    do
                    {
                        if (!(hit->flags & (skip ^ 0x8000)))
                        {
                            box[4] = org.vy + hit->y0 - D_1F800124_box.max_A;
                            box[5] = org.vy + hit->y1 - D_1F800124_box.min_8;
                            if (box[4] < D_1F8000C0.vy && best < box[5])
                            {
                                best = box[5];
                            }
                        }
                        hit++;
                    } while (--left != 0);
                }
            }
        }
    }
    return best;
}

// The nearest wall face (func_800497CC) on the side pl faces: the quarter of its facing angle,
// turned back by unk116 unless func_8002FE74 holds for its kind.
sint32 func_8004976C(PL_WORK *pl)
{
    sint32 turn;

    if (func_8002FE74(pl->kind_1) != 0)
    {
        turn = 0;
    }
    else
    {
        turn = pl->unk116;
    }
    return func_800497CC(&pl->pos, pl->hit_78, ((pl->ang.vy - turn + 0x200) >> 10) & 3, pl->kind_1);
}

// The nearest wall face on one side of pos, for the box ent, among the STG_HITs around pos whose
// area (grown by ent) spans pos across that axis and whose height range (fitted by slope_fit)
// holds it: dir 0 the highest z1 of the areas starting below pos.vz, 1 the highest x1 below
// pos.vx, 2 the lowest z0 of those ending above pos.vz, 3 the lowest x0 above pos.vx. -0x7FFF
// (dir 0/1) or 0x7FFF (dir 2/3) if none. Hits whose flags bit 15 disagrees with kind's
// func_8002FE74 are skipped.
#ifdef NON_MATCHING
// Register allocation only: hit, best and area take s4, s2 and s6 where the target has s2, s4
// and s5 (and a switch constant load moves by one slot).
sint32 func_800497CC(SVECTOR *pos, HIT_ENT *ent, sint32 dir, sint32 kind)
{
    sint16 box[6];
    SVECTOR org;
    sint32 best;
    sint32 skip;
    sint32 n;
    sint32 val;
    sint32 left;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    best = -0x7FFF;
    if (dir & 2)
    {
        best = 0x7FFF;
    }
    D_1F8000C0 = *pos;
    n          = func_8004B1E0(&D_1F8000C0, 0);
    func_8004B3C0((VECTOR *)ent);
    skip = (func_8002FE74(kind) == 0) << 15;
    while (n-- != 0)
    {
        val = func_80048CEC(D_1F800118[n]);
        if (val <= 0)
        {
            continue;
        }
        block = &Map_blocks[val];
        model = (STG_MODEL *)(block->model & 0xFFFFFF);
        if (block->pos.pad & 0xFFF)
        {
            area = model->areas;
        }
        else
        {
            area = model->areas_0;
        }
        org.vx = block->pos.vx;
        org.vy = block->pos.vy;
        org.vz = block->pos.vz;
        for (; area->hits != NULL; area++)
        {
            do
            {
                do
                {
                    do
                    {
                        box[0] = org.vx + area->x0 - D_1F800124_box.max_2;
                        box[1] = org.vx + area->x1 - D_1F800124_box.min_0;
                        box[2] = org.vz + area->z0 - D_1F800124_box.max_6;
                        box[3] = org.vz + area->z1 - D_1F800124_box.min_4;
                        hit    = area->hits;
                    } while (0);
                } while (0);
            } while (0);
            switch (dir)
            {
                case 0:
                case 2:
                    if (D_1F8000C0.vx > box[0] && D_1F8000C0.vx < box[1])
                    {
                        break;
                    }
                    continue;
                case 1:
                case 3:
                    if (!(D_1F8000C0.vz > box[2] && D_1F8000C0.vz < box[3]))
                    {
                        continue;
                    }
                    break;
            }
            left = area->count;
            do
            {
                do
                {
                    if (hit->flags & (skip ^ 0x8000))
                    {
                        goto next;
                    }
                    box[4] = org.vy + hit->y0;
                    box[5] = org.vy + hit->y1;
                    slope_fit(box, hit->kind);
                    if (!(box[4] < D_1F8000C0.vy && D_1F8000C0.vy < box[5]))
                    {
                        goto next;
                    }
                    switch (dir)
                    {
                        case 0:
                            if (best < box[3] && D_1F8000C0.vz > box[2])
                            {
                                best = box[3];
                            }
                            break;
                        case 1:
                            if (best < box[1] && D_1F8000C0.vx > box[0])
                            {
                                best = box[1];
                            }
                            break;
                        case 2:
                            if (box[2] < best && D_1F8000C0.vz < box[3])
                            {
                                best = box[2];
                            }
                            break;
                        case 3:
                            if (box[0] < best && D_1F8000C0.vx < box[1])
                            {
                                best = box[0];
                            }
                            break;
                    }
                next:
                    hit++;
                } while (--left != 0);
            } while (0);
        }
    }
    return best;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_800497CC);
#endif

sint32 func_80049C24(MODEL_WORK *obj)
{
    return func_80049C54(&obj->pos, &obj->old, obj->hit_78, obj->kind_1);
}

// What is at pos, for the box ent: 0x80000000 if the move from prev crosses x or z = 0 far
// (over 0x4000) from it (a wrap), 0x40000000 outside the map window; on pos's own empty cell, its
// value (low 16 bits) if pos is above its step or below the step's bottom (bits 13-14 of the value,
// 0x180 each); else the cell value of the first map block around pos with an STG_HIT whose area
// holds pos and whose height range (fitted by slope_fit) holds it, with the hit's low flag bits
// in bits 16-19. Hits whose flags bit 15 disagrees with kind's func_8002FE74 are skipped. 0 if none.
sint32 func_80049C54(SVECTOR *pos, SVECTOR *prev, HIT_ENT *ent, sint32 kind)
{
    sint16 box[6];
    SVECTOR org;
    sint32 skip;
    sint32 n;
    sint32 val;
    sint32 floor;
    sint32 left;
    sint16 cy;
    sint32 top;
    sint32 bottom;
    uint32 type;
    uint32 flags;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    D_1F8000C0 = *pos;
    D_1F8000C8 = *prev;
    if ((D_1F8000C0.vx ^ D_1F8000C8.vx) & 0x8000 && ABS(D_1F8000C0.vx) > 0x4000)
    {
        return 0x80000000;
    }
    if ((D_1F8000C0.vz ^ D_1F8000C8.vz) & 0x8000 && ABS(D_1F8000C0.vz) > 0x4000)
    {
        return 0x80000000;
    }
    if (Map_cell_get(&D_1F8000C0) == 0)
    {
        return 0x40000000;
    }
    n = func_8004B1E0(&D_1F8000C0, 1);
    func_8004B3C0((VECTOR *)ent);
    skip = (func_8002FE74(kind) == 0) << 15;
    while (n-- != 0)
    {
        val = func_80048CEC(D_1F800118[n]);
        if (val <= 0)
        {
            if (D_1F800118[n] == map_cell_index(&D_1F8000C0))
            {
                floor = -((val & 0x1F00) >> 1);
                cy    = D_1F8000C0.vy;
                top   = floor - 1;
                if (top - D_1F800124_box.max_A < cy)
                {
                    return val & 0xFFFF;
                }
                if (val & 0x6000)
                {
                    bottom = floor - ((val & 0x6000) >> 13) * 0x180 + 1;
                    if (cy < bottom - D_1F800124_box.min_8)
                    {
                        return val & 0xFFFF;
                    }
                }
            }
            continue;
        }
        // The do/while (0)s are needed: they rank the area pointer above flags in GCC's register
        // choice (references weigh by loop depth).
        do
        {
            do
            {
                block = &Map_blocks[val];
                model = (STG_MODEL *)(block->model & 0xFFFFFF);
                if (block->pos.pad & 0xFFF)
                {
                    area = model->areas;
                }
                else
                {
                    area = model->areas_0;
                }
            } while (0);
            org.vx = block->pos.vx;
            org.vy = block->pos.vy;
            org.vz = block->pos.vz;
            for (; area->hits != NULL; area++)
            {
                box[0] = org.vx + area->x0;
                box[1] = org.vx + area->x1;
                box[2] = org.vz + area->z0;
                box[3] = org.vz + area->z1;
                hit    = area->hits;
                if ((type = hit->kind) < 0x100 && Block_test_tbl[(type & 0xF0) >> 4](box, type) != 0)
                {
                    left = area->count;
                    do
                    {
                        flags = hit->flags;
                        if (!(flags & (skip ^ 0x8000)))
                        {
                            box[4] = org.vy + hit->y0;
                            box[5] = org.vy + hit->y1;
                            slope_fit(box, hit->kind);
                            cy = D_1F8000C0.vy;
                            if (cy > box[4] && cy < box[5])
                            {
                                return (val & 0xFFFF) | ((flags & 0xF) << 16);
                            }
                        }
                        hit++;
                    } while (--left != 0);
                }
            }
        } while (0);
    }
    return 0;
}

// Fits the box (x0, x1, z0, z1, y0, y1) of a block hit to its slope at the point D_1F8000C0: for
// a ramp along z (kinds 8/9, 0x10/0x11) or x (0xA/0xB, 0x12/0x13), the top's height there (into
// box[4] for 8-0xB, box[5] for 0x10-0x13), with the low end moved down by D_1F800124_box's size
// along the ramp; ridges (0xC along z, 0xD along x, 0xE both) and diagonal ramps (0x18-0x55) set
// box[4]. Then takes D_1F800124_box's height off both, and leaves in D_1F8000FE which side the
// point is on (1/2: z, 3/4: x, 5-8: diagonal), or 0 (and for the ramps, 0 too when the slope is
// shallower than 45 degrees).
void slope_fit(sint16 *box, uint16 kind)
{
    sint8 side;
    uint8 type;
    sint32 top;
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 y0;
    sint32 y1;
    sint32 min;
    sint32 dx;
    sint32 dz;
    sint32 near;
    sint32 far;
    sint32 quad;

    side = 0;
    top  = 0;
    kind &= 0xFF;
    type = kind;
    y0   = box[4];
    x0   = box[0];
    x1   = box[1];
    z0   = box[2];
    z1   = box[3];
    y1   = box[5];
    min  = y0;
    switch (kind)
    {
        case 0x8:
        case 0x10:
            y0 -= (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            top = y0 + (y1 - y0) * (z1 - D_1F8000C0.vz) / (z1 - z0);
            if (top < min)
            {
                top = min;
            }
            if (z1 - z0 < y1 - y0)
            {
                side = 1;
            }
            break;
        case 0x9:
        case 0x11:
            y0 -= (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            top = y0 + (y1 - y0) * (D_1F8000C0.vz - z0) / (z1 - z0);
            if (top < min)
            {
                top = min;
            }
            if (z1 - z0 < y1 - y0)
            {
                side = 2;
            }
            break;
        case 0xA:
        case 0x12:
            y0 -= (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            top = y0 + (y1 - y0) * (D_1F8000C0.vx - x0) / (x1 - x0);
            if (top < min)
            {
                top = min;
            }
            if (x1 - x0 < y1 - y0)
            {
                side = 3;
            }
            break;
        case 0xB:
        case 0x13:
            y0 -= (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            top = y0 + (y1 - y0) * (x1 - D_1F8000C0.vx) / (x1 - x0);
            if (top < min)
            {
                top = min;
            }
            if (x1 - x0 < y1 - y0)
            {
                side = 4;
            }
            break;
        case 0xC:
            top = y0 + (y0 - y1) - (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            if (z0 + (z1 - z0) / 2 < D_1F8000C0.vz)
            {
                box[4] = top + (y1 - top) * (D_1F8000C0.vz - z0) / (z1 - z0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                side = 2;
            }
            else
            {
                box[4] = top + (y1 - top) * (z1 - D_1F8000C0.vz) / (z1 - z0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                side = 1;
            }
            break;
        case 0xD:
            top = y0 + (y0 - y1) - (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            if (x0 + (x1 - x0) / 2 < D_1F8000C0.vx)
            {
                box[4] = top + (y1 - top) * (D_1F8000C0.vx - x0) / (x1 - x0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                side = 3;
            }
            else
            {
                box[4] = top + (y1 - top) * (x1 - D_1F8000C0.vx) / (x1 - x0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                side = 4;
            }
            break;
        case 0xE:
            dx   = x1 - x0;
            near = D_1F8000C0.vz - z0;
            dz   = z1 - z0;
            far  = z1 - D_1F8000C0.vz;
            top  = y0 + (y0 - y1);
            quad = (D_1F8000C0.vx < x0 + near * dx / dz) * 2;
            if (D_1F8000C0.vx < x0 + far * dx / dz)
            {
                quad |= 1;
            }
            switch (quad)
            {
                case 0:
                    box[4] = top + (y1 - top) * (D_1F8000C0.vx - x0) / dx;
                    if (dx < y1 - y0)
                    {
                        side = 3;
                    }
                    break;
                case 1:
                    box[4] = top + (y1 - top) * far / dz;
                    if (dz < y1 - y0)
                    {
                        side = 1;
                    }
                    break;
                case 2:
                    box[4] = top + (y1 - top) * near / dz;
                    if (dz < y1 - y0)
                    {
                        side = 2;
                    }
                    break;
                case 3:
                    box[4] = top + (y1 - top) * (x1 - D_1F8000C0.vx) / dx;
                    if (dx < y1 - y0)
                    {
                        side = 4;
                    }
                    break;
            }
            break;
        case 0x18:
        case 0x24:
            side   = 5;
            box[4] = y0 + (y1 - y0) * ((D_1F8000C0.vx - x0) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            break;
        case 0x25:
            side   = 6;
            box[4] = y1 - (y1 - y0) * ((D_1F8000C0.vx - x0) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            break;
        case 0x19:
        case 0x34:
            side   = 7;
            box[4] = y0 + (y1 - y0) * ((x1 - D_1F8000C0.vx) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            break;
        case 0x35:
            side   = 8;
            box[4] = y1 - (y1 - y0) * ((x1 - D_1F8000C0.vx) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            break;
        case 0x1A:
        case 0x44:
            side   = 8;
            box[4] = y0 + (y1 - y0) * ((D_1F8000C0.vx - x0) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            break;
        case 0x45:
            side   = 7;
            box[4] = y1 - (y1 - y0) * ((D_1F8000C0.vx - x0) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            break;
        case 0x1B:
        case 0x54:
            side   = 6;
            box[4] = y0 + (y1 - y0) * ((x1 - D_1F8000C0.vx) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            break;
        case 0x55:
            side   = 5;
            box[4] = y1 - (y1 - y0) * ((x1 - D_1F8000C0.vx) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            break;
    }
    if (type >= 0x8 && type < 0xC)
    {
        box[4] = top;
    }
    if (type >= 0x10 && type < 0x14)
    {
        box[5] = top;
    }
    box[4] -= D_1F800124_box.max_A;
    D_1F8000FE = side;
    box[5] -= D_1F800124_box.min_8;
}

// Bounces the speed *vel off the walls in hit (Pos_map_push_out's flags: 0x100/0x200 x, 0x400/0x800 z,
// 0x1000/0x2000 y, the first of each pair the negative side): each axis hit points away from its
// wall; when both x and z walls are hit (a corner), x and z swap their sizes. 1 if any was hit.
sint32 Wall_reflect_spd(sint16 *vel, sint32 hit)
{
    SVECTOR old;
    sint32 bounced;

    bounced = 0;
    if ((hit & 0x300) && (hit & 0xC00))
    {
        bounced = 1;
        old     = *(SVECTOR *)vel;
        if (hit & 0x100)
        {
            if (hit & 0x400)
            {
                vel[0] = -ABS(old.vz);
                vel[2] = -ABS(old.vx);
            }
            else
            {
                vel[0] = -ABS(old.vz);
                vel[2] = ABS(old.vx);
            }
        }
        else
        {
            if (hit & 0x400)
            {
                vel[0] = ABS(old.vz);
                vel[2] = -ABS(old.vx);
            }
            else
            {
                vel[0] = ABS(old.vz);
                vel[2] = ABS(old.vx);
            }
        }
    }
    else
    {
        if (hit & 0x300)
        {
            bounced = 1;
            if (hit & 0x100)
            {
                vel[0] = -ABS(vel[0]);
            }
            else
            {
                vel[0] = ABS(vel[0]);
            }
        }
        if (hit & 0xC00)
        {
            bounced = 1;
            if (hit & 0x400)
            {
                vel[2] = -ABS(vel[2]);
            }
            else
            {
                vel[2] = ABS(vel[2]);
            }
        }
    }
    if (hit & 0x3000)
    {
        bounced = 1;
        if (hit & 0x1000)
        {
            vel[1] = -ABS(vel[1]);
        }
        else
        {
            vel[1] = ABS(vel[1]);
        }
    }
    return bounced;
}

// Reflects the angle off the walls in hit (0x100/0x200: one x side, 0x400/0x800: one z side);
// returns 1 if it hit any.
sint32 func_8004AE88(sint16 *angle, uint32 hit)
{
    sint32 ang;
    sint32 bounced;

    ang     = *angle & 0xFFF;
    bounced = 0;
    if (hit & 0x300)
    {
        bounced = 1;
        if (hit & 0x100)
        {
            // 0x401 <= ang <= 0xBFF
            if ((uint32)(ang - 0x401) < 0x7FF)
            {
                ang = 0x1000 - ang;
            }
        }
        else
        {
            // ang < 0x400 or ang > 0xC00
            if ((uint32)(ang - 0x400) >= 0x801)
            {
                ang = 0x1000 - ang;
            }
        }
    }
    if (hit & 0xC00)
    {
        bounced = 1;
        if (hit & 0x400)
        {
            if (ang >= 0x801)
            {
                ang = 0x1800 - ang;
            }
        }
        else
        {
            if (ang < 0x800)
            {
                ang = 0x800 - ang;
            }
        }
    }
    *angle = ang;
    return bounced;
}

// The slope side (D_1F8000FE, from slope_fit) of the first STG_HIT with flags bit 14 whose area
// holds pos, among the map blocks around it, while the player's field_74 is 0; or 0 if none, or
// if pos stands exactly on the step of its own empty cell.
sint32 func_8004AF28(SVECTOR *pos)
{
    sint16 box[6];
    SVECTOR org;
    sint32 n;
    sint32 val;
    sint32 left;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    D_1F8000C0      = *pos;
    n               = func_8004B1E0(&D_1F8000C0, 0);
    D_1F800124_w[0] = 0;
    D_1F800124_w[1] = 0;
    D_1F800124_w[2] = 0;
    while (n-- != 0)
    {
        val = func_80048CEC(D_1F800118[n]);
        if (val <= 0)
        {
            if (D_1F800118[n] == map_cell_index(&D_1F8000C0) && D_1F8000C0.vy == ~((val & 0x1F00) >> 1) - D_1F800124_box.max_A)
            {
                return 0;
            }
            continue;
        }
        block = &Map_blocks[val];
        model = (STG_MODEL *)(block->model & 0xFFFFFF);
        if (block->pos.pad & 0xFFF)
        {
            area = model->areas;
        }
        else
        {
            area = model->areas_0;
        }
        org.vx = block->pos.vx;
        org.vy = block->pos.vy;
        org.vz = block->pos.vz;
        // The do/while (0) ranks the area pointer above hit in GCC's register choice.
        do
        {
            for (; area->hits != NULL; area++)
            {
                box[0] = org.vx + area->x0;
                box[1] = org.vx + area->x1;
                box[2] = org.vz + area->z0;
                box[3] = org.vz + area->z1;
                hit    = area->hits;
                if (Block_test_tbl[(hit->kind & 0xF0) >> 4](box, hit->kind) != 0)
                {
                    left = area->count;
                    do
                    {
                        box[4] = org.vy + hit->y0;
                        box[5] = org.vy + hit->y1;
                        slope_fit(box, hit->kind);
                        if ((hit->flags & 0x4000) && Player_work[0].field_74 == 0 && D_1F8000FE != 0)
                        {
                            return D_1F8000FE;
                        }
                        hit++;
                    } while (--left != 0);
                }
            }
        } while (0);
    }
    return 0;
}

// Lists in D_1F800118 the map cells (Map_cells indexes) pos and its nearest neighbours touch: its
// own cell and, toward the nearer half of the cell, the one beside it in x, in z and diagonally.
// Empty cells are left out unless keep_empty; a cell whose nonzero value is already listed is
// skipped. Stops at the first cell outside the map window. Returns the count.
sint32 func_8004B1E0(SVECTOR *pos, sint32 keep_empty)
{
    uint16 ofs[4][2];
    sint16 *list;
    sint32 count;
    sint32 i;
    sint32 found;
    sint32 j;
    sint32 cell;
    sint32 val;
    uint32 x;
    uint32 z;

    ofs[0][1] = ofs[1][1] = ofs[0][0] = ofs[2][0] = 0x8000;
    if ((pos->vx & 0x1FF) >= 0x101)
    {
        ofs[1][0] = ofs[3][0] = 0x8200;
    }
    else
    {
        ofs[1][0] = ofs[3][0] = 0x7E00;
    }
    if ((pos->vz & 0x1FF) >= 0x101)
    {
        ofs[2][1] = ofs[3][1] = 0x8200;
    }
    else
    {
        ofs[2][1] = ofs[3][1] = 0x7E00;
    }
    count = 0;
    i     = 0; // here, not in the for after list: that doesn't match
    list  = D_1F800118;
    for (; i < 4; i++)
    {
        x = ((pos->vx + ofs[i][0]) >> 9) - Map_org_x;
        if (x >= Map_w)
        {
            break;
        }
        z = ((pos->vz + ofs[i][1]) >> 9) - Map_org_y;
        if (z >= Map_h)
        {
            break;
        }
        cell = x + z * Map_w;
        val  = func_80048CEC(cell);
        if (val != 0 || keep_empty != 0)
        {
            found = 0;
            for (j = 0; j < count; j++)
            {
                if (val > 0 && val == func_80048CEC(list[j]))
                {
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                list[count] = cell;
                count++;
            }
        }
    }
    return count;
}

void func_8004B3C0(VECTOR *ofs)
{
    if (ofs != NULL)
    {
        D_1F800124.vx = ofs->vx;
        D_1F800124.vy = ofs->vy;
        D_1F800124.vz = ofs->vz;
    }
    else
    {
        D_1F800124.vx = 0;
        D_1F800124.vy = 0;
        D_1F800124.vz = 0;
    }
}

// Collides obj's move (old -> pos) against the map (map_push_out, with obj's box hit_78). On a hit
// (> 0), the pushed axes of pos and pos_l are set from D_1F8000C0, and field_74 (unless 2) from
// D_1F8000F6. If the point is still stuck (< 0), obj goes back to old: only x and z (stopping spd
// vx and vz; y too while field_74 is set) when its kind's func_8002FE74 is 0. Returns the hit flags.
sint32 Obj_map_push_out(MODEL_WORK *obj)
{
    sint32 result;
    sint32 slide;

    func_8004B3C0((VECTOR *)obj->hit_78);
    slide  = (func_8002FE74(obj->kind_1) == 0) << 15;
    result = map_push_out(&obj->pos, &obj->old, obj->field_74, slide);
    if (result != 0)
    {
        if (result > 0)
        {
            if (result & 0x300)
            {
                obj->pos.vx   = D_1F8000C0.vx;
                obj->pos_l.vx = D_1F8000C0.vx << 16;
            }
            if (result & 0xC00)
            {
                obj->pos.vz   = D_1F8000C0.vz;
                obj->pos_l.vz = D_1F8000C0.vz << 16;
            }
            if (result & 0x3000)
            {
                obj->pos.vy   = D_1F8000C0.vy;
                obj->pos_l.vy = D_1F8000C0.vy << 16;
            }
            if (obj->field_74 != 2)
            {
                obj->field_74 = D_1F8000F6;
            }
        }
        else if (slide != 0)
        {
            obj->spd.vz   = 0;
            obj->spd.vx   = 0;
            obj->pos.vx   = obj->old.vx;
            obj->pos.vz   = obj->old.vz;
            obj->pos_l.vx = obj->old_l.vx;
            obj->pos_l.vz = obj->old_l.vz;
            if (obj->field_74 != 0)
            {
                obj->field_74 = 0;
                obj->spd.vy   = 0;
                obj->pos.vy   = obj->old.vy;
                obj->pos_l.vy = obj->old_l.vy;
            }
        }
        else
        {
            obj->pos   = obj->old;
            obj->pos_l = obj->old_l;
        }
    }
    return result;
}

// Collides the move old -> pos against the map for the box ent (map_push_out). On a hit (> 0) the
// pushed axes of pos are set from D_1F8000C0; if the point is still stuck (< 0), pos goes back to
// old. Returns the hit flags.
sint32 Pos_map_push_out(SVECTOR *pos, SVECTOR *old, sint32 n, HIT_ENT *ent)
{
    sint32 result;

    func_8004B3C0((VECTOR *)ent);
    result = map_push_out(pos, old, n, 0);
    if (result != 0)
    {
        if (result > 0)
        {
            if (result & 0x300)
            {
                pos->vx = D_1F8000C0.vx;
            }
            if (result & 0xC00)
            {
                pos->vz = D_1F8000C0.vz;
            }
            if (result & 0x3000)
            {
                pos->vy = D_1F8000C0.vy;
            }
        }
        else
        {
            *pos = *old;
        }
    }
    return result;
}

// The map version of solid_push_out: collides the move old -> pos (the box of D_1F800124_box)
// against the map blocks around pos (func_8004B1E0), and against the floor and ceiling of pos's
// own empty cell. no_step goes to D_1F8000F6; hits whose flags bit 15 matches slide's are skipped.
// Pushes the point out up to 9 times (0x80000000 if it is still inside); returns 0 if it did not
// move, else the axis it moved most along (1/2 x, 3/4 z, 5/6 y) with a bit per moved axis
// (0x100/0x200 x, 0x400/0x800 z, 0x1000/0x2000 y). The result stays in D_1F8000C0.
sint32 map_push_out(SVECTOR *pos, SVECTOR *old, sint32 no_step, sint32 slide)
{
    SVECTOR org;
    sint16 box[6];
    sint32 count;
    sint32 tries;
    sint32 n;
    sint32 id;
    sint32 val;
    sint32 test;
    uint32 kind;
    sint32 found;
    sint32 floor;
    sint32 top;
    sint32 bottom;
    sint32 cy;
    sint32 left;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    found           = 0;
    tries           = 0;
    D_1F8000FF      = 0;
    D_1F8000C8      = *old;
    D_1F8000C0      = *pos;
    D_1F8000F6      = no_step;
    D_1F800100_h[0] = 0;
    D_1F800100_h[1] = 0;
    D_1F800100_h[2] = 0;
    D_1F800106[0]   = 0;
    D_1F800106[1]   = 0;
    D_1F800106[2]   = 0;
    D_1F80010C[0]   = 0;
    D_1F80010C[1]   = 0;
    D_1F80010C[2]   = 0;
    D_1F800112[0]   = 0;
    D_1F800112[1]   = 0;
    D_1F800112[2]   = 0;
    D_1F8000D8.vx   = D_1F8000C0.vx - D_1F8000C8.vx;
    D_1F8000D8.vy   = D_1F8000C0.vy - D_1F8000C8.vy;
    D_1F8000D8.vz   = D_1F8000C0.vz - D_1F8000C8.vz;
    count           = func_8004B1E0(&D_1F8000C0, 0);
retry:
    n = count;
    while (n-- != 0)
    {
        D_1F8000D0.vx = D_1F8000C0.vx - D_1F8000C8.vx;
        D_1F8000D0.vy = D_1F8000C0.vy - D_1F8000C8.vy;
        D_1F8000D0.vz = D_1F8000C0.vz - D_1F8000C8.vz;
        id            = D_1F800118[n];
        val           = func_80048CEC(id);
        if (val <= 0)
        {
            // An empty cell: only pos's own cell, with its floor and ceiling heights. id is
            // reused for the height the point is put at.
            found = 0;
            if (id != map_cell_index(&D_1F8000C0))
            {
                continue;
            }
            floor = -((val & 0x1F00) >> 1);
            cy    = D_1F8000C0.vy;
            top   = floor - 1;
            id    = top - D_1F800124_box.max_A;
            if (id < cy)
            {
                D_1F800106[0] = 0;
                D_1F800106[1] = 0;
                D_1F800106[2] = 0;
                D_1F8000C0.vy = id;
                found         = 1;
                if (D_1F8000D0.vy > 0)
                {
                    D_1F8000F6 = 0;
                }
                break;
            }
            if (val & 0x6000)
            {
                bottom = floor - ((val & 0x6000) >> 13) * 0x180 + 1;
                id     = bottom - D_1F800124_box.min_8;
                if (cy < id)
                {
                    D_1F800106[0] = 0;
                    D_1F800106[1] = 0;
                    D_1F800106[2] = 0;
                    D_1F8000C0.vy = id;
                    found         = 1;
                    break;
                }
            }
            continue;
        }
        // The do/while (0)s rank the pointers in GCC's register choice, as in floor_height_get.
        do
        {
            block = &Map_blocks[val];
            model = (STG_MODEL *)(block->model & 0xFFFFFF);
            if (block->pos.pad & 0xFFF)
            {
                area = model->areas;
            }
            else
            {
                area = model->areas_0;
            }
            org.vx = block->pos.vx;
            org.vy = block->pos.vy;
            org.vz = block->pos.vz;
        } while (0);
        for (; area->hits != NULL; area++)
        {
            do
            {
                do
                {
                    box[0] = org.vx + area->x0;
                    box[1] = org.vx + area->x1;
                    box[2] = org.vz + area->z0;
                    box[3] = org.vz + area->z1;
                } while (0);
                hit = area->hits;
            } while (0);
            if ((kind = hit->kind) >= 0x100 || (test = Block_test_tbl[(kind & 0xF0) >> 4](box, kind)) == 0)
            {
                found = 0;
                continue;
            }
            left = area->count;
            do
            {
                if (!(hit->flags & (slide ^ 0x8000) & 0x8000))
                {
                    box[4] = org.vy + hit->y0;
                    box[5] = org.vy + hit->y1;
                    found  = func_8004BDC8(box, hit->kind, test);
                    if (found != 0)
                    {
                        goto done;
                    }
                }
                hit++;
            } while (--left != 0);
        }
    }
done:
    if (found != 0)
    {
        D_1F8000C0.vx += D_1F800106[0];
        D_1F8000C0.vz += D_1F800106[2];
        D_1F8000C0.vy += D_1F800106[1];
        D_1F800106[0]   = D_1F800100_h[0];
        D_1F800106[1]   = D_1F800100_h[1];
        D_1F800106[2]   = D_1F800100_h[2];
        D_1F800112[0]   = D_1F80010C[0];
        D_1F800112[1]   = D_1F80010C[1];
        D_1F800112[2]   = D_1F80010C[2];
        D_1F800100_h[0] = 0;
        D_1F800100_h[1] = 0;
        D_1F800100_h[2] = 0;
        D_1F80010C[0]   = 0;
        D_1F80010C[1]   = 0;
        D_1F80010C[2]   = 0;
        if (tries++ < 8)
        {
            goto retry;
        }
        return 0x80000000;
    }
    dx = pos->vx - D_1F8000C0.vx;
    dz = pos->vz - D_1F8000C0.vz;
    dy = pos->vy - D_1F8000C0.vy;
    if (dx == 0 && dz == 0 && dy == 0)
    {
        return 0;
    }
    // val is reused for the result.
    if (ABS(dx) > ABS(dz))
    {
        if (ABS(dx) > ABS(dy))
        {
            val = (dx > 0) ? 1 : 2;
        }
        else
        {
            val = (dy > 0) ? 5 : 6;
        }
    }
    else if (ABS(dz) > ABS(dy))
    {
        val = (dz > 0) ? 3 : 4;
    }
    else
    {
        val = (dy > 0) ? 5 : 6;
    }
    if (dx != 0)
    {
        val |= (dx > 0) ? 0x100 : 0x200;
    }
    if (dz != 0)
    {
        val |= (dz > 0) ? 0x400 : 0x800;
    }
    if (dy != 0)
    {
        val |= (dy > 0) ? 0x1000 : 0x2000;
    }
    return val;
}

// Collides the point D_1F8000C0 (moved from D_1F8000C8) with the block box (x0, x1, z0, z1, y0,
// y1) of shape kind (STG_HIT.kind), the box of D_1F800124_box taken off its height: pushes it out
// of flat blocks, walls, corners and slopes (func_8004F44C, func_8004F8BC, ...), steps it up onto
// low ones, and clears the speeds in D_1F800106 it is stopped on. 1 if the point was inside.
// Cross-jumping shapes the shared tails: `landed` is an int so that corner's store of 0x100
// doesn't merge with the 0x1C cases'. The callers pass the block test's result as test, unused.
sint32 func_8004BDC8(sint16 *box, uint16 kind, sint32 test)
{
    uint16 type;
    sint32 height;
    sint32 flag;
    sint32 result;
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 y0;
    sint32 y1;
    sint32 min;
    sint32 top;
    sint32 bottom;
    sint32 gap;
    sint32 dx;
    sint32 dz;
    sint32 b;
    sint32 near;
    sint32 far;
    sint32 near_x;
    sint32 far_x;
    sint32 landed;

    height = 0;
    flag   = 0;
    result = 0;
    type   = kind & 0xFF;
    top    = box[4] - D_1F800124_box.max_A;
    bottom = box[5] - D_1F800124_box.min_8;
    x0     = box[0];
    x1     = box[1];
    z0     = box[2];
    z1     = box[3];
    y0     = box[4];
    y1     = box[5];
    min    = y0;
    switch (kind & 0xFF)
    {
        case 0x0:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                return 1;
            }
            return 0;
        case 0x1:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                result        = 1;
                if (D_1F8000F6 == 0 && D_1F8000C0.vy - top < 8 && D_1F8000FF == 0)
                {
                    D_1F8000C0.vy = top;
                    D_1F8000F6_h  = 0x100;
                    goto clear;
                }
                if (func_8004F44C(&D_1F8000C0, &D_1F8000C8, 1) != 0)
                {
                    if (D_1F8000D0.vy >= 0)
                    {
                        D_1F8000F6_h = 0x100;
                    }
                    goto clear;
                }
            }
            break;
        case 0x2:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                if (func_8004F44C(&D_1F8000C0, &D_1F8000C8, 0) != 0)
                {
                    if (D_1F8000D0.vy >= 0)
                    {
                        D_1F8000F6_h = 0x100;
                    }
                    goto clear;
                }
            }
            break;
        case 0x3:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                result        = 1;
                if (D_1F8000D0.vy >= 0 || D_1F8000F6 == 0)
                {
                    D_1F8000C0.vy = top;
                    goto land;
                }
                if (func_8004F44C(&D_1F8000C0, &D_1F8000C8, 3) != 0)
                {
                    D_1F800106[0] = 0;
                    D_1F800106[1] = 0;
                    D_1F800106[2] = 0;
                }
            }
            break;
        case 0xF:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                D_1F8000C0.vy = bottom;
                result        = 1;
                goto clear;
            }
            break;
        case 0x4:
        case 0x5:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
            side_x:
                if (func_8004F8BC(&D_1F8000C0, &D_1F8000C8, type - 4) != 0)
                {
                    if (D_1F8000D0.vy >= 0)
                    {
                        D_1F8000F6_h = 0x100;
                    }
                    D_1F800106[1] = 0;
                }
                D_1F800106[0] = 0;
                goto clear_z;
            }
            break;
        case 0x6:
        case 0x7:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
            side_z:
                if (func_8004FBE8(&D_1F8000C0, &D_1F8000C8, type - 6) != 0)
                {
                    if (D_1F8000D0.vy >= 0)
                    {
                        D_1F8000F6_h = 0x100;
                    }
                    D_1F800106[1] = 0;
                }
                D_1F800106[0] = 0;
                goto clear_z;
            }
            break;
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                if (func_800501E8(&D_1F8000C0, type - 0x1C) != 0)
                {
                    if (D_1F8000D0.vy >= 0)
                    {
                    land:
                        D_1F8000F6_h = 0x100;
                    }
                    goto clear;
                }
            }
            break;
        case 0x21:
        case 0x22:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                gap           = (ABS(D_1F8000D8.vx) + D_1F800124_box.max_2) * (x1 - x0);
                b             = (ABS(D_1F8000D8.vz) - D_1F800124_box.min_4) * (z1 - z0);
                if (b < gap && (D_1F8000FF & 1))
                {
                    type = 4;
                    goto side_x;
                }
                if (gap < b && (D_1F8000FF & 8))
                {
                    type = 6;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x31:
        case 0x32:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                gap           = (ABS(D_1F8000D8.vx) - D_1F800124_box.min_0) * (x1 - x0);
                b             = (ABS(D_1F8000D8.vz) - D_1F800124_box.min_4) * (z1 - z0);
                if (b < gap && (D_1F8000FF & 2))
                {
                    type = 4;
                    goto side_x;
                }
                if (gap < b && (D_1F8000FF & 8))
                {
                    type = 7;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x41:
        case 0x42:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                gap           = (ABS(D_1F8000D8.vx) + D_1F800124_box.max_2) * (x1 - x0);
                b             = (ABS(D_1F8000D8.vz) + D_1F800124_box.max_6) * (z1 - z0);
                if (b < gap && (D_1F8000FF & 1))
                {
                    type = 5;
                    goto side_x;
                }
                if (gap < b && (D_1F8000FF & 4))
                {
                    type = 6;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x51:
        case 0x52:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result        = 1;
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                gap           = (ABS(D_1F8000D8.vx) + D_1F800124_box.max_2) * (x1 - x0);
                b             = (ABS(D_1F8000D8.vz) - D_1F800124_box.min_4) * (z1 - z0);
                if (b < gap && (D_1F8000FF & 2))
                {
                    type = 5;
                    goto side_x;
                }
                if (gap < b && (D_1F8000FF & 4))
                {
                    type = 7;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x23:
        case 0x33:
        case 0x43:
        case 0x53:
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                D_1F8000F0.vy = top;
                D_1F8000F8.vy = bottom;
                result        = 1;
                if (D_1F8000D0.vy >= 0)
                {
                    D_1F8000C0.vy = top;
                    D_1F8000F6_h  = 0x100;
                    break;
                }
                goto corner;
            }
            break;
        case 0x8:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 8) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            height = y0 + (y1 - y0) * (z1 - D_1F8000C0.vz) / (z1 - z0);
            gap    = D_1F8000C0.vz - D_1F8000F0.vz;
            if (height < min)
            {
                height = min;
            }
            b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F0.vz += b;
            }
            flag = 0x20;
            goto floor;
        case 0x9:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 4) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            height = y0 + (y1 - y0) * (D_1F8000C0.vz - z0) / (z1 - z0);
            gap    = D_1F8000F8.vz - D_1F8000C0.vz;
            if (height < min)
            {
                height = min;
            }
            b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F8.vz -= b;
            }
            flag = 0x20;
            goto floor;
        case 0xA:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 1) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            height = y0 + (y1 - y0) * (D_1F8000C0.vx - x0) / (x1 - x0);
            gap    = D_1F8000F8.vx - D_1F8000C0.vx;
            if (height < min)
            {
                height = min;
            }
            b = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F8.vx -= b;
            }
            flag = 0x10;
            goto floor;
        case 0xB:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 2) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            height = y0 + (y1 - y0) * (x1 - D_1F8000C0.vx) / (x1 - x0);
            gap    = D_1F8000C0.vx - D_1F8000F0.vx;
            if (height < min)
            {
                height = min;
            }
            b = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F0.vx += b;
            }
            flag = 0x10;
            goto floor;
        case 0xC:
            y0 += (y0 - y1) - (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            if (D_1F8000C0.vz < z0 + (z1 - z0) / 2)
            {
                height = y0 + (y1 - y0) * (z1 - D_1F8000C0.vz) / (z1 - z0);
                if (height < min)
                {
                    height = min;
                }
                gap = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (gap > 0)
                {
                    D_1F8000F0.vz += gap;
                }
                gap = D_1F8000C0.vz - D_1F8000F0.vz;
            }
            else
            {
                height = y0 + (y1 - y0) * (D_1F8000C0.vz - z0) / (z1 - z0);
                if (height < min)
                {
                    height = min;
                }
                gap = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (gap > 0)
                {
                    D_1F8000F8.vz -= gap;
                }
                gap = D_1F8000F8.vz - D_1F8000C0.vz;
            }
            flag = 0x20;
            goto floor;
        case 0xD:
            y0 += (y0 - y1) - (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            if (x0 + (x1 - x0) / 2 < D_1F8000C0.vx)
            {
                height = y0 + (y1 - y0) * (D_1F8000C0.vx - x0) / (x1 - x0);
                if (height < min)
                {
                    height = min;
                }
                gap = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (gap > 0)
                {
                    D_1F8000F8.vx -= gap;
                }
                gap = -D_1F8000C0.vx + D_1F8000F8.vx;
            }
            else
            {
                height = y0 + (y1 - y0) * (x1 - D_1F8000C0.vx) / (x1 - x0);
                if (height < min)
                {
                    height = min;
                }
                gap = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (gap > 0)
                {
                    D_1F8000F0.vx += gap;
                }
                gap = D_1F8000C0.vx - D_1F8000F0.vx;
            }
            flag = 0x10;
            goto floor;
        case 0xE:
            dx     = x1 - x0;
            near   = D_1F8000C0.vz - z0;
            dz     = z1 - z0;
            far    = z1 - D_1F8000C0.vz;
            near_x = near * dx / dz;
            far_x  = far * dx / dz;
            y0 += y0 - y1;
            gap = (D_1F8000C0.vx < x0 + near_x) * 2;
            if (D_1F8000C0.vx < x0 + far_x)
            {
                gap |= 1;
            }
            switch (gap)
            {
                case 0:
                    height = y0 + (y1 - y0) * (D_1F8000C0.vx - x0) / dx;
                    gap    = dx * (y1 - D_1F8000C0.vy) / (y1 - y0);
                    if (gap > 0)
                    {
                        D_1F8000F8.vx -= gap;
                    }
                    flag = 0x10;
                    gap  = -D_1F8000C0.vz + D_1F8000F8.vx;
                    goto floor;
                case 1:
                    height = y0 + (y1 - y0) * far / dz;
                    gap    = dz * (y1 - D_1F8000C0.vy) / (y1 - y0);
                    if (gap > 0)
                    {
                        D_1F8000F0.vz += gap;
                    }
                    flag = 0x20;
                    gap  = D_1F8000C0.vz - D_1F8000F0.vz;
                    goto floor;
                case 2:
                    height = y0 + (y1 - y0) * near / dz;
                    gap    = dz * (y1 - D_1F8000C0.vy) / (y1 - y0);
                    if (gap > 0)
                    {
                        D_1F8000F8.vz -= gap;
                    }
                    flag = 0x20;
                    gap  = D_1F8000C0.vz + D_1F8000F8.vz;
                    goto floor;
                case 3:
                    height = y0 + (y1 - y0) * (x1 - D_1F8000C0.vx) / dx;
                    gap    = dx * (y1 - D_1F8000C0.vy) / (y1 - y0);
                    if (gap > 0)
                    {
                        D_1F8000F0.vx += gap;
                    }
                    flag = 0x10;
                    gap  = D_1F8000C0.vx - D_1F8000F0.vx;
                    goto floor;
            }
            goto floor;
        case 0x10:
            y0 += (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            height = y0 + (y1 - y0) * (z1 - D_1F8000C0.vz) / (z1 - z0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x11:
            y0 += (y1 - y0) * (D_1F800124_box.max_6 - D_1F800124_box.min_4) / (z1 - z0);
            height = y0 + (y1 - y0) * (D_1F8000C0.vz - z0) / (z1 - z0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x12:
            y0 += (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            height = y0 + (y1 - y0) * (D_1F8000C0.vx - x0) / (x1 - x0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x13:
            y0 += (y1 - y0) * (D_1F800124_box.max_2 - D_1F800124_box.min_0) / (x1 - x0);
            height = y0 + (y1 - y0) * (x1 - D_1F8000C0.vx) / (x1 - x0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x18:
        case 0x24:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 9) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000F8.vx - D_1F8000C0.vx <= D_1F8000C0.vz - D_1F8000F0.vz) ? D_1F8000F8.vx - D_1F8000C0.vx
                                                                                      : D_1F8000C0.vz - D_1F8000F0.vz;
            height = y0 + (y1 - y0) * ((D_1F8000C0.vx - x0) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            if (type != 0x18)
            {
                b = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F8.vx -= b;
                }
                b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F0.vz += b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x25:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 6) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000F8.vx - D_1F8000C0.vx <= D_1F8000C0.vz - D_1F8000F0.vz) ? D_1F8000F8.vx - D_1F8000C0.vx
                                                                                      : D_1F8000C0.vz - D_1F8000F0.vz;
            height = y1 - (y1 - y0) * ((D_1F8000C0.vx - x0) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            b      = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F8.vx -= b;
            }
            b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F0.vz += b;
            }
            flag = 0x30;
            goto floor;
        case 0x19:
        case 0x34:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 0xA) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000C0.vx - D_1F8000F0.vx <= D_1F8000C0.vz - D_1F8000F0.vz) ? D_1F8000C0.vx - D_1F8000F0.vx
                                                                                      : D_1F8000C0.vz - D_1F8000F0.vz;
            height = y0 + (y1 - y0) * ((x1 - D_1F8000C0.vx) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            if (type != 0x19)
            {
                b = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F0.vx += b;
                }
                b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F0.vz += b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x35:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 5) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000C0.vx - D_1F8000F0.vx <= D_1F8000C0.vz - D_1F8000F0.vz) ? D_1F8000C0.vx - D_1F8000F0.vx
                                                                                      : D_1F8000C0.vz - D_1F8000F0.vz;
            height = y1 - (y1 - y0) * ((x1 - D_1F8000C0.vx) + (z1 - D_1F8000C0.vz)) / (x1 - x0);
            b      = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F0.vx += b;
            }
            b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F0.vz += b;
            }
            flag = 0x30;
            goto floor;
        case 0x1A:
        case 0x44:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 5) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000F8.vx - D_1F8000C0.vx <= D_1F8000F8.vz - D_1F8000C0.vz) ? D_1F8000F8.vx - D_1F8000C0.vx
                                                                                      : D_1F8000F8.vz - D_1F8000C0.vz;
            height = y0 + (y1 - y0) * ((D_1F8000C0.vx - x0) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            if (type != 0x1A)
            {
                b = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F8.vx -= b;
                }
                b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F8.vz -= b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x45:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 0xA) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000F8.vx - D_1F8000C0.vx <= D_1F8000F8.vz - D_1F8000C0.vz) ? D_1F8000F8.vx - D_1F8000C0.vx
                                                                                      : D_1F8000F8.vz - D_1F8000C0.vz;
            height = y1 - (y1 - y0) * ((D_1F8000C0.vx - x0) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            b      = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F8.vx -= b;
            }
            b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F8.vz -= b;
            }
            flag = 0x30;
            goto floor;
        case 0x1B:
        case 0x54:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 6) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000C0.vx - D_1F8000F0.vx <= D_1F8000F8.vz - D_1F8000C0.vz) ? D_1F8000C0.vx - D_1F8000F0.vx
                                                                                      : D_1F8000F8.vz - D_1F8000C0.vz;
            height = y0 + (y1 - y0) * ((x1 - D_1F8000C0.vx) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            if (type != 0x1B)
            {
                b = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F0.vx += b;
                }
                b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
                if (b > 0)
                {
                    D_1F8000F8.vz -= b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x55:
            if (D_1F8000F6 == 0 && (D_1F8000FF & 9) && D_1F8000C0.vy - top < 0x20)
            {
                goto step;
            }
            gap    = (D_1F8000C0.vx - D_1F8000F0.vx <= D_1F8000F8.vz - D_1F8000C0.vz) ? D_1F8000C0.vx - D_1F8000F0.vx
                                                                                      : D_1F8000F8.vz - D_1F8000C0.vz;
            height = y1 - (y1 - y0) * ((x1 - D_1F8000C0.vx) + (D_1F8000C0.vz - z0)) / (x1 - x0);
            b      = (x1 - x0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F0.vx += b;
            }
            b = (z1 - z0) * (y1 - D_1F8000C0.vy) / (y1 - y0);
            if (b > 0)
            {
                D_1F8000F8.vz -= b;
            }
            flag = 0x30;
            goto floor;
        step:
            // Low enough to step up onto: stand on top, keeping the stored x/z speeds.
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                D_1F8000C0.vy = top;
                D_1F800106[1] = 0;
                D_1F8000FF    = 0x20;
                D_1F800106[0] = D_1F800112[0];
                D_1F800106[2] = D_1F800112[2];
                result        = 1;
            }
            break;
        corner:
            if (func_8004FF14(&D_1F8000C0, (type >> 4) - 2) != 0)
            {
                if (D_1F8000D0.vy >= 0)
                {
                    landed       = 0x100;
                    D_1F8000F6_h = landed;
                }
                goto clear;
            }
            break;
        floor:
            height -= D_1F800124_box.max_A;
            if (height < D_1F8000C0.vy && D_1F8000C0.vy < bottom)
            {
                result = 1;
                if (D_1F8000F6 == 0 && D_1F8000C0.vy - height < 0x20 && D_1F8000C0.vy - top < gap)
                {
                    D_1F8000C0.vy = height;
                    D_1F800106[1] = 0;
                    break;
                }
                D_1F8000F0.vy = height;
                D_1F8000F8.vy = bottom;
                if (func_8004F44C(&D_1F8000C0, &D_1F8000C8, flag | 0x43) != 0)
                {
                    D_1F800106[0] = 0;
                    D_1F800106[1] = 0;
                    D_1F800106[2] = 0;
                }
                if (D_1F8000D0.vy >= 0)
                {
                    D_1F8000F6_h = 0x100;
                }
            }
            break;
        ceil:
            height -= D_1F800124_box.min_8;
            if (top < D_1F8000C0.vy && D_1F8000C0.vy < height)
            {
                result        = 1;
                D_1F8000C0.vy = height + 1;
            clear:
                D_1F800106[0] = 0;
                D_1F800106[1] = 0;
            clear_z:
                D_1F800106[2] = 0;
            }
            break;
    }
    return result;
}

// Block test of Block_test_tbl (kinds 0 and 1): shrinks the block's rectangle (x0, x1, z0, z1) by the
// box in D_1F800124_box; if D_1F8000C0 is inside, saves the corners in D_1F8000F0/F8 and returns
// 1 + which side of each of the two diagonals the point is on (bit 1: the z0 one, bit 0: the z1
// one), else 0.
sint32 func_8004E304(sint16 *rect)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint16 px;
    sint16 pz;
    sint32 dz;
    sint32 side;

    x0 = rect[0] -= D_1F800124_box.max_2;
    x1 = rect[1] -= D_1F800124_box.min_0;
    z0 = rect[2] -= D_1F800124_box.max_6;
    z1 = rect[3] -= D_1F800124_box.min_4;
    px = D_1F8000C0.vx;
    if (x0 < px && px < x1)
    {
        pz = D_1F8000C0.vz;
        if (z0 < pz && pz < z1)
        {
            dz            = z1 - z0;
            D_1F8000F0.vx = x0;
            D_1F8000F8.vx = x1;
            D_1F8000F0.vz = z0;
            D_1F8000F8.vz = z1;
            side          = (px < x0 + (pz - z0) * (x1 - x0) / dz) * 2;
            if (px < x0 + (z1 - pz) * (x1 - x0) / dz)
            {
                side |= 1;
            }
            return side + 1;
        }
    }
    return 0;
}

// Same code as func_80054BAC.
sint32 func_8004E488(void)
{
    return 0;
}

// Diagonal block tests of Block_test_tbl, one per corner the diagonal cuts off (func_8004E490,
// func_8004E750, func_8004EA10, func_8004ECD0): grow or shrink the block's rectangle by the box in
// D_1F800124_box (the other way for kinds 0x25, 0x35, 0x45, 0x55); if D_1F8000C0 is inside the
// triangle (its edge moved 4 out, clipped to the rectangle), save the triangle's bounds in
// D_1F8000F0/F8 and return 2 when D_1F8000C8 is on the inside of the diagonal too, else 1;
// 0 when D_1F8000C0 is outside.
sint32 func_8004E490(sint16 *rect, sint32 kind)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 w;
    sint32 d;
    sint32 xl;
    sint32 zl;
    sint32 cx;
    sint32 cz;
    sint32 px;
    sint32 pz;
    SVECTOR *pos;

    if (kind != 0x25)
    {
        x0 = rect[0] += D_1F800124_box.max_2;
        x1 = rect[1] -= D_1F800124_box.min_0;
        z0 = rect[2] -= D_1F800124_box.max_6;
        z1 = rect[3] += D_1F800124_box.min_4;
    }
    else
    {
        x0 = rect[0] -= D_1F800124_box.max_2;
        x1 = rect[1] += D_1F800124_box.min_0;
        z0 = rect[2] += D_1F800124_box.max_6;
        z1 = rect[3] -= D_1F800124_box.min_4;
    }
    pos = &D_1F8000C0;
    cz  = pos->vz;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x0 + (cz - z0) * w / d + 4;
    if (x1 < xl)
    {
        xl = x1;
    }
    cx = pos->vx;
    zl = z0 + (cx - x0) * d / w - 4;
    if (zl < z0)
    {
        zl = z0;
    }
    if (x0 < cx && cx < xl && zl < cz && cz < z1)
    {
        D_1F8000F0.vx = x0;
        D_1F8000F8.vx = xl;
        D_1F8000F0.vz = zl;
        D_1F8000F8.vz = z1;
        pz            = D_1F8000C8.vz;
        xl            = x0 + (pz - z0) * w / d;
        px            = D_1F8000C8.vx;
        zl            = z0 + (px - x0) * d / w;
        if (px < xl || zl < pz)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

sint32 func_8004E750(sint16 *rect, sint32 kind)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 w;
    sint32 d;
    sint32 xl;
    sint32 zl;
    sint32 cx;
    sint32 cz;
    sint32 px;
    sint32 pz;
    SVECTOR *pos;

    if (kind != 0x35)
    {
        x0 = rect[0] -= D_1F800124_box.max_2;
        x1 = rect[1] += D_1F800124_box.min_0;
        z0 = rect[2] -= D_1F800124_box.max_6;
        z1 = rect[3] += D_1F800124_box.min_4;
    }
    else
    {
        x0 = rect[0] += D_1F800124_box.max_2;
        x1 = rect[1] -= D_1F800124_box.min_0;
        z0 = rect[2] += D_1F800124_box.max_6;
        z1 = rect[3] -= D_1F800124_box.min_4;
    }
    pos = &D_1F8000C0;
    cz  = pos->vz;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x1 - (cz - z0) * w / d - 4;
    if (xl < x0)
    {
        xl = x0;
    }
    cx = pos->vx;
    zl = z1 - (cx - x0) * d / w - 4;
    if (zl < z0)
    {
        zl = z0;
    }
    if (xl < cx && cx < x1 && zl < cz && cz < z1)
    {
        D_1F8000F0.vx = xl;
        D_1F8000F8.vx = x1;
        D_1F8000F0.vz = zl;
        D_1F8000F8.vz = z1;
        pos           = &D_1F8000C8;
        pz            = pos->vz;
        xl            = x1 - (pz - z0) * w / d;
        px            = pos->vx;
        zl            = z1 - (px - x0) * d / w;
        if (xl < px || zl < pz)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

sint32 func_8004EA10(sint16 *rect, sint32 kind)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 w;
    sint32 d;
    sint32 xl;
    sint32 zl;
    sint32 cx;
    sint32 cz;
    sint32 px;
    sint32 pz;
    SVECTOR *pos;

    if (kind != 0x45)
    {
        x0 = rect[0] += D_1F800124_box.max_2;
        x1 = rect[1] -= D_1F800124_box.min_0;
        z0 = rect[2] += D_1F800124_box.max_6;
        z1 = rect[3] -= D_1F800124_box.min_4;
    }
    else
    {
        x0 = rect[0] -= D_1F800124_box.max_2;
        x1 = rect[1] += D_1F800124_box.min_0;
        z0 = rect[2] -= D_1F800124_box.max_6;
        z1 = rect[3] += D_1F800124_box.min_4;
    }
    pos = &D_1F8000C0;
    cz  = pos->vz;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x1 - (cz - z0) * w / d + 4;
    if (x1 < xl)
    {
        xl = x1;
    }
    cx = pos->vx;
    zl = z1 - (cx - x0) * d / w + 4;
    if (z1 < zl)
    {
        zl = z1;
    }
    if (x0 < cx && cx < xl && z0 < cz && cz < zl)
    {
        D_1F8000F0.vx = x0;
        D_1F8000F8.vx = xl;
        D_1F8000F0.vz = z0;
        D_1F8000F8.vz = zl;
        pos           = &D_1F8000C8;
        pz            = pos->vz;
        xl            = x1 - (pz - z0) * w / d;
        px            = pos->vx;
        zl            = z1 - (px - x0) * d / w;
        if (px < xl || pz < zl)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

sint32 func_8004ECD0(sint16 *rect, sint32 kind)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 w;
    sint32 d;
    sint32 xl;
    sint32 zl;
    sint32 cx;
    sint32 cz;
    sint32 px;
    sint32 pz;
    SVECTOR *pos;

    if (kind != 0x55)
    {
        x0 = rect[0] -= D_1F800124_box.max_2;
        x1 = rect[1] += D_1F800124_box.min_0;
        z0 = rect[2] += D_1F800124_box.max_6;
        z1 = rect[3] -= D_1F800124_box.min_4;
    }
    else
    {
        x0 = rect[0] += D_1F800124_box.max_2;
        x1 = rect[1] -= D_1F800124_box.min_0;
        z0 = rect[2] -= D_1F800124_box.max_6;
        z1 = rect[3] += D_1F800124_box.min_4;
    }
    pos = &D_1F8000C0;
    cz  = pos->vz;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x0 + (cz - z0) * w / d - 4;
    if (xl < x0)
    {
        xl = x0;
    }
    cx = pos->vx;
    zl = z0 + (cx - x0) * d / w + 4;
    if (z1 < zl)
    {
        zl = z1;
    }
    if (xl < cx && cx < x1 && z0 < cz && cz < zl)
    {
        D_1F8000F0.vx = xl;
        D_1F8000F8.vx = x1;
        D_1F8000F0.vz = z0;
        D_1F8000F8.vz = zl;
        pos           = &D_1F8000C8;
        pz            = pos->vz;
        xl            = x0 + (pz - z0) * w / d;
        px            = pos->vx;
        zl            = z0 + (px - x0) * d / w;
        if (xl < px || pz < zl)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

// Block test of Block_test_tbl (kind 6): shrinks the block's rectangle by the box in D_1F800124_box,
// then cuts its corners (an octagon: each side moves in by the point's distance from the middle
// of the other axis, scaled to the rectangle); if D_1F8000C0 is inside, saves the corners in
// D_1F8000F0/F8 and returns 1, else 0.
sint32 func_8004EF90(sint16 *rect)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 dx;
    sint32 dz;

    x0 = rect[0] -= D_1F800124_box.max_2;
    x1 = rect[1] -= D_1F800124_box.min_0;
    z0 = rect[2] -= D_1F800124_box.max_6;
    z1 = rect[3] -= D_1F800124_box.min_4;
    dx = ABS(z0 + (z1 - z0) / 2 - D_1F8000C0.vz) * (x1 - x0) / (z1 - z0);
    dz = ABS(x0 + (x1 - x0) / 2 - D_1F8000C0.vx) * (z1 - z0) / (x1 - x0);
    if (x0 + dx < D_1F8000C0.vx && D_1F8000C0.vx < x1 - dx && z0 + dz < D_1F8000C0.vz && D_1F8000C0.vz < z1 - dz)
    {
        D_1F8000F0.vx = x0 + dx;
        D_1F8000F8.vx = x1 - dx;
        D_1F8000F0.vz = z0 + dz;
        D_1F8000F8.vz = z1 - dz;
        return 1;
    }
    return 0;
}

// Block test of Block_test_tbl: an octagon, like func_8004EF90, but tested on the shrunk rectangle
// first and with the corner cuts scaled by 0x16A1 (sqrt(2) in 4.12). On a hit, saves the cut
// rectangle widened by 0x35/256 of the block's size in D_1F8000F0/F8 and returns 1, else 0. The
// x and the far z bounds are clamped to the rectangle; the near z bound is set to z0 whenever
// it lies inside (sic: the comparison is the other way round).
sint32 func_8004F150(sint16 *rect)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 cut_x;
    sint32 cut_z;

    x0 = rect[0] -= D_1F800124_box.max_2;
    x1 = rect[1] -= D_1F800124_box.min_0;
    z0 = rect[2] -= D_1F800124_box.max_6;
    z1 = rect[3] -= D_1F800124_box.min_4;
    if (x0 < D_1F8000C0.vx && D_1F8000C0.vx < x1 && z0 < D_1F8000C0.vz && D_1F8000C0.vz < z1)
    {
        cut_x = (ABS(z0 + (z1 - z0) / 2 - D_1F8000C0.vz) * (x1 - x0) / (z1 - z0) * 0x16A1) >> 12;
        cut_z = (ABS(x0 + (x1 - x0) / 2 - D_1F8000C0.vx) * (z1 - z0) / (x1 - x0) * 0x16A1) >> 12;
        if (x0 + cut_x < D_1F8000C0.vx && D_1F8000C0.vx < x1 - cut_x && z0 + cut_z < D_1F8000C0.vz && D_1F8000C0.vz < z1 - cut_z)
        {
            D_1F8000F0.vx = x0 + cut_x - (((x1 - x0) * 0x35) >> 8);
            if (D_1F8000F0.vx < x0)
            {
                D_1F8000F0.vx = x0;
            }
            D_1F8000F8.vx = x1 - cut_x + (((x1 - x0) * 0x35) >> 8);
            if (x1 < D_1F8000F8.vx)
            {
                D_1F8000F8.vx = x1;
            }
            D_1F8000F0.vz = z0 + cut_z - (((z1 - z0) * 0x35) >> 8);
            if (z0 < D_1F8000F0.vz)
            {
                D_1F8000F0.vz = z0;
            }
            D_1F8000F8.vz = z1 - cut_z + (((z1 - z0) * 0x35) >> 8);
            if (z1 < D_1F8000F8.vz)
            {
                D_1F8000F8.vz = z1;
            }
            return 1;
        }
    }
    return 0;
}

// Pushes pos out of the last hit rectangle (D_1F8000F0/F8) on the shortest allowed axis: each
// axis's push goes to the face against the move (D_1F8000D0; y to the top also when mode has bit
// 1), and is allowed by func_80050A24/A90/B68 when mode has bit 4/5/6, else by func_80050808/8BC/970
// (y masked by mode). Returns func_80050BF4's result for a y push, 0 for an x or z push, and
// block_push_out's when no axis is allowed.
sint32 func_8004F44C(SVECTOR *pos, SVECTOR *prev, sint32 mode)
{
    SVECTOR push;
    sint32 hit_x;
    sint32 hit_z;
    sint32 hit_y;

    if (D_1F8000D0.vx >= 0)
    {
        push.vx = D_1F8000F0.vx - D_1F8000C0.vx;
    }
    else
    {
        push.vx = D_1F8000F8.vx - D_1F8000C0.vx;
    }
    if (D_1F8000D0.vz >= 0)
    {
        push.vz = D_1F8000F0.vz - D_1F8000C0.vz;
    }
    else
    {
        push.vz = D_1F8000F8.vz - D_1F8000C0.vz;
    }
    if (D_1F8000D0.vy >= 0 || (mode & 2))
    {
        push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
    }
    else
    {
        push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
    }
    if (mode & 0x10)
    {
        hit_x = func_80050A24(&push);
    }
    else
    {
        hit_x = func_80050808(&push);
    }
    if (mode & 0x20)
    {
        hit_z = func_80050A90(&push);
    }
    else
    {
        hit_z = func_800508BC(&push);
    }
    if (mode & 0x40)
    {
        hit_y = func_80050B68(&push);
    }
    else
    {
        hit_y = func_80050970(&push) & mode;
    }
    if (hit_x == 0 && hit_z == 0 && hit_y == 0)
    {
        return block_push_out(pos, prev, mode);
    }
    if (hit_x == 0)
    {
        if (hit_z != 0 && (hit_y == 0 || ABS(push.vy) > ABS(push.vz)))
        {
            // The do/while (0) is needed: it ranks pos above hit_x in GCC's register choice.
            do
            {
                pos->vz += push.vz;
                D_1F80010C[2] = -push.vz;
                func_80050BB4(&push);
            } while (0);
            goto done;
        }
    }
    else if (hit_z == 0)
    {
        if (hit_y == 0 || ABS(push.vy) > ABS(push.vx))
        {
            pos->vx += push.vx;
            D_1F80010C[0] = -push.vx;
            func_80050B74(&push);
            goto done;
        }
    }
    else
    {
        goto both;
    }
    pos->vy += push.vy;
    D_1F800100.vy = -push.vy;
    return func_80050BF4(&push);

both:
    if (hit_y != 0)
    {
        if (ABS(push.vy) < (ABS(push.vx) < ABS(push.vz) ? ABS(push.vx) : ABS(push.vz)))
        {
            pos->vy += push.vy;
            if (!(mode & 2))
            {
                D_1F800100.vy = -push.vy;
            }
            return func_80050BF4(&push);
        }
    }
    if (ABS(push.vx) < ABS(push.vz))
    {
        pos->vx += push.vx;
        D_1F80010C[0] = D_1F800100.vx = -push.vx;
        func_80050B74(&push);
        goto done;
    }
    pos->vz += push.vz;
    D_1F80010C[2] = D_1F800100.vz = -push.vz;
    func_80050BB4(&push);
done:
    // One shared return: with their own, the x-only path cross-jumps to the wrong tail.
    return 0;
}

// Pushes pos out of the last hit rectangle (D_1F8000F0/F8) along z (to its z0 side when side is
// 0, else z1) or along y (top when moving up), whichever is shorter and still allowed
// (func_80050A90, func_80050AFC); returns func_80050BF4's result for a y push, 0 for a z push.
// When neither axis is allowed, pushes to the nearer face on each axis and moves prev with pos.
sint32 func_8004F8BC(SVECTOR *pos, SVECTOR *prev, sint32 side)
{
    SVECTOR push;
    sint32 hit;
    sint32 hit_y;

    if (side == 0)
    {
        push.vz = D_1F8000F0.vz - D_1F8000C0.vz;
    }
    else
    {
        push.vz = D_1F8000F8.vz - D_1F8000C0.vz;
    }
    if (D_1F8000D0.vy >= 0)
    {
        push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
    }
    else
    {
        push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
    }
    hit   = func_80050A90(&push);
    hit_y = func_80050AFC(&push);
    if (hit != 0 || hit_y != 0)
    {
        if (hit_y != 0 && ABS(push.vy) < ABS(push.vz))
        {
            pos->vy += push.vy;
            D_1F800100.vy = -push.vy;
            return func_80050BF4(&push);
        }
        pos->vz += push.vz;
        D_1F800100.vz = -push.vz;
        func_80050BB4(&push);
        return 0;
    }
    else
    {
        if (ABS(D_1F8000F0.vy - D_1F8000C0.vy) < ABS(D_1F8000F8.vy - D_1F8000C0.vy))
        {
            push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
        }
        else
        {
            push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
        }
        if (ABS(D_1F8000F0.vz - D_1F8000C0.vz) < ABS(D_1F8000F8.vz - D_1F8000C0.vz))
        {
            push.vz = D_1F8000F0.vz - D_1F8000C0.vz;
        }
        else
        {
            push.vz = D_1F8000F8.vz - D_1F8000C0.vz;
        }
        if (ABS(push.vy) < ABS(push.vz))
        {
            pos->vy += push.vy;
            prev->vy += push.vy;
            return func_80050BF4(&push);
        }
        pos->vz += push.vz;
        prev->vz += push.vz;
        func_80050BB4(&push);
        return 0;
    }
}

// func_8004F8BC along x: side 0 pushes to the rectangle's x1 side, else x0.
sint32 func_8004FBE8(SVECTOR *pos, SVECTOR *prev, sint32 side)
{
    SVECTOR push;
    sint32 hit;
    sint32 hit_y;

    if (side != 0)
    {
        push.vx = D_1F8000F0.vx - D_1F8000C0.vx;
    }
    else
    {
        push.vx = D_1F8000F8.vx - D_1F8000C0.vx;
    }
    if (D_1F8000D0.vy >= 0)
    {
        push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
    }
    else
    {
        push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
    }
    hit   = func_80050A24(&push);
    hit_y = func_80050AFC(&push);
    if (hit != 0 || hit_y != 0)
    {
        if (hit_y != 0 && ABS(push.vy) < ABS(push.vx))
        {
            pos->vy += push.vy;
            D_1F800100.vy = -push.vy;
            return func_80050BF4(&push);
        }
        pos->vx += push.vx;
        D_1F800100.vx = -push.vx;
        func_80050B74(&push);
        return 0;
    }
    else
    {
        if (ABS(D_1F8000F0.vx - D_1F8000C0.vx) < ABS(D_1F8000F8.vx - D_1F8000C0.vx))
        {
            push.vx = D_1F8000F0.vx - D_1F8000C0.vx;
        }
        else
        {
            push.vx = D_1F8000F8.vx - D_1F8000C0.vx;
        }
        if (ABS(D_1F8000F0.vy - D_1F8000C0.vy) < ABS(D_1F8000F8.vy - D_1F8000C0.vy))
        {
            push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
        }
        else
        {
            push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
        }
        if (ABS(push.vy) < ABS(push.vx))
        {
            pos->vy += push.vy;
            prev->vy += push.vy;
            return func_80050BF4(&push);
        }
        pos->vx += push.vx;
        prev->vx += push.vx;
        func_80050B74(&push);
        return 0;
    }
}

// func_800501E8 for a rounded corner: pushes pos (moved 4 toward the corner) out along the line
// to the corner of the last hit rectangle (D_1F8000F0/F8), or up or down as func_800501E8 does.
sint32 func_8004FF14(SVECTOR *pos, sint32 corner)
{
    SVECTOR push;
    sint32 c;
    sint32 dx;
    sint32 dz;
    sint32 prod;
    sint32 len;
    sint32 dz0;

    // The corner's coordinate goes through c, so GCC keeps F8 - (x - 4) unfolded.
    switch (corner)
    {
        case 0:
            c  = pos->vx - 4;
            dx = D_1F8000F8.vx - c;
            c  = pos->vz + 4;
            dz = D_1F8000F0.vz - c;
            break;
        case 1:
            c  = pos->vx + 4;
            dx = D_1F8000F0.vx - c;
            c  = pos->vz + 4;
            dz = D_1F8000F0.vz - c;
            break;
        case 2:
            c  = pos->vx - 4;
            dx = D_1F8000F8.vx - c;
            c  = pos->vz - 4;
            dz = D_1F8000F8.vz - c;
            break;
        case 3:
            c  = pos->vx + 4;
            dx = D_1F8000F0.vx - c;
            c  = pos->vz - 4;
            dz = D_1F8000F8.vz - c;
            break;
        default:
            return 0;
    }
    // dz0 keeps the corner's z distance: multiplying into dz itself swaps the mult operands.
    prod    = dx * dz;
    len     = dx * dx + dz * dz;
    dz0     = dz;
    dz      = prod * dz0;
    push.vx = dz / len;
    push.vz = prod * dx / len;
    if (D_1F8000D0.vy > 0)
    {
        push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
    }
    else
    {
        push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
    }
    if (D_1F8000D0.vy == 0 || ABS(push.vx) < ABS(push.vy) || ABS(push.vz) < ABS(push.vy))
    {
        pos->vx += push.vx;
        pos->vz += push.vz;
        D_1F80010C[0] = -push.vx;
        D_1F80010C[2] = -push.vz;
        func_80050B74(&push);
        func_80050BB4(&push);
        return 0;
    }
    pos->vy += push.vy;
    D_1F8000FF    = 0x20;
    D_1F800100.vy = -push.vy;
    return 1;
}

// Pushes pos out of the last hit rectangle (D_1F8000F0/F8) at corner (0-3): sideways along the
// nearer axis (returns 0), or, when moving vertically (D_1F8000D0.vy) and the height to the
// rectangle's top or bottom is the smaller push, up or down (returns 1).
sint32 func_800501E8(SVECTOR *pos, sint32 corner)
{
    SVECTOR push;
    sint32 dx;
    sint32 dz;
    sint32 adx;
    sint32 adz;

    switch (corner)
    {
        case 0:
            dx = D_1F8000F8.vx - pos->vx;
            dz = D_1F8000F0.vz - pos->vz;
            break;
        case 1:
            dx = D_1F8000F0.vx - pos->vx;
            dz = D_1F8000F0.vz - pos->vz;
            break;
        case 2:
            dx = D_1F8000F8.vx - pos->vx;
            dz = D_1F8000F8.vz - pos->vz;
            break;
        case 3:
            dx = D_1F8000F0.vx - pos->vx;
            dz = D_1F8000F8.vz - pos->vz;
            break;
        default:
            return 0;
    }
    adx = ABS(dx);
    adz = ABS(dz);
    if (adz < adx)
    {
        if (dx <= 0)
        {
            push.vx = -adz;
        }
        else
        {
            push.vx = adz;
        }
        push.vz = dz;
    }
    else
    {
        push.vx = dx;
        if (dz <= 0)
        {
            push.vz = -adx;
        }
        else
        {
            push.vz = adx;
        }
    }
    if (D_1F8000D0.vy > 0)
    {
        push.vy = D_1F8000F0.vy - D_1F8000C0.vy;
    }
    else
    {
        push.vy = D_1F8000F8.vy - D_1F8000C0.vy;
    }
    if (D_1F8000D0.vy == 0 || ABS(push.vx) < ABS(push.vy))
    {
        pos->vx += push.vx;
        pos->vz += push.vz;
        func_80050B74(&push);
        func_80050BB4(&push);
        return 0;
    }
    pos->vy += push.vy;
    D_1F8000FF    = 0x20;
    D_1F800100.vy = -push.vy;
    return 1;
}

// Pushes pos (and prev by the same amount) out of the box D_1F8000F0..D_1F8000F8 through its
// nearest face: up or down (only with mode bit 0, when that is the shortest way and y is not
// blocked in D_1F8000FF; mode bit 1 always takes the bottom face), else along x or z, whichever
// is shorter and not blocked. Returns func_80050BF4's result for a y push, else 0.
sint32 block_push_out(SVECTOR *pos, SVECTOR *prev, sint32 mode)
{
    SVECTOR push;

    if (ABS(D_1F8000F0.vx - pos->vx) < ABS(D_1F8000F8.vx - pos->vx))
    {
        push.vx = D_1F8000F0.vx - pos->vx;
    }
    else
    {
        push.vx = D_1F8000F8.vx - pos->vx;
    }
    if (ABS(D_1F8000F0.vz - pos->vz) < ABS(D_1F8000F8.vz - pos->vz))
    {
        push.vz = D_1F8000F0.vz - pos->vz;
    }
    else
    {
        push.vz = D_1F8000F8.vz - pos->vz;
    }
    if (mode & 2)
    {
        push.vy = D_1F8000F0.vy - pos->vy;
    }
    else if (ABS(D_1F8000F0.vy - pos->vy) < ABS(D_1F8000F8.vy - pos->vy))
    {
        push.vy = D_1F8000F0.vy - pos->vy;
    }
    else
    {
        push.vy = D_1F8000F8.vy - pos->vy;
    }
    if (mode & 1)
    {
        if (ABS(push.vy) < ((ABS(push.vx) < ABS(push.vz)) ? ABS(push.vx) : ABS(push.vz)) && !(D_1F8000FF & 0x30))
        {
            pos->vy += push.vy;
            prev->vy += push.vy;
            D_1F800100.vy = -push.vy;
            return func_80050BF4(&push);
        }
    }
    if (!(ABS(push.vx) > ABS(push.vz)) && !(D_1F8000FF & 3))
    {
        goto push_x;
    }
    if (!(ABS(push.vx) < ABS(push.vz)) && !(D_1F8000FF & 0xC))
    {
        goto push_z;
    }
    if (ABS(push.vx) < ABS(push.vz))
    {
    push_x:
        pos->vx += push.vx;
        prev->vx += push.vx;
        func_80050B74(&push);
        return 0;
    }
push_z:
    pos->vz += push.vz;
    prev->vz += push.vz;
    func_80050BB4(&push);
    return 0;
}

// func_80050A24 with a speed check: 0 also when |D_1F8000D0.vx| < |v->vx|.
sint32 func_80050808(SVECTOR *v)
{
    sint32 blocked;
    sint32 limit;
    sint32 speed;
    sint32 result;

    blocked = 0;
    limit   = D_1F8000D0.vx;
    if (limit == 0)
    {
        blocked = 1;
    }
    else
    {
        speed = v->vx;
        if (limit < 0)
        {
            limit = -limit;
        }
        if (speed >= 0 ? limit < speed : limit < -speed)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (v->vx > 0)
        {
            if ((D_1F8000FF & 2) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 1) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

// func_80050A90 with a speed check: 0 also when |D_1F8000D0.vz| < |v->vz|.
sint32 func_800508BC(SVECTOR *v)
{
    sint32 blocked;
    sint32 limit;
    sint32 speed;
    sint32 result;

    blocked = 0;
    limit   = D_1F8000D0.vz;
    if (limit == 0)
    {
        blocked = 1;
    }
    else
    {
        speed = v->vz;
        if (limit < 0)
        {
            limit = -limit;
        }
        if (speed >= 0 ? limit < speed : limit < -speed)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (v->vz > 0)
        {
            if ((D_1F8000FF & 8) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 4) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

// func_80050AFC with a speed check: 0 also when |D_1F8000D0.vy| < |v->vy|.
sint32 func_80050970(SVECTOR *v)
{
    sint32 blocked;
    sint32 limit;
    sint32 speed;
    sint32 result;

    blocked = 0;
    limit   = D_1F8000D0.vy;
    if (limit == 0)
    {
        blocked = 1;
    }
    else
    {
        speed = v->vy;
        if (limit < 0)
        {
            limit = -limit;
        }
        if (speed >= 0 ? limit < speed : limit < -speed)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (v->vy > 0)
        {
            if ((D_1F8000FF & 0x20) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 0x10) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050A24(SVECTOR *v)
{
    sint32 result;

    // result is 0 or 1, but the target has the `result &= 1` (andi) in all three of these.
    result = D_1F8000D0.vx != 0;
    if (result)
    {
        if (v->vx > 0)
        {
            if ((D_1F8000FF & 2) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 1) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050A90(SVECTOR *v)
{
    sint32 result;

    result = D_1F8000D0.vz != 0;
    if (result)
    {
        if (v->vz > 0)
        {
            if ((D_1F8000FF & 8) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 4) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050AFC(SVECTOR *v)
{
    sint32 result;

    result = D_1F8000D0.vy != 0;
    if (result)
    {
        if (v->vy > 0)
        {
            if ((D_1F8000FF & 0x20) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 0x10) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050B68(SVECTOR *v)
{
    return v->vy != 0;
}

void func_80050B74(SVECTOR *v)
{
    if (D_1F8000FF & 3)
    {
        D_1F800106[0] = 0;
    }
    if (v->vx > 0)
    {
        D_1F8000FF = 1;
    }
    else
    {
        D_1F8000FF = 2;
    }
}

void func_80050BB4(SVECTOR *v)
{
    if (D_1F8000FF & 0xC)
    {
        D_1F800106[2] = 0;
    }
    if (v->vz > 0)
    {
        D_1F8000FF = 4;
    }
    else
    {
        D_1F8000FF = 8;
    }
}

sint32 func_80050BF4(SVECTOR *v)
{
    if (v->vy > 0)
    {
        D_1F8000FF = 0x10;
        return 0;
    }
    D_1F8000FF = 0x20;
    return 1;
}

// Acts on the special hit in front of pl (front_hit_search, with pl's box): exits (kind 1 walks
// through, keeping pl's offset; 2, 4-6 and 8 are doors, 3 a door that opens a scene), and event
// triggers that hand a value to func_80063BC8 or set scene or game flags. Only a player
// (kind_1's high nibble 0) not in flags_BD's scene control uses exits; the others need
// func_80051970 (the action button). Returns the hit's kind, or 0 if there is none.
sint32 Front_hit_event(PL_WORK *pl)
{
    FRONT_HIT ev;
    PL_WORK *obj;
    MAP_EXIT *exit;
    sint32 kind;
    uint16 flags;
    sint32 dir;

    if (front_hit_search((MODEL_WORK *)pl, (VECTOR *)pl->hit_78, &ev) == 0)
    {
        return 0;
    }
    obj = NULL;
    if (!(pl->kind_1 & 0xF0))
    {
        obj = pl;
        if (obj->flags_BD != 0)
        {
            return 0;
        }
    }
    kind  = ev.kind;
    flags = ev.flags;
    switch (kind)
    {
        case 1:
            if (obj == NULL)
            {
                break;
            }
            for (exit = Map_exits; exit->id != -1; exit++)
            {
                if (ev.pos.vx == exit->pos.vx && ev.pos.vy == exit->pos.vy && ev.pos.vz == exit->pos.vz)
                {
                    D_800C3558.mode_14  = -1;
                    D_800C3558.pos.vx   = exit->dest.vx + obj->pos.vx - exit->pos.vx;
                    D_800C3558.pos.vy   = obj->pos.vy;
                    D_800C3558.pos.vz   = exit->dest.vz + obj->pos.vz - exit->pos.vz;
                    D_800C3558.ang_y    = obj->ang.vy;
                    D_800C3558.stage_16 = exit->stage_6;
                    D_800C3558.area_17  = exit->area_7;
                    D_800C3558.unk15    = 0;
                    break;
                }
            }
            break;
        case 2:
        case 4:
        case 5:
        case 6:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            for (exit = Map_exits; exit->id != -1; exit++)
            {
                if (ev.pos.vx == exit->pos.vx && ev.pos.vy == exit->pos.vy && ev.pos.vz == exit->pos.vz &&
                    ((ev.pos.pad - exit->pos.pad + 0x200) & 0xFFF) <= 0x400)
                {
                    if (func_800519E4(exit) != 0)
                    {
                        break;
                    }
                    if (func_80051A78(exit) != 0)
                    {
                        break;
                    }
                    D_800C3558.mode_14  = 2;
                    D_800C3558.pos      = exit->dest;
                    D_800C3558.ang_y    = exit->dest.pad;
                    D_800C3558.stage_16 = exit->stage_6;
                    D_800C3558.area_17  = exit->area_7;
                    D_800C3558.unk15    = 0;
                    D_800C3558.unk19    = 0x15;
                    D_800C3558.unk18    = 2;
                    func_8001F6C4();
                    break;
                }
            }
            break;
        case 3:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            // The do/while (0) puts the search one loop level deeper: GCC weighs references by
            // loop depth, and only this ranks the exit pointer above ev.pos.vz.
            do
            {
                for (exit = Map_exits; exit->id != -1; exit++)
                {
                    if (ev.pos.vx == exit->pos.vx && ev.pos.vy == exit->pos.vy && ev.pos.vz == exit->pos.vz &&
                        !((ev.pos.pad - exit->pos.pad + 0x200) & 0x400))
                    {
                        // Only from the side the hit faces.
                        dir = ((ev.pos.pad + 0x200) / 0x400) & 3;
                        if (dir == 0 && pl->pos.vz < ev.pos.vz)
                        {
                            continue;
                        }
                        if (dir == 1 && pl->pos.vx < ev.pos.vx)
                        {
                            continue;
                        }
                        if (dir == 2 && ev.pos.vz < pl->pos.vz)
                        {
                            continue;
                        }
                        if (dir == 3 && ev.pos.vx < pl->pos.vx)
                        {
                            continue;
                        }
                        if (func_800519E4(exit) != 0)
                        {
                            break;
                        }
                        if (exit->id & 0x8000)
                        {
                            D_800C3558.pos_00   = ev.pos;
                            D_800C3558.pos      = exit->dest;
                            D_800C3558.ang_y_10 = exit->pos.pad;
                            D_800C3558.ang_y    = exit->dest.pad;
                            D_800C3558.stage_16 = exit->stage_6;
                            D_800C3558.area_17  = exit->area_7;
                            D_800C3558.unk19    = 10;
                            D_800C3558.unk15    = 0;
                            D_800C3558.unk18    = 2;
                            Obj_work_flag_change(0x56, 5);
                            Sce_flag_on(0x7B0);
                            func_8001F6C4();
                            break;
                        }
                        Sce_flag_on(0x7B1);
                        break;
                    }
                }
            } while (0);
            break;
        case 8:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            for (exit = Map_exits; exit->id != -1; exit++)
            {
                if (ev.pos.vx == exit->pos.vx && ev.pos.vy == exit->pos.vy && ev.pos.vz == exit->pos.vz)
                {
                    if (func_800519E4(exit) != 0)
                    {
                        break;
                    }
                    D_800C3558.mode_14  = 2;
                    D_800C3558.pos      = exit->dest;
                    D_800C3558.ang_y    = exit->dest.pad;
                    D_800C3558.stage_16 = exit->stage_6;
                    D_800C3558.area_17  = exit->area_7;
                    D_800C3558.unk15    = 0;
                    D_800C3558.unk19    = 0x15;
                    D_800C3558.unk18    = 2;
                    func_8001F6C4();
                    break;
                }
            }
            break;
        case 0x10:
            if (pl->field_74 != 0)
            {
                return kind;
            }
            if (Sce_flag_test(0x60F) != 0)
            {
                pl->pos.vx += 8;
                pl->pos_l.vx += 0x80000;
            }
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x2A:
        case 0x2B:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x39:
        case 0x3A:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x55:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0, 0, D_8008AA58[kind] + (flags & 0xF));
            }
            break;
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0x10, 0, D_8008AA58[kind] + (flags & 0xF));
            }
            break;
        case 0x2C:
        case 0x2D:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0, 0, D_8008AA6C[flags & 0xF]);
            }
            break;
        case 0x2F:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0, 0, D_8008AA44[flags & 0xF]);
            }
            break;
        case 0x38:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0, 0, D_8008AA60[flags & 0xF]);
            }
            break;
        case 0x3B:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0, 0, D_8008AA68[flags & 0xF]);
            }
            break;
        case 0x44:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0, 0, D_8008AA50[flags & 0xF]);
            }
            break;
        case 0x50:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            if ((flags & 0xFF) == 0)
            {
                func_80063BC8(NULL, 0, 0, 6);
            }
            else if (Game_work.stage_no == 0xE)
            {
                if (Sce_flag_test(0x1E) == 0)
                {
                    Sce_flag_on(0x608);
                }
            }
            else
            {
                if (Sce_flag_test(0x27) == 0)
                {
                    Sce_flag_on(0x605);
                }
            }
            break;
        case 0x52:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            if ((flags & 0xFF) == 0)
            {
                if (Sce_flag_test(0x44) == 0)
                {
                    func_80063BC8(NULL, 0, 0, 0xC);
                }
            }
            else
            {
                if (Sce_flag_test(0x49) == 0)
                {
                    func_80063BC8(NULL, 0, 0, 0x11);
                }
            }
            break;
        case 0x53:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            if ((flags & 0xFF) != 0)
            {
                break;
            }
            if (Sce_flag_test(0x56) == 0)
            {
                Game_work.unk174.h[3] |= 0x40;
            }
            else
            {
                func_80063BC8(NULL, 0, 0, 1);
            }
            break;
        case 0x54:
            if (func_80051970(obj) != 0)
            {
                Game_work.unk174.w[0] |= 1 << flags;
            }
            break;
        case 0x56:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            if ((flags & 0xFF) == 0)
            {
                func_80063BC8(NULL, 0, 0, 0x1C);
            }
            break;
        case 0x60:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(NULL, 0x10, 0, D_8008AA70[flags & 0xF]);
            }
            break;
    }
    return kind;
}

// Looks for a special STG_HIT (kind 0x100 and up) around obj, with the box ofs: in the map blocks
// around obj's position, the first such hit whose area holds the point (0x40 ahead of obj along
// its facing when the hit's flags have bit 15 set, else obj's position) and whose height range,
// fitted by slope_fit, holds its height. Fills out with it and returns 1, or clears out's kind
// and flags and returns 0.
sint32 front_hit_search(MODEL_WORK *obj, VECTOR *ofs, FRONT_HIT *out)
{
    SVECTOR base;
    SVECTOR ahead;
    SVECTOR org;
    sint16 box[6];
    SVECTOR dir;
    SVECTOR moved;
    MATRIX mtx;
    sint32 n;
    sint32 val;
    sint32 left;
    sint32 cy;
    MAP_BLOCK *block;
    STG_MODEL *model;
    STG_AREA *area;
    STG_HIT *hit;

    ahead = obj->pos;
    base  = ahead;
    n     = func_8004B1E0(&base, 0);
    MATRIX_IDENTITY_W(&mtx);
    RotMatrixY(obj->ang.vy, &mtx);
    dir.vx = 0;
    dir.vy = 0;
    dir.vz = -0x40;
    ApplyMatrixSV(&mtx, &dir, &moved);
    ahead.vx += moved.vx;
    ahead.vz += moved.vz;
    if (ofs != NULL)
    {
        D_1F800124.vx = ofs->vx;
        D_1F800124.vy = ofs->vy;
        D_1F800124.vz = ofs->vz;
    }
    else
    {
        D_1F800124.vx = 0;
        D_1F800124.vy = 0;
        D_1F800124.vz = 0;
    }
    while (n-- != 0)
    {
        val = func_80048CEC(D_1F800118[n]);
        if (val <= 0)
        {
            continue;
        }
        block = &Map_blocks[val];
        model = (STG_MODEL *)(block->model & 0xFFFFFF);
        // The do/while (0)s are needed: they rank left, area and hit in GCC's register choice
        // (references weigh by loop depth).
        if (block->pos.pad & 0xFFF)
        {
            do
            {
                do
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                area = model->areas;
                            } while (0);
                        } while (0);
                    } while (0);
                } while (0);
            } while (0);
        }
        else
        {
            do
            {
                do
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                area = model->areas_0;
                            } while (0);
                        } while (0);
                    } while (0);
                } while (0);
            } while (0);
        }
        org.vx = block->pos.vx;
        org.vy = block->pos.vy;
        org.vz = block->pos.vz;
        for (; area->hits != NULL; area++)
        {
            do
            {
                do
                {
                    box[0] = org.vx + area->x0;
                    box[1] = org.vx + area->x1;
                    box[2] = org.vz + area->z0;
                    box[3] = org.vz + area->z1;
                } while (0);
            } while (0);
            hit = area->hits;
            if (hit->kind < 0x100)
            {
                continue;
            }
            if (hit->flags & 0x8000)
            {
                D_1F8000C0 = ahead;
            }
            else
            {
                D_1F8000C0 = base;
            }
            if (((BLOCK_TEST_RECT_FUNC)Block_test_tbl[(hit->kind & 0xF0) >> 4])(box) == 0)
            {
                continue;
            }
            do
            {
                left = area->count;
            } while (0);
            do
            {
                box[4] = org.vy + hit->y0 - D_1F800124_box.max_A;
                box[5] = org.vy + hit->y1 - D_1F800124_box.min_8;
                slope_fit(box, (uint8)hit->kind); // only the low byte: the high one is the hit's id
                cy = D_1F8000C0.vy;
                if (box[4] < cy && cy < box[5])
                {
                    out->pos.vx  = org.vx + (area->x0 + area->x1) / 2;
                    out->pos.vy  = org.vy + (hit->y0 + hit->y1) / 2;
                    out->pos.vz  = org.vz + (area->z0 + area->z1) / 2;
                    out->pos.pad = obj->ang.vy;
                    out->kind    = hit->kind >> 8;
                    out->flags   = hit->flags;
                    return 1;
                }
                hit++;
            } while (--left != 0);
        }
    }
    out->kind  = 0;
    out->flags = 0;
    return 0;
}

sint32 func_80051970(PL_WORK *pl)
{
    uint32 state;
    uint32 keys;

    if (pl != NULL)
    {
        state = pl->routine_9;
        keys  = pl->pad_on;
        if (pl->obj_184 == NULL)
        {
            if (state >= 2 && state != 4)
            {
                return 0;
            }
            if ((keys & pl->keys_124[9]) == 0)
            {
                return 0;
            }
            if (func_8004324C(pl) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

sint32 func_800519E4(MAP_EXIT *exit)
{
    if (Sce_flag_test(0x7E0) == 0)
    {
        if (Sce_flag_test(0x7E0 | (exit->id & 0x1F)) == 0)
        {
            return 0;
        }
    }
    if (Sce_flag_test(0x7C0) != 0)
    {
        return 1;
    }
    if (Sce_flag_test(0x7C0 | (exit->id & 0x1F)) != 0)
    {
        return 1;
    }
    func_80063BC8(NULL, 0, 0, exit->val_4);
    return 1;
}

// The special exits (exit->kind_2): 1 starts scene 0x1B when scene flag 0x2C is set (scenario 0
// only), 2 and 3 start scenes 0x18 and 0x27 once (scene flags 0x28 and 0x29). 1 if one started.
sint32 func_80051A78(MAP_EXIT *exit)
{
    switch (exit->kind_2)
    {
        case 0:
            return 0;
        case 1:
            if (Game_work.sce_no != 0)
            {
                return 0;
            }
            if (Sce_flag_test(0x2C) == 0)
            {
                return 0;
            }
            func_8001DDE4(0x1B);
            return 1;
        case 2:
            if (Sce_flag_test(0x28) != 0)
            {
                return 0;
            }
            Sce_flag_on(0x28);
            func_8001DDE4(0x18);
            return 1;
        case 3:
            if (Sce_flag_test(0x29) != 0)
            {
                return 0;
            }
            Sce_flag_on(0x29);
            func_8001DDE4(0x27);
            return 1;
        default:
            return 0;
    }
}

void func_80051B40(void)
{
    D_80098894 = D_800BC058;
    D_80098898 = D_800BC360;
}

void func_80051B68(MODEL_WORK *obj, sint32 arg1, sint32 arg2, sint32 arg3)
{
    if (obj->routine_0 & 3)
    {
        D_80098894->obj.model = obj;
        D_80098894->kind_4    = arg1;
        D_80098894->part_6    = arg2;
        D_80098894->hit_8     = arg3;
        D_80098894++;
    }
}

void func_80051BAC(MODEL_WORK *obj)
{
    MODEL_WORK **list;

    if (obj->routine_0 & 3)
    {
        list       = D_80098898;
        *list      = obj;
        D_80098898 = list + 1;
    }
    obj->field_7C = 0;
}

// Collides each object of the D_80098898 list against each solid of the D_80098894 list (but
// itself), by the entry's kind (see OBJ_REQ). The first hit is stored in the object's field_7C
// and the object is tested again, up to 9 times in a row. Then both lists are emptied.
void Solid_collide_all(void)
{
    MODEL_WORK **pp;
    OBJ_REQ *req;
    sint32 result;
    sint32 count;
    sint32 kind;
    sint32 part;
    uint32 hit;

    count = 0;
    pp    = D_800BC360;
    while (pp != D_80098898)
    {
        result = 0;
        req    = D_800BC058;
        while (req != D_80098894)
        {
            result = 0;
            if (req->obj.model != *pp)
            {
                kind = req->kind_4;
                part = req->part_6;
                hit  = req->hit_8;
                switch (kind)
                {
                    case 0:
                        result = obj_solid_push_out(req->obj.model, *pp, part, 0);
                        break;
                    case 1:
                        result = func_80051F08(req->obj.model, *pp, req->obj.model, part, hit, 0);
                        break;
                    case 2:
                        result = obj_solid_push_out(req->obj.model, *pp, part, 1);
                        break;
                    case 3:
                        result = func_80051F08(req->obj.model, *pp, req->obj.model, part, hit, 1);
                        break;
                    case 4:
                    case 6:
                        D_8009A770.pos.vx = D_8009A770.old.vx = req->obj.w48->efc.model.pos.vx;
                        D_8009A770.pos.vy = D_8009A770.old.vy = req->obj.w48->efc.model.pos.vy;
                        D_8009A770.pos.vz = D_8009A770.old.vz = req->obj.w48->efc.model.pos.vz;
                        D_8009A770.pos_l.vx = D_8009A770.old_l.vx = D_8009A770.pos.vx << 16;
                        D_8009A770.pos_l.vy = D_8009A770.old_l.vy = D_8009A770.pos.vy << 16;
                        D_8009A770.pos_l.vz = D_8009A770.old_l.vz = D_8009A770.pos.vz << 16;
                        D_8009A770.ang.vx                         = 0;
                        D_8009A770.ang.vy                         = 0;
                        D_8009A770.ang.vz                         = 0;
                        D_8009A770.spd.vx                         = 0;
                        D_8009A770.spd.vy                         = 0;
                        D_8009A770.spd.vz                         = 0;
                        D_8009A770.data_88                        = req->obj.w48->efc.model.data;
                        D_8009A770.hit_78                         = (HIT_ENT *)req->obj.w48->field_44;
                        result                                    = obj_solid_push_out(&D_8009A770, *pp, -1, 1);
                        break;
                    case 5:
                    case 7:
                        D_8009A770.pos.vx = D_8009A770.old.vx = req->obj.w48->efc.model.pos.vx;
                        D_8009A770.pos.vy = D_8009A770.old.vy = req->obj.w48->efc.model.pos.vy;
                        D_8009A770.pos.vz = D_8009A770.old.vz = req->obj.w48->efc.model.pos.vz;
                        D_8009A770.pos_l.vx = D_8009A770.old_l.vx = D_8009A770.pos.vx << 16;
                        D_8009A770.pos_l.vy = D_8009A770.old_l.vy = D_8009A770.pos.vy << 16;
                        D_8009A770.pos_l.vz = D_8009A770.old_l.vz = D_8009A770.pos.vz << 16;
                        D_8009A770.ang.vx                         = 0;
                        D_8009A770.ang.vy                         = 0;
                        D_8009A770.ang.vz                         = 0;
                        D_8009A770.spd.vx                         = 0;
                        D_8009A770.spd.vy                         = 0;
                        D_8009A770.spd.vz                         = 0;
                        D_8009A770.data_88                        = req->obj.w48->efc.model.data;
                        D_8009A770.hit_78                         = (HIT_ENT *)req->obj.w48->field_44;
                        result                                    = func_80051F08(&D_8009A770, *pp, req->obj.model, -1, hit, 1);
                        break;
                }
                if (result != 0)
                {
                    break;
                }
            }
            // The extra loop level keeps req++ ahead of the end test, as the target does.
            do
            {
                req++;
            } while (0);
        }
        if (result != 0)
        {
            (*pp)->field_7C = result;
            if (++count < 9)
            {
                continue;
            }
        }
        count = 0;
        pp++;
    }
    D_80098894 = D_800BC058;
    D_80098898 = D_800BC360;
}

// Collides obj against the solid object solid (standing in for owner, or its part part). If obj
// is not on solid's floor (func_80052674) but was riding owner (field_76, field_C0), it leaves it
// with owner's speed (turned into obj's frame) added to its own and 0x4000 is returned. Otherwise
// obj is carried with solid's move and turn and pushed out of its collision (solid_push_out); a
// side hit against the move hurts player 0 (hit is added to owner_188.hit_0, unk71 is set from the
// side it came from), and obj lands on owner (field_76, field_C0) when it ends on its floor.
// Returns the hit flags of solid_push_out (0 if the point stayed stuck).
sint32 func_80051F08(MODEL_WORK *solid, MODEL_WORK *obj, MODEL_WORK *owner, sint32 part, uint32 hit, sint32 keep)
{
    MATRIX mtx;
    VECTOR cur;
    VECTOR old;
    VECTOR move;
    VECTOR now;
    VECTOR prev;
    VECTOR delta;
    VECTOR push;
    VECTOR zero;
    SVECTOR rot;
    sint32 result;
    sint32 slide;
    sint32 y;
    sint32 old_74;
    sint32 lim;
    SVECTOR unused; // unused; gives the frame its size

    old_74 = obj->field_74;
    func_800536B0(solid, &now, &prev, part);
    func_8004B3C0((VECTOR *)obj->hit_78);
    slide = (func_8002FE74(obj->kind_1) == 0) << 15;
    if (func_80052674(obj, solid, &now, keep, slide) == 0)
    {
        if (obj->field_76 != 0 && owner == obj->field_C0)
        {
            push.vx = solid->spd.vx;
            push.vy = solid->spd.vy;
            push.vz = solid->spd.vz;
            if (keep == 0)
            {
                rot.vx = solid->ang.vx - obj->ang.vx;
                rot.vy = solid->ang.vy - obj->ang.vy;
                rot.vz = solid->ang.vz - obj->ang.vz;
                if (obj->kind_1 == 0)
                {
                    rot.vx += ((PL_WORK *)obj)->unk114;
                    rot.vy += ((PL_WORK *)obj)->unk116;
                    rot.vz += ((PL_WORK *)obj)->unk118;
                }
                RotMatrixYXZ(&rot, &mtx);
                zero.vx = 0;
                zero.vy = 0;
                zero.vz = 0;
                func_800301A8(&mtx, &push, &zero);
            }
            else if (obj->kind_1 == 0)
            {
                rot.vx = ((PL_WORK *)obj)->unk114;
                rot.vy = ((PL_WORK *)obj)->unk116;
                rot.vz = ((PL_WORK *)obj)->unk118;
                RotMatrixYXZ(&rot, &mtx);
                zero.vx = 0;
                zero.vy = 0;
                zero.vz = 0;
                func_800301A8(&mtx, &push, &zero);
            }
            obj->spd.vx += push.vx;
            obj->spd.vz += push.vz;
            if (obj->field_74 != 0)
            {
                obj->spd.vy += push.vy;
            }
            else
            {
                obj->spd.vy += push.vy - 0x200;
            }
            obj->field_76 = 0;
            obj->field_C0 = 0;
            return 0x4000;
        }
        return 0;
    }
    cur        = obj->pos_l;
    old        = obj->old_l;
    move.vx    = cur.vx - old.vx;
    move.vy    = cur.vy - old.vy;
    move.vz    = cur.vz - old.vz;
    delta.vx   = now.vx - prev.vx;
    delta.vy   = now.vy - prev.vy;
    delta.vz   = now.vz - prev.vz;
    D_1F8000F6 = obj->field_74;
    D_1F8000F7 = obj->field_76;
    func_800534E0(solid, obj, &now, &prev, &cur, &old);
    result = solid_push_out(solid, &now, &cur, &old, keep, slide);
    if (result > 0)
    {
        if (move.vx == 0 || (delta.vx ^ move.vx) < 0)
        {
            lim = (delta.vx - move.vx >= 0 ? delta.vx - move.vx : move.vx - delta.vx) - 0x80000;
            if (ABS(move.vx) < lim)
            {
                goto hurt;
            }
        }
        if (move.vy == 0 || (delta.vy ^ move.vy) < 0)
        {
            lim = (delta.vy - move.vy >= 0 ? delta.vy - move.vy : move.vy - delta.vy) - 0x80000;
            if (ABS(move.vy) < lim)
            {
                goto hurt;
            }
        }
        if (move.vz == 0 || (delta.vz ^ move.vz) < 0)
        {
            lim = (delta.vz - move.vz >= 0 ? delta.vz - move.vz : move.vz - delta.vz) - 0x80000;
            if (move.vz >= 0 ? move.vz < lim : -move.vz < lim)
            {
            hurt:
                if (obj->kind_1 == 0 && D_1F8000F7 == 0)
                {
                    ((PL_WORK *)obj)->owner_188.hit_0 = (((PL_WORK *)obj)->owner_188.hit_0 + (hit & 0xFF)) | (hit & ~0xFF);
                    ((PL_WORK *)obj)->unk71 =
                        ((((solid->ang.vy - obj->ang.vy + ((PL_WORK *)obj)->unk116) & 0xFFF) + 0x200) >> 10 & 3) + 1 | 0x80;
                }
            }
        }
        if (D_1F8000F6 == 0 && D_1F8000F7 != 0)
        {
            obj->field_74 = D_1F8000F6;
            obj->field_76 = D_1F8000F7;
            obj->field_C0 = owner;
        }
    }
    else if (result < 0)
    {
        return 0;
    }
    obj->pos_l.vx = cur.vx;
    obj->pos_l.vz = cur.vz;
    if (func_80052674(obj, solid, &now, keep, slide) != 0)
    {
        y = obj->pos_l.vy;
        if (D_80098AC0.vy - 0x40000 < y && y < D_80098AC0.vy + 0x200000 && obj->field_74 == 0)
        {
            obj->pos_l.vy = D_80098AC0.vy;
            obj->field_76 = 1;
            obj->field_C0 = owner;
        }
        else
        {
            obj->pos_l.vy = cur.vy;
        }
    }
    else
    {
        obj->pos_l.vy = cur.vy;
        if (obj->field_76 != 0)
        {
            obj->field_74 = old_74;
            obj->field_76 = 0;
            obj->field_C0 = 0;
        }
    }
    func_80030150(&obj->pos_l, &obj->pos);
    return result;
}

// Calls func_80052644(key, obj) for every live object of the players, the WORK_3C0 pool, the
// WORK_5A4 pool and the SHL_WORK pool (bit 0x80000000 >> n of each pool's mask: slot n is live).
void func_80052528(void *key)
{
    sint32 i;
    uint32 mask;
    PL_WORK *pl;
    WORK_3C0 *w3c0;
    WORK_5A4 *w5a4;
    SHL_WORK *sh;

    mask = D_8009888C;
    pl   = Player_work;
    for (i = 0; i < 2; i++, pl++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, (MODEL_WORK *)pl);
        }
    }
    w3c0 = D_8009F108;
    mask = D_800987E8;
    for (i = 0; i < 16; i++, w3c0++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, (MODEL_WORK *)w3c0);
        }
    }
    w5a4 = D_800C3580;
    mask = D_80098B20;
    for (i = 0; i < 4; i++, w5a4++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, (MODEL_WORK *)w5a4);
        }
    }
    sh   = D_8009CF88;
    mask = D_800987CC;
    for (i = 0; i < 32; i++, sh++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, (MODEL_WORK *)sh);
        }
    }
}

void func_80052644(void *key, MODEL_WORK *obj)
{
    if (obj->field_76 != 0 && key == obj->field_C0)
    {
        obj->field_76 = 0;
        obj->field_C0 = 0;
    }
}

// Puts obj on top of solid's collision (the STG_AREA list its data_88 points to), at pos (solid's
// origin): obj's position is turned into solid's frame (by minus solid's ang) unless keep, then
// the lowest y0 among the hits whose area holds it and whose top is not above it is the floor.
// 0 if there is none or obj is more than 0x20 above it; else sets the floor height in the 16.16
// D_80098AC0, turns it back into pos (unless keep) and returns 1. slide is unused (its callers pass
// the one they give solid_push_out).
sint32 func_80052674(MODEL_WORK *obj, MODEL_WORK *solid, VECTOR *pos, sint32 keep, sint32 slide)
{
    sint16 box[6];
    MATRIX mtx;
    SVECTOR rot;
    STG_AREA *area;
    sint32 count;
    STG_HIT *hit;
    sint32 best;

    best = 0x7FFF;
    if (keep == 0)
    {
        D_80098AC0.vx = obj->pos_l.vx;
        D_80098AC0.vy = obj->pos_l.vy;
        D_80098AC0.vz = obj->pos_l.vz;
        rot.vx        = -solid->ang.vx;
        rot.vy        = -solid->ang.vy;
        rot.vz        = -solid->ang.vz;
        RotMatrix(&rot, &mtx);
        func_800301A8(&mtx, &D_80098AC0, pos);
        func_80030150(&D_80098AC0, &D_1F8000C0);
    }
    else
    {
        D_1F8000C0 = obj->pos;
    }
    func_80030150(pos, &D_1F8000E0);
    area = *(STG_AREA **)solid->data_88;
    while (area->hits != NULL)
    {
        // The do/while (0) ranks the area pointer above hit and count in GCC's register choice.
        do
        {
            box[0] = D_1F8000E0.vx + area->x0;
            box[1] = D_1F8000E0.vx + area->x1;
            box[2] = D_1F8000E0.vz + area->z0;
            box[3] = D_1F8000E0.vz + area->z1;
        } while (0);
        hit = area->hits;
        if (Block_test_tbl[(hit->kind & 0xF0) >> 4](box, hit->kind) != 0)
        {
            count = area->count;
            do
            {
                box[4] = D_1F8000E0.vy + hit->y0;
                box[5] = D_1F8000E0.vy + hit->y1;
                slope_fit(box, hit->kind);
                if (box[4] < best && D_1F8000C0.vy <= box[5])
                {
                    best = box[4];
                }
                hit++;
            } while (--count != 0);
        }
        area++;
    }
    if (best == 0x7FFF || D_1F8000C0.vy < best - 0x20)
    {
        return 0;
    }
    D_80098AC0.vy = best << 16;
    if (keep == 0)
    {
        rot.vx = -rot.vx;
        rot.vy = -rot.vy;
        rot.vz = -rot.vz;
        RotMatrixYXZ(&rot, &mtx);
        func_800301A8(&mtx, &D_80098AC0, pos);
    }
    return 1;
}

// Collides obj against the solid object solid (or its part part): if obj stands on solid's floor
// (func_80052674), carries obj's 16.16 position with solid's move and turn (func_800534E0),
// pushes it out of solid's collision (solid_push_out) and keeps the pushed axes. Returns the hit
// flags of solid_push_out, or 0.
// mtx and delta are unused (func_80051F08 has them too); they give the frame its size.
sint32 obj_solid_push_out(MODEL_WORK *solid, MODEL_WORK *obj, sint32 part, sint32 keep)
{
    MATRIX mtx;
    VECTOR cur;
    VECTOR old;
    VECTOR now;
    VECTOR prev;
    VECTOR delta;
    sint32 result;
    sint32 slide;

    func_800536B0(solid, &now, &prev, part);
    result = 0;
    func_8004B3C0((VECTOR *)obj->hit_78);
    slide = (func_8002FE74(obj->kind_1) == 0) << 15;
    if (func_80052674(obj, solid, &now, keep, slide) != 0)
    {
        cur = obj->pos_l;
        old = obj->old_l;
        func_800534E0(solid, obj, &now, &prev, &cur, &old);
        result = solid_push_out(solid, &now, &cur, &old, keep, slide);
        if (result != 0)
        {
            if (result & 0x300)
            {
                obj->pos_l.vx = cur.vx;
            }
            if (result & 0xC00)
            {
                obj->pos_l.vz = cur.vz;
            }
            if (result & 0x3000)
            {
                obj->pos_l.vy = cur.vy;
            }
            func_80030150(&obj->pos_l, &obj->pos);
        }
    }
    return result;
}

// Collides the move old -> cur (16.16) against solid's collision (the STG_AREA list its data_88
// points to) at now (solid's origin), in solid's frame (turned by minus its ang) unless keep. Hits
// whose flags bit 15 matches slide's are skipped. Pushes the point out with func_8004BDC8, up to 9
// times (0x80000000 if it is still inside). Returns 0 if the point did not move, else the axis it
// moved most along (1/2 x, 3/4 z, 5/6 y, + or -) with a bit per moved axis (0x100/0x200 x, 0x400/
// 0x800 z, 0x1000/0x2000 y), and sets that axis of cur 2 units back from the face.
// The retry loop is a goto: a for (;;) lets GCC hoist slide ^ 0x8000 out of both loops.
sint32 solid_push_out(MODEL_WORK *solid, VECTOR *now, VECTOR *cur, VECTOR *old, sint32 keep, sint32 slide)
{
    MATRIX mtx;
    SVECTOR rot;
    SVECTOR start;
    sint16 box[6];
    sint32 tries;
    STG_AREA *area;
    STG_HIT *hit;
    sint32 count;
    sint32 test;
    sint32 found;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 result;

    tries      = 0;
    D_1F8000FF = 0;
    found      = 0;
    if (keep == 0)
    {
        rot.vx = -solid->ang.vx;
        rot.vy = -solid->ang.vy;
        rot.vz = -solid->ang.vz;
        RotMatrix(&rot, &mtx);
        func_800301A8(&mtx, old, now);
        func_800301A8(&mtx, cur, now);
    }
    func_80030150(now, &D_1F8000E0);
    func_80030150(old, &D_1F8000C8);
    func_80030150(cur, &D_1F8000C0);
    start           = D_1F8000C0;
    D_1F800100_h[0] = 0;
    D_1F800100_h[1] = 0;
    D_1F800100_h[2] = 0;
    D_1F800106[0]   = 0;
    D_1F800106[1]   = 0;
    D_1F800106[2]   = 0;
    D_1F80010C[0]   = 0;
    D_1F80010C[1]   = 0;
    D_1F80010C[2]   = 0;
    D_1F800112[0]   = 0;
    D_1F800112[1]   = 0;
    D_1F800112[2]   = 0;
retry:
    area          = *(STG_AREA **)solid->data_88;
    D_1F8000D0.vx = D_1F8000C0.vx - D_1F8000C8.vx;
    D_1F8000D0.vy = D_1F8000C0.vy - D_1F8000C8.vy;
    D_1F8000D0.vz = D_1F8000C0.vz - D_1F8000C8.vz;
    while (area->hits != NULL)
    {
        // The do/while (0) ranks the area pointer above hit and count in GCC's register choice.
        do
        {
            box[0] = D_1F8000E0.vx + area->x0;
            box[1] = D_1F8000E0.vx + area->x1;
            box[2] = D_1F8000E0.vz + area->z0;
            box[3] = D_1F8000E0.vz + area->z1;
        } while (0);
        hit  = area->hits;
        test = Block_test_tbl[(hit->kind & 0xF0) >> 4](box, hit->kind);
        if (test == 0)
        {
            found = 0;
        }
        else
        {
            count = area->count;
            do
            {
                if (!(hit->flags & (slide ^ 0x8000) & 0x8000))
                {
                    box[4] = D_1F8000E0.vy + hit->y0;
                    box[5] = D_1F8000E0.vy + hit->y1;
                    found  = func_8004BDC8(box, hit->kind, test);
                    if (found != 0)
                    {
                        goto done;
                    }
                }
                hit++;
            } while (--count != 0);
        }
        area++;
    }
done:
    if (found != 0)
    {
        D_1F8000C0.vx += D_1F800106[0];
        D_1F8000C0.vz += D_1F800106[2];
        D_1F8000C0.vy += D_1F800106[1];
        D_1F800106[0]   = D_1F800100_h[0];
        D_1F800106[1]   = D_1F800100_h[1];
        D_1F800106[2]   = D_1F800100_h[2];
        D_1F800112[0]   = D_1F80010C[0];
        D_1F800112[1]   = D_1F80010C[1];
        D_1F800112[2]   = D_1F80010C[2];
        D_1F800100_h[0] = 0;
        D_1F800100_h[1] = 0;
        D_1F800100_h[2] = 0;
        D_1F80010C[0]   = 0;
        D_1F80010C[1]   = 0;
        D_1F80010C[2]   = 0;
        if (tries++ < 8)
        {
            goto retry;
        }
        return 0x80000000;
    }
    dx = start.vx - D_1F8000C0.vx;
    dz = start.vz - D_1F8000C0.vz;
    dy = start.vy - D_1F8000C0.vy;
    if (dx == 0 && dz == 0 && dy == 0)
    {
        result = 0;
    }
    else
    {
        if (ABS(dx) > ABS(dz))
        {
            if (ABS(dx) > ABS(dy))
            {
                result = (dx > 0) ? 1 : 2;
            }
            else
            {
                result = (dy > 0) ? 5 : 6;
            }
        }
        else if (ABS(dz) > ABS(dy))
        {
            result = (dz > 0) ? 3 : 4;
        }
        else
        {
            result = (dy > 0) ? 5 : 6;
        }
        if (dx != 0)
        {
            cur->vx = (D_1F8000C0.vx + ((dx > 0) ? -2 : 2)) << 16;
            result |= (dx > 0) ? 0x100 : 0x200;
        }
        if (dz != 0)
        {
            cur->vz = (D_1F8000C0.vz + ((dz > 0) ? -2 : 2)) << 16;
            result |= (dz > 0) ? 0x400 : 0x800;
        }
        if (dy != 0)
        {
            cur->vy = (D_1F8000C0.vy + ((dy > 0) ? -2 : 2)) << 16;
            result |= (dy > 0) ? 0x1000 : 0x2000;
        }
    }
    if (keep == 0)
    {
        rot.vx = -rot.vx;
        rot.vy = -rot.vy;
        rot.vz = -rot.vz;
        RotMatrixYXZ(&rot, &mtx);
        func_800301A8(&mtx, cur, now);
    }
    return result;
}

// Carries pl along with the object it rides (obj): turns pl's pos_l about obj's old_l by the change
// from obj's old_ang to ang, moves it by obj's move, and turns pl's ang.vy with obj.
void Ride_move(PL_WORK *pl, MODEL_WORK *obj)
{
    MATRIX mtx;
    VECTOR pos;
    VECTOR now;
    VECTOR old;
    SVECTOR ang;
    SVECTOR inv;

    if (obj->kind_1 < 0x80)
    {
        pos = pl->pos_l;
        now = obj->pos_l;
        old = obj->old_l;
        if (*(uint32 *)&obj->ang & 0x0FFF0FFF)
        {
            inv.vx = -obj->old_ang.vx;
            inv.vy = -obj->old_ang.vy;
            inv.vz = -obj->old_ang.vz;
            RotMatrix(&inv, &mtx);
            func_800301A8(&mtx, &pos, &old);
            ang.vx = obj->ang.vx;
            ang.vy = obj->ang.vy;
            ang.vz = obj->ang.vz;
            RotMatrixYXZ(&ang, &mtx);
            func_800301A8(&mtx, &pos, &old);
        }
        pl->pos_l.vx = pos.vx + now.vx - old.vx;
        pl->pos_l.vy = pos.vy + now.vy - old.vy;
        pl->pos_l.vz = pos.vz + now.vz - old.vz;
        func_80030150(&pl->pos_l, &pl->pos);
        pl->ang.vy += obj->ang.vy - obj->old_ang.vy;
    }
}

// Same as Ride_move, on pl's saved position (pos_428, svec_438, ang_440).
void Ride_move_saved(PL_WORK *pl, MODEL_WORK *obj)
{
    MATRIX mtx;
    VECTOR pos;
    VECTOR now;
    VECTOR old;
    SVECTOR ang;
    SVECTOR inv;

    if (obj->kind_1 < 0x80)
    {
        pos = pl->pos_428;
        now = obj->pos_l;
        old = obj->old_l;
        if (*(uint32 *)&obj->ang & 0x0FFF0FFF)
        {
            inv.vx = -obj->old_ang.vx;
            inv.vy = -obj->old_ang.vy;
            inv.vz = -obj->old_ang.vz;
            RotMatrix(&inv, &mtx);
            func_800301A8(&mtx, &pos, &old);
            ang.vx = obj->ang.vx;
            ang.vy = obj->ang.vy;
            ang.vz = obj->ang.vz;
            RotMatrixYXZ(&ang, &mtx);
            func_800301A8(&mtx, &pos, &old);
        }
        pl->pos_428.vx = pos.vx + now.vx - old.vx;
        pl->pos_428.vy = pos.vy + now.vy - old.vy;
        pl->pos_428.vz = pos.vz + now.vz - old.vz;
        func_80030150(&pl->pos_428, &pl->svec_438);
        pl->ang_440.vy += obj->ang.vy - obj->old_ang.vy;
    }
}

// Adds to *move how far obj carries the point pt (rider's position): obj's move (pos - old, from
// func_800536B0), then, when obj turned (old_ang to ang), the turn of pt about pos. rider is unused.
void func_800534E0(MODEL_WORK *obj, MODEL_WORK *rider, VECTOR *pos, VECTOR *old, VECTOR *pt, VECTOR *move)
{
    MATRIX mtx;
    VECTOR tmp;
    SVECTOR ang;
    SVECTOR inv;

    move->vx += pos->vx - old->vx;
    move->vy += pos->vy - old->vy;
    move->vz += pos->vz - old->vz;
    if (*(uint32 *)&obj->ang & 0x0FFF0FFF)
    {
        inv.vx = -obj->old_ang.vx & 0xFFF;
        inv.vy = -obj->old_ang.vy & 0xFFF;
        inv.vz = -obj->old_ang.vz & 0xFFF;
        ang.vx = obj->ang.vx & 0xFFF;
        ang.vy = obj->ang.vy & 0xFFF;
        ang.vz = obj->ang.vz & 0xFFF;
        if (inv.vx != -ang.vx || inv.vy != -ang.vy || inv.vz != -ang.vz)
        {
            tmp = *pt;
            RotMatrix(&inv, &mtx);
            func_800301A8(&mtx, &tmp, pos);
            RotMatrixYXZ(&ang, &mtx);
            func_800301A8(&mtx, &tmp, pos);
            move->vx += tmp.vx - pt->vx;
            move->vy += tmp.vy - pt->vy;
            move->vz += tmp.vz - pt->vz;
        }
    }
}

// obj's 16.16 position and previous position, or (part >= 0) those of its part part, moved by
// the same step.
void func_800536B0(MODEL_WORK *obj, VECTOR *pos, VECTOR *old, sint32 part)
{
    if (part < 0)
    {
        *pos = obj->pos_l;
        *old = obj->old_l;
    }
    else
    {
        pos->vx = obj->part_180[part].vx << 16;
        pos->vy = obj->part_180[part].vy << 16;
        pos->vz = obj->part_180[part].vz << 16;
        old->vx = obj->old_l.vx + (pos->vx - obj->pos_l.vx);
        old->vy = obj->old_l.vy + (pos->vy - obj->pos_l.vy);
        old->vz = obj->old_l.vz + (pos->vz - obj->pos_l.vz);
    }
}
