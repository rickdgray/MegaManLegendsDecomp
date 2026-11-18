#include "common.h"
#include "stage_common/stcom21.h"

// Shared stage code, linked into 4 stages: r3_st05, r3_st08, r3_st10 and r3_st19. Each stage
// compiles this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the
// names are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom21"

// The villager.
void stcom21_func_0000(STCOM21_WORK *wp)
{
    STCOM_SVECTOR pos;

    func_80051B68(wp, 7, 0, 0);
    stcom21_D_0000[wp->routine_0](wp);
    pos = wp->pos_38;
    pos.y -= 0x50;
    func_800341BC(&pos, 0x64, 0, 0x8000, wp->index_1, &wp->y_48, 0x4000000, 0, 0x80);
    wp->y_48.value = 0;
}

void stcom21_func_00C0(STCOM21_WORK *wp)
{
    // Never used; it reserves retail's frame.
    STCOM_FIXED_VECTOR unused;
    sint32 flag;

    wp->flags_0 |= 6;
    func_8002F9C4(wp, &wp->variant_3);
    STCOM21_IDENTITY(&wp->matrix);
    RotMatrixY((wp->variant_3 & 3) << 10, &wp->matrix.m);
    wp->color_40   = 0x808080;
    wp->model_10   = stcom21_D_001C;
    wp->y_48.value = 0;
    wp->speed_4C   = 0;
    wp->routine_1  = 0;
    wp->routine_2  = 0;
    wp->value_C    = 0;
    wp->value_F    = 0x28;
    wp->routine_0++;
    if (STCOM_STAGE_ROOM == 0x105)
    {
        flag = wp->value_D * 4 + 0x681;
        if (Sce_flag_test(flag))
        {
            func_80031A4C(wp);
        }
        else if (Sce_flag_test(flag + 1))
        {
            wp->value_C |= 2;
            wp->variant_3 += 4;
            func_8002F9C4(wp, &wp->variant_3);
        }
        else if (Sce_flag_test(flag + 2))
        {
            wp->value_C |= 1;
        }
    }
}

void stcom21_func_021C(STCOM21_WORK *wp)
{
    if (stcom21_func_0CE8(wp, &Player_work))
    {
        if (stcom21_func_0D34(wp))
        {
            wp->routine_0++;
        }
        if (wp->y_48.value & 0x20000000)
        {
            wp->routine_1 = 3;
            wp->routine_2 = 0;
            wp->routine_0++;
        }
    }
    if (wp->y_48.value < 0)
    {
        wp->routine_1 = 3;
        wp->routine_2 = 0x1E;
        wp->value_C |= 8;
        wp->routine_0++;
    }
}

void stcom21_func_02D4(STCOM21_WORK *wp)
{
    stcom21_D_000C[wp->routine_1](wp);
}

void stcom21_func_0310(STCOM21_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            Player_work.routine_1 = 0x10;
            Player_work.value_0a  = 0;
            wp->routine_2++;
            break;
        case 1:
            MojiTaskExec(0, D_8008CACC[wp->value_B], -1);
            wp->routine_2++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_2++;
            }
            break;
        case 3:
            if (func_8003A13C() == 0)
            {
                Player_work.target_184 = NULL;
                Player_work.routine_1  = 0;
                Player_work.value_0a   = 0;
                wp->routine_0          = 1;
                wp->routine_1          = 0;
                wp->routine_2          = 0;
            }
            break;
    }
    if (pl->routine_1 == 0xB || pl->routine_1 == 0xC)
    {
        MojiTaskKill();
        pl->target_184 = NULL;
        wp->routine_0  = 1;
        wp->routine_1  = 0;
        wp->routine_2  = 0;
    }
}

