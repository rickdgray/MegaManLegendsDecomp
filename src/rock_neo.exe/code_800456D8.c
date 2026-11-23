#include "common.h"
#include "psyq/rand.h"
#include "code_800456D8.h"
#include "code_80043F34.h"
#include "code_80048620.h"
#include "code_80027678.h"
#include "code_80037FB4.h"
#include "code_8004324C.h"
#include "scratch.h"
#include "game.h"
#include "sound.h"
#include "player.h"

// Small uninitialized statics (.sbss 0x800986D0-0x800986D8).
// Two scalars: func_80046F38's store to D_800986D0 is scheduled past a store through a pointer,
// which GCC allows for a scalar but not for an array element. D_800986D4 is never read here.
static sint32 D_800986D0; // System_timer when func_80046F38 last sampled its tables
static sint32 D_800986D4;

// Called only from this file, ahead of their definitions.
void func_80046F38(void);
void func_80045CE8(SVECTOR *pos, uint32 num, uint32 weights, uint32 kind);
void func_80046B34(SVECTOR *pos, uint32 spec);
uint8 func_800482A8(W48_89_WORK *wp);
sint32 svec_distance(SVECTOR *a, SVECTOR *b);
void func_80045AB4(W48_86_WORK *wp);
void func_80045BC8(W48_86_WORK *wp);
void func_80046890(W48_87_WORK *wp);
void func_800469A4(W48_87_WORK *wp);
void func_80046A0C(W48_87_WORK *wp);
void func_80047C84(W48_88_WORK *wp);
void func_80047CD8(W48_88_WORK *wp);

void func_800456D8(W48_86_WORK *wp)
{
    if (rand() & 1)
    {
        wp->routine_0 |= 2;
    }
    Model_work_init((MODEL_WORK *)wp, &wp->type_3);
    wp->routine_8++;
    Sound_call2(0x9B, &wp->pos_38);
    func_80045AB4(wp);
    func_80045BC8(wp);
}

void func_80045750(W48_86_WORK *wp)
{
    SVECTOR pos;
    SVECTOR old;
    MATRIX *m;
    sint32 hit;

    old = wp->pos_38;
    wp->vx_2C += wp->ax_32;
    wp->pos_38.vx += wp->vx_2C;
    wp->vy_2E += wp->ay_34;
    wp->pos_38.vy += wp->vy_2E;
    wp->vz_30 += wp->az_36;
    wp->pos_38.vz += wp->vz_30;
    pos = wp->pos_38;
    func_80045AB4(wp);
    hit = Pos_map_push_out(&pos, &old, 1, &D_8008A310[wp->field_A]);
    if (hit != 0)
    {
        wp->pos_38.vx = pos.vx;
        wp->pos_38.vy = pos.vy;
        wp->pos_38.vz = pos.vz;
        if (hit & 0x1000)
        {
            wp->pos_38.pad = wp->pos_38.pad >> 1;
            if ((sint16)wp->vy_2E >> 1 < 2)
            {
                m           = (MATRIX *)wp->m;
                wp->timer_B = 1;
                wp->vy_2E   = 0;
                m->m[2][1]  = 0;
                m->m[2][0]  = 0;
                m->m[1][2]  = 0;
                m->m[1][0]  = 0;
                m->m[0][2]  = 0;
                m->m[0][1]  = 0;
                wp->routine_8++;
                m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
                RotMatrixY(wp->ang_y_C, m);
            }
            wp->vy_2E = (sint16)wp->vy_2E >> 1;
        }
        Wall_reflect_spd(&wp->vx_2C, hit);
    }
    func_80045BC8(wp);
}

void func_80045918(W48_86_WORK *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_8 += 2;
    }
}

void func_8004594C(W48_86_WORK *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
    }
}

void func_80045980(W48_86_WORK *wp)
{
    func_80031988((WORK_48 *)wp);
}

void func_800459A0(W48_86_WORK *wp)
{
    wp->vy_2E = -0x28;
    wp->ay_34 = 5;
    wp->routine_8++;
}

void func_800459C0(W48_86_WORK *wp)
{
    MATRIX *m;

    m          = (MATRIX *)wp->m;
    m->m[2][1] = 0;
    m->m[2][0] = 0;
    m->m[1][2] = 0;
    m->m[1][0] = 0;
    m->m[0][2] = 0;
    m->m[0][1] = 0;
    m->m[0][0] = m->m[2][2] = wp->pos_38.pad >> 1;
    m->m[1][1]              = wp->pos_38.pad;
    RotMatrixY(0x180, m);
    wp->vy_2E += wp->ay_34;
    wp->pos_38.vy += wp->vy_2E;
    wp->pos_38.pad -= D_80097E64[wp->field_A] >> 3;
    if (wp->vy_2E >= 0)
    {
        wp->routine_8++;
    }
}

void func_80045A7C(W48_86_WORK *wp)
{
    Sound_call2(0xCF, &wp->pos_38);
    func_80031988((WORK_48 *)wp);
}

void func_80045AB4(W48_86_WORK *wp)
{
    SVECTOR rot;
    MATRIX m;
    VECTOR scale;
    sint32 r;

    m = *(MATRIX *)wp->m;
    r = rand();
    wp->ang_x_E += 0x80 + (r & 0x7F);
    rot.vx = wp->ang_x_E;
    wp->ang_y_C += 0x40 + (r & 0x3F);
    rot.vy = wp->ang_y_C;
    rot.vz = 0;
    RotMatrix(&rot, &m);
    scale.vx = scale.vy = scale.vz = wp->pos_38.pad;
    ScaleMatrix(&m, &scale);
    *(MATRIX *)wp->m = m;
}

