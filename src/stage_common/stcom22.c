#include "common.h"
#include "stage_common/stcom22.h"

// Shared stage code, linked into 3 stages: r3_st0e, r3_st13 and r3_st14. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom22"

void stcom22_func_0000(STCOM22_WORK *wp)
{
    stcom22_D_0024[wp->type](wp);
}

// The lift.
void stcom22_func_003C(STCOM22_WORK *wp)
{
    stcom22_D_0044[wp->routine_0](wp);
}

void stcom22_func_0078(STCOM22_WORK *wp)
{
    STCOM22_PL_WORK *pl;
    STCOM22_CTL *ctl;
    sint32 height;
    sint16 y; // a narrower copy, set before each test
    sint16 *count;
    // Never used; it reserves retail's frame.
    STCOM_FIXED_VECTOR unused;
    STCOM_SVECTOR unused2;

    wp->be_flag |= 6;
    STCOM22_IDENTITY(&wp->matrix);
    wp->matrix.f.ctl.rot.x = 0;
    wp->matrix.f.ctl.rot.z = 0;
    wp->matrix.f.ctl.rot.y = wp->value_F << 4;
    RotMatrixYXZ(&wp->matrix.f.ctl.rot, &wp->matrix.m);
    pl  = STCOM22_PL;
    ctl = &wp->matrix.f.ctl;
    if (Game_work.value_50 == 0xE)
    {
        Model_work_init(wp, NULL);
    }
    else
    {
        Model_work_init(wp, (uint8 *)&wp->value_C);
    }
    wp->value_B = wp->value_D;
    if (Game_work.value_50 == 0xE || Game_work.value_50 == 0x14 || STCOM_STAGE_ROOM == 0x13)
    {
        wp->model_10 = stcom22_D_000C;
        if ((wp->value_5 & 0xF) != 0 || *(count = &STCOM22_GAME->value_194) != 0)
        {
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            if (Game_work.value_50 == 0xE)
            {
                wp->pos_38.y = -0x181;
            }
            else if (Game_work.value_50 == 0x14)
            {
                wp->pos_38.y = -1;
            }
            else if (Game_work.value_50 == 0x13)
            {
                wp->pos_38.y = -1;
            }
            wp->value_E = 8;
        }
        else
        {
            if (wp->pos_38.x == pl->position.x && wp->pos_38.z == pl->position.z)
            {
                pl->pos_438.x = pl->position.x = wp->pos_38.x;
                pl->pos_438.y = pl->position.y = wp->pos_38.y;
                pl->pos_438.z = pl->position.z = wp->pos_38.z;
                pl->fixed_428.x                = pl->pos_438.x << 16;
                pl->fixed_428.y                = pl->pos_438.y << 16;
                pl->fixed_428.z                = pl->pos_438.z << 16;
                pl->rot_440.y = pl->rotation.y = (ctl->rot.y + 0x800) & 0xFFF;
                if (func_80042238(pl) != 1 || pl->routine_0 == 3)
                {
                    return;
                }
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                pl->pos_438.x = pl->position.x = wp->pos_38.x;
                pl->pos_438.y = pl->position.y = wp->pos_38.y;
                pl->pos_438.z = pl->position.z = wp->pos_38.z;
                pl->fixed_428.x                = pl->pos_438.x << 16;
                pl->fixed_428.y                = pl->pos_438.y << 16;
                pl->fixed_428.z                = pl->pos_438.z << 16;
                pl->rot_440.x                  = 0;
                pl->rot_440.z                  = 0;
                pl->value_448                  = 0;
                pl->rot_440.y = pl->rotation.y = (ctl->rot.y + 0x800) & 0xFFF;
                wp->value_E                    = 8;
                wp->routine_1                  = 2;
                ctl->value                     = func_80048EA4(&wp->pos_38, stcom22_D_0000, 0, 0xFFFF);
                Sound_call2(0x176, &wp->pos_38);
                *count = 1;
            }
            else
            {
                wp->routine_1 = 0;
                wp->routine_2 = 0;
                if (Game_work.value_50 == 0xE)
                {
                    wp->pos_38.y = -0x181;
                }
                else if (Game_work.value_50 == 0x14)
                {
                    wp->pos_38.y = -1;
                }
                else if (Game_work.value_50 == 0x13)
                {
                    wp->pos_38.y = -1;
                }
                wp->value_E             = 8;
                STCOM22_GAME->value_194 = 1;
            }
        }
    }
    else
    {
        if (wp->value_F == 0)
        {
            wp->model_10 = stcom22_D_000C;
        }
        else
        {
            wp->model_10 = stcom22_D_0018;
        }
        wp->routine_1 = 0;
        wp->routine_2 = 0;
        if ((wp->value_5 & 0xF) == 2)
        {
            height = STCOM22_GAME->value_19A;
            y      = height;
            if (y != 0)
            {
                ctl->value   = wp->pos_38.y;
                wp->pos_38.y = y;
                wp->value_5  = 0x11;
            }
            else
            {
                ctl->value = wp->pos_38.y;
            }
        }
        else
        {
            ctl->value = wp->pos_38.y;
            if (wp->value_B == 0)
            {
                height = STCOM22_GAME->value_196;
            }
            else
            {
                height = STCOM22_GAME->value_198;
            }
            y = height;
            if (y != 0)
            {
                wp->pos_38.y = y;
                wp->value_5  = (wp->value_5 & 0xF0) | 2;
            }
        }
    }
    wp->routine_0 = 1;
    wp->color_40  = 0x2C808080;
    wp->value_D   = 0x78;
    stcom22_func_04B4(wp);
}

