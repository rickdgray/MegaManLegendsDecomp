#include "common.h"
#include "cd.h"
#include "game.h"
#include "moji.h"
#include "scene.h"
#include "sound.h"
#include "code_80037FB4.h"
#include "code_8004324C.h"

// Small uninitialized statics (.sbss 0x800986E0-0x800986F8).
static uint8 D_800986E0[4];
static uint8 D_800986E4[4];
static uint8 D_800986E8[4];
static uint8 D_800986EC[4];
static sint32 D_800986F0[2];

// Pool variables (tentative definitions).
uint8 D_80098830;
uint8 D_800989D4;
// Four words: func_8005C23C stores to [3] (0x800989EC), which is lui-based, as a common's
// offset access is under ASPSX 2.56.
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", MojiTaskExec);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", MojiTaskExec2);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80054450);

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
        wp->unk_71  = 0;
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80054BEC);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80055344);

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
            wp->unk_71 = 0;
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80055868);

sint32 func_80055A78(MOJI_WORK *wp)
{
    uint8 mes_no;

    if (Game_work.unk050 == wp->cmd_ptr_6C[1] && Game_work.unk051 == wp->cmd_ptr_6C[2])
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005619C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800561E8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80056234);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80056280);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800563A8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800564C8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80056558);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80056610);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800566CC);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800570B0);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057184);

sint32 func_8005721C(MOJI_WORK *wp)
{
    D_80098930 = D_800BE2F8[D_8009899C + wp->unk_71] + wp->cmd_ptr_6C[1];
    if (!Sce_flag_test(0x2EE) && func_8004327C(-D_8008FD3C[D_80098930]))
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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057408);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057574);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800577FC);

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
        wp->cmd_ptr_6C[i + 1] = Game_work.unk084[D_800989D4][i + 2];
    }
    wp->cmd_ptr_6C += 1;
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057E50);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80057FF8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005851C);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800587F8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80058AEC);

sint32 func_80058C08(MOJI_WORK *wp)
{
    wp->unk_3D = wp->cmd_ptr_6C[1];
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
        wp->cmd_ptr_6C = D_8008CBA4[(sint8)Player_work[0].ids_454[wp->cmd_ptr_6C[2] + D_8009899C] - 1];
    }
    else
    {
        wp->cmd_ptr_6C[-1] = 0;
        if ((Moji_flag & 0x20000) && wp->cmd_ptr_6C[2] == wp->unk_71)
        {
            wp->cmd_ptr_6C[-1] = 3;
        }
        wp->cmd_ptr_6C = D_8008CBA4[(sint8)Player_work[0].ids_450[wp->cmd_ptr_6C[2]] - 1];
    }
    return 1;
}

// The id bytes are read signed (lb); typing the fields sint8 breaks Sce_flag_off.
void func_80059660(MOJI_WORK *mp)
{
    mp->call_stk_18[mp->call_sp_BE++] = mp->mes_ptr_14 + 3;
    if (mp->mes_ptr_14[1] != 0)
    {
        mp->mes_ptr_14 = D_8008CBA4[(sint8)Player_work[0].ids_454[mp->mes_ptr_14[2] + D_8009899C] - 1];
    }
    else
    {
        mp->mes_ptr_14[-1] = 0;
        if ((Moji_flag & 0x20000) && mp->mes_ptr_14[3] == mp->unk_71)
        {
            mp->mes_ptr_14[-1] = 3;
        }
        mp->mes_ptr_14 = D_8008CBA4[(sint8)Player_work[0].ids_450[mp->mes_ptr_14[2]] - 1];
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80059728);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_800598C8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_80059B44);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005A874);

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
            wp->corner_88[0][0] = -wp->unk_B4;
            wp->corner_88[0][1] = -wp->unk_B6;
            wp->corner_88[1][0] = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[1][1] = -wp->unk_B6;
            wp->corner_88[2][0] = -wp->unk_B4;
            wp->corner_88[2][1] = wp->unk_B6 + wp->unk_7F * 12;
            wp->corner_88[3][0] = wp->unk_B4 + wp->unk_7E * 12;
            wp->corner_88[3][1] = wp->unk_B6 + wp->unk_7F * 12;
            break;
        case 2:
            wp->flags_0 = (wp->flags_0 | 0x10000000) & ~0x06000000;
            break;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005ACA8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005B454);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005B5D8);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005B85C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005B98C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005BC90);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005BCE4);

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

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005BFC0);

void two_digit_set(uint32 n, uint8 *dst)
{
    dst[0] = D_8008D028[n / 10];
    dst[1] = D_8008D028[n % 10];
    if (dst[0] == D_8008D028[0])
    {
        dst[0] = 0x4F;
    }
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/moji", func_8005C150);

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
