#include "common.h"
#include "shl06.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D90CC[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_800D8854(SHL_WORK *wp)
{
    SVECTOR dir;
    SVECTOR rot;
    VECTOR v;
    MATRIX m;
    SHL_WORK *np;

    func_800354E0(wp->bit_d);
    rot.vx = func_80039B80();
    func_800D8E44(wp, rot.vx, wp->rot_y);
    np = func_80031598();
    if (np)
    {
        func_800D8DD8(wp, np);
        func_800D8E44(np, rot.vx, wp->rot_y + 0x80 + (rand() & 0x1F));
    }
    np = func_80031598();
    if (np)
    {
        func_800D8DD8(wp, np);
        func_800D8E44(np, rot.vx, wp->rot_y - 0x80 + (rand() & 0x1F));
    }
    if (Player_work.value_528 > 0)
    {
        np = func_80031598();
        if (np)
        {
            func_800D8DD8(wp, np);
            func_800D8E44(np, rot.vx, wp->rot_y + 0x100 + (rand() & 0x1F));
        }
        np = func_80031598();
        if (np)
        {
            func_800D8DD8(wp, np);
            func_800D8E44(np, rot.vx, wp->rot_y - 0x100 + (rand() & 0x1F));
        }
        if (Player_work.value_528 >= 2)
        {
            np = func_80031598();
            if (np)
            {
                func_800D8DD8(wp, np);
                func_800D8E44(np, rot.vx, wp->rot_y + 0x180 + (rand() & 0x1F));
            }
            np = func_80031598();
            if (np)
            {
                func_800D8DD8(wp, np);
                func_800D8E44(np, rot.vx, wp->rot_y - 0x180 + (rand() & 0x1F));
            }
        }
    }
    Sound_call2(0x12A, &wp->pos);
}

void func_800D8A6C(SHL_WORK *wp)
{
    MATRIX unused;

    if (func_80037694(wp, 0x20) || wp->hit_7c)
    {
        func_800D8C2C(wp);
        func_80031930(wp);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    wp->hit_7c   = 0;
    wp->vel.vx += wp->ax;
    wp->vel.vy += wp->ay;
    wp->vel.vz += wp->az;
    if (wp->timer_b++ >= 90)
    {
        func_80031930(wp);
        return;
    }
    wp->fpos.w.x += wp->vel.vx << 8;
    wp->fpos.w.y += wp->vel.vy << 8;
    wp->fpos.w.z += wp->vel.vz << 8;
    wp->draw.spr.color_8c = 0x2C808080;
    wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
    wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
    wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    func_800D8D28(wp);
    if (++wp->routine_1 >= 6)
    {
        wp->routine_1 = 0;
    }
    wp->draw.spr.scale_96 = D_800D909C[wp->routine_1].scale_96;
    wp->draw.spr.scale_97 = D_800D909C[wp->routine_1].scale_97;
}

void func_800D8C2C(SHL_WORK *wp)
{
    SHL_FX *fx;
    sint32 level;

    fx = func_80031618();
    if (fx)
    {
        fx->routine_0 = 5;
        fx->kind_2    = 0x80;
        fx->flag_3    = 2;
        level         = Player_work.value_524;
        if (level >= 3)
        {
            level = 2;
        }
        fx->value_d = level;
        fx->value_e = 1;
        fx->pos_38  = wp->pos;
    }
}

void func_800D8CB8(SHL_WORK *wp, MATRIX *m)
{
}

void func_800D8CC0(SHL_WORK *wp)
{
    SHL_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->routine_0 = 1;
        fx->kind_2    = 0x83;
        fx->flag_3    = 1;
        fx->x_1c      = wp->pos.vx;
        fx->y_1e      = wp->pos.vy;
        fx->z_20      = wp->pos.vz;
    }
}

void func_800D8D28(SHL_WORK *wp)
{
    sint32 flags;

    flags = func_800375D4(&Player_work, 6);
    if (wp->index_c)
    {
        func_8003430C(&wp->pos, 0x20, &wp->old_pos, 0x20, 0x200, 0x6000, wp->value_1, &wp->col_c4,
                      flags | 0x88000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&wp->pos, 0x20, &wp->old_pos, 0x20, 0x200, 0x4000, wp->value_1, &wp->col_c4,
                      flags | 0x88000000, 0, 0x80);
    }
}

void func_800D8DD8(SHL_WORK *wp, SHL_WORK *np)
{
    np->flags_0 = 1;
    np->value_2 = wp->value_2;
    np->index_c = wp->index_c;
    np->pos     = wp->pos;
    np->fpos    = wp->fpos;
    np->rot_y   = wp->rot_y;
}

void func_800D8E44(SHL_WORK *wp, sint32 rx, sint32 ry)
{
    SVECTOR dir;
    SVECTOR rot;
    VECTOR v;
    MATRIX m;
    sint32 speed;

    wp->box_78 = &D_800D9090;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->flags_0 |= 2;
    wp->flags_6 |= 0x20;
    rot.vx = rx - 0x10 - (rand() & 0xF);
    rot.vy = ry & 0xFFF;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &m);
    dir.vx = 0;
    dir.vy = 0;
    dir.vz = -0x1000;
    ApplyMatrix(&m, &dir, &v);
    dir.vx                = v.vx;
    dir.vy                = v.vy;
    dir.vz                = v.vz;
    speed                 = func_80037634(&Player_work, 6) + (rand() & 0x1F);
    wp->vel.vx            = (uint32)(dir.vx * speed) >> 4;
    wp->vel.vy            = (uint32)(dir.vy * speed) >> 4;
    wp->vel.vz            = (uint32)(dir.vz * speed) >> 4;
    wp->draw.spr.pos_a4   = dir;
    wp->ax                = 0;
    wp->ay                = 0x200;
    wp->az                = 0;
    wp->draw.spr.code_88  = 0x3D48000E;
    wp->draw.spr.color_8c = 0x2C808080;
    wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
    wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
    wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                   = wp->fpos;
    wp->old_pos                    = wp->pos;
    wp->draw.spr.scale_96          = D_800D909C[0].scale_96;
    wp->draw.spr.scale_97          = D_800D909C[0].scale_97;
    wp->draw.spr.size_98           = 0x18;
    wp->timer_b                    = 0;
    func_800D8CB8(wp, &m);
    wp->routine_1 = 0;
    wp->routine_0++;
    if (wp->mode_a)
    {
        wp->old_pos.pad = wp->pos.pad = 0x6208;
    }
    else
    {
        wp->old_pos.pad = wp->pos.pad = 0x4208;
    }
    func_800D8D28(wp);
}
