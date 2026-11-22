#include "common.h"
#include "code_8006430C.h"
#include "psyq/libapi.h"
#include "game.h"
#include "pad.h"
#include "moji.h"
#include "sound.h"
#include "psyq/libetc.h"
#include "psyq/strings.h"
#include "cd.h"
#include "fastmem.h"
#include "psyq/rand.h"
#include "debug.h"
#include "display.h"
#include "player.h"
#include "scene.h"

// Small data (.sdata 0x8009808C-0x8009809C): only card_free_blocks's string literals "bu00:*" and
// "bu10:*", reached through $gp.

// Small uninitialized statics (.sbss 0x80098708-0x80098730).
static sint32 D_80098708;
static sint32 D_8009870C;
static sint32 D_80098710;
static sint32 D_80098714;
static sint32 D_80098718;
static sint32 D_8009871C;
static sint32 D_80098720;
static sint32 D_80098724;
static sint16 D_80098728[4];

// Pool variables reached through $gp in this file.
SPEC_ENT **D_80098844;
SPEC_ENT **D_8009884C;
CODE_8006430C_WORK D_80098910;
SPEC_ENT **D_80098928;
SPEC_ENT **D_8009892C;
uint8 D_80098A04;

// LOGO_FUNC 1 (D_8008DD64): draws a logo's sprites in a grid (6 columns, 44 x 40 pixels), each
// shown according to its three scene flags (flag_2) and its type (the head's high byte).
#ifdef NON_MATCHING
// Instructions match; the frame is 0x48, the target's 0x50: the target has an unused 8-byte slot
// at 0x18 between wp's spill (0x10) and start's (0x20), a reload slot for a pseudo with no
// instructions left. An unused RECT lands at 0x10 instead. CoastRedWood's fork matched it only
// with a FAKE loop condition (`while (id = (sint16)rec->head_0 >= 0)`).
void func_8006430C(LOGO_WORK *wp)
{
    LOGO_SPRITE *rec;
    ICON_PRIM *start;
    ICON_PRIM *p;
    sint32 id;
    uint32 kind;
    sint32 slot;
    sint32 flag;
    sint32 first;
    sint32 count;
    uint32 value;
    sint32 x;
    sint32 y;

    value   = 0;
    rec     = wp->sprites_8;
    p       = Icon_prim_ptr;
    p->tag  = 0x02000000;
    p->rgbc = 0xE100000C;
    p->xy   = 0;
    p->tag  = ((uint32)(p + 1) & 0xFFFFFF) | 0x02000000;
    start   = p;
    p++;
    do
    {
        flag    = rec->flag_2;
        slot    = rec->head_0 & 0xFF;
        id      = (sint16)rec->head_0;
        p->tag  = ((uint32)(p + 1) & 0xFFFFFF) | 0x04000000;
        p->rgbc = 0x64808080;
        p->xy   = ((slot % 6) * 44 + (x = rec->xy_4.s.x + 0x22)) | (((slot / 6) * 40 + (y = rec->xy_4.s.y + 0x3C)) << 16);
        p->wh   = rec->wh_c;
        first   = Sce_flag_test(flag);
        count   = first + Sce_flag_test(flag + 1) + Sce_flag_test(flag + 2);
        kind    = id >> 8;
        switch (kind)
        {
            case 0:
            case 13:
                if (first != 0)
                {
                    p->uv_clut = rec->uv_8;
                    p++;
                }
                else if (kind == 0)
                {
                    p->uv_clut = ICON_UV_CLUT_NONE;
                    p++;
                }
                break;
            case 1:
                if (count != 0)
                {
                    p->uv_clut = rec->uv_8;
                }
                else
                {
                    p->uv_clut = ICON_UV_CLUT_NONE;
                }
                p++;
                break;
            case 2:
                if (count != 0)
                {
                    p->uv_clut = rec->uv_8;
                    p++;
                }
                break;
            case 3:
                if (count != 0)
                {
                    p->uv_clut = rec->uv_8 + (count - 1) * 8;
                    p++;
                }
                break;
            case 4:
                if (count != 0)
                {
                    p->uv_clut = rec->uv_8 + (count - 1) * 32;
                }
                else
                {
                    p->uv_clut = ICON_UV_CLUT_NONE;
                }
                p++;
                break;
            case 5:
            case 7:
                if (kind == 5)
                {
                    value = Game_work.unk07C;
                }
                else
                {
                    value = Game_work.unk07D;
                }
                if (first != 0 && value >= 10)
                {
                    p->uv_clut = rec->uv_8 + (value / 10) * 8;
                    p++;
                }
                break;
            case 6:
            case 8:
                if (kind == 6)
                {
                    value = Game_work.unk07C;
                }
                else
                {
                    value = Game_work.unk07D;
                }
                if (first != 0)
                {
                    p->uv_clut = rec->uv_8 + (value % 10) * 8;
                    p++;
                }
                break;
            case 9:
            case 10:
            case 11:
            case 12:
                switch (kind)
                {
                    case 9:
                        value = Player_work[0].unk16A;
                        break;
                    case 10:
                        value = Player_work[0].unk16B & 2;
                        break;
                    case 11:
                        value = Player_work[0].unk16B & 1;
                        break;
                    case 12:
                        value = Player_work[0].unk16C;
                        break;
                }
                if (first != 0 && value != 0)
                {
                    p->uv_clut = rec->uv_8;
                    p++;
                }
                break;
        }
        rec++;
    } while ((sint16)rec->head_0 >= 0);
    addPrims(&Disp_env_ptr->ot[wp->value_5], start, p - 1);
    Icon_prim_ptr = p;
}
#else
INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006430C);
#endif

