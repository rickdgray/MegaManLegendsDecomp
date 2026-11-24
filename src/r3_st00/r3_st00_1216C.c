#include "common.h"
#include "st00.h"

void func_8011216C(ST00_STCOM19_WORK *wp)
{
    STCOM_SVECTOR sxy_player;
    STCOM_SVECTOR sxy_edge;
    STCOM_SVECTOR sxy_pos;
    STCOM_SVECTOR edge;
    STCOM_FIXED_VECTOR out;
    STCOM_FIXED_VECTOR player;
    STCOM_FIXED_VECTOR a;
    STCOM_FIXED_VECTOR b;
    ST00_STCOM19_MATRIX m;
    sint32 rot;

    D_8011C928[wp->routine_0](wp);
    if ((sint8)wp->value_D == 10)
    {
        wp->flags_0 &= ~2;
        ST00_SLOTS[wp->cell_44].value_0 = wp->matrix.words[6];
    }
    if (Sce_flag_test(0x606) && (sint8)wp->value_D == 0x17)
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
        // The assignment keeps (value_3 << 11) + 0x800 together, as retail adds it last.
        RotMatrixY((wp->dir_C << 10) + (rot = (wp->value_3 << 11) + 0x800), &m.m);
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

void func_801124B0(ST00_STCOM19_WORK *wp)
{
    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->value_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    RotMatrixY(wp->dir_C << 10, &wp->matrix.m);
    wp->cell_44 = Map_cell_get(&wp->pos_38);
    wp->routine_0++;
    wp->matrix.words[5] = ST00_SLOTS[wp->cell_44].value_0;
    wp->matrix.words[6] = Stage_hed_model_get(*(uint32 *)(wp->matrix.words[5] & 0xFFFFFF) & ~0x1000);
}

void func_80112568(STAGE_PANEL_WORK *wp)
{
    STCOM_SVECTOR_W pos;
    STCOM_MATRIX unused_m;
    STCOM_SVECTOR unused_a;
    STCOM_SVECTOR unused_b;
    uint32 *p;
    uint8 frame;
    uint32 color;

    if (Sce_flag_test(0x7B1) != 0 && wp->cell_44 == Map_cell_get(&Player_work.position) && Sce_flag_test((sint8)wp->value_D + 0x7E0) == 0)
    {
        wp->routine_0 = 2;
        wp->timer_B   = 0x10;
        Sce_flag_on(0x7B2);
        Sound_call2(0x105, &wp->pos_38);
    }
    if ((sint8)wp->value_D == 4 && wp->value_3 != 0 && Sce_flag_test(0x7E1) != 0)
    {
        p                            = *(uint32 **)STAGE_PACKET_PTR;
        D_800BE6D8[D_800988FC]       = p;
        *(uint32 **)STAGE_PACKET_PTR = p + 10;
        D_800988FC++;
        frame             = wp->reserved09[0];
        color             = D_8011C918[frame];
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

void func_801126DC(STAGE_PANEL_WORK *wp)
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
        ST00_SLOTS[wp->cell_44].value_0 = wp->matrix.words[6];
    }
}

void func_801127A0(ST00_STCOM19_WORK *wp)
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
        wp->flags_0 |= 2;
        Sce_flag_on(0x7B2);
        Sound_call2(0x106, &wp->pos_38);
        Sce_flag_off(0x7B1);
    }
}

void func_801128CC(STAGE_PANEL_WORK *wp)
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

void func_80112968(ST00_10C *wp)
{
    ST00_SLOTS[wp->value_44].value_0 = wp->value_2C;
    wp->routine_0                    = 0;
}

void func_80112994(STAGE_OBJ *wp)
{
    if (wp->routine_0 != 0)
    {
        func_80112B28(wp);
        return;
    }
    func_801129D4(wp);
}

void func_801129D4(ST00_STCOM19_WORK *wp)
{
    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->value_3);
    wp->pos_38.x = D_8011C940[wp->value_3 * 3];
    wp->pos_38.y = D_8011C942[wp->value_3 * 3];
    wp->pos_38.z = D_8011C944[wp->value_3 * 3];
    wp->color_40 = 0x2C808080;
    wp->value_D  = 100;
    wp->routine_0++;
    STAGE_MATRIX_IDENTITY(wp->matrix.words);
}

void func_80112AB4(STAGE_OBJ *wp)
{
    wp->routine_1 = (uint8)wp->u_C.b.byte_C;
}

void func_80112AC0(STAGE_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    if (temp_v1 != 0xA)
    {
        wp->u_C.b.byte_D = temp_v1 - 1;
        return;
    }
    wp->routine_1    = 0;
    wp->u_C.b.byte_C = 0;
}

void func_80112AF4(STAGE_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    if (temp_v1 == 0x64)
    {
        wp->routine_1    = 0;
        wp->u_C.b.byte_C = 0;
        return;
    }
    wp->u_C.b.byte_D = temp_v1 + 1;
}

void func_80112B28(ST00_SCALER *wp)
{
    sint16 scale;

    D_8011C94C[wp->routine_1](wp);
    scale                   = (wp->scale_D << 12) / 100;
    wp->matrix_18.m.m[0][0] = scale;
    wp->matrix_18.m.m[2][2] = scale;
}

void func_80112B9C(STAGE_OBJ *wp)
{
    if (wp->routine_0 != 0)
    {
        func_80113EA4(wp);
        return;
    }
    func_80112BDC(wp);
}

void func_80112BDC(ST00_MATRIX_OBJ *wp)
{
    wp->flags_0 |= 6;
    if (wp->variant_3 == 0 || wp->variant_3 == 0xA)
    {
        wp->flags_0 |= 8;
    }
    if (wp->variant_3 == 8)
    {
        Model_work_init(wp, NULL);
    }
    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    wp->routine_0++;
}

void func_80112C70(STAGE_OBJ *wp)
{
    wp->value_44.value = 0;
    wp->routine_2++;
}

void func_80112C84(STAGE_OBJ *wp)
{
    wp->value_44.value += 0x91A2B;
}

void func_80112C9C(ST00_LOWER *wp)
{
    D_8011CA08[wp->routine_2](wp);
    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    RotMatrixY(wp->value_44.half[1], &wp->matrix_18.m);
}

void func_80112D14(STAGE_MATRIX_OBJ *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STCOM_SVECTOR ofs;
    STCOM_MATRIX m;
    STAGE_MATRIX world;
    ST00_PL_HANDS *pl;

    if (wp->index_C != 0)
    {
        func_80031988(wp);
    }
    pl    = STAGE_SCENE_OBJ(0);
    rot.x = 0x400;
    rot.y = 0;
    rot.z = 0;
    RotMatrix(&rot, &m);
    MulMatrix0(&pl->matrix_2A0, &m, &world.m);
    wp->matrix_18.w[0] = world.w[0];
    wp->matrix_18.w[1] = world.w[1];
    wp->matrix_18.w[2] = world.w[2];
    wp->matrix_18.w[3] = world.w[3];
    wp->matrix_18.w[4] = world.w[4];
    wp->matrix_18.w[5] = world.w[5];
    wp->matrix_18.w[6] = world.w[6];
    wp->matrix_18.w[7] = world.w[7];
    scale.x = scale.y = scale.z = 0x8000;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    rot.x = 0x50;
    rot.y = 0;
    rot.z = -0x140;
    ApplyMatrixSV(&world.m, &rot, &ofs);
    wp->pos_38.x = ofs.x + pl->pos_198.x;
    wp->pos_38.y = ofs.y + pl->pos_198.y;
    wp->pos_38.z = ofs.z + pl->pos_198.z;
    wp->color_40 = 0x02808080;
}

