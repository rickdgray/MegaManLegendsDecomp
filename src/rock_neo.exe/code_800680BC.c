#include "common.h"
#include "cd.h"
#include "code_8001786C.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include "psyq/libgpu.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "stage.h"

// The event steps below run the scene of D_8009039C. Its objects come from D_8008FF88
// (event_scene_init): Scene_work.obj_24[0] is a WORK_3C0, [1] and [2] WORK_5A4, [3] a WORK_50.

void func_800680BC(sint32 arg0)
{
    D_800C356C = -1;
    D_800C356E = 0x18;
    D_800C356F = arg0;
    D_800C3560 = 0;
    D_800C3562 = 0;
    D_800C3564 = 0;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xFF;
    D_800C3570 = 0xFF;
}

// Draws a semi-transparent full-screen tile of colour (r, g, b), blended with mode abr (tpage
// bits 5-6), into OT slot 1 of the current buffer.
void screen_tile_draw(uint8 r, uint8 g, uint8 b, uint16 abr)
{
    TILE *tile;
    DR_MODE *mode;

    tile = (TILE *)Map_prim_ptr;
    setTile(tile);
    tile->x0 = tile->y0 = 0;
    setWH(tile, 320, 240);
    setRGB0(tile, r, g, b);
    setSemiTrans(tile, 1);
    Map_prim_ptr++;
    mode = (DR_MODE *)Map_prim_ptr;
    SetDrawMode(mode, 0, 0, (abr << 5) | 0xF, NULL);
    Map_prim_ptr++;
    addPrim(&Disp_env_ptr->ot[1], tile);
    addPrim(&Disp_env_ptr->ot[1], mode);
}

void func_80068244(SCENE_WORK *sw)
{
    WORK_3C0 *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[0];
        wp->field_9 = 0;
        wp->field_A = 0;
        wp->routine_0 |= 2;
        func_800680BC(0);
    }
}

void func_80068290(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;
    WORK_50 *w3;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        w0 = sw->obj_24[0];
        w0->routine_0 &= ~2;
        wp           = sw->obj_24[1];
        wp->field_9  = 11;
        wp->pos_l.vx = 0xFE480000;
        wp->field_A  = 0;
        wp->pos_l.vz = 0xFE700000;
        wp->routine_0 |= 2;
        wp          = sw->obj_24[2];
        wp->field_9 = 0;
        wp->field_A = 0;
        wp->routine_0 |= 2;
        w3 = sw->obj_24[3];
        w3->routine_0 |= 2;
    }
}

void func_80068344(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 1;
        wp->field_A  = 0;
        wp->ang.vy   = 0x800;
        wp->pos_l.vx = 0xFEA20000;
        wp->routine_0 |= 2;
    }
}

void func_80068388(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[1];
        wp->field_9  = 1;
        wp->pos_l.vx = 0xFE5C0000;
        wp->pos_l.vz = 0xFF380000;
        wp->field_A  = 0;
        wp->ang.vy   = 0xC00;
        wp->routine_0 |= 2;
    }
    if (sw->timer_10 == 62)
    {
        wp          = sw->obj_24[1];
        wp->field_9 = 2;
        wp->field_A = 0;
    }
    if (sw->timer_10 == 82)
    {
        wp                     = sw->obj_24[1];
        wp->pos_l.vz           = 0xFF420000;
        wp->slot_F8[20].hide_3 = -1;
        wp->slot_F8[21].hide_3 = -1;
    }
    if (sw->timer_10 == 121)
    {
        wp          = sw->obj_24[1];
        wp->field_9 = 3;
        wp->field_A = 0;
    }
    if (sw->timer_10 == 210)
    {
        wp                     = sw->obj_24[1];
        wp->field_9            = 4;
        wp->field_A            = 0;
        wp->pos_180[1].col     = 0x2108;
        wp->pos_180[3].col     = 0x2D6B;
        wp->pos_180[4].col     = 0x2108;
        wp->pos_180[6].col     = 0x2D6B;
        wp->pos_180[7].col     = 0x2108;
        wp->pos_180[15].col    = 0x2108;
        wp->pos_180[16].col    = 0x2108;
        wp->pos_180[17].col    = 0x2108;
        wp->pos_180[18].col    = 0x2108;
        wp->pos_180[19].col    = 0x2108;
        wp->slot_F8[4].hide_3  = -1;
        wp->slot_F8[7].hide_3  = -1;
        wp->slot_F8[18].hide_3 = 0;
        wp->slot_F8[19].hide_3 = 0;
    }
}

void func_8006849C(SCENE_WORK *sw)
{
    WORK_5A4 *wp;
    sint32 mask;

    if (sw->field_0C == 0)
    {
        func_800680BC(2);
        wp   = sw->obj_24[1];
        mask = ~2; // a local: a literal folds to andi 0xFD at each use
        wp->routine_0 &= mask;
        wp = sw->obj_24[2];
        wp->routine_0 &= mask;
    }
}