void func_8006471C(void)
{
    if (Game_work.unk05B == 2)
    {
        D_80098844 = D_8008F060;
        D_8009884C = D_8008F200;
        D_80098928 = D_8008F260;
        D_8009892C = D_8008F2E4;
    }
    else
    {
        D_80098844 = D_8008EDC4;
        D_8009884C = D_8008EF64;
        D_80098928 = D_8008EFC4;
        D_8009892C = D_8008F048;
    }
}

void Card_init(void)
{
    EnterCriticalSection();
    D_80098708 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_8009870C = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80098710 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80098714 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    D_80098718 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_8009871C = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80098720 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80098724 = OpenEvent(HwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(D_80098708);
    EnableEvent(D_8009870C);
    EnableEvent(D_80098710);
    EnableEvent(D_80098714);
    EnableEvent(D_80098718);
    EnableEvent(D_8009871C);
    EnableEvent(D_80098720);
    EnableEvent(D_80098724);
    InitCARD(1);
    StartCARD();
    _bu_init();
}

sint32 func_8006491C(void)
{
    for (;;)
    {
        if (TestEvent(D_80098708) != 0)
        {
            return 0;
        }
        if (TestEvent(D_80098710) != 0)
        {
            return 1;
        }
        if (TestEvent(D_80098714) != 0)
        {
            return 2;
        }
        if (TestEvent(D_8009870C) != 0)
        {
            return 3;
        }
    }
}

sint32 func_80064984(void)
{
    for (;;)
    {
        if (TestEvent(D_80098718) != 0)
        {
            return 0;
        }
        if (TestEvent(D_80098720) != 0)
        {
            return 1;
        }
        if (TestEvent(D_8009871C) != 0)
        {
            return 2;
        }
        if (TestEvent(D_80098724) != 0)
        {
            return 3;
        }
    }
}

void func_800649EC(void)
{
    TestEvent(D_80098708);
    TestEvent(D_80098710);
    TestEvent(D_8009870C);
    TestEvent(D_80098714);
}

void func_80064A34(void)
{
    TestEvent(D_80098718);
    TestEvent(D_80098720);
    TestEvent(D_8009871C);
    TestEvent(D_80098724);
}

sint32 func_80064A7C(sint32 port)
{
    sint32 r;

    VSync(0);
retry:
    func_800649EC();
    _card_info(port << 4);
    r = func_8006491C();
    if (r == 3)
    {
        return 3;
    }
    if (r == 1)
    {
        return 1;
    }
    if (r == 2)
    {
        func_80064A34();
        if (_card_clear(port << 4) != 1)
        {
            goto retry;
        }
        if (func_80064984() != 0)
        {
            return 3;
        }
    }
    func_800649EC();
    _card_load(port << 4);
    VSync(72);
    r = func_8006491C();
    if (r == 2)
    {
        return 4;
    }
    return (r != 0) ? 3 : 0;
}

sint32 func_80064B60(sint32 port)
{
    sint32 r;

    _card_info(port << 4);
    r = func_8006491C();
    if (r == 1)
    {
        return 0;
    }
    if (r == 2 || r == 0)
    {
        return 1;
    }
    return -1;
}

sint32 func_80064BB4(sint32 port)
{
    sint32 r;

    _card_info(port << 4);
    r = func_8006491C();
    if (r == 1)
    {
        return 0;
    }
    if (r == 0)
    {
        return 1;
    }
    if (r == 2)
    {
        return 2;
    }
    return -1;
}

// Free blocks on the card in port (0 or 1): 15 blocks of 8 KB less the sizes of its files.
uint32 card_free_blocks(sint32 port)
{
    struct DIRENTRY dir;
    char path[24];
    uint32 free;

    free = 15 * 0x2000;
    if (port == 0)
    {
        strcpy(path, "bu00:*");
    }
    else
    {
        strcpy(path, "bu10:*");
    }
    if (firstfile(path, &dir) == &dir)
    {
        free -= dir.size;
        while (nextfile(&dir) == &dir)
        {
            free -= dir.size;
        }
    }
    return free / 0x2000;
}

// Fills the first sector of a save block (the memory card file header): magic "SC", icon flag
// 0x11, one block, the 64-byte title, then the icon's CLUT and image.
void card_header_set(uint8 *buf, uint8 *title)
{
    sint32 i;
    uint8 *dst;
    uint8 *tbl;
    uint8 *dst2;

    buf[0] = 'S';
    buf[1] = 'C';
    buf[2] = 0x11;
    buf[3] = 1;
    dst    = buf + 4;
    for (i = 0; i < 0x40; i++)
    {
        *dst++ = *title++;
    }
    dst = buf + 0x44;
    for (i = 0; i < 0x1C; i++)
    {
        *dst++ = 0;
    }
    tbl  = D_8008F9BC;
    dst2 = buf + 0x80;
    for (i = 0; i < 0x80; i++)
    {
        *dst2++ = *tbl++;
    }
    tbl  = D_8008FA3C;
    dst2 = buf + 0x60;
    for (i = 0; i < 0x20; i++)
    {
        *dst2++ = *tbl++;
    }
}

// Writes size bytes of buf to the file name on the card in port, creating it (in 8 KB blocks)
// if it doesn't exist. 0 on success, func_80064A7C's code if the card isn't ready, 2 if it
// is too full to create the file, -1 on other errors.
sint32 card_file_write(sint32 port, char *name, char *buf, uint32 size)
{
    char path[0x20];
    sint32 fd;
    sint32 r;
    uint32 free_blocks;
    uint32 blocks;

    r = func_80064A7C(port);
    if (r != 0)
    {
        return r;
    }
    blocks      = (size + 0x1FFF) >> 13;
    free_blocks = card_free_blocks(port);
    strcpy(path, D_8008FA5C[port]);
    strcat(path, name);
    fd = open(path, O_WRONLY);
    if (fd == -1)
    {
        fd = open(path, (blocks << 16) | O_CREAT);
        if (fd == -1)
        {
            if (free_blocks < blocks)
            {
                return 2;
            }
            return -1;
        }
        if (close(fd) == -1)
        {
            return -1;
        }
        fd = open(path, O_WRONLY);
        if (fd == -1)
        {
            return -1;
        }
    }
    if (write(fd, buf, size) == -1)
    {
        return -1;
    }
    close(fd);
    return 0;
}

// Reads size bytes of the file name on the card in port into buf. 0 on success,
// func_80064A7C's code if the card isn't ready, 2 or -1 if the file can't be opened, 3 if the
// read fails.
sint32 card_file_read(sint32 port, char *name, void *buf, uint32 size)
{
    char path[0x20];
    sint32 fd;
    sint32 r;
    uint32 free_blocks;
    uint32 blocks;

    r = func_80064A7C(port);
    if (r != 0)
    {
        return r;
    }
    blocks      = (size + 0x1FFF) >> 13;
    free_blocks = card_free_blocks(port);
    strcpy(path, D_8008FA5C[port]);
    strcat(path, name);
    fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        if (free_blocks < blocks)
        {
            return 2;
        }
        return -1;
    }
    if (read(fd, buf, size) == -1)
    {
        return 3;
    }
    close(fd);
    return 0;
}

