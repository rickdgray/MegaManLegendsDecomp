#include "common.h"
#include "cd.h"
#include "display.h"
#include "psyq/rand.h"
#include "game.h"
#include "moji.h"
#include "pad.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "debug.h"
#include "code_8001786C.h"
#include "code_8002E7A8.h"
#include "code_80037FB4.h"
#include "code_8004324C.h"
#include "code_8005C258.h"

// Small uninitialized statics (.sbss 0x800986E0-0x800986F8).
static uint8 D_800986E0[4];
static uint8 D_800986E4[4];
static uint8 D_800986E8[4];
static uint8 D_800986EC[4];
static sint32 D_800986F0[2];

// Pool variables (tentative definitions).
uint8 D_80098830;
uint8 D_800989D4;
// Defined here: func_80057E50 reaches [0] through $gp, which only this file's own small data gets.
// Four words, probably message number parameters: func_80057E50 prints [0] or [3], and [3]
// (0x800989EC) is lui-based, as a common's offset access is under ASPSX 2.56. A separate
// D_800989EC would have to be defined in a file that never uses it ($gp here); nothing anywhere
// (overlays included) touches [1] or [2].
sint32 D_800989E0[4];
sint32 D_80098AF4;
uint32 Moji_flag;
uint8 D_8009899C;
uint32 Moji_flag3;
uint8 D_800987F8;
uint8 D_80098850;
uint8 D_80098851;
uint8 D_80098930;
uint8 D_80098B6C;
uint32 D_80098B2C;
sint32 D_80098960;
sint32 D_800989A8;

// Called only from this file
void six_digit_set(sint32 pad, uint32 n, uint8 *dst);
void time_digit_set(uint32 frames, uint8 *dst);
void two_digit_set(uint32 n, uint8 *dst);

void Moji_init(void)
{
    MOJI_WORK *wp;
    sint16 i;

    Cd_read_comb(30);
    Cd_read_sync();
    for (i = 0; i < MOJI_WORK_MAX; i++)
    {
        // Only cmd_ptr_6C goes through a pointer: the target reaches it off &Moji_work[i] and
        // the other fields by array index.
        wp                      = &Moji_work[i];
        Moji_work[i].flags_0    = 0;
        wp->cmd_ptr_6C          = NULL;
        Moji_work[i].no_6       = i;
        Moji_work[i].cmd_top_48 = NULL;
    }
    D_80098B2C = 0;
    Moji_flag  = 0;
    D_80098960 = 0;
}

sint32 MojiTaskExec(sint32 task_no, uint8 *mes_file, sint32 mess_no)
{
    MOJI_WORK *wp;
    uint8 mes_no;

    mes_no = mess_no;
    if ((Moji_flag & 0x400000) || D_80098824 != 0)
    {
        return 0;
    }
    wp = &Moji_work[task_no];
    if (wp->flags_0 & 0x40000)
    {
        Cd_subcmd(0, CD_SUBCMD_XA_STOP, 0);
    }
    if (task_no != 4)
    {
        if (Moji_work[4].flags_0 & 0x40000)
        {
            Cd_subcmd(0, CD_SUBCMD_XA_STOP, 0);
        }
        Moji_work[4].flags_0   = 0;
        Moji_work[4].mes_no_C2 = 0xFF;
    }
    wp->flags_0   = 0x80000000;
    wp->unk_3F    = 1;
    wp->unk_3E    = 0;
    wp->mes_no_C2 = mes_no;
    wp->timer_4   = 0;
    wp->base_x_8  = 0;
    wp->unk_A     = 0;
    wp->unk_C     = 0;
    wp->unk_E     = 0;
    wp->unk_3C    = wp->unk_3E;
    if (mes_no != 0xFF)
    {
        wp->cmd_ptr_6C = wp->cmd_top_48 = mes_file + ((uint16 *)mes_file)[mes_no];
        wp->mes_file_44                 = mes_file;
    }
    else
    {
        wp->cmd_ptr_6C = wp->cmd_top_48 = mes_file;
        wp->mes_file_44                 = NULL;
    }
    wp->unk_3A     = 2;
    wp->ot_3D      = 3;
    wp->sel_71     = 0;
    wp->unk_72     = 0;
    wp->unk_73     = 0;
    wp->unk_7D     = 0;
    wp->unk_7E     = 0;
    wp->unk_7F     = 0;
    wp->unk_3B     = 0;
    wp->unk_78     = 0x80;
    wp->unk_70     = wp->unk_3E;
    wp->call_sp_C0 = 0;
    wp->call_sp_BE = 0;
    wp->scroll_38  = 0;
    wp->unk_BC     = 0;
    wp->mes_ptr_14 = wp->cmd_ptr_6C;
    Moji_flag |= 0x80000000 | (0x08000000 >> task_no);
    return 1;
}

void MojiTaskExec2(sint32 task_no, sint32 mess_no)
{
    MojiTaskExec(task_no, Msg_file, (uint8)mess_no);
}

void MojiTaskKill(void)
{
    MOJI_WORK *wp;
    uint32 flags;

    flags = 0;
    for (wp = Moji_work; wp < &Moji_work[MOJI_WORK_MAX]; wp++)
    {
        flags |= wp->flags_0;
        wp->flags_0   = 0;
        wp->mes_no_C2 = 0xFF;
    }
    if (flags & 0x40000)
    {
        Cd_subcmd(0, CD_SUBCMD_XA_STOP, 0);
    }
    Moji_flag = 0;
}

void func_80053AA4(uint8 n)
{
    MOJI_WORK *wp;

    wp = &Moji_work[n];
    if (wp->flags_0 & 0x40000)
    {
        Cd_subcmd(0, CD_SUBCMD_XA_STOP, 0);
    }
    wp->mes_no_C2 = 0xFF;
    wp->flags_0   = 0;
    Moji_flag &= 0xBFC1FFFF & ~(0x08000000 >> n);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80053B40);

void Moji_skip_1(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 1;
}

void Moji_skip_2(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 2;
}

void Moji_skip_3(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 3;
}

void Moji_skip_4(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 4;
}

void Moji_skip_5(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 5;
}

void Moji_skip_6(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 6;
}

void Moji_skip_7(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 7;
}

void Moji_skip_9(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 9;
}

void Moji_skip_11(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += 11;
}

