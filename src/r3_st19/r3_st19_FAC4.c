#include "common.h"
#include "st19.h"

#ifdef __wasm32__
void func_80111D50(void);
#endif

void func_8010FAC4(STAGE_OBJ *wp)
{
    D_80118480[wp->variant_3](wp);
}

void func_8010FB00(STAGE_OBJ *wp)
{
    D_80118488[wp->routine_0](wp);
}

void func_8010FB3C(ST19_TRAIL *wp)
{
    uint32 i;
    uint8 *trail;

    wp->routine_0 = 1;
    wp->timer_D   = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->type_F    = 0;
    wp->frame_E   = wp->value_C * 4;
    i             = 0;
    wp->x_1C      = D_80118388[wp->value_C].x;
    trail         = wp->trail_28[0];
    wp->y_1E      = D_80118388[wp->value_C].y;
    wp->z_20      = D_80118388[wp->value_C].z;
    wp->w_24      = 8;
    do
    {
        *trail = i * 8;
        i++;
        trail += 2;
    } while (i < 16);
}

void func_8010FBF4(ST19_TRAIL *wp)
{
    if (STAGE_FRAME & 1)
    {
        wp->frame_E++;
    }
    if (D_8011835C[wp->value_C][0] <= STAGE_SCENE_BYTE(8))
    {
        wp->routine_0 = 2;
    }
}

void func_8010FC58(ST19_TRAIL *wp)
{
    if (STAGE_FRAME & 1)
    {
        wp->frame_E++;
    }
    func_8010FCD4(wp);
    if (STAGE_SCENE_BYTE(8) == D_8011835C[wp->value_C][1])
    {
        func_80031988(wp);
    }
}

void func_8010FCD4(ST19_TRAIL *wp)
{
    STCOM23_PACKET *p;
    STCOM_SVECTOR_W pos;
    uint8(*trail)[2];
    uint8 i;
    uint8 shade;
    sint32 angle;
    uint16 radius;
    uint16 size;
    uint8 u;
    uint8 v;

    trail = wp->trail_28;
    i     = 0;
    u     = 0x40;
    v     = 0;
    do
    {
        if (trail[i][0] < 0x80)
        {
            trail[i][0]++;
        }
        else
        {
            trail[i][0] = 0;
        }
        shade   = 0x40 - (trail[i][0] >> 3) * 4;
        radius  = (rsin((wp->frame_E & 0x7F) << 5) * 60 >> 12) + 0x50;
        angle   = trail[i][0] * 8;
        size    = (trail[i][0] >> 1) + 0x14;
        pos.v.x = wp->x_1C + (rsin(angle) * radius >> 12);
        pos.v.z = wp->z_20;
        pos.v.y = wp->y_1E - trail[i][0] * 4;
        i++;
        p          = Billboard_get();
        p->code_4  = 0x2E000000 | (shade << 16) | (shade << 8) | shade;
        p->uv_C    = 0x3D480000 | (v << 8) | u;
        p->uv_14   = 0x2E0000 | (v << 8) | (u + 0x1F);
        p->uv_1C   = ((v + 0x1F) << 8) | u;
        p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
        p->xy_8    = pos.words[0];
        p->size_18 = size;
        p->pad_20  = 0;
        p->z_10    = *(uint32 *)&pos.v.z;
    } while (i < 16);
}

void func_8010FE88(STAGE_OBJ *wp)
{
    D_80118494[wp->routine_0](wp);
}

void func_8010FEC4(ST19_PROP *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR rot;
    ST19_PROP_REC *rec;
    sint32 s;

    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->value_D   = 0;
    wp->value_E   = 0;
    wp->value_F   = 0;
    rec           = &D_801183C0[wp->index_C];
    rot.x         = rec->rot_x;
    rot.y         = rec->rot_y;
    rot.z         = rec->rot_z;
    RotMatrixYXZ(&rot, &wp->matrix_18.m);
    s       = rec->scale_6;
    scale.y = s;
    scale.z = s;
    scale.x = s;
    ScaleMatrix(&wp->matrix_18.m, &scale);
    wp->pos_38.x = rec->x;
    wp->pos_38.y = rec->y;
    wp->pos_38.z = rec->z;
    wp->color_40 = 0x808080;
    wp->kind_2   = 0x16;
    Model_work_init(wp, rec->variant_E);
    wp->kind_2 = 0x1B;
}

