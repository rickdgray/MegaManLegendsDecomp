#include "common.h"
#include "st04.h"

void func_80109FA0(STAGE_WORK *wp)
{
    D_80111D14[wp->routine_0](wp);
}

void func_80109FDC(STAGE_OBJ *wp)
{
    wp->routine_0 = 1;
}

void func_80109FE8(STAGE_OBJ50 *wp)
{
    if (D_800987B0[0] != 0 && D_800987B5 < 0x10 && (wp->u_C.b.lo = D_80111CE0[D_800987B5]) != 0)
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->value_F   = 0;
    }
}

void func_8010A044(STAGE_OBJ50 *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            pl->value_448 = 0x30;
            wp->routine_1++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                if (Moji_flag & 0xFF)
                {
                    wp->routine_1 = 10;
                }
                else
                {
                    Sound_fade_start(0x10);
                    wp->routine_1++;
                }
            }
            break;
        case 3:
            if (Sound_fade_flags == 0)
            {
                MojiTaskExec2(0, 0xB);
                Sound_work.volume_6 = D_80111D0C[wp->u_C.b.lo];
                Cd_xa_play_id(D_80111CF0[wp->u_C.b.lo]);
                wp->routine_1++;
            }
            break;
        case 4:
            if (func_8001D878())
            {
                wp->routine_1++;
            }
            break;
        case 5:
            if (D_800C0C26 != 0 || !(Moji_flag & 0x8000000) || !func_8001D878())
            {
                pl->value_448 = 0x31;
                func_80053AA4(0);
                Sound_fade_start(0x40);
                wp->routine_1++;
            }
            break;
        case 6:
            if (Sound_fade_flags == 0)
            {
                Sound_work.volume_6 = 0x7F;
                wp->routine_1++;
            }
            break;
        case 7:
            Sound_fade_start(0x20);
            wp->routine_1 = 10;
            break;
        case 10:
            if (!func_8003A13C())
            {
                func_80042314(&Player_work);
                pl->target_184 = NULL;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}
