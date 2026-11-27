#include "common.h"
#include "code_80027678.h"
#include "code_800425FC.h"
#include "code_80043F34.h"
#include "code_8004324C.h"
#include "code_80037534.h"
#include "code_8006430C.h"
#include "code_80037FB4.h"
#include "code_80048620.h"
#include "code_8005C258.h"
#include "fastmem.h"
#include "scratch.h"
#include "game.h"
#include "pad.h"
#include "player.h"
#include "psyq/rand.h"
#include "scene.h"
#include "sound.h"

// Called only from this file
sint32 func_800406A8(PL_WORK *pl);
sint32 func_80040764(PL_WORK *pl);
void player_work_init(PL_WORK *pl, sint32 load);
void key_seq_set(PL_WORK *pl, uint8 idx, sint16 b0, uint8 force);
void func_80041F54(PL_WORK *pl, sint32 spd, sint32 max, uint16 mask);
sint32 func_80042044(PL_WORK *pl, sint32 spd, sint32 max);
sint32 func_80042154(PL_WORK *pl, sint32 spd, sint32 max, sint32 mask);
void func_80040E9C(PL_WORK *pl, sint16 arg);
void func_8003C418(PL_WORK *pl);
void func_8003C4EC(PL_WORK *pl);
void func_80042528(PL_WORK *pl, W48_83_WORK *wp, sint16 n);
void func_8003F188(PL_WORK *pl, sint32 dir, sint32 anim);
sint32 func_8003F224(PL_WORK *pl);
sint32 func_80041044(PL_WORK *pl);
sint32 func_80041158(PL_WORK *pl);
sint32 func_800414F0(PL_WORK *pl, SVECTOR *pos, SVECTOR *ang, HIT_ENT *box);
void func_80041A44(PL_WORK *pl, uint32 flags);
void func_80041EF4(PL_WORK *pl, sint32 spd, sint32 max);
sint32 func_80042094(PL_WORK *pl, sint32 spd, sint32 max, sint32 anim);
void func_8003E068(PL_WORK *pl, sint32 dir);
void func_8003D124(PL_WORK *pl, sint32 dir);
void func_8003EE68(PL_WORK *pl);
sint32 func_80040E00(PL_WORK *pl, sint32 arg, sint16 mode, sint16 cond);
sint32 func_80040B68(PL_WORK *pl, sint32 arg);
sint32 func_80040710(PL_WORK *pl);
sint32 func_80040818(PL_WORK *pl);
sint32 func_800402C4(PL_WORK *pl);
sint32 func_8004030C(PL_WORK *pl, sint32 arg);
sint32 func_80040380(PL_WORK *pl);
sint32 func_800403D4(PL_WORK *pl, sint32 arg);
sint32 func_80040468(PL_WORK *pl, sint32 arg);
sint32 func_800404FC(PL_WORK *pl, sint32 arg);
sint32 func_80040574(PL_WORK *pl);
sint32 func_800405F4(PL_WORK *pl);
sint32 func_80040630(PL_WORK *pl, sint32 arg);
sint32 func_800406DC(PL_WORK *pl);
sint32 func_80040AEC(PL_WORK *pl);
sint32 func_80040FA8(PL_WORK *pl);
sint32 func_800410D4(PL_WORK *pl);
sint32 front_box_search(PL_WORK *pl);
void damage_check(PL_WORK *pl);

void Player_init(sint32 load)
{
    player_work_init(&Player_work[0], load);
}

// Sets up a player: a new one (load 0) or one restored from the save image.
void player_work_init(PL_WORK *pl, sint32 load)
{
    SAVE_IMAGE *save;

    D_8009888C = 0x80000000;
    save       = &Save_image;
    if (Game_work.unk082 & 0x80)
    {
        pl->be_flag = 0;
        pl->flags   = 0;
    }
    else
    {
        pl->be_flag               = MOVE | TRANS;
        pl->flags                 = 3;
        *(uint16 *)&pl->id        = 0; // id, type
        *(uint16 *)&pl->flag_4    = 0; // flag_4, flag_5
        pl->field_C               = 0;
        *(uint32 *)&pl->routine_0 = 0; // routine_0 ... routine_3
    }
    pl->hit_78   = &D_80097D90;
    pl->flags_BD = 0;
    pl->field_75 = 0;
    pl->field_74 = 0;
    pl->unk77    = 0;
    pl->field_76 = 0;
    pl->obj_184  = 0;
    pl->unk110   = 0;
    pl->unk111   = 0;
    pl->unk449   = 0;
    if (pl == &Player_work[0])
    {
        Player_work[0].id = 0;
    }
    else
    {
        pl->id = 1;
    }
    func_800425FC(pl, (sint8)Game_work.unk054);
    if (load == 0)
    {
        pl->life_max                       = 0x50;
        pl->life                           = 0x50;
        pl->unk16A                         = 0;
        pl->unk16B                         = 0;
        pl->unk16C                         = 0;
        pl->weapon_right_no                = 0;
        pl->tbl_sel                        = 0;
        pl->unk171                         = 0;
        pl->unk173                         = 1;
        pl->unk44C                         = 0;
        pl->unk44E                         = 0;
        *(uint32 *)pl->rb_parts_equip_data = 0; // with unk453
        Mem_clear(&pl->rb_parts_sort_data[0], &pl->rb_parts_sort_data[4]);
        Mem_clear(&pl->unk474[0], &pl->unk474[0x3C]);
        func_80037534(pl);
    }
    else
    {
        pl->life = pl->life_max            = save->pl_life_max;
        pl->unk16A                         = save->pl_unk16A;
        pl->unk16B                         = save->pl_unk16B;
        pl->unk16C                         = save->pl_unk16C;
        pl->weapon_right_no                = save->pl_unk170;
        pl->unk171                         = save->pl_unk171;
        pl->tbl_sel                        = save->pl_tbl_sel;
        pl->unk173                         = save->pl_unk173;
        pl->unk44C                         = save->pl_unk44C;
        pl->unk44E                         = save->pl_unk44E;
        pl->unk44F                         = save->pl_unk44F;
        *(uint32 *)pl->rb_parts_equip_data = save->pl_rb_parts_equip_data;
        Mem_copy32(save->pl_rb_parts_sort_data, pl->rb_parts_sort_data, 1);
        Mem_copy32(save->pl_unk474, pl->unk474, 4);
        Mem_copy32(save->pl_rec, pl->rec, 8);
        Player_weapon_bullet_set();
    }
}

// Copies each live player's pad bits for the frame (Joy1's, the scene's while flags_BD bit 5 is
// set, none while bit 6 is set; bit 4 also restores the saved position), then runs its state.
void Player_exec(void)
{
    uint8 flags;

    if ((sint8)Player_work[0].be_flag & Player_work[0].flags & 1)
    {
        flags = Player_work[0].flags_BD;
        if (!(flags & 0x40))
        {
            if (!(flags & 0x20))
            {
                Player_work[0].pad_now = PAD_NOW(Joy1);
                Player_work[0].pad_on  = PAD_ON(Joy1);
                Player_work[0].pad_off = PAD_OFF(Joy1);
                Player_work[0].pad_rep = PAD_REP_OUT(&Joy1);
            }
            else
            {
                Player_work[0].pad_now = D_800C0F96[0];
                Player_work[0].pad_on  = D_800C0F9A;
                Player_work[0].pad_off = D_800C0F9C;
                Player_work[0].pad_rep = D_800C0F9E;
                if (flags & 0x10)
                {
                    Player_work[0].pos   = Player_work[0].svec_438;
                    Player_work[0].pos_l = Player_work[0].pos_428;
                    Player_work[0].ang   = Player_work[0].ang_440;
                    Player_work[0].flags_BD &= 0xEF;
                }
            }
        }
        else
        {
            *(uint32 *)&Player_work[0].pad_now = 0; // pad_now, pad_on
            *(uint32 *)&Player_work[0].pad_off = 0; // pad_off, pad_rep
            if (flags & 0x10)
            {
                Player_work[0].pos   = Player_work[0].svec_438;
                Player_work[0].pos_l = Player_work[0].pos_428;
                Player_work[0].ang   = Player_work[0].ang_440;
                Player_work[0].flags_BD &= 0xEF;
            }
        }
        func_8003C418(&Player_work[0]);
    }
    if ((sint8)Player_work[1].be_flag & Player_work[1].flags & 1)
    {
        if (!(Player_work[1].flags_BD & 0x40))
        {
            Player_work[1].pad_now = D_800C0FE6;
            Player_work[1].pad_on  = D_800C0FEA;
            Player_work[1].pad_off = D_800C0FEC;
            Player_work[1].pad_rep = D_800C0FEE;
        }
        else
        {
            *(uint32 *)&Player_work[1].pad_now = 0; // pad_now, pad_on
            *(uint32 *)&Player_work[1].pad_off = 0; // pad_off, pad_rep
        }
        func_8003C418(&Player_work[1]);
    }
}

void func_8003C2D8(void)
{
    if ((sint8)Player_work[0].be_flag & Player_work[0].flags & 1)
    {
        func_8003C4EC(&Player_work[0]);
        if (Player_work[0].unk449 == 0 && Player_work[0].unk110 == 0)
        {
            func_800341BC(&Player_work[0].joint_pos[8], 0x20, 0, 0, Player_work[0].work_id, &Player_work[0].owner_188, 0x2000000, 0x800000,
                          0);
        }
    }
    if ((sint8)Player_work[1].be_flag & Player_work[1].flags & 1)
    {
        func_8003C4EC(&Player_work[1]);
        if (Player_work[1].unk449 == 0 && Player_work[1].unk110 == 0)
        {
            func_800341BC(&Player_work[1].joint_pos[8], 0x20, 0, 0x2000, Player_work[1].work_id, &Player_work[1].owner_188, 0x2000000,
                          0x800000, 0);
        }
    }
}

void func_8003C418(PL_WORK *pl)
{
    D_80089F94[pl->routine_0](pl);
    if (func_8004324C(pl) == 0)
    {
        pl->set_104      = pl->idx_AC;
        pl->cmd_100.b.b0 = pl->cmd_A4.b.b0;
    }
    if (pl->set_104 != pl->unk105)
    {
        func_800321C8(pl, pl->unk174 & 3, pl->set_104, pl->cmd_100.b.b0);
        pl->unk105 = pl->set_104;
    }
    else
    {
        func_800323FC(pl, pl->unk174 & 3);
    }
    if (pl->idx_AC != pl->old_idx_AD)
    {
        func_800320B8(pl, pl->idx_AC, pl->cmd_A4.b.b0);
        return;
    }
    func_8003234C(pl);
}

void func_8003C4EC(PL_WORK *pl)
{
    sint32 y;
    sint32 floor;

    if (pl->field_74 == 1 && (pl->unk7C & 0x2000) && (uint32)(pl->routine_1 - 7) < 2 && pl->routine_2 < 4)
    {
        key_seq_set(pl, 0x15, 0, 1);
        pl->routine_2 = 4;
        pl->spd.vy    = 0;
        pl->add.vy    = 0;
    }
    if ((uint32)(pl->routine_0 - 1) < 2 && pl->field_76 != 0)
    {
        Ride_move(pl, pl->ride_C0);
    }
    if (pl->routine_0 == 3 && pl->field_76 != 0)
    {
        Ride_move_saved(pl, pl->ride_C0);
    }
    if (Sce_flag_test(0x200) == 0)
    {
        Front_hit_event(pl);
    }
    // field_74 == 0 and field_76 == 0, in one word
    if ((uint32)(pl->routine_0 - 1) < 2 && !(*(uint32 *)&pl->field_74 & 0xFF00FF))
    {
        y     = pl->pos.vy;
        floor = Obj_ceiling_height_get((MODEL_WORK *)pl) - pl->hit_78->max_A;
        if (y < floor - 0x20)
        {
            if (pl->field_75 == 0)
            {
                if (pl->routine_1 == 0xE)
                {
                    func_800394AC();
                    pl->val_108 = 0;
                }
                if (pl->routine_1 == 3)
                {
                    if (pl->routine_2 < 5)
                    {
                        Sound_call(0x8E, 0, 0);
                        Sound_call(0x8F, 0, 0);
                    }
                }
                pl->routine_1             = 7;
                *(uint16 *)&pl->routine_2 = 4; // routine_2 = 4, routine_3 = 0
                pl->spd.vy                = 0;
                pl->unk168                = 0;
                pl->unk169                = 0;
                pl->unk110                = 1;
                pl->unk111                = 0;
            }
            pl->field_74 = 1;
        }
        else if (pl->pos.vy < floor)
        {
            pl->pos.vy   = floor;
            pl->pos_l.vy = floor << 16;
        }
    }
    if (Obj_map_push_out((MODEL_WORK *)pl) < 0)
    {
        pl->spd.vz   = 0;
        pl->spd.vx   = 0;
        pl->pos.vx   = pl->old.vx;
        pl->pos.vz   = pl->old.vz;
        pl->pos_l.vx = pl->old_l.vx;
        pl->pos_l.vz = pl->old_l.vz;
        if (pl->field_74 != 0)
        {
            pl->field_74 = 0;
            pl->spd.vy   = 0;
            pl->pos.vy   = pl->old.vy;
            pl->pos_l.vy = pl->old_l.vy;
        }
    }
    func_8002D004(pl, pl->unk168, pl->unk169);
    Pl_pose_unpack(pl);
    Pl_joint_mtx_set(pl);
    if (pl->be_flag & TRANS)
    {
        Pl_Shadow_Trans(pl, 0x32, 0x2AB, 0);
    }
}

