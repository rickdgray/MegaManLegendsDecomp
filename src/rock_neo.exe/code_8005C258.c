#include "common.h"
#include "player.h"
#include "code_8005c258.h"
#include "code_800133d8.h"
#include "code_80037440.h"

// Small data reached through $gp
sint32 D_80098004;
sint32 D_80098008;
sint32 D_8009800C;
sint32 D_80098010;
sint32 D_80098014;
sint32 D_80098018;
sint32 D_8009801C;
sint32 D_80098034;
sint16 D_800986F8;
sint16 D_800986FC;
sint32 D_8009878C;
sint32 D_80098794;
sint32 D_8009882C;
sint32 D_80098AF0;
sint32 D_80098B18;

void func_8005C258(void)
{
    func_800177CC(D_800BBD78, (uint8 *)D_800BBD78 + 0xD4);
    D_800BBD78[0].active_00 = 3;
    D_800BBD9C              = 3;
    D_80098AF0              = 0;
    D_8009800C              = 5;
    Scene_work              = 0;
    D_80098008              = 0;
    D_8009801C              = 0;
}

void func_8005C2B8(void)
{
    sint32 off;
    uint32 i;

    func_8005C868((CODE5C_WORK *)&D_800BBD78[1]);
    if (D_800BBD94 > 0)
    {
        D_800BBD94--;
    }
    if (D_800BBD96 > 0)
    {
        D_800BBD96--;
    }
    D_80098B18 = 0;
    if (D_80098008 != Scene_work)
    {
        if (D_80098008 != 0)
        {
            D_8009800C = 3;
        }
        else
        {
            D_8009800C = 0;
        }
    }
    D_80098008 = Scene_work;
    switch (D_8009800C)
    {
        case 0:
        default:
            D_80098010                = 10;
            D_8009800C                = 1;
            D_800BBD78[0].byte_0E     = 1;
            D_800BBD78[1].byte_0E     = 1;
            D_800BBD78[2].byte_0E     = 1;
            D_800BBD78[3].byte_0E     = 1;
            D_800BBD78[4].byte_0E     = 1;
            CODE5C_GAUGE_SLOT.byte_0E = 1;
            D_800BBD78[0].x_14        = 8;
            D_800BBD78[0].y_16        = 0x88;
            D_800BBD78[1].x_14        = 0x118;
            D_800BBD78[1].y_16        = 0xBE;
            D_800BBD78[2].x_14        = 0x120;
            D_800BBD78[3].x_14        = 0x120;
            D_800BBD78[2].y_16        = 0x10;
            D_800BBD78[3].y_16        = 0x10;
            D_800BBD78[4].y_16        = 0x10;
            CODE5C_GAUGE_SLOT.y_16    = 0x18;
            D_800BBD78[4].x_14        = 0x120;
            CODE5C_GAUGE_SLOT.x_14    = 0;
            D_80098014                = 8;
            D_80098018                = 0x60;
            D_8009801C                = 1;
            break;
        case 1:
            if (D_80098010-- != 0)
            {
                off                    = (10 - D_80098010) * 8;
                D_800BBD78[0].x_14     = 8 - off;
                D_800BBD78[1].x_14     = off + 0x118;
                D_800BBD78[2].x_14     = off + 0x120;
                D_800BBD78[3].x_14     = off + 0x120;
                D_800BBD78[4].x_14     = off + 0x120;
                CODE5C_GAUGE_SLOT.x_14 = -off;
                D_80098014             = 8 - off;
            }
            else
            {
                D_8009800C = 2;
            }
            break;
        case 3:
            D_80098010                = 10;
            off                       = 0x50;
            D_8009800C                = 4;
            D_800BBD78[0].byte_0E     = 1;
            D_800BBD78[1].byte_0E     = 1;
            D_800BBD78[2].byte_0E     = 1;
            D_800BBD78[3].byte_0E     = 1;
            D_800BBD78[4].byte_0E     = 1;
            CODE5C_GAUGE_SLOT.byte_0E = 1;
            D_800BBD78[0].x_14        = 8 - off;
            D_800BBD78[0].y_16        = 0x88;
            D_800BBD78[1].x_14        = off + 0x118;
            D_800BBD78[1].y_16        = 0xBE;
            D_800BBD78[2].x_14        = off + 0x120;
            D_800BBD78[2].y_16        = 0x10;
            D_800BBD78[3].x_14        = off + 0x120;
            D_800BBD78[3].y_16        = 0x10;
            D_800BBD78[4].y_16        = 0x10;
            D_800BBD78[4].x_14        = off + 0x120;
            CODE5C_GAUGE_SLOT.x_14    = -off;
            CODE5C_GAUGE_SLOT.y_16    = 0x18;
            D_80098014                = 8 - off;
            break;
        case 4:
            if (D_80098010-- != 0)
            {
                off                    = D_80098010 * 8;
                D_800BBD78[0].x_14     = 8 - off;
                D_800BBD78[1].x_14     = off + 0x118;
                D_800BBD78[2].x_14     = off + 0x120;
                D_800BBD78[3].x_14     = off + 0x120;
                D_800BBD78[4].x_14     = off + 0x120;
                CODE5C_GAUGE_SLOT.x_14 = -off;
                D_80098014             = 8 - off;
            }
            else
            {
                D_8009800C = 5;
            }
            break;
        case 5:
            D_800BBD78[0].byte_0E     = 0;
            D_800BBD78[1].byte_0E     = 0;
            D_800BBD78[2].byte_0E     = 0;
            D_800BBD78[3].byte_0E     = 0;
            D_800BBD78[4].byte_0E     = 0;
            CODE5C_GAUGE_SLOT.byte_0E = 0;
            D_8009801C                = 0;
            break;
        case 2:
            return;
    }
    if (D_800BBD78[0].active_00 & 1)
    {
        func_8005C720((CODE5C_WORK *)&D_800BBD78[0]);
    }
    if (D_800BBD78[0].active_00 & 2)
    {
        func_8005C9BC(&D_800BBD78[0]);
    }
    if (Player_work.value171 != 0 && (D_800BBD78[1].active_00 & 2))
    {
        func_8005CCF4(&D_800BBD78[1]);
    }
    for (i = 0; i < 3; i++)
    {
        if (D_800BBD78[i + 2].active_00 & 1)
        {
            func_8005C978((CODE5C_WORK *)&D_800BBD78[i + 2]);
        }
        if (D_800BBD78[i + 2].active_00 & 2)
        {
            func_8005CEFC(&D_800BBD78[i + 2]);
        }
    }
    if (D_800BBD78[5].active_00 & 2)
    {
        func_8005D0FC(&D_800BBD78[5]);
    }
}

