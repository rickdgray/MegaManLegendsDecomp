#include "common.h"
#include "code_80048620.h"
#include "stage.h"
#include "player.h"
#include "scene.h"
#include "game.h"
#include "debug.h"
#include "code_8004324C.h"

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80048620);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80048704);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80048A40);

// Feeds the player's pad bits to D_800C0F96 until timer_10 passes 0x24 frames (steps 0-1) or the
// stage's D_8008AA04 count (steps 2-3), then advances routine_5.
void func_80048A9C(SCENE_WORK *sw)
{
    PL_WORK *pl;

    pl            = &Player_work[0];
    D_800C0F96[0] = 0;
    switch (sw->step_0A)
    {
        case 0:
            sw->time_0B = D_8008AA04[Game_work.stage_no];
            Player_work[0].flags_BD |= 0x20;
            sw->step_0A++;
            // fall through
        case 1:
            D_800C0F96[0] = pl->keys_124[0];
            if (sw->timer_10 >= 0x25)
            {
                sw->routine_5++;
                sw->step_0A++;
                D_800C0F96[0] = 0;
                pl->flags_BD  = (pl->flags_BD & ~0x20) | 0x40;
            }
            break;
        case 2:
            Player_work[0].flags_BD |= 0x20;
            sw->step_0A++;
            // fall through
        case 3:
            D_800C0F96[0] = pl->keys_124[0];
            if (sw->time_0B < sw->timer_10)
            {
                sw->routine_5++;
                sw->step_0A++;
                D_800C0F96[0] = 0;
                pl->flags_BD  = (pl->flags_BD & ~0x20) | 0x40;
            }
            break;
    }
}

void func_80048BE4(void)
{
}

// The map cell index of pos (x + z * Map_w), or 0 outside the map window.
sint32 map_cell_index(SVECTOR *pos)
{
    sint32 x;
    sint32 z;

    if ((uint32)(x = ((pos->vx + 0x8000) >> 9) - Map_org_x) >= Map_w || (uint32)(z = ((pos->vz + 0x8000) >> 9) - Map_org_y) >= Map_h)
    {
        return 0;
    }
    return x + z * Map_w;
}

sint32 Map_cell_get(SVECTOR *pos)
{
    sint32 x;
    sint32 z;

    if ((uint32)(x = ((pos->vx + 0x8000) >> 9) - Map_org_x) >= Map_w || (uint32)(z = ((pos->vz + 0x8000) >> 9) - Map_org_y) >= Map_h)
    {
        return 0;
    }
    // Row offset added last: Map_cells[x + z * Map_w] adds the products in the other order.
    return (Map_cells + x)[z * Map_w];
}

sint32 func_80048CEC(sint32 index)
{
    return Map_cells[index];
}

// Map_cell_get on room map's map (Stage_map_tbl) instead of the current map window.
sint32 Stage_map_cell_get(sint32 map, SVECTOR *pos)
{
    sint32 x;
    sint32 z;
    STAGE_MAP *m;

    m = &Stage_map_tbl[map];
    if ((uint32)(x = ((pos->vx + 0x8000) >> 9) - m->x0) >= m->w || (uint32)(z = ((pos->vz + 0x8000) >> 9) - m->z0) >= m->h)
    {
        return 0;
    }
    return (m->cells + x)[z * m->w];
}

sint32 Map_area_check(SVECTOR *pos)
{
    if ((uint32)(((pos->vx + 0x8000) >> 9) - Map_org_x) >= Map_w || (uint32)(((pos->vz + 0x8000) >> 9) - Map_org_y) >= Map_h)
    {
        return -1;
    }
    return 0;
}

// The low 12 bits of pos.pad of the map block under pos, or 0 outside the map or on cell 0.
sint32 func_80048E18(SVECTOR *pos)
{
    sint32 cell;

    cell = Map_cell_get(pos);
    if (cell > 0)
    {
        return Map_blocks[cell].pos.pad & 0xFFF;
    }
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80048E6C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80048EA4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004920C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80049448);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80049470);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004976C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_800497CC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80049C24);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80049C54);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004A060);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004AC8C);

