#include "common.h"
#include "game.h"
#include "cd.h"
#include "code_800133d8.h"

void func_800155A4(void)
{
    GAME_WORK *wp;

    wp                        = &Game_work;
    GAME_SCRATCH_MODE         = 2;
    *(uint32 *)&wp->routine_0 = 0;
    while (1)
    {
        Game_main_tbl[(sint8)wp->routine_0](wp);
        func_80031AA4();
        func_80016BC0();
        func_80016BF4();
        Thread_wait(1);
    }
}

void func_80015634(GAME_WORK *wp)
{
    sint32 mode;
    sint32 i;

    mode               = wp->flags_82 & 1;
    wp->work04.value04 = 0;
    wp->work08.value08 = 0;
    wp->value68        = -1;
    wp->value6a        = -1;
    wp->value6c        = -1;
    wp->flags_81       = 0;
    wp->flags_83       = 0;
    D_800C356C         = 0;
    func_8002E7A8(1);
    if (mode == 0)
    {
        func_800664BC();
    }
    else
    {
        func_80065AA8();
    }
    func_8003BE40(mode);
    func_8001D8C0(mode);
    func_8003B278(mode);
    func_8005DBB4(mode);
    func_80067E6C(mode);
    func_80063BA8();
    func_80019FB4();
    wp->routine_0 = 1;
    wp->routine_1 = 0;
    for (i = 0; i < 16; i++)
    {
        wp->slots[i] = 0;
    }
    func_8006471C();
    Sce_flag_on(0x1FE);
    Sce_flag_on(0x38A);
    Sce_flag_on(0x3C7);
}

void func_80015734(GAME_WORK *wp)
{
    GAME_ENTRY_WORK *entry;

    entry = &D_800C3558;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            Sce_flag_on(0x527);
            if (!(wp->flags_82 & 1) && wp->option_5b == 0)
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
    if (entry->flags15 == 0)
    {
        wp->routine_50 = entry->stage;
        wp->routine_51 = entry->room;
        wp->flags_52   = wp->flags_53;
        func_80015EE8(&Player_work, entry, 1);
    }
    func_8001F23C();
    wp->routine_0 = 2;
    wp->routine_1 = 1;
    wp->flags_82 &= 0xFE;
}

void func_80015840(GAME_WORK *wp)
{
    GAME_ENTRY_WORK *entry;

    entry = &D_800C3558;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_800C356D == 0)
            {
                wp->routine_51 = D_800C356F;
                wp->flags_52   = wp->flags_53;
                func_80015EE8(&Player_work, entry, 1);
            }
            func_80016D64();
            // fall through
        case 1:
            func_80038648();
            func_8001F3C8();
            entry->flags14 = 0;
            wp->routine_0  = 3;
            wp->routine_1  = 0;
            break;
    }
}

