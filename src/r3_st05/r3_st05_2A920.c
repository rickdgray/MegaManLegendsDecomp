#include "common.h"
#include "st05.h"

void func_8012A920(STAGE_OBJ *wp)
{
    D_80137754[wp->routine_0](wp);
    wp->value_48.value = 0;
}

void func_8012A96C(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;
    sint32 y;

    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[3] = 0;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    scale.x = scale.y = scale.z = 0x400;
    ScaleMatrix(&wp->matrix.m, &scale);
    y             = func_80048EA4(&wp->pos_38, NULL, 0, wp->index_1);
    wp->color_40  = 0x808080;
    wp->pos_38.y  = y - 0xA;
    wp->model_10  = D_80137760;
    wp->value_48  = 0;
    wp->value_4C  = 0;
    wp->routine_1 = 0;
    wp->routine_0++;
}

void func_8012AA30(STAGE_OBJ50 *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (!Sce_flag_test(0x670))
    {
        if (wp->u_C.b.hi != 0)
        {
            wp->u_C.b.hi--;
        }
        else if (wp->u_C.b.lo == 0)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
            Sce_flag_on(0x670);
            return;
        }
        else
        {
            wp->u_C.b.lo--;
            wp->u_C.b.hi = 0x3C;
        }
    }
    if (pl->target_184 == wp)
    {
        wp->routine_1 = 0xA;
        wp->routine_0++;
        Sce_flag_on(0x670);
        return;
    }
    func_800341BC(&wp->pos_38, 0x28, 0, 0x8000, wp->index_1, &wp->value_48, 0x4000000, 0, 0x80);
}

void func_8012AB24(ST05_PRIZE *wp)
{
    STAGE_PL_VIEW *pl;
    STAGE_CAM *cam;
    STCOM_EFFECT *fx;

    cam = &Sce_camera_work;
    pl  = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl) != 0 && func_8003A13C() == 0)
            {
                wp->routine_1++;
            }
            break;
        case 1:
            func_8001E6C0(0, 0, 0);
            cam->pos_10 = wp->pos_38.x << 16;
            cam->pos_14 = wp->pos_38.y << 16;
            cam->pos_18 = wp->pos_38.z << 16;
            cam->rot_40 = D_80137840[wp->variant_3][wp->value_E].x << 16;
            cam->rot_44 = D_80137840[wp->variant_3][wp->value_E].y << 16;
            cam->rot_48 = D_80137840[wp->variant_3][wp->value_E].z << 16;
            wp->routine_1++;
            break;
        case 2:
            if (func_8003A13C() == 0)
            {
                wp->timer_C = 0x1E;
                wp->routine_1++;
            }
            break;
        case 3:
            if (--wp->timer_C == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0           = 5;
                fx->kind_2            = 0x80;
                fx->variant_3         = 0x41;
                fx->sprite.position   = wp->pos_38;
                fx->sprite.position.y = wp->pos_38.y - 0x32;
                Sound_call(0xA4, 0, 0);
                if (wp->variant_3 == 0)
                {
                    func_80037738(Map_cell_get(&wp->pos_38) | 0xF0000, 10000);
                }
                else if (wp->variant_3 == 1)
                {
                    func_80037738(Map_cell_get(&wp->pos_38) | 0xF0000, 10000);
                    Sce_flag_on(0x671);
                }
                else if (wp->variant_3 == 2)
                {
                    func_80037738(Map_cell_get(&D_80137820[wp->value_E]) | 0xF0000, 10000);
                    Sce_flag_on(0x672);
                }
                func_8012AFA0();
                wp->fx_44 = fx;
                wp->flags_0 &= ~2;
                wp->routine_1++;
            }
            break;
        case 5:
            fx = wp->fx_44;
            if ((sint8)fx->flags_0 == 0) // a signed byte test (lb)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->variant_3 != 0 ? 0x41 : 0x3E);
                wp->routine_1++;
            }
            break;
        case 6:
            if (D_800987B0[0] == 0)
            {
                D_800A395C = 1;
                func_80039820();
                wp->routine_1++;
            }
            break;
        case 10:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_448 = 0x30;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 11:
            pl->value_448 = 0x34;
            wp->timer_C   = 0x10;
            wp->routine_1++;
            break;
        case 12:
            if (wp->timer_C != 0)
            {
                wp->timer_C--;
            }
            else
            {
                wp->flags_0 &= ~2;
            }
            if (pl->flags_A7 < 0)
            {
                wp->routine_1++;
            }
            break;
        case 13:
            func_80063BC8(&wp->pos_38, 2, 0, (Sce_flag_test(0x671) || Sce_flag_test(0x672)) ? 0x40 : 0x3F);
            wp->routine_1++;
            break;
        case 14:
            if (!(Moji_flag & 0x08000000))
            {
                if (wp->variant_3 == 1)
                {
                    Sce_flag_on(0x671);
                }
                else if (wp->variant_3 == 2)
                {
                    Sce_flag_on(0x672);
                }
                func_8012AFA0();
                wp->routine_1++;
            }
            break;
        case 7:
        case 15:
            if (func_8003A13C() == 0)
            {
                func_80042314(pl);
                pl->flags_0 |= 2;
                func_80031A4C(wp);
                Sce_flag_off(0x670);
            }
            break;
        case 20:
            break;
    }
}