// Formats the card in port: -1 if func_80064A7C reports no card (1) before or after, else 0.
sint32 card_format(sint32 port)
{
    sint32 r;

    r = func_80064A7C(port);
    if (r == 1)
    {
        return -1;
    }
    format(D_8008FA5C[port]);
    return -(func_80064A7C(port) == 1);
}

sint32 func_80064FF0(sint32 port)
{
    D_8009AB31    = 0xFF;
    D_8009AB30[0] = 0xFF;
    func_80064A34();
    _new_card();
    if (port == 0)
    {
        _card_write(0x00, 0, D_8009AB30);
    }
    else
    {
        _card_write(0x10, 0, D_8009AB30);
    }
    return func_80064984() == 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80065064);

// Seals the save image: picks a random key for each block, writes the block's three sums
// (SAVE_SUM, each mixed with the key), then the overall check words 0x7BC-0x7BF.
void save_sum_set(void)
{
    uint32 sum[3];
    uint32 *save;
    uint32 i;
    uint32 w;

    save        = Save_words;
    save[0x5C]  = (rand() << 16) | rand();
    save[0x6C]  = (rand() << 16) | rand();
    save[0x7C]  = (rand() << 16) | rand();
    save[0xDC]  = (rand() << 16) | rand();
    save[0x74C] = (rand() << 16) | rand();
    save[0x7B8] = (rand() << 16) | rand();
    SAVE_SUM(0, 0x5C);
    save[0x5D] = save[0x5C] + sum[0];
    save[0x5E] = (save[0x5C] ^ 0xE1E1E1E1) + sum[1];
    save[0x5F] = (save[0x5C] ^ 0x57575757) + sum[2];
    SAVE_SUM(0x60, 0x6C);
    save[0x6D] = ~save[0x6C] + sum[0];
    save[0x6E] = (save[0x6C] ^ 0x33333333) + sum[1];
    save[0x6F] = (save[0x6C] ^ 0xCCCCCCCC) + sum[2];
    SAVE_SUM(0x70, 0x7C);
    save[0x7D] = (save[0x7C] ^ 0x69696969) + sum[0];
    save[0x7E] = (save[0x7C] ^ 0x2B2B2B2B) + sum[1];
    save[0x7F] = (save[0x7C] ^ 0xB8B8B8B8) + sum[2];
    SAVE_SUM(0x80, 0xDC);
    save[0xDD] = save[0xDC] + sum[0];
    save[0xDE] = (save[0xDC] ^ 0x1E1E1E1E) + sum[1];
    save[0xDF] = (save[0xDC] ^ 0x75757575) + sum[2];
    SAVE_SUM(0xE0, 0x74C);
    save[0x74D] = ~save[0x74C] + sum[0];
    save[0x74E] = (save[0x74C] ^ 0x33333333) + sum[1];
    save[0x74F] = (save[0x74C] ^ 0xCCCCCCCC) + sum[2];
    SAVE_SUM(0x750, 0x7B8);
    save[0x7B9] = (save[0x7B8] ^ 0x96969696) + sum[0];
    save[0x7BA] = (save[0x7B8] ^ 0xB2B2B2B2) + sum[1];
    save[0x7BB] = (save[0x7B8] ^ 0x8B8B8B8B) + sum[2];
    save[0x7BD] =
        ((save[0x5D] + save[0x6D]) ^ save[0x5C]) + ((save[0x7D] + save[0xDD]) ^ save[0x7C]) + ((save[0x74D] + save[0x7B9]) ^ save[0x74C]);
    save[0x7BE] =
        ((save[0x5E] + save[0x6E]) ^ save[0x6C]) + ((save[0x7E] + save[0xDE]) ^ save[0xDC]) + ((save[0x74E] + save[0x7BA]) ^ save[0x7B8]);
    save[0x7BF] =
        ((save[0x5F] + save[0x6F]) ^ save[0x5C]) + ((save[0x7F] + save[0xDF]) ^ save[0x6C]) + ((save[0x74F] + save[0x7BB]) ^ save[0x7C]);
    save[0x7BC] = ~save[0x7BD] + (save[0x7BE] ^ 0xAAAAAAAA) + (save[0x7BF] ^ 0x55555555);
}