void func_8005C720(CODE5C_WORK *wp)
{
    D_8008D7B4[wp->routine_4](wp);
}

void func_8005C75C(CODE5C_WATCH *wp)
{
    PL_WORK *pl;

    if (wp->done_0F == 0)
    {
        pl = &Player_work;
        if ((uint8)(wp->mode_0D - 1) < 2)
        {
            wp->count_18 += 1;
            if (wp->active_0C != 0)
            {
                wp->idle_0A += 1;
            }
            else
            {
                wp->idle_0A = 0;
            }
            if (*(uint32 *)&pl->position == *(uint32 *)&pl->position_prev &&
                pl->position.z == pl->position_prev.z)
            {
                wp->still_0B += 1;
            }
            else
            {
                wp->still_0B = 0;
            }
        }
        if ((sint16)wp->count_18 >= 0x96 || (sint8)wp->still_0B >= 0x5A ||
            ((sint8)wp->idle_0A >= 0x3C && (sint8)wp->still_0B >= 0x3C))
        {
            func_8005D528();
        }
    }
}

void func_8005C858(void)
{
}

void func_8005C860(void)
{
}

void func_8005C868(CODE5C_WORK *wp)
{
    D_8008D7C0[wp->routine_4](wp);
}

void func_8005C8A4(CODE5C_REPEAT *wp)
{
    PL_WORK *pl;
    sint32 target;
    sint32 limit;

    pl     = &Player_work;
    target = func_80037604(pl, 1);
    limit  = (pl->parts[Player_work.value171].selected != 7) ? 0x11 : 0;
    if (Player_work.value171 == 1)
    {
        if (Player_work.parts[1].value06 == 0)
        {
            if (target < 2)
            {
                return;
            }
        }
        else if (target <= 0)
        {
            return;
        }
        wp->count_0F += 1;
        if (wp->count_0F < limit)
        {
            return;
        }
        wp->count_0F                    = 0;
        pl->parts[pl->value171].value06 = target;
    }
}

void func_8005C978(CODE5C_WORK *wp)
{
    D_8008D7C4[wp->routine_4](wp);
}

void func_8005C9B4(void)
{
}

void func_8005C9BC(CODE5C_SLOT *wp)
{
    sint32 x;
    sint32 y;
    sint32 face;
    sint32 len;
    sint32 hp;
    sint32 rest;
    uint32 n;
    uint32 i;

    D_80098B18 |= 1;
    if (wp->byte_0E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 8;
        y = 0x88;
    }
    if (++wp->anim_08 >= 0xC)
    {
        wp->anim_08 = 0;
    }
    if (wp->byte_0C != 0)
    {
        func_8005D298(&D_8008D570[D_80098020[wp->anim_08]], x, y, 0);
    }
    if (wp->byte_0C == 1)
    {
        wp->byte_0C = 0;
    }
    switch (wp->byte_0D)
    {
        case 0:
            face = 0;
            break;
        case 1:
            face = 4;
            break;
        case 2:
            face = D_8008D7C8[wp->timer_09];
            if (--wp->timer_09 == 0)
            {
                wp->byte_0D = 1;
            }
            break;
        case 3:
            face = D_8009802C[wp->timer_09];
            if (--wp->timer_09 == 0)
            {
                wp->byte_0D = 0;
            }
            break;
        default:
            face = 0;
            break;
    }
    len = (*(sint16 *)((uint8 *)&Player_work + 0xB0) >> 4) * 5 - 10;
    func_8005D298(&D_8008D37C[face][0], x, y - len, 0);
    func_8005D298(&D_8008D37C[face][2], x, y, 0);
    func_8005D298(&D_8008D37C[face][1], x, y - len, D_8008D37C[face][1].width | (len << 8));
    func_8005D298(&D_8008D37C[face][3], x, y, 0);
    hp = Player_work.value6e;
    if (hp > 0)
    {
        n    = hp >> 4;
        rest = hp - (n << 4);
        for (i = 0; i < n; i++)
        {
            func_8005D298(&D_8008D5E8, x, y - i * 5, 0);
        }
        if (rest != 0)
        {
            func_8005D298(&D_8008D5FC, x, y - n * 5, 0);
        }
    }
    func_8005D298(&D_8008D37C[face][4], x, y - len, ((len + 0x10) << 8) | 0x10);
}

