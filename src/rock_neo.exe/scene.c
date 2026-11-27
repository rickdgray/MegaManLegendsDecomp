#include "common.h"
#include "cd.h"
#include "code_8001786C.h"
#include "code_80037FB4.h"
#include "code_8003A3B4.h"
#include "code_8003AC24.h"
#include "code_8006430C.h"
#include "fastmem.h"
#include "game.h"
#include "pad.h"
#include "player.h"
#include "scene.h"
#include "scratch.h"
#include "sound.h"
#include "system.h"
#include "code_80027678.h"
#include "code_80048620.h"
#include "debug.h"

// Small uninitialized statics (.sbss 0x80098198-0x800981A0).
static uint8 D_80098198[8];

// Called only from this file
void func_8001F740(void);
void func_8001F798(sint32 n);

void Sound_fade_start(sint32 fade)
{
    if (Sound_fade_flags == 0)
    {
        Sound_fade_flags = fade;
    }
}

sint32 func_8001D878(void)
{
    return Cd_stat & 0x20;
}

// No parameter list: func_8001F3C8 and code_800133D8's func_80013420 pass an argument it ignores.
void Sce_read_sync()
{
    while (Cd_read_sync2())
    {
        Thread_wait(1);
    }
}

// Clears the scene flags (new game: then sets the starting ones), or loads them from the save image.
void Sce_flag_init(sint32 load)
{
    sint32 i;
    uint32 *p;

    if (load == 0)
    {
        p = (uint32 *)Sce_flag;
        for (i = 0; i < 0x40; i++)
        {
            *p++ = 0;
        }
        func_80067E18();
        func_80067E4C();
    }
    else
    {
        Mem_copy32(Save_image.sce_flag, Sce_flag, 8);
    }
}

void func_8001D928(sint32 keep)
{
    sint32 i;
    sint32 *p;

    if (keep == 0)
    {
        p = D_800BE438;
        for (i = 0; i < 16; i++)
        {
            *p++ = 0;
        }
    }
    *(uint32 *)&Scene_work.unk00 = 0;
    D_800989F8                   = 0;
    D_800989FC                   = 0;
    D_80098A00                   = 0;
}

void func_8001D974(void)
{
    Game_work.unk053++;
}

// Per frame: the stage's function while no scene runs, else the scene's routine; a scene that
// has just ended is marked as seen (scene flag 0x380 + id_01).
void Sce_update(void)
{
    SCENE_WORK *sw;

    sw = &Scene_work;
    if (sw->unk00 == 0)
    {
        if (D_800C356C == 0)
        {
            D_80088FA8[Game_work.stage_no]();
        }
    }
    if (sw->unk00 != 0)
    {
        if (sw->id_01 != 0xFF)
        {
            Scene_func_tbl[sw->id_01](sw);
        }
        if (sw->unk00 == 0)
        {
            Sce_flag_on(sw->id_01 + 0x380);
        }
    }
}

sint32 Sce_flag_test(sint32 flag)
{
    sint32 bit;
    uint32 idx;
    sint32 mask;
    uint8 unused[8]; // never used; the target has its 8-byte frame

    bit  = flag & 7;
    idx  = (uint32)flag >> 3;
    mask = 0x80;
    return (Sce_flag[idx] & (mask >> bit)) != 0;
}

