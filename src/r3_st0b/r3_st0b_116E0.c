#include "common.h"
#include "st0b.h"

// The lifts' model scale, copied by several routines.
const STCOM_FIXED_VECTOR D_80100284 = {0x200, 0x200, 0x200, 0};

void func_801116E0(STAGE_OBJ *wp)
{
    D_8011B76C[wp->routine_0](wp);
}

void func_8011171C(ST0B_10C_E *wp)
{
    ST0B_10C_E *obj;

    obj                = STAGE_SCENE_OBJ(0);
    wp->position       = obj->position;
    wp->position_fixed = obj->position_fixed;
    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->color_B4 = 0x808080;
    wp->value_78 = 0;
    STAGE_MATRIX_IDENTITY(wp->matrix_8C.w);
    wp->routine_0++;
    ScaleMatrix(&wp->matrix_8C.m, &D_8011B778);
    wp->position_AC = wp->position;
}

void func_8011180C(ST0B_10C_C *wp)
{
    ST0B_10C_C *obj;

    obj                = STAGE_SCENE_OBJ(0);
    wp->position       = obj->position;
    wp->position_fixed = obj->position_fixed;
    wp->value_58       = 0;
    wp->position_AC    = wp->position;
}

void func_80111884(ST0B_10C_D *wp)
{
    ST0B_10C_D *obj;

    obj                = STAGE_SCENE_OBJ(0);
    wp->position       = obj->position;
    wp->position_fixed = obj->position_fixed;
    wp->value_C ^= 1;
    wp->position_AC = wp->position;
    if (wp->value_C & 1)
    {
        wp->position_AC.x += 8;
    }
    else
    {
        wp->position_AC.x -= 8;
    }
}

void func_80111934(STAGE_10C *wp)
{
    D_8011BB84[wp->variant_3](wp, &wp->x_CC);
}

void func_80111970(ST0B_LIFT *wp, ST0B_PATH *path)
{
    STCOM_FIXED_VECTOR scale;

    scale                   = D_80100284;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_8011BB98[wp->routine_0](wp, path);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
}

void func_80111A9C(ST0B_ACTOR_B *wp, uint16 *bob)
{
    STAGE_FX *fx;

    wp->flags_0 = (uint8)wp->flags_0 | 6;
    if (STAGE_GAME.value_50 == 0xD)
    {
        func_8002F9EC(wp, 0);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->color_B4     = 0x808080;
    wp->data_10      = NULL;
    bob[0]           = 0;
    bob[1]           = wp->position.y;
    wp->velocity.v.x = 0;
    wp->velocity.v.y = 0;
    wp->velocity.v.z = 0;
    fx               = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 0x15;
        fx->variant_3 = 0;
        fx->value_C   = wp->value_1;
        fx->timer_D   = 0;
        fx->flags_6 |= 0x20;
    }
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 0x15;
        fx->variant_3 = 1;
        fx->value_C   = wp->value_1;
        fx->flags_6 |= 0x20;
    }
    wp->routine_0++;
}

void func_80111BB4(ST0B_ACTOR_C *wp, uint16 *bob)
{
    STAGE_SCENE_WORK *scene;

    scene = &Scene_work;
    switch (wp->routine_1)
    {
        case 0:
            wp->position.y = bob[1] + ((D_800BBCF8[bob[0] & 0x3F] * 5) >> 12);
            bob[0]++;
            wp->position_fixed.y = wp->position.y << 16;
            break;
        case 1:
            wp->timer_C          = 1;
            wp->position.y       = bob[1];
            wp->position_fixed.y = wp->position.y << 16;
            wp->routine_1++;
            // fall through
        case 2:
            if (wp->velocity.v.x < 0x190)
            {
                wp->velocity.v.x += 8;
            }
            if ((uint32)(scene->value_10 - 0x14) < 0x64)
            {
                wp->rotation.y += 8;
            }
            else if (scene->value_10 == 0x78)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            if (wp->velocity.v.x < 0x300)
            {
                wp->velocity.v.x += 0x10;
            }
            break;
    }
    Obj_pos_set(wp, wp->velocity.v.x, 0, 0);
    func_80030150(&wp->position_fixed, &wp->position);
}

void func_80111D44(ST0B_LIFT *wp, ST0B_PATH *path)
{
    STCOM_FIXED_VECTOR scale;

    scale                   = D_80100284;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    D_8011BBA0[wp->routine_0](wp, &wp->path);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
    func_8011250C(wp, &wp->path);
    wp->hit_BC = 0;
    wp->hit_C4 = 0;
}

