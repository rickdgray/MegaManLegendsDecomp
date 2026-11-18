#include "common.h"
#include "stage_common/stcom32.h"

// Shared stage code, linked into 3 stages: r3_st0c, r3_st10 and r3_st11. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom32"

// An item lying about until the player picks it up.
void stcom32_func_0000(STCOM32_WORK *wp)
{
    stcom32_D_0000[wp->routine_0](wp);
    wp->hit_48 = 0;
}

void stcom32_func_004C(STCOM32_WORK *wp)
{
    STCOM32_MATRIX *m;
    STCOM_FIXED_VECTOR scale;
    uint8 i;

    wp->flags_0 |= 2;
    if (wp->variant_3 == 0)
    {
        wp->flags_0 |= 4;
        func_8002F9C4(wp, &wp->variant_3);
        m = &wp->u_14.model.matrix;
        STCOM32_IDENTITY(m);
        scale.x = scale.y = scale.z = 0x300;
        ScaleMatrix(&m->m, &scale);
        RotMatrixX(0x400, &m->m);
        wp->color_40 = 0x808080;
    }
    else
    {
        i = 0;
        while (stcom32_D_0078[i].stage_0 != Game_work.value_50)
        {
            if (stcom32_D_0078[i].stage_0 < 0)
            {
                func_80031A4C(wp);
                return;
            }
            i++;
        }
        wp->flags_0 |= 0x28;
        wp->u_14.sprite.u_E     = stcom32_D_0098[wp->variant_3][0];
        wp->u_14.sprite.v_F     = stcom32_D_0098[wp->variant_3][1];
        wp->u_14.sprite.w_10    = stcom32_D_0098[wp->variant_3][2];
        wp->u_14.sprite.h_12    = stcom32_D_0098[wp->variant_3][3];
        wp->u_14.sprite.x_8     = wp->pos_38.x;
        wp->u_14.sprite.color_4 = 0x808080;
        wp->u_14.sprite.y_A     = wp->pos_38.y;
        wp->u_14.sprite.z_C     = wp->pos_38.z;
        if (wp->variant_3 != 3)
        {
            wp->u_14.sprite.tpage_0 =
                ((stcom32_D_0078[i].clut_y6 << 6) | (stcom32_D_0078[i].clut_x4 / 16)) << 16 |
                (stcom32_D_0078[i].tp_1 << 7 | stcom32_D_0078[i].abr_2 << 5 |
                 stcom32_D_0078[i].page_3);
        }
        else
        {
            wp->u_14.sprite.tpage_0 = (stcom32_D_0078[i].tp_1 << 7 | stcom32_D_0078[i].abr_2 << 5 |
                                       stcom32_D_0078[i].page_3) |
                                      0x3EC00000;
            wp->u_14.sprite.y_A -= wp->u_14.sprite.w_10;
        }
    }
    wp->model_10 = stcom32_D_000C;
    wp->hit_48   = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void stcom32_func_02FC(STCOM32_WORK *wp)
{
    STCOM_SVECTOR pos;

    if (Player_work.target_184 == wp)
    {
        wp->routine_0++;
    }
    if (wp->variant_3 == 0)
    {
        pos = wp->pos_38;
    }
    else
    {
        pos.x   = wp->u_14.sprite.x_8;
        pos.y   = wp->u_14.sprite.y_A;
        pos.z   = wp->u_14.sprite.z_C;
        pos.pad = 0;
        if (wp->variant_3 != 3)
        {
            stcom32_func_0678(wp);
        }
    }
    func_800341BC(&pos, 0x28, 0, 0x8000, wp->index_1, &wp->hit_48, 0x4000000, 0, 0x80);
}

// Picked up: the player holds it up while the message runs.
void stcom32_func_03E8(STCOM32_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM32_MATRIX *m;
    STCOM_FIXED_VECTOR scale;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            pl->value_448 = 0x34;
            wp->timer_A   = 0;
            wp->routine_1++;
            break;
        case 2:
            if (wp->timer_A > 0x10)
            {
                wp->timer_A = 0;
                wp->flags_0 &= ~2;
                wp->routine_1++;
            }
            else
            {
                wp->timer_A++;
            }
            break;
        case 3:
            if (pl->flags_A7 < 0)
            {
                func_8005C150(2, 0, stcom32_D_00A8[wp->variant_3], 0);
                if (wp->variant_3 == 0)
                {
                    wp->flags_0 |= 2;
                    wp->pos_38.x = pl->position.x;
                    wp->pos_38.y = pl->position.y - 0xC8;
                    wp->pos_38.z = pl->position.z;
                }
                wp->routine_1++;
            }
            break;
        case 4:
            if (Moji_flag & 0x8000000)
            {
                if (wp->variant_3 == 0)
                {
                    m = &wp->u_14.model.matrix;
                    STCOM32_IDENTITY(m);
                    scale.x = scale.y = scale.z = 0x400;
                    ScaleMatrix(&m->m, &scale);
                    RotMatrixZ(0, &m->m);
                    RotMatrixY(wp->timer_A << 4, &m->m);
                    RotMatrixX(0, &m->m);
                }
                wp->timer_A += 0xA;
            }
            else
            {
                if (wp->variant_3 == 0)
                {
                    pl->value_448 = 0x35;
                    wp->routine_1++;
                }
                else
                {
                    wp->routine_1 = 0xA;
                }
                wp->flags_0 &= ~2;
            }
            break;
        case 5:
            if (pl->flags_A7 < 0)
            {
                wp->routine_1 = 0xA;
            }
            break;
        case 10:
            Sce_flag_on(stcom32_D_0068[wp->variant_3]);
            func_80042314(pl);
            pl->target_184 = NULL;
            pl->flags_0 |= 2;
            func_80031A4C(wp);
            break;
    }
}

// The sprite cycles through four frames.
void stcom32_func_0678(STCOM32_WORK *wp)
{
    wp->u_14.sprite.u_E = (STCOM32_FRAME * 8) & 0x60;
}
