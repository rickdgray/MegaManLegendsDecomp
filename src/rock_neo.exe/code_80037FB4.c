#include "common.h"
#include "player.h"
#include "code_80037FB4.h"
#include "scene.h"
#include "scratch.h"

// Small data (.sdata 0x80097D28-0x80097D74): reached through $gp in this file.
sint32 D_80097D28 = 0;
sint32 D_80097D2C = 0x200;
sint32 D_80097D30 = 0x30;
sint32 D_80097D34 = 0x200;
sint32 D_80097D38 = 0x300;
sint32 D_80097D3C = 0xa;
sint32 D_80097D40 = 0x14;
sint32 D_80097D44 = 3;
sint32 D_80097D48 = 0x3c;
sint32 D_80097D4C = 1;
sint32 D_80097D50 = 1;
sint32 D_80097D54 = 0x4b0;
sint32 D_80097D58 = 1;
sint32 D_80097D5C = 1;
sint32 D_80097D60 = 0x20ffe0;
sint32 D_80097D64 = 0x20ffe0;
sint32 D_80097D68 = 0x20ffe0;
sint32 D_80097D6C = 0;
uint32 D_80097D70 = 0;

// Small uninitialized statics (.sbss 0x80098660-0x8009869C).
static sint16 D_80098660[2];
static sint16 D_80098664[2];
static sint32 D_80098668;
static sint32 D_8009866C;
static sint32 D_80098670;
static sint32 D_80098674;
static VECTOR D_80098678; // saved camera position (func_8003A264 restores pos[2] from it)
static sint32 D_80098688;
static sint32 D_8009868C;
static sint32 D_80098690;
static sint32 D_80098694;
static sint32 D_80098698;

void func_80037FB4(VECTOR *pos, sint32 dist, sint32 ang_y, sint32 ang_x)
{
    VECTOR v;
    sint32 r;

    D_80098678             = *pos;
    D_800A3958.work.ang.vx = -ang_x & 0xFFF;
    D_80098688             = dist;
    D_8009868C             = ang_y;
    D_80098690             = ang_x;
    D_800A3958.work.ang.vy = ang_y & 0xFFF;
    D_800A3958.work.ang.vz = 0;
    RotMatrixYXZ(&D_800A3958.work.ang, &Scratch_mtx);
    TransposeMatrix(&Scratch_mtx, &Scratch_mtx2);
    r    = dist << Scratch_scale_shift;
    v.vx = (-pos->vx << Scratch_scale_shift) + ((((r * rsin(ang_y)) >> 12) * rcos(ang_x)) >> 12);
    v.vy = (-pos->vy << Scratch_scale_shift) + ((r * rsin(ang_x)) >> 12);
    v.vz = (-pos->vz << Scratch_scale_shift) + ((((r * rcos(ang_y)) >> 12) * rcos(ang_x)) >> 12);
    ApplyMatrixLV(&Scratch_mtx2, &v, (VECTOR *)Scratch_mtx2.t);
    Scratch_view_mtx      = Scratch_mtx2;
    v.vx                  = ((((dist * rsin(ang_y)) >> 12) * rcos(ang_x)) >> 12) - pos->vx;
    v.vy                  = ((dist * rsin(ang_x)) >> 12) - pos->vy;
    v.vz                  = ((((dist * rcos(ang_y)) >> 12) * rcos(ang_x)) >> 12) - pos->vz;
    Camera_work.pos_A8    = Camera_work.pos_98;
    Scratch_cam_pos.vx    = -v.vx;
    Camera_work.pos_98.vx = Scratch_cam_pos.vx;
    Scratch_cam_pos.vy    = -v.vy;
    Camera_work.pos_98.vy = Scratch_cam_pos.vy;
    Scratch_cam_pos.vz    = -v.vz;
    Camera_work.pos_98.vz = Scratch_cam_pos.vz;
    ApplyMatrixLV(&Scratch_mtx2, &v, &v);
    Scratch_trans.vx = v.vx;
    Scratch_trans.vy = v.vy;
    Scratch_trans.vz = v.vz;
}

void func_80038324(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39A0 = *arg0;
    func_80037FB4(arg0, arg1, arg2, arg3);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038370);