void Sce_flag_on(sint32 flag)
{
    uint8 *p;
    sint32 i;
    sint32 mask;

    p = Sce_flag;
    p += (uint32)flag >> 3;
    mask = 0x80;
    mask >>= flag & 7;
    *p |= mask;
    // 0x500-0x51F: buster parts; the part's id joins the first empty entry of the list
    if (flag >= 0x500 && flag < 0x520)
    {
        for (i = 0; i < 32; i++)
        {
            if (Player_work[0].rb_parts_sort_data[i] == 0)
            {
                Player_work[0].rb_parts_sort_data[i] = flag - 0x4FF;
                break;
            }
        }
    }
    if (Player_work[0].unk16C != 0 && flag >= 0x53A && flag < 0x53D)
    {
        Player_work[0].unk16C = Sce_flag_test(0x53A) + Sce_flag_test(0x53B) + Sce_flag_test(0x53C);
    }
    if (flag >= 0x500 && flag < 0x580)
    {
        if (flag >= 0x500 && flag < 0x520)
        {
            Sce_flag_on(flag + 0x80);
        }
        else if (flag >= PL_KEY_ITEM_00 && flag < PL_KEY_ITEM_00 + 0x20)
        {
            if (flag == 0x528)
            {
                Sce_flag_on(0x582);
                Sce_flag_on(0x583);
                Sce_flag_on(0x584);
                Sce_flag_on(0x585);
                Sce_flag_on(0x586);
                Sce_flag_on(0x587);
                Sce_flag_on(0x5C1);
                Sce_flag_on(0x5C2);
            }
            if (flag == 0x53A)
            {
                Sce_flag_off(0x5BA);
                Sce_flag_on(0x5BB);
            }
            if (flag == 0x53B)
            {
                Sce_flag_off(0x5BB);
                Sce_flag_on(0x5BC);
            }
            if (flag == 0x53C)
            {
                Sce_flag_off(0x5BC);
            }
            return;
        }
        else if (flag >= 0x540 && flag < 0x544)
        {
            Sce_flag_on(flag + 0x80);
        }
        else if (flag >= 0x544 && flag < 0x558)
        {
            return;
        }
        else if (flag >= 0x558 && flag < 0x580)
        {
            Sce_flag_on(flag + 0x80);
        }
    }
    if (flag == 0x2A)
    {
        Sce_flag_on(0x580);
        Sce_flag_on(0x581);
        Sce_flag_on(0x5C3);
    }
    if (flag == 0x51)
    {
        Sce_flag_on(0x5BA);
        Sce_flag_on(0x588);
        Sce_flag_on(0x589);
    }
}

void Sce_flag_off(sint32 flag)
{
    uint8 *p;
    sint32 mask;
    sint32 bit;
    sint32 i;

    p = Sce_flag;
    p += (uint32)flag >> 3;
    mask = 0x80;
    bit  = flag & 7;
    *p &= ~(mask >> bit);
    if (flag >= 0x500 && flag < 0x520)
    {
        for (i = 0; i < 32; i++)
        {
            if (Player_work[0].rb_parts_sort_data[i] == flag - 0x4FF)
            {
                Player_work[0].rb_parts_sort_data[i] = 0;
                break;
            }
        }
        for (i = 0; i < 3; i++)
        {
            if (Player_work[0].rb_parts_equip_data[i] == flag - 0x4FF)
            {
                Player_work[0].rb_parts_equip_data[i] = 0;
                break;
            }
        }
    }
}

sint16 func_8001DD88(void)
{
    D_80098198[0] = D_80098B60[0];
    D_80098198[1] = D_80098B60[1];
    D_80098B60 += 2;
    return *(sint16 *)D_80098198;
}

sint16 func_8001DDC0(uint8 *p)
{
    D_80098198[0] = p[0];
    D_80098198[1] = p[1];
    return *(sint16 *)D_80098198;
}

void func_8001DDE4(uint8 arg)
{
    SCENE_WORK *sw;
    sint32 i;

    if (Player_work[0].life < 0)
    {
        return;
    }
    sw                               = &Scene_work;
    sw->unk00                        = 1;
    Scene_work.ev_09                 = 0;
    Scene_work.ev_08                 = 0;
    Scene_work.id_01                 = arg;
    Scene_work.timer_10              = 0;
    Scene_work.field_0C              = 0;
    Scene_work.timer_1C              = 0;
    Scene_work.timer_18              = 0;
    Scene_work.timer_14              = 0;
    *(uint32 *)&Scene_work.routine_4 = 0;
    Scene_work.time_0B               = 0;
    Scene_work.step_0A               = 0;
    Scene_work.ev_ptr_A4             = NULL;
    for (i = 15; i >= 0; i--)
    {
        sw->obj_24[i] = NULL;
    }
}

sint32 func_8001DE84(void)
{
    if (Game_work.unk05A != 0 || Sce_flag_test(Scene_work.id_01 + 0x380) != 0)
    {
        if (PAD_ON(Joy1) & PAD_START)
        {
            return 1;
        }
    }
    return 0;
}

