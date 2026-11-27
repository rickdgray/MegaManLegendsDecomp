#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include "psyq/libgte.h"
#include "code_8002E7A8.h"

// Scene flags (Sce_flag_test), Capcom's names (disc/tcrf.txt).
#define PL_KEY_ITEM_00 0x520 // PL_KEY_ITEM_00 + n: key item n's flag (the sub screen's item menu tests it)
#define PL_KEY_ITEM_04 0x524 // set: the sub screen's item menu can refill life (func_8005F3D0)
#define PL_KEY_ITEM_06 0x526 // set: three buster parts slots instead of two (sub_scrn.c)

typedef struct SCENE_WORK SCENE_WORK;

typedef void (*SCENE_EVENT_FUNC)(SCENE_WORK *sw);
typedef void (*SCENE_FUNC)(SCENE_WORK *sw); // one per scene (Scene_work.id_01; Scene_func_tbl)
typedef void (*STAGE_FUNC)(void);           // one per Game_work.stage_no (D_8008980C)

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

// One 0x14-byte entry of a scene's object table (D_8008FF88), opened by Scene_obj_ent_open (partial).
typedef struct
{
    uint8 index_00; // the object's index in Scene_work.obj_24
    uint8 id_01;    // the object's id
    uint8 flag_02;  // copied to the object's flag_4
    uint8 kind_03;  // pool: 0x20 WORK_3C0, 0x40 WORK_5A4, 0x60 SHL_WORK, 0xE0 WORK_50 (scene_obj_open)
    uint8 type_04;  // copied to the object's type
    uint8 unk05[3];
    uint32 field_08; // copied to the object's field_C
    SVECTOR pos_0C;  // position, pad the Y angle (scene_obj_open)
} SCENE_OBJ_ENT;

// A counted list of object table entries, opened together by Scene_obj_list_open (stage overlays' data).
typedef struct
{
    uint32 count;
    SCENE_OBJ_ENT *ents;
} SCENE_OBJ_LIST;

// Scene work, 0xA8 bytes (partial). Passed to the event-table step functions (D_8009039C).
struct SCENE_WORK
{
    uint8 unk00; // 0x00: set to 1 by func_8001DDE4; bytes 0-3 cleared at once by func_8001D928
    uint8 id_01; // 0x01: the scene's number (func_8001DDE4's argument); scene flag 0x380 + id_01
                 // marks it as seen, so START skips it (func_8001DE84)
    uint8 unk02[2];
    uint8 routine_4; // 0x04: state of the scene's main function (func_80068DAC); bytes 4-7
                     // cleared at once by func_8001DDE4
    uint8 routine_5; // 0x05: state within routine_4's step (func_80048620, func_80048704)
    uint8 unk06[2];
    uint8 ev_08;     // 0x08: byte 0 of the current event-table entry (Sce_event_set, Sce_event_update)
    uint8 ev_09;     // 0x09: byte 1 of the current event-table entry
    uint8 step_0A;   // 0x0A: state of func_80048A9C
    uint8 time_0B;   // 0x0B: frame count func_80048A9C waits for (timer_10), per stage (D_8008AA04)
    sint32 field_0C; // 0x0C: cleared by func_8001DDE4; tested by the event step func_8006849C
    sint32 timer_10; // 0x10: frames since the current event-table step began (Sce_event_update)
    sint32 timer_14; // 0x14: frames since the scene started (Sce_event_update)
    sint32 timer_18; // 0x18: frames since ev_08 last changed (Sce_event_update)
    sint32 timer_1C; // 0x1C: frames since ev_08 or ev_09 last changed (Sce_event_update)
    uint8 unk20[0x24 - 0x20];
    // 0x24: the scene's objects, opened by scene_obj_open from one of four pools chosen by its third
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

// The scene's camera (partial), at 0x800BC730; Sce_camera_update reaches it through one base
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
    VECTOR vel_20; // 0x20: added to pos_10 by Sce_camera_update
    uint8 unk30[0x10];
    VECTOR ang_40;    // 0x40: angles (0..0xFFF in the whole part; cam_ang_set)
    VECTOR angvel_50; // 0x50: added to ang_40 by Sce_camera_update
    uint8 unk60[0x10];
    VECTOR tgt_70;    // 0x70: point looked at when mode_08 is set
    VECTOR tgtvel_80; // 0x80: added to tgt_70 by Sce_camera_update
    uint8 unk90[0x10];
    VECTOR ofs_A0;  // 0xA0: offset added to pos_10 and tgt_70 (func_8001E6C0's arguments)
    VECTOR ofs_B0;  // 0xB0: offset from the followed object (follow_03)
    uint32 *arg_C0; // 0xC0: camera command script (top byte of each word is the command), set
                    // with the event table by Sce_event_set; Sce_camera_update steps it
} SCENE_CAM_WORK;

extern SCENE_WORK Scene_work; // 0x800C4C48
extern uint8 Sce_flag[];      // 0x800BE378: scene flag bits, MSB first in each byte (Sce_flag_test)
extern SCENE_CAM_WORK Sce_camera_work;

extern SCENE_OBJ_ENT D_8008FF88[4]; // objects of code_800680BC's scene (event_scene_init)
extern uint32 D_8008FFD8[];         // camera script of code_800680BC's scene
extern EVENT_ENT D_8009039C[];      // event table of code_800680BC's scene

