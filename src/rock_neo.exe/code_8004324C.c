#include "common.h"
#include "code_8004324C.h"
#include "code_8002E7A8.h"
#include "code_80043F34.h"
#include "game.h"
#include "player.h"
#include "code_80037534.h"
#include "code_80048620.h"
#include "code_80037FB4.h"
#include "code_8005C258.h"
#include "sound.h"

// Small data (.sdata 0x80097DA0-0x80097DDB). Only this file uses it, always indexed or by address,
// so it's lui-based here too. Tables of the shot launched by func_800437F8; the uint8/uint32 ones
// are indexed by Player_work[0].rec[1].idx[0] or idx[2].
HIT_ENT D_80097DA0   = {-16, 16, -16, 16, -16, 16}; // collision box (hit_78)
uint32 D_80097DAC[8] = {0x3EB4002E, 0x3EB4002E, 0x3EB4002E, 0x3EB5002E,
                        0x3EB5002E, 0x3EB5002E, 0x3EB6002E, 0x3EB6002E}; // PL_SHL_WORK.code_88, by idx[0]
uint8 D_80097DCC[8]  = {24, 32, 42, 32, 42, 56, 42, 64};                 // field_98, by idx[0]
uint8 D_80097DD4[8]  = {100, 100, 100, 100, 100, 100, 120, 120};         // speed (spd = dir * n >> 4), by idx[2]

sint32 func_8004324C(PL_WORK *pl)
{
    if ((pl->unk174 & 0xC0) || pl->unk177)
    {
        return 1;
    }
    return 0;
}

sint32 Money_check(sint32 amount)
{
    return -(Game_work.money < (uint32)-amount);
}

sint32 Money_add(sint32 amount, sint32 b, sint32 c)
{
    if (b == 0)
    {
        if (amount > 0)
        {
            Game_work.money += amount;
            if (Game_work.money > MONEY_MAX)
            {
                Game_work.money = MONEY_MAX;
            }
        }
        else
        {
            Game_work.money += amount;
            if (Game_work.money > MONEY_MAX)
            {
                Game_work.money = 0;
            }
            if (c)
            {
                Game_work.unk024 -= amount;
            }
            else
            {
                Game_work.unk020 -= amount;
            }
        }
    }
}

void func_80043340(sint32 amount, sint32 n)
{
    PL_WORK *pl;

    pl = &Player_work[n];
    pl->life += amount;
    if (pl->life > pl->life_max)
    {
        pl->life = pl->life_max;
    }
    if (amount < 0 && n == 0)
    {
        Game_work.unk04C -= amount;
    }
}

void func_800433C0(PL_SHL_WORK *wp)
{
    D_8008A0CC[wp->routine_8](wp);
}

void func_800433FC(PL_SHL_WORK *wp)
{
    SVECTOR v;  // unused (0x18 bytes in the frame, the locals of func_800437F8's
    VECTOR out; // launch vector)
    PL_WORK *pl;

    wp->field_E = wp->pos.pad;
    pl          = func_80036294((uint8)wp->field_C);
    pl->unk198  = 0;
    func_800354E0(wp->slot_D);
    wp->timer_B = 11;
    wp->routine_8++;
    wp->owner_C4.hit_0  = 0;
    wp->owner_C4.mask_4 = 0;
    wp->hit_78          = 0;
    if (wp->field_E)
    {
        wp->old = pl->joint_pos[11];
    }
    else
    {
        wp->old = pl->joint_pos[14];
    }
    wp->pos = wp->old;
    func_800435F8(wp);
    Sound_call2(0x96, &wp->pos);
}

void func_800434F0(PL_SHL_WORK *wp)
{
    PL_WORK *pl;
    PL_WORK *cur;

    pl      = func_80036294((uint8)wp->field_C);
    cur     = func_80036294((uint8)wp->field_C);
    wp->old = cur->pos;
    if (--wp->timer_B == 0)
    {
        Close_PL_SHL_WORK(wp);
    }
    else if (func_80037694((MODEL_WORK *)wp, 0))
    {
        func_80043740(wp);
        wp->routine_8++;
        pl->unk198 = 1;
    }
    else
    {
        func_800435F8(wp);
    }
}

void func_800435BC(PL_SHL_WORK *wp)
{
    PL_WORK *pl;

    pl         = func_80036294((uint8)wp->field_C);
    pl->unk198 = 0;
    Close_PL_SHL_WORK(wp);
}

