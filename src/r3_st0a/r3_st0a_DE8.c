#include "common.h"
#include "st0a.h"

void func_80100DE8(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position.x         = -0x13B8;
        child->position.z         = 0x19B8;
        child->rotation.y         = 0x500;
        child->position_fixed.v.x = child->position.x << 0x10;
        child->position_fixed.v.z = child->position.z << 0x10;
    }
}

void func_80100E34(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position.x         = -0x1400;
        child->position.z         = 0x1A00;
        child->rotation.y         = 0x500;
        child->position_fixed.v.x = child->position.x << 0x10;
        child->position_fixed.v.z = child->position.z << 0x10;
    }
}

void func_80100E80(STAGE_ROOM *wp)
{
    STAGE_OBJ *child;

    if (wp->frame_10 == 0)
    {
        child                     = wp->child_28;
        child->position.x         = -0x1400;
        child->position.y         = -0x2E4;
        child->position.z         = 0x1A00;
        child->rotation.y         = 0x900;
        child->position_fixed.v.x = child->position.x << 16;
        child->position_fixed.v.y = child->position.y << 16;
        child->position_fixed.v.z = child->position.z << 16;
    }
}

void func_80100EE0(void)
{
}

void func_80100EE8(void)
{
}

void func_80100EF0(STAGE_ROOM *wp)
{
    D_800C0F96[0] = 0;
    switch (wp->routine_6)
    {
        case 0:
            if (STAGE_PL.position.z < 0x1A00)
            {
                STAGE_PL.pos_438.x   = -0xD00;
                STAGE_PL.pos_438.y   = -1;
                STAGE_PL.pos_438.z   = 0x1A00;
                STAGE_PL.fixed_428.x = -0xD00 << 16;
                STAGE_PL.fixed_428.y = -1 << 16;
                STAGE_PL.fixed_428.z = 0x1A00 << 16;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0;
                STAGE_PL.value_444   = 0;
                STAGE_PL.flags_bd |= 0x10;
                wp->routine_6++;
            }
            else
            {
                D_800C0F96[0] = ((STAGE_PL_PAD *)&Player_work)->pad_124;
            }
            break;
        case 1:
            if ((STAGE_PL.rotation.y & 0xFFF) > 0x400)
            {
                STAGE_PL.pos_438.x   = -0xD00;
                STAGE_PL.pos_438.y   = -1;
                STAGE_PL.pos_438.z   = 0x1A00;
                STAGE_PL.fixed_428.x = -0xD00 << 16;
                STAGE_PL.fixed_428.y = -1 << 16;
                STAGE_PL.fixed_428.z = 0x1A00 << 16;
                STAGE_PL.value_440   = 0;
                STAGE_PL.value_442   = 0x400;
                STAGE_PL.value_444   = 0;
                STAGE_PL.flags_bd |= 0x10;
                wp->routine_6++;
            }
            else
            {
                D_800C0F96[0] = ((STAGE_PL_PAD *)&Player_work)->pad_12A;
            }
            break;
        case 2:
            STAGE_PL.routine_1++;
            wp->routine_6++;
            break;
        case 3:
            if (STAGE_PL.routine_1 == 0)
            {
                STAGE_PL.flags_bd = (STAGE_PL.flags_bd & ~0x20) | 0x40;
                wp->routine_6++;
            }
            break;
    }
    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_28);
        func_80031824(wp->child_2C);
        func_80031824(wp->child_30);
        wp->reserved09[2] = 1;
    }
    if (wp->frame_10 == 0 || wp->frame_10 == 0x32)
    {
        wp->child_24->routine_0++;
    }
}

void func_80101178(STAGE_ROOM *wp)
{
    D_801154C0[wp->routine_4](wp);
}

void func_801011B4(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x5E, 0x80);
            func_8001E6C0(0, 0, 0);
            D_800BC7F0          = D_80115558;
            wp->tbl_A4          = D_801155A4;
            wp->timer_C         = 0;
            Sound_work.volume_6 = 0x7F;
            D_8011B5FC          = -0x259;
            D_8011B600          = 8;
            wp->reserved09[1]   = 0x80;
            wp->reserved09[2]   = 0;
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl) != 0)
            {
                // statement order found by search
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->flags_0 &= ~2;
                pl->flags_bd |= 0x10;
                pl->value_440   = 0;
                pl->pos_438.x   = -0x1280;
                pl->pos_438.y   = -1;
                pl->value_444   = 0;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->pos_438.z   = 0x1E80;
                pl->value_442   = 0x400;
                pl->fixed_428.y = pl->pos_438.y << 16;
                pl->value_448   = 0x30;
                pl->fixed_428.z = pl->pos_438.z << 16;
                wp->routine_5++;
            }
            break;
        case 2:
            if (wp->reserved09[2] < 0x2D)
            {
                wp->reserved09[2]++;
            }
            else
            {
                wp->reserved09[2] = 0;
                Scene_obj_ent_open(D_801154CC);
                Fade_start(7);
                Cd_xa_play_id(0x20000009);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    Sce_camera_update();
    Sce_event_update();
}

