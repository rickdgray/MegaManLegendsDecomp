#include "common.h"
#include "shl04.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D8C44[wp->routine_0](wp);
}

void func_800D8840(SHL_WORK *wp)
{
    SVECTOR unused_s;
    VECTOR unused_v;

    func_800354E0(wp->bit_d);
    wp->timer_b = 0;
    wp->routine_0++;
    func_800D89F8(wp);
    Sound_call2(0x123, &wp->pos);
}

void func_800D8894(SHL_WORK *wp)
{
    SHL_PLAYER *tp;
    MATRIX unused;
    SVECTOR rot;

    tp         = func_80036294(wp->index_c);
    wp->pos.vx = tp->pos_3c8.vx + (tp->pos_3c8.vx - tp->pos_3c0.vx) * 4;
    wp->pos.vy = tp->pos_3c8.vy + (tp->pos_3c8.vy - tp->pos_3c0.vy) * 4;
    wp->pos.vz = tp->pos_3c8.vz + (tp->pos_3c8.vz - tp->pos_3c0.vz) * 4;
    if (func_80037694(wp, 0x80))
    {
        func_800D8ADC(wp, 1);
        Sound_call(0x125, 0, 0);
    }
    if (tp->state_170 == 4)
    {
        if (tp->timer_51a != 0)
        {
            if (tp->timer_51a != 0x7FFF)
            {
                tp->timer_51a--;
            }
            if (tp->value_100 <= D_80089AB6 && tp->value_174 != 0)
            {
                goto rotate;
            }
        }
        Sound_call(0x124, 0, 0);
    }
    Close_PL_SHL_WORK(wp);
    return;

rotate:
    rot.vx = 0;
    rot.vy = (wp->timer_b & 7) << 9;
    rot.vz = 0;
    func_800D8AE4(tp, &rot);
    wp->timer_b--;
    func_800D89F8(wp);
}

void func_800D89F8(SHL_WORK *wp)
{
    SHL_PLAYER *tp;
    SVECTOR pos;
    sint32 flags;

    flags  = func_800375D4(&Player_work, 4);
    tp     = func_80036294(wp->index_c);
    pos.vx = tp->pos_3c8.vx + (tp->pos_3c8.vx - tp->pos_3c0.vx) * 4;
    pos.vy = tp->pos_3c8.vy + (tp->pos_3c8.vy - tp->pos_3c0.vy) * 4;
    pos.vz = tp->pos_3c8.vz + (tp->pos_3c8.vz - tp->pos_3c0.vz) * 4;
    func_8003430C(&tp->pos_3c8, 0x14, &pos, 8, 0x200, 0x4000, wp->slot, &wp->col_c4, flags | 0x88000000, 0, 0x80);
    wp->col_c4 = 0;
    wp->col_c8 = 0;
}

void func_800D8ADC(SHL_WORK *wp, sint32 arg)
{
}

void func_800D8AE4(SHL_PLAYER *tp, SVECTOR *rot)
{
    VECTOR v;
    SVECTOR unused_s;
    VECTOR unused_v;
    SVECTOR pos;
    MATRIX rm;
    MATRIX m;

    pos.vx = D_800DD600->pos_20.vx;
    pos.vy = D_800DD600->pos_20.vy;
    pos.vz = D_800DD600->pos_20.vz;
    m      = tp->mtx_228;
    ApplyMatrix(&m, &pos, &v);
    RotMatrix(rot, &rm);
    MulMatrix(&m, &rm);
    m.t[0]         = v.vx + tp->pos_3c0.vx;
    m.t[1]         = v.vy + tp->pos_3c0.vy;
    m.t[2]         = v.vz + tp->pos_3c0.vz;
    tp->pos_3c8.vx = m.t[0];
    tp->pos_3c8.vy = m.t[1];
    tp->pos_3c8.vz = m.t[2];
    tp->mtx_248    = m;
}