sint32 func_800543B0(MOJI_WORK *wp)
{
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_800543C8(MOJI_WORK *wp)
{
    wp->cmd_ptr_6C += 2;
    return 1;
}

sint32 func_800543E0(MOJI_WORK *wp)
{
    wp->cmd_ptr_6C += 3;
    return 1;
}

sint32 func_800543F8(MOJI_WORK *wp)
{
    wp->cmd_ptr_6C += 5;
    return 1;
}

sint32 get_le16(uint8 *p)
{
    return p[0] | (p[1] << 8);
}

sint32 get_le32(uint8 *p)
{
    return p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
}

// Waits the command's 16-bit argument in frames, then skips it; with flags_0 bit 0x04000000 it
// runs the entry's D_8008AAC0 handler instead. Stops XA audio if the entry was playing it.
sint32 func_80054450(MOJI_WORK *wp)
{
    if (!(wp->flags_0 & 0x1000000))
    {
        wp->flags_0 |= 0x1000000;
        wp->timer_4 = get_le16(wp->cmd_ptr_6C + 1);
    }
    wp->flags_0 |= 0x10000000;
    if (wp->timer_4 <= 0)
    {
        wp->flags_0 |= 0x20000;
        if (wp->flags_0 & 0x4000000)
        {
            wp->flags_0 |= 0x100000;
            D_8008AAC0[wp->unk_7C](wp);
            return 0;
        }
        wp->flags_0 &= ~0x20000;
        wp->flags_0 &= ~0x81000000;
        wp->cmd_ptr_6C += 3;
        if (wp->flags_0 & 0x40000)
        {
            Cd_subcmd(0, CD_SUBCMD_XA_STOP, 0);
        }
        wp->mes_no_C2 = 0xFF;
        wp->flags_0 &= ~0x40000;
    }
    else
    {
        wp->timer_4 -= 1;
    }
    return 0;
}

sint32 func_8005457C(MOJI_WORK *wp)
{
    wp->unk_3B++;
    wp->cmd_ptr_6C += 1;
    return 1;
}

void func_8005459C(MOJI_WORK *mp)
{
    mp->pos_x_10 = mp->base_x_8;
    mp->pos_y_12 += 12;
    mp->unk_3E = mp->unk_70;
    mp->mes_ptr_14 += 1;
}

sint32 func_800545C8(MOJI_WORK *wp)
{
    if (!(wp->flags_0 & 0x01000000))
    {
        wp->flags_0 |= 0x01000000;
        wp->timer_4 = get_le16(wp->cmd_ptr_6C + 1);
    }
    wp->flags_0 |= 0x10000000;
    if (wp->timer_4 <= 0)
    {
        wp->flags_0 &= ~0x01000000;
        wp->timer_4 = 5;
        wp->sel_71  = 0;
        wp->unk_72  = 0;
        wp->unk_73  = 0;
        wp->cmd_ptr_6C += 3;
        wp->cmd_top_48 = wp->cmd_ptr_6C;
        wp->unk_3C     = wp->unk_3E;
        Moji_flag |= 0x200000;
    }
    else
    {
        wp->timer_4--;
    }
    return 0;
}

void func_80054694(MOJI_WORK *mp)
{
    mp->unk_3E = mp->mes_ptr_14[1];
    mp->mes_ptr_14 += 2;
}

sint32 func_800546B0(MOJI_WORK *wp)
{
    wp->timer_4 = wp->unk_3F = get_le16(wp->cmd_ptr_6C + 1);
    wp->cmd_ptr_6C += 3;
    return 1;
}

sint32 func_80054700(MOJI_WORK *wp)
{
    if (!(wp->flags_0 & 0x01000000))
    {
        wp->flags_0 |= 0x01000000;
        wp->timer_4 = get_le16(wp->cmd_ptr_6C + 1);
    }
    wp->flags_0 |= 0x10000000;
    if (wp->timer_4 <= 0)
    {
        wp->flags_0 &= ~0x01000000;
        wp->cmd_ptr_6C += 3;
    }
    else
    {
        wp->timer_4--;
    }
    return 0;
}

sint32 func_80054798(MOJI_WORK *wp)
{
    wp->base_x_8 = get_le16(wp->cmd_ptr_6C + 1);
    wp->unk_A    = get_le16(wp->cmd_ptr_6C + 3);
    wp->unk_7E   = wp->cmd_ptr_6C[5];
    wp->unk_7F   = wp->cmd_ptr_6C[6];
    wp->cmd_ptr_6C += 7;
    return 1;
}

sint32 func_80054804(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x10000000;
    if (!(Moji_work[wp->cmd_ptr_6C[1]].flags_0 & 0x80000000) || (Moji_work[wp->cmd_ptr_6C[1]].flags_0 & 0x00020000))
    {
        wp->cmd_ptr_6C += 2;
        return 1;
    }
    return 0;
}

sint32 func_80054874(MOJI_WORK *wp)
{
    Sound_call(get_le16(wp->cmd_ptr_6C + 1), 0, 0);
    wp->cmd_ptr_6C += 3;
    return 1;
}

sint32 func_800548C4(MOJI_WORK *wp)
{
    if (!(wp->flags_0 & 0x01000000))
    {
        wp->flags_0 |= 0x01000000;
        Cd_xa_play_id(get_le32(wp->cmd_ptr_6C + 1));
    }
    else if (func_8001D878())
    {
        wp->timer_4 = 5;
        Moji_flag |= 0x100000;
        wp->flags_0 = (wp->flags_0 | 0x40000) & ~0x01000000;
        wp->cmd_ptr_6C += 5;
    }
    wp->flags_0 |= 0x10000000;
    return 0;
}

sint32 func_8005497C(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 2;
    if (wp->mes_file_44 != NULL)
    {
        wp->cmd_ptr_6C = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[wp->cmd_ptr_6C[1]];
    }
    else
    {
        wp->cmd_ptr_6C = D_8008CACC[wp->cmd_ptr_6C[1]];
    }
    return 1;
}

void func_80054A04(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 2;
    if (mp->mes_file_44 != NULL)
    {
        mp->mes_ptr_14 = mp->mes_file_44 + ((uint16 *)mp->mes_file_44)[mp->mes_ptr_14[1]];
    }
    else
    {
        mp->mes_ptr_14 = D_8008CACC[mp->mes_ptr_14[1]];
    }
}

sint32 func_80054A84(MOJI_WORK *wp)
{
    wp->cmd_ptr_6C = wp->call_stk_4C[--wp->call_sp_C0];
    return 1;
}

void func_80054AB4(MOJI_WORK *mp)
{
    mp->mes_ptr_14 = mp->call_stk_18[--mp->call_sp_BE];
}

sint32 func_80054ADC(MOJI_WORK *wp)
{
    if (wp->flags_0 & 0x02000000)
    {
        wp->flags_0 &= ~0x02000000;
        wp->unk_7D = 0;
    }
    wp->unk_7C = wp->cmd_ptr_6C[1];
    D_8008AAC0[wp->unk_7C](wp);
    return 0;
}

void func_80054B4C(MOJI_WORK *mp)
{
    D_8008AB08[mp->unk_7C](mp);
}

sint32 func_80054B88(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x08000000;
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80054BAC(void)
{
    return 0;
}

sint32 func_80054BB4(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x00400800;
    wp->unk_BC = 0;
    wp->unk_72++;
    wp->cmd_ptr_6C += 3;
    return 1;
}

// A choice in a 2D grid: argument bytes 1 and 2 pack the choice to move to for each direction
// (left/right in byte 1's high/low nibble, up/down in byte 2's), PAD_* pressed or auto-repeated.
void func_80054BEC(MOJI_WORK *mp)
{
    sint16 old;

    mp->mes_ptr_14[3] = 0xED;
    mp->unk_78        = 0;
    if (mp->sel_71 == mp->unk_73 && !(mp->flags_0 & 0xC00000))
    {
        old = mp->sel_71;
        if (!(mp->btn_trg_BA & PAD_CROSS))
        {
            if (mp->btn_trg_BA & PAD_UP)
            {
                mp->sel_71 = mp->mes_ptr_14[2] >> 4;
                mp->unk_BC = 0;
            }
            else if ((*(uint32 *)&mp->btn_held_B8 & (PAD_UP << 16 | PAD_UP)) == PAD_UP)
            {
                if (mp->unk_BC >= 13)
                {
                    mp->sel_71 = mp->mes_ptr_14[2] >> 4;
                    mp->unk_BC = 12;
                }
                else
                {
                    mp->unk_BC++;
                }
            }
            else if (mp->btn_trg_BA & PAD_DOWN)
            {
                mp->sel_71 = mp->mes_ptr_14[2] & 0xF;
                mp->unk_BC = 0;
            }
            else if ((*(uint32 *)&mp->btn_held_B8 & (PAD_DOWN << 16 | PAD_DOWN)) == PAD_DOWN)
            {
                if (mp->unk_BC >= 13)
                {
                    mp->sel_71 = mp->mes_ptr_14[2] & 0xF;
                    mp->unk_BC = 12;
                }
                else
                {
                    mp->unk_BC++;
                }
            }
            else if (mp->btn_trg_BA & PAD_LEFT)
            {
                mp->sel_71 = mp->mes_ptr_14[1] >> 4;
                mp->unk_BC = 0;
            }
            else if ((*(uint32 *)&mp->btn_held_B8 & (PAD_LEFT << 16 | PAD_LEFT)) == PAD_LEFT)
            {
                if (mp->unk_BC >= 13)
                {
                    mp->sel_71 = mp->mes_ptr_14[1] >> 4;
                    mp->unk_BC = 12;
                }
                else
                {
                    mp->unk_BC++;
                }
            }
            else if (mp->btn_trg_BA & PAD_RIGHT)
            {
                mp->sel_71 = mp->mes_ptr_14[1] & 0xF;
                mp->unk_BC = 0;
            }
            else if ((*(uint32 *)&mp->btn_held_B8 & (PAD_RIGHT << 16 | PAD_RIGHT)) == PAD_RIGHT)
            {
                if (mp->unk_BC >= 13)
                {
                    mp->sel_71 = mp->mes_ptr_14[1] & 0xF;
                    mp->unk_BC = 12;
                }
                else
                {
                    mp->unk_BC++;
                }
            }
        }
        mp->mes_ptr_14[3] = 0x60;
        mp->unk_78 += 0x30;
        mp->cursor_74 = mp->mes_ptr_14 + 3;
        mp->flags_0 |= 0x800000;
        if (old != mp->sel_71)
        {
            Sound_call(0x81, 1, 0);
        }
    }
    mp->unk_78 += 0x50;
    mp->unk_73++;
    mp->mes_ptr_14 += 3;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80054E54);

void func_80055304(MOJI_WORK *mp)
{
    mp->mes_ptr_14 += mp->unk_72 + 2;
}

sint32 func_8005531C(MOJI_WORK *wp)
{
    wp->flags_0 &= ~0x08000000;
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80055344(MOJI_WORK *wp)
{
    uint8 *p;
    uint8 task_no;
    uint8 mes_no;

    p              = wp->cmd_ptr_6C;
    task_no        = p[1];
    mes_no         = p[2];
    wp->cmd_ptr_6C = p + 3;
    if (wp->mes_file_44 != NULL)
    {
        MojiTaskExec((sint8)task_no, wp->mes_file_44, mes_no);
    }
    else
    {
        MojiTaskExec((sint8)task_no, D_8008CACC[mes_no], 0xFF);
    }
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800553A8);

sint32 func_800553F0(MOJI_WORK *wp)
{
    Sce_flag_off((uint16)get_le16(wp->cmd_ptr_6C + 1));
    wp->cmd_ptr_6C += 3;
    return 1;
}

sint32 func_80055438(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (Sce_flag_test((uint16)get_le16(wp->cmd_ptr_6C + 1)))
    {
        mes_no = wp->cmd_ptr_6C[3];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[4];
    }
    if (mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 5;
    }
    else
    {
        wp->mes_no_C2  = mes_no;
        wp->cmd_top_48 = wp->cmd_ptr_6C = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
    }
    return 1;
}

sint32 func_800554E4(MOJI_WORK *wp)
{
    sint32 h;

    if (!(wp->flags_0 & 0x01000000))
    {
        wp->flags_0 |= 0x01000000;
        wp->timer_4 = get_le16(wp->cmd_ptr_6C + 1);
        wp->unk_3B++;
    }
    wp->flags_0 |= 0x10000000;
    h = wp->unk_3B * 12;
    if (--wp->timer_4 < 0)
    {
        if (wp->timer_4 * wp->unk_3A < -h)
        {
            wp->scroll_38 += h;
            wp->sel_71 = 0;
            wp->unk_72 = 0;
            wp->unk_73 = 0;
            wp->unk_3B = 0;
            wp->flags_0 &= ~0x01000000;
            wp->cmd_top_48 = wp->cmd_ptr_6C += 3;
            wp->unk_3C     = wp->unk_3E;
        }
        else
        {
            wp->scroll_38 -= wp->unk_3A;
        }
    }
    return 0;
}

void func_800555F4(MOJI_WORK *mp)
{
    mp->pos_x_10 += get_le16(mp->mes_ptr_14 + 1);
    mp->mes_ptr_14 += 3;
}

sint32 func_8005563C(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x20000000;
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80055660(MOJI_WORK *wp)
{
    wp->flags_0 &= ~0x20000000;
    wp->cmd_ptr_6C += 1;
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80055688);

sint32 func_800557B8(MOJI_WORK *wp)
{
    if (!(wp->flags_0 & 0x01000000))
    {
        wp->flags_0 |= 0x01000000;
        wp->timer_4 = get_le16(wp->cmd_ptr_6C + 1);
    }
    wp->flags_0 |= 0x10000000;
    if (wp->timer_4 <= 0 || !(wp->flags_0 & 0x00040000))
    {
        wp->timer_4 = 0;
        wp->flags_0 &= ~(0x10000000 | 0x01000000);
        wp->cmd_ptr_6C += 3;
        return 1;
    }
    wp->timer_4--;
    return 0;
}

sint32 func_80055868(MOJI_WORK *wp)
{
    VECTOR vec;
    SVECTOR pos;
    DEBUG_FADE *fp;
    PL_WORK *pl;

    fp = (DEBUG_FADE *)&D_800987B0;
    pl = &Player_work[0];
    if (!(wp->flags_0 & 0x01000000))
    {
        wp->flags_0 |= 0x01000000;
        pos    = *D_800987B8;
        vec.vx = D_800987B8->vx;
        vec.vy = D_800987B8->vy + (sint16)get_le16(wp->cmd_ptr_6C + 9);
        vec.vz = D_800987B8->vz;
        if (Scene_work.unk00 == 0)
        {
            func_80039FAC(&vec, (uint16)get_le16(wp->cmd_ptr_6C + 3),
                          Angle_xz_svector(&pos, &pl->pos) + (uint16)get_le16(wp->cmd_ptr_6C + 5),
                          D_800A396C + (uint16)get_le16(wp->cmd_ptr_6C + 7));
        }
        else
        {
            func_80039FFC(&vec, (uint16)get_le16(wp->cmd_ptr_6C + 3),
                          Angle_xz_svector(&pos, &pl->pos) + (uint16)get_le16(wp->cmd_ptr_6C + 5),
                          D_800A396C + (uint16)get_le16(wp->cmd_ptr_6C + 7));
        }
        wp->flags_0 |= 0x00010000;
        fp->mode_1 = get_le16(wp->cmd_ptr_6C + 1);
    }
    wp->flags_0 |= 0x10000000;
    if (func_8003A13C() == 0)
    {
        wp->flags_0 &= ~(0x10000000 | 0x01000000);
        wp->cmd_ptr_6C += 11;
        return 1;
    }
    return 0;
}

sint32 func_80055A78(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (Game_work.stage_no == wp->cmd_ptr_6C[1] && Game_work.area_no == wp->cmd_ptr_6C[2])
    {
        mes_no = wp->cmd_ptr_6C[3];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[4];
    }
    if (mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 5;
    }
    else
    {
        wp->mes_no_C2  = mes_no;
        wp->cmd_top_48 = wp->cmd_ptr_6C = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
    }
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80055B14);

sint32 func_80055BB0(MOJI_WORK *wp)
{
    if (wp->flags_0 & 0x04000000)
    {
        wp->flags_0 |= 0x00100000;
        D_8008AAC0[wp->unk_7C](wp);
        return 0;
    }
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80055C1C(MOJI_WORK *wp)
{
    if (wp->flags_0 & 0x00010000)
    {
        func_80039E18();
        wp->flags_0 &= ~0x00010000;
    }
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80055C80(MOJI_WORK *wp)
{
    *D_8008D0D4[wp->cmd_ptr_6C[1]] = wp->cmd_ptr_6C[2];
    wp->cmd_ptr_6C += 3;
    return 1;
}

sint32 func_80055CC4(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x00404000;
    wp->unk_BC = 0;
    wp->unk_72++;
    wp->cmd_ptr_6C += 7;
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80055CFC);

void func_800560D0(MOJI_WORK *mp)
{
    if (*D_8008D0D4[mp->mes_ptr_14[1]] == mp->mes_ptr_14[2])
    {
        mp->unk_78 = 0x80;
    }
    else
    {
        mp->unk_78 = 0x40;
    }
    mp->mes_ptr_14 += 3;
}

sint32 func_80056128(MOJI_WORK *wp)
{
    wp->unk_3B++;
    wp->cmd_ptr_6C += 2;
    return 1;
}

void func_80056148(MOJI_WORK *mp)
{
    mp->pos_x_10 = mp->base_x_8;
    mp->pos_y_12 += mp->mes_ptr_14[1];
    mp->unk_3E = mp->unk_70;
    mp->mes_ptr_14 += 2;
}

void func_80056180(MOJI_WORK *mp)
{
    mp->unk_78 = mp->mes_ptr_14[1];
    mp->mes_ptr_14 += 2;
}

sint32 func_8005619C(MOJI_WORK *wp)
{
    if (func_8005DA78(1) != 0)
    {
        wp->cmd_ptr_6C += 1;
        return 1;
    }
    return 0;
}

sint32 func_800561E8(MOJI_WORK *wp)
{
    if (Player_weapon_bullet_fill(1) != 0)
    {
        wp->cmd_ptr_6C += 1;
        return 1;
    }
    return 0;
}

sint32 func_80056234(MOJI_WORK *wp)
{
    if (func_8005DA1C(1) != 0)
    {
        wp->cmd_ptr_6C += 1;
        return 1;
    }
    return 0;
}

sint32 func_80056280(MOJI_WORK *wp)
{
    uint8 a;
    uint8 b;
    sint32 mes_no;

    a = func_8005DA1C(0);
    b = Player_weapon_bullet_fill(0);
    if (a == 0)
    {
        if (b == 0)
        {
            mes_no = wp->cmd_ptr_6C[1];
        }
        else
        {
            mes_no = wp->cmd_ptr_6C[2];
        }
    }
    else if (b == 0)
    {
        mes_no = wp->cmd_ptr_6C[3];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[4];
    }
    wp->timer_4 = 5;
    if ((uint8)mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 5;
    }
    else
    {
        wp->mes_no_C2 = mes_no;
        if (wp->mes_file_44 != NULL)
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[(uint8)mes_no];
        }
        else
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = D_8008CACC[(uint8)mes_no];
        }
        wp->unk_3E = 0;
        wp->unk_3C = 0;
        wp->unk_72 = 0;
    }
    return 1;
}

void func_800563A8(MOJI_WORK *mp)
{
    if (D_80098850 == 0)
    {
        D_80098830 = D_800BE2F8[D_8009899C + mp->sel_71];
    }
    else
    {
        D_80098830 = D_800BE2F8[D_8009899C + mp->sel_71] + 0x20;
    }
    if (mp->flags_0 & 0x2000)
    {
        if (mp->mes_file_44 != NULL)
        {
            MojiTaskExec(mp->mes_ptr_14[1], mp->mes_file_44, (uint8)(mp->mes_ptr_14[2] + D_800BE2F8[D_8009899C + mp->sel_71]));
        }
        else
        {
            MojiTaskExec(mp->mes_ptr_14[1], D_8008CACC[mp->mes_ptr_14[2] + D_800BE2F8[D_8009899C + mp->sel_71]], 0xFF);
        }
    }
    mp->mes_ptr_14 += 3;
}

void func_800564C8(MOJI_WORK *mp)
{
    if (mp->mes_file_44 != NULL)
    {
        MojiTaskExec(mp->mes_ptr_14[1], mp->mes_file_44, (uint8)(mp->mes_ptr_14[2] + mp->sel_71));
    }
    else
    {
        MojiTaskExec(mp->mes_ptr_14[1], D_8008CACC[mp->mes_ptr_14[2] + mp->sel_71], 0xFF);
    }
    mp->mes_ptr_14 += 3;
}

void func_80056558(MOJI_WORK *mp)
{
    if (mp->mes_file_44 != NULL)
    {
        MojiTaskExec(mp->mes_ptr_14[1], mp->mes_file_44, (uint8)(mp->mes_ptr_14[2] + D_800BE2F8[mp->sel_71 + D_8009899C]));
    }
    else
    {
        // The target loads this entry signed (lb), unlike every other use of D_800BE2F8.
        MojiTaskExec(mp->mes_ptr_14[1], D_8008CACC[mp->mes_ptr_14[2] + (sint8)D_800BE2F8[mp->sel_71 + D_8009899C]], 0xFF);
    }
    mp->mes_ptr_14 += 3;
}

// Parts ids are 1-based (0 = empty), so id n is message n - 1.
void func_80056610(MOJI_WORK *mp)
{
    if (mp->mes_file_44 != NULL)
    {
        MojiTaskExec(mp->mes_ptr_14[1], mp->mes_file_44,
                     (uint8)(mp->mes_ptr_14[2] + Player_work[0].rb_parts_sort_data[mp->sel_71 + D_8009899C] - 1));
    }
    else
    {
        MojiTaskExec(mp->mes_ptr_14[1], D_8008CACC[mp->mes_ptr_14[2] + Player_work[0].rb_parts_sort_data[mp->sel_71 + D_8009899C] - 1],
                     0xFF);
    }
    mp->mes_ptr_14 += 3;
}

void func_800566CC(MOJI_WORK *mp)
{
    if (mp->mes_file_44 != NULL)
    {
        MojiTaskExec(mp->mes_ptr_14[1], mp->mes_file_44, (uint8)(mp->mes_ptr_14[2] + Player_work[0].rb_parts_equip_data[mp->sel_71] - 1));
    }
    else
    {
        MojiTaskExec(mp->mes_ptr_14[1], D_8008CACC[mp->mes_ptr_14[2] + Player_work[0].rb_parts_equip_data[mp->sel_71] - 1], 0xFF);
    }
    mp->mes_ptr_14 += 3;
}

sint32 func_80056778(MOJI_WORK *wp)
{
    wp->cmd_ptr_6C[5] = D_800987F8;
    if (D_80098850 == 0)
    {
        D_80098830 = D_800BE2F8[D_8009899C + wp->unk_72];
    }
    else
    {
        D_80098830 = D_800BE2F8[D_8009899C + wp->unk_72] + 0x20;
    }
    wp->flags_0 |= 0x00402000;
    wp->unk_BC = 0;
    wp->unk_72++;
    wp->cmd_ptr_6C += 3;
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80056820);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80056D10);

sint32 func_800570B0(MOJI_WORK *wp)
{
    uint8 *p;
    uint8 task_no;
    uint8 mes_no;
    uint8 flag;

    p              = wp->cmd_ptr_6C;
    task_no        = p[2];
    mes_no         = p[3];
    flag           = p[1];
    wp->cmd_ptr_6C = p + 4;
    if ((uint8)Moji_flag == flag)
    {
        if (wp->mes_file_44 != NULL)
        {
            MojiTaskExec((sint8)task_no, wp->mes_file_44, mes_no);
        }
        else
        {
            MojiTaskExec((sint8)task_no, D_8008CACC[mes_no], 0xFF);
        }
    }
    return 1;
}

sint32 func_80057124(MOJI_WORK *wp)
{
    wp->money_40 = Game_work.money;
    wp->cmd_ptr_6C += 1;
    return 1;
}

void func_80057144(MOJI_WORK *mp)
{
    mp->money_40 = Game_work.money;
    six_digit_set(0, mp->money_40, ++mp->mes_ptr_14);
}

sint32 func_80057184(MOJI_WORK *wp)
{
    uint8 *p;
    uint8 var_no;
    uint8 val;
    uint8 task_no;
    uint8 mes_no;

    p              = wp->cmd_ptr_6C;
    var_no         = p[1];
    val            = p[2];
    task_no        = p[3];
    mes_no         = p[4];
    wp->cmd_ptr_6C = p + 5;
    if (*D_8008D0D4[var_no] == val)
    {
        if (wp->mes_file_44 != NULL)
        {
            MojiTaskExec((sint8)task_no, wp->mes_file_44, mes_no);
        }
        else
        {
            MojiTaskExec((sint8)task_no, D_8008CACC[mes_no], 0xFF);
        }
    }
    return 1;
}

sint32 func_8005721C(MOJI_WORK *wp)
{
    D_80098930 = D_800BE2F8[D_8009899C + wp->sel_71] + wp->cmd_ptr_6C[1];
    if (!Sce_flag_test(0x2EE) && Money_check(-D_8008FD3C[D_80098930]))
    {
        D_80098B6C = 1;
    }
    else
    {
        D_80098B6C = 0;
    }
    wp->cmd_ptr_6C += 2;
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800572C8);

// Jumps to a message: after code 0xD5, one picked at random from its count byte's list, else the
// argument byte's. 0xFF skips the command.
sint32 func_80057408(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (wp->cmd_ptr_6C[0] == 0xD5)
    {
        mes_no = wp->cmd_ptr_6C[rand() % wp->cmd_ptr_6C[1] + 2];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[2];
    }
    if (mes_no == 0xFF)
    {
        if (wp->cmd_ptr_6C[0] == 0xD5)
        {
            wp->cmd_ptr_6C += wp->cmd_ptr_6C[1] + 2;
        }
        else
        {
            wp->cmd_ptr_6C += 3;
        }
    }
    else
    {
        wp->mes_no_C2 = mes_no;
        if (wp->mes_file_44 != NULL)
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
        }
        else
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = D_8008CACC[mes_no];
        }
        wp->unk_3E = 0;
        wp->unk_3C = 0;
        wp->unk_72 = 0;
    }
    return 1;
}

void func_8005753C(MOJI_WORK *mp)
{
    if (mp->mes_ptr_14[0] == 0xD5)
    {
        mp->mes_ptr_14 += mp->mes_ptr_14[1] + 2;
    }
    else
    {
        mp->mes_ptr_14 += 3;
    }
}

void func_80057574(MOJI_WORK *mp)
{
    if (Sce_flag_test(0x2EE) != 0)
    {
        if (D_80098850 == 0)
        {
            six_digit_set(0, D_8008FD3C[D_800BE2F8[D_8009899C + mp->unk_73 - 1]] >> 2, mp->mes_ptr_14 + 1);
        }
        else
        {
            six_digit_set(0, D_8008FD7C[D_800BE2F8[D_8009899C + mp->unk_73 - 1]] >> 2, mp->mes_ptr_14 + 1);
        }
    }
    else if (D_80098850 == 0)
    {
        six_digit_set(0, D_8008FD3C[D_800BE2F8[D_8009899C + mp->unk_73 - 1]], mp->mes_ptr_14 + 1);
    }
    else
    {
        six_digit_set(0, D_8008FD7C[D_800BE2F8[D_8009899C + mp->unk_73 - 1]], mp->mes_ptr_14 + 1);
    }
    mp->mes_ptr_14 += 1;
}

sint32 func_800576C4(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 1;
    wp->cmd_ptr_6C                    = D_8008CBA4[D_80098830];
    return 1;
}

void func_80057708(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 1;
    mp->mes_ptr_14                    = D_8008CBA4[D_80098830];
}

sint32 func_80057744(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (Game_work.unk07D == Game_work.unk07C)
    {
        mes_no = wp->cmd_ptr_6C[1];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[2];
    }
    if (mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 3;
    }
    else
    {
        wp->mes_no_C2 = mes_no;
        if (wp->mes_file_44 != NULL)
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
        }
        else
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = D_8008CACC[mes_no];
        }
        wp->unk_3E = 0;
        wp->unk_3C = 0;
        wp->unk_72 = 0;
    }
    return 1;
}

