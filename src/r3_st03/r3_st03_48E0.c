#include "common.h"
#include "st03.h"

void func_801048E0(ST03_PL *wp)
{
    STAGE_SCENE_WORK *scene;
    sint32 turn;

    scene = &Scene_work;
    switch (wp->value_D)
    {
        case 0:
            wp->pos_438.x   = 0x174B;
            wp->pos_438.y   = -1;
            wp->pos_438.z   = 0x4DA0;
            wp->rot_440.y   = 0x524;
            wp->rot_440.x   = 0;
            wp->rot_440.z   = 0;
            wp->fixed_428.x = wp->pos_438.x << 16;
            wp->fixed_428.y = wp->pos_438.y << 16;
            wp->fixed_428.z = wp->pos_438.z << 16;
            wp->value_D++;
            // fall through
        case 1:
            wp->anim_448   = 0x30;
            wp->target_184 = NULL;
            wp->value_D++;
            break;
        case 2:
            if (scene->u_8.byte[1] == 3)
            {
                wp->value_D++;
            }
            break;
        case 3:
        {
            // Initialized here, not at the top: retail copies it in this case only.
            STCOM_SVECTOR target = {0x1637, -1, 0x4E3A, 0};

            turn          = Muku(&wp->position, &target, wp->rotation.y, 0x40);
            wp->rot_440.y = (wp->rot_440.y + turn) & 0xFFF;
            if ((sint16)turn == 0)
            {
                wp->anim_448 = 0xC;
                wp->timer_E  = 0xA;
                wp->value_D++;
            }
            break;
        }
        case 4:
            if (--wp->timer_E == 0)
            {
                wp->value_D++;
            }
            break;
        case 5:
            func_8002FF34(wp, 0x50, 0, 0);
            break;
    }
}

void func_80104A74(ST03_PL *wp)
{
    D_80116790[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_80104AD4(STAGE_ROOM *wp)
{
    func_8001E6C0(0, 0, 0);
    D_800BC7F0         = D_801166C0;
    wp->tbl_A4         = D_80116768;
    STAGE_PL.routine_0 = 3;
    STAGE_PL.routine_1 = 0;
    STAGE_PL.value_C   = 0;
}

void func_80104B40(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_80104B80(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_80104AD4((STAGE_ROOM *)wp);
                wp->routine_4++;
            }
            break;
        case 1:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_4++;
            }
            if (func_8001DE84())
            {
                wp->routine_4 = 0xA;
            }
            // fall through
        case 2:
            func_80104B40(wp);
            func_80104A74(ST03_PL_PTR);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 2)
            {
                wp->routine_4 = 0xB;
            }
            break;
        case 0xA:
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            ((ST03_ACTOR *)wp->child_24)->flags_6 &= ~1;
            wp->routine_4++;
            break;
        case 0xB:
            func_80042314(&Player_work);
            Game_work.value_81 = 1;
            wp->flags_0        = 0;
            Sce_flag_on(0x45);
            break;
    }
}

void func_80104CFC(void)
{
}

void func_80104D04(ST03_PL *wp)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    switch (wp->value_D)
    {
        case 0:
            wp->pos_438.x   = 0x16F7;
            wp->pos_438.y   = -1;
            wp->pos_438.z   = 0x4E9A;
            wp->rot_440.y   = 0xC1C;
            wp->anim_448    = 0x30;
            wp->rot_440.x   = 0;
            wp->rot_440.z   = 0;
            wp->target_184  = NULL;
            wp->fixed_428.x = wp->pos_438.x << 16;
            wp->fixed_428.y = wp->pos_438.y << 16;
            wp->fixed_428.z = wp->pos_438.z << 16;
            wp->value_D++;
            break;
        case 1:
            wp->rot_440.y =
                (wp->rot_440.y + Muku(&wp->position, &((STAGE_OBJ *)STAGE_SCENE_OBJ(1))->position, wp->rotation.y, 0x800)) & 0xFFF;
            wp->value_D++;
            // fall through
        case 2:
            if (scene->u_8.byte[1] == 1)
            {
                MojiTaskExec2(0, 0xB3);
                wp->value_D++;
            }
            break;
        case 4:
            if (scene->u_8.byte[1] == 5)
            {
                wp->rot_440.y =
                    (wp->rot_440.y + Muku(&wp->position, &((STAGE_OBJ *)STAGE_SCENE_OBJ(0))->position, wp->rotation.y, 0x800)) & 0xFFF;
                wp->value_D++;
            }
            break;
        case 5:
            if (scene->u_8.byte[1] == 6)
            {
                MojiTaskExec2(0, 0xB8);
                wp->value_D++;
            }
            break;
        case 3:
        case 6:
            if (!(Moji_flag & 0x8000000))
            {
                wp->value_D++;
                Sce_event_next();
            }
            break;
    }
}

