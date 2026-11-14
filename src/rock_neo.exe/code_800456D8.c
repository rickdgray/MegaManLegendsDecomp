#include "common.h"
#include "psyq/libc.h"
#include "code_800456D8.h"
#include "code_80027678.h"
#include "code_80037FB4.h"
#include "code_8004324C.h"
#include "scratch.h"
#include "game.h"
#include "sound.h"
#include "player.h"

// Small uninitialized statics (.sbss 0x800986D0-0x800986D8).
static sint32 D_800986D0[2];

// Called only from this file, ahead of their definitions.
void func_80046F38(void);
void func_80045CE8(BYTES8 *pos, uint32 count, uint32 weights, uint32 kind);
void func_80046B34(BYTES8 *pos, uint32 spec);
sint32 func_800482A8(WORK_48 *wp);
sint32 svec_distance(SVECTOR *a, SVECTOR *b);
void func_80045AB4(WORK_48 *wp);
void func_80045BC8(WORK_48 *wp);
void func_80046890(WORK_48 *wp);
void func_800469A4(WORK_48 *wp);
void func_80046A0C(WORK_48 *wp);

void func_800456D8(WORK_48 *wp)
{
    if (rand() & 1)
    {
        wp->routine_0 |= 2;
    }
    Model_work_init((ATTACH_WORK *)wp, &wp->flag_3);
    wp->routine_8++;
    Sound_call2(0x9B, (sint32 *)&wp->pos_38);
    func_80045AB4(wp);
    func_80045BC8(wp);
}

void func_80045750(WORK_48 *wp)
{
    SVECTOR pos;
    BYTES8 old;
    MATRIX *m;
    sint32 hit;

    old = *(BYTES8 *)&wp->pos_38;
    wp->field_2C += wp->field_32;
    wp->pos_38.vx += wp->field_2C;
    wp->field_2E += wp->field_34;
    wp->pos_38.vy += wp->field_2E;
    wp->field_30 += wp->field_36;
    wp->pos_38.vz += wp->field_30;
    pos = *&wp->pos_38;
    func_80045AB4(wp);
    hit = func_8004B5CC(&pos, &old, 1, &D_8008A310[wp->field_A]);
    if (hit != 0)
    {
        wp->pos_38.vx = pos.vx;
        wp->pos_38.vy = pos.vy;
        wp->pos_38.vz = pos.vz;
        if (hit & 0x1000)
        {
            wp->pos_38.pad = wp->pos_38.pad >> 1;
            if ((sint16)wp->field_2E >> 1 < 2)
            {
                m            = (MATRIX *)&wp->field_18;
                wp->timer_B  = 1;
                wp->field_2E = 0;
                m->m[2][1]   = 0;
                m->m[2][0]   = 0;
                m->m[1][2]   = 0;
                m->m[1][0]   = 0;
                m->m[0][2]   = 0;
                m->m[0][1]   = 0;
                wp->routine_8++;
                m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
                RotMatrixY(wp->field_C.angle, m);
            }
            wp->field_2E = (sint16)wp->field_2E >> 1;
        }
        func_8004AC8C(&wp->field_2C, hit);
    }
    func_80045BC8(wp);
}

void func_80045918(WORK_48 *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_8 += 2;
    }
}

void func_8004594C(WORK_48 *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
    }
}

void func_80045980(WORK_48 *wp)
{
    func_80031988(wp);
}

void func_800459A0(WORK_48 *wp)
{
    wp->field_2E = -0x28;
    wp->field_34 = 5;
    wp->routine_8++;
}

void func_800459C0(WORK_48 *wp)
{
    MATRIX *m;

    m          = (MATRIX *)&wp->field_18; // the matrix overlays the 0x18..0x37 fields
    m->m[2][1] = 0;
    m->m[2][0] = 0;
    m->m[1][2] = 0;
    m->m[1][0] = 0;
    m->m[0][2] = 0;
    m->m[0][1] = 0;
    m->m[0][0] = m->m[2][2] = wp->pos_38.pad >> 1;
    m->m[1][1]              = wp->pos_38.pad;
    RotMatrixY(0x180, m);
    wp->field_2E += wp->field_34;
    wp->pos_38.vy += wp->field_2E;
    wp->pos_38.pad -= D_80097E64[wp->field_A] >> 3;
    if (wp->field_2E >= 0)
    {
        wp->routine_8++;
    }
}

void func_80045A7C(WORK_48 *wp)
{
    Sound_call2(0xCF, (sint32 *)&wp->pos_38);
    func_80031988(wp);
}

void func_80045AB4(WORK_48 *wp)
{
    SVECTOR rot;
    MATRIX m;
    VECTOR scale;
    sint32 r;

    m = *(MATRIX *)&wp->field_18;
    r = rand();
    wp->field_C.hw[1] += 0x80 + (r & 0x7F);
    rot.vx = wp->field_C.hw[1];
    wp->field_C.hw[0] += 0x40 + (r & 0x3F);
    rot.vy = wp->field_C.hw[0];
    rot.vz = 0;
    RotMatrix(&rot, &m);
    scale.vx = scale.vy = scale.vz = wp->pos_38.pad;
    ScaleMatrix(&m, &scale);
    *(MATRIX *)&wp->field_18 = m;
}

void func_80045BC8(WORK_48 *wp)
{
    uint32 r;

    r = D_80097E64[wp->field_A + 6]; // table at 0x80097E70
    if ((uint32)(Player_work[0].pos.vx - wp->pos_38.vx + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[0].pos.vz - wp->pos_38.vz + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[0].pos.vy - wp->pos_38.vy + r) <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
    }
    if ((uint32)(Player_work[1].pos.vx - wp->pos_38.vx + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[1].pos.vz - wp->pos_38.vz + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[1].pos.vy - wp->pos_38.vy + r) <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
    }
}

