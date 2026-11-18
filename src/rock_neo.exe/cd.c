#include "common.h"
#include "system.h"
#include "sound.h"
#include "cd.h"
#include "game.h"
#include "psyq/libcd.h"

void Cd_init(void)
{
    sint32 i;

    while (CdInit() == 0)
    {
    }

    D_800988DC = 0; // stored twice in the original; both needed for the match
    D_80098998 = 0;
    Cd_status  = 0;
    D_80098B42 = 7;
    Cd_mode    = 0;
    D_80098AA0 = 0;
    D_800988DC = 0; // stored twice in the original; both needed for the match

    Cd_controlb_retry(CdlSetmode, &Cd_mode, Cd_result);

    Cd_sync_done = 1;

    for (i = 0; i < CD_CMD_QUEUE_LEN; i++)
    {
        Cd_cmd_queue[i].type = CD_CMD_END;
    }

    Cd_cmd_exec_ptr  = Cd_cmd_queue;
    Cd_cmd_write_ptr = Cd_cmd_queue;

    Cd_wait          = 0;
    Cd_movie_playing = 0;
    D_800989C8       = 0;
    Cd_cmd_routine   = 0;
    D_800988D0       = 0;
}

void func_8001B4C4(void)
{
}

void func_8001B4CC(void)
{
    switch ((uint32)Cd_cmd_routine)
    {
        case 0:
            if (Cd_sync_done == 0)
            {
                Cd_stop();
            }
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done == 0)
            {
                break;
            }
            Cd_set_mode(CdlModeSpeed | CdlModeSize1);
            Cd_cmd_routine++;
            // fall through
        case 2:
            if (Cd_wait)
            {
                Cd_wait--;
                break;
            }
            // This command carries the destination pointer in its second argument word.
            func_8001CC7C(Cd_cmd_exec_ptr->args.arg1, (uint8 *)Cd_cmd_exec_ptr->args.arg2);
            D_800988D0 = 0;
            Cd_wait    = 0;
            Cd_cmd_routine++;
            // fall through
        case 3:
            Cd_wait++;
            if (Cd_wait == CD_CMD_TIMEOUT)
            {
                Cd_error_flags |= CD_ERR_CMD_TIMEOUT;
            }
            else if (Cd_status == 0)
            {
                Cd_cmd_dequeue();
            }
            break;
    }
}

void func_8001B63C(void)
{
}

void func_8001B644(void)
{
    sint32 i;

    switch (Cd_cmd_routine)
    {
        case 0:
            for (i = CD_VOL_MAX; i > 0; i--)
            {
                Cd_set_volume(i);
            }

            Sound_work.flags |= SOUND_FLAG_CD_OFF;
            Cd_stop();
            D_800988D0 = 1;
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done)
            {
                D_80098B42 = 1;
                Cd_cmd_dequeue();
            }
            break;
    }
}

void func_8001B6FC(void)
{
    sint32 i;

    switch (Cd_cmd_routine)
    {
        case 0:
            for (i = CD_VOL_MAX; i > 0; i--)
            {
                Cd_set_volume(i);
            }

            Sound_work.flags |= SOUND_FLAG_CD_OFF;
            Cd_stop();
            D_800988D0 = 1;
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done)
            {
                D_80098B42 = 2;
                Cd_cmd_dequeue();
            }
            break;
    }
}

void func_8001B7B4(void)
{
    sint32 i;
    uint16 tmp;

    for (i = CD_VOL_MAX; i > 0; i--)
    {
        Cd_set_volume(i);
    }

    Sound_work.flags |= SOUND_FLAG_CD_OFF;

    if (D_800988DC)
    {
        D_800988DC       = 0;
        Sound_work.unk06 = D_80098994;
    }
    else
    {
        tmp              = Sound_work.unk06;
        Sound_work.unk06 = 0;
        D_800988DC       = 1;
        D_80098994       = tmp;
    }

    Cd_cmd_dequeue();
}

void func_8001B858(void)
{
    D_80087670[Cd_cmd_exec_ptr->args.arg2]();
}