void func_80111E90(ST0B_LIFT *wp, ST0B_PATH_B *path)
{
    STAGE_FX *fx;
    STCOM_SVECTOR *origin[2];

    wp->flags_0 |= 6;
    Model_work_init(wp, NULL);
    wp->velocity.v.x = 0x100;
    wp->color_B4     = 0x808080;
    wp->data_10      = NULL;
    wp->velocity.v.y = 0;
    wp->velocity.v.z = 0;
    path->x_10       = wp->velocity.v.x << 16;
    path->z_14       = wp->velocity.v.z << 16;
    path->rot_20     = wp->rotation.y << 16;
    if (wp->variant_3 == 1)
    {
        path->step_2C = (ST0B_PATH_STEP *)D_8011B788;
    }
    else
    {
        path->step_2C = (ST0B_PATH_STEP *)D_8011B9EC;
    }
    func_801123C0(wp, path);
    wp->hit_BC   = 0;
    wp->value_C0 = 0;
    wp->hit_C4   = 0;
    wp->value_C8 = 0;
    fx           = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 0x15;
        fx->variant_3 = 0;
        fx->value_C   = wp->value_1;
        fx->timer_D   = 0;
        fx->flags_6 |= 0x20;
    }
    fx = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->flags_0   = 1;
        fx->kind_2    = 0x15;
        fx->variant_3 = 1;
        fx->value_C   = wp->value_1;
        fx->flags_6 |= 0x20;
    }
    origin[1]     = &wp->position;
    origin[0]     = &wp->position;
    path->grid_28 = (ST0B_GRID_OBJ_C *)func_80109CB0((STAGE_OBJ *)wp, 2, origin[0]);
    wp->routine_0++;
    wp->routine_1 = 0;
}

// ported from r3_st0d func_80104444
void func_80112004(ST0B_LIFT *wp, ST0B_PATH_D *path)
{
    sint32 dx;
    sint32 dz;
    sint32 damage;
    sint32 damage2;

    damage  = 0;
    damage2 = 0;
    if (--path->timer_4 <= 0)
    {
        if (path->timer_4 == 0)
        {
            path->x_10   = path->x_6 << 16;
            path->z_14   = path->z_8 << 16;
            path->rot_20 = path->rot_A << 16;
            if (path->next_C < 0)
            {
                if (path->next_C != -1)
                {
                    path->step_2C = &D_8011BB48[path->next_C & 0x7F];
                }
            }
            else
            {
                path->step_2C++;
            }
        }
        if (path->step_2C->flag_0 != 0)
        {
            dx = (path->step_2C->x_2 - wp->position.x) << 16;
            dz = (path->step_2C->z_4 - wp->position.z) << 16;
            wp->position_fixed.v.x += dx;
            wp->position_fixed.v.z += dz;
            wp->position_fixed_prev.x += dx;
            wp->position_fixed_prev.z += dz;
            func_80030150(&wp->position_fixed.v, &wp->position);
            func_80030150(&wp->position_fixed_prev, &wp->position_prev);
            Player_work_obj.position_fixed.v.x += dx;
            Player_work_obj.position_fixed.v.z += dz;
            Player_work_obj.position_fixed_prev.x += dx;
            Player_work_obj.position_fixed_prev.z += dz;
            func_80030150(&Player_work_obj.position_fixed.v, &Player_work_obj.position);
            func_80030150(&Player_work_obj.position_fixed_prev, &Player_work_obj.position_prev);
            path->step_2C++;
        }
        func_801123C0(wp, path);
    }
    path->x_10 += path->dx_18;
    wp->velocity.v.x = path->x_10 >> 16;
    path->z_14 += path->dz_1C;
    wp->velocity.v.z = path->z_14 >> 16;
    path->rot_20 += path->drot_24;
    wp->rotation.y = path->rot_20 >> 16;
    Obj_pos_set(wp, wp->velocity.v.x, 0, wp->velocity.v.z);
    if (wp->routine_1 == 0 && Distance_xz(&wp->position.x, &D_8011BBB8.x) < 0x40U)
    {
        path->step_2C = D_8011BB48;
        if (D_8011BB48[0].flag_0 != 0)
        {
            path->timer_4 = D_8011BB50;
        }
        else
        {
            func_801123C0(wp, path);
        }
        wp->routine_1++;
    }
    if ((wp->hit_BC & 0xFFFFFF) && (wp->hit_BC & 0x1C000000))
    {
        damage = wp->hit_BC & 0xFFFFFF;
    }
    if ((wp->hit_C4 & 0xFFFFFF) && (wp->hit_C4 & 0x1C000000))
    {
        damage2 = wp->hit_C4 & 0xFFFFFF;
    }
    if (damage < damage2)
    {
        damage = damage2;
    }
    if (damage != 0 && STAGE_GAME.value_174 == 0)
    {
        Swing_Camera2(0x1E, 0x400, 0x2800, &wp->position);
        STAGE_GAME.value_5C -= damage;
        if (STAGE_GAME.value_5C < 0)
        {
            STAGE_GAME.value_5C = 0;
        }
        if ((sint16)STAGE_GAME.value_5E / 2 >= STAGE_GAME.value_5C)
        {
            path->grid_28->u_C.flags |= 1;
        }
    }
}