void func_80101394(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            Sce_camera_update();
            if (func_8001D878() != 0)
            {
                func_8005D7C0();
                Sce_event_timer_clear();
                D_800BC7F0 = D_801155B4;
                wp->tbl_A4 = D_801158BC;
                wp->routine_5++;
            }
            break;
        case 1:
            if (wp->routine_8 != 0xFF)
            {
                wp->tbl_A4[1](wp);
                if (func_8001DE84() != 0 && !(wp->reserved09[1] & 0x80))
                {
                    wp->reserved09[1] |= 1;
                    wp->routine_5 = 0;
                    wp->routine_4++;
                }
            }
            else
            {
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            Sce_camera_update();
            break;
    }
    Sce_event_update();
}

void func_801014B0(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            Obj_work_flag_change(0x156, 0x80);
            func_8003697C();
            Cd_subcmd(0, 1, 0);
            if (Moji_flag & 0x8000000)
            {
                func_80053AA4(0);
                Game_logo_kill(-1);
            }
            wp->routine_5++;
            break;
        case 1:
            func_80042314(&Player_work);
            D_800A395C = 1;
            if (wp->reserved09[1] & 1)
            {
                func_80039820();
            }
            else
            {
                func_8003A264();
            }
            wp->routine_5++;
            break;
        case 2:
            if (Sound_fade_flags == 0)
            {
                wp->flags_0 = 0;
            }
            break;
    }
}

void func_801015D4(STAGE_OBJ *wp)
{
    if (wp->value_10 == 0)
    {
        wp->flags_6 = 0;
    }
    if ((wp->flags_6 == 0) && (D_80098A72 == 0))
    {
        wp->routine_2 &= 0x7F;
        wp->flags_6++;
    }
}

void func_8010162C(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *tbl;
    STAGE_OBJ *child;
    sint32 y;
    sint32 low;

    if (wp->frame_10 == 0)
    {
        tbl = D_8011551C;
        Scene_obj_ent_open(&tbl[0]);
        Scene_obj_ent_open(&tbl[-3]);
        Scene_obj_ent_open(&tbl[-2]);
        wp->routine_6 = 0;
    }
    switch (wp->routine_6)
    {
        case 0:
            if (wp->frame_10 == 0x14)
            {
                D_8011B604 = 0;
                wp->routine_6++;
            }
            break;
        case 1:
            if (func_80101BB4(0) != 0)
            {
                wp->routine_6++;
            }
            break;
        case 2:
            func_80101BB4(1);
            if (func_80101A78(0) != 0)
            {
                wp->routine_6++;
            }
            low                       = (uint16)D_8011B5FC - 0x54;
            child                     = wp->child_28;
            child->position.y         = low;
            child->position_fixed.v.y = low << 16;
            child                     = wp->child_2C;
            child->position.y         = low;
            child->position_fixed.v.y = low << 16;
            break;
        case 3:
            func_80101BB4(1);
            if (wp->frame_10 == 0xB4)
            {
                wp->routine_6++;
            }
            break;
        case 4:
            func_80101BB4(1);
            if (wp->frame_10 == 0x208)
            {
                wp->routine_6++;
            }
            break;
        case 5:
            func_80101BB4(1);
            if (func_80101A78(1) != 0)
            {
                wp->routine_6++;
            }
            y                         = (uint16)D_8011B5FC;
            child                     = wp->child_24;
            child->position.y         = y;
            child->position_fixed.v.y = y << 16;
            y -= 0x34;
            child                     = wp->child_28;
            child->position.y         = y;
            child->position_fixed.v.y = y << 16;
            child                     = wp->child_2C;
            child->position.y         = y;
            child->position_fixed.v.y = y << 16;
            break;
        default:
            func_80101BB4(1);
            break;
    }
    ((STAGE_OBJ50 *)wp->child_34)->pos_38.y = D_8011B5FC;
}

void func_801017F0(STAGE_ROOM *wp)
{
    STAGE_SCRIPT_ENTRY *tbl;

    if (wp->frame_10 == 0)
    {
        func_8003187C(wp->child_24);
        func_80031824(wp->child_28);
        func_80031824(wp->child_2C);
        func_80031A4C(wp->child_34);
        tbl = D_80115508;
        Scene_obj_ent_open(&tbl[0]);
        Scene_obj_ent_open(&tbl[2]);
        Scene_obj_ent_open(&tbl[3]);
        wp->routine_6 = 0;
    }
    ((STAGE_OBJ50 *)wp->child_38)->pos_38.y -= 5;
    ((STAGE_OBJ50 *)wp->child_3C)->pos_38.y -= 5;
}

