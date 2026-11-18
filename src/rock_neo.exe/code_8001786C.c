#include "common.h"
#include "code_8001786c.h"

void func_8001786C(void)
{
    sint32 i;

    for (i = 0; i < 32; i++)
    {
        if (D_80098868 & 1)
        {
            func_800176A4(&D_800AD168[i * 0x100], &D_800AD168[0x2000 + i * 0x100], 0x20);
        }
        D_80098868 >>= 1;
    }
}

void func_800178FC(void)
{
    LoadImage(&D_80097A28, (u_long *)D_800B1168);
    LoadImage(&D_80097A30, (u_long *)&D_800B1168[0x1000]);
}

void func_80017944(void)
{
    sint32 i;
    uint16 *pixel;
    uint16 color;
    uint32 transparent;

    i           = 0x2000;
    transparent = 0x8000;
    pixel       = D_800B1168;
    for (; i < 0x4000; i++, pixel++)
    {
        color = *pixel;
        if (color != 0)
        {
            if (color == transparent)
            {
                *pixel = 0;
            }
            else
            {
                *pixel = color | 0x8000;
            }
        }
    }
}

void func_80017994(void)
{
    func_800176DC(D_800AD168, D_80098B70, 8);
    func_800176DC(D_800AD168 + 0x80, D_80098B70 + 0x100, 8);
    func_800176DC(D_800AD168 + 0x980, D_80098B70 + 0x200, 8);
}

void func_800179FC(void)
{
    uint32 i, j;
    sint32 r, g, b;
    uint32 color;
    uint32 stp;
    sint32 timer;

    timer = Game_work.timer60;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 128;)
        {
            color = D_8008F168[(D_80097A3A[i].value << 8) + (j + D_80097A38[i].value)];
            r     = color & 31;
            g     = (color >> 5) & 31;
            b     = (color >> 10) & 31;
            stp   = color & 0x8000;
            if ((uint32)timer < 65)
            {
                if ((uint32)timer >= 33)
                {
                    r -= 8;
                    g -= 8;
                    b -= 8;
                }
                else
                {
                    r -= 18;
                    g -= 18;
                    b -= 18;
                }
                if (r < 0)
                {
                    r = 0;
                }
                if (g < 0)
                {
                    g = 0;
                }
                if (b < 0)
                {
                    b = 0;
                }
                color = stp | (b << 10) | (g << 5) | r;
            }
            D_8008F168[0x2000 + (j++ + D_80097A38[i].value) + (D_80097A3A[i].value << 8)] = color;
        }
    }
}

// The colour goes through setRGB0. Its (&tile[i])->field stores build the address as
// pointer arithmetic: combine folds those address pseudos away but leaves their reference
// counts, so each gets an unused 8-byte stack slot (retail's 24-byte leaf frame), and the
// changed RTL gives retail's index/mask register order.
void func_80017B24(void)
{
    if (CODE178_FADE_WORK.enabled != 0)
    {
        setRGB0(&D_80098A28[CODE800133D8_DISPLAY_INDEX], CODE178_FADE_WORK.value,
                CODE178_FADE_WORK.value, CODE178_FADE_WORK.value);
        addPrim(&D_80098934->tag74, &D_80098A28[CODE800133D8_DISPLAY_INDEX]);
        addPrim(&D_80098934->tag74, &D_80098A10[CODE800133D8_DISPLAY_INDEX]);
    }
}

