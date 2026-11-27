#include "common.h"
#include "cd.h"
#include "code_8001786C.h"
#include "code_8001F828.h"
#include "code_800425FC.h"
#include "debug.h"
#include "display.h"
#include "game.h"
#include "moji.h"
#include "pad.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"

// Small uninitialized statics (.sbss 0x80098700-0x80098708).
// Separate scalars, not an array: func_80062CF0's scheduling needs a scalar debug_hold_cnt.
static uint32 debug_hold_cnt; // frames func_80062CF0 has seen UP or DOWN held; auto-repeats from 16
static uint32 D_80098704;     // unused (no code reaches it)

void func_800629E0(void)
{
    *(uint32 *)&Debug_work.routine_0 = 0;
}

void func_800629F0(void)
{
    DEBUG_WORK *wp;

    wp               = &Debug_work;
    Debug_work.on_4  = PAD_ON(Joy1);
    Debug_work.now_6 = PAD_NOW(Joy1);
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
    MojiTaskExec(0, D_8008CACC[0], -1);
    MojiTaskExec(1, D_8008CACC[1], -1);
    return 0;
}

sint32 func_80062B04(DEBUG_WORK *wp)
{
    sint32 i;

    switch (wp->on_4)
    {
        case PAD_START:
        case PAD_CROSS:
            wp->mode_8 = 2;
            wp->on_4   = 0;
            break;
        case PAD_RIGHT:
            wp->sel_9++;
            if (wp->sel_9 >= 5)
            {
                wp->sel_9 = 0;
            }
            goto check;
        case PAD_LEFT:
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
    PL_WORK *pl;

    pl = &Player_work[0];
    e  = &wp->entry[0];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 14; i++)
            {
                D_8008DBF4[i].pos &= ~DEBUG_MENU_CUR;
            }
            e->index_6 = pl->weapon_right_no;
            D_8008DBF4[e->index_6].pos |= DEBUG_MENU_CUR;
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
                D_8008DBF4[i].text[0] = ' ';
            }
            if (wp->sel_c == 1)
            {
                // The held tests read on_4 and now_6 as one word: UP or DOWN held, not just pressed.
                if (wp->on_4 & PAD_CIRCLE)
                {
                    D_8008DBF4[e->index_6].pos &= ~DEBUG_MENU_CUR;
                    D_8008DBF4[e->value_4].pos |= DEBUG_MENU_CUR;
                    e->index_6     = e->value_4;
                    debug_hold_cnt = 0;
                }
                else if (wp->on_4 & PAD_UP)
                {
                    e->value_4--;
                    debug_hold_cnt = 0;
                }
                else if ((*(uint32 *)&wp->on_4 & ((PAD_UP << 16) | PAD_UP)) == (PAD_UP << 16))
                {
                    if (debug_hold_cnt >= 16)
                    {
                        e->value_4--;
                    }
                    else
                    {
                        debug_hold_cnt++;
                    }
                }
                else if (wp->on_4 & PAD_DOWN)
                {
                    e->value_4++;
                    debug_hold_cnt = 0;
                }
                else if ((*(uint32 *)&wp->on_4 & ((PAD_DOWN << 16) | PAD_DOWN)) == (PAD_DOWN << 16))
                {
                    if (debug_hold_cnt >= 16)
                    {
                        e->value_4++;
                    }
                    else
                    {
                        debug_hold_cnt++;
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
                D_8008DBF4[e->value_4].text[0] = '>';
            }
            for (i = 0; i < 14; i++)
            {
                D_800987D4 = 0;
                Print(D_8008DBF4[i].pos, D_8008DBF4[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != pl->weapon_right_no)
            {
                pl->weapon_right_no = pl->tbl_sel = idx;
                if (pl->weapon_right_no != 0)
                {
                    pl->unk44F = 1;
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
    PL_WORK *pl;

    pl = &Player_work[0];
    e  = &wp->entry[1];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DCD4[i].pos &= ~DEBUG_MENU_CUR;
            }
            e->index_6 = pl->unk171;
            D_8008DCD4[e->index_6].pos |= DEBUG_MENU_CUR;
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
                D_8008DCD4[i].text[0] = ' ';
            }
            if (wp->sel_c == 0)
            {
                switch (wp->on_4)
                {
                    case PAD_UP:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case PAD_DOWN:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case PAD_CIRCLE:
                        D_8008DCD4[e->index_6].pos &= ~DEBUG_MENU_CUR;
                        D_8008DCD4[e->value_4].pos |= DEBUG_MENU_CUR;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DCD4[e->value_4].text[0] = '>';
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                Print(D_8008DCD4[i].pos, D_8008DCD4[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != pl->unk171)
            {
                pl->unk171 = pl->unk173 = idx;
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
    PL_WORK *pl;

    pl = &Player_work[0];
    e  = &wp->entry[2];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DCF4[i].pos &= ~DEBUG_MENU_CUR;
            }
            e->index_6 = pl->unk16A;
            D_8008DCF4[e->index_6].pos |= DEBUG_MENU_CUR;
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
                D_8008DCF4[i].text[0] = ' ';
            }
            if (wp->sel_c == 2)
            {
                switch (wp->on_4)
                {
                    case PAD_UP:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case PAD_DOWN:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case PAD_CIRCLE:
                        D_8008DCF4[e->index_6].pos &= ~DEBUG_MENU_CUR;
                        D_8008DCF4[e->value_4].pos |= DEBUG_MENU_CUR;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DCF4[e->value_4].text[0] = '>';
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                Print(D_8008DCF4[i].pos, D_8008DCF4[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != pl->unk16A)
            {
                pl->unk16A = idx;
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
                D_8008DD14[i].pos &= ~DEBUG_MENU_CUR;
            }
            e->index_6 = (sint8)Game_work.unk054;
            // Unlike the other rows, this one indexes by index_6 unsigned (lhu, andi 0xFFFF).
            D_8008DD14[(uint16)e->index_6].pos |= DEBUG_MENU_CUR;
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
                D_8008DD14[i].text[0] = ' ';
            }
            if (wp->sel_c == 3)
            {
                switch (wp->on_4)
                {
                    case PAD_UP:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case PAD_DOWN:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case PAD_CIRCLE:
                        D_8008DD14[(uint16)e->index_6].pos &= ~DEBUG_MENU_CUR;
                        D_8008DD14[e->value_4].pos |= DEBUG_MENU_CUR;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DD14[e->value_4].text[0] = '>';
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                Print(D_8008DD14[i].pos, D_8008DD14[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != (sint8)Game_work.unk054)
            {
                func_800425FC(&Player_work[0], idx);
                Game_work.unk054 = wp->entry[3].index_6;
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
    PL_WORK *pl;

    pl = &Player_work[0];
    e  = &wp->entry[4];
    switch (e->state_0)
    {
        case 0:
            for (i = 0; i < 2; i++)
            {
                D_8008DD34[i].pos &= ~DEBUG_MENU_CUR;
            }
            e->index_6 = (sint8)pl->unk16B;
            D_8008DD34[e->index_6].pos |= DEBUG_MENU_CUR;
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
                D_8008DD34[i].text[0] = ' ';
            }
            if (wp->sel_c == 4)
            {
                switch (wp->on_4)
                {
                    case PAD_UP:
                        e->value_4--;
                        if (e->value_4 < 0)
                        {
                            e->value_4 = 1;
                        }
                        break;
                    case PAD_DOWN:
                        e->value_4++;
                        if (e->value_4 >= 2)
                        {
                            e->value_4 = 0;
                        }
                        break;
                    case PAD_CIRCLE:
                        D_8008DD34[e->index_6].pos &= ~DEBUG_MENU_CUR;
                        D_8008DD34[e->value_4].pos |= DEBUG_MENU_CUR;
                        e->index_6 = e->value_4;
                        break;
                }
                wp->value_d                    = e->value_4;
                D_8008DD34[e->value_4].text[0] = '>';
            }
            for (i = 0; i < 2; i++)
            {
                D_800987D4 = 0;
                Print(D_8008DD34[i].pos, D_8008DD34[i].text);
            }
            return 0;
        case 3:
            idx = e->index_6;
            if (idx != (sint8)pl->unk16B)
            {
                pl->unk16B = idx;
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
    D_800987B8      = NULL;
}

void func_80063BC8(void *pos, sint32 mode, sint32 value_4, sint32 value_5)
{
    DEBUG_FADE *fp;

    fp = (DEBUG_FADE *)&D_800987B0;
    if (Game_work.routine_0 == 3)
    {
        D_800987B0.flag = 1;
        D_800987B1      = mode;
        if (mode & 2)
        {
            D_800987B2 = 2;
        }
        else
        {
            D_800987B2 = 0;
        }
        fp->task_no_4 = value_4;
        fp->mess_no_5 = value_5;
        fp->value_6   = 0;
        fp->pos_8     = pos;
    }
}

void func_80063C30(void)
{
    PL_WORK *pl;
    DEBUG_FADE *fp;

    pl = &Player_work[0];
    fp = (DEBUG_FADE *)&D_800987B0;
    if (D_800987B0.flag == 0)
    {
        return;
    }
    // D_800987B2 is a halfword to func_80063BC8, a byte step here.
    switch (*(sint8 *)&D_800987B2)
    {
        case 0:
            Player_work[0].routine_1 = 0x10;
            Player_work[0].routine_2 = 0;
            Player_work[0].obj_184   = NULL;
            Player_work[0].unk44D    = 0;
            (*(sint8 *)&D_800987B2)++;
            MojiTaskExec2(*(uint8 *)&D_800987B4, D_800987B5);
            if (D_800987B1 & 0x10)
            {
                Player_work[0].unk449 = 1;
            }
            break;
        case 1:
            if (D_800987B1 & 1)
            {
                pl->be_flag &= ~TRANS;
            }
            else
            {
                pl->be_flag |= TRANS;
            }
            if (pl->routine_1 == 0xB || pl->routine_1 == 0xC)
            {
                MojiTaskKill();
            }
            if (!(Moji_flag & D_8008DD54[fp->task_no_4]))
            {
                if (!(fp->mode_1 & 4))
                {
                    pl->be_flag |= TRANS;
                }
                if (!(fp->mode_1 & 8) && pl->routine_1 == 0x10)
                {
                    pl->routine_2++;
                }
                if (fp->mode_1 & 0x10)
                {
                    pl->unk449 = 0;
                }
                fp->flag_0 = 0;
            }
            break;
        case 2:
            Player_work[0].obj_184 = NULL;
            Player_work[0].unk44D  = 0;
            (*(sint8 *)&D_800987B2)++;
            MojiTaskExec2(*(uint8 *)&D_800987B4, D_800987B5);
            break;
        case 3:
            if (D_800987B1 & 1)
            {
                pl->be_flag &= ~TRANS;
            }
            else
            {
                pl->be_flag |= TRANS;
            }
            if (pl->routine_1 == 0xB || pl->routine_1 == 0xC)
            {
                MojiTaskKill();
            }
            if (!(Moji_flag & D_8008DD54[fp->task_no_4]))
            {
                fp->flag_0 = 0;
                pl->be_flag |= TRANS;
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
        wp->sprites_8            = 0;
    }
}

void Game_logo_kill(sint32 index)
{
    sint32 i;
    LOGO_WORK *wp;

    if (index < 0)
    {
        wp = D_800C3528;
        // The flags are ORed into the loop counter itself.
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

void Game_logo_set(sint32 index, sint32 arg)
{
    LOGO_WORK *wp;

    wp            = &D_800C3528[index];
    wp->active_0  = 1;
    wp->value_5   = arg >> 16;
    wp->value_4   = D_8008ECDC[arg & 0xFF].value_2;
    wp->kind_2    = D_8008ECDC[arg & 0xFF].kind_0;
    wp->sprites_8 = D_8008ECDC[arg & 0xFF].sprites_4;
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

    rec   = wp->sprites_8;
    start = Debug_prim_ptr;
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
        p->xy      = rec->xy_4.word;
        p->uv_clut = rec->uv_8;
        p->wh      = rec->wh_c;
        switch ((sint8)(rec->head_0 >> 8))
        {
            case 1:
                if (System_timer & 0x10)
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
                d = Player_work[0].life_max;
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
    addPrims(&Disp_env_ptr->ot[wp->value_5], start, p - 1);
    Debug_prim_ptr = p;
}
