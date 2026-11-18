#include "common.h"
#include "code_80037440.h"
#include "game.h"

// Small data reached through $gp
uint16 D_80097D24;
static uint8 D_8009856C[16];

sint32 func_80037440(void)
{
    sint32 i;
    sint32 part;
    sint32 level;
    sint32 kind;

    part                      = Player_work.value170;
    ((sint32 *)D_8009856C)[0] = 0;
    ((sint32 *)D_8009856C)[1] = 0;
    ((sint32 *)D_8009856C)[2] = 0;
    ((sint32 *)D_8009856C)[3] = 0;
    for (i = 0; i < 16; i++)
    {
        if (D_800BFB20[i].flags & 1)
        {
            kind = D_800BFB20[i].kind - 0x80;
            if (kind < 16)
            {
                D_8009856C[kind]++;
            }
        }
    }
    if (part == 6)
    {
        level = Player_work.parts[6].value04;
    }
    else
    {
        level = Player_work.parts[part].value03;
    }
    if (level >= 4)
    {
        level = 3;
    }
    return D_800899E0[level][part] > D_8009856C[part];
}

void func_80037534(PL_WORK *wp)
{
    sint32 i;
    PL_PART_STATE *part;
    CODE374_VALUES *values;

    part = wp->parts;
    i    = 0;
    for (; i < 16; i++, part++)
    {
        part->current  = 0;
        part->selected = 0;
        part->value02  = 0;
        part->value03  = 0;
        part->value04  = 0;
        values         = D_80089EAC[i];
        part->value06  = values[part->selected].value1;
    }
}

void func_80037594(void)
{
    PL_WORK *wp;

    wp = &Player_work;
    wp->parts[wp->part_index].value06 =
        D_80089EAC[wp->part_index][wp->parts[wp->part_index].selected].value1;
}

sint32 func_800375D4(PL_WORK *wp, sint32 index)
{
    return D_80089EAC[index][wp->parts[index].current].value0;
}

sint32 func_80037604(PL_WORK *wp, sint32 index)
{
    return D_80089EAC[index][wp->parts[index].selected].value1;
}

sint32 func_80037634(PL_WORK *wp, sint32 index)
{
    return D_80089EAC[index][wp->parts[index].value02].value2;
}

sint32 func_80037664(PL_WORK *wp, sint32 index)
{
    return D_80089EAC[index][wp->parts[index].value03].value3;
}

sint32 func_80037694(PL_WORK *wp, sint32 amount)
{
    sint32 value;

    if (wp->value_c4 & 0xFF000000)
    {
        return 0x7FFF;
    }
    value = func_80049C24(wp);
    if (value != 0)
    {
        if (value > 0 && (value & 0xFFFF) <= 0x7FFF && (value & CODE374_GROUP_MASK))
        {
            func_8003777C(value & 0xFFFF, amount);
        }
        func_8004B414(wp);
        return value;
    }
    return 0;
}

void func_80037738(sint32 value, uint32 amount)
{
    if (value > 0 && (value & 0xFFFF) <= 0x7FFF && (value & CODE374_GROUP_MASK))
    {
        func_8003777C((uint16)value, amount);
    }
}

void func_8003777C(uint16 index, uint32 amount)
{
    CODE374_STATUS *status;
    uint32 flags;
    sint32 remaining;

    status    = &CODE374_STATUS_PTR[index];
    flags     = status->flags;
    remaining = (flags & CODE374_STATUS_MASK) - (amount >> (flags >> 12));
    if (remaining <= 0)
    {
        if (**(sint32 **)(0x8015C008 + index * 12) < 0)
        {
            func_80037818(index);
        }
        else
        {
            func_80037C50(index);
        }
    }
    else
    {
        status->flags = (flags & 0xF000) | remaining;
    }
}

void func_80037818(uint16 index)
{
    uint16 flags;
    CODE374_STATUS *status;

    status        = &CODE374_STATUS_PTR[index];
    flags         = status->flags;
    status->flags = 0;
    if ((flags >> 12) == 0)
    {
        func_80037890(0, 4, index);
    }
    else
    {
        func_80037890(4, 4, index);
    }
}

void func_8003786C(uint16 index)
{
    CODE374_STATUS_PTR[index].flags = 0;
}