void func_8003C7B0(PL_WORK *pl)
{
    *(uint32 *)&pl->routine_0          = 1; // routine_0 = 1, routine_1 ... routine_3 = 0
    pl->unk6C                          = 0x3C;
    pl->spd.vx                         = 0;
    pl->spd.vy                         = 0;
    pl->spd.vz                         = 0;
    pl->unk114                         = 0;
    pl->unk116                         = 0;
    pl->unk118                         = 0;
    pl->unk112                         = 0;
    pl->unk113                         = 0;
    pl->unk110                         = 0;
    pl->unk71                          = 0;
    pl->unk73                          = 0;
    pl->owner_188.hit_0                = 0;
    pl->owner_188.mask_4               = 0;
    *(uint32 *)&pl->owner_188.vec_8.vx = 0; // vx, vy
    *(uint32 *)&pl->owner_188.vec_8.vz = 0; // vz, pad
    pl->unk168                         = 0;
    pl->unk169                         = 0;
    pl->set_104                        = 0;
    pl->idx_AC                         = 0;
    pl->unk105                         = 0;
    pl->old_idx_AD                     = 0;
    pl->unk174                         = 0;
    pl->unk177                         = 0;
    pl->unk175                         = 7;
    pl->val_108                        = 0;
    pl->ang_10A                        = 0;
    pl->unk44B                         = 0;
    pl->unk44A                         = 0;
    pl->obj_184                        = 0;
    pl->flags |= 3;
    key_seq_set(pl, 0, 0, 1);
    func_800321C8(pl, 0, 5, 0);
}

void func_8003C88C(PL_WORK *pl)
{
    sint32 hit;
    sint8 timer;
    sint32 mode;

    pl->old        = pl->pos;
    pl->old_l      = pl->pos_l;
    pl->old_ang    = pl->ang;
    pl->old_idx_AD = pl->idx_AC;
    pl->old_life   = pl->life;
    pl->field_75   = pl->field_74;
    pl->unk77      = pl->field_76;
    pl->flags_BD &= 0xF7;
    hit = func_8004AF28(&pl->pos);
    if (hit != 0)
    {
        pl->routine_1 = 0xA;
        pl->routine_2 = 0;
        pl->routine_3 = hit;
    }
    else if ((*(uint32 *)&pl->routine_0 & 0xFFFF00) == 0xA00) // routine_1 == 0xA, routine_2 == 0
    {
        pl->routine_2 = 1;
    }
    if (pl->unk449 == 0)
    {
        if (pl->unk110 == 0)
        {
            pl->flags |= 3;
            damage_check(pl);
        }
        else if (pl->unk110 > 0)
        {
            timer = --pl->unk111;
            if (timer < 0)
            {
                pl->unk71  = 0;
                pl->unk110 = 0;
                pl->flags |= 3;
            }
            else if (timer & 2)
            {
                pl->flags &= 0xFD;
            }
            else
            {
                pl->flags |= 3;
            }
        }
        else
        {
            pl->flags |= 3;
        }
    }
    else
    {
        pl->flags |= 3;
    }
    mode                = pl->unk174 & 0xC0;
    pl->owner_188.hit_0 = 0;
    if (mode != 0)
    {
        if (mode == 0x80)
        {
            func_80042734(pl);
        }
        else
        {
            func_800426F8(pl);
        }
    }
    if (!(pl->flags_BD & 0x80))
    {
        D_80089FF8[pl->routine_1](pl);
        D_80089FA4[pl->routine_1](pl);
    }
    hit = Obj_map_push_out((MODEL_WORK *)pl);
    if (pl->field_74 == 1 && (hit & 0x2000) && (uint32)(pl->routine_1 - 7) < 2 && pl->routine_2 < 4)
    {
        key_seq_set(pl, 0x15, 0, 1);
        pl->routine_2 = 4;
        pl->spd.vy    = 0;
        pl->add.vy    = 0;
    }
    func_80051BAC((MODEL_WORK *)pl);
}

void func_8003CB20(PL_WORK *pl)
{
    if (pl->routine_2 == 0)
    {
        pl->routine_2 = 1;
        pl->spd.vx    = 0;
        pl->spd.vz    = 0;
        pl->unk174 &= 0xFC;
        if (!(pl->unk174 & 0xC0) && pl->unk177 == 0)
        {
            Pl00_shot_enable_on(pl);
            key_seq_set(pl, 0, 0, 0);
        }
        else if (pl->unk174 & 0x40)
        {
            key_seq_set(pl, 0x40, pl->cmd_100.b.b0, 0);
        }
        else
        {
            key_seq_set(pl, 0x60, pl->cmd_100.b.b0, 0);
        }
    }
    else
    {
        pl->unk44D  = 0;
        pl->turn_B4 = 0;
        if (!(pl->unk174 & 0xC0) && pl->unk177 == 0)
        {
            key_seq_set(pl, 0, 0, 0);
        }
    }
}

void func_8003CBF8(PL_WORK *pl)
{
    uint8 flags;

    if (pl->routine_2 == 0)
    {
        pl->routine_2 = 1;
        pl->spd.vz    = 0;
        if (pl->routine_3 == 0)
        {
            pl->spd.vx = 0x50;
        }
        else
        {
            pl->spd.vx = -0x50;
        }
        flags      = pl->unk174 | 4;
        pl->unk174 = flags;
        if ((flags & 0xC0) || pl->unk177 != 0)
        {
            if (flags & 0x40)
            {
                key_seq_set(pl, 0x40, pl->cmd_100.b.b0, 0);
            }
            else
            {
                key_seq_set(pl, 0x60, pl->cmd_100.b.b0, 0);
            }
            return;
        }
    }
    if (!(pl->unk174 & 0xC0) && pl->unk177 == 0)
    {
        if (pl->routine_3 == 0)
        {
            key_seq_set(pl, 0xC, 0, 0);
            func_80042044(pl, 0x20, 0x20);
        }
        else
        {
            key_seq_set(pl, 0xD, 0, 0);
            func_80042044(pl, 0x40, 0x40);
        }
        if (pl->cmd_A4.b.b2 & 0x80)
        {
            Sound_call(0x90, 0, 0);
        }
        func_80041E90(pl, pl->spd.vx, 0, 0);
    }
}

void func_8003CD4C(PL_WORK *pl)
{
    sint32 id;

    id = 0;
    switch (pl->routine_2)
    {
        case 0:
            switch ((sint8)pl->unk112)
            {
                case 0:
                    pl->unk116 = 0;
                    switch ((sint8)pl->unk113)
                    {
                        case 0:
                            id = 4;
                            break;
                        case 1:
                            id = 5;
                            Pl00_shot_enable_off(pl);
                            break;
                        case 2:
                            id = 9;
                            Pl00_shot_enable_off(pl);
                            break;
                        case 3:
                            id = 7;
                            Pl00_shot_enable_off(pl);
                            break;
                    }
                    break;
                case 1:
                    pl->unk116 = 0x400;
                    switch ((sint8)pl->unk113)
                    {
                        case 0:
                            id = 7;
                            break;
                        case 2:
                            id = 5;
                            break;
                        case 3:
                            id = 9;
                            break;
                    }
                    Pl00_shot_enable_off(pl);
                    break;
                case 2:
                    pl->unk116 = 0x800;
                    switch ((sint8)pl->unk113)
                    {
                        case 0:
                            id = 9;
                            break;
                        case 1:
                            id = 7;
                            break;
                        case 3:
                            id = 5;
                            break;
                    }
                    Pl00_shot_enable_off(pl);
                    break;
                case 3:
                    pl->unk116 = -0x400;
                    switch ((sint8)pl->unk113)
                    {
                        case 0:
                            id = 5;
                            break;
                        case 1:
                            id = 9;
                            break;
                        case 2:
                            id = 7;
                            break;
                    }
                    Pl00_shot_enable_off(pl);
                    break;
            }
            pl->spd.vx = 0x200;
            pl->unk113 = 0;
            pl->routine_2 += 2;
            pl->unk174 |= 4;
            key_seq_set(pl, id, 0, 1);
            func_8003D124(pl, (sint8)pl->unk112);
            break;
        case 1:
            if (pl->cmd_A4.b.b0 == 1)
            {
                pl->routine_2++;
            }
            break;
        case 2:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->unk44D = 1;
                pl->routine_2 += 2;
                Pl00_shot_enable_on(pl);
                if ((sint8)pl->unk112 != 1)
                {
                    key_seq_set(pl, 1, 0, 0);
                }
                else
                {
                    key_seq_set(pl, 1, 9, 0);
                }
            }
            func_8003D124(pl, (sint8)pl->unk112);
            break;
        case 3:
            if (pl->cmd_A4.b.b0 == 5)
            {
                pl->unk44D = 1;
                pl->routine_2++;
            }
            // fall through
        case 4:
            func_80042044(pl, 0x28, 0x28);
            func_8003D124(pl, (sint8)pl->unk112);
            if (pl->cmd_A4.b.b2 & 0x80)
            {
                Sound_call(0x91, 0, 0);
            }
            break;
        case 5:
            switch ((sint8)pl->unk112)
            {
                case 0:
                    pl->routine_1             = 0;
                    *(uint16 *)&pl->routine_2 = 0; // routine_2, routine_3
                    break;
                case 1:
                    Pl00_shot_enable_off(pl);
                    key_seq_set(pl, 8, 0, 0);
                    break;
                case 2:
                    Pl00_shot_enable_off(pl);
                    key_seq_set(pl, 0xA, 0, 0);
                    break;
                case 3:
                    Pl00_shot_enable_off(pl);
                    key_seq_set(pl, 6, 0, 0);
                    break;
            }
            pl->add.vx = 0x30;
            pl->routine_2++;
            func_8003D124(pl, (sint8)pl->unk112);
            break;
        case 6:
            if (pl->cmd_A4.b.b2 == 1)
            {
                pl->routine_1             = 0;
                *(uint16 *)&pl->routine_2 = 0; // routine_2, routine_3
                pl->unk116                = 0;
                pl->unk112                = 0;
                pl->spd.vx                = 0;
                pl->turn_B4               = 0;
                Pl00_shot_enable_on(pl);
                key_seq_set(pl, 0, 0, 0);
            }
            break;
    }
}

// Sideways move for direction dir: spd.vz is +-0x140 while exactly one key of key_pair[dir][1]
// is held, and without keys_124[2] or [3] the turn is set to +-0x40.
void func_8003D124(PL_WORK *pl, sint32 dir)
{
    uint16 pad;
    uint32 hit;
    uint32 mask;
    uint32 key;

    pad  = pl->pad_now;
    mask = pl->key_pair[(sint16)dir][1].mask;
    key  = pl->key_pair[(sint16)dir][1].key;
    hit  = (pad & 0xFFFF) & mask;
    if (hit != 0 && hit != mask)
    {
        if ((pad & 0xFFFF) & key)
        {
            pl->spd.vz = -0x140;
            if ((pad & (pl->keys_124[2] | pl->keys_124[3])) == 0)
            {
                pl->turn_B4 = 0x40;
            }
        }
        else
        {
            pl->spd.vz = 0x140;
            if ((pad & (pl->keys_124[2] | pl->keys_124[3])) == 0)
            {
                pl->turn_B4 = -0x40;
            }
        }
    }
    else
    {
        pl->spd.vz = 0;
    }
    func_80041E90(pl, pl->spd.vx, 0, pl->spd.vz);
}

