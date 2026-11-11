#include "common.h"
#include "sound.h"
#include "cd.h"
#include "game.h"
#include "psyq/libsnd.h"
#include "psyq/libspu.h"
#include "psyq/libgte.h"
#include "player.h"

void func_800198C0(void)
{
    sint32 i;
    sint16 queueing;

    if (Sce_flag_test(6) != 0 && Sce_flag_test(0x2C) == 0)
    {
        queueing = 2;
    }
    else
    {
        queueing = 7;
    }
    for (i = 5; i >= 0; i--)
    {
        D_80082220[i] = queueing;
    }
}

void func_80019918(void)
{
    sint16 queueing;

    if ((Sce_flag_test(0x204) != 0 && Sce_flag_test(0x206) == 0) || (Sce_flag_test(0x212) != 0 && Sce_flag_test(0x213) == 0))
    {
        queueing = 0x39;
    }
    else
    {
        queueing = 7;
    }
    D_8008222C = queueing;
}

void func_8001997C(void)
{
    if (Game_work.unk053 == 1)
    {
        D_80082274 = 0x29;
    }
    else
    {
        D_80082274 = 0x108;
    }
}

void func_800199A4(void)
{
    sint16 queueing;

    if (Game_work.unk053 < 4)
    {
        if (Game_work.unk053 > 0 && Sce_flag_test(0x30) == 0)
        {
            queueing = 0x16;
        }
        else
        {
            queueing = 0x108;
        }
    }
    else
    {
        queueing = 0x108;
    }
    D_80082278 = queueing;
}

void func_800199F8(void)
{
    sint32 i;
    sint16 queueing;

    if (Game_work.unk053 == 1)
    {
        queueing = 0x17;
    }
    else
    {
        queueing = 0x108;
    }
    for (i = 5; i >= 0; i--)
    {
        D_8008229C[i] = queueing;
    }
}

void func_80019A34(void)
{
    sint32 i;
    sint16 queueing;

    if (Game_work.unk053 == 1)
    {
        queueing = 0x17;
    }
    else
    {
        queueing = 0x108;
    }
    for (i = 4; i >= 0; i--)
    {
        D_800822A8[i] = queueing;
    }
}

void func_80019A70(void)
{
    if (Sce_flag_test(0x1E1) != 0)
    {
        D_800822D6 = 0x25;
    }
    else
    {
        D_800822D6 = 0x30;
    }
}

void func_80019AA4(void)
{
    if (Sce_flag_test(0x35) == 0)
    {
        D_800822F4 = D_800822F2 = 0xFFFF;
    }
    else
    {
        D_800822F4 = D_800822F2 = 0x2D;
    }
}

void func_80019AE0(void)
{
    if (Sce_flag_test(0x1E1) != 0)
    {
        D_80082218 = 0x25;
    }
    else
    {
        D_80082218 = 0x30;
    }
}

void func_80019B14(sint32 which)
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
            D_80082314[stage] = Sce_flag_test(0x616) ? 0xFFFF : 0x3A;
            break;
        case 1:
            D_80082314[stage] = Sce_flag_test(0x617) ? 0xFFFF : 0x3B;
            break;
        case 2:
            D_80082314[stage] = Sce_flag_test(0x68) ? 0xFFFF : 0x3C;
            break;
    }
}

#ifdef NON_MATCHING
void func_80019C20(void)
{
    sint32 changed;
    uint16 *list;
    uint16 id;

    if (D_800823A0[D_800C356E] != 0)
    {
        D_800823A0[D_800C356E](1);
    }
    list    = D_80082320[D_800C356E];
    changed = 0;
    if (list != 0)
    {
        id = list[D_800C356F];
        if (id == 0xFFFF || D_80082320[Game_work.unk050][Game_work.unk051] != id)
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
        func_8001D854(0x10);
        D_80098958 |= 0x800;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_80019C20);
#endif

#ifdef NON_MATCHING
void func_80019D18(void)
{
    uint16 *list;
    sint32 ok;
    sint16 id;

    if (D_800823A0[Game_work.unk050] != 0)
    {
        D_800823A0[Game_work.unk050](0);
    }
    list = D_80082320[Game_work.unk050];
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
        func_8001B33C();
    }
    D_80098958 &= ~0x800;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_80019D18);