void func_8001B89C(void)
{
    CdlLOC pos;
    CdlFILTER filter;
    sint16 i;

    switch ((uint32)Cd_cmd_routine)
    {
        case 0:
            if (Cd_sync_done == 0)
            {
                Cd_stop();
            }
            D_800988D0 = 2;
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done == 0)
            {
                break;
            }
            Sound_work.unk0E = CD_VOL_MAX;
            Cd_set_mode(CdlModeSpeed | CdlModeRT | CdlModeSF);
            Cd_cmd_routine++;
            // fall through
        case 2:
            if (Cd_wait)
            {
                Cd_wait--;
                break;
            }
            Cd_status      = 0;
            Cd_error_flags = 0;
            Cd_sync_done   = Cd_status;
            if (D_80098B42 != 2)
            {
                filter.file = 1;
                filter.chan = ((uint8 *)&Cd_cmd_exec_ptr->args.arg2)[3] & 0x1F;
                D_800989B0  = Cd_file_tbl[Cd_cmd_exec_ptr->args.arg1].sector +
                              (*(uint32 *)&Cd_cmd_exec_ptr->args.arg3 & 0xFFFFFF);
                CdIntToPos(Cd_file_tbl[Cd_cmd_exec_ptr->args.arg1].sector +
                               (Cd_cmd_exec_ptr->args.arg2 & 0xFFFFFF),
                           &pos);
                Cd_controlb_retry(CdlSetfilter, (u_char *)&filter, Cd_result);
                Cd_controlb_retry(CdlSetloc, (u_char *)&pos, Cd_result);
                Cd_controlb_retry(CdlReadS, NULL, Cd_result);
                Cd_wait    = 0;
                D_80098AB8 = Cd_result[0];
            }
            Cd_cmd_routine++;
            // fall through
        case 3:
            if ((D_80098AB8 & 0x20) == 0)
            {
                Cd_wait++;
                if ((uint32)Cd_wait >= CD_CMD_TIMEOUT)
                {
                    Cd_error_flags |= CD_ERR_TIMEOUT;
                }
            }
            else
            {
                for (i = 0; i < CD_VOL_MAX; i++)
                {
                    Cd_set_volume(i);
                }
                D_80098B42 = 0;
                Sound_work.flags &= ~SOUND_FLAG_CD_OFF;
                Cd_cmd_dequeue();
            }
            break;
    }
}

// Shadow-VRAM row for an image y position (the 0x100 bit selects the second texture page row).
#define SHADOW_ROW(y) ((y) + (((y) & 0x100) >> 4) - (((y) & 0x100) + 0xF0))

