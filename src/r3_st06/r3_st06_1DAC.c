#include "common.h"
#include "st06.h"

void func_80101DAC(STAGE_REC_S *rec)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (rec->step_2)
    {
        case 0:
            rec->step_2++;
            // fall through
        case 1:
            pl->routine_0   = 3;
            pl->routine_1   = 1;
            pl->fixed_428.x = 0x2580000;
            pl->fixed_428.y = 0xFCFF0000;
            pl->fixed_428.z = 0x8340000;
            pl->flags_bd |= 0x10;
            func_80030150(&pl->fixed_428, &pl->pos_438);
            pl->value_442 = 0x990;
            pl->value_440 = 0;
            pl->value_444 = 0;
            pl->value_448 = 0x30;
            rec->step_2++;
            break;
        case 2:
            if (Sce_flag_test(0x607))
            {
                Sce_flag_off(0x607);
                rec->timer_8 = 0x20;
                rec->step_2++;
            }
            break;
        case 3:
            if (--rec->timer_8 == 0)
            {
                pl->value_448 = 0xD;
                rec->timer_8  = 0x10;
                rec->step_2++;
            }
            break;
        case 4:
            if (--rec->timer_8 == 0)
            {
                pl->value_448 = 0x30;
                Sce_flag_off(0x608);
                rec->step_2++;
            }
            else
            {
                pl->value_442 = (pl->value_442 - 0x30) & 0xFFF;
            }
            break;
        case 5:
            break;
    }
}

void func_80101F1C(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = D_8012BE94;
    switch (rec->step_2)
    {
        case 0:
            obj->rotation.y = 0x200;
            rec->step_2++;
            break;
        case 1:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                Sce_flag_on(0x607);
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.b.byte_D          = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                Sce_flag_off(0x607);
                obj->routine_1             = 3;
                *(uint16 *)&obj->routine_2 = 0;
                obj->u_C.b.byte_D          = 1;
                obj->rotation.y            = 0;
                rec->step_2++;
            }
            break;
        case 3:
            if (Sce_flag_test(0x608))
            {
                Sce_flag_off(0x608);
                obj->routine_1             = 1;
                *(uint16 *)&obj->routine_2 = 0;
                MojiTaskExec2(0, 0xB);
                rec->step_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                Sce_flag_on(0x604);
                rec->step_2++;
            }
            break;
    }
}

void func_8010205C(STAGE_REC_S *rec)
{
    STAGE_OBJ *obj;

    obj = D_8012BE98;
    switch (rec->step_2)
    {
        case 0:
            rec->timer_8 = 0x258;
            rec->step_2++;
            // fall through
        case 1:
            if (--rec->timer_8 == 0)
            {
                obj->routine_1             = 2;
                *(uint16 *)&obj->routine_2 = 0;
                rec->step_2++;
            }
            break;
        case 2:
            if (Sce_flag_test(0x609))
            {
                Sce_flag_off(0x609);
                rec->step_2++;
            }
            break;
    }
}

void func_80102124(void)
{
    Sce_camera_update();
    Sce_event_update();
}

void func_8010214C(sint8 index)
{
    ST06_SPAWN_GROUP *group;
    sint16 i;
    uint32 slot;

    group = &D_80123194[index];
    for (i = 0; i < group->count_0; i++)
    {
        slot = group->list_4[i][0];
        Scene_obj_ent_open(group->list_4[i]);
        D_8012BE88[slot] = STAGE_SCENE_OBJ(slot);
        D_8012BE88[slot]->flags_6 &= ~0x20;
        D_801228A4 |= 0x80000000 >> slot;
    }
}

void func_80102238(void)
{
    sint8 var_s0;

    var_s0 = 0;
    if (D_801228A4 != 0)
    {
        do
        {
            func_80102288(var_s0);
            var_s0++;
        } while (D_801228A4 != 0);
    }
}

void func_80102288(sint8 index)
{
    STAGE_SPAWNED *obj;

    if (D_801228A4 & (0x80000000 >> index))
    {
        obj = D_8012BE88[index];
        switch (func_8002FE74(obj->index_1))
        {
            case 0x20:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_3C0[obj->kind_2][obj->handler_4](obj);
                break;
            case 0x60:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_10C[obj->kind_2](obj);
                break;
        }
        D_801228A4 &= ~(0x80000000 >> index);
    }
}

void func_80102388(uint8 index, uint8 kind)
{
    STAGE_REC *rec;

    rec           = &D_8012B990[index];
    rec->active_0 = 1;
    rec->value_2  = 0;
    rec->value_3  = 0;
    rec->data_4   = D_80123188[kind];
}

void func_801023D0(uint8 index)
{
    D_8012B990[index].active_0 = 0;
}

void func_801023F4(void)
{
    STAGE_REC *rec;
    sint32 i;

    for (i = 0, rec = D_8012B990; i < 8; i++)
    {
        rec->active_0 = 0;
        rec->index_1  = i;
        rec->value_2  = 0;
        rec->value_3  = 0;
        rec++;
    }
    rec->active_0 = 0;
}