extern uint8 *D_80098B60;          // read pointer, advanced two bytes by func_8001DD88
extern sint32 D_800988E8;          // bitmask of D_800ACD40 slots in use, slot n = 0x80000000 >> n (Scene_obj_list_open)
extern MODEL_WORK *D_800ACD40[32]; // per slot, a copy of Scene_work.obj_24[n] (Scene_obj_list_open); cleared by func_8001DEE4

extern sint32 D_800BE438[16]; // cleared by func_8001D928(0)
extern sint32 D_800989F8;     // cleared by func_8001D928
extern sint32 D_800989FC;     // cleared by func_8001D928
extern sint32 D_80098A00;     // cleared by func_8001D928

// Per stage (D_800C356E), a list of file indexes: [0] compared with Game_work.unk068, then one per
// D_800C356F at [n + 1] (negative = none) compared with Game_work.unk06A (func_8001F6C4).
extern sint16 *D_800893BC[];

// One reverb preset (Sound_reverb_set) per Game_work.stage_no (func_8001F23C), 32 entries.
extern uint16 Stage_reverb_tbl[32];

// One function per Game_work.stage_no (stage overlay code), called by func_8001F23C after the
// stage's files are loaded.
extern STAGE_FUNC D_80089714[31];

// 12-byte entries {count, src, dst}: func_8001F798(n) copies count halfwords from src to dst.
// Splat splits the first entry's fields into three labels (D_80089248, D_8008924C, D_80089250).
extern HALF_COPY_ENT D_80089248[];

// Files func_8001F5E4 loads for the player's settings (see GAME_WORK.file_070).
extern sint16 D_80089200[];
extern sint16 D_80089204[];
extern sint16 D_80089208[];

// Per quadrant (bit 1: dx < 0, bit 0: dz < 0), the angle Angle_xz adds catan's result to (or
// subtracts it from, in quadrants 0 and 3): 0xC00, 0xC00, 0x400, 0x400.
extern sint32 Angle_xz_quad_tbl[4];

// Steps func_8001E3F0(n) adds to Game_work.unk060 (clamped to 0..0xFF), 30 entries.
extern sint16 D_800891B4[30];

// One function per Game_work.stage_no, called by func_8001F740 after func_8001F798(stage_no).
extern STAGE_FUNC D_8008980C[];

// One function per Game_work.stage_no (stage overlay code), called by func_8001F3C8.
extern STAGE_FUNC D_80089790[31];

// One function per Game_work.stage_no (stage overlay code), called by Sce_update each frame
// while no scene runs and D_800C356C is 0.
extern STAGE_FUNC D_80088FA8[];

// One routine per scene (Scene_work.id_01), called by Sce_update each frame while
// Scene_work.unk00 is set (func_80068DAC is one).
extern SCENE_FUNC Scene_func_tbl[];

sint32 Sce_flag_test(sint32 flag);
void Sce_flag_on(sint32 flag);
void Sce_flag_off(sint32 flag);
void Sound_fade_start(sint32 fade); // starts a sound fade (Sound_fade_flags) unless one is running
sint32 func_8001D878(void);         // Cd_stat & 0x20
// Takes no argument, but code_800133D8's func_80013420 calls it with 1 and func_8001F3C8 with 0,
// so the declaration (and the definition) leave the parameter list unspecified.
void Sce_read_sync();                                // waits, a frame at a time, until the CD reads are done
void func_8001D974(void);                            // Game_work.unk053++
void func_8001DDE4(uint8 arg);                       // starts scene arg (Scene_work.id_01) unless the player is dead
sint32 func_8001DE84(void);                          // START pressed in a scene already seen
void Sce_flag_init(sint32 load);                     // clears the scene flags (new game) or loads them from the save image
void Sce_update(void);                               // per frame: the stage's function, or the running scene's routine
void func_8001E390(sint32 flag);                     // sets scene flag flag among 0x2E0-0x2EB, clears the others
void func_8001E3F0(sint16 n);                        // steps Game_work.unk060 by D_800891B4[n], then func_800179FC
void func_8001E460(sint32 n, sint32 on, sint32 on2); // sets or clears scene flags 0x7E0 + n and 0x7C0 + n
void Sce_camera_update(void);                        // steps the scene camera (Sce_camera_work)
void Sce_event_update(void);
sint32 Angle_xz(sint16 x0, sint16 z0, sint16 x1, sint16 z1); // angle from (x0, z0) to (x1, z1)
void func_8001E6C0(sint32 x, sint32 y, sint32 z);            // resets the scene camera from the current camera
void *Scene_obj_ent_open(SCENE_OBJ_ENT *ent);                // opens the object of one table entry
void Scene_obj_list_open(SCENE_OBJ_LIST *list);              // opens every entry, registered in D_800ACD40 for func_8001E068
void func_8001E4C4(uint8 *ids, uint8 *flags);
void func_8001E550(void); // the scene's camera, while the camera block's routine_0 is not 1 (Camera_update)
MODEL_WORK *func_8001EB98(SCENE_OBJ_ENT *ent);
sint32 func_8001F23C(void); // loads the stage's file when it changed, runs the stage's function
sint32 func_8001F3C8(void); // loads the area's and the player's files, runs the stage's function
void func_8001F5E4(void);   // reloads the files of the player's settings (GAME_WORK.file_070) that changed
void func_8001F6C4(void);   // seeks the CD to the next area's file (D_800C356E, D_800C356F) unless loaded

#endif // SCENE_H