void stcom21_func_0460(STCOM21_WORK *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            pl->routine_1 = 0x10;
            pl->value_0a  = 0;
            wp->routine_2++;
            break;
        case 1:
            MojiTaskExec(0, D_8008CACC[wp->value_B], -1);
            wp->routine_2++;
            break;
        case 2:
            if (!(Moji_flag & 0x8000000))
            {
                if ((uint8)Moji_flag == 0)
                {
                    wp->routine_2++;
                }
                else
                {
                    wp->routine_2 = 0x14;
                }
            }
            break;
        case 3:
            if (func_8004327C(-10) < 0)
            {
                MojiTaskExec(0, D_8008CE08, -1);
                wp->routine_2 = 0x14;
            }
            else
            {
                func_80043294(-10, 0, 0);
                wp->value_E = 0x10;
                wp->routine_2++;
            }
            break;
        case 4:
            pl->routine_1 = 0x11;
            pl->value_0a  = 0;
            wp->routine_2++;
            break;
        case 5:
            if (STCOM21_PL_A7(pl) < 0)
            {
                wp->value_E = 0x10;
                wp->routine_2++;
            }
            break;
        case 6:
            if (wp->value_E != 0)
            {
                wp->value_E--;
            }
            else
            {
                Sound_call2(0x13E, &wp->pos_38);
                wp->value_E = 0x10;
                wp->routine_2++;
            }
            break;
        case 7:
            if (wp->value_E != 0)
            {
                wp->value_E--;
            }
            else
            {
                MojiTaskExec(0, D_8008CE00, -1);
                wp->routine_2++;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                pl->routine_1 = 0x14;
                pl->value_0a  = 0;
                MojiTaskExec(0, D_8008CE04, -1);
                Sound_call2(0x13F, &wp->pos_38);
                func_80043340(pl->value_B0, 0);
                wp->value_C |= 1;
                stcom21_func_0E48(wp->value_D, 2);
                wp->routine_2++;
            }
            break;
        case 9:
            if (STCOM21_PL_A7(pl) < 0)
            {
                wp->routine_2++;
            }
            break;
        case 10:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec(0, D_8008CE3C, -1);
                pl->routine_1 = 0x13;
                pl->value_0a  = 0;
                wp->routine_2++;
            }
            break;
        case 11:
            if (!(Moji_flag & 0x8000000) && STCOM21_PL_A7(pl) < 0)
            {
                wp->routine_2 = 0x14;
            }
            break;
        case 20:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_2++;
            }
            break;
        case 21:
            if (func_8003A13C() == 0)
            {
                pl->routine_1  = 0;
                pl->value_0a   = 0;
                pl->target_184 = NULL;
                wp->routine_0  = 1;
                wp->routine_1  = 0;
                wp->routine_2  = 0;
            }
            break;
    }
    if (pl->routine_1 == 0xB || pl->routine_1 == 0xC)
    {
        MojiTaskKill();
        pl->target_184 = NULL;
        wp->routine_0  = 1;
        wp->routine_1  = 0;
        wp->routine_2  = 0;
    }
}