void func_800384A4(VECTOR *arg0, VECTOR *arg1)
{
    D_800A39A0 = *arg0;
    func_80038370(arg0, arg1);
}

void func_800384F0(VECTOR *pos, sint32 ang_y, sint32 ang_x)
{
    VECTOR v;
    sint16 x;
    sint16 y;
    sint16 z;

    D_800A3958.work.ang.vx = -ang_x & 0xFFF;
    D_800A3958.work.ang.vy = ang_y & 0xFFF;
    D_800A3958.work.ang.vz = 0;
    RotMatrixYXZ(&D_800A3958.work.ang, &Scratch_mtx);
    TransposeMatrix(&Scratch_mtx, &Scratch_mtx2);
    v.vx = -pos->vx;
    v.vy = -pos->vy;
    v.vz = -pos->vz;
    ApplyMatrixLV(&Scratch_mtx2, &v, (VECTOR *)Scratch_mtx2.t);
    x                     = -v.vx;
    y                     = -v.vy;
    z                     = -v.vz;
    Scratch_cam_pos.vx    = x;
    Scratch_cam_pos.vy    = y;
    Scratch_cam_pos.vz    = z;
    Scratch_view_mtx      = Scratch_mtx2;
    Camera_work.pos_98.vx = x;
    Camera_work.pos_98.vy = y;
    Camera_work.pos_98.vz = z;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038648);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_80038894);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_800392CC);

void func_8003949C(void)
{
}

void func_800394A4(void)
{
}

void func_800394AC(void)
{
    if (Camera_work.unk8 != 0)
    {
        Camera_work.unkA             = 0x40 - (uint8)Camera_work.unkA;
        Camera_work.param[2].field_0 = Camera_work.param[0].field_0;
        Camera_work.param[2].field_8 = Camera_work.param[0].field_8;
        Camera_work.pos[2]           = Camera_work.pos[0];
        Camera_work.param[4].field_0 = 0x200;
        Camera_work.param[4].field_8 = 0x30;
        Camera_work.pos[4]           = Camera_work.pos[0];
        Camera_work.pos[1].vy        = 0x96;
        Camera_work.pos[4].vy        = Player_work[0].pos.vy - 0x96;
        Camera_work.unk8             = 0;
        Camera_work.unk9             = -8;
        Camera_work.param[4].ang     = Camera_work.param[0].ang;
        Camera_work.param[2].ang     = Camera_work.param[0].ang;
    }
    else
    {
        Camera_work.param[0].field_8 = 0x30;
        Camera_work.param[0].field_0 = 0x200;
        Camera_work.unkA             = 0;
    }
}

void func_800395E8(void)
{
    D_800A396C = 0x30;
    D_800A3964 = 0x200;
    D_800A3962 = -1;
    D_800A3960 = 0;
    D_800A39B4 = 0x96;
    D_800A3959 = 0;
}

void func_80039630(sint32 field_8, sint32 unused)
{
    if (Camera_work.routine_2 != 0)
    {
        Camera_work.param[0].field_8 = field_8;
        return;
    }
    if (Camera_work.mode_1 != 0)
    {
        return;
    }
    if (Camera_work.unk8 == 0)
    {
        Camera_work.unkA             = 0x40;
        D_80097D2C                   = 0x200;
        Camera_work.param[2].field_0 = Camera_work.param[0].field_0;
        Camera_work.param[2].field_8 = Camera_work.param[0].field_8;
        Camera_work.pos[2]           = Camera_work.pos[0];
        Camera_work.param[4].field_0 = 0x190;
        Camera_work.param[4].field_8 = field_8;
        Camera_work.pos[4]           = Camera_work.pos[0];
        Camera_work.pos[1].vy        = 0xD2;
        Camera_work.pos[4].vy        = Player_work[0].pos.vy - 0xD2;
        Camera_work.unk8             = 3;
        Camera_work.unk9             = -8;
        Camera_work.param[2].ang = Camera_work.param[4].ang = Camera_work.param[0].ang;
    }
    else if (Camera_work.unk8 == 3)
    {
        Camera_work.param[0].field_8 = field_8;
        Camera_work.param[4].field_8 = field_8;
        if (Camera_work.unkA <= 0)
        {
            Camera_work.pos[0].vx = Player_work[0].pos.vx;
            Camera_work.pos[0].vy = Player_work[0].pos.vy - Camera_work.pos[1].vy;
            Camera_work.pos[0].vz = Player_work[0].pos.vz;
        }
    }
}

