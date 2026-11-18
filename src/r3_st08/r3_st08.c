#include "common.h"
#include "st08.h"

// Installs the stage's slot routine tables.
void func_8010031C(void)
{
    STAGE_TABLE_3C0 = D_8011206C;
    STAGE_TABLE_5A4 = D_8011220C;
    STAGE_TABLE_10C = D_80112210;
    STAGE_TABLE_48  = D_801122D0;
    STAGE_TABLE_24  = D_80112300;
    STAGE_TABLE_50  = D_8011234C;
}

// Sets up the current room: models, map, spawns.
void func_80100384(void)
{
    ST08_PL_WORK *pl;
    void *spawn;
    sint16 *cells;

    func_80022FD4(D_80112434[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    pl                        = ST08_PL;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    switch (Game_work.value_51)
    {
        case 0:
            Sce_flag_on(0x31B);
            pl->value_44E = 0;
            if (STAGE_GAME_VALUE_52 >= 5)
            {
                func_8003AC9C(func_80048C60(&D_80112974), 0x93300);
            }
            break;
        case 4:
            pl->value_171 = 1;
            pl->value_170 = 0;
            pl->value_44E = -1;
            break;
        default:
            pl->value_44E = 0;
            break;
    }
    spawn                     = D_8011262C[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_801127DC[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_801128E4[D_8011295C[Game_work.value_51]], D_801127F4[Game_work.value_51]);
    func_8005DC10(0);
    func_80100578();
}

void func_80100578(void)
{
    func_8001DEE4();
    Sce_flag_off(0x604);
    Sce_flag_off(0x605);
    func_8001E4C4(D_80113128, D_80113130[STAGE_GAME_VALUE_52]);
    if (Sce_flag_test(0x37))
    {
        func_8001E460(4, 0, 0);
    }
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

// Runs the current room's script (the second set once scene flag 0x1FF is set).
void func_801005F0(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        D_80113110[Game_work.value_51](&D_800989F8);
    }
    if (Sce_flag_test(0x1FF))
    {
        D_801130D0[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100690(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100708(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        wp->routine_4 = 0xFF;
    }
}

void func_80100724(uint8 arg0, uint8 arg1, sint16 arg2, sint16 arg3, uint16 arg4)
{
    D_800C356C = 2;
    D_800C356E = arg0;
    D_800C356F = arg1;
    D_800C3560 = arg2;
    D_800C3562 = arg3;
    D_800C356A = 0;
    D_800C356D = 0;
    D_800C3571 = 0xA;
    D_800C3570 = 2;
    D_800C3564 = (sint16)arg4;
}

void func_80100788(STAGE_ROOM *wp)
{
    ST08_PL_WORK *pl;

    pl = ST08_PL;
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F78);
            wp->routine_4++;
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                if (Sce_flag_test(0x604))
                {
                    func_80100724(8, 3, 0, 0, 0);
                }
                else if (Sce_flag_test(0x605))
                {
                    func_80100724(8, 4, 0, 0, 0);
                }
                else if (Sce_flag_test(0x606))
                {
                    Game_work.value_78 = 0;
                    Sce_flag_on(0x200);
                    func_80100724(5, 0, 0x426, -1, 0x239F);
                }
                Sce_flag_off(0x604);
                Sce_flag_off(0x605);
            }
            if (pl->flags_16B & 2)
            {
                Sce_flag_on(0x607);
            }
            else
            {
                Sce_flag_off(0x607);
            }
            break;
    }
}

void func_801008D8(STAGE_ROOM *wp)
{
    ST08_MUSIC *p;

    for (p = D_8011297C; p->flag != 0xFFFF; p++)
    {
        if (Sce_flag_test(p->flag))
        {
            func_8001DDE4(p->id);
            return;
        }
    }
    if (wp->routine_4 == 0)
    {
        func_8001DDE4(0x51);
        wp->routine_4 = 0xFF;
    }
}

void func_80100984(STAGE_ROOM *wp)
{
    ST08_MUSIC *p;
    STAGE_50 *obj;

    for (p = D_8011297C; p->flag != 0xFFFF; p++)
    {
        if (Sce_flag_test(p->flag))
        {
            func_8001DDE4(p->id);
            return;
        }
    }
    if (wp->routine_4 == 0)
    {
        obj = func_80031734();
        if (obj != NULL)
        {
            obj->flags_0 = 1;
            obj->kind_2  = 0x33;
        }
        wp->routine_4 = 0xFF;
    }
}

void func_80100A48(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80112F90);
        wp->routine_4 = 0xFF;
    }
}

void func_80100A94(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F80);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(2);
                func_8001E20C(3);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100B48(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80112F70);
        wp->routine_4 = 0xFF;
    }
}

