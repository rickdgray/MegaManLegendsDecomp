#include "common.h"
#include "shl03.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D8E34[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_800D8854(SHL_WORK *wp)
{
    SVECTOR dir;
    SVECTOR rot;
    VECTOR v;
    MATRIX m;

    wp->flags_0 |= 2;
    wp->flags_6 |= 0x20;
    func_800354E0(wp->bit_d);
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = &D_800D8E18;
    rot.vx     = func_80039B80();
    rot.vy     = wp->rot_y & 0xFFF;
    rot.vz     = 0;
    RotMatrixYXZ(&rot, &m);
    dir.vx = 0;
    dir.vy = 0;
    dir.vz = -0x1000;
    ApplyMatrix(&m, &dir, &v);
    dir.vx                = v.vx;
    dir.vy                = v.vy;
    dir.vz                = v.vz;
    wp->vel.vx            = 0;
    wp->vel.vy            = 0;
    wp->vel.vz            = 0;
    wp->draw.spr.pos_a4   = dir;
    wp->ax                = dir.vx / 2;
    wp->ay                = dir.vy / 2;
    wp->az                = dir.vz / 2;
    wp->draw.spr.code_88  = 0x3D08000E;
    wp->draw.spr.color_8c = 0x2C808080;
    wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
    wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
    wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                   = wp->fpos;
    wp->old_pos                    = wp->pos;
    wp->draw.spr.scale_96          = 0x80;
    wp->draw.spr.scale_97          = 0x80;
    wp->draw.spr.size_98           = D_800D8E24[Player_work.value_50c];
    wp->hit_7c                     = 0;
    wp->timer_b                    = 0;
    wp->routine_1                  = 0;
    wp->routine_0++;
    if (wp->mode_a)
    {
        wp->old_pos.pad = wp->pos.pad = 0x6208;
    }
    else
    {
        wp->old_pos.pad = wp->pos.pad = 0x4208;
    }
    func_800D8D5C(wp);
    Sound_call2(0x122, &wp->pos);
}

void func_800D8A7C(SHL_WORK *wp)
{
    MATRIX unused;

    if (func_80037694(wp, 0x20) || wp->hit_7c)
    {
        func_800D8C6C(wp);
        Swing_Camera2(0x14, 0x64, 0xFA0, &wp->pos);
        func_80031930(wp);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    if (wp->timer_b < 15)
    {
        wp->vel.vx += wp->ax;
        wp->vel.vy += wp->ay;
        wp->vel.vz += wp->az;
    }
    if (wp->timer_b++ < func_80037634(&Player_work, 3))
    {
        if (wp->timer_b & 1)
        {
            wp->draw.spr.scale_96 = 0xA0;
            wp->draw.spr.scale_97 = 0x60;
        }
        else
        {
            wp->draw.spr.scale_96 = 0x80;
            wp->draw.spr.scale_97 = 0x80;
        }
        wp->fpos.w.x += wp->vel.vx << 8;
        wp->fpos.w.y += wp->vel.vy << 8;
        wp->fpos.w.z += wp->vel.vz << 8;
        wp->draw.spr.color_8c = 0x2C808080;
        wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
        wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
        wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    }
    else
    {
        func_80031930(wp);
        return;
    }
    func_800D8D5C(wp);
    if (wp->timer_b & 1)
    {
        func_800D8CF4(wp);
    }
}

void func_800D8C6C(SHL_WORK *wp)
{
    SHL_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->routine_0 = 5;
        fx->kind_2    = 0x80;
        fx->flag_3    = 2;
        fx->value_d   = D_800D8E2C[Player_work.value_50c];
        fx->value_e   = 1;
        fx->pos_38    = wp->pos;
    }
}

void func_800D8CF4(SHL_WORK *wp)
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

void func_800D8D5C(SHL_WORK *wp)
{
    sint32 size;
    sint32 flags;

    size  = wp->draw.spr.size_98;
    flags = func_800375D4(&Player_work, 3);
    if (wp->index_c)
    {
        func_8003430C(&wp->pos, size, &wp->old_pos, size, 0x200, 0x6000, wp->value_1, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&wp->pos, size, &wp->old_pos, size, 0x200, 0x4000, wp->value_1, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    }
}
