#include "common.h"
#include "code_80048620.h"

// Small data reached through $gp
PL_FIXED_VECTOR D_80098AC0;

void func_80048620(CODE486_TASK *task)
{
    uint8 *entry;

    entry = (uint8 *)&D_800C3558;
    switch (task->routine_1)
    {
        case 0:
            PLAYER_WORK_PTR->flags06 |= 3;
            Obj_work_flag_change(8, 0x80);
            task->routine_1++;
            // fall through
        case 1:
            if (func_80042238(&Player_work) != 0)
            {
                D_800BC7F0[0]   = D_8008A9D4[*(sint16 *)(entry + 0x10) >> 10];
                task->value_a4  = D_8008A9F4;
                task->value0c   = 0;
                task->routine_1 = 0;
                task->routine_0++;
            }
            break;
    }
}

void func_80048704(CODE486_TASK *task)
{
    PL_WORK *pl;
    uint8 *entry;

    pl    = &Player_work;
    entry = (uint8 *)&D_800C3558;
    switch (task->routine_1)
    {
        case 0:
            func_8001E6C0(CODE486_ENTRY_H(entry, 0), CODE486_ENTRY_H(entry, 2),
                          CODE486_ENTRY_H(entry, 4));
            pl->kind      = 3;
            pl->routine_1 = 1;
            pl->position_saved.x =
                CODE486_ENTRY_H(entry, 0) + ((rsin(CODE486_ENTRY_H(entry, 0x10)) << 6) >> 12);
            pl->position_saved.y = pl->position.y;
            pl->position_saved.z =
                CODE486_ENTRY_H(entry, 4) + ((rcos(CODE486_ENTRY_H(entry, 0x10)) << 6) >> 12);
            pl->rotation_saved.x       = 0;
            pl->rotation_saved.z       = 0;
            pl->value448               = 0x30;
            pl->position_saved_fixed.x = pl->position_saved.x << 16;
            pl->position_saved_fixed.y = pl->position_saved.y << 16;
            pl->position_saved_fixed.z = pl->position_saved.z << 16;
            pl->rotation_saved.y       = CODE486_ENTRY_H(entry, 0x10);
            task->routine_1++;
            break;
        case 2:
            if (Sce_flag_test(0x7B2) == 0)
            {
                pl->routine_1++;
                task->value0a = 0;
                task->routine_1++;
            }
            break;
        case 5:
            if (Sce_flag_test(0x7B2) == 0)
            {
                D_800C356C = 1;
                D_800C3571 = 10;
                D_800C3570 = 2;
                task->routine_1++;
            }
            break;
        case 6:
            if (D_800C356C == 2)
            {
                task->routine_1++;
            }
            break;
        case 7:
            if (Sce_flag_test(0x7B2) == 0)
            {
                D_800C356C = 3;
                task->routine_1++;
            }
            break;
        case 8:
            if (D_800C356C == 0)
            {
                D_800BC7F0[0] = D_8008A9E4[CODE486_ENTRY_H(entry, 0x12) >> 10];
                func_8001E6C0(CODE486_ENTRY_H(entry, 8), CODE486_ENTRY_H(entry, 0xA),
                              CODE486_ENTRY_H(entry, 0xC));
                pl->kind      = 3;
                pl->routine_1 = 1;
                pl->position_saved.x =
                    CODE486_ENTRY_H(entry, 8) + ((rsin(CODE486_ENTRY_H(entry, 0x12)) << 6) >> 12);
                pl->position_saved.y = CODE486_ENTRY_H(entry, 0xA) - 1;
                pl->position_saved.z =
                    CODE486_ENTRY_H(entry, 0xC) + ((rcos(CODE486_ENTRY_H(entry, 0x12)) << 6) >> 12);
                pl->rotation_saved.x       = 0;
                pl->rotation_saved.z       = 0;
                pl->value448               = 0x30;
                pl->position_saved_fixed.x = pl->position_saved.x << 16;
                pl->position_saved_fixed.y = pl->position_saved.y << 16;
                pl->position_saved_fixed.z = pl->position_saved.z << 16;
                pl->rotation_saved.y       = CODE486_ENTRY_H(entry, 0x12);
                task->routine_1++;
            }
            break;
        case 1:
        case 9:
            task->routine_1++;
            Sce_flag_on(0x7B1);
            break;
        case 10:
            if (Sce_flag_test(0x7B2) == 0)
            {
                pl->routine_1++;
                task->routine_1++;
            }
            break;
        case 3:
        case 11:
            func_80048A9C(task);
            break;
        case 4:
        case 12:
            Sce_flag_off(0x7B1);
            task->routine_1++;
            break;
        case 13:
            if (Sce_flag_test(0x7B2) == 0)
            {
                Sce_flag_off(0x7B0);
                Sce_flag_on(0x7B3);
                task->routine_1 = 0;
                task->routine_0++;
            }
            break;
    }
    func_8001EC0C();
    func_8001F070();
}

void func_80048A40(PL_WORK *pl)
{
    func_80042314(&Player_work);
    *(uint32 *)&Player_work.kind = 0;
    D_800A395C                   = 1;
    func_80039820();
    Sce_flag_off(0x7B3);
    pl->routine_0 = 0;
}

// D_800C0F96 is an array: an array reference keeps &D_800C0F96 in a1 within each case.
void func_80048A9C(CODE486_TASK *task)
{
    PL_WORK *pl;

    pl            = &Player_work;
    D_800C0F96[0] = 0;
    switch (task->value0a)
    {
        case 0:
            task->value0b = D_8008AA04[CODE486_GAME_BYTE50];
            Player_work.flags_bd |= 0x20;
            task->value0a++;
            // fall through
        case 1:
            D_800C0F96[0] = pl->value124;
            if (task->value10 >= 0x25)
            {
                task->routine_1++;
                task->value0a++;
                D_800C0F96[0] = 0;
                pl->flags_bd  = (pl->flags_bd & 0xDF) | 0x40;
            }
            break;
        case 2:
            Player_work.flags_bd |= 0x20;
            task->value0a++;
            // fall through
        case 3:
            D_800C0F96[0] = pl->value124;
            if (task->value0b < task->value10)
            {
                task->routine_1++;
                task->value0a++;
                D_800C0F96[0] = 0;
                pl->flags_bd  = (pl->flags_bd & 0xDF) | 0x40;
            }
            break;
    }
}

void func_80048BE4(void)
{
}

sint32 func_80048BEC(PL_SHORT_VECTOR *pos)
{
    sint32 x;
    sint32 z;

    if ((uint32)(x = ((pos->x + 0x8000) >> 9) - CODE486_MAP_X0) >= CODE486_MAP_W ||
        (uint32)(z = ((pos->z + 0x8000) >> 9) - CODE486_MAP_Z0) >= CODE486_MAP_H)
    {
        return 0;
    }
    return x + z * CODE486_MAP_W;
}

sint32 func_80048C60(PL_SHORT_VECTOR *pos)
{
    sint32 x;
    sint32 z;

    if ((uint32)(x = ((pos->x + 0x8000) >> 9) - CODE486_MAP_X0) >= CODE486_MAP_W ||
        (uint32)(z = ((pos->z + 0x8000) >> 9) - CODE486_MAP_Z0) >= CODE486_MAP_H)
    {
        return 0;
    }
    return (CODE486_MAP_CELLS + x)[z * CODE486_MAP_W];
}

sint32 func_80048CEC(sint32 index)
{
    return CODE486_MAP_CELLS[index];
}

sint32 func_80048D08(sint32 map, PL_SHORT_VECTOR *pos)
{
    sint32 x;
    sint32 z;
    CODE486_MAP *m;

    m = &CODE486_MAP_TBL[map];

    if ((uint32)(x = ((pos->x + 0x8000) >> 9) - m->x0) >= m->w ||
        (uint32)(z = ((pos->z + 0x8000) >> 9) - m->z0) >= m->h)
    {
        return 0;
    }
    return (m->cells + x)[z * m->w];
}

sint32 func_80048DAC(PL_SHORT_VECTOR *pos)
{
    if ((uint32)(((pos->x + 0x8000) >> 9) - CODE486_MAP_X0) >= CODE486_MAP_W ||
        (uint32)(((pos->z + 0x8000) >> 9) - CODE486_MAP_Z0) >= CODE486_MAP_H)
    {
        return -1;
    }
    return 0;
}

sint32 func_80048E18(PL_SHORT_VECTOR *pos)
{
    sint32 cell;

    cell = func_80048C60(pos);
    if (cell > 0)
    {
        return CODE486_MAP_INFO[cell].flags6 & 0xFFF;
    }
    return 0;
}

sint32 func_80048E6C(PL_WORK *pl)
{
    return func_80048EA4(&pl->position, pl->info78, pl->position.y - pl->position_prev.y,
                         pl->value01);
}

