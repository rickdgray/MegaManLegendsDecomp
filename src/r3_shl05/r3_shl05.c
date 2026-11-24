#include "common.h"
#include "shl05.h"

// Module entry: ROCK_NEO.EXE's SHL table (0x80089A28) points every special weapon here.
void func_800D8804(SHL_WORK *wp)
{
    SVECTOR p;

    D_800D95EC[wp->routine_0](wp);
    p.vx = wp->draw.spr.x_90;
    p.vy = wp->draw.spr.y_92;
    p.vz = wp->draw.spr.z_94;
    if (wp->index_c)
    {
        func_800341BC(&p, 8, 0, 0x6000, wp->value_1, &wp->col_c4, D_80089C6C[Player_work.value_51c].flags_0 | 0x8000000, 0, 0x80);
    }
    else
    {
        func_800341BC(&p, 8, 0, 0x4000, wp->value_1, &wp->col_c4, D_80089C6C[Player_work.value_51c].flags_0 | 0x8000000, 0, 0x80);
    }
    Model_Shadow_Trans(wp, 0x18, 0x200, 0);
    func_80051BAC(wp);
}

void func_800D8928(SHL_WORK *wp)
{
    SVECTOR dir;
    SVECTOR rot;
    VECTOR v;
    MATRIX m;

    func_800354E0(wp->index_c);
    wp->routine_1 = 0;
    wp->timer_b   = 0;
    wp->mode_a    = 0;
    wp->value_e   = 0;
    wp->col_c4    = 0;
    wp->col_c8    = 0;
    wp->flags_0 |= 0; // stored back unchanged in retail
    wp->flags_6 |= 0x20;
    rot.vx = func_80039B80();
    rot.vy = wp->rot_y & 0xFFF;
    rot.vz = 0;
    RotMatrixYXZ(&rot, &m);
    dir.vx = 0;
    dir.vy = 0;
    dir.vz = -0x1000;
    ApplyMatrix(&m, &dir, &v);
    dir.vx                = v.vx;
    dir.vy                = v.vy;
    dir.vz                = v.vz;
    wp->vel.vx            = (dir.vx * D_80089C6C[Player_work.value_51e].speed_4) >> 4;
    wp->vel.vy            = (dir.vy * D_80089C6C[Player_work.value_51e].speed_4) >> 4;
    wp->vel.vz            = (dir.vz * D_80089C6C[Player_work.value_51e].speed_4) >> 4;
    wp->ax                = 0;
    wp->ay                = 0x200;
    wp->az                = 0;
    wp->hit_7c            = 0;
    wp->draw.spr.code_88  = 0x3D48000E;
    wp->draw.spr.color_8c = 0x2C808080;
    func_80030150(&wp->fpos, &wp->pos);
    wp->old_fpos.w.x = wp->fpos.w.x - (wp->vel.vx << 10);
    wp->old_fpos.w.y = wp->fpos.w.y;
    wp->old_fpos.w.z = wp->fpos.w.z - (wp->vel.vz << 10);
    func_80030150(&wp->old_fpos, &wp->old_pos);
    wp->box_78            = &D_800D95B0;
    wp->draw.spr.scale_96 = D_800D95BC[0].scale_96;
    wp->draw.spr.scale_97 = D_800D95BC[0].scale_97;
    wp->draw.spr.size_98  = 0x18;
    wp->flags_0 |= 2;
    wp->value_74 = 1;
    func_800D94C0(wp);
    wp->draw.spr.x_90 = wp->pos.vx;
    wp->draw.spr.y_92 = wp->pos.vy - 8;
    wp->draw.spr.z_94 = wp->pos.vz;
    wp->value_e &= ~4;
    wp->routine_0++;
    Sound_call2(0x127, &wp->pos);
    if (func_800D90B0(wp))
    {
        wp->routine_0 = 3;
        wp->bit_d     = 0;
    }
}

