#include "common.h"
#include "st05.h"

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
                wp->routine_1 = D_801317C8[wp->variant_3];
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
    STAGE_TABLE_3C0[part->kind_2][part->value_4](part);
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

    temp_v0       = wp->variant_3;
    wp->routine_2 = temp_v0;
    D_80131424[temp_v0](wp);
}

void func_8011472C(ST05_WALKER *wp)
{
    uint8 temp_v0;

    temp_v0       = wp->variant_3;
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
            wp->speed_44  = (sint16)D_8013179C[wp->variant_3] >> 1;
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
            if (((sint16)D_8013179C[wp->variant_3] >> 1) < wp->speed_44)
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
            if (((sint16)D_8013179C[wp->variant_3] >> 1) < wp->speed_44)
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
            wp->accel_4C  = D_801317A4[wp->variant_3] >> 1;
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
                ctl->node_38     = &D_80131790[wp->variant_3][ctl->node_38->link_C[dir]];
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
            if (wp->speed_44 < D_8013179C[wp->variant_3])
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
            wp->accel_4C  = D_801317A4[wp->variant_3] >> 1;
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
                ctl->node_38     = &D_80131790[wp->variant_3][ctl->node_38->link_C[dir]];
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
            if (wp->speed_44 < D_8013179C[wp->variant_3])
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
            wp->accel_4C  = D_801317A4[wp->variant_3] >> 1;
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
                ctl->node_38     = &D_80131790[wp->variant_3][ctl->node_38->link_C[dir]];
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
            if (wp->speed_44 < D_8013179C[wp->variant_3])
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
            wp->accel_4C  = D_801317A4[wp->variant_3] >> 1;
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
                ctl->node_38     = &D_80131790[wp->variant_3][ctl->node_38->link_C[dir]];
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
            if (wp->speed_44 < D_8013179C[wp->variant_3])
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
            wp->accel_4C  = D_801317A4[wp->variant_3] >> 1;
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
                ctl->node_38     = &D_80131790[wp->variant_3][ctl->node_38->link_C[dir]];
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
            if (wp->speed_44 < D_8013179C[wp->variant_3])
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
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 0x42;
                    fx->sprite.position = wp->pos_180;
                }
                if (ctl->flags_0 & 0x200)
                {
                    func_80031824(wp);
                }
                wp->u_E.b.byte_E = 0;
                wp->u_E.b.byte_F = 0;
                wp->flags_0 &= ~3;
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
    if (wp->variant_3 == 1)
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
    if (wp->variant_3 == 0)
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
        func_8005D620(wp, 0, D_801317CC[wp->variant_3], 0x60, D_801317D0[wp->variant_3]);
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
