#include "common.h"
#include "stage_common/stcom30.h"

// Shared stage code, linked into 3 stages: r3_st0e, r3_st13 and r3_st14. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom30"

// Counts the switches turned on (one scene flag each) and sets a scene flag per count; spawns
// the room's objects.
void stcom30_func_0000(STCOM30_WORK *wp)
{
    STCOM30_SPAWN *spawn;
    sint32 *flag;
    sint32 done;
    sint32 on_1;
    sint32 on_2;
    sint32 on_3;
    uint8 count;

    spawn = NULL;
    count = 0;
    flag  = wp->flag_2C;
    if (Game_work.value_50 == 0xE)
    {
        done           = 0x1E;
        on_1           = 0x609;
        on_2           = 0x60A;
        on_3           = 0x60B;
        wp->flag_2C[0] = 0x52E;
        wp->flag_2C[1] = 0x52F;
        wp->flag_2C[2] = 0x530;
    }
    else if (Game_work.value_50 == 0x14)
    {
        done           = 0x27;
        on_1           = 0x606;
        on_2           = 0x607;
        on_3           = 0x608;
        wp->flag_2C[0] = 0x531;
        wp->flag_2C[1] = 0x532;
        wp->flag_2C[2] = 0x533;
    }
    else
    {
        done           = 0x44;
        on_1           = 0x63E;
        on_2           = 0x63F;
        on_3           = 0x640;
        wp->flag_2C[0] = 0x534;
        wp->flag_2C[1] = 0x535;
        wp->flag_2C[2] = 0x536;
    }
    if (Sce_flag_test(done) == 0)
    {
        if (Sce_flag_test(flag[0]))
        {
            count++;
        }
        if (Sce_flag_test(flag[1]))
        {
            count++;
        }
        if (Sce_flag_test(flag[2]))
        {
            count++;
        }
        if (count == 1)
        {
            Sce_flag_on(on_1);
            if (Game_work.value_50 == 0x13 && Sce_flag_test(0x4B) == 0 && !(Moji_flag & 0x800000))
            {
                Sce_flag_on(0x4B);
                MojiTaskExec2(4, 0xE);
                wp->routine_0++;
            }
        }
        else if (count == 2)
        {
            Sce_flag_on(on_1);
            Sce_flag_on(on_2);
        }
        else if (count == 3)
        {
            Sce_flag_on(on_1);
            Sce_flag_on(on_2);
            Sce_flag_on(on_3);
        }
        if (Game_work.value_50 == 0xE)
        {
            spawn = stcom30_D_0000[Game_work.value_51];
        }
        else if (Game_work.value_50 == 0x14)
        {
            spawn = stcom30_D_000C[Game_work.value_51];
        }
        if (Game_work.value_50 == 0xE)
        {
            stcom30_func_02B4(wp, spawn);
            func_80031A4C(wp);
        }
        else if (Game_work.value_50 == 0x14 && wp->spawned_9 == 0)
        {
            stcom30_func_0570(wp, spawn);
            wp->spawned_9 = 1;
        }
        return;
    }
    func_80031A4C(wp);
}