void func_800397E8(void)
{
    D_800A396C            = 0x30;
    D_80097D2C            = 0x200;
    D_800A3964            = 0x200;
    D_800A3962            = -1;
    Player_work[0].unk44D = 0;
}

void func_80039820(void)
{
    sint32 x;
    sint32 y;
    sint32 z;
    sint32 rot;

    x                            = Player_work[0].pos.vx;
    y                            = Player_work[0].pos.vy;
    z                            = Player_work[0].pos.vz;
    rot                          = Player_work[0].ang.vy;
    Camera_work.param[0].field_8 = 0x30;
    Camera_work.param[0].field_0 = D_80097D2C = 0x200;
    Camera_work.unkA                          = -1;
    Camera_work.mode_1                        = 0;
    Player_work[0].unk44D                     = 0;
    Camera_work.pos[1].vy                     = 0x96;
    Camera_work.pos[0].vx = Camera_work.pos[2].vx = Camera_work.pos[4].vx = x;
    Camera_work.pos[0].vy = Camera_work.pos[2].vy = Camera_work.pos[4].vy = y;
    Camera_work.pos[0].vz = Camera_work.pos[2].vz = Camera_work.pos[4].vz = z;
    Camera_work.param[0].ang                                              = rot + 0x800;
}

void func_800398E0(sint32 arg0)
{
    if (arg0 > 0)
    {
        D_800A395F = arg0;
    }
}

void Swing_Camera2(sint32 power, uint32 near, uint32 far, SVECTOR *pos)
{
    VECTOR d;
    uint32 dist;

    if (power > 0)
    {
        d.vx = Scratch_cam_pos.vx - pos->vx;
        d.vy = Scratch_cam_pos.vy - pos->vy;
        d.vz = Scratch_cam_pos.vz - pos->vz;
        dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
        if (far >= dist)
        {
            if (dist < near)
            {
                d.vz = near; // dead store, in the original (the build needs it)
            }
            Camera_work.routine_3 = (far - dist) * power / (far - near);
        }
    }
}

sint32 func_800399EC(uint32 *cmd)
{
    if (D_80097D70 >= 8)
    {
        return 0;
    }
    D_8009869C[(D_80097D6C + D_80097D70++) & 7] = cmd;
    return 1;
}

void func_80039A38(uint32 *cmd)
{
    D_80097D6C = 0;
    D_80097D70 = 0;
    func_800399EC(cmd);
}

void func_80039A60(void)
{
    uint32 *cmd;

    if (D_80097D70 != 0)
    {
        cmd = D_8009869C[D_80097D6C];
        D_80097D70--;
        switch (*cmd)
        {
            case 0:
            case 5:
            case 6:
                break;
            case 1:
                Camera_work.routine_1 = 0;
                break;
            case 3:
                D_8009A478            = D_800A3958;
                Camera_work.routine_1 = 6;
                break;
            case 4:
                D_800A3958 = D_8009A478;
                // fall through
            case 2:
                Camera_work.routine_1 = 4;
                break;
        }
    }
}

sint32 func_80039B80(void)
{
    if (D_800A3960 == 0)
    {
        return 0;
    }
    return D_800A396C;
}

void func_80039BA4(sint32 arg0, sint32 arg1)
{
    D_800A395A = arg0;
    D_800A395B = arg1;
}

void func_80039BBC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39A0 = *arg0;
    D_800A3964 = arg1;
    D_800A3968 = arg2;
    D_800A396C = arg3;
}

void func_80039C08(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39D0 = *arg0;
    D_800A3988 = arg1;
    D_800A398C = arg2;
    D_800A3990 = arg3;
}

void func_80039C54(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39C0 = *arg0;
    D_800A397C = arg1;
    D_800A3980 = arg2;
    D_800A3984 = arg3;
}

void func_80039CA0(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39B0 = *arg0;
    D_800A3970 = arg1;
    D_800A3974 = arg2;
    D_800A3978 = arg3;
}