// The do/while (0) levels below are loop-depth wrappers: they only raise register
// priorities (area s3, left s4, best s5, the box and hit order) to retail's.
sint32 func_80048EA4(PL_SHORT_VECTOR *pos, PL_HEIGHT_INFO *info, sint32 dy, sint32 kind)
{
    sint16 box[6];
    PL_SHORT_VECTOR org;
    sint32 count;
    sint32 prev;
    sint32 best;
    sint32 slide;
    sint32 n;
    sint32 val;
    sint32 lim;
    sint32 left;
    sint32 top;
    uint32 type;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    best               = 0x7FFF;
    *CODE486_SP_POS_C0 = *pos;
    count              = func_8004B1E0(CODE486_SP_POS_C0, 0);
    func_8004B3C0((sint32 *)info);
    slide = (func_8002FE74(kind) == 0) << 15;
    do
    {
        prev = best;
        n    = count;
        while (n-- != 0)
        {
            val = func_80048CEC(CODE486_SP_CELLS[n]);
            if (val <= 0)
            {
                if (CODE486_SP_CELLS[n] == func_80048BEC(CODE486_SP_POS_C0))
                {
                    lim = ~((val & 0x1F00) >> 1) - CODE486_SP_12E;
                    if (lim < best)
                    {
                        best = lim;
                    }
                }
            }
            else
            {
                cell  = &CODE486_MAP_INFO[val];
                solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
                // Three do/while (0) levels per arm give area the weighted refs that rank it
                // above left (s3), with the solid pointer in its own temporary as retail.
                if (cell->flags6 & 0xFFF)
                {
                    do
                    {
                        do
                        {
                            do
                            {
                                area = solid->areas_a;
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
                                area = solid->areas_b;
                            } while (0);
                        } while (0);
                    } while (0);
                }
                org.x = cell->x;
                org.y = cell->y;
                org.z = cell->z;
                for (; area->hits != NULL; area++)
                {
                    do
                    {
                        do
                        {
                            box[0] = org.x + area->x0;
                            box[1] = org.x + area->x1;
                            box[2] = org.z + area->z0;
                            box[3] = org.z + area->z1;
                        } while (0);
                        hit = area->hits;
                    } while (0);
                    if ((type = hit->kind) < 0x100 &&
                        D_8008AA24[(type & 0xF0) >> 4](box, type) != 0)
                    {
                        left = area->count;
                        do
                        {
                            if (!(hit->pad & (slide ^ 0x8000)))
                            {
                                box[4] = org.y + hit->y0;
                                box[5] = org.y + hit->y1;
                                func_8004A060(box, hit->kind);
                                if (dy >= 0)
                                {
                                    if (box[4] < best)
                                    {
                                        top = CODE486_SP_POS_C0->y;
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
                                else if (box[4] < best && CODE486_SP_POS_C0->y < box[5])
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
    return best + CODE486_SP_12E;
}

// Scalar scratch stores and the do/while hit loop give retail's order. The box corners sit
// one do/while (0) level deeper (see func_8004AF28): GCC weights references by loop depth,
// and only this ranks the area giv above left and hit (s1/s2/s3).
sint16 func_8004920C(PL_SHORT_VECTOR *pos)
{
    sint16 box[6];
    PL_SHORT_VECTOR org;
    sint32 val;
    sint32 best;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    sint32 left;
    CODE486_HIT *hit;

    val  = func_80048C60(pos);
    best = 0x7FFF;
    if (val <= 0)
    {
        return ~((val & 0x1F00) >> 1);
    }
    *CODE486_SP_POS_C0 = *pos;
    cell               = &CODE486_MAP_INFO[val];
    solid              = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
    if (cell->flags6 & 0xFFF)
    {
        area = solid->areas_a;
    }
    else
    {
        area = solid->areas_b;
    }
    org.x            = cell->x;
    org.y            = cell->y;
    org.z            = cell->z;
    CODE486_SP_OFS_A = 0;
    CODE486_SP_OFS_B = 0;
    CODE486_SP_OFS_C = 0;
    for (; area->hits != NULL; area++)
    {
        do
        {
            box[0] = org.x + area->x0;
            box[1] = org.x + area->x1;
            box[2] = org.z + area->z0;
            box[3] = org.z + area->z1;
        } while (0);
        hit = area->hits;
        if (D_8008AA24[(hit->kind & 0xF0) >> 4](box, hit->kind) != 0)
        {
            left = area->count;
            do
            {
                box[4] = org.y + hit->y0;
                box[5] = org.y + hit->y1;
                func_8004A060(box, hit->kind);
                if (box[4] < best && CODE486_SP_POS_C0->y < box[5])
                {
                    best = box[4];
                }
                hit++;
            } while (--left != 0);
        }
    }
    return best;
}

sint32 func_80049448(PL_WORK *pl)
{
    return func_80049470(&pl->position, pl->info78, pl->value01);
}

// The hit loop is a do/while (retail has no zero-count test); the 0x12C/0x12E offsets are
// struct fields (a scalar literal address goes through a register that loop.c hoists), the
// kind goes through an unsigned local (no andi 0xFFFF before the call) and the floor term's
// +1 is its own statement. Loop depth: the box corners sit two do/while (0) levels deeper and
// the hit pointer one (see func_8004AF28); GCC weights each reference by loop depth, and only
// this ranks the area giv above hit (s0/s1) without changing the box[4] temporaries.
sint32 func_80049470(PL_SHORT_VECTOR *pos, PL_HEIGHT_INFO *info, sint32 kind)
{
    sint16 box[6];
    PL_SHORT_VECTOR org;
    sint32 best;
    sint32 slide;
    sint32 n;
    sint32 val;
    sint32 lim;
    uint32 type;
    sint32 left;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    best               = -0x7FFF;
    *CODE486_SP_POS_C0 = *pos;
    n                  = func_8004B1E0(CODE486_SP_POS_C0, 0);
    func_8004B3C0((sint32 *)info);
    slide = (func_8002FE74(kind) == 0) << 15;
    while (n-- != 0)
    {
        val = func_80048CEC(CODE486_SP_CELLS[n]);
        if (val <= 0)
        {
            if (CODE486_SP_CELLS[n] == func_80048BEC(CODE486_SP_POS_C0) && (val & 0x6000))
            {
                lim = -((val & 0x1F00) >> 1) - ((val & 0x6000) >> 13) * 0x180 + 1;
                lim -= CODE486_SP_12C;
                if (best < lim)
                {
                    best = lim;
                }
            }
        }
        else
        {
            cell  = &CODE486_MAP_INFO[val];
            solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
            if (cell->flags6 & 0xFFF)
            {
                area = solid->areas_a;
            }
            else
            {
                area = solid->areas_b;
            }
            org.x = cell->x;
            org.y = cell->y;
            org.z = cell->z;
            for (; area->hits != NULL; area++)
            {
                do
                {
                    do
                    {
                        box[0] = org.x + area->x0;
                        box[1] = org.x + area->x1;
                        box[2] = org.z + area->z0;
                        box[3] = org.z + area->z1;
                    } while (0);
                    hit = area->hits;
                } while (0);
                if ((type = hit->kind) < 0x100 && D_8008AA24[(type & 0xF0) >> 4](box, type) != 0)
                {
                    left = area->count;
                    do
                    {
                        if (!(hit->pad & (slide ^ 0x8000)))
                        {
                            box[4] = org.y + hit->y0 - CODE486_SP_OFSH4.h12e;
                            box[5] = org.y + hit->y1 - CODE486_SP_OFSH4.h12c;
                            if (box[4] < CODE486_SP_POS_C0->y && best < box[5])
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

sint32 func_8004976C(PL_WORK *pl)
{
    sint32 turn;

    if (func_8002FE74(pl->value01) != 0)
    {
        turn = 0;
    }
    else
    {
        turn = (sint16)pl->value116;
    }
    return func_800497CC(&pl->position, pl->info78, ((pl->rotation.y - turn + 0x200) >> 10) & 3,
                         pl->value01);
}

// Nearest wall in one of four directions.
// FAKE MATCH: nine dead conditional stores (`val = 0`), kept only for register allocation.
// The `if (...) { val = 0; }` statements are dead stores (val is reassigned from
// func_80048CEC before every read) and compile to nothing: flow deletes each store, but its
// test survives until jump2 and adds weighted references to area, area->hits (the area giv),
// hit and dir. That gives retail's register order (area giv, hit, dir, best, area, left), and
// unlike do/while (0) levels it leaves no loop note to pin the switch's constant load. The
// one-pass do/while (0) around the hit loop is still needed.
sint32 func_800497CC(PL_SHORT_VECTOR *pos, PL_HEIGHT_INFO *info, sint32 dir, sint32 kind)
{
    sint16 box[6];
    PL_SHORT_VECTOR org;
    sint32 best;
    sint32 slide;
    sint32 n;
    sint32 val;
    sint32 left;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    best = -0x7FFF;
    if (dir & 2)
    {
        best = 0x7FFF;
    }
    *CODE486_SP_POS_C0 = *pos;
    n                  = func_8004B1E0(CODE486_SP_POS_C0, 0);
    func_8004B3C0((sint32 *)info);
    slide = (func_8002FE74(kind) == 0) << 15;
    while (n-- != 0)
    {
        val = func_80048CEC(CODE486_SP_CELLS[n]);
        if (val <= 0)
        {
            continue;
        }
        cell  = &CODE486_MAP_INFO[val];
        solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
        if (cell->flags6 & 0xFFF)
        {
            area = solid->areas_a;
        }
        else
        {
            area = solid->areas_b;
        }
        org.x = cell->x;
        org.y = cell->y;
        org.z = cell->z;
        for (; area->hits != NULL; area++)
        {
            if (area != NULL)
            {
                val = 0;
            }
            box[0] = org.x + area->x0 - CODE486_SP_OFSH4.h126;
            box[1] = org.x + area->x1 - CODE486_SP_OFSH4.h124;
            box[2] = org.z + area->z0 - CODE486_SP_OFSH4.h12a;
            box[3] = org.z + area->z1 - CODE486_SP_OFSH4.h128;
            hit    = area->hits;
            switch (dir)
            {
                case 0:
                case 2:
                    if (CODE486_SP_POS_C0->x > box[0] && CODE486_SP_POS_C0->x < box[1])
                    {
                        break;
                    }
                    continue;
                case 1:
                case 3:
                    if (!(CODE486_SP_POS_C0->z > box[2] && CODE486_SP_POS_C0->z < box[3]))
                    {
                        continue;
                    }
                    break;
            }
            if (area->hits != NULL)
            {
                val = 0;
            }
            left = area->count;
            do
            {
                if (hit != NULL)
                {
                    val = 0;
                }
                if (area != NULL)
                {
                    val = 0;
                }
                do
                {
                    if (hit->pad & (slide ^ 0x8000))
                    {
                        goto next;
                    }
                    box[4] = org.y + hit->y0;
                    box[5] = org.y + hit->y1;
                    func_8004A060(box, hit->kind);
                    if (!(box[4] < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < box[5]))
                    {
                        goto next;
                    }
                    switch (dir)
                    {
                        case 0:
                            if (best < box[3] && CODE486_SP_POS_C0->z > box[2])
                            {
                                best = box[3];
                            }
                            break;
                        case 1:
                            if (best < box[1] && CODE486_SP_POS_C0->x > box[0])
                            {
                                best = box[1];
                            }
                            break;
                        case 2:
                            if (box[2] < best && CODE486_SP_POS_C0->z < box[3])
                            {
                                best = box[2];
                            }
                            break;
                        case 3:
                            if (box[0] < best && CODE486_SP_POS_C0->x < box[1])
                            {
                                best = box[0];
                            }
                            break;
                    }
                next:
                    if (area != NULL)
                    {
                        val = 0;
                    }
                    if (hit != NULL)
                    {
                        val = 0;
                    }
                    hit++;
                } while (--left != 0);
                if (area->hits != NULL)
                {
                    val = 0;
                }
            } while (0);
            if (area != NULL)
            {
                val = 0;
            }
        }
    }
    if (dir != 0)
    {
        val = 0;
    }
    return best;
}

sint32 func_80049C24(PL_WORK *pl)
{
    return func_80049C54(&pl->position, &pl->position_prev, pl->info78, pl->value01);
}

// The cell count goes straight to n, the z test uses ABS_NEG (retail lays it out differently
// from x), the kind and pad go through unsigned locals and the hit loop is a do/while. The two
// floor tests each get their own single-use variable (the subtraction then lands in the first
// operand's register), cy is a sint16. Loop depth: the area loop sits one level deeper than the
// cell loop and the area selection one more (two do/while (0)s, see func_8004AF28); GCC weights
// each reference by loop depth, and only this ranks the area pointer above pad (s4/s5).
sint32 func_80049C54(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, PL_HEIGHT_INFO *info, sint32 kind)
{
    sint16 box[6];
    PL_SHORT_VECTOR org;
    sint32 slide;
    sint32 n;
    sint32 val;
    sint32 floor;
    sint32 left;
    sint16 cy;
    sint32 top;
    sint32 bottom;
    uint32 type;
    uint32 pad;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    *CODE486_SP_POS_C0 = *pos;
    *CODE486_SP_POS_C8 = *prev;
    if ((CODE486_SP_POS_C0->x ^ CODE486_SP_POS_C8->x) & 0x8000 &&
        CODE486_ABS(CODE486_SP_POS_C0->x) > 0x4000)
    {
        return 0x80000000;
    }
    if ((CODE486_SP_POS_C0->z ^ CODE486_SP_POS_C8->z) & 0x8000 &&
        CODE486_ABS_NEG(CODE486_SP_POS_C0->z) > 0x4000)
    {
        return 0x80000000;
    }
    if (func_80048C60(CODE486_SP_POS_C0) == 0)
    {
        return 0x40000000;
    }
    n = func_8004B1E0(CODE486_SP_POS_C0, 1);
    func_8004B3C0((sint32 *)info);
    slide = (func_8002FE74(kind) == 0) << 15;
    while (n-- != 0)
    {
        val = func_80048CEC(CODE486_SP_CELLS[n]);
        if (val <= 0)
        {
            if (CODE486_SP_CELLS[n] == func_80048BEC(CODE486_SP_POS_C0))
            {
                floor = -((val & 0x1F00) >> 1);
                cy    = CODE486_SP_POS_C0->y;
                top   = floor - 1;
                if (top - CODE486_SP_12E < cy)
                {
                    return val & 0xFFFF;
                }
                if (val & 0x6000)
                {
                    bottom = floor - ((val & 0x6000) >> 13) * 0x180 + 1;
                    if (cy < bottom - CODE486_SP_12C)
                    {
                        return val & 0xFFFF;
                    }
                }
            }
            continue;
        }
        do
        {
            do
            {
                cell  = &CODE486_MAP_INFO[val];
                solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
                if (cell->flags6 & 0xFFF)
                {
                    area = solid->areas_a;
                }
                else
                {
                    area = solid->areas_b;
                }
            } while (0);
            org.x = cell->x;
            org.y = cell->y;
            org.z = cell->z;
            for (; area->hits != NULL; area++)
            {
                box[0] = org.x + area->x0;
                box[1] = org.x + area->x1;
                box[2] = org.z + area->z0;
                box[3] = org.z + area->z1;
                hit    = area->hits;
                if ((type = hit->kind) < 0x100 && D_8008AA24[(type & 0xF0) >> 4](box, type) != 0)
                {
                    left = area->count;
                    do
                    {
                        pad = hit->pad;
                        if (!(pad & (slide ^ 0x8000)))
                        {
                            box[4] = org.y + hit->y0;
                            box[5] = org.y + hit->y1;
                            func_8004A060(box, hit->kind);
                            cy = CODE486_SP_POS_C0->y;
                            if (cy > box[4] && cy < box[5])
                            {
                                return (val & 0xFFFF) | ((pad & 0xF) << 16);
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

void func_8004A060(sint16 *box, uint16 kind)
{
    sint8 flag;
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
    sint32 side;

    flag = 0;
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
            y0 -= (y1 - y0) * (CODE486_SP_OFSH6.h12a - CODE486_SP_OFSH6.h128) / (z1 - z0);
            top = y0 + (y1 - y0) * (z1 - CODE486_SP_CLIP_C4) / (z1 - z0);
            if (top < min)
            {
                top = min;
            }
            if (z1 - z0 < y1 - y0)
            {
                flag = 1;
            }
            break;
        case 0x9:
        case 0x11:
            y0 -= (y1 - y0) * (CODE486_SP_OFSH6.h12a - CODE486_SP_OFSH6.h128) / (z1 - z0);
            top = y0 + (y1 - y0) * (CODE486_SP_CLIP_C4 - z0) / (z1 - z0);
            if (top < min)
            {
                top = min;
            }
            if (z1 - z0 < y1 - y0)
            {
                flag = 2;
            }
            break;
        case 0xA:
        case 0x12:
            y0 -= (y1 - y0) * (CODE486_SP_OFSH6.h126 - CODE486_SP_OFSH6.h124) / (x1 - x0);
            top = y0 + (y1 - y0) * (CODE486_SP_CLIP_C0 - x0) / (x1 - x0);
            if (top < min)
            {
                top = min;
            }
            if (x1 - x0 < y1 - y0)
            {
                flag = 3;
            }
            break;
        case 0xB:
        case 0x13:
            y0 -= (y1 - y0) * (CODE486_SP_OFSH6.h126 - CODE486_SP_OFSH6.h124) / (x1 - x0);
            top = y0 + (y1 - y0) * (x1 - CODE486_SP_CLIP_C0) / (x1 - x0);
            if (top < min)
            {
                top = min;
            }
            if (x1 - x0 < y1 - y0)
            {
                flag = 4;
            }
            break;
        case 0xC:
            top = y0 + (y0 - y1) -
                  (y1 - y0) * (CODE486_SP_OFSH6.h12a - CODE486_SP_OFSH6.h128) / (z1 - z0);
            if (z0 + (z1 - z0) / 2 < CODE486_SP_CLIP_C4)
            {
                box[4] = top + (y1 - top) * (CODE486_SP_CLIP_C4 - z0) / (z1 - z0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                flag = 2;
            }
            else
            {
                box[4] = top + (y1 - top) * (z1 - CODE486_SP_CLIP_C4) / (z1 - z0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                flag = 1;
            }
            break;
        case 0xD:
            top = y0 + (y0 - y1) -
                  (y1 - y0) * (CODE486_SP_OFSH6.h126 - CODE486_SP_OFSH6.h124) / (x1 - x0);
            if (x0 + (x1 - x0) / 2 < CODE486_SP_CLIP_C0)
            {
                box[4] = top + (y1 - top) * (CODE486_SP_CLIP_C0 - x0) / (x1 - x0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                flag = 3;
            }
            else
            {
                box[4] = top + (y1 - top) * (x1 - CODE486_SP_CLIP_C0) / (x1 - x0);
                if (box[4] < y0)
                {
                    box[4] = y0;
                }
                flag = 4;
            }
            break;
        case 0xE:
            dx   = x1 - x0;
            near = CODE486_SP_CLIP_C4 - z0;
            dz   = z1 - z0;
            far  = z1 - CODE486_SP_CLIP_C4;
            top  = y0 + (y0 - y1);
            side = (CODE486_SP_CLIP_C0 < x0 + near * dx / dz) * 2;
            if (CODE486_SP_CLIP_C0 < x0 + far * dx / dz)
            {
                side |= 1;
            }
            switch (side)
            {
                case 0:
                    box[4] = top + (y1 - top) * (CODE486_SP_CLIP_C0 - x0) / dx;
                    if (dx < y1 - y0)
                    {
                        flag = 3;
                    }
                    break;
                case 1:
                    box[4] = top + (y1 - top) * far / dz;
                    if (dz < y1 - y0)
                    {
                        flag = 1;
                    }
                    break;
                case 2:
                    box[4] = top + (y1 - top) * near / dz;
                    if (dz < y1 - y0)
                    {
                        flag = 2;
                    }
                    break;
                case 3:
                    box[4] = top + (y1 - top) * (x1 - CODE486_SP_CLIP_C0) / dx;
                    if (dx < y1 - y0)
                    {
                        flag = 4;
                    }
                    break;
            }
            break;
        case 0x18:
        case 0x24:
            flag   = 5;
            box[4] = y0 + (y1 - y0) * ((CODE486_SP_CLIP_C0 - x0) + (z1 - CODE486_SP_CLIP_C4)) /
                              (x1 - x0);
            break;
        case 0x25:
            flag   = 6;
            box[4] = y1 - (y1 - y0) * ((CODE486_SP_CLIP_C0 - x0) + (z1 - CODE486_SP_CLIP_C4)) /
                              (x1 - x0);
            break;
        case 0x19:
        case 0x34:
            flag   = 7;
            box[4] = y0 + (y1 - y0) * ((x1 - CODE486_SP_CLIP_C0) + (z1 - CODE486_SP_CLIP_C4)) /
                              (x1 - x0);
            break;
        case 0x35:
            flag   = 8;
            box[4] = y1 - (y1 - y0) * ((x1 - CODE486_SP_CLIP_C0) + (z1 - CODE486_SP_CLIP_C4)) /
                              (x1 - x0);
            break;
        case 0x1A:
        case 0x44:
            flag   = 8;
            box[4] = y0 + (y1 - y0) * ((CODE486_SP_CLIP_C0 - x0) + (CODE486_SP_CLIP_C4 - z0)) /
                              (x1 - x0);
            break;
        case 0x45:
            flag   = 7;
            box[4] = y1 - (y1 - y0) * ((CODE486_SP_CLIP_C0 - x0) + (CODE486_SP_CLIP_C4 - z0)) /
                              (x1 - x0);
            break;
        case 0x1B:
        case 0x54:
            flag   = 6;
            box[4] = y0 + (y1 - y0) * ((x1 - CODE486_SP_CLIP_C0) + (CODE486_SP_CLIP_C4 - z0)) /
                              (x1 - x0);
            break;
        case 0x55:
            flag   = 5;
            box[4] = y1 - (y1 - y0) * ((x1 - CODE486_SP_CLIP_C0) + (CODE486_SP_CLIP_C4 - z0)) /
                              (x1 - x0);
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
    box[4] -= CODE486_SP_OFSH6.h12e;
    CODE486_SP_FE = flag;
    box[5] -= CODE486_SP_OFSH6.h12c;
}

sint32 func_8004AC8C(PL_SHORT_VECTOR *vec, sint32 flags)
{
    PL_SHORT_BYTES old;
    sint32 val;
    sint32 changed;

    changed = 0;
    if ((flags & 0x300) && (flags & 0xC00))
    {
        changed = 1;
        old.b8  = *(PL_BYTES8 *)vec;
        if (flags & 0x100)
        {
            if (flags & 0x400)
            {
                vec->x = -CODE486_ABS_NEG(old.v.z);
                vec->z = -CODE486_ABS_NEG(old.v.x);
            }
            else
            {
                vec->x = -CODE486_ABS_NEG(old.v.z);
                val    = old.v.x;
                if (val < 0)
                {
                    val = -val;
                }
                vec->z = val;
            }
        }
        else
        {
            if (flags & 0x400)
            {
                val = old.v.z;
                if (val < 0)
                {
                    val = -val;
                }
                vec->x = val;
                vec->z = -CODE486_ABS_NEG(old.v.x);
            }
            else
            {
                val = old.v.z;
                if (val < 0)
                {
                    val = -val;
                }
                vec->x = val;
                val    = old.v.x;
                if (val < 0)
                {
                    val = -val;
                }
                vec->z = val;
            }
        }
    }
    else
    {
        if (flags & 0x300)
        {
            changed = 1;
            if (flags & 0x100)
            {
                vec->x = -CODE486_ABS_NEG(vec->x);
            }
            else
            {
                val = vec->x;
                if (val < 0)
                {
                    val = -val;
                }
                vec->x = val;
            }
        }
        if (flags & 0xC00)
        {
            changed = 1;
            if (flags & 0x400)
            {
                vec->z = -CODE486_ABS_NEG(vec->z);
            }
            else
            {
                val = vec->z;
                if (val < 0)
                {
                    val = -val;
                }
                vec->z = val;
            }
        }
    }
    if (flags & 0x3000)
    {
        changed = 1;
        if (flags & 0x1000)
        {
            vec->y = -CODE486_ABS_NEG(vec->y);
        }
        else
        {
            val = vec->y;
            if (val < 0)
            {
                val = -val;
            }
            vec->y = val;
        }
    }
    return changed;
}
sint32 func_8004AE88(uint16 *angle, uint32 flags)
{
    uint32 ang;
    sint32 flipped;

    ang     = *angle & 0xFFF;
    flipped = 0;
    if (flags & 0x300)
    {
        flipped = 1;
        if (flags & 0x100)
        {
            if (ang - 0x401 < 0x7FF)
            {
                ang = 0x1000 - ang;
            }
        }
        else
        {
            if (ang - 0x400 >= 0x801)
            {
                ang = 0x1000 - ang;
            }
        }
    }
    if (flags & 0xC00)
    {
        flipped = 1;
        if (flags & 0x400)
        {
            if ((sint32)ang >= 0x801)
            {
                ang = 0x1800 - ang;
            }
        }
        else
        {
            if ((sint32)ang < 0x800)
            {
                ang = 0x800 - ang;
            }
        }
    }
    *angle = ang;
    return flipped;
}

// The area loop sits one loop level deeper than the cell loop (an extra do/while (0)): GCC
// weights each reference by loop depth, and only this depth ranks the area pointer above
// hit as retail does (area s1, hit s2); without it only those two saved registers swap.
sint32 func_8004AF28(PL_SHORT_VECTOR *pos, uint16 a1, uint8 a2, uint8 a3)
{
    sint16 box[6];
    PL_SHORT_VECTOR org;
    sint32 n;
    sint32 val;
    sint32 left;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    *CODE486_SP_POS_C0 = *pos;
    n                  = func_8004B1E0(CODE486_SP_POS_C0, 0);
    CODE486_SP_OFS.a   = 0;
    CODE486_SP_OFS.b   = 0;
    CODE486_SP_OFS.c   = 0;
    while (n-- != 0)
    {
        val = func_80048CEC(CODE486_SP_CELLS[n]);
        if (val <= 0)
        {
            if (CODE486_SP_CELLS[n] == func_80048BEC(CODE486_SP_POS_C0) &&
                CODE486_SP_POS_C0->y == ~((val & 0x1F00) >> 1) - CODE486_SP_12E)
            {
                return 0;
            }
            continue;
        }
        cell  = &CODE486_MAP_INFO[val];
        solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
        if (cell->flags6 & 0xFFF)
        {
            area = solid->areas_a;
        }
        else
        {
            area = solid->areas_b;
        }
        org.x = cell->x;
        org.y = cell->y;
        org.z = cell->z;
        do
        {
            for (; area->hits != NULL; area++)
            {
                box[0] = org.x + area->x0;
                box[1] = org.x + area->x1;
                box[2] = org.z + area->z0;
                box[3] = org.z + area->z1;
                hit    = area->hits;
                if (D_8008AA24[(hit->kind & 0xF0) >> 4](box, hit->kind) != 0)
                {
                    left = area->count;
                    do
                    {
                        box[4] = org.y + hit->y0;
                        box[5] = org.y + hit->y1;
                        func_8004A060(box, hit->kind);
                        if ((hit->pad & 0x4000) && Player_work.value74 == 0 && CODE486_SP_FE != 0)
                        {
                            return CODE486_SP_FE;
                        }
                        hit++;
                    } while (--left != 0);
                }
            }
        } while (0);
    }
    return 0;
}

sint32 func_8004B1E0(PL_SHORT_VECTOR *pos, sint32 keep_empty)
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
    if ((pos->x & 0x1FF) >= 0x101)
    {
        ofs[1][0] = ofs[3][0] = 0x8200;
    }
    else
    {
        ofs[1][0] = ofs[3][0] = 0x7E00;
    }
    if ((pos->z & 0x1FF) >= 0x101)
    {
        ofs[2][1] = ofs[3][1] = 0x8200;
    }
    else
    {
        ofs[2][1] = ofs[3][1] = 0x7E00;
    }
    count = 0;
    i     = 0;
    list  = (sint16 *)0x1F800118;
    for (; i < 4; i++)
    {
        x = ((pos->x + ofs[i][0]) >> 9) - CODE486_MAP_X0;
        if (x >= CODE486_MAP_W)
        {
            break;
        }
        z = ((pos->z + ofs[i][1]) >> 9) - CODE486_MAP_Z0;
        if (z >= CODE486_MAP_H)
        {
            break;
        }
        cell = x + z * CODE486_MAP_W;
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

void func_8004B3C0(sint32 *arg)
{
    if (arg != 0)
    {
        CODE486_SP_OFS.a = arg[0];
        CODE486_SP_OFS.b = arg[1];
        CODE486_SP_OFS.c = arg[2];
    }
    else
    {
        CODE486_SP_OFS.a = 0;
        CODE486_SP_OFS.b = 0;
        CODE486_SP_OFS.c = 0;
    }
}

sint32 func_8004B414(PL_WORK *wp)
{
    sint32 result;
    sint32 slide;

    func_8004B3C0((sint32 *)wp->info78);
    slide  = (func_8002FE74(wp->value01) == 0) << 15;
    result = func_8004B6AC(&wp->position, &wp->position_prev, wp->value74, slide);
    if (result != 0)
    {
        if (result > 0)
        {
            if (result & 0x300)
            {
                wp->position.x       = CODE486_SP_POS_C0->x;
                wp->position_fixed.x = CODE486_SP_POS_C0->x << 16;
            }
            if (result & 0xC00)
            {
                wp->position.z       = CODE486_SP_POS_C0->z;
                wp->position_fixed.z = CODE486_SP_POS_C0->z << 16;
            }
            if (result & 0x3000)
            {
                wp->position.y       = CODE486_SP_POS_C0->y;
                wp->position_fixed.y = CODE486_SP_POS_C0->y << 16;
            }
            if (wp->value74 != 2)
            {
                wp->value74 = *(uint8 *)0x1F8000F6;
            }
        }
        else if (slide != 0)
        {
            wp->value48          = 0;
            wp->value44          = 0;
            wp->position.x       = wp->position_prev.x;
            wp->position.z       = wp->position_prev.z;
            wp->position_fixed.x = wp->position_fixed_prev.x;
            wp->position_fixed.z = wp->position_fixed_prev.z;
            if (wp->value74 != 0)
            {
                wp->value74          = 0;
                wp->value46          = 0;
                wp->position.y       = wp->position_prev.y;
                wp->position_fixed.y = wp->position_fixed_prev.y;
            }
        }
        else
        {
            wp->position       = *(PL_SHORT_VECTOR *)&wp->position_prev;
            wp->position_fixed = wp->position_fixed_prev;
        }
    }
    return result;
}

sint32 func_8004B5CC(PL_SHORT_VECTOR *out, PL_SHORT_VECTOR *in, sint32 arg2, sint32 arg3)
{
    sint32 result;

    func_8004B3C0((sint32 *)arg3);
    result = func_8004B6AC(out, in, arg2, 0);
    if (result != 0)
    {
        if (result > 0)
        {
            if (result & 0x300)
            {
                out->x = CODE486_SP_C0;
            }
            if (result & 0xC00)
            {
                out->z = CODE486_SP_C4;
            }
            if (result & 0x3000)
            {
                out->y = CODE486_SP_C2;
            }
        }
        else
        {
            *(PL_BYTES8 *)out = *(PL_BYTES8 *)in;
        }
    }
    return result;
}

// Map-cell version of func_80052B04 (same retry goto, delta vector and push block). The
// floor/ceiling hits break out to the found test; the cell id variable is reused for the
// target height and val for the result. The two do { } while (0) levels around the box
// corners and the one around the cell setup give retail's saved-register ranking (as in
// func_80052674).
sint32 func_8004B6AC(PL_SHORT_VECTOR *out, PL_SHORT_VECTOR *in, sint32 arg2, sint32 arg3)
{
    PL_SHORT_VECTOR org;
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
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    found               = 0;
    tries               = 0;
    CODE486_MOVE_FLAGS  = 0;
    *CODE486_SP_POS_C8  = *in;
    *CODE486_SP_POS_C0  = *out;
    CODE486_SP_F6       = arg2;
    CODE486_SP_PUSH[0]  = 0;
    CODE486_SP_PUSH[1]  = 0;
    CODE486_SP_PUSH[2]  = 0;
    CODE486_SP_PUSH[3]  = 0;
    CODE486_SP_PUSH[4]  = 0;
    CODE486_SP_PUSH[5]  = 0;
    CODE486_SP_PUSH[6]  = 0;
    CODE486_SP_PUSH[7]  = 0;
    CODE486_SP_PUSH[8]  = 0;
    CODE486_SP_PUSH[9]  = 0;
    CODE486_SP_PUSH[10] = 0;
    CODE486_SP_PUSH[11] = 0;
    CODE486_SP_D8       = CODE486_SP_POS_C0->x - CODE486_SP_POS_C8->x;
    CODE486_SP_DA       = CODE486_SP_POS_C0->y - CODE486_SP_POS_C8->y;
    CODE486_SP_DC       = CODE486_SP_POS_C0->z - CODE486_SP_POS_C8->z;
    count               = func_8004B1E0(CODE486_SP_POS_C0, 0);
retry:
    n = count;
    while (n-- != 0)
    {
        CODE486_SP_POS_D0->x = CODE486_SP_POS_C0->x - CODE486_SP_POS_C8->x;
        CODE486_SP_POS_D0->y = CODE486_SP_POS_C0->y - CODE486_SP_POS_C8->y;
        CODE486_SP_POS_D0->z = CODE486_SP_POS_C0->z - CODE486_SP_POS_C8->z;
        id                   = CODE486_SP_CELLS[n];
        val                  = func_80048CEC(id);
        if (val <= 0)
        {
            found = 0;
            if (id != func_80048BEC(CODE486_SP_POS_C0))
            {
                continue;
            }
            floor = -((val & 0x1F00) >> 1);
            cy    = CODE486_SP_POS_C0->y;
            top   = floor - 1;
            id    = top - CODE486_SP_12E;
            if (id < cy)
            {
                CODE486_SP_PUSH[3]   = 0;
                CODE486_SP_PUSH[4]   = 0;
                CODE486_SP_PUSH[5]   = 0;
                CODE486_SP_POS_C0->y = id;
                found                = 1;
                if (CODE486_SP_D2 > 0)
                {
                    CODE486_SP_F6 = 0;
                }
                break;
            }
            if (val & 0x6000)
            {
                bottom = floor - ((val & 0x6000) >> 13) * 0x180 + 1;
                id     = bottom - CODE486_SP_12C;
                if (cy < id)
                {
                    CODE486_SP_PUSH[3]   = 0;
                    CODE486_SP_PUSH[4]   = 0;
                    CODE486_SP_PUSH[5]   = 0;
                    CODE486_SP_POS_C0->y = id;
                    found                = 1;
                    break;
                }
            }
            continue;
        }
        do
        {
            cell  = &CODE486_MAP_INFO[val];
            solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
            if (cell->flags6 & 0xFFF)
            {
                area = solid->areas_a;
            }
            else
            {
                area = solid->areas_b;
            }
            org.x = cell->x;
            org.y = cell->y;
            org.z = cell->z;
        } while (0);
        for (; area->hits != NULL; area++)
        {
            do
            {
                do
                {
                    box[0] = org.x + area->x0;
                    box[1] = org.x + area->x1;
                    box[2] = org.z + area->z0;
                    box[3] = org.z + area->z1;
                } while (0);
                hit = area->hits;
            } while (0);
            if ((kind = hit->kind) >= 0x100 ||
                (test = D_8008AA24[(kind & 0xF0) >> 4](box, kind)) == 0)
            {
                found = 0;
                continue;
            }
            left = area->count;
            do
            {
                if (!(hit->pad & (arg3 ^ 0x8000) & 0x8000))
                {
                    box[4] = org.y + hit->y0;
                    box[5] = org.y + hit->y1;
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
        CODE486_SP_POS_C0->x += CODE486_SP_PUSH[3];
        CODE486_SP_POS_C0->z += CODE486_SP_PUSH[5];
        CODE486_SP_POS_C0->y += CODE486_SP_PUSH[4];
        CODE486_SP_PUSH[3]  = CODE486_SP_PUSH[0];
        CODE486_SP_PUSH[4]  = CODE486_SP_PUSH[1];
        CODE486_SP_PUSH[5]  = CODE486_SP_PUSH[2];
        CODE486_SP_PUSH[9]  = CODE486_SP_PUSH[6];
        CODE486_SP_PUSH[10] = CODE486_SP_PUSH[7];
        CODE486_SP_PUSH[11] = CODE486_SP_PUSH[8];
        CODE486_SP_PUSH[0]  = 0;
        CODE486_SP_PUSH[1]  = 0;
        CODE486_SP_PUSH[2]  = 0;
        CODE486_SP_PUSH[6]  = 0;
        CODE486_SP_PUSH[7]  = 0;
        CODE486_SP_PUSH[8]  = 0;
        if (tries++ < 8)
        {
            goto retry;
        }
        return 0x80000000;
    }
    dx = out->x - CODE486_SP_POS_C0->x;
    dz = out->z - CODE486_SP_POS_C0->z;
    dy = out->y - CODE486_SP_POS_C0->y;
    if (dx == 0 && dz == 0 && dy == 0)
    {
        return 0;
    }
    if (CODE486_ABS_NEG(dx) > CODE486_ABS_NEG(dz))
    {
        if (CODE486_ABS_NEG(dx) > CODE486_ABS_NEG(dy))
        {
            val = (dx > 0) ? 1 : 2;
        }
        else
        {
            val = (dy > 0) ? 5 : 6;
        }
    }
    else if (CODE486_ABS_NEG(dz) > CODE486_ABS_NEG(dy))
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

// Box-versus-collision-kind test (sibling of func_8004A060). `type` is a uint16 copy (retail
// zero-extends it with andi 0xFFFF for `type != 0x18`) and the switch is on `kind & 0xFF`.
// Cases 8..0xB keep their x product in gap and every wall push amount goes through `b` (as
// mult-only variables they would prefer LO, and reload would spill an extra saved register);
// case 0xE has its own near_x/far_x quotients; the wall cases address F0/F8 directly.
// Cross-jumping (jump2 searches the jump chain from the last jump backwards) shapes the tails:
// - corner stores F6W through the int `landed`. Its li/sh are then SImode with a subreg, so
//   corner's tail never matches 0x1C's HImode one, and cases 1 and 2 merge into 0x1C's tail
//   instead of corner's (the last jump to `clear`).
// - case 3 jumps to `land` inside 0x1C; dbr then fills the jump's delay slot with the li.
// - case 3's call arm writes the clears out; jump2 merges them into ceil's (beqz + j clear).
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
    top    = box[4] - CODE486_SP_12E;
    bottom = box[5] - CODE486_SP_12C;
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
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                return 1;
            }
            return 0;
        case 0x1:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                result               = 1;
                if (CODE486_SP_F6 == 0 && CODE486_SP_POS_C0->y - top < 8 && CODE486_SP_FF == 0)
                {
                    CODE486_SP_POS_C0->y = top;
                    CODE486_SP_F6W       = 0x100;
                    goto clear;
                }
                if (func_8004F44C(CODE486_SP_POS_C0, CODE486_SP_POS_C8, 1) != 0)
                {
                    if (CODE486_SP_D2 >= 0)
                    {
                        CODE486_SP_F6W = 0x100;
                    }
                    goto clear;
                }
            }
            break;
        case 0x2:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                if (func_8004F44C(CODE486_SP_POS_C0, CODE486_SP_POS_C8, 0) != 0)
                {
                    if (CODE486_SP_D2 >= 0)
                    {
                        CODE486_SP_F6W = 0x100;
                    }
                    goto clear;
                }
            }
            break;
        case 0x3:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                result               = 1;
                if (CODE486_SP_D2 >= 0 || CODE486_SP_F6 == 0)
                {
                    CODE486_SP_POS_C0->y = top;
                    goto land;
                }
                if (func_8004F44C(CODE486_SP_POS_C0, CODE486_SP_POS_C8, 3) != 0)
                {
                    CODE486_SP_106 = 0;
                    CODE486_SP_108 = 0;
                    CODE486_SP_10A = 0;
                }
            }
            break;
        case 0xF:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                CODE486_SP_POS_C0->y = bottom;
                result               = 1;
                goto clear;
            }
            break;
        case 0x4:
        case 0x5:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
            side_x:
                if (func_8004F8BC(CODE486_SP_POS_C0, CODE486_SP_POS_C8, type - 4) != 0)
                {
                    if (CODE486_SP_D2 >= 0)
                    {
                        CODE486_SP_F6W = 0x100;
                    }
                    CODE486_SP_108 = 0;
                }
                CODE486_SP_106 = 0;
                goto clear_x;
            }
            break;
        case 0x6:
        case 0x7:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
            side_z:
                if (func_8004FBE8(CODE486_SP_POS_C0, CODE486_SP_POS_C8, type - 6) != 0)
                {
                    if (CODE486_SP_D2 >= 0)
                    {
                        CODE486_SP_F6W = 0x100;
                    }
                    CODE486_SP_108 = 0;
                }
                CODE486_SP_106 = 0;
                goto clear_x;
            }
            break;
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                if (func_800501E8(CODE486_SP_POS_C0, type - 0x1C) != 0)
                {
                    if (CODE486_SP_D2 >= 0)
                    {
                    land:
                        CODE486_SP_F6W = 0x100;
                    }
                    goto clear;
                }
            }
            break;
        case 0x21:
        case 0x22:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                gap = (CODE486_ABS_NEG(CODE486_SP_D8) + CODE486_SP_H126) * (x1 - x0);
                b   = (CODE486_ABS_NEG(CODE486_SP_DC) - CODE486_SP_H128) * (z1 - z0);
                if (b < gap && (CODE486_SP_FF & 1))
                {
                    type = 4;
                    goto side_x;
                }
                if (gap < b && (CODE486_SP_FF & 8))
                {
                    type = 6;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x31:
        case 0x32:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                gap = (CODE486_ABS_NEG(CODE486_SP_D8) - CODE486_SP_H124) * (x1 - x0);
                b   = (CODE486_ABS_NEG(CODE486_SP_DC) - CODE486_SP_H128) * (z1 - z0);
                if (b < gap && (CODE486_SP_FF & 2))
                {
                    type = 4;
                    goto side_x;
                }
                if (gap < b && (CODE486_SP_FF & 8))
                {
                    type = 7;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x41:
        case 0x42:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                gap = (CODE486_ABS_NEG(CODE486_SP_D8) + CODE486_SP_H126) * (x1 - x0);
                b   = (CODE486_ABS_NEG(CODE486_SP_DC) + CODE486_SP_H12A) * (z1 - z0);
                if (b < gap && (CODE486_SP_FF & 1))
                {
                    type = 5;
                    goto side_x;
                }
                if (gap < b && (CODE486_SP_FF & 4))
                {
                    type = 6;
                    goto side_z;
                }
                goto corner;
            }
            break;
        case 0x51:
        case 0x52:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result               = 1;
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                gap = (CODE486_ABS_NEG(CODE486_SP_D8) + CODE486_SP_H126) * (x1 - x0);
                b   = (CODE486_ABS_NEG(CODE486_SP_DC) - CODE486_SP_H128) * (z1 - z0);
                if (b < gap && (CODE486_SP_FF & 2))
                {
                    type = 5;
                    goto side_x;
                }
                if (gap < b && (CODE486_SP_FF & 4))
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
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                CODE486_SP_POS_F0->y = top;
                CODE486_SP_POS_F8->y = bottom;
                result               = 1;
                if (CODE486_SP_D2 >= 0)
                {
                    CODE486_SP_POS_C0->y = top;
                    CODE486_SP_F6W       = 0x100;
                    break;
                }
                goto corner;
            }
            break;
        case 0x8:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 8) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (CODE486_SP_H12A - CODE486_SP_H128) / (z1 - z0);
            height = y0 + (y1 - y0) * (z1 - CODE486_SP_POS_C0->z) / (z1 - z0);
            gap    = CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
            if (height < min)
            {
                height = min;
            }
            b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F0->z += b;
            }
            flag = 0x20;
            goto floor;
        case 0x9:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 4) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (CODE486_SP_H12A - CODE486_SP_H128) / (z1 - z0);
            height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->z - z0) / (z1 - z0);
            gap    = CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z;
            if (height < min)
            {
                height = min;
            }
            b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F8->z -= b;
            }
            flag = 0x20;
            goto floor;
        case 0xA:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 1) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (CODE486_SP_H126 - CODE486_SP_H124) / (x1 - x0);
            height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->x - x0) / (x1 - x0);
            gap    = CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x;
            if (height < min)
            {
                height = min;
            }
            b = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F8->x -= b;
            }
            flag = 0x10;
            goto floor;
        case 0xB:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 2) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            y0 -= (y1 - y0) * (CODE486_SP_H126 - CODE486_SP_H124) / (x1 - x0);
            height = y0 + (y1 - y0) * (x1 - CODE486_SP_POS_C0->x) / (x1 - x0);
            gap    = CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x;
            if (height < min)
            {
                height = min;
            }
            b = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F0->x += b;
            }
            flag = 0x10;
            goto floor;
        case 0xC:
            y0 += (y0 - y1) - (y1 - y0) * (CODE486_SP_H12A - CODE486_SP_H128) / (z1 - z0);
            if (CODE486_SP_POS_C0->z < z0 + (z1 - z0) / 2)
            {
                height = y0 + (y1 - y0) * (z1 - CODE486_SP_POS_C0->z) / (z1 - z0);
                if (height < min)
                {
                    height = min;
                }
                gap = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (gap > 0)
                {
                    CODE486_SP_POS_F0->z += gap;
                }
                gap = CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
            }
            else
            {
                height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->z - z0) / (z1 - z0);
                if (height < min)
                {
                    height = min;
                }
                gap = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (gap > 0)
                {
                    CODE486_SP_POS_F8->z -= gap;
                }
                gap = CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z;
            }
            flag = 0x20;
            goto floor;
        case 0xD:
            y0 += (y0 - y1) - (y1 - y0) * (CODE486_SP_H126 - CODE486_SP_H124) / (x1 - x0);
            if (x0 + (x1 - x0) / 2 < CODE486_SP_POS_C0->x)
            {
                height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->x - x0) / (x1 - x0);
                if (height < min)
                {
                    height = min;
                }
                gap = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (gap > 0)
                {
                    CODE486_SP_POS_F8->x -= gap;
                }
                gap = -CODE486_SP_POS_C0->x + CODE486_SP_POS_F8->x;
            }
            else
            {
                height = y0 + (y1 - y0) * (x1 - CODE486_SP_POS_C0->x) / (x1 - x0);
                if (height < min)
                {
                    height = min;
                }
                gap = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (gap > 0)
                {
                    CODE486_SP_POS_F0->x += gap;
                }
                gap = CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x;
            }
            flag = 0x10;
            goto floor;
        case 0xE:
            dx     = x1 - x0;
            near   = CODE486_SP_POS_C0->z - z0;
            dz     = z1 - z0;
            far    = z1 - CODE486_SP_POS_C0->z;
            near_x = near * dx / dz;
            far_x  = far * dx / dz;
            y0 += y0 - y1;
            gap = (CODE486_SP_POS_C0->x < x0 + near_x) * 2;
            if (CODE486_SP_POS_C0->x < x0 + far_x)
            {
                gap |= 1;
            }
            switch (gap)
            {
                case 0:
                    height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->x - x0) / dx;
                    gap    = dx * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                    if (gap > 0)
                    {
                        CODE486_SP_POS_F8->x -= gap;
                    }
                    flag = 0x10;
                    gap  = -CODE486_SP_POS_C0->z + CODE486_SP_POS_F8->x;
                    goto floor;
                case 1:
                    height = y0 + (y1 - y0) * far / dz;
                    gap    = dz * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                    if (gap > 0)
                    {
                        CODE486_SP_POS_F0->z += gap;
                    }
                    flag = 0x20;
                    gap  = CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
                    goto floor;
                case 2:
                    height = y0 + (y1 - y0) * near / dz;
                    gap    = dz * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                    if (gap > 0)
                    {
                        CODE486_SP_POS_F8->z -= gap;
                    }
                    flag = 0x20;
                    gap  = CODE486_SP_POS_C0->z + CODE486_SP_POS_F8->z;
                    goto floor;
                case 3:
                    height = y0 + (y1 - y0) * (x1 - CODE486_SP_POS_C0->x) / dx;
                    gap    = dx * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                    if (gap > 0)
                    {
                        CODE486_SP_POS_F0->x += gap;
                    }
                    flag = 0x10;
                    gap  = CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x;
                    goto floor;
            }
            goto floor;
        case 0x10:
            y0 += (y1 - y0) * (CODE486_SP_H12A - CODE486_SP_H128) / (z1 - z0);
            height = y0 + (y1 - y0) * (z1 - CODE486_SP_POS_C0->z) / (z1 - z0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x11:
            y0 += (y1 - y0) * (CODE486_SP_H12A - CODE486_SP_H128) / (z1 - z0);
            height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->z - z0) / (z1 - z0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x12:
            y0 += (y1 - y0) * (CODE486_SP_H126 - CODE486_SP_H124) / (x1 - x0);
            height = y0 + (y1 - y0) * (CODE486_SP_POS_C0->x - x0) / (x1 - x0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x13:
            y0 += (y1 - y0) * (CODE486_SP_H126 - CODE486_SP_H124) / (x1 - x0);
            height = y0 + (y1 - y0) * (x1 - CODE486_SP_POS_C0->x) / (x1 - x0);
            if (y1 < height)
            {
                height = y1;
            }
            goto ceil;
        case 0x18:
        case 0x24:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 9) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x <=
                      CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z)
                         ? CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x
                         : CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
            height = y0 + (y1 - y0) * ((CODE486_SP_POS_C0->x - x0) + (z1 - CODE486_SP_POS_C0->z)) /
                              (x1 - x0);
            if (type != 0x18)
            {
                b = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F8->x -= b;
                }
                b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F0->z += b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x25:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 6) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x <=
                      CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z)
                         ? CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x
                         : CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
            height = y1 - (y1 - y0) * ((CODE486_SP_POS_C0->x - x0) + (z1 - CODE486_SP_POS_C0->z)) /
                              (x1 - x0);
            b      = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F8->x -= b;
            }
            b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F0->z += b;
            }
            flag = 0x30;
            goto floor;
        case 0x19:
        case 0x34:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 0xA) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x <=
                      CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z)
                         ? CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x
                         : CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
            height = y0 + (y1 - y0) * ((x1 - CODE486_SP_POS_C0->x) + (z1 - CODE486_SP_POS_C0->z)) /
                              (x1 - x0);
            if (type != 0x19)
            {
                b = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F0->x += b;
                }
                b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F0->z += b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x35:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 5) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x <=
                      CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z)
                         ? CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x
                         : CODE486_SP_POS_C0->z - CODE486_SP_POS_F0->z;
            height = y1 - (y1 - y0) * ((x1 - CODE486_SP_POS_C0->x) + (z1 - CODE486_SP_POS_C0->z)) /
                              (x1 - x0);
            b      = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F0->x += b;
            }
            b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F0->z += b;
            }
            flag = 0x30;
            goto floor;
        case 0x1A:
        case 0x44:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 5) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x <=
                      CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z)
                         ? CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x
                         : CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z;
            height = y0 + (y1 - y0) * ((CODE486_SP_POS_C0->x - x0) + (CODE486_SP_POS_C0->z - z0)) /
                              (x1 - x0);
            if (type != 0x1A)
            {
                b = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F8->x -= b;
                }
                b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F8->z -= b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x45:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 0xA) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x <=
                      CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z)
                         ? CODE486_SP_POS_F8->x - CODE486_SP_POS_C0->x
                         : CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z;
            height = y1 - (y1 - y0) * ((CODE486_SP_POS_C0->x - x0) + (CODE486_SP_POS_C0->z - z0)) /
                              (x1 - x0);
            b      = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F8->x -= b;
            }
            b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F8->z -= b;
            }
            flag = 0x30;
            goto floor;
        case 0x1B:
        case 0x54:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 6) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x <=
                      CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z)
                         ? CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x
                         : CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z;
            height = y0 + (y1 - y0) * ((x1 - CODE486_SP_POS_C0->x) + (CODE486_SP_POS_C0->z - z0)) /
                              (x1 - x0);
            if (type != 0x1B)
            {
                b = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F0->x += b;
                }
                b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
                if (b > 0)
                {
                    CODE486_SP_POS_F8->z -= b;
                }
            }
            flag = 0x30;
            goto floor;
        case 0x55:
            if (CODE486_SP_F6 == 0 && (CODE486_SP_FF & 9) && CODE486_SP_POS_C0->y - top < 0x20)
            {
                goto step;
            }
            gap    = (CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x <=
                      CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z)
                         ? CODE486_SP_POS_C0->x - CODE486_SP_POS_F0->x
                         : CODE486_SP_POS_F8->z - CODE486_SP_POS_C0->z;
            height = y1 - (y1 - y0) * ((x1 - CODE486_SP_POS_C0->x) + (CODE486_SP_POS_C0->z - z0)) /
                              (x1 - x0);
            b      = (x1 - x0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F0->x += b;
            }
            b = (z1 - z0) * (y1 - CODE486_SP_POS_C0->y) / (y1 - y0);
            if (b > 0)
            {
                CODE486_SP_POS_F8->z -= b;
            }
            flag = 0x30;
            goto floor;
        step:
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                CODE486_SP_POS_C0->y = top;
                CODE486_SP_108       = 0;
                CODE486_SP_FF        = 0x20;
                CODE486_SP_106       = CODE486_SP_112;
                CODE486_SP_10A       = CODE486_SP_116;
                result               = 1;
            }
            break;
        corner:
            if (func_8004FF14(CODE486_SP_POS_C0, (type >> 4) - 2) != 0)
            {
                if (CODE486_SP_D2 >= 0)
                {
                    landed         = 0x100;
                    CODE486_SP_F6W = landed;
                }
                goto clear;
            }
            break;
        floor:
            height -= CODE486_SP_12E;
            if (height < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < bottom)
            {
                result = 1;
                if (CODE486_SP_F6 == 0 && CODE486_SP_POS_C0->y - height < 0x20 &&
                    CODE486_SP_POS_C0->y - top < gap)
                {
                    CODE486_SP_POS_C0->y = height;
                    CODE486_SP_108       = 0;
                    break;
                }
                CODE486_SP_POS_F0->y = height;
                CODE486_SP_POS_F8->y = bottom;
                if (func_8004F44C(CODE486_SP_POS_C0, CODE486_SP_POS_C8, flag | 0x43) != 0)
                {
                    CODE486_SP_106 = 0;
                    CODE486_SP_108 = 0;
                    CODE486_SP_10A = 0;
                }
                if (CODE486_SP_D2 >= 0)
                {
                    CODE486_SP_F6W = 0x100;
                }
            }
            break;
        ceil:
            height -= CODE486_SP_12C;
            if (top < CODE486_SP_POS_C0->y && CODE486_SP_POS_C0->y < height)
            {
                result               = 1;
                CODE486_SP_POS_C0->y = height + 1;
            clear:
                CODE486_SP_106 = 0;
                CODE486_SP_108 = 0;
            clear_x:
                CODE486_SP_10A = 0;
            }
            break;
    }
    return result;
}