// Starts the effect once the scene reaches its first line.
void func_8010FFB0(STAGE_FX *wp)
{
    if (D_80118370[wp->value_C][0] <= STAGE_SCENE_BYTE(8))
    {
        wp->routine_0 = 2;
        wp->flags_0 |= 6;
    }
}

// Frees the effect at its last line.
void func_8010FFF8(STAGE_FX *wp)
{
    if (STAGE_SCENE_BYTE(8) == D_80118370[wp->value_C][1])
    {
        func_80031988(wp);
    }
}

void func_80110040(STAGE_FX *wp)
{
    if (wp->timer_D == 0)
    {
        D_801184A0[wp->routine_0](wp);
    }
    else
    {
        D_801184A8[wp->routine_0](wp);
    }
}

void func_801100AC(ST19_FX *wp)
{
    ST19_FX *ep;
    sint8 index;

    if (wp->type_F == 1)
    {
        if (!(wp->routine_1 & 7))
        {
            ep = (ST19_FX *)func_80031618();
            if (ep != NULL)
            {
                index         = wp->value_C + wp->variant_3 * 2;
                ep->flags_0   = 3;
                ep->kind_2    = wp->kind_2;
                ep->variant_3 = wp->variant_3;
                ep->value_C   = wp->value_C;
                ep->timer_D   = 1;
                ep->frame_E   = 0x40;
                ep->type_F    = wp->type_F;
                ep->x_1C      = D_801184B0[index].x - (rand() & 0x7F);
                ep->z_20      = D_801184B0[index].z - (rand() & 0x7F);
                ep->y_1E      = D_801184B0[index].y;
                ep->mode_14   = 0x3D48000E;
                ep->color_18  = 0x2E808080;
                ep->u_22      = 0x40;
                ep->v_23      = 0;
                ep->w_24      = D_801184B0[index].w_8;
            }
        }
        wp->routine_1++;
    }
}

void func_80110200(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_80110220(ST19_FX *wp)
{
    sint8 index;

    if (wp->frame_E > 0)
    {
        index = wp->value_C + wp->variant_3 * 2;
        wp->x_1C += D_801184B0[index].dx_9 + (D_801184B0[index].mask_x_D & rand());
        wp->y_1E -= D_801184B0[index].dy_A + (D_801184B0[index].mask_y_E & rand());
        wp->z_20 += D_801184B0[index].dz_B + (D_801184B0[index].mask_z_F & rand());
        wp->w_24 += D_801184B0[index].dw_C;
        wp->color_18 += 0xFFFEFEFF;
        wp->frame_E--;
    }
    else
    {
        func_80031988(wp);
    }
}

void func_80110380(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_801103A0(STAGE_ROOM *wp)
{
    D_80118510[wp->routine_4](wp);
}

void func_801103DC(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x7E, 0x80);
            func_8001B314();
            func_8001E6C0(0, 0, 0);
            wp->reserved09[1] = 0x80;
            wp->timer_C       = 0;
            wp->reserved09[2] = 0;
            D_800BC7F0_A[0]   = D_8011856C;
            wp->tbl_A4        = D_80118D98;
            func_8001EAE8(&D_80118544[0]);
            func_8001EAE8(&D_80118544[1]);
            wp->routine_5++;
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->value_448   = 0x30;
                pl->value_76    = 0;
                pl->value_74    = 0;
                pl->pos_438.x   = 0;
                pl->pos_438.y   = 0;
                pl->pos_438.z   = 0;
                pl->fixed_428.x = 0;
                pl->fixed_428.y = 0;
                pl->fixed_428.z = 0;
                pl->value_440   = 0;
                pl->value_442   = 0;
                pl->value_444   = 0;
                pl->flags_bd |= 0x10;
                pl->flags_0 &= ~2;
                func_80111C08(0);
                wp->routine_5++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                Cd_xa_play_id(0x20000019);
                wp->routine_5++;
            }
            break;
        case 3:
            if (func_8001D878() != 0)
            {
                Sce_event_timer_clear();
                D_800BC7F0    = D_801185BC;
                wp->tbl_A4    = D_80118DA8;
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->reserved09[1] &= 3;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
    func_8001EC0C();
    Sce_event_update();
}

void func_80110630(STAGE_ROOM *wp)
{
    if (wp->routine_8 == 0xFF)
    {
        func_80017C30(10);
        wp->routine_4++;
        wp->routine_5 = 0;
    }
    else
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84() != 0 || wp->reserved09[1] == 1)
        {
            func_80017C30(10);
            wp->routine_4++;
            wp->routine_5 = 0;
        }
    }
    func_8001EC0C();
    Sce_event_update();
}