void func_80104EBC(ST03_PL *wp)
{
    D_80116860[wp->routine_C](wp);
    func_80030150(&wp->fixed_428, &wp->pos_438);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_80104F1C(STAGE_ROOM *wp)
{
    STAGE_OBJ *slot;
    func_8001E6C0(0, 0, 0);
    D_800BC7F0 = D_80116794;
    wp->tbl_A4 = D_80116810;
    slot       = Scene_obj_ent_open(&D_801167E8[0]);
    slot->flags_6 &= ~0x20;
    Scene_obj_ent_open(&D_801167E8[1]);
    STAGE_PL.routine_0 = 3;
    STAGE_PL.routine_1 = 0;
    STAGE_PL.value_C   = 0;
}

void func_80104FB4(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

// `child` also carries child_28 to func_80031824: reusing the local gives retail's registers.
void func_80104FF4(STAGE_ROOM_WORK *wp)
{
    STAGE_WORK *child;

    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_80104F1C((STAGE_ROOM *)wp);
                Sce_camera_update();
                wp->routine_4++;
            }
            break;
        case 1:
            if (*(uint8 *)wp->tbl_A4 == 0xFF)
            {
                wp->routine_4++;
            }
            if (func_8001DE84())
            {
                wp->routine_4 = 0xA;
            }
            // fall through
        case 2:
            func_80104FB4(wp);
            func_80104EBC(ST03_PL_PTR);
            Sce_camera_update();
            Sce_event_update();
            if (wp->routine_4 == 2)
            {
                wp->routine_4 = 0xB;
            }
            break;
        case 0xA:
            func_80053AA4(0);
            Cd_subcmd(0, 1, 0);
            D_800A395C = 1;
            func_80039820();
            child = wp->child_28;
            func_80031824(child);
            child            = wp->child_24;
            child->routine_0 = 8;
            Sce_flag_on(0x52A);
            wp->routine_4++;
            break;
        case 0xB:
            func_80042314(&Player_work);
            D_800A395C = 1;
            func_8003A264();
            wp->flags_0 = 0;
            break;
    }
}

void func_80105178(STAGE_STCOM15_WORK_348 *wp)
{
    STAGE_STCOM15_CTL *ctl;
    if (STCOM_STAGE_ROOM == 5)
    {
        func_8010D400((ST03_ACTOR *)wp);
        return;
    }
    wp->anim_prev_AD        = wp->anim_AC;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->scale.v.pad         = 0x4210;
    wp->ctl.rand_2          = rand();
    D_80116864[wp->routine_0](wp);
    ctl = &wp->ctl;
    if (wp->anim_prev_AD != wp->anim_AC)
    {
        func_800322A8(wp, wp->anim_AC, 0);
    }
    else
    {
        func_80032488(wp);
    }
    if ((wp->flags_0 & 2) && !(ctl->flags_0 & 0x20))
    {
        Model_Shadow_Trans(wp, 0x30, 0x200, 0);
    }
    if ((wp->flags_0 & 1) && (ctl->flags_0 & 2))
    {
        ctl->pos_C = wp->position;
        ctl->pos_C.y -= 0x28;
        func_800341BC(&ctl->pos_C, 0x28, 0, 0x8000, wp->value_1, &ctl->hit_14, ctl->value_8 | 0x4000000, 0x800000, 0x80);
    }
    ctl->hit_14 = 0;
}

