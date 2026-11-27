#include "common.h"
#include "st04.h"

void func_80108FE0(STAGE_WORK *wp)
{
    D_80111C84[wp->routine_0](wp);
}

void func_8010901C(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 0x10 extra bytes
    sint32 flag;

    wp->be_flag |= 6;
    if (wp->type == 0)
    {
        flag           = wp->pos_38.pad;
        wp->pos_38.pad = 0;
        wp->value_44   = flag;
    }
    Model_work_init(wp, &wp->type);
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
    wp->model_10 = D_80111CA8;
    wp->value_48 = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void func_801090CC(STAGE_OBJ50 *wp)
{
    STCOM_SVECTOR pos;

    D_80111C90[wp->type](wp);
    if (wp->type != 2)
    {
        func_80051B68(wp, 7, 0, 0);
        pos = wp->pos_38;
        pos.y -= 0x2D;
        func_800341BC(&pos, 0x28, 0, 0x8000, wp->slot, &wp->value_48, 0x4000000, 0, 0x80);
        wp->value_48 = 0;
    }
}

void func_8010919C(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = 5;
        ep->id       = 0x80;
        ep->type     = 0x41;
        ep->pos_38   = wp->pos_38;
        ep->pos_38.y = wp->pos_38.y - 0x28;
        func_80031A4C(wp);
    }
}

void func_80109218(STAGE_OBJ *wp)
{
    D_80111C9C[wp->routine_1](wp);
}

void func_80109254(STAGE_OBJ50 *wp)
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
            if (func_801099D8(wp))
            {
                wp->routine_1 = 2;
            }
            else
            {
                func_8010967C(wp);
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

// Opened by talking to it: hands over the contents.
void func_801092F8(STAGE_OBJ50 *wp)
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
            if (!func_801099D8(wp))
            {
                func_8005C150(0, 2, 0, 0);
            }
            else if (wp->u_C.b.hi == 0)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->value_E);
            }
            else if (wp->u_C.b.hi != 1)
            {
                if (wp->u_C.b.hi & 0x80)
                {
                    zenny = (((wp->u_C.b.hi & 0x7F) << 8) | (uint8)wp->value_E) * 10;
                    func_8005C150(0, 1, zenny / 10, 0);
                    Sce_flag_on(wp->u_C.b.lo + 0x400);
                }
                else if (wp->value_E != -1)
                {
                    func_8005C150(0, 0, (uint8)wp->value_E, 0);
                    Sce_flag_on(wp->u_C.b.lo + 0x400);
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
                pl->be_flag |= 2;
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

// Opened by a hit: the lid flies off.
void func_801094D8(STAGE_OBJ50 *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (wp->u_C.b.hi != 1)
            {
                Sound_call2(0x13C, &wp->pos_38);
            }
            wp->value_F = (wp->routine_3 + 0x10) & 0x3F;
            wp->routine_2++;
            // fall through
        case 1:
            wp->routine_2++;
            // fall through
        case 2:
            if (wp->value_F != wp->routine_3)
            {
                STAGE_MATRIX_IDENTITY(wp->matrix.words);
                RotMatrixZ((sint16)D_80111CB4[wp->routine_3 & 7] >> 2, &wp->matrix.m);
                RotMatrixY(wp->routine_3 << 6, &wp->matrix.m);
                wp->routine_3 = (wp->routine_3 + 1) & 0x3F;
            }
            else if (wp->routine_2 == 2)
            {
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->u_C.b.hi == 1 && wp->value_E != -1)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->value_E);
            }
            wp->routine_2++;
            break;
        case 4:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_1 = 0;
                wp->routine_2 = 0;
                wp->value_48  = 0;
            }
            break;
    }
}