void func_800158F0(GAME_WORK *wp)
{
    GAME_ENTRY_WORK *entry;
    PL_WORK *player;
    GAME_DELTA delta;

    func_8001D990();
    func_80063C30();
    entry  = &D_800C3558;
    player = &Player_work;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                if (entry->fade_in == 255)
                {
                    wp->routine_1 += 2;
                }
                else
                {
                    func_80017C30(entry->fade_in);
                    wp->routine_1++;
                }
                func_80015DB4();
                D_800A3A00 = D_800A39F0;
                func_80019D18();
            }
            break;
        case 1:
            func_80015DB4();
            func_80016D0C(wp);
            break;
        case 2:
            if (entry->flags14 != 0)
            {
                if (entry->flags14 == -1)
                {
                    if (Scene_work == 0)
                    {
                        delta.y = 0;
                        delta.x = entry->x - player->position.x;
                        delta.z = entry->z - player->position.z;
                        D_800A39F0.x += delta.x;
                        D_800A39F4 += delta.y;
                        D_800A39F8 += delta.z;
                        func_80039D38(&delta);
                        Obj_work_flag_change(0x200, 0x80);
                        func_8002F420(0x1FE, &delta);
                    }
                    else
                    {
                        func_8002F420(0x1FE, NULL);
                    }
                    wp->routine_51 = entry->room;
                    wp->flags_52   = wp->flags_53;
                    func_80015EE8(player, entry, 0);
                    func_8001F3C8();
                    entry->flags14 = 0;
                }
                else
                {
                    wp->routine_1++;
                    player->flags_bd |= 0x40;
                }
            }
            else if (Scene_work == 0 && D_80098A72 == 0 && !(Moji_flag & 0x0F000000) &&
                     player->value6e >= 0 && (sint8)player->flags_bd == 0 && player->kind == 1)
            {
                if ((D_800C0C2A & 8) || D_800C0C24 == 255)
                {
                    *(uint32 *)&wp->routine_0 = 4;
                    break;
                }
                if ((D_800C0C2A & 1) && wp->flags_83 == 0)
                {
                    if (D_80098004 != 0)
                    {
                        *(uint32 *)&wp->routine_0 = 7;
                        break;
                    }
                    if (wp->routine_50 >= 3 && wp->routine_50 != 26)
                    {
                        *(uint32 *)&wp->routine_0 = 8;
                        break;
                    }
                }
            }
            func_80015DB4();
            if (wp->flags_81 != 0)
            {
                if (wp->flags_81 == 1)
                {
                    *(uint32 *)&wp->routine_0 = 5;
                }
                if (wp->flags_81 == 2)
                {
                    *(uint32 *)&wp->routine_0 = 6;
                }
                wp->flags_81 = 0;
            }
            break;
        case 3:
            func_80015DB4();
            func_80019C20();
            if (entry->fade_out == 255)
            {
                wp->routine_1 += 2;
                break;
            }
            if (entry->fade_out < 16)
            {
                wp->routine_1++;
            }
            else
            {
                player->value110 = 0;
                player->value111 = 0;
                player->flags06 |= 3;
                wp->routine_1 += 2;
            }
            func_80017C30(entry->fade_out);
            break;
        case 4:
            func_80015DB4();
            func_80016D38(wp);
            break;
        case 5:
            func_80015DB4();
            entry->flags14++;
            wp->routine_1++;
            break;
        case 6:
            if (entry->flags14 == 3)
            {
                if (wp->routine_50 != entry->stage)
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
                func_80015DB4();
            }
            break;
        case 7:
            func_80015DB4();
            wp->routine_0 = 9;
            wp->routine_1 = 0;
            break;
    }
}

void func_80015DB4(void)
{
    sint32 index;
    CODE800133D8_LINK *link;

    func_800175D8();
    func_800679B8();
    func_80017478();
    func_8003C07C();
    func_8003606C();
    func_8005C2B8();
    func_80017094();
    func_80016FD4();
    func_80017210();
    func_800172F4();
    func_80017528();
    func_80051BE4();
    func_8003C2D8();
    func_80017154();
    func_800173B4();
    func_80038894();
    func_8003450C();
    func_80037F60();
    func_8005DCB4();
    func_800238B4();
    func_80023144();
    func_80027678();
    func_800175FC();
    func_80028DE0();
    index = CODE800133D8_DISPLAY_INDEX;
    link  = D_80098934;
    setaddr(D_800A4D40[index], getaddr(&link->tag));
    setaddr(&link->tag, &D_800A4D40[index][0x1000] - 1);
}

void func_80015EE8(PL_WORK *wp, GAME_ENTRY_WORK *entry, sint32 reset)
{
    wp->position.x = wp->position_prev.x = entry->x;
    wp->position.y = wp->position_prev.y = entry->y;
    wp->position.z = wp->position_prev.z = entry->z;
    wp->position_fixed.x = wp->position_fixed_prev.x = entry->x << 16;
    wp->position_fixed.y = wp->position_fixed_prev.y = entry->y << 16;
    wp->position_fixed.z = wp->position_fixed_prev.z = entry->z << 16;
    wp->rotation.y = wp->rotation_prev.y = entry->angle;
    if (reset)
    {
        wp->value74 = wp->value75 = 0;
    }
    if (wp->kind == 3)
    {
        wp->position_saved       = wp->position;
        wp->position_saved_fixed = wp->position_fixed;
        wp->rotation_saved       = wp->rotation;
    }
}

void func_80015FE8(GAME_WORK *wp)
{
    PL_WORK *player;

    player = &Player_work;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            if (CODE800133D8_DISPLAY_INDEX != 0)
            {
                D_80098810 = 1;
                D_80098864 = 1;
                MojiTaskKill();
                func_80063EF0();
                Sound_key_off_voice(0x10);
                Sound_key_off_voice(0x16);
                Sound_key_off_voice(0x17);
                func_80017C30(0);
                wp->routine_1++;
            }
            break;
        case 1:
            D_80098810 = 0;
            func_8005EBE4();
            func_8001D494(0, 1, 0);
            wp->routine_1++;
            break;
        case 2:
            wp->routine_1 += func_8005EC34();
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
                player->flags_bd &= 0xBF;
                MojiTaskKill();
                Game_logo_kill(-1);
                wp->routine_0 = 3;
                wp->routine_1 = 1;
            }
            break;
    }
}

