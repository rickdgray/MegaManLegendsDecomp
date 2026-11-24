#include "common.h"
#include "shl08.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL08_WORK *wp)
{
    D_800D90E8[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_800D8854(SHL08_WORK *wp)
{
    SVECTOR rot;
    VECTOR v;

    wp->box_78 = &D_800D90CC;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    rot.vx = func_80039B80() + ((rand() & 7) - 4) * 2;
    rot.vy = (wp->rot_y & 0xFFF) + ((rand() & 7) - 4) * 2;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &wp->mdl.mtx_8c);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&wp->mdl.mtx_8c, &rot, &v);
    wp->vel.vx = v.vx;
    wp->vel.vy = v.vy;
    wp->vel.vz = v.vz;
    v.vy       = 0x200;
    v.vz       = 0x200;
    v.vx       = 0x200;
    ScaleMatrix(&wp->mdl.mtx_8c, &v);
    wp->ax         = 0;
    wp->ay         = 0;
    wp->az         = 0;
    wp->hit_7c     = 0;
    wp->mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
    wp->mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
    wp->mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                = wp->fpos;
    wp->old_pos                 = wp->pos;
    wp->trail[3] = wp->trail[2] = wp->trail[1] = wp->trail[0] = wp->pos;
    wp->mdl.color_b4                                          = 0x808080;
    Model_work_init(wp, 0);
    if (wp->type_3 >= 0x80 && (wp->target.w.w0 | wp->target.w.w1) == 0)
    {
        func_800354E0(wp->bit_d);
        wp->type_3 = 0;
    }
    wp->timer_b = func_80037634(&Player_work, 8);
    wp->routine_0++;
    func_800D8E38(wp);
    Sound_call2(0x12D, &wp->pos);
}

void func_800D8AE0(SHL08_WORK *wp)
{
    VECTOR d;
    SVECTOR n;
    SVECTOR vel;
    SHL_MODEL *mp;
    sint32 speed;

    if (func_80037694(wp, 0x20) || wp->hit_7c)
    {
        Close_PL_SHL_WORK(wp);
        if (wp->type_3 >= 0x80)
        {
            func_800354E0(wp->bit_d);
        }
        func_800D8F0C(wp);
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    wp->trail[3] = wp->trail[2];
    wp->trail[2] = wp->trail[1];
    wp->trail[1] = wp->trail[0];
    wp->trail[0] = wp->pos;
    mp           = &wp->mdl;
    if (wp->timer_b-- != 0)
    {
        if (wp->type_3 >= 0x80)
        {
            if (wp->target.w.w0 | wp->target.w.w1)
            {
                d.vx = wp->target.pos.vx - wp->pos.vx;
                d.vy = wp->target.pos.vy - wp->pos.vy;
                d.vz = wp->target.pos.vz - wp->pos.vz;
                if (d.vx < -0x687E || d.vx > 0x687E || d.vy < -0x687E || d.vy > 0x687E || d.vz < -0x687E || d.vz > 0x687E)
                {
                    d.vx >>= 2;
                    d.vy >>= 2;
                    d.vz >>= 2;
                }
                VectorNormalS(&d, &n);
                func_80033F04(&vel, &n, &wp->vel, 0x424, 0xF746EA4);
                wp->vel = vel;
            }
            else
            {
                func_800354E0(wp->bit_d);
                wp->type_3 = 0;
            }
        }
        speed = D_800D90D8[Player_work.value_536];
        wp->fpos.w.x += (wp->vel.vx * speed) << 4;
        wp->fpos.w.y += (wp->vel.vy * speed) << 4;
        wp->fpos.w.z += (wp->vel.vz * speed) << 4;
        mp->pos.vx = wp->pos.vx = wp->fpos.h.x;
        mp->pos.vy = wp->pos.vy = wp->fpos.h.y;
        mp->pos.vz = wp->pos.vz = wp->fpos.h.z;
    }
    else
    {
        Close_PL_SHL_WORK(wp);
        if (wp->type_3 >= 0x80)
        {
            func_800354E0(wp->bit_d);
        }
        return;
    }
    func_800D8E38(wp);
    func_800D8F98(wp);
}

void func_800D8E38(SHL08_WORK *wp)
{
    SVECTOR p;
    sint32 flags;

    flags = func_800375D4(&Player_work, 8);
    p.vx  = wp->old_pos.vx;
    p.vy  = wp->old_pos.vy;
    p.vz  = wp->old_pos.vz;
    if (wp->index_c)
    {
        func_8003430C(&wp->pos, 0x30, &p, 0x30, 0x200, 0x6000, wp->value_1, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&wp->pos, 0x30, &p, 0x30, 0x200, 0x4000, wp->value_1, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    }
}

void func_800D8F0C(SHL08_WORK *wp)
{
    SHL_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->routine_0 = 5;
        fx->kind_2    = 0x80;
        fx->flag_3    = 2;
        fx->value_d   = D_800D90F0[Player_work.value_534];
        fx->value_e   = 1;
        fx->pos_38.vx = wp->pos.vx;
        fx->pos_38.vy = wp->pos.vy;
        fx->pos_38.vz = wp->pos.vz;
    }
}

void func_800D8F98(SHL08_WORK *wp)
{
    SHL08_LINE *lp;
    sint32 i;

    lp = Billboard_line_get();
    if (lp)
    {
        lp->xy0       = *(uint32 *)&wp->pos;
        lp->code_rgb0 = D_800D90F8[1] | 0x52000000;
        lp->xy1       = *(uint32 *)&wp->trail[0];
        lp->rgb1      = D_800D90F8[0];
        lp->z0z1      = (wp->pos.vz << 16) | (uint16)wp->trail[0].vz;
        lp->tpage     = 0xE1000020;
    }
    for (i = 0; i < 3; i++)
    {
        lp = Billboard_line_get();
        if (lp)
        {
            lp->xy0       = *(uint32 *)&wp->trail[i];
            lp->code_rgb0 = D_800D90F8[i + 2] | 0x52000000;
            lp->xy1       = *(uint32 *)&wp->trail[i + 1];
            lp->rgb1      = D_800D90F8[i + 1];
            lp->z0z1      = (wp->trail[i].vz << 16) | (uint16)(wp->trail + i + 1)->vz;
            lp->tpage     = 0xE1000020;
        }
    }
}
