#include "common.h"
#include "st0d.h"

void func_80109FD4(STAGE_OBJ *wp)
{
    D_8011244C[wp->routine_0](wp);
}

void func_8010A010(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 0x10 extra bytes
    sint32 flag;

    wp->flags_0 |= 6;
    if (wp->variant_3 == 0)
    {
        flag           = wp->pos_38.pad;
        wp->pos_38.pad = 0;
        wp->value_44   = flag;
    }
    Model_work_init(wp, &wp->variant_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    RotMatrixY(wp->value_F << 6, &wp->matrix.m);
    wp->color_40 = 0x808080;
    wp->model_10 = D_80112470;
    wp->value_48 = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void func_8010A0C0(STAGE_OBJ50 *wp)
{
    STCOM_SVECTOR pos;

    D_80112458[wp->variant_3](wp);
    if (wp->variant_3 != 2)
    {
        func_80051B68(wp, 7, 0, 0);
        pos = wp->pos_38;
        pos.y -= 0x2D;
        func_800341BC(&pos, 0x28, 0, 0x8000, wp->index_1, &wp->value_48, 0x4000000, 0, 0x80);
        wp->value_48 = 0;
    }
}

void func_8010A190(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 5;
        ep->kind_2    = 0x80;
        ep->variant_3 = 0x41;
        ep->pos_38    = wp->pos_38;
        ep->pos_38.y  = wp->pos_38.y - 0x28;
        func_80031A4C(wp);
    }
}

void func_8010A20C(STAGE_OBJ *wp)
{
    D_80112464[wp->routine_1](wp);
}

void func_8010A248(STAGE_OBJ50 *wp)
{
    sint32 hit;

    if (Player_work.target_184 == wp)
    {
        wp->routine_1 = 1;
        wp->routine_2 = 0;
    }
    else
    {
        hit = wp->value_48;
        if (hit & 0x20000000)
        {
            if (func_8010A9CC(wp))
            {
                wp->routine_1 = 2;
            }
            else
            {
                func_8010A670(wp);
                Sound_call2(0x13D, &wp->pos_38);
            }
        }
        else if (hit < 0)
        {
            wp->routine_1 = 0;
            wp->routine_0++;
        }
    }
}

void func_8010A2EC(ST0D_STCOM21_WORK *wp)
{
    STCOM_PL_WORK *pl;
    uint32 zenny;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            if (func_80042238(pl))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                Player_work.value_448 = 0x30;
                Player_work.value_C   = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (!func_8010A9CC(wp))
            {
                func_8005C150(0, 2, 0, 0);
            }
            else if (wp->value_D == 0)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->value_E);
            }
            else if (wp->value_D != 1)
            {
                if (wp->value_D & 0x80)
                {
                    zenny = (((wp->value_D & 0x7F) << 8) | (uint8)wp->value_E) * 10;
                    func_8005C150(0, 1, zenny / 10, 0);
                    Sce_flag_on(wp->value_C + 0x400);
                }
                else if (wp->value_E != -1)
                {
                    func_8005C150(0, 0, (uint8)wp->value_E, 0);
                    Sce_flag_on(wp->value_C + 0x400);
                }
                else
                {
                    func_8005C150(0, 2, 0, 0);
                }
            }
            wp->routine_2++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                func_80042314(pl);
                Player_work.target_184 = NULL;
                pl->flags_0 |= 2;
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_8010A4CC(ST0D_STCOM21_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (wp->value_D != 1)
            {
                Sound_call2(0x13C, &wp->pos_38);
            }
            wp->value_F = (wp->value_B + 0x10) & 0x3F;
            wp->routine_2++;
            // fall through
        case 1:
            wp->routine_2++;
            // fall through
        case 2:
            if (wp->value_F != wp->value_B)
            {
                ST0D_STCOM21_IDENTITY(&wp->matrix);
                RotMatrixZ((sint16)D_8011247C[wp->value_B & 7] >> 2, &wp->matrix.m);
                RotMatrixY(wp->value_B << 6, &wp->matrix.m);
                wp->value_B = (wp->value_B + 1) & 0x3F;
            }
            else if (wp->routine_2 == 2)
            {
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_D == 1 && wp->value_E != -1)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->value_E);
            }
            wp->routine_2++;
            break;
        case 4:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_1  = 0;
                wp->routine_2  = 0;
                wp->y_48.value = 0;
            }
            break;
    }
}