sint32 func_8004E304(uint16 *rect)
{
    sint32 x0;
    sint32 x1;
    sint32 y0;
    sint32 y1;
    sint16 clip;
    sint16 clip_y;
    sint32 dy;
    sint32 result;

    x0   = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
    x1   = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
    y0   = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
    y1   = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    clip = CODE486_SP_POS_C0->x;
    if (x0 < clip && clip < x1)
    {
        clip_y = CODE486_SP_CLIP_C4;
        if (y0 < clip_y && clip_y < y1)
        {
            dy            = y1 - y0;
            CODE486_SP_F0 = x0;
            CODE486_SP_F8 = x1;
            CODE486_SP_F4 = y0;
            CODE486_SP_FC = y1;
            result        = (clip < x0 + (clip_y - y0) * (x1 - x0) / dy) * 2;
            if (clip < x0 + (y1 - clip_y) * (x1 - x0) / dy)
            {
                result |= 1;
            }
            return result + 1;
        }
    }
    return 0;
}

sint32 func_8004E488(void)
{
    return 0;
}

sint32 func_8004E490(uint16 *rect, sint32 kind)
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
    PL_SHORT_VECTOR *pos;

    if (kind != 0x25)
    {
        x0 = (sint16)(rect[0] += CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] += CODE486_SP_OFSH4.h128);
    }
    else
    {
        x0 = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] += CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] += CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    }
    pos = CODE486_SP_POS_C0;
    cz  = pos->z;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x0 + (cz - z0) * w / d + 4;
    if (x1 < xl)
    {
        xl = x1;
    }
    cx = pos->x;
    zl = z0 + (cx - x0) * d / w - 4;
    if (zl < z0)
    {
        zl = z0;
    }
    if (x0 < cx && cx < xl && zl < cz && cz < z1)
    {
        CODE486_SP_F0 = x0;
        CODE486_SP_F8 = xl;
        CODE486_SP_F4 = zl;
        CODE486_SP_FC = z1;
        pz            = CODE486_SP_CC;
        xl            = x0 + (pz - z0) * w / d;
        px            = CODE486_SP_C8;
        zl            = z0 + (px - x0) * d / w;
        if (px < xl || zl < pz)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

sint32 func_8004E750(uint16 *rect, sint32 kind)
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
    PL_SHORT_VECTOR *pos;

    if (kind != 0x35)
    {
        x0 = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] += CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] += CODE486_SP_OFSH4.h128);
    }
    else
    {
        x0 = (sint16)(rect[0] += CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] += CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    }
    pos = CODE486_SP_POS_C0;
    cz  = pos->z;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x1 - (cz - z0) * w / d - 4;
    if (xl < x0)
    {
        xl = x0;
    }
    cx = pos->x;
    zl = z1 - (cx - x0) * d / w - 4;
    if (zl < z0)
    {
        zl = z0;
    }
    if (xl < cx && cx < x1 && zl < cz && cz < z1)
    {
        CODE486_SP_F0 = xl;
        CODE486_SP_F8 = x1;
        CODE486_SP_F4 = zl;
        CODE486_SP_FC = z1;
        pos           = CODE486_SP_POS_C8;
        pz            = pos->z;
        xl            = x1 - (pz - z0) * w / d;
        px            = pos->x;
        zl            = z1 - (px - x0) * d / w;
        if (xl < px || zl < pz)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

sint32 func_8004EA10(uint16 *rect, sint32 kind)
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
    PL_SHORT_VECTOR *pos;

    if (kind != 0x45)
    {
        x0 = (sint16)(rect[0] += CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] += CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    }
    else
    {
        x0 = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] += CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] += CODE486_SP_OFSH4.h128);
    }
    pos = CODE486_SP_POS_C0;
    cz  = pos->z;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x1 - (cz - z0) * w / d + 4;
    if (x1 < xl)
    {
        xl = x1;
    }
    cx = pos->x;
    zl = z1 - (cx - x0) * d / w + 4;
    if (z1 < zl)
    {
        zl = z1;
    }
    if (x0 < cx && cx < xl && z0 < cz && cz < zl)
    {
        CODE486_SP_F0 = x0;
        CODE486_SP_F8 = xl;
        CODE486_SP_F4 = z0;
        CODE486_SP_FC = zl;
        pos           = CODE486_SP_POS_C8;
        pz            = pos->z;
        xl            = x1 - (pz - z0) * w / d;
        px            = pos->x;
        zl            = z1 - (px - x0) * d / w;
        if (px < xl || pz < zl)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

sint32 func_8004ECD0(uint16 *rect, sint32 kind)
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
    PL_SHORT_VECTOR *pos;

    if (kind != 0x55)
    {
        x0 = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] += CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] += CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    }
    else
    {
        x0 = (sint16)(rect[0] += CODE486_SP_OFSH4.h126);
        x1 = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
        z0 = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
        z1 = (sint16)(rect[3] += CODE486_SP_OFSH4.h128);
    }
    pos = CODE486_SP_POS_C0;
    cz  = pos->z;
    w   = x1 - x0;
    d   = z1 - z0;
    xl  = x0 + (cz - z0) * w / d - 4;
    if (xl < x0)
    {
        xl = x0;
    }
    cx = pos->x;
    zl = z0 + (cx - x0) * d / w + 4;
    if (z1 < zl)
    {
        zl = z1;
    }
    if (xl < cx && cx < x1 && z0 < cz && cz < zl)
    {
        CODE486_SP_F0 = xl;
        CODE486_SP_F8 = x1;
        CODE486_SP_F4 = z0;
        CODE486_SP_FC = zl;
        pos           = CODE486_SP_POS_C8;
        pz            = pos->z;
        xl            = x0 + (pz - z0) * w / d;
        px            = pos->x;
        zl            = z0 + (px - x0) * d / w;
        if (xl < px || pz < zl)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

// Rect clipped to the octagon around C0/C4: the rect is narrowed by the offsets and tested
// against the point; only a hit stores the narrowed rect.
sint32 func_8004EF90(uint16 *rect)
{
    sint32 x0;
    sint32 x1;
    sint32 y0;
    sint32 y1;
    sint32 offx;
    sint32 offy;

    x0   = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
    x1   = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
    y0   = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
    y1   = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    offx = CODE486_ABS_NEG(y0 + (y1 - y0) / 2 - CODE486_SP_POS_C0->z) * (x1 - x0) / (y1 - y0);
    offy = CODE486_ABS_NEG(x0 + (x1 - x0) / 2 - CODE486_SP_POS_C0->x) * (y1 - y0) / (x1 - x0);
    if (x0 + offx < CODE486_SP_POS_C0->x && CODE486_SP_POS_C0->x < x1 - offx &&
        y0 + offy < CODE486_SP_POS_C0->z && CODE486_SP_POS_C0->z < y1 - offy)
    {
        CODE486_SP_POS_F0->x = x0 + offx;
        CODE486_SP_POS_F8->x = x1 - offx;
        CODE486_SP_POS_F0->z = y0 + offy;
        CODE486_SP_POS_F8->z = y1 - offy;
        return 1;
    }
    return 0;
}

// Octagon test (0x16A1 = sqrt(2) in 4.12): the rect is cut by the corner offsets, and a hit
// stores the cut rect widened by 0x35/256 of its size, clamped by the rect's edges.
sint32 func_8004F150(uint16 *rect)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 cut_x;
    sint32 cut_z;

    x0 = (sint16)(rect[0] -= CODE486_SP_OFSH4.h126);
    x1 = (sint16)(rect[1] -= CODE486_SP_OFSH4.h124);
    z0 = (sint16)(rect[2] -= CODE486_SP_OFSH4.h12a);
    z1 = (sint16)(rect[3] -= CODE486_SP_OFSH4.h128);
    if (x0 < CODE486_SP_POS_C0->x && CODE486_SP_POS_C0->x < x1 && z0 < CODE486_SP_POS_C0->z &&
        CODE486_SP_POS_C0->z < z1)
    {
        cut_x = (CODE486_ABS_NEG(z0 + (z1 - z0) / 2 - CODE486_SP_POS_C0->z) * (x1 - x0) /
                 (z1 - z0) * 0x16A1) >>
                12;
        cut_z = (CODE486_ABS_NEG(x0 + (x1 - x0) / 2 - CODE486_SP_POS_C0->x) * (z1 - z0) /
                 (x1 - x0) * 0x16A1) >>
                12;
        if (x0 + cut_x < CODE486_SP_POS_C0->x && CODE486_SP_POS_C0->x < x1 - cut_x &&
            z0 + cut_z < CODE486_SP_POS_C0->z && CODE486_SP_POS_C0->z < z1 - cut_z)
        {
            CODE486_SP_POS_F0->x = x0 + cut_x - (((x1 - x0) * 0x35) >> 8);
            if (CODE486_SP_POS_F0->x < x0)
            {
                CODE486_SP_POS_F0->x = x0;
            }
            CODE486_SP_POS_F8->x = x1 - cut_x + (((x1 - x0) * 0x35) >> 8);
            if (x1 < CODE486_SP_POS_F8->x)
            {
                CODE486_SP_POS_F8->x = x1;
            }
            CODE486_SP_POS_F0->z = z0 + cut_z - (((z1 - z0) * 0x35) >> 8);
            if (z0 < CODE486_SP_POS_F0->z)
            {
                CODE486_SP_POS_F0->z = z0;
            }
            CODE486_SP_POS_F8->z = z1 - cut_z + (((z1 - z0) * 0x35) >> 8);
            if (z1 < CODE486_SP_POS_F8->z)
            {
                CODE486_SP_POS_F8->z = z1;
            }
            return 1;
        }
    }
    return 0;
}