void func_801106C4(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Cd_subcmd(0, 1, 0);
                Obj_work_flag_change(0x7E, 0x80);
                wp->routine_5++;
            }
            break;
        case 1:
            func_80042314(pl);
            pl->value_76 = 0;
            pl->flags_0 |= 3;
            wp->routine_5++;
            break;
        case 2:
            if (wp->reserved09[2] == 0)
            {
                Cd_read_comb(0xB5);
            }
            wp->routine_5++;
            break;
        case 3:
            if (wp->reserved09[2] == 0 && Cd_read_sync2() != 0)
            {
                break;
            }
            wp->routine_5++;
            break;
        case 4:
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            D_800C356C = -1;
            D_800C356E = 0x19;
            D_800C3560 = -0xCE4;
            D_800C3562 = -1;
            D_800C3564 = -0x99C;
            D_800C356A = 0xC00;
            D_800C356F = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 0xFF;
            wp->routine_5++;
            break;
        case 5:
            func_8003786C(0x1B);
            func_8003786C(0x1C);
            func_8003786C(0x1D);
            func_8003786C(0x25);
            func_8003786C(0x26);
            func_8003786C(0x27);
            func_80111D50();
            Sound_call(0x26, 0, 0);
            func_80017C30(2);
            wp->flags_0 = 0;
            break;
    }
    if (wp->reserved09[1] != 0)
    {
        func_8001EC0C();
        Sce_event_update();
    }
}

void func_801108C8(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    if (wp->frame_10 == 0xEB)
    {
        STAGE_PL.value_448   = 0x80;
        STAGE_PL.pos_438.x   = -450;
        STAGE_PL.pos_438.z   = 100;
        STAGE_PL.fixed_428.x = -450 << 16;
        STAGE_PL.pos_438.y   = 0;
        STAGE_PL.fixed_428.y = 0;
        STAGE_PL.fixed_428.z = 100 << 16;
        STAGE_PL.value_440   = 0;
        STAGE_PL.value_442   = 0xC00;
        STAGE_PL.value_444   = 0;
        pl->flags_0 |= 2;
    }
    STAGE_PL.pos_438.x += 3;
    STAGE_PL.fixed_428.x = STAGE_PL.pos_438.x << 16;
    if (wp->frame_10 >= 0xEC && !(wp->frame_10 & 0xF))
    {
        Sound_call2(0x90, &pl->pos_438);
    }
    func_80111C6C(pl);
}

void func_801109C0(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.pos_438.x   = -850;
            STAGE_PL.fixed_428.x = -850 << 16;
            func_80111C08(1);
            break;
        case 0x14:
        case 0x46:
            func_80111C08(2);
            break;
        case 0x3C:
            func_80111C08(3);
            break;
        case 0x5A:
            func_80111C08(4);
            break;
    }
    pl->pos_438.x += 4;
    pl->fixed_428.x = pl->pos_438.x << 16;
    if (!(wp->frame_10 & 0xF))
    {
        Sound_call2(0x90, &STAGE_PL.pos_438);
    }
    func_80111C6C(pl);
}

void func_80110AB8(void)
{
}

void func_80110AC0(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.pos_438.x   = -200;
            STAGE_PL.fixed_428.x = -200 << 16;
            STAGE_PL.value_448   = 0x81;
            func_80111C08(5);
            break;
        case 2:
        case 8:
            Sound_call2(0x90, &STAGE_PL.pos_438);
            break;
        case 10:
            func_80111C08(6);
            break;
        case 0x28:
            func_80111C08(7);
            break;
        case 0x3A:
            func_80111C08(5);
            break;
        case 0x6E:
            STAGE_PL.value_448 = 0x82;
            func_80111C08(8);
            break;
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110BD0(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            wp->child_2C->routine_1 = 1;
            wp->child_2C->routine_2 = 0;
            wp->child_30->routine_1 = 1;
            wp->child_30->routine_2 = 0;
            func_80111C08(9);
            break;
        case 0x3A:
            func_8001EAE8(D_8011851C);
            wp->child_24->routine_1 = 0;
            wp->child_24->routine_2 = 0;
            break;
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110C88(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.y      = -5;
        STAGE_PL.fixed_428.y    = 0xFFFB0000;
        wp->child_24->routine_1 = 2;
        wp->child_24->routine_2 = 0;
    }
}

void func_80110CCC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.value_448 = 0x83;
        func_80111C08(10);
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110D14(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            wp->child_24->routine_1 = 3;
            wp->child_24->routine_2 = 0;
            func_80111C08(10);
            break;
        case 10:
            STAGE_PL.value_448 = 0x84;
            func_80111C08(0xB);
            break;
        case 0x14:
            func_80111C08(0xC);
            break;
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110DAC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x      = -300;
        STAGE_PL.fixed_428.x    = -300 << 16;
        wp->child_24->routine_1 = 4;
        wp->child_24->routine_2 = 0;
    }
}