void func_8010A670(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031734();
    if (ep != NULL)
    {
        ep->flags_0   = wp->flags_0;
        ep->variant_3 = 2;
        ep->kind_2    = wp->kind_2;
        ep->pos_38    = wp->pos_38;
        ep->pos_38.y  = wp->pos_38.y - 0x50;
        ep->routine_1 = 0;
        ep->routine_3 = 0;
        ep->value_44  = (sint32)wp;
        Model_work_init(ep, &ep->variant_3);
        wp->variant_3 = 1;
        Model_work_init(wp, &wp->variant_3);
        wp->matrix.words[0] = 0x1000;
        wp->matrix.words[1] = 0;
        wp->matrix.words[2] = 0x1000;
        wp->matrix.words[3] = 0;
        wp->matrix.words[4] = 0x1000;
        wp->matrix.words[5] = 0;
        wp->matrix.words[6] = 0;
        wp->matrix.words[7] = 0;
        RotMatrixY(wp->value_F << 6, &wp->matrix.m);
        wp->routine_1 = 0;
    }
}

void func_8010A748(ST0D_STCOM21_WORK *wp)
{
    ST0D_STCOM21_IDENTITY(&wp->matrix);
    RotMatrixZ((sint16)D_8011247C[wp->value_B & 7] >> 2, &wp->matrix.m);
    RotMatrixY(wp->value_B << 6, &wp->matrix.m);
}

void func_8010A7D4(ST0D_STCOM21_WORK *wp)
{
    ST0D_STCOM21_WORK *chest;
    sint16 top;

    chest = wp->u_44.chest;
    switch (wp->routine_1)
    {
        case 0:
            wp->speed_4C   = 0x200000;
            wp->routine_1  = 1;
            wp->y_48.value = wp->pos_38.y << 16;
            // fall through
        case 1:
            if (chest->value_D == 1 && chest->value_E == 0x10)
            {
                func_8010AA54(chest);
            }
            wp->routine_1++;
            // fall through
        case 2:
            top = chest->pos_38.y - 0x50;
            wp->y_48.value -= wp->speed_4C;
            wp->speed_4C -= 0x40000;
            wp->pos_38.y = wp->y_48.words.integer;
            if (top < wp->pos_38.y)
            {
                chest->variant_3  = 0;
                chest->routine_0  = 1;
                chest->routine_1  = 0;
                chest->y_48.value = 0;
                chest->speed_4C   = 0;
                Model_work_init(chest, &chest->variant_3);
                ST0D_STCOM21_IDENTITY(&chest->matrix);
                RotMatrixX(0, &chest->matrix.m);
                RotMatrixY(chest->value_B << 6, &chest->matrix.m);
                RotMatrixZ(0, &chest->matrix.m);
                func_80031A4C(wp);
            }
            else
            {
                ST0D_STCOM21_IDENTITY(&wp->matrix);
                RotMatrixZ((sint16)D_8011247C[chest->value_B & 7], &wp->matrix.m);
                RotMatrixY(wp->value_F << 6, &wp->matrix.m);
                chest->value_B++;
            }
            break;
    }
}

uint8 func_8010A9CC(STAGE_OBJ50 *wp)
{
    sint32 flag;

    flag = wp->value_44;
    if (wp->u_C.b.hi == 1 && wp->value_E == 0x10)
    {
    fail:
        return 0;
    }
    if (flag != 0 && !Sce_flag_test(flag))
    {
        return 0;
    }
    if (Sce_flag_test(wp->u_C.b.lo + 0x400))
    {
        return 0;
    }
    if (wp->value_E == -1)
    {
        goto fail;
    }
    return 1;
}

void func_8010AA54(ST0D_STCOM21_WORK *wp)
{
    ST0D_STCOM21_OBJ *obj;
    uint8 i;

    for (i = 0; i < 3; i++)
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            obj->flags_0          = 1;
            obj->kind_2           = 0x10;
            obj->handler_4        = 1;
            obj->position         = wp->pos_38;
            obj->rotation.y       = i * 0x600;
            obj->position_fixed.x = obj->position.x << 16;
            obj->position_fixed.y = obj->position.y << 16;
            obj->position_fixed.z = obj->position.z << 16;
        }
    }
}

