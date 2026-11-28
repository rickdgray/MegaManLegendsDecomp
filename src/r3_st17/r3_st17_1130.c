#include "common.h"
#include "st17.h"

void func_80101130(STAGE_OBJ *wp)
{
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    wp->anim_prev_AD        = wp->anim_AC;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->scale.words[0]          = 0x2000200;
            wp->scale.words[1]          = 0x200;
            wp->scale.v.pad             = 0x4210;
            wp->value_78                = 0;
            wp->value_44.words.fraction = 0;
            wp->value_48.words.fraction = 0xC0;
            func_800322A8(wp, 1, 0x2E);
            wp->routine_0++;
            break;
        case 1:
            func_80032488(wp);
            break;
        case 2:
            Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, 0, (sint16)wp->value_48.words.fraction);
            func_80032488(wp);
            break;
        case 3:
            if (wp->u_C.b.byte_C < 0x40)
            {
                wp->rotation.z += 3;
                wp->u_C.b.byte_C++;
            }
            if (wp->u_C.b.byte_D < 0x3C)
            {
                wp->value_44.words.fraction -= 8;
                wp->value_48.words.fraction += 0x10;
                wp->u_C.b.byte_D++;
            }
            Obj_pos_set(wp, (sint16)wp->value_44.words.fraction, 0, (sint16)wp->value_48.words.fraction);
            // fall through
        case 4:
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            break;
    }
    func_80051B68(wp, 1, -1, 0);
}

void func_8010130C(STAGE_OBJ *wp)
{
    sint16 x;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            func_8002F9EC(wp, 0);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_78         = 0;
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_48.half[0] = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            func_800322A8(wp, 0, 0);
            wp->routine_0++;
            break;
        case 1:
            x                      = wp->position.x - 5;
            wp->position.x         = x;
            wp->position_fixed.v.x = x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            Ride_move(ST17_SCENE_OBJ(&Scene_work, 2), wp);
            // fall through
        case 2:
            func_80032488(wp);
            break;
    }
}

void func_8010147C(STAGE_OBJ *wp)
{
    D_8011AEF0[wp->routine_1](wp);
    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    func_80032538(wp);
    Model_parts_mtx_set_yxz(wp);
}

// with the move of wp.
void func_80101534(STAGE_OBJ *wp)
{
    sint32 mode;

    wp->flags_0 |= 2;
    mode = 0;
    switch (Scene_work.u_8.byte[0])
    {
        case 5:
            mode = 1;
            func_80101990(wp);
            break;
        case 7:
            mode = 2;
            func_80101990(wp);
            break;
        case 0:
            wp->rotation.z = 0x20;
            break;
        case 0xA:
            mode           = 3;
            wp->rotation.z = 0x40;
            break;
    }
    wp->position.y = -0x1F40;
    wp->position.x = 0;
    wp->position.z = 0;
    wp->routine_1  = mode + 1;
    func_8002F9EC(wp, (sint32)&wp->variant_3);
    wp->scale.words[0] = 0x02000200;
    wp->scale.words[1] = 0x200;
    wp->scale.v.pad    = 0x4210;
    func_800322A8(wp, 0, 0);
}

void func_80101630(STAGE_OBJ *wp)
{
    wp->position.y += D_800BBCF8[ST17_FRAME & 0x3F] >> 10;
    if (wp->u_C.b.byte_C != 0)
    {
        wp->rotation.z -= D_800BBCF8[Scene_work.value_10 & 0x3F] >> 10;
    }
}

void func_801016B4(STAGE_OBJ *wp)
{
    uint16 frame;

    switch (Scene_work.value_10)
    {
        case 0xA:
        case 0x28:
        case 0x46:
            wp->u_C.b.byte_C++;
            break;
        case 0x19:
        case 0x3C:
        case 0x5A:
            wp->u_C.b.byte_C = 0;
            break;
    }
    frame = ST17_FRAME;
    wp->position.y += D_800BBCF8[frame & 0x3F] >> 10;
    if (wp->u_C.b.byte_C != 0)
    {
        wp->rotation.z += D_8011AF0C[frame & 3];
    }
}

void func_801017A0(STAGE_OBJ *wp)
{
    if (Scene_work.value_10 < 0x18)
    {
        wp->rotation.z -= 4;
    }
    else if (Scene_work.value_10 < 0x38)
    {
        wp->rotation.z += 6;
        wp->position.x += 0xA;
    }
    else
    {
        wp->position.x += 0x14;
    }
}

void func_80101808(STAGE_OBJ *wp)
{
    if (Scene_work.value_10 < 0x64)
    {
        wp->position.x += 0x10;
    }
    else if (Scene_work.value_10 < 0x7C)
    {
        wp->rotation.z -= 4;
        wp->position.x += 8;
    }
    else
    {
        wp->position.z -= 0x30;
    }
}

void func_80101870(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = -0x7D0;
        wp->position.x = 0;
        wp->position.z = -0x4B0;
        wp->rotation.x = 0;
        wp->rotation.y = 0;
        wp->rotation.z = 0;
        wp->routine_2++;
    }
    wp->position.z = (uint16)wp->position.z - 0x20;
}

void func_801018BC(STAGE_OBJ *wp)
{
    if (wp->routine_2 == 0)
    {
        wp->position.y = -0x1F40;
        wp->position.x = 0;
        wp->position.z = -0x1B58;
        wp->routine_2++;
    }
    if (Scene_work.value_10 < 0x6E)
    {
        wp->position.y += D_800BBCF8[ST17_FRAME & 0x3F] >> 10;
    }
    else if (Scene_work.value_10 < 0x86)
    {
        wp->rotation.z += 3;
    }
    else if (Scene_work.value_10 < 0xA6)
    {
        wp->rotation.z -= 6;
        wp->position.x -= 0xA;
    }
    else
    {
        wp->position.x -= 0x19;
    }
}

void func_80101990(STAGE_OBJ *wp)
{
    STAGE_FX *ep;
    uint32 i;

    for (i = 0; i < 0x18; i++)
    {
        ep = func_80031618();
        if (ep != NULL)
        {
            ep->flags_0   = 1;
            ep->kind_2    = 0x1A;
            ep->variant_3 = 1;
            ep->value_C   = wp->value_1;
            ep->timer_D   = i;
        }
    }
}