sint32 func_800577FC(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (Money_check(-((Game_work.unk07D - Game_work.unk07C) * 10)) == 0)
    {
        mes_no = wp->cmd_ptr_6C[1];
    }
    else if (Game_work.unk060 >= 0x80 && Money_check(-1) == 0)
    {
        mes_no = wp->cmd_ptr_6C[3];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[2];
    }
    if (mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 4;
    }
    else
    {
        wp->mes_no_C2 = mes_no;
        if (wp->mes_file_44 != NULL)
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
        }
        else
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = D_8008CACC[mes_no];
        }
        wp->unk_3E = 0;
        wp->unk_3C = 0;
        wp->unk_72 = 0;
    }
    return 1;
}

sint32 func_80057924(MOJI_WORK *wp)
{
    if (wp->cmd_ptr_6C[1] == 0)
    {
        Money_add(-((Game_work.unk07D - Game_work.unk07C) * 10), 0, 0);
        Game_work.unk07C = Game_work.unk07D;
    }
    else
    {
        Money_add(-Game_work.money, 0, 0);
        Game_work.unk07C = Game_work.unk07D;
    }
    wp->cmd_ptr_6C += 2;
    return 1;
}

void func_800579D8(MOJI_WORK *mp)
{
    six_digit_set(1, (Game_work.unk07D - Game_work.unk07C) * 10, ++mp->mes_ptr_14);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057A24);

