#include "common.h"
#include "code_800680bc.h"

void func_800680BC(sint32 arg)
{
    D_800C356C = -1;
    D_800C356E = 0x18;
    D_800C356F = arg;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

void func_80068120(sint32 r, sint32 g, sint32 b, uint16 tpage)
{
    CODE68_TILE *tile;
    POLY_FT4 *packet;
    POLY_FT4 *mode;

    tile = (CODE68_TILE *)*CODE68_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->g0   = g;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->r0   = r;
    tile->b0   = b;
    tile->code |= 2;
    packet             = *CODE68_PACKET_PTR;
    mode               = packet + 1;
    *CODE68_PACKET_PTR = mode;
    SetDrawMode((DR_MODE *)mode, 0, 0, (tpage << 5) | 0xF, NULL);
    (*CODE68_PACKET_PTR)++;
    addPrim(&D_80098934->tag74, tile);
    addPrim(&D_80098934->tag74, mode);
}

void func_80068244(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_24;
        child->routine_9 = 0;
        child->routine_a = 0;
        child->flags_0 |= 2;
        func_800680BC(0);
    }
}

void func_80068290(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        func_800680BC(1);
        wp->child_24->flags_0 &= ~2;
        child            = wp->child_28;
        child->routine_9 = 0xB;
        child->word_1c   = 0xFE480000;
        child->routine_a = 0;
        child->word_24   = 0xFE700000;
        child->flags_0 |= 2;
        child            = wp->child_2c;
        child->routine_9 = 0;
        child->routine_a = 0;
        child->flags_0 |= 2;
        wp->child_30->flags_0 |= 2;
    }
}

void func_80068344(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_2c;
        child->routine_9 = 1;
        child->angle_56  = 0x800;
        child->routine_a = 0;
        child->word_1c   = 0xFEA20000;
        child->flags_0 |= 2;
    }
}

// The 0xD2 colours are set in field order; that keeps 0x2108 and 0x2D6B live together.
void func_80068388(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_28;
        child->routine_9 = 1;
        child->word_1c   = 0xFE5C0000;
        child->word_24   = 0xFF380000;
        child->routine_a = 0;
        child->angle_56  = 0xC00;
        child->flags_0 |= 2;
    }
    if (wp->timer_10 == 0x3E)
    {
        child            = wp->child_28;
        child->routine_9 = 2;
        child->routine_a = 0;
    }
    if (wp->timer_10 == 0x52)
    {
        child            = wp->child_28;
        child->word_24   = 0xFF420000;
        child->value_14b = -1;
        child->value_14f = -1;
    }
    if (wp->timer_10 == 0x79)
    {
        child            = wp->child_28;
        child->routine_9 = 3;
        child->routine_a = 0;
    }
    if (wp->timer_10 == 0xD2)
    {
        child            = wp->child_28;
        child->routine_9 = 4;
        child->routine_a = 0;
        child->color_18e = 0x2108;
        child->color_19e = 0x2D6B;
        child->color_1a6 = 0x2108;
        child->color_1b6 = 0x2D6B;
        child->color_1be = 0x2108;
        child->color_1fe = 0x2108;
        child->color_206 = 0x2108;
        child->color_20e = 0x2108;
        child->color_216 = 0x2108;
        child->color_21e = 0x2108;
        child->value_10b = -1;
        child->value_117 = -1;
        child->value_143 = 0;
        child->value_147 = 0;
    }
}

void func_8006849C(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->word_c == 0)
    {
        func_800680BC(2);
        child = wp->child_28;
        child->flags_0 &= ~2;
        child = wp->child_2c;
        child->flags_0 &= ~2;
    }
}

void func_80068508(CODE68_CHILD *child, sint32 index)
{
    CODE68_PAL *pal = (CODE68_PAL *)((uint8 *)child + index * 8);

    if (pal->color_186 != 0x4210)
    {
        pal->color_186 += 0x421;
        if (pal->color_186 == 0x4210)
        {
            pal->color_186 = 0x4210;
        }
    }
}