void func_80112E80(STAGE_MATRIX_OBJ *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    STCOM_SVECTOR unused_rot;
    STCOM_MATRIX m;
    STCOM_MATRIX unused_m;
    ST00_PL_HANDS *pl;

    pl    = STAGE_SCENE_OBJ(0);
    rot.x = 0x400;
    rot.y = 0;
    rot.z = 0;
    RotMatrix(&rot, &m);
    MulMatrix0(&pl->matrix_2A0, &m, &wp->matrix_18.m);
    scale.x = scale.y = scale.z = 0x8000;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    wp->pos_38.x = (pl->hand_1A0.x + pl->hand_1B8.x) / 2;
    wp->pos_38.y = (pl->hand_1A0.y + pl->hand_1B8.y) / 2;
    wp->pos_38.z = (pl->hand_1A0.z + pl->hand_1B8.z) / 2;
    wp->color_40 = 0x02808080;
}

void func_80112F70(STAGE_MATRIX_OBJ *wp)
{
    STCOM_FIXED_VECTOR unused_pos;
    STCOM_SVECTOR rot;
    STCOM_SVECTOR unused_rot;
    STAGE_MATRIX unused_m[2];
    ST00_OBJ *pl;

    pl = ST00_SCENE.slot_24[0];
    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    rot.x = 0x400;
    rot.y = 0;
    rot.z = 0;
    RotMatrix(&rot, &wp->matrix_18.m);
    wp->pos_38.x = pl->value_180 - 0x14;
    wp->pos_38.y = pl->value_182;
    wp->pos_38.z = pl->value_184;
    wp->color_40 = 0x02808080;
}

void func_80113010(STAGE_OBJ *wp)
{
    D_8011CA10[wp->routine_1](wp);
}

void func_8011304C(void)
{
}

void func_80113054(STAGE_FX *wp)
{
    if (*(uint16 *)0x1F800002 & 1)
    {
        wp->value_38.words.integer = (uint16)wp->value_38.words.integer + 2;
    }
    else
    {
        wp->value_38.words.integer = (uint16)wp->value_38.words.integer - 2;
    }
}

void func_8011308C(ST00_FX *wp)
{
    wp->value_44 = wp->value_38.words.integer << 0x10;
    wp->routine_2++;
}

void func_801130A8(STAGE_OBJ *wp)
{
    wp->value_44.value += 0x1999A;
}

void func_801130C0(ST00_LOWER *wp)
{
    D_8011CA20[wp->routine_2](wp);
    wp->pos_38.y = wp->value_44.value >> 16;
    if (STAGE_FRAME & 1)
    {
        wp->pos_38.y += 2;
    }
    else
    {
        wp->pos_38.y -= 2;
    }
}

void func_80113130(STAGE_OBJ *wp)
{
    D_8011CA28[wp->routine_1](wp);
}

void func_8011316C(STAGE_MATRIX_OBJ *wp)
{
    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
}

void func_80113194(STAGE_MATRIX_OBJ *wp)
{
    STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
    wp->pos_38.y = ST00_SCENE.slot_24[0]->pal[6].value_4;
    wp->routine_2++;
}

void func_801131D8(STAGE_MATRIX_OBJ *wp)
{
    ST00_OBJ *pl;
    sint16 top;
    uint8 height;

    pl     = ST00_SCENE.slot_24[0];
    top    = pl->pal[6].value_4;
    height = D_8011C9FC[pl->u_E.b.byte_E][*pl->anim_98];
    if (wp->pos_38.y >= top - height)
    {
        wp->pos_38.y = top - height;
        if (rand() % 6 == 0)
        {
            func_80113E10(wp);
        }
    }
}

void func_80113280(STAGE_OBJ *wp)
{
    D_8011CA34[wp->routine_2](wp);
}

void func_801132BC(STAGE_OBJ *wp)
{
    *(uint32 *)&wp->u_C = 0;
    wp->routine_2++;
    STAGE_SCENE.slot_24[10]->routine_1 = 1;
    STAGE_SCENE.slot_24[10]->routine_2 = 0;
}

void func_801132EC(ST00_LOWER *wp)
{
    sint32 y;

    y = wp->y_C;
    y -= 0x14000;
    if (y <= -0x320000)
    {
        wp->routine_2++;
        STAGE_SCENE.slot_24[10]->routine_1 = 0;
        STAGE_SCENE.slot_24[10]->routine_2 = 0;
    }
    wp->y_C      = y;
    wp->pos_38.y = y >> 16;
}

void func_8011334C(void)
{
}

void func_80113354(STAGE_OBJ *wp)
{
    STCOM_FIXED_VECTOR unused;

    D_8011CA3C[wp->routine_2](wp);
}

void func_80113390(ST00_FX *wp)
{
    wp->value_C  = 0x12;
    wp->value_44 = wp->value_38.words.integer << 0x10;
    wp->routine_2++;
}

void func_801133B4(ST00_FX *wp)
{
    wp->value_44 += 0x14000;
    wp->value_38.words.integer = wp->value_44 >> 16;
    if (rand() % 6 == 0)
    {
        func_80113E10((STAGE_MATRIX_OBJ *)wp);
    }
    if (wp->value_38.words.integer > 0)
    {
        wp->routine_2++;
    }
}

void func_8011344C(STAGE_MATRIX_OBJ *wp)
{
    if (STAGE_FRAME & 1)
    {
        wp->pos_38.y = -2;
    }
    else
    {
        wp->pos_38.y = 2;
    }
    if (--wp->index_C == 0)
    {
        wp->pos_38.y = 0;
        wp->routine_2++;
    }
}

void func_801134A0(void)
{
}

void func_801134A8(STAGE_OBJ *wp)
{
    D_8011CA48[wp->routine_2](wp);
}

void func_801134E4(STAGE_OBJ *wp)
{
    D_8011CA58[wp->routine_1](wp);
}

void func_80113520(void)
{
}

void func_80113528(ST00_FX *wp)
{
    wp->value_44 = (sint16)wp->value_3C.words.fraction << 0x10;
    wp->routine_2++;
}

void func_80113544(ST00_FX *wp)
{
    sint32 temp_v0;

    temp_v0                     = wp->value_44 + 0xFFFD8000;
    wp->value_44                = temp_v0;
    wp->value_3C.words.fraction = (uint16)(temp_v0 >> 0x10);
}

void func_80113564(STAGE_OBJ *wp)
{
    D_8011CA68[wp->routine_2](wp);
}

void func_801135A0(STAGE_OBJ *wp)
{
    D_8011CA70[wp->routine_1](wp);
}

void func_801135DC(void)
{
}

