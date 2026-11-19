#include "common.h"
#include "psyq/rand.h"
#include "code_80043F34.h"
#include "code_800456D8.h"
#include "player.h"
#include "sound.h"
#include "code_80037FB4.h"
#include "code_80048620.h"

// Small data (.sdata 0x80097DDC-0x80097DEF). D_80097DDC and D_80097DE0 are only read indexed
// (lui-based either way); D_80097DE4 is reached through $gp.
uint8 D_80097DDC[4] = {10, 12, 16, 8};          // func_800441CC
uint8 D_80097DE0[4] = {0x80, 0x8B, 0x8C, 0x80}; // func_80043F70
// Step durations, [flag_3][step]: func_80044C94 reads step 0, func_80044D5C..func_80044F44 the
// others (indexed by flag_3)
uint8 D_80097DE4[3][4] = {{3, 3, 3, 3}, {4, 4, 4, 4}, {8, 8, 8, 4}};

void func_80043F34(W48_80_WORK *wp)
{
    D_8008A208[wp->routine_8](wp);
}

void func_80043F70(W48_80_WORK *wp)
{
    uint32 sub;
    W48_80_WORK *e;
    W48_80_WORK *e2;

    if (wp->type_3 == 0xFE)
    {
        wp->sound_C = 0;
        wp->type_3  = 0xC2;
    }
    else
    {
        wp->sound_C = 1;
    }
    if (wp->variant_E != 0)
    {
        wp->routine_0 |= 0x82;
    }
    else
    {
        wp->routine_0 |= 2;
    }
    sub            = wp->type_3 & 0xF;
    wp->hw_44[0]   = D_8008A138[sub][wp->size_D][0];
    wp->hw_44[1]   = D_8008A138[sub][wp->size_D][1];
    wp->rgbc_40    = 0x02808080;
    wp->field_A    = 0;
    wp->pos_38.pad = 0;
    // Identity matrix by words, then the diagonal cleared
    *(uint32 *)&wp->mtx.m[0][0] = 0x1000;
    *(uint32 *)&wp->mtx.m[0][2] = 0;
    *(uint32 *)&wp->mtx.m[1][1] = 0x1000;
    *(uint32 *)&wp->mtx.m[2][0] = 0;
    *(uint32 *)&wp->mtx.m[2][2] = 0x1000;
    wp->mtx.t[0]                = 0;
    wp->mtx.t[1]                = 0;
    wp->mtx.t[2]                = 0;
    wp->mtx.m[2][2]             = 0;
    wp->mtx.m[1][1]             = 0;
    wp->mtx.m[0][0]             = 0;
    if (wp->type_3 & 0x80)
    {
        sub = 0;
    }
    else if (wp->type_3 & 0x20)
    {
        Sound_call2(0xA4, &wp->pos_38);
        wp->sound_C = 0;
        sub         = 2;
        func_800398E0(0x1E);
        e = (W48_80_WORK *)func_80031618();
        if (e != NULL)
        {
            e->routine_0 = 5;
            e->id_2      = 0x80;
            e->type_3    = 5;
            e->pos_38    = wp->pos_38;
        }
        e2 = (W48_80_WORK *)func_80031618();
        if (e2 != NULL)
        {
            e2->routine_0 = 0x45;
            e2->id_2      = 0x80;
            e2->type_3    = 6;
            e2->pos_38    = wp->pos_38;
        }
    }
    else
    {
        switch (sub = wp->type_3 & 0xF)
        {
            case 4:
            case 5:
            case 6:
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
    }
    wp->id_2 = D_80097DE0[wp->variant_E];
    Model_work_init((MODEL_WORK *)wp, (uint8 *)&sub);
    wp->id_2    = 0x80;
    wp->timer_B = 0;
    wp->routine_8++;
    if (wp->sound_C != 0)
    {
        Sound_call2(0xA1, &wp->pos_38);
    }
}

#ifdef NON_MATCHING
// Register allocation only, in the distance test: the target keeps the player's coordinate in v1
// (subu v0,v1,v0) and the three squares in a1/a0/t0; this gives v0 and a2/a1/a0.
void func_800441CC(W48_80_WORK *wp)
{
    uint32 size;
    sint32 dx;
    sint32 dy;
    sint32 dz;
    sint32 r;

    D_8008A214[wp->field_9](wp);
    size = D_80097DDC[wp->size_D];
    switch (wp->variant_E)
    {
        case 0:
            if (wp->type_3 & 0x40)
            {
                func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xA000, wp->kind_1, &D_800986C0, size | 0x10000000, 0, 0x80);
            }
            else if (wp->type_3 == 6)
            {
                if (wp->level_F != 0)
                {
                    dx = Player_work[0].pos.vx - wp->pos_38.vx;
                    dy = Player_work[0].pos.vy - wp->pos_38.vy;
                    dz = Player_work[0].pos.vz - wp->pos_38.vz;
                    r  = wp->pos_38.pad / 2;
                    if ((uint32)(r * r) >= (uint32)(dx * dx + dy * dy + dz * dz) && Player_work[0].field_74 == 0)
                    {
                        Player_work[0].owner_188.pad_0 |= 0x10000000;
                        switch (wp->level_F)
                        {
                            case 1:
                            default:
                                size = 0x20;
                                break;
                            case 2:
                                size = 0x30;
                                break;
                            case 3:
                                size = 0x40;
                                break;
                        }
                        Player_work[0].owner_188.pad_0 = (Player_work[0].owner_188.pad_0 & 0xFF000000) |
                                                         ((Player_work[0].owner_188.pad_0 & 0xFFFFFF) + size) | 0x01000000;
                    }
                }
                else
                {
                    func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xC000, wp->kind_1, &D_800986C0, 0x31000000, 0, 0x80);
                }
            }
            else
            {
                func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0xC000, wp->kind_1, &D_800986C0, size | 0x10000000, 0, 0x80);
            }
            break;
        case 1:
            func_800341BC(&wp->pos_38, wp->pos_38.pad / 2, 0, 0x4000, wp->kind_1, &D_800986C0, size | 0x10000000, 0, 0x80);
            break;
        case 2:
        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_800441CC);