void func_80045BC8(W48_86_WORK *wp)
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
// The clamp copies the parameter into count in its else arm; that puts count's entry copy after
// weights' and kind's, as in the target's prologue.
void func_80045CE8(SVECTOR *pos, uint32 num, uint32 weights, uint32 kind)
{
    W48_86_WORK *wp;
    uint32 i;
    uint32 ang;
    uint32 step;
    uint32 r;
    uint32 acc;
    uint8 idx;
    uint32 pick;
    uint32 count;

    if (num > 0x10)
    {
        count = 0x10;
    }
    else
    {
        count = num;
    }
    if (kind > 5)
    {
        kind = 5;
    }
    step = D_80097E7A[count];
    ang  = rand() & 0xFFF;
    for (i = 0; i < count; i++, ang += step)
    {
        wp = (W48_86_WORK *)func_80031618();
        if (wp == NULL)
        {
            continue;
        }
        wp->routine_0 = 5;
        wp->type_3    = 0;
        wp->id_2      = 0x86;
        pick          = rand() & 0xFF;
        acc           = weights >> 24;
        if (pick < acc)
        {
            wp->ptr_44  = D_8009A5A0;
            wp->field_9 = 0;
        }
        else if (pick < (acc += (weights >> 16) & 0xFF))
        {
            wp->ptr_44  = D_8009A5D0;
            wp->field_9 = 1;
        }
        else if (pick < (acc += (weights >> 8) & 0xFF))
        {
            wp->ptr_44  = D_8009A600;
            wp->field_9 = 2;
        }
        else if (pick < (acc += weights & 0xFF))
        {
            wp->ptr_44  = D_8009A630;
            wp->field_9 = 3;
        }
        else
        {
            wp->type_3  = 1;
            wp->ptr_44  = D_8009A660;
            wp->field_9 = 4;
        }
        wp->pos_38     = *pos;
        r              = rand();
        idx            = D_8008A2B0[kind][r & 0xF];
        wp->field_A    = idx;
        wp->pos_38.pad = D_80097E64[idx];
        wp->ang_y_C    = r & 0xFFF;
        wp->ang_x_E    = r >> 4;
        wp->vx_2C      = (rcos(ang) * (D_80097E9C[idx] + (r & 3))) >> 12;
        wp->vy_2E      = D_80097EA8[idx] + (r & 3);
        wp->vz_30      = (rsin(ang) * (D_80097E9C[idx] + (r & 3))) >> 12;
        wp->ax_32      = 0;
        wp->az_36      = 0;
        wp->ay_34      = 5;
        switch (rand() & 3)
        {
            case 0:
                wp->rgbc_40 = 0x606060;
                break;
            case 1:
                wp->rgbc_40 = 0x8080;
                break;
            case 2:
                wp->rgbc_40 = 0x20;
                break;
            case 3:
                wp->rgbc_40 = 0x200000;
                break;
        }
    }
}

// The table entry is selected and never used; only the switch's copy of the result (move v1,v0)
// survives.
void func_80045FE4(WORK_48 *wp)
{
    SPEC_ENT *ent;

    switch (func_8002FE74(wp->kind_1))
    {
        case 0x40:
            ent = D_8009884C[wp->id_2];
            break;
        case 0x20:
            ent = D_80098844[wp->id_2];
            break;
        case 0x60:
            ent = D_80098928[wp->id_2];
            break;
        case 0xE0:
            ent = D_8009892C[wp->id_2];
            break;
    }
}

// Same code as func_80045FE4.
void func_80046008(WORK_48 *wp)
{
    SPEC_ENT *ent;

    switch (func_8002FE74(wp->kind_1))
    {
        case 0x40:
            ent = D_8009884C[wp->id_2];
            break;
        case 0x20:
            ent = D_80098844[wp->id_2];
            break;
        case 0x60:
            ent = D_80098928[wp->id_2];
            break;
        case 0xE0:
            ent = D_8009892C[wp->id_2];
            break;
    }
}

