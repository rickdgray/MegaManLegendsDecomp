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
    if (wp->be_flag & 2)
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
    if ((wp->be_flag & 1) && (ctl->flags_0 & 8))
    {
        ctl->hit_pos_C = wp->joint_180[0];
        ctl->hit_pos_C.y += 0x38;
        func_800341BC(&ctl->hit_pos_C, 0x100, 0, 0x8000, wp->slot, &ctl->value_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->value_14 = 0;
}

void func_80111CEC(ST05_WAGON *wp)
{
    ST05_WAGON_CTL *ctl;
    sint32 variant;

    ctl = &wp->ctl;
    if (wp->type & 0x40)
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
    wp->be_flag |= 2;
    wp->type &= 0x1F;
    wp->rotation.y = (wp->u_C.b.byte_C << 9) & 0xE00;
    wp->u_C.b.byte_C &= 0xF0;
    Model_work_init(wp, &wp->type);
    wp->scale.words[0]       = 0x2000200;
    wp->scale.words[1]       = 0x200;
    *(sint32 *)&ctl->timer_4 = 0;
    *(sint32 *)&ctl->value_8 = 0;
    ctl->value_14            = 0;
    ctl->value_18            = 0;
    ctl->flags_0 |= 0xB2;
    ctl->link_34 = func_80036294(wp->u_C.b.byte_D);
    Track_reset(ctl->track_24, D_80098844[ctl->link_34->id]->track_F, -0x60);
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
        variant       = wp->type;
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
        ctl->part_44->be_flag               = 1;
        ctl->part_44->id                    = 0;
        ctl->part_44->type                  = 0x40;
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
                ctl->part_44->type               = 1;
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
                    ctl->fx_4C->be_flag         = 5;
                    ctl->fx_4C->id              = 0x80;
                    ctl->fx_4C->type            = 0x42;
                    ctl->fx_4C->sprite.position = wp->joint_180[0];
                }
                if (ctl->flags_0 & 0x200)
                {
                    func_80031824(wp);
                }
                wp->u_E.b.byte_F = 0;
                wp->be_flag &= ~3;
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
                ctl->timer_4  = D_801313D4[wp->type];
            }
            break;
        case 3:
            pitch          = func_80031CA4(&wp->joint_180[ctl->side_3A], &ctl->pl_54->joint_3A8[8], *ctl->value_3C, 0x10);
            *ctl->value_3C = (*ctl->value_3C + pitch) & 0xFFF;
            if (D_80138024 == wp->type && ctl->timer_38 == 0 && wp->value_80 < 0xC80000)
            {
                ctl->obj_50 = (ST05_PROP_B *)Open_SHL_WORK();
                if (ctl->obj_50 != NULL)
                {
                    ctl->obj_50->be_flag = 1;
                    ctl->obj_50->id      = 0x2E;
                    if (ctl->side_3A == 3)
                    {
                        ctl->obj_50->type = 0x40;
                    }
                    else
                    {
                        ctl->obj_50->type = 0x41;
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
            else if (D_80138024 == wp->type)
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
                ctl->timer_4  = D_801313D8[wp->type];
            }
            break;
        case 3:
            pitch             = func_80031CA4(&wp->joint_180[wp->ctl.side_3A], &wp->ctl.pl_54->joint_3A8[8], *wp->ctl.value_3C, 0x10);
            *wp->ctl.value_3C = (*wp->ctl.value_3C + pitch) & 0xFFF;
            if (wp->ctl.timer_38 == 0 && wp->value_80 < D_801313C8[wp->type])
            {
                wp->ctl.obj_50 = (ST05_PROP_B *)Open_SHL_WORK();
                if (wp->ctl.obj_50 != NULL)
                {
                    wp->ctl.obj_50->be_flag = 1;
                    wp->ctl.obj_50->id      = 0x2E;
                    if (wp->ctl.side_3A == 3)
                    {
                        wp->ctl.obj_50->type = 0x40;
                    }
                    else
                    {
                        wp->ctl.obj_50->type = 0x41;
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
    if (wp->be_flag & 2)
    {
        Model_Shadow_Trans(wp, 0x80, 0x200, 1);
    }
    if ((wp->be_flag & 1) && (ctl->flags_0 & 8))
    {
        ctl->hit_pos_C = wp->pos_180;
        ctl->hit_pos_C.y -= 0x40;
        func_800341BC(&ctl->hit_pos_C, 0xC8, 0, 0x8000, wp->slot, &ctl->hit_14, ctl->value_8 | 0x4880000, 0x800000, 0);
    }
    ctl->hit_14 = 0;
}

void func_801139EC(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    if (wp->type & 0x20)
    {
        wp->routine_0   = 6;
        wp->routine_1   = 0;
        wp->ctl.flags_0 = 8;
    }
    else if (wp->type & 0x40)
    {
        wp->routine_0   = 4;
        wp->routine_1   = 0;
        wp->ctl.flags_0 = 0x208;
    }
    else if (!(wp->type & 0x80))
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
        ctl->part_34->be_flag               = 1;
        ctl->part_34->id                    = 0x1A;
        ctl->part_34->type                  = wp->type;
        *(uint32 *)&ctl->part_34->routine_0 = 0;
        *(uint32 *)&ctl->part_34->u_C       = *(uint32 *)&wp->u_C;
        ctl->part_34->position_fixed.v.x    = wp->pos_180.x << 16;
        ctl->part_34->position_fixed.v.y    = wp->pos_180.y << 16;
        ctl->part_34->position_fixed.v.z    = wp->pos_180.z << 16;
        ctl->part_34->position              = wp->pos_180;
        ctl->part_34->u_C.b.byte_D          = wp->slot;
    }
    else
    {
        func_80031824(wp);
        return;
    }
    wp->rotation.x           = 0;
    wp->rotation.z           = 0;
    *(sint32 *)&wp->value_64 = 0;
    wp->be_flag |= 2;
    wp->type &= 0x1F;
    wp->rotation.y = (wp->u_C.b.byte_C << 9) & 0xE00;
    if (!(ctl->flags_0 & 0x200))
    {
        wp->speed_44 = D_8013179C[wp->type];
        wp->accel_4C = D_801317A4[wp->type];
        wp->turn_66  = D_801317AC[wp->type];
    }
    wp->u_C.b.byte_C &= 0xF0;
    // Pointer arithmetic, not life_A[...]: it keeps retail's addu operand order.
    wp->value_B2 = wp->value_B0 = wp->value_6E = *(D_80098844[wp->id]->life_A + wp->type) * 32;
    wp->data_78                                = D_8013143C;
    wp->value_10                               = 0;
    wp->position.y                             = Obj_ceiling_height_get(wp);
    wp->position_fixed.v.y                     = wp->position.y << 16;
    wp->scale.v.pad                            = 0x4210;
    Model_work_init(wp, &wp->type);
    wp->scale.words[0]          = 0x2000200;
    wp->scale.words[1]          = 0x200;
    *(sint32 *)&ctl->timer_4    = 0;
    *(sint32 *)&ctl->value_8    = 0;
    ctl->hit_14                 = 0;
    *(sint32 *)&ctl->reserved18 = 0;
    ctl->flags_0 |= 6;
    Track_reset(ctl->track_24, D_80098844[wp->id]->track_F, -0x200);
    if (!(ctl->flags_0 & 0x200))
    {
        ctl->node_38         = &D_80131790[wp->type][D_801317B4[wp->type]];
        ctl->node_3C         = &D_80131790[wp->type][D_801317BA[wp->type]];
        ctl->node_id_49      = 3;
        ctl->target_40.x     = ctl->node_38->x_4;
        ctl->target_40.y     = 0;
        ctl->target_40.z     = ctl->node_38->z_6;
        ctl->dir_4A          = D_801317B7[wp->type];
        D_801380A0[wp->type] = ctl->part_34;
        D_801380B8[wp->type] = wp;
        D_80138080           = 0;
        D_80138020           = *(uint8 *)0x1F800000;
        if (wp->type == 2)
        {
            D_80138094 = Open_SHL_WORK();
            if (D_80138094 != NULL)
            {
                D_80138094->be_flag = 1;
                D_80138094->id      = 0xD;
                D_80138094->type    = 0;
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

void func_80113E6C(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 i;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    if (D_80138078 == 0 && D_80138020 != ST05_BUFFER_INDEX)
    {
        if (D_80138080 != 0)
        {
            D_80138080--;
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                D_80137F48    = D_801380A0[D_801317C0[i][0]];
                D_80137F4C    = D_801380A0[D_801317C0[i][1]];
                dx            = D_80137F48->position.x - D_80137F4C->position.x;
                dz            = D_80137F48->position.z - D_80137F4C->position.z;
                D_80138028[i] = dx * dx + dz * dz;
            }
            for (i = 0; i < 3; i++)
            {
                if (D_80138028[i] < 0x800000)
                {
                    D_80137F48 = D_801380A0[D_801317C0[i][0]];
                    D_80137F4C = D_801380A0[D_801317C0[i][1]];
                    D_80137F50 = D_801380B8[D_801317C0[i][0]];
                    D_80137F54 = D_801380B8[D_801317C0[i][1]];
                    if (((D_80137F48->u_E.b.byte_F | D_80137F4C->u_E.b.byte_F) & 0x40) && !(D_80137F48->u_E.b.byte_E & 0x4C) &&
                        !(D_80137F4C->u_E.b.byte_E & 0x4C))
                    {
                        D_80137F48->u_C.b.byte_D = D_801317C0[i][1];
                        D_80137F48->u_E.b.byte_E |= 2;
                        if (D_80137F48->u_E.b.byte_F & 0x40)
                        {
                            D_80137F48->u_E.b.byte_E |= 0x80;
                            D_80137F48->routine_1 = 8;
                            D_80137F50->routine_1 = 0xA;
                        }
                        else
                        {
                            D_80137F48->routine_1 = 7;
                            D_80137F50->routine_1 = 0xA;
                        }
                        *(uint16 *)&D_80137F48->routine_2 = 0;
                        *(uint16 *)&D_80137F50->routine_2 = 0;
                        D_80137F4C->u_C.b.byte_D          = D_801317C0[i][0];
                        D_80137F4C->u_E.b.byte_E |= 2;
                        if (D_80137F4C->u_E.b.byte_F & 0x40)
                        {
                            D_80137F4C->u_E.b.byte_E |= 0x80;
                            D_80137F4C->routine_1 = 8;
                            D_80137F54->routine_1 = 0xA;
                        }
                        else
                        {
                            D_80137F4C->routine_1 = 7;
                            D_80137F54->routine_1 = 0xA;
                        }
                        *(uint16 *)&D_80137F4C->routine_2 = 0;
                        *(uint16 *)&D_80137F54->routine_2 = 0;
                        D_80138078                        = 1;
                        break;
                    }
                }
            }
        }
        D_80138020 = ST05_BUFFER_INDEX;
    }
    if (func_8003648C(ctl->track_24, wp))
    {
        ctl->flags_0 |= 0x10;
    }
    else
    {
        ctl->flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 2)
    {
        func_80116254(wp);
    }
    D_801313F8[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 1:
                wp->routine_1 = D_801317C8[wp->type];
                break;
            case 9:
                if (func_80031DCC(&wp->position_fixed.v, wp->rotation.y, 0x400, &ST05_PL.position_fixed, ST05_PL.rotation.y, 0x800))
                {
                    func_80116528(wp);
                }
                else
                {
                    ctl->flags_0 &= ~0x20;
                }
                wp->routine_1 = 5;
                break;
            case 5:
                if (!(ctl->flags_0 & 0x20))
                {
                    wp->routine_1 = 1;
                    break;
                }
                // fall through
            case 4:
                wp->routine_1 = 2;
                break;
            case 3:
                wp->routine_1 = 1;
                break;
            case 10:
                ctl->flags_0 &= ~0x80;
                // fall through
            case 6:
            case 7:
                wp->routine_1 = 5;
                break;
            default:
                wp->routine_1 = 0;
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->value_A != 0)
    {
        ctl->value_A--;
    }
    if (ctl->value_52 != 0)
    {
        ctl->value_52--;
    }
}

void func_801143D8(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    if (func_8003648C(ctl->track_24, wp) != 0)
    {
        wp->ctl.flags_0 |= 0x10;
    }
    else
    {
        wp->ctl.flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 2)
    {
        func_80116254(wp);
    }
    D_801313F8[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->value_A != 0)
    {
        ctl->value_A--;
    }
    if (ctl->value_52 != 0)
    {
        ctl->value_52--;
    }
}

void func_801144D4(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    if (func_8003648C(ctl->track_24, wp) != 0)
    {
        wp->ctl.flags_0 |= 0x10;
    }
    else
    {
        wp->ctl.flags_0 &= ~0x10;
    }
    if (ctl->flags_0 & 2)
    {
        func_80116380(wp);
    }
    D_801313F8[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        wp->routine_1             = 0;
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (ctl->value_A != 0)
    {
        ctl->value_A--;
    }
    if (ctl->value_52 != 0)
    {
        ctl->value_52--;
    }
}

void func_801145D0(ST05_WALKER *wp)
{
    STAGE_OBJ *part;

    func_80031824(wp);
    wp->ctl.part_34->routine_0 = 2;
    part                       = wp->ctl.part_34;
    STAGE_TABLE_3C0[part->id][part->value_4](part);
    if (wp->ctl.part_34->u_E.b.byte_F & 0x40)
    {
        Close_SHL_WORK(D_80138094);
    }
}

void func_8011466C(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 0;
            wp->speed_44  = 0;
            ctl->timer_4  = 0x3C;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801146EC(ST05_WALKER *wp)
{
    uint8 temp_v0;

    temp_v0       = wp->type;
    wp->routine_2 = temp_v0;
    D_80131424[temp_v0](wp);
}

void func_8011472C(ST05_WALKER *wp)
{
    uint8 temp_v0;

    temp_v0       = wp->type;
    wp->routine_2 = temp_v0;
    D_80131430[temp_v0](wp);
}

void func_8011476C(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    ST05_NODE *node;
    sint16 turn;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            node = ctl->node_3C;
            dx   = wp->position.x - (node->x_4 - (node->w_8 >> 1));
            dz   = wp->position.z - (node->z_6 - (node->d_A >> 1));
            if ((uint32)dx < node->w_8 && (uint32)dz < node->d_A)
            {
                wp->routine_2 = 2;
            }
            else
            {
                if (((sint16)D_8013179C[0] >> 1) < wp->speed_44)
                {
                    wp->speed_44 -= wp->accel_4C;
                }
                Obj_pos_set(wp, wp->speed_44, 0, 0);
                break;
            }
            // fall through
        case 2:
            if ((((wp->rotation.y - (sint16)Angle_xz_svector(&wp->position, &ctl->target_40)) + 0x200) & 0xFFF) < 0x400)
            {
                wp->routine_2 = 3;
            }
            // fall through
        case 3:
            turn           = Muku(&wp->position, &ctl->target_40, wp->rotation.y, wp->turn_66);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            Obj_pos_set(wp, wp->speed_44, 0, 0);
            if (turn == 0)
            {
                ctl->flags_0 |= 1;
                ctl->part_34->u_E.b.byte_E &= ~4;
            }
            break;
    }
}

void func_8011493C(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    ST05_NODE *node;
    sint16 turn;
    sint32 dx;
    sint32 dz;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            ctl->value_8  = 0;
            ctl->flags_0 |= 0x100;
            // fall through
        case 1:
            node = ctl->node_3C;
            dx   = wp->position.x - (node->x_4 - (node->w_8 >> 1));
            dz   = wp->position.z - (node->z_6 - (node->d_A >> 1));
            if ((uint32)dx < node->w_8 && (uint32)dz < node->d_A)
            {
                wp->routine_2 = 2;
            }
            else
            {
                if (((sint16)D_8013179C[0] >> 1) < wp->speed_44)
                {
                    wp->speed_44 -= wp->accel_4C;
                }
                Obj_pos_set(wp, -wp->speed_44, 0, 0);
                break;
            }
            // fall through
        case 2:
            turn           = Muku(&wp->position, &ctl->target_40, (wp->rotation.y + 0x800) & 0xFFF, wp->turn_66);
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            Obj_pos_set(wp, -wp->speed_44, 0, 0);
            if (turn == 0)
            {
                ctl->flags_0 |= 1;
                ctl->part_34->u_E.b.byte_E &= ~4;
            }
            break;
    }
}

void func_80114AE0(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 3;
            wp->speed_44  = (sint16)D_8013179C[wp->type] >> 1;
            ctl->timer_4  = 5;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                wp->anim_AC = 4;
            }
            break;
    }
}

void func_80114B8C(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 5;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            if (((sint16)D_8013179C[wp->type] >> 1) < wp->speed_44)
            {
                wp->speed_44 -= wp->accel_4C;
                Obj_pos_set(wp, wp->speed_44, 0, 0);
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 6;
            wp->speed_44  = 0;
            ctl->timer_4  = 0xA;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80114CA0(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 5;
            ctl->value_8  = 0;
            ctl->flags_0 |= 0x100;
            // fall through
        case 1:
            if (((sint16)D_8013179C[wp->type] >> 1) < wp->speed_44)
            {
                wp->speed_44 -= wp->accel_4C;
                Obj_pos_set(wp, -wp->speed_44, 0, 0);
                break;
            }
            wp->routine_2 = 2;
            wp->anim_AC   = 6;
            wp->speed_44  = 0;
            ctl->timer_4  = 0xA;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80114DB8(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 dx;
    sint32 dz;
    sint16 dir;
    sint8 d;

    ctl = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->routine_3 = 1;
            wp->accel_4C  = D_801317A4[wp->type] >> 1;
            ctl->value_8  = 0;
            Track_stop(ctl->track_24);
            ctl->flags_0 &= ~0x110;
            // fall through
        case 1:
            dx = wp->position.x - ctl->node_38->x_4;
            dz = wp->position.z - ctl->node_38->z_6;
            if (dx * dx + dz * dz < 0x200000)
            {
                dir              = func_80115E98(wp);
                ctl->node_id_49  = ctl->node_38->id_0;
                ctl->node_3C     = ctl->node_38;
                ctl->node_38     = &D_80131790[wp->type][ctl->node_38->link_C[dir]];
                ctl->target_40.x = ctl->node_38->x_4;
                ctl->target_40.y = 0;
                ctl->target_40.z = ctl->node_38->z_6;
                d                = dir & 3;
                if (ctl->dir_4A != d)
                {
                    wp->routine_1             = 3;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->part_34->u_E.b.byte_E |= 4;
                }
                ctl->dir_4A = d;
                ctl->flags_0 &= ~0x10;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_40, wp->rotation.y, 0x800)) & 0xFFF;
            }
            if (wp->speed_44 < D_8013179C[wp->type])
            {
                wp->speed_44 += wp->accel_4C;
            }
            Obj_pos_set(wp, wp->speed_44, 0, 0);
            if (ctl->value_52 == 0 && (ctl->flags_0 & 0x10))
            {
                ctl->flags_0 |= 0x21;
                func_80116528(wp);
            }
            break;
    }
}

void func_80114FF4(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 dx;
    sint32 dz;
    sint16 dir;
    sint8 d;

    ctl = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->routine_3 = 1;
            wp->accel_4C  = D_801317A4[wp->type] >> 1;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            dx = wp->position.x - ctl->node_38->x_4;
            dz = wp->position.z - ctl->node_38->z_6;
            if (dx * dx + dz * dz < 0x200000)
            {
                dir              = func_80115E98(wp);
                ctl->node_id_49  = ctl->node_38->id_0;
                ctl->node_3C     = ctl->node_38;
                ctl->node_38     = &D_80131790[wp->type][ctl->node_38->link_C[dir]];
                ctl->target_40.x = ctl->node_38->x_4;
                ctl->target_40.y = 0;
                ctl->target_40.z = ctl->node_38->z_6;
                d                = dir & 3;
                if (ctl->dir_4A != d)
                {
                    wp->routine_1             = 3;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->part_34->u_E.b.byte_E |= 4;
                }
                ctl->dir_4A = d;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_40, wp->rotation.y, 0x800)) & 0xFFF;
            }
            if (wp->speed_44 < D_8013179C[wp->type])
            {
                wp->speed_44 += wp->accel_4C;
            }
            Obj_pos_set(wp, wp->speed_44, 0, 0);
            break;
    }
}

void func_801151E8(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 dx;
    sint32 dz;
    sint16 dir;
    sint8 d;

    ctl = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->routine_3 = 1;
            wp->accel_4C  = D_801317A4[wp->type] >> 1;
            ctl->value_8  = 0;
            Track_stop(ctl->track_24);
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            dx = wp->position.x - ctl->node_38->x_4;
            dz = wp->position.z - ctl->node_38->z_6;
            if (dx * dx + dz * dz < 0x200000)
            {
                dir              = func_80115E98(wp);
                ctl->node_id_49  = ctl->node_38->id_0;
                ctl->node_3C     = ctl->node_38;
                ctl->node_38     = &D_80131790[wp->type][ctl->node_38->link_C[dir]];
                ctl->target_40.x = ctl->node_38->x_4;
                ctl->target_40.y = 0;
                ctl->target_40.z = ctl->node_38->z_6;
                d                = dir & 3;
                if (ctl->dir_4A != d)
                {
                    wp->routine_1             = 3;
                    *(uint16 *)&wp->routine_2 = 0;
                    ctl->part_34->u_E.b.byte_E |= 4;
                }
                ctl->dir_4A = d;
                ctl->flags_0 &= ~0x10;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_40, wp->rotation.y, 0x800)) & 0xFFF;
            }
            if (wp->speed_44 < D_8013179C[wp->type])
            {
                wp->speed_44 += wp->accel_4C;
            }
            Obj_pos_set(wp, wp->speed_44, 0, 0);
            if (ctl->value_52 == 0 && (ctl->flags_0 & 0x10) && wp->value_80 <= 0x120000)
            {
                ctl->flags_0 |= 0x21;
            }
            break;
    }
}