void func_8006854C(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        func_800680BC(1);
        child            = wp->child_28;
        child->routine_9 = 5;
        child->word_1c   = 0xFE590000;
        child->word_24   = 0xFF3D0000;
        child->routine_a = 0;
        child->value_10b = 0;
        child->value_117 = 0;
        child->value_143 = -1;
        child->value_147 = -1;
        child->flags_0 |= 2;
        child = wp->child_2c;
        child->flags_0 |= 2;
        wp->word_64 = 1;
        wp->word_74 = 2;
        wp->word_70 = 0;
        wp->word_6c = 0;
        wp->word_68 = 0;
    }
    if (wp->timer_10 >= 0xE && wp->timer_10 < 0x15)
    {
        child = wp->child_28;
        func_80068508(child, 1);
        func_80068508(child, 3);
        func_80068508(child, 6);
        func_80068508(child, 7);
        func_80068508(child, 4);
        func_80068508(child, 0xF);
        func_80068508(child, 0x10);
        func_80068508(child, 0x11);
        func_80068508(child, 0x12);
        func_80068508(child, 0x13);
    }
    if (wp->timer_10 == 0x39)
    {
        child          = wp->child_28;
        child->value_d = 1;
    }
    if (wp->timer_10 == 0x57)
    {
        child          = wp->child_28;
        child->value_d = 0;
    }
    if (wp->timer_10 >= 0x5A && wp->timer_10 < 0x79)
    {
        wp->word_68 += 9;
        wp->word_6c += 9;
        wp->word_70 += 9;
        if (wp->word_68 >= 0xFF)
        {
            wp->word_68 = wp->word_6c = wp->word_70 = 0xFF;
        }
    }
}

void func_80068728(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child                 = wp->child_2c;
        child->routine_9      = 1;
        child->routine_a      = 0;
        wp->word_64           = 0;
        wp->child_30->value_e = -0x80;
    }
}

void func_80068760(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_2c;
        child->routine_9 = 2;
        child->word_1c   = 0xFECC0000;
        child->routine_a = 0;
        child->word_24   = 0xFE840000;
        child            = wp->child_28;
        child->routine_9 = 0xC;
        child->routine_a = 0;
        child->word_1c   = 0xFE5C0000;
        child->angle_56  = 0;
    }
    if (wp->timer_10 == 0x11)
    {
        child            = wp->child_2c;
        child->routine_9 = 0;
        child->routine_a = 0;
        child->angle_56  = 0;
    }
}

void func_800687D8(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_28;
        child->routine_9 = 6;
        child->value_d   = 1;
        child->routine_a = 0;
        child->word_1c   = 0xFF380000;
        child->word_24   = 0xFF380000;
        child->angle_56  = 0;
    }
    if (wp->timer_10 == 0x3C)
    {
        child          = wp->child_28;
        child->value_d = 0;
    }
    if (wp->timer_10 == 0x66)
    {
        child            = wp->child_2c;
        child->routine_9 = 3;
        child->routine_a = 0;
        child->angle_56  = 0x800;
    }
}

void func_8006885C(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_2c;
        child->routine_9 = 4;
        child->routine_a = 0;
        child->angle_56  = 0x800;
    }
}

void func_8006888C(CODE68_WORK *wp)
{
    if (wp->timer_10 == 0xA)
    {
        func_80101D94();
    }
}

void func_800688BC(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_2c;
        child->routine_9 = 5;
        child->routine_a = 0;
    }
}

void func_800688E4(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_28;
        child->routine_9 = 7;
        child->routine_a = 0;
    }
}

void func_8006890C(CODE68_WORK *wp)
{
    CODE68_CHILD *child;
    CODE68_CHILD *other;

    if (wp->timer_10 == 0)
    {
        func_800680BC(0);
        child            = wp->child_24;
        child->routine_9 = 1;
        child->routine_a = 0;
        child->flags_0 |= 2;
        other = wp->child_28;
        other->flags_0 &= ~2;
        other = wp->child_2c;
        other->flags_0 &= ~2;
    }
}

void func_80068998(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        func_800680BC(1);
        wp->child_24->flags_0 &= ~2;
        child = wp->child_28;
        child->flags_0 |= 2;
        child            = wp->child_2c;
        child->routine_9 = 6;
        child->routine_a = 0;
        child->flags_0 |= 2;
    }
}

