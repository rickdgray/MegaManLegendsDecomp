#include "common.h"
#include "game.h"
#include "psyq/libgpu.h"
#include "display.h"
#include "scratch.h"
#include "system.h"
#include "sound.h"
#include "player.h"
#include "code_8002E7A8.h"
#include "code_8004324C.h"
#include "scene.h"
#include "debug.h"
#include "code_8003AC24.h"
#include "code_8005C258.h"
#include "code_8006430C.h"
#include "code_800133D8.h"
#include "code_8001786C.h"
#include "moji.h"
#include "pad.h"
#include "cd.h"
#include "sub_scrn.h"
#include "code_80037FB4.h"
#include "fastmem.h"
#include "code_8001F828.h"
#include "code_80027678.h"
#include "code_80037534.h"
#include "code_80048620.h"
#include "code_8003A3B4.h"

// Called only from this file
void game_frame_exec(void);
void game_timer_count(void);
void soft_reset_check(void);
void player_entry_set(PL_WORK *pl, AREA_ENTRY *entry, sint32 reset);
void func_80016434(sint32 mode);
void func_80016D0C(GAME_WORK *gw);
void func_80016D38(GAME_WORK *gw);
void func_80016DAC(void);
void func_80016E90(void);
void func_80017094(void);
void func_80017154(void);
void func_80017210(void);
void func_800172F4(void);
void func_800173B4(void);
void eve_work_exec(void);
void func_80017528(void);

// The game thread: clears Game_work's routines and runs Game_main_tbl[routine_0] once a frame.
void Game_main(void)
{
    GAME_WORK *wp;

    wp                        = &Game_work;
    Vsync_wait                = 2;
    *(uint32 *)&wp->routine_0 = 0; // one store over routine_0, routine_1 and unk002
    while (1)
    {
        Game_main_tbl[wp->routine_0](wp);
        func_80031AA4();
        game_timer_count();
        soft_reset_check();
        Thread_wait(1);
    }
}

// Starts a game: a new one when bit 0 of unk082 is clear, else the one in the loaded save image.
void Game_init(GAME_WORK *wp)
{
    sint32 load;
    sint32 i;

    load                        = wp->unk082 & 1;
    *(uint32 *)&wp->unk004      = 0; // one store over unk004 and unk006
    *(uint32 *)&wp->aperture_08 = 0; // one store over aperture_08 and the halfword after it
    wp->unk068                  = -1;
    wp->unk06A                  = -1;
    wp->unk06C                  = -1;
    wp->unk081                  = 0;
    wp->unk083                  = 0;
    D_800C356C                  = 0;
    Work_pools_init(1);
    if (load == 0)
    {
        func_800664BC();
    }
    else
    {
        Save_image_restore();
    }
    Player_init(load);
    Sce_flag_init(load);
    func_8003B278(load);
    func_8005DBB4(load);
    func_80067E6C(load);
    func_80063BA8();
    func_80019FB4();
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    for (i = 0; i < 16; i++)
    {
        wp->unk174.w[i] = 0;
    }
    func_8006471C();
    Sce_flag_on(0x1FE);
    Sce_flag_on(0x38A);
    Sce_flag_on(0x3C7);
}

void func_80015734(GAME_WORK *wp)
{
    AREA_ENTRY *entry;

    entry = &D_800C3558;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            Sce_flag_on(0x527);
            if (!(wp->unk082 & 1) && wp->unk05B == 0)
            {
                Sce_flag_on(0x510);
                Sce_flag_on(0x522);
                Sce_flag_on(0x446);
                Sce_flag_on(0x448);
            }
            break;
        case 1:
            func_80016D64();
            break;
    }
    if (entry->unk15 == 0)
    {
        wp->stage_no = entry->stage_16;
        wp->area_no  = entry->area_17;
        wp->sce_no   = wp->unk053;
        player_entry_set(&Player_work[0], entry, 1);
    }
    func_8001F23C();
    wp->routine_0 = 2;
    wp->routine_1 = 1;
    wp->unk082 &= 0xFE;
}