void func_8003D1E0(PL_WORK *pl)
{
    uint16 pad;
    uint16 trig;
    sint32 mode;
    uint16 hit;
    WORK_48 *wp;

    pad  = pl->pad_now;
    trig = pl->pad_on;
    switch (pl->routine_2)
    {
        case 0:
            pl->unk174 |= 4;
            key_seq_set(pl, 0x38, 0, 0);
            pl->unk44A++;
            pl->routine_2 += 2;
            break;
        case 1:
            if (pl->keys_124[2] & pad)
            {
                wp = func_80031618();
                if (wp != NULL)
                {
                    wp->be_flag = MOVE;
                    wp->id      = 0x89;
                    wp->type    = 0;
                }
            }
            if (pl->keys_124[3] & pad)
            {
                wp = func_80031618();
                if (wp != NULL)
                {
                    wp->be_flag = MOVE;
                    wp->id      = 0x89;
                    wp->type    = 1;
                }
            }
            pl->routine_2++;
            // fall through
        case 2:
            if (pl->cmd_A4.b.b2 == 0)
            {
                pl->unk44A++;
                break;
            }
            pl->routine_2 = 3;
            pl->spd.vx    = 0x340;
            // fall through
        case 3:
            if (pl->cmd_A4.b.ctl != -1)
            {
                func_80041E90(pl, pl->spd.vx, 0, 0);
                break;
            }
            Sound_call(0x8C, 0, 0);
            pl->routine_2++;
            // fall through
        case 4:
            if ((pl->keys_124[0] | pl->keys_124[1]) & pad)
            {
                if (pad & pl->keys_124[0])
                {
                    mode       = func_80042044(pl, 0x10, 0x10);
                    pl->spd.vx = 0x400;
                    pl->spd.vz = 0xC0;
                }
                else
                {
                    mode       = func_80042044(pl, 0x20, 0x20);
                    pl->spd.vx = 0x280;
                    pl->spd.vz = 0x140;
                    wp         = func_80031618();
                    if (wp != NULL)
                    {
                        func_80042528(pl, (W48_83_WORK *)wp, 1);
                    }
                    wp = func_80031618();
                    if (wp != NULL)
                    {
                        func_80042528(pl, (W48_83_WORK *)wp, 2);
                    }
                }
            }
            else
            {
                mode       = func_80042044(pl, 0x18, 0x18);
                pl->spd.vx = 0x340;
                pl->spd.vz = 0x100;
            }
            hit = (pl->keys_124[4] | pl->keys_124[5]) & pad;
            if (hit != 0 && hit != (pl->keys_124[4] | pl->keys_124[5]))
            {
                if (pad & pl->keys_124[5])
                {
                    if (mode == 0)
                    {
                        mode = 1;
                    }
                    pl->spd.vz = -pl->spd.vz;
                    if (!((pl->keys_124[2] | pl->keys_124[3]) & pad))
                    {
                        pl->turn_B4 = 0x40;
                    }
                }
                else
                {
                    if (mode == 0)
                    {
                        mode = 2;
                    }
                    if (!((pl->keys_124[2] | pl->keys_124[3]) & pad))
                    {
                        pl->turn_B4 = -0x40;
                    }
                }
            }
            else
            {
                pl->spd.vz = 0;
            }
            switch (mode)
            {
                case 0:
                    key_seq_set(pl, 0x39, 0, 0);
                    Sound_call(0x8F, 0, 0);
                    break;
                case 1:
                    key_seq_set(pl, 0x3C, 0, 0);
                    if (pl->keys_124[2] & pad)
                    {
                        Sound_call(0x8F, 0, 0);
                    }
                    break;
                case 2:
                    key_seq_set(pl, 0x3D, 0, 0);
                    if (pl->keys_124[3] & pad)
                    {
                        Sound_call(0x8F, 0, 0);
                    }
                    break;
            }
            func_80041E90(pl, pl->spd.vx, 0, pl->spd.vz);
            pl->unk44D = 1;
            if (!(pl->keys_124[8] & pad) || !(pl->unk16B & 2))
            {
                Sound_call(0x8E, 0, 0);
                Sound_call(0x8F, 0, 0);
                key_seq_set(pl, 0x3A, 0, 0);
                pl->routine_2++;
            }
            break;
        case 5:
            pl->spd.vx -= 0x28;
            func_80042044(pl, 0x20, 0x20);
            func_80041E90(pl, pl->spd.vx, 0, 0);
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->routine_1             = 0;
                *(uint16 *)&pl->routine_2 = 0; // routine_2, routine_3
                pl->spd.vx                = 0;
                pl->unk44A                = 0;
            }
            break;
    }
    if (pl->routine_2 == 3 || pl->routine_2 == 4)
    {
        if (pl->keys_124[3] & trig)
        {
            wp = func_80031618();
            if (wp != NULL)
            {
                wp->be_flag = MOVE;
                wp->id      = 0x89;
                wp->type    = 1;
            }
        }
        if (pl->keys_124[2] & trig)
        {
            wp = func_80031618();
            if (wp != NULL)
            {
                wp->be_flag = MOVE;
                wp->id      = 0x89;
                wp->type    = 0;
            }
        }
    }
}

void func_8003D6DC(PL_WORK *pl)
{
    uint32 pad;
    sint32 spd;
    sint32 max;
    sint32 mask;

    pad = pl->pad_now;
    if (pl->routine_2 == 0)
    {
        pl->routine_2++;
        pl->turn_acc_B6 = 0;
        pl->unk44D      = 0;
    }
    spd = 2;
    if (pl->keys_124[8] & pad)
    {
        max = 0x20;
    }
    else
    {
        spd = 4;
        max = 0x48;
    }
    if (!(pl->unk174 & 0xC0))
    {
        mask = pl->keys_124[2] | pl->keys_124[3];
        if ((pad & mask) != mask)
        {
            // Both arms make the same call in the original too.
            if (pl->keys_124[2] & pad)
            {
                key_seq_set(pl, 0xD, 0, 0);
            }
            else
            {
                key_seq_set(pl, 0xD, 0, 0);
            }
        }
        else
        {
            key_seq_set(pl, 0, 0, 0);
        }
    }
    else if (pl->unk174 & 0x80)
    {
        key_seq_set(pl, 0x60, 0, 0);
    }
    else
    {
        key_seq_set(pl, 0x40, 0, 0);
    }
    func_80042044(pl, spd, max);
}

void func_8003D7D4(PL_WORK *pl)
{
    uint32 pad;
    sint16 key;

    switch (pl->routine_2)
    {
        case 0:
            switch ((sint8)pl->unk112)
            {
                case 1:
                    pl->turn_10E = -0x80;
                    pl->key_164  = pl->keys_124[4];
                    break;
                case 2:
                    pl->turn_10E = 0x100;
                    pl->key_164  = pl->keys_124[1];
                    break;
                case 3:
                    pl->turn_10E = 0x80;
                    pl->key_164  = pl->keys_124[5];
                    break;
            }
            pl->routine_2++;
            // fall through
        case 1:
            pad = pl->pad_now;
            key = pl->key_164;
            if (!(pad & key) || (pad & (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) & ~key))
            {
                pl->key_164 = 0;
            }
            pl->ang.vy = (pl->ang.vy + pl->turn_10E) & 0xFFF;
            pl->unk116 = (pl->unk116 + pl->turn_10E) & 0xFFF;
            if (pl->unk116 == 0)
            {
                pl->unk112    = 0;
                pl->routine_1 = 0;
                if (pl->key_164 != 0)
                {
                    *(uint16 *)&pl->routine_2 = 0x100; // routine_2 = 0, routine_3 = 1
                }
                else
                {
                    *(uint16 *)&pl->routine_2 = 0; // routine_2, routine_3
                }
                Pl00_shot_enable_on(pl);
            }
            break;
    }
    if (!(pl->unk174 & 0xC0) && pl->unk177 == 0)
    {
        pl->turn_B4 = 0;
        key_seq_set(pl, 0, 0, 0);
    }
}

void func_8003D960(PL_WORK *pl)
{
    uint32 pad;
    uint32 mask;
    uint32 key;

    pad = pl->pad_now;
    if (pl->routine_2 == 0)
    {
        pl->routine_2 = 1;
        pl->turn_B4   = 0;
        pl->unk174 |= 4;
    }
    key  = pl->keys_124[6];
    mask = key | pl->keys_124[7];
    if ((pad & mask) != mask)
    {
        if (key & pad)
        {
            pl->spd.vz = 0x20;
            key_seq_set(pl, 0xF, 0, 0);
        }
        else
        {
            pl->spd.vz = -0x20;
            key_seq_set(pl, 0xE, 0, 0);
        }
    }
    else
    {
        pl->spd.vz = 0;
    }
    func_80041E90(pl, 0, 0, pl->spd.vz);
    if (pl->cmd_A4.b.b0 == 8)
    {
        Sound_call(0x95, 0, 0);
    }
}

void func_8003DA34(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    switch (pl->routine_2)
    {
        case 0:
            pl->routine_2++;
            pl->unk112  = 0;
            pl->unk116  = 0;
            pl->turn_B4 = 0;
            if (!(pad & pl->key_pair[0][1].mask))
            {
                pl->spd.vz = 0;
            }
            Pl00_shot_enable_off(pl);
            key_seq_set(pl, 0x10, 0, 1);
            break;
        case 1:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->field_74 = 1;
                pl->routine_2++;
                pl->old_idx_AD = pl->idx_AC;
                if (pl->unk16B & 1)
                {
                    pl->spd.vy = -0x320;
                }
                else
                {
                    pl->spd.vy = -0x1C0;
                }
                Pl00_shot_enable_on(pl);
                key_seq_set(pl, 0x11, 0, 1);
                func_8003E068(pl, 0);
                Sound_call(0x92, 0, 0);
            }
            break;
        case 2:
            func_8003E068(pl, (sint8)pl->unk112);
            if (pad & pl->keys_124[10])
            {
                pl->spd.vy += 0x30;
                if (pl->spd.vy >= 0)
                {
                    key_seq_set(pl, 0x12, 0, 1);
                    pl->routine_2 += 2;
                }
            }
            else
            {
                pl->routine_2++;
            }
            break;
        case 3:
            func_8003E068(pl, (sint8)pl->unk112);
            if (-pl->spd.vy > 0x240)
            {
                pl->spd.vy += 0x240;
            }
            else
            {
                key_seq_set(pl, 0x12, 0, 1);
                pl->spd.vy = 0;
                pl->routine_2 += 2;
            }
            break;
        case 4:
            key_seq_set(pl, 0x12, 0, 1);
            pl->routine_2++;
            // fall through
        case 5:
            func_8003E068(pl, (sint8)pl->unk112);
            pl->spd.vy += 0x30;
            break;
        case 6:
            break;
    }
}

void func_8003DC5C(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    switch (pl->routine_2)
    {
        case 0:
            pl->field_74 = 1;
            pl->unk44D   = 1;
            pl->routine_2 += 2;
            pl->old_idx_AD = pl->idx_AC;
            if (pl->unk16B & 1)
            {
                pl->spd.vy = -0x320;
            }
            else
            {
                pl->spd.vy = -0x1C0;
            }
            if (!(pad & pl->key_pair[(sint8)pl->unk112][1].mask))
            {
                pl->spd.vz = 0;
            }
            Pl00_shot_enable_on(pl);
            key_seq_set(pl, 0x14, 0, 1);
            func_8003E068(pl, (sint8)pl->unk112);
            Sound_call(0x92, 0, 0);
            break;
        case 1:
        case 2:
            func_8003E068(pl, (sint8)pl->unk112);
            if (pad & pl->keys_124[10])
            {
                pl->spd.vy += 0x30;
                if (pl->spd.vy >= 0)
                {
                    key_seq_set(pl, 0x15, 0, 1);
                    pl->routine_2 += 3;
                }
            }
            else
            {
                pl->routine_2++;
            }
            break;
        case 3:
            func_8003E068(pl, (sint8)pl->unk112);
            if (-pl->spd.vy > 0x240)
            {
                pl->spd.vy += 0x240;
            }
            else
            {
                key_seq_set(pl, 0x15, 0, 1);
                pl->spd.vy = 0;
                pl->routine_2 += 2;
            }
            break;
        case 4:
            key_seq_set(pl, 0x12, 0, 1);
            pl->spd.vx = 0x200;
            pl->routine_2++;
            // fall through
        case 5:
            func_8003E068(pl, (sint8)pl->unk112);
            pl->spd.vy += 0x30;
            break;
        case 6:
            if (pl->cmd_A4.b.ctl != -1)
            {
                break;
            }
            Pl00_shot_enable_off(pl);
            switch ((sint8)pl->unk112)
            {
                case 0:
                    if (!(pad & pl->keys_124[8]))
                    {
                        if (pad & pl->keys_124[0])
                        {
                            goto land;
                        }
                        key_seq_set(pl, 0x2A, 0, 0);
                    }
                    else if (pl->unk44A > 0x10)
                    {
                        pl->routine_1             = 3;
                        *(uint16 *)&pl->routine_2 = 1; // routine_2 = 1, routine_3 = 0
                        pl->spd.vx                = 0x300;
                        pl->spd.vz                = 0;
                        key_seq_set(pl, 0x3B, 0, 0);
                        return;
                    }
                    else
                    {
                        key_seq_set(pl, 0x2A, 0, 0);
                    }
                    pl->routine_2++;
                    return;
                case 1:
                    if (!(pad & pl->keys_124[8]) && (pad & pl->keys_124[4]))
                    {
                        goto land;
                    }
                    key_seq_set(pl, 0x2B, 0, 0);
                    pl->routine_2++;
                    return;
                case 2:
                    if (!(pad & pl->keys_124[8]) && (pad & pl->keys_124[1]))
                    {
                        goto land;
                    }
                    key_seq_set(pl, 0x2D, 0, 0);
                    pl->routine_2++;
                    return;
                case 3:
                    if (!(pad & pl->keys_124[8]) && (pad & pl->keys_124[5]))
                    {
                        goto land;
                    }
                    key_seq_set(pl, 0x2C, 0, 0);
                    pl->routine_2++;
                    return;
            }
        land:
            pl->spd.vx                = 0x200;
            pl->routine_1             = 2;
            pl->spd.vy                = 0;
            *(uint16 *)&pl->routine_2 = 2; // routine_2 = 2, routine_3 = 0
            key_seq_set(pl, 0x17, 0, 0);
            break;
        case 7:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->routine_1             = 0;
                *(uint16 *)&pl->routine_2 = 0; // routine_2, routine_3
                pl->spd.vx                = 0;
                pl->spd.vz                = 0;
                pl->unk44A                = 0;
                Pl00_shot_enable_on(pl);
                key_seq_set(pl, 0, 0, 0);
                pl->unk116  = 0;
                pl->unk112  = 0;
                pl->turn_B4 = 0;
            }
            break;
    }
}

void func_8003E068(PL_WORK *pl, sint32 dir)
{
    uint16 pad;
    sint32 mask;
    sint32 key;
    sint32 hit;

    mask = pl->key_pair[(sint16)dir]->mask;
    pad  = pl->pad_now;
    key  = pl->key_pair[(sint16)dir]->key;
    hit  = pad & mask;
    if (hit != 0 && hit != mask)
    {
        if (pad & key)
        {
            pl->spd.vx += 0x28;
            if (pl->spd.vx > 0x280)
            {
                pl->spd.vx = 0x280;
            }
        }
        else
        {
            pl->spd.vx -= 0x28;
            if (pl->spd.vx < -0x280)
            {
                pl->spd.vx = -0x280;
            }
        }
    }
    mask = pl->key_pair[(sint16)dir][1].mask;
    key  = pl->key_pair[(sint16)dir][1].key;
    hit  = pad & mask;
    if (hit != 0)
    {
        if (hit != mask)
        {
            if (pad & key)
            {
                pl->spd.vz -= 0x20;
                if (pl->spd.vz < -0x100)
                {
                    pl->spd.vz = -0x100;
                }
            }
            else
            {
                pl->spd.vz += 0x20;
                if (pl->spd.vz > 0x100)
                {
                    pl->spd.vz = 0x100;
                }
            }
        }
        else
        {
            pl->spd.vz = 0;
        }
    }
    func_80042044(pl, 4, 0x20);
    func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
    if (pl->field_74 == 0)
    {
        if (pl->routine_1 == 7)
        {
            key_seq_set(pl, 0x13, 0, 1);
        }
        else
        {
            key_seq_set(pl, 0x16, 0, 1);
        }
        Sound_call(0x93, 0, 0);
        pl->routine_1 = 8;
        pl->routine_2 = 6;
    }
}

