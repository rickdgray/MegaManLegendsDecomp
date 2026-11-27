#include "common.h"
#include "stage_common/stcom19.h"

// Shared stage code, linked into 5 stages: r3_st09, r3_st0e, r3_st13, r3_st14 and r3_st1a. Each
// stage compiles this file against its own copy of the assembly (TARGET_ASM, set by
// tools/cc.sh); the names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom19"

// The panels' spawner (type 0xFF) or a panel: runs its routine, then lights it while the
// player stands on the far side of its edge.
void stcom19_func_0000(STCOM19_WORK *wp)
{
    STCOM_SVECTOR sxy_player;
    STCOM_SVECTOR sxy_edge;
    STCOM_SVECTOR sxy_pos;
    STCOM_SVECTOR edge;
    STCOM_FIXED_VECTOR out;
    STCOM_FIXED_VECTOR player;
    STCOM_FIXED_VECTOR a;
    STCOM_FIXED_VECTOR b;
    STCOM19_MATRIX m;

    if (wp->type == 0xFF)
    {
        stcom19_func_0640();
        func_80031A4C(wp);
        return;
    }
    stcom19_D_0150[wp->routine_0](wp);
    if (Sce_flag_test(0x7B0) == 0)
    {
        edge.x     = -0x200;
        edge.y     = 0;
        edge.z     = 0;
        m.words[0] = 0x1000;
        m.words[1] = 0;
        m.words[2] = 0x1000;
        m.words[3] = 0;
        m.words[4] = 0x1000;
        RotMatrixY((wp->dir_C << 10) + 0x800, &m.m);
        ApplyMatrix(&m.m, &edge, &out);
        edge.x = out.x += wp->pos_38.x;
        edge.y = out.y += wp->pos_38.y;
        edge.z = out.z += wp->pos_38.z;
        STCOM_GTE_SET_MATRIX(0x1F800008);
        STCOM_GTE_LDV0(&Player_work.position);
        STCOM_GTE_RTV0TR();
        STCOM_GTE_STLVNL(&player);
        STCOM_GTE_RTPS();
        STCOM_GTE_STSXY(&sxy_player);
        STCOM_GTE_LDV0(&edge);
        STCOM_GTE_RTV0TR();
        STCOM_GTE_STLVNL(&a);
        STCOM_GTE_RTPS();
        STCOM_GTE_STSXY(&sxy_edge);
        STCOM_GTE_LDV0(&wp->pos_38);
        STCOM_GTE_RTV0TR();
        STCOM_GTE_STLVNL(&b);
        STCOM_GTE_RTPS();
        STCOM_GTE_STSXY(&sxy_pos);
        if (b.x != a.x && (b.z - a.z) * (player.x - a.x) / (b.x - a.x) + a.z < player.z &&
            ((sxy_player.x < sxy_edge.x && sxy_pos.x < sxy_player.x) || (sxy_edge.x < sxy_player.x && sxy_player.x < sxy_pos.x)))
        {
            wp->color_40 = 0x2404040;
            return;
        }
    }
    wp->color_40 = 0x808080;
}

void stcom19_func_02F4(STCOM19_WORK *wp)
{
    wp->be_flag |= TRANS;
    wp->routine_0++;
}

void stcom19_func_0310(STCOM19_WORK *wp)
{
    // Never used; they reserve retail's frame (stcom19_func_0000's locals).
    STCOM_SVECTOR v;
    STCOM_FIXED_VECTOR out;
    STCOM_MATRIX m;

    if (Sce_flag_test(0x7B1) && wp->cell_44 == Map_cell_get(&Player_work.position))
    {
        wp->routine_0 = 2;
        wp->timer_B   = 16;
        Sce_flag_on(0x7B2);
        Sound_call2(0x105, &wp->pos_38);
    }
}

void stcom19_func_0384(STCOM19_WORK *wp)
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
        wp->routine_0++;
        wp->be_flag &= ~TRANS;
        Sound_call(0x185, 0, 0);
        Sce_flag_off(0x7B2);
        STCOM19_CELLS[wp->cell_44].value = wp->matrix.words[6];
    }
}

