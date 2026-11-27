#include "common.h"
#include "st06.h"

void func_80105D20(STAGE_ROOM *wp)
{
    STAGE_PL_VIEW *pl;
    ST06_ENTRY *entry;
    STCOM_FIXED_VECTOR unused; // unused: reserves the frame's 16 extra bytes

    pl = &STAGE_PL;
    switch (wp->routine_4)
    {
        case 0:
            Fade_start(2);
            func_80105C3C(wp);
            wp->routine_4++;
            pl->flags_0 |= 3;
            Sce_camera_update();
            Sce_event_update();
            break;
        case 1:
            if (func_80042238(pl) != 0)
            {
                pl->routine_0   = 3;
                pl->routine_1   = 1;
                pl->value_448   = 0x30;
                pl->pos_438.x   = 0x200;
                pl->pos_438.y   = -0x301;
                pl->pos_438.z   = 0x2E8;
                pl->fixed_428.x = 0x2000000;
                pl->fixed_428.y = 0xFCFF0000;
                pl->fixed_428.z = 0x2E80000;
                pl->value_440   = 0;
                pl->value_442   = 0x800;
                pl->value_444   = 0;
                pl->flags_bd |= 0x10;
                wp->routine_4++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 2:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            Sce_camera_update();
            Sce_event_update();
            break;
        case 3:
            D_800C0F96[0] = 0;
            pl->flags_bd |= 0x20;
            wp->reserved09[1] = 1;
            Sce_event_next();
            wp->routine_4++;
            Sce_camera_update();
            Sce_event_update();
            break;
        case 4:
            if (wp->reserved09[2] != 0)
            {
                wp->routine_4++;
                break;
            }
            if (func_8001DE84() != 0 && wp->reserved09[1] == 1)
            {
                func_80053AA4(0);
                Cd_subcmd(0, 1, 0);
                wp->routine_4 = 0xC;
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 5:
            if (D_800C356C_A[0] == 2)
            {
                func_80031824(wp->child_24);
                wp->routine_4++;
                D_800C356C_A[0]++;
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 6:
            if (D_800C356C == 0)
            {
                Fade_start(2);
                func_8001E6C0(0, 0, 0);
                wp->routine_4++;
                Sce_event_next();
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 7:
            wp->routine_4++;
            Sce_event_next();
            break;
        case 8:
            if (D_80098A72 == 0)
            {
                wp->reserved09[1] = 1;
                wp->routine_4++;
                Sce_event_next();
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 9:
            if (wp->routine_8 == 0xFF)
            {
                wp->routine_4++;
                break;
            }
            if (func_8001DE84() != 0 && wp->reserved09[1] == 1)
            {
                func_80053AA4(0);
                Cd_subcmd(0, 1, 0);
                wp->routine_4 = 0x10;
            }
            func_80105CE0((STAGE_ROOM_WORK *)wp);
            Sce_camera_update();
            Sce_event_update();
            break;
        case 10:
            if (D_80098A72 == 0)
            {
                wp->routine_4++;
            }
            break;
        case 11:
            if (!(Moji_flag & 0x08000000))
            {
                Player_work.flags_0 |= 2;
                func_80042314(&Player_work);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                wp->child_24->variant_3 = wp->child_30->variant_3 = 1;
                wp->child_24->routine_0 = wp->child_30->routine_0 = 0;
                wp->child_24->u_C.b.byte_C                        = 0x46;
                wp->child_30->u_C.b.byte_C                        = 0x47;
                wp->child_24->position.x                          = 0x6F;
                wp->child_24->position.z -= 0x14;
                wp->child_30->position.x += 0xA;
                wp->child_30->position.z = -0x13D;
                func_80031824(wp->child_28);
                func_80031824(wp->child_2C);
                func_80031824(wp->child_30);
                Scene_obj_ent_open(&D_80123F4C[0]);
                Scene_obj_ent_open(&D_80123F4C[1]);
                Sce_flag_on(0x2C);
                Sce_flag_off(0x7E0);
                func_8001D974();
                wp->flags_0 = 0;
            }
            break;
        case 12:
            entry      = &D_800C3558;
            D_800C356C = 1;
            D_800C356E = 6;
            if (Sce_flag_test(0x629) != 0)
            {
                D_800C356F = 4;
            }
            else
            {
                D_800C356F = 1;
            }
            entry->fade_out = 9;
            entry->flags15  = 0;
            entry->fade_in  = 0xFF;
            wp->routine_4++;
            break;
        case 13:
            if (D_800C356C_A[0] == 2)
            {
                func_80031824(wp->child_24);
                func_8003697C();
                D_800A395C = 1;
                func_80039820();
                wp->routine_4++;
                D_800C356C_A[0]++;
            }
            break;
        case 14:
            if (D_800C356C == 0)
            {
                pl->pos_438.x        = -0x4E;
                pl->position.x       = -0x4E;
                pl->pos_438.y        = -1;
                pl->position.y       = -1;
                pl->pos_438.z        = -0x51;
                pl->position.z       = -0x51;
                pl->fixed_428.x      = 0xFFB20000;
                pl->position_fixed.x = 0xFFB20000;
                pl->fixed_428.y      = 0xFFFF0000;
                pl->position_fixed.y = 0xFFFF0000;
                pl->fixed_428.z      = 0xFFAF0000;
                pl->position_fixed.z = 0xFFAF0000;
                pl->value_442        = 0x800;
                pl->rotation.y       = 0x800;
                pl->value_448        = 0x30;
                Player_work.flags_0 |= 2;
                Scene_obj_ent_open(&D_80123EFC[0]);
                wp->child_24->position.x         = 0x6F;
                wp->child_24->position.y         = -1;
                wp->child_24->position.z         = -0x65;
                wp->child_24->position_fixed.v.x = 0x6F0000;
                wp->child_24->position_fixed.v.y = 0xFFFF0000;
                wp->child_24->position_fixed.v.z = 0xFF9B0000;
                wp->child_24->rotation.y         = 0;
                wp->child_24->u_E.b.byte_E       = 0;
                wp->child_24->u_C.b.byte_D       = 1;
                wp->child_24->value_44.half[0]   = 0;
                Scene_obj_ent_open(&D_80123EFC[4]);
                Scene_obj_ent_open(&D_80123EFC[5]);
                Scene_obj_ent_open(&D_80123EFC[3]);
                wp->child_24->variant_3 = wp->child_30->variant_3 = 1;
                wp->child_30->position.x += 0xA;
                wp->child_30->position.z = -0x13D;
                wp->child_24->routine_0 = wp->child_30->routine_0 = 0;
                wp->child_24->u_C.b.byte_C                        = 0x46;
                wp->child_30->u_C.b.byte_C                        = 0x47;
                wp->child_28->rotation.y                          = 0;
                wp->child_28->value_44.half[0]                    = 0;
                wp->child_2C->rotation.y                          = 0;
                wp->child_2C->value_44.half[0]                    = 0;
                wp->child_30->rotation.y                          = 0x800;
                wp->child_30->value_44.half[0]                    = 0;
                Fade_start(1);
                wp->routine_4++;
            }
            break;
        case 15:
            if (D_80098A72 == 0)
            {
                Sce_flag_on(0x2C);
                func_80042314(&Player_work);
                func_80031824(wp->child_34);
                func_80031824(wp->child_38);
                func_80031824(wp->child_30);
                Scene_obj_ent_open(&D_80123F4C[0]);
                Scene_obj_ent_open(&D_80123F4C[1]);
                Sce_flag_off(0x7E0);
                func_8001D974();
                wp->flags_0 = 0;
            }
            break;
        case 16:
            Player_work.flags_0 |= 2;
            func_8003697C();
            D_800A395C = 1;
            func_80039820();
            wp->child_24->position.x         = 0x6F;
            wp->child_24->position.y         = -1;
            wp->child_24->position.z         = -0x65;
            wp->child_24->position_fixed.v.x = 0x6F0000;
            wp->child_24->position_fixed.v.y = 0xFFFF0000;
            wp->child_24->position_fixed.v.z = 0xFF9B0000;
            wp->child_24->rotation.y         = 0;
            wp->child_24->u_E.b.byte_E       = 0;
            wp->child_24->u_C.b.byte_D       = 1;
            wp->child_24->value_44.half[0]   = 0;
            wp->child_24->variant_3 = wp->child_30->variant_3 = 1;
            wp->child_30->position.x += 0xA;
            wp->child_30->position.z = -0x13D;
            func_80031824(wp->child_28);
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            Scene_obj_ent_open(&D_80123F4C[0]);
            Scene_obj_ent_open(&D_80123F4C[1]);
            wp->child_24->routine_0 = wp->child_30->routine_0 = 0;
            wp->child_24->u_C.b.byte_C                        = 0x46;
            wp->child_30->u_C.b.byte_C                        = 0x47;
            wp->child_30->rotation.y                          = 0x800;
            wp->child_30->value_44.half[0]                    = 0;
            Sce_flag_on(0x2C);
            func_80042314(&Player_work);
            func_80031824(wp->child_28);
            func_80031824(wp->child_2C);
            func_80031824(wp->child_30);
            Sce_flag_off(0x7E0);
            func_8001D974();
            wp->flags_0 = 0;
            break;
    }
}
