#include "common.h"
#include "st1d.h"

void func_80112B18(STAGE_OBJ *wp)
{
    D_80115584[wp->routine_0](wp);
}

void func_80112B54(STAGE_OBJ *wp)
{
    D_8011558C[wp->variant_3](wp);
}

void func_80112B90(STAGE_OBJ *wp)
{
    Close_EVE_WORK(wp);
}

void func_80112BB0(STAGE_OBJ *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (Sce_flag_test(0x64) == 0)
            {
                wp->routine_1 = 1;
            }
            else if (Sce_flag_test(D_801155A0[Game_work.value_51]) != 0)
            {
                wp->routine_0 = 1;
            }
            else
            {
                wp->routine_1 = 3;
            }
            break;
        case 1:
            if (STAGE_PL.position.z < D_80115598[Game_work.value_51])
            {
                MojiTaskExec2(4, 1);
                Sce_flag_on(0x64);
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x800000))
            {
                wp->routine_1++;
            }
            break;
        case 3:
            if (Sce_flag_test(D_801155A0[Game_work.value_51]) != 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x800000))
            {
                MojiTaskExec2(4, 3);
                wp->routine_1++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x800000))
            {
                wp->routine_0 = 1;
            }
            break;
    }
}

void func_80112D3C(STAGE_OBJ *wp)
{
    sint8 i;
    sint32 count;
    switch (wp->routine_1)
    {
        case 0:
            if (Sce_flag_test(D_801155A0[Game_work.value_51]) == 0)
            {
                wp->routine_1++;
            }
            else
            {
                wp->routine_0 = 1;
            }
            break;
        case 1:
            if (Sce_flag_test(D_801155A0[Game_work.value_51]) != 0)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_1++;
            }
            break;
        case 3:
            for (i = 0, count = 0; i < 3; i++)
            {
                if (Sce_flag_test(D_801155AC[i]) != 0)
                {
                    count++;
                }
            }
            MojiTaskExec2(4, count + 3);
            if (count == 3)
            {
                Sce_flag_on(0x2B);
                func_8001D974();
            }
            wp->routine_1++;
            break;
        case 4:
            if (!(Moji_flag & 0x800000))
            {
                wp->routine_0 = 1;
            }
            break;
    }
}

void func_80112ED0(ST1D_VIEW *wp)
{
    if (wp->routine_1 == 0)
    {
        if (Sce_flag_test(D_801155B8[Game_work.value_51]))
        {
            Sound_fade_start(0x10);
            wp->routine_1++;
        }
    }
    else if (Sound_fade_flags == 0)
    {
        wp->routine_0 = 1;
    }
}

void func_80112F64(STAGE_EV *wp)
{
    STAGE_EV *ev;
    sint32 i;

    for (i = 0x1F; i >= 0; i--)
    {
        ev = func_800317AC(i);
        if (ev != NULL)
        {
            ev->flags_0 = 1;
            ev->kind_2  = 0;
            break;
        }
    }
    Close_EVE_WORK(wp);
}
