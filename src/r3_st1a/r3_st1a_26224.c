#include "common.h"
#include "st1a.h"

void func_80126224(ST1A_50 *wp)
{
    D_801335C0[wp->routine_0](wp, &Scene_work, &wp->rot_48);
    func_8012642C(wp, &wp->rot_48);
}

void func_80126288(STAGE_FX *wp)
{
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, NULL);
    wp->value_40 = 0x808080;
    if (wp->type == 0)
    {
        wp->value_38.words.integer = 0x100;
    }
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_801262EC(ST1A_50 *wp, STAGE_SCENE_WORK *scene, STCOM_SVECTOR *rot)
{
    D_801335C8[wp->type](wp, scene, rot);
}

void func_80126328(STAGE_FX *wp, STAGE_SCENE_WORK *scene)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 0x19 && scene->value_10 == 5)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            wp->value_38.half[1] -= 0x20;
            if (wp->value_38.half[1] == 0)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            break;
    }
}

void func_801263A8(STAGE_FX *wp, STAGE_SCENE_WORK *scene)
{
    switch (wp->routine_1)
    {
        case 0:
            if (scene->u_8.byte[1] == 4 && scene->value_10 == 0x55)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            wp->value_38.half[1] += 8;
            if (wp->value_38.half[1] == 0x100)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            break;
    }
}

void func_8012642C(ST1A_50 *wp, STCOM_SVECTOR *rot)
{
    STCOM_FIXED_VECTOR scale;

    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    scale.x   = 0x1000;
    scale.y   = 0x1000;
    scale.z   = 0x1000;
    scale.pad = 0;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    RotMatrixY(wp->angle_C << 6, &wp->matrix_18.m);
}

void func_801264AC(STAGE_OBJ *wp)
{
    D_801335D0[wp->routine_0](wp);
    func_801273A0(wp);
    if (wp->u_E.b.work_3 != 0)
    {
        func_8012751C(wp);
    }
}

void func_80126514(STAGE_OBJ *wp)
{
    D_801335DC[wp->type](wp);
}

void func_80126550(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    if (Sce_flag_test(0x5A))
    {
        Stage_idx_model_set(Map_cell_get(&D_8013361C[0]), 0x10060200);
        Stage_idx_model_set(Map_cell_get(&D_8013361C[5]), 0x10060300);
        wp->routine_0 = 2;
        return;
    }
    func_8012742C(wp);
    wp->u_C.b.work_0 = 0;
    wp->u_C.b.work_1 = 0;
    wp->u_E.b.work_3 = 1;
    func_8012748C(wp);
}

void func_801265F4(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    if (Sce_flag_test(0x5B))
    {
        Stage_idx_model_set(Map_cell_get(&D_8013361C[1]), 0x10060200);
        Stage_idx_model_set(Map_cell_get(&D_8013361C[6]), 0x10060300);
        wp->routine_0 = 2;
        return;
    }
    func_8012742C(wp);
    wp->u_C.b.work_0 = 0;
    wp->u_C.b.work_1 = 0;
    wp->u_E.b.work_3 = 1;
    func_8012748C(wp);
}

void func_80126698(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    if (Sce_flag_test(0x5C))
    {
        Stage_idx_model_set(Map_cell_get(&D_8013361C[2]), 0x10060200);
        Stage_idx_model_set(Map_cell_get(&D_8013361C[7]), 0x10060300);
        wp->routine_0 = 2;
        return;
    }
    func_8012742C(wp);
    wp->u_C.b.work_0 = 0;
    wp->u_C.b.work_1 = 0;
    wp->u_E.b.work_3 = 1;
    func_8012748C(wp);
}

void func_8012673C(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    func_8012742C(wp);
    wp->u_C.b.work_0 = 0;
    wp->u_C.b.work_1 = 0;
    wp->u_E.b.work_3 = 1;
    func_8012748C(wp);
}