sint32 func_8012AFA0(void)
{
    if (Sce_flag_test(0x671) && Sce_flag_test(0x672))
    {
        if (!Sce_flag_test(0x575) || !Sce_flag_test(0x576))
        {
            if (Sce_flag_test(0x575))
            {
                func_8001E3F0(4);
            }
            else if (!Sce_flag_test(0x576))
            {
                func_8001E3F0(5);
            }
            else
            {
                func_8001E3F0(4);
            }
            Sce_flag_on(0x205);
            func_8001E390(0x2E6);
        }
        else
        {
            func_8001E3F0(8);
            func_8001E390(0x2E5);
        }
        Sce_flag_off(0x7E0);
        Sce_flag_off(0x236);
        Sce_flag_on(0x206);
        Game_work.value_78 = 1;
        return 1;
    }
    return 0;
}

void func_8012B078(STAGE_OBJ *wp)
{
    D_801378A0[wp->routine_0](wp);
}

void func_8012B0B4(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 0x10 extra bytes

    wp->flags_0 |= 6;
    Model_work_init(wp, &wp->variant_3);
    STAGE_MATRIX_IDENTITY(wp->matrix.words);
    RotMatrixY(wp->value_F << 10, &wp->matrix.m);
    func_8012B44C(wp);
    wp->color_40  = 0x808080;
    wp->model_10  = D_801378B0;
    wp->value_48  = 0;
    wp->value_4C  = 0;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_0++;
}

void func_8012B15C(STAGE_OBJ50 *wp)
{
    sint16 floor;
    sint16 y;

    STAGE_MATRIX_IDENTITY(wp->matrix.words);
    switch (wp->routine_1)
    {
        case 0:
            wp->value_4C = 0x400000;
            wp->value_48 = wp->pos_38.y << 16;
            wp->routine_1++;
            // fall through
        case 1:
            floor = Ceiling_height_get(&wp->pos_38) - 0x14;
            wp->value_48 -= wp->value_4C;
            wp->pos_38.y = y = ((STAGE_FIXED *)&wp->value_48)->words.integer;
            wp->value_4C -= 0x40000;
            if (floor < y)
            {
                RotMatrixX(0x400, &wp->matrix.m);
                wp->pos_38.y  = floor;
                wp->routine_2 = 0;
                wp->routine_0++;
            }
            else
            {
                RotMatrixX(wp->routine_2 << 4, &wp->matrix.m);
                RotMatrixY(wp->routine_2 << 4, &wp->matrix.m);
                wp->routine_2 += 0xD;
            }
            break;
    }
    func_8012B44C(wp);
}

void func_8012B298(STAGE_OBJ50 *wp)
{
    if (STAGE_PL.target_184 == wp)
    {
        wp->routine_1 = 0;
        wp->routine_0++;
    }
    func_800341BC(&wp->pos_38, 0x28, 0, 0x8000, wp->index_1, &wp->value_48, 0x4000000, 0, 0x80);
    wp->value_48 = 0;
}

