#include "common.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include "scratch.h"
#include "sub_scrn.h"

// Pool common (see sub_scrn.h): Map_screen_init stores routine_0 through $gp.
MAP_SCREEN_WORK Map_screen_work;

// Called only from this file
void sub_screen_sort_sub(PL_WORK *pp, sint32 d0, sint32 d1);
void sub_screen_rb_parts_calc_sub00(SUB_SCREEN_WORK *subp, sint32 d0);
void sub_screen_rb_parts_calc_sub01(SUB_SCREEN_WORK *subp, sint32 d0);
void map_screen_set(void);
void map_cursor_set(void);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", func_8005EC34);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_sort_attack);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_sort_energy);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_sort_range);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_sort_rapid);

void sub_screen_sort_sub(PL_WORK *pp, sint32 d0, sint32 d1)
{
    uint8 sort_buff;

    sort_buff                  = pp->rb_parts_sort_data[d0];
    pp->rb_parts_sort_data[d0] = pp->rb_parts_sort_data[d1];
    pp->rb_parts_sort_data[d1] = sort_buff;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_rb_parts_set);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", sub_screen_status_calc);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_gauge_set);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_gauge_set2);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_status_param_set);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/sub_scrn", Sub_screen_sound_reinit);

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

// The blinking cursor on the map: a 16x16 POLY_FT4 at D_8008DB34's place for the current stage
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

    x0           = D_8008DB34[d0].vx + 32;
    y0           = D_8008DB34[d0].vy;
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