// Reflects the angle off the walls in hit (0x100/0x200: one x side, 0x400/0x800: one z side);
// returns 1 if it hit any.
sint32 func_8004AE88(sint16 *angle, uint32 hit)
{
    sint32 ang;
    sint32 bounced;

    ang     = *angle & 0xFFF;
    bounced = 0;
    if (hit & 0x300)
    {
        bounced = 1;
        if (hit & 0x100)
        {
            // 0x401 <= ang <= 0xBFF
            if ((uint32)(ang - 0x401) < 0x7FF)
            {
                ang = 0x1000 - ang;
            }
        }
        else
        {
            // ang < 0x400 or ang > 0xC00
            if ((uint32)(ang - 0x400) >= 0x801)
            {
                ang = 0x1000 - ang;
            }
        }
    }
    if (hit & 0xC00)
    {
        bounced = 1;
        if (hit & 0x400)
        {
            if (ang >= 0x801)
            {
                ang = 0x1800 - ang;
            }
        }
        else
        {
            if (ang < 0x800)
            {
                ang = 0x800 - ang;
            }
        }
    }
    *angle = ang;
    return bounced;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004AF28);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004B1E0);

void func_8004B3C0(VECTOR *ofs)
{
    if (ofs != NULL)
    {
        D_1F800124.vx = ofs->vx;
        D_1F800124.vy = ofs->vy;
        D_1F800124.vz = ofs->vz;
    }
    else
    {
        D_1F800124.vx = 0;
        D_1F800124.vy = 0;
        D_1F800124.vz = 0;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004B414);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004B5CC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004B6AC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004BDC8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004E304);

// Same code as func_80054BAC.
sint32 func_8004E488(void)
{
    return 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004E490);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004E750);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004EA10);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004ECD0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004EF90);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004F150);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004F44C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004F8BC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004FBE8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8004FF14);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_800501E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80050400);