void func_8010AB1C(STAGE_OBJ50 *wp)
{
    STCOM_SVECTOR pos;

    func_80051B68(wp, 7, 0, 0);
    D_8011248C[wp->routine_0](wp);
    pos = wp->pos_38;
    pos.y -= 0x2D;
    func_800341BC(&pos, 0x32, 0, 0x8000, wp->index_1, &wp->value_48, 0x4000000, 0, 0x80);
    wp->value_48 = 0;
}

void func_8010ABDC(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 0x10 extra bytes
    sint32 flag;

    wp->flags_0 |= 6;
    flag           = wp->pos_38.pad;
    wp->pos_38.pad = 0;
    wp->value_44   = flag;
    Model_work_init(wp, &wp->variant_3);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    RotMatrixY(wp->value_F << 10, &wp->matrix.m);
    wp->color_40 = 0x808080;
    wp->model_10 = D_8011249C;
    wp->value_48 = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void func_8010AC80(STAGE_OBJ50 *wp)
{
    if (Player_work.target_184 == wp)
    {
        wp->routine_0++;
    }
    if (wp->value_48 < 0)
    {
        wp->routine_0 = 3;
    }
}

void func_8010ACC0(ST0D_STCOM21_WORK *wp)
{
    STCOM_PL_WORK *pl;
    sint32 zenny;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl))
            {
                Player_work.routine_0 = 3;
                Player_work.routine_1 = 0;
                Player_work.value_448 = 0x30;
                Player_work.value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            if (!func_8010AF28(wp))
            {
                func_8005C150(1, 2, 0, 0);
            }
            else if (wp->value_D == 0)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->value_E);
            }
            else if (wp->value_D != 1)
            {
                if (wp->value_D & 0x80)
                {
                    zenny = (((wp->value_D & 0x7F) << 8) | (uint8)wp->value_E) * 10;
                    func_8005C150(1, 1, zenny / 10, 0);
                    Sce_flag_on(wp->value_C + 0x400);
                }
                else if (wp->value_E != -1)
                {
                    func_8005C150(1, 0, (uint8)wp->value_E, 0);
                    Sce_flag_on(wp->value_C + 0x400);
                }
                else
                {
                    func_8005C150(1, 2, 0, 0);
                }
            }
            wp->routine_1++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                func_80042314(pl);
                Player_work.target_184 = NULL;
                pl->flags_0 |= 2;
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_8010AEAC(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 5;
        ep->kind_2    = 0x80;
        ep->variant_3 = 0x41;
        ep->pos_38    = wp->pos_38;
        ep->pos_38.y  = wp->pos_38.y - 0x28;
        func_80031A4C(wp);
    }
}

uint8 func_8010AF28(ST0D_STCOM21_WORK *wp)
{
    if ((wp->u_44.flag == 0 || Sce_flag_test(wp->u_44.flag)) && !Sce_flag_test(wp->value_C + 0x400) && wp->value_E != -1)
    {
        return 1;
    }
    return 0;
}

void func_8010AF94(STAGE_OBJ *wp)
{
    STAGE_OBJ *owner;

    owner = func_80036294(wp->u_C.b.byte_C);
    if (STAGE_GAME.value_50 != 0xD || owner->u_C.b.byte_C != 0)
    {
        D_801124C0[wp->variant_3](wp);
    }
}

void func_8010B010(STAGE_OBJ *wp)
{
    D_801124CC[wp->routine_0](wp);
}

void func_8010B04C(ST0D_PAIRS *wp)
{
    uint8 *pair;
    uint32 i;

    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
    wp->value_F   = 0;
    for (i = 0, pair = wp->pair_28[0]; i < 16; i++)
    {
        pair[0] = 0;
        pair[1] = 0;
        pair += 2;
    }
}

void func_8010B08C(ST0D_FLAMES *wp)
{
    STAGE_OBJ *owner;
    ST0D_FLAME *flame;
    uint32 dist;
    uint32 i;

    flame = wp->flame_28;
    owner = func_80036294(wp->value_C);
    if (wp->timer_D == 0)
    {
        if (!(owner->flags_0 & 1))
        {
            wp->routine_0++;
            return;
        }
    }
    else if (wp->timer_D == 1)
    {
        if (owner->value_44.half[0] == 0)
        {
            wp->routine_0++;
            return;
        }
    }
    if (wp->count_F < 0x40)
    {
        wp->count_F++;
    }
    wp->x_1C = owner->position.x;
    wp->y_1E = owner->position.y;
    wp->z_20 = owner->position.z;
    dist     = D_801124A8[wp->timer_D];
    wp->x_1C += (rsin((owner->rotation.y + 0x800) & 0xFFF) * dist) >> 12;
    wp->z_20 += (rcos((owner->rotation.y + 0x800) & 0xFFF) * dist) >> 12;
    wp->y_1E -= D_801124B8[wp->timer_D];
    for (i = 0; i < 6; i++)
    {
        if (flame[i].flags_0 & 1)
        {
            func_8010B29C(wp, (owner->rotation.y + 0x800) & 0xFFF, flame[i].frame_1);
            if (++flame[i].frame_1 >= 25)
            {
                flame[i].frame_1 = 0;
            }
        }
        else if (i < (wp->count_F >> 2))
        {
            flame[i].flags_0 |= 1;
        }
    }
}

