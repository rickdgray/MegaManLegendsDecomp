#include "common.h"
#include "shl0d.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL0D_WORK *wp)
{
    D_800D92B4[wp->routine_0](wp);
}

void func_800D8840(SHL0D_WORK *wp)
{
    uint8 level;
    uint8 i;

    func_800354E0(wp->bit_d);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->mode_a    = 0;
    wp->timer_b   = 0;
    wp->index_c   = 0;
    wp->bit_d     = 0;
    wp->value_e   = 0;
    wp->value_f   = 0;
    wp->flags_0 |= 6;
    wp->flags_6 |= 0x20;
    level             = Player_work.value_55e;
    wp->beam.len_bd   = 8;
    wp->beam.value_be = D_800D9260[level];
    wp->beam.value_bf = D_800D9258[level];
    wp->beam.size_c0  = D_800D9268[level];
    wp->beam.flags_c4 = func_800375D4(&Player_work, 0xD);
    wp->beam.scale_c8 = D_800D9288[level];
    func_800D8AB8(wp);
    wp->color_b4 = 0x02808080;
    func_8002F9C4(wp, 0);
    for (i = 0; i < 16; i++)
    {
        wp->beam.hit[i] = 0;
    }
    wp->box_78 = &D_800D92A8;
    func_800D8D08(wp);
    Sound_call2(0x136, &wp->pos);
}

void func_800D8988(SHL0D_WORK *wp)
{
    SHL0D_BEAM *bp;
    sint32 len;

    bp = &wp->beam;
    if (wp->beam.len_bd < 0x40)
    {
        wp->beam.len_bd += 8;
    }
    else
    {
        wp->beam.len_bd = 0x40;
    }
    if (func_800D8A6C(wp))
    {
        goto end;
    }
    len = func_800D9010(wp);
    if (len)
    {
        bp->len_bd = len;
    }
    if (func_800D91FC(wp))
    {
        wp->color_b4 = 0x02808080;
    }
    if (Player_work.timer_562 == 0)
    {
    end:
        Sound_call2(0x137, &wp->pos);
        func_80031930(wp);
        return;
    }
    if (Player_work.timer_562 != 0x7FFF)
    {
        Player_work.timer_562--;
    }
    func_800D8AB8(wp);
    func_800D8D08(wp);
}

uint8 func_800D8A6C(SHL0D_WORK *wp)
{
    if ((PLAYER_WORK_PTR->pad_11c & PLAYER_WORK_PTR->value_13c) && func_8004324C(&Player_work))
    {
        return 0;
    }
    return 1;
}

void func_800D8AB8(SHL0D_WORK *wp)
{
    VECTOR v;
    SVECTOR rot;
    SVECTOR p;

    rot.vx = func_80039B80();
    rot.vy = Player_work.rot.vy & 0xFFF;
    rot.vz = (SHL_FRAME & 0xF) << 8;
    RotMatrixYXZ(&rot, &wp->mtx_8c);
    v.vx = v.vy = v.vz = 0x1000;
    ScaleMatrix(&wp->mtx_8c, &v);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&wp->mtx_8c, &rot, &v);
    wp->vx        = (uint32)(v.vx * 15) >> 3;
    wp->vy        = (uint32)(v.vy * 15) >> 3;
    wp->vz        = (uint32)(v.vz * 15) >> 3;
    p             = Player_work.pos_3c8;
    wp->fpos.w.x  = (p.vx << 16) + (wp->vx << 8);
    wp->fpos.w.y  = (p.vy << 16) + (wp->vy << 8);
    wp->fpos.w.z  = (p.vz << 16) + (wp->vz << 8);
    wp->pos_ac.vx = wp->pos.vx = wp->fpos.h.x;
    wp->pos_ac.vy = wp->pos.vy = wp->fpos.h.y;
    wp->pos_ac.vz = wp->pos.vz = wp->fpos.h.z;
    wp->old_fpos               = wp->fpos;
    wp->old_pos                = wp->pos;
    wp->vx                     = (v.vx * wp->beam.value_bf) >> 4;
    wp->vy                     = (v.vy * wp->beam.value_bf) >> 4;
    wp->vz                     = (v.vz * wp->beam.value_bf) >> 4;
    v.vx = v.vy = wp->beam.scale_c8;
    v.vz        = wp->beam.value_be * wp->beam.len_bd;
    ScaleMatrix(&wp->mtx_8c, &v);
}