void func_8001DEDC(void)
{
}

void func_8001DEE4(void)
{
    sint32 i;

    D_800988E8 = 0;
    for (i = 0; i < 32; i++)
    {
        D_800ACD40[i] = 0;
    }
}

void Scene_obj_list_open(SCENE_OBJ_LIST *list)
{
    sint16 i;
    uint32 index;

    for (i = 0; i < list->count; i++)
    {
        index = list->ents[i].index_00;
        Scene_obj_ent_open(&list->ents[i]);
        D_800ACD40[index] = Scene_work.obj_24[index];
        D_800ACD40[index]->flags &= ~0x20;
        D_800988E8 |= 0x80000000 >> index;
    }
}

void obj_list_ent_open(SCENE_OBJ_LIST *list, sint32 n)
{
    uint32 index;

    index = list->ents[n].index_00;
    Scene_obj_ent_open(&list->ents[n]);
    D_800ACD40[index] = Scene_work.obj_24[index];
    D_800988E8 |= 0x80000000 >> index;
}

void func_8001E068(void)
{
    MODEL_WORK *obj;
    WORK_3C0 *wp;
    WORK_5A4 *mp;
    SHL_WORK *sp;
    WORK_50 *ep;
    sint32 pool;
    sint32 i;

    i = 0;
    while (D_800988E8 != 0)
    {
        if (D_800988E8 & (0x80000000U >> i))
        {
            obj  = D_800ACD40[i];
            pool = func_8002FE74(obj->work_id);
            switch (pool)
            {
                case 0x40:
                    mp            = (WORK_5A4 *)obj;
                    mp->routine_0 = 2;
                    Work_5A4_tbl[mp->id][mp->handler](mp);
                    break;
                case 0x20:
                    wp = (WORK_3C0 *)obj;
                    if (wp->id != 0x10)
                    {
                        wp->routine_0 = 2;
                        Work_3C0_tbl[wp->id][wp->handler](wp);
                    }
                    else
                    {
                        func_80031824(wp);
                    }
                    break;
                case 0x60:
                    sp            = (SHL_WORK *)obj;
                    sp->routine_0 = 2;
                    Shl_work_tbl[sp->id](sp);
                    break;
                case 0xE0:
                    ep            = (WORK_50 *)obj;
                    ep->routine_0 = 2;
                    Work_50_tbl[ep->id](ep);
                    break;
            }
            D_800988E8 &= ~(0x80000000U >> i);
        }
        i++;
    }
}

void func_8001E20C(sint8 index)
{
    MODEL_WORK *obj;
    WORK_3C0 *wp;
    WORK_5A4 *mp;
    SHL_WORK *sp;
    WORK_50 *ep;
    sint32 pool;

    if (D_800988E8 & (0x80000000U >> index))
    {
        obj  = D_800ACD40[index];
        pool = func_8002FE74(obj->work_id);
        switch (pool)
        {
            case 0x40:
                mp            = (WORK_5A4 *)obj;
                mp->routine_0 = 2;
                Work_5A4_tbl[mp->id][mp->handler](mp);
                break;
            case 0x20:
                wp = (WORK_3C0 *)obj;
                if (wp->id != 0x10)
                {
                    wp->routine_0 = 2;
                    Work_3C0_tbl[wp->id][wp->handler](wp);
                }
                else
                {
                    func_80031824(wp);
                }
                break;
            case 0x60:
                sp            = (SHL_WORK *)obj;
                sp->routine_0 = 2;
                Shl_work_tbl[sp->id](sp);
                break;
            case 0xE0:
                ep            = (WORK_50 *)obj;
                ep->routine_0 = 2;
                Work_50_tbl[ep->id](ep);
                break;
        }
        D_800988E8 &= ~(0x80000000U >> index);
    }
}

void func_8001E390(sint32 flag)
{
    uint32 i;

    for (i = 0x2E0; i < 0x2EC; i++)
    {
        if (flag == i)
        {
            Sce_flag_on(i);
        }
        else
        {
            Sce_flag_off(i);
        }
    }
}

