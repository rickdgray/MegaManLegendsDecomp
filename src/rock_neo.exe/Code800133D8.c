#include "common.h"
#include "code_800133d8.h"
#include "system.h"
#include "psyq/libgpu.h"

void func_800133D8(void)
{
    *(uint32 *)&Code800133D8_work                = 0;
    *(uint32 *)((uint8 *)&Code800133D8_work + 4) = 0;
    *(uint32 *)((uint8 *)&Code800133D8_work + 8) = 0;
    func_80012F78(func_80013420);
}

void func_80013418(void)
{
}

void func_80013420(void)
{
    CODE800133D8_STATE *wp;

    wp                                       = &Code800133D8_work;
    CODE800133D8_SCRATCH_MODE                = 2;
    *(uint32 *)&Code800133D8_work.menu_index = 0;
    Game_work.flags_52                       = 0;
    Game_work.flags_53                       = 0;
    Game_work.flags_82                       = 0;
    func_8005C258();
    Cd_read_comb(20);
    func_8001D888(1);
    func_80019FB4();
    MojiTaskKill();
    func_80063BA8();
    func_80063EF0();
    func_80017994();
    while (1)
    {
        if ((sint8)wp->routine_0 == 2 && (D_800C0C2A & 0x4008))
        {
            Sound_call(0x82, 1, 0);
            if (D_80098A72 > 0 || (D_80098A72 == 0 && D_80098A70 == 0))
            {
                wp->routine_1 = 1;
            }
            else
            {
                wp->routine_1 = 0;
            }
            wp->routine_0 = 4;
        }
        Code800133D8_main_tbl[(sint8)wp->routine_0](wp);
        func_80031AA4();
        Thread_wait(1);
    }
}

// Each arm sets both routine bytes; cross-jumping merges the shared routine_51 store after
// scheduling, which keeps retail's order (one shared store after the join is scheduled earlier).
void func_80013578(CODE800133D8_STATE *wp)
{
    wp->routine_3 ^= 1;
    if (wp->routine_3 != 0)
    {
        Game_work.routine_50 = 1;
        Game_work.routine_51 = 0;
    }
    else
    {
        Game_work.routine_50 = 7;
        Game_work.routine_51 = 0;
    }
    Game_work.flags_82 = -128;
    func_80012F78(func_800155A4);
}

void func_800135DC(CODE800133D8_STATE *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                D_80098810 = 1;
                D_80098864 = 0;
                func_8002E7A8(1);
                func_8003697C();
                func_8002CFA4();
                func_800371A0(D_800808D0, D_800808A8);
                *CODE800133D8_SCRATCH_TABLE = D_800808A4;
                wp->routine_1++;
            }
            break;
        case 1:
            D_80098810  = 0;
            wp->value0a = 0;
            func_80015428(wp);
            func_80017C30(2);
            wp->routine_0 = 2;
            wp->routine_1 = 1;
            break;
    }
}

void func_800136B8(CODE800133D8_STATE *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                break;
            }
            func_80017C30(2);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            wp->timer = 900;
            wp->routine_1++;
            func_80013FB8();
            break;
        case 2:
            func_80013FB8();
            func_80013F60(wp);
            break;
        case 3:
            func_80013FB8();
            func_80014394();
            if (--wp->timer == 0)
            {
                wp->routine_1++;
                func_80017C30(10);
            }
            break;
        case 4:
            MojiTaskKill();
            func_80013FB8();
            func_80013F8C(wp);
            break;
    }
}

void func_800137D4(void)
{
    sint32 index;
    CODE800133D8_LINK *link;

    func_800175D8();
    func_80015428(&Code800133D8_work);
    func_80016FD4();
    func_80038370(D_800979DC, D_800979EC);
    func_800175FC();
    func_80028DE0();
    index = CODE800133D8_DISPLAY_INDEX;
    link  = D_80098934;
    setaddr(D_800A4D40[index], getaddr(&link->tag));
    setaddr(&link->tag, &D_800A4D40[index][0x1000] - 1);
}

