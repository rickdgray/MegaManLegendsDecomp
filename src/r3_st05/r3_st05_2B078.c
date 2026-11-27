#include "common.h"
#include "st05.h"

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