void func_80126780(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    if (Sce_flag_test(0x56))
    {
        Stage_idx_model_set(Map_cell_get(&D_8013361C[4]), 0x10060100);
        Stage_idx_model_set(Map_cell_get(&D_8013361C[9]), 0x10060102);
        wp->routine_0 = 2;
        return;
    }
    wp->id = 0x2F;
    func_8012742C(wp);
    wp->id           = 0x36;
    wp->u_C.b.work_0 = 0;
    wp->u_C.b.work_1 = 0;
    wp->u_E.b.work_3 = 1;
    func_8012748C(wp);
}

void func_80126830(ST1A_FX *wp)
{
    if (wp->owner_44->type == 4)
    {
        wp->id = 0x2F;
    }
    func_8012742C((STAGE_FX *)wp);
    wp->id      = 0x36;
    wp->work_0  = 1;
    wp->timer_D = 1;
    wp->type_F  = 0;
}

void func_80126890(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    func_8012742C(wp);
    wp->u_C.b.work_0 = 2;
    wp->u_E.b.work_3 = 0;
    wp->u_C.b.work_1 = wp->type != 6;
}

void func_801268D8(STAGE_OBJ *wp)
{
    D_801335FC[wp->type](wp);
}

void func_80126914(STAGE_EV *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (ST1A_GAME_U32(0x174) & 1)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0xB);
                ST1A_GAME_U32(0x174) &= ~1;
                STAGE_PL_BYTE(0xBD) |= 0x40;
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                if (Sce_flag_test(0x5A))
                {
                    wp->routine_1++;
                }
                else
                {
                    STAGE_PL_BYTE(0xBD) &= ~0x40;
                    wp->routine_1 = 0;
                }
            }
            break;
        case 3:
            if (wp->work_2 == 0x20)
            {
                Sound_call(0x105, 0, 0);
            }
            if (--wp->work_2 == 0)
            {
                Sound_call(0x185, 0, 0);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[0]), 0x10060200);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[0 + 5]), 0x10060300);
                STAGE_PL_BYTE(0xBD) &= ~0x40;
                wp->routine_0 = 2;
            }
            break;
    }
}

void func_80126AF0(STAGE_EV *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (ST1A_GAME_U32(0x174) & 2)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0xF);
                ST1A_GAME_U32(0x174) &= ~2;
                STAGE_PL_BYTE(0xBD) |= 0x40;
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                if (Sce_flag_test(0x5B))
                {
                    wp->routine_1++;
                }
                else
                {
                    STAGE_PL_BYTE(0xBD) &= ~0x40;
                    wp->routine_1 = 0;
                }
            }
            break;
        case 3:
            if (wp->work_2 == 0x20)
            {
                Sound_call(0x105, 0, 0);
            }
            if (--wp->work_2 == 0)
            {
                Sound_call(0x185, 0, 0);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[1]), 0x10060200);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[1 + 5]), 0x10060300);
                STAGE_PL_BYTE(0xBD) &= ~0x40;
                wp->routine_0 = 2;
            }
            break;
    }
}

void func_80126CCC(STAGE_EV *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (ST1A_GAME_U32(0x174) & 4)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0x11);
                ST1A_GAME_U32(0x174) &= ~4;
                STAGE_PL_BYTE(0xBD) |= 0x40;
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                if (Sce_flag_test(0x5C))
                {
                    wp->routine_1++;
                }
                else
                {
                    STAGE_PL_BYTE(0xBD) &= ~0x40;
                    wp->routine_1 = 0;
                }
            }
            break;
        case 3:
            if (wp->work_2 == 0x20)
            {
                Sound_call(0x105, 0, 0);
            }
            if (--wp->work_2 == 0)
            {
                Sound_call(0x185, 0, 0);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[2]), 0x10060200);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[2 + 5]), 0x10060300);
                STAGE_PL_BYTE(0xBD) &= ~0x40;
                wp->routine_0 = 2;
            }
            break;
    }
}