// The buffered asset loader. One byte pointer serves as both the sector's record header and the
// destination of the byte-copy loops (one variable, which sets its register). D_8009BE48 is an
// incomplete array (a complete 8-byte RECT is small data to GCC, which then folds rect->x to the
// absolute address); the clut test reads back the stored clut_x; the seq/sep destination is a
// chained assignment.
void func_8001BB4C(void)
{
    CD_ASSET_REC *rec;
    uint8 *src;
    uint8 *buf;
    RECT *rect;

    switch (Cd_cmd_routine)
    {
        case 0:
            if (Cd_sync_done == 0)
            {
                Cd_stop();
            }
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done == 0)
            {
                break;
            }
            Cd_set_mode(0xA0);
            Cd_cmd_routine++;
            // fall through
        case 2:
            if (Cd_wait != 0)
            {
                Cd_wait--;
                break;
            }
            func_8001CF98(Cd_cmd_exec_ptr->args.arg1);
            D_800988D0 = 0;
            D_800987A8 = 0;
            Cd_wait    = 0;
            Cd_cmd_routine++;
            // fall through
        case 3:
            if (++Cd_wait == CD_CMD_TIMEOUT)
            {
                Cd_error_flags |= CD_ERR_CMD_TIMEOUT;
                break;
            }
            while (D_80098B38[D_800987A8] == 1)
            {
                switch (D_800989C8)
                {
                    case 0:
                        buf        = CD_SECTOR_BUF(D_800987A8);
                        D_80098A54 = ((CD_ASSET_REC *)buf)->type;
                        if (D_80098A54 == -1)
                        {
                            Cd_cmd_routine = 4;
                            return;
                        }
                        D_800C5604.size  = ((CD_ASSET_REC *)buf)->size;
                        D_800C5604.count = ((CD_ASSET_REC *)buf)->count;
                        rec              = (CD_ASSET_REC *)buf;
                        switch (D_80098A54)
                        {
                            case 0:
                                D_800C5604.u.dest = (uint8 *)rec->arg[0];
                                D_800C5604.count--;
                                break;
                            case 1:
                                rect                    = D_8009BE48;
                                D_800C5604.u.tim.clut_x = rec->arg[0];
                                D_800C5604.u.tim.clut_y = rec->arg[1];
                                D_800C5604.u.tim.clut_w = rec->arg[2];
                                D_800C5604.u.tim.clut_h = rec->arg[3];
                                D_800C5604.u.tim.x      = rec->arg[4];
                                D_800C5604.u.tim.y      = rec->arg[5];
                                D_800C5604.u.tim.w      = rec->arg[6];
                                D_800C5604.u.tim.h      = rec->arg[7];
                                D_800C5604.row          = 0;
                                D_800C5604.col          = 0;
                                if (D_800C5604.u.tim.clut_x != -1)
                                {
                                    if (rec->arg[0] < 0x140)
                                    {
                                        func_800176A4(((CD_ASSET_REC *)buf)->data,
                                                      &D_800AD168[rec->arg[0] +
                                                                  (SHADOW_ROW(rec->arg[1]) << 8)],
                                                      ((uint32)(rec->arg[3] * rec->arg[2]) >> 4) *
                                                          2);
                                        D_80098868 |= 1 << SHADOW_ROW(rec->arg[1]);
                                    }
                                    else
                                    {
                                        rect->x = rec->arg[0];
                                        rect->y = rec->arg[1];
                                        rect->w = rec->arg[2];
                                        rect->h = rec->arg[3];
                                        LoadImage(rect, (u_long *)((CD_ASSET_REC *)buf)->data);
                                    }
                                }
                                rect->w = 0x20;
                                rect->h = 0x20;
                                D_800C5604.count--;
                                break;
                            case 3:
                                D_800C5604.u.tiles.x    = rec->arg[0];
                                D_800C5604.u.tiles.y    = rec->arg[1];
                                D_800C5604.u.tiles.cols = rec->arg[2];
                                D_800C5604.u.tiles.rows = rec->arg[3];
                                D_800C5604.row          = 0;
                                D_800C5604.col          = 0;
                                D_8009BE48[0].w         = 0x20;
                                D_8009BE48[0].h         = 0x20;
                                break;
                            case 4:
                                rect = D_8009BE48;
                            case 9:
                            case 10:
                                if (rec->arg[0] < 0x100)
                                {
                                    func_800176A4(
                                        ((CD_ASSET_REC *)buf)->data,
                                        &D_800AD168[rec->arg[0] + (SHADOW_ROW(rec->arg[1]) << 8)],
                                        ((uint32)(rec->arg[3] * rec->arg[2]) >> 4) * 2);
                                    D_80098868 |= 1 << SHADOW_ROW(rec->arg[1]);
                                }
                                else
                                {
                                    rect    = D_8009BE48;
                                    rect->x = rec->arg[0];
                                    rect->y = rec->arg[1];
                                    if (D_80098A54 != 10)
                                    {
                                        rect->w = rec->arg[2];
                                        rect->h = rec->arg[3];
                                    }
                                    else
                                    {
                                        rect->h = (uint32)(rec->arg[2] * rec->arg[3]) >> 6;
                                        rect->w = 0x40;
                                    }
                                    LoadImage(rect, (u_long *)((CD_ASSET_REC *)buf)->data);
                                }
                                D_800989C8 = 0;
                                goto next;
                            case 5:
                                D_800C5604.u.vab.slot = rec->arg[0];
                                D_800C5604.u.vab.id   = rec->arg[1];
                                D_800C5604.u.vab.arg  = rec->arg[2];
                                D_800C5604.u.vab.size = rec->arg[3];
                                D_800C5604.u.vab.head =
                                    (uint8 *)(rec->arg[0] * 0x1820 + 0x8014B000);
                                D_800C5604.u.vab.load = 1;
                                if (rec->arg[0] == 4)
                                {
                                    if (Game_work.sound_1b8[4].id == rec->arg[1])
                                    {
                                        D_800C5604.u.vab.load = 0;
                                    }
                                    if (D_80098958 & 0x800)
                                    {
                                        D_800C5604.u.vab.load = 1;
                                        func_8001B33C();
                                    }
                                }
                                if (D_800C5604.u.vab.load == 1)
                                {
                                    Game_work.sound_1b8[rec->arg[0]].id = rec->arg[1];
                                    *(sint32 *)&Game_work.sound_1b8[rec->arg[0]].reserved03[1] =
                                        rec->arg[2];
                                    if ((sint16)Game_work.sound_1b8[rec->arg[0]].vab != -1)
                                    {
                                        SsVabClose(Game_work.sound_1b8[rec->arg[0]].vab);
                                    }
                                }
                                D_800C5604.count--;
                                break;
                            case 7:
                                D_800C5604.u.seq.dest = (uint8 *)(D_80098AD4[rec->arg[0]][0] =
                                                                      rec->arg[2] + 0x8013B000);
                                D_800C5604.u.seq.load = 0;
                                if (D_80098AD0[rec->arg[0]].id != rec->arg[1])
                                {
                                    D_80098AD0[rec->arg[0]].id = rec->arg[1];
                                    D_800C5604.u.seq.load      = 1;
                                }
                                break;
                            case 8:
                                D_800C5604.u.sep.dest = (uint8 *)(D_80098AD4[rec->arg[0]][0] =
                                                                      rec->arg[3] + 0x8013B000);
                                D_800C5604.u.sep.load = 0;
                                if (D_80098AD0[rec->arg[0]].id != rec->arg[1])
                                {
                                    D_80098AD0[rec->arg[0]].id            = rec->arg[1];
                                    D_80098AD0[rec->arg[0]].reserved01[0] = rec->arg[2];
                                    D_800C5604.u.sep.load                 = 1;
                                }
                                break;
                        }
                        D_800989C8 = D_80098A54 + 1;
                        break;
                    case 1:
                        if (D_800C5604.size >= 0x800)
                        {
                            func_800176DC(CD_SECTOR_BUF(D_800987A8), D_800C5604.u.dest, 0x40);
                            D_800C5604.size -= 0x800;
                            D_800C5604.u.dest += 0x800;
                        }
                        else
                        {
                            src = CD_SECTOR_BUF(D_800987A8);
                            buf = D_800C5604.u.dest;
                            while (D_800C5604.size != 0)
                            {
                                *buf++ = *src++;
                                D_800C5604.size--;
                            }
                        }
                        if (--D_800C5604.count == 0)
                        {
                            D_800989C8 = 0;
                        }
                        break;
                    case 2:
                        rect    = D_8009BE48;
                        rect->x = D_800C5604.u.tim.x + (D_800C5604.col << 5);
                        rect->y = D_800C5604.u.tim.y + (D_800C5604.row << 5);
                        LoadImage(rect, (u_long *)CD_SECTOR_BUF(D_800987A8));
                        if (++D_800C5604.col == (uint32)D_800C5604.u.tim.w >> 5)
                        {
                            D_800C5604.col = 0;
                            if (++D_800C5604.row == (uint32)D_800C5604.u.tim.h >> 5)
                            {
                                D_800989C8 = 0;
                            }
                        }
                        break;
                    case 4:
                        rect    = D_8009BE48;
                        rect->x = D_800C5604.u.tiles.x + (D_800C5604.col << 5);
                        rect->y = D_800C5604.u.tiles.y + (D_800C5604.row << 5);
                        LoadImage(rect, (u_long *)CD_SECTOR_BUF(D_800987A8));
                        if (++D_800C5604.col == D_800C5604.u.tiles.cols)
                        {
                            D_800C5604.col = 0;
                            if (++D_800C5604.row == D_800C5604.u.tiles.rows)
                            {
                                D_800989C8 = 0;
                            }
                        }
                        break;
                    case 6:
                        if (D_800C5604.u.vab.load == 0)
                        {
                            if (--D_800C5604.count == 0)
                            {
                                D_800989C8 = 0;
                            }
                        }
                        else if (D_800C5604.u.vab.size >= 0x800)
                        {
                            func_800176DC(CD_SECTOR_BUF(D_800987A8), D_800C5604.u.vab.head, 0x40);
                            D_800C5604.u.vab.head += 0x800;
                            D_800C5604.u.vab.size -= 0x800;
                        }
                        else if (D_800C5604.u.vab.size != 0)
                        {
                            func_80017684(CD_SECTOR_BUF(D_800987A8), D_800C5604.u.vab.head,
                                          D_800C5604.u.vab.size / 4);
                            D_800C5604.u.vab.size                          = 0;
                            Game_work.sound_1b8[D_800C5604.u.vab.slot].vab = SsVabOpenHeadSticky(
                                (uint8 *)(D_800C5604.u.vab.slot * 0x1820 + 0x8014B000),
                                D_800C5604.u.vab.slot, D_800C5604.u.vab.arg);
                        }
                        else
                        {
                            if (SsVabTransBodyPartly(
                                    CD_SECTOR_BUF(D_800987A8), 0x800,
                                    Game_work.sound_1b8[D_800C5604.u.vab.slot].vab) ==
                                (sint16)Game_work.sound_1b8[D_800C5604.u.vab.slot].vab)
                            {
                                D_800989C8 = 0;
                            }
                            SsVabTransCompleted(1);
                        }
                        break;
                    case 8:
                        if (D_800C5604.size >= 0x800)
                        {
                            if (D_800C5604.u.seq.load != 0)
                            {
                                func_800176DC(CD_SECTOR_BUF(D_800987A8), D_800C5604.u.seq.dest,
                                              0x40);
                            }
                            D_800C5604.size -= 0x800;
                            D_800C5604.u.seq.dest += 0x800;
                        }
                        else
                        {
                            if (D_800C5604.u.seq.load != 0)
                            {
                                src = CD_SECTOR_BUF(D_800987A8);
                                buf = D_800C5604.u.seq.dest;
                                while (D_800C5604.size != 0)
                                {
                                    *buf++ = *src++;
                                    D_800C5604.size--;
                                }
                            }
                            D_800989C8 = 0;
                        }
                        break;
                    case 9:
                        if (D_800C5604.size >= 0x800)
                        {
                            if (D_800C5604.u.sep.load != 0)
                            {
                                func_800176DC(CD_SECTOR_BUF(D_800987A8), D_800C5604.u.sep.dest,
                                              0x40);
                            }
                            D_800C5604.size -= 0x800;
                            D_800C5604.u.sep.dest += 0x800;
                        }
                        else
                        {
                            if (D_800C5604.u.sep.load != 0)
                            {
                                src = CD_SECTOR_BUF(D_800987A8);
                                buf = D_800C5604.u.sep.dest;
                                while (D_800C5604.size != 0)
                                {
                                    *buf++ = *src++;
                                    D_800C5604.size--;
                                }
                            }
                            D_800989C8 = 0;
                        }
                        break;
                }
            next:
                D_80098B38[D_800987A8] = 0;
                if (++D_800987A8 == CD_READ_BUFFER_COUNT)
                {
                    D_800987A8 = 0;
                }
            }
            break;
        case 4:
            Cd_cmd_dequeue();
            break;
    }
}

