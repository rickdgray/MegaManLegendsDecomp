#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include "psyq/libgte.h"
#include "code_8002E7A8.h"

typedef struct SCENE_WORK SCENE_WORK;

typedef void (*SCENE_EVENT_FUNC)(SCENE_WORK *sw);
typedef void (*STAGE_FUNC)(void); // one per Game_work.stage_no (D_8008980C)

// One 8-byte entry of an event table (D_8009039C).
typedef struct
{
    uint8 ev_0;            // copied to SCENE_WORK.ev_08
    uint8 ev_1;            // copied to SCENE_WORK.ev_09
    sint16 frame_2;        // frame at which Sce_event_update moves to the next entry
    SCENE_EVENT_FUNC func; // step function, called every frame with the scene work (event_step_call)
} EVENT_ENT;

// One entry of D_80089248: a halfword copy job (func_8001F798).
typedef struct
{
    sint32 count;
    uint16 *src;
    uint16 *dst;
} HALF_COPY_ENT;

// One 0x14-byte entry of a scene's object table (D_8008FF88), opened by func_8001EAE8 (partial).
typedef struct
{
    uint8 unk00;
    uint8 unk01;
    uint8 unk02;   // copied to the object's byte 4
    uint8 kind_03; // pool: 0x20 WORK_3C0, 0x40 WORK_5A4, 0x60 SHL_WORK, 0xE0 WORK_50 (func_8001E968)
    uint8 unk04;   // copied to the object's byte 3
    uint8 unk05[3];
    sint32 unk08;    // copied to the object's word 0xC
    sint16 unk0C[4]; // passed by address to func_8001E968
} SCENE_OBJ_ENT;

// Scene work, 0xA8 bytes (partial). Passed to the event-table step functions (D_8009039C).
struct SCENE_WORK
{
    uint8 unk00; // 0x00: set to 1 by func_8001DDE4; bytes 0-3 cleared at once by func_8001D928
    uint8 id_01; // 0x01: the scene's number (func_8001DDE4's argument); scene flag 0x380 + id_01
                 // marks it as seen, so START skips it (func_8001DE84)
    uint8 unk02[2];
    uint8 routine_4; // 0x04: state of the scene's main function (func_80068DAC); bytes 4-7
                     // cleared at once by func_8001DDE4
    uint8 unk05[3];
    uint8 ev_08; // 0x08: byte 0 of the current event-table entry (Sce_event_set, Sce_event_update)
    uint8 ev_09; // 0x09: byte 1 of the current event-table entry
    uint8 unk0A;
    uint8 unk0B;
    sint32 field_0C; // 0x0C: cleared by func_8001DDE4; tested by the event step func_8006849C
    sint32 timer_10; // 0x10: frames since the current event-table step began (Sce_event_update)
    sint32 timer_14; // 0x14: frames since the scene started (Sce_event_update)
    sint32 timer_18; // 0x18: frames since ev_08 last changed (Sce_event_update)
    sint32 timer_1C; // 0x1C: frames since ev_08 or ev_09 last changed (Sce_event_update)
    uint8 unk20[0x24 - 0x20];
    // 0x24: the scene's objects, opened by func_8001E968 from one of four pools chosen by its third
    // argument (kind 0x20: func_80031418, WORK_3C0; 0x40: func_80031498, WORK_5A4; 0x60:
    // Open_SHL_WORK, SHL_WORK; 0xE0: func_80031734, WORK_50), so each entry's type depends on the
    // scene. The users read an entry into a pointer of the type they know: the event steps of
    // code_800680BC have [0] WORK_3C0, [1] and [2] WORK_5A4, [3] WORK_50 (their object table
    // D_8008FF88), and the camera (func_8001E550) only needs the MODEL_WORK layout.
    void *obj_24[16];
    sint32 field_64; // set by the event steps (func_8006854C, func_80068728)
    // 0x68-0x70: three levels that func_8006854C clears, then raises by 9 a frame from timer_10
    // 90 to 120, all set to 0xFF once field_68 reaches it (probably an RGB fade)
    uint32 field_68;
    uint32 field_6C;
    uint32 field_70;
    sint32 field_74; // 0x74: set to 2 by func_8006854C
    uint8 unk78[0xA4 - 0x78];
    EVENT_ENT *ev_ptr_A4; // 0xA4: current entry of the event table (Sce_event_update steps it)
};