// Restores Game_work and the area entry from the loaded save image.
void Save_image_restore(void)
{
    Game_work.unk010                = Save_image.unk010;
    Game_work.timer_14              = Save_image.timer_14;
    Game_work.unk018                = Save_image.unk018;
    Game_work.unk01A                = Save_image.unk01A;
    Game_work.timer_0c              = Save_image.timer_0c;
    Game_work.money                 = Save_image.money;
    Game_work.unk020                = Save_image.unk020;
    Game_work.unk024                = Save_image.unk024;
    Game_work.unk028[0]             = Save_image.unk028[0];
    Game_work.unk028[1]             = Save_image.unk028[1];
    Game_work.unk028[2]             = Save_image.unk028[2];
    Game_work.unk028[3]             = Save_image.unk028[3];
    Game_work.unk028[4]             = Save_image.unk028[4];
    Game_work.unk028[5]             = Save_image.unk028[5];
    Game_work.unk040[0]             = Save_image.unk040[0];
    Game_work.unk040[1]             = Save_image.unk040[1];
    Game_work.unk040[2]             = Save_image.unk040[2];
    Game_work.unk040[3]             = Save_image.unk040[3];
    Game_work.unk040[4]             = Save_image.unk040[4];
    Game_work.unk040[5]             = Save_image.unk040[5];
    Game_work.unk04C                = Save_image.unk04C;
    D_800C356E                      = Save_image.stage_no;
    Game_work.stage_no              = Save_image.stage_no;
    D_800C356F                      = Save_image.area_no;
    Game_work.area_no               = Save_image.area_no;
    Game_work.sce_no                = Save_image.sce_no;
    Game_work.unk053                = Save_image.unk053;
    Game_work.unk060                = Save_image.unk060;
    Game_work.unk078.b.flag         = Save_image.unk078;
    Game_work.unk078.b.unk079       = Save_image.unk079;
    Game_work.unk078.b.unk07A       = Save_image.unk07A;
    Game_work.unk078.b.unk07B       = Save_image.unk07B;
    Game_work.unk07C                = Save_image.unk07C;
    Game_work.unk07D                = Save_image.unk07D;
    *(uint16 *)&Game_work.unk062[0] = Save_image.unk062;
    *(uint32 *)&Game_work.unk062[2] = Save_image.unk064;
    *(uint16 *)&Game_work.unk062[2] = 0;
    if (Game_work.unk062[4] >= 24)
    {
        Game_work.unk062[4] = 0;
    }
    if (Game_work.unk062[5] >= 6)
    {
        Game_work.unk062[5] = 0;
    }
    D_800C3558.pos   = Save_image.pos;
    D_800C3570       = 2;
    D_800C356D       = 0;
    Game_work.unk054 = Save_image.unk054;
    Game_work.unk055 = Save_image.unk055;
    Game_work.unk056 = Save_image.unk056;
    Game_work.mono   = Save_image.mono;
    Game_work.unk059 = Save_image.unk059;
    Game_work.unk05A = Save_image.unk05A;
    Game_work.unk05B = Save_image.unk05B;
    D_800C356A       = Save_image.ang_y;
}