// Same layout as the banked func_8004F8BC (if/else push assignments, ABS_NEG, per-path
// calls). The x-only, z-only and both-x paths jump to one final `return 0`: with their own
// returns the x-only tail cross-jumped onto the last `li v0,0` instead of into the both-x
// tail. The z-only push sits one do/while (0) level deeper (see func_8004AF28): GCC weights
// references by loop depth, and without it pos (14 refs over 155 insns) ranks below hit_x
// and they swap s1/s2. Any one to three of the five push groups wrapped match; four or more
// flip it back.
sint32 func_8004F44C(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 mode)
{
    PL_SHORT_VECTOR push;
    sint32 hit_x;
    sint32 hit_z;
    sint32 hit_y;
    sint32 ay;
    sint32 m;

    if (CODE486_SP_D0 >= 0)
    {
        push.x = CODE486_SP_F0 - CODE486_SP_POS_C0->x;
    }
    else
    {
        push.x = CODE486_SP_F8 - CODE486_SP_POS_C0->x;
    }
    if (CODE486_SP_D4 >= 0)
    {
        push.z = CODE486_SP_F4 - CODE486_SP_POS_C0->z;
    }
    else
    {
        push.z = CODE486_SP_FC - CODE486_SP_POS_C0->z;
    }
    if (CODE486_SP_D2 >= 0 || (mode & 2))
    {
        push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
    }
    else
    {
        push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
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
        return func_80050400(pos, prev, mode);
    }
    if (hit_x == 0)
    {
        if (hit_z != 0 && (hit_y == 0 || CODE486_ABS_NEG(push.y) > CODE486_ABS_NEG(push.z)))
        {
            do
            {
                pos->z += push.z;
                CODE486_SP_PUSH[8] = -push.z;
                func_80050BB4(&push);
            } while (0);
            goto done;
        }
    }
    else if (hit_z == 0)
    {
        if (hit_y == 0 || CODE486_ABS_NEG(push.y) > CODE486_ABS_NEG(push.x))
        {
            pos->x += push.x;
            CODE486_SP_PUSH[6] = -push.x;
            func_80050B74(&push);
            goto done;
        }
    }
    else
    {
        goto both;
    }
    pos->y += push.y;
    CODE486_SP_PUSH[1] = -push.y;
    return func_80050BF4(&push);

both:
    if (hit_y != 0)
    {
        if (CODE486_ABS_NEG(push.y) < ((CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.z))
                                           ? CODE486_ABS_NEG(push.x)
                                           : CODE486_ABS_NEG(push.z)))
        {
            pos->y += push.y;
            if (!(mode & 2))
            {
                CODE486_SP_PUSH[1] = -push.y;
            }
            return func_80050BF4(&push);
        }
    }
    if (CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.z))
    {
        pos->x += push.x;
        CODE486_SP_PUSH[6] = CODE486_SP_PUSH[0] = -push.x;
        func_80050B74(&push);
        goto done;
    }
    pos->z += push.z;
    CODE486_SP_PUSH[8] = CODE486_SP_PUSH[2] = -push.z;
    func_80050BB4(&push);
