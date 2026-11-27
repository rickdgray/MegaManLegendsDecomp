#include "common.h"
#include "stage_common/stcom10.h"

// Shared stage code, linked into 7 stages: r3_st00, r3_st09, r3_st0e, r3_st13, r3_st14, r3_st1a
// and r3_st1d. Each stage compiles this file against its own copy of the assembly (TARGET_ASM,
// set by tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom10"

void stcom10_func_0000(STCOM10_WORK *wp)
{
    stcom10_D_0000[wp->routine_0](wp);
}

void stcom10_func_003C(STCOM10_WORK *wp)
{
    wp->be_flag      = 1;
    wp->state.area_8 = wp->state.value_9 = -1;
    wp->state.table_0                    = stcom10_D_000C[Game_work.value_50][Game_work.value_51];
    wp->state.area_4                     = NULL;
    stcom10_E_0010[0].index              = -1;
    stcom10_E_0010[0].flag               = 0xFF;
    switch (Game_work.value_50)
    {
        case 0:
            Sce_flag_off(0x630);
            break;
        case 9:
            Sce_flag_off(0x610);
            break;
        case 14:
            Sce_flag_off(0x610);
            break;
        case 19:
            Sce_flag_off(0x620);
            break;
        case 20:
            Sce_flag_off(0x609);
            break;
        case 26:
            Sce_flag_off(0x605);
            break;
        case 29:
            Sce_flag_off(0x604);
            break;
    }
    wp->routine_0 = 1;
    stcom10_func_0134(wp);
}

void stcom10_func_0134(STCOM10_WORK *wp)
{
    STCOM10_STATE *st;
    STCOM10_AREA *area;
    STCOM10_PAIR *pair;
    STCOM10_OBJ *obj_3C0;
    STCOM10_OBJ *obj_5A4;
    STCOM10_OBJ *obj_10C;
    STCOM10_OBJ *obj_50;
    uint32 dx; // also the slot's bit number in the mask tests
    uint32 dz;
    uint32 mask;

    st = &wp->state;
    for (area = st->table_0; area->value_0 != -1; area++)
    {
        if (area->area_2 != st->area_8)
        {
            dx = ((sint16)Player_work.position.x >> 9) - area->x_4;
            dz = ((sint16)Player_work.position.z >> 9) - area->z_5;
            if (dx < area->width_6 && dz < area->depth_7)
            {
                if (st->area_8 != -1)
                {
                    for (pair = stcom10_E_0010; pair->flag != 0xFF; pair++)
                    {
                        switch (func_8002FE74(pair->flag))
                        {
                            case 0x20:
                                obj_3C0 = func_80036294(pair->flag);
                                mask    = (D_800987E8 ^ stcom10_E_0004) & stcom10_E_0004;
                                dx      = pair->flag & 0x1F;
                                if (mask & (0x80000000 >> dx))
                                {
                                    Sce_flag_on(area->list_8[pair->index].flag_14);
                                }
                                else
                                {
                                    obj_3C0->routine_0 = 2;
                                    STCOM10_TABLE_3C0[obj_3C0->id][obj_3C0->handler](obj_3C0);
                                }
                                break;
                            case 0x40:
                                obj_5A4 = func_80036294(pair->flag);
                                mask    = (D_80098B20 ^ stcom10_E_0000) & stcom10_E_0000;
                                dx      = pair->flag & 0x1F;
                                if (mask & (0x80000000 >> dx))
                                {
                                    Sce_flag_on(area->list_8[pair->index].flag_14);
                                }
                                else
                                {
                                    obj_5A4->routine_0 = 2;
                                    STCOM10_TABLE_5A4[obj_5A4->id][obj_5A4->handler](obj_5A4);
                                }
                                break;
                            case 0x60:
                                obj_10C = func_80036294(pair->flag);
                                mask    = (D_800987CC ^ stcom10_E_0008) & stcom10_E_0008;
                                dx      = pair->flag & 0x1F;
                                if (mask & (0x80000000 >> dx))
                                {
                                    Sce_flag_on(area->list_8[pair->index].flag_14);
                                }
                                else
                                {
                                    obj_10C->routine_0 = 2;
                                    STCOM10_TABLE_10C[obj_10C->id](obj_10C);
                                }
                                break;
                            case 0xE0:
                                obj_50 = func_80036294(pair->flag);
                                mask   = (D_800989CC ^ stcom10_E_000C) & stcom10_E_000C;
                                dx     = pair->flag & 0x1F;
                                if (mask & (0x80000000 >> dx))
                                {
                                    Sce_flag_on(area->list_8[pair->index].flag_14);
                                }
                                else
                                {
                                    obj_50->routine_0 = 2;
                                    STCOM10_TABLE_50[obj_50->id](obj_50);
                                }
                                break;
                        }
                    }
                }
                st->area_4    = area;
                wp->routine_0 = 2;
            }
        }
        else
        {
            for (pair = stcom10_E_0010; pair->flag != 0xFF; pair++)
            {
                switch (func_8002FE74(pair->flag))
                {
                    case 0x20:
                        mask = (D_800987E8 ^ stcom10_E_0004) & stcom10_E_0004;
                        dx   = pair->flag & 0x1F;
                        if (mask & (0x80000000 >> dx))
                        {
                            Sce_flag_on(area->list_8[pair->index].flag_14);
                        }
                        break;
                    case 0x40:
                        mask = (D_80098B20 ^ stcom10_E_0000) & stcom10_E_0000;
                        dx   = pair->flag & 0x1F;
                        if (mask & (0x80000000 >> dx))
                        {
                            Sce_flag_on(area->list_8[pair->index].flag_14);
                        }
                        break;
                    case 0x60:
                        mask = (D_800987CC ^ stcom10_E_0008) & stcom10_E_0008;
                        dx   = pair->flag & 0x1F;
                        if (mask & (0x80000000 >> dx))
                        {
                            Sce_flag_on(area->list_8[pair->index].flag_14);
                        }
                        break;
                    case 0xE0:
                        mask = (D_800989CC ^ stcom10_E_000C) & stcom10_E_000C;
                        dx   = pair->flag & 0x1F;
                        if (mask & (0x80000000 >> dx))
                        {
                            Sce_flag_on(area->list_8[pair->index].flag_14);
                        }
                        break;
                }
            }
        }
    }
    stcom10_E_0004 = D_800987E8;
    stcom10_E_0000 = D_80098B20;
    stcom10_E_0008 = D_800987CC;
    stcom10_E_000C = D_800989CC;
}

