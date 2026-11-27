#include "common.h"
#include "st1a.h"

void func_8011C870(ST1A_OBJ *wp)
{
    ST1A_BLOCK *bp;
    ST1A_FLASH *fp;
    STCOM_EFFECT *fx;
    sint32 i;
    sint32 first;

    bp = (ST1A_BLOCK *)&wp->hit_440;
    switch (wp->routine_1)
    {
        case 0:
        default:
            fp = (ST1A_FLASH *)Open_SHL_WORK();
            if (fp != NULL)
            {
                fp->flags_0      = 1;
                fp->kind_2       = 0x33;
                fp->variant_3    = 0xFC;
                fp->position.x   = 0xC8;
                fp->position.y   = 0xC8;
                fp->position.z   = 0xC8;
                fp->position.pad = 0x700;
                fp->routine_3    = 0x20;
                fp->routine_2    = 0;
            }
            Sound_call(0x20C, 0, 0);
            func_8005D4E8();
            bp->count_CE  = 0;
            wp->routine_3 = 0x5A;
            wp->routine_1++;
            break;
        case 1:
            first = bp->count_CE * 3;
            for (i = first; i < first + 3; i++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0         = 5;
                    fx->kind_2          = 0x80;
                    fx->variant_3       = 2;
                    fx->sprite.position = wp->part_180[i];
                    fx->sprite.position.x += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.y += (rand() & 0xFF) - 0x80;
                    fx->sprite.position.z += (rand() & 0xFF) - 0x80;
                }
            }
            if (++bp->count_CE >= 5)
            {
                bp->count_CE = 0;
            }
            // One-pass loops (here and in cases 2-7) weight wp's references so it outranks i for s1.
            do
            {
                if (--wp->routine_3 == 0)
                {
                    wp->routine_1++;
                }
                if (wp->routine_3 == 0xA)
                {
                    Sce_flag_on(0x6C);
                }
            } while (0);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            do
            {
                wp->routine_1++;
            } while (0);
            break;
        case 8:
            break;
    }
}