void func_80126EA8(STAGE_EV *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (ST1A_GAME_U32(0x174) & 8)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (wp->work_2 == 0x20)
            {
                Sound_call(0x105, 0, 0);
            }
            wp->work_2--;
            if (wp->work_2 == 0)
            {
                Sound_call(0x185, 0, 0);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[3]), 0x10060200);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[3 + 5]), 0x10060300);
                wp->routine_1++;
            }
            break;
        case 2:
            if (STCOM_ABS(Player_work.position.z - 0x500) > 0x200)
            {
                Stage_idx_model_set(Map_cell_get(&D_8013361C[3]), 0x63200);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[3 + 5]), 0x63300);
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->work_2 == 0)
            {
                Sound_call(0x106, 0, 0);
            }
            if (++wp->work_2 == 0x20)
            {
                Sound_call(0x186, 0, 0);
                wp->routine_1 = 0;
            }
            break;
    }
    if (wp->work_2 == 0)
    {
        wp->be_flag &= ~TRANS;
    }
    else
    {
        wp->be_flag |= TRANS;
    }
    ST1A_GAME_U32(0x174) &= ~8;
}

void func_801270D4(STAGE_EV *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (STAGE_GAME_U16(0x17C) == 1)
            {
                STAGE_GAME_U16(0x17C) = 0;
                wp->routine_1         = 3;
            }
            else if (ST1A_GAME_U32(0x174) & 0x10)
            {
                wp->routine_1 = 1;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec2(0, 0x13);
                ST1A_GAME_U32(0x174) &= ~0x10;
                STAGE_PL_BYTE(0xBD) |= 0x40;
                wp->routine_1++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                STAGE_PL_BYTE(0xBD) &= ~0x40;
                wp->routine_1 = 0;
            }
            break;
        case 3:
            if (wp->work_2 == 0x20)
            {
                Sound_call(0x105, 0, 0);
            }
            if (--wp->work_2 == 0)
            {
                Sound_call(0x185, 0, 0);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[4]), 0x10060100);
                Stage_idx_model_set(Map_cell_get(&D_8013361C[4 + 5]), 0x10060102);
                wp->routine_0 = 2;
            }
            break;
    }
}

void func_801272A4(ST1A_FOLLOWER *wp)
{
    ST1A_FOLLOWER *owner;

    owner         = wp->owner_44;
    wp->routine_0 = owner->routine_0;
    wp->value_E   = owner->value_E;
    wp->value_40  = owner->value_40;
    if (wp->value_E == 0)
    {
        wp->be_flag &= ~TRANS;
    }
    else
    {
        wp->be_flag |= TRANS;
    }
}

void func_801272F8(STAGE_FX *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            if (STAGE_SCENE_BYTE(9) == 0x21 && Scene_work.value_10 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (--wp->frame_E == 0)
            {
                wp->routine_1++;
            }
            break;
        case 2:
            break;
    }
}

void func_80127380(STAGE_50 *wp)
{
    func_80031A4C(wp);
}

void func_801273A0(ST1A_50 *wp)
{
    STCOM_FIXED_VECTOR scale;

    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    scale.x   = wp->work_2 << 7;
    scale.y   = 0x1000;
    scale.z   = 0x1000;
    scale.pad = 0;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    RotMatrixY((wp->work_1 != 0) << 11, &wp->matrix_18.m);
}

void func_8012742C(STAGE_FX *wp)
{
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, NULL);
    wp->value_40  = 0x808080;
    wp->frame_E   = 0x20;
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_8012748C(ST1A_50 *wp)
{
    ST1A_50 *child;

    child = (ST1A_50 *)func_80031734();
    if (child != NULL)
    {
        child->be_flag = MOVE;
        child->id      = 0x36;
        child->type    = 5;
        if (wp->type != 4)
        {
            child->pos_38.x = wp->pos_38.x + 0x300;
        }
        else
        {
            child->pos_38.x = wp->pos_38.x + 0x200;
        }
        child->pos_38.y = wp->pos_38.y;
        child->pos_38.z = wp->pos_38.z;
        child->link_44  = wp;
        wp->link_44     = child;
    }
}