void func_80039CEC(VECTOR *arg0, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39E0 = *arg0;
    D_800A3994 = arg1;
    D_800A3998 = arg2;
    D_800A399C = arg3;
}

void func_80039D38(SVECTOR *d)
{
    D_800A3958.work.pos[2].vx += d->vx;
    D_800A3958.work.pos[2].vy += d->vy;
    D_800A3958.work.pos[2].vz += d->vz;
    D_800A3958.work.pos[4].vx += d->vx;
    D_800A3958.work.pos[4].vy += d->vy;
    D_800A3958.work.pos[4].vz += d->vz;
}

void func_80039DE8(void)
{
    D_80097D2C            = 0x200;
    Player_work[0].unk44D = 0;
    Scene_work.id_01      = D_80098674;
    Scene_work.unk00      = D_80098670;
}

sint32 func_80039E18(void)
{
    Scene_work.id_01 = D_80098674;
    Scene_work.unk00 = D_80098670;
    func_80039E50();
}

// D_80097D2C and param[4].field_0 get 0x200 in separate statements (a chained assignment moves
// the param[0].field_0 load earlier). The wrap distance is written dir + 0x1000 - base, as in
// func_80039FFC and func_8003A264.
void func_80039E50(void)
{
    sint32 base;
    sint32 dir;
    sint32 rot;

    Camera_work.mode_1           = 2;
    Camera_work.unkA             = 0x40;
    Camera_work.pos[2]           = Camera_work.pos[0];
    D_80097D2C                   = 0x200;
    Camera_work.pos[1].vy        = 0x96;
    Camera_work.param[4].field_0 = 0x200;
    Camera_work.param[4].field_8 = 0x30;
    Camera_work.unk9             = -4;
    Camera_work.param[2].field_0 = Camera_work.param[0].field_0;
    base                         = Camera_work.param[0].ang & 0xFFF;
    Camera_work.pos[4].vx        = Player_work[0].pos.vx;
    Player_work[0].unk44D        = 0;
    Camera_work.param[2].ang     = base;
    Camera_work.param[2].field_8 = Camera_work.param[0].field_8;
    Camera_work.pos[4].vy        = Player_work[0].pos.vy - 0x96;
    Camera_work.pos[4].vz        = Player_work[0].pos.vz;
    rot                          = Player_work[0].ang.vy + 0x800;
    Camera_work.param[4].ang = dir = rot & 0xFFF;
    if (dir < base)
    {
        if (base - dir > dir + 0x1000 - base)
        {
            Camera_work.param[4].ang = dir + 0x1000;
        }
    }
    else
    {
        if (dir - base > base + 0x1000 - dir)
        {
            Camera_work.param[2].ang = base + 0x1000;
        }
    }
}

void func_80039FAC(VECTOR *pos, sint32 field_0, sint32 ang, sint32 field_8)
{
    sint32 id;
    sint32 unk00;

    id               = Scene_work.id_01;
    Scene_work.id_01 = 0xFF;
    unk00            = Scene_work.unk00;
    Scene_work.unk00 = 1;
    D_80098674       = id;
    D_80098670       = unk00;
    func_80039FFC(pos, field_0, ang, field_8);
}

void func_80039FFC(VECTOR *pos, sint32 field_0, sint32 ang, sint32 field_8)
{
    sint32 base;

    Camera_work.mode_1           = 1;
    Camera_work.unkA             = 0x40;
    Camera_work.pos[2]           = Camera_work.pos[0];
    Camera_work.param[2].field_0 = Camera_work.param[0].field_0;
    D_80097D2C                   = 0x200;
    ang &= 0xFFF;
    Player_work[0].unk44D        = 0;
    Camera_work.param[2].ang     = Camera_work.param[0].ang & 0xFFF;
    Camera_work.param[2].field_8 = Camera_work.param[0].field_8;
    Camera_work.pos[4]           = *pos;
    Camera_work.param[4].field_0 = field_0;
    Camera_work.param[4].ang     = ang;
    Camera_work.param[4].field_8 = field_8;
    Camera_work.unk9             = -4;
    base                         = Camera_work.param[2].ang;
    if (ang < base)
    {
        if (base - ang > ang + 0x1000 - base)
        {
            Camera_work.param[4].ang = ang + 0x1000;
        }
    }
    else
    {
        if (ang - base > base + 0x1000 - ang)
        {
            Camera_work.param[2].ang = base + 0x1000;
        }
    }
}

