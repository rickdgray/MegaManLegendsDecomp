#include "common.h"
#include "st16.h"

void func_80100C84(STAGE_ROOM_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
            }
            break;
        case 1:
            Sound_seq_stop_all();
            switch ((rand() >> 8) & 1)
            {
                case 0:
                    Cd_xa_play_id(0x2001001C);
                    break;
                case 1:
                    Cd_xa_play_id(0x2001001D);
                    break;
            }
            wp->routine_4++;
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 2;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 4:
            Fade_start(2);
            wp->routine_4++;
            // fall through
        case 5:
            func_80100BDC(wp);
            wp->routine_4++;
            // fall through
        case 6:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                Fade_start(10);
                wp->routine_4 = 10;
            }
            // fall through
        case 10:
            func_80100C44(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 10 && D_80098A72 == 0)
            {
                if (STAGE_GAME_VALUE_52 == 7 && Sce_flag_test(0x21) != 0)
                {
                    D_800C356E = 0x17;
                    D_800C356F = 3;
                    D_800C3560 = 0;
                    D_800C3562 = 0;
                    D_800C3564 = 0;
                    D_800C356A = 0;
                }
                else
                {
                    D_800C356E = 0x1B;
                    D_800C356F = 6;
                    D_800C3560 = -0x40;
                    D_800C3562 = -1;
                    D_800C3564 = 0xC0;
                    D_800C356A = 0x800;
                }
                D_800C356C            = 2;
                D_800C356D            = 0;
                D_800C3571            = 0xFF;
                D_800C3570            = 2;
                wp->flags_0           = 0;
                STAGE_GAME_BYTE(0x7B) = 0;
                pl->flags_0 |= 1;
                Cd_subcmd(0, 1, 0);
                func_80042314(&Player_work);
            }
            break;
    }
}

void func_80100F60(void)
{
}
