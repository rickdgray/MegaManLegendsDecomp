#include "common.h"
#include "code_80037534.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "sub_scrn.h"

// Pool common (see sub_scrn.h): Map_screen_init stores routine_0 through $gp.
MAP_SCREEN_WORK Map_screen_work;

// Called only from this file
void sub_screen_sort_sub(PL_WORK *pp, sint32 d0, sint32 d1);
void sub_screen_rb_parts_calc_sub00(SUB_SCREEN_WORK *subp, sint32 d0);
void sub_screen_rb_parts_calc_sub01(SUB_SCREEN_WORK *subp, sint32 d0);
void sub_screen_status_calc(SUB_SCREEN_WORK *subp, sint32 d0);
void map_screen_set(void);
void map_cursor_set(void);

// The sub screen, each frame: the background, then the current screen.
void Sub_screen_task(void)
{
    Sub_screen_back_ground_set();
    Sub_screen_tbl[Sub_screen_work.routine_0](&Sub_screen_work);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005EC80);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005ECE0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005ED9C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005F210);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005F3D0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005F608);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005F9E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005FAE4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005FBB4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005FDE4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005FFBC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_800600CC);

void func_80060248(SUB_SCREEN_WORK *subp)
{
    subp->mode_6        = 3;
    subp->attack.now_0  = subp->attack.val_2;
    subp->attack.now_1  = subp->attack.val_5;
    subp->bullet.now_0  = subp->bullet.val_2;
    subp->bullet.now_1  = subp->bullet.val_5;
    subp->dist.now_0    = subp->dist.val_2;
    subp->dist.now_1    = subp->dist.val_5;
    subp->repeat.now_0  = subp->repeat.val_2;
    subp->repeat.now_1  = subp->repeat.val_5;
    subp->special.now_0 = subp->special.val_2;
    subp->special.now_1 = subp->special.val_5;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_800602A4);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_800605DC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_80060618);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_80060B00);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_80060C70);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_80060DB8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", sub_screen_cancel_check);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", sub_screen_shift_check);

// Sorts the owned buster parts by attack level, highest first, empty entries last.
void Sub_screen_sort_attack(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].attack_level < Rock_buster_parts_tbl[sort_dist - 1].attack_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

// Sub_screen_sort_attack by energy level.
void Sub_screen_sort_energy(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].bullet_level < Rock_buster_parts_tbl[sort_dist - 1].bullet_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

// Sub_screen_sort_attack by range level.
void Sub_screen_sort_range(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].dist_level < Rock_buster_parts_tbl[sort_dist - 1].dist_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

// Sub_screen_sort_attack by rapid level.
void Sub_screen_sort_rapid(void)
{
    sint32 d0;
    sint32 d1;
    uint8 sort_src;
    uint8 sort_dist;
    PL_WORK *pp;

    pp = &Player_work[0];

    for (d0 = 0; d0 < 0x1F; d0++)
    {
        for (d1 = 0; d1 < 0x1F - d0; d1++)
        {
            if (!(sort_dist = pp->rb_parts_sort_data[d1 + 1]))
            {
                continue;
            }
            if (!(sort_src = pp->rb_parts_sort_data[d1]) ||
                Rock_buster_parts_tbl[sort_src - 1].repeat_level < Rock_buster_parts_tbl[sort_dist - 1].repeat_level)
            {
                sub_screen_sort_sub(pp, d1, d1 + 1);
            }
        }
    }
}

void sub_screen_sort_sub(PL_WORK *pp, sint32 d0, sint32 d1)
{
    uint8 sort_buff;

    sort_buff                  = pp->rb_parts_sort_data[d0];
    pp->rb_parts_sort_data[d0] = pp->rb_parts_sort_data[d1];
    pp->rb_parts_sort_data[d1] = sort_buff;
}

