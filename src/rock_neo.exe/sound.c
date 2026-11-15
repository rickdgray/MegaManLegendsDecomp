#include "common.h"
#include "sound.h"
#include "cd.h"
#include "game.h"
#include "psyq/libsnd.h"
#include "psyq/libspu.h"
#include "psyq/libgte.h"
#include "player.h"
#include "scene.h"

// Called only from this file
sint32 pitch_interp(sint32 x, sint32 frac); // parked: only the NON_MATCHING branch defines it in C
void volume_update(void);

void func_800198C0(void)
{
    sint32 i;
    sint16 id;

    if (Sce_flag_test(6) != 0 && Sce_flag_test(0x2C) == 0)
    {
        id = 2;
    }
    else
    {
        id = 7;
    }
    for (i = 5; i >= 0; i--)
    {
        D_80082220[i] = id;
    }
}

void func_80019918(void)
{
    sint16 id;

    if ((Sce_flag_test(0x204) != 0 && Sce_flag_test(0x206) == 0) || (Sce_flag_test(0x212) != 0 && Sce_flag_test(0x213) == 0))
    {
        id = 0x39;
    }
    else
    {
        id = 7;
    }
    D_8008222C[0] = id;
}

void func_8001997C(void)
{
    if (Game_work.unk053 == 1)
    {
        D_80082274[0] = 0x29;
    }
    else
    {
        D_80082274[0] = 0x108;
    }
}

void func_800199A4(void)
{
    sint16 id;

    if (Game_work.unk053 < 4)
    {
        if (Game_work.unk053 > 0 && Sce_flag_test(0x30) == 0)
        {
            id = 0x16;
        }
        else
        {
            id = 0x108;
        }
    }
    else
    {
        id = 0x108;
    }
    D_80082278[0] = id;
}

void func_800199F8(void)
{
    sint32 i;
    sint16 id;

    if (Game_work.unk053 == 1)
    {
        id = 0x17;
    }
    else
    {
        id = 0x108;
    }
    for (i = 5; i >= 0; i--)
    {
        D_8008229C[i] = id;
    }
}

void func_80019A34(void)
{
    sint32 i;
    sint16 id;

    if (Game_work.unk053 == 1)
    {
        id = 0x17;
    }
    else
    {
        id = 0x108;
    }
    for (i = 4; i >= 0; i--)
    {
        D_800822A8[i] = id;
    }
}

void func_80019A70(void)
{
    if (Sce_flag_test(0x1E1) != 0)
    {
        D_800822C0[11] = 0x25;
    }
    else
    {
        D_800822C0[11] = 0x30;
    }
}

void func_80019AA4(void)
{
    if (Sce_flag_test(0x35) == 0)
    {
        D_800822F0[2] = D_800822F0[1] = 0xFFFF;
    }
    else
    {
        D_800822F0[2] = D_800822F0[1] = 0x2D;
    }
}

void func_80019AE0(void)
{
    if (Sce_flag_test(0x1E1) != 0)
    {
        D_8008220C[6] = 0x25;
    }
    else
    {
        D_8008220C[6] = 0x30;
    }
}

void Sound_stage_slot_set(sint32 which)
{
    sint8 stage;

    if (which == 0)
    {
        stage = Game_work.unk051;
    }
    else
    {
        stage = D_800C356F;
    }
    switch (stage % 3)
    {
        case 0:
            Sound_stage_slot_tbl[stage] = Sce_flag_test(0x616) ? 0xFFFF : 0x3A;
            break;
        case 1:
            Sound_stage_slot_tbl[stage] = Sce_flag_test(0x617) ? 0xFFFF : 0x3B;
            break;
        case 2:
            Sound_stage_slot_tbl[stage] = Sce_flag_test(0x68) ? 0xFFFF : 0x3C;
            break;
    }
}

