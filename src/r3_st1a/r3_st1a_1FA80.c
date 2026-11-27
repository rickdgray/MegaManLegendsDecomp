#include "common.h"
#include "st1a.h"

void func_8011FA80(STAGE_OBJ *wp)
{
    D_80133084[wp->routine_0](wp);
}

void func_8011FABC(ST1A_EMITTER *wp)
{
    wp->routine_0   = 1;
    wp->routine_1   = 0;
    wp->routine_2   = 0;
    wp->routine_3   = 0;
    wp->count_C     = 0;
    wp->frame_D     = 0;
    wp->left_E      = 0x18;
    wp->origin_90.x = wp->position.x = wp->position_fixed.f.x.words.integer;
    wp->origin_90.y = wp->position.y = wp->position_fixed.f.y.words.integer;
    wp->origin_90.z = wp->position.z = wp->position_fixed.f.z.words.integer;
    wp->position_fixed_prev          = wp->position_fixed.v;
    wp->position_prev                = wp->position;
    wp->angle_CC                     = ratan2(Player_work.position.x - wp->position.x, Player_work.position.z - wp->position.z);
}

void func_8011FB90(ST1A_EMITTER *wp)
{
    ST1A_VIEW_G *owner;
    STAGE_FX *fx;
    owner = func_80036294(wp->id_F);
    fx    = (STAGE_FX *)func_80031618();
    if (fx != NULL)
    {
        fx->be_flag    = 1;
        fx->id         = 0x13;
        fx->type       = 0;
        fx->value_C    = wp->slot;
        fx->timer_D    = wp->frame_D;
        fx->u_28.count = wp->angle_CC;
        fx->x_1C       = owner->vec_188.x;
        fx->y_1E       = owner->vec_188.y;
        fx->z_20       = owner->vec_188.z;
        wp->count_C++;
        if (--wp->left_E == 0)
        {
            wp->routine_0++;
        }
    }
    wp->frame_D++;
}

void func_8011FC74(STAGE_OBJ *wp)
{
    if (wp->u_C.b.byte_C == 0)
    {
        Close_SHL_WORK(wp);
    }
}
