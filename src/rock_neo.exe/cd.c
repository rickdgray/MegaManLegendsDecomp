#include "common.h"
#include "system.h"
#include "sound.h"
#include "cd.h"
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
    Cd_xa_state = CD_XA_OFF;
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

            Cd_read_start_buf(Cd_cmd_exec_ptr->args.arg1, Cd_cmd_exec_ptr->args.arg2);
            D_800988D0 = 0;
            Cd_wait    = 0;
            Cd_cmd_routine++;
            // fall through
        case 3:
            Cd_wait++;

            if (Cd_wait == CD_CMD_TIMEOUT)
            {
                Cd_error_flags |= CD_ERR_CMD_TIMEOUT;
                break;
            }

            if (Cd_status == 0)
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
            D_800988D0 = 1;
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
            D_800988D0 = 1;
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

void cd_cmd_subcmd(void)
{
    cd_subcmd_tbl[Cd_cmd_exec_ptr->args.arg2]();
}

void cd_cmd_xa_play(void)
{
    CdlLOC loc;
    CdlFILTER filter;
    sint16 i;
    CD_XA_CMD *cmd;

    switch (Cd_cmd_routine)
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
            if (Cd_wait != 0)
            {
                Cd_wait--;
                break;
            }

            Cd_status      = 0;
            Cd_error_flags = 0;
            Cd_sync_done   = Cd_status;

            if (Cd_xa_state != CD_XA_PAUSED)
            {
                cmd = (CD_XA_CMD *)Cd_cmd_exec_ptr;
                filter.file = CD_XA_FILE_NO;
                filter.chan = cmd->start.b.chan & CD_XA_CHAN_MASK;
                D_800989B0  = Cd_file_tbl[cmd->file].sector + (cmd->end & CD_SECTOR_MASK);
                CdIntToPos(Cd_file_tbl[cmd->file].sector + (cmd->start.offset & CD_SECTOR_MASK), &loc);
                Cd_controlb_retry(CdlSetfilter, (u_char *)&filter, Cd_result);
                Cd_controlb_retry(CdlSetloc, (u_char *)&loc, Cd_result);
                Cd_controlb_retry(CdlReadS, 0, Cd_result);
                Cd_wait    = 0;
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", cd_cmd_read_comb);

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
                D_800988D0 = 0;
                CdSyncCallback(Cd_seek_sync_cb);
                CdIntToPos(Cd_cmd_exec_ptr->args.arg2, &loc);
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
        Cd_sync_done   = 0;
        Cd_mode        = 0;
        Cd_error_flags = 0;
        D_800989C8     = 0;
        Cd_cmd_routine = 0;
        CdSyncCallback(0);
        CdReadyCallback(0);

        while (CdReset(0) == 0)
        {
        }
    }

    if (D_800988D0 == 2)
    {
        Cd_controlb_retry(CdlNop, NULL, Cd_result);
        Cd_stat = Cd_result[0];

        if (Cd_result[0] & CdlStatRead)
        {
            Cd_controlb_retry(CdlGetlocP, NULL, Cd_result);
            D_800989D8 = CdPosToInt((CdlLOC *)&Cd_result[5]); // absolute position

            if (D_800989D8 >= D_800989B0)
            {
                if (D_800989C0 & 0x40000000)
                {
                    Cd_xa_play_id(D_800989B8);
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

#ifdef NON_MATCHING
void Cd_cmd_dequeue(void)
{
    CD_CMD *p;

    for (p = Cd_cmd_queue; p->type != CD_CMD_END; p++)
    {
        p->type = p[1].type;
        p->args = p[1].args;
    }

    p->type        = CD_CMD_END;
    D_800989C8     = 0;
    Cd_cmd_routine = 0;
    Cd_cmd_write_ptr--;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", Cd_cmd_dequeue);
#endif

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
    Cd_stat = 0;
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

void Cd_read_start_buf(sint32 file, sint32 arg2)
{
    Cd_status      = 1;
    Cd_xa_state     = CD_XA_OFF;
    Cd_error_flags = 0;
    Cd_wait        = 0;
    Cd_sync_done   = 0;
    Cd_file_sector     = Cd_file_tbl[file].sector;
    CdIntToPos(Cd_file_sector, &Cd_loc);
    D_800987A4 = (uint8 *)arg2;
    D_8009881C = Cd_file_tbl[file].size;
    CdReadyCallback(Cd_ready_cb_buf);
    Cd_controlb_retry(CdlSetloc, (u_char *)&Cd_loc, Cd_result);
    Cd_controlb_retry(CdlReadN, NULL, Cd_result);
}

void Cd_ready_cb_buf(u_char status, u_char *result)
{
    sint32 pos;
    sint32 n;
    uint8 *src;

    Cd_wait = 0;

    if (status == CdlDataReady)
    {
        CdGetSector(Cd_ring_buf, 3); // sector header
        pos = CdPosToInt((CdlLOC *)Cd_ring_buf);

        if (pos != Cd_file_sector)
        {
            Cd_error_flags |= CD_ERR_WRONG_SECTOR;
            goto set_status;
        }

        Cd_file_sector = pos + 1;

        if (D_8009881C >= 0x800)
        {
            CdGetSector(D_800987A4, 0x200);

            if (D_800989C8 == 0)
            {
                if (Cd_file_tbl[Cd_cmd_exec_ptr->args.arg1].unk8 != *(sint32 *)D_800987A4)
                {
                    Cd_error_flags |= CD_ERR_BAD_DATA;
                    goto set_status;
                }

                D_800989C8 = status;
            }

            D_8009881C -= 0x800;

            if (D_8009881C == 0)
            {
                CdReadyCallback(0);
                CdSyncCallback(Cd_sync_cb);
                Cd_control_retry(CdlPause, NULL, Cd_result);
            }
            else
            {
                D_800987A4 += 0x800;
            }
        }
        else
        {
            // last, partial sector: copy the remaining bytes
            CdGetSector(Cd_ring_buf, 0x200);

            for (n = D_8009881C, src = Cd_ring_buf[0]; n != 0; n--)
            {
                *D_800987A4 = *src++;
                D_800987A4++;
            }

            CdSyncCallback(Cd_sync_cb);
            Cd_control_retry(CdlPause, NULL, Cd_result);
            goto stop;
        }
    }
    else
    {
        Cd_error_flags |= CD_ERR_READY;
    set_status:
        Cd_status = 0x80;
    stop:
        CdReadyCallback(0);
    }
}

void Cd_read_start_ring(sint32 file)
{
    uint8 *p;
    sint32 i;

    for (i = 9, p = &Cd_ring_ready[9]; i >= 0; i--)
    {
        *p-- = 0;
    }

    Cd_status      = 1;
    Cd_xa_state     = CD_XA_OFF;
    Cd_error_flags = 0;
    Cd_wait        = 0;
    Cd_sync_done   = 0;
    D_80098998     = 0;
    Cd_file_sector     = Cd_file_tbl[file].sector;
    CdIntToPos(Cd_file_sector, &Cd_loc);
    D_8009881C = Cd_file_tbl[file].size;
    CdReadyCallback(Cd_ready_cb_ring);
    Cd_controlb_retry(CdlReadN, (u_char *)&Cd_loc, Cd_result);
}

void Cd_ready_cb_ring(u_char status, u_char *result)
{
    sint32 pos;

    Cd_wait = 0;

    if (status == CdlDataReady)
    {
        if (Cd_ring_ready[D_80098998] == 0)
        {
            CdGetSector(Cd_ring_buf[D_80098998], 3); // sector header
            pos = CdPosToInt((CdlLOC *)Cd_ring_buf[D_80098998]);

            if (pos != Cd_file_sector)
            {
                Cd_error_flags |= CD_ERR_WRONG_SECTOR;
                goto set_status;
            }
            else
            {
                Cd_file_sector = pos + 1;
                CdGetSector(Cd_ring_buf[D_80098998], 0x200);
                Cd_ring_ready[D_80098998] = 1;
                D_80098998++;

                if (D_80098998 == 10)
                {
                    D_80098998 = 0;
                }

                D_8009881C -= 0x800;

                if (D_8009881C <= 0)
                {
                    CdReadyCallback(0);
                    Cd_control_retry(CdlPause, NULL, Cd_result);
                    CdSyncCallback(Cd_sync_cb);
                }
            }
        }
        else
        {
            Cd_status = 0x80;
            Cd_error_flags |= CD_ERR_RING_FULL;
            goto stop;
        }
    }
    else
    {
        Cd_error_flags |= CD_ERR_READY;
    set_status:
        Cd_status = 0x80;
    stop:
        CdReadyCallback(0);
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

void Cd_xa_play(sint32 arg1, sint32 arg2)
{
    Cd_cmd_write_ptr->type      = CD_CMD_XA_PLAY;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr->args.arg2 = arg2;
    Cd_cmd_write_ptr++;
}

void Cd_read_comb(sint32 arg1)
{
    Cd_cmd_write_ptr->type      = CD_CMD_READ_COMB;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr++;
}

void Cd_read(sint32 arg1, sint32 arg2)
{
    Cd_cmd_write_ptr->type      = CD_CMD_READ;
    Cd_cmd_write_ptr->args.arg1 = arg1;
    Cd_cmd_write_ptr->args.arg2 = arg2;
    Cd_cmd_write_ptr++;
}

#ifdef NON_MATCHING
void Cd_subcmd(sint32 arg1, sint32 arg2, uint32 arg3)
{
    CD_CMD *p;
    CD_CMD *end;
    CD_CMD *q;

    // with arg2 == 1: drop any queued type-2 command with arg2 == 1 (never the one being run)
    if (arg2 == CD_SUBCMD_XA_STOP)
    {
        for (p = &Cd_cmd_queue[1]; p < Cd_cmd_write_ptr; p++)
        {
            if (p->type == CD_CMD_SUBCMD && p->args.arg2 == CD_SUBCMD_XA_STOP)
            {
                end = Cd_cmd_write_ptr;

                for (q = p; q + 1 < end; q++)
                {
                    q->type = q[1].type;
                    q->args = q[1].args;
                }

                Cd_cmd_write_ptr--;
            }
        }
    }

    Cd_cmd_write_ptr->type                  = CD_CMD_SUBCMD;
    Cd_cmd_write_ptr->args.arg1             = arg1;
    Cd_cmd_write_ptr->args.arg2             = arg2;
    *(uint32 *)&Cd_cmd_write_ptr->args.arg3 = arg3;
    Cd_cmd_write_ptr++;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", Cd_subcmd);
#endif

#ifdef NON_MATCHING
void Cd_xa_play_id(uint32 arg)
{
    uint32 hi  = (arg >> 28) & 3;
    uint32 mid = (arg << 4) >> 20;
    uint32 lo  = arg & 0xFFFF;
    CD_POS *pos;

    D_800989B8                              = arg;
    Cd_cmd_write_ptr->type                  = CD_CMD_XA_PLAY;
    Cd_cmd_write_ptr->args.arg1             = D_80088F9C[hi][mid];
    pos                                     = &D_80088EF8[hi][mid][lo];
    Cd_cmd_write_ptr->args.arg2             = pos->offset;
    *(uint32 *)&Cd_cmd_write_ptr->args.arg3 = pos->unk4 | (arg & 0x40000000);
    D_800989BC                              = Cd_cmd_exec_ptr->args.arg2;
    Cd_cmd_write_ptr++;
    D_800989C0 = *(uint32 *)&Cd_cmd_exec_ptr->args.arg3;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", Cd_xa_play_id);
#endif

#ifdef NON_MATCHING
void func_8001D648(uint32 arg)
{
    uint32 hi  = arg >> 28;
    uint32 mid = (arg << 4) >> 20;
    uint32 lo  = arg & 0xFFFF;

    Cd_seek(Cd_file_tbl[D_80088F9C[hi][mid]].sector +
                  (D_80088EF8[hi][mid][lo].offset & 0xFFFFFF));
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001D648);
#endif

#ifdef NON_MATCHING
void Cd_seek(sint32 sector)
{
    CD_CMD *p;
    CD_CMD *q;
    CD_CMD *end;

    // drop any command of type 7 already queued (never the one being run), then queue this one
    for (p = &Cd_cmd_queue[1]; p < Cd_cmd_write_ptr; p++)
    {
        if (p->type == CD_CMD_SEEK)
        {
            end = Cd_cmd_write_ptr;

            for (q = p; q + 1 < end; q++)
            {
                q->type = q[1].type;
                q->args = q[1].args;
            }

            Cd_cmd_write_ptr--;
        }
    }

    Cd_cmd_write_ptr->type      = CD_CMD_SEEK;
    Cd_cmd_write_ptr->args.arg2 = sector;
    Cd_cmd_write_ptr++;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", Cd_seek);
#endif

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