void stcom22_func_04B4(STCOM22_WORK *wp)
{
    stcom22_D_0050[wp->routine_1](wp);
    func_80051B68(wp, 5, -1, 0);
}

void stcom22_func_0510(STCOM22_WORK *wp)
{
    func_80031A4C(wp);
}

void stcom22_func_0530(STCOM22_WORK *wp)
{
    STCOM22_PL_WORK *pl;
    STCOM22_CTL *ctl;
    sint32 moji;

    pl  = STCOM22_PL;
    ctl = &wp->matrix.f.ctl;
    if (Game_work.value_50 == 0x13 && Sce_flag_test(0x64B))
    {
        return;
    }
    if (wp->routine_2 == 1 || !Sce_flag_test(0x49))
    {
        moji = Moji_flag;
    }
    else
    {
        moji = 0;
    }
    if (wp->routine_2 == 0)
    {
        if (pl->rotation.y > ((ctl->rot.y + 0x620) & 0xFFF) && pl->rotation.y < ((ctl->rot.y + 0x9E0) & 0xFFF) && pl->target_184 == wp)
        {
            wp->routine_2  = 1;
            pl->target_184 = NULL;
            pl->flags_bd |= 0x40;
            if (Game_work.value_50 == 0xE || Game_work.value_50 == 0x14)
            {
                MojiTaskExec2(0, 0x13);
            }
            else if (wp->value_5 == 0)
            {
                MojiTaskExec2(0, 0x17);
            }
            else if (!Sce_flag_test(0x49))
            {
                MojiTaskExec2(0, 6);
            }
        }
        return;
    }
    if (moji < 0)
    {
        return;
    }
    if ((moji & 0xFF) == 0)
    {
        if (func_80042238(pl) == 0)
        {
            return;
        }
        if (Game_work.value_50 == 0xE || Game_work.value_50 == 0x14 || STCOM_STAGE_ROOM == 0x13)
        {
            wp->routine_1 = 1;
            wp->value_D   = -0x61;
            wp->value_E *= -1;
            Sound_call2(0x178, &wp->pos_38);
            return;
        }
        if (Sce_flag_test(0x49))
        {
            if ((wp->value_5 & 0xF) == 2)
            {
                func_80042238(pl);
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_bd |= 0x10;
                pl->pos_438.x   = pl->position.x;
                pl->pos_438.y   = pl->position.y;
                pl->pos_438.z   = pl->position.z;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                pl->rot_440.x   = 0;
                pl->rot_440.y   = pl->rotation.y;
                pl->rot_440.z   = 0;
                pl->value_448   = 0;
                if (wp->value_5 & 0xF0)
                {
                    if (Sce_flag_test(0x6B))
                    {
                        wp->value_E   = 4;
                        wp->routine_1 = 2;
                        pl->rot_440.y = 0x7FF;
                        Sound_call2(0x176, &wp->pos_38);
                    }
                    else
                    {
                        wp->value_E = 0xC;
                        Sce_flag_on(0x6B);
                        MojiTaskExec2(0, 0x13);
                        wp->routine_1 = 5;
                        pl->rot_440.y = 0x7FF;
                    }
                }
                else
                {
                    wp->value_E   = 0xC;
                    wp->routine_1 = 2;
                    Sound_call2(0x176, &wp->pos_38);
                }
            }
            else
            {
                wp->value_E   = -0xC;
                wp->routine_1 = 1;
                Sound_call2(0x178, &wp->pos_38);
            }
            return;
        }
    }
    pl->flags_bd &= ~0x40;
    wp->routine_2 = 0;
}

