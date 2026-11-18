#include "common.h"
#include "rock_neo.exe/code_800425fc.h"

void func_800425FC(C800425FC_COLORS *wp, sint32 idx)
{
    uint32 i;

    for (i = 0; i < 16; i++)
    {
        wp->src[i] = D_8008A04C[idx][i];
    }
    wp->out[0]  = wp->src[0] | wp->src[1];
    wp->out[1]  = wp->src[0];
    wp->out[2]  = wp->src[4] | wp->src[5];
    wp->out[3]  = wp->src[5];
    wp->out[4]  = wp->src[4] | wp->src[5];
    wp->out[5]  = wp->src[4];
    wp->out[6]  = wp->src[0] | wp->src[1];
    wp->out[7]  = wp->src[0];
    wp->out[8]  = wp->src[0] | wp->src[1];
    wp->out[9]  = wp->src[1];
    wp->out[10] = wp->src[4] | wp->src[5];
    wp->out[11] = wp->src[4];
    wp->out[12] = wp->src[4] | wp->src[5];
    wp->out[13] = wp->src[5];
    wp->out[14] = wp->src[0] | wp->src[1];
    wp->out[15] = wp->src[1];
}

void func_800426F8(C800425FC_WORK *wp)
{
    D_8008A08C[wp->routine_170](wp);
}

void func_80042734(C800425FC_WORK *wp)
{
    D_8008A0C4[wp->routine_171](wp);
}

void func_80042770(C800425FC_ACT *ap)
{
    sint32 act;
    uint16 pad;
    uint8 dir;

    act = ap->routine_170;
    pad = ap->h11c;
    switch ((sint8)ap->b178)
    {
        case 0:
            if (ap->b100 == D_80089A84[act * 12])
            {
                ap->b178 += 2;
                ap->b174 |= 0x10;
            }
            break;
        case 1:
            if (!(ap->b174 & 4))
            {
                func_800320B8(ap, ap->b0ac, D_80089A84[act * 12]);
            }
            dir      = func_80042458(ap);
            ap->b104 = dir;
            func_800321C8(ap, ap->b174 & 3, dir, D_80089A84[act * 12]);
            ap->b178++;
            ap->b174 |= 0x10;
            break;
        case 2:
            ap->b174 &= 0xCF;
            if (D_80089A87[act * 12] != 0 && ap->parts[act].h06 > 0)
            {
                if (ap->b100 != D_80089A85[act * 12] + func_80037664(ap, act))
                {
                    break;
                }
                ap->b178++;
            }
            else
            {
                ap->b178 += 2;
                break;
            }
            // fall through
        case 3:
            if (ap->b100 == D_80089A86[act * 12])
            {
                ap->b178++;
            }
            else if ((ap->h13c & pad) && (ap->b175 & 3) == 3)
            {
                ap->b174 = 0;
                ap->b177 = 2;
            }
            break;
        case 4:
            if (ap->s103 == -1)
            {
                ap->b174 = 0;
                ap->b177 = 0;
                if (act == 0)
                {
                    ap->h44.u = 0;
                }
            }
            break;
    }
    if (act == 0)
    {
        if (Game_work[0x83] == 0)
        {
            if (ap->w198 != 0)
            {
                ap->h44.s = -0x300;
            }
            else
            {
                ap->h44.u += 0x80;
                if (ap->h44.s > 0)
                {
                    ap->h44.u = 0;
                }
            }
            func_80041E90(ap, ap->h44.s, 0, 0);
        }
        else
        {
            ap->h44.u = 0;
        }
    }
}

void func_80042A40(C800425FC_ACT *ap)
{
    sint32 act;

    act = ap->routine_170;
    switch ((sint8)ap->b178)
    {
        case 0:
            if (ap->b100 != D_80089A84[act * 12])
            {
                ap->h44.u = 0;
            }
            else
            {
                ap->b178 = ap->b178 + 2;
                ap->b174 |= 0x10;
                if (Game_work[0x83] == 1)
                {
                    ap->h44.u = 0;
                }
                else
                {
                    ap->h44.s = -0x300;
                }
            }
            break;
        case 1:
        case 2:
            ap->b174 &= 0xCF;
            ap->b178++;
            break;
        case 3:
            if (ap->s103 == -1)
            {
                ap->b174 = 0;
                ap->b177 = 0;
            }
            break;
    }
    ap->h44.u += 0xE0;
    if (ap->h44.s < 0)
    {
        func_80041E90(ap, ap->h44.s, 0, 0);
        return;
    }
    ap->h44.u = 0;
}

