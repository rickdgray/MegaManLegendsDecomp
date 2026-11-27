#include "common.h"
#include "st03.h"

void func_8010DE18(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 turn;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC      = 1;
            wp->velocity.v.x = 0x3C;
            wp->turn_64      = 0x20;
            wp->routine_2++;
            ctl->target_C = func_80036294(wp->timer_C)->position;
            // fall through
        case 1:
            turn           = Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (wp->value_A6 == 1)
            {
                Sound_call(0x10C, 0, 0);
            }
            if ((sint16)turn == 0)
            {
                Sce_flag_on(0x606);
                wp->routine_2++;
            }
            break;
        case 2:
            wp->routine_2++;
            ctl->target_C = func_80036294(wp->value_D)->position;
            // fall through
        case 3:
            wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_C, wp->rotation.y, wp->turn_64)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
            if (wp->value_A6 == 1)
            {
                Sound_call(0x10C, 0, 0);
            }
            dx = wp->position.x - ctl->target_C.x;
            dz = wp->position.z - ctl->target_C.z;
            if (dx * dx + dz * dz < 0x800)
            {
                wp->anim_AC      = 0;
                wp->velocity.v.x = 0;
                wp->turn_64      = 0;
                wp->routine_2++;
                Sce_flag_on(0x606);
            }
            break;
        case 4:
            break;
    }
}

void func_8010E014(ST03_OBJ *wp)
{
    sint32 temp_v1;
    uint8 temp_a1;

    temp_a1 = wp->routine_2;
    temp_v1 = temp_a1 & 0xFF;
    switch (temp_v1)
    {
        case 0:
            wp->routine_2 = temp_a1 + 1;
            wp->anim_AC   = 0;
        case 1:
            if (Moji_flag & 0x200000)
            {
                wp->anim_AC = 8;
                wp->routine_2++;
                return;
            }
            return;
        case 2:
            if (wp->value_A7 < 0)
            {
                wp->routine_2 = temp_a1 - 1;
                wp->anim_AC   = 0;
            }
            break;
    }
}