// FAKE MATCH: one dead conditional store (`level = 0`), kept only for register allocation.
// The dead store under x != 0x118 matters: flow deletes it, but its jump survives until
// jump2, so the code after the call starts a new block. tbl and lim are then global pseudos
// set before that label: combine can't fold the table address into the load, and the
// condition's temporary (v0) pushes them into a2/a3, where sched2 hoists both to the top.
void func_8005CCF4(CODE5C_SLOT *wp)
{
    CODE5C_RECT unused; // retail's frame has 8 unexplained bytes
    PL_WORK *pl;
    sint32 x;
    sint32 y;
    sint32 dy;
    sint32 max;
    sint32 fill;
    sint32 shift;
    sint32 level;
    CODE374_VALUES **tbl;
    sint32 lim;

    D_80098B18 |= 2;
    pl = &Player_work;
    if (wp->byte_0E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 0x118;
        y = 0xBE;
    }
    dy = 0;
    if (wp->byte_0D != 0)
    {
        dy = wp->y_1A;
    }
    func_8005D298(&D_8008D610, x, y, 0);
    tbl = D_80089EAC;
    lim = 0x7FFF;
    if (x != 0x118)
    {
        level = 0; // dead store; see above
    }
    shift = D_80089A8C[pl->value170].shift;
    level = pl->parts[pl->value170].value06 - 1;
    max   = tbl[pl->value170][pl->parts[pl->value170].selected].value1;
    fill  = ((level + ((1 << shift) >> 16)) << 16) >> shift;
    if (max == lim)
    {
        func_8005D298(&D_8008D674, x, y + dy, 0);
    }
    else
    {
        max = (max << 16) >> shift;
        if (fill != 0)
        {
            func_8005D298(&D_8008D638[0], x, y + dy - fill + 1,
                          D_8008D638[0].width | ((fill - 1) << 8));
            func_8005D298(&D_8008D638[1], x, y + dy - fill, 0);
        }
        func_8005D298(&D_8008D660, x, y + dy - max, D_8008D660.width | (max << 8));
    }
    func_8005D298(&D_8008D624, x, y + dy - max, 0);
}

void func_8005CEFC(CODE5C_SLOT *wp)
{
    sint32 shift;
    sint32 mask;
    sint32 len;
    sint32 full;
    sint32 set;
    sint32 x;
    sint32 y;

    D_80098B18 |= 4;
    shift = wp->byte_0C >> 4;
    mask  = (1 << shift) - 1;
    if (wp->owner_20->value6e > 0)
    {
        len = (uint32)(wp->owner_20->value6e + mask) >> shift;
    }
    else
    {
        len = 0;
    }
    full = *(sint16 *)((uint8 *)wp->owner_20 + 0xB0) >> shift;
    set  = wp->byte_0C & 0xF;
    if (wp->byte_0E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 0x120;
        y = 0x10;
    }
    if (wp->byte_0D != 0)
    {
        x += wp->x_18;
        y += wp->y_1A;
    }
    func_8005D298(&D_8008D688[set][0], x, y, 0);
    func_8005D298(&D_8008D688[set][1], x - full, y, 0);
    if (len > 0)
    {
        func_8005D39C(&D_8008D688[set][3], x - len + 1, y, (D_8008D688[set][3].height << 8) | len,
                      wp->word_10);
        func_8005D39C(&D_8008D688[set][4], x - len, y, (D_8008D688[set][4].height << 8) | 1,
                      wp->word_10);
    }
    func_8005D298(&D_8008D688[set][2], x - full, y, (D_8008D688[set][2].height << 8) | full);
}

void func_8005D0FC(CODE5C_SLOT *wp)
{
    sint32 shift;
    sint32 len;
    sint32 full;
    sint32 mask;
    sint32 x;
    sint32 y;

    D_80098B18 |= 4;
    shift = wp->byte_0C;
    mask  = (1 << shift) - 1;
    if (*(sint16 *)((uint8 *)&Game_work + 0x5C) > 0)
    {
        len = (uint32)(*(sint16 *)((uint8 *)&Game_work + 0x5C) + mask) >> shift;
    }
    else
    {
        len = 0;
    }
    full = *(sint16 *)((uint8 *)&Game_work + 0x5E) >> shift;
    if (wp->byte_0E != 0)
    {
        x = wp->x_14;
        y = wp->y_16;
    }
    else
    {
        x = 0;
        y = 0x18;
    }
    if (wp->byte_0D != 0)
    {
        x += wp->x_18;
        y += wp->y_1A;
    }
    func_8005D298(&D_8008D750[0], x, y, 0);
    func_8005D298(&D_8008D750[1], x + full, y, 0);
    if (len > 0)
    {
        func_8005D298(&D_8008D750[3], x - 1, y, (D_8008D750[3].height << 8) | len);
        func_8005D298(&D_8008D750[4], x + len - 1, y, (D_8008D750[4].height << 8) | 1);
    }
    func_8005D298(&D_8008D750[2], x, y, (D_8008D750[2].height << 8) | full);
}