void func_80015840(GAME_WORK *wp)
{
    AREA_ENTRY *entry;

    entry = &D_800C3558;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_800C356D == 0)
            {
                wp->area_no = D_800C356F;
                wp->sce_no  = wp->unk053;
                player_entry_set(&Player_work[0], entry, 1);
            }
            func_80016D64();
            // fall through
        case 1:
            Camera_init();
            func_8001F3C8();
            entry->mode_14 = 0;
            wp->routine_0  = 3;
            wp->routine_1  = 0;
            break;
    }
}

// Game routine 3, the game in an area: fades in, runs the frame, takes the room changes the area
// entry asks for (mode_14), opens the sub screen (START), area map or map screen (SELECT), the
// SUPPORT module or save screen (unk081 1 or 2), and fades out to the next area (routine 1 for a
// new stage, else 2).
void func_800158F0(GAME_WORK *wp)
{
    AREA_ENTRY *entry;
    PL_WORK *player;
    SVECTOR delta;

    Sce_update();
    func_80063C30();
    entry  = &D_800C3558;
    player = &Player_work[0];
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                if (entry->unk18 == 255)
                {
                    wp->routine_1 += 2;
                }
                else
                {
                    Fade_start(entry->unk18);
                    wp->routine_1++;
                }
                game_frame_exec();
                D_800A3958.work.pos_A8 = D_800A3958.work.pos_98;
                Sound_stage_play();
            }
            break;
        case 1:
            game_frame_exec();
            func_80016D0C(wp);
            break;
        case 2:
            if (entry->mode_14 != 0)
            {
                if (entry->mode_14 == -1)
                {
                    if (Scene_work.unk00 == 0)
                    {
                        delta.vy = 0;
                        delta.vx = entry->pos.vx - player->pos.vx;
                        delta.vz = entry->pos.vz - player->pos.vz;
                        // vx through the block (its address stays in a register), vy and vz
                        // through the cast (a lui each), as the target has them
                        D_800A3958.work.pos_98.vx += delta.vx;
                        Camera_work.pos_98.vy += delta.vy;
                        Camera_work.pos_98.vz += delta.vz;
                        func_80039D38(&delta);
                        Obj_work_flag_change(0x200, 0x80);
                        func_8002F420(0x1FE, &delta);
                    }
                    else
                    {
                        func_8002F420(0x1FE, NULL);
                    }
                    wp->area_no = entry->area_17;
                    wp->sce_no  = wp->unk053;
                    player_entry_set(player, entry, 0);
                    func_8001F3C8();
                    entry->mode_14 = 0;
                }
                else
                {
                    wp->routine_1++;
                    player->flags_BD |= 0x40;
                }
            }
            else if (Scene_work.unk00 == 0 && D_80098A72 == 0 && !(Moji_flag & 0x0F000000) && player->life >= 0 && player->flags_BD == 0 &&
                     player->routine_0 == 1)
            {
                if ((PAD_ON(Joy1) & PAD_START) || Joy1.type == 0xFF)
                {
                    *(uint32 *)&wp->routine_0 = 4; // routine_0 = 4, routine_1 = 0
                    break;
                }
                if ((PAD_ON(Joy1) & PAD_SELECT) && wp->unk083 == 0)
                {
                    if (D_80098004 != 0)
                    {
                        *(uint32 *)&wp->routine_0 = 7;
                        break;
                    }
                    if (wp->stage_no >= 3 && wp->stage_no != 26)
                    {
                        *(uint32 *)&wp->routine_0 = 8;
                        break;
                    }
                }
            }
            game_frame_exec();
            if (wp->unk081 != 0)
            {
                if (wp->unk081 == 1)
                {
                    *(uint32 *)&wp->routine_0 = 5;
                }
                if (wp->unk081 == 2)
                {
                    *(uint32 *)&wp->routine_0 = 6;
                }
                wp->unk081 = 0;
            }
            break;
        case 3:
            game_frame_exec();
            Sound_stage_check();
            if (entry->unk19 == 255)
            {
                wp->routine_1 += 2;
                break;
            }
            if (entry->unk19 < 16)
            {
                wp->routine_1++;
            }
            else
            {
                player->unk110 = 0;
                player->unk111 = 0;
                player->flags |= 3;
                wp->routine_1 += 2;
            }
            Fade_start(entry->unk19);
            break;
        case 4:
            game_frame_exec();
            func_80016D38(wp);
            break;
        case 5:
            game_frame_exec();
            entry->mode_14++;
            wp->routine_1++;
            break;
        case 6:
            if (entry->mode_14 == 3)
            {
                if (wp->stage_no != entry->stage_16)
                {
                    wp->routine_0 = 1;
                    wp->routine_1 = 1;
                }
                else
                {
                    wp->routine_0 = 2;
                    wp->routine_1 = 0;
                }
                func_8003B140();
                MojiTaskKill();
                Game_logo_kill(-1);
                func_80063BA8();
            }
            else
            {
                game_frame_exec();
            }
            break;
        case 7:
            game_frame_exec();
            wp->routine_0 = 9;
            wp->routine_1 = 0;
            break;
    }
}