void func_8011CAB4(ST1A_OBJ *wp)
{
    STAGE_10C *slot;

    switch (wp->routine_2)
    {
        case 0:
        default:
            slot = Open_SHL_WORK();
            if (slot != NULL)
            {
                slot->flags_0      = 1;
                slot->kind_2       = 0x33;
                slot->variant_3    = 0xFC;
                slot->position.y   = 0x10;
                slot->position.z   = 0x10;
                slot->position.pad = 0x500;
                slot->position.x   = 0;
                slot->routine_3    = 0x1E;
                slot->routine_2    = 0;
            }
            wp->routine_3 = 0x1E;
            wp->routine_2++;
            break;
        case 1:
            if (--wp->routine_3 == 0)
            {
                wp->value_4DE = 0;
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            break;
    }
}

void func_8011CB80(ST1A_OBJ *wp)
{
    ST1A_PICK *pick;
    uint32 r;
    uint32 tries;

    tries         = 0;
    pick          = (ST1A_PICK *)&wp->hit_440;
    pick->move_A3 = pick->move_A2;
    pick->move_A2 = pick->move_A1;
    pick->move_A1 = pick->move_A0;
    switch (pick->phase_9E)
    {
        case 0:
            r = rand() & 0xF;
            if (r < 8)
            {
                pick->move_A0 = 2;
                wp->routine_1 = 2;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            else
            {
                pick->move_A0 = 3;
                wp->routine_1 = 3;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            if (wp->value_6E < wp->value_B0 / 2)
            {
                pick->phase_9E = 2;
            }
            else
            {
                pick->phase_9E = 1;
            }
            break;
        case 1:
        retry1:
            r = rand() & 0xF;
            if (r < 2)
            {
                pick->move_A0 = 2;
                wp->routine_1 = 2;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
                if (wp->value_6E < wp->value_B0 / 2)
                {
                    pick->phase_9E = 2;
                }
                else
                {
                    pick->phase_9E = 1;
                }
            }
            else if (r < 3)
            {
                pick->move_A0 = 3;
                wp->routine_1 = 3;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
                if (wp->value_6E < wp->value_B0 / 2)
                {
                    pick->phase_9E = 2;
                }
                else
                {
                    pick->phase_9E = 1;
                }
            }
            else
            {
                if (r < 9)
                {
                    pick->move_A0  = 4;
                    wp->routine_1  = 4;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
                else
                {
                    pick->move_A0  = 5;
                    wp->routine_1  = 5;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
            }
            if (pick->move_A1 == pick->move_A0 && pick->move_A2 == pick->move_A1 && ++tries < 16)
            {
                goto retry1;
            }
            break;
        case 2:
        retry2:
            r = rand() & 0xF;
            if (r < 3)
            {
                pick->move_A0 = 2;
                wp->routine_1 = 2;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
                if (wp->value_6E < wp->value_B0 / 2)
                {
                    pick->phase_9E = 2;
                }
                else
                {
                    pick->phase_9E = 1;
                }
            }
            else
            {
                if (r < 8)
                {
                    pick->move_A0  = 4;
                    wp->routine_1  = 4;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
                else if (r < 10)
                {
                    pick->move_A0  = 5;
                    wp->routine_1  = 5;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
                else
                {
                    pick->move_A0  = 6;
                    wp->routine_1  = 6;
                    wp->routine_2  = 0;
                    wp->routine_3  = 0;
                    pick->phase_9E = 0;
                }
            }
            if (pick->move_A1 == pick->move_A0 && pick->move_A2 == pick->move_A1 && ++tries < 16)
            {
                goto retry2;
            }
            break;
    }
}

void func_8011CE4C(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    STCOM_EFFECT *fx;
    STCOM_SVECTOR target;
    sint32 turn;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            aim->value_98 = 1;
            aim->value_9A = 1;
            aim->value_9B = 0;
            if (!(rand() & 3))
            {
                Sound_call2(0x1FC, &wp->position);
            }
            Sound_call2(0x1EB, &wp->position);
            wp->routine_2++;
            break;
        case 2:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            wp->position.y += (sint8)D_80132F10[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 2;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A7 < 0)
            {
                Sound_call2(0x1EC, &wp->position);
                aim->value_98 = 1;
                aim->value_9A = 3;
                aim->value_9B = 0;
                aim->value_9C = 1;
                aim->timer_C8 = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            if (++aim->timer_C8 < 0xA)
            {
                wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x20);
            }
            Obj_pos_set(wp, 0x400, 0, 0);
            if (func_8011E9E8(&wp->position) == 0)
            {
                Sound_call2(0x1ED, &wp->position);
                wp->routine_2++;
            }
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->flags_0   = 5;
                fx->kind_2    = 0x1D;
                fx->timer_E   = 1;
                fx->value_D   = 0;
                fx->variant_3 = 0x22;
                if (STAGE_FRAME & 1)
                {
                    fx->sprite.position = wp->part_180[11];
                }
                else
                {
                    fx->sprite.position = wp->part_180[15];
                }
                fx->sprite.position.y = -0x1F;
            }
            break;
        case 5:
            aim->value_98 = 1;
            aim->value_9A = 4;
            aim->value_9B = 0;
            aim->value_9C = 0;
            wp->routine_2++;
            break;
        case 6:
            wp->position.y -= 0xA;
            if (wp->position.y < -0x32)
            {
                wp->position.y = -0x33;
            }
            wp->position_fixed.v.y = wp->position.y << 16;
            target.x               = wp->position.x * 2;
            target.y               = wp->position.y;
            target.z               = wp->position.z * 2 - 0x400;
            turn                   = Muku(&wp->position, &target, wp->rotation.y & 0xFFF, 0x80);
            if (wp->value_A7 < 0 && turn == 0 && wp->position.y == -0x33)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
                break;
            }
            wp->rotation.y += turn;
            break;
        case 7:
            Obj_pos_set(wp, -0x1E0, 0, 0);
            if (func_8011EAC0(&wp->position) != 0)
            {
                wp->routine_2++;
            }
            break;
        case 8:
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

void func_8011D240(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    ST1A_10C *slot;
    STCOM_SVECTOR vec;
    sint32 turn;
    sint32 t;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->count_A4 = 0;
            aim->value_A6 = 0;
            wp->routine_2++;
            break;
        case 1:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 2:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            if (!(rand() & 3))
            {
                Sound_call2(0x200, &wp->position);
            }
            aim->value_98 = 1;
            aim->value_9A = 0x11;
            aim->value_9B = 0;
            wp->routine_2++;
            break;
        case 3:
            if (wp->value_A4 >= 0x10)
            {
                wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
                if (wp->value_A4 == 0x10)
                {
                    Sound_call2(0x1EE, &wp->position);
                    vec.x = aim->target_0.x - wp->position.x;
                    vec.y = aim->target_0.y - wp->position.y;
                    vec.z = aim->target_0.z - wp->position.z;
                    SquareRoot0(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
                    aim->start_A8 = wp->position;
                    aim->timer_C0 = 0;
                    aim->angle_C4 = wp->rotation.y + Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x800);
                    break;
                }
                if (++aim->timer_C0 >= 0x14)
                {
                    aim->count_A4++;
                    if (func_8011EAC0(&wp->position) != 0)
                    {
                        Sound_call2(0x1F0, &wp->position);
                        aim->value_98 = 1;
                        aim->value_9A = 0x12;
                        aim->value_9B = 0;
                        Swing_Camera2(0x28, 0x64, 0xFA0, &wp->position);
                        aim->value_9C = 2;
                        wp->routine_2++;
                    }
                    else if (aim->count_A4 == 2)
                    {
                        Sound_call2(0x1EF, &wp->position);
                        aim->value_98 = 1;
                        aim->value_9A = 0x13;
                        aim->value_9B = 0;
                        Swing_Camera2(0x28, 0x64, 0xFA0, &wp->position);
                        aim->value_9C = 2;
                        wp->routine_2 = 6;
                    }
                    else
                    {
                        Sound_call2(0x1EF, &wp->position);
                        aim->value_98 = 1;
                        aim->value_9A = 0x13;
                        aim->value_9B = 0;
                        Swing_Camera2(0x28, 0x64, 0xFA0, &wp->position);
                        aim->value_9C = 2;
                        wp->routine_2 = 5;
                    }
                }
                t                      = aim->timer_C0;
                wp->position_fixed.v.x = ((aim->target_0.x * t + aim->start_A8.x * (0x14 - t)) / 0x14) << 16;
                wp->position_fixed.v.z = ((aim->target_0.z * t + aim->start_A8.z * (0x14 - t)) / 0x14) << 16;
                wp->position_fixed.v.y = t * (t * 7 << 16) - (t * 140 << 16) - 0x10000;
                wp->position.x         = wp->position_fixed.v.x >> 16;
                wp->position.y         = wp->position_fixed.v.y >> 16;
                wp->position.z         = wp->position_fixed.v.z >> 16;
                break;
            }
            if (func_8011EA54(&Player_work.position) != 0)
            {
                aim->target_0 = Player_work.position;
            }
            else
            {
                aim->dir_B0.x = -Player_work.position.x;
                aim->dir_B0.y = Player_work.position.y;
                aim->dir_B0.z = 0x400 - Player_work.position.z;
                VectorNormalS(&aim->dir_B0, &vec);
                aim->target_0.x = Player_work.position.x + ((vec.x * 25) >> 10);
                aim->target_0.y = Player_work.position.y + ((vec.y * 25) >> 10);
                aim->target_0.z = Player_work.position.z + ((vec.z * 25) >> 10);
            }
            wp->position.y += (sint8)D_80132F20[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->rotation.y += Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            break;
        case 4:
            if (wp->value_A4 < 0x18)
            {
                slot = Open_SHL_WORK();
                if (slot != NULL)
                {
                    slot->flags_0         = 1;
                    slot->kind_2          = 0x33;
                    slot->variant_3       = 0xFF;
                    slot->model_88        = wp->model_88;
                    slot->position_AC     = wp->part_180[15];
                    slot->position_AC.pad = 0xF;
                    slot->matrix_8C       = wp->matrix_420;
                }
            }
            if (func_8011F150((STAGE_OBJ *)wp, -5) != 0 && wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                aim->value_9C = 0;
                wp->routine_2 = 0xF;
            }
            break;
        case 5:
            if (func_8011EA54(&Player_work.position) != 0)
            {
                aim->target_0 = Player_work.position;
            }
            else
            {
                aim->dir_B0.x = -Player_work.position.x;
                aim->dir_B0.y = Player_work.position.y;
                aim->dir_B0.z = 0x400 - Player_work.position.z;
                VectorNormalS(&aim->dir_B0, &vec);
                aim->target_0.x = Player_work.position.x + ((vec.x * 25) >> 10);
                aim->target_0.y = Player_work.position.y + ((vec.y * 25) >> 10);
                aim->target_0.z = Player_work.position.z + ((vec.z * 25) >> 10);
            }
            wp->rotation.y += Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            func_8011F150((STAGE_OBJ *)wp, 0);
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9B = 0x10;
                aim->value_9A = 0;
                wp->routine_2 = 3;
            }
            break;
        case 6:
            aim->target_0.y = -1;
            aim->target_0.x = 0;
            aim->target_0.z = 0x400;
            wp->rotation.y += Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            func_8011F150((STAGE_OBJ *)wp, 0);
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9B = 0x10;
                aim->value_9A = 0;
                wp->routine_2 = 3;
            }
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            break;
        case 15:
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
    }
}

void func_8011DA38(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    ST1A_DEBRIS *shot;
    STCOM_FIXED_VECTOR dir;
    sint32 turn;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            Sound_call2(0x1F1, &wp->position);
            aim->value_98 = 1;
            aim->value_9A = 5;
            aim->value_9B = 0;
            wp->routine_2++;
            break;
        case 2:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            wp->position.y += (sint8)D_80132F3C[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_A7 < 0)
            {
                Sound_call2(0x1FF, &wp->position);
                Sound_call2(0x1F2, &wp->position);
                aim->value_98 = 1;
                aim->value_9A = 6;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A4 == 2)
            {
                Sound_call2(0x1F3, &wp->position);
            }
            if (wp->value_A4 >= 2 && wp->value_A4 <= 10 && !(wp->value_A4 & 1))
            {
                shot = (ST1A_DEBRIS *)Open_SHL_WORK();
                if (shot != NULL)
                {
                    shot->flags_0   = 1;
                    shot->kind_2    = 0x32;
                    shot->variant_3 = 3;
                    dir.x           = wp->part_180[11].x - wp->position.x;
                    dir.y           = 0;
                    dir.z           = wp->part_180[11].z - wp->position.z;
                    VectorNormalS(&dir, &shot->velocity);
                    shot->position   = wp->part_180[11];
                    shot->position.y = -2;
                }
            }
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 7;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 5:
            if (func_8011F150((STAGE_OBJ *)wp, -5) != 0)
            {
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            break;
        case 6:
        case 7:
        case 8:
            break;
    }
}

void func_8011DCD8(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    ST1A_SIGHT *sight;
    sint32 turn;
    STCOM_FIXED_VECTOR unused; // unused, but retail reserves its 16 bytes

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            turn = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (turn != 0)
            {
                wp->rotation.y += turn;
                break;
            }
            aim->value_98 = 1;
            aim->value_9A = 0xF;
            aim->value_9B = 0;
            wp->routine_2++;
            sight = (ST1A_SIGHT *)Open_SHL_WORK();
            if (sight != NULL)
            {
                aim->sight_D8    = sight;
                sight->flags_0   = 1;
                sight->kind_2    = 0x33;
                sight->variant_3 = 1;
                sight->target_B8 = &STAGE_PL.value_3A8;
                sight->owner_D4  = wp;
            }
            break;
        case 2:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0x10;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A4 == 9)
            {
                Sound_call2(0x1FD, &wp->position);
                aim->sight_D8->fire_C = 1;
            }
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->routine_1 = 1;
            wp->routine_2 = 0;
            wp->routine_3 = 0;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            break;
    }
}

void func_8011DE9C(ST1A_OBJ *wp)
{
    ST1A_AIM *aim;
    STCOM_EFFECT *fx;
    STAGE_10C *slot;
    sint32 i;
    sint32 n;

    aim = (ST1A_AIM *)&wp->hit_440;
    switch (wp->routine_2)
    {
        case 0:
        case 10:
        default:
            aim->target_0 = Player_work.position;
            wp->routine_2++;
            break;
        case 1:
            i = Muku(&wp->position, &aim->target_0, wp->rotation.y & 0xFFF, 0x80);
            if (i != 0)
            {
                wp->rotation.y += i;
                break;
            }
            aim->fx_D0 = func_80031618();
            if (aim->fx_D0 != NULL)
            {
                aim->fx_D0->flags_0           = 5;
                aim->fx_D0->kind_2            = 0x1D;
                aim->fx_D0->value_D           = 0x80;
                aim->fx_D0->timer_E           = 1;
                aim->fx_D0->value_F           = 1;
                aim->fx_D0->variant_3         = 3;
                aim->fx_D0->sprite.position.x = (wp->part_180[11].x + wp->part_180[15].x) >> 1;
                aim->fx_D0->sprite.position.y = (wp->part_180[11].y + wp->part_180[15].y) >> 1;
                aim->fx_D0->sprite.position.z = (wp->part_180[11].z + wp->part_180[15].z) >> 1;
            }
            Sound_call2(0x1FE, &wp->position);
            Sound_call2(0x1F7, &wp->position);
            aim->value_98 = 1;
            aim->value_9A = 8;
            aim->value_9B = 0;
            wp->routine_2++;
            aim->count_CC = 0;
            break;
        case 2:
            aim->count_CC++;
            i = rand() & 0x3F;
            for (n = 0; n < 2; n++)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x1D;
                    fx->value_D           = 3;
                    fx->timer_E           = 1;
                    fx->variant_3         = 0x22;
                    fx->sprite.position.x = wp->position.x + ((D_800BBCF8[i] << 16) >> 20);
                    fx->sprite.position.y = -0x1F - (rand() & 0x3F);
                    fx->sprite.position.z = wp->position.z + ((D_800BAEB0[i] << 16) >> 20);
                    i                     = (i + 0x15) & 0x3F;
                }
            }
            if (aim->value_E0 != 0 && aim->count_CC == 0x50)
            {
                fx = func_80031618();
                if (fx != NULL)
                {
                    fx->flags_0           = 5;
                    fx->kind_2            = 0x80;
                    fx->variant_3         = 6;
                    fx->value_F           = 3;
                    fx->sprite.position   = wp->position;
                    fx->sprite.position.y = -1;
                }
            }
            if (wp->value_A4 >= 0x2B)
            {
                if (wp->value_A4 == 0x2B)
                {
                    Sound_call2(0x1F8, &wp->position);
                    slot = Open_SHL_WORK();
                    if (slot != NULL)
                    {
                        slot->flags_0      = 1;
                        slot->kind_2       = 0x33;
                        slot->variant_3    = 0xFC;
                        slot->position.x   = 0xFF;
                        slot->position.y   = 0x10;
                        slot->position.z   = 0x10;
                        slot->position.pad = 0x500;
                        slot->routine_3    = 0x1E;
                        slot->routine_2    = 0;
                    }
                }
                if (wp->value_A4 == 0x30)
                {
                    fx = func_80031618();
                    if (fx != NULL)
                    {
                        fx->flags_0           = 5;
                        fx->kind_2            = 0x80;
                        fx->variant_3         = 6;
                        fx->value_F           = 3;
                        fx->sprite.position   = wp->position;
                        fx->sprite.position.y = -1;
                    }
                }
                aim->fx_D0->sprite.position.x = (wp->part_180[11].x + wp->part_180[15].x) >> 1;
                aim->fx_D0->sprite.position.y = ((wp->part_180[11].y + wp->part_180[15].y) >> 1) - 0x64;
                aim->fx_D0->sprite.position.z = (wp->part_180[11].z + wp->part_180[15].z) >> 1;
                aim->fx_D0->value_F += 0xA;
                if ((uint8)aim->fx_D0->value_F >= 0xDC)
                {
                    aim->fx_D0->value_F = 0xDC;
                }
                if (STAGE_FRAME & 1)
                {
                    slot = Open_SHL_WORK();
                    if (slot != NULL)
                    {
                        slot->flags_0   = 1;
                        slot->kind_2    = 0x32;
                        slot->variant_3 = 0;
                        slot->position  = aim->fx_D0->sprite.position;
                    }
                }
            }
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            wp->position.y += (sint8)D_80132F58[wp->value_A4];
            wp->position_fixed.v.y = wp->position.y << 16;
            if (wp->value_A7 < 0 && aim->count_CC >= 0x5B)
            {
                slot = Open_SHL_WORK();
                if (slot != NULL)
                {
                    slot->flags_0      = 1;
                    slot->kind_2       = 0x33;
                    slot->variant_3    = 0xFC;
                    slot->position.y   = 0x10;
                    slot->position.z   = 0x10;
                    slot->position.pad = 0x3E8;
                    slot->position.x   = 0;
                    slot->routine_3    = 0x1E;
                    slot->routine_2    = 0;
                }
                Sound_call(0x20C, 0, 0);
                aim->value_98 = 1;
                aim->value_9A = 9;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 3:
            if (wp->value_A4 < 8)
            {
                aim->fx_D0->sprite.position.x = (wp->part_180[11].x + wp->part_180[15].x) >> 1;
                aim->fx_D0->sprite.position.y = ((wp->part_180[11].y + wp->part_180[15].y) >> 1) - 0x64;
                aim->fx_D0->sprite.position.z = (wp->part_180[11].z + wp->part_180[15].z) >> 1;
                aim->fx_D0->value_D -= 0x10;
            }
            else if (wp->value_A4 == 8)
            {
                func_80031988(aim->fx_D0);
            }
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80);
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xA;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 4:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 5:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 6:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 7:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 8:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 9:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 11:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 12:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xB;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 13:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) - 0x40;
            if (wp->value_A7 < 0)
            {
                func_8011F208();
                aim->value_98 = 1;
                aim->value_9A = 0xC;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[15]);
                wp->routine_2++;
            }
            break;
        case 14:
            wp->rotation.y += Muku(&wp->position, &Player_work.position, wp->rotation.y & 0xFFF, 0x80) + 0x40;
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0xE;
                aim->value_9B = 0;
                Swing_Camera2(0x1E, 0x64, 0xFA0, &wp->part_180[11]);
                wp->routine_2++;
            }
            break;
        case 15:
            if (wp->value_A7 < 0)
            {
                aim->value_98 = 1;
                aim->value_9A = 0;
                aim->value_9B = 0;
                wp->routine_2++;
            }
            break;
        case 16:
            if (func_8011F150((STAGE_OBJ *)wp, -5) != 0)
            {
                wp->routine_1 = 1;
                wp->routine_2 = 0;
                wp->routine_3 = 0;
            }
            break;
    }
}