void func_8005D298(CODE5C_SPRITE *spr, sint16 x, sint16 y, uint16 size)
{
    POLY_FT4 *p;
    sint32 dx;
    sint32 dy;
    sint32 w;
    sint32 h;
    sint32 ww;
    sint32 hh;
    uint8 u;
    uint8 v;

    dx = spr->x_off;
    dy = spr->y_off;
    w  = spr->width;
    h  = spr->height;
    if ((uint16)size != 0)
    {
        ww = size & 0xFF;
        hh = (uint16)size >> 8;
    }
    else
    {
        ww = w;
        hh = h;
    }
    u                        = spr->u;
    v                        = spr->v;
    p                        = *(POLY_FT4 **)0x1F800070;
    *(POLY_FT4 **)0x1F800070 = p + 1;
    *(u_long *)p             = 0x09000000;
    *((u_long *)p + 1)       = spr->color;
    *((u_long *)p + 3)       = *((u_long *)spr + 3);
    p->tpage                 = spr->tpage;
    p->x0                    = x + dx;
    p->y0                    = y + dy;
    p->x1                    = x + dx + ww;
    p->y1                    = y + dy;
    p->x2                    = x + dx;
    p->y2                    = y + dy + hh;
    p->x3                    = x + dx + ww;
    p->y3                    = y + dy + hh;
    p->u1                    = u + w;
    p->v1                    = v;
    p->u2                    = u;
    p->v2                    = v + h;
    p->u3                    = u + w;
    p->v3                    = v + h;
    addPrim(&D_80098934->tag78, p);
}

void func_8005D39C(CODE5C_SPRITE *spr, sint16 x, sint16 y, uint16 size, sint32 color)
{
    POLY_FT4 *p;
    sint32 dx;
    sint32 dy;
    sint32 w;
    sint32 h;
    sint32 ww;
    sint32 hh;
    uint8 u;
    uint8 v;

    dx = spr->x_off;
    dy = spr->y_off;
    w  = spr->width;
    h  = spr->height;
    if ((uint16)size != 0)
    {
        ww = size & 0xFF;
        hh = (uint16)size >> 8;
    }
    else
    {
        ww = w;
        hh = h;
    }
    u                        = spr->u;
    v                        = spr->v;
    p                        = *(POLY_FT4 **)0x1F800070;
    *(POLY_FT4 **)0x1F800070 = p + 1;
    *(u_long *)p             = 0x09000000;
    *((u_long *)p + 1)       = (color & 0xFFFFFF) | 0x2C000000;
    *((u_long *)p + 3)       = *((u_long *)spr + 3);
    p->tpage                 = spr->tpage;
    p->x0                    = x + dx;
    p->y0                    = y + dy;
    p->x1                    = x + dx + ww;
    p->y1                    = y + dy;
    p->x2                    = x + dx;
    p->y2                    = y + dy + hh;
    p->x3                    = x + dx + ww;
    p->y3                    = y + dy + hh;
    p->u1                    = u + w;
    p->v1                    = v;
    p->u2                    = u;
    p->v2                    = v + h;
    p->u3                    = u + w;
    p->v3                    = v + h;
    addPrim(&D_80098934->tag78, p);
}

void func_8005D4C0(void)
{
    D_800BBD84[0] = 1;
}

void func_8005D4D4(void)
{
    D_800BBD84[0] = 2;
}

void func_8005D4E8(void)
{
    D_800BBD84[0] = 0;
}

void func_8005D4F8(void)
{
    if (D_800BBD84[1] == 0)
    {
        D_800BBD84[1] = 2;
        D_800BBD81    = 0x1C;
    }
}

void func_8005D528(void)
{
    if (D_800BBD84[3] != 1)
    {
        if ((uint8)(D_800BBD85 - 1) < 2)
        {
            D_800BBD85 = 3;
            D_800BBD81 = 6;
        }
    }
}

void func_8005D574(PL_WORK *owner, sint16 x, sint16 y, uint8 kind)
{
    uint32 i;

    if ((uint32)D_80098AF0 < 3)
    {
        for (i = 0; i < 3; i++)
        {
            if (D_800BBD78[i + 2].active_00 == 0)
            {
                goto found;
            }
        }
    }
    return;

found:
    D_80098AF0 += 1;
    D_800BBD78[i + 2].x_18      = x;
    D_800BBD78[i + 2].y_1A      = y;
    D_800BBD78[i + 2].owner_20  = owner;
    D_800BBD78[i + 2].active_00 = 3;
    D_800BBD78[i + 2].byte_0C   = kind;
    D_800BBD78[i + 2].byte_0D   = 1;
}

// word_10 is indexed from slot 2 (retail recomputes i * 0x24 for it instead of reusing the
// scan offset).
void func_8005D620(PL_WORK *owner, sint16 x, sint16 y, uint8 kind, sint32 value)
{
    uint32 i;

    if ((uint32)D_80098AF0 < 3)
    {
        for (i = 0; i < 3; i++)
        {
            if (D_800BBD78[i + 2].active_00 == 0)
            {
                goto found;
            }
        }
    }
    return;

found:
    D_80098AF0 += 1;
    D_800BBD78[i + 2].x_18      = x;
    D_800BBD78[i + 2].y_1A      = y;
    D_800BBD78[i + 2].active_00 = 3;
    D_800BBD78[i + 2].byte_0D   = 1;
    D_800BBD78[i + 2].byte_0C   = kind;
    (&D_800BBD78[2])[i].word_10 = value;
    D_800BBD78[i + 2].owner_20  = owner;
}