void func_801135E4(STAGE_OBJ *wp)
{
    wp->u_C.b.byte_C   = 0x12;
    wp->value_44.value = 0;
    wp->routine_2++;
}

void func_80113600(ST00_FX *wp)
{
    wp->value_44 += 0x14E80;
    wp->value_38.words.integer += wp->value_44 >> 16;
    if (wp->value_38.words.integer > 0)
    {
        func_80113C30((STAGE_MATRIX_OBJ *)wp);
        D_800BC744[0] += 0x100000;
        wp->routine_2++;
        return;
    }
    if ((rand() & 3) == 0)
    {
        func_80113C98((STAGE_MATRIX_OBJ *)wp);
    }
}

void func_801136A4(STAGE_OBJ *wp)
{
    D_800BC744[0] -= 0x100000;
    wp->routine_2++;
}

void func_801136D0(STAGE_MATRIX_OBJ *wp)
{
    if (STAGE_FRAME & 1)
    {
        wp->pos_38.y = -2;
    }
    else
    {
        wp->pos_38.y = 2;
    }
    if (--wp->index_C == 0)
    {
        wp->pos_38.y = 0;
        wp->routine_2++;
    }
}

void func_80113724(void)
{
}

void func_8011372C(STAGE_OBJ *wp)
{
    D_8011CA78[wp->routine_2](wp);
}

void func_80113768(STAGE_OBJ *wp)
{
    D_8011CA8C[wp->routine_1](wp);
}

void func_801137A4(STAGE_MATRIX_OBJ *wp)
{
    if (wp->index_C != 0)
    {
        STAGE_MATRIX_IDENTITY(wp->matrix_18.w);
        wp->color_40 = 0x808080;
        wp->index_C  = 0;
        wp->flags_0 |= 6;
    }
}

void func_801137FC(void)
{
}

void func_80113804(STAGE_OBJ *wp)
{
    wp->u_E.b.byte_E = 0;
    wp->u_C.b.byte_D = 0;
    wp->routine_2++;
}

void func_8011381C(ST00_MATRIX_OBJ *wp)
{
    uint8 *uv;

    if (++wp->count_D == 3)
    {
        wp->count_D = 0;
        uv          = Model_face_get(wp->model_14, 0x10001);
        uv[0] = uv[2] = D_8011CA94[wp->frame_E][0] + 1;
        uv[4] = uv[6] = D_8011CA94[wp->frame_E][0] + 0x1F;
        uv[1]         = D_8011CA94[wp->frame_E][1] + 0x2F;
        uv[3]         = D_8011CA94[wp->frame_E][1] + 0x10;
        uv[5]         = D_8011CA94[wp->frame_E][1] + 0x3E;
        uv[7]         = D_8011CA94[wp->frame_E][1] + 1;
        uv            = Model_face_get(wp->model_14, 0x10000);
        uv[0] = uv[2] = D_8011CA94[wp->frame_E][0] + 0x1F;
        uv[4] = uv[6] = D_8011CA94[wp->frame_E][0] + 0x3E;
        uv[1]         = D_8011CA94[wp->frame_E][1] + 0x3E;
        uv[3]         = D_8011CA94[wp->frame_E][1] + 1;
        uv[5]         = D_8011CA94[wp->frame_E][1] + 0x2F;
        uv[7]         = D_8011CA94[wp->frame_E][1] + 0x10;
        if (++wp->frame_E == 6)
        {
            wp->count_D = 0;
            wp->routine_2++;
        }
    }
}

void func_80113A6C(ST00_MATRIX_OBJ *wp)
{
    if (++wp->count_D == 7)
    {
        wp->count_D = 0;
        wp->routine_2++;
        D_800BC744[0] += 0x100000;
    }
    wp->pos_38.z -= 0x49;
    if (!(rand() & 3))
    {
        func_80113D64(wp);
    }
}

void func_80113B00(STAGE_OBJ *wp)
{
    D_800BC744[0] -= 0x100000;
    wp->routine_2++;
}

void func_80113B2C(STAGE_FX *wp)
{
    sint8 temp_v0;

    temp_v0     = (uint8)wp->timer_D + 1;
    wp->timer_D = temp_v0;
    if (temp_v0 == 2)
    {
        wp->routine_2++;
    }
    wp->value_3C.words.fraction += 0x20;
}

void func_80113B70(void)
{
}

void func_80113B78(STAGE_OBJ *wp)
{
    D_8011CAA0[wp->routine_2](wp);
}

void func_80113BB4(STAGE_OBJ *wp)
{
    D_8011CAB8[wp->routine_1](wp);
}

void func_80113BF0(STAGE_MATRIX_OBJ *wp)
{
    STAGE_MATRIX_OBJ *src;

    src          = (STAGE_MATRIX_OBJ *)STAGE_SCENE.slot_24[wp->index_C + 7];
    wp->pos_38.x = src->pos_38.x;
    wp->pos_38.y = src->pos_38.y;
    wp->pos_38.z = src->pos_38.z;
}

void func_80113C30(STAGE_MATRIX_OBJ *wp)
{
    STAGE_FX *fx;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 4;
        fx->variant_3 = 0;
        fx->value_C   = 4;
        fx->timer_D   = 0;
        fx->x_1C      = wp->pos_38.x;
        fx->y_1E      = 0;
        fx->z_20      = wp->pos_38.z;
        fx->routine_0 = 0;
        fx->routine_1 = 0;
    }
}

void func_80113C98(STAGE_MATRIX_OBJ *wp)
{
    STAGE_FX *fx;
    sint32 v;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        rand();
        fx->flags_0   = 1;
        fx->kind_2    = 3;
        fx->variant_3 = 0;
        fx->value_C   = 3;
        fx->timer_D   = 0;
        fx->type_F    = 0;
        v             = wp->pos_38.x;
        fx->x_1C      = (rand() & 1) ? v - 0x182 : v + 0x182;
        fx->y_1E      = wp->pos_38.y + (rand() & 0x1FF) - 0xCF;
        v             = wp->pos_38.z;
        fx->z_20      = (rand() & 1) ? v - 0x40 : v + 0x40;
        fx->routine_0 = 0;
        fx->routine_1 = 0;
    }
}

void func_80113D64(STAGE_MATRIX_OBJ *wp)
{
    STAGE_FX *fx;
    sint32 x;

    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        rand();
        fx->flags_0   = 1;
        fx->kind_2    = 3;
        fx->variant_3 = 0;
        fx->value_C   = 3;
        fx->timer_D   = 0;
        fx->type_F    = 0;
        x             = wp->pos_38.x;
        fx->x_1C      = (rand() & 1) ? x - 0x80 : x + 0x80;
        fx->y_1E      = wp->pos_38.y - 0x20;
        fx->z_20      = wp->pos_38.z;
        fx->routine_0 = 0;
        fx->routine_1 = 0;
    }
}

void func_80113E10(STAGE_MATRIX_OBJ *wp)
{
    STAGE_FX *ep;

    ep = (STAGE_FX *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 3;
        ep->variant_3 = 0;
        ep->value_C   = 3;
        ep->timer_D   = 0;
        ep->type_F    = 1;
        ep->x_1C      = wp->pos_38.x + (rand() & 0xFF) - 0x7F;
        ep->y_1E      = wp->pos_38.y;
        ep->z_20      = wp->pos_38.z;
        ep->routine_0 = 0;
        ep->routine_1 = 0;
    }
}

