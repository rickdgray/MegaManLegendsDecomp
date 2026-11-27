#include "common.h"
#include "shl0a.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D8F50[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_800D8854(SHL_WORK *wp)
{
    SVECTOR rot;
    VECTOR v;
    MATRIX m;
    sint32 speed;

    wp->be_flag |= 0xA;
    wp->flags |= 0x20;
    func_800354E0(wp->bit_d);
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = &D_800D8F04;
    rot.vx     = func_80039B80() - 0x80;
    rot.vy     = wp->rot_y & 0xFFF;
    rot.vz     = 0;
    RotMatrixYXZ(&rot, &m);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&m, &rot, &v);
    rot.vx                = v.vx;
    rot.vy                = v.vy;
    rot.vz                = v.vz;
    speed                 = func_80037634(&Player_work, 0xA);
    wp->vel.vx            = (rot.vx * speed) >> 4;
    wp->vel.vy            = (rot.vy * speed) >> 4;
    wp->vel.vz            = (rot.vz * speed) >> 4;
    wp->draw.spr.pos_a4   = rot;
    wp->ax                = 0;
    wp->ay                = 0x200;
    wp->az                = 0;
    wp->draw.spr.code_88  = D_800D8F20[Player_work.value_544];
    wp->draw.spr.color_8c = 0x2C808080;
    wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
    wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
    wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                   = wp->fpos;
    wp->old_pos                    = wp->pos;
    wp->draw.spr.scale_96          = 0;
    wp->draw.spr.scale_97          = 0;
    wp->draw.spr.size_98           = D_800D8F10[Player_work.value_544];
    wp->hit_7c                     = 0;
    wp->timer_b                    = 0;
    wp->routine_1                  = 0;
    wp->routine_0++;
    func_800D8E48(wp);
    Sound_call2(0x12F, &wp->pos);
}

// The identical arms (merged by jump2) test `hit` again, so it stays live past the first test and
// combine can't fold its copy into the branch: retail's move v1,v0.
void func_800D8A88(SHL_WORK *wp)
{
    MATRIX unused;
    sint32 i;
    sint32 hit;

    hit = func_80037694(wp, 0x40);
    if (hit || wp->hit_7c)
    {
        if (wp->hit_7c || hit)
        {
            func_800D8BE8(wp);
            Sound_call2(0x130, &wp->pos);
            Close_PL_SHL_WORK(wp);
            return;
        }
        else
        {
            func_800D8BE8(wp);
            Sound_call2(0x130, &wp->pos);
            Close_PL_SHL_WORK(wp);
            return;
        }
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    wp->vel.vy += wp->ay;
    wp->fpos.w.x += wp->vel.vx << 8;
    wp->fpos.w.y += wp->vel.vy << 8;
    wp->fpos.w.z += wp->vel.vz << 8;
    wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
    wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
    wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    i                              = ++wp->timer_b & 7;
    wp->draw.spr.scale_96          = D_800D8F40[i].scale_96;
    wp->draw.spr.scale_97          = D_800D8F40[i].scale_97;
    func_800D8E48(wp);
}

void func_800D8BE8(SHL_WORK *wp)
{
    SHL_FX *fx;
    sint32 i;

    if (Player_work.value_544 == 0)
    {
        fx = func_80031618();
        if (fx)
        {
            fx->be_flag = 5;
            fx->id      = 0x80;
            fx->flag_3  = 2;
            fx->value_d = 1;
            fx->value_e = 1;
            fx->pos_38  = wp->pos;
        }
        for (i = 0; i < 4; i++)
        {
            fx = func_80031618();
            if (fx)
            {
                fx->be_flag   = 5;
                fx->id        = 0x80;
                fx->flag_3    = 2;
                fx->value_d   = 0;
                fx->value_e   = 1;
                fx->pos_38.vx = wp->pos.vx + ((rcos(i << 10) * 150) >> 12);
                fx->pos_38.vz = wp->pos.vz + ((rsin(i << 10) * 150) >> 12);
                fx->pos_38.vy = wp->pos.vy;
            }
        }
    }
    else
    {
        fx = func_80031618();
        if (fx)
        {
            fx->be_flag = 5;
            fx->id      = 0x80;
            fx->flag_3  = 2;
            fx->value_d = 2;
            fx->value_e = 1;
            fx->pos_38  = wp->pos;
        }
        for (i = 0; i < 8; i++)
        {
            fx = func_80031618();
            if (fx)
            {
                fx->be_flag   = 5;
                fx->id        = 0x80;
                fx->flag_3    = 2;
                fx->value_d   = 1;
                fx->value_e   = 1;
                fx->pos_38.vx = wp->pos.vx + ((rcos(i << 9) * 250) >> 12);
                fx->pos_38.vz = wp->pos.vz + ((rsin(i << 9) * 250) >> 12);
                fx->pos_38.vy = wp->pos.vy;
            }
        }
    }
}

void func_800D8E48(SHL_WORK *wp)
{
    sint32 size;
    sint32 flags;

    size  = wp->draw.spr.size_98;
    flags = func_800375D4(&Player_work, 1);
    if (wp->index_c)
    {
        func_8003430C(&wp->pos, size, &wp->old_pos, size, 0x200, 0x6000, wp->slot, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&wp->pos, size, &wp->old_pos, size, 0x200, 0x4000, wp->slot, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    }
}
