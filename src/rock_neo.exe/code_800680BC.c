#include "common.h"
#include "display.h"
#include "psyq/libgpu.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "stage.h"

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
void screen_tile_draw(sint32 r, sint32 g, sint32 b, uint16 abr)
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
    WORK_10C *wp;

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
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        sw->obj_24[0]->routine_0 &= ~2;
        wp          = sw->obj_24[1];
        wp->field_9 = 11;
        wp->x_1C    = 0xFE480000;
        wp->field_A = 0;
        wp->z_24    = 0xFE700000;
        wp->routine_0 |= 2;
        wp          = sw->obj_24[2];
        wp->field_9 = 0;
        wp->field_A = 0;
        wp->routine_0 |= 2;
        sw->obj_24[3]->routine_0 |= 2;
    }
}

void func_80068344(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 1;
        wp->field_A  = 0;
        wp->angle_56 = 0x800;
        wp->x_1C     = 0xFEA20000;
        wp->routine_0 |= 2;
    }
}

// obj_24[1] is larger than WORK_10C (see func_80068508): the offsets past 0x10C are written as
// byte offsets until its type is known. The halfwords at 0x186 + n * 8 are RGB555 colours.
void func_80068388(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[1];
        wp->field_9  = 1;
        wp->x_1C     = 0xFE5C0000;
        wp->z_24     = 0xFF380000;
        wp->field_A  = 0;
        wp->angle_56 = 0xC00;
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
        wp->z_24               = 0xFF420000;
        *((sint8 *)wp + 0x14B) = -1;
        *((sint8 *)wp + 0x14F) = -1;
    }
    if (sw->timer_10 == 121)
    {
        wp          = sw->obj_24[1];
        wp->field_9 = 3;
        wp->field_A = 0;
    }
    if (sw->timer_10 == 210)
    {
        wp                               = sw->obj_24[1];
        wp->field_9                      = 4;
        wp->field_A                      = 0;
        *(sint16 *)((uint8 *)wp + 0x18E) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x19E) = 0x2D6B;
        *(sint16 *)((uint8 *)wp + 0x1A6) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x1B6) = 0x2D6B;
        *(sint16 *)((uint8 *)wp + 0x1BE) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x1FE) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x206) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x20E) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x216) = 0x2108;
        *(sint16 *)((uint8 *)wp + 0x21E) = 0x2108;
        *((sint8 *)wp + 0x10B)           = -1;
        *((sint8 *)wp + 0x117)           = -1;
        *((sint8 *)wp + 0x143)           = 0;
        *((sint8 *)wp + 0x147)           = 0;
    }
}

void func_8006849C(SCENE_WORK *sw)
{
    WORK_10C *wp;
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

// wp is Scene_work.obj_24[1] (func_8006854C), an object of unknown type larger than WORK_10C
// with 8-byte entries from +0x180. Steps entry n's halfword at +6 by 0x421 (1 per 5-bit channel)
// until it reaches 0x4210.
void func_80068508(uint8 *wp, sint32 n)
{
    sint16 *col;

    col = (sint16 *)(wp + n * 8 + 0x186);
    if (*col != 0x4210)
    {
        *col += 0x421;
        if (*col == 0x4210)
        {
            *col = 0x4210; // redundant, but in the target
        }
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800680BC", func_8006854C);

void func_80068728(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 1;
        wp->field_A  = 0;
        wp           = sw->obj_24[3];
        sw->field_64 = 0;
        wp->field_E  = -0x80;
    }
}

void func_80068760(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 2;
        wp->field_A  = 0;
        wp->x_1C     = 0xFECC0000;
        wp->z_24     = 0xFE840000;
        wp           = sw->obj_24[1];
        wp->field_9  = 12;
        wp->field_A  = 0;
        wp->x_1C     = 0xFE5C0000;
        wp->angle_56 = 0;
    }
    if (sw->timer_10 == 17)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 0;
        wp->field_A  = 0;
        wp->angle_56 = 0;
    }
}

void func_800687D8(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[1];
        wp->field_9  = 6;
        wp->slot_D   = 1;
        wp->field_A  = 0;
        wp->x_1C     = 0xFF380000;
        wp->z_24     = 0xFF380000;
        wp->angle_56 = 0;
    }
    if (sw->timer_10 == 60)
    {
        wp         = sw->obj_24[1];
        wp->slot_D = 0;
    }
    if (sw->timer_10 == 102)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 3;
        wp->field_A  = 0;
        wp->angle_56 = 0x800;
    }
}

void func_8006885C(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp           = sw->obj_24[2];
        wp->field_9  = 4;
        wp->field_A  = 0;
        wp->angle_56 = 0x800;
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
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 5;
        wp->field_A = 0;
    }
}

void func_800688E4(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[1];
        wp->field_9 = 7;
        wp->field_A = 0;
    }
}

void func_8006890C(SCENE_WORK *sw)
{
    WORK_10C *wp;
    WORK_10C *op;
    sint32 mask;

    if (sw->timer_10 == 0)
    {
        func_800680BC(0);
        wp          = sw->obj_24[0];
        wp->field_9 = 1;
        wp->field_A = 0;
        wp->routine_0 |= 2;
        op   = sw->obj_24[1];
        mask = ~2;
        op->routine_0 &= mask;
        op = sw->obj_24[2];
        op->routine_0 &= mask;
    }
}

void func_80068998(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        sw->obj_24[0]->routine_0 &= ~2;
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
    WORK_10C *wp;
    WORK_10C *op;
    sint32 mask;

    if (sw->timer_10 == 0)
    {
        func_800680BC(0);
        wp          = sw->obj_24[0];
        wp->field_9 = 1;
        wp->field_A = 0;
        wp->routine_0 |= 2;
        op   = sw->obj_24[1];
        mask = ~2;
        op->routine_0 &= mask;
        op = sw->obj_24[2];
        op->routine_0 &= mask;
    }
}

void func_80068AB0(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        sw->obj_24[0]->routine_0 &= ~3;
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
    WORK_10C *wp;
    sint32 mask;

    if (sw->timer_10 == 0)
    {
        func_800680BC(0);
        sw->obj_24[0]->routine_0 |= 3;
        wp   = sw->obj_24[1];
        mask = ~2;
        wp->routine_0 &= mask;
        wp = sw->obj_24[2];
        wp->routine_0 &= mask;
    }
}

void func_80068BC0(SCENE_WORK *sw)
{
    if (sw->timer_10 == 0)
    {
        sw->obj_24[0]->field_A = 2;
    }
}

void func_80068BE4(SCENE_WORK *sw)
{
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        func_800680BC(1);
        sw->obj_24[0]->routine_0 &= ~2;
        wp           = sw->obj_24[1];
        wp->field_9  = 9;
        wp->x_1C     = 0xFF1F0000;
        wp->y_20     = 0xFFFB0000;
        wp->z_24     = 0xFE700000;
        wp->field_A  = 0;
        wp->angle_56 = 0x400;
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
    WORK_10C *wp;

    if (sw->timer_10 == 0)
    {
        wp          = sw->obj_24[2];
        wp->field_9 = 7;
        wp->field_A = 0;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800680BC", func_80068CE0);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800680BC", func_80068DAC);