done:
    return 0;
}

sint32 func_8004F8BC(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 side)
{
    PL_SHORT_VECTOR push;
    sint32 hit;
    sint32 hit_y;

    if (side == 0)
    {
        push.z = CODE486_SP_F4 - CODE486_SP_POS_C0->z;
    }
    else
    {
        push.z = CODE486_SP_FC - CODE486_SP_POS_C0->z;
    }
    if (CODE486_SP_D2 >= 0)
    {
        push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
    }
    else
    {
        push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
    }
    hit   = func_80050A90(&push);
    hit_y = func_80050AFC(&push);
    if (hit != 0 || hit_y != 0)
    {
        if (hit_y != 0 && CODE486_ABS_NEG(push.y) < CODE486_ABS_NEG(push.z))
        {
            pos->y += push.y;
            CODE486_SP_PUSH[1] = -push.y;
            return func_80050BF4(&push);
        }
        pos->z += push.z;
        CODE486_SP_PUSH[2] = -push.z;
        func_80050BB4(&push);
        return 0;
    }
    else
    {
        if (CODE486_ABS_NEG((sint16)CODE486_SP_F2 - CODE486_SP_POS_C0->y) <
            CODE486_ABS_NEG((sint16)CODE486_SP_FA - CODE486_SP_POS_C0->y))
        {
            push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
        }
        else
        {
            push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
        }
        if (CODE486_ABS_NEG(CODE486_SP_F4 - CODE486_SP_POS_C0->z) <
            CODE486_ABS_NEG(CODE486_SP_FC - CODE486_SP_POS_C0->z))
        {
            push.z = CODE486_SP_F4 - CODE486_SP_POS_C0->z;
        }
        else
        {
            push.z = CODE486_SP_FC - CODE486_SP_POS_C0->z;
        }
        if (CODE486_ABS_NEG(push.y) < CODE486_ABS_NEG(push.z))
        {
            pos->y += push.y;
            prev->y += push.y;
            return func_80050BF4(&push);
        }
        pos->z += push.z;
        prev->z += push.z;
        func_80050BB4(&push);
        return 0;
    }
}

sint32 func_8004FBE8(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 side)
{
    PL_SHORT_VECTOR push;
    sint32 hit;
    sint32 hit_y;

    if (side != 0)
    {
        push.x = CODE486_SP_F0 - CODE486_SP_POS_C0->x;
    }
    else
    {
        push.x = CODE486_SP_F8 - CODE486_SP_POS_C0->x;
    }
    if (CODE486_SP_D2 >= 0)
    {
        push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
    }
    else
    {
        push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
    }
    hit   = func_80050A24(&push);
    hit_y = func_80050AFC(&push);
    if (hit != 0 || hit_y != 0)
    {
        if (hit_y != 0 && CODE486_ABS_NEG(push.y) < CODE486_ABS_NEG(push.x))
        {
            pos->y += push.y;
            CODE486_SP_PUSH[1] = -push.y;
            return func_80050BF4(&push);
        }
        pos->x += push.x;
        CODE486_SP_PUSH[0] = -push.x;
        func_80050B74(&push);
        return 0;
    }
    else
    {
        if (CODE486_ABS_NEG(CODE486_SP_F0 - CODE486_SP_POS_C0->x) <
            CODE486_ABS_NEG(CODE486_SP_F8 - CODE486_SP_POS_C0->x))
        {
            push.x = CODE486_SP_F0 - CODE486_SP_POS_C0->x;
        }
        else
        {
            push.x = CODE486_SP_F8 - CODE486_SP_POS_C0->x;
        }
        if (CODE486_ABS_NEG((sint16)CODE486_SP_F2 - CODE486_SP_POS_C0->y) <
            CODE486_ABS_NEG((sint16)CODE486_SP_FA - CODE486_SP_POS_C0->y))
        {
            push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
        }
        else
        {
            push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
        }
        if (CODE486_ABS_NEG(push.y) < CODE486_ABS_NEG(push.x))
        {
            pos->y += push.y;
            prev->y += push.y;
            return func_80050BF4(&push);
        }
        pos->x += push.x;
        prev->x += push.x;
        func_80050B74(&push);
        return 0;
    }
}