void func_8012B314(STAGE_OBJ50 *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_2 = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            pl->value_448 = 0x34;
            wp->routine_2 = 0;
            wp->routine_1++;
            break;
        case 2:
            if (wp->routine_2 > 0x10)
            {
                wp->routine_2 = 0;
                wp->flags_0 &= ~2;
                wp->routine_1++;
            }
            else
            {
                wp->routine_2++;
            }
            break;
        case 3:
            if (pl->flags_A7 < 0)
            {
                func_80063BC8(&wp->pos_38, 2, 0, 0x45);
                Sce_flag_on(0x546);
                wp->routine_1++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                func_80042314(pl);
                func_80031A4C(wp);
            }
            break;
    }
}

void func_8012B44C(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR scale;

    scale.x = scale.y = scale.z = 0x200;
    scale.pad                   = 0;
    ScaleMatrix(&wp->matrix.m, &scale);
}

void func_8012B484(STAGE_OBJ50 *wp, sint32 x, sint32 z, uint8 variant, uint8 flag, uint8 value)
{
    ST05_PROP *obj;

    obj = (ST05_PROP *)Open_SHL_WORK();
    if (obj != NULL)
    {
        obj->flags_0    = 1;
        obj->kind_2     = 0x1F;
        obj->position.y = -1;
        obj->variant_3  = variant;
        obj->value_C    = 0;
        obj->position.x = x;
        obj->position.z = z;
        if (variant < 4 && flag == 0)
        {
            obj->rotation.y = 0x400;
        }
        else
        {
            obj->rotation.y = 0;
        }
        obj->value_E = wp->index_1;
        obj->value_F = value;
    }
}

void func_8012B544(STAGE_OBJ50 *wp)
{
    ST05_ITEM *item;
    ST05_SPOT_POS *pos;
    sint32 i;

    item = D_801379E4[wp->value_F].items_0;
    for (i = 0; item->x_0 != 0; i++, item++)
    {
        if (item->flag_5 == 0)
        {
            func_8012B484(wp, item->x_0, item->z_2, item->variant_4, 0, i);
        }
        else
        {
            func_8012B484(wp, item->x_0, item->z_2, item->variant_4, item->flag_5, i);
        }
    }
    pos = D_801379E4[wp->value_F].spots_4;
    while (pos->x_0 != 0)
    {
        func_8012B484(wp, pos->x_0, pos->z_2, 4, 0, 0);
        pos++;
    }
}

void func_8012B680(STAGE_OBJ50 *wp)
{
    sint16 x;
    sint16 z;

    Player_work.routine_0 = 3;
    Player_work.routine_1 = 1;
    Player_work.flags_bd |= 0x10;
    x                    = D_801379F8[wp->value_F].x_18;
    STAGE_PL.pos_438.y   = -1;
    STAGE_PL.pos_438.x   = x;
    z                    = D_801379F8[wp->value_F].z_1A;
    STAGE_PL.fixed_428.x = x << 16;
    STAGE_PL.fixed_428.y = 0xFFFF0000;
    STAGE_PL.value_440   = 0;
    STAGE_PL.pos_438.z   = z;
    STAGE_PL.fixed_428.z = z << 16;
    STAGE_PL.value_442   = D_801379F8[wp->value_F].angle_1C;
    STAGE_PL.value_444   = 0;
    STAGE_PL.value_448   = 0;
}