void func_800D8B90(SHL_WORK *wp)
{
    SVECTOR unused;
    SHL_FX *fx;

    func_800D94C0(wp);
    if (func_80037694(wp, 0) || wp->hit_7c)
    {
        wp->draw.spr.value_9c = 0;
        fx                    = func_80031618();
        if (fx)
        {
            func_800D9450(wp, fx);
        }
        wp->flags_0 = 0;
        Close_PL_SHL_WORK(wp);
        return;
    }
    wp->old_fpos          = wp->fpos;
    wp->old_pos           = wp->pos;
    wp->draw.spr.color_8c = 0x2C808080;
    func_800D935C(wp);
    func_80030150(&wp->old_fpos, &wp->old_pos);
    func_80030150(&wp->fpos, &wp->pos);
    if ((Game_work.value_50 == 0x10 || Game_work.value_50 == 0x11) && wp->pos.vy >= -1)
    {
        wp->flags_0 = 0;
        Close_PL_SHL_WORK(wp);
        return;
    }
    if (func_800D90B0(wp))
    {
        wp->routine_0 = 3;
        wp->bit_d     = 0;
    }
    if (wp->mode_a >= 150)
    {
        wp->routine_0 = 3;
        wp->bit_d     = 0;
    }
    else
    {
        wp->mode_a++;
        if (++wp->routine_1 >= 6)
        {
            wp->routine_1 = 0;
        }
    }
    wp->draw.spr.x_90     = wp->pos.vx;
    wp->draw.spr.y_92     = wp->pos.vy - 8;
    wp->draw.spr.z_94     = wp->pos.vz;
    wp->draw.spr.scale_96 = D_800D95BC[wp->routine_1].scale_96;
    wp->draw.spr.scale_97 = D_800D95BC[wp->routine_1].scale_97;
}

void func_800D8D60(SHL_WORK *wp)
{
    SHL_FX *fx;

    wp->draw.spr.code_88  = 0x3D48000E;
    wp->draw.spr.color_8c = 0x2C808080;
    wp->draw.spr.scale_97 = wp->draw.spr.scale_96 = 0xD8;
    wp->draw.spr.size_98                          = 0x20;
    wp->draw.spr.x_90 = wp->pos.vx = wp->fpos.h.x;
    wp->draw.spr.y_92 = wp->pos.vy = wp->fpos.h.y;
    wp->draw.spr.z_94 = wp->pos.vz = wp->fpos.h.z;
    fx                             = func_80031618();
    if (fx)
    {
        func_800D9450(wp, fx);
    }
    wp->flags_0 = 0;
    Close_PL_SHL_WORK(wp);
}

