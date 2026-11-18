#include "common.h"
#include "code_8004324c.h"

sint32 func_8004324C(CODE43_FLAGS *wp)
{
    if ((wp->flags_174 & 0xC0) || wp->value_177)
    {
        return 1;
    }
    return 0;
}

sint32 func_8004327C(sint32 amount)
{
    return -(Game_work.money_1c < (uint32)-amount);
}

void func_80043294(sint32 amount, sint32 arg1, sint32 alt)
{
    if (arg1 == 0)
    {
        if (amount > 0)
        {
            Game_work.money_1c += amount;
            if (Game_work.money_1c > CODE43_MONEY_MAX)
            {
                Game_work.money_1c = CODE43_MONEY_MAX;
            }
        }
        else
        {
            Game_work.money_1c += amount;
            if (Game_work.money_1c > CODE43_MONEY_MAX)
            {
                Game_work.money_1c = 0;
            }
            if (alt)
            {
                Game_work.spent_24 -= amount;
            }
            else
            {
                Game_work.spent_20 -= amount;
            }
        }
    }
}

void func_80043340(sint32 amount, sint32 index)
{
    CODE43_PLAYER *pl = &Player_work[index];

    pl->hp_6e += amount;
    if ((sint16)pl->hp_6e > pl->hp_max_b0)
    {
        pl->hp_6e = pl->hp_max_b0;
    }
    if (amount < 0 && index == 0)
    {
        Game_work.hp_lost_4c -= amount;
    }
}

void func_800433C0(CODE43_WORK *wp)
{
    D_8008A0CC[wp->routine_8](wp);
}

void func_800433FC(CODE43_WORK *wp)
{
    CODE43_SVECTOR unused[3];
    CODE43_TARGET *target;

    wp->mode_e        = wp->pos_14.pad;
    target            = func_80036294(wp->index_c);
    target->state_198 = 0;
    func_800354E0(wp->bit_d);
    wp->timer_b = 0xB;
    wp->word_c4 = 0;
    wp->word_c8 = 0;
    wp->ptr_78  = 0;
    wp->routine_8++;
    if (wp->mode_e)
    {
        wp->pos_2c = target->pos_400;
    }
    else
    {
        wp->pos_2c = target->pos_418;
    }
    wp->pos_14 = wp->pos_2c;
    func_800435F8(wp);
    Sound_call2(0x96, &wp->pos_14);
}

void func_800434F0(CODE43_WORK *wp)
{
    CODE43_TARGET *target;

    target     = func_80036294(wp->index_c);
    wp->pos_2c = func_80036294(wp->index_c)->pos_14;
    if (--wp->timer_b == 0)
    {
        func_80031930(wp);
    }
    else if (func_80037694(wp, 0))
    {
        func_80043740(wp);
        wp->routine_8++;
        target->state_198 = 1;
    }
    else
    {
        func_800435F8(wp);
    }
}

void func_800435BC(CODE43_WORK *wp)
{
    func_80036294(wp->index_c)->state_198 = 0;
    func_80031930(wp);
}

void func_800435F8(CODE43_WORK *wp)
{
    sint32 id;
    CODE43_TARGET *target;

    id     = wp->index_c;
    target = func_80036294(id);
    if (wp->mode_e)
    {
        wp->pos_14 = target->pos_400;
        if (id)
        {
            func_8003430C(&wp->pos_14, 0x20, &wp->pos_2c, 0x20, 0x200, 0x6000, wp->value_1,
                          &wp->word_c4, 0x28000008, 0, 0x80);
        }
        else
        {
            func_8003430C(&wp->pos_14, 0x20, &wp->pos_2c, 0x20, 0x200, 0x4000, wp->value_1,
                          &wp->word_c4, 0x28000008, 0, 0x80);
        }
    }
    else
    {
        wp->pos_14 = target->pos_418;
        if (id)
        {
            func_8003430C(&wp->pos_14, 0x20, &wp->pos_2c, 0x20, 0x200, 0x6000, wp->value_1,
                          &wp->word_c4, 0x28000008, 0, 0x80);
        }
        else
        {
            func_8003430C(&wp->pos_14, 0x20, &wp->pos_2c, 0x20, 0x200, 0x4000, wp->value_1,
                          &wp->word_c4, 0x28000008, 0, 0x80);
        }
    }
    wp->pos_2c = wp->pos_14;
}

