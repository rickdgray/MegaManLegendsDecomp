#include "common.h"
#include "st06.h"

void func_80121560(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        D_8012B94C[wp->variant_3](wp);
    }
    else
    {
        D_8012B950[wp->variant_3](wp);
    }
}

void func_801215CC(STAGE_FX *wp)
{
    uint8 i;

    if (wp->type_F == 1)
    {
        for (i = 0; i < 16; i++)
        {
            D_8012BB88[wp->frame_E][i].x = D_8012B954[wp->frame_E].x - (rand() & 0x7F);
            D_8012BB88[wp->frame_E][i].y = D_8012B954[wp->frame_E].y - i * 0x28;
            D_8012BB88[wp->frame_E][i].z = D_8012B954[wp->frame_E].z - (rand() & 0x7F);
        }
        wp->timer_D = 1;
    }
}

void func_801216D8(STAGE_FX *wp)
{
    ST06_PUFF *p;
    uint8 n;
    sint8 count;
    sint8 i;
    uint8 shade;
    sint8 frac;
    sint32 color;

    if (wp->type_F == 1)
    {
        n     = wp->routine_1 >> 5;
        count = 16 - n;
        if (wp->routine_2 != 0)
        {
            count -= 8;
        }
        else if (count == 16)
        {
            count = 0;
        }
        frac = wp->routine_1 - (n << 5);
        for (i = 0; i < 16; i++)
        {
            if (i >= count)
            {
                shade = i - count;
            }
            else
            {
                shade = i + n + wp->routine_2 * 8;
            }
            p = func_8002D464();
            if (!(wp->routine_1 & 1))
            {
                D_8012BB88[wp->frame_E][i].x -= rand() & 7;
                D_8012BB88[wp->frame_E][i].z -= rand() & 3;
            }
            D_8012BB88[wp->frame_E][i].y -= rand() & 7;
            color      = 0x2E404040 - (frac / 8) * 0x10101;
            p->code_4  = color - shade * 0x40404;
            p->xy_8    = (uint16)D_8012BB88[wp->frame_E][i].x | (D_8012BB88[wp->frame_E][i].y << 16);
            p->z_10    = D_8012BB88[wp->frame_E][i].z;
            p->size_18 = shade * 16 + 0x100 + frac / 2;
            p->uv_C    = 0x3D48001F;
            p->uv_1C   = 0x201F;
            p->uv_24   = 0x203F;
            p->uv_14   = 0x4E003F;
            p->pad_20  = 0;
            if (frac == 0x1F && (i == count - 1 || (count == 0 && i == 15)))
            {
                D_8012BB88[wp->frame_E][i].x = D_8012B954[wp->frame_E].x - (rand() & 0x7F);
                D_8012BB88[wp->frame_E][i].y = D_8012B954[wp->frame_E].y;
                D_8012BB88[wp->frame_E][i].z = D_8012B954[wp->frame_E].z - (rand() & 0x7F);
                if (wp->h_26 == 1)
                {
                    D_8012BB88[wp->frame_E][i].y = D_8012B984[wp->frame_E];
                }
            }
        }
        if (++wp->routine_1 == 0)
        {
            if (wp->routine_2 != 0)
            {
                wp->routine_2 = 0;
            }
            else
            {
                wp->routine_2 = 1;
            }
        }
    }
}