void func_801018B0(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        func_80031A4C(wp->child_38);
        func_80031A4C(wp->child_3C);
        wp->routine_6      = 0;
        STAGE_PL.value_448 = 0x80;
        STAGE_PL.value_168 = 0;
        STAGE_PL.value_169 = 6;
        STAGE_PL.flags_0 |= 2;
    }
    switch (wp->routine_6)
    {
        case 0:
            D_8011B604 = 0;
            wp->routine_6++;
            // fall through
        case 1:
            if (func_80101BB4(2) != 0)
            {
                wp->routine_6++;
            }
            break;
        case 2: // retail's compare tree has a third case
            break;
    }
}

void func_8010198C(STAGE_ROOM *wp)
{
    if (wp->frame_10 == 0)
    {
        wp->routine_6      = 0;
        STAGE_PL.value_448 = 0x30;
    }
}

void func_801019B0(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;

    pl = &STAGE_PL;
    if (wp->frame_10 == 0)
    {
        func_80031824(wp->child_30);
        wp->routine_6 = 0;
    }
    else if (wp->frame_10 == 0x1E)
    {
        MojiTaskExec2(0, 0x28);
    }
    switch (wp->routine_6)
    {
        case 0:
            if (wp->frame_10 == 0x32)
            {
                pl->value_448 = 0x81;
                pl->value_168 = 0;
                pl->value_169 = 0;
                wp->routine_6++;
            }
            break;
        case 1:
            if (pl->flags_A7 == -1)
            {
                pl->value_448 = 0;
                wp->routine_6++;
            }
            break;
    }
}

// Moves the gate: raises it (down == 0) or lowers it; returns 1 once it is fully up or down.
sint32 func_80101A78(sint32 down)
{
    sint32 done;

    done = 0;
    if (down == 0)
    {
        if (D_8011B5FC >= -1)
        {
            D_8011B600 = 0;
        }
        else if (D_8011B5FC >= -0x3C)
        {
            D_8011B600 = 2;
        }
        else if (D_8011B5FC >= -0xB4)
        {
            D_8011B600 = 4;
        }
        else if (D_8011B5FC >= -0x168)
        {
            D_8011B600 = 6;
        }
        if (D_8011B600 > 0)
        {
            D_8011B5FC += D_8011B600;
            goto finish;
        }
        D_8011B5FC = -1;
        done       = 1;
    }
    else
    {
        if (D_8011B5FC < -0x169)
        {
            D_8011B600 = 6;
        }
        else if (D_8011B5FC < -0xB5)
        {
            D_8011B600 = 6;
        }
        else if (D_8011B5FC < -0x3D)
        {
            D_8011B600 = 4;
        }
        else if (D_8011B5FC < 0)
        {
            D_8011B600 = 2;
        }
        if (D_8011B5FC >= -0x258)
        {
            D_8011B5FC -= D_8011B600;
            goto finish;
        }
        done = 1;
    }
finish:
    return done;
}

// Draws a translucent black screen; mode 0 fades it in, 2 out, 1 holds it. Returns 1 once a fade
// is done.
sint32 func_80101BB4(sint32 mode)
{
    STAGE_TILE *tile;
    DR_MODE *dm;
    sint32 done;
    uint8 shade;

    tile = (STAGE_TILE *)*STAGE_PACKET_PTR;
    setlen(tile, 3);
    tile->code = 0x60;
    tile->w    = 0x140;
    tile->y0   = 0;
    tile->x0   = 0;
    tile->h    = 0xF0;
    tile->code |= 2;
    done = 0;
    switch (mode)
    {
        case 0:
            if (D_8011B604 < 0x19)
            {
                shade = D_8011B604 * 2;
            }
            else
            {
                done  = 1;
                shade = 0x32;
            }
            tile->r0 = tile->g0 = tile->b0 = shade;
            if (D_8011B604 < 0xFF)
            {
                D_8011B604++;
            }
            break;
        case 1:
            tile->r0 = tile->g0 = tile->b0 = 0x32;
            break;
        case 2:
            if (D_8011B604 < 0x19)
            {
                tile->r0 = tile->g0 = tile->b0 = 0x32 - D_8011B604 * 2;
            }
            else
            {
                done     = 1;
                tile->r0 = tile->g0 = tile->b0 = 0;
            }
            if (D_8011B604 < 0xFF)
            {
                D_8011B604++;
            }
            break;
    }
    dm = (DR_MODE *)++*STAGE_PACKET_PTR;
    SetDrawMode(dm, 0, 0, 0x4F, NULL);
    ++*STAGE_PACKET_PTR;
    addPrim(&Disp_env_ptr->ot_74, tile);
    addPrim(&Disp_env_ptr->ot_74, dm);
    return done;
}