void func_80115430(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 dx;
    sint32 dz;
    sint16 dir;
    uint8 previous;
    sint32 dist;
    STCOM_SVECTOR unused; // Retail reserves this eight-byte local.

    dist = -1;
    ctl  = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->routine_3 = 2;
            wp->accel_4C  = D_801317A4[wp->type] >> 1;
            wp->ctl.flags_0 |= 0x100;
            if ((wp->ctl.flags_0 & 0x40) && wp->ctl.node_3C->link_C[(wp->ctl.dir_4A + 2) & 3] != dist)
            {
                wp->routine_3 = 3;
                wp->ctl.mask_50 |= 0x8000 >> ((wp->ctl.value_4B + 2) & 3);
                goto back;
            }
            ctl->flags_0 &= ~0x40;
            // fall through
        case 2:
            dx   = wp->position.x - ctl->node_38->x_4;
            dz   = wp->position.z - ctl->node_38->z_6;
            dist = dx * dx + dz * dz;
            if (dist < 0x200000)
            {
                if (func_801160F8(wp) != 4)
                {
                    wp->routine_3 = 3;
                    dir           = ctl->dir_4A;
                }
                else
                {
                    dir = func_80115E98(wp);
                    if (ctl->dir_4A != dir)
                    {
                        wp->routine_1             = 4;
                        *(uint16 *)&wp->routine_2 = 0;
                        ctl->flags_0 |= 0x40;
                        ctl->part_34->u_E.b.byte_E |= 4;
                    }
                }
                ctl->node_id_49  = ctl->node_38->id_0;
                ctl->node_3C     = ctl->node_38;
                ctl->node_38     = &D_80131790[wp->type][ctl->node_38->link_C[dir]];
                ctl->target_40.x = ctl->node_38->x_4;
                ctl->target_40.y = 0;
                ctl->target_40.z = ctl->node_38->z_6;
                dir &= 3;
                previous      = ctl->dir_4A;
                ctl->dir_4A   = dir;
                ctl->value_4B = previous;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_40, (wp->rotation.y + 0x800) & 0xFFF, 0x800)) & 0xFFF;
            }
            goto move;
        case 3:
        back:
            dx   = wp->position.x - ctl->node_3C->x_4;
            dz   = wp->position.z - ctl->node_3C->z_6;
            dist = dx * dx + dz * dz;
            if (dist > 0x200000)
            {
                wp->routine_3 = 4;
                wp->anim_AC   = 6;
                wp->speed_44  = 0;
                ctl->timer_4  = 0xA;
                goto wait;
            }
        move:
            if (wp->speed_44 < D_8013179C[wp->type])
            {
                wp->speed_44 += wp->accel_4C;
            }
            Obj_pos_set(wp, -wp->speed_44, 0, 0);
            break;
        case 4:
        wait:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_1             = 5;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->flags_0 &= ~0x20;
                if (!(ctl->flags_0 & 0x40))
                {
                    ctl->mask_50 |= 0x8000 >> ((ctl->dir_4A + 2) & 3);
                }
                func_80116528(wp);
                ctl->value_52 = 0x78;
                ctl->flags_0 &= ~0x40;
            }
            break;
    }
}