void func_80105360(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint16 life;

    ctl = &wp->ctl;
    wp->flags_0 |= 2;
    if ((wp->variant_3 & 0xF0) != 0x50)
    {
        wp->rotation.x = 0;
        wp->rotation.z = 0;
        wp->rotation.y = (wp->timer_C << 9) & 0xE00;
    }
    *(uint32 *)&wp->turn_64 = 0;
    wp->timer_C &= 0xF0;
    Model_work_init(wp, NULL);
    wp->scale.words[0]       = 0x02000200;
    wp->scale.words[1]       = 0x200;
    ctl->flags_0             = 0xE;
    *(uint32 *)&ctl->timer_4 = 0;
    *(uint32 *)&ctl->value_8 = 0;
    ctl->hit_14              = 0;
    ctl->value_18            = 0;
    Track_reset(ctl->track_24, 0, -0x60);
    ctl->range_34 = 0x7FFFFFFF;
    life          = D_80098844[wp->kind_2]->life_8;
    wp->value_78  = 0;
    wp->value_6E  = life;
    wp->value_B0  = life;
    wp->value_B2  = life;
    if ((wp->variant_3 & 0xF0) != 0x50)
    {
        wp->position.y       = Obj_ceiling_height_get(wp);
        wp->position_fixed.y = wp->position.y << 16;
    }
    wp->routine_0 = 1;
    switch (wp->variant_3 & 0xF0)
    {
        case 0:
            wp->routine_1 = 0;
            func_800322A8(wp, 0, 0);
            break;
        case 0x10:
            wp->routine_1 = 0xE;
            func_800322A8(wp, 1, 0);
            break;
        case 0x20:
            wp->routine_1 = 0xD;
            func_800322A8(wp, 0xC, 0);
            break;
        case 0x30:
            wp->routine_1 = 0x10;
            wp->flags_0 &= ~2;
            ctl->flags_0 = (ctl->flags_0 & ~6) | 0x20;
            func_800322A8(wp, 0xA, 0);
            break;
        case 0x40:
            wp->routine_1 = 0xF;
            wp->value_D   = 0;
            wp->flags_0 &= ~2;
            ctl->flags_0 = (ctl->flags_0 & ~6) | 0x20;
            func_800322A8(wp, 0, 0);
            break;
        case 0x50:
            wp->routine_1 = 0xB;
            func_800322A8(wp, 0x25, 0);
            break;
    }
    *(uint16 *)&wp->routine_2 = 0;
    wp->variant_3 &= 0xF;
    if (wp->timer_C != 0)
    {
        ctl->other_38 = (ST03_HELD *)Open_SHL_WORK();
        if (ctl->other_38 != NULL)
        {
            ctl->other_38->flags_0          = 1;
            ctl->other_38->kind_2           = 6;
            ctl->other_38->variant_3        = 0x80;
            ctl->other_38->position.x       = wp->position.x;
            ctl->other_38->position.y       = wp->position.y - 0x64;
            ctl->other_38->position.z       = wp->position.z;
            ctl->other_38->position_fixed.x = ctl->other_38->position.x << 16;
            ctl->other_38->position_fixed.y = ctl->other_38->position.y << 16;
            ctl->other_38->position_fixed.z = ctl->other_38->position.z << 16;
            ctl->other_38->routine_0        = 4;
            ctl->other_38->value_9C         = 0x20;
            ctl->other_38->value_A0         = 0x10;
        }
    }
    wp->scale.v.pad = 0x4210;
}

void func_80105694(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    if (ctl->flags_0 & 4)
    {
        func_80107978(wp);
    }
    D_80116870[wp->routine_1](wp);
    if (ctl->flags_0 & 1)
    {
        switch (wp->routine_1)
        {
            case 8:
                func_80031824(wp);
                break;
            case 5:
            case 6:
            case 7:
                if (wp->variant_3 < 2 && wp->timer_C == 0)
                {
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->routine_1 = 2;
                }
                break;
            case 9:
            case 10:
            case 11:
                if (wp->value_6E > 0)
                {
                    wp->spin_66   = 0x80;
                    wp->routine_1 = 5;
                }
                else
                {
                    ctl->flags_0 &= ~4;
                    wp->routine_1 = 8;
                }
                break;
            case 13:
            case 14:
                if (wp->value_D != 0)
                {
                    wp->value_D--;
                    break;
                }
                // fall through
            default:
                if (ctl->flags_0 & 0x10)
                {
                    if (wp->variant_3 < 2 && wp->timer_C == 0)
                    {
                        wp->routine_1 = 3;
                    }
                    else
                    {
                        wp->routine_1 = 2;
                    }
                }
                else if (wp->variant_3 & 1)
                {
                    wp->routine_1 = 0;
                }
                else
                {
                    wp->routine_1 = 1;
                    func_80107878(wp);
                }
                break;
        }
        *(uint16 *)&wp->routine_2 = 0;
        ctl->flags_0 &= ~1;
    }
    if (wp->timer_C != 0)
    {
        ctl->other_38->position.x       = wp->position.x;
        ctl->other_38->position.y       = wp->position.y - 0x64;
        ctl->other_38->position.z       = wp->position.z;
        ctl->other_38->position_fixed.x = ctl->other_38->position.x << 16;
        ctl->other_38->position_fixed.y = ctl->other_38->position.y << 16;
        ctl->other_38->position_fixed.z = ctl->other_38->position.z << 16;
    }
    if (ctl->timer_A != 0)
    {
        ctl->timer_A--;
    }
}

void func_80105900(ST03_OBJ *wp)
{
    if (wp->u_C.b.byte_C != 0)
    {
        wp->value_380->routine_0 = 0;
    }
    func_80031824(wp);
}

