#include "common.h"
#include "st04.h"

void func_8010A248(STAGE_WORK *wp)
{
    D_80111D20[wp->routine_0](wp);
}

void func_8010A284(ST04_EV *wp)
{
    ST04_SLOT *slot;

    slot = Scene_obj_ent_open(D_80111D2C);
    slot->flags_6 &= ~0x20;
    wp->slot_1C   = slot;
    wp->routine_0 = 1;
}

void func_8010A2D4(ST04_EV *wp)
{
    if (wp->slot_1C->routine_2 == 0 && func_8010A484(wp->slot_1C))
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
    }
}

void func_8010A32C(ST04_EV *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (!(Moji_flag & 0x0F800000))
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            pl->value_448 = 0x30;
            wp->routine_1++;
            break;
        case 3:
            pl->value_448 = 0x35;
            MojiTaskExec2(0, 0xD2);
            wp->routine_1++;
            break;
        case 4:
            if (pl->flags_A7 < 0 && !(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0xD3);
                wp->routine_1++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1++;
            }
            break;
        case 6:
            if (!func_8003A13C())
            {
                func_80042314(pl);
                pl->flags_0 |= 2;
                func_8001E3F0(0x1A);
                wp->routine_1++;
            }
            break;
        case 7:
        case 8:
            break;
    }
}

uint8 func_8010A484(ST04_SLOT *slot)
{
    if ((D_80111D40.x >= slot->position.x && slot->position.x >= D_80111D48.x) &&
        (D_80111D40.y >= slot->position.y && slot->position.y >= D_80111D48.y) &&
        (D_80111D40.z >= slot->position.z && slot->position.z >= D_80111D48.z))
    {
        return 1;
    }
    return 0;
}