void func_8001E3F0(sint16 n)
{
    Game_work.unk060 += D_800891B4[n];
    if (Game_work.unk060 < 0)
    {
        Game_work.unk060 = 0;
    }
    else if (Game_work.unk060 >= 0x100)
    {
        Game_work.unk060 = 0xFF;
    }
    func_800179FC();
}

void func_8001E460(sint32 n, sint32 on, sint32 on2)
{
    if (on != 0)
    {
        Sce_flag_on(n + 0x7E0);
        if (on2 != 0)
        {
            Sce_flag_on(n + 0x7C0);
            return;
        }
    }
    else
    {
        Sce_flag_off(n + 0x7E0);
    }
    Sce_flag_off(n + 0x7C0);
}

// The flags cursor is a local copy: walking the parameter itself swaps its register with i.
void func_8001E4C4(uint8 *ids, uint8 *flags)
{
    sint32 i;
    uint8 *flag;

    flag = flags;
    for (i = 0; i < 8 && *ids != 0; i++, flag++, ids++)
    {
        if (*flag != 0xFF)
        {
            func_8001E460(*ids, *flag & 1, (*flag >> 1) & 1);
        }
    }
}

void func_8001E550(void)
{
    SCENE_CAM_WORK *cp;
    MODEL_WORK *obj;
    VECTOR pos;
    VECTOR tgt;

    cp = &Sce_camera_work;
    if (cp->follow_03 == 0)
    {
        pos.vx = (cp->pos_10.vx + cp->ofs_A0.vx) >> 16;
        pos.vy = (cp->pos_10.vy + cp->ofs_A0.vy) >> 16;
        pos.vz = (cp->pos_10.vz + cp->ofs_A0.vz) >> 16;
    }
    else
    {
        obj           = Scene_work.obj_24[cp->obj_09];
        cp->pos_10.vx = obj->pos_l.vx + cp->ofs_B0.vx;
        cp->pos_10.vy = obj->pos_l.vy + cp->ofs_B0.vy;
        cp->pos_10.vz = obj->pos_l.vz + cp->ofs_B0.vz;
        pos.vx        = cp->pos_10.vx >> 16;
        pos.vy        = cp->pos_10.vy >> 16;
        pos.vz        = cp->pos_10.vz >> 16;
    }
    if (cp->mode_08 == 0)
    {
        func_80038324(&pos, cp->ang_40.vz >> 16, cp->ang_40.vx >> 16, cp->ang_40.vy >> 16);
    }
    else
    {
        tgt.vx = (cp->tgt_70.vx + cp->ofs_A0.vx) >> 16;
        tgt.vy = (cp->tgt_70.vy + cp->ofs_A0.vy) >> 16;
        tgt.vz = (cp->tgt_70.vz + cp->ofs_A0.vz) >> 16;
        func_800384A4(&pos, &tgt);
    }
}

void func_8001E6C0(sint32 x, sint32 y, sint32 z)
{
    Sce_camera_work.ofs_A0.vx = x << 16;
    D_800A395C                = 3; // after the first store: first, its li comes before x's sll
    Sce_camera_work.ofs_A0.vy = y << 16;
    Sce_camera_work.ofs_A0.vz = z << 16;
    Sce_camera_work.vel_20.vx = Sce_camera_work.vel_20.vy = Sce_camera_work.vel_20.vz = 0;
    Sce_camera_work.angvel_50.vx = Sce_camera_work.angvel_50.vy = Sce_camera_work.angvel_50.vz = 0;
    Sce_camera_work.tgtvel_80.vx = Sce_camera_work.tgtvel_80.vy = Sce_camera_work.tgtvel_80.vz = 0;
    Sce_camera_work.mode_08                                                                    = 0;
    Sce_camera_work.pos_10.vx                                                                  = D_800A39A0.vx << 16;
    Sce_camera_work.pos_10.vy                                                                  = D_800A39A0.vy << 16;
    Sce_camera_work.pos_10.vz                                                                  = D_800A39A0.vz << 16;
    Sce_camera_work.ang_40.vx                                                                  = (D_800A3968 & 0xFFF) << 16;
    Sce_camera_work.ang_40.vy                                                                  = (D_800A396C & 0xFFF) << 16;
    Sce_camera_work.ang_40.vz                                                                  = (D_800A3964 & 0xFFF) << 16;
    func_800398E0(0);
}

