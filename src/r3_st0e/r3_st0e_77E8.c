#include "common.h"
#include "st0e.h"

void func_801077E8(ST0E_VIEW *wp)
{
    wp->position_prev           = wp->position;
    wp->position_fixed_prev.x   = wp->position_fixed.x;
    wp->position_fixed_prev.y   = wp->position_fixed.y;
    wp->position_fixed_prev.z   = wp->position_fixed.z;
    wp->position_fixed_prev.pad = wp->position_fixed.pad;
    wp->rotation_prev           = wp->rotation;
    wp->u_C.b[1]                = (sint8)(uint8)wp->u_C.b[0];
    if (wp->rotation.x != wp->rotation_prev.x)
    {
        wp->u_C.b[0] = 1;
    }
    D_801104A4[wp->routine_0](wp);
}

void func_801078A8(ST0E_VIEW *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX *m;

    wp->vec_AC     = wp->position;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->u_64.w[0]  = 0;
    wp->u_70.w[0]  = 0;
    wp->u_74.w[0]  = 0;
    wp->flags_0 |= 6;
    func_8002F9C4(wp, NULL);
    m = &wp->matrix_8C;
    RotMatrixYXZ(&wp->rotation, m);
    scale.x = 0x1000;
    scale.y = 0x1000;
    scale.z = 0x1000;
    ScaleMatrix(m, &scale);
    wp->routine_0      = 1;
    wp->value_B4       = 0x808080;
    wp->value_78       = 0;
    wp->u_70.b[3]      = D_80098928[wp->kind_2]->value_A;
    wp->value_6E       = D_80098928[wp->kind_2]->life_8;
    wp->hit_CC.flags_8 = 0;
}

void func_801079BC(ST0E_VIEW *wp)
{
    STCOM_FIXED_VECTOR scale;
    ST0E_HIT *hit;
    STCOM_MATRIX *m;

    hit = &wp->hit_CC;
    if (Sce_flag_test(0x60F))
    {
        wp->rotation.x = (wp->rotation.x + 0x1E) & 0xFFF;
    }
    m = &wp->matrix_8C;
    RotMatrixYXZ(&wp->rotation, m);
    scale.x = 0x1000;
    scale.y = 0x1000;
    scale.z = 0x1000;
    ScaleMatrix(m, &scale);
    wp->vec_AC       = wp->position;
    wp->hit_CC.pos_0 = wp->position;
    func_800341BC(hit, 0x78, 0, 0x8000, wp->value_1, &hit->flags_8, wp->u_70.b[3] | 0x05000000, 0,
                  0x80);
    wp->hit_CC.pos_0 = wp->position;
    wp->hit_CC.pos_0.z += 0xB4;
    func_800341BC(hit, 0x78, 0, 0x8000, wp->value_1, &hit->flags_8, wp->u_70.b[3] | 0x05000000, 0,
                  0x80);
    wp->hit_CC.pos_0 = wp->position;
    wp->hit_CC.pos_0.z -= 0xB4;
    func_800341BC(hit, 0x78, 0, 0x8000, wp->value_1, &hit->flags_8, wp->u_70.b[3] | 0x05000000, 0,
                  0x80);
    wp->hit_CC.flags_8 = 0;
}