void func_80057A94(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 1;
    mp->mes_ptr_14                    = D_8008CBA4[D_80098830];
}

sint32 func_80057AD0(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 2;
    wp->cmd_ptr_6C                    = D_8008CBA4[wp->cmd_ptr_6C[1]];
    return 1;
}

void func_80057B24(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 2;
    mp->mes_ptr_14                    = D_8008CBA4[mp->mes_ptr_14[1]];
}

sint32 func_80057B70(MOJI_WORK *wp)
{
    Money_add(D_80098AF4, 0, 0);
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80057BB4(MOJI_WORK *wp)
{
    Money_add(-D_80098AF4, 0, 0);
    wp->cmd_ptr_6C += 1;
    return 1;
}

void func_80057BFC(MOJI_WORK *mp)
{
    six_digit_set(1, D_80098AF4, ++mp->mes_ptr_14);
}

sint32 func_80057C2C(MOJI_WORK *wp)
{
    uint8 *flag;
    uint32 i;
    sint32 n;
    uint8 mes_no;

    flag = &Sce_flag[0x63];
    n    = 0;
    for (i = 0; i < 8; i++)
    {
        if (*flag & (0x80 >> i))
        {
            D_800BE2F8[n++] = i;
        }
    }
    D_800BE2F8[n] = 8;
    mes_no        = wp->cmd_ptr_6C[n];
    if (mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 9;
    }
    else
    {
        wp->mes_no_C2 = mes_no;
        if (wp->mes_file_44 != NULL)
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
        }
        else
        {
            wp->cmd_ptr_6C = wp->cmd_top_48 = D_8008CACC[mes_no];
        }
        wp->unk_3E = 0;
        wp->unk_3C = 0;
        wp->unk_72 = 0;
    }
    return 1;
}