void func_80113E9C(void)
{
}

void func_80113EA4(STAGE_OBJ *wp)
{
    D_8011CAC0[wp->variant_3](wp);
}

void func_80113EE0(STAGE_FX *wp)
{
    D_8011CAE4[wp->routine_0](wp);
    wp->y_30.value = 0;
}

void func_80113F2C(ST00_TARGET *wp)
{
    ST00_TARGET_HIT *hit;

    hit = &wp->u_18.h.hit;
    STAGE_MATRIX_IDENTITY(wp->u_18.matrix.w);
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->color_40              = 0x808080;
    wp->u_18.h.hit.flags_0    = 0xE;
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
    wp->value_46 = wp->pos_38.pad;
    hit->hit_4   = 0;
    hit->value_8 = 0;
    func_80113FEC(wp);
}

void func_80113FEC(ST00_BOX_B *wp)
{
    if (wp->matrix.f.ctl.flags_0 & 8)
    {
        wp->color_40 = 0x808080;
    }
    wp->matrix.f.ctl.value_2 = rand();
    if (wp->matrix.f.ctl.flags_0 & 2)
    {
        func_80114370(wp);
    }
    D_8011CAF0[wp->routine_1](wp);
    if (wp->flags_0 & 1)
    {
        if (wp->routine_1 != 1)
        {
            func_80051B68(wp, 5, -1, 0);
        }
        if ((wp->flags_0 & 1) && (wp->matrix.f.ctl.flags_0 & 4))
        {
            wp->pos_38.y -= 0x80;
            func_800341BC(&wp->pos_38, 0xA0, 0, D_8011CB00[wp->variant_3 >> 4], wp->index_1, &wp->matrix.f.ctl.hit_4,
                          D_8011CAF8[wp->variant_3 >> 4], 0, 0x80);
            wp->pos_38.y += 0x80;
        }
    }
}

void func_80114148(STAGE_50 *wp)
{
    func_80031A4C(wp);
}

void func_80114168(void)
{
}

void func_80114170(ST00_BOX_B *wp)
{
    ST00_BOX_CTL *ctl;
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
            D_8011CB0C = D_8011CB10 = D_8011CB08[0].x += wp->timer_C * 20;
            ScaleMatrix(&wp->matrix.m, D_8011CB08);
            break;
    }
}

sint32 func_80114370(ST00_TARGET *wp)
{
    sint32 hit;
    sint32 damage;

    hit    = wp->u_18.h.hit.hit_4;
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
                wp->u_18.h.hit.flags_0 &= ~2;
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

void func_80114424(STAGE_OBJ *wp)
{
    D_8011CB18[wp->routine_0](wp);
}

void func_80114460(STAGE_OBJ *wp)
{
    sint16 i;
    ST00_BOX *box;

    wp->routine_0             = 1;
    wp->routine_1             = 0;
    *(uint16 *)&wp->routine_2 = 0;
    for (i = 0; D_8011CC9C[i] != (ST00_BOX *)-1; i++)
    {
        if (D_8011CC9C[i] != NULL)
        {
            box = D_8011CC9C[i];
            while (box->kind_0 != -1)
            {
                *(sint32 *)&box->state_8 = 0;
                box++;
            }
        }
    }
}

void func_80114504(STAGE_MATRIX_OBJ *wp)
{
    ST00_BOX *box;

    box          = D_8011CC9C[STAGE_GAME.value_51];
    wp->pos_38.x = STAGE_PL.position.x >> 9;
    wp->pos_38.y = STAGE_PL.position.z >> 9;
    while (box->kind_0 != -1)
    {
        D_8011CB24[box->kind_0](wp, box++);
    }
}

void func_801145D4(STAGE_50 *wp)
{
    func_80031A4C(wp);
}

void func_801145F4(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x610))
    {
        switch (box->state_8)
        {
            case 0:
            case 1:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    Cd_xa_seek_id(0);
                }
                break;
        }
    }
}

void func_8011466C(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x610))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Cd_xa_seek_id(5);
                    Sce_flag_on(0x610);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80114774(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x612))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Cd_xa_seek_id(6);
                    Sce_flag_on(0x612);
                }
                break;
        }
    }
}

void func_80114838(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x613))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x613);
                }
                break;
        }
    }
}

void func_801148F4(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    STAGE_PL_VIEW *pl;

    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x614))
    {
        pl = &STAGE_PL;
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    if (((STAGE_PL.rotation.y - 0x200) & 0xFFF) < 0x400)
                    {
                        MojiTaskExec2(0, box->value_1);
                    }
                    else
                    {
                        MojiTaskExec2(0, box->value_1 + 1);
                    }
                    pl->flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x614);
                    pl->flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80114A34(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x615))
    {
        switch (box->state_8)
        {
            case 0:
            case 1:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    Cd_xa_seek_id(0xA);
                }
                break;
        }
    }
}

void func_80114AAC(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    STAGE_ACTOR *obj;
    sint32 i;
    uint32 dx;
    uint32 dz;

    if (!Sce_flag_test(0x60A))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box) && Sce_flag_test(0x607))
                {
                    box->state_8 = 1;
                    box->timer_C = 0;
                    Sce_flag_on(0x615);
                    if (!Sce_flag_test(0x622))
                    {
                        MojiTaskExec2(0, box->value_1);
                    }
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000) || Sce_flag_test(0x622))
                {
                    for (i = 0, obj = D_8009F108; i < 16; obj++, i++)
                    {
                        if (obj->flags_0 & 1)
                        {
                            dx = (obj->position.x >> 9) - box->x_2;
                            dz = (obj->position.z >> 9) - box->y_3;
                            if (dx < box->w_4 && dz < box->h_6)
                            {
                                break;
                            }
                        }
                    }
                    if (i == 16)
                    {
                        box->state_8 = 2;
                        if (!Sce_flag_test(0x622))
                        {
                            MojiTaskExec2(0, box->value_1 + 1);
                        }
                        Sce_flag_on(0x61F);
                    }
                }
                break;
            case 2:
                if (!(Moji_flag & 0x08000000) || Sce_flag_test(0x622))
                {
                    box->state_8 = 3;
                }
                break;
        }
    }
}

void func_80114C88(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x616))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Cd_xa_seek_id(14);
                    Sce_flag_on(0x616);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80114D90(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x617))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Cd_xa_seek_id(7);
                    Sce_flag_on(0x617);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80114E98(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x618))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box) && STAGE_PL.position.y == -0xC1)
                {
                    if (box->timer_C >= 0x5A)
                    {
                        box->state_8 = 1;
                        MojiTaskExec2(0, box->value_1);
                        STAGE_PL.flags_bd |= 0x40;
                        Obj_work_flag_change(0x27E, 1);
                        wp->flags_0 |= 1;
                    }
                    else
                    {
                        box->timer_C++;
                    }
                }
                else
                {
                    box->timer_C = 0;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Cd_xa_seek_id(0x15);
                    Sce_flag_on(0x618);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80114FE0(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x619))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    Sce_flag_on(0x618);
                    Sce_flag_on(0x60B);
                    STAGE_PL.flags_bd |= 0x40;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x619);
                    STAGE_PL.flags_bd &= ~0x40;
                }
                break;
        }
    }
}