void func_801157E4(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 dx;
    sint32 dz;
    sint16 dir;
    uint8 previous;
    sint32 dist;
    STCOM_SVECTOR unused; // Retail reserves this eight-byte local.

    dist = -1;
    ctl  = &wp->ctl;
    switch (wp->routine_3)
    {
        case 0:
            wp->routine_3 = 2;
            wp->accel_4C  = D_801317A4[wp->type] >> 1;
            wp->ctl.flags_0 |= 0x100;
            if ((wp->ctl.flags_0 & 0x40) && wp->ctl.node_3C->link_C[(wp->ctl.dir_4A + 2) & 3] != dist)
            {
                wp->routine_3 = 3;
                wp->ctl.mask_50 |= 0x8000 >> ((wp->ctl.value_4B + 2) & 3);
                goto back;
            }
            ctl->flags_0 &= ~0x40;
            // fall through
        case 2:
            dx   = wp->position.x - ctl->node_38->x_4;
            dz   = wp->position.z - ctl->node_38->z_6;
            dist = dx * dx + dz * dz;
            if (dist < 0x200000)
            {
                if (func_801160F8(wp) != 4)
                {
                    wp->routine_3 = 3;
                    dir           = ctl->dir_4A;
                }
                else
                {
                    dir = func_80115E98(wp);
                    if (ctl->dir_4A != dir)
                    {
                        wp->routine_1             = 4;
                        *(uint16 *)&wp->routine_2 = 0;
                        ctl->flags_0 |= 0x40;
                        ctl->part_34->u_E.b.byte_E |= 4;
                    }
                }
                ctl->node_id_49  = ctl->node_38->id_0;
                ctl->node_3C     = ctl->node_38;
                ctl->node_38     = &D_80131790[wp->type][ctl->node_38->link_C[dir]];
                ctl->target_40.x = ctl->node_38->x_4;
                ctl->target_40.y = 0;
                ctl->target_40.z = ctl->node_38->z_6;
                dir &= 3;
                previous      = ctl->dir_4A;
                ctl->dir_4A   = dir;
                ctl->value_4B = previous;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &ctl->target_40, (wp->rotation.y + 0x800) & 0xFFF, 0x800)) & 0xFFF;
            }
            goto move;
        case 3:
        back:
            dx   = wp->position.x - ctl->node_3C->x_4;
            dz   = wp->position.z - ctl->node_3C->z_6;
            dist = dx * dx + dz * dz;
            if (dist > 0x200000)
            {
                wp->routine_3 = 4;
                wp->anim_AC   = 6;
                wp->speed_44  = 0;
                ctl->timer_4  = 0xA;
                goto wait;
            }
        move:
            if (wp->speed_44 < D_8013179C[wp->type])
            {
                wp->speed_44 += wp->accel_4C;
            }
            Obj_pos_set(wp, -wp->speed_44, 0, 0);
            break;
        case 4:
        wait:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_1             = 5;
                *(uint16 *)&wp->routine_2 = 0;
                ctl->flags_0 &= ~0x20;
                if (!(ctl->flags_0 & 0x40))
                {
                    ctl->mask_50 |= 0x8000 >> ((ctl->dir_4A + 2) & 3);
                }
                func_80116528(wp);
                ctl->value_52 = 0x78;
                ctl->flags_0 &= ~0x40;
            }
            break;
    }
}

