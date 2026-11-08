#include "common.h"
#include "system.h"
#include "sound.h"
#include "cd.h"
#include "game.h"
#include "vram.h"
#include "fastmem.h"
#include "psyq/libgpu.h"
#include "psyq/libsnd.h"
#include "psyq/libcd.h"

void Cd_init(void)
{
    sint32 i;

    while (CdInit() == 0)
    {
    }

    Cd_muted      = 0; // stored twice in the original; both needed for the match
    Cd_ring_write = 0;
    Cd_status     = CD_STATUS_IDLE;
    Cd_xa_state   = CD_XA_OFF;
    Cd_mode       = 0;
    D_80098AA0    = 0;
    Cd_muted      = 0; // stored twice in the original; both needed for the match

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
    Cd_head_checked  = 0;
    Cd_cmd_routine   = 0;
    Cd_play_mode     = 0;
}

void cd_cmd_nop(void)
{
}

void cd_cmd_read(void)
{
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

            Cd_set_mode(CdlModeSpeed | CdlModeSize1);
            Cd_cmd_routine++;
            // fall through
        case 2:
            if (Cd_wait != 0)
            {
                Cd_wait--;
                break;
            }

            Cd_read_start_buf(Cd_cmd_exec_ptr->args.read.file, Cd_cmd_exec_ptr->args.read.buf);
            Cd_play_mode = 0;
            Cd_wait      = 0;
            Cd_cmd_routine++;
            // fall through
        case 3:
            Cd_wait++;

            if (Cd_wait == CD_CMD_TIMEOUT)
            {
                Cd_error_flags |= CD_ERR_CMD_TIMEOUT;
                break;
            }

            if (Cd_status == CD_STATUS_IDLE)
            {
                Cd_cmd_dequeue();
            }

            break;
    }
}

void cd_subcmd_nop(void)
{
}

void cd_subcmd_xa_stop(void)
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
            Cd_play_mode = 1;
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done)
            {
                Cd_xa_state = CD_XA_STOPPED;
                Cd_cmd_dequeue();
            }
            break;
    }
}

void cd_subcmd_xa_pause(void)
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
            Cd_play_mode = 1;
            Cd_cmd_routine++;
            // fall through
        case 1:
            if (Cd_sync_done)
            {
                Cd_xa_state = CD_XA_PAUSED;
                Cd_cmd_dequeue();
            }
            break;
    }
}

void cd_subcmd_mute(void)
{
    sint32 i;
    uint16 tmp;

    for (i = CD_VOL_MAX; i > 0; i--)
    {
        Cd_set_volume(i);
    }

    Sound_work.flags |= SOUND_FLAG_CD_OFF;

    if (Cd_muted)
    {
        Cd_muted              = 0;
        Sound_work.serial_vol = Cd_mute_save;
    }
    else
    {
        tmp                   = Sound_work.serial_vol;
        Sound_work.serial_vol = 0;
        Cd_muted              = 1;
        Cd_mute_save          = tmp;
    }

    Cd_cmd_dequeue();
}

void cd_cmd_subcmd(void)
{
    cd_subcmd_tbl[Cd_cmd_exec_ptr->args.subcmd.sub]();
}

void cd_cmd_xa_play(void)
{
    CdlLOC loc;
    CdlFILTER filter;
    sint16 i;
    CD_XA_ARGS *cmd;

    switch (Cd_cmd_routine)
    {
        case 0:
            if (Cd_sync_done == 0)
            {
                Cd_stop();
            }

            Cd_play_mode = 2;
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
            if (Cd_wait != 0)
            {
                Cd_wait--;
                break;
            }

            Cd_status      = CD_STATUS_IDLE;
            Cd_error_flags = 0;
            Cd_sync_done   = Cd_status;

            if (Cd_xa_state != CD_XA_PAUSED)
            {
                cmd              = &Cd_cmd_exec_ptr->args.xa;
                filter.file      = CD_XA_FILE_NO;
                filter.chan      = cmd->start.b.chan & CD_XA_CHAN_MASK;
                Cd_xa_end_sector = Cd_file_tbl[cmd->file].sector + (cmd->end & CD_SECTOR_MASK);
                CdIntToPos(Cd_file_tbl[cmd->file].sector + (cmd->start.offset & CD_SECTOR_MASK),
                           &loc);
                Cd_controlb_retry(CdlSetfilter, (u_char *)&filter, Cd_result);
                Cd_controlb_retry(CdlSetloc, (u_char *)&loc, Cd_result);
                Cd_controlb_retry(CdlReadS, 0, Cd_result);
                Cd_wait = 0;
                Cd_stat = Cd_result[0];
            }

            Cd_cmd_routine++;
            // fall through
        case 3:
            if (!(Cd_stat & CdlStatRead))
            {
                Cd_wait++;

                if (Cd_wait >= CD_STREAM_TIMEOUT)
                {
                    Cd_error_flags |= CD_ERR_TIMEOUT;
                }

                break;
            }

            for (i = 0; i < CD_VOL_MAX; i++)
            {
                Cd_set_volume(i);
            }

            Cd_xa_state = CD_XA_PLAYING;
            Sound_work.flags &= ~SOUND_FLAG_CD_OFF;
            Cd_cmd_dequeue();
            break;
    }
}