// Each case is written out in full (retail's shared tails come from cross-jumping), and the
// fade fields go through CODE178_FADE_WORK so the table reads stay after the stores. The tile
// loop is written like func_8001326C's (main.c), which keeps the pointer unbiased.
void func_80017C30(sint32 arg)
{
    uint32 i;
    CODE178_TILE *tile;

    if (D_80098A72 == 0)
    {
        switch (arg)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 8:
            case 9:
            case 10:
            case 11:
                CODE178_FADE_WORK.routine_0 = 0;
                CODE178_FADE_WORK.terminate = D_80097A44[arg >> 3];
                CODE178_FADE_WORK.step      = D_80097A48[arg & 3];
                break;
            case 5:
            case 6:
            case 7:
            case 13:
            case 14:
            case 15:
                CODE178_FADE_WORK.routine_0 = 1;
                CODE178_FADE_WORK.terminate = D_80097A44[arg >> 3];
                CODE178_FADE_WORK.step      = D_80097A48[arg & 3];
                break;
            case 16:
            case 17:
            case 18:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_3           = arg - 16;
                CODE178_FADE_WORK.routine_1           = 0;
                CODE178_FADE_WORK.routine_2           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
            case 19:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_1           = 1;
                CODE178_FADE_WORK.routine_2           = 0;
                CODE178_FADE_WORK.routine_3           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
            case 20:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_1           = 2;
                CODE178_FADE_WORK.routine_2           = 0;
                CODE178_FADE_WORK.routine_3           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
            case 21:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_1           = 3;
                CODE178_FADE_WORK.routine_2           = 0;
                CODE178_FADE_WORK.routine_3           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
            case 22:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_1           = 4;
                CODE178_FADE_WORK.routine_2           = 0;
                CODE178_FADE_WORK.routine_3           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
            case 23:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_1           = 5;
                CODE178_FADE_WORK.routine_2           = 0;
                CODE178_FADE_WORK.routine_3           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
            default:
                CODE178_FADE_WORK.routine_0           = 2;
                CODE178_FADE_WORK.routine_1           = 0;
                CODE178_FADE_WORK.routine_2           = 0;
                CODE178_FADE_WORK.routine_3           = 0;
                *(uint32 *)&CODE178_FADE_WORK.flags04 = 0;
                D_80098A72                            = -1;
                break;
        }
        for (i = 0; i < 2; i++)
        {
            setlen(&D_80098A28[i], 3);
            setcode(&D_80098A28[i], 0x62);
            tile    = &D_80098A28[i];
            tile->w = 320;
            tile->x = 0;
            tile->y = 0;
            tile->h = 240;
            SetDrawMode(&D_80098A10[i], 0, 0,
                        GetTPage(2, 2 - (CODE178_FADE_WORK.routine_0 & 1), 0, 0), NULL);
        }
        func_80012E10(2, func_80017E94);
    }
}

void func_80017E94(void)
{
    D_80082140[D_80098A68]();
}

void func_80017ED0(void)
{
    CODE178_FADE *wp;

    wp = (CODE178_FADE *)&D_80098A68;
    if (D_80098A72 > 0)
    {
        D_80098A69 = 0;
        D_80098A76 = 255;
    }
    else
    {
        D_80098A69 = 1;
        D_80098A76 = 0;
    }
    wp->flags04 = 0;
    wp->enabled = 1;
    while (1)
    {
        switch (wp->routine_1)
        {
            case 0:
                if ((wp->value -= wp->step) <= 0)
                {
                    wp->value     = 0;
                    wp->routine_1 = 2;
                    wp->step      = GAME_SCRATCH_MODE;
                }
                break;
            case 1:
                if ((wp->value += wp->step) >= 256)
                {
                    wp->value     = 255;
                    wp->routine_1 = 2;
                    wp->step      = GAME_SCRATCH_MODE;
                }
                break;
            case 2:
                if (wp->step == 0)
                {
                    if (wp->terminate == 1)
                    {
                        wp->enabled = 0;
                    }
                    wp->terminate = 0;
                    func_80012ECC();
                }
                else
                {
                    wp->step--;
                }
                break;
        }
        Thread_wait(1);
    }
}

void func_80018050(void)
{
    while (1)
    {
        D_800821BC[D_800821E0[D_80098A69][D_80098A6A]]();
        Thread_wait(1);
    }
}

void func_800180D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (CODE800133D8_DISPLAY_INDEX != 0)
            {
                D_800C0C66 = 0;
                D_800C0C5E = 0;
                D_800C0C4A = 0;
                D_800C0C74 = 0;
                D_800C0C73 = 0;
                D_800C0CF6 = 0;
                D_800C0CEE = 0;
                D_800C0CDA = 0;
                D_800C0D04 = 0;
                D_800C0D03 = 0;
                MojiTaskKill();
                D_80098810 = 1;
                D_80098824 = 1;
                D_80098864 = 1;
                D_80098A6B++;
                func_800196A0();
            }
            break;
        case 1:
            D_80098A6B = 0;
            D_80098A6A++;
            break;
    }
}