void func_8011E9D0(STAGE_OBJ *wp)
{
    wp->routine_0 = 2;
    wp->routine_1 = 0;
    wp->routine_2 = 0;
    wp->routine_3 = 0;
}

sint32 func_8011E9E8(STCOM_SVECTOR *pos)
{
    sint32 x;
    sint32 z;
    sint32 nx;

    x = pos->x;
    z = pos->z - 0x400;
    if (x < 0x538 && z < 0x538 && x >= -0x537 && z >= -0x537)
    {
        nx = -x;
        if (z < x + 0x8E5 && z < nx + 0x8E5 && x - 0x8E5 < z)
        {
            if (nx - 0x8E5 < z)
            {
                return 1;
            }
        }
    }
    return 0;
}

sint32 func_8011EA54(STCOM_SVECTOR *pos)
{
    sint32 x;
    sint32 z;
    sint32 nx;

    x = pos->x;
    z = pos->z - 0x400;
    if (x < 0x59C && z < 0x59C && x >= -0x59B && z >= -0x59B)
    {
        nx = -x;
        if (z < x + 0x973 && z < nx + 0x973 && x - 0x973 < z)
        {
            if (nx - 0x973 < z)
            {
                return 1;
            }
        }
    }
    return 0;
}

sint32 func_8011EAC0(STCOM_SVECTOR *pos)
{
    return pos->x * pos->x + (pos->z - 0x400) * (pos->z - 0x400) <= 0xC5C0F;
}