void func_8012751C(ST1A_50 *wp)
{
    STCOM_SVECTOR sxy_player;
    STCOM_SVECTOR sxy_edge;
    STCOM_SVECTOR sxy_pos;
    STCOM_SVECTOR edge;
    STCOM_FIXED_VECTOR out;
    STCOM_FIXED_VECTOR player;
    STCOM_FIXED_VECTOR a;
    STCOM_FIXED_VECTOR b;
    STAGE_MATRIX m;
    sint32 edge_x;

    edge_x = 0x200;
    if (wp->type != 4)
    {
        edge_x = 0x300;
    }
    edge.x = edge_x;
    edge.y = 0;
    edge.z = 0;
    m.w[0] = 0x1000;
    m.w[1] = 0;
    m.w[2] = 0x1000;
    m.w[3] = 0;
    m.w[4] = 0x1000;
    RotMatrixY((wp->work_1 != 0) << 11, &m.m);
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
    wp->color_40 = 0x808080;
}

void func_801277C4(STAGE_OBJ *wp)
{
    D_8013366C[wp->routine_0](wp);
    func_80127F3C(wp);
}

void func_80127814(STAGE_OBJ *wp)
{
    D_80133678[wp->type](wp);
}

void func_80127850(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    func_8012800C(wp);
    wp->u_C.b.work_0 = 0;
    wp->u_C.b.work_1 = 0;
    func_8012806C(wp);
}

void func_8012788C(STAGE_OBJ *wp)
{
    func_8012800C(wp);
    wp->u_C.b.work_0 = 1;
    wp->u_C.b.work_1 = 1;
}

void func_801278C0(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;
    sint8 i;

    if (Sce_flag_test(0x57) || Sce_flag_test(0x58) || Sce_flag_test(0x6C))
    {
        wp->routine_0 = 2;
        return;
    }
    wp->value_44 = 0;
    wp->id       = 0x16;
    wp->type     = 0;
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, &wp->type);
    wp->id       = 0x37;
    wp->type     = 2;
    wp->color_40 = 0x2808080;
    func_801280DC(wp);
    for (i = 0; i < 12; i++)
    {
        ep = (STAGE_OBJ50 *)func_80031618();
        if (ep != NULL)
        {
            ep->be_flag  = MOVE;
            ep->id       = 0x18;
            ep->type     = 1;
            ep->u_C.b.lo = wp->work_id;
        }
    }
    wp->value_48  = 0;
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_801279E8(STAGE_OBJ *wp)
{
    wp->id   = 0x16;
    wp->type = 1;
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, &wp->type);
    wp->id                      = 0x37;
    wp->type                    = 3;
    wp->position_fixed_prev.pad = 0x2C808080;
    wp->value_48.value          = 0;
    wp->routine_0               = 1;
    wp->routine_1               = 0;
    wp->routine_2               = 0;
    wp->routine_3               = 0;
}

void func_80127A68(STAGE_OBJ *wp)
{
    func_8012800C(wp);
    wp->u_C.b.work_0 = 2;
    wp->u_C.b.work_1 = wp->type != 4;
}

void func_80127AA8(STAGE_OBJ *wp)
{
    D_80133690[wp->type](wp);
}