#endif

#ifdef NON_MATCHING
void func_80019DE0(void)
{
    SpuEnv env;
    sint32 i;

    func_8006B594();
    SsSetTableSize(D_800C1010, 4, 4);
    SsSetTickMode(SS_TICK60);
    D_80098938            = D_800BE4F8;
    Sound_work.unk08      = 0x40;
    Sound_work.unk0A      = 0x64;
    D_80098840            = 4;
    Sound_work.unk04      = SS_VOL_MAX;
    Sound_work.serial_vol = SS_VOL_MAX;
    Sound_work.unk12      = SS_VOL_MAX;
    Sound_work.unk10      = SS_VOL_MAX;
    Sound_work.unk0E      = SS_VOL_MAX;
    Sound_work.unk0C      = SS_VOL_MAX;
    D_80098788            = 0;
    D_80098958            = 0;
    Sound_work.unk18      = 0xF;
    Sound_work.unk19      = 0;
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SON);
    SsSetSerialVol(SS_SERIAL_A, SS_VOL_MAX, SS_VOL_MAX);
    Sound_work.unk1A = 0;
    Sound_work.unk20 = 0;
    Sound_work.unk1C = D_800821F8[0];
    for (i = 0; i < 5; i++)
    {
        Game_work.vab[i].vab_id = -1;
        Game_work.vab[i].num    = 0xFF;
    }
    for (i = 0; i < 4; i++)
    {
        D_80098AF8[i].unk2   = -1;
        Sound_seq_tbl[i].num = 0xFF;
    }
    p_Player_work = &Player_work;
    env.mask      = SPU_ENV_EVENT_QUEUEING;
    env.queueing  = SPU_OFF;
    SpuSetEnv(&env);
    SsStart();
    D_80098958 |= 1;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_80019DE0);
#endif

void func_80019F94(sint32 idx)
{
    Sound_work.unk1C = D_800821F8[idx];
}

void func_80019FB4(void)
{
    D_80098958 |= 0x800;
    if (D_800823A0[Game_work.unk050] != 0)
    {
        D_800823A0[Game_work.unk050](0);
    }
}

void Sound_call(sint16 id, sint32 arg1, sint32 arg2)
{
    if (D_80098938 != &D_800BE4F8[SOUND_CALL_MAX])
    {
        D_80098938->busy = 0;
        D_80098938->id   = id;
        D_80098938->arg1 = arg1;
        D_80098938->arg2 = arg2;
        D_80098938++;
    }
}