// The corner offset goes through cx so GCC keeps F8 - (x - 4) unfolded.
sint32 func_8004FF14(PL_SHORT_VECTOR *pos, sint32 corner)
{
    PL_SHORT_VECTOR push;
    sint32 cx;
    sint32 dx;
    sint32 dz;
    sint32 lo;
    sint32 n;
    sint32 dz0;

    switch (corner)
    {
        case 0:
            cx = pos->x - 4;
            dx = CODE486_SP_F8 - cx;
            cx = pos->z + 4;
            dz = CODE486_SP_F4 - cx;
            break;
        case 1:
            cx = pos->x + 4;
            dx = CODE486_SP_F0 - cx;
            cx = pos->z + 4;
            dz = CODE486_SP_F4 - cx;
            break;
        case 2:
            cx = pos->x - 4;
            dx = CODE486_SP_F8 - cx;
            cx = pos->z - 4;
            dz = CODE486_SP_FC - cx;
            break;
        case 3:
            cx = pos->x + 4;
            dx = CODE486_SP_F0 - cx;
            cx = pos->z - 4;
            dz = CODE486_SP_FC - cx;
            break;
        default:
            return 0;
    }
    // dz0 keeps the corner's z distance; multiplying into dz itself swaps the mult operands.
    lo     = dx * dz;
    n      = dx * dx + dz * dz;
    dz0    = dz;
    dz     = lo * dz0;
    push.x = dz / n;
    push.z = lo * dx / n;
    if (CODE486_SP_D2 > 0)
    {
        push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
    }
    else
    {
        push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
    }
    if (CODE486_SP_D2 == 0 || CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.y) ||
        CODE486_ABS_NEG(push.z) < CODE486_ABS_NEG(push.y))
    {
        pos->x += push.x;
        pos->z += push.z;
        CODE486_SP_PUSH[6] = -push.x;
        CODE486_SP_PUSH[8] = -push.z;
        func_80050B74(&push);
        func_80050BB4(&push);
        return 0;
    }
    pos->y += push.y;
    CODE486_MOVE_FLAGS = 0x20;
    CODE486_SP_PUSH[1] = -push.y;
    return 1;
}

sint32 func_800501E8(PL_SHORT_VECTOR *pos, sint32 corner)
{
    PL_SHORT_VECTOR push;
    sint32 dx;
    sint32 dz;
    sint32 adx;
    sint32 adz;

    switch (corner)
    {
        case 0:
            dx = CODE486_SP_F8 - pos->x;
            dz = CODE486_SP_F4 - pos->z;
            break;
        case 1:
            dx = CODE486_SP_F0 - pos->x;
            dz = CODE486_SP_F4 - pos->z;
            break;
        case 2:
            dx = CODE486_SP_F8 - pos->x;
            dz = CODE486_SP_FC - pos->z;
            break;
        case 3:
            dx = CODE486_SP_F0 - pos->x;
            dz = CODE486_SP_FC - pos->z;
            break;
        default:
            return 0;
    }
    adx = dx;
    if (adx < 0)
    {
        adx = -adx;
    }
    adz = CODE486_ABS_NEG(dz);
    if (adz < adx)
    {
        if (dx <= 0)
        {
            push.x = -adz;
        }
        else
        {
            push.x = adz;
        }
        push.z = dz;
    }
    else
    {
        push.x = dx;
        if (dz <= 0)
        {
            push.z = -adx;
        }
        else
        {
            push.z = adx;
        }
    }
    if (CODE486_SP_D2 > 0)
    {
        push.y = CODE486_SP_F2 - CODE486_SP_POS_C0->y;
    }
    else
    {
        push.y = CODE486_SP_FA - CODE486_SP_POS_C0->y;
    }
    if (CODE486_SP_D2 == 0 || CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.y))
    {
        pos->x += push.x;
        pos->z += push.z;
        func_80050B74(&push);
        func_80050BB4(&push);
        return 0;
    }
    pos->y += push.y;
    CODE486_MOVE_FLAGS = 0x20;
    CODE486_SP_102     = -push.y;
    return 1;
}

sint32 func_80050400(PL_SHORT_VECTOR *pos, PL_SHORT_VECTOR *prev, sint32 mode)
{
    PL_SHORT_VECTOR push;

    if (CODE486_ABS(CODE486_SP_F0 - pos->x) < CODE486_ABS(CODE486_SP_F8 - pos->x))
    {
        push.x = CODE486_SP_F0 - pos->x;
    }
    else
    {
        push.x = CODE486_SP_F8 - pos->x;
    }
    if (CODE486_ABS(CODE486_SP_F4 - pos->z) < CODE486_ABS(CODE486_SP_FC - pos->z))
    {
        push.z = CODE486_SP_F4 - pos->z;
    }
    else
    {
        push.z = CODE486_SP_FC - pos->z;
    }
    if (mode & 2)
    {
        push.y = CODE486_SP_F2 - pos->y;
    }
    else if (CODE486_ABS((sint16)CODE486_SP_F2 - pos->y) <
             CODE486_ABS((sint16)CODE486_SP_FA - pos->y))
    {
        push.y = CODE486_SP_F2 - pos->y;
    }
    else
    {
        push.y = CODE486_SP_FA - pos->y;
    }
    if (mode & 1)
    {
        if (CODE486_ABS_NEG(push.y) < ((CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.z))
                                           ? CODE486_ABS_NEG(push.x)
                                           : CODE486_ABS_NEG(push.z)) &&
            !(CODE486_MOVE_FLAGS & 0x30))
        {
            pos->y += push.y;
            prev->y += push.y;
            CODE486_SP_PUSH[1] = -push.y;
            return func_80050BF4(&push);
        }
    }
    if (!(CODE486_ABS_NEG(push.x) > CODE486_ABS_NEG(push.z)) && !(CODE486_MOVE_FLAGS & 3))
    {
        goto push_x;
    }
    if (!(CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.z)) && !(CODE486_MOVE_FLAGS & 0xC))
    {
        goto push_z;
    }
    if (CODE486_ABS_NEG(push.x) < CODE486_ABS_NEG(push.z))
    {
    push_x:
        pos->x += push.x;
        prev->x += push.x;
        func_80050B74(&push);
        return 0;
    }
push_z:
    pos->z += push.z;
    prev->z += push.z;
    func_80050BB4(&push);
    return 0;
}

