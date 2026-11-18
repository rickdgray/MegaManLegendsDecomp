#include "common.h"
#include "st1d.h"

void func_80111300(STAGE_OBJ50 *wp)
{
    if (wp->variant_3 == 0xFF)
    {
        func_801113A4();
        func_80031A4C(wp);
        return;
    }
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        wp->routine_0++;
    }
    if ((uint32)((uint16)STAGE_PL.rotation.y - 0x3AC) >= 0x8A9)
    {
        wp->color_40 = 0x2404040;
    }
    else
    {
        wp->color_40 = 0x808080;
    }
}

void func_801113A4(void)
{
    STCOM_SVECTOR pos;
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 z;
    sint32 count;
    uint32 type;
    STAGE_PANEL_SPAWN *list;
    STAGE_PANEL_WORK *wp;
    sint32 found;
    sint32 i;
    sint32 k;
    sint32 x;
    sint32 cell;
    list  = D_80114FD0[0].list;
    found = 0;
    for (i = 0; D_80114FD0[i].stage != 0xFF; i++)
    {
        if (Game_work.value_50 == D_80114FD0[i].stage && Game_work.value_51 == D_80114FD0[i].room)
        {
            found = 1;
            list  = D_80114FD0[i].list;
            break;
        }
    }
    if (found == 0)
    {
        return;
    }
    count = STAGE_PANEL_COUNT;
    z0    = STAGE_MAP_Z0;
    z1    = STAGE_MAP_Z1;
    x0    = STAGE_MAP_X0;
    x1    = STAGE_MAP_X1;
    for (z = z0; z < z1; z++)
    {
        for (x = x0; x < x1; x++)
        {
            cell = *(STAGE_MAP_CELLS + (x - x0) + (z - z0) * STAGE_MAP_W);
            if (cell > 0)
            {
                type = *STAGE_CELL_TBL[cell].info;
                k    = 0;
                do
                {
                    if (list[k].type_4 == type)
                    {
                        for (i = 0; i < 2; i++)
                        {
                            wp = func_80031734();
                            if (wp != NULL)
                            {
                                wp->flags_0 = 5;
                                wp->kind_2  = 0x34;
                                wp->value_3 = list[k].spawn_E[i] >> 4;
                                func_8002F9C4(wp, &wp->value_3);
                                wp->dir_C           = list[k].spawn_E[i] & 0xF;
                                wp->value_D         = count;
                                pos                 = STAGE_CELL_TBL[cell].pos;
                                wp->pos_38.x        = STAGE_CELL_TBL[cell].pos.x + list[k].x_8 +
                                                      D_80114FF0[wp->dir_C].x;
                                wp->pos_38.z        = STAGE_CELL_TBL[cell].pos.z + list[k].z_C +
                                                      D_80114FF0[wp->dir_C].z;
                                wp->pos_38.y        = STAGE_CELL_TBL[cell].pos.y + list[k].y_A;
                                wp->matrix.words[0] = 0x1000;
                                wp->matrix.words[1] = 0;
                                wp->matrix.words[2] = 0x1000;
                                wp->matrix.words[3] = 0;
                                wp->matrix.words[4] = 0x1000;
                                RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
                                wp->cell_44         = cell;
                                wp->matrix.words[5] = (uint32)STAGE_CELL_TBL[cell].info;
                                wp->matrix.words[6] = func_8003AC24(list[k].key_0);
                            }
                        }
                        count++;
                        STAGE_PANEL_COUNT++;
                    }
                    k++;
                } while (list[k].key_0 != 0);
            }
        }
    }
}

void func_8011174C(STAGE_OBJ50 *wp)
{
    sint32 diff;
    if (wp->variant_3 == 1)
    {
        func_80111D78();
        func_80031A4C(wp);
        return;
    }
    D_80115000[wp->routine_0](wp);
    if (wp->u_C.b.lo == 0)
    {
        if ((uint32)((uint16)STAGE_PL.rotation.y - 0x3AC) >= 0x8A9)
        {
            wp->color_40 = 0x2404040;
        }
        else
        {
            wp->color_40 = 0x808080;
        }
    }
    else
    {
        diff = (STAGE_PL.rotation.y & 0xFFF) - (wp->u_C.b.lo << 10);
        if (STCOM_ABS(diff) < 0x3AC)
        {
            wp->color_40 = 0x2404040;
        }
        else
        {
            wp->color_40 = 0x808080;
        }
    }
}

void func_80111830(STAGE_OBJ50 *wp)
{
    sint32 flag;
    flag          = 0;
    wp->routine_0 = 7;
    wp->model_10  = D_80115294;
    wp->flags_0 |= 2;
    if (wp->variant_3 == 0)
    {
        switch (Game_work.value_51)
        {
            case 0:
            case 3:
                flag = 0x66;
                break;
            case 1:
            case 4:
                flag = 0x67;
                break;
            case 2:
            case 5:
                flag = 0x68;
                break;
        }
        if (Sce_flag_test(flag) != 0)
        {
            wp->value_E = 0;
        }
        else
        {
            wp->value_E = 10;
        }
    }
}

