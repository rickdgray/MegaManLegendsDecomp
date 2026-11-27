#include "common.h"
#include "st0c.h"

void func_8010A590(STAGE_OBJ *wp)
{
    D_8010D7D0[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_8010A5E0(ST0C_SHL *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR v;

    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = D_8010D7C4;
    wp->be_flag |= 6;
    wp->flags |= 0x20;
    if (wp->type & 0x40)
    {
        rot.x = wp->rot_x;
    }
    else
    {
        func_800354E0(wp->bit_d);
        rot.x = func_80039B80();
    }
    rot.y = wp->rot_y & 0xFFF;
    rot.z = 0;
    if (wp->type & 0x40)
    {
        rot.x += ((rand() & 7) - 4) * 2;
        rot.y += ((rand() & 7) - 4) * 2;
    }
    else
    {
        switch (ST0C_PL_SBYTE(0x508))
        {
            case 0:
                rot.x += ((rand() & 3) - 2) * 2;
                rot.y += ((rand() & 3) - 2) * 2;
                break;
            case 1:
                rot.x += ((rand() & 7) - 4) * 2;
                rot.y += ((rand() & 7) - 4) * 2;
                break;
            case 2: // shares default; listing it gives retail's compare tree
            default:
                rot.x += ((rand() & 0xF) - 8) * 2;
                rot.y += ((rand() & 0xF) - 8) * 2;
                break;
        }
    }
    RotMatrixYXZ(&rot, &wp->mtx_8c);
    v.y = 0x1000;
    v.z = 0x1000;
    v.x = 0x1000;
    ScaleMatrix(&wp->mtx_8c, &v);
    rot.x = 0;
    rot.y = 0;
    rot.z = -0x1000;
    ApplyMatrix(&wp->mtx_8c, &rot, &v);
    if (!(wp->type & 0x40) && ST0C_PL_SBYTE(0x507) >= 3)
    {
        wp->vel.x = (uint32)(v.x * 15) >> 1;
        wp->vel.y = (uint32)(v.y * 15) >> 1;
        wp->vel.z = (uint32)(v.z * 15) >> 1;
    }
    else
    {
        wp->vel.x = (uint32)(v.x * 25) >> 2;
        wp->vel.y = (uint32)(v.y * 25) >> 2;
        wp->vel.z = (uint32)(v.z * 25) >> 2;
    }
    wp->ax     = 0;
    wp->ay     = 0;
    wp->az     = 0;
    wp->hit_7c = 0;
    if (wp->type & 0x40)
    {
        wp->fpos.v.x += wp->vel.x * 0x1C0;
        wp->fpos.v.y += wp->vel.y * 0x1C0;
        wp->fpos.v.z += wp->vel.z * 0x1C0;
    }
    wp->mpos.x = wp->pos.x = wp->fpos.f.x.words.integer;
    wp->mpos.y = wp->pos.y = wp->fpos.f.y.words.integer;
    wp->mpos.z = wp->pos.z = wp->fpos.f.z.words.integer;
    wp->old_fpos           = wp->fpos;
    wp->old_pos            = wp->pos;
    wp->color_b4           = 0x02808080;
    wp->id                 = 0x82;
    Model_work_init(wp, 0);
    wp->id      = 0x2E;
    wp->timer_b = func_80037634(&Player_work, 2);
    wp->routine_0++;
    func_8010ACA4(wp, 0);
    func_8010AB60(wp);
    Sound_call2(0x120, &wp->pos);
}

void func_8010A9E8(ST0C_SHOT *wp)
{
    if (func_80037694((STCOM23_WORK *)wp, 0) || wp->hit_7C)
    {
        if (wp->type & 0x40)
        {
            Close_SHL_WORK(wp);
        }
        else
        {
            Close_PL_SHL_WORK(wp);
        }
        func_8010ACA4(wp, 1);
        return;
    }
    wp->old_fpos = wp->fpos;
    wp->old_pos  = wp->pos;
    if (wp->timer_B-- != 0)
    {
        wp->fpos.w.x += wp->vel.x << 8;
        wp->fpos.w.y += wp->vel.y << 8;
        wp->fpos.w.z += wp->vel.z << 8;
        wp->model_pos_AC.x = wp->pos.x = wp->fpos.h.x;
        wp->model_pos_AC.y = wp->pos.y = wp->fpos.h.y;
        wp->model_pos_AC.z = wp->pos.z = wp->fpos.h.z;
    }
    else
    {
        if (wp->type & 0x40)
        {
            Close_SHL_WORK(wp);
        }
        else
        {
            Close_PL_SHL_WORK(wp);
        }
        return;
    }
    func_8010AB60(wp);
}

void func_8010AB60(ST0C_SHOT *wp)
{
    STCOM_SVECTOR p;
    sint32 flags;

    flags = func_800375D4(&Player_work, 2);
    p.x   = wp->pos.x * 2 - wp->old_pos.x;
    p.y   = wp->pos.y * 2 - wp->old_pos.y;
    p.z   = wp->pos.z * 2 - wp->old_pos.z;
    if (STAGE_PL.value_171 == 0)
    {
        flags = 0x1000;
    }
    if (wp->type & 0x40)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0xA000, wp->slot, &wp->col_C4, 0x8000005, 0, 0x80);
    }
    else if (wp->index_C)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x6000, wp->slot, &wp->col_C4, flags | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x4000, wp->slot, &wp->col_C4, flags | 0x8000000, 0, 0x80);
    }
}

void func_8010ACA4(ST0C_SHOT *wp, sint32 arg)
{
    ST0C_SHOT_FX *fx;

    fx = (ST0C_SHOT_FX *)func_80031618();
    if (fx)
    {
        fx->be_flag = 1;
        fx->id      = 0x85;
        fx->x_1C    = wp->pos.x;
        fx->y_1E    = wp->pos.y;
        fx->z_20    = wp->pos.z;
        fx->vx_30   = wp->vel.x;
        fx->vy_32   = wp->vel.y;
        fx->vz_34   = wp->vel.z;
        if (wp->type == 0x40)
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type == 0x41)
        {
            fx->value_40 = (wp->rot_y - 0x400) & 0xFFF;
            fx->flag_3   = arg + 0x10;
        }
        else if (wp->type == 0x42)
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