void func_8010593C(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    ST03_SPARK *ep;
    sint16 i;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->ctl.timer_4 = 0x40;
            wp->accel_4C.y  = 0x40;
            wp->ctl.value_6 = 0;
            wp->timer_C     = 0;
            wp->anim_AC     = 0;
            wp->accel_4C.x  = 0x30;
            wp->ctl.flags_0 &= ~2;
            for (i = 0; i < 6; i++)
            {
                ep = func_80031618();
                if (ep == NULL)
                {
                    break;
                }
                ep->flags_0 = 3;
                ep->kind_2  = 0x83;
                ep->x_1C    = wp->value_180[i].x;
                ep->y_1E    = wp->value_180[i].y;
                ep->z_20    = wp->value_180[i].z;
            }
            wp->value_FB  = -1;
            wp->value_103 = -1;
            wp->value_107 = -1;
            wp->value_10B = -1;
            wp->value_10F = -1;
            func_80047148(wp, wp->value_180);
            // fall through
        case 1:
            t            = (uint16)ctl->timer_4 - 1;
            ctl->timer_4 = t;
            if ((sint16)t <= 0)
            {
                wp->routine_2 = 2;
            }
            else
            {
                wp->velocity.v.y = ((uint16)wp->accel_4C.x - t) * 2;
            }
            // fall through
        case 2:
            wp->flags_0 |= 2;
            ctl->value_6 = (ctl->value_6 + 1) & 3;
            if (wp->value_6E <= 0 && ctl->value_6 == 0)
            {
                wp->flags_0 &= ~2;
            }
            Obj_pos_set(wp, 0, wp->velocity.v.y << 4, 0);
            wp->position.y -= 0x34;
            wp->position_fixed.y = wp->position.y << 16;
            if (Obj_map_push_out(wp) & 0x1000)
            {
                if (++wp->routine_3 == 3)
                {
                    ctl->timer_4  = 0x16;
                    wp->routine_2 = 3;
                }
                else
                {
                    wp->routine_2 = 1;
                    wp->flags_0 |= 2;
                    wp->accel_4C.x >>= 1;
                    wp->accel_4C.y >>= 1;
                    ctl->timer_4 = wp->accel_4C.y;
                }
            }
            wp->position.y += 0x34;
            wp->position_fixed.y = wp->position.y << 16;
            break;
        case 3:
            wp->flags_0 ^= 2;
            if (--wp->ctl.timer_4 < 0)
            {
                wp->ctl.flags_0 |= 1;
            }
            break;
    }
}

void func_80105BF8(STAGE_ACTOR *wp)
{
    STAGE_ACTOR_CTL *ctl;
    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 120;
            wp->routine_2   = 1;
            wp->anim_AC     = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80105C64(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.timer_4 = 0x5A;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                break;
            }
            wp->rotation.y = (wp->rotation.y + wp->spin_66) & 0xFFF;
            Obj_pos_set(wp, 0x30, 0, 0);
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            break;
    }
}

void func_80105DC4(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0xA;
            wp->ctl.timer_4 = 0xF;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                break;
            }
            Obj_pos_set(wp, 0x80, 0, 0);
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            break;
    }
}

void func_80105F14(ST03_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    ST03_ACTOR_CTL *ctl;
    sint16 turn;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.x = 8;
            wp->spin_66      = 0x10;
            if (wp->timer_C != 0)
            {
                ctl->range_34 = 0x80000;
                wp->anim_AC   = 9;
            }
            else
            {
                ctl->range_34 = 0x8000;
                wp->anim_AC   = 2;
            }
            // fall through
        case 1:
            if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 |= 1;
                break;
            }
            if (func_80031E60(&pl->position_fixed, pl->rotation.y, 0x800, &wp->position_fixed, wp->rotation.y, 0x400))
            {
                wp->spin_66               = 0x80;
                wp->routine_1             = 5;
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            turn = Muku(&wp->position, &pl->position, wp->rotation.y, wp->spin_66);
            if (STCOM_ABS(turn) < 0x10 && wp->value_80 < ctl->range_34)
            {
                if (wp->timer_C != 0)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 7;
                }
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x * 16, 0, 0);
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            break;
    }
}

void func_8010616C(ST03_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    ST03_ACTOR_CTL *ctl;
    sint16 turn;
    sint32 hit;

    ctl = &wp->ctl;
    pl  = &Player_work;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2    = 1;
            wp->velocity.v.x = 0xC;
            wp->spin_66      = 0x18;
            wp->anim_AC      = 9;
            if (wp->timer_C != 0)
            {
                ctl->range_34 = 0x80000;
            }
            else
            {
                ctl->range_34 = 0x8000;
            }
            // fall through
        case 1:
            if (!(ctl->flags_0 & 0x10))
            {
                ctl->flags_0 |= 1;
                break;
            }
            turn = Muku(&wp->position, &pl->position, wp->rotation.y, wp->spin_66);
            turn = STCOM_ABS(turn);
            if (turn < 0x10 && wp->value_80 < ctl->range_34)
            {
                if (wp->timer_C != 0)
                {
                    wp->routine_1 = 6;
                }
                else
                {
                    wp->routine_1 = 7;
                }
                *(uint16 *)&wp->routine_2 = 0;
                wp->anim_AC               = wp->anim_prev_AD;
                break;
            }
            wp->rotation.y = (wp->rotation.y + Muku(&pl->position, &wp->position, wp->rotation.y, wp->spin_66)) & 0xFFF;
            Obj_pos_set(wp, wp->velocity.v.x << 4, 0, 0);
            hit                  = Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->routine_1             = 0xC;
                *(uint16 *)&wp->routine_2 = 0;
                wp->position              = wp->position_prev;
                wp->position_fixed        = wp->position_fixed_prev;
            }
            else if (hit & 0xF00)
            {
                wp->rotation.y = (wp->rotation.y + 0x800) & 0xFFF;
            }
            else if (!(ctl->value_2 & 0x1FF))
            {
                wp->routine_1             = 0xA;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
    }
}