void func_8001C7F0(u_char status, u_char *result)
{
    Cd_cmd_routine++;
    CdSyncCallback(0);
}

void func_8001C824(void)
{
    CdlLOC pos;

    switch ((uint32)Cd_cmd_routine)
    {
        case 0:
            if (Cd_sync_done == 0)
            {
                Cd_stop();
            }
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done == 0)
            {
                break;
            }
            D_800988D0 = 0;
            CdSyncCallback(func_8001C7F0);
            CdIntToPos(Cd_cmd_exec_ptr->args.arg2, &pos);
            Cd_control_retry(CdlSeekL, (u_char *)&pos, Cd_result);
            Cd_wait = 0;
            Cd_cmd_routine++;
            // fall through
        case 2:
            Cd_wait++;
            if (Cd_wait == CD_CMD_TIMEOUT)
            {
                Cd_error_flags |= CD_ERR_CMD_TIMEOUT;
            }
            break;
        case 3:
            Cd_cmd_dequeue();
            break;
    }
}

void func_8001C95C(void)
{
    uint32 sector;

    if (Cd_error_flags)
    {
        Cd_sync_done   = 0;
        Cd_mode        = 0;
        Cd_error_flags = 0;
        D_800989C8     = 0;
        Cd_cmd_routine = 0;
        CdSyncCallback(NULL);
        CdReadyCallback(NULL);
        while (CdReset(0) == 0)
        {
        }
    }

    if (D_800988D0 == 2)
    {
        Cd_controlb_retry(CdlNop, NULL, Cd_result);
        D_80098AB8 = Cd_result[0];
        if (Cd_result[0] & 0x20)
        {
            Cd_controlb_retry(CdlGetlocP, NULL, Cd_result);
            sector     = CdPosToInt((CdlLOC *)D_80098A9D);
            D_800989D8 = sector;
            if (sector >= D_800989B0)
            {
                if (D_800989C0 & 0x40000000)
                {
                    func_8001D58C(D_800989B8);
                }
                else
                {
                    Cd_stop();
                }
            }
        }
    }
    D_80087680[Cd_cmd_exec_ptr->type]();
}

