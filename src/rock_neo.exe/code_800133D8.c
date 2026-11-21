#include "common.h"
#include "code_800133D8.h"
#include "display.h"
#include "game.h"
#include "psyq/libgpu.h"
#include "scratch.h"
#include "system.h"

// Called only from this file
void func_80013F60(CODE_800133D8_WORK *wp);

void func_800133D8(void)
{
    // Clears routine_0 ... field_8 as three words.
    ((uint32 *)&D_80098AA8)[0] = 0;
    ((uint32 *)&D_80098AA8)[1] = 0;
    ((uint32 *)&D_80098AA8)[2] = 0;
    func_80012F78(func_80013420);
}

void func_80013418(void)
{
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_80013420);

void func_80013578(CODE_800133D8_WORK *wp)
{
    wp->routine_3 ^= 1;
    if (wp->routine_3 != 0)
    {
        Game_work.unk050 = 1;
        Game_work.unk051 = 0;
    }
    else
    {
        // Each arm sets both bytes: one shared unk051 store after the join schedules differently.
        Game_work.unk050 = 7;
        Game_work.unk051 = 0;
    }
    Game_work.unk082 = -0x80;
    func_80012F78(func_800155A4);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_800135DC);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_800136B8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_800137D4);

void func_80013890(CODE_800133D8_WORK *wp)
{
    wp->routine_0 = 0;
    wp->routine_1 = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_8001389C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_80013CA0);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_80013E0C);

void func_80013F60(CODE_800133D8_WORK *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_1++;
    }
}

void func_80013F8C(CODE_800133D8_WORK *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_1 = 0;
        wp->routine_0++;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_800133D8", func_80013FB8);

// Draws two images from the texture page at VRAM (320, 256) into OT slot 2.
void func_80014394(void)
{
    POLY_FT4 *prim;

    prim = Map_prim_ptr;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 320, 256);
    prim->clut  = GetClut(0, 0x1F1);
    setXY4(prim, 56, 176, 264, 176, 56, 192, 264, 192);
    setUV4(prim, 0, 160, 208, 160, 0, 176, 208, 176);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[2], prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 320, 256);
    prim->clut  = GetClut(0, 0x1F1);
    setXY4(prim, 32, 208, 288, 208, 32, 232, 288, 232);
    setUV4(prim, 0, 176, 255, 176, 0, 200, 255, 200);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[2], prim);
    prim++;
    Map_prim_ptr = prim;
}

// Draws a menu of three entries (a fourth while Game_work.unk018 is set) on a black box, into OT
// slot 2: entry `sel` gets CLUT x 0x20 (highlighted), the others 0x10. Every primitive takes a
// POLY_FT4-sized slot, the box's POLY_F4 too.
void func_8001456C(sint32 sel)
{
    sint32 clut;
    sint32 clut_x;
    POLY_FT4 *prim;
    POLY_F4 *box;

    prim = Map_prim_ptr;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 320, 256);
    prim->clut  = GetClut(sel == 0 ? 0x20 : 0x10, 0x1F1);
    setXY4(prim, 104, 148, 216, 148, 104, 164, 216, 164);
    setUV4(prim, 0, 200, 112, 200, 0, 216, 112, 216);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[2], prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 320, 256);
    prim->clut  = GetClut(sel == 1 ? 0x20 : 0x10, 0x1F1);
    setXY4(prim, 104, 164, 216, 164, 104, 180, 216, 180);
    setUV4(prim, 112, 200, 224, 200, 112, 216, 224, 216);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[2], prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(0, 0, 320, 256);
    prim->clut  = GetClut(sel == 2 ? 0x20 : 0x10, 0x1F1);
    setXY4(prim, 120, 180, 200, 180, 120, 196, 200, 196);
    setUV4(prim, 0, 216, 80, 216, 0, 232, 80, 232);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[2], prim);
    prim++;
    if (Game_work.unk018 != 0)
    {
        setPolyFT4(prim);
        prim->tpage = GetTPage(0, 0, 320, 256);
        // Each image of the fourth entry has its own pair of CLUTs: highlighted, then normal.
        clut   = (Game_work.unk05B + 1) * 2;
        clut_x = clut + 1;
        if (sel != 3)
        {
            clut_x = (clut + 2) * 16;
        }
        else
        {
            clut_x *= 16;
        }
        prim->clut = GetClut(clut_x, 0x1F1);
        setRGB0(prim, 0x80, 0x80, 0x80);
        setSemiTrans(prim, 0);
        switch (Game_work.unk05B)
        {
            case 0:
                setXY4(prim, 132, 196, 188, 196, 132, 212, 188, 212);
                setUV4(prim, 80, 216, 136, 216, 80, 232, 136, 232);
                break;
            case 1:
                setXY4(prim, 120, 196, 200, 196, 120, 212, 200, 212);
                setUV4(prim, 136, 216, 216, 216, 136, 232, 216, 232);
                break;
            case 2:
                setXY4(prim, 132, 196, 188, 196, 132, 212, 188, 212);
                setUV4(prim, 0, 232, 56, 232, 0, 248, 56, 248);
                break;
        }
        AddPrim(&Disp_env_ptr->ot[2], prim);
        prim++;
    }
    box = (POLY_F4 *)prim;
    setcode(box, 0x28);
    setlen(box, 5);
    setRGB0(box, 0, 0, 0);
    setSemiTrans(box, 1);
    if (Game_work.unk018 != 0)
    {
        setXY4(box, 96, 144, 224, 144, 96, 216, 224, 216);
    }
    else
    {
        setXY4(box, 96, 144, 224, 144, 96, 200, 224, 200);
    }
    AddPrim(&Disp_env_ptr->ot[2], prim);
    prim++;
    Map_prim_ptr = prim;
}