sint32 func_80057D00(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 2;
    wp->cmd_ptr_6C                    = D_8008CE10[D_800BE2F8[wp->cmd_ptr_6C[1]]];
    return 1;
}

void func_80057D60(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 2;
    mp->mes_ptr_14                    = D_8008CE10[D_800BE2F8[mp->mes_ptr_14[1]]];
}

sint32 func_80057DB8(MOJI_WORK *wp)
{
    sint32 idx;

    idx = Moji_flag & 0xFF;
    Moji_flag &= ~0xFF;
    Moji_flag |= D_800BE2F8[idx];
    wp->cmd_ptr_6C += 1;
    return 1;
}

sint32 func_80057DF4(MOJI_WORK *wp)
{
    uint32 i;

    for (i = 0; i < 3; i++)
    {
        wp->cmd_ptr_6C[i + 1] = Game_work.records_84.h[D_800989D4][i + 2];
    }
    wp->cmd_ptr_6C += 1;
    return 1;
}

void func_80057E50(MOJI_WORK *mp)
{
    uint8 *p;

    p = mp->mes_ptr_14;
    if (p[1] == 0)
    {
        time_digit_set(D_800989E0[0], p + 3);
    }
    else if (p[1] == 1)
    {
        time_digit_set(Game_work.records_84.rec[p[2]].id_0, p + 3);
    }
    else if (p[1] == 2)
    {
        two_digit_set(Game_work.records_84.rec[p[2]].id_0, p + 8);
        mp->mes_ptr_14[3] = 0xC6;
        mp->mes_ptr_14[4] = 0xC6;
        mp->mes_ptr_14[5] = 0xC6;
        mp->mes_ptr_14[6] = 0xC6;
        mp->mes_ptr_14[7] = 0xC6;
    }
    else if (p[1] == 3)
    {
        two_digit_set(D_800989E0[3], p + 8);
        mp->mes_ptr_14[3] = 0xC6;
        mp->mes_ptr_14[4] = 0xC6;
        mp->mes_ptr_14[5] = 0xC6;
        mp->mes_ptr_14[6] = 0xC6;
        mp->mes_ptr_14[7] = 0xC6;
    }
    else if (p[1] == 4)
    {
        // Game_work.timer_14 as hh:mm:ss (func_80067B7C writes the digits).
        mp->mes_ptr_14[3]  = D_80097FF4;
        mp->mes_ptr_14[4]  = D_80097FF5;
        mp->mes_ptr_14[5]  = D_80097FF6;
        mp->mes_ptr_14[6]  = D_80097FF7;
        mp->mes_ptr_14[7]  = D_80097FF8;
        mp->mes_ptr_14[8]  = D_80097FF9;
        mp->mes_ptr_14[9]  = D_80097FFA;
        mp->mes_ptr_14[10] = D_80097FFB;
    }
    mp->mes_ptr_14 += 3;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057FF8);

sint32 func_8005851C(MOJI_WORK *wp)
{
    uint16 *val;
    sint8 *idx;
    uint8 *src;
    uint8 n;
    sint32 i;

    n   = wp->cmd_ptr_6C[1];
    val = D_8008D8EC[D_800989D4][n];
    if (D_800989D4 != 0)
    {
        idx = &Player_work[0].rec[D_800989D4 + 1].idx[n];
    }
    else
    {
        idx = &Player_work[0].rec[0].idx[n];
    }
    if (val[0] == 0)
    {
        src = D_80097FEC;
    }
    else if (val[*idx] == 0)
    {
        src = D_80097FE4;
    }
    else
    {
        D_80097FE2[0] = D_8008D028[*idx + 1];
        src           = D_80097FDC;
    }
    for (i = 0; i < 8; i++)
    {
        wp->cmd_ptr_6C[i + 2] = src[i];
    }
    wp->cmd_ptr_6C += 2;
    return 1;
}

sint32 func_8005861C(MOJI_WORK *wp)
{
    uint16 *val;
    sint8 *idx;
    uint8 mes_no;

    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 5;
    val                               = D_8008D8EC[D_800989D4][wp->cmd_ptr_6C[1]];
    if (D_800989D4 != 0)
    {
        idx = &Player_work[0].rec[D_800989D4 + 1].idx[wp->cmd_ptr_6C[1]];
    }
    else
    {
        idx = &Player_work[0].rec[0].idx[wp->cmd_ptr_6C[1]];
    }
    if (val[0] == 0)
    {
        mes_no = wp->cmd_ptr_6C[2];
        Moji_flag &= ~0x20000;
    }
    else if (val[*idx] == 0)
    {
        mes_no = wp->cmd_ptr_6C[3];
        Moji_flag &= ~0x20000;
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[4];
        Moji_flag |= 0x20000;
    }
    wp->mes_no_C2  = mes_no;
    wp->cmd_ptr_6C = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
    return 1;
}

void func_80058740(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 5;
    mp->mes_ptr_14                    = mp->mes_file_44 + ((uint16 *)mp->mes_file_44)[mp->mes_no_C2];
}

sint32 func_80058788(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x00400800;
    wp->unk_BC = 0;
    wp->unk_72++;
    wp->cmd_ptr_6C += 5;
    Moji_flag3 &= ~(0x20000 << (wp - Moji_work));
    return 1;
}

// A choice of up to four neighbours: argument bytes 1-4 are the choices to move to for PAD_UP,
// PAD_DOWN, PAD_LEFT and PAD_RIGHT, pressed or auto-repeated. Moji_flag3 bit 17 + (entry index)
// marks a move this frame.
void func_800587F8(MOJI_WORK *mp)
{
    uint32 held;
    uint32 trg;
    sint16 old;

    mp->mes_ptr_14[5] = 0xED;
    mp->unk_78        = 0;
    if (mp->sel_71 == mp->unk_73 && !(mp->flags_0 & 0xC00000))
    {
        Moji_flag3 &= ~(0x20000 << (mp - Moji_work));
        old = mp->sel_71;
        if (!(Moji_work[0].flags_0 & 0x80000000) && !((trg = mp->btn_trg_BA) & PAD_CROSS))
        {
            if (trg & PAD_UP)
            {
                mp->sel_71 = mp->mes_ptr_14[1];
                mp->unk_BC = 0;
            }
            else if (((held = *(uint32 *)&mp->btn_held_B8) & (PAD_UP << 16 | PAD_UP)) == PAD_UP)
            {
                if (mp->unk_BC < 13)
                {
                    mp->unk_BC++;
                }
                else
                {
                    mp->sel_71 = mp->mes_ptr_14[1];
                    mp->unk_BC = 12;
                }
            }
            else if (trg & PAD_DOWN)
            {
                mp->sel_71 = mp->mes_ptr_14[2];
                mp->unk_BC = 0;
            }
            else if ((held & (PAD_DOWN << 16 | PAD_DOWN)) == PAD_DOWN)
            {
                if (mp->unk_BC < 13)
                {
                    mp->unk_BC++;
                }
                else
                {
                    mp->sel_71 = mp->mes_ptr_14[2];
                    mp->unk_BC = 12;
                }
            }
            else if (trg & PAD_LEFT)
            {
                mp->sel_71 = mp->mes_ptr_14[3];
                mp->unk_BC = 0;
            }
            else if ((held & (PAD_LEFT << 16 | PAD_LEFT)) == PAD_LEFT)
            {
                if (mp->unk_BC < 13)
                {
                    mp->unk_BC++;
                }
                else
                {
                    mp->sel_71 = mp->mes_ptr_14[3];
                    mp->unk_BC = 12;
                }
            }
            else if (trg & PAD_RIGHT)
            {
                mp->sel_71 = mp->mes_ptr_14[4];
                mp->unk_BC = 0;
            }
            else if ((held & (PAD_RIGHT << 16 | PAD_RIGHT)) == PAD_RIGHT)
            {
                if (mp->unk_BC >= 13)
                {
                    mp->sel_71 = mp->mes_ptr_14[4];
                    mp->unk_BC = 12;
                }
                else
                {
                    mp->unk_BC++;
                }
            }
        }
        if (!(Moji_flag & 0x20000))
        {
            mp->mes_ptr_14[5] = 0x60;
        }
        else
        {
            mp->mes_ptr_14[5] = 0xED;
        }
        mp->unk_78 += 0x30;
        mp->cursor_74 = mp->mes_ptr_14 + 5;
        mp->flags_0 |= 0x800000;
        if (old != mp->sel_71)
        {
            Sound_call(0x81, 1, 0);
            Moji_flag3 |= 0x20000 << (mp - Moji_work);
        }
    }
    mp->unk_78 += 0x50;
    mp->unk_73++;
    mp->mes_ptr_14 += 5;
}

