#include "common.h"
#include "st06.h"

void func_8011E75C(ST06_BOAT *wp)
{
    wp->color_B4 = 0x808080;
    D_8012B7CC[wp->routine_0](wp, &wp->ctl_CC);
    func_800341BC(&wp->position, 0x200, 0, 0x8000, wp->work_id, &wp->ctl_CC.hit_10, 0x4880000, 0, 0x80);
    wp->ctl_CC.hit_10 = 0;
}

void func_8011E7E8(ST06_BOAT *wp, ST06_BOAT_CTL *ctl)
{
    switch (wp->routine_1)
    {
        case 0:
            wp->position.x = 0x870;
            wp->position.y = -0x610;
            wp->position.z = -0x328;
            wp->rotation.x = 0;
            wp->rotation.y = 0x400;
            wp->rotation.z = 0;
            wp->be_flag |= TRANS | MODEL;
            wp->position_AC = wp->position;
            Model_work_init(wp, NULL);
            wp->color_B4     = 0x808080;
            wp->data_78      = D_8012B7D8;
            wp->sway_D       = 0;
            wp->timer_C      = 0;
            ctl->flags_0     = 1;
            ctl->wave_4      = 0;
            ctl->life_prev_C = 0x180;
            ctl->life_8      = 0x180;
            wp->routine_2    = 0;
            wp->routine_1++;
            break;
        case 1:
            wp->position_prev       = wp->position;
            wp->position_fixed_prev = wp->position_fixed;
            wp->rotation_prev       = wp->rotation;
            wp->position.y          = ((D_800BBCF8[ctl->wave_4] * 16) >> 12) - 0x610;
            ctl->wave_4             = (ctl->wave_4 + 1) & 0x3F;
            if (STAGE_SCENE_PTR->reserved00[0] == 0)
            {
                wp->routine_1 = 0;
                wp->routine_2 = 0;
                wp->routine_0++;
            }
            break;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    func_8011F1B4(wp);
    wp->position_AC = wp->position;
    Model_Shadow_Trans(wp, 0x12C, 0x200, 0);
}

void func_8011EA08(ST06_BOAT *wp, ST06_BOAT_CTL *ctl)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    func_8011EEBC(wp, ctl);
    switch (wp->routine_1)
    {
        case 0:
            wp->position.y = -0xC00;
            wp->routine_1++;
            break;
        case 1:
            wp->position.x -= 0xC;
            wp->position.y = ((D_800BBCF8[ctl->wave_4] * 16) >> 12) - 0xC00;
            ctl->wave_4    = (ctl->wave_4 + 1) & 0x3F;
            if (wp->position.x < 0)
            {
                wp->position.x = 0;
                ctl->angle_2   = 0x800;
                wp->routine_1++;
            }
            break;
        case 2:
            ctl->angle_2   = (ctl->angle_2 + 2) & 0xFFF;
            wp->rotation.y = (wp->rotation.y + 2) & 0xFFF;
            wp->position.x = (uint32)(rsin(ctl->angle_2) * 0xB) >> 4;
            wp->position.z = ((rcos(ctl->angle_2) * 0xB00) >> 12) + 0x7D8;
            wp->position.y = ((D_800BBCF8[ctl->wave_4] * 16) >> 12) - 0xC00;
            ctl->wave_4    = (ctl->wave_4 + 1) & 0x3F;
            if (wp->rotation.y == 0x800)
            {
                wp->routine_1++;
            }
            break;
        case 3:
            wp->position.z += 0xC;
            wp->position.y = ((D_800BBCF8[ctl->wave_4] * 16) >> 12) - 0xC00;
            ctl->wave_4    = (ctl->wave_4 + 1) & 0x3F;
            if (wp->position.z > 0x1000)
            {
                wp->position.x = -0xB00;
                wp->position.y = -0xC00;
                wp->position.z = 0x1000;
                wp->rotation.y = 0x800;
                wp->rotation.x = 0;
                wp->rotation.z = 0;
                ctl->angle_2   = 0xC00;
                wp->routine_1  = 0;
                wp->routine_0++;
            }
            break;
    }
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    func_8011F1B4(wp);
    wp->position_AC = wp->position;
}

void func_8011ED24(ST06_BOAT *wp, ST06_BOAT_CTL *ctl)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    func_8011EEBC(wp, ctl);
    ctl->angle_2         = (ctl->angle_2 + 2) & 0xFFF;
    wp->rotation.y       = (wp->rotation.y + 2) & 0xFFF;
    wp->position.x       = (uint32)(rsin(ctl->angle_2) * 0xB) >> 4;
    wp->position.z       = ((rcos(ctl->angle_2) * 0xB00) >> 12) + 0x1000;
    wp->position.y       = ((D_800BBCF8[ctl->wave_4] * 16) >> 12) - 0xC00;
    ctl->wave_4          = (ctl->wave_4 + 1) & 0x3F;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    func_8011F1B4(wp);
    wp->position_AC = wp->position;
}

