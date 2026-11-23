#include "common.h"
#include "cd.h"
#include "code_8003AC24.h"
#include "fastmem.h"
#include "game.h"
#include "scene.h"
#include "stage.h"

// The model word of the Stage_hed_tbl entry whose id is `id`, or 0.
uint32 Stage_hed_model_get(uint32 id)
{
    uint32 i;

    i = 0;
    while (Stage_hed_tbl[i].model != 0)
    {
        if (i >= 0x800)
        {
            break;
        }
        if (Stage_hed_tbl[i].id == id)
        {
            return Stage_hed_tbl[i].model;
        }
        i++;
    }
    return 0;
}

// Points Stage_idx_tbl[idx] at the model of the HED entry `id`; returns the old pointer.
IDX_SHAPE *Stage_idx_model_set(sint32 idx, uint32 id)
{
    IDX_SHAPE *old;

    old                    = Stage_idx_tbl[idx].ptr;
    Stage_idx_tbl[idx].ptr = (IDX_SHAPE *)Stage_hed_model_get(id);
    return old;
}

void func_8003ACF4(sint32 idx, IDX_SHAPE *ptr)
{
    Stage_idx_tbl[idx].ptr = ptr;
}

#ifdef NON_MATCHING
// Only the registers of i, j and k differ: the target gives k (the first loop's innermost counter,
// reused as the second loop's outer one) s3, j s4 and i s5; this gives j s3, i s4, k s5. The fork
// matched only with a dead `if (k != 0) wp = NULL;` in the innermost first loop.
// The val stores go through a zero-offset view at 0x8015C006: the target hoists that constant
// into a register (t0), which a plain Stage_idx_tbl[idx].val (offset 6) doesn't do.
void func_8003AD14(void)
{
    IDX_SHAPE *shapes[2][2][4];
    sint32 row;
    sint32 stage;
    sint32 i;
    sint32 j;
    sint32 k;
    sint32 idx;
    uint32 *wp;
    uint32 bits;
    sint8 special;

    if (*(uint16 *)&Game_work.unk062[2] != 0)
    {
        func_8003B5B4();
    }
    stage = Game_work.stage_no;
    row   = D_80089F04[stage];
    if (row < 0)
    {
        return;
    }
    Stage_idx_tbl[0].ptr = (IDX_SHAPE *)1;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            for (k = 0; k < 4; k++)
            {
                shapes[i][j][k] = (IDX_SHAPE *)Stage_hed_model_get(D_80089F24[i][j][k]);
            }
        }
    }
    if (Game_work.stage_no == 6)
    {
        if ((uint32)(func_8003B2D4(6, 0x1C7) - 1) < 2)
        {
            Stage_idx_tbl[0x1C7].x = -0x1200;
            Stage_idx_tbl[0x1C7].y = -0x300;
            Stage_idx_tbl[0x1C7].z = 0xA00;
        }
        else
        {
            Stage_idx_tbl[0x1C7].x = -0x11F0;
            Stage_idx_tbl[0x1C7].y = -0x300;
            Stage_idx_tbl[0x1C7].z = 0xA10;
        }
        if ((uint32)(func_8003B2D4(6, 0x1F8) - 1) < 2)
        {
            Stage_idx_tbl[0x1F8].x = 0x2000;
            Stage_idx_tbl[0x1F8].y = -0x300;
            Stage_idx_tbl[0x1F8].z = 0xE00;
        }
        else
        {
            Stage_idx_tbl[0x1F8].x = 0x2010;
            Stage_idx_tbl[0x1F8].y = -0x300;
            Stage_idx_tbl[0x1F8].z = 0xE10;
        }
    }
    wp      = D_800BD3B8[row];
    special = (uint32)(stage - 5) < 2;
    for (k = 0; k < 0x800; k += 16)
    {
        bits = wp[k >> 4];
        for (j = 0; j < 16; j++)
        {
            idx = k + j;
            if (Stage_idx_tbl[idx].ptr == NULL)
            {
                return;
            }
            if (idx == 0)
            {
                continue;
            }
            switch ((bits >> (j * 2)) & 3)
            {
                case 0:
                    ((IDX_ENT *)&Stage_idx_tbl[0].val)[idx].x = 0;
                    break;
                case 1:
                    ((IDX_ENT *)&Stage_idx_tbl[0].val)[idx].x = 100;
                    if (special && (Stage_idx_tbl[idx].ptr->head & 0xFFFF0000) == 0x81000000)
                    {
                        Stage_idx_tbl[idx].ptr = shapes[0][0][(*(uint32 *)((uint32)Stage_idx_tbl[idx].ptr->unk18 & 0xFFFFFF) >> 14) & 3];
                    }
                    else
                    {
                        Stage_idx_tbl[idx].ptr = shapes[1][0][(*(uint32 *)((uint32)Stage_idx_tbl[idx].ptr->unk18 & 0xFFFFFF) >> 14) & 3];
                    }
                    break;
                case 2:
                    ((IDX_ENT *)&Stage_idx_tbl[0].val)[idx].x = 200;
                    if (special && (Stage_idx_tbl[idx].ptr->head & 0xFFFF0000) == 0x81000000)
                    {
                        Stage_idx_tbl[idx].ptr = shapes[0][1][(*(uint32 *)((uint32)Stage_idx_tbl[idx].ptr->unk18 & 0xFFFFFF) >> 14) & 3];
                    }
                    else
                    {
                        Stage_idx_tbl[idx].ptr = shapes[1][1][(*(uint32 *)((uint32)Stage_idx_tbl[idx].ptr->unk18 & 0xFFFFFF) >> 14) & 3];
                    }
                    break;
            }
        }
    }
    Stage_idx_tbl[0].ptr = NULL;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003AD14);
