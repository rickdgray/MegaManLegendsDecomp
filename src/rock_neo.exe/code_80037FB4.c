#include "common.h"
#include "player.h"
#include "code_80037FB4.h"
#include "scene.h"
#include "scratch.h"
#include "pad.h"
#include "fastmem.h"
#include "code_80048620.h"

// Small data (.sdata 0x80097D28-0x80097D74): reached through $gp in this file.
sint32 D_80097D28  = 0;
sint32 D_80097D2C  = 0x200;
sint32 D_80097D30  = 0x30;
sint32 D_80097D34  = 0x200;
sint32 D_80097D38  = 0x300;
sint32 D_80097D3C  = 0xa;
sint32 D_80097D40  = 0x14;
sint32 D_80097D44  = 3;
sint32 D_80097D48  = 0x3c;
sint32 D_80097D4C  = 1;
sint32 D_80097D50  = 1;
sint32 D_80097D54  = 0x4b0;
uint32 D_80097D58  = 1;                                       // camera command word (Camera_init runs it through func_80039A38)
uint32 D_80097D5C  = 1;                                       // camera command word (Camera_update runs it through func_80039A38)
HIT_ENT D_80097D60 = {-0x20, 0x20, -0x20, 0x20, -0x20, 0x20}; // collision box of the camera position

sint32 D_80097D6C = 0;
uint32 D_80097D70 = 0;

// Small uninitialized statics (.sbss 0x80098660-0x8009869C).
static SVECTOR D_80098660; // camera position, tested against walls (Camera_update)
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

// Called only from this file
void func_800397E8(void);
void func_800392CC(void);

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

void func_80038370(VECTOR *pos, VECTOR *target)
{
    sint32 unused[24]; // unused: the frame has 0x60 bytes no code touches
    sint32 dist;
    sint32 sq;
    sint32 ang_y;

    D_800A39A0 = *pos;
    sq         = (pos->vx - target->vx) * (pos->vx - target->vx) + (pos->vz - target->vz) * (pos->vz - target->vz);
    dist       = SquareRoot0(sq);
    if (dist != 0)
    {
        dist = (sq / dist + dist) >> 1;
    }
    ang_y = ratan2(target->vx - pos->vx, target->vz - pos->vz) + 0x800;
    func_80037FB4(pos, dist, ang_y, -ratan2(target->vy - pos->vy, dist));
}

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

void Camera_init(void)
{
    sint32 x;
    sint32 y;
    sint32 z;
    sint32 i;
    CAMERA_BLOCK *cb;

    cb = &D_800A3958;
    Mem_clear(cb, &cb->words[0x38]);
    cb->work.unk0                = 1;
    x                            = Player_work[0].pos.vx;
    y                            = Player_work[0].pos.vy;
    z                            = Player_work[0].pos.vz;
    Camera_work.param[0].field_0 = Camera_work.param[2].field_0 = Camera_work.param[4].field_0 = 0x200;
    Camera_work.param[0].field_8 = Camera_work.param[2].field_8 = Camera_work.param[4].field_8 = 0x30;
    Camera_work.pos[1].vy                                                                      = 0x96;
    Camera_work.mode_1                                                                         = 0;
    Camera_work.unk2                                                                           = 0;
    Camera_work.unk3                                                                           = 0;
    *(uint32 *)&Camera_work.routine_0                                                          = 0;
    *(uint32 *)&Camera_work.unk8                                                               = 0;
    Camera_work.param[1].field_0                                                               = 0;
    Camera_work.param[1].field_8                                                               = 0;
    Camera_work.param[1].ang                                                                   = 0;
    Camera_work.param[0].ang = Camera_work.param[2].ang = Camera_work.param[4].ang = 0;
    cb->words[0x38]                                                                = 0;
    Camera_work.pos_98.vx = Camera_work.pos[0].vx = Camera_work.pos[2].vx = Camera_work.pos[4].vx = x;
    Camera_work.pos_98.vy = Camera_work.pos[0].vy = Camera_work.pos[2].vy = Camera_work.pos[4].vy = y;
    Camera_work.pos_98.vz = Camera_work.pos[0].vz = Camera_work.pos[2].vz = Camera_work.pos[4].vz = z;
    Camera_work.routine_1                                                                         = 0;
    Camera_work.routine_2                                                                         = 0;
    Camera_work.routine_3                                                                         = 0;
    Camera_work.routine_0                                                                         = 1;
    Camera_work.unkA                                                                              = -1;
    D_80098668                                                                                    = 0;
    D_8009866C                                                                                    = 0;
    D_80098670                                                                                    = 0;
    D_80098674                                                                                    = 0;
    D_80098678.vz                                                                                 = 0;
    D_80098678.vy                                                                                 = 0;
    D_80098678.vx                                                                                 = 0;
    D_80098690                                                                                    = 0;
    D_8009868C                                                                                    = 0;
    D_80098688                                                                                    = 0;
    D_80098694                                                                                    = 0;
    D_80097D28                                                                                    = 0;
    // The 16 words before D_8009A598's end (0x8009A55C-0x8009A59B) have no symbol of their own.
    for (i = 15; i >= 0; i--)
    {
        D_8009A598[i - 15] = 0;
    }
    D_80098698 = 0;
    D_80097D2C = 0x200;
    D_80097D30 = 0x30;
    D_80097D38 = 0x300;
    D_80097D3C = 10;
    D_80097D40 = 20;
    D_80097D44 = 3;
    D_80097D48 = 60;
    D_80097D4C = 1;
    D_80097D50 = 1;
    D_80097D34 = 0x200;
    D_80097D54 = 0x4B0;
    func_80037FB4(&cb->work.pos[0], cb->work.param[0].field_0, cb->work.param[0].ang, cb->work.param[0].field_8);
    func_80039A38(&D_80097D58);
    func_800397E8();
}