// Checks the save image's sums (save_sum_set): 0 if they all hold, else 3.
sint32 save_sum_check(void)
{
    uint32 sum[3];
    uint32 *save;
    uint32 i;
    uint32 w;

    save = Save_words;
    SAVE_SUM(0, 0x5C);
    if (save[0x5D] != save[0x5C] + sum[0])
    {
        return 3;
    }
    if (save[0x5E] != (save[0x5C] ^ 0xE1E1E1E1) + sum[1])
    {
        return 3;
    }
    if (save[0x5F] != (save[0x5C] ^ 0x57575757) + sum[2])
    {
        return 3;
    }
    SAVE_SUM(0x60, 0x6C);
    if (save[0x6D] != ~save[0x6C] + sum[0])
    {
        return 3;
    }
    if (save[0x6E] != (save[0x6C] ^ 0x33333333) + sum[1])
    {
        return 3;
    }
    if (save[0x6F] != (save[0x6C] ^ 0xCCCCCCCC) + sum[2])
    {
        return 3;
    }
    SAVE_SUM(0x70, 0x7C);
    if (save[0x7D] != (save[0x7C] ^ 0x69696969) + sum[0])
    {
        return 3;
    }
    if (save[0x7E] != (save[0x7C] ^ 0x2B2B2B2B) + sum[1])
    {
        return 3;
    }
    if (save[0x7F] != (save[0x7C] ^ 0xB8B8B8B8) + sum[2])
    {
        return 3;
    }
    SAVE_SUM(0x80, 0xDC);
    if (save[0xDD] != save[0xDC] + sum[0])
    {
        return 3;
    }
    if (save[0xDE] != (save[0xDC] ^ 0x1E1E1E1E) + sum[1])
    {
        return 3;
    }
    if (save[0xDF] != (save[0xDC] ^ 0x75757575) + sum[2])
    {
        return 3;
    }
    SAVE_SUM(0xE0, 0x74C);
    if (save[0x74D] != ~save[0x74C] + sum[0])
    {
        return 3;
    }
    if (save[0x74E] != (save[0x74C] ^ 0x33333333) + sum[1])
    {
        return 3;
    }
    if (save[0x74F] != (save[0x74C] ^ 0xCCCCCCCC) + sum[2])
    {
        return 3;
    }
    SAVE_SUM(0x750, 0x7B8);
    if (save[0x7B9] != (save[0x7B8] ^ 0x96969696) + sum[0])
    {
        return 3;
    }
    if (save[0x7BA] != (save[0x7B8] ^ 0xB2B2B2B2) + sum[1])
    {
        return 3;
    }
    if (save[0x7BB] != (save[0x7B8] ^ 0x8B8B8B8B) + sum[2])
    {
        return 3;
    }
    if (save[0x7BD] !=
        ((save[0x5D] + save[0x6D]) ^ save[0x5C]) + ((save[0x7D] + save[0xDD]) ^ save[0x7C]) + ((save[0x74D] + save[0x7B9]) ^ save[0x74C]))
    {
        return 3;
    }
    if (save[0x7BE] !=
        ((save[0x5E] + save[0x6E]) ^ save[0x6C]) + ((save[0x7E] + save[0xDE]) ^ save[0xDC]) + ((save[0x74E] + save[0x7BA]) ^ save[0x7B8]))
    {
        return 3;
    }
    if (save[0x7BF] !=
        ((save[0x5F] + save[0x6F]) ^ save[0x5C]) + ((save[0x7F] + save[0xDF]) ^ save[0x6C]) + ((save[0x74F] + save[0x7BB]) ^ save[0x7C]))
    {
        return 3;
    }
    if (save[0x7BC] != ~save[0x7BD] + (save[0x7BE] ^ 0xAAAAAAAA) + (save[0x7BF] ^ 0x55555555))
    {
        return 3;
    }
    return 0;
}