void func_80106398(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + wp->spin_66) & 0xFFF;
            }
            break;
    }
}

void func_8010641C(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 turn;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->anim_AC     = 1;
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (wp->variant_3 < 2 && wp->timer_C == 0)
            {
                turn = Muku(&Player_work.position, &wp->position, wp->rotation.y, wp->spin_66);
            }
            else
            {
                turn = Muku(&wp->position, &Player_work.position, wp->rotation.y, wp->spin_66);
            }
            if ((sint16)turn == 0)
            {
                ctl->flags_0 |= 1;
            }
            else
            {
                wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
            }
            break;
    }
}

void func_80106508(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 15;
            wp->anim_AC     = 0x30;
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->other_38->routine_0 = 0;
            ctl->other_38->turn_64   = wp->rotation.y;
            ctl->other_38->value_9C  = 0x20;
            ctl->other_38->value_A0  = 0x10;
            wp->timer_C              = 0;
            ctl->timer_4             = 8;
            wp->routine_2            = 2;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801065F8(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 hit;

    ctl = &wp->ctl;
    if (wp->ctl.hit_14 & 0x2000000)
    {
        wp->ctl.value_8 = 0;
    }
    switch (wp->routine_2)
    {
        case 0:
            ctl->timer_4  = 0xF;
            wp->anim_AC   = 0x15;
            wp->routine_2 = 1;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2    = 2;
            wp->anim_AC      = 0x18;
            wp->velocity.v.x = 0xF;
            ctl->timer_4     = 0xF;
            ctl->value_8     = D_80098844[wp->kind_2]->value_A;
            // fall through
        case 2:
            ctl->timer_4--;
            if (ctl->hit_14 & 0x2000000)
            {
                wp->velocity.v.x = 0;
            }
            wp->velocity.v.y = (8 - (uint16)ctl->timer_4) * 4;
            Obj_pos_set(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = Obj_map_push_out(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if (hit & 0x1000)
                {
                    ctl->timer_4  = 0xF;
                    ctl->value_8  = 0;
                    wp->anim_AC   = 0x17;
                    wp->routine_2 = 3;
                }
            }
            break;
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 4;
                ctl->timer_4  = 0x12;
                wp->anim_AC   = 0x23;
            }
            else if (wp->velocity.v.x != 0)
            {
                wp->velocity.v.x--;
            }
            Obj_pos_set(wp, wp->velocity.v.x << 4, 0, 0);
            Obj_map_push_out(wp);
            wp->position.y       = Obj_ceiling_height_get(wp);
            wp->position_fixed.y = wp->position.y << 16;
            if (wp->position.y - wp->position_prev.y > 0x10)
            {
                wp->position       = wp->position_prev;
                wp->position_fixed = wp->position_fixed_prev;
            }
            break;
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_80106880(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 10;
            wp->routine_2   = 1;
            wp->anim_AC     = 0x20;
            wp->ctl.value_8 = 0;
            wp->value_110   = 7;
            wp->ctl.flags_0 &= ~8;
            // fall through
        case 1:
            if (--ctl->timer_4 < 0)
            {
                ctl->timer_4  = 10;
                wp->anim_AC   = 8;
                wp->value_110 = 6;
            }
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 9;
            }
            break;
    }
}

void func_80106950(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.value_8  = 0;
            wp->ctl.timer_4  = 4;
            wp->routine_2    = 1;
            wp->anim_AC      = 0x21;
            wp->velocity.v.x = 0xD;
            wp->velocity.v.y = -0x18;
            wp->value_110    = 7;
            wp->ctl.flags_0 &= ~8;
            wp->rotation.y &= 0xFFF;
            if (wp->timer_C != 0)
            {
                wp->ctl.other_38->routine_0 = 0;
                wp->ctl.other_38->turn_64   = wp->rotation.y;
                wp->ctl.other_38->value_9C  = 0x20;
                wp->ctl.other_38->value_A0  = 0x10;
                wp->timer_C                 = 0;
            }
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    Obj_map_push_out(wp);
                }
                break;
            }
            ctl->timer_4  = 7;
            wp->routine_2 = 2;
            wp->anim_AC   = 0x22;
            // fall through
        case 2:
            t = (uint16)ctl->timer_4;
            t--;
            ctl->timer_4     = t;
            wp->velocity.v.y = (4 - t) * 8;
            Obj_pos_set(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = Obj_map_push_out(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if ((hit & 0x1000) && ctl->timer_4 <= 0)
                {
                    ctl->timer_4  = 0x12;
                    wp->routine_2 = 3;
                    wp->anim_AC   = 0x23;
                }
            }
            break;
        case 3:
            if (--wp->ctl.timer_4 < 0)
            {
                wp->ctl.flags_0 |= 1;
                wp->value_110 = 6;
                wp->ctl.flags_0 |= 8;
            }
            break;
    }
    wp->flags_0 |= 2;
    ctl->value_6 = (ctl->value_6 + 1) & 3;
    if (wp->value_6E <= 0 && ctl->value_6 == 0)
    {
        wp->flags_0 &= ~2;
    }
}

