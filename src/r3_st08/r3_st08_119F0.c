#include "common.h"
#include "st08.h"

void func_801119F0(STAGE_WORK *wp)
{
    D_8011847C[wp->routine_0](wp);
}

void func_80111A2C(ST08_EV *wp)
{
    wp->key_20 = Stage_hed_model_get(0x40100);
    if (wp->key_20 == 0)
    {
        Close_EVE_WORK(wp);
        return;
    }
    wp->value_14 = wp->value_16 = wp->value_17 = wp->value_18 = wp->value_15 = 0;
    wp->value_19                                                             = D_80118345;
    wp->value_1A                                                             = D_8011837F[wp->value_15 * 2];
    wp->value_1B                                                             = D_801183B9[wp->value_16 * 2];
    wp->value_1C                                                             = D_801183F3[wp->value_17 * 2];
    wp->value_1D                                                             = D_8011842D[wp->value_18 * 2];
    wp->routine_0++;
}

void func_80111B08(ST08_ANIM_EV *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK unpack;
    sint16 i;

    unpack = func_8002DC84((void *)wp->key_20, 0, 6);
    for (i = 0; i < 5; i++)
    {
        if (--wp->timer_19[i] == 0)
        {
            wp->step_14[i]++;
            if (D_80118344[i][wp->step_14[i]][0] == 0xFF)
            {
                wp->step_14[i] = 0;
            }
            wp->timer_19[i] = D_80118344[i][wp->step_14[i]][1];
            uv              = func_8002DD1C(unpack.c, i);
            uv.b[0]         = D_80118468[i][0] + D_80118344[i][wp->step_14[i]][0] * 0x30;
            uv.b[2]         = D_80118468[i][1] + D_80118344[i][wp->step_14[i]][0] * 0x30;
            uv.b[4]         = D_80118468[i][2] + D_80118344[i][wp->step_14[i]][0] * 0x30;
            uv.b[6]         = D_80118468[i][3] + D_80118344[i][wp->step_14[i]][0] * 0x30;
            func_8002DE04(unpack.c, i, uv.w);
        }
    }
}

void func_80111D24(STAGE_WORK *wp)
{
    D_80118508[wp->routine_0](wp);
}

void func_80111D60(ST08_EV1C *wp)
{
    wp->key_1C = Stage_hed_model_get(0x30100);
    if (wp->key_1C == 0)
    {
        Close_EVE_WORK(wp);
        return;
    }
    wp->value_14 = wp->value_16 = wp->value_17 = wp->value_18 = wp->value_15 = 0;
    wp->value_16                                                             = D_80118485;
    wp->value_17                                                             = D_801184BF[wp->value_15 * 2];
    wp->value_18                                                             = D_801184F9[wp->value_16 * 2];
    wp->value_19                                                             = D_80118533[wp->value_17 * 2];
    wp->value_1A                                                             = D_8011856D[wp->value_18 * 2];
    wp->routine_0++;
}

void func_80111E3C(ST08_ANIM2_EV *wp)
{
    STAGE_UV4 uv;
    STAGE_UNPACK unpack;
    sint16 i;
    uint32 frame; // the frame as 16.16: u steps by 0x40 (frame & 3), v by 0x30 (frame >> 2)

    for (i = 0; i < 2; i++)
    {
        if (--wp->timer_16[i] == 0)
        {
            wp->step_14[i]++;
            if (D_80118484[i][wp->step_14[i]][0] == 0xFF)
            {
                wp->step_14[i] = 0;
            }
            wp->timer_16[i] = D_80118484[i][wp->step_14[i]][1];
            unpack          = func_8002DC84((void *)wp->key_1C, 0, 5);
            uv              = func_8002DD1C(unpack.c, i);
            frame           = D_80118484[i][wp->step_14[i]][0] << 16;
            uv.b[0]         = D_801184F8[i][0] + (frame >> 10);
            uv.b[2]         = D_801184F8[i][1] + (frame >> 10);
            uv.b[4]         = D_801184F8[i][2] + (frame >> 10);
            uv.b[6]         = D_801184F8[i][3] + (frame >> 10);
            uv.b[1]         = D_80118500[i][0] + (frame >> 18) * 0x30;
            uv.b[3]         = D_80118500[i][1] + (frame >> 18) * 0x30;
            uv.b[5]         = D_80118500[i][2] + (frame >> 18) * 0x30;
            uv.b[7]         = D_80118500[i][3] + (frame >> 18) * 0x30;
            func_8002DE04(unpack.c, i, uv.w);
        }
    }
}
