#include "common.h"
#include "st09.h"

#ifdef __wasm32__
void Sce_flag_off(sint32 flag);
#endif

#ifdef __wasm32__
void func_80031A4C(void *wp);
#endif

#ifdef __wasm32__
void ApplyMatrix(void *matrix, void *vector, void *output);
#endif

void func_80118308(STAGE_PANEL_WORK *wp)
{
    STCOM_SVECTOR sxy_player;
    STCOM_SVECTOR sxy_edge;
    STCOM_SVECTOR sxy_pos;
    STCOM_SVECTOR edge;
    STCOM_FIXED_VECTOR out;
    STCOM_FIXED_VECTOR player;
    STCOM_FIXED_VECTOR a;
    STCOM_FIXED_VECTOR b;
    STAGE_PANEL_MATRIX m;
    sint32 side;

    D_8011E4C0[wp->routine_0](wp);
    if ((sint8)wp->value_D == 0xA)
    {
        wp->flags_0 &= ~2;
        STAGE_CELLS[wp->cell_44].value = wp->matrix.words[6];
    }
    if (Sce_flag_test(0x606) != 0 && (sint8)wp->value_D == 0x17)
    {
        wp->flags_0 &= ~2;
    }
    if (Sce_flag_test(0x7B0) == 0)
    {
        edge.x     = 0x100;
        edge.y     = 0;
        edge.z     = 0;
        m.words[0] = 0x1000;
        m.words[1] = 0;
        m.words[2] = 0x1000;
        m.words[3] = 0;
        m.words[4] = 0x1000;
        // The assignment keeps 0x800 with the side term (retail adds it before the sum).
        RotMatrixY((wp->dir_C << 10) + (side = (wp->value_3 << 11) + 0x800), &m.m);
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

void func_8011864C(STAGE_PANEL_WORK *wp)
{
    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->value_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
    wp->cell_44 = func_80048C60(&wp->pos_38);
    wp->routine_0++;
    wp->matrix.words[5] = STAGE_CELLS[wp->cell_44].value;
    // The cell's record pointer, kept without its segment bits.
    wp->matrix.words[6] = func_8003AC24(*(uint32 *)(wp->matrix.words[5] & 0xFFFFFF) & ~0x1000);
}

// Starts the panel turning when the player stands on it; panel 4 also draws a sprite.
// The unused locals are retail's frame size (as in st00 func_80112568).
void func_80118704(STAGE_PANEL_WORK *wp)
{
    STCOM_SVECTOR_W pos;
    STCOM_MATRIX unused_m;
    STCOM_SVECTOR unused_a;
    STCOM_SVECTOR unused_b;
    uint32 *p;
    uint8 frame;
    uint32 color;

    if (Sce_flag_test(0x7B1) != 0 && wp->cell_44 == func_80048C60(&STAGE_PL.position) && Sce_flag_test((sint8)wp->value_D + 0x7E0) == 0)
    {
        wp->routine_0 = 2;
        wp->timer_B   = 0x10;
        Sce_flag_on(0x7B2);
        Sound_call2(0x105, &wp->pos_38);
    }
    if ((sint8)wp->value_D == 4 && wp->value_3 != 0 && Sce_flag_test(0x7E1) != 0)
    {
        p                      = *ST09_PACKET_PTR;
        D_800BE6D8[D_800988FC] = p;
        *ST09_PACKET_PTR       = p + 10;
        D_800988FC++;
        frame             = wp->reserved09[0];
        color             = D_8011E4B0[frame];
        wp->reserved09[0] = (frame + 1) & 0xF;
        p[1]              = color | 0x2E000000;
        pos.v.x           = 0x4F80;
        pos.v.z           = 0x2BF0;
        pos.v.y           = -0x216;
        p[2]              = pos.words[0];
        p[4]              = pos.words[1];
        p[3]              = 0x3EC0E0E0;
        p[5]              = 0x25E0FF;
        p[7]              = 0xFFE0;
        p[9]              = 0xFFFF;
        p[6]              = 0x20;
        p[8]              = 0;
    }
}

void func_80118878(STAGE_PANEL_WORK *wp)
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
        wp->flags_0 &= ~2;
        Sound_call(0x185, 0, 0);
        Sce_flag_off(0x7B2);
        STAGE_CELLS[wp->cell_44].value = wp->matrix.words[6];
    }
}

void func_8011893C(STAGE_PANEL_WORK *wp)
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
            wp->flags_0 |= 2;
            Sce_flag_on(0x7B2);
            Sound_call2(0x106, &wp->pos_38);
        }
    }
    else if (wp->cell_44 != func_80048C60(&Player_work.position))
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
        wp->flags_0 |= 2;
        Sce_flag_on(0x7B2);
        Sound_call2(0x106, &wp->pos_38);
        Sce_flag_off(0x7B1);
    }
}