// Retail separates mflo from the next mult by two instructions even across a register-based load;
// tools/patches/maspsx-mflo-mult-register-load.patch makes maspsx do the same.
void func_800D8D08(SHL0D_WORK *wp)
{
    VECTOR step;
    SVECTOR a;
    SVECTOR b;
    SHL0D_BEAM *bp;
    uint8 i;
    sint32 rest;
    sint32 j;
    sint32 k;
    sint32 m;

    step.vx = wp->vx << 8;
    step.vy = wp->vy << 8;
    step.vz = wp->vz << 8;
    bp      = &wp->beam;
    for (i = 0; i < (bp->len_bd >> 3); i++)
    {
        j    = i << 3;
        a.vx = (wp->fpos.w.x + step.vx * (uint8)(j | 6)) >> 16;
        a.vy = (wp->fpos.w.y + step.vy * (uint8)(j | 6)) >> 16;
        a.vz = (wp->fpos.w.z + step.vz * (uint8)(j | 6)) >> 16;
        m    = j | 1;
        b.vx = (wp->fpos.w.x + step.vx * (uint8)m) >> 16;
        b.vy = (wp->fpos.w.y + step.vy * (uint8)m) >> 16;
        b.vz = (wp->fpos.w.z + step.vz * (uint8)m) >> 16;
        func_8003430C(&a, bp->size_c0, &b, bp->size_c0, 0x200, 0x4000, wp->value_1,
                      &wp->beam.hit[i], bp->flags_c4 | 0x8000000, 0, 0x80);
        wp->beam.hit[i * 2]     = 0;
        wp->beam.hit[i * 2 + 1] = 0;
    }
    rest = bp->len_bd & 7;
    if (rest && i < 8)
    {
        k    = i << 3;
        m    = k | rest;
        a.vx = (wp->fpos.w.x + step.vx * (uint8)m) >> 16;
        a.vy = (wp->fpos.w.y + step.vy * (uint8)m) >> 16;
        a.vz = (wp->fpos.w.z + step.vz * (uint8)m) >> 16;
        b.vx = (wp->fpos.w.x + step.vx * (uint8)(k & 0xF8)) >> 16;
        b.vy = (wp->fpos.w.y + step.vy * (uint8)(k & 0xF8)) >> 16;
        b.vz = (wp->fpos.w.z + step.vz * (uint8)(k & 0xF8)) >> 16;
        func_8003430C(&a, bp->size_c0, &b, bp->size_c0, 0x200, 0x4000, wp->value_1,
                      &wp->beam.hit[i], bp->flags_c4 | 0x8000000, 0, 0x80);
        wp->beam.hit[i * 2]     = 0;
        wp->beam.hit[i * 2 + 1] = 0;
    }
}

sint32 func_800D9010(SHL0D_WORK *wp)
{
    VECTOR step;
    SVECTOR a;
    SVECTOR b;
    SHL_FX *fx;
    SHL0D_BEAM *bp;
    uint8 i;

    step.vx = wp->vx << 8;
    step.vy = wp->vy << 8;
    step.vz = wp->vz << 8;
    bp      = &wp->beam;
    for (i = 0; i < bp->len_bd; i++)
    {
        a.vx = (wp->fpos.w.x + step.vx * (uint8)(i + 1)) >> 16;
        a.vy = (wp->fpos.w.y + step.vy * (uint8)(i + 1)) >> 16;
        a.vz = (wp->fpos.w.z + step.vz * (uint8)(i + 1)) >> 16;
        b.vx = (wp->fpos.w.x + step.vx * i) >> 16;
        b.vy = (wp->fpos.w.y + step.vy * i) >> 16;
        b.vz = (wp->fpos.w.z + step.vz * i) >> 16;
        if (func_80049C54(&a, &b, &D_800D92A8, 0xFFFF))
        {
            if ((SHL_FRAME & 3) == 0)
            {
                fx = func_80031618();
                if (fx)
                {
                    fx->routine_0 = 1;
                    fx->kind_2    = 0x8A;
                    fx->flag_3    = 1;
                    fx->x_1c      = b.vx;
                    fx->y_1e      = b.vy;
                    fx->z_20      = b.vz;
                }
            }
            return i + 1;
        }
    }
    return 0;
}

sint32 func_800D91FC(SHL0D_WORK *wp)
{
    uint8 i;

    for (i = 0; i < (wp->beam.len_bd >> 3); i++)
    {
        if (wp->beam.hit[i * 2] & 0xFF000000)
        {
            return 1;
        }
    }
    return 0;
}
