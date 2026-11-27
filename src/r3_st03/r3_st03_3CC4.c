#include "common.h"
#include "st03.h"

void func_80103CC4(sint8 index)
{
    STAGE_SPAWNED *obj;

    if (stcom36_D_0000 & (0x80000000 >> index))
    {
        obj = stcom36_E2_0000[index];
        switch (func_8002FE74(obj->index_1))
        {
            case 0x20:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_3C0[obj->kind_2][obj->handler_4](obj);
                break;
            case 0x60:
                obj->routine_0 = 2;
                STAGE_SPAWNED_TABLE_10C[obj->kind_2](obj);
                break;
        }
        stcom36_D_0000 &= ~(0x80000000 >> index);
    }
}

void func_80103DC4(STAGE_ROOM_WORK *wp)
{
    STAGE_OBJ *obj;

    if (func_80042238(&Player_work))
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            obj->flags_0            = 1;
            obj->kind_2             = 0x24;
            obj->value_4            = 4;
            obj->position.x         = 0x1884;
            obj->position.y         = -1;
            obj->position.z         = 0x5CDF;
            obj->variant_3          = 0;
            obj->rotation.y         = 0;
            obj->u_E.b.byte_E       = 0;
            obj->position_fixed.v.x = obj->position.x << 16;
            obj->position_fixed.v.y = obj->position.y << 16;
            obj->position_fixed.v.z = obj->position.z << 16;
            wp->child_24            = (STAGE_WORK *)obj;
        }
        D_800C0F9A          = 0;
        D_800C0F96[0]       = 0;
        D_8011CA88          = 0;
        STAGE_PL_BYTE(0xBD) = (STAGE_PL_BYTE(0xBD) | 0x20) & ~0x40;
        wp->routine_5       = 0;
        wp->routine_6       = 0;
        wp->routine_7       = 0;
        wp->routine_4++;
    }
}

void func_80103EBC(ST03_ROOM_WORK *wp)
{
    ST03_CAM *cam;
    ST03_PL *pl;

    cam = &Sce_camera_work;
    pl  = ST03_PL_PTR;
    switch (wp->routine_5)
    {
        case 0:
            MojiTaskExec2(0, 0x6D);
            wp->routine_5++;
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                wp->child_24->velocity.v.x = 0x320;
                wp->child_24->value_D      = 1;
                wp->child_24->value_E      = 2;
                if (pl->rotation.y < 0x800)
                {
                    D_800C0F96[0] = pl->pad_12A;
                }
                else
                {
                    D_800C0F96[0] = pl->pad_128;
                }
                wp->routine_5++;
            }
            break;
        case 2:
            if (wp->child_24->position.z < 0x4588)
            {
                wp->child_24->velocity.v.x = 0;
            }
            if (D_800C0F96[0] & pl->pad_128)
            {
                if (pl->rotation.y < 0x801)
                {
                    D_800C0F96[0] = 0;
                }
            }
            else if (pl->rotation.y >= 0x800)
            {
                D_800C0F96[0] = 0;
            }
            if (D_800C0F96[0] == 0 && wp->child_24->velocity.v.x == 0)
            {
                wp->child_24->value_D = 1;
                wp->child_24->value_E = 0;
                wp->routine_5++;
            }
            break;
        case 3:
            pl->routine_8 = 3;
            pl->pos_438.x = 0x1884;
            pl->pos_438.y = -1;
            pl->pos_438.z = 0x407E;
            pl->rot_440.y = 0x800;
            pl->anim_448  = 0x30;
            pl->routine_9 = 1;
            pl->rot_440.x = 0;
            pl->rot_440.z = 0;
            pl->flags_BD |= 0x10;
            pl->fixed_428.x                = pl->pos_438.x << 16;
            pl->fixed_428.y                = pl->pos_438.y << 16;
            pl->fixed_428.z                = pl->pos_438.z << 16;
            wp->child_24->value_D          = 1;
            wp->child_24->value_E          = 8;
            wp->child_24->position.z       = 0x413C;
            wp->child_24->position_fixed.z = 0x413C0000;
            func_8001E6C0(0, 0, 0);
            cam->pos_10 = 0x19A10000;
            cam->pos_14 = 0xFF740000;
            cam->pos_18 = 0x41B20000;
            cam->rot_40 = 0xA8E0000;
            cam->rot_44 = 0x400000;
            cam->rot_48 = 0;
            MojiTaskExec2(0, 0x68);
            wp->routine_5++;
            // fall through
        case 4:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() && wp->routine_4 == 1)
    {
        func_80053AA4(0);
        D_8011CA88    = 1;
        wp->routine_5 = 0;
        wp->routine_4++;
    }
}

void func_801041C8(ST03_ROOM_WORK *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            if (D_8011CA88 != 0)
            {
                ST03_PL_PTR->pos_438.x   = 0x1884;
                ST03_PL_PTR->pos_438.y   = -1;
                ST03_PL_PTR->pos_438.z   = 0x407E;
                ST03_PL_PTR->fixed_428.x = 0x18840000;
                ST03_PL_PTR->fixed_428.y = 0xFFFF0000;
                ST03_PL_PTR->fixed_428.z = 0x407E0000;
                ST03_PL_PTR->rot_440.x   = 0;
                ST03_PL_PTR->rot_440.y   = 0x800;
                ST03_PL_PTR->rot_440.z   = 0;
                ST03_PL_PTR->flags_BD |= 0x10;
                wp->child_24->position.z       = 0x413C;
                wp->child_24->position_fixed.z = 0x413C0000;
            }
            wp->child_24->timer_C   = 0x69;
            wp->child_24->value_D   = 0;
            wp->child_24->routine_0 = 0;
            wp->child_24->value_4   = 0;
            D_800C0F9A              = 0;
            D_800C0F96[0]           = 0;
            wp->routine_5++;
            break;
        case 1:
            func_80042314(&Player_work);
            D_800A395C = 1;
            func_80039820();
            wp->flags_0 = 0;
            break;
    }
}