void func_8003E224(PL_WORK *pl)
{
    switch (pl->routine_2)
    {
        case 0:
            pl->unk110 = -1;
            if (pl->cmd_A4.b.ctl != -1)
            {
                return;
            }
            pl->field_74 = 1;
            pl->spd.vx   = 0;
            pl->spd.vy   = 0;
            pl->routine_2++;
            if (pl->routine_3 != 0)
            {
                pl->spd.vz = -0x200;
                key_seq_set(pl, 0x18, 0, 1);
            }
            else
            {
                pl->spd.vz = 0x200;
                key_seq_set(pl, 0x19, 0, 1);
            }
            Sound_call(0x92, 0, 0);
            return;
        case 1:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->spd.vx = 0x200;
                pl->spd.vy = -0x80;
                pl->spd.vz = 0;
                pl->routine_2++;
                if (pl->routine_3 != 0)
                {
                    pl->unk112 = 3;
                    pl->unk116 = -0x400;
                }
                else
                {
                    pl->unk112 = 1;
                    pl->unk116 = 0x400;
                }
                key_seq_set(pl, 0x1A, 0, 1);
            }
            pl->field_74 = 1;
            break;
        case 2:
            pl->spd.vy += 0x30;
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->unk110 = 0;
                if (pl->field_74 != 0)
                {
                    pl->routine_2++;
                    key_seq_set(pl, 0x1C, 0, 1);
                }
                else
                {
                    pl->spd.vy = 0;
                    pl->routine_2 += 2;
                    key_seq_set(pl, 0x1B, 0, 1);
                }
            }
            else
            {
                pl->field_74 = 1;
            }
            break;
        case 3:
            pl->spd.vy += 0x30;
            if (pl->field_74 == 0)
            {
                pl->spd.vy = 0;
                pl->routine_2++;
                key_seq_set(pl, 0x1B, pl->cmd_A4.b.b0, 1);
            }
            else if (pl->cmd_A4.b.ctl == -1)
            {
                key_seq_set(pl, 0x12, 0, 1);
                pl->routine_1 = 7;
                pl->routine_2 = 5;
            }
            break;
        case 4:
            if (pl->cmd_A4.b.b2 == 1)
            {
                if (pl->routine_3 != 0)
                {
                    pl->spd.vz = 0xC0;
                }
                else
                {
                    pl->spd.vz = -0xC0;
                }
                Sound_call(0x93, 0, 0);
                pl->routine_1 = 8;
                pl->routine_2 = 6;
                return;
            }
            break;
    }
    func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
}

void func_8003E4A8(PL_WORK *pl)
{
    W48_83_WORK *wp;

    switch (pl->routine_2)
    {
        case 0:
            switch (pl->routine_3)
            {
                case 1:
                    pl->pos_l.vz += -0x180000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 2:
                    pl->pos_l.vz += 0x180000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 3:
                    pl->pos_l.vx += 0x180000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 4:
                    pl->pos_l.vx += -0x180000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 5:
                    pl->pos_l.vx += 0xC0000;
                    pl->pos_l.vz -= 0xC0000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 6:
                    pl->pos_l.vx += -0xC0000;
                    pl->pos_l.vz += 0xC0000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 7:
                    pl->pos_l.vx += -0xC0000;
                    pl->pos_l.vz += -0xC0000;
                    pl->pos_l.vy += 0x200000;
                    break;
                case 8:
                    pl->pos_l.vx += 0xC0000;
                    pl->pos_l.vz += 0xC0000;
                    pl->pos_l.vy += 0x200000;
                    break;
            }
            wp = (W48_83_WORK *)func_80031618();
            if (wp != NULL)
            {
                func_80042528(pl, wp, 0);
            }
            func_80030150(&pl->pos_l, &pl->pos);
            key_seq_set(pl, 0x12, 0, 0);
            pl->spd.vz = 0;
            pl->spd.vy = 0;
            pl->spd.vx = 0;
            break;
        case 1:
            key_seq_set(pl, 0x13, 0, 1);
            pl->routine_2++;
            break;
        case 2:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->routine_1 = 8;
                pl->routine_2 = 6;
            }
            break;
    }
}

void func_8003E6B0(PL_WORK *pl)
{
    switch (pl->routine_2)
    {
        case 0:
            if (pl->routine_3 == 0)
            {
                key_seq_set(pl, 0x20, 0, 1);
                pl->spd.vx = -0x200;
            }
            else
            {
                key_seq_set(pl, 0x21, 0, 1);
                pl->spd.vx = 0x200;
            }
            pl->spd.vy = 0;
            pl->spd.vz = 0;
            pl->unk168 = 1;
            pl->unk169 = 1;
            pl->unk44A = 0;
            Pl00_shot_enable_off(pl);
            func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
            Sound_key_off_voice(0x16);
            Sound_call(0x97, 0, 0);
            func_800395E8();
            pl->val_108 = 0;
            pl->routine_2++;
            return;
        case 1:
            if (pl->cmd_A4.b.b2 == 1)
            {
                pl->routine_2++;
            }
            // fall through
        case 2:
            if (pl->routine_3 == 0)
            {
                pl->spd.vx += 0x40;
            }
            else
            {
                pl->spd.vx -= 0x40;
            }
            if (pl->spd.vx != 0)
            {
                func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
                return;
            }
            pl->spd.vx = 0;
            pl->routine_2++;
            return;
        case 3:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->routine_1 = 8;
                pl->routine_2 = 6;
                pl->unk71     = 0;
                pl->unk168    = 0;
                pl->unk169    = 0;
            }
            return;
    }
}

void func_8003E860(PL_WORK *pl)
{
    switch (pl->routine_2)
    {
        case 0:
        case 1:
            key_seq_set(pl, 0x22, pl->routine_2 != 0 ? 6 : 0, 1);
            pl->spd.vx = -0x200;
            Pl00_shot_enable_off(pl);
            pl->spd.vy   = -0x160;
            pl->spd.vz   = 0;
            pl->field_74 = 1;
            pl->unk110   = -1;
            pl->unk168   = 1;
            pl->unk169   = 1;
            pl->unk44A   = 0;
            func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
            Sound_key_off_voice(0x16);
            Sound_call(0x98, 0, 0);
            func_800395E8();
            pl->val_108 = 0;
            pl->routine_2++;
            return;
        case 2:
            if (pl->field_74 == 0)
            {
                key_seq_set(pl, 0x23, 0, 1);
                Sound_call(0x99, 0, 0);
                pl->routine_2++;
                return;
            }
            if (pl->cmd_A4.b.b2 == 1)
            {
                pl->routine_2 += 2;
            }
            pl->spd.vy += 0x30;
            func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
            return;
        case 3:
            if (pl->cmd_A4.b.ctl != -1)
            {
                return;
            }
            if (pl->life >= 0)
            {
                key_seq_set(pl, 0x25, 0, 1);
                pl->ang.vy -= pl->unk116;
                pl->unk112 = 0;
                pl->unk116 = 0;
                func_80039A38(&D_80097D9C);
                func_8005D528();
                pl->routine_1 = 8;
                pl->routine_2 = 6;
                pl->unk110    = 1;
                pl->unk71     = 0;
                pl->unk168    = 0;
                pl->unk169    = 0;
                pl->unk111    = 0x30;
            }
            else
            {
                pl->routine_0 = 2;
                pl->routine_1 = 0;
            }
            return;
        case 4:
            if (pl->field_74 == 0)
            {
                key_seq_set(pl, 0x24, 0, 1);
                if (func_8005D8C4(8) && pl->unk16A == 0)
                {
                    pl->life -= 8;
                }
                Swing_Camera2(0x1E, 0x400, 0x2800, &pl->pos);
                Sound_call(0x99, 0, 0);
                pl->routine_2++;
            }
            else
            {
                pl->spd.vy += 0x30;
                func_80041E90(pl, pl->spd.vx, pl->spd.vy, pl->spd.vz);
            }
            return;
        case 5:
            if (pl->cmd_A4.b.ctl != -1)
            {
                return;
            }
            if (pl->life >= 0)
            {
                key_seq_set(pl, 0x29, 0, 1);
                pl->ang.vy -= pl->unk116;
                pl->unk112 = 0;
                pl->unk116 = 0;
                func_80039A38(&D_80097D9C);
                func_8005D528();
                pl->routine_1 = 8;
                pl->routine_2 = 6;
                pl->unk110    = 1;
                pl->unk71     = 0;
                pl->unk168    = 0;
                pl->unk169    = 0;
                pl->unk111    = 0x30;
            }
            else
            {
                pl->routine_0 = 2;
                pl->routine_1 = 0;
            }
            return;
    }
}

void func_8003EB08(PL_WORK *pl)
{
    SVECTOR pos;
    uint16 pad;
    sint32 dir;
    sint32 h;

    pad = pl->pad_now;
    switch (pl->routine_2)
    {
        case 0:
            Pl00_shot_enable_off(pl);
            key_seq_set(pl, 0x1D, 0, 0);
            Sound_call(0x9F, 0, 0);
            pl->unk44A  = 0;
            pl->turn_B4 = 0;
            pl->unk44D  = 0;
            pl->routine_2++;
            break;
        case 1:
            if (pl->cmd_A4.b.ctl == -1)
            {
                key_seq_set(pl, 0x1E, 0, 0);
                pl->routine_2++;
            }
            break;
        case 2:
            if (pl->keys_124[1] & pad)
            {
                pl->routine_2 = 6;
                break;
            }
            pos = pl->pos;
            dir = (pl->ang.vy - pl->unk116 + 0x200) >> 10;
            if (dir & 1)
            {
                if (dir & 2)
                {
                    pos.vx += pl->hit_78->max_2 + 1;
                }
                else
                {
                    pos.vx += pl->hit_78->min_0 - 1;
                }
            }
            else if (dir & 2)
            {
                pos.vz += pl->hit_78->max_6 + 1;
            }
            else
            {
                pos.vz += pl->hit_78->min_4 - 1;
            }
            pos.vy -= 0x98;
            h = func_80048EA4(&pos, 0, 0, pl->work_id) + 0x98;
            if (ABS(pl->pos.vy - h) < 0x20)
            {
                pl->pos.vy   = h;
                pl->pos_l.vy = h << 16;
            }
            else
            {
                func_8003EE68(pl);
                break;
            }
            if (pl->keys_124[0] & pad)
            {
                pl->field_75 = 2;
                pl->field_74 = 2;
                pl->field_76 = 0;
                pl->spd.vx   = 0;
                pl->spd.vz   = 0;
                pl->routine_2++;
                pl->spd.vy = ((pl->pos.vy - pl->old.vy) << 5) - 0x90;
                key_seq_set(pl, 0x1F, 0, 0);
            }
            break;
        case 3:
            func_80041E90(pl, 0, pl->spd.vy, 0);
            if (pl->cmd_A4.b.b2 == 1)
            {
                pl->routine_2++;
            }
            break;
        case 4:
            pl->spd.vx = 0x50;
            pl->spd.vy = -0x1B0;
            pl->spd.vz = 0;
            func_80041E90(pl, pl->spd.vx, pl->spd.vy, 0);
            pl->routine_2++;
            break;
        case 5:
            pl->spd.vy += 0x30;
            func_80041E90(pl, pl->spd.vx, pl->spd.vy, 0);
            if (pl->field_74 == 0)
            {
                key_seq_set(pl, 0x13, 0, 1);
                Sound_call(0x93, 0, 0);
                pl->routine_1 = 8;
                pl->routine_2 = 6;
            }
            if (pl->cmd_A4.b.ctl == -1)
            {
                func_8003EE68(pl);
            }
            break;
        case 6:
            pl->spd.vx = -0x2A;
            pl->spd.vy = 0;
            pl->spd.vz = 0;
            func_80041E90(pl, pl->spd.vx, 0, 0);
            func_8003EE68(pl);
            break;
    }
}

void func_8003EE68(PL_WORK *pl)
{
    pl->routine_1             = 7;
    *(uint16 *)&pl->routine_2 = 4; // routine_2 = 4, routine_3 = 0
    pl->field_74 = pl->field_75 = 1;
    Pl00_shot_enable_on(pl);
    key_seq_set(pl, 0x12, 0, 1);
}

