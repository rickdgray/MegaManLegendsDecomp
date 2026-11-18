#include "common.h"
#include "rock_neo.exe/code_8003ac24.h"

uint32 func_8003AC24(uint32 key)
{
    uint32 i;
    uint32 *p;

    if (D_8013A004 != 0)
    {
        i = 0;
        p = (uint32 *)0x8013A000;
    next:
        if (i < 0x4000)
        {
            if (*p == key)
            {
                return *(uint32 *)(0x8013A004 + i);
            }
            i += 8;
            p += 2;
            if (*(uint32 *)(0x8013A004 + i) != 0)
            {
                goto next;
            }
        }
    }
    return 0;
}

uint32 func_8003AC9C(sint32 idx, uint32 key)
{
    uint32 old;
    sint32 off;

    off                           = idx * 12;
    old                           = *(uint32 *)(0x8015C008 + off);
    *(uint32 *)(0x8015C008 + off) = func_8003AC24(key);
    return old;
}

void func_8003ACF4(sint32 idx, uint32 val)
{
    C8003AC24_SLOTS[idx].v = val;
}

// FAKE MATCH: one dead conditional store (`map = NULL`), kept only for register allocation.
// The dead store in the key loop is needed: its test survives until jump2 and adds
// weighted references to k, which ranks k above j and i (retail's s3/s4/s5).
void func_8003AD14(void)
{
    uint32 keys[2][2][4];
    sint32 row;
    sint32 game_row;
    sint32 i;
    sint32 j;
    sint32 k;
    uint32 *map;
    uint32 bits;
    sint8 special;

    if (C8003AC24_GAME_FLAG64 != 0)
    {
        func_8003B5B4();
    }
    game_row = C8003AC24_GAME_ROW;
    row      = D_80089F04[game_row];
    if (row < 0)
    {
        return;
    }
    D_8015C008[0].v = 1;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            for (k = 0; k < 4; k++)
            {
                if (k != 0)
                {
                    map = NULL; // dead: map is set before use
                }
                keys[i][j][k] = func_8003AC24(D_80089F24[i][j][k]);
            }
        }
    }
    if (C8003AC24_GAME_ROW == 6)
    {
        if ((uint32)(func_8003B2D4(6, 0x1C7) - 1) < 2)
        {
            D_8015D554 = -0x1200;
            D_8015D556 = -0x300;
            D_8015D558 = 0xA00;
        }
        else
        {
            D_8015D554 = -0x11F0;
            D_8015D556 = -0x300;
            D_8015D558 = 0xA10;
        }
        if ((uint32)(func_8003B2D4(6, 0x1F8) - 1) < 2)
        {
            D_8015D7A0 = 0x2000;
            D_8015D7A2 = -0x300;
            D_8015D7A4 = 0xE00;
        }
        else
        {
            D_8015D7A0 = 0x2010;
            D_8015D7A2 = -0x300;
            D_8015D7A4 = 0xE10;
        }
    }
    map     = D_800BD3B8[row];
    special = (uint32)(game_row - 5) < 2;
    for (k = 0; k < 0x800; k += 16)
    {
        bits = map[k >> 4];
        for (j = 0; j < 16; j++)
        {
            if (C8003AC24_ENTRIES[k + j].v08 == 0)
            {
                return;
            }
            if (k + j == 0)
            {
                continue;
            }
            switch ((bits >> (j * 2)) & 3)
            {
                case 0:
                    C8003AC24_PREV_SLOTS[k + j].h = 0;
                    break;
                case 1:
                    C8003AC24_PREV_SLOTS[k + j].h = 100;
                    if (special &&
                        (*(uint32 *)C8003AC24_ENTRIES[k + j].v08 & 0xFFFF0000) == 0x81000000)
                    {
                        C8003AC24_ENTRIES[k + j].v08 =
                            keys[0][0]
                                [(*(uint32 *)(*(uint32 *)(C8003AC24_ENTRIES[k + j].v08 + 0x18) &
                                              0xFFFFFF) >>
                                  14) &
                                 3];
                    }
                    else
                    {
                        C8003AC24_ENTRIES[k + j].v08 =
                            keys[1][0]
                                [(*(uint32 *)(*(uint32 *)(C8003AC24_ENTRIES[k + j].v08 + 0x18) &
                                              0xFFFFFF) >>
                                  14) &
                                 3];
                    }
                    break;
                case 2:
                    C8003AC24_PREV_SLOTS[k + j].h = 200;
                    if (special &&
                        (*(uint32 *)C8003AC24_ENTRIES[k + j].v08 & 0xFFFF0000) == 0x81000000)
                    {
                        C8003AC24_ENTRIES[k + j].v08 =
                            keys[0][1]
                                [(*(uint32 *)(*(uint32 *)(C8003AC24_ENTRIES[k + j].v08 + 0x18) &
                                              0xFFFFFF) >>
                                  14) &
                                 3];
                    }
                    else
                    {
                        C8003AC24_ENTRIES[k + j].v08 =
                            keys[1][1]
                                [(*(uint32 *)(*(uint32 *)(C8003AC24_ENTRIES[k + j].v08 + 0x18) &
                                              0xFFFFFF) >>
                                  14) &
                                 3];
                    }
                    break;
            }
        }
    }
    D_8015C008[0].v = 0;
}