void func_80127AE4(STAGE_EV *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            if (Sce_flag_test(0x57))
            {
                wp->routine_1 = 0xFF;
            }
            else
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (ST1A_GAME_U32(0x174) & 0x20)
            {
                ST1A_GAME_U32(0x174) &= ~0x20;
                wp->routine_1++;
            }
            break;
        case 2:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_1++;
            }
            break;
        case 3:
            pl->routine_1++;
            wp->routine_1++;
            break;
        case 4:
            D_800C0F96[0] = 0;
            pl->flags_bd |= 0x20;
            wp->routine_1++;
            break;
        case 5:
            if (wp->work_2 == 0x20)
            {
                Sound_call(0x105, 0, 0);
            }
            if (--wp->work_2 == 0)
            {
                Sound_call(0x185, 0, 0);
                Stage_idx_model_set(Map_cell_get(&D_801336A8[0]), 0x10060400);
                Stage_idx_model_set(Map_cell_get(&D_801336A8[1]), 0x10060500);
                wp->work_3 = 0;
                if (pl->rotation.y < 0x800)
                {
                    wp->routine_1 = 6;
                }
                else if (pl->rotation.y <= 0x800)
                {
                    wp->routine_1 = 8;
                }
                else
                {
                    wp->routine_1 = 7;
                }
            }
            break;
        case 6:
            if ((pl->rotation.y & 0xFFF) > 0x800)
            {
                D_800C0F96[0] = 0;
                pl->flags_bd |= 0x10;
                pl->pos_438   = pl->position;
                pl->fixed_428 = pl->position_fixed;
                pl->value_442 = 0x800;
                pl->value_440 = 0;
                pl->value_444 = 0;
                wp->routine_1 = 8;
            }
            else
            {
                D_800C0F96[0] = ST1A_PL_U16(pl, 0x12A);
            }
            break;
        case 7:
            if ((pl->rotation.y & 0xFFF) < 0x800)
            {
                D_800C0F96[0] = 0;
                pl->flags_bd |= 0x10;
                pl->pos_438   = pl->position;
                pl->fixed_428 = pl->position_fixed;
                pl->value_442 = 0x800;
                pl->value_440 = 0;
                pl->value_444 = 0;
                wp->routine_1 = 8;
            }
            else
            {
                D_800C0F96[0] = ST1A_PL_U16(pl, 0x128);
            }
            break;
        case 8:
            Sound_fade_start(0x10);
            wp->routine_1++;
            // fall through
        case 9:
            D_800C0F96[0] = pl->value_124;
            if (pl->position.z > 0x300)
            {
                D_800C0F96[0] = 0;
                wp->routine_1++;
            }
            break;
        case 10:
            D_800C0F96[0] = 0;
            if (++wp->work_3 == 0xF)
            {
                wp->work_2 = 0x20;
                Stage_idx_model_set(Map_cell_get(&D_801336A8[0]), 0x60400);
                Stage_idx_model_set(Map_cell_get(&D_801336A8[1]), 0x60500);
                wp->routine_1++;
            }
            break;
        case 11:
            if (Sound_fade_flags == 0)
            {
                Sce_flag_on(0x57);
                wp->routine_1 = 0xFF;
            }
            break;
    }
}

void func_80127EA4(ST1A_FOLLOWER *wp)
{
    wp->routine_0 = wp->owner_44->routine_0;
    wp->value_E   = wp->owner_44->value_E;
    if (wp->value_E == 0)
    {
        wp->be_flag &= ~TRANS;
    }
    else
    {
        wp->be_flag |= TRANS;
    }
}

void func_80127EE8(STAGE_OBJ *wp)
{
    wp->value_48.value = (wp->value_48.value + 8) & 0xFFF;
}

void func_80127F00(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    child        = wp->child_44;
    wp->child_48 = child->value_48.value;
}

void func_80127F14(void)
{
}

void func_80127F1C(STAGE_50 *wp)
{
    func_80031A4C(wp);
}

void func_80127F3C(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;

    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    if (wp->type == 2 || wp->type == 3)
    {
        scale.x = scale.y = scale.z = 0x600;
        scale.pad                   = 0;
        ScaleMatrix(&wp->matrix.m, &scale);
        RotMatrixY(wp->value_48, &wp->matrix.m);
    }
    else
    {
        scale.x   = wp->value_E << 7;
        scale.y   = 0x1000;
        scale.z   = 0x1000;
        scale.pad = 0;
        ScaleMatrix(&wp->matrix.m, &scale);
        RotMatrixY((wp->u_C.b.hi != 0) << 11, &wp->matrix.m);
    }
}

