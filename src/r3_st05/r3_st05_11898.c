#include "common.h"
#include "st05.h"

void func_80111898(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    ST05_WALKER *link;

    if (wp->routine_0 == 0)
    {
        D_80131380[0](wp);
    }
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    ctl                     = &wp->ctl;
    if (wp->u_E.b.byte_F & 2)
    {
        wp->scale.v.pad = 0x7FFF;
        wp->u_E.b.byte_F &= ~2;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    ctl->value_2 = rand();
    if (ctl->flags_0 & 0x20)
    {
        wp->position           = ((ST05_WALKER *)ctl->link_34)->pos_180;
        wp->position_fixed.v.x = wp->position.x << 16;
        wp->position_fixed.v.y = wp->position.y << 16;
        wp->position_fixed.v.z = wp->position.z << 16;
        link                   = (ST05_WALKER *)ctl->link_34;
        wp->rotation.y         = (wp->rotation.y + (link->rotation.y - link->rotation_prev.y)) & 0xFFF;
    }
    D_80131380[wp->routine_0](wp);
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032538(wp);
    }
    if (ctl->flags_0 & 4)
    {
        for (ctl->joint_48 = 3; ctl->joint_48 < 7; ctl->joint_48 += 2)
        {
            ST05_SP_JOINT[ctl->joint_48].x = ctl->value_40[ctl->joint_48 >> 2];
            ST05_SP_JOINT[ctl->joint_48].y = 0;
            ST05_SP_JOINT[ctl->joint_48].z = 0;
            RotMatrix(ST05_SP_JOINT, &D_80137E90);
            TransposeMatrix(&D_80137E90, &D_80137EB0);
            RotMatrix(&ST05_SP_JOINT[ctl->joint_48], &D_80137ED0);
            MulMatrix0(&D_80137E90, &D_80137ED0, &D_80137EF0);
            MulMatrix0(&D_80137EB0, &wp->matrix_1E8[ctl->joint_48].m, &D_80137F10);
            MulMatrix0(&D_80137EF0, &D_80137F10, &wp->matrix_1E8[ctl->joint_48].m);
        }
    }
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 1);
    }
    if (!(ctl->flags_0 & 0x40))
    {
        func_80051B68(wp, 1, -1, 0x1000008);
    }
    if (ctl->flags_0 & 0x80)
    {
        ctl->part_44->position_fixed.v.x = wp->joint_180[0].x << 16;
        ctl->part_44->position_fixed.v.z = wp->joint_180[0].z << 16;
        func_80030150(&ctl->part_44->position_fixed.v, &ctl->part_44->position);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        ctl->hit_pos_C = wp->joint_180[0];
        ctl->hit_pos_C.y += 0x38;
        func_800341BC(&ctl->hit_pos_C, 0x100, 0, 0x8000, wp->value_1, &ctl->value_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->value_14 = 0;
}

void func_80111CEC(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint32 variant;

    ctl = &wp->ctl;
    if (wp->variant_3 & 0x40)
    {
        wp->ctl.flags_0 = 0x200;
    }
    else
    {
        wp->ctl.flags_0 = 0;
    }
    wp->rotation.x           = 0;
    wp->rotation.z           = 0;
    *(sint32 *)&wp->value_64 = 0;
    *(sint32 *)&wp->speed_44 = 0;
    wp->value_48.value       = 0;
    wp->flags_0 |= 2;
    wp->variant_3 &= 0x1F;
    wp->rotation.y = (wp->u_C.b.byte_C << 9) & 0xE00;
    wp->u_C.b.byte_C &= 0xF0;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]       = 0x2000200;
    wp->scale.words[1]       = 0x200;
    *(sint32 *)&ctl->timer_4 = 0;
    *(sint32 *)&ctl->value_8 = 0;
    ctl->value_14            = 0;
    ctl->value_18            = 0;
    ctl->flags_0 |= 0xB2;
    ctl->link_34 = func_80036294(wp->u_C.b.byte_D);
    Track_reset(ctl->track_24, D_80098844[ctl->link_34->kind_2]->track_F, -0x60);
    ctl->value_3C          = ctl->value_40;
    ctl->value_40[0]       = 0;
    ctl->value_40[1]       = 0;
    ctl->joint_48          = 0;
    ctl->fx_4C             = NULL;
    ctl->obj_50            = NULL;
    ctl->pl_54             = NULL;
    ctl->value_58[0]       = 0;
    ctl->value_58[1]       = 0;
    ctl->timer_38          = 0;
    wp->value_6E           = 0;
    wp->value_B0           = 0;
    wp->value_B2           = 0;
    wp->data_78            = D_801313BC;
    wp->value_10           = 0;
    wp->position.y         = Obj_ceiling_height_get(wp);
    wp->position_fixed.v.y = wp->position.y << 16;
    if (ctl->link_34->flags_F & 4)
    {
        wp->routine_0             = 5;
        wp->routine_1             = 4;
        *(uint16 *)&wp->routine_2 = 0;
    }
    else
    {
        variant       = wp->variant_3;
        wp->routine_0 = 1;
        if (variant == 2)
        {
            wp->routine_1             = 3;
            D_80138024                = variant;
            *(uint16 *)&wp->routine_2 = 0;
        }
        else
        {
            wp->routine_1             = 1;
            *(uint16 *)&wp->routine_2 = 0;
        }
    }
    func_800322A8(wp, 0, 0);
    wp->scale.v.pad = 0x4210;
    ctl->part_44    = func_80031418();
    if (ctl->part_44 != NULL)
    {
        ctl->part_44->flags_0               = 1;
        ctl->part_44->kind_2                = 0;
        ctl->part_44->variant_3             = 0x40;
        *(uint32 *)&ctl->part_44->routine_0 = 0;
        *(uint32 *)&ctl->part_44->u_C       = 0;
        ctl->part_44->position_fixed.v.x    = wp->joint_180[0].x << 16;
        ctl->part_44->position_fixed.v.y    = (wp->joint_180[0].y - 0x180) << 16;
        ctl->part_44->position_fixed.v.z    = wp->joint_180[0].z << 16;
        func_80030150(&ctl->part_44->position_fixed.v, &ctl->part_44->position);
        ctl->part_44->rotation = wp->rotation;
    }
}