// The slot table is read as whole records from 0x8015C000 (C8003AC24_ENTRIES), which gives
// retail's lui at / addu at,reg,at loads without hoisting.
void func_8003B140(void)
{
    sint32 row;
    uint32 *map;
    sint32 base;
    sint32 idx;
    sint32 j;
    sint32 shift;
    uint32 bits;
    uint32 entry;

    func_8003BC44();
    row = D_80089F04[C8003AC24_GAME_ROW];
    if (row >= 0)
    {
        D_8015C008[0].v = 1;
        map             = D_800BD3B8[row];
        for (base = 0; base < 0x800; base += 0x10)
        {
            bits = map[base >> 4];
            for (j = 0, shift = 0; j < 0x10; j++, shift += 2)
            {
                idx   = base + j;
                entry = C8003AC24_ENTRIES[idx].v08;
                if (entry == 0)
                {
                    return;
                }
                if (idx != 0)
                {
                    if (!(*(uint32 *)(*(uint32 *)(entry + 0x18) & 0xFFFFFF) & 0xF0000000))
                    {
                        bits |= 3 << shift;
                    }
                    else if (!(C8003AC24_ENTRIES[idx].h06 & 0xFFF))
                    {
                        bits &= ~(3 << shift);
                    }
                }
            }
            map[base >> 4] = bits;
        }
        D_8015C008[0].v = 0;
    }
}

void func_8003B278(sint32 mode)
{
    sint32 i;

    if (mode == 0)
    {
        for (i = 0; i < 0x380; i++)
        {
            D_800BD3B8[0][i] = -1; // all seven rows
        }
    }
    else
    {
        func_800176DC(D_800B6230, D_800BD3B8, 0x70);
    }
}