#endif

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_8004441C);

void func_8004492C(void)
{
}

void func_80044934(void)
{
}

void func_8004493C(W48_80_WORK *wp)
{
    func_80031988((WORK_48 *)wp);
}

void func_8004495C(W48_81_WORK *wp)
{
    D_8008A220[wp->routine_8](wp);
}

void func_80044998(W48_81_WORK *wp)
{
    wp->routine_0 |= 2;
    Model_work_init((MODEL_WORK *)wp, 0);
    wp->rgbc_40 = 0x2808080;
    // The word at 0x10 of the block the model data's word at 0x70 points to
    wp->ptr_44 = *(void **)(*(uint8 **)(wp->data_14 + 0x70) + 0x10);
    wp->routine_8++;
    wp->timer_B = 0x10;
}

void func_80044A00(W48_81_WORK *wp)
{
    VECTOR scale;

    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
    }
    scale.vx = scale.vy = scale.vz = 0x1115;
    ScaleMatrix(&wp->mtx, &scale);
    wp->rgbc_40 -= 0x80808;
}

void func_80044A80(W48_81_WORK *wp)
{
    wp->routine_0 = 0;
    func_80031988((WORK_48 *)wp);
}

void func_80044AA0(void)
{
}

void func_80044AA8(void)
{
}

void func_80044AB0(W48_82_WORK *wp)
{
    D_8008A250[wp->routine_8](wp);
}

void func_80044AEC(W48_82_WORK *wp)
{
    wp->code_14 = 0x3D48002E;
    wp->rgbc_18 = 0x2E808080;
    wp->routine_0 |= 0x22;
    wp->field_22 = D_8008A234[0][0];
    wp->field_23 = D_8008A234[0][1];
    wp->field_24 = D_8008A248[0];
    wp->field_26 = rand() & 0x3F;
    wp->timer_B  = D_8008A240[0];
    wp->field_A  = 0;
    wp->field_9  = 0;
    wp->routine_8++;
    if (wp->field_C != 0)
    {
        Sound_call2(0x9B, (SVECTOR *)wp->pos_1C);
    }
}

void func_80044BA0(W48_82_WORK *wp)
{
    uint8 step;
    SVECTOR unused; // never used; the target's frame (0x20) has room for an 8-byte local

    wp->field_9++;
    if (--wp->timer_B == 0)
    {
        step = ++wp->field_A;
        if (step >= 6)
        {
            func_80031988((WORK_48 *)wp);
        }
        else
        {
            wp->timer_B  = D_8008A240[step];
            wp->field_22 = D_8008A234[step][0];
            wp->field_23 = D_8008A234[step][1];
            wp->field_24 = D_8008A248[wp->field_9];
        }
    }
}