void game_frame_exec(void)
{
    Stack_to_scratch();
    func_800679B8();
    eve_work_exec();
    Player_exec();
    Obj_player_dist_set();
    Gauge_update();
    func_80017094();
    func_80016FD4();
    func_80017210();
    func_800172F4();
    func_80017528();
    Solid_collide_all();
    func_8003C2D8();
    func_80017154();
    func_800173B4();
    Camera_update();
    Hit_check_all();
    func_80037F60();
    func_8005DCB4();
    Map_draw();
    Room_model_update();
    Obj_draw_all();
    Stack_restore();
    Model_draw_all();
    // Link the whole frame OT (reverse-cleared, so its last entry is the head) into ot[4].
    addPrims(&Disp_env_ptr->ot[4], &D_800A4D40[Dbl_buff_idx][0x1000] - 1, D_800A4D40[Dbl_buff_idx]);
}

// Puts the player at the area entry: position (and its previous copies) and facing angle; reset
// also clears field_74/75, and in routine_0 3 the saved position is set too.
void player_entry_set(PL_WORK *pl, AREA_ENTRY *entry, sint32 reset)
{
    pl->pos.vx = pl->old.vx = entry->pos.vx;
    pl->pos.vy = pl->old.vy = entry->pos.vy;
    pl->pos.vz = pl->old.vz = entry->pos.vz;
    pl->pos_l.vx = pl->old_l.vx = entry->pos.vx << 16;
    pl->pos_l.vy = pl->old_l.vy = entry->pos.vy << 16;
    pl->pos_l.vz = pl->old_l.vz = entry->pos.vz << 16;
    pl->ang.vy = pl->old_ang.vy = entry->ang_y;
    if (reset)
    {
        pl->field_74 = pl->field_75 = 0;
    }
    if (pl->routine_0 == 3)
    {
        pl->svec_438 = pl->pos;
        pl->pos_428  = pl->pos_l;
        pl->ang_440  = pl->ang;
    }
}