#ifdef NON_MATCHING
void Sound_stage_check(void)
{
    sint32 changed;
    uint16 *list;
    uint16 id;

    if (Sound_stage_func_tbl[D_800C356E] != 0)
    {
        Sound_stage_func_tbl[D_800C356E](1);
    }
    list    = Sound_stage_id_tbl[D_800C356E];
    changed = 0;
    if (list != 0)
    {
        id = list[D_800C356F];
        if (id == 0xFFFF || Sound_stage_id_tbl[Game_work.unk050][Game_work.unk051] != id)
        {
            changed = 1;
        }
    }
    else
    {
        changed = 1;
    }
    if (changed)
    {
        Sound_fade_start(0x10);
        D_80098958 |= 0x800;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_stage_check);
#endif

#ifdef NON_MATCHING
void Sound_stage_play(void)
{
    uint16 *list;
    sint32 ok;
    uint16 id;

    if (Sound_stage_func_tbl[Game_work.unk050] != 0)
    {
        Sound_stage_func_tbl[Game_work.unk050](0);
    }
    list = Sound_stage_id_tbl[Game_work.unk050];
    id   = 0;
    ok   = 0;
    if (list != 0)
    {
        id = list[Game_work.unk051];
        ok = id != 0xFFFF;
    }
    if (ok)
    {
        Sound_call(id, 0, 0);
    }
    else
    {
        Sound_seq_stop_all();
    }
    D_80098958 &= ~0x800;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_stage_play);
#endif

#ifdef NON_MATCHING
void Sound_init(void)
{
    SpuEnv env;
    sint32 i;

    SsInit();
    SsSetTableSize(D_800C1010, 4, 4);
    SsSetTickMode(SS_TICK60);
    Sound_call_ptr                = Sound_call_queue;
    Sound_work.se_vol             = 0x40;
    Sound_work.seq_vol            = 0x64;
    Sound_fade_step_size          = 4;
    Sound_work.mvol               = SS_VOL_MAX;
    Sound_work.serial_vol         = SS_VOL_MAX;
    Sound_work.seq_fade           = SS_VOL_MAX;
    Sound_work.se_fade            = SS_VOL_MAX;
    Sound_work.serial_fade        = SS_VOL_MAX;
    Sound_work.mvol_fade          = SS_VOL_MAX;
    Sound_fade_flags              = 0;
    D_80098958                    = 0;
    Sound_work.reserved_voice     = 0xF;
    Sound_work.reserved_voice_set = 0;
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);
    SsSetSerialVol(SS_SERIAL_A, SS_VOL_MAX, SS_VOL_MAX);
    Sound_work.reverb_state = 0;
    Sound_work.reverb_set   = 0;
    Sound_work.reverb       = &Sound_reverb_tbl[0];
    for (i = 0; i < 5; i++)
    {
        Game_work.vab[i].vab_id = -1;
        Game_work.vab[i].num    = 0xFF;
    }
    for (i = 0; i < 4; i++)
    {
        Sound_seq_chan_tbl[i].kind = -1;
        Sound_seq_tbl[i].num       = 0xFF;
    }
    p_Player_work = &Player_work;
    env.mask      = SPU_ENV_EVENT_QUEUEING;
    env.queueing  = SPU_OFF;
    SpuSetEnv(&env);
    SsStart();
    D_80098958 |= 1;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_init);
#endif

void Sound_reverb_set(sint32 idx)
{
    Sound_work.reverb = &Sound_reverb_tbl[idx];
}

void func_80019FB4(void)
{
    D_80098958 |= 0x800;
    if (Sound_stage_func_tbl[Game_work.unk050] != 0)
    {
        Sound_stage_func_tbl[Game_work.unk050](0);
    }
}

void Sound_call(uint16 id, sint32 arg1, sint32 arg2)
{
    if (Sound_call_ptr != &Sound_call_queue[SOUND_CALL_MAX])
    {
        Sound_call_ptr->mode = SOUND_MODE_PAN;
        Sound_call_ptr->id   = id;
        Sound_call_ptr->arg1 = arg1;
        Sound_call_ptr->arg2 = arg2;
        Sound_call_ptr++;
    }
}