void func_80016160(GAME_WORK *wp)
{
    PL_WORK *player;
    sint32 sound;
    sint32 result;

    player = &Player_work;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            player->flags_bd |= 0x40;
            if (D_80098788 == 0)
            {
                if (*(uint16 *)&Game_work.routine_50 == 0x603 ||
                    *(uint16 *)&Game_work.routine_50 == 0xB13 ||
                    *(uint16 *)&Game_work.routine_50 == 0x61B)
                {
                    sound = 0xCF;
                }
                else
                {
                    sound = 0xCE;
                }
                func_8001D7AC(sound);
                func_80017C30(0x17);
                func_8001D854(0x10);
                wp->routine_1++;
            }
            func_80015DB4();
            break;
        case 1:
            if (D_80098810 == 0)
            {
                func_80015DB4();
            }
            else
            {
                wp->routine_1++;
            }
            break;
        case 2:
            if (D_80098788 == 0)
            {
                func_8001B33C();
                func_8001B314();
                MojiTaskKill();
                func_80063EF0();
                if (*(uint16 *)&Game_work.routine_50 == 0x603 ||
                    *(uint16 *)&Game_work.routine_50 == 0xB13 ||
                    *(uint16 *)&Game_work.routine_50 == 0x61B)
                {
                    sound = 0xCF;
                }
                else
                {
                    sound = 0xCE;
                }
                Cd_read_comb(sound);
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
            func_80017C30(1);
            wp->routine_1++;
            // fall through
        case 5:
            result = func_801D816C();
            if (result != 0)
            {
                if (result > 0)
                {
                    func_8001D7AC(0x17);
                    func_80016434(result);
                    func_8001D854(0x10);
                    func_80017C30(0x15);
                    wp->routine_1++;
                }
                else
                {
                    wp->routine_1 = 2;
                }
            }
            break;
        case 6:
            if (D_80098788 == 0)
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
                player->flags_bd &= 0xBF;
                func_80038648();
                if (D_800C356C == 0)
                {
                    func_80017C30(1);
                    wp->routine_0 = 3;
                    wp->routine_1 = 1;
                    func_80019D18();
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
        D_800C356C         = 3;
        D_800C356E         = 24;
        D_800C3562         = -1;
        D_800C3570         = 255;
        Game_work.flags_79 = 27;
        D_800C356F         = 0;
        D_800C3560         = 0;
        D_800C3564         = 0;
        D_800C356A         = 0;
        D_800C356D         = 0;
        Game_work.flags_7a = 1;
    }
}

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
    func_80015DB4();
}

void func_80016528(GAME_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            func_8005DF3C();
            PLAYER_WORK_PTR->flags_bd |= 0x40;
            MojiTaskKill();
            func_80063EF0();
            func_80017C30(0);
            Sound_key_off_voice(0x10);
            Sound_key_off_voice(0x16);
            Sound_key_off_voice(0x17);
            wp->routine_1++;
            break;
        case 1:
            func_8005DF4C();
            if ((D_800C0C2A & 1) || (D_800C0C2A & 0x1000))
            {
                Sub_screen_sound_reinit(&Player_work);
                PLAYER_WORK_PTR->flags_bd &= 0xBF;
                MojiTaskKill();
                Game_logo_kill(-1);
                wp->routine_0 = 3;
                wp->routine_1 = 1;
            }
            break;
    }
}