// Game routine 4, the sub screen: stops text and sound, runs Sub_screen_task until its result
// moves routine_1 on, reloads the player's setting files, then returns to routine 3.
void Game_sub_screen(GAME_WORK *wp)
{
    PL_WORK *player;

    player = &Player_work[0];
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (Dbl_buff_idx != 0)
            {
                D_80098810 = 1;
                D_80098864 = 1;
                MojiTaskKill();
                func_80063EF0();
                Sound_key_off_voice(0x10);
                Sound_key_off_voice(0x16);
                Sound_key_off_voice(0x17);
                Fade_start(0);
                wp->routine_1++;
            }
            break;
        case 1:
            D_80098810 = 0;
            func_8005EBE4();
            Cd_subcmd(0, 1, 0);
            wp->routine_1++;
            break;
        case 2:
            wp->routine_1 += Sub_screen_task();
            break;
        case 3:
            D_80098810 = 1;
            D_80098864 = 0;
            func_8001F5E4();
            wp->routine_1++;
            break;
        case 4:
            if (Cd_read_sync2() == 0)
            {
                D_80098810 = 0;
                Sub_screen_sound_reinit(player);
                player->flags_BD &= ~0x40;
                MojiTaskKill();
                Game_logo_kill(-1);
                wp->routine_0 = 3;
                wp->routine_1 = 1;
            }
            break;
    }
}

// Game routine 5: loads and runs the SUPPORT module (file 0xCF on stage 3 area 6, stage 0x13 area
// 0xB and stage 0x1B area 6, else 0xCE) until it answers, then reloads file 0x17 and returns to
// routine 3.
void func_80016160(GAME_WORK *wp)
{
    PL_WORK *player;
    sint32 file;
    sint32 result;

    player = &Player_work[0];
    switch ((sint8)wp->routine_1)
    {
        case 0:
            player->flags_BD |= 0x40;
            if (Sound_fade_flags == 0)
            {
                // stage_no and area_no read as one halfword
                if (*(uint16 *)&Game_work.stage_no == 0x603 || *(uint16 *)&Game_work.stage_no == 0xB13 ||
                    *(uint16 *)&Game_work.stage_no == 0x61B)
                {
                    file = 0xCF;
                }
                else
                {
                    file = 0xCE;
                }
                Cd_seek_file(file);
                Fade_start(0x17);
                Sound_fade_start(0x10);
                wp->routine_1++;
            }
            game_frame_exec();
            break;
        case 1:
            if (D_80098810 == 0)
            {
                game_frame_exec();
            }
            else
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (Sound_fade_flags == 0)
            {
                Sound_seq_stop_all();
                func_8001B314();
                MojiTaskKill();
                func_80063EF0();
                if (*(uint16 *)&Game_work.stage_no == 0x603 || *(uint16 *)&Game_work.stage_no == 0xB13 ||
                    *(uint16 *)&Game_work.stage_no == 0x61B)
                {
                    file = 0xCF;
                }
                else
                {
                    file = 0xCE;
                }
                Cd_read_comb(file);
                wp->routine_1++;
            }
            break;
        case 3:
            if (Cd_read_sync2() == 0)
            {
                func_801D8130();
                func_8003A744();
                wp->routine_1++;
            }
            break;
        case 4:
            if (D_80098A72 != 0)
            {
                break;
            }
            Fade_start(1);
            wp->routine_1++;
            // fall through
        case 5:
            result = func_801D816C();
            if (result != 0)
            {
                if (result > 0)
                {
                    Cd_seek_file(0x17);
                    func_80016434(result);
                    Sound_fade_start(0x10);
                    Fade_start(0x15);
                    wp->routine_1++;
                }
                else
                {
                    wp->routine_1 = 2;
                }
            }
            break;
        case 6:
            if (Sound_fade_flags == 0)
            {
                MojiTaskKill();
                Game_logo_kill(-1);
                Cd_read_comb(0x17);
                wp->routine_1++;
            }
            break;
        case 7:
            if (D_80098A72 == 0 && Cd_read_sync2() == 0)
            {
                player->flags_BD &= ~0x40;
                Camera_init();
                if (D_800C356C == 0)
                {
                    Fade_start(1);
                    wp->routine_0 = 3;
                    wp->routine_1 = 1;
                    Sound_stage_play();
                }
                else
                {
                    wp->routine_0 = 3;
                    wp->routine_1 = 6;
                }
            }
            break;
    }
}