sint32 func_80058AEC(MOJI_WORK *wp)
{
    if (!(wp->flags_0 & 0x1000000))
    {
        wp->flags_0 = (wp->flags_0 | 0x1000000) & ~0x8000;
        wp->timer_4 = 5;
    }
    wp->flags_0 &= ~0x400000;
    if (Moji_flag & 0x8000000)
    {
        Moji_flag |= 0x20000;
    }
    else
    {
        Moji_flag &= ~0x20000;
    }
    if (wp->timer_4 <= 0)
    {
        if (wp->btn_trg_BA & PAD_CROSS)
        {
            Moji_flag &= ~0xFF;
            // The target reads sel_71 unsigned here (lbu), signed everywhere else.
            Moji_flag |= 0x40000000 | (uint8)wp->sel_71;
        }
        else if (wp->btn_trg_BA & PAD_TRIANGLE)
        {
            Moji_flag &= ~0xFF;
            Moji_flag |= 0x20000000 | ((wp->unk_72 - 1) & 0xFF);
        }
    }
    else
    {
        wp->timer_4--;
    }
    wp->unk_78 = 0x80;
    return 0;
}

sint32 func_80058C08(MOJI_WORK *wp)
{
    wp->ot_3D = wp->cmd_ptr_6C[1];
    wp->cmd_ptr_6C += 2;
    return 1;
}

sint32 func_80058C28(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 3;
    if (Sce_flag_test((uint16)get_le16(wp->cmd_ptr_6C + 1)))
    {
        wp->cmd_ptr_6C = D_8008BAA4[(uint16)get_le16(wp->cmd_ptr_6C + 1)];
    }
    else
    {
        wp->cmd_ptr_6C = D_8008CE58;
    }
    return 1;
}

void func_80058CC8(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 3;
    if (Sce_flag_test((uint16)get_le16(mp->mes_ptr_14 + 1)))
    {
        mp->mes_ptr_14 = D_8008BAA4[(uint16)get_le16(mp->mes_ptr_14 + 1)];
    }
    else
    {
        mp->mes_ptr_14 = D_8008CE58;
    }
}

void func_80058D64(MOJI_WORK *mp)
{
    mp->pos_x_10 = get_le16(mp->mes_ptr_14 + 1);
    mp->pos_y_12 = get_le16(mp->mes_ptr_14 + 3);
    mp->mes_ptr_14 += 5;
}

sint32 func_80058DB4(MOJI_WORK *wp)
{
    sint32 i;

    D_8009899C = 0;
    wp->cmd_ptr_6C += 1;
    for (i = 0; i < 0x80; i++)
    {
        D_800BE2F8[i] = 0xFF;
    }
    return 1;
}

void func_80058DEC(MOJI_WORK *mp)
{
    uint8 *flag;
    sint32 i;

    flag       = &Sce_flag[0xA8];
    D_800989A8 = 0;
    for (i = 0; i < 0x40; i++)
    {
        if (flag[i >> 3] & (0x80 >> (i & 7)))
        {
            D_800BE2F8[D_800989A8] = i;
            D_800989A8++;
        }
    }
    for (i = D_800989A8; i < 0x80; i++)
    {
        D_800BE2F8[i] = 0xFF;
    }
    mp->mes_ptr_14 += 1;
}

sint32 func_80058EA0(MOJI_WORK *wp)
{
    wp->flags_0 |= 0x00402800;
    wp->unk_BC = 0;
    wp->unk_72++;
    wp->cmd_ptr_6C += 5;
    D_80098851 = 0xFF;
    Moji_flag3 &= ~(0x20000 << (wp - Moji_work));
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80058F18);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800592FC);

sint32 func_800594CC(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 1;
    wp->cmd_ptr_6C                    = D_8008CCA4[((sint8 *)D_800BE2F8)[D_8009899C + wp->unk_72 - 1]];
    return 1;
}

void func_80059530(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 1;
    mp->mes_ptr_14                    = D_8008CCA4[((sint8 *)D_800BE2F8)[D_8009899C + mp->unk_73 - 1]];
}

// The id bytes are read signed (lb), as in func_80059660.
sint32 func_8005958C(MOJI_WORK *wp)
{
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 3;
    if (wp->cmd_ptr_6C[1] != 0)
    {
        wp->cmd_ptr_6C = D_8008CBA4[(sint8)Player_work[0].rb_parts_sort_data[wp->cmd_ptr_6C[2] + D_8009899C] - 1];
    }
    else
    {
        wp->cmd_ptr_6C[-1] = 0;
        if ((Moji_flag & 0x20000) && wp->cmd_ptr_6C[2] == wp->sel_71)
        {
            wp->cmd_ptr_6C[-1] = 3;
        }
        wp->cmd_ptr_6C = D_8008CBA4[(sint8)Player_work[0].rb_parts_equip_data[wp->cmd_ptr_6C[2]] - 1];
    }
    return 1;
}

// The id bytes are read signed (lb); typing the fields sint8 breaks Sce_flag_off.
void func_80059660(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 3;
    if (mp->mes_ptr_14[1] != 0)
    {
        mp->mes_ptr_14 = D_8008CBA4[(sint8)Player_work[0].rb_parts_sort_data[mp->mes_ptr_14[2] + D_8009899C] - 1];
    }
    else
    {
        mp->mes_ptr_14[-1] = 0;
        if ((Moji_flag & 0x20000) && mp->mes_ptr_14[3] == mp->sel_71)
        {
            mp->mes_ptr_14[-1] = 3;
        }
        mp->mes_ptr_14 = D_8008CBA4[(sint8)Player_work[0].rb_parts_equip_data[mp->mes_ptr_14[2]] - 1];
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80059728);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800598C8);

// Lists in D_800BE2F8 the entries of D_8008AF00 whose Game_work value is below its maximum (the
// first four only once their scene flag is set), ends the list with 6, and jumps to message
// (argument byte + 6 - count).
sint32 func_80059B44(MOJI_WORK *wp)
{
    sint32 n;
    sint32 mes_no;

    n = 0;
    if (Sce_flag_test(0x23D) != 0 && Game_work.unk028[0] != 500)
    {
        D_800BE2F8[n++] = 0;
    }
    if (Sce_flag_test(0x23E) != 0 && Game_work.unk028[1] != 200)
    {
        D_800BE2F8[n++] = 1;
    }
    if (Sce_flag_test(0x23F) != 0 && Game_work.unk028[2] != 250)
    {
        D_800BE2F8[n++] = 2;
    }
    if (Sce_flag_test(0x240) != 0 && Game_work.unk028[3] != 200)
    {
        D_800BE2F8[n++] = 3;
    }
    if (Game_work.unk062[4] * 150 != Game_work.unk028[4])
    {
        D_800BE2F8[n++] = 5;
    }
    if (Game_work.unk062[5] * 180 != Game_work.unk028[5])
    {
        D_800BE2F8[n++] = 4;
    }
    D_800BE2F8[n] = 6;
    mes_no        = wp->cmd_ptr_6C[1] + 6;
    mes_no -= n;
    wp->mes_no_C2  = (uint8)mes_no;
    wp->cmd_ptr_6C = wp->cmd_top_48 = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[(uint8)mes_no];
    wp->unk_3E                      = 0;
    wp->unk_3C                      = 0;
    wp->unk_72                      = 0;
    return 1;
}

#ifdef NON_MATCHING
// Only the else branch differs: the target reuses i * 4 (computed for D_8008AF00[i]) for the word
// address; this recomputes it there, which shifts registers. Tried: uint8/uint32/sint32 i,
// [9 - i] indexing (adds 9 separately), a single call with ?:.
sint32 func_80059D20(MOJI_WORK *wp)
{
    sint32 n;
    uint32 i;
    sint32 val;

    n   = wp->cmd_ptr_6C[1];
    i   = D_800BE2F8[n];
    val = D_8008AF00[i];
    if (i < 4)
    {
        six_digit_set(0, val - Game_work.unk028[i], wp->cmd_ptr_6C + 7);
    }
    else
    {
        six_digit_set(0, (&Game_work.unk062[9])[-i] * val - (&Game_work.unk028[9])[-i], wp->cmd_ptr_6C + 7);
    }
    wp->call_stk_4C[wp->call_sp_C0++] = wp->cmd_ptr_6C + 2;
    wp->cmd_ptr_6C                    = D_8008CE5C[D_800BE2F8[n]];
    return 1;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80059D20);
