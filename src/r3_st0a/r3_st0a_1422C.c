#include "common.h"
#include "st0a.h"

void func_8011422C(STAGE_OBJ *wp)
{
    D_80116594[wp->type](wp);
}

void func_80114268(ST0A_EV *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_0)
    {
        case 0:
            wp->frame_1C = 0;
            wp->routine_0++;
            break;
        case 1:
            if (pl->position.x < -0x900)
            {
                if (func_80042208())
                {
                    pl->flags_bd |= 0x40;
                    Sound_fade_start(0x10);
                    Sce_flag_on(0x26);
                    wp->routine_0++;
                }
                else
                {
                    Close_EVE_WORK(wp);
                }
            }
            break;
        case 2:
            if (Sce_flag_test(0x604))
            {
                pl->flags_bd |= 0x40;
                MojiTaskKill();
                wp->routine_0++;
            }
            break;
        case 3:
            Fade_start(0xE);
            Sound_fade_start(0x10);
            wp->routine_0++;
            // fall through
        case 4:
            if (wp->frame_1C % 5 == 0)
            {
                Sound_call(0xA1, 0, 0);
            }
            if (++wp->frame_1C == 0x2E)
            {
                wp->routine_0++;
            }
            break;
        case 5:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                Sce_flag_on(0x10);
                Close_EVE_WORK(wp);
            }
            break;
    }
}

void func_801143F8(ST0A_EV *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_0)
    {
        case 0:
            if (pl->position.x >= -0x7CF)
            {
                if (func_80042208())
                {
                    pl->flags_bd |= 0x40;
                    wp->routine_0++;
                }
                else
                {
                    Close_EVE_WORK(wp);
                }
            }
            break;
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_0++;
            }
            break;
        case 2:
            MojiTaskExec2(0, 0xB);
            wp->routine_0++;
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                Fade_start(0xA);
                wp->routine_0++;
            }
            break;
        case 4:
            if (D_80098A72 == 0)
            {
                wp->routine_0++;
            }
            break;
        case 5:
            func_80042314(pl);
            D_800C356C = 2;
            D_800C356E = 7;
            D_800C356F = 5;
            D_800C3560 = 0;
            D_800C3562 = 0;
            D_800C3564 = 0;
            D_800C356A = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            Close_EVE_WORK(wp);
            break;
    }
}