void func_80118A68(STAGE_PANEL_WORK *wp)
{
    wp->matrix.words[0]  = 0x1000;
    wp->matrix.words[2]  = 0x1000;
    wp->matrix.words[4]  = 0x1000;
    wp->matrix.words[1]  = 0;
    wp->matrix.words[3]  = 0;
    wp->matrix.m.m[0][0] = (16 - wp->timer_B) << 8;
    RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
    if (--wp->timer_B == 0)
    {
        wp->routine_0++;
        Sound_call(0x186, 0, 0);
        Sce_flag_off(0x7B2);
    }
}

void func_80118B04(STAGE_PANEL_WORK *wp)
{
    STAGE_CELLS[wp->cell_44].value = wp->matrix.words[5];
    wp->routine_0                  = 0;
}

void func_80118B30(STAGE_FX *wp)
{
    D_8011E4D8[wp->routine_0](wp);
    wp->y_30.value = 0;
}

void func_80118B7C(ST09_BOX *wp)
{
    ST09_BOX_CTL *ctl;

    ctl                 = &wp->matrix.f.ctl;
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->color_40              = 0x808080;
    wp->matrix.f.ctl.flags_0  = 0xE;
    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    if (wp->variant_3 & 0xF0)
    {
        wp->life_44 = 0x22;
    }
    else
    {
        wp->life_44 = 0xA0;
    }
    wp->flag_46  = wp->pos_38.pad;
    ctl->hit_4   = 0;
    ctl->value_8 = 0;
    func_80118C3C(wp);
}

void func_80118C3C(ST09_BOX *wp)
{
    if (wp->matrix.f.ctl.flags_0 & 8)
    {
        wp->color_40 = 0x808080;
    }
    wp->matrix.f.ctl.value_2 = rand();
    if (wp->matrix.f.ctl.flags_0 & 2)
    {
        func_80118FC0(wp);
    }
    D_8011E4E4[wp->routine_1](wp);
    if (wp->flags_0 & 1)
    {
        if (wp->routine_1 != 1)
        {
            func_80051B68(wp, 5, -1, 0);
        }
        if ((wp->flags_0 & 1) && (wp->matrix.f.ctl.flags_0 & 4))
        {
            wp->pos_38.y -= 0x80;
            func_800341BC(&wp->pos_38, 0xA0, 0, D_8011E4F4[wp->variant_3 >> 4], wp->index_1, &wp->matrix.f.ctl.hit_4,
                          D_8011E4EC[wp->variant_3 >> 4], 0, 0x80);
            wp->pos_38.y += 0x80;
        }
    }
}

void func_80118D98(STAGE_OBJ *wp)
{
    func_80031A4C(wp);
}

void func_80118DB8(void)
{
}

void func_80118DC0(ST09_BOX *wp)
{
    ST09_BOX_CTL *ctl;
    STCOM_EFFECT *fx;

    ctl = &wp->matrix.f.ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->timer_C   = 1;
            wp->color_40  = 0x808080;
            ctl->flags_0 &= ~8;
            func_80052528(wp);
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0         = 5;
                fx->kind_2          = 0x80;
                fx->variant_3       = 0x42;
                fx->sprite.position = wp->pos_38;
                fx->sprite.position.y -= 0x80;
            }
            // fall through
        case 1:
            if (--wp->timer_C != 0)
            {
                break;
            }
            wp->routine_2 = 2;
            wp->timer_C   = 1;
            wp->color_40  = 0x2E808080;
            // fall through
        case 2:
            if (++wp->timer_C == 5)
            {
                func_80031A4C(wp);
                if ((wp->variant_3 & 0xF) == 1)
                {
                    func_80047228(wp, &wp->pos_38, 2);
                    Sce_flag_on(wp->flag_46);
                    break;
                }
                if ((wp->variant_3 & 0xF) == 2)
                {
                    Sce_flag_on(wp->flag_46);
                }
                func_80047228(wp, &wp->pos_38, ctl->value_2 & 1);
                break;
            }
            wp->color_40 -= 0x202020;
            D_8011E500 = D_8011E504 = D_8011E4FC[0].x += wp->timer_C * 20;
            ScaleMatrix(&wp->matrix.m, D_8011E4FC);
            break;
    }
}

sint32 func_80118FC0(ST09_BOX *wp)
{
    uint32 hit;
    uint32 damage;

    hit    = wp->matrix.f.ctl.hit_4;
    damage = hit & 0xFFFFFF;
    if (damage != 0)
    {
        if (hit & 0x1C000000)
        {
            wp->life_44 -= damage;
            if (wp->life_44 <= 0)
            {
                wp->routine_1             = 1;
                *(uint16 *)&wp->routine_2 = 0;
                wp->matrix.f.ctl.flags_0 &= ~2;
                Sound_call2(0xA2, &wp->pos_38);
            }
            else
            {
                Sound_call2(0xA0, &wp->pos_38);
            }
            wp->color_40 = 0xFFFFFF;
        }
        else
        {
            Sound_call2(0xA3, &wp->pos_38);
        }
    }
    return 1;
}