#endif

void func_80059E24(MOJI_WORK *mp)
{
    sint32 idx;

    idx                               = mp->mes_ptr_14[1];
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 2;
    mp->mes_ptr_14                    = D_8008CE5C[D_800BE2F8[idx]];
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80059E74);

sint32 func_8005A598(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (wp->cmd_ptr_6C[1] <= Game_work.unk060 && Game_work.unk060 <= wp->cmd_ptr_6C[2])
    {
        mes_no = wp->cmd_ptr_6C[3];
    }
    else
    {
        mes_no = wp->cmd_ptr_6C[4];
    }
    if (mes_no == 0xFF)
    {
        wp->cmd_ptr_6C += 5;
    }
    else
    {
        wp->mes_no_C2  = mes_no;
        wp->cmd_top_48 = wp->cmd_ptr_6C = wp->mes_file_44 + ((uint16 *)wp->mes_file_44)[mes_no];
    }
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005A634);

void func_8005A858(MOJI_WORK *mp)
{
    mp->pos_x_10 += 12;
    mp->mes_ptr_14 += 1;
}

// Window kind 0 (D_8008AAC0[0]): opens the window from a flat line, unk_85 pixels a frame each way
// (state 0 sets it up, state 1 opens), and state 2 closes it.
void func_8005A874(MOJI_WORK *wp)
{
    switch (wp->unk_7D)
    {
        case 0:
            wp->unk_85 = 8;
            wp->flags_0 |= 0x14000000;
            wp->unk_80 = wp->flags_0 & 0x08000000;
            wp->flags_0 |= 0x08000000;
            wp->unk_B6 = wp->unk_B4 = wp->cmd_ptr_6C[2];
            wp->unk_7D++;
            wp->corner_88[0].vy = wp->unk_7F * 6;
            wp->corner_88[1].vy = wp->unk_7F * 6;
            wp->corner_88[2].vy = wp->unk_7F * 6;
            wp->corner_88[3].vy = wp->unk_7F * 6;
            wp->corner_88[0].vx = -wp->unk_B4;
            wp->corner_88[1].vx = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[2].vx = -wp->unk_B4;
            wp->corner_88[3].vx = wp->unk_B4 + wp->unk_7E * 12;
            break;
        case 1:
            wp->flags_0 |= 0x10000000;
            wp->corner_88[0].vy -= wp->unk_85;
            wp->corner_88[1].vy -= wp->unk_85;
            wp->corner_88[2].vy += wp->unk_85;
            wp->corner_88[3].vy += wp->unk_85;
            if (wp->unk_A + wp->corner_88[0].vy <= wp->unk_A - wp->unk_B6)
            {
                Moji_flag |= 0x200000;
                wp->corner_88[0].vx = -wp->unk_B4;
                wp->corner_88[0].vy = -wp->unk_B6;
                wp->corner_88[1].vy = -wp->unk_B6;
                wp->corner_88[2].vx = -wp->unk_B4;
                wp->flags_0 |= 0x12000000;
                wp->flags_0 = (wp->flags_0 & ~0x08000000) | wp->unk_80;
                wp->cmd_ptr_6C += 3;
                wp->corner_88[1].vx = wp->unk_B4 + wp->unk_7E * 12;
                wp->corner_88[2].vy = wp->unk_B6 + wp->unk_7F * 12;
                wp->corner_88[3].vx = wp->unk_B4 + wp->unk_7E * 12;
                wp->corner_88[3].vy = wp->unk_B6 + wp->unk_7F * 12;
                wp->unk_7D++;
            }
            break;
        case 2:
            wp->flags_0 |= 0x10000000;
            wp->corner_88[0].vy += wp->unk_85;
            wp->corner_88[1].vy += wp->unk_85;
            wp->corner_88[2].vy -= wp->unk_85;
            wp->corner_88[3].vy -= wp->unk_85;
            if (wp->corner_88[0].vy > wp->corner_88[2].vy)
            {
                wp->flags_0 &= ~0x06000000;
            }
            break;
    }
}