void func_80044C58(W48_83_WORK *wp)
{
    D_8008A258[wp->routine_8](wp);
}

void func_80044C94(W48_83_WORK *wp)
{
    wp->code_14  = 0x3D48002E;
    wp->rgbc_18  = 0x2E404040;
    wp->field_22 = 0x20;
    wp->routine_0 |= 2;
    wp->field_23 = 0;
    wp->flags |= 0x20;
    switch (wp->type_3)
    {
        case 0:
        default:
            wp->field_24 = 0xD;
            wp->timer_B  = D_80097DE4[0][0];
            wp->type_3   = 0;
            break;
        case 1:
            wp->field_24 = 0x20;
            wp->timer_B  = D_80097DE4[1][0];
            wp->type_3   = 1;
            break;
        case 2:
            wp->field_24 = 0x40;
            wp->timer_B  = D_80097DE4[2][0];
            wp->type_3   = 2;
            break;
        case 3:
            wp->field_24 = 0x80;
            wp->timer_B  = D_80097DE4[0][0];
            wp->type_3   = 0;
            break;
    }
    wp->field_A = 0;
    wp->routine_8++;
}

void func_80044D5C(W48_83_WORK *wp)
{
    switch (wp->type_3)
    {
        case 0:
            wp->pos_1C[1]--;
            wp->field_24++;
            wp->rgbc_18 -= 0x40404;
            break;
        case 1:
            wp->field_24--;
            wp->rgbc_18 -= 0x40404;
            break;
        case 2:
        default:
            wp->pos_1C[1] -= 5;
            wp->field_24 += 6;
            wp->rgbc_18 += 0x40404;
            break;
    }
    if (--wp->timer_B == 0)
    {
        wp->timer_B = D_80097DE4[wp->type_3][1];
        wp->routine_8++;
        wp->field_22 = 0x40;
    }
}

void func_80044E50(W48_83_WORK *wp)
{
    switch (wp->type_3)
    {
        case 0:
            wp->pos_1C[1]--;
            wp->field_24++;
            wp->rgbc_18 -= 0x40404;
            break;
        case 1:
            wp->field_24--;
            wp->rgbc_18 -= 0x40404;
            break;
        case 2:
        default:
            wp->pos_1C[1] -= 5;
            wp->field_24 -= 2;
            wp->rgbc_18 -= 0x40404;
            break;
    }
    if (--wp->timer_B == 0)
    {
        wp->timer_B = D_80097DE4[wp->type_3][2];
        wp->routine_8++;
        wp->field_22 = 0x60;
    }
}

void func_80044F44(W48_83_WORK *wp)
{
    switch (wp->type_3)
    {
        case 0:
            wp->pos_1C[1] -= 2;
            wp->field_24++;
            wp->rgbc_18 -= 0x40404;
            break;
        case 1:
            wp->field_24--;
            wp->rgbc_18 -= 0x40404;
            break;
        case 2:
        default:
            wp->pos_1C[1] -= 5;
            wp->field_24 -= 2;
            wp->rgbc_18 -= 0x40404;
            break;
    }
    if (--wp->timer_B == 0)
    {
        wp->timer_B = D_80097DE4[wp->type_3][3];
        wp->routine_8++;
        wp->field_22 = 0x80;
    }
}

void func_80045038(W48_83_WORK *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_0 = 0;
        func_80031988((WORK_48 *)wp);
    }
}

void func_80045074(W48_84_WORK *wp)
{
    D_8008A288[wp->routine_8](wp);
}

void func_800450B0(W48_84_WORK *wp)
{
    wp->code_14 = 0x3D48002E;
    wp->rgbc_18 = 0x2E208080;
    wp->routine_0 |= 0x22;
    wp->field_22 = D_8008A26C[0][0];
    wp->field_23 = D_8008A26C[0][1];
    if (wp->type_3 == 0)
    {
        wp->field_C = 12;
    }
    wp->field_24 = (D_8008A280[0] * wp->field_C) >> 4;
    wp->field_26 = rand() & 0x3F;
    wp->timer_B  = D_8008A278[0];
    wp->field_A  = 0;
    wp->field_9  = 0;
    wp->routine_8++;
}