void func_80111F80(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;

    ctl = &wp->ctl;
    if (func_800364B0(ctl->track_24, wp, wp->rotation.y))
    {
        wp->ctl.flags_0 |= 0x100;
    }
    else
    {
        wp->ctl.flags_0 &= ~0x100;
    }
    D_80131398[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 7:
                D_80138078 = 0;
                D_80138080 = 0xF0;
                // fall through
            case 0:
            case 6:
            case 8:
                if ((wp->u_E.b.byte_E & 1) || (ctl->flags_0 & 0x100) || (wp->u_E.b.byte_F & 1))
                {
                    wp->routine_1 = 6;
                    wp->u_E.b.byte_F &= ~1;
                }
                else
                {
                    wp->routine_1 = 0;
                }
                break;
            case 1:
            case 3:
                if ((wp->u_E.b.byte_E & 1) || (ctl->flags_0 & 0x100) || (wp->u_E.b.byte_F & 1))
                {
                    wp->routine_1 = 3;
                    wp->u_E.b.byte_F &= ~1;
                }
                else
                {
                    wp->routine_1 = 1;
                    wp->u_E.b.byte_F &= ~1;
                }
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->timer_38 != 0)
    {
        ctl->timer_38--;
    }
}

void func_8011214C(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;

    ctl = &wp->ctl;
    if (func_800364B0(ctl->track_24, wp, wp->rotation.y))
    {
        wp->ctl.flags_0 |= 0x100;
    }
    else
    {
        wp->ctl.flags_0 &= ~0x100;
    }
    D_80131398[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        wp->routine_1             = 1;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
    if (ctl->timer_38 != 0)
    {
        ctl->timer_38--;
    }
}

void func_80112230(ST05_OBJ *wp)
{
    func_80031824(wp);
    func_80031824(wp->value_36C);
}

void func_80112264(STAGE_OBJ *wp)
{
    func_80112284(wp);
}

void func_80112284(STAGE_OBJ *obj)
{
    ST05_WAGON *wp;
    ST05_WAGON_CTL *ctl;
    STAGE_OBJ *owner;

    wp  = (ST05_WAGON *)obj;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            owner = (STAGE_OBJ *)wp->ctl.link_34;
            wp->routine_2++;
            wp->anim_AC     = 0;
            wp->ctl.value_8 = 0;
            wp->ctl.timer_4 = 0x20;
            D_80137F30[0]   = owner->position;
            D_80137F38      = ((STAGE_OBJ *)wp->ctl.link_34)->position_fixed.v;
            func_8002FFC4(D_80137F30, &D_80137F38, ((STAGE_OBJ *)wp->ctl.link_34)->rotation.y, 0x100, 0, 0);
            wp->turn_66 = Muku(&wp->position, D_80137F30, wp->rotation.y, 0x800) >> 5;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2++;
                wp->rotation.y = ((STAGE_OBJ *)ctl->link_34)->rotation.y;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + wp->turn_66) & 0xFFF;
            }
            // fall through
        case 2:
            if ((ctl->flags_0 & 0x100) || (wp->u_E.b.byte_F & 1) || (wp->u_E.b.byte_E & 1))
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80112444(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0xA;
            wp->rotation.y  = ((STAGE_OBJ *)wp->ctl.link_34)->rotation.y;
            wp->ctl.timer_4 = 0x3C;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 |= 0x40;
            func_80052528(wp);
            wp->ctl.part_44->routine_1 = 0xF;
            // fall through
        case 1:
            if (ctl->timer_4 == 0x2B)
            {
                ctl->flags_0 &= ~0x80;
                ctl->part_44->routine_0          = 0;
                ctl->part_44->variant_3          = 1;
                ctl->part_44->value_4            = 1;
                ctl->part_44->rotation.y         = ((STAGE_OBJ *)ctl->link_34)->rotation.y;
                ctl->part_44->position           = wp->joint_180[1];
                ctl->part_44->position_fixed.v.x = ctl->part_44->position.x << 16;
                ctl->part_44->position_fixed.v.y = ctl->part_44->position.y << 16;
                ctl->part_44->position_fixed.v.z = ctl->part_44->position.z << 16;
                Obj_pos_set(ctl->part_44, -0x300, -0x400, 0);
                Sound_call2(0xE4, &wp->position);
            }
            if (--ctl->timer_4 < 0)
            {
                if (wp->u_E.b.byte_F & 0x40)
                {
                    D_80138094->routine_1             = 3;
                    *(uint16 *)&D_80138094->routine_2 = 0;
                    D_80138094->position              = wp->position;
                    D_80138094->position_fixed        = wp->position_fixed;
                }
                ctl->fx_4C = func_80031618();
                if (ctl->fx_4C != NULL)
                {
                    ctl->fx_4C->flags_0         = 5;
                    ctl->fx_4C->kind_2          = 0x80;
                    ctl->fx_4C->variant_3       = 0x42;
                    ctl->fx_4C->sprite.position = wp->joint_180[0];
                }
                if (ctl->flags_0 & 0x200)
                {
                    func_80031824(wp);
                }
                wp->u_E.b.byte_F = 0;
                wp->flags_0 &= ~3;
            }
            break;
    }
}