void func_80115B98(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 6;
            wp->speed_44  = 0;
            ctl->timer_4  = 0xA;
            ctl->value_8  = 0;
            ctl->part_34->u_E.b.byte_E |= 5;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            ctl->timer_4  = 0x78;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            // fall through
        case 3:
            if (wp->value_80 > 0x120000)
            {
                ctl->flags_0 |= 1;
                ctl->part_34->u_E.b.byte_E &= ~5;
            }
            break;
    }
}

void func_80115CA4(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    STCOM_EFFECT *fx;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2                       = 1;
            wp->anim_AC                         = 0xD;
            ctl->timer_4                        = 0x3C;
            ctl->value_8                        = 0;
            ctl->part_34->routine_1             = 2;
            *(uint16 *)&ctl->part_34->routine_2 = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->be_flag         = 5;
                    fx->id              = 0x80;
                    fx->type            = 0x42;
                    fx->sprite.position = wp->pos_180;
                }
                if (ctl->flags_0 & 0x200)
                {
                    func_80031824(wp);
                }
                wp->u_E.b.byte_E = 0;
                wp->u_E.b.byte_F = 0;
                wp->be_flag &= ~3;
                func_80047148(wp, &wp->position);
            }
            break;
    }
}

void func_80115DD8(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2 = 1;
            wp->anim_AC   = 6;
            wp->speed_44  = 0;
            ctl->timer_4  = 0xA;
            ctl->value_8  = 0;
            ctl->flags_0 &= ~0x100;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 2;
            // fall through
        case 2:
            if (!(ctl->part_34->u_E.b.byte_E & 2) || (ctl->part_34->u_E.b.byte_E & 0x40))
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

const ST05_DIRS D_801004E0 = {{0, 0, 0, 0}};

sint32 func_80115E98(ST05_WALKER *wp)
{
    ST05_DIRS open;
    ST05_WALKER_CTL *ctl;
    uint8 *p;
    sint16 count;
    sint16 pick;
    sint16 i;
    uint32 dir;
    sint32 link;

    open = D_801004E0;
    ctl  = &wp->ctl;
    if (wp->type == 1)
    {
        dir  = (uint32)((Angle_xz_svector(&wp->position, &Player_work.position) + 0x200) & 0xFFF) >> 10;
        link = wp->ctl.node_38->link_C[dir];
        if (link != -1 && wp->ctl.node_id_49 != link && !(wp->ctl.mask_50 & (0x8000 >> dir)))
        {
            open.dir[dir] = 1;
            count         = 1;
            goto choose;
        }
    }
    count = 0;
    for (i = 0; i < 4; i++)
    {
        link = ctl->node_38->link_C[i];
        if (link != -1 && ctl->node_id_49 != link && !(ctl->mask_50 & (0x8000 >> i)))
        {
            open.dir[i] = 1;
            count++;
        }
        // An empty statement (found by the permuter) keeps retail's delay-slot fill.
        do
        {
        } while (0);
    }
    if (wp->type == 0)
    {
        p = &open.dir[(uint32)((Angle_xz_svector(&wp->position, &Player_work.position) + 0x200) & 0xFFF) >> 10];
        if (*p != 0 && count >= 2)
        {
            *p = 0;
            count--;
        }
    }
choose:
    ctl->mask_50 = 0;
    if (count == 0)
    {
        return 4;
    }
    pick  = (ctl->random_2 & 3) % count;
    count = 0;
    for (i = 0; i < 4; i++)
    {
        count += open.dir[i];
        if (pick < count)
        {
            break;
        }
    }
    return i;
}

sint16 func_801160F8(ST05_WALKER *wp)
{
    ST05_DIRS open;
    sint16 count;
    sint16 pick;
    sint16 sum;
    sint16 i;
    sint32 left;
    sint32 right;

    open  = D_801004E0;
    count = 0;
    left  = (wp->ctl.dir_4A - 1) & 3;
    if (wp->ctl.node_38->link_C[left] != -1)
    {
        open.dir[left] = 1;
        count          = 1;
    }
    right = (wp->ctl.dir_4A + 1) & 3;
    if (wp->ctl.node_38->link_C[right] != -1)
    {
        open.dir[right] = 1;
        count++;
    }
    if (wp->ctl.node_38->link_C[wp->ctl.dir_4A] == -1 || count == 0)
    {
        return 4;
    }
    pick = (wp->ctl.random_2 & 3) % count;
    sum  = 0;
    for (i = 0; i < 4; i++)
    {
        sum += open.dir[i];
        if (pick < sum)
        {
            break;
        }
    }
    return i;
}

sint32 func_80116254(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 damage;

    ctl    = &wp->ctl;
    damage = ctl->hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (ctl->hit_14 & 0x38000000)
        {
            wp->ctl.part_34->u_E.b.byte_F |= 1;
            if ((wp->value_6E <= 0 || (wp->value_B2 = wp->value_6E, (wp->value_6E -= damage) <= 0)) &&
                !(wp->ctl.part_34->u_E.b.byte_E & 0x80))
            {
                Sound_call2(0xA2, &wp->position);
                wp->routine_1                 = 8;
                *(uint16 *)&wp->routine_2     = 0;
                wp->ctl.flags_0               = (wp->ctl.flags_0 & ~2) | 4;
                wp->ctl.part_34->u_E.b.byte_E = 0x40;
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
            ctl->part_34->u_E.b.byte_F |= 2;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    return 1;
}

sint32 func_80116380(ST05_WALKER *wp)
{
    ST05_WALKER_CTL *ctl;
    sint32 damage;

    ctl    = &wp->ctl;
    damage = ctl->hit_14 & 0xFFFFFF;
    if (damage != 0)
    {
        if (ctl->hit_14 & 0x38000000)
        {
            wp->ctl.part_34->u_E.b.byte_F |= 1;
            if ((wp->ctl.life_54 -= damage) <= 0 && !(wp->ctl.part_34->u_E.b.byte_E & 0x80))
            {
                Sound_call2(0xA2, &wp->position);
                Sce_flag_on(0x605);
                if (Sce_flag_test(0x610) == 0)
                {
                    MojiTaskExec2(4, 5);
                    Sce_flag_on(0x610);
                    D_80138078 = 0;
                    D_80138080 = 8;
                    D_80138020 = *(uint8 *)0x1F800000;
                }
            }
            else
            {
                Sound_call2(0xA0, &wp->position);
            }
            wp->scale.v.pad = 0x7FFF;
            ctl->part_34->u_E.b.byte_F |= 2;
        }
        else
        {
            Sound_call2(0xA3, &wp->position);
        }
    }
    if (Sce_flag_test(0x605) != 0)
    {
        wp->routine_0                       = 1;
        wp->routine_1                       = 5;
        *(uint16 *)&wp->routine_2           = 0;
        ctl->part_34->routine_1             = 0;
        *(uint16 *)&ctl->part_34->routine_2 = 0;
        func_8005D620(wp, 0, D_801317CC[wp->type], 0x60, D_801317D0[wp->type]);
    }
    return 1;
}

void func_80116528(ST05_WALKER *wp)
{
    ST05_NODE *node;

    wp->ctl.node_id_49  = wp->ctl.node_38->id_0;
    wp->ctl.target_40.x = wp->ctl.node_3C->x_4;
    wp->ctl.target_40.y = 0;
    wp->ctl.target_40.z = wp->ctl.node_3C->z_6;
    node                = wp->ctl.node_38;
    wp->ctl.node_38     = wp->ctl.node_3C;
    wp->ctl.node_3C     = node;
    wp->ctl.dir_4A      = (wp->ctl.dir_4A + 2) & 3;
}
