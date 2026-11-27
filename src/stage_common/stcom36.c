#include "common.h"
#include "stage_common/stcom36.h"

// Shared stage code, linked into 3 stages: r3_st03, r3_st04 and r3_st05. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom36"

void stcom36_func_0000(void)
{
    Sce_camera_update();
    Sce_event_update();
}

// Spawns a room's scripted objects and remembers them.
void stcom36_func_0028(sint8 room)
{
    STCOM36_ROOM *r;
    sint16 i;
    sint32 index;

    r              = &stcom36_E_0000[room];
    stcom36_D_0000 = 0;
    for (i = 0; i < r->count; i++)
    {
        index = r->list[i].index_0;
        Scene_obj_ent_open(&r->list[i]);
        stcom36_E2_0000[index] = Scene_work.obj_24[index];
        stcom36_E2_0000[index]->flags &= ~0x20;
        stcom36_D_0000 |= 0x80000000 >> index;
    }
}

// Ends the objects still left.
void stcom36_func_0118(void)
{
    STCOM36_OBJ *obj;
    sint32 kind;
    sint32 i;

    i = 0;
    while (stcom36_D_0000 != 0)
    {
        if (stcom36_D_0000 & (0x80000000 >> i))
        {
            obj  = stcom36_E2_0000[i];
            kind = func_8002FE74(obj->work_id);
            switch (kind)
            {
                case 0x20:
                    obj->routine_0 = 2;
                    STCOM36_TABLE_3C0[obj->id][obj->handler](obj);
                    break;
                case 0x60:
                    obj->routine_0 = 2;
                    STCOM36_TABLE_10C[obj->id](obj);
                    break;
            }
            stcom36_D_0000 &= ~(0x80000000 >> i);
        }
        i++;
    }
}