void func_801126CC(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint16 turn;
    sint16 pitch;

    wp->ctl.pl_54 = &ST05_PL;
    ctl           = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            ctl->value_8  = 0;
            ctl->flags_0 |= 4;
            Track_stop(ctl->track_24);
            ctl->value_6 = 0x5A;
            D_801380A0[0]->u_E.b.byte_F |= 1;
            D_801380A0[1]->u_E.b.byte_F |= 1;
            D_801380A0[2]->u_E.b.byte_F |= 1;
            // fall through
        case 1:
            if (Muku(&wp->position, &ctl->pl_54->position, wp->rotation.y, 0x800) < 0)
            {
                ctl->side_3A  = 3;
                ctl->value_3C = &ctl->value_40[0];
            }
            else
            {
                ctl->side_3A  = 5;
                ctl->value_3C = &ctl->value_40[1];
            }
            wp->routine_2 = 2;
            // fall through
        case 2:
            turn           = Muku(&wp->joint_180[ctl->side_3A], &ctl->pl_54->joint_3A8[8], wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            pitch          = func_80031CA4(&wp->joint_180[ctl->side_3A], &ctl->pl_54->joint_3A8[8], *ctl->value_3C, 0x10);
            *ctl->value_3C = (*ctl->value_3C + pitch) & 0xFFF;
            if (ctl->timer_38 != 0)
            {
                break;
            }
            if ((turn < 0 ? -turn : turn) < 0x20 && (pitch < 0 ? -pitch : pitch) < 0x10)
            {
                wp->routine_2 = 3;
                ctl->timer_4  = D_801313D4[wp->variant_3];
            }
            break;
        case 3:
            pitch          = func_80031CA4(&wp->joint_180[ctl->side_3A], &ctl->pl_54->joint_3A8[8], *ctl->value_3C, 0x10);
            *ctl->value_3C = (*ctl->value_3C + pitch) & 0xFFF;
            if (D_80138024 == wp->variant_3 && ctl->timer_38 == 0 && wp->value_80 < 0xC80000)
            {
                ctl->obj_50 = (ST05_PROP_B *)Open_SHL_WORK();
                if (ctl->obj_50 != NULL)
                {
                    ctl->obj_50->flags_0 = 1;
                    ctl->obj_50->kind_2  = 0x2E;
                    if (ctl->side_3A == 3)
                    {
                        ctl->obj_50->variant_3 = 0x40;
                    }
                    else
                    {
                        ctl->obj_50->variant_3 = 0x41;
                    }
                    ctl->obj_50->spin_64.h[0]     = wp->rotation.y;
                    ctl->obj_50->spin_64.h[1]     = (*ctl->value_3C + 0x400) & 0xFFF;
                    ctl->obj_50->position         = wp->joint_180[ctl->side_3A];
                    ctl->obj_50->position_fixed.x = ctl->obj_50->position.x << 16;
                    ctl->obj_50->position_fixed.y = ctl->obj_50->position.y << 16;
                    ctl->obj_50->position_fixed.z = ctl->obj_50->position.z << 16;
                    ctl->timer_38                 = 5;
                    Sound_call2(0xE3, &wp->position);
                }
            }
            if (ctl->timer_4 != 0)
            {
                ctl->timer_4--;
            }
            else if (D_80138024 == wp->variant_3)
            {
                wp->routine_2++;
                ctl->timer_4 = 0x1E;
            }
            else
            {
                ctl->flags_0 |= 1;
                wp->u_E.b.byte_F &= ~1;
            }
            break;
        case 4:
            if (--ctl->timer_4 < 0)
            {
                D_80138024 = (D_80138024 + 1) % 3;
                ctl->flags_0 |= 1;
                wp->u_E.b.byte_F &= ~1;
            }
            break;
    }
}

