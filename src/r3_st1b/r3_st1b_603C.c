#include "common.h"
#include "st1b.h"

#ifdef __wasm32__
void Sce_flag_off(sint32 flag);
#endif

void func_8010603C(STAGE_WORK *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    func_800322A8(wp, 0, 0);
    wp->routine_0++;
}

void func_801060AC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 1, 0);
        wp->routine_2++;
    }
}

void func_801060F8(STAGE_OBJ *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->routine_2;
    switch (temp_v1)
    {
        case 0:
            func_800322A8(wp, 8, 0);
            wp->routine_2++;
            return;
        case 1:
            if (*wp->anim_98 == 0x12)
            {
                wp->routine_2 = 0;
            }
            return;
    }
}

void func_8010617C(STAGE_OBJ *wp)
{
    D_8010E71C[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_801061E4(STAGE_WORK *wp)
{
    if (wp->routine_0 == 0)
    {
        func_8010603C(wp);
    }
    func_8010617C(wp);
}

void func_80106228(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_80106284(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x15, 0);
        wp->routine_2++;
    }
}

void func_801062D0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_8010631C(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x17, 0);
        wp->routine_2++;
    }
}

void func_80106368(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x18, 0);
        wp->routine_2++;
    }
}

void func_801063B4(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x19, 0);
        wp->routine_2++;
    }
}

void func_80106400(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x1DU, 0);
        wp->routine_2++;
    }
}

void func_8010644C(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x1A, 0);
        wp->routine_2++;
    }
}

void func_80106498(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x1BU, 0);
        wp->routine_2++;
    }
}

void func_801064E4(ST1B_VIEW *wp)
{
    D_8010E768[wp->routine_1](wp);
    if (wp->u_C.b[1] == 0)
    {
        func_80030150(&wp->position_fixed, &wp->position);
        func_80032488(wp);
    }
    if (wp->u_C.b[0] != 0)
    {
        wp->u_C.b[3] = (wp->u_C.b[3] + 1) & 0x1F;
        wp->value_FC = D_8010E724[wp->u_C.b[2]][wp->u_C.b[3]];
    }
    else
    {
        wp->value_FC = D_8010E764[wp->u_C.b[2]];
    }
}

void func_801065AC(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80106228(wp);
    }
    func_801064E4(wp);
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}

void func_80106604(ST1B_VIEW *wp)
{
    uint8 temp_v0;

    wp->position_prev           = wp->position;
    wp->position_fixed_prev.x   = wp->position_fixed.x;
    wp->position_fixed_prev.y   = wp->position_fixed.y;
    wp->position_fixed_prev.z   = wp->position_fixed.z;
    wp->position_fixed_prev.pad = wp->position_fixed.pad;
    wp->rotation_prev           = wp->rotation;
    D_8010E788[wp->routine_0](wp);
    if ((uint8)wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    temp_v0 = wp->routine_1;
    if (temp_v0 != 0)
    {
        func_80032488(wp);
        return;
    }
    wp->routine_1 = temp_v0 + 1;
}

void func_801066F4(ST1B_ACTOR *wp)
{
    sint32 y;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->flags_0 |= 2;
    wp->turn_64 = STCOM_ABS((sint16)Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x800)) >> 3;
    Model_work_init(wp, NULL);
    wp->scale.words[0]   = 0x02000200;
    wp->scale.words[1]   = 0x200;
    wp->scale.v.pad      = 0x4210;
    wp->value_78         = 0;
    y                    = func_80048E6C(wp);
    wp->position.y       = y;
    wp->position_fixed.y = y << 16;
    wp->value_6E         = 0;
    wp->value_B0         = 0;
    wp->value_B2         = 0;
    func_800322A8(wp, 0, 0);
    wp->routine_0 = 1;
    wp->routine_1 = 0;
}

void func_80106810(ST1B_ACTOR *wp)
{
    STCOM_FIXED_VECTOR cam;
    STAGE_PL_VIEW *pl;
    sint16 step;
    sint16 pl_step;
    pl = &STAGE_PL;
    switch (wp->routine_2)
    {
        case 0:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->value_C   = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                pl->value_448 = 0x30;
                cam.x         = wp->value_180.x;
                cam.y         = wp->value_180.y - 0x20;
                cam.z         = wp->value_180.z;
                func_80039FAC(&cam, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
                pl->flags_0 &= ~2;
                wp->routine_2++;
            }
            break;
        case 2:
            step           = Muku(&wp->position, &pl->position, wp->rotation.y, wp->turn_64);
            pl_step        = Muku(&pl->position, &wp->position, pl->rotation.y, wp->turn_64);
            wp->rotation.y = (wp->rotation.y + step) & 0xFFF;
            pl->value_442  = (pl->value_442 + pl_step) & 0xFFF;
            if (step + pl_step == 0 && !func_8003A13C())
            {
                MojiTaskExec2(0, 0x35);
                func_800322A8(wp, 8, 0);
                wp->routine_1 = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_80039E18();
                wp->routine_2++;
            }
            break;
        case 4:
            if (!func_8003A13C())
            {
                func_80042314(pl);
                pl->flags_0 |= 2;
                wp->routine_0 = wp->routine_1 = wp->routine_2 = wp->routine_3 = 0;
                wp->value_D = wp->value_E = wp->value_F = wp->timer_C = 0;
                wp->value_4                                           = 1;
            }
            break;
    }
}