void cam_pos_set(sint32 x, sint32 y, sint32 z)
{
    Sce_camera_work.pos_10.vx = x << 16;
    Sce_camera_work.pos_10.vy = y << 16;
    Sce_camera_work.pos_10.vz = z << 16;
}

void cam_ang_set(sint32 x, sint32 y, sint32 z)
{
    Sce_camera_work.ang_40.vx = x << 16;
    Sce_camera_work.ang_40.vy = y << 16;
    Sce_camera_work.ang_40.vz = z << 16;
}

sint32 Angle_xz(sint16 x0, sint16 z0, sint16 x1, sint16 z1)
{
    sint32 dx;
    sint32 dz;
    sint32 quad;

    dx   = x1 - x0;
    dz   = (z1 - z0) << 12;
    quad = 0;
    if (dx < 0)
    {
        dx   = -dx;
        quad = 2;
    }
    if (dz < 0)
    {
        dz = -dz;
        quad += 1;
    }
    if (dx == 0)
    {
        return (1 - quad) << 11;
    }
    if (quad == 0 || quad == 3)
    {
        return Angle_xz_quad_tbl[quad] - catan(dz / dx);
    }
    return catan(dz / dx) + Angle_xz_quad_tbl[quad];
}

// The 0xE0 object shares the table store with the others, and an unknown pool jumps to the common
// return: one assignment and one return of obj.
void *scene_obj_open(sint32 index, sint32 id, sint32 pool, SVECTOR *pos)
{
    void *obj;
    MODEL_WORK *mp;
    WORK_50 *ep;

    obj = NULL;
    switch (pool)
    {
        case 0x20:
            mp = (MODEL_WORK *)func_80031418();
            break;
        case 0x40:
            mp = (MODEL_WORK *)func_80031498();
            break;
        case 0xE0:
            ep = func_80031734();
            if (ep != NULL)
            {
                ep->be_flag = MOVE;
                ep->id      = id;
                ep->flags |= 0x20;
                *(uint32 *)&ep->efc.model.pos.vx = *(uint32 *)&pos->vx;
                obj                              = ep;
                *(uint32 *)&ep->efc.model.pos.vz = *(uint32 *)&pos->vz;
                goto set;
            }
            goto end;
        case 0x60:
            mp = (MODEL_WORK *)Open_SHL_WORK();
            break;
        default:
            goto end;
    }
    if (mp != NULL)
    {
        mp->be_flag = MOVE;
        mp->id      = id;
        mp->flags |= 0x20;
        *(uint32 *)&mp->pos.vx = *(uint32 *)&pos->vx;
        mp->pos.vz             = pos->vz;
        mp->ang.vx             = 0;
        mp->ang.vz             = 0;
        mp->ang.vy             = pos->pad;
        mp->pos_l.vx           = pos->vx << 16;
        mp->pos_l.vy           = pos->vy << 16;
        obj                    = mp;
        mp->pos_l.vz           = pos->vz << 16;
    set:
        Scene_work.obj_24[index] = obj;
    }
end:
    return obj;
}

void *Scene_obj_ent_open(SCENE_OBJ_ENT *ent)
{
    MODEL_WORK *mp;

    mp = scene_obj_open(ent->index_00, ent->id_01, ent->kind_03, &ent->pos_0C);
    if (mp == NULL)
    {
        return NULL;
    }
    switch (ent->kind_03)
    {
        case 0x40:
        case 0x20:
        case 0x60:
        case 0xE0:
            mp->type    = ent->type_04;
            mp->flag_4  = ent->flag_02;
            mp->field_C = ent->field_08;
            break;
    }
    return mp;
}

// Opens the entry's object without taking over its Scene_work.obj_24 slot (the slot keeps its old
// object), and clears the object's flag bit 5.
MODEL_WORK *func_8001EB98(SCENE_OBJ_ENT *ent)
{
    void *saved;
    MODEL_WORK *obj;

    saved = Scene_work.obj_24[ent->index_00];
    obj   = Scene_obj_ent_open(ent);
    obj->flags &= ~0x20;
    Scene_work.obj_24[ent->index_00] = saved;
    return obj;
}