void func_801150CC(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    sint32 y;

    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x61A))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x256, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                y = STAGE_PL.position.y;
                if (y == func_80048E6C_int(&Player_work))
                {
                    box->state_8 = 2;
                    MojiTaskExec2(0, box->value_1);
                }
                break;
            case 2:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x61A);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x256, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80115210(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x61B) && (!Sce_flag_test(0x608) || !Sce_flag_test(0x609)))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x61B);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80115330(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    STAGE_PL_VIEW *pl;

    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x61C))
    {
        pl = &STAGE_PL;
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box) && (!Sce_flag_test(0x608) || !Sce_flag_test(0x609)))
                {
                    box->state_8 = 1;
                    if (Sce_flag_test(0x61B))
                    {
                        MojiTaskExec2(0, box->value_1);
                    }
                    else
                    {
                        MojiTaskExec2(0, box->value_1 + 1);
                    }
                    pl->flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x61C);
                    pl->flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80115480(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x61D))
    {
        switch (box->state_8)
        {
            case 0:
                if (Sce_flag_test(0x60E))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                    Sce_flag_off(0x60E);
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x61D);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_801155A4(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x622) && !Sce_flag_test(0x61E))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box))
                {
                    box->state_8 = 1;
                    MojiTaskExec2(0, box->value_1);
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x27E, 1);
                    wp->flags_0 |= 1;
                }
                break;
            case 1:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x61E);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x27E, 2);
                    wp->flags_0 |= 1;
                    Sce_flag_on(0x622);
                }
                break;
        }
    }
}

void func_801156C8(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if (!Sce_flag_test(0x621))
    {
        switch (box->state_8)
        {
            case 0:
                if (func_801159F8(wp, box) && Sce_flag_test(0x620))
                {
                    box->state_8 = 1;
                    STAGE_PL.flags_bd |= 0x40;
                    Obj_work_flag_change(0x256, 1);
                    wp->flags_0 |= 1;
                    box->timer_C = 0x3C;
                }
                Sce_flag_off(0x620);
                break;
            case 1:
                if (--box->timer_C < 0)
                {
                    box->state_8 = 2;
                    Obj_work_flag_change(0x20, 1);
                    MojiTaskExec2(0, box->value_1);
                }
                break;
            case 2:
                if (!(Moji_flag & 0x08000000))
                {
                    Sce_flag_on(0x621);
                    STAGE_PL.flags_bd &= ~0x40;
                    Obj_work_flag_change(0x276, 2);
                    wp->flags_0 |= 1;
                }
                break;
        }
    }
}

void func_80115848(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    STAGE_PL_VIEW *pl;
    sint8 id;

    if (!Sce_flag_test(0x608))
    {
        pl = &STAGE_PL;
        switch (box->state_8)
        {
            case 0:
                box->state_8 = 1;
                pl->flags_bd |= 0x40;
                // fall through
            case 1:
                if (D_8011CCE0 > 60)
                {
                    if (func_801159F8(wp, box))
                    {
                        box->state_8 = 2;
                        Fade_start(10);
                    }
                }
                else
                {
                    D_8011CCE0++;
                }
                break;
            case 2:
                if (D_80098A72 == 0)
                {
                    box->state_8 = 3;
                    MojiTaskExec2(0, box->value_1);
                    Obj_work_flag_change(0x2FF, 5);
                }
                break;
            case 3:
                if (!(Moji_flag & 0x08000000))
                {
                    box->state_8 = 4;
                    id           = Moji_flag + 1;
                    Cd_read_comb(D_8011CCC0[id]);
                    Cd_read_sync();
                    pl->value_170 = id;
                    Obj_work_flag_change(0x2FF, 10);
                    Fade_start(2);
                }
                break;
            case 4:
                if (D_80098A72 == 0)
                {
                    pl->flags_bd &= ~0x40;
                    Sce_flag_on(0x608);
                }
                break;
        }
    }
}

sint32 func_801159F8(STAGE_MATRIX_OBJ *wp, ST00_BOX *box)
{
    if ((uint16)(wp->pos_38.x - box->x_2) < box->w_4 && (uint16)(wp->pos_38.y - box->y_3) < box->h_6)
    {
        return 1;
    }
    return 0;
}

void func_80115A4C(STAGE_OBJ *wp)
{
    D_8011CCE4[wp->routine_0](wp);
}

void func_80115A88(STAGE_PANEL_WORK *wp)
{
    if (Sce_flag_test(0x607))
    {
        func_80031A4C(wp);
        return;
    }
    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->value_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->color_40        = 0x808080;
    if (wp->value_3 != 0)
    {
        wp->routine_0 = 5;
    }
    else
    {
        wp->routine_0        = 1;
        wp->matrix.m.m[1][1] = 0;
        wp->cell_44          = Map_cell_get(&wp->pos_38);
        wp->matrix.words[5]  = ST00_SLOTS[wp->cell_44].value_0;
        wp->matrix.words[6]  = Stage_hed_model_get(0x40500);
    }
    Sce_flag_off(0x607);
}

void func_80115B64(ST00_10C *wp)
{
    if (Sce_flag_test(0x607) != 0)
    {
        wp->routine_3 = 8;
        wp->routine_0++;
        Sound_call2(0x119, &wp->value_38);
        ST00_SLOTS[wp->value_44].value_0 = wp->value_30;
    }
}

void func_80115BD8(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0       = wp->routine_3 - 1;
    wp->routine_3 = temp_v0;
    if (!(temp_v0 & 0xFF))
    {
        wp->routine_0++;
        func_800398E0(0x1E);
        Sound_call2(0x118, &wp->position_fixed_prev.y);
    }
    wp->position_fixed.f.y.words.fraction = (8 - wp->routine_3) << 9;
}

void func_80115C4C(STAGE_OBJ *wp)
{
    if (Sce_flag_test(0x61F) != 0)
    {
        wp->routine_3 = 0x40;
        wp->routine_0++;
        Sce_flag_on(0x60A);
        Sound_call2(0x119, &wp->position_fixed_prev.y);
    }
}

void func_80115CA4(STAGE_PANEL_WORK *wp)
{
    if (--wp->timer_B == 0)
    {
        Sound_key_off_voice(0xF);
        func_80031A4C(wp);
        return;
    }
    if (wp->timer_B == 0x10)
    {
        ST00_SLOTS[wp->cell_44].value_0 = wp->matrix.words[5];
    }
    wp->matrix.m.m[1][1] = wp->timer_B << 6;
}