void func_80100B94(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F80);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(2);
                func_8001E20C(3);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100C48(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80112F70);
        wp->routine_4 = 0xFF;
    }
}

void func_80100C94(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F80);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(2);
                func_8001E20C(3);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100D48(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80112F70);
        wp->routine_4 = 0xFF;
    }
}

void func_80100D94(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F80);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(2);
                func_8001E20C(3);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100E48(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_80112F70);
        wp->routine_4 = 0xFF;
    }
}

void func_80100E94(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F88);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(5);
                func_8001E20C(6);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100F48(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F88);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(5);
                func_8001E20C(6);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100FFC(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_8001DF10(D_80112F98);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(5);
                func_8001E20C(6);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_801010B0(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_80101424();
            func_8001DF10(D_80112FA0);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(5);
                func_8001E20C(6);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_8010116C(STAGE_ROOM_WORK *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_80101424();
            func_8001DF10(D_80112FA8);
            if (Sce_flag_test(0x37))
            {
                func_8001E20C(5);
                func_8001E20C(6);
            }
            wp->routine_4++;
            break;
        case 1:
            if (Sce_flag_test(0x225) || Sce_flag_test(0x37))
            {
                func_8001E460(4, 0, 0);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

sint32 func_80101228(STAGE_ROOM *wp)
{
    if ((wp->routine_4 == 0) && (Sce_flag_test(0x22E) != 0) && (Sce_flag_test(0x22F) == 0))
    {
        Sce_flag_on(0x22F);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101280(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        if (STAGE_GAME_VALUE_52 < 8)
        {
            Sce_flag_off(0x22D);
        }
        if (Sce_flag_test(0x22D) && !Sce_flag_test(0x22E))
        {
            func_8001DDE4(0x55);
        }
        if (Sce_flag_test(0x22E) && Sce_flag_test(0x22F))
        {
            func_8001EB98(D_80113190);
        }
        if (Sce_flag_test(0x55) && !Sce_flag_test(0x233))
        {
            func_8001EB98(D_801131A4);
        }
        Sce_flag_on(0x7E6);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101360(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_4 == 0 && Sce_flag_test(0x233))
    {
        if (!Sce_flag_test(0x234))
        {
            func_8001EB98(D_801131B8);
            func_8001E3F0(0xB);
        }
        else
        {
            func_8001EB98(D_801131CC);
        }
        func_8001EB98(&D_801131E0[0]);
        func_8001EB98(&D_801131E0[1]);
    }
    Sce_flag_on(0x1FF);
    return 0;
}

sint32 func_80101404(void)
{
    Sce_flag_on(0x1FF);
    return 0;
}

void func_80101424(void)
{
    STCOM_SVECTOR pos = {0x1900, 0, 0x300, 0};

    func_8003AC9C(func_80048C60(&pos), 0x80100000);
}

// Puts the player at (x, y, z) facing `angle`.
void func_80101478(sint16 x, sint16 y, sint16 z, sint16 angle)
{
    ST08_PL->routine_0   = 3;
    ST08_PL->routine_1   = 1;
    ST08_PL->pos_438.x   = x;
    ST08_PL->pos_438.y   = y;
    ST08_PL->pos_438.z   = z;
    ST08_PL->fixed_428.x = x << 16;
    ST08_PL->fixed_428.y = y << 16;
    ST08_PL->fixed_428.z = z << 16;
    ST08_PL->rot_440.x   = 0;
    ST08_PL->rot_440.y   = angle;
    ST08_PL->rot_440.z   = 0;
    ST08_PL->value_448   = 0;
    ST08_PL->flags_bd |= 0x10;
}

// Inserts `score` into a three-entry ranking (highest first); returns its place, or 3.
uint8 func_80101508(ST08_RANK *tbl, uint32 score)
{
    sint32 i;
    sint32 j;
    sint32 k;

    for (i = 0; i < 3; i++)
    {
        if (score >= tbl[i].score)
        {
            if (i < 2)
            {
                for (j = 2; j > i; j--)
                {
                    tbl[j].score = tbl[j - 1].score;
                    for (k = 0; k < 4; k++)
                    {
                        tbl[j].value[k] = tbl[j - 1].value[k];
                    }
                }
            }
            tbl[i].score = score;
            return i;
        }
    }
    return 3;
}

void func_8010159C(sint16 arg0, sint16 arg1, sint16 arg2, sint16 arg3)
{
    D_800C356C = 1;
    D_800C356E = 8;
    D_800C356F = 2;
    D_800C3560 = arg0;
    D_800C3562 = arg1;
    D_800C3564 = arg2;
    D_800C356A = arg3;
    D_800C356D = 0;
    D_800C3571 = 0xA;
    D_800C3570 = 2;
}

void func_80101604(STAGE_ROOM *wp)
{
    ST08_PL_WORK *pl;
    STAGE_OBJ *obj;
    uint16 *mask;

    pl = ST08_PL;
    if (++STAGE_SCENE_WORD(0xC) >= 900)
    {
        wp->routine_4 = 6;
        return;
    }
    if (STAGE_SCENE_WORD(0xC) % 300 == 0)
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            obj->flags_0   = 1;
            obj->kind_2    = 8;
            obj->routine_0 = 2;
        }
    }
    mask = D_800C0C2A_A;
    *mask &= pl->key_12C | pl->key_12E | (pl->key_13A | pl->key_13C) | 9;
    D_800C0C26_S.value &=
        pl->key_134 | (pl->key_12C | pl->key_12E | (pl->key_13A | pl->key_13C)) | 9;
    if (Player_work.position.x < -200)
    {
        D_800C0C26_S.value &= ~pl->key_12C;
        *mask &= ~pl->key_12C;
    }
    if (Player_work.position.x > 200)
    {
        D_800C0C26_S.value &= ~pl->key_12E;
        *mask &= ~pl->key_12E;
    }
}

void func_80101798(void)
{
    STAGE_OBJ *obj;
    STAGE_10C *shot;
    STAGE_50 *item;
    sint32 i;

    for (i = 0; i < 2; i++)
    {
        obj = func_80031418();
        if (obj != NULL)
        {
            obj->flags_0   = 1;
            obj->kind_2    = 8;
            obj->variant_3 = i;
        }
    }
    shot = func_80031518();
    if (shot != NULL)
    {
        shot->flags_0 = 1;
        shot->kind_2  = 0x21;
    }
    item = func_80031734();
    if (item != NULL)
    {
        item->flags_0   = 1;
        item->kind_2    = 0x1F;
        item->variant_3 = 1;
    }
    func_80101478(0, -1, -0xE0, 0x800);
}

void func_80101858(STAGE_ROOM *wp)
{
    if (ST08_GAME_WORD(0x120) == 3)
    {
        func_8005C224(D_80113220 +
                      (Scene_work.value_A - D_80113224) * (Scene_work.value_A - D_80113224) * 2);
    }
    else
    {
        func_8005C224(D_80113208[ST08_GAME_WORD(0x120)].value_0);
    }
}

void func_801018CC(STAGE_ROOM *wp)
{
    STAGE_CAM *cam;

    cam = &D_800BC730;
    switch (wp->routine_4)
    {
        case 0:
            if (func_80042238(&Player_work))
            {
                func_8001D854(0x10);
                func_80101798();
                STAGE_GAME.value_83 = 2;
                func_800425FC(&Player_work, 0);
                ST08_PL->value_44B = 1;
                func_8001E6C0(0, 0, 0);
                cam->pos_10   = 0;
                cam->pos_14   = -0x100 << 16;
                cam->pos_18   = 0x490 << 16;
                cam->rot_40   = 0x800 << 16;
                cam->rot_44   = 0x70 << 16;
                cam->rot_48   = 0x200 << 16;
                wp->routine_4 = 1;
            }
            break;
        case 1:
            if (D_80098A72 == 0 && D_80098788 == 0)
            {
                Sound_call(0x19, 1, 0);
                wp->routine_4 = 2;
            }
            break;
        case 2:
            if (wp->routine_5 == 0)
            {
                cam->pos_18 += -0x12 << 16;
                if (cam->pos_18 <= -0x20E << 16)
                {
                    cam->pos_18 = -0x20E << 16;
                    wp->routine_5++;
                }
            }
            else
            {
                cam->rot_40 += -0x2D << 16;
                if (cam->rot_40 <= 0)
                {
                    cam->rot_40 = 0;
                    MojiTaskExec2(0, 0);
                    wp->routine_4 = 3;
                    wp->routine_5 = 0;
                }
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_8001D854(0x10);
                MojiTaskExec2(0, ST08_GAME_WORD(0x120) + 9);
                wp->routine_4 = 4;
            }
            break;
        case 4:
            if (!(Moji_flag & 0x8000000) && D_80098788 == 0)
            {
                Sound_call2(0x163, &Player_work.position);
                Sound_work.volume_6 = 0x1E;
                func_8001D58C(0x2001000F);
                Scene_work.value_A    = 0;
                Scene_work.value_10   = 0;
                STAGE_SCENE_WORD(0xC) = 0;
                func_80042314(&Player_work);
                MojiTaskExec2(2, 0x1A);
                MojiTaskExec2(1, 0x23);
                MojiTaskExec2(3, ST08_GAME_WORD(0x120) + 0x2D);
                wp->routine_4 = 5;
            }
            break;
        case 5:
            func_80101604(wp);
            break;
        case 6:
            if (func_80042238(&Player_work))
            {
                Sound_call2(0x163, &Player_work.position);
                func_8001D854(0x40);
                func_80053AA4(2);
                func_80053AA4(3);
                func_80053AA4(1);
                MojiTaskExec2(0, 0x1F);
                wp->routine_4 = 7;
            }
            break;
        case 7:
            if (!(Moji_flag & 0x8000000) && D_80098788 == 0)
            {
                if (Scene_work.value_A < (uint8)D_80113208[ST08_GAME_WORD(0x120)].value_4)
                {
                    Sound_call(0x1A, 1, 0);
                    MojiTaskExec2(0, 3);
                    D_80118510    = 0xFF;
                    wp->routine_4 = 8;
                    break;
                }
                D_80118510 = func_80101508((ST08_RANK *)&ST08_GAME_WORD(0x114), Scene_work.value_A);
                func_8001E3F0(7);
                if (!Sce_flag_test(0x314))
                {
                    if (D_80118510 == 0)
                    {
                        if (ST08_GAME_WORD(0x120) == 3)
                        {
                            func_8005C218(0x64);
                            MojiTaskExec2(0, 7);
                            Sce_flag_on(0x314);
                            Sound_call(0x1C, 1, 0);
                            Sound_call2(0x164, &Player_work.position);
                        }
                        else
                        {
                            func_80101858(wp);
                            MojiTaskExec2(0, 6);
                            Sound_call(0x1C, 1, 0);
                            Sound_call2(0x164, &Player_work.position);
                        }
                    }
                    else if (ST08_GAME_WORD(0x120) == 3)
                    {
                        func_8005C218(0x64);
                        Sce_flag_on(0x314);
                        MojiTaskExec2(0, 5);
                        Sound_call(0x1B, 1, 0);
                    }
                    else
                    {
                        func_80101858(wp);
                        MojiTaskExec2(0, 4);
                        Sound_call(0x1B, 1, 0);
                    }
                }
                else if (D_80118510 == 0)
                {
                    func_80101858(wp);
                    MojiTaskExec2(0, 6);
                    Sound_call(0x1C, 1, 0);
                    Sound_call2(0x164, &Player_work.position);
                }
                else
                {
                    func_80101858(wp);
                    MojiTaskExec2(0, 4);
                    Sound_call(0x1B, 1, 0);
                }
                if ((uint32)ST08_GAME_WORD(0x120) < 3)
                {
                    ST08_GAME_WORD(0x120)++;
                }
                wp->routine_4 = 8;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                if (D_80118510 < 3)
                {
                    func_8005C24C(D_80118510 + 9);
                    MojiTaskExec2(0, 0x1C);
                }
                else
                {
                    MojiTaskExec2(0, 0x1D);
                }
                wp->routine_4 = 9;
            }
            break;
        case 9:
            if (!(Moji_flag & 0x8000000) && !func_8001A0A8(0))
            {
                if (!(Moji_flag & 0xFF))
                {
                    func_80017C30(9);
                    wp->routine_4 = 10;
                }
                else
                {
                    MojiTaskExec2(0, 8);
                    wp->routine_4 = 0xD;
                }
            }
            break;
        case 10:
            if (D_80098A72 == 0)
            {
                wp->routine_4 = 0xB;
            }
            break;
        case 11:
            func_80101798();
            func_80017C30(1);
            wp->routine_4 = 0xC;
            break;
        case 12:
            if (D_80098A72 == 0)
            {
                wp->routine_4 = 3;
            }
            break;
        case 13:
            if (!(Moji_flag & 0x8000000))
            {
                func_8010159C(-0xBE, -0x41, 0x296, 0x800);
                wp->routine_4 = 0xE;
            }
            break;
        case 14:
            if (D_800C356C_A[0] == 2)
            {
                func_8001D854(0xA0);
                STAGE_GAME.value_83 = 0;
                D_800C356C_A[0]++;
                func_80042314(&Player_work);
                D_800A395C         = 1;
                ST08_PL->value_44B = 0;
                func_80039820();
                Sound_work.volume_6 = 0x7F;
                func_800425FC(&Player_work, (sint8)STAGE_GAME_BYTE(0x54));
                wp->flags_0 = 0;
            }
            break;
    }
    func_8005C230(STAGE_SCENE_WORD(0xC));
    func_8005C23C(Scene_work.value_A);
}

void func_80101F84(STAGE_FX *wp)
{
    func_801018CC(wp);
}

void func_80101FA4(STAGE_ROOM *wp)
{
    D_80113228[wp->routine_4](wp);
}

void func_80101FE0(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;
    STAGE_EV *slot;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            slot = func_8001EAE8(D_80113238);
            slot->flags_6 &= ~0x20;
            func_8001E6C0(0, 0, 0);
            D_800BC7F0 = D_8011324C;
            wp->tbl_A4 = (STAGE_ROOM2_FUNC *)D_801132EC;
            wp->routine_5++;
            // fall through
        case 1:
            if (func_80042238(pl))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 0;
                pl->flags_0 &= ~2;
                wp->routine_5 = 0;
                wp->routine_6 = 0;
                wp->routine_7 = 0;
                wp->routine_4++;
                func_8001F158();
            }
            break;
    }
}

void func_801020C4(STAGE_ROOM *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
        if (func_8001DE84())
        {
            func_80017C30(0xA);
            wp->routine_5 = 0;
            wp->routine_4++;
        }
    }
    else
    {
        wp->routine_5 = 0;
        wp->routine_4 += 2;
    }
    func_8001EC0C();
    func_8001F070();
}

void func_80102158(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
    if (D_80098A72 == 0)
    {
        wp->routine_4++;
    }
    func_8001EC0C();
    func_8001F070();
}

void func_801021D8(STAGE_ROOM *wp)
{
    STCOM_PL_WORK *pl;

    pl = &Player_work;
    switch (wp->routine_5)
    {
        case 0:
            wp->routine_5++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                func_8003697C();
                func_80042314(pl);
                D_800A395C = 1;
                func_80039820();
                wp->routine_5++;
            }
            break;
        case 2:
            D_800C356C = 2;
            D_800C356E = 8;
            D_800C356F = 1;
            D_800C3560 = -0x100;
            D_800C3562 = -1;
            D_800C3564 = 0x80;
            D_800C356A = 0;
            D_800C356D = 0;
            D_800C3571 = 0xFF;
            D_800C3570 = 2;
            pl->flags_0 |= 3;
            Sce_flag_on(0x22E);
            wp->flags_0 = 0;
            break;
    }
}