void func_8001663C(GAME_WORK *wp)
{
    PL_WORK *player;

    player = &Player_work;
    switch ((sint8)wp->routine_1)
    {
        case 0:
            player->flags_bd |= 0x40;
            MojiTaskKill();
            func_80063EF0();
            func_80017C30(0);
            Sound_key_off_voice(0x10);
            Sound_key_off_voice(0x16);
            Sound_key_off_voice(0x17);
            Cd_read_comb((sint8)wp->flags_52 < 9 ? 0x21 : 0x23);
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
                player->flags_bd &= 0xBF;
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

void func_80016798(GAME_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            GAME_SCRATCH_MODE = 4;
            func_80015DB4();
            func_8001D7AC(0x19);
            func_80017C30(11);
            wp->work08.transition_aperture = 120;
            wp->routine_1++;
            break;
        case 1:
            func_80015DB4();
            func_80016E90();
            if ((wp->work08.transition_aperture -= 2) < 0)
            {
                wp->work08.transition_aperture = 0;
            }
            goto wait;
        case 2:
            GAME_SCRATCH_MODE = 2;
            D_80098A70        = 0;
            MojiTaskKill();
            func_80063BA8();
            func_80063EF0();
            func_8001D494(0, 1, 0);
            func_8001B33C();
            func_8001B314();
            Cd_read_comb(0x19);
            Cd_read_sync();
            wp->work04.words.timer06 = 150;
            wp->routine_1++;
#ifdef PORT
            Sound_call(0x41, 0, 0);
#else
            // Retail passes no a1/a2 (whatever Cd_read_sync left); the port passes 0, 0.
            Sound_call(0x41);
#endif
            func_80017C30(2);
            break;
        case 3:
            func_80016DAC();
            func_80016D0C(wp);
            break;
        case 4:
            func_80016DAC();
            if ((D_800C0C2A & 8) || func_8001A0A8(0) == 0)
            {
                wp->routine_1++;
                func_8001D854(0x10);
                func_80017C30(10);
            }
            break;
        case 5:
            func_80016DAC();
        wait:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 6:
            Sce_flag_off(0x1FE);
            *(uint16 *)&Code800133D8_work.routine_0 = 1;
            func_80012F78(func_80013420);
            break;
    }
}

void func_800169AC(GAME_WORK *wp)
{
    switch ((sint8)wp->routine_1)
    {
        case 0:
            GAME_SCRATCH_MODE = 4;
            func_80015DB4();
            func_8001D7AC(0x19);
            func_80017C30(15);
            wp->work08.transition_aperture = 120;
            wp->routine_1++;
            break;
        case 1:
            func_80015DB4();
            func_80016E90();
            if ((wp->work08.transition_aperture -= 2) < 0)
            {
                wp->work08.transition_aperture = 0;
            }
            goto wait;
        case 2:
            GAME_SCRATCH_MODE = 2;
            D_80098A70        = 0;
            MojiTaskKill();
            func_80063BA8();
            func_80063EF0();
            func_8001D494(0, 1, 0);
            func_8001B33C();
            func_8001B314();
            Cd_read_comb(0x19);
            Cd_read_sync();
            wp->work04.words.timer06 = 150;
            wp->routine_1++;
#ifdef PORT
            Sound_call(0x41, 0, 0);
#else
            // Retail passes no a1/a2 (whatever Cd_read_sync left); the port passes 0, 0.
            Sound_call(0x41);
#endif
            func_80017C30(2);
            break;
        case 3:
            func_80016DAC();
            func_80016D0C(wp);
            break;
        case 4:
            func_80016DAC();
            if ((D_800C0C2A & 8) || func_8001A0A8(0) == 0)
            {
                wp->routine_1++;
                func_8001D854(0x10);
                func_80017C30(10);
            }
            break;
        case 5:
            func_80016DAC();
        wait:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                wp->routine_1++;
            }
            break;
        case 6:
            Sce_flag_off(0x1FE);
            *(uint16 *)&Code800133D8_work.routine_0 = 1;
            func_80012F78(func_80013420);
            break;
    }
}

void func_80016BC0(void)
{
    if (++Game_work.timer_0c > GAME_TIMER_MAX)
    {
        Game_work.timer_0c = GAME_TIMER_MAX;
    }
}

void func_80016BF4(void)
{
    if ((sint8)Game_work.routine_0 >= 3 && (sint8)Game_work.routine_0 != 6 && D_80098910 == 0)
    {
        if ((D_800C0C26 & 9) == 9)
        {
            if (Game_work.work08.words.value0a++ >= 61)
            {
                GAME_SCRATCH_MODE = 2;
                MojiTaskKill();
                func_80063BA8();
                func_80063EF0();
                func_800665E8();
                func_8001B314();
                func_8001B33C();
                func_8001D494(0, 1, 0);
                D_80098A70 = 0;
                func_80017C30(8);
                Sce_flag_off(0x1FE);
                *(uint16 *)&Code800133D8_work.routine_0 = 1;
                func_80012F78(func_80013420);
            }
        }
        else
        {
            Game_work.work08.words.value0a = 0;
        }
    }
}

void func_80016D0C(GAME_WORK *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_1++;
    }
}

void func_80016D38(GAME_WORK *wp)
{
    if (D_80098A72 == 0)
    {
        wp->routine_1++;
    }
}

void func_80016D64(void)
{
    while (D_80098788 != 0)
    {
        Thread_wait(1);
    }
    func_8001B314();
}

void func_80016DAC(void)
{
    POLY_FT4 *p;

    p                        = *CODE800133D8_PACKET_PTR;
    *CODE800133D8_PACKET_PTR = p + 1;
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
    AddPrim(&D_80098934->tag78, p);
}