void func_8011EAFC(ST1A_OBJ *wp, sint32 arg)
{
    ST1A_HITS *hits;
    STCOM_SVECTOR v;
    sint32 i;

    hits = (ST1A_HITS *)&wp->hit_440;
    for (i = 0; i < 8; i++)
    {
        ApplyMatrixSV(&(&wp->matrix_240)[D_80132F90[i].part_7].m, (STCOM_SVECTOR *)&D_80132F90[i], &v);
        v.x += wp->part_180[D_80132F90[i].part_7].x;
        v.y += wp->part_180[D_80132F90[i].part_7].y;
        v.z += wp->part_180[D_80132F90[i].part_7].z;
        func_800341BC(&v, D_80132F90[i].radius_6, 0, 0x8000, wp->value_1, &hits->hit_8[i], D_80133020[hits->kind_E0][arg], 0, 0);
    }
    for (i = 8; i < 18; i++)
    {
        ApplyMatrixSV(&(&wp->matrix_240)[D_80132F90[i].part_7].m, (STCOM_SVECTOR *)&D_80132F90[i], &v);
        v.x += wp->part_180[D_80132F90[i].part_7].x;
        v.y += wp->part_180[D_80132F90[i].part_7].y;
        v.z += wp->part_180[D_80132F90[i].part_7].z;
        func_800341BC(&v, D_80132F90[i].radius_6, 0, 0x8000, wp->value_1, &hits->hit_8[i], D_80133040[hits->kind_E0][arg], 0, 0x80);
    }
}

