#include "common.h"
#include "stage_common/stcom25.h"

// Shared stage code, linked into 3 stages: r3_st05, r3_st06 and r3_st08. Each stage compiles
// this file against its own copy of the assembly (TARGET_ASM, set by tools/cc.sh); the names
// are the same in every stage's registry.
#define ASM_DIR TARGET_ASM "/stage_common/stcom25"

// A block that rolls over and over along a course.
void stcom25_func_0000(STCOM25_WORK *wp)
{
    stcom25_D_0438[wp->routine_0](wp);
}

void stcom25_func_003C(STCOM25_WORK *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX *m;

    wp->ctl.nodes_0 = stcom25_D_03B4[wp->course_C];
    wp->ctl.start_4 = stcom25_D_03E0[wp->course_C];
    wp->ctl.order_8 = stcom25_D_040C[wp->course_C];
    wp->flags_0 |= 2;
    wp->position.x       = (wp->ctl.start_4[wp->start_D].x_0 - 0x40) << 9;
    wp->position.y       = 0;
    wp->position.z       = (wp->ctl.start_4[wp->start_D].z_1 - 0x40) << 9;
    wp->position_fixed.x = wp->position.x << 16;
    wp->position_fixed.y = wp->position.y << 16;
    wp->position_fixed.z = wp->position.z << 16;
    wp->rotation.x       = 0;
    wp->rotation.y       = (wp->ctl.start_4[wp->start_D].dir_3 & 0x30) << 6;
    wp->rotation.z       = 0;
    wp->ctl.dir_C = wp->ctl.dir_D = (wp->ctl.start_4[wp->start_D].dir_3 & 0x30) >> 4;
    wp->position_fixed_prev       = wp->position_fixed;
    wp->position_prev             = wp->position;
    wp->rotation_prev             = wp->rotation;
    wp->velocity.words[0]         = 0;
    wp->velocity.words[1]         = 0;
    wp->accel.words[0]            = 0;
    wp->accel.words[1]            = 0;
    wp->ctl.speed_10              = wp->ctl.start_4[wp->start_D].flags_2 << 4;
    wp->ctl.flags_F               = 0;
    wp->data_78                   = NULL;
    wp->position.y                = func_8004920C(&wp->position);
    stcom25_func_0D08(wp, 0x100);
    m                    = &wp->matrix;
    wp->position_fixed.y = wp->position.y << 16;
    wp->draw_pos         = wp->position;
    RotMatrix(&wp->rotation, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    wp->variant_3 = wp->ctl.start_4[wp->start_D].next[0];
    wp->color_B4  = 0x808080;
    func_8002F9C4(wp, &wp->variant_3);
    wp->ctl.value_1C = 0;
    wp->ctl.index_1A = 0;
    wp->routine_1    = 0;
    wp->routine_0++;
}

void stcom25_func_02CC(STCOM25_WORK *wp)
{
    STCOM_FIXED_VECTOR scale;
    STCOM_MATRIX *m;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed;
    wp->rotation_prev       = wp->rotation;
    wp->rotation.z          = 0;
    wp->rotation.x          = 0;
    stcom25_D_0448[wp->routine_1](wp);
    wp->position.y = func_8004920C(&wp->position);
    stcom25_func_0D08(wp, 0x100);
    m                    = &wp->matrix;
    wp->position_fixed.y = wp->position.y << 16;
    wp->draw_pos         = wp->position;
    RotMatrixYXZ(&wp->rotation, m);
    scale.x = 0x200;
    scale.y = 0x200;
    scale.z = 0x200;
    ScaleMatrix(m, &scale);
    func_80051B68(wp, 1, -1, 0x1000008);
}

void stcom25_func_040C(STCOM25_WORK *wp)
{
    func_800318D8(wp);
}

void stcom25_func_042C(void)
{
}

void stcom25_func_0434(STCOM25_WORK *wp)
{
    stcom25_func_0E3C(wp);
    wp->routine_1++;
}

void stcom25_func_046C(STCOM25_WORK *wp)
{
    stcom25_func_0A38(wp);
    if (stcom25_func_06E4(wp) == 0)
    {
        func_8002FEA4(wp, wp->velocity.v.x, 0, 0);
        return;
    }
    wp->routine_1 = 2;
    wp->ctl.phase_12 += (wp->velocity.v.x * 3) >> 5;
    stcom25_func_08AC(wp);
}

void stcom25_func_04E8(STCOM25_WORK *wp)
{
    STCOM25_CTL *ctl;
    sint8 sign;

    stcom25_func_0A38(wp);
    ctl             = &wp->ctl;
    wp->ctl.dist_14 = 0x7FFF;
    wp->ctl.phase_12 += (wp->velocity.v.x * 3) >> 5;
    if (wp->ctl.phase_12 > 0x400)
    {
        wp->ctl.phase_12 -= 0x400;
        if (wp->ctl.nodes_0[wp->ctl.node_E].flags_2 & 0x10)
        {
            sign           = -1;
            wp->rotation.y = ((wp->ctl.dir_C << 10) + 0xC00) & 0xFFF;
        }
        else
        {
            sign           = 1;
            wp->rotation.y = ((wp->ctl.dir_C << 10) + 0x400) & 0xFFF;
        }
        wp->position.x = ctl->pivot_16;
        wp->position.z = ctl->pivot_18;
        if (ctl->dir_C == 0)
        {
            wp->position.x -= sign * ctl->phase_12;
            wp->position.z -= 0x200;
        }
        else if (ctl->dir_C == 1)
        {
            wp->position.x -= 0x200;
            wp->position.z += sign * ctl->phase_12;
        }
        else if (ctl->dir_C == 2)
        {
            wp->position.x += sign * ctl->phase_12;
            wp->position.z += 0x200;
        }
        else
        {
            wp->position.x += 0x200;
            wp->position.z -= sign * ctl->phase_12;
        }
        wp->position_fixed.x = wp->position.x << 16;
        wp->position_fixed.z = wp->position.z << 16;
        stcom25_func_0E3C(wp);
        ctl->phase_12 = 0;
        ctl->flags_F &= ~1;
        wp->routine_1 = 1;
        return;
    }
    stcom25_func_08AC(wp);
}

// Nonzero once it reaches the node's cell: sets up the turn over its edge.
sint16 stcom25_func_06E4(STCOM25_WORK *wp)
{
    STCOM25_CTL *ctl;
    sint16 result;
    uint8 dir;
    sint16 z;
    sint16 x;
    sint32 px;
    sint32 pz;
    uint8 left;
    sint32 half;

    ctl = &wp->ctl;
    if ((wp->ctl.flags_F & 0xE0) == 0x40)
    {
        stcom25_func_0E3C(wp);
        wp->ctl.flags_F &= ~0x40;
        return 0;
    }
    result        = 0;
    dir           = wp->rotation.y >> 10;
    px            = wp->position.x >> 9;
    x             = px + 0x40;
    wp->ctl.dir_C = dir;
    pz            = wp->position.z >> 9;
    z             = pz + 0x40;
    if (dir == 0)
    {
        z = pz + 0x41;
    }
    else if (dir == 1)
    {
        x = px + 0x41;
    }
    if (x == ctl->nodes_0[ctl->node_E].x_0 && z == ctl->nodes_0[ctl->node_E].z_1)
    {
        left          = (ctl->nodes_0[ctl->node_E].flags_2 & 0x10) >> 4;
        ctl->phase_12 = (wp->position.x & 0x1FF) + (wp->position.z & 0x1FF);
        if (ctl->dir_C < 2)
        {
            ctl->phase_12 = 0x200 - ctl->phase_12;
        }
        ctl->pivot_16 = x - 0x40;
        ctl->pivot_18 = z - 0x40;
        if (ctl->dir_C & 1)
        {
            half = (ctl->dir_C >> 1) & 1;
            ctl->pivot_18 += ((left + half + 1) & 1) * 2 - 1;
        }
        else
        {
            half = (ctl->dir_C >> 1) & 1;
            ctl->pivot_16 += ((left + half) & 1) * 2 - 1;
        }
        ctl->pivot_16 <<= 9;
        ctl->pivot_18 <<= 9;
        if (left)
        {
            ctl->dir_D = (ctl->dir_C + 3) & 3;
        }
        else
        {
            ctl->dir_D = (ctl->dir_C + 1) & 3;
        }
        result = 1;
    }
    return result;
}

// Places it on its turn over the pivot edge.
void stcom25_func_08AC(STCOM25_WORK *wp)
{
    STCOM25_CTL *ctl;
    sint32 c;
    sint32 s;
    sint8 sign;
    sint32 t;

    sign = 1;
    ctl  = &wp->ctl;
    if (wp->ctl.nodes_0[wp->ctl.node_E].flags_2 & 0x10)
    {
        sign = -1;
    }
    c                    = rcos(wp->ctl.phase_12) << 13;
    t                    = rsin(wp->ctl.phase_12) << 13;
    wp->position_fixed.x = wp->ctl.pivot_16 << 16;
    // s holds the z value, then the sine: retail reuses one register, and every arm reloads both
    // fixed halves.
    s                    = wp->ctl.pivot_18 << 16;
    wp->position_fixed.z = s;
    s                    = t;
    if (wp->ctl.dir_C == 0)
    {
        wp->position_fixed.z -= s;
        wp->position_fixed.x += sign * c;
    }
    else if (wp->ctl.dir_C == 1)
    {
        wp->position_fixed.x -= s;
        wp->position_fixed.z -= sign * c;
    }
    else if (wp->ctl.dir_C == 2)
    {
        wp->position_fixed.z += s;
        wp->position_fixed.x -= sign * c;
    }
    else
    {
        wp->position_fixed.x += s;
        wp->position_fixed.z += sign * c;
    }
    func_80030150(&wp->position_fixed, &wp->position);
    wp->rotation.y = (ctl->dir_C << 10) + sign * ctl->phase_12;
}

// Speeds it up or slows it down toward speed_10, braking before corners.
void stcom25_func_0A38(STCOM25_WORK *wp)
{
    STCOM25_CTL *ctl;
    STCOM25_NODE *node;
    sint32 max;
    sint16 target;
    sint16 dist;
    sint32 px;
    sint32 pz;
    sint32 dx;
    sint32 dz;
    uint8 kind;
    sint32 corner;
    sint32 v;
    sint32 limit;

    max = 8;
    ctl = &wp->ctl;
    // Index first, base last: &nodes_0[node_E] adds the other way round.
    node   = (STCOM25_NODE *)(wp->ctl.node_E * sizeof(STCOM25_NODE) + (uint32)wp->ctl.nodes_0);
    target = wp->ctl.speed_10;
    px     = wp->position.x;
    pz     = wp->position.z;
    dx     = abs(((node->x_0 - 0x40) << 9) - px);
    kind   = node->flags_2;
    dz     = abs(((node->z_1 - 0x40) << 9) - pz);
    dist   = dx + dz;
    wp->ctl.dist_14 = dist + 0x1FF;
    if (wp->ctl.flags_F & 4)
    {
        max = 0x20;
    }
    if (!(wp->ctl.flags_F & 0x11))
    {
        corner = kind & 0xE0;
        if (corner != 0)
        {
            limit = wp->velocity.v.x;
            v     = (limit * ((limit >> 4) + 6)) >> 4;
            limit = v + 0x180;
            if (corner == 0x40)
            {
                limit = v + 0x380;
            }
            else if (corner == 0x60)
            {
                limit = v + 0x580;
            }
            if (limit >= dist)
            {
                ctl->flags_F |= 0x10;
                wp->accel.v.x = 0;
            }
        }
        else
        {
            limit = wp->velocity.v.x - 0x140;
            limit = ((limit * limit) >> 7) - limit + 0x400;
            if (limit >= dist)
            {
                wp->ctl.flags_F |= 1;
                if (wp->accel.v.x > 0)
                {
                    wp->accel.v.x = 0;
                }
            }
        }
    }
    if (wp->velocity.v.x < target)
    {
        if (wp->accel.v.x < 0)
        {
            wp->accel.v.x = 0;
        }
        if (wp->velocity.v.x < target - 0xD)
        {
            if (wp->accel.v.x < max)
            {
                wp->accel.v.x++;
            }
        }
        else if (wp->accel.v.x >= 3)
        {
            wp->accel.v.x -= 2;
        }
        else
        {
            wp->velocity.v.x = target;
            wp->accel.v.x    = 0;
        }
        wp->velocity.v.x += wp->accel.v.x;
        if (wp->velocity.v.x > target)
        {
            wp->velocity.v.x = target;
            wp->accel.v.x    = 0;
        }
    }
    else if (wp->velocity.v.x > target)
    {
        if (wp->accel.v.x > 0)
        {
            wp->accel.v.x = 0;
        }
        if (wp->velocity.v.x > target + 0xD)
        {
            if (wp->accel.v.x > -max)
            {
                wp->accel.v.x--;
            }
        }
        else if (wp->accel.v.x < -2)
        {
            wp->accel.v.x += 2;
        }
        else
        {
            wp->velocity.v.x = target;
            wp->accel.v.x    = 0;
        }
        wp->velocity.v.x += wp->accel.v.x;
        if (wp->velocity.v.x < target)
        {
            wp->velocity.v.x = target;
            wp->accel.v.x    = 0;
        }
    }
}

// Tilts it (rotation.x) by the ground's slope across `size`.
void stcom25_func_0D08(STCOM25_WORK *wp, sint16 size)
{
    STCOM_SVECTOR pos;
    sint16 h;
    sint16 dir;
    sint16 height;

    if (size != 0)
    {
        dir   = wp->rotation.y >> 10;
        pos.x = wp->position.x;
        pos.y = wp->position.y - 0x80;
        pos.z = wp->position.z;
        if (dir & 1)
        {
            pos.x -= size >> 1;
            h = func_8004920C(&pos);
            pos.x += size;
            height = func_8004920C(&pos);
        }
        else
        {
            pos.z -= size >> 1;
            h = func_8004920C(&pos);
            pos.z += size;
            height = func_8004920C(&pos);
        }
        wp->rotation.x += ((dir & 2) - 1) * (height - h) * 3;
        if (wp->accel.v.x > 0)
        {
            wp->rotation.x -= wp->accel.v.x >> 1;
        }
        else
        {
            wp->rotation.x -= wp->accel.v.x * 2;
        }
    }
}

// Picks the next node: in order_8's order, or at random by each branch's chance.
void stcom25_func_0E3C(STCOM25_WORK *wp)
{
    STCOM25_CTL *ctl;
    sint16 i;
    uint8 next;
    sint32 r;
    sint32 chance;

    ctl = &wp->ctl;
    if (wp->ctl.start_4[wp->start_D].next[0] == 6)
    {
        if (wp->routine_1 == 0)
        {
            wp->ctl.index_1A = wp->ctl.start_4[wp->start_D].next[1];
        }
        wp->ctl.node_E   = wp->ctl.order_8[wp->ctl.index_1A];
        wp->ctl.index_1A = (wp->ctl.index_1A + 1) % stcom25_D_0000[wp->course_C][0];
        return;
    }
    for (i = 0; i < 4; i++)
    {
        if (wp->routine_1 == 0)
        {
            next = ctl->start_4[wp->start_D].next[i + 1];
            if (i == 2)
            {
                break;
            }
        }
        else
        {
            next = ctl->nodes_0[ctl->node_E].next[i];
            if (i == 3)
            {
                break;
            }
        }
        r      = rand() >> (i * 4);
        chance = ctl->nodes_0[next].flags_2 & 0xF;
        if ((r & 0xF) < chance || chance == 0)
        {
            break;
        }
    }
    ctl->node_E = next;
}