// The command is copied field by field: a struct assignment is a block move, which
// reserves a fourth scratch register and shifts the allocation.
void Cd_cmd_dequeue(void)
{
    CD_CMD *p;

    for (p = Cd_cmd_queue; p->type != 0; p++)
    {
        p->type                  = p[1].type;
        p->args.arg1             = p[1].args.arg1;
        p->args.arg2             = p[1].args.arg2;
        *(uint32 *)&p->args.arg3 = *(uint32 *)&p[1].args.arg3;
    }

    p->type        = 0;
    D_800989C8     = 0;
    Cd_cmd_routine = 0;
    Cd_cmd_write_ptr--;
}

void Cd_pause(void)
{
    Cd_error_flags = 0;
    CdReadyCallback(0);
    CdSyncCallback(Cd_sync_cb);
    Cd_control_retry(CdlPause, NULL, Cd_result);
}

void Cd_stop(void)
{
    sint32 i;

    for (i = CD_VOL_MAX; i > 0; i--)
    {
        Cd_set_volume(i);
    }

    Sound_work.flags |= SOUND_FLAG_CD_OFF;
    Cd_error_flags = 0;
    CdReadyCallback(0);
    CdSyncCallback(Cd_sync_cb);
    Cd_control_retry(CdlPause, 0, Cd_result);
    D_800988D0 = 0;
    D_80098AB8 = 0;
}

