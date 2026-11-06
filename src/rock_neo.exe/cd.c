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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001B4CC);

void func_8001B63C(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001B644);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001B6FC);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001B89C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001BB4C);

void func_8001C7F0(void)
{
    Cd_cmd_routine++;
    CdSyncCallback(0);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001C824);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001C95C);

#ifdef NON_MATCHING
void Cd_cmd_dequeue(void)
{
    CD_CMD *p;

    for (p = Cd_cmd_queue; p->type != 0; p++)
    {
        p->type = p[1].type;
        p->args = p[1].args;
    }

    p->type        = 0;
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001CC7C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001CD60);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001CF98);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001D078);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001D494);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001D58C);

#ifdef NON_MATCHING
void func_8001D648(uint32 arg)
{
    uint32 hi  = arg >> 28;
    uint32 mid = (arg << 4) >> 20;
    uint32 lo  = arg & 0xFFFF;

    func_8001D6D8(Cd_file_tbl[D_80088F9C[hi][mid]].sector +
                  (D_80088EF8[hi][mid][lo].offset & 0xFFFFFF));
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001D648);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/cd", func_8001D6D8);

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