void func_80068A24(CODE68_WORK *wp)
{
    CODE68_CHILD *child;
    CODE68_CHILD *other;

    if (wp->timer_10 == 0)
    {
        func_800680BC(0);
        child            = wp->child_24;
        child->routine_9 = 1;
        child->routine_a = 0;
        child->flags_0 |= 2;
        other = wp->child_28;
        other->flags_0 &= ~2;
        other = wp->child_2c;
        other->flags_0 &= ~2;
    }
}

void func_80068AB0(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        func_800680BC(1);
        wp->child_24->flags_0 &= ~3;
        child            = wp->child_28;
        child->routine_9 = 8;
        child->routine_a = 0;
        child->flags_0 |= 2;
        child = wp->child_2c;
        child->flags_0 |= 2;
    }
}

void func_80068B3C(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        func_800680BC(0);
        wp->child_24->flags_0 |= 3;
        child = wp->child_28;
        child->flags_0 &= ~2;
        child = wp->child_2c;
        child->flags_0 &= ~2;
    }
}

void func_80068BC0(CODE68_WORK *wp)
{
    if (wp->timer_10 == 0)
    {
        wp->child_24->routine_a = 2;
    }
}

void func_80068BE4(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        func_800680BC(1);
        wp->child_24->flags_0 &= ~2;
        child            = wp->child_28;
        child->routine_9 = 9;
        child->word_1c   = 0xFF1F0000;
        child->word_20   = 0xFFFB0000;
        child->word_24   = 0xFE700000;
        child->routine_a = 0;
        child->angle_56  = 0x400;
        child->flags_0 |= 2;
        child = wp->child_2c;
        child->flags_0 |= 2;
    }
    if (wp->timer_10 == 0x32)
    {
        child            = wp->child_28;
        child->routine_9 = 0xA;
        child->routine_a = 0;
        child->flags_0 |= 2;
    }
}

void func_80068CB8(CODE68_WORK *wp)
{
    CODE68_CHILD *child;

    if (wp->timer_10 == 0)
    {
        child            = wp->child_2c;
        child->routine_9 = 7;
        child->routine_a = 0;
    }
}

void func_80068CE0(CODE68_WORK *wp)
{
    CODE68_ENTRY *entry;

    func_8001E6C0(0, 0, 0);
    entry      = D_8008FF88;
    D_800BC7F0 = D_8008FFD8;
    wp->tbl_a4 = D_8009039C;
    func_8001EAE8(entry);
    func_8001EAE8(entry + 1);
    func_8001EAE8(entry + 2);
    func_8001EAE8(entry + 3);
    wp->word_64 = 0;
}

void func_80068D64(CODE68_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_a4[1](wp);
    }
}

void func_80068DA4(void)
{
}

void func_80068DAC(CODE68_WORK *wp)
{
    PL_WORK *pl;

    switch (wp->routine_4)
    {
        case 0:
            pl = &Player_work;
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 &= 0xFC;
                wp->routine_4++;
                func_8001D58C(0x2001000B);
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->word_c = 0x1E;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->word_c == 0)
            {
                wp->routine_4++;
                func_80017C30(2);
            }
            break;
        case 3:
            func_80068CE0(wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_a4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(10);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80068D64(wp);
            if (wp->word_64 != 0)
            {
                func_80068120((uint8)wp->word_68, (uint8)wp->word_6c, (uint8)wp->word_70,
                              wp->word_74);
            }
            func_8001EC0C();
            func_8001F070();
            if (wp->word_14 == 0x4680)
            {
                func_80068DA4();
            }
            if (wp->routine_4 == 5 && D_80098A72 == 0)
            {
                D_800C356C  = 2;
                D_800C356E  = 0x1B;
                D_800C356F  = 6;
                D_800C3560  = -0x40;
                D_800C3562  = -1;
                D_800C3564  = 0xC0;
                D_800C356A  = 0x800;
                D_800C356D  = 0;
                D_800C3571  = 0xFF;
                D_800C3570  = 2;
                wp->flags_0 = 0;
                func_8001D494(0, 1, 0);
                Player_work.routine_0 |= 1;
                func_80042314(&Player_work);
                func_8001E390(0x2EB);
                Sce_flag_on(0x55);
                func_8001D974();
            }
            break;
    }
}
