#include "common.h"
#include "st06.h"

void func_8010BD58(ST06_ACTOR *wp)
{
    wp->scale.v.pad = 0x4210;
    if (wp->flags_0 & 2)
    {
        func_8002C8CC(wp, 0x30, 0x200, 0);
    }
    D_80125150[wp->variant_3](wp);
    if (wp->routine_1 != 0)
    {
        func_80051B68(wp, 3, -1, 0);
    }
    else
    {
        func_80051B68(wp, 1, -1, 0);
    }
}

void func_8010BDEC(STAGE_OBJ *wp)
{
    D_80125130[wp->routine_0](wp);
}

void func_8010BE28(STAGE_OBJ *wp)
{
    D_8012513C[wp->routine_0](wp);
}

// Statement order found by search; retail stores position_prev.z twice.
void func_8010BE64(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    func_8002F9C4(wp, NULL);
    wp->position_fixed.x      = wp->position.x << 16;
    wp->value_78              = NULL;
    wp->data_10               = NULL;
    wp->position_fixed.y      = wp->position.y << 16;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->position_fixed.z      = wp->position.z << 16;
    wp->position_fixed_prev.x = wp->position_fixed.x;
    wp->position_fixed_prev.y = wp->position_fixed.y;
    wp->position_prev.z       = wp->position.z;
    wp->scale.words[0]        = 0x2000200;
    wp->position_prev.x       = wp->position.x;
    wp->position_prev.y       = wp->position.y;
    wp->velocity.v.x          = 0;
    wp->position_prev.z       = wp->position.z;
    wp->rotation_prev.x       = wp->rotation.x;
    wp->rotation_prev.y       = wp->rotation.y;
    wp->velocity.v.y          = 0;
    wp->scale.words[1]        = 0x200;
    wp->rotation_prev.z       = wp->rotation.z;
    wp->scale.v.pad           = 0x4210;
    wp->velocity.v.z          = 0;
    wp->accel_4C.x            = 0;
    wp->accel_4C.y            = 0;
    wp->accel_4C.z            = 0;
    wp->routine_1             = 0;
    wp->turn_64               = 0x80;
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_8010BF78(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    STCOM_FIXED_VECTOR cam;

    pl = &Player_work;
    if (Player_work.target_184 == wp)
    {
        pl->target_184 = NULL;
        pl->flags_0 &= ~2;
        pl->flags_bd |= 0x80;
        cam.x = wp->value_180.x;
        cam.y = wp->value_180.y - 0x20;
        cam.z = wp->value_180.z;
        func_80039FAC(&cam, 0x100, func_80031198(&pl->position, &wp->position) + 0x800, D_800A396C);
        func_800322A8(wp, 1, 0);
        D_8012BA08    = func_80031198(&wp->position, &pl->position);
        wp->routine_0 = 2;
        return;
    }
    if (wp->value_D == 0)
    {
        func_80032488(wp);
        return;
    }
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
}

void func_8010C090(STAGE_OBJ *wp)
{
    func_8002FEA4(wp, wp->value_44.half[0], 0, 0);
    if (wp->u_C.b.byte_D == 0)
    {
        func_80032488(wp);
    }
    else
    {
        func_800322A8(wp, wp->u_E.b.byte_E, 0);
        wp->u_C.b.byte_D = 0;
    }
}

void func_8010C0F4(ST06_ACTOR *wp)
{
    wp->flags_0 |= 2;
    func_8002F9C4(wp, NULL);
    wp->data_10               = D_80125158;
    wp->scale.words[0]        = 0x2000200;
    wp->scale.words[1]        = 0x200;
    wp->rotation.x            = 0;
    wp->rotation.z            = 0;
    wp->value_78              = 0;
    wp->velocity.v.x          = 0;
    wp->velocity.v.y          = 0;
    wp->position_fixed.x      = wp->position.x << 16;
    wp->position_fixed.y      = wp->position.y << 16;
    wp->position_fixed.z      = wp->position.z << 16;
    wp->scale.v.pad           = 0x4210;
    wp->position_fixed_prev.x = wp->position_fixed.x;
    wp->position_fixed_prev.y = wp->position_fixed.y;
    wp->position_fixed_prev.z = wp->position_fixed.z;
    wp->position_prev.x       = wp->position.x;
    wp->position_prev.y       = wp->position.y;
    wp->position_prev.z       = wp->position.z;
    wp->rotation_prev.x       = wp->rotation.x;
    wp->rotation_prev.y       = wp->rotation.y;
    wp->rotation_prev.z       = wp->rotation.z;
    wp->velocity.v.z          = 0;
    wp->accel_4C.x            = 0;
    wp->accel_4C.y            = 0;
    wp->accel_4C.z            = 0;
    wp->turn_64               = 0x80;
    func_800322A8(wp, wp->value_E, 0);
    wp->value_D = 0;
    wp->routine_0++;
}

void func_8010C20C(ST06_ACTOR *wp)
{
    sint16 turn;

    turn           = func_80031D5C(D_8012BA08, wp->rotation.y, wp->turn_64);
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_80063BC8(&wp->position, 3, 0, wp->timer_C);
        func_800322A8(wp, 8, 0);
        wp->routine_1 = 1;
        wp->routine_0++;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010C2B4(STAGE_OBJ *wp)
{
    if ((sint8)*D_800987B0 == 0)
    {
        func_80039E18();
        func_800322A8(wp, 1, 0);
        wp->routine_0++;
        return;
    }
    func_80032488(wp);
}

void func_8010C318(ST06_ACTOR *wp)
{
    STCOM_PL_WORK *pl;
    sint16 turn;

    turn           = func_80031D5C(wp->rotation_prev.y, wp->rotation.y, wp->turn_64);
    pl             = &Player_work;
    wp->rotation.y = (wp->rotation.y + turn) & 0xFFF;
    if (turn == 0 && func_8003A13C() == 0)
    {
        func_800322A8(wp, 0, 0);
        wp->routine_1 = 0;
        pl->flags_bd &= ~0x80;
        pl->flags_0 |= 2;
        wp->routine_0 = 1;
    }
    else
    {
        func_80032488(wp);
    }
}

void func_8010C3CC(STAGE_OBJ *wp)
{
    D_80125164[wp->variant_3](wp);
}

void func_8010C408(STAGE_OBJ *wp)
{
    if (wp->routine_0 == 0)
    {
        wp->flags_0 |= 2;
        func_8002F9EC(wp, NULL);
        wp->scale.words[0] = 0x2000200;
        wp->scale.words[1] = 0x200;
        wp->scale.v.pad    = 0x4210;
        func_800322A8(wp, 0, 0);
        wp->routine_0++;
        return;
    }
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    func_80032488(wp);
}