void func_800664BC(void)
{
    sint32 flags;
    AREA_ENTRY *ep;

    flags                           = Game_work.unk082;
    ep                              = &D_800C3558;
    Game_work.unk060                = 0x80;
    Game_work.unk078.b.unk079       = -1;
    Game_work.unk078.b.unk07A       = -1;
    Game_work.unk05A                = 1;
    Game_work.timer_0c              = 0;
    Game_work.money                 = 0;
    Game_work.unk020                = 0;
    Game_work.unk024                = 0;
    Game_work.unk028[0]             = 0;
    Game_work.unk028[1]             = 0;
    Game_work.unk028[2]             = 0;
    Game_work.unk028[3]             = 0;
    Game_work.unk028[4]             = 0;
    Game_work.unk028[5]             = 0;
    Game_work.unk040[0]             = 0;
    Game_work.unk040[1]             = 0;
    Game_work.unk040[2]             = 0;
    Game_work.unk040[3]             = 0;
    Game_work.unk040[4]             = 0;
    Game_work.unk040[5]             = 0;
    Game_work.unk04C                = 0;
    Game_work.unk078.b.flag         = 0;
    Game_work.unk078.b.unk07B       = 0;
    Game_work.unk07C                = 0;
    Game_work.unk07D                = 0;
    *(uint16 *)&Game_work.unk062[0] = 0;
    *(uint32 *)&Game_work.unk062[2] = 0;
    if (flags & 0x80)
    {
        D_800C3570 = 0xFF;
    }
    else if (*(uint16 *)&Game_work.stage_no != 0)
    {
        D_800C3570 = 2;
    }
    else
    {
        D_800C3570 = 0xFF;
    }
    ep->unk15 = 1;
}

