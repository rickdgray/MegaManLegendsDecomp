#include "common.h"
#include "st1b.h"

void func_8010C3EC(STAGE_EV *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            if (Sce_flag_test(D_80113E5C[wp->variant_3]))
            {
                STAGE_PL_BYTE(0xBD) |= 0x40;
                wp->routine_0++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                func_80017C30(0xA);
                func_8001D854(0x10);
                wp->routine_0++;
            }
            break;
        case 2:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                D_800C356C = 2;
                D_800C356E = 0x16;
                D_800C356F = (wp->variant_3 == 0) * 2;
                D_800C3560 = 0;
                D_800C3562 = 0;
                D_800C3564 = 0;
                D_800C356A = 0;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 0xFF;
                Close_EVE_WORK(wp);
            }
            break;
    }
}