void func_800181D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (CODE800133D8_DISPLAY_INDEX != 0)
            {
                D_800C0C66 = 0;
                D_800C0C5E = 0;
                D_800C0C4A = 0;
                D_800C0C74 = 0;
                D_800C0C73 = 0;
                D_800C0CF6 = 0;
                D_800C0CEE = 0;
                D_800C0CDA = 0;
                D_800C0D04 = 0;
                D_800C0D03 = 0;
                MojiTaskKill();
                D_80098810 = 1;
                D_80098824 = 1;
                D_80098864 = 1;
                D_80098A6B++;
                func_800196A0();
            }
            break;
        case 1:
            D_80098A6B = 0;
            D_80098A6A++;
            break;
    }
}

void func_800182D4(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (CODE800133D8_DISPLAY_INDEX == 0)
            {
                if (D_80098824 != 0)
                {
                    D_80098824 = 0;
                    D_80098864 = 0;
                }
            }
            else if (D_80098824 == 0)
            {
                D_800C0C66 = 0;
                D_800C0C5E = 0;
                D_800C0C4A = 256;
                D_800C0C74 = 1;
                D_800C0C72 = 0;
                D_800C0C73 = 1;
                D_800C0CF6 = 256;
                D_800C0CEE = 256;
                D_800C0CDA = 0;
                D_800C0D04 = 1;
                D_800C0D02 = 0;
                D_800C0D03 = 1;
                D_80098810 = 0;
                D_80098824 = 0;
                D_80098864 = 0;
                D_80098A6B++;
            }
            break;
        case 1:
            D_80098810 = 0;
            D_80098A72 = 0;
            func_80012ECC();
            break;
    }
}

void func_8001840C(void)
{
    switch (D_80098A6B)
    {
        case 0:
            if (CODE800133D8_DISPLAY_INDEX == 0)
            {
                if (D_80098824 != 0)
                {
                    D_80098824 = 0;
                }
            }
            else if (D_80098824 == 0)
            {
                D_800C0C66 = 0;
                D_800C0C5E = 0;
                D_800C0C4A = 256;
                D_800C0C74 = 1;
                D_800C0C72 = 0;
                D_800C0C73 = 1;
                D_800C0CF6 = 256;
                D_800C0CEE = 256;
                D_800C0CDA = 0;
                D_800C0D04 = 1;
                D_800C0D02 = 0;
                D_800C0D03 = 1;
                D_80098810 = 0;
                D_80098824 = 0;

                D_80098A6B++;
            }
            break;
        case 1:
            D_80098810 = 0;
            D_80098A72 = 0;
            func_80012ECC();
            break;
    }
}

void func_80018534(void)
{
    POLY_FT4 *prims;
    POLY_FT4 *p;
    sint32 i;
    uint32 color;
    uint32 tpage;
    sint32 frame;
    sint32 mode;
    sint32 scale;

    D_80098810 = 0;
    prims      = D_80098E70[CODE800133D8_DISPLAY_INDEX];
    frame      = D_80098A6C;
    mode       = D_80098A6B;
    if ((frame & 3) == 0)
    {
        color = D_80097A60[mode][0];
    }
    else
    {
        color = D_80097A60[mode][1];
    }
    tpage = D_80097A78[mode];
    scale = frame * 200 + 256;
    if (mode == 1)
    {
        func_80019760(160, 120, 0, scale);
    }
    else
    {
        func_80019760(160, 120, frame << 5, scale);
    }
    for (i = 0; i < 10; i++)
    {
        p                 = &prims[i];
        p->tag            = 0x09000000;
        *(uint32 *)&p->r0 = color;
        p->tpage          = (p->tpage & 0x7F) | tpage;
        p->clut           = GetClut(0, 0x1F0);
        p->x0             = D_80099190[CODE178_QUAD_CORNER(i, 0)].value;
        p->y0             = D_80099192[CODE178_QUAD_CORNER(i, 0)].value;
        p->x1             = D_80099190[CODE178_QUAD_CORNER(i, 1)].value;
        p->y1             = D_80099192[CODE178_QUAD_CORNER(i, 1)].value;
        p->x2             = D_80099190[CODE178_QUAD_CORNER(i, 2)].value;
        p->y2             = D_80099192[CODE178_QUAD_CORNER(i, 2)].value;
        p->x3             = D_80099190[CODE178_QUAD_CORNER(i, 3)].value;
        p->y3             = D_80099192[CODE178_QUAD_CORNER(i, 3)].value;
        addPrim(&D_80098934->tag78, p);
    }
    if (++D_80098A6C >= 64)
    {
        D_80098A70 = 1;
        D_80098A68 = 0;
        D_80098A6B = 0;
        D_80098A76 = 255;
        D_80098A6A++;
    }
}