// Locked on: turns the player toward D_80097D08 (ang_10A) and tilts val_108 toward its pitch,
// stepping by turn_10E (up to 0x40, within -0x1C0..0x1C0). Without a target, or when
// func_8003F224 says so, val_108 and the turn follow the keys instead.
void func_8003EEC0(PL_WORK *pl)
{
    MODEL_WORK *target;
    sint32 dir;
    uint16 angle;

    if (pl->routine_2 == 0)
    {
        pl->routine_2 = 1;
        pl->spd.vx    = 0;
        pl->spd.vy    = 0;
        pl->spd.vz    = 0;
        pl->val_108   = 0;
        pl->ang_10A   = 0;
        pl->turn_10E  = 0;
    }
    target = D_80097D08;
    if (target == NULL || !(D_80098B18 & 2) || func_8003F224(pl) != 0)
    {
        func_80041EF4(pl, 2, 0x40);
        func_80039630(pl->val_108, 0x15E);
        pl->turn_10E = 0;
        if (!(pl->unk174 & 0xC0))
        {
            func_80042094(pl, 4, 0x48, 1);
        }
        else if (func_80041158(pl) == 0)
        {
            func_80042094(pl, 4, 0x48, 0);
        }
        else
        {
            pl->turn_B4 = 0;
        }
        return;
    }
    angle       = func_80031268(&pl->pos, &target->pos) & 0xFFF;
    pl->ang_10A = angle;
    dir         = pl->ang.vy - angle;
    if (dir > 0x800)
    {
        dir -= 0x1000;
    }
    if (dir < -0x800)
    {
        dir += 0x1000;
    }
    if (!(pl->unk174 & 0xC0))
    {
        func_8003F188(pl, dir, 1);
    }
    else if (func_80041044(pl) == 0)
    {
        func_8003F188(pl, dir, 0);
    }
    dir = func_8003129C(&pl->pos, &target->pos) - 0xC00;
    if (dir == pl->val_108)
    {
        pl->turn_10E = 0;
    }
    else if (dir - pl->val_108 > 0)
    {
        if (pl->turn_10E < 0)
        {
            pl->turn_10E = 0;
        }
        else
        {
            pl->turn_10E += 4;
            if (pl->turn_10E > 0x40)
            {
                pl->turn_10E = 0x40;
            }
        }
        if (dir - pl->val_108 > pl->turn_10E)
        {
            pl->val_108 += pl->turn_10E;
        }
        else
        {
            pl->val_108 = dir;
        }
        if (pl->val_108 > 0x1C0)
        {
            pl->val_108 = 0x1C0;
        }
    }
    else
    {
        if (pl->turn_10E > 0)
        {
            pl->turn_10E = 0;
        }
        else
        {
            pl->turn_10E -= 4;
            if (pl->turn_10E < -0x40)
            {
                pl->turn_10E = -0x40;
            }
        }
        if (dir - pl->val_108 < pl->turn_10E)
        {
            pl->val_108 += pl->turn_10E;
        }
        else
        {
            pl->val_108 = dir;
        }
        if (pl->val_108 < -0x1C0)
        {
            pl->val_108 = -0x1C0;
        }
    }
    func_80039630(pl->val_108, 0x15E);
}

// Turns toward ang_10A: by 0x80 a frame (with sequence 0xD) while dir is at least 0x80 away,
// then snaps to it (sequence 0). anim: also set the keyframe sequence.
void func_8003F188(PL_WORK *pl, sint32 dir, sint32 anim)
{
    sint16 turn;

    if ((dir < 0 ? -dir : dir) < 0x80)
    {
        pl->turn_B4 = 0;
        pl->ang.vy  = pl->ang_10A;
        if (anim)
        {
            key_seq_set(pl, 0, 0, 0);
        }
    }
    else
    {
        turn = -0x80;
        if (dir <= 0)
        {
            turn = 0x80;
        }
        pl->turn_B4 = turn;
        if (anim)
        {
            key_seq_set(pl, 0xD, 0, 0);
        }
        pl->ang.vy += pl->turn_B4;
    }
}

sint32 func_8003F224(PL_WORK *pl)
{
    uint16 pad;
    sint32 mode;

    pad = pl->pad_now;
    if (Game_work.unk056 == 0)
    {
        mode = Game_work.unk083;
        if (mode == 0 && (pl->keys_124[13] & pad))
        {
            return 1;
        }
        if (mode != 1)
        {
            return 0;
        }
        if (pl->keys_124[14] & pad)
        {
            return 0;
        }
    }
    return 1;
}

void func_8003F288(PL_WORK *pl)
{
    switch (pl->routine_2)
    {
        case 0:
            key_seq_set(pl, 0x80, 0, 1);
            pl->routine_2++;
            break;
        case 1:
            pl->old        = pl->pos;
            pl->old_l      = pl->pos_l;
            pl->old_ang    = pl->ang;
            pl->old_idx_AD = pl->idx_AC;
            pl->pos        = pl->svec_438;
            pl->pos_l      = pl->pos_428;
            pl->ang        = pl->ang_440;
            break;
        case 2:
            pl->routine_1 = 0xC;
            pl->routine_2 = 0;
            break;
    }
}

void func_8003F3E8(PL_WORK *pl)
{
    switch (pl->routine_2)
    {
        case 0:
            key_seq_set(pl, 0x30, 0, 1);
            pl->routine_2++;
            break;
        case 1: // empty, but it keeps the compare chain's layout
            break;
        case 2:
            key_seq_set(pl, 0x31, 0, 1);
            pl->routine_2++;
            break;
        case 3:
            if (pl->cmd_A4.b.ctl == -1)
            {
                pl->routine_1 = 0;
                pl->routine_2 = 0;
            }
            break;
    }
}

void func_8003F498(PL_WORK *pl)
{
    if (pl->routine_2 == 0)
    {
        key_seq_set(pl, 0x33, 0, 1);
        pl->routine_2++;
    }
}

// Same code as func_8003F498, with sequence 0x34.
void func_8003F4E8(PL_WORK *pl)
{
    if (pl->routine_2 == 0)
    {
        key_seq_set(pl, 0x34, 0, 1);
        pl->routine_2++;
    }
}

// Same code as func_8003F498, with sequence 0x35.
void func_8003F538(PL_WORK *pl)
{
    if (pl->routine_2 == 0)
    {
        key_seq_set(pl, 0x35, 0, 1);
        pl->routine_2++;
    }
}

// Same code as func_8003F498, with sequence 0x36.
void func_8003F588(PL_WORK *pl)
{
    if (pl->routine_2 == 0)
    {
        key_seq_set(pl, 0x36, 0, 1);
        pl->routine_2++;
    }
}

void func_8003F5D8(PL_WORK *pl)
{
    uint32 pad;
    uint32 on;

    pad = pl->pad_now;
    on  = pl->pad_on;
    if (func_80040AEC(pl) != 0 || front_box_search(pl) != 0)
    {
        pl->unk44A = 0;
        return;
    }
    if (on & (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])))
    {
        pl->routine_3 = 0;
    }
    if ((pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                (pl->keys_124[11] | pl->keys_124[12]) | (pl->keys_124[2] | pl->keys_124[3]))) ||
        (pl->unk176 & 3))
    {
        pl->unk44A = 0;
        if (func_800410D4(pl) != 0 ||
            ((func_80040B68(pl, 0), func_800406A8(pl) == 0) &&
             (func_80041044(pl) != 0 || func_80040FA8(pl) == 0 || pl->routine_3 != 0 ||
              (func_80040380(pl) == 0 && func_800403D4(pl, pl->routine_3) == 0 && func_80040468(pl, pl->routine_3) == 0 &&
               func_800404FC(pl, pl->routine_3) == 0)) &&
             ((pl->unk174 & 0xC0) || pl->unk177 != 0 ||
              (func_800402C4(pl) == 0 && func_80040630(pl, pl->routine_3) == 0 && func_8004030C(pl, pl->routine_3) == 0))))
        {
            if (func_80041158(pl) == 0)
            {
                func_800405F4(pl);
            }
            goto reset;
        }
    }
    else
    {
    reset:
        func_80040574(pl);
    }
}

void func_8003F7F0(PL_WORK *pl)
{
    uint32 pad;

    pad = pl->pad_now;
    if (front_box_search(pl) == 0)
    {
        if (!(pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                     (pl->keys_124[11] | pl->keys_124[12]))) ||
            func_80040B68(pl, 0) != 0)
        {
            goto reset;
        }
        if (func_800406A8(pl) == 0 && func_80040380(pl) == 0 && func_800404FC(pl, 0) == 0)
        {
            if ((pl->unk174 & 0xC0) || pl->unk177 != 0)
            {
                goto reset;
            }
            if (func_800402C4(pl) == 0 && func_8004030C(pl, 0) == 0)
            {
                if (pl->routine_3 != 0)
                {
                    if (pl->keys_124[0] & pad)
                    {
                        if (!(pl->keys_124[8] & pad))
                        {
                            pl->routine_1             = 2;
                            *(uint16 *)&pl->routine_2 = 0;
                            pl->unk112                = 0;
                        }
                    }
                    else
                    {
                        goto reset;
                    }
                }
                else if (pl->keys_124[1] & pad)
                {
                    if (!(pl->keys_124[8] & pad))
                    {
                        pl->routine_1             = 2;
                        *(uint16 *)&pl->routine_2 = 0;
                        pl->unk112                = 2;
                    }
                }
                else
                {
                    goto reset;
                }
            }
        }
        return;
    reset:
        pl->routine_1             = 0;
        *(uint16 *)&pl->routine_2 = 0;
    }
}

void func_8003F97C(PL_WORK *pl)
{
    uint16 pad;
    uint16 on;

    pad = pl->pad_now;
    on  = pl->pad_on;
    switch ((sint8)pl->unk112) // lb here, lbu elsewhere
    {
        case 0:
            if (pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                       (pl->keys_124[11] | pl->keys_124[12])))
            {
                func_80040B68(pl, 1);
                if (func_800406DC(pl) || func_8004030C(pl, 0) || func_800404FC(pl, 0))
                {
                    return;
                }
                if (pad & pl->keys_124[0])
                {
                    if (pad & pl->keys_124[8])
                    {
                        pl->routine_1             = 1;
                        *(uint16 *)&pl->routine_2 = 0;
                    }
                    return;
                }
            }
            pl->routine_1             = 0;
            *(uint16 *)&pl->routine_2 = 0;
            Pl00_shot_enable_off(pl);
            return;
        case 1:
            if (!(pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                         (pl->keys_124[11] | pl->keys_124[12]))) ||
                (pad & (pl->keys_124[4] | pl->keys_124[5])) == (pl->keys_124[4] | pl->keys_124[5]) || func_80041044(pl))
            {
                break;
            }
            func_80040B68(pl, 1);
            if (func_800406DC(pl))
            {
                return;
            }
            if (!(pad & pl->keys_124[8]))
            {
                if (func_80040380(pl) || func_800404FC(pl, 0) || func_80040468(pl, 0) || (pad & pl->keys_124[4]))
                {
                    return;
                }
                break;
            }
            if (Game_work.unk083 != 0)
            {
                break;
            }
            if (pad & pl->keys_124[4])
            {
                if (pl->routine_2 < 5)
                {
                    pl->routine_1             = 5;
                    *(uint16 *)&pl->routine_2 = 0;
                    Pl00_shot_enable_off(pl);
                }
                return;
            }
            break;
        case 2:
            if (!(pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                         (pl->keys_124[11] | pl->keys_124[12]))))
            {
                break;
            }
            if (on & (pl->keys_124[11] | pl->keys_124[12]))
            {
                if (on & pl->keys_124[11])
                {
                    pl->unk176 = 2;
                }
                else
                {
                    pl->unk176 = 1;
                }
                break;
            }
            if (func_800406DC(pl))
            {
                return;
            }
            if (!(pad & pl->keys_124[8]))
            {
                if ((pad & pl->keys_124[1]) || func_80040380(pl) || func_800403D4(pl, 0) || func_80040468(pl, 0))
                {
                    return;
                }
                break;
            }
            if (Game_work.unk083 != 0)
            {
                break;
            }
            if (pad & pl->keys_124[1])
            {
                if (pl->routine_2 < 5)
                {
                    pl->routine_1             = 5;
                    *(uint16 *)&pl->routine_2 = 0;
                    Pl00_shot_enable_off(pl);
                }
                return;
            }
            break;
        case 3:
            if (!(pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                         (pl->keys_124[11] | pl->keys_124[12]))) ||
                (pad & (pl->keys_124[4] | pl->keys_124[5])) == (pl->keys_124[4] | pl->keys_124[5]) || func_80041044(pl))
            {
                break;
            }
            func_80040B68(pl, 1);
            if (func_800406DC(pl))
            {
                return;
            }
            if (pad & pl->keys_124[8])
            {
                if (Game_work.unk083 != 0)
                {
                    break;
                }
                if (pad & pl->keys_124[5])
                {
                    if (pl->routine_2 < 5)
                    {
                        pl->routine_1             = 5;
                        *(uint16 *)&pl->routine_2 = 0;
                        Pl00_shot_enable_off(pl);
                    }
                    return;
                }
                break;
            }
            if (func_80040380(pl) || func_800403D4(pl, 0) || func_800404FC(pl, 0) || (pad & pl->keys_124[5]))
            {
                return;
            }
            break;
    }
    if (pl->routine_2 < 5)
    {
        pl->routine_2 = 5;
    }
}

void func_8003FDA8(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    if (pl->routine_2 < 3 && !(pad & pl->keys_124[8]))
    {
        pl->unk44A = 0;
        Sound_call(0x8F, 0, 0);
        if (!func_800406A8(pl))
        {
            pl->routine_1             = 0;
            *(uint16 *)&pl->routine_2 = 0;
        }
    }
}

