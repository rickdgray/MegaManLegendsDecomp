#include "common.h"
#include "code_800133D8.h"
#include "code_80014AC0.h"
#include "cd.h"
#include "code_8001786C.h"
#include "code_80027678.h"
#include "code_8002E7A8.h"
#include "code_80037FB4.h"
#include "code_8005C258.h"
#include "code_8006430C.h"
#include "debug.h"
#include "display.h"
#include "fastmem.h"
#include "game.h"
#include "moji.h"
#include "pad.h"
#include "psyq/libgpu.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "sub_scrn.h"
#include "system.h"

// Called only from this file
void func_80013F60(CODE_800133D8_WORK *wp);
void func_80013F8C(CODE_800133D8_WORK *wp);
void func_80013FB8(void);
void func_80014394(void);
void func_8001456C(sint32 sel);

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

void func_80013420(void)
{
    CODE_800133D8_WORK *wp;

    wp         = &D_80098AA8;
    Vsync_wait = VSYNC_30FPS;
    // Clears cursor_C ... field_E as one word.
    *(uint32 *)&D_80098AA8.cursor_C = 0;
    Game_work.sce_no                = 0;
    Game_work.unk053                = 0;
    Game_work.unk082                = 0;
    func_8005C258();
    Cd_read_comb(20);
    Sce_read_sync(1);
    func_80019FB4();
    MojiTaskKill();
    func_80063BA8();
    func_80063EF0();
    func_80017994();
    while (1)
    {
        if (wp->routine_0 == 2 && (PAD_ON(Joy1) & (PAD_CROSS | PAD_START)))
        {
            Sound_call(0x82, 1, 0);
            if (D_80098A72 > 0 || (D_80098A72 == 0 && Fade_work.draw == 0))
            {
                wp->routine_1 = 1;
            }
            else
            {
                wp->routine_1 = 0;
            }
            wp->routine_0 = 4;
        }
        D_80080950[wp->routine_0](wp);
        func_80031AA4();
        Thread_wait(1);
    }
}

void func_80013578(CODE_800133D8_WORK *wp)
{
    wp->routine_3 ^= 1;
    if (wp->routine_3 != 0)
    {
        Game_work.stage_no = 1;
        Game_work.area_no  = 0;
    }
    else
    {
        // Each arm sets both bytes: one shared area_no store after the join schedules differently.
        Game_work.stage_no = 7;
        Game_work.area_no  = 0;
    }
    Game_work.unk082 = -0x80;
    func_80012F78(Game_main);
}

void func_800135DC(CODE_800133D8_WORK *wp)
{
    // Read signed here (lb); the increment below reads it unsigned (lbu).
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                D_80098810 = 1;
                D_80098864 = 0;
                Work_pools_init(1);
                func_8003697C();
                func_8002CFA4();
                func_800371A0(D_800808D0, &D_800808A8);
                Work_3C0_tbl = D_800808A4;
                wp->routine_1++;
            }
            break;
        case 1:
            D_80098810    = 0;
            wp->routine_A = 0;
            func_80015428(wp);
            Fade_start(2);
            wp->routine_0 = 2;
            wp->routine_1 = 1;
            break;
    }
}

void func_800136B8(CODE_800133D8_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                break;
            }
            Fade_start(2);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            wp->timer_4 = 900;
            wp->routine_1++;
            func_80013FB8();
            break;
        case 2:
            func_80013FB8();
            func_80013F60(wp);
            break;
        case 3:
            func_80013FB8();
            func_80014394();
            if (--wp->timer_4 == 0)
            {
                wp->routine_1++;
                Fade_start(10);
            }
            break;
        case 4:
            MojiTaskKill();
            func_80013FB8();
            func_80013F8C(wp);
            break;
    }
}

void func_800137D4(void)
{
    Stack_to_scratch();
    func_80015428(&D_80098AA8);
    func_80016FD4();
    func_80038370(&D_800979DC, &D_800979EC);
    Stack_restore();
    Model_draw_all();
    // Link the whole frame OT (reverse-cleared, so its last entry is the head) into ot[4].
    addPrims(&Disp_env_ptr->ot[4], &D_800A4D40[Dbl_buff_idx][0x1000] - 1, D_800A4D40[Dbl_buff_idx]);
}