void func_801123C0(ST0B_LIFT *wp, ST0B_PATH_B *path)
{
    ST0B_PATH_STEP *step;
    sint32 turn;

    step          = path->step_2C;
    path->timer_4 = step->frames_8;
    path->x_6     = step->x_2;
    path->z_8     = step->z_4;
    path->rot_A   = step->rot_6;
    path->next_C  = step->next_A;
    path->dx_18   = ((path->x_6 - wp->velocity.v.x) << 16) / path->timer_4;
    path->dz_1C   = ((path->z_8 - wp->velocity.v.z) << 16) / path->timer_4;
    turn          = (path->rot_A - wp->rotation.y) & 0xFFF;
    if (turn > 0x800)
    {
        turn -= 0x1000;
    }
    if (turn < -0x800)
    {
        turn = 0x1000 - turn;
    }
    path->drot_24 = (turn << 16) / path->timer_4;
}

void func_8011250C(ST0B_LIFT *wp, ST0B_PATH_C *path)
{
    if (wp->flags_0 & 1)
    {
        path->box_38 = wp->position;
        path->box_30 = path->box_38;
        path->box_38.y -= 0x280;
        func_800341BC(&path->box_30, 0x100, 0, 0, wp->value_1, &wp->hit_BC, 0x2000000, 0, 0);
        func_800341BC(&path->box_38, 0x60, 0, 0, wp->value_1, &wp->hit_C4, 0x2000000, 0, 0);
    }
}

void func_80112608(STAGE_PROP *wp, uint16 *bob)
{
    STCOM_FIXED_VECTOR scale;

    scale                   = D_80100284;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8011BBA8[wp->routine_0](wp, bob);
    wp->position.y = bob[1] + ((D_800BBCF8[bob[0] & 0x3F] * 5) >> 12);
    bob[0]++;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
    func_80051B68(wp, 1, -1, 0);
}

void func_801127A0(ST0B_ACTOR *wp, uint16 *bob)
{
    wp->flags_0 = (uint8)wp->flags_0 | 6;
    if (STAGE_GAME.value_50 == 0xD)
    {
        func_8002F9EC(wp, 0);
    }
    else
    {
        Model_work_init(wp, NULL);
    }
    wp->color_B4     = 0x808080;
    wp->data_10      = D_8011BBC0;
    wp->timer_C      = 0;
    wp->value_E      = 1;
    bob[0]           = 0;
    bob[1]           = wp->position.y;
    wp->velocity.v.x = 0;
    wp->velocity.v.y = 0;
    wp->velocity.v.z = 0;
    wp->routine_1    = 0;
    wp->routine_0++;
}