void func_8010967C(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031734();
    if (ep != NULL)
    {
        ep->be_flag   = wp->be_flag;
        ep->type      = 2;
        ep->id        = wp->id;
        ep->pos_38    = wp->pos_38;
        ep->pos_38.y  = wp->pos_38.y - 0x50;
        ep->routine_1 = 0;
        ep->routine_3 = 0;
        ep->value_44  = (sint32)wp;
        Model_work_init(ep, &ep->type);
        wp->type = 1;
        Model_work_init(wp, &wp->type);
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

void func_80109754(STAGE_OBJ50 *wp)
{
    STAGE_MATRIX_IDENTITY(wp->matrix.words);
    RotMatrixZ((sint16)D_80111CB4[wp->routine_3 & 7] >> 2, &wp->matrix.m);
    RotMatrixY(wp->routine_3 << 6, &wp->matrix.m);
}

// The lid: rises, then falls back onto its chest.
void func_801097E0(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *chest;
    sint16 top;

    chest = (STAGE_OBJ50 *)wp->value_44;
    switch (wp->routine_1)
    {
        case 0:
            wp->value_4C  = 0x200000;
            wp->routine_1 = 1;
            wp->value_48  = wp->pos_38.y << 16;
            // fall through
        case 1:
            if (chest->u_C.b.hi == 1 && chest->value_E == 0x10)
            {
                func_80109A60(chest);
            }
            wp->routine_1++;
            // fall through
        case 2:
            top = chest->pos_38.y - 0x50;
            wp->value_48 -= wp->value_4C;
            wp->value_4C -= 0x40000;
            wp->pos_38.y = ST04_OBJ50_Y(wp);
            if (top < wp->pos_38.y)
            {
                chest->type      = 0;
                chest->routine_0 = 1;
                chest->routine_1 = 0;
                chest->value_48  = 0;
                chest->value_4C  = 0;
                Model_work_init(chest, &chest->type);
                STAGE_MATRIX_IDENTITY(chest->matrix.words);
                RotMatrixX(0, &chest->matrix.m);
                RotMatrixY(chest->routine_3 << 6, &chest->matrix.m);
                RotMatrixZ(0, &chest->matrix.m);
                func_80031A4C(wp);
            }
            else
            {
                STAGE_MATRIX_IDENTITY(wp->matrix.words);
                RotMatrixZ((sint16)D_80111CB4[chest->routine_3 & 7], &wp->matrix.m);
                RotMatrixY(wp->value_F << 6, &wp->matrix.m);
                chest->routine_3++;
            }
            break;
    }
}

uint8 func_801099D8(STAGE_OBJ50 *wp)
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

// Three creatures jump out of the chest.
void func_80109A60(STAGE_OBJ50 *wp)
{
    STAGE_OBJ *obj;
    uint8 i;

    for (i = 0; i < 3; i++)
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            obj->be_flag            = 1;
            obj->id                 = 0x10;
            obj->value_4            = 1;
            obj->position           = wp->pos_38;
            obj->rotation.y         = i * 0x600;
            obj->position_fixed.v.x = obj->position.x << 16;
            obj->position_fixed.v.y = obj->position.y << 16;
            obj->position_fixed.v.z = obj->position.z << 16;
        }
    }
}

void func_80109B28(STAGE_OBJ50 *wp)
{
    STCOM_SVECTOR pos;

    func_80051B68(wp, 7, 0, 0);
    D_80111CC4[wp->routine_0](wp);
    pos = wp->pos_38;
    pos.y -= 0x2D;
    func_800341BC(&pos, 0x32, 0, 0x8000, wp->slot, &wp->value_48, 0x4000000, 0, 0x80);
    wp->value_48 = 0;
}

void func_80109BE8(STAGE_OBJ50 *wp)
{
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 0x10 extra bytes
    sint32 flag;

    wp->be_flag |= 6;
    flag           = wp->pos_38.pad;
    wp->pos_38.pad = 0;
    wp->value_44   = flag;
    Model_work_init(wp, &wp->type);
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
    wp->model_10 = D_80111CD4;
    wp->value_48 = 0;
    wp->value_4C = 0;
    wp->routine_0++;
}

void func_80109C8C(STAGE_OBJ50 *wp)
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