void Sce_camera_update(void)
{
    SCENE_CAM_WORK *cp;
    SCENE_WORK *sw;
    uint32 cmd;
    sint32 done;

    sw = &Scene_work;
    cp = &Sce_camera_work;
    if (*Sce_camera_work.arg_C0 != -1)
    {
        done = 0;
        do
        {
            cmd = cp->arg_C0[0];
            switch (cmd >> 24)
            {
                case 0: // wait until frame (low 24 bits) of the scene
                    if (sw->timer_14 < (cp->arg_C0[0] & 0xFFFFFF))
                    {
                        done = 1;
                        break;
                    }
                    cp->arg_C0++;
                    break;
                case 1: // wait until ev_08 and its frame timer_18
                    if (sw->ev_08 == (cmd & 0xFF0000) >> 16)
                    {
                        if (sw->timer_18 == (cmd & 0xFFFF))
                        {
                            cp->arg_C0++;
                        }
                        else
                        {
                            done = 1;
                        }
                    }
                    else
                    {
                        done = 1;
                    }
                    break;
                case 2: // wait until ev_09 and its frame timer_1C
                    if (sw->ev_09 == (cmd & 0xFF0000) >> 16)
                    {
                        if (sw->timer_1C == (cmd & 0xFFFF))
                        {
                            cp->arg_C0++;
                        }
                        else
                        {
                            done = 1;
                        }
                    }
                    else
                    {
                        done = 1;
                    }
                    break;
                case 3:
                    cp->mode_08 = 0;
                    cp->arg_C0++;
                    break;
                case 4:
                    cp->mode_08 = 1;
                    cp->arg_C0++;
                    break;
                case 5:
                    cp->follow_03 = 0;
                    cp->arg_C0++;
                    break;
                case 6:
                    cp->follow_03 = 1;
                    cp->arg_C0++;
                    break;
                case 0x10:
                    cp->follow_03 = 0;
                    cp->pos_10.vx = cp->arg_C0[1];
                    cp->pos_10.vy = cp->arg_C0[2];
                    cp->pos_10.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x11:
                    cp->ang_40.vx = cp->arg_C0[1];
                    cp->ang_40.vy = cp->arg_C0[2];
                    cp->ang_40.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x12:
                    cp->vel_20.vx = cp->arg_C0[1];
                    cp->vel_20.vy = cp->arg_C0[2];
                    cp->vel_20.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x13:
                    cp->angvel_50.vx = cp->arg_C0[1];
                    cp->angvel_50.vy = cp->arg_C0[2];
                    cp->angvel_50.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x14:
                    cp->follow_03 = 1;
                    cp->obj_09    = (cp->arg_C0[0] & 0xFF0000) >> 16;
                    cp->ofs_B0.vx = cp->arg_C0[1];
                    cp->ofs_B0.vy = cp->arg_C0[2];
                    cp->ofs_B0.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x15:
                    cp->tgt_70.vx = cp->arg_C0[1];
                    cp->tgt_70.vy = cp->arg_C0[2];
                    cp->tgt_70.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x16:
                    cp->tgtvel_80.vx = cp->arg_C0[1];
                    cp->tgtvel_80.vy = cp->arg_C0[2];
                    cp->tgtvel_80.vz = cp->arg_C0[3];
                    cp->arg_C0 += 4;
                    break;
                case 0x20:
                    func_8003697C();
                    cp->arg_C0++;
                    break;
                case 0x21:
                    func_800369C0();
                    cp->arg_C0++;
                    break;
                case 0x22:
                    func_80036A1C();
                    cp->arg_C0++;
                    break;
                case 0xFF: // end of the script
                    done = 1;
                    break;
            }
        } while (done == 0);
    }
    cp->pos_10.vx += cp->vel_20.vx;
    cp->pos_10.vy += cp->vel_20.vy;
    cp->pos_10.vz += cp->vel_20.vz;
    cp->ang_40.vx += cp->angvel_50.vx;
    cp->ang_40.vy += cp->angvel_50.vy;
    cp->ang_40.vz += cp->angvel_50.vz;
    cp->tgt_70.vx += cp->tgtvel_80.vx;
    cp->tgt_70.vy += cp->tgtvel_80.vy;
    cp->tgt_70.vz += cp->tgtvel_80.vz;
}