// Spawns `count` effects around `pos`, spread over a circle. `weights` packs four byte weights
// choosing the kind of each (tables D_8009A5A0..); `kind` selects a row of D_8008A2B0.
// Whole body matches; only the prologue differs: the target saves/moves the arguments in the
// order a2 (s5), a3 (s0), a1 (s7), this build does a1, a2, a3.
#ifdef NON_MATCHING
void func_80045CE8(BYTES8 *pos, uint32 count, uint32 weights, uint32 kind)
{
    WORK_48 *wp;
    uint32 i;
    uint32 r;
    sint32 sel;
    uint32 acc;
    sint32 ang;
    sint32 step;
    sint32 idx;
    sint32 rnd;

    if (count > 0x10)
    {
        count = 0x10;
    }
    if (kind > 5)
    {
        kind = 5;
    }
    step = D_80097E7A[count];
    ang  = rand() & 0xFFF;
    for (i = 0; i < count; i++, ang += step)
    {
        wp = func_80031618();
        if (wp != 0)
        {
            wp->routine_0 = 5;
            wp->flag_3    = 0;
            wp->field_2   = 0x86;
            r             = rand() & 0xFF;
            acc           = weights >> 24;
            if (r < acc)
            {
                wp->u_44.ptr = D_8009A5A0;
                wp->field_9  = 0;
            }
            else
            {
                acc += (weights >> 16) & 0xFF;
                if (r < acc)
                {
                    wp->u_44.ptr = D_8009A5D0;
                    wp->field_9  = 1;
                }
                else
                {
                    acc += (weights >> 8) & 0xFF;
                    if (r < acc)
                    {
                        wp->u_44.ptr = D_8009A600;
                        wp->field_9  = 2;
                    }
                    else
                    {
                        acc += weights & 0xFF;
                        if (r < acc)
                        {
                            wp->u_44.ptr = D_8009A630;
                            wp->field_9  = 3;
                        }
                        else
                        {
                            wp->flag_3   = 1;
                            wp->u_44.ptr = D_8009A660;
                            wp->field_9  = 4;
                        }
                    }
                }
            }
            *(BYTES8 *)&wp->pos_38 = *pos;
            rnd                    = rand();
            idx                    = D_8008A2B0[kind][rnd & 0xF];
            wp->field_A            = idx;
            wp->pos_38.pad         = D_80097E64[idx];
            wp->field_C.hw[0]      = rnd & 0xFFF;
            wp->field_C.hw[1]      = (uint32)rnd >> 4;
            wp->field_2C           = (uint32)(rcos(ang) * (D_80097E9C[idx] + (rnd & 3))) >> 12;
            wp->field_2E           = D_80097EA8[idx] + (rnd & 3);
            wp->field_30           = (uint32)(rsin(ang) * (D_80097E9C[idx] + (rnd & 3))) >> 12;
            wp->field_32           = 0;
            wp->field_36           = 0;
            wp->field_34           = 5;
            sel                    = rand() & 3;
            switch (sel)
            {
                case 0:
                    wp->field_40 = 0x606060;
                    break;
                case 1:
                    wp->field_40 = 0x8080;
                    break;
                case 2:
                    wp->field_40 = 0x20;
                    break;
                case 3:
                    wp->field_40 = 0x200000;
                    break;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80045CE8);
#endif

// Target copies the result into v1 (`move v1,v0`) after the call; GCC drops the dead copy.
#ifdef NON_MATCHING
void func_80045FE4(WORK_48 *wp)
{
    uint32 kind;

    kind = func_8002FE74(wp->kind_1);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80045FE4);
#endif

#ifdef NON_MATCHING
void func_80046008(WORK_48 *wp)
{
    uint32 kind;

    kind = func_8002FE74(wp->kind_1);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80046008);
#endif

void func_8004602C(WORK_48 *wp)
{
    uint32 *p;
    uint32 a;
    uint32 b;
    uint32 c;
    uint32 d;

    if (D_800986D0[0] != System_timer)
    {
        func_80046F38();
    }
    D_8008A6A8[wp->routine_8](wp);
    if (wp->flag_3 != 0 && (wp->routine_0 & 2) && wp->routine_8 < 5)
    {
        wp->field_9++;
        if (wp->field_9 >= 4)
        {
            wp->field_9 = 0;
        }
        a    = D_80097EC0[wp->field_9][0];
        b    = D_80097EC0[wp->field_9][1];
        c    = D_80097EC0[wp->field_9][2];
        d    = D_80097EC0[wp->field_9][3];
        p    = func_8002D464();
        p[1] = 0x2C808080;
        p[2] = *(sint32 *)&wp->pos_38;
        p[4] = *(uint32 *)&wp->pos_38.vz;
        p[3] = a | 0x3D080000;
        p[5] = b | 0xE0000;
        p[7] = c;
        p[9] = d;
        p[6] = D_80097EE8[wp->field_A];
        p[8] = 0;
    }
}

void func_800461A4(WORK_48 *wp)
{
    wp->routine_0 |= 2;
    Model_work_init((ATTACH_WORK *)wp, &wp->flag_3);
    wp->routine_8++;
    Sound_call2(0x9B, (sint32 *)&wp->pos_38);
    if (wp->flag_3 != 0)
    {
        func_80046890(wp);
    }
    else
    {
        func_800469A4(wp);
    }
    func_80046A0C(wp);
    wp->timer_B = 0xFF;
}

void func_8004622C(WORK_48 *wp)
{
    SVECTOR pos;
    BYTES8 old;
    MATRIX *m;
    sint32 hit;

    old = *(BYTES8 *)&wp->pos_38;
    wp->field_2C += wp->field_32;
    wp->pos_38.vx += wp->field_2C;
    wp->field_2E += wp->field_34;
    wp->pos_38.vy += wp->field_2E;
    wp->field_30 += wp->field_36;
    wp->pos_38.vz += wp->field_30;
    pos = *&wp->pos_38;
    if (wp->flag_3 != 0)
    {
        func_80046890(wp);
    }
    else
    {
        func_800469A4(wp);
    }
    hit = func_8004B5CC(&pos, &old, 1, &D_8008A618[wp->flag_3][wp->field_A]);
    if (hit != 0)
    {
        wp->pos_38.vx = pos.vx;
        wp->pos_38.vy = pos.vy;
        wp->pos_38.vz = pos.vz;
        if ((hit & 0x1000) || --wp->timer_B == 0)
        {
            if ((sint16)wp->field_2E >> 1 < 2)
            {
                m            = (MATRIX *)&wp->field_18;
                wp->timer_B  = 0x96;
                wp->field_2E = 0;
                m->m[2][1]   = 0;
                m->m[2][0]   = 0;
                m->m[1][2]   = 0;
                m->m[1][0]   = 0;
                m->m[0][2]   = 0;
                m->m[0][1]   = 0;
                wp->routine_8++;
                m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
                RotMatrixY(wp->field_C.angle, m);
            }
            wp->field_2E = (sint16)wp->field_2E >> 1;
        }
        func_8004AC8C(&wp->field_2C, hit);
    }
    func_80046A0C(wp);
}

// Best attempt: only the register of the limit differs (target keeps ground - h in v0, this
// build puts it in v1, h's register).
#ifdef NON_MATCHING
void func_80046438(WORK_48 *wp)
{
    BYTES8 old;
    sint32 ground;
    sint32 h;

    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
        wp->timer_B = (rand() & 7) + 0x1E;
    }
    ground = func_80048EA4((sint32 *)&wp->pos_38, &D_8008A618[wp->flag_3][wp->field_A], wp->field_2E, 0xFFFF);
    h      = D_8008A622[wp->flag_3][wp->field_A][0] + 1;
    ground -= h;
    old = *(BYTES8 *)&wp->pos_38;
    if (wp->pos_38.vy < ground)
    {
        wp->field_2E += wp->field_34;
        wp->pos_38.vy += wp->field_2E;
    }
    func_8004B5CC((sint32 *)&wp->pos_38, &old, 1, &D_8008A618[wp->flag_3][wp->field_A]);
    func_80046A0C(wp);
    if (wp->flag_3 == 0)
    {
        func_800469A4(wp);
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80046438);
#endif

// Best attempt: only the register of the limit differs (see func_80046438).
#ifdef NON_MATCHING
void func_800465C8(WORK_48 *wp)
{
    BYTES8 old;
    sint32 ground;
    sint32 h;

    wp->routine_0 ^= 2;
    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
    }
    ground = func_80048EA4((sint32 *)&wp->pos_38, &D_8008A618[wp->flag_3][wp->field_A], wp->field_2E, 0xFFFF);
    h      = D_8008A622[wp->flag_3][wp->field_A][0] + 1;
    ground -= h;
    old = *(BYTES8 *)&wp->pos_38;
    if (wp->pos_38.vy < ground)
    {
        wp->field_2E += wp->field_34;
        wp->pos_38.vy += wp->field_2E;
    }
    func_8004B5CC((sint32 *)&wp->pos_38, &old, 1, &D_8008A618[wp->flag_3][wp->field_A]);
    func_80046A0C(wp);
    if (wp->flag_3 == 0)
    {
        func_800469A4(wp);
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_800465C8);
#endif

void func_8004674C(WORK_48 *wp)
{
    func_80031988(wp);
}

void func_8004676C(WORK_48 *wp)
{
    wp->field_2E = -0x28;
    wp->field_34 = 5;
    wp->routine_8++;
}

void func_8004678C(WORK_48 *wp)
{
    MATRIX *m;

    m          = (MATRIX *)&wp->field_18; // the matrix overlays the 0x18..0x37 fields
    m->m[2][1] = 0;
    m->m[2][0] = 0;
    m->m[1][2] = 0;
    m->m[1][0] = 0;
    m->m[0][2] = 0;
    m->m[0][1] = 0;
    m->m[0][0] = m->m[2][2] = wp->pos_38.pad >> 1;
    m->m[1][1]              = wp->pos_38.pad;
    RotMatrixY(0x180, m);
    wp->field_2E += wp->field_34;
    wp->pos_38.vy += wp->field_2E;
    wp->pos_38.pad -= D_80097EE0[wp->field_A] >> 3;
    if (wp->field_2E >= 0)
    {
        wp->routine_8++;
    }
}

void func_80046848(WORK_48 *wp)
{
    uint32 id;

    if (wp->flag_3 != 0)
    {
        id = 0x9E;
    }
    else
    {
        id = 0x9D;
    }
    Sound_call2(id, (sint32 *)&wp->pos_38);
    func_80031988(wp);
}

void func_80046890(WORK_48 *wp)
{
    SVECTOR rot;
    MATRIX m;
    VECTOR scale;
    sint32 r;

    m = *(MATRIX *)&wp->field_18;
    r = rand();
    wp->field_C.hw[1] += 0x80 + (r & 0x7F);
    rot.vx = wp->field_C.hw[1];
    wp->field_C.hw[0] += 0x40 + (r & 0x3F);
    rot.vy = wp->field_C.hw[0];
    rot.vz = 0;
    RotMatrix(&rot, &m);
    scale.vx = scale.vy = scale.vz = wp->pos_38.pad;
    ScaleMatrix(&m, &scale);
    *(MATRIX *)&wp->field_18 = m;
}

void func_800469A4(WORK_48 *wp)
{
    MATRIX *m;

    m          = (MATRIX *)&wp->field_18; // the matrix overlays the 0x18..0x37 fields
    m->m[2][1] = 0;
    m->m[2][0] = 0;
    m->m[1][2] = 0;
    m->m[1][0] = 0;
    m->m[0][2] = 0;
    m->m[0][1] = 0;
    m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
    RotMatrixY(wp->field_C.angle, m);
    wp->field_C.angle += 0x100;
}

void func_80046A0C(WORK_48 *wp)
{
    uint32 r;
    uint32 i;

    i = wp->field_A;
    r = D_80097EEC[wp->flag_3][i];
    if ((uint32)(Player_work[0].pos.vx - wp->pos_38.vx + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[0].pos.vz - wp->pos_38.vz + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[0].pos.vy - wp->pos_38.vy + r) <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
        if (wp->flag_3 == 0)
        {
            func_80043294(D_8008A678[Game_work.unk05B][i], 0, 0);
        }
        else
        {
            func_80043340(D_8008A680[Game_work.unk05B][i], 0);
        }
    }
}

// Two bursts of effects around `pos`; `spec` packs four bytes: count and kind row (D_8008A5A8)
// of the first burst (bits 0-7, 8-15), then of the second (bits 16-23, 24-31).
// Register allocation only: the target keeps the first burst's count/kind in s7/s0 and spills the
// second burst's (sp18, sp20) plus both table pointers (sp28, sp30); here count2 lands in a
// register, so the frame is 0x60 instead of 0x70.
#ifdef NON_MATCHING
void func_80046B34(BYTES8 *pos, uint32 spec)
{
    WORK_48 *wp;
    MATRIX *m;
    uint32 i;
    uint32 count;
    uint32 kind;
    uint32 count2;
    uint32 kind2;
    sint32 ang;
    sint32 step;
    uint32 idx;
    sint32 rnd;

    count  = spec & 0xFF;
    kind   = (spec >> 8) & 0xFF;
    count2 = (spec >> 16) & 0xFF;
    kind2  = spec >> 24;
    if (count > 0x10)
    {
        count = 0x10;
    }
    step = D_80097EFA[count];
    ang  = rand() & 0xFFF;
    for (i = 0; i < count; i++, ang += step)
    {
        wp = func_80031618();
        if (wp != 0)
        {
            wp->routine_0 = 0x15;
            wp->flag_3    = 0;
            wp->field_2   = 0x87;
            rand();
            wp->field_9            = 0;
            *(BYTES8 *)&wp->pos_38 = *pos;
            wp->pos_38.vy -= 0x14;
            rnd = rand();
            idx = D_8008A5A8[kind][rnd & 0xF];
            if (idx >= 5)
            {
                func_80031988(wp);
            }
            else
            {
                wp->field_A       = idx;
                wp->u_44.ptr      = D_8009A6C0[idx];
                wp->pos_38.pad    = D_80097EE0[idx];
                wp->field_C.hw[0] = rnd & 0xFFF;
                wp->field_C.hw[1] = (uint32)rnd >> 4;
                wp->field_2C      = (uint32)(rcos(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
                wp->field_2E      = D_80097F24[idx] + (rnd & 3);
                wp->field_30      = (uint32)(rsin(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
                wp->field_32      = 0;
                wp->field_36      = 0;
                wp->field_34      = 5;
                wp->field_40      = 0x02808080;
                m                 = (MATRIX *)&wp->field_18;
                m->m[2][1]        = 0;
                m->m[2][0]        = 0;
                m->m[1][2]        = 0;
                m->m[1][0]        = 0;
                m->m[0][2]        = 0;
                m->m[0][1]        = 0;
                m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
            }
        }
    }
    if (count2 > 0x10)
    {
        count2 = 0x10;
    }
    step = D_80097EFA[count2];
    ang  = (ang + 0x800) & 0xFFF;
    for (i = 0; i < count2; i++, ang += step)
    {
        wp = func_80031618();
        if (wp != 0)
        {
            wp->routine_0 = 0x19;
            wp->flag_3    = 1;
            wp->field_2   = 0x87;
            rand();
            wp->u_44.ptr           = D_8009A710;
            wp->field_9            = 0;
            *(BYTES8 *)&wp->pos_38 = *pos;
            rnd                    = rand();
            idx                    = D_8008A5A8[kind2][rnd & 0xF];
            if (idx >= 5)
            {
                func_80031988(wp);
            }
            else
            {
                wp->field_A       = idx;
                wp->pos_38.pad    = D_80097EE0[idx];
                wp->field_C.hw[0] = rnd & 0xFFF;
                wp->field_C.hw[1] = (uint32)rnd >> 4;
                wp->field_2C      = (uint32)(rcos(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
                wp->field_2E      = D_80097F24[idx] + (rnd & 3);
                wp->field_30      = (uint32)(rsin(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
                wp->field_32      = 0;
                wp->field_36      = 0;
                wp->field_34      = 5;
                wp->field_40      = 0x02202020;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80046B34);
#endif

// Table reads (D_8008A378 + row * 0x80 + index) match with plain 2D indexing. The destination
// does not: the target keeps &D_8009A6C0 in a register and steps it by 0x14 for column 0 of each
// row, but reaches columns 1-4 with a fresh lui each (separate symbols), and its loads and
// stores stay strictly alternating. 2D indexing of D_8009A6C0 gives a lui per store instead.
#ifdef NON_MATCHING
void func_80046F38(void)
{
    uint32 t;
    uint32 i;
    uint32 j;
    uint32 r;

    t             = System_timer;
    D_800986D0[0] = t;
    for (r = 0; r < 4; r++)
    {
        for (j = 0; j < 5; j++)
        {
            D_8009A6C0[r][j] = D_8008A378[r][(t + j * 10) & 0x1F];
        }
    }
    for (i = 0; i < 6; i++)
    {
        D_8009A710[i][0] = D_8008A578[i];
        D_8009A710[i][1] = D_8008A578[i];
        D_8009A710[i][2] = D_8008A578[i];
        D_8009A710[i][3] = D_8008A578[i];
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80046F38);
#endif

void func_80047148(WORK_48 *wp, BYTES8 *pos)
{
    switch (func_8002FE74(wp->kind_1))
    {
        case 0x40:
            func_80046B34(pos, D_8009884C[wp->field_2][0].spec);
            break;
        case 0x20:
            func_80046B34(pos, D_80098844[wp->field_2][0].spec);
            break;
        case 0x60:
            func_80046B34(pos, D_80098928[wp->field_2][0].spec);
            break;
        case 0xE0:
            func_80046B34(pos, D_8009892C[wp->field_2][0].spec);
            break;
    }
}

// Only the final add differs: the target emits `addu v1,v1,v0` (entry pointer first, then n << 4),
// ours `addu v0,v0,v1`. Tried: 2D array, n[tbl], SPEC_ENT index, byte-offset cast, local pointer
// with shared call, signed/unsigned n.
#ifdef NON_MATCHING
void func_80047228(WORK_48 *wp, BYTES8 *pos, sint32 n)
{
    SPEC_ENT *e;

    switch (func_8002FE74(wp->kind_1))
    {
        case 0x40:
            e = D_8009884C[wp->field_2];
            break;
        case 0x20:
            e = D_80098844[wp->field_2];
            break;
        case 0x60:
            e = D_80098928[wp->field_2];
            break;
        case 0xE0:
            e = D_8009892C[wp->field_2];
            break;
        default:
            return;
    }
    func_80046B34(pos, e[n].spec);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80047228);
#endif

void func_80047318(WORK_48 *wp)
{
    D_8008A708[wp->routine_8](wp);
}

// Called only from this file, ahead of their definitions.
void func_80047C84(WORK_48 *wp);
void func_80047CD8(WORK_48 *wp);

// Close: everything matches except the tail's branch layout. The target tests flag_3 & 0x80 with
// `beqz` (the `sub = 0` store sits before a jump to the shared Model_work_init call) and keeps the
// three `sub = 4/5/6` arms as separate `j; sw v1` stubs; ours inverts the 0x80 test and merges them.
#ifdef NON_MATCHING
void func_80047354(WORK_48 *wp)
{
    sint32 sub;
    WORK_48 *e;
    WORK_48 *e2;
    SVECTOR *pos;
    sint16 *p;

    if (wp->flag_3 == 0xFF)
    {
        wp->routine_0             = 3;
        wp->field_18              = 0x2C808080;
        *(uint32 *)&wp->pos_1C[0] = *(sint32 *)&wp->pos_38;
        wp->pos_1C[2]             = wp->pos_38.vz;
        wp->routine_8             = 3;
        func_80047C84(wp);
        func_80045CE8((BYTES8 *)&wp->pos_38, 3, 0x40404040, 1);
        return;
    }
    if (wp->flag_3 == 0xFE)
    {
        wp->field_C.rec.b0 = 0;
        wp->flag_3         = 0xC2;
    }
    else
    {
        wp->field_C.rec.b0 = 1;
    }
    wp->routine_0 |= 2;
    p = wp->u_44.hw;
    switch (wp->flag_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            p[0]         = 0x37;
            p[1]         = -5;
            wp->field_40 = 0x02808080;
            break;
        case 1:
            p[0]         = 0x37;
            p[1]         = -5;
            wp->field_40 = 0x02808080;
            break;
        case 2:
            p[0]         = 0x46;
            p[1]         = -5;
            wp->field_40 = 0x02808080;
            break;
        case 4:
            p[0]         = 0x8C;
            p[1]         = -5;
            wp->field_40 = 0x02808080;
            break;
        case 5:
            p[0]         = 0xAE;
            p[1]         = -6;
            wp->field_40 = 0x02808080;
            break;
        case 6:
            p[0]         = 0x118;
            p[1]         = 0;
            wp->field_40 = 0x02808080;
            break;
    }
    wp->field_A    = 0;
    wp->pos_38.pad = 0;
    // Matrix at 0x18: identity words, then the three diagonal halfwords cleared
    ((uint32 *)wp)[6]    = 0x1000;
    ((uint32 *)wp)[7]    = 0;
    ((uint32 *)wp)[8]    = 0x1000;
    ((uint32 *)wp)[9]    = 0;
    ((uint32 *)wp)[10]   = 0x1000;
    ((uint32 *)wp)[11]   = 0;
    ((uint32 *)wp)[12]   = 0;
    ((uint32 *)wp)[13]   = 0;
    ((uint16 *)wp)[0x14] = 0;
    ((uint16 *)wp)[0x10] = 0;
    ((uint16 *)wp)[0xC]  = 0;
    if (wp->flag_3 & 0x80)
    {
        sub = 0;
        goto init;
    }
    if (wp->flag_3 & 0x20)
    {
        sub = 2;
        Model_work_init((ATTACH_WORK *)wp, (uint8 *)&sub);
        func_800398E0(0x1E);
        e = func_80031618();
        if (e != NULL)
        {
            e->routine_0          = 5;
            e->field_2            = 0x80;
            e->flag_3             = 5;
            *(BYTES8 *)&e->pos_38 = *(BYTES8 *)&wp->pos_38;
        }
        e2 = func_80031618();
        if (e2 != NULL)
        {
            e2->routine_0          = 5;
            e2->field_2            = 0x80;
            e2->flag_3             = 6;
            *(BYTES8 *)&e2->pos_38 = *(BYTES8 *)&wp->pos_38;
        }
    }
    else
    {
        switch (wp->flag_3 & 0xF)
        {
            case 4:
                sub = 4;
                break;
            case 5:
                sub = 5;
                break;
            case 6:
                sub = 6;
                break;
            default:
                if (func_8004920C(&wp->pos_38) - wp->pos_38.vy < 0x1E)
                {
                    sub = 0;
                }
                else
                {
                    sub = 1;
                }
                break;
        }
    init:
        Model_work_init((ATTACH_WORK *)wp, (uint8 *)&sub);
    }
    pos         = &wp->pos_38;
    wp->timer_B = 0;
    wp->routine_8++;
    sub = svec_distance(pos, &Player_work[0].pos);
    if (wp->field_C.rec.b0 != 0)
    {
        Sound_call2(0xA1, (sint32 *)pos);
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80047354);
#endif

void func_800476A4(WORK_48 *wp)
{
    D_8008A718[wp->field_9](wp);
    if (wp->flag_3 & 0x40)
    {
        func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xA000, wp->kind_1, &D_800986D8, 0x10000008, 0, 0x80);
    }
    else if (wp->flag_3 == 6)
    {
        func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xC000, wp->kind_1, &D_800986D8, 0x30000000, 0, 0x80);
    }
    else
    {
        func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xC000, wp->kind_1, &D_800986D8, 0x10000008, 0, 0x80);
    }
}

// Close (prologue, sums and switch table match): the target keeps all five colour tails separate, each ending
// in a jump to one shared `or; sw`, and uses a2 for the channel in every case; GCC cross-jumps
// the identical colour computations into one block, and moves of the channel between registers
// follow. Separate locals per case made it worse.
#ifdef NON_MATCHING
void func_800477A0(WORK_48 *wp)
{
    sint16 *p;
    MATRIX *m;
    sint32 g;

    p = wp->u_44.hw;
    switch (wp->flag_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            p[0] += p[1];
            wp->pos_38.pad += p[0];
            g = 0x80;
            if ((sint16)p[0] <= 0)
            {
                if (wp->pos_38.pad < 0x64)
                {
                    wp->pos_38.pad = 0;
                    wp->routine_8++;
                }
                p[1] = 0;
                p[0] = -0xA;
                g    = wp->pos_38.pad - 0x64;
                if (wp->pos_38.pad >= 0x100)
                {
                    g = 0x80;
                }
            }
            wp->field_40 = g | (g << 8) | 0x02000000 | (g << 16);
            break;
        case 1:
            p[0] += p[1];
            wp->pos_38.pad += p[0];
            if (wp->pos_38.pad < 0)
            {
                wp->pos_38.pad = 0;
                wp->routine_8++;
            }
            g = 0x80;
            if ((sint16)p[0] <= 0)
            {
                if (wp->pos_38.pad < 0x100)
                {
                    g = wp->pos_38.pad >> 1;
                }
            }
            wp->field_40 = g | (g << 8) | 0x02000000 | (g << 16);
            break;
        case 2:
            p[0] += p[1];
            wp->pos_38.pad += p[0];
            if ((sint16)p[0] <= 0)
            {
                wp->pos_38.pad = 0;
                wp->routine_8++;
            }
            g = 0x80;
            if (wp->pos_38.pad >= 0x10F)
            {
                wp->field_A += 0xE;
                if (wp->field_A < 0x81)
                {
                    g = 0x80 - wp->field_A;
                }
                else
                {
                    g = 0;
                }
            }
            wp->field_40 = g | (g << 8) | 0x02000000 | (g << 16);
            break;
        case 4:
            p[0] += p[1];
            wp->pos_38.pad += p[0];
            g = 0x80;
            if ((sint16)p[0] <= 0)
            {
                if (wp->pos_38.pad < 0x64)
                {
                    wp->pos_38.pad = 0;
                    wp->routine_8++;
                }
                p[1] = 0;
                p[0] = -0x14;
                g    = wp->pos_38.pad >> 3;
                if (wp->pos_38.pad >= 0x401)
                {
                    g = 0x80;
                }
            }
            wp->field_40 = g | (g << 8) | 0x02000000 | (g << 16);
            break;
        case 5:
            p[0] += p[1];
            wp->pos_38.pad += p[0];
            if ((sint16)p[0] < 0x82)
            {
                wp->field_A++;
            }
            if (wp->field_A >= 8)
            {
                wp->field_A = 8;
                wp->routine_8++;
            }
            g            = 8 - wp->field_A;
            wp->field_40 = (g << 4) | (g << 12) | 0x02000000 | (g << 20);
            break;
        case 6:
            p[0] += p[1];
            wp->pos_38.pad += p[0];
            g = 0x80;
            if (wp->pos_38.pad >= 0x801)
            {
                wp->field_A += 0xA;
                if (wp->field_A < 0x81)
                {
                    g = 0x80 - wp->field_A;
                }
                else
                {
                    g = 0;
                }
            }
            wp->field_40 = g | (g << 8) | 0x02000000 | (g << 16);
            if (g == 0)
            {
                wp->pos_38.pad = 0;
                wp->routine_8++;
            }
            break;
    }
    m                      = (MATRIX *)&wp->field_18;
    *(sint32 *)&m->m[0][0] = 0x1000;
    *(sint32 *)&m->m[1][1] = 0x1000;
    *(sint32 *)&m->m[2][2] = 0x1000;
    *(sint32 *)&m->m[0][2] = 0;
    *(sint32 *)&m->m[2][0] = 0;
    m->t[0]                = 0;
    m->t[1]                = 0;
    m->t[2]                = 0;
    wp->timer_B++;
    m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
    RotMatrixY(wp->timer_B << 7, m);
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_800477A0);
#endif

void func_80047BC8(void)
{
}

void func_80047BD0(void)
{
}

void func_80047BD8(WORK_48 *wp)
{
    func_80031988(wp);
}

sint32 svec_distance(SVECTOR *a, SVECTOR *b)
{
    sint32 dx;
    sint32 dy;
    sint32 dz;

    dx = a->vx - b->vx;
    dy = a->vy - b->vy;
    dz = a->vz - b->vz;
    return SquareRoot0(dx * dx + dy * dy + dz * dz);
}

void func_80047C64(WORK_48 *wp)
{
    func_80047CD8(wp);
}

// Target does the field_14 word copy third, in source order; GCC delays the lw/sw to the end
// (v1), whatever the statement order.
#ifdef NON_MATCHING
void func_80047C84(WORK_48 *wp)
{
    wp->field_9  = 0;
    wp->field_A  = D_8008A6CD[0];
    wp->field_14 = D_8008A6C8[0];
    wp->field_22 = D_8008A6CE[0];
    wp->field_23 = D_8008A6CF[0];
    wp->field_24 = D_8008A6CC[0];
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80047C84);
#endif

void func_80047CD8(WORK_48 *wp)
{
    uint32 i;

    wp->field_A--;
    if (wp->field_A == 0)
    {
        wp->field_9++;
        i           = wp->field_9;
        wp->field_A = D_8008A6CD[i * 8];
        if (wp->field_A == 0)
        {
            func_80031988(wp);
        }
        else
        {
            wp->field_14 = D_8008A6C8[i * 2];
            wp->field_22 = D_8008A6CE[i * 8];
            wp->field_23 = D_8008A6CF[i * 8];
            wp->field_24 = D_8008A6CC[i * 8];
        }
    }
}

void func_80047D9C(WORK_48 *wp)
{
    D_8008A724[wp->routine_8](wp);
}

// Close: GCC folds `- 0x100 + (rand() & 0xFF)` into `ori 0xff00` where the target does
// `addiu -0x100` then `addu`; and `addu s0` has its operands swapped.
#ifdef NON_MATCHING
void func_80047DD8(WORK_48 *wp)
{
    uint8 i;
    sint16 *base; // 8 angles at 0x28, 8 indexes at 0x38
    sint16 *p;
    PL_WORK *pl;
    uint8 busy;

    busy = func_800482A8(wp);
    pl   = Player_work;
    if (!busy)
    {
        wp->routine_6 |= 0x20;
        base = (sint16 *)&wp->pad_26[2];
        for (i = 0; i < 8; i++)
        {
            p    = &base[i];
            p[8] = i;
            if (wp->flag_3)
            {
                p[0] = ((uint16)pl->unk56 + 0x80 + (rand() & 0xFF)) & 0xFFF;
            }
            else
            {
                p[0] = ((uint16)pl->unk56 - 0x100U + (rand() & 0xFF)) & 0xFFF;
            }
        }
        Sound_call(0x8D, 0, 0);
        wp->routine_8 = 1;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80047DD8);
#endif

// Structure matches. Remaining differences: the else-branch angle is `li a0,0xff00; addu` where the
// target has `addiu -0x100`; the y coordinate (`y - (sin - 0x10)`) is folded into `y + 0x10 - sin`
// where the target keeps the `- 0x10` on the sine term; the primitive pointer is copied to a2 in
// the target (a0 here); and `addu s0` has its operands swapped.
#ifdef NON_MATCHING
void func_80047EC8(WORK_48 *wp)
{
    uint8 i;
    uint8 j;
    uint8 busy;
    uint8 flip;
    uint16 r;
    uint16 step;
    uint16 h;
    uint32 s;
    sint32 t;
    sint16 *base; // 8 angles at 0x28, 8 counts at 0x38
    sint16 *p;
    uint32 *prim;
    SVECTOR v0;
    SVECTOR v1;

    busy = func_800482A8(wp);
    base = (sint16 *)&wp->pad_26[2];
    if (!busy)
    {
        if (wp->flag_3)
        {
            wp->pos_1C[0] = Player_work[0].unk400[0];
            wp->pos_1C[1] = Player_work[0].unk400[1];
            wp->pos_1C[2] = Player_work[0].unk400[2];
        }
        else
        {
            wp->pos_1C[0] = Player_work[0].unk418[0];
            wp->pos_1C[1] = Player_work[0].unk418[1];
            wp->pos_1C[2] = Player_work[0].unk418[2];
        }
        for (i = 0; i < 8; i++)
        {
            flip = 0;
            r    = 5;
            s    = 0;
            step = (rand() & 7) | 0x10;
            h    = (rand() & 0x3F) + 0x28;
            p    = &base[i];
            p[8]++;
            if (p[8] >= 8)
            {
                p[8] = 0;
            }
            if (wp->flag_3)
            {
                p[0] = ((uint16)Player_work[0].unk56 + 0x80 + (rand() & 0xFF)) & 0xFFF;
            }
            else
            {
                p[0] = (((sint32)(uint16)Player_work[0].unk56 - 0x100) + (rand() & 0xFF)) & 0xFFF;
            }
            for (j = 0; j < base[8 + i] * 2; j++)
            {
                v0.vx = wp->pos_1C[0] + ((rsin((uint16)base[i]) * r) >> 12);
                v0.vz = wp->pos_1C[2] + ((rcos((uint16)base[i]) * r) >> 12);
                t     = (rsin(s) * h) >> 12;
                v0.vy = wp->pos_1C[1] - (t - 0x10);
                r += step;
                s     = (j + 1) << 6;
                v1.vx = wp->pos_1C[0] + ((rsin((uint16)base[i]) * r) >> 12);
                v1.vz = wp->pos_1C[2] + ((rcos((uint16)base[i]) * r) >> 12);
                t     = (rsin(s) * h) >> 12;
                v1.vy = wp->pos_1C[1] - (t - 0x10);
                if (rand() & 1)
                {
                    prim    = func_8002D4B8();
                    prim[1] = 0x52104080;
                    prim[0] = (v0.vy << 16) + v0.vx;
                    prim[2] = (v1.vy << 16) + v1.vx;
                    if (flip)
                    {
                        prim[3] = 0x104080;
                    }
                    else
                    {
                        prim[3] = 0x10101;
                    }
                    prim[6] = 0xE1000020;
                    flip    = 1;
                    prim[4] = (v0.vz << 16) + v1.vz;
                }
                else
                {
                    flip = 0;
                }
            }
        }
        Sound_call(0x8D, 0, 0);
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_80047EC8);
#endif

void func_80048268(WORK_48 *wp)
{
    Sound_call(0x8F, 0, 0);
    wp->routine_0 = 0;
    func_80031988(wp);
}

// GCC turns the final `hit != 0` into `sltu` and lays out the fail block before the shared tail;
// the target branches on the AND result (`beqz`/`li 1`/`move 0`) and has no `sltu`.
#ifdef NON_MATCHING
sint32 func_800482A8(WORK_48 *wp)
{
    uint32 hit;

    if (Player_work[0].unk09 == 3)
    {
        if (wp->flag_3 != 0)
        {
            if (!(Player_work[0].unk11C & Player_work[0].unk12A))
            {
                goto fail;
            }
            hit = Player_work[0].unk128 & Player_work[0].unk11C;
        }
        else
        {
            if (!(Player_work[0].unk11C & Player_work[0].unk128))
            {
                goto fail;
            }
            hit = Player_work[0].unk12A & Player_work[0].unk11C;
        }
        if (hit == 0)
        {
            return 0;
        }
        return 1;
    }
fail:
    wp->routine_8 = 2;
    return 1;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800456D8", func_800482A8);
#endif

void func_80048354(WORK_48 *wp)
{
    D_8008A76C[wp->routine_8](wp);
}

void func_80048390(WORK_48 *wp)
{
    wp->field_24        = 0x20;
    wp->field_C.rec.b0  = 0x80;
    wp->field_14        = 0x3D48002C;
    wp->field_18        = 0x2EC06060;
    wp->field_C.rec.idx = 0;
    wp->routine_0 |= 0x22;
    if (wp->flag_3 != 0)
    {
        wp->field_C.rec.timer = D_8008A748[0].time_4;
        wp->field_22          = D_8008A748[wp->field_C.rec.idx].val_0;
        wp->field_23          = D_8008A748[wp->field_C.rec.idx].val_2;
    }
    else
    {
        wp->field_C.rec.timer = D_8008A730[0].time_4;
        wp->field_22          = D_8008A730[wp->field_C.rec.idx].val_0;
        wp->field_23          = D_8008A730[wp->field_C.rec.idx].val_2;
    }
    wp->routine_8 = 1;
    wp->timer_B   = 0;
}

void func_80048484(WORK_48 *wp)
{
    wp->field_C.rec.timer--;
    if ((sint8)wp->field_C.rec.timer == 0) // the cast is needed to match (sll/sra test)
    {
        if (wp->flag_3 != 0)
        {
            wp->field_24 += 8;
            wp->field_C.rec.idx++;
            wp->field_C.rec.timer = D_8008A748[wp->field_C.rec.idx].time_4;
            wp->field_22          = D_8008A748[wp->field_C.rec.idx].val_0;
            wp->field_23          = D_8008A748[wp->field_C.rec.idx].val_2;
        }
        else
        {
            wp->field_C.rec.idx++;
            wp->field_C.rec.timer = D_8008A730[wp->field_C.rec.idx].time_4;
            wp->field_22          = D_8008A730[wp->field_C.rec.idx].val_0;
            wp->field_23          = D_8008A730[wp->field_C.rec.idx].val_2;
        }
    }
    if (wp->field_C.rec.timer == 0x80)
    {
        wp->routine_8 = 2;
    }
}

void func_800485C4(WORK_48 *wp)
{
    func_80031988(wp);
}

void func_800485E4(WORK_48 *wp)
{
    D_8008A778[wp->flag_4](wp);
}
