#include "common.h"
#include "shl07.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D8C28[wp->routine_0](wp);
}

void func_800D8840(SHL_WORK *wp)
{
    SVECTOR unused_s;
    VECTOR unused_v;

    func_800354E0(wp->bit_d);
    wp->timer_b = 0;
    wp->routine_0++;
    Sound_call2(0x12B, &wp->pos);
}

void func_800D888C(SHL_WORK *wp)
{
    SHL_PLAYER *tp;
    SHL_FX *fx;
    SVECTOR p;
    SVECTOR d;
    SVECTOR old;
    SVECTOR tmp;
    VECTOR diff;
    uint32 i;
    uint32 r;
    uint32 r2;
    sint32 push;

    wp->timer_b++;
    tp   = func_80036294(wp->index_c);
    p    = tp->pos;
    r    = func_80037634(&Player_work, 7);
    r2   = r * 2;
    push = D_800D8C30[Player_work.value_530];
    for (i = 0; i < 64; i++)
    {
        fx = &D_800A3B40[i];
        if (fx->be_flag == 0 || fx->id != 0x87 || fx->routine_0 >= 5)
        {
            continue;
        }
        d       = fx->pos_38;
        diff.vx = p.vx - d.vx;
        if (diff.vx + r > r2)
        {
            continue;
        }
        diff.vy = p.vy - d.vy;
        if (diff.vy + r > r2)
        {
            continue;
        }
        diff.vz = p.vz - d.vz;
        if (diff.vz + r > r2)
        {
            continue;
        }
        if (diff.vx * diff.vx + diff.vy * diff.vy + diff.vz * diff.vz >= r * r)
        {
            continue;
        }
        VectorNormalS(&diff, &d);
        old = fx->pos_38;
        if (push > 0)
        {
            fx->pos_38.vx += (d.vx * push) >> 12;
            fx->pos_38.vz += (d.vz * push) >> 12;
            tmp = fx->pos_38;
            Pos_map_push_out(&tmp, &old, 1, &D_8008A310[fx->index_a]);
            fx->pos_38.vx = tmp.vx;
            fx->pos_38.vy = tmp.vy;
            fx->pos_38.vz = tmp.vz;
        }
        else
        {
            fx->pos_38.vx = p.vx - ((d.vx * ((rand() & 0x1F) - 0x10)) >> 12);
            fx->pos_38.vy = p.vy - 0x8C;
            fx->pos_38.vz = p.vz - ((d.vz * ((rand() & 0x1F) - 0x10)) >> 12);
            break;
        }
    }
    if (tp->state_170 == 7)
    {
        if (tp->timer_532 == 0)
        {
            Sound_call(0x12C, 0, 0);
            Close_PL_SHL_WORK(wp);
        }
        else
        {
            if (tp->timer_532 != 0x7FFF)
            {
                tp->timer_532--;
            }
            if (tp->value_100 > D_80089ADA)
            {
                Sound_call(0x12C, 0, 0);
                Close_PL_SHL_WORK(wp);
            }
        }
    }
    else
    {
        Close_PL_SHL_WORK(wp);
    }
}

void func_800D8C20(void)
{
}
