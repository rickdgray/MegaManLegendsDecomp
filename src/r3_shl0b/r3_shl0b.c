#include "common.h"
#include "shl0b.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D8F88[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_800D8854(SHL_WORK *wp)
{
    SVECTOR rot;
    VECTOR v;

    func_800354E0(wp->bit_d);
    wp->box_78   = &D_800D8F7C;
    wp->value_74 = 1;
    wp->value_cc = 0xF0;
    wp->col_bc   = 0;
    wp->col_c0   = 0;
    wp->col_c4   = 0;
    wp->col_c8   = 0;
    wp->be_flag |= TRANS | MODEL;
    wp->flags |= 0x20;
    wp->value_d0 = Player_work.value_54c;
    wp->value_d4 = func_800375D4(&Player_work, 0xB);
    rot.vx       = 0;
    rot.vy       = wp->rot_y & 0xFFF;
    rot.vz       = 0;
    RotMatrixYXZ(&rot, &wp->draw.mdl.mtx_8c);
    v.vy = 0x1000;
    v.vz = 0x1000;
    v.vx = 0x1000;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&wp->draw.mdl.mtx_8c, &rot, &v);
    wp->vel.vx          = (uint32)(v.vx * 5) >> 1;
    wp->vel.vy          = (uint32)(v.vy * 5) >> 1;
    wp->vel.vz          = (uint32)(v.vz * 5) >> 1;
    wp->ax              = 0;
    wp->ay              = 0x200;
    wp->az              = 0;
    wp->draw.mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
    wp->draw.mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
    wp->draw.mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                     = wp->fpos;
    wp->old_fpos.w.x -= wp->vel.vx << 8;
    wp->old_fpos.w.y -= wp->vel.vy << 8;
    wp->old_fpos.w.z -= wp->vel.vz << 8;
    wp->old_pos.vx = wp->old_fpos.w.x >> 16;
    wp->old_pos.vy = wp->old_fpos.w.y >> 16;
    wp->old_pos.vz = wp->old_fpos.w.z >> 16;
    wp->hit_7c     = 0;
    v.vz           = 0x200;
    v.vx           = 0x200;
    v.vy           = 0x300;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    if (wp->value_d0)
    {
        wp->draw.mdl.color_b4 = 0x8080C0;
    }
    else
    {
        wp->draw.mdl.color_b4 = 0x808080;
    }
    Model_work_init(wp, 0);
    func_800D8E64(wp, 0x4000);
    Sound_call2(0x132, &wp->pos);
    wp->routine_0 = 1;
}

void func_800D8AAC(SHL_WORK *wp)
{
    sint32 hit;

    if (func_80037694(wp, 0) == 0x7FFF || wp->hit_7c || !Map_cell_get(&wp->pos))
    {
        func_800D8EF4(wp);
        Close_PL_SHL_WORK(wp);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    wp->vel.vy += wp->ay;
    wp->fpos.w.x += wp->vel.vx << 8;
    wp->fpos.w.y += wp->vel.vy << 8;
    wp->fpos.w.z += wp->vel.vz << 8;
    wp->draw.mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
    wp->draw.mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
    wp->draw.mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    hit                              = Obj_map_push_out(wp);
    if (hit >= 0)
    {
        if (hit & 0x1000)
        {
            wp->value_74  = 0;
            wp->routine_0 = 2;
        }
        Wall_reflect_spd(&wp->vel, hit);
    }
    else
    {
        wp->value_74  = 0;
        wp->routine_0 = 2;
    }
    func_800D8E64(wp, 0x4000);
}

void func_800D8C1C(SHL_WORK *wp)
{
    if (func_80037694(wp, 0) == 0x7FFF)
    {
        func_800D8EF4(wp);
        Close_PL_SHL_WORK(wp);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    Front_hit_event(wp);
    Obj_map_push_out(wp);
    wp->pos.vy          = Obj_ceiling_height_get(wp);
    wp->fpos.w.y        = wp->pos.vy << 16;
    wp->draw.mdl.pos.vx = wp->pos.vx;
    wp->draw.mdl.pos.vy = wp->pos.vy;
    wp->draw.mdl.pos.vz = wp->pos.vz;
    if (--wp->value_cc == 0)
    {
        wp->value_cc  = 0x3C;
        wp->routine_0 = 3;
    }
    func_800D8E64(wp, 0x6000);
}

void func_800D8D14(SHL_WORK *wp)
{
    sint32 *timer; // retail keeps &wp->value_cc in a saved register from the start

    timer = &wp->value_cc;
    if (func_80037694(wp, 0) == 0x7FFF)
    {
        goto end;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    Front_hit_event(wp);
    Obj_map_push_out(wp);
    wp->pos.vy          = Obj_ceiling_height_get(wp);
    wp->fpos.w.y        = wp->pos.vy << 16;
    wp->draw.mdl.pos.vx = wp->pos.vx;
    wp->draw.mdl.pos.vy = wp->pos.vy;
    wp->draw.mdl.pos.vz = wp->pos.vz;
    if (SHL_FRAME & 2)
    {
        if (SHL_FRAME & 1)
        {
            Sound_call2(0x133, &wp->pos);
        }
        wp->draw.mdl.color_b4 = 0xE0E0E0;
    }
    else if (wp->value_d0)
    {
        wp->draw.mdl.color_b4 = 0x8080C0;
    }
    else
    {
        wp->draw.mdl.color_b4 = 0x808080;
    }
    if (--*timer == 0)
    {
    end:
        func_800D8EF4(wp);
        Close_PL_SHL_WORK(wp);
        return;
    }
    func_800D8E64(wp, 0x6000);
}

void func_800D8E64(SHL_WORK *wp, uint16 arg)
{
    SVECTOR p;

    p.vx = wp->pos.vx;
    p.vy = wp->pos.vy - 0x28;
    p.vz = wp->pos.vz;
    func_800341BC(&p, 0x30, 0, arg, wp->work_id, &wp->col_c4, wp->value_d4 | 0x8000000, 0, 0x80);
    wp->col_bc = 0;
    wp->col_c0 = 0;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
}

void func_800D8EF4(SHL_WORK *wp)
{
    SHL_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->be_flag = MOVE | MODEL;
        fx->id      = 0x80;
        fx->type    = 2;
        fx->value_c = 1;
        fx->value_d = D_800D8F98[wp->value_d0];
        fx->value_e = 1;
        fx->pos_38  = wp->pos;
    }
}