void func_8004602C(W48_87_WORK *wp)
{
    uint32 *p;
    uint32 a;
    uint32 b;
    uint32 c;
    uint32 d;

    if (D_800986D0 != System_timer)
    {
        func_80046F38();
    }
    D_8008A6A8[wp->routine_8](wp);
    if (wp->type_3 != 0 && (wp->routine_0 & 2) && wp->routine_8 < 5)
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
        p    = Billboard_get();
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

void func_800461A4(W48_87_WORK *wp)
{
    wp->routine_0 |= 2;
    Model_work_init((MODEL_WORK *)wp, &wp->type_3);
    wp->routine_8++;
    Sound_call2(0x9B, &wp->pos_38);
    if (wp->type_3 != 0)
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

void func_8004622C(W48_87_WORK *wp)
{
    SVECTOR pos;
    SVECTOR old;
    MATRIX *m;
    sint32 hit;

    old = wp->pos_38;
    wp->vx_2C += wp->ax_32;
    wp->pos_38.vx += wp->vx_2C;
    wp->vy_2E += wp->ay_34;
    wp->pos_38.vy += wp->vy_2E;
    wp->vz_30 += wp->az_36;
    wp->pos_38.vz += wp->vz_30;
    pos = wp->pos_38;
    if (wp->type_3 != 0)
    {
        func_80046890(wp);
    }
    else
    {
        func_800469A4(wp);
    }
    hit = Pos_map_push_out(&pos, &old, 1, &D_8008A618[wp->type_3][wp->field_A]);
    if (hit != 0)
    {
        wp->pos_38.vx = pos.vx;
        wp->pos_38.vy = pos.vy;
        wp->pos_38.vz = pos.vz;
        if ((hit & 0x1000) || --wp->timer_B == 0)
        {
            if ((sint16)wp->vy_2E >> 1 < 2)
            {
                m           = (MATRIX *)wp->m;
                wp->timer_B = 0x96;
                wp->vy_2E   = 0;
                m->m[2][1]  = 0;
                m->m[2][0]  = 0;
                m->m[1][2]  = 0;
                m->m[1][0]  = 0;
                m->m[0][2]  = 0;
                m->m[0][1]  = 0;
                wp->routine_8++;
                m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
                RotMatrixY(wp->ang_y_C, m);
            }
            wp->vy_2E = (sint16)wp->vy_2E >> 1;
        }
        Wall_reflect_spd(&wp->vx_2C, hit);
    }
    func_80046A0C(wp);
}

// The limit gets its own variable (it then takes ground's register), computed before the
// position copy.
void func_80046438(W48_87_WORK *wp)
{
    SVECTOR old;
    sint32 ground;
    sint32 h;
    sint32 limit;

    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
        wp->timer_B = (rand() & 7) + 0x1E;
    }
    ground = func_80048EA4(&wp->pos_38, &D_8008A618[wp->type_3][wp->field_A], wp->vy_2E, 0xFFFF);
    h      = D_8008A618[wp->type_3][wp->field_A].max_A + 1;
    limit  = ground - h;
    old    = wp->pos_38;
    if (limit > wp->pos_38.vy)
    {
        wp->vy_2E += wp->ay_34;
        wp->pos_38.vy += wp->vy_2E;
    }
    Pos_map_push_out(&wp->pos_38, &old, 1, &D_8008A618[wp->type_3][wp->field_A]);
    func_80046A0C(wp);
    if (wp->type_3 == 0)
    {
        func_800469A4(wp);
    }
}

// Same limit form as func_80046438.
void func_800465C8(W48_87_WORK *wp)
{
    SVECTOR old;
    sint32 ground;
    sint32 h;
    sint32 limit;

    wp->routine_0 ^= 2;
    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
    }
    ground = func_80048EA4(&wp->pos_38, &D_8008A618[wp->type_3][wp->field_A], wp->vy_2E, 0xFFFF);
    h      = D_8008A618[wp->type_3][wp->field_A].max_A + 1;
    limit  = ground - h;
    old    = wp->pos_38;
    if (limit > wp->pos_38.vy)
    {
        wp->vy_2E += wp->ay_34;
        wp->pos_38.vy += wp->vy_2E;
    }
    Pos_map_push_out(&wp->pos_38, &old, 1, &D_8008A618[wp->type_3][wp->field_A]);
    func_80046A0C(wp);
    if (wp->type_3 == 0)
    {
        func_800469A4(wp);
    }
}

void func_8004674C(W48_87_WORK *wp)
{
    func_80031988((WORK_48 *)wp);
}

void func_8004676C(W48_87_WORK *wp)
{
    wp->vy_2E = -0x28;
    wp->ay_34 = 5;
    wp->routine_8++;
}

void func_8004678C(W48_87_WORK *wp)
{
    MATRIX *m;

    m          = (MATRIX *)wp->m;
    m->m[2][1] = 0;
    m->m[2][0] = 0;
    m->m[1][2] = 0;
    m->m[1][0] = 0;
    m->m[0][2] = 0;
    m->m[0][1] = 0;
    m->m[0][0] = m->m[2][2] = wp->pos_38.pad >> 1;
    m->m[1][1]              = wp->pos_38.pad;
    RotMatrixY(0x180, m);
    wp->vy_2E += wp->ay_34;
    wp->pos_38.vy += wp->vy_2E;
    wp->pos_38.pad -= D_80097EE0[wp->field_A] >> 3;
    if (wp->vy_2E >= 0)
    {
        wp->routine_8++;
    }
}

void func_80046848(W48_87_WORK *wp)
{
    uint32 id;

    if (wp->type_3 != 0)
    {
        id = 0x9E;
    }
    else
    {
        id = 0x9D;
    }
    Sound_call2(id, &wp->pos_38);
    func_80031988((WORK_48 *)wp);
}

void func_80046890(W48_87_WORK *wp)
{
    SVECTOR rot;
    MATRIX m;
    VECTOR scale;
    sint32 r;

    m = *(MATRIX *)wp->m;
    r = rand();
    wp->ang_x_E += 0x80 + (r & 0x7F);
    rot.vx = wp->ang_x_E;
    wp->ang_y_C += 0x40 + (r & 0x3F);
    rot.vy = wp->ang_y_C;
    rot.vz = 0;
    RotMatrix(&rot, &m);
    scale.vx = scale.vy = scale.vz = wp->pos_38.pad;
    ScaleMatrix(&m, &scale);
    *(MATRIX *)wp->m = m;
}