// A for (;;) loop that returns 0 at the end marker and breaks out to the gate check gives
// retail's unrotated loop and its item+2 induction pointer; pos = &wp->pos_14 gives the hoisted
// wp+20. A shift variable per arm (d1, d2) keeps w = variant + 1 in a3. a's sign extension is
// written into the cross-block `ext` (used by both tests), so global alloc gives the shifts a's
// register; a block-local extension would take v0 ahead of b.
sint32 func_8012B788(ST05_RACE *wp)
{
    STAGE_PL_VIEW *pl;
    ST05_ITEM *item;
    sint32 i;
    sint32 w;
    sint32 d1;
    sint32 d2;
    STCOM_SVECTOR *pos;
    sint32 mid;
    sint32 mid2;
    sint16 x;
    sint16 a;
    sint16 b;
    sint32 ext;

    i    = 0;
    pl   = &STAGE_PL;
    item = D_801379E4[wp->value_F].items_0;
    pos  = &wp->pos_14;
    for (;;)
    {
        x = item->x_0;
        if (x == 0)
        {
            return 0;
        }
        w = item->variant_4 + 1;
        if (item->flag_5 == 0)
        {
            mid = (pl->position.z + pl->value_30) >> 1;
            d1  = w << 6;
            if (item->z_2 + d1 < mid || mid < item->z_2 - d1)
            {
                goto next;
            }
            a = pl->value_2C; // set twice: puts a in v1
            a = x - a;
            b = x - pos->x;
        }
        else
        {
            mid2 = (pl->position.x + pl->value_2C) >> 1;
            d2   = w << 6;
            if (x + d2 < mid2 || mid2 < x - d2)
            {
                goto next;
            }
            a = item->z_2 - pl->value_30;
            b = item->z_2 - pos->z;
        }
        ext = a << 16;
        ext >>= 16;
        if (ext * b < 0 || ext == 0)
        {
            break;
        }
    next:
        i++;
        item++;
    }
    if (i != wp->gate_C)
    {
        return 1;
    }
    wp->gate_C++;
    if (item[1].x_0 == 0)
    {
        return 2;
    }
    return 3;
}

void func_8012B8FC(STAGE_OBJ *wp)
{
    Sound_call(0x1D, 1, 0);
    wp->routine_1    = 0;
    wp->routine_2    = 0;
    wp->routine_3    = 0;
    wp->u_E.b.byte_E = (uint8)wp->u_E.b.byte_F + 1;
}

void func_8012B948(STAGE_OBJ50 *wp)
{
    sint32 kind;
    uint32 d;
    STCOM_SVECTOR unused; // unused: retail's frame has room for it

    kind = Game_work_90[wp->value_F].kind_0;
    if (kind == 3)
    {
        d = (uint32)(D_801379F8[wp->value_F].value_0 - (wp->value_48 & ~3)) / 15;
        func_8005C224(D_801379F8[wp->value_F].value_10 + d * d);
    }
    else
    {
        func_8005C224(D_801379F8[wp->value_F].value_4[kind]);
    }
}

uint8 func_8012BA14(STAGE_OBJ50 *wp)
{
    sint32 i;
    sint32 j;
    sint32 k;

    for (i = 0; i < 3; i++)
    {
        if (wp->value_48 <= Game_work_84[wp->value_F * 3 + i].score_0)
        {
            for (j = 2; i < j; j--)
            {
                Game_work_84[wp->value_F * 3 + j].score_0 = Game_work_84[wp->value_F * 3 + j - 1].score_0;
                for (k = 0; k < 4; k++)
                {
                    Game_work_84[wp->value_F * 3 + j].name_4[k] = Game_work_84[wp->value_F * 3 + j - 1].name_4[k];
                }
            }
            Game_work_84[wp->value_F * 3 + i].score_0 = wp->value_48;
            return i;
        }
    }
    return 3;
}

void func_8012BB3C(void)
{
    STAGE_50 *slot;
    uint32 mask;
    sint32 i;

    mask = D_800989CC;
    slot = D_800BF118;
    for (i = 0; i < 32; i++, slot++)
    {
        if ((sint32)(mask << i) < 0)
        {
            switch (slot->kind_2)
            {
                case 0xE:
                case 0x18:
                case 0x19:
                case 0x21:
                    func_80052528(slot);
                    func_80031A4C(slot);
                    break;
            }
        }
    }
}