void func_8012800C(STAGE_FX *wp)
{
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, NULL);
    wp->value_40  = 0x808080;
    wp->frame_E   = 0x20;
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

void func_8012806C(ST1A_50 *wp)
{
    ST1A_50 *child;

    child = (ST1A_50 *)func_80031734();
    if (child != NULL)
    {
        child->be_flag  = MOVE;
        child->id       = 0x37;
        child->type     = 1;
        child->pos_38.x = wp->pos_38.x + 0x400;
        child->pos_38.y = wp->pos_38.y;
        child->pos_38.z = wp->pos_38.z;
        child->link_44  = wp;
        wp->link_44     = child;
    }
}

void func_801280DC(ST1A_50 *wp)
{
    ST1A_50 *child;

    child = (ST1A_50 *)func_80031734();
    if (child != NULL)
    {
        child->be_flag  = MOVE;
        child->id       = 0x37;
        child->type     = 3;
        child->pos_38.x = wp->pos_38.x;
        child->pos_38.y = wp->pos_38.y;
        child->pos_38.z = wp->pos_38.z;
        child->link_44  = wp;
        wp->link_44     = child;
    }
}

void func_8012814C(ST1A_50 *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;

    switch (wp->routine_0)
    {
        case 0:
            wp->be_flag |= TRANS | MODEL;
            Model_work_init(wp, &wp->type);
            wp->color_40 = 0x808080;
            wp->routine_0++;
            // fall through
        case 1:
            rot.x = 0;
            rot.y = 0;
            rot.z = 0;
            RotMatrixYXZ(&rot, &wp->matrix_18.m);
            scale.x = 0x1000;
            scale.y = 0x1000;
            scale.z = 0x1000;
            ScaleMatrix(&wp->matrix_18.m, &scale);
            break;
    }
}

void func_801281F8(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale = {0x2000, 0x2000, 0x2000, 0};

    D_801336B8[wp->routine_0](wp);
    if (wp->u_C.b.lo == -1)
    {
        if ((wp->value_E & 3) == 0)
        {
            wp->u_C.b.hi += wp->u_C.b.lo;
        }
        wp->value_E++;
    }
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[3] = 0;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    wp->pos_38.y += wp->u_C.b.hi;
    ScaleMatrix(&wp->matrix.m, &scale);
    RotMatrixY(0x800, &wp->matrix.m);
}

void func_80128310(STAGE_FX *wp)
{
    wp->id = 0x29;
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, &wp->type);
    wp->work_0    = 0;
    wp->id        = 0x3B;
    wp->value_40  = 0x808080;
    wp->timer_D   = 4;
    wp->frame_E   = 0;
    wp->type_F    = 0;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_0++;
}

void func_8012838C(STAGE_OBJ *wp)
{
    D_801336C0[wp->routine_1](wp, &Scene_work);
}

void func_801283CC(STAGE_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_E.b.work_3;
    if (temp_v1 == 0x66)
    {
        wp->u_E.b.work_2 = 0;
        wp->u_C.b.work_0 = -1;
    }
    else if (temp_v1 == 0x76)
    {
        wp->u_C.b.work_0 = 0;
        wp->u_C.b.work_1 = 0;
        wp->routine_2    = 0;
        wp->routine_1++;
    }
    wp->u_E.b.work_3++;
}

void func_80128420(STAGE_FX *wp, STAGE_SCENE_WORK *scene)
{
    switch (wp->routine_2)
    {
        case 0:
            if (scene->u_8.byte[1] == 0xF && scene->value_10 == 0x258)
            {
                wp->frame_E = 0;
                wp->work_0  = -1;
                wp->timer_D = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (scene->value_10 == 0x268)
            {
                wp->work_0 = 0;
                wp->routine_2++;
            }
            break;
        case 2:
            break;
    }
}
