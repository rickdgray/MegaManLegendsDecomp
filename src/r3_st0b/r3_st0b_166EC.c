#include "common.h"
#include "st0b.h"

void func_801166EC(STAGE_OBJ *wp)
{
    D_8011C16C[wp->routine_0](wp);
}

#ifdef __wasm32__
void func_80117938(STAGE_OBJ *wp);
#endif

void func_80116728(ST0B_EVENT *wp)
{
    ST0B_PL *pl;

    if (Sce_flag_test(0x1D) != 0 || STAGE_GAME.value_52 != 5)
    {
        wp->routine_0 = 2;
        return;
    }
    if (STAGE_SCENE_BYTE(0) != 0)
    {
        return;
    }
    ST0B_GAME_174       = 0;
    STAGE_GAME.value_5E = D_80098928[0x12]->value_8 << 4;
    wp->flags_6 |= 0x20;
    if (Sce_flag_test(0x1B) == 0)
    {
        STAGE_GAME.value_5C = STAGE_GAME.value_5E;
        wp->variant_3       = 0;
    }
    else
    {
        if (Sce_flag_test(0x1C) == 0)
        {
            wp->variant_3 = 1;
            Sce_flag_on(0x1C);
            func_80017C30(2);
        }
        else
        {
            wp->variant_3       = 2;
            STAGE_GAME.value_5C = STAGE_GAME.value_5E;
        }
        Sound_call(0x10, 0, 0);
    }
    Sound_call(0x100, 0, 0);
    func_8005D844(0, 0, D_80098928[0x12]->value_A);
    func_80117938((STAGE_OBJ *)wp);
    if (wp->variant_3 != 0)
    {
        func_80117A74(wp);
    }
    pl            = ST0B_PL_PTR;
    pl->value_449 = -1;
    pl->flags_0 |= 3;
    if (wp->variant_3 == 0)
    {
        pl->position.x = 0x3200;
        pl->position.y = -0x262;
        pl->position.z = 0x400;
        pl->rotation.y = 0x400;
    }
    else
    {
        pl->position.x = 0xA00;
        pl->position.y = -0x262;
        pl->position.z = -0x2000;
        pl->rotation.y = 0x600;
    }
    pl->rotation.z          = 0;
    pl->rotation.x          = 0;
    pl->position_fixed.x    = pl->position.x << 16;
    pl->position_fixed.y    = pl->position.y << 16;
    pl->position_fixed.z    = pl->position.z << 16;
    pl->position_prev       = pl->position;
    pl->position_fixed_prev = pl->position_fixed;
    pl->rotation_prev       = pl->rotation;
    pl->value_76            = 1;
    pl->value_74            = 0;
    pl->held_C0             = D_80120364;
    wp->timer_1C            = 0;
    D_800A395E[0]           = 1;
    STAGE_GAME.value_83     = 1;
    wp->routine_0           = 1;
    wp->value_C             = 0;
    switch (wp->variant_3)
    {
        case 0:
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            break;
        case 1:
            wp->routine_1 = 2;
            wp->routine_2 = 0;
            break;
        case 2:
            wp->routine_1 = 4;
            wp->routine_2 = 0;
            break;
        default:
            wp->routine_2 = 0;
            break;
    }
    wp->routine_3 = 0;
}

void func_80116A2C(STAGE_OBJ *wp)
{
    D_8011C178[wp->routine_1](wp);
}

void func_80116A68(STAGE_OBJ *wp)
{
    Close_EVE_WORK(wp);
}