void func_80109CCC(STAGE_OBJ50 *wp)
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
            if (!func_80109F34(wp))
            {
                func_8005C150(1, 2, 0, 0);
            }
            else if (wp->u_C.b.hi == 0)
            {
                func_80063BC8(&wp->pos_38, 2, 0, wp->value_E);
            }
            else if (wp->u_C.b.hi != 1)
            {
                if (wp->u_C.b.hi & 0x80)
                {
                    zenny = (((wp->u_C.b.hi & 0x7F) << 8) | (uint8)wp->value_E) * 10;
                    func_8005C150(1, 1, zenny / 10, 0);
                    Sce_flag_on(wp->u_C.b.lo + 0x400);
                }
                else if (wp->value_E != -1)
                {
                    func_8005C150(1, 0, (uint8)wp->value_E, 0);
                    Sce_flag_on(wp->u_C.b.lo + 0x400);
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
                pl->be_flag |= 2;
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_80109EB8(STAGE_OBJ50 *wp)
{
    STAGE_OBJ50 *ep;

    ep = (STAGE_OBJ50 *)func_80031618();
    if (ep != NULL)
    {
        ep->be_flag  = 5;
        ep->id       = 0x80;
        ep->type     = 0x41;
        ep->pos_38   = wp->pos_38;
        ep->pos_38.y = wp->pos_38.y - 0x28;
        func_80031A4C(wp);
    }
}

// Whether the box still has something to give.
uint8 func_80109F34(STAGE_OBJ50 *wp)
{
    if ((wp->value_44 == 0 || Sce_flag_test(wp->value_44)) && !Sce_flag_test(wp->u_C.b.lo + 0x400) && wp->value_E != -1)
    {
        return 1;
    }
    return 0;
}

void func_80109FA0(STAGE_WORK *wp)
{
    D_80111D14[wp->routine_0](wp);
}

void func_80109FDC(STAGE_OBJ *wp)
{
    wp->routine_0 = 1;
}

void func_80109FE8(STAGE_OBJ50 *wp)
{
    if (D_800987B0[0] != 0 && D_800987B5 < 0x10 && (wp->u_C.b.lo = D_80111CE0[D_800987B5]) != 0)
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
        wp->value_F   = 0;
    }
}

void func_8010A044(STAGE_OBJ50 *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 1:
            pl->value_448 = 0x30;
            wp->routine_1++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                if (Moji_flag & 0xFF)
                {
                    wp->routine_1 = 10;
                }
                else
                {
                    Sound_fade_start(0x10);
                    wp->routine_1++;
                }
            }
            break;
        case 3:
            if (Sound_fade_flags == 0)
            {
                MojiTaskExec2(0, 0xB);
                Sound_work.volume_6 = D_80111D0C[wp->u_C.b.lo];
                Cd_xa_play_id(D_80111CF0[wp->u_C.b.lo]);
                wp->routine_1++;
            }
            break;
        case 4:
            if (func_8001D878())
            {
                wp->routine_1++;
            }
            break;
        case 5:
            if (D_800C0C26 != 0 || !(Moji_flag & 0x8000000) || !func_8001D878())
            {
                pl->value_448 = 0x31;
                func_80053AA4(0);
                Sound_fade_start(0x40);
                wp->routine_1++;
            }
            break;
        case 6:
            if (Sound_fade_flags == 0)
            {
                Sound_work.volume_6 = 0x7F;
                wp->routine_1++;
            }
            break;
        case 7:
            Sound_fade_start(0x20);
            wp->routine_1 = 10;
            break;
        case 10:
            if (!func_8003A13C())
            {
                func_80042314(&Player_work);
                pl->target_184 = NULL;
                pl->be_flag |= 2;
                wp->routine_0 = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_8010A248(STAGE_WORK *wp)
{
    D_80111D20[wp->routine_0](wp);
}

void func_8010A284(ST04_EV *wp)
{
    ST04_SLOT *slot;

    slot = Scene_obj_ent_open(D_80111D2C);
    slot->flags &= ~0x20;
    wp->slot_1C   = slot;
    wp->routine_0 = 1;
}

void func_8010A2D4(ST04_EV *wp)
{
    if (wp->slot_1C->routine_2 == 0 && func_8010A484(wp->slot_1C))
    {
        wp->routine_0 = 2;
        wp->routine_1 = 0;
    }
}

void func_8010A32C(ST04_EV *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_1)
    {
        case 0:
            if (!(Moji_flag & 0x0F800000))
            {
                wp->routine_1++;
            }
            break;
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_1++;
            }
            break;
        case 2:
            pl->value_448 = 0x30;
            wp->routine_1++;
            break;
        case 3:
            pl->value_448 = 0x35;
            MojiTaskExec2(0, 0xD2);
            wp->routine_1++;
            break;
        case 4:
            if (pl->flags_A7 < 0 && !(Moji_flag & 0x08000000))
            {
                MojiTaskExec2(0, 0xD3);
                wp->routine_1++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                wp->routine_1++;
            }
            break;
        case 6:
            if (!func_8003A13C())
            {
                func_80042314(pl);
                pl->be_flag |= 2;
                func_8001E3F0(0x1A);
                wp->routine_1++;
            }
            break;
        case 7:
        case 8:
            break;
    }
}

uint8 func_8010A484(ST04_SLOT *slot)
{
    if ((D_80111D40.x >= slot->position.x && slot->position.x >= D_80111D48.x) &&
        (D_80111D40.y >= slot->position.y && slot->position.y >= D_80111D48.y) &&
        (D_80111D40.z >= slot->position.z && slot->position.z >= D_80111D48.z))
    {
        return 1;
    }
    return 0;
}