void func_8011ED6C(ST1A_OBJ *wp)
{
    ST1A_HITS *hits;
    sint32 damage;
    sint32 i;
    sint32 unit;

    hits         = (ST1A_HITS *)&wp->hit_440;
    wp->value_B2 = wp->value_6E;
    for (i = 0; i < 18; i++)
    {
        damage = hits->hit_8[i].damage_0 & 0xFFFFFF;
        if (damage != 0)
        {
            break;
        }
    }
    for (i = 0; i < 18; i++)
    {
        hits->hit_8[i].damage_0 = 0;
    }
    if (wp->value_6E < damage)
    {
        if (STAGE_PL.value_6E >= 0)
        {
            STAGE_PL.value_449 = 1;
            wp->value_6E       = 0;
            hits->value_98     = -1;
            wp->routine_1      = 7;
            wp->routine_2      = 0;
            wp->routine_3      = 0;
        }
        else
        {
            wp->value_6E = 0;
        }
    }
    else if (damage != 0)
    {
        Sound_call2(0xA0, &wp->position);
        wp->scale.v.pad = 0x7FFF;
        wp->value_6E -= damage;
    }
    else
    {
        wp->scale.v.pad = 0x4210;
    }
    if (wp->value_6E != wp->value_B2)
    {
        unit = wp->value_B0 >> 6;
        if (wp->value_6E <= unit * 6)
        {
            if (!(hits->cried_DC & 1))
            {
                hits->cried_DC |= 1;
                Sound_call2(0x204, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 12)
        {
            if (!((hits->cried_DC >> 1) & 1))
            {
                hits->cried_DC |= 2;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 16)
        {
            if (!((hits->cried_DC >> 2) & 1))
            {
                hits->cried_DC |= 4;
                Sound_call2(0x203, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 19)
        {
            if (!((hits->cried_DC >> 3) & 1))
            {
                hits->cried_DC |= 8;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 25)
        {
            if (!((hits->cried_DC >> 4) & 1))
            {
                hits->cried_DC |= 0x10;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 32)
        {
            if (!((hits->cried_DC >> 5) & 1))
            {
                hits->cried_DC |= 0x20;
                Sound_call2(0x202, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 38)
        {
            if (!((hits->cried_DC >> 6) & 1))
            {
                hits->cried_DC |= 0x40;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 44)
        {
            if (!((hits->cried_DC >> 7) & 1))
            {
                hits->cried_DC |= 0x80;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 48)
        {
            if (!((hits->cried_DC >> 8) & 1))
            {
                hits->cried_DC |= 0x100;
                Sound_call2(0x201, &wp->position);
            }
        }
        else if (wp->value_6E <= unit * 51)
        {
            if (!((hits->cried_DC >> 9) & 1))
            {
                hits->cried_DC |= 0x200;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
        else if (wp->value_6E <= unit * 57)
        {
            if (!((hits->cried_DC >> 10) & 1))
            {
                hits->cried_DC |= 0x400;
                if (rand() & 1)
                {
                    Sound_call2(0x1FA, &wp->position);
                }
                else
                {
                    Sound_call2(0x1FB, &wp->position);
                }
            }
        }
    }
}

sint32 func_8011F150(STAGE_OBJ *wp, sint32 dy)
{
    sint32 landed;

    landed = 0;
    wp->position.y += dy;
    if (wp->position.y < -0x32)
    {
        wp->position.y = -0x33;
        landed         = 1;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    return landed;
}

sint32 func_8011F1AC(STAGE_OBJ *wp, sint32 dy)
{
    sint32 landed;

    landed = 0;
    wp->position.y += dy;
    if (wp->position.y >= -1)
    {
        wp->position.y = -1;
        landed         = 1;
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
    return landed;
}

void func_8011F208(void)
{
    STAGE_10C *slot;

    slot = Open_SHL_WORK();
    if (slot != NULL)
    {
        slot->flags_0   = 1;
        slot->kind_2    = 0x32;
        slot->variant_3 = 1;
        slot->position  = Player_work.position;
        slot->position.y -= 0x3E8;
    }
}

STAGE_OBJ *func_8011F27C(void)
{
    STAGE_OBJ *op;

    op = func_80031498();
    if (op != NULL)
    {
        op->flags_0    = 1;
        op->kind_2     = 0x16;
        op->position.y = -0x33;
        op->position.z = 0x400;
        op->position.x = 0;
        op->value_4    = 0;
        op->rotation.x = op->rotation.y = op->rotation.z = 0;
        op->value_44.half[0] = op->value_44.half[1] = op->value_48.half[0] = 0;
        op->flags_6 |= 0x20;
        op->position_fixed.v.x  = op->position.x << 16;
        op->position_fixed.v.y  = op->position.y << 16;
        op->position_fixed.v.z  = op->position.z << 16;
        op->position_prev       = op->position;
        op->position_fixed_prev = op->position_fixed.v;
        op->rotation_prev       = op->rotation;
        func_8005D7C0();
        op->life_prev_B2 = op->life_max_B0 = op->life_6E = D_8009884C[op->kind_2]->life_8 << 8;
        func_8005D620(op, 0, 0, 0x81, 0x806468);
        func_8005D4D4();
        return op;
    }
    return NULL;
}

void func_8011F3E0(ST1A_OBJ *wp)
{
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->value_44.value = 0;
            wp->value_48.value = 0;
            wp->scale.words[0] = 0x02000200;
            wp->scale.words[1] = 0x42100200;
            wp->value_78       = 0;
            func_800322A8(wp, 0x14, 0);
            wp->u_C.b.byte_C = 0;
            wp->u_C.b.byte_D = 0;
            wp->u_E.b.byte_E = 0;
            wp->u_E.b.byte_F = 0;
            wp->routine_0++;
            break;
        case 1:
            if (wp->value_44.half[0] != 0)
            {
                Obj_pos_set(wp, wp->value_44.half[0], 0, 0);
            }
            if (wp->u_C.b.byte_C == 0)
            {
                func_80032488(wp);
            }
            else
            {
                func_800322A8(wp, wp->u_C.b.byte_D, 0);
                wp->u_C.b.byte_C = 0;
            }
            break;
    }
}