void stcom19_func_0448(STCOM19_WORK *wp)
{
    if (Sce_flag_test(0x7B0))
    {
        if (!Sce_flag_test(0x7B1))
        {
            wp->timer_B          = 16;
            wp->matrix.words[0]  = 0x1000;
            wp->matrix.words[2]  = 0x1000;
            wp->matrix.words[4]  = 0x1000;
            wp->matrix.words[1]  = 0;
            wp->matrix.words[3]  = 0;
            wp->matrix.m.m[0][0] = 0;
            wp->routine_0++;
            RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
            wp->be_flag |= TRANS;
            Sce_flag_on(0x7B2);
            Sound_call2(0x106, &wp->pos_38);
        }
    }
    else if (wp->cell_44 != Map_cell_get(&Player_work.position))
    {
        wp->timer_B          = 16;
        wp->matrix.words[0]  = 0x1000;
        wp->matrix.words[2]  = 0x1000;
        wp->matrix.words[4]  = 0x1000;
        wp->matrix.words[1]  = 0;
        wp->matrix.words[3]  = 0;
        wp->matrix.m.m[0][0] = 0;
        wp->routine_0++;
        RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
        wp->be_flag |= TRANS;
        Sce_flag_on(0x7B2);
        Sound_call2(0x106, &wp->pos_38);
        Sce_flag_off(0x7B1);
    }
}

void stcom19_func_0574(STCOM19_WORK *wp)
{
    if (--wp->timer_B == 0)
    {
        wp->routine_0++;
        Sound_call(0x186, 0, 0);
        Sce_flag_off(0x7B2);
    }
    wp->matrix.words[0]  = 0x1000;
    wp->matrix.words[2]  = 0x1000;
    wp->matrix.words[4]  = 0x1000;
    wp->matrix.words[1]  = 0;
    wp->matrix.words[3]  = 0;
    wp->matrix.m.m[0][0] = (16 - wp->timer_B) << 8;
    RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
}

void stcom19_func_0614(STCOM19_WORK *wp)
{
    STCOM19_CELLS[wp->cell_44].value = wp->matrix.words[5];
    wp->routine_0                    = 0;
}

// Spawns the room's panels: two on every map cell whose attribute matches a list entry.
void stcom19_func_0640(void)
{
    STCOM_SVECTOR pos;
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 z;
    sint32 count;
    uint32 type;
    STCOM19_SPAWN *list;
    STCOM19_WORK *wp;
    sint32 found;
    sint32 i;
    sint32 k;
    sint32 x;
    sint32 cell;

    list  = (STCOM19_SPAWN *)1;
    found = 0;
    for (i = 0; stcom19_D_0000[i].stage != 0xFF; i++)
    {
        if (Game_work.value_50 == stcom19_D_0000[i].stage && Game_work.value_51 == stcom19_D_0000[i].room)
        {
            found = 1;
            list  = stcom19_D_0000[i].list;
            break;
        }
    }
    if (found == 0)
    {
        return;
    }
    count = STCOM19_GAME_COUNT;
    z0    = STCOM19_MAP_Z0;
    z1    = STCOM19_MAP_Z1;
    x0    = STCOM19_MAP_X0;
    x1    = STCOM19_MAP_X1;
    for (z = z0; z < z1; z++)
    {
        for (x = x0; x < x1; x++)
        {
            cell = *(STCOM19_MAP_CELLS + (x - x0) + (z - z0) * STCOM19_MAP_W);
            if (cell > 0)
            {
                type = *STCOM19_CELL_TBL[cell].info;
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
                                wp->be_flag = MOVE | MODEL;
                                wp->id      = 0x2F;
                                wp->type    = list[k].spawn_E[i] >> 4;
                                Model_work_init(wp, &wp->type);
                                wp->dir_C           = list[k].spawn_E[i] & 0xF;
                                wp->value_D         = count;
                                pos                 = STCOM19_CELL_TBL[cell].pos;
                                wp->pos_38.x        = STCOM19_CELL_TBL[cell].pos.x + list[k].x_8 + stcom19_D_0140[wp->dir_C].x;
                                wp->pos_38.z        = STCOM19_CELL_TBL[cell].pos.z + list[k].z_C + stcom19_D_0140[wp->dir_C].z;
                                wp->pos_38.y        = STCOM19_CELL_TBL[cell].pos.y + list[k].y_A;
                                wp->matrix.words[0] = 0x1000;
                                wp->matrix.words[1] = 0;
                                wp->matrix.words[2] = 0x1000;
                                wp->matrix.words[3] = 0;
                                wp->matrix.words[4] = 0x1000;
                                RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
                                wp->cell_44         = cell;
                                wp->matrix.words[5] = (uint32)STCOM19_CELL_TBL[cell].info;
                                wp->matrix.words[6] = Stage_hed_model_get(list[k].key_0);
                            }
                        }
                        count++;
                        STCOM19_GAME_COUNT++;
                    }
                    k++;
                } while (list[k].key_0 != 0);
            }
        }
    }
}
