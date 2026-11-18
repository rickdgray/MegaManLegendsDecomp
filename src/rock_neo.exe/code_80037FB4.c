#include "common.h"
#include "code_80037fb4.h"
#include "player.h"

// Small data reached through $gp
sint32 D_80097D28;
sint32 D_80097D2C;
sint32 D_80097D30;
sint32 D_80097D34;
sint32 D_80097D38;
sint32 D_80097D3C;
sint32 D_80097D40;
sint32 D_80097D44;
sint32 D_80097D48;
sint32 D_80097D4C;
sint32 D_80097D50;
sint32 D_80097D54;
sint32 D_80097D6C;
uint32 D_80097D70;
sint32 D_80098668;
sint32 D_8009866C;
sint32 D_80098670;
sint32 D_80098674;
sint32 D_80098678;
sint32 D_8009867C;
sint32 D_80098680;
sint32 D_80098688;
sint32 D_8009868C;
sint32 D_80098690;
sint32 D_80098694;
sint32 D_80098698;
sint16 D_80098660;
sint16 D_80098662;
sint16 D_80098664;

void func_80037FB4(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    sint32 v[3];
    sint32 r;

    *(CAM_VEC *)&D_80098678   = *vec;
    D_800A3958.work.rot_B8.vx = -arg3 & 0xFFF;
    D_80098688                = arg1;
    D_8009868C                = arg2;
    D_80098690                = arg3;
    D_800A3A12                = arg2 & 0xFFF;
    D_800A3A14                = 0;
    RotMatrixYXZ(&D_800A3958.work.rot_B8, CAM_MATRIX_C);
    TransposeMatrix(CAM_MATRIX_C, CAM_MATRIX_E);
    r    = arg1 << CAM_SHIFT;
    v[0] = (-vec->x << CAM_SHIFT) + ((((r * rsin(arg2)) >> 12) * rcos(arg3)) >> 12);
    v[1] = (-vec->y << CAM_SHIFT) + ((r * rsin(arg3)) >> 12);
    v[2] = (-vec->z << CAM_SHIFT) + ((((r * rcos(arg2)) >> 12) * rcos(arg3)) >> 12);
    ApplyMatrixLV(CAM_MATRIX_E, v, CAM_VECTOR_F);
    *CAM_MATRIX_A = *CAM_MATRIX_E;
    v[0]          = ((((arg1 * rsin(arg2)) >> 12) * rcos(arg3)) >> 12) - vec->x;
    v[1]          = ((arg1 * rsin(arg3)) >> 12) - vec->y;
    v[2]          = ((((arg1 * rcos(arg2)) >> 12) * rcos(arg3)) >> 12) - vec->z;
    D_800A3A00    = *(CAM_VEC *)&D_800A39F0;
    CAM_POS_X     = -v[0];
    D_800A39F0    = CAM_POS_X;
    CAM_POS_Y     = -v[1];
    D_800A39F4    = CAM_POS_Y;
    CAM_POS_Z     = -v[2];
    D_800A39F8    = CAM_POS_Z;
    ApplyMatrixLV(CAM_MATRIX_E, v, v);
    CAM_VIEW[0] = v[0];
    CAM_VIEW[1] = v[1];
    CAM_VIEW[2] = v[2];
}

void func_80038324(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39A0 = *vec;
    func_80037FB4(vec, arg1, arg2, arg3);
}

void func_80038370(CAM_VEC *vec, CAM_VEC *target)
{
    sint32 unused[24];
    sint32 dist;
    sint32 sq;
    sint32 yaw;

    D_800A39A0 = *vec;
    sq = (vec->x - target->x) * (vec->x - target->x) + (vec->z - target->z) * (vec->z - target->z);
    dist = SquareRoot0(sq);
    if (dist != 0)
    {
        dist = (sq / dist + dist) >> 1;
    }
    yaw = ratan2(target->x - vec->x, target->z - vec->z) + 0x800;
    func_80037FB4(vec, dist, yaw, -ratan2(target->y - vec->y, dist));
}

void func_800384A4(CAM_VEC *vec, CAM_VEC *target)
{
    D_800A39A0 = *vec;
    func_80038370(vec, target);
}