void Cd_sync_cb(u_char status, u_char *result)
{
    CdSyncCallback(0);

    if (status == CdlComplete)
    {
        Cd_sync_done = 1;
        Cd_status    = 0;
    }
    else
    {
        Cd_status = 0x80;
        Cd_error_flags |= CD_ERR_SYNC;
    }
}

void func_8001CC7C(sint32 index, uint8 *dest)
{
    sint32 sector;

    sector         = Cd_file_tbl[index].sector;
    Cd_status      = 1;
    D_80098B42     = 7;
    Cd_error_flags = 0;
    Cd_wait        = 0;
    Cd_sync_done   = 0;
    D_80098A7C     = sector;
    CdIntToPos(sector, &D_80098814);
    D_800987A4 = dest;
    D_8009881C = Cd_file_tbl[index].size;
    CdReadyCallback(func_8001CD60);
    Cd_controlb_retry(CdlSetloc, (u_char *)&D_80098814, Cd_result);
    Cd_controlb_retry(CdlReadN, NULL, Cd_result);
}

void func_8001CD60(u_char status, u_char *result)
{
    sint32 sector;
    sint32 count;
    uint8 *src;

    Cd_wait = 0;
    if (status == CdlDataReady)
    {
        CdGetSector(D_800B5DB0, 3);
        sector = CdPosToInt((CdlLOC *)D_800B5DB0);
        if (sector != D_80098A7C)
        {
            Cd_error_flags |= CD_ERR_SECTOR;
            goto read_error;
        }
        D_80098A7C = sector + 1;
        if (D_8009881C >= CD_SECTOR_BYTES)
        {
            CdGetSector(D_800987A4, CD_SECTOR_WORDS);
            if (D_800989C8 == 0)
            {
                if (Cd_file_tbl[Cd_cmd_exec_ptr->args.arg1].unk8 != *(sint32 *)D_800987A4)
                {
                    Cd_error_flags |= CD_ERR_FILE_ID;
                    goto read_error;
                }
                D_800989C8 = status;
            }
            D_8009881C -= CD_SECTOR_BYTES;
            if (D_8009881C == 0)
            {
                CdReadyCallback(NULL);
                CdSyncCallback(Cd_sync_cb);
                Cd_control_retry(CdlPause, NULL, Cd_result);
                return;
            }
            D_800987A4 += CD_SECTOR_BYTES;
            return;
        }
        CdGetSector(D_800B5DB0, CD_SECTOR_WORDS);
        count = D_8009881C;
        src   = D_800B5DB0;
        while (count != 0)
        {
            *D_800987A4 = *src;
            D_800987A4++;
            src++;
            count--;
        }
        CdSyncCallback(Cd_sync_cb);
        Cd_control_retry(CdlPause, NULL, Cd_result);
    }
    else
    {
        Cd_error_flags |= CD_ERR_READY;
    read_error:
        Cd_status = 0x80;
    }
    CdReadyCallback(NULL);
}