void func_80043740(CODE43_WORK *wp)
{
    CODE43_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->flags_0 = 1;
        fx->kind_2  = 0x84;
        fx->value_3 = 0;
        fx->x_1c    = wp->pos_14.x;
        fx->y_1e    = wp->pos_14.y;
        fx->z_20    = wp->pos_14.z;
    }
}

void func_800437A8(CODE43_WORK *wp)
{
    D_8008A0D8[wp->routine_8](wp);
    func_80051BAC(wp);
}

void func_800437F8(CODE43_WORK *wp)
{
    CODE43_SVECTOR rot;
    CODE43_VECTOR vec;
    CODE43_MATRIX mtx;
    sint32 speed;
    uint32 word;

    wp->flags_0 |= 0x2A;
    wp->flags_6 |= 0x20;
    func_8005D97C();
    wp->word_c4 = 0;
    wp->word_c8 = 0;
    wp->ptr_78  = D_80097DA0;
    rot.vx      = func_80039B80();
    rot.vy      = wp->angle_64 & 0xFFF;
    rot.vz      = 0;
    RotMatrixYXZ(&rot, &mtx);
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = -0x1000;
    ApplyMatrix(&mtx, &rot, &vec);
    rot.vy       = vec.vy;
    rot.vx       = vec.vx;
    rot.vz       = vec.vz;
    speed        = D_80097DD4[Player_work[0].speed_idx_4fe];
    wp->vel_44   = (rot.vx * speed) >> 4;
    wp->vel_46   = (rot.vy * speed) >> 4;
    wp->vel_48   = (rot.vz * speed) >> 4;
    wp->pos_a4   = rot;
    wp->value_4c = 0;
    wp->value_4e = 0;
    wp->value_50 = 0;
    wp->word_88  = 0x3D48002E; // overwritten below; retail stores both
    word         = D_80097DAC[Player_work[0].speed_idx_4fc];
    wp->x_90 = wp->pos_14.x = wp->pos_1c.h.x_1e;
    wp->word_8c             = 0x2E808080;
    wp->y_92 = wp->pos_14.y = wp->pos_1c.h.y_22;
    wp->z_94 = wp->pos_14.z = wp->pos_1c.h.z_26;
    wp->word_88             = word;
    wp->vec_34              = wp->pos_1c.v;
    wp->pos_2c              = wp->pos_14;
    wp->value_96            = 0xC0;
    wp->value_97            = 0x60;
    wp->value_98            = D_80097DCC[Player_work[0].speed_idx_4fc];
    wp->value_7c            = 0;
    wp->timer_b             = 0;
    func_80043DF8(wp, &mtx);
    wp->routine_9 = 0;
    wp->routine_8++;
    if (wp->mode_a)
    {
        wp->pos_2c.pad = wp->pos_14.pad = 0x6208;
    }
    else
    {
        wp->pos_2c.pad = wp->pos_14.pad = 0x4208;
    }
    if (wp->value_3 >= 0x80 && (wp->target.w.w_bc | wp->target.w.w_c0) == 0)
    {
        func_800354E0(wp->bit_d);
        wp->value_3 = 0;
    }
    func_80043E78(wp);
    Sound_call2(0x9A, &wp->pos_14);
}