void func_8005D6E8(PL_WORK *owner)
{
    uint32 i;
    uint32 slot;

    for (i = 0, slot = 2; i < 3; i++, slot++)
    {
        if (D_800BBD78[slot].active_00 != 0 && D_800BBD78[slot].owner_20 == owner)
        {
            goto found;
        }
    }
    return;

found:
    D_80098AF0 -= 1;
    ((uint32 *)&D_800BBD78[slot])[0] = 0;
    ((uint32 *)&D_800BBD78[slot])[1] = 0;
    ((uint32 *)&D_800BBD78[slot])[2] = 0;
    ((uint32 *)&D_800BBD78[slot])[3] = 0;
    ((uint32 *)&D_800BBD78[slot])[4] = 0;
    ((uint32 *)&D_800BBD78[slot])[5] = 0;
    ((uint32 *)&D_800BBD78[slot])[6] = 0;
    ((uint32 *)&D_800BBD78[slot])[7] = 0;
}

void func_8005D7C0(void)
{
    uint32 i;

    D_80098AF0 = 0;
    for (i = 0; i < 3; i++)
    {
        ((uint32 *)&D_800BBD78[i + 2])[0] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[1] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[2] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[3] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[4] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[5] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[6] = 0;
        ((uint32 *)&D_800BBD78[i + 2])[7] = 0;
    }
}

void func_8005D844(sint16 arg0, sint16 arg1, uint8 arg2)
{
    D_800BBE2C.byte = 3;
    D_800BBE44.half = arg0;
    D_800BBE46      = arg1;
    D_800BBE38.byte = arg2;
    D_800BBE39      = 1;
}

void func_8005D87C(void)
{
    D_800BBE2C.word = 0;
    D_800BBE30      = 0;
    D_800BBE34      = 0;
    D_800BBE38.word = 0;
    D_800BBE3C      = 0;
    D_800BBE40      = 0;
    D_800BBE44.word = 0;
    D_800BBE48      = 0;
}

sint32 func_8005D8C4(sint32 arg0)
{
    if (D_800BBD94 > 0)
    {
    fail:
        return 0;
    }
    switch (D_800BBD85)
    {
        case 0:
        case 3:
            if (arg0 == 0)
            {
                goto fail;
            }
            func_8005D4F8();
            D_800BBD82 = 0;
            D_800BBD83 = 0;
            D_800BBD90 = 0;
            break;
    }
    return 1;
}

uint8 func_8005D938(void)
{
    if (D_800BBD94 > 0)
    {
        return 0;
    }
    return D_800BBD84[3];
}

sint32 func_8005D95C(void)
{
    return D_800BBD84[3];
}

void func_8005D96C(void)
{
}

void func_8005D974(void)
{
}

void func_8005D97C(void)
{
    D_800BBDAB = 0;
}

void func_8005D98C(void)
{
    if (D_800BBD94 <= 0)
    {
        D_800BBD84[3] = 1;
        func_8005D4F8();
    }
}

void func_8005D9C4(void)
{
    D_800BBD84[3] = 0;
    func_8005D528();
}

void func_8005D9EC(void)
{
    Player_work.value6e = *(uint16 *)((uint8 *)&Player_work + 0xB0);
    func_8005D9C4();
}

sint32 func_8005DA1C(sint32 arg0)
{
    if (arg0 != 0 && D_800BBD84[3] != 0)
    {
        D_800BBD84[3] = 0;
        D_800BBD85    = 3;
        D_800BBD81    = 6;
        return 0;
    }
    return D_800BBD84[3] == 0;
}

sint32 func_8005DA78(sint32 arg0)
{
    sint16 cur;
    sint16 target;

    if (arg0 != 0)
    {
        cur    = Player_work.value6e;
        target = *(sint16 *)((uint8 *)&Player_work + 0xB0);
        if (cur + 2 >= target)
        {
            Player_work.value6e = target;
            return 1;
        }
        Player_work.value6e = cur + 2;
        return 0;
    }
    return Player_work.value6e == *(sint16 *)((uint8 *)&Player_work + 0xB0);
}

sint32 func_8005DAEC(sint32 arg0)
{
    PL_WORK *pl;
    sint32 target;
    sint16 cur;

    pl     = &Player_work;
    target = func_80037604(pl, Player_work.part_index);
    if (target == 0x7FFF)
    {
        return 1;
    }
    if (arg0 != 0)
    {
        cur = pl->parts[Player_work.part_index].value06;
        if (cur + 0x10 >= target)
        {
            pl->parts[Player_work.part_index].value06 = target;
            return 1;
        }
        pl->parts[Player_work.part_index].value06 = cur + 0x10;
        return 0;
    }
    return pl->parts[Player_work.part_index].value06 == target;
}

void func_8005DBB4(sint32 arg0)
{
    sint32 i;

    if (arg0 == 0)
    {
        for (i = 0; i < 0x280; i++)
        {
            D_800BC9B8[i] = -1;
        }
    }
    else
    {
        func_800176DC(&D_800B7030, D_800BC9B8, 0x50);
    }
}