void stcom21_func_0768(STCOM21_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_EFFECT *effect;

    pl = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            pl->flags_bd |= 0x40;
            if (func_8004324C(pl) == 0)
            {
                pl->routine_1 = 0x10;
                pl->value_0a  = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (wp->value_C & 2)
            {
                wp->routine_2 = 0x1E;
            }
            else if (rand() & 1)
            {
                stcom21_func_0E48(wp->value_D, 1);
                wp->routine_2 = 0x14;
                wp->value_C |= 2;
            }
            else
            {
                wp->value_E   = 0x10;
                wp->routine_2 = 10;
            }
            break;
        case 10:
            if (wp->value_E != 0)
            {
                wp->value_E--;
            }
            else
            {
                Sound_call2(0x13E, &wp->pos_38);
                wp->value_E = 0x10;
                wp->routine_2++;
            }
            break;
        case 11:
            if (wp->value_E != 0)
            {
                wp->value_E--;
            }
            else
            {
                MojiTaskExec(0, D_8008CE00, -1);
                wp->routine_2++;
            }
            break;
        case 12:
            if (!(Moji_flag & 0x8000000))
            {
                pl->routine_1 = 0x14;
                pl->value_0a  = 0;
                MojiTaskExec(0, D_8008CE04, -1);
                Sound_call2(0x13F, &wp->pos_38);
                func_80043340(pl->value_B0, 0);
                wp->routine_2++;
            }
            break;
        case 13:
            if (STCOM21_PL_A7(pl) < 0)
            {
                wp->routine_2++;
            }
            break;
        case 14:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001E3F0(0);
                wp->routine_2++;
            }
            break;
        case 15:
            if (!(Moji_flag & 0x8000000))
            {
                MojiTaskExec(0, D_8008CE3C, -1);
                pl->routine_1 = 0x13;
                pl->value_0a  = 0;
                wp->routine_2++;
            }
            break;
        case 16:
            if (!(Moji_flag & 0x8000000) && STCOM21_PL_A7(pl) < 0)
            {
                pl->routine_1 = 0x10;
                pl->value_0a  = 0;
                wp->routine_2++;
            }
            break;
        case 17:
            if (!(Moji_flag & 0x8000000) && STCOM21_PL_A7(pl) < 0)
            {
                wp->routine_2 = 0x28;
            }
            break;
        case 20:
            wp->variant_3 += 4;
            func_8002F9C4(wp, &wp->variant_3);
            STCOM21_IDENTITY(&wp->matrix);
            RotMatrixY((wp->variant_3 & 3) << 10, &wp->matrix.m);
            wp->value_B = 0;
            wp->routine_2++;
            Sound_call2(0xA4, &wp->pos_38);
            break;
        case 21:
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0         = 1;
                effect->kind_2          = 0xB;
                effect->variant_3       = 3;
                effect->timer_E         = 0x14;
                effect->value_C         = 0;
                effect->value_D         = 0;
                effect->value_F         = 8;
                effect->sprite.pos_8[0] = wp->pos_38.x + stcom21_D_0028[wp->variant_3 & 3].x;
                effect->sprite.pos_8[1] = wp->pos_38.y - 0xC8;
                effect->sprite.pos_8[2] = wp->pos_38.z;
                effect->routine_1       = 4;
                wp->value_E             = 2;
                wp->routine_2++;
            }
            break;
        case 22:
            if (wp->value_E != 0)
            {
                wp->value_E--;
            }
            else if (wp->value_B < 8)
            {
                wp->routine_2--;
                wp->value_B++;
            }
            else
            {
                wp->value_B = 0;
                wp->routine_2++;
            }
            break;
        case 23:
            MojiTaskExec(0, D_8008CE0C, -1);
            wp->routine_2++;
            break;
        case 24:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_2 = 0x28;
            }
            break;
        case 30:
            effect = func_80031618();
            if (effect != NULL)
            {
                effect->flags_0           = 5;
                effect->kind_2            = 0x80;
                effect->variant_3         = 0x41;
                effect->sprite.position   = wp->pos_38;
                effect->sprite.position.y = wp->pos_38.y - 0x64;
                wp->u_44.effect           = effect;
                wp->flags_0 &= ~2;
                if (!(wp->value_C & 8))
                {
                    stcom21_func_0D9C();
                }
                func_8001E3F0(1);
                wp->value_C |= 4;
                stcom21_func_0E48(wp->value_D, 0);
                wp->routine_2++;
            }
            break;
        case 31:
            effect = wp->u_44.effect;
            if ((sint8)effect->flags_0 == 0)
            {
                wp->routine_2 = 0x28;
            }
            break;
        case 40:
            if (func_8003A13C() == 0)
            {
                if (!(wp->value_C & 8))
                {
                    pl->routine_1  = 0x10;
                    pl->value_0a   = 2;
                    pl->target_184 = NULL;
                    pl->flags_bd &= ~0x40;
                }
                wp->routine_2++;
            }
            break;
        case 41:
            wp->routine_0 = 1;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            if (wp->value_C & 4)
            {
                func_80031A4C(wp);
            }
            break;
    }
    if (pl->routine_1 == 0xB || pl->routine_1 == 0xC)
    {
        MojiTaskKill();
        pl->target_184 = NULL;
        pl->flags_bd &= ~0x40;
        wp->routine_0 = 1;
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        if (wp->value_C & 4)
        {
            func_80031A4C(wp);
        }
    }
}

// Whether the player faces the villager from the front.
uint8 stcom21_func_0CE8(STCOM21_WORK *wp, STCOM_PL_WORK *pl)
{
    return func_80031EF0(&wp->pos_38, ((wp->variant_3 << 10) - 0x400) & 0xC00, 0x1FF, &pl->position,
                         pl->rotation.y, 0x1FF);
}

// Whether the player talks to the villager: picks the conversation.
sint32 stcom21_func_0D34(STCOM21_WORK *wp)
{
    sint32 message;

    if (Player_work.target_184 == wp)
    {
        if (wp->value_C & 2)
        {
            wp->routine_1 = 0;
            message       = 0xCB;
        }
        else if (wp->value_C & 1)
        {
            wp->routine_1 = 1;
            message       = 0xCA;
        }
        else
        {
            wp->routine_1 = 2;
            message       = 0xCC;
        }
        wp->value_B = message;
        return 1;
    }
    return 0;
}

