#include "common.h"
#include "psyq/libc.h"
#include "code_8002E7A8.h"
#include "player.h"
#include "code_80037FB4.h"
#include "stage.h"

// Called only from this file, ahead of their definitions.
void func_8003777C(uint16 arg0, uint32 arg1);
void func_80037818(uint16 arg0);
void func_80037890(sint32 arg0, sint32 arg1, uint16 arg2);
void func_80037C50(uint16 arg0);
void func_80037CD8(uint16 arg0);

// Small data (.sdata 0x80097D24-0x80097D28): reached through $gp in this file.
uint16 Cell_stack_idx = 0;
sint16 D_80097D26 = 0;

void func_80037534(PL_WORK *pl)
{
    TBL_IDX *p = pl->rec;
    sint32 i;

    for (i = 0; i < 16; i++, p++)
    {
        p->idx[0]   = 0;
        p->idx[1]   = 0;
        p->idx[2]   = 0;
        p->idx[3]   = 0;
        p->unk04[0] = 0;
        p->val      = D_80089EAC[i][p->idx[1]].val[1];
    }
}

#ifdef NON_MATCHING
void func_80037594(void)
{
    // best attempt: target loads tbl_sel via its own lui, then builds &Player_work with a
    // second lui/addiu and uses 0x4F5/0x4FA offsets from it; ours folds +0x172/+0x382 into one base
    sint32 sel   = Player_work[0].tbl_sel;
    TBL_IDX *rec = &Player_work[0].rec[sel];

    rec->val = D_80089EAC[sel][rec->idx[1]].val[1];
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037534", func_80037594);
#endif

sint16 func_800375D4(PL_WORK *pl, sint32 n)
{
    return D_80089EAC[n][pl->rec[n].idx[0]].val[0];
}

sint16 func_80037604(PL_WORK *pl, sint32 n)
{
    return D_80089EAC[n][pl->rec[n].idx[1]].val[1];
}

sint16 func_80037634(PL_WORK *pl, sint32 n)
{
    return D_80089EAC[n][pl->rec[n].idx[2]].val[2];
}

sint16 func_80037664(PL_WORK *pl, sint32 n)
{
    return D_80089EAC[n][pl->rec[n].idx[3]].val[3];
}

sint32 func_80037694(STAGE_OBJ *obj, uint32 arg1)
{
    sint32 id;

    if (obj->unkC4 & 0xFF000000)
    {
        return 0x7FFF;
    }
    id = func_80049C24(obj);
    if (id != 0)
    {
        if (id > 0 && (id & 0xFFFF) <= 0x7FFF && (id & 0xF0000))
        {
            func_8003777C(id, arg1);
        }
        func_8004B414(obj);
        return id;
    }
    return 0;
}

void func_80037738(sint32 arg0, uint32 arg1)
{
    if (arg0 > 0 && (arg0 & 0xFFFF) <= 0x7FFF && (arg0 & 0xF0000))
    {
        func_8003777C(arg0, arg1);
    }
}

void func_8003777C(uint16 arg0, uint32 arg1)
{
    uint16 *p   = &Stage_idx_tbl[arg0].val;
    uint16 val  = *p;
    sint32 left = (val & 0xFFF) - (arg1 >> (val >> 12));

    if (left <= 0)
    {
        if (Stage_idx_tbl[arg0].ptr->head < 0)
        {
            func_80037818(arg0);
        }
        else
        {
            func_80037C50(arg0);
        }
    }
    else
    {
        *p = (val & 0xF000) | left;
    }
}

#ifdef NON_MATCHING
void func_80037818(uint16 arg0)
{
    // best attempt: target keeps arg0 in a2 and does `li a0,4` in a delay slot, then `move a0,zero`
    uint16 *p   = &Stage_idx_tbl[arg0].val;
    uint16 old  = *p;
    sint32 kind = 4;

    *p = 0;
    if ((old >> 12) == 0)
    {
        kind = 0;
    }
    func_80037890(kind, 4, arg0);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037534", func_80037818);
#endif

void func_8003786C(uint16 arg0)
{
    Stage_idx_tbl[arg0].val = 0;
}

// Spawns two bursts of effects around entry `id`: 1 << (n0 - 1) of kind 5, then 1 << (n1 - 1) of kind 1.
void func_80037890(sint32 n0, sint32 n1, uint16 id)
{
    SVECTOR pos;
    SVECTOR ofs;
    IDX_SHAPE *shape;
    WORK_48 *e;
    uint32 width;
    uint32 spread;
    uint32 cnt0;
    uint32 cnt1;
    uint32 j;
    uint32 r;
    sint32 step0;
    sint32 step1;
    sint32 a;

    shape  = Stage_idx_tbl[id].ptr;
    ofs    = shape->ofs;
    spread = shape->size;
    pos    = *(SVECTOR *)&Stage_idx_tbl[id];
    width  = spread & 0xFFFF;
    spread = spread >> 17;
    pos.vx += ofs.vx;
    pos.vy += ofs.vy >> 1;
    pos.vz += ofs.vz;
    Swing_Camera2(30, 1000, 5000, &pos);

    step0 = 0x1000 >> (n0 - 1);
    cnt0  = 1 << (n0 - 1);
    step1 = 0x1000 >> (n1 - 1);
    cnt1  = 1 << (n1 - 1);

    if (n0 != 0)
    {
        for (j = 0; j < cnt0; j++)
        {
            e = func_80031618();
            if (e != 0)
            {
                e->routine_0 = 5;
                e->field_2   = 0x80;
                e->flag_3    = 2;
                r            = rand();
                a            = j * step0 - (r & 0x1F);
                if (cnt0 == 1)
                {
                    spread = 0;
                }
                e->pos_38.vx = pos.vx + ((rcos(a) * spread) >> 12);
                e->pos_38.vy = pos.vy - ((((r & 0xFF) + ((r >> 7) & 0xFF) - 0x100) * (width >> 1)) >> 8);
                e->pos_38.vz = pos.vz + ((rsin(a) * spread) >> 12);
            }
        }
    }

    if (n1 != 0)
    {
        for (j = 0; j < cnt1; j++)
        {
            e = func_80031618();
            if (e != 0)
            {
                e->field_2   = 0x83;
                e->routine_0 = 1;
                e->flag_3    = 2;
                r            = rand();
                a            = j * step1 - (r & 0x1F);
                if (cnt1 == 1)
                {
                    spread = 0;
                }
                e->pos_1C[0] = pos.vx + ((rcos(a) * spread) >> 12);
                e->pos_1C[1] = pos.vy - ((((r & 0xFF) + ((r >> 7) & 0xFF) - 0x100) * (width >> 1)) >> 8);
                e->pos_1C[2] = pos.vz + ((rsin(a) * spread) >> 12);
            }
        }
    }
}

sint32 func_80037BB4(sint32 arg0)
{
    sint32 v;

    if (arg0 > 0 && (uint16)arg0 <= 0x7FFF)
    {
        v = Stage_idx_tbl[(uint16)arg0].val & 0xFFF;
        if (v == 0)
        {
            return 0;
        }
        if (arg0 & 0xF0000)
        {
            return v;
        }
    }
    return -1;
}

sint32 func_80037C14(uint16 arg0)
{
    if (arg0 < 0x8000)
    {
        return Stage_idx_tbl[arg0].val & 0xFFF;
    }
    return -1;
}

void func_80037C50(uint16 arg0)
{
    if (arg0 < 0x800)
    {
        Cell_stack[Cell_stack_idx] =
            (((Stage_idx_tbl[arg0].x + 0x8000) >> 9) - Map_org_x) + ((((Stage_idx_tbl[arg0].y + 0x8000) >> 9) - Map_org_y) << 8);
        Cell_stack_idx++;
    }
}

void func_80037CD8(uint16 arg0)
{
    uint32 cx = arg0 & 0xFF;
    uint32 cy = arg0 >> 8;
    uint16 id = (Map_cells + cx)[cy * Map_w];
    uint8 unused[8]; // unused local; reserves the 8 bytes at 0x10(sp)
    sint16 c;
    uint32 x;
    uint32 y;
    uint32 i;

    if ((Stage_idx_tbl[id].val & 0xFFF) != 0)
    {
        for (i = 0; i < 8; i++)
        {
            x = cx + D_80089EEC[i];
            y = cy + D_80089EF4[i];
            if (x < Map_w && y < Map_h)
            {
                c = (Map_cells + x)[y * Map_w];
                if ((uint32)(c - 1) < 0x7FF && c == id)
                {
                    Cell_stack[Cell_stack_idx] = x + (y << 8);
                    Cell_stack_idx++;
                }
            }
        }
        func_80037818(id);
    }
    else
    {
        Cell_stack_idx--;
        for (i = 0; i < 4; i++)
        {
            x = cx + D_80089EFC[i];
            y = cy + D_80089F00[i];
            if (x < Map_w && y < Map_h)
            {
                c = (Map_cells + x)[y * Map_w];
                if ((uint32)(c - 1) < 0x7FF && c != id && ((uint16 *)Stage_idx_tbl[c].ptr)[1] == ((uint16 *)Stage_idx_tbl[id].ptr)[1] &&
                    (Stage_idx_tbl[c].val & 0xFFF) != 0)
                {
                    Cell_stack[Cell_stack_idx] = x + (y << 8);
                    Cell_stack_idx++;
                }
            }
        }
    }
}

void func_80037F60(void)
{
    while (Cell_stack_idx != 0)
    {
        func_80037CD8(D_8009A376[Cell_stack_idx]);
    }
}