void stcom22_func_0864(STCOM22_WORK *wp)
{
    sint32 diff;
    STCOM_PL_WORK *pl;

    pl = &Player_work;

    if (Game_work.value_50 == 0xE || Game_work.value_50 == 0x14 || STCOM_STAGE_ROOM == 0x13)
    {
        if (wp->value_D != 0x30)
        {
            wp->pos_38.y += wp->value_E;
            wp->value_D--;
        }
        else
        {
            Fade_start(10);
            wp->routine_1 = 3;
        }
        return;
    }
    wp->pos_38.y += wp->value_E;
    if ((wp->value_5 & 0xF0) == 0)
    {
        diff = wp->pos_38.y - wp->matrix.f.ctl.value;
        if (STCOM_ABS(diff) >= 0x2E0)
        {
            wp->pos_38.y  = wp->matrix.f.ctl.value - 0x2E0;
            wp->routine_1 = 0;
            pl->flags_bd &= ~0x40;
            wp->routine_2 = 0;
            Sound_call2(0x179, &wp->pos_38);
            wp->value_5 = (wp->value_5 & 0xF0) | 2;
            if (wp->value_B == 0)
            {
                STCOM22_GAME->value_196 = wp->pos_38.y;
            }
            else
            {
                STCOM22_GAME->value_198 = wp->pos_38.y;
            }
        }
    }
    else if (wp->pos_38.y <= wp->matrix.f.ctl.value)
    {
        wp->pos_38.y += (wp->pos_38.y - wp->matrix.f.ctl.value) + 0x10;
        wp->routine_1 = 0;
        pl->flags_bd &= ~0x40;
        wp->routine_2 = 0;
        Sound_call2(0x179, &wp->pos_38);
        wp->value_5             = (wp->value_5 & 0xF0) | 2;
        STCOM22_GAME->value_19A = 0;
    }
}

void stcom22_func_0A24(STCOM22_WORK *wp)
{
    STCOM22_PL_WORK *pl;
    STCOM22_CTL *ctl;
    sint32 diff;

    pl  = STCOM22_PL;
    ctl = &wp->matrix.f.ctl;
    if (Game_work.value_50 == 0xE || Game_work.value_50 == 0x14 || STCOM_STAGE_ROOM == 0x13)
    {
        wp->pos_38.y += wp->value_E;
        pl->pos_438.y += wp->value_E;
        pl->fixed_428.y = pl->pos_438.y << 16;
        if (wp->pos_38.y >= ctl->value)
        {
            func_80042314(pl);
            pl->flags_bd &= ~0x40;
            wp->pos_38.y  = ctl->value;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            Sound_call2(0x177, &wp->pos_38);
        }
    }
    else if ((wp->value_5 & 0xF0) == 0)
    {
        wp->pos_38.y += wp->value_E;
        STCOM22_PL->pos_438.y += wp->value_E;
        STCOM22_PL->fixed_428.y = STCOM22_PL->pos_438.y << 16;
        if (wp->pos_38.y >= wp->matrix.f.ctl.value)
        {
            func_80042314(pl);
            wp->routine_1 = 0;
            STCOM22_PL->flags_bd &= ~0x40;
            wp->routine_2 = 0;
            wp->value_5   = (wp->value_5 & 0xF0) | 1;
            Sound_call2(0x177, &wp->pos_38);
            if (wp->value_B == 0)
            {
                STCOM22_GAME->value_196 = 0;
            }
            else
            {
                STCOM22_GAME->value_198 = 0;
            }
        }
    }
    else
    {
        if (STCOM22_PL->rotation.y == 0x7FF)
        {
            wp->pos_38.y += wp->value_E;
            STCOM22_PL->pos_438.y += wp->value_E;
            STCOM22_PL->fixed_428.y = STCOM22_PL->pos_438.y << 16;
        }
        diff = wp->pos_38.y - wp->matrix.f.ctl.value;
        if (STCOM_ABS(diff) >= 0x460)
        {
            func_80042314(pl);
            wp->routine_1 = 0;
            STCOM22_PL->flags_bd &= ~0x40;
            wp->routine_2           = 0;
            STCOM22_GAME->value_19A = wp->pos_38.y;
            wp->value_5             = (wp->value_5 & 0xF0) | 1;
            Sound_call2(0x177, &wp->pos_38);
        }
    }
}