void func_800665E8(void)
{
    D_80098910.active_0              = 0;
    *(uint32 *)&D_80098910.routine_0 = 0;
}

// Returns the routine's result (1 once it is done): the in-game save screen (r3_sup) adds it to
// its routine.
sint32 func_800665FC(sint16 mode)
{
    D_80098910.mode_2    = mode;
    D_80098910.pad_on_A  = PAD_ON(Joy1);
    D_80098910.pad_now_8 = PAD_NOW(Joy1);
    return D_8008FD10[D_80098910.routine_0](&D_80098910);
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066664);

sint32 func_800666D8(CODE_8006430C_WORK *wp)
{
    D_8008FD20[wp->routine_1](wp);
    return 0;
}

// Same code as func_800666D8.
sint32 func_80066714(CODE_8006430C_WORK *wp)
{
    D_8008FD20[wp->routine_1](wp);
    return 0;
}

sint32 func_80066750(CODE_8006430C_WORK *wp)
{
    wp->active_0              = 0;
    *(uint32 *)&wp->routine_0 = 0;
    wp->routine_0             = 0; // the build needs this store after the word clear
    return 1;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066764);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006689C);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066D60);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066E48);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80066F40);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067174);

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_8006779C);

// Resets the five save slots: header, slot text from D_8008CE94's row 0 and D_80097FFC, and
// the slot number (1 to 5) in the text.
void func_80067884(void)
{
    sint32 i;
    sint32 j;
    CARD_SLOT *slot;

    for (i = 0; i < 5; i++)
    {
        slot = &D_800BAF38[i];
        card_header_set(slot->header, D_8008FA64);
        slot->unk_109 = 0;
        slot->unk_100 = 0;
        for (j = 0; j < 13; j++)
        {
            D_8008D168[i][j] = D_8008CE94[slot->unk_100][j];
        }
        for (j = 0; j < 8; j++)
        {
            D_8008D184[i][j] = slot->unk_101[j] = D_80097FFC[j];
        }
        D_8008D168[i][-2] = D_8008D028[i + 1];
    }
}

// Writes Game_work.timer_0c (frames at 30 a second) as hh:mm:ss into D_80097FD4's font string,
// keeping the digits in D_80098800-D_80098805 (func_80067D10 reads them).
void func_800679B8(void)
{
    uint32 sec;
    uint32 min;
    uint32 hour;
    uint32 digit;

    sec        = Game_work.timer_0c / 30;
    min        = sec / 60;
    digit      = sec % 10;
    D_80097FDB = D_8008D028[digit];
    D_80098805 = digit;
    digit      = (sec % 60) / 10;
    D_80097FDA = D_8008D028[digit];
    D_80098804 = digit;
    hour       = min / 60;
    digit      = min % 10;
    D_80097FD8 = D_8008D028[digit];
    D_80098803 = digit;
    digit      = (min % 60) / 10;
    D_80097FD7 = D_8008D028[digit];
    D_80098802 = digit;
    digit      = hour % 10;
    D_80097FD5 = D_8008D028[digit];
    D_80098801 = digit;
    digit      = (hour % 100) / 10;
    D_80097FD4 = D_8008D028[digit];
    D_80098800 = digit;
}