// CODE178_FADE_WORK keeps case 1's field order; case 0's init loop has its own primitive
// pointer, so it stays block-local.
void func_80018850(void)
{
    sint32 j;
    sint32 i;
    uint8 index;
    POLY_G4 *g4;
    POLY_G4 *p;
    CODE800133D8_LINK *link;

    switch (CODE178_FADE_WORK.routine_3)
    {
        case 0:
            for (i = 0; i < 32; i++)
            {
                D_80099AD8[i].value = rcos(i << 7);
                D_80099ADA[i].value = rsin(i << 7);
            }
            for (j = 0; j < 2; j++)
            {
                for (i = 0; i < 32; i++)
                {
                    g4                 = &D_800991D8[j][i];
                    g4->tag            = 0x08000000;
                    *(uint32 *)&g4->r0 = 0x3AFFFFFF;
                    *(uint32 *)&g4->r1 = 0xFFFFFF;
                    *(uint32 *)&g4->r2 = 0;
                    *(uint32 *)&g4->r3 = 0;
                }
                SetDrawMode(&D_80098160[j], 1, 1, 0x140, NULL);
            }
            CODE178_FADE_WORK.routine_3++;
            break;
        case 1:
            D_80098810 = 0;
            j          = CODE178_FADE_WORK.flags04 * 4;
            link       = D_80098934;
            for (i = 0; i < 32; i++)
            {
                index = CODE800133D8_DISPLAY_INDEX;
                p     = D_800991D8[index] + i;
                p->x0 = 160;
                p->y0 = 120;
                p->x1 = 160;
                p->y1 = 120;
                p->x2 = ((D_80099AD8[i].value * j) >> 12) + 160;
                p->y2 = ((D_80099ADA[i].value * j) >> 12) + 120;
                p->x3 = ((D_80099AD8[(i + 1) & 0x1F].value * j) >> 12) + 160;
                p->y3 = ((D_80099ADA[(i + 1) & 0x1F].value * j) >> 12) + 120;
                addPrim(&link->tag78, p);
            }
            addPrim(&D_80098934->tag78, &D_80098160[index]);
            if (++CODE178_FADE_WORK.flags04 >= 64)
            {
                CODE178_FADE_WORK.enabled   = 1;
                CODE178_FADE_WORK.routine_0 = 0;
                CODE178_FADE_WORK.routine_3 = 0;
                CODE178_FADE_WORK.value     = 255;
                CODE178_FADE_WORK.routine_2++;
            }
            break;
    }
}

