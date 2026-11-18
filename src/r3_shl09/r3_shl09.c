#include "common.h"
#include "shl09.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
// type_3 selects the object: 0 the beam, 1 the orbiting shot, 2 its spark.
void func_800D8804(SHL_WORK *wp)
{
    wp->type_3 &= 0x7F;
    D_800D9730[wp->type_3](wp);
}

void func_800D8848(SHL_WORK *wp)
{
    D_800D973C[wp->routine_0](wp);
}

void func_800D8884(SHL_WORK *wp)
{
    wp->box_78 = &D_800D96F8;
    wp->col_bc = 0;
    wp->col_c0 = 0;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    func_800354E0(wp->bit_d);
    func_800D9570(wp);
    wp->old_fpos          = wp->fpos;
    wp->old_pos           = wp->pos;
    wp->draw.mdl.color_b4 = 0x02808080;
    func_8002F9C4(wp, &wp->type_3);
    func_800D8F50(wp);
    Sound_call2(0x12E, &wp->pos);
    wp->value_f   = 0xD;
    wp->value_e   = 0;
    wp->routine_0 = 1;
}

void func_800D896C(SHL_WORK *wp)
{
    if (--wp->value_f == 0)
    {
        func_80031930(wp);
        return;
    }
    if (wp->value_f == 9)
    {
        if (Player_work.value_53e)
        {
            func_800D942C(wp);
        }
        func_800D947C(wp);
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    func_800D9570(wp);
    func_800D8F50(wp);
    if (wp->value_f >= 8 && wp->value_f <= 10)
    {
        func_800D922C(wp);
    }
}

void func_800D8A5C(SHL_WORK *wp)
{
    D_800D9744[wp->routine_0](wp);
}

void func_800D8A98(SHL_WORK *wp)
{
    SVECTOR rot;
    VECTOR v;

    wp->box_78 = &D_800D96F8;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    rot.vx = wp->rot.vx = func_80039B80();
    rot.vy = wp->rot.vy = Player_work.rot.vy;
    rot.vz = wp->rot.vz = 0x680;
    RotMatrixYXZ(&rot, &wp->draw.mdl.mtx_8c);
    v.vx = v.vy = v.vz = 0x200;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    func_800D9608(&wp->vel, 0x32);
    wp->pos               = Player_work.pos_3c8;
    wp->draw.mdl.pos      = wp->pos;
    wp->fpos.w.x          = wp->pos.vx << 16;
    wp->fpos.w.y          = wp->pos.vy << 16;
    wp->fpos.w.z          = wp->pos.vz << 16;
    wp->old_fpos          = wp->fpos;
    wp->old_pos           = wp->pos;
    wp->draw.mdl.color_b4 = 0x02808080;
    func_8002F9C4(wp, &wp->type_3);
    func_800D9398(wp);
    wp->value_e   = 4;
    wp->value_f   = func_80037634(&Player_work, 9) / 50;
    wp->routine_0 = 1;
}

void func_800D8C64(SHL_WORK *wp)
{
    if (--wp->value_f == 0)
    {
        wp->routine_0 = 2;
        return;
    }
    if (func_80037694(wp, 0))
    {
        wp->routine_0 = 2;
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    wp->fpos.w.x += wp->vel.vx << 8;
    wp->fpos.w.y += wp->vel.vy << 8;
    wp->fpos.w.z += wp->vel.vz << 8;
    wp->draw.mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
    wp->draw.mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
    wp->draw.mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    func_800D9398(wp);
}

void func_800D8D68(SHL_WORK *wp)
{
    SVECTOR rot;
    VECTOR v;

    wp->draw.mdl.color_b4 = SHL_RGB(2, wp->value_e << 5, wp->value_e << 5, wp->value_e << 5);
    rot.vx                = wp->rot.vx;
    rot.vy                = wp->rot.vy;
    rot.vz                = wp->rot.vz;
    RotMatrixYXZ(&rot, &wp->draw.mdl.mtx_8c);
    v.vx = v.vy = 0x200;
    v.vz        = (wp->value_e << 4) + 0x100;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    if (--wp->value_e == 0)
    {
        func_80031930(wp);
    }
}

void func_800D8E2C(SHL_WORK *wp)
{
    D_800D9750[wp->routine_0](wp);
}

void func_800D8E68(SHL_WORK *wp)
{
    wp->routine_0         = 1;
    wp->bit_d             = 0;
    wp->draw.spr.code_88  = 0x3D48002C;
    wp->draw.spr.color_8c = 0x2E808080;
    wp->flags_0 |= 0x22;
    wp->draw.spr.scale_96 = D_800D9724[wp->bit_d].scale_96;
    wp->draw.spr.scale_97 = D_800D9724[wp->bit_d].scale_97;
    wp->draw.spr.size_98  = 0x60;
    wp->draw.spr.value_9a = 0xB;
}

void func_800D8EDC(SHL_WORK *wp)
{
    wp->bit_d++;
    wp->draw.spr.scale_96 = D_800D9724[wp->bit_d].scale_96;
    wp->draw.spr.scale_97 = D_800D9724[wp->bit_d].scale_97;
    if (wp->bit_d >= 6)
    {
        func_80031930(wp);
    }
}

void func_800D8F50(SHL_WORK *wp)
{
    MATRIX m;
    SVECTOR dir;
    SVECTOR p;
    VECTOR v;
    sint32 level;
    sint32 flags;

    level = Player_work.value_53c;
    flags = func_800375D4(&Player_work, 9);
    m     = Player_work.mtx_248;
    p     = Player_work.pos_3c8;
    // Identity, written a word at a time.
    *(uint32 *)&wp->draw.mdl.mtx_8c.m[0][0] = 0x1000;
    *(uint32 *)&wp->draw.mdl.mtx_8c.m[0][2] = 0;
    *(uint32 *)&wp->draw.mdl.mtx_8c.m[1][1] = 0x1000;
    *(uint32 *)&wp->draw.mdl.mtx_8c.m[2][0] = 0;
    *(uint32 *)&wp->draw.mdl.mtx_8c.m[2][2] = 0x1000;
    wp->draw.mdl.mtx_8c.t[0]                = 0;
    wp->draw.mdl.mtx_8c.t[1]                = 0;
    wp->draw.mdl.mtx_8c.t[2]                = 0;
    v.vx = v.vy = v.vz = 0x1000;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    MulMatrix2(&m, &wp->draw.mdl.mtx_8c);
    dir.vx = 0;
    dir.vy = 0x1000;
    dir.vz = 0;
    ApplyMatrix(&wp->draw.mdl.mtx_8c, &dir, &v);
    dir.vx = (v.vx * 80) >> 4;
    dir.vy = (v.vy * 80) >> 4;
    dir.vz = (v.vz * 80) >> 4;
    v.vx   = (p.vx << 16) + (dir.vx << 8) * D_800D9758[level];
    v.vy   = (p.vy << 16) + (dir.vy << 8) * D_800D9758[level];
    v.vz   = (p.vz << 16) + (dir.vz << 8) * D_800D9758[level];
    dir.vx = v.vx >> 16;
    dir.vy = v.vy >> 16;
    dir.vz = v.vz >> 16;
    v.vx   = D_800D9798[level].width + 0x1000;
    v.vz   = D_800D9798[level].width + 0x1000;
    v.vy   = D_800D9798[level].len + 0x1000;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    func_8003430C(&dir, D_800D9778[level], &wp->pos, D_800D9778[level], 0x200, 0x4000, wp->value_1,
                  &wp->col_bc, flags | 0x28000000, 0, 0x80);
    wp->col_bc = 0;
    wp->col_c0 = 0;
}

void func_800D922C(SHL_WORK *wp)
{
    SVECTOR d;
    SVECTOR a;
    SVECTOR b;
    SHL_FIXED f;
    sint32 size;
    sint32 flags;

    f = Player_work.fpos;
    f.w.y -= 0x500000;
    size  = D_800D97D8[Player_work.value_53c];
    flags = func_800375D4(&Player_work, 9);
    func_800D9608(&d, 0x3C);
    a.vx = (f.w.x + (d.vx << 9)) >> 16;
    a.vy = (f.w.y + (d.vy << 9)) >> 16;
    a.vz = (f.w.z + (d.vz << 9)) >> 16;
    b.vx = (f.w.x + (d.vx << 8)) >> 16;
    b.vy = (f.w.y + (d.vy << 8)) >> 16;
    b.vz = (f.w.z + (d.vz << 8)) >> 16;
    func_8003430C(&a, size, &b, size, 0x200, 0x4000, wp->value_1, &wp->col_c4, flags | 0x28000000,
                  0, 0x80);
    wp->col_c4 = 0;
    wp->col_c8 = 0;
}

// The level goes through a sint8 local: retail loads it with lbu and sign-extends it in a
// register (sll 24/sra 22); indexing with the field directly gives lb.
void func_800D9398(SHL_WORK *wp)
{
    sint8 level;

    level = Player_work.value_53c;
    func_8003430C(&wp->pos, 8, &wp->old_pos, 0x5C, 0x200, 0x4000, wp->value_1, &wp->col_c4,
                  D_800D9704[level] | 0x8000000, 0, 0x80);
    wp->col_c4 = 0;
    wp->col_c8 = 0;
}

void func_800D942C(SHL_WORK *wp)
{
    SHL_WORK *np;

    np = func_80031598();
    if (np)
    {
        np->flags_0 = 1;
        np->value_2 = wp->value_2;
        np->type_3  = 1;
        np->index_c = wp->value_1;
    }
}

void func_800D947C(SHL_WORK *wp)
{
    SVECTOR d;
    SVECTOR p;
    VECTOR v;
    SHL_WORK *np;

    p = Player_work.pos_3a8;
    func_800D9608(&d, 100);
    v.vx = (p.vx << 16) + (d.vx << 8);
    v.vy = (p.vy << 16) + (d.vy << 8);
    v.vz = (p.vz << 16) + (d.vz << 8);
    np   = func_80031598();
    if (np)
    {
        np->flags_0       = 1;
        np->value_2       = wp->value_2;
        np->type_3        = 2;
        np->index_c       = wp->value_1;
        np->draw.spr.x_90 = v.vx >> 16;
        np->draw.spr.y_92 = v.vy >> 16;
        np->draw.spr.z_94 = v.vz >> 16;
    }
}

void func_800D9570(SHL_WORK *wp)
{
    SVECTOR p;

    p                   = Player_work.pos_3c8;
    wp->fpos.w.x        = p.vx << 16;
    wp->fpos.w.y        = p.vy << 16;
    wp->fpos.w.z        = p.vz << 16;
    wp->draw.mdl.pos.vx = wp->pos.vx = p.vx;
    wp->draw.mdl.pos.vy = wp->pos.vy = p.vy;
    wp->draw.mdl.pos.vz = wp->pos.vz = p.vz;
}

void func_800D9608(SVECTOR *out, sint32 speed)
{
    MATRIX m;
    SVECTOR rot;
    VECTOR v;

    rot.vx = func_80039B80();
    rot.vy = Player_work.rot.vy;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &m);
    v.vx = v.vy = v.vz = 0x1000;
    ScaleMatrix(&m, &v);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&m, &rot, &v);
    out->vx = (v.vx * speed) >> 4;
    out->vy = (v.vy * speed) >> 4;
    out->vz = (v.vz * speed) >> 4;
}