void func_80106BBC(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            ctl->timer_4 = 4;
            ctl->value_6 = 0;
            ctl->value_8 = 0;
            ctl->flags_0 &= ~8;
            wp->routine_2    = 1;
            wp->anim_AC      = 0x25;
            wp->velocity.v.x = -0xB;
            wp->velocity.v.y = -0x18;
            wp->value_110    = 7;
            wp->rotation.y &= 0xFFF;
            if (wp->timer_C != 0)
            {
                ctl->other_38->routine_0 = 0;
                ctl->other_38->turn_64   = (wp->rotation.y + 0x800) & 0xFFF;
                ctl->other_38->value_9C  = 0x20;
                ctl->other_38->value_A0  = 0x10;
                wp->timer_C              = 0;
            }
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                if (ctl->timer_4 < 2)
                {
                    Obj_pos_set(wp, wp->velocity.v.x, wp->velocity.v.y, 0);
                    Obj_map_push_out(wp);
                }
                break;
            }
            ctl->timer_4  = 0xB;
            wp->routine_2 = 2;
            wp->anim_AC   = 0x26;
            // fall through
        case 2:
            t = (uint16)ctl->timer_4;
            t--;
            ctl->timer_4     = t;
            wp->velocity.v.y = (8 - t) * 8;
            Obj_pos_set(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = Obj_map_push_out(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if ((hit & 0x1000) && ctl->timer_4 <= 0)
                {
                    ctl->timer_4  = 0x26;
                    wp->routine_2 = 3;
                    wp->anim_AC   = 0x27;
                }
            }
            break;
        case 3:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = 0x11;
            wp->routine_2 = 4;
            wp->anim_AC   = 0x28;
            // fall through
        case 4:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
                wp->value_110 = 6;
                ctl->flags_0 |= 8;
            }
            break;
    }
    wp->flags_0 |= 2;
    ctl->value_6 = (ctl->value_6 + 1) & 3;
    if (wp->value_6E <= 0 && ctl->value_6 == 0)
    {
        wp->flags_0 &= ~2;
    }
}

void func_80106E54(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    sint32 hit;
    sint32 t;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            ctl->timer_4     = 5;
            ctl->value_8     = 0;
            wp->routine_2    = 1;
            wp->anim_AC      = 0x10;
            wp->velocity.v.x = 8;
            wp->velocity.v.y = -0xE;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = 0xE;
            wp->routine_2 = 2;
            wp->anim_AC   = 0x11;
            // fall through
        case 2:
            t            = (uint16)ctl->timer_4 - 1;
            ctl->timer_4 = t;
            if ((sint16)t < 0)
            {
                wp->routine_2    = 3;
                wp->velocity.v.x = 0;
            }
            else
            {
                wp->velocity.v.y = (7 - t) * 2;
            }
            // fall through
        case 3:
            if (wp->routine_2 == 3)
            {
                t = (uint16)ctl->timer_4;
                t--;
                ctl->timer_4     = t;
                wp->velocity.v.y = (7 - t) * 2;
            }
            Obj_pos_set(wp, wp->velocity.v.x << 4, wp->velocity.v.y << 4, 0);
            hit = Obj_map_push_out(wp);
            if (hit != 0)
            {
                if (hit & 0xF00)
                {
                    wp->velocity.v.x = 0;
                }
                if (hit & 0x1000)
                {
                    if (!(ctl->value_2 & 0xF))
                    {
                        ctl->timer_4  = 0xE;
                        wp->routine_2 = 4;
                        wp->anim_AC += 3;
                        if (wp->timer_C != 0)
                        {
                            ctl->other_38->routine_0 = 0;
                            ctl->other_38->turn_64   = (wp->rotation.y + 0x800) & 0xFFF;
                            ctl->other_38->value_9C  = 0x20;
                            ctl->other_38->value_A0  = 0x10;
                            wp->timer_C              = 0;
                        }
                        wp->value_110 = 7;
                    }
                    else
                    {
                        ctl->timer_4  = 7;
                        wp->routine_2 = 5;
                        wp->anim_AC += 2;
                    }
                }
            }
            break;
        case 4:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->value_110 = 6;
            ctl->timer_4  = 0x26;
            wp->routine_2 = 5;
            wp->anim_AC   = 0x28;
            // fall through
        case 5:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
}

