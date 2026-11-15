#include "common.h"
#include "code_8004324C.h"
#include "code_8002E7A8.h"
#include "game.h"
#include "player.h"
#include "code_80037534.h"

sint32 func_8004324C(PL_WORK *pl)
{
    if ((pl->unk174 & 0xC0) || pl->unk177)
    {
        return 1;
    }
    return 0;
}

sint32 func_8004327C(sint32 amount)
{
    return -(Game_work.money < (uint32)-amount);
}

sint32 Money_add(sint32 amount, sint32 b, sint32 c)
{
    if (b == 0)
    {
        if (amount > 0)
        {
            Game_work.money += amount;
            if (Game_work.money > MONEY_MAX)
            {
                Game_work.money = MONEY_MAX;
            }
        }
        else
        {
            Game_work.money += amount;
            if (Game_work.money > MONEY_MAX)
            {
                Game_work.money = 0;
            }
            if (c)
            {
                Game_work.unk024 -= amount;
            }
            else
            {
                Game_work.unk020 -= amount;
            }
        }
    }
}

void func_80043340(sint32 amount, sint32 n)
{
    PL_WORK *pl;

    pl = &Player_work[n];
    pl->unk6E += amount;
    if (pl->unk6E > pl->unkB0)
    {
        pl->unk6E = pl->unkB0;
    }
    if (amount < 0 && n == 0)
    {
        Game_work.unk04C -= amount;
    }
}

void func_800433C0(WORK_10C *wp)
{
    D_8008A0CC[wp->routine_8](wp);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8004324C", func_800433FC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8004324C", func_800434F0);

void func_800435BC(WORK_10C *wp)
{
    PL_WORK *pl;

    pl         = func_80036294((uint8)wp->field_C);
    pl->unk198 = 0;
    func_80031930(wp);
}

void func_800435F8(WORK_10C *wp)
{
    sint32 id;
    PL_WORK *pl;

    id = wp->field_C;
    pl = func_80036294((uint8)id);
    if (wp->field_E)
    {
        *(SVECTOR *)&wp->x_14 = pl->joint_pos[11];
        if (id)
        {
            func_8003430C((SVECTOR *)&wp->x_14, 0x20, &wp->pos_2C, 0x20, 0x200, 0x6000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
        else
        {
            func_8003430C((SVECTOR *)&wp->x_14, 0x20, &wp->pos_2C, 0x20, 0x200, 0x4000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
    }
    else
    {
        *(SVECTOR *)&wp->x_14 = pl->joint_pos[14];
        if (id)
        {
            func_8003430C((SVECTOR *)&wp->x_14, 0x20, &wp->pos_2C, 0x20, 0x200, 0x6000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
        else
        {
            func_8003430C((SVECTOR *)&wp->x_14, 0x20, &wp->pos_2C, 0x20, 0x200, 0x4000, wp->kind_1, &wp->owner_C4, 0x28000008, 0, 0x80);
        }
    }
    wp->pos_2C = *(SVECTOR *)&wp->x_14;
}

void func_80043740(WORK_10C *wp)
{
    WORK_48 *e;

    e = func_80031618();
    if (e != 0)
    {
        e->routine_0        = 1;
        e->field_2          = 0x84;
        e->flag_3           = 0;
        e->u_18.s.pos_1C[0] = wp->x_14;
        e->u_18.s.pos_1C[1] = wp->y_16;
        e->u_18.s.pos_1C[2] = wp->z_18;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8004324C", func_800437A8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8004324C", func_800437F8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8004324C", func_80043A8C);

void func_80043DF8(void)
{
}

void func_80043E00(WORK_10C *wp, uint8 arg)
{
    WORK_48 *e;

    e = func_80031618();
    if (e != 0)
    {
        e->routine_0        = 9;
        e->field_2          = 0x82;
        e->u_18.s.pos_1C[0] = wp->x_14;
        e->u_18.s.pos_1C[1] = wp->y_16;
        e->u_18.s.pos_1C[2] = wp->z_18;
        e->flag_3           = 1;
        e->field_C.rec.b0   = arg;
    }
}

void func_80043E78(WORK_10C *wp)
{
    uint32 pad;
    sint32 val;

    pad = wp->field_98;
    val = func_800375D4(Player_work, 1);
    if (wp->field_C)
    {
        func_8003430C((SVECTOR *)&wp->x_14, pad, &wp->pos_2C, pad, 0x200, 0x6000, wp->kind_1, &wp->owner_C4, val | 0x8000000, 0, 0x80);
    }
    else
    {
        func_8003430C((SVECTOR *)&wp->x_14, pad, &wp->pos_2C, pad, 0x200, 0x4000, wp->kind_1, &wp->owner_C4, val | 0x8000000, 0, 0x80);
    }
}