void func_80013890(CODE800133D8_STATE *wp)
{
    wp->routine_0 = 0;
    wp->routine_1 = 0;
}

void func_8001389C(CODE800133D8_STATE *wp)
{
    GAME_WORK *gp;

    gp = &Game_work;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                break;
            }
            func_80017C30(1);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            wp->timer = 900;
            wp->routine_1++;
            gp->routine_50 = 0;
            gp->routine_51 = 0;
            func_80013FB8();
            func_8001456C(wp->menu_index);
            break;
        case 2:
            func_80013FB8();
            func_8001456C(wp->menu_index);
            func_80013F60(wp);
            break;
        case 3:
            func_80013FB8();
            func_8001456C(wp->menu_index);
            if ((D_800C0C2A & 0x10) && wp->menu_index > 0)
            {
                Sound_call(0x81, 1, 0);
                wp->menu_index--;
                break;
            }
            if ((D_800C0C2A & 0x40) && wp->menu_index < (gp->flags_18 != 0 ? 3 : 2))
            {
                Sound_call(0x81, 1, 0);
                wp->menu_index++;
                break;
            }
            if ((D_800C0C2A & 0x80) && wp->menu_index == 3)
            {
                Sound_call(0x81, 1, 0);
                if (--gp->option_5b < (gp->flags_1a != 0 ? 0 : 1))
                {
                    gp->option_5b = 2;
                }
            }
            if ((D_800C0C2A & 0x20) && wp->menu_index == 3)
            {
                Sound_call(0x81, 1, 0);
                if (++gp->option_5b >= 3)
                {
                    if (gp->flags_1a != 0)
                    {
                        gp->option_5b = 0;
                    }
                    else
                    {
                        gp->option_5b = 1;
                    }
                }
            }
            if (D_800C0C2A & 0x4008)
            {
                switch (wp->menu_index)
                {
                    case 0:
                        wp->routine_1 += 2;
                        func_80017C30(22);
                        Sound_call(0xA6, 0, 0);
                        break;
                    case 1:
                        wp->routine_0 = 5;
                        wp->routine_1 = 0;
                        func_80017C30(9);
                        Sound_call(0xA7, 0, 0);
                        break;
                    case 2:
                        wp->routine_0 = 6;
                        wp->routine_1 = 0;
                        func_80017C30(9);
                        Sound_call(0xA8, 0, 0);
                        break;
                    case 3:
                        if (++gp->option_5b >= 3)
                        {
                            if (gp->flags_1a != 0)
                            {
                                gp->option_5b = 0;
                            }
                            else
                            {
                                gp->option_5b = 1;
                            }
                        }
                        Sound_call(0x81, 1, 0);
                        break;
                }
            }
            else if (D_800C0C2A & 0x1000)
            {
                Sound_call(0x83, 1, 0);
                wp->flags_0e  = 1;
                wp->routine_0 = 2;
                wp->routine_1 = 1;
            }
            break;
        case 5:
            func_80013FB8();
            func_8001456C(wp->menu_index);
            MojiTaskKill();
            Game_work.flags_82 = 0;
            func_80012F78(func_800155A4);
            break;
    }
}

void func_80013CA0(CODE800133D8_STATE *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                func_80013FB8();
                func_8001456C(wp->menu_index);
                break;
            }
            func_80017C30(1);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            wp->timer = 900;
            wp->routine_1++;
            break;
        case 2:
            D_800C0C2A = 0;
            D_800C0C26 = 0;
            func_800665FC(0);
            func_800137D4();
            func_80013F60(wp);
            break;
        case 3:
            wp->routine_1 += func_800665FC(0);
            func_800137D4();
            break;
        case 4:
            if (Game_work.flags_82 == 1)
            {
                func_80017C30(22);
                Sub_screen_back_ground_set();
                func_80012F78(func_800155A4);
            }
            else
            {
                func_80017C30(9);
                func_800137D4();
                wp->routine_0 = 4;
                wp->routine_1 = 0;
            }
            break;
    }
    Sub_screen_back_ground_set();
}