// Spawns the objects whose switches are not on yet.
void stcom30_func_02B4(STCOM30_WORK *wp, STCOM30_SPAWN *spawn)
{
    STCOM30_OBJ *obj;
    STCOM30_OBJ50 *obj50;
    sint32 *flag;
    sint16 skip;

    flag = wp->flag_2C;
    skip = 0;
    do
    {
        if (spawn->kind_1 == 0x20)
        {
            if (spawn->value_2 == 0x35 && Sce_flag_test(flag[2]))
            {
                skip = 1;
            }
            if (!skip)
            {
                if (Sce_flag_test(0x60C))
                {
                    Sce_flag_off(0x60C);
                }
                obj = func_80031418();
                if (obj != NULL)
                {
                    obj->flags_0          = spawn->flags_0;
                    obj->kind_2           = spawn->value_2;
                    obj->value_3          = spawn->value_3;
                    obj->handler_4        = spawn->value_4;
                    obj->value_5          = spawn->value_5;
                    obj->rotation.y       = spawn->rotation_7 << 4;
                    obj->value_C          = spawn->value_8;
                    obj->value_D          = spawn->value_9;
                    obj->value_E          = spawn->value_A;
                    obj->value_F          = spawn->value_B;
                    obj->position.x       = spawn->pos_C.x;
                    obj->position.y       = spawn->pos_C.y;
                    obj->position.z       = spawn->pos_C.z;
                    obj->position_fixed.x = obj->position.x << 16;
                    obj->position_fixed.y = obj->position.y << 16;
                    obj->position_fixed.z = obj->position.z << 16;
                }
            }
        }
        else
        {
            skip = 0;
            if (spawn->kind_1 == 0x60)
            {
                if (spawn->value_2 == 0x2A)
                {
                    if (spawn->value_8 == 2)
                    {
                        skip = Sce_flag_test(flag[0]) != 0;
                    }
                    else if (spawn->value_8 == 1 && Sce_flag_test(flag[1]))
                    {
                        skip = 1;
                    }
                }
                if (!skip)
                {
                    obj = func_80031518();
                    if (obj != NULL)
                    {
                        obj->flags_0          = spawn->flags_0;
                        obj->kind_2           = spawn->value_2;
                        obj->value_3          = spawn->value_3;
                        obj->handler_4        = spawn->value_4;
                        obj->value_5          = spawn->value_5;
                        obj->rotation.y       = spawn->rotation_7 << 4;
                        obj->value_C          = spawn->value_8;
                        obj->value_D          = spawn->value_9;
                        obj->value_E          = spawn->value_A;
                        obj->value_F          = spawn->value_B;
                        obj->position.x       = spawn->pos_C.x;
                        obj->position.y       = spawn->pos_C.y;
                        obj->position.z       = spawn->pos_C.z;
                        obj->position_fixed.x = obj->position.x << 16;
                        obj->position_fixed.y = obj->position.y << 16;
                        obj->position_fixed.z = obj->position.z << 16;
                    }
                }
            }
            else if (spawn->kind_1 == 0xE0)
            {
                obj50 = func_80031734();
                if (obj50 != NULL)
                {
                    obj50->flags_0   = spawn->flags_0;
                    obj50->kind_2    = spawn->value_2;
                    obj50->variant_3 = spawn->value_3;
                    obj50->value_4   = spawn->value_4;
                    obj50->value_5   = spawn->value_5;
                    obj50->value_C   = spawn->value_8;
                    obj50->value_D   = spawn->value_9;
                    obj50->value_E   = spawn->value_A;
                    obj50->value_F   = spawn->value_B;
                    obj50->pos_38.x  = spawn->pos_C.x;
                    obj50->pos_38.y  = spawn->pos_C.y;
                    obj50->pos_38.z  = spawn->pos_C.z;
                }
            }
        }
        spawn++;
    } while (spawn->flags_0 != -1);
}

// Spawns all the objects.
void stcom30_func_0570(STCOM30_WORK *wp, STCOM30_SPAWN *spawn)
{
    STCOM30_OBJ *obj;
    STCOM30_OBJ50 *obj50;

    while (spawn->flags_0 != -1)
    {
        if (spawn->kind_1 == 0x20)
        {
            obj = func_80031418();
            if (obj != NULL)
            {
                obj->flags_0          = spawn->flags_0;
                obj->kind_2           = spawn->value_2;
                obj->value_3          = spawn->value_3;
                obj->handler_4        = spawn->value_4;
                obj->value_5          = spawn->value_5;
                obj->rotation.y       = spawn->rotation_7 << 4;
                obj->value_C          = spawn->value_8;
                obj->value_D          = spawn->value_9;
                obj->value_E          = spawn->value_A;
                obj->value_F          = spawn->value_B;
                obj->position.x       = spawn->pos_C.x;
                obj->position.y       = spawn->pos_C.y;
                obj->position.z       = spawn->pos_C.z;
                obj->position_fixed.x = obj->position.x << 16;
                obj->position_fixed.y = obj->position.y << 16;
                obj->position_fixed.z = obj->position.z << 16;
            }
        }
        else if (spawn->kind_1 == 0xE0)
        {
            obj50 = func_80031734();
            if (obj50 != NULL)
            {
                obj50->flags_0   = spawn->flags_0;
                obj50->kind_2    = spawn->value_2;
                obj50->variant_3 = spawn->value_3;
                obj50->value_4   = spawn->value_4;
                obj50->value_5   = spawn->value_5;
                obj50->value_C   = spawn->value_8;
                obj50->value_D   = spawn->value_9;
                obj50->value_E   = spawn->value_A;
                obj50->value_F   = spawn->value_B;
                obj50->pos_38.x  = spawn->pos_C.x;
                obj50->pos_38.y  = spawn->pos_C.y;
                obj50->pos_38.z  = spawn->pos_C.z;
            }
        }
        spawn++;
    }
}