// The camera's per-frame update: param[0]/pos[0] follow the player (or target_E0) by
// routine_1, then blend toward param[3]/pos[3] by unk2 out of 0x100 - unk3 and set the view.
// The source reuses its locals: case 0's blend weight is blend, case 4's angle difference is rot
// (computed before the cur < want test), and the wrap test keeps param[3].ang - rot in speed.
void Camera_update(void)
{
    VECTOR pos;
    VECTOR unused;
    CAMERA_WORK *cw;
    sint32 cur;
    sint32 want;
    sint32 diff;
    sint32 step;
    sint32 speed;
    sint32 rot;
    sint32 total;
    sint32 rest;
    sint32 blend;
    sint32 wrap;
    sint32 base;
    sint32 near;

    func_80039A60();
    cw = &Camera_work;
    if (Camera_work.routine_0 != 1)
    {
        func_8001E550();
        D_80098668 = 0;
        return;
    }
    D_80098668++;
    if (Camera_work.routine_2 != 0)
    {
        func_800392CC();
        D_8009866C = Camera_work.routine_2;
        return;
    }
    switch (Camera_work.routine_1)
    {
        case 0:
            if (cw->unkA >= 0)
            {
                // vx and vy compared as one word
                if (Scene_work.unk00 == 0 && (*(sint32 *)&Player_work[0].pos.vx != *(sint32 *)&Player_work[0].old.vx ||
                                              Player_work[0].pos.vz != Player_work[0].old.vz))
                {
                    cw->pos[4].vx = Player_work[0].pos.vx;
                    cw->pos[4].vy = Player_work[0].pos.vy - cw->pos[1].vy;
                    cw->pos[4].vz = Player_work[0].pos.vz;
                }
                if (cw->unkA != 0)
                {
                    cw->unkA += cw->unk9;
                    if (cw->unkA < 0)
                    {
                        cw->unkA = 0;
                    }
                    blend                = cw->unkA;
                    cw->param[0].field_0 = (cw->param[2].field_0 * blend + cw->param[4].field_0 * (0x40 - blend)) >> 6;
                    cw->param[0].field_8 = (cw->param[2].field_8 * blend + cw->param[4].field_8 * (0x40 - blend)) >> 6;
                    cw->pos[0].vy        = (cw->pos[2].vy * blend + cw->pos[4].vy * (0x40 - blend)) >> 6;
                    if (cw->unk8 == 3)
                    {
                        cw->param[0].ang = Player_work[0].ang.vy + 0x800;
                    }
                    else
                    {
                        cw->param[0].ang = (cw->param[2].ang * blend + cw->param[4].ang * (0x40 - blend)) >> 6;
                    }
                    cw->pos[0].vx = (cw->pos[2].vx * blend + cw->pos[4].vx * (0x40 - blend)) >> 6;
                    cw->pos[0].vz = (cw->pos[2].vz * blend + cw->pos[4].vz * (0x40 - blend)) >> 6;
                }
                else
                {
                    cw->unkA             = -1;
                    cw->param[0].field_0 = cw->param[4].field_0;
                    cw->param[0].field_8 = cw->param[4].field_8;
                    cw->pos[0].vy        = cw->pos[4].vy;
                    if (cw->unk8 == 3)
                    {
                        cw->param[0].ang = Player_work[0].ang.vy + 0x800;
                    }
                    else
                    {
                        cw->param[0].ang = cw->param[4].ang;
                    }
                    cw->pos[0].vx = cw->pos[4].vx;
                    cw->pos[0].vz = cw->pos[4].vz;
                    if (cw->mode_1 == 2)
                    {
                        cw->mode_1 = 0;
                    }
                }
            }
            else if (cw->mode_1 == 0)
            {
                if (cw->unk8 == 3)
                {
                    cw->param[0].ang = Player_work[0].ang.vy + 0x800;
                }
                else
                {
                    cw->pos[0].vx = Player_work[0].pos.vx;
                    cw->pos[0].vy = Player_work[0].pos.vy - cw->pos[1].vy;
                    cw->pos[0].vz = Player_work[0].pos.vz;
                    if (D_80098668 == 1)
                    {
                        cw->param[0].ang = Player_work[0].ang.vy + 0x800;
                    }
                    else
                    {
                        speed      = (Player_work[0].turn_B4 >= 0) ? Player_work[0].turn_B4 : -Player_work[0].turn_B4;
                        D_80098694 = speed;
                        if (speed != 0)
                        {
                            if (speed >= 0x48)
                            {
                                D_80097D28 += 6;
                                if (D_80097D28 >= 0x48)
                                {
                                    D_80097D28 = 0x48;
                                }
                            }
                            else
                            {
                                D_80097D28 = speed * 7 / 8;
                            }
                        }
                        else
                        {
                            diff = func_8003A218(Player_work[0].ang.vy + 0x800, cw->param[0].ang);
                            if (diff >= 0x200)
                            {
                                D_80097D28 = 0x80;
                            }
                            else
                            {
                                D_80097D28 = diff / 4;
                                if (D_80097D28 < 0x18)
                                {
                                    D_80097D28 = 0x18;
                                }
                            }
                        }
                        cw->param[0].ang = func_8003A154(Player_work[0].ang.vy + 0x800, D_80097D28, 0x200);
                    }
                    if (Player_work[0].unk44D == 1)
                    {
                        D_80098660.vx = cw->pos_98.vx;
                        D_80098660.vy = cw->pos_98.vy;
                        D_80098660.vz = cw->pos_98.vz;
                        if (func_80049C54(&D_80098660, &D_80098660, &D_80097D60, 0xFFFF) == 0)
                        {
                            D_80097D48 = 0x3C;
                            D_80097D2C += 0xA;
                        }
                        else if (D_80097D48 == 0)
                        {
                            D_80097D2C -= 0xA;
                        }
                        else
                        {
                            D_80097D48--;
                        }
                    }
                    else if (D_80097D48 == 0)
                    {
                        D_80097D2C -= 0xA;
                    }
                    else
                    {
                        D_80097D48--;
                    }
                    if (D_80097D2C > 0x300)
                    {
                        D_80097D2C = 0x300;
                    }
                    if (D_80097D2C < 0x200)
                    {
                        D_80097D2C = 0x200;
                    }
                    cw->param[0].field_0 = D_80097D2C;
                }
            }
            break;
        case 1:
            if (PAD_ON(Joy2) & PAD_L1)
            {
                cw->routine_1 = 2;
            }
            break;
        case 2:
            if (PAD_ON(Joy2) & PAD_L1)
            {
                cw->routine_1 = 3;
            }
            if (cw->target_E0 != NULL)
            {
                cw->pos[0].vx    = cw->target_E0->pos.vx;
                cw->pos[0].vy    = cw->target_E0->pos.vy - cw->pos[1].vy;
                cw->pos[0].vz    = cw->target_E0->pos.vz;
                cw->param[0].ang = cw->target_E0->ang.vy + 0x800;
            }
            break;
        case 3:
            if (PAD_ON(Joy2) & PAD_L1)
            {
                cw->routine_1 = 5;
                goto follow;
            }
            else
            {
                if (cw->target_E0 != NULL)
                {
                    cw->pos[0].vx = cw->target_E0->pos.vx;
                    cw->pos[0].vy = cw->target_E0->pos.vy - cw->pos[1].vy;
                    cw->pos[0].vz = cw->target_E0->pos.vz;
                }
            }
            break;
        case 6:
            break;
        case 4:
            cur  = cw->param[0].ang & 0xFFF;
            want = (Player_work[0].ang.vy + 0x800) & 0xFFF;
            rot  = want - cur;
            if (cur < want)
            {
                if (rot > 0x60)
                {
                    step = -0x60;
                    base = want - 0x1000;
                    if (rot < cur - base)
                    {
                        step = 0x60;
                    }
                    goto turn;
                }
            }
            else
            {
                rot = cur - want;
                if (cur != want && rot > 0x60)
                {
                    step = 0x60;
                    base = cur - 0x1000;
                    if (rot < want - base)
                    {
                        step = -0x60;
                    }
                    goto turn;
                }
            }
            cw->param[0].ang = want;
            func_80039A38(&D_80097D5C);
            goto aim;
        turn:
            cw->param[0].ang += step;
        aim:
            cw->pos[0].vx = Player_work[0].pos.vx;
            cw->pos[0].vy = Player_work[0].pos.vy - cw->pos[1].vy;
            cw->pos[0].vz = Player_work[0].pos.vz;
            break;
        default:
            if (PAD_ON(Joy2) & PAD_L1)
            {
                cw->routine_1 = 0;
            }
        follow:
            cw->pos[0].vx    = Player_work[0].pos.vx;
            cw->pos[0].vy    = Player_work[0].pos.vy - cw->pos[1].vy;
            cw->pos[0].vz    = Player_work[0].pos.vz;
            cw->param[0].ang = Player_work[0].ang.vy + 0x800;
            break;
    }
    total = 0x100 - cw->unk3;
    blend = cw->unk2;
    rest  = total - blend;
    if (blend != 0)
    {
        rot = cw->param[0].ang;
        if (rot < cw->param[3].ang)
        {
            speed = cw->param[3].ang - rot;
            base  = cw->param[3].ang - 0x1000;
            if (rot - base < speed)
            {
                rot += 0x1000;
            }
        }
        else
        {
            near = rot - cw->param[3].ang;
            wrap = rot - 0x1000;
            if (cw->param[3].ang - wrap < near)
            {
                rot = wrap;
            }
        }
        pos.vx = (cw->pos[3].vx * rest + cw->pos[0].vx * blend) / total;
        pos.vy = (cw->pos[3].vy * rest + cw->pos[0].vy * blend) / total;
        pos.vz = (cw->pos[3].vz * rest + cw->pos[0].vz * blend) / total;
        func_80037FB4(&pos, (cw->param[3].field_0 * rest + cw->param[0].field_0 * blend) / total,
                      (cw->param[3].ang * rest + rot * blend) / total,
                      (cw->param[3].field_8 * rest + cw->param[0].field_8 * blend) / total);
        return;
    }
    cw->pos[0].vy -= cw->routine_3;
    func_80037FB4(&cw->pos[0], cw->param[0].field_0, cw->param[0].ang + cw->param[1].ang, cw->param[0].field_8 + cw->param[1].field_8);
    if (cw->routine_3 != 0)
    {
        if (cw->routine_3 < 10)
        {
            cw->routine_3 = 0;
        }
        else
        {
            cw->routine_3 -= 10;
        }
    }
}