void func_80013E0C(CODE800133D8_STATE *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                func_80013FB8();
                func_8001456C(wp->menu_index);
                break;
            }
            func_80017C30(1);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            MojiTaskExec(0, D_8008CB64[0], -1);
            wp->timer = 900;
            wp->routine_1++;
            func_800137D4();
            break;
        case 2:
            if ((Moji_flag & 0x40000000) || (D_800C0C2A & 8))
            {
                if (D_800C0C2A & 8)
                {
                    Sound_call(0x83, 1, 0);
                }
                func_80017C30(9);
                wp->routine_0 = 4;
                wp->routine_1 = 0;
            }
            func_800137D4();
            break;
    }
    Sub_screen_back_ground_set();
}

void func_80013F60(CODE800133D8_STATE *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_1++;
    }
}

void func_80013F8C(CODE800133D8_STATE *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_1 = 0;
        wp->routine_0++;
    }
}

void func_80013FB8(void)
{
    POLY_FT4 *prim;

    prim = *CODE800133D8_PACKET_PTR;
    setPolyFT4(prim);
    prim->tpage = GetTPage(1, 0, 0x140, 0x100);
    prim->clut  = GetClut(0, 0x1F0);
    prim->x0    = 0x20;
    prim->y0    = 8;
    prim->x1    = 0x11F;
    prim->y1    = 8;
    prim->x2    = 0x20;
    prim->y2    = 0xA8;
    prim->x3    = 0x11F;
    prim->y3    = 0xA8;
    prim->u0    = 0;
    prim->v0    = 0;
    prim->u1    = 0xFF;
    prim->v1    = 0;
    prim->u2    = 0;
    prim->v2    = 0xA0;
    prim->u3    = 0xFF;
    prim->v3    = 0xA0;
    prim->r0    = 0x80;
    prim->g0    = 0x80;
    prim->b0    = 0x80;
    prim->code &= 0xFD;
    AddPrim(D_800A4F50[CODE800133D8_DISPLAY_INDEX], prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(1, 2, 0x240, 0x100);
    prim->clut  = GetClut(0, 0x1F2);
    prim->x0    = 0;
    prim->y0    = 0;
    prim->x1    = 0xA0;
    prim->y1    = 0;
    prim->x2    = 0;
    prim->y2    = 0xA0;
    prim->x3    = 0xA0;
    prim->y3    = 0xA0;
    prim->u0    = 0;
    prim->v0    = 0;
    prim->u1    = 0xA0;
    prim->v1    = 0;
    prim->u2    = 0;
    prim->v2    = 0xA0;
    prim->u3    = 0xA0;
    prim->v3    = 0xA0;
    prim->r0    = 0x80;
    prim->g0    = 0x80;
    prim->b0    = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag8c, prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(1, 2, 0x240, 0x100);
    prim->clut  = GetClut(0, 0x1F2);
    prim->x0    = 0xA0;
    prim->y0    = 0;
    prim->x1    = 0x140;
    prim->y1    = 0;
    prim->x2    = 0xA0;
    prim->y2    = 0xA0;
    prim->x3    = 0x140;
    prim->y3    = 0xA0;
    prim->u0    = 0xA0;
    prim->v0    = 0;
    prim->u1    = 0;
    prim->v1    = 0;
    prim->u2    = 0xA0;
    prim->v2    = 0xA0;
    prim->u3    = 0;
    prim->v3    = 0xA0;
    prim->r0    = 0x80;
    prim->g0    = 0x80;
    prim->b0    = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag8c, prim);
    prim++;
    setPolyG4((POLY_G4 *)prim);
    ((POLY_G4 *)prim)->x0 = 0;
    ((POLY_G4 *)prim)->y0 = 0x90;
    ((POLY_G4 *)prim)->x1 = 0x140;
    ((POLY_G4 *)prim)->y1 = 0x90;
    ((POLY_G4 *)prim)->x2 = 0;
    ((POLY_G4 *)prim)->y2 = 0xA0;
    ((POLY_G4 *)prim)->x3 = 0x140;
    ((POLY_G4 *)prim)->y3 = 0xA0;
    ((POLY_G4 *)prim)->r0 = 0;
    ((POLY_G4 *)prim)->g0 = 0;
    ((POLY_G4 *)prim)->b0 = 0;
    ((POLY_G4 *)prim)->r1 = 0;
    ((POLY_G4 *)prim)->g1 = 0;
    ((POLY_G4 *)prim)->b1 = 0;
    ((POLY_G4 *)prim)->r2 = 0xFF;
    ((POLY_G4 *)prim)->g2 = 0xFF;
    ((POLY_G4 *)prim)->b2 = 0xFF;
    ((POLY_G4 *)prim)->r3 = 0xFF;
    ((POLY_G4 *)prim)->g3 = 0xFF;
    ((POLY_G4 *)prim)->b3 = 0xFF;
    ((POLY_G4 *)prim)->code |= 2;
    AddPrim(&D_80098934->tag88, prim);
    prim++;
    SetDrawMode((DR_MODE *)prim, 0, 0, GetTPage(1, 2, 0, 0) & 0xFFFF, NULL);
    AddPrim(&D_80098934->tag88, prim);
    prim++;
    setPolyG4((POLY_G4 *)prim);
    ((POLY_G4 *)prim)->x0 = 0;
    ((POLY_G4 *)prim)->y0 = 0xA2;
    ((POLY_G4 *)prim)->x1 = 0x140;
    ((POLY_G4 *)prim)->y1 = 0xA2;
    ((POLY_G4 *)prim)->x2 = 0;
    ((POLY_G4 *)prim)->y2 = 0xF0;
    ((POLY_G4 *)prim)->x3 = 0x140;
    ((POLY_G4 *)prim)->y3 = 0xF0;
    ((POLY_G4 *)prim)->r0 = 0;
    ((POLY_G4 *)prim)->g0 = 0;
    ((POLY_G4 *)prim)->b0 = 0;
    ((POLY_G4 *)prim)->r1 = 0;
    ((POLY_G4 *)prim)->g1 = 0;
    ((POLY_G4 *)prim)->b1 = 0;
    ((POLY_G4 *)prim)->r2 = 0xC0;
    ((POLY_G4 *)prim)->g2 = 0xFF;
    ((POLY_G4 *)prim)->b2 = 0xE0;
    ((POLY_G4 *)prim)->r3 = 0xC0;
    ((POLY_G4 *)prim)->g3 = 0xFF;
    ((POLY_G4 *)prim)->b3 = 0xE0;
    ((POLY_G4 *)prim)->code &= 0xFD;
    AddPrim(&D_80098934->tag8c, prim);
    prim++;
    *CODE800133D8_PACKET_PTR = prim;
    func_800137D4();
}