void func_80016434(sint32 mode)
{
    if (mode == 2)
    {
        D_800C356C                = 3;
        D_800C356E                = 24;
        D_800C3562                = -1;
        D_800C3570                = 255;
        Game_work.unk078.b.unk079 = 27;
        D_800C356F                = 0;
        D_800C3560                = 0;
        D_800C3564                = 0;
        D_800C356A                = 0;
        D_800C356D                = 0;
        Game_work.unk078.b.unk07A = 1;
    }
}

// Game routine 6: runs the save screen (func_800665FC) over the running frame until it is done,
// then returns to routine 3.
void func_800164B4(GAME_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            wp->routine_1 += func_800665FC(1);
            break;
        case 1:
            wp->routine_0 = 3;
            wp->routine_1 = 2;
            break;
    }
    game_frame_exec();
}

// Game routine 7, the area map: draws it until SELECT or TRIANGLE, then returns to routine 3.
void Game_area_map(GAME_WORK *wp)
{
    PL_WORK *player;

    player = &Player_work[0];
    switch ((sint8)wp->routine_1)
    {
        case 0:
            func_8005DF3C();
            player->flags_BD |= 0x40;
            MojiTaskKill();
            func_80063EF0();
            Fade_start(0);
            Sound_key_off_voice(0x10);
            Sound_key_off_voice(0x16);
            Sound_key_off_voice(0x17);
            wp->routine_1++;
            break;
        case 1:
            Area_map_screen_draw();
            if ((PAD_ON(Joy1) & PAD_SELECT) || (PAD_ON(Joy1) & PAD_TRIANGLE))
            {
                Sub_screen_sound_reinit(player);
                player->flags_BD &= ~0x40;
                MojiTaskKill();
                Game_logo_kill(-1);
                wp->routine_0 = 3;
                wp->routine_1 = 1;
            }
            break;
    }
}

// Game routine 8, the map screen: loads its file (0x21 before scenario 9, else 0x23), runs
// Map_screen_task until it answers nonzero, reloads file 0x15, then returns to routine 3.
void Game_map_screen(GAME_WORK *wp)
{
    PL_WORK *player;

    player = &Player_work[0];
    switch ((sint8)wp->routine_1)
    {
        case 0:
            player->flags_BD |= 0x40;
            MojiTaskKill();
            func_80063EF0();
            Fade_start(0);
            Sound_key_off_voice(0x10);
            Sound_key_off_voice(0x16);
            Sound_key_off_voice(0x17);
            Cd_read_comb(wp->sce_no < 9 ? 0x21 : 0x23);
            wp->routine_1++;
            break;
        case 1:
            if (Cd_read_sync2() == 0)
            {
                Map_screen_init();
                wp->routine_1++;
            }
            break;
        case 2:
            if (Map_screen_task())
            {
                player->flags_BD &= ~0x40;
                MojiTaskKill();
                Game_logo_kill(-1);
                wp->routine_1++;
            }
            break;
        case 3:
            Cd_read_comb(0x15);
            wp->routine_1++;
            break;
        case 4:
            if (Cd_read_sync2() == 0)
            {
                Sub_screen_sound_reinit(player);
                wp->routine_0 = 3;
                wp->routine_1 = 1;
            }
            break;
    }
}