void func_80107B94(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_80107BB4(ST0E_10C *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    D_801104B0[wp->variant_3](wp);
    wp->value_D4 = 0;
}

void func_80107C40(void)
{
}

void func_80107C48(void)
{
}

void func_80107C50(void)
{
}

void func_80107C58(STAGE_OBJ *wp)
{
    D_801104D4[wp->routine_0](wp);
}

void func_80107C94(ST0E_VIEW *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR pos;
    ST0E_HIT *hit;
    STCOM_MATRIX *m;

    wp->vec_AC     = wp->position;
    wp->rotation.x = 0;
    wp->rotation.z = 0;
    wp->u_44.w[0]  = 0;
    wp->u_48.w[0]  = 0;
    wp->u_64.w[0]  = 0;
    wp->u_70.w[0]  = 0;
    wp->u_74.w[0]  = 0;
    wp->flags_0 |= 6;
    func_8002F9C4(wp, &wp->variant_3);
    m = &wp->matrix_8C;
    RotMatrixYXZ(&wp->rotation, m);
    scale.x = 0x1000;
    scale.y = 0x1000;
    scale.z = 0x1000;
    ScaleMatrix(m, &scale);
    wp->value_B4  = 0x808080;
    wp->routine_0 = 1;
    wp->value_6E  = 1;
    wp->value_78  = 0;
    wp->value_FB  = 1;
    hit           = &wp->hit_CC;
    if (wp->rotation.y == 0)
    {
        pos.x = -0xB00;
        pos.y = -0x181;
        pos.z = -0xD00;
        func_8003AC9C(func_80048D08(1, &pos), 0x31802);
    }
    else
    {
        pos.x = -0x1B00;
        pos.y = -0x181;
        pos.z = -0x1100;
        func_8003AC9C(func_80048D08(1, &pos), 0x31702);
    }
    hit->flags_8 = 0;
}

void func_80107DE0(ST0E_VIEW *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX *m;
    ST0E_VIEW_CTL *ctl;
    sint32 damage;

    ctl = (ST0E_VIEW_CTL *)&wp->hit_CC;
    if (!(wp->hit_CC.flags_8 & 0x20000000))
    {
        damage = wp->hit_CC.flags_8 & 0xFFFFFF;
        if (damage != 0)
        {
            Sound_call2(0xA0, &wp->position);
            if (!((uint32)func_80031F84(&wp->position, (STCOM_SVECTOR *)wp->data_DC, wp->rotation.y,
                                        0) >>
                  16))
            {
                wp->value_6E -= damage;
                if (wp->value_6E <= 0)
                {
                    wp->routine_1 = 1;
                    wp->u_4C.h[0] = 0;
                }
                else
                {
                    if (wp->routine_1 == 2)
                    {
                        if (wp->rotation.x > wp->rotation_prev.x && wp->rotation_prev.x >= 0x1000)
                        {
                            wp->value_F4  = 0;
                            wp->routine_2 = 1;
                            wp->u_4C.h[0] += 5;
                        }
                        else
                        {
                            ctl->value_2E       = 0;
                            wp->u_4C.h[0]       = 5;
                            ctl->value_28       = 0;
                            wp->rotation.x      = 0;
                            wp->rotation_prev.x = 0;
                            wp->routine_2       = 0;
                        }
                    }
                    else
                    {
                        wp->value_FA        = 0;
                        wp->u_4C.h[0]       = 5;
                        wp->value_F4        = 0;
                        wp->rotation.x      = 0;
                        wp->rotation_prev.x = 0;
                        wp->routine_2       = 0;
                    }
                    wp->routine_1 = 2;
                }
            }
        }
    }
    else if (!((uint32)func_80031F84(&wp->position, (STCOM_SVECTOR *)wp->data_DC, wp->rotation.y,
                                     0) >>
               16))
    {
        wp->routine_1 = 1;
    }
    D_801104E0[wp->routine_1](wp);
    m = &wp->matrix_8C;
    RotMatrixYXZ(&wp->rotation, m);
    scale.x = 0x1000;
    scale.y = 0x1000;
    scale.z = 0x1000;
    ScaleMatrix(m, &scale);
    wp->vec_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
    if (ctl->value_2F != 0)
    {
        ctl->hit.pos_0.x = wp->position.x;
        ctl->hit.pos_0.y = wp->position.y - 0x78;
        ctl->hit.pos_0.z = wp->position.z;
        func_800341BC(&ctl->hit, 0x78, 0, 0x8000, wp->value_1, &ctl->hit.flags_8, 0x04080000,
                      0x800000, 0x80);
        ctl->hit.pos_0.x = wp->position.x;
        ctl->hit.pos_0.y = wp->position.y - 0x168;
        ctl->hit.pos_0.z = wp->position.z;
        func_800341BC(&ctl->hit, 0x78, 0, 0x8000, wp->value_1, &ctl->hit.flags_8, 0x04080000,
                      0x800000, 0x80);
    }
    ctl->hit.flags_8 = 0;
}

void func_80108084(STAGE_OBJ *wp)
{
    func_80031824(wp);
}

void func_801080A4(void)
{
}

void func_801080AC(ST0E_VIEW *wp)
{
    STCOM_SVECTOR pos;

    if (wp->rotation.x != 0xC00)
    {
        wp->u_4C.h[0] -= 0xA;
        wp->rotation.x = (wp->rotation.x + wp->u_4C.h[0]) & 0xFFF;
    }
    if (wp->rotation.x < 0xC00)
    {
        wp->rotation.x = 0;
        wp->variant_3  = 8;
        func_8002F9C4(wp, &wp->variant_3);
        wp->routine_1 = 0;
        wp->value_FB  = 0;
        Sound_call2(0x107, &wp->position);
        if (wp->rotation.y == 0)
        {
            pos.x = -0xB00;
            pos.y = -0x181;
            pos.z = -0xD00;
            func_8003AC9C(func_80048D08(1, &pos), 0x30802);
        }
        else
        {
            pos.x = -0x1B00;
            pos.y = -0x181;
            pos.z = -0x1100;
            func_8003AC9C(func_80048D08(1, &pos), 0x30702);
        }
    }
}

void func_801081AC(ST0E_VIEW *wp)
{
    ST0E_VIEW_CTL *ctl;

    ctl = (ST0E_VIEW_CTL *)&wp->hit_CC;
    if (wp->routine_2 == 0)
    {
        if (wp->rotation.x == 0)
        {
            ctl->value_2E ^= 1;
            if (abs(wp->u_4C.h[0] - wp->value_F4) < 3)
            {
                wp->rotation.x = 0;
                wp->routine_1  = 0;
                return;
            }
            wp->value_F4 = wp->u_4C.h[0];
        }
    }
    else if (abs(wp->rotation_prev.x - wp->rotation.x) > 0x800)
    {
        ctl->value_2E ^= 1;
        if (abs(wp->u_4C.h[0] - wp->value_F4) < 3)
        {
            wp->rotation.x = 0;
            wp->routine_1  = 0;
            return;
        }
        wp->value_F4 = wp->u_4C.h[0];
    }
    if (ctl->value_2E != 0)
    {
        wp->u_4C.h[0]--;
    }
    else
    {
        wp->u_4C.h[0]++;
    }
    wp->rotation_prev.x = wp->rotation.x;
    wp->rotation.x      = (wp->rotation.x - wp->u_4C.h[0]) & 0xFFF;
}

void func_801082D8(ST0E_10C *wp)
{
    STCOM_FIXED_VECTOR scale;

    D_801104EC[wp->routine_0](wp);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    scale.x = 0x1000;
    scale.y = 0x1000;
    scale.z = 0x1000;
    ScaleMatrix(&wp->matrix_8C.m, &scale);
}

void func_8010834C(ST0E_10C *wp)
{
    wp->position_AC = wp->position;
    wp->rotation.x  = 0;
    wp->rotation.z  = 0;
    wp->value_44    = 0;
    wp->value_48    = 0;
    wp->value_64    = 0;
    wp->value_70    = 0;
    wp->value_74    = 0;
    wp->flags_0 |= 6;
    func_8002F9C4(wp, &wp->variant_3);
    wp->routine_0 = 1;
    wp->byte_D    = 0x28;
    wp->routine_1 = 0;
    wp->color_B4  = 0x2C808080;
    wp->byte_E    = 0x78;
}

void func_801083EC(STAGE_OBJ *wp)
{
    wp->rotation_prev = wp->rotation;
    D_801104F8[wp->routine_1](wp);
}

void func_80108448(STAGE_OBJ *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_SVECTOR pos;

    pl = &Player_work;
    if ((sint32)func_80030254(pl, wp) < 0x384 &&
        func_80031DCC(&wp->position_fixed.v, wp->rotation.y + 0x400, 0x100, &pl->position_fixed,
                      Player_work.rotation.y, 0x800))
    {
        wp->routine_1 = 1;
        if (wp->u_C.b.byte_C == 0)
        {
            pos.x = -0x900;
            pos.y = -0x12B;
            pos.z = -0x2300;
            func_8003AC9C(func_80048D08(2, &pos), 0x60302);
        }
        else
        {
            pos.x = -0x1700;
            pos.y = -0x2AB;
            pos.z = -0x2300;
            func_8003AC9C(func_80048D08(2, &pos), 0x60402);
        }
    }
}

void func_80108540(STAGE_OBJ *wp)
{
    sint16 temp_v0;

    temp_v0        = ((uint16)wp->rotation.z - 0x50) & 0xFFF;
    wp->rotation.z = temp_v0;
    if (temp_v0 < 0xC01)
    {
        wp->rotation.z = 0xC00;
        wp->routine_1  = 2;
    }
}

void func_80108574(void)
{
}

void func_8010857C(STAGE_OBJ *wp)
{
    func_80031A4C(wp);
}