void Sce_event_update(void)
{
    SCENE_WORK *sw;

    sw = &Scene_work;
    sw->timer_14++;
    sw->timer_18++;
    sw->timer_1C++;
    sw->timer_10++;
    if (sw->ev_ptr_A4->frame_2 != -1 && sw->ev_ptr_A4->frame_2 == sw->timer_10)
    {
        sw->ev_ptr_A4++;
        if (sw->ev_08 != sw->ev_ptr_A4->ev_0)
        {
            sw->timer_18 = 0;
            sw->timer_1C = 0;
        }
        sw->ev_08 = sw->ev_ptr_A4->ev_0;
        if (sw->ev_09 != sw->ev_ptr_A4->ev_1)
        {
            sw->timer_1C = 0;
        }
        sw->ev_09    = sw->ev_ptr_A4->ev_1;
        sw->timer_10 = 0;
    }
}

// Steps the event table to its next entry (Sce_event_update's step, without the frame test).
void Sce_event_next(void)
{
    SCENE_WORK *sw;

    sw = &Scene_work;
    sw->ev_ptr_A4++;
    if (sw->ev_08 != sw->ev_ptr_A4->ev_0)
    {
        sw->timer_18 = 0;
        sw->timer_1C = 0;
    }
    sw->ev_08 = sw->ev_ptr_A4->ev_0;
    if (sw->ev_09 != sw->ev_ptr_A4->ev_1)
    {
        sw->timer_1C = 0;
    }
    sw->ev_09    = sw->ev_ptr_A4->ev_1;
    sw->timer_10 = 0;
}

void Sce_event_timer_clear(void)
{
    Scene_work.timer_10 = 0;
    Scene_work.timer_18 = 0;
    Scene_work.timer_1C = 0;
    Scene_work.ev_08    = 0;
    Scene_work.ev_09    = 0;
}

void Sce_event_set(EVENT_ENT *ev, uint32 *arg1)
{
    Sce_camera_work.arg_C0 = arg1;
    Scene_work.ev_ptr_A4   = ev;
    Scene_work.ev_08       = ev->ev_0;
    Scene_work.ev_09       = ev->ev_1;
}

// Called by r3_sup: sets the stage's reverb; when the stage's file (D_800893BC[stage_no][0])
// changed, clears Stage_idx_tbl and loads it and the area's file; runs D_80089714[stage_no].
sint32 func_8001F23C(void)
{
    GAME_WORK *gw;
    sint32 stage; // the stage, then the loop counter
    sint32 area;
    sint32 file;
    sint32 cur;
    sint32 next;

    gw    = &Game_work;
    stage = Game_work.stage_no;
    area  = Game_work.area_no;
    func_8001F740();
    file = Stage_reverb_tbl[stage]; // the reverb preset, then the stage's file
    Sound_reverb_set(file);
    cur  = Game_work.unk068;
    file = D_800893BC[stage][0];
    if (cur != file)
    {
        Game_work.unk068 = file;
        Mem_clear(Stage_idx_tbl, (uint8 *)&Stage_idx_tbl[IDX_ENT_MAX] - 4);
        Cd_read_comb(file);
        next             = D_800893BC[stage][area + 1];
        Game_work.unk06A = next;
        if (next >= 0)
        {
            Cd_read_comb(next);
        }
        Sce_read_sync(0);
        func_8003A3B4();
        func_8003AD14();
    }
    D_80089714[stage]();
    func_8001D928(Game_work.unk082 & 1);
    (*(uint16 *)&gw->unk062[0])++;
    if ((uint8)gw->stage_no - 5u >= 2 && gw->stage_no != 0xF)
    {
        gw->unk062[3] = 1;
        gw->unk062[2] = 1;
    }
    for (stage = 0; stage < 8; stage++)
    {
        gw->unk174.w[stage] = 0;
    }
    Clut_buf_stp_set();
    return 0;
}