// Game routine 9 (from func_800158F0's routine_1 7): closes the black bars, stops text, sound and
// CD, shows file 0x19's picture with sound 0x41 until START or the sequence ends, then reopens the
// main thread at func_80013420.
// Parked: the only difference is Sound_call(0x41): the target sets up a0 alone (a1 and a2 keep
// whatever Cd_read_sync left), which the three-argument prototype in sound.h can't produce.
#ifdef NON_MATCHING
void func_80016798(GAME_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            Vsync_wait = 4;
            game_frame_exec();
            Cd_seek_file(0x19);
            Fade_start(11);
            wp->aperture_08 = 120;
            wp->routine_1++;
            break;
        case 1:
            game_frame_exec();
            func_80016E90();
            if ((wp->aperture_08 -= 2) < 0)
            {
                wp->aperture_08 = 0;
            }
            goto wait;
        case 2:
            Vsync_wait     = 2;
            Fade_work.draw = 0;
            MojiTaskKill();
            func_80063BA8();
            func_80063EF0();
            Cd_subcmd(0, 1, 0);
            Sound_seq_stop_all();
            func_8001B314();
            Cd_read_comb(0x19);
            Cd_read_sync();
            wp->unk006 = 150;
            wp->routine_1++;
            Sound_call(0x41, 0, 0);
            Fade_start(2);
            break;
        case 3:
            func_80016DAC();
            func_80016D0C(wp);
            break;
        case 4:
            func_80016DAC();
            if ((PAD_ON(Joy1) & PAD_START) || Sound_seq_is_eos(0) == 0)
            {
                wp->routine_1++;
                Sound_fade_start(0x10);
                Fade_start(10);
            }
            break;
        case 5:
            func_80016DAC();
        wait:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                wp->routine_1++;
            }
            break;
        case 6:
            Sce_flag_off(0x1FE);
            *(uint16 *)&D_80098AA8.routine_0 = 1; // routine_0 = 1, routine_1 = 0
            func_80012F78(func_80013420);
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016798);
#endif

// Same code as func_80016798, with Fade_start(15) in routine_1 0.
// Parked: as func_80016798 (Sound_call(0x41) with a0 alone).
#ifdef NON_MATCHING
void func_800169AC(GAME_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            Vsync_wait = 4;
            game_frame_exec();
            Cd_seek_file(0x19);
            Fade_start(15);
            wp->aperture_08 = 120;
            wp->routine_1++;
            break;
        case 1:
            game_frame_exec();
            func_80016E90();
            if ((wp->aperture_08 -= 2) < 0)
            {
                wp->aperture_08 = 0;
            }
            goto wait;
        case 2:
            Vsync_wait     = 2;
            Fade_work.draw = 0;
            MojiTaskKill();
            func_80063BA8();
            func_80063EF0();
            Cd_subcmd(0, 1, 0);
            Sound_seq_stop_all();
            func_8001B314();
            Cd_read_comb(0x19);
            Cd_read_sync();
            wp->unk006 = 150;
            wp->routine_1++;
            Sound_call(0x41, 0, 0);
            Fade_start(2);
            break;
        case 3:
            func_80016DAC();
            func_80016D0C(wp);
            break;
        case 4:
            func_80016DAC();
            if ((PAD_ON(Joy1) & PAD_START) || Sound_seq_is_eos(0) == 0)
            {
                wp->routine_1++;
                Sound_fade_start(0x10);
                Fade_start(10);
            }
            break;
        case 5:
            func_80016DAC();
        wait:
            if (D_80098A72 == 0 && Sound_fade_flags == 0)
            {
                wp->routine_1++;
            }
            break;
        case 6:
            Sce_flag_off(0x1FE);
            *(uint16 *)&D_80098AA8.routine_0 = 1; // routine_0 = 1, routine_1 = 0
            func_80012F78(func_80013420);
            break;
    }
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_800169AC);
#endif

void game_timer_count(void)
{
    if (++Game_work.timer_0c > GAME_TIMER_MAX)
    {
        Game_work.timer_0c = GAME_TIMER_MAX;
    }
}

