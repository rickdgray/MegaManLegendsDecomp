#include "common.h"
#include "code_8001786C.h"
#include "debug.h"
#include "display.h"
#include "game.h"
#include "moji.h"
#include "pad.h"
#include "player.h"
#include "scratch.h"

// Small uninitialized statics (.sbss 0x80098700-0x80098708).
static sint32 D_80098700[2];

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", func_80062CF0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", func_80063058);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", func_80063334);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", func_80063604);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", func_800638D8);

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
            Player_work[0].routine_9 = 0x10;
            Player_work[0].field_A   = 0;
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
                pl->unk00 &= ~2;
            }
            else
            {
                pl->unk00 |= 2;
            }
            if (pl->routine_9 == 0xB || pl->routine_9 == 0xC)
            {
                MojiTaskKill();
            }
            if (!(Moji_flag & D_8008DD54[fp->task_no_4]))
            {
                if (!(fp->mode_1 & 4))
                {
                    pl->unk00 |= 2;
                }
                if (!(fp->mode_1 & 8) && pl->routine_9 == 0x10)
                {
                    pl->field_A++;
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
                pl->unk00 &= ~2;
            }
            else
            {
                pl->unk00 |= 2;
            }
            if (pl->routine_9 == 0xB || pl->routine_9 == 0xC)
            {
                MojiTaskKill();
            }
            if (!(Moji_flag & D_8008DD54[fp->task_no_4]))
            {
                fp->flag_0 = 0;
                pl->unk00 |= 2;
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", Game_logo_kill);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/debug", func_80063FC0);

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