void func_80112B58(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint16 turn;
    sint16 pitch;

    wp->ctl.pl_54 = &ST05_PL;
    ctl           = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            wp->ctl.flags_0 |= 4;
            Track_stop(wp->ctl.track_24);
            wp->ctl.value_6 = 0x5A;
            // fall through
        case 1:
            if (Muku(&wp->position, &ctl->pl_54->position, wp->rotation.y, 0x800) < 0)
            {
                ctl->side_3A  = 3;
                ctl->value_3C = &ctl->value_40[0];
            }
            else
            {
                ctl->side_3A  = 5;
                ctl->value_3C = &ctl->value_40[1];
            }
            wp->routine_2 = 2;
            // fall through
        case 2:
            turn           = Muku(&wp->joint_180[ctl->side_3A], &ctl->pl_54->joint_3A8[8], wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            pitch          = func_80031CA4(&wp->joint_180[ctl->side_3A], &ctl->pl_54->joint_3A8[8], *ctl->value_3C, 0x10);
            *ctl->value_3C = (*ctl->value_3C + pitch) & 0xFFF;
            if (ctl->timer_38 != 0)
            {
                break;
            }
            if ((turn < 0 ? -turn : turn) < 0x20 && (pitch < 0 ? -pitch : pitch) < 0x10)
            {
                wp->routine_2 = 3;
                ctl->timer_4  = D_801313D8[wp->variant_3];
            }
            break;
        case 3:
            pitch             = func_80031CA4(&wp->joint_180[wp->ctl.side_3A], &wp->ctl.pl_54->joint_3A8[8], *wp->ctl.value_3C, 0x10);
            *wp->ctl.value_3C = (*wp->ctl.value_3C + pitch) & 0xFFF;
            if (wp->ctl.timer_38 == 0 && wp->value_80 < D_801313C8[wp->variant_3])
            {
                wp->ctl.obj_50 = (ST05_PROP_B *)Open_SHL_WORK();
                if (wp->ctl.obj_50 != NULL)
                {
                    wp->ctl.obj_50->flags_0 = 1;
                    wp->ctl.obj_50->kind_2  = 0x2E;
                    if (wp->ctl.side_3A == 3)
                    {
                        wp->ctl.obj_50->variant_3 = 0x40;
                    }
                    else
                    {
                        wp->ctl.obj_50->variant_3 = 0x41;
                    }
                    ctl->obj_50->spin_64.h[0]     = wp->rotation.y;
                    ctl->obj_50->spin_64.h[1]     = (*ctl->value_3C + 0x400) & 0xFFF;
                    ctl->obj_50->position         = wp->joint_180[ctl->side_3A];
                    ctl->obj_50->position_fixed.x = ctl->obj_50->position.x << 16;
                    ctl->obj_50->position_fixed.y = ctl->obj_50->position.y << 16;
                    ctl->obj_50->position_fixed.z = ctl->obj_50->position.z << 16;
                    ctl->timer_38                 = 5;
                    Sound_call2(0xE3, &wp->position);
                }
            }
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 1;
                ctl->timer_38 = 0x2D;
                if (!(ctl->flags_0 & 0x100))
                {
                    ctl->flags_0 |= 1;
                }
            }
            break;
    }
    if (!(wp->u_E.b.byte_F & 0x40) && !(ctl->flags_0 & 0x200) && ctl->value_6 == 0)
    {
        switch (wp->routine_3)
        {
            case 0:
                if (wp->value_80 > 0x200000)
                {
                    break;
                }
                if (func_80031DCC(&wp->position_fixed.v, ((STAGE_OBJ *)ctl->link_34)->rotation.y, 0x600, &ctl->pl_54->position_fixed,
                                  ctl->pl_54->rotation.y, 0x800) != 0)
                {
                    break;
                }
                wp->routine_3 = 1;
                wp->u_E.b.byte_E |= 0x88;
                ctl->part_44->rotation           = wp->rotation;
                ctl->part_44->position.y         = wp->joint_180[0].y - 0xD0;
                ctl->part_44->position_fixed.v.y = ctl->part_44->position.y << 16;
                // fall through
            case 1:
                wp->routine_3    = 2;
                wp->u_C.b.byte_C = 8;
                wp->anim_AC      = 1;
                Sound_call2(0xDF, &wp->position);
                // fall through
            case 2:
                if (--wp->u_C.b.byte_C == 0)
                {
                    wp->routine_3                       = 3;
                    ctl->part_44->routine_1             = 0x11;
                    *(uint16 *)&ctl->part_44->routine_2 = 0;
                }
                break;
            case 3:
                if (ctl->part_44->u_C.b.byte_D == 1)
                {
                    wp->routine_3    = 4;
                    wp->u_C.b.byte_C = 8;
                    wp->anim_AC      = 2;
                }
                break;
            case 4:
                if (--wp->u_C.b.byte_C == 0)
                {
                    wp->routine_3 = 0;
                    wp->anim_AC   = 0;
                    wp->u_E.b.byte_E &= ~0x80;
                    ctl->value_6 = 0x5A;
                    wp->u_E.b.byte_E &= ~0x08;
                }
                break;
        }
    }
    if (ctl->value_6 != 0)
    {
        ctl->value_6--;
    }
}