// Soft reset: SELECT+START held for over 61 frames, once a game runs (routine_0 3 and up, but
// not 6) and code_8006430C's module is idle, stops text, sound and CD, fades out, and reopens
// the main thread at func_80013420 with D_80098AA8.routine_0 = 1.
void soft_reset_check(void)
{
    if (Game_work.routine_0 >= 3 && Game_work.routine_0 != 6 && D_80098910.active_0 == 0)
    {
        if ((PAD_NOW(Joy1) & (PAD_SELECT | PAD_START)) == (PAD_SELECT | PAD_START))
        {
            if (Game_work.reset_timer++ >= 61)
            {
                Vsync_wait = 2;
                MojiTaskKill();
                func_80063BA8();
                func_80063EF0();
                func_800665E8();
                func_8001B314();
                Sound_seq_stop_all();
                Cd_subcmd(0, 1, 0);
                Fade_work.draw = 0;
                Fade_start(8);
                Sce_flag_off(0x1FE);
                *(uint16 *)&D_80098AA8.routine_0 = 1; // routine_0 = 1, routine_1 = 0
                func_80012F78(func_80013420);
            }
        }
        else
        {
            Game_work.reset_timer = 0;
        }
    }
}

// Same code as func_80013F60, on Game_work.
void func_80016D0C(GAME_WORK *gw)
{
    if (D_80098A72 == 0)
    {
        gw->routine_1++;
    }
}

// Same code as func_80013F60, on Game_work.
void func_80016D38(GAME_WORK *gw)
{
    if (D_80098A72 == 0)
    {
        gw->routine_1++;
    }
}

// Waits for the running sound fade to end, then calls func_8001B314.
void func_80016D64(void)
{
    while (Sound_fade_flags != 0)
    {
        Thread_wait(1);
    }
    func_8001B314();
}

// Draws a 256x128 textured quad at (32, 56) from the texture page at VRAM (0, 0), CLUT row 496.
void func_80016DAC(void)
{
    POLY_FT4 *p;

    p            = Map_prim_ptr;
    Map_prim_ptr = p + 1;
    setPolyFT4(p);
    p->tpage = GetTPage(0, 0, 320, 256);
    p->clut  = GetClut(0, 496);
    p->x0    = 32;
    p->y0    = 56;
    p->x1    = 287;
    p->y1    = 56;
    p->x2    = 32;
    p->y2    = 184;
    p->x3    = 287;
    p->y3    = 184;
    p->u0    = 0;
    p->v0    = 0;
    p->u1    = 255;
    p->v1    = 0;
    p->u2    = 0;
    p->v2    = 128;
    p->u3    = 255;
    p->v3    = 128;
    p->r0    = 128;
    p->g0    = 128;
    p->b0    = 128;
    AddPrim(&Disp_env_ptr->ot[2], p);
}

