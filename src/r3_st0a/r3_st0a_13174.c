#include "common.h"
#include "st0a.h"

void func_80113174(STAGE_OBJ *wp)
{
    D_8011656C[wp->routine_0](wp);
    func_80051BAC(wp);
}

void func_801131C4(ST0A_SHL *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR v;

    wp->col_c4 = 0;
    wp->col_c8 = 0;
    wp->box_78 = D_80116560;
    wp->be_flag |= TRANS | MODEL;
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
        switch (ST0A_PL_SBYTE(0x508))
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
    if (!(wp->type & 0x40) && ST0A_PL_SBYTE(0x507) >= 3)
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
    func_80113888(wp, 0);
    func_80113744(wp);
    Sound_call2(0x120, &wp->pos);
}

void func_801135CC(ST0A_SHOT *wp)
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
        func_80113888(wp, 1);
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
    func_80113744(wp);
}

void func_80113744(ST0A_SHOT *wp)
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
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0xA000, wp->work_id, &wp->col_C4, 0x8000005, 0, 0x80);
    }
    else if (wp->index_C)
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x6000, wp->work_id, &wp->col_C4, flags | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&p, 0x20, &wp->pos, 0x20, 0x200, 0x4000, wp->work_id, &wp->col_C4, flags | 0x8000000, 0, 0x80);
    }
}

void func_80113888(ST0A_SHOT *wp, sint32 arg)
{
    ST0A_SHOT_FX *fx;

    fx = (ST0A_SHOT_FX *)func_80031618();
    if (fx)
    {
        fx->be_flag = MOVE;
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
            fx->type     = arg + 0x10;
        }
        else if (wp->type == 0x41)
        {
            fx->value_40 = (wp->rot_y - 0x400) & 0xFFF;
            fx->type     = arg + 0x10;
        }
        else if (wp->type == 0x42)
        {
            fx->value_40 = 0xFFFF;
            fx->type     = arg + 0x10;
        }
        else
        {
            fx->value_40 = (wp->rot_y + 0x400) & 0xFFF;
            fx->type     = arg;
        }
    }
}

void func_80113988(STAGE_SPARK *wp)
{
    STAGE_OBJ *owner;

    owner = wp->owner_2C;
    if (--wp->timer_D == 0 || owner->routine_0 == 2)
    {
        wp->timer_D = 0;
        wp->routine_0++;
    }
    wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
    wp->w_24 += wp->type_F;
    wp->y_1E += wp->rise_28;
}

void func_80113A14(STAGE_SPARK *wp)
{
    wp->be_flag |= TRANS;
    wp->routine_0++;
    func_80113988(wp);
}

void func_80113A48(STAGE_OBJ *wp)
{
    func_80031988(wp);
}

void func_80113A68(STAGE_OBJ *wp)
{
    D_80116574[wp->routine_0](wp);
}

void func_80113AA4(ST0A_SPARK *wp)
{
    ST0A_SPARK *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->be_flag  = MOVE;
            ep->type     = 1;
            ep->flags    = wp->flags;
            ep->work_0   = 0;
            ep->timer_D  = (rand() & 7) * 2 + 0x40;
            ep->x_1C     = wp->x_1C + (rand() & 0xF);
            ep->y_1E     = wp->y_1E;
            ep->z_20     = wp->z_20 + (rand() & 0xF);
            ep->mode_14  = 0x3D48004E;
            ep->u_22     = ((rand() & 3) << 5) + 0x20;
            ep->v_23     = 0;
            ep->w_24     = wp->width_E;
            ep->type_F   = wp->type_F;
            ep->rise_28  = wp->rise_28;
            ep->owner_2C = wp;
            for (i = 0; i < wp->count_26; i++)
            {
                func_80113A68(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_80113BEC(STAGE_OBJ *wp)
{
    if (wp->type == 1)
    {
        func_80113A68(wp);
        return;
    }
    if (wp->routine_0 != 2)
    {
        func_80113AA4(wp);
        return;
    }
    func_80031988((STCOM_EFFECT *)wp);
}

ST0A_SPARK *func_80113C4C(STAGE_XYZ *pos, sint32 width, sint32 growth, sint16 count, sint32 rise, uint8 flag)
{
    ST0A_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = MOVE;
        ep->id       = 0;
        ep->type     = 0;
        ep->work_0   = 0;
        ep->width_E  = width;
        ep->type_F   = growth;
        ep->x_1C     = pos->x;
        ep->y_1E     = pos->y;
        ep->z_20     = pos->z;
        ep->count_26 = count;
        if (flag)
        {
            ep->flags |= 0x20;
        }
        else
        {
            ep->flags &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < count; i++)
        {
            func_80113AA4(ep);
        }
    }
    return ep;
}