void func_800435F8(PL_SHL_WORK *wp)
{
    sint32 id;
    PL_WORK *pl;

    id = wp->field_C;
    pl = func_80036294((uint8)id);
    if (wp->field_E)
    {
        wp->pos = pl->joint_pos[11];
        if (id)
        {
            func_8003430C(&wp->pos, 0x20, &wp->old, 0x20, 0x200, 0x6000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
        else
        {
            func_8003430C(&wp->pos, 0x20, &wp->old, 0x20, 0x200, 0x4000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
    }
    else
    {
        wp->pos = pl->joint_pos[14];
        if (id)
        {
            func_8003430C(&wp->pos, 0x20, &wp->old, 0x20, 0x200, 0x6000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
        else
        {
            func_8003430C(&wp->pos, 0x20, &wp->old, 0x20, 0x200, 0x4000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
    }
    wp->old = wp->pos;
}

void func_80043740(PL_SHL_WORK *wp)
{
    W48_84_WORK *e;

    e = (W48_84_WORK *)func_80031618();
    if (e != 0)
    {
        e->routine_0 = 1;
        e->id_2      = 0x84;
        e->type_3    = 0;
        e->pos_1C[0] = wp->pos.vx;
        e->pos_1C[1] = wp->pos.vy;
        e->pos_1C[2] = wp->pos.vz;
    }
}

void func_800437A8(PL_SHL_WORK *wp)
{
    D_8008A0D8[wp->routine_8](wp);
    func_80051BAC((MODEL_WORK *)wp);
}

void func_800437F8(PL_SHL_WORK *wp)
{
    SVECTOR v;
    VECTOR out;
    MATRIX m;
    uint8 spd;

    wp->routine_0 |= 0x2A;
    wp->flags |= 0x20;
    func_8005D97C();
    wp->owner_C4.hit_0  = 0;
    wp->owner_C4.mask_4 = 0;
    wp->hit_78          = &D_80097DA0;
    v.vx                = func_80039B80();
    v.vy                = wp->field_64 & 0xFFF;
    v.vz                = 0;
    RotMatrixYXZ(&v, &m);
    v.vx = 0;
    v.vy = 0;
    v.vz = -0x1000;
    ApplyMatrix(&m, &v, &out);
    v.vx          = out.vx;
    v.vy          = out.vy;
    v.vz          = out.vz;
    spd           = D_80097DD4[Player_work[0].rec[1].idx[2]];
    wp->spd.vx    = (v.vx * spd) >> 4;
    wp->spd.vy    = (v.vy * spd) >> 4;
    wp->spd.vz    = (v.vz * spd) >> 4;
    wp->dir_A4    = v;
    wp->add.vx    = 0;
    wp->add.vy    = 0;
    wp->add.vz    = 0;
    wp->code_88   = 0x3D48002E;
    wp->code_88   = D_80097DAC[Player_work[0].rec[1].idx[0]];
    wp->rgbc_8C   = 0x2E808080;
    wp->pos_90[0] = wp->pos.vx = wp->pos_l.vx >> 16;
    wp->pos_90[1] = wp->pos.vy = wp->pos_l.vy >> 16;
    wp->pos_90[2] = wp->pos.vz = wp->pos_l.vz >> 16;
    wp->old_l                  = wp->pos_l;
    wp->old                    = wp->pos;
    wp->field_96               = 0xC0;
    wp->field_97               = 0x60;
    wp->field_98               = D_80097DCC[Player_work[0].rec[1].idx[0]];
    wp->field_7C               = 0;
    wp->timer_B                = 0;
    func_80043DF8(wp, &m);
    wp->field_9 = 0;
    wp->routine_8++;
    if (wp->field_A)
    {
        wp->old.pad = wp->pos.pad = 0x6208;
    }
    else
    {
        wp->old.pad = wp->pos.pad = 0x4208;
    }
    if (wp->type_3 >= 0x80 && (*(uint32 *)&wp->tgt_BC.vx | *(uint32 *)&wp->tgt_BC.vz) == 0)
    {
        func_800354E0(wp->slot_D);
        wp->type_3 = 0;
    }
    func_80043E78(wp);
    Sound_call2(0x9A, &wp->pos);
}

#ifdef NON_MATCHING
// Two differences: GCC turns the hit flag into xori/sltu where the target branches (if/else,
// switch, ternary, goto and two calls all tried), and the speed multiplies load dir.vx before
// the table byte (register swap v0/v1).
void func_80043A8C(PL_SHL_WORK *wp)
{
    SVECTOR dir;
    SVECTOR nrm;
    VECTOR d;
    sint32 id;
    uint8 spd;
    sint32 hit;

    id = func_80037694((MODEL_WORK *)wp, 0);
    if (id != 0 || wp->field_7C != 0)
    {
        if (id == 0x7FFF)
        {
            hit = 0;
        }
        else
        {
            hit = 1;
        }
        func_80043E00(wp, hit);
        goto close;
    }
    wp->old_l = wp->pos_l;
    wp->old   = wp->pos;
    if (wp->timer_B++ < func_80037634(Player_work, 1))
    {
        if (wp->type_3 >= 0x80)
        {
            if (*(uint32 *)&wp->tgt_BC.vx | *(uint32 *)&wp->tgt_BC.vz)
            {
                d.vx = wp->tgt_BC.vx - wp->pos.vx;
                d.vy = wp->tgt_BC.vy - wp->pos.vy;
                d.vz = wp->tgt_BC.vz - wp->pos.vz;
                if (d.vx < -0x687E || d.vx > 0x687E || d.vy < -0x687E || d.vy > 0x687E || d.vz < -0x687E || d.vz > 0x687E)
                {
                    d.vx >>= 2;
                    d.vy >>= 2;
                    d.vz >>= 2;
                }
                VectorNormalS(&d, &nrm);
                if (wp->timer_B < 4)
                {
                    func_80033F04(&dir, &nrm, &wp->dir_A4, 0x424, 0x0F746EA4);
                }
                else if (wp->timer_B < 9)
                {
                    func_80033F04(&dir, &nrm, &wp->dir_A4, 0x8F, 0x0FFD813C);
                }
                else
                {
                    func_80033F04(&dir, &nrm, &wp->dir_A4, 0x47, 0x0FFF604C);
                    func_800354E0(wp->slot_D);
                    wp->type_3 = 0;
                }
                wp->dir_A4 = dir;
                spd        = D_80097DD4[Player_work[0].rec[1].idx[2]];
                wp->spd.vx = (dir.vx * spd) >> 4;
                wp->spd.vy = (dir.vy * spd) >> 4;
                wp->spd.vz = (dir.vz * spd) >> 4;
            }
            else
            {
                func_800354E0(wp->slot_D);
                wp->type_3 = 0;
            }
        }
        wp->pos_l.vx += wp->spd.vx << 8;
        wp->pos_l.vy += wp->spd.vy << 8;
        wp->pos_l.vz += wp->spd.vz << 8;
        wp->pos_90[0] = wp->pos.vx = wp->pos_l.vx >> 16;
        wp->pos_90[1] = wp->pos.vy = wp->pos_l.vy >> 16;
        wp->pos_90[2] = wp->pos.vz = wp->pos_l.vz >> 16;
        wp->field_9A += 5;
    }
    else
    {
    close:
        Close_PL_SHL_WORK(wp);
        if (wp->type_3 >= 0x80)
        {
            func_800354E0(wp->slot_D);
        }
        return;
    }
    func_80043E78(wp);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8004324C", func_80043A8C);
#endif

void func_80043DF8(PL_SHL_WORK *wp, MATRIX *m)
{
}

void func_80043E00(PL_SHL_WORK *wp, uint8 arg)
{
    W48_82_WORK *e;

    e = (W48_82_WORK *)func_80031618();
    if (e != 0)
    {
        e->routine_0 = 9;
        e->id_2      = 0x82;
        e->pos_1C[0] = wp->pos.vx;
        e->pos_1C[1] = wp->pos.vy;
        e->pos_1C[2] = wp->pos.vz;
        e->type_3    = 1;
        e->field_C   = arg;
    }
}

void func_80043E78(PL_SHL_WORK *wp)
{
    uint32 pad;
    sint32 val;

    pad = wp->field_98;
    val = func_800375D4(Player_work, 1);
    if (wp->field_C)
    {
        func_8003430C(&wp->pos, pad, &wp->old, pad, 0x200, 0x6000, wp->kind_1, &wp->owner_C4, val | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&wp->pos, pad, &wp->old, pad, 0x200, 0x4000, wp->kind_1, &wp->owner_C4, val | 0x8000000, 0, 0x80);
    }
}