#ifdef __wasm32__
void func_801196C0(void);
#endif

void func_80119074(STAGE_PANEL_WORK *wp)
{
    STCOM_SVECTOR sxy_player;
    STCOM_SVECTOR sxy_edge;
    STCOM_SVECTOR sxy_pos;
    STCOM_SVECTOR edge;
    STCOM_FIXED_VECTOR out;
    STCOM_FIXED_VECTOR player;
    STCOM_FIXED_VECTOR a;
    STCOM_FIXED_VECTOR b;
    STAGE_PANEL_MATRIX m;
    if (wp->value_3 == 0xFF)
    {
        func_801196C0();
        func_80031A4C(wp);
        return;
    }
    D_8011E5CC[wp->routine_0](wp);
    if (Sce_flag_test(0x7B0) == 0)
    {
        edge.x     = 0x100;
        edge.y     = 0;
        edge.z     = 0;
        m.words[0] = 0x1000;
        m.words[1] = 0;
        m.words[2] = 0x1000;
        m.words[3] = 0;
        m.words[4] = 0x1000;
        RotMatrixY((wp->dir_C << 10) + 0x800 + (wp->value_3 << 11), &m.m);
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

void func_80119374(STAGE_PANEL_WORK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
}

void func_80119390(STAGE_PANEL_WORK *wp)
{
    // Never used; they reserve retail's frame (stcom19_func_0000's locals).
    STCOM_SVECTOR v;
    STCOM_FIXED_VECTOR out;
    STCOM_MATRIX m;

    if (Sce_flag_test(0x7B1) && wp->cell_44 == func_80048C60(&Player_work.position))
    {
        wp->routine_0 = 2;
        wp->timer_B   = 16;
        Sce_flag_on(0x7B2);
        Sound_call2(0x105, &wp->pos_38);
    }
}

void func_80119404(STAGE_PANEL_WORK *wp)
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
        wp->flags_0 &= ~2;
        Sound_call(0x185, 0, 0);
        Sce_flag_off(0x7B2);
        STAGE_CELLS[wp->cell_44].value = wp->matrix.words[6];
    }
}

void func_801194C8(STAGE_PANEL_WORK *wp)
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
            wp->flags_0 |= 2;
            Sce_flag_on(0x7B2);
            Sound_call2(0x106, &wp->pos_38);
        }
    }
    else if (wp->cell_44 != func_80048C60(&Player_work.position))
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
        wp->flags_0 |= 2;
        Sce_flag_on(0x7B2);
        Sound_call2(0x106, &wp->pos_38);
        Sce_flag_off(0x7B1);
    }
}

void func_801195F4(STAGE_PANEL_WORK *wp)
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

void func_80119694(STAGE_PANEL_WORK *wp)
{
    STAGE_CELLS[wp->cell_44].value = wp->matrix.words[5];
    wp->routine_0                  = 0;
}

// Spawns the room's turning panel pairs on the cells whose attribute matches a record.
void func_801196C0(void)
{
    STCOM_SVECTOR pos;
    sint32 x0;
    sint32 x1;
    sint32 z0;
    sint32 z1;
    sint32 z;
    uint8 count;
    uint32 type;
    STAGE_PANEL_SPAWN *list;
    STAGE_PANEL_WORK *wp;
    sint32 found;
    sint32 i;
    sint32 k;
    sint32 x;
    sint32 cell;

    // Unused preset (overwritten before any use), but retail sets it: removing it breaks the match.
    list  = (STAGE_PANEL_SPAWN *)1;
    found = 0;
    for (i = 0; D_8011E55C[i].stage != 0xFF; i++)
    {
        if (Game_work.value_50 == D_8011E55C[i].stage && Game_work.value_51 == D_8011E55C[i].room)
        {
            found = 1;
            list  = D_8011E55C[i].list;
            break;
        }
    }
    if (found == 0)
    {
        return;
    }
    z0    = STAGE_MAP_Z0;
    count = STAGE_PANEL_COUNT;
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
                                wp->kind_2  = 0x21;
                                wp->value_3 = i;
                                Model_work_init(wp, &wp->value_3);
                                wp->dir_C           = list[k].spawn_E[i];
                                wp->value_D         = count;
                                pos                 = STAGE_CELL_TBL[cell].pos;
                                wp->pos_38.x        = D_8011E5AC[wp->dir_C][wp->value_3].x + (STAGE_CELL_TBL[cell].pos.x + list[k].x_8);
                                wp->pos_38.z        = D_8011E5AC[wp->dir_C][wp->value_3].z + (STAGE_CELL_TBL[cell].pos.z + list[k].z_C);
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