void func_800D8DF4(SHL_WORK *wp)
{
    SHL_FX *fx;
    sint16 mask;

    if (func_80037694(wp, 0) || wp->hit_7c)
    {
        wp->draw.spr.value_9c = 0;
        goto end;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    func_800D935C(wp);
    func_80030150(&wp->old_fpos, &wp->old_pos);
    func_80030150(&wp->fpos, &wp->pos);
    if ((Game_work.value_50 == 0x10 || Game_work.value_50 == 0x11) && wp->pos.vy >= -1)
    {
        goto remove;
    }
    func_800D90B0(wp);
    wp->draw.spr.x_90     = wp->pos.vx;
    wp->draw.spr.y_92     = wp->pos.vy - 8;
    wp->draw.spr.z_94     = wp->pos.vz;
    wp->draw.spr.scale_96 = D_800D95BC[wp->routine_1].scale_96;
    wp->draw.spr.scale_97 = D_800D95BC[wp->routine_1].scale_97;
    if (wp->vel.vx)
    {
        if (++wp->routine_1 >= 6)
        {
            wp->routine_1 = 0;
        }
    }
    func_800D94C0(wp);
    if (wp->bit_d < 30)
    {
        if (wp->bit_d < 15)
        {
            mask = 1;
        }
        else
        {
            mask = -1;
        }
        if (wp->bit_d & mask)
        {
            if ((wp->draw.spr.color_8c & 0xFF) == 0xFF)
            {
                wp->draw.spr.color_8c = 0x2C808080;
            }
            else
            {
                wp->draw.spr.color_8c = 0x2CFFFFFF;
            }
        }
        wp->bit_d++;
        return;
    }
end:
    fx = func_80031618();
    if (fx)
    {
        func_800D9450(wp, fx);
    }
remove:
    wp->flags_0 = 0;
    Close_PL_SHL_WORK(wp);
}

void func_800D8FEC(SHL_WORK *wp)
{
    wp->draw.spr.code_88  = 0x3D48000E;
    wp->draw.spr.color_8c = 0x2C808080;
    func_80030150(&wp->fpos, &wp->pos);
    wp->draw.spr.x_90     = wp->pos.vx;
    wp->draw.spr.y_92     = wp->pos.vy - 0x10;
    wp->draw.spr.z_94     = wp->pos.vz;
    wp->old_fpos          = wp->fpos;
    wp->old_pos           = wp->pos;
    wp->draw.spr.scale_97 = wp->draw.spr.scale_96 = 0xD8;
    wp->draw.spr.size_98                          = 0x20;
    wp->flags_0 |= 2;
}

sint16 func_800D90B0(SHL_WORK *wp)
{
    SHL05_FX *fx;
    sint32 hit;
    sint32 v;
    sint16 stop;

    stop         = 0;
    wp->value_74 = 1;
    func_800D94C0(wp);
    hit = Obj_map_push_out(wp);
    if (hit != 0)
    {
        if (hit & 0x1000)
        {
            if ((wp->vel.vy < 0 ? -wp->vel.vy : wp->vel.vy) <= 0x1000)
            {
                stop       = 1;
                wp->vel.vx = 0;
                wp->vel.vy = 0;
                wp->vel.vz = 0;
                wp->ax     = 0;
                wp->ay     = 0;
                wp->az     = 0;
            }
            else
            {
                v          = wp->vel.vy * 160;
                v          = v < 0 ? (uint32)-v >> 8 : (uint32)v >> 8;
                wp->vel.vy = v;
                wp->vel.vx = wp->vel.vx >> 1;
                wp->vel.vz = wp->vel.vz >> 1;
            }
            if (Game_work.value_50 == 11 && wp->pos.vy == -1)
            {
                Close_PL_SHL_WORK(wp);
                Sound_call2(0x102, &wp->pos);
                fx = func_80031618();
                if (fx)
                {
                    fx->spr = wp->draw.spr;
                }
                func_800D9574(wp, (SHL_FX *)fx);
            }
            else
            {
                Sound_call2(0x129, &wp->pos);
                fx = func_80031618();
                if (fx)
                {
                    fx->routine_0 = 1;
                    fx->kind_2    = 0x83;
                    fx->flag_3    = 0;
                    fx->spr       = wp->draw.spr;
                }
            }
        }
        else
        {
            if (Game_work.value_50 != 11 || wp->pos.vy != -1)
            {
                Sound_call2(0x129, &wp->pos);
            }
            fx = func_80031618();
            if (fx)
            {
                fx->routine_0 = 1;
                fx->kind_2    = 0x83;
                fx->flag_3    = 0;
                fx->spr       = wp->draw.spr;
            }
        }
        Wall_reflect_spd(&wp->vel, hit);
    }
    return stop;
}

void func_800D935C(SHL_WORK *wp)
{
    wp->vel.vx += wp->ax;
    wp->vel.vy += wp->ay;
    wp->vel.vz += wp->az;
    if (wp->vel.vx < -0x6000)
    {
        wp->vel.vx = -0x6000;
    }
    else if (wp->vel.vx > 0x6000)
    {
        wp->vel.vx = 0x6000;
    }
    if (wp->vel.vy < -0x6000)
    {
        wp->vel.vy = -0x6000;
    }
    else if (wp->vel.vy > 0x6000)
    {
        wp->vel.vy = 0x6000;
    }
    if (wp->vel.vz < -0x6000)
    {
        wp->vel.vz = -0x6000;
    }
    else if (wp->vel.vz > 0x6000)
    {
        wp->vel.vz = 0x6000;
    }
    wp->fpos.w.x += wp->vel.vx << 8;
    wp->fpos.w.y += wp->vel.vy << 8;
    wp->fpos.w.z += wp->vel.vz << 8;
    // Retail stores the position back unchanged.
    wp->pos.vx = wp->pos.vx;
    wp->pos.vy = wp->pos.vy;
    wp->pos.vz = wp->pos.vz;
}

void func_800D9450(SHL_WORK *wp, SHL_FX *fx)
{
    fx->routine_0 = 5;
    fx->kind_2    = 0x80;
    fx->flag_3    = 2;
    fx->value_e   = 1;
    if (Player_work.value_51c == 0)
    {
        fx->value_d = 1;
    }
    else
    {
        fx->value_d = 2;
    }
    fx->pos_38 = wp->pos;
}

void func_800D94C0(SHL_WORK *wp)
{
    uint32 d;

    d = func_800D9508(&Player_work.pos, &wp->pos);
    if (d < 0x1C00)
    {
        D_800D9600 = d >> 6;
    }
    else
    {
        D_800D9600 = 0x80;
    }
}

sint32 func_800D9508(SVECTOR *a, SVECTOR *b)
{
    sint32 dx;
    sint32 dy;
    sint32 dz;

    dx = a->vx - b->vx;
    dy = a->vy - b->vy;
    dz = a->vz - b->vz;
    return SquareRoot0(dx * dx + dy * dy + dz * dz);
}

void func_800D9574(SHL_WORK *wp, SHL_FX *fx)
{
    fx->routine_0 = 1;
    fx->kind_2    = 0x19;
    fx->flag_3    = 0;
    fx->pos_38    = wp->pos;
}