void func_80013890(CODE_800133D8_WORK *wp)
{
    wp->routine_0 = 0;
    wp->routine_1 = 0;
}

void func_8001389C(CODE_800133D8_WORK *wp)
{
    GAME_WORK *gp;

    gp = &Game_work;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                break;
            }
            Fade_start(1);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            wp->timer_4 = 900;
            wp->routine_1++;
            gp->stage_no = 0;
            gp->area_no  = 0;
            func_80013FB8();
            func_8001456C(wp->cursor_C);
            break;
        case 2:
            func_80013FB8();
            func_8001456C(wp->cursor_C);
            func_80013F60(wp);
            break;
        case 3:
            func_80013FB8();
            func_8001456C(wp->cursor_C);
            if ((PAD_ON(Joy1) & PAD_UP) && wp->cursor_C > 0)
            {
                Sound_call(0x81, 1, 0);
                wp->cursor_C--;
                break;
            }
            if ((PAD_ON(Joy1) & PAD_DOWN) && wp->cursor_C < (gp->unk018 != 0 ? 3 : 2))
            {
                Sound_call(0x81, 1, 0);
                wp->cursor_C++;
                break;
            }
            if ((PAD_ON(Joy1) & PAD_LEFT) && wp->cursor_C == 3)
            {
                Sound_call(0x81, 1, 0);
                if (--gp->unk05B < (gp->unk01A != 0 ? 0 : 1))
                {
                    gp->unk05B = 2;
                }
            }
            if ((PAD_ON(Joy1) & PAD_RIGHT) && wp->cursor_C == 3)
            {
                Sound_call(0x81, 1, 0);
                if (++gp->unk05B >= 3)
                {
                    if (gp->unk01A != 0)
                    {
                        gp->unk05B = 0;
                    }
                    else
                    {
                        gp->unk05B = 1;
                    }
                }
            }
            if (PAD_ON(Joy1) & (PAD_CROSS | PAD_START))
            {
                switch (wp->cursor_C)
                {
                    case 0:
                        wp->routine_1 += 2;
                        Fade_start(22);
                        Sound_call(0xA6, 0, 0);
                        break;
                    case 1:
                        wp->routine_0 = 5;
                        wp->routine_1 = 0;
                        Fade_start(9);
                        Sound_call(0xA7, 0, 0);
                        break;
                    case 2:
                        wp->routine_0 = 6;
                        wp->routine_1 = 0;
                        Fade_start(9);
                        Sound_call(0xA8, 0, 0);
                        break;
                    case 3:
                        if (++gp->unk05B >= 3)
                        {
                            if (gp->unk01A != 0)
                            {
                                gp->unk05B = 0;
                            }
                            else
                            {
                                gp->unk05B = 1;
                            }
                        }
                        Sound_call(0x81, 1, 0);
                        break;
                }
            }
            else if (PAD_ON(Joy1) & PAD_TRIANGLE)
            {
                Sound_call(0x83, 1, 0);
                wp->field_E   = 1;
                wp->routine_0 = 2;
                wp->routine_1 = 1;
            }
            break;
        case 5:
            func_80013FB8();
            func_8001456C(wp->cursor_C);
            MojiTaskKill();
            Game_work.unk082 = 0;
            func_80012F78(Game_main);
            break;
    }
}

void func_80013CA0(CODE_800133D8_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                func_80013FB8();
                func_8001456C(wp->cursor_C);
                break;
            }
            Fade_start(1);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            wp->timer_4 = 900;
            wp->routine_1++;
            break;
        case 2:
            PAD_ON(Joy1)  = 0;
            PAD_NOW(Joy1) = 0;
            func_800665FC(0);
            func_800137D4();
            func_80013F60(wp);
            break;
        case 3:
            wp->routine_1 += func_800665FC(0);
            func_800137D4();
            break;
        case 4:
            if (Game_work.unk082 == 1)
            {
                Fade_start(22);
                Sub_screen_back_ground_set();
                func_80012F78(Game_main);
            }
            else
            {
                Fade_start(9);
                func_800137D4();
                wp->routine_0 = 4;
                wp->routine_1 = 0;
            }
            break;
    }
    Sub_screen_back_ground_set();
}

