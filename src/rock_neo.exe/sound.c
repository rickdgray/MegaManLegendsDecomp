#include "common.h"
#include "game.h"
#include "sound.h"

void func_800198C0(void)
{
    sint32 i;
    sint32 v;

    if (Sce_flag_test(6) == 0 || Sce_flag_test(0x2C) != 0)
    {
        v = 7;
    }
    else
    {
        v = 2;
    }
    for (i = 0; i < 6; i++)
    {
        D_80082224[i] = v;
    }
}

void func_80019918(void)
{
    sint32 v;

    if (Sce_flag_test(0x204) && !Sce_flag_test(0x206))
    {
        v = 0x39;
    }
    else if (!Sce_flag_test(0x212) || Sce_flag_test(0x213))
    {
        v = 7;
    }
    else
    {
        v = 0x39;
    }
    D_8008222C = v;
}

void func_8001997C(void)
{
    if (GAME_WORK_FLAG53 == 1)
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
    sint32 mode;

    mode = GAME_WORK_FLAG53;
    if (mode < 4)
    {
        if (mode > 0)
        {
            if (Sce_flag_test(0x30))
            {
                D_80082278 = 0x108;
            }
            else
            {
                D_80082278 = 0x16;
            }
        }
        else
        {
            D_80082278 = 0x108;
        }
    }
    else
    {
        D_80082278 = 0x108;
    }
}

void func_800199F8(void)
{
    uint16 value;
    sint32 i;

    value = (GAME_WORK_FLAG53 == 1) ? 0x17 : 0x108;
    for (i = 5; i >= 0; i--)
    {
        D_800822A0[i] = value;
    }
}

void func_80019A34(void)
{
    uint16 value;
    sint32 i;

    value = (GAME_WORK_FLAG53 == 1) ? 0x17 : 0x108;
    for (i = 4; i >= 0; i--)
    {
        D_800822A8[i] = value;
    }
}

void func_80019A70(void)
{
    if (Sce_flag_test(0x1E1))
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
    if (Sce_flag_test(0x35))
    {
        D_800822F2 = 0x2D;
        D_800822F4 = 0x2D;
    }
    else
    {
        D_800822F2 = 0xFFFF;
        D_800822F4 = 0xFFFF;
    }
}

void func_80019AE0(void)
{
    if (Sce_flag_test(0x1E1))
    {
        D_80082218 = 0x25;
    }
    else
    {
        D_80082218 = 0x30;
    }
}

void func_80019B14(sint32 arg)
{
    sint8 idx;

    if (arg == 0)
    {
        idx = Game_work.routine_51;
    }
    else
    {
        idx = D_800C356F;
    }
    switch (idx % 3)
    {
        case 0:
            D_80082314[idx] = Sce_flag_test(0x616) ? 0xFFFF : 0x3A;
            break;
        case 1:
            D_80082314[idx] = Sce_flag_test(0x617) ? 0xFFFF : 0x3B;
            break;
        case 2:
            D_80082314[idx] = Sce_flag_test(0x68) ? 0xFFFF : 0x3C;
            break;
    }
}

void func_80019C20(void)
{
    uint16 *tbl;
    uint16 v;
    SOUND_FUNC fn;
    sint32 diff;

    fn = D_800823A0[D_800C356E];
    if (fn != 0)
    {
        fn(1);
    }
    tbl  = D_80082320[D_800C356E];
    diff = 0;
    if (tbl == 0)
    {
        diff = 1;
    }
    else
    {
        v = tbl[D_800C356F];
        if (v == 0xFFFF)
        {
            diff = 1;
        }
        else
        {
            tbl = D_80082320[Game_work.routine_50];
            if (tbl[(sint8)Game_work.routine_51] != v)
            {
                diff = 1;
            }
        }
    }
    if (diff)
    {
        func_8001D854(0x10);
        D_80098958 |= 0x800;
    }
}