void func_80106A34(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80106A54(STAGE_OBJ *wp)
{
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x42100200;
    wp->routine_0++;
}

void func_80106AB0(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x14, 0);
        wp->routine_2++;
    }
}

void func_80106AFC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x15, 0);
        wp->routine_2++;
    }
}

void func_80106B48(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x16, 0);
        wp->routine_2++;
    }
}

void func_80106B94(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x17, 0);
        wp->routine_2++;
    }
}

void func_80106BE0(STAGE_WORK *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x1A, 0);
        wp->routine_2++;
    }
}

void func_80106C2C(STAGE_WORK *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            func_800322A8(wp, 0x18, 0);
            wp->routine_2++;
            break;
        case 1:
            if (*wp->anim_98 > 0x30)
            {
                Obj_pos_set(wp, -0x40, 0, 0);
            }
            if (*wp->anim_98 == 0x45)
            {
                func_800322A8(wp, 0x19, 0);
                wp->routine_2++;
            }
            break;
        case 2:
            Obj_pos_set(wp, -0x40, 0, 0);
            break;
    }
}

void func_80106D08(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        func_800322A8(wp, 0x19, 0);
        wp->routine_2++;
    }
}

void func_80106D54(STAGE_OBJ *wp)
{
    D_8010E794[wp->routine_1](wp);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80030150(&wp->position_fixed.v, &wp->position);
        func_80032488(wp);
    }
}

void func_80106DBC(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        func_80106A54(wp);
    }
    func_80106D54(wp);
    Model_Shadow_Trans(wp, 0x32, 0x2AB, 0);
}

void func_80106E14(STAGE_ACTOR *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8010E7B0[wp->routine_0](wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if (wp->routine_2 != 0)
    {
        func_80032488(wp);
    }
    else
    {
        wp->routine_2++;
    }
}

void func_80106F04(ST1B_ACTOR *wp)
{
    STAGE_PL_VIEW *pl;
    pl = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            func_8010706C(wp);
            wp->routine_1++;
            break;
        case 1:
            if (func_80107114(wp) == 0)
            {
                break;
            }
            wp->routine_1++;
            break;
        case 2:
            if (func_8003A13C() != 0)
            {
                break;
            }
            func_80063BC8(&wp->position, 5, 0, wp->timer_C);
            wp->routine_1++;
            break;
        case 3:
            if (Moji_flag & 0x8000000)
            {
                break;
            }
            func_80039E18();
            wp->routine_1++;
            break;
        case 4:
            if (func_8003A13C() != 0)
            {
                break;
            }
            if (*(uint8 *)&Moji_flag == 0)
            {
                wp->routine_1++;
                D_800989F8.routine_4 = 0;
                Sce_flag_off(0x1FF);
            }
            else
            {
                pl->flags_bd &= ~0x40;
                wp->routine_1 = 0;
            }
            pl->flags_0 |= 2;
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010706C(ST1B_VIEW *wp)
{
    sint16 temp_v0;

    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->value_64   = 0x80;
    wp->flags_0 |= 2;
    Model_work_init(wp, NULL);
    wp->value_158        = 0x02000200;
    wp->u_15C.w[0]       = 0x200;
    wp->u_15C.h[1]       = 0x4210;
    wp->value_78         = 0;
    temp_v0              = func_80048E6C(wp);
    wp->position.y       = temp_v0;
    wp->position_fixed.y = temp_v0 << 0x10;
    wp->value_6E         = 0;
    wp->vec_AC.z         = 0;
    wp->vec_AC.pad       = 0;
    wp->value_10         = (sint32)D_8010E7B4;
    func_800322A8(wp, 3, 0);
    wp->routine_2 = 0;
}

sint32 func_80107114(ST1B_ACTOR *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    if (Player_work.target_184 == wp)
    {
        if ((sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) < 0)
        {
            wp->turn_64 = (uint32) - (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        else
        {
            wp->turn_64 = (sint16)Muku(&wp->position, &pl->position, wp->rotation.y, 0x800) >> 3;
        }
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x40;
        D_80113E74.x = wp->value_180.x;
        D_80113E74.y = wp->value_180.y - 0x20;
        D_80113E74.z = wp->value_180.z;
        func_80039FAC(&D_80113E74, 0x100, Angle_xz_svector(&pl->position, &wp->position) + 0x800, D_800A396C);
        return 1;
    }
    return 0;
}