void func_80014394(void)
{
    POLY_FT4 *prim;

    prim = *CODE800133D8_PACKET_PTR;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 0x140, 0x100);
    prim->clut  = GetClut(0, 0x1F1);
    prim->x0    = 0x38;
    prim->y0    = 0xB0;
    prim->x1    = 0x108;
    prim->y1    = 0xB0;
    prim->x2    = 0x38;
    prim->y2    = 0xC0;
    prim->x3    = 0x108;
    prim->y3    = 0xC0;
    prim->u0    = 0;
    prim->v0    = 0xA0;
    prim->u1    = 0xD0;
    prim->v1    = 0xA0;
    prim->u2    = 0;
    prim->v2    = 0xB0;
    prim->u3    = 0xD0;
    prim->v3    = 0xB0;
    prim->r0    = 0x80;
    prim->g0    = 0x80;
    prim->b0    = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag78, prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 0x140, 0x100);
    prim->clut  = GetClut(0, 0x1F1);
    prim->x0    = 0x20;
    prim->y0    = 0xD0;
    prim->x1    = 0x120;
    prim->y1    = 0xD0;
    prim->x2    = 0x20;
    prim->y2    = 0xE8;
    prim->x3    = 0x120;
    prim->y3    = 0xE8;
    prim->u0    = 0;
    prim->v0    = 0xB0;
    prim->u1    = 0xFF;
    prim->v1    = 0xB0;
    prim->u2    = 0;
    prim->v2    = 0xC8;
    prim->u3    = 0xFF;
    prim->v3    = 0xC8;
    prim->r0    = 0x80;
    prim->g0    = 0x80;
    prim->b0    = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag78, prim);
    prim++;
    *CODE800133D8_PACKET_PTR = prim;
}

