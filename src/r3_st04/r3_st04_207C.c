#include "common.h"
#include "stage_common/stcom36.h"

// Ends one of stcom36's spawned objects if it is still left.
void func_8010207C(sint8 index)
{
    STCOM36_OBJ *obj;
    sint32 kind;

    if (stcom36_D_0000 & (0x80000000 >> index))
    {
        obj  = stcom36_E2_0000[index];
        kind = func_8002FE74(obj->slot);
        if (kind == 0x20 || kind == 0x60)
        {
            obj->routine_0 = 2;
            STCOM36_TABLE_3C0[obj->id][obj->handler](obj);
        }
        stcom36_D_0000 &= ~(0x80000000 >> index);
    }
}