void func_80113100(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint16 turn;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 1;
            ctl->value_8  = 0;
            // fall through
        case 1:
            turn           = Muku(&wp->position, &D_801380A0[wp->u_C.b.byte_D]->position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (turn < 0)
            {
                break;
            }
            if (turn != 0)
            {
                break;
            }
            wp->routine_2 = 2;
            wp->u_E.b.byte_E |= 0x10;
            // fall through
        case 2:
            if (D_801380A0[wp->u_C.b.byte_D]->u_E.b.byte_E & 0x10)
            {
                wp->routine_2 = 3;
            }
            if (wp->timer_CA != 0)
            {
                wp->timer_CA--;
            }
            break;
        case 3:
            if (wp->timer_CA == 0)
            {
                wp->routine_2 = 4;
                wp->anim_AC   = 2;
                wp->u_E.b.byte_F |= 0x40;
                ctl->timer_4                      = 8;
                D_80138094->routine_1             = 1;
                *(uint16 *)&D_80138094->routine_2 = 0;
            }
            else
            {
                wp->timer_CA--;
            }
            break;
        case 4:
            if (--ctl->timer_4 < 0)
            {
                wp->anim_AC = 0;
                wp->u_E.b.byte_E &= ~0x12;
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801132AC(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint16 turn;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.value_8 = 0;
            wp->ctl.timer_4 = 8;
            wp->u_E.b.byte_E |= 0x80;
            // fall through
        case 1:
            turn           = Muku(&wp->position, &D_801380A0[wp->u_C.b.byte_D]->position, wp->rotation.y, 0x20);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            if (ctl->timer_4 == 0)
            {
                if (turn < 0)
                {
                    break;
                }
                if (turn != 0)
                {
                    break;
                }
                if (D_801380A0[wp->u_C.b.byte_D]->u_E.b.byte_E & 0x50)
                {
                    wp->routine_2                       = 2;
                    ctl->part_44->u_E.b.byte_E          = wp->u_C.b.byte_D;
                    ctl->part_44->rotation              = wp->rotation;
                    ctl->part_44->position.y            = wp->joint_180[0].y - 0xD0;
                    ctl->part_44->position_fixed.v.y    = ctl->part_44->position.y << 16;
                    ctl->part_44->routine_1             = 0x12;
                    *(uint16 *)&ctl->part_44->routine_2 = 0;
                }
            }
            else
            {
                ctl->timer_4--;
            }
            break;
        case 2:
            if (wp->ctl.part_44->u_C.b.byte_D == 1)
            {
                wp->routine_2   = 3;
                wp->anim_AC     = 2;
                wp->ctl.timer_4 = 8;
                wp->u_E.b.byte_E |= 0x10;
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->anim_AC = 0;
                wp->u_E.b.byte_E &= ~0x80;
                wp->ctl.flags_0 |= 1;
                wp->u_E.b.byte_E &= ~0x12;
            }
            break;
    }
}

void func_801134E0(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint16 turn;
    sint16 pitch;
    sint16 roll;

    wp->ctl.pl_54 = &ST05_PL;
    ctl           = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            if (!(ctl->link_34->flags_F & 8))
            {
                break;
            }
            // fall through
        case 1:
            wp->routine_2++;
            ctl->timer_38 = 7;
            ctl->value_8  = 0;
            ctl->flags_0 |= 4;
            Sound_call2(0xE1, &wp->position);
            Sound_call2(0xE2, &wp->position);
            // fall through
        case 2:
            turn             = Muku(&wp->position, &ctl->pl_54->joint_3A8[8], wp->rotation.y, 0x80);
            wp->rotation.y   = (wp->rotation.y + turn) & 0xFFF;
            pitch            = func_80031CA4(&wp->joint_180[3], &ctl->pl_54->joint_3A8[8], ctl->value_40[0], 0x80);
            ctl->value_40[0] = (ctl->value_40[0] + pitch) & 0xFFF;
            roll             = func_80031CA4(&wp->joint_180[5], &ctl->pl_54->joint_3A8[8], ctl->value_40[1], 0x80);
            ctl->value_40[1] = (ctl->value_40[1] + roll) & 0xFFF;
            if (turn == 0 && pitch == 0 && roll == 0)
            {
                wp->routine_1             = 5;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void func_8011366C(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            if (ctl->link_34->flags_F & 0x20)
            {
                wp->routine_0             = 1;
                wp->routine_1             = 3;
                *(uint16 *)&wp->routine_2 = 0;
                break;
            }
            if (!(ctl->link_34->flags_F & 0x10))
            {
                break;
            }
            // fall through
        case 1:
            wp->anim_AC = 1;
            wp->routine_2++;
            ctl->timer_4 = 8;
            ctl->value_8 = 0;
            ctl->link_34->flags_F &= ~0x10;
            Sound_call2(0xDF, &wp->position);
            // fall through
        case 2:
            if (!(ctl->link_34->flags_F & 0x10))
            {
                break;
            }
            ctl->link_34->flags_F &= ~0x10;
            // fall through
        case 3:
            wp->routine_2 = 4;
            wp->anim_AC   = 2;
            ctl->timer_4  = 8;
            ctl->value_8  = 0;
            Sound_call2(0xE0, &wp->position);
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                wp->anim_AC   = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_801137AC(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    if (wp->routine_0 == 0)
    {
        D_801313DC[0](wp);
    }
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.random_2        = rand();
    D_801313DC[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_80032304(wp, wp->anim_AC, ctl->value_48);
    }
    else
    {
        func_80032538(wp);
    }
    ctl->value_48 = 0;
    if (ctl->flags_0 & 0x100)
    {
        ctl->angle_4E = (ctl->angle_4E + (-wp->speed_44 >> 2)) & 0xFFF;
    }
    else
    {
        ctl->angle_4E = (ctl->angle_4E + (wp->speed_44 >> 2)) & 0xFFF;
    }
    STAGE_WHEEL_SP->wheel_138 = ctl->angle_4E;
    STAGE_WHEEL_SP->wheel_148 = ctl->angle_4E * 2;
    Model_parts_mtx_set_y(wp);
    if (wp->flags_0 & 2)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 1);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 8))
    {
        ctl->hit_pos_C = wp->pos_180;
        ctl->hit_pos_C.y -= 0x40;
        func_800341BC(&ctl->hit_pos_C, 0xC8, 0, 0x8000, wp->value_1, &ctl->hit_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_801139EC(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->variant_3 & 0x20)
    {
        wp->routine_0   = 6;
        wp->routine_1   = 0;
        wp->ctl.flags_0 = 8;
    }
    else if (wp->variant_3 & 0x40)
    {
        wp->routine_0   = 4;
        wp->routine_1   = 0;
        wp->ctl.flags_0 = 0x208;
    }
    else if (!(wp->variant_3 & 0x80))
    {
        wp->routine_0   = 1;
        wp->routine_1   = 5;
        wp->ctl.flags_0 = 8;
    }
    else
    {
        wp->routine_0   = 5;
        wp->routine_1   = 0;
        wp->ctl.flags_0 = 0;
    }
    *(uint16 *)&wp->routine_2 = 0;
    ctl->part_34              = func_80031418();
    if (ctl->part_34 != NULL)
    {
        ctl->part_34->flags_0               = 1;
        ctl->part_34->kind_2                = 0x1A;
        ctl->part_34->variant_3             = wp->variant_3;
        *(uint32 *)&ctl->part_34->routine_0 = 0;
        *(uint32 *)&ctl->part_34->u_C       = *(uint32 *)&wp->u_C;
        ctl->part_34->position_fixed.v.x    = wp->pos_180.x << 16;
        ctl->part_34->position_fixed.v.y    = wp->pos_180.y << 16;
        ctl->part_34->position_fixed.v.z    = wp->pos_180.z << 16;
        ctl->part_34->position              = wp->pos_180;
        ctl->part_34->u_C.b.byte_D          = wp->value_1;
    }
    else
    {
        func_80031824(wp);
        return;
    }
    wp->rotation.x           = 0;
    wp->rotation.z           = 0;
    *(sint32 *)&wp->value_64 = 0;
    wp->flags_0 |= 2;
    wp->variant_3 &= 0x1F;
    wp->rotation.y = (wp->u_C.b.byte_C << 9) & 0xE00;
    if (!(ctl->flags_0 & 0x200))
    {
        wp->speed_44 = D_8013179C[wp->variant_3];
        wp->accel_4C = D_801317A4[wp->variant_3];
        wp->turn_66  = D_801317AC[wp->variant_3];
    }
    wp->u_C.b.byte_C &= 0xF0;
    // Pointer arithmetic, not life_A[...]: it keeps retail's addu operand order.
    wp->value_B2 = wp->value_B0 = wp->value_6E = *(D_80098844[wp->kind_2]->life_A + wp->variant_3) * 32;
    wp->data_78                                = D_8013143C;
    wp->value_10                               = 0;
    wp->position.y                             = Obj_ceiling_height_get(wp);
    wp->position_fixed.v.y                     = wp->position.y << 16;
    wp->scale.v.pad                            = 0x4210;
    Model_work_init(wp, &wp->variant_3);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    *(sint32 *)&ctl->timer_4    = 0;
    *(sint32 *)&ctl->value_8    = 0;
    ctl->hit_14                 = 0;
    *(sint32 *)&ctl->reserved18 = 0;
    ctl->flags_0 |= 6;
    Track_reset(ctl->track_24, D_80098844[wp->kind_2]->track_F, -0x200);
    if (!(ctl->flags_0 & 0x200))
    {
        ctl->node_38              = &D_80131790[wp->variant_3][D_801317B4[wp->variant_3]];
        ctl->node_3C              = &D_80131790[wp->variant_3][D_801317BA[wp->variant_3]];
        ctl->node_id_49           = 3;
        ctl->target_40.x          = ctl->node_38->x_4;
        ctl->target_40.y          = 0;
        ctl->target_40.z          = ctl->node_38->z_6;
        ctl->dir_4A               = D_801317B7[wp->variant_3];
        D_801380A0[wp->variant_3] = ctl->part_34;
        D_801380B8[wp->variant_3] = wp;
        D_80138080                = 0;
        D_80138020                = *(uint8 *)0x1F800000;
        if (wp->variant_3 == 2)
        {
            D_80138094 = Open_SHL_WORK();
            if (D_80138094 != NULL)
            {
                D_80138094->flags_0   = 1;
                D_80138094->kind_2    = 0xD;
                D_80138094->variant_3 = 0;
                D_801380A4->u_E.b.byte_F |= 0x40;
            }
        }
    }
    ctl->value_4C = 0;
    ctl->angle_4E = 0;
    ctl->value_48 = 0;
    ctl->value_52 = 0;
    ctl->life_54  = 0x140;
    ctl->mask_50  = 0;
    ctl->value_4B = 0;
    func_800322A8(wp, 0, 0);
}
