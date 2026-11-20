#include "common.h"
#include "st1b.h"

void func_8010021C(void)
{
}

void func_80100224(void)
{
}

void func_8010022C(STAGE_ROOM_WORK *wp)
{
    if (wp->routine_8 != 0xFF)
    {
        wp->tbl_A4[1](wp);
    }
}

void func_8010026C(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            func_80017C30(0xA);
            wp->routine_4++;
            break;
        case 1:
            if (D_80098A72 == 0)
            {
                Sce_flag_on(0x22D);
                wp->routine_4++;
            }
            break;
        case 2:
            D_800C356C  = 2;
            D_800C356E  = 8;
            D_800C356F  = 1;
            D_800C3560  = -0x100;
            D_800C3562  = -1;
            D_800C356A  = 0;
            D_800C3564  = 0x80;
            D_800C356D  = 0;
            D_800C3571  = 0xFF;
            D_800C3570  = 2;
            wp->flags_0 = 0;
            break;
    }
}

void func_80100378(STAGE_ROOM *wp)
{
    if (func_80042238(&Player_work) != 0)
    {
        STAGE_PL.routine_0 = 3;
        STAGE_PL.routine_1 = 1;
        STAGE_PL.flags_bd |= 0x10;
        STAGE_PL.pos_438.x   = STAGE_PL.position.x;
        STAGE_PL.pos_438.y   = STAGE_PL.position.y;
        STAGE_PL.pos_438.z   = STAGE_PL.position.z;
        STAGE_PL.value_440   = 0;
        STAGE_PL.fixed_428.x = STAGE_PL.position.x << 16;
        STAGE_PL.fixed_428.y = STAGE_PL.position.y << 16;
        STAGE_PL.fixed_428.z = STAGE_PL.position.z << 16;
        STAGE_PL.value_444   = 0;
        STAGE_PL.value_442   = 0xB2C;
        func_8001E6C0(0, 0, 0);
        D_800BC740    = -0x120000;
        D_800BC744    = -0x970000;
        D_800BC748    = -0x340000;
        D_800BC770    = 0x10000000;
        D_800BC774    = 0;
        D_800BC778    = 0;
        wp->routine_5 = 0;
        wp->routine_6 = 0;
        wp->routine_7 = 0;
        wp->routine_4++;
    }
}

void func_801004B4(STAGE_ROOM *wp)
{
    ST1B_CAM *cam;
    ST1B_CAMERA *req;
    STAGE_PL_VIEW *pl;
    cam = &Sce_camera_work;
    req = &D_800C3558;
    pl  = &STAGE_PL;
    switch (wp->routine_5)
    {
        case 0:
            if (D_80098A72 == 0)
            {
                MojiTaskExec2(0, 0xA);
                wp->routine_5++;
            }
            break;
        case 1:
            if (!(Moji_flag & 0x8000000))
            {
                pl->routine_0 = 3;
                pl->routine_1 = 1;
                pl->value_448 = 0x30;
                pl->value_168 = 0xC;
                pl->value_169 = 0xC;
                pl->flags_bd |= 0x10;
                wp->frame_10 = 8;
                wp->routine_5++;
            }
            break;
        case 2:
            cam->rot_40 += -0x9A8000;
            cam->pos_10 += -0x18C000;
            cam->pos_14 += 0x52000;
            cam->pos_18 += -0x86000;
            if (--wp->frame_10 == 0)
            {
                cam->pos_10 = -0xD80000;
                cam->pos_14 = -0x6E0000;
                cam->pos_18 = -0x770000;
                cam->rot_40 = 0xB2C0000;
                MojiTaskExec2(0, 0xB);
                wp->routine_5++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                req->state_14 = 1;
                req->mode_16  = 0x1B;
                req->value_17 = 7;
                req->x_8      = 0xC1;
                req->y_A      = -1;
                req->value_12 = 0;
                req->z_C      = -0x101;
                req->value_15 = 0;
                req->value_19 = 9;
                req->value_18 = 1;
                wp->routine_5++;
            }
            break;
        case 4:
            if (req->state_14 == 2)
            {
                req->state_14++;
                D_800A395C = 1;
                func_80039820();
                wp->routine_5++;
            }
            break;
        case 5:
            if (req->state_14 == 0)
            {
                MojiTaskExec2(0, 0x2D);
                pl->value_448 = 0;
                pl->value_168 = 0;
                pl->value_169 = 0;
                wp->routine_5++;
            }
            break;
        case 6:
            if (!(Moji_flag & 0x8000000))
            {
                wp->routine_5++;
            }
            break;
        case 7:
            wp->routine_5 = 0;
            wp->routine_4++;
            break;
    }
}

void func_80100724(sint8 *arg0)
{
    func_80042314((STCOM_PL_WORK *)&Player_work);
    Cd_subcmd(0, 1, 0);
    *arg0 = 0;
}

void func_8010076C(STAGE_ROOM *wp)
{
    D_8010C574[wp->routine_4](wp);
}