void func_801070B4(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->ctl.timer_4 = 14;
            wp->routine_2   = 1;
            wp->ctl.value_8 = 0;
            wp->anim_AC     = 0xC;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = (ctl->value_2 & 0x1F) + 8;
            wp->routine_2 = 2;
            wp->anim_AC   = 0xD;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            ctl->timer_4  = 7;
            wp->routine_2 = 3;
            wp->anim_AC   = 0xE;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                ctl->flags_0 |= 1;
            }
            break;
    }
    if (ctl->flags_0 & 0x10)
    {
        wp->value_D = 0;
        ctl->flags_0 |= 1;
    }
}

void func_801071E0(uint8 *arg0)
{
    *arg0 &= 0xFD;
}

void func_801071F4(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            break;
        case 1:
            wp->routine_2 = 2;
            wp->anim_AC   = 0x11;
            wp->flags_0 |= 2;
            ctl->timer_4  = 8;
            ctl->value_8  = 0;
            wp->value_10B = -1;
            wp->value_10F = -1;
            // fall through
        case 2:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 3;
                wp->anim_AC   = 0xA;
            }
            else
            {
                wp->position.y -= 4;
            }
            break;
        case 3:
            break;
        case 4:
            wp->routine_2 = 5;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = 8;
            // fall through
        case 5:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_2 = 6;
                wp->flags_0 &= ~2;
            }
            else
            {
                wp->position.y += 8;
            }
            break;
    }
}

void func_801072F4(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;

    ctl = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->value_D      = 0;
            wp->ctl.other_38 = (ST03_HELD *)Open_SHL_WORK();
            if (wp->ctl.other_38 == NULL)
            {
                wp->routine_1             = 0xF;
                *(uint16 *)&wp->routine_2 = 0;
                wp->value_D               = 1;
                break;
            }
            wp->ctl.other_38->flags_0   = 1;
            wp->ctl.other_38->routine_0 = 4;
            wp->ctl.other_38->kind_2    = 6;
            wp->ctl.other_38->variant_3 = 0x80;
            wp->anim_AC                 = 0x30;
            wp->ctl.timer_4             = 0xF;
            wp->routine_2               = 1;
            wp->ctl.value_8             = 0;
            wp->value_10B               = -1;
            wp->value_10F               = -1;
            wp->flags_0 |= 2;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &Player_work.position, wp->rotation.y, 0x40)) & 0xFFF;
                wp->position.y -= 4;
                wp->position_fixed.y            = wp->position.y << 16;
                ctl->other_38->position.x       = wp->position.x;
                ctl->other_38->position.y       = wp->position.y - 0x64;
                ctl->other_38->position.z       = wp->position.z;
                ctl->other_38->position_fixed.x = ctl->other_38->position.x << 16;
                ctl->other_38->position_fixed.y = ctl->other_38->position.y << 16;
                ctl->other_38->position_fixed.z = ctl->other_38->position.z << 16;
                break;
            }
            ctl->other_38->routine_0 = 0;
            ctl->other_38->turn_64   = wp->rotation.y;
            ctl->other_38->value_9C  = 0x18;
            ctl->other_38->value_A0  = 8;
            wp->timer_C              = 0;
            ctl->timer_4             = 8;
            wp->routine_2            = 2;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = 8;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_1             = 0xF;
                *(uint16 *)&wp->routine_2 = 0;
                wp->value_D               = 1;
                wp->flags_0 &= ~2;
            }
            else
            {
                wp->position.y += 8;
                wp->position_fixed.y = wp->position.y << 16;
            }
            break;
    }
}

