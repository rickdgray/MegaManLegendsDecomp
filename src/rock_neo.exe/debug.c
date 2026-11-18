#include "common.h"
#include "game.h"
#include "debug.h"
#include "code_800133d8.h"
#include "code_8001786c.h"
#include "cd.h"

// Small data reached through $gp
uint32 D_80098700;

void func_800629E0(void)
{
    *(uint32 *)&Debug_work.routine_0 = 0;
}

void func_800629F0(void)
{
    DEBUG_WORK *wp;

    wp               = &Debug_work;
    Debug_work.pad_4 = D_800C0C2A;
    Debug_work.pad_6 = D_800C0C26;
    D_8008DBD4[Debug_work.mode_8](wp);
}

sint32 func_80062A50(DEBUG_WORK *wp)
{
    sint32 i;

    *(uint32 *)&wp->routine_0        = 0;
    *(uint32 *)&wp->mode_8           = 0;
    *(uint32 *)&wp->sel_c            = 0;
    *(uint32 *)&wp->entry[0].state_0 = 0;
    *(uint32 *)&wp->entry[1].state_0 = 0;
    *(uint32 *)&wp->entry[2].state_0 = 0;
    *(uint32 *)&wp->entry[3].state_0 = 0;
    *(uint32 *)&wp->entry[4].state_0 = 0;
    for (i = 0; i < 5; i++)
    {
        D_8008DBE0[i](wp);
    }
    wp->mode_8 = 1;
    MojiTaskExec(0, D_8008CACC, -1);
    MojiTaskExec(1, D_8008CAD0, -1);
    return 0;
}

sint32 func_80062B04(DEBUG_WORK *wp)
{
    sint32 i;

    switch (wp->pad_4)
    {
        case 8:
        case 0x4000:
            wp->mode_8 = 2;
            wp->pad_4  = 0;
            break;
        case 0x20:
            wp->sel_9++;
            if (wp->sel_9 >= 5)
            {
                wp->sel_9 = 0;
            }
            goto check;
        case 0x80:
            wp->sel_9--;
            if (wp->sel_9 < 0)
            {
                wp->sel_9 = 4;
            }
        check:
            switch (wp->sel_9)
            {
                case 1:
                    wp->entry[0].state_0 = 2;
                    break;
                case 0:
                    wp->entry[1].state_0 = 2;
                    break;
                case 2:
                    wp->entry[2].state_0 = 2;
                    break;
                case 3:
                    wp->entry[3].state_0 = 2;
                    break;
                default:
                    break;
            }
            break;
    }
    wp->sel_c = wp->sel_9;
    for (i = 0; i < 5; i++)
    {
        D_8008DBE0[i](wp);
    }
    return 0;
}

sint32 func_80062C6C(DEBUG_WORK *wp)
{
    sint32 i;

    *(uint32 *)&wp->routine_0 = 0;
    *(uint32 *)&wp->mode_8    = 0;
    *(uint32 *)&wp->sel_c     = 0;
    wp->entry[0].state_0      = 3;
    wp->entry[1].state_0      = 3;
    wp->entry[2].state_0      = 3;
    wp->entry[3].state_0      = 3;
    wp->entry[4].state_0      = 3;
    for (i = 0; i < 5; i++)
    {
        D_8008DBE0[i](wp);
    }
    return 1;
}

