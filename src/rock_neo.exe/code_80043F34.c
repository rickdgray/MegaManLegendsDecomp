#include "common.h"
#include "psyq/libc.h"
#include "code_80043F34.h"
#include "sound.h"

// Small data (.sdata 0x80097DE4-0x80097DF0): reached through $gp in this file.
// Step durations, [flag_3][step]: func_80044C94 reads step 0, func_80044D5C..func_80044F44 the
// others (indexed by flag_3)
uint8 D_80097DE4[3][4] = {{3, 3, 3, 3}, {4, 4, 4, 4}, {8, 8, 8, 4}};

void func_80043F34(WORK_48 *wp)
{
    D_8008A208[wp->routine_8](wp);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_80043F70);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_800441CC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_8004441C);

void func_8004492C(void)
{
}

void func_80044934(void)
{
}

void func_8004493C(WORK_48 *wp)
{
    func_80031988(wp);
}

void func_8004495C(WORK_48 *wp)
{
    D_8008A220[wp->routine_8](wp);
}

void func_80044998(WORK_48 *wp)
{
    wp->routine_0 |= 2;
    Model_work_init((ATTACH_WORK *)wp, 0);
    wp->field_40 = 0x2808080;
    // field_14 is the model data Model_work_init found; the word at 0x10 of the block its word at
    // 0x70 points to
    wp->u_44.ptr = *(void **)(*(uint8 **)((uint8 *)wp->field_14 + 0x70) + 0x10);
    wp->routine_8++;
    wp->timer_B = 0x10;
}

void func_80044A00(WORK_48 *wp)
{
    VECTOR scale;

    if (--wp->timer_B == 0)
    {
        wp->routine_8++;
    }
    scale.vx = scale.vy = scale.vz = 0x1115;
    ScaleMatrix(&wp->u_18.mtx, &scale);
    wp->field_40 -= 0x80808;
}

void func_80044A80(WORK_48 *wp)
{
    wp->routine_0 = 0;
    func_80031988(wp);
}

void func_80044AA0(void)
{
}

void func_80044AA8(void)
{
}

void func_80044AB0(WORK_48 *wp)
{
    D_8008A250[wp->routine_8](wp);
}

void func_80044AEC(WORK_48 *wp)
{
    wp->field_14        = 0x3D48002E;
    wp->u_18.s.field_18 = 0x2E808080;
    wp->routine_0 |= 0x22;
    wp->u_18.s.field_22 = D_8008A234[0][0];
    wp->u_18.s.field_23 = D_8008A234[0][1];
    wp->u_18.s.field_24 = D_8008A248[0];
    wp->u_18.s.field_26 = rand() & 0x3F;
    wp->timer_B         = D_8008A240[0];
    wp->field_A         = 0;
    wp->field_9         = 0;
    wp->routine_8++;
    if (wp->field_C.rec.b0 != 0)
    {
        Sound_call2(0x9B, (SVECTOR *)wp->u_18.s.pos_1C);
    }
}

void func_80044BA0(WORK_48 *wp)
{
    uint8 step;
    SVECTOR unused; // never used; the target's frame (0x20) has room for an 8-byte local

    wp->field_9++;
    if (--wp->timer_B == 0)
    {
        step = ++wp->field_A;
        if (step >= 6)
        {
            func_80031988(wp);
        }
        else
        {
            wp->timer_B         = D_8008A240[step];
            wp->u_18.s.field_22 = D_8008A234[step][0];
            wp->u_18.s.field_23 = D_8008A234[step][1];
            wp->u_18.s.field_24 = D_8008A248[wp->field_9];
        }
    }
}

void func_80044C58(WORK_48 *wp)
{
    D_8008A258[wp->routine_8](wp);
}

void func_80044C94(WORK_48 *wp)
{
    wp->field_14        = 0x3D48002E;
    wp->u_18.s.field_18 = 0x2E404040;
    wp->u_18.s.field_22 = 0x20;
    wp->routine_0 |= 2;
    wp->u_18.s.field_23 = 0;
    wp->flags |= 0x20;
    switch (wp->flag_3)
    {
        case 0:
        default:
            wp->u_18.s.field_24 = 0xD;
            wp->timer_B         = D_80097DE4[0][0];
            wp->flag_3          = 0;
            break;
        case 1:
            wp->u_18.s.field_24 = 0x20;
            wp->timer_B         = D_80097DE4[1][0];
            wp->flag_3          = 1;
            break;
        case 2:
            wp->u_18.s.field_24 = 0x40;
            wp->timer_B         = D_80097DE4[2][0];
            wp->flag_3          = 2;
            break;
        case 3:
            wp->u_18.s.field_24 = 0x80;
            wp->timer_B         = D_80097DE4[0][0];
            wp->flag_3          = 0;
            break;
    }
    wp->field_A = 0;
    wp->routine_8++;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_80044D5C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_80044E50);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_80044F44);

void func_80045038(WORK_48 *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_0 = 0;
        func_80031988(wp);
    }
}

void func_80045074(WORK_48 *wp)
{
    D_8008A288[wp->routine_8](wp);
}