void func_8005DC10(sint32 arg0)
{
    sint32 i;

    D_80098004 = 0;
    if (arg0 != 0)
    {
        for (i = 0; i < 0x40; i++)
        {
            if (D_8008D19C[i].stage == 0xFF)
            {
                return;
            }
            if (D_8008D19C[i].stage == Game_work.routine_50 &&
                D_8008D19C[i].room == (sint8)Game_work.routine_51)
            {
                D_80098004 = 3;
                D_8009878C = arg0;
                D_80098794 = i;
                D_8009882C = D_8008D19C[i].value;
                return;
            }
        }
    }
}

void func_8005DCB4(void)
{
    func_8005DCDC();
    func_8005DE28();
}

// The negated room origin comes first so the room x/z loads precede the player loads.
void func_8005DCDC(void)
{
    CODE5C_OFS9 dx;
    CODE5C_OFS9 dz;
    uint32 width;
    uint32 height;
    sint32 px;
    sint32 pz;
    sint32 x;
    sint32 z;
    sint32 i;
    uint8 *map;

    dx = D_80098038;
    dz = D_80098044;
    if (D_80098004 & 1)
    {
        width  = D_8008D19C[D_80098794].width;
        px     = (-D_8008D19C[D_80098794].x + Player_work.position.x) >> 9;
        height = D_8008D19C[D_80098794].height;
        pz     = (-D_8008D19C[D_80098794].z + Player_work.position.z) >> 9;
        for (i = 0; i < 9; i++)
        {
            x = px + dx.v[i];
            z = pz + dz.v[i];
            if ((uint32)x < width && (uint32)z < height)
            {
                map = (uint8 *)D_8009882C + ((sint32)(width * z + x) >> 3);
                *map &= ~(0x80 >> (x & 7));
            }
        }
    }
}

// Statement order sets retail's load/store schedule.
void func_8005DE28(void)
{
    CODE5C_POINT pos;
    CODE5C_POINT size;
    CODE5C_POINT cell;
    CODE5C_RECT rect;
    sint32 room_x;
    sint32 room_z;

    if (*((sint8 *)&Game_work + 0x59) == 0 && (D_80098004 & 2))
    {
        if (D_8009801C == 0)
        {
            D_80098014 = 8;
            D_80098018 = 0x60;
        }
        room_x     = D_8008D19C[D_80098794].x;
        room_z     = D_8008D19C[D_80098794].z;
        pos.x      = D_80098014;
        cell.x     = ((Player_work.position.x - room_x) >> 9) - 5;
        cell.y     = ((Player_work.position.z - room_z) >> 9) - 5;
        size.x     = 0xB;
        pos.y      = D_80098018;
        size.y     = 0xB;
        rect.w     = 0x36;
        rect.h     = 0x36;
        rect.x     = pos.x + 6;
        D_80098034 = 6;
        rect.y     = pos.y - 0x3C;
        func_8005E144(&pos, &size, &cell, &rect);
        func_8005E9F8(&rect);
    }
}

void func_8005DF3C(void)
{
    D_800986F8 = 0;
    D_800986FC = 0;
}

void func_8005DF4C(void)
{
    CODE5C_POINT pos;
    CODE5C_POINT size;
    CODE5C_POINT cell;
    CODE5C_RECT rect;
    uint16 pad;
    uint32 scale;
    uint32 w;
    uint32 h;
    uint32 mw;
    uint32 mh;

    if (D_80098004 & 2)
    {
        pad = D_800C0C26;
        if (pad & 0x10)
        {
            D_800986FC -= 2;
        }
        if (pad & 0x40)
        {
            D_800986FC += 2;
        }
        if (pad & 0x80)
        {
            D_800986F8 -= 2;
        }
        if (pad & 0x20)
        {
            D_800986F8 += 2;
        }
        if (D_800986F8 < -0x20)
        {
            D_800986F8 = -0x20;
        }
        if (D_800986F8 > 0x20)
        {
            D_800986F8 = 0x20;
        }
        if (D_800986FC < -0x20)
        {
            D_800986FC = -0x20;
        }
        if (D_800986FC > 0x20)
        {
            D_800986FC = 0x20;
        }
        scale      = 6;
        w          = 0x140 / scale;
        h          = 0xF0 / scale;
        D_80098034 = scale;
        size.x = mw = D_8008D19C[D_80098794].width;
        size.y = mh = D_8008D19C[D_80098794].height;
        cell.x      = 0;
        cell.y      = 0;
        rect.x      = 0;
        rect.y      = 0;
        rect.w      = 0x140;
        rect.h      = 0xF0;
        pos.x       = D_800986F8 + (((w - mw) * scale >> 1) + 1);
        pos.y       = D_800986FC - (((h - mh) * scale >> 1) - 0xF0);
        func_8005E144(&pos, &size, &cell, &rect);
        func_8005EAA8(&rect);
    }
}