// Steps part n's colour (RGB555) by 0x421 (1 per 5-bit channel) until it reaches 0x4210.
void part_col_step(WORK_5A4 *wp, sint32 n)
{
    if (wp->pos_180[n].col != 0x4210)
    {
        wp->pos_180[n].col += 0x421;
        if (wp->pos_180[n].col == 0x4210)
        {
            wp->pos_180[n].col = 0x4210; // redundant, but in the target
        }
    }
}

void func_8006854C(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        wp                     = sw->obj_24[1];
        wp->field_9            = 5;
        wp->pos_l.vx           = 0xFE590000;
        wp->pos_l.vz           = 0xFF3D0000;
        wp->field_A            = 0;
        wp->slot_F8[4].hide_3  = 0;
        wp->slot_F8[7].hide_3  = 0;
        wp->slot_F8[18].hide_3 = -1;
        wp->slot_F8[19].hide_3 = -1;
        wp->routine_0 |= 2;
        wp = sw->obj_24[2];
        wp->routine_0 |= 2;
        sw->field_64 = 1;
        sw->field_74 = 2;
        sw->field_68 = sw->field_6C = sw->field_70 = 0;
    }
    if (sw->timer_10 >= 14 && sw->timer_10 <= 20)
    {
        wp = sw->obj_24[1];
        part_col_step(wp, 1);
        part_col_step(wp, 3);
        part_col_step(wp, 6);
        part_col_step(wp, 7);
        part_col_step(wp, 4);
        part_col_step(wp, 15);
        part_col_step(wp, 16);
        part_col_step(wp, 17);
        part_col_step(wp, 18);
        part_col_step(wp, 19);
    }
    if (sw->timer_10 == 57)
    {
        wp         = sw->obj_24[1];
        wp->slot_D = 1;
    }
    if (sw->timer_10 == 87)
    {
        wp         = sw->obj_24[1];
        wp->slot_D = 0;
    }
    if (sw->timer_10 >= 90 && sw->timer_10 <= 120)
    {
        sw->field_68 += 9;
        sw->field_6C += 9;
        sw->field_70 += 9;
        if (sw->field_68 >= 0xFF)
        {
            sw->field_68 = sw->field_6C = sw->field_70 = 0xFF;
        }
    }
}

void func_80068728(SCENE_WORK *sw)
{
    WORK_5A4 *wp;
    WORK_50 *w3;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 1;
        wp->field_A  = 0;
        w3           = sw->obj_24[3];
        sw->field_64 = 0;
        w3->field_E  = -0x80;
    }
}

void func_80068760(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 2;
        wp->field_A  = 0;
        wp->pos_l.vx = 0xFECC0000;
        wp->pos_l.vz = 0xFE840000;
        wp           = sw->obj_24[1];
        wp->field_9  = 12;
        wp->field_A  = 0;
        wp->pos_l.vx = 0xFE5C0000;
        wp->ang.vy   = 0;
    }
    if (sw->timer_10 == 17)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 0;
        wp->field_A = 0;
        wp->ang.vy  = 0;
    }
}

void func_800687D8(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[1];
        wp->field_9  = 6;
        wp->slot_D   = 1;
        wp->field_A  = 0;
        wp->pos_l.vx = 0xFF380000;
        wp->pos_l.vz = 0xFF380000;
        wp->ang.vy   = 0;
    }
    if (sw->timer_10 == 60)
    {
        wp         = sw->obj_24[1];
        wp->slot_D = 0;
    }
    if (sw->timer_10 == 102)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 3;
        wp->field_A = 0;
        wp->ang.vy  = 0x800;
    }
}

void func_8006885C(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 4;
        wp->field_A = 0;
        wp->ang.vy  = 0x800;
    }
}

void func_8006888C(SCENE_WORK *sw)
{
    if (sw->timer_10 == 10)
    {
        func_80101D94();
    }
}

void func_800688BC(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 5;
        wp->field_A = 0;
    }
}

void func_800688E4(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[1];
        wp->field_9 = 7;
        wp->field_A = 0;
    }
}

void func_8006890C(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;
    sint32 mask;

    if (sw->timer_10 == 0)
    {
        func_800680BC(0);
        w0          = sw->obj_24[0];
        w0->field_9 = 1;
        w0->field_A = 0;
        w0->routine_0 |= 2;
        wp   = sw->obj_24[1];
        mask = ~2;
        wp->routine_0 &= mask;
        wp = sw->obj_24[2];
        wp->routine_0 &= mask;
    }
}

void func_80068998(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        w0 = sw->obj_24[0];
        w0->routine_0 &= ~2;
        wp = sw->obj_24[1];
        wp->routine_0 |= 2;
        wp          = sw->obj_24[2];
        wp->field_9 = 6;
        wp->field_A = 0;
        wp->routine_0 |= 2;
    }
}