#ifdef NON_MATCHING
void Sound_call2(sint16 id, SVECTOR *pos)
{
    if (Sound_call_ptr != &Sound_call_queue[SOUND_CALL_MAX])
    {
        Sound_call_ptr->mode = SOUND_MODE_POS;
        Sound_call_ptr->id   = id;
        Sound_call_ptr->arg1 = ((sint32 *)pos)[0]; // vx (vy in the high half)
        Sound_call_ptr->arg2 = ((sint32 *)pos)[1]; // vz (pad in the high half)
        Sound_call_ptr++;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_call2);
#endif

sint32 Sound_seq_is_eos(sint32 idx)
{
    sint32 ret;

    ret = 0;
    if (Sound_seq_chan_tbl[idx].kind != -1 && Sound_seq_chan_tbl[idx].access != -1)
    {
        ret = SsIsEos(Sound_seq_chan_tbl[idx].access, Sound_seq_chan_tbl[idx].seq_num);
    }
    return ret;
}

#ifdef NON_MATCHING
void Sound_update(void)
{
    SOUND_CALL *call;
    sint32 i;

    if (D_80098958 != 0)
    {
        volume_update();
        for (i = 0; i < 4; i++)
        {
            Sound_seq_chan_tbl[i].playing = Sound_seq_is_eos(i);
        }
        for (call = Sound_call_queue; call != Sound_call_ptr; call++)
        {
            Sound_call_func_tbl[Sound_call_info_tbl[call->id].type >> 6](call);
        }
        Sound_call_ptr = Sound_call_queue;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_update);
#endif

sint32 vab_find(sint32 num)
{
    sint32 i;

    for (i = 0; i < 5; i++)
    {
        if (Game_work.vab[i].num == num)
        {
            return i;
        }
    }
    return -1;
}

sint32 seq_find(sint32 num)
{
    sint32 i;

    for (i = 0; i < 5; i++)
    {
        if (Sound_seq_tbl[i].num == num)
        {
            return i;
        }
    }
    return -1;
}

void calc_vol(SOUND_CALL *call, uint16 vol, uint16 *left, uint16 *right, sint16 dist)
{
    sint32 angle;
    uint16 v;
    sint32 pan;
    sint32 scale;

    v = vol * 0x81;
    switch (call->mode)
    {
        case SOUND_MODE_PAN:
            if (call->arg1 > 0)
            {
                *left  = (v * (0x80 - (uint16)call->arg1)) / 128;
                *right = v;
            }
            else
            {
                *left  = v;
                *right = (v * (uint16)(call->arg1 + 0x80)) / 128;
            }
            if (Game_work.mono != 0)
            {
                if (*left > *right)
                {
                    *right = *left;
                }
                else
                {
                    *left = *right;
                }
            }
            *left  = (*left * (0x80 - call->arg2)) / 128;
            *right = (*right * (0x80 - call->arg2)) / 128;
            break;
        case SOUND_MODE_POS:
            if (dist == 0)
            {
                *left = *right = v;
                return;
            }
            angle =
                p_Player_work->unk56 - func_8001E83C(p_Player_work->pos.vx, p_Player_work->pos.vz, (sint16)call->arg1, (sint16)call->arg2);
            angle &= 0xFFF;
            pan = (ccos(angle) << 7) >> 12;
            if (pan < 0)
            {
                pan = -pan;
            }
            if (angle < 0x800)
            {
                *left  = v;
                *right = (v * pan) / 128;
            }
            else
            {
                *left  = (v * pan) / 128;
                *right = v;
            }
            if (Game_work.mono != 0)
            {
                if (*left > *right)
                {
                    *right = *left;
                }
                else
                {
                    *left = *right;
                }
            }
            scale  = 5000 - dist;
            *left  = (*left * scale) / 5000;
            *right = (*right * scale) / 5000;
            break;
    }
    *left  = (*left * Sound_work.se_vol) / 127;
    *right = (*right * Sound_work.se_vol) / 127;
    *left  = (*left * Sound_work.se_fade) / 127;
    *right = (*right * Sound_work.se_fade) / 127;
}

sint32 pitch_scale(sint32 x)
{
    sint32 scale;
    sint32 mul;

    scale = 0x1000;
    if (x >= 0)
    {
        scale <<= x / 12;
        mul = Sound_pitch_tbl_up[x % 12];
    }
    else
    {
        x   = -x;
        mul = Sound_pitch_tbl_down[x % 12];
        scale >>= x / 12;
    }
    scale *= mul;
    return scale >> 16;
}

#ifdef NON_MATCHING
sint32 pitch_interp(sint32 x, sint32 frac)
{
    sint32 a;

    a = pitch_scale(x);
    return a + ((pitch_scale(x + 1) - a) * frac) / 128;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", pitch_interp);
#endif

void key_on_tone(uint16 vab_id, SOUND_CALL_INFO *info, VagAtr *tone, SOUND_CALL *call)
{
    SpuVoiceAttr attr;
    uint32 voice;

    voice = info->unk3 & 0x1F;
    calc_vol(call, tone->vol, &attr.volume.left, &attr.volume.right, Game_work.unk1E0[voice]);
    attr.voice = 1 << voice;
    attr.mask  = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH | SPU_VOICE_WDSA | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    attr.addr  = SsUtGetVagAddr(vab_id, tone->vag);
    attr.pitch = pitch_interp(tone->min - tone->center, tone->shift);
    attr.adsr1 = tone->adsr1;
    attr.adsr2 = tone->adsr2;
    Sound_voice_priority[voice] = info->unk2 & 0xF;
    SpuSetKeyOnWithAttr(&attr);
}

sint32 voice_check(SOUND_CALL_INFO *info, SOUND_CALL *call)
{
    uint32 voice;
    sint32 status;
    sint32 dist;
    sint32 dz;
    sint32 dx;

    voice  = info->unk3 & 0x1F;
    status = SpuGetKeyStatus(1 << voice);
    if (status == 1 && (info->unk2 & 0xF) < Sound_voice_priority[voice])
    {
        return 0;
    }
    if (call->mode == SOUND_MODE_POS)
    {
        dx   = p_Player_work->pos.vx - (sint16)call->arg1;
        dx   = dx * dx;
        dz   = p_Player_work->pos.vz - (sint16)call->arg2;
        dz   = dz * dz;
        dist = SquareRoot0(dx + dz);
        if (dist >= 5000 || (status == 1 && Sound_voice_priority[voice] >= (info->unk2 & 0xF) && dist >= 3001))
        {
            return 0;
        }
        Game_work.unk1E0[voice] = dist;
    }
    return 1;
}

#ifdef NON_MATCHING
void Sound_call_play(SOUND_CALL *call)
{
    SOUND_CALL_INFO *info;
    VagAtr *tone;
    sint32 bank;
    sint32 count;
    uint16 voice;
    uint16 vab_id;

    info = &Sound_call_info_tbl[call->id];
    bank = vab_find(info->type & 0x3F);
    if (bank == -1)
    {
        return;
    }
    tone   = &((VAB_HEAD *)VAB_HEAD_BUF)[bank].tone[info->unk1 & 0x7F][info->unk2 >> 4];
    voice  = info->unk3 & 0x1F;
    count  = (info->unk3 & 0x60) >> 5;
    vab_id = Game_work.vab[bank].vab_id;
    while (count >= 0 && voice < 0x18)
    {
        if (voice_check(info, call) != 0)
        {
            key_on_tone(vab_id, info, tone, call);
        }
        tone++;
        count--;
        voice++;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_call_play);
#endif

void Sound_seq_play(SOUND_CALL *call)
{
    SOUND_WORK *work;
    SOUND_CALL_INFO *info;
    SOUND_SEQ_CHAN *chan;
    sint32 bank;
    sint32 seq;

    info = &Sound_call_info_tbl[call->id];
    bank = vab_find(info->type & 0x3F);
    if (bank == -1)
    {
        return;
    }
    seq = seq_find(info->unk1 & 0x7F);
    if (seq == -1)
    {
        return;
    }
    chan = &Sound_seq_chan_tbl[info->unk2 >> 4];
    if (call->arg1 == 0 && chan->playing != 0 && chan->id == call->id)
    {
        return;
    }
    if ((info->unk2 & 0xF) < chan->priority)
    {
        return;
    }
    if (chan->access != -1 && chan->kind != -1)
    {
        if (chan->kind == 0)
        {
            SsSeqStop(chan->access);
            SsSeqClose(chan->access);
        }
        else
        {
            SsSepStop(chan->access, chan->seq_num);
            SsSepClose(chan->access);
        }
    }
    chan->access   = SsSeqOpen((unsigned long *)Sound_seq_tbl[seq].data, Game_work.vab[bank].vab_id);
    chan->priority = info->unk2 & 0xF;
    chan->kind     = 0;
    if (chan->access != -1)
    {
        work = &Sound_work;
        if (info->unk1 != 0)
        {
            SsSeqPlay(chan->access, SSPLAY_PLAY, SSPLAY_INFINITY);
        }
        else
        {
            SsSeqPlay(chan->access, SSPLAY_PLAY, 1);
        }
        work->seq_fade = 0x7F;
        chan->id       = call->id;
    }
}

void Sound_sep_play(SOUND_CALL *call)
{
    SOUND_CALL_INFO *info;
    SOUND_SEQ_CHAN *chan;
    SOUND_WORK *work;
    sint32 bank;
    sint32 seq;

    info = &Sound_call_info_tbl[call->id];
    work = &Sound_work;
    bank = vab_find(info->type & 0x3F);
    if (bank == -1)
    {
        return;
    }
    seq = seq_find(info->unk1 & 0x7F);
    if (seq == -1)
    {
        return;
    }
    chan = &Sound_seq_chan_tbl[info->unk2 >> 4];
    if (call->arg1 == 0 && chan->playing != 0 && chan->id == call->id)
    {
        Sound_work.seq_fade = 0x7F;
        return;
    }
    if ((info->unk2 & 0xF) < chan->priority)
    {
        return;
    }
    if (chan->access != -1 && chan->kind != -1)
    {
        if (chan->kind == 0)
        {
            SsSeqStop(chan->access);
            SsSeqClose(chan->access);
        }
        else
        {
            SsSepStop(chan->access, chan->seq_num);
            SsSepClose(chan->access);
        }
    }
    chan->access   = SsSepOpen((unsigned long *)Sound_seq_tbl[seq].data, Game_work.vab[bank].vab_id, Sound_seq_tbl[seq].sep_count);
    chan->priority = info->unk2 & 0xF;
    chan->kind     = 1;
    if (chan->access != -1)
    {
        chan->seq_num = info->unk3 & 0x1F;
        if (info->unk1 & 0x80)
        {
            SsSepPlay(chan->access, chan->seq_num, SSPLAY_PLAY, SSPLAY_INFINITY);
        }
        else
        {
            SsSepPlay(chan->access, chan->seq_num, SSPLAY_PLAY, 1);
        }
        work->seq_fade = 0x7F;
        chan->id       = call->id;
    }
}

sint32 fade_step(sint32 flags, sint16 *fade)
{
    sint32 ret;

    ret = 0;
    if (flags & 3)
    {
        ret = 1;
        if (flags & 1)
        {
            *fade -= Sound_fade_step_size;
            if (*fade <= 0)
            {
                *fade = 0;
                ret   = 0;
            }
        }
        else
        {
            *fade += Sound_fade_step_size;
            if (*fade >= 0x7F)
            {
                *fade = 0x7F;
                ret   = 0;
            }
        }
    }
    return ret;
}

void volume_update(void)
{
    SOUND_WORK *work = &Sound_work;
    sint32 i;
    SOUND_SEQ_CHAN *chan;
    sint16 vol;
    SOUND_REVERB *rev;

    if (fade_step(Sound_fade_flags & SOUND_FADE_MVOL, &work->mvol_fade) == 0)
    {
        Sound_fade_flags &= ~SOUND_FADE_MVOL;
    }
    if (fade_step((Sound_fade_flags & SOUND_FADE_SE) >> 2, &work->se_fade) == 0)
    {
        Sound_fade_flags &= ~SOUND_FADE_SE;
    }
    if (fade_step((Sound_fade_flags & SOUND_FADE_SEQ) >> 4, &work->seq_fade) == 0)
    {
        Sound_fade_flags &= ~SOUND_FADE_SEQ;
    }
    D_80098958 |= 0x400;
    if (fade_step(Sound_fade_flags >> 6, &work->serial_fade) == 0)
    {
        if (Sound_fade_flags & 0x40) // serial fade out
        {
            Cd_subcmd(0, 1, 0);
        }
        Sound_fade_flags &= ~SOUND_FADE_SERIAL;
    }
    vol = (work->mvol * work->mvol_fade) / 127;
    SsSetMVol(vol, vol);
    if (!(work->flags & SOUND_FLAG_CD_OFF))
    {
        vol = (work->serial_vol * work->serial_fade) / 127;
        SsSetSerialVol(SS_SERIAL_A, vol, vol);
        if (Game_work.mono != 0)
        {
            work->atv.val0 = 0x7F;
            work->atv.val1 = 0x7F;
            work->atv.val2 = 0x7F;
            work->atv.val3 = 0x7F;
        }
        else
        {
            work->atv.val0 = 0x7F;
            work->atv.val1 = 0;
            work->atv.val2 = 0x7F;
            work->atv.val3 = 0;
        }
        CdMix(&work->atv);
    }
    if (Game_work.mono != 0)
    {
        SsSetMono();
    }
    else
    {
        SsSetStereo();
    }
    chan = Sound_seq_chan_tbl;
    for (i = 0; i < 4; chan++, i++)
    {
        if (chan->access != -1 && chan->kind != -1)
        {
            vol = (work->seq_vol * work->seq_fade) / 127;
            if (chan->kind == 0)
            {
                SsSeqSetVol(chan->access, vol, vol);
            }
            else
            {
                SsSepSetVol(chan->access, chan->seq_num, vol, vol);
            }
        }
    }
    D_80098958 &= ~0x400;
    if (work->reserved_voice != work->reserved_voice_set)
    {
        SsUtAllKeyOff(0);
        SsSetReservedVoice(work->reserved_voice);
    }
    work->reserved_voice_set = work->reserved_voice;
    rev                      = work->reverb;
    switch (work->reverb_state)
    {
        case 0:
            if (rev != work->reverb_set)
            {
                SsUtSetReverbType(rev->type);
                SsUtReverbOn();
                work->reverb_timer = 0x1E;
                work->reverb_state++;
            }
            break;
        case 1:
            work->reverb_timer--;
            if (work->reverb_timer == 0)
            {
                if (rev->type != 0)
                {
                    SsUtSetReverbDepth(rev->depth, rev->depth);
                    SsSetRVol(rev->vol, rev->vol);
                }
                work->reverb_state = 0;
                work->reverb_set   = rev;
            }
            break;
    }
}

void Sound_key_off_voice(sint16 voice)
{
    SsUtKeyOffV(voice);
}

void func_8001B314(void)
{
    SpuSetKey(SPU_OFF, 0xFF8000);
}

void Sound_seq_stop_all(void)
{
    SOUND_SEQ_CHAN *chan;
    sint32 i;

    chan = Sound_seq_chan_tbl;
    for (i = 0; i < 4; chan++, i++)
    {
        if (chan->access != -1 && chan->kind != -1)
        {
            if (chan->kind == 0)
            {
                SsSeqStop(chan->access);
            }
            else
            {
                SsSepStop(chan->access, chan->seq_num);
            }
        }
    }
}