void func_801118E0(STAGE_OBJ50 *wp)
{
    STAGE_PL_VIEW *pl;
    sint32 flag;
    pl   = &STAGE_PL;
    flag = 0;
    if (wp->value_E == 0 && D_800987E8 == 0 && D_80098B20 == 0)
    {
        switch (Game_work.value_51)
        {
            case 0:
                Sce_flag_on(0x616);
                break;
            case 1:
                Sce_flag_on(0x617);
                break;
            case 2:
                Sce_flag_on(0x618);
                break;
        }
    }
    if (wp->variant_3 == 0)
    {
        switch (Game_work.value_51)
        {
            case 0:
            case 3:
                flag = 0x66;
                break;
            case 1:
            case 4:
                flag = 0x67;
                break;
            case 2:
            case 5:
                flag = 0x68;
                break;
        }
        if (wp->value_E == 0)
        {
            if ((D_800987E8 == 0 && D_80098B20 == 0) || Sce_flag_test(flag) != 0)
            {
                wp->routine_0 = 3;
                wp->routine_3 = 0x10;
                Sound_call2(0x105, &wp->pos_38);
                Sce_flag_on(flag);
            }
            else if (pl->target_184 == wp)
            {
                pl->target_184 = NULL;
                if (Sce_flag_test(0x65) == 0)
                {
                    MojiTaskExec2(0, 2);
                    Sce_flag_on(0x65);
                }
            }
        }
        else
        {
            wp->value_E--;
        }
    }
    else if (pl->target_184 == wp)
    {
        pl->target_184 = NULL;
        if (!(pl->flags_bd & 0x40))
        {
            pl->flags_bd |= 0x40;
            func_80017C30(0xA);
            Sce_flag_on(0x5F);
            wp->routine_0 = 6;
            wp->routine_1 = 0;
        }
    }
}

void func_80111AF0(STAGE_PANEL_WORK *wp)
{
    wp->matrix.words[0]  = 0x1000;
    wp->matrix.words[2]  = 0x1000;
    wp->matrix.words[4]  = 0x1000;
    wp->matrix.words[1]  = 0;
    wp->matrix.words[3]  = 0;
    wp->matrix.m.m[0][0] = wp->timer_B << 8;
    RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
    if (--wp->timer_B == 0)
    {
        Sound_key_off_voice(0x10);
        wp->routine_0++;
        wp->flags_0 &= ~2;
        STAGE_CELLS[wp->cell_44].value = wp->matrix.words[6];
    }
}

void func_80111BA8(STAGE_OBJ *wp)
{
    if (Sce_flag_test(0x5F) != 0)
    {
        wp->routine_0++;
    }
}

void func_80111BEC(STAGE_PANEL_WORK *wp)
{
    STAGE_CELLS[wp->cell_44].value = wp->matrix.words[5];
    wp->routine_0                  = 2;
}

void func_80111C1C(STAGE_OBJ50 *wp)
{
    if (wp->routine_1 == 0)
    {
        STAGE_CAM_REQ_PTR->mode_C   = 1;
        STAGE_CAM_REQ_PTR->value_E  = 0x1D;
        STAGE_CAM_REQ_PTR->x_0      = D_80115258[Game_work.value_51].x_0;
        STAGE_CAM_REQ_PTR->y_2      = D_80115258[Game_work.value_51].y_2;
        STAGE_CAM_REQ_PTR->z_4      = D_80115258[Game_work.value_51].z_4;
        STAGE_CAM_REQ_PTR->angle_A  = D_80115258[Game_work.value_51].value_6;
        STAGE_CAM_REQ_PTR->value_F  = D_80115258[Game_work.value_51].value_8;
        STAGE_CAM_REQ_PTR->value_11 = 0xFF;
        STAGE_CAM_REQ_PTR->value_D  = 0;
        STAGE_CAM_REQ_PTR->value_10 = 2;
        wp->routine_1++;
    }
    else if (D_800C356C == 2)
    {
        D_800C356C++;
        func_80042314(&Player_work);
        wp->routine_0 = 2;
    }
}

void func_80111D4C(STAGE_OBJ *wp)
{
    func_80031A4C(wp);
}

void func_80111D6C(STAGE_OBJ *wp)
{
    wp->routine_0 = 1;
}