void func_80068A24(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;
    sint32 mask;

    if (sw->timer_10 == 0)
    {
        func_800680BC(0);
        w0          = sw->obj_24[0];
        w0->field_9 = 1;
        w0->field_A = 0;
        w0->routine_0 |= 2;
        wp   = sw->obj_24[1];
        mask = ~2;
        wp->routine_0 &= mask;
        wp = sw->obj_24[2];
        wp->routine_0 &= mask;
    }
}

void func_80068AB0(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        w0 = sw->obj_24[0];
        w0->routine_0 &= ~3;
        wp          = sw->obj_24[1];
        wp->field_9 = 8;
        wp->field_A = 0;
        wp->routine_0 |= 2;
        wp = sw->obj_24[2];
        wp->routine_0 |= 2;
    }
}

void func_80068B3C(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;
    sint32 mask;

    if (sw->timer_10 == 0)
    {
        func_800680BC(0);
        w0 = sw->obj_24[0];
        w0->routine_0 |= 3;
        wp   = sw->obj_24[1];
        mask = ~2;
        wp->routine_0 &= mask;
        wp = sw->obj_24[2];
        wp->routine_0 &= mask;
    }
}

void func_80068BC0(SCENE_WORK *sw)
{
    WORK_3C0 *w0;

    if (sw->timer_10 == 0)
    {
        w0          = sw->obj_24[0];
        w0->field_A = 2;
    }
}

void func_80068BE4(SCENE_WORK *sw)
{
    WORK_3C0 *w0;
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        w0 = sw->obj_24[0];
        w0->routine_0 &= ~2;
        wp           = sw->obj_24[1];
        wp->field_9  = 9;
        wp->pos_l.vx = 0xFF1F0000;
        wp->pos_l.vy = 0xFFFB0000;
        wp->pos_l.vz = 0xFE700000;
        wp->field_A  = 0;
        wp->ang.vy   = 0x400;
        wp->routine_0 |= 2;
        wp = sw->obj_24[2];
        wp->routine_0 |= 2;
    }
    if (sw->timer_10 == 50)
    {
        wp          = sw->obj_24[1];
        wp->field_9 = 10;
        wp->field_A = 0;
        wp->routine_0 |= 2;
    }
}

void func_80068CB8(SCENE_WORK *sw)
{
    WORK_5A4 *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 7;
        wp->field_A = 0;
    }
}

void event_scene_init(SCENE_WORK *sw)
{
    func_8001E6C0(0, 0, 0);
    Sce_camera_work.arg_C0 = D_8008FFD8;
    sw->ev_ptr_A4          = D_8009039C;
    Scene_obj_ent_open(&D_8008FF88[0]);
    Scene_obj_ent_open(&D_8008FF88[1]);
    Scene_obj_ent_open(&D_8008FF88[2]);
    Scene_obj_ent_open(&D_8008FF88[3]);
    sw->field_64 = 0;
}

void event_step_call(SCENE_WORK *sw)
{
    if (sw->ev_08 != 0xFF)
    {
        sw->ev_ptr_A4->func(sw);
    }
}

void func_80068DA4(void)
{
}

void func_80068DAC(SCENE_WORK *sw)
{
    switch (sw->routine_4)
    {
        case 0:
            if (func_80042238(Player_work))
            {
                Player_work[0].routine_0 &= ~3;
                sw->routine_4++;
                Cd_xa_play_id(0x2001000B);
            }
            break;
        case 1:
            if (func_8001D878())
            {
                sw->routine_4++;
                sw->field_0C = 30;
            }
            break;
        case 2:
            if (--sw->field_0C == 0)
            {
                sw->routine_4++;
                Fade_start(2);
            }
            break;
        case 3:
            event_scene_init(sw);
            sw->routine_4++;
            // fall through
        case 4:
            if (D_80098A72 == 0 && (sw->ev_ptr_A4->ev_0 == 0xFF || func_8001DE84()))
            {
                Fade_start(10);
                sw->routine_4++;
            }
            // fall through
        case 5:
            event_step_call(sw);
            if (sw->field_64)
            {
                screen_tile_draw(sw->field_68, sw->field_6C, sw->field_70, sw->field_74);
            }
            Sce_camera_update();
            Sce_event_update();
            if (sw->timer_14 == 0x4680)
            {
                func_80068DA4();
            }
            if (sw->routine_4 == 5 && D_80098A72 == 0)
            {
                D_800C356C = 2;
                D_800C356E = 0x1B;
                D_800C356F = 6;
                D_800C3560 = -0x40;
                D_800C3562 = -1;
                D_800C3564 = 0xC0;
                D_800C356A = 0x800;
                D_800C356D = 0;
                D_800C3571 = 0xFF;
                D_800C3570 = 2;
                sw->unk00  = 0;
                Cd_subcmd(0, 1, 0);
                Player_work[0].routine_0 |= 1;
                func_80042314(Player_work);
                func_8001E390(0x2EB);
                Sce_flag_on(0x55);
                func_8001D974();
            }
            break;
    }
}