void func_80110DF0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -180;
        STAGE_PL.fixed_428.x = -180 << 16;
        func_80111C08(14);
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110E44(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 5:
            STAGE_PL.pos_438.y   = -7;
            STAGE_PL.fixed_428.y = -7 << 16;
            STAGE_PL.value_448   = 0x85;
            func_80111C08(0xF);
            wp->child_24->routine_1 = 5;
            wp->child_24->routine_2 = 0;
            break;
        case 10:
            func_80111C08(0x10);
            break;
        case 0x5C:
            func_80111C08(0x11);
            break;
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110F00(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x      = -300;
        STAGE_PL.fixed_428.x    = -300 << 16;
        wp->child_24->routine_1 = 6;
        wp->child_24->routine_2 = 0;
    }
}

void func_80110F44(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -180;
        STAGE_PL.fixed_428.x = -180 << 16;
        STAGE_PL.value_448   = 0x86;
        func_80111C08(0x11);
        wp->child_24->routine_1 = 7;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x14)
    {
        func_80111C08(0x12);
    }
    func_80111C6C(&STAGE_PL);
}

void func_80110FE0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x      = -300;
        STAGE_PL.fixed_428.x    = -300 << 16;
        wp->child_24->routine_1 = 8;
        wp->child_24->routine_2 = 0;
    }
}

void func_80111024(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.z      = 300;
        STAGE_PL.fixed_428.z    = 300 << 16;
        STAGE_PL.value_448      = 0x84;
        wp->child_24->routine_1 = 9;
        wp->child_24->routine_2 = 0;
        func_8001EAE8(D_80118530);
    }
    if (wp->frame_10 == 0x262)
    {
        func_8003187C(wp->child_28);
    }
}

void func_801110B4(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        STAGE_PL.pos_438.x   = -240;
        STAGE_PL.pos_438.z   = 100;
        STAGE_PL.fixed_428.x = -240 << 16;
        STAGE_PL.fixed_428.z = 100 << 16;
        func_80111C08(0);
        wp->child_24->routine_1 = 10;
        wp->child_24->routine_2 = 0;
    }
    func_80111C6C(&STAGE_PL);
}

void func_80111144(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 0xB;
        wp->child_24->routine_2 = 0;
    }
    if (wp->frame_10 == 0x82)
    {
        wp->child_24->routine_1 = 0xC;
        wp->child_24->routine_2 = 0;
    }
}

void func_8011119C(STAGE_ROOM *wp)
{
    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.value_448 = 0x87;
            func_80111C08(0x14);
            break;
        case 0x18:
            func_80111C08(0x19);
            break;
        case 0x4A:
        case 0x64:
            func_80111C08(0x15);
            break;
    }
    func_80111C6C(&STAGE_PL);
}

void func_8011122C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_24->routine_1 = 0xD;
        wp->child_24->routine_2 = 0;
    }
}

void func_8011125C(STAGE_ROOM *wp)
{
    STAGE_FX *fx;

    switch (wp->frame_10)
    {
        case 0:
            wp->child_2C->routine_1 = 2;
            wp->child_2C->routine_2 = 0;
            wp->child_30->routine_1 = 2;
            wp->child_30->routine_2 = 0;
            break;
        case 10:
            fx = (STAGE_FX *)func_80031618();
            if (fx != NULL)
            {
                fx->flags_0 = 1;
                fx->kind_2  = 5;
                fx->value_C = 5;
                fx->frame_E = 2;
                fx->x_1C    = 0x1C2;
                fx->y_1E    = -0x26E;
                fx->timer_D = 0;
                fx->z_20    = 0x1D;
            }
            fx = (STAGE_FX *)func_80031618();
            if (fx != NULL)
            {
                fx->flags_0 = 1;
                fx->kind_2  = 5;
                fx->value_C = 5;
                fx->frame_E = 2;
                fx->x_1C    = 0x1C2;
                fx->y_1E    = -0x26E;
                fx->timer_D = 0;
                fx->z_20    = -0x20;
            }
            break;
        case 0x3C:
            wp->routine_6++;
            break;
    }
    if (wp->routine_6 != 0)
    {
        D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 16;
    }
}