void func_80104328(STAGE_ROOM *wp)
{
    D_801166A8[wp->routine_4](wp);
}

void func_80104364(ST03_ROOM_WORK *wp)
{
    ST03_ACTOR *obj;
    sint32 i;

    if (func_80042238(&Player_work))
    {
        obj = D_8009F108;
        for (i = 0; i < 0x10; i++, obj++)
        {
            if (obj->flags_0 != 0 && obj->kind_2 == 9 && obj->value_4 == 2)
            {
                break;
            }
        }
        wp->child_24 = obj;
        ST03_PL_PTR->flags_BD |= 0x10;
        ST03_PL_PTR->rot_440.x   = 0;
        ST03_PL_PTR->rot_440.z   = 0;
        D_8011CA90               = 0;
        ST03_PL_PTR->pos_438.x   = ST03_PL_PTR->position.x;
        ST03_PL_PTR->pos_438.y   = ST03_PL_PTR->position.y;
        ST03_PL_PTR->pos_438.z   = ST03_PL_PTR->position.z;
        ST03_PL_PTR->fixed_428.x = ST03_PL_PTR->pos_438.x << 16;
        ST03_PL_PTR->fixed_428.y = ST03_PL_PTR->pos_438.y << 16;
        ST03_PL_PTR->fixed_428.z = ST03_PL_PTR->pos_438.z << 16;
        ST03_PL_PTR->rot_440.y   = Player_work.rotation.y;
        wp->routine_5            = 0;
        wp->routine_6            = 0;
        wp->routine_7            = 0;
        wp->routine_4++;
    }
}

void func_801044A4(ST03_ROOM_WORK *wp)
{
    ST03_PL *pl;

    pl = ST03_PL_PTR;
    switch (wp->routine_5)
    {
        case 0:
            MojiTaskExec2(0, 0x70);
            wp->child_24->value_D = 1;
            wp->child_24->value_E = 8;
            pl->pos_438.x         = -0xB12;
            pl->pos_438.y         = -1;
            pl->pos_438.z         = -0x5289;
            pl->fixed_428.x       = 0xF4EE0000;
            pl->fixed_428.y       = 0xFFFF0000;
            pl->fixed_428.z       = 0xAD770000;
            pl->rot_440.x         = 0;
            pl->flags_BD |= 0x10;
            pl->rot_440.y = Angle_xz_svector(&pl->pos_438, &wp->child_24->position);
            pl->rot_440.z = 0;
            func_8001E6C0(0, 0, 0);
            Sce_camera_work.pos_10 = 0xF6400000;
            Sce_camera_work.pos_14 = 0xFF7C0000;
            Sce_camera_work.pos_18 = 0xAEB90000;
            Sce_camera_work.rot_40 = 0x8000000;
            Sce_camera_work.rot_44 = 0;
            Sce_camera_work.rot_48 = 0;
            pl->flags_0 &= ~2;
            wp->routine_5++;
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                pl->flags_0 |= 2;
                wp->child_24->value_D = 1;
                // One-pass block preserves retail's register allocation and scheduling.
                do
                {
                    wp->child_24->value_E = 2;
                } while (0);
                wp->child_24->velocity.v.x = 0x320;
                D_800A395C                 = 1;
                func_80039820();
                wp->routine_5++;
            }
            break;
        case 2:
            if (wp->child_24->rotation.y == 0x800)
            {
                pl->flags_BD |= 0x10;
                pl->rot_440.y = Angle_xz_svector(&pl->position, &wp->child_24->position);
                if (wp->child_24->position.z >= -0x3B23)
                {
                    wp->child_24->rotation.y = 0xC00;
                }
            }
            else if (wp->child_24->position.x >= 0x12D)
            {
                func_80031824(wp->child_24);
            }
            if (wp->child_24->flags_0 == 0)
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() && wp->routine_4 == 1)
    {
        D_8011CA90 = 1;
        func_80053AA4(0);
        wp->routine_5 = 0;
        wp->routine_4++;
    }
}

void func_80104778(STAGE_ROOM_WORK *wp)
{
    ST03_PL *pl;

    pl = (ST03_PL *)&Player_work;
    switch (wp->routine_5)
    {
        case 0:
            if (D_8011CA90 != 0)
            {
                pl->pos_438.x   = -0xB12;
                pl->pos_438.y   = -1;
                pl->pos_438.z   = -0x5289;
                pl->fixed_428.x = 0xF4EE0000;
                pl->fixed_428.y = 0xFFFF0000;
                pl->fixed_428.z = 0xAD770000;
                pl->rot_440.x   = 0;
                pl->rot_440.y   = 0x800;
                pl->rot_440.z   = 0;
                pl->flags_0 |= 2;
                STAGE_PL_BYTE(0xBD) |= 0x10;
                func_80031824(wp->child_24);
                D_800A395C = 1;
                func_80039820();
            }
            wp->routine_5++;
            break;
        case 1:
            func_80042314(pl);
            func_8001D974();
            wp->flags_0 = 0;
            break;
    }
}

void func_8010489C(STAGE_ROOM *wp)
{
    D_801166B4[wp->routine_4](wp);
}

void func_801048D8(void)
{
}
