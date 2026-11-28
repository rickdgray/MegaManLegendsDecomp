#include "common.h"
#include "st1b.h"

void func_801022D4(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            Fade_start(0xA);
            wp->routine_4++;
            break;
        case 1:
            if (func_80042238(&Player_work) != 0)
            {
                Player_work.flags_0 &= ~3;
                Obj_work_flag_change(0x56, 0x80);
                Cd_xa_play_id(0x20000020);
                wp->routine_4++;
            }
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x14;
                wp->routine_4++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                Fade_start(2);
                wp->routine_4++;
            }
            break;
        case 4:
            func_801021BC(wp);
            wp->routine_4++;
            // fall through
        case 5:
            if (D_80098A72 == 0 && *(uint8 *)wp->tbl_A4 == 0xFF)
            {
                Fade_start(0xB);
                wp->routine_4++;
            }
            // fall through
        case 6:
            func_80102294(wp);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 6 && D_80098A72 == 0)
            {
                D_800C356C  = 2;
                D_800C356E  = 0x1E;
                D_800C356F  = 0;
                D_800C3560  = 0;
                D_800C3562  = 0;
                D_800C3564  = 0;
                D_800C356A  = 0;
                D_800C356D  = 0;
                D_800C3571  = 0xFF;
                D_800C3570  = 0xFF;
                wp->flags_0 = 0;
                Cd_subcmd(0, 1, 0);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}