void stcom22_func_0CC8(STCOM22_WORK *wp)
{
    STCOM22_ENTRY *entry;

    entry      = &D_800C3558;
    D_800C356C = 1;
    Sound_call2(0x179, &wp->pos_38);
    if (Game_work.value_50 == 0xE)
    {
        D_800C356E = 0xC;
        D_800C3560 = 0xBEC;
        D_800C3562 = -1;
        D_800C356F = 0;
        D_800C3564 = 0x13FD;
        D_800C356A = 0;
    }
    else if (Game_work.value_50 == 0x14)
    {
        D_800C356E = 0xB;
        D_800C356F = 2;
        D_800C3560 = -0x200;
        D_800C3562 = -0x101;
        D_800C3564 = -0x271;
        D_800C356A = 0;
    }
    else if (STCOM22_GAME->value_7B != 0)
    {
        D_800C356E = 0x13;
        D_800C356F = 0xC;
        D_800C3562 = -1;
        D_800C3564 = -0x1C0;
        D_800C3560 = 0;
        D_800C356A = 0x800;
    }
    else
    {
        D_800C356E = 0xA;
        D_800C3560 = -0x1A00;
        D_800C3562 = -0x601;
        D_800C356F = 0;
        D_800C3564 = 0x17E0;
        D_800C356A = 0;
    }
    entry->fade_out = 0xFF;
    entry->flags15  = 0;
    entry->fade_in  = 2;
    wp->routine_1++;
}

void stcom22_func_0E50(STCOM22_WORK *wp)
{
    // Never used; it reserves retail's frame.
    sint32 unused;

    if (D_800C356C == 2 && D_80098A72 == 0)
    {
        D_800C356C++;
        func_80042314(&Player_work);
    }
}

void stcom22_func_0EA8(STCOM22_WORK *wp)
{
    if (!(Moji_flag & 0x8000000))
    {
        wp->value_E   = 4;
        wp->routine_1 = 2;
        Sound_call2(0x176, &wp->pos_38);
        MojiTaskExec2(0, 0x1B);
    }
}

// The crate.
void stcom22_func_0F00(STCOM22_WORK *wp)
{
    stcom22_D_0068[wp->routine_0](wp);
}

void stcom22_func_0F3C(STCOM22_WORK *wp)
{
    wp->be_flag |= 6;
    STCOM22_IDENTITY(&wp->matrix);
    wp->matrix.f.ctl.rot.x = 0;
    wp->matrix.f.ctl.rot.y = 0;
    wp->matrix.f.ctl.rot.z = 0;
    RotMatrixYXZ(&wp->matrix.f.ctl.rot, &wp->matrix.m);
    Model_work_init(wp, &wp->type);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->color_40  = 0x2C808080;
    stcom22_func_0FD4(wp);
}

void stcom22_func_0FD4(STCOM22_WORK *wp)
{
    stcom22_D_0074[wp->routine_1](wp);
}

void stcom22_func_1010(STCOM22_WORK *wp)
{
    func_80031A4C(wp);
}

void stcom22_func_1030(STCOM22_WORK *wp)
{
    if (Player_work.value_76 != 0 && Player_work.value_C0 == wp)
    {
        wp->routine_1 = 1;
        wp->type      = 2;
        Sound_call2(0x113, &wp->pos_38);
        Model_work_init(wp, &wp->type);
        wp->value_D = 0x1E;
    }
    func_80051B68(wp, 5, -1, 0);
}