void func_8012BBF8(STAGE_OBJ50 *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            Sound_fade_start(0x10);
            Sce_flag_on(0x7E0);
            func_8012BB3C();
            wp->routine_1++;
            break;
        case 1:
            if (func_80042238(&Player_work))
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                Sound_work.volume_6 = 0x50;
                Sound_call(0x1D, 1, 0);
                MojiTaskExec2(0, 0x2F);
                wp->routine_1++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000))
            {
                wp->value_E   = 0;
                wp->routine_1 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_8012BD2C(STAGE_OBJ50 *wp)
{
    uint8 next;
    uint8 *row;
    sint32 choice;
    sint32 msg;
    sint32 msg2;

    switch (wp->routine_2)
    {
        case 0:
            MojiTaskExec2(0, D_801378BC[wp->value_E * 5]);
            wp->routine_2++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                choice = Moji_flag & 0xFF;
                row    = &D_801378BD[wp->value_E * 5];
                next   = row[choice];
                if (next == 0xFF)
                {
                    wp->routine_1 = 0;
                    wp->routine_2 = 0;
                    wp->routine_0++;
                    break;
                }
                wp->value_F = next;
                Fade_start(9);
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                Obj_work_flag_change(0x18, 0x80);
                func_8012B680(wp);
                wp->routine_2++;
            }
            break;
        case 3:
            Fade_start(1);
            func_8012B544(wp);
            wp->u_C.b.lo = 0;
            wp->value_48 = 0;
            wp->u_C.b.hi = 0;
            wp->routine_2++;
            break;
        case 4:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                msg = Game_work_90[wp->value_F].kind_0 + 0x4E;
                MojiTaskExec2(0, wp->value_F * 4 + msg);
                Sound_fade_start(0x10);
                wp->routine_2++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000) && Sound_fade_flags == 0)
            {
                func_80042314(&Player_work);
                MojiTaskExec2(2, 0x39);
                msg2 = Game_work_90[wp->value_F].kind_0 + 0x64;
                MojiTaskExec2(3, wp->value_F * 4 + msg2);
                Cd_xa_play_id(0x2001000D);
                wp->routine_2 = 0;
                wp->routine_1++;
            }
            break;
    }
}

void func_8012BF74(ST05_RACE *wp)
{
    if (wp->value_D == 0)
    {
        wp->time_48++;
    }
    else
    {
        if ((sint8)(wp->value_D % 7) == 0)
        {
            Sound_call2(0x169, &Player_work.position);
        }
        wp->value_D--;
    }
    switch (func_8012B788(wp) & 0xFF)
    {
        case 1:
            wp->routine_2 = 0;
            wp->routine_1++;
            break;
        case 2:
            Sound_call2(0x16A, &Player_work.position);
            D_80138018 = func_8012BA14((STAGE_OBJ50 *)wp);
            wp->routine_1++;
            if (D_80138018 != 0)
            {
                if (Game_work_90[wp->value_F].kind_0 == 3 && Sce_flag_test(wp->value_F + 0x201) == 0)
                {
                    wp->routine_2 = 3;
                }
                else
                {
                    wp->routine_2 = 2;
                }
            }
            else
            {
                if (Game_work_90[wp->value_F].kind_0 == 3 && Sce_flag_test(wp->value_F + 0x201) == 0)
                {
                    wp->routine_2 = 5;
                }
                else
                {
                    wp->routine_2 = 4;
                }
            }
            break;
        case 3:
            Sound_call2(0x167, &Player_work.position);
            // fall through
        case 0:
            if (wp->time_48 >= D_801379EC[wp->value_F].limit_0[Game_work_90[wp->value_F].kind_0])
            {
                wp->routine_2 = 1;
                wp->routine_1++;
            }
            break;
    }
    if (wp->routine_1 == 2)
    {
        func_80053AA4(2);
        func_80053AA4(3);
        Sound_fade_start(0x40);
    }
}

