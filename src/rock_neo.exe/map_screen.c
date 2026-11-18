#include "common.h"
#include "map_screen.h"

// Small data reached through $gp
MAP_SCREEN_WORK Map_screen_work;

void Map_screen_init(void)
{
    *(uint32 *)&Map_screen_work.routine_0 = 0;
    *(uint32 *)&Map_screen_work.mode_4    = 0;
    if ((sint8)Game_work.flags_52 < 9)
    {
        Map_screen_work.mode_4 = 0;
    }
    else
    {
        Map_screen_work.mode_4 = 1;
    }
}

sint32 Map_screen_task(void)
{
    MAP_SCREEN_WORK *wp;
    uint16 pad;
    sint32 cursor;

    wp  = &Map_screen_work;
    pad = D_800C0C2A;
    switch (Map_screen_work.routine_0)
    {
        case 0:
            map_cursor_set();
            map_screen_set();
            if (pad & 0x1009)
            {
                Sound_call(0x83, 1, 0);
                return 1;
            }
            if (((pad & 0x4828) == 0) != ((pad & 0x480) == 0))
            {
                if (pad & 0x480)
                {
                    if (--Map_screen_work.cursor_5 < 0)
                    {
                        Map_screen_work.cursor_5 = (Map_screen_work.mode_4 > 0) ? 2 : 1;
                    }
                }
                else
                {
                    cursor = ++Map_screen_work.cursor_5;
                    if ((Map_screen_work.mode_4 > 0) ? (cursor >= 3) : (cursor >= 2))
                    {
                        wp->cursor_5 = 0;
                    }
                }
                Sound_call(0x82, 1, 0);
                wp->routine_0++;
            }
            break;
        case 1:
            if (Map_screen_work.mode_4 == 0)
            {
                Cd_read_comb(D_8008DB28[Map_screen_work.cursor_5]);
            }
            else
            {
                Cd_read_comb(D_8008DB2C[Map_screen_work.cursor_5]);
            }
            wp->routine_0++;
            break;
        case 2:
            if (Cd_read_sync2() != 0)
            {
                return 0;
            }
            Map_screen_work.routine_0 = 0;
            break;
    }
    return 0;
}

void map_screen_set(void)
{
    POLY_FT4 *p;

    p                        = *CODE800133D8_PACKET_PTR;
    *CODE800133D8_PACKET_PTR = p + 1;
    *(u_long *)p             = 0x09000000;
    p->x0 = p->x2 = 0x20;
    p->x1 = p->x3 = 0x11F;
    p->y2 = p->y3      = 0xF0;
    p->tpage           = 0x8C;
    *(u_short *)&p->u1 = 0xFF;
    *(u_short *)&p->u2 = 0xF000;
    *(u_long *)&p->r0  = 0x2C808080;
    *(u_short *)&p->u0 = 0;
    *(u_short *)&p->u3 = 0xF0FF;
    p->y0 = p->y1 = 0;
    p->clut       = 0x3E80;
    AddPrim(&D_80098934->tag78, p);
}

void map_cursor_set(void)
{
    GAME_WORK *gw;
    POLY_FT4 *p;
    sint32 n;
    sint32 x;
    sint32 y;
    sint32 u;

    gw = &Game_work;
    switch (gw->routine_50)
    {
        case 3:
        case 27:
            n = 3;
            if ((sint8)gw->routine_51 < 3)
            {
                n = (sint8)gw->routine_51;
            }
            break;
        case 15:
            n = 6;
            break;
        case 19:
            n = 10;
            break;
        case 28:
            n = 8;
            break;
        case 23:
        case 29:
            return;
        default:
            n = gw->routine_50;
            break;
    }
    x                        = D_8008DB34[n].x;
    y                        = D_8008DB34[n].y;
    p                        = *CODE800133D8_PACKET_PTR;
    *CODE800133D8_PACKET_PTR = p + 1;
    u                        = (MAP_SCREEN_FRAME & 7) << 4;
    *(u_long *)p             = 0x09000000;
    p->tpage                 = 0x8C;
    *(u_long *)&p->r0        = 0x2C808080;
    p->x0 = p->x2 = x + 0x18;
    p->x1 = p->x3 = x + 0x27;
    p->y0 = p->y1 = y - 8;
    p->y2 = p->y3      = y + 7;
    *(u_short *)&p->u0 = u | 0xF000;
    *(u_short *)&p->u1 = (u + 0xF) | 0xF000;
    *(u_short *)&p->u2 = u | 0xFF00;
    *(u_short *)&p->u3 = (u + 0xF) | 0xFF00;
    p->clut            = 0x3E80;
    AddPrim(&D_80098934->tag78, p);
}