// The z jitter reuses `hit` (live across blocks, so local-alloc doesn't tie its shift to the
// result); the mask in a local keeps combine from folding (rnd << 16) >> 22 & 0xF into a srl.
void func_8011EEBC(ST06_BOAT *wp, ST06_BOAT_CTL *ctl)
{
    STCOM_FIXED_VECTOR fixed;
    STCOM_SVECTOR pos;
    STCOM_EFFECT *fx;
    uint32 rnd;
    uint16 bits;
    sint32 damage;
    sint32 mask;
    sint32 hit;

    hit    = ctl->hit_10;
    damage = hit & 0xFFFFFF;
    if (damage != 0 && (hit & 0x38000000))
    {
        if (ctl->flags_0 & 1)
        {
            ctl->life_prev_C = ctl->life_8;
            ctl->life_8 -= damage;
            if (ctl->life_8 <= 0)
            {
                ctl->flags_0 &= ~1;
                wp->timer_C   = 0;
                wp->routine_2 = 1;
                func_8001E3F0(0x1B);
            }
            Sound_call2(0xA0, &wp->position);
            wp->color_B4 = 0xFFFFFF;
        }
        else
        {
            Sound_call2(0x9B, &wp->position);
        }
    }
    switch (wp->routine_2)
    {
        case 0:
            break;
        case 1:
            if (wp->timer_C % 5 == 0)
            {
                mask = 0xF;
                fx   = func_80031618();
                if (fx != NULL)
                {
                    rnd         = rand();
                    bits        = rnd;
                    fx->be_flag = MOVE | MODEL;
                    fx->id      = 0x80;
                    fx->type    = 0x41;
                    fx->value_D = 1;
                    func_80030058(&fixed, wp->rotation.y, -0x2000, 0, 0);
                    func_80030150(&fixed, &pos);
                    if (!(rnd & 1))
                    {
                        pos.x += (rnd >> 2) & 0xF;
                    }
                    else
                    {
                        pos.x -= (rnd >> 2) & 0xF;
                    }
                    hit = (sint16)bits << 16;
                    pos.z += (hit >> 22) & mask;
                    fx->sprite.position.x = wp->position.x + pos.x;
                    fx->sprite.position.z = wp->position.z + pos.z;
                    fx->sprite.position.y = wp->position.y + ((bits >> 8) & 0xF);
                }
            }
            wp->timer_C++;
            if (wp->timer_C == 0x15)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            fx = func_80031618();
            if (fx != NULL)
            {
                fx->be_flag = MOVE;
                fx->id      = 0xB;
                fx->type    = 3;
                fx->timer_E = 0x28;
                fx->value_C = 0;
                fx->value_D = 0;
                fx->value_F = 0xC;
                func_80030058(&fixed, wp->rotation.y, -0x2000, 0, 0);
                func_80030150(&fixed, &pos);
                fx->sprite.pos_8[0] = wp->position.x + pos.x;
                fx->sprite.pos_8[1] = wp->position.y;
                fx->sprite.pos_8[2] = wp->position.z + pos.z;
                fx->routine_1       = rand() & 0xF;
            }
            break;
    }
}

void func_8011F1B4(ST06_BOAT *wp)
{
    STCOM_FIXED_VECTOR scale = {0x200, 0x200, 0x200, 0};

    if (wp->routine_2 != 0)
    {
        wp->rotation.z = D_8012B7E4[(uint8)(wp->sway_D % 36)];
        wp->sway_D++;
    }
    STAGE_MATRIX_IDENTITY(wp->matrix_8C.w);
    ScaleMatrix(&wp->matrix_8C.m, &scale);
    RotMatrixY(wp->rotation.y, &wp->matrix_8C.m);
    RotMatrixZ(wp->rotation.z, &wp->matrix_8C.m);
}

void func_8011F2B0(STAGE_OBJ *wp)
{
    D_8012B82C[wp->routine_0](wp);
}

void func_8011F2EC(ST06_10C *wp)
{
    ST06_10C *obj;

    obj                = STAGE_SCENE_OBJ(0);
    wp->position       = obj->position;
    wp->position_fixed = obj->position_fixed;
    wp->be_flag |= TRANS | MODEL;
    Model_work_init(wp, NULL);
    wp->color_B4 = 0x808080;
    wp->value_78 = 0;
    STAGE_MATRIX_IDENTITY(wp->matrix_8C.w);
    wp->routine_0++;
    ScaleMatrix(&wp->matrix_8C.m, &D_8012B838);
    wp->position_AC = wp->position;
}

void func_8011F3DC(ST06_10C *wp)
{
    ST06_10C *obj;

    obj                = STAGE_SCENE_OBJ(0);
    wp->position       = obj->position;
    wp->position_fixed = obj->position_fixed;
    wp->rotation.z     = 0;
    wp->position_AC    = wp->position;
}

void func_8011F454(ST06_10C *wp)
{
    ST06_10C *obj;

    obj                = STAGE_SCENE_OBJ(0);
    wp->position       = obj->position;
    wp->position_fixed = obj->position_fixed;
    wp->work_0 ^= 1;
    wp->position_AC = wp->position;
    if (wp->work_0 & 1)
    {
        wp->position_AC.x += 8;
    }
    else
    {
        wp->position_AC.x -= 8;
    }
}
