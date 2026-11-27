#include "common.h"
#include "st13.h"

void func_80104AF0(STAGE_OBJ *wp)
{
    D_80117660[wp->type](wp);
}

void func_80104B2C(STAGE_OBJ *wp)
{
    D_80117664[wp->routine_0](wp);
}

void func_80104B68(ST13_SPARK *wp)
{
    wp->routine_0    = 1;
    wp->ctl.shade_18 = 0x80;
    wp->ctl.timer_6  = 0x24;
    wp->routine_1    = 0;
    wp->routine_2    = 0;
    wp->routine_3    = 0;
    wp->ctl.bob_4    = 0;
    wp->be_flag |= 2;
    wp->ctl.wobble_1A   = wp->value_D;
    wp->ctl.frame_19    = rand() & 3;
    wp->ctl.origin_10.x = wp->u_1C.spr.x;
    wp->ctl.hit_8       = 0;
    wp->ctl.value_C     = 0;
    wp->ctl.origin_10.y = wp->u_1C.spr.y;
    wp->mode_14         = 0x3D08002E;
    wp->ctl.origin_10.z = wp->u_1C.spr.z;
    wp->color_18        = 0x2E000000 | (wp->ctl.shade_18 << 16) | (wp->ctl.shade_18 << 8) | wp->ctl.shade_18;
    wp->u_1C.spr.u      = D_80117644[wp->ctl.frame_19].u;
    wp->u_1C.spr.v      = D_80117644[wp->ctl.frame_19].v;
    wp->w_24            = 0x20;
    func_800341BC(&wp->u_1C.pos, 0x20, 0, 0xA000, wp->slot, &wp->ctl.hit_8, 0x68000010, 0, 0x80);
}

void func_80104C9C(ST13_SPARK *wp)
{
    ST13_SPARK_CTL *ctl;
    STCOM_SVECTOR pos;
    sint32 angle;
    sint32 c;

    ctl = &wp->ctl;
    if (func_80049C54(&wp->u_1C.pos, &wp->u_1C.pos, D_80117654, wp->slot) == 0 && !(ctl->hit_8 & 0x2000000))
    {
        wp->ctl.shade_18 = (ctl->timer_6 < 6) ? ctl->timer_6 * 16 : 0x80;
        c                = ctl->shade_18;
        wp->color_18     = 0x2E000000 | (c << 16) | (c << 8) | c;
        if (++ctl->frame_19 >= 7)
        {
            ctl->frame_19 = 0;
        }
        wp->u_1C.spr.u = D_80117644[ctl->frame_19].u;
        wp->u_1C.spr.v = D_80117644[ctl->frame_19].v;
        wp->w_24 += 2;
        ctl->wobble_1A++;
        angle = (ctl->angle_0 + ((rsin((ctl->wobble_1A & 0x3F) << 6) << 8) >> 12)) & 0xFFF;
        wp->u_1C.pos.x += (rsin(angle) * 40) >> 12;
        wp->u_1C.pos.z += (rcos(angle) * 40) >> 12;
        ctl->bob_4     = (ctl->bob_4 + 0x20) & 0xFFF;
        wp->u_1C.pos.y = ctl->origin_10.y + ((rsin(ctl->bob_4) * 80) >> 12);
        pos.x          = wp->u_1C.pos.x;
        pos.y          = wp->u_1C.pos.y;
        pos.z          = wp->u_1C.pos.z;
        pos.y          = func_80048EA4(&pos, D_80117654, 0, wp->slot);
        if (pos.y < wp->u_1C.pos.y)
        {
            wp->u_1C.pos.y = pos.y;
        }
        func_800341BC(&wp->u_1C.pos, wp->w_24, 0, 0xA000, wp->slot, &ctl->hit_8, 0x68000010, 0, 0x80);
        ctl->hit_8 = 0;
        if (--ctl->timer_6 != 0)
        {
            return;
        }
    }
    wp->routine_0++;
}

void func_80104F10(STAGE_FX *wp)
{
    STAGE_OBJ *owner;

    owner = func_80036294(wp->value_C);
    owner->u_C.b.byte_C--;
    func_80031988(wp);
}