void func_800469A4(W48_87_WORK *wp)
{
    MATRIX *m;

    m          = (MATRIX *)wp->m;
    m->m[2][1] = 0;
    m->m[2][0] = 0;
    m->m[1][2] = 0;
    m->m[1][0] = 0;
    m->m[0][2] = 0;
    m->m[0][1] = 0;
    m->m[0][0] = m->m[1][1] = m->m[2][2] = wp->pos_38.pad;
    RotMatrixY(wp->ang_y_C, m);
    wp->ang_y_C += 0x100;
}

void func_80046A0C(W48_87_WORK *wp)
{
    uint32 r;
    uint32 i;

    i = wp->field_A;
    r = D_80097EEC[wp->type_3][i];
    if ((uint32)(Player_work[0].pos.vx - wp->pos_38.vx + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[0].pos.vz - wp->pos_38.vz + r + 0x32) <= r * 2 + 0x64 &&
        (uint32)(Player_work[0].pos.vy - wp->pos_38.vy + r) <= r * 2 + 0x96)
    {
        wp->routine_8 = 5;
        if (wp->type_3 == 0)
        {
            Money_add(D_8008A678[Game_work.unk05B][i], 0, 0);
        }
        else
        {
            func_80043340(D_8008A680[Game_work.unk05B][i], 0);
        }
    }
}