void func_80013E0C(CODE_800133D8_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 != 0)
            {
                func_80013FB8();
                func_8001456C(wp->cursor_C);
                break;
            }
            Fade_start(1);
            wp->routine_1++;
            // fall through
        case 1:
            MojiTaskKill();
            MojiTaskExec(0, D_8008CB64[0], -1);
            wp->timer_4 = 900;
            wp->routine_1++;
            func_800137D4();
            break;
        case 2:
            if ((Moji_flag & 0x40000000) || (PAD_ON(Joy1) & PAD_START))
            {
                if (PAD_ON(Joy1) & PAD_START)
                {
                    Sound_call(0x83, 1, 0);
                }
                Fade_start(9);
                wp->routine_0 = 4;
                wp->routine_1 = 0;
            }
            func_800137D4();
            break;
    }
    Sub_screen_back_ground_set();
}

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

// Draws the screen's images (texture pages at VRAM (320, 256) and (576, 256)) and two gradient
// boxes, then the rest of the frame (func_800137D4). Every primitive takes a POLY_FT4-sized slot.
void func_80013FB8(void)
{
    POLY_FT4 *prim;
    POLY_G4 *box;

    prim = Map_prim_ptr;
    setPolyFT4(prim);
    prim->tpage = GetTPage(1, 0, 320, 256);
    prim->clut  = GetClut(0, 0x1F0);
    setXY4(prim, 32, 8, 287, 8, 32, 168, 287, 168);
    setUV4(prim, 0, 0, 255, 0, 0, 160, 255, 160);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&D_800A4D40[Dbl_buff_idx][0x84], prim);
    prim++;
    setPolyFT4(prim);
    prim->tpage = GetTPage(1, 2, 576, 256);
    prim->clut  = GetClut(0, 0x1F2);
    setXY4(prim, 0, 0, 160, 0, 0, 160, 160, 160);
    setUV4(prim, 0, 0, 160, 0, 0, 160, 160, 160);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[7], prim);
    prim++;
    // The same image again, mirrored.
    setPolyFT4(prim);
    prim->tpage = GetTPage(1, 2, 576, 256);
    prim->clut  = GetClut(0, 0x1F2);
    setXY4(prim, 160, 0, 320, 0, 160, 160, 320, 160);
    setUV4(prim, 160, 0, 0, 0, 160, 160, 0, 160);
    setRGB0(prim, 0x80, 0x80, 0x80);
    setSemiTrans(prim, 0);
    AddPrim(&Disp_env_ptr->ot[7], prim);
    prim++;
    box = (POLY_G4 *)prim;
    setPolyG4(box);
    setXY4(box, 0, 144, 320, 144, 0, 160, 320, 160);
    setRGB0(box, 0, 0, 0);
    setRGB1(box, 0, 0, 0);
    setRGB2(box, 0xFF, 0xFF, 0xFF);
    setRGB3(box, 0xFF, 0xFF, 0xFF);
    setSemiTrans(box, 1);
    AddPrim(&Disp_env_ptr->ot[6], box);
    prim++;
    SetDrawMode((DR_MODE *)prim, 0, 0, GetTPage(1, 2, 0, 0), NULL);
    AddPrim(&Disp_env_ptr->ot[6], prim);
    prim++;
    box = (POLY_G4 *)prim;
    setPolyG4(box);
    setXY4(box, 0, 162, 320, 162, 0, 240, 320, 240);
    setRGB0(box, 0, 0, 0);
    setRGB1(box, 0, 0, 0);
    setRGB2(box, 0xC0, 0xFF, 0xE0);
    setRGB3(box, 0xC0, 0xFF, 0xE0);
    setSemiTrans(box, 0);
    AddPrim(&Disp_env_ptr->ot[7], box);
    prim++;
    Map_prim_ptr = prim;
    func_800137D4();
}

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