#ifdef NON_MATCHING
void Sound_call2(sint16 id, sint32 *args)
{
    if (D_80098938 != &D_800BE4F8[SOUND_CALL_MAX])
    {
        D_80098938->busy = 1;
        D_80098938->id   = id;
        D_80098938->arg1 = args[0];
        D_80098938->arg2 = args[1];
        D_80098938++;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", Sound_call2);
#endif

sint32 func_8001A0A8(sint32 idx)
{
    sint32 ret;

    ret = 0;
    if (D_80098AF8[idx].unk2 != -1 && D_80098AF8[idx].unk0 != -1)
    {
        ret = SsIsEos(D_80098AF8[idx].unk0, D_80098AF8[idx].unk4);
    }
    return ret;
}

#ifdef NON_MATCHING
void func_8001A110(void)
{
    SOUND_CALL *call;
    sint32 i;

    if (D_80098958 != 0)
    {
        func_8001AEF0();
        for (i = 0; i < 4; i++)
        {
            D_80098AF8[i].unk5 = func_8001A0A8(i);
        }
        for (call = D_800BE4F8; call != D_80098938; call++)
        {
            D_80082C64[D_8008241C[call->id].type >> 6](call);
        }
        D_80098938 = D_800BE4F8;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_8001A110);
#endif

sint32 func_8001A1FC(sint32 num)
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

sint32 func_8001A238(sint32 num)
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

void func_8001A274(SOUND_CALL *call, uint16 vol, uint16 *left, uint16 *right, sint16 dist)
{
    sint32 angle;
    uint16 v;
    sint32 pan;
    sint32 scale;

    v = vol * 0x81;
    switch (call->busy)
    {
        case 0:
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
            if (Game_work.unk058 != 0)
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
        case 1:
            if (dist == 0)
            {
                *left = *right = v;
                return;
            }
            angle =
                p_Player_work->unk56 - func_8001E83C(p_Player_work->unk14, p_Player_work->unk18, (sint16)call->arg1, (sint16)call->arg2);
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
            if (Game_work.unk058 != 0)
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
    *left  = (*left * Sound_work.unk08) / 127;
    *right = (*right * Sound_work.unk08) / 127;
    *left  = (*left * Sound_work.unk10) / 127;
    *right = (*right * Sound_work.unk10) / 127;
}

sint32 func_8001A63C(sint32 x)
{
    sint32 scale;
    sint32 mul;

    scale = 0x1000;
    if (x >= 0)
    {
        scale <<= x / 12;
        mul = D_80082C70[x % 12];
    }
    else
    {
        x   = -x;
        mul = D_80082CA0[x % 12];
        scale >>= x / 12;
    }
    scale *= mul;
    return scale >> 16;
}

#ifdef NON_MATCHING
sint32 func_8001A6DC(sint32 x, sint32 frac)
{
    sint32 a;

    a = func_8001A63C(x);
    return a + ((func_8001A63C(x + 1) - a) * frac) / 128;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_8001A6DC);
#endif

void func_8001A744(uint16 vab_id, SOUND_CALL_INFO *info, VagAtr *tone, SOUND_CALL *call)
{
    SpuVoiceAttr attr;
    uint32 voice;

    voice = info->unk3 & 0x1F;
    func_8001A274(call, tone->vol, &attr.volume.left, &attr.volume.right, Game_work.unk1E0[voice]);
    attr.voice        = 1 << voice;
    attr.mask         = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH | SPU_VOICE_WDSA | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
    attr.addr         = SsUtGetVagAddr(vab_id, tone->vag);
    attr.pitch        = func_8001A6DC(tone->min - tone->center, tone->shift);
    attr.adsr1        = tone->adsr1;
    attr.adsr2        = tone->adsr2;
    D_80098B48[voice] = info->unk2 & 0xF;
    SpuSetKeyOnWithAttr(&attr);
}

sint32 func_8001A834(SOUND_CALL_INFO *info, SOUND_CALL *call)
{
    uint32 voice;
    sint32 status;
    sint32 dist;
    sint32 dz;
    sint32 dx;

    voice  = info->unk3 & 0x1F;
    status = SpuGetKeyStatus(1 << voice);
    if (status == 1 && (info->unk2 & 0xF) < D_80098B48[voice])
    {
        return 0;
    }
    if (call->busy == 1)
    {
        dx   = p_Player_work->unk14 - (sint16)call->arg1;
        dx   = dx * dx;
        dz   = p_Player_work->unk18 - (sint16)call->arg2;
        dz   = dz * dz;
        dist = SquareRoot0(dx + dz);
        if (dist >= 5000 || (status == 1 && D_80098B48[voice] >= (info->unk2 & 0xF) && dist >= 3001))
        {
            return 0;
        }
        Game_work.unk1E0[voice] = dist;
    }
    return 1;
}

#ifdef NON_MATCHING
void func_8001A968(SOUND_CALL *call)
{
    SOUND_CALL_INFO *info;
    VagAtr *tone;
    sint32 bank;
    sint32 count;
    uint16 voice;
    uint16 vab_id;

    info = &D_8008241C[call->id];
    bank = func_8001A1FC(info->type & 0x3F);
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
        if (func_8001A834(info, call) != 0)
        {
            func_8001A744(vab_id, info, tone, call);
        }
        tone++;
        count--;
        voice++;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_8001A968);
#endif

void func_8001AA8C(SOUND_CALL *call)
{
    SOUND_WORK *work;
    SOUND_CALL_INFO *info;
    SOUND_SEQ_CHAN *chan;
    sint32 bank;
    sint32 seq;

    info = &D_8008241C[call->id];
    bank = func_8001A1FC(info->type & 0x3F);
    if (bank == -1)
    {
        return;
    }
    seq = func_8001A238(info->unk1 & 0x7F);
    if (seq == -1)
    {
        return;
    }
    chan = &D_80098AF8[info->unk2 >> 4];
    if (call->arg1 == 0 && chan->unk5 != 0 && chan->unk6 == call->id)
    {
        return;
    }
    if ((info->unk2 & 0xF) < chan->unk3)
    {
        return;
    }
    if (chan->unk0 != -1 && chan->unk2 != -1)
    {
        if (chan->unk2 == 0)
        {
            func_80070114(chan->unk0);
            SsSeqClose(chan->unk0);
        }
        else
        {
            func_8007013C(chan->unk0, chan->unk4);
            SsSepClose(chan->unk0);
        }
    }
    chan->unk0 = SsSeqOpen((unsigned long *)Sound_seq_tbl[seq].data, Game_work.vab[bank].vab_id);
    chan->unk3 = info->unk2 & 0xF;
    chan->unk2 = 0;
    if (chan->unk0 != -1)
    {
        work = &Sound_work;
        if (info->unk1 != 0)
        {
            SsSeqPlay(chan->unk0, SSPLAY_PLAY, SSPLAY_INFINITY);
        }
        else
        {
            SsSeqPlay(chan->unk0, SSPLAY_PLAY, 1);
        }
        work->unk12 = 0x7F;
        chan->unk6  = call->id;
    }
}

void func_8001AC58(SOUND_CALL *call)
{
    SOUND_CALL_INFO *info;
    SOUND_SEQ_CHAN *chan;
    SOUND_WORK *work;
    sint32 bank;
    sint32 seq;

    info = &D_8008241C[call->id];
    work = &Sound_work;
    bank = func_8001A1FC(info->type & 0x3F);
    if (bank == -1)
    {
        return;
    }
    seq = func_8001A238(info->unk1 & 0x7F);
    if (seq == -1)
    {
        return;
    }
    chan = &D_80098AF8[info->unk2 >> 4];
    if (call->arg1 == 0 && chan->unk5 != 0 && chan->unk6 == call->id)
    {
        Sound_work.unk12 = 0x7F;
        return;
    }
    if ((info->unk2 & 0xF) < chan->unk3)
    {
        return;
    }
    if (chan->unk0 != -1 && chan->unk2 != -1)
    {
        if (chan->unk2 == 0)
        {
            func_80070114(chan->unk0);
            SsSeqClose(chan->unk0);
        }
        else
        {
            func_8007013C(chan->unk0, chan->unk4);
            SsSepClose(chan->unk0);
        }
    }
    chan->unk0 = SsSepOpen((unsigned long *)Sound_seq_tbl[seq].data, Game_work.vab[bank].vab_id, Sound_seq_tbl[seq].unk1);
    chan->unk3 = info->unk2 & 0xF;
    chan->unk2 = 1;
    if (chan->unk0 != -1)
    {
        chan->unk4 = info->unk3 & 0x1F;
        if (info->unk1 & 0x80)
        {
            SsSepPlay(chan->unk0, chan->unk4, SSPLAY_PLAY, SSPLAY_INFINITY);
        }
        else
        {
            SsSepPlay(chan->unk0, chan->unk4, SSPLAY_PLAY, 1);
        }
        work->unk12 = 0x7F;
        chan->unk6  = call->id;
    }
}

sint32 func_8001AE6C(sint32 flags, sint16 *queueing)
{
    sint32 ret;

    ret = 0;
    if (flags & 3)
    {
        ret = 1;
        if (flags & 1)
        {
            *queueing -= D_80098840;
            if (*queueing <= 0)
            {
                *queueing = 0;
                ret       = 0;
            }
        }
        else
        {
            *queueing += D_80098840;
            if (*queueing >= 0x7F)
            {
                *queueing = 0x7F;
                ret       = 0;
            }
        }
    }
    return ret;
}

#ifdef NON_MATCHING
void func_8001AEF0(void)
{
    SOUND_WORK *work = &Sound_work;
    sint32 i;
    SOUND_SEQ_CHAN *chan;
    sint16 vol;
    uint8 *rev;

    if (func_8001AE6C(D_80098788 & 3, &work->unk0C) == 0)
    {
        D_80098788 &= 0xFC;
    }
    if (func_8001AE6C((D_80098788 & 0xC) >> 2, &work->unk10) == 0)
    {
        D_80098788 &= 0xF3;
    }
    if (func_8001AE6C((D_80098788 & 0x30) >> 4, &work->unk12) == 0)
    {
        D_80098788 &= 0xCF;
    }
    D_80098958 |= 0x400;
    if (func_8001AE6C(D_80098788 >> 6, &work->unk0E) == 0)
    {
        if (D_80098788 & 0x40)
        {
            Cd_subcmd(0, 1, 0);
        }
        D_80098788 &= 0x3F;
    }
    vol = (work->unk04 * work->unk0C) / 127;
    SsSetMVol(vol, vol);
    if (!(work->flags & SOUND_FLAG_CD_OFF))
    {
        vol = (work->serial_vol * work->unk0E) / 127;
        SsSetSerialVol(SS_SERIAL_A, vol, vol);
        if (Game_work.unk058 != 0)
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
    if (Game_work.unk058 != 0)
    {
        func_80075AA4();
    }
    else
    {
        func_80075AB8();
    }
    chan = D_80098AF8;
    for (i = 0; i < 4; i++)
    {
        if (chan->unk0 != -1 && chan->unk2 != -1)
        {
            vol = (work->unk0A * work->unk12) / 127;
            if (chan->unk2 == 0)
            {
                func_80070634(chan->unk0, vol, vol);
            }
            else
            {
                func_80070694(chan->unk0, chan->unk4, vol, vol);
            }
        }
        chan++;
    }
    D_80098958 &= ~0x400;
    if (work->unk18 != work->unk19)
    {
        func_80070974(0);
        SsSetReservedVoice(work->unk18);
    }
    work->unk19 = work->unk18;
    rev         = work->unk1C;
    switch (work->unk1A)
    {
        case 0:
            if (rev != work->unk20)
            {
                SsUtSetReverbType(rev[0]);
                func_800721C4();
                work->unk1B = 0x1E;
                work->unk1A++;
            }
            break;
        case 1:
            work->unk1B--;
            if (work->unk1B == 0)
            {
                if (rev[0] != 0)
                {
                    SsUtSetReverbDepth(rev[2], rev[2]);
                    SsSetRVol(rev[1], rev[1]);
                }
                work->unk1A = 0;
                work->unk20 = rev;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_8001AEF0);
#endif

void Sound_key_off_voice(sint16 voice)
{
    SsUtKeyOffV(voice);
}

void func_8001B314(void)
{
    SpuSetKey(SPU_OFF, 0xFF8000);
}

#ifdef NON_MATCHING
void func_8001B33C(void)
{
    SOUND_SEQ_CHAN *chan;
    sint32 i;

    chan = D_80098AF8;
    for (i = 0; i < 4; i++, chan++)
    {
        if (chan->unk0 != -1 && chan->unk2 != -1)
        {
            if (chan->unk2 == 0)
            {
                func_80070114(chan->unk0);
            }
            else
            {
                func_8007013C(chan->unk0, chan->unk4);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sound", func_8001B33C);
#endif