#ifdef NON_MATCHING
void cd_cmd_read_comb(void)
{
    CD_COMB_HEAD *head;
    RECT *rect;
    uint8 *buf;
    uint8 *src;
    uint8 *dst;
    uint32 row;
    uint32 bit;
    uint32 row2;
    uint32 bit2;

    switch (Cd_cmd_routine)
    {
        case 0: // stop the drive if busy
            if (Cd_sync_done == 0)
            {
                Cd_stop();
            }

            Cd_cmd_routine++;
            // fall through
        case 1: // double speed, whole sectors
            if (Cd_sync_done == 0)
            {
                break;
            }

            Cd_set_mode(CdlModeSpeed | CdlModeSize1);
            Cd_cmd_routine++;
            // fall through
        case 2: // start the read into the ring
            if (Cd_wait != 0)
            {
                Cd_wait--;
                break;
            }

            Cd_read_start_ring(Cd_cmd_exec_ptr->args.read.file);
            Cd_play_mode = 0;
            Cd_ring_read = 0;
            Cd_wait      = 0;
            Cd_cmd_routine++;
            // fall through
        case 3: // take the sectors that have arrived
            Cd_wait++;

            if (Cd_wait == CD_CMD_TIMEOUT)
            {
                Cd_error_flags |= CD_ERR_CMD_TIMEOUT;
                break;
            }

            // Read every filled ring slot. Cd_head_checked is 0 while a header sector is
            // expected, then the entry's type + 1 while its data sectors arrive.
            while (Cd_ring_ready[Cd_ring_read] == 1)
            {
                switch ((uint32)Cd_head_checked)
                {
                    case 0: // a header sector: start an entry
                        // buf and head are the same sector: the original reads the first
                        // three words and the data through one pointer, the arguments
                        // through another (head lives across calls, buf doesn't)
                        buf          = Cd_ring_buf[Cd_ring_read];
                        Cd_comb_type = ((CD_COMB_HEAD *)buf)->type;

                        if (Cd_comb_type == CD_COMB_END)
                        {
                            Cd_cmd_routine = 4;
                            return;
                        }

                        Cd_comb_work.size  = ((CD_COMB_HEAD *)buf)->size;
                        Cd_comb_work.count = ((CD_COMB_HEAD *)buf)->count;
                        head               = (CD_COMB_HEAD *)buf;

                        switch (Cd_comb_type)
                        {
                            case CD_COMB_DATA:
                                Cd_comb_work.u.data.dest = (uint8 *)head->arg[0];
                                Cd_comb_work.count--;
                                break;

                            case CD_COMB_TIM:
                                rect                      = &Cd_comb_rect[0];
                                Cd_comb_work.u.tim.clut_x = head->arg[0];
                                Cd_comb_work.u.tim.clut_y = head->arg[1];
                                Cd_comb_work.u.tim.clut_w = head->arg[2];
                                Cd_comb_work.u.tim.clut_h = head->arg[3];
                                Cd_comb_work.u.tim.x      = head->arg[4];
                                Cd_comb_work.u.tim.y      = head->arg[5];
                                Cd_comb_work.u.tim.w      = head->arg[6];
                                Cd_comb_work.u.tim.h      = head->arg[7];
                                Cd_comb_work.u.tim.col = Cd_comb_work.u.tim.row = 0;

                                if (Cd_comb_work.u.tim.clut_x != -1)
                                {
                                    if (head->arg[0] < 0x140)
                                    {
                                        CLUT_BUF_ROW(row, head->arg[1]);
                                        Mem_copy16((u_long *)(buf + 0x100),
                                                   &Clut_buf[head->arg[0] + (row << 8)],
                                                   head->arg[3] * head->arg[2] / 16 * 2);
                                        CLUT_BUF_ROW(bit, head->arg[1]);
                                        Clut_buf_dirty |= 1 << bit;
                                    }
                                    else
                                    {
                                        rect->x = head->arg[0];
                                        rect->y = head->arg[1];
                                        rect->w = head->arg[2];
                                        rect->h = head->arg[3];
                                        LoadImage(rect, (u_long *)(buf + 0x100));
                                    }
                                }

                                rect->w = CD_COMB_TILE_SIZE;
                                rect->h = CD_COMB_TILE_SIZE;
                                Cd_comb_work.count--;
                                break;

                            case CD_COMB_TILES:
                                Cd_comb_work.u.tiles.x    = head->arg[0];
                                Cd_comb_work.u.tiles.y    = head->arg[1];
                                Cd_comb_work.u.tiles.cols = head->arg[2];
                                Cd_comb_work.u.tiles.rows = head->arg[3];
                                Cd_comb_work.u.tiles.col = Cd_comb_work.u.tiles.row = 0;
                                Cd_comb_rect[0].w = CD_COMB_TILE_SIZE;
                                Cd_comb_rect[0].h = CD_COMB_TILE_SIZE;
                                break;

                            case CD_COMB_IMAGE:
                            case CD_COMB_IMAGE2:
                            case CD_COMB_IMAGE3:
                                if (head->arg[0] < 0x100)
                                {
                                    CLUT_BUF_ROW(row2, head->arg[1]);
                                    Mem_copy16((u_long *)(buf + 0x100),
                                               &Clut_buf[head->arg[0] + (row2 << 8)],
                                               head->arg[3] * head->arg[2] / 16 * 2);
                                    CLUT_BUF_ROW(bit2, head->arg[1]);
                                    Clut_buf_dirty |= 1 << bit2;
                                }
                                else
                                {
                                    rect    = &Cd_comb_rect[0];
                                    rect->x = head->arg[0];
                                    rect->y = head->arg[1];

                                    if (Cd_comb_type != CD_COMB_IMAGE3)
                                    {
                                        rect->w = head->arg[2];
                                        rect->h = head->arg[3];
                                    }
                                    else
                                    {
                                        rect->w = 64;
                                        rect->h = head->arg[2] * head->arg[3] / 64;
                                    }

                                    LoadImage(rect, (u_long *)(buf + 0x100));
                                }

                                Cd_head_checked = 0;
                                goto next;

                            case CD_COMB_VAB:
                                Cd_comb_work.u.vab.slot      = head->arg[0];
                                Cd_comb_work.u.vab.num       = head->arg[1];
                                Cd_comb_work.u.vab.sbaddr    = head->arg[2];
                                Cd_comb_work.u.vab.head_size = head->arg[3];
                                Cd_comb_work.u.vab.dest =
                                    VAB_HEAD_BUF + head->arg[0] * VAB_HEAD_SIZE;
                                Cd_comb_work.u.vab.load = 1;

                                if (head->arg[0] == 4)
                                {
                                    if (Game_work.vab[4].unk2 == head->arg[1])
                                    {
                                        Cd_comb_work.u.vab.load = 0;
                                    }

                                    if (D_80098958 & 0x800)
                                    {
                                        Cd_comb_work.u.vab.load = 1;
                                        func_8001B33C();
                                    }
                                }

                                if (Cd_comb_work.u.vab.load == 1)
                                {
                                    Game_work.vab[head->arg[0]].unk2 = head->arg[1];
                                    Game_work.vab[head->arg[0]].unk4 = head->arg[2];

                                    if (Game_work.vab[head->arg[0]].vab_id != -1)
                                    {
                                        SsVabClose(Game_work.vab[head->arg[0]].vab_id);
                                    }
                                }

                                Cd_comb_work.count--;
                                break;

                            case CD_COMB_SOUND:
                                Cd_comb_work.u.sound.dest = D_80098AD0[head->arg[0]].data =
                                    SOUND_DATA_BUF + head->arg[2];
                                Cd_comb_work.u.sound.load = 0;

                                if (D_80098AD0[head->arg[0]].unk0 != head->arg[1])
                                {
                                    D_80098AD0[head->arg[0]].unk0 = head->arg[1];
                                    Cd_comb_work.u.sound.load     = 1;
                                }
                                break;

                            case CD_COMB_SOUND2:
                                Cd_comb_work.u.sound2.dest = D_80098AD0[head->arg[0]].data =
                                    SOUND_DATA_BUF + head->arg[3];
                                Cd_comb_work.u.sound2.load = 0;

                                if (D_80098AD0[head->arg[0]].unk0 != head->arg[1])
                                {
                                    D_80098AD0[head->arg[0]].unk0 = head->arg[1];
                                    D_80098AD0[head->arg[0]].unk1 = head->arg[2];
                                    Cd_comb_work.u.sound2.load    = 1;
                                }
                                break;
                        }

                        Cd_head_checked = Cd_comb_type + 1;
                        break;

                    case CD_COMB_DATA + 1: // copy to memory
                        if (Cd_comb_work.size >= CD_SECTOR_SIZE)
                        {
                            Mem_copy32(Cd_ring_buf[Cd_ring_read], Cd_comb_work.u.data.dest,
                                       CD_SECTOR_SIZE / 32);
                            Cd_comb_work.size -= CD_SECTOR_SIZE;
                            Cd_comb_work.u.data.dest += CD_SECTOR_SIZE;
                        }
                        else
                        {
                            src = Cd_ring_buf[Cd_ring_read];
                            dst = Cd_comb_work.u.data.dest;

                            while (Cd_comb_work.size != 0)
                            {
                                *dst++ = *src++;
                                Cd_comb_work.size--;
                            }
                        }

                        if (--Cd_comb_work.count == 0)
                        {
                            Cd_head_checked = 0;
                        }
                        break;

                    case CD_COMB_TIM + 1: // load one image tile
                        rect    = &Cd_comb_rect[0];
                        rect->x = Cd_comb_work.u.tim.x + Cd_comb_work.u.tim.col * CD_COMB_TILE_SIZE;
                        rect->y = Cd_comb_work.u.tim.y + Cd_comb_work.u.tim.row * CD_COMB_TILE_SIZE;
                        LoadImage(rect, (u_long *)Cd_ring_buf[Cd_ring_read]);

                        if (++Cd_comb_work.u.tim.col == Cd_comb_work.u.tim.w / CD_COMB_TILE_SIZE)
                        {
                            Cd_comb_work.u.tim.col = 0;

                            if (++Cd_comb_work.u.tim.row ==
                                Cd_comb_work.u.tim.h / CD_COMB_TILE_SIZE)
                            {
                                Cd_head_checked = 0;
                            }
                        }
                        break;

                    case CD_COMB_TILES + 1: // load one image tile
                        rect = &Cd_comb_rect[0];
                        rect->x =
                            Cd_comb_work.u.tiles.x + Cd_comb_work.u.tiles.col * CD_COMB_TILE_SIZE;
                        rect->y =
                            Cd_comb_work.u.tiles.y + Cd_comb_work.u.tiles.row * CD_COMB_TILE_SIZE;
                        LoadImage(rect, (u_long *)Cd_ring_buf[Cd_ring_read]);

                        if (++Cd_comb_work.u.tiles.col == Cd_comb_work.u.tiles.cols)
                        {
                            Cd_comb_work.u.tiles.col = 0;

                            if (++Cd_comb_work.u.tiles.row == Cd_comb_work.u.tiles.rows)
                            {
                                Cd_head_checked = 0;
                            }
                        }
                        break;

                    case CD_COMB_VAB + 1: // VAB header, then body
                        if (Cd_comb_work.u.vab.load == 0)
                        {
                            if (--Cd_comb_work.count == 0)
                            {
                                Cd_head_checked = 0;
                            }
                        }
                        else if (Cd_comb_work.u.vab.head_size >= CD_SECTOR_SIZE)
                        {
                            Mem_copy32(Cd_ring_buf[Cd_ring_read], Cd_comb_work.u.vab.dest,
                                       CD_SECTOR_SIZE / 32);
                            Cd_comb_work.u.vab.dest += CD_SECTOR_SIZE;
                            Cd_comb_work.u.vab.head_size -= CD_SECTOR_SIZE;
                        }
                        else if (Cd_comb_work.u.vab.head_size != 0)
                        {
                            Mem_copy4(Cd_ring_buf[Cd_ring_read], Cd_comb_work.u.vab.dest,
                                      Cd_comb_work.u.vab.head_size / 4);
                            Cd_comb_work.u.vab.head_size                  = 0;
                            Game_work.vab[Cd_comb_work.u.vab.slot].vab_id = SsVabOpenHeadSticky(
                                VAB_HEAD_BUF + Cd_comb_work.u.vab.slot * VAB_HEAD_SIZE,
                                Cd_comb_work.u.vab.slot, Cd_comb_work.u.vab.sbaddr);
                        }
                        else
                        {
                            if (SsVabTransBodyPartly(
                                    Cd_ring_buf[Cd_ring_read], CD_SECTOR_SIZE,
                                    Game_work.vab[Cd_comb_work.u.vab.slot].vab_id) ==
                                Game_work.vab[Cd_comb_work.u.vab.slot].vab_id)
                            {
                                Cd_head_checked = 0;
                            }

                            SsVabTransCompleted(SS_WAIT_COMPLETED);
                        }
                        break;

                    case CD_COMB_SOUND + 1: // copy if loading
                        if (Cd_comb_work.size >= CD_SECTOR_SIZE)
                        {
                            if (Cd_comb_work.u.sound.load)
                            {
                                Mem_copy32(Cd_ring_buf[Cd_ring_read], Cd_comb_work.u.sound.dest,
                                           CD_SECTOR_SIZE / 32);
                            }

                            Cd_comb_work.size -= CD_SECTOR_SIZE;
                            Cd_comb_work.u.sound.dest += CD_SECTOR_SIZE;
                        }
                        else
                        {
                            if (Cd_comb_work.u.sound.load)
                            {
                                src = Cd_ring_buf[Cd_ring_read];
                                dst = Cd_comb_work.u.sound.dest;

                                while (Cd_comb_work.size != 0)
                                {
                                    *dst++ = *src++;
                                    Cd_comb_work.size--;
                                }
                            }

                            Cd_head_checked = 0;
                        }
                        break;

                    case CD_COMB_SOUND2 + 1: // copy if loading
                        if (Cd_comb_work.size >= CD_SECTOR_SIZE)
                        {
                            if (Cd_comb_work.u.sound2.load)
                            {
                                Mem_copy32(Cd_ring_buf[Cd_ring_read], Cd_comb_work.u.sound2.dest,
                                           CD_SECTOR_SIZE / 32);
                            }

                            Cd_comb_work.size -= CD_SECTOR_SIZE;
                            Cd_comb_work.u.sound2.dest += CD_SECTOR_SIZE;
                        }
                        else
                        {
                            if (Cd_comb_work.u.sound2.load)
                            {
                                src = Cd_ring_buf[Cd_ring_read];
                                dst = Cd_comb_work.u.sound2.dest;

                                while (Cd_comb_work.size != 0)
                                {
                                    *dst++ = *src++;
                                    Cd_comb_work.size--;
                                }
                            }

                            Cd_head_checked = 0;
                        }
                        break;
                }
            next:
                Cd_ring_ready[Cd_ring_read] = 0;

                if (++Cd_ring_read == CD_RING_SLOTS)
                {
                    Cd_ring_read = 0;
                }
            }
            break;

        case 4: // CD_COMB_END reached
            Cd_cmd_dequeue();
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", cd_cmd_read_comb);
#endif

void Cd_seek_sync_cb(u_char status, u_char *result)
{
    Cd_cmd_routine++;
    CdSyncCallback(NULL);
}

void cd_cmd_seek(void)
{
    CdlLOC loc;

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
            if (Cd_sync_done)
            {
                Cd_play_mode = 0;
                CdSyncCallback(Cd_seek_sync_cb);
                CdIntToPos(Cd_cmd_exec_ptr->args.seek.sector, &loc);
                Cd_control_retry(CdlSeekL, (u_char *)&loc, Cd_result);
                Cd_wait = 0;
                Cd_cmd_routine++;
            }
            else
            {
                break;
            }
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

void Cd_cmd_exec(void)
{
    if (Cd_error_flags)
    {
        Cd_sync_done    = 0;
        Cd_mode         = 0;
        Cd_error_flags  = 0;
        Cd_head_checked = 0;
        Cd_cmd_routine  = 0;
        CdSyncCallback(NULL);
        CdReadyCallback(NULL);

        while (CdReset(0) == 0)
        {
        }
    }

    if (Cd_play_mode == CD_PLAY_XA)
    {
        Cd_controlb_retry(CdlNop, NULL, Cd_result);
        Cd_stat = Cd_result[0];

        if (Cd_result[0] & CdlStatRead)
        {
            Cd_controlb_retry(CdlGetlocP, NULL, Cd_result);
            Cd_xa_sector = CdPosToInt((CdlLOC *)&Cd_result[CD_GETLOCP_ABS]);

            if (Cd_xa_sector >= Cd_xa_end_sector)
            {
                if (Cd_xa_flags & CD_XA_LOOP)
                {
                    Cd_xa_play_id(Cd_xa_id);
                }
                else
                {
                    Cd_stop();
                }
            }
        }
    }

    cd_cmd_tbl[Cd_cmd_exec_ptr->type]();
}

void Cd_cmd_dequeue(void)
{
    CD_CMD *p = Cd_cmd_queue;

    while (p->type != CD_CMD_END)
    {
        p->type         = p[1].type;
        p->args.word[0] = p[1].args.word[0];
        p->args.word[1] = p[1].args.word[1];
        p->args.word[2] = p[1].args.word[2];
        p++;
    }

    p->type         = CD_CMD_END;
    Cd_head_checked = 0;
    Cd_cmd_routine  = 0;
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
    Cd_play_mode = 0;
    Cd_stat      = 0;
}

void Cd_sync_cb(u_char status, u_char *result)
{
    CdSyncCallback(0);

    if (status == CdlComplete)
    {
        Cd_sync_done = 1;
        Cd_status    = CD_STATUS_IDLE;
    }
    else
    {
        Cd_status = CD_STATUS_ERROR;
        Cd_error_flags |= CD_ERR_SYNC;
    }
}

void Cd_read_start_buf(sint32 file, uint8 *buf)
{
    Cd_status      = CD_STATUS_BUSY;
    Cd_xa_state    = CD_XA_OFF;
    Cd_error_flags = 0;
    Cd_wait        = 0;
    Cd_sync_done   = 0;
    Cd_file_sector = Cd_file_tbl[file].sector;
    CdIntToPos(Cd_file_sector, &Cd_loc);
    Cd_read_buf  = buf;
    Cd_read_left = Cd_file_tbl[file].size;
    CdReadyCallback(Cd_ready_cb_buf);
    Cd_controlb_retry(CdlSetloc, (u_char *)&Cd_loc, Cd_result);
    Cd_controlb_retry(CdlReadN, NULL, Cd_result);
}

// Same shape as Cd_ready_cb_ring, whose bytes require both labels: error: marks the read failed,
// stop: stops receiving sectors. (This function also matches without stop:.)
void Cd_ready_cb_buf(u_char status, u_char *result)
{
    sint32 pos;
    sint32 n;
    uint8 *src;

    Cd_wait = 0;

    if (status == CdlDataReady)
    {
        CdGetSector(Cd_ring_buf, CD_SECTOR_HEADER_WORDS);
        pos = CdPosToInt((CdlLOC *)Cd_ring_buf);

        if (pos != Cd_file_sector)
        {
            Cd_error_flags |= CD_ERR_WRONG_SECTOR;
            goto error;
        }

        Cd_file_sector = pos + 1;

        if (Cd_read_left >= CD_SECTOR_SIZE)
        {
            CdGetSector(Cd_read_buf, CD_SECTOR_WORDS);

            if (Cd_head_checked == 0)
            {
                if (Cd_file_tbl[Cd_cmd_exec_ptr->args.read.file].head != *(sint32 *)Cd_read_buf)
                {
                    Cd_error_flags |= CD_ERR_BAD_DATA;
                    goto error;
                }

                Cd_head_checked = status;
            }

            Cd_read_left -= CD_SECTOR_SIZE;

            if (Cd_read_left == 0)
            {
                CdReadyCallback(NULL);
                CdSyncCallback(Cd_sync_cb);
                Cd_control_retry(CdlPause, NULL, Cd_result);
            }
            else
            {
                Cd_read_buf += CD_SECTOR_SIZE;
            }
        }
        else
        {
            // last, partial sector: copy the remaining bytes
            CdGetSector(Cd_ring_buf, CD_SECTOR_WORDS);

            for (n = Cd_read_left, src = Cd_ring_buf[0]; n != 0; n--)
            {
                *Cd_read_buf = *src++;
                Cd_read_buf++;
            }

            CdSyncCallback(Cd_sync_cb);
            Cd_control_retry(CdlPause, NULL, Cd_result);
            goto stop;
        }
    }
    else
    {
        Cd_error_flags |= CD_ERR_READY;
        goto error;
    }

    return;

error:
    Cd_status = CD_STATUS_ERROR;
stop:
    CdReadyCallback(NULL);
}

void Cd_read_start_ring(sint32 file)
{
    uint8 *p;
    sint32 i;

    for (i = CD_RING_SLOTS - 1, p = &Cd_ring_ready[CD_RING_SLOTS - 1]; i >= 0; i--)
    {
        *p-- = 0;
    }

    Cd_status      = CD_STATUS_BUSY;
    Cd_xa_state    = CD_XA_OFF;
    Cd_error_flags = 0;
    Cd_wait        = 0;
    Cd_sync_done   = 0;
    Cd_ring_write  = 0;
    Cd_file_sector = Cd_file_tbl[file].sector;
    CdIntToPos(Cd_file_sector, &Cd_loc);
    Cd_read_left = Cd_file_tbl[file].size;
    CdReadyCallback(Cd_ready_cb_ring);
    Cd_controlb_retry(CdlReadN, (u_char *)&Cd_loc, Cd_result);
}

void Cd_ready_cb_ring(u_char status, u_char *result)
{
    sint32 pos;

    Cd_wait = 0;

    if (status == CdlDataReady)
    {
        if (Cd_ring_ready[Cd_ring_write] == 0)
        {
            CdGetSector(Cd_ring_buf[Cd_ring_write], CD_SECTOR_HEADER_WORDS);
            pos = CdPosToInt((CdlLOC *)Cd_ring_buf[Cd_ring_write]);

            if (pos != Cd_file_sector)
            {
                Cd_error_flags |= CD_ERR_WRONG_SECTOR;
                goto error;
            }

            Cd_file_sector = pos + 1;
            CdGetSector(Cd_ring_buf[Cd_ring_write], CD_SECTOR_WORDS);
            Cd_ring_ready[Cd_ring_write] = 1;
            Cd_ring_write++;

            if (Cd_ring_write == CD_RING_SLOTS)
            {
                Cd_ring_write = 0;
            }

            Cd_read_left -= CD_SECTOR_SIZE;

            if (Cd_read_left <= 0)
            {
                CdReadyCallback(NULL);
                Cd_control_retry(CdlPause, NULL, Cd_result);
                CdSyncCallback(Cd_sync_cb);
            }
        }
        else // every slot is still waiting to be read
        {
            Cd_status = CD_STATUS_ERROR;
            Cd_error_flags |= CD_ERR_RING_FULL;
            goto stop;
        }
    }
    else
    {
        Cd_error_flags |= CD_ERR_READY;
        goto error;
    }

    return;

error:
    Cd_status = CD_STATUS_ERROR;
stop:
    CdReadyCallback(NULL);
    CdSyncCallback(Cd_sync_cb);
    Cd_control_retry(CdlPause, NULL, Cd_result);
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

void Cd_xa_play(sint32 arg1, sint32 arg2)
{
    Cd_cmd_write_ptr->type                 = CD_CMD_XA_PLAY;
    Cd_cmd_write_ptr->args.xa.file         = arg1;
    Cd_cmd_write_ptr->args.xa.start.offset = arg2;
    Cd_cmd_write_ptr++;
}

void Cd_read_comb(sint32 arg1)
{
    Cd_cmd_write_ptr->type           = CD_CMD_READ_COMB;
    Cd_cmd_write_ptr->args.read.file = arg1;
    Cd_cmd_write_ptr++;
}

void Cd_read(sint32 file, uint8 *buf)
{
    Cd_cmd_write_ptr->type           = CD_CMD_READ;
    Cd_cmd_write_ptr->args.read.file = file;
    Cd_cmd_write_ptr->args.read.buf  = buf;
    Cd_cmd_write_ptr++;
}

void Cd_subcmd(sint32 arg1, sint32 arg2, uint32 arg3)
{
    CD_CMD *p;
    CD_CMD *q;

    // with arg2 == 1: drop any queued type-2 command with arg2 == 1 (never the one being run)
    if (arg2 == CD_SUBCMD_XA_STOP)
    {
        for (p = &Cd_cmd_queue[1]; p < Cd_cmd_write_ptr; p++)
        {
            if (p->type == CD_CMD_SUBCMD && p->args.subcmd.sub == CD_SUBCMD_XA_STOP)
            {
                for (q = p; q + 1 < Cd_cmd_write_ptr; q++)
                {
                    q->type         = q[1].type;
                    q->args.word[0] = q[1].args.word[0];
                    q->args.word[1] = q[1].args.word[1];
                    q->args.word[2] = q[1].args.word[2];
                }

                Cd_cmd_write_ptr--;
            }
        }
    }

    Cd_cmd_write_ptr->type             = CD_CMD_SUBCMD;
    Cd_cmd_write_ptr->args.subcmd.arg1 = arg1;
    Cd_cmd_write_ptr->args.subcmd.sub  = arg2;
    Cd_cmd_write_ptr->args.subcmd.arg3 = arg3;
    Cd_cmd_write_ptr++;
}

#ifdef NON_MATCHING
void Cd_xa_play_id(uint32 id)
{
    uint32 file  = CD_XA_FILE(id);
    uint32 num   = CD_XA_NUM(id);
    uint32 group = CD_XA_GROUP(id);
    CD_XA_TRACK *track;

    Cd_xa_id                        = id;
    Cd_cmd_write_ptr->type          = CD_CMD_XA_PLAY;
    Cd_cmd_write_ptr->args.xa.file  = Cd_xa_file_tbl[group][file];
    track                           = &Cd_xa_track_tbl[group][file][num];
    Cd_cmd_write_ptr->args.xa.start = track->start;
    Cd_cmd_write_ptr->args.xa.end   = track->end | (id & CD_XA_LOOP);
    // reads the running command, not the one just queued (bug in the original)
    Cd_xa_start = Cd_cmd_exec_ptr->args.xa.start.offset;
    Cd_cmd_write_ptr++;
    Cd_xa_flags = Cd_cmd_exec_ptr->args.xa.end;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", Cd_xa_play_id);
#endif

#ifdef NON_MATCHING
void Cd_xa_seek_id(uint32 id)
{
    uint32 group = CD_XA_GROUP(id);
    uint32 file  = CD_XA_FILE(id);
    uint32 num   = CD_XA_NUM(id);

    Cd_seek(Cd_file_tbl[Cd_xa_file_tbl[group][file]].sector +
            (Cd_xa_track_tbl[group][file][num].start.offset & CD_SECTOR_MASK));
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", Cd_xa_seek_id);
#endif

void Cd_seek(sint32 sector)
{
    CD_CMD *p;
    CD_CMD *q;

    // drop any seek already queued (never the one being run), then queue this one
    for (p = &Cd_cmd_queue[1]; p < Cd_cmd_write_ptr; p++)
    {
        if (p->type == CD_CMD_SEEK)
        {
            for (q = p; q + 1 < Cd_cmd_write_ptr; q++)
            {
                q->type         = q[1].type;
                q->args.word[0] = q[1].args.word[0];
                q->args.word[1] = q[1].args.word[1];
                q->args.word[2] = q[1].args.word[2];
            }

            Cd_cmd_write_ptr--;
        }
    }

    Cd_cmd_write_ptr->type             = CD_CMD_SEEK;
    Cd_cmd_write_ptr->args.seek.sector = sector;
    Cd_cmd_write_ptr++;
}

void func_8001D7AC(sint32 index)
{
    Cd_seek(Cd_file_tbl[index].sector);
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