// Two bursts of effects around `pos`; `spec` packs four bytes: count and kind row (D_8008A5A8)
// of the first burst (bits 0-7, 8-15), then of the second (bits 16-23, 24-31).
// The first count's mask is written in the test and again in the assignment: CSE keeps it in v0
// and copies it to s7, as the target does (a plain count = spec & 0xFF folds the andi into s7).
void func_80046B34(SVECTOR *pos, uint32 spec)
{
    uint32 count;
    W48_87_WORK *wp;
    uint32 kind;
    uint32 count2;
    uint32 kind2;
    uint32 i;
    uint32 ang;
    uint32 step;
    uint32 idx;
    uint32 rnd;

    kind   = (spec >> 8) & 0xFF;
    count2 = (spec >> 16) & 0xFF;
    kind2  = spec >> 24;
    if ((spec & 0xFF) > 16)
    {
        count = 16;
    }
    else
    {
        count = spec & 0xFF;
    }
    step = D_80097EFA[count];
    ang  = rand() & 0xFFF;
    for (i = 0; i < count; i++, ang += step)
    {
        wp = (W48_87_WORK *)func_80031618();
        if (wp == NULL)
        {
            continue;
        }
        wp->routine_0 = 0x15;
        wp->type_3    = 0;
        wp->id_2      = 0x87;
        rand();
        wp->field_9 = 0;
        wp->pos_38  = *pos;
        wp->pos_38.vy -= 20;
        rnd = rand();
        idx = D_8008A5A8[kind][rnd & 0xF];
        if (idx >= 5)
        {
            func_80031988((WORK_48 *)wp);
            continue;
        }
        wp->ptr_44     = D_8009A6C0[idx];
        wp->field_A    = idx;
        wp->pos_38.pad = D_80097EE0[idx];
        wp->ang_y_C    = rnd & 0xFFF;
        wp->ang_x_E    = rnd >> 4;
        wp->vx_2C      = (rcos(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
        wp->vy_2E      = D_80097F24[idx] + (rnd & 3);
        wp->vz_30      = (rsin(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
        wp->ay_34      = 5;
        wp->ax_32      = 0;
        wp->az_36      = 0;
        wp->rgbc_40    = 0x02808080;
        wp->m[2][1]    = 0;
        wp->m[2][0]    = 0;
        wp->m[1][2]    = 0;
        wp->m[1][0]    = 0;
        wp->m[0][2]    = 0;
        wp->m[0][1]    = 0;
        wp->m[0][0] = wp->m[1][1] = wp->m[2][2] = wp->pos_38.pad;
    }
    count = count2;
    if (count > 16)
    {
        count = 16;
    }
    step = D_80097EFA[count];
    ang  = (ang + 0x800) & 0xFFF;
    for (i = 0; i < count; i++, ang += step)
    {
        wp = (W48_87_WORK *)func_80031618();
        if (wp == NULL)
        {
            continue;
        }
        wp->routine_0 = 0x19;
        wp->type_3    = 1;
        wp->id_2      = 0x87;
        rand();
        wp->ptr_44  = D_8009A710;
        wp->field_9 = 0;
        wp->pos_38  = *pos;
        rnd         = rand();
        idx         = D_8008A5A8[kind2][rnd & 0xF];
        if (idx >= 5)
        {
            func_80031988((WORK_48 *)wp);
            continue;
        }
        wp->field_A    = idx;
        wp->pos_38.pad = D_80097EE0[idx];
        wp->ang_y_C    = rnd & 0xFFF;
        wp->ang_x_E    = rnd >> 4;
        wp->vx_2C      = (rcos(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
        wp->vy_2E      = D_80097F24[idx] + (rnd & 3);
        wp->vz_30      = (rsin(ang) * (D_80097F1C[idx] + (rnd & 3))) >> 12;
        wp->ax_32      = 0;
        wp->az_36      = 0;
        wp->ay_34      = 5;
        wp->rgbc_40    = 0x02202020;
    }
}

// Samples five columns of each D_8008A378 row, 10 apart from the frame, into D_8009A6C0, and
// spreads each D_8008A578 word over a row of D_8009A710. Written unrolled.
void func_80046F38(void)
{
    uint32 t;
    uint32 i;
    uint32 *dst;

    dst        = D_8009A6C0[0];
    t          = System_timer;
    D_800986D0 = t;
    dst[0]     = D_8008A378[0][t & 0x1F];
    dst[1]     = D_8008A378[0][(t + 10) & 0x1F];
    dst[2]     = D_8008A378[0][(t + 20) & 0x1F];
    dst[3]     = D_8008A378[0][(t + 30) & 0x1F];
    dst[4]     = D_8008A378[0][(t + 40) & 0x1F];
    dst += 5;
    dst[0] = D_8008A378[1][t & 0x1F];
    dst[1] = D_8008A378[1][(t + 10) & 0x1F];
    dst[2] = D_8008A378[1][(t + 20) & 0x1F];
    dst[3] = D_8008A378[1][(t + 30) & 0x1F];
    dst[4] = D_8008A378[1][(t + 40) & 0x1F];
    dst += 5;
    dst[0] = D_8008A378[2][t & 0x1F];
    dst[1] = D_8008A378[2][(t + 10) & 0x1F];
    dst[2] = D_8008A378[2][(t + 20) & 0x1F];
    dst[3] = D_8008A378[2][(t + 30) & 0x1F];
    dst[4] = D_8008A378[2][(t + 40) & 0x1F];
    dst += 5;
    dst[0] = D_8008A378[3][t & 0x1F];
    dst[1] = D_8008A378[3][(t + 10) & 0x1F];
    dst[2] = D_8008A378[3][(t + 20) & 0x1F];
    dst[3] = D_8008A378[3][(t + 30) & 0x1F];
    dst[4] = D_8008A378[3][(t + 40) & 0x1F];
    dst    = D_8009A710[0];
    for (i = 0; i < 6; i++)
    {
        dst[0] = D_8008A578[i];
        dst[1] = D_8008A578[i];
        dst[2] = D_8008A578[i];
        dst[3] = D_8008A578[i];
        dst += 4;
    }
}

void func_80047148(WORK_48 *wp, SVECTOR *pos)
{
    switch (func_8002FE74(wp->kind_1))
    {
        case 0x40:
            func_80046B34(pos, D_8009884C[wp->id_2][0].spec);
            break;
        case 0x20:
            func_80046B34(pos, D_80098844[wp->id_2][0].spec);
            break;
        case 0x60:
            func_80046B34(pos, D_80098928[wp->id_2][0].spec);
            break;
        case 0xE0:
            func_80046B34(pos, D_8009892C[wp->id_2][0].spec);
            break;
    }
}

void func_80047228(WORK_48 *wp, SVECTOR *pos, sint32 n)
{
    SPEC_ENT *e;

    switch (func_8002FE74(wp->kind_1))
    {
        case 0x40:
            e = D_8009884C[wp->id_2] + n;
            break;
        case 0x20:
            e = D_80098844[wp->id_2] + n;
            break;
        case 0x60:
            e = D_80098928[wp->id_2] + n;
            break;
        case 0xE0:
            e = D_8009892C[wp->id_2] + n;
            break;
        default:
            return;
    }
    func_80046B34(pos, e->spec);
}

void func_80047318(W48_88_WORK *wp)
{
    D_8008A708[wp->routine_8](wp);
}

// Every path makes its own Model_work_init call, the default's in each arm of its test.
// Cross-jumping then merges the calls and leaves each path its own argument store (the target's
// separate `j; sw` blocks for the 0x80 path and cases 4, 5 and 6).
void func_80047354(W48_88_WORK *wp)
{
    sint32 sub;
    W48_80_WORK *e;
    sint16 *p;

    if (wp->type_3 == 0xFF)
    {
        wp->routine_0                     = 3;
        wp->efc.sprite.rgbc               = 0x2C808080;
        wp->routine_8                     = 3;
        *(uint32 *)&wp->efc.sprite.pos[0] = *(sint32 *)&wp->efc.model.pos;
        wp->efc.sprite.pos[2]             = wp->efc.model.pos.vz;
        func_80047C84(wp);
        func_80045CE8(&wp->efc.model.pos, 3, 0x40404040, 1);
        return;
    }
    if (wp->type_3 == 0xFE)
    {
        wp->field_C = 0;
        wp->type_3  = 0xC2;
    }
    else
    {
        wp->field_C = 1;
    }
    wp->routine_0 |= 2;
    p = wp->hw_44;
    switch (wp->type_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            p[0]               = 0x37;
            p[1]               = -5;
            wp->efc.model.rgbc = 0x02808080;
            break;
        case 1:
            p[0]               = 0x37;
            p[1]               = -5;
            wp->efc.model.rgbc = 0x02808080;
            break;
        case 2:
            p[0]               = 0x46;
            p[1]               = -5;
            wp->efc.model.rgbc = 0x02808080;
            break;
        case 4:
            p[0]               = 0x8C;
            p[1]               = -5;
            wp->efc.model.rgbc = 0x02808080;
            break;
        case 5:
            p[0]               = 0xAE;
            p[1]               = -6;
            wp->efc.model.rgbc = 0x02808080;
            break;
        case 6:
            p[0]               = 0x118;
            p[1]               = 0;
            wp->efc.model.rgbc = 0x02808080;
            break;
    }
    wp->field_A           = 0;
    wp->efc.model.pos.pad = 0;
    // Identity matrix by words, then the diagonal cleared
    *(uint32 *)&wp->efc.model.mtx.m[0][0] = 0x1000;
    *(uint32 *)&wp->efc.model.mtx.m[0][2] = 0;
    *(uint32 *)&wp->efc.model.mtx.m[1][1] = 0x1000;
    *(uint32 *)&wp->efc.model.mtx.m[2][0] = 0;
    *(uint32 *)&wp->efc.model.mtx.m[2][2] = 0x1000;
    wp->efc.model.mtx.t[0]                = 0;
    wp->efc.model.mtx.t[1]                = 0;
    wp->efc.model.mtx.t[2]                = 0;
    wp->efc.model.mtx.m[2][2]             = 0;
    wp->efc.model.mtx.m[1][1]             = 0;
    wp->efc.model.mtx.m[0][0]             = 0;
    if (wp->type_3 & 0x80)
    {
        sub = 0;
        Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
    }
    else if (wp->type_3 & 0x20)
    {
        sub = 2;
        Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
        func_800398E0(0x1E);
        e = (W48_80_WORK *)func_80031618();
        if (e != NULL)
        {
            e->routine_0 = 5;
            e->id_2      = 0x80;
            e->type_3    = 5;
            e->pos_38    = wp->efc.model.pos;
        }
        e = (W48_80_WORK *)func_80031618();
        if (e != NULL)
        {
            e->routine_0 = 5;
            e->id_2      = 0x80;
            e->type_3    = 6;
            e->pos_38    = wp->efc.model.pos;
        }
    }
    else
    {
        switch (wp->type_3 & 0xF)
        {
            case 4:
                sub = 4;
                Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
                break;
            case 5:
                sub = 5;
                Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
                break;
            case 6:
                sub = 6;
                Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
                break;
            default:
                if (Ceiling_height_get(&wp->efc.model.pos) - wp->efc.model.pos.vy < 0x1E)
                {
                    sub = 0;
                    Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
                }
                else
                {
                    sub = 1;
                    Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
                }
                break;
        }
    }
    wp->routine_8++;
    wp->timer_B = 0;
    sub         = svec_distance(&wp->efc.model.pos, &Player_work[0].pos); // dead store, needed to match
    if (wp->field_C != 0)
    {
        Sound_call2(0xA1, &wp->efc.model.pos);
    }
}

void func_800476A4(W48_88_WORK *wp)
{
    D_8008A718[wp->field_9](wp);
    if (wp->type_3 & 0x40)
    {
        func_800341BC(&wp->efc.model.pos, wp->efc.model.pos.pad / 2, 0, 0xA000, wp->kind_1, &D_800986D8, 0x10000008, 0, 0x80);
    }
    else if (wp->type_3 == 6)
    {
        func_800341BC(&wp->efc.model.pos, wp->efc.model.pos.pad / 2, 0, 0xC000, wp->kind_1, &D_800986D8, 0x30000000, 0, 0x80);
    }
    else
    {
        func_800341BC(&wp->efc.model.pos, wp->efc.model.pos.pad / 2, 0, 0xC000, wp->kind_1, &D_800986D8, 0x10000008, 0, 0x80);
    }
}

void func_800477A0(W48_88_WORK *wp)
{
    sint16 *v;
    sint32 c;

    v = wp->hw_44;
    switch (wp->type_3 & 0xF)
    {
        case 0:
        case 3:
        default:
            v[0] += v[1];
            wp->efc.model.pos.pad += v[0];
            if (v[0] <= 0)
            {
                if (wp->efc.model.pos.pad < 100)
                {
                    wp->routine_8++;
                    wp->efc.model.pos.pad = 0;
                }
                v[1] = 0;
                v[0] = -10;
                if (wp->efc.model.pos.pad >= 0x100)
                {
                    c = 0x80;
                }
                else
                {
                    c = wp->efc.model.pos.pad - 100;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->efc.model.rgbc = c | 0x02000000 | (c << 8) | (c << 16);
            break;
        case 1:
            v[0] += v[1];
            wp->efc.model.pos.pad += v[0];
            if (wp->efc.model.pos.pad < 0)
            {
                wp->routine_8++;
                wp->efc.model.pos.pad = 0;
            }
            c = 0x80;
            if (v[0] <= 0 && wp->efc.model.pos.pad < 0x100)
            {
                c = wp->efc.model.pos.pad >> 1;
            }
            wp->efc.model.rgbc = c | 0x02000000 | (c << 8) | (c << 16);
            break;
        case 2:
            v[0] += v[1];
            wp->efc.model.pos.pad += v[0];
            if (v[0] <= 0)
            {
                wp->routine_8++;
                wp->efc.model.pos.pad = 0;
            }
            if (wp->efc.model.pos.pad >= 0x10F)
            {
                wp->field_A += 14;
                if (wp->field_A <= 0x80)
                {
                    c = 0x80 - wp->field_A;
                }
                else
                {
                    c = 0;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->efc.model.rgbc = c | 0x02000000 | (c << 8) | (c << 16);
            break;
        case 4:
            v[0] += v[1];
            wp->efc.model.pos.pad += v[0];
            if (v[0] <= 0)
            {
                if (wp->efc.model.pos.pad < 100)
                {
                    wp->routine_8++;
                    wp->efc.model.pos.pad = 0;
                }
                v[1] = 0;
                v[0] = -20;
                if (wp->efc.model.pos.pad > 0x400)
                {
                    c = 0x80;
                }
                else
                {
                    c = wp->efc.model.pos.pad >> 3;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->efc.model.rgbc = c | 0x02000000 | (c << 8) | (c << 16);
            break;
        case 5:
            v[0] += v[1];
            wp->efc.model.pos.pad += v[0];
            if (v[0] < 0x82)
            {
                wp->field_A++;
            }
            if (wp->field_A >= 8)
            {
                wp->field_A = 8;
                wp->routine_8++;
            }
            c                  = (8 - wp->field_A) * 16;
            wp->efc.model.rgbc = c | 0x02000000 | (c << 8) | (c << 16);
            break;
        case 6:
            v[0] += v[1];
            wp->efc.model.pos.pad += v[0];
            if (wp->efc.model.pos.pad > 0x800)
            {
                wp->field_A += 10;
                if (wp->field_A <= 0x80)
                {
                    c = 0x80 - wp->field_A;
                }
                else
                {
                    c = 0;
                }
            }
            else
            {
                c = 0x80;
            }
            wp->efc.model.rgbc = c | 0x02000000 | (c << 8) | (c << 16);
            if (c == 0)
            {
                wp->routine_8++;
                wp->efc.model.pos.pad = 0;
            }
            break;
    }
    // Word stores over pairs of matrix fields: the diagonal pairs set 0x1000, the others clear.
    *(sint32 *)&wp->efc.model.mtx.m[0][0] = 0x1000;
    *(sint32 *)&wp->efc.model.mtx.m[1][1] = 0x1000;
    *(sint32 *)&wp->efc.model.mtx.m[2][2] = 0x1000;
    *(sint32 *)&wp->efc.model.mtx.m[0][2] = 0;
    *(sint32 *)&wp->efc.model.mtx.m[2][0] = 0;
    wp->efc.model.mtx.t[0]                = 0;
    wp->efc.model.mtx.t[1]                = 0;
    wp->efc.model.mtx.t[2]                = 0;
    wp->efc.model.mtx.m[0][0] = wp->efc.model.mtx.m[1][1] = wp->efc.model.mtx.m[2][2] = wp->efc.model.pos.pad;
    RotMatrixY(++wp->timer_B << 7, &wp->efc.model.mtx);
}

void func_80047BC8(void)
{
}

void func_80047BD0(void)
{
}

void func_80047BD8(W48_88_WORK *wp)
{
    func_80031988((WORK_48 *)wp);
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

void func_80047C64(W48_88_WORK *wp)
{
    func_80047CD8(wp);
}

void func_80047C84(W48_88_WORK *wp)
{
    wp->field_9         = 0;
    wp->field_A         = D_8008A6CD[0];
    wp->efc.sprite.code = D_8008A6C8[0];
    wp->efc.sprite.u    = D_8008A6CE[0];
    wp->efc.sprite.v    = D_8008A6CF[0];
    wp->efc.sprite.size = D_8008A6CC[0];
}

void func_80047CD8(W48_88_WORK *wp)
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
            func_80031988((WORK_48 *)wp);
        }
        else
        {
            wp->efc.sprite.code = D_8008A6C8[i * 2];
            wp->efc.sprite.u    = D_8008A6CE[i * 8];
            wp->efc.sprite.v    = D_8008A6CF[i * 8];
            wp->efc.sprite.size = D_8008A6CC[i * 8];
        }
    }
}

void func_80047D9C(W48_89_WORK *wp)
{
    D_8008A724[wp->routine_8](wp);
}

void func_80047DD8(W48_89_WORK *wp)
{
    PL_WORK *pl;
    W48_89_LINES *d;
    uint8 i;

    pl = Player_work;
    if (func_800482A8(wp) == 0)
    {
        d = &wp->lines_28;
        wp->flags |= 0x20;
        for (i = 0; i < 8; i++)
        {
            d->idx[i] = i;
            if (wp->type_3)
            {
                d->ang[i] = ((uint16)pl->ang.vy + 0x80 + (rand() & 0xFF)) & 0xFFF;
            }
            else
            {
                d->ang[i] = ((sint16)(pl->ang.vy - 0x100) + (rand() & 0xFF)) & 0xFFF;
            }
        }
        Sound_call(0x8D, 0, 0);
        wp->routine_8 = 1;
    }
}

void func_80047EC8(W48_89_WORK *wp)
{
    uint32 *prim;
    uint16 step;
    W48_89_LINES *d;
    SVECTOR v0;
    SVECTOR v1;
    uint16 h;
    uint16 r;
    sint32 s;
    uint8 i;
    uint8 j;
    uint8 lit;

    d = &wp->lines_28;
    if (func_800482A8(wp) != 0)
    {
        return;
    }
    if (wp->type_3)
    {
        wp->pos_1C[0] = Player_work[0].joint_pos[11].vx;
        wp->pos_1C[1] = Player_work[0].joint_pos[11].vy;
        wp->pos_1C[2] = Player_work[0].joint_pos[11].vz;
    }
    else
    {
        wp->pos_1C[0] = Player_work[0].joint_pos[14].vx;
        wp->pos_1C[1] = Player_work[0].joint_pos[14].vy;
        wp->pos_1C[2] = Player_work[0].joint_pos[14].vz;
    }
    for (i = 0; i < 8; i++)
    {
        lit  = 0;
        r    = 5;
        s    = 0;
        step = (rand() & 7) | 0x10;
        h    = (rand() & 0x3F) + 0x28;
        if (++d->idx[i] >= 8)
        {
            d->idx[i] = 0;
        }
        if (wp->type_3)
        {
            d->ang[i] = ((uint16)Player_work[0].ang.vy + 0x80 + (rand() & 0xFF)) & 0xFFF;
        }
        else
        {
            d->ang[i] = ((sint16)(Player_work[0].ang.vy - 0x100) + (rand() & 0xFF)) & 0xFFF;
        }
        for (j = 0; j < d->idx[i] * 2; j++)
        {
            v0.vx = wp->pos_1C[0] + ((rsin(d->ang[i]) * r) >> 12);
            v0.vz = wp->pos_1C[2] + ((rcos(d->ang[i]) * r) >> 12);
            // The (sint16) keeps the `- 16` on the sine term; without it GCC folds it into y.
            v0.vy = wp->pos_1C[1] - (sint16)(((rsin(s) * h) >> 12) - 16);
            r += step;
            s     = (j + 1) << 6;
            v1.vx = wp->pos_1C[0] + ((rsin(d->ang[i]) * r) >> 12);
            v1.vz = wp->pos_1C[2] + ((rcos(d->ang[i]) * r) >> 12);
            v1.vy = wp->pos_1C[1] - (sint16)(((rsin(s) * h) >> 12) - 16);
            if (rand() & 1)
            {
                prim    = Billboard_line_get();
                prim[0] = (v0.vy << 16) + v0.vx;
                prim[1] = 0x52104080;
                prim[2] = (v1.vy << 16) + v1.vx;
                prim[3] = lit ? 0x104080 : 0x10101;
                prim[4] = (v0.vz << 16) + v1.vz;
                prim[6] = 0xE1000020;
                lit     = 1;
            }
            else
            {
                lit = 0;
            }
        }
    }
    Sound_call(0x8D, 0, 0);
}

void func_80048268(W48_89_WORK *wp)
{
    Sound_call(0x8F, 0, 0);
    wp->routine_0 = 0;
    func_80031988((WORK_48 *)wp);
}

uint8 func_800482A8(W48_89_WORK *wp)
{
    uint16 pad;
    uint16 hit;

    if (Player_work[0].routine_9 == 3)
    {
        if (wp->type_3 != 0)
        {
            pad = Player_work[0].pad_now;
            if (!(pad & Player_work[0].keys_124[3]))
            {
                goto fail;
            }
            hit = Player_work[0].keys_124[2] & pad;
        }
        else
        {
            pad = Player_work[0].pad_now;
            if (!(pad & Player_work[0].keys_124[2]))
            {
                goto fail;
            }
            hit = Player_work[0].keys_124[3] & pad;
        }
        if (hit)
        {
            return 1;
        }
    }
    else
    {
    fail:
        wp->routine_8 = 2;
        return 1;
    }
    return 0;
}

void func_80048354(W48_8A_WORK *wp)
{
    D_8008A76C[wp->routine_8](wp);
}

void func_80048390(W48_8A_WORK *wp)
{
    wp->field_24 = 0x20;
    wp->field_C  = 0x80;
    wp->code_14  = 0x3D48002C;
    wp->rgbc_18  = 0x2EC06060;
    wp->idx_D    = 0;
    wp->routine_0 |= 0x22;
    if (wp->type_3 != 0)
    {
        wp->timer_E  = D_8008A748[0].time_4;
        wp->field_22 = D_8008A748[wp->idx_D].val_0;
        wp->field_23 = D_8008A748[wp->idx_D].val_2;
    }
    else
    {
        wp->timer_E  = D_8008A730[0].time_4;
        wp->field_22 = D_8008A730[wp->idx_D].val_0;
        wp->field_23 = D_8008A730[wp->idx_D].val_2;
    }
    wp->routine_8 = 1;
    wp->timer_B   = 0;
}

void func_80048484(W48_8A_WORK *wp)
{
    wp->timer_E--;
    if ((sint8)wp->timer_E == 0) // the cast is needed to match (sll/sra test)
    {
        if (wp->type_3 != 0)
        {
            wp->field_24 += 8;
            wp->idx_D++;
            wp->timer_E  = D_8008A748[wp->idx_D].time_4;
            wp->field_22 = D_8008A748[wp->idx_D].val_0;
            wp->field_23 = D_8008A748[wp->idx_D].val_2;
        }
        else
        {
            wp->idx_D++;
            wp->timer_E  = D_8008A730[wp->idx_D].time_4;
            wp->field_22 = D_8008A730[wp->idx_D].val_0;
            wp->field_23 = D_8008A730[wp->idx_D].val_2;
        }
    }
    if (wp->timer_E == 0x80)
    {
        wp->routine_8 = 2;
    }
}

void func_800485C4(W48_8A_WORK *wp)
{
    func_80031988((WORK_48 *)wp);
}

void func_800485E4(WORK_48 *wp)
{
    D_8008A778[wp->flag_4](wp);
}
