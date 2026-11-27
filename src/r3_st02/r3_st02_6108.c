#include "common.h"
#include "st02.h"

void func_80106108(STAGE_EV *wp)
{
    STAGE_EV *ep;
    sint32 base;
    sint32 i;

    base = (Game_work.value_50 != 2) ? 5 : 0;
    for (i = 0; i < 5; i++)
    {
        ep = Open_EVE_WORK();
        if (ep != NULL)
        {
            ep->be_flag = 1;
            ep->id      = 6;
            ep->type    = i;
            ep->step_D  = 0;
            ep->timer_C = 0;
            ep->value_F = 1;
            ep->key_1C  = Stage_hed_model_get(D_80107E24[i + base]);
            if (wp->flags & 0x20)
            {
                ep->flags |= 0x20;
            }
        }
    }
    Close_EVE_WORK(wp);
}

void func_80106200(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    sint32 u0;

    u       = func_8002DC84((void *)wp->position_fixed.v.x, 0, 4);
    uv      = func_8002DD1C(u.c, 0);
    u0      = (++wp->u_C.b.byte_C & 0x18) * 8;
    uv.b[0] = u0 + 6;
    uv.b[2] = u0 + 1;
    uv.b[4] = u0 + 0x3D;
    uv.b[6] = u0 + 0x3F;
    func_8002DE04(u.c, 0, uv.w);
}

void func_8010628C(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    sint32 u0;

    u  = func_8002DC84((void *)wp->position_fixed.v.x, 0, 4);
    uv = func_8002DD1C(u.c, 0);
    if (++wp->u_C.b.byte_C == D_80107E4C[wp->u_C.b.byte_D].hold)
    {
        wp->u_C.b.byte_D++;
        wp->u_C.b.byte_C = 0;
        if (wp->u_C.b.byte_D == 14)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
    u0      = D_80107E4C[wp->u_C.b.byte_D].frame * 0x30;
    uv.b[0] = u0 + 1;
    uv.b[2] = u0 + 0x2E;
    uv.b[4] = u0 + 1;
    uv.b[6] = u0 + 0x2E;
    func_8002DE04(u.c, 0, uv.w);
}

void func_8010636C(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    sint32 u0;

    u  = func_8002DC84((void *)wp->position_fixed.v.x, 0, 5);
    uv = func_8002DD1C(u.c, 0);
    if (++wp->u_C.b.byte_C == D_80107E68[wp->u_C.b.byte_D].hold)
    {
        wp->u_C.b.byte_D++;
        wp->u_C.b.byte_C = 0;
        if (wp->u_C.b.byte_D == 5)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
    u0      = D_80107E4C[wp->u_C.b.byte_D].frame * 0x30; // the first table's frames
    uv.b[0] = u0 + 0x2E;
    uv.b[2] = u0 + 0x2E;
    uv.b[4] = u0 + 1;
    uv.b[6] = u0 + 1;
    func_8002DE04(u.c, 0, uv.w);
}

void func_8010644C(STAGE_OBJ *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK u;
    uint8 u0;

    u  = func_8002DC84((void *)wp->position_fixed.v.x, 0, 6);
    uv = func_8002DD1C(u.c, 0);
    if (++wp->u_C.b.byte_C == D_80107E74[wp->u_C.b.byte_D].hold)
    {
        wp->u_C.b.byte_D++;
        wp->u_C.b.byte_C = 0;
        if (wp->u_C.b.byte_D == 9)
        {
            wp->u_C.b.byte_D = 0;
        }
    }
    u0      = D_80107E4C[wp->u_C.b.byte_D].frame * 0x30; // the first table's frames
    uv.b[0] = u0;
    uv.b[2] = u0 + 0x2F;
    uv.b[4] = u0;
    uv.b[6] = u0 + 0x2F;
    func_8002DE04(u.c, 0, uv.w);
}

void func_8010652C(STAGE_EV *wp)
{
    STAGE_UNPACK u;
    STAGE_UV4 uv;
    sint32 x;
    sint32 y;

    if (++wp->timer_C == D_80107E88[wp->step_D].hold)
    {
        wp->step_D++;
        wp->timer_C = 0;
        if (wp->step_D == 0xC)
        {
            wp->step_D = 0;
        }
    }
    x       = (uint8)(D_80107E88[wp->step_D].frame % 6) * 0x28;
    y       = (uint8)(D_80107E88[wp->step_D].frame / 6) * 0x28;
    u       = func_8002DC84((void *)wp->key_1C, 0, 7);
    uv      = func_8002DD1C(u.c, 0);
    uv.b[0] = x + 0x23;
    uv.b[2] = x + 0x26;
    uv.b[4] = x + 4;
    uv.b[6] = x + 1;
    uv.b[1] = y + 0x54;
    uv.b[3] = y + 0x67;
    uv.b[5] = y + 0x54;
    uv.b[7] = y + 0x67;
    func_8002DE04(u.c, 0, uv.w);
    uv      = func_8002DD1C(u.c, 1);
    uv.b[0] = x + 0x20;
    uv.b[2] = x + 0x23;
    uv.b[4] = x + 7;
    uv.b[6] = x + 4;
    uv.b[1] = y + 0x41;
    uv.b[3] = y + 0x54;
    uv.b[5] = y + 0x41;
    uv.b[7] = y + 0x54;
    func_8002DE04(u.c, 1, uv.w);
}

void func_801066DC(void)
{
}

void func_801066E4(STAGE_EV *wp)
{
    if (wp->value_F == 0)
    {
        func_80106108(wp);
        return;
    }
    D_80107EA0[wp->type](wp);
}