void func_8001CF98(sint32 index)
{
    sint32 i;
    sint32 sector;

    for (i = 0; i < 10; i++)
    {
        D_80098B38[i] = 0;
    }

    sector         = Cd_file_tbl[index].sector;
    Cd_status      = 1;
    D_80098B42     = 7;
    Cd_error_flags = 0;
    Cd_wait        = 0;
    Cd_sync_done   = 0;
    D_80098998     = 0;
    D_80098A7C     = sector;
    CdIntToPos(sector, &D_80098814);
    D_8009881C = Cd_file_tbl[index].size;
    CdReadyCallback(func_8001D078);
    Cd_controlb_retry(CdlReadN, (u_char *)&D_80098814, Cd_result);
}

void func_8001D078(u_char status, u_char *result)
{
    sint32 sector;

    Cd_wait = 0;
    if (status == CdlDataReady)
    {
        if (D_80098B38[D_80098998] == 0)
        {
            CdGetSector(D_800B5DB0 + D_80098998 * CD_SECTOR_BYTES, 3);
            sector = CdPosToInt((CdlLOC *)(D_800B5DB0 + D_80098998 * CD_SECTOR_BYTES));
            if (sector != D_80098A7C)
            {
                Cd_error_flags |= CD_ERR_SECTOR;
                goto read_error;
            }
            D_80098A7C = sector + 1;
            CdGetSector(D_800B5DB0 + D_80098998 * CD_SECTOR_BYTES, CD_SECTOR_WORDS);
            D_80098B38[D_80098998] = 1;
            D_80098998++;
            if (D_80098998 == CD_READ_BUFFER_COUNT)
            {
                D_80098998 = 0;
            }
            D_8009881C -= CD_SECTOR_BYTES;
            if (D_8009881C <= 0)
            {
                CdReadyCallback(NULL);
                Cd_control_retry(CdlPause, NULL, Cd_result);
                CdSyncCallback(Cd_sync_cb);
            }
        }
        else
        {
            Cd_status = 0x80;
            Cd_error_flags |= CD_ERR_BUFFER_FULL;
            goto stop_read;
        }
    }
    else
    {
        Cd_error_flags |= CD_ERR_READY;
    read_error:
        Cd_status = 0x80;
    stop_read:
        CdReadyCallback(NULL);
        CdSyncCallback(Cd_sync_cb);
        Cd_control_retry(CdlPause, NULL, Cd_result);
    }
}

void Cd_control_retry(u_char com, u_char *param, u_char *result)
{
    while (CdSync(1, result) == 0)
    {
    }

    while (CdControl(com, param, result) == 0)
    {
    }
}

void Cd_controlb_retry(u_char com, u_char *param, u_char *result)
{
    while (CdSync(1, result) == 0)
    {
    }

    while (CdControlB(com, param, result) == 0)
    {
    }
}

void Cd_set_mode(u_char mode)
{
    Cd_wait = 0;

    if (Cd_mode != mode)
    {
        if ((Cd_mode & CdlModeSpeed) != (mode & CdlModeSpeed))
        {
            Cd_wait = 2;
        }

        Cd_mode = mode;
        Cd_controlb_retry(CdlSetmode, &Cd_mode, Cd_result);
    }
}

void Cd_set_volume(uint8 vol)
{
    SOUND_WORK *sw = &Sound_work;

    if (Sound_work.flags & SOUND_FLAG_MONO)
    {
        // mono: both inputs to both outputs
        Sound_work.atv.val0 = vol;
        Sound_work.atv.val1 = vol;
        Sound_work.atv.val2 = vol;
        Sound_work.atv.val3 = vol;
    }
    else
    {
        // stereo: left to left, right to right
        Sound_work.atv.val0 = vol;
        Sound_work.atv.val1 = 0;
        Sound_work.atv.val2 = vol;
        Sound_work.atv.val3 = 0;
    }

    CdMix(&sw->atv);
}

void func_8001D414(sint32 arg1, sint32 arg2)
{
    Cd_cmd_write_ptr->type      = 4;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr->args.arg2 = arg2;
    Cd_cmd_write_ptr++;
}

void Cd_read_comb(sint32 arg1)
{
    Cd_cmd_write_ptr->type      = 6;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr++;
}

void func_8001D468(sint32 arg1, sint32 arg2)
{
    Cd_cmd_write_ptr->type      = 1;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr->args.arg2 = arg2;
    Cd_cmd_write_ptr++;
}