// The menu-cursor clut x is set to clut + 1 before the test and scaled in each arm, which gives
// retail's per-arm sll (a ternary or a single scaled if/else shares one shift).
void func_8001456C(sint32 arg0)
{
    sint32 clut;
    sint32 clut_x;
    POLY_FT4 *prim;

    prim                 = *CODE800133D8_PACKET_PTR;
    ((P_TAG *)prim)->len = 9;
    prim->code           = 0x2C;
    prim->tpage          = GetTPage(0, 0, 0x140, 0x100);
    prim->clut           = GetClut(arg0 == 0 ? 0x20 : 0x10, 0x1F1);
    prim->x0             = 0x68;
    prim->y0             = 0x94;
    prim->x1             = 0xD8;
    prim->y1             = 0x94;
    prim->x2             = 0x68;
    prim->y2             = 0xA4;
    prim->x3             = 0xD8;
    prim->y3             = 0xA4;
    prim->u0             = 0;
    prim->v0             = 0xC8;
    prim->u1             = 0x70;
    prim->v1             = 0xC8;
    prim->u2             = 0;
    prim->v2             = 0xD8;
    prim->u3             = 0x70;
    prim->v3             = 0xD8;
    prim->r0             = 0x80;
    prim->g0             = 0x80;
    prim->b0             = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag78, prim);
    prim++;
    ((P_TAG *)prim)->len = 9;
    prim->code           = 0x2C;
    prim->tpage          = GetTPage(0, 0, 0x140, 0x100);
    prim->clut           = GetClut(arg0 == 1 ? 0x20 : 0x10, 0x1F1);
    prim->x0             = 0x68;
    prim->y0             = 0xA4;
    prim->x1             = 0xD8;
    prim->y1             = 0xA4;
    prim->x2             = 0x68;
    prim->y2             = 0xB4;
    prim->x3             = 0xD8;
    prim->y3             = 0xB4;
    prim->u0             = 0x70;
    prim->v0             = 0xC8;
    prim->u1             = 0xE0;
    prim->v1             = 0xC8;
    prim->u2             = 0x70;
    prim->v2             = 0xD8;
    prim->u3             = 0xE0;
    prim->v3             = 0xD8;
    prim->r0             = 0x80;
    prim->g0             = 0x80;
    prim->b0             = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag78, prim);
    prim++;
    ((P_TAG *)prim)->len = 9;
    prim->code           = 0x2C;
    prim->tpage          = GetTPage(0, 0, 0x140, 0x100);
    prim->clut           = GetClut(arg0 == 2 ? 0x20 : 0x10, 0x1F1);
    prim->x0             = 0x78;
    prim->y0             = 0xB4;
    prim->x1             = 0xC8;
    prim->y1             = 0xB4;
    prim->x2             = 0x78;
    prim->y2             = 0xC4;
    prim->x3             = 0xC8;
    prim->y3             = 0xC4;
    prim->u0             = 0;
    prim->v0             = 0xD8;
    prim->u1             = 0x50;
    prim->v1             = 0xD8;
    prim->u2             = 0;
    prim->v2             = 0xE8;
    prim->u3             = 0x50;
    prim->v3             = 0xE8;
    prim->r0             = 0x80;
    prim->g0             = 0x80;
    prim->b0             = 0x80;
    prim->code &= 0xFD;
    AddPrim(&D_80098934->tag78, prim);
    prim++;
    if (Game_work.flags_18 != 0)
    {
        ((P_TAG *)prim)->len = 9;
        prim->code           = 0x2C;
        prim->tpage          = GetTPage(0, 0, 0x140, 0x100);
        clut                 = (Game_work.option_5b + 1) * 2;
        clut_x               = clut + 1;
        if (arg0 != 3)
        {
            clut_x = (clut + 2) * 16;
        }
        else
        {
            clut_x *= 16;
        }
        prim->clut = GetClut(clut_x, 0x1F1);
        prim->r0   = 0x80;
        prim->g0   = 0x80;
        prim->b0   = 0x80;
        prim->code &= 0xFD;
        switch (Game_work.option_5b)
        {
            case 0:
                prim->x0 = 0x84;
                prim->y0 = 0xC4;
                prim->x1 = 0xBC;
                prim->y1 = 0xC4;
                prim->x2 = 0x84;
                prim->y2 = 0xD4;
                prim->x3 = 0xBC;
                prim->y3 = 0xD4;
                prim->u0 = 0x50;
                prim->v0 = 0xD8;
                prim->u1 = 0x88;
                prim->v1 = 0xD8;
                prim->u2 = 0x50;
                prim->v2 = 0xE8;
                prim->u3 = 0x88;
                prim->v3 = 0xE8;
                break;
            case 1:
                prim->x0 = 0x78;
                prim->y0 = 0xC4;
                prim->x1 = 0xC8;
                prim->y1 = 0xC4;
                prim->x2 = 0x78;
                prim->y2 = 0xD4;
                prim->x3 = 0xC8;
                prim->y3 = 0xD4;
                prim->u0 = 0x88;
                prim->v0 = 0xD8;
                prim->u1 = 0xD8;
                prim->v1 = 0xD8;
                prim->u2 = 0x88;
                prim->v2 = 0xE8;
                prim->u3 = 0xD8;
                prim->v3 = 0xE8;
                break;
            case 2:
                prim->x0 = 0x84;
                prim->y0 = 0xC4;
                prim->x1 = 0xBC;
                prim->y1 = 0xC4;
                prim->x2 = 0x84;
                prim->y2 = 0xD4;
                prim->x3 = 0xBC;
                prim->y3 = 0xD4;
                prim->u0 = 0;
                prim->v0 = 0xE8;
                prim->u1 = 0x38;
                prim->v1 = 0xE8;
                prim->u2 = 0;
                prim->v2 = 0xF8;
                prim->u3 = 0x38;
                prim->v3 = 0xF8;
                break;
        }
        AddPrim(&D_80098934->tag78, prim);
        prim++;
    }
    ((POLY_F4 *)prim)->code = 0x28;
    ((P_TAG *)prim)->len    = 5;
    ((POLY_F4 *)prim)->r0   = 0;
    ((POLY_F4 *)prim)->g0   = 0;
    ((POLY_F4 *)prim)->b0   = 0;
    ((POLY_F4 *)prim)->code |= 2;
    if (Game_work.flags_18 != 0)
    {
        ((POLY_F4 *)prim)->x0 = 0x60;
        ((POLY_F4 *)prim)->y0 = 0x90;
        ((POLY_F4 *)prim)->x1 = 0xE0;
        ((POLY_F4 *)prim)->y1 = 0x90;
        ((POLY_F4 *)prim)->x2 = 0x60;
        ((POLY_F4 *)prim)->y2 = 0xD8;
        ((POLY_F4 *)prim)->x3 = 0xE0;
        ((POLY_F4 *)prim)->y3 = 0xD8;
    }
    else
    {
        ((POLY_F4 *)prim)->x0 = 0x60;
        ((POLY_F4 *)prim)->y0 = 0x90;
        ((POLY_F4 *)prim)->x1 = 0xE0;
        ((POLY_F4 *)prim)->y1 = 0x90;
        ((POLY_F4 *)prim)->x2 = 0x60;
        ((POLY_F4 *)prim)->y2 = 0xC8;
        ((POLY_F4 *)prim)->x3 = 0xE0;
        ((POLY_F4 *)prim)->y3 = 0xC8;
    }
    AddPrim(&D_80098934->tag78, prim);
    prim++;
    *CODE800133D8_PACKET_PTR = prim;
}
