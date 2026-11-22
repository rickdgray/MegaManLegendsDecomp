#include "common.h"
#include "cd.h"
#include "code_8003AC24.h"
#include "fastmem.h"
#include "game.h"
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003AD14);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003B140);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003B5B4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003B8B0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003BA58);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8003AC24", func_8003BC44);

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