void func_8001D494(sint32 arg1, sint32 arg2, sint32 arg3)
{
    CD_CMD *p;
    CD_CMD *q;

    if (arg2 == 1)
    {
        for (p = &Cd_cmd_queue[1]; p < Cd_cmd_write_ptr; p++)
        {
            if (p->type == 2 && p->args.arg2 == 1)
            {
                for (q = p; q + 1 < Cd_cmd_write_ptr; q++)
                {
                    q->type                  = q[1].type;
                    q->args.arg1             = q[1].args.arg1;
                    q->args.arg2             = q[1].args.arg2;
                    *(uint32 *)&q->args.arg3 = *(uint32 *)&q[1].args.arg3;
                }
                Cd_cmd_write_ptr--;
            }
        }
    }

    Cd_cmd_write_ptr->type      = 2;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr->args.arg2 = arg2;
    // This command uses the complete final word, including the movie argument's padding.
    *(uint32 *)&Cd_cmd_write_ptr->args.arg3 = arg3;
    Cd_cmd_write_ptr++;
}

// As in func_8001D648: `arg &= 0xFFFF` keeps retail's three shifts and one table pointer serves
// both rows. The type store written through a plain word pointer (not the struct field) keeps
// D_800989B8's store above it; the final word through CD_CMD_RAW lets the exec-pointer load move
// above it.
void func_8001D58C(uint32 arg)
{
    uint32 hi;
    uint32 mid;
    uint32 rep;
    sint32 *tbl;
    CD_CMD *cmd;

    cmd            = Cd_cmd_write_ptr;
    hi             = (arg >> 28) & 3;
    D_800989B8     = arg;
    *(sint32 *)cmd = 4;
    mid            = (arg << 4) >> 20;
    rep            = arg & 0x40000000;
    arg &= 0xFFFF;
    tbl                         = D_80088F9C[hi];
    cmd->args.arg1              = tbl[mid];
    tbl                         = (sint32 *)D_80088EF8[hi][mid];
    cmd->args.arg2              = ((CD_POS *)tbl)[arg].offset;
    ((CD_CMD_RAW *)cmd)->arg[2] = ((CD_POS *)tbl)[arg].unk4 | rep;
    D_800989BC                  = Cd_cmd_exec_ptr->args.arg2;
    D_800989C0                  = *(uint32 *)&Cd_cmd_exec_ptr->args.arg3;
    Cd_cmd_write_ptr            = cmd + 1;
}

// `arg &= 0xFFFF` between the middle index and its first use keeps retail's three shifts (combine
// can't fold them across the redefinition). The one table pointer reused for the file row and then
// the offset row gives retail's registers.
void func_8001D648(uint32 arg)
{
    uint32 hi;
    uint32 mid;
    sint32 *tbl;
    sint32 file;

    hi  = arg >> 28;
    tbl = D_80088F9C[hi];
    mid = (arg << 4) >> 20;
    arg &= 0xFFFF;
    file = tbl[mid];
    tbl  = (sint32 *)D_80088EF8[hi][mid];
    hi   = Cd_file_tbl[file].sector + (((CD_POS *)tbl)[arg].offset & 0xFFFFFF);
    func_8001D6D8(hi);
}

void func_8001D6D8(sint32 sector)
{
    CD_CMD *p;
    CD_CMD *q;

    for (p = &Cd_cmd_queue[1]; p < Cd_cmd_write_ptr; p++)
    {
        if (p->type == 7)
        {
            for (q = p; q + 1 < Cd_cmd_write_ptr; q++)
            {
                q->type                  = q[1].type;
                q->args.arg1             = q[1].args.arg1;
                q->args.arg2             = q[1].args.arg2;
                *(uint32 *)&q->args.arg3 = *(uint32 *)&q[1].args.arg3;
            }
            Cd_cmd_write_ptr--;
        }
    }

    Cd_cmd_write_ptr->type      = 7;
    Cd_cmd_write_ptr->args.arg2 = sector;
    Cd_cmd_write_ptr++;
}

void func_8001D7AC(sint32 index)
{
    func_8001D6D8(Cd_file_tbl[index].sector);
}

void Cd_read_sync(void)
{
    while (Cd_cmd_write_ptr != Cd_cmd_queue)
    {
        Thread_wait(1);
    }
}

sint32 Cd_read_sync2(void)
{
    return Cd_cmd_write_ptr != Cd_cmd_queue;
}
