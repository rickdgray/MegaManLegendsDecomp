#include "common.h"
#include "st09.h"

void func_801170B0(STAGE_OBJ *wp)
{
    D_8011E3AC[wp->routine_0](wp);
}

void func_801170EC(ST09_EVENT *wp)
{
    ST09_MODEL *model;

    model = (ST09_MODEL *)Stage_hed_model_get(0x50000);
    if (model == NULL)
    {
        Close_EVE_WORK(wp);
        return;
    }
    model = (ST09_MODEL *)((uint32)model & 0xFFFFFF);
    wp->u_8.routine_0++;
    D_8011E9C8      = model->part_18[0];
    D_8011E9CC      = model->part_18[1];
    wp->color_1C[0] = model->part_18[0]->color_24;
    wp->color_1C[1] = model->part_18[1]->color_24;
}

void func_80117180(ST09_EVENT *wp)
{
    sint32 i;
    uint32 *color;
    uint32 a;
    uint32 b;

    for (i = 0; i < 2; i++)
    {
        color = wp->color_1C[i];
        a     = color[0];
        b     = color[1];
        a += 0x10001;
        b += 0x10001;
        if (a > 0xC0C0FEBF)
        {
            a = 0xC080FE80;
            b = 0xC0BFFEBF;
        }
        color[0] = a;
        color[1] = b;
        color[2] = a;
        color[3] = b;
        color[4] = a;
        color[5] = b;
        color[6] = a;
        color[7] = b;
    }
}

void func_801171FC(void)
{
}

void func_80117204(void)
{
}

void func_8011720C(STAGE_OBJ *wp)
{
    D_8011E3BC[wp->routine_0](wp);
}

void func_80117248(ST09_EVENT *wp)
{
    uint32 i;

    for (i = 0; i < 3; i++)
    {
        wp->cell_C[i]                  = Map_cell_get(&D_8011E3C8[i]);
        wp->value_14[i]                = 0x80;
        wp->delay_5[i]                 = i << 6;
        ST09_MAP_OBJS[wp->cell_C[i]].y = -0x180;
    }
    wp->u_8.word = 0;
    wp->value_4++;
}

void func_80117300(ST09_EVENT *wp)
{
    if (Map_cell_get(&Player_work.position) == wp->cell_C[0])
    {
        wp->value_4++;
    }
}

void func_80117354(ST09_EVENT *wp)
{
    uint32 i;

    for (i = 0; i < 3; i++)
    {
        if (wp->delay_5[i] != 0)
        {
            wp->delay_5[i]--;
            continue;
        }
        switch (wp->u_8.state[i])
        {
            case 0:
                ST09_MAP_OBJS[wp->cell_C[i]].y -= 3;
                if (ST09_MAP_OBJS[wp->cell_C[i]].y < -0x2FF)
                {
                    wp->u_8.state[i] = 1;
                }
                break;
            case 1:
                ST09_MAP_OBJS[wp->cell_C[i]].y += 3;
                if (ST09_MAP_OBJS[wp->cell_C[i]].y >= -0x180)
                {
                    wp->u_8.state[i] = 0;
                }
                break;
        }
    }
}