void func_800450B0(WORK_48 *wp)
{
    wp->field_14        = 0x3D48002E;
    wp->u_18.s.field_18 = 0x2E208080;
    wp->routine_0 |= 0x22;
    wp->u_18.s.field_22 = D_8008A26C[0][0];
    wp->u_18.s.field_23 = D_8008A26C[0][1];
    if (wp->flag_3 == 0)
    {
        wp->field_C.rec.b0 = 12;
    }
    wp->u_18.s.field_24 = (D_8008A280[0] * wp->field_C.rec.b0) >> 4;
    wp->u_18.s.field_26 = rand() & 0x3F;
    wp->timer_B         = D_8008A278[0];
    wp->field_A         = 0;
    wp->field_9         = 0;
    wp->routine_8++;
}

void func_80045170(WORK_48 *wp)
{
    uint8 step;
    SVECTOR unused; // never used; the target's frame (0x20) has room for an 8-byte local

    wp->field_9++;
    if (--wp->timer_B == 0)
    {
        step = ++wp->field_A;
        if (step >= 6)
        {
            func_80031988(wp);
        }
        else
        {
            wp->timer_B         = D_8008A278[step];
            wp->u_18.s.field_22 = D_8008A26C[step][0];
            wp->u_18.s.field_23 = D_8008A26C[step][1];
            wp->u_18.s.field_24 = (D_8008A280[wp->field_9] * wp->field_C.rec.b0) >> 4;
        }
    }
}

void func_80045238(WORK_48 *wp)
{
    D_8008A290[wp->routine_8](wp);
}

void func_80045274(WORK_48 *wp)
{
    uint32 idx;

    wp->routine_0 |= 0x22;
    idx = wp->flag_3;
    if (idx >= 0x10)
    {
        wp->u_18.s.field_24 = 0x40;
        idx                 = wp->flag_3 -= 0x10;
    }
    else
    {
        wp->u_18.s.field_24 = D_80097DF0[idx].field_24;
    }
    wp->field_14        = D_80097DF0[idx].field_14;
    wp->u_18.s.field_18 = D_80097DF0[idx].field_18;
    wp->u_18.s.field_22 = D_80097DF0[idx].field_22;
    wp->u_18.s.field_23 = D_80097DF0[idx].field_23;
    wp->field_A         = 0;
    wp->routine_8       = D_80097DF0[idx].routine_8;
}

void func_80045338(WORK_48 *wp)
{
    if (wp->field_40 == 0xFFFF)
    {
        func_80031988(wp);
    }
    else
    {
        wp->u_18.s.field_22 = 0xA0;
        wp->u_18.s.field_23 = 0x40;
        wp->routine_8++;
        if (wp->u_18.s.field_24 >= 0x40)
        {
            wp->u_18.s.pos_1C[0] -= wp->u_18.s.vz_30 / 256;
            wp->u_18.s.pos_1C[1] -= wp->u_18.s.ax_32 / 256;
            wp->u_18.s.pos_1C[2] -= wp->u_18.s.ay_34 / 256;
        }
        wp->u_18.s.field_24 >>= 1;
    }
}

void func_80045400(WORK_48 *wp)
{
    wp->u_18.s.field_26 = rand() & 0x3F;
    wp->field_A         = 0x10;
    wp->routine_8++;
    wp->u_18.s.vz_30    = (uint32)-rsin(wp->field_40) >> 9;
    wp->u_18.s.ax_32    = (rand() & 3) - 0x14;
    wp->u_18.s.ay_34    = (uint32)-rcos(wp->field_40) >> 9;
    wp->u_18.s.field_28 = wp->u_18.s.vx_2C = 0;
    wp->u_18.s.field_2A                    = 5;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80043F34", func_8004548C);

void func_8004557C(WORK_48 *wp)
{
    func_80031988(wp);
}

void func_8004559C(WORK_48 *wp)
{
    wp->u_18.s.field_22 = D_80097E08[wp->routine_8 - 5][0];
    wp->u_18.s.field_23 = D_80097E08[wp->routine_8 - 5][1];
    wp->routine_8++;
    Sound_call2(0x121, (SVECTOR *)wp->u_18.s.pos_1C);
}

void func_80045608(WORK_48 *wp)
{
    wp->u_18.s.field_22 = D_80097E08[wp->routine_8 - 5][0];
    wp->u_18.s.field_23 = D_80097E08[wp->routine_8 - 5][1];
    wp->routine_8++;
}

void func_80045650(WORK_48 *wp)
{
    wp->u_18.s.field_22 = D_80097E08[wp->routine_8 - 5][0];
    wp->u_18.s.field_23 = D_80097E08[wp->routine_8 - 5][1];
    wp->routine_8       = 4;
}

void func_8004569C(WORK_48 *wp)
{
    D_8008A358[wp->routine_8](wp);
}

// For the code still in assembly: splat's labels inside the table above (aliases). Drop each
// once no assembly names it.
__asm__(".text\n"
        ".globl D_80097DE5\n.set D_80097DE5, D_80097DE4+1\n"
        ".globl D_80097DE6\n.set D_80097DE6, D_80097DE4+2\n"
        ".globl D_80097DE7\n.set D_80097DE7, D_80097DE4+3\n");