// The first arm ends with its own copy of the timeout tail (func_80031930 and the
// func_800354E0 check); cross-jumping then merges the two func_80043E00 calls into one, as in
// retail.
void func_80043A8C(CODE43_WORK *wp)
{
    sint32 result;
    sint32 timer;
    sint32 speed;
    CODE43_SVECTOR step;
    CODE43_SVECTOR dir;
    CODE43_VECTOR delta;

    result = func_80037694(wp, 0);
    if (result != 0 || wp->value_7c != 0)
    {
        if (result == 0x7FFF)
        {
            func_80043E00(wp, 0);
        }
        else
        {
            func_80043E00(wp, 1);
        }
        func_80031930(wp);
        if (wp->value_3 >= 0x80)
        {
            func_800354E0(wp->bit_d);
        }
        return;
    }
    else
    {
        wp->vec_34 = wp->pos_1c.v;
        wp->pos_2c = wp->pos_14;
        timer      = wp->timer_b++;
        if (timer < func_80037634(Player_work, 1))
        {
            if (wp->value_3 >= 0x80)
            {
                if (wp->target.w.w_bc | wp->target.w.w_c0)
                {
                    delta.vx = wp->target.h.x_bc - (sint16)wp->pos_14.x;
                    delta.vy = wp->target.h.y_be - (sint16)wp->pos_14.y;
                    delta.vz = wp->target.h.z_c0 - (sint16)wp->pos_14.z;
                    if ((uint32)(delta.vx + 0x687E) > 0xD0FC ||
                        (uint32)(delta.vy + 0x687E) > 0xD0FC ||
                        (uint32)(delta.vz + 0x687E) > 0xD0FC)
                    {
                        delta.vx >>= 2;
                        delta.vy >>= 2;
                        delta.vz >>= 2;
                    }
                    VectorNormalS(&delta, &dir);
                    if (wp->timer_b < 4)
                    {
                        func_80033F04(&step, &dir, &wp->pos_a4, 0x424, 0xF746EA4);
                    }
                    else if (wp->timer_b < 9)
                    {
                        func_80033F04(&step, &dir, &wp->pos_a4, 0x8F, 0xFFD813C);
                    }
                    else
                    {
                        func_80033F04(&step, &dir, &wp->pos_a4, 0x47, 0xFFF604C);
                        func_800354E0(wp->bit_d);
                        wp->value_3 = 0;
                    }
                    wp->pos_a4 = step;
                    speed      = D_80097DD4[Player_work[0].speed_idx_4fe];
                    wp->vel_44 = (step.vx * speed) >> 4;
                    wp->vel_46 = (step.vy * speed) >> 4;
                    wp->vel_48 = (step.vz * speed) >> 4;
                }
                else
                {
                    func_800354E0(wp->bit_d);
                    wp->value_3 = 0;
                }
            }
            wp->pos_1c.v.vx += wp->vel_44 << 8;
            wp->pos_1c.v.vy += wp->vel_46 << 8;
            wp->pos_1c.v.vz += wp->vel_48 << 8;
            wp->x_90 = wp->pos_14.x = wp->pos_1c.h.x_1e;
            wp->y_92 = wp->pos_14.y = wp->pos_1c.h.y_22;
            wp->value_9a += 5;
            wp->z_94 = wp->pos_14.z = wp->pos_1c.h.z_26;
            goto move;
        }
    }
    func_80031930(wp);
    if (wp->value_3 >= 0x80)
    {
        func_800354E0(wp->bit_d);
    }
    return;
move:
    func_80043E78(wp);
}

void func_80043DF8(CODE43_WORK *wp, CODE43_MATRIX *mtx)
{
}

void func_80043E00(CODE43_WORK *wp, sint32 value)
{
    CODE43_FX *fx;

    fx = func_80031618();
    if (fx)
    {
        fx->flags_0 = 9;
        fx->kind_2  = 0x82;
        fx->x_1c    = wp->pos_14.x;
        fx->y_1e    = wp->pos_14.y;
        fx->z_20    = wp->pos_14.z;
        fx->value_3 = 1;
        fx->value_c = value;
    }
}

void func_80043E78(CODE43_WORK *wp)
{
    sint32 size;
    sint32 flags;

    size  = wp->value_98;
    flags = func_800375D4(Player_work, 1);
    if (wp->index_c)
    {
        func_8003430C(&wp->pos_14, size, &wp->pos_2c, size, 0x200, 0x6000, wp->value_1,
                      &wp->word_c4, flags | 0x08000000, 0, 0x80);
    }
    else
    {
        func_8003430C(&wp->pos_14, size, &wp->pos_2c, size, 0x200, 0x4000, wp->value_1,
                      &wp->word_c4, flags | 0x08000000, 0, 0x80);
    }
}