void stcom22_func_10B8(STCOM22_WORK *wp)
{
    STCOM_SVECTOR pos;

    if (wp->value_D != 0)
    {
        wp->value_D--;
        func_80051B68(wp, 5, -1, 0);
        return;
    }
    pos = wp->pos_38;
    pos.y -= 0x301;
    pos.x -= 0x3E;
    pos.z -= 0x3E;
    func_8010D9F8(0, 4, 1, &pos);
    pos.x -= 0x3E;
    pos.z -= 0x3E;
    func_8010D9F8(0, 5, 1, &pos);
    pos.x -= 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x -= 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x = wp->pos_38.x;
    pos.z = wp->pos_38.z;
    pos.x += 0x3E;
    pos.z += 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x += 0x3E;
    pos.z += 0x3E;
    func_8010D9F8(0, 5, 1, &pos);
    pos.x += 0x3E;
    func_8010D9F8(0, 4, 1, &pos);
    pos.x += 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x = wp->pos_38.x;
    pos.z = wp->pos_38.z;
    pos.x -= 0x3E;
    pos.z += 0x3E;
    func_8010D9F8(0, 5, 1, &pos);
    pos.x -= 0x3E;
    pos.z += 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x -= 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x -= 0x3E;
    func_8010D9F8(0, 4, 1, &pos);
    pos.x = wp->pos_38.x;
    pos.z = wp->pos_38.z;
    pos.x += 0x3E;
    pos.z -= 0x3E;
    func_8010D9F8(0, 6, 1, &pos);
    pos.x += 0x3E;
    pos.z -= 0x3E;
    func_8010D9F8(0, 4, 1, &pos);
    pos.x += 0x3E;
    func_8010D9F8(0, 5, 1, &pos);
    pos.x += 0x3E;
    func_8010D9F8(0, 4, 1, &pos);
    func_80052528(wp);
    if (wp->value_5 != 0)
    {
        Sce_flag_on(0x60C);
    }
    wp->routine_0 = 2;
    Sound_call2(0x114, &wp->pos_38);
}

void stcom22_func_13F0(STCOM22_WORK *wp)
{
    stcom22_D_0068[wp->routine_0](wp);
}

void stcom22_func_142C(void)
{
}

// The lever.
void stcom22_func_1434(STCOM22_WORK *wp)
{
    STCOM_FIXED_VECTOR scale;

    stcom22_D_007C[wp->routine_0](wp);
    RotMatrixYXZ(&wp->matrix.f.ctl.rot, &wp->matrix.m);
    scale.x = 0x1000;
    scale.y = 0x1000;
    scale.z = 0x1000;
    ScaleMatrix(&wp->matrix.m, &scale);
}

void stcom22_func_14A8(STCOM22_WORK *wp)
{
    STCOM_SVECTOR pos;

    wp->be_flag |= 6;
    wp->matrix.f.ctl.rot.x = 0;
    wp->matrix.f.ctl.rot.y = 0;
    wp->matrix.f.ctl.rot.z = 0;
    Model_work_init(wp, &wp->type);
    wp->routine_0 = 1;
    wp->color_40  = 0x2C808080;
    wp->value_D   = 0x28;
    wp->routine_1 = 0;
    wp->value_E   = 0x78;
    if (wp->value_C == 0)
    {
        pos.x = -0x900;
        pos.y = -0x12B;
        pos.z = -0x2300;
        Stage_idx_model_set(Stage_map_cell_get(2, &pos), 0x61302);
    }
    else
    {
        pos.x = -0x1700;
        pos.y = -0x2AB;
        pos.z = -0x2300;
        Stage_idx_model_set(Stage_map_cell_get(2, &pos), 0x61402);
    }
}

void stcom22_func_1588(STCOM22_WORK *wp)
{
    stcom22_D_0088[wp->routine_1](wp);
}

void stcom22_func_15C4(STCOM22_WORK *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR pos;

    pl = &Player_work;
    if (Distance_xyz(&pl->position, &wp->pos_38) < 0x384)
    {
        fixed.x = wp->pos_38.x << 16;
        fixed.y = wp->pos_38.y << 16;
        fixed.z = wp->pos_38.z << 16;
        if (func_80031DCC(&fixed, wp->matrix.f.ctl.rot.y + 0x400, 0x100, &pl->position_fixed, Player_work.rotation.y, 0x800))
        {
            wp->routine_1 = 1;
            if (wp->value_C == 0)
            {
                pos.x = -0x900;
                pos.y = -0x12B;
                pos.z = -0x2300;
                Stage_idx_model_set(Stage_map_cell_get(2, &pos), 0x60302);
            }
            else
            {
                pos.x = -0x1700;
                pos.y = -0x2AB;
                pos.z = -0x2300;
                Stage_idx_model_set(Stage_map_cell_get(2, &pos), 0x60402);
            }
            Sound_call2(0x175, &wp->pos_38);
        }
    }
}