void func_8005E144(CODE5C_POINT *pos, CODE5C_POINT *size, CODE5C_POINT *cell, CODE5C_RECT *rect)
{
    POLY_G4 *arrow;
    DR_AREA *area;
    CODE5C_FT4_WORDS *p;
    RECT clip;
    uint32 width;
    uint32 height;
    sint32 x;
    sint32 y;
    sint32 angle;
    sint32 i;
    sint32 j;
    uint32 cx;
    sint32 left;
    sint32 right;
    sint32 bottom;
    sint32 top;

    if ((sint16)rect->x + (sint16)rect->w >= 0)
    {
        arrow                = CODE5C_PRIM(POLY_G4);
        width                = D_8008D19C[D_80098794].width;
        height               = D_8008D19C[D_80098794].height;
        CODE5C_PRIM(POLY_G4) = arrow + 1;
        // The tags are stored through plain casts and the colour words through a word
        // view; the different alias classes give retail's load/store order.
        *(uint32 *)arrow                 = 0x08000000;
        ((CODE5C_G4_WORDS *)arrow)->rgb0 = 0x3800FFFF;
        ((CODE5C_G4_WORDS *)arrow)->rgb1 = 0xFFFF;
        ((CODE5C_G4_WORDS *)arrow)->rgb2 = 0xFF;
        ((CODE5C_G4_WORDS *)arrow)->rgb3 = 0xFF;
        angle                            = -Player_work.rotation.y;
        x = pos->x +
            (((Player_work.position.x - D_8008D19C[D_80098794].x) >> 9) - cell->x) * D_80098034 +
            ((uint32)D_80098034 >> 1);
        y = pos->y -
            (((Player_work.position.z - D_8008D19C[D_80098794].z) >> 9) - cell->y) * D_80098034 -
            ((uint32)D_80098034 >> 1);
        arrow->x0 = ((rsin(angle - 0x40) * 6 + 0x800) >> 12) + x;
        arrow->y0 = ((rcos(angle - 0x40) * 6 + 0x800) >> 12) + y;
        arrow->x1 = ((rsin(angle + 0x40) * 6 + 0x800) >> 12) + x;
        arrow->y1 = ((rcos(angle + 0x40) * 6 + 0x800) >> 12) + y;
        arrow->x2 = ((rsin(angle + 0x600) * 4 + 0x800) >> 12) + x;
        arrow->y2 = ((rcos(angle + 0x600) * 4 + 0x800) >> 12) + y;
        arrow->x3 = ((rsin(angle - 0x600) * 4 + 0x800) >> 12) + x;
        arrow->y3 = ((rcos(angle - 0x600) * 4 + 0x800) >> 12) + y;
        addPrim(&D_80098934->tag78, arrow);

        area = CODE5C_PRIM(DR_AREA)++;
        SetDrawArea(area, &D_80098050[CODE800133D8_DISPLAY_INDEX]);
        addPrim(&D_80098934->tag78, area);

        for (j = 0; j < size->y; j++)
        {
            if ((uint32)(cell->y + j) < height)
            {
                for (i = 0; i < size->x; i++)
                {
                    cx = cell->x + i;
                    if (cx < width &&
                        (sint8)(((uint8 *)D_8009882C)[(sint32)(width * (cell->y + j) + cx) >> 3]
                                << (cx & 7)) >= 0)
                    {
                        p            = CODE5C_PRIM(CODE5C_FT4_WORDS)++;
                        *(uint32 *)p = 0x09000000;
                        p->rgb0      = 0x2EC0C0C0;
                        left         = pos->x + i * D_80098034;
                        right        = left + D_80098034;
                        bottom       = pos->y - j * D_80098034;
                        top          = bottom - D_80098034;
                        p->xy0       = (top << 16) | (left & 0xFFFF);
                        p->xy1       = (top << 16) | (right & 0xFFFF);
                        p->xy2       = (bottom << 16) | (left & 0xFFFF);
                        p->xy3       = (bottom << 16) | (right & 0xFFFF);
                        switch (*((uint8 *)D_8009878C + (cell->y + j) * width + (cell->x + i)))
                        {
                            default:
                            case 0:
                                p->uv0 = 0x3E748109;
                                p->uv1 = 0xD810F;
                                p->uv2 = 0x8709;
                                p->uv3 = 0x870F;
                                break;
                            case 1:
                                p->uv0 = 0x3E748101;
                                p->uv1 = 0xD8107;
                                p->uv2 = 0x8701;
                                p->uv3 = 0x8707;
                                break;
                            case 2:
                                p->uv0 = 0x3E748111;
                                p->uv1 = 0xD8117;
                                p->uv2 = 0x8711;
                                p->uv3 = 0x8717;
                                break;
                            case 3:
                                p->uv0 = 0x3E748119;
                                p->uv1 = 0xD811F;
                                p->uv2 = 0x8719;
                                p->uv3 = 0x871F;
                                break;
                            case 4:
                                p->uv0 = 0x3E748121;
                                p->uv1 = 0xD8127;
                                p->uv2 = 0x8721;
                                p->uv3 = 0x8727;
                                break;
                            case 5:
                                p->uv0 = 0x3E748129;
                                p->uv1 = 0xD812F;
                                p->uv2 = 0x8729;
                                p->uv3 = 0x872F;
                                break;
                            case 6:
                                p->uv0 = 0x3E748131;
                                p->uv1 = 0xD8137;
                                p->uv2 = 0x8731;
                                p->uv3 = 0x8737;
                                break;
                            case 7:
                                p->uv0 = 0x3E748139;
                                p->uv1 = 0xD813F;
                                p->uv2 = 0x8739;
                                p->uv3 = 0x873F;
                                break;
                            case 8:
                                p->uv0 = 0x3E748141;
                                p->uv1 = 0xD8147;
                                p->uv2 = 0x8741;
                                p->uv3 = 0x8747;
                                break;
                            case 9:
                                p->uv0 = 0x3E748149;
                                p->uv1 = 0xD814F;
                                p->uv2 = 0x8749;
                                p->uv3 = 0x874F;
                                break;
                            case 10:
                                p->uv0 = 0x3E748909;
                                p->uv1 = 0xD890F;
                                p->uv2 = 0x8F09;
                                p->uv3 = 0x8F0F;
                                break;
                            case 11:
                                p->uv0 = 0x3E748901;
                                p->uv1 = 0xD8907;
                                p->uv2 = 0x8F01;
                                p->uv3 = 0x8F07;
                                break;
                            case 12:
                                p->uv0 = 0x3E748911;
                                p->uv1 = 0xD8917;
                                p->uv2 = 0x8F11;
                                p->uv3 = 0x8F17;
                                break;
                            case 13:
                                p->uv0 = 0x3E748919;
                                p->uv1 = 0xD891F;
                                p->uv2 = 0x8F19;
                                p->uv3 = 0x8F1F;
                                break;
                            case 14:
                                p->uv0 = 0x3E748921;
                                p->uv1 = 0xD8927;
                                p->uv2 = 0x8F21;
                                p->uv3 = 0x8F27;
                                break;
                            case 15:
                                p->uv0 = 0x3E748929;
                                p->uv1 = 0xD892F;
                                p->uv2 = 0x8F29;
                                p->uv3 = 0x8F2F;
                                break;
                            case 16:
                                p->uv0 = 0x3E748931;
                                p->uv1 = 0xD8937;
                                p->uv2 = 0x8F31;
                                p->uv3 = 0x8F37;
                                break;
                            case 17:
                                p->uv0 = 0x3E748939;
                                p->uv1 = 0xD893F;
                                p->uv2 = 0x8F39;
                                p->uv3 = 0x8F3F;
                                break;
                            case 18:
                                p->uv0 = 0x3E748941;
                                p->uv1 = 0xD8947;
                                p->uv2 = 0x8F41;
                                p->uv3 = 0x8F47;
                                break;
                            case 19:
                                p->uv0 = 0x3E748949;
                                p->uv1 = 0xD894F;
                                p->uv2 = 0x8F49;
                                p->uv3 = 0x8F4F;
                                break;
                        }
                        addPrim(&D_80098934->tag78, p);
                    }
                }
            }
        }

        area   = CODE5C_PRIM(DR_AREA)++;
        clip.x = rect->x;
        clip.y = rect->y + (CODE800133D8_DISPLAY_INDEX << 8);
        clip.w = rect->w;
        clip.h = rect->h;
        SetDrawArea(area, &clip);
        addPrim(&D_80098934->tag78, area);
    }
}