#endif

void func_8003B140(void)
{
    sint32 row;
    uint32 *wp;
    sint32 base;
    sint32 idx;
    sint32 j;
    sint32 shift;
    uint32 bits;
    IDX_SHAPE *shape;

    func_8003BC44();
    row = D_80089F04[Game_work.stage_no];
    if (row >= 0)
    {
        // Entry 0's pointer is set to 1 while the states are rebuilt.
        Stage_idx_tbl[0].ptr = (IDX_SHAPE *)1;
        wp                   = D_800BD3B8[row];
        for (base = 0; base < 0x800; base += 0x10)
        {
            bits = wp[base >> 4];
            for (j = 0, shift = 0; j < 0x10; j++, shift += 2)
            {
                idx   = base + j;
                shape = Stage_idx_tbl[idx].ptr;
                if (shape == NULL)
                {
                    return;
                }
                if (idx != 0)
                {
                    if (!(*(uint32 *)((uint32)shape->unk18 & 0xFFFFFF) & 0xF0000000))
                    {
                        bits |= 3 << shift;
                    }
                    else if (!(Stage_idx_tbl[idx].val & 0xFFF))
                    {
                        bits &= ~(3 << shift);
                    }
                }
            }
            wp[base >> 4] = bits;
        }
        Stage_idx_tbl[0].ptr = NULL;
    }
}

void func_8003B278(sint32 mode)
{
    sint32 i;

    if (mode == 0)
    {
        for (i = 0; i < IDX_STATE_ROWS * IDX_STATE_WORDS; i++)
        {
            D_800BD3B8[0][i] = -1;
        }
    }
    else
    {
        Mem_copy32(&Cd_ring_buf[0][0x480], D_800BD3B8, sizeof(D_800BD3B8) / 32);
    }
}

sint32 func_8003B2D4(sint32 stage, sint32 idx)
{
    sint32 row;
    uint32 bits;

    if (idx < 0)
    {
        return -1;
    }
    row = D_80089F04[stage];
    if (row < 0)
    {
        return -1;
    }
    bits = D_800BD3B8[row][idx >> 4];
    switch ((bits >> ((idx & 0xF) * 2)) & 3)
    {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return -1;
    }
}

sint32 func_8003B360(sint32 idx)
{
    sint32 row;
    uint32 bits;

    if (idx < 0)
    {
        return -1;
    }
    row = D_80089F04[Game_work.stage_no];
    if (row < 0)
    {
        return -1;
    }
    if ((Stage_idx_tbl[idx].val & 0xFFF) != 0)
    {
        bits = D_800BD3B8[row][idx >> 4];
        switch ((bits >> ((idx & 0xF) * 2)) & 3)
        {
            case 0:
                break;
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            default:
                return -1;
        }
    }
    return 0;
}

sint32 func_8003B420(sint32 idx)
{
    sint32 row;
    uint32 bits;

    if (idx < 0)
    {
        return -1;
    }
    row = D_80089F04[Game_work.stage_no];
    if (row < 0)
    {
        return -1;
    }
    bits = D_800BD3B8[row][idx >> 4];
    switch ((bits >> ((idx & 0xF) * 2)) & 3)
    {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return -1;
    }
}

