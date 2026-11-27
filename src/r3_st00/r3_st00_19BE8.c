#include "common.h"
#include "st00.h"

void func_80119BE8(STAGE_EV *wp)
{
    STAGE_OBJ *obj;
    sint32 i;

    for (i = 0x1F; i >= 0; i--)
    {
        obj = func_800317AC(i);
        if (obj != NULL)
        {
            obj->be_flag = MOVE;
            obj->id      = 0;
            break;
        }
    }
    Close_EVE_WORK(wp);
}