void func_8010B27C(STAGE_OBJ *wp)
{
    func_80031988(wp);
}

// len is a sint16: as a sint32 it swaps s1/s2 with frame's extension. The position words are
// read through casts: scalar stack loads may move above the packet's struct stores, as in retail.
// The local copy of frame orders the spill slots (rot at 0x18, frame at 0x20), and the (sint16)
// casts stop fold-const reassociating the constants. The same code as st0b's func_80115780.
void func_8010B29C(ST0D_FLAMES *wp, sint16 angle, sint8 arg)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    sint16 rot;
    sint32 bob;
    sint16 len;
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 u;
    uint8 v;
    sint8 frame;

    frame = arg;
    rot   = (angle + (sint16)(frame * 16 + 0x400)) & 0xFFF;
    b     = 0xF0;
    bob   = (frame << 7) & 0xFFF;
    g     = 0xA0;
    r     = 0xA0;
    len   = frame * 15;
    u     = 0x80;
    pos.x = wp->x_1C + ((rsin(rot) * len) >> 12);
    pos.z = wp->z_20 + ((rcos(rot) * len) >> 12);
    v     = 0x40;
    if (frame <= 16)
    {
        pos.y = wp->y_1E - ((rsin(bob) * 40) >> 12);
    }
    else
    {
        pos.y = wp->y_1E;
    }
    p          = func_8002D464();
    p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
    p->uv_C    = 0x3D480000 | (v << 8) | u;
    p->uv_14   = 0xE0000 | (v << 8) | (u + 0x1F);
    p->uv_1C   = ((v + 0x1F) << 8) | u;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
    p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
    p->size_18 = D_801124B0[wp->timer_D] - frame * 2;
    rot        = ((sint16)(rot - 0x800) - (frame << 5)) & 0xFFF;
    p->pad_20  = 0;
    pos.x      = wp->x_1C + ((rsin(rot) * len) >> 12);
    pos.z      = wp->z_20 + ((rcos(rot) * len) >> 12);
    p          = func_8002D464();
    p->code_4  = 0x2E000000 | (b << 16) | (g << 8) | r;
    p->uv_C    = 0x3D480000 | (v << 8) | u;
    p->uv_14   = 0xE0000 | (v << 8) | (u + 0x1F);
    p->uv_1C   = ((v + 0x1F) << 8) | u;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
    p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
    p->size_18 = D_801124B0[wp->timer_D] - frame * 2;
    p->pad_20  = 0;
}

void func_8010B508(STAGE_OBJ *wp)
{
    D_801124D8[wp->routine_0](wp);
}

void func_8010B544(ST0D_FLAMES *wp)
{
    STAGE_OBJ *owner;
    ST0D_FLAME *flame;
    uint32 i;

    flame = wp->flame_28;
    owner = func_80036294(wp->value_C);
    if (!(owner->flags_0 & 1))
    {
        wp->routine_0++;
        return;
    }
    if (wp->count_F < 0x40)
    {
        wp->count_F++;
    }
    wp->x_1C = owner->position.x;
    wp->y_1E = owner->position.y;
    wp->z_20 = owner->position.z;
    wp->x_1C += (rsin(owner->rotation.y & 0xFFF) * 500) >> 12;
    wp->z_20 += (rcos(owner->rotation.y & 0xFFF) * 500) >> 12;
    wp->y_1E -= 0x60;
    for (i = 0; i < 6; i++)
    {
        if (flame[i].flags_0 & 1)
        {
            func_8010B6E8(wp, owner->rotation.y & 0xFFF, flame[i].frame_1);
            if (++flame[i].frame_1 >= 13)
            {
                flame[i].frame_1 = 0;
            }
        }
        else if (i < (wp->count_F >> 1))
        {
            flame[i].flags_0 |= 1;
        }
    }
}