void func_8003FE1C(PL_WORK *pl)
{
    uint32 pad;

    pad = pl->pad_now;
    if (func_80041158(pl) != 0 || !(pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                                           (pl->keys_124[11] | pl->keys_124[12]) | (pl->keys_124[2] | pl->keys_124[3]))))
    {
        goto reset;
    }
    if (func_80040B68(pl, 0) != 0 || func_800406A8(pl) != 0)
    {
        return;
    }
    if (func_80041044(pl) == 0)
    {
        if (func_800403D4(pl, 0) != 0 || func_80040468(pl, 0) != 0 || func_80040380(pl) != 0)
        {
            return;
        }
        if (pl->unk174 & 0xC0)
        {
            goto check;
        }
        if (func_800404FC(pl, 0) != 0)
        {
            return;
        }
    }
    if (!(pl->unk174 & 0xC0) && pl->unk177 == 0)
    {
        if (func_800402C4(pl) != 0 || func_80040630(pl, 0) != 0 || func_8004030C(pl, 0) != 0)
        {
            return;
        }
    }
check:
    if (pad & (pl->keys_124[2] | pl->keys_124[3]))
    {
        return;
    }
reset:
    pl->routine_1             = 0;
    *(uint16 *)&pl->routine_2 = 0;
}

void func_8003FFA8(void)
{
}

void func_8003FFB0(PL_WORK *pl)
{
    uint32 pad;
    sint32 mask;

    pad = pl->pad_now;
    if (!(pad & (pl->keys_124[10] | (pl->keys_124[0] | pl->keys_124[1] | (pl->keys_124[4] | pl->keys_124[5])) |
                 (pl->keys_124[11] | pl->keys_124[12]) | (pl->keys_124[6] | pl->keys_124[7]))) ||
        func_80040B68(pl, 0) != 0 ||
        (func_800406A8(pl) == 0 && func_800402C4(pl) == 0 && func_8004030C(pl, 0) == 0 && func_800404FC(pl, 0) == 0 &&
         ((mask = pl->keys_124[6] | pl->keys_124[7], (pad & mask) == mask) || !(pl->keys_124[8] & pad))))
    {
        pl->routine_1             = 0;
        *(uint16 *)&pl->routine_2 = 0;
    }
}

void func_800400B8(PL_WORK *pl)
{
    if (func_80040818(pl))
    {
        return;
    }
    if (pl->field_74 == 0 && pl->routine_2 == 1)
    {
        if (func_80040710(pl))
        {
            return;
        }
    }
    if ((sint8)pl->unk112 != 2)
    {
        func_80040B68(pl, 2);
    }
}

void func_80040130(void)
{
}

void func_80040138(void)
{
}

void func_80040140(PL_WORK *pl)
{
    if (pl->routine_2 == 2)
    {
        func_80040764(pl);
    }
}

void func_80040170(void)
{
}

void func_80040178(PL_WORK *pl)
{
    sint32 y;
    sint32 top;

    if (pl->routine_2 == 1)
    {
        y   = pl->pos.vy;
        top = Obj_ceiling_height_get((MODEL_WORK *)pl) - 0x20;
        if (top - pl->hit_78->max_A < y)
        {
            pl->routine_1             = 7;
            *(uint16 *)&pl->routine_2 = 4; // routine_2 = 4, routine_3 = 0
            pl->field_74 = pl->field_75 = 1;
            pl->spd.vx                  = -0x2A;
            pl->spd.vy                  = 0;
            pl->spd.vz                  = 0;
            Pl00_shot_enable_on(pl);
            key_seq_set(pl, 0x12, 0, 1);
        }
    }
}

void func_80040224(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    func_80040B68(pl, 0);
    if (Game_work.unk083 != 1 && !(pl->keys_124[14] & pad))
    {
        pl->routine_1             = 0;
        *(uint16 *)&pl->routine_2 = 0;
        func_800394AC();
        pl->val_108 = 0;
    }
}

void func_80040294(void)
{
}

void func_8004029C(void)
{
}

void func_800402A4(void)
{
}

void func_800402AC(void)
{
}

void func_800402B4(void)
{
}

void func_800402BC(void)
{
}

sint32 func_800402C4(PL_WORK *pl)
{
    if (pl->pad_now & pl->keys_124[0])
    {
        if (pl->pad_now & pl->keys_124[8])
        {
            pl->routine_1             = 1;
            *(uint16 *)&pl->routine_2 = 0;
            return 1;
        }
    }
    return 0;
}

sint32 func_8004030C(PL_WORK *pl, sint32 arg)
{
    uint16 pad;

    if (Scene_work.unk00 != 0 || arg == 0)
    {
        pad = pl->pad_now;
    }
    else
    {
        pad = pl->pad_on;
    }
    if (pad & pl->keys_124[1])
    {
        if (pad & pl->keys_124[8])
        {
            pl->routine_1             = 1;
            *(uint16 *)&pl->routine_2 = 0x100;
            return 1;
        }
    }
    return 0;
}

sint32 func_80040380(PL_WORK *pl)
{
    uint8 tmp;

    if (pl->pad_now & pl->keys_124[0])
    {
        if (!(pl->pad_now & pl->keys_124[8]))
        {
            tmp                       = pl->unk112;
            pl->routine_1             = 2;
            *(uint16 *)&pl->routine_2 = 0;
            pl->unk112                = 0;
            pl->unk113                = tmp;
            return 1;
        }
    }
    return 0;
}

sint32 func_800403D4(PL_WORK *pl, sint32 arg)
{
    uint16 pad;
    uint16 first;
    uint16 second;
    uint16 mask;
    uint8 tmp;

    if (Scene_work.unk00 != 0 || arg == 0)
    {
        pad = pl->pad_now;
    }
    else
    {
        pad = pl->pad_on;
    }
    first  = pl->keys_124[4];
    second = pl->keys_124[5];
    mask   = first | second;
    if ((pad & mask) == mask)
    {
        return 0;
    }
    if (pad & first)
    {
        if (!(pad & pl->keys_124[8]))
        {
            tmp                       = pl->unk112;
            pl->routine_1             = 2;
            *(uint16 *)&pl->routine_2 = 0;
            pl->unk112                = 1;
            pl->unk113                = tmp;
            return 1;
        }
    }
    return 0;
}

sint32 func_80040468(PL_WORK *pl, sint32 arg)
{
    uint16 pad;
    uint16 first;
    uint16 second;
    uint16 mask;
    uint8 tmp;

    if (Scene_work.unk00 != 0 || arg == 0)
    {
        pad = pl->pad_now;
    }
    else
    {
        pad = pl->pad_on;
    }
    first  = pl->keys_124[4];
    second = pl->keys_124[5];
    mask   = first | second;
    if ((pad & mask) == mask)
    {
        return 0;
    }
    if (pad & second)
    {
        if (!(pad & pl->keys_124[8]))
        {
            tmp                       = pl->unk112;
            pl->routine_1             = 2;
            *(uint16 *)&pl->routine_2 = 0;
            pl->unk112                = 3;
            pl->unk113                = tmp;
            return 1;
        }
    }
    return 0;
}

sint32 func_800404FC(PL_WORK *pl, sint32 arg)
{
    uint16 pad;
    uint8 tmp;

    if (Scene_work.unk00 != 0 || arg == 0)
    {
        pad = pl->pad_now;
    }
    else
    {
        pad = pl->pad_on;
    }
    if (pad & pl->keys_124[1])
    {
        if (!(pad & pl->keys_124[8]))
        {
            tmp                       = pl->unk112;
            pl->routine_1             = 2;
            *(uint16 *)&pl->routine_2 = 0;
            pl->unk112                = 2;
            pl->unk113                = tmp;
            return 1;
        }
    }
    return 0;
}

sint32 func_80040574(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    if ((pad & pl->keys_124[8]) && (pl->unk16B & 2))
    {
        pl->unk44A++;
        if (pl->unk44A >= 9 && pl->unk44B == 0)
        {
            pl->routine_1             = 3;
            *(uint16 *)&pl->routine_2 = 0;
            return 1;
        }
        return 0;
    }
    pl->unk44A = 0;
    return 0;
}

sint32 func_800405F4(PL_WORK *pl)
{
    if (pl->pad_now & (pl->keys_124[2] | pl->keys_124[3]))
    {
        pl->routine_1             = 4;
        *(uint16 *)&pl->routine_2 = 0;
        return 1;
    }
    return 0;
}

sint32 func_80040630(PL_WORK *pl, sint32 arg)
{
    uint16 pad;

    if (Scene_work.unk00 != 0 || arg == 0)
    {
        pad = pl->pad_now;
    }
    else
    {
        pad = pl->pad_on;
    }
    if (pad & pl->keys_124[8])
    {
        if (pad & (pl->keys_124[6] | pl->keys_124[7]))
        {
            pl->routine_1             = 6;
            *(uint16 *)&pl->routine_2 = 0;
            return 1;
        }
    }
    return 0;
}

sint32 func_800406A8(PL_WORK *pl)
{
    if (pl->pad_on & pl->keys_124[10])
    {
        pl->routine_1             = 7;
        *(uint16 *)&pl->routine_2 = 0;
        return 1;
    }
    return 0;
}

sint32 func_800406DC(PL_WORK *pl)
{
    if (pl->pad_on & pl->keys_124[10])
    {
        pl->routine_1             = 8;
        *(uint16 *)&pl->routine_2 = 0;
        return 1;
    }
    return 0;
}

sint32 func_80040710(PL_WORK *pl)
{
    uint16 hit;

    hit = pl->pad_now & (pl->keys_124[2] | pl->keys_124[3]);
    if (hit == pl->keys_124[2])
    {
        pl->routine_1             = 9;
        *(uint16 *)&pl->routine_2 = 0;
        return 1;
    }
    if (hit == pl->keys_124[3])
    {
        pl->routine_1             = 9;
        *(uint16 *)&pl->routine_2 = 0x100;
        return 1;
    }
    return 0;
}

sint32 func_80040764(PL_WORK *pl)
{
    uint16 pad;
    uint16 hit;
    sint32 right_none;
    sint32 hit_none;

    pad = pl->pad_now;
    if (pl->pad_on & pl->keys_124[10])
    {
        right_none = (pad & (pl->keys_124[3] | pl->keys_124[5])) == 0;
        hit        = pad & (pl->keys_124[2] | pl->keys_124[4]);
        hit_none   = hit == 0;
        if (right_none != hit_none)
        {
            if (hit != 0)
            {
                pl->routine_1             = 9;
                *(uint16 *)&pl->routine_2 = 0;
            }
            else
            {
                pl->routine_1             = 9;
                *(uint16 *)&pl->routine_2 = 0x100;
            }
        }
        else if (rand() & 1)
        {
            pl->routine_1             = 9;
            *(uint16 *)&pl->routine_2 = 0;
        }
        else
        {
            pl->routine_1             = 9;
            *(uint16 *)&pl->routine_2 = 0x100;
        }
        pl->unk168 = 0;
        pl->unk169 = 0;
        return 1;
    }
    return 0;
}

// Each of the four arms computes and stores the stepped coordinate itself (GCC merges the
// identical tails, and the longer chain makes it load hit_78 before the coordinate).
sint32 func_80040818(PL_WORK *pl)
{
    SVECTOR from;
    SVECTOR to;
    SVECTOR step;
    sint32 y;
    sint32 floor;
    sint32 dir;
    sint32 raw;
    sint32 off;
    uint16 x;
    sint32 h;
    uint16 edge;

    to   = pl->pos;
    from = to;
    if (pl->field_74 == 0 || pl->spd.vy <= 0)
    {
        return 0;
    }
    y = pl->pos.vy;
    h = Obj_ceiling_height_get((MODEL_WORK *)pl) - 0x30;
    if (h - pl->hit_78->max_A < y)
    {
        return 0;
    }
    off = func_8004976C(pl);
    raw = (pl->ang.vy - pl->unk116 + 0x200) >> 10;
    dir = raw & 3;
    if (raw & 1)
    {
        from.vz += pl->hit_78->min_4;
        off -= D_1F8000C0.vx;
        to.vz += pl->hit_78->max_6;
        step.vx = off;
        step.vz = 0;
        if (raw & 2)
        {
            edge = pl->hit_78->max_2;
            x    = to.vx;
            x++;
            x += edge + off;
            from.vx = to.vx = x;
        }
        else
        {
            edge = pl->hit_78->min_0;
            x    = to.vx;
            x--;
            x += edge + off;
            from.vx = to.vx = x;
        }
    }
    else
    {
        from.vx += pl->hit_78->min_0;
        off -= D_1F8000C0.vz;
        to.vx += pl->hit_78->max_2;
        step.vx = 0;
        step.vz = off;
        if (raw & 2)
        {
            edge = pl->hit_78->max_6;
            x    = to.vz;
            x++;
            x += edge + off;
            from.vz = to.vz = x;
        }
        else
        {
            edge = pl->hit_78->min_4;
            x    = to.vz;
            x--;
            x += edge + off;
            from.vz = to.vz = x;
        }
    }
    if (ABS(off) > 0x40)
    {
        return 0;
    }
    from.vy -= 0x98;
    to.vy -= 0x98;
    floor = func_80048EA4(&from, 0, 0, pl->work_id);
    if (floor != func_80048EA4(&to, 0, 0, pl->work_id))
    {
        return 0;
    }
    if (floor < pl->pos.vy - 0x68 && pl->pos.vy - 0x98 < floor)
    {
        pl->pos.vx += step.vx;
        pl->pos.vz += step.vz;
        pl->pos.vy   = floor + 0x98;
        pl->pos_l.vy = (floor + 0x98) << 16;
        pl->ang.vy   = dir << 10;
        pl->unk116   = 0;
        pl->unk112   = 0;
        func_80039A38(&D_80097D9C);
        pl->routine_1             = 0xD;
        *(uint16 *)&pl->routine_2 = dir << 8; // routine_2 = 0, routine_3 = dir
        return 1;
    }
    return 0;
}

sint32 func_80040AEC(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    if (Game_work.unk083 == 1 || (pad & pl->keys_124[14]))
    {
        pl->routine_1             = 14;
        *(uint16 *)&pl->routine_2 = 0;
        return 1;
    }
    return 0;
}