void func_80115D38(STAGE_MATRIX_OBJ *wp)
{
    uint32 limit;
    uint32 dy;
    uint32 height;

    limit = 0x78;
    if ((uint32)(STAGE_PL.position.x - wp->pos_38.x + 0x3C) <= limit && (uint32)(STAGE_PL.position.z - wp->pos_38.z + 0x3C) <= limit)
    {
        dy     = STAGE_PL.position.y - wp->pos_38.y + 0xA;
        height = 0xAA;
        if (dy <= height)
        {
            Sce_flag_on(0x607);
            Sound_call2(0x11E, &wp->pos_38);
            wp->routine_3 = 0x10;
            wp->routine_0++;
        }
    }
}

void func_80115DF4(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0       = wp->routine_3 - 1;
    wp->routine_3 = temp_v0;
    if (!(temp_v0 & 0xFF))
    {
        wp->routine_0++;
    }
    wp->position_fixed.f.y.words.fraction = wp->routine_3 << 8;
}

void func_80115E34(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_80115E48(void)
{
}

void func_80115E50(STAGE_50 *wp)
{
    func_80031A4C(wp);
}

void func_80115E70(STAGE_OBJ *wp)
{
    D_8011CD2C[wp->routine_0](wp);
}

void func_80115EAC(ST00_POOL *wp)
{
    ST00_PART_REC *rec;
    uint32 i;

    wp->flags_0 |= 6;
    if (wp->variant_3 >= 0x80)
    {
        if (Sce_flag_test(0x608) && Sce_flag_test(0x609))
        {
            func_80031A4C(wp);
            return;
        }
        i = 1;
        Model_work_init(wp, (uint8 *)&i);
        wp->color_40 = 0x02808080;
        wp->data_10  = D_8011CD20;
    }
    else
    {
        if (Sce_flag_test((wp->variant_3 & 0x1F) ? 0x609 : 0x608))
        {
            func_80031A4C(wp);
            return;
        }
        i             = 0;
        wp->routine_1 = 0;
        Model_work_init(wp, (uint8 *)&i);
        wp->color_40 = 0x808080;
        wp->data_10  = D_8011CD14;
    }
    wp->matrix_18.words[0] = 0x1000;
    wp->matrix_18.words[1] = 0;
    wp->matrix_18.words[2] = 0x1000;
    wp->matrix_18.words[3] = 0;
    wp->matrix_18.words[4] = 0x1000;
    if (wp->variant_3 < 0x80)
    {
        wp->matrix_18.m.m[0][0] = wp->matrix_18.m.m[1][1] = wp->matrix_18.m.m[2][2] = 0x200;
        wp->pos_38.y -= 0x20;
    }
    RotMatrixY((wp->variant_3 & 0x60) << 5, &wp->matrix_18.m);
    D_80122620[wp->variant_3 & 1].words[0] = 0;
    D_80122620[wp->variant_3 & 1].words[1] = 0;
    D_80122620[wp->variant_3 & 1].words[2] = 0;
    D_80122620[wp->variant_3 & 1].words[3] = 0;
    if (wp->variant_3 >= 0x80)
    {
        if (wp->variant_3 == 0x81)
        {
            for (i = 0; i < 16; i++)
            {
                D_8012256C[i] = *(ST00_UV8 *)Model_face_get((uint32)wp->model_14, i | 0x10000);
            }
            rec = wp->model_14->parts_70->recs_24;
            for (i = 0; i < 25; i++)
            {
                D_801225EC[i] = rec[i].value_2;
            }
        }
        wp->routine_0 = 5;
        wp->flags_0 |= 0x40;
        wp->value_A = 0;
        if (wp->variant_3 & 0x4F)
        {
            wp->cell_44            = Map_cell_get(&wp->pos_38);
            wp->cell_C             = ST00_SLOTS[wp->cell_44].value_0;
            wp->matrix_18.f.key_14 = Stage_hed_model_get(D_8011CD0C[wp->variant_3 & 0xF]);
        }
    }
    else
    {
        wp->routine_0 = 1;
        wp->value_A   = 0x64;
    }
    wp->count_48 = (rand() & 7) * 3;
}

void func_801161D4(ST00_ORBIT *wp)
{
    STCOM_SVECTOR pos;
    uint32 damage;

    damage = D_80122620[wp->variant_3 & 1].f.hit_0 & 0xFFFFFF;
    if (damage != 0)
    {
        wp->color_40 = 0xFFFFFF;
    }
    else if (--wp->routine_1 == 0)
    {
        wp->routine_1 = ((rand() & 8) + 1) * 2;
        wp->color_40  = 0xFFC080;
        Sound_call2(0x11C, &wp->pos_38);
    }
    else
    {
        wp->color_40 = 0x808080;
    }
    if (Player_work.target_184 == wp)
    {
        Sce_flag_on(0x60E);
        Player_work.target_184 = NULL;
        wp->value_10           = 0;
    }
    if (Sce_flag_test(0x61D))
    {
        Player_work.target_184 = NULL;
        wp->value_10           = 0;
    }
    if ((sint32)(wp->routine_2 - damage) < 0 || (D_80122620[wp->variant_3 & 1].f.hit_0 & 0x20000000))
    {
        pos = D_80122620[wp->variant_3 & 1].f.from_8;
        if (pos.pad == 0)
        {
            wp->matrix_18.f.angle_30 = -ratan2(pos.x, -pos.z);
        }
        wp->routine_3 = 0x10;
        wp->color_40  = 0x808080;
        wp->routine_0++;
        Sound_call2(0xA2, &wp->pos_38);
        if (wp->variant_3 & 0x1F)
        {
            Sce_flag_on(0x609);
        }
        else
        {
            Sce_flag_on(0x608);
        }
    }
    else
    {
        wp->routine_2                         = wp->routine_2 - damage;
        D_80122620[wp->variant_3 & 1].f.hit_0 = 0;
        if (damage != 0)
        {
            Sound_call2(0xA0, &wp->pos_38);
        }
    }
    pos = wp->pos_38;
    pos.y -= 0x28;
    func_800341BC(&pos, 0x50, 0, 0x8000, wp->index_1, &D_80122620[wp->variant_3 & 1].f.hit_0, 0x4000000, 0x800000, 0);
    func_80051B68(wp, 5, -1, 0);
}

void func_801164A8(ST00_ORBIT *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX unused;
    STCOM_EFFECT *ep;
    sint32 cos;
    sint32 t;
    sint32 i;
    uint8 timer;

    wp->matrix_18.f.rot[0] = 0x1000;
    wp->matrix_18.f.rot[1] = 0;
    wp->matrix_18.f.rot[2] = 0x1000;
    wp->matrix_18.f.rot[3] = 0;
    wp->matrix_18.f.rot[4] = 0x1000;
    RotMatrixY((wp->variant_3 & 0x60) << 5, &wp->matrix_18.m);
    RotMatrixY(-wp->matrix_18.f.angle_30, &wp->matrix_18.m);
    t   = 0x10 - wp->routine_3;
    cos = 0x1000 - (t * 16) * t;
    RotMatrixX(ratan2(SquareRoot0(0x1000000 - cos * cos), cos), &wp->matrix_18.m);
    RotMatrixY(wp->matrix_18.f.angle_30, &wp->matrix_18.m);
    scale.x = scale.y = scale.z = 0x200;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    timer         = wp->routine_3 - 1;
    wp->routine_3 = timer;
    if (!(timer & 0xFF))
    {
        wp->routine_3 = 8;
        wp->routine_0++;
        for (i = 0; i < 3; i++)
        {
            ep = func_80031618();
            if (ep != NULL)
            {
                ep->flags_0         = 1;
                ep->kind_2          = 0x83;
                ep->variant_3       = 2;
                ep->sprite.pos_8[0] = wp->pos_38.x - (((rsin(wp->matrix_18.f.angle_30) << 6) * i) >> 12);
                ep->sprite.pos_8[1] = wp->pos_38.y - 0x10;
                ep->sprite.pos_8[2] = wp->pos_38.z - (((rcos(wp->matrix_18.f.angle_30) << 6) * i) >> 12);
            }
        }
    }
}

void func_80116658(STAGE_OBJ *wp)
{
    uint8 temp_v0;

    temp_v0       = wp->routine_3 - 1;
    wp->routine_3 = temp_v0;
    if (!(temp_v0 & 0xFF))
    {
        wp->routine_0++;
    }
}

void func_8011668C(ST00_ORBIT *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0           = 5;
        ep->kind_2            = 0x80;
        ep->variant_3         = 0x82;
        ep->sprite.position.x = wp->pos_38.x - ((rsin(wp->matrix_18.f.angle_30) * 100) >> 12);
        ep->sprite.position.y = wp->pos_38.y;
        ep->sprite.position.z = wp->pos_38.z - ((rcos(wp->matrix_18.f.angle_30) * 100) >> 12);
    }
    wp->routine_0 = 9;
}