// Same as r3_st0d's func_80104C9C: everything matches but the D_800C356D zero store, which sched hoists above the z store (retail: after the z store and the angle load).
void func_8011285C(ST0B_ACTOR *wp, uint16 *bob)
{
    sint32 msg;
    sint32 flag_on;
    sint32 flag;
    ST0B_CAM_SHOT *shot;
    STCOM_PL_WORK *pl;

    pl      = &Player_work;
    msg     = D_8011BBCC[wp->value_D];
    flag_on = D_8011BBE0[wp->value_D];
    flag    = D_8011BC2C[wp->value_D];
    switch (wp->routine_1)
    {
        case 0:
            if (pl->target_184 == wp)
            {
                pl->target_184 = NULL;
                pl->flags_bd |= 0x40;
                wp->routine_1++;
            }
            break;
        case 1:
            if (msg != 0x7FFFFFFF)
            {
                MojiTaskExec2(0, msg);
            }
            wp->routine_1++;
            break;
        case 2:
            if (msg != 0x7FFFFFFF)
            {
                if (Moji_flag & 0x8000000)
                {
                    break;
                }
                if (flag != 0x7FFFFFFF)
                {
                    if (Sce_flag_test(flag))
                    {
                        Fade_start(10);
                        wp->routine_1 = 3;
                    }
                    else
                    {
                        wp->value_E   = 0;
                        wp->routine_1 = 4;
                    }
                }
                else
                {
                    wp->routine_1 = 4;
                }
            }
            else if (flag != 0x7FFFFFFF)
            {
                if (Sce_flag_test(flag))
                {
                    Fade_start(10);
                    wp->routine_1 = 3;
                }
                else
                {
                    wp->value_E   = 0;
                    wp->routine_1 = 4;
                }
            }
            else
            {
                wp->routine_1 = 4;
            }
            break;
        case 3:
            if (D_80098A72 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 4:
            pl->flags_bd &= ~0x40;
            wp->routine_1++;
            break;
        case 5:
            if (flag_on != 0x7FFFFFFF && (flag == 0x7FFFFFFF || Sce_flag_test(flag)))
            {
                Sce_flag_on(flag_on);
            }
            if (wp->value_E == 1)
            {
                shot = D_8011BC18[wp->value_D];
                if (shot != (ST0B_CAM_SHOT *)0x7FFFFFFF)
                {
                    STAGE_CAM_REQ_PTR->mode_C   = shot->value_8;
                    STAGE_CAM_REQ_PTR->value_E  = shot->value_9;
                    STAGE_CAM_REQ_PTR->value_F  = shot->value_A;
                    STAGE_CAM_REQ_PTR->x_0      = shot->x_0;
                    STAGE_CAM_REQ_PTR->y_2      = shot->y_2;
                    STAGE_CAM_REQ_PTR->z_4      = shot->z_4;
                    STAGE_CAM_REQ_PTR->angle_A  = shot->value_6;
                    STAGE_CAM_REQ_PTR->value_D  = 0;
                    STAGE_CAM_REQ_PTR->value_11 = 0xFF;
                    if (wp->value_D == 4)
                    {
                        STAGE_CAM_REQ_PTR->value_10 = 0xFF;
                    }
                    else
                    {
                        STAGE_CAM_REQ_PTR->value_10 = 2;
                    }
                }
                func_80052528(wp);
                Close_SHL_WORK(wp);
            }
            else
            {
                wp->value_E   = 1;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_80112B00(STAGE_PROP *wp, uint16 *bob)
{
    STCOM_FIXED_VECTOR scale;
    scale                   = D_80100284;
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    D_8011BBB0[wp->routine_0](wp, bob);
    RotMatrixYXZ(&wp->rotation, &wp->matrix_8C.m);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    wp->position_AC = wp->position;
}

void func_80112C18(STAGE_OBJ *wp, uint16 *bob)
{
    if (wp->u_C.b.byte_C == 0)
    {
        wp->position.y = bob[1] + ((D_800BBCF8[bob[0] & 0x3F] * 5) >> 12);
        bob[0]++;
    }
    else
    {
        wp->position.y = bob[1];
    }
    wp->position_fixed.v.x = wp->position.x << 16;
    wp->position_fixed.v.y = wp->position.y << 16;
    wp->position_fixed.v.z = wp->position.z << 16;
}

void func_80112CA8(ST0B_10C *wp)
{
    if (wp->routine_0 != 0)
    {
        func_80113120(wp);
    }
    D_8011BC58[wp->routine_0](wp);
    func_801131F0(wp);
}

void func_80112D10(ST0B_TRAIL5 *wp)
{
    STCOM_FIXED_VECTOR unused;

    wp->data_78             = D_8011BC40;
    wp->sprite.mode_0       = 0x3DC8002A;
    wp->sprite.color_4.word = 0x2E808080;
    wp->flags_0 |= 2;
    wp->position_fixed.v.x  = wp->position.x << 16;
    wp->position_fixed.v.y  = wp->position.y << 16;
    wp->position_fixed.v.z  = wp->position.z << 16;
    wp->value_C4            = 0;
    wp->value_C8            = 0;
    wp->sprite.pos_8[0]     = wp->position.x;
    wp->sprite.pos_8[1]     = wp->position.y;
    wp->sprite.pos_8[2]     = wp->position.z;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->position_prev       = wp->position;
    wp->trail_CC[0].v       = wp->position;
    wp->trail_CC[1].v       = wp->trail_CC[0].v;
    wp->trail_CC[2].v       = wp->trail_CC[1].v;
    wp->trail_CC[3].v       = wp->trail_CC[2].v;
    wp->trail_CC[4].v       = wp->trail_CC[3].v;
    wp->sprite.value_E      = D_8011BC4C[0].u;
    wp->sprite.value_F      = D_8011BC4C[0].v;
    wp->sprite.value_10     = 100;
    wp->speed_44[0]         = (uint32)(-rsin(wp->rotation.y) * 5) >> 1;
    wp->speed_44[1]         = 0;
    wp->speed_44[2]         = (uint32)(-rcos(wp->rotation.y) * 5) >> 1;
    wp->accel_4C[0]         = 0;
    wp->accel_4C[1]         = 0;
    wp->accel_4C[2]         = 0;
    wp->routine_2           = 0;
    wp->routine_3           = 0xB4;
    wp->value_7C            = 0;
    wp->routine_0++;
    func_801131F0((ST0B_10C *)wp);
}

void func_80112F18(ST0B_TRAIL5 *wp)
{
    wp->trail_CC[4].v = wp->trail_CC[3].v;
    wp->trail_CC[3].v = wp->trail_CC[2].v;
    wp->trail_CC[2].v = wp->trail_CC[1].v;
    wp->trail_CC[1].v = wp->trail_CC[0].v;
    wp->trail_CC[0].v = wp->position;
    wp->position_fixed.v.x += wp->speed_44[0] << 8;
    wp->position_fixed.v.y += wp->speed_44[1] << 8;
    wp->position_fixed.v.z += wp->speed_44[2] << 8;
    wp->sprite.pos_8[0] = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->sprite.pos_8[1] = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->sprite.pos_8[2] = wp->position.z = wp->position_fixed.f.z.words.integer;
    wp->rotation.y += Muku(&wp->position, &ST0B_PL_PTR->pos_3A8, wp->rotation.y & 0xFFF, 0x40);
    wp->speed_44[0] = (uint32)(-rsin(wp->rotation.y) * 5) >> 1;
    wp->speed_44[1] = 0;
    wp->speed_44[2] = (uint32)(-rcos(wp->rotation.y) * 5) >> 1;
    if (--wp->routine_3 == 0)
    {
        func_8011325C((STAGE_OBJ *)wp);
        Close_SHL_WORK(wp);
        return;
    }
    if (wp->routine_3 < 0x9D)
    {
        if (++wp->routine_2 >= 10)
        {
            wp->routine_2 = 0;
            Sound_call2(0x14B, &wp->position);
        }
    }
    func_80113324(wp);
}

void func_80113120(ST0B_10C *wp)
{
    STCOM_FIXED_VECTOR unused;

    if ((wp->value_C4 & 0x1A000000) || func_80048EA4(&wp->position, NULL, 0, 0xFFFF) < -0x10 || wp->value_7C != 0 ||
        (uint32)wp->value_80 <= 0xFFFF)
    {
        func_8011325C((STAGE_OBJ *)wp);
        Close_SHL_WORK(wp);
        return;
    }
    wp->value_34                    = wp->position_fixed.v.x;
    wp->value_38                    = wp->position_fixed.v.y;
    wp->value_3C                    = wp->position_fixed.v.z;
    wp->value_40                    = wp->position_fixed.v.pad;
    *(STCOM_SVECTOR *)&wp->value_2C = wp->position;
}

void func_801131F0(ST0B_10C *wp)
{
    func_800341BC(&wp->position, 0x64, 0, 0x8000, wp->value_1, &wp->value_C4, D_80098928[wp->kind_2]->value_9 | 0x4000000, 0, 0);
}

void func_8011325C(STAGE_OBJ *wp)
{
    STCOM_EFFECT *ep;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0         = 5;
        ep->kind_2          = 0x10;
        ep->variant_3       = 0;
        ep->value_C         = 0;
        ep->sprite.position = wp->position;
    }
    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0         = 5;
        ep->kind_2          = 0x10;
        ep->variant_3       = 1;
        ep->value_C         = 0;
        ep->sprite.position = wp->position;
    }
    func_80115068(1, 0, 8, &wp->position);
}

// Draws the trail. (wp->trail_CC + i) gives retail's addu operand order; trail_CC[i] swaps it.
void func_80113324(ST0B_TRAIL5 *wp)
{
    STCOM23_PACKET *p;
    sint32 i;
    uint32 u;
    uint32 v;

    for (i = 0; i < 5; i++)
    {
        u          = D_8011BC4C[i + 1].u;
        v          = D_8011BC4C[i + 1].v;
        p          = Billboard_get();
        p->code_4  = 0x2E808080;
        p->xy_8    = (wp->trail_CC + i)->words[0];
        p->z_10    = (wp->trail_CC + i)->words[1];
        p->uv_C    = (v << 8) | 0x3DC80000 | u;
        p->uv_14   = (v << 8) | 0x2A0000 | (u + 0x1F);
        p->uv_1C   = ((v + 0x1F) << 8) | u;
        p->uv_24   = ((v + 0x1F) << 8) | (u + 0x1F);
        p->size_18 = 0x64;
    }
}

void func_80113410(STAGE_SPARK *wp)
{
    STAGE_OBJ *owner;

    owner = wp->owner_2C;
    if (--wp->timer_D == 0 || owner->routine_0 == 2)
    {
        wp->timer_D = 0;
        wp->routine_0++;
    }
    wp->color_18 = wp->timer_D + (wp->timer_D << 8) + (wp->timer_D << 16) + 0x2E000000;
    wp->w_24 += wp->type_F;
    wp->y_1E += wp->rise_28;
}

void func_8011349C(STAGE_SPARK *wp)
{
    wp->flags_0 |= 2;
    wp->routine_0++;
    func_80113410(wp);
}

void func_801134D0(STCOM_EFFECT *arg0)
{
    func_80031988(arg0);
}

void func_801134F0(STAGE_OBJ *wp)
{
    D_8011BC60[wp->routine_0](wp);
}

void func_8011352C(ST0B_SPARK *wp)
{
    ST0B_SPARK *ep;
    sint32 i;

    if (++wp->routine_3 == 8)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->variant_3 = 1;
            ep->flags_6   = wp->flags_6;
            ep->value_C   = 0;
            ep->timer_D   = (rand() & 7) * 2 + 0x40;
            ep->x_1C      = wp->x_1C + (rand() & 0xF);
            ep->y_1E      = wp->y_1E;
            ep->z_20      = wp->z_20 + (rand() & 0xF);
            ep->mode_14   = 0x3D48004E;
            ep->u_22      = ((rand() & 3) << 5) + 0x20;
            ep->v_23      = 0;
            ep->w_24      = wp->width_E;
            ep->type_F    = wp->type_F;
            ep->rise_28   = wp->rise_28;
            ep->owner_2C  = wp;
            for (i = 0; i < wp->count_26; i++)
            {
                func_801134F0(ep);
            }
            wp->count_26  = 0;
            wp->routine_3 = rand() & 3;
        }
    }
}

void func_80113674(STAGE_OBJ *wp)
{
    if (wp->variant_3 == 1)
    {
        func_801134F0(wp);
        return;
    }
    if (wp->routine_0 != 2)
    {
        func_8011352C(wp);
        return;
    }
    func_80031988((STCOM_EFFECT *)wp);
}

ST0B_SPARK *func_801136D4(STCOM_SVECTOR *pos, sint32 width, sint32 type, sint32 count, sint32 rise, uint8 hide)
{
    ST0B_SPARK *ep;
    sint32 i;

    ep = func_80031618();
    if (ep != NULL)
    {
        ep->flags_0   = 1;
        ep->kind_2    = 0;
        ep->variant_3 = 0;
        ep->value_C   = 0;
        ep->width_E   = width;
        ep->type_F    = type;
        ep->x_1C      = pos->x;
        ep->y_1E      = pos->y;
        ep->z_20      = pos->z;
        ep->count_26  = count;
        if (hide)
        {
            ep->flags_6 |= 0x20;
        }
        else
        {
            ep->flags_6 &= ~0x20;
        }
        ep->rise_28 = rise;
        for (i = 0; i < (sint16)count; i++)
        {
            func_8011352C(ep);
        }
    }
    return ep;
}