// The buster's levels (Player_work[0].rec[1]): the sum of its equipped parts' levels, up to
// RB_LEVEL_MAX each.
void Sub_screen_rb_parts_set(void)
{
    sint32 d0;
    sint32 d1;
    sint32 d2;
    PL_WORK *pp;

    pp = &Player_work[0];

    if (Sce_flag_test(PL_KEY_ITEM_06))
    {
        d0 = 3;
    }
    else
    {
        d0 = 2;
    }

    pp->rec[1].idx[0] = 0;
    pp->rec[1].idx[1] = 0;
    pp->rec[1].idx[2] = 0;
    pp->rec[1].idx[3] = 0;

    for (d1 = 0; d1 < d0; d1++)
    {
        if (!(d2 = pp->rb_parts_equip_data[d1]))
        {
            continue;
        }
        pp->rec[1].idx[0] += Rock_buster_parts_tbl[d2 - 1].attack_level;
        pp->rec[1].idx[1] += Rock_buster_parts_tbl[d2 - 1].bullet_level;
        pp->rec[1].idx[2] += Rock_buster_parts_tbl[d2 - 1].dist_level;
        pp->rec[1].idx[3] += Rock_buster_parts_tbl[d2 - 1].repeat_level;
    }
    if (pp->rec[1].idx[0] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[0] = RB_LEVEL_MAX;
    }
    if (pp->rec[1].idx[1] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[1] = RB_LEVEL_MAX;
    }
    if (pp->rec[1].idx[2] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[2] = RB_LEVEL_MAX;
    }
    if (pp->rec[1].idx[3] > RB_LEVEL_MAX)
    {
        pp->rec[1].idx[3] = RB_LEVEL_MAX;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", sub_screen_rb_parts_calc);

void sub_screen_rb_parts_calc_sub00(SUB_SCREEN_WORK *subp, sint32 d0)
{
    subp->attack.end_0 += Rock_buster_parts_tbl[d0].attack_level * 10;
    subp->bullet.end_0 += Rock_buster_parts_tbl[d0].bullet_level * 10;
    subp->dist.end_0 += Rock_buster_parts_tbl[d0].dist_level * 10;
    subp->repeat.end_0 += Rock_buster_parts_tbl[d0].repeat_level * 10;

    if (subp->attack.end_0 > RB_LEVEL_MAX * 10)
    {
        subp->attack.end_0 = RB_LEVEL_MAX * 10;
    }
    if (subp->bullet.end_0 > RB_LEVEL_MAX * 10)
    {
        subp->bullet.end_0 = RB_LEVEL_MAX * 10;
    }
    if (subp->dist.end_0 > RB_LEVEL_MAX * 10)
    {
        subp->dist.end_0 = RB_LEVEL_MAX * 10;
    }
    if (subp->repeat.end_0 > RB_REPEAT_LEVEL_MAX * 10)
    {
        subp->repeat.end_0 = RB_REPEAT_LEVEL_MAX * 10;
    }
}

// Same as sub_screen_rb_parts_calc_sub00, on the _1 values.
void sub_screen_rb_parts_calc_sub01(SUB_SCREEN_WORK *subp, sint32 d0)
{
    subp->attack.end_1 += Rock_buster_parts_tbl[d0].attack_level * 10;
    subp->bullet.end_1 += Rock_buster_parts_tbl[d0].bullet_level * 10;
    subp->dist.end_1 += Rock_buster_parts_tbl[d0].dist_level * 10;
    subp->repeat.end_1 += Rock_buster_parts_tbl[d0].repeat_level * 10;

    if (subp->attack.end_1 > RB_LEVEL_MAX * 10)
    {
        subp->attack.end_1 = RB_LEVEL_MAX * 10;
    }
    if (subp->bullet.end_1 > RB_LEVEL_MAX * 10)
    {
        subp->bullet.end_1 = RB_LEVEL_MAX * 10;
    }
    if (subp->dist.end_1 > RB_LEVEL_MAX * 10)
    {
        subp->dist.end_1 = RB_LEVEL_MAX * 10;
    }
    if (subp->repeat.end_1 > RB_REPEAT_LEVEL_MAX * 10)
    {
        subp->repeat.end_1 = RB_REPEAT_LEVEL_MAX * 10;
    }
}

// The gauges' end values (_0) for weapon slot d0 (Player_work[0].rec[d0]), from its levels;
// a negative d0 clears them. A table value of 0xFF is drawn as a full gauge marked "infinite".
void sub_screen_status_calc(SUB_SCREEN_WORK *subp, sint32 d0)
{
    PL_WORK *pp;

    pp = &Player_work[0];

    if (d0 < 0)
    {
        subp->attack.end_0 = subp->attack.infi_0 = 0;
        subp->bullet.end_0 = subp->bullet.infi_0 = 0;
        subp->dist.end_0 = subp->dist.infi_0 = 0;
        subp->repeat.end_0 = subp->repeat.infi_0 = 0;
        subp->special.end_0 = subp->special.infi_0 = 0;
    }
    else
    {
        subp->attack.end_0  = D_8008D7E8[D_8008DB08[d0]].attack[pp->rec[d0].idx[0]];
        subp->bullet.end_0  = D_8008D7E8[D_8008DB08[d0]].energy[pp->rec[d0].idx[1]];
        subp->dist.end_0    = D_8008D7E8[D_8008DB08[d0]].range[pp->rec[d0].idx[2]];
        subp->repeat.end_0  = D_8008D7E8[D_8008DB08[d0]].rapid[pp->rec[d0].idx[3]];
        subp->special.end_0 = D_8008D7E8[D_8008DB08[d0]].special[pp->rec[d0].sp_perform];

        if (subp->attack.end_0 == 0xFF)
        {
            subp->attack.end_0  = 88;
            subp->attack.infi_0 = 1;
        }
        else
        {
            subp->attack.infi_0 = 0;
        }
        if (subp->bullet.end_0 == 0xFF)
        {
            subp->bullet.end_0  = 88;
            subp->bullet.infi_0 = 1;
        }
        else
        {
            subp->bullet.infi_0 = 0;
        }
        if (subp->dist.end_0 == 0xFF)
        {
            subp->dist.end_0  = 88;
            subp->dist.infi_0 = 1;
        }
        else
        {
            subp->dist.infi_0 = 0;
        }
        if (subp->repeat.end_0 == 0xFF)
        {
            subp->repeat.end_0  = 88;
            subp->repeat.infi_0 = 1;
        }
        else
        {
            subp->repeat.infi_0 = 0;
        }
        if (subp->special.end_0 == 0xFF)
        {
            subp->special.end_0  = 88;
            subp->special.infi_0 = 1;
        }
        else
        {
            subp->special.infi_0 = 0;
        }
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_gauge_set);

// A stat gauge power wide at (x0, y0), and its end cap, into OT 2; an "infinite" gauge (infi, at
// full length 88) gets its label over it.
void Sub_screen_gauge_set2(sint32 x0, sint32 y0, sint32 power, sint32 infi)
{
    POLY_FT4 *ft4_buff_ptr1;
    POLY_FT4 *ft4_buff_ptr2;

    ft4_buff_ptr2 = Map_prim_ptr;

    SET_TAG_NEXT(ft4_buff_ptr2, 9);
    SET_CODE_RGB(ft4_buff_ptr2, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr2->x0 = ft4_buff_ptr2->x2 = x0;
    ft4_buff_ptr2->x1 = ft4_buff_ptr2->x3 = x0 + power;
    ft4_buff_ptr2->y0 = ft4_buff_ptr2->y1 = y0;
    ft4_buff_ptr2->y2 = ft4_buff_ptr2->y3 = y0 + 8;

    ft4_buff_ptr2->tpage = getTPage(0, 0, 768, 0);
    ft4_buff_ptr2->clut  = getClut(48, 250);

    SET_UV_HALF(ft4_buff_ptr2->u0, 0x48, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u1, 0x49, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u2, 0x48, 0x98);
    SET_UV_HALF(ft4_buff_ptr2->u3, 0x49, 0x98);

    ft4_buff_ptr1 = ft4_buff_ptr2;
    ft4_buff_ptr2++;

    SET_TAG_NEXT(ft4_buff_ptr2, 9);
    SET_CODE_RGB(ft4_buff_ptr2, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr2->x0 = ft4_buff_ptr2->x2 = x0 + power;
    ft4_buff_ptr2->x1 = ft4_buff_ptr2->x3 = x0 + power + 4;
    ft4_buff_ptr2->y0 = ft4_buff_ptr2->y1 = y0;
    ft4_buff_ptr2->y2 = ft4_buff_ptr2->y3 = y0 + 8;

    ft4_buff_ptr2->tpage = getTPage(0, 0, 768, 0);
    ft4_buff_ptr2->clut  = getClut(48, 250);

    SET_UV_HALF(ft4_buff_ptr2->u0, 0x4C, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u1, 0x50, 0x90);
    SET_UV_HALF(ft4_buff_ptr2->u2, 0x4C, 0x98);
    SET_UV_HALF(ft4_buff_ptr2->u3, 0x50, 0x98);

    ft4_buff_ptr2++;

    if (infi && power == 88)
    {
        // A SPRT in a POLY_FT4-sized slot: linked and stepped as a POLY_FT4.
        SET_TAG_NEXT(ft4_buff_ptr2, 4);
        SET_CODE_RGB(ft4_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
        ((SPRT *)ft4_buff_ptr2)->x0 = x0 + 0x18;
        ((SPRT *)ft4_buff_ptr2)->y0 = y0;
        SET_UV0_CLUT((SPRT *)ft4_buff_ptr2, 0x28, 0xF8, getClut(32, 250));
        SET_WH_WORD((SPRT *)ft4_buff_ptr2, 0x28, 8);

        ft4_buff_ptr2++;
    }
    Map_prim_ptr = ft4_buff_ptr2;
    addPrims(&Disp_env_ptr->ot[2], ft4_buff_ptr1, ft4_buff_ptr2 - 1);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_basic_param_set);

// Draws num as (flag & NUM_DIGITS_MASK) digits from pos (x | y << 16) in the large digit font, one
// SPRT per digit drawn, linked after one another; returns the next free SPRT.
SPRT *Sub_screen_basic_param_set_sub(SPRT *ptr, uint32 pos, sint32 num, sint32 flag)
{
    sint32 d0;
    sint32 d1;

    for (d0 = (flag & NUM_DIGITS_MASK) - 1; d0 >= 0; d0--)
    {
        d1 = num % 10;
        if (((d0 == (flag & NUM_DIGITS_MASK) - 1) && !(flag & NUM_NO_ZERO)) || num || !(flag & NUM_NO_LEAD_ZERO))
        {
            SET_TAG_NEXT(ptr, 4);
            SET_CODE_RGB(ptr, 0x64, 0x80, 0x80, 0x80);
            SET_XY0_WORD(ptr, d0 * 7 + pos);
            SET_WH_WORD(ptr, 8, 8);
            SET_UV0_CLUT(ptr, d1 * 8 + 0x60, 0xB0, getClut(848, 249));
            ptr++;
        }
        num /= 10;
    }
    return ptr;
}

// Weapon slot d0's "now / max" counter (Player_work[0].rec[d0].val and Player_weapon_bullet_calc), into OT 2;
// none when max is 0x7FFF (unlimited).
void Sub_screen_status_param_set(sint32 d0)
{
    sint32 d1;
    sint32 d2;
    PL_WORK *pp;
    SPRT *sprt_buff_ptr1;
    SPRT *sprt_buff_ptr2;

    pp             = &Player_work[0];
    sprt_buff_ptr1 = sprt_buff_ptr2 = (SPRT *)Map_prim_ptr;

    d1 = pp->rec[d0].val;
    if ((d2 = Player_weapon_bullet_calc(pp, d0)) < 0x7FFF)
    {
        SET_TAG_LEN(sprt_buff_ptr2, 2);
        ((DR_MODE *)sprt_buff_ptr2)->code[0] = DRAW_MODE_CODE(getTPage(0, 0, 768, 0));
        SET_TAG_NEXT(sprt_buff_ptr2, 2);
        ((DR_MODE *)sprt_buff_ptr2)->code[1] = 0;
        sprt_buff_ptr2++;

        // The slash between the two numbers.
        SET_TAG_NEXT(sprt_buff_ptr2, 4);
        SET_CODE_RGB(sprt_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
        SET_XY0_WORD(sprt_buff_ptr2, 0xD1 | (0x8C << 16));
        SET_WH_WORD(sprt_buff_ptr2, 6, 8);
        SET_UV0_CLUT(sprt_buff_ptr2, 0x40, 0xF0, getClut(32, 250));
        sprt_buff_ptr2++;

        sprt_buff_ptr2 = Sub_screen_status_param_set_sub(sprt_buff_ptr2, 0xB4 | (0x8C << 16), d1, 4);
        sprt_buff_ptr2 = Sub_screen_status_param_set_sub(sprt_buff_ptr2, 0xD8 | (0x8C << 16), d2, 4);

        addPrims(&Disp_env_ptr->ot[2], sprt_buff_ptr1, sprt_buff_ptr2 - 1);
        Map_prim_ptr = (POLY_FT4 *)sprt_buff_ptr2;
    }
}

// Sub_screen_basic_param_set_sub in the small digit font (6x8).
SPRT *Sub_screen_status_param_set_sub(SPRT *ptr, uint32 pos, sint32 num, sint32 flag)
{
    sint32 d0;
    sint32 d1;

    for (d0 = (flag & NUM_DIGITS_MASK) - 1; d0 >= 0; d0--)
    {
        d1 = num % 10;
        if (((d0 == (flag & NUM_DIGITS_MASK) - 1) && !(flag & NUM_NO_ZERO)) || num || !(flag & NUM_NO_LEAD_ZERO))
        {
            SET_TAG_NEXT(ptr, 4);
            SET_CODE_RGB(ptr, 0x64, 0x80, 0x80, 0x80);
            SET_XY0_WORD(ptr, d0 * 7 + pos);
            SET_WH_WORD(ptr, 6, 8);
            SET_UV0_CLUT(ptr, d1 * 8, 0xC0, getClut(32, 250));
            ptr++;
        }
        num /= 10;
    }
    return ptr;
}

// The sub screen's background: a 7x5 grid of 64x64 tiles scrolling diagonally with System_timer,
// after a draw mode for its texture page, into OT 7.
void Sub_screen_back_ground_set(void)
{
    sint32 x0;
    sint32 y0;
    SPRT *sprt_buff_ptr1;
    SPRT *sprt_buff_ptr2;

    sprt_buff_ptr1 = sprt_buff_ptr2 = (SPRT *)Map_prim_ptr;

    SET_TAG_LEN(sprt_buff_ptr2, 2);
    ((DR_MODE *)sprt_buff_ptr2)->code[0] = DRAW_MODE_CODE(getTPage(0, 0, 832, 0));
    ((DR_MODE *)sprt_buff_ptr2)->code[1] = 0;
    SET_TAG_NEXT(sprt_buff_ptr2, 2);
    sprt_buff_ptr2++;

    for (y0 = 0; y0 <= 4; y0++)
    {
        for (x0 = 0; x0 <= 6; x0++)
        {
            SET_TAG_NEXT(sprt_buff_ptr2, 4);
            SET_CODE_RGB(sprt_buff_ptr2, 0x64, 0x80, 0x80, 0x80);
            SET_XY0_WORD(sprt_buff_ptr2,
                         (((x0 - 1) * 64 + (System_timer & 0x3F)) & 0xFFFF) | (((y0 - 1) * 64 + (System_timer & 0x3F)) << 16));
            SET_UV0_CLUT(sprt_buff_ptr2, 0xC0, 0x88, getClut(880, 249));
            SET_WH_WORD(sprt_buff_ptr2, 64, 64);
            sprt_buff_ptr2++;
        }
    }

    addPrims(&Disp_env_ptr->ot[7], sprt_buff_ptr1, sprt_buff_ptr2 - 1);
    Map_prim_ptr = (POLY_FT4 *)sprt_buff_ptr2;
}

// Called with Player_work by game.c on the way back from a screen: calls sound 0x8C when the
// player is in state 3, step 4, and, with unk174's top bits 0x40 and unk178 at 2, sound 0x123,
// 0x12B, 0x134 or 0x136 at joint 4 for unk170 4, 7, 0xC or 0xD.
void Sub_screen_sound_reinit(PL_WORK *pp)
{
    if ((*(uint32 *)&pp->routine_8 & 0xFFFF00) == 0x40300)
    {
        Sound_call(0x8C, 0, 0);
    }
    if (pp->unk174 & 0xC0)
    {
        if ((pp->unk174 & 0xC0) == 0x40)
        {
            if (pp->unk170 == 4)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x123, &pp->joint_pos[4]);
                }
            }
            if (pp->unk170 == 7)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x12B, &pp->joint_pos[4]);
                }
            }
            if (pp->unk170 == 0xC)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x134, &pp->joint_pos[4]);
                }
            }
            if (pp->unk170 == 0xD)
            {
                if (pp->unk178 == 2)
                {
                    Sound_call2(0x136, &pp->joint_pos[4]);
                }
            }
        }
    }
}