void stcom22_func_16F4(STCOM22_WORK *wp)
{
    wp->matrix.f.ctl.rot.z = (wp->matrix.f.ctl.rot.z - 0x50) & 0xFFF;
    if (wp->matrix.f.ctl.rot.z <= 0xC00)
    {
        wp->matrix.f.ctl.rot.z = 0xC00;
        wp->routine_1          = 2;
    }
}

void stcom22_func_1728(void)
{
}

void stcom22_func_1730(STCOM22_WORK *wp)
{
    func_80031A4C(wp);
}

void stcom22_func_1750(void)
{
}

// The gate.
void stcom22_func_1758(STCOM22_WORK *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;

    stcom22_D_0094[wp->routine_0](wp);
    rot.x = 0;
    rot.y = 0;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->matrix.m);
    scale.x = 0x1000;
    scale.y = wp->matrix.f.ctl.value;
    scale.z = 0x1000;
    ScaleMatrix(&wp->matrix.m, &scale);
}

void stcom22_func_17E0(STCOM22_WORK *wp)
{
    wp->be_flag |= 6;
    STCOM22_IDENTITY(&wp->matrix);
    Model_work_init(wp, &wp->type);
    wp->routine_0          = 1;
    wp->routine_1          = 0;
    wp->routine_2          = 0;
    wp->color_40           = 0x2C808080;
    wp->matrix.f.ctl.value = 0x1000;
}

void stcom22_func_1864(STCOM22_WORK *wp)
{
    STCOM_SVECTOR pos;
    sint32 *hit;

    hit = &wp->u_48.hit;
    if (wp->u_48.hit != 0)
    {
        wp->routine_1 = 1;
    }
    pos = wp->pos_38;
    pos.y -= 0x28;
    pos.z -= 0x80;
    func_800341BC(&pos, 0x3C, 0, 0xC000, wp->slot, hit, 0x4000000, 0, 0x80);
    stcom22_D_00A0[wp->routine_1](wp);
    wp->u_48.hit = 0;
}

void stcom22_func_1934(STCOM22_WORK *wp)
{
    func_80031A4C(wp);
}

void stcom22_func_1954(void)
{
}

void stcom22_func_195C(STCOM22_WORK *wp)
{
    STCOM22_CTL *ctl;

    ctl = &wp->matrix.f.ctl;
    if (wp->value_5 == 0)
    {
        if (!Sce_flag_test(0x605))
        {
            Sound_call2(0x11E, &wp->pos_38);
        }
        Sce_flag_on(0x605);
    }
    else if (wp->value_5 == 1)
    {
        if (!Sce_flag_test(0x606))
        {
            Sound_call2(0x11E, &wp->pos_38);
        }
        Sce_flag_on(0x606);
    }
    else if (wp->value_5 == 2)
    {
        if (!Sce_flag_test(0x604))
        {
            Sound_call2(0x11E, &wp->pos_38);
        }
        Sce_flag_on(0x604);
    }
    ctl->value    = 0x10;
    wp->routine_1 = 2;
    wp->value_B   = 0x80;
}

void stcom22_func_1A2C(STCOM22_WORK *wp)
{
    if (wp->value_B != 0)
    {
        wp->value_B--;
    }
    else
    {
        wp->matrix.f.ctl.value = 0x1000;
        wp->routine_1          = 0;
        if (wp->value_5 == 0)
        {
            Sce_flag_off(0x605);
        }
        else if (wp->value_5 == 1)
        {
            Sce_flag_off(0x606);
        }
        else if (wp->value_5 == 2)
        {
            Sce_flag_off(0x604);
        }
    }
}