void func_800384F0(CAM_VEC *pos, sint32 arg1, sint32 arg2)
{
    sint32 v[3];
    sint16 x;
    sint16 y;
    sint16 z;

    D_800A3958.work.rot_B8.vx = -arg2 & 0xFFF;
    D_800A3A12                = arg1 & 0xFFF;
    D_800A3A14                = 0;
    RotMatrixYXZ(&D_800A3958.work.rot_B8, CAM_MATRIX_C);
    TransposeMatrix(CAM_MATRIX_C, CAM_MATRIX_E);
    v[0] = -pos->x;
    v[1] = -pos->y;
    v[2] = -pos->z;
    ApplyMatrixLV(CAM_MATRIX_E, v, CAM_VECTOR_F);
    x                     = -v[0];
    y                     = -v[1];
    z                     = -v[2];
    *(sint16 *)0x1F800028 = x;
    *(sint16 *)0x1F80002A = y;
    *(sint16 *)0x1F80002C = z;
    *CAM_MATRIX_A         = *CAM_MATRIX_E;
    Camera_work.pos_98.x  = x;
    Camera_work.pos_98.y  = y;
    Camera_work.pos_98.z  = z;
}

// The D_8009A55C table has no symbol, so the clear loop indexes D_8009A598 (its last word).
// D_80098698 and D_80097D2C are set first after the loop and D_80097D34 separately: that gives
// retail's early 0x200 load and its store order.
void func_80038648(void)
{
    CAM_SAVE *cw;
    sint32 x;
    sint32 y;
    sint32 z;
    sint32 i;

    cw = &D_800A3958.save;
    func_800177CC(cw, &cw->w[0x38]);
    *(uint8 *)cw = 1;
    x            = Player_work.position.x;
    y            = Player_work.position.y;
    z            = Player_work.position.z;
    D_800A3964 = D_800A397C = D_800A3994 = 0x200;
    D_800A396C = D_800A3984 = D_800A399C = 0x30;
    D_800A39B4                           = 0x96;
    D_800A3959                           = 0;
    D_800A395A                           = 0;
    D_800A395B                           = 0;
    *(uint32 *)&D_800A395C               = 0;
    *(uint32 *)&D_800A3960               = 0;
    D_800A3970                           = 0;
    D_800A3978                           = 0;
    D_800A3974                           = 0;
    D_800A3968 = D_800A3980 = D_800A3998 = 0;
    cw->w[0x38]                          = 0;
    D_800A39F0 = D_800A39A0.x = D_800A39C0.x = D_800A39E0.value = x;
    D_800A39F4 = D_800A39A0.y = D_800A39C4.value = D_800A39E4.value = y;
    D_800A39F8 = D_800A39A0.z = D_800A39C8.value = D_800A39E8.value = z;
    D_800A395D                                                      = 0;
    D_800A395E                                                      = 0;
    D_800A395F                                                      = 0;
    D_800A395C                                                      = 1;
    D_800A3962                                                      = -1;
    D_80098668                                                      = 0;
    D_8009866C                                                      = 0;
    D_80098670                                                      = 0;
    D_80098674                                                      = 0;
    D_80098680                                                      = 0;
    D_8009867C                                                      = 0;
    D_80098678                                                      = 0;
    D_80098690                                                      = 0;
    D_8009868C                                                      = 0;
    D_80098688                                                      = 0;
    D_80098694                                                      = 0;
    D_80097D28                                                      = 0;
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
    func_80037FB4((CAM_VEC *)&cw->w[0x12], cw->w[3], cw->w[4], cw->w[5]);
    func_80039A38(D_80097D58);
    func_800397E8();
}