void func_8005E9F8(CODE5C_RECT *rect)
{
    POLY_F4 *p;

    p                       = *(POLY_F4 **)0x1F800070;
    *(POLY_F4 **)0x1F800070 = p + 1;
    *(u_long *)p            = 0x05000000;
    *((u_long *)p + 1)      = 0x2A808080;
    p->x0 = p->x2 = rect->x;
    p->x1 = p->x3 = rect->x + rect->w;
    p->y0 = p->y1 = rect->y;
    p->y2 = p->y3 = rect->y + rect->h;
    addPrim(&D_80098934->tag78, p);
}

void func_8005EAA8(CODE5C_RECT *rect)
{
    POLY_G4 *p;
    sint32 i;

    for (i = 0; i < 2; i++)
    {
        p                            = CODE5C_PRIM(POLY_G4)++;
        *(u_long *)p                 = 0x08000000;
        ((CODE5C_G4_WORDS *)p)->rgb0 = D_8009806C[i].color[0] | 0x38000000;
        ((CODE5C_G4_WORDS *)p)->rgb1 = D_8009806C[i].color[1];
        ((CODE5C_G4_WORDS *)p)->rgb2 = D_8009806C[i].color[2];
        ((CODE5C_G4_WORDS *)p)->rgb3 = D_8009806C[i].color[3];
        p->x0 = p->x2 = 0;
        p->x1 = p->x3 = 0x140;
        p->y0 = p->y1 = i * 0x78;
        p->y2 = p->y3 = (i + 1) * 0x78;
        addPrim(&D_80098934->tag78, p);
    }
}

void func_8005EBA4(sint16 arg0)
{
    D_800BBD94 = arg0;
}

void func_8005EBB4(sint16 arg0)
{
    D_800BBD96 = arg0;
}

sint16 func_8005EBC4(void)
{
    return D_800BBD94;
}

sint16 func_8005EBD4(void)
{
    return D_800BBD96;
}

void func_8005EBE4(void)
{
    D_800A38F0 = 0;
    D_800A38F8 = *((uint8 *)&Player_work + 0x450);
    D_800A38F9 = *((uint8 *)&Player_work + 0x451);
    D_800A38FA = *((uint8 *)&Player_work + 0x452);
    D_800A38FB = Player_work.value170;
}