// Spawns the room's turning panel pairs on the cells whose attribute matches a pair's record.
// FAKE MATCH: `j = 1` is set before the key tests and again by the `for`, only for a delay slot.
// The second pair counts with its own variable, `j`, set twice: once before the key tests and
// again as the loop's start value. Retail has `li s3,1` in the delay slot of the first key test
// and no copy in the body. The copy before the tests is the one reorg moves into the slot (from
// the target it can't: s3 still counts as live there after the first pair's `k += 2`). The loop
// pass needs the start value after the body's label to step `rec` as a pointer from list + 16,
// so the `for` sets it again. The one-pass block around `match` hides the first copy from cse1
// (it stops at a loop end), which keeps the second for the loop pass; cse2 then drops the second
// as redundant. A separate counter keeps the first pair's `k` below the hoisted cell offsets in
// the allocator's priority order (s2 for the offset, s3 for the counter).
void func_80111D78(void)
{
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 z;
    sint8 done0;
    sint8 done1;
    ST1D_PANEL_SPAWN *list;
    ST1D_PANEL_SPAWN *rec;
    STAGE_PANEL_WORK *wp;
    sint32 found;
    sint32 i;
    sint32 k;
    sint32 j;
    sint32 x;
    sint32 cell;
    uint8 match;
    list  = NULL;
    found = 0;
    done0 = 0;
    done1 = 0;
    for (i = 0; D_80115220[i].stage != 0xFF; i++)
    {
        if (Game_work.value_50 == D_80115220[i].stage && Game_work.value_51 == D_80115220[i].room)
        {
            list  = D_80115220[i].list;
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        return;
    }
    x0 = STAGE_MAP_X0;
    x1 = STAGE_MAP_X1;
    z0 = STAGE_MAP_Z0;
    z1 = STAGE_MAP_Z1;
    Sce_flag_off(0x5F);
    for (z = z0; z < z1; z++)
    {
        for (x = x0; x < x1; x++)
        {
            cell = *(STAGE_MAP_CELLS + (x - x0) + (z - z0) * STAGE_MAP_W);
            if (cell > 0)
            {
                D_8011A758 = *STAGE_CELL_TBL[cell].info;
                if (done0 == 0 && (list[0].key_0 == D_8011A758 || list[0].type_4 == D_8011A758))
                {
                    k     = 0;
                    match = list[0].key_0 == D_8011A758;
                    for (; k < 4; k += 2)
                    {
                        rec = &list[k];
                        if (match)
                        {
                            D_8011A758                = rec->key_0;
                            STAGE_CELL_TBL[cell].info = (uint32 *)func_8003AC24(rec->type_4);
                        }
                        wp = func_80031734();
                        if (wp != NULL)
                        {
                            done0       = 1;
                            wp->flags_0 = 5;
                            wp->kind_2  = 0x35;
                            if (k == 0)
                            {
                                wp->value_3 = 0;
                            }
                            else
                            {
                                wp->value_3 = 2;
                            }
                            wp->value_D = rec->value_F;
                            func_8002F9C4(wp, &wp->value_D);
                            wp->dir_C           = rec->dir_E;
                            wp->matrix.words[0] = 0x1000;
                            wp->matrix.words[1] = 0;
                            wp->matrix.words[2] = 0x1000;
                            wp->matrix.words[3] = 0;
                            wp->matrix.words[4] = 0x1000;
                            wp->pos_38.x        = STAGE_CELL_TBL[cell].pos.x + rec->x_8;
                            wp->pos_38.z        = STAGE_CELL_TBL[cell].pos.z + rec->z_C;
                            wp->pos_38.y        = STAGE_CELL_TBL[cell].pos.y;
                            RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
                            wp->cell_44         = cell;
                            wp->matrix.words[5] = (uint32)STAGE_CELL_TBL[cell].info;
                            wp->matrix.words[6] = func_8003AC24(rec->key_0);
                        }
                    }
                }
                if (done1 == 0)
                {
                    j = 1;
                    if (list[1].key_0 == D_8011A758 || list[1].type_4 == D_8011A758)
                    {
                        do
                        {
                            match = list[1].key_0 == D_8011A758;
                        } while (0);
                        for (j = 1; j < 4; j += 2)
                        {
                            rec = &list[j];
                            if (match)
                            {
                                D_8011A758                = rec->key_0;
                                STAGE_CELL_TBL[cell].info = (uint32 *)func_8003AC24(rec->type_4);
                            }
                            wp = func_80031734();
                            if (wp != NULL)
                            {
                                done1       = 1;
                                wp->flags_0 = 5;
                                wp->kind_2  = 0x35;
                                if (j == 1)
                                {
                                    wp->value_3 = 0;
                                }
                                else
                                {
                                    wp->value_3 = 2;
                                }
                                wp->value_D = rec->value_F;
                                func_8002F9C4(wp, &wp->value_D);
                                wp->dir_C           = rec->dir_E;
                                wp->matrix.words[0] = 0x1000;
                                wp->matrix.words[1] = 0;
                                wp->matrix.words[2] = 0x1000;
                                wp->matrix.words[3] = 0;
                                wp->matrix.words[4] = 0x1000;
                                wp->pos_38.x        = STAGE_CELL_TBL[cell].pos.x + rec->x_8;
                                wp->pos_38.z        = STAGE_CELL_TBL[cell].pos.z + rec->z_C;
                                wp->pos_38.y        = STAGE_CELL_TBL[cell].pos.y;
                                RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
                                wp->cell_44         = cell;
                                wp->matrix.words[5] = (uint32)STAGE_CELL_TBL[cell].info;
                                wp->matrix.words[6] = func_8003AC24(rec->key_0);
                            }
                        }
                    }
                }
            }
        }
    }
}