void stcom10_func_05F4(STCOM10_WORK *wp)
{
    STCOM10_AREA *area;
    STCOM10_SPAWN *spawn;
    STCOM10_PAIR *pair;
    STCOM10_OBJ *obj;
    STCOM10_OBJ50 *obj50;
    STCOM10_STATE *st;
    sint32 i;

    i    = 0;
    st   = &wp->state;
    area = st->area_4;
    pair = stcom10_E_0010;
    for (spawn = area->list_8; spawn->flags_0 != -1; spawn++, i++)
    {
        if (Sce_flag_test(spawn->flag_14))
        {
            continue;
        }
        switch (spawn->kind_1)
        {
            case 0x20:
                obj = func_80031418();
                if (obj == NULL)
                {
                    break;
                }
                obj->be_flag          = spawn->flags_0;
                obj->id               = spawn->value_2;
                obj->type             = spawn->value_3;
                obj->handler          = spawn->value_4;
                obj->value_5          = spawn->value_5;
                obj->value_C          = spawn->value_8;
                obj->position_fixed.x = obj->position_fixed_prev.x = spawn->pos_C.x << 16;
                obj->position_fixed.y = obj->position_fixed_prev.y = spawn->pos_C.y << 16;
                obj->position_fixed.z = obj->position_fixed_prev.z = spawn->pos_C.z << 16;
                obj->position = obj->position_prev = spawn->pos_C;
                obj->rotation.x = obj->rotation_prev.x = 0;
                obj->rotation.y = obj->rotation_prev.y = spawn->rotation_7 << 4;
                obj->rotation.z = obj->rotation_prev.z = 0;
                pair->flag                             = obj->slot;
                pair->index                            = i;
                pair++;
                break;
            case 0x40:
                obj = func_80031498();
                if (obj == NULL)
                {
                    break;
                }
                obj->be_flag          = spawn->flags_0;
                obj->id               = spawn->value_2;
                obj->type             = spawn->value_3;
                obj->handler          = spawn->value_4;
                obj->value_5          = spawn->value_5;
                obj->value_C          = spawn->value_8;
                obj->position_fixed.x = obj->position_fixed_prev.x = spawn->pos_C.x << 16;
                obj->position_fixed.y = obj->position_fixed_prev.y = spawn->pos_C.y << 16;
                obj->position_fixed.z = obj->position_fixed_prev.z = spawn->pos_C.z << 16;
                obj->position = obj->position_prev = spawn->pos_C;
                obj->rotation.x = obj->rotation_prev.x = 0;
                obj->rotation.y = obj->rotation_prev.y = spawn->rotation_7 << 4;
                obj->rotation.z = obj->rotation_prev.z = 0;
                pair->flag                             = obj->slot;
                pair->index                            = i;
                pair++;
                break;
            case 0x60:
                obj = Open_SHL_WORK();
                if (obj == NULL)
                {
                    break;
                }
                obj->be_flag          = spawn->flags_0;
                obj->id               = spawn->value_2;
                obj->type             = spawn->value_3;
                obj->value_C          = spawn->value_8;
                obj->position_fixed.x = obj->position_fixed_prev.x = spawn->pos_C.x << 16;
                obj->position_fixed.y = obj->position_fixed_prev.y = spawn->pos_C.y << 16;
                obj->position_fixed.z = obj->position_fixed_prev.z = spawn->pos_C.z << 16;
                obj->position = obj->position_prev = spawn->pos_C;
                obj->rotation.x = obj->rotation_prev.x = 0;
                obj->rotation.y = obj->rotation_prev.y = spawn->rotation_7 << 4;
                obj->rotation.z = obj->rotation_prev.z = 0;
                pair->flag                             = obj->slot;
                pair->index                            = i;
                pair++;
                break;
            case 0xE0:
                obj50 = func_80031734();
                if (obj50 == NULL)
                {
                    break;
                }
                obj50->be_flag = spawn->flags_0;
                obj50->id      = spawn->value_2;
                obj50->type    = spawn->value_3;
                obj50->value_C = spawn->value_8;
                obj50->pos_38  = spawn->pos_C;
                obj50->x_1C    = spawn->pos_C.x;
                obj50->y_1E    = spawn->pos_C.y;
                obj50->z_20    = spawn->pos_C.z;
                pair->flag     = obj50->slot;
                pair->index    = i;
                pair++;
                break;
        }
    }
    pair->index   = -1;
    pair->flag    = 0xFF;
    st->area_8    = area->area_2;
    st->value_9   = area->value_0;
    wp->routine_0 = 1;
}