void func_80116A88(ST0B_EVENT *wp)
{
    ST0B_PL *pl;
    sint32 trigger;
    sint32 i;
    STAGE_OBJ *obj;

    pl      = ST0B_PL_PTR;
    trigger = func_80117B14(wp, 0);
    switch (wp->routine_2)
    {
        case 0:
            if (wp->timer_1C < 0x14)
            {
                wp->timer_1C++;
            }
            else
            {
                MojiTaskExec2(4, 1);
                wp->timer_1C = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (trigger != 0)
            {
                func_80117C50((STAGE_OBJ *)wp, 0x2C, 0, &D_8011C204[0]);
                wp->value_C++;
                wp->timer_1C = 0;
                if (Moji_flag & 0x800000)
                {
                    func_80053AA4(4);
                    func_8001D494(0, 1, 0);
                }
                MojiTaskExec2(4, 0);
                wp->routine_2++;
            }
            break;
        case 2:
            if (trigger != 0 && !(Moji_flag & 0x800000))
            {
                wp->timer_1C = 0;
                pl->flags_BD |= 0x40;
                wp->routine_2++;
            }
            break;
        case 3:
            if (func_8004324C(pl) == 0)
            {
                Sound_call(0x101, 0, 0);
                MojiTaskExec2(0, 0x18);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x08000000))
            {
                pl->flags_BD &= ~0x40;
                Sound_call(0x100, 0, 0);
                Sound_call(0xE, 0, 0);
                wp->routine_2++;
            }
            break;
        case 5:
            if (trigger != 0)
            {
                for (i = 1; i < 4; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 6:
            if (trigger != 0)
            {
                for (i = 4; i < 7; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                for (i = 0; i < 4; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x32, i, &D_8011C2D4[i]);
                }
                MojiTaskExec2(4, 0x19);
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 7:
            if (trigger != 0)
            {
                for (i = 0; i < 4; i++)
                {
                    obj = D_801203D4[i];
                    if (obj->flags_0 != 0 && obj->kind_2 == 0x32)
                    {
                        func_80031824(obj);
                    }
                }
                for (i = 7; i < 10; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                MojiTaskExec2(4, 0x1A);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 8:
            if (wp->timer_1C < 0x258)
            {
                wp->timer_1C++;
            }
            else if (wp->timer_1C == 0x258 && STAGE_PL.position.z > 0)
            {
                MojiTaskExec2(4, 0xB);
                wp->timer_1C++;
            }
            if (trigger != 0)
            {
                for (i = 4; i < 8; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x32, i, &D_8011C2D4[i]);
                }
                MojiTaskExec2(4, 0x1B);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 9:
            if (trigger != 0)
            {
                for (i = 10; i < 13; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                MojiTaskExec2(4, 0x1A);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 10:
            if (trigger != 0)
            {
                for (i = 13; i < 17; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                MojiTaskExec2(4, 0x19);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 11:
            if (wp->timer_1C < 0x352)
            {
                wp->timer_1C++;
            }
            else if (wp->timer_1C == 0x352)
            {
                if ((sint16)STAGE_GAME.value_5E / 2 < STAGE_GAME.value_5C)
                {
                    MojiTaskExec2(4, 0xC);
                }
                wp->timer_1C++;
            }
            if (trigger != 0)
            {
                for (i = 17; i < 20; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                MojiTaskExec2(4, 0x1A);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 12:
            if (trigger != 0)
            {
                for (i = 20; i < 24; i++)
                {
                    func_80117C50((STAGE_OBJ *)wp, 0x2C, i, &D_8011C204[i]);
                }
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 13:
            if (trigger != 0)
            {
                func_80117C50((STAGE_OBJ *)wp, 0x2C, 24, &D_8011C204[24]);
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 14:
            if (trigger != 0)
            {
                func_80117C50((STAGE_OBJ *)wp, 0x2C, 25, &D_8011C204[25]);
                for (i = 4; i < 8; i++)
                {
                    if (D_801203D4[i]->flags_0 != 0 && D_801203D4[i]->kind_2 == 0x32)
                    {
                        D_801203D4[i]->u_E.b.byte_F = 1;
                    }
                }
                wp->timer_1C = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 15:
            if (trigger != 0)
            {
                wp->timer_1C  = 0;
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->value_C++;
            }
            break;
    }
    func_80117DD8(wp);
}

void func_801170A8(ST0B_EVENT *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    switch (wp->routine_2)
    {
        case 0:
            if (func_80117DFC() != 0)
            {
                pl->flags_BD |= 0x40;
                MojiTaskExec2(0, 2);
                wp->timer_1C = 0;
                wp->routine_2++;
            }
            else
            {
                wp->routine_1 = 5;
                wp->routine_2 = 0;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                Sound_call(0x101, 0, 0);
                wp->routine_2++;
            }
            break;
        case 2:
            func_8001D854(0x10);
            func_80017C30(0xA);
            wp->routine_2++;
            break;
        case 3:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                func_8005D87C();
                wp->routine_2++;
            }
            break;
        case 4:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_2++;
            }
            break;
        case 5:
            pl->value_76    = 0;
            pl->value_449   = 0;
            pl->speed_44[0] = 0;
            pl->speed_44[1] = 0;
            pl->speed_44[2] = 0;
            pl->flags_0 &= ~3;
            Sce_flag_on(0x1B);
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            break;
    }
}

void func_80117220(ST0B_EVENT *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (wp->timer_1C < 360)
            {
                wp->timer_1C++;
            }
            else
            {
                MojiTaskExec2(4, 3);
                wp->timer_1C = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (func_80117B14(wp, 1))
            {
                Player_work.flags_bd |= 0x40;
                wp->timer_1C  = 0;
                wp->routine_1 = 3;
                wp->routine_2 = 0;
                wp->value_C++;
            }
            break;
    }
    if (wp->routine_2 < 2)
    {
        func_80117DD8(wp);
    }
}

void func_80117300(ST0B_EVENT *wp)
{
    ST0B_PL *pl;

    pl = ST0B_PL_PTR;
    switch (wp->routine_2)
    {
        case 0:
            if (func_80117DFC() != 0)
            {
                pl->flags_BD |= 0x40;
                wp->routine_2++;
            }
            else
            {
                wp->routine_1 = 5;
                wp->routine_2 = 0;
            }
            break;
        case 1:
            if (func_8004324C(pl) == 0)
            {
                Obj_work_flag_change(0x7F, 1);
                if (Moji_flag & 0x08000000)
                {
                    func_80053AA4(0);
                    func_8001D494(0, 1, 0);
                }
                MojiTaskExec2(0, 4);
                Sound_call(0x101, 0, 0);
                wp->timer_1C = 0;
                wp->routine_2++;
            }
            break;
        case 2:
            if (!(Moji_flag & 0x08000000))
            {
                Obj_work_flag_change(0x7F, 2);
                if (Sce_flag_test(0x604) != 0)
                {
                    MojiTaskExec2(4, 5);
                    wp->routine_2 = 4;
                }
                else
                {
                    MojiTaskExec2(4, 6);
                    Sound_call(0x100, 0, 0);
                    wp->routine_2 = 3;
                }
            }
            break;
        case 3:
            STAGE_GAME.value_174 = 0;
            pl->flags_BD &= ~0x40;
            wp->routine_1 = 4;
            wp->routine_2 = 0;
            break;
        case 4:
            if (!(Moji_flag & 0x800000))
            {
                func_8001D854(0x10);
                func_80017C30(0xA);
                wp->routine_2++;
            }
            break;
        case 5:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                func_8005D87C();
                wp->routine_2++;
            }
            break;
        case 6:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_2++;
            }
            break;
        case 7:
            pl->value_76    = 0;
            pl->value_449   = 0;
            pl->speed_44[0] = 0;
            pl->speed_44[1] = 0;
            pl->speed_44[2] = 0;
            pl->flags_0 &= ~3;
            Sce_flag_on(0x1F);
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            break;
    }
}

void func_8011754C(ST0B_EVENT *wp)
{
    ST0B_PL *pl;

    pl = ST0B_PL_PTR;
    switch (wp->routine_2)
    {
        case 0:
            if (Game_work.value_51 == 3)
            {
                wp->value_C = 0;
                wp->routine_2++;
            }
            break;
        case 1:
            if (func_80117B14(wp, 2) != 0)
            {
                MojiTaskExec2(4, 7);
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 2:
            if (func_80117B14(wp, 2) != 0)
            {
                if (Moji_flag & 0x800000)
                {
                    func_80053AA4(4);
                    func_8001D494(0, 1, 0);
                }
                MojiTaskExec2(4, 9);
                func_8005D620(D_80120368, 0, 0, 0x50, 0x2C400040);
                D_80120368->u_E.b.byte_E = 1;
                wp->timer_1C             = 0;
                wp->routine_3            = 0;
                wp->value_C++;
                wp->routine_2++;
            }
            break;
        case 3:
            func_80117E2C(wp);
            if (D_80120368->life_6E <= 0)
            {
                if (func_80117DFC() != 0)
                {
                    if (Moji_flag & 0x800000)
                    {
                        func_80053AA4(4);
                        func_8001D494(0, 1, 0);
                    }
                    wp->routine_3 = 0;
                    wp->routine_2++;
                }
                else
                {
                    wp->routine_1 = 5;
                    wp->routine_2 = 0;
                }
            }
            break;
        case 4:
            if (func_80042238(pl) != 0)
            {
                MojiTaskExec2(0, 0x1F);
                wp->routine_2++;
            }
            break;
        case 5:
            if (!(Moji_flag & 0x08000000))
            {
                func_8001D854(0x10);
                Sound_call(0x101, 0, 0);
                func_80017C30(0xA);
                wp->routine_2++;
            }
            break;
        case 6:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                D_80120368->routine_0 = 2;
                func_8005D87C();
                func_8005D6E8(D_80120368);
                wp->routine_2++;
            }
            break;
        case 7:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                wp->routine_2++;
            }
            break;
        case 8:
            Sce_flag_on(0x1D);
            wp->routine_0 = 2;
            wp->routine_1 = 0;
            wp->routine_2 = 0;
            break;
    }
    if (wp->routine_2 < 4)
    {
        func_80117DD8(wp);
    }
}

void func_80117830(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            Pl00_shot_enable_off(&Player_work);
            STAGE_PL.value_449 = 1;
            STAGE_PL.value_175 = 0;
            func_8001D854(0x10);
            if (Moji_flag & 0x08000000)
            {
                func_80053AA4(0);
                func_8001D494(0, 1, 0);
            }
            MojiTaskExec2(0, 0x12);
            wp->routine_2++;
            break;
        case 1:
            if (!(Moji_flag & 0x08000000))
            {
                Sound_call(0x101, 0, 0);
                Game_work.mode_0   = 0xA;
                STAGE_GAME.value_1 = 0;
                wp->routine_0      = 2;
                wp->routine_1      = 0;
                wp->routine_2      = 0;
            }
            break;
    }
}

void func_80117938(STAGE_OBJ *wp)
{
    STAGE_OBJ *obj;

    obj = (STAGE_OBJ *)func_80031518();
    if (obj != NULL)
    {
        obj->flags_0 = 1;
        obj->kind_2  = 0x12;
        if (wp->variant_3 == 0)
        {
            obj->position.x = 0x3200;
            obj->variant_3  = 1;
            obj->position.z = 0x400;
            obj->rotation.y = 0x400;
        }
        else
        {
            obj->variant_3  = 2;
            obj->position.x = 0xA00;
            obj->position.z = -0x2000;
            obj->rotation.y = 0x600;
            obj->flags_6 |= 0x20;
        }
        obj->position.y          = -1;
        obj->rotation.z          = 0;
        obj->rotation.x          = 0;
        obj->value_44.half[0]    = 0;
        obj->value_44.half[1]    = 0;
        obj->value_48.half[0]    = 0;
        obj->position_fixed.v.x  = obj->position.x << 16;
        obj->position_fixed.v.y  = obj->position.y << 16;
        obj->position_fixed.v.z  = obj->position.z << 16;
        obj->position_prev       = obj->position;
        obj->position_fixed_prev = obj->position_fixed.v;
        obj->rotation_prev       = obj->rotation;
        D_80120364               = obj;
    }
}

void func_80117A74(ST0B_EVENT *wp)
{
    STAGE_OBJ *obj;

    obj = func_80031498();
    if (obj != NULL)
    {
        obj->flags_0            = 1;
        obj->value_4            = 1;
        obj->kind_2             = 0xC;
        obj->variant_3          = 0;
        obj->position.x         = -0x200;
        obj->position.y         = -1;
        obj->position.z         = -0x1600;
        obj->position_fixed.v.x = obj->position.x << 16;
        obj->position_fixed.v.y = obj->position.y << 16;
        obj->position_fixed.v.z = obj->position.z << 16;
        obj->rotation.y         = 0xC00;
        obj->u_C.b.byte_C       = D_80120364->value_1;
        obj->u_E.b.byte_F       = 1;
        D_80120368              = obj;
    }
}

sint32 func_80117B14(ST0B_EVENT *wp, sint32 arg)
{
    ST0B_ZONE *zone;
    STCOM_SVECTOR *pos;
    sint16 in;
    sint32 ret;

    ret = 0;
    switch (arg)
    {
        case 0:
            zone = &D_8011C190[(sint8)wp->value_C];
            break;
        case 1:
            zone = &D_8011C1E4[(sint8)wp->value_C];
            break;
        default:
            zone = &D_8011C1F0[(sint8)wp->value_C];
            break;
    }
    if (zone->kind_0 == 0xFF)
    {
        return 0;
    }
    pos = &Player_work.position;
    if (zone->kind_0 == 1)
    {
        if (zone->type_1 == 3)
        {
            if (Player_work.position.z > zone->z_4)
            {
                ret = 1;
            }
        }
        else if (Player_work.position.z < zone->z_4)
        {
            ret = 1;
        }
    }
    else
    {
        if (zone->kind_0 == 0)
        {
            in = pos->x > zone->x_2;
        }
        else
        {
            in = pos->x < zone->x_2;
        }
        if (in)
        {
            if (zone->type_1 == 3)
            {
                if (Player_work.position.z > zone->z_4)
                {
                    ret = 1;
                }
            }
            else if (zone->type_1 == 5)
            {
                if (Player_work.position.z < zone->z_4)
                {
                    ret = 1;
                }
            }
            else
            {
                ret = 1;
            }
        }
    }
    return ret;
}

void func_80117C50(STAGE_OBJ *owner, sint32 kind, sint32 index, ST0B_PLACE *place)
{
    STAGE_OBJ *obj;
    ST0B_SETUP_2C *setup;

    obj = func_80031418();
    if (obj != NULL)
    {
        obj->flags_0            = 1;
        obj->position.x         = place->x;
        obj->position.y         = place->y;
        obj->position.z         = place->z;
        obj->position_fixed.v.x = obj->position.x << 16;
        obj->position_fixed.v.y = obj->position.y << 16;
        obj->position_fixed.v.z = obj->position.z << 16;
        obj->rotation.z         = 0;
        obj->rotation.x         = 0;
        obj->rotation.y         = place->angle;
        if (kind == 0x2C)
        {
            D_8012036C[index] = obj;
            obj->kind_2       = 0x2C;
            setup             = &D_8011C334[index];
            obj->value_4      = 0;
            obj->variant_3    = setup->variant_0;
            obj->u_C.b.byte_C = setup->value_4[0];
            obj->u_C.b.byte_D = setup->value_4[1];
            obj->u_E.b.byte_E = setup->value_4[2];
            obj->u_E.b.byte_F = setup->value_4[3];
        }
        else
        {
            D_801203D4[index] = obj;
            obj->kind_2       = 0x32;
            obj->variant_3    = 0;
            obj->value_4      = 2;
            obj->u_C.b.byte_C = D_8011C314[index].value_0[0];
            obj->u_C.b.byte_D = D_8011C314[index].value_0[1];
            obj->u_E.b.byte_E = D_8011C314[index].value_0[2];
        }
        obj->owner_308 = owner;
    }
}

void func_80117DD8(ST0B_EVENT *wp)
{
    if (STAGE_GAME.value_5C == 0)
    {
        wp->routine_1 = 5;
        wp->routine_2 = 0;
    }
}

sint32 func_80117DFC(void)
{
    if (STAGE_GAME.value_5C > 0)
    {
        STAGE_GAME.value_174 = 0xFFFF;
        return 1;
    }
    return 0;
}

void func_80117E2C(ST0B_EVENT *wp)
{
    switch (wp->routine_3)
    {
        case 0:
            if (wp->timer_1C < 0x3C)
            {
                wp->timer_1C++;
                break;
            }
            func_8001D854(0x10);
            wp->timer_1C = 0;
            wp->routine_3++;
            break;
        case 1:
            if (D_80098788 == 0)
            {
                Sound_call(0x2A, 0, 0);
                wp->routine_3++;
            }
            break;
        case 2: // an idle state: the switch needs it for retail's compare tree
            break;
    }
}

void func_80117ED0(STAGE_OBJ *wp)
{
    D_8011C404[wp->routine_0](wp);
}

void func_80117F0C(STAGE_OBJ *wp)
{
    wp->routine_1    = 0;
    wp->routine_2    = 0;
    wp->routine_3    = 0;
    wp->u_C.b.byte_C = 0;
    wp->u_C.b.byte_D = 0;
    wp->routine_0++;
}

// Scrolls four textures in VRAM: two 0x40-line strips by 2 lines a frame, two 0x20-line strips by 1.
void func_80117F30(STAGE_OBJ *wp)
{
    RECT rect;
    ST0B_DR_MOVE *p;
    sint32 ofs;

    ofs    = wp->routine_2;
    p      = ST0B_PACKET_PTR++;
    rect.x = 0x2D0;
    rect.y = 0x140 + ofs;
    rect.w = 0x10;
    rect.h = 0x40 - ofs;
    SetDrawMove(p, &rect, 0x2D0, 0x100);
    addPrim(&ST0B_LINK_PTR->ot_88, p);
    if (ofs != 0)
    {
        p      = ST0B_PACKET_PTR++;
        rect.y = 0x140;
        rect.h = ofs;
        SetDrawMove(p, &rect, 0x2D0, 0x140 - ofs);
        addPrim(&ST0B_LINK_PTR->ot_88, p);
    }
    if (ofs == 0)
    {
        wp->routine_2 = 0x3E;
    }
    else
    {
        wp->routine_2 -= 2;
    }
    ofs    = wp->routine_3;
    p      = ST0B_PACKET_PTR++;
    rect.x = 0x2C8;
    rect.y = 0x120 + ofs;
    rect.w = 8;
    rect.h = 0x20 - ofs;
    SetDrawMove(p, &rect, 0x2C8, 0x100);
    addPrim(&ST0B_LINK_PTR->ot_88, p);
    if (ofs != 0)
    {
        p      = ST0B_PACKET_PTR++;
        rect.y = 0x120;
        rect.h = ofs;
        SetDrawMove(p, &rect, 0x2C8, 0x120 - ofs);
        addPrim(&ST0B_LINK_PTR->ot_88, p);
    }
    if (ofs == 0)
    {
        wp->routine_3 = 0x1F;
    }
    else
    {
        wp->routine_3 -= 1;
    }
    ofs    = wp->u_C.b.byte_C;
    p      = ST0B_PACKET_PTR++;
    rect.x = 0x370;
    rect.y = 0x140 + ofs;
    rect.w = 0x10;
    rect.h = 0x40 - ofs;
    SetDrawMove(p, &rect, 0x370, 0x100);
    addPrim(&ST0B_LINK_PTR->ot_88, p);
    if (ofs != 0)
    {
        p      = ST0B_PACKET_PTR++;
        rect.y = 0x140;
        rect.h = ofs;
        SetDrawMove(p, &rect, 0x370, 0x140 - ofs);
        addPrim(&ST0B_LINK_PTR->ot_88, p);
    }
    if (ofs == 0)
    {
        wp->u_C.b.byte_C = 0x3E;
    }
    else
    {
        wp->u_C.b.byte_C -= 2;
    }
    ofs    = wp->u_C.b.byte_D;
    p      = ST0B_PACKET_PTR++;
    rect.x = 0x368;
    rect.y = 0x160 + ofs;
    rect.w = 8;
    rect.h = 0x20 - ofs;
    SetDrawMove(p, &rect, 0x368, 0x140);
    addPrim(&ST0B_LINK_PTR->ot_88, p);
    if (ofs != 0)
    {
        p      = ST0B_PACKET_PTR++;
        rect.y = 0x160;
        rect.h = ofs;
        SetDrawMove(p, &rect, 0x368, 0x160 - ofs);
        addPrim(&ST0B_LINK_PTR->ot_88, p);
    }
    if (ofs == 0)
    {
        wp->u_C.b.byte_D = 0x1F;
    }
    else
    {
        wp->u_C.b.byte_D -= 1;
    }
}

void func_801183FC(void)
{
}

void func_80118404(STAGE_FX *wp)
{
    wp->value_38.words.fraction += 2;
    wp->value_38.words.integer--;
    if (wp->value_38.words.integer == -100)
    {
        wp->routine_1++;
    }
}

void func_80118448(void)
{
}

void func_80118450(STAGE_FX *wp)
{
    wp->value_38.words.fraction -= 2;
    wp->value_38.words.integer++;
    if (wp->value_38.words.integer == 0)
    {
        wp->routine_1 = 0;
    }
}

void func_8011847C(STAGE_OBJ *wp)
{
    D_8011C40C[wp->routine_1](wp);
}

void func_801184B8(void)
{
}

void func_801184C0(STAGE_FX *wp)
{
    wp->value_38.words.fraction -= 2;
    wp->value_38.words.integer++;
    if (wp->value_38.words.integer == 100)
    {
        wp->routine_1++;
    }
}

void func_80118504(void)
{
}

void func_8011850C(STAGE_FX *wp)
{
    wp->value_38.words.fraction += 2;
    wp->value_38.words.integer--;
    if ((sint16)wp->value_38.words.fraction == 0)
    {
        wp->routine_1 = 0;
    }
}

void func_8011853C(STAGE_OBJ *wp)
{
    D_8011C41C[wp->routine_1](wp);
}

void func_80118578(void)
{
}

void func_80118580(STAGE_OBJ *wp)
{
    wp->u_C.timer += 0x11;
}

void func_80118594(STAGE_OBJ *wp)
{
    if (wp->routine_1 == 0)
    {
        func_80118578();
        return;
    }
    func_80118580(wp);
}

void func_801185D4(ST0B_WHEEL *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_SVECTOR unused_sv; // unused: retail's frame has room for it and the two matrices below
    STAGE_PANEL_MATRIX rot;
    STAGE_PANEL_MATRIX unused_m[2];
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 4;
        func_8002F9C4(wp, &wp->variant_3);
        wp->value_10 = 0;
        wp->color_40 = 0x808080;
        wp->routine_0++;
    }
    D_8011C42C[wp->variant_3](wp);
    wp->matrix.words[0] = 0x1000;
    wp->matrix.words[1] = 0;
    wp->matrix.words[2] = 0x1000;
    wp->matrix.words[3] = 0;
    wp->matrix.words[4] = 0x1000;
    wp->matrix.words[5] = 0;
    wp->matrix.words[6] = 0;
    wp->matrix.words[7] = 0;
    scale.x = scale.y = scale.z = 0x1000;
    ScaleMatrix(&wp->matrix.m, &scale);
    rot.words[0] = 0x1000;
    rot.words[2] = 0x1000;
    rot.words[4] = 0x1000;
    rot.words[1] = 0;
    rot.words[3] = 0;
    rot.words[5] = 0;
    rot.words[6] = 0;
    rot.words[7] = 0;
    RotMatrixZ(wp->angle_C, &rot.m);
    MulMatrix(&wp->matrix.m, &rot.m);
}

void func_801186E8(uint8 arg0)
{
    D_800C356C = -1;
    D_800C356F = arg0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
    D_800C356E = (uint8)Game_work.value_50;
}

void func_80118730(ST0B_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        wp->value_448 = 0;
        wp->u_C.b.byte_D++;
    }
}

void func_80118758(ST0B_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    switch (temp_v1)
    {
        case 0:
            wp->value_448    = 0xD;
            wp->u_E.b.byte_E = 0;
            wp->u_C.b.byte_D++;
            return;
        case 1:
            wp->u_E.b.byte_E++;
            wp->value_430 += 0xFFFB0000;
            if (wp->u_E.b.byte_E == 0x1E)
            {
                wp->u_C.b.byte_C = 0;
                wp->u_C.b.byte_D = 0;
            }
            return;
    }
}

void func_801187D4(ST0B_OBJ *wp)
{
    sint8 temp_v1;

    temp_v1 = wp->u_C.b.byte_D;
    switch (temp_v1)
    {
        case 0:
            wp->value_448 = 0xC;
            wp->u_C.b.byte_D++;
            return;
        case 1:
            wp->value_430 += 0x50000;
            return;
    }
}

void func_80118824(ST0B_OBJ *wp)
{
    if (wp->u_C.b.byte_D == 0)
    {
        wp->value_448 = 0x80;
        wp->value_168 = 0;
        wp->value_169 = 0;
        wp->u_C.b.byte_D++;
    }
}

void func_80118854(STAGE_PL_SCRIPT *wp)
{
    D_80120314[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_801188B4(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(2);
            STAGE_PL.fixed_428.x = 0xFE000000;
            STAGE_PL.fixed_428.z = 0xFE000000;
            STAGE_PL.fixed_428.y = 0xFEFF0000;
        }
        else
        {
            func_801186E8(0);
            STAGE_PL.fixed_428.x = 0xC000000;
            STAGE_PL.fixed_428.z = 0x14000000;
            STAGE_PL.fixed_428.y = 0xFFFF0000;
        }
        pl->value_442 = 0x800;
    }
    if (wp->frame_10 == 0xA)
    {
        pl->routine_C = 1;
        pl->value_D   = 0;
    }
}

void func_80118978(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;
    STAGE_FX *fx;

    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(6);
        }
        else
        {
            func_801186E8(1);
        }
        child          = wp->child_24;
        child->flags_0 = (uint8)child->flags_0 | 2;
    }
    if (wp->frame_10 == 5)
    {
        fx = (STAGE_FX *)func_80031618();
        if (fx != NULL)
        {
            fx->flags_0 = 1;
            fx->kind_2  = 5;
            fx->value_C = 5;
            fx->frame_E = 2;
            fx->x_1C    = 0x85;
            fx->y_1E    = -0x16E;
            fx->timer_D = 0;
            fx->z_20    = -0xC8;
        }
    }
    if (wp->frame_10 == 0x72)
    {
        child            = wp->child_24;
        child->routine_1 = 1;
    }
    if (wp->frame_10 == 0xAC)
    {
        child            = wp->child_24;
        child->routine_1 = 0;
    }
}

void func_80118A74(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(2);
        }
        else
        {
            func_801186E8(0);
        }
        wp->child_24->flags_0 &= ~2;
        pl->routine_C = 3;
        pl->value_D   = 0;
    }
    if (wp->frame_10 == 1)
    {
        pl->flags_0 &= ~1;
    }
    if (wp->frame_10 == 0x14)
    {
        pl->flags_0 |= 1;
    }
}

void func_80118B38(STAGE_ROOM *wp)
{
    ST0B_PL *pl;

    pl = (ST0B_PL *)&Player_work;
    if (wp->frame_10 == 0)
    {
        wp->child_28->flags_0 = (uint8)wp->child_28->flags_0 | 2;
        wp->child_2C->flags_0 = (uint8)wp->child_2C->flags_0 | 2;
        if (STAGE_GAME.value_50 == 0xB)
        {
            func_801186E8(7);
        }
        else
        {
            func_801186E8(2);
        }
        pl->fixed_428.x = 0;
        pl->fixed_428.z = 0;
        pl->fixed_428.y = 0;
        pl->value_D     = 0;
        pl->routine_C   = 0;
    }
    if (wp->frame_10 == 0xF)
    {
        wp->child_28->routine_1++;
        wp->child_2C->routine_1++;
    }
    if (wp->frame_10 == 0x46)
    {
        pl->routine_C = 2;
        pl->value_D   = 0;
    }
}

void func_80118C34(STAGE_ROOM *wp)
{
    sint32 i;

    func_8001E6C0(0, 0, 0);
    Obj_work_flag_change(0x56, 0x80);
    if (STAGE_GAME.value_50 == 0xB)
    {
        D_800BC7F0 = D_80120214;
    }
    else
    {
        D_800BC7F0 = D_80120114;
    }
    wp->tbl_A4 = D_80120324;
    for (i = 0; i < 10; i++)
    {
        func_8001EAE8(&D_801200D8[i]);
    }
    STAGE_PL.routine_0 = 3;
    STAGE_PL.routine_1 = 1;
    STAGE_PL.value_C   = 0;
}

void func_80118D00(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80118D40(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work) != 0)
            {
                func_8001D854(0x10);
                func_8001B314();
                if (STAGE_GAME.value_50 == 0xB)
                {
                    func_8001D58C(0x20010013);
                }
                else
                {
                    func_8001D58C(0x2000000E);
                }
                wp->routine_4++;
            }
            break;
        case 1:
            if (func_8001D878() != 0)
            {
                wp->timer_C = 0x17;
                wp->routine_4++;
            }
            break;
        case 2:
            if (--wp->timer_C == 0)
            {
                wp->routine_4++;
            }
            break;
        case 3:
            func_80118C34((STAGE_ROOM *)wp);
            wp->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (*(uint8 *)wp->tbl_A4 == 0xFF || func_8001DE84() != 0))
            {
                func_80017C30(0xA);
                wp->routine_4++;
            }
            // fall through
        case 5:
            func_80118D00(wp);
            func_80118854((STAGE_PL_SCRIPT *)&Player_work);
            if (D_800C356C_A[0] == -1)
            {
                D_800C3560 = STAGE_PL.fixed_428.x >> 16;
                D_800C3562 = STAGE_PL.fixed_428.y >> 16;
                D_800C3564 = STAGE_PL.fixed_428.z >> 16;
                D_800C356A = STAGE_PL.value_442;
            }
            func_8001EC0C();
            func_8001F070();
            if (wp->routine_4 == 5 && D_80098A72 == 0 && D_80098788 == 0)
            {
                if (STAGE_GAME.value_50 == 0xB)
                {
                    D_800C356C_A[0] = 2;
                    D_800C356E      = 0x14;
                    D_800C3560      = 0x100;
                    D_800C3562      = -1;
                    D_800C3564      = -0x7300;
                    D_800C356F      = 0;
                    D_800C356A      = 0;
                    D_800C356D      = 0;
                    D_800C3571      = 0xFF;
                    D_800C3570      = 2;
                }
                else
                {
                    D_800C356C_A[0] = 2;
                    D_800C356E      = 0xE;
                    D_800C3560      = -0xC6B;
                    D_800C3562      = -0x181;
                    D_800C3564      = 0xB00;
                    D_800C356A      = 0x400;
                    D_800C356F      = 0;
                    D_800C356D      = 0;
                    D_800C3571      = 0xFF;
                    D_800C3570      = 2;
                }
                wp->flags_0 = 0;
                func_8001D494(0, 1, 0);
                Player_work.flags_0 |= 1;
                func_80042314(&Player_work);
            }
            break;
    }
}