void func_80045170(W48_84_WORK *wp)
{
    uint8 step;
    SVECTOR unused; // never used; the target's frame (0x20) has room for an 8-byte local

    wp->field_9++;
    if (--wp->timer_B == 0)
    {
        step = ++wp->field_A;
        if (step >= 6)
        {
            func_80031988((WORK_48 *)wp);
        }
        else
        {
            wp->timer_B  = D_8008A278[step];
            wp->field_22 = D_8008A26C[step][0];
            wp->field_23 = D_8008A26C[step][1];
            wp->field_24 = (D_8008A280[wp->field_9] * wp->field_C) >> 4;
        }
    }
}

void func_80045238(W48_85_WORK *wp)
{
    D_8008A290[wp->routine_8](wp);
}

void func_80045274(W48_85_WORK *wp)
{
    uint32 idx;

    wp->routine_0 |= 0x22;
    idx = wp->type_3;
    if (idx >= 0x10)
    {
        wp->field_24 = 0x40;
        idx          = wp->type_3 -= 0x10;
    }
    else
    {
        wp->field_24 = D_80097DF0[idx].field_24;
    }
    wp->code_14   = D_80097DF0[idx].field_14;
    wp->rgbc_18   = D_80097DF0[idx].field_18;
    wp->field_22  = D_80097DF0[idx].field_22;
    wp->field_23  = D_80097DF0[idx].field_23;
    wp->field_A   = 0;
    wp->routine_8 = D_80097DF0[idx].routine_8;
}

void func_80045338(W48_85_WORK *wp)
{
    if (wp->dir_40 == 0xFFFF)
    {
        func_80031988((WORK_48 *)wp);
    }
    else
    {
        wp->field_22 = 0xA0;
        wp->field_23 = 0x40;
        wp->routine_8++;
        if (wp->field_24 >= 0x40)
        {
            wp->pos_1C[0] -= wp->spd.vx / 256;
            wp->pos_1C[1] -= wp->spd.vy / 256;
            wp->pos_1C[2] -= wp->spd.vz / 256;
        }
        wp->field_24 >>= 1;
    }
}

void func_80045400(W48_85_WORK *wp)
{
    wp->field_26 = rand() & 0x3F;
    wp->field_A  = 0x10;
    wp->routine_8++;
    wp->spd.vx = (uint32)-rsin(wp->dir_40) >> 9;
    wp->spd.vy = (rand() & 3) - 0x14;
    wp->spd.vz = (uint32)-rcos(wp->dir_40) >> 9;
    wp->add.vx = wp->add.vz = 0;
    wp->add.vy              = 5;
}

void func_8004548C(W48_85_WORK *wp)
{
    if (func_80049C54((SVECTOR *)wp->pos_1C, (SVECTOR *)wp->pos_1C, 0, wp->kind_1) == 0)
    {
        wp->code_14 = 0x3D48002E;
        wp->rgbc_18 = 0x2E000000 | (wp->field_A << 3) | (wp->field_A << 11) | (wp->field_A << 19);
        if (wp->field_A-- != 0)
        {
            wp->pos_1C[0] += (wp->spd.vx += wp->add.vx);
            wp->pos_1C[1] += (wp->spd.vy += wp->add.vy);
            wp->pos_1C[2] += (wp->spd.vz += wp->add.vz);
            wp->field_26 += 8;
            return;
        }
    }
    wp->routine_8++;
}

void func_8004557C(W48_85_WORK *wp)
{
    func_80031988((WORK_48 *)wp);
}

void func_8004559C(W48_85_WORK *wp)
{
    wp->field_22 = D_80097E08[wp->routine_8 - 5][0];
    wp->field_23 = D_80097E08[wp->routine_8 - 5][1];
    wp->routine_8++;
    Sound_call2(0x121, (SVECTOR *)wp->pos_1C);
}

void func_80045608(W48_85_WORK *wp)
{
    wp->field_22 = D_80097E08[wp->routine_8 - 5][0];
    wp->field_23 = D_80097E08[wp->routine_8 - 5][1];
    wp->routine_8++;
}

void func_80045650(W48_85_WORK *wp)
{
    wp->field_22  = D_80097E08[wp->routine_8 - 5][0];
    wp->field_23  = D_80097E08[wp->routine_8 - 5][1];
    wp->routine_8 = 4;
}

void func_8004569C(W48_86_WORK *wp)
{
    D_8008A358[wp->routine_8](wp);
}