void func_80019D18(void)
{
    uint16 *tbl;
    SOUND_FUNC fn;
    sint32 id;
    sint32 ok;

    fn = D_800823A0[GAME_WORK_PTR->routine_50];
    if (fn != 0)
    {
        fn(0);
    }
    tbl = D_80082320[GAME_WORK_PTR->routine_50];
    id  = 0;
    ok  = 0;
    if (tbl != 0)
    {
        id = tbl[(sint8)GAME_WORK_PTR->routine_51];
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

// Store order found by search; neither field order nor source order of the
// assignments reproduces retail's early 0x7F in v1.
void func_80019DE0(void)
{
    SOUND_SPU_ENV env;
    sint32 i;

    func_8006B594();
    SsSetTableSize(D_800C1010, 4, 4);
    SsSetTickMode(1);
    D_80098788       = 0;
    D_80098938       = D_800BE4F8;
    D_80098958       = 0;
    Sound_work.unk04 = 0x7F;
    Sound_work.unk08 = 0x40;
    Sound_work.unk0A = 0x64;
    D_80098840       = 4;
    Sound_work.unk06 = 0x7F;
    Sound_work.unk12 = 0x7F;
    Sound_work.unk10 = 0x7F;
    Sound_work.unk0E = 0x7F;
    Sound_work.unk0C = 0x7F;
    Sound_work.unk18 = 0xF;
    Sound_work.unk19 = 0;
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 0x7F, 0x7F);
    Sound_work.unk1A = 0;
    Sound_work.unk20 = 0;
    Sound_work.unk1C = (uint8 *)D_800821F8;
    for (i = 0; i < 5; i++)
    {
        Game_work.sound_1b8[i].vab = -1;
        Game_work.sound_1b8[i].id  = 0xFF;
    }
    for (i = 0; i < 4; i++)
    {
        D_80098AFA[i][0] = -1;
        D_80098AD0[i].id = 0xFF;
    }
    p_Player_work = (SOUND_PLAYER *)&Player_work;
    env.mask      = 1;
    env.value     = 0;
    SpuSetEnv(&env);
    SsStart();
    D_80098958 |= 1;
}

void func_80019F94(sint32 index)
{
    Sound_work.unk1C = (uint8 *)&D_800821F8[index];
}

void func_80019FB4(void)
{
    SOUND_FUNC func;

    func = D_800823A0[Game_work.routine_50];
    D_80098958 |= 0x800;
    if (func != 0)
    {
        func(0);
    }
}

void Sound_call(sint16 id, uint32 arg1, uint32 arg2)
{
    SOUND_CALL *call;

    if (D_80098938 != D_800BE6D8)
    {
        D_80098938->kind      = 0;
        D_80098938->id        = id;
        D_80098938->args.arg1 = arg1;
        D_80098938->args.arg2 = arg2;
        D_80098938++;
    }
}

void Sound_call2(sint16 id, SOUND_ARGS *args)
{
    SOUND_CALL *call;

    if (D_80098938 != D_800BE6D8)
    {
        D_80098938->kind = 1;
        call             = D_80098938;
        call->id         = id;
        call->args.arg1  = args->arg1;
        call->args.arg2  = args->arg2;
        D_80098938       = ++call;
    }
}

sint32 func_8001A0A8(sint32 i)
{
    sint32 r;

    r = 0;
    if (D_80098AFA[i][0] != -1 && D_80098AF8[i][0] != -1)
    {
        r = SsIsEos(D_80098AF8[i][0], D_80098AFC[i][0]);
    }
    return r;
}

void func_8001A110(void)
{
    sint32 i;
    SOUND_CALL *call;
    SOUND_INFO *info;

    if (D_80098958 != 0)
    {
        func_8001AEF0();
        for (i = 0; i < 4; i++)
        {
            D_80098AFD[i][0] = func_8001A0A8(i);
        }
        call = D_800BE4F8;
        if (D_80098938 != call)
        {
            do
            {
                info = &D_8008241C[call->id];
                D_80082C64[info->flags >> 6](call);
                call++;
            } while (call != D_80098938);
        }
        D_80098938 = D_800BE4F8;
    }
}

sint32 func_8001A1FC(sint32 id)
{
    sint32 i;

    for (i = 0; i < 5; i++)
    {
        if (Game_work.sound_1b8[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

sint32 func_8001A238(sint32 id)
{
    sint32 i;

    for (i = 0; i < 5; i++)
    {
        if (D_80098AD0[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void func_8001A274(SOUND_POS *pos, uint32 pan, uint16 *left, uint16 *right, sint16 dist)
{
    uint16 l;
    uint16 r;
    sint32 fade;
    sint32 side;
    uint16 base;
    sint32 angle;

    base = (uint16)pan * 0x81;
    switch (pos->kind_0)
    {
        case 0:
            if ((sint32)((SOUND_CALL *)pos)->args.arg1 > 0)
            {
                *left  = (base * (0x80 - (uint16)((SOUND_CALL *)pos)->args.arg1)) / 128;
                *right = base;
            }
            else
            {
                *left  = base;
                *right = (base * (uint16)(((SOUND_CALL *)pos)->args.arg1 + 0x80)) / 128;
            }
            if (GAME_WORK_FLAG58 != 0)
            {
                l = *left;
                r = *right;
                if (r < l)
                {
                    *right = l;
                }
                else
                {
                    *left = r;
                }
            }
            *left  = (*left * (0x80 - (sint32)((SOUND_CALL *)pos)->args.arg2)) / 128;
            *right = (*right * (0x80 - (sint32)((SOUND_CALL *)pos)->args.arg2)) / 128;
            break;
        case 1:
            if (dist == 0)
            {
                *right = base;
                *left  = base;
                return;
            }
            angle = p_Player_work->rot_56 -
                    func_8001E83C(p_Player_work->x, p_Player_work->z, pos->x_4, pos->z_8);
            angle &= 0xFFF;
            side = (ccos(angle) << 7) >> 12;
            if (side < 0)
            {
                side = -side;
            }
            if (angle < 0x800)
            {
                *left  = base;
                *right = (base * side) / 128;
            }
            else
            {
                *left  = (base * side) / 128;
                *right = base;
            }
            if (GAME_WORK_FLAG58 != 0)
            {
                l = *left;
                r = *right;
                if (r < l)
                {
                    *right = l;
                }
                else
                {
                    *left = r;
                }
            }
            fade   = 0x1388 - dist;
            *left  = (*left * fade) / 5000;
            *right = (*right * fade) / 5000;
            break;
    }
    *left  = (*left * Sound_work.unk08) / 127;
    *right = (*right * Sound_work.unk08) / 127;
    *left  = (*left * Sound_work.unk10) / 127;
    *right = (*right * Sound_work.unk10) / 127;
}

sint32 func_8001A63C(sint32 n)
{
    sint32 f;
    sint32 a;

    a = 0x1000;
    if (n >= 0)
    {
        f = D_80082C70[n % 12];
        a <<= n / 12;
    }
    else
    {
        n = -n;
        f = D_80082CA0[n % 12];
        a >>= n / 12;
    }
    a *= f;
    return a >> 16;
}

// Interpolates between two pitch steps. Accumulating into lo (set twice) keeps it out of
// sched1's birthing-insn preference, so lo is saved before n + 1 is formed, as in retail.
sint32 func_8001A6DC(sint32 n, sint32 frac)
{
    sint32 lo;
    sint32 hi;

    lo = func_8001A63C(n);
    hi = func_8001A63C(n + 1);
    lo += ((hi - lo) * frac) / 128;
    return lo;
}

void func_8001A744(sint32 vab, SOUND_VOICE *voice, SOUND_TONE *tone, SOUND_POS *pos)
{
    SOUND_VOICE_ATTR attr;
    sint32 slot;

    slot = voice->voice_3 & 0x1F;
    func_8001A274(pos, tone->pan_2, &attr.volume_l, &attr.volume_r, SOUND_DIST_TBL[slot]);
    attr.voice       = 1 << slot;
    attr.mask        = 0x60093;
    attr.addr        = SsUtGetVagAddr((sint16)vab, tone->vag_16);
    attr.pitch       = func_8001A6DC(tone->note_6 - tone->note_4, tone->frac_5);
    attr.adsr1       = tone->adsr1_10;
    attr.adsr2       = tone->adsr2_12;
    D_80098B48[slot] = voice->priority_2 & 0xF;
    SpuSetKeyOnWithAttr(&attr);
}

sint32 func_8001A834(SOUND_VOICE *voice, SOUND_POS *pos)
{
    sint32 slot;
    sint32 status;
    sint32 dist;
    sint32 dz;
    sint32 dx;

    slot   = voice->voice_3 & 0x1F;
    status = SpuGetKeyStatus(1 << slot);
    if (status == 1 && (voice->priority_2 & 0xF) < D_80098B48[slot])
    {
        return 0;
    }
    if (pos->kind_0 == 1)
    {
        dx   = p_Player_work->x - pos->x_4;
        dz   = p_Player_work->z - pos->z_8;
        dx   = dx * dx;
        dz   = dz * dz;
        dist = SquareRoot0(dx + dz);
        if (dist >= 0x1388)
        {
            return 0;
        }
        if (status == 1 && (voice->priority_2 & 0xF) <= D_80098B48[slot] && dist >= 0xBB9)
        {
            return 0;
        }
        SOUND_DIST_TBL[slot] = dist;
    }
    return 1;
}

void func_8001A968(SOUND_POS *call)
{
    SOUND_INFO *info;
    sint32 slot;
    sint32 count;
    uint16 voice;
    SOUND_TONE *tone;
    uint16 vab;
    uint8 range;

    info = &D_8008241C[((SOUND_CALL *)call)->id];
    slot = func_8001A1FC(info->flags & 0x3F);
    if (slot == -1)
    {
        return;
    }
    range = info->byte_3;
    voice = range & 0x1F;
    tone  = (SOUND_TONE *)(SOUND_TONE_BASE + slot * 0x1820 +
                           (((info->byte_2 >> 4) + ((info->byte_1 & 0x7F) << 4)) << 5));
    count = (range & 0x60) >> 5;
    vab   = GAME_WORK_SLOT_VAB(slot);
    while (count >= 0 && voice < 0x18)
    {
        if (func_8001A834((SOUND_VOICE *)info, call))
        {
            func_8001A744(vab, (SOUND_VOICE *)info, tone, call);
        }
        tone++;
        count--;
        voice++;
    }
}

void func_8001AA8C(SOUND_CALL *call)
{
    SOUND_INFO *info;
    SOUND_SEQ *seq;
    sint32 slot;
    sint32 idx;
    SOUND_WORK *sw;

    info = &D_8008241C[call->id];
    slot = func_8001A1FC(info->flags & 0x3F);
    if (slot == -1)
    {
        return;
    }
    idx = func_8001A238(info->byte_1 & 0x7F);
    if (idx == -1)
    {
        return;
    }
    seq = &SOUND_SEQ_TBL[info->byte_2 >> 4];
    if (call->args.arg1 == 0 && seq->flag_5 != 0 && seq->id == call->id)
    {
        return;
    }
    if ((info->byte_2 & 0xF) < seq->prio)
    {
        return;
    }
    if (seq->seq != -1 && seq->kind != -1)
    {
        if (seq->kind == 0)
        {
            func_80070114(seq->seq);
            SsSeqClose(seq->seq);
        }
        else
        {
            func_8007013C(seq->seq, seq->arg_4);
            SsSepClose(seq->seq);
        }
    }
    seq->seq  = SsSeqOpen(D_80098AD4[idx][0], GAME_WORK_SLOT_VAB(slot));
    seq->prio = info->byte_2 & 0xF;
    seq->kind = 0;
    if (seq->seq != -1)
    {
        sw = &Sound_work; // needed: retail keeps the base in a register
        if (info->byte_1 != 0)
        {
            SsSeqPlay(seq->seq, 1, 0);
        }
        else
        {
            SsSeqPlay(seq->seq, 1, 1);
        }
        sw->unk12 = 0x7F;
        seq->id   = call->id;
    }
}

void func_8001AC58(SOUND_CALL *call)
{
    SOUND_INFO *info;
    SOUND_SEQ *seq;
    sint32 slot;
    sint32 idx;
    SOUND_WORK *sw;
    uint8 sep;

    sw   = &Sound_work;
    info = &D_8008241C[call->id];
    slot = func_8001A1FC(info->flags & 0x3F);
    if (slot == -1)
    {
        return;
    }
    idx = func_8001A238(info->byte_1 & 0x7F);
    if (idx == -1)
    {
        return;
    }
    seq = &SOUND_SEQ_TBL[info->byte_2 >> 4];
    if (call->args.arg1 == 0 && seq->flag_5 != 0 && seq->id == call->id)
    {
        sw->unk12 = 0x7F;
        return;
    }
    if ((info->byte_2 & 0xF) < seq->prio)
    {
        return;
    }
    if (seq->seq != -1 && seq->kind != -1)
    {
        if (seq->kind == 0)
        {
            func_80070114(seq->seq);
            SsSeqClose(seq->seq);
        }
        else
        {
            func_8007013C(seq->seq, seq->arg_4);
            SsSepClose(seq->seq);
        }
    }
    seq->seq =
        SsSepOpen(D_80098AD4[idx][0], GAME_WORK_SLOT_VAB(slot), D_80098AD0[idx].reserved01[0]);
    seq->prio = info->byte_2 & 0xF;
    seq->kind = 1;
    if (seq->seq != -1)
    {
        sep        = info->byte_3 & 0x1F;
        seq->arg_4 = sep;
        if (info->byte_1 & 0x80)
        {
            SsSepPlay(seq->seq, sep, 1, 0);
        }
        else
        {
            SsSepPlay(seq->seq, sep, 1, 1);
        }
        sw->unk12 = 0x7F;
        seq->id   = call->id;
    }
}

sint32 func_8001AE6C(sint32 flags, uint16 *p)
{
    sint32 r;

    r = 0;
    if (flags & 3)
    {
        r = 1;
        if (flags & 1)
        {
            *p -= D_80098840;
            if ((sint16)*p <= 0)
            {
                *p = 0;
                r  = 0;
            }
        }
        else
        {
            *p += D_80098840;
            if ((sint16)*p >= 0x7F)
            {
                *p = 0x7F;
                r  = 0;
            }
        }
    }
    return r;
}

// The table base in a local lets loop.c treat tbl[i] as an induction variable (retail strength-
// reduces it after hoisting the -1); indexing D_80098AFC directly leaves the base unhoisted.
void func_8001AEF0(void)
{
    sint32 i;
    sint16 *ph;
    uint8 *pc;
    sint16 vol;
    uint8 *reverb;
    SOUND_WORK *sw;
    uint8(*tbl)[8];

    sw = &Sound_work;
    if (!func_8001AE6C(D_80098788 & 3, (uint16 *)&sw->unk0C))
    {
        D_80098788 &= 0xFC;
    }
    if (!func_8001AE6C((D_80098788 & 0xC) >> 2, (uint16 *)&sw->unk10))
    {
        D_80098788 &= 0xF3;
    }
    if (!func_8001AE6C((D_80098788 & 0x30) >> 4, (uint16 *)&sw->unk12))
    {
        D_80098788 &= 0xCF;
    }
    D_80098958 |= 0x400;
    if (!func_8001AE6C(D_80098788 >> 6, (uint16 *)&sw->unk0E))
    {
        if (D_80098788 & 0x40)
        {
            func_8001D494(0, 1, 0);
        }
        D_80098788 &= 0x3F;
    }
    vol = sw->unk04 * sw->unk0C / 127;
    SsSetMVol(vol, vol);
    if (!(sw->flags & SOUND_FLAG_CD_OFF))
    {
        vol = sw->unk06 * sw->unk0E / 127;
        SsSetSerialVol(SS_SERIAL_A, vol, vol);
        if (GAME_WORK_FLAG58)
        {
            sw->atv.val0 = 0x7F;
            sw->atv.val1 = 0x7F;
            sw->atv.val2 = 0x7F;
            sw->atv.val3 = 0x7F;
        }
        else
        {
            sw->atv.val0 = 0x7F;
            sw->atv.val1 = 0;
            sw->atv.val2 = 0x7F;
            sw->atv.val3 = 0;
        }
        CdMix(&sw->atv);
    }
    if (GAME_WORK_FLAG58)
    {
        func_80075AA4();
    }
    else
    {
        func_80075AB8();
    }
    ph  = D_80098AF8[0];
    tbl = D_80098AFC;
    for (i = 0; i < 4; i++, ph += 4)
    {
        pc = tbl[i];
        if (*ph != -1 && ((sint8 *)pc)[-2] != -1)
        {
            vol = sw->unk0A * sw->unk12 / 127;
            if (((sint8 *)pc)[-2] == 0)
            {
                func_80070634(*ph, vol, vol);
            }
            else
            {
                func_80070694(*ph, *pc, vol, vol);
            }
        }
    }
    D_80098958 &= ~0x400;
    if (sw->unk18 != sw->unk19)
    {
        func_80070974(0);
        SsSetReservedVoice(sw->unk18);
    }
    sw->unk19 = sw->unk18;
    reverb    = sw->unk1C;
    switch (sw->unk1A)
    {
        case 0:
            if (reverb != sw->unk20)
            {
                SsUtSetReverbType(reverb[0]);
                func_800721C4();
                sw->unk1B = 30;
                sw->unk1A++;
            }
            break;
        case 1:
            if (--sw->unk1B == 0)
            {
                if (reverb[0])
                {
                    SsUtSetReverbDepth(reverb[2], reverb[2]);
                    SsSetRVol(reverb[1], reverb[1]);
                }
                sw->unk1A = 0;
                sw->unk20 = reverb;
            }
            break;
    }
}

void Sound_key_off_voice(sint32 voice)
{
    SsUtKeyOffV(voice);
}

void func_8001B314(void)
{
    SpuSetKey(0, 0xFF8000);
}

void func_8001B33C(void)
{
    sint32 i;
    sint16 *ph;
    uint8 *pc;
    sint32 kind;

    ph = D_80098AF8[0];
    for (i = 0; i < 4; i++, ph += 4)
    {
        pc = D_80098AFC[i];
        if (*ph != -1 && (kind = ((sint8 *)pc)[-2]) != -1)
        {
            if (kind == 0)
            {
                func_80070114(*ph);
            }
            else
            {
                func_8007013C(*ph, *pc);
            }
        }
    }
}