void func_8012C1F4(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_3;
    switch (temp_v1)
    {
        case 0:
            if (func_80042238((STCOM_PL_WORK *)&Player_work) != 0)
            {
                MojiTaskExec2(0, 0x32);
                wp->routine_3++;
                return;
            }
            return;
        case 1:
            if (!(Moji_flag & 0x08000000) && (Sound_seq_is_eos(0) == 0))
            {
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C29C(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_3;
    switch (temp_v1)
    {
        case 0:
            if (func_80042238((STCOM_PL_WORK *)&Player_work) != 0)
            {
                MojiTaskExec2(0, 0x34);
                wp->routine_3++;
                return;
            }
            return;
        case 1:
            if (!(Moji_flag & 0x08000000) && (Sound_seq_is_eos(0) == 0))
            {
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C344(STAGE_OBJ50 *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_8012B948(wp);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x35);
                if (Game_work_90[wp->value_F].kind_0 < 3)
                {
                    Game_work_90[wp->value_F].kind_0++;
                }
                wp->routine_3++;
            }
            break;
        case 1:
            if (D_80138018 < 3)
            {
                if (!(Moji_flag & 0x08000000))
                {
                    func_8005C24C(wp->value_F * 3 + D_80138018);
                    MojiTaskExec2(0, 2);
                    wp->routine_3++;
                }
            }
            else
            {
                wp->routine_3 = 3;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->value_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                func_8012B8FC((STAGE_OBJ *)wp);
            }
            break;
    }
}

void func_8012C4F4(STAGE_OBJ *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                Sce_flag_on(wp->u_E.b.byte_F + 0x201);
                func_8005C218(D_801379F8[wp->u_E.b.byte_F].value_14[0]);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x36);
                wp->routine_3++;
            }
            break;
        case 1:
            if (D_80138018 < 3)
            {
                if (!(Moji_flag & 0x08000000))
                {
                    func_8005C24C(wp->u_E.b.byte_F * 3 + D_80138018);
                    MojiTaskExec2(0, 2);
                    wp->routine_3++;
                }
            }
            else
            {
                wp->routine_3 = 3;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->u_E.b.byte_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                Sce_flag_on(wp->u_E.b.byte_F + 0x201);
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C6A0(STAGE_OBJ50 *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_8012B948(wp);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x37);
                if (Game_work_90[wp->value_F].kind_0 < 3)
                {
                    Game_work_90[wp->value_F].kind_0++;
                }
                wp->routine_3++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                func_8005C24C(wp->value_F * 3 + D_80138018);
                MojiTaskExec2(0, 2);
                wp->routine_3++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->value_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                func_8012B8FC((STAGE_OBJ *)wp);
            }
            break;
    }
}

void func_8012C830(STAGE_OBJ *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                Sce_flag_on(wp->u_E.b.byte_F + 0x201);
                func_8005C218(D_801379F8[wp->u_E.b.byte_F].value_14[0]);
                func_8001E3F0(7);
                MojiTaskExec2(0, 0x4D);
                wp->routine_3++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                func_8005C24C(wp->u_E.b.byte_F * 3 + D_80138018);
                MojiTaskExec2(0, 2);
                wp->routine_3++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, wp->u_E.b.byte_F + 3);
                wp->routine_3++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x08000000) && Sound_seq_is_eos(0) == 0)
            {
                func_8012B8FC(wp);
            }
            break;
    }
}

void func_8012C9B0(STAGE_OBJ *wp)
{
    D_80137A80[wp->routine_2](wp);
}

void func_8012C9EC(STAGE_OBJ *wp)
{
    D_80137A98[wp->routine_1](wp);
    func_8005C230(wp->value_48.value);
}

void func_8012CA40(STAGE_OBJ50 *wp)
{
    switch (wp->routine_1)
    {
        case 0:
            MojiTaskExec2(0, 0x38);
            wp->routine_1++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                D_800C356C = 1;
                D_800C356E = 8;
                D_800C356F = 2;
                D_800C3560 = 0x35F;
                D_800C3562 = -0x41;
                D_800C3564 = 0x160;
                D_800C356A = 0xC00;
                D_800C356D = 0;
                D_800C3571 = 0xA;
                D_800C3570 = 2;
                wp->routine_1++;
            }
            break;
        case 2:
            if (D_800C356C == 2)
            {
                D_800C356C++;
                Sound_work.volume_6 = 0x7F;
                Sce_flag_off(0x7E0);
                Sce_flag_off(0x200);
                STAGE_GAME.value_78 = 1;
                func_80042314(&Player_work);
                func_80031A4C(wp);
            }
            break;
    }
}

void func_8012CBA8(STAGE_OBJ *wp)
{
    D_80137AA4[wp->routine_0](wp);
    wp->position = STAGE_PL_OBJ->position_prev;
}