sint32 func_80050808(PL_SHORT_VECTOR *vec)
{
    sint32 blocked;
    sint32 delta;
    sint32 vel;
    sint32 result;

    blocked = 0;
    delta   = CODE486_SP_D0;
    if (delta == 0)
    {
        blocked = 1;
    }
    else
    {
        vel = vec->x;
        if (delta < 0)
        {
            delta = -delta;
        }
        if (vel >= 0 ? delta < vel : delta < -vel)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (vec->x > 0)
        {
            if ((CODE486_MOVE_FLAGS & 2) == 0)
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
            if ((CODE486_MOVE_FLAGS & 1) == 0)
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

sint32 func_800508BC(PL_SHORT_VECTOR *vec)
{
    sint32 blocked;
    sint32 delta;
    sint32 vel;
    sint32 result;

    blocked = 0;
    delta   = CODE486_SP_D4;
    if (delta == 0)
    {
        blocked = 1;
    }
    else
    {
        vel = vec->z;
        if (delta < 0)
        {
            delta = -delta;
        }
        if (vel >= 0 ? delta < vel : delta < -vel)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (vec->z > 0)
        {
            if ((CODE486_MOVE_FLAGS & 8) == 0)
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
            if ((CODE486_MOVE_FLAGS & 4) == 0)
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

sint32 func_80050970(PL_SHORT_VECTOR *vec)
{
    sint32 blocked;
    sint32 delta;
    sint32 vel;
    sint32 result;

    blocked = 0;
    delta   = CODE486_SP_D2;
    if (delta == 0)
    {
        blocked = 1;
    }
    else
    {
        vel = vec->y;
        if (delta < 0)
        {
            delta = -delta;
        }
        if (vel >= 0 ? delta < vel : delta < -vel)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (vec->y > 0)
        {
            if ((CODE486_MOVE_FLAGS & 0x20) == 0)
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
            if ((CODE486_MOVE_FLAGS & 0x10) == 0)
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

sint32 func_80050A24(PL_SHORT_VECTOR *vec)
{
    sint32 result;

    result = CODE486_SP_D0 != 0;
    if (result)
    {
        if (vec->x > 0)
        {
            if ((CODE486_MOVE_FLAGS & 2) == 0)
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
            if ((CODE486_MOVE_FLAGS & 1) == 0)
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

sint32 func_80050A90(PL_SHORT_VECTOR *vec)
{
    sint32 result;

    result = CODE486_SP_D4 != 0;
    if (result)
    {
        if (vec->z > 0)
        {
            if ((CODE486_MOVE_FLAGS & 8) == 0)
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
            if ((CODE486_MOVE_FLAGS & 4) == 0)
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

sint32 func_80050AFC(PL_SHORT_VECTOR *vec)
{
    sint32 result;

    result = CODE486_SP_D2 != 0;
    if (result)
    {
        if (vec->y > 0)
        {
            if ((CODE486_MOVE_FLAGS & 0x20) == 0)
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
            if ((CODE486_MOVE_FLAGS & 0x10) == 0)
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

sint32 func_80050B68(PL_SHORT_VECTOR *vec)
{
    return vec->y != 0;
}

void func_80050B74(PL_SHORT_VECTOR *vec)
{
    if (CODE486_MOVE_FLAGS & 3)
    {
        *(uint16 *)0x1F800106 = 0;
    }
    if (vec->x > 0)
    {
        CODE486_MOVE_FLAGS = 1;
    }
    else
    {
        CODE486_MOVE_FLAGS = 2;
    }
}

void func_80050BB4(PL_SHORT_VECTOR *vec)
{
    if (CODE486_MOVE_FLAGS & 0xC)
    {
        *(uint16 *)0x1F80010A = 0;
    }
    if (vec->z > 0)
    {
        CODE486_MOVE_FLAGS = 4;
    }
    else
    {
        CODE486_MOVE_FLAGS = 8;
    }
}

sint32 func_80050BF4(PL_SHORT_VECTOR *vec)
{
    if (vec->y > 0)
    {
        CODE486_MOVE_FLAGS = 0x10;
        return 0;
    }
    CODE486_MOVE_FLAGS = 0x20;
    return 1;
}

// Case 3's exit search sits one loop level deeper (an extra do/while (0)), as in
// func_8004AF28: GCC weights references by loop depth, and only this depth ranks the
// exit+0xE pointer above ev.z (a0/a1) as retail does.
sint32 func_80050C2C(PL_WORK *pl)
{
    CODE486_EVENT ev;
    PL_WORK *obj;
    CODE486_EXIT *exit;
    sint32 kind;
    uint16 flags;
    sint32 dir;

    if (func_800514FC(pl, (sint32 *)pl->info78, &ev) == 0)
    {
        return 0;
    }
    obj = NULL;
    if (!(pl->value01 & 0xF0))
    {
        obj = pl;
        if ((sint8)obj->flags_bd != 0)
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
            for (exit = CODE486_EXIT_LIST; exit->id != -1; exit++)
            {
                if (ev.x == exit->x && ev.y == exit->y && ev.z == exit->z)
                {
                    D_800C3558.flags14  = -1;
                    D_800C3558.dest.v.x = exit->dest.v.x + obj->position.x - exit->x;
                    D_800C3558.dest.v.y = obj->position.y;
                    D_800C3558.dest.v.z = exit->dest.v.z + obj->position.z - exit->z;
                    D_800C3558.rot      = obj->rotation.y;
                    D_800C3558.stage    = exit->stage;
                    D_800C3558.room     = exit->room;
                    D_800C3558.flags15  = 0;
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
            for (exit = CODE486_EXIT_LIST; exit->id != -1; exit++)
            {
                if (ev.x == exit->x && ev.y == exit->y && ev.z == exit->z &&
                    ((ev.rot - exit->rot + 0x200) & 0xFFF) <= 0x400)
                {
                    if (func_800519E4(exit) != 0)
                    {
                        break;
                    }
                    if (func_80051A78(exit) != 0)
                    {
                        break;
                    }
                    D_800C3558.flags14  = 2;
                    D_800C3558.dest.b8  = exit->dest.b8;
                    D_800C3558.rot      = exit->dest.v.pad;
                    D_800C3558.stage    = exit->stage;
                    D_800C3558.room     = exit->room;
                    D_800C3558.flags15  = 0;
                    D_800C3558.fade_out = 0x15;
                    D_800C3558.fade_in  = 2;
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
            do
            {
                for (exit = CODE486_EXIT_LIST; exit->id != -1; exit++)
                {
                    if (ev.x == exit->x && ev.y == exit->y && ev.z == exit->z &&
                        !((ev.rot - exit->rot + 0x200) & 0x400))
                    {
                        dir = ((ev.rot + 0x200) / 0x400) & 3;
                        if (dir == 0 && pl->position.z < ev.z)
                        {
                            continue;
                        }
                        if (dir == 1 && pl->position.x < ev.x)
                        {
                            continue;
                        }
                        if (dir == 2 && ev.z < pl->position.z)
                        {
                            continue;
                        }
                        if (dir == 3 && ev.x < pl->position.x)
                        {
                            continue;
                        }
                        if (func_800519E4(exit) != 0)
                        {
                            break;
                        }
                        if (exit->id & 0x8000)
                        {
                            D_800C3558.from.b8  = *(PL_BYTES8 *)&ev;
                            D_800C3558.dest.b8  = exit->dest.b8;
                            D_800C3558.rot_from = exit->rot;
                            D_800C3558.rot      = exit->dest.v.pad;
                            D_800C3558.stage    = exit->stage;
                            D_800C3558.room     = exit->room;
                            D_800C3558.fade_out = 10;
                            D_800C3558.flags15  = 0;
                            D_800C3558.fade_in  = 2;
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
            for (exit = CODE486_EXIT_LIST; exit->id != -1; exit++)
            {
                if (ev.x == exit->x && ev.y == exit->y && ev.z == exit->z)
                {
                    if (func_800519E4(exit) != 0)
                    {
                        break;
                    }
                    D_800C3558.flags14  = 2;
                    D_800C3558.dest.b8  = exit->dest.b8;
                    D_800C3558.rot      = exit->dest.v.pad;
                    D_800C3558.stage    = exit->stage;
                    D_800C3558.room     = exit->room;
                    D_800C3558.flags15  = 0;
                    D_800C3558.fade_out = 0x15;
                    D_800C3558.fade_in  = 2;
                    func_8001F6C4();
                    break;
                }
            }
            break;
        case 0x10:
            if (pl->value74 != 0)
            {
                return kind;
            }
            if (Sce_flag_test(0x60F) != 0)
            {
                pl->position.x += 8;
                pl->position_fixed.x += 0x80000;
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
                func_80063BC8(0, 0, 0, D_8008AA58[kind] + (flags & 0xF));
            }
            break;
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0x10, 0, D_8008AA58[kind] + (flags & 0xF));
            }
            break;
        case 0x2C:
        case 0x2D:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0, 0, D_8008AA6C[flags & 0xF]);
            }
            break;
        case 0x2F:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0, 0, D_8008AA44[flags & 0xF]);
            }
            break;
        case 0x38:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0, 0, D_8008AA60[flags & 0xF]);
            }
            break;
        case 0x3B:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0, 0, D_8008AA68[flags & 0xF]);
            }
            break;
        case 0x44:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0, 0, D_8008AA50[flags & 0xF]);
            }
            break;
        case 0x50:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            if ((flags & 0xFF) == 0)
            {
                func_80063BC8(0, 0, 0, 6);
            }
            else if (CODE486_GAME_BYTE50 == 0xE)
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
                    func_80063BC8(0, 0, 0, 0xC);
                }
            }
            else
            {
                if (Sce_flag_test(0x49) == 0)
                {
                    func_80063BC8(0, 0, 0, 0x11);
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
                CODE486_GAME_HALF17A |= 0x40;
            }
            else
            {
                func_80063BC8(0, 0, 0, 1);
            }
            break;
        case 0x54:
            if (func_80051970(obj) != 0)
            {
                CODE486_GAME_WORD174 |= 1 << flags;
            }
            break;
        case 0x56:
            if (func_80051970(obj) == 0)
            {
                break;
            }
            if ((flags & 0xFF) == 0)
            {
                func_80063BC8(0, 0, 0, 0x1C);
            }
            break;
        case 0x60:
            if (func_80051970(obj) != 0)
            {
                func_80063BC8(0, 0x10, 0, D_8008AA70[flags & 0xF]);
            }
            break;
    }
    return kind;
}

// The identity matrix is built with eight word stores through a word view (field stores
// schedule the t words first). The do/while (0) levels below are loop-depth wrappers: they
// only raise register priorities (left s2, area s3, hit s4) to retail's.
sint32 func_800514FC(PL_WORK *pl, sint32 *ofs, CODE486_EVENT *out)
{
    PL_SHORT_VECTOR base;
    PL_SHORT_VECTOR ahead;
    PL_SHORT_VECTOR org;
    sint16 box[6];
    CODE486_SVECTOR dir;
    CODE486_SVECTOR moved;
    CODE486_MTX mtx;
    sint32 n;
    sint32 val;
    sint32 left;
    sint32 cy;
    CODE486_CELL *cell;
    CODE486_CELL_SOLID *solid;
    CODE486_AREA *area;
    CODE486_HIT *hit;

    ahead               = pl->position;
    base                = ahead;
    n                   = func_8004B1E0(&base, 0);
    ((sint32 *)&mtx)[0] = 0x1000;
    ((sint32 *)&mtx)[1] = 0;
    ((sint32 *)&mtx)[2] = 0x1000;
    ((sint32 *)&mtx)[3] = 0;
    ((sint32 *)&mtx)[4] = 0x1000;
    ((sint32 *)&mtx)[5] = 0;
    ((sint32 *)&mtx)[6] = 0;
    ((sint32 *)&mtx)[7] = 0;
    RotMatrixY(pl->rotation.y, &mtx);
    dir.vx = 0;
    dir.vy = 0;
    dir.vz = -0x40;
    ApplyMatrixSV(&mtx, &dir, &moved);
    ahead.x += moved.vx;
    ahead.z += moved.vz;
    if (ofs != NULL)
    {
        CODE486_SP_OFS.a = ofs[0];
        CODE486_SP_OFS.b = ofs[1];
        CODE486_SP_OFS.c = ofs[2];
    }
    else
    {
        CODE486_SP_OFS.a = 0;
        CODE486_SP_OFS.b = 0;
        CODE486_SP_OFS.c = 0;
    }
    while (n-- != 0)
    {
        val = func_80048CEC(CODE486_SP_CELLS[n]);
        if (val <= 0)
        {
            continue;
        }
        cell  = &CODE486_MAP_INFO[val];
        solid = (CODE486_CELL_SOLID *)(cell->value8 & 0xFFFFFF);
        if (cell->flags6 & 0xFFF)
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
                                area = solid->areas_a;
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
                                area = solid->areas_b;
                            } while (0);
                        } while (0);
                    } while (0);
                } while (0);
            } while (0);
        }
        org.x = cell->x;
        org.y = cell->y;
        org.z = cell->z;
        for (; area->hits != NULL; area++)
        {
            do
            {
                do
                {
                    box[0] = org.x + area->x0;
                    box[1] = org.x + area->x1;
                    box[2] = org.z + area->z0;
                    box[3] = org.z + area->z1;
                } while (0);
            } while (0);
            hit = area->hits;
            if (hit->kind < 0x100)
            {
                continue;
            }
            if (hit->pad & 0x8000)
            {
                *CODE486_SP_POS_C0 = ahead;
            }
            else
            {
                *CODE486_SP_POS_C0 = base;
            }
            if (((CODE486_BOX_TEST_FUNC)D_8008AA24[(hit->kind & 0xF0) >> 4])(box) == 0)
            {
                continue;
            }
            do
            {
                left = area->count;
            } while (0);
            do
            {
                box[4] = org.y + hit->y0 - CODE486_SP_OFSH4.h12e;
                box[5] = org.y + hit->y1 - CODE486_SP_OFSH4.h12c;
                func_8004A060(box, (uint8)hit->kind);
                cy = CODE486_SP_POS_C0->y;
                if (box[4] < cy && cy < box[5])
                {
                    out->x     = org.x + (area->x0 + area->x1) / 2;
                    out->y     = org.y + (hit->y0 + hit->y1) / 2;
                    out->z     = org.z + (area->z0 + area->z1) / 2;
                    out->rot   = pl->rotation.y;
                    out->kind  = hit->kind >> 8;
                    out->flags = hit->pad;
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
    uint32 pad;

    if (pl != 0)
    {
        state = pl->routine_1;
        pad   = pl->value11e;
        if (*(uint32 *)&pl->table180[0].z == 0)
        {
            if (state >= 2 && state != 4)
            {
                return 0;
            }
            if ((pad & pl->value136) == 0)
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

sint32 func_800519E4(CODE486_EXIT *exit)
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
    func_80063BC8(0, 0, 0, exit->value4);
    return 1;
}

sint32 func_80051A78(CODE486_EXIT *exit)
{
    switch (exit->value2)
    {
        case 0:
            return 0;
        case 1:
            if (CODE486_GAME_BYTE52 != 0)
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

void func_80051B68(PL_WORK *obj, sint32 arg1, sint32 arg2, uint32 arg3)
{
    if (obj->routine_0 & 3)
    {
        D_80098894->obj.pl = obj;
        D_80098894->value4 = arg1;
        D_80098894->value6 = arg2;
        D_80098894->value8 = arg3;
        D_80098894++;
    }
}

void func_80051BAC(PL_WORK *obj)
{
    PL_WORK **list;

    if (obj->routine_0 & 3)
    {
        list       = D_80098898;
        *list      = obj;
        D_80098898 = list + 1;
    }
    obj->value7c = 0;
}

// D_8009A770 is a stand-in solid inside D_8009A710, reached here through its own symbol.
void func_80051BE4(void)
{
    PL_WORK **pp;
    CODE486_REQ *req;
    sint32 result;
    sint32 count;
    sint32 kind;
    sint32 index;
    uint32 value;

    count = 0;
    pp    = D_800BC360;
    while (pp != D_80098898)
    {
        result = 0;
        req    = D_800BC058;
        while (req != D_80098894)
        {
            result = 0;
            if (req->obj.pl != *pp)
            {
                kind  = req->value4;
                index = req->value6;
                value = req->value8;
                switch (kind)
                {
                    case 0:
                        result = func_80052970((sint32)req->obj.pl, *pp, index, 0);
                        break;
                    case 1:
                        result =
                            func_80051F08((sint32)req->obj.pl, *pp, req->obj.pl, index, value, 0);
                        break;
                    case 2:
                        result = func_80052970((sint32)req->obj.pl, *pp, index, 1);
                        break;
                    case 3:
                        result =
                            func_80051F08((sint32)req->obj.pl, *pp, req->obj.pl, index, value, 1);
                        break;
                    case 4:
                    case 6:
                        D_8009A770.position.x = D_8009A770.position_prev.x = req->obj.prop->x;
                        D_8009A770.position.y = D_8009A770.position_prev.y = req->obj.prop->y;
                        D_8009A770.position.z = D_8009A770.position_prev.z = req->obj.prop->z;
                        D_8009A770.position_fixed.x = D_8009A770.position_fixed_prev.x =
                            D_8009A770.position.x << 16;
                        D_8009A770.position_fixed.y = D_8009A770.position_fixed_prev.y =
                            D_8009A770.position.y << 16;
                        D_8009A770.position_fixed.z = D_8009A770.position_fixed_prev.z =
                            D_8009A770.position.z << 16;
                        D_8009A770.rot.vx  = 0;
                        D_8009A770.rot.vy  = 0;
                        D_8009A770.rot.vz  = 0;
                        D_8009A770.value44 = 0;
                        D_8009A770.value46 = 0;
                        D_8009A770.value48 = 0;
                        D_8009A770.areas   = req->obj.prop->areas;
                        D_8009A770.info78  = req->obj.prop->info;
                        result             = func_80052970((sint32)&D_8009A770, *pp, -1, 1);
                        break;
                    case 5:
                    case 7:
                        D_8009A770.position.x = D_8009A770.position_prev.x = req->obj.prop->x;
                        D_8009A770.position.y = D_8009A770.position_prev.y = req->obj.prop->y;
                        D_8009A770.position.z = D_8009A770.position_prev.z = req->obj.prop->z;
                        D_8009A770.position_fixed.x = D_8009A770.position_fixed_prev.x =
                            D_8009A770.position.x << 16;
                        D_8009A770.position_fixed.y = D_8009A770.position_fixed_prev.y =
                            D_8009A770.position.y << 16;
                        D_8009A770.position_fixed.z = D_8009A770.position_fixed_prev.z =
                            D_8009A770.position.z << 16;
                        D_8009A770.rot.vx  = 0;
                        D_8009A770.rot.vy  = 0;
                        D_8009A770.rot.vz  = 0;
                        D_8009A770.value44 = 0;
                        D_8009A770.value46 = 0;
                        D_8009A770.value48 = 0;
                        D_8009A770.areas   = req->obj.prop->areas;
                        D_8009A770.info78  = req->obj.prop->info;
                        result = func_80051F08((sint32)&D_8009A770, *pp, req->obj.pl, -1, value, 1);
                        break;
                }
                if (result != 0)
                {
                    break;
                }
            }
            // The loop level (as in func_8004AF28) keeps req++ ahead of the end test and
            // gives req the reference count that ranks it above the stand-in base.
            do
            {
                req++;
            } while (0);
        }
        if (result != 0)
        {
            (*pp)->value7c = result;
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

sint32 func_80051F08(sint32 key, PL_WORK *pl, PL_WORK *obj, sint32 index, uint32 value8,
                     sint32 flag)
{
    CODE486_MTX mtx;
    PL_FIXED_VECTOR cur;
    PL_FIXED_VECTOR old;
    PL_FIXED_VECTOR move;
    PL_FIXED_VECTOR now;
    PL_FIXED_VECTOR prev;
    PL_FIXED_VECTOR delta;
    PL_FIXED_VECTOR push;
    PL_FIXED_VECTOR zero;
    CODE486_SVECTOR rot;
    sint32 result;
    sint32 slide;
    sint32 y;
    sint32 old74;
    sint32 lim;
    PL_SHORT_VECTOR unused; // unused; gives retail's frame size

    old74 = pl->value74;
    func_800536B0((PL_WORK *)key, &now, &prev, index);
    func_8004B3C0((sint32 *)pl->info78);
    slide = (func_8002FE74(pl->value01) == 0) << 15;
    if (func_80052674(pl, key, &now, flag, slide) == 0)
    {
        if (pl->value76 != 0 && (uint32)obj == pl->value_c0)
        {
            push.x = CODE486_SOLID_AT(key)->value44;
            push.y = CODE486_SOLID_AT(key)->value46;
            push.z = CODE486_SOLID_AT(key)->value48;
            if (flag == 0)
            {
                rot.vx = CODE486_SOLID_AT(key)->rot.vx - pl->rotation.x;
                rot.vy = CODE486_SOLID_AT(key)->rot.vy - pl->rotation.y;
                rot.vz = CODE486_SOLID_AT(key)->rot.vz - pl->rotation.z;
                if (pl->value01 == 0)
                {
                    rot.vx += pl->value114;
                    rot.vy += pl->value116;
                    rot.vz += pl->value118;
                }
                RotMatrixYXZ(&rot, &mtx);
                zero.x = 0;
                zero.y = 0;
                zero.z = 0;
                func_800301A8(&mtx, &push, &zero);
            }
            else if (pl->value01 == 0)
            {
                rot.vx = pl->value114;
                rot.vy = pl->value116;
                rot.vz = pl->value118;
                RotMatrixYXZ(&rot, &mtx);
                zero.x = 0;
                zero.y = 0;
                zero.z = 0;
                func_800301A8(&mtx, &push, &zero);
            }
            pl->value44 += push.x;
            pl->value48 += push.z;
            if (pl->value74 != 0)
            {
                pl->value46 += push.y;
            }
            else
            {
                pl->value46 += push.y - 0x200;
            }
            pl->value76  = 0;
            pl->value_c0 = 0;
            return 0x4000;
        }
        return 0;
    }
    cur           = pl->position_fixed;
    old           = pl->position_fixed_prev;
    move.x        = cur.x - old.x;
    move.y        = cur.y - old.y;
    move.z        = cur.z - old.z;
    delta.x       = now.x - prev.x;
    delta.y       = now.y - prev.y;
    delta.z       = now.z - prev.z;
    CODE486_SP_F6 = pl->value74;
    CODE486_SP_F7 = pl->value76;
    func_800534E0(key, pl, &now, &prev, &cur, &old);
    result = func_80052B04(key, &now, &cur, &old, flag, slide);
    if (result > 0)
    {
        if (move.x == 0 || (delta.x ^ move.x) < 0)
        {
            lim = (delta.x - move.x >= 0 ? delta.x - move.x : move.x - delta.x) - 0x80000;
            if (CODE486_ABS_NEG(move.x) < lim)
            {
                goto hit;
            }
        }
        if (move.y == 0 || (delta.y ^ move.y) < 0)
        {
            lim = (delta.y - move.y >= 0 ? delta.y - move.y : move.y - delta.y) - 0x80000;
            if (CODE486_ABS_NEG(move.y) < lim)
            {
                goto hit;
            }
        }
        if (move.z == 0 || (delta.z ^ move.z) < 0)
        {
            lim = (delta.z - move.z >= 0 ? delta.z - move.z : move.z - delta.z) - 0x80000;
            if (move.z >= 0 ? move.z < lim : -move.z < lim)
            {
            hit:
                if (pl->value01 == 0 && CODE486_SP_F7 == 0)
                {
                    pl->value188 = (pl->value188 + (value8 & 0xFF)) | (value8 & ~0xFF);
                    pl->value71  = (((((CODE486_SOLID_AT(key)->rot.vy - pl->rotation.y +
                                        (sint16)pl->value116) &
                                       0xFFF) +
                                      0x200) >>
                                     10) &
                                    3) +
                                       1 |
                                   0x80;
                }
            }
        }
        if (CODE486_SP_F6 == 0 && CODE486_SP_F7 != 0)
        {
            pl->value74  = CODE486_SP_F6;
            pl->value76  = CODE486_SP_F7;
            pl->value_c0 = (uint32)obj;
        }
    }
    else if (result < 0)
    {
        return 0;
    }
    pl->position_fixed.x = cur.x;
    pl->position_fixed.z = cur.z;
    if (func_80052674(pl, key, &now, flag, slide) != 0)
    {
        y = pl->position_fixed.y;
        if (D_80098AC0.y - 0x40000 < y && y < D_80098AC0.y + 0x200000 && pl->value74 == 0)
        {
            pl->position_fixed.y = D_80098AC0.y;
            pl->value76          = 1;
            pl->value_c0         = (uint32)obj;
        }
        else
        {
            pl->position_fixed.y = cur.y;
        }
    }
    else
    {
        pl->position_fixed.y = cur.y;
        if (pl->value76 != 0)
        {
            pl->value74  = old74;
            pl->value76  = 0;
            pl->value_c0 = 0;
        }
    }
    func_80030150(&pl->position_fixed, &pl->position);
    return result;
}

void func_80052528(sint32 key)
{
    sint32 i;
    uint32 mask;
    PL_WORK5F4 *players;
    PL_WORK3C0 *objs3c0;
    PL_WORK5A4 *objs5a4;
    PL_WORK10C *objs10c;

    mask    = D_8009888C;
    players = (PL_WORK5F4 *)&Player_work;
    for (i = 0; i < 2; i++, players++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, &players->link);
        }
    }
    objs3c0 = D_8009F108;
    mask    = D_800987E8;
    for (i = 0; i < 16; i++, objs3c0++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, &objs3c0->link);
        }
    }
    objs5a4 = D_800C3580;
    mask    = D_80098B20;
    for (i = 0; i < 4; i++, objs5a4++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, &objs5a4->link);
        }
    }
    objs10c = D_8009CF88;
    mask    = D_800987CC;
    for (i = 0; i < 32; i++, objs10c++)
    {
        if ((sint32)(mask << i) < 0)
        {
            func_80052644(key, &objs10c->link);
        }
    }
}

void func_80052644(sint32 key, CODE486_LINK *pl)
{
    if (pl->value76 != 0 && key == pl->value_c0)
    {
        pl->value76  = 0;
        pl->value_c0 = 0;
    }
}

// D_80098AC0 is a 16-byte vector reached through $gp (the file is built with -G32, see
// tools/cc.sh). The box corners sit one do/while (0) level deeper (see func_8004AF28): GCC
// weights references by loop depth, and only this ranks the area giv above hit and count.
// The solid is reached through key at each use (a separate pointer local reorders the
// prologue). The final negations in natural x, y, z order give retail's store order.
sint32 func_80052674(PL_WORK *pl, sint32 key, PL_FIXED_VECTOR *pos, sint32 keep, sint32 slide)
{
    sint16 box[6];
    CODE486_MTX mtx;
    CODE486_SVECTOR rot;
    CODE486_AREA *area;
    sint32 count;
    CODE486_HIT *hit;
    sint32 best;

    best = 0x7FFF;
    if (keep == 0)
    {
        D_80098AC0.x = pl->position_fixed.x;
        D_80098AC0.y = pl->position_fixed.y;
        D_80098AC0.z = pl->position_fixed.z;
        rot.vx       = -CODE486_SOLID_AT(key)->rot.vx;
        rot.vy       = -CODE486_SOLID_AT(key)->rot.vy;
        rot.vz       = -CODE486_SOLID_AT(key)->rot.vz;
        RotMatrix(&rot, &mtx);
        func_800301A8(&mtx, &D_80098AC0, pos);
        func_80030150(&D_80098AC0, CODE486_SP_POS_C0);
    }
    else
    {
        *(PL_BYTES8 *)CODE486_SP_POS_C0 = *(PL_BYTES8 *)&pl->position;
    }
    func_80030150(pos, CODE486_SP_POS_E0);
    area = *CODE486_SOLID_AT(key)->areas;
    while (area->hits != NULL)
    {
        do
        {
            box[0] = CODE486_SP_POS_E0->x + area->x0;
            box[1] = CODE486_SP_POS_E0->x + area->x1;
            box[2] = CODE486_SP_POS_E0->z + area->z0;
            box[3] = CODE486_SP_POS_E0->z + area->z1;
        } while (0);
        hit = area->hits;
        if (D_8008AA24[(hit->kind & 0xF0) >> 4](box, hit->kind) != 0)
        {
            count = area->count;
            do
            {
                box[4] = CODE486_SP_POS_E0->y + hit->y0;
                box[5] = CODE486_SP_POS_E0->y + hit->y1;
                func_8004A060(box, hit->kind);
                if (box[4] < best && CODE486_SP_POS_C0->y <= box[5])
                {
                    best = box[4];
                }
                hit++;
            } while (--count != 0);
        }
        area++;
    }
    if (best == 0x7FFF || CODE486_SP_POS_C0->y < best - 0x20)
    {
        return 0;
    }
    D_80098AC0.y = best << 16;
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

// mtx and delta are unused (left over from the func_80051F08 template); they give retail's
// 0xA8 frame and stack layout.
sint32 func_80052970(sint32 arg0, PL_WORK *pl, sint32 index, sint32 arg3)
{
    CODE486_MTX mtx;
    PL_FIXED_VECTOR cur;
    PL_FIXED_VECTOR old;
    PL_FIXED_VECTOR now;
    PL_FIXED_VECTOR prev;
    PL_FIXED_VECTOR delta;
    sint32 result;
    sint32 slide;

    func_800536B0((PL_WORK *)arg0, &now, &prev, index);
    result = 0;
    func_8004B3C0((sint32 *)pl->info78);
    slide = (func_8002FE74(pl->value01) == 0) << 15;
    if (func_80052674(pl, arg0, &now, arg3, slide) != 0)
    {
        cur = pl->position_fixed;
        old = pl->position_fixed_prev;
        func_800534E0(arg0, pl, &now, &prev, &cur, &old);
        result = func_80052B04(arg0, &now, &cur, &old, arg3, slide);
        if (result != 0)
        {
            if (result & 0x300)
            {
                pl->position_fixed.x = cur.x;
            }
            if (result & 0xC00)
            {
                pl->position_fixed.z = cur.z;
            }
            if (result & 0x3000)
            {
                pl->position_fixed.y = cur.y;
            }
            func_80030150(&pl->position_fixed, &pl->position);
        }
    }
    return result;
}

// Solid-object collision. The retry loop is a goto: a for (;;) lets loop.c hoist
// slide ^ 0x8000 out of both loop levels, where retail recomputes it before the area loop.
// The push block copies PUSH[0..2]/[6..8] straight into [3..5]/[9..11] after moving C0 by
// PUSH[3..5] (no temporaries), then clears the sources. The do { } while (0) around the
// box corners (as in func_80049C54) ranks &area->hits above left and hit, as retail.
sint32 func_80052B04(sint32 key, PL_FIXED_VECTOR *now, PL_FIXED_VECTOR *cur, PL_FIXED_VECTOR *old,
                     sint32 keep, sint32 slide)
{
    CODE486_MTX mtx;
    CODE486_SVECTOR rot;
    PL_SHORT_VECTOR start;
    sint16 box[6];
    sint32 tries;
    CODE486_AREA *area;
    CODE486_HIT *hit;
    sint32 count;
    sint32 test;
    sint32 found;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 result;

    tries              = 0;
    CODE486_MOVE_FLAGS = 0;
    found              = 0;
    if (keep == 0)
    {
        rot.vx = -CODE486_SOLID_AT(key)->rot.vx;
        rot.vy = -CODE486_SOLID_AT(key)->rot.vy;
        rot.vz = -CODE486_SOLID_AT(key)->rot.vz;
        RotMatrix(&rot, &mtx);
        func_800301A8(&mtx, old, now);
        func_800301A8(&mtx, cur, now);
    }
    func_80030150(now, CODE486_SP_POS_E0);
    func_80030150(old, CODE486_SP_POS_C8);
    func_80030150(cur, CODE486_SP_POS_C0);
    start               = *CODE486_SP_POS_C0;
    CODE486_SP_PUSH[0]  = 0;
    CODE486_SP_PUSH[1]  = 0;
    CODE486_SP_PUSH[2]  = 0;
    CODE486_SP_PUSH[3]  = 0;
    CODE486_SP_PUSH[4]  = 0;
    CODE486_SP_PUSH[5]  = 0;
    CODE486_SP_PUSH[6]  = 0;
    CODE486_SP_PUSH[7]  = 0;
    CODE486_SP_PUSH[8]  = 0;
    CODE486_SP_PUSH[9]  = 0;
    CODE486_SP_PUSH[10] = 0;
    CODE486_SP_PUSH[11] = 0;
retry:
    area                 = *CODE486_SOLID_AT(key)->areas;
    CODE486_SP_POS_D0->x = CODE486_SP_POS_C0->x - CODE486_SP_POS_C8->x;
    CODE486_SP_POS_D0->y = CODE486_SP_POS_C0->y - CODE486_SP_POS_C8->y;
    CODE486_SP_POS_D0->z = CODE486_SP_POS_C0->z - CODE486_SP_POS_C8->z;
    while (area->hits != NULL)
    {
        do
        {
            box[0] = CODE486_SP_POS_E0->x + area->x0;
            box[1] = CODE486_SP_POS_E0->x + area->x1;
            box[2] = CODE486_SP_POS_E0->z + area->z0;
            box[3] = CODE486_SP_POS_E0->z + area->z1;
        } while (0);
        hit  = area->hits;
        test = D_8008AA24[(hit->kind & 0xF0) >> 4](box, hit->kind);
        if (test == 0)
        {
            found = 0;
        }
        else
        {
            count = area->count;
            do
            {
                if (!(hit->pad & (slide ^ 0x8000) & 0x8000))
                {
                    box[4] = CODE486_SP_POS_E0->y + hit->y0;
                    box[5] = CODE486_SP_POS_E0->y + hit->y1;
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
        CODE486_SP_POS_C0->x += CODE486_SP_PUSH[3];
        CODE486_SP_POS_C0->z += CODE486_SP_PUSH[5];
        CODE486_SP_POS_C0->y += CODE486_SP_PUSH[4];
        CODE486_SP_PUSH[3]  = CODE486_SP_PUSH[0];
        CODE486_SP_PUSH[4]  = CODE486_SP_PUSH[1];
        CODE486_SP_PUSH[5]  = CODE486_SP_PUSH[2];
        CODE486_SP_PUSH[9]  = CODE486_SP_PUSH[6];
        CODE486_SP_PUSH[10] = CODE486_SP_PUSH[7];
        CODE486_SP_PUSH[11] = CODE486_SP_PUSH[8];
        CODE486_SP_PUSH[0]  = 0;
        CODE486_SP_PUSH[1]  = 0;
        CODE486_SP_PUSH[2]  = 0;
        CODE486_SP_PUSH[6]  = 0;
        CODE486_SP_PUSH[7]  = 0;
        CODE486_SP_PUSH[8]  = 0;
        if (tries++ < 8)
        {
            goto retry;
        }
        return 0x80000000;
    }
    dx = start.x - CODE486_SP_POS_C0->x;
    dz = start.z - CODE486_SP_POS_C0->z;
    dy = start.y - CODE486_SP_POS_C0->y;
    if (dx == 0 && dz == 0 && dy == 0)
    {
        result = 0;
    }
    else
    {
        if (CODE486_ABS_NEG(dx) > CODE486_ABS_NEG(dz))
        {
            if (CODE486_ABS_NEG(dx) > CODE486_ABS_NEG(dy))
            {
                result = (dx > 0) ? 1 : 2;
            }
            else
            {
                result = (dy > 0) ? 5 : 6;
            }
        }
        else if (CODE486_ABS_NEG(dz) > CODE486_ABS_NEG(dy))
        {
            result = (dz > 0) ? 3 : 4;
        }
        else
        {
            result = (dy > 0) ? 5 : 6;
        }
        if (dx != 0)
        {
            cur->x = (CODE486_SP_POS_C0->x + ((dx > 0) ? -2 : 2)) << 16;
            result |= (dx > 0) ? 0x100 : 0x200;
        }
        if (dz != 0)
        {
            cur->z = (CODE486_SP_POS_C0->z + ((dz > 0) ? -2 : 2)) << 16;
            result |= (dz > 0) ? 0x400 : 0x800;
        }
        if (dy != 0)
        {
            cur->y = (CODE486_SP_POS_C0->y + ((dy > 0) ? -2 : 2)) << 16;
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

void func_80053158(PL_WORK *pl, uint32 arg)
{
    CODE486_MTX mtx;
    PL_FIXED_VECTOR pos;
    PL_FIXED_VECTOR org;
    PL_FIXED_VECTOR piv;
    CODE486_SVECTOR rot;
    CODE486_SVECTOR rot_inv;

    if (CODE486_PLAT_AT(arg).value01 < 0x80)
    {
        pos = pl->position_fixed;
        org = CODE486_PLAT_AT(arg).origin;
        piv = CODE486_PLAT_AT(arg).pivot;
        if (CODE486_PLAT_AT(arg).rot.word & 0x0FFF0FFF)
        {
            rot_inv.vx = -CODE486_PLAT_AT(arg).rot_inv.x;
            rot_inv.vy = -CODE486_PLAT_AT(arg).rot_inv.y;
            rot_inv.vz = -CODE486_PLAT_AT(arg).rot_inv.z;
            RotMatrix(&rot_inv, &mtx);
            func_800301A8(&mtx, &pos, &piv);
            rot.vx = CODE486_PLAT_AT(arg).rot.vec.x;
            rot.vy = CODE486_PLAT_AT(arg).rot.vec.y;
            rot.vz = CODE486_PLAT_AT(arg).rot.vec.z;
            RotMatrixYXZ(&rot, &mtx);
            func_800301A8(&mtx, &pos, &piv);
        }
        pl->position_fixed.x = pos.x + org.x - piv.x;
        pl->position_fixed.y = pos.y + org.y - piv.y;
        pl->position_fixed.z = pos.z + org.z - piv.z;
        func_80030150(&pl->position_fixed, &pl->position);
        pl->rotation.y += CODE486_PLAT_AT(arg).rot.vec.y - CODE486_PLAT_AT(arg).rot_inv.y;
    }
}

void func_8005331C(PL_WORK *pl, uint32 arg)
{
    CODE486_MTX mtx;
    PL_FIXED_VECTOR pos;
    PL_FIXED_VECTOR org;
    PL_FIXED_VECTOR piv;
    CODE486_SVECTOR rot;
    CODE486_SVECTOR rot_inv;

    if (CODE486_PLAT_AT(arg).value01 < 0x80)
    {
        pos = pl->position_saved_fixed;
        org = CODE486_PLAT_AT(arg).origin;
        piv = CODE486_PLAT_AT(arg).pivot;
        if (CODE486_PLAT_AT(arg).rot.word & 0x0FFF0FFF)
        {
            rot_inv.vx = -CODE486_PLAT_AT(arg).rot_inv.x;
            rot_inv.vy = -CODE486_PLAT_AT(arg).rot_inv.y;
            rot_inv.vz = -CODE486_PLAT_AT(arg).rot_inv.z;
            RotMatrix(&rot_inv, &mtx);
            func_800301A8(&mtx, &pos, &piv);
            rot.vx = CODE486_PLAT_AT(arg).rot.vec.x;
            rot.vy = CODE486_PLAT_AT(arg).rot.vec.y;
            rot.vz = CODE486_PLAT_AT(arg).rot.vec.z;
            RotMatrixYXZ(&rot, &mtx);
            func_800301A8(&mtx, &pos, &piv);
        }
        pl->position_saved_fixed.x = pos.x + org.x - piv.x;
        pl->position_saved_fixed.y = pos.y + org.y - piv.y;
        pl->position_saved_fixed.z = pos.z + org.z - piv.z;
        func_80030150(&pl->position_saved_fixed, &pl->position_saved);
        pl->rotation_saved.y += CODE486_PLAT_AT(arg).rot.vec.y - CODE486_PLAT_AT(arg).rot_inv.y;
    }
}

void func_800534E0(sint32 a0, PL_WORK *pl, PL_FIXED_VECTOR *a2, PL_FIXED_VECTOR *a3,
                   PL_FIXED_VECTOR *a4, PL_FIXED_VECTOR *a5)
{
    CODE486_MTX mtx;
    PL_FIXED_VECTOR pos;
    CODE486_SVECTOR rot;
    CODE486_SVECTOR rot_inv;

    a5->x += a2->x - a3->x;
    a5->y += a2->y - a3->y;
    a5->z += a2->z - a3->z;
    if (CODE486_PLAT_AT(a0).rot.word & 0x0FFF0FFF)
    {
        rot_inv.vx = -CODE486_PLAT_AT(a0).rot_inv.x & 0xFFF;
        rot_inv.vy = -CODE486_PLAT_AT(a0).rot_inv.y & 0xFFF;
        rot_inv.vz = -CODE486_PLAT_AT(a0).rot_inv.z & 0xFFF;
        rot.vx     = CODE486_PLAT_AT(a0).rot.vec.x & 0xFFF;
        rot.vy     = CODE486_PLAT_AT(a0).rot.vec.y & 0xFFF;
        rot.vz     = CODE486_PLAT_AT(a0).rot.vec.z & 0xFFF;
        if (rot_inv.vx != -rot.vx || rot_inv.vy != -rot.vy || rot_inv.vz != -rot.vz)
        {
            pos = *a4;
            RotMatrix(&rot_inv, &mtx);
            func_800301A8(&mtx, &pos, a2);
            RotMatrixYXZ(&rot, &mtx);
            func_800301A8(&mtx, &pos, a2);
            a5->x += pos.x - a4->x;
            a5->y += pos.y - a4->y;
            a5->z += pos.z - a4->z;
        }
    }
}

void func_800536B0(PL_WORK *pl, PL_FIXED_VECTOR *pos, PL_FIXED_VECTOR *prev, sint32 index)
{
    if (index < 0)
    {
        *pos  = pl->position_fixed;
        *prev = pl->position_fixed_prev;
    }
    else
    {
        pos->x  = pl->table180[index].x << 16;
        pos->y  = pl->table180[index].y << 16;
        pos->z  = pl->table180[index].z << 16;
        prev->x = pl->position_fixed_prev.x + (pos->x - pl->position_fixed.x);
        prev->y = pl->position_fixed_prev.y + (pos->y - pl->position_fixed.y);
        prev->z = pl->position_fixed_prev.z + (pos->z - pl->position_fixed.z);
    }
}