void func_80042B58(C800425FC_ACT *ap)
{
    sint32 act;
    uint16 pad;
    sint8 hit;

    act = ap->routine_170;
    pad = ap->h11c;
    switch ((sint8)ap->b178)
    {
        case 0:
            if (ap->b100 == D_80089A84[act * 12])
            {
                ap->b178 += 2;
                ap->b174 |= 0x10;
            }
            break;
        case 1:
        case 2:
            ap->b174 &= 0xCF;
            if (ap->b100 >= D_80089A86[act * 12])
            {
                // The second read of each table byte goes through the base symbol;
                // the same spelling twice lets GCC keep the whole address live.
                func_800320B8(ap, ap->b0ac, D_80089A85[act * 12]);
                func_800321C8(ap, ap->b174 & 3, ap->b104, D_80089A84[act * 12 + 1]);
            }
            if (!(pad & ap->h13c) || ap->parts[act].h06 <= 0)
            {
                ap->b110 = 0;
                ap->b178++;
            }
            break;
        case 3:
            func_800320B8(ap, ap->b0ac, D_80089A86[act * 12]);
            func_800321C8(ap, ap->b174 & 3, ap->b104, D_80089A84[act * 12 + 2]);
            ap->b110 = 0;
            ap->b178++;
            break;
        case 4:
            if (ap->s103 == -1)
            {
                ap->b174 = 0;
                ap->b177 = 0;
                ap->b110 = 0;
            }
            break;
    }
    if (act == 12)
    {
        if (Game_work[0x83] == 0)
        {
            hit = ap->s44c;
            if (hit != 0)
            {
                if (hit & 2)
                {
                    ap->h44.s = -0x280;
                }
                if (ap->s44c & 1)
                {
                    ap->b110 = -1;
                }
                ap->s44c = 0;
            }
            if (ap->b009 == 0 || ap->b009 == 4 || ap->b009 == 14)
            {
                ap->h44.u += 0x80;
                if (ap->h44.s > 0)
                {
                    ap->h44.u = 0;
                    ap->b110  = 0;
                }
            }
            func_80041E90(ap, ap->h44.s, 0, 0);
        }
        else
        {
            ap->h44.u = 0;
        }
    }
    if (ap->s074 != 0)
    {
        Pl00_shot_enable_off(ap);
        ap->b110 = 0;
    }
}

void func_80042DF8(C800425FC_ACT *ap)
{
    sint32 act;

    act = ap->routine_170;
    switch ((sint8)ap->b178)
    {
        case 0:
            if (ap->b100 == D_80089A84[act * 12])
            {
                ap->b178 = ap->b178 + 1;
                ap->b174 |= 0x10;
            }
            if (Game_work[0x83] != 1)
            {
                ap->h44.u = 0x90;
            }
            else
            {
                ap->h44.u = 0;
            }
            break;
        case 1:
            ap->b174 &= 0xCF;
            if (ap->b100 == D_80089A85[act * 12])
            {
                ap->h44.u = 0;
                ap->b178++;
            }
            break;
        case 2:
            if (ap->b100 >= D_80089A86[act * 12])
            {
                if (Game_work[0x83] == 1)
                {
                    ap->h44.u = 0;
                }
                else
                {
                    ap->h44.u = 0x60;
                }
                ap->b178++;
            }
            break;
        case 3:
            if (ap->s103 == -1)
            {
                ap->b174  = 0;
                ap->b177  = 0;
                ap->h44.u = 0;
            }
            break;
    }
    func_80041E90(ap, ap->h44.s, 0, 0);
}

void func_80042F78(C800425FC_ACT *ap)
{
    sint32 act;
    uint16 pad;
    uint8 dir;

    act = ap->routine_171;
    pad = ap->h11c;
    switch ((sint8)ap->b178)
    {
        case 0:
            if (ap->b100 == D_80089A84[act * 12])
            {
                ap->b178 += 2;
                ap->b174 |= 0x20;
            }
            break;
        case 1:
            if (!(ap->b174 & 4))
            {
                func_800320B8(ap, ap->b0ac, D_80089A84[act * 12]);
            }
            dir      = func_800423DC(ap);
            ap->b104 = dir;
            func_800321C8(ap, ap->b174 & 3, dir, D_80089A84[act * 12]);
            ap->b178++;
            ap->b174 |= 0x20;
            break;
        case 2:
            ap->b174 &= 0xCF;
            if (D_80089A87[act * 12] != 0 && ap->parts[act].h06 > 0)
            {
                if (ap->b100 != D_80089A85[act * 12] + func_80037664(ap, act))
                {
                    break;
                }
                ap->b178++;
            }
            else
            {
                ap->b178 += 2;
                break;
            }
            // fall through
        case 3:
            if (ap->b100 == D_80089A86[act * 12])
            {
                ap->b178++;
            }
            else if ((pad & ap->h13a) && (ap->b175 & 5) == 5)
            {
                ap->b174 = 0;
                ap->b177 = 1;
            }
            break;
        case 4:
            if (ap->s103 == -1)
            {
                ap->b174 = 0;
                ap->b177 = 0;
                if (act == 0)
                {
                    ap->h44.u = 0;
                }
            }
            break;
    }
    if (act == 0)
    {
        if (Game_work[0x83] == 0)
        {
            if (ap->w198 != 0)
            {
                ap->w198  = 0;
                ap->h44.s = -0x300;
            }
            else
            {
                ap->h44.u += 0x80;
                if (ap->h44.s > 0)
                {
                    ap->h44.u = 0;
                }
            }
            func_80041E90(ap, ap->h44.s, 0, 0);
        }
        else
        {
            ap->h44.u = 0;
        }
    }
}