// func_80050A24 with a speed check: 0 also when |D_1F8000D0.vx| < |v->vx|.
sint32 func_80050808(SVECTOR *v)
{
    sint32 blocked;
    sint32 limit;
    sint32 speed;
    sint32 result;

    blocked = 0;
    limit   = D_1F8000D0.vx;
    if (limit == 0)
    {
        blocked = 1;
    }
    else
    {
        speed = v->vx;
        if (limit < 0)
        {
            limit = -limit;
        }
        if (speed >= 0 ? limit < speed : limit < -speed)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (v->vx > 0)
        {
            if ((D_1F8000FF & 2) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 1) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

// func_80050A90 with a speed check: 0 also when |D_1F8000D0.vz| < |v->vz|.
sint32 func_800508BC(SVECTOR *v)
{
    sint32 blocked;
    sint32 limit;
    sint32 speed;
    sint32 result;

    blocked = 0;
    limit   = D_1F8000D0.vz;
    if (limit == 0)
    {
        blocked = 1;
    }
    else
    {
        speed = v->vz;
        if (limit < 0)
        {
            limit = -limit;
        }
        if (speed >= 0 ? limit < speed : limit < -speed)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (v->vz > 0)
        {
            if ((D_1F8000FF & 8) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 4) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

// func_80050AFC with a speed check: 0 also when |D_1F8000D0.vy| < |v->vy|.
sint32 func_80050970(SVECTOR *v)
{
    sint32 blocked;
    sint32 limit;
    sint32 speed;
    sint32 result;

    blocked = 0;
    limit   = D_1F8000D0.vy;
    if (limit == 0)
    {
        blocked = 1;
    }
    else
    {
        speed = v->vy;
        if (limit < 0)
        {
            limit = -limit;
        }
        if (speed >= 0 ? limit < speed : limit < -speed)
        {
            blocked = 1;
        }
    }
    result = blocked ^ 1;
    if (result)
    {
        if (v->vy > 0)
        {
            if ((D_1F8000FF & 0x20) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 0x10) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050A24(SVECTOR *v)
{
    sint32 result;

    // result is 0 or 1, but the target has the `result &= 1` (andi) in all three of these.
    result = D_1F8000D0.vx != 0;
    if (result)
    {
        if (v->vx > 0)
        {
            if ((D_1F8000FF & 2) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 1) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050A90(SVECTOR *v)
{
    sint32 result;

    result = D_1F8000D0.vz != 0;
    if (result)
    {
        if (v->vz > 0)
        {
            if ((D_1F8000FF & 8) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 4) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050AFC(SVECTOR *v)
{
    sint32 result;

    result = D_1F8000D0.vy != 0;
    if (result)
    {
        if (v->vy > 0)
        {
            if ((D_1F8000FF & 0x20) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            if ((D_1F8000FF & 0x10) == 0)
            {
                result &= 1;
            }
            else
            {
                result = 0;
            }
        }
    }
    return result;
}

sint32 func_80050B68(SVECTOR *v)
{
    return v->vy != 0;
}

void func_80050B74(SVECTOR *v)
{
    if (D_1F8000FF & 3)
    {
        D_1F800106[0] = 0;
    }
    if (v->vx > 0)
    {
        D_1F8000FF = 1;
    }
    else
    {
        D_1F8000FF = 2;
    }
}

void func_80050BB4(SVECTOR *v)
{
    if (D_1F8000FF & 0xC)
    {
        D_1F800106[2] = 0;
    }
    if (v->vz > 0)
    {
        D_1F8000FF = 4;
    }
    else
    {
        D_1F8000FF = 8;
    }
}

sint32 func_80050BF4(SVECTOR *v)
{
    if (v->vy > 0)
    {
        D_1F8000FF = 0x10;
        return 0;
    }
    D_1F8000FF = 0x20;
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80050C2C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_800514FC);

sint32 func_80051970(PL_WORK *pl)
{
    uint32 state;
    uint32 keys;

    if (pl != NULL)
    {
        state = pl->routine_9;
        keys  = pl->unk11E;
        if (pl->unk184 == 0)
        {
            if (state >= 2 && state != 4)
            {
                return 0;
            }
            if ((keys & pl->keys_124[9]) == 0)
            {
                return 0;
            }
            if (func_8004324C(pl) == 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

sint32 func_800519E4(MAP_EXIT *exit)
{
    if (Sce_flag_test(0x7E0) == 0)
    {
        if (Sce_flag_test(0x7E0 | (exit->id & 0x1F)) == 0)
        {
            return 0;
        }
    }
    if (Sce_flag_test(0x7C0) != 0)
    {
        return 1;
    }
    if (Sce_flag_test(0x7C0 | (exit->id & 0x1F)) != 0)
    {
        return 1;
    }
    func_80063BC8(NULL, 0, 0, exit->val_4);
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80051A78);

void func_80051B40(void)
{
    D_80098894 = D_800BC058;
    D_80098898 = D_800BC360;
}

void func_80051B68(MODEL_WORK *obj, sint32 arg1, sint32 arg2, sint32 arg3)
{
    if (obj->routine_0 & 3)
    {
        D_80098894->obj   = obj;
        D_80098894->arg_4 = arg1;
        D_80098894->arg_6 = arg2;
        D_80098894->arg_8 = arg3;
        D_80098894++;
    }
}

void func_80051BAC(MODEL_WORK *obj)
{
    MODEL_WORK **list;

    if (obj->routine_0 & 3)
    {
        list       = D_80098898;
        *list      = obj;
        D_80098898 = list + 1;
    }
    obj->field_7C = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80051BE4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80051F08);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80052528);

void func_80052644(sint32 key, MODEL_WORK *obj)
{
    if (obj->field_76 != 0 && key == obj->field_C0)
    {
        obj->field_76 = 0;
        obj->field_C0 = 0;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80052674);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80052970);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80052B04);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_80053158);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_8005331C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_80048620", func_800534E0);

// obj's 16.16 position and previous position, or (part >= 0) those of its part part, moved by
// the same step.
void func_800536B0(MODEL_WORK *obj, VECTOR *pos, VECTOR *old, sint32 part)
{
    if (part < 0)
    {
        *pos = obj->pos_l;
        *old = obj->old_l;
    }
    else
    {
        pos->vx = obj->part_180[part].vx << 16;
        pos->vy = obj->part_180[part].vy << 16;
        pos->vz = obj->part_180[part].vz << 16;
        old->vx = obj->old_l.vx + (pos->vx - obj->pos_l.vx);
        old->vy = obj->old_l.vy + (pos->vy - obj->pos_l.vy);
        old->vz = obj->old_l.vz + (pos->vz - obj->pos_l.vz);
    }
}