void func_80116750(ST00_POOL *wp)
{
    ST00_UV8 uv;
    STCOM_FIXED_VECTOR unused;
    ST00_PART_REC *rec;
    uint32 anim;
    uint32 i;
    uint32 shade;

    if (wp->variant_3 == 0xA0)
    {
        wp->value_A += 2;
        if ((uint8)wp->value_A >= 0x40)
        {
            wp->value_A = 0;
        }
        anim = (uint8)wp->value_A;
        for (i = 0; i < 16; i++)
        {
            uv      = D_8012256C[i];
            uv.b[0] = D_8012256C[i].b[0] + anim;
            uv.b[2] = D_8012256C[i].b[2] + anim;
            uv.b[4] = D_8012256C[i].b[4] + anim;
            uv.b[6] = D_8012256C[i].b[6] + anim;
            Model_face_uv_set(wp->model_14, i | 0x10000, &uv);
        }
        rec = wp->model_14->parts_70->recs_24;
        for (i = 0; i < 25; i++)
        {
            rec->value_2 = D_801225EC[i] - ((rand() & 7) - 4);
            rec++;
        }
    }
    wp->count_48++;
    if (Sce_flag_test(0x608) || Sce_flag_test(0x609))
    {
        if (Sce_flag_test(0x608) && Sce_flag_test(0x609))
        {
            if (wp->variant_3 & 0x4F)
            {
                ST00_SLOTS[wp->cell_44].value_0 = wp->matrix_18.f.key_14;
            }
            wp->routine_3 = 8;
            wp->routine_0++;
        }
        shade        = (rand() & 0x1F) + 0x10;
        wp->color_40 = 0x2000000 | (shade << 16) | (shade << 8) | shade;
        if (wp->count_48 >= 0x1F && (wp->variant_3 & 0x40))
        {
            Sound_call2(0x11B, &wp->pos_38);
            wp->count_48 = 0;
        }
    }
    else
    {
        shade        = (rand() & 0x3F) + 0x40;
        wp->color_40 = 0x2000000 | (shade << 16) | (shade << 8) | shade;
        if (wp->count_48 >= 0x19 && (wp->variant_3 & 0x40))
        {
            Sound_call2(0x11A, &wp->pos_38);
            wp->count_48 = 0;
        }
    }
}

// Fades a gray level out.
void func_80116A08(STAGE_FX *wp)
{
    wp->value_40 = 0x2000000 | (wp->routine_3 * 8 << 16) | (wp->routine_3 * 8 << 8) | (wp->routine_3 * 8);
    if (--wp->routine_3 == 0)
    {
        wp->routine_0 = 9;
    }
}