// Scalar reads of the position words let them move above the packet stores, as in retail.
void func_8010B6E8(ST0D_FLAMES *wp, sint32 angle, sint8 frame)
{
    STCOM_SVECTOR pos;
    STCOM23_PACKET *p;
    sint32 v;
    sint32 y;
    sint16 side;

    v     = rsin((sint16)angle) * 30;
    pos.x = wp->x_1C + ((v * frame) >> 12);
    v     = rcos((sint16)angle) * 30;
    side  = (angle + 0x400) & 0xFFF;
    pos.z = wp->z_20 + ((v * frame) >> 12);
    y     = frame * 4;
    pos.y = wp->y_1E + y;
    pos.x += (rsin(side) * 100) >> 12;
    pos.z += (rcos(side) * 100) >> 12;
    p          = func_8002D464();
    p->uv_1C   = 0x5F80;
    p->code_4  = 0x2EF0A0A0;
    p->uv_C    = 0x3D484080;
    p->uv_14   = 0xE409F;
    p->uv_24   = 0x5F9F;
    p->size_18 = 0x80 - y;
    p->pad_20  = 0;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
    v          = rsin((sint16)angle) * 30;
    pos.x      = wp->x_1C + ((v * frame) >> 12);
    v          = rcos((sint16)angle) * 30;
    side       = (side - 0x800) & 0xFFF;
    pos.z      = wp->z_20 + ((v * frame) >> 12);
    pos.x += (rsin(side) * 100) >> 12;
    pos.z += (rcos(side) * 100) >> 12;
    p          = func_8002D464();
    p->uv_1C   = 0x5F80;
    p->code_4  = 0x2EF0A0A0;
    p->uv_C    = 0x3D484080;
    p->uv_14   = 0xE409F;
    p->uv_24   = 0x5F9F;
    p->size_18 = 0x80 - y;
    p->pad_20  = 0;
    p->xy_8    = *(uint32 *)&pos.x;
    p->z_10    = *(uint32 *)&pos.z;
}

void func_8010B97C(STAGE_OBJ *wp)
{
    D_801124E4[wp->routine_0](wp);
}

void func_8010B9B8(ST0D_FLAMES *wp)
{
    STAGE_OBJ *owner;
    ST0D_FLAME *flame;
    uint32 i;
    flame = wp->flame_28;
    owner = func_80036294(wp->value_C);
    if (owner->value_44.half[0] == 0)
    {
        wp->routine_0++;
        return;
    }
    if (wp->count_F < 0x40)
    {
        wp->count_F++;
    }
    wp->x_1C = owner->position.x;
    wp->y_1E = owner->position.y;
    wp->z_20 = owner->position.z;
    wp->x_1C += (rsin(owner->rotation.y & 0xFFF) * 0x140) >> 12;
    wp->z_20 += (rcos(owner->rotation.y & 0xFFF) * 0x140) >> 12;
    wp->y_1E -= 0x10;
    for (i = 0; i < 4; i++)
    {
        if (flame[i].flags_0 & 1)
        {
            func_8010BB48(wp, owner->rotation.y & 0xFFF, flame[i].frame_1);
            if (++flame[i].frame_1 >= 9)
            {
                flame[i].frame_1 = 0;
            }
        }
        else if (i < (wp->count_F >> 1))
        {
            flame[i].flags_0 |= 1;
        }
    }
}

void func_8010BB48(ST0D_FLAMES *wp, sint16 angle, sint8 frame)
{
    STCOM_SVECTOR_W pos;
    STCOM23_PACKET *p;
    sint32 v;
    uint32 xy;
    uint32 z;

    v          = rsin(angle) * 30;
    pos.v.x    = wp->x_1C + ((v * frame) >> 12);
    v          = rcos(angle) * 30;
    pos.v.z    = wp->z_20 + ((v * frame) >> 12);
    v          = frame * 4;
    pos.v.y    = wp->y_1E + v;
    p          = func_8002D464();
    p->code_4  = 0x2EF0A0A0;
    p->uv_C    = 0x3D484080;
    p->uv_14   = 0xE409F;
    p->uv_1C   = 0x5F80;
    p->uv_24   = 0x5F9F;
    xy         = pos.words[0];
    z          = pos.words[1];
    p->size_18 = 0x40 - v;
    p->pad_20  = 0;
    p->xy_8    = xy;
    p->z_10    = z;
}