// CODE178_FADE_WORK fixes the timer reload order, and the cast tag plus word-view colours fix
// case 0's stores. Case 0's init loop has its own primitive pointer, and case 2 its own OT
// pointer, loaded after the counter in the for clause.
void func_80018BB8(void)
{
    sint32 i;
    sint32 j;
    sint32 outer;
    uint8 index;
    POLY_G4 *g4;
    POLY_G4 *p;
    CODE800133D8_LINK *link;
    CODE800133D8_LINK *ot;

    switch (CODE178_FADE_WORK.routine_3)
    {
        case 0:
            for (i = 0; i < 32; i++)
            {
                D_80099AD8[i].value = rcos(i << 7);
                D_80099ADA[i].value = rsin(i << 7);
            }
            for (j = 0; j < 2; j++)
            {
                for (i = 0; i < 32; i++)
                {
                    g4                             = &D_800991D8[j][i];
                    *(uint32 *)g4                  = 0x08000000;
                    ((CODE178_G4_WORDS *)g4)->rgb0 = 0x3A000000;
                    ((CODE178_G4_WORDS *)g4)->rgb1 = 0;
                    ((CODE178_G4_WORDS *)g4)->rgb2 = 0xFFFFFF;
                    ((CODE178_G4_WORDS *)g4)->rgb3 = 0xFFFFFF;
                }
                SetDrawMode(&D_80098160[j], 1, 1, 0x140, NULL);
            }
            CODE178_FADE_WORK.flags04 = 60;
            CODE178_FADE_WORK.routine_3++;
            break;
        case 1:
            D_80098810 = 0;
            j          = CODE178_FADE_WORK.flags04 * 4;
            link       = D_80098934;
            for (i = 0; i < 32; i++)
            {
                index = CODE800133D8_DISPLAY_INDEX;
                p     = &D_800991D8[index][i];
                p->x0 = ((D_80099AD8[i].value * j) >> 12) + 160;
                p->y0 = ((D_80099ADA[i].value * j) >> 12) + 120;
                p->x1 = ((D_80099AD8[(i + 1) & 0x1F].value * j) >> 12) + 160;
                p->y1 = ((D_80099ADA[(i + 1) & 0x1F].value * j) >> 12) + 120;
                p->x2 = ((D_80099AD8[i].value * 105) >> 11) + 160;
                p->y2 = ((D_80099ADA[i].value * 105) >> 11) + 120;
                p->x3 = ((D_80099AD8[(i + 1) & 0x1F].value * 105) >> 11) + 160;
                p->y3 = ((D_80099ADA[(i + 1) & 0x1F].value * 105) >> 11) + 120;
                addPrim(&link->tag78, p);
            }
            addPrim(&D_80098934->tag78, &D_80098160[index]);
            if (--CODE178_FADE_WORK.flags04 == 0)
            {
                CODE178_FADE_WORK.flags04 = 5;
                CODE178_FADE_WORK.routine_3++;
            }
            break;
        case 2:
            if (--CODE178_FADE_WORK.flags04 == 0)
            {
                CODE178_FADE_WORK.enabled   = 1;
                CODE178_FADE_WORK.routine_0 = 0;
                CODE178_FADE_WORK.routine_3 = 0;
                CODE178_FADE_WORK.value     = 255;
                CODE178_FADE_WORK.routine_2++;
            }
            j     = CODE178_FADE_WORK.flags04 * 4;
            outer = CODE178_FADE_WORK.flags04 * 16 + 16;
            for (i = 0, ot = D_80098934; i < 32; i++)
            {
                index = CODE800133D8_DISPLAY_INDEX;
                p     = &D_800991D8[index][i];
                p->x0 = ((D_80099AD8[i].value * j) >> 12) + 160;
                p->y0 = ((D_80099ADA[i].value * j) >> 12) + 120;
                p->x1 = ((D_80099AD8[(i + 1) & 0x1F].value * j) >> 12) + 160;
                p->y1 = ((D_80099ADA[(i + 1) & 0x1F].value * j) >> 12) + 120;
                p->x2 = ((D_80099AD8[i].value * outer) >> 12) + 160;
                p->y2 = ((D_80099ADA[i].value * outer) >> 12) + 120;
                p->x3 = ((D_80099AD8[(i + 1) & 0x1F].value * outer) >> 12) + 160;
                p->y3 = ((D_80099ADA[(i + 1) & 0x1F].value * outer) >> 12) + 120;
                addPrim(&ot->tag78, p);
            }
            addPrim(&D_80098934->tag78, &D_80098160[index]);
            break;
    }
}