void Map_screen_init(void)
{
    *(uint32 *)&Map_screen_work.routine_0 = 0;
    *(uint32 *)&Map_screen_work.type      = 0;
    if (Game_work.sce_no < 9)
    {
        Map_screen_work.type = 0;
    }
    else
    {
        Map_screen_work.type = 1;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Map_screen_task);

// The map image: one 256x240 POLY_FT4 at x 32, into OT 2.
void map_screen_set(void)
{
    POLY_FT4 *ft4_buff_ptr;

    ft4_buff_ptr = Map_prim_ptr++;

    SET_TAG_LEN(ft4_buff_ptr, 9);
    SET_CODE_RGB(ft4_buff_ptr, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr->x0 = ft4_buff_ptr->x2 = 32;
    ft4_buff_ptr->x1 = ft4_buff_ptr->x3 = 287;
    ft4_buff_ptr->y0 = ft4_buff_ptr->y1 = 0;
    ft4_buff_ptr->y2 = ft4_buff_ptr->y3 = 240;

    ft4_buff_ptr->tpage = getTPage(1, 0, 768, 0);
    ft4_buff_ptr->clut  = getClut(0, 250);

    SET_UV_HALF(ft4_buff_ptr->u0, 0x00, 0x00);
    SET_UV_HALF(ft4_buff_ptr->u1, 0xFF, 0x00);
    SET_UV_HALF(ft4_buff_ptr->u2, 0x00, 0xF0);
    SET_UV_HALF(ft4_buff_ptr->u3, 0xFF, 0xF0);

    AddPrim(&Disp_env_ptr->ot[2], ft4_buff_ptr);
}

// The blinking cursor on the map: a 16x16 POLY_FT4 at map_cursor_pos's place for the current stage
// (the area within stages 3 and 0x1B; none in stages 0x17 and 0x1D), animated by System_timer.
void map_cursor_set(void)
{
    sint32 d0;
    sint32 d1;
    sint32 x0;
    sint32 y0;
    GAME_WORK *gp;
    POLY_FT4 *ft4_buff_ptr;

    gp = &Game_work;

    switch (gp->stage_no)
    {
        case 0x17:
        case 0x1D:
            return;

        case 0x03:
        case 0x1B:
            if (gp->area_no < 3)
            {
                d0 = gp->area_no;
            }
            else
            {
                d0 = 3;
            }
            break;

        case 0x0F:
            d0 = 6;
            break;

        case 0x13:
            d0 = 10;
            break;

        case 0x1C:
            d0 = 8;
            break;

        default:
            d0 = gp->stage_no;
            break;
    }

    x0           = map_cursor_pos[d0].vx + 32;
    y0           = map_cursor_pos[d0].vy;
    d1           = (System_timer & 7) * 16;
    ft4_buff_ptr = Map_prim_ptr++;

    SET_TAG_LEN(ft4_buff_ptr, 9);
    SET_CODE_RGB(ft4_buff_ptr, 0x2C, 0x80, 0x80, 0x80);

    ft4_buff_ptr->x0 = ft4_buff_ptr->x2 = x0 - 8;
    ft4_buff_ptr->x1 = ft4_buff_ptr->x3 = x0 + 7;
    ft4_buff_ptr->y0 = ft4_buff_ptr->y1 = y0 - 8;
    ft4_buff_ptr->y2 = ft4_buff_ptr->y3 = y0 + 7;

    ft4_buff_ptr->tpage = getTPage(1, 0, 768, 0);
    ft4_buff_ptr->clut  = getClut(0, 250);

    SET_UV_HALF(ft4_buff_ptr->u0, d1, 0xF0);
    SET_UV_HALF(ft4_buff_ptr->u1, d1 + 15, 0xF0);
    SET_UV_HALF(ft4_buff_ptr->u2, d1, 0xFF);
    SET_UV_HALF(ft4_buff_ptr->u3, d1 + 15, 0xFF);

    AddPrim(&Disp_env_ptr->ot[2], ft4_buff_ptr);
}
