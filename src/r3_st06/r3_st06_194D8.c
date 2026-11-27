#include "common.h"
#include "st06.h"

void func_801194D8(STAGE_OBJ *wp)
{
    D_80125914[wp->routine_0](wp);
}

void func_80119514(STAGE_OBJ *wp)
{
    ST06_CRAB_START *start;
    ST06_CRAB *crab;
    sint32 i;

    switch (wp->routine_1)
    {
        case 0:
            wp->routine_1++;
            for (i = 0; i < 7; i++)
            {
                crab = (ST06_CRAB *)func_80031418();
                if (crab != NULL)
                {
                    start                       = &D_80125924[i];
                    D_8012BAAC[i]               = crab;
                    crab->be_flag               = start->flags_0;
                    crab->id                    = start->kind_1;
                    crab->value_4               = start->value_2;
                    crab->type                  = start->variant_3;
                    *(uint32 *)&crab->routine_0 = 0;
                    *(sint32 *)&crab->u_C       = start->value_4;
                    crab->u_C.b.byte_C |= 0x10;
                    crab->position.x         = start->pos_8.x;
                    crab->position.y         = start->pos_8.y;
                    crab->position.z         = start->pos_8.z;
                    crab->position_fixed.v.x = start->pos_8.x << 16;
                    crab->position_fixed.v.y = start->pos_8.y << 16;
                    crab->position_fixed.v.z = start->pos_8.z << 16;
                    crab->rotation.x         = 0;
                    crab->rotation.y         = start->pos_8.pad;
                    crab->rotation.z         = 0;
                    if (i != 5)
                    {
                        crab->ctl.owner_0 = NULL;
                    }
                    else
                    {
                        crab->ctl.owner_0 = (STAGE_OBJ *)D_8012BAAC[1];
                    }
                }
            }
            break;
        case 1:
            if (STAGE_SCENE_BYTE(0) != 0)
            {
                wp->routine_1++;
                *(uint16 *)&wp->routine_2 = 0;
            }
            break;
        case 2:
            if (STAGE_SCENE_BYTE(0) == 0)
            {
                wp->routine_1             = 0;
                *(uint16 *)&wp->routine_2 = 0;
                wp->routine_0++;
            }
            break;
    }
}

void func_801196E8(STAGE_OBJ *wp)
{
    ST06_CRAB_START *start;
    ST06_CRAB *crab;
    sint32 i;

    D_8012BAA8 = 0;
    D_8012BAA4 = 0;
    D_8012BAA0 = 0;
    for (i = 0; i < 7; i++)
    {
        crab  = D_8012BAAC[i];
        start = &D_80125994[i];
        D_8012BAA0 |= 1 << i;
        *(uint32 *)&crab->routine_0 = 0;
        *(sint32 *)&crab->u_C       = start->value_4;
        crab->position.x            = start->pos_8.x;
        crab->position.y            = start->pos_8.y;
        crab->position.z            = start->pos_8.z;
        crab->position_fixed.v.x    = start->pos_8.x << 16;
        crab->position_fixed.v.y    = start->pos_8.y << 16;
        crab->position_fixed.v.z    = start->pos_8.z << 16;
        crab->rotation.x            = 0;
        crab->rotation.y            = start->pos_8.pad;
        crab->rotation.z            = 0;
        crab->ctl.owner_0           = NULL;
    }
    wp->routine_0++;
}

void func_801197D0(STAGE_OBJ *wp)
{
    ST06_CRAB_CTL *ctl;
    ST06_CRAB_CTL *track;
    ST06_CRAB *crab;
    ST06_CRAB *other;
    sint16 busy;
    sint16 i;
    sint16 j;
    uint8 variant;

    busy = func_80119C8C(wp);
    for (i = 0; i < 7; i++)
    {
        if ((D_8012BAA0 >> i) & 1)
        {
            crab = D_8012BAAC[i];
            ctl  = &crab->ctl;
            if (crab->id == 0x23)
            {
                track = &crab->ctl;
                if (((wp->u_E.b.work_3 >> i) & 1) && busy == 0)
                {
                    crab->ctl.flags_4 = (crab->ctl.flags_4 & ~0x80) | 0x100;
                }
                else
                {
                    ctl->flags_4 = (ctl->flags_4 | 0x80) & ~0x100;
                }
                if (crab->u_C.b.byte_C & 2)
                {
                    crab->u_C.b.byte_C &= ~2;
                    variant = 0;
                    if (track->u_3C.b.value_7 >= 2 && track->u_3C.b.value_7 < 6 && (track->random_6 & 3))
                    {
                        variant = !Sce_flag_test(0x625);
                    }
                    for (j = 3; j < 7; j++)
                    {
                        if (!((D_8012BAA0 >> j) & 1))
                        {
                            func_80119B78(crab, j, variant);
                            break;
                        }
                    }
                }
                if (crab->u_C.b.byte_C & 8)
                {
                    crab->u_C.b.byte_C &= ~8;
                    if (ctl->owner_0 != NULL)
                    {
                        ctl->owner_0->routine_1 = 1;
                        other                   = (ST06_CRAB *)crab->ctl.owner_0;
                        crab->ctl.owner_0       = NULL;
                        ctl                     = &other->ctl;
                        other->ctl.owner_0      = NULL;
                    }
                }
                if (crab->u_C.b.byte_C & 4)
                {
                    crab->u_C.b.byte_C &= ~4;
                    if (ctl->owner_0 != NULL)
                    {
                        ctl->owner_0->routine_1 = 2;
                    }
                    D_8012BAA8++;
                }
            }
            if ((crab->u_C.b.byte_C & 1) && crab->be_flag != 0)
            {
                crab->be_flag      = 0;
                other              = (ST06_CRAB *)ctl->owner_0;
                ctl->owner_0       = NULL;
                other->ctl.owner_0 = NULL;
                if (crab->id == 0x20)
                {
                    D_8012BAA4++;
                }
                if (i >= 3)
                {
                    func_80031824(D_8012BAAC[i]);
                }
                D_8012BAA0 &= ~(1 << i);
            }
        }
    }
    if (D_8012BAA4 == 3 && D_8012BAA8 < 3)
    {
        Sce_flag_on(0x627);
    }
    if (D_8012BAA0 == 0)
    {
        wp->routine_1 = 0;
        wp->routine_0++;
    }
}