// The gate's switch.
void stcom22_func_1A9C(STCOM22_WORK *wp)
{
    STCOM_SVECTOR rot;
    STCOM_FIXED_VECTOR scale;

    stcom22_D_00AC[wp->routine_0](wp);
    rot.x = 0;
    rot.y = 0x400;
    rot.z = 0;
    RotMatrixYXZ(&rot, &wp->matrix.m);
    scale.x = 0x1000;
    scale.y = wp->matrix.f.ctl.value;
    scale.z = 0x1000;
    ScaleMatrix(&wp->matrix.m, &scale);
}

void stcom22_func_1B28(STCOM22_WORK *wp)
{
    STCOM22_CTL *ctl;
    STCOM22_WORK *gate;

    wp->be_flag |= 6;
    STCOM22_IDENTITY(&wp->matrix);
    ctl = &wp->matrix.f.ctl;
    if (Game_work.value_50 == 0xE)
    {
        Model_work_init(wp, &wp->type);
    }
    else
    {
        Model_work_init(wp, (uint8 *)&wp->value_C);
    }
    wp->color_40  = 0x2E808080;
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    ctl->value    = 0x1000;
    gate          = func_80031734();
    if (gate != NULL)
    {
        gate->be_flag   = 1;
        gate->id        = 0x16;
        gate->type      = 0;
        gate->value_C   = 0;
        gate->value_D   = 0;
        gate->value_E   = 0;
        gate->value_F   = 0;
        gate->routine_0 = 0;
        gate->routine_1 = 0;
        gate->routine_2 = 0;
        if (Game_work.value_50 == 0xE)
        {
            gate->pos_38.x = 0x4FE;
            gate->pos_38.y = -0x256;
            gate->pos_38.z = 0xB00;
        }
        else
        {
            gate->pos_38.x = -0x100;
            gate->pos_38.y = -0xDC;
            gate->pos_38.z = 0x300;
        }
        wp->u_48.gate = gate;
    }
    stcom22_func_1C5C(wp);
}

void stcom22_func_1C5C(STCOM22_WORK *wp)
{
    STCOM_SVECTOR pos;
    STCOM_PL_WORK *pl;
    STCOM22_CTL *ctl;
    sint32 flag;

    pos = wp->pos_38;
    pos.y -= 0x96;
    func_800341BC(&pos, 0x96, 0, 0x8000, wp->slot, &wp->matrix.f.ctl.rot, 0x4000001, 0, 0x80);
    pl  = &Player_work;
    ctl = &wp->matrix.f.ctl;
    if (wp->routine_2 == 0 && Sce_flag_test(Game_work.value_50 == 0xE ? 0x608 : 0x605))
    {
        MojiTaskKill();
        MojiTaskExec2(0, 9);
        wp->routine_2 = 1;
        Player_work.flags_bd |= 0x40;
    }
    flag = Game_work.value_50 == 0xE ? 0x60B : 0x608;
    if (wp->routine_2 == 1 && (sint32)Moji_flag >= 0)
    {
        if (Sce_flag_test(flag))
        {
            if ((Moji_flag & 0xFF) == 0)
            {
                if (wp->value_B == 0)
                {
                    Sound_call2(0x17A, &wp->pos_38);
                    wp->value_B++;
                }
                if (ctl->value != 0)
                {
                    ctl->value -= 0x40;
                }
                else
                {
                    wp->routine_0 = 2;
                    pl->flags_bd &= ~0x40;
                    if (Game_work.value_50 == 0xE)
                    {
                        Sce_flag_on(0x1E);
                    }
                    else
                    {
                        Sce_flag_on(0x27);
                    }
                    wp->u_48.gate->routine_0 = 2;
                    Fade_start(8);
                }
            }
            else
            {
                pl->flags_bd &= ~0x40;
                wp->routine_2 = 0;
                if (Game_work.value_50 == 0xE)
                {
                    Sce_flag_off(0x608);
                }
                else if (Game_work.value_50 == 0x14)
                {
                    Sce_flag_off(0x605);
                }
            }
        }
        else
        {
            pl->flags_bd &= ~0x40;
            wp->routine_2 = 0;
            if (Game_work.value_50 == 0xE)
            {
                Sce_flag_off(0x608);
            }
            else if (Game_work.value_50 == 0x14)
            {
                Sce_flag_off(0x605);
            }
        }
    }
}

void stcom22_func_1ED0(STCOM22_WORK *wp)
{
    func_80031A4C(wp);
}
