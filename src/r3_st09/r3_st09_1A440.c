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
            ev->be_flag = MOVE;
            ev->id      = 0;
            break;
        }
    }
    Close_EVE_WORK(wp);
}