sint32 func_80040B34(PL_WORK *pl)
{
    if (pl->pad_now & pl->keys_124[13])
    {
        pl->routine_1             = 5;
        *(uint16 *)&pl->routine_2 = 0;
        return 1;
    }
    return 0;
}

sint32 func_80040B68(PL_WORK *pl, sint32 arg)
{
    sint16 mode;
    uint32 pad;
    uint8 cond2;
    uint8 cond1;

    mode  = arg;
    pad   = pl->pad_now;
    cond2 = D_80089A84[pl->weapon_right_no].flag_4;
    cond1 = D_80089A84[pl->unk171].flag_4;
    if (!(pl->unk174 & 0xC0))
    {
        if ((pl->unk177 == 1 && ((pl->keys_124[11] & pad) || (pl->unk176 & 3) == 2) && (pl->unk175 & 5) == 5 &&
             func_80040E00(pl, 0, mode, cond1) != 0) ||
            (pl->unk177 == 2 && ((pl->keys_124[12] & pad) || (pl->unk176 & 3) == 1) && (pl->unk175 & 3) == 3 && func_80037440() != 0 &&
             func_80040E00(pl, 2, mode, cond2) != 0))
        {
            *(uint16 *)&pl->unk178 = 1; // unk178 = 1, unk179[0] = 0
            pl->unk177             = 0;
            pl->unk176             = 0;
            return 1;
        }
        if (((pl->keys_124[11] & pad) || (pl->unk176 & 3) == 2) && pl->rec[pl->unk171].val > 0 && (pl->unk175 & 5) == 5)
        {
            pl->unk176 = 0;
            return func_80040E00(pl, 4, mode, cond1);
        }
        if (((pl->keys_124[12] & pad) || (pl->unk176 & 3) == 1) && pl->rec[pl->weapon_right_no].val > 0 && (pl->unk175 & 3) == 3 &&
            func_80037440() != 0)
        {
            pl->unk176 = 0;
            return func_80040E00(pl, 6, mode, cond2);
        }
    }
    pl->unk176 = 0;
    return 0;
}

sint32 func_80040E00(PL_WORK *pl, sint32 arg, sint16 mode, sint16 cond)
{
    switch (mode)
    {
        case 0:
            arg++;
            break;
        case 1:
            if (cond == 0)
            {
                pl->routine_1             = 0;
                *(uint16 *)&pl->routine_2 = 0; // routine_2, routine_3
                return 0;
            }
            break;
        case 2:
            if (cond == 0)
            {
                return 0;
            }
            break;
        default:
            return 1;
    }
    func_80040E9C(pl, arg);
    return 1;
}

void func_80040E9C(PL_WORK *pl, sint16 arg)
{
    switch (arg)
    {
        case 0:
            pl->unk174 = 0x86;
            return;
        case 1:
            pl->unk174 = 0x82;
            return;
        case 2:
            pl->unk174 = 0x45;
            return;
        case 3:
            pl->unk174 = 0x41;
            return;
        case 4:
            pl->unk174  = 0x86;
            pl->set_104 = func_800423DC(pl);
            break;
        case 5:
            pl->unk174  = 0x82;
            pl->set_104 = func_800423DC(pl);
            break;
        case 6:
            pl->unk174  = 0x45;
            pl->set_104 = func_80042458(pl);
            break;
        case 7:
            pl->unk174  = 0x41;
            pl->set_104 = func_80042458(pl);
            break;
    }
    *(uint16 *)&pl->unk178 = 0; // unk178 and the byte after it
    pl->unk105             = 0;
    pl->cmd_100.b.b0       = 0;
    if (!(pl->unk174 & 4) && pl->idx_AC == pl->old_idx_AD)
    {
        key_seq_set(pl, pl->set_104, 0, 1);
    }
}

sint32 func_80040FA8(PL_WORK *pl)
{
    sint32 type;

    type = pl->unk174 & 0xC0;
    if (type == 0 || (type == 0x40 && pl->cmd_100.b.b0 > D_80089A84[pl->weapon_right_no].key_0) ||
        (type == 0x80 && pl->cmd_100.b.b0 > D_80089A84[pl->unk171].key_0))
    {
        return 1;
    }
    return 0;
}

sint32 func_80041044(PL_WORK *pl)
{
    uint16 pad;

    pad = pl->pad_now;
    if (((pad & pl->keys_124[12]) && D_80089A84[pl->weapon_right_no].flag_4 == 0) ||
        ((pad & pl->keys_124[11]) && D_80089A84[pl->unk171].flag_4 == 0))
    {
        return 1;
    }
    return 0;
}

sint32 func_800410D4(PL_WORK *pl)
{
    sint32 type;

    type = pl->unk174 & 0xC0;
    if ((type == 0x40 && D_80089A84[pl->weapon_right_no].flag_5 == 0) || (type == 0x80 && D_80089A84[pl->unk171].flag_5 == 0))
    {
        return 1;
    }
    return 0;
}

sint32 func_80041158(PL_WORK *pl)
{
    sint32 type;

    type = pl->unk174 & 0xC0;
    if ((type == 0x40 && D_80089A84[pl->weapon_right_no].flag_6 == 0) || (type == 0x80 && D_80089A84[pl->unk171].flag_6 == 0))
    {
        return 1;
    }
    return 0;
}

// While keys_124[9] is held (and field_74 is clear), finds the nearest live object of the model
// pools and of D_800BF118 whose box_10 lies in front of the player (func_800414F0): within 0xD0,
// it goes to obj_184 (distance in dist_182) and the answer is 1.
sint32 front_box_search(PL_WORK *pl)
{
    SVECTOR pos;
    SVECTOR ang;
    WORK_3C0 *wp3c0;
    WORK_5A4 *wp5a4;
    SHL_WORK *shl;
    WORK_50 *wp50;
    MODEL_WORK *best_wp;
    uint32 best;
    uint32 dist;
    sint32 i;
    uint16 pad;

    best_wp = NULL;
    if (func_8003A13C() != 0 || (pl->unk174 & 0xC0) || pl->unk177 != 0)
    {
        return 0;
    }
    pad            = pl->pad_now;
    ang.vz         = 0;
    ang.vy         = 0;
    ang.vx         = 0;
    best           = 0x7FFF;
    Scratch_pl_sin = rsin(pl->ang.vy);
    Scratch_pl_cos = rcos(pl->ang.vy);
    if ((pad & pl->keys_124[9]) && pl->field_74 == 0)
    {
        for (wp3c0 = D_8009F108, i = 0; i < 16; i++, wp3c0++)
        {
            if ((wp3c0->be_flag & (MOVE | TRANS)) == 3 && wp3c0->box_10 != NULL)
            {
                dist = func_800414F0(pl, &wp3c0->pos, &wp3c0->ang, wp3c0->box_10);
                if (dist != 0 && dist < best)
                {
                    best    = dist;
                    best_wp = (MODEL_WORK *)wp3c0;
                }
            }
        }
        for (wp5a4 = D_800C3580, i = 0; i < 4; i++, wp5a4++)
        {
            if ((wp5a4->be_flag & (MOVE | TRANS)) == 3 && wp5a4->box_10 != NULL)
            {
                dist = func_800414F0(pl, &wp5a4->pos, &wp5a4->ang, wp5a4->box_10);
                if (dist != 0 && dist < best)
                {
                    best    = dist;
                    best_wp = (MODEL_WORK *)wp5a4;
                }
            }
        }
        for (shl = D_8009CF88, i = 0; i < 32; i++, shl++)
        {
            if ((shl->be_flag & (MOVE | TRANS)) == 3 && shl->id < 0x80 && shl->box_10 != NULL)
            {
                dist = func_800414F0(pl, &shl->pos, &shl->ang, shl->box_10);
                if (dist != 0 && dist < best)
                {
                    best    = dist;
                    best_wp = (MODEL_WORK *)shl;
                }
            }
        }
        for (wp50 = D_800BF118, i = 0; i < 32; i++, wp50++)
        {
            if ((wp50->be_flag & (MOVE | TRANS)) == 3 && wp50->box_10 != NULL)
            {
                if (wp50->be_flag & MODEL)
                {
                    pos.vx = wp50->efc.model.pos.vx;
                    pos.vy = wp50->efc.model.pos.vy;
                    pos.vz = wp50->efc.model.pos.vz;
                }
                else
                {
                    pos.vx = wp50->efc.sprite.pos[0];
                    pos.vy = wp50->efc.sprite.pos[1];
                    pos.vz = wp50->efc.sprite.pos[2];
                }
                dist = func_800414F0(pl, &pos, &ang, wp50->box_10);
                if (dist != 0 && dist < best)
                {
                    best    = dist;
                    best_wp = (MODEL_WORK *)wp50;
                }
            }
        }
        if (best < 0xD0)
        {
            pl->dist_182 = best;
            pl->obj_184  = best_wp;
            return 1;
        }
    }
    pl->obj_184 = NULL;
    return 0;
}

// Tests whether box (at pos, rotated by ang) lies at one of three points in front of the player
// (0x50, 0x80 and 0xB0 ahead, each with a wider margin). Answers the XZ distance to the box's
// center, or 0 if none.
sint32 func_800414F0(PL_WORK *pl, SVECTOR *pos, SVECTOR *ang, HIT_ENT *box)
{
    SVECTOR probe;
    SVECTOR hit;
    VECTOR center;
    VECTOR origin;
    MATRIX mtx;
    sint32 i;
    sint32 margin;
    sint32 dist;
    sint32 min_x;
    sint32 max_x;
    sint32 min_z;
    sint32 max_z;

    origin.vx = pos->vx << 16;
    center.vx = origin.vx + ((box->min_0 + box->max_2) << 15);
    origin.vz = pos->vz << 16;
    center.vz = origin.vz + ((box->min_4 + box->max_6) << 15);
    center.vy = origin.vy = pos->vy << 16;
    min_x                 = box->min_0 - (box->min_0 + box->max_2) / 2;
    max_x                 = box->max_2 - (box->min_0 + box->max_2) / 2;
    min_z                 = box->min_4 - (box->min_4 + box->max_6) / 2;
    max_z                 = box->max_6 - (box->min_4 + box->max_6) / 2;
    RotMatrixYXZ(ang, &mtx);
    func_800301A8(&mtx, &center, &origin);
    for (i = 0, margin = 0xC, dist = 0x50; i < 3; margin += 0xC, i++, dist += 0x30)
    {
        probe.vx = pl->pos.vx - (Scratch_pl_sin * dist) / 0x1000;
        probe.vz = pl->pos.vz - (Scratch_pl_cos * dist) / 0x1000;
        probe.vy = pl->pos.vy;
        hit.vx   = center.vx >> 16;
        hit.vy   = center.vy >> 16;
        hit.vz   = center.vz >> 16;
        if (hit.vx >= probe.vx - margin - max_x && hit.vx <= probe.vx + margin - min_x && hit.vz >= probe.vz - margin - max_z &&
            hit.vz <= probe.vz + margin - min_z && hit.vy >= probe.vy - box->max_A && hit.vy <= probe.vy - box->min_8)
        {
            return Distance_xz(&pl->pos, &hit);
        }
    }
    return 0;
}

// Takes the hits gathered in owner_188 this frame: the damage (low 24 bits of hit_0, less
// unk16C quarters) comes off life, unk71 records the side the hit came from (1-4, from vec_8),
// and the player enters state 0xB or 0xC (func_80041A44), or 0xC once unk73 builds up.
void damage_check(PL_WORK *pl)
{
    uint32 flags;
    sint32 damage;
    uint32 dir;
    SVECTOR *from;

    if (Scene_work.unk00 != 0)
    {
        return;
    }
    flags  = pl->owner_188.hit_0;
    damage = flags & 0xFFFFFF;
    from   = &pl->owner_188.vec_8;
    if (damage != 0 || (flags & 0x1000000))
    {
        if (flags & 0xFFFFFF)
        {
            damage -= (damage * pl->unk16C) >> 2;
            if (damage == 0)
            {
                damage = 1;
            }
        }
        if ((sint8)pl->unk71 <= 0)
        {
            if ((sint8)pl->unk71 == 0)
            {
                if (from->pad != 0)
                {
                    dir = Angle_xz_svector(from, &pl->pos);
                }
                else
                {
                    dir = ratan2(from->vx, from->vz) + 0x800;
                }
                pl->unk71 = (((dir - pl->ang.vy + pl->unk116 + 0x200) & 0xFFF) >> 10) + 1;
            }
            else if ((pl->unk71 & 0x7F) == 1)
            {
                pl->unk116 += 0x800;
            }
            switch (pl->unk71 & 0x7F)
            {
                case 2:
                    pl->unk112 = (pl->unk112 + 1) & 3;
                    pl->unk116 += 0x400;
                    break;
                case 4:
                    pl->unk112 = (pl->unk112 - 1) & 3;
                    pl->unk116 -= 0x400;
                    break;
            }
        }
        pl->unk174 = 0;
        pl->unk177 = 0;
        if (flags & 0x1000000)
        {
            func_8005D8C4(damage);
        }
        if (flags & 0x40000000)
        {
            func_8005D98C();
        }
        if (func_8005D8C4(0) != 0 || func_8005D938() != 0)
        {
            if (pl->life > 0)
            {
                pl->life -= damage;
                if (pl->life <= 0)
                {
                    pl->life = 0;
                    func_8005D98C();
                }
            }
            else
            {
                pl->life -= damage;
            }
            pl->unk73 += damage;
            if ((sint8)pl->unk73 > (pl->unk16A + 1) * 16)
            {
                pl->routine_1 = 0xC;
                pl->routine_2 = 1;
            }
            else
            {
                func_80041A44(pl, flags);
            }
        }
        else
        {
            if (pl->life > 0)
            {
                func_8005D8C4(damage);
            }
            else
            {
                func_8005D98C();
            }
            func_80041A44(pl, flags);
        }
        pl->ang.vy = (sint16)(pl->ang.vy - 0x80) + (rand() & 0x100);
        if ((pl->unk71 & 0x7F) == 1)
        {
            pl->routine_3 = 1;
        }
        else
        {
            pl->routine_3 = 0;
        }
    }
    else if ((uint8)(pl->routine_1 - 0xB) >= 2)
    {
        pl->unk73 -= 4;
        if ((sint8)pl->unk73 < 0)
        {
            pl->unk73 = 0;
        }
    }
}