// The scene's camera (partial), at 0x800BC730; func_8001EC0C reaches it through one base
// register. All vectors are 16.16 fixed point. func_8001E550 hands it to the camera code each
// frame: position pos_10 (+ ofs_A0) and either the angles ang_40 (func_80038324) or the point
// tgt_70 + ofs_A0 (func_800384A4); func_8001E6C0 resets it from the current camera.
typedef struct
{
    uint8 unk00[3];
    uint8 follow_03; // 0x03: nonzero: pos_10 follows Scene_work.obj_24[obj_09] (+ ofs_B0)
    uint8 unk04[4];
    uint8 mode_08; // 0x08: 0 = aim by angles ang_40, otherwise at the point tgt_70
    uint8 obj_09;  // 0x09: index of the followed object in Scene_work.obj_24
    uint8 unk0A[0x10 - 0x0A];
    VECTOR pos_10; // 0x10: position (cam_pos_set sets it in whole units)
    VECTOR vel_20; // 0x20: added to pos_10 by func_8001EC0C
    uint8 unk30[0x10];
    VECTOR ang_40;    // 0x40: angles (0..0xFFF in the whole part; cam_ang_set)
    VECTOR angvel_50; // 0x50: added to ang_40 by func_8001EC0C
    uint8 unk60[0x10];
    VECTOR tgt_70;    // 0x70: point looked at when mode_08 is set
    VECTOR tgtvel_80; // 0x80: added to tgt_70 by func_8001EC0C
    uint8 unk90[0x10];
    VECTOR ofs_A0;  // 0xA0: offset added to pos_10 and tgt_70 (func_8001E6C0's arguments)
    VECTOR ofs_B0;  // 0xB0: offset from the followed object (follow_03)
    uint32 *arg_C0; // 0xC0: camera command script (top byte of each word is the command), set
                    // with the event table by Sce_event_set; func_8001EC0C steps it
} SCENE_CAM_WORK;

extern SCENE_WORK Scene_work; // 0x800C4C48
extern uint8 Sce_flag[];      // 0x800BE378: scene flag bits, MSB first in each byte (Sce_flag_test)
extern SCENE_CAM_WORK Sce_camera_work;

extern SCENE_OBJ_ENT D_8008FF88[4]; // objects of code_800680BC's scene (event_scene_init)
extern uint32 D_8008FFD8[];         // camera script of code_800680BC's scene
extern EVENT_ENT D_8009039C[];      // event table of code_800680BC's scene

extern uint8 *D_80098B60;    // read pointer, advanced two bytes by func_8001DD88
extern sint32 D_800988E8;    // bitmask of D_800ACD40 slots in use, slot n = 0x80000000 >> n (func_8001DFEC)
extern void *D_800ACD40[32]; // per slot, a copy of Scene_work.obj_24[n] (func_8001DFEC); cleared by func_8001DEE4

extern sint32 D_800BE438[16]; // cleared by func_8001D928(0)
extern sint32 D_800989F8;     // cleared by func_8001D928
extern sint32 D_800989FC;     // cleared by func_8001D928
extern sint32 D_80098A00;     // cleared by func_8001D928

// Per stage (D_800C356E), a list of file indexes: [0] compared with Game_work.unk068, then one per
// D_800C356F at [n + 1] (negative = none) compared with Game_work.unk06A (func_8001F6C4).
extern sint16 *D_800893BC[];

// 12-byte entries {count, src, dst}: func_8001F798(n) copies count halfwords from src to dst.
// Splat splits the first entry's fields into three labels (D_80089248, D_8008924C, D_80089250).
extern HALF_COPY_ENT D_80089248[];

// Files func_8001F5E4 loads for the player's settings (see GAME_WORK.file_070).
extern sint16 D_80089200[];
extern sint16 D_80089204[];
extern sint16 D_80089208[];

// One function per Game_work.stage_no, called by func_8001F740 after func_8001F798(stage_no).
extern STAGE_FUNC D_8008980C[];

sint32 Sce_flag_test(sint32 flag);
void Sce_flag_on(sint32 flag);
void Sce_flag_off(sint32 flag);
void Sound_fade_start(sint32 fade); // starts a sound fade (Sound_fade_flags) unless one is running
sint32 func_8001D878(void);         // Cd_stat & 0x20
void func_8001D974(void);           // Game_work.unk053++
sint32 func_8001DE84(void);         // START pressed in a scene already seen
void func_8001E390(sint32 flag);
void func_8001EC0C(void); // steps the scene camera (Sce_camera_work)
void Sce_event_update(void);
sint32 func_8001E83C(sint16 x, sint16 z, sint16 dx, sint16 dz); // angle to a point
void func_8001E6C0(sint32 x, sint32 y, sint32 z);               // resets the scene camera from the current camera
void *func_8001EAE8(SCENE_OBJ_ENT *ent);                        // opens the object of one table entry

#endif // SCENE_H