sint32 func_8003A13C(void)
{
    return D_800A3962 >= 0;
}

// Moves angle a by step toward Camera_work.param[0].ang the short way round (mod 0x1000), but
// no closer than lim to it.
sint32 func_8003A154(sint32 a, sint32 lim, sint32 step)
{
    sint32 b;
    sint32 near;
    sint32 far;
    sint32 wrap;
    sint32 wrap2; // a separate local from wrap: merging them changes registers
    sint32 v;
    sint32 max;

    a &= 0xFFF;
    b = Camera_work.param[0].ang & 0xFFF;
    if (a < b)
    {
        near  = b - a;
        wrap2 = b - 0x1000;
        far   = a - wrap2;
        if (far < near)
        {
            if (step < far)
            {
                return a - step;
            }
            v = b + lim;
            if (a + 0x1000 < v)
            {
                return a;
            }
            return v;
        }
        if (step < near)
        {
            return a + step;
        }
        v = b - lim;
        if (v < a)
        {
            return a;
        }
        return v;
    }
    near = a - b;
    wrap = a - 0x1000;
    far  = b - wrap;
    if (far < near)
    {
        if (step < far)
        {
            return a + step;
        }
        v = b - lim;
        if (v < wrap)
        {
            return a;
        }
        return v;
    }
    if (step < near)
    {
        return a - step;
    }
    v   = a;
    max = b + lim;
    if (v < max)
    {
        return v;
    }
    return max;
}

// Shortest angular distance (mod 0x1000) from arg0 to D_800A3968.
// Remaining difference: GCC inverts the a < b test and swaps the branch bodies.
#ifdef NON_MATCHING
sint32 func_8003A218(sint32 arg0)
{
    sint32 a;
    sint32 b;
    sint32 d1;
    sint32 d2;
    sint32 t;

    a = arg0 & 0xFFF;
    b = D_800A3968 & 0xFFF;
    if (a < b)
    {
        d1 = b - a;
        t  = b - 0x1000;
        d2 = a - t;
    }
    else
    {
        d1 = a - b;
        t  = a - 0x1000;
        d2 = b - t;
    }
    if (d2 < d1)
    {
        return d2;
    }
    return d1;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80037FB4", func_8003A218);
#endif

// Same as func_80039E50, from the saved position and parameters.
void func_8003A264(void)
{
    sint32 base;
    sint32 dir;

    Camera_work.mode_1           = 2;
    Camera_work.unkA             = 0x40;
    Camera_work.pos[2]           = D_80098678;
    D_80097D2C                   = 0x200;
    Camera_work.pos[1].vy        = 0x96;
    Camera_work.param[4].field_0 = 0x200;
    Camera_work.param[4].field_8 = 0x30;
    Camera_work.unk9             = -4;
    Camera_work.param[2].field_0 = D_80098688;
    base                         = D_8009868C & 0xFFF;
    Camera_work.pos[4].vx        = Player_work[0].pos.vx;
    Player_work[0].unk44D        = 0;
    Camera_work.param[2].ang     = base;
    Camera_work.param[2].field_8 = D_80098690;
    Camera_work.pos[4].vy        = Player_work[0].pos.vy - 0x96;
    Camera_work.pos[4].vz        = Player_work[0].pos.vz;
    Camera_work.param[4].ang = dir = (Player_work[0].ang.vy + 0x800) & 0xFFF;
    if (dir < base)
    {
        if (base - dir > dir + 0x1000 - base)
        {
            Camera_work.param[4].ang = dir + 0x1000;
        }
    }
    else
    {
        if (dir - base > base + 0x1000 - dir)
        {
            Camera_work.param[2].ang = base + 0x1000;
        }
    }
}

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_80098662\n.set D_80098662, D_80098660+2\n"
        ".globl D_8009867C\n.set D_8009867C, D_80098678+4\n"
        ".globl D_80098680\n.set D_80098680, D_80098678+8\n");