// Draws two black bars, over and under a band of 2 * Game_work.aperture_08 lines at the screen's
// middle. Each takes a POLY_FT4-sized slot of Map_prim_ptr, though it is a POLY_F4.
// Parked: GCC keeps &Game_work.aperture_08 in a saved register across the AddPrim call, where the
// target rebuilds it with lui at each of the four reads (see notes/rock_neo.md).
#ifdef NON_MATCHING
void func_80016E90(void)
{
    POLY_FT4 *packet;
    POLY_F4 *p;

    packet = Map_prim_ptr;
    p      = (POLY_F4 *)packet;
    setPolyF4(p);
    p->x0 = 0;
    p->y0 = 0;
    p->x1 = 320;
    p->y1 = 0;
    p->x2 = 0;
    p->y2 = 120 - Game_work.aperture_08;
    p->x3 = 320;
    p->y3 = 120 - Game_work.aperture_08;
    setRGB0(p, 0, 0, 0);
    setSemiTrans(p, 0);
    AddPrim(&Disp_env_ptr->ot[1], packet++);
    p = (POLY_F4 *)packet;
    setPolyF4(p);
    p->x0 = 0;
    p->y0 = 119 + Game_work.aperture_08;
    p->x1 = 320;
    p->y1 = 119 + Game_work.aperture_08;
    p->x2 = 0;
    p->y2 = 240;
    p->x3 = 320;
    p->y3 = 240;
    setRGB0(p, 0, 0, 0);
    setSemiTrans(p, 0);
    AddPrim(&Disp_env_ptr->ot[1], packet++);
    Map_prim_ptr = packet;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/game", func_80016E90);
#endif

// The pool updates: run the handler of every live slot (be_flag and flags both with bit 0 set),
// keeping the slot in a global for the handlers. be_flag is read signed here (lb), where the
// pools' other code reads it unsigned, hence the casts.
void func_80016FD4(void)
{
    for (D_80098820 = D_8009F108; D_80098820 < &D_8009F108[16]; D_80098820++)
    {
        if ((sint8)D_80098820->be_flag & D_80098820->flags & 1)
        {
            Work_3C0_tbl[D_80098820->id][D_80098820->handler](D_80098820);
        }
    }
}

void func_80017094(void)
{
    for (D_800989D0 = D_800C3580; D_800989D0 < &D_800C3580[4]; D_800989D0++)
    {
        if ((sint8)D_800989D0->be_flag & D_800989D0->flags & 1)
        {
            Work_5A4_tbl[D_800989D0->id][D_800989D0->handler](D_800989D0);
        }
    }
}

void func_80017154(void)
{
    for (D_800988F8 = D_800BFB20; D_800988F8 < &D_800BFB20[16]; D_800988F8++)
    {
        if ((sint8)D_800988F8->be_flag & D_800988F8->flags & 1)
        {
            D_80089820[D_800988F8->id]();
        }
    }
}

// The shot pool's update. D_800988F8 serves both shot pools (D_800BFB20 too, func_80017154); the
// layouts are the same, so the stage overlay's handlers (ids below 0x80) get the slot as SHL_WORK.
void func_80017210(void)
{
    for (D_800988F8 = (PL_SHL_WORK *)D_8009CF88; D_800988F8 < (PL_SHL_WORK *)&D_8009CF88[32]; D_800988F8++)
    {
        if ((sint8)D_800988F8->be_flag & D_800988F8->flags & 1)
        {
            if (D_800988F8->id < 0x80)
            {
                Shl_work_tbl[D_800988F8->id]((SHL_WORK *)D_800988F8);
            }
            else
            {
                D_80089820[D_800988F8->id]();
            }
        }
    }
}

// The effect pool's update, first pass: the stage overlay's kinds (ids below 0x80).
void func_800172F4(void)
{
    for (D_800988E4 = D_800A3B40; D_800988E4 < &D_800A3B40[64]; D_800988E4++)
    {
        if ((sint8)D_800988E4->be_flag & D_800988E4->flags & 1)
        {
            if (D_800988E4->id < 0x80)
            {
                Work_48_tbl[D_800988E4->id](D_800988E4);
            }
        }
    }
}

// Second pass: ROCK_NEO's own kinds (0x80 and up).
void func_800173B4(void)
{
    for (D_800988E4 = D_800A3B40; D_800988E4 < &D_800A3B40[64]; D_800988E4++)
    {
        if ((sint8)D_800988E4->be_flag & D_800988E4->flags & 1)
        {
            if (D_800988E4->id >= 0x80)
            {
                D_80089858[D_800988E4->id](D_800988E4);
            }
        }
    }
}

void eve_work_exec(void)
{
    for (D_800988F0 = D_800A2D08; D_800988F0 < &D_800A2D08[16]; D_800988F0++)
    {
        if ((sint8)D_800988F0->be_flag & D_800988F0->flags & 1)
        {
            Eve_work_tbl[D_800988F0->id](D_800988F0);
        }
    }
}

void func_80017528(void)
{
    for (D_80098924 = D_800BF118; D_80098924 < &D_800BF118[32]; D_80098924++)
    {
        if ((sint8)D_80098924->be_flag & D_80098924->flags & 1)
        {
            Work_50_tbl[D_80098924->id](D_80098924);
        }
    }
}