void func_80102320(void)
{
}

void func_80102328(STAGE_FX *wp)
{
    uint8 temp_v1;

    temp_v1 = wp->flags_6;
    switch (temp_v1)
    {
        case 0:
            func_80017C30(0xA);
            wp->flags_6++;
            return;
        case 1:
            if (D_80098A72 == 0)
            {
                func_8001F158();
            }
            return;
    }
}

void func_801023A4(STAGE_ROOM *wp)
{
    if (func_80042238(&Player_work))
    {
        ST08_PL->routine_1 = 0x10;
        ST08_PL->flags_bd |= 0x10;
        ST08_PL->rot_440.x   = 0;
        ST08_PL->rot_440.z   = 0;
        ST08_PL->value_A     = 0;
        D_80118514           = 0;
        ST08_PL->pos_438.x   = ST08_PL->position.x;
        ST08_PL->pos_438.y   = ST08_PL->position.y;
        ST08_PL->pos_438.z   = ST08_PL->position.z;
        ST08_PL->fixed_428.x = ST08_PL->pos_438.x << 16;
        ST08_PL->fixed_428.y = ST08_PL->pos_438.y << 16;
        ST08_PL->fixed_428.z = ST08_PL->pos_438.z << 16;
        ST08_PL->rot_440.y   = ST08_PL->rotation.y;
        wp->routine_5        = 0;
        wp->routine_6        = 0;
        wp->routine_7        = 0;
        wp->routine_4++;
    }
}

