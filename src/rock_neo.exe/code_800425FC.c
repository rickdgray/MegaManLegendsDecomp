#include "common.h"
#include "code_800425FC.h"
#include "code_80037534.h"
#include "game.h"
#include "player.h"

void func_800425FC(PL_WORK *pl, sint32 row)
{
    uint32 i;

    for (i = 0; i < 16; i++)
    {
        pl->keys_124[i] = D_8008A04C[row][i];
    }
    pl->key_pair[0][0] = pl->keys_124[0] | pl->keys_124[1];
    pl->key_pair[0][1] = pl->keys_124[0];
    pl->key_pair[1][0] = pl->keys_124[4] | pl->keys_124[5];
    pl->key_pair[1][1] = pl->keys_124[5];
    pl->key_pair[2][0] = pl->keys_124[4] | pl->keys_124[5];
    pl->key_pair[2][1] = pl->keys_124[4];
    pl->key_pair[3][0] = pl->keys_124[0] | pl->keys_124[1];
    pl->key_pair[3][1] = pl->keys_124[0];
    pl->key_pair[4][0] = pl->keys_124[0] | pl->keys_124[1];
    pl->key_pair[4][1] = pl->keys_124[1];
    pl->key_pair[5][0] = pl->keys_124[4] | pl->keys_124[5];
    pl->key_pair[5][1] = pl->keys_124[4];
    pl->key_pair[6][0] = pl->keys_124[4] | pl->keys_124[5];
    pl->key_pair[6][1] = pl->keys_124[5];
    pl->key_pair[7][0] = pl->keys_124[0] | pl->keys_124[1];
    pl->key_pair[7][1] = pl->keys_124[1];
}

void func_800426F8(PL_WORK *pl)
{
    D_8008A08C[pl->unk170](pl);
}

void func_80042734(PL_WORK *pl)
{
    D_8008A0C4[pl->unk171](pl);
}

void func_80042770(PL_WORK *pl)
{
    sint32 n;
    uint16 mask;

    n    = pl->unk170;
    mask = pl->unk11C;
    switch (pl->unk178)
    {
        case 0:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_0)
            {
                pl->unk178 += 2;
                pl->unk174 |= 0x10;
            }
            break;
        case 1:
            if (!(pl->unk174 & 4))
            {
                func_800320B8(pl, pl->idx_AC, D_80089A84[n].key_0);
            }
            pl->set_104 = func_80042458(pl);
            func_800321C8(pl, pl->unk174 & 3, pl->set_104, D_80089A84[n].key_0);
            pl->unk178++;
            pl->unk174 |= 0x10;
            break;
        case 2:
            pl->unk174 &= 0xCF;
            if (D_80089A84[n].flag_3 != 0 && pl->rec[n].val > 0)
            {
                if (pl->cmd_100.b.b0 != D_80089A84[n].key_1 + func_80037664(pl, n))
                {
                    break;
                }
                pl->unk178++;
            }
            else
            {
                pl->unk178 += 2;
                break;
            }
            // fall through
        case 3:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_2)
            {
                pl->unk178++;
                break;
            }
            if ((pl->keys_124[12] & mask) && (pl->unk175 & 3) == 3)
            {
                pl->unk174 = 0;
                pl->unk177 = 2;
            }
            break;
        case 4:
            if (pl->cmd_100.b.ctl == -1)
            {
                pl->unk174 = 0;
                pl->unk177 = 0;
                if (n == 0)
                {
                    pl->spd.vx = 0;
                }
            }
            break;
    }
    if (n == 0)
    {
        if (Game_work.unk083 == 0)
        {
            if (pl->unk198 != 0)
            {
                pl->spd.vx = -0x300;
            }
            else
            {
                pl->spd.vx += 0x80;
                if (pl->spd.vx > 0)
                {
                    pl->spd.vx = 0;
                }
            }
            func_80041E90(pl, pl->spd.vx, 0, 0);
        }
        else
        {
            pl->spd.vx = 0;
        }
    }
}

void func_80042A40(PL_WORK *pl)
{
    sint32 n;

    n = pl->unk170;
    switch (pl->unk178)
    {
        case 0:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_0)
            {
                pl->unk178 += 2;
                pl->unk174 |= 0x10;
                if (Game_work.unk083 == 1)
                {
                    pl->spd.vx = 0;
                }
                else
                {
                    pl->spd.vx = -0x300;
                }
            }
            else
            {
                pl->spd.vx = 0;
            }
            break;
        case 1:
        case 2:
            pl->unk174 &= 0xCF;
            pl->unk178++;
            break;
        case 3:
            if (pl->cmd_100.b.ctl == -1)
            {
                pl->unk174 = 0;
                pl->unk177 = 0;
            }
            break;
    }
    pl->spd.vx += 0xE0;
    if (pl->spd.vx < 0)
    {
        func_80041E90(pl, pl->spd.vx, 0, 0);
    }
    else
    {
        pl->spd.vx = 0;
    }
}

