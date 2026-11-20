#include "common.h"
#include "st0a.h"

void func_80107428(ST0A_VIEW *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->u_AC.b[1]           = wp->u_AC.b[0];
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->value_158  = 0x02000200;
            wp->u_15C.w[0] = 0x200;
            wp->u_15C.h[1] = 0x4210;
            wp->u_AC.b[0]  = 0;
            wp->u_AC.b[1]  = 0xFF;
            wp->u_44.h[0]  = 0;
            wp->u_44.h[1]  = 0;
            wp->routine_0++;
            break;
        case 1:
            if (Scene_work.u_8.byte[1] == 4)
            {
                wp->u_44.h[0] = 6;
                wp->u_44.h[1] = 0xC;
                wp->routine_0++;
            }
            break;
        case 2:
            if (Scene_work.value_10 == 0x96)
            {
                wp->routine_0++;
            }
            break;
        case 3:
            if (wp->u_44.h[0] < 0xC)
            {
                wp->u_44.h[0] += 2;
            }
            if (wp->u_44.h[0] < 0x18)
            {
                wp->u_44.h[1] += 3;
            }
            break;
    }
    Obj_pos_set(wp, (sint16)(wp->u_44.h[0] << 4), (sint16)(-wp->u_44.h[1] << 4), 0);
    if (wp->u_AC.b[0] != wp->u_AC.b[1])
    {
        func_800322A8(wp, wp->u_AC.b[0], 0);
    }
    else
    {
        func_80032488(wp);
    }
}