void func_80102498(STAGE_ROOM *wp)
{
    STCOM_FIXED_VECTOR vec;
    STCOM_SVECTOR pos;
    ST08_PL_WORK *pl;
    STAGE_CAM *cam;
    ST08_ACTOR *actor;
    STAGE_OBJ *other;
    sint16 turn;

    pl    = ST08_PL;
    cam   = &D_800BC730;
    actor = (ST08_ACTOR *)wp->child_24;
    other = wp->child_28;
    switch (wp->routine_5)
    {
        case 0:
            pos   = actor->position;
            vec.x = actor->position.x;
            vec.y = actor->position.y - 0x92;
            vec.z = actor->position.z;
            func_80039FFC(&vec, 0xD4, func_80031198(&pos, &pl->position), 0);
            pl->flags_0 &= ~2;
            wp->routine_5++;
            break;
        case 1:
            turn = func_80031BEC(&actor->position, &pl->pos_438, actor->rotation.v.y, 0x80);
            actor->rotation.v.y += turn;
            if (!func_8003A13C() && turn == 0)
            {
                actor->value_D = 9;
                actor->value_E = 1;
                wp->frame_10   = 0x10;
                wp->routine_5++;
            }
            break;
        case 2:
            if (--wp->frame_10 == 0)
            {
                MojiTaskExec2(0, 0x1B);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                actor->value_D = 5;
                actor->value_E = 1;
                wp->frame_10   = 0x22;
                wp->routine_5++;
            }
            break;
        case 4:
            if (--wp->frame_10 == 0)
            {
                func_80039E50();
                actor->rotation.v.y     = 0xA78;
                actor->value_D          = 6;
                actor->value_E          = 1;
                actor->position.x       = -0x4CE;
                actor->position.z       = 0x71C;
                actor->position_fixed.x = actor->position_fixed_prev.x = actor->position.x << 16;
                actor->position_fixed.z = actor->position_fixed_prev.z = actor->position.z << 16;
                pl->pos_438.x                                          = -0x514;
                pl->pos_438.z                                          = 0x692;
                pl->flags_0 |= 2;
                pl->flags_bd |= 0x10;
                pl->fixed_428.x = pl->pos_438.x << 16;
                pl->fixed_428.z = pl->pos_438.z << 16;
                pl->rot_440.y   = func_80031198(&pl->pos_438, &actor->position);
                func_8001E6C0(0, 0, 0);
                cam->pos_10  = -0x365 << 16;
                cam->pos_14  = -0x2D1 << 16;
                cam->pos_18  = 0x73C << 16;
                cam->rot_40  = 0xBA9 << 16;
                cam->rot_44  = 0xF0 << 16;
                cam->rot_48  = 0;
                wp->frame_10 = 0x3C;
                wp->routine_5++;
            }
            break;
        case 5:
            if (--wp->frame_10 == 0)
            {
                actor->value_D = 7;
                actor->value_E = 1;
                wp->frame_10   = 0x2D;
                wp->routine_5++;
            }
            break;
        case 6:
            if (--wp->frame_10 == 0)
            {
                actor->value_D = 9;
                actor->value_E = 1;
                wp->frame_10   = 0x14;
                wp->routine_5++;
            }
            break;
        case 7:
            if (--wp->frame_10 == 0)
            {
                MojiTaskExec2(0, 0x1C);
                actor->value_D = 10;
                actor->value_E = 1;
                wp->routine_5++;
            }
            break;
        case 8:
            if (!(Moji_flag & 0x8000000))
            {
                actor->value_D = 0xD;
                actor->value_E = 1;
                wp->frame_10   = 10;
                wp->routine_5++;
            }
            break;
        case 9:
            turn = func_80031BEC(&actor->position, &pl->pos_438, actor->rotation.v.y, 0x80);
            actor->rotation.v.y += turn;
            if (turn == 0)
            {
                MojiTaskExec2(0, 0x24);
                actor->value_D = 8;
                actor->value_E = 1;
                wp->routine_5++;
            }
            break;
        case 10:
            if (!(Moji_flag & 0x8000000))
            {
                func_80031824(other);
                cam->pos_10             = -0x52E << 16;
                cam->pos_14             = -0x271 << 16;
                cam->pos_18             = 0x6A1 << 16;
                cam->rot_40             = 0x9F9 << 16;
                cam->rot_44             = 0x40 << 16;
                cam->rot_48             = 0x150 << 16;
                actor->position.x       = -0x4B0;
                actor->position.z       = 0x5DC;
                actor->position_fixed.x = actor->position.x << 16;
                actor->position_fixed.z = actor->position.z << 16;
                pos.x                   = -0xF9E;
                pos.y                   = -0x2F0;
                pos.z                   = -0x1E0;
                actor->rotation.v.y     = func_80031198(&actor->position, &pos);
                actor->velocity.v.x     = 0x320;
                actor->value_D          = 2;
                actor->value_E          = 1;
                pl->flags_bd |= 0x10;
                pl->rot_440.y = func_80031198(&pl->pos_438, &actor->position);
                wp->routine_5++;
            }
            break;
        case 11:
            if (actor->position.x < -0xC1C)
            {
                actor->rotation.v.y = 0;
                wp->routine_5++;
            }
            else
            {
                pl->flags_bd |= 0x10;
                pl->rot_440.y = func_80031198(&pl->pos_438, &actor->position);
            }
            break;
        case 12:
            if (actor->position.z < -0x190)
            {
                actor->rotation.v.y = 0xC00;
                wp->routine_5++;
            }
            break;
        case 13:
            if (actor->position.x >= -0x7CF)
            {
                func_80031824(actor);
                wp->routine_5 = 0;
                wp->routine_4++;
            }
            break;
    }
    if (func_8001DE84() && wp->routine_4 == 1)
    {
        if (wp->routine_5 < 5)
        {
            func_80039E50();
        }
        func_80053AA4(0);
        D_80118514    = 1;
        wp->routine_5 = 0;
        wp->routine_4++;
    }
}

void func_80102A24(STAGE_ROOM *wp)
{
    switch (wp->routine_5)
    {
        case 0:
            ST08_PL->flags_bd |= 0x10;
            if (D_80118514 != 0)
            {
                ST08_PL->pos_438.x   = -0x514;
                ST08_PL->pos_438.z   = 0x692;
                ST08_PL->fixed_428.x = -0x514 << 16;
                ST08_PL->fixed_428.z = 0x692 << 16;
                func_80031824(wp->child_24);
                func_80031824(wp->child_28);
            }
            ST08_PL->rot_440.y = 0x400;
            wp->routine_5++;
            break;
        case 1:
            func_8001D494(0, 1, 0);
            Sce_flag_off(0x549);
            Sce_flag_on(0x37);
            func_8001E3F0(0x18);
            func_8001E390(0x2E8);
            func_80042314(&Player_work);
            D_800A395C = 1;
            ST08_PL->value_A++;
            func_80039820();
            wp->flags_0 = 0;
            break;
    }
}

void func_80102B58(STAGE_ROOM *wp)
{
    D_8011330C[wp->routine_4](wp);
}