sint32 func_80062CF0(DEBUG_WORK *wp)
{
    DEBUG_ENTRY *e;
    sint32 i;
    sint16 idx;
    uint8 *pl;

    pl = (uint8 *)&Player_work;
    e  = &wp->entry[0];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 14; i++)
            {
                D_8008DBF4[i].flags &= 0xFFFBFFFF;
            }
            e->index_6 = (sint8)pl[0x170];
            D_8008DBF4[(sint16)e->index_6].flags |= 0x40000;
            // fall through
        case 2:
            if (wp->value_d >= 14)
            {
                e->value_4 = 13;
            }
            else
            {
                e->value_4 = wp->value_d;
            }
            e->state_0 = 1;
            // fall through
        case 1:
            for (i = 13; i >= 0; i--)
            {
                D_8008DBF4[i].text[0] = 0x20;
            }
            if (wp->sel_c == 1)
            {
                if (wp->pad_4 & 0x2000)
                {
                    D_8008DBF4[e->index_6].flags &= 0xFFFBFFFF;
                    D_8008DBF4[e->value_4].flags |= 0x40000;
                    e->index_6 = e->value_4;
                    D_80098700 = 0;
                }
                else if (wp->pad_4 & 0x10)
                {
                    e->value_4--;
                    D_80098700 = 0;
                }
                else if ((*(uint32 *)&wp->pad_4 & 0x100010) == 0x100000)
                {
                    if (D_80098700 >= 0x10)
                    {
                        e->value_4--;
                    }
                    else
                    {
                        D_80098700++;
                    }
                }
                else if (wp->pad_4 & 0x40)
                {
                    e->value_4++;
                    D_80098700 = 0;
                }
                else if ((*(uint32 *)&wp->pad_4 & 0x400040) == 0x400000)
                {
                    if (D_80098700 >= 0x10)
                    {
                        e->value_4++;
                    }
                    else
                    {
                        D_80098700++;
                    }
                }
                if (e->value_4 < 0)
                {
                    e->value_4 = 13;
                }
                if (e->value_4 >= 14)
                {
                    e->value_4 = 0;
                }
                wp->value_d                    = e->value_4;
                D_8008DBF4[e->value_4].text[0] = 0x3E;
            }
            for (i = 0; i < 14; i++)
            {
                D_800987D4 = 0;
                func_8001FE38(D_8008DBF4[i].flags, D_8008DBF4[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != (sint8)pl[0x170])
            {
                pl[0x170] = pl[0x172] = idx;
                if (((sint8 *)pl)[0x170] != 0)
                {
                    pl[0x44F] = 1;
                }
                func_8001F5E4();
                Cd_read_sync();
            }
            return 0;
        default:
            return 0;
    }
}