// Steps the two-flag counter in scene flags 0x220 and 0x221.
void stcom21_func_0D9C(void)
{
    if (Sce_flag_test(0x220) && Sce_flag_test(0x221))
    {
        Sce_flag_off(0x220);
        Sce_flag_off(0x221);
        func_8001E390(0x2E0);
    }
    else if (!Sce_flag_test(0x220) && Sce_flag_test(0x221))
    {
        Sce_flag_on(0x220);
    }
    else if (Sce_flag_test(0x220) && !Sce_flag_test(0x221))
    {
        Sce_flag_off(0x220);
        Sce_flag_on(0x221);
    }
    else
    {
        Sce_flag_on(0x220);
    }
}

void stcom21_func_0E48(uint8 index, uint8 n)
{
    if (STCOM_STAGE_ROOM == 0x105)
    {
        Sce_flag_on(index * 4 + (0x681 + n));
    }
}

// The chest.
void stcom21_func_0E88(STCOM21_WORK *wp)
{
    stcom21_D_0038[wp->routine_0](wp);
}

void stcom21_func_0EC4(STCOM21_WORK *wp)
{
    // Never used; it reserves retail's frame.
    STCOM_FIXED_VECTOR unused;

    wp->flags_0 |= 6;
    if (wp->variant_3 == 0)
    {
        wp->u_44.flag  = wp->pos_38.pad;
        wp->pos_38.pad = 0;
    }
    func_8002F9C4(wp, &wp->variant_3);
    STCOM21_IDENTITY(&wp->matrix);
    RotMatrixY(wp->value_F << 6, &wp->matrix.m);
    wp->color_40   = 0x808080;
    wp->model_10   = stcom21_D_005C;
    wp->y_48.value = 0;
    wp->speed_4C   = 0;
    wp->routine_0++;
}

void stcom21_func_0F74(STCOM21_WORK *wp)
{
    STCOM_SVECTOR pos;

    stcom21_D_0044[wp->variant_3](wp);
    if (wp->variant_3 != 2)
    {
        func_80051B68(wp, 7, 0, 0);
        pos = wp->pos_38;
        pos.y -= 0x2D;
        func_800341BC(&pos, 0x28, 0, 0x8000, wp->index_1, &wp->y_48, 0x4000000, 0, 0x80);
        wp->y_48.value = 0;
    }
}

// Vanishes in a puff.
void stcom21_func_1044(STCOM21_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0           = 5;
        effect->kind_2            = 0x80;
        effect->variant_3         = 0x41;
        effect->sprite.position   = wp->pos_38;
        effect->sprite.position.y = wp->pos_38.y - 0x28;
        func_80031A4C(wp);
    }
}

void stcom21_func_10C0(STCOM21_WORK *wp)
{
    stcom21_D_0050[wp->routine_1](wp);
}

void stcom21_func_10FC(STCOM21_WORK *wp)
{
    if (Player_work.target_184 == wp)
    {
        wp->routine_1 = 1;
        wp->routine_2 = 0;
    }
    else if (wp->y_48.value & 0x20000000)
    {
        if (stcom21_func_1880(wp))
        {
            wp->routine_1 = 2;
        }
        else
        {
            stcom21_func_1524(wp);
            Sound_call2(0x13D, &wp->pos_38);
        }
    }
    else if (wp->y_48.value < 0)
    {
        wp->routine_1 = 0;
        wp->routine_0++;
    }
}

// Opened by talking to it: hands over the contents.
void stcom21_func_11A0(STCOM21_WORK *wp)
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
            if (!stcom21_func_1880(wp))
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

// Opened by a hit: the lid flies off.
void stcom21_func_1380(STCOM21_WORK *wp)
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
                STCOM21_IDENTITY(&wp->matrix);
                RotMatrixZ((sint16)stcom21_D_0068[wp->value_B & 7] >> 2, &wp->matrix.m);
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

// Spawns the lid (variant 2) and shows the chest open.
void stcom21_func_1524(STCOM21_WORK *wp)
{
    STCOM21_WORK *lid;

    lid = func_80031734();
    if (lid != NULL)
    {
        lid->flags_0    = wp->flags_0;
        lid->variant_3  = 2;
        lid->kind_2     = wp->kind_2;
        lid->pos_38     = wp->pos_38;
        lid->pos_38.y   = wp->pos_38.y - 0x50;
        lid->routine_1  = 0;
        lid->value_B    = 0;
        lid->u_44.chest = wp;
        func_8002F9C4(lid, &lid->variant_3);
        wp->variant_3 = 1;
        func_8002F9C4(wp, &wp->variant_3);
        STCOM21_IDENTITY(&wp->matrix);
        RotMatrixY(wp->value_F << 6, &wp->matrix.m);
        wp->routine_1 = 0;
    }
}