sint32 func_8003B2D4(sint32 idx, sint32 bit)
{
    sint32 row;
    uint32 bits;

    if (bit < 0)
    {
        return -1;
    }
    row = D_80089F04[idx];
    if (row < 0)
    {
        return -1;
    }
    bits = D_800BD3B8[row][bit >> 4];
    switch ((bits >> ((bit & 0xF) * 2)) & 3)
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

sint32 func_8003B360(sint32 bit)
{
    sint32 row;
    uint32 bits;

    if (bit < 0)
    {
        return -1;
    }
    row = D_80089F04[C8003AC24_GAME_ROW];
    if (row < 0)
    {
        return -1;
    }
    if ((*(uint16 *)(0x8015C006 + bit * 12) & 0xFFF) != 0)
    {
        bits = D_800BD3B8[row][bit >> 4];
        switch ((bits >> ((bit & 0xF) * 2)) & 3)
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

sint32 func_8003B420(sint32 bit)
{
    sint32 row;
    uint32 bits;

    if (bit < 0)
    {
        return -1;
    }
    row = D_80089F04[C8003AC24_GAME_ROW];
    if (row < 0)
    {
        return -1;
    }
    bits = D_800BD3B8[row][bit >> 4];
    switch ((bits >> ((bit & 0xF) * 2)) & 3)
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

sint32 func_8003B4BC(sint32 idx, sint32 bit)
{
    sint32 row;
    uint32 *wp;
    uint32 v;

    if (bit < 0)
    {
        return -1;
    }
    row = D_80089F04[idx];
    if (row < 0)
    {
        return -1;
    }
    wp = D_800BD3B8[row];
    v  = (wp[bit >> 4] >> ((bit & 0xF) * 2)) & 3;
    if (v == 3)
    {
        return 0;
    }
    v++;
    wp[bit >> 4] = (wp[bit >> 4] & ~(3 << ((bit & 0xF) * 2))) | (v << ((bit & 0xF) * 2));
    return 1;
}

sint32 func_8003B540(sint32 idx, sint32 bit, uint32 val)
{
    uint32 *wp;
    sint32 row;

    if (bit < 0)
    {
        return -1;
    }
    row = D_80089F04[idx];
    if (row < 0)
    {
        return -1;
    }
    wp           = D_800BD3B8[row];
    wp[bit >> 4] = (wp[bit >> 4] & ~(3 << ((bit & 0xF) * 2))) | (val << ((bit & 0xF) * 2));
    return 1;
}

void func_8003B5B4(void)
{
    uint32 i;
    uint32 state;
    uint32 key;
    uint32 left;
    uint32 *slot;

    if ((uint8)(Game_work[0x50] - 5) < 2)
    {
        if ((sint8)Game_work[0x50] == 5 && Game_work[0x64] != 0)
        {
            Game_work[0x64] = 0;
            func_8003B8B0((uint32 *)(Game_work + 0x34), 0xC8, D_80089F64, 5, 0x240);
            i    = 1;
            key  = D_80089F68;
            left = C8003AC24_GAME32(0x38) / 150;
            for (; i < 0x800; i++)
            {
                slot = (uint32 *)C8003AC24_SLOTS[i].v;
                if (slot == 0)
                {
                    break;
                }
                if ((*slot & 0xFFFF0000) == key)
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
                                Game_work[0x66]--;
                                C8003AC24_GAME32(0x38) -= 0x96;
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
        if ((sint8)Game_work[0x50] == 6 && Game_work[0x65] != 0)
        {
            Game_work[0x65] = 0;
            func_8003BA58((uint32 *)(Game_work + 0x28), 0x1F4, D_80089F6C, 6);
            func_8003B8B0((uint32 *)(Game_work + 0x2C), 0xC8, D_80089F70, 6, 0x23E);
            func_8003B8B0((uint32 *)(Game_work + 0x30), 0xFA, D_80089F74, 6, 0x23F);
            i    = 1;
            key  = D_80089F78;
            left = C8003AC24_GAME32(0x3C) / 180;
            for (; i < 0x800; i++)
            {
                slot = (uint32 *)C8003AC24_SLOTS[i].v;
                if (slot == 0)
                {
                    break;
                }
                if ((*slot & 0xFFFF0000) == key)
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
                                Game_work[0x67]--;
                                C8003AC24_GAME32(0x3C) -= 0xB4;
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

void func_8003B8B0(uint32 *remain, uint32 amount, uint32 key, sint32 row, sint32 flag)
{
    uint32 state;
    uint32 left;
    uint32 first;
    uint32 i;
    uint32 *slot;

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
        slot = (uint32 *)C8003AC24_SLOTS[i].v;
        if (slot == 0)
        {
            return;
        }
        if ((*slot & 0xFFFF0000) == key)
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
            func_8003B540(row, i, state);
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

void func_8003BA58(uint32 *remain, uint32 amount, uint32 key, sint32 unused)
{
    uint32 state;
    uint32 left;
    uint32 first;
    uint32 *slot;
    sint32 tmp[8];
    uint32 i;
    C8003AC24_SLOT *entry;

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
    entry = &C8003AC24_SLOTS[1];
    // i is set before first: initialising it in the for clause schedules differently
    for (; i < 0x800; i++, entry++)
    {
        slot = (uint32 *)entry->v;
        if (slot == 0)
        {
            break;
        }
        if ((*slot & 0xFFFF0000) == key)
        {
            tmp[(*slot >> 8) & 0xFF] = i;
            if (*(uint32 *)entry->v == 0x40400 && first != 0)
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
        func_8003B540(6, tmp[i], D_80097D74[state][i]);
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
    uint8 *rp;

    rp = Game_work + 0x50;
    if (*rp == 5 || *rp == 6)
    {
        if ((sint8)*rp == 5)
        {
            func_8003BD0C((uint32 *)(rp - 0x1C), D_80089F7C);
            func_8003BDC0(rp + 0x16, D_80089F80, 0x8FFF0000);
        }
        if ((sint8)*rp == 6)
        {
            func_8003BD0C((uint32 *)(rp - 0x28), D_80089F84);
            func_8003BD0C((uint32 *)(rp - 0x24), D_80089F88);
            func_8003BD0C((uint32 *)(rp - 0x20), D_80089F8C);
            func_8003BDC0(rp + 0x17, D_80089F90, 0x8FFF0000);
        }
    }
}

void func_8003BD0C(uint32 *out, uint32 key)
{
    uint32 i;
    uint8 *p;
    uint32 *ptr;
    uint32 mask;

    i    = 1;
    mask = 0xFFFF0000;
    p    = (uint8 *)0x8015C012;
    for (; i < 0x800; i++)
    {
        ptr = *(uint32 **)(p + 2);
        if (ptr == 0)
        {
            break;
        }
        if ((*ptr & mask) == key && *(sint16 *)p == 0)
        {
            if (func_8003B420(i) > 0)
            {
                *out = 0;
                break;
            }
        }
        p += 12;
    }
}

void func_8003BDC0(uint8 *count, uint32 a1, uint32 a2)
{
    uint32 i;
    uint8 *p;
    uint32 *ptr;
    uint32 key;
    uint32 mask;

    *count = 0;
    i      = 1;
    mask   = 0xFFFF0000;
    p      = (uint8 *)0x8015C012;
    for (; i < 0x800; i++)
    {
        ptr = *(uint32 **)(p + 2);
        if (ptr == 0)
        {
            break;
        }
        key = *ptr & mask;
        if ((key == a1 || key == a2) && *(sint16 *)p == 0)
        {
            (*count)++;
        }
        p += 12;
    }
}

void func_8003BE38(void)
{
}