// Camera update through the cw pointer (retail keeps &D_800A3958 in s0). Retail reuses its
// locals: the case 0 blend weight is blend, case 4's angle difference is rot (computed before
// the cur < want test), and the wrap test keeps value_34 - rot in speed. The abs is a ternary.
void func_80038894(void)
{
    CAM_VEC pos;
    CAM_VEC unused;
    CAM_WORK *cw;
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
    if (D_800A395C != 1)
    {
        func_8001E550();
        D_80098668 = 0;
        return;
    }
    D_80098668++;
    if (D_800A395E != 0)
    {
        func_800392CC();
        D_8009866C = D_800A395E;
        return;
    }
    switch (D_800A395D)
    {
        case 0:
            if (cw->angle_A >= 0)
            {
                if (Scene_work.routine_0 == 0 &&
                    (*(sint32 *)&Player_work.position.x !=
                         *(sint32 *)&Player_work.position_prev.x ||
                     Player_work.position.z != Player_work.position_prev.z))
                {
                    cw->pos_88.x = Player_work.position.x;
                    cw->pos_88.y = Player_work.position.y - cw->vec_58.y;
                    cw->pos_88.z = Player_work.position.z;
                }
                if (cw->angle_A != 0)
                {
                    cw->angle_A += cw->step_9;
                    if (cw->angle_A < 0)
                    {
                        cw->angle_A = 0;
                    }
                    blend         = cw->angle_A;
                    cw->dist_0C   = (cw->dist_24 * blend + cw->dist_3C * (0x40 - blend)) >> 6;
                    cw->height_14 = (cw->height_2C * blend + cw->height_44 * (0x40 - blend)) >> 6;
                    cw->pos_48.y  = (cw->pos_68.y * blend + cw->pos_88.y * (0x40 - blend)) >> 6;
                    if (cw->flag_8 == 3)
                    {
                        cw->rot_10 = Player_work.rotation.y + 0x800;
                    }
                    else
                    {
                        cw->rot_10 = (cw->rot_28 * blend + cw->rot_40 * (0x40 - blend)) >> 6;
                    }
                    cw->pos_48.x = (cw->pos_68.x * blend + cw->pos_88.x * (0x40 - blend)) >> 6;
                    cw->pos_48.z = (cw->pos_68.z * blend + cw->pos_88.z * (0x40 - blend)) >> 6;
                }
                else
                {
                    cw->angle_A   = -1;
                    cw->dist_0C   = cw->dist_3C;
                    cw->height_14 = cw->height_44;
                    cw->pos_48.y  = cw->pos_88.y;
                    if (cw->flag_8 == 3)
                    {
                        cw->rot_10 = Player_work.rotation.y + 0x800;
                    }
                    else
                    {
                        cw->rot_10 = cw->rot_40;
                    }
                    cw->pos_48.x = cw->pos_88.x;
                    cw->pos_48.z = cw->pos_88.z;
                    if (cw->mode_1 == 2)
                    {
                        cw->mode_1 = 0;
                    }
                }
            }
            else if (cw->mode_1 == 0)
            {
                if (cw->flag_8 == 3)
                {
                    cw->rot_10 = Player_work.rotation.y + 0x800;
                }
                else
                {
                    cw->pos_48.x = Player_work.position.x;
                    cw->pos_48.y = Player_work.position.y - cw->vec_58.y;
                    cw->pos_48.z = Player_work.position.z;
                    if (D_80098668 == 1)
                    {
                        cw->rot_10 = Player_work.rotation.y + 0x800;
                    }
                    else
                    {
                        speed      = (Player_work.value_b4 >= 0) ? Player_work.value_b4
                                                                 : -Player_work.value_b4;
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
                            diff = func_8003A218(Player_work.rotation.y + 0x800, cw->rot_10);
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
                        cw->rot_10 =
                            func_8003A154(Player_work.rotation.y + 0x800, D_80097D28, 0x200);
                    }
                    if ((sint8)Player_work.value44d == 1)
                    {
                        D_80098660 = cw->pos_98.x;
                        D_80098662 = cw->pos_98.y;
                        D_80098664 = cw->pos_98.z;
                        if (func_80049C54((PL_SHORT_VECTOR *)&D_80098660,
                                          (PL_SHORT_VECTOR *)&D_80098660, &D_80097D60, 0xFFFF) == 0)
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
                    cw->dist_0C = D_80097D2C;
                }
            }
            break;
        case 1:
            if (D_800C0D92 & 0x400)
            {
                cw->flag_5 = 2;
            }
            break;
        case 2:
            if (D_800C0D92 & 0x400)
            {
                cw->flag_5 = 3;
            }
            if (cw->target_E0 != NULL)
            {
                cw->pos_48.x = cw->target_E0->position.x;
                cw->pos_48.y = cw->target_E0->position.y - cw->vec_58.y;
                cw->pos_48.z = cw->target_E0->position.z;
                cw->rot_10   = cw->target_E0->rotation.y + 0x800;
            }
            break;
        case 3:
            if (D_800C0D92 & 0x400)
            {
                cw->flag_5 = 5;
                goto follow;
            }
            else
            {
                if (cw->target_E0 != NULL)
                {
                    cw->pos_48.x = cw->target_E0->position.x;
                    cw->pos_48.y = cw->target_E0->position.y - cw->vec_58.y;
                    cw->pos_48.z = cw->target_E0->position.z;
                }
            }
            break;
        case 6:
            break;
        case 4:
            cur  = cw->rot_10 & 0xFFF;
            want = (Player_work.rotation.y + 0x800) & 0xFFF;
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
            cw->rot_10 = want;
            func_80039A38(D_80097D5C);
            goto aim;
        turn:
            cw->rot_10 += step;
        aim:
            cw->pos_48.x = Player_work.position.x;
            cw->pos_48.y = Player_work.position.y - cw->vec_58.y;
            cw->pos_48.z = Player_work.position.z;
            break;
        default:
            if (D_800C0D92 & 0x400)
            {
                cw->flag_5 = 0;
            }
        follow:
            cw->pos_48.x = Player_work.position.x;
            cw->pos_48.y = Player_work.position.y - cw->vec_58.y;
            cw->pos_48.z = Player_work.position.z;
            cw->rot_10   = Player_work.rotation.y + 0x800;
            break;
    }
    total = 0x100 - cw->flag_3;
    blend = cw->flag_2;
    rest  = total - blend;
    if (blend != 0)
    {
        rot = cw->rot_10;
        if (rot < cw->value_34)
        {
            speed = cw->value_34 - rot;
            base  = cw->value_34 - 0x1000;
            if (rot - base < speed)
            {
                rot += 0x1000;
            }
        }
        else
        {
            near = rot - cw->value_34;
            wrap = rot - 0x1000;
            if (cw->value_34 - wrap < near)
            {
                rot = wrap;
            }
        }
        pos.x = (cw->vec_78.x * rest + cw->pos_48.x * blend) / total;
        pos.y = (cw->vec_78.y * rest + cw->pos_48.y * blend) / total;
        pos.z = (cw->vec_78.z * rest + cw->pos_48.z * blend) / total;
        func_80037FB4(&pos, (cw->value_30 * rest + cw->dist_0C * blend) / total,
                      (cw->value_34 * rest + rot * blend) / total,
                      (cw->value_38 * rest + cw->height_14 * blend) / total);
        return;
    }
    cw->pos_48.y -= cw->flag_7;
    func_80037FB4(&cw->pos_48, cw->dist_0C, cw->rot_10 + cw->value_1C,
                  cw->height_14 + cw->value_20);
    if (cw->flag_7 != 0)
    {
        if (cw->flag_7 < 10)
        {
            cw->flag_7 = 0;
        }
        else
        {
            cw->flag_7 -= 10;
        }
    }
}

void func_800392CC(void)
{
    CAM_WORK *cw;

    cw                   = &Camera_work;
    Camera_work.pos_48.x = Player_work.position.x;
    Camera_work.pos_48.y = Player_work.position.y - 0xD2;
    Camera_work.pos_48.z = Player_work.position.z;
    Camera_work.rot_10   = Player_work.rotation.y + 0x800;
    if (D_80097D4C != 0)
    {
        if (--D_80097D50 == 0)
        {
            D_80097D4C = 0;
        }
        Camera_work.dist_0C =
            (Camera_work.dist_0C * D_80097D50 + D_80097D54 * (0x10 - D_80097D50)) >> 4;
    }
    else if (D_800C0C2A & 1)
    {
        if (++Camera_work.flag_6 >= 3)
        {
            Camera_work.flag_6 = 1;
        }
        switch (Camera_work.flag_6 - 1)
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
    Camera_work.flag_8 = 1;
    cw->pos_48.y -= cw->flag_7;
    func_80037FB4(&cw->pos_48, cw->dist_0C, cw->rot_10, cw->height_14);
    if (cw->flag_7 != 0)
    {
        if (cw->flag_7 < 10)
        {
            cw->flag_7 = 0;
        }
        else
        {
            cw->flag_7 -= 10;
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
    if (Camera_work.flag_8 != 0)
    {
        Camera_work.angle_A   = 0x40 - (uint8)Camera_work.angle_A;
        Camera_work.dist_24   = Camera_work.dist_0C;
        Camera_work.height_2C = Camera_work.height_14;
        Camera_work.pos_68    = Camera_work.pos_48;
        Camera_work.dist_3C   = 0x200;
        Camera_work.height_44 = 0x30;
        Camera_work.pos_88    = Camera_work.pos_48;
        Camera_work.vec_58.y  = 0x96;
        Camera_work.pos_88.y  = Player_work.position.y - 0x96;
        Camera_work.flag_8    = 0;
        Camera_work.step_9    = -8;
        Camera_work.rot_40    = Camera_work.rot_10;
        Camera_work.rot_28    = Camera_work.rot_10;
    }
    else
    {
        Camera_work.height_14 = 0x30;
        Camera_work.dist_0C   = 0x200;
        Camera_work.angle_A   = 0;
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

void func_80039630(sint32 arg)
{
    if (Camera_work.flag_6 != 0)
    {
        Camera_work.height_14 = arg;
        return;
    }
    if (Camera_work.mode_1 != 0)
    {
        return;
    }
    if (Camera_work.flag_8 == 0)
    {
        Camera_work.angle_A   = 0x40;
        D_80097D2C            = 0x200;
        Camera_work.dist_24   = Camera_work.dist_0C;
        Camera_work.height_2C = Camera_work.height_14;
        Camera_work.pos_68    = Camera_work.pos_48;
        Camera_work.dist_3C   = 0x190;
        Camera_work.height_44 = arg;
        Camera_work.pos_88    = Camera_work.pos_48;
        Camera_work.vec_58.y  = 0xD2;
        Camera_work.pos_88.y  = Player_work.position.y - 0xD2;
        Camera_work.flag_8    = 3;
        Camera_work.step_9    = -8;
        Camera_work.rot_28 = Camera_work.rot_40 = Camera_work.rot_10;
    }
    else if (Camera_work.flag_8 == 3)
    {
        Camera_work.height_14 = arg;
        Camera_work.height_44 = arg;
        if (Camera_work.angle_A <= 0)
        {
            Camera_work.pos_48.x = Player_work.position.x;
            Camera_work.pos_48.y = Player_work.position.y - Camera_work.vec_58.y;
            Camera_work.pos_48.z = Player_work.position.z;
        }
    }
}

void func_800397E8(void)
{
    D_800A396C = 0x30;
    D_800A3964 = D_80097D2C = 0x200;
    D_800A3962              = -1;
    Player_work.value44d    = 0;
}

void func_80039820(void)
{
    sint32 x;
    sint32 y;
    sint32 z;
    sint32 rot;

    x          = Player_work.position.x;
    y          = Player_work.position.y;
    z          = Player_work.position.z;
    rot        = Player_work.rotation.y;
    D_800A396C = 0x30;
    D_800A3964 = D_80097D2C = 0x200;
    D_800A3962              = -1;
    D_800A3959              = 0;
    Player_work.value44d    = 0;
    D_800A39B4              = 0x96;
    D_800A39A0.x = D_800A39C0.x = D_800A39E0.value = x;
    D_800A39A0.y = D_800A39C4.value = D_800A39E4.value = y;
    D_800A39A0.z = D_800A39C8.value = D_800A39E8.value = z;
    D_800A3968                                         = rot + 0x800;
}

void func_800398E0(sint32 arg0)
{
    if (arg0 > 0)
    {
        D_800A395F = arg0;
    }
}

void Swing_Camera2(sint32 arg0, uint32 arg1, uint32 arg2, CAM_DELTA *pos)
{
    sint32 d[3];
    uint32 dist;

    if (arg0 > 0)
    {
        d[0] = *(sint16 *)0x1F800028 - pos->x;
        d[1] = *(sint16 *)0x1F80002A - pos->y;
        d[2] = *(sint16 *)0x1F80002C - pos->z;
        dist = SquareRoot0(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (arg2 >= dist)
        {
            if (dist < arg1)
            {
                d[2] = arg1;
            }
            D_800A395F = (arg2 - dist) * arg0 / (arg2 - arg1);
        }
    }
}

sint32 func_800399EC(uint32 *cmd)
{
    uint32 n;

    n = D_80097D70;
    if (n >= 8)
    {
        return 0;
    }
    D_80097D70                       = n + 1;
    D_8009869C[(D_80097D6C + n) & 7] = cmd;
    return 1;
}

void func_80039A38(void *data)
{
    D_80097D6C = 0;
    D_80097D70 = 0;
    func_800399EC(data);
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
                D_800A395D = 0;
                break;
            case 3:
                D_8009A478 = D_800A3958.save;
                D_800A395D = 6;
                break;
            case 4:
                D_800A3958.save = D_8009A478;
                // fall through
            case 2:
                D_800A395D = 4;
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

void func_80039BA4(uint8 arg0, uint8 arg1)
{
    D_800A395A = arg0;
    D_800A395B = arg1;
}

void func_80039BBC(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39A0 = *vec;
    D_800A3964 = arg1;
    D_800A3968 = arg2;
    D_800A396C = arg3;
}

void func_80039C08(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39D0 = *vec;
    D_800A3988 = arg1;
    D_800A398C = arg2;
    D_800A3990 = arg3;
}

void func_80039C54(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39C0 = *vec;
    D_800A397C = arg1;
    D_800A3980 = arg2;
    D_800A3984 = arg3;
}

void func_80039CA0(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    D_800A39B0 = *vec;
    D_800A3970 = arg1;
    D_800A3974 = arg2;
    D_800A3978 = arg3;
}

void func_80039CEC(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    *(CAM_VEC *)&D_800A39E0 = *vec;
    D_800A3994              = arg1;
    D_800A3998              = arg2;
    D_800A399C              = arg3;
}

void func_80039D38(CAM_DELTA *delta)
{
    D_800A39C0.x += delta->x;
    D_800A39C4.value += delta->y;
    D_800A39C8.value += delta->z;
    D_800A39E0.value += delta->x;
    D_800A39E4.value += delta->y;
    D_800A39E8.value += delta->z;
}

void func_80039DE8(void)
{
    D_80097D2C           = 0x200;
    Player_work.value44d = 0;
    Scene_work.routine_1 = D_80098674;
    Scene_work.routine_0 = D_80098670;
}

void func_80039E18(void)
{
    Scene_work.routine_1 = D_80098674;
    Scene_work.routine_0 = D_80098670;
    func_80039E50();
}

// D_80097D2C and dist_3C get 0x200 in separate statements, with the vec_58.y store between
// them; the chained form schedules the dist_0C load first. The x + 0x1000 - y wrap form fixes
// the dir/near registers (as func_80039FFC).
void func_80039E50(void)
{
    sint32 base;
    sint32 dir;
    sint32 rot;

    Camera_work.mode_1    = 2;
    Camera_work.angle_A   = 0x40;
    Camera_work.pos_68    = Camera_work.pos_48;
    D_80097D2C            = 0x200;
    Camera_work.vec_58.y  = 0x96;
    Camera_work.dist_3C   = 0x200;
    Camera_work.height_44 = 0x30;
    Camera_work.step_9    = -4;
    Camera_work.dist_24   = Camera_work.dist_0C;
    base                  = Camera_work.rot_10 & 0xFFF;
    Camera_work.pos_88.x  = Player_work.position.x;
    Player_work.value44d  = 0;
    Camera_work.rot_28    = base;
    Camera_work.height_2C = Camera_work.height_14;
    Camera_work.pos_88.y  = Player_work.position.y - 0x96;
    Camera_work.pos_88.z  = Player_work.position.z;
    rot                   = Player_work.rotation.y + 0x800;
    Camera_work.rot_40 = dir = rot & 0xFFF;
    if (dir < base)
    {
        if (base - dir > dir + 0x1000 - base)
        {
            Camera_work.rot_40 = dir + 0x1000;
        }
    }
    else
    {
        if (dir - base > base + 0x1000 - dir)
        {
            Camera_work.rot_28 = base + 0x1000;
        }
    }
}

void func_80039FAC(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    sint32 saved1;
    sint32 saved0;

    saved1               = Scene_work.routine_1;
    Scene_work.routine_1 = 0xFF;
    saved0               = Scene_work.routine_0;
    Scene_work.routine_0 = 1;
    D_80098674           = saved1;
    D_80098670           = saved0;
    func_80039FFC(vec, arg1, arg2, arg3);
}

// The wrap distance is written x + 0x1000 - y so the near distance is computed first.
void func_80039FFC(CAM_VEC *vec, sint32 arg1, sint32 arg2, sint32 arg3)
{
    sint32 base;

    Camera_work.mode_1  = 1;
    Camera_work.angle_A = 0x40;
    Camera_work.pos_68  = Camera_work.pos_48;
    Camera_work.dist_24 = Camera_work.dist_0C;
    D_80097D2C          = 0x200;
    arg2 &= 0xFFF;
    Player_work.value44d  = 0;
    Camera_work.rot_28    = Camera_work.rot_10 & 0xFFF;
    Camera_work.height_2C = Camera_work.height_14;
    Camera_work.pos_88    = *vec;
    Camera_work.dist_3C   = arg1;
    Camera_work.rot_40    = arg2;
    Camera_work.height_44 = arg3;
    Camera_work.step_9    = -4;
    base                  = Camera_work.rot_28;
    if (arg2 < base)
    {
        if (base - arg2 > arg2 + 0x1000 - base)
        {
            Camera_work.rot_40 = arg2 + 0x1000;
        }
    }
    else
    {
        if (arg2 - base > base + 0x1000 - arg2)
        {
            Camera_work.rot_28 = base + 0x1000;
        }
    }
}

sint32 func_8003A13C(void)
{
    return D_800A3962 >= 0;
}

sint32 func_8003A154(sint32 arg0, sint32 arg1, sint32 arg2)
{
    sint32 b;
    sint32 near;
    sint32 far;
    sint32 wrap;
    sint32 wrap2;
    sint32 v;
    sint32 lim;

    arg0 &= 0xFFF;
    b = D_800A3968 & 0xFFF;
    if (arg0 < b)
    {
        near  = b - arg0;
        wrap2 = b - 0x1000;
        far   = arg0 - wrap2;
        if (far < near)
        {
            if (arg2 < far)
            {
                return arg0 - arg2;
            }
            v = b + arg1;
            if (arg0 + 0x1000 < v)
            {
                return arg0;
            }
            return v;
        }
        if (arg2 < near)
        {
            return arg0 + arg2;
        }
        v = b - arg1;
        if (v < arg0)
        {
            return arg0;
        }
        return v;
    }
    near = arg0 - b;
    wrap = arg0 - 0x1000;
    far  = b - wrap;
    if (far < near)
    {
        if (arg2 < far)
        {
            return arg0 + arg2;
        }
        v = b - arg1;
        if (v < wrap)
        {
            return arg0;
        }
        return v;
    }
    if (arg2 < near)
    {
        return arg0 - arg2;
    }
    v   = arg0;
    lim = b + arg1;
    if (v < lim)
    {
        return v;
    }
    return lim;
}

sint32 func_8003A218(sint32 arg0)
{
    sint32 b;
    sint32 near;
    sint32 far;
    sint32 wrap;

    arg0 &= 0xFFF;
    b = D_800A3968 & 0xFFF;
    if (arg0 < b)
    {
        near = b - arg0;
        wrap = b - 0x1000;
        far  = arg0 - wrap;
    }
    else
    {
        near = arg0 - b;
        wrap = arg0 - 0x1000;
        far  = b - wrap;
    }
    if (far < near)
    {
        return far;
    }
    return near;
}

// Twin of func_80039E50.
void func_8003A264(void)
{
    sint32 base;
    sint32 dir;

    Camera_work.mode_1    = 2;
    Camera_work.angle_A   = 0x40;
    Camera_work.pos_68    = *(CAM_VEC *)&D_80098678;
    D_80097D2C            = 0x200;
    Camera_work.vec_58.y  = 0x96;
    Camera_work.dist_3C   = 0x200;
    Camera_work.height_44 = 0x30;
    Camera_work.step_9    = -4;
    Camera_work.dist_24   = D_80098688;
    base                  = D_8009868C & 0xFFF;
    Camera_work.pos_88.x  = Player_work.position.x;
    Player_work.value44d  = 0;
    Camera_work.rot_28    = base;
    Camera_work.height_2C = D_80098690;
    Camera_work.pos_88.y  = Player_work.position.y - 0x96;
    Camera_work.pos_88.z  = Player_work.position.z;
    Camera_work.rot_40 = dir = (Player_work.rotation.y + 0x800) & 0xFFF;
    if (dir < base)
    {
        if (base - dir > dir + 0x1000 - base)
        {
            Camera_work.rot_40 = dir + 0x1000;
        }
    }
    else
    {
        if (dir - base > base + 0x1000 - dir)
        {
            Camera_work.rot_28 = base + 0x1000;
        }
    }
}