void func_801113C4(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_2C->flags_0 &= ~2;
        wp->child_30->flags_0 &= ~2;
        func_80111B1C(0, 0);
    }
    D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 17;
}

void func_80111458(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->frame_10)
    {
        case 0:
            STAGE_PL.value_448 = 0x89;
            func_80111C08(0x16);
            func_80111B1C(1, 1);
            break;
        case 10:
            func_80111C08(0x17);
            break;
        case 0x32:
            STAGE_PL.value_448 = 0x88;
            break;
    }
    D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 16;
    if (wp->frame_10 >= 0x33)
    {
        pl->pos_438.z += 3;
        pl->fixed_428.z = pl->pos_438.x << 16;
    }
    func_80111C6C(pl);
}

void func_80111564(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->child_2C->flags_0 |= 2;
        wp->child_30->flags_0 |= 2;
        wp->child_2C->routine_1 = 1;
        wp->child_2C->routine_2 = 0;
        wp->child_30->routine_1 = 1;
        wp->child_30->routine_2 = 0;
    }
    if (wp->frame_10 == 0x3C)
    {
        wp->child_2C->routine_1 = 3;
        wp->child_2C->routine_2 = 0;
    }
    D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 17;
}

void func_80111634(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->frame_10)
    {
        case 0:
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            STAGE_PL.pos_438.z   = -0xD02;
            STAGE_PL.value_448   = 1;
            STAGE_PL.fixed_428.z = STAGE_PL.pos_438.x << 16;
            func_80111B1C(2, 0);
            break;
        case 0x50:
            STAGE_PL.value_448 = 0x30;
            break;
        case 0x55:
            func_80017C30(0xE);
            break;
    }
    D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 17;
    if (wp->frame_10 >= 0x51 && !(rand() & 7))
    {
        Sound_call(0xA1, 0, 0);
    }
    if (wp->frame_10 < 0x64)
    {
        pl->pos_438.z += 0x18;
        pl->fixed_428.z = pl->pos_438.z << 16;
    }
}

void func_801117A8(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                Cd_subcmd(0, 1, 0);
                Obj_work_flag_change(0x5E, 0x80);
                wp->reserved09[1] = 0x80;
                Cd_read_comb(0xB5);
                wp->routine_5++;
            }
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                Cd_xa_play_id(0x2000001C);
                wp->reserved09[2]++;
                wp->routine_5++;
            }
            break;
        case 2:
            if (func_8001D878() != 0)
            {
                func_8001EAE8(&D_80118544[0]);
                func_8001EAE8(&D_80118544[1]);
                STAGE_PL.value_442   = 0xC00;
                STAGE_PL.pos_438.x   = -0xBB8;
                STAGE_PL.pos_438.z   = -0xA00;
                STAGE_PL.fixed_428.x = 0xF4480000;
                STAGE_PL.fixed_428.z = 0xF6000000;
                func_8003786C(0x1B);
                func_8003786C(0x1C);
                func_8003786C(0x1D);
                func_8003786C(0x25);
                func_8003786C(0x26);
                func_8003786C(0x27);
                func_80111DE4(0);
                func_80017C30(6);
                wp->routine_5++;
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                wp->frame_10 = 0;
                wp->reserved09[1] &= 1;
                wp->routine_5++;
            }
            break;
        case 4:
            if (wp->frame_10 == 0x8C)
            {
                Sce_event_next();
                Obj_work_flag_change(0x60, 0x80);
                wp->routine_5 = 0;
            }
            break;
    }
    D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 16;
    if (func_8001DE84() != 0)
    {
        wp->reserved09[1] |= 1;
    }
}

void func_801119DC(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 1)
    {
        func_80111DE4(1);
        wp->child_2C->routine_1 = 5;
        wp->child_2C->routine_2 = 0;
        wp->child_30->routine_1 = 5;
        wp->child_30->routine_2 = 0;
    }
    D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 17;
}

void func_80111A78(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        Obj_work_flag_change(0x60, 0x80);
        func_80111DE4(2);
    }
    if (wp->frame_10 == 0x46)
    {
        wp->routine_6 = 0;
        D_800BC7D4[0] = 0;
    }
    if (wp->routine_6 != 0)
    {
        D_800BC7D4[0] = D_80118E88[STAGE_FRAME & 3] << 15;
    }
}