void func_800392CC(void)
{
    CAMERA_WORK *cw;

    cw                       = &D_800A3958.work;
    Camera_work.pos[0].vx    = Player_work[0].pos.vx;
    Camera_work.pos[0].vy    = Player_work[0].pos.vy - 0xD2;
    Camera_work.pos[0].vz    = Player_work[0].pos.vz;
    Camera_work.param[0].ang = Player_work[0].ang.vy + 0x800;
    if (D_80097D4C != 0)
    {
        if (--D_80097D50 == 0)
        {
            D_80097D4C = 0;
        }
        Camera_work.param[0].field_0 = (Camera_work.param[0].field_0 * D_80097D50 + D_80097D54 * (0x10 - D_80097D50)) >> 4;
    }
    else if (PAD_ON(Joy1) & PAD_SELECT)
    {
        if (++Camera_work.routine_2 >= 3)
        {
            Camera_work.routine_2 = 1;
        }
        switch (Camera_work.routine_2 - 1)
        {
            case 0:
                D_80097D54 = 0x4B0;
                D_80097D50 = 0x10;
                D_80097D4C = 1;
                break;
            case 1:
                D_80097D54 = 0x190;
                D_80097D50 = 0x10;
                D_80097D4C = 1;
                break;
        }
    }
    Camera_work.unk8 = 1;
    cw->pos[0].vy -= cw->routine_3;
    func_80037FB4(&cw->pos[0], cw->param[0].field_0, cw->param[0].ang, cw->param[0].field_8);
    if (cw->routine_3 != 0)
    {
        if (cw->routine_3 < 10)
        {
            cw->routine_3 = 0;
        }
        else
        {
            cw->routine_3 -= 10;
        }
    }
}

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

// Shortest angular distance (mod 0x1000) from ang to D_800A3968.
sint32 func_8003A218(sint32 ang, sint32 unused)
{
    sint32 b;
    sint32 near;
    sint32 far;
    sint32 wrap;

    ang &= 0xFFF;
    b = D_800A3968 & 0xFFF;
    if (ang < b)
    {
        near = b - ang;
        wrap = b - 0x1000;
        far  = ang - wrap;
    }
    else
    {
        near = ang - b;
        wrap = ang - 0x1000;
        far  = b - wrap;
    }
    if (far < near)
    {
        return far;
    }
    return near;
}

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
        ".globl D_8009867C\n.set D_8009867C, D_80098678+4\n"
        ".globl D_80098680\n.set D_80098680, D_80098678+8\n");