void func_80116A54(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_80116A68(STAGE_OBJ *wp)
{
    wp->routine_0++;
}

void func_80116A7C(STAGE_50 *wp)
{
    func_80031A4C(wp);
}

void func_80116A9C(STAGE_SPARK *wp)
{
    STAGE_OBJ *owner;

    owner = wp->owner_2C;
    if (--wp->timer_D == 0 || owner->routine_0 == 2)
    {
        wp->timer_D = 0;
        wp->routine_0++;
    }
    wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
    wp->w_24 += wp->type_F;
    wp->y_1E += wp->rise_28;
}

void func_80116B28(STAGE_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_80116A9C(wp);
}

void func_80116B5C(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80116B7C(STAGE_OBJ *wp)
{
    D_8011CD54[wp->routine_0](wp);
}

void func_80116BB8(ST00_SPARK *wp)
{
    ST00_SPARK *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->variant_3 = 1;
            ep->flags_6   = wp->flags_6;
            ep->value_C   = 0;
            ep->timer_D   = (rand() & 7) * 2 + 0x40;
            ep->x_1C      = wp->x_1C + (rand() & 0xF);
            ep->y_1E      = wp->y_1E;
            ep->z_20      = wp->z_20 + (rand() & 0xF);
            ep->mode_14   = 0x3D48004E;
            ep->u_22      = ((rand() & 3) << 5) + 0x20;
            ep->v_23      = 0;
            ep->w_24      = wp->width_E;
            ep->type_F    = wp->type_F;
            ep->rise_28   = wp->rise_28;
            ep->owner_2C  = wp;
            for (i = 0; i < wp->count_26; i++)
            {
                func_80116B7C(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_80116D00(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 1)
    {
        func_80116B7C(wp);
        return;
    }
    if (wp->routine_0 != 2)
    {
        func_80116BB8(wp);
        return;
    }
    func_80031988((STCOM_EFFECT *)wp);
}

ST00_SPARK *func_80116D60(STCOM_SVECTOR *pos, sint32 width, sint32 type, sint32 count, sint32 rise, uint8 hide)
{
    ST00_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0;
        ep->variant_3 = 0;
        ep->value_C   = 0;
        ep->width_E   = width;
        ep->type_F    = type;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->count_26  = count;
        if (hide)
        {
            ep->flags_6 |= 0x20;
        }
        else
        {
            ep->flags_6 &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < (sint16)count; i++)
        {
            func_80116BB8(ep);
        }
    }
    return ep;
}

void func_80116E68(ST00_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        D_8011CD68[wp->variant_3](wp);
    }
    else
    {
        D_8011CD60[wp->routine_0](wp);
    }
}

void func_80116ED4(STCOM_EFFECT *wp)
{
    STCOM_EFFECT *ep;

    if (!(wp->timer_B & 3))
    {
        ep                  = func_80031618();
        ep->flags_0         = 3;
        ep->kind_2          = 2;
        ep->value_C         = 2;
        ep->variant_3       = 0;
        ep->value_D         = 1;
        ep->timer_E         = wp->timer_E;
        ep->sprite.pos_8[0] = wp->sprite.pos_8[0];
        ep->sprite.pos_8[1] = wp->sprite.pos_8[1];
        ep->sprite.pos_8[2] = wp->sprite.pos_8[2];
        ep->sprite.pos_8[0] += rand() % 20 - 10;
        ep->sprite.pos_8[1] += (rand() >> 8) % 38 - 19;
        ep->sprite.pos_8[2] += (rand() >> 4) % 20 - 10;
        if (ep->timer_E == 7)
        {
            ep->sprite.mode_0 = 0x3D48000E;
        }
        else
        {
            ep->sprite.mode_0 = 0x3D48002E;
        }
        ep->sprite.color_4.word = 0x2E000000;
        ep->sprite.value_E      = 0xA0;
        ep->sprite.value_F      = 0x60;
        ep->sprite.value_10     = 3;
        ep->timer_B             = 0x18;
    }
    wp->timer_B++;
}

void func_80117094(STAGE_FX *wp)
{
    STAGE_FX *ep;

    if ((wp->routine_3 & 7) == 0)
    {
        ep            = (STAGE_FX *)func_80031618();
        ep->flags_0   = 3;
        ep->kind_2    = 2;
        ep->variant_3 = 1;
        ep->value_C   = 2;
        ep->timer_D   = 1;
        ep->frame_E   = wp->frame_E;
        ep->x_1C      = wp->x_1C;
        ep->z_20      = wp->z_20;
        ep->y_1E      = wp->y_1E;
        if (ep->frame_E == 7)
        {
            ep->mode_14 = 0x3C880006;
        }
        else
        {
            ep->mode_14 = 0x3C880026;
        }
        ep->color_18   = (D_8011CD74[ep->frame_E] << 7) | 0x2E000000;
        ep->u_22       = 0x80;
        ep->w_24       = 1;
        ep->routine_3  = 0x20;
        ep->u_28.count = 0x100;
        ep->v_23       = 0;
        ep->x_2C.value = ep->w_24 << 8;
    }
    if (++wp->routine_3 > 0x10)
    {
        func_80031988(wp);
    }
}

void func_801171C4(void)
{
}

void func_801171CC(STAGE_FX *wp)
{
    switch (wp->variant_3)
    {
        case 0:
            if (wp->routine_3 >= 9)
            {
                wp->color_18 += D_8011CD74[wp->frame_E] << 3;
            }
            else
            {
                wp->color_18 -= D_8011CD74[wp->frame_E] << 4;
            }
            break;
        case 1:
            wp->color_18 -= D_8011CD74[wp->frame_E] << 2;
            wp->x_2C.value += wp->u_28.count;
            wp->u_28.count -= 8;
            wp->w_24 = (uint32)wp->x_2C.value >> 8;
            break;
        case 2:
        default:
            break;
    }
    if (--wp->routine_3 == 0)
    {
        wp->routine_0++;
    }
}

void func_801172DC(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_801172FC(ST00_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        D_8011CD9C[wp->variant_3](wp);
    }
    else
    {
        D_8011CD94[wp->routine_0](wp);
    }
}

void func_80117368(STAGE_FX *wp)
{
    STAGE_FX *fx;

    if ((wp->routine_1 & 3) == 0)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx == NULL)
        {
            return;
        }
        fx->flags_0   = 3;
        fx->kind_2    = 3;
        fx->value_C   = 3;
        fx->variant_3 = 0;
        fx->timer_D   = 1;
        fx->frame_E   = 0;
        fx->x_1C      = wp->x_1C + (rand() & 7) - 3;
        if (wp->type_F == 0)
        {
            fx->y_1E = wp->y_1E + 0x30;
        }
        else
        {
            fx->y_1E = wp->y_1E + 0x18;
        }
        fx->z_20     = wp->z_20 + (rand() & 7) - 3;
        fx->mode_14  = 0x3D080026;
        fx->color_18 = 0x2C804040;
        fx->u_22     = D_8011CDA8[0];
        fx->v_23     = 0;
        if (wp->type_F == 0)
        {
            fx->w_24 = 0x30;
        }
        else
        {
            fx->w_24 = 0x18;
        }
        fx->routine_0 = 0;
        fx->routine_2 = 1;
    }
    if (wp->routine_1 >= 4)
    {
        wp->routine_0++;
        wp->timer_D++;
    }
    wp->routine_1++;
}

void func_801174BC(void)
{
}

void func_801174C4(void)
{
}

void func_801174CC(STAGE_FX *wp)
{
    wp->y_1E += 6;
    wp->u_22 = D_8011CDA8[wp->routine_2];
    wp->routine_2++;
    if (D_8011CDA8[wp->routine_2] == -1)
    {
        wp->routine_0++;
    }
}

void func_80117538(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80117558(ST00_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        D_8011CDC0[wp->variant_3](wp);
    }
    else
    {
        D_8011CDC4[wp->routine_0](wp);
    }
}

void func_801175C4(STAGE_OBJ *wp)
{
    if (!(wp->routine_1 & 3))
    {
        func_80117740(wp);
    }
    if ((uint8)wp->routine_1 >= 4)
    {
        wp->routine_0++;
        wp->u_C.b.byte_D++;
    }
    wp->routine_1++;
}

void func_80117640(STAGE_FX *wp)
{
    wp->y_1E += (sint8)D_8011CDCD[wp->routine_2 * 4];
    wp->z_20 += wp->frame_E;
    wp->u_22 = D_8011CDCC[wp->routine_2 * 4];
    wp->w_24 += (sint8)D_8011CDCF[wp->routine_2 * 4];
    if (--wp->routine_1 == 0)
    {
        wp->routine_1 = D_8011CDCE[++wp->routine_2 * 4];
        if (wp->routine_1 == 0)
        {
            wp->routine_0++;
        }
    }
}

void func_80117720(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80117740(STAGE_FX *wp)
{
    STAGE_FX *ep;
    sint16 i;

    for (i = 0; i < 24; i++)
    {
        ep = (STAGE_FX *)func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 3;
            ep->kind_2    = 4;
            ep->value_C   = 4;
            ep->timer_D   = 1;
            ep->variant_3 = 0;
            if (i < 12)
            {
                ep->z_20    = wp->z_20 + (sint16)((rand() & 0xF) - 0x40) - 7;
                ep->frame_E = -(rand() & 0xF) + 7;
            }
            else
            {
                ep->z_20    = wp->z_20 + (sint16)((rand() & 0xF) + 0x40) - 7;
                ep->frame_E = (rand() & 7) + 8;
            }
            ep->x_1C      = wp->x_1C + (sint16)(i % 12 * 64 + 0x40) + (sint16)((rand() & 0x3F) - 0x180) - 0x1F;
            ep->y_1E      = wp->y_1E;
            ep->mode_14   = 0x3D48002E;
            ep->color_18  = 0x2E403028;
            ep->u_22      = D_8011CDCC[0];
            ep->v_23      = 0;
            ep->w_24      = (rand() & 7) + 0x1D;
            ep->routine_0 = 0;
            ep->routine_1 = D_8011CDCC[2] + (rand() & 3);
            ep->routine_2 = 0;
        }
    }
}
