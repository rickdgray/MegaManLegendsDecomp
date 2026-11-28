#include "common.h"
#include "st17.h"

void func_8010C36C(STAGE_OBJ *wp)
{
    STCOM_MATRIX m;
    STCOM_SVECTOR v;
    STAGE_SCENE_WORK *scene;
    STAGE_OBJ *model;
    sint32 i;

    wp->position_prev       = wp->position;
    wp->position_fixed_prev = wp->position_fixed.v;
    wp->rotation_prev       = wp->rotation;
    scene                   = &Scene_work;
    switch (wp->routine_0)
    {
        case 0:
            wp->flags_0 |= 2;
            Model_work_init(wp, NULL);
            wp->scale.words[0]   = 0x02000200;
            wp->scale.words[1]   = 0x200;
            wp->scale.v.pad      = 0x4210;
            wp->value_78         = 0;
            wp->value_44.half[0] = 0;
            wp->value_44.half[1] = 0;
            wp->value_48.half[0] = 0;
            wp->u_C.b.byte_C     = 0;
            wp->u_C.b.byte_D     = 0;
            func_800322A8(wp, 9, 0);
            wp->routine_0++;
            model                       = func_80105A0C(wp, 3, D_80122B08);
            ST17_SCENE_OBJ(scene, 0x1F) = model;
            model->flags_6 |= 0x20;
            break;
        case 1:
            func_80032488(wp);
            break;
        case 3:
            wp->rotation.z = 0x28;
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            wp->routine_0++;
            break;
        case 4:
            if (scene->value_10 & 8)
            {
                wp->rotation.z += 0xA;
            }
            else
            {
                wp->rotation.z -= 0xA;
            }
            if (scene->value_10 == 0x5A)
            {
                wp->value_44.half[0] = -0x14;
                wp->value_44.half[1] = 0x40;
                wp->value_4C.half[1] = 4;
                wp->value_48.half[0] = -0x140;
                wp->value_50         = -4;
                wp->routine_0++;
            }
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            break;
        case 5:
            wp->value_48.half[0] += wp->value_50;
            wp->rotation.z += wp->value_48.half[0] >> 4;
            wp->position.x += wp->value_44.half[0];
            wp->value_44.half[1] += wp->value_4C.half[1];
            wp->position.y += wp->value_44.half[1] >> 4;
            wp->position.z += 0xF;
            wp->position_fixed.v.x = wp->position.x << 16;
            wp->position_fixed.v.y = wp->position.y << 16;
            wp->position_fixed.v.z = wp->position.z << 16;
            func_80032538(wp);
            Model_parts_mtx_set_yxz(wp);
            break;
    }
    for (i = 0; i < 7; i++)
    {
        RotMatrixYXZ(&wp->rotation, &m);
        ApplyMatrixSV(&m, &D_8011BDC8[i], &v);
        D_80122B08[i].x = wp->position.x + v.x;
        D_80122B08[i].y = wp->position.y + v.y;
        D_80122B08[i].z = wp->position.z + v.z;
    }
}