void func_80119AF8(ST06_WAIT *wp)
{
    if (wp->routine_1 == 0)
    {
        Sound_work.volume_6 = 0x7F;
        Sound_fade_start(0x10);
        wp->timer_14 = 300;
        wp->routine_1++;
    }
    else if (--wp->timer_14 == 0)
    {
        Sce_flag_on(0x628);
        func_80031A4C(wp);
    }
}

void func_80119B78(ST06_CRAB *wp, sint16 slot, uint8 variant)
{
    ST06_CRAB *part;

    part = (ST06_CRAB *)func_80031418();
    if (part != NULL)
    {
        D_8012BAAC[slot] = part;
        D_8012BAA0 |= 1 << slot;
        part->be_flag            = MOVE;
        part->id                 = 0x20;
        part->u_C.b.byte_C       = 2;
        part->value_4            = 0;
        part->type               = variant;
        part->u_C.b.byte_D       = slot - 3;
        part->u_E.b.work_2       = 0;
        part->u_E.b.work_3       = 1;
        part->ctl.owner_0        = (STAGE_OBJ *)wp;
        wp->ctl.owner_0          = (STAGE_OBJ *)part;
        part->position.x         = wp->position.x;
        part->position.y         = wp->position.y;
        part->position.z         = wp->position.z;
        part->position_fixed.v.x = wp->position_fixed.v.x;
        part->position_fixed.v.y = wp->position_fixed.v.y;
        part->position_fixed.v.z = wp->position_fixed.v.z;
        part->rotation.y         = wp->rotation.y;
        part->rotation.z         = 0;
        part->rotation.x         = 0;
    }
}

sint32 func_80119C8C(STAGE_OBJ *wp)
{
    uint32 dist[3];
    ST06_CRAB *crab;
    sint16 i;
    sint16 near;
    sint16 count;
    sint16 j;
    sint16 chase;

    chase            = 0;
    near             = 0;
    count            = 0;
    wp->u_E.b.work_3 = 0;
    for (i = 0; i < 3; i++)
    {
        if ((D_8012BAA0 >> i) & 1)
        {
            crab = D_8012BAAC[i];
            if (crab->ctl.flags_4 & 0x400)
            {
                count++;
                near++;
                wp->u_E.b.work_3 |= 1 << i;
                dist[i] = 0;
            }
            else
            {
                chase   = 1;
                dist[i] = crab->dist_80;
            }
        }
        else
        {
            dist[i] = 0;
        }
    }
    if (near < 2)
    {
        for (i = 3; i < 7; i++)
        {
            if ((D_8012BAA0 >> i) & 1)
            {
                crab = D_8012BAAC[i];
                if (!(crab->routine_0 == 4 && crab->routine_1 == 0))
                {
                    count++;
                }
            }
        }
        if (count < 4)
        {
            if (count == 3)
            {
                j = dist[0] <= dist[1];
                if (dist[j] < dist[2])
                {
                    j = 2;
                }
                wp->u_E.b.work_3 |= 1 << j;
            }
            else
            {
                j = dist[0] >= dist[1];
                if (dist[j] > dist[2])
                {
                    j = 2;
                }
                wp->u_E.b.work_3 = (1 << j) ^ 7;
            }
        }
    }
    if (chase)
    {
        func_8005D4D4();
    }
    else
    {
        func_8005D4E8();
    }
    return D_8012BAA4 >= 0x12;
}