void func_801007A8(void)
{
    STAGE_TABLE_3C0      = D_8010C608;
    STAGE_TABLE_5A4      = D_8010C79C;
    STAGE_TABLE_10C      = D_8010C7B8;
    STAGE_TABLE_48       = D_8010C80C;
    STAGE_TABLE_24       = D_8010C810;
    STAGE_TABLE_50       = D_8010C884;
    STAGE_PL_BYTE(0x170) = 0;
}

void func_80100818(void)
{
    STAGE_PL_VIEW *pl;
    sint16 *cells;
    void *spawn;
    func_80022FD4(D_8010C8C4[Game_work.value_51]);
    STAGE_MAP_WORK_PTR->w     = STAGE_MAP_TBL[Game_work.value_51].w;
    STAGE_MAP_WORK_PTR->h     = STAGE_MAP_TBL[Game_work.value_51].h;
    STAGE_MAP_WORK_PTR->x0    = STAGE_MAP_TBL[Game_work.value_51].x0;
    STAGE_MAP_WORK_PTR->z0    = STAGE_MAP_TBL[Game_work.value_51].z0;
    STAGE_MAP_WORK_PTR->x1    = STAGE_MAP_WORK_PTR->x0 + STAGE_MAP_WORK_PTR->w;
    STAGE_MAP_WORK_PTR->z1    = STAGE_MAP_WORK_PTR->z0 + STAGE_MAP_WORK_PTR->h;
    cells                     = STAGE_MAP_TBL[Game_work.value_51].cells;
    STAGE_MAP_WORK_PTR->info  = STAGE_CELL_INFO;
    STAGE_MAP_WORK_PTR->cells = cells;
    pl                        = &STAGE_PL;
    if (STAGE_GAME_VALUE_52 != 0xB)
    {
        switch (Game_work.value_51)
        {
            case 1:
                Game_work.value_79    = 0x1B;
                Game_work.value_7A    = 1;
                STAGE_GAME_BYTE(0x7B) = 0;
                // fall through
            case 0:
            case 2:
                pl->value_44E = 1;
                break;
            default:
                pl->value_44E = 0;
                break;
        }
    }
    else
    {
        Game_work.value_78    = 0;
        STAGE_GAME_BYTE(0x7B) = 0;
        STAGE_PL_BYTE(0x44E)  = 0;
        STAGE_PL_BYTE(0x44F)  = 0;
    }
    spawn                     = D_8010CB18[Game_work.value_51];
    STAGE_MAP_WORK_PTR->exits = D_8010CD7C[Game_work.value_51];
    func_8002EA50(spawn, D_800C356D);
    func_800371A0(D_8010CF08[D_8010D108[Game_work.value_51]], D_8010CDA0[Game_work.value_51]);
    func_8005DC10(0);
    func_80100A20();
}

void func_80100A20(void)
{
    func_8001DEE4();
    func_8001E4C4(D_8010DAA0, D_8010DAA8[STAGE_GAME_VALUE_52]);
    *(uint32 *)&D_800989F8.routine_4 = 0;
}

void func_80100A6C(void)
{
    if (!Sce_flag_test(0x1FF))
    {
        if (STAGE_GAME_VALUE_52 != 0xB)
        {
            D_8010D950[Game_work.value_51](&D_800989F8);
        }
        else
        {
            Sce_flag_on(0x1FF);
        }
    }
    if (Sce_flag_test(0x1FF))
    {
        D_8010D204[STAGE_GAME_VALUE_52][Game_work.value_51](&D_800989F8);
    }
}

void func_80100B30(STAGE_ROOM *wp)
{
    if (wp->routine_4 == 0)
    {
        func_8001DF10(D_8010D938);
        wp->routine_4++;
    }
}

void func_80100B84(STAGE_ROOM *wp)
{
    switch (wp->routine_4)
    {
        case 0:
            if (!Sce_flag_test(0x4D))
            {
                Sce_flag_on(0x4D);
                func_8001DDE4(0x48);
                break;
            }
            func_8001DF10(D_8010D940);
            if (!Sce_flag_test(0x70))
            {
                Sce_flag_on(0x70);
                func_80017C30(2);
            }
            wp->routine_4 = 1;
            break;
        case 1:
            if (Sce_flag_test(0x4E) && !(Moji_flag & 0x8000000))
            {
                Sce_flag_on(0x4E);
                func_8001DDE4(0x49);
                wp->routine_4 = 0xFF;
            }
            break;
    }
}

void func_80100C68(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        func_8001DF10(&D_8010D948);
        if (Sce_flag_test(0x6F) == 0)
        {
            func_8001E20C(0);
            func_8001E20C(1);
            func_8001E20C(2);
        }
        wp->value_4++;
    }
}

void func_80100CE4(void)
{
}

void func_80100CEC(void)
{
}

void func_80100CF4(void)
{
}

void func_80100CFC(STAGE_OBJ *wp)
{
    if (wp->value_4 == 0)
    {
        if ((Sce_flag_test(0x33) == 0) && (Sce_flag_test(0x21) != 0))
        {
            func_8001DDE4(0x56);
            Sce_flag_on(0x33);
        }
        wp->value_4 = 0xFF;
    }
}

void func_80100D68(void)
{
}