sint32 func_8003B4BC(sint32 stage, sint32 idx)
{
    sint32 row;
    uint32 *wp;
    uint32 v;

    if (idx < 0)
    {
        return -1;
    }
    row = D_80089F04[stage];
    if (row < 0)
    {
        return -1;
    }
    wp = D_800BD3B8[row];
    v  = (wp[idx >> 4] >> ((idx & 0xF) * 2)) & 3;
    if (v == 3)
    {
        return 0;
    }
    v++;
    wp[idx >> 4] = (wp[idx >> 4] & ~(3 << ((idx & 0xF) * 2))) | (v << ((idx & 0xF) * 2));
    return 1;
}

sint32 func_8003B540(sint32 stage, sint32 idx, uint32 state)
{
    uint32 *wp;
    sint32 row;

    if (idx < 0)
    {
        return -1;
    }
    row = D_80089F04[stage];
    if (row < 0)
    {
        return -1;
    }
    wp           = D_800BD3B8[row];
    wp[idx >> 4] = (wp[idx >> 4] & ~(3 << ((idx & 0xF) * 2))) | (state << ((idx & 0xF) * 2));
    return 1;
}

void func_8003B5B4(void)
{
    uint32 i;
    uint32 state;
    uint32 kind;
    uint32 left;
    IDX_SHAPE *shape;

    if (Game_work.stage_no == 5 || Game_work.stage_no == 6)
    {
        if (Game_work.stage_no == 5 && Game_work.unk062[2] != 0)
        {
            Game_work.unk062[2] = 0;
            func_8003B8B0(&Game_work.unk028[3], 200, D_80089F64, 5, 0x240);
            kind = D_80089F68;
            left = Game_work.unk028[4] / 150;
            for (i = 1; i < 0x800; i++)
            {
                shape = Stage_idx_tbl[i].ptr;
                if (shape == NULL)
                {
                    break;
                }
                if ((shape->head & 0xFFFF0000) == kind)
                {
                    state = 0;
                    switch (func_8003B360(i))
                    {
                        case 0:
                        default:
                            if (left != 0)
                            {
                                left--;
                                state = 1;
                                Game_work.unk062[4]--;
                                Game_work.unk028[4] -= 150;
                            }
                            break;
                        case 1:
                            state = 2;
                            break;
                        case 2:
                        case 3:
                            state = 3;
                            break;
                    }
                    func_8003B540(5, i, state);
                }
            }
        }
        if (Game_work.stage_no == 6 && Game_work.unk062[3] != 0)
        {
            Game_work.unk062[3] = 0;
            func_8003BA58(&Game_work.unk028[0], 500, D_80089F6C, 6);
            func_8003B8B0(&Game_work.unk028[1], 200, D_80089F70, 6, 0x23E);
            func_8003B8B0(&Game_work.unk028[2], 250, D_80089F74, 6, 0x23F);
            kind = D_80089F78;
            left = Game_work.unk028[5] / 180;
            for (i = 1; i < 0x800; i++)
            {
                shape = Stage_idx_tbl[i].ptr;
                if (shape == NULL)
                {
                    break;
                }
                if ((shape->head & 0xFFFF0000) == kind)
                {
                    state = 0;
                    switch (func_8003B360(i))
                    {
                        case 0:
                        default:
                            if (left != 0)
                            {
                                left--;
                                state = 1;
                                Game_work.unk062[5]--;
                                Game_work.unk028[5] -= 180;
                            }
                            break;
                        case 1:
                            state = 2;
                            break;
                        case 2:
                        case 3:
                            state = 3;
                            break;
                    }
                    func_8003B540(6, i, state);
                }
            }
        }
    }
}

void func_8003B8B0(uint32 *remain, uint32 amount, uint32 kind, sint32 stage, sint32 flag)
{
    uint32 state;
    uint32 left;
    uint32 first;
    uint32 i;
    IDX_SHAPE *shape;

    left = *remain;
    if (left == 0)
    {
        state = 0;
    }
    else if ((amount >> 1) >= left)
    {
        state = 1;
    }
    else
    {
        state = 3;
        if (left < amount)
        {
            state = 2;
        }
    }
    i     = 1;
    first = 1;
    for (; i < 0x800; i++)
    {
        shape = Stage_idx_tbl[i].ptr;
        if (shape == NULL)
        {
            return;
        }
        if ((shape->head & 0xFFFF0000) == kind)
        {
            if (first != 0)
            {
                first = 0;
                switch (func_8003B360(i))
                {
                    case 0:
                    default:
                        if (state != 0)
                        {
                            state = 1;
                        }
                        break;
                    case 1:
                        if (state >= 2)
                        {
                            state = 2;
                        }
                        break;
                    case 2:
                        if (state >= 3)
                        {
                            state = 3;
                            *remain -= amount;
                            Sce_flag_on(flag + 6);
                        }
                        break;
                    case 3:
                        return;
                }
            }
            func_8003B540(stage, i, state);
        }
    }
    if (state < 3)
    {
        Sce_flag_on(flag);
    }
    else
    {
        Sce_flag_off(flag);
    }
}

