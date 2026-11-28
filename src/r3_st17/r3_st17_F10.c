#include "common.h"
#include "st17.h"

void func_80100F10(STAGE_OBJ *wp)
{
    sint16 x;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    switch (wp->routine_0)
    {
        case 1:
        case 3:
            break;
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_44.half[0] = -0x10E;
            wp->value_48.half[0] = -0x10E;
            wp->anim_AC          = 1;
            wp->value_78         = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            wp->anim_prev_AD     = 0xFF;
            wp->routine_0++;
            break;
        case 2:
            x                      = wp->position.x + 0xC;
            wp->position.x         = x;
            wp->position_fixed.v.x = x << 0x10;
            break;
        case 4:
            if (wp->u_C.b.byte_C < 0x40)
            {
                wp->rotation.z -= 3;
                wp->u_C.b.byte_C++;
            }
            if (wp->u_C.b.byte_D < 0x3C)
            {
                wp->value_44.half[0] -= 9;
                wp->value_48.half[0] -= 9;
                wp->u_C.b.byte_D++;
            }
            Obj_pos_set(wp, wp->value_44.half[0], 0, wp->value_48.half[0]);
            break;
    }
    if (wp->anim_AC != wp->anim_prev_AD)
    {
        func_800322A8(wp, 1, 0x2E);
        wp->anim_prev_AD = wp->anim_AC;
    }
    else if (wp->routine_0 == 4)
    {
        func_80032538(wp);
        Model_parts_mtx_set_yxz(wp);
    }
    else
    {
        func_80032488(wp);
    }
    func_80051B68(wp, 1, -1, 0);
}