sint32 func_80063058(DEBUG_WORK *wp)
{
    DEBUG_ENTRY *e;
    sint32 i;
    sint16 idx;
    uint8 *pl;

    pl = (uint8 *)&Player_work;
    e  = &wp->entry[1];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DCD4[i].flags &= 0xFFFBFFFF;
            }
            e->index_6 = (sint8)pl[0x171];
            D_8008DCD4[(sint16)e->index_6].flags |= 0x40000;
            // fall through
        case 2:
            if (wp->value_d >= 2)
            {
                e->value_4 = 1;
            }
            else
            {
                e->value_4 = wp->value_d;
            }
            e->state_0 = 1;
            // fall through
        case 1:
            for (i = 1; i >= 0; i--)
            {
                D_8008DCD4[i].text[0] = 0x20;
            }
            if (wp->sel_c == 0)
            {
                switch (wp->pad_4)
                {
                    case 0x10:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case 0x40:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case 0x2000:
                        D_8008DCD4[e->index_6].flags &= 0xFFFBFFFF;
                        D_8008DCD4[e->value_4].flags |= 0x40000;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DCD4[e->value_4].text[0] = 0x3E;
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                func_8001FE38(D_8008DCD4[i].flags, D_8008DCD4[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != (sint8)pl[0x171])
            {
                pl[0x171] = pl[0x173] = idx;
                func_8001F5E4();
                Cd_read_sync();
            }
            return 0;
        default:
            return 0;
    }
}

sint32 func_80063334(DEBUG_WORK *wp)
{
    DEBUG_ENTRY *e;
    sint32 i;
    sint16 idx;
    uint8 *pl;

    pl = (uint8 *)&Player_work;
    e  = &wp->entry[2];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DCF4[i].flags &= 0xFFFBFFFF;
            }
            e->index_6 = (sint8)pl[0x16A];
            D_8008DCF4[(sint16)e->index_6].flags |= 0x40000;
            // fall through
        case 2:
            if (wp->value_d >= 2)
            {
                e->value_4 = 1;
            }
            else
            {
                e->value_4 = wp->value_d;
            }
            e->state_0 = 1;
            // fall through
        case 1:
            for (i = 0; i < 2; i++)
            {
                D_8008DCF4[i].text[0] = 0x20;
            }
            if (wp->sel_c == 2)
            {
                switch (wp->pad_4)
                {
                    case 0x10:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case 0x40:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case 0x2000:
                        D_8008DCF4[e->index_6].flags &= 0xFFFBFFFF;
                        D_8008DCF4[e->value_4].flags |= 0x40000;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DCF4[e->value_4].text[0] = 0x3E;
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                func_8001FE38(D_8008DCF4[i].flags, D_8008DCF4[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != (sint8)pl[0x16A])
            {
                pl[0x16A] = idx;
                func_8001F5E4();
                Cd_read_sync();
            }
            return 0;
        default:
            return 0;
    }
}

sint32 func_80063604(DEBUG_WORK *wp)
{
    DEBUG_ENTRY *e;
    sint32 i;
    uint16 idx;

    e = &wp->entry[3];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DD14[i].flags &= 0xFFFBFFFF;
            }
            e->index_6 = DEBUG_GAME_54;
            D_8008DD14[(uint16)e->index_6].flags |= 0x40000;
            // fall through
        case 2:
            if (wp->value_d >= 2)
            {
                e->value_4 = 1;
            }
            else
            {
                e->value_4 = wp->value_d;
            }
            e->state_0 = 1;
            // fall through
        case 1:
            for (i = 0; i < 2; i++)
            {
                D_8008DD14[i].text[0] = 0x20;
            }
            if (wp->sel_c == 3)
            {
                switch (wp->pad_4)
                {
                    case 0x10:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case 0x40:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case 0x2000:
                        D_8008DD14[(uint16)e->index_6].flags &= 0xFFFBFFFF;
                        D_8008DD14[e->value_4].flags |= 0x40000;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DD14[e->value_4].text[0] = 0x3E;
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                func_8001FE38(D_8008DD14[i].flags, D_8008DD14[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != DEBUG_GAME_54)
            {
                func_800425FC(&Player_work, idx);
                DEBUG_GAME_54 = wp->entry[3].index_6;
            }
            return 0;
        default:
            return 0;
    }
}

sint32 func_800638D8(DEBUG_WORK *wp)
{
    DEBUG_ENTRY *e;
    sint32 i;
    sint16 idx;
    uint8 *pl;

    pl = (uint8 *)&Player_work;
    e  = &wp->entry[4];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DD34[i].flags &= 0xFFFBFFFF;
            }
            e->index_6 = (sint8)pl[0x16B];
            D_8008DD34[(sint16)e->index_6].flags |= 0x40000;
            // fall through
        case 2:
            if (wp->value_d >= 2)
            {
                e->value_4 = 1;
            }
            else
            {
                e->value_4 = wp->value_d;
            }
            e->state_0 = 1;
            // fall through
        case 1:
            for (i = 1; i >= 0; i--)
            {
                D_8008DD34[i].text[0] = 0x20;
            }
            if (4 == wp->sel_c)
            {
                switch (wp->pad_4)
                {
                    case 0x10:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case 0x40:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case 0x2000:
                        D_8008DD34[e->index_6].flags &= 0xFFFBFFFF;
                        D_8008DD34[e->value_4].flags |= 0x40000;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DD34[e->value_4].text[0] = 0x3E;
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                func_8001FE38(D_8008DD34[i].flags, D_8008DD34[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != (sint8)pl[0x16B])
            {
                pl[0x16B] = idx;
                func_8001F5E4();
                Cd_read_sync();
            }
            return 0;
        default:
            return 0;
    }
}

void func_80063BA8(void)
{
    D_800987B0.word = 0;
    D_800987B4      = 0;
    D_800987B8      = 0;
}

void func_80063BC8(sint32 arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    DEBUG_FADE *fp;

    fp = (DEBUG_FADE *)&D_800987B0;
    if (*(sint8 *)&Game_work == 3)
    {
        D_800987B0.flag = 1;
        D_800987B1      = arg1;
        if (arg1 & 2)
        {
            D_800987B2 = 2;
        }
        else
        {
            D_800987B2 = 0;
        }
        fp->value_4 = arg2;
        fp->value_5 = arg3;
        fp->value_6 = 0;
        fp->value_8 = arg0;
    }
}

void func_80063C30(void)
{
    PL_WORK *pl;
    DEBUG_FADE *fp;

    pl = &Player_work;
    fp = (DEBUG_FADE *)&D_800987B0;
    if (*(sint8 *)&D_800987B0 == 0)
    {
        return;
    }
    switch (*(sint8 *)&D_800987B2)
    {
        case 0:
            Player_work.routine_1                 = 0x10;
            Player_work.value0a                   = 0;
            *(uint32 *)&Player_work.table180[0].z = 0;
            Player_work.value44d                  = 0;
            (*(sint8 *)&D_800987B2)++;
            MojiTaskExec2(*(uint8 *)&D_800987B4, D_800987B5);
            if (D_800987B1 & 0x10)
            {
                Player_work.value449 = 1;
            }
            break;
        case 1:
            if (D_800987B1 & 1)
            {
                pl->routine_0 &= 0xFD;
            }
            else
            {
                pl->routine_0 |= 2;
            }
            if ((uint32)(pl->routine_1 - 0xB) < 2)
            {
                MojiTaskKill();
            }
            if (!(Moji_flag & D_8008DD54[(uint8)fp->value_4]))
            {
                if (!(fp->mode_1 & 4))
                {
                    pl->routine_0 |= 2;
                }
                if (!(fp->mode_1 & 8) && pl->routine_1 == 0x10)
                {
                    pl->value0a++;
                }
                if (fp->mode_1 & 0x10)
                {
                    pl->value449 = 0;
                }
                fp->flag_0 = 0;
            }
            break;
        case 2:
            *(uint32 *)&Player_work.table180[0].z = 0;
            Player_work.value44d                  = 0;
            (*(sint8 *)&D_800987B2)++;
            MojiTaskExec2(*(uint8 *)&D_800987B4, D_800987B5);
            break;
        case 3:
            if (D_800987B1 & 1)
            {
                pl->routine_0 &= 0xFD;
            }
            else
            {
                pl->routine_0 |= 2;
            }
            if ((uint32)(pl->routine_1 - 0xB) < 2)
            {
                MojiTaskKill();
            }
            if (!(Moji_flag & D_8008DD54[(uint8)fp->value_4]))
            {
                fp->flag_0 = 0;
                pl->routine_0 |= 2;
            }
            break;
    }
}

void func_80063EF0(void)
{
    sint32 i;
    LOGO_WORK *wp;

    wp = D_800C3528;
    for (i = 0; i < 4; i++, wp++)
    {
        *(uint32 *)&wp->active_0 = 0;
        *(uint32 *)&wp->value_4  = 0;
        wp->value_8              = 0;
    }
}

void Game_logo_kill(sint32 index)
{
    sint32 i;
    LOGO_WORK *wp;

    if (index < 0)
    {
        wp = D_800C3528;
        // The accumulator is the loop counter itself.
        for (i = 0; i < 4; i++)
        {
            i |= wp->flag_1;
            wp++;
        }
        if (i != 0)
        {
            Obj_work_flag_change(0x3FF, 2);
        }
        func_80063EF0();
        return;
    }
    wp           = &D_800C3528[index];
    wp->active_0 = 0;
    if (wp->flag_1 != 0)
    {
        Obj_work_flag_change(0x3FF, 2);
    }
}

void func_80063FC0(sint32 index, sint32 arg)
{
    LOGO_WORK *wp;

    wp           = &D_800C3528[index];
    wp->active_0 = 1;
    wp->value_5  = arg >> 16;
    wp->value_4  = D_8008ECDE[arg & 0xFF][0];
    wp->kind_2   = D_8008ECDC[arg & 0xFF][0];
    wp->value_8  = D_8008ECE0[arg & 0xFF][0];
    if (arg >= 0)
    {
        wp->flag_1 = 1;
        Obj_work_flag_change(0x3FF, 1);
    }
    else
    {
        wp->flag_1 = 0;
    }
}

void func_80064060(void)
{
    sint32 i;
    LOGO_WORK *wp;

    if (D_80098824 == 0)
    {
        wp = D_800C3528;
        for (i = 0; i < 4; i++)
        {
            if (wp->active_0 != 0)
            {
                D_8008DD64[wp->kind_2](wp);
            }
            wp++;
        }
    }
}

void func_800640F0(LOGO_WORK *wp)
{
    LOGO_SPRITE *rec;
    DEBUG_PRIM *start;
    DEBUG_PRIM *p;
    sint32 d;

    rec   = (LOGO_SPRITE *)wp->value_8;
    start = *(DEBUG_PRIM **)0x1F800070;
    p     = start;
    // The first tag store stays: the value_4 load between the two may alias it.
    p->tag  = 0x02000000;
    p->rgbc = (uint32)wp->value_4 | 0xE1000000;
    p->tag  = (((uint32)(p + 1)) & 0xFFFFFF) | 0x02000000;
    p->xy   = 0;
    p++;
    do
    {
        p->tag     = (((uint32)(p + 1)) & 0xFFFFFF) | 0x04000000;
        p->rgbc    = 0x64808080;
        p->xy      = rec->xy_4;
        p->uv_clut = rec->uv_8;
        p->wh      = rec->wh_c;
        switch ((sint8)(rec->head_0 >> 8))
        {
            case 1:
                if (*(uint16 *)0x1F800002 & 0x10)
                {
                    continue;
                }
                break;
            case 2:
                if (((Game_work.timer_0c / 15) % 60) & 1)
                {
                    continue;
                }
                break;
            case 3:
                d = *(sint16 *)((uint8 *)&Player_work + 0xB0);
                if (d > 0x50)
                {
                    d = ((d - 0x41) >> 4) * 5;
                    *(uint8 *)&p->uv_clut -= d;
                    *(uint16 *)&p->wh += d;
                }
                break;
        }
        p++;
    } while ((sint16)(++rec)->head_0 >= 0);
    addPrims(&DEBUG_OT[wp->value_5], start, p - 1);
    *(DEBUG_PRIM **)0x1F800070 = p;
}