void func_80037890(sint32 mode, sint32 count, uint16 index)
{
    CODE374_VALUES pos;
    CODE374_VALUES ofs;
    CODE374_OBJ *obj;
    CODE374_FX *fx;
    uint32 radius;
    uint32 height;
    uint32 r;
    sint32 a;
    uint32 i;
    uint32 n1;
    uint32 n2;
    sint32 step1;
    sint32 step2;

    obj    = (CODE374_OBJ *)CODE374_ENTRY_PTR[index].data;
    ofs    = obj->ofs;
    radius = obj->size;
    pos    = *(CODE374_VALUES *)&CODE374_ENTRY_PTR[index];
    height = radius & 0xFFFF;
    radius >>= 17;
    pos.value0 += ofs.value0;
    pos.value1 += ofs.value1 >> 1;
    pos.value2 += ofs.value2;
    Swing_Camera2(0x1E, 0x3E8, 0x1388, &pos);
    step1 = 0x1000 >> (mode - 1);
    n1    = 1 << (mode - 1);
    step2 = 0x1000 >> (count - 1);
    n2    = 1 << (count - 1);
    if (mode != 0)
    {
        for (i = 0; i < n1; i++)
        {
            fx = (CODE374_FX *)func_80031618();
            if (fx != NULL)
            {
                fx->kind_0  = 5;
                fx->value_2 = 0x80;
                fx->value_3 = 2;
                r           = rand();
                a           = i * step1 - (r & 0x1F);
                if (n1 == 1)
                {
                    radius = 0;
                }
                fx->x_38 = pos.value0 + ((rcos(a) * radius) >> 12);
                fx->y_3a =
                    pos.value1 - ((((r & 0xFF) + ((r >> 7) & 0xFF) - 0x100) * (height >> 1)) >> 8);
                fx->z_3c = pos.value2 + ((rsin(a) * radius) >> 12);
            }
        }
    }
    if (count != 0)
    {
        for (i = 0; i < n2; i++)
        {
            fx = (CODE374_FX *)func_80031618();
            if (fx != NULL)
            {
                fx->value_2 = 0x83;
                fx->kind_0  = 1;
                fx->value_3 = 2;
                r           = rand();
                a           = i * step2 - (r & 0x1F);
                if (n2 == 1)
                {
                    radius = 0;
                }
                fx->x_1c = pos.value0 + ((rcos(a) * radius) >> 12);
                fx->y_1e =
                    pos.value1 - ((((r & 0xFF) + ((r >> 7) & 0xFF) - 0x100) * (height >> 1)) >> 8);
                fx->z_20 = pos.value2 + ((rsin(a) * radius) >> 12);
            }
        }
    }
}

sint32 func_80037BB4(sint32 value)
{
    uint32 index;
    sint32 amount;

    index = value & 0xFFFF;
    if (value > 0 && index <= 0x7FFF)
    {
        amount = CODE374_STATUS_PTR[index].flags & CODE374_STATUS_MASK;
        if (amount == 0)
        {
            return 0;
        }
        if (value & CODE374_GROUP_MASK)
        {
            return amount;
        }
    }
    return -1;
}

sint32 func_80037C14(sint32 value)
{
    uint32 index;
    sint32 result;

    index = value & 0xFFFF;
    if (index <= 0x7FFF)
    {
        return CODE374_STATUS_PTR[index].flags & CODE374_STATUS_MASK;
    }
    return -1;
}

void func_80037C50(uint16 index)
{
    if (index < 0x800)
    {
        D_8009A378[D_80097D24] =
            (((CODE374_ENTRY_PTR[index].x + 0x8000) >> 9) - CODE374_MAP_X) +
            ((((CODE374_ENTRY_PTR[index].z + 0x8000) >> 9) - CODE374_MAP_Z) << 8);
        D_80097D24++;
    }
}

void func_80037CD8(uint16 cell)
{
    CODE374_VALUES unused; // never referenced; retail's frame reserves it
    uint32 x;
    uint32 z;
    uint32 nx;
    uint32 nz;
    uint32 i;
    uint16 id;
    sint16 n;

    x  = cell & 0xFF;
    z  = cell >> 8;
    id = *(CODE374_MAP + x + z * CODE374_MAP_W);
    if (CODE374_STATUS_PTR[id].flags & CODE374_STATUS_MASK)
    {
        for (i = 0; i < 8; i++)
        {
            nx = x + D_80089EEC[i];
            nz = z + D_80089EF4[i];
            if (nx < CODE374_MAP_W && nz < CODE374_MAP_H)
            {
                n = *(CODE374_MAP + nx + nz * CODE374_MAP_W);
                if ((uint32)(n - 1) < 0x7FF && n == id)
                {
                    D_8009A378[D_80097D24] = nx + (nz << 8);
                    D_80097D24++;
                }
            }
        }
        func_80037818(id);
    }
    else
    {
        D_80097D24--;
        for (i = 0; i < 4; i++)
        {
            nx = x + D_80089EFC[i];
            nz = z + D_80089F00[i];
            if (nx < CODE374_MAP_W && nz < CODE374_MAP_H)
            {
                n = *(CODE374_MAP + nx + nz * CODE374_MAP_W);
                if ((uint32)(n - 1) < 0x7FF && n != id &&
                    ((uint16 *)CODE374_ENTRY_PTR[n].data)[1] ==
                        ((uint16 *)CODE374_ENTRY_PTR[id].data)[1] &&
                    (CODE374_STATUS_PTR[n].flags & CODE374_STATUS_MASK))
                {
                    D_8009A378[D_80097D24] = nx + (nz << 8);
                    D_80097D24++;
                }
            }
        }
    }
}

void func_80037F60(void)
{
    while (D_80097D24 != 0)
    {
        func_80037CD8(D_8009A378[D_80097D24 - 1]);
    }
}
