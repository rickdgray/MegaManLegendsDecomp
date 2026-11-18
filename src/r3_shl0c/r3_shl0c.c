#include "common.h"
#include "shl0c.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    D_800D90EC[wp->routine_0](wp);
}

void func_800D8840(SHL_WORK *wp)
{
    SVECTOR rot;
    SVECTOR p;
    VECTOR v;

    wp->box_78 = &D_800D9080;
    wp->col_bc = 0;
    wp->col_c0 = 0;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    func_800354E0(wp->bit_d);
    wp->value_f = Player_work.value_558;
    rot.vx      = func_80039B80();
    rot.vy      = Player_work.rot.vy & 0xFFF;
    rot.vz      = 0;
    RotMatrixYXZ(&rot, &wp->draw.mdl.mtx_8c);
    v.vx = v.vy = v.vz = D_800D908C[wp->value_f];
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&wp->draw.mdl.mtx_8c, &rot, &v);
    wp->vel.vx          = (uint32)(v.vx * 5) >> 1;
    wp->vel.vy          = (uint32)(v.vy * 5) >> 1;
    wp->vel.vz          = (uint32)(v.vz * 5) >> 1;
    p                   = Player_work.pos_3c8;
    wp->fpos.w.x        = (p.vx << 16) + (wp->vel.vx << 10);
    wp->fpos.w.y        = (p.vy << 16) + (wp->vel.vy << 10);
    wp->fpos.w.z        = (p.vz << 16) + (wp->vel.vz << 10);
    wp->draw.mdl.pos.vx = wp->pos.vx = wp->fpos.h.x;
    wp->draw.mdl.pos.vy = wp->pos.vy = wp->fpos.h.y;
    wp->draw.mdl.pos.vz = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos                     = wp->fpos;
    wp->old_pos                      = wp->pos;
    wp->draw.mdl.color_b4            = 0x02808080;
    func_8002F9C4(wp, 0);
    func_800D8D74(wp);
    Sound_call2(0x134, &wp->pos);
    wp->routine_0++;
}

void func_800D8A88(SHL_WORK *wp)
{
    SVECTOR rot;
    SVECTOR p;
    VECTOR v;
    SHL_MODEL *mp;

    mp = &wp->draw.mdl;
    if (func_800D8D28())
    {
        goto end;
    }
    wp->draw.mdl.color_b4 = 0x02808080;
    if (wp->col_c4 & 0x0C000000)
    {
        wp->draw.mdl.color_b4 = 0x02E0E0E0;
        Player_work.value_44c |= 3;
    }
    else if (func_800D8E8C(wp))
    {
        Player_work.value_44c |= 1;
    }
    if (Player_work.timer_55a == 0)
    {
    end:
        Sound_call2(0x135, &wp->pos);
        func_80031930(wp);
        return;
    }
    if (Player_work.timer_55a != 0x7FFF)
    {
        Player_work.timer_55a--;
    }
    rot.vx = func_80039B80();
    rot.vy = Player_work.rot.vy & 0xFFF;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &wp->draw.mdl.mtx_8c);
    v.vx = v.vy = v.vz = D_800D908C[wp->value_f];
    ScaleMatrix(&wp->draw.mdl.mtx_8c, &v);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&wp->draw.mdl.mtx_8c, &rot, &v);
    wp->vel.vx   = (uint32)(v.vx * 5) >> 1;
    wp->vel.vy   = (uint32)(v.vy * 5) >> 1;
    wp->vel.vz   = (uint32)(v.vz * 5) >> 1;
    p            = Player_work.pos_3c8;
    wp->fpos.w.x = (p.vx << 16) + (wp->vel.vx << 10);
    wp->fpos.w.y = (p.vy << 16) + (wp->vel.vy << 10);
    wp->fpos.w.z = (p.vz << 16) + (wp->vel.vz << 10);
    mp->pos.vx = wp->pos.vx = wp->fpos.h.x;
    mp->pos.vy = wp->pos.vy = wp->fpos.h.y;
    mp->pos.vz = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos            = wp->fpos;
    wp->old_pos             = wp->pos;
    func_800D8D74(wp);
}

uint8 func_800D8D28(void)
{
    if ((PLAYER_WORK_PTR->pad_11c & PLAYER_WORK_PTR->value_13c) && func_8004324C(&Player_work))
    {
        return 0;
    }
    return 1;
}

void func_800D8D74(SHL_WORK *wp)
{
    SVECTOR p;

    p.vx = (wp->fpos.w.x + (wp->vel.vx << 10)) >> 16;
    p.vy = (wp->fpos.w.y + (wp->vel.vy << 10)) >> 16;
    p.vz = (wp->fpos.w.z + (wp->vel.vz << 10)) >> 16;
    func_800341BC(&p, D_800D90AC[wp->value_f], 0, 0, wp->value_1, &wp->col_c4, 0x2000001, 0, 0x80);
    func_800341BC(&p, D_800D90AC[wp->value_f], 0, 0x4000, wp->value_1, &wp->col_bc, 0x28000001, 0,
                  0x80);
    wp->col_bc = 0;
    wp->col_c0 = 0;
    wp->col_c4 = 0;
    wp->col_c8 = 0;
}

uint8 func_800D8E8C(SHL_WORK *wp)
{
    SVECTOR p;
    SVECTOR r;
    SVECTOR q;
    VECTOR d;
    SHL0C_OBJ *obj;
    uint32 i;
    uint32 ang;
    uint32 hi;
    uint32 range;

    p     = Player_work.pos;
    r     = Player_work.rot;
    range = D_800D90CC[wp->value_f];
    for (i = 0; i < 32; i++)
    {
        obj = &D_8009CF88[i];
        if (obj->flag_0 == 0)
        {
            continue;
        }
        q    = obj->pos;
        d.vx = p.vx - q.vx;
        if (d.vx < -2000 || d.vx > 2000)
        {
            continue;
        }
        d.vy = p.vy - q.vy;
        if (d.vy < -2000 || d.vy > 2000)
        {
            continue;
        }
        d.vz = p.vz - q.vz;
        if (d.vz < -2000 || d.vz > 2000)
        {
            continue;
        }
        if ((uint32)(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz) > 999999)
        {
            continue;
        }
        ang = ratan2(d.vx, d.vz) & 0xFFF;
        hi  = (r.vy + range) & 0xFFF;
        if (hi < r.vy || ((r.vy - range) & 0xFFF) > r.vy)
        {
            if (ang < hi || ((r.vy - range) & 0xFFF) < ang)
            {
                return 1;
            }
        }
        else if (ang < hi && ((r.vy - range) & 0xFFF) < ang)
        {
            return 1;
        }
    }
    return 0;
}