// Called by func_800158F0 and r3_sup: unless D_800C356C is -1, loads the area's file
// (D_800893BC[stage_no][area_no + 1]) when it changed, the player's setting files, and closes the
// objects; then runs D_80089790[stage_no] and resets per-area state.
sint32 func_8001F3C8(void)
{
    GAME_WORK *gw;
    PL_WORK *pw;
    sint32 stage;
    sint32 area;
    sint32 file;

    gw    = &Game_work;
    pw    = &Player_work[0];
    stage = Game_work.stage_no;
    area  = Game_work.area_no;
    func_8001F740();
    if (D_800C356C != -1)
    {
        file = D_800893BC[stage][area + 1];
        if (file >= 0 && Game_work.unk06A != file)
        {
            Cd_read_comb(file);
            Game_work.unk06A = file;
        }
        func_8001F5E4();
        Sce_read_sync(0);
        Obj_work_flag_change(0x3FE, WORK_KILL);
        func_80031AA4();
    }
    D_80089790[stage]();
    if (Scene_work.unk00 == 0)
    {
        Scratch_scale_shift = 0;
        if (D_800C356C != -1)
        {
            *(uint32 *)&pw->routine_0 = 0;
            pw->flags_BD &= ~0x40;
        }
    }
    if (pw->unk44E >= 0)
    {
        if (pw->unk44E != 0)
        {
            if (pw->unk44F != 0)
            {
                pw->weapon_right_no = pw->tbl_sel;
            }
            else
            {
                pw->weapon_right_no = 0;
            }
            pw->unk171 = pw->unk173;
        }
        else
        {
            pw->weapon_right_no = 0;
            pw->unk171          = 0;
        }
    }
    func_8002CFA4();
    func_80051B40();
    func_80033EBC();
    func_800629E0();
    func_800179FC();
    gw->unk07E = 0;
    Sce_flag_off(0x1FF);
    return 0;
}

// Loads file (Cd_read_comb); close first closes the objects of the stage's first EBD file, set
// records it as the area's file (Game_work.unk06A).
void func_8001F580(sint16 file, sint32 close, sint32 set)
{
    if (close != 0)
    {
        func_8002FBF4();
    }
    if (set != 0)
    {
        Game_work.unk06A = file;
    }
    Cd_read_comb(file);
}

void func_8001F5E4(void)
{
    sint32 file;

    file = D_80089200[Player_work[0].unk16A];
    if (Game_work.file_070 != file)
    {
        Game_work.file_070 = file;
        Cd_read_comb(file);
    }
    file = D_80089204[(sint8)Player_work[0].unk16B >> 1];
    if (Game_work.file_072 != file)
    {
        Game_work.file_072 = file;
        Cd_read_comb(file);
    }
    if (Player_work[0].tbl_sel >= 2)
    {
        file = D_80089208[Player_work[0].tbl_sel];
        if (Game_work.file_074 != file)
        {
            Game_work.file_074 = file;
            Cd_read_comb(file);
        }
    }
}

void func_8001F6C4(void)
{
    sint16 *list;
    sint32 n;
    sint32 file;

    list = D_800893BC[D_800C356E];
    file = list[0];
    n    = D_800C356F;
    if (Game_work.unk068 == file)
    {
        file = list[n + 1];
        if (file < 0 || Game_work.unk06A == file)
        {
            return;
        }
    }
    Cd_seek_file(file);
}

void func_8001F740(void)
{
    func_8001F798(Game_work.stage_no);
    D_8008980C[Game_work.stage_no]();
}

void func_8001F798(sint32 n)
{
    sint32 i;

    for (i = 0; i < D_80089248[n].count; i++)
    {
        D_80089248[n].dst[i] = D_80089248[n].src[i];
    }
}

void func_8001F820(void)
{
}

INCLUDE_RODATA("asm/rock_neo.exe/nonmatchings/scene", D_800102B0);

// For the code and data still in assembly: splat's labels inside the statics above (aliases),
// and statics that .data tables or other files point to (made global). Drop each once no
// assembly names it.
__asm__(".text\n"
        ".globl D_80098199\n.set D_80098199, D_80098198+1\n");