void func_80016E90(void)
{
    POLY_FT4 *packet;
    POLY_F4 *p;

    packet = *CODE800133D8_PACKET_PTR;
    p      = (POLY_F4 *)packet;
    setPolyF4(p);
    p->x0 = 0;
    p->y0 = 0;
    p->x1 = 320;
    p->y1 = 0;
    p->x2 = 0;
    p->y2 = 120 - GAME_WORK_PTR->work08.aperture;
    p->x3 = 320;
    p->y3 = 120 - GAME_WORK_PTR->work08.aperture;
    p->r0 = 0;
    p->g0 = 0;
    p->b0 = 0;
    p->code &= ~2;
    AddPrim(&D_80098934->tag74, packet++);
    p = (POLY_F4 *)packet;
    setPolyF4(p);
    p->x0 = 0;
    p->y0 = 119 + GAME_WORK_PTR->work08.aperture;
    p->x1 = 320;
    p->y1 = 119 + GAME_WORK_PTR->work08.aperture;
    p->x2 = 0;
    p->y2 = 240;
    p->x3 = 320;
    p->y3 = 240;
    p->r0 = 0;
    p->g0 = 0;
    p->b0 = 0;
    p->code &= ~2;
    AddPrim(&D_80098934->tag74, packet++);
    *CODE800133D8_PACKET_PTR = packet;
}

void func_80016FD4(void)
{
    for (D_80098820 = D_8009F108; (uint32)D_80098820 < (uint32)&D_8009F108[16]; D_80098820++)
    {
        if (D_80098820->flags & D_80098820->active & 1)
        {
            GAME_TABLE_3C0[D_80098820->kind][D_80098820->routine](D_80098820);
        }
    }
}

void func_80017094(void)
{
    for (D_800989D0 = D_800C3580; (uint32)D_800989D0 < (uint32)&D_800C3580[4]; D_800989D0++)
    {
        if (D_800989D0->flags & D_800989D0->active & 1)
        {
            GAME_TABLE_5A4[D_800989D0->kind][D_800989D0->routine](D_800989D0);
        }
    }
}

void func_80017154(void)
{
    for (D_800988F8 = D_800BFB20; (uint32)D_800988F8 < (uint32)&D_800BFB20[16]; D_800988F8++)
    {
        if (D_800988F8->flags & D_800988F8->active & 1)
        {
            D_80089820[D_800988F8->kind](D_800988F8);
        }
    }
}

void func_80017210(void)
{
    for (D_800988F8 = D_8009CF88; (uint32)D_800988F8 < (uint32)&D_8009CF88[32]; D_800988F8++)
    {
        if (D_800988F8->flags & D_800988F8->active & 1)
        {
            if (D_800988F8->kind < 0x80)
            {
                GAME_TABLE_10C[D_800988F8->kind](D_800988F8);
            }
            else
            {
                ((GAME_FUNC_10C_RET)D_80089820[D_800988F8->kind])(D_800988F8);
            }
        }
    }
}

void func_800172F4(void)
{
    for (D_800988E4 = D_800A3B40; (uint32)D_800988E4 < (uint32)&D_800A3B40[64]; D_800988E4++)
    {
        if (D_800988E4->flags & D_800988E4->active & 1)
        {
            if (D_800988E4->kind < 0x80)
            {
                GAME_TABLE_48[D_800988E4->kind](D_800988E4);
            }
        }
    }
}

void func_800173B4(void)
{
    for (D_800988E4 = D_800A3B40; (uint32)D_800988E4 < (uint32)&D_800A3B40[64]; D_800988E4++)
    {
        if (D_800988E4->flags & D_800988E4->active & 1)
        {
            if (D_800988E4->kind >= 0x80)
            {
                D_80089858[D_800988E4->kind](D_800988E4);
            }
        }
    }
}

void func_80017478(void)
{
    for (D_800988F0 = D_800A2D08; (uint32)D_800988F0 < (uint32)&D_800A2D08[16]; D_800988F0++)
    {
        if (D_800988F0->flags & D_800988F0->active & 1)
        {
            GAME_TABLE_24[D_800988F0->kind](D_800988F0);
        }
    }
}

void func_80017528(void)
{
    for (D_80098924 = D_800BF118; (uint32)D_80098924 < (uint32)&D_800BF118[32]; D_80098924++)
    {
        if (D_80098924->flags & D_80098924->active & 1)
        {
            GAME_TABLE_50[D_80098924->kind](D_80098924);
        }
    }
}