void func_8005AB78(MOJI_WORK *wp)
{
    switch (wp->unk_7D)
    {
        case 0:
            wp->flags_0 |= 0x06000000;
            wp->unk_7D += 2;
            wp->unk_B4 = wp->unk_B6 = wp->cmd_ptr_6C[2];
            wp->cmd_ptr_6C += 3;
            Moji_flag |= 0x200000;
            wp->corner_88[0].vx = -wp->unk_B4;
            wp->corner_88[0].vy = -wp->unk_B6;
            wp->corner_88[1].vx = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[1].vy = -wp->unk_B6;
            wp->corner_88[2].vx = -wp->unk_B4;
            wp->corner_88[2].vy = wp->unk_B6 + wp->unk_7F * 12;
            wp->corner_88[3].vx = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[3].vy = wp->unk_B6 + wp->unk_7F * 12;
            break;
        case 2:
            wp->flags_0 = (wp->flags_0 | 0x10000000) & ~0x06000000;
            break;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005ACA8);

// Fades a full-screen (320 x 240) quad in to grey 0x80 (unk_7D 0 sets it up, 1 fades in and
// skips the command) and out again (2).
void func_8005B454(MOJI_WORK *mp)
{
    switch (mp->unk_7D)
    {
        case 0:
            mp->corner_88[1].vx = 320;
            mp->corner_88[2].vy = 240;
            mp->corner_88[3].vx = 320;
            mp->corner_88[3].vy = 240;
            mp->r_B0            = 0;
            mp->g_B1            = 0;
            mp->b_B2            = 0;
            mp->corner_88[0].vx = 0;
            mp->corner_88[0].vy = 0;
            mp->corner_88[1].vy = 0;
            mp->corner_88[2].vx = 0;
            mp->flags_0 |= 0x14000000;
            mp->unk_80 = mp->flags_0 & 0x08000000;
            mp->unk_7D++;
            mp->flags_0 |= 0x08000000;
            break;
        case 1:
            mp->flags_0 |= 0x10000000;
            mp->r_B0 += 8;
            mp->g_B1 += 8;
            mp->b_B2 += 8;
            if (mp->r_B0 == 0x80)
            {
                mp->flags_0 |= 0x12000000;
                mp->flags_0 = (mp->flags_0 & ~0x08000000) | mp->unk_80;
                mp->unk_7D++;
                mp->cmd_ptr_6C += 3;
            }
            break;
        case 2:
            mp->flags_0 |= 0x10000000;
            mp->r_B0 -= 8;
            mp->g_B1 -= 8;
            mp->b_B2 -= 8;
            if (mp->r_B0 == 0)
            {
                mp->flags_0 &= ~0x06000000;
            }
            break;
    }
}

void func_8005B5D8(MOJI_WORK *mp)
{
    DR_MODE *mode;
    DR_MODE *mode2;
    POLY_F4 *f4;

    f4           = (POLY_F4 *)Map_prim_ptr;
    Map_prim_ptr = (POLY_FT4 *)(f4 + 1);
    mp->prim_98  = f4;
    setPolyF4(mp->prim_98);
    setSemiTrans(mp->prim_98, 1);
    mp->prim_98->r0 = mp->r_B0;
    mp->prim_98->g0 = mp->g_B1;
    mp->prim_98->b0 = mp->b_B2;
    mode            = (DR_MODE *)Map_prim_ptr;
    Map_prim_ptr    = (POLY_FT4 *)(mode + 1);
    SetDrawMode(mode, 0, 0, GetTPage(0, 0, 0x3C0, 0x100), NULL);
    addPrim(&Disp_env_ptr->ot[mp->ot_3D], mode);
    mp->prim_98->x0 = mp->corner_88[0].vx;
    mp->prim_98->y0 = mp->corner_88[0].vy;
    mp->prim_98->x1 = mp->corner_88[1].vx;
    mp->prim_98->y1 = mp->corner_88[1].vy;
    mp->prim_98->x2 = mp->corner_88[2].vx;
    mp->prim_98->y2 = mp->corner_88[2].vy;
    mp->prim_98->x3 = mp->corner_88[3].vx;
    mp->prim_98->y3 = mp->corner_88[3].vy;
    addPrim(&Disp_env_ptr->ot[mp->ot_3D], mp->prim_98);
    mode2        = (DR_MODE *)Map_prim_ptr;
    Map_prim_ptr = (POLY_FT4 *)(mode2 + 1);
    SetDrawMode(mode2, 0, 0, GetTPage(0, 2, 0x3C0, 0x100), NULL);
    addPrim(&Disp_env_ptr->ot[mp->ot_3D], mode2);
}

// Same code as func_8005AB78.
void func_8005B85C(MOJI_WORK *wp)
{
    switch (wp->unk_7D)
    {
        case 0:
            wp->flags_0 |= 0x06000000;
            wp->unk_7D += 2;
            wp->unk_B4 = wp->unk_B6 = wp->cmd_ptr_6C[2];
            wp->cmd_ptr_6C += 3;
            Moji_flag |= 0x200000;
            wp->corner_88[0].vx = -wp->unk_B4;
            wp->corner_88[0].vy = -wp->unk_B6;
            wp->corner_88[1].vx = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[1].vy = -wp->unk_B6;
            wp->corner_88[2].vx = -wp->unk_B4;
            wp->corner_88[2].vy = wp->unk_B6 + wp->unk_7F * 12;
            wp->corner_88[3].vx = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[3].vy = wp->unk_B6 + wp->unk_7F * 12;
            break;
        case 2:
            wp->flags_0 = (wp->flags_0 | 0x10000000) & ~0x06000000;
            break;
    }
}

// Same code as func_8005A874.
void func_8005B98C(MOJI_WORK *wp)
{
    switch (wp->unk_7D)
    {
        case 0:
            wp->unk_85 = 8;
            wp->flags_0 |= 0x14000000;
            wp->unk_80 = wp->flags_0 & 0x08000000;
            wp->flags_0 |= 0x08000000;
            wp->unk_B6 = wp->unk_B4 = wp->cmd_ptr_6C[2];
            wp->unk_7D++;
            wp->corner_88[0].vy = wp->unk_7F * 6;
            wp->corner_88[1].vy = wp->unk_7F * 6;
            wp->corner_88[2].vy = wp->unk_7F * 6;
            wp->corner_88[3].vy = wp->unk_7F * 6;
            wp->corner_88[0].vx = -wp->unk_B4;
            wp->corner_88[1].vx = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[2].vx = -wp->unk_B4;
            wp->corner_88[3].vx = wp->unk_B4 + wp->unk_7E * 12;
            break;
        case 1:
            wp->flags_0 |= 0x10000000;
            wp->corner_88[0].vy -= wp->unk_85;
            wp->corner_88[1].vy -= wp->unk_85;
            wp->corner_88[2].vy += wp->unk_85;
            wp->corner_88[3].vy += wp->unk_85;
            if (wp->unk_A + wp->corner_88[0].vy <= wp->unk_A - wp->unk_B6)
            {
                Moji_flag |= 0x200000;
                wp->corner_88[0].vx = -wp->unk_B4;
                wp->corner_88[0].vy = -wp->unk_B6;
                wp->corner_88[1].vy = -wp->unk_B6;
                wp->corner_88[2].vx = -wp->unk_B4;
                wp->flags_0 |= 0x12000000;
                wp->flags_0 = (wp->flags_0 & ~0x08000000) | wp->unk_80;
                wp->cmd_ptr_6C += 3;
                wp->corner_88[1].vx = wp->unk_B4 + wp->unk_7E * 12;
                wp->corner_88[2].vy = wp->unk_B6 + wp->unk_7F * 12;
                wp->corner_88[3].vx = wp->unk_B4 + wp->unk_7E * 12;
                wp->corner_88[3].vy = wp->unk_B6 + wp->unk_7F * 12;
                wp->unk_7D++;
            }
            break;
        case 2:
            wp->flags_0 |= 0x10000000;
            wp->corner_88[0].vy += wp->unk_85;
            wp->corner_88[1].vy += wp->unk_85;
            wp->corner_88[2].vy -= wp->unk_85;
            wp->corner_88[3].vy -= wp->unk_85;
            if (wp->corner_88[0].vy > wp->corner_88[2].vy)
            {
                wp->flags_0 &= ~0x06000000;
            }
            break;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005BC90);

void window_prim_set(MOJI_WORK *wp, sint32 col)
{
    POLY_F4 *f4;
    POLY_G4 *g4;
    sint32 i;

    f4           = (POLY_F4 *)Map_prim_ptr;
    Map_prim_ptr = (POLY_FT4 *)(f4 + 1);
    wp->prim_98  = f4;
    Map_prim_ptr = (POLY_FT4 *)(f4 + 2);
    wp->prim_9C  = f4 + 1;
    setPolyF4(wp->prim_98);
    setSemiTrans(wp->prim_98, 1);
    wp->prim_98->r0 = D_80097F6C[col][0];
    wp->prim_98->g0 = D_80097F6C[col][1];
    wp->prim_98->b0 = D_80097F6C[col][2];
    setPolyF4(wp->prim_9C);
    setSemiTrans(wp->prim_9C, 1);
    wp->prim_9C->r0 = D_80097F6C[col][3];
    wp->prim_9C->g0 = D_80097F6C[col][4];
    wp->prim_9C->b0 = D_80097F6C[col][5];
    for (i = 0; i < 4; i++)
    {
        g4             = (POLY_G4 *)Map_prim_ptr;
        Map_prim_ptr   = (POLY_FT4 *)(g4 + 1);
        wp->prim_A0[i] = g4;
        setPolyG4(wp->prim_A0[i]);
        // Row i of the shade table at 0x80097F78 (no label of its own), one grey per vertex.
        // Indexed off D_80097F7B as (i << 2) - 3: with that form loop.c hoists the constants
        // and walks four table pointers, as the target does.
        wp->prim_A0[i]->r0 = D_80097F7B[(i << 2) - 3];
        wp->prim_A0[i]->g0 = D_80097F7B[(i << 2) - 3];
        wp->prim_A0[i]->b0 = D_80097F7B[(i << 2) - 3];
        wp->prim_A0[i]->r1 = D_80097F79[i << 2];
        wp->prim_A0[i]->g1 = D_80097F79[i << 2];
        wp->prim_A0[i]->b1 = D_80097F79[i << 2];
        wp->prim_A0[i]->r2 = D_80097F7A[i << 2];
        wp->prim_A0[i]->g2 = D_80097F7A[i << 2];
        wp->prim_A0[i]->b2 = D_80097F7A[i << 2];
        wp->prim_A0[i]->r3 = D_80097F7B[i << 2];
        wp->prim_A0[i]->g3 = D_80097F7B[i << 2];
        wp->prim_A0[i]->b3 = D_80097F7B[i << 2];
    }
}

#ifdef NON_MATCHING
// Remaining difference: the loop end is built as lui/addiu %lo(D_8008AF24+0x18) (one instruction
// more); the target computes it from the table pointer's register (addiu t3,t0,0x18).
// Writes n as six digits (leading zeros as D_8008AF3C[pad]) and a terminator.
void six_digit_set(sint32 pad, uint32 n, uint8 *dst)
{
    uint32 i;
    uint32 digit;

    for (i = 0; i < 6; i++)
    {
        digit = n / D_8008AF24[i];
        if (D_800986F0[0] == 1 || digit != 0)
        {
            dst[i]        = D_8008D028[digit];
            D_800986F0[0] = 1;
        }
        else
        {
            dst[i] = D_8008AF3C[pad];
        }
        n %= D_8008AF24[i];
    }
    D_800986F0[0] = 0;
    dst[6]        = D_8008D028[0];
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", six_digit_set);
#endif

// Writes a frame count (30 per second) as a time: minutes' last digit at [0], seconds at [2] and
// [3], tenths at [5] and hundredths (0, 3 or 6) at [6]. One index variable serves every digit.
void time_digit_set(uint32 frames, uint8 *dst)
{
    uint32 sec;
    uint32 idx;

    sec    = frames / 30;
    idx    = (frames % 3) * 3;
    dst[6] = D_8008D028[idx];
    idx    = (frames % 30) / 3;
    dst[5] = D_8008D028[idx];
    idx    = sec % 10;
    dst[3] = D_8008D028[idx];
    idx    = (sec % 60) / 10;
    dst[2] = D_8008D028[idx];
    idx    = (sec / 60) % 10;
    dst[0] = D_8008D028[idx];
}

void two_digit_set(uint32 n, uint8 *dst)
{
    dst[0] = D_8008D028[n / 10];
    dst[1] = D_8008D028[n % 10];
    if (dst[0] == D_8008D028[0])
    {
        dst[0] = 0x4F;
    }
}

void func_8005C150(sint32 index, uint32 mode, sint32 value, sint32 task_no)
{
    switch (mode)
    {
        case 0:
            D_80098830 = value;
            MojiTaskExec(task_no, D_8008CACC[D_8008AF40[index] + 1], 0xFF);
            break;
        case 1:
            D_80098AF4 = value;
            MojiTaskExec(task_no, D_8008CACC[D_8008AF40[index] + 2], 0xFF);
            break;
        case 2:
            MojiTaskExec(task_no, D_8008CACC[D_8008AF40[index]], 0xFF);
            break;
    }
}

void func_8005C218(uint8 val)
{
    D_80098830 = val;
}

void func_8005C224(sint32 val)
{
    D_80098AF4 = val;
}

void func_8005C230(sint32 val)
{
    D_800989E0[0] = val;
}

void func_8005C23C(sint32 val)
{
    D_800989E0[3] = val;
}

void func_8005C24C(uint8 val)
{
    D_800989D4 = val;
}
