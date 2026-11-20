#include "common.h"
#include "st09.h"

void func_8011A440(STAGE_EV *wp)
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