// Fade fields through CODE178_FADE_WORK (one struct, so GCC reloads the counter after the
// addPrim stores as retail does). Case 1 reuses i for the band height, and case 0 has its own
// primitive pointer.
void func_80019210(void)
{
    sint32 i, j;
    POLY_G4 *g4;
    POLY_G4 *p;
    uint32 index;
    CODE800133D8_LINK *link;

    switch (CODE178_FADE_WORK.routine_3)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    g4                 = &D_800991D8[i][j];
                    g4->tag            = 0x08000000;
                    *(uint32 *)&g4->r0 = 0x3A000000;
                    *(uint32 *)&g4->r1 = 0;
                    *(uint32 *)&g4->r2 = 0x00303030;
                    *(uint32 *)&g4->r3 = 0x00303030;
                }
                SetDrawMode(&D_80098160[i], 1, 1, 0x140, NULL);
            }
            CODE178_FADE_WORK.flags04 = 60;
            CODE178_FADE_WORK.routine_3++;
            break;
        case 1:
            index      = CODE800133D8_DISPLAY_INDEX;
            link       = D_80098934;
            D_80098810 = 0;
            p          = &D_800991D8[index][0];
            i          = (60 - CODE178_FADE_WORK.flags04) * 3;
            p->x0      = 0;
            p->y0      = i;
            p->x1      = 320;
            p->y1      = i;
            p->x2      = 0;
            p->y2      = 0;
            p->x3      = 320;
            p->y3      = 0;
            addPrim(&link->tag78, p);
            p     = &D_800991D8[index][1];
            p->y0 = 240 - i;
            p->y1 = 240 - i;
            p->x0 = 0;
            p->x1 = 320;
            p->x2 = 0;
            p->y2 = 240;
            p->x3 = 320;
            p->y3 = 240;
            addPrim(&link->tag78, p);
            addPrim(&link->tag78, &D_80098160[index]);
            if (--CODE178_FADE_WORK.flags04 == 0)
            {
                CODE178_FADE_WORK.enabled   = 1;
                CODE178_FADE_WORK.routine_0 = 0;
                CODE178_FADE_WORK.routine_3 = 0;
                CODE178_FADE_WORK.value     = 255;
                CODE178_FADE_WORK.routine_2++;
            }
            break;
    }
}

void func_800194C4(void)
{
    sint32 i;
    CODE178_TILE *tile;
    uint32 index;
    CODE800133D8_LINK *link;

    switch (CODE178_FADE_WORK.routine_3)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                tile                 = &D_80098178[i];
                tile->tag            = 0x03000000;
                *(uint32 *)&tile->r0 = 0x62080808;
                *(uint32 *)&tile->x  = 0;
                *(uint32 *)&tile->w  = 0x00F00140;
                SetDrawMode(&D_80098160[i], 1, 1, 0x140, NULL);
            }
            CODE178_FADE_WORK.flags04 = 63;
            CODE178_FADE_WORK.routine_3++;
            break;
        case 1:
            index = CODE800133D8_DISPLAY_INDEX;
            link  = D_80098934;
            addPrim(&link->tag78, &D_80098178[index]);
            addPrim(&link->tag78, &D_80098160[index]);
            D_80098810 = 0;
            if (--CODE178_FADE_WORK.flags04 == 0)
            {
                CODE178_FADE_WORK.enabled   = 1;
                CODE178_FADE_WORK.routine_0 = 0;
                CODE178_FADE_WORK.routine_3 = 0;
                CODE178_FADE_WORK.value     = 255;
                CODE178_FADE_WORK.routine_2++;
            }
            break;
    }
}

void func_800196A0(void)
{
    sint32 i, j;
    sint32 v, page;
    POLY_FT4 *p;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 10; j++)
        {
            p = &D_80098E70[i][j];
            if (j < 5)
            {
                v    = 0;
                page = j;
            }
            else
            {
                v    = 119;
                page = j - 5;
            }
            p->tpage = page;
            if (page == 4)
            {
                p->u0 = 0;
                p->v0 = v;
                p->u1 = 63;
                p->v1 = v;
                p->u2 = 0;
                p->v2 = v + 120;
                p->u3 = 63;
                p->v3 = v + 120;
            }
            else
            {
                p->u0 = 0;
                p->v0 = v;
                p->u1 = 64;
                p->v1 = v;
                p->u2 = 0;
                p->v2 = v + 120;
                p->u3 = 64;
                p->v3 = v + 120;
            }
        }
    }
}

void func_80019760(sint16 x, sint16 y, sint16 angle, sint16 scale)
{
    sint32 i;
    sint32 trig, trig2;
    sint32 dx, dy;

    for (i = 0; i < 18; i++)
    {
        dx                  = D_8008214C[i].value - x;
        dy                  = D_8008214E[i].value - y;
        trig                = rcos(angle);
        D_80099190[i].value = x + ((scale * ((dx * trig - dy * rsin(angle)) >> 8)) >> 16);
        trig2               = rsin(angle);
        D_80099192[i].value = y + ((scale * ((dx * trig2 + dy * rcos(angle)) >> 8)) >> 16);
    }
}