// Writes Game_work.timer_14 as hh:mm:ss into D_80097FF4's font string.
void func_80067B7C(void)
{
    uint32 sec;
    uint32 min;
    uint32 hour;
    uint32 digit;

    sec        = Game_work.timer_14 / 30;
    min        = sec / 60;
    digit      = sec % 10;
    D_80097FFB = D_8008D028[digit];
    digit      = (sec % 60) / 10;
    D_80097FFA = D_8008D028[digit];
    hour       = min / 60;
    digit      = min % 10;
    D_80097FF8 = D_8008D028[digit];
    digit      = (min % 60) / 10;
    D_80097FF7 = D_8008D028[digit];
    digit      = hour % 10;
    D_80097FF5 = D_8008D028[digit];
    digit      = (hour % 100) / 10;
    D_80097FF4 = D_8008D028[digit];
}

void func_80067D10(void)
{
    D_8008FA84[0] = D_80098124[D_80098A04 + 1];
    D_8008FA84[9] = D_80098124[D_80098805];
    D_8008FA84[8] = D_80098124[D_80098804];
    D_8008FA84[6] = D_80098124[D_80098803];
    D_8008FA84[5] = D_80098124[D_80098802];
    D_8008FA84[3] = D_80098124[D_80098801];
    D_8008FA84[2] = D_80098124[D_80098800];
}

void func_80067E18(void)
{
    D_800BE428 = 0x3F00;
    D_800BE42C = 0x18;
    D_800BE430 = 0x80;
    D_800BE434 = 0;
}

INCLUDE_ASM("asm/rock_neo.exe/nonmatchings/code_8006430C", func_80067E4C);

// Sets up Game_work.records_84: from the new-game tables when load is 0, else from the save
// image in Cd_ring_buf.
void func_80067E6C(sint32 load)
{
    sint32 i;

    // data_4 is copied as two words, through word pointers: the build needs the casts (as
    // fields, GCC addresses both words from one base register).
    if (load == 0)
    {
        for (i = 0; i < 9; i++)
        {
            Game_work.records_84.rec[i].id_0            = D_8008FF64[i];
            ((uint32 *)&Game_work.records_84.rec[i])[1] = ((uint32 *)&D_8008D034[i])[0];
            ((uint32 *)&Game_work.records_84.rec[i])[2] = ((uint32 *)&D_8008D034[i])[1];
            Game_work.records_84.rec[i].unk_c           = 0;
        }
        for (i = 0; i < 3; i++)
        {
            Game_work.records_84.rec[i + 9].id_0             = D_8009813C[i];
            Game_work.records_84.rec[i + 12].id_0            = D_80098148[i];
            ((uint32 *)&Game_work.records_84.rec[i + 9])[1]  = ((uint32 *)&D_8008D07C[i])[0];
            ((uint32 *)&Game_work.records_84.rec[i + 9])[2]  = ((uint32 *)&D_8008D07C[i])[1];
            ((uint32 *)&Game_work.records_84.rec[i + 12])[1] = ((uint32 *)&D_8008D07C[i + 3])[0];
            ((uint32 *)&Game_work.records_84.rec[i + 12])[2] = ((uint32 *)&D_8008D07C[i + 3])[1];
            Game_work.records_84.rec[i + 9].unk_c            = 0;
            Game_work.records_84.rec[i + 12].unk_c           = 0;
        }
    }
    else
    {
        Mem_copy16(&Cd_ring_buf[0][0x1D40], Game_work.records_84.rec, sizeof(Game_work.records_84) / 16);
    }
}
