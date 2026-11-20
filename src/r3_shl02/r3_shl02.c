#include "common.h"
#include "shl02.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D9014[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_800D8854(SHL_WORK *wp)
{
    SVECTOR rot;
    VECTOR v;

    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = &D_800D9008;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    if (wp->type_3 & 0x40)
    {
        rot.vx = wp->rot_x;
    }
    else
    {
        func_800354E0(wp->bit_d);
        rot.vx = func_80039B80();
    }
    rot.vy = wp->rot_y & 0xFFF;
    rot.vz = 0;
    if (wp->type_3 & 0x40)
    {
        rot.vx += ((rand() & 7) - 4) * 2;
        rot.vy += ((rand() & 7) - 4) * 2;
    }
    else
    {
        switch (Player_work.value_508)
        {
            case 0:
                rot.vx += ((rand() & 3) - 2) * 2;
                rot.vy += ((rand() & 3) - 2) * 2;
                break;
            case 1:
                rot.vx += ((rand() & 7) - 4) * 2;
                rot.vy += ((rand() & 7) - 4) * 2;
                break;
            case 2: // shares default; listing it gives retail's compare tree
            default:
                rot.vx += ((rand() & 0xF) - 8) * 2;
                rot.vy += ((rand() & 0xF) - 8) * 2;
                break;
        }
    }
    RotMatrixYXZ(&rot, &wp->draw.mdl.mtx_8c);
    v.vy = 0x1000;
    v.vz = 0x1000;
    v.vx = 0x1000;
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&wp->draw.mdl.mtx_8c, &rot, &v);
    if (!(wp->type_3 & 0x40) && Player_work.value_507 >= 3)
    {
        wp->vel.vx = (uint32)(v.vx * 15) >> 1;
        wp->vel.vy = (uint32)(v.vy * 15) >> 1;
        wp->vel.vz = (uint32)(v.vz * 15) >> 1;
    }
    else
    {
        wp->vel.vx = (uint32)(v.vx * 25) >> 2;
        wp->vel.vy = (uint32)(v.vy * 25) >> 2;
        wp->vel.vz = (uint32)(v.vz * 25) >> 2;
    }
    wp->ax     = 0;
    wp->ay     = 0;
    wp->az     = 0;
    wp->hit_7c = 0;
    if (wp->type_3 & 0x40)
    {
        wp->fpos.w.x += wp->vel.vx * 0x1C0;
        wp->fpos.w.y += wp->vel.vy * 0x1C0;
        wp->fpos.w.z += wp->vel.vz * 0x1C0;
    }
    wp->draw.mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
    wp->draw.mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
    wp->draw.mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                     = wp->fpos;
    wp->old_pos                      = wp->pos;
    wp->draw.mdl.color_b4            = 0x02808080;
    Model_work_init(wp, 0);
    wp->timer_b = func_80037634(&Player_work, 2);
    wp->routine_0++;
    func_800D8F08(wp, 0);
    func_800D8DC4(wp);
    Sound_call2(0x120, &wp->pos);
}

void func_800D8C4C(SHL_WORK *wp)
{
    if (func_80037694(wp, 0) || wp->hit_7c)
    {
        if (wp->type_3 & 0x40)
        {
            Close_SHL_WORK(wp);
        }
        else
        {
            func_80031930(wp);
        }
        func_800D8F08(wp, 1);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    if (wp->timer_b-- != 0)
    {
        wp->fpos.w.x += wp->vel.vx << 8;
        wp->fpos.w.y += wp->vel.vy << 8;
        wp->fpos.w.z += wp->vel.vz << 8;
        wp->draw.mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
        wp->draw.mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
        wp->draw.mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    }
    else
    {
        if (wp->type_3 & 0x40)
        {
            Close_SHL_WORK(wp);
        }
        else
        {
            func_80031930(wp);
        }
        return;
    }
    func_800D8DC4(wp);
}

void func_800D8DC4(SHL_WORK *wp)
{
    SVECTOR p;
    sint32 flags;

    flags = func_800375D4(&Player_work, 2);
    p.vx  = wp->pos.vx * 2 - wp->old_pos.vx;
    p.vy  = wp->pos.vy * 2 - wp->old_pos.vy;
    p.vz  = wp->pos.vz * 2 - wp->old_pos.vz;
    if (Player_work.value_171 == 0)
    {
        flags = 0x1000;
    }
    if (wp->type_3 & 0x40)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0xA000, wp->value_1, &wp->col_c4, 0x8000005, 0, 0x80);
    }
    else if (wp->index_c)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x6000, wp->value_1, &wp->col_c4, flags | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x4000, wp->value_1, &wp->col_c4, flags | 0x8000000, 0, 0x80);
    }
}

void func_800D8F08(SHL_WORK *wp, sint32 arg)
{
    SHL_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->routine_0 = 1;
        fx->kind_2    = 0x85;
        fx->x_1c      = wp->pos.vx;
        fx->y_1e      = wp->pos.vy;
        fx->z_20      = wp->pos.vz;
        fx->vx_30     = wp->vel.vx;
        fx->vy_32     = wp->vel.vy;
        fx->vz_34     = wp->vel.vz;
        if (wp->type_3 == 0x40)
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type_3 == 0x41)
        {
            fx->value_40 = (wp->rot_y - 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type_3 == 0x42)
        {
            fx->value_40 = 0xFFFF;
            fx->flag_3   = arg + 0x10;
        }
        else
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg;
        }
    }
}