void func_80042B58(PL_WORK *pl)
{
    sint32 n;
    uint16 mask;

    n    = pl->unk170;
    mask = pl->unk11C;
    switch (pl->unk178)
    {
        case 0:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_0)
            {
                pl->unk178 += 2;
                pl->unk174 |= 0x10;
            }
            break;
        case 1:
        case 2:
            pl->unk174 &= 0xCF;
            if (pl->cmd_100.b.b0 >= D_80089A84[n].key_2)
            {
                func_800320B8(pl, pl->idx_AC, D_80089A84[n].key_1);
                func_800321C8(pl, pl->unk174 & 3, pl->set_104, D_80089A84[n].key_1);
            }
            if ((mask & pl->keys_124[12]) && pl->rec[n].val > 0)
            {
                break;
            }
            pl->unk110 = 0;
            pl->unk178++;
            break;
        case 3:
            func_800320B8(pl, pl->idx_AC, D_80089A84[n].key_2);
            func_800321C8(pl, pl->unk174 & 3, pl->set_104, D_80089A84[n].key_2);
            pl->unk110 = 0;
            pl->unk178++;
            break;
        case 4:
            if (pl->cmd_100.b.ctl == -1)
            {
                pl->unk174 = 0;
                pl->unk177 = 0;
                pl->unk110 = 0;
            }
            break;
    }
    if (n == 12)
    {
        if (Game_work.unk083 == 0)
        {
            if (pl->unk44C != 0)
            {
                if (pl->unk44C & 2)
                {
                    pl->spd.vx = -0x280;
                }
                if (pl->unk44C & 1)
                {
                    pl->unk110 = -1;
                }
                pl->unk44C = 0;
            }
            if (pl->routine_9 == 0 || pl->routine_9 == 4 || pl->routine_9 == 14)
            {
                pl->spd.vx += 0x80;
                if (pl->spd.vx > 0)
                {
                    pl->spd.vx = 0;
                    pl->unk110 = 0;
                }
            }
            func_80041E90(pl, pl->spd.vx, 0, 0);
        }
        else
        {
            pl->spd.vx = 0;
        }
    }
    if (pl->field_74 != 0)
    {
        Pl00_shot_enable_off(pl);
        pl->unk110 = 0;
    }
}

void func_80042DF8(PL_WORK *pl)
{
    sint32 n;

    n = pl->unk170;
    switch (pl->unk178)
    {
        case 0:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_0)
            {
                pl->unk178++;
                pl->unk174 |= 0x10;
            }
            if (Game_work.unk083 == 1)
            {
                pl->spd.vx = 0;
            }
            else
            {
                pl->spd.vx = 0x90;
            }
            break;
        case 1:
            pl->unk174 &= 0xCF;
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_1)
            {
                pl->spd.vx = 0;
                pl->unk178++;
            }
            break;
        case 2:
            if (pl->cmd_100.b.b0 >= D_80089A84[n].key_2)
            {
                if (Game_work.unk083 == 1)
                {
                    pl->spd.vx = 0;
                }
                else
                {
                    pl->spd.vx = 0x60;
                }
                pl->unk178++;
            }
            break;
        case 3:
            if (pl->cmd_100.b.ctl == -1)
            {
                pl->unk174 = 0;
                pl->unk177 = 0;
                pl->spd.vx = 0;
            }
            break;
    }
    func_80041E90(pl, pl->spd.vx, 0, 0);
}

// Near twin of func_80042770, for PL_WORK.unk171.
void func_80042F78(PL_WORK *pl)
{
    sint32 n;
    uint16 mask;

    n    = pl->unk171;
    mask = pl->unk11C;
    switch (pl->unk178)
    {
        case 0:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_0)
            {
                pl->unk178 += 2;
                pl->unk174 |= 0x20;
            }
            break;
        case 1:
            if (!(pl->unk174 & 4))
            {
                func_800320B8(pl, pl->idx_AC, D_80089A84[n].key_0);
            }
            pl->set_104 = func_800423DC(pl);
            func_800321C8(pl, pl->unk174 & 3, pl->set_104, D_80089A84[n].key_0);
            pl->unk178++;
            pl->unk174 |= 0x20;
            break;
        case 2:
            pl->unk174 &= 0xCF;
            if (D_80089A84[n].flag_3 != 0 && pl->rec[n].val > 0)
            {
                if (pl->cmd_100.b.b0 != D_80089A84[n].key_1 + func_80037664(pl, n))
                {
                    break;
                }
                pl->unk178++;
            }
            else
            {
                pl->unk178 += 2;
                break;
            }
            // fall through
        case 3:
            if (pl->cmd_100.b.b0 == D_80089A84[n].key_2)
            {
                pl->unk178++;
                break;
            }
            if ((mask & pl->keys_124[11]) && (pl->unk175 & 5) == 5)
            {
                pl->unk174 = 0;
                pl->unk177 = 1;
            }
            break;
        case 4:
            if (pl->cmd_100.b.ctl == -1)
            {
                pl->unk174 = 0;
                pl->unk177 = 0;
                if (n == 0)
                {
                    pl->spd.vx = 0;
                }
            }
            break;
    }
    if (n == 0)
    {
        if (Game_work.unk083 == 0)
        {
            if (pl->unk198 != 0)
            {
                pl->unk198 = 0;
                pl->spd.vx = -0x300;
            }
            else
            {
                pl->spd.vx += 0x80;
                if (pl->spd.vx > 0)
                {
                    pl->spd.vx = 0;
                }
            }
            func_80041E90(pl, pl->spd.vx, 0, 0);
        }
        else
        {
            pl->spd.vx = 0;
        }
    }
}
