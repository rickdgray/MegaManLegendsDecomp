#include "common.h"
#include "st13.h"

#ifdef __wasm32__
void func_80031A4C(void *wp);
#endif

void func_801078D4(STAGE_OBJ *wp)
{
    ST13_REC10 *rec;
    STAGE_PL_VIEW *pl;
    uint8 i;
    sint16 dx;
    sint16 dz;
    rec = D_801177FC[Game_work.value_51];
    pl  = &STAGE_PL;
    switch (wp->routine_1)
    {
        case 0:
            if (rec == NULL)
            {
                func_80031A4C(wp);
                break;
            }
            wp->routine_1++;
            // fall through
        case 1:
            for (i = 0; rec->routine_9 != -1; rec++, i++)
            {
                dx = pl->position.x - rec->x_0;
                dz = pl->position.z - rec->z_2;
                if ((uint32)dx < rec->w_4 && (uint32)dz < rec->d_6)
                {
                    wp->u_C.b.byte_C = i;
                    wp->routine_0++;
                    wp->routine_1 = rec->routine_9;
                    break;
                }
            }
            break;
    }
}

void func_801079DC(STAGE_OBJ *wp)
{
    if ((Sce_flag_test(0x4C) == 0) && (Sce_flag_test(0x644) == 0))
    {
        Sce_flag_on(0x644);
        MojiTaskExec2(4, 7);
    }
    wp->routine_0 = 0;
}

void func_80107A38(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(0x4C) || Sce_flag_test(0x645) || (sint8)STAGE_PL.value_74 == 0)
            {
                wp->routine_0 = 0;
                wp->routine_1 = 0;
                break;
            }
            wp->routine_2++;
            break;
        case 1:
            if ((sint8)STAGE_PL.value_74 == 0)
            {
                if (STAGE_PL.position.y >= -0x22)
                {
                    Sce_flag_on(0x645);
                    MojiTaskExec2(4, 9);
                }
                wp->routine_0 = 0;
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_80107B1C(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(0x4C) || Sce_flag_test(0x647))
            {
                wp->routine_0 = 0;
                wp->routine_1 = 0;
                break;
            }
            wp->routine_2++;
            // fall through
        case 1:
            if (Scene_work.reserved00[0] != 0)
            {
                break;
            }
            wp->routine_2++;
            // fall through
        case 2:
            if (func_80042238(&Player_work))
            {
                Sce_flag_on(0x647);
                MojiTaskExec2(0, 0xB);
                wp->routine_2++;
            }
            break;
        case 3:
            if (!(Moji_flag & 0x8000000))
            {
                func_80042314(&Player_work);
                wp->routine_0 = 0;
                wp->routine_1 = 0;
            }
            break;
    }
}

void func_80107C48(STAGE_OBJ *wp)
{
    switch (wp->routine_2)
    {
        case 0:
            if (Sce_flag_test(0x53) || Sce_flag_test(0x64A))
            {
                wp->routine_0 = 0;
                wp->routine_1 = 0;
                break;
            }
            wp->routine_2++;
            // fall through
        case 1:
            if (D_80098B20 != 0)
            {
                wp->routine_2++;
            }
            break;
        case 2:
            if (D_80098B20 == 0)
            {
                Sce_flag_on(0x64A);
                MojiTaskExec2(0, 0x10);
                wp->routine_0 = 0;
                wp->routine_1 = 0;
                wp->routine_2 = 0;
            }
            break;
    }
}

void func_80107D40(STAGE_OBJ *wp)
{
    D_80117828[wp->routine_1](wp, &D_801177FC[Game_work.value_51][wp->u_C.b.byte_C]);
}

void func_80107DA0(STAGE_OBJ *wp)
{
    D_80117838[wp->routine_0](wp);
}