void func_80041A44(PL_WORK *pl, uint32 flags)
{
    uint8 state;

    if (pl->field_74 != 0 || (flags & 0x41000000) || pl->life <= 0)
    {
        state = 0xC;
    }
    else
    {
        if (pl->routine_1 == 0xB && pl->routine_2 < 2)
        {
            return;
        }
        state = 0xB;
    }
    pl->routine_1 = state;
    pl->routine_2 = 0;
}

void func_80041AB0(PL_WORK *pl)
{
    pl->old_ang    = pl->ang;
    pl->old_idx_AD = pl->idx_AC;
    pl->old_life   = pl->life;
    pl->field_75   = pl->field_74;
    pl->unk77      = pl->field_76;
    Obj_map_push_out((MODEL_WORK *)pl);
    pl->old   = pl->pos;
    pl->old_l = pl->pos_l;
    if (pl->routine_1 == 0)
    {
        Game_work.routine_0 = 9;
        Game_work.routine_1 = 0;
        pl->routine_1++;
    }
}

void func_80041B8C(PL_WORK *pl)
{
    uint8 cur;
    uint32 idx;

    switch (pl->routine_1)
    {
        case 0:
            pl->svec_438 = pl->pos;
            pl->pos_428  = pl->pos_l;
            pl->ang_440  = pl->ang;
            pl->unk448   = 0xFF;
            // fall through
        case 1:
            Pl00_shot_enable_off(pl);
            pl->flags_BD  = 0x40;
            pl->routine_1 = 2;
            // fall through
        case 2:
            pl->old        = pl->pos;
            pl->old_l      = pl->pos_l;
            pl->old_ang    = pl->ang;
            pl->old_idx_AD = pl->idx_AC;
            pl->pos        = pl->svec_438;
            pl->pos_l      = pl->pos_428;
            pl->ang        = pl->ang_440;
            idx            = pl->unk448;
            pl->flags_BD &= 0xF7;
            if (idx != 0xFF)
            {
                cur = pl->idx_AC;
                if (cur != idx)
                {
                    key_seq_set(pl, idx, 0, 1);
                    pl->unk448 = 0xFF;
                }
                else if (pl->cmd_A4.b.ctl == -1)
                {
                    key_seq_set(pl, cur, 0, 1);
                    pl->unk448 = 0xFF;
                }
            }
            if (pl->cmd_A4.b.b2 & 0x80)
            {
                Sound_call(0x90, 0, 0);
            }
            break;
        case 3:
            Pl00_shot_enable_on(pl);
            *(uint32 *)&pl->routine_0 = 1; // routine_0 = 1, routine_1 ... routine_3 = 0
            pl->flags_BD              = 8;
            break;
    }
    func_80051BAC((MODEL_WORK *)pl);
}

// Switches the player to keyframe sequence idx at step b0 (force: even if it is already running).
// Between sequences 1 and 0xC, the current step is converted instead (doubled or halved, offset
// by 4, wrapping at 0x20).
void key_seq_set(PL_WORK *pl, uint8 idx, sint16 b0, uint8 force)
{
    if (force)
    {
        pl->old_idx_AD = 0xFF;
    }
    else if (idx == pl->old_idx_AD)
    {
        return;
    }
    switch (idx)
    {
        case 0xC:
            if (pl->old_idx_AD == 1)
            {
                b0 = pl->cmd_A4.b.b0 * 2 + 4;
                if (b0 >= 0x20)
                {
                    b0 = pl->cmd_A4.b.b0 * 2 - 0x1C;
                }
            }
            break;
        case 1:
            if (pl->old_idx_AD == 0xC)
            {
                b0 = pl->cmd_A4.b.b0 - 4;
                if (b0 < 0)
                {
                    b0 = pl->cmd_A4.b.b0 + 0x1C;
                }
                b0 = b0 >> 1;
            }
            break;
    }
    pl->idx_AC      = idx;
    pl->cmd_A4.b.b0 = b0;
}

void func_80041E90(PL_WORK *pl, sint16 x, sint16 y, sint16 z)
{
    pl->ang.vy -= pl->unk116;
    Obj_pos_set((MODEL_WORK *)pl, x, y, z);
    pl->ang.vy += pl->unk116;
}

// Moves val_108 with keys_124[0] or [1] held (func_80041F54 tests keys_124[1] when
// Game_work.unk055 is set, [0] otherwise); with neither held, step_10C stops.
void func_80041EF4(PL_WORK *pl, sint32 spd, sint32 max)
{
    uint16 first;
    uint16 second;

    first  = pl->keys_124[0];
    second = pl->keys_124[1];
    if (pl->pad_now & (first | second))
    {
        func_80041F54(pl, spd, max, Game_work.unk055 ? second : first);
    }
    else
    {
        pl->step_10C = 0;
    }
}

// As func_80042154, for val_108 (kept within -0x200..0x200) instead of the facing angle.
void func_80041F54(PL_WORK *pl, sint32 spd, sint32 max, uint16 mask)
{
    if (pl->pad_now & mask)
    {
        if (pl->step_10C < 0)
        {
            pl->step_10C = 0;
        }
        else
        {
            pl->step_10C += spd;
            if (pl->step_10C > max)
            {
                pl->step_10C = max;
            }
        }
        pl->val_108 += pl->step_10C;
        if (pl->val_108 > 0x200)
        {
            pl->val_108 = 0x200;
        }
    }
    else
    {
        if (pl->step_10C > 0)
        {
            pl->step_10C = 0;
        }
        else
        {
            pl->step_10C -= spd;
            if (pl->step_10C < -max)
            {
                pl->step_10C = -max;
            }
        }
        pl->val_108 += pl->step_10C;
        if (pl->val_108 < -0x200)
        {
            pl->val_108 = -0x200;
        }
    }
}

// Turns the player (func_80042154, mask keys_124[3]) while exactly one of keys_124[2] and [3] is
// held; otherwise turn_B4 stops and it answers 0.
sint32 func_80042044(PL_WORK *pl, sint32 spd, sint32 max)
{
    sint32 ret;
    uint32 both;
    uint32 held;

    both = pl->keys_124[2] | pl->keys_124[3];
    held = pl->pad_now & both;
    ret  = 0;
    if (held != 0 && held != both)
    {
        ret = func_80042154(pl, spd, max, pl->keys_124[3]);
    }
    else
    {
        pl->turn_B4 = 0;
    }
    return ret;
}

sint32 func_80042094(PL_WORK *pl, sint32 spd, sint32 max, sint32 anim)
{
    uint32 pad;
    uint16 mask_a;
    uint16 mask_b;
    sint32 ret;

    ret    = 0;
    pad    = pl->pad_now;
    mask_a = pl->keys_124[3] | pl->keys_124[5];
    mask_b = pl->keys_124[2] | pl->keys_124[4];
    if (!(pad & mask_a) != !(pad & mask_b))
    {
        ret = func_80042154(pl, spd, max, mask_a);
        if (anim)
        {
            // Both arms make the same call in the original too.
            if (pad & pl->keys_124[3])
            {
                key_seq_set(pl, 0xD, 0, 0);
            }
            else
            {
                key_seq_set(pl, 0xD, 0, 0);
            }
        }
    }
    else
    {
        if (anim)
        {
            key_seq_set(pl, 0, 0, 0);
        }
        pl->turn_B4 = 0;
    }
    return ret;
}

// Turns the player: while a key of mask is held, turn_B4 grows by spd up to max (answers 1),
// otherwise it falls by spd down to -max (answers 2). A reversal stops the turn for one frame.
sint32 func_80042154(PL_WORK *pl, sint32 spd, sint32 max, sint32 mask)
{
    sint32 ret;

    if (pl->pad_now & mask)
    {
        ret = 1;
        if (pl->turn_B4 < 0)
        {
            pl->turn_B4 = 0;
        }
        else
        {
            pl->turn_B4 += spd;
            if (pl->turn_B4 > max)
            {
                pl->turn_B4 = max;
            }
            pl->turn_acc_B6 = spd;
        }
    }
    else
    {
        ret = 2;
        if (pl->turn_B4 > 0)
        {
            pl->turn_B4 = 0;
        }
        else
        {
            pl->turn_B4 -= spd;
            if (pl->turn_B4 < -max)
            {
                pl->turn_B4 = -max;
            }
            pl->turn_acc_B6 = -spd;
        }
    }
    pl->ang.vy = (pl->ang.vy + pl->turn_B4) & 0xFFF;
    return ret;
}

sint32 func_80042208(void)
{
    if (Player_work[0].life >= 0)
    {
        Player_work[0].unk449 = 1;
        return 1;
    }
    return 0;
}

sint32 func_80042238(PL_WORK *pl)
{
    pl->unk449 = -1;
    pl->flags_BD |= 0x40;
    if (pl->be_flag & MOVE)
    {
        if (pl->routine_0 == 1)
        {
            switch (pl->routine_1)
            {
                case 14:
                    if (Game_work.unk083 != 0)
                    {
                        case 0:
                            if (func_8004324C(pl) == 0)
                            {
                                goto reset;
                            }
                    }
                    // fall through
                default:
                    // One word compare of routine_1 == 0xD and routine_2 == 2
                    if ((*(uint32 *)&pl->routine_0 & 0xFFFF00) == 0x20D00)
                    {
                        pl->routine_2 = 6;
                    }
            }
        }
        if (pl->routine_0 != 3)
        {
            return 0;
        }
    }
reset:
    pl->turn_B4 = 0;
    Sound_key_off_voice(0x16);
    Sound_key_off_voice(0x17);
    return 1;
}

void func_80042314(PL_WORK *pl)
{
    func_8002D004(pl, 0, 0);
    pl->unk449                         = 0;
    pl->unk111                         = 0;
    pl->unk71                          = 0;
    pl->unk73                          = 0;
    pl->owner_188.hit_0                = 0;
    pl->owner_188.mask_4               = 0;
    *(uint32 *)&pl->owner_188.vec_8.vx = 0; // vx, vy
    *(uint32 *)&pl->owner_188.vec_8.vz = 0; // vz, pad
    pl->unk168                         = 0;
    pl->unk169                         = 0;
    if (pl->be_flag & MOVE)
    {
        pl->be_flag = MOVE | TRANS;
        pl->flags   = 3;
        if (pl->routine_0 == 3)
        {
            pl->routine_1 = 3;
            return;
        }
    }
    pl->flags_BD = 8;
}

void Pl00_shot_enable_off(PL_WORK *pl)
{
    pl->unk174 = 0;
    pl->unk177 = 0;
    pl->unk175 &= ~1;
    pl->set_104      = pl->idx_AC;
    pl->cmd_100.b.b0 = pl->cmd_A4.b.b0;
}

void Pl00_shot_enable_on(PL_WORK *pl)
{
    pl->unk175 |= 1;
}

sint32 func_800423DC(PL_WORK *pl)
{
    switch (pl->routine_1)
    {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
            break;
        case 2:
        case 8:
            switch ((sint8)pl->unk112) // lb here; the state checks copy it with lbu
            {
                case 0:
                    return 0x61;
                case 1:
                    return 0x63;
                case 3:
                    return 0x62;
            }
            break;
    }
    return 0x60;
}

sint32 func_80042458(PL_WORK *pl)
{
    switch (pl->routine_1)
    {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
            break;
        case 2:
        case 8:
            switch ((sint8)pl->unk112) // lb here; the state checks copy it with lbu
            {
                case 0:
                    return 0x41;
                case 1:
                    return 0x43;
                case 3:
                    return 0x42;
            }
            break;
    }
    return 0x40;
}

void func_800424D4(PL_WORK *pl, W48_80_WORK *wp)
{
    wp->be_flag = MOVE | TRANS | MODEL;
    wp->id      = 0x80;
    wp->type    = 2;
    wp->pos_38  = pl->joint_pos[pl->routine_2 >> 1];
}

void func_80042528(PL_WORK *pl, W48_83_WORK *wp, sint16 n)
{
    wp->be_flag = MOVE | TRANS;
    wp->id      = 0x83;
    wp->type    = 0;
    switch (n)
    {
        case 0:
            wp->pos_1C[0] = pl->pos.vx;
            wp->pos_1C[1] = pl->pos.vy + 0x10;
            wp->pos_1C[2] = pl->pos.vz;
            break;
        case 1:
            wp->pos_1C[0] = pl->joint_pos[14].vx;
            wp->pos_1C[1] = pl->joint_pos[14].vy + 0x10;
            wp->pos_1C[2] = pl->joint_pos[14].vz;
            break;
        case 2:
            wp->pos_1C[0] = pl->joint_pos[11].vx;
            wp->pos_1C[1] = pl->joint_pos[11].vy + 0x10;
            wp->pos_1C[2] = pl->joint_pos[11].vz;
            break;
    }
}