void func_8010758C(ST03_ACTOR *wp)
{
    ST03_ACTOR *held;
    ST03_ACTOR_CTL *ctl;

    held = D_80138094;
    ctl  = &wp->ctl;
    switch (wp->routine_2)
    {
        case 0:
            wp->routine_2   = 1;
            wp->anim_AC     = 0x30;
            wp->value_10B   = -1;
            wp->value_10F   = -1;
            wp->ctl.timer_4 = 0xF;
            wp->value_D     = 0;
            wp->ctl.value_8 = 0;
            wp->flags_0 |= 2;
            held->routine_1             = 5;
            *(uint16 *)&held->routine_2 = 0;
            // fall through
        case 1:
            if (--ctl->timer_4 >= 0)
            {
                wp->rotation.y = (wp->rotation.y + Muku(&wp->position, &D_801380A0[wp->value_E]->position, wp->rotation.y, 0x40)) & 0xFFF;
                wp->position.y -= 4;
                wp->position_fixed.y   = wp->position.y << 16;
                held->position.x       = wp->position.x;
                held->position.y       = wp->position.y - 0x50;
                held->position.z       = wp->position.z;
                held->position_fixed.x = held->position.x << 16;
                held->position_fixed.y = held->position.y << 16;
                held->position_fixed.z = held->position.z << 16;
                held->rotation.y       = wp->rotation.y;
                break;
            }
            wp->routine_2                     = 2;
            wp->timer_C                       = 0;
            ctl->timer_4                      = 8;
            held->routine_1                   = 2;
            *(uint16 *)&held->routine_2       = 0;
            D_801380A0[wp->value_E]->value_C4 = D_801380A0[wp->value_E]->value_180[0];
            D_801380A0[wp->value_E]->value_C4.y -= 0x140;
            func_80030934(held, D_801380A0[wp->value_E], 0x18, 0);
            D_801380A0[D_801380A0[wp->value_E]->value_D]->value_F &= ~0x40;
            // fall through
        case 2:
            if (--ctl->timer_4 >= 0)
            {
                break;
            }
            wp->routine_2 = 3;
            wp->anim_AC   = 0x11;
            ctl->timer_4  = 8;
            // fall through
        case 3:
            if (--ctl->timer_4 < 0)
            {
                wp->routine_1             = 0xF;
                *(uint16 *)&wp->routine_2 = 0;
                wp->value_D               = 1;
                wp->flags_0 &= ~2;
            }
            else
            {
                wp->position.y += 8;
                wp->position_fixed.y = wp->position.y << 16;
            }
            break;
    }
}

sint32 func_80107878(ST03_ACTOR *wp)
{
    ST03_ACTOR_CTL *ctl;
    uint8 *tbl;
    sint16 sum;
    sint16 i;

    ctl = &wp->ctl;
    tbl = D_801168C4;
    if (wp->variant_3 & 1)
    {
        tbl = D_801168BC;
    }
    sum = 0;
    for (i = 0; i < 6; i++)
    {
        sum += *tbl;
        if ((wp->ctl.value_2 & 0xF) < sum)
        {
            break;
        }
        tbl++;
    }
    switch (i)
    {
        case 0:
            wp->spin_66 = 0;
            break;
        case 1:
            wp->spin_66 = 6;
            break;
        case 2:
            wp->spin_66 = -6;
            break;
        case 3:
            wp->routine_1             = 4;
            wp->spin_66               = 0x10;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->timer_4              = 0x40;
            break;
        case 4:
            wp->routine_1             = 4;
            wp->spin_66               = -0x10;
            *(uint16 *)&wp->routine_2 = 0;
            ctl->timer_4              = 0x40;
            break;
        default:
            wp->routine_1             = 0;
            *(uint16 *)&wp->routine_2 = 0;
            break;
    }
    return 1;
}

sint32 func_80107978(ST03_ACTOR *wp)
{
    STCOM_SVECTOR origin = {0, 0, 0, 0};
    ST03_ACTOR_CTL *ctl;
    uint32 damage;
    sint16 turn;

    damage = wp->ctl.hit_14 & 0xFFFFFF;
    ctl    = &wp->ctl;
    if (damage == 0)
    {
        return 1;
    }
    if (!(wp->ctl.hit_14 & 0x38000000))
    {
        return 1;
    }
    if (wp->value_6E <= 0)
    {
        wp->ctl.flags_0 = (wp->ctl.flags_0 & ~4) | 8;
        damage          = D_80098844[wp->kind_2]->limit_9;
    }
    if (wp->ctl.flags_0 & 8)
    {
        wp->ctl.timer_A += damage;
        if ((wp->ctl.hit_14 & 0x20000000) || wp->ctl.timer_A >= D_80098844[wp->kind_2]->limit_9 ||
            wp->position.y != Obj_ceiling_height_get(wp))
        {
            if (ctl->from_1C.pad & 1)
            {
                turn = Angle_xz_svector(&wp->position, &ctl->from_1C);
                if (((wp->rotation.y - turn + 0x400) & 0xFFF) < 0x800)
                {
                    wp->routine_1  = 0xB;
                    wp->rotation.y = turn;
                }
                else
                {
                    wp->routine_1  = 0xA;
                    wp->rotation.y = (turn + 0x800) & 0xFFF;
                }
            }
            else
            {
                turn = Angle_xz_svector(&origin, &ctl->from_1C);
                if (((turn - wp->rotation.y + 0x400) & 0xFFF) < 0x800)
                {
                    wp->routine_1  = 0xA;
                    wp->rotation.y = turn;
                }
                else
                {
                    wp->routine_1  = 0xB;
                    wp->rotation.y = (turn + 0x800) & 0xFFF;
                }
            }
            ctl->timer_A = 0;
        }
        else
        {
            wp->routine_1 = 9;
        }
        *(uint16 *)&wp->routine_2 = 0;
    }
    wp->scale.v.pad = 0x7FFF;
    return 1;
}