void func_8003BA58(uint32 *remain, uint32 amount, uint32 kind, sint32 unused)
{
    uint32 state;
    uint32 left;
    uint32 first;
    IDX_SHAPE *shape;
    sint32 idx[8];
    uint32 i;
    IDX_ENT *ent;

    left = *remain;
    if (left == 0)
    {
        state = 0;
    }
    else if ((amount >> 1) >= left)
    {
        state = 1;
    }
    else
    {
        state = 3;
        if (left < amount)
        {
            state = 2;
        }
    }
    i     = 1;
    first = 1;
    ent   = &Stage_idx_tbl[1];
    // i is set before first: initialising it in the for clause schedules differently.
    for (; i < 0x800; i++, ent++)
    {
        shape = ent->ptr;
        if (shape == NULL)
        {
            break;
        }
        if ((shape->head & 0xFFFF0000) == kind)
        {
            // Byte 1 of head numbers the entry within its kind; the target shifts it unsigned.
            idx[((uint32)shape->head >> 8) & 0xFF] = i;
            if (ent->ptr->head == 0x40400 && first != 0)
            {
                first = 0;
                switch (func_8003B360(i))
                {
                    case 0:
                    default:
                        if (state != 0)
                        {
                            state = 1;
                        }
                        break;
                    case 1:
                        if (state >= 2)
                        {
                            state = 2;
                        }
                        break;
                    case 2:
                        if (state >= 3)
                        {
                            state = 3;
                            *remain -= amount;
                            Sce_flag_on(0x243);
                        }
                        break;
                    case 3:
                        return;
                }
            }
        }
    }
    for (i = 0; i < 7; i++)
    {
        func_8003B540(6, idx[i], D_80097D74[state][i]);
    }
    if (state < 3)
    {
        Sce_flag_on(0x23D);
    }
    else
    {
        Sce_flag_off(0x23D);
    }
}

void func_8003BC44(void)
{
    if (Game_work.stage_no == 5 || Game_work.stage_no == 6)
    {
        if (Game_work.stage_no == 5)
        {
            func_8003BD0C(&Game_work.unk028[3], D_80089F7C);
            func_8003BDC0(&Game_work.unk062[4], D_80089F80, 0x8FFF0000);
        }
        if (Game_work.stage_no == 6)
        {
            func_8003BD0C(&Game_work.unk028[0], D_80089F84);
            func_8003BD0C(&Game_work.unk028[1], D_80089F88);
            func_8003BD0C(&Game_work.unk028[2], D_80089F8C);
            func_8003BDC0(&Game_work.unk062[5], D_80089F90, 0x8FFF0000);
        }
    }
}

// Clears *flag if a Stage_idx_tbl entry after the first, whose shape's kind (high half of head)
// is `kind` and whose val is 0, has a state above 0 (func_8003B420).
void func_8003BD0C(uint32 *flag, uint32 kind)
{
    uint32 i;

    for (i = 1; i < 0x800; i++)
    {
        if (Stage_idx_tbl[i].ptr == NULL)
        {
            break;
        }
        if ((Stage_idx_tbl[i].ptr->head & 0xFFFF0000) == kind && (sint16)Stage_idx_tbl[i].val == 0)
        {
            if (func_8003B420(i) > 0)
            {
                *flag = 0;
                break;
            }
        }
    }
}

// Counts into *count the Stage_idx_tbl entries after the first whose shape's kind (high half of
// head) is kind0 or kind1 and whose val is 0.
void func_8003BDC0(uint8 *count, uint32 kind0, uint32 kind1)
{
    uint32 i;
    uint32 kind;

    *count = 0;
    // The target reads val signed here (lh): hence the cast.
    for (i = 1; i < 0x800; i++)
    {
        if (Stage_idx_tbl[i].ptr == NULL)
        {
            break;
        }
        kind = Stage_idx_tbl[i].ptr->head & 0xFFFF0000;
        if ((kind == kind0 || kind == kind1) && (sint16)Stage_idx_tbl[i].val == 0)
        {
            (*count)++;
        }
    }
}

void func_8003BE38(void)
{
}