void stcom21_func_15FC(STCOM21_WORK *wp)
{
    STCOM21_IDENTITY(&wp->matrix);
    RotMatrixZ((sint16)stcom21_D_0068[wp->value_B & 7] >> 2, &wp->matrix.m);
    RotMatrixY(wp->value_B << 6, &wp->matrix.m);
}

// The lid: rises, then falls back onto its chest.
void stcom21_func_1688(STCOM21_WORK *wp)
{
    STCOM21_WORK *chest;
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
                stcom21_func_1908(chest);
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
                func_8002F9C4(chest, &chest->variant_3);
                STCOM21_IDENTITY(&chest->matrix);
                RotMatrixX(0, &chest->matrix.m);
                RotMatrixY(chest->value_B << 6, &chest->matrix.m);
                RotMatrixZ(0, &chest->matrix.m);
                func_80031A4C(wp);
            }
            else
            {
                STCOM21_IDENTITY(&wp->matrix);
                RotMatrixZ((sint16)stcom21_D_0068[chest->value_B & 7], &wp->matrix.m);
                RotMatrixY(wp->value_F << 6, &wp->matrix.m);
                chest->value_B++;
            }
            break;
    }
}

// Whether the chest still has something to give.
uint8 stcom21_func_1880(STCOM21_WORK *wp)
{
    sint32 flag;

    flag = wp->u_44.flag;
    if (wp->value_D == 1 && wp->value_E == 0x10)
    {
        return 0;
    }
    if ((flag == 0 || Sce_flag_test(flag)) && !Sce_flag_test(wp->value_C + 0x400) &&
        wp->value_E != -1)
    {
        return 1;
    }
    return 0;
}

// Three creatures jump out of the chest.
void stcom21_func_1908(STCOM21_WORK *wp)
{
    STCOM21_OBJ *obj;
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

// The box.
void stcom21_func_19D0(STCOM21_WORK *wp)
{
    STCOM_SVECTOR pos;

    func_80051B68(wp, 7, 0, 0);
    stcom21_D_0078[wp->routine_0](wp);
    pos = wp->pos_38;
    pos.y -= 0x2D;
    func_800341BC(&pos, 0x32, 0, 0x8000, wp->index_1, &wp->y_48, 0x4000000, 0, 0x80);
    wp->y_48.value = 0;
}

void stcom21_func_1A90(STCOM21_WORK *wp)
{
    // Never used; it reserves retail's frame.
    STCOM_FIXED_VECTOR unused;

    wp->flags_0 |= 6;
    wp->u_44.flag  = wp->pos_38.pad;
    wp->pos_38.pad = 0;
    func_8002F9C4(wp, &wp->variant_3);
    STCOM21_IDENTITY(&wp->matrix);
    RotMatrixY(wp->value_F << 10, &wp->matrix.m);
    wp->color_40   = 0x808080;
    wp->model_10   = stcom21_D_0088;
    wp->y_48.value = 0;
    wp->speed_4C   = 0;
    wp->routine_0++;
}

void stcom21_func_1B34(STCOM21_WORK *wp)
{
    if (Player_work.target_184 == wp)
    {
        wp->routine_0++;
    }
    if (wp->y_48.value < 0)
    {
        wp->routine_0 = 3;
    }
}

void stcom21_func_1B74(STCOM21_WORK *wp)
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
            if (!stcom21_func_1DDC(wp))
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

// Vanishes in a puff.
void stcom21_func_1D60(STCOM21_WORK *wp)
{
    STCOM_EFFECT *effect;

    effect = func_80031618();
    if (effect != NULL)
    {
        effect->flags_0           = 5;
        effect->kind_2            = 0x80;
        effect->variant_3         = 0x41;
        effect->sprite.position   = wp->pos_38;
        effect->sprite.position.y = wp->pos_38.y - 0x28;
        func_80031A4C(wp);
    }
}

// Whether the box still has something to give.
uint8 stcom21_func_1DDC(STCOM21_WORK *wp)
{
    if ((wp->u_44.flag == 0 || Sce_flag_test(wp->u_44.flag)) &&
        !Sce_flag_test(wp->value_C + 0x400) && wp->value_E != -1)
    {
        return 1;
    }
    return 0;
}
